h40716
s 00002/00002/00021
d D 8.1 93/06/04 15:44:11 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00012/00011
d D 5.5 91/04/18 19:05:49 bostic 7 6
c new version from Chris Torek
e
s 00008/00007/00015
d D 5.4 91/04/12 13:04:31 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00002/00020
d D 5.3 86/03/09 21:11:03 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00021
d D 5.2 85/06/05 18:56:55 mckusick 4 3
c Fix copyright
e
s 00010/00001/00012
d D 5.1 85/05/30 15:11:56 dist 3 2
c Add copyright
e
s 00002/00002/00011
d D 4.2 84/11/01 23:51:15 sam 2 1
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00013/00000/00000
d D 4.1 83/06/27 16:08:47 root 1 0
c date and time created 83/06/27 16:08:47 by root
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1983 The Regents of the University of California.
E 7
I 7
D 8
 * Copyright (c) 1991 The Regents of the University of California.
E 7
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
 * %sccs.include.proprietary.c%
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */

D 5
#ifndef lint
E 5
I 5
D 6
#ifdef LIBC_SCCS
E 5
D 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
I 4
	.asciz	"%W% (Berkeley) %G%"
E 4
D 5
#endif not lint
E 5
I 5
#endif LIBC_SCCS
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 6
E 5

E 3
D 2
/* like alloc, but automatic automatic free in return */
E 2
I 2
D 7
/* like alloc, but automatic free in return */
E 2

E 7
#include "DEFS.h"

D 2
ENTRY(alloca)
E 2
I 2
D 7
ENTRY(alloca, 0)
E 2
	subl2	4(ap),sp	/* crude allocation */
	movl	16(fp),r1	/* pc */
	movq	8(fp),ap	/* new (old) ap and fp */
	bicl2	$3,sp		/* 4-byte align */
	addl2	$7*4,sp		/* reuse space of mscp */
	movl	sp,r0		/* return value */
	jmp 	(r1)		/* funny return */
E 7
I 7
ENTRY(alloca, 0)
	movl	4(ap),r0	# get allocation size
	movl	16(fp),r2	# save return address before we smash it
	movab	here,16(fp)
	ret
here:
	subl2	r0,sp		# create stack space
	bicl2	$3,sp		# align to longword boundary
	movl	sp,r0
	jmp	(r2)
E 7
E 1
