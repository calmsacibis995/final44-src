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
 * $Log:	kern_proc.c,v $
 * Revision 2.8  89/05/30  10:33:49  rvb
 * 	Removed inclusion of psl.h for mips too.
 * 	[89/05/15            af]
 * 
 * Revision 2.7  89/03/09  19:28:45  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  14:41:43  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/09  04:31:13  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/30  22:02:51  rpd
 * 	Updated includes to the new style.
 * 	Added declarations of pidhash, proc, procNPROC,
 * 	freeproc, zombproc, allproc, nproc, qs, mpid.
 * 	(The declarations in .h files are "extern" now.)
 * 	[89/01/25  14:51:34  rpd]
 * 
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Removed use of "sys/vm.h".
 *
 * 17-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed include of text.h for MACH.
 *
 * 23-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon Univerity
 *	Moved mysterious reappearance of pte.h under else leg
 *	of CMUCS.
 *
 *  7-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Removed unnecessary include of pte.h
 *
 * 14-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added switch ROMP around #includes "../machine/psl.h" so that
 *	the Sailboat doesn't gag on it.  (Question: why does the vax
 *	include it if it still compiles when we cut it out???)
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_proc.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/reg.h>
#if	!defined(ibmrt) && !defined(mips)
#include <machine/psl.h>
#endif	!defined(ibmrt) && !defined(mips)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/acct.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/quota.h>
#include <sys/uio.h>
#include <sys/mbuf.h>

short	pidhash[PIDHSZ];
struct	proc *proc, *procNPROC;	/* the proc table itself */
struct	proc *freeproc, *zombproc, *allproc;
			/* lists of procs in various states */
int	nproc;
struct	prochd qs[NQS];
int	mpid;			/* generic for unique process id's */

/*
 * Clear any pending stops for top and all descendents.
 */
spgrp(top)
	struct proc *top;
{
	register struct proc *p;
	int f = 0;

	p = top;
	for (;;) {
		p->p_sig &=
			  ~(sigmask(SIGTSTP)|sigmask(SIGTTIN)|sigmask(SIGTTOU));
		f++;
		/*
		 * If this process has children, descend to them next,
		 * otherwise do any siblings, and if done with this level,
		 * follow back up the tree (but not past top).
		 */
		if (p->p_cptr)
			p = p->p_cptr;
		else if (p == top)
			return (f);
		else if (p->p_osptr)
			p = p->p_osptr;
		else for (;;) {
			p = p->p_pptr;
			if (p == top)
				return (f);
			if (p->p_osptr) {
				p = p->p_osptr;
				break;
			}
		}
	}
}

/*
 * Is p an inferior of the current process?
 */
inferior(p)
	register struct proc *p;
{

	for (; p != u.u_procp; p = p->p_pptr)
		if (p->p_ppid == 0)
			return (0);
	return (1);
}

struct proc *
pfind(pid)
	int pid;
{
	register struct proc *p;

	for (p = &proc[pidhash[PIDHASH(pid)]]; p != &proc[0]; p = &proc[p->p_idhash])
		if (p->p_pid == pid)
			return (p);
	return ((struct proc *)0);
}

/*
 * init the process queues
 */
pqinit()
{
	register struct proc *p;

	/*
	 * most procs are initially on freequeue
	 *	nb: we place them there in their "natural" order.
	 */

	freeproc = NULL;
	for (p = procNPROC; --p > proc; freeproc = p)
		p->p_nxt = freeproc;

	/*
	 * but proc[0] is special ...
	 */

	allproc = p;
	p->p_nxt = NULL;
	p->p_prev = &allproc;

	zombproc = NULL;
}
