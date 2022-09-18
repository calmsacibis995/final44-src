h23885
s 00002/00002/00871
d D 8.1 93/06/06 22:28:17 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00013/00853
d D 3.8 92/11/10 11:49:56 edward 8 7
c checkpointing stuff
e
s 00004/00001/00862
d D 3.7 92/08/24 19:17:41 edward 7 6
c use close-on-exec
e
s 00001/00001/00862
d D 3.6 90/08/12 12:44:56 edward 6 5
c lint
e
s 00003/00000/00860
d D 3.5 90/06/06 21:43:33 bostic 5 4
c fix contrib notice (Edward Wang)
e
s 00001/00011/00859
d D 3.4 90/06/02 15:19:35 bostic 4 3
c new copyright notice
e
s 00321/00292/00549
d D 3.3 89/09/15 17:49:04 edward 3 2
c compress control characters as well
e
s 00753/00173/00088
d D 3.2 89/08/24 04:42:20 edward 2 1
c new compression algorithm
e
s 00261/00000/00000
d D 3.1 89/08/02 19:14:20 edward 1 0
c date and time created 89/08/02 19:14:20 by edward
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
I 5
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 5
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "ww.h"
D 3
#include "xx.h"
E 3
#include "tt.h"

I 3
	/* special */
#include <stdio.h>
I 7
#include <fcntl.h>
E 7
int cc_trace = 0;
FILE *cc_trace_fp;

E 3
D 2
	/* tunable constants */
int xc_token_size = 2;
int xc_weight = 1024;
int xc_thresh;
int xc_limit;
E 2
I 2
	/* tunable parameters */
E 2

D 2
	/* fundamental constants */
#define TOKEN_MAX	32
#define NTOKEN		128
#define NCTOKEN		(NTOKEN * 32)	/* should be at least xxbufsize */
#define H		13
#define HSIZE		(1 << H)	/* at least twice NCTOKEN */
E 2
I 2
D 3
int xc_reverse = 1;
int xc_sort = 0;
int xc_chop = 0;
E 3
I 3
int cc_reverse = 1;
int cc_sort = 0;
int cc_chop = 0;
E 3
E 2

D 2
struct xc_token {
	long time;
	long weight;
E 2
I 2
D 3
int xc_token_max = 8;		/* <= TOKEN_MAX */
int xc_token_min = 2;		/* > tt.tt_put_token_cost */
int xc_npass0 = 1;
int xc_npass1 = 1;
E 3
I 3
int cc_token_max = 8;		/* <= TOKEN_MAX */
int cc_token_min = 2;		/* > tt.tt_put_token_cost */
int cc_npass0 = 1;
int cc_npass1 = 1;
E 3

D 3
int xc_bufsize = 1024 * 3;	/* XXX, or 80 * 24 * 2 */
E 3
I 3
int cc_bufsize = 1024 * 3;	/* XXX, or 80 * 24 * 2 */
E 3

D 3
int xc_ntoken = 8192;
E 3
I 3
int cc_ntoken = 8192;
E 3

D 3
#define xc_weight XXX
#ifndef xc_weight
int xc_weight = 0;
E 3
I 3
#define cc_weight XXX
#ifndef cc_weight
int cc_weight = 0;
E 3
#endif

#define TOKEN_MAX 16

D 3
struct xc {
E 3
I 3
struct cc {
E 3
E 2
	char string[TOKEN_MAX];
D 2
	short index;
	struct xc_token *forw;
	struct xc_token *back;
	struct xc_token *hforw;
	struct xc_token **hback;
E 2
I 2
	char length;
	char flag;
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
	short weight;
#endif
	long time;		/* time last seen */
	short bcount;		/* count in this buffer */
	short ccount;		/* count in compression */
	short places;		/* places in the buffer */
	short code;		/* token code */
D 3
	struct xc *qforw, *qback;
	struct xc *hforw, **hback;
E 3
I 3
	struct cc *qforw, *qback;
	struct cc *hforw, **hback;
E 3
E 2
};

D 2
struct xc_token xc_q1, xc_q2;
struct xc_token **xc_htab;
struct xc_token **xc_line;
long xc_time;
long xc_time0;
E 2
I 2
D 3
short xc_thresholds[TOKEN_MAX + 1];
#define thresh(length) (xc_thresholds[length])
E 3
I 3
short cc_thresholds[TOKEN_MAX + 1];
#define thresh(length) (cc_thresholds[length])
E 3
#define threshp(code, count, length) \
D 3
	((code) >= 0 || (short) (count) >= xc_thresholds[length])
E 3
I 3
	((code) >= 0 || (short) (count) >= cc_thresholds[length])
E 3
E 2

D 2
#define xc_hs1 3
#define xc_hs2 (H - 3)
int xc_uhs1, xc_uhs2;
#define xchash(h, c)	((((h) << xc_hs1 | (h) >> xc_hs2) ^ (c)) & HSIZE - 1)
#define xcunhash(h, c)	(((h) ^ (c) << xc_uhs1 ^ (c) >> xc_uhs2) & HSIZE - 1)
#define xccopy(f, t)	bcopy(f, t, xc_token_size)
#define xcequal(f, t)	(bcmp(f, t, xc_token_size) == 0)
#define xcinsert(t1, t2) \
			((t1)->back->forw = (t1)->forw, \
			(t1)->forw->back = (t1)->back, \
			(t2)->forw->back = (t1), \
			(t1)->forw = (t2)->forw, \
			(t2)->forw = (t1), \
			(t1)->back = (t2))
E 2
I 2
D 3
#ifndef xc_weight
short xc_wthresholds[TOKEN_MAX + 1];
#define wthresh(length) (xc_wthresholds[length])
#define wthreshp(weight, length) ((short) (weight) >= xc_wthresholds[length])
E 3
I 3
#ifndef cc_weight
short cc_wthresholds[TOKEN_MAX + 1];
#define wthresh(length) (cc_wthresholds[length])
#define wthreshp(weight, length) ((short) (weight) >= cc_wthresholds[length])
E 3
#else
#define wthreshp(weight, length) (0)
#endif
E 2

I 2
D 3
#ifndef xc_weight
short xc_wlimits[TOKEN_MAX + 1];
#define wlimit(length) (xc_wlimits[length])
E 3
I 3
#ifndef cc_weight
short cc_wlimits[TOKEN_MAX + 1];
#define wlimit(length) (cc_wlimits[length])
E 3
#endif

#define put_token_score(length) ((length) - tt.tt_put_token_cost)

D 3
int xc_score_adjustments[TOKEN_MAX + 1][8]; /* XXX, 8 > max of xc_thresholds */
E 3
I 3
int cc_score_adjustments[TOKEN_MAX + 1][8]; /* XXX, 8 > max of cc_thresholds */
E 3
#define score_adjust(score, p) \
	do { \
		int length = (p)->length; \
		int ccount = (p)->ccount; \
		if (threshp((p)->code, ccount, length) || \
		    wthreshp((p)->weight, length)) /* XXX */ \
			(score) -= length - tt.tt_put_token_cost; \
		else \
D 3
			(score) += xc_score_adjustments[length][ccount]; \
E 3
I 3
			(score) += cc_score_adjustments[length][ccount]; \
E 3
	} while (0)

D 3
int xc_initial_scores[TOKEN_MAX + 1][8]; /* XXX, 8 > max of xc_thresholds */
E 3
I 3
int cc_initial_scores[TOKEN_MAX + 1][8]; /* XXX, 8 > max of cc_thresholds */
E 3

D 3
struct xc xc_q0a, xc_q0b, xc_q1a, xc_q1b;
E 3
I 3
struct cc cc_q0a, cc_q0b, cc_q1a, cc_q1b;
E 3

D 3
#define qinsert(x1, x2) \
E 3
I 3
#define qinsert(p1, p2) \
E 3
	do { \
D 3
		register struct xc *forw = (x1)->qforw; \
		register struct xc *back = (x1)->qback; \
E 3
I 3
		register struct cc *forw = (p1)->qforw; \
		register struct cc *back = (p1)->qback; \
E 3
		back->qforw = forw; \
		forw->qback = back; \
D 3
		forw = (x2)->qforw; \
		(x1)->qforw = forw; \
		forw->qback = (x1); \
		(x2)->qforw = (x1); \
		(x1)->qback = (x2); \
E 3
I 3
		forw = (p2)->qforw; \
		(p1)->qforw = forw; \
		forw->qback = (p1); \
		(p2)->qforw = (p1); \
		(p1)->qback = (p2); \
E 3
	} while (0)

D 3
#define qinsertq(q, x) \
E 3
I 3
#define qinsertq(q, p) \
E 3
	((q)->qforw == (q) ? 0 : \
D 3
	 ((q)->qback->qforw = (x)->qforw, \
	  (x)->qforw->qback = (q)->qback, \
	  (q)->qforw->qback = (x), \
	  (x)->qforw = (q)->qforw, \
E 3
I 3
	 ((q)->qback->qforw = (p)->qforw, \
	  (p)->qforw->qback = (q)->qback, \
	  (q)->qforw->qback = (p), \
	  (p)->qforw = (q)->qforw, \
E 3
	  (q)->qforw = (q), \
	  (q)->qback = (q)))

#define H		(14)
#define HSIZE		(1 << H)
D 3
#define hash(h, c)	((((h) >> H - 8 | (h) << 8) ^ (unsigned char)(c)) & \
				HSIZE - 1)
E 3
I 3
#define hash(h, c)	((((h) >> H - 8 | (h) << 8) ^ (c)) & HSIZE - 1)
E 3

D 3
struct xc **xc_output;			/* the output array */
short *xc_places[TOKEN_MAX + 1];
short *xc_hashcodes;			/* for computing hashcodes */
struct xc **xc_htab;			/* the hash table */
struct xc **xc_tokens;			/* holds all the active tokens */
struct xc_undo {
	struct xc **pos;
	struct xc *val;
} *xc_undo;
E 3
I 3
char *cc_buffer;
struct cc **cc_output;			/* the output array */
short *cc_places[TOKEN_MAX + 1];
short *cc_hashcodes;			/* for computing hashcodes */
struct cc **cc_htab;			/* the hash table */
struct cc **cc_tokens;			/* holds all the active tokens */
struct cc_undo {
	struct cc **pos;
	struct cc *val;
} *cc_undo;
E 3

D 3
long xc_time, xc_time0;
E 3
I 3
long cc_time, cc_time0;
E 3

E 2
D 3
xcinit()
E 3
I 3
char *cc_tt_ob, *cc_tt_obe;

ccinit()
E 3
{
D 2
	register struct xc_token *tp;
	register i;
E 2
I 2
	register i, j;
D 3
	register struct xc *p;
E 3
I 3
	register struct cc *p;
E 3
E 2

D 2
	if (xc_token_size < 2) {
E 2
I 2
D 3
	if (tt.tt_token_max > xc_token_max)
		tt.tt_token_max = xc_token_max;
	if (tt.tt_token_min < xc_token_min)
		tt.tt_token_min = xc_token_min;
E 3
I 3
	if (tt.tt_token_max > cc_token_max)
		tt.tt_token_max = cc_token_max;
	if (tt.tt_token_min < cc_token_min)
		tt.tt_token_min = cc_token_min;
E 3
	if (tt.tt_token_min > tt.tt_token_max) {
E 2
		tt.tt_ntoken = 0;
D 2
		return;
E 2
I 2
		return 0;
E 2
	}
D 2
	xc_thresh = xc_weight *
		(1 + (tt.tt_set_token_cost + tt.tt_put_token_cost) /
			xc_token_size);
	xc_limit = xc_thresh + xc_weight;
	if (tt.tt_token_max > TOKEN_MAX)
		tt.tt_token_max = TOKEN_MAX;
	xc_uhs1 = (xc_token_size - 1) * xc_hs1 % H;
	xc_uhs2 = H - xc_uhs1;
	xc_time = 0;
	xc_htab = (struct xc_token **) calloc(HSIZE, sizeof *xc_htab);
	xc_line = (struct xc_token **)
		malloc((unsigned) xxbufsize * sizeof *xc_line);
	if (xc_line == 0)
E 2
I 2
D 3
	if (tt.tt_ntoken > xc_ntoken / 2)	/* not likely */
		tt.tt_ntoken = xc_ntoken / 2;
	if (xxbufsize > xc_bufsize)
		xxbufsize = xc_bufsize;		/* XXX */
E 3
I 3
	if (tt.tt_ntoken > cc_ntoken / 2)	/* not likely */
		tt.tt_ntoken = cc_ntoken / 2;
E 3
#define C(x) (sizeof (x) / sizeof *(x))
D 3
	for (i = 0; i < C(xc_thresholds); i++) {
E 3
I 3
	for (i = 0; i < C(cc_thresholds); i++) {
E 3
		int h = i - tt.tt_put_token_cost;
		if (h > 0)
D 3
			xc_thresholds[i] =
E 3
I 3
			cc_thresholds[i] =
E 3
				(tt.tt_set_token_cost + 1 + h - 1) / h + 1;
		else
D 3
			xc_thresholds[i] = 0;
E 3
I 3
			cc_thresholds[i] = 0;
E 3
	}
D 3
	for (i = 0; i < C(xc_score_adjustments); i++) {
		int t = xc_thresholds[i];
		for (j = 0; j < C(*xc_score_adjustments); j++) {
E 3
I 3
	for (i = 0; i < C(cc_score_adjustments); i++) {
		int t = cc_thresholds[i];
		for (j = 0; j < C(*cc_score_adjustments); j++) {
E 3
			if (j >= t)
D 3
				xc_score_adjustments[i][j] =
E 3
I 3
				cc_score_adjustments[i][j] =
E 3
					- (i - tt.tt_put_token_cost);
			else if (j < t - 1)
D 3
				xc_score_adjustments[i][j] = 0;
E 3
I 3
				cc_score_adjustments[i][j] = 0;
E 3
			else
				/*
				 * cost now is
				 *	length * (ccount + 1)		a
				 * cost before was
				 *	set-token-cost + length +
				 *		ccount * put-token-cost	b
				 * the score adjustment is (b - a)
				 */
D 3
				xc_score_adjustments[i][j] =
E 3
I 3
				cc_score_adjustments[i][j] =
E 3
					tt.tt_set_token_cost + i +
						j * tt.tt_put_token_cost -
							i * (j + 1);
			if (j >= t)
D 3
				xc_initial_scores[i][j] = 0;
E 3
I 3
				cc_initial_scores[i][j] = 0;
E 3
			else
				/*
				 * - (set-token-cost +
				 *	(length - put-token-cost) -
				 *	(length - put-token-cost) * ccount)
				 */
D 3
				xc_initial_scores[i][j] =
E 3
I 3
				cc_initial_scores[i][j] =
E 3
					- (tt.tt_set_token_cost +
					   (i - tt.tt_put_token_cost) -
					   (i - tt.tt_put_token_cost) * j);
		}
	}
D 3
#ifndef xc_weight
	for (i = 1; i < C(xc_wthresholds); i++) {
		xc_wthresholds[i] =
E 3
I 3
#ifndef cc_weight
	for (i = 1; i < C(cc_wthresholds); i++) {
		cc_wthresholds[i] =
E 3
			((tt.tt_set_token_cost + tt.tt_put_token_cost) / i +
				i / 5 + 1) *
D 3
				xc_weight + 1;
		xc_wlimits[i] = xc_wthresholds[i] + xc_weight;
E 3
I 3
				cc_weight + 1;
		cc_wlimits[i] = cc_wthresholds[i] + cc_weight;
E 3
	}
#endif
#undef C
D 3
	if ((xc_output = (struct xc **)
	     malloc((unsigned) xxbufsize * sizeof *xc_output)) == 0)
E 3
I 3
	if ((cc_output = (struct cc **)
	     malloc((unsigned) cc_bufsize * sizeof *cc_output)) == 0)
E 3
E 2
		goto nomem;
D 2
	tp = (struct xc_token *) malloc(NCTOKEN * sizeof *tp);
	if (tp == 0)
E 2
I 2
D 3
	if ((xc_hashcodes = (short *)
	     malloc((unsigned) xxbufsize * sizeof *xc_hashcodes)) == 0)
E 3
I 3
	if ((cc_hashcodes = (short *)
	     malloc((unsigned) cc_bufsize * sizeof *cc_hashcodes)) == 0)
E 3
E 2
		goto nomem;
D 2
	xc_q1.forw = &xc_q1;
	xc_q1.back = &xc_q1;
	for (i = 0; i < NTOKEN; i++, tp++) {
		tp->index = i + 1;
		tp->weight = 0;
		tp->time = -1;
		xc_q1.forw->back = tp;
		tp->forw = xc_q1.forw;
		xc_q1.forw = tp;
		tp->back = &xc_q1;
		tp->hback = 0;
E 2
I 2
D 3
	if ((xc_htab = (struct xc **) malloc(HSIZE * sizeof *xc_htab)) == 0)
E 3
I 3
	if ((cc_htab = (struct cc **) malloc(HSIZE * sizeof *cc_htab)) == 0)
E 3
		goto nomem;
D 3
	if ((xc_tokens = (struct xc **)
E 3
I 3
	if ((cc_tokens = (struct cc **)
E 3
	     malloc((unsigned)
D 3
	            (xc_ntoken + tt.tt_token_max - tt.tt_token_min + 1) *
		    sizeof *xc_tokens)) == 0)
E 3
I 3
	            (cc_ntoken + tt.tt_token_max - tt.tt_token_min + 1) *
		    sizeof *cc_tokens)) == 0)
E 3
		goto nomem;
D 3
	if ((xc_undo = (struct xc_undo *)
	     malloc((unsigned) xxbufsize * sizeof *xc_undo)) == 0)
E 3
I 3
	if ((cc_undo = (struct cc_undo *)
	     malloc((unsigned) cc_bufsize * sizeof *cc_undo)) == 0)
E 3
		goto nomem;
	for (i = tt.tt_token_min; i <= tt.tt_token_max; i++)
D 3
		if ((xc_places[i] = (short *)
		     malloc((unsigned) xxbufsize * sizeof **xc_places)) == 0)
E 3
I 3
		if ((cc_places[i] = (short *)
		     malloc((unsigned) cc_bufsize * sizeof **cc_places)) == 0)
E 3
			goto nomem;
D 3
	xc_q0a.qforw = xc_q0a.qback = &xc_q0a;
	xc_q0b.qforw = xc_q0b.qback = &xc_q0b;
	xc_q1a.qforw = xc_q1a.qback = &xc_q1a;
	xc_q1b.qforw = xc_q1b.qback = &xc_q1b;
	if ((p = (struct xc *) malloc((unsigned) xc_ntoken * sizeof *p)) == 0)
E 3
I 3
	cc_q0a.qforw = cc_q0a.qback = &cc_q0a;
	cc_q0b.qforw = cc_q0b.qback = &cc_q0b;
	cc_q1a.qforw = cc_q1a.qback = &cc_q1a;
	cc_q1b.qforw = cc_q1b.qback = &cc_q1b;
	if ((p = (struct cc *) malloc((unsigned) cc_ntoken * sizeof *p)) == 0)
E 3
		goto nomem;
	for (i = 0; i < tt.tt_ntoken; i++) {
		p->code = i;
		p->time = -1;
D 3
		p->qback = xc_q0a.qback;
		p->qforw = &xc_q0a;
E 3
I 3
		p->qback = cc_q0a.qback;
		p->qforw = &cc_q0a;
E 3
		p->qback->qforw = p;
D 3
		xc_q0a.qback = p;
E 3
I 3
		cc_q0a.qback = p;
E 3
		p++;
E 2
	}
D 2
	xc_q2.forw = &xc_q2;
	xc_q2.back = &xc_q2;
	for (; i < NCTOKEN; i++, tp++) {
		tp->index = 0;
		tp->weight = 0;
		tp->time = -1;
		xc_q2.forw->back = tp;
		tp->forw = xc_q2.forw;
		xc_q2.forw = tp;
		tp->back = &xc_q2;
		tp->hback = 0;
E 2
I 2
D 3
	for (; i < xc_ntoken; i++) {
E 3
I 3
	for (; i < cc_ntoken; i++) {
E 3
		p->code = -1;
		p->time = -1;
D 3
		p->qback = xc_q1a.qback;
		p->qforw = &xc_q1a;
E 3
I 3
		p->qback = cc_q1a.qback;
		p->qforw = &cc_q1a;
E 3
		p->qback->qforw = p;
D 3
		xc_q1a.qback = p;
E 3
I 3
		cc_q1a.qback = p;
E 3
		p++;
E 2
	}
I 3
	cc_tt_ob = tt_ob;
	cc_tt_obe = tt_obe;
	if ((cc_buffer = malloc((unsigned) cc_bufsize)) == 0)
		goto nomem;
E 3
	return 0;
nomem:
	wwerrno = WWE_NOMEM;
	return -1;
}

D 3
xcstart()
E 3
I 3
ccstart()
E 3
{
D 2
	register struct xc_token *tp;
E 2
I 2
D 3
	register struct xc *p;
E 3
I 3
D 8
	register struct cc *p;
E 8
	int ccflush();
E 3
E 2

D 2
	for (tp = xc_q1.forw; tp != &xc_q1; tp = tp->forw)
		if (tp->index > 0)
			tp->index = - tp->index;
E 2
I 2
D 3
	bzero((char *) xc_htab, HSIZE * sizeof *xc_htab);
	for (p = xc_q0a.qforw; p != &xc_q0a; p = p->qforw)
E 3
I 3
D 8
	(*tt.tt_flush)();
E 8
I 8
	ttflush();
E 8
	tt_obp = tt_ob = cc_buffer;
	tt_obe = tt_ob + cc_bufsize;
	tt.tt_flush = ccflush;
I 8
	if (cc_trace) {
		cc_trace_fp = fopen("window-trace", "a");
		(void) fcntl(fileno(cc_trace_fp), F_SETFD, 1);
	}
	ccreset();
}

ccreset()
{
	register struct cc *p;

E 8
	bzero((char *) cc_htab, HSIZE * sizeof *cc_htab);
	for (p = cc_q0a.qforw; p != &cc_q0a; p = p->qforw)
E 3
		p->hback = 0;
D 3
	for (p = xc_q1a.qforw; p != &xc_q1a; p = p->qforw)
E 3
I 3
	for (p = cc_q1a.qforw; p != &cc_q1a; p = p->qforw)
E 3
		p->hback = 0;
I 3
D 7
	if (cc_trace)
E 7
I 7
D 8
	if (cc_trace) {
E 7
		cc_trace_fp = fopen("window-trace", "a");
I 7
		(void) fcntl(fileno(cc_trace_fp), F_SETFD, 1);
	}
E 8
E 7
E 3
E 2
}

D 2
xcreset()
E 2
I 2
D 3
xcscan(buffer, bufsize)
	char *buffer;
E 3
I 3
ccend()
E 3
E 2
{
I 3
D 8
	int ttflush();
E 8

D 8
	(*tt.tt_flush)();
E 8
I 8
	ttflush();
E 8
	tt_obp = tt_ob = cc_tt_ob;
	tt_obe = cc_tt_obe;
D 8
	tt.tt_flush = ttflush;
E 8
I 8
	tt.tt_flush = 0;
E 8
	if (cc_trace_fp != NULL) {
		(void) fclose(cc_trace_fp);
		cc_trace_fp = NULL;
	}
}

ccflush()
{
	int bufsize = tt_obp - tt_ob;
E 3
I 2
	int n;
I 3
D 8
	int ttflush();
E 8
E 3

D 3
	if (bufsize <= tt.tt_token_min)		/* one more for char_sep */
E 3
I 3
	if (tt_ob != cc_buffer)
		abort();
	if (cc_trace_fp != NULL) {
		(void) fwrite(tt_ob, 1, bufsize, cc_trace_fp);
D 8
		putc(-1, cc_trace_fp);
E 8
I 8
		(void) putc(-1, cc_trace_fp);
E 8
	}
I 8
	tt.tt_flush = 0;
	(*tt.tt_compress)(1);
E 8
	if (bufsize < tt.tt_token_min) {
		ttflush();
E 3
D 8
		return;
E 8
I 8
		goto out;
E 8
E 2
D 3
	xc_time0 = xc_time;
I 2
	xc_time += bufsize;
#ifdef STATS
	if (verbose >= 0)
		time_begin();
#endif
	n = xc_sweep_phase(buffer, bufsize, xc_tokens);
#ifdef STATS
	if (verbose >= 0) {
		time_end();
		time_begin();
E 3
	}
D 3
#endif
	xc_compress_phase(xc_output, bufsize, xc_tokens, n);
#ifdef STATS
	if (verbose >= 0)
		time_end();
#endif
E 3
I 3
	tt_obp = tt_ob = cc_tt_ob;
	tt_obe = cc_tt_obe;
D 8
	tt.tt_flush = ttflush;
E 8
	cc_time0 = cc_time;
	cc_time += bufsize;
	n = cc_sweep_phase(cc_buffer, bufsize, cc_tokens);
	cc_compress_phase(cc_output, bufsize, cc_tokens, n);
	cc_output_phase(cc_buffer, cc_output, bufsize);
	ttflush();
	tt_obp = tt_ob = cc_buffer;
	tt_obe = cc_buffer + cc_bufsize;
I 8
out:
	(*tt.tt_compress)(0);
E 8
	tt.tt_flush = ccflush;
E 3
E 2
}

D 2
xcscan(s, n, x)
	char *s;
E 2
I 2
D 3
xc_sweep_phase(buffer, bufsize, tokens)
E 3
I 3
cc_sweep_phase(buffer, bufsize, tokens)
E 3
	char *buffer;
D 3
	struct xc **tokens;
E 3
I 3
	struct cc **tokens;
E 3
{
D 3
	register struct xc **pp = tokens;
E 3
I 3
	register struct cc **pp = tokens;
E 3
	register i, n;
#ifdef STATS
	int nn, ii;
#endif

#ifdef STATS
I 3
	if (verbose >= 0)
		time_begin();
E 3
	if (verbose > 0)
		printf("Sweep:");
#endif
D 3
	xc_sweep0(buffer, bufsize, tt.tt_token_min - 1);
E 3
I 3
	cc_sweep0(buffer, bufsize, tt.tt_token_min - 1);
E 3
#ifdef STATS
D 3
	xc_ntoken_stat = 0;
E 3
I 3
	ntoken_stat = 0;
E 3
	nn = 0;
	ii = 0;
#endif
	for (i = tt.tt_token_min; i <= tt.tt_token_max; i++) {
#ifdef STATS
		if (verbose > 0) {
			if (ii > 7) {
				printf("\n      ");
				ii = 0;
			}
			ii++;
			printf(" (%d", i);
			(void) fflush(stdout);
		}
#endif
D 3
		n = xc_sweep(buffer, bufsize, pp, i);
E 3
I 3
		n = cc_sweep(buffer, bufsize, pp, i);
E 3
		pp += n;
#ifdef STATS
		if (verbose > 0) {
			if (--n > 0) {
				printf(" %d", n);
				nn += n;
			}
			putchar(')');
		}
#endif
	}
D 3
	qinsertq(&xc_q1b, &xc_q1a);
E 3
I 3
	qinsertq(&cc_q1b, &cc_q1a);
E 3
#ifdef STATS
	if (verbose > 0)
		printf("\n       %d tokens, %d candidates\n",
D 3
			xc_ntoken_stat, nn);
E 3
I 3
			ntoken_stat, nn);
	if (verbose >= 0)
		time_end();
E 3
#endif
	return pp - tokens;
}

D 3
xc_sweep0(buffer, n, length)
E 3
I 3
cc_sweep0(buffer, n, length)
E 3
	char *buffer;
E 2
D 3
	register n;
I 2
	register length;
E 3
E 2
{
I 3
	register char *p;
	register short *hc;
E 3
D 2
	register char *p;
E 2
I 2
	register i;
D 3
	register char *p = buffer;
	register short *hc = xc_hashcodes;
E 2
	register h;
E 3
I 3
	register short c;
	register short pc = tt.tt_padc;
E 3
I 2

D 3
	if (--length == 0)
		do {
#ifdef char_sep
			if ((*hc++ = *p++) == char_sep)
				hc[-1] = -1;
#else
			*hc++ = *p++;
#endif
		} while (--n);
	else
		for (n -= length; --n >= 0;) {
#ifdef char_sep
			if (*p == char_sep) {
				*hc++ = -1;
				p++;
				continue;
			}
#endif
			h = *p++;
			for (i = length; --i >= 0;) {
#ifdef char_sep
				if (*p == char_sep) {
					h = -1;
					p += i + 1;
					break;
				}
#endif
				h = hash(h, *p++);
			}
			*hc++ = h;
			p -= length;
E 3
I 3
	/* n and length are at least 1 */
	p = buffer++;
	hc = cc_hashcodes;
	i = n;
	do {
		if ((*hc++ = *p++) == pc)
			hc[-1] = -1;
	} while (--i);
	while (--length) {
		p = buffer++;
		hc = cc_hashcodes;
		for (i = n--; --i;) {
			if ((c = *p++) == pc || *hc < 0)
				c = -1;
			else
				c = hash(*hc, c);
			*hc++ = c;
E 3
		}
I 3
	}
E 3
}

D 3
xc_sweep(buffer, bufsize, tokens, length)
E 3
I 3
cc_sweep(buffer, bufsize, tokens, length)
E 3
	char *buffer;
D 3
	struct xc **tokens;
E 3
I 3
	struct cc **tokens;
E 3
	register length;
{
D 3
	register struct xc *p;
E 3
I 3
	register struct cc *p;
E 3
	register char *cp;
E 2
	register i;
D 2
	register struct xc_token *tp;
	register struct xc_token **lp = xc_line + x;
E 2
I 2
	short *hc;
D 3
	short *places = xc_places[length];
	struct xc **pp = tokens;
E 3
I 3
	short *places = cc_places[length];
	struct cc **pp = tokens;
E 3
	short threshold = thresh(length);
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
	short wthreshold = wthresh(length);
	short limit = wlimit(length);
#endif
	int time;
I 3
	short pc = tt.tt_padc;
E 3
E 2

D 2
	if (n < xc_token_size)
		return;
	p = s;
	for (i = xc_token_size - 2, h = xchash(0, *p++); --i >= 0;
	     h = xchash(h, *p++))
		;
	for (i = n - xc_token_size;;) {
		xc_time++;
		h = xchash(h, *p++);
		for (tp = xc_htab[h];
		     tp != 0 && !xcequal(tp->string, p - xc_token_size);
		     tp = tp->hforw)
			;
		if (tp == 0) {
			tp = xc_q2.back;
			if (tp->time >= xc_time0) {
				*lp = 0;
				goto cont;
E 2
I 2
	i = length - 1;
	bufsize -= i;
	cp = buffer + i;
D 3
	hc = xc_hashcodes;
	time = xc_time0;
E 3
I 3
	hc = cc_hashcodes;
	time = cc_time0;
E 3
	for (i = 0; i < bufsize; i++, time++) {
D 3
		struct xc **h;
E 3
I 3
		struct cc **h;
E 3

		{
			register short *hc1 = hc;
D 3
#ifdef char_sep
			if (*hc1 < 0 || *cp == char_sep) {
E 3
I 3
			register short c = *cp++;
			register short hh;
			if ((hh = *hc1) < 0 || c == pc) {
E 3
				*hc1++ = -1;
				hc = hc1;
D 3
				cp++;
E 3
				continue;
E 2
			}
D 2
			if (tp->hback != 0 && (*tp->hback = tp->hforw) != 0)
				tp->hforw->hback = tp->hback;
			xccopy(p - xc_token_size, tp->string);
			if ((tp->hforw = xc_htab[h]) != 0)
				tp->hforw->hback = &tp->hforw;
			tp->hback = xc_htab + h;
			xc_htab[h] = tp;
			tp->weight = xc_weight;
		} else {
E 2
I 2
D 3
#endif
			h = xc_htab + (*hc1 = hash(*hc1, *cp++));
			hc = hc1 + 1;
E 3
I 3
			h = cc_htab + (*hc1++ = hash(hh, c));
			hc = hc1;
E 3
		}
		for (p = *h; p != 0; p = p->hforw)
			if (p->length == (char) length) {
				register char *p1 = p->string;
				register char *p2 = cp - length;
				register n = length;
				do
					if (*p1++ != *p2++)
						goto fail;
				while (--n);
				break;
			fail:;
			}
		if (p == 0) {
D 3
			p = xc_q1a.qback;
			if (p == &xc_q1a ||
			    p->time >= xc_time0 && p->length == (char) length)
E 3
I 3
			p = cc_q1a.qback;
			if (p == &cc_q1a ||
			    p->time >= cc_time0 && p->length == (char) length)
E 3
				continue;
			if (p->hback != 0)
				if ((*p->hback = p->hforw) != 0)
					p->hforw->hback = p->hback;
			{
				register char *p1 = p->string;
				register char *p2 = cp - length;
				register n = length;
				do
					*p1++ = *p2++;
				while (--n);
			}
			p->length = length;
D 3
#ifndef xc_weight
			p->weight = xc_weight;
E 3
I 3
#ifndef cc_weight
			p->weight = cc_weight;
E 3
#endif
			p->time = time;
			p->bcount = 1;
			p->ccount = 0;
			p->flag = 0;
			if ((p->hforw = *h) != 0)
				p->hforw->hback = &p->hforw;
			*h = p;
			p->hback = h;
D 3
			qinsert(p, &xc_q1a);
E 3
I 3
			qinsert(p, &cc_q1a);
E 3
			places[i] = -1;
			p->places = i;
#ifdef STATS
D 3
			xc_ntoken_stat++;
E 3
I 3
			ntoken_stat++;
E 3
#endif
D 3
		} else if (p->time < xc_time0) {
#ifndef xc_weight
E 3
I 3
		} else if (p->time < cc_time0) {
#ifndef cc_weight
E 3
			if ((p->weight += p->time - time) < 0)
D 3
				p->weight = xc_weight;
			else if ((p->weight += xc_weight) > limit)
E 3
I 3
				p->weight = cc_weight;
			else if ((p->weight += cc_weight) > limit)
E 3
				p->weight = limit;
#endif
			p->time = time;
			p->bcount = 1;
			p->ccount = 0;
			if (p->code >= 0) {
				p->flag = 1;
				*pp++ = p;
			} else
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
			if (p->weight >= wthreshold) {
				p->flag = 1;
				*pp++ = p;
D 3
				qinsert(p, &xc_q1b);
E 3
I 3
				qinsert(p, &cc_q1b);
E 3
			} else
#endif
			{
				p->flag = 0;
D 3
				qinsert(p, &xc_q1a);
E 3
I 3
				qinsert(p, &cc_q1a);
E 3
			}
			places[i] = -1;
			p->places = i;
#ifdef STATS
D 3
			xc_ntoken_stat++;
E 3
I 3
			ntoken_stat++;
E 3
#endif
		} else if (p->time + length > time) {
E 2
			/*
D 2
			 * Don't count overlapping tokens as two,
			 * and don't update the time so a token that overlaps
			 * this but not the previous will be counted,.
			 * but do fix up the weight to compensate for
			 * the incorrect time.
E 2
I 2
			 * overlapping token, don't count as two and
			 * don't update time, but do adjust weight to offset
			 * the difference
E 2
			 */
D 2
			if (tp->time > xc_time - xc_token_size)
				tp->weight += xc_time - tp->time;
			else if ((tp->weight += tp->time - xc_time) < 0)
				tp->weight = xc_weight;
			else if ((tp->weight += xc_weight) > xc_limit)
				tp->weight = xc_limit;
E 2
I 2
D 3
#ifndef xc_weight
			if (xc_weight != 0) {	/* XXX */
E 3
I 3
#ifndef cc_weight
			if (cc_weight != 0) {	/* XXX */
E 3
				p->weight += time - p->time;
				if (!p->flag && p->weight >= wthreshold) {
					p->flag = 1;
					*pp++ = p;
D 3
					qinsert(p, &xc_q1b);
E 3
I 3
					qinsert(p, &cc_q1b);
E 3
				}
			}
#endif
			places[i] = p->places;
			p->places = i;
		} else {
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
			if ((p->weight += p->time - time) < 0)
D 3
				p->weight = xc_weight;
			else if ((p->weight += xc_weight) > limit)
E 3
I 3
				p->weight = cc_weight;
			else if ((p->weight += cc_weight) > limit)
E 3
				p->weight = limit;
#endif
			p->time = time;
			p->bcount++;
			if (!p->flag &&
			    /* code must be < 0 if flag false here */
			    (p->bcount >= threshold
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
			     || p->weight >= wthreshold
#endif
			     )) {
				p->flag = 1;
				*pp++ = p;
D 3
				qinsert(p, &xc_q1b);
E 3
I 3
				qinsert(p, &cc_q1b);
E 3
			}
			places[i] = p->places;
			p->places = i;
E 2
		}
D 2
		tp->time = xc_time;
		if (tp->index == 0)
			xcinsert(tp, &xc_q2);
		else
			xcinsert(tp, &xc_q1);
		*lp = tp;
	cont:
		lp++;
		if (--i < 0)
			break;
		h = xcunhash(h, p[- xc_token_size]);
E 2
I 2
	}
	if ((i = pp - tokens) > 0) {
		*pp = 0;
D 3
		if (xc_reverse)
			xc_sweep_reverse(tokens, places);
		if (xc_sort && i > 1) {
			int xc_token_compare();
E 3
I 3
		if (cc_reverse)
			cc_sweep_reverse(tokens, places);
		if (cc_sort && i > 1) {
			int cc_token_compare();
E 3
			qsort((char *) tokens, i, sizeof *tokens,
D 3
			      xc_token_compare);
E 3
I 3
			      cc_token_compare);
E 3
		}
D 3
		if (xc_chop) {
			if ((i = i * xc_chop / 100) == 0)
E 3
I 3
		if (cc_chop) {
			if ((i = i * cc_chop / 100) == 0)
E 3
				i = 1;
			tokens[i] = 0;
		}
		i++;
E 2
	}
D 2
	for (i = xc_token_size - 1; --i >= 0;)
		*lp++ = 0;
E 2
I 2
	return i;
E 2
}

I 2
D 3
xc_sweep_reverse(pp, places)
	register struct xc **pp;
E 3
I 3
cc_sweep_reverse(pp, places)
	register struct cc **pp;
E 3
	register short *places;
{
D 3
	register struct xc *p;
E 3
I 3
	register struct cc *p;
E 3
	register short front, back, t;

	while ((p = *pp++) != 0) {
		back = -1;
		t = p->places;
		/* the list is never empty */
		do {
			front = places[t];
			places[t] = back;
			back = t;
		} while ((t = front) >= 0);
		p->places = back;
	}
}

D 3
xc_compress_phase(output, bufsize, tokens, ntoken)
	struct xc **output;
	struct xc **tokens;
E 3
I 3
cc_compress_phase(output, bufsize, tokens, ntoken)
	struct cc **output;
	struct cc **tokens;
E 3
{
	register i;

	bzero((char *) output, bufsize * sizeof *output);
D 3
	for (i = 0; i < xc_npass0; i++)
		xc_compress_phase1(output, tokens, ntoken, 0);
	for (i = 0; i < xc_npass1; i++)
		xc_compress_phase1(output, tokens, ntoken, 1);
	xc_compress_cleanup(output, bufsize);
E 3
I 3
	for (i = 0; i < cc_npass0; i++)
		cc_compress_phase1(output, tokens, ntoken, 0);
	for (i = 0; i < cc_npass1; i++)
		cc_compress_phase1(output, tokens, ntoken, 1);
	cc_compress_cleanup(output, bufsize);
E 3
}

D 3
xc_compress_phase1(output, tokens, ntoken, flag)
	register struct xc **output;
	struct xc **tokens;
E 3
I 3
cc_compress_phase1(output, tokens, ntoken, flag)
	register struct cc **output;
	struct cc **tokens;
E 3
{
D 6
	register int i = 0;
E 6
D 3
	register struct xc **pp;
E 3
I 3
	register struct cc **pp;
#ifdef STATS
I 6
	register int i = 0;
E 6
	int nt = 0, cc = 0, nc = 0;
#endif
E 3

#ifdef STATS
I 3
	if (verbose >= 0)
		time_begin();
E 3
	if (verbose > 0)
		printf("Compress:");
#endif
	pp = tokens;
	while (pp < tokens + ntoken) {
#ifdef STATS
		if (verbose > 0) {
D 3
			xc_ntoken_stat = 0;
			xc_ccount_stat = 0;
			xc_ncover_stat = 0;
E 3
I 3
			ntoken_stat = 0;
			ccount_stat = 0;
			ncover_stat = 0;
E 3
			if (i > 2) {
				printf("\n         ");
				i = 0;
			}
			i++;
			printf(" (%d", (*pp)->length);
			(void) fflush(stdout);
		}
#endif
D 3
		pp += xc_compress(output, pp, flag);
E 3
I 3
		pp += cc_compress(output, pp, flag);
E 3
#ifdef STATS
D 3
		if (verbose > 0)
			printf(" %dt %du %dc)", xc_ntoken_stat, xc_ccount_stat,
			       xc_ncover_stat);
E 3
I 3
		if (verbose > 0) {
			printf(" %dt %du %dc)", ntoken_stat, ccount_stat,
			       ncover_stat);
			nt += ntoken_stat;
			cc += ccount_stat;
			nc += ncover_stat;
		}
E 3
#endif
	}
#ifdef STATS
	if (verbose > 0)
D 3
		printf("\n");
E 3
I 3
		printf("\n   total: (%dt %du %dc)\n", nt, cc, nc);
	if (verbose >= 0)
		time_end();
E 3
#endif
}

D 3
xc_compress_cleanup(output, bufsize)
	register struct xc **output;
E 3
I 3
cc_compress_cleanup(output, bufsize)
	register struct cc **output;
E 3
{
D 3
	register struct xc **end;
E 3
I 3
	register struct cc **end;
E 3

	/* the previous output phase may have been interrupted */
D 3
	qinsertq(&xc_q0b, &xc_q0a);
E 3
I 3
	qinsertq(&cc_q0b, &cc_q0a);
E 3
	for (end = output + bufsize; output < end;) {
D 3
		register struct xc *p;
E 3
I 3
		register struct cc *p;
E 3
		register length;
		if ((p = *output) == 0) {
			output++;
			continue;
		}
		length = p->length;
		if (!p->flag) {
		} else if (p->code >= 0) {
D 3
			qinsert(p, &xc_q0b);
E 3
I 3
			qinsert(p, &cc_q0b);
E 3
			p->flag = 0;
		} else if (p->ccount == 0) {
			*output = 0;
		} else if (p->ccount >= thresh(length)
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
			   || wthreshp(p->weight, length)
#endif
			   ) {
			p->flag = 0;
		} else {
			p->ccount = 0;
			*output = 0;
		}
		output += length;
	}
}

D 3
xc_compress(output, tokens, flag)
	struct xc **output;
	struct xc **tokens;
E 3
I 3
cc_compress(output, tokens, flag)
	struct cc **output;
	struct cc **tokens;
E 3
	char flag;
{
D 3
	struct xc **pp = tokens;
	register struct xc *p = *pp++;
E 3
I 3
	struct cc **pp = tokens;
	register struct cc *p = *pp++;
E 3
	int length = p->length;
	int threshold = thresh(length);
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
	short wthreshold = wthresh(length);
#endif
D 3
	short *places = xc_places[length];
	int *initial_scores = xc_initial_scores[length];
E 3
I 3
	short *places = cc_places[length];
	int *initial_scores = cc_initial_scores[length];
E 3
	int initial_score0 = put_token_score(length);

	do {
		int score;
D 3
		register struct xc_undo *undop;
E 3
I 3
		register struct cc_undo *undop;
E 3
		int ccount;
#ifdef STATS
		int ncover;
#endif
		int i;

		ccount = p->ccount;
		if ((short) ccount >= p->bcount)
			continue;
		if (p->code >= 0 || ccount >= threshold)
			score = 0;
D 3
#ifndef xc_weight
E 3
I 3
#ifndef cc_weight
E 3
		else if (p->weight >= wthreshold)
			/* allow one fewer match than normal */
			/* XXX, should adjust for ccount */
			score = - tt.tt_set_token_cost;
#endif
		else
			score = initial_scores[ccount];
D 3
		undop = xc_undo;
E 3
I 3
		undop = cc_undo;
E 3
#ifdef STATS
		ncover = 0;
#endif
		for (i = p->places; i >= 0; i = places[i]) {
D 3
			register struct xc **jp;
			register struct xc *x;
			register struct xc **ip = output + i;
E 3
I 3
			register struct cc **jp;
			register struct cc *x;
			register struct cc **ip = output + i;
E 3
			register score0 = initial_score0;
D 3
			struct xc **iip = ip + length;
			struct xc_undo *undop1 = undop;
E 3
I 3
			struct cc **iip = ip + length;
			struct cc_undo *undop1 = undop;
E 3

			if ((x = *(jp = ip)) != 0)
				goto z;
			while (--jp >= output)
				if ((x = *jp) != 0) {
					if (jp + x->length > ip)
						goto z;
					break;
				}
			jp = ip + 1;
			while (jp < iip) {
				if ((x = *jp) == 0) {
					jp++;
					continue;
				}
			z:
				if (x == p)
					goto undo;
#ifdef STATS
				ncover++;
#endif
				undop->pos = jp;
				undop->val = x;
				undop++;
				*jp = 0;
				x->ccount--;
				score_adjust(score0, x);
				if (score0 < 0 && flag)
					goto undo;
				jp += x->length;
			}
			undop->pos = ip;
			undop->val = 0;
			undop++;
			*ip = p;
			ccount++;
			score += score0;
			continue;
		undo:
			while (--undop >= undop1)
				if (*undop->pos = x = undop->val)
					x->ccount++;
			undop++;
		}
		if (score > 0) {
#ifdef STATS
D 3
			xc_ccount_stat += ccount - p->ccount;
			xc_ntoken_stat++;
			xc_ncover_stat += ncover;
E 3
I 3
			ccount_stat += ccount - p->ccount;
			ntoken_stat++;
			ncover_stat += ncover;
E 3
#endif
			p->ccount = ccount;
		} else {
D 3
			register struct xc_undo *u = xc_undo;
E 3
I 3
			register struct cc_undo *u = cc_undo;
E 3
			while (--undop >= u) {
D 3
				register struct xc *x;
E 3
I 3
				register struct cc *x;
E 3
				if (*undop->pos = x = undop->val)
					x->ccount++;
			}
		}
	} while ((p = *pp++) != 0);
	return pp - tokens;
}

E 2
D 3
xcwrite(s, n, x)
	register char *s;
	register n;
E 3
I 3
cc_output_phase(buffer, output, bufsize)
	register char *buffer;
	register struct cc **output;
	register bufsize;
E 3
{
	register i;
D 2
	register struct xc_token **lp = xc_line + x;
	register struct xc_token *tp;
	register struct xc_token *tq;
E 2
I 2
D 3
	register struct xc *p, *p1;
	register struct xc **output = xc_output + x;
E 3
I 3
	register struct cc *p, *p1;
E 3
E 2

D 2
	if (n < xc_token_size) {
E 2
I 2
D 3
	if (n < tt.tt_token_min) {
E 2
		(*tt.tt_write)(s, n);
		return;
	}
	for (i = 0; i < n;) {
E 3
I 3
	for (i = 0; i < bufsize;) {
E 3
D 2
		if ((tp = lp[i]) == 0) {
E 2
I 2
		if ((p = output[i]) == 0) {
E 2
D 3
			(*tt.tt_putc)(s[i]);
E 3
I 3
			ttputc(buffer[i]);
E 3
			i++;
D 2
		} else if (tp->index > 0) {
			xcinsert(tp, &xc_q1);
			(*tt.tt_put_token)(tp->index - 1, tp->string,
				xc_token_size);
E 2
I 2
		} else if (p->code >= 0) {
			if (--p->ccount == 0)
D 3
				qinsert(p, &xc_q0a);
E 3
I 3
				qinsert(p, &cc_q0a);
E 3
			(*tt.tt_put_token)(p->code, p->string, p->length);
E 2
			wwntokuse++;
D 2
			wwntoksave += xc_token_size - tt.tt_put_token_cost;
			i += xc_token_size;
		} else if (tp->index < 0) {
			tp->index = - tp->index;
			xcinsert(tp, &xc_q1);
			(*tt.tt_set_token)(tp->index - 1, tp->string,
				xc_token_size);
E 2
I 2
			wwntoksave += put_token_score(p->length);
			i += p->length;
D 3
		} else if ((p1 = xc_q0a.qback) != &xc_q0a) {
E 3
I 3
		} else if ((p1 = cc_q0a.qback) != &cc_q0a) {
E 3
			p->code = p1->code;
			p1->code = -1;
D 3
			qinsert(p1, &xc_q1a);
E 3
I 3
			qinsert(p1, &cc_q1a);
E 3
			if (--p->ccount == 0)
D 3
				qinsert(p, &xc_q0a);
E 3
I 3
				qinsert(p, &cc_q0a);
E 3
			else
D 3
				qinsert(p, &xc_q0b);
E 3
I 3
				qinsert(p, &cc_q0b);
E 3
			(*tt.tt_set_token)(p->code, p->string, p->length);
E 2
			wwntokdef++;
			wwntoksave -= tt.tt_set_token_cost;
D 2
			i += xc_token_size;
		} else if (tp->weight > xc_thresh &&
			   ((tq = xc_q1.back)->index < 0 ||
			    tq->weight + (tq->time - tp->time) + xc_thresh <
			    tp->weight)) {
			if ((tp->index = tq->index) < 0)
				tp->index = - tp->index;
			tq->index = 0;
			xcinsert(tq, &xc_q2);
			xcinsert(tp, &xc_q1);
			(*tt.tt_set_token)(tp->index - 1, tp->string,
				xc_token_size);
			wwntokdef++;
			wwntoksave -= tt.tt_set_token_cost;
			i += xc_token_size;
E 2
I 2
			i += p->length;
E 2
		} else {
D 2
			(*tt.tt_putc)(s[i]);
			i++;
E 2
I 2
			p->ccount--;
D 3
			(*tt.tt_write)(p->string, p->length);
E 3
I 3
			ttwrite(p->string, p->length);
E 3
			wwntokbad++;
			i += p->length;
E 2
		}
	}
D 3
	wwntokc += n;
E 3
I 3
	wwntokc += bufsize;
E 3
I 2
}

D 3
xc_token_compare(p1, p2)
	struct xc **p1, **p2;
E 3
I 3
cc_token_compare(p1, p2)
	struct cc **p1, **p2;
E 3
{
	return (*p2)->bcount - (*p1)->bcount;
E 2
}
E 1
