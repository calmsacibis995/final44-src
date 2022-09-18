h12124
s 00002/00002/00090
d D 8.1 93/06/04 13:07:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00047/00028/00045
d D 5.3 93/05/06 22:44:16 torek 3 2
c split out buffer size and tty determination code for setvbuf
c (add new function __swhatbuf)
e
s 00001/00000/00072
d D 5.2 91/02/24 13:30:13 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00072/00000/00000
d D 5.1 91/01/20 21:34:56 bostic 1 0
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

#include <sys/types.h>
#include <sys/stat.h>
I 2
#include <unistd.h>
E 2
#include <stdio.h>
#include <stdlib.h>
#include "local.h"

/*
 * Allocate a file buffer, or switch to unbuffered I/O.
 * Per the ANSI C standard, ALL tty devices default to line buffered.
 *
 * As a side effect, we set __SOPT or __SNPT (en/dis-able fseek
 * optimisation) right after the fstat() that finds the buffer size.
 */
void
__smakebuf(fp)
	register FILE *fp;
{
D 3
	register size_t size, couldbetty;
E 3
	register void *p;
D 3
	struct stat st;
E 3
I 3
	register int flags;
	size_t size;
	int couldbetty;
E 3

	if (fp->_flags & __SNBF) {
		fp->_bf._base = fp->_p = fp->_nbuf;
		fp->_bf._size = 1;
		return;
	}
D 3
	if (fp->_file < 0 || fstat(fp->_file, &st) < 0) {
		couldbetty = 0;
		size = BUFSIZ;
		/* do not try to optimise fseek() */
		fp->_flags |= __SNPT;
	} else {
		couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
		size = st.st_blksize <= 0 ? BUFSIZ : st.st_blksize;
		/*
		 * Optimise fseek() only if it is a regular file.
		 * (The test for __sseek is mainly paranoia.)
		 */
		if ((st.st_mode & S_IFMT) == S_IFREG &&
		    fp->_seek == __sseek) {
			fp->_flags |= __SOPT;
			fp->_blksize = st.st_blksize;
		} else
			fp->_flags |= __SNPT;
	}
E 3
I 3
	flags = __swhatbuf(fp, &size, &couldbetty);
E 3
	if ((p = malloc(size)) == NULL) {
		fp->_flags |= __SNBF;
		fp->_bf._base = fp->_p = fp->_nbuf;
		fp->_bf._size = 1;
D 3
	} else {
		__cleanup = _cleanup;
		fp->_flags |= __SMBF;
		fp->_bf._base = fp->_p = p;
		fp->_bf._size = size;
		if (couldbetty && isatty(fp->_file))
			fp->_flags |= __SLBF;
E 3
I 3
		return;
E 3
	}
I 3
	__cleanup = _cleanup;
	flags |= __SMBF;
	fp->_bf._base = fp->_p = p;
	fp->_bf._size = size;
	if (couldbetty && isatty(fp->_file))
		flags |= __SLBF;
	fp->_flags |= flags;
}

/*
 * Internal routine to determine `proper' buffering for a file.
 */
int
__swhatbuf(fp, bufsize, couldbetty)
	register FILE *fp;
	size_t *bufsize;
	int *couldbetty;
{
	struct stat st;

	if (fp->_file < 0 || fstat(fp->_file, &st) < 0) {
		*couldbetty = 0;
		*bufsize = BUFSIZ;
		return (__SNPT);
	}

	/* could be a tty iff it is a character device */
	*couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
	if (st.st_blksize <= 0) {
		*bufsize = BUFSIZ;
		return (__SNPT);
	}

	/*
	 * Optimise fseek() only if it is a regular file.  (The test for
	 * __sseek is mainly paranoia.)  It is safe to set _blksize
	 * unconditionally; it will only be used if __SOPT is also set.
	 */
	*bufsize = st.st_blksize;
	fp->_blksize = st.st_blksize;
	return ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == __sseek ?
	    __SOPT : __SNPT);
E 3
}
E 1
