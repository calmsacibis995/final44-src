h61902
s 00001/00000/00133
d D 8.5 95/05/17 21:33:51 mckusick 13 12
c add definition for ability to produce a backtrace
e
s 00001/00001/00132
d D 8.4 94/01/04 17:14:33 mckusick 12 11
c do not need to do anything for cpu_set_init_frame() as the PMAX stores
c registers in u.u_pcb rather than on stack (i.e., fork() sets p_md.md_regs)
e
s 00004/00004/00129
d D 8.3 93/12/10 17:46:37 mckusick 11 10
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00132
d D 8.2 93/09/23 16:38:58 bostic 10 9
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00131
d D 8.1 93/06/10 23:01:54 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00000/00122
d D 7.8 93/05/24 18:23:27 ralph 8 7
c added CTL_MACHDEP support
e
s 00010/00012/00112
d D 7.7 92/11/15 16:02:30 ralph 7 6
c updates from Rick Macklem. Also, fix MIPS implementation defines.
e
s 00001/00001/00123
d D 7.6 92/10/24 14:19:40 ralph 6 5
c use COPY_SIGCODE now.
e
s 00001/00001/00123
d D 7.5 92/10/11 11:14:20 bostic 5 4
c make kernel includes standard
e
s 00013/00024/00111
d D 7.4 92/07/27 21:33:26 ralph 4 3
c added changes for clock interrupts/profiling
e
s 00002/00000/00133
d D 7.3 92/02/29 17:51:33 ralph 3 2
c added cpu_setstack macro
e
s 00013/00003/00120
d D 7.2 92/02/29 14:20:56 ralph 2 1
c added support for DS5000
e
s 00123/00000/00000
d D 7.1 92/01/07 20:35:46 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 7
/*
 * Copyright (c) 1992 Regents of the University of California.
E 7
I 7
/*-
D 9
 * Copyright (c) 1992 The Regents of the University of California.
E 7
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * Ralph Campbell.
E 7
I 7
 * Ralph Campbell and Rick Macklem.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _CPU_H_
#define _CPU_H_

D 5
#include "machConst.h"
E 5
I 5
#include <machine/machConst.h>
E 5

/*
 * Exported definitions unique to pmax/mips cpu support.
 */

/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
D 6
#undef	COPY_SIGCODE		/* copy sigcode above user stack in exec */
E 6
I 6
#define	COPY_SIGCODE		/* copy sigcode above user stack in exec */
E 6

D 4
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
#undef	NEED_FFS		/* don't need ffs function */
#undef	NEED_BCMP		/* don't need bcmp function */
#undef	NEED_STRLEN		/* don't need strlen function */

E 4
D 2
#define	cpu_exec(p)	/* nothing */
E 2
I 2
D 11
#define	cpu_exec(p)	(p->p_md.md_ss_addr = 0) /* init single step */
E 2
#define	cpu_wait(p)	/* nothing */
I 3
#define cpu_setstack(p, ap) \
	(p)->p_md.md_regs[SP] = ap
E 11
I 11
#define	cpu_exec(p)		(p->p_md.md_ss_addr = 0) /* init single step */
#define	cpu_wait(p)		/* nothing */
#define cpu_setstack(p, ap)	(p)->p_md.md_regs[SP] = ap
D 12
#define cpu_set_init_frame(p, fp) (p)->p_md.md_regs = fp
E 12
I 12
#define cpu_set_init_frame(p, fp) /* nothing */
I 13
#define	BACKTRACE(p)		/* not implemented */
E 13
E 12
E 11
E 3

/*
D 4
 * Arguments to hardclock, softclock and gatherstats
 * encapsulate the previous machine state in an opaque
 * clockframe;
E 4
I 4
 * Arguments to hardclock and gatherstats encapsulate the previous
 * machine state in an opaque clockframe.
E 4
 */
D 4
typedef struct intrframe {
	int	pc;
	int	ps;
} clockframe;
E 4
I 4
struct clockframe {
	int	pc;	/* program counter at time of interrupt */
	int	sr;	/* status register at time of interrupt */
};
E 4

D 4
#define	CLKF_USERMODE(framep)	((framep)->ps & MACH_SR_KU_PREV)
E 4
I 4
#define	CLKF_USERMODE(framep)	((framep)->sr & MACH_SR_KU_PREV)
E 4
#define	CLKF_BASEPRI(framep)	\
D 4
	(((framep)->ps & (MACH_INT_MASK | MACH_SR_INT_ENA_PREV)) == \
	(MACH_INT_MASK | MACH_SR_INT_ENA_PREV))
E 4
I 4
	((~(framep)->sr & (MACH_INT_MASK | MACH_SR_INT_ENA_PREV)) == 0)
E 4
#define	CLKF_PC(framep)		((framep)->pc)
I 4
#define	CLKF_INTR(framep)	(0)
E 4

/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
#define	need_resched()	{ want_resched = 1; aston(); }

/*
D 4
 * Give a profiling tick to the current process from the softclock
 * interrupt.
E 4
I 4
 * Give a profiling tick to the current process when the user profiling
 * buffer pages are invalid.  On the PMAX, request an ast to send us
 * through trap, marking the proc as needing a profiling tick.
E 4
 */
D 4
#define	profile_tick(p, framep) \
	addupc((framep)->pc, &p->p_stats->p_prof, 1);
E 4
I 4
D 10
#define	need_proftick(p)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 10
I 10
#define	need_proftick(p)	{ (p)->p_flag |= P_OWEUPC; aston(); }
E 10
E 4

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
I 8
 * CTL_MACHDEP definitions.
 */
#define	CPU_CONSDEV		1	/* dev_t: console terminal device */
#define	CPU_MAXID		2	/* number of valid machdep ids */

#define CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
	{ "console_device", CTLTYPE_STRUCT }, \
}

/*
E 8
 * MIPS CPU types (cp_imp).
 */
D 2
#define	MIPS_R2000	2
E 2
I 2
D 7
#define	MIPS_R2000	0x02
#define	MIPS_R3000	0x03
E 7
I 7
#define	MIPS_R2000	0x01
#define	MIPS_R3000	0x02
#define	MIPS_R6000	0x03
E 7
#define	MIPS_R4000	0x04
I 7
#define	MIPS_R6000A	0x06
E 7
E 2

/*
 * MIPS FPU types
 */
D 2
#define	MIPS_R2010	3
E 2
I 2
D 7
#define	MIPS_R2010	0x03
#define	MIPS_R3010	0x04
E 7
I 7
#define	MIPS_R2010	0x02
#define	MIPS_R3010	0x03
#define	MIPS_R6010	0x04
E 7
#define	MIPS_R4010	0x05
E 2
D 7

I 2
struct intr_tab {
	void	(*func)();	/* pointer to interrupt routine */
	int	unit;		/* logical unit number */
};
E 7

E 2
#ifdef KERNEL
union	cpuprid cpu;
union	cpuprid fpu;
u_int	machDataCacheSize;
u_int	machInstCacheSize;
I 2
extern	struct intr_tab intr_tab[];
E 2
#endif

/*
 * Enable realtime clock (always enabled).
 */
#define	enablertclock()

#endif /* _CPU_H_ */
E 1
