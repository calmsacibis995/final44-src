/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_ix.c,v $
 * Revision 2.3  89/03/09  22:27:09  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  10:54:13  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)if_ix.c	7.1 (Berkeley) 6/5/86
 */

#include <np.h>
#if	NNP > 0

/*
 * Interlan NP100 Ethernet Communications Controller interface
 */
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>

#ifdef	INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#endif

#ifdef	NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#endif

#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vaxif/if_uba.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
#include <vaxuba/npreg.h>
#include <vaxif/if_ix.h>

int	ixattach(), ixrint(), ixcint();
#define ILUNIT(x)	minor(x)
int	ixinit(), ixoutput(), ixioctl(), ixreset(), ixwatch();
int (*IxAttach)() = ixattach;
int (*IxReset)() = ixreset;

/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * ix_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 * We also have, for each interface, a UBA interface structure, which
 * contains information about the UNIBUS resources held by the interface:
 * map registers, buffered data paths, etc.  Information is cached in this
 * structure for use by the if_uba.c routines in running the interface
 * efficiently.
 */
struct	ix_softc {
	struct	arpcom ix_ac;		/* Ethernet common part */
#define ix_if	ix_ac.ac_if		/* network-visible interface */
#define ix_addr	ix_ac.ac_enaddr		/* hardware Ethernet address */
	int	ix_flags;
#define IXF_OACTIVE	0x1		/* output is active */
#define IXF_RCVPENDING	0x2		/* start rcv in ilcint */
#define IXF_GOTUBA	0x4		/* unibus resources mapped */
#define IXF_RUNNING	0x8		/* board is running */
#define IXF_SETADDR	0x10		/* physical address is changed */
#define IXF_STATPENDING	0x20		/* stat cmd pending */
#define IXF_GOTCQE	0x40		/* np resources available */
	struct	ifuba ix_ifuba;		/* unibus resources */
	u_short	ix_aid;			/* Access Id returned by open DDL */
	u_short ix_badcqe;
	struct	npmaster *ix_mp;	/* Board physio request header */
	struct	npreq *ix_rrp;		/* Cached npreq for recv */
	struct	npreq *ix_wrp;		/* Cached npreq for xmit */
	short	ix_scaninterval;	/* interval of stat collection */
#define IXWATCHINTERVAL	60		/* once every 60 seconds */
	union	ix_stats ix_stats;	/* holds on-board statistics */
	int	ix_ubaddr;		/* mapping registers of ix_stats */
} ix_softc[NNP];
extern struct uba_device *npdinfo[];

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.  We can't even get the ethernet address
 * or other interesting data until the board has been downloaded.
 * running ifconfig will attempt to start unit.
 */
ixattach(ui)
	struct uba_device *ui;
{
	register struct ix_softc *ix = &ix_softc[ui->ui_unit];
	register struct ifnet *ifp = &ix->ix_if;
	extern struct npmaster npmasters[];

	ifp->if_unit = ui->ui_unit;
	ifp->if_name = "ix";
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST;

	ifp->if_init = ixinit;
	ifp->if_output = ixoutput;
	ifp->if_ioctl = ixioctl;
	ifp->if_reset = ixreset;

	ix->ix_mp = npmasters + ui->ui_unit;
	ix->ix_ifuba.ifu_flags = UBA_CANTWAIT;

	if_attach(ifp);
}

struct npreq *
ix_GetReq(mp, addr, len)
	struct npmaster *mp;
	caddr_t addr;
{
	int unit = mp->unit;
	register struct npreq *rp;
	register struct CQE *ep;
	struct ix_softc *ix = ix_softc + unit;
	extern struct npreq *NpGetReq();

	while ((rp = NpGetReq(mp->reqtab)) == NULL) {
		mp->reqtab->flags |= WANTREQ;
		sleep((caddr_t)(mp->reqtab), PZERO - 1);
	}
	rp->flags = KERNREQ;			/* Clear flags */

	ep = rp->element;			/* Associated CQE */
	ep->cqe_famid = (unsign32)ix;		/* Process ID */
	ep->cqe_wind = 0;			/* Amount of buffer mapped */
	ep->cqe_nbuf = 1;			/* Must be 1, no buffer chain */
	ep->cqe_char = 1;			/* Driver owns this CQE */
	ep->cqe_prot = NPDLA;			/* Data Link Access  protocol */
	ep->cqe_bcnt = len;			/* Byte count */
	rp->bufaddr = (caddr_t) (UBADDRMASK & (int) addr);/* mapped buffer */
	ep->cqe_dma[0] = (unsign16)LOWORD(rp->bufaddr);
	ep->cqe_dma[1] = (unsign16)HIWORD(rp->bufaddr);
	return (rp);
}

ix_DoReq(mp, rp, cmd, addr, len, rpb, routine)
	struct npmaster *mp;
	register struct npreq *rp;
	u_short cmd;
	caddr_t addr;
	int len;
	register u_short *rpb;
	int (*routine)();
{
	register struct CQE *ep = rp->element;
	register u_short *p = &ep->rpb1;
	u_short cnt = *rpb++;
	extern long NpDebug;
	int pri;

	ep->cqe_ust0 = ep->cqe_ust1 = NPCLEAR;	/* Clear status */
	ep->cqe_bcnt = len;			/* Byte count */
	rp->flags = KERNREQ;			/* Clear flags */
	rp->bufaddr = (caddr_t) (UBADDRMASK & (int) addr);/* mapped buffer */
	rp->intr = routine;
	rp->user = (caddr_t) (ep->cqe_func = cmd);/* In case pissed on in CQE */
	ep->cqe_dma[0] = (unsign16)LOWORD(rp->bufaddr);
	ep->cqe_dma[1] = (unsign16)HIWORD(rp->bufaddr);
	ep->cqe_lenrpb = cnt + cnt;
	for (; cnt > 0; cnt--) *p++ = *rpb++;

	if (NpDebug & DEBCQE)
		printf("Function is %x ep %x reqid %x\n", ep->cqe_func, ep, ep->cqe_reqid);
	if (NpDebug & DEBCQE)
		printf("irp len = %x rp = %x\n", ep->cqe_lenrpb, rp);
	if (routine == 0) {
		NpAddReq(mp->reqtab, rp);	/* Queue onto active list */
		while (!(rp->flags & REQDONE)) {
			pri = spl4();
			NpAddCQE(ep, &mp->shmemp->devcq, mp);
			sleep((caddr_t)rp, PZERO - 1);
			splx(pri);
		}
		if (rp->flags & IOABORT || ep->cqe_sts != NPDONE
		    || ep->cqe_ust0 != NPDONE
		    || ep->cqe_ust1 != NPOK) {
			struct ix_softc *ix = (struct ix_softc *)ep->cqe_famid;
			printf("ix%d: Req failed, cmd %x, stat %x, ",
				ix->ix_if.if_unit, rp->user, ep->cqe_sts);
			printf("ust error %x,%x\n", ep->cqe_ust0, ep->cqe_ust1);
		}
		NpRemReq(rp);			/* Clear request */
	} else {
		pri = spl4();
		NpAddCQE(ep, &mp->shmemp->devcq, mp);
		splx(pri);
	}
}

/*
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 */
ixoutput(ifp, m0, dst)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
{
	int type, s, error;
 	u_char edst[6];
	struct in_addr idst;
	register struct ix_softc *ix = &ix_softc[ifp->if_unit];
	register struct mbuf *m = m0;
	register struct ether_header *il;
	register int off;
	int usetrailers;

	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}
	switch (dst->sa_family) {

#ifdef	INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
 		if (!arpresolve(&ix->ix_ac, m, &idst, edst, &usetrailers))
			return (0);	/* if not yet resolved */
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
		type = ETHERTYPE_IP;
		off = 0;
		goto gottype;
#endif
#ifdef	NS
	case AF_NS:
		type = ETHERTYPE_NS;
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		(caddr_t)edst, sizeof (edst));
		off = 0;
		goto gottype;
#endif

	case AF_UNSPEC:
		il = (struct ether_header *)dst->sa_data;
 		bcopy((caddr_t)il->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = il->ether_type;
		goto gottype;

	default:
		printf("ix%d: can't handle af%d\n", ifp->if_unit,
			dst->sa_family);
		error = EAFNOSUPPORT;
		goto bad;
	}

gottrailertype:
	/*
	 * Packet to be sent as trailer: move first packet
	 * (control information) to end of chain.
	 */
	while (m->m_next)
		m = m->m_next;
	m->m_next = m0;
	m = m0->m_next;
	m0->m_next = 0;
	m0 = m;

gottype:
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF ||
	    MMINOFF + sizeof (struct ether_header) > m->m_off) {
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			error = ENOBUFS;
			goto bad;
		}
		m->m_next = m0;
		m->m_off = MMINOFF;
		m->m_len = sizeof (struct ether_header);
	} else {
		m->m_off -= sizeof (struct ether_header);
		m->m_len += sizeof (struct ether_header);
	}
	il = mtod(m, struct ether_header *);
	il->ether_type = htons((u_short)type);
 	bcopy((caddr_t)edst, (caddr_t)il->ether_dhost, sizeof (edst));
 	bcopy((caddr_t)ix->ix_addr, (caddr_t)il->ether_shost,
	    sizeof(il->ether_shost));

	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splimp();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(s);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	if ((ix->ix_flags & IXF_OACTIVE) == 0)
		ixstart(ifp->if_unit);
	splx(s);
	return (0);

bad:
	m_freem(m0);
	return (error);
}
/*
 * Reset of interface after UNIBUS reset.
 * If interface is on specified uba, reset its state.
 */
ixreset(unit, uban, softp)
	int unit, uban;
	caddr_t softp;
{
	register struct uba_device *ui;
	int mask = IXF_SETADDR;		/* Only remember new physaddr */

	if (unit >= NNP || (ui = npdinfo[unit]) == 0 || ui->ui_alive == 0 ||
	    ui->ui_ubanum != uban)
		return;
	printf(" ix%d reset", unit);
	if (softp) 
		mask |= IXF_GOTUBA;	/* UBA mapping regs still valid; */
	ix_softc[unit].ix_if.if_flags &= ~IFF_RUNNING;
	ix_softc[unit].ix_flags &= mask;
}


/*
 * Initialization of interface; clear recorded pending
 * operations, and reinitialize UNIBUS usage.
 */
ixinit(unit)
	int unit;
{
	register struct ix_softc *ix = &ix_softc[unit];
	struct uba_device *ui = npdinfo[unit];
	register struct ifnet *ifp = &ix->ix_if;
	register struct CQE *ep;
	struct npreq *rp;
	struct npmaster *mp = ix->ix_mp;
	register u_short *dpmp = & mp->shmemp->statblock.sb_dpm;
	u_short rpb[7];
	int s;

	/* not yet, if address still unknown */
	if (ifp->if_addrlist == (struct ifaddr *)0)
		return;
	if (ix->ix_flags & IXF_RUNNING)
		return;
	if ((mp->flags & AVAILABLE) == 0 || (*dpmp & PROTOMASK(NPDLA)) == 0) {
		ifp->if_flags &= ~IFF_UP;
		return;
	}
	if ((ix->ix_flags & IXF_GOTUBA) == 0) {
		ix->ix_ifuba.ifu_flags = UBA_CANTWAIT;
		if (if_ubainit(&ix->ix_ifuba, ui->ui_ubanum,
		    sizeof (struct ether_header), (int)btoc(ETHERMTU)) == 0) { 
			printf("ix%d: can't initialize\n", unit);
			ix->ix_if.if_flags &= ~IFF_UP;
			return;
		}
		ix->ix_ubaddr = uballoc(ui->ui_ubanum, (caddr_t)&ix->ix_stats,
			sizeof (union ix_stats), 0);
		ix->ix_flags |= IXF_GOTUBA;
	}
	if ((ix->ix_flags & IXF_GOTCQE) == 0) {
		ix->ix_rrp = ix_GetReq(mp, ix->ix_ifuba.ifu_r.ifrw_info,
								ETHERMTU);
		ix->ix_wrp = ix_GetReq(mp, 0, 0);
		ix->ix_flags |= IXF_GOTCQE;
	}

	rp = ix->ix_wrp;
	ep = rp->element;

	/* Changing the ethernet address resets the dla module,
	   so must do it before opening the channel */
	if (ix->ix_flags & IXF_SETADDR) {
		register char *cp = (char *) &ix->ix_stats;
		int spincount;
		int x;
		*cp++ = 1;
		bcopy(ix->ix_addr, (caddr_t)cp, 6);
		rpb[0] = 1;				/* RPB length */
		ix_DoReq(mp, rp, IXC_LDPA, ix->ix_ubaddr, 7, rpb, 0);
#ifndef	TheyFinallyFixedTheBoard
		/* Board requires some time to reinitialize its protocols */
		x = spl1();
		spincount = 2000000;
		while (((*dpmp & PROTOMASK(NPDLA))==0) && spincount > 0)
			spincount--;
		if (spincount==0) {
			printf("ix%d: failed to reinitialize DLA module\n",
					unit);
			splx(x);
		}
		splx(x);
#endif
	}
	rpb[0] = 6;		/* RPB length */
	rpb[2] = 0x10;		/* Share with any smart users */
	rpb[3] = 0;		/* Take (a copy of) all frames */
	rpb[5] = 8;		/* On board rcv queue length */
	rpb[6] = 0;		/* XMT packets as is */
	ix_DoReq(mp, rp, IXC_OPEN, 0, 0, rpb, 0);

	ix->ix_aid = ep->rpb1;

	/* Here we request our ethernet address, if we didn't reset it*/
	if ((ix->ix_flags & IXF_SETADDR)==0) {
		rpb[0] = 2;
		rpb[1] = ix->ix_aid;
		rpb[2] = 0;		/* get all stats */
		ix_DoReq(mp, rp, IXC_GSTAT,	/* Get Stats */
			 (caddr_t) ix->ix_ubaddr, sizeof(ix->ix_stats) - 8,
			 rpb, 0);
		bcopy((caddr_t) &ix->ix_stats, (caddr_t) ix->ix_addr, 6);
	}
	ix->ix_if.if_flags |= IFF_RUNNING;
	ix->ix_flags |= IXF_RUNNING;
	ifp->if_watchdog = ixwatch;
	ifp->if_timer = ix->ix_scaninterval = IXWATCHINTERVAL;
	ixrint(mp, 0);
}

/*
 * Start output on interface.
 * Get another datagram to send off of the interface queue,
 * and map it to the interface before starting the output.
 */
ixstart(dev)
dev_t dev;
{
        int len = 0;
	int unit = minor(dev);
	register struct ix_softc *ix = &ix_softc[unit];
	register struct mbuf *n;
	struct mbuf *m;
	int s, error = 0;
	struct npmaster *mp = ix->ix_mp;
	struct npreq *rp = ix->ix_wrp;
	struct CQE *ep;
	u_short rpb[8];

	IF_DEQUEUE(&ix->ix_if.if_snd, m);
	if (m == 0) {
		if (ix->ix_flags & IXF_STATPENDING) {
			ix->ix_flags |= IXF_OACTIVE;
			rpb[0] = 2;
			rpb[1] = ix->ix_aid;
			rpb[2] = 0;			/* get all stats */
			ix_DoReq(mp, rp, IXC_GSTAT,	/* general Stats */
				 (caddr_t) ix->ix_ubaddr, sizeof(ix->ix_stats) - 8,
				 rpb, ixcint);
		}
		return;
	}
	/*
	 * Ensure minimum packet length.
	 * This makes the safe assumtion that there are no virtual holes
	 * after the data.
	 * For security, it might be wise to zero out the added bytes,
	 * but we're mainly interested in speed at the moment.
	 */
	len = if_wubaput(&ix->ix_ifuba, m);
	if (len - sizeof(struct ether_header) < ETHERMIN)
		len = ETHERMIN + sizeof(struct ether_header);

	ix->ix_flags |= IXF_OACTIVE;

	/* Now setup to call np driver */
	rpb[0] = 8;
	rpb[1] = ix->ix_aid;
	ix_DoReq(mp, rp, IXC_XMIT,			 /* send frame */
		    ix->ix_ifuba.ifu_w.ifrw_info, len, rpb, ixcint);
}

/*
 * Command done interrupt. (almost)
 */
ixcint(mp, rp)
	struct npmaster *mp;
	struct npreq *rp;
{
	struct CQE *ep;
	register struct ix_softc *ix;
	int s = splimp();

	ep = rp->element;
	ix = (struct ix_softc *)ep->cqe_famid;
	if ((ix->ix_flags & IXF_OACTIVE) == 0) {
		printf("ix%d: stray xmit interrupt, npreq=%x\n",
			ix->ix_if.if_unit, rp);
	}
	ix->ix_flags &= ~IXF_OACTIVE;

	switch (ep->cqe_func) {

	case IXC_XMIT:
		if (ep->cqe_sts == 1)
			ix->ix_if.if_opackets++;
		else
			ix->ix_if.if_oerrors++;
		break;

	case IXC_GSTAT:
		if (ep->cqe_sts == 1)
			ix->ix_if.if_collisions = ix->ix_stats.ixg.macg_xrty;
		break;
	}
	if (ix->ix_ifuba.ifu_xtofree) {
		m_freem(ix->ix_ifuba.ifu_xtofree);
		ix->ix_ifuba.ifu_xtofree = 0;
	}
done:
	ixstart(ix->ix_if.if_unit);
	splx(s);
}

/*
 * Ethernet interface receiver interrupt.
 * If input error just drop packet.
 * Otherwise purge input buffered data path and examine 
 * packet to determine type.  If can't determine length
 * from type, then have to drop packet.  Othewise decapsulate
 * packet based on type and pass to type specific higher-level
 * input routine.
 */
ixrint(mp, rp)
	struct npmaster *mp;
	struct npreq *rp;
{
	struct CQE *ep;
	register struct ix_softc *ix = ix_softc + mp->unit;
	register struct ether_header *il;
    	struct mbuf *m;
	int len, off, resid, s;
	register struct ifqueue *inq;

	if ((ix->ix_flags & IXF_RUNNING) == 0)
		return;
	if (rp == 0)
		goto setup;
	ix->ix_flags &= ~IXF_RCVPENDING;
	ep = rp->element;
	ix->ix_if.if_ipackets++;
	if (ix->ix_ifuba.ifu_flags & UBA_NEEDBDP)
		UBAPURGE(ix->ix_ifuba.ifu_uba, ix->ix_ifuba.ifu_r.ifrw_bdp);
	il = (struct ether_header *)(ix->ix_ifuba.ifu_r.ifrw_addr);
	len = ep->cqe_bcnt - sizeof (struct ether_header);
	if (ep->cqe_sts != NPDONE
	    || ep->cqe_ust0 != NPDONE
	    || ep->cqe_ust1 != NPOK) {
		printf("ixrint: cqe error %x, %x, %x\n",
			ep->cqe_sts, ep->cqe_ust0, ep->cqe_ust1);
		if (++ix->ix_badcqe > 100) {
			ix->ix_badcqe = 0;
			printf("ixrint: shutting down unix dla\n");
			ix->ix_if.if_flags &= ~IFF_UP;
			return;
		}
		goto setup;
	}

	if ( len < 46 || len > ETHERMTU) {
		ix->ix_if.if_ierrors++;
#ifdef	notdef
		if (ix->ix_if.if_ierrors % 100 == 0)
			printf("ix%d: += 100 input errors\n", unit);
#endif
		goto setup;
	}

	/*
	 * Deal with trailer protocol: if type is trailer type
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	il->ether_type = ntohs((u_short)il->ether_type);
#define ildataaddr(il, off, type)	((type)(((caddr_t)((il)+1)+(off))))
	if (il->ether_type >= ETHERTYPE_TRAIL &&
	    il->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (il->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU)
			goto setup;		/* sanity */
		il->ether_type = ntohs(*ildataaddr(il, off, u_short *));
		resid = ntohs(*(ildataaddr(il, off+2, u_short *)));
		if (off + resid > len)
			goto setup;		/* sanity */
		len = off + resid;
	} else
		off = 0;
	if (len == 0)
		goto setup;

	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; ilget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	m = if_rubaget(&ix->ix_ifuba, len, off, &ix->ix_if);
	if (m == 0)
		goto setup;
	if (off) {
		struct ifnet *ifp;

		ifp = *(mtod(m, struct ifnet **));
		m->m_off += 2 * sizeof (u_short);
		m->m_len -= 2 * sizeof (u_short);
		*(mtod(m, struct ifnet **)) = ifp;
	}
	switch (il->ether_type) {

#ifdef	INET
	case ETHERTYPE_IP:
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

	case ETHERTYPE_ARP:
		arpinput(&ix->ix_ac, m);
		goto setup;
#endif
#ifdef	NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
	default:
		m_freem(m);
		goto setup;
	}

	s = splimp();
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else
		IF_ENQUEUE(inq, m);
	splx(s);

setup:
	/*
	 * Reset for next packet if possible.
	 * If waiting for transmit command completion, set flag
	 * and wait until command completes.
	 */
	if (rp == 0) {
		rp = ix->ix_rrp;
		rp->intr = ixrint;
		ep = rp->element;
	}
	len = ETHERMTU + sizeof(struct ether_header);

	/* Now setup to call np driver */
	/* Initializations of request structure */

	ep->cqe_func = IXC_RECV;			/* get frame */
	ep->cqe_ust0 = ep->cqe_ust1 = NPCLEAR;		/* Clear status */
	ep->cqe_bcnt = len;				/* Byte count */
	ep->cqe_lenrpb = 10;				/* RPB length */
	ep->rpb1 = ix->ix_aid;				/* which channel */
	ep->rpb2 = 65535;				/* Timeout */

	ix->ix_flags |= IXF_RCVPENDING;

	s = spl4();
	NpAddCQE(ep, &mp->shmemp->devcq, mp); /* Add CQE to device's queue */
	splx(s);
}


/*
 * Watchdog routine, request statistics from board.
 */
ixwatch(unit)
	int unit;
{
	register struct ix_softc *ix = &ix_softc[unit];
	register struct ifnet *ifp = &ix->ix_if;
	int s;

	if (ix->ix_flags & IXF_STATPENDING) {
		ifp->if_timer = ix->ix_scaninterval;
		return;
	}
	s = splimp();
	ix->ix_flags |= IXF_STATPENDING;
	if ((ix->ix_flags & IXF_OACTIVE) == 0)
		ixstart(ifp->if_unit);
	splx(s);
	ifp->if_timer = ix->ix_scaninterval;
}
/*
 * Process an ioctl request.
 */
ixioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	register struct ix_softc *ix = &ix_softc[ifp->if_unit];
	int s = splimp(), error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		ixinit(ifp->if_unit);
		if ((ifp->if_flags & IFF_UP) == 0)
			return (EBUSY);

		switch (ifa->ifa_addr.sa_family) {
#ifdef	INET
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef	NS
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
			
			if (ns_nullhost(*ina)) {
				ina->x_host = * (union ns_host *) 
				     (ix_softc[ifp->if_unit].ix_addr);
			} else {
			    return
				ix_setaddr(ina->x_host.c_host, ifp->if_unit);
			}
			break;
		    }
#endif
		}
		break;

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ix->ix_flags & IXF_RUNNING) {
			ix->ix_flags &= ~IXF_RUNNING;
			NpReset(ix->ix_mp, 0);
		} else if (ifp->if_flags & IFF_UP &&
		    (ix->ix_flags & IXF_RUNNING) == 0)
			ixinit(ifp->if_unit);
		break;

	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}

/*
 * set ethernet address for unit
 */
ix_setaddr(physaddr, unit)
u_char *physaddr;
int unit;
{
	register struct ix_softc *ix = &ix_softc[unit];
	
	if (! (ix->ix_flags & IXF_RUNNING))
		return (EBUSY);

	/* The following is a big cop out due to the fact that
	   Changing the ethernet address resets the dla module,
	   so must re-open the channel, anyway. */


	bcopy((caddr_t)physaddr, (caddr_t)ix->ix_addr, sizeof ix->ix_addr);
	ix->ix_flags &= ~IXF_RUNNING;
	ix->ix_flags |= IXF_SETADDR;
	ixinit(unit);
	NpKill(ix->ix_mp, ix->ix_rrp);
}
#endif
