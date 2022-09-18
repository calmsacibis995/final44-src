h22817
s 00008/00005/00013
d D 5.4 91/04/12 15:00:02 bostic 5 4
c new copyright; att/bsd/shared
e
s 00004/00002/00014
d D 5.3 85/07/09 15:34:06 jerry 4 3
c do store in global to force convert to float despite C bug.
e
s 00001/00001/00015
d D 5.2 85/07/08 14:30:56 jerry 3 2
c declare function as float, not double.
e
s 00005/00001/00011
d D 5.1 85/06/07 22:27:11 kre 2 1
c Add copyright
e
s 00012/00000/00000
d D 1.1 83/01/21 11:18:15 dlw 1 0
c date and time created 83/01/21 11:18:15 by dlw
e
u
U
t
T
I 1
D 5
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
 *
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
E 2
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

I 4
float flt_retval;

E 4
D 3
double r_nint(x)
E 3
I 3
float r_nint(x)
E 3
float *x;
{
double floor();

D 4
return( (*x)>=0 ?
	floor(*x + .5) : -floor(.5 - *x) );
E 4
I 4
flt_retval = (*x)>=0 ? floor(*x + .5) : -floor(.5 - *x);
return(flt_retval);
E 4
}
E 1
