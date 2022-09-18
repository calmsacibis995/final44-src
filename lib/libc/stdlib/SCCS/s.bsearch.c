h55569
s 00002/00002/00053
d D 8.1 93/06/04 13:05:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00053
d D 5.6 91/11/19 13:34:53 torek 6 5
c lim cannot be signed, must be size_t
e
s 00002/00002/00052
d D 5.5 91/07/22 10:41:46 bostic 5 4
c delete comment
e
s 00006/00006/00048
d D 5.4 91/02/23 22:56:34 donn 4 3
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00000/00053
d D 5.3 90/05/17 11:57:18 bostic 3 2
c might as well keep header and source in sync
e
s 00036/00029/00017
d D 5.2 90/05/16 12:26:24 bostic 2 1
c faster version from Chris Torek
e
s 00046/00000/00000
d D 5.1 89/10/14 14:28:52 bostic 1 0
c date and time created 89/10/14 14:28:52 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
D 7
 * Copyright (c) 1990 Regents of the University of California.
E 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 2
#include <sys/types.h>
#include <stdio.h>
E 2
I 2
D 5
#include <stddef.h>		/* size_t */
E 5
I 5
#include <stddef.h>
E 5
I 3
#include <stdlib.h>
E 3
E 2

D 2
char *
bsearch(key, base, nmemb, size, compar)
	register char *key, *base;
E 2
I 2
/*
 * Perform a binary search.
 *
 * The code below is a bit sneaky.  After a comparison fails, we
 * divide the work in half by moving either left or right. If lim
 * is odd, moving left simply involves halving lim: e.g., when lim
 * is 5 we look at item 2, so we change lim to 2 so that we will
 * look at items 0 & 1.  If lim is even, the same applies.  If lim
 * is odd, moving right again involes halving lim, this time moving
 * the base up one item past p: e.g., when lim is 5 we change base
 * to item 3 and make lim 2 so that we will look at items 3 and 4.
 * If lim is even, however, we have to shrink it by one before
 * halving: e.g., when lim is 4, we still looked at item 2, so we
 * have to make lim 3, then halve, obtaining 1, so that we will only
 * look at item 3.
 */
void *
bsearch(key, base0, nmemb, size, compar)
D 4
	register void *key;
	void *base0;
E 4
I 4
	register const void *key;
	const void *base0;
E 4
E 2
	size_t nmemb;
	register size_t size;
D 4
	register int (*compar)();
E 4
I 4
	register int (*compar) __P((const void *, const void *));
E 4
{
D 2
	register int bottom, middle, result, top;
	register char *p;
E 2
I 2
D 4
	register char *base = base0;
E 4
I 4
	register const char *base = base0;
E 4
D 6
	register int lim, cmp;
E 6
I 6
	register size_t lim;
	register int cmp;
E 6
D 4
	register void *p;
E 4
I 4
	register const void *p;
E 4
E 2

D 2
	for (bottom = 0, top = nmemb - 1; bottom <= top;) {
		middle = (bottom + top) >> 1;
		p = base + middle * size;
		if (!(result = (*compar)(key, p)))
			return(p);
		if (result > 0)
			bottom = middle + 1;
		else
			top = middle - 1;
E 2
I 2
	for (lim = nmemb; lim != 0; lim >>= 1) {
		p = base + (lim >> 1) * size;
		cmp = (*compar)(key, p);
		if (cmp == 0)
D 4
			return (p);
E 4
I 4
			return ((void *)p);
E 4
		if (cmp > 0) {	/* key > p: move right */
			base = (char *)p + size;
			lim--;
D 5
		} /* else move left */
E 5
I 5
		}		/* else move left */
E 5
E 2
	}
D 2
	return(NULL);
E 2
I 2
	return (NULL);
E 2
}
E 1
