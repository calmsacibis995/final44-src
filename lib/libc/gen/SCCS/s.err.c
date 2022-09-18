h59132
s 00002/00002/00158
d D 8.1 93/06/04 12:01:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00160
d D 5.3 93/05/06 00:58:02 bostic 3 2
c typo
e
s 00014/00006/00148
d D 5.2 93/03/19 12:07:07 bostic 2 1
c add support for fmt == NULL, so can display "prog: errno_msg"
e
s 00154/00000/00000
d D 5.1 93/03/04 15:03:14 bostic 1 0
c date and time created 93/03/04 15:03:14 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

extern char *__progname;		/* Program name, from crt0. */

__dead void
#ifdef __STDC__
err(int eval, const char *fmt, ...)
#else
err(eval, fmt, va_alist)
	int eval;
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	verr(eval, fmt, ap);
	va_end(ap);
}

__dead void
verr(eval, fmt, ap)
	int eval;
	const char *fmt;
	va_list ap;
{
	int sverrno;

	sverrno = errno;
	(void)fprintf(stderr, "%s: ", __progname);
D 2
	(void)vfprintf(stderr, fmt, ap);
	(void)fprintf(stderr, ": %s\n", strerror(sverrno));
E 2
I 2
	if (fmt != NULL) {
		(void)vfprintf(stderr, fmt, ap);
		(void)fprintf(stderr, ": ");
	}
	(void)fprintf(stderr, "%s\n", strerror(sverrno));
E 2
	exit(eval);
}

__dead void
#if __STDC__
errx(int eval, const char *fmt, ...)
#else
errx(eval, fmt, va_alist)
	int eval;
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	verrx(eval, fmt, ap);
	va_end(ap);
}

__dead void
verrx(eval, fmt, ap)
	int eval;
	const char *fmt;
	va_list ap;
{
	(void)fprintf(stderr, "%s: ", __progname);
D 2
	(void)vfprintf(stderr, fmt, ap);
E 2
I 2
	if (fmt != NULL)
		(void)vfprintf(stderr, fmt, ap);
E 2
	(void)fprintf(stderr, "\n");
	exit(eval);
}

void
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
D 3
	int eval;
E 3
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vwarn(fmt, ap);
	va_end(ap);
}

void
vwarn(fmt, ap)
	const char *fmt;
	va_list ap;
{
	int sverrno;

	sverrno = errno;
	(void)fprintf(stderr, "%s: ", __progname);
D 2
	(void)vfprintf(stderr, fmt, ap);
	(void)fprintf(stderr, ": %s\n", strerror(sverrno));
E 2
I 2
	if (fmt != NULL) {
		(void)vfprintf(stderr, fmt, ap);
		(void)fprintf(stderr, ": ");
	}
	(void)fprintf(stderr, "%s\n", strerror(sverrno));
E 2
}

void
#ifdef __STDC__
warnx(const char *fmt, ...)
#else
warnx(fmt, va_alist)
D 3
	int eval;
E 3
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
#ifdef __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vwarnx(fmt, ap);
	va_end(ap);
}

void
vwarnx(fmt, ap)
	const char *fmt;
	va_list ap;
{
	(void)fprintf(stderr, "%s: ", __progname);
D 2
	(void)vfprintf(stderr, fmt, ap);
E 2
I 2
	if (fmt != NULL)
		(void)vfprintf(stderr, fmt, ap);
E 2
	(void)fprintf(stderr, "\n");
}
E 1
