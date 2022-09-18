h41935
s 00001/00000/00124
d D 8.3 95/05/17 21:33:36 mckusick 9 8
c add definition for ability to produce a backtrace
e
s 00001/00001/00123
d D 8.2 94/01/21 19:42:12 bostic 8 7
c typo
e
s 00002/00002/00122
d D 8.1 94/01/11 16:14:29 mckusick 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00123
d D 7.6 94/01/05 09:50:48 mckusick 6 5
c add cpu_swapin (nothing needed)
e
s 00004/00004/00119
d D 7.5 93/12/10 17:48:01 mckusick 5 4
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00122
d D 7.4 93/01/20 00:11:27 utashiro 4 3
c Use COPY_SIGCODE
e
s 00001/00001/00122
d D 7.3 92/12/17 02:58:17 utashiro 3 2
c make kernel includes standard
e
s 00013/00024/00110
d D 7.2 92/07/28 17:33:18 bostic 2 1
c update from Kazumasa Utashiro
e
s 00134/00000/00000
d D 7.1 92/06/04 16:03:04 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
D 8
 *	Regents of the University of California.  All rights reserved.
E 8
I 8
 *	The Regents of the University of California.  All rights reserved.
E 8
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell and Kazumasa Utashiro of Software Research
 * Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _CPU_H_
#define _CPU_H_

D 3
#include "machConst.h"
E 3
I 3
#include <machine/machConst.h>
E 3

/*
 * Exported definitions unique to pmax/mips cpu support.
 */

/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
D 4
#undef	COPY_SIGCODE		/* copy sigcode above user stack in exec */
E 4
I 4
#define	COPY_SIGCODE		/* copy sigcode above user stack in exec */
E 4

D 2
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
#define	NEED_FFS		/* don't need ffs function */
#undef	NEED_BCMP		/* don't need bcmp function */
#undef	NEED_STRLEN		/* don't need strlen function */

E 2
D 5
#define	cpu_exec(p)	(p->p_md.md_ss_addr = 0) /* init single step */
#define	cpu_wait(p)	/* nothing */
#define cpu_setstack(p, ap) \
	(p)->p_md.md_regs[SP] = ap
E 5
I 5
#define	cpu_exec(p)		(p->p_md.md_ss_addr = 0) /* init single step */
I 6
#define	cpu_swapin(p)		/* nothing */
E 6
#define	cpu_wait(p)		/* nothing */
#define cpu_setstack(p, ap)	(p)->p_md.md_regs[SP] = ap
#define cpu_set_init_frame(p, fp) (p)->p_md.md_regs = fp
I 9
#define	BACKTRACE(p)		/* not implemented */
E 9
E 5

/*
D 2
 * Arguments to hardclock, softclock and gatherstats
 * encapsulate the previous machine state in an opaque
 * clockframe;
E 2
I 2
 * Arguments to hardclock and gatherstats encapsulate the previous
 * machine state in an opaque clockframe.
E 2
 */
D 2
typedef struct intrframe {
	int	pc;
	int	ps;
} clockframe;
E 2
I 2
struct clockframe {
	int	pc;	/* program counter at time of interrupt */
	int	sr;	/* status register at time of interrupt */
};
E 2

D 2
#define	CLKF_USERMODE(framep)	((framep)->ps & MACH_SR_KU_PREV)
E 2
I 2
#define	CLKF_USERMODE(framep)	((framep)->sr & MACH_SR_KU_PREV)
E 2
#define	CLKF_BASEPRI(framep)	\
D 2
	(((framep)->ps & (MACH_INT_MASK | MACH_SR_INT_ENA_PREV)) == \
	(MACH_INT_MASK | MACH_SR_INT_ENA_PREV))
E 2
I 2
	((~(framep)->sr & (MACH_INT_MASK | MACH_SR_INT_ENA_PREV)) == 0)
E 2
#define	CLKF_PC(framep)		((framep)->pc)
I 2
#define	CLKF_INTR(framep)	(0)
E 2

/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
#define	need_resched()	{ want_resched = 1; aston(); }

/*
D 2
 * Give a profiling tick to the current process from the softclock
 * interrupt.
E 2
I 2
 * Give a profiling tick to the current process when the user profiling
 * buffer pages are invalid.  On the PMAX, request an ast to send us
 * through trap, marking the proc as needing a profiling tick.
E 2
 */
D 2
#define	profile_tick(p, framep) \
	addupc((framep)->pc, &p->p_stats->p_prof, 1);
E 2
I 2
#define	need_proftick(p)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 2

/*
 * Notify the current process (p) that it has a signal pending,
 * process as soon as possible.
 */
#define	signotify(p)	aston()

#define aston()		(astpending = 1)

int	astpending;	/* need to trap before returning to user mode */
int	want_resched;	/* resched() was called */

/*
 * CPU identification, from PRID register.
 */
union cpuprid {
	int	cpuprid;
	struct {
#if BYTE_ORDER == BIG_ENDIAN
		u_int	pad1:16;	/* reserved */
		u_int	cp_imp:8;	/* implementation identifier */
		u_int	cp_majrev:4;	/* major revision identifier */
		u_int	cp_minrev:4;	/* minor revision identifier */
#else
		u_int	cp_minrev:4;	/* minor revision identifier */
		u_int	cp_majrev:4;	/* major revision identifier */
		u_int	cp_imp:8;	/* implementation identifier */
		u_int	pad1:16;	/* reserved */
#endif
	} cpu;
};

/*
 * MIPS CPU types (cp_imp).
 */
#define	MIPS_R2000	0x01
#define	MIPS_R3000	0x02
#define	MIPS_R6000	0x03
#define	MIPS_R4000	0x04
#define	MIPS_R6000A	0x06

/*
 * MIPS FPU types
 */
#define	MIPS_R2010_FPU	0x02
#define	MIPS_R3010_FPU	0x03
#define	MIPS_R6010_FPU	0x04
#define	MIPS_R4000_FPU	0x05

struct intr_tab {
	void	(*func)();	/* pointer to interrupt routine */
	int	unit;		/* logical unit number */
};

#ifdef KERNEL
union	cpuprid cpu;
union	cpuprid fpu;
u_int	machDataCacheSize;
u_int	machInstCacheSize;
extern	struct intr_tab intr_tab[];
#endif

#endif /* _CPU_H_ */
E 1
