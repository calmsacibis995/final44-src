h00159
s 00001/00000/00121
d D 8.2 93/11/03 23:58:36 torek 13 12
c ungetc clears EOF condition
e
s 00002/00002/00119
d D 8.1 93/06/04 13:10:08 bostic 12 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00007/00114
d R 5.8 93/05/21 14:53:09 torek 11 10
c always call __sflush, in case somehow fp->_p > fp->_bf._base in __SRW
e
s 00002/00001/00119
d D 5.7 93/03/04 15:36:39 torek 10 9
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00001/00001/00119
d D 5.6 91/05/04 16:40:50 bostic 9 8
c the C library should only use bcopy, so programs don't load both!
e
s 00001/00001/00119
d D 5.5 91/02/01 19:31:40 bostic 8 7
c fflush -> __sflush
e
s 00107/00011/00013
d D 5.4 91/01/20 21:32:06 bostic 7 6
c new stdio
e
s 00004/00001/00020
d D 5.3 86/03/26 18:08:36 bloom 6 5
c avoid possible problem from too many calls to ungetc
e
s 00002/00002/00019
d D 5.2 86/03/09 20:54:42 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00018
d D 5.1 85/06/05 13:44:40 mckusick 4 3
c Add copyright
e
s 00008/00007/00011
d D 4.3 85/02/13 15:49:01 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00008/00007/00010
d D 4.2 83/09/25 12:58:05 sam 2 1
c make return values correspond to man page; from lepreau@utah-cs
e
s 00017/00000/00000
d D 4.1 80/12/21 16:51:04 wnj 1 0
c date and time created 80/12/21 16:51:04 by wnj
e
u
U
t
T
I 7
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 7
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 5
E 4

E 2
#include <stdio.h>
I 7
#include <stdlib.h>
#include <string.h>
#include "local.h"
E 7

D 7
ungetc(c, iop)
D 2
register FILE *iop;
E 2
I 2
	register FILE *iop;
E 7
I 7
/*
 * Expand the ungetc buffer `in place'.  That is, adjust fp->_p when
 * the buffer moves, so that it points the same distance from the end,
 * and move the bytes in the buffer around as necessary so that they
 * are all at the end (stack-style).
 */
static
__submore(fp)
	register FILE *fp;
E 7
E 2
{
D 3
	if (c == EOF)
D 2
		return(-1);
	if ((iop->_flag&_IOREAD)==0 || iop->_ptr <= iop->_base)
		if (iop->_ptr == iop->_base && iop->_cnt==0)
E 2
I 2
		return (-1);
	if ((iop->_flag&_IOREAD) == 0 || iop->_ptr <= iop->_base)
		if (iop->_ptr == iop->_base && iop->_cnt == 0)
E 2
			*iop->_ptr++;
		else
D 2
			return(-1);
E 2
I 2
			return (EOF);
E 3
I 3
D 7
	if (c == EOF || (iop->_flag & (_IOREAD|_IORW)) == 0 ||
	    iop->_ptr == NULL || iop->_base == NULL)
E 7
I 7
	register int i;
	register unsigned char *p;

	if (fp->_ub._base == fp->_ubuf) {
		/*
		 * Get a new buffer (rather than expanding the old one).
		 */
		if ((p = malloc((size_t)BUFSIZ)) == NULL)
			return (EOF);
		fp->_ub._base = p;
		fp->_ub._size = BUFSIZ;
		p += BUFSIZ - sizeof(fp->_ubuf);
		for (i = sizeof(fp->_ubuf); --i >= 0;)
			p[i] = fp->_ubuf[i];
		fp->_p = p;
		return (0);
	}
	i = fp->_ub._size;
	p = realloc(fp->_ub._base, i << 1);
	if (p == NULL)
E 7
		return (EOF);
I 7
D 9
	(void) memcpy((void *)(p + i), (void *)p, (size_t)i);
E 9
I 9
D 10
	(void) bcopy((void *)p, (void *)(p + i), (size_t)i);
E 10
I 10
	/* no overlap (hence can use memcpy) because we doubled the size */
	(void)memcpy((void *)(p + i), (void *)p, (size_t)i);
E 10
E 9
	fp->_p = p + i;
	fp->_ub._base = p;
	fp->_ub._size = i << 1;
	return (0);
}
E 7

D 7
	if (iop->_ptr == iop->_base)
D 6
		iop->_ptr++;
E 6
I 6
		if (iop->_cnt == 0)
			iop->_ptr++;
		else
E 7
I 7
ungetc(c, fp)
	int c;
	register FILE *fp;
{
	if (c == EOF)
		return (EOF);
	if (!__sdidinit)
		__sinit();
	if ((fp->_flags & __SRD) == 0) {
		/*
		 * Not already reading: no good unless reading-and-writing.
		 * Otherwise, flush any current write stuff.
		 */
		if ((fp->_flags & __SRW) == 0)
E 7
			return (EOF);
I 7
		if (fp->_flags & __SWR) {
D 8
			if (fflush(fp))
E 8
I 8
			if (__sflush(fp))
E 8
				return (EOF);
			fp->_flags &= ~__SWR;
			fp->_w = 0;
			fp->_lbfsize = 0;
		}
		fp->_flags |= __SRD;
	}
	c = (unsigned char)c;
E 7
E 6

E 3
E 2
D 7
	iop->_cnt++;
	*--iop->_ptr = c;
E 7
I 7
	/*
	 * If we are in the middle of ungetc'ing, just continue.
	 * This may require expanding the current ungetc buffer.
	 */
	if (HASUB(fp)) {
		if (fp->_r >= fp->_ub._size && __submore(fp))
			return (EOF);
		*--fp->_p = c;
		fp->_r++;
		return (c);
	}
I 13
	fp->_flags &= ~__SEOF;
E 13
E 7
I 3

I 7
	/*
	 * If we can handle this by simply backing up, do so,
	 * but never replace the original character.
	 * (This makes sscanf() work when scanning `const' data.)
	 */
	if (fp->_bf._base != NULL && fp->_p > fp->_bf._base &&
	    fp->_p[-1] == c) {
		fp->_p--;
		fp->_r++;
		return (c);
	}

	/*
	 * Create an ungetc buffer.
	 * Initially, we will use the `reserve' buffer.
	 */
	fp->_ur = fp->_r;
	fp->_up = fp->_p;
	fp->_ub._base = fp->_ubuf;
	fp->_ub._size = sizeof(fp->_ubuf);
	fp->_ubuf[sizeof(fp->_ubuf) - 1] = c;
	fp->_p = &fp->_ubuf[sizeof(fp->_ubuf) - 1];
	fp->_r = 1;
E 7
E 3
D 2
	return(0);
E 2
I 2
	return (c);
E 2
}
E 1
