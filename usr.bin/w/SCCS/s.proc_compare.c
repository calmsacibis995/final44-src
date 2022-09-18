h35118
s 00033/00037/00061
d D 8.2 93/09/23 19:37:34 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00096
d D 8.1 93/06/06 22:23:08 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00095
d D 5.5 93/04/27 15:20:09 bostic 5 4
c lint
e
s 00005/00005/00090
d D 5.4 91/02/07 10:45:42 marc 4 3
c oops - reverse test for isrun
e
s 00020/00004/00075
d D 5.3 90/06/26 12:26:35 marc 3 2
c zombies count last
e
s 00011/00002/00068
d D 5.2 90/05/04 16:02:38 marc 2 1
c get headers right
e
s 00070/00000/00000
d D 5.1 90/05/04 15:52:22 marc 1 0
c date and time created 90/05/04 15:52:22 by marc
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#include <sys/param.h>
#include <sys/time.h>
#include <sys/proc.h>

#include "extern.h"

E 7
/*
D 7
 * Returns 1 if p2 is more active than p1
E 7
I 7
 * Returns 1 if p2 is "better" than p1
E 7
 *
D 2
 * The algorithm for picking the "interesting" process is thus:
E 2
I 2
D 7
 * The algorithm for picking the "more active" process is thus:
E 7
I 7
 * The algorithm for picking the "interesting" process is thus:
E 7
E 2
 *
D 7
 *	1) Runnable processes are favored over anything
 *	   else.  The runner with the highest cpu
 *	   utilization is picked (p_cpu).  Ties are
E 7
I 7
 *	1) Only foreground processes are eligible - implied.
 *	2) Runnable processes are favored over anything else.  The runner
 *	   with the highest cpu utilization is picked (p_estcpu).  Ties are
E 7
 *	   broken by picking the highest pid.
D 7
 *	2) Next, the sleeper with the shortest sleep
 *	   time is favored.  With ties, we pick out
 *	   just short-term sleepers (p_pri <= PZERO).
 *	   Further ties are broken by picking the highest
 *	   pid.
E 7
I 7
 *	3) The sleeper with the shortest sleep time is next.  With ties,
 *	   we pick out just "short-term" sleepers (P_SINTR == 0).
 *	4) Further ties are broken by picking the highest pid.
E 7
 *
D 2
 *	TODO - consider whether to use pctcpu
E 2
I 2
D 7
 *	NOTE - if you change this, be sure to consider making
 *	   the change in the kernel too (^T in kern/tty.c).
E 7
I 7
 * If you change this, be sure to consider making the change in the kernel
 * too (^T in kern/tty.c).
E 7
E 2
 *
I 2
D 7
 *	TODO - consider whether pctcpu should be used
 *
E 7
I 7
 * TODO - consider whether pctcpu should be used.
E 7
E 2
 */
I 2

D 7
#include <sys/param.h>
#include <sys/time.h>
#include <sys/proc.h>
E 7
I 7
#define ISRUN(p)	(((p)->p_stat == SRUN) || ((p)->p_stat == SIDL))
#define TESTAB(a, b)    ((a)<<1 | (b))
#define ONLYA   2
#define ONLYB   1
#define BOTH    3
E 7

I 5
D 7
#include "extern.h"

E 5
E 2
#define isrun(p)	(((p)->p_stat == SRUN) || ((p)->p_stat == SIDL))
I 2

I 3
#define	TESTAB(a, b)	((a)<<1 | (b))
D 4
#define	ONLYA	0x10
#define	ONLYB	0x01
#define	BOTH	0x11
E 4
I 4
#define	ONLYA	2
#define	ONLYB	1
#define	BOTH	3
E 4

E 7
I 5
int
E 5
E 3
E 2
proc_compare(p1, p2)
	register struct proc *p1, *p2;
{

	if (p1 == NULL)
		return (1);
	/*
	 * see if at least one of them is runnable
	 */
D 3
	switch (isrun(p1)<<1 | isrun(p2)) {
	case 0x01:
E 3
I 3
D 7
	switch (TESTAB(isrun(p1), isrun(p2))) {
E 7
I 7
	switch (TESTAB(ISRUN(p1), ISRUN(p2))) {
E 7
	case ONLYA:
E 3
D 4
		return (1);
D 3
	case 0x10:
E 3
I 3
	case ONLYB:
E 4
E 3
		return (0);
I 4
	case ONLYB:
		return (1);
E 4
D 3
	case 0x11:
E 3
I 3
	case BOTH:
E 3
		/*
		 * tie - favor one with highest recent cpu utilization
		 */
D 7
		if (p2->p_cpu > p1->p_cpu)
E 7
I 7
		if (p2->p_estcpu > p1->p_estcpu)
E 7
			return (1);
D 7
		if (p1->p_cpu > p2->p_cpu)
E 7
I 7
		if (p1->p_estcpu > p2->p_estcpu)
E 7
			return (0);
I 3
		return (p2->p_pid > p1->p_pid);	/* tie - return highest pid */
	}
	/*
D 7
	 * weed out zombies
E 7
I 7
 	 * weed out zombies
E 7
	 */
	switch (TESTAB(p1->p_stat == SZOMB, p2->p_stat == SZOMB)) {
	case ONLYA:
		return (1);
	case ONLYB:
		return (0);
	case BOTH:
E 3
D 7
		return (p2->p_pid > p1->p_pid);	/* tie - return highest pid */
E 7
I 7
		return (p2->p_pid > p1->p_pid); /* tie - return highest pid */
E 7
	}
D 7
	/* 
E 7
I 7
	/*
E 7
	 * pick the one with the smallest sleep time
	 */
	if (p2->p_slptime > p1->p_slptime)
		return (0);
	if (p1->p_slptime > p2->p_slptime)
		return (1);
	/*
	 * favor one sleeping in a non-interruptible sleep
	 */
D 7
	 if (p1->p_flag&SSINTR && (p2->p_flag&SSINTR) == 0)
		 return (1);
	 if (p2->p_flag&SSINTR && (p1->p_flag&SSINTR) == 0)
		 return (0);
	return(p2->p_pid > p1->p_pid);		/* tie - return highest pid */
E 7
I 7
	if (p1->p_flag & P_SINTR && (p2->p_flag & P_SINTR) == 0)
		return (1);
	if (p2->p_flag & P_SINTR && (p1->p_flag & P_SINTR) == 0)
		return (0);
	return (p2->p_pid > p1->p_pid);		/* tie - return highest pid */
E 7
}
E 1
