h45444
s 00002/00002/00031
d D 8.1 93/06/06 15:18:15 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00024
d D 1.5 90/04/09 18:27:13 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00012/00003/00014
d D 1.4 83/01/10 18:14:32 mckusick 4 3
c get rid of RAND.s and use floating point instead
e
s 00002/00000/00015
d D 1.3 81/03/07 15:59:49 mckusic 3 2
c merge in onyx changes
e
s 00004/00001/00011
d D 1.2 81/01/16 16:36:03 mckusic 2 1
c Rewrite the random number generator
e
s 00012/00000/00000
d D 1.1 80/10/30 00:34:32 mckusick 1 0
c date and time created 80/10/30 00:34:32 by mckusick
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
/*-
D 6
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */
E 5

D 5
static char sccsid[] = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

I 2
#include "h00vars.h"

I 3
extern long RAND();

E 3
E 2
double
RANDOM()
{
I 4
	double d;
	long l;

E 4
	/*
D 4
	 * div by maxint to get 0..1
E 4
I 4
	 * calculate (1103515245 * seed) mod 2^31-1
E 4
	 */
D 2
	return (rand() / 2.147483647e+09);
E 2
I 2
D 4
	_seed = RAND(_seed);
	return((double)_seed / 0x7fffffff);
E 4
I 4
	d = 1103515245.0 * _seed / 2147483647.0;
	l = d;
	d = d - l;
	_seed = d * 2147483647.0;
	/*
	 * want a value in the range 0..1
	 */
	return(d);
E 4
E 2
}
E 1
