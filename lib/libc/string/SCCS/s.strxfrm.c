h04253
s 00002/00002/00039
d D 8.1 93/06/04 15:13:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00015/00033
d D 5.3 92/10/04 13:10:15 bostic 3 2
c make it work for n==0: give in and run strlen first, then use memcpy
c from Chris Torek
e
s 00001/00001/00047
d D 5.2 91/01/26 15:32:11 bostic 2 1
c stdc.h -> cdefs.h
e
s 00048/00000/00000
d D 5.1 90/05/17 11:11:04 bostic 1 0
c date and time created 90/05/17 11:11:04 by bostic
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

D 2
#include <sys/stdc.h>
E 2
I 2
#include <sys/cdefs.h>
E 2
#include <string.h>

/*
 * Transform src, storing the result in dst, such that
 * strcmp() on transformed strings returns what strcoll()
 * on the original untransformed strings would return.
 */
size_t
strxfrm(dst, src, n)
	register char *dst;
D 3
	register const char *src;
	register size_t n;
E 3
I 3
	const char *src;
	size_t n;
E 3
{
D 3
	register size_t r = 0;
	register int c;
E 3
I 3
	register size_t srclen, copysize;
E 3

	/*
	 * Since locales are unimplemented, this is just a copy.
	 */
I 3
	srclen = strlen(src);
E 3
	if (n != 0) {
D 3
		while ((c = *src++) != 0) {
			r++;
			if (--n == 0) {
				while (*src++ != 0)
					r++;
				break;
			}
			*dst++ = c;
		}
		*dst = 0;
E 3
I 3
		copysize = srclen < n ? srclen : n - 1;
		(void)memcpy(dst, src, copysize);
		dst[copysize] = 0;
E 3
	}
D 3
	return (r);
E 3
I 3
	return (srclen);
E 3
}
E 1
