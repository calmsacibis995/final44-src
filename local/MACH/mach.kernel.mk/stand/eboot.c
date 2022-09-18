/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	eboot.c,v $
 * Revision 2.3  89/03/09  21:14:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:26:25  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
#include <vaxuba/dereg.h>

main()
{
        addr = ubamem();
	/*
	 * Reset the board and temporarily map
	 * the pcbb buffer onto the Unibus.
	 */
	addr->pcsr0 = PCSR0_RSET;
	(void)dewait(ui, "reset");

	ds->ds_ubaddr = uballoc(ui->ui_ubanum, (char *)&ds->ds_pcbb,
		sizeof (struct de_pcbb), 0);
	addr->pcsr2 = ds->ds_ubaddr & 0xffff;
	addr->pcsr3 = (ds->ds_ubaddr >> 16) & 0x3;
	addr->pclow = CMD_GETPCBB;
	(void)dewait(ui, "pcbb");

	ds->ds_pcbb.pcbb0 = FC_RDPHYAD;
	addr->pclow = CMD_GETCMD;
	(void)dewait(ui, "read addr ");

	ubarelse(ui->ui_ubanum, &ds->ds_ubaddr);
 	bcopy((caddr_t)&ds->ds_pcbb.pcbb2, (caddr_t)ds->ds_addr,
	    sizeof (ds->ds_addr));
	printf("de%d: hardware address %s\n", ui->ui_unit,
		ether_sprintf(ds->ds_addr));
	ifp->if_init = deinit;
	ifp->if_output = deoutput;
	ifp->if_ioctl = deioctl;
	ifp->if_reset = dereset;
	ds->ds_deuba.iff_flags = UBA_CANTWAIT;
#ifdef	notdef
	/* CAN WE USE BDP's ??? */
	ds->ds_deuba.iff_flags |= UBA_NEEDBDP;
#endif
	if_attach(ifp);
}

/*
 * Reset of interface after UNIBUS reset.
 * If interface is on specified uba, reset its state.
 */
dereset(unit, uban)
	int unit, uban;
{
	register struct uba_device *ui;

	if (unit >= NDE || (ui = deinfo[unit]) == 0 || ui->ui_alive == 0 ||
	    ui->ui_ubanum != uban)
		return;
	printf(" de%d", unit);
	de_softc[unit].ds_if.if_flags &= ~IFF_RUNNING;
	de_softc[unit].ds_flags &= ~(DSF_LOCK | DSF_RUNNING);
	deinit(unit);
}

/*
 * Initialization of interface; clear recorded pending
 * operations, and reinitialize UNIBUS usage.
 */
deinit(unit)
	int unit;
{
	register struct de_softc *ds = &de_softc[unit];
	register struct uba_device *ui = deinfo[unit];
	register struct dedevice *addr;
	register struct ifrw *ifrw;
	register struct ifxmt *ifxp;
	struct ifnet *ifp = &ds->ds_if;
	int s;
	struct de_ring *rp;
	int incaddr;

	/* not yet, if address still unknown */
	if (ifp->if_addrlist == (struct ifaddr *)0)
		return;

	if (ds->ds_flags & DSF_RUNNING)
		return;
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		if (if_ubaminit(&ds->ds_deuba, ui->ui_ubanum,
		    sizeof (struct ether_header), (int)btoc(ETHERMTU),
		    ds->ds_ifr, NRCV, ds->ds_ifw, NXMT) == 0) { 
			printf("de%d: can't initialize\n", unit);
			ds->ds_if.if_flags &= ~IFF_UP;
			return;
		}
		ds->ds_ubaddr = uballoc(ui->ui_ubanum, INCORE_BASE(ds),
			INCORE_SIZE, 0);
	}
	addr = (struct dedevice *)ui->ui_addr;

	/* set the pcbb block address */
	incaddr = ds->ds_ubaddr + PCBB_OFFSET;
	addr->pcsr2 = incaddr & 0xffff;
	addr->pcsr3 = (incaddr >> 16) & 0x3;
	addr->pclow = CMD_GETPCBB;
	(void)dewait(ui, "pcbb");

	/* set the transmit and receive ring header addresses */
	incaddr = ds->ds_ubaddr + UDBBUF_OFFSET;
	ds->ds_pcbb.pcbb0 = FC_WTRING;
	ds->ds_pcbb.pcbb2 = incaddr & 0xffff;
	ds->ds_pcbb.pcbb4 = (incaddr >> 16) & 0x3;

	incaddr = ds->ds_ubaddr + XRENT_OFFSET;
	ds->ds_udbbuf.b_tdrbl = incaddr & 0xffff;
	ds->ds_udbbuf.b_tdrbh = (incaddr >> 16) & 0x3;
	ds->ds_udbbuf.b_telen = sizeof (struct de_ring) / sizeof (short);
	ds->ds_udbbuf.b_trlen = NXMT;
	incaddr = ds->ds_ubaddr + RRENT_OFFSET;
	ds->ds_udbbuf.b_rdrbl = incaddr & 0xffff;
	ds->ds_udbbuf.b_rdrbh = (incaddr >> 16) & 0x3;
	ds->ds_udbbuf.b_relen = sizeof (struct de_ring) / sizeof (short);
	ds->ds_udbbuf.b_rrlen = NRCV;

	addr->pclow = CMD_GETCMD;
	(void)dewait(ui, "wtring");

	/* initialize the mode - enable hardware padding */
	ds->ds_pcbb.pcbb0 = FC_WTMODE;
	/* let hardware do padding - set MTCH bit on broadcast */
#if	CS_GENERIC
	ds->ds_pcbb.pcbb2 = MOD_TPAD|MOD_HDX|ds->ds_mode;
#else	CS_GENERIC
	ds->ds_pcbb.pcbb2 = MOD_TPAD|MOD_HDX;
#endif	CS_GENERIC
	addr->pclow = CMD_GETCMD;
	(void)dewait(ui, "wtmode");

	/* set up the receive and transmit ring entries */
	ifxp = &ds->ds_ifw[0];
	for (rp = &ds->ds_xrent[0]; rp < &ds->ds_xrent[NXMT]; rp++) {
		rp->r_segbl = ifxp->ifw_info & 0xffff;
		rp->r_segbh = (ifxp->ifw_info >> 16) & 0x3;
		rp->r_flags = 0;
		ifxp++;
	}
	ifrw = &ds->ds_ifr[0];
	for (rp = &ds->ds_rrent[0]; rp < &ds->ds_rrent[NRCV]; rp++) {
		rp->r_slen = sizeof (struct de_buf);
		rp->r_segbl = ifrw->ifrw_info & 0xffff;
		rp->r_segbh = (ifrw->ifrw_info >> 16) & 0x3;
		rp->r_flags = RFLG_OWN;		/* hang receive */
		ifrw++;
	}

	/* start up the board (rah rah) */
	s = splimp();
	ds->ds_rindex = ds->ds_xindex = ds->ds_xfree = ds->ds_nxmit = 0;
	ds->ds_if.if_flags |= IFF_RUNNING;
	destart(unit);				/* queue output packets */
	addr->pclow = PCSR0_INTE;		/* avoid interlock */
	ds->ds_flags |= DSF_RUNNING;		/* need before de_setaddr */
	if (ds->ds_flags & DSF_SETADDR)
		de_setaddr(ds->ds_addr, unit);
	addr->pclow = CMD_START | PCSR0_INTE;
	splx(s);
#if	DLI
	dli_init(&de_dlv[ui->ui_unit], ifp, ds->ds_addr, etherbroadcastaddr,
		 sizeof(etherbroadcastaddr), sizeof(struct ether_header));
#endif	DLI
}
}
