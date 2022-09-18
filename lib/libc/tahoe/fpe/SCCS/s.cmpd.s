h42308
s 00002/00002/00055
d D 8.1 93/06/04 13:13:52 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00056
d D 1.4 90/06/01 14:47:10 bostic 4 3
c new copyright notice
e
s 00023/00003/00044
d D 1.3 89/02/17 17:35:24 bostic 3 2
c add Berkeley specific copyright notice
e
s 00004/00000/00043
d D 1.2 86/07/02 16:27:04 sam 2 1
c add sccsid
e
s 00043/00000/00000
d D 1.1 86/07/02 16:25:46 sam 1 0
c date and time created 86/07/02 16:25:46 by sam
e
u
U
t
T
I 2
D 3
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS
E 3
I 3
/*
D 5
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 3

E 2
I 1
#include "DEFS.h"

XENTRY(cmpd, R12|R11|R10|R9)
	movl	4(fp),r12
	movl	8(fp),r10
	movl	12(fp),r11
	movl	16(fp),r9
	tstl	r12
	jgeq	L16
	xorl2	$-2147483648,r12
	tstl	r10
	jeql	L17
	mnegl	r10,r10
	mcoml	r12,r12
	jbr	L16
L17:	mnegl	r12,r12
L16:	tstl	r11
	jgeq	L19
	xorl2	$-2147483648,r11
	tstl	r9
	jeql	L20
	mnegl	r9,r9
	mcoml	r11,r11
	jbr	L19
L20:	mnegl	r11,r11
L19:	cmpl	r12,r11
	jeql	L22
	cmpl	r12,r11
	jleq	L9999
	movl	$1,r0
	jbr	L9998
L9999:	mnegl	$1,r0
L9998:	ret
L22:	cmpl	r10,r9
	jeql	L23
	cmpl	r10,r9
	jlequ	L9997
	movl	$1,r0
	jbr	L9996
L9997:	mnegl	$1,r0
L9996:	ret
L23:	clrl	r0
	ret
E 1
