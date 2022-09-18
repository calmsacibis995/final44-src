h22060
s 00002/00002/00150
d D 8.1 93/06/04 12:11:04 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00151
d D 5.3 93/04/30 00:11:23 mckusick 3 2
c use hashfraction defined in gmonparam
e
s 00002/00002/00150
d D 5.2 92/07/13 20:25:58 torek 2 1
c fix comments: MCOUNT macros are in <machine/profile.h>
e
s 00152/00000/00000
d D 5.1 92/07/10 17:15:52 mckusick 1 0
c date and time created 92/07/10 17:15:52 by mckusick
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1983, 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if !defined(lint) && !defined(KERNEL) && defined(LIBC_SCCS)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif

#include <sys/param.h>
#include <sys/gmon.h>

/*
 * mcount is called on entry to each function compiled with the profiling
 * switch set.  _mcount(), which is declared in a machine-dependent way
 * with _MCOUNT_DECL, does the actual work and is either inlined into a
 * C routine or called by an assembly stub.  In any case, this magic is
D 2
 * taken care of by the MCOUNT definition in <machine/mcount.h>.
E 2
I 2
 * taken care of by the MCOUNT definition in <machine/profile.h>.
E 2
 *
 * _mcount updates data structures that represent traversals of the
 * program's call graph edges.  frompc and selfpc are the return
 * address and function address that represents the given call graph edge.
 * 
 * Note: the original BSD code used the same variable (frompcindex) for
 * both frompcindex and frompc.  Any reasonable, modern compiler will
 * perform this optimization.
 */
_MCOUNT_DECL(frompc, selfpc)	/* _mcount; may be static, inline, etc */
	register u_long frompc, selfpc;
{
	register u_short *frompcindex;
	register struct tostruct *top, *prevtop;
	register struct gmonparam *p;
	register long toindex;
#ifdef KERNEL
	register int s;
#endif

	p = &_gmonparam;
	/*
	 * check that we are profiling
	 * and that we aren't recursively invoked.
	 */
	if (p->state != GMON_PROF_ON)
		return;
#ifdef KERNEL
	MCOUNT_ENTER;
#else
	p->state = GMON_PROF_BUSY;
#endif
	/*
	 * check that frompcindex is a reasonable pc value.
	 * for example:	signal catchers get called from the stack,
	 *		not from text space.  too bad.
	 */
	frompc -= p->lowpc;
	if (frompc > p->textsize)
		goto done;

D 3
	frompcindex = &p->froms[frompc / (HASHFRACTION * sizeof(*p->froms))];
E 3
I 3
	frompcindex = &p->froms[frompc / (p->hashfraction * sizeof(*p->froms))];
E 3
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
		 *	first time traversing this arc
		 */
		toindex = ++p->tos[0].link;
		if (toindex >= p->tolimit)
			/* halt further profiling */
			goto overflow;

		*frompcindex = toindex;
		top = &p->tos[toindex];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		goto done;
	}
	top = &p->tos[toindex];
	if (top->selfpc == selfpc) {
		/*
		 * arc at front of chain; usual case.
		 */
		top->count++;
		goto done;
	}
	/*
	 * have to go looking down chain for it.
	 * top points to what we are looking at,
	 * prevtop points to previous top.
	 * we know it is not at the head of the chain.
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
			 * top is end of the chain and none of the chain
			 * had top->selfpc == selfpc.
			 * so we allocate a new tostruct
			 * and link it to the head of the chain.
			 */
			toindex = ++p->tos[0].link;
			if (toindex >= p->tolimit)
				goto overflow;

			top = &p->tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
		 * otherwise, check the next arc on the chain.
		 */
		prevtop = top;
		top = &p->tos[top->link];
		if (top->selfpc == selfpc) {
			/*
			 * there it is.
			 * increment its count
			 * move it to the head of the chain.
			 */
			top->count++;
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		
	}
done:
#ifdef KERNEL
	MCOUNT_EXIT;
#else
	p->state = GMON_PROF_ON;
#endif
	return;
overflow:
	p->state = GMON_PROF_ERROR;
#ifdef KERNEL
	MCOUNT_EXIT;
#endif
	return;
}

/*
D 2
 * Actual definition of mcount function.  Defined in <machine/mcount.h>,
E 2
I 2
 * Actual definition of mcount function.  Defined in <machine/profile.h>,
E 2
 * which is included by <sys/gmon.h>.
 */
MCOUNT
E 1
