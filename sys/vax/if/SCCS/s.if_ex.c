h60293
s 00027/00027/00754
d D 7.9 90/12/16 16:51:25 bostic 24 23
c kernel reorg
e
s 00001/00011/00780
d D 7.8 90/06/28 22:51:28 bostic 23 22
c new copyright notice
e
s 00003/00004/00788
d D 7.7 90/06/20 19:07:24 sklower 22 21
c minor change to locate multicast address for ALL_ES and ALL_IS
e
s 00002/00001/00790
d D 7.6 90/04/03 11:30:25 karels 21 20
c needed start routine pointer
e
s 00054/00209/00737
d D 7.5 89/04/22 12:20:51 sklower 20 19
c changes for var. length sockaddrs; new routing; mv common ether input
c and output routines to if_ethersubr.c; checkpoint at first working iso/tp4
c connection and before gnodes.
e
s 00016/00003/00930
d D 7.4 88/08/04 15:20:11 bostic 19 18
c add Berkeley specific copyright
e
s 00002/00003/00931
d D 7.3 88/05/27 16:40:23 karels 18 17
c turn off debugging log/panics by default
e
s 00009/00006/00925
d D 7.2 86/10/13 16:57:09 karels 17 16
c must protect IF_ENQUEUE with splimp; s/printf/log/
e
s 00001/00001/00930
d D 7.1 86/06/05 17:06:18 mckusick 16 15
c 4.3BSD release version
e
s 00007/00006/00924
d D 6.14 86/02/23 23:28:35 karels 15 14
c lint
e
s 00000/00001/00930
d D 6.13 86/02/19 22:16:11 karels 14 13
c lint
e
s 00007/00009/00924
d D 6.12 86/01/31 14:20:41 karels 13 12
c typo
e
s 00010/00015/00923
d D 6.11 86/01/24 18:34:21 karels 12 11
c use per-host trailer option from ARP
e
s 00021/00018/00917
d D 6.10 86/01/07 14:31:50 mckusick 11 10
c fix for configuring multiple units (from Terry Slattery)
e
s 00000/00003/00935
d D 6.9 85/12/19 15:45:01 karels 10 9
c rm bbnnet
e
s 00063/00003/00875
d D 6.8 85/12/18 13:59:37 sklower 9 8
c XNS support for secondary boards -- reprogramming phys addr.
e
s 00032/00015/00846
d D 6.7 85/11/08 19:18:28 karels 8 7
c ifconfig down resets interface, ifconfig up reinitializes;
c return error when attempting to send to down interface
e
s 00002/00000/00859
d D 6.6 85/10/24 10:07:09 bloom 7 5
c add "#if N?? > 0" 
e
s 00000/00000/00859
d R 6.6 85/10/15 10:31:14 sklower 6 5
c Support XNS on a single interface.
e
s 00029/00000/00830
d D 6.5 85/09/05 18:18:56 sklower 5 4
c Put in support for XNS for machines not requiring the ethernet
c address to be reprogrammed.
e
s 00016/00003/00814
d D 6.4 85/09/05 11:25:16 karels 4 3
c new uba routines
e
s 00008/00002/00809
d D 6.3 85/06/08 13:55:31 mckusick 3 2
c Add copyright
e
s 00043/00054/00768
d D 6.2 85/06/03 08:41:28 karels 2 1
c now they compile at least
e
s 00822/00000/00000
d D 6.1 85/05/01 17:08:34 karels 1 0
c from Excelan
e
u
U
t
T
I 1
D 3
/*	%W% (Berkeley) %G% */
/*	from @(#)if_ex.c	1.4 (Excelan)	84/10/11 */
E 3
I 3
/*
D 16
 * Copyright (c) 1982 Regents of the University of California.
E 16
I 16
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 16
D 19
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
 * All rights reserved.
E 19
 *
I 19
 * This code is derived from software contributed to Berkeley by
 * Excelan Inc.
 *
D 23
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 23
I 23
 * %sccs.include.redist.c%
E 23
 *
E 19
 *	%W% (Berkeley) %G%
 */
D 19

E 19
E 3

#include "ex.h"
I 7
#if NEX > 0
E 7

/*
 * Excelan EXOS 204 Interface
 *
 *	George Powers
 *	Excelan Inc.
 */

D 18
#include "../machine/pte.h"

E 18
D 2
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/buf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/vmmac.h"
#include "../h/ioctl.h"
#include "../h/errno.h"
E 2
I 2
D 24
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "vmmac.h"
#include "ioctl.h"
I 17
#include "syslog.h"
E 17
#include "errno.h"
E 24
I 24
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/protosw.h"
#include "sys/socket.h"
#include "sys/vmmac.h"
#include "sys/ioctl.h"
#include "sys/syslog.h"
#include "sys/errno.h"
E 24
E 2

D 24
#include "../net/if.h"
#include "../net/netisr.h"
#include "../net/route.h"
E 24
I 24
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 24
I 4

D 10
#ifdef	BBNNET
#define	INET
#endif
E 10
#ifdef	INET
E 4
D 24
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
I 2
#include "../netinet/in_var.h"
E 2
#include "../netinet/ip.h"
D 4
#include "../netinet/ip_var.h"
E 4
#include "../netinet/if_ether.h"
E 24
I 24
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 24
I 4
#endif

E 4
I 2
D 8
#ifdef PUP
E 2
#include "../netpup/pup.h"
I 2
#endif
E 2

E 8
I 5
#ifdef NS
D 24
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 24
I 24
#include "netns/ns.h"
#include "netns/ns_if.h"
E 24
#endif

I 20
#ifdef ISO
D 24
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
E 24
I 24
#include "netiso/iso.h"
#include "netiso/iso_var.h"
E 24
D 22
#include "../netiso/iso_snpac.h"
extern struct snpa_cache all_es, all_is;
E 22
I 22
extern char all_es_snpa[], all_is_snpa[];
E 22
#endif

E 20
I 18
D 24
#include "../vax/pte.h"
E 18
E 5
#include "../vax/cpu.h"
#include "../vax/mtpr.h"
E 24
I 24
#include "../include/pte.h"
#include "../include/cpu.h"
#include "../include/mtpr.h"
E 24
D 2
#include "../vaxif/if_exreg.h"
#include "../vaxif/if_uba.h"
E 2
I 2
#include "if_exreg.h"
#include "if_uba.h"
E 2
D 24
#include "../vaxuba/ubareg.h"
#include "../vaxuba/ubavar.h"
E 24
I 24
#include "../uba/ubareg.h"
#include "../uba/ubavar.h"
E 24

D 18
#define DEBUG			/* check for "impossible" events */
E 18
I 18
/* #define DEBUG			/* check for "impossible" events */
E 18

#define	NH2X 4			/* a sufficient number is critical */
#define	NX2H 4			/* this is pretty arbitrary */
#define	EXWATCHINTVL 10		/* call exwatch() every 10 seconds */

int	exprobe(), exattach(), excdint();
struct	uba_device *exinfo[NEX];
u_short exstd[] = { 0 };
struct	uba_driver exdriver =
	{ exprobe, 0, exattach, 0, exstd, "ex", exinfo };
D 20
int	exinit(),exoutput(),exioctl(),exreset(),exwatch();
E 20
I 20
D 21
int	exinit(),ether_output(),exioctl(),exreset(),exwatch();
E 21
I 21
int	exinit(),exstart(),ether_output(),exioctl(),exreset(),exwatch();
E 21
E 20
struct ex_msg *exgetcbuf();

/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * xs_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 * We also have, for each interface, a UBA interface structure, which
 * contains information about the UNIBUS resources held by the interface:
 * map registers, buffered data paths, etc.  Information is cached in this
 * structure for use by the if_uba.c routines in running the interface
 * efficiently.
 */
struct	ex_softc {
D 2
#ifdef DEBUG
	int	xs_wait;
#endif
E 2
	struct	arpcom xs_ac;		/* Ethernet common part */
#define	xs_if	xs_ac.ac_if		/* network-visible interface */
#define	xs_addr	xs_ac.ac_enaddr		/* hardware Ethernet address */
I 2
#ifdef DEBUG
	int	xs_wait;
#endif
E 2
	struct	ifuba xs_ifuba;		/* UNIBUS resources */
	int	xs_flags;		/* private flags */
#define	EX_XPENDING	1		/* xmit rqst pending on EXOS */
#define	EX_STATPENDING	(1<<1)		/* stats rqst pending on EXOS */
I 8
#define	EX_RUNNING	(1<<2)		/* board is running */
I 9
#define EX_SETADDR	(1<<3)		/* physaddr has been changed */
E 9
E 8
	struct	ex_msg *xs_h2xnext;	/* host pointer to request queue */
	struct	ex_msg *xs_x2hnext;	/* host pointer to reply queue */
D 15
	u_long	xs_ubaddr;		/* map info for structs below */
E 15
I 15
	int	xs_ubaddr;		/* map info for structs below */
E 15
#define	UNIADDR(x)	((u_long)(x)&0x3FFFF)
#define	P_UNIADDR(x)	((u_long)(x)&0x3FFF0)
	/* the following structures are always mapped in */
	u_short	xs_h2xhdr;		/* EXOS's request queue header */
	u_short	xs_x2hhdr;		/* EXOS's reply queue header */
	struct	ex_msg xs_h2xent[NH2X];	/* request msg buffers */
	struct	ex_msg xs_x2hent[NX2H];	/* reply msg buffers */
	struct	confmsg xs_cm;		/* configuration message */
	struct	stat_array xs_xsa;	/* EXOS writes stats here */
	/* end mapped area */
D 15
#define	INCORE_BASE(p)	(((u_long)(&(p)->xs_h2xhdr)) & 0xFFFFFFF0)
E 15
I 15
#define	INCORE_BASE(p)	((caddr_t)((u_long)(&(p)->xs_h2xhdr) & 0xFFFFFFF0))
E 15
D 11
#define	RVAL_OFF(n)	((u_long)(&(ex_softc[0].n)) - INCORE_BASE(&ex_softc[0]))
#define	LVAL_OFF(n)	((u_long)(ex_softc[0].n) - INCORE_BASE(&ex_softc[0]))
#define	H2XHDR_OFFSET	RVAL_OFF(xs_h2xhdr)
#define	X2HHDR_OFFSET	RVAL_OFF(xs_x2hhdr)
#define	H2XENT_OFFSET	LVAL_OFF(xs_h2xent)
#define	X2HENT_OFFSET	LVAL_OFF(xs_x2hent)
#define	CM_OFFSET	RVAL_OFF(xs_cm)
#define	SA_OFFSET	RVAL_OFF(xs_xsa)
#define	INCORE_SIZE	RVAL_OFF(xs_end)
E 11
I 11
#define	RVAL_OFF(unit, n) \
D 15
	((u_long)(&(ex_softc[unit].n)) - INCORE_BASE(&ex_softc[unit]))
E 15
I 15
	((caddr_t)(&(ex_softc[unit].n)) - INCORE_BASE(&ex_softc[unit]))
E 15
#define	LVAL_OFF(unit, n) \
D 15
	((u_long)(ex_softc[unit].n) - INCORE_BASE(&ex_softc[unit]))
E 15
I 15
	((caddr_t)(ex_softc[unit].n) - INCORE_BASE(&ex_softc[unit]))
E 15
#define	H2XHDR_OFFSET(unit)	RVAL_OFF(unit, xs_h2xhdr)
#define	X2HHDR_OFFSET(unit)	RVAL_OFF(unit, xs_x2hhdr)
#define	H2XENT_OFFSET(unit)	LVAL_OFF(unit, xs_h2xent)
#define	X2HENT_OFFSET(unit)	LVAL_OFF(unit, xs_x2hent)
#define	CM_OFFSET(unit)		RVAL_OFF(unit, xs_cm)
#define	SA_OFFSET(unit)		RVAL_OFF(unit, xs_xsa)
#define	INCORE_SIZE(unit)	RVAL_OFF(unit, xs_end)
E 11
	int	xs_end;			/* place holder */
} ex_softc[NEX];

/*
 * The following structure is a kludge to store a cvec value
 * between the time exprobe is called, and exconfig.
 */
struct	ex_cvecs {
	struct	exdevice *xc_csraddr;
	int	xc_cvec;
}ex_cvecs[NEX];

int	ex_ncall = 0;			/* counts calls to exprobe */

exprobe(reg)
	caddr_t reg;
{
	register int br, cvec;		/* r11, r10 value-result */
	register struct exdevice *addr = (struct exdevice *)reg;
	register i;

	/*
	 * We program the EXOS interrupt vector, like dmf device.
	 */
	br = 0x15;
	cvec = (uba_hd[numuba].uh_lastiv -= 4);
D 13
#ifdef DEBUG
printf("exprobe%d: cvec = %o\n", ex_ncall, cvec);
#endif
E 13
	ex_cvecs[ex_ncall].xc_csraddr = addr;
D 13
	ex_cvecs[ex_ncall++].xc_cvec = cvec;
E 13
I 13
	ex_cvecs[ex_ncall].xc_cvec = cvec;
E 13
	/*
	 * Reset EXOS and run self-test (guaranteed to
	 * complete within 2 seconds).
	 */
	addr->xd_porta = EX_RESET;
D 13
	i = 1000000;
E 13
I 13
	i = 2000;
E 13
	while (((addr->xd_portb & EX_TESTOK) == 0) && --i)
D 13
		;
E 13
I 13
		DELAY(1000);
E 13
	if ((addr->xd_portb & EX_TESTOK) == 0) {
		printf("ex: self-test failed\n");
		return 0;
	}
I 4
#ifdef lint
	br = br;
I 15
	excdint(0);
E 15
#endif
I 13
	ex_ncall++;
E 13
E 4
	return (sizeof(struct exdevice));
}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.  Board is temporarily configured and issues
 * a NET_ADDRS command, only to get the Ethernet address.
 */
exattach(ui)
D 20
	struct uba_device *ui;
E 20
I 20
	register struct uba_device *ui;
E 20
{
	register struct ex_softc *xs = &ex_softc[ui->ui_unit];
	register struct ifnet *ifp = &xs->xs_if;
	register struct exdevice *addr = (struct exdevice *)ui->ui_addr;
D 2
	struct sockaddr_in *sin;
E 2
	register struct ex_msg *bp;
D 11

E 11
I 11
	int unit = ui->ui_unit;
E 11
	ifp->if_unit = ui->ui_unit;
	ifp->if_name = "ex";
	ifp->if_mtu = ETHERMTU;

	/*
	 * Temporarily map queues in order to configure EXOS
	 */
D 11
	xs->xs_ubaddr = uballoc(ui->ui_ubanum, INCORE_BASE(xs), INCORE_SIZE, 0);
E 11
I 11
	xs->xs_ubaddr = uballoc(ui->ui_ubanum, INCORE_BASE(xs),
		INCORE_SIZE(unit), 0);
E 11
	exconfig(ui, 0);			/* without interrupts */
	if (xs->xs_cm.cm_cc) goto badconf;

	bp = exgetcbuf(xs);
	bp->mb_rqst = LLNET_ADDRS;
	bp->mb_na.na_mask = READ_OBJ;
	bp->mb_na.na_slot = PHYSSLOT;
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
	bp = xs->xs_x2hnext;
	while ((bp->mb_status & MH_OWNER) == MH_EXOS)	/* poll for reply */
		;
D 12
	printf("ex%d: HW %c.%c, NX %c.%c, addr %x.%x.%x.%x.%x.%x\n",
		ui->ui_unit,
E 12
I 12
	printf("ex%d: HW %c.%c, NX %c.%c, hardware address %s\n",
D 13
		ui->ui_unit, ether_sprintf(bp->mb_na.na_addrs),
E 12
		xs->xs_cm.cm_vc[2], xs->xs_cm.cm_vc[3],
D 12
		xs->xs_cm.cm_vc[0], xs->xs_cm.cm_vc[1],
		bp->mb_na.na_addrs[0], bp->mb_na.na_addrs[1],
		bp->mb_na.na_addrs[2], bp->mb_na.na_addrs[3],
		bp->mb_na.na_addrs[4], bp->mb_na.na_addrs[5]);
E 12
I 12
		xs->xs_cm.cm_vc[0], xs->xs_cm.cm_vc[1]);
E 13
I 13
		ui->ui_unit, xs->xs_cm.cm_vc[2], xs->xs_cm.cm_vc[3],
		xs->xs_cm.cm_vc[0], xs->xs_cm.cm_vc[1],
		ether_sprintf(bp->mb_na.na_addrs));
E 13
E 12
	bcopy((caddr_t)bp->mb_na.na_addrs, (caddr_t)xs->xs_addr,
	    sizeof (xs->xs_addr));

D 2
	sin = (struct sockaddr_in *)&ifp->if_addr;
	sin->sin_family = AF_INET;
	sin->sin_addr = arpmyaddr((struct arpcom *)0);
E 2
	ifp->if_init = exinit;
D 20
	ifp->if_output = exoutput;
E 20
I 20
	ifp->if_output = ether_output;
I 21
	ifp->if_start = exstart;
E 21
E 20
	ifp->if_ioctl = exioctl;
	ifp->if_reset = exreset;
I 2
	ifp->if_flags = IFF_BROADCAST;
E 2
	xs->xs_ifuba.ifu_flags = UBA_CANTWAIT;
	if_attach(ifp);
badconf:
	ubarelse(ui->ui_ubanum, &xs->xs_ubaddr);
}

/*
 * Reset of interface after UNIBUS reset.
 * If interface is on specified uba, reset its state.
 */
exreset(unit, uban)
	int unit, uban;
{
	register struct uba_device *ui;

	if (unit >= NEX || (ui = exinfo[unit]) == 0 || ui->ui_alive == 0 ||
	    ui->ui_ubanum != uban)
		return;
	printf(" ex%d", unit);
I 2
	ex_softc[unit].xs_if.if_flags &= ~IFF_RUNNING;
I 8
	ex_softc[unit].xs_flags &= ~EX_RUNNING;
E 8
E 2
	exinit(unit);
}

/*
 * Initialization of interface; clear recorded pending
 * operations, and reinitialize UNIBUS usage.
 * Called at boot time (with interrupts disabled?),
 * and at ifconfig time via exioctl, with interrupts disabled.
 */
exinit(unit)
	int unit;
{
	register struct ex_softc *xs = &ex_softc[unit];
	register struct uba_device *ui = exinfo[unit];
	register struct exdevice *addr = (struct exdevice *)ui->ui_addr;
	register struct ifnet *ifp = &xs->xs_if;
D 2
	register struct sockaddr_in *sin;
E 2
	register struct ex_msg *bp;
	int s;

D 2
	sin = (struct sockaddr_in *)&ifp->if_addr;
	if (sin->sin_addr.s_addr == 0)		/* address still unknown */
E 2
I 2
	/* not yet, if address still unknown */
	if (ifp->if_addrlist == (struct ifaddr *)0)
E 2
		return;
D 8

	if (ifp->if_flags & IFF_RUNNING)
E 8
I 8
	if (xs->xs_flags & EX_RUNNING)
E 8
D 2
		goto justarp;
E 2
I 2
		return;
E 2
D 8
	if (if_ubainit(&xs->xs_ifuba, ui->ui_ubanum,
	    sizeof (struct ether_header),
	    (int)btoc(EXMAXRBUF-sizeof(struct ether_header))) == 0) { 
		printf("ex%d: can't initialize\n", unit);
		xs->xs_if.if_flags &= ~IFF_UP;
		return;
E 8
I 8

	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		if (if_ubainit(&xs->xs_ifuba, ui->ui_ubanum,
		    sizeof (struct ether_header),
		    (int)btoc(EXMAXRBUF-sizeof(struct ether_header))) == 0) { 
			printf("ex%d: can't initialize\n", unit);
			xs->xs_if.if_flags &= ~IFF_UP;
			return;
		}
		xs->xs_ubaddr = uballoc(ui->ui_ubanum, INCORE_BASE(xs),
D 11
			INCORE_SIZE, 0);
E 11
I 11
			INCORE_SIZE(unit), 0);
E 11
E 8
	}
D 8
	xs->xs_ubaddr = uballoc(ui->ui_ubanum, INCORE_BASE(xs), INCORE_SIZE, 0);
E 8
	exconfig(ui, 4);		/* with vectored interrupts*/
	/*
	 * Put EXOS on the Ethernet, using NET_MODE command
	 */
	bp = exgetcbuf(xs);
	bp->mb_rqst = LLNET_MODE;
	bp->mb_nm.nm_mask = WRITE_OBJ;
	bp->mb_nm.nm_optn = 0;
	bp->mb_nm.nm_mode = MODE_PERF;
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
	bp = xs->xs_x2hnext;
	while ((bp->mb_status & MH_OWNER) == MH_EXOS)	/* poll for reply */
		;
	bp->mb_length = MBDATALEN;
	bp->mb_status |= MH_EXOS;		/* free up buffer */
	addr->xd_portb = EX_NTRUPT;		/* tell EXOS about it */
	xs->xs_x2hnext = xs->xs_x2hnext->mb_next;

	ifp->if_watchdog = exwatch;
	ifp->if_timer = EXWATCHINTVL;
	s = splimp();	/* are interrupts always disabled here, anyway? */
	exhangrcv(unit);			/* hang receive request */
D 9
	exstart(unit);				/* start transmits */
E 9
D 2
	xs->xs_if.if_flags |= IFF_UP|IFF_RUNNING;
E 2
I 2
	xs->xs_if.if_flags |= IFF_RUNNING;
I 8
	xs->xs_flags |= EX_RUNNING;
I 9
	if (xs->xs_flags & EX_SETADDR)
D 15
		ex_setaddr(0, unit);
E 15
I 15
		ex_setaddr((u_char *)0, unit);
E 15
D 20
	exstart(unit);				/* start transmits */
E 20
I 20
#ifdef ISO
D 22
	ex_setmulti(all_es.sc_snpa, unit, 1);
	ex_setmulti(all_is.sc_snpa, unit, 2);
E 22
I 22
	ex_setmulti(all_es_snpa, unit, 1);
	ex_setmulti(all_is_snpa, unit, 2);
E 22
#endif
	(void) exstart(&xs->xs_if);			/* start transmits */
E 20
E 9
E 8
E 2
	splx(s);
D 2
justarp:
	if_rtinit(&xs->xs_if, RTF_UP);
	arpattach(&xs->xs_ac);
	arpwhohas(&xs->xs_ac, &sin->sin_addr);
E 2
}

/*
 * Reset, test, and configure EXOS.  This routine assumes
 * that message queues, etc. have already been mapped into
 * the UBA.  It is called by exinit, and should also be
 * callable by exattach.
 */
exconfig(ui, itype)
	struct	uba_device *ui;
	int itype;
{
	register int unit = ui->ui_unit;
	register struct ex_softc *xs = &ex_softc[unit];
	register struct exdevice *addr = (struct exdevice *) ui->ui_addr;
	register struct confmsg *cm = &xs->xs_cm;
	register struct ex_msg *bp;
	int i;
	u_long shiftreg;

	xs->xs_flags = 0;
	/*
	 * Reset EXOS, wait for self-test to complete
	 */
	addr->xd_porta = EX_RESET;
	while ((addr->xd_portb & EX_TESTOK) == 0)
		;
	/*
	 * Set up configuration message.
	 */
	cm->cm_1rsrv = 1;
	cm->cm_cc = 0xFF;
	cm->cm_opmode = 0;		/* link-level controller mode */
	cm->cm_dfo = 0x0101;		/* enable host data order conversion */
	cm->cm_dcn1 = 1;
D 20
	cm->cm_2rsrv[0] =
		cm->cm_2rsrv[1] = 0;
E 20
I 20
	cm->cm_2rsrv[0] = cm->cm_2rsrv[1] = 0;
E 20
	cm->cm_ham = 3;			/* absolute address mode */
	cm->cm_3rsrv = 0;
	cm->cm_mapsiz = 0;
	cm->cm_byteptrn[0] = 0x01;	/* EXOS deduces data order of host */
	cm->cm_byteptrn[1] = 0x03;	/*  by looking at this pattern */
	cm->cm_byteptrn[2] = 0x07;
	cm->cm_byteptrn[3] = 0x0F;
	cm->cm_wordptrn[0] = 0x0103;
	cm->cm_wordptrn[1] = 0x070F;
	cm->cm_lwordptrn = 0x0103070F;
	for (i=0; i<20; i++) cm->cm_rsrvd[i] = 0;
	cm->cm_mba = 0xFFFFFFFF;
	cm->cm_nproc = 0xFF;
	cm->cm_nmbox = 0xFF;
	cm->cm_nmcast = 0xFF;
	cm->cm_nhost = 1;
	cm->cm_h2xba = P_UNIADDR(xs->xs_ubaddr);
D 11
	cm->cm_h2xhdr = H2XHDR_OFFSET;
E 11
I 11
	cm->cm_h2xhdr = H2XHDR_OFFSET(unit);
E 11
	cm->cm_h2xtyp = 0;		/* should never wait for rqst buffer */
	cm->cm_x2hba = cm->cm_h2xba;
D 11
	cm->cm_x2hhdr = X2HHDR_OFFSET;
E 11
I 11
	cm->cm_x2hhdr = X2HHDR_OFFSET(unit);
E 11
	cm->cm_x2htyp = itype;		/* 0 for none, 4 for vectored */
	for (i=0; (addr != ex_cvecs[i].xc_csraddr); i++)
#ifdef DEBUG
	if (i >= NEX)
		panic("ex: matching csr address not found");
#endif
		;
	cm->cm_x2haddr = ex_cvecs[i].xc_cvec;	/* stashed here by exprobe */
	/*
	 * Set up message queues and headers.
	 * First the request queue.
	 */
	for (bp = &xs->xs_h2xent[0]; bp < &xs->xs_h2xent[NH2X]; bp++) {
		bp->mb_link = (u_short)((char *)(bp+1)-INCORE_BASE(xs));
		bp->mb_rsrv = 0;
		bp->mb_length = MBDATALEN;
		bp->mb_status = MH_HOST;
		bp->mb_next = bp+1;
	}
	xs->xs_h2xhdr =
D 20
		xs->xs_h2xent[NH2X-1].mb_link =
D 11
		(u_short)H2XENT_OFFSET;
E 11
I 11
		(u_short)H2XENT_OFFSET(unit);
E 11
	xs->xs_h2xnext =
		xs->xs_h2xent[NH2X-1].mb_next =
		xs->xs_h2xent;
E 20
I 20
		xs->xs_h2xent[NH2X-1].mb_link = (u_short)H2XENT_OFFSET(unit);
	xs->xs_h2xnext = xs->xs_h2xent[NH2X-1].mb_next = xs->xs_h2xent;
E 20

	/* Now the reply queue. */
	for (bp = &xs->xs_x2hent[0]; bp < &xs->xs_x2hent[NX2H]; bp++) {
		bp->mb_link = (u_short)((char *)(bp+1)-INCORE_BASE(xs));
		bp->mb_rsrv = 0;
		bp->mb_length = MBDATALEN;
		bp->mb_status = MH_EXOS;
		bp->mb_next = bp+1;
	}
	xs->xs_x2hhdr =
D 20
		xs->xs_x2hent[NX2H-1].mb_link =
D 11
		(u_short)X2HENT_OFFSET;
E 11
I 11
		(u_short)X2HENT_OFFSET(unit);
E 11
	xs->xs_x2hnext =
		xs->xs_x2hent[NX2H-1].mb_next =
		xs->xs_x2hent;
E 20
I 20
		xs->xs_x2hent[NX2H-1].mb_link = (u_short)X2HENT_OFFSET(unit);
	xs->xs_x2hnext = xs->xs_x2hent[NX2H-1].mb_next = xs->xs_x2hent;
E 20

	/*
	 * Write config msg address to EXOS and wait for
	 * configuration to complete (guaranteed response
	 * within 2 seconds).
	 */
	shiftreg = (u_long)0x0000FFFF;
	for (i = 0; i < 8; i++) {
		if (i == 4)
D 11
			shiftreg = P_UNIADDR(xs->xs_ubaddr) + CM_OFFSET;
E 11
I 11
			shiftreg = P_UNIADDR(xs->xs_ubaddr) + CM_OFFSET(unit);
E 11
		while (addr->xd_portb & EX_UNREADY)
			;
		addr->xd_portb = (u_char)(shiftreg & 0xFF);
		shiftreg >>= 8;
	}
	for (i = 1000000; (cm->cm_cc == 0xFF) && i; --i);
	if (cm->cm_cc)
		printf("ex%d: configuration failed; cc = %x\n",
			unit, cm->cm_cc);
}

/*
 * Start or re-start output on interface.
 * Get another datagram to send off of the interface queue,
 * and map it to the interface before starting the output.
D 20
 * This routine is called by exinit(), exoutput(), and excdint().
E 20
I 20
 * This routine is called by exinit(), ether_output(), and excdint().
E 20
 * In all cases, interrupts by EXOS are disabled.
 */
D 20
exstart(unit)
	int unit;
E 20
I 20
exstart(ifp)
struct ifnet *ifp;
E 20
{
I 20
	int unit = ifp->if_unit;
E 20
	struct uba_device *ui = exinfo[unit];
	register struct ex_softc *xs = &ex_softc[unit];
	register struct exdevice *addr = (struct exdevice *)ui->ui_addr;
	register struct ex_msg *bp;
	struct mbuf *m;
        int len;

#ifdef DEBUG
D 20
	if (xs->xs_flags & EX_XPENDING)
E 20
I 20
	if (xs->xs_if.if_flags & IFF_OACTIVE)
E 20
		panic("exstart(): xmit still pending");
#endif
	IF_DEQUEUE(&xs->xs_if.if_snd, m);
	if (m == 0)
D 20
		return;
E 20
I 20
		return (0);
E 20
	len = if_wubaput(&xs->xs_ifuba, m);
	if (len - sizeof(struct ether_header) < ETHERMIN)
		len = ETHERMIN + sizeof(struct ether_header);
	/*
	 * Place a transmit request.
	 */
	bp = exgetcbuf(xs);
	bp->mb_rqst = LLRTRANSMIT;
	bp->mb_et.et_nblock = 1;
	bp->mb_et.et_blks[0].bb_len = (u_short)len;
	*(u_long *)bp->mb_et.et_blks[0].bb_addr =
		UNIADDR(xs->xs_ifuba.ifu_w.ifrw_info);
D 20
	xs->xs_flags |= EX_XPENDING;
E 20
I 20
	xs->xs_if.if_flags |= IFF_OACTIVE;
E 20
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
I 20
	return (0);
E 20
}

/*
 * Command done interrupt.
 */
excdint(unit)
	int unit;
{
	register struct ex_softc *xs = &ex_softc[unit];
	register struct ex_msg *bp = xs->xs_x2hnext;
	struct uba_device *ui = exinfo[unit];
	struct exdevice *addr = (struct exdevice *)ui->ui_addr;

	while ((bp->mb_status & MH_OWNER) == MH_HOST) {
		switch (bp->mb_rqst) {
		case LLRECEIVE:
			exrecv(unit, bp);
			exhangrcv(unit);
			break;
		case LLRTRANSMIT:
#ifdef DEBUG
D 20
			if ((xs->xs_flags & EX_XPENDING) == 0)
E 20
I 20
			if ((xs->xs_if.if_flags & IFF_OACTIVE) == 0)
E 20
				panic("exxmit: no xmit pending");
#endif
D 20
			xs->xs_flags &= ~EX_XPENDING;
E 20
I 20
			xs->xs_if.if_flags &= ~IFF_OACTIVE;
E 20
			xs->xs_if.if_opackets++;
			if (bp->mb_rply == LL_OK) {
				;
			} else if (bp->mb_rply & LLXM_1RTRY) {
				xs->xs_if.if_collisions++;
			} else if (bp->mb_rply & LLXM_RTRYS) {
				xs->xs_if.if_collisions += 2;	/* guess */
			} else if (bp->mb_rply & LLXM_ERROR) {
				xs->xs_if.if_oerrors++;
D 17
				printf("ex%d: transmit error=%b\n",
E 17
I 17
				log(LOG_ERR, "ex%d: transmit error=%b\n",
E 17
					unit, bp->mb_rply, XMIT_BITS);
			}
			if (xs->xs_ifuba.ifu_xtofree) {
				m_freem(xs->xs_ifuba.ifu_xtofree);
				xs->xs_ifuba.ifu_xtofree = 0;
			}
D 20
			exstart(unit);
E 20
I 20
			(void) exstart(&xs->xs_if);
E 20
			break;
		case LLNET_STSTCS:
			xs->xs_if.if_ierrors = xs->xs_xsa.sa_crc;
			xs->xs_flags &= ~EX_STATPENDING;
			break;
I 9
		case LLNET_ADDRS:
		case LLNET_RECV:
			break;
E 9
#ifdef	DEBUG
		default:
			panic("ex%d: unknown reply");
#endif
		} /* end of switch */
		bp->mb_length = MBDATALEN;
		bp->mb_status |= MH_EXOS;		/* free up buffer */
		addr->xd_portb = EX_NTRUPT;		/* tell EXOS about it */
		bp = xs->xs_x2hnext = xs->xs_x2hnext->mb_next;
	}
}

/*
 * Get a request buffer, fill in standard values, advance pointer.
 */
struct ex_msg *
exgetcbuf(xs)
	struct ex_softc *xs;
{
	register struct ex_msg *bp = xs->xs_h2xnext;

#ifdef DEBUG
	if ((bp->mb_status & MH_OWNER) == MH_EXOS)
		panic("exgetcbuf(): EXOS owns message buffer");
#endif
	bp->mb_1rsrv = 0;
	bp->mb_length = MBDATALEN;
	xs->xs_h2xnext = xs->xs_h2xnext->mb_next;
	return bp;
}

/*
 * Process Ethernet receive completion:
 *	If input error just drop packet.
 *	Otherwise purge input buffered data path and examine 
 *	packet to determine type.  If can't determine length
 *	from type, then have to drop packet.  Otherwise decapsulate
 *	packet based on type and pass to type-specific higher-level
 *	input routine.
 */
exrecv(unit, bp)
	int unit;
	register struct ex_msg *bp;
{
	register struct ex_softc *xs = &ex_softc[unit];
	register struct ether_header *eh;
    	struct mbuf *m;
	register int len, off, resid;
	register struct ifqueue *inq;
I 17
	int s;
E 17

	xs->xs_if.if_ipackets++;
	len = bp->mb_er.er_blks[0].bb_len - sizeof(struct ether_header) - 4;
	if (bp->mb_rply != LL_OK) {
		xs->xs_if.if_ierrors++;
D 17
		printf("ex%d: receive error=%b\n",
E 17
I 17
		log(LOG_ERR, "ex%d: receive error=%b\n",
E 17
			unit, bp->mb_rply, RECV_BITS);
		return;
	}
	eh = (struct ether_header *)(xs->xs_ifuba.ifu_r.ifrw_addr);

	/*
D 2
	 * Deal with trailer protocol: if type is PUP trailer
E 2
I 2
	 * Deal with trailer protocol: if type is trailer
E 2
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	eh->ether_type = ntohs((u_short)eh->ether_type);
#define	exdataaddr(eh, off, type)	((type)(((caddr_t)((eh)+1)+(off))))
D 2
	if (eh->ether_type >= ETHERPUP_TRAIL &&
	    eh->ether_type < ETHERPUP_TRAIL+ETHERPUP_NTRAILER) {
		off = (eh->ether_type - ETHERPUP_TRAIL) * 512;
E 2
I 2
	if (eh->ether_type >= ETHERTYPE_TRAIL &&
	    eh->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eh->ether_type - ETHERTYPE_TRAIL) * 512;
E 2
		if (off >= ETHERMTU)
			return;		/* sanity */
		eh->ether_type = ntohs(*exdataaddr(eh, off, u_short *));
		resid = ntohs(*(exdataaddr(eh, off+2, u_short *)));
		if (off + resid > len)
			return;		/* sanity */
		len = off + resid;
	} else
		off = 0;
	if (len == 0)
		return;

	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; if_rubaget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
D 4
	m = if_rubaget(&xs->xs_ifuba, len, off);
E 4
I 4
	m = if_rubaget(&xs->xs_ifuba, len, off, &xs->xs_if);
E 4
	if (m == 0)
		return;
D 20
	if (off) {
I 4
		struct ifnet *ifp;

		ifp = *(mtod(m, struct ifnet **));
E 4
		m->m_off += 2 * sizeof (u_short);
		m->m_len -= 2 * sizeof (u_short);
I 4
		*(mtod(m, struct ifnet **)) = ifp;
E 4
	}
	switch (eh->ether_type) {

#ifdef INET
D 2
	case ETHERPUP_IPTYPE:
E 2
I 2
	case ETHERTYPE_IP:
E 2
		schednetisr(NETISR_IP);	/* is this necessary */
		inq = &ipintrq;
		break;

D 2
	case ETHERPUP_ARPTYPE:
E 2
I 2
	case ETHERTYPE_ARP:
E 2
		arpinput(&xs->xs_ac, m);
		return;
#endif
I 5
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
E 5
	default:
		m_freem(m);
		return;
	}

I 17
	s = splimp();
E 17
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
D 17
		return;
	}
	IF_ENQUEUE(inq, m);
E 17
I 17
	} else
		IF_ENQUEUE(inq, m);
	splx(s);
E 20
I 20
	ether_input(&xs->xs_if, eh, m);
E 20
E 17
}

/*
 * Send receive request to EXOS.
 * This routine is called by exinit and excdint,
 * with interrupts disabled in both cases.
 */
exhangrcv(unit)
	int unit;
{
	register struct ex_softc *xs = &ex_softc[unit];
	register struct ex_msg *bp = exgetcbuf(xs);
	struct exdevice *addr = (struct exdevice *)exinfo[unit]->ui_addr;
	
	bp->mb_rqst = LLRECEIVE;
	bp->mb_er.er_nblock = 1;
	bp->mb_er.er_blks[0].bb_len = EXMAXRBUF;
	*(u_long *)bp->mb_er.er_blks[0].bb_addr =
		UNIADDR(xs->xs_ifuba.ifu_r.ifrw_info);
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
}

/*
D 20
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 */
exoutput(ifp, m0, dst)
	register struct ifnet *ifp;
	register struct mbuf *m0;
	struct sockaddr *dst;
{
	int type, s, error;
	u_char edst[6];
	struct in_addr idst;
	register struct ex_softc *xs = &ex_softc[ifp->if_unit];
	register struct mbuf *m = m0;
	register struct ether_header *eh;
	register int off;
I 12
	int usetrailers;
E 12

I 8
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}
E 8
	switch (dst->sa_family) {

#ifdef INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
D 12
		if (!arpresolve(&xs->xs_ac, m, &idst, edst))
E 12
I 12
		if (!arpresolve(&xs->xs_ac, m, &idst, edst, &usetrailers))
E 12
			return (0);	/* if not yet resolved */
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
D 12
		/* need per host negotiation */
		if ((ifp->if_flags & IFF_NOTRAILERS) == 0)
		if (off > 0 && (off & 0x1ff) == 0 &&
E 12
I 12
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
E 12
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
D 2
			type = ETHERPUP_TRAIL + (off>>9);
E 2
I 2
			type = ETHERTYPE_TRAIL + (off>>9);
E 2
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
D 2
			*mtod(m, u_short *) = htons((u_short)ETHERPUP_IPTYPE);
E 2
I 2
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
E 2
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
D 2
		type = ETHERPUP_IPTYPE;
E 2
I 2
		type = ETHERTYPE_IP;
E 2
		off = 0;
		goto gottype;
#endif
I 5
#ifdef NS
	case AF_NS:
		type = ETHERTYPE_NS;
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		(caddr_t)edst, sizeof (edst));
		off = 0;
		goto gottype;
#endif
E 5

	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;

	default:
		printf("ex%d: can't handle af%d\n", ifp->if_unit,
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
	eh = mtod(m, struct ether_header *);
	eh->ether_type = htons((u_short)type);
	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
	bcopy((caddr_t)xs->xs_addr, (caddr_t)eh->ether_shost, 6);

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
	/*
	 * If transmit request not already pending, then
	 * kick the back end.
	 */
	if ((xs->xs_flags & EX_XPENDING) == 0) {
		exstart(ifp->if_unit);
	}
#ifdef DEBUG
	else {
		xs->xs_wait++;
	}
#endif
	splx(s);
	return (0);

bad:
	m_freem(m0);
	return (error);
}

/*
E 20
 * Watchdog routine - place stats request to EXOS
 * (This could be dispensed with, if you don't care
 *  about the if_ierrors count, or are willing to receive
 *  bad packets in order to derive it.)
 */
exwatch(unit)
	int unit;
{
	struct uba_device *ui = exinfo[unit];
	struct exdevice *addr = (struct exdevice *)ui->ui_addr;
	register struct ex_softc *xs = &ex_softc[unit];
	register struct ex_msg *bp;
	int s = splimp();

	if (xs->xs_flags & EX_STATPENDING) goto exspnd;
	bp = exgetcbuf(xs);
	xs->xs_flags |= EX_STATPENDING;
	bp->mb_rqst = LLNET_STSTCS;
	bp->mb_ns.ns_mask = READ_OBJ;
	bp->mb_ns.ns_rsrv = 0;
	bp->mb_ns.ns_nobj = 8;		/* read all 8 stats objects */
	bp->mb_ns.ns_xobj = 0;		/* starting with the 1st one */
D 11
	bp->mb_ns.ns_bufp = P_UNIADDR(xs->xs_ubaddr) + SA_OFFSET;
E 11
I 11
	bp->mb_ns.ns_bufp = P_UNIADDR(xs->xs_ubaddr) + SA_OFFSET(unit);
E 11
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
exspnd:
	splx(s);
	xs->xs_if.if_timer = EXWATCHINTVL;
}

/*
 * Process an ioctl request.
 */
exioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
D 2
	register struct ifreq *ifr = (struct ifreq *)data;
E 2
I 2
	register struct ifaddr *ifa = (struct ifaddr *)data;
I 8
	register struct ex_softc *xs = &ex_softc[ifp->if_unit];
E 8
E 2
	int s = splimp(), error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
D 2
		if (ifp->if_flags & IFF_RUNNING)
			if_rtinit(ifp, -1);	/* delete previous route */
		exsetaddr(ifp, (struct sockaddr_in *)&ifr->ifr_addr);
		exinit(ifp->if_unit);
E 2
I 2
                ifp->if_flags |= IFF_UP;
D 4
                ecinit(ifp->if_unit);
E 4
I 4
                exinit(ifp->if_unit);
E 4

D 20
                switch (ifa->ifa_addr.sa_family) {
E 20
I 20
                switch (ifa->ifa_addr->sa_family) {
E 20
I 5
#ifdef INET
E 5
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
I 5
#endif
#ifdef NS
		case AF_NS:
D 9
			IA_SNS(ifa)->sns_addr.x_host =
D 8
				* (union ns_host *) 
				     (ex_softc[ifp->if_unit].xs_addr);
E 8
I 8
				*(union ns_host *)(xs->xs_addr);
E 9
I 9
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
			
			if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)(xs->xs_addr);
			else
				ex_setaddr(ina->x_host.c_host,ifp->if_unit);
E 9
E 8
			break;
I 9
		    }
E 9
#endif
E 5
		}
I 8
		break;

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    xs->xs_flags & EX_RUNNING) {
			((struct exdevice *)
			  (exinfo[ifp->if_unit]->ui_addr))->xd_porta = EX_RESET;
			xs->xs_flags &= ~EX_RUNNING;
		} else if (ifp->if_flags & IFF_UP &&
		    (xs->xs_flags & EX_RUNNING) == 0)
			exinit(ifp->if_unit);
E 8
E 2
		break;

	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
I 9
}

/*
 * set ethernet address for unit
 */
ex_setaddr(physaddr, unit)
	u_char *physaddr;
	int unit;
{
	register struct ex_softc *xs = &ex_softc[unit];
D 20
	struct uba_device *ui = exinfo[unit];
	register struct exdevice *addr= (struct exdevice *)ui->ui_addr;
D 14
	register struct ifnet *ifp = &xs->xs_if;
E 14
	register struct ex_msg *bp;
E 20
	
	if (physaddr) {
		xs->xs_flags |= EX_SETADDR;
		bcopy((caddr_t)physaddr, (caddr_t)xs->xs_addr, 6);
	}
I 20
	ex_setmulti((u_char *)xs->xs_addr, unit, PHYSSLOT);
}
/*
 * enable multicast reception on a particular address.
 */
ex_setmulti(linkaddr, unit, slot)
	u_char *linkaddr;
	int unit;
{
	register struct ex_softc *xs = &ex_softc[unit];
	struct uba_device *ui = exinfo[unit];
	register struct exdevice *addr= (struct exdevice *)ui->ui_addr;
	register struct ex_msg *bp;
	
E 20
	if (! (xs->xs_flags & EX_RUNNING))
		return;
	bp = exgetcbuf(xs);
	bp->mb_rqst = LLNET_ADDRS;
	bp->mb_na.na_mask = READ_OBJ|WRITE_OBJ;
D 20
	bp->mb_na.na_slot = PHYSSLOT;
D 15
	bcopy(xs->xs_addr, bp->mb_na.na_addrs, 6);
E 15
I 15
	bcopy((caddr_t)xs->xs_addr, (caddr_t)bp->mb_na.na_addrs, 6);
E 20
I 20
	bp->mb_na.na_slot = slot;
	bcopy((caddr_t)linkaddr, (caddr_t)bp->mb_na.na_addrs, 6);
E 20
E 15
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
	bp = xs->xs_x2hnext;
	while ((bp->mb_status & MH_OWNER) == MH_EXOS)	/* poll for reply */
		;
D 12
	printf("ex%d: reset addr %x.%x.%x.%x.%x.%x\n",
		ui->ui_unit,
		bp->mb_na.na_addrs[0], bp->mb_na.na_addrs[1],
		bp->mb_na.na_addrs[2], bp->mb_na.na_addrs[3],
		bp->mb_na.na_addrs[4], bp->mb_na.na_addrs[5]);
E 12
I 12
#ifdef	DEBUG
D 17
	printf("ex%d: reset addr %s\n", ui->ui_unit,
E 17
I 17
D 20
	log(LOG_DEBUG, "ex%d: reset addr %s\n", ui->ui_unit,
E 17
		ether_sprintf(bp->mb_na.na_addrs));
E 20
I 20
	log(LOG_DEBUG, "ex%d: %s %s (slot %d)\n", unit,
		(slot == PHYSSLOT ? "reset addr" : "add multicast"
		ether_sprintf(bp->mb_na.na_addrs), slot);
E 20
#endif
E 12
	/*
D 20
	 * Now, re-enable reception on phys slot.
E 20
I 20
	 * Now, re-enable reception on slot.
E 20
	 */
	bp = exgetcbuf(xs);
	bp->mb_rqst = LLNET_RECV;
	bp->mb_nr.nr_mask = ENABLE_RCV|READ_OBJ|WRITE_OBJ;
D 20
	bp->mb_nr.nr_slot = PHYSSLOT;
E 20
I 20
	bp->mb_nr.nr_slot = slot;
E 20
	bp->mb_status |= MH_EXOS;
	addr->xd_portb = EX_NTRUPT;
	bp = xs->xs_x2hnext;
	while ((bp->mb_status & MH_OWNER) == MH_EXOS)	/* poll for reply */
		;
E 9
D 2
}

exsetaddr(ifp, sin)
	register struct ifnet *ifp;
	register struct sockaddr_in *sin;
{
	ifp->if_addr = *(struct sockaddr *)sin;
	ifp->if_net = in_netof(sin->sin_addr);
	ifp->if_host[0] = in_lnaof(sin->sin_addr);
	sin = (struct sockaddr_in *)&ifp->if_broadaddr;
	sin->sin_family = AF_INET;
	sin->sin_addr = if_makeaddr(ifp->if_net, INADDR_ANY);
	ifp->if_flags |= IFF_BROADCAST;
E 2
}
I 7
#endif
E 7
E 1
