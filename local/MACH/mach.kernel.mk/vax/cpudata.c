/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cpudata.c,v $
 * Revision 2.4  89/03/09  22:13:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:12:39  gm0w
 * 	Changes for cleanup.
 * 
 * 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI:  augmented VAX820 and VAX8800 conditionals to also require
 *	this symbol so that BI support can be omitted more easily
 *	without changing the cpu set.
 *	[ V5.1(XF24) ]
 *
 * 10-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for VAX650.
 *
 *  2-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for VAX-8800.
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Forced include of "param.h" to find "../h" version.
 *
 * 22-Jul-86  UNIX Kernel Software (uk) at Carnegie-Mellon University
 *	CMUCS: Revised VAX630 "nexus" definition array to include
 *	memory and Q-bus pseudo-nexus spaces.
 *
 * 17-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	VAX1, VAX820:  Added 4.3-style tables to support uVax-1 and 8200.
 *	Previous local support for the uVax-2 and 8600 have been
 *	subsumed by 4.3.
 *
 * 03-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	BI support.
 *
 */ 
 
#include <bi.h>
#include <cputypes.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)cpudata.c	7.1 (Berkeley) 6/5/86
 */

#include <vax/pte.h>

#include <sys/param.h>

#include <vax/cpu.h>
#include <vax/nexus.h>
#include <vax/ioa.h>
#include <vaxuba/ubareg.h>
#if	VAX820
#include <vax/bi_node.h>
#endif	VAX820

/*
 * Initialization of per-cpu data structures.
 */

/*
 * These are the (fixed) addresses of the (last 8k bytes of)
 * unibus memory for each of the possible unibus adapters.  Note that the
 * unibus memory addresses are actually indexed by the unibus adapter type code.
 */
#if	VAX8800 && NBI > 0
caddr_t	umaddr8800[1] = {
	(caddr_t) UMEM8800(0)	/* these are calculated */
};
#endif	VAX8800 && NBI > 0
#if	VAX8600
caddr_t umaddr8600a[4] = {
	(caddr_t) UMEMA8600(0),	(caddr_t) UMEMA8600(1),
	(caddr_t) UMEMA8600(2),	(caddr_t) UMEMA8600(3),
};
caddr_t umaddr8600b[4] = {
	(caddr_t) UMEMB8600(0),	(caddr_t) UMEMB8600(1),
	(caddr_t) UMEMB8600(2),	(caddr_t) UMEMB8600(3),
};
#endif
#if	VAX780
caddr_t	umaddr780[4] = {
	(caddr_t) UMEM780(0), (caddr_t) UMEM780(1),
	(caddr_t) UMEM780(2), (caddr_t) UMEM780(3)
};
#endif
#if	VAX750
caddr_t	umaddr750[2] = {
	(caddr_t) UMEM750(0), (caddr_t) UMEM750(1),
};
#endif
#if	VAX730
caddr_t	umaddr730[1] = {
	(caddr_t) UMEM730
};
#endif
#if	VAX650
caddr_t	umaddr650[1] = {
	(caddr_t) UMEM650
};
#endif	VAX650
#if	VAX630
caddr_t	umaddr630[1] = {
	(caddr_t) UMEM630
};
#endif
#if	VAX820 && NBI > 0
caddr_t	umaddr820[1] = {
	(caddr_t) UMEM820(0)	/* these are calculated */
};
#endif	VAX820 && NBI > 0
#if	VAX1
caddr_t	umaddr1[1] = {
	(caddr_t) UMEM1
};
#endif	VAX1

/*
 * Information to patch around the stupidity of configuration
 * registers not returning types on some of the processors.
 */
#if	VAX750
short	nexty750[NNEX750] = {
	NEX_MEM16,	NEX_MEM16,	NEX_MEM16,	NEX_MEM16,
	NEX_MBA,	NEX_MBA,	NEX_MBA,	NEX_MBA,
	NEX_UBA0,	NEX_UBA1,	NEX_ANY,	NEX_ANY,
	NEX_ANY,	NEX_ANY,	NEX_ANY,	NEX_ANY
};
#endif
#if	VAX730
short	nexty730[NNEX730] = {
	NEX_MEM16,	NEX_ANY,	NEX_ANY,	NEX_ANY,
	NEX_ANY,	NEX_ANY,	NEX_ANY,	NEX_ANY,
};
#endif

#if	VAX8800 && NBI > 0
struct nexusconnect bi8800[] = {
	{ BI_MAX_NODE, (struct nexus *)BI_ADDR(0), umaddr8800, NBDPBI, 0, 0 },
	{ BI_MAX_NODE, (struct nexus *)BI_ADDR(1), umaddr8800, NBDPBI, 0, 0 },
	{ BI_MAX_NODE, (struct nexus *)BI_ADDR(2), umaddr8800, NBDPBI, 0, 0 },
	{ BI_MAX_NODE, (struct nexus *)BI_ADDR(3), umaddr8800, NBDPBI, 0, 0 }
};
struct iobus io8800[] = {
	{ IO_BI, 0, 0, (caddr_t)&bi8800[0] },
	{ IO_BI, 0, 0, (caddr_t)&bi8800[1] },
	{ IO_BI, 0, 0, (caddr_t)&bi8800[2] },
	{ IO_BI, 0, 0, (caddr_t)&bi8800[3] },
};
#endif	VAX8800 && NBI > 0
#if	VAX8600
struct nexusconnect sbi8600[] = {
	{ NNEX8600, NEXA8600, umaddr8600a, NBDP8600, 1, 0 },
	{ NNEX8600, NEXB8600, umaddr8600b, NBDP8600, 1, 0 },
};
struct iobus io8600[] = {
	{ IO_ABUS, IOA8600(0), IOAMAPSIZ, (caddr_t)&sbi8600[0] },
	{ IO_ABUS, IOA8600(1), IOAMAPSIZ, (caddr_t)&sbi8600[1] },
};
#endif
#if	VAX650
short	nexty650[NNEX650] = {
	NEX_MEMCTL,	NEX_ANY,	NEX_CACR_BDR,	NEX_ANY,
	NEX_UBA0,
};
#endif	VAX650
#if	VAX630
short	nexty630[NNEX630] = {
	NEX_BDRMEM,	NEX_ANY,	NEX_ANY,	NEX_ANY,
	NEX_UBA0,
};
#endif
#if	VAX1
short	nexty1[NNEX1] = {
	NEX_UBA0,
};
#endif	VAX1

#if	VAX780
struct nexusconnect sbi780 = {
	NNEX780, NEX780, umaddr780, NBDP780, 1, 0,
};
struct iobus io780[] = { IO_SBI780, 0, 0, (caddr_t)&sbi780 };
#endif

#if	VAX750
struct nexusconnect cmi750 = {
	NNEX750, NEX750, umaddr750, NBDP750, 0, nexty750,
};
struct iobus io750[] = { IO_CMI750, 0, 0, (caddr_t)&cmi750 };
#endif

#if	VAX730
struct nexusconnect xxx730 = {
	NNEX730, NEX730, umaddr730, NBDP730, 0, nexty730,
};
struct iobus io730[] = { IO_XXX730, 0, 0, (caddr_t)&xxx730 };
#endif
#if	VAX650
struct nexusconnect xxx650[] = {
	{ NNEX650, NEX650, umaddr650, NBDP650, 0, nexty650 },
};
struct iobus io650[] =  {
	{ IO_QBUS, 0, 0, (caddr_t)&xxx650[0] },
};
#endif	VAX650
#if	VAX630
struct nexusconnect xxx630 = {
	NNEX630, NEX630, umaddr630, NBDP630, 0, nexty630,
};
struct iobus io630[] = { IO_QBUS, 0, 0, (caddr_t)&xxx630 };
#endif
#if	VAX820 && NBI > 0
struct nexusconnect bi820 = {
	BI_MAX_NODE, (struct nexus *)BI_ADDR(0), umaddr820, NBDPBI, 0, 0
};
struct iobus io820[] = { IO_BI, 0, 0, (caddr_t)&bi820 };
#endif	VAX820 && NBI > 0
#if	VAX1
struct nexusconnect xxx1 = {
	NNEX1, NEX1, umaddr1, NBDP1, 0, nexty1,
};
struct iobus io1[] = { IO_QBUS, 0, 0, (caddr_t)&xxx1 };
#endif	VAX1


struct percpu percpu[] = {
#if	VAX8800 && NBI > 0
	{ VAX_8800, 10, 4, io8800 },
#endif	VAX8800 && NBI > 0
#if	VAX8600
	{ VAX_8600, 6, 2, io8600 },
#endif
#if	VAX780
	{ VAX_780, 2, 1, io780 },
#endif
#if	VAX750
	{ VAX_750, 1, 1, io750 },
#endif
#if	VAX730
	{ VAX_730, 1, 1, io730 },
#endif
#if	VAX650
	{ VAX_650, 6, 1, io650 },
#endif	VAX650
#if	VAX630
	{ VAX_630, 2, 1, io630 },
#endif
#if	VAX820 && NBI > 0
	{ VAX_820, 2, 1, io820 },
#endif	VAX820 && NBI > 0
#if	VAX1
	{ VAX_1, 2, 1, io1 },
#endif	VAX1
	0,
};
#if	VAX1 && !VAX630
#include <OOPS: VAX1 currently requires VAX630>
#endif	VAX1 && !VAX630
