h04953
s 00000/00000/00030
d D 8.1 93/06/06 16:30:05 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00024
d D 4.2 91/04/16 16:48:52 bostic 2 1
c new copyright; att/bsd/shared
e
s 00026/00000/00000
d D 4.1 83/02/11 15:44:56 rrh 1 0
c date and time created 83/02/11 15:44:56 by rrh
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
#include "4.def.h"

LOGICAL *brace;
output()
	{
	VERT w;
	int i;
	brace = challoc(nodenum * sizeof(*brace));
	for (i = 0; i < nodenum; ++i)
		brace[i] = FALSE;
	if (progress) fprintf(stderr,"ndbrace:\n");
	for (w = START; DEFINED(w); w = RSIB(w))
		ndbrace(w);
	if (progress) fprintf(stderr,"outrat:\n");
	for (w = START; DEFINED(w); w = RSIB(w))
		outrat(w,0,YESTAB);
	OUTSTR("END\n");
	chfree(brace,nodenum * sizeof(*brace));
	brace = 0;
	}
E 1
