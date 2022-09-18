h03015
s 00002/00002/00034
d D 8.1 93/06/04 15:41:12 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00035
d D 5.6 90/06/01 14:54:19 bostic 9 8
c new copyright notice
e
s 00013/00008/00033
d D 5.5 88/06/27 17:25:22 bostic 8 7
c install approved copyright notice
e
s 00011/00005/00030
d D 5.4 88/05/25 17:14:14 bostic 7 6
c written by Kirk McKusick and Sam Leffler; add Berkeley specific header
e
s 00002/00002/00033
d D 5.3 86/03/09 21:14:46 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00034
d D 5.2 85/06/05 19:00:48 mckusick 5 4
c Fix copyright
e
s 00009/00001/00026
d D 5.1 85/05/30 15:17:01 dist 4 3
c Add copyright
e
s 00003/00002/00024
d D 4.3 84/11/07 12:24:03 mckusick 3 2
c return proper value; fix bug in >65535 byte copies
e
s 00002/00003/00024
d D 4.2 84/11/01 23:52:11 sam 2 1
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00027/00000/00000
d D 4.1 84/11/01 23:19:41 sam 1 0
c date and time created 84/11/01 23:19:41 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
E 7
 */

D 6
#ifndef lint
E 6
I 6
D 7
#ifdef LIBC_SCCS
E 6
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
	.asciz	"%W% (Berkeley) %G%"
E 5
D 6
#endif not lint
E 6
I 6
#endif LIBC_SCCS
E 7
I 7
D 8
#if defined(SYSLIBC_SCCS) && !defined(lint)
_sccsid:.asciz	"%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 8
I 8
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 8
E 7
E 6
E 4

/*
 * Copy string s2 over top of s1.
I 3
 * Return base of s1.
E 3
 *
 * char *
 * strcpy(s1, s2)
 *	char *s1, *s2;
 */
D 2
	.globl	_strcpy
E 2
I 2
#include "DEFS.h"
E 2

D 2
_strcpy:
	.word	0x80
E 2
I 2
ENTRY(strcpy, R6)
E 2
	movl	4(ap), r3	# r3 = s1
	movl	8(ap), r6	# r6 = s2
1:
	locc	$0,$65535,(r6)	# find length of s2
	bneq	2f
	movc3	$65535,(r6),(r3)# copy full block
D 3
	movl	r6,r1
E 3
I 3
	movl	r1,r6
E 3
	jbr	1b
2:
	subl2	r6,r1		# calculate length
	incl	r1
	movc3	r1,(r6),(r3)	# copy remainder
D 3
	movl	r6,r0
E 3
I 3
	movl	4(ap),r0	# return base of s1
E 3
	ret
E 1
