h59543
s 00002/00002/00036
d D 8.1 93/06/04 12:13:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00005/00022
d D 5.2 93/05/03 16:10:39 hibler 2 1
c add STDC versions for both gcc1 and gcc2, eliminate non-gcc versions
e
s 00027/00000/00000
d D 5.1 90/05/12 16:01:37 bostic 1 0
c date and time created 90/05/12 16:01:37 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#ifdef __STDC__
E 2
#ifdef PROF
D 2
#ifdef __GNUC__
E 2
I 2
#if __GNUC__ >= 2
E 2
#define	ENTRY(x) \
D 2
	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; .long 0; .text; \
	link a6,#0; lea PROF/**/x,a0; jsr mcount; unlk a6
E 2
I 2
	.globl _ ## x; .even; _ ## x:; .data; PROF ## x:; .long 0; .text; \
	link a6,\#0; lea PROF ## x,a0; jsr mcount; unlk a6
E 2
#else
#define	ENTRY(x) \
D 2
	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; .long 0; .text; \
	lea PROF/**/x,a0; jsr mcount
E 2
I 2
	.globl _ ## x; .even; _ ## x:; .data; PROF ## x:; .long 0; .text; \
	link a6,#0; lea PROF ## x,a0; jsr mcount; unlk a6
E 2
#endif
#else
#define	ENTRY(x) \
I 2
	.globl _ ## x; .even; _ ## x:
#endif
#else
#ifdef PROF
#define	ENTRY(x) \
	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; .long 0; .text; \
	link a6,#0; lea PROF/**/x,a0; jsr mcount; unlk a6
#else
#define	ENTRY(x) \
E 2
	.globl _/**/x; .even; _/**/x:
I 2
#endif
E 2
#endif
E 1
