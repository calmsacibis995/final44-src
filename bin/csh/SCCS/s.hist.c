h27089
s 00006/00002/00156
d D 8.2 95/03/22 14:12:39 christos 24 23
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/00156
d D 8.1 93/05/31 16:42:21 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00157
d D 5.11 93/05/22 19:06:36 christos 22 21
c Fixed gcc -Wall warnings
e
s 00024/00046/00134
d D 5.10 91/07/19 17:31:04 christos 21 20
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/00174
d D 5.9 91/06/08 17:08:50 christos 20 19
c More prototype fixes, Removed TERMIOS define
e
s 00003/00001/00171
d D 5.8 91/06/08 12:20:24 bostic 19 18
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00003/00003/00169
d D 5.7 91/06/07 20:57:28 christos 18 17
c static function prototypes
e
s 00002/00001/00170
d D 5.6 91/06/07 11:13:30 bostic 17 16
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00124/00096/00047
d D 5.5 91/06/04 13:31:38 bostic 16 15
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00136
d D 5.4 91/04/04 18:17:46 bostic 15 14
c new copyright; att/bsd/shared
e
s 00001/00001/00141
d D 5.3 87/06/25 09:15:18 bostic 14 13
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00003/00003/00139
d D 5.2 85/06/06 13:08:40 edward 13 12
c cleaning up after bozos
e
s 00008/00002/00134
d D 5.1 85/06/04 11:00:03 dist 12 11
c Add copyright
e
s 00017/00007/00119
d D 4.10 85/03/19 18:30:51 mckusick 11 10
c better argument cracking
e
s 00020/00017/00106
d D 4.9 84/12/13 14:39:13 edward 10 9
c performance
e
s 00003/00006/00120
d D 4.8 84/10/15 10:00:07 ralph 9 8
c don't loop if option unknown (history -x).
e
s 00001/00001/00125
d D 4.7 84/08/31 09:30:59 ralph 8 7
c use new signal calls instead of compatibility routines.
e
s 00001/00001/00125
d D 4.6 83/06/11 16:49:39 sam 7 6
c different approach, try signal compatibility package
e
s 00001/00001/00125
d D 4.5 83/06/10 23:59:23 sam 6 5
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00001/00001/00125
d D 4.4 82/12/30 17:35:18 sam 5 4
c finally works (updated for 4.1c and merged with sun)
e
s 00015/00015/00111
d D 4.3 81/11/19 21:04:04 mckusic 4 2
c add ``history -h >file'' and ``source -h file'' to 
c implement history save and restore.
e
s 00003/00003/00123
d R 4.3 81/08/20 23:47:45 mckusic 3 2
c put in history save and restore
e
s 00019/00011/00107
d D 4.2 81/08/18 17:00:37 mckusic 2 1
c save history in ~/.history at logout and restore at login
e
s 00118/00000/00000
d D 4.1 80/10/09 12:41:10 bill 1 0
c date and time created 80/10/09 12:41:10 by bill
e
u
U
t
T
I 12
D 15
/*
 * Copyright (c) 1980 Regents of the University of California.
D 13
 * All rights reserved.  The Berkeley software License Agreement
E 13
I 13
 * All rights reserved.  The Berkeley Software License Agreement
E 13
 * specifies the terms and conditions for redistribution.
E 15
I 15
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
E 15
 */

E 12
I 1
D 10
static	char *sccsid = "%Z%%M% %I% %G%";
E 10
I 10
#ifndef lint
D 12
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 12
I 12
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 13
I 13
D 15
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 15
I 15
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 15
E 13
E 12
E 10

I 19
#include <sys/types.h>
#include <stdlib.h>
I 20
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 20
E 19
D 17
#include "sh.h"
E 17
I 17
#include "csh.h"
#include "extern.h"
E 17

D 16
/*
 * C shell
 */
E 16
I 16
D 18
static void hfree();
static void dohist1();
static void phist();
E 18
I 18
static void	hfree __P((struct Hist *));
D 21
static void	dohist1 __P((struct Hist *, int *, int, int, int));
static void	phist __P((struct Hist *, int, int));
E 21
I 21
static void	dohist1 __P((struct Hist *, int *, int, int));
static void	phist __P((struct Hist *, int));
E 21
E 18
E 16

I 16
void
E 16
savehist(sp)
D 16
	struct wordent *sp;
E 16
I 16
    struct wordent *sp;
E 16
{
D 16
	register struct Hist *hp, *np;
D 10
	int histlen;
	register char *cp;
E 10
I 10
	register int histlen = 0;
	char *cp;
E 16
I 16
    register struct Hist *hp, *np;
    register int histlen = 0;
    Char   *cp;
E 16
E 10

D 10
	cp = value("history");
	if (*cp == 0)
		histlen = 0;
	else {
		while (*cp && digit(*cp))
			cp++;
		/* avoid a looping snafu */
		if (*cp)
			set("history", "10");
		histlen = getn(value("history"));
	}
E 10
D 16
	/* throw away null lines */
	if (sp->next->word[0] == '\n')
		return;
I 10
	cp = value("history");
	if (*cp) {
		register char *p = cp;
E 16
I 16
    /* throw away null lines */
    if (sp->next->word[0] == '\n')
	return;
    cp = value(STRhistory);
    if (*cp) {
	register Char *p = cp;
E 16

D 16
		while (*p) {
			if (!digit(*p)) {
				histlen = 0;
				break;
			}
			histlen = histlen * 10 + *p++ - '0';
		}
E 16
I 16
	while (*p) {
	    if (!Isdigit(*p)) {
		histlen = 0;
		break;
	    }
	    histlen = histlen * 10 + *p++ - '0';
E 16
	}
E 10
D 16
	for (hp = &Histlist; np = hp->Hnext;)
		if (eventno - np->Href >= histlen || histlen == 0)
			hp->Hnext = np->Hnext, hfree(np);
		else
			hp = np;
D 10
	enthist(++eventno, sp, 1);
E 10
I 10
	(void) enthist(++eventno, sp, 1);
E 16
I 16
    }
D 22
    for (hp = &Histlist; np = hp->Hnext;)
E 22
I 22
    for (hp = &Histlist; (np = hp->Hnext) != NULL;)
E 22
	if (eventno - np->Href >= histlen || histlen == 0)
	    hp->Hnext = np->Hnext, hfree(np);
	else
	    hp = np;
    (void) enthist(++eventno, sp, 1);
E 16
E 10
}

struct Hist *
enthist(event, lp, docopy)
D 16
	int event;
	register struct wordent *lp;
	bool docopy;
E 16
I 16
    int     event;
    register struct wordent *lp;
    bool    docopy;
E 16
{
D 16
	register struct Hist *np;
E 16
I 16
    register struct Hist *np;
E 16

D 10
	np = (struct Hist *) calloc(1, sizeof *np);
E 10
I 10
D 16
	np = (struct Hist *) xalloc(sizeof *np);
E 10
	np->Hnum = np->Href = event;
	if (docopy)
		copylex(&np->Hlex, lp);
	else {
		np->Hlex.next = lp->next;
		lp->next->prev = &np->Hlex;
		np->Hlex.prev = lp->prev;
		lp->prev->next = &np->Hlex;
	}
	np->Hnext = Histlist.Hnext;
	Histlist.Hnext = np;
	return (np);
E 16
I 16
    np = (struct Hist *) xmalloc((size_t) sizeof(*np));
D 21
    (void) time(&(np->Htime));
E 21
    np->Hnum = np->Href = event;
    if (docopy) {
	copylex(&np->Hlex, lp);
    }
    else {
	np->Hlex.next = lp->next;
	lp->next->prev = &np->Hlex;
	np->Hlex.prev = lp->prev;
	lp->prev->next = &np->Hlex;
    }
    np->Hnext = Histlist.Hnext;
    Histlist.Hnext = np;
    return (np);
E 16
}

I 16
static void
E 16
hfree(hp)
D 16
	register struct Hist *hp;
E 16
I 16
    register struct Hist *hp;
E 16
{

D 16
	freelex(&hp->Hlex);
	xfree((char *)hp);
E 16
I 16
    freelex(&hp->Hlex);
    xfree((ptr_t) hp);
E 16
}

I 16
void
E 16
D 21
dohist(vp)
D 16
	char **vp;
E 16
I 16
    Char  **vp;
E 21
I 21
/*ARGSUSED*/
dohist(v, t)
    Char **v;
    struct command *t;
E 21
E 16
{
D 2
	int n, rflg = 0;
E 2
I 2
D 4
	int n, rflg = 0, cflg = 0;
E 2

E 4
I 4
D 16
	int n, rflg = 0, hflg = 0;
E 4
	if (getn(value("history")) == 0)
		return;
	if (setintr)
D 6
		sigrelse(SIGINT);
E 6
I 6
D 7
		(void) sigrelse(mask(SIGINT));
E 7
I 7
D 8
		sigrelse(SIGINT);
E 8
I 8
D 10
		sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 10
I 10
D 14
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 14
I 14
		(void) sigsetmask(sigblock(0L) & ~sigmask(SIGINT));
E 14
E 10
E 8
E 7
E 6
D 11
	vp++;
D 2
	if (*vp && eq(*vp, "-r")) {
		rflg++;
		vp++;
E 2
I 2
D 5
	while (*vp[0] == '-') {
E 5
I 5
	while (*vp && *vp[0] == '-') {
E 5
D 4
		if (*vp && eq(*vp, "-c")) {
			cflg++;
E 4
I 4
D 9
		if (*vp && eq(*vp, "-h")) {
E 9
I 9
		if (*vp && eq(*vp, "-h"))
E 9
			hflg++;
E 4
D 9
			vp++;
		}
		if (*vp && eq(*vp, "-r")) {
E 9
I 9
		else if (*vp && eq(*vp, "-r"))
E 9
			rflg++;
D 9
			vp++;
		}
E 9
I 9
		vp++;
E 11
I 11
 	while (*++vp && **vp == '-') {
 		char *vp2 = *vp;
 
 		while (*++vp2)
 			switch (*vp2) {
 			case 'h':
 				hflg++;
 				break;
 			case 'r':
 				rflg++;
 				break;
 			case '-':	/* ignore multiple '-'s */
 				break;
 			default:
 				printf("Unknown flag: -%c\n", *vp2);
 				error("Usage: history [-rh] [# number of events]");
			}
E 11
E 9
E 2
	}
	if (*vp)
		n = getn(*vp);
D 4
	else
		n = 1000;
D 2
	dohist1(Histlist.Hnext, &n, rflg);
E 2
I 2
	dohist1(Histlist.Hnext, &n, rflg, cflg);
E 4
I 4
	else {
		n = getn(value("history"));
	}
	dohist1(Histlist.Hnext, &n, rflg, hflg);
E 16
I 16
D 21
    int     n, rflg = 0, hflg = 0, tflg = 0;
E 21
I 21
    int     n, rflg = 0, hflg = 0;
I 24
    sigset_t sigset;
E 24
E 21

    if (getn(value(STRhistory)) == 0)
	return;
D 24
    if (setintr)
D 19
	(void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 19
I 19
	(void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 24
I 24
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }
E 24
E 19
D 21
    while (*++vp && **vp == '-') {
	Char   *vp2 = *vp;
E 21
I 21
    while (*++v && **v == '-') {
	Char   *vp = *v;
E 21

D 21
	while (*++vp2)
	    switch (*vp2) {
E 21
I 21
	while (*++vp)
	    switch (*vp) {
E 21
	    case 'h':
		hflg++;
		break;
	    case 'r':
		rflg++;
		break;
D 21
	    case 't':
		tflg++;
		break;
E 21
	    case '-':		/* ignore multiple '-'s */
		break;
	    default:
		stderror(ERR_HISTUS);
		break;
	    }
    }
D 21
    if (*vp)
	n = getn(*vp);
E 21
I 21
    if (*v)
	n = getn(*v);
E 21
    else {
	n = getn(value(STRhistory));
    }
D 21
    dohist1(Histlist.Hnext, &n, rflg, hflg, tflg);
E 21
I 21
    dohist1(Histlist.Hnext, &n, rflg, hflg);
E 21
E 16
E 4
E 2
}

D 2
dohist1(hp, np, rflg)
E 2
I 2
D 4
dohist1(hp, np, rflg, cflg)
E 4
I 4
D 16
dohist1(hp, np, rflg, hflg)
E 4
E 2
	struct Hist *hp;
D 4
	int *np;
E 4
I 4
	int *np, rflg, hflg;
E 16
I 16
static void
D 21
dohist1(hp, np, rflg, hflg, tflg)
E 21
I 21
dohist1(hp, np, rflg, hflg)
E 21
    struct Hist *hp;
D 21
    int    *np, rflg, hflg, tflg;
E 21
I 21
    int    *np, rflg, hflg;
E 21
E 16
E 4
{
D 16
	bool print = (*np) > 0;
top:
	if (hp == 0)
		return;
E 16
I 16
    bool    print = (*np) > 0;

    for (; hp != 0; hp = hp->Hnext) {
E 16
	(*np)--;
	hp->Href++;
	if (rflg == 0) {
D 2
		dohist1(hp->Hnext, np, rflg);
E 2
I 2
D 4
		dohist1(hp->Hnext, np, rflg, cflg);
E 4
I 4
D 16
		dohist1(hp->Hnext, np, rflg, hflg);
E 4
E 2
		if (print)
D 2
			phist(hp);
E 2
I 2
D 4
			phist(hp, cflg);
E 4
I 4
			phist(hp, hflg);
E 4
E 2
		return;
E 16
I 16
D 21
	    dohist1(hp->Hnext, np, rflg, hflg, tflg);
E 21
I 21
	    dohist1(hp->Hnext, np, rflg, hflg);
E 21
	    if (print)
D 21
		phist(hp, hflg, tflg);
E 21
I 21
		phist(hp, hflg);
E 21
	    return;
E 16
	}
	if (*np >= 0)
D 2
		phist(hp);
E 2
I 2
D 4
		phist(hp, cflg);
E 4
I 4
D 16
		phist(hp, hflg);
E 4
E 2
	hp = hp->Hnext;
	goto top;
E 16
I 16
D 21
	    phist(hp, hflg, tflg);
E 21
I 21
	    phist(hp, hflg);
E 21
    }
E 16
}

D 2
phist(hp)
E 2
I 2
D 4
phist(hp, cflg)
E 4
I 4
D 16
phist(hp, hflg)
E 4
E 2
	register struct Hist *hp;
I 2
D 4
	int cflg;
E 4
I 4
	int hflg;
E 16
I 16
static void
D 21
phist(hp, hflg, tflg)
E 21
I 21
phist(hp, hflg)
E 21
    register struct Hist *hp;
D 21
    int     hflg, tflg;
E 21
I 21
    int     hflg;
E 21
E 16
E 4
E 2
{
I 16
D 21
    struct tm *t;
    char    ampm = 'a';
E 16

D 2
	printf("%6d\t", hp->Hnum);
E 2
I 2
D 4
	if (cflg == 0)
E 4
I 4
D 16
	if (hflg == 0)
E 4
		printf("%6d\t", hp->Hnum);
E 2
	prlex(&hp->Hlex);
E 16
I 16
    if (hflg == 0) {
	xprintf("%6d\t", hp->Hnum);
	if (tflg == 0) {
	    t = localtime(&hp->Htime);
	    if (adrof(STRampm)) {	/* addition by Hans J. Albertsson */
		if (t->tm_hour >= 12) {
		    if (t->tm_hour > 12)
			t->tm_hour -= 12;
		    ampm = 'p';
		}
		else if (t->tm_hour == 0)
		    t->tm_hour = 12;
		xprintf("%2d:%02d%cm\t", t->tm_hour, t->tm_min, ampm);
	    }
	    else {
		xprintf("%2d:%02d\t", t->tm_hour, t->tm_min);
	    }
	}
    }
    prlex(&hp->Hlex);
E 21
I 21
    if (hflg == 0)
	(void) fprintf(cshout, "%6d\t", hp->Hnum);
    prlex(cshout, &hp->Hlex);
E 21
E 16
}
E 1
