h47306
s 00002/00002/00156
d D 8.1 93/06/04 13:06:44 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00015/00143
d D 5.8 91/11/12 11:09:24 bostic 8 7
c make Reiser cpp happy
e
s 00006/00003/00152
d D 5.7 91/09/27 11:54:58 bostic 7 6
c KNF patrol
e
s 00040/00040/00115
d D 5.6 91/09/27 10:50:15 elan 6 5
c Changed macros so that all the  arguments in them are passed by the 
c calling procedure.  Also renamed the  vaiables  to  make the  code more 
c readable.
e
s 00001/00001/00154
d D 5.5 91/09/23 15:16:04 bostic 5 4
c fix copyright header
e
s 00035/00040/00120
d D 5.4 91/09/23 15:15:31 bostic 4 3
c minor cleanups by Elan and I.
e
s 00075/00017/00085
d D 5.3 91/08/06 12:40:06 elan 3 2
c Algorithm changed to cut down on number of calls to comparison fn.
c This change is motivated by Knuth, Vol. 3, p. 158, problem 18.  
c The savings in time are on the order of about 20 % for 100000 random elements.
c In addition to this change various details were changed to make the program
c more efficient such as assigning rather than swapping blocks of data.
e
s 00003/00000/00099
d D 5.2 91/07/22 12:37:03 bostic 2 1
c add contrib  notice
e
s 00100/00000/00000
d D 5.1 91/06/04 10:17:06 bostic 1 0
c date and time created 91/06/04 10:17:06 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Ronnie Kon at Mindcraft Inc., Kevin Lew and Elmer Yglesias.
 *
E 2
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 5
static char sccsid[] = "@(#)heapsort.c	1.3 (Berkeley) 7/29/91";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
E 3
#endif /* LIBC_SCCS and not lint */

D 4
#include <sys/cdefs.h>
E 4
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
I 4
#include <stddef.h>
E 4

/*
 * Swap two areas of size number of bytes.  Although qsort(3) permits random
 * blocks of memory to be sorted, sorting pointers is almost certainly the
 * common case (and, were it not, could easily be made so).  Regardless, it
 * isn't worth optimizing; the SWAP's get sped up by the cache, and pointer
 * arithmetic gets lost in the time required for comparison function calls.
 */
D 6
#define	SWAP(a, b) { \
D 3
	cnt = size; \
E 3
I 3
D 4
	int cnt = size; \
	char	ch; \
E 4
I 4
	cnt = size; \
E 6
I 6
#define	SWAP(a, b, count, size, tmp) { \
	count = size; \
E 6
E 4
E 3
	do { \
D 6
		ch = *a; \
E 6
I 6
		tmp = *a; \
E 6
		*a++ = *b; \
D 6
		*b++ = ch; \
	} while (--cnt); \
E 6
I 6
		*b++ = tmp; \
	} while (--count); \
E 6
}

D 4
/*
I 3
 * Assign one block of size size to another.
 */

#define ASSIGN(a,b) { \
	int cnt = size; \
	char *t1 = a, *t2 = b; \
E 4
I 4
/* Copy one block of size size to another. */
D 6
#define COPY(a, b) { \
	cnt = size; \
	t1 = a; \
	t2 = b; \
E 6
I 6
#define COPY(a, b, count, size, tmp1, tmp2) { \
	count = size; \
	tmp1 = a; \
	tmp2 = b; \
E 6
E 4
	do { \
D 6
		*t1++ = *t2++; \
	} while (--cnt); \
E 6
I 6
		*tmp1++ = *tmp2++; \
	} while (--count); \
E 6
}

D 4

E 4
/*
E 3
 * Build the list into a heap, where a heap is defined such that for
 * the records K1 ... KN, Kj/2 >= Kj for 1 <= j/2 <= j <= N.
 *
 * There two cases.  If j == nmemb, select largest of Ki and Kj.  If
 * j < nmemb, select largest of Ki, Kj and Kj+1.
D 4
 *
E 4
D 3
 * The initial value depends on if we're building the initial heap or
 * reconstructing it after saving a value.
E 3
 */
D 3
#define	HEAP(initval) { \
E 3
I 3
D 6
#define CREATE(initval) { \
D 4
	int i,j; \
	char *t,*p; \
E 4
E 3
	for (i = initval; (j = i * 2) <= nmemb; i = j) { \
		p = (char *)bot + j * size; \
		if (j < nmemb && compar(p, p + size) < 0) { \
			p += size; \
			++j; \
E 6
I 6
#define CREATE(initval, nmemb, par_i, child_i, par, child, size, count, tmp) { \
D 7
	for (par_i = initval; (child_i = par_i * 2) <= nmemb; par_i = child_i) { \
E 7
I 7
	for (par_i = initval; (child_i = par_i * 2) <= nmemb; \
	    par_i = child_i) { \
E 7
D 8
		child = (char *)bot + child_i * size; \
E 8
I 8
		child = base + child_i * size; \
E 8
		if (child_i < nmemb && compar(child, child + size) < 0) { \
			child += size; \
			++child_i; \
E 6
		} \
D 6
		t = (char *)bot + i * size; \
D 3
		if (compar(p, t) <= 0) \
E 3
I 3
D 4
		if (compar(p,t) <= 0) \
E 4
I 4
		if (compar(p, t) <= 0) \
E 6
I 6
D 8
		par = (char *)bot + par_i * size; \
E 8
I 8
		par = base + par_i * size; \
E 8
		if (compar(child, par) <= 0) \
E 6
E 4
E 3
			break; \
D 6
		SWAP(t, p); \
E 6
I 6
		SWAP(par, child, count, size, tmp); \
E 6
	} \
}

/*
I 3
 * Select the top of the heap and 'heapify'.  Since by far the most expensive
D 4
 * action is the call to the compar function, an considerable optimization
E 4
I 4
 * action is the call to the compar function, a considerable optimization
E 4
 * in the average case can be achieved due to the fact that k, the displaced
 * elememt, is ususally quite small, so it would be preferable to first
 * heapify, always maintaining the invariant that the larger child is copied
 * over its parent's record.
 *
D 4
 * Then, starting from the *bottom* of the heap, finding k's correct
 * place, again maintianing the invariant.  As a result of the invariant
 * no element is 'lost' when k is assigned it's correct place in the heap.
E 4
I 4
 * Then, starting from the *bottom* of the heap, finding k's correct place,
 * again maintianing the invariant.  As a result of the invariant no element
 * is 'lost' when k is assigned its correct place in the heap.
E 4
 *
 * The time savings from this optimization are on the order of 15-20% for the
 * average case. See Knuth, Vol. 3, page 158, problem 18.
I 8
 *
 * XXX Don't break the #define SELECT line, below.  Reiser cpp gets upset.
E 8
 */
D 4

#define SELECT(initval) { \
	int	i,j; \
	char	*p,*t; \
	for (i = initval; (j = i * 2) <= nmemb; i = j) { \
E 4
I 4
D 6
#define SELECT { \
	for (i = 1; (j = i * 2) <= nmemb; i = j) { \
E 4
		p = (char *)bot + j * size; \
		if (j < nmemb && compar(p, p + size) < 0) { \
			p += size; \
			++j; \
E 6
I 6
D 7
#define SELECT(par_i, child_i, nmemb, par, child, size, k, count, tmp1, tmp2) { \
E 7
I 7
D 8
#define SELECT(par_i, child_i, nmemb, par, child, size, k, count, tmp1, \
    tmp2) { \
E 8
I 8
#define SELECT(par_i, child_i, nmemb, par, child, size, k, count, tmp1, tmp2) { \
E 8
E 7
	for (par_i = 1; (child_i = par_i * 2) <= nmemb; par_i = child_i) { \
D 8
		child = (char *)bot + child_i * size; \
E 8
I 8
		child = base + child_i * size; \
E 8
		if (child_i < nmemb && compar(child, child + size) < 0) { \
			child += size; \
			++child_i; \
E 6
		} \
D 6
		t = (char *)bot + i * size; \
D 4
		ASSIGN(t, p); \
E 4
I 4
		COPY(t, p); \
E 6
I 6
D 8
		par = (char *)bot + par_i * size; \
E 8
I 8
		par = base + par_i * size; \
E 8
		COPY(par, child, count, size, tmp1, tmp2); \
E 6
E 4
	} \
D 4
	while (1) { \
E 4
I 4
	for (;;) { \
E 4
D 6
		j = i; \
		i = j / 2; \
		p = (char *)bot + j * size; \
		t = (char *)bot + i * size; \
D 4
		if ( j == initval || compar(k, t) < 0) { \
			ASSIGN(p, k); \
E 4
I 4
		if (j == 1 || compar(k, t) < 0) { \
			COPY(p, k); \
E 6
I 6
		child_i = par_i; \
		par_i = child_i / 2; \
D 8
		child = (char *)bot + child_i * size; \
		par = (char *)bot + par_i * size; \
E 8
I 8
		child = base + child_i * size; \
		par = base + par_i * size; \
E 8
		if (child_i == 1 || compar(k, par) < 0) { \
			COPY(child, k, count, size, tmp1, tmp2); \
E 6
E 4
			break; \
		} \
D 4
		ASSIGN(p, t); \
E 4
I 4
D 6
		COPY(p, t); \
E 6
I 6
		COPY(child, par, count, size, tmp1, tmp2); \
E 6
E 4
	} \
}

/*
E 3
 * Heapsort -- Knuth, Vol. 3, page 145.  Runs in O (N lg N), both average
 * and worst.  While heapsort is faster than the worst case of quicksort,
 * the BSD quicksort does median selection so that the chance of finding
 * a data set that will trigger the worst case is nonexistent.  Heapsort's
D 4
 * only advantage over quicksort is that it requires no additional memory.
E 4
I 4
 * only advantage over quicksort is that it requires little additional memory.
E 4
 */
I 3
int
E 3
D 8
heapsort(bot, nmemb, size, compar)
D 3
	register void *bot;
	register size_t nmemb, size;
	int (*compar) __P((const void *, const void *));
E 3
I 3
D 4
	void   *bot;
	size_t  nmemb, size;
	int     (*compar) __P((const void *, const void *));
E 4
I 4
	void *bot;
E 8
I 8
heapsort(vbase, nmemb, size, compar)
	void *vbase;
E 8
	size_t nmemb, size;
	int (*compar) __P((const void *, const void *));
E 4
E 3
{
D 3
	register char *p, *t, ch;
	register int cnt, i, j, l;
E 3
I 3
D 4
	char   *p, *t, *k = (char *) malloc(size);
	int     l;
E 4
I 4
	register int cnt, i, j, l;
D 6
	register char ch, *t1, *t2;
E 6
I 6
	register char tmp, *tmp1, *tmp2;
E 6
D 8
	char *k, *p, *t;
E 8
I 8
	char *base, *k, *p, *t;
E 8
E 4
E 3

	if (nmemb <= 1)
		return (0);
I 4

E 4
	if (!size) {
		errno = EINVAL;
		return (-1);
	}
I 4

	if ((k = malloc(size)) == NULL)
		return (-1);

E 4
	/*
	 * Items are numbered from 1 to nmemb, so offset from size bytes
	 * below the starting address.
	 */
D 8
	bot -= size;
E 8
I 8
	base = (char *)vbase - size;
E 8

	for (l = nmemb / 2 + 1; --l;)
D 3
		HEAP(l);
E 3
I 3
D 6
		CREATE(l);
E 6
I 6
		CREATE(l, nmemb, i, j, t, p, size, cnt, tmp);
E 6
E 3

	/*
	 * For each element of the heap, save the largest element into its
D 3
	 * final slot, then recreate the heap.
E 3
I 3
	 * final slot, save the displaced element (k), then recreate the
	 * heap.
E 3
	 */
	while (nmemb > 1) {
D 3
		p = (char *)bot + size;
		t = (char *)bot + nmemb * size;
		SWAP(p, t);
E 3
I 3
D 4
		p = (char *) bot + size;
		t = (char *) bot + nmemb * size;
		ASSIGN(k, t);
		ASSIGN(t, p);
E 4
I 4
D 6
		COPY(k, (char *)bot + nmemb * size);
		COPY((char *)bot + nmemb * size, (char *)bot + size);
E 6
I 6
D 8
		COPY(k, (char *)bot + nmemb * size, cnt, size, tmp1, tmp2);
D 7
		COPY((char *)bot + nmemb * size, (char *)bot + size,  cnt, size, tmp1, tmp2);
E 7
I 7
		COPY((char *)bot + nmemb * size, (char *)bot + size,
		    cnt, size, tmp1, tmp2);
E 8
I 8
		COPY(k, base + nmemb * size, cnt, size, tmp1, tmp2);
		COPY(base + nmemb * size, base + size, cnt, size, tmp1, tmp2);
E 8
E 7
E 6
E 4
E 3
		--nmemb;
D 3
		HEAP(1);
E 3
I 3
D 4
		SELECT(1);
E 4
I 4
D 6
		SELECT;
E 6
I 6
		SELECT(i, j, nmemb, t, p, size, k, cnt, tmp1, tmp2);
E 6
E 4
E 3
	}
I 4
	free(k);
E 4
	return (0);
}
E 1
