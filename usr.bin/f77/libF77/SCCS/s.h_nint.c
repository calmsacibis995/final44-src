h62056
s 00008/00005/00011
d D 5.2 91/04/12 14:59:21 bostic 3 2
c new copyright; att/bsd/shared
e
s 00005/00001/00011
d D 5.1 85/06/07 21:57:38 kre 2 1
c Add copyright
e
s 00012/00000/00000
d D 1.1 83/01/21 11:13:43 dlw 1 0
c date and time created 83/01/21 11:13:43 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
 *
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
E 2
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

short h_nint(x)
float *x;
{
double floor();

return( (*x)>=0 ?
	floor(*x + .5) : -floor(.5 - *x) );
}
E 1