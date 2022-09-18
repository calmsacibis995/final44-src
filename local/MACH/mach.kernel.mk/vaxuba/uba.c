/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	uba.c,v $
 * Revision 2.8  89/04/07  14:59:31  rvb
 * 	#ifdef VAX<foo> conditional in ubasetup should not be there
 * 	at all.  Caused kdb50 only systems to wait for buffered
 * 	data path.
 * 	[89/04/07            rvb]
 * 
 * Revision 2.7  89/03/09  22:40:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/26  11:09:11  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  88/08/22  21:35:29  mja
 * 	Updated #include uses.
 * 	[88/08/10  12:35:42  mja]
 * 	
 * 	Changed conditions around UBA_NEEDBDP to also remove BDPs for
 * 	kdb50 devices on machines w/ BI bus.  Have to check each unibus
 * 	transfer to see if the type is kdb50 since we fudge the uba
 * 	data structures for this device.
 * 	[88/08/10  12:35:42  berman]
 * 
 * Revision 2.4  88/08/11  13:26:54  rvb
 * We need an NBI > 0 conditional in ubainit because the structure being
 * referenced is not defined unless NBI > 0.  Further, some thought should
 * be given whether we should make it illegal to have VAX820, VAX8800 or VAX6200
 * without having bi.
 * 
 * Revision 2.3  88/08/10  10:53:47  rvb
 * Sorry: NBI stands by itself.  It is a bus for the 820, 8800, and
 * 6200.  Of course, if you build for the above processors w/o NBI > 0
 * you have just shot yourself in the foot.
 * 
 *
 * 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI:  augmented VAX820 conditionals to also require this symbol
 *	so that BI support can be omitted more easily without changing
 *	the cpu set.
 *	[ V5.1(XF24) ]
 *
 *  6-Nov-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for the Vax650.  Treat it just like a VAX630.
 *
 * 17-Sep-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	NET_UDA:  install updates for new uda driver from Chris Torek
 *	at UMD.
 *	[ V5.1(XF16) ]
 *
 * 22-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI: corrected conditionals for BI specific code.
 *	[ V5.1(F10) ]
 *
 * 10-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted under MACH_VM.
 *
 * 27-Aug-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed incorrect conditional in ubasetup() which caused mapping
 *	to fail unless MicroVax-1 support was enabled.
 *
 *  5-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for DWBUA.
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 17-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	VAX1:  Added hooks for MicroVAXen (a la ULTRIX-32).
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uba.c	7.1 (Berkeley) 6/5/86
 */
 
#include <bi.h>
#include <net_uda.h>
#ifdef	MACH
#include <cputypes.h>
#endif	MACH

#include <machine/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/vm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/dk.h>
#include <sys/kernel.h>

#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vax/nexus.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

#ifdef	MACH
#include <vm/pmap.h>
#include <kern/thread.h>

#endif	MACH
#if	defined(VAX780) || defined(VAX8600)
char	ubasr_bits[] = UBASR_BITS;
#endif

#define spluba	spl7		/* IPL 17 */

#if	NET_UDA
#define BDPMASK	0xf0000000	/* see ubavar.h */

/* 
 * Do transfer on device argument.  The controller 
 * and uba involved are implied by the device. 
 * We queue for resource wait in the uba code if necessary. 
 * We return 1 if the transfer was started, 0 if it was not. 
 *
 * The onq argument must be zero iff the device is not on the
 * queue for this UBA.  If onq is set, the device must be at the
 * head of the queue.  In any case, if the transfer is started,
 * the device will be off the queue, and if not, it will be on.
 *
 * Drivers that allocate one BDP and hold it for some time should
 * set ud_keepbdp.  In this case um_bdp tells which BDP is allocated
 * to the controller, unless it is zero, indicating that the controller
 * does not now have a BDP.
 */ 
ubaqueue(ui, onq)
 	register struct uba_device *ui;
	int onq;
#else	NET_UDA
/*
 * Do transfer on device argument.  The controller
 * and uba involved are implied by the device.
 * We queue for resource wait in the uba code if necessary.
 * We return 1 if the transfer was started, 0 if it was not.
 * If you call this routine with the head of the queue for a
 * UBA, it will automatically remove the device from the UBA
 * queue before it returns.  If some other device is given
 * as argument, it will be added to the request queue if the
 * request cannot be started immediately.  This means that
 * passing a device which is on the queue but not at the head
 * of the request queue is likely to be a disaster.
 */
ubago(ui)
	register struct uba_device *ui;
#endif	NET_UDA
{
	register struct uba_ctlr *um = ui->ui_mi;
	register struct uba_hd *uh;
#if	NET_UDA
	register struct uba_driver *ud = um->um_driver;
#endif	NET_UDA
	register int s, unit;

	uh = &uba_hd[um->um_ubanum];
	s = spluba();
#if	NET_UDA
	/*
	 * Honor exclusive BDP use requests.
	 */
	if (ud->ud_xclu && uh->uh_users > 0 || uh->uh_xclu)
 		goto rwait;
	if (ud->ud_keepbdp) {
		/*
		 * First get just a BDP (though in fact it comes with
		 * one map register too).
		 */
		if (um->um_bdp == 0) {
			um->um_bdp = uballoc(um->um_ubanum,
				(caddr_t)0, 0, UBA_NEEDBDP|UBA_CANTWAIT);
			if (um->um_bdp == 0)
				goto rwait;
		}
		/* now share it with this transfer */
		um->um_ubinfo = ubasetup(um->um_ubanum,
			um->um_tab.b_actf->b_actf,
			um->um_bdp|UBA_HAVEBDP|UBA_CANTWAIT);
	} else
		um->um_ubinfo = ubasetup(um->um_ubanum,
			um->um_tab.b_actf->b_actf, UBA_NEEDBDP|UBA_CANTWAIT);
#else	NET_UDA
	if (um->um_driver->ud_xclu && uh->uh_users > 0 || uh->uh_xclu)
		goto rwait;
	um->um_ubinfo = ubasetup(um->um_ubanum, um->um_tab.b_actf->b_actf,
	    UBA_NEEDBDP|UBA_CANTWAIT);
#endif	NET_UDA
	if (um->um_ubinfo == 0)
		goto rwait;
	uh->uh_users++;
#if	NET_UDA
	if (ud->ud_xclu)
#else	NET_UDA
	if (um->um_driver->ud_xclu)
#endif	NET_UDA
		uh->uh_xclu = 1;
	splx(s);
	if (ui->ui_dk >= 0) {
		unit = ui->ui_dk;
		dk_busy |= 1<<unit;
		dk_xfer[unit]++;
		dk_wds[unit] += um->um_tab.b_actf->b_actf->b_bcount>>6;
	}
#if	NET_UDA
	if (onq)
#else	NET_UDA
	if (uh->uh_actf == ui)
#endif	NET_UDA
		uh->uh_actf = ui->ui_forw;
#if	NET_UDA
	(*ud->ud_dgo)(um);
#else	NET_UDA
	(*um->um_driver->ud_dgo)(um);
#endif	NET_UDA
	return (1);
rwait:
#if	NET_UDA
	if (!onq) {
#else	NET_UDA
	if (uh->uh_actf != ui) {
#endif	NET_UDA
		ui->ui_forw = NULL;
		if (uh->uh_actf == NULL)
			uh->uh_actf = ui;
		else
			uh->uh_actl->ui_forw = ui;
		uh->uh_actl = ui;
	}
	splx(s);
	return (0);
}

ubadone(um)
	register struct uba_ctlr *um;
{
	register struct uba_hd *uh = &uba_hd[um->um_ubanum];

	if (um->um_driver->ud_xclu)
		uh->uh_xclu = 0;
	uh->uh_users--;
#if	NET_UDA
	if (um->um_driver->ud_keepbdp)
		um->um_ubinfo &= ~BDPMASK;	/* keep BDP for misers */
#endif	NET_UDA
#if	VAX1
	/* no map registers if it's a MicroVAX I */
	if(cpu != VAX_1)
#endif	VAX1
	ubarelse(um->um_ubanum, &um->um_ubinfo);
}

/*
 * Allocate and setup UBA map registers, and bdp's
 * Flags says whether bdp is needed, whether the caller can't
 * wait (e.g. if the caller is at interrupt level).
 *
 * Return value:
 *	Bits 0-8	Byte offset
 *	Bits 9-17	Start map reg. no.
 *	Bits 18-27	No. mapping reg's
 *	Bits 28-31	BDP no.
 */
ubasetup(uban, bp, flags)
	struct buf *bp;
{
	register struct uba_hd *uh = &uba_hd[uban];
	int pfnum, temp;
	int npf, reg, bdp;
#ifdef	MACH
#else	MACH
	unsigned v;
#endif	MACH
	register struct pte *pte, *io;
#ifdef	MACH
#else	MACH
	struct proc *rp;
#endif	MACH
	int a, o, ubinfo;

	if (cpu == VAX_730 || cpu == VAX_650 || 
	    cpu == VAX_630 || cpu == VAX_1 ||
	    uh->uh_type == UBATYPE_KDB50)	/* KDB50's don't have them */
		flags &= ~UBA_NEEDBDP;

#ifdef	MACH
#else	MACH
	v = btop(bp->b_un.b_addr);
#endif	MACH
	o = (int)bp->b_un.b_addr & PGOFSET;
	npf = btoc(bp->b_bcount + o) + 1;
	a = spluba();
	while ((reg = rmalloc(uh->uh_map, (long)npf)) == 0) {
		if (flags & UBA_CANTWAIT) {
			splx(a);
			return (0);
		}
		uh->uh_mrwant++;
		sleep((caddr_t)&uh->uh_mrwant, PSWP);
	}
	if ((flags & UBA_NEED16) && reg + npf > 128) {
		/*
		 * Could hang around and try again (if we can ever succeed).
		 * Won't help any current device...
		 */
		rmfree(uh->uh_map, (long)npf, (long)reg);
		splx(a);
		return (0);
	}
	bdp = 0;
	if (flags & UBA_NEEDBDP) {
		while ((bdp = ffs((long)uh->uh_bdpfree)) == 0) {
			if (flags & UBA_CANTWAIT) {
				rmfree(uh->uh_map, (long)npf, (long)reg);
				splx(a);
				return (0);
			}
			uh->uh_bdpwant++;
			sleep((caddr_t)&uh->uh_bdpwant, PSWP);
		}
		uh->uh_bdpfree &= ~(1 << (bdp-1));
	} else if (flags & UBA_HAVEBDP)
		bdp = (flags >> 28) & 0xf;
	splx(a);
	reg--;
	ubinfo = (bdp << 28) | (npf << 18) | (reg << 9) | o;
	temp = (bdp << 21) | UBAMR_MRV;
	if (bdp && (o & 01))
		temp |= UBAMR_BO;
#ifdef	MACH
	{
		vm_offset_t	addr;
		pmap_t		map;

		addr = (vm_offset_t)bp->b_un.b_addr;
		if ((bp->b_flags & B_PHYS) && ((addr & 0x80000000) == 0))
			map = vm_map_pmap(bp->b_proc->task->map);
		else
			map = pmap_kernel();
		pte = (struct pte *) pmap_pte(map, addr);
	}
#else	MACH
	rp = bp->b_flags&B_DIRTY ? &proc[2] : bp->b_proc;
	if ((bp->b_flags & B_PHYS) == 0)
		pte = &Sysmap[btop(((int)bp->b_un.b_addr)&0x7fffffff)];
	else if (bp->b_flags & B_UAREA)
		pte = &rp->p_addr[v];
	else if (bp->b_flags & B_PAGET)
		pte = &Usrptmap[btokmx((struct pte *)bp->b_un.b_addr)];
	else
		pte = vtopte(rp, v);
#endif	MACH
#if	VAX1
	if (cpu != VAX_1 || (flags&UBA_MAPANYWAY))
	{
#endif	VAX1
#if	NBI > 0
	/*
	 *	We can use the "old" definition here because
	 *	the uba mapping registers are at the same location.
	 */
#endif	NBI > 0
	io = &uh->uh_uba->uba_map[reg];
	while (--npf != 0) {
		pfnum = pte->pg_pfnum;
		if (pfnum == 0)
			panic("uba zero uentry");
		pte++;
		*(int *)io = pfnum | temp;
		io++;
	}
	*(int *)io++ = 0;
#if	VAX1
	} else	{
		ubinfo = contigphys( (caddr_t)ubinfo, (int)bp->b_bcount, pte);
		++reg;
		a = spluba();
		rmfree( uh->uh_map, (long)npf, (long)reg);
		splx(a);
	}
#endif	VAX1
	return (ubinfo);
}

/*
 * Non buffer setup interface... set up a buffer and call ubasetup.
 */
uballoc(uban, addr, bcnt, flags)
	int uban;
	caddr_t addr;
	int bcnt, flags;
{
	struct buf ubabuf;

	ubabuf.b_un.b_addr = addr;
	ubabuf.b_flags = B_BUSY;
	ubabuf.b_bcount = bcnt;
	/* that's all the fields ubasetup() needs */
	return (ubasetup(uban, &ubabuf, flags));
}
 
/*
 * Release resources on uba uban, and then unblock resource waiters.
 * The map register parameter is by value since we need to block
 * against uba resets on 11/780's.
 */
ubarelse(uban, amr)
	int *amr;
{
	register struct uba_hd *uh = &uba_hd[uban];
	register int bdp, reg, npf, s;
	int mr;
 
	/*
	 * Carefully see if we should release the space, since
	 * it may be released asynchronously at uba reset time.
	 */
	s = spluba();
	mr = *amr;
	if (mr == 0) {
		/*
		 * A ubareset() occurred before we got around
		 * to releasing the space... no need to bother.
		 */
		splx(s);
		return;
	}
	*amr = 0;
	bdp = (mr >> 28) & 0x0f;
	if (bdp) {
#if	NBI > 0
		if (uh->uh_type == UBATYPE_DWBUA) {
			((struct dwbua_regs *)uh->uh_uba)->dpr[bdp] |=
				DWBUA_DPR_PURGE;
		}
		else {
#endif	NBI > 0
		switch (cpu) {
#if	defined(VAX780) || defined(VAX8600)
		case VAX_8600:
		case VAX_780:
			uh->uh_uba->uba_dpr[bdp] |= UBADPR_BNE;
			break;
#endif
#if	VAX750
		case VAX_750:
			uh->uh_uba->uba_dpr[bdp] |=
			    UBADPR_PURGE|UBADPR_NXM|UBADPR_UCE;
			break;
#endif
		}
#if	NBI > 0
		}
#endif	NBI > 0
		uh->uh_bdpfree |= 1 << (bdp-1);		/* atomic */
		if (uh->uh_bdpwant) {
			uh->uh_bdpwant = 0;
			wakeup((caddr_t)&uh->uh_bdpwant);
		}
	}
	/*
	 * Put back the registers in the resource map.
	 * The map code must not be reentered,
	 * nor can the registers be freed twice.
	 * Unblock interrupts once this is done.
	 */
	npf = (mr >> 18) & 0x3ff;
	reg = ((mr >> 9) & 0x1ff) + 1;
	rmfree(uh->uh_map, (long)npf, (long)reg);
	splx(s);

	/*
	 * Wakeup sleepers for map registers,
	 * and also, if there are processes blocked in dgo(),
	 * give them a chance at the UNIBUS.
	 */
	if (uh->uh_mrwant) {
		uh->uh_mrwant = 0;
		wakeup((caddr_t)&uh->uh_mrwant);
	}
#if	NET_UDA
	while (uh->uh_actf && ubaqueue(uh->uh_actf, 1))
#else	NET_UDA
	while (uh->uh_actf && ubago(uh->uh_actf))
#endif	NET_UDA
		;
}

ubapurge(um)
	register struct uba_ctlr *um;
{
	register struct uba_hd *uh = um->um_hd;
	register int bdp = (um->um_ubinfo >> 28) & 0x0f;

#if	NBI > 0
	if (uh->uh_type == UBATYPE_DWBUA) {
		((struct dwbua_regs *)uh->uh_uba)->dpr[bdp] |=
			DWBUA_DPR_PURGE;
		return;
	}
#endif	NBI > 0
	switch (cpu) {
#if	defined(VAX780) || defined(VAX8600)
	case VAX_8600:
	case VAX_780:
		uh->uh_uba->uba_dpr[bdp] |= UBADPR_BNE;
		break;
#endif
#if	VAX750
	case VAX_750:
		uh->uh_uba->uba_dpr[bdp] |= UBADPR_PURGE|UBADPR_NXM|UBADPR_UCE;
		break;
#endif
	}
}

ubainitmaps(uhp)
	register struct uba_hd *uhp;
{

	rminit(uhp->uh_map, (long)NUBMREG, (long)1, "uba", UAMSIZ);

	switch (cpu) {
	case VAX_8800:
	case VAX_820:
	case VAX_6200:
#if	NBI > 0
		if (uhp->uh_type == UBATYPE_DWBUA) {
			uhp->uh_bdpfree = (1<<NBDPBI) - 1;
			return;
		} else
			/* do what */;
#endif	NBI > 0
		break;
#if	defined(VAX780) || defined(VAX8600)
	case VAX_8600:
	case VAX_780:
		uhp->uh_bdpfree = (1<<NBDP780) - 1;
		break;
#endif
#if	VAX750
	case VAX_750:
		uhp->uh_bdpfree = (1<<NBDP750) - 1;
		break;
#endif
#if	defined(VAX730) || defined(VAX650) || defined(VAX630)
	case VAX_730:
	case VAX_650:
	case VAX_630:
		break;
#endif
	}
}

/*
 * Generate a reset on uba number uban.  Then
 * call each device in the character device table,
 * giving it a chance to clean up so as to be able to continue.
 */
ubareset(uban)
	int uban;
{
	register struct cdevsw *cdp;
	register struct uba_hd *uh = &uba_hd[uban];
	int s;

	s = spluba();
	uh->uh_users = 0;
	uh->uh_zvcnt = 0;
	uh->uh_xclu = 0;
	uh->uh_actf = uh->uh_actl = 0;
	uh->uh_bdpwant = 0;
	uh->uh_mrwant = 0;
	ubainitmaps(uh);
	wakeup((caddr_t)&uh->uh_bdpwant);
	wakeup((caddr_t)&uh->uh_mrwant);
	printf("uba%d: reset", uban);
	ubainit(uh->uh_uba);
	ubameminit(uban);
	for (cdp = cdevsw; cdp < cdevsw + nchrdev; cdp++)
		(*cdp->d_reset)(uban);
	ifubareset(uban);
	printf("\n");
	splx(s);
}

/*
 * Init a uba.  This is called with a pointer
 * rather than a virtual address since it is called
 * by code which runs with memory mapping disabled.
 * In these cases we really don't need the interrupts
 * enabled, but since we run with ipl high, we don't care
 * if they are, they will never happen anyways.
 */
ubainit(uba)
	register struct uba_regs *uba;
{

	switch (cpu) {
	/*
	 *	This should depend on DWBUA, not VAX820, but there
	 *	is currently no way of knowing.
	 */
#if	VAX8800 || VAX820 || VAX6200
	case VAX_8800:
	case VAX_820:
	case VAX_6200:
#if	NBI > 0
		((struct dwbua_regs *)uba)->csr |= DWBUA_CSR_UPI;
#endif	NBI > 0
		break;
#endif	VAX8800 || VAX820 || VAX6200
#if	defined(VAX780) || defined(VAX8600)
	case VAX_8600:
	case VAX_780:
		uba->uba_cr = UBACR_ADINIT;
		uba->uba_cr = UBACR_IFS|UBACR_BRIE|UBACR_USEFIE|UBACR_SUEFIE;
		while ((uba->uba_cnfgr & UBACNFGR_UBIC) == 0)
			;
		break;
#endif
#if	VAX750
	case VAX_750:
#endif
#if	VAX730
	case VAX_730:
#endif
#if	VAX650
	case VAX_650:
#endif
#if	VAX630
	case VAX_630:
#endif
#if	VAX1
	case VAX_1:
#endif	VAX1
#if	defined(VAX750) || defined(VAX730) || defined(VAX650) || defined(VAX630)
		mtpr(IUR, 0);
		/* give devices time to recover from power fail */
/* THIS IS PROBABLY UNNECESSARY */
		DELAY(500000);
/* END PROBABLY UNNECESSARY */
		break;
#endif
	}
}

#if	defined(VAX780) || defined(VAX8600)
int	ubawedgecnt = 10;
int	ubacrazy = 500;
int	zvcnt_max = 5000;	/* in 8 sec */
/*
 * This routine is called by the locore code to process a UBA
 * error on an 11/780 or 8600.  The arguments are passed
 * on the stack, and value-result (through some trickery).
 * In particular, the uvec argument is used for further
 * uba processing so the result aspect of it is very important.
 * It must not be declared register.
 */
/*ARGSUSED*/
ubaerror(uban, uh, ipl, uvec, uba)
	register int uban;
	register struct uba_hd *uh;
	int ipl, uvec;
	register struct uba_regs *uba;
{
	register sr, s;

#if	NBI > 0
	if (uh->uh_type == UBATYPE_DWBUA) {
		printf("ubaerror called with DWBUA\n");
		printf("We were wrong, we thought this couldn't be called\n");
		return;
	}
#endif	NBI > 0
	if (uvec == 0) {
		/*
		 * Declare dt as unsigned so that negative values
		 * are handled as >8 below, in case time was set back.
		 */
		u_long	dt = time.tv_sec - uh->uh_zvtime;

		uh->uh_zvtotal++;
		if (dt > 8) {
			uh->uh_zvtime = time.tv_sec;
			uh->uh_zvcnt = 0;
		}
		if (++uh->uh_zvcnt > zvcnt_max) {
			printf("uba%d: too many zero vectors (%d in <%d sec)\n",
				uban, uh->uh_zvcnt, dt + 1);
			printf("\tIPL 0x%x\n\tcnfgr: %b  Adapter Code: 0x%x\n",
				ipl, uba->uba_cnfgr&(~0xff), UBACNFGR_BITS,
				uba->uba_cnfgr&0xff);
			printf("\tsr: %b\n\tdcr: %x (MIC %sOK)\n",
				uba->uba_sr, ubasr_bits, uba->uba_dcr,
				(uba->uba_dcr&0x8000000)?"":"NOT ");
			ubareset(uban);
		}
		return;
	}
	if (uba->uba_cnfgr & NEX_CFGFLT) {
		printf("uba%d: sbi fault sr=%b cnfgr=%b\n",
		    uban, uba->uba_sr, ubasr_bits,
		    uba->uba_cnfgr, NEXFLT_BITS);
		ubareset(uban);
		uvec = 0;
		return;
	}
	sr = uba->uba_sr;
	s = spluba();
	printf("uba%d: uba error sr=%b fmer=%x fubar=%o\n",
	    uban, uba->uba_sr, ubasr_bits, uba->uba_fmer, 4*uba->uba_fubar);
	splx(s);
	uba->uba_sr = sr;
	uvec &= UBABRRVR_DIV;
	if (++uh->uh_errcnt % ubawedgecnt == 0) {
		if (uh->uh_errcnt > ubacrazy)
			panic("uba crazy");
		printf("ERROR LIMIT ");
		ubareset(uban);
		uvec = 0;
		return;
	}
	return;
}
#endif

/*
 * Look for devices with unibus memory, allow them to configure, then disable
 * map registers as necessary.  Called during autoconfiguration and ubareset.
 * The device ubamem routine returns 0 on success, 1 on success if it is fully
 * configured (has no csr or interrupt, so doesn't need to be probed),
 * and -1 on failure.
 */
ubameminit(uban)
{
	register struct uba_device *ui;
	register struct uba_hd *uh = &uba_hd[uban];
#ifdef	MACH
	caddr_t umembase = (caddr_t)unibus_start[uban] + 0x3e000;
	caddr_t addr;
#else	MACH
	caddr_t umembase = umem[uban] + 0x3e000, addr;
#endif	MACH
#define ubaoff(off)	((int)(off) & 0x1fff)

	uh->uh_lastmem = 0;
	for (ui = ubdinit; ui->ui_driver; ui++) {
		if (ui->ui_ubanum != uban && ui->ui_ubanum != '?')
			continue;
		if (ui->ui_driver->ud_ubamem) {
			/*
			 * During autoconfiguration, need to fudge ui_addr.
			 */
			addr = ui->ui_addr;
			ui->ui_addr = umembase + ubaoff(addr);
			switch ((*ui->ui_driver->ud_ubamem)(ui, uban)) {
			case 1:
				ui->ui_alive = 1;
				/* FALLTHROUGH */
			case 0:
				ui->ui_ubanum = uban;
				break;
			}
			ui->ui_addr = addr;
		}
	}
#if	defined(VAX780) || defined(VAX8600)
	/*
	 * On a 780, throw away any map registers disabled by rounding
	 * the map disable in the configuration register
	 * up to the next 8K boundary, or below the last unibus memory.
	 */
	if ((cpu == VAX_780) || (cpu == VAX_8600)) {
		register i;

		i = btop(((uh->uh_lastmem + 8191) / 8192) * 8192);
		while (i)
			(void) rmget(uh->uh_map, 1, i--);
	}
#endif
}

/*
 * Allocate UNIBUS memory.  Allocates and initializes
 * sufficient mapping registers for access.  On a 780,
 * the configuration register is setup to disable UBA
 * response on DMA transfers to addresses controlled
 * by the disabled mapping registers.
 * On a 780, should only be called from ubameminit, or in ascending order
 * from 0 with 8K-sized and -aligned addresses; freeing memory that isn't
 * the last unibus memory would free unusable map registers.
 * Doalloc is 1 to allocate, 0 to deallocate.
 */
ubamem(uban, addr, npg, doalloc)
	int uban, addr, npg, doalloc;
{
	register struct uba_hd *uh = &uba_hd[uban];
	register int a;
	int s;

	a = (addr >> 9) + 1;
	s = spluba();
	if (doalloc)
		a = rmget(uh->uh_map, npg, a);
	else
		rmfree(uh->uh_map, (long)npg, (long)a);
	splx(s);
	if (a) {
		register int i, *m;

		m = (int *)&uh->uh_uba->uba_map[a - 1];
		for (i = 0; i < npg; i++)
			*m++ = 0;	/* All off, especially 'valid' */
		i = addr + npg * 512;
		if (doalloc && i > uh->uh_lastmem)
			uh->uh_lastmem = i;
		else if (doalloc == 0 && i == uh->uh_lastmem)
			uh->uh_lastmem = addr;
#if	defined(VAX780) || defined(VAX8600)
		/*
		 * On a 780, set up the map register disable
		 * field in the configuration register.  Beware
		 * of callers that request memory ``out of order''
		 * or in sections other than 8K multiples.
		 * Ubameminit handles such requests properly, however.
		 */
		if ((cpu == VAX_780) || (cpu == VAX_8600)) {
			i = uh->uh_uba->uba_cr &~ 0x7c000000;
			i |= ((uh->uh_lastmem + 8191) / 8192) << 26;
			uh->uh_uba->uba_cr = i;
		}
#endif
	}
	return (a);
}

#include <ik.h>
#include <vs.h>
#if	NIK > 0 || NVS > 0
/*
 * Map a virtual address into users address space. Actually all we
 * do is turn on the user mode write protection bits for the particular
 * page of memory involved.
 */
maptouser(vaddress)
	caddr_t vaddress;
{

	Sysmap[(((unsigned)(vaddress))-0x80000000) >> 9].pg_prot = (PG_UW>>27);
}

unmaptouser(vaddress)
	caddr_t vaddress;
{

	Sysmap[(((unsigned)(vaddress))-0x80000000) >> 9].pg_prot = (PG_KW>>27);
}
#endif
#if	VAX1

/*
 * convert virtual address to physical address, check that region is
 * contiguous.
 */
contigphys( va, size, pte)
 caddr_t	va;
 int		size;
 struct pte	*pte;
{
	int	physaddr;
	int	npte, pfn;

	physaddr = (int) va & PGOFSET;
	npte = btoc( size + physaddr);
	pfn = pte->pg_pfnum;
	physaddr |= pfn << 9;
	while( --npte > 0) {
		if( (++pte)->pg_pfnum != pfn+1) {
			printf( "contigphys: non-contiguous request\n");
			printf( " va=%x, size=%d, pa=%x, npte=%d, pfn0=%x, pfn1=%x\n",
				va, size, physaddr, npte, pfn, pte->pg_pfnum);
			return	0;
		}
		pfn = pte->pg_pfnum;
	}
	return	physaddr;
}
#endif	VAX1
