h63747
s 00002/00002/00038
d D 8.1 93/06/10 21:45:26 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00037
d D 7.6 92/06/05 15:29:24 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00003/00000/00035
d D 7.5 91/05/09 18:27:07 karels 5 4
c add T_USER
e
s 00001/00001/00034
d D 7.4 91/05/08 14:22:15 karels 4 3
c update comment
e
s 00001/00001/00034
d D 7.3 90/11/03 13:01:34 mckusick 3 2
c update identifier from Utah
e
s 00001/00001/00034
d D 7.2 90/06/22 09:32:23 hibler 2 1
c T_AST -> T_ASTFLT to be more consisent with VAX
e
s 00035/00000/00000
d D 7.1 90/05/08 17:51:22 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 7
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: trap.h 1.6 88/11/25$
E 3
I 3
D 6
 * from: Utah $Hdr: trap.h 1.1 90/07/09$
E 6
I 6
 * from: Utah $Hdr: trap.h 1.7 91/03/25$
E 6
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
D 4
 * Trap type values
E 4
I 4
 * Trap codes
E 4
 */

#define	T_BUSERR	0
#define	T_ADDRERR	1
#define	T_ILLINST	2
#define	T_ZERODIV	3
#define	T_CHKINST	4
#define	T_TRAPVINST	5
#define	T_PRIVINST	6
#define	T_TRACE		7
#define	T_MMUFLT	8
#define	T_SSIR		9
#define	T_FMTERR	10
#define T_FPERR		11
#define T_COPERR	12
D 2
#define T_AST		13
E 2
I 2
#define T_ASTFLT	13
E 2
#define T_TRAP15	15
I 6
#define T_FPEMULI	16
#define T_FPEMULD	17
E 6
I 5

#define	T_USER		0x80		/* user-mode flag or'ed with type */

E 5
E 1
