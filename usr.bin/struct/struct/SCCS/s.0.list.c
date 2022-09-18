h54458
s 00000/00000/00074
d D 8.1 93/06/06 16:28:36 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00068
d D 4.2 91/04/16 16:48:22 bostic 2 1
c new copyright; att/bsd/shared
e
s 00070/00000/00000
d D 4.1 83/02/11 15:43:55 rrh 1 0
c date and time created 83/02/11 15:43:55 by rrh
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

struct list *consls(v,ls)		/* make list */
VERT v;
struct list *ls;
	{
	struct list *temp;
	temp = challoc(sizeof(*temp));
	temp->elt = v;
	temp->nxtlist = ls;
	return(temp);
	}

struct list *append(v,ls)		/* return ls . v */
VERT v;
struct list *ls;
	{
	struct list *temp;
	if (!ls) return(consls(v,0));
	for (temp = ls; temp -> nxtlist; temp = temp->nxtlist)
		;
	temp->nxtlist = consls(v,0);
	return(ls);
	}


freelst(ls)
struct list *ls;
	{
	if (!ls) return;
	if (ls->nxtlist)
		freelst(ls->nxtlist);
	chfree(ls,sizeof(*ls));
	}


oneelt(ls)		/* return w if w is only elt of ls, UNDEFINED otherwise */
struct list *ls;
	{
	if (!ls) return(UNDEFINED);
	if (ls->nxtlist) return(UNDEFINED);
	return(ls->elt);
	}


lslen(ls)		/* return number of elements in list ls */
struct list *ls;
	{
	int count;
	struct list *lp;
	count = 0;
	for (lp = ls; lp; lp = lp->nxtlist)
		++count;
	return(count);
	}


prlst(ls)
struct list *ls;
	{
	struct list *lp;
	for (lp = ls; lp; lp = lp->nxtlist)
		printf("%d,",lp->elt);
	fprintf(stderr,"\n");
	}
E 1
