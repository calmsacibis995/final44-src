h38132
s 00002/00002/00021
d D 8.1 93/06/02 19:56:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00009/00013
d D 7.2 91/05/05 18:37:26 bostic 2 1
c new copyright; att/bsd/shared
e
s 00022/00000/00000
d D 7.1 91/05/05 18:36:37 bostic 1 0
c date and time created 91/05/05 18:36:37 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
E 2
 *
D 2
 *	@(#)vadvise.h	7.1 (Berkeley) 6/4/86
E 2
I 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 2
 */

/*
 * Parameters to vadvise() to tell system of particular paging
 * behaviour:
 *	VA_NORM		Normal strategy
 *	VA_ANOM		Sampling page behaviour is not a win, don't bother
 *			Suitable during GCs in LISP, or sequential or random
 *			page referencing.
 *	VA_SEQL		Sequential behaviour expected.
 *	VA_FLUSH	Invalidate all page table entries.
 */
D 2
#define	VA_NORM	0
#define	VA_ANOM	1
#define	VA_SEQL	2
#define	VA_FLUSH 3
E 2
I 2
#define	VA_NORM		0
#define	VA_ANOM		1
#define	VA_SEQL		2
#define	VA_FLUSH 	3
E 2
E 1
