h29810
s 00002/00002/00055
d D 8.1 93/06/05 11:07:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00057/00000/00000
d D 5.1 91/09/19 10:18:49 bostic 1 0
c date and time created 91/09/19 10:18:49 by bostic
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
#include <sys/types.h>
#include <sys/disklabel.h>
#include <stdlib.h>
#include <stdio.h>
#include "extern.h"

u_int
log2(num)
        u_int num;
{
        register u_int i, limit;

        limit = 1;
        for (i = 0; limit < num; limit = limit << 1, i++);
        return (i);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
fatal(const char *fmt, ...)
#else
fatal(fmt, va_alist)
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
	(void)fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
}
E 1
