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
 * $Log:	udareg.h,v $
 * Revision 2.6  89/03/09  22:41:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/26  11:10:07  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/24  03:10:16  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  19:07:22  mwyoung]
 *
 * Revision 2.3  88/08/10  10:56:08  rvb
 * Add some #define's for MSCP state printout.
 *
 * 12-Jun-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Create separate kdb50device structure since overloading the
 *	UDA50 structure with an extra short word breaks the return from
 *	udaprobe().
 *	[ V5.1(XF12) ]
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed CS_NEWCPU.
 *
 *  9-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added support for KDB50 (BI-bus) controller.
 *
 * 12-Mar-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add <sys/features.h> include when not KERNEL.
 *
 */
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)udareg.h	6.2 (Berkeley) 6/8/85
 */
 
#include <bi.h>
#ifdef	MACH
#include <cputypes.h>
#endif	MACH
#include <net_uda.h>

#if	NET_UDA
#include <vaxuba/udareg_umd.h>
#else	NET_UDA

/*
 * UDA-50 registers and structures
 */

struct udadevice {
	short	udaip;		/* initialization and polling */
	short	udasa;		/* status and address */
};

#if	NBI > 0
struct kdb50device {
	struct udadevice kdb50_uda;
	short	         kdb50_wr;		/* write register (KDB50) */
};
#define kdbip	kdb50_uda.udaip
#define kdbsa	kdb50_uda.udasa
#define kdbwr	kdb50_wr
#endif	NBI > 0

#define UDA_ERR		0100000	/* error bit */
#define UDA_STEP4	0040000	/* step 4 has started */
#define UDA_STEP3	0020000	/* step 3 has started */
#define UDA_STEP2	0010000	/* step 2 has started */
#define UDA_STEP1	0004000	/* step 1 has started */
#define UDA_NV		0002000	/* no host settable interrupt vector */
#define UDA_QB		0001000	/* controller supports Q22 bus */
#define UDA_DI		0000400	/* controller implements diagnostics */
#define UDA_IE		0000200	/* interrupt enable */
#define UDA_PI		0000001	/* host requests adapter purge interrupts */
#define UDA_GO		0000001	/* start operation, after init */

#define MSCP_ERR	0x00008000
#define MSCP_4		0x00004000
#define MSCP_3		0x00002000
#define MSCP_2		0x00001000
#define MSCP_1		0x00000800
#define MSCP_NV		0x00000400
#define MSCP_Q22	0x00000200
#define MSCP_DIAG	0x00000100
#define MSCP_IE		0x00000080
#define MSCP_DATA	0x00000070
#define MSCP	"\20\20ERR\17#4\16#3\15#2\14#1\13NV\12Q22\11DIAG\10IE\07\01DATA"

/*
 * UDA Communications Area
 */

struct udaca {
	short	ca_xxx1;	/* unused */
	char	ca_xxx2;	/* unused */
	char	ca_bdp;		/* BDP to purge */
	short	ca_cmdint;	/* command queue transition interrupt flag */
	short	ca_rspint;	/* response queue transition interrupt flag */
	long	ca_rspdsc[NRSP];/* response descriptors */
	long	ca_cmddsc[NCMD];/* command descriptors */
};

#define ca_ringbase	ca_rspdsc[0]

#define UDA_OWN	0x80000000	/* UDA owns this descriptor */
#define UDA_INT	0x40000000	/* allow interrupt on ring transition */
#if	VAX820 || VAX1
#define UDA_MAP	0x80000000	/* modifier for mapped buffer descriptors */
#endif	VAX820 || VAX1

/*
 * MSCP packet info
 */
struct mscp_header {
	short	uda_msglen;	/* length of MSCP packet */
	char	uda_credits;	/* low 4 bits: credits, high 4 bits: msgtype */
	char	uda_vcid;	/* virtual circuit id */
};
#endif	NET_UDA
