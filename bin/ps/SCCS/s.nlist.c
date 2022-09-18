h65323
s 00001/00001/00109
d D 8.4 94/04/02 10:01:13 pendry 12 11
c add 1994 copyright
e
s 00000/00001/00110
d D 8.3 94/04/02 09:58:34 pendry 11 10
c prettyness police
e
s 00001/00001/00110
d D 8.2 93/09/23 19:08:45 bostic 10 9
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00109
d D 8.1 93/05/31 15:05:41 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00009/00099
d D 5.8 93/04/29 13:17:52 bostic 8 7
c use err/warn from C library
e
s 00007/00003/00101
d D 5.7 92/06/05 18:56:53 bostic 7 6
c ANSI prototypes (two real bugs)
e
s 00010/00007/00094
d D 5.6 92/04/03 14:55:41 mckusick 6 5
c update from Steve McCanne for Sun compatible kvm
e
s 00013/00001/00088
d D 5.5 91/07/01 18:00:08 marc 5 4
c print better error message if nlist fails
e
s 00035/00007/00054
d D 5.4 91/07/01 17:01:21 karels 4 3
c newvm changes for memory size
e
s 00001/00001/00060
d D 5.3 91/07/01 15:41:15 bostic 3 2
c print out kvm error message, not errno message
e
s 00001/00001/00060
d D 5.2 91/06/03 16:55:39 bostic 2 1
c fix err routine, make everyone use it; minor ANSI cleanups
e
s 00061/00000/00000
d D 5.1 91/02/08 10:58:15 bostic 1 0
c Put print/keyword routines into separate modules; delete attime.c, use
c strftime(3) instead; put combination keywords into main keyword list,
c sort, delete aliases, and use bsearch(3); don't fail if nlist fails or
c devices aren't found.  Whack the manual page for consistency, correctness.
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 12
 * Copyright (c) 1990, 1993
E 12
I 12
 * Copyright (c) 1990, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
#include <sys/time.h>
#include <sys/proc.h>
I 7
#include <sys/resource.h>
E 7
E 4
D 8
#include <nlist.h>
E 8
I 8

#include <err.h>
E 8
#include <errno.h>
I 8
#include <kvm.h>
#include <nlist.h>
E 8
#include <stdio.h>
I 2
#include <string.h>
I 6
D 8
#include <kvm.h>
E 8
I 8

E 8
I 7
#include "ps.h"
E 7
E 6
E 2

I 4
D 10
#ifdef SPPWAIT
E 10
I 10
#ifdef P_PPWAIT
E 10
#define NEWVM
#endif

E 4
struct	nlist psnl[] = {
D 4
	{"_ecmx"},
#define	X_ECMX		0
E 4
	{"_fscale"},
D 4
#define	X_FSCALE	1
E 4
I 4
#define	X_FSCALE	0
E 4
	{"_ccpu"},
D 4
#define	X_CCPU		2
E 4
I 4
#define	X_CCPU		1
#ifdef NEWVM
	{"_avail_start"},
#define	X_AVAILSTART	2
	{"_avail_end"},
#define	X_AVAILEND	3
#else
	{"_ecmx"},
#define	X_ECMX		2
#endif
E 4
	{NULL}
};

fixpt_t	ccpu;				/* kernel _ccpu variable */
int	nlistread;			/* if nlist already read. */
D 4
int	ecmx;				/* kernel _ecmx variable */
E 4
I 4
int	mempages;			/* number of pages of phys. memory */
E 4
int	fscale;				/* kernel _fscale variable */

I 6
extern kvm_t *kd;

E 6
#define kread(x, v) \
D 6
	kvm_read(psnl[x].n_value, (char *)&v, sizeof v) != sizeof(v)
E 6
I 6
	kvm_read(kd, psnl[x].n_value, (char *)&v, sizeof v) != sizeof(v)
E 6

I 7
int
E 7
donlist()
{
D 11
	extern int eval;
E 11
	int rval;
I 4
#ifdef NEWVM
	int tmp;
#endif
E 4

	rval = 0;
	nlistread = 1;
D 6
	if (kvm_nlist(psnl)) {
E 6
I 6
	if (kvm_nlist(kd, psnl)) {
E 6
D 3
		(void)fprintf(stderr, "ps: kvm_nlist: %s\n", strerror(errno));
E 3
I 3
D 5
		(void)fprintf(stderr, "ps: kvm_nlist: %s\n", kvm_geterr());
E 5
I 5
		nlisterr(psnl);
E 5
E 3
		eval = 1;
D 8
		return(1);
E 8
I 8
		return (1);
E 8
	}
	if (kread(X_FSCALE, fscale)) {
D 6
		(void)fprintf(stderr, "ps: fscale: %s\n", kvm_geterr());
E 6
I 6
D 8
		(void)fprintf(stderr, "ps: fscale: %s\n", kvm_geterr(kd));
E 8
I 8
		warnx("fscale: %s", kvm_geterr(kd));
E 8
E 6
		eval = rval = 1;
	}
D 4
	if (kread(X_ECMX, ecmx)) {
E 4
I 4
#ifdef NEWVM
	if (kread(X_AVAILEND, mempages)) {
D 6
		(void)fprintf(stderr, "ps: avail_start: %s\n", kvm_geterr());
E 6
I 6
D 8
		(void)fprintf(stderr, "ps: avail_start: %s\n", kvm_geterr(kd));
E 8
I 8
		warnx("avail_start: %s", kvm_geterr(kd));
E 8
E 6
		eval = rval = 1;
	}
	if (kread(X_AVAILSTART, tmp)) {
D 6
		(void)fprintf(stderr, "ps: avail_end: %s\n", kvm_geterr());
E 6
I 6
D 8
		(void)fprintf(stderr, "ps: avail_end: %s\n", kvm_geterr(kd));
E 8
I 8
		warnx("avail_end: %s", kvm_geterr(kd));
E 8
E 6
		eval = rval = 1;
	}
	mempages -= tmp;
#else
	if (kread(X_ECMX, mempages)) {
E 4
D 6
		(void)fprintf(stderr, "ps: ecmx: %s\n", kvm_geterr());
E 6
I 6
D 8
		(void)fprintf(stderr, "ps: ecmx: %s\n", kvm_geterr(kd));
E 8
I 8
		warnx("ecmx: %s", kvm_geterr(kd));
E 8
E 6
		eval = rval = 1;
	}
I 4
#endif
E 4
	if (kread(X_CCPU, ccpu)) {
D 6
		(void)fprintf(stderr, "ps: ccpu: %s\n", kvm_geterr());
E 6
I 6
D 8
		(void)fprintf(stderr, "ps: ccpu: %s\n", kvm_geterr(kd));
E 8
I 8
		warnx("ccpu: %s", kvm_geterr(kd));
E 8
E 6
		eval = rval = 1;
	}
D 8
	return(rval);
E 8
I 8
	return (rval);
E 8
I 5
}

I 7
void
E 7
nlisterr(nl)
	struct nlist nl[];
{
	int i;

D 7
	fprintf(stderr, "ps: nlist: can't find following symbols:");
E 7
I 7
	(void)fprintf(stderr, "ps: nlist: can't find following symbols:");
E 7
	for (i = 0; nl[i].n_name != NULL; i++)
		if (nl[i].n_value == 0)
D 7
			fprintf(stderr, " %s", nl[i].n_name);
	fprintf(stderr, "\n");
E 7
I 7
			(void)fprintf(stderr, " %s", nl[i].n_name);
	(void)fprintf(stderr, "\n");
E 7
E 5
}
D 2

E 2
E 1
