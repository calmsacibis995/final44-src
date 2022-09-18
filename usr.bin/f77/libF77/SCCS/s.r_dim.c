h18437
s 00008/00005/00011
d D 5.4 91/04/12 14:59:56 bostic 5 4
c new copyright; att/bsd/shared
e
s 00004/00001/00012
d D 5.3 85/07/09 15:34:00 jerry 4 3
c do store in global to force convert to float despite C bug.
e
s 00001/00001/00012
d D 5.2 85/07/08 14:31:09 jerry 3 2
c declare function as float, not double.
e
s 00005/00001/00008
d D 5.1 85/06/07 22:24:32 kre 2 1
c Add copyright
e
s 00009/00000/00000
d D 1.1 83/01/21 11:17:36 dlw 1 0
c date and time created 83/01/21 11:17:36 by dlw
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
double r_dim(a,b)
E 3
I 3
float r_dim(a,b)
E 3
float *a, *b;
{
D 4
return( *a > *b ? *a - *b : 0);
E 4
I 4
flt_retval =  *a > *b ? *a - *b : 0;
return(flt_retval);
E 4
}
E 1
