h64401
s 00009/00002/00019
d D 4.3 91/04/17 17:25:29 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00018
d D 4.2 83/08/11 20:39:09 sam 2 1
c standardize sccs keyword lines
e
s 00019/00000/00000
d D 4.1 83/02/11 18:28:25 shannon 1 0
c date and time created 83/02/11 18:28:25 by shannon
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3
E 2

#include "e.h"

mark(p1) int p1; {
	markline = 1;
	printf(".ds %d \\k(97\\*(%d\n", p1, p1);
	yyval = p1;
	if(dbg)printf(".\tmark %d\n", p1);
}

lineup(p1) {
	markline = 1;
	if (p1 == 0) {
		yyval = oalloc();
		printf(".ds %d \\h'|\\n(97u'\n", yyval);
	}
	if(dbg)printf(".\tlineup %d\n", p1);
}
E 1
