h56801
s 00002/00002/00029
d D 8.1 93/06/04 15:10:30 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00028
d D 5.7 91/02/24 13:57:45 bostic 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00004/00000/00026
d D 5.6 90/06/23 11:00:05 bostic 7 6
c build strchr out of index
e
s 00005/00014/00021
d D 5.5 90/05/16 16:44:08 bostic 6 5
c cleanup includes, copyright
e
s 00010/00005/00025
d D 5.4 88/06/27 17:34:07 bostic 5 4
c install approved copyright notice
e
s 00023/00014/00007
d D 5.3 88/06/02 09:27:58 bostic 4 3
c rewritten from scratch; add Berkeley specific header
e
s 00002/00002/00019
d D 5.2 86/03/09 19:49:42 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00017
d D 5.1 85/06/05 12:25:39 mckusick 2 1
c Add copyright
e
s 00018/00000/00000
d D 4.1 80/12/21 16:39:43 wnj 1 0
c date and time created 80/12/21 16:39:43 by wnj
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
D 6
/*
D 4
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
E 4
I 4
 * Copyright (c) 1988 Regents of the University of California.
E 6
I 6
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
E 6
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

D 4
#define	NULL	0
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 4

I 8
#include <sys/cdefs.h>
E 8
I 4
D 6
#include <stdio.h>
E 6
I 6
#include <string.h>
#include <stddef.h>
E 6

E 4
char *
I 7
#ifdef STRCHR
strchr(p, ch)
#else
E 7
D 4
index(sp, c)
register char *sp, c;
E 4
I 4
index(p, ch)
I 7
#endif
E 7
D 8
	register char *p, ch;
E 8
I 8
	register const char *p, ch;
E 8
E 4
{
D 4
	do {
		if (*sp == c)
			return(sp);
	} while (*sp++);
	return(NULL);
E 4
I 4
	for (;; ++p) {
		if (*p == ch)
D 8
			return(p);
E 8
I 8
			return((char *)p);
E 8
		if (!*p)
			return((char *)NULL);
	}
	/* NOTREACHED */
E 4
}
E 1
