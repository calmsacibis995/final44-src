h06239
s 00013/00001/00027
d D 5.2 91/04/12 15:16:06 bostic 2 1
c new copyright; att/bsd/shared
e
s 00028/00000/00000
d D 5.1 86/11/03 20:00:53 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
#	"%W% (Berkeley) %G%"
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
	.asciz "%W% (Berkeley) %G%"
#endif /* not lint */
E 2

.data
.text
LL0:.align	1
.globl	_s_copy
.set	MASK__,0x1004		/* save r2, r12 */
.data
.text
_s_copy:.word	MASK__
movl	4(fp),r1		/* dest addr */
movl	8(fp),r0		/* src addr */
movl	12(fp),r12		/* dest length */
cmpl	r12,16(fp)		/* if (ldest <= lsrc) */
jgtr	L16
movl	r12, r2			/* copy according to ldest */
movs3
ret
L16: 				/* else */
movl	16(fp),r2		/* copy according to lsrc */
movs3
addl2	4(fp),r12		/* and pad with spaces */
L20:movb	$32,(r1)
incl	r1
cmpl	r1,r12
jlssu	L20
ret

E 1
