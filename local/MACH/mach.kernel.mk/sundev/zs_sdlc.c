/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	zs_sdlc.c,v $
 * Revision 2.4  89/03/09  21:50:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:00:46  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Made VOLATILE
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)zs_sdlc.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif
int zsdebug = 0;
#define dprintf	if(zsdebug)printf

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <zss.h>
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/netisr.h>
#include <sundev/zsreg.h>
#include <sundev/zscom.h>

/*
 * The SDLC zs protocol
 */
int	zss_attach(), zss_txint(), zss_xsint(), zss_rxint(), zss_srint(),
	zss_softint();

struct zsops zsops_sdlc = {
	zss_attach,
	zss_txint,
	zss_xsint,
	zss_rxint,
	zss_srint,
	zss_softint,
};

#define ZSDLCMTU	512	/* ??? inet only? */

struct zss_stats {
	int	zss_ipack;	/* input packets */	
	int	zss_opack;	/* output packets */	
	int	zss_ichar;	/* input bytes */	
	int	zss_ochar;	/* output bytes */	
	/* input errors */
	int	zss_nobuf;	/* no buffers available */
	int	zss_abort;	/* abort received */
	int	zss_crc;	/* CRC error */
	int	zss_overrun;	/* receiver overrun */
	/* output errors */
	int	zss_underrun;	/* xmitter underrun */
	int	zss_drops;	/* out Q too long */
} zss_stats[NZSS];

struct zsdlc {
	struct ifnet zd_if;	/* MUST BE FIRST */
	struct zscom *zd_zs;		/* related zscom */
	struct zss_stats *zd_st;	/* related stats */
	u_char	zd_rr0;			/* saved RR0 */
	char	zd_xactive;		/* output active */
	struct mbuf *zd_xact;		/* first mbuf of xmit packet */
	struct mbuf *zd_xactm;		/* current mbuf of xmit packet */
	struct mbuf *zd_txfree;		/* xmitted mbufs to be freed */
	u_char	*zd_optr;		/* output ptr */	
	short	zd_ocnt;		/* output count */	
	struct mbuf *zd_ract;		/* first mbuf of recv packet */
	struct mbuf *zd_ractm;		/* current mbuf of recv packet */
	struct mbuf *zd_rxfree;		/* free mbufs to be filled */
	struct ifqueue zd_rqueue;	/* received packets */
	short	zd_nrfree;		/* # of mbufs on rxfree list */
	short	zd_nrinuse;		/* # of mbufs on ract list */
	short	zd_nropt;		/* # of mbufs desired on standby */
	short	zd_rxoff;		/* offset of first byte in packet */
	u_char	*zd_rptr;		/* recv ptr */	
	short	zd_rcnt;		/* recv count */	
} zsdlc[NZSS];
#define IFTOZD(ifp)	((struct zsdlc *)(ifp))

int	zss_output(), zss_init(), zss_ioctl();

zss_attach(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = &zsdlc[zs->zs_unit];
	register struct ifnet *ifp = &zd->zd_if;

	if (zd >= &zsdlc[NZSS])
		return;
	zd->zd_zs = zs;
	zd->zd_st = &zss_stats[zs->zs_unit];
	ifp->if_name = "zss";
	ifp->if_mtu = ZSDLCMTU;
	zd->zd_nropt = 2 * (1 + ZSDLCMTU / MLEN);
	ifp->if_flags = IFF_POINTOPOINT;
	ifp->if_unit = zs->zs_unit;
	ifp->if_output = zss_output;
	ifp->if_init = zss_init;
	ifp->if_ioctl = zss_ioctl;
	if_attach(ifp);
#include <ptp.h>
#if	NPTP > 0
	ptp_init();
#endif
}

#define SDLCFLAG	0x7E	/* 01111110 - manifest flag of SDLC */
zss_init(unit)
	int unit;
{
	register struct zsdlc *zd = &zsdlc[unit];
	register struct ifnet *ifp = &zd->zd_if;
	register struct zscom *zs = zd->zd_zs;
	int s;

	if ((ifp->if_flags & IFF_RUNNING) == 0)
		return;

	s = splzs();
	zs->zs_priv = (caddr_t)zd;
	zsopinit(zs, &zsops_sdlc);
	ZWRITE(3, 0);		/* disable receiver while changing modes */
	(void) splx(s);
	s = splimp();
	zss_softint(zs);		/* initializes recv buffers */
	(void) splx(s);
	s = splzs();
	ZWRITE(4, ZSWR4_SDLC );
	ZWRITE(10, ZSWR10_PRESET_ONES);
	ZWRITE(7, SDLCFLAG);
	ZWRITE(11, ZSWR11_TXCLK_TRXC + ZSWR11_RXCLK_RTXC);
	ZWRITE(14, ZSWR14_DPLL_DISABLE);
	ZWRITE(3, ZSWR3_RX_ENABLE + ZSWR3_RXCRC_ENABLE + ZSWR3_RX_8);
	ZWRITE(5, ZSWR5_TX_8 + ZSWR5_DTR + ZSWR5_RTS +
		ZSWR5_TXCRC_ENABLE + ZSWR5_TX_ENABLE);
	ZWRITE(1, ZSWR1_SIE|ZSWR1_TIE|ZSWR1_RIE);
	zs->zs_addr->zscc_control =
		ZSWR0_RESET_ERRORS + ZSWR0_RESET_STATUS + ZSWR0_RESET_TXCRC;
	(void) splx(s);
	ifp->if_flags |= IFF_UP|IFF_RUNNING;
}

/*
 * Process an interface ioctl request.
 */
zss_ioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	struct sockaddr *sa;
	int mtu;

	switch (cmd) {

	case SIOCSIFADDR:
		sa = (struct sockaddr *)data;
		if (sa->sa_family == AF_UNSPEC)
			return (EINVAL);
		ifp->if_addr = *sa;
		if ((ifp->if_flags & IFF_RUNNING) == 0) {
			ifp->if_flags |= IFF_RUNNING;
			zss_init(ifp->if_unit);
		}
		break;

	case SIOCSIFMTU:
		mtu = *(int *)data;
		if (mtu < 32 || mtu > 4096)
			return (EINVAL);
		ifp->if_mtu = mtu;
		IFTOZD(ifp)->zd_nropt = 2 * (1 + mtu / MLEN);
		break;

	default:
		return (EINVAL);
	}
	return (0);
}

zss_output(ifp, m, dst)
	register struct ifnet *ifp;
	struct mbuf *m;
	struct sockaddr *dst;
{
	register struct zsdlc *zd = IFTOZD(ifp);
	register struct zscom *zs = zd->zd_zs;
	int s;

	if (zd != (struct zsdlc *)zs->zs_priv) {
		m_freem(m);
		return (ENETDOWN);
	}
/* XXX ??? check dst? */
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splzs();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		(void) splx(s);
		m_freem(m);
		zd->zd_st->zss_drops++;
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	if (!zd->zd_xactive) {
		zd->zd_xactive = 1;
		zss_start(zs);
	}
	(void) splx(s);
	return (0);
}

/*
 * Pull an mbuf chain off the queue and start the first character xmitting.
 * call at splzs
 */
zss_start(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register struct ifnet *ifp = &zd->zd_if;
	register volatile struct zscc_device *zsaddr = zs->zs_addr;
	register struct mbuf *m;

top:
	IF_DEQUEUE(&ifp->if_snd, m);
	if (m == 0) {
		zd->zd_xactive = 0;
		zsaddr->zscc_control = ZSWR0_RESET_TXINT;
		return;
	}
	zd->zd_xact = m;
	m->m_act = 0;
	while (m && m->m_len == 0)
		m = m->m_next;
	if (m == 0) {		/* zero length packet! */
		m = zd->zd_xact;
		zd->zd_xact = 0;
		m->m_act = zd->zd_txfree;
		zd->zd_txfree = m;
		ZSSETSOFT(zs);
		goto top;
	}
	zd->zd_xactm = m;
	zsaddr->zscc_control = ZSWR0_RESET_TXCRC;
	zd->zd_optr = mtod(m, u_char *);
	zd->zd_ocnt = m->m_len - 1;
	zsaddr->zscc_data = *zd->zd_optr++;	/* resets TXINT */
}

zss_txint(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register volatile struct zscc_device *zsaddr = zs->zs_addr;
	register struct mbuf *m;

	if (zd->zd_ocnt-- > 0) {
		zsaddr->zscc_data = *zd->zd_optr++;
		return;
	}
	if (m = zd->zd_xactm) {
		zd->zd_st->zss_ochar += m->m_len;
		do {
			m = m->m_next;
		} while (m && m->m_len == 0);
		zd->zd_xactm = m;
		if (m) {			/* more data in packet */
			zd->zd_optr = mtod(m, u_char *);
			zd->zd_ocnt = m->m_len - 1;
			zsaddr->zscc_data = *zd->zd_optr++; /* resets TXINT */
			return;
		}
		/* sent last character */
		zsaddr->zscc_control = ZSWR0_RESET_EOM + ZSWR0_RESET_TXINT;
		zd->zd_rr0 &= ~ZSRR0_TXUNDER;
		m = zd->zd_xact;
		zd->zd_xact = 0;
		m->m_act = zd->zd_txfree;
		zd->zd_txfree = m;
		zd->zd_if.if_opackets++;
		zd->zd_st->zss_opack++;
		ZSSETSOFT(zs);
		return;
	}
	/* here only after transmitting CRC */
	zss_start(zs);
}

zss_xsint(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register volatile struct zscc_device *zsaddr = zs->zs_addr;
	register struct mbuf *m;
	u_char s0, x0;

	s0 = zsaddr->zscc_control;
	x0 = s0 ^ zd->zd_rr0;
	zd->zd_rr0 = s0;
	zsaddr->zscc_control = ZSWR0_RESET_STATUS;
	if (zd->zd_ocnt > 0 && (x0 & ZSRR0_TXUNDER) && (s0 & ZSRR0_TXUNDER)) {
		zd->zd_ocnt = 0;
		zd->zd_xactm = 0;
		m = zd->zd_xact;
		zd->zd_xact = 0;
		m->m_act = zd->zd_txfree;
		zd->zd_txfree = m;
		zd->zd_if.if_oerrors++;
		zd->zd_st->zss_underrun++;
	}
	if ((x0 & ZSRR0_BREAK) && (s0 & ZSRR0_BREAK)) {
		zd->zd_st->zss_abort++;
		zss_rxbad(zs);
	}
	ZSSETSOFT(zs);
}

zss_rxint(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register volatile struct zscc_device *zsaddr = zs->zs_addr;
	register struct mbuf *m;
	u_char c;

	if (zd->zd_rcnt-- > 0) {
		*zd->zd_rptr++ = zsaddr->zscc_data;
		return;
	}
	c = zsaddr->zscc_data;		/* resets intr */
	if (m = zd->zd_ractm) {		/* middle of packet */
		zd->zd_st->zss_ichar += m->m_len;
		m->m_next = zd->zd_rxfree;
		if ((m = m->m_next) == 0) {	/* out of mbufs */
			zd->zd_st->zss_nobuf++;
			zss_rxbad(zs);
			return;
		}
		zd->zd_rxfree = zd->zd_rxfree->m_next;
		m->m_next = 0;
		zd->zd_ractm = m;
		zd->zd_nrfree--;
		zd->zd_nrinuse++;
		m->m_off = MMINOFF;
		m->m_len = MLEN;
		zd->zd_rptr = mtod(m, u_char *);
		zd->zd_rcnt = MLEN - 1;
		*zd->zd_rptr++ = c;
		return;
	}
	/* here if beginning of packet */
	if ((m = zd->zd_rxfree) == 0) {		/* no mbufs */
		zd->zd_st->zss_nobuf++;
		zss_rxbad(zs);
		return;
	}
	zd->zd_rxfree = zd->zd_rxfree->m_next;
	m->m_next = 0;
	zd->zd_ract = zd->zd_ractm = m;
	zd->zd_nrfree--;
	zd->zd_nrinuse = 1;
	m->m_off = MMINOFF + zd->zd_rxoff;
	m->m_len = MLEN - zd->zd_rxoff;
	zd->zd_rptr = mtod(m, u_char *);
	zd->zd_rcnt = m->m_len - 1;
	*zd->zd_rptr++ = c;
}

zss_srint(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register volatile struct zscc_device *zsaddr = zs->zs_addr;
	register struct mbuf *m;
	u_char s1, c, *p;

	s1 = ZREAD(1);
	c = zsaddr->zscc_data;
	zsaddr->zscc_control = ZSWR0_RESET_ERRORS;
	if (s1 & ZSRR1_RXEOF) {			/* end of frame */
		if (s1 & ZSRR1_FE) {		/* bad CRC */
			zd->zd_st->zss_crc++;
			zss_rxbad(zs);
			return;
		}
		if ((m = zd->zd_ractm) == 0) 	/* confused */
			return;
		p = mtod(m, u_char *);
		m->m_len = zd->zd_rptr - p;
		zd->zd_rcnt = 0;
		/* drop previous byte from packet (first CRC byte) */
		m->m_len--;
		zd->zd_st->zss_ichar += m->m_len;
		/* put on done queue */
		m = zd->zd_ract;
		zd->zd_ract = zd->zd_ractm = 0;
		zd->zd_nrinuse = 0;
		IF_ENQUEUE(&zd->zd_rqueue, m);
		ZSSETSOFT(zs);
	} else if (s1 & ZSRR1_DO) {
		c = zsaddr->zscc_data;	/* swallow bad char */
		c = zsaddr->zscc_data;	/* swallow bad char */
		zd->zd_st->zss_overrun++;
		zss_rxbad(zs);
	}
}

zss_softint(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;
	register struct ifnet *ifp = &zd->zd_if;
	register struct mbuf *m;
	int s;

	/*
	 * Clean up after transmitter 
	 */
	do {
		s = splzs();
		if (m = zd->zd_txfree) {
			zd->zd_txfree = m->m_act;
			m->m_act = 0;
		}
		(void) splx(s);
		if (m)
			m_freem(m);
	} while (m);

	/*
	 * Make sure the receiver has the nominal number of free mbufs
	 * on his list
	 */
	if (zsdebug) {
		int nfree = 0, xfree;

		s = splzs();
		for (m = zd->zd_rxfree; m; m = m->m_next)
			nfree++;
		xfree = zd->zd_nrfree;
		zd->zd_nrfree = nfree;
		(void) splx(s);
		if (nfree != xfree)
			printf("free count %d actual %x\n", xfree, nfree);
	}

	while (zd->zd_nrfree < zd->zd_nropt) {
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == 0)
			break;
		s = splzs();
		m->m_next = zd->zd_rxfree;
		zd->zd_rxfree = m;
		zd->zd_nrfree++;
		(void) splx(s);
	}

	/*
	 * Move received packets from queue at splzs
	 * into the system at splimp
	 */
	for (;;) {
		s = splzs();
		IF_DEQUEUE(&zd->zd_rqueue, m);
		(void) splx(s);
		if (m == 0)
			break;
		if (ifp->if_upper && ifp->if_upper->if_input)
			(*ifp->if_upper->if_input)(ifp->if_upper, m);
		else
			m_freem(m);
		ifp->if_ipackets++;
		zd->zd_st->zss_ipack++;
	}
}

zss_rxbad(zs)
	register struct zscom *zs;
{
	register struct zsdlc *zd = (struct zsdlc *)zs->zs_priv;

	zd->zd_if.if_ierrors++;
	/* enter hunt mode - ignores rest of frame */
	ZWRITE(3, ZSWR3_RX_ENABLE+ZSWR3_RXCRC_ENABLE+
		ZSWR3_RX_8+ZSWR3_HUNT);
	/* put any used mbufs back on free list */
	if (zd->zd_ractm) {
		zd->zd_ractm->m_next = zd->zd_rxfree;
		zd->zd_rxfree = zd->zd_ract;
		zd->zd_nrfree += zd->zd_nrinuse;
		zd->zd_nrinuse = 0;
		zd->zd_ract = zd->zd_ractm = 0;
	}
	zd->zd_rcnt = 0;
	ZSSETSOFT(zs);
}
