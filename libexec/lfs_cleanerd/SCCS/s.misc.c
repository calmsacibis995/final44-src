h06080
s 00002/00002/00066
d D 8.1 93/06/04 18:55:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00065
d D 5.2 93/06/04 17:34:52 cgd 4 3
c have error function only print errno if it's nonzero
e
s 00006/00030/00060
d D 5.1 92/08/06 12:38:26 bostic 3 2
c integrate into the source tree, yank to 5.1, minor lint
e
s 00024/00024/00066
d D 1.2 92/08/06 12:28:15 bostic 2 1
c Stolen from newlfs; should be shared code.
e
s 00090/00000/00000
d D 1.1 92/07/21 15:23:22 bostic 1 0
c date and time created 92/07/21 15:23:22 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
E 3
I 3
D 5
 * Copyright (c) 1992 The Regents of the University of California.
E 3
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 3
static char sccsid[] = "@(#)misc.c	5.1 (Berkeley) 9/19/91";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
#endif /* not lint */

#include <sys/types.h>
I 3

E 3
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
I 3

E 3
D 2
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
		err("%s: %s", special, strerror(errno));
	if ((rbytes = read(fd, p, len)) < 0)
		err("%s: %s", special, strerror(errno));
	if (rbytes != len)
		err("%s: short read (%d, not %d)", special, rbytes, len);
}

E 2
I 2
extern char *special;
I 3

E 3
E 2
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
err(const int fatal, const char *fmt, ...)
E 2
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
D 2
	(void)fprintf(stderr, "dumplfs: ");
E 2
I 2
	(void)fprintf(stderr, "%s: ", special);
E 2
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
D 2
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 2
I 2
D 4
	(void)fprintf(stderr, " %s\n", strerror(errno));
E 4
I 4
	if (errno)
		(void)fprintf(stderr, " %s", strerror(errno));
	(void)fprintf(stderr, "\n");
E 4
	if (fatal)
		exit(1);
E 2
}
I 2

void
get(fd, off, p, len)
	int fd;
	off_t off;
	void *p;
	size_t len;
{
	int rbytes;

	if (lseek(fd, off, SEEK_SET) < 0)
		err(1, "%s: %s", special, strerror(errno));
	if ((rbytes = read(fd, p, len)) < 0)
		err(1, "%s: %s", special, strerror(errno));
	if (rbytes != len)
		err(1, "%s: short read (%d, not %d)", special, rbytes, len);
}
D 3

E 3
E 2
E 1
