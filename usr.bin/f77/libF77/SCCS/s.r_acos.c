h03331
s 00008/00005/00009
d D 5.3 91/04/12 14:59:50 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00013
d D 5.2 85/07/08 14:30:02 jerry 3 2
c declare function as float, not double.
e
s 00005/00001/00009
d D 5.1 85/06/07 22:20:33 kre 2 1
c Add copyright
e
s 00010/00000/00000
d D 1.1 83/01/21 11:17:04 dlw 1 0
c date and time created 83/01/21 11:17:04 by dlw
e
u
U
t
T
I 1
D 4
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
 *
D 4
 *	%W%	%G%
E 4
I 4
 * %sccs.include.proprietary.c%
E 4
E 2
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

D 3
double r_acos(x)
E 3
I 3
float r_acos(x)
E 3
float *x;
{
double acos();
return( acos(*x) );
}
E 1
