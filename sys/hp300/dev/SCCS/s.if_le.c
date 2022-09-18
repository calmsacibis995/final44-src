h52494
s 00002/00001/00893
d D 8.2 95/02/19 07:45:55 cgd 18 17
c fix external declarations to match prototyped return types
e
s 00002/00002/00892
d D 8.1 93/06/10 21:33:14 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00893
d D 7.16 93/03/11 18:00:12 sklower 16 15
c fix from hibler & forys; check for non-null return from m_devget before 
c oring in flags (shame on me!)
e
s 00011/00000/00883
d D 7.15 92/12/28 08:59:58 hibler 15 14
c USELEDS changes
e
s 00019/00001/00864
d D 7.14 92/12/28 08:59:21 hibler 14 13
c for sklower: CCITT changes
e
s 00027/00027/00838
d D 7.13 92/10/11 09:23:57 bostic 13 12
c make kernel includes standard
e
s 00138/00039/00727
d D 7.12 92/07/06 15:30:22 sklower 12 11
c multicast changes from lbl
e
s 00071/00081/00695
d D 7.11 92/06/05 15:31:57 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00016/00078/00760
d D 7.10 92/03/20 18:53:09 sklower 10 9
c use m_devget instead of le_get.  Other minor changes
e
s 00006/00002/00832
d D 7.9 92/02/05 23:34:10 mckusick 9 8
c lint
e
s 00033/00006/00801
d D 7.8 91/08/08 20:13:19 sklower 8 7
c this version has 2 tx buffers; appears to work.
e
s 00035/00086/00772
d D 7.7 91/08/08 17:51:12 sklower 7 6
c put in hacks for ISO, (put it into ALLMULTI mode), take out RMP
e
s 00001/00006/00857
d D 7.6 91/05/08 11:33:46 mccanne 6 5
c changed interface to bpfattach -- bpf_devp is gone
e
s 00001/00001/00862
d D 7.5 91/05/03 16:22:49 mccanne 5 4
c oops, the bpf tap call must happen after the packet is in interface memory
e
s 00011/00000/00852
d D 7.4 91/04/27 15:19:44 mccanne 4 3
c changed promiscuous mode handling per Karels' sugesstion
e
s 00056/00000/00796
d D 7.3 91/03/19 01:08:40 mccanne 3 2
c add bpf hooks
e
s 00024/00024/00772
d D 7.2 90/12/16 16:36:16 bostic 2 1
c kernel reorg
e
s 00796/00000/00000
d D 7.1 90/05/08 22:07:00 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 17
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include "le.h"
#if NLE > 0

I 3
#include "bpfilter.h"

E 3
/*
 * AMD 7990 LANCE
 *
D 12
 * This driver will generate and accept tailer encapsulated packets even
E 12
I 12
 * This driver will accept tailer encapsulated packets even
E 12
 * though it buys us nothing.  The motivation was to avoid incompatibilities
 * with VAXen, SUNs, and others that handle and benefit from them.
 * This reasoning is dubious.
 */
D 2
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "syslog.h"
#include "ioctl.h"
#include "errno.h"
E 2
I 2
D 13
#include "sys/param.h"
I 10
#include "sys/proc.h"
E 10
#include "sys/systm.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/protosw.h"
#include "sys/socket.h"
#include "sys/syslog.h"
#include "sys/ioctl.h"
#include "sys/errno.h"
E 13
I 13
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
E 13
E 2

D 2
#include "../net/if.h"
#include "../net/netisr.h"
#include "../net/route.h"
E 2
I 2
D 13
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 13
I 13
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
E 13
E 2

#ifdef INET
D 2
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
#include "../netinet/in_var.h"
#include "../netinet/ip.h"
#include "../netinet/if_ether.h"
E 2
I 2
D 13
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 13
I 13
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 13
E 2
#endif

#ifdef NS
D 2
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 2
I 2
D 13
#include "netns/ns.h"
#include "netns/ns_if.h"
E 13
I 13
#include <netns/ns.h>
#include <netns/ns_if.h>
E 13
E 2
#endif

I 14
#if defined (CCITT) && defined (LLC)
#include <sys/socketvar.h>
#include <netccitt/x25.h>
D 18
extern llc_ctlinput(), cons_rtrequest();
E 18
I 18
extern int llc_ctlinput();
extern void cons_rtrequest();
E 18
#endif

E 14
D 7
#ifdef RMP
D 2
#include "../netrmp/rmp.h"
#include "../netrmp/rmp_var.h"
E 2
I 2
#include "netrmp/rmp.h"
#include "netrmp/rmp_var.h"
E 7
I 7
D 12
#ifdef ISO
extern	char all_es_snpa[], all_is_snpa[], all_l1is_snpa[], all_l2is_snpa[];
E 7
E 2
#endif

E 12
D 2
#include "machine/cpu.h"
#include "machine/isr.h"
#include "machine/mtpr.h"
E 2
I 2
D 13
#include "../include/cpu.h"
#include "../hp300/isr.h"
#include "../include/mtpr.h"
E 2
D 11
#include "device.h"
E 11
I 11
#include "hp/dev/device.h"
E 11
#include "if_lereg.h"
E 13
I 13
#include <machine/cpu.h>
#include <hp300/hp300/isr.h>
#include <machine/mtpr.h>
#include <hp/dev/device.h>
#include <hp300/dev/if_lereg.h>
I 15
#ifdef USELEDS
#include <hp300/hp300/led.h>
#endif
E 15
E 13

I 3
#if NBPFILTER > 0
D 13
#include "../net/bpf.h"
#include "../net/bpfdesc.h"
E 13
I 13
#include <net/bpf.h>
#include <net/bpfdesc.h>
E 13
I 7
D 12
char hprmp_multi[] = { 9, 0, 9, 0, 0, 4};
E 12
E 7
#endif

E 3
/* offsets for:	   ID,   REGS,    MEM,  NVRAM */
int	lestd[] = { 0, 0x4000, 0x8000, 0xC008 };

int	leattach();
struct	driver ledriver = {
	leattach, "le",
};

struct	isr le_isr[NLE];
int	ledebug = 0;		/* console error messages */

D 14
int	leintr(), leinit(), leioctl(), lestart(), ether_output();
E 14
I 14
int	leintr(), leinit(), leioctl(), lestart(), ether_output(), lereset();
E 14
D 10
struct	mbuf *leget();
E 10
I 10
struct	mbuf *m_devget();
E 10
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
	struct	lereg0 *sc_r0;	/* DIO registers */
	struct	lereg1 *sc_r1;	/* LANCE registers */
	struct	lereg2 *sc_r2;	/* dual-port RAM */
	int	sc_rmd;		/* predicted next rmd to process */
I 11
	int	sc_tmd;		/* next available tmd */
	int	sc_txcnt;	/* # of transmit buffers in use */
	/* stats */
E 11
	int	sc_runt;
	int	sc_jab;
	int	sc_merr;
	int	sc_babl;
	int	sc_cerr;
	int	sc_miss;
D 11
	int	sc_xint;
E 11
I 11
	int	sc_rown;
E 11
	int	sc_xown;
I 11
	int	sc_xown2;
E 11
	int	sc_uflo;
	int	sc_rxlen;
	int	sc_rxoff;
	int	sc_txoff;
	int	sc_busy;
I 4
	short	sc_iflags;
E 4
I 3
D 7
#if NBPFILTER > 0
E 7
D 12
	caddr_t sc_bpf;
E 12
I 8
D 11
	int	sc_tmd;		/* predicted next tmd to process */
	int	sc_txcnt;	/* transmissions in progress */
	int	sc_txbad;
	int	sc_txbusy;
E 11
E 8
D 7
#endif
E 7
E 3
} le_softc[NLE];

/* access LANCE registers */
#define	LERDWR(cntl, src, dst) \
	do { \
		(dst) = (src); \
	} while (((cntl)->ler0_status & LE_ACK) == 0);

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
leattach(hd)
	struct hp_device *hd;
{
	register struct lereg0 *ler0;
	register struct lereg2 *ler2;
	struct lereg2 *lemem = 0;
	struct le_softc *le = &le_softc[hd->hp_unit];
	struct ifnet *ifp = &le->sc_if;
	char *cp;
	int i;

	ler0 = le->sc_r0 = (struct lereg0 *)(lestd[0] + (int)hd->hp_addr);
	le->sc_r1 = (struct lereg1 *)(lestd[1] + (int)hd->hp_addr);
	ler2 = le->sc_r2 = (struct lereg2 *)(lestd[2] + (int)hd->hp_addr);
	if (ler0->ler0_id != LEID)
		return(0);
	le_isr[hd->hp_unit].isr_intr = leintr;
	hd->hp_ipl = le_isr[hd->hp_unit].isr_ipl = LE_IPL(ler0->ler0_status);
	le_isr[hd->hp_unit].isr_arg = hd->hp_unit;
	ler0->ler0_id = 0xFF;
	DELAY(100);

	/*
	 * Read the ethernet address off the board, one nibble at a time.
	 */
	cp = (char *)(lestd[3] + (int)hd->hp_addr);
	for (i = 0; i < sizeof(le->sc_addr); i++) {
		le->sc_addr[i] = (*++cp & 0xF) << 4;
		cp++;
		le->sc_addr[i] |= *++cp & 0xF;
		cp++;
	}
	printf("le%d: hardware address %s\n", hd->hp_unit,
		ether_sprintf(le->sc_addr));

	/*
	 * Setup for transmit/receive
	 */
	ler2->ler2_mode = LE_MODE;
D 7
	ler2->ler2_padr[0] = le->sc_addr[1];
	ler2->ler2_padr[1] = le->sc_addr[0];
	ler2->ler2_padr[2] = le->sc_addr[3];
	ler2->ler2_padr[3] = le->sc_addr[2];
	ler2->ler2_padr[4] = le->sc_addr[5];
	ler2->ler2_padr[5] = le->sc_addr[4];
#ifdef RMP
	/*
	 * Set up logical addr filter to accept multicast 9:0:9:0:0:4
	 * This should be an ioctl() to the driver.  (XXX)
	 */
	ler2->ler2_ladrf0 = 0x00100000;
	ler2->ler2_ladrf1 = 0x0;
E 7
I 7
D 12
#if defined(ISO) || NBPFILTER > 0
	ler2->ler2_ladrf0 = 0xffffffff;
	ler2->ler2_ladrf1 = 0xffffffff;
E 7
#else
	ler2->ler2_ladrf0 = 0;
	ler2->ler2_ladrf1 = 0;
#endif
E 12
I 12
	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
E 12
	ler2->ler2_rlen = LE_RLEN;
	ler2->ler2_rdra = (int)lemem->ler2_rmd;
	ler2->ler2_tlen = LE_TLEN;
	ler2->ler2_tdra = (int)lemem->ler2_tmd;
	isrlink(&le_isr[hd->hp_unit]);
	ler0->ler0_status = LE_IE;

	ifp->if_unit = hd->hp_unit;
	ifp->if_name = "le";
	ifp->if_mtu = ETHERMTU;
	ifp->if_init = leinit;
I 14
	ifp->if_reset = lereset;
E 14
	ifp->if_ioctl = leioctl;
	ifp->if_output = ether_output;
	ifp->if_start = lestart;
I 12
#ifdef MULTICAST
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
#else
E 12
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX;
I 12
#endif
E 12
I 3
#if NBPFILTER > 0
D 6
	{
		static struct bpf_devp dev =
			{ DLT_EN10MB, sizeof(struct ether_header) };

		bpfattach(&le->sc_bpf, ifp, &dev);
        }
E 6
I 6
D 12
	bpfattach(&le->sc_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 12
I 12
	bpfattach(&ifp->if_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 12
E 6
#endif
E 3
	if_attach(ifp);
	return (1);
}

I 12
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

E 12
D 7
ledrinit(ler2)
E 7
I 7
ledrinit(ler2, le)
E 7
	register struct lereg2 *ler2;
I 7
	register struct le_softc *le;
E 7
{
	register struct lereg2 *lemem = 0;
	register int i;

I 7
	ler2->ler2_padr[0] = le->sc_addr[1];
	ler2->ler2_padr[1] = le->sc_addr[0];
	ler2->ler2_padr[2] = le->sc_addr[3];
	ler2->ler2_padr[3] = le->sc_addr[2];
	ler2->ler2_padr[4] = le->sc_addr[5];
	ler2->ler2_padr[5] = le->sc_addr[4];
E 7
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
I 12
	/* Setup the logical address filter */
#ifdef MULTICAST
	lesetladrf(le);
#else
	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
#endif
E 12
}

lereset(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct lereg0 *ler0 = le->sc_r0;
	register struct lereg1 *ler1 = le->sc_r1;
	register struct lereg2 *lemem = 0;
	register int timo = 100000;
	register int stat;

#ifdef lint
	stat = unit;
#endif
I 3
#if NBPFILTER > 0
	if (le->sc_if.if_flags & IFF_PROMISC)
		/* set the promiscuous bit */
		le->sc_r2->ler2_mode = LE_MODE|0x8000;
	else
		le->sc_r2->ler2_mode = LE_MODE;
#endif
E 3
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_STOP, ler1->ler1_rdp);
D 7
	ledrinit(le->sc_r2);
E 7
I 7
	ledrinit(le->sc_r2, le);
E 7
D 8
	le->sc_rmd = 0;
E 8
I 8
D 11
	le->sc_txcnt = le->sc_tmd = le->sc_rmd = 0;
E 11
I 11
	le->sc_rmd = le->sc_tmd = 0;
E 11
E 8
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
I 11
	le->sc_txcnt = 0;
E 11
}

/*
 * Initialization of interface
 */
leinit(unit)
	int unit;
{
D 10
	struct le_softc *le = &le_softc[unit];
	register struct ifnet *ifp = &le->sc_if;
E 10
I 10
	register struct ifnet *ifp = &le_softc[unit].sc_if;
	register struct ifaddr *ifa;
E 10
	int s;

	/* not yet, if address still unknown */
D 10
	if (ifp->if_addrlist == (struct ifaddr *)0)
		return;
E 10
I 10
	for (ifa = ifp->if_addrlist;; ifa = ifa->ifa_next)
		if (ifa == 0)
			return;
		else if (ifa->ifa_addr && ifa->ifa_addr->sa_family != AF_LINK)
			break;
E 10
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

I 8
D 11
again:
E 11
E 8
	if ((le->sc_if.if_flags & IFF_RUNNING) == 0)
		return (0);
D 11
	IF_DEQUEUE(&le->sc_if.if_snd, m);
	if (m == 0)
		return (0);
I 5
D 8
	len = leput(le->sc_r2->ler2_tbuf[0], m);
E 8
I 8
	tmd = le->sc_r2->ler2_tmd + le->sc_tmd;
	if (tmd->tmd1 & LE_OWN)
		return (le->sc_txbusy++, 0);
	len = leput(le->sc_r2->ler2_tbuf[le->sc_tmd], m);
E 11
I 11
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
E 11
E 8
E 5
I 3
#if NBPFILTER > 0
D 11
	/*
	 * If bpf is listening on this interface, let it
	 * see the packet before we commit it to the wire.
	 */
	if (le->sc_bpf)
D 8
                bpf_tap(le->sc_bpf, le->sc_r2->ler2_tbuf[0], len);
E 8
I 8
                bpf_tap(le->sc_bpf, le->sc_r2->ler2_tbuf[le->sc_tmd], len);
E 11
I 11
		/* 
		 * If bpf is listening on this interface, let it 
		 * see the packet before we commit it to the wire.
		 */
D 12
		if (le->sc_bpf)
			bpf_tap(le->sc_bpf, le->sc_r2->ler2_tbuf[le->sc_tmd],
E 12
I 12
		if (ifp->if_bpf)
			bpf_tap(ifp->if_bpf, le->sc_r2->ler2_tbuf[le->sc_tmd],
E 12
				len);
E 11
E 8
#endif
E 3
D 5
	len = leput(le->sc_r2->ler2_tbuf[0], m);
E 5
D 8
	tmd = le->sc_r2->ler2_tmd;
E 8
D 11
	tmd->tmd3 = 0;
	tmd->tmd2 = -len;
D 10
	tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
E 10
D 8
	le->sc_if.if_flags |= IFF_OACTIVE;
E 8
I 8
	if (++le->sc_tmd >= LETBUF)
		le->sc_tmd = 0;
	if (++le->sc_txcnt >= LETBUF) {
		le->sc_txcnt = LETBUF;
		le->sc_if.if_flags |= IFF_OACTIVE;
E 11
I 11

		tmd->tmd3 = 0;
		tmd->tmd2 = -len;
E 11
D 10
	} else
E 10
I 10
		tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
D 11
	} else {
		tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
E 10
		goto again;
I 10
	}
E 11
I 11
		if (++le->sc_tmd == LETBUF) {
			le->sc_tmd = 0;
			tmd = le->sc_r2->ler2_tmd;
		} else
			tmd++;
	} while (++le->sc_txcnt < LETBUF);
	le->sc_if.if_flags |= IFF_OACTIVE;
E 11
E 10
E 8
	return (0);
}

leintr(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register struct lereg0 *ler0 = le->sc_r0;
	register struct lereg1 *ler1;
	register int stat;

	if ((ler0->ler0_status & LE_IR) == 0)
		return(0);
	if (ler0->ler0_status & LE_JAB) {
		le->sc_jab++;
		lereset(unit);
		return(1);
	}
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
D 11
	if (stat & LE_RINT) {
		/* interrupt is cleared in lerint */
E 11
I 11
	if (stat & LE_RINT)
E 11
		lerint(unit);
D 11
	}
	if (stat & LE_TINT) {
		LERDWR(ler0, LE_TINT|LE_INEA, ler1->ler1_rdp);
E 11
I 11
	if (stat & LE_TINT)
E 11
		lexint(unit);
D 11
	}
E 11
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
D 8
	register struct letmd *tmd = le->sc_r2->ler2_tmd;
E 8
I 8
	register struct letmd *tmd;
D 11
	int i, loopcount = 0;
E 11
I 11
	int i, gotone = 0;
E 11
E 8

I 15
#ifdef USELEDS
	if (inledcontrol == 0)
		ledcontrol(0, 0, LED_LANXMT);
#endif
E 15
D 10
	if ((le->sc_if.if_flags & IFF_OACTIVE) == 0) {
E 10
I 10
D 11
	if (le->sc_txcnt == 0) {
E 10
		le->sc_xint++;
		return;
	}
I 8
again:
	if ((i = le->sc_tmd - le->sc_txcnt) < 0) i += LETBUF;
	tmd = le->sc_r2->ler2_tmd + i;
E 8
	if (tmd->tmd1 & LE_OWN) {
I 8
		if (loopcount)
			goto out;
E 8
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
E 11
I 11
	do {
		if ((i = le->sc_tmd - le->sc_txcnt) < 0)
			i += LETBUF;
		tmd = &le->sc_r2->ler2_tmd[i];
		if (tmd->tmd1 & LE_OWN) {
			if (gotone)
				break;
			le->sc_xown++;
			return;
E 11
		}
D 11
		else if (tmd->tmd3 & LE_LCOL)
			le->sc_if.if_collisions++;
		else if (tmd->tmd3 & LE_RTRY)
			le->sc_if.if_collisions += 16;
	}
	else if (tmd->tmd3 & LE_TBUFF)
E 11
I 11

		/* clear interrupt */
		LERDWR(le->sc_r0, LE_TINT|LE_INEA, le->sc_r1->ler1_rdp);

E 11
		/* XXX documentation says BUFF not included in ERR */
D 11
		goto err;
	else if (tmd->tmd1 & LE_ONE)
		le->sc_if.if_collisions++;
	else if (tmd->tmd1 & LE_MORE)
		/* what is the real number? */
		le->sc_if.if_collisions += 2;
	else
		le->sc_if.if_opackets++;
I 8
	loopcount++;
	if (--le->sc_txcnt > 0)
		goto again;
	if (le->sc_txcnt < 0) {
		le->sc_txbad++;
		le->sc_txcnt = 0;
	}
out:
E 11
I 11
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
E 11
E 8
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

I 15
#ifdef USELEDS
	if (inledcontrol == 0)
		ledcontrol(0, 0, LED_LANRCV);
#endif
E 15
	/*
	 * Out of sync with hardware, should never happen?
	 */
	if (rmd->rmd1 & LE_OWN) {
I 11
		le->sc_rown++;
E 11
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
D 12
	int off, resid;
E 12
I 12
	int off, resid, flags;
E 12

	le->sc_if.if_ipackets++;
	et = (struct ether_header *)buf;
	et->ether_type = ntohs((u_short)et->ether_type);
	/* adjust input length to account for header and CRC */
	len = len - sizeof(struct ether_header) - 4;

D 7
#ifdef RMP
	/*  (XXX)
	 *
	 *  If Ethernet Type field is < MaxPacketSize, we probably have
	 *  a IEEE802 packet here.  Make sure that the size is at least
	 *  that of the HP LLC.  Also do sanity checks on length of LLC
	 *  (old Ethernet Type field) and packet length.
	 *
	 *  Provided the above checks succeed, change `len' to reflect
	 *  the length of the LLC (i.e. et->ether_type) and change the
	 *  type field to ETHERTYPE_IEEE so we can switch() on it later.
	 *  Yes, this is a hack and will eventually be done "right".
	 */
	if (et->ether_type <= IEEE802LEN_MAX && len >= sizeof(struct hp_llc) &&
	    len >= et->ether_type && len >= IEEE802LEN_MIN) {
		len = et->ether_type;
		et->ether_type = ETHERTYPE_IEEE;	/* hack! */
	}
#endif

E 7
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
I 12
	flags = 0;
	if (bcmp((caddr_t)etherbroadcastaddr,
	    (caddr_t)et->ether_dhost, sizeof(etherbroadcastaddr)) == 0)
		flags |= M_BCAST;
	if (et->ether_dhost[0] & 1)
		flags |= M_MCAST;

E 12
I 3
#if NBPFILTER > 0
	/*
	 * Check if there's a bpf filter listening on this interface.
D 12
	 * If so, hand off the raw packet to bpf, which must deal with
	 * trailers in its own way.
E 12
I 12
	 * If so, hand off the raw packet to enet.
E 12
	 */
D 7
	if (le->sc_bpf) {
E 7
I 7
D 12
	if (le->sc_bpf)
E 7
		bpf_tap(le->sc_bpf, buf, len + sizeof(struct ether_header));
E 12
I 12
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
E 12
E 3
D 7

I 3
		/*
		 * Note that the interface cannot be in promiscuous mode if
		 * there are no bpf listeners.  And if we are in promiscuous
		 * mode, we have to check if this packet is really ours.
		 *
		 * XXX This test does not support multicasts.
		 */
		if ((le->sc_if.if_flags & IFF_PROMISC)
		    && bcmp(et->ether_dhost, le->sc_addr, 
			    sizeof(et->ether_dhost)) != 0
		    && bcmp(et->ether_dhost, etherbroadcastaddr, 
			    sizeof(et->ether_dhost)) != 0)
			return;
	}
E 7
#endif
I 7
D 12
#if defined(ISO) || NBPFILTER > 0
E 7
E 3
	/*
I 7
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
E 12
I 12
		    bcmp(et->ether_dhost, le->sc_addr,
			sizeof(et->ether_dhost)) != 0)
			return;
	}
E 12
#endif
D 12
		     ) return;
	} else if ((le->sc_if.if_flags & IFF_PROMISC) && NOT_TO(le->sc_addr))
		return;
#endif
E 12
	/*
E 7
	 * Pull packet off interface.  Off is nonzero if packet
D 10
	 * has trailing header; leget will then force this header
E 10
I 10
	 * has trailing header; m_devget will then force this header
E 10
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
D 10
	m = leget(buf, len, off, &le->sc_if);
E 10
I 10
	m = m_devget((char *)(et + 1), len, off, &le->sc_if, 0);
I 12
D 16
	m->m_flags |= flags;
E 16
E 12
E 10
	if (m == 0)
		return;
I 16
	m->m_flags |= flags;
E 16
D 7
#ifdef RMP
	/*
	 * (XXX)
	 * This needs to be integrated with the ISO stuff in ether_input()
	 */
	if (et->ether_type == ETHERTYPE_IEEE) {
		/*
		 *  Snag the Logical Link Control header (IEEE 802.2).
		 */
		struct hp_llc *llc = &(mtod(m, struct rmp_packet *)->hp_llc);

		/*
		 *  If the DSAP (and HP's extended DXSAP) indicate this
		 *  is an RMP packet, hand it to the raw input routine.
		 */
		if (llc->dsap == IEEE_DSAP_HP && llc->dxsap == HPEXT_DXSAP) {
			static struct sockproto rmp_sp = {AF_RMP,RMPPROTO_BOOT};
			static struct sockaddr rmp_src = {AF_RMP};
			static struct sockaddr rmp_dst = {AF_RMP};

			bcopy(et->ether_shost, rmp_src.sa_data,
			      sizeof(et->ether_shost));
			bcopy(et->ether_dhost, rmp_dst.sa_data,
			      sizeof(et->ether_dhost));

			raw_input(m, &rmp_sp, &rmp_src, &rmp_dst);
			return;
		}
	}
#endif
E 7
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
D 10
}

/*
 * Routine to copy from board local memory into mbufs.
 */
struct mbuf *
leget(lebuf, totlen, off0, ifp)
	char *lebuf;
	int totlen, off0;
	struct ifnet *ifp;
{
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	register int off = off0, len;
	register char *cp;
	char *epkt;

	lebuf += sizeof (struct ether_header);
	cp = lebuf;
	epkt = cp + totlen;
	if (off) {
		cp += off + 2 * sizeof(u_short);
		totlen -= 2 * sizeof(u_short);
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
		len = min(totlen, epkt - cp);
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
		bcopy(cp, mtod(m, caddr_t), (unsigned)len);
		cp += len;
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		if (cp == epkt)
			cp = lebuf;
	}
	return (top);
E 10
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
I 7
				LERDWR(le->sc_r0, LE_STOP, ler1->ler1_rdp);
E 7
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
I 14

#if defined (CCITT) && defined (LLC)
	case SIOCSIFCONF_X25:
		ifp -> if_flags |= IFF_UP;
		ifa -> ifa_rtrequest = cons_rtrequest;
		error = x25_llcglue(PRC_IFUP, ifa -> ifa_addr);
		if (error == 0)
			leinit(ifp -> if_unit);
		break;
#endif /* CCITT && LLC */

E 14

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ifp->if_flags & IFF_RUNNING) {
			LERDWR(le->sc_r0, LE_STOP, ler1->ler1_rdp);
			ifp->if_flags &= ~IFF_RUNNING;
		} else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0)
			leinit(ifp->if_unit);
I 4
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
E 4
		break;

I 12
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
E 12
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
D 9
	    len > 11 ? ether_sprintf(&le->sc_r2->ler2_rbuf[le->sc_rmd][6]) : "unknown",
E 9
I 9
	    len > 11 ?
		ether_sprintf((u_char *)&le->sc_r2->ler2_rbuf[le->sc_rmd][6]) :
		"unknown",
E 9
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
D 9
	    len > 5 ? ether_sprintf(&le->sc_r2->ler2_tbuf[0][0]) : "unknown",
E 9
I 9
	    len > 5 ?
		ether_sprintf((u_char *)&le->sc_r2->ler2_tbuf[0][0]) :
		"unknown",
E 9
	    0, len,
	    tmd->tmd1,
	    "\20\20OWN\17ERR\16RES\15MORE\14ONE\13DEF\12STP\11ENP",
	    tmd->tmd3,
	    "\20\20BUFF\17UFLO\16RES\15LCOL\14LCAR\13RTRY");
}
#endif
E 1
