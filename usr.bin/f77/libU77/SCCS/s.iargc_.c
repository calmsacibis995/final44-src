h11036
s 00008/00005/00018
d D 5.2 91/04/12 15:33:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00016
d D 5.1 85/06/07 23:21:28 kre 2 1
c Add copyright
e
s 00017/00000/00000
d D 1.1 81/02/18 22:02:54 dlw 1 0
c date and time created 81/02/18 22:02:54 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_iargc[] = "%W%";
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
E 2
 *
I 2
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

/*
E 2
 * return the number of args on the command line following the command name
 *
 * calling sequence:
 *	nargs = iargc()
 * where:
 *	nargs will be set to the number of args
 */

extern int xargc;

long iargc_()
{
	return ((long)(xargc - 1));
}
E 1
