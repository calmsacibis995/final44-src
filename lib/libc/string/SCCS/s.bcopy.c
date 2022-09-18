h44054
s 00002/00002/00111
d D 8.1 93/06/04 15:10:11 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00007/00109
d D 5.11 91/06/21 12:25:03 torek 11 10
c memcpy and memmove must always return first arg
e
s 00002/00002/00114
d D 5.10 91/02/24 13:20:04 bostic 10 9
c bcopy takes a void *, not a char *
e
s 00001/00001/00115
d D 5.9 91/01/26 15:31:47 bostic 9 8
c stdc.h -> cdefs.h
e
s 00018/00000/00098
d D 5.8 90/06/23 10:51:13 bostic 8 7
c build memcopy and memmove out of fast bcopy code
e
s 00082/00049/00016
d D 5.7 90/05/16 16:27:33 bostic 7 6
c Chris Torek's new version; runs better on non-aligned addresses/lengths
e
s 00001/00001/00064
d D 5.6 89/07/25 11:20:59 jak 6 5
c fixed backwards copy by words
e
s 00021/00013/00044
d D 5.5 89/07/23 13:13:13 karels 5 4
c make it compile *and* work (and portable)
e
s 00000/00001/00057
d D 5.4 89/04/01 14:32:52 bostic 4 3
c bcopy and bzero don't return any value
e
s 00003/00001/00055
d D 5.3 89/03/08 16:46:24 bostic 3 2
c make it compile...
e
s 00014/00003/00042
d D 5.2 88/07/21 11:31:57 bostic 2 1
c add Berkeley specific copyright; written by Robert Elz
e
s 00045/00000/00000
d D 5.1 87/01/27 16:02:46 mckusick 1 0
c new addition for portability
e
u
U
t
T
I 1
D 7
/*
D 5
 * Copyright (c) 1987 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1987, 1989 Regents of the University of California.
E 7
I 7
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
E 7
E 5
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 7
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 7
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif LIBC_SCCS and not lint
E 2
I 2
#endif /* LIBC_SCCS and not lint */
E 2

I 3
D 7
#include <sys/types.h>
E 7
I 7
D 9
#include <sys/stdc.h>
E 9
I 9
#include <sys/cdefs.h>
E 9
#include <string.h>
E 7

E 3
/*
D 5
 * bcopy -- vax movc3 instruction
E 5
I 5
D 7
 * bcopy -- copy memory block, handling overlap of source and destination
 *	(vax movc3 instruction)
E 7
I 7
 * sizeof(word) MUST BE A POWER OF TWO
 * SO THAT wmask BELOW IS ALL ONES
E 7
E 5
 */
I 7
typedef	int word;		/* "word" used for optimal copy speed */
E 7
I 5

D 7
typedef int word;		/* size of "word" used for optimal copy speed */
E 7
I 7
#define	wsize	sizeof(word)
#define	wmask	(wsize - 1)
E 7

E 5
D 7
bcopy(src, dst, length)
D 3
	register char *src, *dst;
E 3
I 3
D 5
	register long *src, *dst;
E 5
I 5
	register char *src, *dst;
E 5
E 3
	register int length;
E 7
I 7
/*
 * Copy a block of memory, handling overlap.
 * This is the routine that actually implements
 * (the portable versions of) bcopy, memcpy, and memmove.
 */
I 8
#ifdef MEMCOPY
void *
memcpy(dst0, src0, length)
#else
#ifdef MEMMOVE
void *
memmove(dst0, src0, length)
#else
E 8
void
bcopy(src0, dst0, length)
I 8
#endif
#endif
E 8
D 10
	char *dst0;
	const char *src0;
E 10
I 10
	void *dst0;
	const void *src0;
E 10
	register size_t length;
E 7
{
D 7
	if (length && src != dst)
		if ((u_int)dst < (u_int)src)
D 5
			if (((int)src | (int)dst | length) & 3)
E 5
I 5
			if (((int)src | (int)dst | length) & (sizeof(word) - 1))
E 5
				do	/* copy by bytes */
					*dst++ = *src++;
				while (--length);
			else {
D 5
				length >>= 2;
				do	/* copy by longs */
					*((long *)dst)++ = *((long *)src)++;
				while (--length);
E 5
I 5
				length /= sizeof(word);
				do {	/* copy by words */
					*(word *)dst = *(word *)src;
					src += sizeof(word);
					dst += sizeof(word);
				} while (--length);
E 5
			}
		else {			/* copy backwards */
			src += length;
			dst += length;
D 5
			if (((int)src | (int)dst | length) & 3)
E 5
I 5
			if (((int)src | (int)dst | length) & (sizeof(word) - 1))
E 5
				do	/* copy by bytes */
					*--dst = *--src;
				while (--length);
			else {
D 5
				length >>= 2;
				do	/* copy by shorts */
					*--((long *)dst) = *--((long *)src);
				while (--length);
E 5
I 5
				length /= sizeof(word);
				do {	/* copy by words */
D 6
					*(word *)dst = *(word *)src;
E 6
					src -= sizeof(word);
					dst -= sizeof(word);
I 6
					*(word *)dst = *(word *)src;
E 6
				} while (--length);
E 5
			}
E 7
I 7
	register char *dst = dst0;
	register const char *src = src0;
	register size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
D 11
		return;
E 11
I 11
		goto done;
E 11

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)

	if ((unsigned long)dst < (unsigned long)src) {
		/*
		 * Copy forward.
		 */
		t = (int)src;	/* only need low bits */
		if ((t | (int)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (int)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
E 7
		}
I 7
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (int)src;
		if ((t | (int)dst) & wmask) {
			if ((t ^ (int)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
I 8
D 11
#ifdef MEMCOPY
	return(dst0);
E 11
I 11
done:
#if defined(MEMCOPY) || defined(MEMMOVE)
	return (dst0);
E 11
#else
D 11
#ifdef MEMMOVE
	return(dst0);
#else
E 11
E 8
	return;
I 8
D 11
#endif
E 11
#endif
E 8
E 7
D 4
	return(0);
E 4
}
E 1
