h11191
s 00002/00002/00062
d D 8.1 93/06/11 15:15:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00062
d D 7.3 93/04/20 20:54:47 torek 3 2
c spelling
e
s 00005/00000/00059
d D 7.2 92/07/21 16:54:16 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00059/00000/00000
d D 7.1 92/07/13 00:44:27 torek 1 0
c date and time created 92/07/13 00:44:27 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: asm.h,v 1.4 92/06/17 05:21:52 torek Exp $
E 3
I 3
 * from: $Header: asm.h,v 1.5 92/11/26 03:04:42 torek Exp $
E 3
 */

/*
 * GCC __asm constructs for doing assembly stuff.
 */

/*
 * ``Routines'' to load and store from/to alternate address space.
 * The location can be a variable, the asi value (address space indicator)
 * must be a constant.
 *
 * N.B.: You can put as many special functions here as you like, since
 * they cost no kernel space or time if they are not used.
 *
 * These were static inline functions, but gcc screws up the constraints
 * on the address space identifiers (the "n"umeric value part) because
 * it inlines too late, so we have to use the funny valued-macro syntax.
 */

/* load byte from alternate address space */
#define	lduba(loc, asi) ({ \
	register int _lduba_v; \
	__asm __volatile("lduba [%1]%2,%0" : "=r" (_lduba_v) : \
	    "r" ((int)(loc)), "n" (asi)); \
	_lduba_v; \
})

/* load int from alternate address space */
#define	lda(loc, asi) ({ \
	register int _lda_v; \
	__asm __volatile("lda [%1]%2,%0" : "=r" (_lda_v) : \
	    "r" ((int)(loc)), "n" (asi)); \
	_lda_v; \
})

/* store byte to alternate address space */
#define	stba(loc, asi, value) ({ \
	__asm __volatile("stba %0,[%1]%2" : : \
	    "r" ((int)(value)), "r" ((int)(loc)), "n" (asi)); \
})

/* store int to alternate address space */
#define	sta(loc, asi, value) ({ \
	__asm __volatile("sta %0,[%1]%2" : : \
	    "r" ((int)(value)), "r" ((int)(loc)), "n" (asi)); \
})
E 1
