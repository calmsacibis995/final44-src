h31618
s 00002/00002/00076
d D 8.1 93/06/04 13:09:51 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00076
d D 5.3 91/02/24 13:30:22 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00078
d D 5.2 91/02/01 19:31:29 bostic 2 1
c stdc.h -> cdefs.h
e
s 00079/00000/00000
d D 5.1 91/01/20 21:35:00 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
D 3
#include <sys/cdefs.h>
E 2
#include <sys/types.h>
#include <sys/file.h>
E 3
I 3
#include <fcntl.h>
#include <unistd.h>
E 3
D 2
#include <sys/stdc.h>
E 2
#include <stdio.h>
#include "local.h"

/*
 * Small standard I/O/seek/close functions.
 * These maintain the `known seek offset' for seek optimisation.
 */
__sread(cookie, buf, n)
	void *cookie;
	char *buf;
	int n;
{
	register FILE *fp = cookie;
	register int ret;
	
	ret = read(fp->_file, buf, n);
	/* if the read succeeded, update the current offset */
	if (ret >= 0)
		fp->_offset += ret;
	else
		fp->_flags &= ~__SOFF;	/* paranoia */
	return (ret);
}

__swrite(cookie, buf, n)
	void *cookie;
	char const *buf;
	int n;
{
	register FILE *fp = cookie;

	if (fp->_flags & __SAPP)
		(void) lseek(fp->_file, (off_t)0, SEEK_END);
	fp->_flags &= ~__SOFF;	/* in case FAPPEND mode is set */
	return (write(fp->_file, buf, n));
}

fpos_t
__sseek(cookie, offset, whence)
	void *cookie;
	fpos_t offset;
	int whence;
{
	register FILE *fp = cookie;
	register off_t ret;
	
	ret = lseek(fp->_file, (off_t)offset, whence);
	if (ret == -1L)
		fp->_flags &= ~__SOFF;
	else {
		fp->_flags |= __SOFF;
		fp->_offset = ret;
	}
	return (ret);
}

__sclose(cookie)
	void *cookie;
{

	return (close(((FILE *)cookie)->_file));
}
E 1
