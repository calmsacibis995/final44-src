h65356
s 00003/00003/00047
d D 8.2 93/10/05 09:20:35 bostic 7 6
c use #ifdef __STDC__, it's more correct, and, #if doesn't work on Suns
e
s 00002/00002/00048
d D 8.1 93/06/04 16:47:27 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00048
d D 5.5 93/05/16 15:54:53 bostic 5 4
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00000/00001/00050
d D 5.4 92/11/10 12:28:57 elan 4 3
c Undid debugging.
e
s 00001/00000/00050
d D 5.3 92/10/01 15:05:31 elan 3 2
c quit
e
s 00000/00000/00050
d D 5.2 92/09/14 11:00:45 elan 2 1
c Converted to new data structures.
e
s 00050/00000/00000
d D 5.1 92/08/23 14:43:04 bostic 1 0
c date and time created 92/08/23 14:43:04 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 3
D 4
#define DEBUG
E 4
E 3
#ifdef DEBUG
#include <stdio.h>

D 7
#if __STDC__
E 7
I 7
#ifdef __STDC__
E 7
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#ifndef TFILE
#define	TFILE	"__curses.out"
#endif

static FILE *tracefp;			/* Curses debugging file descriptor. */

void
D 7
#if __STDC__
E 7
I 7
#ifdef __STDC__
E 7
D 5
__TRACE(const char *fmt, ...)
E 5
I 5
__CTRACE(const char *fmt, ...)
E 5
#else
D 5
__TRACE(fmt, va_alist)
E 5
I 5
__CTRACE(fmt, va_alist)
E 5
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
D 7
#if __STDC__
E 7
I 7
#ifdef __STDC__
E 7
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	if (tracefp == NULL)
		tracefp = fopen(TFILE, "w");
	if (tracefp == NULL)
		return;
	(void)vfprintf(tracefp, fmt, ap);
	va_end(ap);
	(void)fflush(tracefp);
}
#endif
E 1
