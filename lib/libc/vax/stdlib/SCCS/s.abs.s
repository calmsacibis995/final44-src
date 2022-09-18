h13401
s 00002/00002/00017
d D 8.1 93/06/04 16:15:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00016
d D 5.6 91/11/12 13:43:53 bostic 8 7
c add register save mask, include DEFS.h
e
s 00004/00006/00013
d D 5.5 91/04/12 16:56:03 bostic 7 6
c from Donn Seeley -- from scratch, add Berkeley copyright
e
s 00008/00010/00011
d D 5.4 91/04/12 13:38:11 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00002/00019
d D 5.3 86/03/09 21:10:51 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00020
d D 5.2 85/06/05 18:56:42 mckusick 4 3
c Fix copyright
e
s 00010/00001/00011
d D 5.1 85/05/30 15:19:11 dist 3 2
c Add copyright
e
s 00001/00001/00011
d D 4.2 84/11/01 23:51:12 sam 2 1
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00012/00000/00000
d D 4.1 83/06/27 15:41:44 root 1 0
c date and time created 83/06/27 15:41:44 by root
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
 * Copyright (c) 1984 The Regents of the University of California.
E 7
I 7
D 9
 * Copyright (c) 1991 The Regents of the University of California.
E 7
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
E 5

E 3

/* abs - int absolute value */
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 6

D 7
#include "DEFS.h"

D 2
ENTRY(abs)
E 2
I 2
ENTRY(abs, 0)
E 7
I 7
D 8
ENTRY(abs)
E 8
I 8
#include "DEFS.h"

ENTRY(abs, 0)
E 8
E 7
E 2
	movl	4(ap),r0
D 7
	bgeq	1f
E 7
I 7
	jgeq	1f
E 7
	mnegl	r0,r0
1:
	ret
E 1
