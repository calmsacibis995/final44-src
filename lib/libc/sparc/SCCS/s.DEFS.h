h10326
s 00002/00002/00022
d D 8.1 93/06/04 13:02:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00000/00017
d D 5.2 92/06/25 06:01:12 torek 2 1
c copyright
e
s 00017/00000/00000
d D 5.1 92/06/25 05:58:23 torek 1 0
c date and time created 92/06/25 05:58:23 by torek
e
u
U
t
T
I 1
/*-
I 2
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef PROF
#define	FUNC(x) \
	.align 4; .globl x; .proc 1; x:; .data; .align 4; 1: .long 0; \
	.text; save %sp,-96,%sp; sethi %hi(1b),%o0; call mcount; \
	or %lo(1b),%o0,%o0; restore
#else
#define	FUNC(x) \
	.align 4; .globl x; .proc 1; x:
#endif

#define	ENTRY(x) FUNC(_##x)
E 1
