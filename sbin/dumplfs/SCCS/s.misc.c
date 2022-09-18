h02915
s 00007/00034/00030
d D 8.2 95/04/28 10:19:58 bostic 3 2
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00062
d D 8.1 93/06/05 10:54:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00000/00000
d D 5.1 91/09/19 10:16:34 bostic 1 0
c date and time created 91/09/19 10:16:34 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 3
#include <unistd.h>
E 3
I 3

#include <err.h>
E 3
#include <errno.h>
D 3
#include <stdlib.h>
E 3
#include <stdio.h>
I 3
#include <stdlib.h>
E 3
#include <string.h>
I 3
#include <unistd.h>
E 3
#include "extern.h"

void
get(fd, off, p, len)
	int fd;
	off_t off;
	void *p;
	size_t len;
{
	int rbytes;

	if (lseek(fd, off, SEEK_SET) < 0)
D 3
		err("%s: %s", special, strerror(errno));
E 3
I 3
		err(1, "%s", special);
E 3
	if ((rbytes = read(fd, p, len)) < 0)
D 3
		err("%s: %s", special, strerror(errno));
E 3
I 3
		err(1, "%s", special);
E 3
	if (rbytes != len)
D 3
		err("%s: short read (%d, not %d)", special, rbytes, len);
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
	(void)fprintf(stderr, "dumplfs: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 3
I 3
		errx(1, "%s: short read (%d, not %d)", special, rbytes, len);
E 3
}
E 1
