h38538
s 00002/00002/00031
d D 8.1 93/06/04 12:50:35 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00029
d D 5.6 91/02/24 12:40:14 bostic 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00029
d D 5.5 90/06/01 14:15:45 bostic 6 5
c new copyright notice
e
s 00010/00005/00030
d D 5.4 88/06/27 18:28:13 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00026
d D 5.3 88/03/07 21:07:42 bostic 4 3
c add Berkeley specific headers
e
s 00002/00002/00027
d D 5.2 86/03/09 20:11:33 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00020
d D 5.1 85/05/30 11:15:59 dist 2 1
c Add copyright
e
s 00021/00000/00000
d D 4.1 83/06/12 02:36:14 root 1 0
c date and time created 83/06/12 02:36:14 by root
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
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
E 2

/*
 * Convert network-format internet address
 * to base 256 d.d.d.d representation.
 */
#include <sys/types.h>
#include <netinet/in.h>
I 7
#include <arpa/inet.h>
#include <stdio.h>
E 7

char *
inet_ntoa(in)
	struct in_addr in;
{
	static char b[18];
	register char *p;

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
D 7
	sprintf(b, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
E 7
I 7
	(void)snprintf(b, sizeof(b),
	    "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
E 7
	return (b);
}
E 1
