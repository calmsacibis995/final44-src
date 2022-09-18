h49594
s 00000/00000/00058
d D 8.1 93/06/06 16:29:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00052
d D 4.2 91/04/16 16:48:39 bostic 2 1
c new copyright; att/bsd/shared
e
s 00054/00000/00000
d D 4.1 83/02/11 15:44:26 rrh 1 0
c date and time created 83/02/11 15:44:26 by rrh
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
set dom[v] to immediate dominator of v, based on arcs as stored in inarcs
(i.e. pretending the graph is reducible if it isn't).
Algorithm is from Hecht and Ullman, Analysis of a simple algorithm for global
flow analysis problems, except bit vector operations replaced by search
through DOM to save quadratic blowup in space 
*/
#include "def.h"
#include "2.def.h"


getdom(inarc,dom)
struct list **inarc;
VERT *dom;
	{
	VERT v;
	int i;
	struct list *ls;
	for (v = 0; v < nodenum; ++v)
		dom[v] = UNDEFINED;
	for (i = 1; i < accessnum; ++i)
		{
		v = after[i];
		for (ls = inarc[v]; ls; ls = ls->nxtlist)
			{
			ASSERT(ntoaft[ls->elt] < i,getdom);
			dom[v] = comdom(dom[v],ls->elt,dom);
			}

		}
	}


comdom(u,v,dom)			/* find closest common dominator of u,v */
VERT u,v, *dom;
	{
	if (u == UNDEFINED) return(v);
	if (v == UNDEFINED) return(u);
	while(u != v)
		{
		ASSERT(u != UNDEFINED && v != UNDEFINED, comdom);
		if (ntoaft[u] < ntoaft[v])	
			v = dom[v];
		else
			u = dom[u];
		}
	return(u);
	}
E 1
