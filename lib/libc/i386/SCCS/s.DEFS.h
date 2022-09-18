h64892
s 00002/00002/00019
d D 8.1 93/06/04 12:41:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00000/00000
d D 5.1 90/04/23 19:56:45 william 1 0
c date and time created 90/04/23 19:56:45 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; _/**/x:  \
			.data; 1:; .long 0; .text; lea 1b,%eax ; call mcount
#define	ASENTRY(x)	.globl x; x: \
			.data; 1:; .long 0; .text; lea 1b,%eax ; call mcount
#else
#define	ENTRY(x)	.globl _/**/x; _/**/x: 
#define	ASENTRY(x)	.globl x; x: 
#endif
E 1
