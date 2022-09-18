h62688
s 00001/00000/00149
d D 8.5 95/05/17 21:34:12 mckusick 11 10
c add definition for ability to produce a backtrace
e
s 00001/00000/00148
d D 8.4 94/01/05 09:51:22 mckusick 10 9
c add cpu_swapin (nothing needed)
e
s 00011/00002/00137
d D 8.3 93/12/10 22:59:46 mckusick 9 7
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00004/00003/00136
d R 8.3 93/12/10 17:49:43 mckusick 8 7
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00138
d D 8.2 93/09/23 16:44:49 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00137
d D 8.1 93/06/11 15:11:45 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00014/00124
d D 7.5 93/05/25 03:39:49 torek 5 4
c add cpu sysctl definitions; protect kernel stuff against user inclusion
e
s 00002/00002/00136
d D 7.4 93/04/20 06:39:40 torek 4 3
c spelling
e
s 00002/00002/00136
d D 7.3 92/10/11 12:42:13 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00133
d D 7.2 92/07/21 16:41:26 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00133/00000/00000
d D 7.1 92/07/13 00:42:59 torek 1 0
c date and time created 92/07/13 00:42:59 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: cpu.h,v 1.10 92/07/09 03:10:54 torek Exp $ (LBL)
E 4
I 4
D 5
 * from: $Header: cpu.h,v 1.11 92/11/26 02:04:33 torek Exp $ (LBL)
E 5
I 5
 * from: $Header: cpu.h,v 1.12 93/05/25 10:36:34 torek Exp $ (LBL)
E 5
E 4
 */

#ifndef _CPU_H_
#define _CPU_H_

D 3
#include "machine/psl.h"
#include "../sparc/intreg.h"
E 3
I 3
D 5
#include <machine/psl.h>
#include <sparc/sparc/intreg.h>
E 5
I 5
/*
 * CTL_MACHDEP definitinos.
 */
#define	CPU_MAXID	1	/* no valid machdep ids */
E 5
E 3

I 5
#define	CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
}

#ifdef KERNEL
E 5
/*
 * Exported definitions unique to SPARC cpu support.
 */

I 5
#include <machine/psl.h>
#include <sparc/sparc/intreg.h>

E 5
/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
#define	COPY_SIGCODE		/* copy sigcode above user stack in exec */

D 5
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
#undef	NEED_FFS		/* don't need ffs function */
#define	NEED_BCMP		/* need bcmp function */
#define	NEED_STRLEN		/* need strlen function */

E 5
D 9
#define	cpu_exec(p)	/* nothing */
#define	cpu_wait(p)	/* nothing */
E 9
I 9
#define	cpu_exec(p)		/* nothing */
I 10
#define	cpu_swapin(p)		/* nothing */
E 10
#define	cpu_wait(p)		/* nothing */
E 9
#define	cpu_setstack(p, ap)	((p)->p_md.md_tf->tf_out[6] = (ap) - 64)
I 11
#define	BACKTRACE(p)		/* not implemented */
E 11
I 9

/*
 * See syscall() for an explanation of the following.  Note that the
 * locore bootstrap code follows the syscall stack protocol.  The
 * framep argument is unused.
 */
#define cpu_set_init_frame(p, fp) \
	(p)->p_md.md_tf = (struct trapframe *) \
	    ((caddr_t)(p)->p_addr + UPAGES * NBPG - sizeof(struct trapframe))
E 9

/*
 * Arguments to hardclock, softclock and gatherstats encapsulate the
 * previous machine state in an opaque clockframe.  The ipl is here
 * as well for strayintr (see locore.s:interrupt and intr.c:strayintr).
 * Note that CLKF_INTR is valid only if CLKF_USERMODE is false.
 */
struct clockframe {
	u_int	psr;		/* psr before interrupt, excluding PSR_ET */
	u_int	pc;		/* pc at interrupt */
	u_int	npc;		/* npc at interrupt */
	u_int	ipl;		/* actual interrupt priority level */
	u_int	fp;		/* %fp at interrupt */
};

extern int eintstack[];

#define	CLKF_USERMODE(framep)	(((framep)->psr & PSR_PS) == 0)
#define	CLKF_BASEPRI(framep)	(((framep)->psr & PSR_PIL) == 0)
#define	CLKF_PC(framep)		((framep)->pc)
#define	CLKF_INTR(framep)	((framep)->fp < (u_int)eintstack)

/*
 * Software interrupt request `register'.
 */
union sir {
	int	sir_any;
	char	sir_which[4];
} sir;

#define SIR_NET		0
#define SIR_CLOCK	1

#define	setsoftint()	ienab_bis(IE_L1)
#define setsoftnet()	(sir.sir_which[SIR_NET] = 1, setsoftint())
#define setsoftclock()	(sir.sir_which[SIR_CLOCK] = 1, setsoftint())

int	want_ast;

/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
int	want_resched;		/* resched() was called */
#define	need_resched()		(want_resched = 1, want_ast = 1)

/*
 * Give a profiling tick to the current process when the user profiling
 * buffer pages are invalid.  On the sparc, request an ast to send us 
 * through trap(), marking the proc as needing a profiling tick.
 */
D 7
#define	need_proftick(p)	((p)->p_flag |= SOWEUPC, want_ast = 1)
E 7
I 7
#define	need_proftick(p)	((p)->p_flag |= P_OWEUPC, want_ast = 1)
E 7

/*
 * Notify the current process (p) that it has a signal pending,
 * process as soon as possible.
 */
#define	signotify(p)		(want_ast = 1)

/*
 * Only one process may own the FPU state.
 *
 * XXX this must be per-cpu (eventually)
 */
struct	proc *fpproc;		/* FPU owner */
int	foundfpu;		/* true => we have an FPU */

/*
 * Interrupt handler chains.  Interrupt handlers should return 0 for
 * ``not me'' or 1 (``I took care of it'').  intr_establish() inserts a
 * handler into the list.  The handler is called with its (single)
 * argument, or with a pointer to a clockframe if ih_arg is NULL.
 */
struct intrhand {
	int	(*ih_fun) __P((void *));
	void	*ih_arg;
	struct	intrhand *ih_next;
} *intrhand[15];

void	intr_establish __P((int level, struct intrhand *));

/*
 * intr_fasttrap() is a lot like intr_establish, but is used for ``fast''
 * interrupt vectors (vectors that are not shared and are handled in the
 * trap window).  Such functions must be written in assembly.
 */
void	intr_fasttrap __P((int level, void (*vec)(void)));

D 5
#endif _CPU_H_
E 5
I 5
#endif /* KERNEL */
#endif /* _CPU_H_ */
E 5
E 1
