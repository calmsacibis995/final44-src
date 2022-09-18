h47921
s 00002/00005/01289
d D 8.4 94/10/09 21:07:14 mckusick 17 16
c Bug fix for diskless operation (from NetBSD via Ralph)
e
s 00002/00002/01292
d D 8.3 94/07/03 14:46:08 mckusick 16 15
c turn off debug error messages (from Ralph)
e
s 00001/00001/01293
d D 8.2 93/11/16 12:31:08 bostic 15 14
c Here is a bugfix for the Lance chip driver for the DECstation 2100/3100.
c The fix is specific to the original DECstations (not the 5000's) and results
c in persistent TCP checksum errors when a TCP connection's window size
c adjusts such that the start offset is on a byte boundary. The problem
c is that "from" is a signed char and sign extended over the high order
c bits of the short.
c From: rmacklem@herman.cs.uoguelph.ca (Richard A Macklem)
e
s 00002/00002/01292
d D 8.1 93/06/29 15:09:17 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00023/01277
d D 7.12 93/06/29 15:07:28 mckusick 13 11
c fix bp_filter stuff
e
s 00002/00002/01298
d R 8.1 93/06/10 22:38:41 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00008/01280
d D 7.11 93/05/29 22:31:28 ralph 11 10
c fix code for MULTICAST
e
s 00171/00160/01117
d D 7.10 93/05/09 17:37:28 ralph 10 9
c update bpf stuff from hp300/dev/if_le.c
e
s 00006/00006/01271
d D 7.9 92/12/20 11:36:37 ralph 9 8
c changes from Rick Macklem
e
s 00555/00296/00722
d D 7.8 92/11/15 15:49:04 ralph 8 7
c changes for maxine from Rick Macklem.
e
s 00002/00002/01016
d D 7.7 92/10/11 11:24:38 bostic 7 6
c use pmax as top directory, not mips
e
s 00026/00026/00992
d D 7.6 92/10/11 11:13:30 bostic 6 5
c make kernel includes standard
e
s 00001/00001/01017
d D 7.5 92/07/27 21:18:33 ralph 5 4
c use min not MIN()
e
s 00032/00008/00986
d D 7.4 92/06/20 12:12:48 ralph 4 3
c fix error printing
e
s 00001/00001/00993
d D 7.3 92/03/29 20:37:41 ralph 3 2
c fix printf
e
s 00092/00019/00902
d D 7.2 92/02/29 11:04:38 ralph 2 1
c added support for DS5000
e
s 00921/00000/00000
d D 7.1 92/01/07 18:29:20 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 8
/*
 * Copyright (c) 1992 Regents of the University of California.
E 8
I 8
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
E 8
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Ralph Campbell.
E 8
I 8
 * Ralph Campbell and Rick Macklem.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 8
#include "le.h"
E 8
I 8
#include <le.h>
E 8
#if NLE > 0

D 8
#include "bpfilter.h"
E 8
I 8
#include <bpfilter.h>
E 8

/*
 * AMD 7990 LANCE
 *
 * This driver will generate and accept trailer encapsulated packets even
 * though it buys us nothing.  The motivation was to avoid incompatibilities
 * with VAXen, SUNs, and others that handle and benefit from them.
 * This reasoning is dubious.
 */
D 6
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "syslog.h"
#include "ioctl.h"
#include "errno.h"
E 6
I 6
#include <sys/param.h>
I 10
#include <sys/proc.h>
E 10
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/syslog.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
E 6

D 6
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 6
I 6
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
E 6

#ifdef INET
D 6
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 6
I 6
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 6
#endif

#ifdef NS
D 6
#include "netns/ns.h"
#include "netns/ns_if.h"
E 6
I 6
#include <netns/ns.h>
#include <netns/ns_if.h>
E 6
#endif

D 10
#ifdef RMP
D 6
#include "netrmp/rmp.h"
#include "netrmp/rmp_var.h"
E 6
I 6
#include <netrmp/rmp.h>
#include <netrmp/rmp_var.h>
E 10
I 10
#if defined (CCITT) && defined (LLC)
#include <sys/socketvar.h>
#include <netccitt/x25.h>
extern llc_ctlinput(), cons_rtrequest();
E 10
E 6
#endif

D 6
#include "machine/machConst.h"
#include "device.h"
#include "if_lereg.h"
E 6
I 6
#include <machine/machConst.h>
I 8

#include <pmax/pmax/pmaxtype.h>
#include <pmax/pmax/kn01.h>
#include <pmax/pmax/kmin.h>
#include <pmax/pmax/asic.h>

E 8
D 7
#include <mips/dev/device.h>
#include <mips/dev/if_lereg.h>
E 7
I 7
#include <pmax/dev/device.h>
#include <pmax/dev/if_lereg.h>
E 7
E 6

#if NBPFILTER > 0
D 6
#include "../net/bpf.h"
#include "../net/bpfdesc.h"
E 6
I 6
#include <net/bpf.h>
#include <net/bpfdesc.h>
E 6
#endif

int	leprobe();
I 2
void	leintr();
E 2
struct	driver ledriver = {
D 2
	"le", leprobe,
E 2
I 2
	"le", leprobe, 0, 0, leintr,
E 2
};

D 16
int	ledebug = 1;		/* console error messages */
E 16
I 16
int	ledebug = 0;		/* console error messages */
E 16

D 2
int	leintr(), leinit(), leioctl(), lestart(), ether_output();
struct	mbuf *leget();

E 2
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
	volatile struct	lereg1 *sc_r1;	/* LANCE registers */
D 8
	volatile struct	lereg2 *sc_r2;	/* dual-port RAM */
E 8
I 8
	volatile void *sc_r2;	/* dual-port RAM */
	int	sc_ler2pad;	/* Do ring descriptors require short pads? */
	void	(*sc_copytobuf)(); /* Copy to buffer */
	void	(*sc_copyfrombuf)(); /* Copy from buffer */
	void	(*sc_zerobuf)(); /* and Zero bytes in buffer */
E 8
	int	sc_rmd;		/* predicted next rmd to process */
	int	sc_tmd;		/* last tmd processed */
	int	sc_tmdnext;	/* next tmd to transmit with */
I 10
	/* stats */
E 10
	int	sc_runt;
D 10
	int	sc_jab;
E 10
	int	sc_merr;
	int	sc_babl;
	int	sc_cerr;
	int	sc_miss;
I 10
	int	sc_rown;
E 10
	int	sc_xint;
D 10
	int	sc_xown;
E 10
	int	sc_uflo;
	int	sc_rxlen;
	int	sc_rxoff;
	int	sc_txoff;
	int	sc_busy;
	short	sc_iflags;
D 10
#if NBPFILTER > 0
	caddr_t sc_bpf;
#endif
E 10
} le_softc[NLE];

I 2
D 8
#ifdef DS3100
E 8
E 2
/* access LANCE registers */
I 8
static void lewritereg();
E 8
#define	LERDWR(cntl, src, dst)	{ (dst) = (src); DELAY(10); }
I 8
#define	LEWREG(src, dst)	lewritereg(&(dst), (src))
E 8

#define CPU_TO_CHIP_ADDR(cpu) \
D 8
	(((unsigned)(&(((struct lereg2 *)0)->cpu))) >> 1)
I 2
#endif
E 2

I 2
#ifdef DS5000
/* access LANCE registers */
#define	LERDWR(cntl, src, dst)	(dst) = (src);

#define CPU_TO_CHIP_ADDR(cpu) \
E 8
	((unsigned)(&(((struct lereg2 *)0)->cpu)))

#define LE_OFFSET_RAM		0x0
#define LE_OFFSET_LANCE		0x100000
#define LE_OFFSET_ROM		0x1c0000
D 8
#endif
E 8

I 8
void copytobuf_contig(), copyfrombuf_contig(), bzerobuf_contig();
void copytobuf_gap2(), copyfrombuf_gap2(), bzerobuf_gap2();
void copytobuf_gap16(), copyfrombuf_gap16(), bzerobuf_gap16();

extern int pmax_boardtype;
extern u_long le_iomem;
I 9
extern u_long asic_base;
E 9

E 8
E 2
/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 * If interface exists, make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
leprobe(dp)
	struct pmax_ctlr *dp;
{
	volatile struct lereg1 *ler1;
	struct le_softc *le = &le_softc[dp->pmax_unit];
	struct ifnet *ifp = &le->sc_if;
	u_char *cp;
	int i;
I 2
D 10
	extern int leinit(), leioctl(), lestart(), ether_output();
E 10
I 10
	extern int leinit(), lereset(), leioctl(), lestart(), ether_output();
E 10
E 2

I 2
D 8
#ifdef DS3100
E 2
	le->sc_r1 = ler1 = (volatile struct lereg1 *)dp->pmax_addr;
	le->sc_r2 = (volatile struct lereg2 *)MACH_NETWORK_BUFFER_ADDR;
E 8
I 8
	switch (pmax_boardtype) {
	case DS_PMAX:
		le->sc_r1 = ler1 = (volatile struct lereg1 *)dp->pmax_addr;
		le->sc_r2 = (volatile void *)MACH_PHYS_TO_UNCACHED(0x19000000);
		cp = (u_char *)(MACH_PHYS_TO_UNCACHED(KN01_SYS_CLOCK) + 1);
		le->sc_ler2pad = 1;
		le->sc_copytobuf = copytobuf_gap2;
		le->sc_copyfrombuf = copyfrombuf_gap2;
		le->sc_zerobuf = bzerobuf_gap2;
		break;
	case DS_3MIN:
	case DS_MAXINE:
I 9
	case DS_3MAXPLUS:
E 9
		if (dp->pmax_unit == 0) {
			volatile u_int *ssr, *ldp;
E 8

D 8
	/*
	 * Read the ethernet address.
	 * See "DECstation 3100 Desktop Workstation Functional Specification".
	 */
	cp = (u_char *)(MACH_CLOCK_ADDR + 1);
	for (i = 0; i < sizeof(le->sc_addr); i++) {
		le->sc_addr[i] = *cp;
		cp += 4;
	}
I 2
#endif
#ifdef DS5000
	le->sc_r1 = ler1 = (volatile struct lereg1 *)
		(dp->pmax_addr + LE_OFFSET_LANCE);
	le->sc_r2 = (volatile struct lereg2 *)(dp->pmax_addr + LE_OFFSET_RAM);
E 8
I 8
			le->sc_r1 = ler1 = (volatile struct lereg1 *)
D 9
				MACH_PHYS_TO_UNCACHED(KMIN_SYS_LANCE);
E 9
I 9
				ASIC_SYS_LANCE(asic_base);
			cp = (u_char *)ASIC_SYS_ETHER_ADDRESS(asic_base);
E 9
			le->sc_r2 = (volatile void *)
				MACH_PHYS_TO_UNCACHED(le_iomem);
D 9
			cp = (u_char *)MACH_PHYS_TO_UNCACHED(
				KMIN_SYS_ETHER_ADDRESS);
E 9
			le->sc_ler2pad = 1;
			le->sc_copytobuf = copytobuf_gap16;
			le->sc_copyfrombuf = copyfrombuf_gap16;
			le->sc_zerobuf = bzerobuf_gap16;
E 8
E 2

I 8
			/*
			 * And enable Lance dma through the asic.
			 */
D 9
			ssr = (volatile u_int *)
				MACH_PHYS_TO_UNCACHED(KMIN_REG_CSR);
E 9
I 9
			ssr = (volatile u_int *)ASIC_REG_CSR(asic_base);
E 9
			ldp = (volatile u_int *)
D 9
				MACH_PHYS_TO_UNCACHED(KMIN_REG_LANCE_DMAPTR);
E 9
I 9
				ASIC_REG_LANCE_DMAPTR(asic_base);
E 9
			*ldp = (le_iomem << 3);	/* phys addr << 3 */
			*ssr |= ASIC_CSR_DMAEN_LANCE;
			break;
		}
		/*
		 * Units other than 0 are turbochannel option boards and fall
		 * through to DS_3MAX.
		 */
	case DS_3MAX:
		le->sc_r1 = ler1 = (volatile struct lereg1 *)
			(dp->pmax_addr + LE_OFFSET_LANCE);
		le->sc_r2 = (volatile void *)(dp->pmax_addr + LE_OFFSET_RAM);
		cp = (u_char *)(dp->pmax_addr + LE_OFFSET_ROM + 2);
		le->sc_ler2pad = 0;
		le->sc_copytobuf = copytobuf_contig;
		le->sc_copyfrombuf = copyfrombuf_contig;
		le->sc_zerobuf = bzerobuf_contig;
		break;
	default:
		printf("Unknown CPU board type %d\n", pmax_boardtype);
		return (0);
	};

E 8
I 2
	/*
D 8
	 * Read the ethernet address.
E 8
I 8
	 * Get the ethernet address out of rom
E 8
	 */
D 8
	cp = (u_char *)(dp->pmax_addr + LE_OFFSET_ROM + 2);
E 8
	for (i = 0; i < sizeof(le->sc_addr); i++) {
		le->sc_addr[i] = *cp;
		cp += 4;
	}
D 8
#endif
E 8

E 2
	/* make sure the chip is stopped */
D 8
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_STOP, ler1->ler1_rdp);
E 8
I 8
	LEWREG(LE_CSR0, ler1->ler1_rap);
	LEWREG(LE_STOP, ler1->ler1_rdp);
E 8

	ifp->if_unit = dp->pmax_unit;
	ifp->if_name = "le";
	ifp->if_mtu = ETHERMTU;
	ifp->if_init = leinit;
I 10
	ifp->if_reset = lereset;
E 10
	ifp->if_ioctl = leioctl;
	ifp->if_output = ether_output;
	ifp->if_start = lestart;
I 10
#ifdef MULTICAST
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
#else
E 10
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX;
I 10
#endif
E 10
#if NBPFILTER > 0
D 10
	bpfattach(&le->sc_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 10
I 10
	bpfattach(&ifp->if_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 10
#endif
	if_attach(ifp);

D 2
	printf("le%d at nexus0 csr 0x%x ethernet address %s\n", dp->pmax_unit,
		dp->pmax_addr, ether_sprintf(le->sc_addr));
E 2
I 2
	printf("le%d at nexus0 csr 0x%x priority %d ethernet address %s\n",
		dp->pmax_unit, dp->pmax_addr, dp->pmax_pri,
		ether_sprintf(le->sc_addr));
E 2
	return (1);
}

I 10
#ifdef MULTICAST
/*
 * Setup the logical address filter
 */
void
D 11
lesetladrf(sc)
	register struct le_softc *sc;
E 11
I 11
lesetladrf(le)
	register struct le_softc *le;
E 11
{
D 11
	register volatile struct lereg2 *ler2 = sc->sc_r2;
	register struct ifnet *ifp = &sc->sc_if;
E 11
I 11
	register volatile struct lereg2 *ler2 = le->sc_r2;
	register struct ifnet *ifp = &le->sc_if;
E 11
	register struct ether_multi *enm;
	register u_char *cp;
	register u_long crc;
	register u_long c;
	register int i, len;
	struct ether_multistep step;

	/*
	 * Set up multicast address filter by passing all multicast
	 * addresses through a crc generator, and then using the high
D 16
	 * order 6 bits as a index into the 64 bit logical address
E 16
I 16
	 * order 6 bits as an index into the 64 bit logical address
E 16
	 * filter. The high order two bits select the word, while the
	 * rest of the bits select the bit within the word.
	 */

D 11
	ler2->ler2_ladrf[0] = 0;
	ler2->ler2_ladrf[1] = 0;
E 11
I 11
	LER2_ladrf0(ler2, 0);
	LER2_ladrf1(ler2, 0);
E 11
	ifp->if_flags &= ~IFF_ALLMULTI;
D 11
	ETHER_FIRST_MULTI(step, &sc->sc_ac, enm);
E 11
I 11
	ETHER_FIRST_MULTI(step, &le->sc_ac, enm);
E 11
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
			LER2_ladrf0(ler2, 0xff);
			LER2_ladrf1(ler2, 0xff);
			LER2_ladrf2(ler2, 0xff);
			LER2_ladrf3(ler2, 0xff);
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
D 11
		ler2->ler2_ladrf[crc >> 5] |= 1 << (crc & 0x1f);
E 11
I 11
		switch (crc >> 5) {
		case 0:
			LER2_ladrf0(ler2, 1 << (crc & 0x1f));
			break;
		case 1:
			LER2_ladrf1(ler2, 1 << (crc & 0x1f));
			break;
		case 2:
			LER2_ladrf2(ler2, 1 << (crc & 0x1f));
			break;
		case 3:
			LER2_ladrf3(ler2, 1 << (crc & 0x1f));
		}
E 11

		ETHER_NEXT_MULTI(step, enm);
	}
}
#endif

E 10
D 8
ledrinit(ler2)
	register volatile struct lereg2 *ler2;
E 8
I 8
ledrinit(le)
	struct le_softc *le;
E 8
{
I 8
	register volatile void *rp;
E 8
	register int i;

	for (i = 0; i < LERBUF; i++) {
D 8
		ler2->ler2_rmd[i].rmd0 = CPU_TO_CHIP_ADDR(ler2_rbuf[i][0]);
		ler2->ler2_rmd[i].rmd1 = LE_OWN;
		ler2->ler2_rmd[i].rmd2 = -LEMTU;
		ler2->ler2_rmd[i].rmd3 = 0;
E 8
I 8
		rp = LER2_RMDADDR(le->sc_r2, i);
		LER2_rmd0(rp, CPU_TO_CHIP_ADDR(ler2_rbuf[i][0]));
		LER2_rmd1(rp, LE_OWN);
		LER2_rmd2(rp, -LEMTU);
		LER2_rmd3(rp, 0);
E 8
	}
	for (i = 0; i < LETBUF; i++) {
D 8
		ler2->ler2_tmd[i].tmd0 = CPU_TO_CHIP_ADDR(ler2_tbuf[i][0]);
		ler2->ler2_tmd[i].tmd1 = 0;
		ler2->ler2_tmd[i].tmd2 = 0;
		ler2->ler2_tmd[i].tmd3 = 0;
E 8
I 8
		rp = LER2_TMDADDR(le->sc_r2, i);
		LER2_tmd0(rp, CPU_TO_CHIP_ADDR(ler2_tbuf[i][0]));
		LER2_tmd1(rp, 0);
		LER2_tmd2(rp, 0);
		LER2_tmd3(rp, 0);
E 8
	}
}

lereset(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register volatile struct lereg1 *ler1 = le->sc_r1;
D 8
	register volatile struct lereg2 *ler2 = le->sc_r2;
E 8
I 8
	register volatile void *ler2 = le->sc_r2;
E 8
	register int timo = 100000;
	register int stat;

#ifdef lint
	stat = unit;
#endif
I 8
	LEWREG(LE_CSR0, ler1->ler1_rap);
	LEWREG(LE_STOP, ler1->ler1_rdp);

	/*
	 * Setup for transmit/receive
	 */
E 8
#if NBPFILTER > 0
	if (le->sc_if.if_flags & IFF_PROMISC)
		/* set the promiscuous bit */
D 8
		le->sc_r2->ler2_mode = LE_MODE|0x8000;
E 8
I 8
D 10
		LER2_mode(ler2, LE_MODE|0x8000);
E 10
I 10
		LER2_mode(ler2, LE_MODE | 0x8000);
E 10
E 8
	else
D 8
		le->sc_r2->ler2_mode = LE_MODE;
E 8
#endif
D 8
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
	LERDWR(ler0, LE_STOP, ler1->ler1_rdp);

	/*
	 * Setup for transmit/receive
	 */
	ler2->ler2_mode = LE_MODE;
	ler2->ler2_padr0 = (le->sc_addr[1] << 8) | le->sc_addr[0];
	ler2->ler2_padr1 = (le->sc_addr[3] << 8) | le->sc_addr[2];
	ler2->ler2_padr2 = (le->sc_addr[5] << 8) | le->sc_addr[4];
E 8
I 8
		LER2_mode(ler2, LE_MODE);
	LER2_padr0(ler2, (le->sc_addr[1] << 8) | le->sc_addr[0]);
	LER2_padr1(ler2, (le->sc_addr[3] << 8) | le->sc_addr[2]);
	LER2_padr2(ler2, (le->sc_addr[5] << 8) | le->sc_addr[4]);
E 8
D 10
#ifdef RMP
	/*
	 * Set up logical addr filter to accept multicast 9:0:9:0:0:4
	 * This should be an ioctl() to the driver.  (XXX)
	 */
D 8
	ler2->ler2_ladrf0 = 0x0010;
	ler2->ler2_ladrf1 = 0x0;
	ler2->ler2_ladrf2 = 0x0;
	ler2->ler2_ladrf3 = 0x0;
E 8
I 8
	LER2_ladrf0(ler2, 0x0010);
	LER2_ladrf1(ler2, 0x0);
	LER2_ladrf2(ler2, 0x0);
	LER2_ladrf3(ler2, 0x0);
E 10
I 10
	/* Setup the logical address filter */
#ifdef MULTICAST
	lesetladrf(le);
E 10
E 8
#else
D 8
	ler2->ler2_ladrf0 = 0;
	ler2->ler2_ladrf1 = 0;
	ler2->ler2_ladrf2 = 0;
	ler2->ler2_ladrf3 = 0;
E 8
I 8
	LER2_ladrf0(ler2, 0);
	LER2_ladrf1(ler2, 0);
	LER2_ladrf2(ler2, 0);
	LER2_ladrf3(ler2, 0);
E 8
#endif
D 8
	ler2->ler2_rlen = LE_RLEN;
	ler2->ler2_rdra = CPU_TO_CHIP_ADDR(ler2_rmd[0]);
	ler2->ler2_tlen = LE_TLEN;
	ler2->ler2_tdra = CPU_TO_CHIP_ADDR(ler2_tmd[0]);
	ledrinit(ler2);
E 8
I 8
	LER2_rlen(ler2, LE_RLEN);
	LER2_rdra(ler2, CPU_TO_CHIP_ADDR(ler2_rmd[0]));
	LER2_tlen(ler2, LE_TLEN);
	LER2_tdra(ler2, CPU_TO_CHIP_ADDR(ler2_tmd[0]));
	ledrinit(le);
E 8
	le->sc_rmd = 0;
	le->sc_tmd = LETBUF - 1;
	le->sc_tmdnext = 0;

D 8
	LERDWR(ler0, LE_CSR1, ler1->ler1_rap);
	LERDWR(ler0, CPU_TO_CHIP_ADDR(ler2_mode), ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR2, ler1->ler1_rap);
	LERDWR(ler0, 0, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR3, ler1->ler1_rap);
	LERDWR(ler0, 0, ler1->ler1_rdp);
	LERDWR(ler0, LE_CSR0, ler1->ler1_rap);
E 8
I 8
	LEWREG(LE_CSR1, ler1->ler1_rap);
	LEWREG(CPU_TO_CHIP_ADDR(ler2_mode), ler1->ler1_rdp);
	LEWREG(LE_CSR2, ler1->ler1_rap);
	LEWREG(0, ler1->ler1_rdp);
	LEWREG(LE_CSR3, ler1->ler1_rap);
	LEWREG(0, ler1->ler1_rdp);
	LEWREG(LE_CSR0, ler1->ler1_rap);
E 8
	LERDWR(ler0, LE_INIT, ler1->ler1_rdp);
D 8
	MachEmptyWriteBuffer();
E 8
	do {
		if (--timo == 0) {
			printf("le%d: init timeout, stat = 0x%x\n",
			       unit, stat);
			break;
		}
D 8
		LERDWR(ler0, ler1->ler1_rdp, stat);
E 8
I 8
		stat = ler1->ler1_rdp;
E 8
	} while ((stat & LE_IDON) == 0);
	LERDWR(ler0, LE_IDON, ler1->ler1_rdp);
	LERDWR(ler0, LE_STRT | LE_INEA, ler1->ler1_rdp);
D 8
	MachEmptyWriteBuffer();
E 8
	le->sc_if.if_flags &= ~IFF_OACTIVE;
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
D 17
	for (ifa = ifp->if_addrlist;; ifa = ifa->ifa_next)
		if (ifa == 0)
			return;
		else if (ifa->ifa_addr && ifa->ifa_addr->sa_family != AF_LINK)
			break;
E 17
I 17
	if (ifp->if_addrlist == NULL)
		return;
E 17
E 10
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		s = splnet();
		ifp->if_flags |= IFF_RUNNING;
		lereset(unit);
	        (void) lestart(ifp);
		splx(s);
	}
}

#define	LENEXTTMP \
D 8
	if (++bix == LETBUF) bix = 0, tmd = le->sc_r2->ler2_tmd; else ++tmd
E 8
I 8
	if (++bix == LETBUF) \
		bix = 0; \
	tmd = LER2_TMDADDR(le->sc_r2, bix)
E 8

/*
 * Start output on interface.  Get another datagram to send
 * off of the interface queue, and copy it to the interface
 * before starting the output.
 */
lestart(ifp)
	struct ifnet *ifp;
{
	register struct le_softc *le = &le_softc[ifp->if_unit];
	register int bix = le->sc_tmdnext;
D 8
	register volatile struct letmd *tmd = &le->sc_r2->ler2_tmd[bix];
E 8
I 8
	register volatile void *tmd = LER2_TMDADDR(le->sc_r2, bix);
E 8
	register struct mbuf *m;
	int len = 0;

	if ((le->sc_if.if_flags & IFF_RUNNING) == 0)
		return (0);
	while (bix != le->sc_tmd) {
D 8
		if (tmd->tmd1 & LE_OWN)
E 8
I 8
		if (LER2V_tmd1(tmd) & LE_OWN)
E 8
			panic("lestart");
		IF_DEQUEUE(&le->sc_if.if_snd, m);
		if (m == 0)
			break;
I 10
D 13
		len = leput(le, LER2_TBUFADDR(le->sc_r2, bix), m);
E 13
E 10
D 8
		len = leput(le->sc_r2->ler2_tbuf[bix], m);
E 8
#if NBPFILTER > 0
		/*
		 * If bpf is listening on this interface, let it
		 * see the packet before we commit it to the wire.
		 */
D 10
		if (le->sc_bpf)
D 8
			bpf_tap(le->sc_bpf, le->sc_r2->ler2_tbuf[bix], len);
E 8
I 8
			bpf_mtap(le->sc_bpf, m);
E 10
I 10
		if (ifp->if_bpf)
D 13
			bpf_tap(ifp->if_bpf,
				LER2_TBUFADDR(le->sc_r2, le->sc_tmd), len);
E 13
I 13
			bpf_mtap(ifp->if_bpf, m);
E 13
E 10
E 8
#endif
I 13
		len = leput(le, LER2_TBUFADDR(le->sc_r2, bix), m);
E 13
D 8
		tmd->tmd3 = 0;
		tmd->tmd2 = -len;
		tmd->tmd1 = LE_OWN | LE_STP | LE_ENP;
E 8
I 8
D 10
		len = leput(le, LER2_TBUFADDR(le->sc_r2, bix), m);
E 10
		LER2_tmd3(tmd, 0);
		LER2_tmd2(tmd, -len);
		LER2_tmd1(tmd, LE_OWN | LE_STP | LE_ENP);
E 8
		LENEXTTMP;
	}
	if (len != 0) {
		le->sc_if.if_flags |= IFF_OACTIVE;
		LERDWR(ler0, LE_TDMD | LE_INEA, le->sc_r1->ler1_rdp);
D 8
		MachEmptyWriteBuffer();
E 8
	}
	le->sc_tmdnext = bix;
	return (0);
}

/*
 * Process interrupts from the 7990 chip.
 */
D 2
leintr()
E 2
I 2
void
leintr(unit)
	int unit;
E 2
{
	register struct le_softc *le;
	register volatile struct lereg1 *ler1;
D 2
	register int unit, stat;
E 2
I 2
	register int stat;
E 2

D 2
	/* only one unit right now; should be a loop. */
	unit = 0;
E 2
	le = &le_softc[unit];
	ler1 = le->sc_r1;
	stat = ler1->ler1_rdp;
	if (!(stat & LE_INTR)) {
D 3
		printf("le?: spurrious interrupt\n");
E 3
I 3
		printf("le%d: spurrious interrupt\n", unit);
E 3
		return;
	}
	if (stat & LE_SERR) {
		leerror(unit, stat);
		if (stat & LE_MERR) {
			le->sc_merr++;
			lereset(unit);
			return;
		}
		if (stat & LE_BABL)
			le->sc_babl++;
		if (stat & LE_CERR)
			le->sc_cerr++;
		if (stat & LE_MISS)
			le->sc_miss++;
		LERDWR(ler0, LE_BABL|LE_CERR|LE_MISS|LE_INEA, ler1->ler1_rdp);
D 8
		MachEmptyWriteBuffer();
E 8
	}
	if ((stat & LE_RXON) == 0) {
		le->sc_rxoff++;
		lereset(unit);
		return;
	}
	if ((stat & LE_TXON) == 0) {
		le->sc_txoff++;
		lereset(unit);
		return;
	}
	if (stat & LE_RINT) {
		/* interrupt is cleared in lerint */
		lerint(unit);
	}
	if (stat & LE_TINT) {
		LERDWR(ler0, LE_TINT|LE_INEA, ler1->ler1_rdp);
D 8
		MachEmptyWriteBuffer();
E 8
		lexint(unit);
	}
}

/*
 * Ethernet interface transmitter interrupt.
 * Start another output if more data to send.
 */
lexint(unit)
	register int unit;
{
	register struct le_softc *le = &le_softc[unit];
	register int bix = le->sc_tmd;
D 8
	register volatile struct letmd *tmd = &le->sc_r2->ler2_tmd[bix];
E 8
I 8
	register volatile void *tmd;
E 8

	if ((le->sc_if.if_flags & IFF_OACTIVE) == 0) {
		le->sc_xint++;
		return;
	}
	LENEXTTMP;
D 8
	while (bix != le->sc_tmdnext && (tmd->tmd1 & LE_OWN) == 0) {
E 8
I 8
	while (bix != le->sc_tmdnext && (LER2V_tmd1(tmd) & LE_OWN) == 0) {
E 8
		le->sc_tmd = bix;
D 8
		if ((tmd->tmd1 & LE_ERR) || (tmd->tmd3 & LE_TBUFF)) {
E 8
I 8
		if ((LER2V_tmd1(tmd) & LE_ERR) || (LER2V_tmd3(tmd) & LE_TBUFF)) {
E 8
			lexerror(unit);
			le->sc_if.if_oerrors++;
D 8
			if (tmd->tmd3 & (LE_TBUFF|LE_UFLO)) {
E 8
I 8
			if (LER2V_tmd3(tmd) & (LE_TBUFF|LE_UFLO)) {
E 8
				le->sc_uflo++;
				lereset(unit);
				break;
			}
D 8
			else if (tmd->tmd3 & LE_LCOL)
E 8
I 8
			else if (LER2V_tmd3(tmd) & LE_LCOL)
E 8
				le->sc_if.if_collisions++;
D 8
			else if (tmd->tmd3 & LE_RTRY)
E 8
I 8
			else if (LER2V_tmd3(tmd) & LE_RTRY)
E 8
				le->sc_if.if_collisions += 16;
		}
D 8
		else if (tmd->tmd1 & LE_ONE)
E 8
I 8
		else if (LER2V_tmd1(tmd) & LE_ONE)
E 8
			le->sc_if.if_collisions++;
D 8
		else if (tmd->tmd1 & LE_MORE)
E 8
I 8
		else if (LER2V_tmd1(tmd) & LE_MORE)
E 8
			/* what is the real number? */
			le->sc_if.if_collisions += 2;
		else
			le->sc_if.if_opackets++;
		LENEXTTMP;
	}
	if (bix == le->sc_tmdnext)
		le->sc_if.if_flags &= ~IFF_OACTIVE;
	(void) lestart(&le->sc_if);
}

#define	LENEXTRMP \
D 8
	if (++bix == LERBUF) bix = 0, rmd = le->sc_r2->ler2_rmd; else ++rmd
E 8
I 8
	if (++bix == LERBUF) \
		bix = 0; \
	rmd = LER2_RMDADDR(le->sc_r2, bix)
E 8

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
D 8
	register volatile struct lermd *rmd = &le->sc_r2->ler2_rmd[bix];
E 8
I 8
	register volatile void *rmd = LER2_RMDADDR(le->sc_r2, bix);
E 8

	/*
	 * Out of sync with hardware, should never happen?
	 */
D 8
	if (rmd->rmd1 & LE_OWN) {
E 8
I 8
	if (LER2V_rmd1(rmd) & LE_OWN) {
I 10
		le->sc_rown++;
E 10
E 8
		LERDWR(le->sc_r0, LE_RINT|LE_INEA, le->sc_r1->ler1_rdp);
D 8
		MachEmptyWriteBuffer();
E 8
		return;
	}

	/*
	 * Process all buffers with valid data
	 */
D 8
	while ((rmd->rmd1 & LE_OWN) == 0) {
		int len = rmd->rmd3;
E 8
I 8
	while ((LER2V_rmd1(rmd) & LE_OWN) == 0) {
		int len = LER2V_rmd3(rmd);
E 8

		/* Clear interrupt to avoid race condition */
		LERDWR(le->sc_r0, LE_RINT|LE_INEA, le->sc_r1->ler1_rdp);
D 8
		MachEmptyWriteBuffer();
E 8

D 8
		if (rmd->rmd1 & LE_ERR) {
E 8
I 8
		if (LER2V_rmd1(rmd) & LE_ERR) {
E 8
			le->sc_rmd = bix;
			lererror(unit, "bad packet");
			le->sc_if.if_ierrors++;
D 8
		} else if ((rmd->rmd1 & (LE_STP|LE_ENP)) != (LE_STP|LE_ENP)) {
E 8
I 8
		} else if ((LER2V_rmd1(rmd) & (LE_STP|LE_ENP)) != (LE_STP|LE_ENP)) {
E 8
			/*
			 * Find the end of the packet so we can see how long
			 * it was.  We still throw it away.
			 */
			do {
				LERDWR(le->sc_r0, LE_RINT|LE_INEA,
				       le->sc_r1->ler1_rdp);
D 8
				MachEmptyWriteBuffer();
				rmd->rmd3 = 0;
				rmd->rmd1 = LE_OWN;
E 8
I 8
				LER2_rmd3(rmd, 0);
				LER2_rmd1(rmd, LE_OWN);
E 8
				LENEXTRMP;
D 8
			} while (!(rmd->rmd1 & (LE_OWN|LE_ERR|LE_STP|LE_ENP)));
E 8
I 8
			} while (!(LER2V_rmd1(rmd) & (LE_OWN|LE_ERR|LE_STP|LE_ENP)));
E 8
			le->sc_rmd = bix;
			lererror(unit, "chained buffer");
			le->sc_rxlen++;
			/*
			 * If search terminated without successful completion
			 * we reset the hardware (conservative).
			 */
D 8
			if ((rmd->rmd1 & (LE_OWN|LE_ERR|LE_STP|LE_ENP)) !=
E 8
I 8
			if ((LER2V_rmd1(rmd) & (LE_OWN|LE_ERR|LE_STP|LE_ENP)) !=
E 8
			    LE_ENP) {
				lereset(unit);
				return;
			}
		} else
D 8
			leread(unit, le->sc_r2->ler2_rbuf[bix], len);
		rmd->rmd3 = 0;
		rmd->rmd1 = LE_OWN;
E 8
I 8
			leread(unit, LER2_RBUFADDR(le->sc_r2, bix), len);
		LER2_rmd3(rmd, 0);
		LER2_rmd1(rmd, LE_OWN);
E 8
		LENEXTRMP;
	}
	MachEmptyWriteBuffer();		/* Paranoia */
	le->sc_rmd = bix;
}

/*
 * Look at the packet in network buffer memory so we can be smart about how
 * we copy the data into mbufs.
 * This needs work since we can't just read network buffer memory like
 * regular memory.
 */
leread(unit, buf, len)
	int unit;
D 2
	volatile u_short *buf;
E 2
I 2
D 8
	le_buf_t *buf;
E 8
I 8
	volatile void *buf;
E 8
E 2
	int len;
{
	register struct le_softc *le = &le_softc[unit];
	struct ether_header et;
D 8
    	struct mbuf *m;
E 8
I 8
D 13
    	struct mbuf *m, **hdrmp, **tailmp;
E 13
I 13
    	struct mbuf *m;
E 13
E 8
D 10
	int off, resid;
E 10
I 10
	int off, resid, flags;
E 10
I 2
D 8
#ifdef DS3100
E 2
	u_short sbuf[2];
I 2
#endif
E 8
I 8
	u_short sbuf[2], eth_type;
E 8
	extern struct mbuf *leget();
E 2

	le->sc_if.if_ipackets++;
I 2
D 8
#ifdef DS3100
E 2
	CopyFromBuffer(buf, (char *)&et, sizeof(et));
I 2
#endif
#ifdef DS5000
	bcopy(buf, (char *)&et, sizeof(et));
#endif
E 2
	et.ether_type = ntohs(et.ether_type);
E 8
I 8
	(*le->sc_copyfrombuf)(buf, 0, (char *)&et, sizeof (et));
	eth_type = ntohs(et.ether_type);
E 8
	/* adjust input length to account for header and CRC */
	len = len - sizeof(struct ether_header) - 4;

D 10
#ifdef RMP
	/*  (XXX)
	 *
	 *  If Ethernet Type field is < MaxPacketSize, we probably have
	 *  a IEEE802 packet here.  Make sure that the size is at least
	 *  that of the HP LLC.  Also do sanity checks on length of LLC
	 *  (old Ethernet Type field) and packet length.
	 *
	 *  Provided the above checks succeed, change `len' to reflect
	 *  the length of the LLC (i.e. et.ether_type) and change the
	 *  type field to ETHERTYPE_IEEE so we can switch() on it later.
	 *  Yes, this is a hack and will eventually be done "right".
	 */
D 8
	if (et.ether_type <= IEEE802LEN_MAX && len >= sizeof(struct hp_llc) &&
	    len >= et.ether_type && len >= IEEE802LEN_MIN) {
		len = et.ether_type;
		et.ether_type = ETHERTYPE_IEEE;	/* hack! */
E 8
I 8
	if (eth_type <= IEEE802LEN_MAX && len >= sizeof(struct hp_llc) &&
	    len >= eth_type && len >= IEEE802LEN_MIN) {
		len = eth_type;
		eth_type = ETHERTYPE_IEEE;	/* hack! */
E 8
	}
#endif

E 10
D 8
	if (et.ether_type >= ETHERTYPE_TRAIL &&
	    et.ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (et.ether_type - ETHERTYPE_TRAIL) * 512;
E 8
I 8
	if (eth_type >= ETHERTYPE_TRAIL &&
	    eth_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eth_type - ETHERTYPE_TRAIL) * 512;
E 8
		if (off >= ETHERMTU)
			return;		/* sanity */
I 2
D 8
#ifdef DS3100
E 2
		CopyFromBuffer(buf + (sizeof(et) + off),
			(char *)sbuf, sizeof(sbuf));
		et.ether_type = ntohs(sbuf[0]);
E 8
I 8
		(*le->sc_copyfrombuf)(buf, sizeof (et) + off, (char *)sbuf,
			sizeof (sbuf));
		eth_type = ntohs(sbuf[0]);
E 8
		resid = ntohs(sbuf[1]);
I 2
D 8
#endif
#ifdef DS5000
D 4
		et.ether_type = ntohs((u_short *)(buf + (sizeof(et) + off))[0]);
		resid = ntohs((u_short *)(buf + (sizeof(et) + off))[1]);
E 4
I 4
		et.ether_type = ntohs(((u_short *)(buf + (sizeof(et) + off)))[0]);
		resid = ntohs(((u_short *)(buf + (sizeof(et) + off)))[1]);
E 4
#endif
E 8
E 2
		if (off + resid > len)
			return;		/* sanity */
		len = off + resid;
	} else
		off = 0;

	if (len <= 0) {
		if (ledebug)
			log(LOG_WARNING,
			    "le%d: ierror(runt packet): from %s: len=%d\n",
			    unit, ether_sprintf(et.ether_shost), len);
		le->sc_runt++;
		le->sc_if.if_ierrors++;
		return;
	}
I 10
	flags = 0;
	if (bcmp((caddr_t)etherbroadcastaddr,
	    (caddr_t)et.ether_dhost, sizeof(etherbroadcastaddr)) == 0)
		flags |= M_BCAST;
	if (et.ether_dhost[0] & 1)
		flags |= M_MCAST;
E 10
D 8
#if NBPFILTER > 0
	/*
	 * Check if there's a bpf filter listening on this interface.
	 * If so, hand off the raw packet to bpf, which must deal with
	 * trailers in its own way.
	 */
	if (le->sc_bpf) {
		bpf_tap(le->sc_bpf, buf, len + sizeof(struct ether_header));
E 8

I 13
	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; leget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	m = leget(le, buf, len, off, &le->sc_if);
	if (m == 0)
		return;
E 13
I 10
#if NBPFILTER > 0
E 10
D 8
		/*
		 * Note that the interface cannot be in promiscuous mode if
		 * there are no bpf listeners.  And if we are in promiscuous
		 * mode, we have to check if this packet is really ours.
		 *
		 * XXX This test does not support multicasts.
		 */
		if ((le->sc_if.if_flags & IFF_PROMISC)
		    && bcmp(et.ether_dhost, le->sc_addr, 
			    sizeof(et.ether_dhost)) != 0
		    && bcmp(et.ether_dhost, etherbroadcastaddr, 
			    sizeof(et.ether_dhost)) != 0)
			return;
	}
#endif
E 8
	/*
I 10
	 * Check if there's a bpf filter listening on this interface.
	 * If so, hand off the raw packet to enet.
	 */
	if (le->sc_if.if_bpf) {
D 13
		bpf_tap(le->sc_if.if_bpf, buf, len + sizeof(struct ether_header));
E 13
I 13
		bpf_mtap(le->sc_if.if_bpf, m);
E 13

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
#endif
		    bcmp(et.ether_dhost, le->sc_addr,
D 13
			sizeof(et.ether_dhost)) != 0)
E 13
I 13
			sizeof(et.ether_dhost)) != 0) {
			m_freem(m);
E 13
			return;
I 13
		}
E 13
	}
#endif
D 13

	/*
E 10
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; leget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
I 8
	 * The hdrmp and tailmp pointers are used by lebpf_tap() to
	 * temporarily reorder the mbuf list. See the comment at the beginning
	 * of lebpf_tap() for all the ugly details.
E 8
	 */
D 8
	m = leget(buf, len, off, &le->sc_if);
E 8
I 8
	m = leget(le, buf, len, off, &le->sc_if, &hdrmp, &tailmp);
E 8
	if (m == 0)
		return;
E 13
I 8
D 10
#if NBPFILTER > 0
	if (le->sc_bpf)
		if (lebpf_tap(le, m, hdrmp, tailmp, off, &et, sbuf))
			return;
#endif
E 8
#ifdef RMP
	/*
	 * (XXX)
	 * This needs to be integrated with the ISO stuff in ether_input()
	 */
D 8
	if (et.ether_type == ETHERTYPE_IEEE) {
E 8
I 8
	if (eth_type == ETHERTYPE_IEEE) {
E 8
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

			bcopy(et.ether_shost, rmp_src.sa_data,
			      sizeof(et.ether_shost));
			bcopy(et.ether_dhost, rmp_dst.sa_data,
			      sizeof(et.ether_dhost));

			raw_input(m, &rmp_sp, &rmp_src, &rmp_dst);
			return;
		}
	}
#endif
E 10
I 10
	m->m_flags |= flags;
E 10
I 8
	et.ether_type = eth_type;
E 8
	ether_input(&le->sc_if, &et, m);
}

/*
 * Routine to copy from mbuf chain to transmit buffer in
 * network buffer memory.
D 2
 * NOTE: network memory can only be written one short at every other address.
E 2
I 2
D 8
 * NOTE: On the DS3100, network memory can only be written one short at
 *	every other address.
E 8
E 2
 */
D 8
leput(lebuf, m)
D 2
	volatile register u_short *lebuf;
E 2
I 2
	register le_buf_t *lebuf;
E 8
I 8
leput(le, lebuf, m)
	struct le_softc *le;
	register volatile void *lebuf;
E 8
E 2
	register struct mbuf *m;
{
	register struct mbuf *mp;
D 2
	register int len, tlen = 0, xfer;
E 2
I 2
	register int len, tlen = 0;
D 8
#ifdef DS3100
E 2
	register char *cp;
D 2
	int tmp;
E 2
I 2
	int tmp, xfer;
#endif
E 8
I 8
	register int boff = 0;
E 8
E 2

	for (mp = m; mp; mp = mp->m_next) {
		len = mp->m_len;
		if (len == 0)
			continue;
I 2
D 8
#ifdef DS3100
E 2
		/* copy data for this mbuf */
		cp = mtod(mp, char *);
		if (tlen & 1) {
			/* handle odd length from previous mbuf */
			*lebuf = (cp[0] << 8) | tmp;
			lebuf += 2;
			cp++;
			len--;
			tlen++;
		}
E 8
I 8
		(*le->sc_copytobuf)(mtod(mp, char *), lebuf, boff, len);
E 8
		tlen += len;
D 8
		if ((unsigned)cp & 1) {
			while (len > 1) {
				*lebuf = (cp[1] << 8) | cp[0];
				lebuf += 2;
				cp += 2;
				len -= 2;
			}
		} else {
			/* optimize for aligned transfers */
			xfer = (int)((unsigned)len & ~0x1);
			CopyToBuffer((u_short *)cp, lebuf, xfer);
			lebuf += xfer;
			cp += xfer;
			len -= xfer;
		}
		if (len == 1)
			tmp = *cp;
I 2
#endif
#ifdef DS5000
		tlen += len;
		bcopy(mtod(mp, char *), lebuf, len);
		lebuf += len;
#endif
E 8
I 8
		boff += len;
E 8
E 2
	}
	m_freem(m);
I 2
D 8
#ifdef DS3100
E 2
	/* handle odd length from previous mbuf */
	if (tlen & 1)
		*lebuf = tmp;
D 2
	if (tlen < LEMINSIZE)
E 2
I 2
#endif
E 8
	if (tlen < LEMINSIZE) {
D 8
#ifdef DS3100
		tlen = (tlen + 1) & ~1;
		while (tlen < LEMINSIZE) {
			*lebuf++ = 0;
			tlen += 2;
		}
#endif
#ifdef DS5000
		bzero(lebuf, LEMINSIZE - tlen);
#endif
E 8
I 8
		(*le->sc_zerobuf)(lebuf, boff, LEMINSIZE - tlen);
E 8
E 2
		tlen = LEMINSIZE;
I 2
	}
E 2
	return(tlen);
}

/*
 * Routine to copy from network buffer memory into mbufs.
D 2
 * NOTE: network memory can only be read one short at every other address.
E 2
I 2
D 8
 * NOTE: On the DS3100, network memory can only be written one short at
 *	every other address.
E 8
E 2
 */
struct mbuf *
D 8
leget(lebuf, totlen, off, ifp)
D 2
	volatile u_short *lebuf;
E 2
I 2
	le_buf_t *lebuf;
E 8
I 8
D 13
leget(le, lebuf, totlen, off, ifp, hdrmp, tailmp)
E 13
I 13
leget(le, lebuf, totlen, off, ifp)
E 13
	struct le_softc *le;
	volatile void *lebuf;
E 8
E 2
	int totlen, off;
	struct ifnet *ifp;
I 8
D 13
	struct mbuf ***hdrmp, ***tailmp;
E 13
E 8
{
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
D 8
	register int len, resid;
D 2
	register volatile u_short *sp;
E 2
I 2
	register le_buf_t *sp;
E 8
I 8
	register int len, resid, boff;
E 8
E 2

	/* NOTE: sizeof(struct ether_header) should be even */
D 8
	lebuf += sizeof(struct ether_header);
	sp = lebuf;
E 8
I 8
	boff = sizeof(struct ether_header);
E 8
	if (off) {
		/* NOTE: off should be even */
D 8
		sp += off + 2 * sizeof(u_short);
E 8
I 8
		boff += off + 2 * sizeof(u_short);
E 8
		totlen -= 2 * sizeof(u_short);
		resid = totlen - off;
	} else
		resid = totlen;

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

		if (resid >= MINCLSIZE)
			MCLGET(m, M_DONTWAIT);
		if (m->m_flags & M_EXT)
D 5
			m->m_len = MIN(resid, MCLBYTES);
E 5
I 5
			m->m_len = min(resid, MCLBYTES);
E 5
		else if (resid < m->m_len) {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (top == 0 && resid + max_linkhdr <= m->m_len)
				m->m_data += max_linkhdr;
			m->m_len = resid;
		}
		len = m->m_len;
I 2
D 8
#ifdef DS3100
E 2
		if ((unsigned)sp & 2) {
			/*
			 * Previous len was odd. Copy the single byte specially.
			 * XXX Can this ever happen??
			 */
			panic("le odd rcv");
			*mtod(m, char *) = ((volatile char *)sp)[-1];
			CopyFromBuffer(sp + 1, mtod(m, char *) + 1, len - 1);
		} else
			CopyFromBuffer(sp, mtod(m, char *), len);
I 2
#endif
#ifdef DS5000
		bcopy(sp, mtod(m, char *), len);
#endif
E 2
		sp += len;
E 8
I 8
		(*le->sc_copyfrombuf)(lebuf, boff, mtod(m, char *), len);
		boff += len;
E 8
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		resid -= len;
		if (resid == 0) {
D 8
			sp = lebuf;
E 8
I 8
			boff = sizeof (struct ether_header);
E 8
			resid = totlen;
I 8
D 13
			*hdrmp = mp;
E 13
E 8
		}
	}
I 8
D 13
	*tailmp = mp;
E 13
E 8
	return (top);
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
	volatile struct lereg1 *ler1 = le->sc_r1;
	int s, error = 0;

	s = splnet();
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
I 10
				LEWREG(LE_STOP, ler1->ler1_rdp);
E 10
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

I 10
#if defined (CCITT) && defined (LLC)
	case SIOCSIFCONF_X25:
		ifp->if_flags |= IFF_UP;
		ifa->ifa_rtrequest = cons_rtrequest;
		error = x25_llcglue(PRC_IFUP, ifa->ifa_addr);
		if (error == 0)
			leinit(ifp->if_unit);
		break;
#endif /* CCITT && LLC */

E 10
	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ifp->if_flags & IFF_RUNNING) {
D 8
			LERDWR(le->sc_r0, LE_STOP, ler1->ler1_rdp);
			MachEmptyWriteBuffer();
E 8
I 8
			LEWREG(LE_STOP, ler1->ler1_rdp);
E 8
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

I 10
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

E 10
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
D 8
	register volatile struct lermd *rmd;
E 8
I 8
	register volatile void *rmd;
E 8
I 4
	u_char eaddr[6];
D 8
	char *cp;
E 8
E 4
	int len;

	if (!ledebug)
		return;

D 8
	rmd = &le->sc_r2->ler2_rmd[le->sc_rmd];
	len = rmd->rmd3;
I 4
	if (len > 11) {
#ifdef DS3100
		CopyFromBuffer((char *)&le->sc_r2->ler2_rbuf[le->sc_rmd][6],
			eaddr, sizeof(eaddr));
#endif
#ifdef DS5000
		bcopy((char *)&le->sc_r2->ler2_rbuf[le->sc_rmd][6],
			eaddr, sizeof(eaddr));
#endif
		cp = ether_sprintf(eaddr);
	} else
		cp = "unknown";
E 8
I 8
	rmd = LER2_RMDADDR(le->sc_r2, le->sc_rmd);
	len = LER2V_rmd3(rmd);
	if (len > 11)
		(*le->sc_copyfrombuf)(LER2_RBUFADDR(le->sc_r2, le->sc_rmd),
			6, eaddr, 6);
E 8
E 4
	log(LOG_WARNING,
	    "le%d: ierror(%s): from %s: buf=%d, len=%d, rmd1=%b\n",
D 4
	    unit, msg,
	    len > 11 ? ether_sprintf(&le->sc_r2->ler2_rbuf[le->sc_rmd][6]) : "unknown",
	    le->sc_rmd, len,
E 4
I 4
D 8
	    unit, msg, cp, le->sc_rmd, len,
E 4
	    rmd->rmd1,
E 8
I 8
	    unit, msg,
	    len > 11 ? ether_sprintf(eaddr) : "unknown",
	    le->sc_rmd, len,
	    LER2V_rmd1(rmd),
E 8
	    "\20\20OWN\17ERR\16FRAM\15OFLO\14CRC\13RBUF\12STP\11ENP");
}

lexerror(unit)
	int unit;
{
	register struct le_softc *le = &le_softc[unit];
D 8
	register volatile struct letmd *tmd;
E 8
I 8
	register volatile void *tmd;
E 8
I 4
	u_char eaddr[6];
D 8
	char *cp;
E 8
E 4
	int len;

	if (!ledebug)
		return;

D 8
	tmd = le->sc_r2->ler2_tmd;
	len = -tmd->tmd2;
I 4
	if (len > 5) {
#ifdef DS3100
		CopyFromBuffer((char *)&le->sc_r2->ler2_tbuf[le->sc_tmd][0],
			eaddr, sizeof(eaddr));
#endif
#ifdef DS5000
		bcopy((char *)&le->sc_r2->ler2_tbuf[le->sc_tmd][0],
			eaddr, sizeof(eaddr));
#endif
		cp = ether_sprintf(eaddr);
	} else
		cp = "unknown";
E 8
I 8
	tmd = LER2_TMDADDR(le->sc_r2, 0);
	len = -LER2V_tmd2(tmd);
	if (len > 5)
		(*le->sc_copyfrombuf)(LER2_TBUFADDR(le->sc_r2, 0), 0, eaddr, 6);
E 8
E 4
	log(LOG_WARNING,
	    "le%d: oerror: to %s: buf=%d, len=%d, tmd1=%b, tmd3=%b\n",
D 4
	    unit,
	    len > 5 ? ether_sprintf(&le->sc_r2->ler2_tbuf[0][0]) : "unknown",
	    0, len,
E 4
I 4
D 8
	    unit, cp, le->sc_tmd, len,
E 4
	    tmd->tmd1,
E 8
I 8
	    unit,
	    len > 5 ? ether_sprintf(eaddr) : "unknown",
	    0, len,
	    LER2V_tmd1(tmd),
E 8
	    "\20\20OWN\17ERR\16RES\15MORE\14ONE\13DEF\12STP\11ENP",
D 8
	    tmd->tmd3,
E 8
I 8
	    LER2V_tmd3(tmd),
E 8
	    "\20\20BUFF\17UFLO\16RES\15LCOL\14LCAR\13RTRY");
}
D 8
#endif
E 8
I 8

/*
 * Write a lance register port, reading it back to ensure success. This seems
 * to be necessary during initialization, since the chip appears to be a bit
 * pokey sometimes.
 */
static void
lewritereg(regptr, val)
	register volatile u_short *regptr;
	register u_short val;
{
	register int i = 0;

	while (*regptr != val) {
		*regptr = val;
		MachEmptyWriteBuffer();
		if (++i > 10000) {
			printf("le: Reg did not settle (to x%x): x%x\n",
			       val, *regptr);
			return;
		}
		DELAY(100);
	}
}

/*
 * Routines for accessing the transmit and receive buffers. Unfortunately,
 * CPU addressing of these buffers is done in one of 3 ways:
 * - contiguous (for the 3max and turbochannel option card)
 * - gap2, which means shorts (2 bytes) interspersed with short (2 byte)
 *   spaces (for the pmax)
 * - gap16, which means 16bytes interspersed with 16byte spaces
 *   for buffers which must begin on a 32byte boundary (for 3min and maxine)
 * The buffer offset is the logical byte offset, assuming contiguous storage.
 */
void
copytobuf_contig(from, lebuf, boff, len)
	char *from;
	volatile void *lebuf;
	int boff;
	int len;
{

	/*
	 * Just call bcopy() to do the work.
	 */
	bcopy(from, ((char *)lebuf) + boff, len);
}

void
copyfrombuf_contig(lebuf, boff, to, len)
	volatile void *lebuf;
	int boff;
	char *to;
	int len;
{

	/*
	 * Just call bcopy() to do the work.
	 */
	bcopy(((char *)lebuf) + boff, to, len);
}

void
bzerobuf_contig(lebuf, boff, len)
	volatile void *lebuf;
	int boff;
	int len;
{

	/*
	 * Just let bzero() do the work
	 */
	bzero(((char *)lebuf) + boff, len);
}

/*
 * For the pmax the buffer consists of shorts (2 bytes) interspersed with
 * short (2 byte) spaces and must be accessed with halfword load/stores.
 * (don't worry about doing an extra byte)
 */
void
copytobuf_gap2(from, lebuf, boff, len)
	register char *from;
	volatile void *lebuf;
	int boff;
	register int len;
{
	register volatile u_short *bptr;
	register int xfer;

	if (boff & 0x1) {
		/* handle unaligned first byte */
		bptr = ((volatile u_short *)lebuf) + (boff - 1);
		*bptr = (*from++ << 8) | (*bptr & 0xff);
		bptr += 2;
		len--;
	} else
		bptr = ((volatile u_short *)lebuf) + boff;
	if ((unsigned)from & 0x1) {
		while (len > 1) {
D 15
			*bptr = (from[1] << 8) | from[0];
E 15
I 15
			*bptr = (from[1] << 8) | (from[0] & 0xff);
E 15
			bptr += 2;
			from += 2;
			len -= 2;
		}
	} else {
		/* optimize for aligned transfers */
		xfer = (int)((unsigned)len & ~0x1);
		CopyToBuffer((u_short *)from, bptr, xfer);
		bptr += xfer;
		from += xfer;
		len -= xfer;
	}
	if (len == 1)
		*bptr = (u_short)*from;
}

void
copyfrombuf_gap2(lebuf, boff, to, len)
	volatile void *lebuf;
	int boff;
	register char *to;
	register int len;
{
	register volatile u_short *bptr;
	register u_short tmp;
	register int xfer;

	if (boff & 0x1) {
		/* handle unaligned first byte */
		bptr = ((volatile u_short *)lebuf) + (boff - 1);
		*to++ = (*bptr >> 8) & 0xff;
		bptr += 2;
		len--;
	} else
		bptr = ((volatile u_short *)lebuf) + boff;
	if ((unsigned)to & 0x1) {
		while (len > 1) {
			tmp = *bptr;
			*to++ = tmp & 0xff;
			*to++ = (tmp >> 8) & 0xff;
			bptr += 2;
			len -= 2;
		}
	} else {
		/* optimize for aligned transfers */
		xfer = (int)((unsigned)len & ~0x1);
		CopyFromBuffer(bptr, to, xfer);
		bptr += xfer;
		to += xfer;
		len -= xfer;
	}
	if (len == 1)
		*to = *bptr & 0xff;
}

void
bzerobuf_gap2(lebuf, boff, len)
	volatile void *lebuf;
	int boff;
	int len;
{
	register volatile u_short *bptr;

	if ((unsigned)boff & 0x1) {
		bptr = ((volatile u_short *)lebuf) + (boff - 1);
		*bptr &= 0xff;
		bptr += 2;
		len--;
	} else
		bptr = ((volatile u_short *)lebuf) + boff;
	while (len > 0) {
		*bptr = 0;
		bptr += 2;
		len -= 2;
	}
}

/*
 * For the 3min and maxine, the buffers are in main memory filled in with
 * 16byte blocks interspersed with 16byte spaces.
 */
void
copytobuf_gap16(from, lebuf, boff, len)
	register char *from;
	volatile void *lebuf;
	int boff;
	register int len;
{
	register char *bptr;
	register int xfer;

	bptr = ((char *)lebuf) + ((boff << 1) & ~0x1f);
	boff &= 0xf;
	xfer = min(len, 16 - boff);
	while (len > 0) {
		bcopy(from, ((char *)bptr) + boff, xfer);
		from += xfer;
		bptr += 32;
		boff = 0;
		len -= xfer;
		xfer = min(len, 16);
	}
}

void
copyfrombuf_gap16(lebuf, boff, to, len)
	volatile void *lebuf;
	int boff;
	register char *to;
	register int len;
{
	register char *bptr;
	register int xfer;

	bptr = ((char *)lebuf) + ((boff << 1) & ~0x1f);
	boff &= 0xf;
	xfer = min(len, 16 - boff);
	while (len > 0) {
		bcopy(((char *)bptr) + boff, to, xfer);
		to += xfer;
		bptr += 32;
		boff = 0;
		len -= xfer;
		xfer = min(len, 16);
	}
}

void
bzerobuf_gap16(lebuf, boff, len)
	volatile void *lebuf;
	int boff;
	register int len;
{
	register char *bptr;
	register int xfer;

	bptr = ((char *)lebuf) + ((boff << 1) & ~0x1f);
	boff &= 0xf;
	xfer = min(len, 16 - boff);
	while (len > 0) {
		bzero(((char *)bptr) + boff, xfer);
		bptr += 32;
		boff = 0;
		len -= xfer;
		xfer = min(len, 16);
	}
}
D 10

#if NBPFILTER > 0
/*
 * This is exceptionally ugly, but since the lance buffers are not always
 * contiguous in cpu address space, this was the best I could think of.
 * Essentially build an mbuf list with the entire raw packet in it and
 * then dismantle it again if it is a local packet. I can't believe I am
 * rebuilding the trailer encapsulation, but...
 * Return true if the packet has been thrown away.
 */
static int
lebpf_tap(le, m, hdrmp, tailmp, off, ep, sbuf)
	struct le_softc *le;
	struct mbuf *m;
	struct mbuf **hdrmp;
	struct mbuf **tailmp;
	int off;
	struct ether_header *ep;
	u_short *sbuf;
{
	register struct mbuf *em, *sm;
	u_short *sp;

	MGET(em, M_DONTWAIT, MT_DATA);
	if (off && em) {
		MGET(sm, M_DONTWAIT, MT_DATA);
		if (sm == (struct mbuf *)0) {
			m_freem(em);
			em = (struct mbuf *)0;
		}
	}
	if (em) {
		bcopy((caddr_t)ep, mtod(em, caddr_t), sizeof (*ep));
		em->m_len = sizeof (*ep);
		if (off) {
			sp = mtod(sm, u_short *);
			*sp++ = *sbuf++;
			*sp = *sbuf;
			sm->m_len = 2 * sizeof (u_short);
			em->m_next = *hdrmp;
			*hdrmp = (struct mbuf *)0;
			*tailmp = sm;
			sm->m_next = m;
		} else
			em->m_next = m;
		bpf_tap(le->sc_bpf, em);
	}
	/*
	 * Note that the interface cannot be in promiscuous mode if
	 * there are no bpf listeners.  And if we are in promiscuous
	 * mode, we have to check if this packet is really ours.
	 *
	 * XXX This test does not support multicasts.
	 */
	if ((le->sc_if.if_flags & IFF_PROMISC)
	    && bcmp(ep->ether_dhost, le->sc_addr, 
		    sizeof(ep->ether_dhost)) != 0
	    && bcmp(ep->ether_dhost, etherbroadcastaddr, 
		    sizeof(ep->ether_dhost)) != 0) {
		if (em)
			m_freem(em);
		else
			m_freem(m);
		return (1);
	}
	if (em == (struct mbuf *)0)
		return (0);
	if (off) {
		MFREE(em, *hdrmp);
		*tailmp = (struct mbuf *)0;
		MFREE(sm, em);
	} else {
		MFREE(em, sm);
	}
	return (0);
}
#endif /* NBPFILTER */
E 10
#endif /* NLE */
E 8
E 1
