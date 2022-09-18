h10493
s 00002/00002/00161
d D 8.1 93/06/04 13:07:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00162
d D 5.4 93/03/04 15:36:34 torek 4 3
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00001/00001/00162
d D 5.3 91/05/04 16:40:49 bostic 3 2
c the C library should only use bcopy, so programs don't load both!
e
s 00004/00001/00159
d D 5.2 91/02/05 00:29:00 torek 2 1
c keep gcc happy
e
s 00160/00000/00000
d D 5.1 91/01/20 21:34:52 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <string.h>
#include "local.h"
#include "fvwrite.h"

/*
 * Write some memory regions.  Return zero on success, EOF on error.
 *
 * This routine is large and unsightly, but most of the ugliness due
 * to the three different kinds of output buffering is handled here.
 */
__sfvwrite(fp, uio)
	register FILE *fp;
	register struct __suio *uio;
{
	register size_t len;
	register char *p;
	register struct __siov *iov;
	register int w, s;
	char *nl;
	int nlknown, nldist;

	if ((len = uio->uio_resid) == 0)
		return (0);
	/* make sure we can write */
	if (cantwrite(fp))
		return (EOF);

#define	MIN(a, b) ((a) < (b) ? (a) : (b))
D 3
#define	COPY(n)	  (void) memcpy((void *)fp->_p, (void *)p, (size_t)(n));
E 3
I 3
D 4
#define	COPY(n)	  (void) bcopy((void *)p, (void *)fp->_p, (size_t)(n));
E 4
I 4
#define	COPY(n)	  (void)memcpy((void *)fp->_p, (void *)p, (size_t)(n))
E 4
E 3

	iov = uio->uio_iov;
D 2
	len = 0;
E 2
I 2
	p = iov->iov_base;
	len = iov->iov_len;
	iov++;
E 2
#define GETIOV(extra_work) \
	while (len == 0) { \
		extra_work; \
		p = iov->iov_base; \
		len = iov->iov_len; \
		iov++; \
	}
	if (fp->_flags & __SNBF) {
		/*
		 * Unbuffered: write up to BUFSIZ bytes at a time.
		 */
		do {
			GETIOV(;);
			w = (*fp->_write)(fp->_cookie, p, MIN(len, BUFSIZ));
			if (w <= 0)
				goto err;
			p += w;
			len -= w;
		} while ((uio->uio_resid -= w) != 0);
	} else if ((fp->_flags & __SLBF) == 0) {
		/*
		 * Fully buffered: fill partially full buffer, if any,
		 * and then flush.  If there is no partial buffer, write
		 * one _bf._size byte chunk directly (without copying).
		 *
		 * String output is a special case: write as many bytes
		 * as fit, but pretend we wrote everything.  This makes
		 * snprintf() return the number of bytes needed, rather
		 * than the number used, and avoids its write function
		 * (so that the write function can be invalid).
		 */
		do {
			GETIOV(;);
			w = fp->_w;
			if (fp->_flags & __SSTR) {
				if (len < w)
					w = len;
				COPY(w);	/* copy MIN(fp->_w,len), */
				fp->_w -= w;
				fp->_p += w;
				w = len;	/* but pretend copied all */
			} else if (fp->_p > fp->_bf._base && len > w) {
				/* fill and flush */
				COPY(w);
				/* fp->_w -= w; */ /* unneeded */
				fp->_p += w;
				if (fflush(fp))
					goto err;
			} else if (len >= (w = fp->_bf._size)) {
				/* write directly */
				w = (*fp->_write)(fp->_cookie, p, w);
				if (w <= 0)
					goto err;
			} else {
				/* fill and done */
				w = len;
				COPY(w);
				fp->_w -= w;
				fp->_p += w;
			}
			p += w;
			len -= w;
		} while ((uio->uio_resid -= w) != 0);
	} else {
		/*
		 * Line buffered: like fully buffered, but we
		 * must check for newlines.  Compute the distance
		 * to the first newline (including the newline),
		 * or `infinity' if there is none, then pretend
		 * that the amount to write is MIN(len,nldist).
		 */
		nlknown = 0;
I 2
		nldist = 0;	/* XXX just to keep gcc happy */
E 2
		do {
			GETIOV(nlknown = 0);
			if (!nlknown) {
				nl = memchr((void *)p, '\n', len);
				nldist = nl ? nl + 1 - p : len + 1;
				nlknown = 1;
			}
			s = MIN(len, nldist);
			w = fp->_w + fp->_bf._size;
			if (fp->_p > fp->_bf._base && s > w) {
				COPY(w);
				/* fp->_w -= w; */
				fp->_p += w;
				if (fflush(fp))
					goto err;
			} else if (s >= (w = fp->_bf._size)) {
				w = (*fp->_write)(fp->_cookie, p, w);
				if (w <= 0)
				 	goto err;
			} else {
				w = s;
				COPY(w);
				fp->_w -= w;
				fp->_p += w;
			}
			if ((nldist -= w) == 0) {
				/* copied the newline: flush and forget */
				if (fflush(fp))
					goto err;
				nlknown = 0;
			}
			p += w;
			len -= w;
		} while ((uio->uio_resid -= w) != 0);
	}
	return (0);

err:
	fp->_flags |= __SERR;
	return (EOF);
}
E 1
