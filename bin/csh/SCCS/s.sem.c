h45649
s 00001/00001/00626
d D 8.3 95/04/29 13:09:09 christos 32 31
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00022/00014/00605
d D 8.2 95/03/22 14:12:33 christos 31 30
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/00617
d D 8.1 93/05/31 16:42:53 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00005/00610
d D 5.23 93/05/22 19:06:48 christos 29 28
c Fixed gcc -Wall warnings
e
s 00001/00001/00614
d D 5.22 91/11/06 16:09:53 christos 28 27
c Added support for displaying non-printable characters
e
s 00067/00011/00548
d D 5.21 91/11/04 18:20:55 christos 27 26
c Added noambiguous
e
s 00015/00003/00544
d D 5.20 91/09/04 01:37:26 christos 26 25
c Fix for -n flag. Contine execution for some `special' builtins
e
s 00009/00009/00538
d D 5.19 91/07/19 17:31:25 christos 25 24
c stdio based version; brace glob fix; builtin prototypes
e
s 00005/00003/00542
d D 5.18 91/07/01 21:16:17 christos 24 23
c Fixed memory leak  > [filename] filename not freed.
e
s 00014/00015/00531
d D 5.17 91/06/17 14:53:02 christos 23 22
c Fixed MAXPATHLEN limit problem
e
s 00006/00000/00540
d D 5.16 91/06/08 17:09:04 christos 22 21
c More prototype fixes, Removed TERMIOS define
e
s 00015/00008/00525
d D 5.15 91/06/08 12:20:37 bostic 21 20
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00006/00005/00527
d D 5.14 91/06/07 20:57:40 christos 20 19
c static function prototypes
e
s 00005/00023/00527
d D 5.13 91/06/07 11:13:41 bostic 19 18
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00470/00365/00080
d D 5.12 91/06/04 13:31:58 bostic 18 17
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00438
d D 5.11 91/04/04 18:17:57 bostic 17 16
c new copyright; att/bsd/shared
e
s 00064/00057/00380
d D 5.10 91/04/01 17:37:20 bostic 16 15
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00001/00001/00436
d D 5.9 91/03/14 12:30:31 bostic 15 14
c any -> index (use the faster library routine)
e
s 00002/00003/00435
d D 5.8 90/04/14 14:17:15 mckusick 14 13
c use O_APPEND instead of open/lseek (4.3BSD-tahoe/bin/32)
e
s 00000/00031/00438
d D 5.7 89/11/20 17:52:44 marc 13 12
c remove debugging ifdefs
e
s 00071/00007/00398
d D 5.6 89/11/20 17:42:25 marc 12 11
c POSIX Job Control
e
s 00001/00001/00404
d D 5.5 87/06/25 09:15:24 bostic 11 10
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00014/00005/00391
d D 5.4 86/05/13 01:08:33 lepreau 10 9
c nice is absolute after all; comment the problem Sun has with signal status
c getting zapped by vfork'ed child
e
s 00003/00002/00393
d D 5.3 86/01/12 02:34:15 lepreau 9 8
c nice is relative, not absolute. (Kirk "authorized" it.)
e
s 00003/00003/00392
d D 5.2 85/06/06 13:10:22 edward 8 7
c cleaning up after bozos
e
s 00008/00002/00387
d D 5.1 85/06/04 11:07:36 dist 7 6
c Add copyright
e
s 00003/00003/00386
d D 4.6 85/01/16 14:26:44 edward 6 5
c don't need to turn off close-on-exec after dup any more
e
s 00059/00044/00330
d D 4.5 84/12/13 14:40:58 edward 5 4
c performance
e
s 00018/00017/00356
d D 4.4 84/08/31 09:31:31 ralph 4 3
c use new signal calls instead of compatibility routines.
e
s 00013/00013/00360
d D 4.3 83/06/11 16:50:05 sam 3 2
c different approach, try signal compatibility package
e
s 00017/00013/00356
d D 4.2 83/06/10 23:59:48 sam 2 1
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00369/00000/00000
d D 4.1 80/10/09 12:41:47 bill 1 0
c date and time created 80/10/09 12:41:47 by bill
e
u
U
t
T
I 7
D 17
/*
 * Copyright (c) 1980 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
E 8
I 8
 * All rights reserved.  The Berkeley Software License Agreement
E 8
 * specifies the terms and conditions for redistribution.
E 17
I 17
/*-
D 30
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * %sccs.include.redist.c%
E 17
 */

E 7
I 1
D 5
static	char *sccsid = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
D 7
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 7
I 7
D 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 8
I 8
D 17
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 17
I 17
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 17
E 8
E 7
E 5

I 21
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 22
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 22
E 21
D 19
#include "sh.h"
I 18
#include "sh.dir.h"
E 18
#include "sh.proc.h"
E 19
I 19
#include "csh.h"
D 21
#include "dir.h"
E 21
#include "proc.h"
#include "extern.h"
E 19
I 14
D 18
#include <sys/file.h>
E 14
#include <sys/ioctl.h>
I 12
#include "pathnames.h"
E 18
E 12

I 18
D 19
#ifdef VFORK
E 19
D 20
static void vffree();
D 19

#endif
E 19
static void doio();
static void chkclob();
E 20
I 20
D 27
static void	vffree __P((int));
static void	doio __P((struct command *t, int *, int *));
D 23
static void	chkclob __P((Char *));
E 23
I 23
static void	chkclob __P((char *));
E 27
I 27
static void	 vffree __P((int));
static Char	*splicepipe __P((struct command *t, Char *));
static void	 doio __P((struct command *t, int *, int *));
static void	 chkclob __P((char *));
E 27
E 23
E 20

E 18
D 19
/*
 * C shell
 */
D 18

I 12
static int nosigchld = 0, osigmask;
static int onosigchld = 0, oosigmask;
E 18
E 12
/*VARARGS 1*/
E 19
I 18
void
E 18
execute(t, wanttty, pipein, pipeout)
D 18
	register struct command *t;
	int wanttty, *pipein, *pipeout;
E 18
I 18
    register struct command *t;
    int     wanttty, *pipein, *pipeout;
E 18
{
D 18
	bool forked = 0;
	struct biltins *bifunc;
	int pid = 0;
	int pv[2];
E 18
I 18
    bool    forked = 0;
    struct biltins *bifunc;
    int     pid = 0;
    int     pv[2];
I 31
    sigset_t sigset;
E 31
E 18

D 18
	if (t == 0)
		return;
I 12
D 13
#ifdef REMOVE_THIS 
{ short x=t->t_dtyp;
int flg = t->t_dflg;
printf("execute: cmd=%s pid=%d t_dtyp=%s wanttty=%d ", t->t_dcom[0], getpid(), 
	x == TCOM ? "TCOM" : x == TPAR ? "TPAR" : x == TFIL ? "TFIL" : 
	x == TLST ? "TLST" : x == TOR ? "TOR" : x == TAND ? "TAND" : "UNKNOWN",
	wanttty);
if (flg&FAND) printf("FAND "); if (flg&FCAT) printf("FCAT ");
if (flg&FPIN) printf("FPIN "); if (flg&FPOU) printf("FPOU ");
if (flg&FPAR) printf("FPAR "); if (flg&FINT) printf("FINT ");
if (flg&FDIAG) printf("FDIAG "); if (flg&FANY) printf("FANY ");
if (flg&FHERE) printf("FHERE "); if (flg&FREDO) printf("FREDO ");
if (flg&FNICE) printf("FNICE "); if (flg&FNOHUP) printf("FNOHUP ");
if (flg&FTIME) printf("FTIME "); printf("\n");
}
#endif
E 13
E 12
D 16
	if ((t->t_dflg & FAND) && wanttty > 0)
E 16
I 16
	if ((t->t_dflg & F_AMPERSAND) && wanttty > 0)
E 16
		wanttty = 0;
	switch (t->t_dtyp) {
E 18
I 18
D 21
    static sigmask_t csigmask;
E 21
I 21
D 31
    static sigset_t csigmask;
E 31
I 31
    static sigset_t csigset;
E 31
E 21
E 18

D 16
	case TCOM:
E 16
I 16
D 18
	case NODE_COMMAND:
E 16
		if ((t->t_dcom[0][0] & (QUOTE|TRIM)) == QUOTE)
D 5
			strcpy(t->t_dcom[0], t->t_dcom[0] + 1);
E 5
I 5
			(void) strcpy(t->t_dcom[0], t->t_dcom[0] + 1);
E 5
D 16
		if ((t->t_dflg & FREDO) == 0)
E 16
I 16
		if ((t->t_dflg & F_REPEAT) == 0)
E 16
			Dfix(t);		/* $ " ' \ */
		if (t->t_dcom[0] == 0)
			return;
		/* fall into... */
E 18
I 18
D 19
#ifdef VFORK
E 19
D 21
    static sigmask_t ocsigmask;
E 21
I 21
D 31
    static sigset_t ocsigmask;
E 31
I 31
    static sigset_t ocsigset;
E 31
E 21
E 18
D 19

D 16
	case TPAR:
		if (t->t_dflg & FPOU)
E 16
I 16
D 18
	case NODE_PAREN:
		if (t->t_dflg & F_PIPEOUT)
E 16
			mypipe(pipeout);
		/*
		 * Must do << early so parent will know
		 * where input pointer should be.
		 * If noexec then this is all we do.
		 */
D 16
		if (t->t_dflg & FHERE) {
E 16
I 16
		if (t->t_dflg & F_READ) {
E 16
D 5
			close(0);
E 5
I 5
			(void) close(0);
E 5
			heredoc(t->t_dlef);
			if (noexec)
D 5
				close(0);
E 5
I 5
				(void) close(0);
E 5
		}
		if (noexec)
			break;
E 18
I 18
#endif				/* VFORK */
E 19
    static int onosigchld = 0;
    static int nosigchld = 0;
E 18

I 29
    UNREGISTER(forked);
    UNREGISTER(bifunc);
    UNREGISTER(wanttty);

E 29
D 18
		set("status", "0");
E 18
I 18
    if (t == 0)
	return;
E 18

D 18
		/*
		 * This mess is the necessary kludge to handle the prefix
		 * builtins: nice, nohup, time.  These commands can also
		 * be used by themselves, and this is not handled here.
		 * This will also work when loops are parsed.
		 */
D 16
		while (t->t_dtyp == TCOM)
E 16
I 16
		while (t->t_dtyp == NODE_COMMAND)
E 16
			if (eq(t->t_dcom[0], "nice"))
				if (t->t_dcom[1])
D 15
					if (any(t->t_dcom[1][0], "+-"))
E 15
I 15
					if (index("+-", t->t_dcom[1][0]))
E 15
						if (t->t_dcom[2]) {
							setname("nice");
							t->t_nice = getn(t->t_dcom[1]);
							lshift(t->t_dcom, 2);
D 16
							t->t_dflg |= FNICE;
E 16
I 16
							t->t_dflg |= F_NICE;
E 16
						} else
							break;
					else {
						t->t_nice = 4;
						lshift(t->t_dcom, 1);
D 16
						t->t_dflg |= FNICE;
E 16
I 16
						t->t_dflg |= F_NICE;
E 16
					}
				else
					break;
			else if (eq(t->t_dcom[0], "nohup"))
				if (t->t_dcom[1]) {
D 16
					t->t_dflg |= FNOHUP;
E 16
I 16
					t->t_dflg |= F_NOHUP;
E 16
					lshift(t->t_dcom, 1);
				} else
					break;
			else if (eq(t->t_dcom[0], "time"))
				if (t->t_dcom[1]) {
D 16
					t->t_dflg |= FTIME;
E 16
I 16
					t->t_dflg |= F_TIME;
E 16
					lshift(t->t_dcom, 1);
				} else
					break;
			else
				break;
		/*
		 * Check if we have a builtin function and remember which one.
		 */
D 16
		bifunc = t->t_dtyp == TCOM ? isbfunc(t) : (struct biltins *) 0;
E 16
I 16
		bifunc = t->t_dtyp ==
		    NODE_COMMAND ? isbfunc(t) : (struct biltins *) 0;
E 18
I 18
    if (t->t_dflg & F_AMPERSAND)
	wanttty = 0;
    switch (t->t_dtyp) {
E 18
E 16

D 18
		/*
		 * We fork only if we are timed, or are not the end of
		 * a parenthesized list and not a simple builtin function.
		 * Simple meaning one that is not pipedout, niced, nohupped,
		 * or &'d.
		 * It would be nice(?) to not fork in some of these cases.
		 */
D 16
		if (((t->t_dflg & FTIME) || (t->t_dflg & FPAR) == 0 &&
		     (!bifunc || t->t_dflg & (FPOU|FAND|FNICE|FNOHUP))))
E 16
I 16
		if (((t->t_dflg & F_TIME) || (t->t_dflg & F_NOFORK) == 0 &&
		    (!bifunc ||
		    t->t_dflg & (F_PIPEOUT|F_AMPERSAND|F_NICE|F_NOHUP))))
E 16
#ifdef VFORK
D 16
		    if (t->t_dtyp == TPAR || t->t_dflg&(FREDO|FAND) || bifunc)
E 16
I 16
		    if (t->t_dtyp == NODE_PAREN ||
			t->t_dflg&(F_REPEAT|F_AMPERSAND) || bifunc)
E 16
#endif
D 12
			{ forked++; pid = pfork(t, wanttty); }
E 12
I 12
			{ forked++; 
			  if (wanttty >= 0 && !nosigchld) {
D 13
#ifdef REMOVE_THIS
				printf("(%d) blocking sigchld\n", getpid());
#endif
E 13
				osigmask = sigblock(sigmask(SIGCHLD));
				nosigchld = 1;
			  }
E 18
I 18
    case NODE_COMMAND:
	if ((t->t_dcom[0][0] & (QUOTE | TRIM)) == QUOTE)
	    (void) Strcpy(t->t_dcom[0], t->t_dcom[0] + 1);
	if ((t->t_dflg & F_REPEAT) == 0)
	    Dfix(t);		/* $ " ' \ */
	if (t->t_dcom[0] == 0)
	    return;
	/* fall into... */
E 18

D 18
			  pid = pfork(t, wanttty);
			  if (pid == 0 && nosigchld) {
D 13
#ifdef REMOVE_THIS
				printf("%d unblocking sigchld after fork\n", getpid());
#endif
E 13
				sigsetmask(osigmask);
				nosigchld = 0;
			  }
			}
E 12
#ifdef VFORK
		    else {
D 12
			int vffree();
E 12
I 12
			sig_t vffree;
E 12
D 5
			int ochild, osetintr, ohaderr, odidfds, odidcch;
E 5
I 5
			int ochild, osetintr, ohaderr, odidfds;
E 5
			int oSHIN, oSHOUT, oSHDIAG, oOLDSTD, otpgrp;
I 4
D 11
			int omask;
E 11
I 11
			long omask;
E 18
I 18
    case NODE_PAREN:
	if (t->t_dflg & F_PIPEOUT)
	    mypipe(pipeout);
	/*
	 * Must do << early so parent will know where input pointer should be.
	 * If noexec then this is all we do.
	 */
	if (t->t_dflg & F_READ) {
	    (void) close(0);
	    heredoc(t->t_dlef);
	    if (noexec)
		(void) close(0);
	}
D 26
	if (noexec)
	    break;
E 26
E 18
E 11
E 4

I 10
D 18
			/* 
			 * Prepare for the vfork by saving everything
			 * that the child corrupts before it exec's.
			 * Note that in some signal implementations
			 * which keep the signal info in user space
			 * (e.g. Sun's) it will also be necessary to
 			 * save and restore the current sigvec's for
			 * the signals the child touches before it
			 * exec's.
			 */
I 12
			if (wanttty >= 0 && !nosigchld && !noexec) {
D 13
#ifdef REMOVE_THIS
				printf("(%d) blocking sigchld\n", getpid());
#endif
E 13
				osigmask = sigblock(sigmask(SIGCHLD));
				nosigchld = 1;
			}
E 12
E 10
D 2
			sighold(SIGCHLD);
E 2
I 2
D 3
			(void) sigblock(mask(SIGCHLD));
E 3
I 3
D 4
			sighold(SIGCHLD);
E 4
I 4
			omask = sigblock(sigmask(SIGCHLD));
E 4
E 3
E 2
			ochild = child; osetintr = setintr;
D 5
			ohaderr = haderr; odidfds = didfds; odidcch = didcch;
E 5
I 5
			ohaderr = haderr; odidfds = didfds;
E 5
			oSHIN = SHIN; oSHOUT = SHOUT;
			oSHDIAG = SHDIAG; oOLDSTD = OLDSTD; otpgrp = tpgrp;
I 12
			oosigmask = osigmask; onosigchld = nosigchld;
E 12
			Vsav = Vdp = 0; Vav = 0;
			pid = vfork();
			if (pid < 0) {
D 2
				sigrelse(SIGCHLD);
E 2
I 2
D 3
				(void) sigrelse(mask(SIGCHLD));
E 3
I 3
D 4
				sigrelse(SIGCHLD);
E 4
I 4
D 5
				sigsetmask(omask);
E 5
I 5
				(void) sigsetmask(omask);
E 5
E 4
E 3
E 2
				error("No more processes");
			}
			forked++;
D 10
			if (pid) {
E 10
I 10
			if (pid) {	/* parent */
E 10
				child = ochild; setintr = osetintr;
				haderr = ohaderr; didfds = odidfds;
D 5
				didcch = odidcch; SHIN = oSHIN;
E 5
I 5
				SHIN = oSHIN;
E 5
				SHOUT = oSHOUT; SHDIAG = oSHDIAG;
				OLDSTD = oOLDSTD; tpgrp = otpgrp;
I 12
				osigmask = oosigmask; nosigchld = onosigchld;
E 12
				xfree(Vsav); Vsav = 0;
				xfree(Vdp); Vdp = 0;
D 5
				xfree(Vav); Vav = 0;
E 5
I 5
				xfree((char *)Vav); Vav = 0;
E 5
				/* this is from pfork() */
				palloc(pid, t);
D 2
				sigrelse(SIGCHLD);
E 2
I 2
D 3
				(void) sigrelse(mask(SIGCHLD));
E 3
I 3
D 4
				sigrelse(SIGCHLD);
E 4
I 4
D 5
				sigsetmask(omask);
E 5
I 5
				(void) sigsetmask(omask);
E 5
E 4
E 3
E 2
D 10
			} else {
E 10
I 10
			} else {	/* child */
E 10
				/* this is from pfork() */
				int pgrp;
				bool ignint = 0;
E 18
I 18
	set(STRstatus, Strsave(STR0));
E 18

I 12
D 18
				if (nosigchld) {
D 13
#ifdef REMOVE_THIS
					printf("%d unblocking sigchld after fork\n", getpid());
#endif
E 13
					sigsetmask(osigmask);
					nosigchld = 0;
				}
E 12
				if (setintr)
D 16
					ignint =
					    (tpgrp == -1 && (t->t_dflg&FINT))
					    || gointr && eq(gointr, "-");
E 16
I 16
					ignint = (tpgrp == -1 &&
					    (t->t_dflg&F_NOINTERRUPT)) ||
					    gointr && eq(gointr, "-");
E 16
				pgrp = pcurrjob ? pcurrjob->p_jobid : getpid();
				child++;
				if (setintr) {
					setintr = 0;
D 2
					sigsys(SIGCHLD, SIG_DFL);
					sigsys(SIGINT, ignint ? SIG_IGN : vffree);
					sigsys(SIGQUIT, ignint ? SIG_IGN : SIG_DFL);
E 2
I 2
#ifdef notdef
D 3
					signal(SIGCHLD, SIG_DFL);
E 3
I 3
D 4
					sigsys(SIGCHLD, SIG_DFL);
E 4
I 4
D 5
					signal(SIGCHLD, SIG_DFL);
E 5
I 5
					(void) signal(SIGCHLD, SIG_DFL);
E 5
E 4
E 3
#endif
D 3
					signal(SIGINT,
E 3
I 3
D 4
					sigsys(SIGINT,
E 3
					    ignint ? SIG_IGN : vffree);
D 3
					signal(SIGQUIT,
E 3
I 3
					sigsys(SIGQUIT,
E 3
					    ignint ? SIG_IGN : SIG_DFL);
E 4
I 4
D 5
					signal(SIGINT, ignint ?
E 5
I 5
					(void) signal(SIGINT, ignint ?
E 5
						SIG_IGN : vffree);
D 5
					signal(SIGQUIT, ignint ?
E 5
I 5
					(void) signal(SIGQUIT, ignint ?
E 5
						SIG_IGN : SIG_DFL);
E 4
E 2
					if (wanttty >= 0) {
D 2
						sigsys(SIGTSTP, SIG_DFL);
						sigsys(SIGTTIN, SIG_DFL);
						sigsys(SIGTTOU, SIG_DFL);
E 2
I 2
D 3
						signal(SIGTSTP, SIG_DFL);
						signal(SIGTTIN, SIG_DFL);
						signal(SIGTTOU, SIG_DFL);
E 3
I 3
D 4
						sigsys(SIGTSTP, SIG_DFL);
						sigsys(SIGTTIN, SIG_DFL);
						sigsys(SIGTTOU, SIG_DFL);
E 4
I 4
D 5
						signal(SIGTSTP, SIG_DFL);
						signal(SIGTTIN, SIG_DFL);
						signal(SIGTTOU, SIG_DFL);
E 5
I 5
						(void) signal(SIGTSTP, SIG_DFL);
						(void) signal(SIGTTIN, SIG_DFL);
						(void) signal(SIGTTOU, SIG_DFL);
E 5
E 4
E 3
E 2
					}
D 2
					sigsys(SIGTERM, parterm);
E 2
I 2
D 3
					signal(SIGTERM, parterm);
E 3
I 3
D 4
					sigsys(SIGTERM, parterm);
E 4
I 4
D 5
					signal(SIGTERM, parterm);
E 5
I 5
					(void) signal(SIGTERM, parterm);
E 5
E 4
E 3
E 2
D 16
				} else if (tpgrp == -1 && (t->t_dflg&FINT)) {
E 16
I 16
				} else if (tpgrp == -1 &&
				    (t->t_dflg&F_NOINTERRUPT)) {
E 16
D 2
					sigsys(SIGINT, SIG_IGN);
					sigsys(SIGQUIT, SIG_IGN);
E 2
I 2
D 3
					signal(SIGINT, SIG_IGN);
					signal(SIGQUIT, SIG_IGN);
E 3
I 3
D 4
					sigsys(SIGINT, SIG_IGN);
					sigsys(SIGQUIT, SIG_IGN);
E 4
I 4
D 5
					signal(SIGINT, SIG_IGN);
					signal(SIGQUIT, SIG_IGN);
E 5
I 5
					(void) signal(SIGINT, SIG_IGN);
					(void) signal(SIGQUIT, SIG_IGN);
E 5
E 4
E 3
E 2
				}
I 12
				if (wanttty >= 0 && tpgrp >= 0)
					(void) setpgrp(0, pgrp);
E 12
				if (wanttty > 0)
D 5
					ioctl(FSHTTY, TIOCSPGRP, &pgrp);
E 5
I 5
					(void) ioctl(FSHTTY, TIOCSPGRP,
						(char *)&pgrp);
E 5
D 12
				if (wanttty >= 0 && tpgrp >= 0)
D 5
					setpgrp(0, pgrp);
E 5
I 5
					(void) setpgrp(0, pgrp);
E 12
E 5
				if (tpgrp > 0)
					tpgrp = 0;
D 16
				if (t->t_dflg & FNOHUP)
E 16
I 16
				if (t->t_dflg & F_NOHUP)
E 16
D 2
					sigsys(SIGHUP, SIG_IGN);
E 2
I 2
D 3
					signal(SIGHUP, SIG_IGN);
E 3
I 3
D 4
					sigsys(SIGHUP, SIG_IGN);
E 4
I 4
D 5
					signal(SIGHUP, SIG_IGN);
E 5
I 5
					(void) signal(SIGHUP, SIG_IGN);
E 5
E 4
E 3
E 2
D 16
				if (t->t_dflg & FNICE)
E 16
I 16
				if (t->t_dflg & F_NICE)
E 16
D 4
					nice(t->t_nice);
E 4
I 4
D 5
					setpriority(PRIO_PROCESS, 0, t->t_nice);
E 5
I 5
D 9
					(void) setpriority(PRIO_PROCESS,
						0, t->t_nice);
E 9
I 9
D 10
					(void) setpriority(PRIO_PROCESS, 0,
			    		    getpriority(PRIO_PROCESS, 0)
					    + t->t_nice);
E 10
I 10
					(void) setpriority(PRIO_PROCESS,
						0, t->t_nice);
E 18
I 18
	/*
	 * This mess is the necessary kludge to handle the prefix builtins:
	 * nice, nohup, time.  These commands can also be used by themselves,
	 * and this is not handled here. This will also work when loops are
	 * parsed.
	 */
	while (t->t_dtyp == NODE_COMMAND)
	    if (eq(t->t_dcom[0], STRnice))
		if (t->t_dcom[1])
		    if (strchr("+-", t->t_dcom[1][0]))
			if (t->t_dcom[2]) {
			    setname("nice");
			    t->t_nice =
				getn(t->t_dcom[1]);
			    lshift(t->t_dcom, 2);
			    t->t_dflg |= F_NICE;
E 18
E 10
E 9
E 5
E 4
			}
D 18

E 18
I 18
			else
			    break;
		    else {
			t->t_nice = 4;
			lshift(t->t_dcom, 1);
			t->t_dflg |= F_NICE;
E 18
D 4
		}
E 4
I 4
		    }
E 4
D 18
#endif
		if (pid != 0) {
			/*
			 * It would be better if we could wait for the
			 * whole job when we knew the last process
			 * had been started.  Pwait, in fact, does
			 * wait for the whole job anyway, but this test
			 * doesn't really express our intentions.
			 */
D 5
			if (didfds==0 && t->t_dflg&FPIN)
				close(pipein[0]), close(pipein[1]);
E 5
I 5
D 16
			if (didfds==0 && t->t_dflg&FPIN) {
E 16
I 16
			if (didfds==0 && t->t_dflg&F_PIPEIN) {
E 16
				(void) close(pipein[0]);
				(void) close(pipein[1]);
			}
E 5
D 12
			if ((t->t_dflg & (FPOU|FAND)) == 0)
				pwait();
E 12
I 12
D 16
			if ((t->t_dflg & FPOU) == 0) {
E 16
I 16
			if ((t->t_dflg & F_PIPEOUT) == 0) {
E 16
D 13
#ifdef REMOVE_THIS
				printf("(%d) last command - should unblock sigchld? (%d)\n", getpid(), nosigchld);
#endif
E 13
				if (nosigchld) {
#ifdef foobarbaz
					printf("DID\n");
#endif
					sigsetmask(osigmask);
					nosigchld = 0;
				}
D 16
				if ((t->t_dflg & FAND) == 0)
E 16
I 16
				if ((t->t_dflg & F_AMPERSAND) == 0)
E 16
					pwait();
			}
E 12
			break;
E 18
I 18
		else
		    break;
	    else if (eq(t->t_dcom[0], STRnohup))
		if (t->t_dcom[1]) {
		    t->t_dflg |= F_NOHUP;
		    lshift(t->t_dcom, 1);
E 18
		}
D 18
		doio(t, pipein, pipeout);
D 5
		if (t->t_dflg & FPOU)
			close(pipeout[0]), close(pipeout[1]);
E 5
I 5
D 16
		if (t->t_dflg & FPOU) {
E 16
I 16
		if (t->t_dflg & F_PIPEOUT) {
E 16
			(void) close(pipeout[0]);
			(void) close(pipeout[1]);
E 18
I 18
		else
		    break;
	    else if (eq(t->t_dcom[0], STRtime))
		if (t->t_dcom[1]) {
		    t->t_dflg |= F_TIME;
		    lshift(t->t_dcom, 1);
E 18
		}
I 18
		else
		    break;
	    else
		break;
E 18
E 5

I 18
D 26
	/* is t a command */
E 26
I 26
	/* is it a command */
E 26
	if (t->t_dtyp == NODE_COMMAND) {
	    /*
	     * Check if we have a builtin function and remember which one.
	     */
	    bifunc = isbfunc(t);
I 26
 	    if (noexec) {
		/*
		 * Continue for builtins that are part of the scripting language
		 */
		if (bifunc->bfunct != dobreak   && bifunc->bfunct != docontin &&
		    bifunc->bfunct != doelse    && bifunc->bfunct != doend    &&
		    bifunc->bfunct != doforeach && bifunc->bfunct != dogoto   &&
		    bifunc->bfunct != doif      && bifunc->bfunct != dorepeat &&
		    bifunc->bfunct != doswbrk   && bifunc->bfunct != doswitch &&
		    bifunc->bfunct != dowhile   && bifunc->bfunct != dozip)
		    break;
	    }
E 26
	}
	else {			/* not a command */
D 21
	    bifunc = (struct biltins *) 0;
E 21
I 21
	    bifunc = NULL;
I 26
	    if (noexec)
		break;
E 26
E 21
	}

	/*
	 * We fork only if we are timed, or are not the end of a parenthesized
	 * list and not a simple builtin function. Simple meaning one that is
	 * not pipedout, niced, nohupped, or &'d. It would be nice(?) to not
	 * fork in some of these cases.
	 */
	/*
	 * Prevent forking cd, pushd, popd, chdir cause this will cause the
	 * shell not to change dir!
	 */
	if (bifunc && (bifunc->bfunct == dochngd ||
		       bifunc->bfunct == dopushd ||
		       bifunc->bfunct == dopopd))
	    t->t_dflg &= ~(F_NICE);
D 29
	if (((t->t_dflg & F_TIME) || (t->t_dflg & F_NOFORK) == 0 &&
E 29
I 29
	if (((t->t_dflg & F_TIME) || ((t->t_dflg & F_NOFORK) == 0 &&
E 29
	     (!bifunc || t->t_dflg &
D 29
	      (F_PIPEOUT | F_AMPERSAND | F_NICE | F_NOHUP))) ||
E 29
I 29
	      (F_PIPEOUT | F_AMPERSAND | F_NICE | F_NOHUP)))) ||
E 29
	/*
	 * We have to fork for eval too.
	 */
D 25
	    (bifunc && (t->t_dflg & F_PIPEIN) != 0 &&
E 25
I 25
	    (bifunc && (t->t_dflg & (F_PIPEIN | F_PIPEOUT)) != 0 &&
E 25
	     bifunc->bfunct == doeval))
D 19
#ifdef VFORK
E 19
	    if (t->t_dtyp == NODE_PAREN ||
D 19
		t->t_dflg & (F_REPEAT | F_AMPERSAND) || bifunc)
#endif
	    {
E 19
I 19
		t->t_dflg & (F_REPEAT | F_AMPERSAND) || bifunc) {
E 19
		forked++;
E 18
		/*
D 18
		 * Perform a builtin function.
		 * If we are not forked, arrange for possible stopping
E 18
I 18
		 * We need to block SIGCHLD here, so that if the process does
		 * not die before we can set the process group
E 18
		 */
D 18
		if (bifunc) {
			func(t, bifunc);
			if (forked)
				exitstat();
			break;
E 18
I 18
		if (wanttty >= 0 && !nosigchld) {
D 31
		    csigmask = sigblock(sigmask(SIGCHLD));
E 31
I 31
		    sigemptyset(&sigset);
		    sigaddset(&sigset, SIGCHLD);
		    sigprocmask(SIG_BLOCK, &sigset, &csigset);
E 31
		    nosigchld = 1;
E 18
		}
D 16
		if (t->t_dtyp != TPAR) {
E 16
I 16
D 18
		if (t->t_dtyp != NODE_PAREN) {
E 16
			doexec(t);
			/*NOTREACHED*/
E 18
I 18

		pid = pfork(t, wanttty);
		if (pid == 0 && nosigchld) {
D 31
		    (void) sigsetmask(csigmask);
E 31
I 31
		    sigprocmask(SIG_SETMASK, &csigset, NULL);
E 31
		    nosigchld = 0;
E 18
		}
I 27
		else if (pid != 0 && (t->t_dflg & F_AMPERSAND))
		    backpid = pid;

E 27
I 18
	    }
D 19

#ifdef VFORK
E 19
	    else {
		int     ochild, osetintr, ohaderr, odidfds;
D 25
		int     oSHIN, oSHOUT, oSHDIAG, oOLDSTD, otpgrp;
E 25
I 25
		int     oSHIN, oSHOUT, oSHERR, oOLDSTD, otpgrp;
E 25
D 21
		sigmask_t omask;
E 21
I 21
D 31
		sigset_t omask;
E 31
I 31
		sigset_t osigset;
E 31
E 21

E 18
		/*
D 18
		 * For () commands must put new 0,1,2 in FSH* and recurse
E 18
I 18
		 * Prepare for the vfork by saving everything that the child
		 * corrupts before it exec's. Note that in some signal
		 * implementations which keep the signal info in user space
		 * (e.g. Sun's) it will also be necessary to save and restore
D 31
		 * the current sigvec's for the signals the child touches
E 31
I 31
		 * the current sigaction's for the signals the child touches
E 31
		 * before it exec's.
E 18
		 */
D 18
		OLDSTD = dcopy(0, FOLDSTD);
		SHOUT = dcopy(1, FSHOUT);
		SHDIAG = dcopy(2, FSHDIAG);
D 5
		close(SHIN), SHIN = -1;
		didcch = 0, didfds = 0;
E 5
I 5
		(void) close(SHIN);
		SHIN = -1;
		didfds = 0;
E 5
		wanttty = -1;
D 16
		t->t_dspr->t_dflg |= t->t_dflg & FINT;
E 16
I 16
		t->t_dspr->t_dflg |= t->t_dflg & F_NOINTERRUPT;
E 16
		execute(t->t_dspr, wanttty);
		exitstat();
E 18
I 18
		if (wanttty >= 0 && !nosigchld && !noexec) {
D 31
		    csigmask = sigblock(sigmask(SIGCHLD));
E 31
I 31
		    sigemptyset(&sigset);
		    sigaddset(&sigset, SIGCHLD);
		    sigprocmask(SIG_BLOCK, &sigset, &csigset);
E 31
		    nosigchld = 1;
		}
D 31
		omask = sigblock(sigmask(SIGCHLD) | sigmask(SIGINT));
E 31
I 31
		sigemptyset(&sigset);
		sigaddset(&sigset, SIGCHLD);
		sigaddset(&sigset, SIGINT);
		sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 31
		ochild = child;
		osetintr = setintr;
		ohaderr = haderr;
		odidfds = didfds;
		oSHIN = SHIN;
		oSHOUT = SHOUT;
D 25
		oSHDIAG = SHDIAG;
E 25
I 25
		oSHERR = SHERR;
E 25
		oOLDSTD = OLDSTD;
		otpgrp = tpgrp;
D 31
		ocsigmask = csigmask;
E 31
I 31
		ocsigset = csigset;
E 31
		onosigchld = nosigchld;
		Vsav = Vdp = 0;
		Vexpath = 0;
		Vt = 0;
		pid = vfork();
E 18

D 16
	case TFIL:
		t->t_dcar->t_dflg |= FPOU |
		    (t->t_dflg & (FPIN|FAND|FDIAG|FINT));
E 16
I 16
D 18
	case NODE_PIPE:
		t->t_dcar->t_dflg |= F_PIPEOUT |
		    (t->t_dflg & (F_PIPEIN|F_AMPERSAND|F_STDERR|F_NOINTERRUPT));
E 16
		execute(t->t_dcar, wanttty, pipein, pv);
D 16
		t->t_dcdr->t_dflg |= FPIN |
		    (t->t_dflg & (FPOU|FAND|FPAR|FINT));
E 16
I 16
		t->t_dcdr->t_dflg |= F_PIPEIN |
		    (t->t_dflg &
		    (F_PIPEOUT|F_AMPERSAND|F_NOFORK|F_NOINTERRUPT));
E 16
		if (wanttty > 0)
			wanttty = 0;		/* got tty already */
		execute(t->t_dcdr, wanttty, pv, pipeout);
		break;
E 18
I 18
		if (pid < 0) {
D 31
		    (void) sigsetmask(omask);
E 31
I 31
		    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 31
		    stderror(ERR_NOPROC);
		}
		forked++;
		if (pid) {	/* parent */
		    child = ochild;
		    setintr = osetintr;
		    haderr = ohaderr;
		    didfds = odidfds;
		    SHIN = oSHIN;
		    SHOUT = oSHOUT;
D 25
		    SHDIAG = oSHDIAG;
E 25
I 25
		    SHERR = oSHERR;
E 25
		    OLDSTD = oOLDSTD;
		    tpgrp = otpgrp;
D 31
		    csigmask = ocsigmask;
E 31
I 31
		    csigset = ocsigset;
E 31
		    nosigchld = onosigchld;
E 18

D 16
	case TLST:
E 16
I 16
D 18
	case NODE_LIST:
E 16
		if (t->t_dcar) {
D 16
			t->t_dcar->t_dflg |= t->t_dflg & FINT;
E 16
I 16
			t->t_dcar->t_dflg |= t->t_dflg & F_NOINTERRUPT;
E 16
			execute(t->t_dcar, wanttty);
			/*
			 * In strange case of A&B make a new job after A
			 */
D 16
			if (t->t_dcar->t_dflg&FAND && t->t_dcdr &&
			    (t->t_dcdr->t_dflg&FAND) == 0)
E 16
I 16
			if (t->t_dcar->t_dflg&F_AMPERSAND && t->t_dcdr &&
			    (t->t_dcdr->t_dflg&F_AMPERSAND) == 0)
E 16
				pendjob();
E 18
I 18
		    xfree((ptr_t) Vsav);
		    Vsav = 0;
		    xfree((ptr_t) Vdp);
		    Vdp = 0;
		    xfree((ptr_t) Vexpath);
		    Vexpath = 0;
		    blkfree((Char **) Vt);
		    Vt = 0;
		    /* this is from pfork() */
		    palloc(pid, t);
D 31
		    (void) sigsetmask(omask);
E 31
I 31
		    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 31
E 18
		}
D 18
		if (t->t_dcdr) {
D 16
			t->t_dcdr->t_dflg |= t->t_dflg & (FPAR|FINT);
E 16
I 16
			t->t_dcdr->t_dflg |=
			    t->t_dflg & (F_NOFORK|F_NOINTERRUPT);
E 16
			execute(t->t_dcdr, wanttty);
E 18
I 18
		else {		/* child */
		    /* this is from pfork() */
		    int     pgrp;
		    bool    ignint = 0;

		    if (nosigchld) {
D 31
			(void) sigsetmask(csigmask);
E 31
I 31
		        sigprocmask(SIG_SETMASK, &csigset, NULL);
E 31
			nosigchld = 0;
		    }

		    if (setintr)
			ignint =
			    (tpgrp == -1 &&
			     (t->t_dflg & F_NOINTERRUPT))
D 29
			    || gointr && eq(gointr, STRminus);
E 29
I 29
			    || (gointr && eq(gointr, STRminus));
E 29
		    pgrp = pcurrjob ? pcurrjob->p_jobid : getpid();
		    child++;
		    if (setintr) {
			setintr = 0;
			if (ignint) {
			    (void) signal(SIGINT, SIG_IGN);
			    (void) signal(SIGQUIT, SIG_IGN);
			}
			else {
			    (void) signal(SIGINT, vffree);
			    (void) signal(SIGQUIT, SIG_DFL);
			}

			if (wanttty >= 0) {
			    (void) signal(SIGTSTP, SIG_DFL);
			    (void) signal(SIGTTIN, SIG_DFL);
			    (void) signal(SIGTTOU, SIG_DFL);
			}

			(void) signal(SIGTERM, parterm);
		    }
		    else if (tpgrp == -1 &&
			     (t->t_dflg & F_NOINTERRUPT)) {
			(void) signal(SIGINT, SIG_IGN);
			(void) signal(SIGQUIT, SIG_IGN);
		    }

		    pgetty(wanttty, pgrp);
		    if (t->t_dflg & F_NOHUP)
			(void) signal(SIGHUP, SIG_IGN);
		    if (t->t_dflg & F_NICE)
			(void) setpriority(PRIO_PROCESS, 0, t->t_nice);
E 18
		}
D 18
		break;
E 18

D 16
	case TOR:
	case TAND:
E 16
I 16
D 18
	case NODE_OR:
	case NODE_AND:
E 16
		if (t->t_dcar) {
D 16
			t->t_dcar->t_dflg |= t->t_dflg & FINT;
E 16
I 16
			t->t_dcar->t_dflg |= t->t_dflg & F_NOINTERRUPT;
E 16
			execute(t->t_dcar, wanttty);
D 16
			if ((getn(value("status")) == 0) != (t->t_dtyp == TAND))
E 16
I 16
			if ((getn(value("status")) == 0) !=
			    (t->t_dtyp == NODE_AND))
E 16
				return;
E 18
I 18
	    }
D 19
#endif				/* VFORK */
E 19
	if (pid != 0) {
	    /*
	     * It would be better if we could wait for the whole job when we
	     * knew the last process had been started.  Pwait, in fact, does
	     * wait for the whole job anyway, but this test doesn't really
	     * express our intentions.
	     */
	    if (didfds == 0 && t->t_dflg & F_PIPEIN) {
		(void) close(pipein[0]);
		(void) close(pipein[1]);
	    }
	    if ((t->t_dflg & F_PIPEOUT) == 0) {
		if (nosigchld) {
D 31
		    (void) sigsetmask(csigmask);
E 31
I 31
		    sigprocmask(SIG_SETMASK, &csigset, NULL);
E 31
		    nosigchld = 0;
E 18
		}
D 18
		if (t->t_dcdr) {
D 16
			t->t_dcdr->t_dflg |= t->t_dflg & (FPAR|FINT);
E 16
I 16
			t->t_dcdr->t_dflg |=
			    t->t_dflg & (F_NOFORK|F_NOINTERRUPT);
E 16
			execute(t->t_dcdr, wanttty);
		}
		break;
E 18
I 18
		if ((t->t_dflg & F_AMPERSAND) == 0)
		    pwait();
	    }
	    break;
E 18
	}
I 18
	doio(t, pipein, pipeout);
	if (t->t_dflg & F_PIPEOUT) {
	    (void) close(pipeout[0]);
	    (void) close(pipeout[1]);
	}
E 18
	/*
D 16
	 * Fall through for all breaks from switch
E 16
I 16
D 18
	 * Fall through for all breaks from switch.
E 16
	 *
D 16
	 * If there will be no more executions of this
	 * command, flush all file descriptors.
	 * Places that turn on the FREDO bit are responsible
	 * for doing donefds after the last re-execution
E 16
I 16
	 * If there will be no more executions of this command, flush all
	 * file descriptors.  Places that turn on the F_REPEAT bit are
	 * responsible for doing donefds after the last re-execution
E 18
I 18
	 * Perform a builtin function. If we are not forked, arrange for
	 * possible stopping
E 18
E 16
	 */
D 16
	if (didfds && !(t->t_dflg & FREDO))
E 16
I 16
D 18
	if (didfds && !(t->t_dflg & F_REPEAT))
E 16
		donefds();
E 18
I 18
	if (bifunc) {
	    func(t, bifunc);
	    if (forked)
		exitstat();
	    break;
	}
	if (t->t_dtyp != NODE_PAREN) {
D 25
	    doexec(t);
E 25
I 25
	    doexec(NULL, t);
E 25
	    /* NOTREACHED */
	}
	/*
	 * For () commands must put new 0,1,2 in FSH* and recurse
	 */
	OLDSTD = dcopy(0, FOLDSTD);
	SHOUT = dcopy(1, FSHOUT);
D 25
	SHDIAG = dcopy(2, FSHDIAG);
E 25
I 25
	SHERR = dcopy(2, FSHERR);
E 25
	(void) close(SHIN);
	SHIN = -1;
	didfds = 0;
	wanttty = -1;
	t->t_dspr->t_dflg |= t->t_dflg & F_NOINTERRUPT;
	execute(t->t_dspr, wanttty, NULL, NULL);
	exitstat();

    case NODE_PIPE:
	t->t_dcar->t_dflg |= F_PIPEOUT |
	    (t->t_dflg & (F_PIPEIN | F_AMPERSAND | F_STDERR | F_NOINTERRUPT));
	execute(t->t_dcar, wanttty, pipein, pv);
	t->t_dcdr->t_dflg |= F_PIPEIN | (t->t_dflg &
			(F_PIPEOUT | F_AMPERSAND | F_NOFORK | F_NOINTERRUPT));
	if (wanttty > 0)
	    wanttty = 0;	/* got tty already */
	execute(t->t_dcdr, wanttty, pv, pipeout);
	break;

    case NODE_LIST:
	if (t->t_dcar) {
	    t->t_dcar->t_dflg |= t->t_dflg & F_NOINTERRUPT;
	    execute(t->t_dcar, wanttty, NULL, NULL);
	    /*
	     * In strange case of A&B make a new job after A
	     */
	    if (t->t_dcar->t_dflg & F_AMPERSAND && t->t_dcdr &&
		(t->t_dcdr->t_dflg & F_AMPERSAND) == 0)
		pendjob();
	}
	if (t->t_dcdr) {
	    t->t_dcdr->t_dflg |= t->t_dflg &
		(F_NOFORK | F_NOINTERRUPT);
	    execute(t->t_dcdr, wanttty, NULL, NULL);
	}
	break;

    case NODE_OR:
    case NODE_AND:
	if (t->t_dcar) {
	    t->t_dcar->t_dflg |= t->t_dflg & F_NOINTERRUPT;
	    execute(t->t_dcar, wanttty, NULL, NULL);
	    if ((getn(value(STRstatus)) == 0) !=
		(t->t_dtyp == NODE_AND))
		return;
	}
	if (t->t_dcdr) {
	    t->t_dcdr->t_dflg |= t->t_dflg &
		(F_NOFORK | F_NOINTERRUPT);
	    execute(t->t_dcdr, wanttty, NULL, NULL);
	}
	break;
    }
    /*
     * Fall through for all breaks from switch
     * 
     * If there will be no more executions of this command, flush all file
     * descriptors. Places that turn on the F_REPEAT bit are responsible for
     * doing donefds after the last re-execution
     */
    if (didfds && !(t->t_dflg & F_REPEAT))
	donefds();
E 18
}

D 19
#ifdef VFORK
E 19
I 18
static void
E 18
D 20
vffree()
E 20
I 20
vffree(i)
int i;
E 20
{
D 18
	register char **v;
E 18
I 18
    register Char **v;
E 18

D 18
	if (v = gargv)
D 5
		gargv = 0, xfree(gargv);
E 5
I 5
		gargv = 0, xfree((char *)v);
E 5
	if (v = pargv)
D 5
		pargv = 0, xfree(pargv);
E 5
I 5
		pargv = 0, xfree((char *)v);
E 5
	_exit(1);
E 18
I 18
D 29
    if (v = gargv) {
E 29
I 29
    if ((v = gargv) != NULL) {
E 29
	gargv = 0;
	xfree((ptr_t) v);
    }
D 29
    if (v = pargv) {
E 29
I 29
    if ((v = pargv) != NULL) {
E 29
	pargv = 0;
	xfree((ptr_t) v);
    }
D 20
    _exit(1);
E 20
I 20
    _exit(i);
E 20
E 18
}
I 18
D 19

E 18
#endif
E 19

/*
I 27
 * Expand and glob the words after an i/o redirection.
 * If more than one word is generated, then update the command vector.
 *
 * This is done differently in all the shells:
 * 1. in the bourne shell and ksh globbing is not performed
 * 2. Bash/csh say ambiguous
 * 3. zsh does i/o to/from all the files
 * 4. itcsh concatenates the words.
 *
 * I don't know what is best to do. I think that Ambiguous is better
 * than restructuring the command vector, because the user can get
 * unexpected results. In any case, the command vector restructuring 
 * code is present and the user can choose it by setting noambiguous
 */
static Char *
splicepipe(t, cp)
    register struct command *t;
    Char *cp;	/* word after < or > */
{
    Char *blk[2];

    if (adrof(STRnoambiguous)) {
	Char **pv;

	blk[0] = Dfix1(cp); /* expand $ */
	blk[1] = NULL;

	gflag = 0, tglob(blk);
	if (gflag) {
	    pv = globall(blk);
	    if (pv == NULL) {
D 28
		setname(short2str(blk[0]));
E 28
I 28
		setname(vis_str(blk[0]));
E 28
		xfree((ptr_t) blk[0]);
		stderror(ERR_NAME | ERR_NOMATCH);
	    }
	    gargv = NULL;
	    if (pv[1] != NULL) { /* we need to fix the command vector */
		Char **av = blkspl(t->t_dcom, &pv[1]);
		xfree((ptr_t) t->t_dcom);
		t->t_dcom = av;
	    }
	    xfree((ptr_t) blk[0]);
	    blk[0] = pv[0];
	    xfree((ptr_t) pv);
	}
    }
    else {
	blk[0] = globone(blk[1] = Dfix1(cp), G_ERROR);
	xfree((ptr_t) blk[1]);
    }
    return(blk[0]);
}

/*
E 27
 * Perform io redirection.
 * We may or maynot be forked here.
 */
I 18
static void
E 18
doio(t, pipein, pipeout)
D 18
	register struct command *t;
	int *pipein, *pipeout;
E 18
I 18
    register struct command *t;
    int    *pipein, *pipeout;
E 18
{
D 18
	register char *cp;
	register int flags = t->t_dflg;
E 18
I 18
    register int fd;
D 24
    register Char *cp;
E 24
I 24
D 27
    register Char *cp, *dp;
E 27
I 27
    register Char *cp;
E 27
E 24
    register int flags = t->t_dflg;
E 18

D 16
	if (didfds || (flags & FREDO))
E 16
I 16
D 18
	if (didfds || (flags & F_REPEAT))
E 16
		return;
D 16
	if ((flags & FHERE) == 0) {	/* FHERE already done */
E 16
I 16
	if ((flags & F_READ) == 0) {	/* F_READ already done */
E 16
D 5
		close(0);
E 5
I 5
		(void) close(0);
E 5
		if (cp = t->t_dlef) {
			cp = globone(Dfix1(cp));
			xfree(cp);
			if (open(cp, 0) < 0)
				Perror(cp);
D 5
		} else if (flags & FPIN)
			dup(pipein[0]), close(pipein[0]), close(pipein[1]);
		else if ((flags & FINT) && tpgrp == -1)
			close(0), open("/dev/null", 0);
		else
			dup(OLDSTD);
E 5
I 5
D 16
		} else if (flags & FPIN) {
E 16
I 16
		} else if (flags & F_PIPEIN) {
E 16
			(void) dup(pipein[0]);
			(void) close(pipein[0]);
			(void) close(pipein[1]);
D 16
		} else if ((flags & FINT) && tpgrp == -1) {
E 16
I 16
		} else if ((flags & F_NOINTERRUPT) && tpgrp == -1) {
E 16
			(void) close(0);
D 12
			(void) open("/dev/null", 0);
E 12
I 12
			(void) open(_PATH_DEVNULL, 0);
E 12
		} else
D 6
			(void) ioctl(dup(OLDSTD), FIONCLEX, (char *)0);
E 6
I 6
			(void) dup(OLDSTD);
E 18
I 18
    if (didfds || (flags & F_REPEAT))
	return;
    if ((flags & F_READ) == 0) {/* F_READ already done */
D 27
	if (cp = t->t_dlef) {
E 27
I 27
	if (t->t_dlef) {
E 27
D 23
	    char    tmp[MAXPATHLEN];
E 23
I 23
	    char    tmp[MAXPATHLEN+1];
E 23

	    /*
	     * so < /dev/std{in,out,err} work
	     */
	    (void) dcopy(SHIN, 0);
	    (void) dcopy(SHOUT, 1);
D 25
	    (void) dcopy(SHDIAG, 2);
E 25
I 25
	    (void) dcopy(SHERR, 2);
E 25
D 24
	    cp = globone(Dfix1(cp), G_IGNORE);
E 24
I 24
D 27
	    cp = globone(dp = Dfix1(cp), G_IGNORE);
E 27
I 27
	    cp = splicepipe(t, t->t_dlef);
E 27
E 24
	    (void) strncpy(tmp, short2str(cp), MAXPATHLEN);
D 23
	    tmp[MAXPATHLEN - 1] = '\0';
E 23
I 23
	    tmp[MAXPATHLEN] = '\0';
E 23
	    xfree((ptr_t) cp);
I 24
D 27
	    xfree((ptr_t) dp);
E 27
E 24
	    if ((fd = open(tmp, O_RDONLY)) < 0)
		stderror(ERR_SYSTEM, tmp, strerror(errno));
	    (void) dmove(fd, 0);
E 18
E 6
E 5
	}
I 18
	else if (flags & F_PIPEIN) {
	    (void) close(0);
	    (void) dup(pipein[0]);
	    (void) close(pipein[0]);
	    (void) close(pipein[1]);
	}
	else if ((flags & F_NOINTERRUPT) && tpgrp == -1) {
	    (void) close(0);
	    (void) open(_PATH_DEVNULL, O_RDONLY);
	}
	else {
	    (void) close(0);
	    (void) dup(OLDSTD);
D 21
	    (void) ioctl(0, FIONCLEX, (char *) 0);
E 21
I 21
	    (void) ioctl(0, FIONCLEX, NULL);
E 21
	}
    }
D 27
    if (cp = t->t_drit) {
E 27
I 27
    if (t->t_drit) {
E 27
D 23
	Char    tmp[MAXPATHLEN];
E 23
I 23
	char    tmp[MAXPATHLEN+1];
E 23

D 24
	cp = globone(Dfix1(cp), G_IGNORE);
E 24
I 24
D 27
	cp = globone(dp = Dfix1(cp), G_IGNORE);
E 27
I 27
	cp = splicepipe(t, t->t_drit);
E 27
E 24
D 23
	(void) Strncpy(tmp, cp, MAXPATHLEN);
	tmp[MAXPATHLEN - 1] = '\0';
E 23
I 23
	(void) strncpy(tmp, short2str(cp), MAXPATHLEN);
	tmp[MAXPATHLEN] = '\0';
E 23
	xfree((ptr_t) cp);
I 24
D 27
	xfree((ptr_t) dp);
E 27
E 24
	/*
	 * so > /dev/std{out,err} work
	 */
	(void) dcopy(SHOUT, 1);
D 25
	(void) dcopy(SHDIAG, 2);
E 25
I 25
	(void) dcopy(SHERR, 2);
E 25
	if ((flags & F_APPEND) &&
#ifdef O_APPEND
D 23
	    (fd = open(short2str(tmp), O_WRONLY | O_APPEND)) >= 0);
E 23
I 23
	    (fd = open(tmp, O_WRONLY | O_APPEND)) >= 0);
E 23
#else
D 23
	    (fd = open(short2str(tmp), O_WRONLY)) >= 0)
E 23
I 23
	    (fd = open(tmp, O_WRONLY)) >= 0)
E 23
	    (void) lseek(1, (off_t) 0, L_XTND);
#endif
	else {
	    if (!(flags & F_OVERWRITE) && adrof(STRnoclobber)) {
		if (flags & F_APPEND)
D 23
		    stderror(ERR_SYSTEM, short2str(tmp), strerror(errno));
E 23
I 23
		    stderror(ERR_SYSTEM, tmp, strerror(errno));
E 23
		chkclob(tmp);
	    }
D 23
	    if ((fd = creat(short2str(tmp), 0666)) < 0)
		stderror(ERR_SYSTEM, short2str(tmp), strerror(errno));
E 23
I 23
D 32
	    if ((fd = creat(tmp, 0666)) < 0)
E 32
I 32
	    if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
E 32
		stderror(ERR_SYSTEM, tmp, strerror(errno));
E 23
	}
	(void) dmove(fd, 1);
    }
    else if (flags & F_PIPEOUT) {
E 18
D 5
	close(1);
E 5
I 5
	(void) close(1);
E 5
D 18
	if (cp = t->t_drit) {
		cp = globone(Dfix1(cp));
		xfree(cp);
D 14
		if ((flags & FCAT) && open(cp, 1) >= 0)
D 5
			lseek(1, 0l, 2);
E 5
I 5
			(void) lseek(1, (off_t)0, 2);
E 5
		else {
E 14
I 14
D 16
		if (!(flags & FCAT) || open(cp, O_WRONLY|O_APPEND, 0) < 0) {
E 14
			if (!(flags & FANY) && adrof("noclobber")) {
				if (flags & FCAT)
E 16
I 16
		if (!(flags & F_APPEND) || open(cp, O_WRONLY|O_APPEND, 0) < 0) {
			if (!(flags & F_OVERWRITE) && adrof("noclobber")) {
				if (flags & F_APPEND)
E 16
					Perror(cp);
				chkclob(cp);
			}
			if (creat(cp, 0666) < 0)
				Perror(cp);
		}
D 16
	} else if (flags & FPOU)
E 16
I 16
	} else if (flags & F_PIPEOUT)
E 16
D 5
		dup(pipeout[1]);
E 5
I 5
		(void) dup(pipeout[1]);
E 5
	else
D 5
		dup(SHOUT);
E 5
I 5
D 6
		(void) ioctl(dup(SHOUT), FIONCLEX, (char *)0);
E 6
I 6
		(void) dup(SHOUT);
E 18
I 18
	(void) dup(pipeout[1]);
    }
    else {
	(void) close(1);
	(void) dup(SHOUT);
D 21
	(void) ioctl(1, FIONCLEX, (char *) 0);
E 21
I 21
	(void) ioctl(1, FIONCLEX, NULL);
E 21
    }
E 18
E 6
E 5

D 5
	close(2);
	dup((flags & FDIAG) ? 1 : SHDIAG);
E 5
I 5
D 18
	(void) close(2);
D 16
	if (flags & FDIAG)
E 16
I 16
	if (flags & F_STDERR)
E 16
		(void) dup(1);
	else
D 6
		(void) ioctl(dup(SHDIAG), FIONCLEX, (char *)0);
E 6
I 6
		(void) dup(SHDIAG);
E 6
E 5
	didfds = 1;
E 18
I 18
    (void) close(2);
    if (flags & F_STDERR) {
	(void) dup(1);
    }
    else {
D 25
	(void) dup(SHDIAG);
E 25
I 25
	(void) dup(SHERR);
E 25
D 21
	(void) ioctl(2, FIONCLEX, (char *) 0);
E 21
I 21
	(void) ioctl(2, FIONCLEX, NULL);
E 21
    }
    didfds = 1;
E 18
}

I 18
void
E 18
mypipe(pv)
D 18
	register int *pv;
E 18
I 18
    register int *pv;
E 18
{

D 18
	if (pipe(pv) < 0)
		goto oops;
	pv[0] = dmove(pv[0], -1);
	pv[1] = dmove(pv[1], -1);
	if (pv[0] >= 0 && pv[1] >= 0)
		return;
E 18
I 18
    if (pipe(pv) < 0)
	goto oops;
    pv[0] = dmove(pv[0], -1);
    pv[1] = dmove(pv[1], -1);
    if (pv[0] >= 0 && pv[1] >= 0)
	return;
E 18
oops:
D 18
	error("Can't make pipe");
E 18
I 18
    stderror(ERR_PIPE);
E 18
}

I 18
static void
E 18
chkclob(cp)
D 18
	register char *cp;
E 18
I 18
D 23
    register Char *cp;
E 23
I 23
    register char *cp;
E 23
E 18
{
D 18
	struct stat stb;
E 18
I 18
    struct stat stb;
D 23
    char   *ptr;
E 23
E 18

D 18
	if (stat(cp, &stb) < 0)
		return;
	if ((stb.st_mode & S_IFMT) == S_IFCHR)
		return;
	error("%s: File exists", cp);
E 18
I 18
D 23
    if (stat(ptr = short2str(cp), &stb) < 0)
E 23
I 23
    if (stat(cp, &stb) < 0)
E 23
	return;
D 27
    if ((stb.st_mode & S_IFMT) == S_IFCHR)
E 27
I 27
    if (S_ISCHR(stb.st_mode))
E 27
	return;
D 23
    stderror(ERR_EXISTS, ptr);
E 23
I 23
    stderror(ERR_EXISTS, cp);
E 23
E 18
}
E 1
