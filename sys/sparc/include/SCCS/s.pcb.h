h35337
s 00003/00003/00094
d D 8.2 93/09/23 16:44:53 bostic 5 4
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00095
d D 8.1 93/06/11 15:12:16 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00095
d D 7.3 93/04/20 18:54:33 torek 3 2
c spelling
e
s 00005/00000/00092
d D 7.2 92/07/21 16:41:33 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00092/00000/00000
d D 7.1 92/07/13 00:43:03 torek 1 0
c date and time created 92/07/13 00:43:03 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: pcb.h,v 1.5 92/06/17 06:10:21 torek Exp $
E 3
I 3
 * from: $Header: pcb.h,v 1.6 92/11/26 02:04:39 torek Exp $
E 3
 */

#include <machine/reg.h>

#ifdef notyet
#define	PCB_MAXWIN	32	/* architectural limit */
#else
#define	PCB_MAXWIN	8	/* worried about u area sizes ... */
#endif

/*
 * SPARC Process Control Block.
 *
 * pcb_uw is positive if there are any user windows that are
 * are currently in the CPU windows rather than on the user
 * stack.  Whenever we are running in the kernel with traps
 * enabled, we decrement pcb_uw for each ``push'' of a CPU
 * register window into the stack, and we increment it for
 * each ``pull'' from the stack into the CPU.  (If traps are
 * disabled, or if we are in user mode, pcb_uw is junk.)
 *
 * To ease computing pcb_uw on traps from user mode, we keep track
 * of the log base 2 of the single bit that is set in %wim.
 *
 * If an overflow occurs while the associated user stack pages
 * are invalid (paged out), we have to store the registers
 * in a page that is locked in core while the process runs,
 * i.e., right here in the pcb.  We also need the stack pointer
 * for the last such window (but only the last, as the others
 * are in each window) and the count of windows saved.  We
 * cheat by having a whole window structure for that one %sp.
 * Thus, to save window pcb_rw[i] to memory, we write it at
 * pcb_rw[i + 1].rw_in[6].
 *
 * pcb_nsaved has three `kinds' of values.  If 0, it means no
 * registers are in the PCB (though if pcb_uw is positive,
 * there may be the next time you look).  If positive, it means
 * there are no user registers in the CPU, but there are some
 * saved in pcb_rw[].  As a special case, traps that needed
 * assistance to pull user registers from the stack also store
 * the registers in pcb_rw[], and set pcb_nsaved to -1.  This
 * special state is normally short-term: it can only last until the
 * trap returns, and it can never persist across entry to user code.
 */
struct pcb {
D 5
	int	pcb_sp;		/* sp (%o6) when swtch() was called */
	int	pcb_pc;		/* pc (%o7) when swtch() was called */
	int	pcb_psr;	/* %psr when swtch() was called */
E 5
I 5
	int	pcb_sp;		/* sp (%o6) when switch() was called */
	int	pcb_pc;		/* pc (%o7) when switch() was called */
	int	pcb_psr;	/* %psr when switch() was called */
E 5

	caddr_t	pcb_onfault;	/* for copyin/out */

	int	pcb_uw;		/* user windows inside CPU */
	int	pcb_wim;	/* log2(%wim) */
	int	pcb_nsaved;	/* number of windows saved in pcb */

#ifdef notdef
	int	pcb_winof;	/* number of window overflow traps */
	int	pcb_winuf;	/* number of window underflow traps */
#endif
	int	pcb_pad;	/* pad to doubleword boundary */

	/* the following MUST be aligned on a doubleword boundary */
	struct	rwindow pcb_rw[PCB_MAXWIN];	/* saved windows */
};

/*
 * The pcb is augmented with machine-dependent additional data for
 * core dumps.  Note that the trapframe here is a copy of the one
 * from the top of the kernel stack (included here so that the kernel
 * stack itself need not be dumped).
 */
struct md_coredump {
	struct	trapframe md_tf;
	struct	fpstate md_fpstate;
};

#ifdef KERNEL
extern struct pcb *cpcb;
#endif /* KERNEL */
E 1
