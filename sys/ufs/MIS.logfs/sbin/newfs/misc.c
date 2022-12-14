/*
 * CLFS
 * $Log: misc.c,v $
 * Revision 1.2  1994/11/29  16:34:42  margo
 * Remove checksum debug message
 *
 * Revision 1.1  1994/11/22  15:51:08  margo
 * Initial revision
 *
 */

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
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
 */

#ifndef lint
static char sccsid[] = "@(#)misc.c	8.1 (Berkeley) 6/5/93";
#endif /* not lint */

#include <sys/types.h>
#include <sys/disklabel.h>
#include <errno.h>
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

void
put(fd, off, p, len)
	int fd;
	off_t off;
	void *p;
	size_t len;
{
	int wbytes;

	if (lseek(fd, off, SEEK_SET) < 0)
		fatal("%s: %s", special, strerror(errno));
	if ((wbytes = write(fd, p, len)) < 0)
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != len)
		fatal("%s: short write (%d, not %d)", special, wbytes, len);
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

/*
 * Simple, general purpose, fast checksum.  Data must be short-aligned.
 * Returns a u_long in case we ever want to do something more rigorous.
 *
 * XXX
 * Use the TCP/IP checksum instead.
 */
u_long
cksum(str, len)
	register u_short *str;
	register size_t len;
{
	register u_long sum;
	
	len &= ~(sizeof(u_short) - 1);
	for (sum = 0; len; len -= sizeof(u_short)) {
		sum ^= *str;
		++str;
	}
	return (sum);
}
