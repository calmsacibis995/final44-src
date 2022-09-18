h48942
s 00002/00002/00029
d D 8.1 93/06/04 15:40:11 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00030
d D 5.6 90/06/01 14:53:05 bostic 9 8
c new copyright notice
e
s 00013/00008/00028
d D 5.5 88/06/27 17:25:02 bostic 8 7
c install approved copyright notice
e
s 00011/00005/00025
d D 5.4 88/05/25 17:13:42 bostic 7 6
c written by Kirk McKusick and Sam Leffler; add Berkeley specific header
e
s 00002/00002/00028
d D 5.3 86/03/09 21:11:31 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00029
d D 5.2 85/06/05 18:57:38 mckusick 5 4
c Fix copyright
e
s 00010/00001/00020
d D 5.1 85/05/30 15:12:57 dist 4 3
c Add copyright
e
s 00001/00001/00020
d D 4.3 84/11/01 23:51:28 sam 3 2
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00014/00001/00007
d D 4.2 83/01/14 15:08:35 mckusick 2 1
c fix to allow compares of greater than 65K
e
s 00008/00000/00000
d D 4.1 82/12/15 15:33:33 sam 1 0
c date and time created 82/12/15 15:33:33 by sam
e
u
U
t
T
I 1
D 4
/* %W% %G% */
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
/* bcmp(s1, s2, n) */

#include "DEFS.h"

D 3
ENTRY(bcmp)
E 3
I 3
ENTRY(bcmp, 0)
E 3
D 2
	cmpc3	12(ap), *4(ap), *8(ap)
E 2
I 2
	movl	4(ap),r1
	movl	8(ap),r3
	movl	12(ap),r4
1:
	movzwl	$65535,r0
	cmpl	r4,r0
	jleq	2f
	subl2	r0,r4
	cmpc3	r0,(r1),(r3)
	jeql	1b
	addl2	r4,r0
	ret
2:
	cmpc3	r4,(r1),(r3)
E 2
	ret
E 1
