h30227
s 00002/00002/00146
d D 8.1 93/06/04 13:07:42 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00023/00133
d D 5.14 93/01/19 18:51:49 bostic 16 15
c fix the copyright notice, make the style consistent
e
s 00006/00007/00150
d D 5.13 93/01/18 14:11:50 elan 15 14
c Fixed bug in tail recursion elimination.
e
s 00001/00001/00156
d D 5.12 93/01/08 17:33:01 bostic 14 13
c typo in integration
e
s 00121/00221/00036
d D 5.11 92/12/10 12:16:07 elan 13 12
c New qsort from Bentley & McIlroy.
e
s 00008/00000/00249
d D 5.10 92/06/22 12:47:30 bostic 12 11
c put Bentley's comment into the source code for info purposes
e
s 00006/00003/00243
d D 5.9 91/02/23 22:56:39 donn 11 10
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00208/00173/00038
d D 5.8 90/11/26 16:52:52 bostic 10 9
c reimplementation of qsort
c fix so that comparison routine can call qsort
c do insertion sort of each partition at THRESH
c detect already sorted data and skip partition sort
c select a better median in a few cases
c some coding improvements, and lots of comments
e
s 00001/00000/00210
d D 5.7 90/05/17 15:38:39 bostic 9 8
c change declaration to match stdlib.h
e
s 00002/00000/00208
d D 5.6 90/05/17 11:57:21 bostic 8 7
c might as well keep header and source in sync
e
s 00003/00013/00205
d D 5.5 90/05/16 12:30:14 bostic 7 6
c add new copyright notice
e
s 00010/00005/00208
d D 5.4 88/06/27 17:34:09 bostic 6 5
c install approved copyright notice
e
s 00009/00003/00204
d D 5.3 88/05/23 20:18:32 bostic 5 4
c added Berkeley specific header
e
s 00002/00002/00205
d D 5.2 86/03/09 19:53:05 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00198
d D 5.1 85/06/05 12:30:25 mckusick 3 2
c Add copyright
e
s 00181/00103/00018
d D 4.2 83/03/09 00:50:33 mckusick 2 1
c Earl Cohen's faster version of qsort
e
s 00121/00000/00000
d D 4.1 80/12/21 16:39:59 wnj 1 0
c date and time created 80/12/21 16:39:59 by wnj
e
u
U
t
T
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
E 7
I 7
D 13
/*-
D 10
 * Copyright (c) 1980, 1983 The Regents of the University of California.
E 10
I 10
 * Copyright (c) 1980, 1983, 1990 The Regents of the University of California.
E 13
I 13
D 16
/*
E 16
I 16
/*-
E 16
D 17
 * Copyright (c) 1992 The Regents of the University of California.
E 13
E 10
E 7
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
I 13
D 16
 *
E 16
E 13
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

D 4
#ifndef lint
E 4
I 4
D 13
#if defined(LIBC_SCCS) && !defined(lint)
E 13
I 13
D 16

#ifndef lint
static char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 16
I 16
#if defined(LIBC_SCCS) && !defined(lint)
E 16
E 13
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
D 13
#endif /* LIBC_SCCS and not lint */
E 13
I 13
D 16
#endif /* not lint */
E 16
I 16
#endif /* LIBC_SCCS and not lint */
E 16
E 13
E 5
E 4
E 3

I 8
D 10
#include <stdlib.h>
E 10
I 10
#include <sys/types.h>
I 16
#include <stdlib.h>
E 16
I 11
D 13
#include <stdlib.h>
E 13
E 11
E 10

E 8
D 2
static int	(*qscmp)();
static int	qses;
E 2
I 2
D 13
/*
I 12
 * XXX
 * Report from John Bentley at ATT:  the BSD qsort goes quadratic on random
 * 0 and 1  (N/2 of each.)  This is because it does not keep = elements
 * together.   (<= go before test element; > go after, > so everything gets
 * shoved before the test element, which is qsort's worst case.)
 */
E 13
I 13
D 16
static char	*med3 __P((char *, char *, char *, int (*)()));
static void	 swapfunc __P((char *, char *, int, int));
E 16
I 16
static inline char	*med3 __P((char *, char *, char *, int (*)()));
static inline void	 swapfunc __P((char *, char *, int, int));
E 16
E 13

D 13
/*
E 12
D 10
 * qsort.c:
 * Our own version of the system qsort routine which is faster by an average
 * of 25%, with lows and highs of 10% and 50%.
 * The THRESHold below is the insertion sort threshold, and has been adjusted
 * for records of size 48 bytes.
 * The MTHREShold is where we stop finding a better median.
E 10
I 10
 * MTHRESH is the smallest partition for which we compare for a median
 * value instead of using the middle value.
E 10
 */
I 10
#define	MTHRESH	6
E 13
I 13
D 16
#define min(a, b) (a) < (b) ? a : b
E 16
I 16
#define min(a, b)	(a) < (b) ? a : b
E 16
E 13
E 10
E 2

D 2
qsort(a, n, es, fc)
char *a;
unsigned n;
int es;
int (*fc)();
{
	qscmp = fc;
	qses = es;
	qs1(a, a+n*es);
}
E 2
I 2
D 10
#define		THRESH		4		/* threshold for insertion */
#define		MTHRESH		6		/* threshold for median */
E 2

D 2
static qs1(a, l)
char *a, *l;
{
	register char *i, *j;
	register es;
	char **k;
	char *lp, *hp;
	int c;
	unsigned n;
E 2
I 2
static  int		(*qcmp)();		/* the comparison routine */
static  int		qsz;			/* size of each record */
static  int		thresh;			/* THRESHold in chars */
static  int		mthresh;		/* MTHRESHold in chars */
E 2

E 10
I 2
/*
D 10
 * qsort:
 * First, set up some global parameters for qst to share.  Then, quicksort
 * with qst(), and then a cleanup insertion sort ourselves.  Sound simple?
 * It's not...
E 10
I 10
D 13
 * THRESH is the minimum number of entries in a partition for continued
 * partitioning.
E 13
I 13
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
E 13
E 10
 */
I 10
D 13
#define	THRESH	4
E 13
I 13
#define swapcode(TYPE, parmi, parmj, n) { 		\
	long i = (n) / sizeof (TYPE); 			\
	register TYPE *pi = (TYPE *) (parmi); 		\
	register TYPE *pj = (TYPE *) (parmj); 		\
	do { 						\
		register TYPE	t = *pi;		\
		*pi++ = *pj;				\
		*pj++ = t;				\
        } while (--i > 0);				\
}
E 13
E 10
E 2

I 9
D 13
void
E 9
D 2
	es = qses;
E 2
I 2
D 10
qsort(base, n, size, compar)
	char	*base;
	int	n;
	int	size;
	int	(*compar)();
E 10
I 10
qsort(bot, nmemb, size, compar)
D 11
	char *bot;
	int nmemb, size, (*compar)();
E 11
I 11
	void *bot;
	size_t nmemb, size;
	int (*compar) __P((const void *, const void *));
E 11
E 10
{
D 10
	register char c, *i, *j, *lo, *hi;
	char *min, *max;
E 10
I 10
D 11
	void insertion_sort(), quick_sort();
E 11
I 11
	static void insertion_sort(), quick_sort();
E 13
I 13
#define SWAPINIT(a, es) swaptype = ((char *)a - (char *)0) % sizeof(long) || \
	es % sizeof(long) ? 2 : es == sizeof(long)? 0 : 1;
E 13
E 11
E 10
E 2

D 2
start:
	if((n=l-a) <= es)
E 2
I 2
D 10
	if (n <= 1)
E 10
I 10
D 13
	if (nmemb <= 1)
E 10
E 2
		return;
D 2
	n = es * (n / (2*es));
	hp = lp = a+n;
	i = a;
	j = l-es;
	for(;;) {
		if(i < lp) {
			if((c = (*qscmp)(i, lp)) == 0) {
				qsexc(i, lp -= es);
				continue;
			}
			if(c < 0) {
				i += es;
				continue;
			}
E 2
I 2
D 10
	qsz = size;
	qcmp = compar;
	thresh = qsz * THRESH;
	mthresh = qsz * MTHRESH;
	max = base + n * qsz;
	if (n >= THRESH) {
		qst(base, max);
		hi = base + thresh;
	} else {
		hi = max;
	}
E 10
I 10

	if (nmemb >= THRESH)
		quick_sort(bot, nmemb, size, compar);
E 13
I 13
D 16
static void
E 16
I 16
static inline void
E 16
swapfunc(a, b, n, swaptype)
	char *a, *b;
	int n, swaptype;
{
	if(swaptype <= 1) 
		swapcode(long, a, b, n)
E 13
	else
D 13
		insertion_sort(bot, nmemb, size, compar);
E 13
I 13
		swapcode(char, a, b, n)
E 13
}

D 13
/*
 * Swap two areas of size number of bytes.  Although qsort(3) permits random
 * blocks of memory to be sorted, sorting pointers is almost certainly the
 * common case (and, were it not, could easily be made so).  Regardless, it
 * isn't worth optimizing; the SWAP's get sped up by the cache, and pointer
 * arithmetic gets lost in the time required for comparison function calls.
 */
#define	SWAP(a, b) { \
	cnt = size; \
	do { \
		ch = *a; \
		*a++ = *b; \
		*b++ = ch; \
	} while (--cnt); \
}
E 13
I 13
D 16
#define swap(a, b) \
	if (swaptype == 0) { \
		long t = *(long *)(a); \
		*(long *)(a) = *(long *)(b); \
		*(long *)(b) = t; \
	} else \
E 16
I 16
#define swap(a, b)					\
	if (swaptype == 0) {				\
		long t = *(long *)(a);			\
		*(long *)(a) = *(long *)(b);		\
		*(long *)(b) = t;			\
	} else						\
E 16
		swapfunc(a, b, es, swaptype)
E 13

D 13
/*
 * Knuth, Vol. 3, page 116, Algorithm Q, step b, argues that a single pass
 * of straight insertion sort after partitioning is complete is better than
 * sorting each small partition as it is created.  This isn't correct in this
 * implementation because comparisons require at least one (and often two)
 * function calls and are likely to be the dominating expense of the sort.
 * Doing a final insertion sort does more comparisons than are necessary
 * because it compares the "edges" and medians of the partitions which are
 * known to be already sorted.
 *
 * This is also the reasoning behind selecting a small THRESH value (see
 * Knuth, page 122, equation 26), since the quicksort algorithm does less
 * comparisons than the insertion sort.
 */
#define	SORT(bot, n) { \
	if (n > 1) \
		if (n == 2) { \
			t1 = bot + size; \
			if (compar(t1, bot) < 0) \
				SWAP(t1, bot); \
		} else \
			insertion_sort(bot, n, size, compar); \
E 13
I 13
#define vecswap(a, b, n) 	if ((n) > 0) swapfunc(a, b, n, swaptype)

D 16
static char *
E 16
I 16
static inline char *
E 16
med3(a, b, c, cmp)
	char *a, *b, *c;
	int (*cmp)();
{
	return cmp(a, b) < 0 ?
	       (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a ))
              :(cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c ));
E 13
}

D 13
static void
quick_sort(bot, nmemb, size, compar)
	register char *bot;
	register int size;
	int nmemb, (*compar)();
E 13
I 13
void
qsort(a, n, es, cmp)
	void *a;
	size_t n, es;
	int (*cmp)();
E 13
{
D 13
	register int cnt;
	register u_char ch;
	register char *top, *mid, *t1, *t2;
	register int n1, n2;
	char *bsv;
I 11
	static void insertion_sort();
E 13
I 13
	char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
	int d, r, swaptype, swap_cnt;
E 13
E 11

D 13
	/* bot and nmemb must already be set. */
partition:

	/* find mid and top elements */
	mid = bot + size * (nmemb >> 1);
	top = bot + (nmemb - 1) * size;

E 10
	/*
D 10
	 * First put smallest element, which must be in the first THRESH, in
	 * the first position as a sentinel.  This is done just by searching
	 * the first THRESH elements (or the first n if n < THRESH), finding
	 * the min, and swapping it into the first position.
E 10
I 10
	 * Find the median of the first, last and middle element (see Knuth,
	 * Vol. 3, page 123, Eq. 28).  This test order gets the equalities
	 * right.
E 10
	 */
D 10
	for (j = lo = base; (lo += qsz) < hi; )
		if (qcmp(j, lo) > 0)
			j = lo;
	if (j != base) {
		/* swap j into place */
		for (i = base, hi = base + qsz; i < hi; ) {
			c = *j;
			*j++ = *i;
			*i++ = c;
E 10
I 10
	if (nmemb >= MTHRESH) {
		n1 = compar(bot, mid);
		n2 = compar(mid, top);
		if (n1 < 0 && n2 > 0)
			t1 = compar(bot, top) < 0 ? top : bot;
		else if (n1 > 0 && n2 < 0)
			t1 = compar(bot, top) > 0 ? top : bot;
		else
			t1 = mid;

		/* if mid element not selected, swap selection there */
		if (t1 != mid) {
			SWAP(t1, mid);
			mid -= size;
E 13
I 13
loop:	SWAPINIT(a, es);
	swap_cnt = 0;
	if (n < 7) {
		for (pm = a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0;
			     pl -= es)
				swap(pl, pl - es);
		return;
	}
	pm = a + (n / 2) * es;
	if (n > 7) {
		pl = a;
		pn = a + (n - 1) * es;
		if (n > 40) {
			d = (n / 8) * es;
			pl = med3(pl, pl + d, pl + 2 * d, cmp);
			pm = med3(pm - d, pm, pm + d, cmp);
			pn = med3(pn - 2 * d, pn - d, pn, cmp);
E 13
E 10
E 2
		}
I 13
		pm = med3(pl, pm, pn, cmp);
E 13
D 2

loop:
		if(j > hp) {
			if((c = (*qscmp)(hp, j)) == 0) {
				qsexc(hp += es, j);
				goto loop;
E 2
I 2
	}
I 13
	swap(a, pm);
	pa = pb = a + es;
E 13
D 10
	/*
	 * With our sentinel in place, we now run the following hyper-fast
	 * insertion sort.  For each remaining element, min, from [1] to [n-1],
	 * set hi to the index of the element AFTER which this one goes.
	 * Then, do the standard insertion sort shift on a character at a time
	 * basis for each element in the frob.
	 */
	for (min = base; (hi = min += qsz) < max; ) {
		while (qcmp(hi -= qsz, min) > 0)
			/* void */;
		if ((hi += qsz) != min) {
			for (lo = min + qsz; --lo >= min; ) {
				c = *lo;
				for (i = j = lo; (j -= qsz) >= hi; i = j)
					*i = *j;
				*i = c;
E 10
I 10

D 13
	/* Standard quicksort, Knuth, Vol. 3, page 116, Algorithm Q. */
#define	didswap	n1
#define	newbot	t1
#define	replace	t2
	didswap = 0;
	for (bsv = bot;;) {
		for (; bot < mid && compar(bot, mid) <= 0; bot += size);
		while (top > mid) {
			if (compar(mid, top) <= 0) {
				top -= size;
				continue;
E 13
I 13
	pc = pd = a + (n - 1) * es;
	for (;;) {
		while (pb <= pc && (r = cmp(pb, a)) <= 0) {
			if (r == 0) {
				swap_cnt = 1;
				swap(pa, pb);
				pa += es;
E 13
E 10
E 2
			}
I 10
D 13
			newbot = bot + size;	/* value of bot after swap */
			if (bot == mid)		/* top <-> mid, mid == top */
				replace = mid = top;
			else {			/* bot <-> top */
				replace = top;
				top -= size;
E 13
I 13
			pb += es;
		}
		while (pb <= pc && (r = cmp(pc, a)) >= 0) {
			if (r == 0) {
				swap_cnt = 1;
				swap(pc, pd);
				pd -= es;
E 13
			}
D 13
			goto swap;
E 13
I 13
			pc -= es;
E 13
E 10
D 2
			if(c > 0) {
				if(i == lp) {
					qstexc(i, hp += es, j);
					i = lp += es;
					goto loop;
				}
				qsexc(i, j);
				j -= es;
				i += es;
				continue;
			}
			j -= es;
			goto loop;
E 2
		}
I 10
D 13
		if (bot == mid)
E 13
I 13
		if (pb > pc)
E 13
			break;
D 13

		/* bot <-> mid, mid == bot */
		replace = mid;
		newbot = mid = bot;		/* value of bot after swap */
		top -= size;

swap:		SWAP(bot, replace);
		bot = newbot;
		didswap = 1;
E 13
I 13
		swap(pb, pc);
		swap_cnt = 1;
		pb += es;
		pc -= es;
E 13
E 10
D 2


		if(i == lp) {
			if(lp-a >= l-hp) {
				qs1(hp+es, l);
				l = lp;
			} else {
				qs1(a, lp);
				a = hp+es;
			}
			goto start;
		}


		qstexc(j, lp -= es, i);
		j = hp -= es;
E 2
	}
D 10
}
E 10
D 13

D 2
static qsexc(i, j)
char *i, *j;
{
	register char *ri, *rj, c;
	int n;
E 2
I 2
D 10
/*
 * qst:
 * Do a quicksort
 * First, find the median element, and put that one in the first place as the
 * discriminator.  (This "median" is just the median of the first, last and
 * middle elements).  (Using this median instead of the first element is a big
 * win).  Then, the usual partitioning/swapping, followed by moving the
 * discriminator into the right place.  Then, figure out the sizes of the two
 * partions, do the smaller one recursively and the larger one via a repeat of
 * this code.  Stopping when there are less than THRESH elements in a partition
 * and cleaning up with an insertion sort (in our caller) is a huge win.
 * All data swaps are done in-line, which is space-losing but time-saving.
 * (And there are only three places where this is done).
 */
E 10
I 10
	/*
	 * Quicksort behaves badly in the presence of data which is already
	 * sorted (see Knuth, Vol. 3, page 119) going from O N lg N to O N^2.
	 * To avoid this worst case behavior, if a re-partitioning occurs
	 * without swapping any elements, it is not further partitioned and
	 * is insert sorted.  This wins big with almost sorted data sets and
	 * only loses if the data set is very strangely partitioned.  A fix
	 * for those data sets would be to return prematurely if the insertion
	 * sort routine is forced to make an excessive number of swaps, and
	 * continue the partitioning.
	 */
	if (!didswap) {
		insertion_sort(bsv, nmemb, size, compar);
E 13
I 13
	if (swap_cnt == 0) {  /* Switch to insertion sort */
		for (pm = a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0; 
			     pl -= es)
				swap(pl, pl - es);
E 13
		return;
	}
E 10
E 2

D 2
	n = qses;
	ri = i;
	rj = j;
	do {
		c = *ri;
		*ri++ = *rj;
		*rj++ = c;
	} while(--n);
}

static qstexc(i, j, k)
char *i, *j, *k;
E 2
I 2
D 10
static
qst(base, max)
	char *base, *max;
E 2
{
D 2
	register char *ri, *rj, *rk;
	int c;
	int n;
E 2
I 2
	register char c, *i, *j, *jj;
	register int ii;
	char *mid, *tmp;
	int lo, hi;
E 10
I 10
D 13
	/*
	 * Re-partition or sort as necessary.  Note that the mid element
	 * itself is correctly positioned and can be ignored.
	 */
#define	nlower	n1
#define	nupper	n2
	bot = bsv;
	nlower = (mid - bot) / size;	/* size of lower partition */
	mid += size;
	nupper = nmemb - nlower - 1;	/* size of upper partition */
E 10
E 2

D 2
	n = qses;
	ri = i;
	rj = j;
	rk = k;
	do {
		c = *ri;
		*ri++ = *rk;
		*rk++ = *rj;
		*rj++ = c;
	} while(--n);
E 2
I 2
	/*
D 10
	 * At the top here, lo is the number of characters of elements in the
	 * current partition.  (Which should be max - base).
	 * Find the median of the first, last, and middle element and make
	 * that the middle element.  Set j to largest of first and middle.
	 * If max is larger than that guy, then it's that guy, else compare
	 * max with loser of first and take larger.  Things are set up to
	 * prefer the middle, then the first in case of ties.
E 10
I 10
	 * If must call recursively, do it on the smaller partition; this
	 * bounds the stack to lg N entries.
E 10
	 */
D 10
	lo = max - base;		/* number of elements as chars */
	do	{
		mid = i = base + qsz * ((lo / qsz) >> 1);
		if (lo >= mthresh) {
			j = (qcmp((jj = base), i) > 0 ? jj : i);
			if (qcmp(j, (tmp = max - qsz)) > 0) {
				/* switch to first loser */
				j = (j == jj ? i : jj);
				if (qcmp(j, tmp) < 0)
					j = tmp;
E 10
I 10
	if (nlower > nupper) {
		if (nupper >= THRESH)
			quick_sort(mid, nupper, size, compar);
		else {
			SORT(mid, nupper);
			if (nlower < THRESH) {
				SORT(bot, nlower);
				return;
E 10
			}
D 10
			if (j != i) {
				ii = qsz;
				do	{
					c = *i;
					*i++ = *j;
					*j++ = c;
				} while (--ii);
			}
E 10
		}
D 10
		/*
		 * Semi-standard quicksort partitioning/swapping
		 */
		for (i = base, j = max - qsz; ; ) {
			while (i < mid && qcmp(i, mid) <= 0)
				i += qsz;
			while (j > mid) {
				if (qcmp(mid, j) <= 0) {
					j -= qsz;
					continue;
				}
				tmp = i + qsz;	/* value of i after swap */
				if (i == mid) {
					/* j <-> mid, new mid is j */
					mid = jj = j;
				} else {
					/* i <-> j */
					jj = j;
					j -= qsz;
				}
				goto swap;
E 10
I 10
		nmemb = nlower;
	} else {
		if (nlower >= THRESH)
			quick_sort(bot, nlower, size, compar);
		else {
			SORT(bot, nlower);
			if (nupper < THRESH) {
				SORT(mid, nupper);
				return;
E 10
			}
D 10
			if (i == mid) {
				break;
			} else {
				/* i <-> mid, new mid is i */
				jj = mid;
				tmp = mid = i;	/* value of i after swap */
				j -= qsz;
			}
		swap:
			ii = qsz;
			do	{
				c = *i;
				*i++ = *jj;
				*jj++ = c;
			} while (--ii);
			i = tmp;
E 10
		}
D 10
		/*
		 * Look at sizes of the two partitions, do the smaller
		 * one first by recursion, then do the larger one by
		 * making sure lo is its size, base and max are update
		 * correctly, and branching back.  But only repeat
		 * (recursively or by branching) if the partition is
		 * of at least size THRESH.
		 */
		i = (j = mid) + qsz;
		if ((lo = j - base) <= (hi = max - i)) {
			if (lo >= thresh)
				qst(base, j);
			base = i;
			lo = hi;
		} else {
			if (hi >= thresh)
				qst(i, max);
			max = j;
		}
	} while (lo >= thresh);
E 10
I 10
		bot = mid;
		nmemb = nupper;
E 13
I 13
	pn = a + n * es;
	r = min(pa - (char *)a, pb - pa);
	vecswap(a, pb - r, r);
	r = min(pd - pc, pn - pd - es);
	vecswap(pb, pn - r, r);
D 15
	if ((r = pb - pa) > es) {
		/*
		 * To decrease the stack space we iterate here rather than 
		 * recurse.
		 */
E 15
I 15
	if ((r = pb - pa) > es)
		qsort(a, r / es, es, cmp);
	if ((r = pd - pc) > es) { 
		/* Iterate rather than recurse to save stack space */
		a = pn - r;
E 15
		n = r / es;
		goto loop;
E 13
	}
D 13
	goto partition;
	/* NOTREACHED */
E 13
I 13
D 15
	if ((r = pd - pc) > es)
D 14
		nqsort(pn - r, r / es, es, cmp);
E 14
I 14
		qsort(pn - r, r / es, es, cmp);
E 15
I 15
/*		qsort(pn - r, r / es, es, cmp);*/
E 15
E 14
E 13
}
D 13

static void
insertion_sort(bot, nmemb, size, compar)
	char *bot;
	register int size;
	int nmemb, (*compar)();
{
	register int cnt;
	register u_char ch;
	register char *s1, *s2, *t1, *t2, *top;

	/*
	 * A simple insertion sort (see Knuth, Vol. 3, page 81, Algorithm
	 * S).  Insertion sort has the same worst case as most simple sorts
	 * (O N^2).  It gets used here because it is (O N) in the case of
	 * sorted data.
	 */
	top = bot + nmemb * size;
	for (t1 = bot + size; t1 < top;) {
		for (t2 = t1; (t2 -= size) >= bot && compar(t1, t2) < 0;);
		if (t1 != (t2 += size)) {
			/* Bubble bytes up through each element. */
			for (cnt = size; cnt--; ++t1) {
				ch = *t1;
				for (s1 = s2 = t1; (s2 -= size) >= t2; s1 = s2)
					*s1 = *s2;
				*s1 = ch;
			}
		} else
			t1 += size;
	}
E 10
E 2
}
E 13
I 13
D 16
	
E 16
E 13
E 1
