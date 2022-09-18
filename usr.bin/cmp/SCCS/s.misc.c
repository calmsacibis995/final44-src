h03383
s 00001/00001/00037
d D 8.3 94/04/02 10:07:01 pendry 5 4
c add 1994 copyright
e
s 00006/00032/00032
d D 8.2 94/04/01 07:42:21 pendry 4 3
c prettyness police
e
s 00002/00002/00062
d D 8.1 93/06/06 14:28:00 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00063
d D 5.2 92/06/21 13:35:17 bostic 2 1
c off_t is a quad, use %qd; 2nd arg to mmap is an int
e
s 00064/00000/00000
d D 5.1 91/10/27 14:14:47 bostic 1 0
c date and time created 91/10/27 14:14:47 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
D 5
 * Copyright (c) 1991, 1993
E 5
I 5
 * Copyright (c) 1991, 1993, 1994
E 5
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 4

#include <err.h>
E 4
#include <stdio.h>
#include <stdlib.h>
I 4

E 4
#include "extern.h"

void
eofmsg(file)
	char *file;
{
	if (!sflag)
D 4
		(void)fprintf(stderr, "cmp: EOF on %s\n", file);
	exit(1);
E 4
I 4
		warnx("EOF on %s", file);
	exit(DIFF_EXIT);
E 4
}

void
diffmsg(file1, file2, byte, line)
	char *file1, *file2;
	off_t byte, line;
{
	if (!sflag)
D 2
		(void)printf("%s %s differ: char %ld, line %ld\n",
E 2
I 2
		(void)printf("%s %s differ: char %qd, line %qd\n",
E 2
		    file1, file2, byte, line);
D 4
	exit(1);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "cmp: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(2);
	/* NOTREACHED */
E 4
I 4
	exit(DIFF_EXIT);
E 4
}
E 1
