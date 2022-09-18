h57999
s 00002/00002/00113
d D 8.1 93/06/06 16:16:19 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00014/00115
d D 5.5 93/05/18 14:46:19 elan 6 5
c Strnchr() -> memchr().
e
s 00014/00000/00115
d D 5.4 93/04/14 06:22:36 elan 5 4
c make sed work on 8-bit objects
c TK checking in for Elan Amir
e
s 00001/00001/00114
d D 5.3 92/08/26 15:28:39 bostic 4 3
c put the line number first
e
s 00003/00009/00112
d D 5.2 92/08/24 18:42:18 bostic 3 1
c we can't survive some of the compile errors, just die
e
s 00001/00009/00112
d R 5.2 92/08/24 18:38:24 bostic 2 1
c always die, we can't survive some of the compile errors
e
s 00121/00000/00000
d D 5.1 92/08/23 18:26:10 bostic 1 0
c date and time created 92/08/23 18:26:10 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "extern.h"

/*
 * malloc with result test
 */
void *
xmalloc(size)
	u_int size;
{
	void *p;

	if ((p = malloc(size)) == NULL)
		err(FATAL, "%s", strerror(errno));
	return (p);
}

/*
 * realloc with result test
 */
void *
xrealloc(p, size)
	void *p;
	u_int size;
{
	if (p == NULL)			/* Compatibility hack. */
		return (xmalloc(size));

	if ((p = realloc(p, size)) == NULL)
		err(FATAL, "%s", strerror(errno));
	return (p);
}

I 5
D 6
char *
strnchr(buf, c, len)
	const char *buf;
	int c;
	size_t len;
{
	const char *cp;
       
	for (cp = buf; cp - buf < len; cp++)
		if (*cp == c)
			return ((char *)cp);
	return (NULL);
}

E 6
E 5
/*
 * Return a string for a regular expression error passed.  This is a overkill,
 * because of the silly semantics of regerror (we can never know the size of
 * the buffer).
 */
char *
strregerror(errcode, preg)
	int errcode;
	regex_t *preg;
{
	static char *oe;
	size_t s;

	if (oe != NULL)
		free(oe);
	s = regerror(errcode, preg, "", 0);
	oe = xmalloc(s);
	(void)regerror(errcode, preg, oe, s);
	return (oe);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
/*
 * Error reporting function
 */
void
#if __STDC__
err(int severity, const char *fmt, ...)
#else
err(severity, fmt, va_alist)
	int severity;
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
	(void)fprintf(stderr, "sed: ");
	switch (severity) {
	case WARNING:
	case COMPILE:
D 4
		(void)fprintf(stderr, "%s(%lu): ", fname, linenum);
E 4
I 4
		(void)fprintf(stderr, "%lu: %s: ", linenum, fname);
E 4
	}
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
D 3
	switch (severity) {
	case COMPILE:
		compile_errors++;
#define	MAX_COMPILE_ERRS	20
		if (compile_errors > MAX_COMPILE_ERRS)
			err(FATAL, "too many compilation errors; exiting");
	case FATAL:
		exit(1);
	}
E 3
I 3
	if (severity == WARNING)
		return;
	exit(1);
E 3
	/* NOTREACHED */
}
E 1
