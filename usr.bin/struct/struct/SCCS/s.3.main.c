h26934
s 00000/00000/00041
d D 8.1 93/06/06 16:29:50 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00035
d D 4.2 91/04/16 16:48:47 bostic 2 1
c new copyright; att/bsd/shared
e
s 00037/00000/00000
d D 4.1 83/02/11 15:44:43 rrh 1 0
c date and time created 83/02/11 15:44:43 by rrh
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

structure()
	{
	VERT v, *head;

	if (progress)
		fprintf(stderr,"	getreach:\n");
	getreach();
	if (routerr) return;
	if (progress)
		fprintf(stderr,"	getflow:\n");
	getflow();
	if (progress)
		fprintf(stderr,"	getthen:\n");
	getthen(START);
	head = challoc(nodenum * sizeof(*head));
	for (v = 0; v < nodenum; ++v)
		head[v] = UNDEFINED;
	for (v = START; DEFINED(v); v = RSIB(v))
		fixhd(v,UNDEFINED,head);
			/* fixhd must be called before getloop so that
				it gets applied to IFVX which becomes NXT(w) for UNTVX w */
	if (progress)
		fprintf(stderr,"	getloop:\n");
	getloop();
	if (progress)
		fprintf(stderr,"	getbranch:\n");
	getbranch(head);
	chfree(head,nodenum * sizeof(*head));
	head = 0;
	}
E 1
