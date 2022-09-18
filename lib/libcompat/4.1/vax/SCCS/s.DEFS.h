h26008
s 00002/00002/00016
d D 8.1 93/06/04 16:21:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00013
d D 5.2 91/04/12 13:55:04 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00010
d D 5.1 85/05/30 14:51:44 dist 2 1
c Add copyright
e
s 00011/00000/00000
d D 4.1 83/07/05 19:55:38 sam 1 0
c date and time created 83/07/05 19:55:38 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */
E 2

#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0
#endif
E 1
