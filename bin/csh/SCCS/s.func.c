h56028
s 00035/00016/01456
d D 8.2 95/03/22 14:12:37 christos 57 56
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/01470
d D 8.1 93/05/31 16:42:11 bostic 56 55
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00016/01454
d D 5.39 93/05/22 19:06:32 christos 55 54
c Fixed gcc -Wall warnings
e
s 00001/00001/01469
d D 5.38 92/12/01 13:43:26 mckusick 54 53
c RLIMIT_OFILE => RLIMIT_NOFILE for compatibility with other UNIX's
e
s 00002/00004/01468
d D 5.37 92/07/12 12:15:10 christos 53 52
c Fixed limit bounds check
e
s 00001/00001/01471
d D 5.36 92/05/28 17:25:11 mckusick 52 51
c type of limits is quad_t
e
s 00002/00000/01470
d D 5.35 92/05/15 00:10:03 christos 51 50
c flush in printf() so that we don't lose the output
e
s 00007/00003/01463
d D 5.34 92/02/05 16:30:10 christos 50 49
c Use vis(3) to print unprintable characters
e
s 00001/00001/01465
d D 5.33 91/11/12 20:33:45 bostic 49 48
c search is static void, not just void
e
s 00006/00006/01460
d D 5.32 91/11/06 16:09:41 christos 48 47
c Added support for displaying non-printable characters
e
s 00018/00011/01448
d D 5.31 91/11/04 18:49:14 christos 47 46
c Loop freeing was busted
e
s 00015/00012/01444
d D 5.30 91/10/28 21:27:58 leres 46 45
c Fix gcc "bodyless for/while" warnings.
e
s 00000/00001/01456
d D 5.29 91/10/27 16:26:47 christos 45 44
c Small declatation typo
e
s 00021/00008/01436
d D 5.28 91/10/27 16:01:17 christos 44 43
c Loops were broken again. (Michael Schroeder's fix)
e
s 00007/00006/01437
d D 5.27 91/10/19 17:26:42 christos 43 42
c Fixed nested loop bug
e
s 00003/00003/01440
d D 5.26 91/09/06 01:25:45 christos 42 41
c Replaced exp with expr to avoild libm conflict
e
s 00002/00001/01441
d D 5.25 91/09/04 01:36:47 christos 41 40
c fix xfree() so it can be re-written as a macro
e
s 00036/00022/01406
d D 5.24 91/08/30 21:23:43 christos 40 39
c Bugfix for loops in aliases.
e
s 00001/00001/01427
d D 5.23 91/08/02 03:42:29 christos 39 38
c make setenv() use G_APPEND
e
s 00018/00000/01410
d D 5.22 91/07/28 14:14:21 christos 38 37
c Added dowhich() and doprintf() builtins.
e
s 00138/00078/01272
d D 5.21 91/07/19 17:30:53 christos 37 36
c stdio based version; brace glob fix; builtin prototypes
e
s 00021/00022/01329
d D 5.20 91/06/26 23:41:36 christos 36 35
c unsetenv can take more than one pattern
e
s 00006/00000/01345
d D 5.19 91/06/08 17:08:45 christos 35 34
c More prototype fixes, Removed TERMIOS define
e
s 00012/00004/01333
d D 5.18 91/06/08 12:20:20 bostic 34 33
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00021/00019/01316
d D 5.17 91/06/07 20:57:23 christos 33 32
c static function prototypes
e
s 00009/00008/01326
d D 5.16 91/06/07 11:13:26 bostic 32 31
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 01053/00851/00281
d D 5.15 91/06/04 13:31:30 bostic 31 30
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/01127
d D 5.14 91/04/04 18:17:41 bostic 30 29
c new copyright; att/bsd/shared
e
s 00045/00043/01086
d D 5.13 91/04/01 17:37:11 bostic 29 28
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00002/00002/01127
d D 5.12 91/03/14 12:29:49 bostic 28 27
c lost the SCCS id's...
e
s 00004/00004/01125
d D 5.11 91/03/14 12:29:20 bostic 27 26
c use the library globbing routines instead of rolling our own
e
s 00001/00001/01128
d D 5.10 89/11/20 17:42:30 marc 26 25
c POSIX Job Control
e
s 00001/00001/01128
d D 5.9 89/09/24 16:49:01 bostic 25 24
c POSIX signals
e
s 00000/00006/01129
d D 5.8 89/08/14 18:14:22 karels 24 23
c we've only got one tty discipline now.
e
s 00002/00001/01133
d D 5.7 89/03/05 21:23:54 bostic 23 22
c pathnames.h
e
s 00000/00015/01134
d D 5.6 89/02/15 11:06:41 bostic 22 21
c use pathname include files; remove IIASA commands; remove newgrp
c command; add globall .cshrc, .login, and .logout files; minor cleanups
e
s 00003/00003/01146
d D 5.5 88/05/19 15:38:48 bostic 21 20
c install C version of _doprnt
e
s 00005/00004/01144
d D 5.4 87/06/25 09:15:15 bostic 20 19
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00002/00002/01146
d D 5.3 86/05/13 01:03:33 lepreau 19 18
c avoid null ptr deref, from glenn@sun
e
s 00003/00003/01145
d D 5.2 85/06/06 13:11:42 edward 18 17
c cleaning up after bozos
e
s 00008/00002/01140
d D 5.1 85/06/04 10:59:01 dist 17 16
c Add copyright
e
s 00015/00003/01127
d D 4.16 85/06/01 16:55:51 edward 16 15
c allow setenv with 0 and 1 arugments:
c 	setenv -> printenv
c 	setenv x -> setenv x ''
e
s 00032/00015/01098
d D 4.15 85/03/28 18:32:15 edward 15 14
c limit and unlimit bug fixed,
c plus -h to set and unset hard limits
e
s 00017/00007/01096
d D 4.14 85/03/19 18:20:19 mckusick 14 13
c null pointers; system call boiler plate
e
s 00086/00059/01017
d D 4.13 84/12/13 14:43:06 edward 13 12
c performance
e
s 00018/00018/01058
d D 4.12 84/08/31 09:31:57 ralph 12 11
c use new signal calls instead of compatibility routines.
e
s 00004/00001/01072
d D 4.11 84/07/03 19:51:13 mckusick 11 10
c fix the unlimit command so that it does not try to set greater than the
c user is allowed.
e
s 00015/00015/01058
d D 4.10 83/06/11 16:49:11 sam 10 9
c different approach, try signal compatibility package
e
s 00018/00016/01055
d D 4.9 83/06/10 23:59:04 sam 9 8
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00001/00001/01070
d D 4.8 83/02/09 14:17:04 sam 8 7
c cleanups from sun
e
s 00025/00028/01046
d D 4.7 82/12/30 17:34:57 sam 7 6
c finally works (updated for 4.1c and merged with sun)
e
s 00001/00000/01073
d D 4.6 81/08/20 23:48:57 mckusic 6 5
c save history on "login" command
e
s 00003/00001/01070
d D 4.5 81/06/19 13:54:39 root 5 4
c fix to bug rep #32 from cmu
e
s 00004/00000/01067
d D 4.4 81/05/18 11:58:23 root 4 3
c fix per ken greer
e
s 00001/00000/01066
d D 4.3 81/04/13 20:01:07 wnj 3 2
c add limit on memoryuse
e
s 00001/00001/01065
d D 4.2 81/02/07 12:15:31 wnj 2 1
c fixed include file
e
s 01066/00000/00000
d D 4.1 80/10/09 12:40:58 bill 1 0
c date and time created 80/10/09 12:40:58 by bill
e
u
U
t
T
I 17
D 30
/*
 * Copyright (c) 1980 Regents of the University of California.
D 18
 * All rights reserved.  The Berkeley software License Agreement
E 18
I 18
 * All rights reserved.  The Berkeley Software License Agreement
E 18
 * specifies the terms and conditions for redistribution.
E 30
I 30
/*-
D 56
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 56
I 56
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 56
 *
 * %sccs.include.redist.c%
E 30
 */

E 17
I 1
D 5
static	char *sccsid = "%Z%%M% %I% %G%";
E 5
I 5
D 13
static	char *sccsid = "%Z%%M% %I% %E%";
E 13
I 13
#ifndef lint
D 17
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 17
I 17
D 18
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 18
I 18
D 27
static char *sccsid = "%W% (Berkeley) %G%";
E 27
I 27
D 28
static char *sccsid = "@(#)sh.func.c	5.10 (Berkeley) 11/20/89";
E 27
#endif
E 28
I 28
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 28
E 18
E 17
E 13
E 5

I 34
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 35
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 35
E 34
D 32
#include "sh.h"
E 32
I 32
#include "csh.h"
#include "extern.h"
I 34
#include "pathnames.h"
E 34
E 32
D 31
#include <sys/ioctl.h>
I 23
#include "pathnames.h"
E 31
E 23

D 31
/*
 * C shell
 */
E 31
I 31
extern char **environ;
E 31

I 31
static int zlast = -1;
D 33
static void islogin();
static void reexecute();
static void preread();
static void doagain();
static int getword();
static int keyword();
static void Unsetenv();
static void toend();
static void xecho();
E 33
I 33
static void	islogin __P((void));
static void	reexecute __P((struct command *));
static void	preread __P((void));
static void	doagain __P((void));
I 44
D 45
static char    *isrchx __P((int));
E 45
static void	search __P((int, int, Char *));
E 44
static int	getword __P((Char *));
static int	keyword __P((Char *));
D 44
static void	Unsetenv __P((Char *));
E 44
static void	toend __P((void));
static void	xecho __P((int, Char **));
I 44
static void	Unsetenv __P((Char *));
E 44
E 33

E 31
struct biltins *
isbfunc(t)
D 13
	register struct command *t;
E 13
I 13
D 31
	struct command *t;
E 31
I 31
    struct command *t;
E 31
E 13
{
D 31
	register char *cp = t->t_dcom[0];
D 13
	register char *dp;
	register struct biltins *bp;
E 13
I 13
	register struct biltins *bp, *bp1, *bp2;
E 13
	int dolabel(), dofg1(), dobg1();
	static struct biltins label = { "", dolabel, 0, 0 };
	static struct biltins foregnd = { "%job", dofg1, 0, 0 };
	static struct biltins backgnd = { "%job &", dobg1, 0, 0 };
E 31
I 31
    register Char *cp = t->t_dcom[0];
    register struct biltins *bp, *bp1, *bp2;
    static struct biltins label = {"", dozip, 0, 0};
    static struct biltins foregnd = {"%job", dofg1, 0, 0};
    static struct biltins backgnd = {"%job &", dobg1, 0, 0};
E 31

D 31
	if (lastchr(cp) == ':') {
		label.bname = cp;
		return (&label);
E 31
I 31
    if (lastchr(cp) == ':') {
	label.bname = short2str(cp);
	return (&label);
    }
    if (*cp == '%') {
	if (t->t_dflg & F_AMPERSAND) {
	    t->t_dflg &= ~F_AMPERSAND;
	    backgnd.bname = short2str(cp);
	    return (&backgnd);
E 31
	}
D 31
	if (*cp == '%') {
D 29
		if (t->t_dflg & FAND) {
			t->t_dflg &= ~FAND;
E 29
I 29
		if (t->t_dflg & F_AMPERSAND) {
			t->t_dflg &= ~F_AMPERSAND;
E 29
			backgnd.bname = cp;
			return (&backgnd);
D 13
		} 
E 13
I 13
		}
E 13
		foregnd.bname = cp;
		return (&foregnd);
	}
D 13
	for (bp = bfunc; dp = bp->bname; bp++) {
		if (dp[0] == cp[0] && eq(dp, cp))
			return (bp);
		if (dp[0] > cp[0])
			break;
E 13
I 13
	/*
	 * Binary search
	 * Bp1 is the beginning of the current search range.
	 * Bp2 is one past the end.
	 */
	for (bp1 = bfunc, bp2 = bfunc + nbfunc; bp1 < bp2;) {
		register i;
E 31
I 31
	foregnd.bname = short2str(cp);
	return (&foregnd);
    }
    /*
     * Binary search Bp1 is the beginning of the current search range. Bp2 is
     * one past the end.
     */
    for (bp1 = bfunc, bp2 = bfunc + nbfunc; bp1 < bp2;) {
	register i;
E 31

D 31
		bp = bp1 + (bp2 - bp1 >> 1);
		if ((i = *cp - *bp->bname) == 0 &&
		    (i = strcmp(cp, bp->bname)) == 0)
			return bp;
		if (i < 0)
			bp2 = bp;
		else
			bp1 = bp + 1;
E 13
	}
	return (0);
E 31
I 31
	bp = bp1 + ((bp2 - bp1) >> 1);
	if ((i = *cp - *bp->bname) == 0 &&
	    (i = Strcmp(cp, str2short(bp->bname))) == 0)
	    return bp;
	if (i < 0)
	    bp2 = bp;
	else
	    bp1 = bp + 1;
    }
    return (0);
E 31
}

I 31
void
E 31
func(t, bp)
D 31
	register struct command *t;
	register struct biltins *bp;
E 31
I 31
    register struct command *t;
    register struct biltins *bp;
E 31
{
D 31
	int i;
E 31
I 31
    int     i;
E 31

D 31
	xechoit(t->t_dcom);
	setname(bp->bname);
	i = blklen(t->t_dcom) - 1;
	if (i < bp->minargs)
		bferr("Too few arguments");
	if (i > bp->maxargs)
		bferr("Too many arguments");
	(*bp->bfunct)(t->t_dcom, t);
E 31
I 31
    xechoit(t->t_dcom);
    setname(bp->bname);
    i = blklen(t->t_dcom) - 1;
    if (i < bp->minargs)
	stderror(ERR_NAME | ERR_TOOFEW);
    if (i > bp->maxargs)
	stderror(ERR_NAME | ERR_TOOMANY);
    (*bp->bfunct) (t->t_dcom, t);
E 31
}

D 31
dolabel()
{

}

E 31
I 31
void
E 31
D 37
doonintr(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
doonintr(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register char *cp;
	register char *vv = v[1];
E 31
I 31
    register Char *cp;
    register Char *vv = v[1];
I 57
    sigset_t sigset;
E 57
E 31

D 31
	if (parintr == SIG_IGN)
		return;
	if (setintr && intty)
		bferr("Can't from terminal");
	cp = gointr, gointr = 0, xfree(cp);
	if (vv == 0) {
		if (setintr)
D 9
			sighold(SIGINT);
E 9
I 9
D 10
			(void) sigblock(mask(SIGINT));
E 10
I 10
D 12
			sighold(SIGINT);
E 12
I 12
D 13
			sigblock(sigmask(SIGINT));
E 13
I 13
			(void) sigblock(sigmask(SIGINT));
E 13
E 12
E 10
E 9
		else
D 9
			sigset(SIGINT, SIG_DFL);
E 9
I 9
D 10
			signal(SIGINT, SIG_DFL);
E 10
I 10
D 12
			sigset(SIGINT, SIG_DFL);
E 12
I 12
D 13
			signal(SIGINT, SIG_DFL);
E 13
I 13
			(void) signal(SIGINT, SIG_DFL);
E 13
E 12
E 10
E 9
		gointr = 0;
	} else if (eq((vv = strip(vv)), "-")) {
D 9
		sigset(SIGINT, SIG_IGN);
E 9
I 9
D 10
		signal(SIGINT, SIG_IGN);
E 10
I 10
D 12
		sigset(SIGINT, SIG_IGN);
E 12
I 12
D 13
		signal(SIGINT, SIG_IGN);
E 13
I 13
		(void) signal(SIGINT, SIG_IGN);
E 13
E 12
E 10
E 9
		gointr = "-";
	} else {
		gointr = savestr(vv);
D 9
		sigset(SIGINT, pintr);
E 9
I 9
D 10
		signal(SIGINT, pintr);
E 10
I 10
D 12
		sigset(SIGINT, pintr);
E 12
I 12
D 13
		signal(SIGINT, pintr);
E 13
I 13
		(void) signal(SIGINT, pintr);
E 13
E 12
E 10
E 9
	}
E 31
I 31
    if (parintr == SIG_IGN)
	return;
    if (setintr && intty)
	stderror(ERR_NAME | ERR_TERMINAL);
    cp = gointr;
    gointr = 0;
    xfree((ptr_t) cp);
    if (vv == 0) {
D 57
	if (setintr)
	    (void) sigblock(sigmask(SIGINT));
	else
E 57
I 57
	if (setintr) {
	    sigemptyset(&sigset);
	    sigaddset(&sigset, SIGINT);
	    sigprocmask(SIG_BLOCK, &sigset, NULL);
	} else
E 57
	    (void) signal(SIGINT, SIG_DFL);
	gointr = 0;
    }
    else if (eq((vv = strip(vv)), STRminus)) {
	(void) signal(SIGINT, SIG_IGN);
	gointr = Strsave(STRminus);
    }
    else {
	gointr = Strsave(vv);
	(void) signal(SIGINT, pintr);
    }
E 31
}

I 31
void
E 31
D 37
donohup()
E 37
I 37
/*ARGSUSED*/
donohup(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	if (intty)
		bferr("Can't from terminal");
	if (setintr == 0) {
D 13
		signal(SIGHUP, SIG_IGN);
E 13
I 13
		(void) signal(SIGHUP, SIG_IGN);
E 13
#ifdef CC
		submit(getpid());
#endif
	}
E 31
I 31
    if (intty)
	stderror(ERR_NAME | ERR_TERMINAL);
    if (setintr == 0) {
	(void) signal(SIGHUP, SIG_IGN);
    }
E 31
}

I 31
void
E 31
D 37
dozip()
E 37
I 37
/*ARGSUSED*/
dozip(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	;
E 31
I 31
    ;
E 31
}

I 31
void
E 31
prvars()
{
D 31

	plist(&shvhed);
E 31
I 31
    plist(&shvhed);
E 31
}

I 31
void
E 31
D 37
doalias(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
doalias(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register struct varent *vp;
	register char *p;
E 31
I 31
    register struct varent *vp;
    register Char *p;
E 31

D 31
	v++;
	p = *v++;
	if (p == 0)
		plist(&aliases);
	else if (*v == 0) {
		vp = adrof1(strip(p), &aliases);
		if (vp)
			blkpr(vp->vec), printf("\n");
	} else {
		if (eq(p, "alias") || eq(p, "unalias")) {
			setname(p);
			bferr("Too dangerous to alias that");
		}
		set1(strip(p), saveblk(v), &aliases);
E 31
I 31
    v++;
    p = *v++;
    if (p == 0)
	plist(&aliases);
    else if (*v == 0) {
	vp = adrof1(strip(p), &aliases);
D 37
	if (vp)
	    blkpr(vp->vec), xprintf("\n");
E 37
I 37
	if (vp) {
	    blkpr(cshout, vp->vec);
	    fputc('\n', cshout);
	}
E 37
    }
    else {
	if (eq(p, STRalias) || eq(p, STRunalias)) {
D 48
	    setname(short2str(p));
E 48
I 48
	    setname(vis_str(p));
E 48
	    stderror(ERR_NAME | ERR_DANGER);
E 31
	}
I 31
	set1(strip(p), saveblk(v), &aliases);
    }
E 31
}

I 31
void
E 31
D 37
unalias(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
unalias(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31

	unset1(v, &aliases);
E 31
I 31
    unset1(v, &aliases);
E 31
}

I 31
void
E 31
D 37
dologout()
E 37
I 37
/*ARGSUSED*/
dologout(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	islogin();
	goodbye();
E 31
I 31
    islogin();
    goodbye();
E 31
}

I 31
void
E 31
D 37
dologin(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
dologin(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31

	islogin();
I 6
	rechist();
E 6
D 13
	signal(SIGTERM, parterm);
E 13
I 13
	(void) signal(SIGTERM, parterm);
E 13
D 23
	execl("/bin/login", "login", v[1], 0);
E 23
I 23
	execl(_PATH_LOGIN, "login", v[1], 0);
E 23
	untty();
	exit(1);
E 31
I 31
    islogin();
    rechist();
    (void) signal(SIGTERM, parterm);
D 33
    (void) execl(_PATH_LOGIN, "login", short2str(v[1]), (Char *) 0);
E 33
I 33
    (void) execl(_PATH_LOGIN, "login", short2str(v[1]), NULL);
E 33
    untty();
    xexit(1);
E 31
}

I 31
static void
E 31
I 9
D 22
#ifdef NEWGRP
E 9
donewgrp(v)
	char **v;
{

I 5
	if (chkstop == 0 && setintr)
		panystop(0);
E 5
D 13
	signal(SIGTERM, parterm);
E 13
I 13
	(void) signal(SIGTERM, parterm);
E 13
	execl("/bin/newgrp", "newgrp", v[1], 0);
	execl("/usr/bin/newgrp", "newgrp", v[1], 0);
	untty();
	exit(1);
}
I 9
#endif
E 9

E 22
islogin()
{
D 31

	if (chkstop == 0 && setintr)
		panystop(0);
	if (loginsh)
		return;
	error("Not login shell");
E 31
I 31
    if (chkstop == 0 && setintr)
	panystop(0);
    if (loginsh)
	return;
    stderror(ERR_NOTLOGIN);
E 31
}

I 31
void
E 31
doif(v, kp)
D 31
	char **v;
	struct command *kp;
E 31
I 31
    Char  **v;
    struct command *kp;
E 31
{
D 31
	register int i;
	register char **vv;
E 31
I 31
    register int i;
    register Char **vv;
E 31

D 31
	v++;
	i = exp(&v);
	vv = v;
	if (*vv == NOSTR)
		bferr("Empty if");
	if (eq(*vv, "then")) {
		if (*++vv)
			bferr("Improper then");
		setname("then");
		/*
		 * If expression was zero, then scan to else,
		 * otherwise just fall into following code.
		 */
		if (!i)
D 29
			search(ZIF, 0);
E 29
I 29
			search(T_IF, 0);
E 29
		return;
	}
E 31
I 31
    v++;
D 42
    i = exp(&v);
E 42
I 42
    i = expr(&v);
E 42
    vv = v;
    if (*vv == NULL)
	stderror(ERR_NAME | ERR_EMPTYIF);
    if (eq(*vv, STRthen)) {
	if (*++vv)
	    stderror(ERR_NAME | ERR_IMPRTHEN);
D 48
	setname(short2str(STRthen));
E 48
I 48
	setname(vis_str(STRthen));
E 48
E 31
	/*
D 31
	 * Simple command attached to this if.
	 * Left shift the node in this tree, munging it
	 * so we can reexecute it.
E 31
I 31
	 * If expression was zero, then scan to else, otherwise just fall into
	 * following code.
E 31
	 */
D 31
	if (i) {
		lshift(kp->t_dcom, vv - kp->t_dcom);
		reexecute(kp);
		donefds();
	}
E 31
I 31
	if (!i)
D 33
	    search(T_IF, 0);
E 33
I 33
	    search(T_IF, 0, NULL);
E 33
	return;
    }
    /*
     * Simple command attached to this if. Left shift the node in this tree,
     * munging it so we can reexecute it.
     */
    if (i) {
	lshift(kp->t_dcom, vv - kp->t_dcom);
	reexecute(kp);
	donefds();
    }
E 31
}

/*
 * Reexecute a command, being careful not
 * to redo i/o redirection, which is already set up.
 */
I 31
static void
E 31
reexecute(kp)
D 31
	register struct command *kp;
E 31
I 31
    register struct command *kp;
E 31
{
D 31

D 29
	kp->t_dflg &= FSAVE;
	kp->t_dflg |= FREDO;
E 29
I 29
	kp->t_dflg &= F_SAVE;
	kp->t_dflg |= F_REPEAT;
E 29
	/*
	 * If tty is still ours to arbitrate, arbitrate it;
	 * otherwise dont even set pgrp's as the jobs would
	 * then have no way to get the tty (we can't give it
	 * to them, and our parent wouldn't know their pgrp, etc.
	 */
	execute(kp, tpgrp > 0 ? tpgrp : -1);
E 31
I 31
    kp->t_dflg &= F_SAVE;
    kp->t_dflg |= F_REPEAT;
    /*
     * If tty is still ours to arbitrate, arbitrate it; otherwise dont even set
     * pgrp's as the jobs would then have no way to get the tty (we can't give
     * it to them, and our parent wouldn't know their pgrp, etc.
     */
D 32
    execute(kp, (tpgrp > 0 ? tpgrp : -1), (int *) 0, (int *) 0);
E 32
I 32
    execute(kp, (tpgrp > 0 ? tpgrp : -1), NULL, NULL);
E 32
E 31
}

I 31
void
E 31
D 37
doelse()
E 37
I 37
/*ARGSUSED*/
doelse(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

D 29
	search(ZELSE, 0);
E 29
I 29
	search(T_ELSE, 0);
E 31
I 31
D 33
    search(T_ELSE, 0);
E 33
I 33
    search(T_ELSE, 0, NULL);
E 33
E 31
E 29
}

I 31
void
E 31
D 37
dogoto(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
dogoto(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register struct whyle *wp;
	char *lp;
E 31
I 31
D 44
    register struct whyle *wp;
E 44
    Char   *lp;
E 31

I 44
    gotolab(lp = globone(v[1], G_ERROR));
    xfree((ptr_t) lp);
}

void
gotolab(lab)
    Char *lab;
{
    register struct whyle *wp;
E 44
D 31
	/*
	 * While we still can, locate any unknown ends of existing loops.
	 * This obscure code is the WORST result of the fact that we
	 * don't really parse.
	 */
	for (wp = whyles; wp; wp = wp->w_next)
		if (wp->w_end == 0) {
D 29
			search(ZBREAK, 0);
E 29
I 29
			search(T_BREAK, 0);
E 29
			wp->w_end = btell();
		} else
			bseek(wp->w_end);
D 29
	search(ZGOTO, 0, lp = globone(v[1]));
E 29
I 29
	search(T_GOTO, 0, lp = globone(v[1]));
E 29
	xfree(lp);
	/*
	 * Eliminate loops which were exited.
	 */
	wfree();
E 31
I 31
    /*
     * While we still can, locate any unknown ends of existing loops. This
     * obscure code is the WORST result of the fact that we don't really parse.
     */
    zlast = T_GOTO;
    for (wp = whyles; wp; wp = wp->w_next)
D 40
	if (wp->w_end == 0) {
E 40
I 40
D 43
	if (wp->w_end.type == I_SEEK) {
E 43
I 43
	if (wp->w_end.type == F_SEEK && wp->w_end.f_seek == 0) {
E 43
E 40
D 33
	    search(T_BREAK, 0);
E 33
I 33
	    search(T_BREAK, 0, NULL);
E 33
D 32
	    wp->w_end = btell();
E 32
I 32
D 40
	    wp->w_end = fseekp;
E 40
I 40
	    btell(&wp->w_end);
E 40
E 32
	}
	else
D 40
	    bseek(wp->w_end);
E 40
I 40
	    bseek(&wp->w_end);
E 40
D 44
    search(T_GOTO, 0, lp = globone(v[1], G_ERROR));
    xfree((ptr_t) lp);
E 44
I 44
    search(T_GOTO, 0, lab);
E 44
    /*
     * Eliminate loops which were exited.
     */
    wfree();
E 31
}

I 31
void
E 31
D 37
doswitch(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
doswitch(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register char *cp, *lp;
E 31
I 31
    register Char *cp, *lp;
E 31

D 31
	v++;
	if (!*v || *(*v++) != '(')
		goto syntax;
	cp = **v == ')' ? "" : *v++;
	if (*(*v++) != ')')
		v--;
	if (*v)
syntax:
		error("Syntax error");
D 29
	search(ZSWITCH, 0, lp = globone(cp));
E 29
I 29
	search(T_SWITCH, 0, lp = globone(cp));
E 29
	xfree(lp);
E 31
I 31
    v++;
    if (!*v || *(*v++) != '(')
	stderror(ERR_SYNTAX);
    cp = **v == ')' ? STRNULL : *v++;
    if (*(*v++) != ')')
	v--;
    if (*v)
	stderror(ERR_SYNTAX);
    search(T_SWITCH, 0, lp = globone(cp, G_ERROR));
    xfree((ptr_t) lp);
E 31
}

I 31
void
E 31
D 37
dobreak()
E 37
I 37
/*ARGSUSED*/
dobreak(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	if (whyles)
		toend();
	else
		bferr("Not in while/foreach");
E 31
I 31
    if (whyles)
	toend();
    else
	stderror(ERR_NAME | ERR_NOTWHILE);
E 31
}

I 31
void
E 31
D 37
doexit(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
doexit(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31

	if (chkstop == 0)
		panystop(0);
	/*
	 * Don't DEMAND parentheses here either.
	 */
	v++;
	if (*v) {
		set("status", putn(exp(&v)));
		if (*v)
			bferr("Expression syntax");
	}
	btoeof();
	if (intty)
D 13
		close(SHIN);
E 13
I 13
		(void) close(SHIN);
E 31
I 31
    if (chkstop == 0 && (intty || intact) && evalvec == 0)
	panystop(0);
    /*
     * Don't DEMAND parentheses here either.
     */
    v++;
    if (*v) {
D 42
	set(STRstatus, putn(exp(&v)));
E 42
I 42
	set(STRstatus, putn(expr(&v)));
E 42
	if (*v)
	    stderror(ERR_NAME | ERR_EXPRESSION);
    }
    btoeof();
    if (intty)
	(void) close(SHIN);
E 31
E 13
}

I 31
void
E 31
D 37
doforeach(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
doforeach(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register char *cp;
	register struct whyle *nwp;
E 31
I 31
    register Char *cp, *sp;
    register struct whyle *nwp;
E 31

D 31
	v++;
	cp = strip(*v);
	while (*cp && letter(*cp))
		cp++;
	if (*cp || strlen(*v) >= 20)
		bferr("Invalid variable");
	cp = *v++;
	if (v[0][0] != '(' || v[blklen(v) - 1][0] != ')')
		bferr("Words not ()'ed");
	v++;
D 13
	gflag = 0, rscan(v, tglob);
E 13
I 13
	gflag = 0, tglob(v);
E 13
D 27
	v = glob(v);
E 27
I 27
	v = globall(v);
E 27
	if (v == 0)
		bferr("No match");
	nwp = (struct whyle *) calloc(1, sizeof *nwp);
	nwp->w_fe = nwp->w_fe0 = v; gargv = 0;
	nwp->w_start = btell();
	nwp->w_fename = savestr(cp);
	nwp->w_next = whyles;
	whyles = nwp;
	/*
	 * Pre-read the loop so as to be more
	 * comprehensible to a terminal user.
	 */
	if (intty)
		preread();
	doagain();
E 31
I 31
    v++;
    sp = cp = strip(*v);
    if (!letter(*sp))
	stderror(ERR_NAME | ERR_VARBEGIN);
    while (*cp && alnum(*cp))
	cp++;
    if (*cp)
	stderror(ERR_NAME | ERR_VARALNUM);
    if ((cp - sp) > MAXVARLEN)
	stderror(ERR_NAME | ERR_VARTOOLONG);
    cp = *v++;
    if (v[0][0] != '(' || v[blklen(v) - 1][0] != ')')
	stderror(ERR_NAME | ERR_NOPAREN);
    v++;
    gflag = 0, tglob(v);
    v = globall(v);
    if (v == 0)
	stderror(ERR_NAME | ERR_NOMATCH);
    nwp = (struct whyle *) xcalloc(1, sizeof *nwp);
    nwp->w_fe = nwp->w_fe0 = v;
    gargv = 0;
D 32
    nwp->w_start = btell();
E 32
I 32
D 40
    nwp->w_start = fseekp;
E 40
I 40
    btell(&nwp->w_start);
E 40
E 32
    nwp->w_fename = Strsave(cp);
    nwp->w_next = whyles;
I 43
    nwp->w_end.type = F_SEEK;
E 43
    whyles = nwp;
    /*
     * Pre-read the loop so as to be more comprehensible to a terminal user.
     */
    zlast = T_FOREACH;
    if (intty)
	preread();
    doagain();
E 31
}

I 31
void
E 31
D 37
dowhile(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
dowhile(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register int status;
	register bool again = whyles != 0 && whyles->w_start == lineloc &&
	    whyles->w_fename == 0;
E 31
I 31
    register int status;
D 40
    register bool again = whyles != 0 && whyles->w_start == lineloc &&
E 40
I 40
    register bool again = whyles != 0 && SEEKEQ(&whyles->w_start, &lineloc) &&
E 40
    whyles->w_fename == 0;
E 31

D 31
	v++;
	/*
	 * Implement prereading here also, taking care not to
	 * evaluate the expression before the loop has been read up
	 * from a terminal.
	 */
	if (intty && !again)
		status = !exp0(&v, 1);
	else
		status = !exp(&v);
	if (*v)
		bferr("Expression syntax");
	if (!again) {
		register struct whyle *nwp = (struct whyle *) calloc(1, sizeof (*nwp));
E 31
I 31
    v++;
    /*
     * Implement prereading here also, taking care not to evaluate the
     * expression before the loop has been read up from a terminal.
     */
    if (intty && !again)
	status = !exp0(&v, 1);
    else
D 42
	status = !exp(&v);
E 42
I 42
	status = !expr(&v);
E 42
    if (*v)
	stderror(ERR_NAME | ERR_EXPRESSION);
    if (!again) {
	register struct whyle *nwp =
	(struct whyle *) xcalloc(1, sizeof(*nwp));
E 31

D 31
		nwp->w_start = lineloc;
		nwp->w_end = 0;
		nwp->w_next = whyles;
		whyles = nwp;
		if (intty) {
			/*
			 * The tty preread
			 */
			preread();
			doagain();
			return;
		}
E 31
I 31
	nwp->w_start = lineloc;
D 40
	nwp->w_end = 0;
E 40
I 40
D 43
	nwp->w_end.type = I_SEEK;
E 43
I 43
	nwp->w_end.type = F_SEEK;
	nwp->w_end.f_seek = 0;
E 43
E 40
	nwp->w_next = whyles;
	whyles = nwp;
	zlast = T_WHILE;
	if (intty) {
	    /*
	     * The tty preread
	     */
	    preread();
	    doagain();
	    return;
E 31
	}
D 31
	if (status)
		/* We ain't gonna loop no more, no more! */
		toend();
E 31
I 31
    }
    if (status)
	/* We ain't gonna loop no more, no more! */
	toend();
E 31
}

I 31
static void
E 31
preread()
{
I 57
    sigset_t sigset;

E 57
I 31
D 40
    whyles->w_end = -1;
E 40
I 40
    whyles->w_end.type = I_SEEK;
E 40
D 57
    if (setintr)
D 34
	(void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 34
I 34
	(void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 57
I 57
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }
E 57
E 34
E 31

D 31
	whyles->w_end = -1;
	if (setintr)
D 9
		sigrelse(SIGINT);
E 9
I 9
D 10
		(void) sigrelse(mask(SIGINT));
E 10
I 10
D 12
		sigrelse(SIGINT);
E 12
I 12
D 13
		sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 13
I 13
D 20
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 20
I 20
		(void) sigsetmask(sigblock(0L) & ~sigmask(SIGINT));
E 20
E 13
E 12
E 10
E 9
D 29
	search(ZBREAK, 0);
E 29
I 29
	search(T_BREAK, 0);
E 29
	if (setintr)
D 9
		sighold(SIGINT);
E 9
I 9
D 10
		sigblock(mask(SIGINT));
E 10
I 10
D 12
		sighold(SIGINT);
E 12
I 12
D 13
		sigblock(sigmask(SIGINT));
E 13
I 13
		(void) sigblock(sigmask(SIGINT));
E 13
E 12
E 10
E 9
	whyles->w_end = btell();
E 31
I 31
D 33
    search(T_BREAK, 0);		/* read the expression in */
E 33
I 33
    search(T_BREAK, 0, NULL);		/* read the expression in */
E 33
    if (setintr)
D 57
	(void) sigblock(sigmask(SIGINT));
E 57
I 57
	sigprocmask(SIG_BLOCK, &sigset, NULL);
E 57
D 32
    whyles->w_end = btell();
E 32
I 32
D 40
    whyles->w_end = fseekp;
E 40
I 40
    btell(&whyles->w_end);
E 40
E 32
E 31
}

I 31
void
E 31
D 37
doend()
E 37
I 37
/*ARGSUSED*/
doend(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	if (!whyles)
		bferr("Not in while/foreach");
	whyles->w_end = btell();
	doagain();
E 31
I 31
    if (!whyles)
	stderror(ERR_NAME | ERR_NOTWHILE);
D 32
    whyles->w_end = btell();
E 32
I 32
D 40
    whyles->w_end = fseekp;
E 40
I 40
    btell(&whyles->w_end);
E 40
E 32
    doagain();
E 31
}

I 31
void
E 31
D 37
docontin()
E 37
I 37
/*ARGSUSED*/
docontin(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

	if (!whyles)
		bferr("Not in while/foreach");
	doagain();
E 31
I 31
    if (!whyles)
	stderror(ERR_NAME | ERR_NOTWHILE);
    doagain();
E 31
}

I 31
static void
E 31
doagain()
{
D 31

	/* Repeating a while is simple */
	if (whyles->w_fename == 0) {
		bseek(whyles->w_start);
		return;
	}
	/*
	 * The foreach variable list actually has a spurious word
	 * ")" at the end of the w_fe list.  Thus we are at the
	 * of the list if one word beyond this is 0.
	 */
	if (!whyles->w_fe[1]) {
		dobreak();
		return;
	}
	set(whyles->w_fename, savestr(*whyles->w_fe++));
E 31
I 31
    /* Repeating a while is simple */
    if (whyles->w_fename == 0) {
E 31
D 40
	bseek(whyles->w_start);
E 40
I 40
	bseek(&whyles->w_start);
E 40
I 31
	return;
    }
    /*
     * The foreach variable list actually has a spurious word ")" at the end of
     * the w_fe list.  Thus we are at the of the list if one word beyond this
     * is 0.
     */
    if (!whyles->w_fe[1]) {
D 37
	dobreak();
E 37
I 37
	dobreak(NULL, NULL);
E 37
	return;
    }
    set(whyles->w_fename, Strsave(*whyles->w_fe++));
D 40
    bseek(whyles->w_start);
E 40
I 40
    bseek(&whyles->w_start);
E 40
E 31
}

I 31
void
E 31
dorepeat(v, kp)
D 31
	char **v;
	struct command *kp;
E 31
I 31
    Char  **v;
    struct command *kp;
E 31
{
D 12
	register int i;
E 12
I 12
D 20
	register int i, omask;
E 20
I 20
D 31
	register int i;
	register long	omask;
E 31
I 31
    register int i;
D 34
    register sigmask_t omask = 0;
E 34
I 34
D 57
    register sigset_t omask = 0;
E 57
I 57
    sigset_t sigset;
E 57
E 34
E 31
E 20
E 12

D 31
	i = getn(v[1]);
E 31
I 31
    i = getn(v[1]);
D 57
    if (setintr)
	omask = sigblock(sigmask(SIGINT)) & ~sigmask(SIGINT);
E 57
I 57
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
    }
E 57
    lshift(v, 2);
    while (i > 0) {
E 31
	if (setintr)
D 9
		sighold(SIGINT);
E 9
I 9
D 10
		(void) sigblock(mask(SIGINT));
E 10
I 10
D 12
		sighold(SIGINT);
E 12
I 12
D 31
		omask = sigblock(sigmask(SIGINT)) & ~sigmask(SIGINT);
E 12
E 10
E 9
	lshift(v, 2);
	while (i > 0) {
		if (setintr)
D 9
			sigrelse(SIGINT);
E 9
I 9
D 10
			(void) sigrelse(mask(SIGINT));
E 10
I 10
D 12
			sigrelse(SIGINT);
E 12
I 12
D 13
			sigsetmask(omask);
E 13
I 13
			(void) sigsetmask(omask);
E 13
E 12
E 10
E 9
		reexecute(kp);
		--i;
	}
	donefds();
	if (setintr)
D 9
		sigrelse(SIGINT);
E 9
I 9
D 10
		(void) sigrelse(mask(SIGINT));
E 10
I 10
D 12
		sigrelse(SIGINT);
E 12
I 12
D 13
		sigsetmask(omask);
E 13
I 13
		(void) sigsetmask(omask);
E 31
I 31
D 57
	    (void) sigsetmask(omask);
E 57
I 57
	    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
E 57
	reexecute(kp);
	--i;
    }
    donefds();
    if (setintr)
D 57
	(void) sigsetmask(omask);
E 57
I 57
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
E 57
E 31
E 13
E 12
E 10
E 9
}

I 31
void
E 31
D 37
doswbrk()
E 37
I 37
/*ARGSUSED*/
doswbrk(v, t)
    Char **v;
    struct command *t;
E 37
{
D 31

D 29
	search(ZBRKSW, 0);
E 29
I 29
	search(T_BRKSW, 0);
E 31
I 31
D 33
    search(T_BRKSW, 0);
E 33
I 33
    search(T_BRKSW, 0, NULL);
E 33
E 31
E 29
}

I 31
int
E 31
srchx(cp)
D 31
	register char *cp;
E 31
I 31
    register Char *cp;
E 31
{
D 13
	register struct srch *sp;
E 13
I 13
D 31
	register struct srch *sp, *sp1, *sp2;
	register i;
E 31
I 31
    register struct srch *sp, *sp1, *sp2;
    register i;
E 31
E 13

D 13
	for (sp = srchn; sp->s_name; sp++)
		if (eq(cp, sp->s_name))
			return (sp->s_value);
E 13
I 13
D 31
	/*
	 * Binary search
	 * Sp1 is the beginning of the current search range.
	 * Sp2 is one past the end.
	 */
	for (sp1 = srchn, sp2 = srchn + nsrchn; sp1 < sp2;) {
		sp = sp1 + (sp2 - sp1 >> 1);
		if ((i = *cp - *sp->s_name) == 0 &&
		    (i = strcmp(cp, sp->s_name)) == 0)
			return sp->s_value;
		if (i < 0)
			sp2 = sp;
		else
			sp1 = sp + 1;
	}
E 13
	return (-1);
E 31
I 31
    /*
     * Binary search Sp1 is the beginning of the current search range. Sp2 is
     * one past the end.
     */
    for (sp1 = srchn, sp2 = srchn + nsrchn; sp1 < sp2;) {
	sp = sp1 + ((sp2 - sp1) >> 1);
	if ((i = *cp - *sp->s_name) == 0 &&
	    (i = Strcmp(cp, str2short(sp->s_name))) == 0)
	    return sp->s_value;
	if (i < 0)
	    sp2 = sp;
	else
	    sp1 = sp + 1;
    }
    return (-1);
E 31
}

D 31
char	Stype;
char	*Sgoal;
E 31
I 31
static Char Stype;
static Char *Sgoal;
E 31

/*VARARGS2*/
I 31
D 49
void
E 49
I 49
static void
E 49
E 31
search(type, level, goal)
D 31
	int type;
	register int level;
	char *goal;
E 31
I 31
    int     type;
    register int level;
    Char   *goal;
E 31
{
D 31
	char wordbuf[BUFSIZ];
	register char *aword = wordbuf;
	register char *cp;
E 31
I 31
    Char    wordbuf[BUFSIZ];
    register Char *aword = wordbuf;
    register Char *cp;
E 31

D 31
	Stype = type; Sgoal = goal;
D 29
	if (type == ZGOTO)
E 29
I 29
	if (type == T_GOTO)
E 29
D 13
		bseek(0l);
E 13
I 13
		bseek((off_t)0);
E 13
	do {
		if (intty && fseekp == feobp)
			printf("? "), flush();
D 13
		aword[0] = 0, getword(aword);
E 13
I 13
		aword[0] = 0;
		(void) getword(aword);
E 13
		switch (srchx(aword)) {
E 31
I 31
    Stype = type;
    Sgoal = goal;
D 40
    if (type == T_GOTO)
	bseek((off_t) 0);
E 40
I 40
    if (type == T_GOTO) {
	struct Ain a;
	a.type = F_SEEK;
	a.f_seek = 0;
	bseek(&a);
    }
E 40
    do {
D 40
	if (intty && fseekp == feobp)
E 40
I 40
	if (intty && fseekp == feobp && aret == F_SEEK)
E 40
D 37
	    xprintf("? "), flush();
E 37
I 37
	    (void) fprintf(cshout, "? "), (void) fflush(cshout);
E 37
	aword[0] = 0;
	(void) getword(aword);
	switch (srchx(aword)) {
E 31

D 29
		case ZELSE:
			if (level == 0 && type == ZIF)
E 29
I 29
D 31
		case T_ELSE:
			if (level == 0 && type == T_IF)
E 29
				return;
			break;
E 31
I 31
	case T_ELSE:
	    if (level == 0 && type == T_IF)
		return;
	    break;
E 31

D 29
		case ZIF:
E 29
I 29
D 31
		case T_IF:
E 29
			while (getword(aword))
				continue;
D 29
			if ((type == ZIF || type == ZELSE) && eq(aword, "then"))
E 29
I 29
			if ((type == T_IF || type == T_ELSE) &&
			    eq(aword, "then"))
E 29
				level++;
			break;
E 31
I 31
	case T_IF:
	    while (getword(aword))
		continue;
	    if ((type == T_IF || type == T_ELSE) &&
		eq(aword, STRthen))
		level++;
	    break;
E 31

D 29
		case ZENDIF:
			if (type == ZIF || type == ZELSE)
E 29
I 29
D 31
		case T_ENDIF:
			if (type == T_IF || type == T_ELSE)
E 29
				level--;
			break;
E 31
I 31
	case T_ENDIF:
	    if (type == T_IF || type == T_ELSE)
		level--;
	    break;
E 31

D 29
		case ZFOREACH:
		case ZWHILE:
			if (type == ZBREAK)
E 29
I 29
D 31
		case T_FOREACH:
		case T_WHILE:
			if (type == T_BREAK)
E 29
				level++;
			break;
E 31
I 31
	case T_FOREACH:
	case T_WHILE:
	    if (type == T_BREAK)
		level++;
	    break;
E 31

D 29
		case ZEND:
			if (type == ZBREAK)
E 29
I 29
D 31
		case T_END:
			if (type == T_BREAK)
E 29
				level--;
			break;
E 31
I 31
	case T_END:
	    if (type == T_BREAK)
		level--;
	    break;
E 31

D 29
		case ZSWITCH:
			if (type == ZSWITCH || type == ZBRKSW)
E 29
I 29
D 31
		case T_SWITCH:
			if (type == T_SWITCH || type == T_BRKSW)
E 29
				level++;
			break;
E 31
I 31
	case T_SWITCH:
	    if (type == T_SWITCH || type == T_BRKSW)
		level++;
	    break;
E 31

D 29
		case ZENDSW:
			if (type == ZSWITCH || type == ZBRKSW)
E 29
I 29
D 31
		case T_ENDSW:
			if (type == T_SWITCH || type == T_BRKSW)
E 29
				level--;
			break;
E 31
I 31
	case T_ENDSW:
	    if (type == T_SWITCH || type == T_BRKSW)
		level--;
	    break;
E 31

D 29
		case ZLABEL:
			if (type == ZGOTO && getword(aword) && eq(aword, goal))
E 29
I 29
D 31
		case T_LABEL:
			if (type == T_GOTO && getword(aword) && eq(aword, goal))
E 29
				level = -1;
			break;
E 31
I 31
	case T_LABEL:
	    if (type == T_GOTO && getword(aword) && eq(aword, goal))
		level = -1;
	    break;
E 31

D 31
		default:
D 29
			if (type != ZGOTO && (type != ZSWITCH || level != 0))
E 29
I 29
			if (type != T_GOTO && (type != T_SWITCH || level != 0))
E 29
				break;
			if (lastchr(aword) != ':')
				break;
			aword[strlen(aword) - 1] = 0;
D 29
			if (type == ZGOTO && eq(aword, goal) || type == ZSWITCH && eq(aword, "default"))
E 29
I 29
			if (type == T_GOTO && eq(aword, goal) ||
			    type == T_SWITCH && eq(aword, "default"))
E 29
				level = -1;
			break;
E 31
I 31
	default:
	    if (type != T_GOTO && (type != T_SWITCH || level != 0))
		break;
	    if (lastchr(aword) != ':')
		break;
	    aword[Strlen(aword) - 1] = 0;
D 55
	    if (type == T_GOTO && eq(aword, goal) ||
		type == T_SWITCH && eq(aword, STRdefault))
E 55
I 55
	    if ((type == T_GOTO && eq(aword, goal)) ||
		(type == T_SWITCH && eq(aword, STRdefault)))
E 55
		level = -1;
	    break;
E 31

D 29
		case ZCASE:
			if (type != ZSWITCH || level != 0)
E 29
I 29
D 31
		case T_CASE:
			if (type != T_SWITCH || level != 0)
E 29
				break;
D 13
			getword(aword);
E 13
I 13
			(void) getword(aword);
E 13
			if (lastchr(aword) == ':')
				aword[strlen(aword) - 1] = 0;
			cp = strip(Dfix1(aword));
			if (Gmatch(goal, cp))
				level = -1;
			xfree(cp);
			break;
E 31
I 31
	case T_CASE:
	    if (type != T_SWITCH || level != 0)
		break;
	    (void) getword(aword);
	    if (lastchr(aword) == ':')
		aword[Strlen(aword) - 1] = 0;
	    cp = strip(Dfix1(aword));
	    if (Gmatch(goal, cp))
		level = -1;
	    xfree((ptr_t) cp);
	    break;
E 31

D 29
		case ZDEFAULT:
			if (type == ZSWITCH && level == 0)
E 29
I 29
D 31
		case T_DEFAULT:
			if (type == T_SWITCH && level == 0)
E 29
				level = -1;
			break;
		}
D 13
		getword(NOSTR);
E 13
I 13
		(void) getword(NOSTR);
E 13
	} while (level >= 0);
E 31
I 31
	case T_DEFAULT:
	    if (type == T_SWITCH && level == 0)
		level = -1;
	    break;
	}
	(void) getword(NULL);
    } while (level >= 0);
E 31
}

I 31
static int
E 31
getword(wp)
D 31
	register char *wp;
E 31
I 31
    register Char *wp;
E 31
{
D 31
	register int found = 0;
	register int c, d;
E 31
I 31
    register int found = 0;
    register int c, d;
    int     kwd = 0;
    Char   *owp = wp;
D 33
    static int keyword();
E 33
E 31

D 31
	c = readc(1);
	d = 0;
E 31
I 31
    c = readc(1);
    d = 0;
    do {
	while (c == ' ' || c == '\t')
	    c = readc(1);
	if (c == '#')
	    do
		c = readc(1);
	    while (c >= 0 && c != '\n');
	if (c < 0)
	    goto past;
	if (c == '\n') {
	    if (wp)
		break;
	    return (0);
	}
	unreadc(c);
	found = 1;
E 31
	do {
D 31
		while (c == ' ' || c == '\t')
			c = readc(1);
I 4
		if (c == '#')
			do
				c = readc(1);
			while (c >= 0 && c != '\n');
E 4
		if (c < 0)
			goto past;
		if (c == '\n') {
			if (wp)
				break;
			return (0);
		}
		unreadc(c);
		found = 1;
		do {
			c = readc(1);
			if (c == '\\' && (c = readc(1)) == '\n')
				c = ' ';
D 13
			if (any(c, "'\""))
E 13
I 13
			if (c == '\'' || c == '"')
E 13
				if (d == 0)
					d = c;
				else if (d == c)
					d = 0;
			if (c < 0)
				goto past;
			if (wp)
				*wp++ = c;
		} while ((d || c != ' ' && c != '\t') && c != '\n');
	} while (wp == 0);
E 31
I 31
	    c = readc(1);
	    if (c == '\\' && (c = readc(1)) == '\n')
		c = ' ';
	    if (c == '\'' || c == '"')
		if (d == 0)
		    d = c;
		else if (d == c)
		    d = 0;
	    if (c < 0)
		goto past;
	    if (wp) {
		*wp++ = c;
		*wp = 0;	/* end the string b4 test */
	    }
D 55
	} while ((d || !(kwd = keyword(owp)) && c != ' '
		  && c != '\t') && c != '\n');
E 55
I 55
	} while ((d || (!(kwd = keyword(owp)) && c != ' '
		  && c != '\t')) && c != '\n');
E 55
    } while (wp == 0);

    /*
     * if we have read a keyword ( "if", "switch" or "while" ) then we do not
     * need to unreadc the look-ahead char
     */
    if (!kwd) {
E 31
	unreadc(c);
	if (found)
D 31
		*--wp = 0;
	return (found);
E 31
I 31
	    *--wp = 0;
    }
E 31

I 31
    return (found);

E 31
past:
D 31
	switch (Stype) {
E 31
I 31
    switch (Stype) {
E 31

D 29
	case ZIF:
E 29
I 29
D 31
	case T_IF:
E 29
		bferr("then/endif not found");
E 31
I 31
    case T_IF:
	stderror(ERR_NAME | ERR_NOTFOUND, "then/endif");
E 31

D 29
	case ZELSE:
E 29
I 29
D 31
	case T_ELSE:
E 29
		bferr("endif not found");
E 31
I 31
    case T_ELSE:
	stderror(ERR_NAME | ERR_NOTFOUND, "endif");
E 31

D 29
	case ZBRKSW:
	case ZSWITCH:
E 29
I 29
D 31
	case T_BRKSW:
	case T_SWITCH:
E 29
		bferr("endsw not found");
E 31
I 31
    case T_BRKSW:
    case T_SWITCH:
	stderror(ERR_NAME | ERR_NOTFOUND, "endsw");
E 31

D 29
	case ZBREAK:
E 29
I 29
D 31
	case T_BREAK:
E 29
		bferr("end not found");
E 31
I 31
    case T_BREAK:
	stderror(ERR_NAME | ERR_NOTFOUND, "end");
E 31

D 29
	case ZGOTO:
E 29
I 29
D 31
	case T_GOTO:
E 29
		setname(Sgoal);
		bferr("label not found");
	}
	/*NOTREACHED*/
E 31
I 31
    case T_GOTO:
D 48
	setname(short2str(Sgoal));
E 48
I 48
	setname(vis_str(Sgoal));
E 48
	stderror(ERR_NAME | ERR_NOTFOUND, "label");
    }
    /* NOTREACHED */
    return (0);
E 31
}

D 31
toend()
E 31
I 31
/*
 * keyword(wp) determines if wp is one of the built-n functions if,
 * switch or while. It seems that when an if statement looks like
 * "if(" then getword above sucks in the '(' and so the search routine
 * never finds what it is scanning for. Rather than rewrite doword, I hack
 * in a test to see if the string forms a keyword. Then doword stops
 * and returns the word "if" -strike
 */

static int
keyword(wp)
    Char   *wp;
E 31
{
I 31
    static Char STRif[] = {'i', 'f', '\0'};
    static Char STRwhile[] = {'w', 'h', 'i', 'l', 'e', '\0'};
    static Char STRswitch[] = {'s', 'w', 'i', 't', 'c', 'h', '\0'};
E 31

D 31
	if (whyles->w_end == 0) {
D 29
		search(ZBREAK, 0);
E 29
I 29
		search(T_BREAK, 0);
E 29
		whyles->w_end = btell() - 1;
	} else
		bseek(whyles->w_end);
	wfree();
E 31
I 31
    if (!wp)
	return (0);

    if ((Strcmp(wp, STRif) == 0) || (Strcmp(wp, STRwhile) == 0)
	|| (Strcmp(wp, STRswitch) == 0))
	return (1);

    return (0);
E 31
}

I 31
static void
toend()
{
D 40
    if (whyles->w_end == 0) {
E 40
I 40
D 43
    if (whyles->w_end.type == I_SEEK) {
E 43
I 43
    if (whyles->w_end.type == F_SEEK && whyles->w_end.f_seek == 0) {
E 43
E 40
	search(T_BREAK, 0, NULL);
D 32
	whyles->w_end = btell() - 1;
E 32
I 32
D 40
	whyles->w_end = fseekp - 1;
E 40
I 40
	btell(&whyles->w_end);
	whyles->w_end.f_seek--;
E 40
E 32
    }
    else
D 40
	bseek(whyles->w_end);
E 40
I 40
	bseek(&whyles->w_end);
E 40
    wfree();
}

void
E 31
wfree()
{
D 31
	long o = btell();
E 31
I 31
D 32
    long    o = btell();
E 32
I 32
D 40
    long    o = fseekp;
E 40
I 40
    struct Ain    o;
    struct whyle *nwp;
I 47

E 47
    btell(&o);
E 40
E 32
E 31

D 31
	while (whyles) {
		register struct whyle *wp = whyles;
		register struct whyle *nwp = wp->w_next;
E 31
I 31
D 40
    while (whyles) {
E 40
I 40
D 46
    if (o.type != F_SEEK) 
E 46
I 46
D 47
    if (o.type != F_SEEK)
E 46
	return;

E 47
    for (; whyles; whyles = nwp) {
E 40
	register struct whyle *wp = whyles;
D 40
	register struct whyle *nwp = wp->w_next;
E 40
I 40
	nwp = wp->w_next;
D 43
	if (wp->w_start.type != F_SEEK || wp->w_end.type != F_SEEK)
	    continue;
E 40
E 31

E 43
I 43
D 44
	if (wp->w_start.type != F_SEEK || wp->w_end.type != F_SEEK) 
E 44
I 44
D 47
	if (wp->w_start.type != F_SEEK)
E 44
	    break;
E 43
D 31
		if (o >= wp->w_start && (wp->w_end == 0 || o < wp->w_end))
			break;
		if (wp->w_fe0)
			blkfree(wp->w_fe0);
		if (wp->w_fename)
			xfree(wp->w_fename);
		xfree((char *)wp);
		whyles = nwp;
	}
E 31
I 31
D 40
	if (o >= wp->w_start && (wp->w_end == 0 || o < wp->w_end))
E 40
I 40
D 44
	if (o.f_seek >= wp->w_start.f_seek && 
	    (wp->w_end.f_seek == 0 || o.f_seek < wp->w_end.f_seek))
E 40
	    break;
E 44
I 44
	if (wp->w_end.type != I_SEEK) {
	    if (wp->w_end.type != F_SEEK)
		break;
D 46
	    if (o.f_seek >= wp->w_start.f_seek && 
E 46
I 46
	    if (o.f_seek >= wp->w_start.f_seek &&
E 46
		(wp->w_end.f_seek == 0 || o.f_seek < wp->w_end.f_seek))
		break;
E 47
I 47

	/*
	 * We free loops that have different seek types.
	 */
	if (wp->w_end.type != I_SEEK && wp->w_start.type == wp->w_end.type &&
	    wp->w_start.type == o.type) {
	    if (wp->w_end.type == F_SEEK) {
		if (o.f_seek >= wp->w_start.f_seek && 
		    (wp->w_end.f_seek == 0 || o.f_seek < wp->w_end.f_seek))
		    break;
	    }
	    else {
		if (o.a_seek >= wp->w_start.a_seek && 
		    (wp->w_end.a_seek == 0 || o.a_seek < wp->w_end.a_seek))
		    break;
	    }
E 47
	}
I 47

E 47
E 44
	if (wp->w_fe0)
	    blkfree(wp->w_fe0);
	if (wp->w_fename)
	    xfree((ptr_t) wp->w_fename);
	xfree((ptr_t) wp);
D 40
	whyles = nwp;
E 40
    }
E 31
}

I 31
void
E 31
D 37
doecho(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
doecho(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31

	echo(' ', v);
E 31
I 31
    xecho(' ', v);
E 31
}

I 31
void
E 31
D 37
doglob(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
doglob(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31

	echo(0, v);
	flush();
E 31
I 31
    xecho(0, v);
D 37
    flush();
E 37
I 37
    (void) fflush(cshout);
E 37
E 31
}

D 31
echo(sep, v)
	char sep;
	register char **v;
E 31
I 31
static void
xecho(sep, v)
D 33
    Char    sep;
E 33
I 33
    int    sep;
E 33
    register Char **v;
E 31
{
D 31
	register char *cp;
	int nonl = 0;
E 31
I 31
    register Char *cp;
    int     nonl = 0;
I 57
    sigset_t sigset;
E 57
E 31

D 31
	if (setintr)
D 9
		sigrelse(SIGINT);
E 9
I 9
D 10
		(void) sigrelse(mask(SIGINT));
E 10
I 10
D 12
		sigrelse(SIGINT);
E 12
I 12
D 13
		sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 13
I 13
D 20
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 20
I 20
		(void) sigsetmask(sigblock(0L) & ~sigmask(SIGINT));
E 20
E 13
E 12
E 10
E 9
	v++;
	if (*v == 0)
		return;
D 13
	gflag = 0; rscan(v, tglob);
E 13
I 13
	gflag = 0, tglob(v);
E 13
	if (gflag) {
D 27
		v = glob(v);
E 27
I 27
		v = globall(v);
E 27
		if (v == 0)
			bferr("No match");
	} else
D 13
		scan(v, trim);
E 13
I 13
		trim(v);
E 13
D 14
	if (sep == ' ' && !strcmp(*v, "-n"))
E 14
I 14
	if (sep == ' ' && *v && !strcmp(*v, "-n"))
E 14
		nonl++, v++;
	while (cp = *v++) {
		register int c;
E 31
I 31
D 57
    if (setintr)
D 34
	(void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 34
I 34
	(void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 57
I 57
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }
E 57
E 34
    v++;
    if (*v == 0)
	return;
    gflag = 0, tglob(v);
    if (gflag) {
	v = globall(v);
	if (v == 0)
	    stderror(ERR_NAME | ERR_NOMATCH);
    }
    else {
	v = gargv = saveblk(v);
	trim(v);
    }
    if (sep == ' ' && *v && eq(*v, STRmn))
	nonl++, v++;
D 55
    while (cp = *v++) {
E 55
I 55
    while ((cp = *v++) != NULL) {
E 55
	register int c;
E 31

D 31
		while (c = *cp++)
D 21
			putchar(c | QUOTE);
E 21
I 21
			cshputchar(c | QUOTE);
E 21
		if (*v)
D 21
			putchar(sep | QUOTE);
E 21
I 21
			cshputchar(sep | QUOTE);
E 21
	}
	if (sep && nonl == 0)
D 21
		putchar('\n');
E 21
I 21
		cshputchar('\n');
E 21
	else
		flush();
	if (setintr)
D 9
		sighold(SIGINT);
E 9
I 9
D 10
		(void) sigblock(mask(SIGINT));
E 10
I 10
D 12
		sighold(SIGINT);
E 12
I 12
D 13
		sigblock(sigmask(SIGINT));
E 13
I 13
		(void) sigblock(sigmask(SIGINT));
E 13
E 12
E 10
E 9
	if (gargv)
		blkfree(gargv), gargv = 0;
E 31
I 31
D 55
	while (c = *cp++)
E 55
I 55
	while ((c = *cp++) != '\0')
E 55
D 37
	    xputchar(c | QUOTE);
E 37
I 37
D 48
	    (void) fputc(c | QUOTE, cshout);
E 48
I 48
	    (void) vis_fputc(c | QUOTE, cshout);
E 48
E 37

	if (*v)
D 37
	    xputchar(sep | QUOTE);
E 37
I 37
D 48
	    (void) fputc(sep | QUOTE, cshout);
E 48
I 48
	    (void) vis_fputc(sep | QUOTE, cshout);
E 48
E 37
    }
    if (sep && nonl == 0)
D 37
	xputchar('\n');
E 37
I 37
	(void) fputc('\n', cshout);
E 37
    else
D 37
	flush();
E 37
I 37
	(void) fflush(cshout);
E 37
    if (setintr)
D 57
	(void) sigblock(sigmask(SIGINT));
E 57
I 57
	sigprocmask(SIG_BLOCK, &sigset, NULL);
E 57
    if (gargv)
	blkfree(gargv), gargv = 0;
E 31
}

D 31
char	**environ;
E 31
I 31
D 37
/* from "Karl Berry." <karl%mote.umb.edu@relay.cs.net> -- for NeXT things
   (and anything else with a modern compiler) */
E 31

E 37
I 31
void
E 31
D 37
dosetenv(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
dosetenv(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 16
	char *lp = globone(v[2]);
E 16
I 16
D 31
	char *vp, *lp;
E 31
I 31
    Char   *vp, *lp;
I 57
    sigset_t sigset;
E 57
E 31
E 16

D 16
	setenv(v[1], lp);
	if (eq(v[1], "PATH")) {
E 16
I 16
D 31
	v++;
	if ((vp = *v++) == 0) {
		register char **ep;
E 31
I 31
    v++;
    if ((vp = *v++) == 0) {
	register Char **ep;
E 31

D 31
		if (setintr)
D 20
			(void) sigsetmask(sigblock(0) & ~ sigmask(SIGINT));
E 20
I 20
			(void) sigsetmask(sigblock(0L) & ~ sigmask(SIGINT));
E 20
		for (ep = environ; *ep; ep++)
			printf("%s\n", *ep);
		return;
	}
	if ((lp = *v++) == 0)
		lp = "";
	setenv(vp, lp = globone(lp));
	if (eq(vp, "PATH")) {
E 16
		importpath(lp);
		dohash();
	}
	xfree(lp);
E 31
I 31
D 57
	if (setintr)
D 34
	    (void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 34
I 34
	    (void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 57
I 57
	if (setintr) {
	    sigemptyset(&sigset);
	    sigaddset(&sigset, SIGINT);
	    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	}
E 57
E 34
	for (ep = STR_environ; *ep; ep++)
D 37
	    xprintf("%s\n", short2str(*ep));
E 37
I 37
D 48
	    (void) fprintf(cshout, "%s\n", short2str(*ep));
E 48
I 48
	    (void) fprintf(cshout, "%s\n", vis_str(*ep));
E 48
E 37
	return;
    }
    if ((lp = *v++) == 0)
	lp = STRNULL;
D 39
    Setenv(vp, lp = globone(lp, G_ERROR));
E 39
I 39
    Setenv(vp, lp = globone(lp, G_APPEND));
E 39
    if (eq(vp, STRPATH)) {
	importpath(lp);
D 37
	dohash();
E 37
I 37
	dohash(NULL, NULL);
E 37
    }
    else if (eq(vp, STRLANG) || eq(vp, STRLC_CTYPE)) {
#ifdef NLS
	int     k;

	(void) setlocale(LC_ALL, "");
D 46
	for (k = 0200; k <= 0377 && !Isprint(k); k++);
E 46
I 46
	for (k = 0200; k <= 0377 && !Isprint(k); k++)
		continue;
E 46
	AsciiOnly = k > 0377;
#else
	AsciiOnly = 0;
#endif				/* NLS */
    }
    xfree((ptr_t) lp);
E 31
}

I 31
void
E 31
D 37
dounsetenv(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
dounsetenv(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
I 31
    Char  **ep, *p, *n;
    int     i, maxi;
    static Char *name = NULL;
E 31

D 31
	v++;
	do
		unsetenv(*v++);
	while (*v);
E 31
I 31
    if (name)
	xfree((ptr_t) name);
    /*
     * Find the longest environment variable
     */
    for (maxi = 0, ep = STR_environ; *ep; ep++) {
D 46
	for (i = 0, p = *ep; *p && *p != '='; p++, i++);
E 46
I 46
	for (i = 0, p = *ep; *p && *p != '='; p++, i++)
	    continue;
E 46
	if (i > maxi)
	    maxi = i;
    }

    name = (Char *) xmalloc((size_t) (maxi + 1) * sizeof(Char));

D 36
    v++;
    maxi = 1;
    while (maxi)
	for (maxi = 0, ep = STR_environ; *ep; ep++) {
	    for (n = name, p = *ep; *p && *p != '='; *n++ = *p++);
	    *n = '\0';
	    if (!Gmatch(name, *v))
		continue;
	    maxi = 1;
	    if (eq(name, STRLANG) || eq(name, STRLC_CTYPE)) {
E 36
I 36
    while (++v && *v)
	for (maxi = 1; maxi;)
	    for (maxi = 0, ep = STR_environ; *ep; ep++) {
D 46
		for (n = name, p = *ep; *p && *p != '='; *n++ = *p++);
E 46
I 46
		for (n = name, p = *ep; *p && *p != '='; *n++ = *p++)
		    continue;
E 46
		*n = '\0';
		if (!Gmatch(name, *v))
		    continue;
		maxi = 1;
		if (eq(name, STRLANG) || eq(name, STRLC_CTYPE)) {
E 36
#ifdef NLS
D 36
		int     k;
E 36
I 36
		    int     k;
E 36

D 36
		(void) setlocale(LC_ALL, "");
		for (k = 0200; k <= 0377 && !Isprint(k); k++);
		AsciiOnly = k > 0377;
E 36
I 36
		    (void) setlocale(LC_ALL, "");
D 46
		    for (k = 0200; k <= 0377 && !Isprint(k); k++);
E 46
I 46
		    for (k = 0200; k <= 0377 && !Isprint(k); k++)
			continue;
E 46
		    AsciiOnly = k > 0377;
E 36
#else
D 36
		AsciiOnly = getenv("LANG") == NULL &&
		    getenv("LC_CTYPE") == NULL;
E 36
I 36
		    AsciiOnly = getenv("LANG") == NULL &&
			getenv("LC_CTYPE") == NULL;
E 36
#endif				/* NLS */
I 36
		}
		/*
		 * Delete name, and start again cause the environment changes
		 */
		Unsetenv(name);
		break;
E 36
	    }
D 36
	    /*
	     * Delete name, and start again cause the environment changes
	     */
	    Unsetenv(name);
	    break;
	}
E 36
D 41
    xfree((ptr_t) name), name = NULL;
E 41
I 41
    xfree((ptr_t) name);
    name = NULL;
E 41
E 31
}

D 13
setenv(name, value)
	char *name, *value;
E 13
I 13
D 31
setenv(name, val)
	char *name, *val;
E 31
I 31
void
Setenv(name, val)
    Char   *name, *val;
E 31
E 13
{
D 31
	register char **ep = environ;
	register char *cp, *dp;
	char *blk[2], **oep = ep;
E 31
I 31
    register Char **ep = STR_environ;
    register Char *cp, *dp;
    Char   *blk[2];
    Char  **oep = ep;
E 31

D 31
	for (; *ep; ep++) {
		for (cp = name, dp = *ep; *cp && *cp == *dp; cp++, dp++)
			continue;
		if (*cp != 0 || *dp != '=')
			continue;
D 13
		cp = strspl("=", value);
E 13
I 13
		cp = strspl("=", val);
E 13
		xfree(*ep);
		*ep = strspl(name, cp);
		xfree(cp);
D 13
		scan(ep, trim);
E 13
I 13
		trim(ep);
E 13
		return;
	}
	blk[0] = strspl(name, "="); blk[1] = 0;
	environ = blkspl(environ, blk);
	xfree((char *)oep);
D 13
	setenv(name, value);
E 13
I 13
	setenv(name, val);
E 31
I 31

    for (; *ep; ep++) {
	for (cp = name, dp = *ep; *cp && *cp == *dp; cp++, dp++)
	    continue;
	if (*cp != 0 || *dp != '=')
	    continue;
	cp = Strspl(STRequal, val);
	xfree((ptr_t) * ep);
	*ep = strip(Strspl(name, cp));
	xfree((ptr_t) cp);
	blkfree((Char **) environ);
	environ = short2blk(STR_environ);
	return;
    }
    cp = Strspl(name, STRequal);
    blk[0] = strip(Strspl(cp, val));
    xfree((ptr_t) cp);
    blk[1] = 0;
    STR_environ = blkspl(STR_environ, blk);
    blkfree((Char **) environ);
    environ = short2blk(STR_environ);
    xfree((ptr_t) oep);
E 31
E 13
}

D 31
unsetenv(name)
	char *name;
E 31
I 31
static void
Unsetenv(name)
    Char   *name;
E 31
{
D 31
	register char **ep = environ;
	register char *cp, *dp;
	char **oep = ep;
E 31
I 31
    register Char **ep = STR_environ;
    register Char *cp, *dp;
    Char  **oep = ep;
E 31

D 31
	for (; *ep; ep++) {
		for (cp = name, dp = *ep; *cp && *cp == *dp; cp++, dp++)
			continue;
		if (*cp != 0 || *dp != '=')
			continue;
		cp = *ep;
		*ep = 0;
		environ = blkspl(environ, ep+1);
		*ep = cp;
		xfree(cp);
		xfree((char *)oep);
		return;
	}
E 31
I 31
    for (; *ep; ep++) {
	for (cp = name, dp = *ep; *cp && *cp == *dp; cp++, dp++)
	    continue;
	if (*cp != 0 || *dp != '=')
	    continue;
	cp = *ep;
	*ep = 0;
	STR_environ = blkspl(STR_environ, ep + 1);
	environ = short2blk(STR_environ);
	*ep = cp;
	xfree((ptr_t) cp);
	xfree((ptr_t) oep);
	return;
    }
E 31
}

I 31
void
E 31
D 37
doumask(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
doumask(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register char *cp = v[1];
	register int i;
E 31
I 31
    register Char *cp = v[1];
    register int i;
E 31

D 31
	if (cp == 0) {
		i = umask(0);
D 13
		umask(i);
E 13
I 13
		(void) umask(i);
E 13
		printf("%o\n", i);
		return;
	}
	i = 0;
	while (digit(*cp) && *cp != '8' && *cp != '9')
		i = i * 8 + *cp++ - '0';
	if (*cp || i < 0 || i > 0777)
		bferr("Improper mask");
E 31
I 31
    if (cp == 0) {
	i = umask(0);
E 31
D 13
	umask(i);
E 13
I 13
	(void) umask(i);
I 31
D 37
	xprintf("%o\n", i);
E 37
I 37
	(void) fprintf(cshout, "%o\n", i);
E 37
	return;
    }
    i = 0;
    while (Isdigit(*cp) && *cp != '8' && *cp != '9')
	i = i * 8 + *cp++ - '0';
    if (*cp || i < 0 || i > 0777)
	stderror(ERR_NAME | ERR_MASK);
    (void) umask(i);
E 31
E 13
}

I 31
D 52
typedef int RLIM_TYPE;
E 52
I 52
typedef quad_t RLIM_TYPE;
E 52
E 31
D 2
#include <sys/limit.h>
E 2
I 2
D 7
#include <sys/vlimit.h>
E 7
E 2

D 31
struct limits {
	int	limconst;
	char	*limname;
	int	limdiv;
	char	*limscale;
} limits[] = {
D 7
	LIM_NORAISE,	"noraise",	1,	"",
	LIM_CPU,	"cputime",	1,	"seconds",
	LIM_FSIZE,	"filesize",	1024,	"kbytes",
	LIM_DATA,	"datasize",	1024,	"kbytes",
	LIM_STACK,	"stacksize",	1024,	"kbytes",
	LIM_CORE,	"coredumpsize",	1024,	"kbytes",
I 3
	LIM_MAXRSS,	"memoryuse",	1024,	"kbytes",
E 7
I 7
	RLIMIT_CPU,	"cputime",	1,	"seconds",
	RLIMIT_FSIZE,	"filesize",	1024,	"kbytes",
	RLIMIT_DATA,	"datasize",	1024,	"kbytes",
	RLIMIT_STACK,	"stacksize",	1024,	"kbytes",
	RLIMIT_CORE,	"coredumpsize",	1024,	"kbytes",
	RLIMIT_RSS,	"memoryuse",	1024,	"kbytes",
E 7
E 3
	-1,		0,
E 31
I 31
static struct limits {
    int     limconst;
    char   *limname;
    int     limdiv;
    char   *limscale;
}       limits[] = {
D 46
    RLIMIT_CPU, 	"cputime",	1,	"seconds",
E 46
I 46
D 55
    RLIMIT_CPU,		"cputime",	1,	"seconds",
E 46
    RLIMIT_FSIZE,	"filesize",	1024,	"kbytes",
    RLIMIT_DATA,	"datasize",	1024,	"kbytes",
    RLIMIT_STACK,	"stacksize",	1024,	"kbytes",
    RLIMIT_CORE,	"coredumpsize", 1024,	"kbytes",
D 46
    RLIMIT_RSS,		"memoryuse", 	1024,	"kbytes",
E 46
I 46
    RLIMIT_RSS,		"memoryuse",	1024,	"kbytes",
E 46
D 33
    -1, 		(char *) 0, 	0,	(char *) 0
E 33
I 33
    RLIMIT_MEMLOCK,	"memorylocked",	1024,	"kbytes",
    RLIMIT_NPROC,	"maxproc",	1,	"",
D 54
    RLIMIT_OFILE,	"openfiles",	1,	"",
E 54
I 54
    RLIMIT_NOFILE,	"openfiles",	1,	"",
E 54
D 46
    -1, 		NULL, 		0,	NULL
E 46
I 46
    -1,			NULL,		0,	NULL
E 55
I 55
    { RLIMIT_CPU,	"cputime",	1,	"seconds" },
    { RLIMIT_FSIZE,	"filesize",	1024,	"kbytes" },
    { RLIMIT_DATA,	"datasize",	1024,	"kbytes" },
    { RLIMIT_STACK,	"stacksize",	1024,	"kbytes" },
    { RLIMIT_CORE,	"coredumpsize", 1024,	"kbytes" },
    { RLIMIT_RSS,	"memoryuse",	1024,	"kbytes" },
    { RLIMIT_MEMLOCK,	"memorylocked",	1024,	"kbytes" },
    { RLIMIT_NPROC,	"maxproc",	1,	"" },
    { RLIMIT_NOFILE,	"openfiles",	1,	"" },
    { -1,		NULL,		0,	NULL }
E 55
E 46
E 33
E 31
};

D 31
struct limits *
E 31
I 31
static struct limits *findlim();
static RLIM_TYPE getval();
static void limtail();
static void plim();
static int setlim();

static struct limits *
E 31
findlim(cp)
D 31
	char *cp;
E 31
I 31
    Char   *cp;
E 31
{
D 31
	register struct limits *lp, *res;
E 31
I 31
    register struct limits *lp, *res;
E 31

D 31
	res = 0;
	for (lp = limits; lp->limconst >= 0; lp++)
		if (prefix(cp, lp->limname)) {
			if (res)
				bferr("Ambiguous");
			res = lp;
		}
	if (res)
		return (res);
	bferr("No such limit");
I 13
	/*NOTREACHED*/
E 31
I 31
    res = (struct limits *) NULL;
    for (lp = limits; lp->limconst >= 0; lp++)
	if (prefix(cp, str2short(lp->limname))) {
	    if (res)
		stderror(ERR_NAME | ERR_AMBIG);
	    res = lp;
	}
    if (res)
	return (res);
    stderror(ERR_NAME | ERR_LIMIT);
    /* NOTREACHED */
    return (0);
E 31
E 13
}

I 31
void
E 31
D 37
dolimit(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
dolimit(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register struct limits *lp;
	register int limit;
I 15
	char hard = 0;
E 31
I 31
    register struct limits *lp;
    register RLIM_TYPE limit;
    char    hard = 0;
E 31
E 15

I 31
    v++;
    if (*v && eq(*v, STRmh)) {
	hard = 1;
E 31
	v++;
I 15
D 19
	if (eq(*v, "-h")) {
E 19
I 19
D 31
	if (*v && eq(*v, "-h")) {
E 19
		hard = 1;
		v++;
	}
E 15
	if (*v == 0) {
D 15
		for (lp = limits+1; lp->limconst >= 0; lp++)
			plim(lp);
E 15
I 15
		for (lp = limits; lp->limconst >= 0; lp++)
			plim(lp, hard);
E 15
D 7
		if (vlimit(LIM_NORAISE, -1) && getuid())
			printf("Limits cannot be raised\n");
E 7
		return;
	}
	lp = findlim(v[0]);
	if (v[1] == 0) {
D 15
		plim(lp);
E 15
I 15
		plim(lp,  hard);
E 15
		return;
	}
	limit = getval(lp, v+1);
D 14
	setlim(lp, limit);
E 14
I 14
D 15
	if (setlim(lp, limit) < 0)
E 15
I 15
	if (setlim(lp, hard, limit) < 0)
E 15
		error(NOSTR);
E 31
I 31
    }
    if (*v == 0) {
	for (lp = limits; lp->limconst >= 0; lp++)
	    plim(lp, hard);
	return;
    }
    lp = findlim(v[0]);
    if (v[1] == 0) {
	plim(lp, hard);
	return;
    }
    limit = getval(lp, v + 1);
    if (setlim(lp, hard, limit) < 0)
	stderror(ERR_SILENT);
E 31
E 14
}

I 31
static  RLIM_TYPE
E 31
getval(lp, v)
D 31
	register struct limits *lp;
	char **v;
E 31
I 31
    register struct limits *lp;
    Char  **v;
E 31
{
D 31
	register float f;
	double atof();
	char *cp = *v++;
E 31
I 31
    register float f;
    double  atof();
    Char   *cp = *v++;
E 31

D 31
	f = atof(cp);
	while (digit(*cp) || *cp == '.' || *cp == 'e' || *cp == 'E')
		cp++;
	if (*cp == 0) {
		if (*v == 0)
			return ((int)(f+0.5) * lp->limdiv);
		cp = *v;
	}
D 7
	if (lp->limconst == LIM_NORAISE)
		goto badscal;
E 7
	switch (*cp) {
E 31
I 31
    f = atof(short2str(cp));
E 31

D 31
	case ':':
D 7
		if (lp->limconst != LIM_CPU)
E 7
I 7
		if (lp->limconst != RLIMIT_CPU)
E 7
			goto badscal;
		return ((int)(f * 60.0 + atof(cp+1)));

	case 'h':
D 7
		if (lp->limconst != LIM_CPU)
E 7
I 7
		if (lp->limconst != RLIMIT_CPU)
E 7
			goto badscal;
		limtail(cp, "hours");
		f *= 3600.;
		break;

	case 'm':
D 7
		if (lp->limconst == LIM_CPU) {
E 7
I 7
		if (lp->limconst == RLIMIT_CPU) {
E 7
			limtail(cp, "minutes");
			f *= 60.;
			break;
		}
	case 'M':
D 7
		if (lp->limconst == LIM_CPU)
E 7
I 7
		if (lp->limconst == RLIMIT_CPU)
E 7
			goto badscal;
		*cp = 'm';
		limtail(cp, "megabytes");
		f *= 1024.*1024.;
		break;

	case 's':
D 7
		if (lp->limconst != LIM_CPU)
E 7
I 7
		if (lp->limconst != RLIMIT_CPU)
E 7
			goto badscal;
		limtail(cp, "seconds");
		break;

	case 'k':
D 7
		if (lp->limconst == LIM_CPU)
E 7
I 7
		if (lp->limconst == RLIMIT_CPU)
E 7
			goto badscal;
		limtail(cp, "kbytes");
		f *= 1024;
		break;

	case 'u':
		limtail(cp, "unlimited");
D 7
		return (INFINITY);
E 7
I 7
		return (RLIM_INFINITY);
E 7

	default:
badscal:
		bferr("Improper or unknown scale factor");
E 31
I 31
    while (Isdigit(*cp) || *cp == '.' || *cp == 'e' || *cp == 'E')
	cp++;
    if (*cp == 0) {
	if (*v == 0)
	    return ((RLIM_TYPE) ((f + 0.5) * lp->limdiv));
	cp = *v;
    }
    switch (*cp) {
    case ':':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	return ((RLIM_TYPE) (f * 60.0 + atof(short2str(cp + 1))));
    case 'h':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	limtail(cp, "hours");
	f *= 3600.0;
	break;
    case 'm':
	if (lp->limconst == RLIMIT_CPU) {
	    limtail(cp, "minutes");
	    f *= 60.0;
	    break;
E 31
	}
D 31
	return ((int)(f+0.5));
E 31
I 31
	*cp = 'm';
	limtail(cp, "megabytes");
	f *= 1024.0 * 1024.0;
	break;
    case 's':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	limtail(cp, "seconds");
	break;
    case 'M':
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
	*cp = 'm';
	limtail(cp, "megabytes");
	f *= 1024.0 * 1024.0;
	break;
    case 'k':
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
	limtail(cp, "kbytes");
	f *= 1024.0;
	break;
    case 'u':
	limtail(cp, "unlimited");
	return (RLIM_INFINITY);
    default:
badscal:
	stderror(ERR_NAME | ERR_SCALEF);
    }
I 40
D 50
    if ((f + 0.5) >= (float) 0x7fffffff || (f + 0.5) < (float) 0x80000000)
	stderror(ERR_NAME | ERR_SCALEF);
E 40
    return ((RLIM_TYPE) (f + 0.5));
E 50
I 50
    f += 0.5;
D 53
    if (f > (float) 0x7fffffff)
	return 0x7fffffff;
    else if (f < (float) 0x80000000)
	return 0x80000000;
E 53
I 53
    if (f > (float) RLIM_INFINITY)
	return RLIM_INFINITY;
E 53
    else
	return ((RLIM_TYPE) f);
E 50
E 31
}

D 31
limtail(cp, str0)
	char *cp, *str0;
E 31
I 31
static void
limtail(cp, str)
    Char   *cp;
    char   *str;
E 31
{
D 31
	register char *str = str0;

	while (*cp && *cp == *str)
		cp++, str++;
	if (*cp)
		error("Bad scaling; did you mean ``%s''?", str0);
E 31
I 31
    while (*cp && *cp == *str)
	cp++, str++;
    if (*cp)
	stderror(ERR_BADSCALE, str);
E 31
}

I 31

/*ARGSUSED*/
static void
E 31
D 15
plim(lp)
E 15
I 15
plim(lp, hard)
E 15
D 31
	register struct limits *lp;
I 15
	char hard;
E 31
I 31
    register struct limits *lp;
    Char    hard;
E 31
E 15
{
D 7
	register int lim;
E 7
I 7
D 31
	struct rlimit rlim;
I 15
	int limit;
E 31
I 31
    struct rlimit rlim;
    RLIM_TYPE limit;
E 31
E 15
E 7

D 31
	printf("%s \t", lp->limname);
D 7
	lim = vlimit(lp->limconst, -1);
	if (lim == INFINITY)
E 7
I 7
D 13
	getrlimit(lp->limconst, &rlim);
E 13
I 13
	(void) getrlimit(lp->limconst, &rlim);
E 13
D 15
	if (rlim.rlim_cur == RLIM_INFINITY)
E 15
I 15
	limit = hard ? rlim.rlim_max : rlim.rlim_cur;
	if (limit == RLIM_INFINITY)
E 15
E 7
		printf("unlimited");
D 7
	else if (lp->limconst == LIM_CPU)
		psecs((long)lim);
E 7
I 7
	else if (lp->limconst == RLIMIT_CPU)
D 15
		psecs((long)rlim.rlim_cur);
E 15
I 15
		psecs((long)limit);
E 15
E 7
	else
D 7
		printf("%d %s", lim / lp->limdiv, lp->limscale);
E 7
I 7
D 15
		printf("%d %s", rlim.rlim_cur / lp->limdiv, lp->limscale);
E 15
I 15
		printf("%d %s", limit / lp->limdiv, lp->limscale);
E 15
E 7
	printf("\n");
E 31
I 31
D 37
    xprintf("%s \t", lp->limname);
E 37
I 37
    (void) fprintf(cshout, "%s \t", lp->limname);
E 37

    (void) getrlimit(lp->limconst, &rlim);
    limit = hard ? rlim.rlim_max : rlim.rlim_cur;

    if (limit == RLIM_INFINITY)
D 37
	xprintf("unlimited");
E 37
I 37
	(void) fprintf(cshout, "unlimited");
E 37
    else if (lp->limconst == RLIMIT_CPU)
	psecs((long) limit);
    else
D 37
	xprintf("%ld %s", (long) (limit / lp->limdiv), lp->limscale);
    xprintf("\n");
E 37
I 37
D 46
	(void) fprintf(cshout, "%ld %s", (long) (limit / lp->limdiv), 
E 46
I 46
	(void) fprintf(cshout, "%ld %s", (long) (limit / lp->limdiv),
E 46
		       lp->limscale);
    (void) fputc('\n', cshout);
E 37
E 31
}

I 31
void
E 31
D 37
dounlimit(v)
D 31
	register char **v;
E 31
I 31
    register Char **v;
E 37
I 37
/*ARGSUSED*/
dounlimit(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	register struct limits *lp;
I 14
	int err = 0;
I 15
	char hard = 0;
E 31
I 31
    register struct limits *lp;
    int     lerr = 0;
    Char    hard = 0;
E 31
E 15
E 14

I 31
    v++;
    if (*v && eq(*v, STRmh)) {
	hard = 1;
E 31
	v++;
I 15
D 19
	if (eq(*v, "-h")) {
E 19
I 19
D 31
	if (*v && eq(*v, "-h")) {
E 19
		hard = 1;
		v++;
	}
E 15
	if (*v == 0) {
D 15
		for (lp = limits+1; lp->limconst >= 0; lp++)
D 7
			setlim(lp, INFINITY);
E 7
I 7
D 13
			setlim(lp, RLIM_INFINITY);
E 13
I 13
D 14
			setlim(lp, (int)RLIM_INFINITY);
E 14
I 14
			if (setlim(lp, (int)RLIM_INFINITY) < 0)
E 15
I 15
		for (lp = limits; lp->limconst >= 0; lp++)
			if (setlim(lp, hard, (int)RLIM_INFINITY) < 0)
E 15
				err++;
		if (err)
			error(NOSTR);
E 14
E 13
E 7
		return;
	}
	while (*v) {
		lp = findlim(*v++);
D 7
		setlim(lp, INFINITY);
E 7
I 7
D 13
		setlim(lp, RLIM_INFINITY);
E 13
I 13
D 14
		setlim(lp, (int)RLIM_INFINITY);
E 14
I 14
D 15
		if (setlim(lp, (int)RLIM_INFINITY) < 0)
E 15
I 15
		if (setlim(lp, hard, (int)RLIM_INFINITY) < 0)
E 15
			error(NOSTR);
E 14
E 13
E 7
	}
E 31
I 31
    }
    if (*v == 0) {
	for (lp = limits; lp->limconst >= 0; lp++)
	    if (setlim(lp, hard, (RLIM_TYPE) RLIM_INFINITY) < 0)
		lerr++;
	if (lerr)
	    stderror(ERR_SILENT);
	return;
    }
    while (*v) {
	lp = findlim(*v++);
	if (setlim(lp, hard, (RLIM_TYPE) RLIM_INFINITY) < 0)
	    stderror(ERR_SILENT);
    }
E 31
}

I 31
static int
E 31
D 15
setlim(lp, limit)
E 15
I 15
setlim(lp, hard, limit)
E 15
D 31
	register struct limits *lp;
I 15
	char hard;
E 31
I 31
    register struct limits *lp;
    Char    hard;
    RLIM_TYPE limit;
E 31
E 15
{
I 7
D 31
	struct rlimit rlim;
E 31
I 31
    struct rlimit rlim;
E 31
E 7

D 7
	if (vlimit(lp->limconst, limit) < 0)
E 7
I 7
D 13
	getrlimit(lp->limconst, &rlim);
E 13
I 13
D 31
	(void) getrlimit(lp->limconst, &rlim);
E 13
D 11
	rlim.rlim_cur = limit;
E 11
I 11
D 14
  	if(limit == RLIM_INFINITY && geteuid() != 0)
E 14
I 14
D 15
  	if (limit == RLIM_INFINITY && geteuid() != 0)
E 15
I 15
	if (hard)
		rlim.rlim_max = limit;
  	else if (limit == RLIM_INFINITY && geteuid() != 0)
E 15
E 14
 		rlim.rlim_cur = rlim.rlim_max;
 	else
D 13
 		rlim.rlim_cur = limit;     
E 13
I 13
 		rlim.rlim_cur = limit;
E 13
E 11
D 14
	if (setrlimit(lp->limconst, &rlim) < 0)
E 7
		Perror(bname);
E 14
I 14
	if (setrlimit(lp->limconst, &rlim) < 0) {
D 15
		printf("%s: %s: Can't %s limit\n", bname, lp->limname,
		    limit == RLIM_INFINITY ? "remove" : "set");
E 15
I 15
		printf("%s: %s: Can't %s%s limit\n", bname, lp->limname,
		    limit == RLIM_INFINITY ? "remove" : "set",
		    hard ? " hard" : "");
E 15
		return (-1);
	}
	return (0);
E 31
I 31
    (void) getrlimit(lp->limconst, &rlim);

    if (hard)
	rlim.rlim_max = limit;
    else if (limit == RLIM_INFINITY && geteuid() != 0)
	rlim.rlim_cur = rlim.rlim_max;
    else
	rlim.rlim_cur = limit;

    if (setrlimit(lp->limconst, &rlim) < 0) {
D 37
	xprintf("%s: %s: Can't %s%s limit\n", bname, lp->limname,
		limit == RLIM_INFINITY ? "remove" : "set",
		hard ? " hard" : "");
E 37
I 37
	(void) fprintf(csherr, "%s: %s: Can't %s%s limit\n", bname, lp->limname,
		       limit == RLIM_INFINITY ? "remove" : "set",
		       hard ? " hard" : "");
E 37
	return (-1);
    }
    return (0);
E 31
E 14
}

I 31
void
E 31
D 37
dosuspend()
E 37
I 37
/*ARGSUSED*/
dosuspend(v, t)
    Char **v;
    struct command *t;
E 37
{
I 25
D 31
	sig_t old;
E 25
D 9
	int old, ldisc;
E 9
I 9
D 12
	int (*old)(), ldisc;
E 9
D 8
	short ctpgrp;
E 8
I 8
	int ctpgrp;
E 12
I 12
	int ldisc, ctpgrp;
E 31
I 31
    int     ctpgrp;
E 31
D 25
	int (*old)();
E 25
E 12
E 8

D 31
	if (loginsh)
		error("Can't suspend a login shell (yet)");
	untty();
D 9
	old = sigsys(SIGTSTP, SIG_DFL);
E 9
I 9
D 10
	old = signal(SIGTSTP, SIG_DFL);
E 10
I 10
D 12
	old = sigsys(SIGTSTP, SIG_DFL);
E 12
I 12
	old = signal(SIGTSTP, SIG_DFL);
E 12
E 10
E 9
D 13
	kill(0, SIGTSTP);
E 13
I 13
	(void) kill(0, SIGTSTP);
E 13
	/* the shell stops here */
D 9
	sigsys(SIGTSTP, old);
E 9
I 9
D 10
	signal(SIGTSTP, old);
E 10
I 10
D 12
	sigsys(SIGTSTP, old);
E 12
I 12
D 13
	signal(SIGTSTP, old);
E 13
I 13
	(void) signal(SIGTSTP, old);
E 13
E 12
E 10
E 9
	if (tpgrp != -1) {
E 31
I 31
    void    (*old) ();

    if (loginsh)
	stderror(ERR_SUSPLOG);
    untty();

    old = signal(SIGTSTP, SIG_DFL);
    (void) kill(0, SIGTSTP);
    /* the shell stops here */
    (void) signal(SIGTSTP, old);

    if (tpgrp != -1) {
E 31
D 37
retry:
E 37
D 13
		ioctl(FSHTTY, TIOCGPGRP, &ctpgrp);
E 13
I 13
D 31
		(void) ioctl(FSHTTY, TIOCGPGRP, (char *)&ctpgrp);
E 13
		if (ctpgrp != opgrp) {
D 9
			old = sigsys(SIGTTIN, SIG_DFL);
E 9
I 9
D 10
			old = signal(SIGTTIN, SIG_DFL);
E 10
I 10
D 12
			old = sigsys(SIGTTIN, SIG_DFL);
E 12
I 12
			old = signal(SIGTTIN, SIG_DFL);
E 12
E 10
E 9
D 13
			kill(0, SIGTTIN);
D 9
			sigsys(SIGTTIN, old);
E 9
I 9
D 10
			signal(SIGTTIN, old);
E 10
I 10
D 12
			sigsys(SIGTTIN, old);
E 12
I 12
			signal(SIGTTIN, old);
E 13
I 13
			(void) kill(0, SIGTTIN);
			(void) signal(SIGTTIN, old);
E 13
E 12
E 10
E 9
			goto retry;
		}
D 13
		ioctl(FSHTTY, TIOCSPGRP, &shpgrp);
		setpgrp(0, shpgrp);
E 13
I 13
D 26
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&shpgrp);
E 26
		(void) setpgrp(0, shpgrp);
I 26
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&shpgrp);
E 31
I 31
	ctpgrp = tcgetpgrp(FSHTTY);
D 37
	if (ctpgrp != opgrp) {
E 37
I 37
	while  (ctpgrp != opgrp) {
E 37
	    old = signal(SIGTTIN, SIG_DFL);
	    (void) kill(0, SIGTTIN);
	    (void) signal(SIGTTIN, old);
D 37
	    goto retry;
E 37
E 31
E 26
E 13
	}
I 31
	(void) setpgid(0, shpgrp);
	(void) tcsetpgrp(FSHTTY, shpgrp);
    }
E 31
D 13
	ioctl(FSHTTY, TIOCGETD, &oldisc);
E 13
I 13
D 24
	(void) ioctl(FSHTTY, TIOCGETD, (char *)&oldisc);
E 13
	if (oldisc != NTTYDISC) {
		printf("Switching to new tty driver...\n");
		ldisc = NTTYDISC;
D 13
		ioctl(FSHTTY, TIOCSETD, &ldisc);
E 13
I 13
		(void) ioctl(FSHTTY, TIOCSETD, (char *)&ldisc);
E 13
	}
E 24
}

I 31
/* This is the dreaded EVAL built-in.
 *   If you don't fiddle with file descriptors, and reset didfds,
 *   this command will either ignore redirection inside or outside
 *   its aguments, e.g. eval "date >x"  vs.  eval "date" >x
 *   The stuff here seems to work, but I did it by trial and error rather
 *   than really knowing what was going on.  If tpgrp is zero, we are
 *   probably a background eval, e.g. "eval date &", and we want to
 *   make sure that any processes we start stay in our pgrp.
 *   This is also the case for "time eval date" -- stay in same pgrp.
 *   Otherwise, under stty tostop, processes will stop in the wrong
 *   pgrp, with no way for the shell to get them going again.  -IAN!
 */
I 37
static Char **gv = NULL;
E 37
void
E 31
D 37
doeval(v)
D 31
	char **v;
E 31
I 31
    Char  **v;
E 37
I 37
/*ARGSUSED*/
doeval(v, t)
    Char **v;
    struct command *t;
E 37
E 31
{
D 31
	char **oevalvec = evalvec;
	char *oevalp = evalp;
	jmp_buf osetexit;
	int reenter;
	char **gv = 0;
E 31
I 31
    Char  **oevalvec;
    Char   *oevalp;
    int     odidfds;
    jmp_buf osetexit;
    int     my_reenter;
D 37
    Char  **gv;
E 37
I 37
    Char  **savegv = gv;
E 37
    int     saveIN;
    int     saveOUT;
D 37
    int     saveDIAG;
E 37
I 37
    int     saveERR;
E 37
    int     oSHIN;
    int     oSHOUT;
D 37
    int     oSHDIAG;
E 37
I 37
    int     oSHERR;
I 55

    UNREGISTER(v);
E 55
E 37
E 31

D 31
	v++;
	if (*v == 0)
		return;
D 13
	gflag = 0; rscan(v, tglob);
E 13
I 13
	gflag = 0, tglob(v);
E 13
	if (gflag) {
D 27
		gv = v = glob(v);
E 27
I 27
		gv = v = globall(v);
E 27
		gargv = 0;
		if (v == 0)
			error("No match");
		v = copyblk(v);
	} else
D 13
		scan(v, trim);
E 13
I 13
		trim(v);
E 13
	getexit(osetexit);
	reenter = 0;
D 29
	setexit();
E 29
I 29
	(void)setjmp(reslab);
E 29
	reenter++;
	if (reenter == 1) {
		evalvec = v;
		evalp = 0;
		process(0);
	}
	evalvec = oevalvec;
	evalp = oevalp;
	doneinp = 0;
	if (gv)
		blkfree(gv);
	resexit(osetexit);
	if (reenter >= 2)
		error(NOSTR);
E 31
I 31
    oevalvec = evalvec;
    oevalp = evalp;
    odidfds = didfds;
    oSHIN = SHIN;
    oSHOUT = SHOUT;
D 37
    oSHDIAG = SHDIAG;
E 37
I 37
    oSHERR = SHERR;
E 37

    v++;
    if (*v == 0)
	return;
    gflag = 0, tglob(v);
    if (gflag) {
	gv = v = globall(v);
	gargv = 0;
	if (v == 0)
	    stderror(ERR_NOMATCH);
	v = copyblk(v);
    }
    else {
D 33
	gv = (Char **) 0;
E 33
I 33
	gv = NULL;
E 33
	v = copyblk(v);
	trim(v);
    }

    saveIN = dcopy(SHIN, -1);
    saveOUT = dcopy(SHOUT, -1);
D 37
    saveDIAG = dcopy(SHDIAG, -1);
E 37
I 37
    saveERR = dcopy(SHERR, -1);
E 37

    getexit(osetexit);

    if ((my_reenter = setexit()) == 0) {
	evalvec = v;
	evalp = 0;
	SHIN = dcopy(0, -1);
	SHOUT = dcopy(1, -1);
D 37
	SHDIAG = dcopy(2, -1);
E 37
I 37
	SHERR = dcopy(2, -1);
E 37
	didfds = 0;
	process(0);
    }

    evalvec = oevalvec;
    evalp = oevalp;
    doneinp = 0;
    didfds = odidfds;
    (void) close(SHIN);
    (void) close(SHOUT);
D 37
    (void) close(SHDIAG);
E 37
I 37
    (void) close(SHERR);
E 37
    SHIN = dmove(saveIN, oSHIN);
    SHOUT = dmove(saveOUT, oSHOUT);
D 37
    SHDIAG = dmove(saveDIAG, oSHDIAG);

E 37
I 37
    SHERR = dmove(saveERR, oSHERR);
E 37
    if (gv)
D 37
	blkfree(gv);
E 37
I 37
	blkfree(gv), gv = NULL;
E 37
    resexit(osetexit);
I 37
    gv = savegv;
E 37
    if (my_reenter)
	stderror(ERR_SILENT);
E 31
}
I 38

void
/*ARGSUSED*/
doprintf(v, t)
    Char **v;
    struct command *t;
{
    char **c;
    extern int progprintf __P((int, char **));
    int ret;
D 46
    
E 46
I 46

E 46
    ret = progprintf(blklen(v), c = short2blk(v));
I 51
    (void) fflush(cshout);
    (void) fflush(csherr);
E 51

    blkfree((Char **) c);
    if (ret)
	stderror(ERR_SILENT);
}
D 46

E 46
E 38
E 1
