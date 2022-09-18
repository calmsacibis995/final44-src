h10161
s 00002/00002/00031
d D 8.1 93/06/04 15:11:05 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00031
d D 5.10 92/08/07 08:56:23 bostic 11 10
c prototype typo
e
s 00002/00002/00030
d D 5.9 91/02/24 13:57:46 bostic 10 9
c Add include files to get prototype declarations, and fix bugs found.
e
s 00004/00000/00028
d D 5.8 90/06/23 11:00:18 bostic 9 8
c build strrchr out of rindex
e
s 00001/00011/00027
d D 5.7 90/06/01 14:45:11 bostic 8 7
c new copyright notice
e
s 00001/00000/00037
d D 5.6 90/05/17 12:05:35 bostic 7 6
c keep string.h and source in sync
e
s 00001/00001/00036
d D 5.5 90/05/16 17:17:20 bostic 6 5
c use right include file
e
s 00010/00005/00027
d D 5.4 88/06/27 17:34:11 bostic 5 4
c install approved copyright notice
e
s 00021/00016/00008
d D 5.3 88/06/02 09:28:09 bostic 4 3
c rewritten from scratch; add Berkeley specific header
e
s 00002/00002/00022
d D 5.2 86/03/09 19:54:26 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00005/00002/00019
d D 5.1 85/06/05 12:31:05 mckusick 2 1
c Add copyright
e
s 00021/00000/00000
d D 4.1 80/12/21 16:40:05 wnj 1 0
c date and time created 80/12/21 16:40:05 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
D 4
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif LIBC_SCCS and not lint
E 3

E 4
E 2
/*
D 4
 * Return the ptr in sp at which the character c last
 * appears; NULL if not found
E 4
I 4
D 12
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 5
E 4
D 2
*/
E 2
I 2
 */
E 2

D 4
#define NULL 0
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 4

I 4
D 6
#include <stdio.h>
E 6
I 6
#include <stddef.h>
I 7
#include <string.h>
E 7
E 6

E 4
char *
I 9
#ifdef STRRCHR
strrchr(p, ch)
#else
E 9
D 4
rindex(sp, c)
register char *sp, c;
E 4
I 4
rindex(p, ch)
I 9
#endif
E 9
D 10
	register char *p, ch;
E 10
I 10
D 11
	register const char *p, ch;
E 11
I 11
	register const char *p;
	register int ch;
E 11
E 10
E 4
{
D 4
	register char *r;
E 4
I 4
	register char *save;
E 4

D 4
	r = NULL;
	do {
		if (*sp == c)
			r = sp;
	} while (*sp++);
	return(r);
E 4
I 4
	for (save = NULL;; ++p) {
		if (*p == ch)
D 10
			save = p;
E 10
I 10
			save = (char *)p;
E 10
		if (!*p)
			return(save);
	}
	/* NOTREACHED */
E 4
}
E 1
