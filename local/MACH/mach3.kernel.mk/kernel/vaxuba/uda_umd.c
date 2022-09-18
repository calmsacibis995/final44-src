/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon the
 * rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	uda_umd.c,v $
 * Revision 2.11  93/05/17  10:25:27  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 
 * Revision 2.10  93/05/15  19:00:41  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.9  92/02/25  14:18:08  elf
 * 	Include device/param.h for DEV_BSIZE
 * 	[92/02/25            elf]
 * 
 * Revision 2.8  92/02/23  22:45:59  elf
 * 	Added udgetstat().
 * 	[92/02/22  18:56:39  af]
 * 
 * Revision 2.7  91/06/19  12:02:14  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:50:44  rvb]
 * 
 * Revision 2.6  91/05/14  17:47:36  mrt
 * 	Correcting copyright
 * 
 * Revision 2.5  91/05/13  06:09:10  af
 * 	Rid of the "CMU" conditional once and forall.
 * 	[91/05/12  16:41:19  af]
 * 
 * Revision 2.4  91/05/08  13:34:15  dbg
 * 	Use free MSCP definition from Berkeley Tahoe release.
 * 	[91/04/26            dbg]
 * 
 * 	Add volatile declarations.
 * 	[91/04/16            dbg]
 * 
 * 	Move br and cvec to memory.
 * 	[91/03/26            dbg]
 * 
 * 	Include vax/machparam.h for SPL definitions.
 * 	Use todr() function to get pseudo time-of-day register.
 * 	[91/03/20            dbg]
 * 
 * Revision 2.3  91/01/08  16:43:55  rpd
 * 	Added continuation argument to thread_block.
 * 	[90/12/08            rpd]
 * 
 * Revision 2.2  90/01/11  11:47:12  dbg
 * 	Serialize read/write to make work on multiple CPU machines.
 * 	[89/11/27            dbg]
 * 
 * 	MACH_KERNEL conversion.
 * 	[88/12/01            dbg]
 * 
 * Revision 2.1  89/08/03  16:41:19  rwd
 * Created.
 * 
 * Revision 2.6  88/11/14  14:54:33  gm0w
 * 	Added disk tables for rd54, ra80wrenv, ra80cdc8, and ra80cdc12.
 * 	[88/11/14            berman]
 * 
 * Revision 2.5  88/10/11  13:10:45  rpd
 * 	Dont reset bi_node in udainit().  It is no longer necessary.
 * 	[88/10/03            rvb]
 * 
 * Revision 2.4  88/08/22  21:36:12  mja
 * 	CS_DISK => CMUCS_DISK and confine its use to changes in
 * 	partitioning from the original driver (other changes and
 * 	support for new types are not incompatible with existing
 * 	foreign sites since they never existed there).
 * 	[88/08/18            mja]
 * 	
 * 	Fix udprobe() to be more persistent in retrying failures before
 * 	giving up and add RA82 table [berman]; CS_GENERIC => CMUCS
 * 	[mja].
 * 	[88/08/11  16:10:36  mja]
 * 
 * Revision 2.3  88/08/10  10:55:25  rvb
 * BCI_UINTEN => BCI_UCSREN  (according to spec)
 * 
 *  3-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Converted to use CS_DISK to mark CMUCS partition tables.
 *
 * 12-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added RA81M table.
 *	[ V5.1(XF24) ]
 *
 * 03-Mar-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Defined RA80TYPE1 and RA80TYPE6 in place of old RA80TYPE and
 *	updated type tables to reflect use of older type #1 by Emulex
 *	controllers rather than the newer type #6.
 *	[ V5.1(XF22) ]
 *
 * 20-Feb-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added RA80DD, RA80E, RA80EM, and RA80PF tables;  fixed
 *	udaprobe() to bypass device probe when the register address is
 *	zero (used for BI KDB50 probes).
 *	[ V5.1(XF22) ]
 *
 * 17-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added RA80DF and RA81ED tables.
 *	[ V5.1(XF21) ]
 *
 * 07-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 * 07-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	CMUCS:  Attempt to retry host memory access errors until
 *	we can figure out what is really going on with them (this code
 *	may not even work as currently implemented - so far it's hard
 *	to tell).
 *	[ V5.1(XF17) ]
 *
 * 18-Sep-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  added support for MicroVAX and other CMU local
 *	drive types/partitions on the various controller emulations;
 *	revised wildcard slave processing to work better with these
 *	non-DEC controllers; suppressed attempts to bring empty RX50
 *	floppy drives on-line during configuration; suppressed unit
 *	status message printing by default and tinkered with the drive
 *	type display format;  made a stab at emulating mfpr(TODR) for
 *	the 8800 and 630.
 *	
 *	Carried over (albeit without testing) changes for KDB50 support
 *	on BI (from below).
 *	[ V5.1(XF16) ]
 *
 * 11-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for kdb50 (8200).
 *
 */
/*
 * This code is derived from software contributed to Mach by
 * Chris Torek, of the University of Maryland.
 */
 
#include <bi.h>
#include <platforms.h>

#include <cmucs_disk.h>
/*
 * UDA50/MSCP device driver
 */

/*
 * TODO
 *	write bad block forwarding code
 */

#include <ra.h>

#if NUDA > 0

/*
 * CONFIGURATION OPTIONS.  The next three defines are tunable -- tune away!
 *
 * NRSPL2 and NCMDL2 control the number of response and command
 * packets respectively.  They may be any value from 0 to 7, though
 * setting them higher than 5 is unlikely to be of any value.
 * If you get warnings about your command ring being too small,
 * try increasing the values by one.
 *
 * MAXUNIT controls the maximum unit number (number of drives per
 * controller) we are prepared to handle.
 *
 * DEFAULT_BURST must be at least 1.
 */
#define	NRSPL2	5		/* log2 number of response packets */
#define NCMDL2	5		/* log2 number of command packets */
#define	MAXUNIT	8		/* maximum allowed unit number */
#define	DEFAULT_BURST	4	/* default DMA burst size */
#if	MACH
#define MAX_RETRY       10      /* Maximum number of retries on 4-step init */
#endif	MACH

#ifdef	MACH_KERNEL
#include <mach/boolean.h>
#include <kern/sched_prim.h>
#include <kern/time_out.h>
#include <sys/syslog.h>

#include <sys/types.h>
#include <device/buf.h>
#include <device/param.h>
#include <device/dk.h>
#include <device/errno.h>
#include <device/dev_master.h>

#include <vax/cpu_data.h>
#include <vax/vm_defs.h>
#include <vax/machspl.h>
#else	MACH_KERNEL
#include "../machine/pte.h"

#include "param.h"
#include "systm.h"
#include "buf.h"
#include "conf.h"
#include "dir.h"
#include "user.h"
#include "map.h"
#include "vm.h"
#include "dk.h"
#include "cmap.h"
#include "syslog.h"

#include "../vax/cpu.h"
#endif	MACH_KERNEL
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

#define	NRSP	(1 << NRSPL2)
#define	NCMD	(1 << NCMDL2)

#include <vaxuba/udareg_umd.h>
#include <vax/mscp.h>
#include <vax/mscpvar.h>
#include <vax/mtpr.h>

#if	NBI > 0
#include <vax/bi_node.h>
/*
 *	Assume VM is on, if not, this won't work for kdb50 anyway.
 */
#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/pmap.h>

#endif	NBI > 0
/*
 * Backwards compatibility:  Reuse the old names.  Should fix someday.
 */
#define	udaprobe	udprobe
#define	udaslave	udslave
#define	udaattach	udattach
#define	udaopen		udopen
#define	udastrategy	udstrategy
#define	udaread		udread
#define	udawrite	udwrite
#define	udareset	udreset
#define	udaintr		udintr
#define	udadump		uddump
#define	udasize		udsize

/*
 * UDA communications area and MSCP packet pools, per controller.
 */
struct	uda {
	struct	udaca uda_ca;		/* communications area */
	struct	mscp uda_rsp[NRSP];	/* response packets */
	struct	mscp uda_cmd[NCMD];	/* command packets */
} uda[NUDA];

/*
 * Software status, per controller.
 */
struct	uda_softc {
	struct	uda *sc_uda;	/* Unibus address of uda struct */
    volatile
	short	sc_state;	/* UDA50 state; see below */
	short	sc_flags;	/* flags; see below */
	int	sc_micro;	/* microcode revision */
	int	sc_ivec;	/* interrupt vector address */
	struct	mscp_info sc_mi;/* MSCP info (per mscpvar.h) */
	int	sc_wticks;	/* watchdog timer ticks */
#if	NBI > 0
	short	kdb50;		/* are we on a kdb50? */
	struct bi_node *bi;	/* address of BI node space */
#endif	NBI > 0
} uda_softc[NUDA];

/*
 * Controller states
 */
#define	ST_IDLE		0	/* uninitialised */
#define	ST_STEP1	1	/* in `STEP 1' */
#define	ST_STEP2	2	/* in `STEP 2' */
#define	ST_STEP3	3	/* in `STEP 3' */
#define	ST_SETCHAR	4	/* in `Set Controller Characteristics' */
#define	ST_RUN		5	/* up and running */

/*
 * Flags
 */
#define	SC_MAPPED	0x01	/* mapped in Unibus I/O space */
#define	SC_INSTART	0x02	/* inside udastart() */
#define	SC_GRIPED	0x04	/* griped about cmd ring too small */
#define	SC_INSLAVE	0x08	/* inside udaslave() */
#define	SC_DOWAKE	0x10	/* wakeup when ctlr init done */

/*
 * Device to unit number and partition:
 */
#define	UNITSHIFT	3
#define	UNITMASK	7
#define	udaunit(dev)	(minor(dev) >> UNITSHIFT)
#define	udapart(dev)	(minor(dev) & UNITMASK)

/* THIS SHOULD BE READ OFF THE PACK, PER DRIVE */
struct size {
	daddr_t nblocks;
	daddr_t blkoff;
} ra81_sizes[8] = {
#if	CMUCS_DISK
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
	184458,	15884+33440,	/* D=blk 49324 thru 233781 */
	-1,	15884+33440+184458,/* E=blk 233782 thru end */
	368916,	15884+33440,	/* F=blk 49324 thru 418239 */
	-1,	15884+33440+368916,/* G=blk 418240 thru end */
	-1,	15884+33440,	/* H=blk 49324 thru end */
#else	CMUCS_DISK
#ifdef MARYLAND
#ifdef ENEEVAX
	30706,	0,		/* A=cyl    0 thru   42 + 2 sectors */
	40696,	30706,		/* B=cyl   43 thru   99 - 2 sectors */
	-1,	0,		/* C=cyl    0 thru 1247 */
	-1,	71400,		/* D=cyl  100 thru 1247 */

	15884,	0,		/* E=blk      0 thru  15883 */
	33440,	15884,		/* F=blk  15884 thru  49323 */
	82080,	49324,		/* G=blk  49324 thru 131403 */
	-1,	131404,		/* H=blk 131404 thru    end */
#else
	67832,	0,		/* A=cyl    0 thru   94 + 2 sectors */
	67828,	67832,		/* B=cyl   95 thru  189 - 2 sectors */
	-1,	0,		/* C=cyl    0 thru 1247 */
	-1,	135660,		/* D=cyl  190 thru 1247 */
	0,	0,
	0,	0,
	0,	0,
	0,	0,
#endif ENEEVAX
#else
	/* THE FOLLOWING ARE STRAIGHT FROM THE 4.3BSD uda.c */
	/* THIS KIND OF GARBAGE IS WHY THIS SHOULD BE READ FROM THE PACK */

/*
 * These are the new standard partition sizes for ra81's.
 * An RA_COMPAT system is compiled with D, E, and F corresponding
 * to the 4.2 partitions for G, H, and F respectively.
 */
#ifndef	UCBRA
	15884,	0,		/* A=sectors 0 thru 15883 */
	66880,	16422,		/* B=sectors 16422 thru 83301 */
	891072,	0,		/* C=sectors 0 thru 891071 */
#ifdef RA_COMPAT
	82080,	49324,		/* 4.2 G => D=sectors 49324 thru 131403 */
	759668,	131404,		/* 4.2 H => E=sectors 131404 thru 891071 */
	478582,	412490,		/* 4.2 F => F=sectors 412490 thru 891071 */
#else
	15884,	375564,		/* D=sectors 375564 thru 391447 */
	307200,	391986,		/* E=sectors 391986 thru 699185 */
	191352,	699720,		/* F=sectors 699720 thru 891071 */
#endif RA_COMPAT
	515508,	375564,		/* G=sectors 375564 thru 891071 */
	291346,	83538,		/* H=sectors 83538 thru 374883 */

/*
 * These partitions correspond to the sizes used by sites at Berkeley,
 * and by those sites that have received copies of the Berkeley driver
 * with deltas 6.2 or greater (11/15/83).
 */
#else UCBRA

	15884,	0,		/* A=sectors 0 thru 15883 */
	33440,	15884,		/* B=sectors 15884 thru 49323 */
	891072,	0,		/* C=sectors 0 thru 891071 */
	15884,	242606,		/* D=sectors 242606 thru 258489 */
	307200,	258490,		/* E=sectors 258490 thru 565689 */
	325382,	565690,		/* F=sectors 565690 thru 891071 */
	648466,	242606,		/* G=sectors 242606 thru 891071 */
	193282,	49324,		/* H=sectors 49324 thru 242605 */

#endif UCBRA
#endif MARYLAND
#endif	CMUCS_DISK
},
#if GYRE
cdc9771_sizes[8] = {		/* HACK: treat some RA81s as 9771s on gyre */
	79680,	0,		/* A = cyl    0 thru   59 */
	79680,	79680,		/* B = cyl   60 thru  119 */
	-1,	0,		/* C = cyl    0 thru 1021 */
	-1,	159360,		/* D = cyl  120 thru 1021 */
	0,	0,
	0,	0,
	0,	0,
	0,	0,
},
#endif
ra80_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
	0,	0,
	0,	0,
	0,	0,
	82080,	49324,		/* G=blk 49324 thru 131403 */
	-1,	131404,		/* H=blk 131404 thru end */
}, ra60_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
	-1,	49324,		/* D=blk 49324 thru end */
	0,	0,
	0,	0,
	82080,	49324,		/* G=blk 49324 thru 131403 */
	-1,	131404,		/* H=blk 131404 thru end */
#if	MACH
}, ra81e_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	33440,	15884,		   /* B=blk  15884 thru  49323 */
	787156,	0,		   /* C=blk      0 thru 787155 */
	184458,	15884+33440,	   /* D=blk  49324 thru 233781 */
	-1,	15884+33440+184458,/* E=blk 233782 thru    end */
	368916,	15884+33440,	   /* F=blk  49324 thru 418239 */
	-1,	15884+33440+368916,/* G=blk 418240 thru    end */
	-1,	15884+33440,	   /* H=blk  49324 thru    end */
}, ra81ed_sizes[8] = {
	16080,	0,		/* A=sectors 0 thru 16079 */
	67000,	16080,		/* B=sectors 16080 thru 83079 */
	1122116,0,		/* C=sectors 0 thru 1122115 */
	194300,	83080,		/* D=sectors 83080 thru 277379 */
	152760,	277380,		/* E=sectors 277380 thru 430139 */
	347060,	83080,		/* F=sectors 83080 thru 430139 */
	345720,	430140,		/* G=sectors 430140 thru 775859 */
	-1,	775860,		/* H=sectors 775860 thru 1122115 */
}, ra81em_sizes[8] = {
	16048,	0,		/* A=sectors 0 thru 16047 */
	33456,	16048,		/* B=sectors 16048 thru 49503 */
	276896,	0,		/* C=sectors 0 thru 276895 */
	34544,	49504,		/* D=sectors 49504 thru 84047 */
	-1,	84048,		/* E=sectors 84048 thru 276895 */
	0,	0,
	-1,	0,		/* G=sectors 0 thru 276895 */
	-1,	49504,		/* H=sectors 49504 thru 276895 */
}, ra81m_sizes[8] = {
	15939,	0,		/* A=sectors 0 thru 15938 */
	33495,	15939,		/* B=sectors 15939 thru 49433 */
	281127,	0,		/* C=sectors 0 thru 281126 */
	34419,	49434,		/* D=sectors 49434 thru 83852 */
	-1,	83853,		/* E=sectors 83853 thru 281126 */
	0,	0,
	-1,	0,		/* G=sectors 0 thru 281126 */
	-1,	49434,		/* H=sectors 49434 thru 281126 */
}, ra81s_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	33440,	15884,		   /* B=blk  15884 thru  49323 */
	702240,	0,		   /* C=blk      0 thru 702239 */
	189772,	15884+33440,	   /* D=blk  49324 thru 239095 */
	-1,	15884+33440+189772,/* E=blk 239096 thru    end */
	326876,	15884+33440,	   /* F=blk  49324 thru 376199 */
	-1,	15884+33440+326876,/* G=blk 376200 thru    end */
	-1,	15884+33440,	   /* H=blk  49324 thru    end */
}, ra80cdc8_sizes[8] = {
	16560,	0,		/* A=sectors 0 thru 16559 */
	67275,	16560,		/* B=sectors 16560 thru 83834 */
	1427265,0,		/* C=sectors 0 thru 1427264 */
	194580,	83835,		/* D=sectors 83835 thru 278414 */
	253575,	278415,		/* E=sectors 278415 thru 531989 */
	448155,	83835,		/* F=sectors 83835 thru 531989 */
	447120,	531990,		/* G=sectors 531990 thru 979109 */
	448155,	979110,		/* H=sectors 979110 thru 1427264 */
}, ra80cdc12_sizes[8] = {
	16575,  0,		/* A=sectors 0 thru 16574 */
	67575,  16575,		/* B=sectors 16575 thru 84149 */
	2082075, 0,		/* C=sectors 0 thru 2082074 */
	195075, 84150,		/* D=sectors 84150 thru 279224 */
	470475, 279225,		/* E=sectors 279225 thru 749699 */
	665550, 84150,		/* F=sectors 84150 thru 749699 */
	665550, 749700,		/* G=sectors 749700 thru 1415249 */
	666825, 1415250,	/* H=sectors 1415250 thru 2082074 */
}, ra80wrenv_sizes[8] = {
	16275,  0,		/* A=sectors 0 thru 16274 */
	33600,  16275,		/* B=sectors 16275 thru 49874 */
	737625, 0,		/* C=sectors 0 thru 737624 */
	194250, 49875,		/* D=sectors 49875 thru 244124 */
	149625, 244125,		/* E=sectors 244125 thru 393749 */
	343875, 49875,		/* F=sectors 49875 thru 393749 */
	343875, 393750,		/* G=sectors 393750 thru 737624 */
	687750, 49875,		/* H=sectors 49875 thru 737624 */
}, ra80dd_sizes[8] = {
	16080,	0,		/* A=sectors 0 thru 16079 */
	67000,	16080,		/* B=sectors 16080 thru 83079 */
	1125600,0,		/* C=sectors 0 thru 1125599 */
	194300,	83080,		/* D=sectors 83080 thru 277379 */
	152760,	277380,		/* E=sectors 277380 thru 430139 */
	347060,	83080,		/* F=sectors 83080 thru 430139 */
	347060,	430140,		/* G=sectors 430140 thru 777199 */
	-1,	777200,		/* H=sectors 777200 thru 1125599 */
}, ra80de_sizes[8] = {
	16560,	0,		   /* A=blk      0 thru  16557 */
	34040,	16560,		   /* B=blk  16560 thru  50599 */
	772800,	0,		   /* C=blk      0 thru 772799 */
	190440,	16560+34040,	   /* D=blk  50600 thru 241039 */
	-1,	16560+34040+190440,/* E=blk 241040 thru    end */
	360640,	16560+34040,	   /* F=blk  50600 thru 411239 */
	-1,	16560+34040+360640,/* G=blk 411240 thru    end */
	-1,	16560+34040,	   /* H=blk  50600 thru    end */
}, ra80df_sizes[8] = {
	15980,	0,		/* A=sectors 0 thru 15979 */
	33840,	15980,		/* B=sectors 15980 thru 49819 */
	789600,	0,		/* C=sectors 0 thru 789599 */
	194580,	49820,		/* D=sectors 49820 thru 244399 */
	174840,	244400,		/* E=sectors 244400 thru 419239 */
	369420,	49820,		/* F=sectors 49820 thru 419239 */
	-1,	419240,		/* G=sectors 419240 thru 789599 */
	-1,	49820,		/* H=sectors 49820 thru 789599 */
}, ra80e_sizes[8] = {
	16340,	0,		/* A=sectors 0 thru 16339 */
	33540,	16340,		/* B=sectors 16340 thru 49879 */
	720680,	0,		/* C=sectors 0 thru 720679 */
	194360,	49880,		/* D=sectors 49880 thru 244239 */
	141040,	244240,		/* E=sectors 244240 thru 385279 */
	335400,	49880,		/* F=sectors 49880 thru 385279 */
	-1,	385280,		/* G=sectors 385280 thru 720679 */
	-1,	49880,		/* H=sectors 49880 thru 720679 */
}, ra80f_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	33440,	15884,		   /* B=blk  15884 thru  49323 */
	277440,	0,		   /* C=blk      0 thru 277439 */
	34830,	15884+33440,	   /* D=blk  49324 thru  84153 */
	-1,	15884+33440+34830, /* E=blk  84154 thru    end */
	0,	0,		   /* F=blk */
	0,	0,		   /* G=blk */
	-1,	15884+33440,	   /* H=blk  49324 thru    end */
}, ra80p_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	33440,	15884,		   /* B=blk  15884 thru  49323 */
	639450,	0,		   /* C=blk      0 thru 639449 */
	34830,	15884+33440,	   /* D=blk  49324 thru  84153 */
	-1,	15884+33440+34830, /* E=blk  84154 thru    end */
	0,	0,		   /* F=blk */
	0,	0,		   /* G=blk */
	-1,	15884+33440,	   /* H=blk  49324 thru    end */
}, ra80pf_sizes[8] = {
	16275,	0,		/* A=sectors 0 thru 16274 */
	33600,	16275,		/* B=sectors 16275 thru 49874 */
	642075,	0,		/* C=sectors 0 thru 642074 */
	194250,	49875,		/* D=sectors 49875 thru 244124 */
	101850,	244125,		/* E=sectors 244125 thru 345974 */
	296100,	49875,		/* F=sectors 49875 thru 345974 */
	-1,	345975,		/* G=sectors 345975 thru 642074 */
	-1,	49875,		/* H=sectors 49875 thru 642074 */
}, rd54_sizes[8] ={
        15884,  0,              /* A=blk 0 thru 15883 */
        33440,  15884,          /* B=blk 15884 thru 49323 */
        -1, 	0,              /* C=blk 0 thru end 311200 */
        130938, 49324,          /* D=blk 49324 thru 180261 */
        -1,     180262,         /* E=blk 180262 thru end   */
        0,      0,
        -1,     49324,          /* G=blk 49324 thru end */
        0,      0
}, rd53_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	33440,	15884,		   /* B=blk  15884 thru  49323 */
	-1,	0,		   /* C=blk      0 thru    end */
	34830,	15884+33440,	   /* D=blk  49324 thru  84153 */
	-1,	15884+33440+34830, /* E=blk  84154 thru    end */
	0,	0,		   /* F=blk */
	-1,	49324,		   /* G=blk  49324 thru    end */
	-1,	15884+33440,	   /* H=blk  49324 thru    end */
}, rd52_sizes[8] = {
	15884,	0,		   /* A=blk      0 thru  15883 */
	9766,	15884,		   /* B=blk  15884 thru  25649 */
	-1,	0,		   /* C=blk      0 thru    end */
	32000,	9766+15884,	   /* D=blk  25650 thru  57649 */
	-1,	9766+15884+32000,  /* E=blk  57650 thru    end */
	-1,	15884,		   /* F=blk  15884 thru    end */
	-1,	25650,		   /* G=blk  25650 thru    end */
	-1,	9766+15884,	   /* H=blk  25650 thru    end */
}, rx50_sizes[8] = {
	800,	0,		   /* A=blk      0 thru    799 */
	0,	0,		   /* B */
	-1,	0,		   /* C=blk      0 thru    end */
	0,	0,		   /* B */
	0,	0,		   /* B */
	0,	0,		   /* B */
	0,	0,		   /* B */
	0,	0,		   /* B */
}, ra82_sizes[8] = {
	16245,	0,		/* A=sectors 0 thru 16244 */
	67545,	16245,		/* B=sectors 16245 thru 83789 */
	1216665,0,		/* C=sectors 0 thru 1216664 */
	194085,	83790,		/* D=sectors 83790 thru 277874 */
	183825,	277875,		/* E=sectors 277875 thru 461699 */
	377910,	83790,		/* F=sectors 83790 thru 461699 */
	377055,	461700,		/* G=sectors 461700 thru 838754 */
	377910,	838755,		/* H=sectors 838755 thru 1216664 */
#endif	MACH
};
/* END OF STUFF WHICH SHOULD BE READ IN PER DISK */

/*
 * Drive type index decoding table.  `ut_name' is null iff the
 * type is not known.
 */
struct	udatypes {
	char	*ut_name;	/* drive type name */
	struct	size *ut_sizes;	/* partition tables */
} udatypes[] = {
	NULL,		NULL,
	"ra80",		ra80_sizes,	/* 1 = ra80 */
	"old ra81",	ra81_sizes,	/* 2 = old ra81 microcode */
	NULL,		NULL,		/* 3 = old ra60?? */
	"ra60",		ra60_sizes,	/* 4 = ra60 */
	"ra81",		ra81_sizes,	/* 5 = ra81 */
#if	MACH
#define	RA80TYPE1			   1
#define	RA81TYPE			   5
#define	RA80TYPE6			   6
	"ra80",		ra80_sizes,	/* 6 = ra80 */
#define	RX50TYPE			   7
	"rx50",		rx50_sizes,	/* 7 = rx50 */
#define	RD52TYPE			   8
	"rd52",		rd52_sizes,	/* 8 = rd52 */
#define	RD53TYPE			   9
	"rd53",		rd53_sizes,	/* 9 = rd53 */
	NULL,		NULL,		/* Place holder */
#define	RA82TYPE			  11
	"ra82",		ra82_sizes,	/*11 = ra82 */
        NULL,           NULL,           /* Place holder */
#define	RD54TYPE			  13
	"rd54",		rd54_sizes,	/*13 = rd54 */
	/*
	 *  End of real drive types as reported by the protocol (which we are
	 *  prepared to recognize).  Everything at and above NTYPES is only a
	 *  pseudo-type used internally.
	 */
#define	NTYPES				  14
#define	RA80DDTYPE			  (NTYPES+0)
	"ra80dd",	ra80dd_sizes,
#define	RA80DETYPE			  (NTYPES+1)
	"ra80de",	ra80de_sizes,
#define	RA80DFTYPE			  (NTYPES+2)
	"ra80df",	ra80df_sizes,
#define	RA80ETYPE			  (NTYPES+3)
	"ra80e",	ra80e_sizes,
#define	RA80FTYPE			  (NTYPES+4)
	"ra80f",	ra80f_sizes,
#define	RA80PTYPE			  (NTYPES+5)
	"ra80p",	ra80p_sizes,
#define	RA80PFTYPE			  (NTYPES+6)
	"ra80pf",	ra80pf_sizes,
#define	RA81ETYPE			  (NTYPES+7)
	"ra81e",	ra81e_sizes,
#define	RA81EDTYPE			  (NTYPES+8)
	"ra81ed",	ra81ed_sizes,
#define	RA81EMTYPE			  (NTYPES+9)
	"ra81em",	ra81em_sizes,
#define	RA81MTYPE			  (NTYPES+10)
	"ra81m",	ra81m_sizes,
#define	RA81STYPE			  (NTYPES+11)
	"ra81s",	ra81s_sizes,
#define	RA80CDC8TYPE			  (NTYPES+12)
	"ra80cdc8",	ra80cdc8_sizes,
#define	RA80CDC12TYPE			  (NTYPES+13)
	"ra80cdc12",	ra80cdc12_sizes,
#define	RA80WRENVTYPE			  (NTYPES+14)
	"ra80wrenv",	ra80wrenv_sizes,
#else	MACH
#if GYRE
	/*
	 * This CDC partition hack depends on the fact that the
	 * Emulex SC41/MS controller is `version 6 model 6' and
	 * the current DEC devices are `version 5 model 6'.
	 */
	"cdc9771",	cdc9771_sizes,
#define	CDCTYPE	6	/* note that this is past the last real type */
#define	ISCDC(sc) ((sc)->sc_micro == 0x66)
#endif
#endif	MACH
};

#if	MACH
int uda_printstatus = 0;	/* enable unit status message printing */
int uda_host_access_retry = 0;	/* enable host retry testing */

/*
 *  We redefine NTYPES above closer to the actual table definition.
 */
#else	MACH
#define NTYPES 6
#endif	MACH

/*
 * Definition of the driver for autoconf.
 */
int	udaprobe(), udaslave(), udaattach(), udadgo(), udaintr();
struct	uba_ctlr *udaminfo[NUDA];
struct	uba_device *udadinfo[NRA];

u_short	udastd[] = { 0772150, 0772550, 0777550, 0 };
struct	uba_driver udadriver =
 { udaprobe, udaslave, udaattach, udadgo, udastd, "ra", udadinfo, "uda",
   udaminfo };

/*
 * More driver definitions, for generic MSCP code.
 */
int	udadgram(), udactlrdone(), udaunconf(), udaonline(), udagotstatus();
int	udaioerror(), udareplace(), udabb();

struct	buf udautab[NRA];	/* per drive transfer queue */

struct	mscp_driver udamscpdriver =
 { MAXUNIT, NRA, UNITSHIFT, udautab,
   udadgram, udactlrdone, udaunconf,
   udaonline, udagotstatus, udareplace, udaioerror, udabb };

/*
 * Miscellaneous private variables.
 */
struct	buf rudabuf[NRA];	/* raw I/O buffer headers */

char	udasr_bits[] = UDASR_BITS;

struct	uba_device *udaip[NUDA][MAXUNIT];
				/* inverting pointers: ctlr & unit => Unibus
				   device pointer */

int	udaburst[NUDA] = {0};	/* burst size, per UDA50, zero => default;
				   in data space so patchable via adb */

daddr_t	ra_dsize[NRA];		/* drive sizes, from on line end packets */

struct	mscp udaslavereply;	/* get unit status response packet, set
				   for udaslave by udaunconf, via udaintr */

static struct uba_ctlr *probeum;/* this is a hack---autoconf should pass ctlr
				   info to slave routine; instead, we remember
				   the last ctlr argument to probe */

int	udawstart, udawatch();	/* watchdog timer */

/*
 * Externals
 */
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
int	wakeup();
int	hz;
#endif	MACH_KERNEL

#if	NBI > 0
/*
 * Called from autoconf to flag a KDB.
 */
udaiskdb50(ctlr, bi, vec)
	int		ctlr;
	struct bi_node	*bi;
	int		vec;
{
	uda_softc[ctlr].kdb50 = TRUE;
	uda_softc[ctlr].sc_ivec = vec;
	uda_softc[ctlr].bi = bi;
}

#endif	NBI > 0
/*
 * Poke at a supposed UDA50 to see if it is there.
 * This routine duplicates some of the code in udainit() only
 * because autoconf has not set up the right information yet.
 * We have to do everything `by hand'.
 */
extern volatile int	br, cvec;

udaprobe(reg, ctlr, um)
	caddr_t reg;
	int ctlr;
	struct uba_ctlr *um;
{
	register struct uda_softc *sc;
	register struct udadevice *udaddr;
	register struct mscp_info *mi;
	int probe_timeout, tries;

#ifdef VAX750
	/*
	 * The UDA50 wants to share BDPs on 750s, but not on 780s or
	 * 8600s.  (730s have no BDPs anyway.)  Toward this end, we
	 * here set the `keep bdp' flag in the per-driver information
	 * if this is a 750.  (We just need to do it once, but it is
	 * easiest to do it now, for each UDA50.)
	 */
	if (cpu == VAX_750)
		udadriver.ud_keepbdp = 1;
#endif

	probeum = um;			/* remember for udaslave() */
#ifdef lint
	udaintr(0);
#endif
	/*
	 * Set up the controller-specific generic MSCP driver info.
	 * Note that this should really be done in the (nonexistent)
	 * controller attach routine.
	 */
	sc = &uda_softc[ctlr];
	mi = &sc->sc_mi;
	mi->mi_md = &udamscpdriver;
	mi->mi_um = um;
	mi->mi_ip = udaip[ctlr];
	mi->mi_cmd.mri_size = NCMD;
	mi->mi_cmd.mri_desc = uda[ctlr].uda_ca.ca_cmddsc;
	mi->mi_cmd.mri_ring = uda[ctlr].uda_cmd;
	mi->mi_rsp.mri_size = NRSP;
	mi->mi_rsp.mri_desc = uda[ctlr].uda_ca.ca_rspdsc;
	mi->mi_rsp.mri_ring = uda[ctlr].uda_rsp;
	mi->mi_wtab.av_forw = mi->mi_wtab.av_back = &mi->mi_wtab;

	/*
	 * More controller specific variables.  Again, this should
	 * be in the controller attach routine.
	 */
	if (udaburst[ctlr] == 0)
		udaburst[ctlr] = DEFAULT_BURST;
#if	NBI > 0

	/*
	 *  For a KDB50 on the BI, we aren't interested in the remaining code
	 *  which probes for the controller (since we already found it on the
	 *  BI using "extraordinary" means before getting here.  For lack of
	 *  any better convention, use a zero probe address to indicate that we
	 *  already know that the controller exists.
	 *
	 *  I don't think this routine can ever be called any other way for a
	 *  KDB50 so the remaining BI specific changes below are probably
	 *  spurious but we did it this way in the old driver so we'll do it
	 *  this way in the new one until we know for sure.
	 */
	if (reg == 0)
	    return (sizeof (struct kdb50device));
#endif	NBI > 0

	/*
	 * Get an interrupt vector.  Note that even if the controller
	 * does not respond, we keep the vector.  This is not a serious
	 * problem; but it would be easily fixed if we had a controller
	 * attach routine.  Sigh.
	 */
	sc->sc_ivec = (uba_hd[numuba].uh_lastiv -= 4);
	udaddr = (struct udadevice *) reg;

	/*
	 * Initialise the controller (partially).  The UDA50 programmer's
	 * manual states that if initialisation fails, it should be retried
	 * at least once, but after a second failure the port should be
	 * considered `down'; it also mentions that the controller should
	 * initialise within ten seconds.  Or so I hear; I have not seen
	 * this manual myself.
	 *
	 * N.B.: mfpr(TODR) will not work on uVaxen.
	 */
	tries = 0;
again:
	udaddr->udaip = 0;		/* start initialisation */
#if	MACH
	todr_prime();			/* prime TODR emulation */
#endif	MACH
	probe_timeout = todr() + 1000;	/* timeout in 10 seconds */
	while ((udaddr->udasa & UDA_STEP1) == 0)
		if (todr() > probe_timeout)
			goto bad;
#if	NBI > 0
	if (sc->kdb50) ((struct kdb50device *)udaddr)
	      ->kdbwr = UDA_ERR | (NCMDL2 << 11) | (NRSPL2 << 8) | UDA_IE |
 		(sc->sc_ivec >> 2);
	else
#endif	NBI > 0
	udaddr->udasa = UDA_ERR | (NCMDL2 << 11) | (NRSPL2 << 8) | UDA_IE |
		(sc->sc_ivec >> 2);
	while ((udaddr->udasa & UDA_STEP2) == 0)
		if (todr() > probe_timeout)
			goto bad;

	/* should have interrupted by now */
#if	NBI > 0
	/*
	 *  Be careful to return the proper size here to prevent non KDB50
	 *  controllers from appearing to take up more Q-bus address space than
	 *  they actually occupy.
	 */
	if (sc->kdb50)
	    return (sizeof (struct kdb50device));
	else
#endif	NBI > 0
	return (sizeof (struct udadevice));
bad:
	if (++tries < 2)
		goto again;
	return (0);
}

/*
 * Find a slave.  We allow wildcard slave numbers (something autoconf
 * is not really prepared to deal with); and we need to know the
 * controller number to talk to the UDA.  For the latter, we keep
 * track of the last controller probed, since a controller probe
 * immediately precedes all slave probes for that controller.  For the
 * former, we simply put the unit number into ui->ui_slave after we
 * have found one.
 *
 * Note that by the time udaslave is called, the interrupt vector
 * for the UDA50 has been set up (so that udaunconf() will be called).
 */
udaslave(ui, reg)
	register struct uba_device *ui;
	caddr_t reg;
{
	register struct uba_ctlr *um = probeum;
	register struct mscp *mp;
	register struct uda_softc *sc;
	int next = 0, type, init_timeout, tries, i;

#ifdef lint
	i = 0; i = i;
#endif
	/*
	 * Make sure the controller is fully initialised, by waiting
	 * for it if necessary.
	 */
	sc = &uda_softc[um->um_ctlr];
	if (sc->sc_state == ST_RUN)
		goto findunit;
	tries = 0;
again:
	if (udainit(ui->ui_ctlr))
		return (0);
#if	MACH
	todr_prime();			/* prime TODR emulation */
#endif	MACH
	init_timeout = todr() + 1000;	/* 10 seconds */
	while (todr() < init_timeout)
		if (sc->sc_state == ST_RUN)	/* made it */
			goto findunit;
	if (++tries < 2)
		goto again;
	printf("uda%d: controller hung\n", um->um_ctlr);
	return (0);

	/*
	 * The controller is all set; go find the unit.  Grab an
	 * MSCP packet and send out a Get Unit Status command, with
	 * the `next unit' modifier if we are looking for a generic
	 * unit.  We set the `in slave' flag so that udaunconf()
	 * knows to copy the response to `udaslavereply'.
	 */
findunit:
	udaslavereply.mscp_opcode = 0;
	sc->sc_flags |= SC_INSLAVE;
	if ((mp = mscp_getcp(&sc->sc_mi, MSCP_DONTWAIT)) == NULL)
		panic("udaslave");		/* `cannot happen' */
	mp->mscp_opcode = M_OP_GETUNITST;
#if	MACH
	/*
	 *  The current CMU config program records wildcard slaves as -1,
	 *  not '?' ...
	 */
	if (ui->ui_slave == -1)
	    ui->ui_slave = '?';
#endif	MACH
	if (ui->ui_slave == '?') {
#if	MACH
		/*
		 *  As far as I can tell, the M_GUM_NEXTUNIT modifier isn't
		 *  implemented properly by some of the RQDXn lookalikes.
		 *  Thus, we'll simply poll for the next unconfigured drive
		 *  directly rather than depend on this modifier to do the
		 *  right thing.
		 */
		for (; next<MAXUNIT; next++)
		    if (udaip[um->um_ctlr][next] == 0)
			break;
 		mp->mscp_unit = next;
		mp->mscp_modifier = 0;
#else	MACH
		mp->mscp_unit = next;
		mp->mscp_modifier = M_GUM_NEXTUNIT;
#endif	MACH
	} else {
		mp->mscp_unit = ui->ui_slave;
		mp->mscp_modifier = 0;
	}
	*mp->mscp_seq.seq_addr |= MSCP_OWN | MSCP_INT;
	i = ((struct udadevice *) reg)->udaip;	/* initiate polling */
	mp = &udaslavereply;
#if	MACH
	todr_prime();			/* prime TODR emulation */
#endif	MACH
	init_timeout = todr() + 1000;
	while (todr() < init_timeout)
		if (*(volatile u_char *)&mp->mscp_opcode)
			goto gotit;
	printf("uda%d: no response to Get Unit Status request\n",
		um->um_ctlr);
	sc->sc_flags &= ~SC_INSLAVE;
	return (0);

gotit:
	sc->sc_flags &= ~SC_INSLAVE;

	/*
	 * Got a slave response.  If the unit is there, use it.
	 */
	switch (mp->mscp_status & M_ST_MASK) {

	case M_ST_SUCCESS:	/* worked */
	case M_ST_AVAILABLE:	/* found another drive */
		break;		/* use it */

	case M_ST_OFFLINE:
		/*
		 * Figure out why it is off line.  It may be because
		 * it is nonexistent, or because it is spun down, or
		 * for some other reason.
		 */
		switch (mp->mscp_status & ~M_ST_MASK) {

		case M_OFFLINE_UNKNOWN:
			/*
			 * No such drive, and there are none with
			 * higher unit numbers either, if we are
			 * using M_GUM_NEXTUNIT.
			 */
#if	MACH
			/*
			 *  Without a functioning M_GUM_NEXTUNIT modifier we
			 *  don't want to give up here in the wildcard case
			 *  unless we just tried the last possible unit.
			 */
			if (ui->ui_slave == '?' && mp->mscp_unit < (MAXUNIT-1))
				goto try_another;
#endif	MACH
			return (0);

		case M_OFFLINE_UNMOUNTED:
			/*
			 * The drive is not spun up.  Use it anyway.
			 *
			 * N.B.: this seems to be a common occurrance
			 * after a power failure.  The first attempt
			 * to bring it on line seems to spin it up
			 * (and thus takes several minutes).  Perhaps
			 * we should note here that the on-line may
			 * take longer than usual.
			 */
			break;

		default:
			/*
			 * In service, or something else equally unusable.
			 */
			printf("uda%d: unit %d off line: ", um->um_ctlr,
				mp->mscp_unit);
			mscp_printevent(mp);
			goto try_another;
		}
		break;

	default:
		printf("uda%d: unable to get unit status: ", um->um_ctlr);
		mscp_printevent(mp);
		return (0);
	}

	/*
	 * Does this ever happen?  What (if anything) does it mean?
	 */
	if (mp->mscp_unit < next) {
		printf("uda%d: unit %d, next %d\n",
			um->um_ctlr, mp->mscp_unit, next);
		return (0);
	}

	if (mp->mscp_unit >= MAXUNIT) {
		printf("uda%d: cannot handle unit number %d (max is %d)\n",
			um->um_ctlr, mp->mscp_unit, MAXUNIT - 1);
		return (0);
	}

	/*
	 * See if we already handle this drive.
	 * (Only likely if ui->ui_slave=='?'.)
	 */
	if (udaip[um->um_ctlr][mp->mscp_unit] != NULL)
		goto try_another;

	/*
	 * Make sure we know about this kind of drive.
	 * Others say we should treat unknowns as RA81s; I am
	 * not sure this is safe.
	 */
#if	MACH
	/*
	 * Correct for RQDX3 drive type 19 botch
	 */
	type = udafixtype(sc,
			  (int)mp->mscp_guse.guse_drivetype,
			  (int)mp->mscp_guse.guse_mediaid);
#else	MACH
	type = mp->mscp_guse.guse_drivetype;
#endif	MACH
	if (type >= NTYPES || udatypes[type].ut_name == 0) {
		printf("uda%d: unit %d (media ID `", um->um_ctlr,
			mp->mscp_unit);
		uda_decode_media(mp->mscp_guse.guse_mediaid);
		printf("') is of unknown type %d; ignored\n", type);
try_another:
		if (ui->ui_slave != '?')
			return (0);
		next = mp->mscp_unit + 1;
		goto findunit;
	}
#if GYRE
	if (ISCDC(sc))
		type = CDCTYPE;
#endif

	/*
	 * Voila!
	 */
	ui->ui_type = type;
	ui->ui_flags = 0;	/* not on line, nor anything else */
	ui->ui_slave = mp->mscp_unit;
	return (1);
}

/*
 * Decode and print the media ID.  It is made up of five 5-bit
 * `characters' and 7 bits of numeric information.  BITS(i)
 * selects character i's bits; CHAR returns the corresponding
 * character.
 */
uda_decode_media(id)
	register long id;
{
	int c4, c3, c2, c1, c0;
#define	CHAR(c)	((c) ? (c) + '@' : ' ')

	c4 = MSCP_MID_ECH(4, id);
	c3 = MSCP_MID_ECH(3, id);
	c2 = MSCP_MID_ECH(2, id);
	c1 = MSCP_MID_ECH(1, id);
	c0 = MSCP_MID_ECH(0, id);
	printf("%c%c %c%c%c%d", CHAR(c4), CHAR(c3), CHAR(c2),
		CHAR(c1), CHAR(c0), MSCP_MID_NUM(id));
#undef	CHAR
}

/*
 * Attach a found slave.  Make sure the watchdog timer is running.
 * If this disk is being profiled, fill in the `mspw' value (used by
 * what?).  Set up the inverting pointer, and attempt to bring the
 * drive on line.
 */
udaattach(ui)
	register struct uba_device *ui;
{

	if (udawstart == 0) {
		timeout(udawatch, (caddr_t) 0, hz);
		udawstart++;
	}
	if (ui->ui_dk >= 0)
		dk_mspw[ui->ui_dk] = 1.0 / (60 * 31 * 256);	/* approx */
	udaip[ui->ui_ctlr][ui->ui_slave] = ui;
#if	MACH
	/*
	 *  The floppy off-line messages during configuration can get tiresome
	 *  so don't bother trying to bring an RX50 floppy on-line when the
	 *  status showed it off-line rather than available.
	 */
	if (ui->ui_type != RX50TYPE
	    ||
	    (udaslavereply.mscp_status & ~M_ST_MASK) !=  M_OFFLINE_UNMOUNTED)
#endif	MACH
	(void) uda_bringonline(&uda_softc[ui->ui_ctlr], ui, 1);
	/* should we get its status too? */
}

/*
 * Initialise a UDA50.  Return true iff something goes wrong.
 */
udainit(ctlr)
	int ctlr;
{
	register struct uda_softc *sc;
	register struct udadevice *udaddr;
	struct uba_ctlr *um;
	int timo, ubinfo;

	sc = &uda_softc[ctlr];
	um = udaminfo[ctlr];
	if ((sc->sc_flags & SC_MAPPED) == 0) {
#if	NBI > 0
	    if (sc->kdb50) {
#if	MACH
			sc->sc_uda = (struct uda *)
				pmap_extract(pmap_kernel(),
					     (vm_offset_t)&uda[ctlr]);
#endif	MACH
	    }
	    else {
#endif	NBI > 0
		/*
		 * Map the communication area and command and
		 * response packets into Unibus space.
		 */
		ubinfo = uballoc(um->um_ubanum, (caddr_t) &uda[ctlr],
			sizeof (struct uda), UBA_CANTWAIT);
		if (ubinfo == 0) {
			printf("uda%d: uballoc map failed\n", ctlr);
			return (-1);
		}
		sc->sc_uda = (struct uda *) (ubinfo & 0x3ffff);
#if	NBI > 0
	    }
#endif	NBI > 0
		sc->sc_flags |= SC_MAPPED;
	}

	/*
	 * While we are thinking about it, reset the next command
	 * and response indicies.
	 */
	sc->sc_mi.mi_cmd.mri_next = 0;
	sc->sc_mi.mi_rsp.mri_next = 0;

	/*
	 * Start up the hardware initialisation sequence.
	 */
#define	STEP0MASK	(UDA_ERR | UDA_STEP4 | UDA_STEP3 | UDA_STEP2 | \
			 UDA_STEP1 | UDA_NV)

	sc->sc_state = ST_IDLE;	/* in case init fails */
	udaddr = (struct udadevice *) um->um_addr;
#if	NBI > 0
	if (sc->kdb50) {
		/* bi_node_reset(sc->bi) */;
	}
	else
#endif	NBI > 0
	udaddr->udaip = 0;
#if	MACH
	todr_prime();			/* prime TODR emulation */
#endif	MACH
	timo = todr() + 1000;
	while ((udaddr->udasa & STEP0MASK) == 0) {
		if (todr() > timo) {
			printf("uda%d: timeout during init\n", ctlr);
			return (-1);
		}
	}
	if ((udaddr->udasa & STEP0MASK) != UDA_STEP1) {
		printf("uda%d: init failed, sa=%b\n", ctlr,
			udaddr->udasa, udasr_bits);
		return (-1);
	}

	/*
	 * Success!  Record new state, and start step 1 initialisation.
	 * The rest is done in the interrupt handler.
	 */
	sc->sc_state = ST_STEP1;
#if	NBI > 0
	if (sc->kdb50) {
		((struct kdb50device *)udaddr)
              ->kdbwr = UDA_ERR | (NCMDL2 << 11) | (NRSPL2 << 8) | UDA_IE |
	    (sc->sc_ivec >> 2);
	}
	else
#endif	NBI > 0
	udaddr->udasa = UDA_ERR | (NCMDL2 << 11) | (NRSPL2 << 8) | UDA_IE |
	    (sc->sc_ivec >> 2);
	return (0);
}

/*
 * Open a drive.
 */
/*ARGSUSED*/
udaopen(dev, flag)
	dev_t dev;
	int flag;
{
	register int unit;
	register struct uba_device *ui;
	register struct uda_softc *sc;
	int s;

	/*
	 * Make sure this is a reasonable open request.
	 */
	unit = udaunit(dev);
	if (unit >= NRA || (ui = udadinfo[unit]) == 0 || ui->ui_alive == 0)
		return (ENXIO);

	/*
	 * Make sure the controller is running, by (re)initialising it if
	 * necessary.
	 */
	sc = &uda_softc[ui->ui_ctlr];
	s = spl5();
	if (sc->sc_state != ST_RUN) {
		if (sc->sc_state == ST_IDLE && udainit(ui->ui_ctlr)) {
			splx(s);
			return (EIO);
		}
		/*
		 * In case it does not come up, make sure we will be
		 * restarted in 10 seconds.  This corresponds to the
		 * 10 second timeouts in udaprobe() and udaslave().
		 */
		sc->sc_flags |= SC_DOWAKE;
#ifdef	MACH_KERNEL
		assert_wait((event_t)sc, FALSE);
		thread_set_timeout((unsigned)(10 * hz));
		thread_block((void (*)()) 0);
#else	MACH_KERNEL
		timeout(wakeup, (caddr_t) sc, 10 * hz);
		sleep((caddr_t) sc, PRIBIO);
#endif	MACH_KERNEL
		if (sc->sc_state != ST_RUN) {
			splx(s);
			printf("uda%d: controller hung\n", ui->ui_ctlr);
			return (EIO);
		}
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
		untimeout(wakeup, (caddr_t) sc);
#endif	MACH_KERNEL
	}
	if ((ui->ui_flags & UNIT_ONLINE) == 0) {
		/*
		 * Bring the drive on line so we can find out how
		 * big it is.  If it is not spun up, it will not
		 * come on line; this cannot really be considered
		 * an `error condition'.
		 */
		if (uda_bringonline(sc, ui, 0)) {
			splx(s);
			printf("ra%d: drive will not come on line\n", unit);
			return (EIO);
		}
	}
	splx(s);
	return (0);
}

/*
 * Bring a drive on line.  In case it fails to respond, we set
 * a timeout on it.  The `nosleep' parameter should be set if
 * we are to spin-wait; otherwise this must be called at spl5().
 */
uda_bringonline(sc, ui, nosleep)
	register struct uda_softc *sc;
	register struct uba_device *ui;
	int nosleep;
{
	register struct mscp *mp;
	int i;

	if (nosleep) {
		mp = mscp_getcp(&sc->sc_mi, MSCP_DONTWAIT);
		if (mp == NULL)
			return (-1);
	} else
		mp = mscp_getcp(&sc->sc_mi, MSCP_WAIT);
	mp->mscp_opcode = M_OP_ONLINE;
	mp->mscp_unit = ui->ui_slave;
	mp->mscp_cmdref = (long) &ui->ui_flags;
	*mp->mscp_seq.seq_addr |= MSCP_OWN | MSCP_INT;
	i = ((struct udadevice *) ui->ui_addr)->udaip;

	if (nosleep) {
#if	MACH
		todr_prime();		/* prime TODR emulation */
#endif	MACH
		i = todr() + 1000;
		while ((*(volatile int *)&ui->ui_flags & UNIT_ONLINE) == 0)
			if (todr() > i)
				return (-1);
	} else {
#ifdef	MACH_KERNEL
		assert_wait((event_t) &ui->ui_flags, FALSE);
		thread_set_timeout((unsigned)(10 * hz));
		thread_block((void (*)()) 0);
#else	MACH_KERNEL
		timeout(wakeup, (caddr_t) &ui->ui_flags, 10 * hz);
		sleep((caddr_t) &ui->ui_flags, PRIBIO);
#endif	MACH_KERNEL
		if ((ui->ui_flags & UNIT_ONLINE) == 0)
			return (-1);
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
		untimeout(wakeup, (caddr_t) &ui->ui_flags);
#endif	MACH_KERNEL
	}
	return (0);	/* made it */
}

/*
 * Queue a transfer request, and if possible, hand it to the controller.
 *
 * This routine is broken into two so that the internal version
 * udastrat1() can be called by the (nonexistent, as yet) bad block
 * revectoring routine.
 */
udastrategy(bp)
	register struct buf *bp;
{
	register int unit;
	register struct uba_device *ui;
	register struct size *st;
	daddr_t sz, maxsz;

	/*
	 * Make sure this is a reasonable drive to use.
	 */
	if ((unit = udaunit(bp->b_dev)) >= NRA ||
	    (ui = udadinfo[unit]) == NULL || ui->ui_alive == 0) {
		bp->b_error = ENXIO;
		bp->b_flags |= B_ERROR;
		iodone(bp);
		return;
	}

	/*
	 * Determine the size of the transfer, and make sure it is
	 * within the boundaries of the drive.
	 */
	sz = (bp->b_bcount + 511) >> 9;
	st = &udatypes[ui->ui_type].ut_sizes[udapart(bp->b_dev)];
	if ((maxsz = st->nblocks) < 0)
		maxsz = ra_dsize[unit] - st->blkoff;
	if (bp->b_blkno < 0 || bp->b_blkno + sz > maxsz ||
	    st->blkoff >= ra_dsize[unit]) {
		/* if exactly at end of disk, return an EOF */
		if (bp->b_blkno == maxsz)
			bp->b_resid = bp->b_bcount;
		else {
			bp->b_error = EINVAL;
			bp->b_flags |= B_ERROR;
		}
		iodone(bp);
		return;
	}
	udastrat1(bp);
}

/*
 * Work routine for udastrategy.
 */
udastrat1(bp)
	register struct buf *bp;
{
	register int unit = udaunit(bp->b_dev);
	register struct uba_ctlr *um;
	register struct buf *dp;
	struct uba_device *ui;
	int s = spl5();

	/*
	 * Append the buffer to the drive queue, and if it is not
	 * already there, the drive to the controller queue.  (However,
	 * if the drive queue is marked to be requeued, we must be
	 * awaiting an on line or get unit status command; in this
	 * case, leave it off the controller queue.)
	 */
	um = (ui = udadinfo[unit])->ui_mi;
	dp = &udautab[unit];
	APPEND(bp, dp, av_forw);
	if (dp->b_active == 0 && (ui->ui_flags & UNIT_REQUEUE) == 0) {
		APPEND(dp, &um->um_tab, b_forw);
		dp->b_active++;
	}

	/*
	 * Start activity on the controller.  Note that unlike other
	 * Unibus drivers, we must always do this, not just when the
	 * controller is not active.
	 */
	udastart(um);
	splx(s);
}

/*
 * Start up whatever transfers we can find.
 * Note that udastart() must be called at spl5().
 */
udastart(um)
	register struct uba_ctlr *um;
{
	register struct uda_softc *sc = &uda_softc[um->um_ctlr];
	register struct buf *bp, *dp;
	register struct mscp *mp;
	struct uba_device *ui;
	struct udadevice *udaddr;
	int i;

#ifdef lint
	i = 0; i = i;
#endif
	/*
	 * If it is not running, try (again and again...) to initialise
	 * it.  If it is currently initialising just ignore it for now.
	 */
	if (sc->sc_state != ST_RUN) {
		if (sc->sc_state == ST_IDLE && udainit(um->um_ctlr))
			printf("uda%d: still hung\n", um->um_ctlr);
		return;
	}

	/*
	 * If um_cmd is nonzero, this controller is on the Unibus
	 * resource wait queue.  It will not help to try more requests;
	 * instead, when the Unibus unblocks and calls udadgo(), we
	 * will call udastart() again.
	 */
	if (um->um_cmd)
		return;
	sc->sc_flags |= SC_INSTART;
	udaddr = (struct udadevice *) um->um_addr;

loop:
	/*
	 * Service the drive at the head of the queue.  We take exactly
	 * one transfer from this drive, then move it to the end of the
	 * controller queue, so as to get more drive overlap.
	 */
	if ((dp = um->um_tab.b_actf) == NULL) {
		um->um_tab.b_active = 0;
		goto out;
	}

	/*
	 * Get the first request from the drive queue.  There must be
	 * one, or something is rotten.
	 */
	if ((bp = dp->b_actf) == NULL)
		panic("udastart: bp==NULL\n");

	if (udaddr->udasa & UDA_ERR) {	/* ctlr fatal error */
		udasaerror(um);
		goto out;
	}

	/*
	 * Get an MSCP packet, then figure out what to do.  If
	 * we cannot get a command packet, the command ring may
	 * be too small:  We should have at least as many command
	 * packets as credits, for best performance.
	 */
	if ((mp = mscp_getcp(&sc->sc_mi, MSCP_DONTWAIT)) == NULL) {
		if (sc->sc_mi.mi_credits > MSCP_MINCREDITS &&
		    (sc->sc_flags & SC_GRIPED) == 0) {
			log(LOG_NOTICE, "uda%d: command ring too small\n",
				um->um_ctlr);
			sc->sc_flags |= SC_GRIPED;/* complain only once */
		}
		goto out;
	}

	/*
	 * Mark the controller active, but do not move the drive off
	 * the controller queue: ubago() wants it there.
	 */
	um->um_tab.b_active = 1;

	/*
	 * Bring the drive on line if it is not already.  Get its status
	 * if we do not already have it.  Otherwise just start the transfer.
	 */
	ui = udadinfo[udaunit(bp->b_dev)];
	if ((ui->ui_flags & UNIT_ONLINE) == 0) {
		mp->mscp_opcode = M_OP_ONLINE;
		goto common;
	}
	if ((ui->ui_flags & UNIT_HAVESTATUS) == 0) {
		mp->mscp_opcode = M_OP_GETUNITST;
common:
if (ui->ui_flags & UNIT_REQUEUE) panic("udastart");
		/*
		 * Take the drive off the controller queue.  When the
		 * command finishes, make sure the drive is requeued.
		 */
		um->um_tab.b_actf = dp->b_forw;
		dp->b_active = 0;
		ui->ui_flags |= UNIT_REQUEUE;
		mp->mscp_unit = ui->ui_slave;
		*mp->mscp_seq.seq_addr |= MSCP_OWN | MSCP_INT;
		i = udaddr->udaip;
		goto loop;
	}

	mp->mscp_opcode = (bp->b_flags & B_READ) ? M_OP_READ : M_OP_WRITE;
	mp->mscp_unit = ui->ui_slave;
	mp->mscp_seq.seq_lbn = bp->b_blkno +
		udatypes[ui->ui_type].ut_sizes[udapart(bp->b_dev)].blkoff;
	mp->mscp_seq.seq_bytecount = bp->b_bcount;
#if	NBI > 0
	if (sc->kdb50) {
		/*
		 *  N.B. We rely on mscp_go() not to clobber the UDA_MAP bit
		 *  when it ORs in the rest of the buffer address.
		 */
		mp->mscp_seq.seq_buffer = UDA_MAP;
		mp->mscp_seq.seq_mapbase = (long)
#if	MACH_KERNEL
			pmap_extract(kernel_pmap,
				     (vm_offset_t)uba_hd[um->um_ubanum].uh_mr);
#else	MACH_KERNEL
			&(uba_hd[um->um_ubanum].uh_physuba->uba_map[0]);
#endif	MACH_KERNEL
	}
#endif	NBI > 0
	/* mscp_cmdref and mscp_buffer are filled in by mscp_go() */

	/*
	 * Drop the packet pointer into the `command' field so udadgo()
	 * can tell what to start.  If ubago returns 1, we can do another
	 * transfer.  If not, um_cmd will still point at mp, so we will
	 * know that we are waiting for resources.
	 */
	um->um_cmd = (int) mp;
	if (ubago(ui))
		goto loop;
	/*
	 * All done, or blocked in ubago().
	 */
out:
	sc->sc_flags &= ~SC_INSTART;
}

/*
 * Start a transfer.
 *
 * If we are not called from within udastart(), we must have been
 * blocked, so call udastart to do more requests (if any).  If
 * this calls us again immediately we will not recurse, because
 * that time we will be in udastart().  Clever....
 */
udadgo(um)
	register struct uba_ctlr *um;
{
	struct uda_softc *sc = &uda_softc[um->um_ctlr];
	int i;

#ifdef lint
	i = 0; i = i;
#endif
	/*
	 * Fill in the MSCP packet and move the buffer to the
	 * I/O wait queue.  Mark the controller as no longer on
	 * the resource queue, and initiate polling.
	 */
	mscp_go(um, &sc->sc_mi, (struct mscp *) um->um_cmd);
	um->um_cmd = 0;	
	i = ((struct udadevice *) um->um_addr)->udaip;

	if ((sc->sc_flags & SC_INSTART) == 0)
		udastart(um);
}

/*
 * The error bit was set in the controller status register.  Gripe,
 * reset the controller, requeue pending transfers.
 */
udasaerror(um)
	register struct uba_ctlr *um;
{

	printf("uda%d: controller error, sa=%b\n", um->um_ctlr,
		((struct udadevice *) um->um_addr)->udasa, udasr_bits);
	mscp_requeue(&uda_softc[um->um_ctlr].sc_mi);
	(void) udainit(um->um_ctlr);
}

/*
 * Interrupt routine.  Depending on the state of the controller,
 * continue initialisation, or acknowledge command and response
 * interrupts, and process responses.
 */
udaintr(ctlr)
	int ctlr;
{
	register struct uba_ctlr *um = udaminfo[ctlr];
	register struct uda_softc *sc = &uda_softc[ctlr];
	register struct udadevice *udaddr = (struct udadevice *) um->um_addr;
	register struct uda *ud;
	register struct mscp *mp;
	register int i;
#if	MACH
	register retries;
#endif	MACH

	sc->sc_wticks = 0;	/* reset interrupt watchdog */

	/*
	 * Combinations during steps 1, 2, and 3: STEPnMASK
	 * corresponds to which bits should be tested;
	 * STEPnGOOD corresponds to the pattern that should
	 * appear after the interrupt from STEPn initialisation.
	 * All steps test the bits in ALLSTEPS.
	 */
#define	ALLSTEPS	(UDA_ERR | UDA_STEP4 | UDA_STEP3 | UDA_STEP2 | \
			 UDA_STEP1 | UDA_IE)

#define	STEP1MASK	(ALLSTEPS | UDA_NCNRMASK)
#define	STEP1GOOD	(UDA_STEP2 | UDA_IE | (NCMDL2 << 3) | NRSPL2)

#define	STEP2MASK	(ALLSTEPS | UDA_IVECMASK)
#define	STEP2GOOD	(UDA_STEP3 | UDA_IE | (sc->sc_ivec >> 2))

#if	MACH
/*  
 *  The 4.3 driver didn't include the UDA_IE bit in the mask at this point and
 *  more importantly leaving it in breaks with at least the DILOG DQ656
 *  controller.
 */
#define	STEP3MASK	(ALLSTEPS &~ UDA_IE)
#else	MACH
#define	STEP3MASK	ALLSTEPS
#endif	MACH
#define	STEP3GOOD	UDA_STEP4

	switch (sc->sc_state) {

	case ST_IDLE:
		/*
		 * Ignore unsolicited interrupts.
		 */
		log(LOG_WARNING, "uda%d: stray intr\n", ctlr);
		return;

	case ST_STEP1:
		/*
		 * Begin step two initialisation.
		 */
		if ((udaddr->udasa & STEP1MASK) != STEP1GOOD) {
			i = 1;
#if	MACH
                        retries = 0;
                        while ((udaddr->udasa & STEP1MASK) != STEP1GOOD &&
                                retries < MAX_RETRY) {
                            retries++;
                            printf("uda%d: init step %d failed, retrying...\n",
                                   ctlr,i);
			    DELAY(100);
			}

initfailed:	    if (retries > MAX_RETRY) {
#else	MACH
initfailed:
#endif	MACH
			printf("uda%d: init step %d failed, sa=%b\n",
				ctlr, i, udaddr->udasa, udasr_bits);
			sc->sc_state = ST_IDLE;
			if (sc->sc_flags & SC_DOWAKE) {
				sc->sc_flags &= ~SC_DOWAKE;
#ifdef	MACH_KERNEL
				thread_wakeup((event_t)sc);
#else	MACH_KERNEL
				wakeup((caddr_t) sc);
#endif	MACH_KERNEL
			}
			return;
#if	MACH
		    }
#endif	MACH
		}
#if	NBI > 0
		if (sc->kdb50) ((struct kdb50device *)udaddr)
		      ->kdbwr = (int) &sc->sc_uda->uda_ca.ca_rspdsc[0] |
			(cpu == VAX_780 || cpu == VAX_8600 ? UDA_PI : 0);
		else
#endif	NBI > 0
		udaddr->udasa = (int) &sc->sc_uda->uda_ca.ca_rspdsc[0] |
			(cpu == VAX_780 || cpu == VAX_8600 ? UDA_PI : 0);
		sc->sc_state = ST_STEP2;
		return;

	case ST_STEP2:
		/*
		 * Begin step 3 initialisation.
		 */
		if ((udaddr->udasa & STEP2MASK) != STEP2GOOD) {
			i = 2;
#if	MACH
                        retries = 0;
                        while ((udaddr->udasa & STEP2MASK) != STEP2GOOD &&
                                retries < MAX_RETRY) {
                            retries++;
                            printf("uda%d: init step %d failed, retrying...\n",
                                   ctlr,i);
			    DELAY(100);
			}

                        if (retries > MAX_RETRY)
#endif	MACH
			goto initfailed;
		}
#if	NBI > 0
		if (sc->kdb50) ((struct kdb50device *)udaddr)
		      ->kdbwr = ((int) &sc->sc_uda->uda_ca.ca_rspdsc[0]) >> 16;
		else
#endif	NBI > 0
		udaddr->udasa = ((int) &sc->sc_uda->uda_ca.ca_rspdsc[0]) >> 16;
		sc->sc_state = ST_STEP3;
		return;

	case ST_STEP3:
		/*
		 * Set controller characteristics (finish initialisation).
		 */
		if ((udaddr->udasa & STEP3MASK) != STEP3GOOD) {
			i = 3;
#if	MACH
                        retries = 0;
                        while ((udaddr->udasa & STEP3MASK) != STEP3GOOD &&
                                retries < MAX_RETRY) {
                            retries++;
                            printf("uda%d: init step %d failed, retrying...\n",
                                   ctlr,i);
			    DELAY(100);
                        }

                        if (retries > MAX_RETRY)
#endif	MACH
			goto initfailed;
		}
		i = udaddr->udasa & 0xff;
		if (i != sc->sc_micro) {
			sc->sc_micro = i;
			printf("uda%d: version %d model %d\n",
				ctlr, i & 0xf, i >> 4);
		}

		/*
		 * Present the burst size, then remove it.  Why this
		 * should be done this way, I have no idea.
		 *
		 * Note that this assumes udaburst[ctlr] > 0.
		 */
#if	NBI > 0
		if (sc->kdb50) {
		    ((struct kdb50device *)udaddr)
		      ->kdbwr = UDA_GO | (udaburst[ctlr] - 1) << 2;
		    ((struct kdb50device *)udaddr)
		      ->kdbwr = UDA_GO;
		} else {
#endif	NBI > 0
		udaddr->udasa = UDA_GO | (udaburst[ctlr] - 1) << 2;
		udaddr->udasa = UDA_GO;
#if	NBI > 0
		}
#endif	NBI > 0
		printf("uda%d: DMA burst size set to %d\n",
			ctlr, udaburst[ctlr]);

		udainitds(ctlr);	/* initialise data structures */

		/*
		 * Before we can get a command packet, we need some
		 * credits.  Fake some up to keep mscp_getcp() happy,
		 * get a packet, and cancel all credits (the right
		 * number should come back in the response to the
		 * SCC packet).
		 */
		sc->sc_mi.mi_credits = MSCP_MINCREDITS + 1;
		mp = mscp_getcp(&sc->sc_mi, MSCP_DONTWAIT);
		if (mp == NULL)	/* `cannot happen' */
			panic("udaintr");
		sc->sc_mi.mi_credits = 0;
		mp->mscp_opcode = M_OP_SETCTLRC;
		/*
		 * WHICH OF THE FOLLOWING ARE REQUIRED??
		 * IT SURE WOULD BE NICE IF DEC SOLD DOCUMENTATION
		 * FOR THEIR OWN CONTROLLERS.
		 */
		mp->mscp_unit = 0;
		mp->mscp_flags = 0;
		mp->mscp_modifier = 0;
		mp->mscp_seq.seq_bytecount = 0;
		mp->mscp_seq.seq_buffer = 0;
		mp->mscp_sccc.sccc_errlgfl = 0;
		mp->mscp_sccc.sccc_copyspd = 0;
		mp->mscp_sccc.sccc_ctlrflags = M_CF_ATTN | M_CF_MISC |
			M_CF_THIS;
		*mp->mscp_addr |= MSCP_OWN | MSCP_INT;
		i = udaddr->udaip;
		sc->sc_state = ST_SETCHAR;
		return;

	case ST_SETCHAR:
	case ST_RUN:
		/*
		 * Handle Set Ctlr Characteristics responses and operational
		 * responses (via mscp_dorsp).
		 */
		break;

	default:
		printf("uda%d: driver bug, state %d\n", ctlr, sc->sc_state);
		panic("udastate");
	}

	if (udaddr->udasa & UDA_ERR) {	/* ctlr fatal error */
		udasaerror(um);
		return;
	}

	ud = &uda[ctlr];

	/*
	 * Handle buffer purge requests.
	 * I have never seen these to work usefully, thus the log().
	 */
	if (ud->uda_ca.ca_bdp) {
		log(LOG_DEBUG, "uda%d: purge bdp %d\n",
			ctlr, ud->uda_ca.ca_bdp);
		UBAPURGE(um->um_hd->uh_uba, ud->uda_ca.ca_bdp);
		ud->uda_ca.ca_bdp = 0;
#if	NBI > 0
		if (sc->kdb50) ((struct kdb50device *)udaddr)
		      ->kdbwr = 0;	/* signal purge complete */
		else
#endif	NBI > 0
		udaddr->udasa = 0;	/* signal purge complete */
	}

	/*
	 * Check for response and command ring transitions.
	 */
	if (ud->uda_ca.ca_rspint) {
		ud->uda_ca.ca_rspint = 0;
		mscp_dorsp(&sc->sc_mi);
	}
	if (ud->uda_ca.ca_cmdint) {
		ud->uda_ca.ca_cmdint = 0;
		MSCP_DOCMD(&sc->sc_mi);
	}
	udastart(um);
}

/*
 * Initialise the various data structures that control the UDA50.
 */
udainitds(ctlr)
	int ctlr;
{
	register struct uda *ud = &uda[ctlr];
	register struct uda *uud = uda_softc[ctlr].sc_uda;
	register struct mscp *mp;
	register int i;

	for (i = 0, mp = ud->uda_rsp; i < NRSP; i++, mp++) {
		ud->uda_ca.ca_rspdsc[i] = MSCP_OWN | MSCP_INT |
			(long) &uud->uda_rsp[i].mscp_cmdref;
		mp->mscp_seq.seq_addr = &ud->uda_ca.ca_rspdsc[i];
		mp->mscp_msglen = MSCP_MSGLEN;
	}
	for (i = 0, mp = ud->uda_cmd; i < NCMD; i++, mp++) {
		ud->uda_ca.ca_cmddsc[i] = MSCP_INT |
			(long) &uud->uda_cmd[i].mscp_cmdref;
		mp->mscp_seq.seq_addr = &ud->uda_ca.ca_cmddsc[i];
		mp->mscp_msglen = MSCP_MSGLEN;
	}
}

/*
 * Handle an error datagram.  All we do now is decode it.
 */
udadgram(um, mp)
	struct uba_ctlr *um;
	struct mscp *mp;
{

	mscp_decodeerror(um, mp);
}

/*
 * The Set Controller Characteristics command finished.
 * Record the new state of the controller.
 */
udactlrdone(um, mp)
	register struct uba_ctlr *um;
	struct mscp *mp;
{
	register struct uda_softc *sc = &uda_softc[um->um_ctlr];

	if ((mp->mscp_status & M_ST_MASK) == M_ST_SUCCESS)
		sc->sc_state = ST_RUN;
	else {
		printf("uda%d: SETCTLRC failed: ",
			um->um_ctlr, mp->mscp_status);
		mscp_printevent(mp);
		sc->sc_state = ST_IDLE;
	}
	um->um_tab.b_active = 0;
	if (sc->sc_flags & SC_DOWAKE) {
		sc->sc_flags &= ~SC_DOWAKE;
#ifdef	MACH_KERNEL
		thread_wakeup((event_t) sc);
#else	MACH_KERNEL
		wakeup((caddr_t) sc);
#endif	MACH_KERNEL
	}
}

/*
 * Received a response from an as-yet unconfigured drive.  Configure it
 * in, if possible.
 */
udaunconf(um, mp)
	struct uba_ctlr *um;
	register struct mscp *mp;
{

	/*
	 * If it is a slave response, copy it to udaslavereply for
	 * udaslave() to look at.
	 */
	if (mp->mscp_opcode == (M_OP_GETUNITST | M_OP_END) &&
	    (uda_softc[um->um_ctlr].sc_flags & SC_INSLAVE) != 0) {
		udaslavereply = *mp;
		return (MSCP_DONE);
	}

	/*
	 * Otherwise, it had better be an available attention response.
	 */
	if (mp->mscp_opcode != M_OP_AVAILATTN)
		return (MSCP_FAILED);

	/* do what autoconf does */
	return (MSCP_FAILED);	/* not yet, arwhite, not yet */
}

/*
 * A drive came on line.  Check its type and size.  Return DONE if
 * we think the drive is truly on line.  In any case, awaken anyone
 * sleeping on the drive on-line-ness.
 */
udaonline(ui, mp)
	register struct uba_device *ui;
	struct mscp *mp;
{
	register int type;

#ifdef	MACH_KERNEL
	thread_wakeup((event_t) &ui->ui_flags);
#else	MACH_KERNEL
	wakeup((caddr_t) &ui->ui_flags);
#endif	MACH_KERNEL
	if ((mp->mscp_status & M_ST_MASK) != M_ST_SUCCESS) {
		printf("uda%d: attempt to bring ra%d on line failed: ",
			ui->ui_ctlr, ui->ui_unit);
		mscp_printevent(mp);
		return (MSCP_FAILED);
	}

#if	MACH
	/*
	 *  Correct RQDX3 drive type 19 botch.
 	 */
	type = udafixtype(&uda_softc[ui->ui_ctlr], 
			  (int)mp->mscp_onle.onle_drivetype,
			  (int)mp->mscp_onle.onle_mediaid);
#else	MACH
	type = mp->mscp_onle.onle_drivetype;
#endif	MACH
	if (type >= NTYPES || udatypes[type].ut_name == 0) {
		printf("uda%d: ra%d: unknown type %d\n",
			ui->ui_ctlr, ui->ui_unit, type);
		return (MSCP_FAILED);
	}
#if GYRE			/* special partition hack */
	if (ISCDC(&uda_softc[ui->ui_ctlr]))
		type = CDCTYPE;
#endif
	/*
	 * Note any change of types.  Not sure if we should do
	 * something special about them, or if so, what....
	 */
#if	MACH
	type = udaadjtype(&uda_softc[ui->ui_ctlr],
			  type,
			  (int)mp->mscp_onle.onle_unitsize);
#endif	MACH
	if (type != ui->ui_type) {
		printf("ra%d: changed types! was %s\n",
			ui->ui_unit, udatypes[ui->ui_type].ut_name);
		ui->ui_type = type;
	}
	ra_dsize[ui->ui_unit] = (daddr_t) mp->mscp_onle.onle_unitsize;
#if	MACH
	printf("ra%d: %s (", ui->ui_unit, udatypes[type].ut_name);
	uda_decode_media(mp->mscp_guse.guse_mediaid);
        printf(",type %d), %d sectors\n", mp->mscp_guse.guse_drivetype,
 		ra_dsize[ui->ui_unit]);
#else	MACH
	printf("ra%d: %s, size = %d sectors\n",
		ui->ui_unit, udatypes[type].ut_name, ra_dsize[ui->ui_unit]);
#endif	MACH
	return (MSCP_DONE);
}

/*
 * We got some (configured) unit's status.  Return DONE if it succeeded.
 */
udagotstatus(ui, mp)
	register struct uba_device *ui;
	register struct mscp *mp;
{

	if ((mp->mscp_status & M_ST_MASK) != M_ST_SUCCESS) {
		printf("uda%d: attempt to get status for ra%d failed: ",
			ui->ui_ctlr, ui->ui_unit);
		mscp_printevent(mp);
		return (MSCP_FAILED);
	}
#if	MACH
	if (uda_printstatus)
#endif	MACH
	/* need to record later for bad block forwarding - for now, print */
	printf("\
ra%d: unit %d, nspt %d, group %d, ngpc %d, rctsize %d, nrpt %d, nrct %d\n",
		ui->ui_unit, mp->mscp_unit,
		mp->mscp_guse.guse_nspt, mp->mscp_guse.guse_group,
		mp->mscp_guse.guse_ngpc, mp->mscp_guse.guse_rctsize,
		mp->mscp_guse.guse_nrpt, mp->mscp_guse.guse_nrct);
	return (MSCP_DONE);
}

/*
 * A transfer failed.  We get a chance to fix or restart it.
 * Need to write the bad block forwaring code first....
 */
/*ARGSUSED*/
udaioerror(ui, mp, bp)
	register struct uba_device *ui;
	register struct mscp *mp;
	struct buf *bp;
{

#if	MACH
	if (uda_host_access_retry
	    &&
	    (mp->mscp_opcode == (M_OP_END|M_OP_WRITE)
	     ||
	     mp->mscp_opcode == (M_OP_END|M_OP_READ))
	    &&
	    (mp->mscp_status&M_ST_MASK) == M_ST_HOSTBUFERR) {
		harderr(bp, ui->ui_driver->ud_dname);
		printf("retrying host buffer access error\n");
		udastrat1(bp);
		return (MSCP_RESTARTED);
	}
#endif	MACH
	if (mp->mscp_flags & M_EF_BBLKR) {
		/*
		 * A bad block report.  Eventually we will
		 * restart this transfer, but for now, just
		 * log it and give up.
		 */
		log(LOG_ERR, "ra%d: bad block report: %d%s\n",
			ui->ui_unit, mp->mscp_seq.seq_lbn,
			mp->mscp_flags & M_EF_BBLKU ? " + others" : "");
	} else {
		/*
		 * What the heck IS a `serious exception' anyway?
		 * IT SURE WOULD BE NICE IF DEC SOLD DOCUMENTATION
		 * FOR THEIR OWN CONTROLLERS.
		 */
		if (mp->mscp_flags & M_EF_SEREX)
			log(LOG_ERR, "ra%d: serious exception reported\n",
				ui->ui_unit);
	}
	return (MSCP_FAILED);
}

/*
 * A replace operation finished.
 */
/*ARGSUSED*/
udareplace(ui, mp)
	struct uba_device *ui;
	struct mscp *mp;
{

	panic("udareplace");
}

/*
 * A bad block related operation finished.
 */
/*ARGSUSED*/
udabb(ui, mp, bp)
	struct uba_device *ui;
	struct mscp *mp;
	struct buf *bp;
{

	panic("udabb");
}


/*
 * Raw read request.
 */
udaread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register int unit = udaunit(dev);

	if (unit >= NRA)
		return (ENXIO);
#if	MACH_KERNEL
	{
	    register int error;

	    io_grab_master();
	    error = block_io(udastrategy, minphys, uio);
	    io_release_master();
	    return (error);
	}
#else	MACH_KERNEL
	return (physio(udastrategy, &rudabuf[unit], dev, B_READ,
		minphys, uio));
#endif	MACH_KERNEL
}

/*
 * Raw write request.
 */
udawrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register int unit = udaunit(dev);

	if (unit >= NRA)
		return (ENXIO);
#if	MACH_KERNEL
	{
	    register int error;

	    io_grab_master();
	    error = block_io(udastrategy, minphys, uio);
	    io_release_master();
	    return (error);
	}
#else	MACH_KERNEL
	return (physio(udastrategy, &rudabuf[unit], dev, B_WRITE,
		minphys, uio));
#endif	MACH_KERNEL
}

#ifdef	MACH_KERNEL
/*
 * Get status routine
 */
udgetstat(dev, flavor, status, count)
	dev_t	dev;
	int	*status, *count;
{
	register int unit = udaunit(dev);

	if (flavor == DEV_GET_SIZE) {
		unsigned int length;

		length = ra_dsize[unit];
		status[DEV_GET_SIZE_DEVICE_SIZE] = length * DEV_BSIZE;
		status[DEV_GET_SIZE_RECORD_SIZE] = DEV_BSIZE;
		*count = DEV_GET_SIZE_COUNT;
		
		return D_SUCCESS;
	} else return D_INVALID_OPERATION;
}

#else	/*MACH_KERNEL*/
/*
 * I/O controls.  Not yet!
 */
udaioctl(dev, cmd, flag, data)
	dev_t dev;
	int cmd, flag;
	caddr_t data;
{
	int error = 0;
	register int unit = udaunit(dev);

	if (unit >= NRA || uddinfo[unit] == NULL)
		return (ENXIO);

	switch (cmd) {

	case UDAIOCREPLACE:
		/*
		 * Initiate bad block replacement for the given LBN.
		 * (Should we allow modifiers?)
		 */
		error = EOPNOTSUPP;
		break;

	case UDAIOCGMICRO:
		/*
		 * Return the microcode revision for the UDA50 running
		 * this drive.
		 */
		*(int *) data = uda_softc[uddinfo[unit]->ui_ctlr].sc_micro;
		break;

	case UDAIOCGSIZE:
		/*
		 * Return the size (in 512 byte blocks) of this
		 * disk drive.
		 */
		*(daddr_t *) data = ra_dsize[unit];
		break;

	default:
		error = EINVAL;
		break;
	}
	return (error);
}
#endif	/*MACH_KERNEL*/

/*
 * A Unibus reset has occurred on UBA uban.  Reinitialise the controller(s)
 * on that Unibus, and requeue outstanding I/O.
 */
udareset(uban)
	int uban;
{
	register struct uba_ctlr *um;
	register struct uda_softc *sc;
	register int ctlr;

	for (ctlr = 0, sc = uda_softc; ctlr < NUDA; ctlr++, sc++) {
		if ((um = udaminfo[ctlr]) == NULL || um->um_ubanum != uban ||
		    um->um_alive == 0)
			continue;
		printf(" uda%d", ctlr);

		/*
		 * Our BDP (if any) is gone; our command (if any) is
		 * flushed; the device is no longer mapped; and the
		 * UDA50 is not yet initialised.
		 */
		if (um->um_bdp) {
			printf("<%d>", (um->um_bdp >> 28) & 15);
			um->um_bdp = 0;
		}
		um->um_ubinfo = 0;
		um->um_cmd = 0;
		sc->sc_flags &= ~SC_MAPPED;
		sc->sc_state = ST_IDLE;

		/* reset queues and requeue pending transfers */
		mscp_requeue(&sc->sc_mi);

		/*
		 * If it fails to initialise we will notice later and
		 * try again (and again...).  Do not call udastart()
		 * here; it will be done after the controller finishes
		 * initialisation.
		 */
		if (udainit(ctlr))
			printf(" (hung)");
	}
}

/*
 * Watchdog timer:  If the controller is active, and no interrupts
 * have occurred for 30 seconds, assume it has gone away.
 */
udawatch()
{
	register int i, unit;
	register struct uba_ctlr *um;
	register struct uda_softc *sc;

	timeout(udawatch, (caddr_t) 0, hz);	/* every second */
	for (i = 0, sc = uda_softc; i < NUDA; i++, sc++) {
		if ((um = udaminfo[i]) == 0 || um->um_alive == 0)
			continue;
		if (um->um_tab.b_active ||
		    sc->sc_mi.mi_wtab.av_forw != &sc->sc_mi.mi_wtab ||
		    sc->sc_state != ST_IDLE && sc->sc_state != ST_RUN)
			goto active;
		for (unit = 0; unit < NRA; unit++)
			if (udautab[unit].b_active &&
			    udadinfo[unit]->ui_mi == um)
				goto active;
		sc->sc_wticks = 0;
		continue;
active:
		if (++sc->sc_wticks >= 30) {
			sc->sc_wticks = 0;
			printf("uda%d: lost interrupt\n", i);
			ubareset(um->um_ubanum);
		}
	}
}

#if	MACH_KERNEL
#else	MACH_KERNEL
/*
 * Do a panic dump.  We set up the controller for one command packet
 * and one response packet, for which we use `struct uda1'.
 */
struct	uda1 {
	struct	uda1ca uda1_ca;	/* communications area */
	struct	mscp uda1_rsp;	/* response packet */
	struct	mscp uda1_cmd;	/* command packet */
} uda1;

#define	DBSIZE	32		/* dump 16K at a time */

udadump(dev)
	dev_t dev;
{
	struct udadevice *udaddr;
	struct uda1 *ud_ubaddr;
	char *start;
	int num, blk, unit, maxsz, blkoff, reg;
	register struct uba_regs *uba;
	register struct uba_device *ui;
	register struct uda1 *ud;
	register struct pte *io;
	register int i;

	/*
	 * Make sure the device is a reasonable place on which to dump.
	 */
	unit = udaunit(dev);
	if (unit >= NRA)
		return (ENXIO);
#define	phys(cast, addr)	((cast) ((int) addr & 0x7fffffff))
	ui = phys(struct uba_device *, udadinfo[unit]);
	if (ui == NULL || ui->ui_alive == 0)
		return (ENXIO);

	/*
	 * Find and initialise the UBA; get the physical address of the
	 * device registers, and of communications area and command and
	 * response packet.
	 */
	uba = phys(struct uba_hd *, ui->ui_hd)->uh_physuba;
	ubainit(uba);
	udaddr = (struct udadevice *) ui->ui_physaddr;
	ud = phys(struct uda1 *, &uda1);

	/*
	 * Map the ca+packets into Unibus I/O space so the UDA50 can get
	 * at them.  Use the registers at the end of the Unibus map (since
	 * we will use the registers at the beginning to map the memory
	 * we are dumping).
	 */
	num = btoc(sizeof (struct uda1)) + 1;
	reg = NUBMREG - num;
	io = &uba->uba_map[reg];
	for (i = 0; i < num; i++)
		*(int *)io++ = UBAMR_MRV | (btop(ud) + i);
	ud_ubaddr = (struct uda1 *) (((int) ud & PGOFSET) | (reg << 9));

#if	NBI > 0
	if (cpu == VAX_820) {
		printf("someone please fix dumps on 8200!\n");
		return(EINVAL);
	}
#endif	NBI > 0
	/*
	 * Initialise the controller, with one command and one response
	 * packet.
	 */
	udaddr->udaip = 0;
	if (udadumpwait(udaddr, UDA_STEP1))
		return (EFAULT);
	udaddr->udasa = UDA_ERR;
	if (udadumpwait(udaddr, UDA_STEP2))
		return (EFAULT);
	udaddr->udasa = (int) &ud_ubaddr->uda1_ca.ca_rspdsc;
	if (udadumpwait(udaddr, UDA_STEP3))
		return (EFAULT);
	udaddr->udasa = ((int) &ud_ubaddr->uda1_ca.ca_rspdsc) >> 16;
	if (udadumpwait(udaddr, UDA_STEP4))
		return (EFAULT);
	uda_softc[ui->ui_ctlr].sc_micro = udaddr->udasa & 0xff;
	udaddr->udasa = UDA_GO;

	/*
	 * Set up the command and response descriptor, then set the
	 * controller characteristics and bring the drive on line.
	 * Note that all uninitialised locations in uda1_cmd are zero.
	 */
	ud->uda1_ca.ca_rspdsc = (long) &ud_ubaddr->uda1_rsp.mscp_cmdref;
	ud->uda1_ca.ca_cmddsc = (long) &ud_ubaddr->uda1_cmd.mscp_cmdref;
	/* ud->uda1_cmd.mscp_sccc.sccc_ctlrflags = 0; */
	/* ud->uda1_cmd.mscp_sccc.sccc_version = 0; */
	if (udadumpcmd(M_OP_SETCTLRC, ud, ui))
		return (EFAULT);
	ud->uda1_cmd.mscp_unit = ui->ui_slave;
	if (udadumpcmd(M_OP_ONLINE, ud, ui))
		return (EFAULT);

	/*
	 * Pick up the drive type from the on line end packet;
	 * convert that to a dump area size and a disk offset.
	 */
#if	MACH
	/*
	 *  Correct RQDX3 drive type 19 botch.
	 */
	i = udafixtype(&uda_softc[ui->ui_ctlr], 
			ud->uda1_rsp.mscp_onle.onle_drivetype,
			ud->uda1_rsp.mscp_onle.onle_mediaid);
#else	MACH
	i = ud->uda1_rsp.mscp_onle.onle_drivetype;
#endif	MACH
	if (i >= NTYPES || udatypes[i].ut_name == 0) {
		printf("disk type %d unknown\ndump ");
		return (EINVAL);
	}
#if GYRE
	if (ISCDC(&uda_softc[ui->ui_ctlr]))
		i = CDCTYPE;
#endif
#if	MACH
	i = udaadjtype(&uda_softc[ui->ui_ctlr],
			i,
			(int)ud->uda1_rsp.mscp_onle.onle_unitsize);
#endif	MACH
	printf("on %s ", udatypes[i].ut_name);
	maxsz = udatypes[i].ut_sizes[udapart(dev)].nblocks;
	blkoff = udatypes[i].ut_sizes[udapart(dev)].blkoff;

	/*
	 * Dump all of physical memory, or as much as will fit in the
	 * space provided.
	 */
	start = 0;
	num = maxfree;
	if (dumplo < 0)
		return (EINVAL);
	if (dumplo + num >= maxsz)
		num = maxsz - dumplo;
	blkoff += dumplo;

	/*
	 * Write out memory, DBSIZE pages at a time.
	 * N.B.: this code depends on the fact that the sector
	 * size == the page size.
	 */
	while (num > 0) {
		blk = num > DBSIZE ? DBSIZE : num;
		io = uba->uba_map;
		/*
		 * Map in the pages to write, leaving an invalid entry
		 * at the end to guard against wild Unibus transfers.
		 * Then do the write.
		 */
		for (i = 0; i < blk; i++)
			*(int *) io++ = UBAMR_MRV | (btop(start) + i);
		*(int *) io = 0;
		ud->uda1_cmd.mscp_unit = ui->ui_slave;
		ud->uda1_cmd.mscp_seq.seq_lbn = btop(start) + blkoff;
		ud->uda1_cmd.mscp_seq.seq_bytecount = blk << PGSHIFT;
		if (udadumpcmd(M_OP_WRITE, ud, ui))
			return (EIO);
		start += blk << PGSHIFT;
		num -= blk;
	}
	return (0);		/* made it! */
}

/*
 * Wait for some of the bits in `bits' to come on.  If the error bit
 * comes on, or ten seconds pass without response, return true (error).
 */
udadumpwait(udaddr, bits)
	register struct udadevice *udaddr;
	register int bits;
{
#if	MACH
	register int timo;

	todr_prime();			/* prime TODR emulation */
 	timo = todr() + 1000;
#else	MACH
	register int timo = todr() + 1000;
#endif	MACH

	while ((udaddr->udasa & bits) == 0) {
		if (udaddr->udasa & UDA_ERR) {
			printf("udasa=%b\ndump ", udaddr->udasa, udasr_bits);
			return (1);
		}
		if (todr() >= timo) {
			printf("timeout\ndump ");
			return (1);
		}
	}
	return (0);
}

/*
 * Feed a command to the UDA50, wait for its response, and return
 * true iff something went wrong.
 */
udadumpcmd(op, ud, ui)
	int op;
	register struct uda1 *ud;
	struct uba_device *ui;
{
	register struct udadevice *udaddr;
	register int n;
#define mp (&ud->uda1_rsp)

	udaddr = (struct udadevice *) ui->ui_physaddr;
	ud->uda1_cmd.mscp_opcode = op;
	ud->uda1_cmd.mscp_msglen = MSCP_MSGLEN;
	ud->uda1_rsp.mscp_msglen = MSCP_MSGLEN;
	ud->uda1_ca.ca_rspdsc |= MSCP_OWN | MSCP_INT;
	ud->uda1_ca.ca_cmddsc |= MSCP_OWN | MSCP_INT;
	if (udaddr->udasa & UDA_ERR) {
		printf("udasa=%b\ndump ", udaddr->udasa, udasr_bits);
		return (1);
	}
	n = udaddr->udaip;
#if	MACH
	todr_prime();			/* prime TODR emulation */
#endif	MACH
	n = todr() + 1000;
	for (;;) {
		if (todr() > n) {
			printf("timeout\ndump ");
			return (1);
		}
		if (ud->uda1_ca.ca_cmdint)
			ud->uda1_ca.ca_cmdint = 0;
		if (ud->uda1_ca.ca_rspint == 0)
			continue;
		ud->uda1_ca.ca_rspint = 0;
		if (mp->mscp_opcode == (op | M_OP_END))
			break;
		printf("\n");
		switch (MSCP_MSGTYPE(mp->mscp_msgtc)) {

		case MSCPT_SEQ:
			printf("sequential");
			break;

		case MSCPT_DATAGRAM:
			mscp_decodeerror(ui->ui_mi, mp);
			printf("datagram");
			break;

		case MSCPT_CREDITS:
			printf("credits");
			break;

		case MSCPT_MAINTENANCE:
			printf("maintenance");
			break;

		default:
			printf("unknown (type 0x%x)",
				MSCP_MSGTYPE(mp->mscp_msgtc));
			break;
		}
		printf(" ignored\ndump ");
		ud->uda1_ca.ca_rspdsc |= MSCP_OWN | MSCP_INT;
	}
	if ((mp->mscp_status & M_ST_MASK) != M_ST_SUCCESS) {
		printf("error: op 0x%x => 0x%x status 0x%x\ndump ", op,
			mp->mscp_opcode, mp->mscp_status);
		return (1);
	}
	return (0);
#undef mp
}

/*
 * Return the size of a partition, if known, or -1 if not.
 */
udasize(dev)
	dev_t dev;
{
	register int unit = udaunit(dev);
	register struct uba_device *ui;
	register struct size *st;

	if (unit >= NRA || (ui = udadinfo[unit]) == NULL || ui->ui_alive == 0)
		return (-1);
	st = &udatypes[ui->ui_type].ut_sizes[udapart(dev)];
	if (st->nblocks == -1) {
		int s = spl5();

		/*
		 * We need to have the drive on line to find the size
		 * of this particular partition.
		 * IS IT OKAY TO GO TO SLEEP IN THIS ROUTINE?
		 * (If not, better not page on one of these...)
		 */
		if ((ui->ui_flags & UNIT_ONLINE) == 0) {
			if (uda_bringonline(&uda_softc[unit], ui, 0)) {
				splx(s);
				return (-1);
			}
		}
		splx(s);
		if (st->blkoff > ra_dsize[unit])
			return (-1);
		return (ra_dsize[unit] - st->blkoff);
	}
	return (st->nblocks);
}
#endif	MACH_KERNEL
#endif
#if	MACH


/*
 *  The RQDX3 model 3 version 1 controller has been observed to return a drive
 *  type number of 19 for the RD53, RD52 and RX50.  We correct for this
 *  strangeness here by using the low 7 bits of the mediaid to distinguish the
 *  drives.
 */

udafixtype(sc, type, mediaid)
	register struct uda_softc *sc;
	int type;
	int mediaid;
{
	if (sc->sc_micro == 0x31 && type == 19)
		switch (mediaid&0x7f)
		{
			case 53: type = RD53TYPE; break;
			case 52: type = RD52TYPE; break;
			case 50: type = RX50TYPE; break;
		}
	return(type);
}


/*
 *  Adjust the drive type supplied by the controller to a more precise internal
 *  type, if possible, based on the disk size and controller microcode level.
 */

udaadjtype(sc, type, dsize)
	register struct uda_softc *sc;
	int type;
	int dsize;
{
	static struct {short type, xtype, micro;} xtypes[] =
	{
		{RA80TYPE1,	RA80CDC8TYPE},	
		{RA80TYPE1,	RA80CDC12TYPE},	
		{RA80TYPE1,	RA80DDTYPE},	
		{RA80TYPE1,	RA80DETYPE},	
		{RA80TYPE1,	RA80DFTYPE},	
		{RA80TYPE6,	RA80ETYPE},	
		{RA80TYPE6,	RA80FTYPE},	
		{RA80TYPE6,	RA80PTYPE},	
		{RA80TYPE6,	RA80PFTYPE},	
		{RA80TYPE6,	RA80WRENVTYPE},	
		{RA81TYPE,	RA81ETYPE},	
		{RA81TYPE,	RA81EDTYPE},	
		{RA81TYPE,	RA81EMTYPE},	
		{RA81TYPE,	RA81MTYPE},	
		{RA81TYPE,	RA81STYPE},	
	};
	register int i;

	for (i=0; i<(sizeof(xtypes)/sizeof(xtypes[0])); i++)
		if (xtypes[i].type == type
		    &&
		    udatypes[xtypes[i].xtype].ut_sizes[2].nblocks == dsize
		    &&
		    (xtypes[i].micro == 0 || xtypes[i].micro == sc->sc_micro))
			return(xtypes[i].xtype);

	return(type);
}


/*
 *  Fake mfpr(TODR) for 8800 and 630.
 */

int	ms10, usec;

todr_prime()
{
	ms10 = 0;		/* 10ms pseudo-clock */
	usec = 0;		/* usec pesduo-clock */
}

int
todr()
{
	int inc;

	switch (cpu)
	{
	    case VAX_630:
		inc = 12;	/* estimated usec/iteration? */
		goto common;
	    case VAX_8800:
		inc = 2;	/* estimated usec/iteration? */
		goto common;
	    common:
		usec += inc;
		if (usec > 10*1000)
		{
		    usec -= 10*1000;
		    ms10++;
		}
		return(ms10);
	    default:
		return(mfpr(TODR));
	}
}
#endif	MACH
