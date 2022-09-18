h15453
s 00001/00000/00088
d D 8.5 95/05/17 21:32:19 mckusick 15 14
c add definition for ability to produce a backtrace
e
s 00001/00000/00087
d D 8.4 94/01/05 09:49:44 mckusick 14 13
c add cpu_swapin (nothing needed)
e
s 00004/00014/00083
d D 8.3 93/12/10 17:43:54 mckusick 13 12
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00096
d D 8.2 93/09/23 16:44:42 bostic 12 11
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00095
d D 8.1 93/06/11 15:47:45 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00091
d D 5.8 93/06/10 21:56:58 cgd 10 9
c make a struct clockframe
e
s 00011/00000/00084
d D 5.7 93/05/21 18:39:27 mckusick 9 8
c add support for CTL_MACHDEP
e
s 00002/00002/00082
d D 5.6 92/10/11 10:11:57 bostic 8 7
c make kernel includes standard
e
s 00002/00000/00082
d D 5.5 92/02/05 17:16:41 mckusick 7 6
c add cpu_setstack
e
s 00004/00004/00078
d D 5.4 91/05/09 18:08:25 william 6 5
c last minute changes, updating present version
e
s 00068/00001/00014
d D 5.3 91/05/06 17:51:04 karels 5 4
c (mostly by william) update to current system, add cpu types
e
s 00001/00001/00014
d D 5.2 91/01/18 14:32:00 william 4 3
c fixed just which copyright notice is included.
e
s 00000/00000/00015
d D 5.1 90/04/24 19:13:07 william 3 2
c 1st Berkeley Release
e
s 00010/00050/00005
d D 1.2 90/04/24 18:56:27 william 2 1
c 1st Berkeley Release
e
s 00055/00000/00000
d D 1.1 90/03/12 15:47:47 bill 1 0
c date and time created 90/03/12 15:47:47 by bill
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 5

E 5
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 2
 *
D 2
 *	@(#)cpu.h	1.2 (Berkeley) 3/13/87
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 4
 * %sccs.include.noredist.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
E 2
 */

I 5
/*
 * Definitions unique to i386 cpu support.
 */
D 8
#include "machine/frame.h"
#include "machine/segments.h"
E 8
I 8
#include <machine/frame.h>
#include <machine/segments.h>
E 8

/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
D 6
#undef	COPY_SIGCODE		/* copy sigcode above user stack in exec */
E 6
I 6
D 13
#undef	COPY_SIGCODE		/* don't copy sigcode above user stack in exec */
E 13
I 13
#undef	COPY_SIGCODE	/* don't copy sigcode above user stack in exec */
E 13
E 6

D 13
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
D 6
#define	NEED_FFS		/* don't need ffs function */
#define	NEED_BCMP		/* don't need bcmp function */
#define	NEED_STRLEN		/* don't need strlen function */
E 6
I 6
#define	NEED_FFS		/* need ffs function */
#define	NEED_BCMP		/* need bcmp function */
#define	NEED_STRLEN		/* need strlen function */
E 6

#define	cpu_exec(p)	/* nothing */
I 7
#define cpu_setstack(p, ap) \
	(p)->p_md.md_regs[SP] = ap
E 13
I 13
#define	cpu_exec(p)			/* nothing */
I 14
#define	cpu_swapin(p)			/* nothing */
E 14
#define cpu_setstack(p, ap)		(p)->p_md.md_regs[SP] = ap
#define cpu_set_init_frame(p, fp)	(p)->p_md.md_regs = fp
I 15
#define	BACKTRACE(p)			/* not implemented */
E 15
E 13
E 7

/*
 * Arguments to hardclock, softclock and gatherstats
 * encapsulate the previous machine state in an opaque
 * clockframe; for now, use generic intrframe.
 */
D 10
typedef struct intrframe clockframe;
E 10
I 10
struct clockframe {
	struct intrframe	cf_if;
};
E 10

D 10
#define	CLKF_USERMODE(framep)	(ISPL((framep)->if_cs) == SEL_UPL)
#define	CLKF_BASEPRI(framep)	((framep)->if_ppl == 0)
#define	CLKF_PC(framep)		((framep)->if_eip)
E 10
I 10
#define	CLKF_USERMODE(framep)	(ISPL((framep)->cf_if.if_cs) == SEL_UPL)
#define	CLKF_BASEPRI(framep)	((framep)->cf_if.if_ppl == 0)
#define	CLKF_PC(framep)		((framep)->cf_if.if_eip)
E 10

E 5
D 2
/*
 * Assorted definitions unique to TAHOE CPU support.
 */

#define	uncache(v)	mtpr(PDCS, (caddr_t)(v))
#define	movow(a,w)	_movow((u_short *)(a), (u_short)(w))
#define	movob(a,b)	_movob((u_char *)(a), (u_char)(b))

E 2
#define	resettodr()	/* no todr to set */

I 5
/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
#define	need_resched()	{ want_resched++; aston(); }

/*
 * Give a profiling tick to the current process from the softclock
 * interrupt.  On tahoe, request an ast to send us through trap(),
 * marking the proc as needing a profiling tick.
 */
D 12
#define	profile_tick(p, framep)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 12
I 12
#define	profile_tick(p, framep)	{ (p)->p_flag |= P_OWEUPC; aston(); }
E 12

/*
 * Notify the current process (p) that it has a signal pending,
 * process as soon as possible.
 */
#define	signotify(p)	aston()

#define aston() (astpending++)

int	astpending;		/* need to trap before returning to user mode */
int	want_resched;		/* resched() was called */

/*
 * Kinds of processor
 */

#define	CPU_386SX	0
#define	CPU_386		1
#define	CPU_486SX	2
#define	CPU_486		3
#define	CPU_586		4
I 9

/*
 * CTL_MACHDEP definitions.
 */
#define	CPU_CONSDEV		1	/* dev_t: console terminal device */
#define	CPU_MAXID		2	/* number of valid machdep ids */

#define CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
	{ "console_device", CTLTYPE_STRUCT }, \
}
E 9
E 5
D 2
#define	MAXCKEY	255		/* maximal allowed code key */
#define	MAXDKEY	255		/* maximal allowed data key */
#define	NCKEY	(MAXCKEY+1)	/* # code keys, including 0 (reserved) */
#define	NDKEY	(MAXDKEY+1)	/* # data keys, including 0 (reserved) */

#ifndef LOCORE
#ifdef KERNEL
char	ckey_cache[NCKEY];	/* 1 =>'s key i may be in code cache */
short	ckey_cnt[NCKEY];	/* code key reference count */
char	dkey_cache[NDKEY];	/* 1 =>'s key i may be in data cache */
short	dkey_cnt[NDKEY];	/* data key reference count */
#endif

/*
 * Statistics maintained for code and
 * data cache key allocations algorithms.
 */
struct	keystats {
	long	ks_avail;	/* number of keys currently unallocated */
	long	ks_dirty;	/* number of keys currently waiting for purge */
	long	ks_allocs;	/* number of keys allocated */
	long	ks_allocfree;	/* key allocated from free slot */
	long	ks_norefs;	/* key marked in use, but refcnt 0 */
	long	ks_taken;	/* key taken from single process */
	long	ks_shared;	/* key taken from multiple processes */
	long	ks_inval;	/* number of times keys exchanged */
};
#endif

long	*user_psl;		/* user mode psl for ast's */
int	intenable;		/* interrupts enable startup flag */
int	clk_enable;		/* clock enable startup flag */

/*
 * Enable realtime clock.
 */
#define	enablertclock()	(clk_enable = 1)
E 2
E 1
