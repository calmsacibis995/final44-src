h48152
s 00002/00002/00132
d D 8.2 94/01/02 14:06:42 bostic 6 5
c rename fgetline.{3,c} -> fgetln.{3,c}
e
s 00002/00002/00132
d D 8.1 93/06/04 13:04:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00132
d D 5.4 93/03/04 15:36:38 torek 4 3
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00034/00035/00100
d D 5.3 93/03/03 15:28:56 torek 3 2
c interface change: size parameter is required, keep newline;
c no longer returns a C string (callers must use care)
e
s 00002/00002/00133
d D 5.2 91/05/04 16:40:44 bostic 2 1
c the C library should only use bcopy, so programs don't load both!
e
s 00135/00000/00000
d D 5.1 91/01/20 21:34:46 bostic 1 0
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
#include <stdlib.h>
#include <string.h>
#include "local.h"

/*
 * Expand the line buffer.  Return -1 on error.
I 3
#ifdef notdef
E 3
 * The `new size' does not account for a terminating '\0',
 * so we add 1 here.
I 3
#endif
E 3
 */
__slbexpand(fp, newsize)
	FILE *fp;
	size_t newsize;
{
	void *p;

D 3
	if (fp->_lb._size >= ++newsize)
E 3
I 3
#ifdef notdef
	++newsize;
#endif
	if (fp->_lb._size >= newsize)
E 3
		return (0);
	if ((p = realloc(fp->_lb._base, newsize)) == NULL)
		return (-1);
	fp->_lb._base = p;
	fp->_lb._size = newsize;
	return (0);
}

/*
 * Get an input line.  The returned pointer often (but not always)
D 3
 * points into a stdio buffer.  Fgetline smashes the newline (if any)
 * in the stdio buffer; callers must not use it on streams that
 * have `magic' setvbuf() games happening.
E 3
I 3
D 6
 * points into a stdio buffer.  Fgetline does not alter the text of
E 6
I 6
 * points into a stdio buffer.  Fgetln does not alter the text of
E 6
 * the returned line (which is thus not a C string because it will
 * not necessarily end with '\0'), but does allow callers to modify
 * it if they wish.  Thus, we set __SMOD in case the caller does.
E 3
 */
char *
D 6
fgetline(fp, lenp)
E 6
I 6
fgetln(fp, lenp)
E 6
	register FILE *fp;
	size_t *lenp;
{
	register unsigned char *p;
	register size_t len;
	size_t off;

	/* make sure there is input */
	if (fp->_r <= 0 && __srefill(fp)) {
D 3
		if (lenp != NULL)
			*lenp = 0;
E 3
I 3
		*lenp = 0;
E 3
		return (NULL);
	}

	/* look for a newline in the input */
	if ((p = memchr((void *)fp->_p, '\n', fp->_r)) != NULL) {
		register char *ret;

		/*
D 3
		 * Found one.  Flag buffer as modified to keep
		 * fseek from `optimising' a backward seek, since
		 * the newline is about to be trashed.  (We should
		 * be able to get away with doing this only if
		 * p is not pointing into an ungetc buffer, since
		 * fseek discards ungetc data, but this is the
		 * usual case anyway.)
E 3
I 3
		 * Found one.  Flag buffer as modified to keep fseek from
		 * `optimising' a backward seek, in case the user stomps on
		 * the text.
E 3
		 */
I 3
		p++;		/* advance over it */
E 3
		ret = (char *)fp->_p;
D 3
		len = p - fp->_p;
E 3
I 3
		*lenp = len = p - fp->_p;
E 3
		fp->_flags |= __SMOD;
D 3
		*p = 0;
		fp->_r -= len + 1;
		fp->_p = p + 1;
		if (lenp != NULL)
			*lenp = len;
E 3
I 3
		fp->_r -= len;
		fp->_p = p;
E 3
		return (ret);
	}

	/*
	 * We have to copy the current buffered data to the line buffer.
I 3
	 * As a bonus, though, we can leave off the __SMOD.
E 3
	 *
D 3
	 * OPTIMISTIC is length that we (optimistically)
	 * expect will accomodate the `rest' of the string,
	 * on each trip through the loop below.
E 3
I 3
	 * OPTIMISTIC is length that we (optimistically) expect will
	 * accomodate the `rest' of the string, on each trip through the
	 * loop below.
E 3
	 */
#define OPTIMISTIC 80

	for (len = fp->_r, off = 0;; len += fp->_r) {
		register size_t diff;

		/*
D 3
		 * Make sure there is room for more bytes.
		 * Copy data from file buffer to line buffer,
		 * refill file and look for newline.  The
		 * loop stops only when we find a newline.
E 3
I 3
		 * Make sure there is room for more bytes.  Copy data from
		 * file buffer to line buffer, refill file and look for
		 * newline.  The loop stops only when we find a newline.
E 3
		 */
		if (__slbexpand(fp, len + OPTIMISTIC))
			goto error;
D 2
		(void) memcpy((void *)(fp->_lb._base + off), (void *)fp->_p,
E 2
I 2
D 3
		(void) bcopy((void *)fp->_p, (void *)(fp->_lb._base + off),
E 3
I 3
D 4
		(void)bcopy((void *)fp->_p, (void *)(fp->_lb._base + off),
E 4
I 4
		(void)memcpy((void *)(fp->_lb._base + off), (void *)fp->_p,
E 4
E 3
E 2
		    len - off);
		off = len;
		if (__srefill(fp))
			break;	/* EOF or error: return partial line */
		if ((p = memchr((void *)fp->_p, '\n', fp->_r)) == NULL)
			continue;

		/* got it: finish up the line (like code above) */
D 3
		fp->_flags |= __SMOD;	/* soon */
E 3
I 3
		p++;
E 3
		diff = p - fp->_p;
		len += diff;
		if (__slbexpand(fp, len))
			goto error;
D 2
		(void) memcpy((void *)(fp->_lb._base + off), (void *)fp->_p,
E 2
I 2
D 3
		(void) bcopy((void *)fp->_p, (void *)(fp->_lb._base + off),
E 3
I 3
D 4
		(void)bcopy((void *)fp->_p, (void *)(fp->_lb._base + off),
E 4
I 4
		(void)memcpy((void *)(fp->_lb._base + off), (void *)fp->_p,
E 4
E 3
E 2
		    diff);
D 3
		fp->_r -= diff + 1;
		fp->_p = p + 1;
E 3
I 3
		fp->_r -= diff;
		fp->_p = p;
E 3
		break;
	}
D 3
	if (lenp != NULL)
		*lenp = len;
E 3
I 3
	*lenp = len;
#ifdef notdef
E 3
	fp->_lb._base[len] = 0;
I 3
#endif
E 3
	return ((char *)fp->_lb._base);

error:
D 3
	if (lenp != NULL)
		*lenp = 0;	/* ??? */
E 3
I 3
	*lenp = 0;		/* ??? */
E 3
	return (NULL);		/* ??? */
}
E 1
