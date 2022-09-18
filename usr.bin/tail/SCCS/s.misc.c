h62086
s 00002/00002/00063
d D 8.1 93/06/06 16:30:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00057
d D 5.2 92/03/03 16:13:31 bostic 2 1
c make tail work like head for multiple files
e
s 00063/00000/00000
d D 5.1 91/07/21 14:50:09 bostic 1 0
c date and time created 91/07/21 14:50:09 by bostic
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
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Edward Sze-Tyan Wang.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void
ierr()
{
D 2
	err("%s: %s", fname, strerror(errno));
E 2
I 2
	err(0, "%s: %s", fname, strerror(errno));
E 2
}

void
oerr()
{
D 2
	err("stdout: %s", strerror(errno));
E 2
I 2
	err(1, "stdout: %s", strerror(errno));
E 2
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
D 2
err(const char *fmt, ...)
E 2
I 2
err(int fatal, const char *fmt, ...)
E 2
#else
D 2
err(fmt, va_alist)
E 2
I 2
err(fatal, fmt, va_alist)
	int fatal;
E 2
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
	(void)fprintf(stderr, "tail: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
D 2
	exit(1);
	/* NOTREACHED */
E 2
I 2
	if (fatal)
		exit(1);
	rval = 1;
E 2
}
E 1
