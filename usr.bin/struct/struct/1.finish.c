/*-
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)1.finish.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include <stdio.h>
#include "def.h"
#include "1.incl.h"

fingraph()
	{
	/* if any entry statements, add a DUMVX with arcs to all entry statements */
	if (ENTLST)
		{
		ARC(START,0) = addum(ARC(START,0),ENTLST);
		freelst(ENTLST);
		}
	/* if any FMTVX, add a DUMVX with arcs to all FMTVX's */
	if (FMTLST)
		{
		ARC(START,0) = addum(ARC(START,0),FMTLST);
		freelst(FMTLST);
		}
	}

addum(v,lst)
VERT v;
struct list *lst;
	{
	VERT new;
	int count,i;
	struct list *ls;
	count = lslen(lst);		/* length of lst */
	new = create(DUMVX,1+count);
	ARC(new,0) = v;
	for (i = count, ls = lst; i >= 1; --i, ls = ls->nxtlist)
		{
		ASSERT(ls,addum);
		ARC(new,i) = ls->elt;
		}
	ASSERT(!ls, addum);
	return(new);
	}
