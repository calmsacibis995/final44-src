h20463
s 00000/00000/00097
d D 8.1 93/06/06 16:29:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00091
d D 4.2 91/04/16 16:48:45 bostic 2 1
c new copyright; att/bsd/shared
e
s 00093/00000/00000
d D 4.1 83/02/11 15:44:40 rrh 1 0
c date and time created 83/02/11 15:44:40 by rrh
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>
#
/*
correct the flow of control in the new program - use GOTO's which may
be changed later to NEXT, BREAK, etc.
*/
#include "def.h"
#include "3.def.h"

#define BRANCHTYPE(v)	(NTYPE(v) == GOVX )
#define HASLEX(t)	(t != GOVX && t != COMPVX && t != ASGOVX  && t != ITERVX )
			/* for these, control never flows directly to following statement */


getflow()
	{
	fixflow(START,UNDEFINED);
	}


fixflow(v,autolex)
VERT v;
VERT autolex;		/* lexical successor of v */
	{
	VERT lex,chlex,z,x,w;
	int i;
	lex = lexval(v,autolex);
	if (HASLEX(NTYPE(v)) && NTYPE(v) != ICASVX)
		if (DEFINED(REACH(v)) && REACH(v) != lex)
			insib(v,makebr(REACH(v)));
		else if (NTYPE(v) == DOVX && ARC(v,1) != lex)
			insib(v,makebr(ARC(v,1)));
	if (NTYPE(v) == ITERVX)
		{
		BRK(v) = autolex;
		chlex = v;
		}
	else
		chlex = lexval(v,autolex);

	for (i = 0; i < CHILDNUM(v); ++i)
		{
		w = LCHILD(v,i);
		if (DEFINED(w))
			fixflow(w,chlex);
		else
			{
			ASSERT(i < ARCNUM(v),fixflow);
			z = ARC(v,i);
			ASSERT(DEFINED(z), fixflow);
			if (z != chlex)
				{
				x = makebr(z);
				LCHILD(v,i) = x;
				RSIB(x) = UNDEFINED;
				}
			}
		}
	if (DEFINED(RSIB(v)))
		fixflow(RSIB(v),autolex);
	}


lexval(v,lastlex)
VERT v,lastlex;
	{
	VERT sib;
	if (!HASLEX(NTYPE(v))) return(UNDEFINED);
	sib = RSIB(v);
	if (NTYPE(v) == ICASVX || NTYPE(v) == ACASVX)
		return(lastlex);
	else if (!DEFINED(sib))
		return(lastlex);
	else if (BRANCHTYPE(sib))
		return(ARC(sib,0));
	else return(sib);
	}


makebr(w)		/* make branching node leading to w */
VERT w;
	{
	VERT new;
	new = create(GOVX,1);
	ARC(new,0) = w;
	RSIB(new) = UNDEFINED;
	REACH(new) = UNDEFINED;
	return(new);
	}
E 1
