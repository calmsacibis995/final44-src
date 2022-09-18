h57849
s 00002/00002/00017
d D 8.1 93/06/04 13:05:10 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00018
d D 5.7 91/02/23 22:56:32 donn 10 9
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00011/00018
d D 5.6 90/06/01 14:44:05 bostic 9 8
c new copyright notice
e
s 00002/00003/00027
d D 5.5 90/05/16 13:49:42 bostic 8 7
c cleanup includes
e
s 00005/00015/00025
d D 5.4 89/11/01 11:19:03 bostic 7 6
c use strtol()
e
s 00033/00021/00007
d D 5.3 88/07/19 14:25:59 bostic 6 5
c rewritten from the manual page; add Berkeley specific header
e
s 00002/00002/00026
d D 5.2 86/03/09 19:44:23 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00024
d D 5.1 85/06/05 12:03:44 mckusick 4 3
c Add copyright
e
s 00001/00001/00024
d D 4.3 81/02/28 22:25:24 wnj 3 2
c now ident to atol
e
s 00017/00017/00008
d D 4.2 81/02/28 22:24:42 wnj 2 1
c now same as atoi
e
s 00025/00000/00000
d D 4.1 80/12/21 16:39:26 wnj 1 0
c date and time created 80/12/21 16:39:26 by wnj
e
u
U
t
T
I 6
/*
D 11
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

E 6
I 1
D 2
/* %W% (Berkeley) %G% */
atoi(ap)
char *ap;
E 2
I 2
D 3
/* @(#)atoi.c	4.2 (Berkeley) 1/11/81 */
E 3
I 3
D 4
/* %W% (Berkeley) %E% */
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
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
D 6
atoi(p)
register char *p;
E 6
I 6
D 7
#include <ctype.h>
E 7
I 7
D 8
#include <stdio.h>
E 8
I 8
#include <stdlib.h>
#include <stddef.h>
E 8
E 7

D 7
atoi(ascii)
	register char *ascii;
E 7
I 7
atoi(str)
D 10
	char *str;
E 10
I 10
	const char *str;
E 10
E 7
E 6
E 2
{
D 2
	register int  n, c;
	register char *p;
	int f;
E 2
I 2
D 6
	register int n;
	register int f;
E 6
I 6
D 7
	register int val;
	int negative = 0;
E 7
I 7
D 8
	long strtol();
E 7
E 6
E 2

E 8
D 2
	p = ap;
E 2
D 6
	n = 0;
	f = 0;
D 2
loop:
	while(*p == ' ' || *p == '	')
		p++;
	if(*p == '-') {
		f++;
		p++;
		goto loop;
E 2
I 2
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
E 6
I 6
D 7
	for (; isascii(*ascii) && isspace(*ascii); ++ascii);
	if (*ascii == '+')
		++ascii;
	else if (*ascii == '-') {
		++ascii;
		negative = 1;
E 6
E 2
	}
D 6
	while(*p >= '0' && *p <= '9')
		n = n*10 + *p++ - '0';
D 2
	if(f)
		n = -n;
	return(n);
E 2
I 2
	return(f? -n: n);
E 6
I 6
	for (val = 0; isascii(*ascii) && isdigit(*ascii); ++ascii)
		val = val * 10 + *ascii - '0';
	return(negative ? -val : val);
E 7
I 7
	return((int)strtol(str, (char **)NULL, 10));
E 7
E 6
E 2
}
E 1
