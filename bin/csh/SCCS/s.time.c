h18443
s 00002/00002/00288
d D 8.1 93/05/31 16:43:05 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00290
d D 5.16 93/05/22 19:06:52 christos 22 21
c Fixed gcc -Wall warnings
e
s 00074/00021/00216
d D 5.15 91/07/19 17:31:33 christos 21 20
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/00231
d D 5.14 91/06/08 17:09:09 christos 20 19
c More prototype fixes, Removed TERMIOS define
e
s 00003/00002/00228
d D 5.13 91/06/08 12:20:40 bostic 19 18
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00001/00001/00229
d D 5.12 91/06/07 21:05:51 christos 18 17
c prototype typo fixes
e
s 00004/00010/00226
d D 5.11 91/06/07 20:57:43 christos 17 16
c static function prototypes
e
s 00002/00001/00234
d D 5.10 91/06/07 11:13:48 bostic 16 15
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00142/00094/00093
d D 5.9 91/06/04 13:32:03 bostic 15 14
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00180
d D 5.8 91/04/04 18:17:59 bostic 14 13
c new copyright; att/bsd/shared
e
s 00001/00001/00185
d D 5.7 91/03/14 12:32:56 bostic 13 12
c any -> index (use the faster library routine)
e
s 00002/00002/00184
d D 5.6 88/05/19 15:39:09 bostic 12 11
c install C version of _doprnt
e
s 00012/00012/00174
d D 5.5 87/06/25 09:15:26 bostic 11 10
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00001/00002/00185
d D 5.4 86/05/13 01:07:23 lepreau 10 9
c nice is absolute (note that in 5.2 and before "nice +<num>" was relative.)
e
s 00005/00003/00182
d D 5.3 86/01/12 02:34:21 lepreau 9 8
c nice is relative, not absolute. (Kirk "authorized" it.)
e
s 00003/00003/00182
d D 5.2 85/06/06 13:08:23 edward 8 7
c cleaning up after bozos
e
s 00008/00002/00177
d D 5.1 85/06/04 11:08:28 dist 7 6
c Add copyright
e
s 00008/00010/00171
d D 4.6 84/12/13 14:38:55 edward 6 5
c performance
e
s 00005/00013/00176
d D 4.5 84/10/13 17:35:39 sam 5 4
c fix nice
e
s 00003/00001/00186
d D 4.4 83/08/11 20:13:09 sam 4 3
c standardize sccs keyword lines
e
s 00010/00008/00177
d D 4.3 83/02/03 09:13:16 sam 3 2
c use high precision time calls
e
s 00073/00068/00112
d D 4.2 82/12/30 17:35:50 sam 2 1
c finally works (updated for 4.1c and merged with sun)
e
s 00180/00000/00000
d D 4.1 80/10/09 12:41:59 bill 1 0
c date and time created 80/10/09 12:41:59 by bill
e
u
U
t
T
I 7
D 14
/*
 * Copyright (c) 1980 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
E 8
I 8
 * All rights reserved.  The Berkeley Software License Agreement
E 8
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 23
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
 * %sccs.include.redist.c%
E 14
 */

E 7
I 1
D 2
static	char *sccsid = "%Z%%M% %I% %G%";
E 2
I 2
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
#ifndef lint
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
I 6
D 7
static char *sccsid = "%W% (Berkeley) %G%";
E 6
#endif
E 7
I 7
D 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 8
I 8
D 14
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 14
I 14
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 14
E 8
E 7
E 4
E 2

I 19
#include <sys/types.h>
I 20
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 20
E 19
D 16
#include "sh.h"
E 16
I 16
#include "csh.h"
#include "extern.h"
E 16

/*
 * C Shell - routines handling process timing and niceing
 */
I 15
D 17
static void pdeltat();
E 17
I 17
D 18
static void	pdeltat __P((struct timeval *, struct timevail *));
E 18
I 18
static void	pdeltat __P((struct timeval *, struct timeval *));
E 18
E 17
E 15
D 2
#ifdef VMUNIX
struct	vtimes vm0;
#else
E 2
D 6
struct	tms times0;
struct	tms timesdol;
E 6
D 2
#endif
E 2

I 15
void
E 15
settimes()
{
I 2
D 15
	struct rusage ruch;
E 15
I 15
    struct rusage ruch;
E 15
E 2

D 3
	time(&time0);
E 3
I 3
D 6
	gettimeofday(&time0, (struct timezone *)0);
E 3
D 2
#ifdef VMUNIX
	vtimes(&vm0, 0);
#else
	times(&times0);
#endif
E 2
I 2
	getrusage(RUSAGE_SELF, &ru0);
	getrusage(RUSAGE_CHILDREN, &ruch);
E 6
I 6
D 15
	(void) gettimeofday(&time0, (struct timezone *)0);
	(void) getrusage(RUSAGE_SELF, &ru0);
	(void) getrusage(RUSAGE_CHILDREN, &ruch);
E 6
	ruadd(&ru0, &ruch);
E 15
I 15
D 19
    (void) gettimeofday(&time0, (struct timezone *) 0);
E 19
I 19
    (void) gettimeofday(&time0, NULL);
E 19
    (void) getrusage(RUSAGE_SELF, &ru0);
    (void) getrusage(RUSAGE_CHILDREN, &ruch);
    ruadd(&ru0, &ruch);
E 15
E 2
}

/*
 * dotime is only called if it is truly a builtin function and not a
 * prefix to another command
 */
I 15
void
E 15
D 21
dotime()
E 21
I 21
/*ARGSUSED*/
dotime(v, t)
    Char **v;
    struct command *t;
E 21
{
D 3
	time_t timedol;
E 3
I 3
D 15
	struct timeval timedol;
E 3
D 2
#ifdef VMUNIX
	struct vtimes vm1, vmch;
E 2
I 2
	struct rusage ru1, ruch;
E 15
I 15
    struct timeval timedol;
    struct rusage ru1, ruch;
E 15
E 2

D 2
	vtimes(&vm1, &vmch);
	vmsadd(&vm1, &vmch);
#endif

E 2
I 2
D 6
	getrusage(RUSAGE_SELF, &ru1);
	getrusage(RUSAGE_CHILDREN, &ruch);
E 6
I 6
D 15
	(void) getrusage(RUSAGE_SELF, &ru1);
	(void) getrusage(RUSAGE_CHILDREN, &ruch);
E 6
	ruadd(&ru1, &ruch);
E 2
D 3
	time(&timedol);
D 2
#ifdef VMUNIX
	pvtimes(&vm0, &vm1, timedol - time0);
#else
	times(&timesdol);
	ptimes(timedol - time0, &times0, &timesdol);
#endif
E 2
I 2
	prusage(&ru0, &ru1, timedol - time0);
E 3
I 3
D 6
	gettimeofday(&timedol, (struct timezone *)0);
E 6
I 6
	(void) gettimeofday(&timedol, (struct timezone *)0);
E 6
	prusage(&ru0, &ru1, &timedol, &time0);
E 15
I 15
    (void) getrusage(RUSAGE_SELF, &ru1);
    (void) getrusage(RUSAGE_CHILDREN, &ruch);
    ruadd(&ru1, &ruch);
D 19
    (void) gettimeofday(&timedol, (struct timezone *) 0);
E 19
I 19
    (void) gettimeofday(&timedol, NULL);
E 19
    prusage(&ru0, &ru1, &timedol, &time0);
E 15
E 3
E 2
}

/*
 * donice is only called when it on the line by itself or with a +- value
 */
I 15
void
E 15
D 21
donice(v)
D 15
	register char **v;
E 15
I 15
    register Char **v;
E 21
I 21
/*ARGSUSED*/
donice(v, t)
    Char **v;
    struct command *t;
E 21
E 15
{
D 15
	register char *cp;
I 9
	int nval;
E 15
I 15
    register Char *cp;
    int     nval = 0;
E 15
E 9

D 15
	v++, cp = *v++;
D 5
	if (cp == 0) {
#ifndef V6
		nice(20);
		nice(-10);
#endif
		nice(4);
	} else if (*v == 0 && any(cp[0], "+-")) {
#ifndef V6
		nice(20);
		nice(-10);
#endif
		nice(getn(cp));
	}
E 5
I 5
	if (cp == 0)
D 9
		(void) setpriority(PRIO_PROCESS, 0, 4);
E 9
I 9
		nval = 4;
E 9
D 13
	else if (*v == 0 && any(cp[0], "+-"))
E 13
I 13
	else if (*v == 0 && index("+-", cp[0]))
E 13
D 9
		(void) setpriority(PRIO_PROCESS, 0, 
		    getpriority(PRIO_PROCESS, 0) + getn(cp));
E 9
I 9
		nval = getn(cp);
D 10
	(void) setpriority(PRIO_PROCESS, 0,
		getpriority(PRIO_PROCESS, 0) + nval);
E 10
I 10
	(void) setpriority(PRIO_PROCESS, 0, nval);
E 15
I 15
    v++, cp = *v++;
    if (cp == 0)
	nval = 4;
    else if (*v == 0 && any("+-", cp[0]))
	nval = getn(cp);
    (void) setpriority(PRIO_PROCESS, 0, nval);
E 15
E 10
E 9
E 5
}

I 15
void
E 15
D 2
#ifndef VMUNIX
ptimes(utime, stime, etime)
	register time_t utime, stime, etime;
E 2
I 2
ruadd(ru, ru2)
D 15
	register struct rusage *ru, *ru2;
E 15
I 15
    register struct rusage *ru, *ru2;
E 15
E 2
{
I 2
D 15
	register long *lp, *lp2;
	register int cnt;
E 15
I 15
    tvadd(&ru->ru_utime, &ru2->ru_utime);
    tvadd(&ru->ru_stime, &ru2->ru_stime);
    if (ru2->ru_maxrss > ru->ru_maxrss)
	ru->ru_maxrss = ru2->ru_maxrss;
E 15
E 2

D 2
	p60ths(utime);
	printf("u ");
	p60ths(stime);
	printf("s ");
	psecs(etime);
	printf(" %d%%\n", (int) (100 * (utime+stime) /
		(60 * (etime ? etime : 1))));
E 2
I 2
D 15
	tvadd(&ru->ru_utime, &ru2->ru_utime);
	tvadd(&ru->ru_stime, &ru2->ru_stime);
	if (ru2->ru_maxrss > ru->ru_maxrss)
		ru->ru_maxrss = ru2->ru_maxrss;
	cnt = &ru->ru_last - &ru->ru_first + 1;
	lp = &ru->ru_first; lp2 = &ru2->ru_first;
	do
		*lp++ += *lp2++;
	while (--cnt > 0);
E 15
I 15
    ru->ru_ixrss += ru2->ru_ixrss;
    ru->ru_idrss += ru2->ru_idrss;
    ru->ru_isrss += ru2->ru_isrss;
    ru->ru_minflt += ru2->ru_minflt;
    ru->ru_majflt += ru2->ru_majflt;
    ru->ru_nswap += ru2->ru_nswap;
    ru->ru_inblock += ru2->ru_inblock;
    ru->ru_oublock += ru2->ru_oublock;
    ru->ru_msgsnd += ru2->ru_msgsnd;
    ru->ru_msgrcv += ru2->ru_msgrcv;
    ru->ru_nsignals += ru2->ru_nsignals;
    ru->ru_nvcsw += ru2->ru_nvcsw;
    ru->ru_nivcsw += ru2->ru_nivcsw;
E 15
E 2
}

I 15
void
E 15
D 2
#else
vmsadd(vp, wp)
	register struct vtimes *vp, *wp;
{

	vp->vm_utime += wp->vm_utime;
	vp->vm_stime += wp->vm_stime;
	vp->vm_nswap += wp->vm_nswap;
	vp->vm_idsrss += wp->vm_idsrss;
	vp->vm_ixrss += wp->vm_ixrss;
	if (vp->vm_maxrss < wp->vm_maxrss)
		vp->vm_maxrss = wp->vm_maxrss;
	vp->vm_majflt += wp->vm_majflt;
	vp->vm_minflt += wp->vm_minflt;
	vp->vm_inblk += wp->vm_inblk;
	vp->vm_oublk += wp->vm_oublk;
}

pvtimes(v0, v1, sec)
	register struct vtimes *v0, *v1;
E 2
I 2
D 3
prusage(r0, r1, sec)
E 3
I 3
prusage(r0, r1, e, b)
E 3
D 15
	register struct rusage *r0, *r1;
E 2
D 3
	time_t sec;
E 3
I 3
	struct timeval *e, *b;
E 15
I 15
    register struct rusage *r0, *r1;
    struct timeval *e, *b;
E 15
E 3
{
D 15
	register time_t t =
D 2
	    (v1->vm_utime-v0->vm_utime)+(v1->vm_stime-v0->vm_stime);
E 2
I 2
	    (r1->ru_utime.tv_sec-r0->ru_utime.tv_sec)*100+
	    (r1->ru_utime.tv_usec-r0->ru_utime.tv_usec)/10000+
	    (r1->ru_stime.tv_sec-r0->ru_stime.tv_sec)*100+
	    (r1->ru_stime.tv_usec-r0->ru_stime.tv_usec)/10000;
E 2
	register char *cp;
D 11
	register int i;
E 11
I 11
	register long i;
E 11
	register struct varent *vp = adrof("time");
I 3
D 11
	int ms =
E 11
I 11
	long ms =
E 11
	    (e->tv_sec-b->tv_sec)*100 + (e->tv_usec-b->tv_usec)/10000;
E 15
I 15
    register time_t t =
    (r1->ru_utime.tv_sec - r0->ru_utime.tv_sec) * 100 +
    (r1->ru_utime.tv_usec - r0->ru_utime.tv_usec) / 10000 +
    (r1->ru_stime.tv_sec - r0->ru_stime.tv_sec) * 100 +
    (r1->ru_stime.tv_usec - r0->ru_stime.tv_usec) / 10000;
    register char *cp;
    register long i;
    register struct varent *vp = adrof(STRtime);
E 15
E 3

D 15
	cp = "%Uu %Ss %E %P %X+%Dk %I+%Oio %Fpf+%Ww";
	if (vp && vp->vec[0] && vp->vec[1])
		cp = vp->vec[1];
	for (; *cp; cp++)
E 15
I 15
    int     ms =
    (e->tv_sec - b->tv_sec) * 100 + (e->tv_usec - b->tv_usec) / 10000;

    cp = "%Uu %Ss %E %P %X+%Dk %I+%Oio %Fpf+%Ww";
D 17
#ifdef TDEBUG
    xprintf("es->tms_utime %lu bs->tms_utime %lu\n",
	    es->tms_utime, bs->tms_utime);
    xprintf("es->tms_stime %lu bs->tms_stime %lu\n",
	    es->tms_stime, bs->tms_stime);
    xprintf("ms %lu e %lu b %lu\n", ms, e, b);
    xprintf("t %lu\n", t);
#endif				/* TDEBUG */
E 17

    if (vp && vp->vec[0] && vp->vec[1])
	cp = short2str(vp->vec[1]);
I 17

E 17
    for (; *cp; cp++)
E 15
	if (*cp != '%')
D 12
		putchar(*cp);
E 12
I 12
D 15
		cshputchar(*cp);
E 12
	else if (cp[1]) switch(*++cp) {
E 15
I 15
D 21
	    xputchar(*cp);
E 21
I 21
	    (void) fputc(*cp, cshout);
E 21
	else if (cp[1])
	    switch (*++cp) {
E 15

D 15
	case 'U':
E 15
I 15
	    case 'U':		/* user CPU time used */
E 15
D 2
		p60ths(v1->vm_utime - v0->vm_utime);
E 2
I 2
		pdeltat(&r1->ru_utime, &r0->ru_utime);
E 2
		break;

D 15
	case 'S':
E 15
I 15
	    case 'S':		/* system CPU time used */
E 15
D 2
		p60ths(v1->vm_stime - v0->vm_stime);
E 2
I 2
		pdeltat(&r1->ru_stime, &r0->ru_stime);
E 2
		break;

D 15
	case 'E':
D 3
		psecs(sec);
E 3
I 3
D 6
		psecs(ms / 100);
E 6
I 6
D 11
		psecs((long)(ms / 100));
E 11
I 11
		psecs(ms / 100);
E 15
I 15
	    case 'E':		/* elapsed (wall-clock) time */
		pcsecs((long) ms);
E 15
E 11
E 6
E 3
		break;

D 15
	case 'P':
D 2
		printf("%d%%", (int) ((100 * t) / (60 * (sec ? sec : 1))));
E 2
I 2
D 3
		printf("%d%%", (int) (t / ((sec ? sec : 1))));
E 3
I 3
		printf("%d%%", (int) (t*100 / ((ms ? ms : 1))));
E 15
I 15
	    case 'P':		/* percent time spent running */
D 17
		i = (int) (t * 1000 / ((ms ? ms : 1)));
E 17
I 17
		/* check if it did not run at all */
		i = (ms == 0) ? 0 : (t * 1000 / ms);
E 17
D 21
		xprintf("%ld.%01ld%%", i / 10, i % 10);	/* nn.n% */
E 21
I 21
		/* nn.n% */
		(void) fprintf(cshout, "%ld.%01ld%%", i / 10, i % 10);
E 21
E 15
E 3
E 2
		break;

D 15
	case 'W':
E 15
I 15
	    case 'W':		/* number of swaps */
E 15
D 2
		i = v1->vm_nswap - v0->vm_nswap;
E 2
I 2
		i = r1->ru_nswap - r0->ru_nswap;
E 2
D 11
		printf("%d", i);
E 11
I 11
D 15
		printf("%ld", i);
E 15
I 15
D 21
		xprintf("%ld", i);
E 21
I 21
		(void) fprintf(cshout, "%ld", i);
E 21
E 15
E 11
		break;

D 15
	case 'X':
D 2
		printf("%d", t == 0 ? 0 : (v1->vm_ixrss-v0->vm_ixrss)/(2*t));
E 2
I 2
D 11
		printf("%d", t == 0 ? 0 : (r1->ru_ixrss-r0->ru_ixrss)/t);
E 11
I 11
		printf("%ld", t == 0 ? 0L : (r1->ru_ixrss-r0->ru_ixrss)/t);
E 15
I 15
	    case 'X':		/* (average) shared text size */
D 21
		xprintf("%ld", t == 0 ? 0L : (r1->ru_ixrss - r0->ru_ixrss) / t);
E 21
I 21
		(void) fprintf(cshout, "%ld", t == 0 ? 0L : 
			       (r1->ru_ixrss - r0->ru_ixrss) / t);
E 21
E 15
E 11
E 2
		break;

D 15
	case 'D':
D 2
		printf("%d", t == 0 ? 0 : (v1->vm_idsrss-v0->vm_idsrss)/(2*t));
E 2
I 2
D 11
		printf("%d", t == 0 ? 0 :
E 11
I 11
		printf("%ld", t == 0 ? 0L :
E 11
		    (r1->ru_idrss+r1->ru_isrss-(r0->ru_idrss+r0->ru_isrss))/t);
E 15
I 15
	    case 'D':		/* (average) unshared data size */
D 21
		xprintf("%ld", t == 0 ? 0L :
E 21
I 21
		(void) fprintf(cshout, "%ld", t == 0 ? 0L :
E 21
			(r1->ru_idrss + r1->ru_isrss -
			 (r0->ru_idrss + r0->ru_isrss)) / t);
E 15
E 2
		break;

D 15
	case 'K':
D 2
		printf("%d", t == 0 ? 0 : ((v1->vm_ixrss+v1->vm_idsrss) -
		   (v0->vm_ixrss+v0->vm_idsrss))/(2*t));
E 2
I 2
D 11
		printf("%d", t == 0 ? 0 :
E 11
I 11
		printf("%ld", t == 0 ? 0L :
E 11
		    ((r1->ru_ixrss+r1->ru_isrss+r1->ru_idrss) -
		    (r0->ru_ixrss+r0->ru_idrss+r0->ru_isrss))/t);
E 15
I 15
	    case 'K':		/* (average) total data memory used  */
D 21
		xprintf("%ld", t == 0 ? 0L :
E 21
I 21
		(void) fprintf(cshout, "%ld", t == 0 ? 0L :
E 21
			((r1->ru_ixrss + r1->ru_isrss + r1->ru_idrss) -
			 (r0->ru_ixrss + r0->ru_idrss + r0->ru_isrss)) / t);
E 15
E 2
		break;

D 15
	case 'M':
D 2
		printf("%d", v1->vm_maxrss/2);
E 2
I 2
D 11
		printf("%d", r1->ru_maxrss/2);
E 11
I 11
		printf("%ld", r1->ru_maxrss/2);
E 15
I 15
	    case 'M':		/* max. Resident Set Size */
D 21
		xprintf("%ld", r1->ru_maxrss / 2L);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_maxrss / 2L);
E 21
E 15
E 11
E 2
		break;

D 15
	case 'F':
D 2
		printf("%d", v1->vm_majflt-v0->vm_majflt);
E 2
I 2
D 11
		printf("%d", r1->ru_majflt-r0->ru_majflt);
E 11
I 11
		printf("%ld", r1->ru_majflt-r0->ru_majflt);
E 15
I 15
	    case 'F':		/* page faults */
D 21
		xprintf("%ld", r1->ru_majflt - r0->ru_majflt);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_majflt - r0->ru_majflt);
E 21
E 15
E 11
E 2
		break;

D 15
	case 'R':
D 2
		printf("%d", v1->vm_minflt-v0->vm_minflt);
E 2
I 2
D 11
		printf("%d", r1->ru_minflt-r0->ru_minflt);
E 11
I 11
		printf("%ld", r1->ru_minflt-r0->ru_minflt);
E 15
I 15
	    case 'R':		/* page reclaims */
D 21
		xprintf("%ld", r1->ru_minflt - r0->ru_minflt);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_minflt - r0->ru_minflt);
E 21
E 15
E 11
E 2
		break;

D 15
	case 'I':
D 2
		printf("%d", v1->vm_inblk-v0->vm_inblk);
E 2
I 2
D 11
		printf("%d", r1->ru_inblock-r0->ru_inblock);
E 11
I 11
		printf("%ld", r1->ru_inblock-r0->ru_inblock);
E 15
I 15
	    case 'I':		/* FS blocks in */
D 21
		xprintf("%ld", r1->ru_inblock - r0->ru_inblock);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_inblock - r0->ru_inblock);
E 21
E 15
E 11
E 2
		break;

D 15
	case 'O':
D 2
		printf("%d", v1->vm_oublk-v0->vm_oublk);
E 2
I 2
D 11
		printf("%d", r1->ru_oublock-r0->ru_oublock);
E 11
I 11
		printf("%ld", r1->ru_oublock-r0->ru_oublock);
E 15
I 15
	    case 'O':		/* FS blocks out */
D 21
		xprintf("%ld", r1->ru_oublock - r0->ru_oublock);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_oublock - r0->ru_oublock);
E 21
E 15
E 11
E 2
		break;
D 2

E 2
D 15
	}
D 12
	putchar('\n');
E 12
I 12
	cshputchar('\n');
E 15
I 15

	    case 'r':		/* socket messages recieved */
D 21
		xprintf("%ld", r1->ru_msgrcv - r0->ru_msgrcv);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_msgrcv - r0->ru_msgrcv);
E 21
		break;

	    case 's':		/* socket messages sent */
D 21
		xprintf("%ld", r1->ru_msgsnd - r0->ru_msgsnd);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_msgsnd - r0->ru_msgsnd);
E 21
		break;

	    case 'k':		/* number of signals recieved */
D 21
		xprintf("%ld", r1->ru_nsignals - r0->ru_nsignals);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_nsignals-r0->ru_nsignals);
E 21
		break;

	    case 'w':		/* num. voluntary context switches (waits) */
D 21
		xprintf("%ld", r1->ru_nvcsw - r0->ru_nvcsw);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_nvcsw - r0->ru_nvcsw);
E 21
		break;

	    case 'c':		/* num. involuntary context switches */
D 21
		xprintf("%ld", r1->ru_nivcsw - r0->ru_nivcsw);
E 21
I 21
		(void) fprintf(cshout, "%ld", r1->ru_nivcsw - r0->ru_nivcsw);
E 21
		break;
	    }
D 21
    xputchar('\n');
E 21
I 21
    (void) fputc('\n', cshout);
E 21
E 15
E 12
}
D 2
#endif
E 2
I 2

I 15
static void
E 15
pdeltat(t1, t0)
D 15
	struct timeval *t1, *t0;
E 15
I 15
    struct timeval *t1, *t0;
E 15
{
D 15
	struct timeval td;
E 15
I 15
    struct timeval td;
E 15

D 15
	tvsub(&td, t1, t0);
	printf("%d.%01d", td.tv_sec, td.tv_usec/100000);
E 15
I 15
    tvsub(&td, t1, t0);
D 21
    xprintf("%d.%01d", td.tv_sec, td.tv_usec / 100000);
E 21
I 21
    (void) fprintf(cshout, "%d.%01d", td.tv_sec, td.tv_usec / 100000);
E 21
E 15
}

I 15
void
E 15
tvadd(tsum, t0)
D 15
	struct timeval *tsum, *t0;
E 15
I 15
    struct timeval *tsum, *t0;
E 15
{

D 15
	tsum->tv_sec += t0->tv_sec;
	tsum->tv_usec += t0->tv_usec;
	if (tsum->tv_usec > 1000000)
		tsum->tv_sec++, tsum->tv_usec -= 1000000;
E 15
I 15
    tsum->tv_sec += t0->tv_sec;
    tsum->tv_usec += t0->tv_usec;
    if (tsum->tv_usec > 1000000)
	tsum->tv_sec++, tsum->tv_usec -= 1000000;
E 15
}

I 15
void
E 15
tvsub(tdiff, t1, t0)
D 15
	struct timeval *tdiff, *t1, *t0;
E 15
I 15
    struct timeval *tdiff, *t1, *t0;
E 15
{

D 15
	tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
	tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	if (tdiff->tv_usec < 0)
		tdiff->tv_sec--, tdiff->tv_usec += 1000000;
E 15
I 15
    tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
    tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
    if (tdiff->tv_usec < 0)
	tdiff->tv_sec--, tdiff->tv_usec += 1000000;
I 21
}

#define  P2DIG(i) (void) fprintf(cshout, "%d%d", (i) / 10, (i) % 10)

void
psecs(l)
    long    l;
{
    register int i;

    i = l / 3600;
    if (i) {
	(void) fprintf(cshout, "%d:", i);
	i = l % 3600;
	P2DIG(i / 60);
	goto minsec;
    }
    i = l;
    (void) fprintf(cshout, "%d", i / 60);
minsec:
    i %= 60;
    (void) fputc(':', cshout);
    P2DIG(i);
}

void
pcsecs(l)			/* PWP: print mm:ss.dd, l is in sec*100 */
    long    l;
{
    register int i;

    i = l / 360000;
    if (i) {
	(void) fprintf(cshout, "%d:", i);
	i = (l % 360000) / 100;
	P2DIG(i / 60);
	goto minsec;
    }
    i = l / 100;
    (void) fprintf(cshout, "%d", i / 60);
minsec:
    i %= 60;
    (void) fputc(':', cshout);
    P2DIG(i);
    (void) fputc('.', cshout);
    P2DIG((int) (l % 100));
E 21
E 15
}
E 2
E 1
