h61870
s 00001/00000/00071
d D 8.4 93/12/10 18:06:53 mckusick 8 7
c lint
e
s 00009/00009/00062
d D 8.3 93/09/23 16:45:07 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00069
d D 8.2 93/09/21 08:00:01 bostic 6 5
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00069
d D 8.1 93/06/11 15:16:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00069
d D 7.4 93/04/20 23:33:05 torek 4 3
c spelling
e
s 00003/00003/00068
d D 7.3 92/10/11 12:57:19 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00066
d D 7.2 92/07/21 16:54:34 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00066/00000/00000
d D 7.1 92/07/13 00:44:38 torek 1 0
c date and time created 92/07/13 00:44:38 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 * from: $Header: locore2.c,v 1.7 92/06/20 08:47:28 mccanne Exp $ (LBL)
E 4
I 4
 * from: $Header: locore2.c,v 1.8 92/11/26 03:05:01 mccanne Exp $ (LBL)
E 4
 */

/*
 * Primitives which are in locore.s on other machines,
 * but which have no reason to be assembly-coded on SPARC.
 */

D 3
#include "param.h"
#include "proc.h"
#include "resourcevar.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
E 3

int	whichqs;

/*
 * Put process p on the run queue indicated by its priority.
 * Calls should be made at splstatclock(), and p->p_stat should be SRUN.
 */
I 8
void
E 8
D 6
setrq(p)
E 6
I 6
setrunqueue(p)
E 6
	register struct proc *p;
{
	register struct prochd *q;
	register struct proc *oldlast;
D 7
	register int which = p->p_pri >> 2;
E 7
I 7
	register int which = p->p_priority >> 2;
E 7

D 7
	if (p->p_rlink != NULL)
E 7
I 7
	if (p->p_back != NULL)
E 7
D 6
		panic("setrq");
E 6
I 6
		panic("setrunqueue");
E 6
	q = &qs[which];
	whichqs |= 1 << which;
D 7
	p->p_link = (struct proc *)q;
	p->p_rlink = oldlast = q->ph_rlink;
E 7
I 7
	p->p_forw = (struct proc *)q;
	p->p_back = oldlast = q->ph_rlink;
E 7
	q->ph_rlink = p;
D 7
	oldlast->p_link = p;
E 7
I 7
	oldlast->p_forw = p;
E 7
}

/*
 * Remove process p from its run queue, which should be the one
 * indicated by its priority.  Calls should be made at splstatclock().
 */
remrq(p)
	register struct proc *p;
{
D 7
	register int which = p->p_pri >> 2;
E 7
I 7
	register int which = p->p_priority >> 2;
E 7
	register struct prochd *q;

	if ((whichqs & (1 << which)) == 0)
		panic("remrq");
D 7
	p->p_link->p_rlink = p->p_rlink;
	p->p_rlink->p_link = p->p_link;
	p->p_rlink = NULL;
E 7
I 7
	p->p_forw->p_back = p->p_back;
	p->p_back->p_forw = p->p_forw;
	p->p_back = NULL;
E 7
	q = &qs[which];
	if (q->ph_link == (struct proc *)q)
		whichqs &= ~(1 << which);
}
E 1
