h04818
s 00002/00002/00100
d D 8.1 93/06/04 13:08:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00101
d D 5.3 91/02/24 13:30:19 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00099
d D 5.2 91/02/01 19:30:59 bostic 2 1
c fflush -> __sflush
e
s 00101/00000/00000
d D 5.1 91/01/20 21:34:57 bostic 1 0
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

#include <errno.h>
#include <stdio.h>
I 3
#include <stdlib.h>
E 3
#include "local.h"

static
lflush(fp)
	FILE *fp;
{

	if ((fp->_flags & (__SLBF|__SWR)) == __SLBF|__SWR)
D 2
		return (fflush(fp));
E 2
I 2
		return (__sflush(fp));
E 2
	return (0);
}

/*
 * Refill a stdio buffer.
 * Return EOF on eof or error, 0 otherwise.
 */
__srefill(fp)
	register FILE *fp;
{

	/* make sure stdio is set up */
	if (!__sdidinit)
		__sinit();

	fp->_r = 0;		/* largely a convenience for callers */

	/* SysV does not make this test; take it out for compatibility */
	if (fp->_flags & __SEOF)
		return (EOF);

	/* if not already reading, have to be reading and writing */
	if ((fp->_flags & __SRD) == 0) {
		if ((fp->_flags & __SRW) == 0) {
			errno = EBADF;
			return (EOF);
		}
		/* switch to reading */
		if (fp->_flags & __SWR) {
D 2
			if (fflush(fp))
E 2
I 2
			if (__sflush(fp))
E 2
				return (EOF);
			fp->_flags &= ~__SWR;
			fp->_w = 0;
			fp->_lbfsize = 0;
		}
		fp->_flags |= __SRD;
	} else {
		/*
		 * We were reading.  If there is an ungetc buffer,
		 * we must have been reading from that.  Drop it,
		 * restoring the previous buffer (if any).  If there
		 * is anything in that buffer, return.
		 */
		if (HASUB(fp)) {
			FREEUB(fp);
			if ((fp->_r = fp->_ur) != 0) {
				fp->_p = fp->_up;
				return (0);
			}
		}
	}

	if (fp->_bf._base == NULL)
		__smakebuf(fp);

	/*
	 * Before reading from a line buffered or unbuffered file,
	 * flush all line buffered output files, per the ANSI C
	 * standard.
	 */
	if (fp->_flags & (__SLBF|__SNBF))
		(void) _fwalk(lflush);
	fp->_p = fp->_bf._base;
	fp->_r = (*fp->_read)(fp->_cookie, (char *)fp->_p, fp->_bf._size);
	fp->_flags &= ~__SMOD;	/* buffer contents are again pristine */
	if (fp->_r <= 0) {
		if (fp->_r == 0)
			fp->_flags |= __SEOF;
		else {
			fp->_r = 0;
			fp->_flags |= __SERR;
		}
		return (EOF);
	}
	return (0);
}
E 1
