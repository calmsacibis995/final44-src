h21980
s 00002/00002/00031
d D 8.1 93/06/10 21:45:04 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00000/00000
d D 7.1 92/07/14 00:54:36 mckusick 1 0
c date and time created 92/07/14 00:54:36 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_MCOUNT_DECL static inline void _mcount

#define	MCOUNT \
extern void mcount() asm("mcount"); void mcount() { \
	int selfpc, frompcindex; \
	asm("movl a6@(4),%0" : "=r" (selfpc)); \
	asm("movl a6@(0)@(4),%0" : "=r" (frompcindex)); \
	_mcount(frompcindex, selfpc); \
}

#ifdef KERNEL
/*
 * The following two macros do splhigh and splx respectively.
 * They have to be defined this way because these are real
 * functions on the HP, and we do not want to invoke mcount
 * recursively.
 */
#define MCOUNT_ENTER \
	asm("movw	sr,%0" : "=g" (s)); \
	asm("movw	#0x2700,sr")

#define MCOUNT_EXIT \
	asm("movw	%0,sr" : : "g" (s))
#endif /* KERNEL */
E 1
