h02480
s 00000/00000/00096
d D 8.1 93/06/06 16:29:39 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00090
d D 4.2 91/04/16 16:48:43 bostic 2 1
c new copyright; att/bsd/shared
e
s 00092/00000/00000
d D 4.1 83/02/11 15:44:37 rrh 1 0
c date and time created 83/02/11 15:44:37 by rrh
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


getbranch(head)
VERT *head;
	{
	VERT v;
	for (v = 0; v < nodenum; ++v)
		LABEL(v) = FALSE;
	for (v = START; DEFINED(v); v = RSIB(v))
		chkbranch(v,head);
	addlab(START);
	}



chkbranch(v,head)
VERT v,*head;
	{
	VERT  w;
	int i;
	switch(NTYPE(v))
		{
		case GOVX:
				for (i = 1, w = head[v]; DEFINED(w); w = head[w], ++i)
					{
					if (i > 1 && !levnxt && !levbrk) break;
					if (ARC(v,0) == BRK(w) && (levbrk || i == 1))
						{
						NTYPE(v) = BRKVX;
						LEVEL(v) = i;
						break;
						}
					else if (ARC(v,0) == NXT(w) && (levnxt || i == 1))
						{
						NTYPE(v) = NXTVX;
						LEVEL(v) = i;
						break;
						}
					}
			if (NTYPE(v) == GOVX)
				{
				if (ARC(v,0) == stopvert)
					NTYPE(v) = STOPVX;
				else if (ARC(v,0) == retvert)
					NTYPE(v) = RETVX;
				else LABEL(ARC(v,0)) = TRUE;
				}
			break;
		case COMPVX:
		case ASGOVX:
			for (i = 0; i < ARCNUM(v); ++i)
				LABEL(ARC(v,i)) = TRUE;
			break;
		case IOVX:
				if (DEFINED(ARC(v,ENDEQ)))
					LABEL(ARC(v,ENDEQ)) = TRUE;
				if (DEFINED(ARC(v,ERREQ)))
					LABEL(ARC(v,ERREQ)) = TRUE;
				if (DEFINED(FMTREF(v)))
					LABEL(FMTREF(v)) = TRUE;
				break;
		}
	for (i = 0; i < CHILDNUM(v); ++i)
		for (w = LCHILD(v,i); DEFINED(w); w = RSIB(w))
			chkbranch(w,head);
	}


addlab(v)		/* add labels */
VERT v;
	{
	int recvar;
	if (NTYPE(v) != ITERVX && LABEL(v) )
		LABEL(v) = nxtlab();
	RECURSE(addlab,v,recvar);
	if (NTYPE(v) == ITERVX && LABEL(NXT(v)))
		LABEL(NXT(v)) = nxtlab();
	}


nxtlab()
	{
	static count;
	return(labinit + (count++) * labinc);
	}
E 1
