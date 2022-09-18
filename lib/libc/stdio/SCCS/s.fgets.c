h58449
s 00004/00003/00074
d D 8.2 93/12/22 06:49:32 torek 9 8
c fgets with count 1 should read no bytes successfully
e
s 00002/00002/00075
d D 8.1 93/06/04 13:05:04 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00075
d D 5.5 93/03/04 15:36:35 torek 7 6
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00002/00002/00075
d D 5.4 91/05/04 16:40:47 bostic 6 5
c the C library should only use bcopy, so programs don't load both!
e
s 00069/00017/00008
d D 5.3 91/01/20 21:10:43 bostic 5 4
c new stdio
e
s 00002/00002/00023
d D 5.2 86/03/09 20:49:15 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00021
d D 5.1 85/06/05 13:33:42 mckusick 3 2
c Add copyright
e
s 00002/00002/00020
d D 4.2 85/02/13 15:48:30 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00022/00000/00000
d D 4.1 80/12/21 16:50:10 wnj 1 0
c date and time created 80/12/21 16:50:10 by wnj
e
u
U
t
T
I 5
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

E 3
D 5
#include	<stdio.h>
E 5
I 5
#include <stdio.h>
#include <string.h>
E 5

I 5
/*
 * Read at most n-1 characters from the given file.
 * Stop when a newline has been read, or the count runs out.
 * Return first argument, or NULL if no characters were read.
 */
E 5
char *
D 5
fgets(s, n, iop)
char *s;
register FILE *iop;
E 5
I 5
fgets(buf, n, fp)
	char *buf;
	register size_t n;
	register FILE *fp;
E 5
{
D 5
	register c;
	register char *cs;
E 5
I 5
	register size_t len;
	register char *s;
	register unsigned char *p, *t;
E 5

D 5
	cs = s;
D 2
	while (--n>0 && (c = getc(iop))>=0) {
E 2
I 2
	while (--n>0 && (c = getc(iop)) != EOF) {
E 2
		*cs++ = c;
		if (c=='\n')
			break;
	}
D 2
	if (c<0 && cs==s)
E 2
I 2
	if (c == EOF && cs==s)
E 2
		return(NULL);
	*cs++ = '\0';
	return(s);
E 5
I 5
D 9
	if (n < 2)		/* sanity check */
E 9
I 9
	if (n == 0)		/* sanity check */
E 9
		return (NULL);

	s = buf;
	n--;			/* leave space for NUL */
D 9
	do {
E 9
I 9
	while (n != 0) {
E 9
		/*
		 * If the buffer is empty, refill it.
		 */
		if ((len = fp->_r) <= 0) {
			if (__srefill(fp)) {
				/* EOF/error: stop with partial or no line */
				if (s == buf)
					return (NULL);
				break;
			}
			len = fp->_r;
		}
		p = fp->_p;

		/*
		 * Scan through at most n bytes of the current buffer,
		 * looking for '\n'.  If found, copy up to and including
		 * newline, and stop.  Otherwise, copy entire chunk
		 * and loop.
		 */
		if (len > n)
			len = n;
		t = memchr((void *)p, '\n', len);
		if (t != NULL) {
			len = ++t - p;
			fp->_r -= len;
			fp->_p = t;
D 6
			(void) memcpy((void *)s, (void *)p, len);
E 6
I 6
D 7
			(void) bcopy((void *)p, (void *)s, len);
E 7
I 7
			(void)memcpy((void *)s, (void *)p, len);
E 7
E 6
			s[len] = 0;
			return (buf);
		}
		fp->_r -= len;
		fp->_p += len;
D 6
		(void) memcpy((void *)s, (void *)p, len);
E 6
I 6
D 7
		(void) bcopy((void *)p, (void *)s, len);
E 7
I 7
		(void)memcpy((void *)s, (void *)p, len);
E 7
E 6
		s += len;
D 9
	} while ((n -= len) != 0);
E 9
I 9
		n -= len;
	}
E 9
	*s = 0;
	return (buf);
E 5
}
E 1
