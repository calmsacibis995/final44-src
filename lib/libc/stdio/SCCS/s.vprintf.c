h25558
s 00002/00002/00020
d D 8.1 93/06/04 13:10:22 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00021
d D 5.7 92/06/23 09:58:28 bostic 7 6
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00000/00001/00022
d D 5.6 91/02/24 13:30:30 bostic 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00022
d D 5.5 91/02/01 19:32:12 bostic 5 4
c stdc.h -> cdefs.h
e
s 00009/00010/00014
d D 5.4 91/01/20 21:32:18 bostic 4 3
c new stdio
e
s 00001/00011/00023
d D 5.3 90/06/01 14:43:54 bostic 3 2
c new copyright notice
e
s 00010/00005/00024
d D 5.2 88/06/27 17:50:09 bostic 2 1
c install approved copyright notice
e
s 00029/00000/00000
d D 5.1 88/05/24 18:59:04 bostic 1 0
c date and time created 88/05/24 18:59:04 by bostic
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1988 Regents of the University of California.
E 4
I 4
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
I 4
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
E 4
D 3
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 4
D 5
#include <sys/stdc.h>
E 5
I 5
D 6
#include <sys/cdefs.h>
E 6
E 5
E 4
#include <stdio.h>
D 4
#include <varargs.h>
E 4

D 4
int
E 4
vprintf(fmt, ap)
D 4
	char *fmt;
	va_list ap;
E 4
I 4
	char const *fmt;
D 7
	_VA_LIST_ ap;
E 7
I 7
	_BSD_VA_LIST_ ap;
E 7
E 4
{
D 4
	int len;

	len = _doprnt(fmt, ap, stdout);
	return (ferror(stdout) ? EOF : len);
E 4
I 4
	return (vfprintf(stdout, fmt, ap));
E 4
}
E 1
