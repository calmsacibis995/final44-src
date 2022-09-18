h00842
s 00013/00001/00025
d D 5.2 91/04/12 15:16:07 bostic 2 1
c new copyright; att/bsd/shared
e
s 00026/00000/00000
d D 5.1 86/11/03 20:00:54 mckusick 1 0
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
.globl	_system_
.set	MASK__,0x04
.data
.text
_system_:.word	MASK__
subl3	$1056,fp,sp
movl	4(fp),r0		/* s */
subl3	$1056,fp,r1		/* buf */
cmpl	8(fp),$1000		/* if (n < 1000) */
jgeq	L9999
movl	8(fp),r2		/* length = n */
jbr	L1000
L9999:
movl	$1000,r2		/* else length = 1000 */
L1000:
movs3				/* copy string */
clrb	(r1)			/* add end-of-str */
subl3	$1056,fp,-(sp)		/* push &buf */
callf	$8,_system
ret#2

E 1
