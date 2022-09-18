h64148
s 00000/00000/00160
d D 8.1 93/06/06 16:29:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00154
d D 4.2 91/04/16 16:48:46 bostic 2 1
c new copyright; att/bsd/shared
e
s 00156/00000/00000
d D 4.1 83/02/11 15:44:42 rrh 1 0
c date and time created 83/02/11 15:44:42 by rrh
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
#include "def.h"
#include "3.def.h"

#define ARCCOUNT(v)	REACH(v)


fixhd(v,hd,head)
VERT v,hd,*head;
	{
	VERT w,newhd;
	int i;
	head[v] = hd;
	newhd = (NTYPE(v) == ITERVX) ? v : hd;
	for (i = 0; i < CHILDNUM(v); ++i)
		for (w = LCHILD(v,i); DEFINED(w); w = RSIB(w))
			fixhd(w,newhd,head);
	}

getloop()
	{
	cntarcs();
	fixloop(START);
	}


cntarcs()	/* count arcs entering each node */
	{
	VERT w,v;
	int i;
	for (v = 0; v < nodenum; ++v)
		ARCCOUNT(v) = 0;
	for (v = 0; v < nodenum; ++v)
		for (i = 0; i < ARCNUM(v); ++i)
			{
			w = ARC(v,i);
			if (!DEFINED(w)) continue;
			++ARCCOUNT(w);
			}
	}


fixloop(v)		/* find WHILE loops  */
VERT v;
	{
	int recvar;
	if (NTYPE(v) == LOOPVX)
		{
		ASSERT(DEFINED(ARC(v,0)),fixloop);
		NXT(ARC(v,0)) = ARC(v,0);
		if (!getwh(v))
			getun(v);
		}
	else if (NTYPE(v) == IFVX && arbcase)
		getswitch(v);
	else if (NTYPE(v)==DOVX)
		{
		ASSERT(DEFINED(ARC(v,0)),fixloop);
		NXT(ARC(v,0))=ARC(v,0);
		}
	RECURSE(fixloop,v,recvar);
	}


getwh(v)
VERT v;
	{
	VERT vchild, vgrand,vgreat;
	ASSERT(NTYPE(v) == LOOPVX,getwh);
	vchild = LCHILD(v,0);
	ASSERT(DEFINED(vchild),getwh);
	ASSERT(NTYPE(vchild) == ITERVX,getwh);
	vgrand = LCHILD(vchild,0);
	if (!DEFINED(vgrand) || !IFTHEN(vgrand) )
		return(FALSE);
	vgreat = LCHILD(vgrand,THEN);
	if (DEFINED(vgreat) && NTYPE(vgreat) == GOVX && ARC(vgreat,0) == BRK(vchild))
		{
		/* turn into WHILE */
		NTYPE(v) = WHIVX;
		NEG(vgrand) = !NEG(vgrand);
		LPRED(vchild) = vgrand; 
		LCHILD(vchild,0) = RSIB(vgrand);
		RSIB(vgrand) = UNDEFINED;
		return(TRUE);
		}
	return(FALSE);
	}



getun(v)		/* change loop to REPEAT UNTIL if possible */
VERT v;
	{
	VERT vchild, vgrand,  vgreat, before, ch;
	ASSERT(NTYPE(v) == LOOPVX,getun);
	vchild = LCHILD(v,0);
	ASSERT(DEFINED(vchild), getun);
	if (ARCCOUNT(vchild) > 2) 
		return(FALSE);		/* loop can be iterated without passing through predicate of UNTIL */
	vgrand = ARC(vchild,0);
	if (!DEFINED(vgrand))
		return(FALSE);
	for (ch = vgrand,before = UNDEFINED; DEFINED(RSIB(ch)); ch = RSIB(ch))
		before = ch;
	if (!IFTHEN(ch))
		return(FALSE);
	vgreat = LCHILD(ch,THEN);
	if (DEFINED(vgreat) && NTYPE(vgreat) == GOVX && ARC(vgreat,0) == BRK(vchild))
		{
		/* create  UNTIL node */
		NTYPE(v) = UNTVX;
		NXT(vchild) = ch;
		LPRED(vchild)=ch;
		RSIB(before) = UNDEFINED;
		return(TRUE);
		}
	return(FALSE);
	}


#define FORMCASE(w)	(DEFINED(w) && !DEFINED(RSIB(w)) && NTYPE(w) == IFVX && ARCCOUNT(w) == 1)

getswitch(v)
VERT v;
	{
	VERT ch, grand, temp;
	/* must be of form if ... else if ... else if ... */
	if (NTYPE(v) != IFVX) return(FALSE);
	ch = LCHILD(v,ELSE);
	if (!FORMCASE(ch)) return(FALSE);
	grand = LCHILD(ch,ELSE);
	if (!FORMCASE(grand)) return(FALSE);

	temp = create(SWCHVX,0);
	exchange(&graph[temp],&graph[v]);	/* want arcs to enter switch, not first case*/
	BEGCOM(v) = UNDEFINED;
	RSIB(v) = RSIB(temp);		/* statements which followed IFVX should follow switch */
	EXP(v) = UNDEFINED;
	LCHILD(v,0) = temp;
	NTYPE(temp) = ACASVX;
	for (ch = LCHILD(temp,ELSE); FORMCASE(ch); )
		{
		LCHILD(temp,ELSE) = UNDEFINED;
		RSIB(temp) = ch;
		NTYPE(ch) = ACASVX;
		temp = ch;
		ch = LCHILD(temp,ELSE);
		}
	ASSERT(!DEFINED(RSIB(temp)),getswitch);
	return(TRUE);
	}
E 1
