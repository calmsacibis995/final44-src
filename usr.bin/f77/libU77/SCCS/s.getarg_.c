h25744
s 00008/00005/00032
d D 5.2 91/04/12 15:32:59 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00030
d D 5.1 85/06/07 23:17:27 kre 2 1
c Add copyright
e
s 00031/00000/00000
d D 1.1 81/02/18 22:03:16 dlw 1 0
c date and time created 81/02/18 22:03:16 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_getarg[] = "%W%";
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
 * return a specified command line argument
 *
 * calling sequence:
 *	character*20 arg
 *	call getarg(k, arg)
 * where:
 *	arg will receive the kth unix command argument
*/

getarg_(n, s, ls)
long int *n;
register char *s;
long int ls;
{
extern int xargc;
extern char **xargv;
register char *t;
register int i;

if(*n>=0 && *n<xargc)
	t = xargv[*n];
else
	t = "";
for(i = 0; i<ls && *t!='\0' ; ++i)
	*s++ = *t++;
for( ; i<ls ; ++i)
	*s++ = ' ';
}
E 1
