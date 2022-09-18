h40373
s 00055/00032/01298
d D 8.2 95/03/22 14:12:31 christos 48 47
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/01328
d D 8.1 93/05/31 16:42:44 bostic 47 46
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/01328
d D 5.29 93/05/22 19:06:45 christos 46 45
c Fixed gcc -Wall warnings
e
s 00006/00006/01323
d D 5.28 91/11/06 16:09:50 christos 45 44
c Added support for displaying non-printable characters
e
s 00009/00008/01320
d D 5.27 91/10/28 21:28:07 leres 44 43
c Fix gcc "bodyless for/while" warnings.
e
s 00001/00001/01327
d D 5.26 91/09/01 22:41:18 christos 43 42
c fixed signal reporting
e
s 00018/00020/01310
d D 5.25 91/08/04 17:36:32 christos 42 41
c Signal names from libc; /bin/kill compatible builtin
e
s 00055/00018/01275
d D 5.24 91/07/20 21:35:36 christos 41 40
c Fixed newline printing in pprint()
e
s 00090/00066/01203
d D 5.23 91/07/19 17:31:18 christos 40 39
c stdio based version; brace glob fix; builtin prototypes
e
s 00004/00003/01265
d D 5.22 91/06/14 14:34:24 christos 39 38
c Small Exit formatting error. Print background job exit status.
e
s 00015/00015/01253
d D 5.21 91/06/09 18:39:54 christos 38 37
c replaced PNULL def with NULL
e
s 00006/00000/01262
d D 5.20 91/06/08 17:09:00 christos 37 36
c More prototype fixes, Removed TERMIOS define
e
s 00017/00012/01245
d D 5.19 91/06/08 12:20:34 bostic 36 35
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00011/00010/01246
d D 5.18 91/06/07 20:57:38 christos 35 34
c static function prototypes
e
s 00007/00004/01249
d D 5.17 91/06/07 11:13:39 bostic 34 33
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00948/00797/00305
d D 5.16 91/06/04 13:31:52 bostic 33 32
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/01095
d D 5.15 91/04/04 18:17:54 bostic 32 31
c new copyright; att/bsd/shared
e
s 00026/00026/01075
d D 5.14 91/04/01 17:37:18 bostic 31 30
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00003/00001/01098
d D 5.13 91/02/25 08:11:56 bostic 30 29
c ANSI fixes
e
s 00005/00007/01094
d D 5.12 90/06/30 16:11:24 marc 29 28
c strerror(); set proc in pgrp before setting terminal
e
s 00002/00003/01099
d D 5.11 89/11/20 17:42:33 marc 28 27
c POSIX Job Control
e
s 00002/00002/01100
d D 5.10 88/05/19 15:39:01 bostic 27 26
c install C version of _doprnt
e
s 00002/00001/01100
d D 5.9 88/01/20 11:55:28 bostic 26 25
c Bug involving csh and the "source" command; 4.3BSD/bin/115
e
s 00003/00003/01098
d D 5.8 87/09/16 14:47:47 bostic 25 24
c use "Suspended", not "Stopped"; bug report 4.3BSD/bin/56
e
s 00001/00001/01100
d D 5.7 87/09/16 11:47:30 bostic 24 23
c non-interactive csh/children fix; bug report 4.3BSD/bin/42
e
s 00014/00009/01087
d D 5.6 87/06/25 09:15:20 bostic 23 22
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00006/00006/01090
d D 5.5 86/05/13 01:12:24 lepreau 22 21
c nice is absolute after all; allow killing with 0 as a signum and negative pids;
c fix botched code that suppresses SIGPIPE and SIGINT termiantion msgs (from
c glenn@sun).  Not sure he fixed it rgiht but it's a lot better than before.
e
s 00002/00001/01094
d D 5.4 86/01/12 02:34:05 lepreau 21 20
c nice is relative, not absolute. (Kirk "authorized" it.)
e
s 00001/00001/01094
d D 5.3 85/07/31 19:48:26 mckusick 20 19
c block SIGINTS while waiting for a kid (from ks@purdue)
e
s 00003/00003/01092
d D 5.2 85/06/06 13:08:48 edward 19 18
c cleaning up after bozos
e
s 00008/00002/01087
d D 5.1 85/06/04 11:06:58 dist 18 17
c Add copyright
e
s 00005/00001/01084
d D 4.17 85/03/19 18:40:03 mckusick 17 16
c boiler plate around killpg()
e
s 00016/00006/01069
d D 4.16 85/02/01 12:18:27 edward 16 15
c padds fixed to take care of && and ||
e
s 00043/00053/01032
d D 4.15 84/12/13 14:39:22 edward 15 14
c performance
e
s 00000/00005/01085
d D 4.14 84/11/21 11:25:29 ralph 14 13
c don't need to ignore SIGINT due to process groups.
e
s 00035/00045/01055
d D 4.13 84/08/31 09:31:02 ralph 13 12
c use new signal calls instead of compatibility routines.
e
s 00001/00001/01099
d D 4.12 83/07/01 23:28:25 wnj 12 11
c include fixes
e
s 00011/00006/01089
d D 4.11 83/07/01 03:57:46 sam 11 10
c fixes from wnj to allow job names to be globbed
e
s 00029/00040/01066
d D 4.10 83/06/11 16:49:45 sam 10 9
c different approach, try signal compatibility package
e
s 00040/00029/01066
d D 4.9 83/06/10 23:59:30 sam 9 8
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00011/00008/01084
d D 4.8 83/02/03 09:12:55 sam 8 7
c use high precision time calls
e
s 00012/00037/01080
d D 4.7 82/12/30 17:35:28 sam 7 6
c finally works (updated for 4.1c and merged with sun)
e
s 00004/00001/01113
d D 4.6 81/05/03 19:52:00 root 6 5
c fix to way time is printed
e
s 00001/00001/01113
d D 4.5 81/04/05 22:15:28 root 5 4
c fixed up!
e
s 00007/00005/01107
d D 4.4 81/04/05 22:14:51 root 4 3
c really fixed
e
s 00009/00008/01103
d D 4.3 81/03/11 18:52:01 wnj 3 2
c minor bug fixes
e
s 00018/00012/01093
d D 4.2 81/02/07 12:16:15 wnj 2 1
c fixed job control bug, improved choice of + and - jobs
e
s 01105/00000/00000
d D 4.1 80/10/09 12:41:33 bill 1 0
c date and time created 80/10/09 12:41:33 by bill
e
u
U
t
T
I 18
D 32
/*
 * Copyright (c) 1980 Regents of the University of California.
D 19
 * All rights reserved.  The Berkeley software License Agreement
E 19
I 19
 * All rights reserved.  The Berkeley Software License Agreement
E 19
 * specifies the terms and conditions for redistribution.
E 32
I 32
/*-
D 47
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 47
I 47
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 47
 *
 * %sccs.include.redist.c%
E 32
 */

E 18
I 1
D 4
static	char *sccsid = "%Z%%M% %I% %G%";
E 4
I 4
D 5
static	char *sccsid = "@(#)sh.proc.c 4.4 3/31/81";
E 5
I 5
D 15
static	char *sccsid = "%W% (Berkeley) %E%";
E 15
I 15
#ifndef lint
D 18
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 18
I 18
D 19
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 19
I 19
D 32
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 32
I 32
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 32
E 19
E 18
E 15
E 5
E 4

I 36
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
I 37
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 37
E 36
D 34
#include "sh.h"
#include "sh.dir.h"
#include "sh.proc.h"
E 34
I 34
#include "csh.h"
#include "dir.h"
#include "proc.h"
#include "extern.h"
E 34
I 29
D 33
#include <string.h>
E 33
E 29
D 12
#include <wait.h>
E 12
I 12
D 36
#include <sys/wait.h>
E 36
E 12
D 33
#include <sys/ioctl.h>
E 33

D 33
/*
 * C Shell - functions that manage processes, handling hanging, termination
 */

E 33
#define BIGINDEX	9	/* largest desirable job index */

I 33
static struct rusage zru;

D 35
static void pflushall();
static void pflush();
static void pclrcurr();
static void padd();
static int pprint();
static void ptprint();
static void pads();
static void pkill();
static struct process *pgetcurr();
static void okpcntl();
E 35
I 35
static void	 pflushall __P((void));
static void	 pflush __P((struct process *));
static void	 pclrcurr __P((struct process *));
static void	 padd __P((struct command *));
static int	 pprint __P((struct process *, int));
static void	 ptprint __P((struct process *));
static void	 pads __P((Char *));
static void	 pkill __P((Char **v, int));
D 44
static struct	process 
E 44
I 44
static struct	process
E 44
		*pgetcurr __P((struct process *));
static void	 okpcntl __P((void));
E 35

E 33
/*
 * pchild - called at interrupt level by the SIGCHLD signal
 *	indicating that at least one child has terminated or stopped
 *	thus at least one wait system call will definitely return a
 *	childs status.  Top level routines (like pwait) must be sure
 *	to mask interrupts when playing with the proclist data structures!
 */
I 34
/* ARGUSED */
E 34
I 30
void
E 30
D 34
pchild()
E 34
I 34
pchild(notused)
	int notused;
E 34
{
D 33
	register struct process *pp;
	register struct process	*fp;
	register int pid;
	union wait w;
	int jobflags;
D 7
#ifdef VMUNIX
	struct vtimes vt;
#endif
E 7
I 7
	struct rusage ru;
I 26
	extern int insource;
E 33
I 33
    register struct process *pp;
    register struct process *fp;
    register int pid;
    extern int insource;
    union wait w;
    int     jobflags;
    struct rusage ru;
E 33
E 26
E 7

D 15
	if (!timesdone)
		timesdone++, times(&shtimes);
E 15
loop:
D 15
	pid = wait3(&w.w_status, (setintr ? WNOHANG|WUNTRACED:WNOHANG),
D 7
#ifndef VMUNIX
	    0);
#else
	    &vt);
#endif
E 7
I 7
	    &ru);
E 15
I 15
D 24
	pid = wait3(&w, (setintr ? WNOHANG|WUNTRACED:WNOHANG), &ru);
E 24
I 24
D 26
	pid = wait3(&w, ((setintr && intty) ? WNOHANG|WUNTRACED:WNOHANG), &ru);
E 26
I 26
D 30
	pid = wait3(&w, (setintr && (intty || insource) ? WNOHANG|WUNTRACED:WNOHANG), &ru);
E 30
I 30
D 33
	pid = wait3((int *)&w,
	    (setintr && (intty || insource) ? WNOHANG|WUNTRACED:WNOHANG), &ru);
E 30
E 26
E 24
E 15
E 7
	if (pid <= 0) {
		if (errno == EINTR) {
			errno = 0;
			goto loop;
		}
		pnoprocesses = pid == -1;
		return;
E 33
I 33
    errno = 0;			/* reset, just in case */
    pid = wait3(&w.w_status,
       (setintr && (intty || insource) ? WNOHANG | WUNTRACED : WNOHANG), &ru);

    if (pid <= 0) {
	if (errno == EINTR) {
	    errno = 0;
	    goto loop;
E 33
	}
D 33
	for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next)
		if (pid == pp->p_pid)
			goto found;
	goto loop;
E 33
I 33
	pnoprocesses = pid == -1;
	return;
    }
D 38
    for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next)
E 38
I 38
    for (pp = proclist.p_next; pp != NULL; pp = pp->p_next)
E 38
	if (pid == pp->p_pid)
	    goto found;
    goto loop;
E 33
found:
D 33
	if (pid == atoi(value("child")))
		unsetv("child");
	pp->p_flags &= ~(PRUNNING|PSTOPPED|PREPORTED);
	if (WIFSTOPPED(w)) {
		pp->p_flags |= PSTOPPED;
		pp->p_reason = w.w_stopsig;
	} else {
D 15
		if (pp->p_flags & (PTIME|PPTIME) || adrof("time")) {
			time_t oldcutimes, oldcstimes;
			oldcutimes = shtimes.tms_cutime;
			oldcstimes = shtimes.tms_cstime;
D 8
			time(&pp->p_etime);
E 8
I 8
			gettimeofday(&pp->p_etime, (struct timezone *)0);
E 8
			times(&shtimes);
			pp->p_utime = shtimes.tms_cutime - oldcutimes;
			pp->p_stime = shtimes.tms_cstime - oldcstimes;
		} else
			times(&shtimes);
E 15
I 15
		if (pp->p_flags & (PTIME|PPTIME) || adrof("time"))
			(void) gettimeofday(&pp->p_etime, (struct timezone *)0);
E 15
D 7
#ifdef VMUNIX
		pp->p_vtimes = vt;
#endif
E 7
I 7
		pp->p_rusage = ru;
E 7
		if (WIFSIGNALED(w)) {
			if (w.w_termsig == SIGINT)
				pp->p_flags |= PINTERRUPTED;
			else
				pp->p_flags |= PSIGNALED;
			if (w.w_coredump)
				pp->p_flags |= PDUMPED;
			pp->p_reason = w.w_termsig;
		} else {
			pp->p_reason = w.w_retcode;
D 7
#ifdef IIASA
			if (pp->p_reason >= 3)
#else
E 7
			if (pp->p_reason != 0)
D 7
#endif
E 7
				pp->p_flags |= PAEXITED;
			else
				pp->p_flags |= PNEXITED;
		}
E 33
I 33
    if (pid == atoi(short2str(value(STRchild))))
	unsetv(STRchild);
    pp->p_flags &= ~(PRUNNING | PSTOPPED | PREPORTED);
    if (WIFSTOPPED(w)) {
	pp->p_flags |= PSTOPPED;
	pp->p_reason = w.w_stopsig;
    }
    else {
	if (pp->p_flags & (PTIME | PPTIME) || adrof(STRtime))
D 36
	    (void) gettimeofday(&pp->p_etime, (struct timezone *) 0);
E 36
I 36
	    (void) gettimeofday(&pp->p_etime, NULL);
E 36

	pp->p_rusage = ru;
	if (WIFSIGNALED(w)) {
	    if (w.w_termsig == SIGINT)
		pp->p_flags |= PINTERRUPTED;
	    else
		pp->p_flags |= PSIGNALED;
	    if (w.w_coredump)
		pp->p_flags |= PDUMPED;
	    pp->p_reason = w.w_termsig;
E 33
	}
D 33
	jobflags = 0;
E 33
I 33
	else {
	    pp->p_reason = w.w_retcode;
	    if (pp->p_reason != 0)
		pp->p_flags |= PAEXITED;
	    else
		pp->p_flags |= PNEXITED;
	}
    }
    jobflags = 0;
    fp = pp;
    do {
	if ((fp->p_flags & (PPTIME | PRUNNING | PSTOPPED)) == 0 &&
	    !child && adrof(STRtime) &&
	    fp->p_rusage.ru_utime.tv_sec + fp->p_rusage.ru_stime.tv_sec
	    >= atoi(short2str(value(STRtime))))
	    fp->p_flags |= PTIME;
	jobflags |= fp->p_flags;
    } while ((fp = fp->p_friends) != pp);
    pp->p_flags &= ~PFOREGND;
    if (pp == pp->p_friends && (pp->p_flags & PPTIME)) {
	pp->p_flags &= ~PPTIME;
	pp->p_flags |= PTIME;
    }
    if ((jobflags & (PRUNNING | PREPORTED)) == 0) {
E 33
	fp = pp;
	do {
D 33
		if ((fp->p_flags & (PPTIME|PRUNNING|PSTOPPED)) == 0 &&
		    !child && adrof("time") &&
D 15
		    (fp->p_utime + fp->p_stime) / HZ >=
E 15
I 15
		    fp->p_rusage.ru_utime.tv_sec+fp->p_rusage.ru_stime.tv_sec >=
E 15
		     atoi(value("time")))
			fp->p_flags |= PTIME;
		jobflags |= fp->p_flags;
E 33
I 33
	    if (fp->p_flags & PSTOPPED)
		fp->p_flags |= PREPORTED;
E 33
	} while ((fp = fp->p_friends) != pp);
D 33
	pp->p_flags &= ~PFOREGND;
	if (pp == pp->p_friends && (pp->p_flags & PPTIME)) {
		pp->p_flags &= ~PPTIME;
		pp->p_flags |= PTIME;
E 33
I 33
	while (fp->p_pid != fp->p_jobid)
	    fp = fp->p_friends;
	if (jobflags & PSTOPPED) {
	    if (pcurrent && pcurrent != fp)
		pprevious = pcurrent;
	    pcurrent = fp;
E 33
	}
D 33
	if ((jobflags & (PRUNNING|PREPORTED)) == 0) {
		fp = pp;
		do {
			if (fp->p_flags&PSTOPPED)
				fp->p_flags |= PREPORTED;
		} while((fp = fp->p_friends) != pp);
		while(fp->p_pid != fp->p_jobid)
			fp = fp->p_friends;
I 2
		if (jobflags&PSTOPPED) {
			if (pcurrent && pcurrent != fp)
				pprevious = pcurrent;
			pcurrent = fp;
		} else
			pclrcurr(fp);
E 2
		if (jobflags&PFOREGND) {
D 2
			if (jobflags&PSTOPPED) {
				if (pcurrent && pcurrent != fp)
					pprevious = pcurrent;
				pcurrent = fp;
			} else
				pclrcurr(fp);
E 2
			if (jobflags & (PSIGNALED|PSTOPPED|PPTIME) ||
D 28
#ifdef IIASA
			    jobflags & PAEXITED ||
#endif
E 28
			    !eq(dcwd->di_name, fp->p_cwd->di_name)) {
D 3
				if (jobflags & PSTOPPED)
					printf("\n");
				pprint(fp, AREASON|SHELLDIR);
E 3
I 3
				;	/* print in pjwait */
E 3
D 6
			} else if ((jobflags & (PTIME|PSTOPPED)) == PTIME)
E 6
I 6
			}
/*
		else if ((jobflags & (PTIME|PSTOPPED)) == PTIME)
E 6
				ptprint(fp);
I 6
*/
E 6
		} else {
			if (jobflags&PNOTIFY || adrof("notify")) {
				printf("\215\n");
D 15
				pprint(pp, NUMBER|NAME|REASON);
E 15
I 15
				(void) pprint(pp, NUMBER|NAME|REASON);
E 15
				if ((jobflags&PSTOPPED) == 0)
					pflush(pp);
			} else {
D 2
				if ((jobflags&PSTOPPED) == 0)
					pclrcurr(fp);
E 2
				fp->p_flags |= PNEEDNOTE;
				neednote++;
			}
		}
E 33
I 33
	else
	    pclrcurr(fp);
	if (jobflags & PFOREGND) {
	    if (jobflags & (PSIGNALED | PSTOPPED | PPTIME) ||
#ifdef IIASA
		jobflags & PAEXITED ||
#endif
		!eq(dcwd->di_name, fp->p_cwd->di_name)) {
		;		/* print in pjwait */
	    }
	    /* PWP: print a newline after ^C */
D 41
	    else if (jobflags & PINTERRUPTED)
D 40
		xputchar('\r' | QUOTE), xputchar('\n');
E 40
I 40
		(void) fputc('\r' | QUOTE, cshout), (void) fputc('\n', cshout);
E 41
I 41
	    else if (jobflags & PINTERRUPTED) {
D 45
		(void) fputc('\r' | QUOTE, cshout);
E 45
I 45
		(void) vis_fputc('\r' | QUOTE, cshout);
E 45
		(void) fputc('\n', cshout);
	    }
E 41
E 40
E 33
	}
D 33
	goto loop;
E 33
I 33
	else {
	    if (jobflags & PNOTIFY || adrof(STRnotify)) {
D 40
		xputchar('\r' | QUOTE), xputchar('\n');
E 40
I 40
D 41
		(void) fputc('\r' | QUOTE, cshout), (void) fputc('\n', cshout);
E 41
I 41
D 45
		(void) fputc('\r' | QUOTE, cshout);
E 45
I 45
		(void) vis_fputc('\r' | QUOTE, cshout);
E 45
		(void) fputc('\n', cshout);
E 41
E 40
		(void) pprint(pp, NUMBER | NAME | REASON);
		if ((jobflags & PSTOPPED) == 0)
		    pflush(pp);
	    }
	    else {
		fp->p_flags |= PNEEDNOTE;
		neednote++;
	    }
	}
    }
    goto loop;
E 33
}

I 33
void
E 33
pnote()
{
D 33
	register struct process *pp;
D 13
	int flags;
E 13
I 13
D 23
	int flags, omask;
E 23
I 23
	int flags;
	long omask;
E 33
I 33
    register struct process *pp;
    int     flags;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
E 33
E 23
E 13

D 33
	neednote = 0;
	for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next) {
		if (pp->p_flags & PNEEDNOTE) {
D 9
			sighold(SIGCHLD);
E 9
I 9
D 10
			(void) sigblock(mask(SIGCHLD));
E 10
I 10
D 13
			sighold(SIGCHLD);
E 13
I 13
			omask = sigblock(sigmask(SIGCHLD));
E 13
E 10
E 9
			pp->p_flags &= ~PNEEDNOTE;
			flags = pprint(pp, NUMBER|NAME|REASON);
			if ((flags&(PRUNNING|PSTOPPED)) == 0)
				pflush(pp);
D 9
			sigrelse(SIGCHLD);
E 9
I 9
D 10
			(void) sigrelse(mask(SIGCHLD));
E 10
I 10
D 13
			sigrelse(SIGCHLD);
E 13
I 13
D 15
			sigsetmask(omask);
E 15
I 15
			(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
		}
E 33
I 33
    neednote = 0;
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
E 48
D 38
    for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next) {
E 38
I 38
    for (pp = proclist.p_next; pp != NULL; pp = pp->p_next) {
E 38
	if (pp->p_flags & PNEEDNOTE) {
D 48
	    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
	    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
	    pp->p_flags &= ~PNEEDNOTE;
	    flags = pprint(pp, NUMBER | NAME | REASON);
	    if ((flags & (PRUNNING | PSTOPPED)) == 0)
		pflush(pp);
D 48
	    (void) sigsetmask(omask);
E 48
I 48
	    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
E 33
	}
I 33
    }
E 33
}

/*
 * pwait - wait for current job to terminate, maintaining integrity
 *	of current and previous job indicators.
 */
I 33
void
E 33
pwait()
{
D 33
	register struct process *fp, *pp;
I 13
D 23
	int omask;
E 23
I 23
	long omask;
E 33
I 33
    register struct process *fp, *pp;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
E 33
E 23
E 13

D 33
	/*
	 * Here's where dead procs get flushed.
	 */
D 9
	sighold(SIGCHLD);
E 9
I 9
D 10
	(void) sigblock(mask(SIGCHLD));
E 10
I 10
D 13
	sighold(SIGCHLD);
E 13
I 13
	omask = sigblock(sigmask(SIGCHLD));
E 13
E 10
E 9
	for (pp = (fp = &proclist)->p_next; pp != PNULL; pp = (fp = pp)->p_next)
		if (pp->p_pid == 0) {
			fp->p_next = pp->p_next;
			xfree(pp->p_command);
			if (pp->p_cwd && --pp->p_cwd->di_count == 0)
				if (pp->p_cwd->di_next == 0)
					dfree(pp->p_cwd);
			xfree((char *)pp);
			pp = fp;
		}
D 9
	sigrelse(SIGCHLD);
E 9
I 9
D 10
	(void) sigrelse(mask(SIGCHLD));
#ifdef notdef
E 10
I 10
D 13
	sigrelse(SIGCHLD);
E 10
E 9
	if (setintr)
D 9
		sigignore(SIGINT);
E 9
I 9
D 10
		signal(SIGINT, SIG_IGN);
#endif
E 10
I 10
		sigignore(SIGINT);
E 13
I 13
D 15
	sigsetmask(omask);
E 15
I 15
	(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
	pjwait(pcurrjob);
E 33
I 33
    /*
     * Here's where dead procs get flushed.
     */
D 48
    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
D 38
    for (pp = (fp = &proclist)->p_next; pp != PNULL; pp = (fp = pp)->p_next)
E 38
I 38
    for (pp = (fp = &proclist)->p_next; pp != NULL; pp = (fp = pp)->p_next)
E 38
	if (pp->p_pid == 0) {
	    fp->p_next = pp->p_next;
	    xfree((ptr_t) pp->p_command);
	    if (pp->p_cwd && --pp->p_cwd->di_count == 0)
		if (pp->p_cwd->di_next == 0)
		    dfree(pp->p_cwd);
	    xfree((ptr_t) pp);
	    pp = fp;
	}
D 48
    (void) sigsetmask(omask);
E 48
I 48
    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
    pjwait(pcurrjob);
E 33
}

I 33

E 33
/*
 * pjwait - wait for a job to finish or become stopped
 *	It is assumed to be in the foreground state (PFOREGND)
 */
I 33
void
E 33
pjwait(pp)
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33
{
D 33
	register struct process *fp;
D 9
	int jobflags, reason;
E 9
I 9
D 10
	int jobflags, reason, omask;
E 10
I 10
D 13
	int jobflags, reason;
E 13
I 13
D 23
	int jobflags, reason, omask;
E 23
I 23
	int jobflags, reason;
	long omask;
E 33
I 33
    register struct process *fp;
    int     jobflags, reason;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
E 33
E 23
D 15
	int (*old)();
E 15
E 13
E 10
E 9

I 13
D 14
	if (setintr)
		old = signal(SIGINT, SIG_IGN);

E 14
E 13
I 11
D 33
	while (pp->p_pid != pp->p_jobid)
		pp = pp->p_friends;
E 11
	fp = pp;
	do {
		if ((fp->p_flags&(PFOREGND|PRUNNING)) == PRUNNING)
			printf("BUG: waiting for background job!\n");
	} while ((fp = fp->p_friends) != pp);
	/*
	 * Now keep pausing as long as we are not interrupted (SIGINT),
	 * and the target process, or any of its friends, are running
	 */
	fp = pp;
I 13
	omask = sigblock(sigmask(SIGCHLD));
E 13
I 9
D 10
	omask = sigblock(mask(SIGCHLD));
E 10
E 9
	for (;;) {
I 10
D 13
		sighold(SIGCHLD);
E 13
E 10
D 9
		sighold(SIGCHLD);
E 9
		jobflags = 0;
		do
			jobflags |= fp->p_flags;
D 13
		while((fp = (fp->p_friends)) != pp);
E 13
I 13
		while ((fp = (fp->p_friends)) != pp);
E 13
		if ((jobflags & PRUNNING) == 0)
			break;
D 9
		sigpause(SIGCHLD);
E 9
I 9
D 10
		sigpause(omask &~ mask(SIGCHLD));
E 10
I 10
D 13
		sigpause(sigblock(0) &~ mask(SIGCHLD));
E 13
I 13
D 20
		sigpause(0);
E 20
I 20
D 23
		sigpause(sigblock(0) &~ sigmask(SIGCHLD));
E 23
I 23
		sigpause(sigblock(0L) &~ sigmask(SIGCHLD));
E 33
I 33
    while (pp->p_pid != pp->p_jobid)
	pp = pp->p_friends;
    fp = pp;

    do {
	if ((fp->p_flags & (PFOREGND | PRUNNING)) == PRUNNING)
D 40
	    xprintf("BUG: waiting for background job!\n");
E 40
I 40
	    (void) fprintf(csherr, "BUG: waiting for background job!\n");
E 40
    } while ((fp = fp->p_friends) != pp);
    /*
     * Now keep pausing as long as we are not interrupted (SIGINT), and the
     * target process, or any of its friends, are running
     */
    fp = pp;
D 48
    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
    for (;;) {
D 48
	(void) sigblock(sigmask(SIGCHLD));
E 48
I 48
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGCHLD);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
E 48
	jobflags = 0;
	do
	    jobflags |= fp->p_flags;
	while ((fp = (fp->p_friends)) != pp);
	if ((jobflags & PRUNNING) == 0)
	    break;
#ifdef JOBDEBUG
D 40
	xprintf("starting to sigpause for  SIGCHLD on %d\n", fp->p_pid);
E 40
I 40
D 44
	(void) fprintf(csherr, "starting to sigpause for  SIGCHLD on %d\n", 
E 44
I 44
D 48
	(void) fprintf(csherr, "starting to sigpause for  SIGCHLD on %d\n",
E 48
I 48
	(void) fprintf(csherr, "starting to sigsuspend for  SIGCHLD on %d\n",
E 48
E 44
		       fp->p_pid);
E 40
#endif				/* JOBDEBUG */
D 48
	(void) sigpause(omask & ~sigmask(SIGCHLD));
E 48
I 48
	sigset = osigset;
	sigdelset(&sigset, SIGCHLD);
	sigsuspend(&sigset);
E 48
    }
D 48
    (void) sigsetmask(omask);
E 48
I 48
    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
    if (tpgrp > 0)		/* get tty back */
	(void) tcsetpgrp(FSHTTY, tpgrp);
    if ((jobflags & (PSIGNALED | PSTOPPED | PTIME)) ||
	!eq(dcwd->di_name, fp->p_cwd->di_name)) {
	if (jobflags & PSTOPPED) {
D 40
	    xprintf("\n");
E 40
I 40
D 41
	    (void) fprintf(cshout, "\n");
E 41
I 41
	    (void) fputc('\n', cshout);
E 41
E 40
	    if (adrof(STRlistjobs)) {
		Char   *jobcommand[3];

		jobcommand[0] = STRjobs;
		if (eq(value(STRlistjobs), STRlong))
		    jobcommand[1] = STRml;
		else
		    jobcommand[1] = NULL;
		jobcommand[2] = NULL;

D 40
		dojobs(jobcommand);
E 40
I 40
		dojobs(jobcommand, NULL);
E 40
		(void) pprint(pp, SHELLDIR);
	    }
	    else
		(void) pprint(pp, AREASON | SHELLDIR);
E 33
E 23
E 20
E 13
E 10
E 9
	}
D 9
	sigrelse(SIGCHLD);
E 9
I 9
D 10
	sigsetmask(omask);
E 10
I 10
D 13
	sigrelse(SIGCHLD);
E 13
I 13
D 15
	sigsetmask(omask);
E 13
E 10
E 9
	if (tpgrp > 0)
		ioctl(FSHTTY, TIOCSPGRP, &tpgrp);	/* get tty back */
E 15
I 15
D 33
	(void) sigsetmask(omask);
	if (tpgrp > 0)			/* get tty back */
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&tpgrp);
E 15
I 4
	if ((jobflags&(PSIGNALED|PSTOPPED|PTIME)) ||
	     !eq(dcwd->di_name, fp->p_cwd->di_name)) {
		if (jobflags&PSTOPPED)
			printf("\n");
D 15
		pprint(pp, AREASON|SHELLDIR);
E 15
I 15
		(void) pprint(pp, AREASON|SHELLDIR);
E 15
	}
E 4
D 3
	if (jobflags & PSTOPPED)
		return;
	if ((jobflags&PINTERRUPTED) && setintr &&
E 3
I 3
	if ((jobflags&(PINTERRUPTED|PSTOPPED)) && setintr &&
E 3
	    (!gointr || !eq(gointr, "-"))) {
D 3
		pflush(pp);
		pintr();
E 3
I 3
		if ((jobflags & PSTOPPED) == 0)
			pflush(pp);
D 4
		else {
			printf("\n");
			pprint(pp, AREASON|SHELLDIR);
		}
E 4
		pintr1(0);
E 3
		/*NOTREACHED*/
	}
	reason = 0;
	fp = pp;
	do {
		if (fp->p_reason)
			reason = fp->p_flags & (PSIGNALED|PINTERRUPTED) ?
				fp->p_reason | QUOTE : fp->p_reason;
	} while ((fp = fp->p_friends) != pp);
	set("status", putn(reason));
	if (reason && exiterr)
		exitstat();
	pflush(pp);
E 33
I 33
	else
	    (void) pprint(pp, AREASON | SHELLDIR);
    }
    if ((jobflags & (PINTERRUPTED | PSTOPPED)) && setintr &&
	(!gointr || !eq(gointr, STRminus))) {
	if ((jobflags & PSTOPPED) == 0)
	    pflush(pp);
	pintr1(0);
	/* NOTREACHED */
    }
    reason = 0;
    fp = pp;
    do {
	if (fp->p_reason)
	    reason = fp->p_flags & (PSIGNALED | PINTERRUPTED) ?
		fp->p_reason | META : fp->p_reason;
    } while ((fp = fp->p_friends) != pp);
D 41
    if ((reason != 0) && (adrof(STRprintexitvalue)))
E 41
I 41
    if ((reason != 0) && (adrof(STRprintexitvalue))) {
E 41
D 40
	xprintf("Exit %d\n", reason);
E 40
I 40
	(void) fprintf(cshout, "Exit %d\n", reason);
I 41
    }
E 41
E 40
    set(STRstatus, putn(reason));
    if (reason && exiterr)
	exitstat();
    pflush(pp);
E 33
I 13
D 14
	if (setintr)
		signal(SIGINT, old);
E 14
E 13
}

/*
 * dowait - wait for all processes to finish
 */
I 33
void
E 33
D 40
dowait()
E 40
I 40
/*ARGSUSED*/
dowait(v, t)
    Char **v;
    struct command *t;
E 40
{
D 33
	register struct process *pp;
I 13
D 23
	int omask;
E 23
I 23
	long omask;
E 33
I 33
    register struct process *pp;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
E 33
E 23
E 13
I 9
D 10
	int omask;
E 10
E 9

D 33
	pjobs++;
D 13
	if (setintr)
D 9
		sigrelse(SIGINT);
E 9
I 9
D 10
		(void) sigrelse(mask(SIGINT));
	omask = sigblock(mask(SIGCHLD));
E 10
I 10
		sigrelse(SIGINT);
E 13
I 13
	omask = sigblock(sigmask(SIGCHLD));
E 33
I 33
    pjobs++;
D 48
    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
E 33
E 13
E 10
E 9
loop:
I 10
D 13
	sighold(SIGCHLD);
E 13
E 10
D 9
	sighold(SIGCHLD);
E 9
D 33
	for (pp = proclist.p_next; pp; pp = pp->p_next)
D 11
		if (pp->p_pid && pp->p_pid == pp->p_jobid &&
E 11
I 11
		if (pp->p_pid && /* pp->p_pid == pp->p_jobid && */
E 11
		    pp->p_flags&PRUNNING) {
D 9
			sigpause(SIGCHLD);
E 9
I 9
D 10
			sigpause(omask &~ mask(SIGCHLD));
E 10
I 10
D 13
			sigpause(sigblock(0) &~ mask(SIGCHLD));
E 13
I 13
D 23
			sigpause(0);
E 23
I 23
			sigpause(0L);
E 23
E 13
E 10
E 9
			goto loop;
		}
D 9
	sigrelse(SIGCHLD);
E 9
I 9
D 10
	sigsetmask(omask);
E 10
I 10
D 13
	sigrelse(SIGCHLD);
E 13
I 13
D 15
	sigsetmask(omask);
E 15
I 15
	(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
	pjobs = 0;
E 33
I 33
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_pid &&	/* pp->p_pid == pp->p_jobid && */
	    pp->p_flags & PRUNNING) {
D 36
	    (void) sigpause((sigmask_t) 0);
E 36
I 36
D 48
	    (void) sigpause((sigset_t) 0);
E 48
I 48
	    sigemptyset(&sigset);
	    sigsuspend(&sigset);
E 48
E 36
	    goto loop;
	}
D 48
    (void) sigsetmask(omask);
E 48
I 48
    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
    pjobs = 0;
E 33
}

/*
 * pflushall - flush all jobs from list (e.g. at fork())
 */
I 33
static void
E 33
pflushall()
{
D 33
	register struct process	*pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next)
		if (pp->p_pid)
			pflush(pp);
E 33
I 33
D 38
    for (pp = proclist.p_next; pp != PNULL; pp = pp->p_next)
E 38
I 38
    for (pp = proclist.p_next; pp != NULL; pp = pp->p_next)
E 38
	if (pp->p_pid)
	    pflush(pp);
E 33
}

/*
 * pflush - flag all process structures in the same job as the
 *	the argument process for deletion.  The actual free of the
 *	space is not done here since pflush is called at interrupt level.
 */
I 33
static void
E 33
pflush(pp)
D 33
	register struct process	*pp;
E 33
I 33
    register struct process *pp;
E 33
{
D 33
	register struct process *np;
	register int index;
E 33
I 33
    register struct process *np;
    register int idx;
E 33

D 33
	if (pp->p_pid == 0) {
		printf("BUG: process flushed twice");
		return;
	}
	while (pp->p_pid != pp->p_jobid)
		pp = pp->p_friends;
	pclrcurr(pp);
	if (pp == pcurrjob)
		pcurrjob = 0;
	index = pp->p_index;
	np = pp;
	do {
		np->p_index = np->p_pid = 0;
		np->p_flags &= ~PNEEDNOTE;
	} while ((np = np->p_friends) != pp);
	if (index == pmaxindex) {
		for (np = proclist.p_next, index = 0; np; np = np->p_next)
			if (np->p_index > index)
				index = np->p_index;
		pmaxindex = index;
	}
E 33
I 33
    if (pp->p_pid == 0) {
D 40
	xprintf("BUG: process flushed twice");
E 40
I 40
	(void) fprintf(csherr, "BUG: process flushed twice");
E 40
	return;
    }
    while (pp->p_pid != pp->p_jobid)
	pp = pp->p_friends;
    pclrcurr(pp);
    if (pp == pcurrjob)
	pcurrjob = 0;
    idx = pp->p_index;
    np = pp;
    do {
	np->p_index = np->p_pid = 0;
	np->p_flags &= ~PNEEDNOTE;
    } while ((np = np->p_friends) != pp);
    if (idx == pmaxindex) {
	for (np = proclist.p_next, idx = 0; np; np = np->p_next)
	    if (np->p_index > idx)
		idx = np->p_index;
	pmaxindex = idx;
    }
E 33
}

/*
 * pclrcurr - make sure the given job is not the current or previous job;
 *	pp MUST be the job leader
 */
I 33
static void
E 33
pclrcurr(pp)
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33
{

D 33
	if (pp == pcurrent)
		if (pprevious != PNULL) {
			pcurrent = pprevious;
			pprevious = pgetcurr(pp);
		} else {
			pcurrent = pgetcurr(pp);
			pprevious = pgetcurr(pp);
		}
	else if (pp == pprevious)
		pprevious = pgetcurr(pp);
E 33
I 33
    if (pp == pcurrent)
D 38
	if (pprevious != PNULL) {
E 38
I 38
	if (pprevious != NULL) {
E 38
	    pcurrent = pprevious;
	    pprevious = pgetcurr(pp);
	}
	else {
	    pcurrent = pgetcurr(pp);
	    pprevious = pgetcurr(pp);
	}
    else if (pp == pprevious)
	pprevious = pgetcurr(pp);
E 33
}

/* +4 here is 1 for '\0', 1 ea for << >& >> */
D 33
char	command[PMAXLEN+4];
int	cmdlen;
char	*cmdp;
E 33
I 33
static Char command[PMAXLEN + 4];
static int cmdlen;
static Char *cmdp;

E 33
/*
 * palloc - allocate a process structure and fill it up.
 *	an important assumption is made that the process is running.
 */
I 33
void
E 33
palloc(pid, t)
D 33
	int pid;
	register struct command *t;
E 33
I 33
    int     pid;
    register struct command *t;
E 33
{
D 33
	register struct process	*pp;
	int i;
E 33
I 33
    register struct process *pp;
    int     i;
E 33

D 33
	pp = (struct process *)calloc(1, sizeof(struct process));
	pp->p_pid = pid;
D 31
	pp->p_flags = t->t_dflg & FAND ? PRUNNING : PRUNNING|PFOREGND;
	if (t->t_dflg & FTIME)
E 31
I 31
	pp->p_flags = t->t_dflg & F_AMPERSAND ? PRUNNING : PRUNNING|PFOREGND;
	if (t->t_dflg & F_TIME)
E 31
		pp->p_flags |= PPTIME;
	cmdp = command;
	cmdlen = 0;
	padd(t);
	*cmdp++ = 0;
D 31
	if (t->t_dflg & FPOU) {
E 31
I 31
	if (t->t_dflg & F_PIPEOUT) {
E 31
		pp->p_flags |= PPOU;
D 31
		if (t->t_dflg & FDIAG)
E 31
I 31
		if (t->t_dflg & F_STDERR)
E 31
			pp->p_flags |= PDIAG;
	}
	pp->p_command = savestr(command);
	if (pcurrjob) {
		struct process *fp;
		/* careful here with interrupt level */
		pp->p_cwd = 0;
		pp->p_index = pcurrjob->p_index;
		pp->p_friends = pcurrjob;
		pp->p_jobid = pcurrjob->p_pid;
		for (fp = pcurrjob; fp->p_friends != pcurrjob; fp = fp->p_friends)
			;
		fp->p_friends = pp;
	} else {
		pcurrjob = pp;
		pp->p_jobid = pid;
		pp->p_friends = pp;
		pp->p_cwd = dcwd;
		dcwd->di_count++;
		if (pmaxindex < BIGINDEX)
			pp->p_index = ++pmaxindex;
		else {
			struct process *np;
E 33
I 33
    pp = (struct process *) xcalloc(1, (size_t) sizeof(struct process));
    pp->p_pid = pid;
    pp->p_flags = t->t_dflg & F_AMPERSAND ? PRUNNING : PRUNNING | PFOREGND;
    if (t->t_dflg & F_TIME)
	pp->p_flags |= PPTIME;
    cmdp = command;
    cmdlen = 0;
    padd(t);
    *cmdp++ = 0;
    if (t->t_dflg & F_PIPEOUT) {
	pp->p_flags |= PPOU;
	if (t->t_dflg & F_STDERR)
D 40
	    pp->p_flags |= PDIAG;
E 40
I 40
	    pp->p_flags |= PERR;
E 40
    }
    pp->p_command = Strsave(command);
    if (pcurrjob) {
	struct process *fp;
E 33

D 33
			for (i = 1; ; i++) {
				for (np = proclist.p_next; np; np = np->p_next)
					if (np->p_index == i)
						goto tryagain;
D 2
				pmaxindex = pp->p_index = i;
E 2
I 2
				pp->p_index = i;
				if (i > pmaxindex)
					pmaxindex = i;
E 2
				break;			
			tryagain:;
			}
		}
		if (pcurrent == PNULL)
			pcurrent = pp;
		else if (pprevious == PNULL)
			pprevious = pp;
E 33
I 33
	/* careful here with interrupt level */
	pp->p_cwd = 0;
	pp->p_index = pcurrjob->p_index;
	pp->p_friends = pcurrjob;
	pp->p_jobid = pcurrjob->p_pid;
D 44
	for (fp = pcurrjob; fp->p_friends != pcurrjob; fp = fp->p_friends);
E 44
I 44
	for (fp = pcurrjob; fp->p_friends != pcurrjob; fp = fp->p_friends)
	    continue;
E 44
	fp->p_friends = pp;
    }
    else {
	pcurrjob = pp;
	pp->p_jobid = pid;
	pp->p_friends = pp;
	pp->p_cwd = dcwd;
	dcwd->di_count++;
	if (pmaxindex < BIGINDEX)
	    pp->p_index = ++pmaxindex;
	else {
	    struct process *np;

	    for (i = 1;; i++) {
		for (np = proclist.p_next; np; np = np->p_next)
		    if (np->p_index == i)
			goto tryagain;
		pp->p_index = i;
		if (i > pmaxindex)
		    pmaxindex = i;
		break;
	tryagain:;
	    }
E 33
	}
D 33
	pp->p_next = proclist.p_next;
	proclist.p_next = pp;
D 8
	time(&pp->p_btime);
E 8
I 8
D 15
	gettimeofday(&pp->p_btime, (struct timezone *)0);
E 15
I 15
	(void) gettimeofday(&pp->p_btime, (struct timezone *)0);
E 33
I 33
D 38
	if (pcurrent == PNULL)
E 38
I 38
	if (pcurrent == NULL)
E 38
	    pcurrent = pp;
D 38
	else if (pprevious == PNULL)
E 38
I 38
	else if (pprevious == NULL)
E 38
	    pprevious = pp;
    }
    pp->p_next = proclist.p_next;
    proclist.p_next = pp;
D 36
    (void) gettimeofday(&pp->p_btime, (struct timezone *) 0);
E 36
I 36
    (void) gettimeofday(&pp->p_btime, NULL);
E 36
E 33
E 15
E 8
}

I 33
static void
E 33
padd(t)
D 33
	register struct command *t;
E 33
I 33
    register struct command *t;
E 33
{
D 33
	char **argp;
E 33
I 33
    Char  **argp;
E 33

D 33
	if (t == 0)
		return;
	switch (t->t_dtyp) {
E 33
I 33
    if (t == 0)
	return;
    switch (t->t_dtyp) {
E 33

D 31
	case TPAR:
E 31
I 31
D 33
	case NODE_PAREN:
E 31
		pads("( ");
		padd(t->t_dspr);
		pads(" )");
		break;
E 33
I 33
    case NODE_PAREN:
	pads(STRLparensp);
	padd(t->t_dspr);
	pads(STRspRparen);
	break;
E 33

D 31
	case TCOM:
E 31
I 31
D 33
	case NODE_COMMAND:
E 31
		for (argp = t->t_dcom; *argp; argp++) {
			pads(*argp);
			if (argp[1])
				pads(" ");
		}
		break;
E 33
I 33
    case NODE_COMMAND:
	for (argp = t->t_dcom; *argp; argp++) {
	    pads(*argp);
	    if (argp[1])
		pads(STRspace);
	}
	break;
E 33

I 33
    case NODE_OR:
    case NODE_AND:
    case NODE_PIPE:
    case NODE_LIST:
	padd(t->t_dcar);
	switch (t->t_dtyp) {
E 33
I 16
D 31
	case TOR:
	case TAND:
E 16
	case TFIL:
D 16
		padd(t->t_dcar);
		pads(" | ");
		padd(t->t_dcdr);
		return;

E 16
	case TLST:
E 31
I 31
	case NODE_OR:
I 33
	    pads(STRspor2sp);
	    break;
E 33
	case NODE_AND:
I 33
	    pads(STRspand2sp);
	    break;
E 33
	case NODE_PIPE:
I 33
	    pads(STRsporsp);
	    break;
E 33
	case NODE_LIST:
E 31
D 33
		padd(t->t_dcar);
D 16
		pads("; ");
E 16
I 16
		switch (t->t_dtyp) {
D 31
		case TOR:
E 31
I 31
		case NODE_OR:
E 31
			pads(" || ");
			break;
D 31
		case TAND:
E 31
I 31
		case NODE_AND:
E 31
			pads(" && ");
			break;
D 31
		case TFIL:
E 31
I 31
		case NODE_PIPE:
E 31
			pads(" | ");
			break;
D 31
		case TLST:
E 31
I 31
		case NODE_LIST:
E 31
			pads("; ");
			break;
		}
E 16
		padd(t->t_dcdr);
		return;
E 33
I 33
	    pads(STRsemisp);
	    break;
E 33
	}
D 31
	if ((t->t_dflg & FPIN) == 0 && t->t_dlef) {
		pads((t->t_dflg & FHERE) ? " << " : " < ");
E 31
I 31
D 33
	if ((t->t_dflg & F_PIPEIN) == 0 && t->t_dlef) {
		pads((t->t_dflg & F_READ) ? " << " : " < ");
E 31
		pads(t->t_dlef);
	}
D 31
	if ((t->t_dflg & FPOU) == 0 && t->t_drit) {
		pads((t->t_dflg & FCAT) ? " >>" : " >");
		if (t->t_dflg & FDIAG)
E 31
I 31
	if ((t->t_dflg & F_PIPEOUT) == 0 && t->t_drit) {
		pads((t->t_dflg & F_APPEND) ? " >>" : " >");
		if (t->t_dflg & F_STDERR)
E 31
			pads("&");
		pads(" ");
		pads(t->t_drit);
	}
E 33
I 33
	padd(t->t_dcdr);
	return;
    }
    if ((t->t_dflg & F_PIPEIN) == 0 && t->t_dlef) {
	pads((t->t_dflg & F_READ) ? STRspLarrow2sp : STRspLarrowsp);
	pads(t->t_dlef);
    }
    if ((t->t_dflg & F_PIPEOUT) == 0 && t->t_drit) {
	pads((t->t_dflg & F_APPEND) ? STRspRarrow2 : STRspRarrow);
	if (t->t_dflg & F_STDERR)
	    pads(STRand);
	pads(STRspace);
	pads(t->t_drit);
    }
E 33
}

I 33
static void
E 33
pads(cp)
D 33
	char *cp;
E 33
I 33
    Char   *cp;
E 33
{
D 33
	register int i = strlen(cp);
E 33
I 33
    register int i;
E 33

D 33
	if (cmdlen >= PMAXLEN)
		return;
	if (cmdlen + i >= PMAXLEN) {
D 15
		strcpy(cmdp, " ...");
E 15
I 15
		(void) strcpy(cmdp, " ...");
E 15
		cmdlen = PMAXLEN;
		cmdp += 4;
		return;
	}
D 15
	strcpy(cmdp, cp);
E 15
I 15
	(void) strcpy(cmdp, cp);
E 15
	cmdp += i;
	cmdlen += i;
E 33
I 33
    /*
     * Avoid the Quoted Space alias hack! Reported by:
     * sam@john-bigboote.ICS.UCI.EDU (Sam Horrocks)
     */
    if (cp[0] == STRQNULL[0])
	cp++;

    i = Strlen(cp);

    if (cmdlen >= PMAXLEN)
	return;
    if (cmdlen + i >= PMAXLEN) {
	(void) Strcpy(cmdp, STRsp3dots);
	cmdlen = PMAXLEN;
	cmdp += 4;
	return;
    }
    (void) Strcpy(cmdp, cp);
    cmdp += i;
    cmdlen += i;
E 33
}

/*
 * psavejob - temporarily save the current job on a one level stack
 *	so another job can be created.  Used for { } in exp6
 *	and `` in globbing.
 */
I 33
void
E 33
psavejob()
{

D 33
	pholdjob = pcurrjob;
	pcurrjob = PNULL;
E 33
I 33
    pholdjob = pcurrjob;
D 38
    pcurrjob = PNULL;
E 38
I 38
    pcurrjob = NULL;
E 38
E 33
}

/*
 * prestjob - opposite of psavejob.  This may be missed if we are interrupted
 *	somewhere, but pendjob cleans up anyway.
 */
I 33
void
E 33
prestjob()
{

D 33
	pcurrjob = pholdjob;
	pholdjob = PNULL;
E 33
I 33
    pcurrjob = pholdjob;
D 38
    pholdjob = PNULL;
E 38
I 38
    pholdjob = NULL;
E 38
E 33
}

/*
 * pendjob - indicate that a job (set of commands) has been completed
 *	or is about to begin.
 */
I 33
void
E 33
pendjob()
{
D 33
	register struct process *pp, *tp;
E 33
I 33
    register struct process *pp, *tp;
E 33

D 33
	if (pcurrjob && (pcurrjob->p_flags&(PFOREGND|PSTOPPED)) == 0) {
		pp = pcurrjob;
		while (pp->p_pid != pp->p_jobid)
			pp = pp->p_friends;
		printf("[%d]", pp->p_index);
		tp = pp;
		do {
			printf(" %d", pp->p_pid);
			pp = pp->p_friends;
		} while (pp != tp);
		printf("\n");
	}
	pholdjob = pcurrjob = 0;
E 33
I 33
    if (pcurrjob && (pcurrjob->p_flags & (PFOREGND | PSTOPPED)) == 0) {
	pp = pcurrjob;
	while (pp->p_pid != pp->p_jobid)
	    pp = pp->p_friends;
D 40
	xprintf("[%d]", pp->p_index);
E 40
I 40
	(void) fprintf(cshout, "[%d]", pp->p_index);
E 40
	tp = pp;
	do {
D 40
	    xprintf(" %d", pp->p_pid);
E 40
I 40
	    (void) fprintf(cshout, " %d", pp->p_pid);
E 40
	    pp = pp->p_friends;
	} while (pp != tp);
D 40
	xprintf("\n");
E 40
I 40
	(void) fputc('\n', cshout);
E 40
    }
    pholdjob = pcurrjob = 0;
E 33
}

/*
 * pprint - print a job
 */
I 33
static int
E 33
pprint(pp, flag)
D 33
	register struct process	*pp;
E 33
I 33
    register struct process *pp;
    bool    flag;
E 33
{
D 33
	register status, reason;
	struct process *tp;
	extern char *linp, linbuf[];
	int jobflags, pstatus;
	char *format;
E 33
I 33
    register status, reason;
    struct process *tp;
D 40
    extern char *linp, linbuf[];
E 40
    int     jobflags, pstatus;
I 41
    bool hadnl = 1;	/* did we just have a newline */
E 41
    char   *format;
E 33

I 40
    (void) fpurge(cshout);

E 40
D 33
	while (pp->p_pid != pp->p_jobid)
		pp = pp->p_friends;
	if (pp == pp->p_friends && (pp->p_flags & PPTIME)) {
		pp->p_flags &= ~PPTIME;
		pp->p_flags |= PTIME;
	}
	tp = pp;
	status = reason = -1; 
	jobflags = 0;
	do {
		jobflags |= pp->p_flags;
		pstatus = pp->p_flags & PALLSTATES;
		if (tp != pp && linp != linbuf && !(flag&FANCY) &&
		    (pstatus == status && pp->p_reason == reason ||
		     !(flag&REASON)))
			printf(" ");
E 33
I 33
    while (pp->p_pid != pp->p_jobid)
	pp = pp->p_friends;
    if (pp == pp->p_friends && (pp->p_flags & PPTIME)) {
	pp->p_flags &= ~PPTIME;
	pp->p_flags |= PTIME;
    }
    tp = pp;
    status = reason = -1;
    jobflags = 0;
    do {
	jobflags |= pp->p_flags;
	pstatus = pp->p_flags & PALLSTATES;
D 40
	if (tp != pp && linp != linbuf && !(flag & FANCY) &&
	    (pstatus == status && pp->p_reason == reason ||
E 40
I 40
D 41
	if (tp != pp && !(flag & FANCY) 
	    && (pstatus == status && pp->p_reason == reason ||
E 40
	     !(flag & REASON)))
E 41
I 41
D 44
	if (tp != pp && !hadnl && !(flag & FANCY) && 
E 44
I 44
	if (tp != pp && !hadnl && !(flag & FANCY) &&
E 44
	    ((pstatus == status && pp->p_reason == reason) ||
	     !(flag & REASON))) {
E 41
D 40
	    xprintf(" ");
E 40
I 40
	    (void) fputc(' ', cshout);
I 41
	    hadnl = 0;
	}
E 41
E 40
	else {
D 40
	    if (tp != pp && linp != linbuf)
		xprintf("\n");
E 40
I 40
D 41
	    if (tp != pp)
E 41
I 41
	    if (tp != pp && !hadnl) {
E 41
		(void) fputc('\n', cshout);
E 40
D 41
	    if (flag & NUMBER)
E 41
I 41
		hadnl = 1;
	    }
	    if (flag & NUMBER) {
E 41
		if (pp == tp)
D 40
		    xprintf("[%d]%s %c ", pp->p_index,
E 40
I 40
		    (void) fprintf(cshout, "[%d]%s %c ", pp->p_index,
E 40
			    pp->p_index < 10 ? " " : "",
			    pp == pcurrent ? '+' :
			    (pp == pprevious ? '-' : ' '));
		else
D 40
		    xprintf("       ");
E 40
I 40
		    (void) fprintf(cshout, "       ");
I 41
		hadnl = 0;
	    }
E 41
E 40
	    if (flag & FANCY) {
D 40
		xprintf("%5d ", pp->p_pid);
E 40
I 40
		(void) fprintf(cshout, "%5d ", pp->p_pid);
I 41
		hadnl = 0;
E 41
E 40
	    }
	    if (flag & (REASON | AREASON)) {
		if (flag & NAME)
		    format = "%-23s";
		else
		    format = "%s";
		if (pstatus == status)
		    if (pp->p_reason == reason) {
D 40
			xprintf(format, "");
E 40
I 40
			(void) fprintf(cshout, format, "");
I 41
			hadnl = 0;
E 41
E 40
			goto prcomd;
		    }
		    else
			reason = pp->p_reason;
E 33
		else {
D 33
			if (tp != pp && linp != linbuf)
				printf("\n");
			if(flag&NUMBER)
				if (pp == tp)
					printf("[%d]%s %c ", pp->p_index,
					    pp->p_index < 10 ? " " : "",
					    pp==pcurrent ? '+' :
						(pp == pprevious ? '-' : ' '));
				else
					printf("       ");
			if (flag&FANCY)
				printf("%5d ", pp->p_pid);
			if (flag&(REASON|AREASON)) {
				if (flag&NAME)
D 25
					format = "%-21s";
E 25
I 25
					format = "%-23s";
E 25
				else
					format = "%s";
				if (pstatus == status)
					if (pp->p_reason == reason) {
						printf(format, "");
						goto prcomd;
					} else
						reason = pp->p_reason;
				else {
					status = pstatus;
					reason = pp->p_reason;
				}
				switch (status) {
E 33
I 33
		    status = pstatus;
		    reason = pp->p_reason;
		}
		switch (status) {
E 33

D 33
				case PRUNNING:
					printf(format, "Running ");
					break;
E 33
I 33
		case PRUNNING:
D 40
		    xprintf(format, "Running ");
E 40
I 40
		    (void) fprintf(cshout, format, "Running ");
I 41
		    hadnl = 0;
E 41
E 40
		    break;
E 33

D 33
				case PINTERRUPTED:
				case PSTOPPED:
				case PSIGNALED:
D 22
					if (flag&REASON || reason != SIGINT ||
					    reason != SIGPIPE)
E 22
I 22
					if ((flag&(REASON|AREASON))
					    && reason != SIGINT
					    && reason != SIGPIPE)
E 22
						printf(format, mesg[pp->p_reason].pname);
					break;
E 33
I 33
		case PINTERRUPTED:
		case PSTOPPED:
		case PSIGNALED:
D 39
		    if ((flag & (REASON | AREASON)) && reason != SIGINT
			&& reason != SIGPIPE)
E 39
I 39
D 41
		    if ((flag & REASON) || 
			((flag & AREASON) && reason != SIGINT 
			 && reason != SIGPIPE))
E 41
I 41
                    /*
                     * tell what happened to the background job
                     * From: Michael Schroeder
                     * <mlschroe@immd4.informatik.uni-erlangen.de>
                     */
                    if ((flag & REASON)
                        || ((flag & AREASON)
                            && reason != SIGINT
                            && (reason != SIGPIPE
                                || (pp->p_flags & PPOU) == 0))) {
E 41
E 39
D 40
			xprintf(format, mesg[pp->p_reason].pname);
E 40
I 40
D 44
			(void) fprintf(cshout, format, 
E 44
I 44
			(void) fprintf(cshout, format,
E 44
D 42
				       mesg[pp->p_reason].pname);
E 42
I 42
D 43
				       sys_signame[pp->p_reason]);
E 43
I 43
D 46
				       sys_siglist[pp->p_reason]);
E 46
I 46
				       sys_siglist[(unsigned char)
						   pp->p_reason]);
E 46
E 43
E 42
I 41
			hadnl = 0;
		    }
E 41
E 40
		    break;
E 33

D 33
				case PNEXITED:
				case PAEXITED:
					if (flag & REASON)
						if (pp->p_reason)
							printf("Exit %-16d", pp->p_reason);
						else
							printf(format, "Done");
					break;
E 33
I 33
		case PNEXITED:
		case PAEXITED:
D 41
		    if (flag & REASON)
E 41
I 41
		    if (flag & REASON) {
E 41
			if (pp->p_reason)
D 39
			    xprintf("Exit %-16d", pp->p_reason);
E 39
I 39
D 40
			    xprintf("Exit %-18d", pp->p_reason);
E 40
I 40
			    (void) fprintf(cshout, "Exit %-18d", pp->p_reason);
E 40
E 39
			else
D 40
			    xprintf(format, "Done");
E 40
I 40
			    (void) fprintf(cshout, format, "Done");
I 41
			hadnl = 0;
		    }
E 41
E 40
		    break;
E 33

D 33
				default:
					printf("BUG: status=%-9o", status);
				}
			}
E 33
I 33
		default:
D 40
		    xprintf("BUG: status=%-9o", status);
E 40
I 40
		    (void) fprintf(csherr, "BUG: status=%-9o", status);
E 40
E 33
		}
I 33
	    }
	}
E 33
prcomd:
D 33
		if (flag&NAME) {
			printf("%s", pp->p_command);
			if (pp->p_flags & PPOU)
				printf(" |");
			if (pp->p_flags & PDIAG)
				printf("&");
		}
		if (flag&(REASON|AREASON) && pp->p_flags&PDUMPED)
			printf(" (core dumped)");
		if (tp == pp->p_friends) {
			if (flag&AMPERSAND)
				printf(" &");
			if (flag&JOBDIR &&
			    !eq(tp->p_cwd->di_name, dcwd->di_name)) {
				printf(" (wd: ");
				dtildepr(value("home"), tp->p_cwd->di_name);
				printf(")");
			}
		}
		if (pp->p_flags&PPTIME && !(status&(PSTOPPED|PRUNNING))) {
			if (linp != linbuf)
				printf("\n\t");
D 7
#ifndef VMUNIX
			ptimes(pp->p_utime, pp->p_stime, pp->p_etime-pp->p_btime);
#else
			pvtimes(&zvms, &pp->p_vtimes, pp->p_etime - pp->p_btime);
#endif
E 7
I 7
			{ static struct rusage zru;
D 8
			  prusage(&zru, &pp->p_rusage,
			      pp->p_etime - pp->p_btime);
E 8
I 8
			  prusage(&zru, &pp->p_rusage, &pp->p_etime,
			    &pp->p_btime);
E 8
			}
E 7
		}
		if (tp == pp->p_friends) {
			if (linp != linbuf)
				printf("\n");
			if (flag&SHELLDIR && !eq(tp->p_cwd->di_name, dcwd->di_name)) {
				printf("(wd now: ");
				dtildepr(value("home"), dcwd->di_name);
				printf(")\n");
			}
		}
	} while ((pp = pp->p_friends) != tp);
	if (jobflags&PTIME && (jobflags&(PSTOPPED|PRUNNING)) == 0) {
		if (jobflags & NUMBER)
			printf("       ");
		ptprint(tp);
E 33
I 33
	if (flag & NAME) {
D 40
	    xprintf("%s", short2str(pp->p_command));
E 40
I 40
D 45
	    (void) fprintf(cshout, "%s", short2str(pp->p_command));
E 45
I 45
	    (void) fprintf(cshout, "%s", vis_str(pp->p_command));
E 45
E 40
	    if (pp->p_flags & PPOU)
D 40
		xprintf(" |");
	    if (pp->p_flags & PDIAG)
		xprintf("&");
E 40
I 40
		(void) fprintf(cshout, " |");
	    if (pp->p_flags & PERR)
		(void) fputc('&', cshout);
I 41
	    hadnl = 0;
E 41
E 40
E 33
	}
D 33
	return (jobflags);
E 33
I 33
D 41
	if (flag & (REASON | AREASON) && pp->p_flags & PDUMPED)
E 41
I 41
	if (flag & (REASON | AREASON) && pp->p_flags & PDUMPED) {
E 41
D 40
	    xprintf(" (core dumped)");
E 40
I 40
	    (void) fprintf(cshout, " (core dumped)");
I 41
	    hadnl = 0;
	}
E 41
E 40
	if (tp == pp->p_friends) {
D 41
	    if (flag & AMPERSAND)
E 41
I 41
	    if (flag & AMPERSAND) {
E 41
D 40
		xprintf(" &");
E 40
I 40
		(void) fprintf(cshout, " &");
I 41
		hadnl = 0;
	    }
E 41
E 40
	    if (flag & JOBDIR &&
		!eq(tp->p_cwd->di_name, dcwd->di_name)) {
D 40
		xprintf(" (wd: ");
E 40
I 40
		(void) fprintf(cshout, " (wd: ");
E 40
		dtildepr(value(STRhome), tp->p_cwd->di_name);
D 40
		xprintf(")");
E 40
I 40
		(void) fputc(')', cshout);
I 41
		hadnl = 0;
E 41
E 40
	    }
	}
	if (pp->p_flags & PPTIME && !(status & (PSTOPPED | PRUNNING))) {
D 40
	    if (linp != linbuf)
		xprintf("\n\t");
E 40
I 40
D 41
	    (void) fprintf(cshout, "\n\t");
E 41
I 41
	    if (!hadnl)
		(void) fprintf(cshout, "\n\t");
E 41
E 40
	    prusage(&zru, &pp->p_rusage, &pp->p_etime,
		    &pp->p_btime);
I 41
	    hadnl = 1;
E 41
	}
	if (tp == pp->p_friends) {
D 40
	    if (linp != linbuf)
		xprintf("\n");
E 40
I 40
D 41
	    if (flag != SHELLDIR)
E 41
I 41
	    if (!hadnl) {
E 41
		(void) fputc('\n', cshout);
I 41
		hadnl = 1;
	    }
E 41
E 40
	    if (flag & SHELLDIR && !eq(tp->p_cwd->di_name, dcwd->di_name)) {
D 40
		xprintf("(wd now: ");
E 40
I 40
		(void) fprintf(cshout, "(wd now: ");
E 40
		dtildepr(value(STRhome), dcwd->di_name);
D 40
		xprintf(")\n");
E 40
I 40
		(void) fprintf(cshout, ")\n");
I 41
		hadnl = 1;
E 41
E 40
	    }
	}
    } while ((pp = pp->p_friends) != tp);
    if (jobflags & PTIME && (jobflags & (PSTOPPED | PRUNNING)) == 0) {
	if (jobflags & NUMBER)
D 40
	    xprintf("       ");
E 40
I 40
	    (void) fprintf(cshout, "       ");
E 40
	ptprint(tp);
I 41
	hadnl = 1;
E 41
    }
I 40
    (void) fflush(cshout);
E 40
    return (jobflags);
E 33
}

I 33
static void
E 33
ptprint(tp)
D 33
	register struct process *tp;
E 33
I 33
    register struct process *tp;
E 33
{
D 8
	time_t tetime = 0;
E 8
I 8
D 33
	struct timeval tetime, diff;
	static struct timeval ztime;
E 8
D 7
#ifdef VMUNIX
	struct vtimes vmt;
#else
	time_t tutime = 0, tstime = 0;
#endif
E 7
I 7
	struct rusage ru;
	static struct rusage zru;
E 7
	register struct process *pp = tp;
E 33
I 33
    struct timeval tetime, diff;
    static struct timeval ztime;
    struct rusage ru;
    static struct rusage zru;
    register struct process *pp = tp;
E 33

D 7
	vmt = zvms;
E 7
I 7
D 33
	ru = zru;
I 8
	tetime = ztime;
E 8
E 7
	do {
D 7
#ifdef VMUNIX
		vmsadd(&vmt, &pp->p_vtimes);
#else
		tutime += pp->p_utime;
		tstime += pp->p_stime;
#endif
E 7
I 7
		ruadd(&ru, &pp->p_rusage);
E 7
D 8
		if (pp->p_etime - pp->p_btime > tetime)
			tetime = pp->p_etime - pp->p_btime;
E 8
I 8
		tvsub(&diff, &pp->p_etime, &pp->p_btime);
		if (timercmp(&diff, &tetime, >))
			tetime = diff;
E 8
	} while ((pp = pp->p_friends) != tp);
D 7
#ifdef VMUNIX
	pvtimes(&zvms, &vmt, tetime);
#else
	ptimes(tutime, tstime, tetime);
#endif
E 7
I 7
D 8
	prusage(&zru, &ru, tetime);
E 8
I 8
	prusage(&zru, &ru, &tetime, &ztime);
E 33
I 33
    ru = zru;
    tetime = ztime;
    do {
	ruadd(&ru, &pp->p_rusage);
	tvsub(&diff, &pp->p_etime, &pp->p_btime);
	if (timercmp(&diff, &tetime, >))
	    tetime = diff;
    } while ((pp = pp->p_friends) != tp);
    prusage(&zru, &ru, &tetime, &ztime);
E 33
E 8
E 7
}

/*
 * dojobs - print all jobs
 */
I 33
void
E 33
D 40
dojobs(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dojobs(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
	register int flag = NUMBER|NAME|REASON;
	int i;
E 33
I 33
    register struct process *pp;
    register int flag = NUMBER | NAME | REASON;
    int     i;
E 33

D 33
	if (chkstop)
		chkstop = 2;
	if (*++v) {
		if (v[1] || !eq(*v, "-l"))
			error("Usage: jobs [ -l ]");
		flag |= FANCY|JOBDIR;
	}
	for (i = 1; i <= pmaxindex; i++)
		for (pp = proclist.p_next; pp; pp = pp->p_next)
			if (pp->p_index == i && pp->p_pid == pp->p_jobid) {
				pp->p_flags &= ~PNEEDNOTE;
				if (!(pprint(pp, flag) & (PRUNNING|PSTOPPED)))
					pflush(pp);
				break;
			}
E 33
I 33
    if (chkstop)
	chkstop = 2;
    if (*++v) {
	if (v[1] || !eq(*v, STRml))
	    stderror(ERR_JOBS);
	flag |= FANCY | JOBDIR;
    }
    for (i = 1; i <= pmaxindex; i++)
	for (pp = proclist.p_next; pp; pp = pp->p_next)
	    if (pp->p_index == i && pp->p_pid == pp->p_jobid) {
		pp->p_flags &= ~PNEEDNOTE;
		if (!(pprint(pp, flag) & (PRUNNING | PSTOPPED)))
		    pflush(pp);
		break;
	    }
E 33
}

/*
 * dofg - builtin - put the job into the foreground
 */
I 33
void
E 33
D 40
dofg(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dofg(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	okpcntl();
	++v;
	do {
		pp = pfind(*v);
		pstart(pp, 1);
D 13
		if (setintr)
D 9
			sigignore(SIGINT);
E 9
I 9
D 10
			signal(SIGINT, SIG_IGN);
E 10
I 10
			sigignore(SIGINT);
E 13
E 10
E 9
		pjwait(pp);
	} while (*v && *++v);
E 33
I 33
    okpcntl();
    ++v;
    do {
	pp = pfind(*v);
	pstart(pp, 1);
	pjwait(pp);
    } while (*v && *++v);
E 33
}

/*
 * %... - builtin - put the job into the foreground
 */
I 33
void
E 33
D 40
dofg1(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dofg1(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	okpcntl();
	pp = pfind(v[0]);
	pstart(pp, 1);
D 13
	if (setintr)
D 9
		sigignore(SIGINT);
E 9
I 9
D 10
		signal(SIGINT, SIG_IGN);
E 10
I 10
		sigignore(SIGINT);
E 13
E 10
E 9
	pjwait(pp);
E 33
I 33
    okpcntl();
    pp = pfind(v[0]);
    pstart(pp, 1);
    pjwait(pp);
E 33
}

/*
 * dobg - builtin - put the job into the background
 */
I 33
void
E 33
D 40
dobg(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dobg(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	okpcntl();
	++v;
	do {
		pp = pfind(*v);
		pstart(pp, 0);
	} while (*v && *++v);
E 33
I 33
    okpcntl();
    ++v;
    do {
	pp = pfind(*v);
	pstart(pp, 0);
    } while (*v && *++v);
E 33
}

/*
 * %... & - builtin - put the job into the background
 */
I 33
void
E 33
D 40
dobg1(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dobg1(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	pp = pfind(v[0]);
	pstart(pp, 0);
E 33
I 33
    pp = pfind(v[0]);
    pstart(pp, 0);
E 33
}

/*
 * dostop - builtin - stop the job
 */
I 33
void
E 33
D 40
dostop(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dostop(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33

	pkill(++v, SIGSTOP);
E 33
I 33
    pkill(++v, SIGSTOP);
E 33
}

/*
 * dokill - builtin - superset of kill (1)
 */
I 33
void
E 33
D 40
dokill(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
dokill(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register int signum;
	register char *name;
E 33
I 33
D 42
    register int signum, len = 0;
E 42
I 42
    register int signum = SIGTERM;
E 42
    register char *name;
E 33

D 33
	v++;
	if (v[0] && v[0][0] == '-') {
		if (v[0][1] == 'l') {
			for (signum = 1; signum <= NSIG; signum++) {
				if (name = mesg[signum].iname)
					printf("%s ", name);
				if (signum == 16)
D 15
					printf("\n");
E 15
I 15
D 27
					putchar('\n');
E 27
I 27
					cshputchar('\n');
E 27
E 15
			}
D 15
			printf("\n");
E 15
I 15
D 27
			putchar('\n');
E 27
I 27
			cshputchar('\n');
E 27
E 15
			return;
E 33
I 33
    v++;
    if (v[0] && v[0][0] == '-') {
	if (v[0][1] == 'l') {
D 42
	    for (signum = 1; signum <= NSIG; signum++) {
		if ((name = mesg[signum].iname) != NULL) {
		    len += strlen(name) + 1;
		    if (len >= 80 - 1) {
D 40
			xprintf("\n");
E 40
I 40
			(void) fputc('\n', cshout);
E 40
			len = strlen(name) + 1;
		    }
D 40
		    xprintf("%s ", name);
E 40
I 40
		    (void) fprintf(cshout, "%s ", name);
E 40
E 33
		}
E 42
I 42
	    for (signum = 1; signum < NSIG; signum++) {
		(void) fprintf(cshout, "%s ", sys_signame[signum]);
		if (signum == NSIG / 2)
		    (void) fputc('\n', cshout);
E 42
D 33
		if (digit(v[0][1])) {
			signum = atoi(v[0]+1);
D 22
			if (signum < 1 || signum > NSIG)
E 22
I 22
			if (signum < 0 || signum > NSIG)
E 22
				bferr("Bad signal number");
		} else {
			name = &v[0][1];
			for (signum = 1; signum <= NSIG; signum++)
			if (mesg[signum].iname &&
			    eq(name, mesg[signum].iname))
				goto gotsig;
			setname(name);
			bferr("Unknown signal; kill -l lists signals");
		}
E 33
I 33
	    }
D 40
	    xprintf("\n");
E 40
I 40
	    (void) fputc('\n', cshout);
E 40
	    return;
	}
	if (Isdigit(v[0][1])) {
	    signum = atoi(short2str(v[0] + 1));
	    if (signum < 0 || signum > NSIG)
		stderror(ERR_NAME | ERR_BADSIG);
	}
	else {
D 42
	    for (signum = 1; signum <= NSIG; signum++)
		if (mesg[signum].iname &&
		    eq(&v[0][1], str2short(mesg[signum].iname)))
		    goto gotsig;
	    setname(short2str(&v[0][1]));
	    stderror(ERR_NAME | ERR_UNKSIG);
E 42
I 42
	    name = short2str(&v[0][1]);
	    if (!strncasecmp(name, "sig", 3))
		name += 3;

D 44
	    for (signum = 1; signum < NSIG; signum++) 
E 44
I 44
	    for (signum = 1; signum < NSIG; signum++)
E 44
		if (!strcasecmp(sys_signame[signum], name))
		    break;

	    if (signum == NSIG) {
D 45
		setname(short2str(&v[0][1]));
E 45
I 45
		setname(vis_str(&v[0][1]));
E 45
		stderror(ERR_NAME | ERR_UNKSIG);
	    }
E 42
	}
E 33
D 42
gotsig:
E 42
D 33
		v++;
	} else
		signum = SIGTERM;
	pkill(v, signum);
E 33
I 33
	v++;
    }
D 42
    else
	signum = SIGTERM;
E 42
    pkill(v, signum);
E 33
}

I 33
static void
E 33
pkill(v, signum)
D 33
	char **v;
	int signum;
E 33
I 33
    Char  **v;
    int     signum;
E 33
{
D 33
	register struct process *pp, *np;
	register int jobflags = 0;
D 13
	int pid;
E 13
I 13
D 23
	int omask, pid, err = 0;
E 23
I 23
	int pid, err = 0;
	long omask;
E 23
E 13
I 11
	char *cp;
E 33
I 33
    register struct process *pp, *np;
    register int jobflags = 0;
    int     pid, err1 = 0;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset;
E 48
E 36
    Char   *cp;
E 33
E 11
D 29
	extern char *sys_errlist[];
E 29
D 9
	int err = 0;
E 9
I 9
D 10
	int err = 0, omask = 0;
E 10
I 10
D 13
	int err = 0;
E 13
E 10
E 9

I 13
D 33
	omask = sigmask(SIGCHLD);
E 13
	if (setintr)
D 9
		sighold(SIGINT);
	sighold(SIGCHLD);
E 9
I 9
D 10
		omask |= mask(SIGINT);
	omask |= mask(SIGCHLD);
	omask = sigblock(omask);
E 10
I 10
D 13
		sighold(SIGINT);
	sighold(SIGCHLD);
E 13
I 13
		omask |= sigmask(SIGINT);
	omask = sigblock(omask) & ~omask;
E 13
E 10
E 9
	while (*v) {
D 11
		if (**v == '%') {
			np = pp = pfind(*v);
E 11
I 11
		cp = globone(*v);
		if (*cp == '%') {
			np = pp = pfind(cp);
E 11
			do
				jobflags |= np->p_flags;
			while ((np = np->p_friends) != pp);
			switch (signum) {
E 33
I 33
D 48
    omask = sigmask(SIGCHLD);
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
E 48
    if (setintr)
D 48
	omask |= sigmask(SIGINT);
    omask = sigblock(omask) & ~omask;
E 48
I 48
	sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
E 48
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
E 33

D 33
			case SIGSTOP:
			case SIGTSTP:
			case SIGTTIN:
			case SIGTTOU:
				if ((jobflags & PRUNNING) == 0) {
D 11
					printf("%s: Already stopped\n", *v);
E 11
I 11
D 25
					printf("%s: Already stopped\n", cp);
E 25
I 25
					printf("%s: Already suspended\n", cp);
E 25
E 11
					err++;
					goto cont;
				}
			}
D 15
			killpg(pp->p_jobid, signum);
E 15
I 15
D 17
			(void) killpg(pp->p_jobid, signum);
E 17
I 17
			if (killpg(pp->p_jobid, signum) < 0) {
D 29
				printf("%s: ", cp);
				printf("%s\n", sys_errlist[errno]);
E 29
I 29
				printf("%s: %s\n", cp, strerror(errno));
E 29
				err++;
			}
E 17
E 15
			if (signum == SIGTERM || signum == SIGHUP)
D 15
				killpg(pp->p_jobid, SIGCONT);
E 15
I 15
				(void) killpg(pp->p_jobid, SIGCONT);
E 15
D 11
		} else if (!digit(**v))
E 11
I 11
D 22
		} else if (!digit(*cp))
E 22
I 22
		} else if (!(digit(*cp) || *cp == '-'))
E 22
E 11
			bferr("Arguments should be jobs or process id's");
		else {
D 11
			pid = atoi(*v);
E 11
I 11
			pid = atoi(cp);
E 11
			if (kill(pid, signum) < 0) {
D 29
				printf("%d: ", pid);
				printf("%s\n", sys_errlist[errno]);
E 29
I 29
				printf("%d: %s\n", pid, strerror(errno));
E 29
				err++;
				goto cont;
			}
			if (signum == SIGTERM || signum == SIGHUP)
D 15
				kill(pid, SIGCONT);
E 15
I 15
				(void) kill(pid, SIGCONT);
E 33
I 33
    while (v && (cp = *v)) {
	if (*cp == '%') {
	    np = pp = pfind(cp);
	    do
		jobflags |= np->p_flags;
	    while ((np = np->p_friends) != pp);
	    switch (signum) {

	    case SIGSTOP:
	    case SIGTSTP:
	    case SIGTTIN:
	    case SIGTTOU:
		if ((jobflags & PRUNNING) == 0) {
D 40
		    xprintf("%s: Already suspended\n", short2str(cp));
E 40
I 40
D 44
		    (void) fprintf(csherr, "%s: Already suspended\n", 
E 44
I 44
		    (void) fprintf(csherr, "%s: Already suspended\n",
E 44
D 45
				   short2str(cp));
E 45
I 45
				   vis_str(cp));
E 45
E 40
		    err1++;
		    goto cont;
E 33
E 15
		}
D 33
cont:
I 11
		xfree(cp);
E 11
		v++;
E 33
I 33
		break;
		/*
		 * suspend a process, kill -CONT %, then type jobs; the shell
		 * says it is suspended, but it is running; thanks jaap..
		 */
	    case SIGCONT:
		pstart(pp, 0);
		goto cont;
	    }
	    if (killpg((pid_t) pp->p_jobid, signum) < 0) {
D 40
		xprintf("%s: %s\n", short2str(cp), strerror(errno));
E 40
I 40
D 44
		(void) fprintf(csherr, "%s: %s\n", short2str(cp), 
E 44
I 44
D 45
		(void) fprintf(csherr, "%s: %s\n", short2str(cp),
E 45
I 45
		(void) fprintf(csherr, "%s: %s\n", vis_str(cp),
E 45
E 44
			       strerror(errno));
E 40
		err1++;
	    }
	    if (signum == SIGTERM || signum == SIGHUP)
		(void) killpg((pid_t) pp->p_jobid, SIGCONT);
E 33
	}
D 9
	sigrelse(SIGCHLD);
	if (setintr)
		sigrelse(SIGINT);
E 9
I 9
D 10
	sigsetmask(omask);
E 10
I 10
D 13
	sigrelse(SIGCHLD);
	if (setintr)
		sigrelse(SIGINT);
E 13
I 13
D 15
	sigsetmask(omask);
E 15
I 15
D 33
	(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
	if (err)
		error(NOSTR);
E 33
I 33
	else if (!(Isdigit(*cp) || *cp == '-'))
	    stderror(ERR_NAME | ERR_JOBARGS);
	else {
	    pid = atoi(short2str(cp));
	    if (kill((pid_t) pid, signum) < 0) {
D 40
		xprintf("%d: %s\n", pid, strerror(errno));
E 40
I 40
		(void) fprintf(csherr, "%d: %s\n", pid, strerror(errno));
E 40
		err1++;
		goto cont;
	    }
	    if (signum == SIGTERM || signum == SIGHUP)
		(void) kill((pid_t) pid, SIGCONT);
	}
cont:
	v++;
    }
    if (gargv)
	blkfree(gargv), gargv = 0;
D 48
    (void) sigsetmask(omask);
E 48
I 48
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
E 48
    if (err1)
	stderror(ERR_SILENT);
E 33
}

/*
 * pstart - start the job in foreground/background
 */
I 33
void
E 33
pstart(pp, foregnd)
D 33
	register struct process *pp;
	int foregnd;
E 33
I 33
    register struct process *pp;
    int     foregnd;
E 33
{
D 33
	register struct process *np;
D 13
	int jobflags = 0;
E 13
I 13
D 23
	int omask, jobflags = 0;
E 23
I 23
	int jobflags = 0;
	long omask;
E 33
I 33
    register struct process *np;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
    long    jobflags = 0;
E 33
E 23
E 13

D 9
	sighold(SIGCHLD);
E 9
I 9
D 10
	(void) sigblock(mask(SIGCHLD));
E 10
I 10
D 13
	sighold(SIGCHLD);
E 13
I 13
D 33
	omask = sigblock(sigmask(SIGCHLD));
E 13
E 10
E 9
	np = pp;
	do {
		jobflags |= np->p_flags;
		if (np->p_flags&(PRUNNING|PSTOPPED)) {
			np->p_flags |= PRUNNING;
			np->p_flags &= ~PSTOPPED;
			if (foregnd)
				np->p_flags |= PFOREGND;
			else
				np->p_flags &= ~PFOREGND;
		}
	} while((np = np->p_friends) != pp);
I 2
	if (!foregnd)
		pclrcurr(pp);
E 2
D 15
	pprint(pp, foregnd ? NAME|JOBDIR : NUMBER|NAME|AMPERSAND);
E 15
I 15
	(void) pprint(pp, foregnd ? NAME|JOBDIR : NUMBER|NAME|AMPERSAND);
E 15
	if (foregnd)
D 15
		ioctl(FSHTTY, TIOCSPGRP, &pp->p_jobid);
E 15
I 15
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&pp->p_jobid);
E 15
	if (jobflags&PSTOPPED)
D 15
		killpg(pp->p_jobid, SIGCONT);
D 9
	sigrelse(SIGCHLD);
E 9
I 9
D 10
	(void) sigrelse(mask(SIGCHLD));
E 10
I 10
D 13
	sigrelse(SIGCHLD);
E 13
I 13
	sigsetmask(omask);
E 15
I 15
		(void) killpg(pp->p_jobid, SIGCONT);
	(void) sigsetmask(omask);
E 33
I 33
D 48
    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
    np = pp;
    do {
	jobflags |= np->p_flags;
	if (np->p_flags & (PRUNNING | PSTOPPED)) {
	    np->p_flags |= PRUNNING;
	    np->p_flags &= ~PSTOPPED;
	    if (foregnd)
		np->p_flags |= PFOREGND;
	    else
		np->p_flags &= ~PFOREGND;
	}
    } while ((np = np->p_friends) != pp);
    if (!foregnd)
	pclrcurr(pp);
    (void) pprint(pp, foregnd ? NAME | JOBDIR : NUMBER | NAME | AMPERSAND);
    if (foregnd)
	(void) tcsetpgrp(FSHTTY, pp->p_jobid);
    if (jobflags & PSTOPPED)
	(void) killpg((pid_t) pp->p_jobid, SIGCONT);
D 48
    (void) sigsetmask(omask);
E 48
I 48
    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
E 33
E 15
E 13
E 10
E 9
}

I 33
void
E 33
panystop(neednl)
I 33
    bool    neednl;
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	chkstop = 2;
	for (pp = proclist.p_next; pp; pp = pp->p_next)
		if (pp->p_flags & PSTOPPED)
D 25
			error("\nThere are stopped jobs" + 1 - neednl);
E 25
I 25
			error("\nThere are suspended jobs" + 1 - neednl);
E 33
I 33
    chkstop = 2;
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_flags & PSTOPPED)
	    stderror(ERR_STOPPED, neednl ? "\n" : "");
E 33
E 25
}

struct process *
pfind(cp)
D 33
	char *cp;
E 33
I 33
    Char   *cp;
E 33
{
D 33
	register struct process *pp, *np;
E 33
I 33
    register struct process *pp, *np;
E 33

D 33
	if (cp == 0 || cp[1] == 0 || eq(cp, "%%") || eq(cp, "%+")) {
		if (pcurrent == PNULL)
			bferr("No current job");
		return (pcurrent);
	}
	if (eq(cp, "%-") || eq(cp, "%#")) {
		if (pprevious == PNULL)
			bferr("No previous job");
		return (pprevious);
	}
	if (digit(cp[1])) {
		int index = atoi(cp+1);
		for (pp = proclist.p_next; pp; pp = pp->p_next)
			if (pp->p_index == index && pp->p_pid == pp->p_jobid)
				return (pp);
		bferr("No such job");
	}
	np = PNULL;
E 33
I 33
    if (cp == 0 || cp[1] == 0 || eq(cp, STRcent2) || eq(cp, STRcentplus)) {
D 38
	if (pcurrent == PNULL)
E 38
I 38
	if (pcurrent == NULL)
E 38
	    stderror(ERR_NAME | ERR_JOBCUR);
	return (pcurrent);
    }
    if (eq(cp, STRcentminus) || eq(cp, STRcenthash)) {
D 38
	if (pprevious == PNULL)
E 38
I 38
	if (pprevious == NULL)
E 38
	    stderror(ERR_NAME | ERR_JOBPREV);
	return (pprevious);
    }
    if (Isdigit(cp[1])) {
	int     idx = atoi(short2str(cp + 1));

E 33
	for (pp = proclist.p_next; pp; pp = pp->p_next)
D 33
		if (pp->p_pid == pp->p_jobid) {
			if (cp[1] == '?') {
				register char *dp;
				for (dp = pp->p_command; *dp; dp++) {
					if (*dp != cp[2])
						continue;
					if (prefix(cp+2, dp))
						goto match;
				}
			} else if (prefix(cp+1, pp->p_command)) {
match:
				if (np)
					bferr("Ambiguous");
				np = pp;
			}
E 33
I 33
	    if (pp->p_index == idx && pp->p_pid == pp->p_jobid)
		return (pp);
	stderror(ERR_NAME | ERR_NOSUCHJOB);
    }
D 38
    np = PNULL;
E 38
I 38
    np = NULL;
E 38
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_pid == pp->p_jobid) {
	    if (cp[1] == '?') {
		register Char *dp;

		for (dp = pp->p_command; *dp; dp++) {
		    if (*dp != cp[2])
			continue;
		    if (prefix(cp + 2, dp))
			goto match;
E 33
		}
D 33
	if (np)
		return (np);
	if (cp[1] == '?')
		bferr("No job matches pattern");
	else
		bferr("No such job");
I 15
	/*NOTREACHED*/
E 33
I 33
	    }
	    else if (prefix(cp + 1, pp->p_command)) {
	match:
		if (np)
		    stderror(ERR_NAME | ERR_AMBIG);
		np = pp;
	    }
	}
    if (np)
	return (np);
    stderror(ERR_NAME | cp[1] == '?' ? ERR_JOBPAT : ERR_NOSUCHJOB);
    /* NOTREACHED */
    return (0);
E 33
E 15
}

I 33

E 33
/*
D 2
 * pgetcurr - find a job that is not pp and ``most recent''
E 2
I 2
 * pgetcurr - find most recent job that is not pp, preferably stopped
E 2
 */
D 33
struct process *
E 33
I 33
static struct process *
E 33
pgetcurr(pp)
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33
{
D 33
	register struct process *np;
I 2
	register struct process *xp = PNULL;
E 33
I 33
    register struct process *np;
D 38
    register struct process *xp = PNULL;
E 38
I 38
    register struct process *xp = NULL;
E 38
E 33
E 2

D 33
	for (np = proclist.p_next; np; np = np->p_next)
		if (np != pcurrent && np != pp && np->p_pid &&
		    np->p_pid == np->p_jobid) {
D 2
			return (np);
E 2
I 2
			if (np->p_flags & PSTOPPED)
				return (np);
			if (xp == PNULL)
				xp = np;
E 2
		}
D 2
	return (PNULL);
E 2
I 2
	return (xp);
E 33
I 33
    for (np = proclist.p_next; np; np = np->p_next)
	if (np != pcurrent && np != pp && np->p_pid &&
	    np->p_pid == np->p_jobid) {
	    if (np->p_flags & PSTOPPED)
		return (np);
D 38
	    if (xp == PNULL)
E 38
I 38
	    if (xp == NULL)
E 38
		xp = np;
	}
    return (xp);
E 33
E 2
}

/*
 * donotify - flag the job so as to report termination asynchronously
 */
I 33
void
E 33
D 40
donotify(v)
D 33
	char **v;
E 33
I 33
    Char  **v;
E 40
I 40
/*ARGSUSED*/
donotify(v, t)
    Char **v;
    struct command *t;
E 40
E 33
{
D 33
	register struct process *pp;
E 33
I 33
    register struct process *pp;
E 33

D 33
	pp = pfind(*++v);
	pp->p_flags |= PNOTIFY;
E 33
I 33
    pp = pfind(*++v);
    pp->p_flags |= PNOTIFY;
E 33
}

/*
 * Do the fork and whatever should be done in the child side that
 * should not be done if we are not forking at all (like for simple builtin's)
 * Also do everything that needs any signals fiddled with in the parent side
 *
 * Wanttty tells whether process and/or tty pgrps are to be manipulated:
 *	-1:	leave tty alone; inherit pgrp from parent
 *	 0:	already have tty; manipulate process pgrps only
 *	 1:	want to claim tty; manipulate process and tty pgrps
 * It is usually just the value of tpgrp.
 */
I 33

int
E 33
pfork(t, wanttty)
D 33
	struct command *t;	/* command we are forking for */
	int wanttty;
E 33
I 33
    struct command *t;		/* command we are forking for */
    int     wanttty;
E 33
{
D 33
	register int pid;
	bool ignint = 0;
D 9
	int pgrp;
E 9
I 9
D 10
	int pgrp, omask;
E 10
I 10
D 13
	int pgrp;
E 13
I 13
D 23
	int pgrp, omask;
E 23
I 23
	int pgrp;
	long omask;
E 33
I 33
    register int pid;
    bool    ignint = 0;
    int     pgrp;
D 36
    sigmask_t omask;
E 36
I 36
D 48
    sigset_t omask;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36
E 33
E 23
E 13
E 10
E 9

I 33
    /*
     * A child will be uninterruptible only under very special conditions.
     * Remember that the semantics of '&' is implemented by disconnecting the
     * process from the tty so signals do not need to ignored just for '&'.
     * Thus signals are set to default action for children unless: we have had
     * an "onintr -" (then specifically ignored) we are not playing with
     * signals (inherit action)
     */
    if (setintr)
	ignint = (tpgrp == -1 && (t->t_dflg & F_NOINTERRUPT))
	    || (gointr && eq(gointr, STRminus));
    /*
     * Check for maximum nesting of 16 processes to avoid Forking loops
     */
    if (child == 16)
	stderror(ERR_NESTING, 16);
    /*
     * Hold SIGCHLD until we have the process installed in our table.
     */
D 48
    omask = sigblock(sigmask(SIGCHLD));
E 48
I 48
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 48
    while ((pid = fork()) < 0)
	if (setintr == 0)
	    (void) sleep(FORKSLEEP);
	else {
D 48
	    (void) sigsetmask(omask);
E 48
I 48
	    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
	    stderror(ERR_NOPROC);
	}
    if (pid == 0) {
	settimes();
	pgrp = pcurrjob ? pcurrjob->p_jobid : getpid();
	pflushall();
D 38
	pcurrjob = PNULL;
E 38
I 38
	pcurrjob = NULL;
E 38
	child++;
	if (setintr) {
	    setintr = 0;	/* until I think otherwise */
	    /*
	     * Children just get blown away on SIGINT, SIGQUIT unless "onintr
	     * -" seen.
	     */
	    (void) signal(SIGINT, ignint ? SIG_IGN : SIG_DFL);
	    (void) signal(SIGQUIT, ignint ? SIG_IGN : SIG_DFL);
	    if (wanttty >= 0) {
		/* make stoppable */
		(void) signal(SIGTSTP, SIG_DFL);
		(void) signal(SIGTTIN, SIG_DFL);
		(void) signal(SIGTTOU, SIG_DFL);
	    }
	    (void) signal(SIGTERM, parterm);
	}
	else if (tpgrp == -1 && (t->t_dflg & F_NOINTERRUPT)) {
	    (void) signal(SIGINT, SIG_IGN);
	    (void) signal(SIGQUIT, SIG_IGN);
	}
	pgetty(wanttty, pgrp);
E 33
	/*
D 33
	 * A child will be uninterruptible only under very special
	 * conditions. Remember that the semantics of '&' is
	 * implemented by disconnecting the process from the tty so
	 * signals do not need to ignored just for '&'.
	 * Thus signals are set to default action for children unless:
	 *	we have had an "onintr -" (then specifically ignored)
	 *	we are not playing with signals (inherit action)
E 33
I 33
	 * Nohup and nice apply only to NODE_COMMAND's but it would be nice
	 * (?!?) if you could say "nohup (foo;bar)" Then the parser would have
	 * to know about nice/nohup/time
E 33
	 */
D 33
	if (setintr)
D 31
		ignint = (tpgrp == -1 && (t->t_dflg&FINT))
E 31
I 31
		ignint = (tpgrp == -1 && (t->t_dflg&F_NOINTERRUPT))
E 31
		    || (gointr && eq(gointr, "-"));
	/*
	 * Hold SIGCHLD until we have the process installed in our table.
	 */
D 9
	sighold(SIGCHLD);
E 9
I 9
D 10
	(void) sigblock(mask(SIGCHLD));
E 10
I 10
D 13
	sighold(SIGCHLD);
E 13
I 13
	omask = sigblock(sigmask(SIGCHLD));
E 13
E 10
E 9
	while ((pid = fork()) < 0)
		if (setintr == 0)
			sleep(FORKSLEEP);
		else {
D 9
			sigrelse(SIGINT);
			sigrelse(SIGCHLD);
E 9
I 9
D 10
			(void) sigrelse(mask(SIGINT)|mask(SIGCHLD));
E 10
I 10
D 13
			sigrelse(SIGINT);
			sigrelse(SIGCHLD);
E 13
I 13
D 15
			sigsetmask(omask);
E 15
I 15
			(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
			error("No more processes");
		}
	if (pid == 0) {
		settimes();
		pgrp = pcurrjob ? pcurrjob->p_jobid : getpid();
		pflushall();
		pcurrjob = PNULL;
D 15
		timesdone = 0;
E 15
		child++;
		if (setintr) {
			setintr = 0;		/* until I think otherwise */
D 9
			sigrelse(SIGCHLD);
E 9
I 9
D 10
			(void) sigrelse(mask(SIGCHLD));
E 10
I 10
D 13
			sigrelse(SIGCHLD);
E 13
E 10
E 9
			/*
			 * Children just get blown away on SIGINT, SIGQUIT
			 * unless "onintr -" seen.
			 */
D 15
			signal(SIGINT, ignint ? SIG_IGN : SIG_DFL);
			signal(SIGQUIT, ignint ? SIG_IGN : SIG_DFL);
E 15
I 15
			(void) signal(SIGINT, ignint ? SIG_IGN : SIG_DFL);
			(void) signal(SIGQUIT, ignint ? SIG_IGN : SIG_DFL);
E 15
			if (wanttty >= 0) {
				/* make stoppable */
D 15
				signal(SIGTSTP, SIG_DFL);
				signal(SIGTTIN, SIG_DFL);
				signal(SIGTTOU, SIG_DFL);
E 15
I 15
				(void) signal(SIGTSTP, SIG_DFL);
				(void) signal(SIGTTIN, SIG_DFL);
				(void) signal(SIGTTOU, SIG_DFL);
E 15
			}
D 15
			signal(SIGTERM, parterm);
E 15
I 15
			(void) signal(SIGTERM, parterm);
E 15
D 31
		} else if (tpgrp == -1 && (t->t_dflg&FINT)) {
E 31
I 31
		} else if (tpgrp == -1 && (t->t_dflg&F_NOINTERRUPT)) {
E 31
D 15
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
E 15
I 15
			(void) signal(SIGINT, SIG_IGN);
			(void) signal(SIGQUIT, SIG_IGN);
E 15
		}
D 29
		if (wanttty > 0)
D 15
			ioctl(FSHTTY, TIOCSPGRP, &pgrp);
E 15
I 15
			(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&pgrp);
E 29
E 15
		if (wanttty >= 0 && tpgrp >= 0)
D 15
			setpgrp(0, pgrp);
E 15
I 15
			(void) setpgrp(0, pgrp);
I 29
		if (wanttty > 0)
			(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&pgrp);
E 29
E 15
		if (tpgrp > 0)
			tpgrp = 0;		/* gave tty away */
		/*
D 31
		 * Nohup and nice apply only to TCOM's but it would be
		 * nice (?!?) if you could say "nohup (foo;bar)"
		 * Then the parser would have to know about nice/nohup/time
E 31
I 31
		 * Nohup and nice apply only to NODE_COMMAND's but it would be
		 * nice (?!?) if you could say "nohup (foo;bar)".  Then the
		 * parser would have to know about nice/nohup/time.
E 31
		 */
D 31
		if (t->t_dflg & FNOHUP)
E 31
I 31
		if (t->t_dflg & F_NOHUP)
E 31
D 15
			signal(SIGHUP, SIG_IGN);
E 15
I 15
			(void) signal(SIGHUP, SIG_IGN);
E 15
D 13
		if (t->t_dflg & FNICE) {
/* sigh...
			nice(20);
			nice(-10);
*/
			nice(t->t_nice);
		}
I 9
D 10
		sigrelse(mask(SIGINT));
E 10
E 9

E 13
I 13
D 31
		if (t->t_dflg & FNICE)
E 31
I 31
		if (t->t_dflg & F_NICE)
E 31
D 15
			setpriority(PRIO_PROCESS, 0, t->t_nice);
E 15
I 15
D 21
			(void) setpriority(PRIO_PROCESS, 0, t->t_nice);
E 21
I 21
D 22
			(void) setpriority(PRIO_PROCESS, 0,
			    getpriority(PRIO_PROCESS, 0) + t->t_nice);
E 22
I 22
			(void) setpriority(PRIO_PROCESS, 0, t->t_nice);
E 22
E 21
E 15
E 13
	} else {
I 28
		if (wanttty >= 0 && tpgrp >= 0)
			(void) setpgrp(pid, pcurrjob ? pcurrjob->p_jobid : pid);
E 28
		palloc(pid, t);
D 9
		sigrelse(SIGCHLD);
E 9
I 9
D 10
		(void) sigrelse(mask(SIGCHLD));
E 10
I 10
D 13
		sigrelse(SIGCHLD);
E 13
I 13
D 15
		sigsetmask(omask);
E 15
I 15
		(void) sigsetmask(omask);
E 15
E 13
E 10
E 9
	}
E 33
I 33
	if (t->t_dflg & F_NOHUP)
	    (void) signal(SIGHUP, SIG_IGN);
	if (t->t_dflg & F_NICE)
	    (void) setpriority(PRIO_PROCESS, 0, t->t_nice);
    }
    else {
	if (wanttty >= 0)
	    (void) setpgid(pid, pcurrjob ? pcurrjob->p_jobid : pid);
	palloc(pid, t);
D 48
	(void) sigsetmask(omask);
E 48
I 48
	sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
    }
E 33

D 33
	return (pid);
E 33
I 33
    return (pid);
E 33
}

I 33
static void
E 33
okpcntl()
{
I 33
    if (tpgrp == -1)
	stderror(ERR_JOBCONTROL);
    if (tpgrp == 0)
	stderror(ERR_JOBCTRLSUB);
}
E 33

D 33
	if (tpgrp == -1)
		error("No job control in this shell");
	if (tpgrp == 0)
		error("No job control in subshells");
E 33
I 33
/*
 * if we don't have vfork(), things can still go in the wrong order
 * resulting in the famous 'Stopped (tty output)'. But some systems
 * don't permit the setpgid() call, (these are more recent secure
 * systems such as ibm's aix). Then we'd rather print an error message
 * than hang the shell!
 * I am open to suggestions how to fix that.
 */
void
pgetty(wanttty, pgrp)
    int     wanttty, pgrp;
{
D 36
    sigmask_t omask = 0;
E 36
I 36
D 48
    sigset_t omask = 0;
E 48
I 48
    sigset_t sigset, osigset;
E 48
E 36

    /*
     * christos: I am blocking the tty signals till I've set things
     * correctly....
     */
D 48
    if (wanttty > 0)
	omask = sigblock(sigmask(SIGTSTP)|sigmask(SIGTTIN)|sigmask(SIGTTOU));
E 48
I 48
    if (wanttty > 0) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGTSTP);
	sigaddset(&sigset, SIGTTIN);
	sigaddset(&sigset, SIGTTOU);
	sigprocmask(SIG_BLOCK, &sigset, &osigset);
    }
E 48
    /*
     * From: Michael Schroeder <mlschroe@immd4.informatik.uni-erlangen.de>
     * Don't check for tpgrp >= 0 so even non-interactive shells give
     * background jobs process groups Same for the comparison in the other part
     * of the #ifdef
     */
    if (wanttty >= 0)
	if (setpgid(0, pgrp) == -1) {
D 40
	    xprintf("csh: setpgid error.\n");
E 40
I 40
	    (void) fprintf(csherr, "csh: setpgid error.\n");
E 40
	    xexit(0);
	}

    if (wanttty > 0) {
	(void) tcsetpgrp(FSHTTY, pgrp);
D 48
	(void) sigsetmask(omask);
E 48
I 48
	sigprocmask(SIG_SETMASK, &osigset, NULL);
E 48
    }

    if (tpgrp > 0)
	tpgrp = 0;		/* gave tty away */
E 33
I 9
D 10
}

/*
 * For "compatibility".
 */
sigrelse(m)
{

	return (sigsetmask(sigblock(0) &~ m));
E 10
E 9
}
E 1
