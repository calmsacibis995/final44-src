h40023
s 00002/00002/00071
d D 8.1 93/06/08 11:21:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00003/00058
d D 5.3 91/04/20 15:35:01 bostic 3 2
c new copyright; att/bsd/shared
e
s 00006/00010/00055
d D 5.2 91/02/28 18:56:47 bostic 2 1
c get rid of the "portability" sugar
e
s 00065/00000/00000
d D 5.1 90/02/02 17:24:08 bostic 1 0
c date and time created 90/02/02 17:24:08 by bostic
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Arthur David Olson of the National Cancer Institute.
 *
 * %sccs.include.redist.c%
 */

E 3
I 1
#ifndef lint
D 3
#ifndef NOID
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef notdef
E 3
static char	elsieid[] = "@(#)scheck.c	8.9";
D 3
#endif /* !defined lint */
#endif /* !defined NOID */
E 3
I 3
#endif
E 3

/*LINTLIBRARY*/

D 2
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "nonstd.h"
E 2
I 2
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
E 2

D 2
extern char *	imalloc P((int n));
extern void	ifree P((char * p));

E 2
char *
scheck(string, format)
const char * const	string;
const char * const	format;
{
	register char *		fbuf;
	register const char *	fp;
	register char *		tp;
	register int		c;
	register char *		result;
	char			dummy;

	result = "";
	if (string == NULL || format == NULL)
		return result;
D 2
	fbuf = imalloc(2 * strlen(format) + 4);
E 2
I 2
	fbuf = malloc(2 * strlen(format) + 4);
E 2
	if (fbuf == NULL)
		return result;
	fp = format;
	tp = fbuf;
	while ((*tp++ = c = *fp++) != '\0') {
		if (c != '%')
			continue;
		if (*fp == '%') {
			*tp++ = *fp++;
			continue;
		}
		*tp++ = '*';
		if (*fp == '*')
			++fp;
		while (isascii(*fp) && isdigit(*fp))
			*tp++ = *fp++;
		if (*fp == 'l' || *fp == 'h')
			*tp++ = *fp++;
		else if (*fp == '[')
			do *tp++ = *fp++;
				while (*fp != '\0' && *fp != ']');
		if ((*tp++ = *fp++) == '\0')
			break;
	}
	*(tp - 1) = '%';
	*tp++ = 'c';
	*tp = '\0';
D 2
	if (sscanf(string, fbuf, &dummy) != 1)
E 2
I 2
	if (sscanf((char *)string, fbuf, &dummy) != 1)
E 2
		result = (char *) format;
	ifree(fbuf);
	return result;
}
E 1
