h54009
s 00011/00000/00032
d D 5.2 91/04/12 15:42:43 bostic 2 1
c new copyright; att/bsd/shared
e
s 00032/00000/00000
d D 5.1 90/06/25 14:07:16 bostic 1 0
c date and time created 90/06/25 14:07:16 by bostic
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
	.asciz "%W% (Berkeley) %G%"
#endif /* not lint */

E 2
I 1
	.data
	.even
L16:
	0.;8.
	.even
L17:
	-1.;-1.
	.data
	.bss
~~sigfpe_ = _sigfpe_
~~:
	.data
	.globl	_sigfpe_
	.globl	_signal_
	.even
.text
jbr	L11
L14:mov	$L17,(sp)
mov	r5,-(sp)
mov	$L16,-(sp)
jsr	pc,*$_signal_
cmp	(sp)+,(sp)+
jbr	L13
L13:L12:jmp	cret
L11:_sigfpe_:
~~sigfpe_:
jsr	r5,csv
mov	r5,r4
add	$4,r4
jbr	L14
.globl
.data
E 1
