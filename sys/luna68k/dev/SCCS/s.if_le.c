h56637
s 00002/00002/00889
d D 8.1 93/06/10 22:16:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00001/00874
d D 7.6 93/05/12 04:09:03 akito 6 5
c LUNA-II (68040 based LUNA) support
e
s 00002/00002/00873
d D 7.5 93/03/17 11:09:01 akito 5 4
c sync up to hp300/dev/if_le.c    7.16
e
s 00020/00002/00855
d D 7.4 93/01/13 15:48:22 akito 4 3
c sync up to hp300/dev/if_le.c    7.15
e
s 00026/00027/00831
d D 7.3 92/10/11 10:57:17 bostic 3 2
c make kernel includes standard
e
s 00209/00118/00649
d D 7.2 92/07/23 16:02:02 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00767/00000/00000
d D 7.1 92/06/15 06:45:47 fujita 1 0
c date and time created 92/06/15 06:45:47 by fujita
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
E 2
I 2
D 7
 * Copyright (c) 1982, 1990 The Regents of the University of California.
E 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
I 2
D 4
 * from: hp300/dev/if_le.c	7.12 (Berkeley) 7/6/92
E 4
I 4
D 5
 * from: hp300/dev/if_le.c	7.15 (Berkeley) 12/28/92
E 5
I 5
 * from: hp300/dev/if_le.c	7.16 (Berkeley) 3/11/93
E 5
E 4
 *
E 2
 *	%W% (Berkeley) %G%
 */

#include "le.h"
#if NLE > 0

#include "bpfilter.h"

/*
 * AMD 7990 LANCE
 *
D 2
 * This driver will generate and accept tailer encapsulated packets even
E 2
I 2
 * This driver will accept tailer encapsulated packets even
E 2
 * though it buys us nothing.  The motivation was to avoid incompatibilities
 * with VAXen, SUNs, and others that handle and benefit from them.
 * This reasoning is dubious.
 */
D 3
#include "sys/param.h"
#include "sys/proc.h"
#include "sys/systm.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/protosw.h"
#include "sys/socket.h"
#include "sys/syslog.h"
#include "sys/ioctl.h"
#include "sys/errno.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/syslog.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
E 3

D 3
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 3
I 3
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
E 3

#ifdef INET
D 3
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 3
I 3
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 3
#endif

#ifdef NS
D 3
#include "netns/ns.h"
#include "netns/ns_if.h"
E 3
I 3
#include <netns/ns.h>
#include <netns/ns_if.h>
E 3
#endif

I 4
#if defined (CCITT) && defined (LLC)
#include <sys/socketvar.h>
#include <netccitt/x25.h>
extern llc_ctlinput(), cons_rtrequest();
#endif

E 4
D 2
#ifdef ISO
extern	char all_es_snpa[], all_is_snpa[], all_l1is_snpa[], all_l2is_snpa[];
#endif

E 2
D 3
#include "../include/cpu.h"
#include "../include/mtpr.h"
#include "device.h"
#include "if_lereg.h"
E 3
I 3
#include <machine/cpu.h>
#include <machine/mtpr.h>
#include <luna68k/dev/device.h>
#include <luna68k/dev/if_lereg.h>
E 3

#if NBPFILTER > 0
D 3
#include "../net/bpf.h"
#include "../net/bpfdesc.h"
E 3
I 3
#include <net/bpf.h>
#include <net/bpfdesc.h>
E 3
D 2
char hprmp_multi[] = { 9, 0, 9, 0, 0, 4};
E 2
#endif
D 3

E 3

int	leattach();
struct	driver ledriver = {
	leattach, "le",
};

int	ledebug = 0;		/* console error messages */

D 4
int	leintr(), leinit(), leioctl(), lestart(), ether_output();
E 4
I 4
int	leintr(), leinit(), leioctl(), lestart(), ether_output(), lereset();
E 4
struct	mbuf *m_devget();
extern	struct ifnet loif;

/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * le_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
struct	le_softc {
	struct	arpcom sc_ac;	/* common Ethernet structures */
#define	sc_if	sc_ac.ac_if	/* network-visible interface */
#define	sc_addr	sc_ac.ac_enaddr	/* hardware Ethernet address */
	struct	lereg1 *sc_r1;	/* LANCE registers */
	struct	lereg2 *sc_r2;	/* dual-port RAM */
	int	sc_rmd;		/* predicted next rmd to process */
I 2
	int	sc_tmd;		/* next available tmd */
	int	sc_txcnt;	/* # of transmit buffers in use */
	/* stats */
E 2
	int	sc_runt;
	int	sc_jab;
	int	sc_merr;
	int	sc_babl;
	int	sc_cerr;
	int	sc_miss;
D 2
	int	sc_xint;
E 2
I 2
	int	sc_rown;
E 2
	int	sc_xown;
I 2
	int	sc_xown2;
E 2
	int	sc_uflo;
	int	sc_rxlen;
	int	sc_rxoff;
	int	sc_txoff;
	int	sc_busy;
	short	sc_iflags;
D 2
	caddr_t sc_bpf;
	int	sc_tmd;		/* predicted next tmd to process */
	int	sc_txcnt;	/* transmissions in progress */
	int	sc_txbad;
	int	sc_txbusy;
E 2
} le_softc[NLE];

/* access LANCE registers */
#define	LERDWR(cntl, src, dst)	(dst) = (src)

#define LE_IPL		3

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
leattach(hd)
	struct hp_device *hd;
{
	register struct lereg2 *ler2;
	struct lereg2 *lemem = (struct lereg2 *) 0;
	struct le_softc *le = &le_softc[hd->hp_unit];
	struct ifnet *ifp = &le->sc_if;
	char *cp;
	int i;

	le->sc_r1 = (struct lereg1 *) hd->hp_addr;
	ler2 = le->sc_r2 = (struct lereg2 *) 0x71000000;

	hd->hp_ipl = LE_IPL;

	/*
	 * Read the ethernet address off the board, one nibble at a time.
	 */
#ifdef NOROM
	cp = "00000a02456c";
#else
D 6
	cp = (char *) 0x4101FFE0;
E 6
I 6
#if defined(LUNA2)
	if (machineid == LUNA_II) {
		static char rom_data[128];
		volatile u_int *from = (u_int *)0xf1000004;
		for (i = 0; i < 128; i++) {
			*from = (i * 2) << 16;
			rom_data[i] |= (*from >> 12) & 0xf0;
			*from = (i * 2 + 1) << 16;
			rom_data[i] |= (*from >> 16) & 0xf;
		}
		cp =&rom_data[6]; /* ETHER0 must be here */
		/* one port only now  XXX */
	} else
#endif
	{
		cp = (char *) 0x4101FFE0;
	}
E 6
#endif
	for (i = 0; i < sizeof(le->sc_addr); i++) {
		le->sc_addr[i]  = (*cp < 'A' ? (*cp & 0xF) : (*cp & 0xF) + 9) << 4;
		cp++;
		le->sc_addr[i] |= (*cp < 'A' ? (*cp & 0xF) : (*cp & 0xF) + 9);
		cp++;
	}
	printf("le%d: hardware address %s\n", hd->hp_unit,
		ether_sprintf(le->sc_addr));

	/*
	 * Setup for transmit/receive
	 */
	ler2->ler2_mode = LE_MODE;
D 2
#if defined(ISO) || NBPFILTER > 0
	ler2->ler2_ladrf0 = 0xffffffff;
	ler2->ler2_ladrf1 = 0xffffffff;
#else
	ler2->ler2_ladrf0 = 0;
	ler2->ler2_ladrf1 = 0;
#endif
E 2
I 2
	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
E 2
	ler2->ler2_rlen = LE_RLEN;
	ler2->ler2_rdra = (int)lemem->ler2_rmd;
	ler2->ler2_tlen = LE_TLEN;
	ler2->ler2_tdra = (int)lemem->ler2_tmd;

	ifp->if_unit = hd->hp_unit;
	ifp->if_name = "le";
	ifp->if_mtu = ETHERMTU;
	ifp->if_init = leinit;
I 4
	ifp->if_reset = lereset;
E 4
	ifp->if_ioctl = leioctl;
	ifp->if_output = ether_output;
	ifp->if_start = lestart;
I 2
#ifdef MULTICAST
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
#else
E 2
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX;
I 2
#endif
E 2
#if NBPFILTER > 0
D 2
	bpfattach(&le->sc_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 2
I 2
	bpfattach(&ifp->if_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 2
#endif
	if_attach(ifp);
	return (1);
}

I 2
#ifdef MULTICAST
/*
 * Setup the logical address filter
 */
void
lesetladrf(sc)
	register struct le_softc *sc;
{
	register volatile struct lereg2 *ler2 = sc->sc_r2;
	register struct ifnet *ifp = &sc->sc_if;
	register struct ether_multi *enm;
	register u_char *cp;
	register u_long crc;
	register u_long c;
	register int i, len;
	struct ether_multistep step;

	/*
	 * Set up multicast address filter by passing all multicast
	 * addresses through a crc generator, and then using the high
	 * order 6 bits as a index into the 64 bit logical address
	 * filter. The high order two bits select the word, while the
	 * rest of the bits select the bit within the word.
	 */

	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
	ifp->if_flags &= ~IFF_ALLMULTI;
	ETHER_FIRST_MULTI(step, &sc->sc_ac, enm);
	while (enm != NULL) {
		if (bcmp((caddr_t)&enm->enm_addrlo,
		    (caddr_t)&enm->enm_addrhi, sizeof(enm->enm_addrlo)) == 0) {
			/*
			 * We must listen to a range of multicast
			 * addresses. For now, just accept all
			 * multicasts, rather than trying to set only
			 * those filter bits needed to match the range.
			 * (At this time, the only use of address
			 * ranges is for IP multicast routing, for
			 * which the range is big enough to require all
			 * bits set.)
			 */
			ler2->ler2_ladrf[0] = 0xffffffff;
			ler2->ler2_ladrf[1] = 0xffffffff;
			ifp->if_flags |= IFF_ALLMULTI;
			return;
		}

		cp = (unsigned char *)&enm->enm_addrlo;
		c = *cp;
		crc = 0xffffffff;
		len = 6;
		while (len-- > 0) {
			c = *cp;
			for (i = 0; i < 8; i++) {
				if ((c & 0x01) ^ (crc & 0x01)) {
					crc >>= 1;
					crc = crc ^ 0xedb88320;
				}
				else
					crc >>= 1;
				c >>= 1;
			}
			cp++;
		}
		/* Just want the 6 most significant bits. */
		crc = crc >> 26;

		/* Turn on the corresponding bit in the filter. */
		ler2->ler2_ladrf[crc >> 5] |= 1 << (crc & 0x1f);

		ETHER_NEXT_MULTI(step, enm);
	}
}
#endif

E 2
ledrinit(ler2, le)
	register struct lereg2 *ler2;
	register struct le_softc *le;
{
	register struct lereg2 *lemem = (struct lereg2 *) 0;
	register int i;

	ler2->ler2_padr[0] = le->sc_addr[1];
	ler2->ler2_padr[1] = le->sc_addr[0];
	ler2->ler2_padr[2] = le->sc_addr[3];
	ler2->ler2_padr[3] = le->sc_addr[2];
	ler2->ler2_padr[4] = le->sc_addr[5];
	ler2->ler2_padr[5] = le->sc_addr[4];
	for (i = 0; i < LERBUF; i++) {
		ler2->ler2_rmd[i].rmd0 = (int)lemem->ler2_rbuf[i];
		ler2->ler2_rmd[i].rmd1 = LE_OWN;
		ler2->ler2_rmd[i].rmd2 = -LEMTU;
		ler2->ler2_rmd[i].rmd3 = 0;
	}
	for (i = 0; i < LETBUF; i++) {
		ler2->ler2_tmd[i].tmd0 = (int)lemem->ler2_tbuf[i];
		ler2->ler2_tmd[i].tmd1 = 0;
		ler2->ler2_tmd[i].tmd2 = 0;
		ler2->ler2_tmd[i].tmd3 = 0;
	}
I 2
	/* Setup the logical address filter */
#ifdef MULTICAST
	lesetladrf(le);
#else
	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
#endif
E 2
}

lereset(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct lereg1 *ler1 = le->sc_r1;
	register struct lereg2 *lemem = (struct lereg2 *) 0;
	register int timo = 100000;
	register int stat;

#ifdef lint
	stat = unit;
#endif
#if NBPFILTER > 0
	if (le->sc_if.if_flags & IFF_PROMISC)
		/* set the promiscuous bit */
		le->sc_r2->ler2_mode = LE_MODE|0x8000;
	else
		le->sc_r2->ler2_mode = LE_MODE;
#endif
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_STOP, ler1->ler1_rdp);
	ledrinit(le->sc_r2, le);
D 2
	le->sc_txcnt = le->sc_tmd = le->sc_rmd = 0;
E 2
I 2
	le->sc_rmd = le->sc_tmd = 0;
E 2
	LERDWR(ler0, LE_CSR1, ler1->ler1_rap);
	LERDWR(ler0, (int)&lemem->ler2_mode, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR2, ler1->ler1_rap);
	LERDWR(ler0, 0, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_INIT, ler1->ler1_rdp);
	do {
		if (--timo == 0) {
			printf("le%d: init timeout, stat = 0x%x\n",
			       unit, stat);
			break;
		}
		LERDWR(ler0, ler1->ler1_rdp, stat);
	} while ((stat & LE_IDON) == 0);
	LERDWR(ler0, LE_STOP, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR3, ler1->ler1_rap);
	LERDWR(ler0, LE_BSWP, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_STRT | LE_INEA, ler1->ler1_rdp);
	le->sc_if.if_flags &= ~IFF_OACTIVE;
I 2
	le->sc_txcnt = 0;
E 2
}

/*
 * Initialization of interface
 */
leinit(unit)
	int unit;
{
	register struct ifnet *ifp = &le_softc[unit].sc_if;
	register struct ifaddr *ifa;
	int s;

	/* not yet, if address still unknown */
	for (ifa = ifp->if_addrlist;; ifa = ifa->ifa_next)
		if (ifa == 0)
			return;
		else if (ifa->ifa_addr && ifa->ifa_addr->sa_family != AF_LINK)
			break;
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		s = splimp();
		ifp->if_flags |= IFF_RUNNING;
		lereset(unit);
	        (void) lestart(ifp);
		splx(s);
	}
}

/*
 * Start output on interface.  Get another datagram to send
 * off of the interface queue, and copy it to the interface
 * before starting the output.
 */
lestart(ifp)
	struct ifnet *ifp;
{
	register struct le_softc *le = &le_softc[ifp->if_unit];
	register struct letmd *tmd;
	register struct mbuf *m;
	int len;

D 2
again:
E 2
	if ((le->sc_if.if_flags & IFF_RUNNING) == 0)
		return (0);
D 2
	IF_DEQUEUE(&le->sc_if.if_snd, m);
	if (m == 0)
		return (0);
	tmd = le->sc_r2->ler2_tmd + le->sc_tmd;
	if (tmd->tmd1 & LE_OWN)
		return (le->sc_txbusy++, 0);
	len = leput(le->sc_r2->ler2_tbuf[le->sc_tmd], m);
E 2
I 2
	tmd = &le->sc_r2->ler2_tmd[le->sc_tmd];
	do {
		if (tmd->tmd1 & LE_OWN) {
			le->sc_xown2++;
			return (0);
		}
		IF_DEQUEUE(&le->sc_if.if_snd, m);
		if (m == 0)
			return (0);
		len = leput(le->sc_r2->ler2_tbuf[le->sc_tmd], m);
E 2
#if NBPFILTER > 0
D 2
	/*
	 * If bpf is listening on this interface, let it
	 * see the packet before we commit it to the wire.
	 */
	if (le->sc_bpf)
                bpf_tap(le->sc_bpf, le->sc_r2->ler2_tbuf[le->sc_tmd], len);
E 2
I 2
		/* 
		 * If bpf is listening on this interface, let it 
		 * see the packet before we commit it to the wire.
		 */
		if (ifp->if_bpf)
			bpf_tap(ifp->if_bpf, le->sc_r2->ler2_tbuf[le->sc_tmd],
				len);
E 2
#endif
D 2
	tmd->tmd3 = 0;
	tmd->tmd2 = -len;
	if (++le->sc_tmd >= LETBUF)
		le->sc_tmd = 0;
	if (++le->sc_txcnt >= LETBUF) {
		le->sc_txcnt = LETBUF;
		le->sc_if.if_flags |= IFF_OACTIVE;
E 2
I 2

		tmd->tmd3 = 0;
		tmd->tmd2 = -len;
E 2
		tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
D 2
	} else {
		tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
		goto again;
	}
E 2
I 2
		if (++le->sc_tmd == LETBUF) {
			le->sc_tmd = 0;
			tmd = le->sc_r2->ler2_tmd;
		} else
			tmd++;
	} while (++le->sc_txcnt < LETBUF);
	le->sc_if.if_flags |= IFF_OACTIVE;
E 2
	return (0);
}

void
_leintr()
{
	register int i;

	for (i = 0; i < NLE; i++) {
		leintr(i);
	}
}

int
leintr(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct lereg1 *ler1;
	register int stat;

	ler1 = le->sc_r1;
	LERDWR(ler0, ler1->ler1_rdp, stat);
	if (stat & LE_SERR) {
		leerror(unit, stat);
		if (stat & LE_MERR) {
			le->sc_merr++;
			lereset(unit);
			return(1);
		}
		if (stat & LE_BABL)
			le->sc_babl++;
		if (stat & LE_CERR)
			le->sc_cerr++;
		if (stat & LE_MISS)
			le->sc_miss++;
		LERDWR(ler0, LE_BABL|LE_CERR|LE_MISS|LE_INEA, ler1->ler1_rdp);
	}
	if ((stat & LE_RXON) == 0) {
		le->sc_rxoff++;
		lereset(unit);
		return(1);
	}
	if ((stat & LE_TXON) == 0) {
		le->sc_txoff++;
		lereset(unit);
		return(1);
	}
D 2
	if (stat & LE_RINT) {
		/* interrupt is cleared in lerint */
E 2
I 2
	if (stat & LE_RINT)
E 2
		lerint(unit);
D 2
	}
	if (stat & LE_TINT) {
		LERDWR(ler0, LE_TINT|LE_INEA, ler1->ler1_rdp);
E 2
I 2
	if (stat & LE_TINT)
E 2
		lexint(unit);
D 2
	}
E 2
	return(1);
}

/*
 * Ethernet interface transmitter interrupt.
 * Start another output if more data to send.
 */
lexint(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct letmd *tmd;
D 2
	int i, loopcount = 0;
E 2
I 2
	int i, gotone = 0;
E 2

D 2
	if (le->sc_txcnt == 0) {
		le->sc_xint++;
		return;
	}
again:
	if ((i = le->sc_tmd - le->sc_txcnt) < 0) i += LETBUF;
	tmd = le->sc_r2->ler2_tmd + i;
	if (tmd->tmd1 & LE_OWN) {
		if (loopcount)
			goto out;
		le->sc_xown++;
		return;
	}
	if (tmd->tmd1 & LE_ERR) {
err:
		lexerror(unit);
		le->sc_if.if_oerrors++;
		if (tmd->tmd3 & (LE_TBUFF|LE_UFLO)) {
			le->sc_uflo++;
			lereset(unit);
E 2
I 2
	do {
		if ((i = le->sc_tmd - le->sc_txcnt) < 0)
			i += LETBUF;
		tmd = &le->sc_r2->ler2_tmd[i];
		if (tmd->tmd1 & LE_OWN) {
			if (gotone)
				break;
			le->sc_xown++;
			return;
E 2
		}
D 2
		else if (tmd->tmd3 & LE_LCOL)
			le->sc_if.if_collisions++;
		else if (tmd->tmd3 & LE_RTRY)
			le->sc_if.if_collisions += 16;
	}
	else if (tmd->tmd3 & LE_TBUFF)
E 2
I 2

		/* clear interrupt */
		LERDWR(le->sc_r0, LE_TINT|LE_INEA, le->sc_r1->ler1_rdp);

E 2
		/* XXX documentation says BUFF not included in ERR */
D 2
		goto err;
	else if (tmd->tmd1 & LE_ONE)
		le->sc_if.if_collisions++;
	else if (tmd->tmd1 & LE_MORE)
		/* what is the real number? */
		le->sc_if.if_collisions += 2;
	else
		le->sc_if.if_opackets++;
	loopcount++;
	if (--le->sc_txcnt > 0)
		goto again;
	if (le->sc_txcnt < 0) {
		le->sc_txbad++;
		le->sc_txcnt = 0;
	}
out:
E 2
I 2
		if ((tmd->tmd1 & LE_ERR) || (tmd->tmd3 & LE_TBUFF)) {
			lexerror(unit);
			le->sc_if.if_oerrors++;
			if (tmd->tmd3 & (LE_TBUFF|LE_UFLO)) {
				le->sc_uflo++;
				lereset(unit);
			} else if (tmd->tmd3 & LE_LCOL)
				le->sc_if.if_collisions++;
			else if (tmd->tmd3 & LE_RTRY)
				le->sc_if.if_collisions += 16;
		} else if (tmd->tmd1 & LE_ONE)
			le->sc_if.if_collisions++;
		else if (tmd->tmd1 & LE_MORE)
			/* what is the real number? */
			le->sc_if.if_collisions += 2;
		else
			le->sc_if.if_opackets++;
		gotone++;
	} while (--le->sc_txcnt > 0);
E 2
	le->sc_if.if_flags &= ~IFF_OACTIVE;
	(void) lestart(&le->sc_if);
}

#define	LENEXTRMP \
	if (++bix == LERBUF) bix = 0, rmd = le->sc_r2->ler2_rmd; else ++rmd

/*
 * Ethernet interface receiver interrupt.
 * If input error just drop packet.
 * Decapsulate packet based on type and pass to type specific
 * higher-level input routine.
 */
lerint(unit)
	int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register int bix = le->sc_rmd;
	register struct lermd *rmd = &le->sc_r2->ler2_rmd[bix];

	/*
	 * Out of sync with hardware, should never happen?
	 */
	if (rmd->rmd1 & LE_OWN) {
I 2
		le->sc_rown++;
E 2
		LERDWR(le->sc_r0, LE_RINT|LE_INEA, le->sc_r1->ler1_rdp);
		return;
	}

	/*
	 * Process all buffers with valid data
	 */
	while ((rmd->rmd1 & LE_OWN) == 0) {
		int len = rmd->rmd3;

		/* Clear interrupt to avoid race condition */
		LERDWR(le->sc_r0, LE_RINT|LE_INEA, le->sc_r1->ler1_rdp);

		if (rmd->rmd1 & LE_ERR) {
			le->sc_rmd = bix;
			lererror(unit, "bad packet");
			le->sc_if.if_ierrors++;
		} else if ((rmd->rmd1 & (LE_STP|LE_ENP)) != (LE_STP|LE_ENP)) {
			/*
			 * Find the end of the packet so we can see how long
			 * it was.  We still throw it away.
			 */
			do {
				LERDWR(le->sc_r0, LE_RINT|LE_INEA,
				       le->sc_r1->ler1_rdp);
				rmd->rmd3 = 0;
				rmd->rmd1 = LE_OWN;
				LENEXTRMP;
			} while (!(rmd->rmd1 & (LE_OWN|LE_ERR|LE_STP|LE_ENP)));
			le->sc_rmd = bix;
			lererror(unit, "chained buffer");
			le->sc_rxlen++;
			/*
			 * If search terminated without successful completion
			 * we reset the hardware (conservative).
			 */
			if ((rmd->rmd1 & (LE_OWN|LE_ERR|LE_STP|LE_ENP)) !=
			    LE_ENP) {
				lereset(unit);
				return;
			}
		} else
			leread(unit, le->sc_r2->ler2_rbuf[bix], len);
		rmd->rmd3 = 0;
		rmd->rmd1 = LE_OWN;
		LENEXTRMP;
	}
	le->sc_rmd = bix;
}

leread(unit, buf, len)
	int unit;
	char *buf;
	int len;
{
	register struct le_softc *le = &le_softc[unit];
	register struct ether_header *et;
    	struct mbuf *m;
D 2
	int off, resid;
E 2
I 2
	int off, resid, flags;
E 2

	le->sc_if.if_ipackets++;
	et = (struct ether_header *)buf;
	et->ether_type = ntohs((u_short)et->ether_type);
	/* adjust input length to account for header and CRC */
	len = len - sizeof(struct ether_header) - 4;

#define	ledataaddr(et, off, type)	((type)(((caddr_t)((et)+1)+(off))))
	if (et->ether_type >= ETHERTYPE_TRAIL &&
	    et->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (et->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU)
			return;		/* sanity */
		et->ether_type = ntohs(*ledataaddr(et, off, u_short *));
		resid = ntohs(*(ledataaddr(et, off+2, u_short *)));
		if (off + resid > len)
			return;		/* sanity */
		len = off + resid;
	} else
		off = 0;

	if (len <= 0) {
		if (ledebug)
			log(LOG_WARNING,
			    "le%d: ierror(runt packet): from %s: len=%d\n",
			    unit, ether_sprintf(et->ether_shost), len);
		le->sc_runt++;
		le->sc_if.if_ierrors++;
		return;
	}
I 2
	flags = 0;
	if (bcmp((caddr_t)etherbroadcastaddr,
	    (caddr_t)et->ether_dhost, sizeof(etherbroadcastaddr)) == 0)
		flags |= M_BCAST;
	if (et->ether_dhost[0] & 1)
		flags |= M_MCAST;

E 2
#if NBPFILTER > 0
	/*
	 * Check if there's a bpf filter listening on this interface.
D 2
	 * If so, hand off the raw packet to bpf, which must deal with
	 * trailers in its own way.
E 2
I 2
	 * If so, hand off the raw packet to enet.
E 2
	 */
D 2
	if (le->sc_bpf)
		bpf_tap(le->sc_bpf, buf, len + sizeof(struct ether_header));
E 2
I 2
	if (le->sc_if.if_bpf) {
		bpf_tap(le->sc_if.if_bpf, buf, len + sizeof(struct ether_header));

		/*
		 * Keep the packet if it's a broadcast or has our
		 * physical ethernet address (or if we support
		 * multicast and it's one).
		 */
		if (
#ifdef MULTICAST
		    (flags & (M_BCAST | M_MCAST)) == 0 &&
#else
		    (flags & M_BCAST) == 0 &&
E 2
#endif
D 2
#if defined(ISO) || NBPFILTER > 0
	/*
	 * Note that the interface cannot be in promiscuous mode if
	 * there are no bpf listeners.  If we are in promiscuous
	 * mode, we have to check if this packet is really ours.
	 * However, there may be appropriate multicate addresses involved
	 */
#define NOT_TO(p) (bcmp(et->ether_dhost, p, sizeof(et->ether_dhost)) != 0)
	if (et->ether_dhost[0] & 1) {
		if (NOT_TO(etherbroadcastaddr) && NOT_TO(hprmp_multi)
#ifdef ISO
		    && NOT_TO(all_es_snpa) && NOT_TO(all_is_snpa)
		    && NOT_TO(all_l1is_snpa) && NOT_TO(all_l2is_snpa)
E 2
I 2
		    bcmp(et->ether_dhost, le->sc_addr,
			sizeof(et->ether_dhost)) != 0)
			return;
	}
E 2
#endif
D 2
		     ) return;
	} else if ((le->sc_if.if_flags & IFF_PROMISC) && NOT_TO(le->sc_addr))
		return;
#endif
E 2
	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; m_devget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	m = m_devget((char *)(et + 1), len, off, &le->sc_if, 0);
I 2
D 5
	m->m_flags |= flags;
E 5
E 2
	if (m == 0)
		return;
I 5
	m->m_flags |= flags;
E 5
	ether_input(&le->sc_if, et, m);
}

/*
 * Routine to copy from mbuf chain to transmit
 * buffer in board local memory.
 */
leput(lebuf, m)
	register char *lebuf;
	register struct mbuf *m;
{
	register struct mbuf *mp;
	register int len, tlen = 0;

	for (mp = m; mp; mp = mp->m_next) {
		len = mp->m_len;
		if (len == 0)
			continue;
		tlen += len;
		bcopy(mtod(mp, char *), lebuf, len);
		lebuf += len;
	}
	m_freem(m);
	if (tlen < LEMINSIZE) {
		bzero(lebuf, LEMINSIZE - tlen);
		tlen = LEMINSIZE;
	}
	return(tlen);
}

/*
 * Process an ioctl request.
 */
leioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	struct le_softc *le = &le_softc[ifp->if_unit];
	struct lereg1 *ler1 = le->sc_r1;
	int s = splimp(), error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			leinit(ifp->if_unit);	/* before arpwhohas */
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef NS
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);

			if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)(le->sc_addr);
			else {
				/* 
				 * The manual says we can't change the address 
				 * while the receiver is armed,
				 * so reset everything
				 */
				ifp->if_flags &= ~IFF_RUNNING; 
				LERDWR(le->sc_r0, LE_STOP, ler1->ler1_rdp);
				bcopy((caddr_t)ina->x_host.c_host,
				    (caddr_t)le->sc_addr, sizeof(le->sc_addr));
			}
			leinit(ifp->if_unit); /* does le_setaddr() */
			break;
		    }
#endif
		default:
			leinit(ifp->if_unit);
			break;
		}
		break;
I 4

#if defined (CCITT) && defined (LLC)
	case SIOCSIFCONF_X25:
		ifp -> if_flags |= IFF_UP;
		ifa -> ifa_rtrequest = cons_rtrequest;
		error = x25_llcglue(PRC_IFUP, ifa -> ifa_addr);
		if (error == 0)
			leinit(ifp -> if_unit);
		break;
#endif /* CCITT && LLC */

E 4

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ifp->if_flags & IFF_RUNNING) {
			LERDWR(le->sc_r0, LE_STOP, ler1->ler1_rdp);
			ifp->if_flags &= ~IFF_RUNNING;
		} else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0)
			leinit(ifp->if_unit);
		/*
		 * If the state of the promiscuous bit changes, the interface
		 * must be reset to effect the change.
		 */
		if (((ifp->if_flags ^ le->sc_iflags) & IFF_PROMISC) &&
		    (ifp->if_flags & IFF_RUNNING)) {
			le->sc_iflags = ifp->if_flags;
			lereset(ifp->if_unit);
			lestart(ifp);
		}
		break;

I 2
#ifdef MULTICAST
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		/* Update our multicast list  */
		error = (cmd == SIOCADDMULTI) ?
		    ether_addmulti((struct ifreq *)data, &le->sc_ac) :
		    ether_delmulti((struct ifreq *)data, &le->sc_ac);

		if (error == ENETRESET) {
			/*
			 * Multicast list has changed; set the hardware
			 * filter accordingly.
			 */
			lereset(ifp->if_unit);
			error = 0;
		}
		break;
#endif
E 2
	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}

leerror(unit, stat)
	int unit;
	int stat;
{
	if (!ledebug)
		return;

	/*
	 * Not all transceivers implement heartbeat
	 * so we only log CERR once.
	 */
	if ((stat & LE_CERR) && le_softc[unit].sc_cerr)
		return;
	log(LOG_WARNING,
	    "le%d: error: stat=%b\n", unit,
	    stat,
	    "\20\20ERR\17BABL\16CERR\15MISS\14MERR\13RINT\12TINT\11IDON\10INTR\07INEA\06RXON\05TXON\04TDMD\03STOP\02STRT\01INIT");
}

lererror(unit, msg)
	int unit;
	char *msg;
{
	register struct le_softc *le = &le_softc[unit];
	register struct lermd *rmd;
	int len;

	if (!ledebug)
		return;

	rmd = &le->sc_r2->ler2_rmd[le->sc_rmd];
	len = rmd->rmd3;
	log(LOG_WARNING,
	    "le%d: ierror(%s): from %s: buf=%d, len=%d, rmd1=%b\n",
	    unit, msg,
	    len > 11 ?
		ether_sprintf((u_char *)&le->sc_r2->ler2_rbuf[le->sc_rmd][6]) :
		"unknown",
	    le->sc_rmd, len,
	    rmd->rmd1,
	    "\20\20OWN\17ERR\16FRAM\15OFLO\14CRC\13RBUF\12STP\11ENP");
}

lexerror(unit)
	int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct letmd *tmd;
	int len;

	if (!ledebug)
		return;

	tmd = le->sc_r2->ler2_tmd;
	len = -tmd->tmd2;
	log(LOG_WARNING,
	    "le%d: oerror: to %s: buf=%d, len=%d, tmd1=%b, tmd3=%b\n",
	    unit,
	    len > 5 ?
		ether_sprintf((u_char *)&le->sc_r2->ler2_tbuf[0][0]) :
		"unknown",
	    0, len,
	    tmd->tmd1,
	    "\20\20OWN\17ERR\16RES\15MORE\14ONE\13DEF\12STP\11ENP",
	    tmd->tmd3,
	    "\20\20BUFF\17UFLO\16RES\15LCOL\14LCAR\13RTRY");
}
#endif
E 1
