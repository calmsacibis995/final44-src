h39527
s 00001/00001/00320
d D 8.2 94/02/14 07:08:56 bostic 4 3
c mistake in the natural merge setup, broke on Jan-Simon's directory
c setup; From: pmcilroy@physics.att.com (Peter McIlroy)
e
s 00002/00002/00319
d D 8.1 93/06/04 13:07:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00320
d D 5.2 92/12/02 16:21:48 bostic 2 1
c typo
e
s 00321/00000/00000
d D 5.1 92/12/02 15:55:33 bostic 1 0
c merge sort from Peter McIlroy
c date and time created 92/12/02 15:55:33 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Peter McIlroy.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
 * Hybrid exponential search/linear search merge sort with hybrid
 * natural/pairwise first pass.  Requires about .3% more comparisons
 * for random data than LSMS with pairwise first pass alone.
 * It works for objects as small as two bytes.
 */

#define NATURAL
#define THRESHOLD 16	/* Best choice for natural merge cut-off. */

/* #define NATURAL to get hybrid natural merge.
 * (The default is pairwise merging.)
 */

#include <sys/types.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

static void setup __P((u_char *, u_char *, size_t, size_t, int (*)()));
static void insertionsort __P((u_char *, size_t, size_t, int (*)()));

#define ISIZE sizeof(int)
#define PSIZE sizeof(u_char *)
#define ICOPY_LIST(src, dst, last)				\
	do							\
	*(int*)dst = *(int*)src, src += ISIZE, dst += ISIZE;	\
	while(src < last)
#define ICOPY_ELT(src, dst, i)					\
	do							\
	*(int*) dst = *(int*) src, src += ISIZE, dst += ISIZE;	\
	while (i -= ISIZE)

#define CCOPY_LIST(src, dst, last)		\
	do					\
		*dst++ = *src++;		\
	while (src < last)
#define CCOPY_ELT(src, dst, i)			\
	do					\
		*dst++ = *src++;		\
	while (i -= 1)
		
/*
 * Find the next possible pointer head.  (Trickery for forcing an array
 * to do double duty as a linked list when objects do not align with word
 * boundaries.
 */
/* Assumption: PSIZE is a power of 2. */
#define EVAL(p) (u_char **)						\
	((u_char *)0 +							\
	    (((u_char *)p + PSIZE - 1 - (u_char *) 0) & ~(PSIZE - 1)))

/*
 * Arguments are as for qsort.
 */
int
mergesort(base, nmemb, size, cmp)
	void *base;
	size_t nmemb;
	register size_t size;
	int (*cmp) __P((const void *, const void *));
{
	register int i, sense;
	int big, iflag;
	register u_char *f1, *f2, *t, *b, *tp2, *q, *l1, *l2;
	u_char *list2, *list1, *p2, *p, *last, **p1;

D 2
	if (size < PSIZE/2) {	/* pointers must fit into 2*size */
E 2
I 2
	if (size < PSIZE / 2) {		/* Pointers must fit into 2 * size. */
E 2
		errno = EINVAL;
		return (-1);
	}

	/*
	 * XXX
	 * Stupid subtraction for the Cray.
	 */
	iflag = 0;
	if (!(size % ISIZE) && !(((char *)base - (char *)0) % ISIZE))
		iflag = 1;

	if ((list2 = malloc(nmemb * size + PSIZE)) == NULL)
		return (-1);

	list1 = base;
	setup(list1, list2, nmemb, size, cmp);
	last = list2 + nmemb * size;
	i = big = 0;
	while (*EVAL(list2) != last) {
	    l2 = list1;
	    p1 = EVAL(list1);
	    for (tp2 = p2 = list2; p2 != last; p1 = EVAL(l2)) {
	    	p2 = *EVAL(p2);
	    	f1 = l2;
	    	f2 = l1 = list1 + (p2 - list2);
	    	if (p2 != last)
	    		p2 = *EVAL(p2);
	    	l2 = list1 + (p2 - list2);
	    	while (f1 < l1 && f2 < l2) {
	    		if ((*cmp)(f1, f2) <= 0) {
	    			q = f2;
	    			b = f1, t = l1;
	    			sense = -1;
	    		} else {
	    			q = f1;
	    			b = f2, t = l2;
	    			sense = 0;
	    		}
	    		if (!big) {	/* here i = 0 */
LINEAR:	    			while ((b += size) < t && cmp(q, b) >sense)
	    				if (++i == 6) {
	    					big = 1;
	    					goto EXPONENTIAL;
	    				}
	    		} else {
EXPONENTIAL:	    		for (i = size; ; i <<= 1)
	    				if ((p = (b + i)) >= t) {
	    					if ((p = t - size) > b &&
						    (*cmp)(q, p) <= sense)
	    						t = p;
	    					else
	    						b = p;
	    					break;
	    				} else if ((*cmp)(q, p) <= sense) {
	    					t = p;
	    					if (i == size)
	    						big = 0; 
	    					goto FASTCASE;
	    				} else
	    					b = p;
SLOWCASE:	    		while (t > b+size) {
	    				i = (((t - b) / size) >> 1) * size;
	    				if ((*cmp)(q, p = b + i) <= sense)
	    					t = p;
	    				else
	    					b = p;
	    			}
	    			goto COPY;
FASTCASE:	    		while (i > size)
	    				if ((*cmp)(q,
	    					p = b + (i >>= 1)) <= sense)
	    					t = p;
	    				else
	    					b = p;
COPY:	    			b = t;
	    		}
	    		i = size;
	    		if (q == f1) {
	    			if (iflag) {
	    				ICOPY_LIST(f2, tp2, b);
	    				ICOPY_ELT(f1, tp2, i);
	    			} else {
	    				CCOPY_LIST(f2, tp2, b);
	    				CCOPY_ELT(f1, tp2, i);
	    			}
	    		} else {
	    			if (iflag) {
	    				ICOPY_LIST(f1, tp2, b);
	    				ICOPY_ELT(f2, tp2, i);
	    			} else {
	    				CCOPY_LIST(f1, tp2, b);
	    				CCOPY_ELT(f2, tp2, i);
	    			}
	    		}
	    	}
	    	if (f2 < l2) {
	    		if (iflag)
	    			ICOPY_LIST(f2, tp2, l2);
	    		else
	    			CCOPY_LIST(f2, tp2, l2);
	    	} else if (f1 < l1) {
	    		if (iflag)
	    			ICOPY_LIST(f1, tp2, l1);
	    		else
	    			CCOPY_LIST(f1, tp2, l1);
	    	}
	    	*p1 = l2;
	    }
	    tp2 = list1;	/* swap list1, list2 */
	    list1 = list2;
	    list2 = tp2;
	    last = list2 + nmemb*size;
	}
	if (base == list2) {
		memmove(list2, list1, nmemb*size);
		list2 = list1;
	}
	free(list2);
	return (0);
}

#define	swap(a, b) {					\
		s = b;					\
		i = size;				\
		do {					\
			tmp = *a; *a++ = *s; *s++ = tmp; \
		} while (--i);				\
		a -= size;				\
	}
#define reverse(bot, top) {				\
	s = top;					\
	do {						\
		i = size;				\
		do {					\
			tmp = *bot; *bot++ = *s; *s++ = tmp; \
		} while (--i);				\
		s -= size2;				\
	} while(bot < s);				\
}

/*
 * Optional hybrid natural/pairwise first pass.  Eats up list1 in runs of
 * increasing order, list2 in a corresponding linked list.  Checks for runs
 * when THRESHOLD/2 pairs compare with same sense.  (Only used when NATURAL
 * is defined.  Otherwise simple pairwise merging is used.)
 */
void
setup(list1, list2, n, size, cmp)
	size_t n, size;
	int (*cmp) __P((const void *, const void *));
	u_char *list1, *list2;
{
	int i, length, size2, tmp, sense;
	u_char *f1, *f2, *s, *l2, *last, *p2;

	size2 = size*2;
	if (n <= 5) {
		insertionsort(list1, n, size, cmp);
		*EVAL(list2) = (u_char*) list2 + n*size;
		return;
	}
	/*
	 * Avoid running pointers out of bounds; limit n to evens
	 * for simplicity.
	 */
	i = 4 + (n & 1);
	insertionsort(list1 + (n - i) * size, i, size, cmp);
	last = list1 + size * (n - i);
	*EVAL(list2 + (last - list1)) = list2 + n * size;

#ifdef NATURAL
	p2 = list2;
	f1 = list1;
	sense = (cmp(f1, f1 + size) > 0);
	for (; f1 < last; sense = !sense) {
		length = 2;
					/* Find pairs with same sense. */
		for (f2 = f1 + size2; f2 < last; f2 += size2) {
			if ((cmp(f2, f2+ size) > 0) != sense)
				break;
			length += 2;
		}
		if (length < THRESHOLD) {		/* Pairwise merge */
			do {
				p2 = *EVAL(p2) = f1 + size2 - list1 + list2;
				if (sense > 0)
					swap (f1, f1 + size);
			} while ((f1 += size2) < f2);
		} else {				/* Natural merge */
			l2 = f2;
			for (f2 = f1 + size2; f2 < l2; f2 += size2) {
				if ((cmp(f2-size, f2) > 0) != sense) {
					p2 = *EVAL(p2) = f2 - list1 + list2;
					if (sense > 0)
						reverse(f1, f2-size);
					f1 = f2;
				}
			}
			if (sense > 0)
				reverse (f1, f2-size);
			f1 = f2;
D 4
			if (f2 < last || cmp(f2, f2 + size) > 0)
E 4
I 4
			if (f2 < last || cmp(f2 - size, f2) > 0)
E 4
				p2 = *EVAL(p2) = f2 - list1 + list2;
			else
				p2 = *EVAL(p2) = list2 + n*size;
		}
	}
#else		/* pairwise merge only. */
	for (f1 = list1, p2 = list2; f1 < last; f1 += size2) {
		p2 = *EVAL(p2) = p2 + size2;
		if (cmp (f1, f1 + size) > 0)
			swap(f1, f1 + size);
	}
#endif /* NATURAL */
}

/*
 * This is to avoid out-of-bounds addresses in sorting the
 * last 4 elements.
 */
static void
insertionsort(a, n, size, cmp)
	u_char *a;
	size_t n, size;
	int (*cmp) __P((const void *, const void *));
{
	u_char *ai, *s, *t, *u, tmp;
	int i;

	for (ai = a+size; --n >= 1; ai += size)
		for (t = ai; t > a; t -= size) {
			u = t - size;
			if (cmp(u, t) <= 0)
				break;
			swap(u, t);
		}
}
E 1
