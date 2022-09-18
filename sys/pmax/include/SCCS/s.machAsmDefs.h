h04269
s 00002/00002/00136
d D 8.1 93/06/10 23:02:10 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00136
d D 7.6 93/05/09 16:06:58 ralph 6 5
c fix profiling defs for locore.s and config -p
e
s 00012/00000/00126
d D 7.5 93/04/13 20:06:27 ralph 5 4
c added NNON_LEAF for non-profiled non-leaf entry points.
e
s 00004/00004/00122
d D 7.4 93/02/26 19:11:46 ralph 4 3
c fix profiling
e
s 00030/00002/00096
d D 7.3 93/02/21 13:56:31 ralph 3 2
c define MCOUNT for profiling.
e
s 00010/00002/00088
d D 7.2 92/02/29 12:23:24 bostic 2 1
c combine C library and kernel versions of this file
e
s 00090/00000/00000
d D 7.1 92/01/07 20:35:48 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 2
 *
E 2
I 2
 */

/*
E 2
 * machAsmDefs.h --
 *
 *	Macros used when writing assembler programs.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: $Header: /sprite/src/kernel/mach/ds3100.md/RCS/machAsmDefs.h,
 *	v 1.2 89/08/15 18:28:24 rab Exp $ SPRITE (DECWRL)
 */

#ifndef _MACHASMDEFS
#define _MACHASMDEFS

I 2
#include <machine/regdef.h>

E 2
/*
I 3
 * Define -pg profile entry code.
 */
D 6
#ifdef PROF
E 6
I 6
#if defined(GPROF) || defined(PROF)
E 6
#define	MCOUNT	.set noreorder; \
		.set noat; \
		move $1,$31; \
D 4
		jal _mount; \
		subu sp,sp,8;
E 4
I 4
		jal _mcount; \
		subu sp,sp,8; \
E 4
		.set reorder; \
		.set at;
#else
#define	MCOUNT
D 6
#endif PROF
E 6
I 6
#endif
E 6

/*
E 3
 * LEAF(x)
 *
 *	Declare a leaf routine.
 */
#define LEAF(x) \
	.globl x; \
	.ent x, 0; \
x: ; \
I 3
D 4
	.frame sp, 0, ra \
E 4
I 4
	.frame sp, 0, ra; \
E 4
	MCOUNT

/*
 * NLEAF(x)
 *
 *	Declare a non-profiled leaf routine.
 */
#define NLEAF(x) \
	.globl x; \
	.ent x, 0; \
x: ; \
E 3
	.frame sp, 0, ra

/*
D 3
 * ALEAF -- declare alternate entry to leaf routine
E 3
I 3
 * ALEAF -- declare alternate entry to a leaf routine.
E 3
 */
#define	ALEAF(x)					\
	.globl	x;					\
	.aent	x,0;					\
x:

/*
 * NON_LEAF(x)
 *
 *	Declare a non-leaf routine (a routine that makes other C calls).
 */
#define NON_LEAF(x, fsize, retpc) \
	.globl x; \
	.ent x, 0; \
x: ; \
D 3
	.frame sp, fsize, retpc
E 3
I 3
D 4
	.frame sp, fsize, retpc \
E 4
I 4
	.frame sp, fsize, retpc; \
E 4
	MCOUNT
E 3

/*
I 5
 * NNON_LEAF(x)
 *
 *	Declare a non-profiled non-leaf routine
 *	(a routine that makes other C calls).
 */
#define NNON_LEAF(x, fsize, retpc) \
	.globl x; \
	.ent x, 0; \
x: ; \
	.frame sp, fsize, retpc

/*
E 5
 * END(x)
 *
 *	Mark end of a procedure.
 */
#define END(x) \
	.end x

#define STAND_FRAME_SIZE	24
#define STAND_RA_OFFSET		20

/*
 * Macros to panic and printf from assembly language.
 */
#define PANIC(msg) \
	la	a0, 9f; \
	jal	panic; \
	MSG(msg)

#define	PRINTF(msg) \
D 2
	la	a0,9f; \
E 2
I 2
	la	a0, 9f; \
E 2
	jal	printf; \
	MSG(msg)

#define	MSG(msg) \
	.rdata; \
9:	.asciiz	msg; \
	.text
I 2

#define ASMSTR(str) \
	.asciiz str; \
	.align	2
E 2

#endif /* _MACHASMDEFS */
E 1
