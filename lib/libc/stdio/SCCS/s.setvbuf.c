h33848
s 00023/00011/00111
d D 8.2 93/11/16 20:04:32 torek 9 7
c well, looks like we have to get all the fields right after all --
c otherwise problems occur for __SWR mode files.  I suppose we could
c have lots more flags, but this should be OK.
e
s 00023/00011/00111
d R 8.2 93/11/16 20:03:22 torek 8 7
c well, looks like we have to get all the fields right after all --
c otherwise problems occur for __SWR mode files.  I suppose we could
e
s 00002/00002/00120
d D 8.1 93/06/04 13:09:36 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00010/00113
d D 5.6 93/05/22 14:12:45 torek 6 5
c trying to get all the fields right is too much trouble: just reset
c to a minimal state and let __srefill or __swsetup do the dirty work
e
s 00069/00053/00054
d D 5.5 93/05/06 22:48:01 torek 5 4
c rewrite: always allocate buffer immediately; always honor user
c mode flags; set fseek optimization iff new buffer is proper size
e
s 00037/00016/00070
d D 5.4 92/12/04 05:34:53 torek 4 3
c do early allocation for nonzero size with NULL buffer; cleanup; prettiness
e
s 00002/00000/00084
d D 5.3 92/08/13 09:50:34 bostic 3 2
c look at size iff buff != NULL; fix from Chris Torek
e
s 00001/00001/00083
d D 5.2 91/02/01 19:31:12 bostic 2 1
c fflush -> __sflush
e
s 00084/00000/00000
d D 5.1 91/01/20 21:34:59 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
#include <stdlib.h>
#include "local.h"

/*
 * Set one of the three kinds of buffering, optionally including
 * a buffer.
 */
setvbuf(fp, buf, mode, size)
	register FILE *fp;
	char *buf;
	register int mode;
	register size_t size;
{
I 3
D 4
	if (buf == NULL)
		size = 0;
E 4
I 4
	register int ret, flags;
I 5
	size_t iosize;
	int ttyflag;
E 5
E 4
E 3

	/*
	 * Verify arguments.  The `int' limit on `size' is due to this
D 5
	 * particular implementation.
E 5
I 5
	 * particular implementation.  Note, buf and size are ignored
	 * when setting _IONBF.
E 5
	 */
D 5
	if ((mode != _IOFBF && mode != _IOLBF && mode != _IONBF) ||
	    (int)size < 0)
		return (EOF);
E 5
I 5
	if (mode != _IONBF)
		if ((mode != _IOFBF && mode != _IOLBF) || (int)size < 0)
			return (EOF);
E 5

	/*
D 4
	 * Write current buffer, if any; drop read count, if any.
	 * Make sure putc() will not think fp is line buffered.
	 * Free old buffer if it was from malloc().  Clear line and
	 * non buffer flags, and clear malloc flag.
E 4
I 4
D 5
	 * OK so far.  Write current buffer, if any; drop read count, if
	 * any.  Make sure putc() will not think fp is line buffered.  Free
	 * old buffer if it was from malloc().  Clear line and non-buffer
	 * flags, and clear malloc flag.
E 5
I 5
D 9
	 * Write current buffer, if any.  Discard unread input, cancel
	 * line buffering, and free old buffer if malloc()ed.
E 9
I 9
	 * Write current buffer, if any.  Discard unread input (including
	 * ungetc data), cancel line buffering, and free old buffer if
	 * malloc()ed.  We also clear any eof condition, as if this were
	 * a seek.
E 9
E 5
E 4
	 */
I 4
	ret = 0;
E 4
D 2
	(void) fflush(fp);
E 2
I 2
D 5
	(void) __sflush(fp);
E 2
	fp->_r = 0;
	fp->_lbfsize = 0;
E 5
I 5
	(void)__sflush(fp);
I 9
	if (HASUB(fp))
		FREEUB(fp);
E 9
	fp->_r = fp->_lbfsize = 0;
E 5
D 4
	if (fp->_flags & __SMBF)
E 4
I 4
	flags = fp->_flags;
	if (flags & __SMBF)
E 4
		free((void *)fp->_bf._base);
D 4
	fp->_flags &= ~(__SLBF|__SNBF|__SMBF);
E 4
I 4
D 5
	flags &= ~(__SLBF | __SNBF | __SMBF);
E 5
I 5
D 9
	flags &= ~(__SLBF | __SNBF | __SMBF | __SOPT | __SNPT);
E 9
I 9
	flags &= ~(__SLBF | __SNBF | __SMBF | __SOPT | __SNPT | __SEOF);
E 9
E 5
E 4

I 4
D 5
	if (size == 0)
		buf = NULL;	/* we will make a real one later */
	else if (buf == NULL) {
		/*
		 * Caller wants specific buffering mode and size but did
		 * not provide a buffer.  Produce one of the given size.
		 * If that fails, set the size to 0 and continue, so that
		 * we will try again later with a system-supplied size
		 * (failure here is probably from someone with the bogus
		 * idea that larger is always better, asking for many MB),
		 * but return EOF to indicate failure.
		 */
E 5
I 5
	/* If setting unbuffered mode, skip all the hard work. */
	if (mode == _IONBF)
		goto nbf;

	/*
	 * Find optimal I/O size for seek optimization.  This also returns
	 * a `tty flag' to suggest that we check isatty(fd), but we do not
	 * care since our caller told us how to buffer.
	 */
	flags |= __swhatbuf(fp, &iosize, &ttyflag);
	if (size == 0) {
		buf = NULL;	/* force local allocation */
		size = iosize;
	}

	/* Allocate buffer if needed. */
	if (buf == NULL) {
E 5
		if ((buf = malloc(size)) == NULL) {
I 5
			/*
			 * Unable to honor user's request.  We will return
			 * failure, but try again with file system size.
			 */
E 5
			ret = EOF;
D 5
			size = 0;
		} else
			flags |= __SMBF;
E 5
I 5
			if (size != iosize) {
				size = iosize;
				buf = malloc(size);
			}
		}
		if (buf == NULL) {
			/* No luck; switch to unbuffered I/O. */
nbf:
			fp->_flags = flags | __SNBF;
			fp->_w = 0;
			fp->_bf._base = fp->_p = fp->_nbuf;
			fp->_bf._size = 1;
			return (ret);
		}
		flags |= __SMBF;
E 5
	}

E 4
	/*
D 4
	 * Now put back whichever flag is needed, and fix _lbfsize
	 * if line buffered.  Ensure output flush on exit if the
	 * stream will be buffered at all.
E 4
I 4
D 5
	 * Now put back whichever flag is needed, and fix _lbfsize if line
	 * buffered.  Ensure output flush on exit if the stream will be
	 * buffered at all.
E 5
I 5
	 * Kill any seek optimization if the buffer is not the
	 * right size.
	 *
	 * SHOULD WE ALLOW MULTIPLES HERE (i.e., ok iff (size % iosize) == 0)?
E 5
E 4
	 */
D 5
	switch (mode) {
E 5
I 5
	if (size != iosize)
		flags |= __SNPT;
E 5

D 5
	case _IONBF:
D 4
		fp->_flags |= __SNBF;
E 4
I 4
		flags |= __SNBF;
E 4
		fp->_bf._base = fp->_p = fp->_nbuf;
		fp->_bf._size = 1;
		break;

	case _IOLBF:
D 4
		fp->_flags |= __SLBF;
E 4
I 4
		flags |= __SLBF;
E 4
		fp->_lbfsize = -size;
		/* FALLTHROUGH */

	case _IOFBF:
		/* no flag */
		__cleanup = _cleanup;
		fp->_bf._base = fp->_p = (unsigned char *)buf;
		fp->_bf._size = size;
		break;
	}

E 5
	/*
D 5
	 * Patch up write count if necessary.
E 5
I 5
	 * Fix up the FILE fields, and set __cleanup for output flush on
D 6
	 * exit (since we are buffered in some way).  Note that _w can
	 * always be set to 0 safely here---it should be 0 in read mode
	 * or the `indeterminate' state, and 0 for line buffered---so
	 * using the new buffer size for fully-buffered streams in write
	 * mode is merely a tiny optimization.
E 6
I 6
D 9
	 * exit (since we are buffered in some way).  If in r/w mode, go
	 * to the intermediate state, so that everyone has to call
	 * __srefill or __swsetup on the first operation -- it is more
	 * trouble than it is worth to set things up correctly here.
E 9
I 9
	 * exit (since we are buffered in some way).
E 9
E 6
E 5
	 */
D 4
	if (fp->_flags & __SWR)
		fp->_w = fp->_flags & (__SLBF|__SNBF) ? 0 : size;
E 4
I 4
D 5
	if (flags & __SWR)
		fp->_w = flags & (__SLBF | __SNBF) ? 0 : size;
E 5
I 5
D 6
	if (mode == _IOLBF) {
E 6
I 6
	if (mode == _IOLBF)
E 6
		flags |= __SLBF;
D 6
		fp->_lbfsize = -size;
		fp->_w = 0;
	} else
		fp->_w = flags & __SWR ? size : 0;
E 6
I 6
D 9
	if (flags & __SRW)
		flags &= ~(__SRD | __SWR);
	fp->_w = 0;
E 9
E 6
E 5
	fp->_flags = flags;
I 5
	fp->_bf._base = fp->_p = (unsigned char *)buf;
	fp->_bf._size = size;
I 6
D 9
	fp->_lbfsize = 0;
E 9
I 9
	/* fp->_lbfsize is still 0 */
	if (flags & __SWR) {
		/*
		 * Begin or continue writing: see __swsetup().  Note
		 * that __SNBF is impossible (it was handled earlier).
		 */
		if (flags & __SLBF) {
			fp->_w = 0;
			fp->_lbfsize = -fp->_bf._size;
		} else
			fp->_w = size;
	} else {
		/* begin/continue reading, or stay in intermediate state */
		fp->_w = 0;
	}
E 9
E 6
	__cleanup = _cleanup;
E 5
E 4

D 4
	return (0);
E 4
I 4
	return (ret);
E 4
}
E 1
