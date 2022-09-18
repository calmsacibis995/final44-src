h56927
s 00001/00001/00037
d D 8.3 94/04/02 10:02:40 pendry 6 5
c add 1994 copyright
e
s 00000/00000/00038
d D 8.2 94/04/01 03:39:16 pendry 5 4
c prettyness police
e
s 00002/00002/00036
d D 8.1 93/05/31 15:48:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00051/00034
d D 5.3 93/04/29 15:18:58 bostic 3 2
c use C library err/warn routines
e
s 00000/00002/00085
d D 5.2 91/06/04 17:42:47 bostic 2 1
c stty.h includes ioctl.h and termios.h; extern.h defines mode/char arrays
e
s 00087/00000/00000
d D 5.1 91/05/02 13:34:52 bostic 1 0
c date and time created 91/05/02 13:34:52 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 1991, 1993
E 6
I 6
 * Copyright (c) 1991, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
D 2
#include <sys/ioctl.h>
#include <termios.h>
E 2
D 3
#include <unistd.h>
E 3
I 3

#include <err.h>
E 3
#include <stdio.h>
#include <stdlib.h>
I 3
#include <unistd.h>

E 3
#include "stty.h"
#include "extern.h"

/*
 * Gross, but since we're changing the control descriptor from 1 to 0, most
 * users will be probably be doing "stty > /dev/sometty" by accident.  If 1
 * and 2 are both ttys, but not the same, assume that 1 was incorrectly
 * redirected.
 */
void
checkredirect()
{
	struct stat sb1, sb2;

	if (isatty(STDOUT_FILENO) && isatty(STDERR_FILENO) &&
	    !fstat(STDOUT_FILENO, &sb1) && !fstat(STDERR_FILENO, &sb2) &&
	    (sb1.st_rdev != sb2.st_rdev))
warn("stdout appears redirected, but stdin is the control descriptor");
D 3
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
	(void)fprintf(stderr, "stty: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
}

void
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
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
	(void)fprintf(stderr, "stty: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 3
}
E 1
