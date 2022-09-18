h55935
s 00002/00002/00290
d D 8.2 95/04/28 15:23:14 bostic 17 16
c name pollution; From: Donn Seeley <donn@BSDI.COM>
e
s 00002/00002/00290
d D 8.1 93/06/04 13:07:55 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00289
d D 5.15 92/08/20 14:05:05 bostic 15 14
c inline the simple sort function
e
s 00011/00012/00280
d D 5.14 92/07/01 08:59:25 bostic 14 13
c fix what I broken, minor reformatting, comments from Peter
e
s 00237/00238/00055
d D 5.13 92/06/30 18:23:13 bostic 13 12
c new versions from Peter McIlroy, add sradixsort(3)
e
s 00001/00000/00292
d D 5.12 92/01/14 19:36:55 bostic 12 11
c init the pointer if not passed the array of weightss
e
s 00099/00065/00193
d D 5.11 91/11/13 17:20:58 bostic 11 10
c Peter McIlroy's modifications to do reverse sorting for speed;
c also bounding of the stack is rigorous and different!
e
s 00003/00007/00255
d D 5.10 91/09/26 13:27:54 bostic 10 9
c Dan Bernstein's fix to allow INT_MAX nmemb
e
s 00003/00000/00259
d D 5.9 91/08/17 08:48:13 bostic 9 8
c add contrib line for Dan Bernstein
e
s 00001/00005/00258
d D 5.8 91/07/23 12:37:29 bostic 8 7
c make endbyte parameter a u_int so ANSI doesn't confuse things
e
s 00019/00008/00244
d D 5.7 91/02/23 22:56:40 donn 7 6
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00037/00030/00215
d D 5.6 91/01/13 11:58:41 bostic 6 5
c make SHELLSORT a subroutine -- it's a lot cleaner, and RISC's don't care.
e
s 00001/00001/00244
d D 5.5 90/12/14 11:00:39 bostic 5 4
c don't bother storing a temp value
e
s 00026/00025/00218
d D 5.4 90/10/29 10:22:46 bostic 4 3
c NCHARS -> NBUCKETS; redo stack bounding explanation;
c off-by-one in the stack bounding; fix max bucket selection loop
e
s 00020/00025/00224
d D 5.3 90/10/13 14:04:23 bostic 3 2
c no real changes; hopefully make the stack explanation clearer
e
s 00084/00054/00165
d D 5.2 90/10/12 21:53:40 bostic 2 1
c bound the stack correctly
e
s 00220/00000/00000
d D 5.1 90/10/01 22:07:21 bostic 1 0
c date and time created 90/10/01 22:07:21 by bostic
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
I 9
 * This code is derived from software contributed to Berkeley by
D 13
 * Dan Bernstein at New York University.
E 13
I 13
 * Peter McIlroy and by Dan Bernstein at New York University, 
E 13
 *
E 9
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 13
/*
 * Radixsort routines.
 * 
 * Program r_sort_a() is unstable but uses O(logN) extra memory for a stack.
 * Use radixsort(a, n, trace, endchar) for this case.
 * 
 * For stable sorting (using N extra pointers) use sradixsort(), which calls
 * r_sort_b().
 * 
 * For a description of this code, see D. McIlroy, P. McIlroy, K. Bostic,
 * "Engineering Radix Sort".
 */

E 13
#include <sys/types.h>
D 2
#include <sys/errno.h>
E 2
D 13
#include <limits.h>
E 13
#include <stdlib.h>
#include <stddef.h>
I 7
D 13
#include <string.h>
E 13
I 11
#include <errno.h>
E 11
E 7

I 11
D 13
static void shellsort __P((const u_char **, int, int, const u_char *, int));
E 13
I 13
typedef struct {
	const u_char **sa;
	int sn, si;
} stack;
E 13

E 11
D 4
#define	NCHARS	(UCHAR_MAX + 1)

E 4
D 13
/*
D 2
 * shellsort (diminishing increment sort) from Data Structures and
E 2
I 2
D 6
 * Shellsort (diminishing increment sort) from Data Structures and
E 2
 * Algorithms, Aho, Hopcraft and Ullman, 1983 Edition, page 290;
 * see also Knuth Vol. 3, page 84.  The increments are selected from
 * formula (8), page 95.  Roughly O(N^3/2).
 *
E 6
 * __rspartition is the cutoff point for a further partitioning instead
 * of a shellsort.  If it changes check __rsshell_increments.  Both of
D 6
 * these are exported, as the best values are data dependent.  Unrolling
 * this loop has not proven worthwhile.
E 6
I 6
 * these are exported, as the best values are data dependent.
E 6
 */
D 11
#define	NPARTITION	40
E 11
I 11
#define	NPARTITION	30
E 13
I 13
D 15
static void simplesort __P((const u_char **, int, int, const u_char *, u_int));
E 15
I 15
static inline void simplesort
	    __P((const u_char **, int, int, const u_char *, u_int));
E 15
static void r_sort_a __P((const u_char **, int, int, const u_char *, u_int));
static void r_sort_b __P((const u_char **,
	    const u_char **, int, int, const u_char *, u_int));
E 13

E 11
D 13
int __rspartition = NPARTITION;
int __rsshell_increments[] = { 4, 1, 0, 0, 0, 0, 0, 0 };
E 13
I 13
#define	THRESHOLD	20		/* Divert to simplesort(). */
#define	SIZE		512		/* Default stack size. */
E 13
D 6
#define SHELLSORT { \
	register u_char ch, *s1, *s2; \
	register int incr, *incrp; \
	for (incrp = __rsshell_increments; incr = *incrp++;) \
		for (t1 = incr; t1 < nmemb; ++t1) \
			for (t2 = t1 - incr; t2 >= 0;) { \
				s1 = p[t2] + indx; \
				s2 = p[t2 + incr] + indx; \
				while ((ch = tr[*s1++]) == tr[*s2] && ch) \
					++s2; \
				if (ch > tr[*s2]) { \
					s1 = p[t2]; \
					p[t2] = p[t2 + incr]; \
					p[t2 + incr] = s1; \
					t2 -= incr; \
				} else \
					break; \
			} \
}
E 6

D 13
/*
D 2
 * stack points to context structures.  Each structure defines a
 * scheduled partitioning.  Radixsort exits when the stack is empty.
E 2
I 2
 * Stackp points to context structures, where each structure schedules a
 * partitioning.  Radixsort exits when the stack is empty.
E 2
 *
D 2
 * The stack size is data dependent, and guessing is probably not
 * worthwhile.  The initial stack fits in 1K with four bytes left over
 * for malloc.  The initial size is exported, as the best value is
 * data, and possibly, system, dependent.
E 2
I 2
D 3
 * If the buckets are placed on the stack randomly, the worst case is when:
E 3
I 3
 * If the buckets are placed on the stack randomly, the worst case is when
D 4
 * all the buckets but one contain (NPARTITION + 1) elements and the bucket
E 4
I 4
D 11
 * all the buckets but one contain (npartitions + 1) elements and the bucket
E 11
I 11
 * all the buckets but one contain (__rspartition + 1) elements and the bucket
E 11
E 4
 * pushed on the stack last contains the rest of the elements.  In this case,
 * stack growth is bounded by:
E 3
 *
D 3
 *	(nbuckets - 1) contain (npartitions + 1) elements, with the last
 *	bucket containing (nelements - ((npartitions + 1) * (nbuckets - 1))
 *	keys.
 *
 * In this case, stack growth is bounded by:
 *
E 3
D 4
 *	(nelements / (npartitions + 1)) - 1
E 4
I 4
D 11
 *	limit = (nelements / (npartitions + 1)) - 1;
E 11
I 11
 *	limit = (nelements / (__rspartitions + 1)) - 1;
E 11
E 4
 *
D 3
 * Therefore, we force the largest bucket to be pushed on the stack first.
 * Then the worst case is when:
E 3
I 3
D 4
 * This is a very large number.  By forcing the largest bucket to be pushed
 * on the stack first the worst case is when all but two buckets each contain
 * (NPARTITION + 1) elements, with the remaining elements split equally between
 * the first and last buckets pushed on the stack.  In this case, stack growth
 * is bounded when:
E 4
I 4
D 11
 * This is a very large number, 52,377,648 for the maximum 32-bit signed int.
E 11
I 11
 * This is a very large number, 102,261,125 for the maximum 32-bit signed
 * integer if NPARTITION is 20.
E 11
E 4
E 3
 *
I 4
 * By forcing the largest bucket to be pushed on the stack first, the worst
D 11
 * case is when all but two buckets each contain (npartitions + 1) elements,
E 11
I 11
 * case is when all but two buckets each contain (__rspartition + 1) elements,
E 11
 * with the remaining elements split equally between the first and last
D 11
 * buckets pushed on the stack.  In this case, stack growth is bounded when:
E 11
I 11
 * buckets pushed on the stack.  In this case, stack growth is bounded by
 * the recurrence relation:
E 11
 *
E 4
D 3
 * 	(nbuckets - 2) buckets contain (npartitions + 1) elements, with
 *	the remaining elements split equally between the first bucket
 *	pushed and the last bucket pushed.
 *
 * In this case, stack growth is bounded when:
 *	
 *	for (partition_cnt = 0; nelements > npartitions; ++partition_cnt) 
E 3
I 3
D 11
 *	for (partition_cnt = 0; nelements > npartitions; ++partition_cnt)
E 3
 *		nelements =
 *		    (nelements - (npartitions + 1) * (nbuckets - 2)) / 2;
E 11
I 11
 * nelements_max[1] = (NBINS-1) * (__rspartition + 1);
 * nelements_max[i] = (NBINS-3) * (__rspartition + 1) + 2 * npartitions[i-1];
 * which resolves to:
 * nelements_max[i] = ((NBINS-2) * (2^i - 1) + 1) * (__rspartitions + 1),
 *
 * which yields, for a given nelements,
 *
 * i = ceil(log2((((nelements / (__rspartition + 1)) - 1) / (NBINS - 2)) + 1));
 *
E 11
 * The bound is:
 *
D 11
 *	limit = partition_cnt * (nbuckets - 1);
E 11
I 11
 *	limit = i * (NBINS - 1);
E 11
I 3
 *
D 4
 * This is a much smaller number.
E 4
I 4
D 11
 * This is a much smaller number, 4590 for the maximum 32-bit signed int.
E 11
I 11
 * This is a much smaller number, 4845 for the maximum 32-bit signed int.
E 11
E 4
E 3
E 2
 */
I 4
#define	NBUCKETS	(UCHAR_MAX + 1)
E 13
I 13
#define SETUP {								\
	if (tab == NULL) {						\
		tr = tr0;						\
		for (c = 0; c < endch; c++)				\
			tr0[c] = c + 1;					\
		tr0[c] = 0;						\
		for (c++; c < 256; c++)					\
			tr0[c] = c;					\
		endch = 0;						\
	} else {							\
		endch = tab[endch];					\
		tr = tab;						\
		if (endch != 0 && endch != 255) {			\
			errno = EINVAL;					\
			return (-1);					\
		}							\
	}								\
}
E 13

E 4
D 13
typedef struct _stack {
D 7
	u_char **bot;
E 7
I 7
	const u_char **bot;
E 7
	int indx, nmemb;
} CONTEXT;
E 13
I 13
int
radixsort(a, n, tab, endch)
	const u_char **a, *tab;
	int n;
	u_int endch;
{
	const u_char *tr;
	int c;
	u_char tr0[256];
E 13

D 2
int __radix_stacksize = (1024 - 4) / sizeof(CONTEXT);
E 2
D 13
#define	STACKPUSH { \
D 2
	if (stackp == estack) { \
		t1 = stackp - stack; \
		stackp = stack; \
		if (!(stack = (CONTEXT *)realloc((char *)stack, \
		    (__radix_stacksize *= 2) * sizeof(CONTEXT)))) { \
			t1 = errno; \
			free((char *)l2); \
			if (stackp) \
				free((char *)stackp); \
			errno = t1; \
			return(-1); \
		} \
		stackp = stack + t1; \
		estack = stack + __radix_stacksize; \
	} \
E 2
	stackp->bot = p; \
	stackp->nmemb = nmemb; \
	stackp->indx = indx; \
	++stackp; \
E 13
I 13
	SETUP;
	r_sort_a(a, n, 0, tr, endch);
	return (0);
E 13
}
D 3

E 3
D 13
#define	STACKPOP { \
	if (stackp == stack) \
		break; \
	--stackp; \
	bot = stackp->bot; \
	nmemb = stackp->nmemb; \
	indx = stackp->indx; \
}
D 11

E 11
/*
 * A variant of MSD radix sorting; see Knuth Vol. 3, page 177, and 5.2.5,
D 2
 * Ex. 10 and 12.  Also, "Three Partition Refinement Algorithms, Paige and
 * Tarjan, SIAM J. Comput. Vol. 16, No. 6, December 1987.
E 2
I 2
 * Ex. 10 and 12.  Also, "Three Partition Refinement Algorithms, Paige
 * and Tarjan, SIAM J. Comput. Vol. 16, No. 6, December 1987.
E 2
 *
D 2
 * This uses a simple sort as soon as a bucket crosses a cutoff point, rather
 * than sorting the entire list after partitioning is finished.
E 2
I 2
 * This uses a simple sort as soon as a bucket crosses a cutoff point,
 * rather than sorting the entire list after partitioning is finished.
 * This should be an advantage.
E 2
 *
D 2
 * This is pure MSD instead of LSD of some number of MSD, switching to the
 * simple sort as soon as possible.  Takes linear time relative to the number
 * of bytes in the strings.
E 2
I 2
 * This is pure MSD instead of LSD of some number of MSD, switching to
 * the simple sort as soon as possible.  Takes linear time relative to
 * the number of bytes in the strings.
E 2
 */
E 13
I 13

E 13
I 7
int
D 8
#if __STDC__
radixsort(const u_char **l1, int nmemb, const u_char *tab, u_char endbyte)
#else
E 8
E 7
D 13
radixsort(l1, nmemb, tab, endbyte)
D 7
	u_char **l1, *tab, endbyte;
E 7
I 7
	const u_char **l1;
E 7
	register int nmemb;
I 7
	const u_char *tab;
D 8
	u_char endbyte;
#endif
E 8
I 8
	u_int endbyte;
E 13
I 13
sradixsort(a, n, tab, endch)
	const u_char **a, *tab;
	int n;
	u_int endch;
E 13
E 8
E 7
{
D 11
	register int i, indx, t1, t2;
D 7
	register u_char **l2, **p, **bot, *tr;
E 7
I 7
	register const u_char **l2;
	register const u_char **p;
	register const u_char **bot;
	register const u_char *tr;
E 11
I 11
D 13
	register int *cpos, *first, *last, i, indx;
	register const u_char **bot, **l2, **p, *tr;
E 11
E 7
D 2
	CONTEXT *estack, *stack, *stackp;
	int c[NCHARS + 1];
E 2
I 2
	CONTEXT *stack, *stackp;
D 4
	int c[NCHARS + 1], max;
E 2
	u_char ltab[NCHARS];
E 4
I 4
D 11
	int c[NBUCKETS + 1], max;
E 11
I 11
	int c[NBUCKETS + 1], *max, *recd, t1, t2;
E 11
	u_char ltab[NBUCKETS];
E 13
I 13
	const u_char *tr, **ta;
	int c;
	u_char tr0[256];
E 13
I 6
D 11
	static void shellsort();
E 11
E 6
E 4

D 13
	if (nmemb <= 1)
D 11
		return(0);
E 11
I 11
		return (0);
E 11

I 2
D 3
	/* 
E 3
I 3
	/*
E 3
	 * T1 is the constant part of the equation, the number of elements
D 10
	 * represented on the stack between the top and bottom entries.
D 3
	 * Don't round as the divide by 2 rounds down (correct for value
	 * being subtracted).  The nelem value has to be rounded up before
	 * each divide because we want an upper bound.
	 */	
E 3
I 3
	 * It doesn't get rounded as the divide by 2 rounds down (correct
	 * for a value being subtracted).  T2, the nelem value, has to be
	 * rounded up before each divide because we want an upper bound;
	 * this could overflow if nmemb is the maximum int.
E 10
I 10
D 11
	 * on the stack other than the two largest, worst-case buckets.
E 11
I 11
	 * represented on the stack between the top and bottom entries.
E 11
E 10
	 */
E 3
D 4
	t1 = ((__rspartition + 1) * (UCHAR_MAX - 2)) >> 1;
D 3
	for (i = 0, t2 = nmemb; t2 > __rspartition; i += UCHAR_MAX - 1) 
E 3
I 3
	for (i = 0, t2 = nmemb; t2 > __rspartition; i += UCHAR_MAX - 1)
E 4
I 4
D 10
	t1 = ((__rspartition + 1) * (NBUCKETS - 2)) >> 1;
E 10
I 10
D 11
	t1 = (__rspartition + 1) * (NBUCKETS - 2);
E 10
	for (i = 0, t2 = nmemb; t2 > __rspartition; i += NBUCKETS - 1)
E 4
E 3
D 5
		t2 = (++t2 >> 1) - t1;
E 5
I 5
D 10
		t2 = ((t2 + 1) >> 1) - t1;
E 10
I 10
		t2 = (t2 - t1) >> 1;
E 11
I 11
	if (nmemb > __rspartition)
		t1 = (nmemb / (__rspartition + 1) - 1) / (NBUCKETS - 2) + 1;
	else
		t1 = 0;
	for (i = 0; t1; ++i)
		t1 /= 2;
E 11
E 10
E 5
	if (i) {
D 3
		if (!(stack = stackp =
		    (CONTEXT *)malloc(i * sizeof(CONTEXT)))) 
E 3
I 3
D 11
		if (!(stack = stackp = (CONTEXT *)malloc(i * sizeof(CONTEXT))))
E 3
			return(-1);
	} else
E 11
I 11
		i *= NBUCKETS - 1;
		if ((stack = stackp = malloc(i * sizeof(CONTEXT))) == NULL)
E 13
I 13
	SETUP;
	if (n < THRESHOLD)
		simplesort(a, n, 0, tr, endch);
	else {
		if ((ta = malloc(n * sizeof(a))) == NULL)
E 13
			return (-1);
I 13
		r_sort_b(a, ta, n, 0, tr, endch);
		free(ta);
E 13
	}
D 13
	else
E 11
		stack = stackp = NULL;
E 13
I 13
	return (0);
}
E 13

E 2
D 13
	/*
D 2
	 * there are two arrays, one provided by the user (l1), and the
E 2
I 2
D 11
	 * There are two arrays, one provided by the user (l1), and the
E 2
	 * temporary one (l2).  The data is sorted to the temporary stack,
	 * and then copied back.  The speedup of using index to determine
	 * which stack the data is on and simply swapping stacks back and
	 * forth, thus avoiding the copy every iteration, turns out to not
E 11
I 11
	 * There are two arrays, l1 and l2.  The data is sorted into the temp
	 * stack, and then copied back.  The speedup of using the index to
	 * determine which stack the data is on and simply swapping stacks back
	 * and forth, thus avoiding the copy every iteration, turns out to not
E 11
	 * be any faster than the current implementation.
	 */
D 7
	if (!(l2 = (u_char **)malloc(sizeof(u_char *) * nmemb)))
E 7
I 7
D 11
	if (!(l2 = (const u_char **)malloc(sizeof(u_char *) * nmemb)))
E 7
		return(-1);

E 11
I 11
	if ((l2 = malloc(nmemb * sizeof(u_char **))) == NULL)
		return (-1);
E 11
D 2
	/* initialize stack */
	stack = stackp = estack = NULL;

E 2
	/*
D 2
	 * tr references a table of sort weights; multiple entries may
E 2
I 2
	 * Tr references a table of sort weights; multiple entries may
E 2
	 * map to the same weight; EOS char must have the lowest weight.
	 */
D 11
	if (tab)
E 11
I 11
	if (tab) {
E 11
		tr = tab;
I 11
		recd = c + tr[endbyte];
		if (recd != c && recd != c + NBUCKETS - 1) {
			errno = EINVAL;
			return (-1);
		}
	}
E 11
	else {
D 7
		tr = ltab;
E 7
		for (t1 = 0, t2 = endbyte; t1 < t2; ++t1)
D 7
			tr[t1] = t1 + 1;
		tr[t2] = 0;
E 7
I 7
			ltab[t1] = t1 + 1;
		ltab[t2] = 0;
E 7
D 4
		for (t1 = endbyte + 1; t1 < NCHARS; ++t1)
E 4
I 4
		for (t1 = endbyte + 1; t1 < NBUCKETS; ++t1)
E 4
D 7
			tr[t1] = t1;
E 7
I 7
			ltab[t1] = t1;
		tr = ltab;
I 12
		recd = c + tr[endbyte];
E 12
E 7
	}
I 11
	last = c + NBUCKETS;
	first = c;
	endbyte = tr[endbyte];
E 13
I 13
#define empty(s)	(s >= sp)
#define pop(a, n, i)	a = (--sp)->sa, n = sp->sn, i = sp->si
#define push(a, n, i)	sp->sa = a, sp->sn = n, (sp++)->si = i
#define swap(a, b, t)	t = a, a = b, b = t
E 13
E 11

D 2
	/* first sort is entire stack */
E 2
I 2
D 11
	/* First sort is entire stack */
E 11
I 11
D 13
	/* First sort is entire stack. */
E 11
E 2
	bot = l1;
	indx = 0;
E 13
I 13
/* Unstable, in-place sort. */
D 17
void
E 17
I 17
static void
E 17
r_sort_a(a, n, i, tr, endch)
	const u_char **a;
	int n, i;
	const u_char *tr;
	u_int endch;
{
	static int count[256], nc, bmin;
	register int c;
	register const u_char **ak, *r;
	stack s[SIZE], *sp, *sp0, *sp1, temp;
	int *cp, bigc;
	const u_char **an, *t, **aj, **top[256];
E 13

D 13
	for (;;) {
D 2
		/* clear bucket count array */
E 2
I 2
		/* Clear bucket count array */
E 2
D 11
		bzero((char *)c, sizeof(c));
E 11
I 11
		bzero(first, sizeof(c[0]) * (last - first + 1));
		*recd = 0;
E 13
I 13
D 14
	sp = s;
E 13
E 11

E 14
D 13
		/*
D 2
		 * compute number of items that sort to the same bucket
E 2
I 2
		 * Compute number of items that sort to the same bucket
E 2
		 * for this index.
		 */
D 6
		for (p = bot, i = nmemb; i--;)
E 6
I 6
D 11
		for (p = bot, i = nmemb; --i >= 0;)
E 6
			++c[tr[(*p++)[indx]]];
E 11
I 11
		first = c + NBUCKETS - 1;
		last = c;
		for (p = bot, i = nmemb; --i >= 0;) {
			++*(cpos = c + tr[(*p++)[indx]]);
			if (cpos > last && cpos != recd)
				last = cpos;
			if (cpos < first && cpos != recd)
				first = cpos;
E 13
I 13
	/* Set up stack. */
I 14
	sp = s;
E 14
	push(a, n, i);
	while (!empty(s)) {
		pop(a, n, i);
		if (n < THRESHOLD) {
			simplesort(a, n, i, tr, endch);
			continue;
E 13
		}
D 13
		++last;
E 13
I 13
		an = a + n;
E 13
E 11

D 13
		/*
D 2
		 * sum the number of characters into c, dividing the temp
E 2
I 2
		 * Sum the number of characters into c, dividing the temp
E 2
		 * stack into the right number of buckets for this bucket,
		 * this index.  C contains the cumulative total of keys
D 11
		 * before and included in this bucket, and will later be
D 4
		 * used as an index to the bucket.  c[NCHARS] contains
E 4
I 4
		 * used as an index to the bucket.  c[NBUCKETS] contains
E 11
I 11
		 * before and included in this bucket, and will later be used
		 * as an index to the bucket.  c[NBUCKETS] (or *last) contains
E 11
E 4
		 * the total number of elements, for determining how many
D 2
		 * elements the last bucket contains.
E 2
I 2
		 * elements the last bucket contains.  At the same time
D 4
		 * find the largest bucket so it gets handled first.
E 4
I 4
		 * find the largest bucket so it gets pushed first.
E 4
E 2
		 */
D 2
		for (i = 1; i <= NCHARS; ++i)
			c[i] += c[i - 1];
E 2
I 2
D 4
		for (i = 1, t2 = -1; i <= NCHARS; ++i) {
			if ((t1 = c[i - 1]) > t2) {
				t2 = t1;
E 4
I 4
D 11
		for (i = max = t1 = 0, t2 = __rspartition; i <= NBUCKETS; ++i) {
			if (c[i] > t2) {
				t2 = c[i];
E 4
				max = i;
E 11
I 11
		t1 = (c == recd) ? c[0] : 0;
		t2 = __rspartition;
		for (i = last - (cpos = max = first); i-- >= 0;) {
			if (*cpos > t2) {
				t2 = *cpos;
				max = cpos;
E 13
I 13
		/* Make character histogram. */
		if (nc == 0) {
			bmin = 255;	/* First occupied bin, excluding eos. */
			for (ak = a; ak < an;) {
				c = tr[(*ak++)[i]];
				if (++count[c] == 1 && c != endch) {
					if (c < bmin)
						bmin = c;
					nc++;
				}
E 13
E 11
			}
D 4
			c[i] += t1;
E 4
I 4
D 11
			t1 = c[i] += t1;
E 11
I 11
D 13
			t1 = *cpos++ += t1;
E 13
I 13
			if (sp + nc > s + SIZE) {	/* Get more stack. */
				r_sort_a(a, n, i, tr, endch);
				continue;
			}
E 13
E 11
E 4
		}
I 11
D 13
		if (c != recd)
			*recd += t1;
E 13
E 11
E 2

		/*
D 2
		 * partition the elements into buckets; c decrements
E 2
I 2
D 4
		 * Partition the elements into buckets; c decrements
E 2
		 * through the bucket, and ends up pointing to the
		 * first element of the bucket.
E 4
I 4
D 13
		 * Partition the elements into buckets; c decrements through
		 * the bucket, and ends up pointing to the first element of
		 * the bucket.
E 13
I 13
		 * Set top[]; push incompletely sorted bins onto stack.
		 * top[] = pointers to last out-of-place element in bins.
		 * count[] = counts of elements in bins.
		 * Before permuting: top[c-1] + count[c] = top[c];
		 * during deal: top[c] counts down to top[c-1].
E 13
E 4
		 */
D 6
		for (i = nmemb; i--;) {
E 6
I 6
D 13
		for (i = nmemb; --i >= 0;) {
E 6
			--p;
			l2[--c[tr[(*p)[indx]]]] = *p;
E 13
I 13
		sp0 = sp1 = sp;		/* Stack position of biggest bin. */
		bigc = 2;		/* Size of biggest bin. */
		if (endch == 0)		/* Special case: set top[eos]. */
			top[0] = ak = a + count[0];
		else {
			ak = a;
			top[255] = an;
E 13
		}
I 13
		for (cp = count + bmin; nc > 0; cp++) {
D 14
			while (*cp == 0)
E 14
I 14
			while (*cp == 0)	/* Find next non-empty pile. */
E 14
				cp++;
			if (*cp > 1) {
				if (*cp > bigc) {
					bigc = *cp;
					sp1 = sp;
				}
				push(ak, *cp, i+1);
			}
			top[cp-count] = ak += *cp;
			nc--;
		}
		swap(*sp0, *sp1, temp);	/* Play it safe -- biggest bin last. */
E 13

D 2
		/* copy the partitioned elements back to user stack */
E 2
I 2
D 13
		/* Copy the partitioned elements back to user stack */
E 2
		bcopy(l2, bot, nmemb * sizeof(u_char *));

		++indx;
E 13
		/*
D 2
		 * sort buckets as necessary; don't sort c[0], it's the
E 2
I 2
D 11
		 * Sort buckets as necessary; don't sort c[0], it's the
E 2
		 * EOS character bucket, and nothing can follow EOS.
E 11
I 11
D 13
		 * Sort buckets as necessary; don't sort the EOS character
		 * bucket c[endbyte] since it is already sorted.  *max is
		 * pushed first.
E 13
I 13
		 * Permute misplacements home.  Already home: everything
		 * before aj, and in bin[c], items from top[c] on.
		 * Inner loop:
		 *	r = next element to put in place;
		 *	ak = top[r[i]] = location to put the next element.
		 *	aj = bottom of 1st disordered bin.
		 * Outer loop:
		 *	Once the 1st disordered bin is done, ie. aj >= ak,
		 *	aj<-aj + count[c] connects the bins in a linked list;
		 *	reset count[c].
E 13
E 11
		 */
D 2
		for (i = NCHARS - 1; i; i--) {
E 2
I 2
D 11
		for (i = max; i; --i) {
E 2
			if ((nmemb = c[i + 1] - (t1 = c[i])) < 2)
E 11
I 11
D 13
		for (i = last - (cpos = max); --i >= 0;) {
			if ((nmemb =  *(cpos+1) - (t1 = *cpos++)) < 2)
E 11
				continue;
			p = bot + t1;
			if (nmemb > __rspartition)
				STACKPUSH
			else
D 6
				SHELLSORT
E 6
I 6
D 11
				shellsort(p, indx, nmemb, tr);
E 11
I 11
				shellsort(p, indx, nmemb, tr, endbyte);
E 13
I 13
		for (aj = a; aj < an;  *aj = r, aj += count[c], count[c] = 0)
			for (r = *aj;  aj < (ak = --top[c = tr[r[i]]]);)
				swap(*ak, r, t);
	}
}

/* Stable sort, requiring additional memory. */
D 17
void
E 17
I 17
static void
E 17
r_sort_b(a, ta, n, i, tr, endch)
	const u_char **a, **ta;
	int n, i;
	const u_char *tr;
	u_int endch;
{
	static int count[256], nc, bmin;
	register int c;
	register const u_char **ak, **ai;
	stack s[512], *sp, *sp0, *sp1, temp;
	const u_char **top[256];
	int *cp, bigc;

	sp = s;
D 14
	/* Set up stack. */
E 14
	push(a, n, i);
	while (!empty(s)) {
		pop(a, n, i);
		if (n < THRESHOLD) {
			simplesort(a, n, i, tr, endch);
			continue;
E 13
E 11
E 6
		}
D 2
		/* break out when stack is empty */
E 2
I 2
D 4
		for (i = max + 1; i < NCHARS; ++i) {
E 4
I 4
D 11
		for (i = max + 1; i < NBUCKETS; ++i) {
E 4
			if ((nmemb = c[i + 1] - (t1 = c[i])) < 2)
E 11
I 11
D 13
		for (i = max - (cpos = first); --i >= 0;) {
			if ((nmemb = *(cpos + 1) - (t1 = *cpos++)) < 2)
E 13
I 13

		if (nc == 0) {
			bmin = 255;
			for (ak = a + n; --ak >= a;) {
				c = tr[(*ak)[i]];
				if (++count[c] == 1 && c != endch) {
					if (c < bmin)
						bmin = c;
					nc++;
				}
			}
			if (sp + nc > s + SIZE) {
				r_sort_b(a, ta, n, i, tr, endch);
E 13
E 11
				continue;
D 13
			p = bot + t1;
			if (nmemb > __rspartition)
				STACKPUSH
			else
D 6
				SHELLSORT
E 6
I 6
D 11
				shellsort(p, indx, nmemb, tr);
E 11
I 11
				shellsort(p, indx, nmemb, tr, endbyte);
E 13
I 13
			}
E 13
E 11
E 6
		}
D 11
		/* Break out when stack is empty */
E 11
I 11
D 13
		/* Break out when stack is empty. */
E 11
E 2
		STACKPOP
E 13
I 13

D 14
		sp0 = sp1 = sp;		/* Stack position of biggest bin. */
		bigc = 2;		/* Size of biggest bin. */
		if (endch == 0) {	/* Special case: set top[eos]. */
E 14
I 14
		sp0 = sp1 = sp;
		bigc = 2;
		if (endch == 0) {
E 14
			top[0] = ak = a + count[0];
			count[0] = 0;
		} else {
			ak = a;
			top[255] = a + n;
			count[255] = 0;
		}
D 14
		for (cp = count + bmin; nc-- > 0; cp++) {
E 14
I 14
		for (cp = count + bmin; nc > 0; cp++) {
E 14
			while (*cp == 0)
				cp++;
			if ((c = *cp) > 1) {
				if (c > bigc) {
					bigc = c;
					sp1 = sp;
				}
				push(ak, c, i+1);
			}
			top[cp-count] = ak += c;
D 14
			*cp = 0;
E 14
I 14
			*cp = 0;			/* Reset count[]. */
			nc--;
E 14
		}
D 14
		swap(*sp0, *sp1, temp);	/* Play it safe -- biggest bin last. */
E 14
I 14
		swap(*sp0, *sp1, temp);
E 14

D 14
		for (ak = ta + n, ai = a+n; ak > ta;)
E 14
I 14
		for (ak = ta + n, ai = a+n; ak > ta;)	/* Copy to temp. */
E 14
			*--ak = *--ai;
D 14
		for (ak = ta+n; --ak >= ta;)
E 14
I 14
		for (ak = ta+n; --ak >= ta;)		/* Deal to piles. */
E 14
			*--top[tr[(*ak)[i]]] = *ak;
E 13
	}
D 11

	free((char *)l2);
	free((char *)stack);
D 2
#ifdef STATS
	(void)fprintf(stderr, "max stack %u.\n", __radix_stacksize);
#endif
E 2
	return(0);
E 11
I 11
D 13
	free(stack);
	free(l2);
	return (0);
E 13
E 11
I 6
}
D 13

/*
 * Shellsort (diminishing increment sort) from Data Structures and
 * Algorithms, Aho, Hopcraft and Ullman, 1983 Edition, page 290;
 * see also Knuth Vol. 3, page 84.  The increments are selected from
 * formula (8), page 95.  Roughly O(N^3/2).
 */
E 13
I 13
		
E 13
D 15
static void
E 15
I 15
static inline void
E 15
D 11
shellsort(p, indx, nmemb, tr)
	register u_char **p, *tr;
	register int indx, nmemb;
E 11
I 11
D 13
shellsort(p, indx, nmemb, tr, recd)
	register const u_char **p, *tr;
	register int indx, nmemb, recd;
E 13
I 13
simplesort(a, n, b, tr, endch)	/* insertion sort */
	register const u_char **a;
	int n, b;
	register const u_char *tr;
	u_int endch;
E 13
E 11
{
D 11
	register u_char ch, *s1, *s2;
E 11
I 11
D 13
	register const u_char *s1, *s2;
E 13
	register u_char ch;
E 11
D 13
	register int incr, *incrp, t1, t2;
E 13
I 13
	const u_char  **ak, **ai, *s, *t;
E 13

D 13
	for (incrp = __rsshell_increments; incr = *incrp++;)
		for (t1 = incr; t1 < nmemb; ++t1)
			for (t2 = t1 - incr; t2 >= 0;) {
				s1 = p[t2] + indx;
				s2 = p[t2 + incr] + indx;
D 11
				while ((ch = tr[*s1++]) == tr[*s2] && ch)
E 11
I 11
				while ((ch = tr[*s1++]) == tr[*s2] &&
				    (ch != recd))
E 11
					++s2;
				if (ch > tr[*s2]) {
					s1 = p[t2];
					p[t2] = p[t2 + incr];
					p[t2 + incr] = s1;
					t2 -= incr;
				} else
E 13
I 13
	for (ak = a+1; --n >= 1; ak++)
		for (ai = ak; ai > a; ai--) {
			for (s = ai[0] + b, t = ai[-1] + b;
			    (ch = tr[*s]) != endch; s++, t++)
				if (ch != tr[*t])
E 13
					break;
D 13
			}
E 13
I 13
			if (ch >= tr[*t])
				break;
			swap(ai[0], ai[-1], s);
		}
E 13
E 6
}
E 1
