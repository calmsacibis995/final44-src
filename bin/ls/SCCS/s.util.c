h04007
s 00002/00001/00044
d D 8.5 95/04/28 14:56:59 bostic 18 17
c add the -o option to the usage statement
c From: "Charles M. Hannum" <mycroft@gnu.ai.mit.edu>
e
s 00001/00001/00044
d D 8.4 94/07/28 03:38:18 pendry 17 16
c changes for whiteouts and union filesystem
e
s 00001/00001/00044
d D 8.3 94/04/02 09:56:22 pendry 16 15
c add 1994 copyright
e
s 00004/00004/00041
d D 8.2 94/04/01 02:08:12 pendry 15 14
c prettyness police
e
s 00002/00002/00043
d D 8.1 93/05/31 14:46:05 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00033/00041
d D 5.13 93/04/29 12:39:44 bostic 13 12
c use err/warn(3) from C library
e
s 00002/00013/00072
d D 5.12 92/03/09 14:30:03 bostic 12 11
c emalloc no longer used, -g flag is gone
e
s 00001/00000/00084
d D 5.11 92/03/01 13:22:07 bostic 11 10
c lint
e
s 00008/00026/00076
d D 5.10 92/01/29 16:19:28 elan 10 9
c Added fatal option to error routines.
e
s 00061/00011/00041
d D 5.9 91/10/28 15:45:26 bostic 9 8
c It's a brave new ANSI world!
e
s 00001/00001/00051
d D 5.8 90/07/22 12:56:36 bostic 8 7
c there needs to be a way to get the hour/minute of a file that's more
c than six months old.  And ls(1) needs more options anyway.
e
s 00001/00011/00051
d D 5.7 90/04/08 17:41:50 bostic 7 6
c get redist notice from /usr/share/misc
e
s 00001/00001/00061
d D 5.6 89/09/02 10:44:15 bostic 6 5
c put -f flag back in; it only stops sorting now
e
s 00001/00001/00061
d D 5.5 89/08/22 12:26:46 bostic 5 4
c default sizes are in 512-byte blocks; add -k flag for kilobytes
e
s 00001/00001/00061
d D 5.4 89/08/16 14:46:52 bostic 4 3
c remove -f option, can't use readdir any more, won't work over NFS
e
s 00008/00011/00054
d D 5.3 89/06/25 09:40:53 bostic 3 2
c replace prablelen with prcopy -- bcopy, but rip out unprintables
e
s 00003/00000/00062
d D 5.2 89/06/24 18:57:46 bostic 2 1
c fix copyright notice
e
s 00062/00000/00000
d D 5.1 89/06/24 18:19:58 bostic 1 0
c date and time created 89/06/24 18:19:58 by bostic
e
u
U
t
T
I 1
/*
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 16
 * Copyright (c) 1989, 1993
E 16
I 16
 * Copyright (c) 1989, 1993, 1994
E 16
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
 *
E 2
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
D 9
%sccs.include.redist.c%
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 9
#include <sys/stat.h>
E 9
D 13
#include <stdio.h>
I 9
#include <stdlib.h>
E 13
I 13

E 13
E 9
#include <ctype.h>
I 10
#include <fts.h>
D 13
#include <errno.h>
E 13
I 13
#include <stdio.h>
#include <stdlib.h>
E 13
I 11
#include <string.h>
I 13

E 13
E 11
E 10
I 9
#include "ls.h"
#include "extern.h"
E 9

I 9
void
E 9
D 3
/**
 * prablelen --
 *	act like strlen, but also translate non-printing chars to '?'
 */
prablelen(cp)
	register char *cp;
{
E 3
I 3
prcopy(src, dest, len)
D 15
	register char *src, *dest;
E 3
	register int len;
E 15
I 15
	char *src, *dest;
	int len;
E 15
I 3
{
D 15
	register int ch;
E 15
I 15
	int ch;
E 15
E 3

D 3
	for (len = 0; *cp; ++len, ++cp)
		if (!isprint(*cp))
			*cp = '?';
	return(len);
E 3
I 3
D 15
	while(len--) {
E 15
I 15
	while (len--) {
E 15
		ch = *src++;
		*dest++ = isprint(ch) ? ch : '?';
	}
E 3
}

D 9
char
*emalloc(size)
E 9
I 9
D 12
void *
emalloc(size)
E 9
	u_int size;
{
D 9
	char *retval, *malloc();
E 9
I 9
	void *retval;
E 9

D 9
	if (!(retval = malloc(size)))
		nomem();
	return(retval);
E 9
I 9
	if ((retval = malloc(size)) == NULL)
D 10
		err("%s", strerror(errno));
E 10
I 10
		err(1, "%s", strerror(errno));
E 10
	return (retval);
E 9
}

E 12
D 9
nomem()
E 9
I 9
void
usage()
E 9
{
D 9
	(void)fprintf(stderr, "ls: out of memory.\n");
E 9
I 9
D 12
	(void)fprintf(stderr, "usage: ls [-1ACFLRTacdfgiklqrstu] [file ...]\n");
E 12
I 12
D 17
	(void)fprintf(stderr, "usage: ls [-1ACFLRTacdfiklqrstu] [file ...]\n");
E 17
I 17
D 18
	(void)fprintf(stderr, "usage: ls [-1ACFLRTWacdfiklqrstu] [file ...]\n");
E 18
I 18
	(void)fprintf(stderr,
	    "usage: ls [-1ACFLRTWacdfikloqrstu] [file ...]\n");
E 18
E 17
E 12
E 9
	exit(1);
D 13
}

D 9
usage()
E 9
I 9
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
D 10
err(const char *fmt, ...)
E 10
I 10
err(int fatal, const char *fmt, ...)
E 10
#else
D 10
err(fmt, va_alist)
E 10
I 10
err(fatal, fmt, va_alist)
	int fatal;
E 10
	char *fmt;
D 12
        va_dcl
E 12
I 12
	va_dcl
E 12
#endif
E 9
{
D 4
	(void)fprintf(stderr, "usage: ls [-1ACFLRacdfgilqrstu] [file ...]\n");
E 4
I 4
D 5
	(void)fprintf(stderr, "usage: ls [-1ACFLRacdgilqrstu] [file ...]\n");
E 5
I 5
D 6
	(void)fprintf(stderr, "usage: ls [-1ACFLRacdgiklqrstu] [file ...]\n");
E 6
I 6
D 8
	(void)fprintf(stderr, "usage: ls [-1ACFLRacdfgiklqrstu] [file ...]\n");
E 8
I 8
D 9
	(void)fprintf(stderr, "usage: ls [-1ACFLRTacdfgiklqrstu] [file ...]\n");
E 9
I 9
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "ls: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 9
E 8
E 6
E 5
E 4
D 10
	exit(1);
I 9
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
	(void)fprintf(stderr, "ls: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 10
I 10
	if (fatal)
		exit(1);
E 13
E 10
E 9
}
E 1
