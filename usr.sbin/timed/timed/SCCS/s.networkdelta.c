h57894
s 00004/00003/00244
d D 8.3 95/04/27 15:43:46 bostic 10 9
c median() has to be prototyped taking a double
c From: Chris Torek <torek@BSDI.COM>
e
s 00022/00013/00225
d D 8.2 95/03/26 14:24:18 vjs 9 8
c fix unlikely loop in median computation
e
s 00002/00002/00236
d D 8.1 93/06/06 14:09:42 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00214/00053/00024
d D 5.1 93/05/11 11:51:14 bostic 7 6
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00001/00076
d D 2.5 91/07/15 10:08:53 bostic 6 5
c typo
e
s 00001/00011/00076
d D 2.4 90/06/01 19:03:55 bostic 5 4
c new copyright notice
e
s 00010/00005/00077
d D 2.3 88/06/18 14:08:20 bostic 4 3
c install approved copyright notice
e
s 00009/00003/00073
d D 2.2 87/12/23 14:30:13 bostic 3 2
c append Berkeley header; NASA wants a copy
e
s 00000/00002/00076
d D 2.1 85/12/10 13:07:14 bloom 2 1
c Multi network support
e
s 00078/00000/00000
d D 1.1 85/06/24 18:27:03 gusella 1 0
c date and time created 85/06/24 18:27:03 by gusella
e
u
U
t
T
I 1
D 7
/*
 * Copyright (c) 1983 Regents of the University of California.
E 7
I 7
/*-
D 8
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 7
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

I 7
#ifdef sgi
#ident "$Revision: 1.4 $"
#endif

E 7
#include "globals.h"
D 7
#include <protocols/timed.h>
E 7

D 7
extern int machup;
E 7
I 7
D 10
static long median __P((float, float *, long *, long *, unsigned int));
E 10
I 10
static long median __P((double, float *, long *, long *, unsigned int));
E 10
E 7
D 2
extern int slvcount;
extern struct host hp[];
E 2

/*
D 7
 * `networkdelta' selects the largest set of deltas that fall within the
 * interval RANGE, and uses them to compute the network average delta 
E 7
I 7
 * Compute a corrected date.
 *	Compute the median of the reasonable differences.  First compute
 *	the median of all authorized differences, and then compute the
 *	median of all differences that are reasonably close to the first
 *	median.
 *
 * This differs from the original BSD implementation, which looked for
 *	the largest group of machines with essentially the same date.
 *	That assumed that machines with bad clocks would be uniformly
 *	distributed.  Unfortunately, in real life networks, the distribution
 *	of machines is not uniform among models of machines, and the
 *	distribution of errors in clocks tends to be quite consistent
 *	for a given model.  In other words, all model VI Supre Servres
 *	from GoFast Inc. tend to have about the same error.
 *	The original BSD implementation would chose the clock of the
 *	most common model, and discard all others.
 *
 *	Therefore, get best we can do is to try to average over all
 *	of the machines in the network, while discarding "obviously"
 *	bad values.
E 7
 */
D 7

long networkdelta()
E 7
I 7
long
networkdelta()
E 7
{
D 7
	int i, j, maxind, minind;
	int ext;
	int tempind;
	long tempdata;
E 7
I 7
	struct hosttbl *htp;
	long med;
	long lodelta, hidelta;
	long logood, higood;
E 7
	long x[NHOSTS];
D 7
	long average;
E 7
I 7
	long *xp;
	int numdelta;
	float eps;
E 7

D 7
	for (i=0; i<slvcount; i++)
		x[i] = hp[i].delta;
	for (i=0; i<slvcount-1; i++) {
		tempdata = x[i];
		tempind = i;
		for (j=i+1; j<slvcount; j++) {
			if (x[j] < tempdata) {
				tempdata = x[j];
				tempind = j;
			}
E 7
I 7
	/*
	 * compute the median of the good values
	 */
	med = 0;
	numdelta = 1;
	xp = &x[0];
	*xp = 0;			/* account for ourself */
	for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
		if (htp->good
		    && htp->noanswer == 0
		    && htp->delta != HOSTDOWN) {
			med += htp->delta;
			numdelta++;
			*++xp = htp->delta;
E 7
		}
D 7
		x[tempind] = x[i];
		x[i] = tempdata;
E 7
	}

D 7
	/* this piece of code is critical: DO NOT TOUCH IT! */
/****/
	i=0; j=1; minind=0; maxind=1;
	if (machup == 2)
		goto compute;
E 7
I 7
	/*
	 * If we are the only trusted time keeper, then do not change our
	 * clock.  There may be another time keeping service active.
	 */
	if (numdelta == 1)
		return 0;

I 9
	/* get average of trusted values */
E 9
	med /= numdelta;
D 9
	eps = med - x[0];
E 9
I 9

E 9
	if (trace)
		fprintf(fd, "median of %d values starting at %ld is about ",
			numdelta, med);
I 9
	/* get median of all trusted values, using average as initial guess */
	eps = med - x[0];
E 9
	med = median(med, &eps, &x[0], xp+1, VALID_RANGE);

D 9
	/*
	 * compute the median of all values near the good median
E 9
I 9
	/* Compute the median of all good values.
	 * Good values are those of all clocks, including untrusted clocks,
	 * that are
	 *	- trusted and somewhat close to the median of the
	 *		trusted clocks
	 *	- trusted or untrusted and very close to the median of the
	 *		trusted clocks
E 9
	 */
	hidelta = med + GOOD_RANGE;
	lodelta = med - GOOD_RANGE;
	higood = med + VGOOD_RANGE;
	logood = med - VGOOD_RANGE;
	xp = &x[0];
	htp = &self;
E 7
	do {
D 7
		if (x[j]-x[i] <= RANGE)
			j++;
		else {
			if (j > i+1) 
 				j--; 
			if ((x[j]-x[i] <= RANGE) && (j-i >= maxind-minind)) {
				minind=i;
				maxind=j;
			}	
			i++;
D 6
			if(i = j)
E 6
I 6
			if(i == j)
E 6
				j++;
E 7
I 7
		if (htp->noanswer == 0
		    && htp->delta >= lodelta
		    && htp->delta <= hidelta
		    && (htp->good
			|| (htp->delta >= logood
			    && htp->delta <= higood))) {
			*xp++ = htp->delta;
E 7
		}
D 7
	} while (j < machup);
	if ((x[machup-1] - x[i] <= RANGE) && (machup-i-1 >= maxind-minind)) {
		minind=i; maxind=machup-1;
E 7
I 7
	} while (&self != (htp = htp->l_fwd));

	if (xp == &x[0]) {
		if (trace)
			fprintf(fd, "nothing close to median %ld\n", med);
		return med;
E 7
	}
D 7
/****/
compute:
	ext = maxind - minind + 1;
	average = 0;
	for (i=minind; i<=maxind; i++)
		average += x[i];
	average /= ext;
	return(average);
E 7
I 7

	if (xp == &x[1]) {
		if (trace)
			fprintf(fd, "only value near median is %ld\n", x[0]);
		return x[0];
	}

	if (trace)
		fprintf(fd, "median of %d values starting at %ld is ",
		        xp-&x[0], med);
	return median(med, &eps, &x[0], xp, 1);
}


/*
 * compute the median of an array of signed integers, using the idea
 *	in <<Numerical Recipes>>.
 */
static long
D 10
median(a, eps_ptr, x, xlim, gnuf)
	float a;			/* initial guess for the median */
E 10
I 10
median(a0, eps_ptr, x, xlim, gnuf)
	double a0;			/* initial guess for the median */
E 10
	float *eps_ptr;			/* spacing near the median */
	long *x, *xlim;			/* the data */
	unsigned int gnuf;		/* good enough estimate */
{
	long *xptr;
I 10
	float a = a0;
E 10
	float ap = LONG_MAX;		/* bounds on the median */
	float am = -LONG_MAX;
	float aa;
	int npts;			/* # of points above & below guess */
	float xp;			/* closet point above the guess */
	float xm;			/* closet point below the guess */
	float eps;
	float dum, sum, sumx;
	int pass;
#define AMP	1.5			/* smoothing constants */
#define AFAC	1.5

	eps = *eps_ptr;
	if (eps < 1.0) {
		eps = -eps;
		if (eps < 1.0)
			eps = 1.0;
	}

	for (pass = 1; ; pass++) {	/* loop over the data */
		sum = 0.0;
		sumx = 0.0;
		npts = 0;
		xp = LONG_MAX;
		xm = -LONG_MAX;

		for (xptr = x; xptr != xlim; xptr++) {
			float xx = *xptr;

			dum = xx - a;
D 9
			if (dum != 0.0) {	/* avoid dividing by 0 */
E 9
I 9
			if (dum != 0.0) {   /* avoid dividing by 0 */
E 9
				if (dum > 0.0) {
					npts++;
					if (xx < xp)
						xp = xx;
				} else {
					npts--;
					if (xx > xm)
						xm = xx;
					dum = -dum;
				}
				dum = 1.0/(eps + dum);
				sum += dum;
				sumx += xx * dum;
			}
		}

		if (ap-am < gnuf || sum == 0) {
			if (trace)
				fprintf(fd,
D 9
			           "%ld in %d passes; early out balance=%d\n",
E 9
I 9
					"%ld in %d passes;"
					" early out balance=%d\n",
E 9
				        (long)a, pass, npts);
			return a;	/* guess was good enough */
		}

		aa = (sumx/sum-a)*AMP;
		if (npts >= 2) {	/* guess was too low */
			am = a;
D 9
			aa = xp + max(0.0, aa);;
			if (aa > ap)
E 9
I 9
			aa = xp + max(0.0, aa);
			if (aa >= ap)
E 9
				aa = (a + ap)/2;

D 9
		} else if (npts <= -2) {  /* guess was two high */
E 9
I 9
		} else if (npts <= -2) {    /* guess was two high */
E 9
			ap = a;
D 9
			aa = xm + min(0.0, aa);;
			if (aa < am)
E 9
I 9
			aa = xm + min(0.0, aa);
			if (aa <= am)
E 9
				aa = (a + am)/2;

		} else {
			break;		/* got it */
		}

		if (a == aa) {
			if (trace)
D 9
				fprintf(fd,
				  "%ld in %d passes; force out balance=%d\n",
E 9
I 9
				fprintf(fd, "%ld in %d passes;"
					" force out balance=%d\n",
E 9
				        (long)a, pass, npts);
			return a;
		}
		eps = AFAC*abs(aa - a);
		*eps_ptr = eps;
		a = aa;
	}

	if (((x - xlim) % 2) != 0) {    /* even number of points? */
		if (npts == 0)		/* yes, return an average */
			a = (xp+xm)/2;
		else if (npts > 0)
			a =  (a+xp)/2;
		else
			a = (xm+a)/2;

D 9
	} else 	if (npts != 0) {	/* odd number of points */
E 9
I 9
	} else if (npts != 0) {		/* odd number of points */
E 9
		if (npts > 0)
			a = xp;
		else
			a = xm;
	}

	if (trace)
		fprintf(fd, "%ld in %d passes\n", (long)a, pass);
	return a;
E 7
}
E 1
