h24634
s 00008/00005/00026
d D 5.2 91/04/12 15:32:53 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00024
d D 5.1 85/06/07 23:14:28 kre 2 1
c Add copyright
e
s 00025/00000/00000
d D 1.1 81/02/10 13:56:24 dlw 1 0
c date and time created 81/02/10 13:56:24 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_fdate[] = "%W%";
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
 * Return date and time in an ASCII string.
 *
 * calling sequence:
 *	character*24 string
 * 	call fdate(string)
 * where:
 *	the 24 character string will be filled with the date & time in
 *	ascii form as described under ctime(3).
 *	No 'newline' or NULL will be included.
 */

fdate_(s, strlen)
char *s; long strlen;
{
	char *ctime(), *c;
	long time(), t;

	t = time(0);
	c = ctime(&t);
	c[24] = '\0';
	b_char(c, s, strlen);
}
E 1
