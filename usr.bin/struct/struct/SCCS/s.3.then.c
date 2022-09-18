h13302
s 00000/00000/00083
d D 8.1 93/06/06 16:29:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00077
d D 4.2 91/04/16 16:48:49 bostic 2 1
c new copyright; att/bsd/shared
e
s 00079/00000/00000
d D 4.1 83/02/11 15:44:48 rrh 1 0
c date and time created 83/02/11 15:44:48 by rrh
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

#define BRANCHTYPE(t)	(t == STOPVX || t == RETVX || t == BRKVX || t == NXTVX || t == GOVX)
#define MAXCHUNK	20
		/* if else clause smaller than MAXCHUNK and smaller than then clause,
			and there is no reason not to negate the if, negate the if */

getthen(v)		/* turn IFVX into THEN when appropriate, create else ifs where possible  */
VERT v;
	{
	VERT tch, fch;
	int tn,fn;
	int recvar;

	if (NTYPE(v) == IFVX)
		{
		tch = LCHILD(v,THEN);
		fch = LCHILD(v,ELSE);
		if (!DEFINED(fch))
			mkthen(v);
		else if (!DEFINED(tch))
			{
			negate(v);
			mkthen(v);
			}
		else if (BRANCHTYPE(NTYPE(tch)))
			mkthen(v);
		else if (BRANCHTYPE(NTYPE(fch)))
			{
			negate(v);
			mkthen(v);
			}
		else if (NTYPE(fch) != IFVX || DEFINED(RSIB(fch)))	/* not an else if */
			if ( NTYPE(tch) == IFVX && !DEFINED(RSIB(tch)))
					/* invert into else if */
				negate(v);
			else
				{
				/* asoc(v,n) returns number of statements associated with v
					if <= n, -1 otherwise */
				tn = asoc(tch,MAXCHUNK);
				fn = asoc(fch,MAXCHUNK);
				if (fn >= 0 && (tn < 0 || fn < tn))
					/* else clause smaller */
					negate(v);
				}
		}
	RECURSE(getthen,v,recvar);
	}

mkthen(v)
VERT v;
	{
	VERT w,tc;
	w = LCHILD(v,ELSE);
	tc = LCHILD(v,THEN);
	ASSERT(!DEFINED(w) || (DEFINED(tc) && BRANCHTYPE(NTYPE(tc)) ),mkthen);
	if (DEFINED(w))
		{
		insib(v,w);
		LCHILD(v,ELSE) = UNDEFINED;
		}
	ASSERT(IFTHEN(v),mkthen);
	}


negate(v)
VERT v;
	{
	ASSERT(NTYPE(v) == IFVX,negate);
	exchange(&LCHILD(v,THEN), &LCHILD(v,ELSE));
	NEG(v) = !NEG(v);
	}
E 1
