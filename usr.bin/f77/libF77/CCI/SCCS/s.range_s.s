h29243
s 00013/00001/00069
d D 5.2 91/04/12 15:16:02 bostic 2 1
c new copyright; att/bsd/shared
e
s 00070/00000/00000
d D 5.1 86/11/03 20:00:47 mckusick 1 0
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
.globl	_flmax_
.set	MASK__1,0x0
.data
.text
_flmax_:.word	MASK__1
movl	$2147483647,r0
ret#1

.align	1
.globl	_dflmax_
.set	MASK__2,0x0
.data
.text
_dflmax_:.word	MASK__2
movl	$2147483647,r0
movl	$0xffffffff,r1
ret#2

.align	1
.globl	_flmin_
.set	MASK__3,0x0
.data
.text
_flmin_:.word	MASK__3
movl	$8388608,r0
ret#1

.align	1
.globl	_dflmin_
.set	MASK__4,0x0
.data
.text
_dflmin_:.word	MASK__4
movl	$8388608,r0
clrl	r1
ret#2

.align	1
.globl	_inmax_
.set	MASK__5,0x0
.data
.text
_inmax_:.word	MASK__5
movl	$2147483647,r0
ret#1

.align	1
.globl	_ffrac_
.set	MASK__6,0x0
.data
.text
_ffrac_:.word	MASK__6
movl	$889192448,r0
ret#1

.align	1
.globl	_dffrac_
.set	MASK__7,0x0
.data
.text
_dffrac_:.word	MASK__7
movl	$620756992,r0
clrl	r1
ret#2

E 1
