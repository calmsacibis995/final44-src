h12864
s 00000/00000/00057
d D 8.1 93/06/06 16:29:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00051
d D 4.2 91/04/16 16:48:42 bostic 2 1
c new copyright; att/bsd/shared
e
s 00053/00000/00000
d D 4.1 83/02/11 15:44:31 rrh 1 0
c date and time created 83/02/11 15:44:31 by rrh
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
#include "2.def.h"

VERT *after;
int *ntobef, *ntoaft;
build()
	{
	VERT v, *dom, *head;
	int type;
	struct list **inarc;
	dfs(START);
	if (routerr) return;
	for (v = 0; v < nodenum; ++v)
		{
		type = NTYPE(v);
		if (type == LOOPVX || type == DOVX)
			FATH(ARC(v,0)) = v;
		}

	head = challoc(sizeof(*head) * nodenum);
	if (progress) fprintf(stderr,"	gethead:\n");
	gethead(head);	/* sets head[v] to ITERVX heading smallest loop containing v or UNDEFINED */

	if (routerr) return;
	inarc = challoc(nodenum * sizeof(*inarc));
	if (progress) fprintf(stderr,"	getinarc:\n");
	getinarc(inarc,head);		/* sets inarc[v] to list of forward arcs entering v */

	dom = challoc(nodenum * sizeof(*dom));
	if (progress) fprintf(stderr,"	getdom:\n");
	getdom(inarc,dom);	/* sets dom[v] to immediate dominator of v or UNDEFINED */
	if (routerr) return;
	if (progress) fprintf(stderr,"	gettree:\n");
	gettree(inarc, dom, head);
	if (routerr) return;

	chfree(head, nodenum * sizeof(*head)); head = 0;
	chfree(dom,nodenum * sizeof(*dom)); dom = 0;
	for (v = 0; v < nodenum; ++v)
		{
		freelst(inarc[v]);
		inarc[v] = 0;
		}
	chfree(inarc,sizeof(*inarc) * nodenum); inarc = 0;
	chfree(ntoaft,sizeof(*ntoaft) * nodenum); ntoaft = 0;
	chfree(ntobef,sizeof(*ntobef) * nodenum); ntobef = 0;
	chfree(after, sizeof(*after) * accessnum); after = 0;
	}
E 1
