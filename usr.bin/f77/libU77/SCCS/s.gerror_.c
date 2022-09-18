h55216
s 00008/00005/00036
d D 5.3 91/04/12 15:32:58 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00039
d D 5.2 90/05/28 12:36:18 bostic 3 2
c sys_errlist -> strerror(3)
e
s 00007/00001/00034
d D 5.1 85/06/07 23:17:03 kre 2 1
c Add copyright
e
s 00035/00000/00000
d D 1.1 81/02/18 21:57:45 dlw 1 0
c date and time created 81/02/18 21:57:45 by dlw
e
u
U
t
T
I 1
D 4
/*
D 2
char id_gerror[] = "%W%";
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
E 2
 *
I 2
D 4
 *	%W%	%G%
E 4
I 4
 * %sccs.include.proprietary.c%
E 4
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
E 2
 * Return a standard error message in a character string.
 *
 * calling sequence:
 *	call gerror (string)
 * or
 *	character*20 gerror, string
 *	string = gerror()
 * where:
 *	'string' will receive the standard error message
 */

#include	<stdio.h>
#include	"../libI77/f_errno.h"

D 3
extern char *sys_errlist[];
E 3
extern int sys_nerr;
extern char *f_errlist[];
extern int f_nerr;

gerror_(s, len)
char *s; long len;
{
	char *mesg;
I 3
	char *strerror();
E 3

	if (errno >=0 && errno < sys_nerr)
D 3
		mesg = sys_errlist[errno];
E 3
I 3
		mesg = strerror(errno);
E 3
	else if (errno >= F_ER && errno < (F_ER + f_nerr))
		mesg = f_errlist[errno - F_ER];
	else
		mesg = "unknown error number";
	b_char(mesg, s, len);
}
E 1
