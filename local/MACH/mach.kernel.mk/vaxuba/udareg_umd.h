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
 * $Log:	udareg_umd.h,v $
 * Revision 2.4  89/03/09  22:41:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:10:14  gm0w
 * 	Changes for cleanup.
 * 
 * 18-Sep-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Carried over support for KDB50 (from below).
 *	[ V5.1(XF16) ]
 *
 * 12-Jun-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI: Create separate kdb50device structure since overloading
 *	the UDA50 structure with an extra short word breaks the return
 *	from udaprobe().
 *
 *  9-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added support for KDB50 (BI-bus) controller.
 *
 */
 
#include <bi.h>
/*
 * UDA50 registers and structures
 */

/*
 * Writing any value to udaip starts initialisation.  Reading from it
 * when the UDA is running makes the UDA look through the command ring
 * to find any new commands.  Reading udasa gives status; writing it
 * during initialisation sets things up.
 */
struct udadevice {
	u_short	udaip;		/* initialisation and polling */
	u_short	udasa;		/* status and address */
};
#if	NBI > 0
 
struct kdb50device {
	struct udadevice kdb50_uda;
	short	         kdb50_wr;		/* write register (KDB50) */
};
#define kdbip	kdb50_uda.udaip
#define kdbsa	kdb50_uda.udasa
#define kdbwr	kdb50_wr

#define UDA_MAP	0x80000000	/* modifier for mapped buffer descriptors */
#endif	NBI > 0

/*
 * Bits in UDA status register during initialisation
 */
#define UDA_ERR		0x8000	/* error */
#define UDA_STEP4	0x4000	/* step 4 has started */
#define UDA_STEP3	0x2000	/* step 3 has started */
#define UDA_STEP2	0x1000	/* step 2 has started */
#define UDA_STEP1	0x0800	/* step 1 has started */
#define UDA_NV		0x0400	/* no host settable interrupt vector */
#define UDA_QB		0x0200	/* controller supports Q22 bus */
#define UDA_DI		0x0100	/* controller implements diagnostics */
#define UDA_IE		0x0080	/* interrupt enable */
#define UDA_NCNRMASK	0x003f	/* in STEP1, bits 0-2=NCMDL2, 3-5=NRSPL2 */
#define UDA_IVECMASK	0x007f	/* in STEP2, bits 0-6 are interruptvec / 4 */
#define UDA_PI		0x0001	/* host requests adapter purge interrupts */

/*
 * Bits in UDA status register after initialisation
 */
#define UDA_GO		0x0001	/* run */

#define UDASR_BITS \
"\20\20ERR\17STEP4\16STEP3\15STEP2\14STEP1\13NV\12QB\11DI\10IE\1GO"

/*
 * UDA Communications Area.  Note that this structure definition
 * requires NRSP and NCMD to be defined already.
 */
struct udaca {
	short	ca_xxx1;	/* unused */
	char	ca_xxx2;	/* unused */
	char	ca_bdp;		/* BDP to purge */
	short	ca_cmdint;	/* command ring transition flag */
	short	ca_rspint;	/* response ring transition flag */
	long	ca_rspdsc[NRSP];/* response descriptors */
	long	ca_cmddsc[NCMD];/* command descriptors */
};

/*
 * Simplified routines (e.g., uddump) reprogram the UDA50 for one command
 * and one response at a time; uda1ca is like udaca except that it provides
 * exactly one command and response descriptor.
 */
struct uda1ca {
	short	ca_xxx1;
	char	ca_xxx2;
	char	ca_bdp;
	short	ca_cmdint;
	short	ca_rspint;
	long	ca_rspdsc;
	long	ca_cmddsc;
};
