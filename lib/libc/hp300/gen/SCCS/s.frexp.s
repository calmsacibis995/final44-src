h36314
s 00027/00033/00001
d D 5.2 91/04/12 12:30:37 bostic 2 1
c another version (completely different)
c put under SCCS simply to keep around, frexp.c is the current version
e
s 00034/00000/00000
d D 5.1 90/05/12 15:47:33 bostic 1 0
c date and time created 90/05/12 15:47:33 by bostic
e
u
U
t
T
I 1
D 2
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "DEFS.h"

/*
 * double frexp(val, eptr)
 * returns: x s.t. val = x * (2 ** n), with n stored in *eptr
 */
ENTRY(frexp)
	fmoved		sp@(4),fp1
	fgetmanx	fp1,fp0
	fgetexpx	fp1
	fmovel		fp1,d0
	addql		#1,d0
	movel		sp@(12),a0
	movel		d0,a0@
	fdivl		#2,fp0
	fmoved		fp0,sp@-
	movel		sp@+,d0
	movel		sp@+,d1
E 2
I 2
#NO_APP
gcc_compiled.:
.text
	.even
.globl _frexp
_frexp:
	link a6,#0
	moveml #0x3000,sp@-
	fmoved a6@(8),fp0
	movel a6@(16),a0
	fjeq L2
	fmoved fp0,sp@-
	movel sp@+,d0
	movel sp@+,d1
	bfextu d0{#1:#11},d2
	addl #-1022,d2
	movel d2,a0@
	movel #1022,d3
	bfins d3,d0{#1:#11}
	jra L1
L2:
	clrl a0@
	clrl d0
	clrl d1
L1:
	moveml a6@(-8),#0xc
	unlk a6
E 2
	rts
E 1
