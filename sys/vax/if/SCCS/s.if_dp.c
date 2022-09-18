h19559
s 00002/00071/00615
d D 7.10 92/05/04 18:08:22 sklower 12 11
c use new m_devget facility
e
s 00007/00015/00679
d D 7.9 91/06/27 14:42:14 sklower 11 10
c add IP, CLNP over X.25 support
e
s 00005/00001/00689
d D 7.8 91/05/02 18:59:17 sklower 10 9
c set if_type, change to no default logging printfs, set addrlen &  hdrlen
e
s 00024/00024/00666
d D 7.7 90/12/16 16:51:13 bostic 9 8
c kernel reorg
e
s 00080/00064/00610
d D 7.6 90/10/02 20:36:27 sklower 8 5
c This version appears to work with accunet; DP_XE must be asserted
c in order to get continuous flag characters; pseudo-dma code must clear DP_XSM;
c also netisr is a global variable and using a local in dpinput hid the def.
e
s 00000/00000/00674
d R 7.6 90/10/02 20:32:35 sklower 7 5
c This version appears to work with accunet; DP_XE must be asserted
c in order to get continuous flag characters; pseudo-dma code must clear DP_XSM.
e
s 00080/00064/00610
d R 7.6 90/10/02 12:41:08 sklower 6 5
c 
e
s 00042/00027/00632
d D 7.5 90/09/17 11:53:50 sklower 5 4
c This version receives packets from accunet, but won't
e
s 00020/00017/00639
d D 7.4 90/09/14 15:47:04 sklower 4 3
c this one should handle up down transitions more gracefully.
e
s 00220/00098/00436
d D 7.3 90/09/12 17:47:09 sklower 3 2
c This version interrupts on transmits and modem state changes;
c we have yet to see a genuine input interrupt.  Maybe a hardware problem.
e
s 00030/00023/00504
d D 7.2 90/08/30 18:49:41 sklower 2 1
c This version compiles; otherwise untested.
e
s 00527/00000/00000
d D 7.1 90/08/30 17:35:31 sklower 1 0
c date and time created 90/08/30 17:35:31 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include "dp.h"
#if NDP > 0

/*
 * DPV-11 device driver, X.25 version
 *
 * Derived from dmc-11 driver:
 *
 *	Bill Nesheim
 *	Cornell University
 *
 *	Lou Salkind
 *	New York University
 */

/* #define DEBUG	/* for base table dump on fatal error */

D 9
#include "machine/pte.h"
E 9
I 9
#include "../include/pte.h"
E 9

D 9
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "ioctl.h"		/* must precede tty.h */
#include "protosw.h"
#include "socket.h"
I 3
#include "socketvar.h"
E 3
#include "syslog.h"
#include "vmmac.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 9
I 9
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/ioctl.h"		/* must precede tty.h */
#include "sys/protosw.h"
#include "sys/socket.h"
#include "sys/socketvar.h"
#include "sys/syslog.h"
#include "sys/vmmac.h"
#include "sys/errno.h"
#include "sys/time.h"
#include "sys/kernel.h"
E 9

D 9
#include "../net/if.h"
#include "../net/netisr.h"
#include "../net/route.h"
E 9
I 9
#include "net/if.h"
I 10
#include "net/if_types.h"
E 10
#include "net/netisr.h"
#include "net/route.h"
E 9

D 9
#include "../vax/cpu.h"
#include "../vax/mtpr.h"
E 9
I 9
#include "../include/cpu.h"
#include "../include/mtpr.h"
E 9
I 2

I 3
#define	dzdevice dpdevice
E 3
E 2
D 9
#include "../vaxuba/pdma.h"
I 2
#include "../vaxuba/ubavar.h"
E 9
I 9
#include "../uba/pdma.h"
#include "../uba/ubavar.h"
E 9
E 2

I 2
D 3
#include "../netcitt/x25.h"
E 3
I 3
D 9
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 9
I 9
#include "netccitt/x25.h"
#include "netccitt/pk.h"
#include "netccitt/pk_var.h"
E 9
E 3

E 2
#include "if_dpreg.h"

/*
 * Driver information for auto-configuration stuff.
 */
int	dpprobe(), dpattach(), dpinit(), dpioctl(), dprint(), dpxint();
D 2
int	dpoutput(), dpreset(), dptimeout(), x25_ifoutput();
E 2
I 2
D 3
int	dpoutput(), dpreset(), dptimeout(), dpstart(), x25_ifoutput();
E 3
I 3
D 11
int	dpoutput(), dpreset(), dptimeout(), dpstart(), x25_ifoutput(), dptestoutput();
E 11
I 11
int	dpoutput(), dpreset(), dptimeout(), dpstart(), dptestoutput();
int	x25_ifoutput(), x25_rtrequest();
E 11
E 3
E 2

struct	uba_device *dpinfo[NDP];

u_short	dpstd[] = { 0 };
struct	uba_driver dpdriver =
	{ dpprobe, 0, dpattach, 0, dpstd, "dp", dpinfo };

/*
I 3
D 8
 * debug info
 */
struct	dpstat {
	long	start;
	long	nohdr;
	long	init;
	long	rint;
	long	xint;
	long	reset;
	long	ioctl;
	long	down;
	long	mchange;
	long	timeout;
I 5
	long	rsm;
	long	rem;
	long	rsmchr;
	long	rga;
E 5
} dpstat;
/*
E 8
E 3
 * Pdma structures for fast interrupts.
 */
struct	pdma dppdma[2*NDP];

D 8
/* error reporting intervals */
#define DPI_RPNBFS	50
#define DPI_RPDSC	1
#define DPI_RPTMO	10
#define DPI_RPDCK	10


E 8
/*
 * DP software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * dp_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
struct dp_softc {
	struct	ifnet dp_if;		/* network-visible interface */
I 3
	int	dp_ipl;
I 4
	struct	dpdevice *dp_addr;	/* dpcsr address */
E 4
E 3
	short	dp_iused;		/* input buffers given to DP */
	short	dp_flags;		/* flags */
I 3
#define DPF_RUNNING	0x01		/* device initialized */
#define DPF_ONLINE	0x02		/* device running (had a RDYO) */
#define DPF_RESTART	0x04		/* software restart in progress */
#define DPF_FLUSH	0x08		/* had a ROVR, flush ipkt when done */
I 11
#define DPF_X25UP	0x10		/* XXX -- someday we'll do PPP also */
E 11
E 3
	short	dp_ostate;		/* restarting, etc. */
	short	dp_istate;		/* not sure this is necessary */
#define DPS_IDLE	0
#define DPS_RESTART	1
#define DPS_ACTIVE	2
#define DPS_XEM		3		/* transmitting CRC, etc. */
D 3
/* flags */
#define DPF_RUNNING	0x01		/* device initialized */
#define DPF_ONLINE	0x02		/* device running (had a RDYO) */
#define DPF_RESTART	0x04		/* software restart in progress */
#define DPF_FLUSH	0x08		/* had a ROVR, flush ipkt when done */
E 3
D 8
	int	dp_errors[4];		/* non-fatal error counters */
#define dp_datck dp_errors[0]
#define dp_timeo dp_errors[1]
#define dp_nobuf dp_errors[2]
#define dp_disc  dp_errors[3]
E 8
I 8
	short	dp_olen;		/* length of last packet sent */
	short	dp_ilen;		/* length of last packet recvd */
E 8
I 3
D 5
	struct timeval	dp_xt;			/* start of last transmission */
E 5
E 3
	char	dp_obuf[DP_MTU+8];
D 2
	char	dp_rbuf[DP_MTU+8];
E 2
I 2
	char	dp_ibuf[DP_MTU+8];
E 2
} dp_softc[NDP];

I 8
/*
 * Debug info
 */
struct	dpstat {
	long	start;
	long	nohdr;
	long	init;
	long	rint;
	long	xint;
	long	reset;
	long	ioctl;
	long	down;
	long	mchange;
	long	timeout;
	long	rsm;
	long	rem;
	long	remchr;
	long	rga;
	long	xem;
	long	rovr;
} dpstat;

short dp_ilb = 0;
D 10
short dp_log = 1;
E 10
I 10
short dp_log = 0;
E 10

#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
int dp_sizes[] = {
	sizeof(dp_softc[0]), sizeof(struct ifnet),
	_offsetof(struct dp_softc, dp_obuf[0]),
	_offsetof(struct dp_softc, dp_ibuf[0]),
	};

E 8
dpprobe(reg, ui)
	caddr_t reg;
	struct	uba_device *ui;
{
	register int br, cvec;
	register struct dpdevice *addr = (struct dpdevice *)reg;
D 4
	register int i;
E 4
I 4
	register int unit = ui->ui_unit;
E 4

#ifdef lint
	br = 0; cvec = br; br = cvec;
	dprint(0); dpxint(0);
#endif
I 3
	(void) spl6();
E 3
	addr->dpclr = DP_CLR;
	addr->dpclr = DP_XIE|DP_XE;
	DELAY(100000);
I 3
D 4
	dp_softc[ui->ui_unit].dp_ipl = br = qbgetpri();
E 4
I 4
	dp_softc[unit].dp_ipl = br = qbgetpri();
	dp_softc[unit].dp_addr = addr;
E 4
E 3
	addr->dpclr = 0;
I 3
	if (cvec && cvec != 0x200){
		cvec -= 4;
	}
E 3
	return (1);
}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
dpattach(ui)
	register struct uba_device *ui;
{
	register struct dp_softc *dp = &dp_softc[ui->ui_unit];
D 3
	register struct pdma *pdp = &dppdma[ui->ui_unit*2];
E 3

	dp->dp_if.if_unit = ui->ui_unit;
	dp->dp_if.if_name = "dp";
	dp->dp_if.if_mtu = DP_MTU;
	dp->dp_if.if_init = dpinit;
	dp->dp_if.if_output = x25_ifoutput;
I 10
	dp->dp_if.if_type = IFT_X25;
	dp->dp_if.if_hdrlen = 5;
	dp->dp_if.if_addrlen = 8;
E 10
	dp->dp_if.if_start = dpstart;
	dp->dp_if.if_ioctl = dpioctl;
	dp->dp_if.if_reset = dpreset;
	dp->dp_if.if_watchdog = dptimeout;
D 3
	dp->dp_if.if_flags = IFF_POINTOPOINT;


	pdp->p_addr = (struct dzdevice *)ui->ui_addr;
	pdp->p_arg = (int)dp;
	pdp->p_fcn = dpxint;
	pdp->p_mem = pdp->p_end = dp->dp_obuf;
	pdp++;
	pdp->p_addr = (struct dzdevice *)ui->ui_addr;
	pdp->p_arg = (int)dp;
	pdp->p_fcn = dprint;
D 2
	pdp->p_mem = pdp->p_end = dp->dp_rbuf;
E 2
I 2
	pdp->p_mem = pdp->p_end = dp->dp_ibuf;
E 2

E 3
I 3
	dp->dp_if.if_flags = 0;
E 3
	if_attach(&dp->dp_if);
}

/*
 * Reset of interface after UNIBUS reset.
 * If interface is on specified UBA, reset its state.
 */
dpreset(unit, uban)
	int unit, uban;
{
	register struct uba_device *ui;
	register struct dp_softc *dp = &dp_softc[unit];
	register struct dpdevice *addr;

I 3
	dpstat.reset++;
E 3
	if (unit >= NDP || (ui = dpinfo[unit]) == 0 || ui->ui_alive == 0 ||
	    ui->ui_ubanum != uban)
		return;
D 4
	printf(" dp%d", unit);
D 2
	dp->dp_flag = 0;
E 2
I 2
	dp->dp_flags = 0;
E 2
	dp->dp_if.if_flags &= ~IFF_RUNNING;
D 2
	addr = ui->ui_addr;
E 2
I 2
	addr = (struct dpdevice *)ui->ui_addr;
E 2
	addr->dpclr = DP_CLR;
I 3
	DELAY(1000);
E 3
	addr->dpsar = 0;
	addr->dprcsr = 0;
E 4
I 4
	dpdown(unit);
E 4
	dpinit(unit);
I 4
	printf(" dp%d", unit);
E 4
}

/*
 * Initialization of interface.
 */
dpinit(unit)
	int unit;
{
	register struct dp_softc *dp = &dp_softc[unit];
D 4
	register struct uba_device *ui = dpinfo[unit];
E 4
	register struct dpdevice *addr;
D 3
	register struct ifnet *ifp = &dp->dp_if;
	struct ifaddr *ifa;
	int base;
	int s;
E 3
I 3
	register struct ifaddr *ifa;
	register struct pdma *pdp = &dppdma[unit*2];
	int base, s;
E 3

D 3
	addr = (struct dpdevice *)ui->ui_addr;

E 3
I 3
	dpstat.init++;
E 3
	/*
	 * Check to see that an address has been set.
	 */
D 3
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
E 3
I 3
	for (ifa = dp->dp_if.if_addrlist; ifa; ifa = ifa->ifa_next)
E 3
		if (ifa->ifa_addr->sa_family != AF_LINK)
			break;
	if (ifa == (struct ifaddr *) 0)
		return;

D 3
	s = spl5();
E 3
I 3
D 4
	addr = (struct dpdevice *)ui->ui_addr;
E 4
I 4
	addr = dp->dp_addr;
E 4
	s = splimp();
E 3
	dp->dp_iused = 0;
	dp->dp_istate = dp->dp_ostate = DPS_IDLE;
D 3
	dppdma[2*unit+1].p_end = 
D 2
		dppdma[2*unit+1].p_mem = = dp->dp_rbuf;
E 2
I 2
		dppdma[2*unit+1].p_mem = dp->dp_ibuf;
E 2
	/* enable receive interrupt; CTS comming up will trigger it also */
	addr->dpsar = DP_CHRM | 0x7E; /* 7E is the flag character */
E 3
I 3
	dp->dp_if.if_flags |= IFF_RUNNING;
	dp->dp_if.if_flags &= ~IFF_OACTIVE;

	pdp->p_addr = addr;
	pdp->p_fcn = dpxint;
	pdp->p_mem = pdp->p_end = dp->dp_obuf;
	pdp++;
	pdp->p_addr = addr;
	pdp->p_fcn = dprint;
	/* force initial interrupt to come to dprint */
	pdp->p_mem = pdp->p_end = dp->dp_ibuf + DP_MTU + 8;

	addr->dpclr = DP_CLR;
D 8
	DELAY(1000);
E 8
I 8
	DELAY(5000);
E 8
E 3
D 5
	addr->dpclr = 0;
D 3
	addr->dprcsr = DP_RIE | DP_DTR | DP_RE;
E 3
I 3
	DELAY(1000);
	/* DP_ATA = 0, DP_CHRM = 0,
E 5
I 5
	/* DP_ATA = 0, DP_CHRM = 0, DP_SSLM = 1, (enable aborts),
E 5
			    CRC = CCIIT, initially all ones, 2nd addr = 0 */
D 5
	addr->dpsar = 0;
	/* enable receive interrupt */
E 5
I 5
	addr->dpsar = DP_SSLM | DP_IDLE;
D 8
	addr->dpclr = 0;
E 8
I 8
	addr->dpclr = DP_XE | dp_ilb;
	addr->dptdsr = DP_XSM;
E 8
	/* enable receiver, receive interrupt, DTR, RTS */
E 5
	addr->dprcsr = DP_RIE | DP_MIE | DP_RE | DP_DTR | DP_RTS;
	dpstart(&dp->dp_if);
E 3
	splx(s);
}

I 3
D 5
int dpMessy = 0;
E 5
E 3
/*
 * Start output on interface.  Get another datagram
 * to send from the interface queue and map it to
 * the interface before starting output.
 *
 */
dpstart(ifp)
	struct ifnet *ifp;
{
D 3
	int s, unit = ifp->if_unit;
E 3
I 3
	int s, unit = ifp->if_unit, error = 0, len;
E 3
	register struct dp_softc *dp = &dp_softc[unit];
D 2
	register struct dpdevice *addr = dpinfo[unit].ui_addr;
E 2
I 2
D 4
	register struct dpdevice *addr =
				(struct dpdevice *)(dpinfo[unit]->ui_addr);
E 4
I 4
D 5
	register struct dpdevice *addr = dp_addr;
E 5
I 5
	register struct dpdevice *addr = dp->dp_addr;
E 5
E 4
E 2
	register struct mbuf *m;
	register char *cp;
	char *cplim;

	/*
	 * If already doing output, go away and depend on transmit
	 * complete or error.
	 */
D 3
	s = splimp();
	if (dp->dp_if.if_flags & IFF_OACTIVE) {
		splx(s);
		return (0);
	}
E 3
I 3
	dpstat.start++;
D 4
	if (dp->dp_if.if_flags & IFF_OACTIVE)
E 4
I 4
	if ((dp->dp_if.if_flags & IFF_OACTIVE) ||
D 8
	    ! (dp->dp_if.if_flags & IFF_RUNNING))
E 8
I 8
	    (dp->dp_if.if_flags & IFF_RUNNING) == 0)
E 8
E 4
		goto out;
E 3
	IF_DEQUEUE(&dp->dp_if.if_snd, m);
	if (m == 0)
D 3
		return (0);
	if ((m->m_flags | M_PKTHDR) == 0 || m->m_pkthdr.len > DP_MTU)
		return (EINVAL);
	s = spl5();
	dppdma[2*unit].p_mem = cp = dp->dp_obuf;
E 3
I 3
		goto out;
	dp->dp_if.if_collisions++;
	if (m->m_flags & M_PKTHDR)
		len = m->m_pkthdr.len;
	else {
		struct mbuf *m0 = m;
		for (len = 0; m; m = m->m_next)
			len += m->m_len;
		m = m0;
		dpstat.nohdr++;
	}
D 8
	if (len == 0)
E 8
I 8
	if (len < 2)
E 8
		goto out;
	if (len > DP_MTU) {
		error = EINVAL;
		goto out;
	}
D 5
	cp = dp->dp_obuf;
	dppdma[2*unit].p_mem = cp + 1;
E 5
I 5
D 8
	dppdma[2*unit].p_mem = 1 + (cp = dp->dp_obuf);
E 8
I 8
	dppdma[2*unit].p_mem = cp = dp->dp_obuf;
E 8
E 5
E 3
	while (m) {
		struct mbuf *n;
		bcopy(mtod(m, caddr_t), (caddr_t)cp, m->m_len);
		cp += m->m_len;
		MFREE(m, n); m = n;
	}
D 3
	if (cp == dp->dp_obuf)
		return (0);
E 3
D 8
	dppdma[2*unit].p_end = cp;
E 8
I 8
	dppdma[2*unit].p_end = cp - 1;
E 8
D 3
	addr->dpclr = DP_XE | DP_XIE;
	addr->dptdsr = DP_XSM;
E 3
I 3
D 5
	if (dpMessy)
		printf("dp: len %d, start %x, end %x, first %x, next %x",
			len, dp->dp_obuf, cp, *(int *)dp->dp_obuf,
			1[(int *)dp->dp_obuf]);
E 5
E 3
	dp->dp_if.if_flags |= IFF_OACTIVE;
	dp->dp_ostate = DPS_ACTIVE;
D 3
	splx(s);
	return (0);
E 3
I 3
	dp->dp_if.if_collisions--;
I 8
	dp->dp_olen = len;
	if (dp_log) {
		register u_char *p = (u_char *)dp->dp_obuf;
		log(LOG_DEBUG, "dpoutput(%d):%x %x %x %x %x\n",
			len, p[0], p[1], p[2], p[3], p[4]);
	}
E 8
D 5
dp->dp_xt = time;
	addr->dpclr = DP_XE | DP_XIE;
	addr->dptdsr = DP_XSM | (0xff & dp->dp_obuf[0]);
E 5
I 5
	addr->dpsar = DP_SSLM | DP_IDLE;
	addr->dprcsr = DP_RIE | DP_MIE | DP_RE | DP_DTR | DP_RTS;
D 8
	addr->dpclr = DP_XIE | DP_XE;
	addr->dptdsr = DP_XSM | (0xff & *cp);
E 8
I 8
	addr->dpclr = DP_XIE | DP_XE | dp_ilb;
	addr->dptdsr = DP_XSM;
E 8
E 5
out:
	return (error);
E 3
}
I 5
D 8
long dp_rdsr;
E 8
E 5
/*
 * Receive done or error interrupt
 */
dprint(unit, pdma, addr)
register struct pdma *pdma;
register struct dpdevice *addr;
{
D 2
	register struct dpsoftc *dp = &dpsoftc[unit];
	unsigned short dprdsr = addr->dprdsr;
E 2
I 2
	register struct dp_softc *dp = &dp_softc[unit];
D 3
	short rdsr = addr->dprdsr;
E 3
I 3
D 5
	short rdsr = addr->dprdsr, rcsr;
E 5
I 5
	short rdsr = addr->dprdsr, rcsr = pdma->p_arg;
E 5
E 3
E 2

D 2
	if (dprdsr & DP_ROVR) {
E 2
I 2
D 3
	if (rdsr & DP_ROVR) {
E 2
		dp->dp_flags |= DPF_FLUSH;
		return;
	}
E 3
I 3
	dpstat.rint++;
I 5
D 8
dp_rdsr = rdsr;
E 8
E 5
	splx(dp->dp_ipl);
I 5
	if (rdsr & DP_RGA) {
		/* DP_ATA = 0, DP_CHRM = 0, DP_SSLM = 1, (enable aborts),
			    CRC = CCIIT, initially all ones, 2nd addr = 0 */
		addr->dpsar = DP_SSLM | DP_IDLE;
		addr->dprcsr = DP_RIE | DP_MIE | DP_RE | DP_DTR | DP_RTS;
		dpstat.rga++;
		return;
	}
E 5
E 3
D 2
	if (dprdsr & DP_RSM) { /* Received Start of Message */
		dp->dp_ibuf[0] = dprdsr & DP_RBUF;
E 2
I 2
	if (rdsr & DP_RSM) { /* Received Start of Message */
D 5
		dp->dp_ibuf[0] = rdsr & DP_RBUF;
E 2
		pdma->p_mem = dp->dp_ibuf + 1;
E 5
I 5
		dpstat.rsm++;
		pdma->p_mem = dp->dp_ibuf;
		if (rcsr & DP_RDR) {
		    dp->dp_ibuf[0] = rdsr & DP_RBUF;
		    pdma->p_mem++;
D 8
		    dpstat.rsmchr++;
E 8
		}
E 5
D 2
		dpflags &= ~DPF_FLUSH;
E 2
I 2
		dp->dp_flags &= ~DPF_FLUSH;
E 2
		return;
	}
D 2
	if (dprdsr & DP_REM) { /* Received End of Message */
		if (dprdsr & DP_REC || dp->dp_flags & DPF_FLUSH) {
			dp->dp_if.if_errors++;
E 2
I 2
	if (rdsr & DP_REM) { /* Received End of Message */
I 5
		dpstat.rem++;
I 8
		if (rcsr & DP_RDR) {
		    *(pdma->p_mem++) = rdsr;
		    dpstat.remchr++;
		}
		dp->dp_ilen = pdma->p_mem - dp->dp_ibuf;
E 8
E 5
		if (rdsr & DP_REC || dp->dp_flags & DPF_FLUSH) {
			dp->dp_if.if_ierrors++;
E 2
D 3
			pdma->p_mem = dp->dp_ibuf;
			dp->dp_flags &= ~ DPF_FLUSH;
			return;
E 3
I 3
		} else
D 8
			dpinput(&dp->dp_if,
				pdma->p_mem - dp->dp_ibuf, dp->dp_ibuf);
E 8
I 8
			dpinput(&dp->dp_if, dp->dp_ilen, dp->dp_ibuf);
E 8
		pdma->p_mem = pdma->p_end;
		dp->dp_flags &= ~ DPF_FLUSH;
		return;
	}
	if (rdsr & DP_ROVR) {
I 8
		dpstat.rovr++;
E 8
		dp->dp_flags |= DPF_FLUSH;
		return;
	}
D 5
	rcsr = pdma->p_arg;
E 5
	if (rcsr & DP_MSC) {
		dpstat.mchange++;
		if (0 == (rcsr & DP_DSR)) {
			log(LOG_DEBUG, "dp%d: lost modem\n", unit);
D 5
			dpdown(unit);
E 5
I 5
			/*dpdown(unit);*/
E 5
E 3
		}
D 3
		dpinput(dp, pdma->p_mem - dp->dp_ibuf, dp->dp_ibuf);
E 3
		return;
	}
	dp->dp_flags |= DPF_FLUSH;
	if (pdma->p_mem != pdma->p_end)
D 2
		log(dp%d: unexplained receiver interrupt\n");
E 2
I 2
D 8
		log("dp%d: unexplained receiver interrupt\n", unit);
E 8
I 8
		log(LOG_DEBUG, "dp%d: unexplained receiver interrupt\n", unit);
E 8
E 2
}
I 3
D 5
struct timeval dp_xt;
E 5
I 5
D 8
int dp_fill;
E 5
E 3

E 8
/*
 * Transmit complete or error interrupt
 */
dpxint(unit, pdma, addr)
register struct pdma *pdma;
register struct dpdevice *addr;
{
D 2
	register struct dpsoftc *dp = &dpsoftc[unit];
E 2
I 2
	register struct dp_softc *dp = &dp_softc[unit];
I 3
	int s;
E 3
E 2

I 3
	splx(dp->dp_ipl);
	dpstat.xint++;
E 3
	if (addr->dptdsr & DP_XERR) {
D 8
		log("if_dp%d: data late\n", unit);
E 8
I 8
		log(LOG_DEBUG, "if_dp%d: data late\n", unit);
E 8
	restart:
		pdma->p_mem = dp->dp_obuf;
		addr->dptdsr = DP_XSM;
I 3
		dp->dp_if.if_oerrors++;
E 3
		return;
	}
	switch (dp->dp_ostate) {

	case DPS_ACTIVE:
		if (pdma->p_mem != pdma->p_end) {
D 3
			log("if_dp%d: misc error in dpxint\n");
E 3
I 3
D 8
			log("if_dp%d: misc error in dpxint\n", unit);
E 8
I 8
			log(LOG_DEBUG, "if_dp%d: misc error in dpxint\n", unit);
E 8
E 3
			goto restart;
		}
I 5
D 8
		addr->dpclr = DP_XIE; /* &= ~DP_XE */
E 5
		addr->dptdsr = DP_XEM;
E 8
I 8
		addr->dpsar = DP_IDLE|DP_SSLM;
		addr->dpclr = DP_XE | DP_XIE | dp_ilb;
		addr->dptdsr = DP_XEM | (0xff & pdma->p_mem[0]);
		addr->dprcsr = DP_RIE | DP_MIE | DP_RE | DP_DTR | DP_RTS;
E 8
		dp->dp_ostate = DPS_XEM;
		break;

	case DPS_XEM:
I 8
		dpstat.xem++;
E 8
I 3
		dp->dp_if.if_opackets++;
I 8
		dp->dp_ostate = DPS_IDLE;
E 8
E 3
		dp->dp_if.if_flags &= ~IFF_OACTIVE;
I 3
D 5
s = splclock();
dp_xt = time;
timevalsub(&dp_xt, &dp->dp_xt);
splx(s);
E 5
E 3
		if (dp->dp_if.if_snd.ifq_len)
			dpstart(&dp->dp_if);
		else {
I 5
D 8
			if (dp_fill) {
				addr->dpsar = DP_IDLE|DP_SSLM;
				addr->dptdsr = DP_XABO;
			} else {
				addr->dptdsr = 0;
			}
E 5
			addr->dpclr = 0;
			dp->dp_ostate = DPS_IDLE;
E 8
I 8
			addr->dpsar = DP_IDLE|DP_SSLM;
			addr->dpclr = DP_XE | dp_ilb;
			addr->dptdsr = DP_XSM;
			addr->dprcsr = DP_RIE | DP_MIE | DP_RE | DP_DTR|DP_RTS;
E 8
		}
		break;

	default:
D 8
		log("if_dp%d: impossible state in dpxint\n");
E 8
I 8
		log(LOG_DEBUG, "if_dp%d: impossible state in dpxint\n");
E 8
	}
}
D 12
/*
 * Routine to copy from device buffer into mbufs.
 *
 * Warning: This makes the fairly safe assumption that
 * mbufs have even lengths.
 */
struct mbuf *
dpget(rxbuf, totlen, off, ifp)
	caddr_t rxbuf;
	int totlen, off;
	struct ifnet *ifp;
{
	register caddr_t cp;
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	int len;
	caddr_t packet_end;
E 12

D 12
	cp = rxbuf;
	packet_end = cp + totlen;
	if (off) {
		off += 2 * sizeof(u_short);
		totlen -= 2 *sizeof(u_short);
		cp = rxbuf + off;
	}

	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return (0);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

	while (totlen > 0) {
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return (0);
			}
			m->m_len = MLEN;
		}
		len = min(totlen, (packet_end - cp));
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT)
				m->m_len = len = min(len, MCLBYTES);
			else
				len = m->m_len;
		} else {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (len < m->m_len) {
				if (top == 0 && len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else
				len = m->m_len;
		}
		bcopy(cp, mtod(m, caddr_t), (u_int)len);
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		cp += len;
		if (cp == packet_end)
			cp = rxbuf;
	}
	return (top);
}

E 12
D 3
dpinput(dp, len, buffer)
D 2
register struct dpsoftc *dp;
E 2
I 2
register struct dp_softc *dp;
E 3
I 3
dpinput(ifp, len, buffer)
register struct ifnet *ifp;
E 3
E 2
caddr_t buffer;
{
D 3
	register struct ifnet *ifp = &dp->dp_if;
E 3
	register struct ifqueue *inq;
	register struct mbuf *m;
D 3
	extern struct ifqueue hdintrq;
E 3
I 3
	extern struct ifqueue hdintrq, ipintrq;
D 8
	int netisr;
E 8
I 8
	int isr;
I 12
	extern struct mbuf *m_devget();
E 12
E 8
E 3

D 3
	if(len <= 0 || ifp->if_addrlist == 0)
E 3
I 3
	ifp->if_ipackets++;
I 8
	if (dp_log) {
		register u_char *p = (u_char *)buffer;
		log(LOG_DEBUG, "dpinput(%d):%x %x %x %x %x\n",
			len, p[0], p[1], p[2], p[3], p[4]);
	}
	
E 8
    {
	register struct ifaddr *ifa = ifp->if_addrlist;
	register u_char *cp = (u_char *)buffer;

	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
		if (ifa->ifa_addr->sa_family != AF_LINK)
			break;
	if (cp[0] == 0xff && cp[1] == 0x3) {
		/* This is a UI HDLC Packet, so we'll assume PPP
		   protocol.  for now, IP only. */
		buffer += 4;
		len -= 4;
		inq = &ipintrq;
D 8
		netisr = NETISR_IP;
E 8
I 8
		isr = NETISR_IP;
E 8
	} else {
		inq = &hdintrq;
D 8
		netisr = NETISR_CCITT;
E 8
I 8
		isr = NETISR_CCITT;
E 8
	}
    }
	if (len <= 0)
E 3
		return;

D 12
	m = dpget(buffer, len , 0, ifp);
E 12
I 12
	m = m_devget(buffer, len , 0, ifp, 0);
E 12
	if (m == 0)
		return;
D 3
	ifp->if_ipackets++;
	
	/* Only AF_CCITT makes sense at this point */
	inq = &hdintrq;
E 3

	if(IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else {
		IF_ENQUEUE(inq, m);
D 2
		schednetisr(NETISR_HD);
E 2
I 2
D 3
		schednetisr(NETISR_CCITT);
E 3
I 3
D 8
		schednetisr(netisr);
E 8
I 8
		schednetisr(isr);
E 8
E 3
E 2
	}
}

/*
 * Process an ioctl request.
 */
dpioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	int s = splimp(), error = 0;
I 2
	struct dp_softc *dp = &dp_softc[ifp->if_unit];
E 2

I 3
	dpstat.ioctl++;
E 3
	switch (cmd) {
D 11

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		switch (ifa->ifa_addr->sa_family) {
D 3
#ifdef CCITT
		case AF_CCITT:
D 2
			error = hd_ctlinput (PRC_IFUP, (caddr_t)&ifa->ifa_addr);
E 2
I 2
			error = hd_ctlinput(PRC_IFUP, (caddr_t)&ifa->ifa_addr);
E 2
			if (error == 0)
				dpinit(ifp->if_unit);
			break;
#endif
		case SIOCSIFFLAGS:
			if ((ifp->if_flags & IFF_UP) == 0 &&
			    (dp->dp_flags & DPF_RUNNING))
				dpdown(ifp->if_unit);
			else if (ifp->if_flags & IFF_UP &&
			    (dp->dp_flags & DPF_RUNNING) == 0)
				dpinit(ifp->if_unit);
			break;

E 3
I 3
		case AF_INET:
			ifp->if_output = dptestoutput;
E 3
		default:
			dpinit(ifp->if_unit);
			break;
		}
		break;
I 3
#ifdef CCITT
E 11
	case SIOCSIFCONF_X25:
		ifp->if_flags |= IFF_UP;
D 11
		ifp->if_output = x25_ifoutput;
E 11
		error = hd_ctlinput(PRC_IFUP, ifa->ifa_addr);
		if (error == 0)
			dpinit(ifp->if_unit);
		break;
D 11
#endif
E 11
I 11

	case SIOCSIFADDR:
		ifa->ifa_rtrequest = x25_rtrequest;
		break;
E 11
E 3

D 3
	/* case SIOCSIFFLAGS: ... */
E 3
I 3
	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    (ifp->if_flags & IFF_RUNNING))
			dpdown(ifp->if_unit);
		else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0)
			dpinit(ifp->if_unit);
		break;
E 3

I 3

E 3
	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}
/*
 * Reset a device and mark down.
 * Flush output queue and drop queue limit.
 */
dpdown(unit)
D 4
	int unit;
E 4
I 4
int unit;
E 4
{
I 4

E 4
	register struct dp_softc *dp = &dp_softc[unit];
I 4
	register struct dpdevice *addr = dp->dp_addr;
E 4
D 3
	register struct ifxmt *ifxp;
I 2
	register struct dpdevice *addr = (struct dpdevice *)dpinfo[unit]->ui_addr;
E 3
E 2

D 2
	dp->dp_flags &= ~(DP_RUNNING | DP_ONLINE);
E 2
I 2
D 3
	dp->dp_flags &= ~(DPF_RUNNING | DPF_ONLINE);
E 2
	addr->dpclr = DP_CLR;
	addr->dpclr = 0;

E 3
I 3
	dpstat.down++;
E 3
	if_qflush(&dp->dp_if.if_snd);
I 3
D 4
	dpreset(unit);
E 4
I 4
	dp->dp_flags = 0;
	dp->dp_if.if_flags &= ~(IFF_RUNNING | IFF_OACTIVE);

	addr->dpclr = DP_CLR;
	DELAY(1000);
	addr->dpsar = 0;
	addr->dprcsr = 0;
E 4
E 3
}

/*
 * Watchdog timeout to see that transmitted packets don't
 * lose interrupts.  The device has to be online (the first
 * transmission may block until the other side comes up).
 */
dptimeout(unit)
	int unit;
{
	register struct dp_softc *dp;
D 3
	struct dpdevice *addr;
E 3

I 3
	/* currently not armed */
	dpstat.timeout++;
E 3
	dp = &dp_softc[unit];
D 2
	if (dp->dp_flags & DP_ONLINE) {
E 2
I 2
D 3
	if (dp->dp_flags & DPF_ONLINE) {
E 2
		addr = (struct dpdevice *)(dpinfo[unit]->ui_addr);
		dpstart(unit);
E 3
I 3
	if (dp->dp_if.if_flags & IFF_OACTIVE) {
		dpstart(&dp->dp_if);
E 3
	}
}
I 3
/*
 * For debugging loopback activity.
 */
static char pppheader[4] = { -1, 3, 0, 0x21 };
int dp_louts;

dptestoutput(ifp, m, dst, rt)
register struct ifnet *ifp;
register struct mbuf *m;
struct sockaddr *dst;
struct rtentry *rt;
{
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	int s = splimp(), error = 0;
	dp_louts++;
	M_PREPEND(m, sizeof pppheader, M_DONTWAIT);
	if (m == 0) {
		splx(s);
		return ENOBUFS;
	}
	bcopy(pppheader, mtod(m, caddr_t), sizeof pppheader);
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
	    /* printf("%s%d: HDLC says OK to send but queue full, may hang\n",
			ifp->if_name, ifp->if_unit);*/
		m_freem(m);
		error = ENOBUFS;
	} else {
		IF_ENQUEUE(&ifp->if_snd, m);
		if ((ifp->if_flags & IFF_OACTIVE) == 0)
			(*ifp->if_start)(ifp);
	}
	splx(s);
	return (error);
}

E 3
#endif
E 1
