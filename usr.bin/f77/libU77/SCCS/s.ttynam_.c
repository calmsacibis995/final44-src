h38253
s 00008/00005/00030
d D 5.2 91/04/12 15:33:26 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00028
d D 5.1 85/06/07 23:30:49 kre 2 1
c Add copyright
e
s 00029/00000/00000
d D 1.1 81/08/11 23:39:51 dlw 1 0
c date and time created 81/08/11 23:39:51 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_ttynam[] = "%W%";
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
 * Return name of tty port associated with lunit
 *
 * calling sequence:
 *	character*19 string, ttynam
 * 	string = ttynam (lunit)
 * where:
 *	the character string will be filled with the name of
 *	the port, preceded with '/dev/', and blank padded.
 *	(19 is the max length ever required)
 */

#include "../libI77/fiodefs.h"

extern unit units[];

ttynam_(name, strlen, lu)
char *name; long strlen; long *lu;
{
	char *t = NULL, *ttyname();

	if (0 <= *lu && *lu < MXUNIT && units[*lu].ufd)
		t = ttyname(fileno(units[*lu].ufd));
	if (t == NULL)
		t = "";
	b_char(t, name, strlen);
}
E 1
