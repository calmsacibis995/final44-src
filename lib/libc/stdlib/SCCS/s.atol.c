h27081
s 00002/00002/00018
d D 8.1 93/06/04 13:05:21 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00019
d D 5.7 91/02/23 22:56:33 donn 8 7
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00011/00019
d D 5.6 90/06/01 14:44:13 bostic 7 6
c new copyright notice
e
s 00002/00003/00028
d D 5.5 90/05/16 13:50:12 bostic 6 5
c cleanup includes
e
s 00005/00015/00026
d D 5.4 89/11/01 11:17:23 bostic 5 4
c use strtol(3)
e
s 00033/00021/00008
d D 5.3 88/07/19 14:28:01 bostic 4 3
c rewritten from manual page; add Berkeley specific header
e
s 00002/00002/00027
d D 5.2 86/03/09 19:44:34 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00025
d D 5.1 85/06/05 12:07:54 mckusick 2 1
c Add copyright
e
s 00026/00000/00000
d D 4.1 80/12/21 16:39:27 wnj 1 0
c date and time created 80/12/21 16:39:27 by wnj
e
u
U
t
T
I 4
/*
D 9
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
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
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3

I 4
D 5
#include <ctype.h>
E 5
I 5
D 6
#include <stdio.h>
E 6
I 6
#include <stddef.h>
#include <stdlib.h>
E 6
E 5

E 4
E 2
long
D 4
atol(p)
register char *p;
E 4
I 4
D 5
atol(ascii)
	register char *ascii;
E 5
I 5
atol(str)
D 8
	char *str;
E 8
I 8
	const char *str;
E 8
E 5
E 4
{
D 4
	long n;
	register int f;
E 4
I 4
D 5
	register long val;
	int negative = 0;
E 5
I 5
D 6
	long strtol();
E 5
E 4

E 6
D 4
	n = 0;
	f = 0;
	for(;;p++) {
		switch(*p) {
		case ' ':
		case '\t':
			continue;
		case '-':
			f++;
		case '+':
			p++;
		}
		break;
E 4
I 4
D 5
	for (; isascii(*ascii) && isspace(*ascii); ++ascii);
	if (*ascii == '+')
		++ascii;
	else if (*ascii == '-') {
		++ascii;
		negative = 1;
E 4
	}
D 4
	while(*p >= '0' && *p <= '9')
		n = n*10 + *p++ - '0';
	return(f? -n: n);
E 4
I 4
	for (val = 0; isascii(*ascii) && isdigit(*ascii); ++ascii)
		val = val * 10 + *ascii - '0';
	return(negative ? -val : val);
E 5
I 5
	return(strtol(str, (char **)NULL, 10));
E 5
E 4
}
E 1
