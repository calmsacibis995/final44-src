h23328
s 00001/00000/00026
d R 8.3 94/03/21 06:17:49 bostic 5 4
c used by factor(6), too, add NEG_BIG (NEG_SEMIBIG) back in
e
s 00006/00010/00020
d D 8.2 94/03/01 06:25:24 bostic 4 3
c primes did not support numbers in the 2^31 - 2^32 range; redefine
c the upper limit, and change the %ld's to %lu's appears to fix it.
c From: Arne Juul <arnej@dsl.unit.no>
e
s 00002/00002/00028
d D 8.1 93/05/31 17:43:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00029
d D 5.2 90/06/01 13:13:47 bostic 2 1
c new copyright notice
e
s 00040/00000/00000
d D 5.1 90/02/01 10:21:45 bostic 1 0
c new version from Landon Curt Noll.
c date and time created 90/02/01 10:21:45 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Landon Curt Noll.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * primes - generate a table of primes between two values
 *
D 4
 * By: Landon Curt Noll   chongo@toad.com,   ...!{sun,tolsoft}!hoptoad!chongo
E 4
I 4
 * By: Landon Curt Noll chongo@toad.com, ...!{sun,tolsoft}!hoptoad!chongo
E 4
 *
D 4
 *   chongo <for a good prime call: 391581 * 2^216193 - 1> /\oo/\
E 4
I 4
 * chongo <for a good prime call: 391581 * 2^216193 - 1> /\oo/\
E 4
 */

/* ubig is the type that holds a large unsigned value */
D 4
typedef unsigned long ubig;           /* must be >=32 bit unsigned value */
E 4
I 4
typedef unsigned long ubig;		/* must be >=32 bit unsigned value */
#define	BIG		ULONG_MAX	/* largest value will sieve */
E 4

D 4
/*
 * sieve parameters
 */
#define BIG ((ubig)0xffffffff)        /* highest value we will sieve */
#define SEMIBIG ((ubig)0x7fffffff)    /* highest signed value */
#define NEG_SEMIBIG ((ubig)0x80000000) /* lowest signed value */
#define TABSIZE 256*1024 /* bytes in sieve table (must be > 3*5*7*11) */
E 4
I 4
/* bytes in sieve table (must be > 3*5*7*11) */
#define	TABSIZE		256*1024
E 4
E 1
