h54086
s 00023/00000/00000
d D 7.1 92/07/16 23:42:44 mckusick 1 0
c date and time created 92/07/16 23:42:44 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_MCOUNT_DECL static inline void _mcount

#define	MCOUNT \
extern void mcount(cntpa) asm("mcount"); void mcount(cntpa) long **cntpa; { \
	int selfpc, frompcindex; \
	/* \
	 * Find the return address for mcount, \
	 * and address of counter pointer. \
	 */ \
	selfpc = *((char **)&cntpa-3);	/* -8(fp) */ \
	frompcindex = \
	    (unsigned short *)(*((((long *)*((char **)&cntpa-1)))-2)); \
	_mcount(frompcindex, selfpc); \
}
E 1
