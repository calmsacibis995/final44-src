h15875
s 00002/00002/00022
d D 8.1 93/06/04 12:07:21 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00018
d D 5.5 91/02/23 19:50:17 donn 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00022
d D 5.4 90/06/01 14:17:51 bostic 7 6
c new copyright notice
e
s 00014/00003/00019
d D 5.3 88/08/03 15:56:28 bostic 6 5
c written by Sam Leffler; add Berkeley specific copyright
e
s 00002/00002/00020
d D 5.2 86/03/09 20:01:20 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00015
d D 5.1 85/05/30 10:53:14 dist 4 3
c Add copyright
e
s 00004/00002/00012
d D 4.3 83/07/01 18:33:06 sam 3 2
c include fixes
e
s 00004/00005/00010
d D 4.2 83/07/01 04:02:33 sam 2 1
c delete valign.h in favor of sys call
e
s 00015/00000/00000
d D 4.1 80/12/21 16:40:28 wnj 1 0
c date and time created 80/12/21 16:40:28 by wnj
e
u
U
t
T
I 4
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
#include <valign.h>
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4
E 3
E 2

D 8
char	*malloc();
E 8
I 8
#include <stdlib.h>
#include <unistd.h>
E 8

D 8
char *
E 8
I 8
void *
E 8
valloc(i)
D 8
	int i;
E 8
I 8
	size_t i;
E 8
{
D 2
	char *cp = malloc(i + (VALSIZ-1));
	int j;
E 2
I 2
	int valsiz = getpagesize(), j;
D 3
	char *cp = malloc(i + (valsize-1));
E 3
I 3
D 8
	char *cp = malloc(i + (valsiz-1));
E 8
I 8
	void *cp = malloc(i + (valsiz-1));
E 8
E 3
E 2

D 2
	j = ((int)cp + (VALSIZ-1)) &~ (VALSIZ-1);
E 2
I 2
	j = ((int)cp + (valsiz-1)) &~ (valsiz-1);
E 2
D 8
	return ((char *)j);
E 8
I 8
	return ((void *)j);
E 8
}
E 1
