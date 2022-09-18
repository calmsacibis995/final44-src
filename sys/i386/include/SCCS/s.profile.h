h31241
s 00002/00002/00028
d D 8.1 93/06/11 15:48:19 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00029
d D 7.2 93/05/25 00:12:03 torek 2 1
c lint
e
s 00030/00000/00000
d D 7.1 92/07/16 23:43:38 mckusick 1 0
c date and time created 92/07/16 23:43:38 by mckusick
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_MCOUNT_DECL static inline void _mcount

#define	MCOUNT \
extern void mcount() asm("mcount"); void mcount() { \
	int selfpc, frompcindex; \
	/* \
	 * find the return address for mcount, \
	 * and the return address for mcount's caller. \
	 * \
	 * selfpc = pc pushed by mcount call \
	 */ \
	asm("movl 4(%%ebp),%0" : "=r" (selfpc)); \
	/* \
	 * frompcindex = pc pushed by jsr into self. \
	 * In GCC the caller's stack frame has already been built so we \
	 * have to chase a6 to find caller's raddr. \
	 */ \
	asm("movl (%%ebp),%0" : "=r" (frompcindex)); \
D 2
	frompcindex = ((unsigned short **)frompcindex)[1]; \
E 2
I 2
	frompcindex = ((int *)frompcindex)[1]; \
E 2
	_mcount(frompcindex, selfpc); \
}
E 1
