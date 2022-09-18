h30896
s 00002/00002/00048
d D 8.1 93/06/09 21:45:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00043
d D 1.4 91/04/17 17:38:36 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00048
d D 1.3 85/06/07 18:26:31 bloom 3 2
c fix sccsid and copyright for xstr
e
s 00009/00002/00040
d D 1.2 85/05/31 15:21:22 dist 2 1
c Add copyright
e
s 00042/00000/00000
d D 1.1 80/08/26 16:14:43 root 1 0
c date and time created 80/08/26 16:14:43 by root
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1979 Regents of the University of California */
static char *sccsid = "%W% %G%";
E 2
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 4
static char *sccsid = "%W% (Berkeley) %G%";
E 3
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

/*
 * This version of printf calls doprnt, and as such is not portable,
 * since doprnt is written in pdp-11 assembly language.  (There is a
 * vax doprnt which has the first 2 arguments reversed.  We don't use it.)
 * This version is used because it is about 900 bytes smaller than the
 * portable version, which is also included in case it is needed.
 */
#ifdef TRACE
#include	<stdio.h>
#undef putchar
#endif

printf(fmt, args)
char *fmt;
{
	_doprnt(fmt, &args, 0);
}

_strout(string, count, adjust, file, fillch)
register char *string;
register count;
int adjust;
register struct _iobuf *file;
{
	while (adjust < 0) {
		if (*string=='-' && fillch=='0') {
			putchar(*string++);
			count--;
		}
		putchar(fillch);
		adjust++;
	}
	while (--count>=0)
		putchar(*string++);
	while (adjust) {
		putchar(fillch);
		adjust--;
	}
}
E 1
