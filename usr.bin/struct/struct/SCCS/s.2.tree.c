h47877
s 00000/00000/00139
d D 8.1 93/06/06 16:29:37 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00133
d D 4.2 91/04/16 16:48:43 bostic 2 1
c new copyright; att/bsd/shared
e
s 00135/00000/00000
d D 4.1 83/02/11 15:44:35 rrh 1 0
c date and time created 83/02/11 15:44:35 by rrh
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
/* use inarc, dom, and head to build tree representing structure of program.
	Each node v has CHILDNUM(v) children denoted by
	LCHILD(v,0), LCHILD(v,1),...
	RSIB((v) is right sibling of v or UNDEFINED;
	RSIB(v) represents code following v at the same level of nesting,
	while LCHILD(v,i) represents code nested within v
*/
#include "def.h"
#include "2.def.h"

gettree(inarc,dom,head)		/* build tree */
struct list **inarc;
VERT *dom, *head;
	{
	VERT v,u,from;
	int i;
	for ( v = 0; v < nodenum; ++v)
		{
		RSIB(v) = UNDEFINED;
		for (i = 0; i < CHILDNUM(v); ++i)
			LCHILD(v,i) = UNDEFINED;
		}
	for (i = accessnum-1; i > 0; --i)
		{
		v = after[i];
		from = oneelt(inarc[v]);	/* the unique elt of inarc[v] or UNDEFINED */
		if (DEFINED(from))
			if (NTYPE(from) == IFVX && (head[v] == head[from] || asoc(v,exitsize) != -1) )
				/* place in clause of IFVX if in smallest loop containing it
				or if size of code for v is <= exitsize */
				if (ARC(from,THEN) == v)
					{
					LCHILD(from,THEN) = v;
					continue;
					}
				else
					{
					ASSERT(ARC(from,ELSE) == v,gettree);
					LCHILD(from,ELSE) = v;
					continue;
					}
			else if (NTYPE(v) == ITERVX || NTYPE(from) == ITERVX )
				/* LOOPVX -> ITERVX ->vert always in same loop*/
				{
				LCHILD(from,0) = v;
				continue;
				}
			else if (NTYPE(from) == SWCHVX)
				{
				ASSERT(0 < ARCNUM(v),gettree);
				if (ARC(from,0) == v)
					LCHILD(from,0) = v;
				else
					{
					int j;
					for (j = 1; j < ARCNUM(from); ++j)
						if (ARC(from,j) == v)
							{insib(ARC(from,j-1),v);
							break;
							}
					}
				continue;
				}
			else if (NTYPE(from) == ICASVX && (head[v] == head[from] || asoc(v,exitsize) != -1))
				{
				LCHILD(from,0) = v;
				continue;
				}
			else if (NTYPE(from) == DUMVX && ARC(from,0) == v)
				{
				LCHILD(from,0) = v;
				continue;
				}
		if (loomem(v,head[dom[v]],head))
				/* v is in smallest loop containing dom[v] */
			insib(dom[v],v);
		else
			{
				/* make v follow LOOPVX heading largest loop
					containing DOM[v] but not v */
			ASSERT(DEFINED(head[dom[v]]),gettree);
			for (u = head[dom[v]]; head[u] != head[v]; u = head[u])
				ASSERT(DEFINED(head[u]),gettree);
			ASSERT(NTYPE(u) == ITERVX,gettree);
			insib(FATH(u),v);
			}
		}
	}




insib(w,v)		/* make RSIB(w) = v, and make RSIB(rightmost sib of v) = old RSIB(w) */
VERT w,v;
	{
	VERT u, temp;
	temp = RSIB(w);
	RSIB(w) = v;
	for (u = v; DEFINED(RSIB(u)); u = RSIB(u))
		;
	RSIB(u) = temp;
	}


asoc(v,n)		/* return # of nodes associated with v if <= n, -1 otherwise */
VERT v;
int n;
	{
	int count,i,temp;
	VERT w;
	count = (NTYPE(v) == STLNVX) ? CODELINES(v) : 1;
	for (i = 0; i < CHILDNUM(v); ++i)
		{
		w = LCHILD(v,i);
		if (!DEFINED(w)) continue;
		temp = asoc(w,n-count);
		if (temp == -1) return(-1);
		count += temp;
		if (count > n) return(-1);
		}
	if (DEFINED(RSIB(v)))
		{
		temp = asoc(RSIB(v),n-count);
		if (temp == -1) return(-1);
		count += temp;
		}
	if (count > n) return(-1);
	else return(count);
	}
E 1
