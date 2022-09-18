h62030
s 00008/00005/00009
d D 5.2 91/04/12 14:58:52 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00014
d D 5.1 85/08/09 16:11:46 jerry 2 1
c 
e
s 00014/00000/00000
d D 1.1 85/08/09 16:11:23 jerry 1 0
c date and time created 85/08/09 16:11:23 by jerry
e
u
U
t
T
I 1
D 3
/*
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
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

double d_dprod(x,y)
double *x, *y;
{
/* dprod with -r8 flag - all in double precision */
return( (*x) * (*y) );
}
E 1
