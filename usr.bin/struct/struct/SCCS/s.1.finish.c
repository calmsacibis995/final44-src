h20488
s 00000/00000/00046
d D 8.1 93/06/06 16:28:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00040
d D 4.2 91/04/16 16:48:26 bostic 2 1
c new copyright; att/bsd/shared
e
s 00042/00000/00000
d D 4.1 83/02/11 15:44:02 rrh 1 0
c date and time created 83/02/11 15:44:02 by rrh
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
E 1
