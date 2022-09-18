h10607
s 00012/00004/00708
d D 8.3 95/05/23 15:39:41 christos 36 35
c fix which /bin/csh returning .//bin/csh 
c (adapted changes from the tcsh source)
e
s 00003/00001/00709
d D 8.2 95/03/22 14:12:34 christos 35 34
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/00708
d D 8.1 93/05/31 16:41:55 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00706
d D 5.22 93/05/22 19:06:26 christos 33 32
c Fixed gcc -Wall warnings
e
s 00006/00006/00704
d D 5.21 91/11/06 16:09:34 christos 32 31
c Added support for displaying non-printable characters
e
s 00063/00010/00647
d D 5.20 91/10/18 00:20:49 christos 31 30
c Fixed exec so that it does not exit when it fails
e
s 00230/00000/00427
d D 5.19 91/07/28 14:14:18 christos 30 29
c Added dowhich() and doprintf() builtins.
e
s 00035/00026/00392
d D 5.18 91/07/19 17:30:41 christos 29 28
c stdio based version; brace glob fix; builtin prototypes
e
s 00003/00002/00415
d D 5.17 91/06/17 14:54:09 christos 28 27
c changed execv's to execve's
e
s 00006/00000/00411
d D 5.16 91/06/08 17:08:41 christos 27 26
c More prototype fixes, Removed TERMIOS define
e
s 00012/00005/00399
d D 5.15 91/06/08 12:20:15 bostic 26 25
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00004/00004/00400
d D 5.14 91/06/07 20:57:18 christos 25 24
c static function prototypes
e
s 00002/00035/00402
d D 5.13 91/06/07 11:13:21 bostic 24 23
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00311/00217/00126
d D 5.12 91/06/04 13:31:24 bostic 23 22
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00001/00001/00342
d D 5.11 91/04/04 18:17:37 bostic 22 21
c new copyright; att/bsd/shared
e
s 00007/00006/00336
d D 5.10 91/04/02 15:18:34 bostic 21 20
c get the SCCS id back
e
s 00001/00001/00341
d D 5.9 91/04/01 17:37:09 bostic 20 19
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00003/00003/00339
d D 5.8 91/03/14 12:27:44 bostic 19 18
c use the library globbing routines instead of rolling our own 
c any -> index (use the faster library routine)
e
s 00002/00002/00340
d D 5.7 90/05/27 15:42:58 bostic 18 17
c sys_errlist -> sterror(3)
e
s 00001/00001/00341
d D 5.6 89/04/02 11:57:50 bostic 17 16
c rest of pathnames
e
s 00003/00006/00339
d D 5.5 89/02/15 11:06:39 bostic 16 15
c use pathname include files; remove IIASA commands; remove newgrp
c command; add globall .cshrc, .login, and .logout files; minor cleanups
e
s 00001/00001/00344
d D 5.4 88/05/19 15:38:39 bostic 15 14
c install C version of _doprnt
e
s 00002/00003/00343
d D 5.3 87/06/25 09:15:10 bostic 14 13
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00003/00003/00343
d D 5.2 85/06/06 13:08:31 edward 13 12
c cleaning up after bozos
e
s 00008/00002/00338
d D 5.1 85/06/04 10:57:16 dist 12 11
c Add copyright
e
s 00001/00000/00339
d D 4.11 85/02/28 11:13:39 karels 11 10
c missing initialization
e
s 00065/00042/00274
d D 4.10 84/12/13 14:39:02 edward 10 9
c performance
e
s 00000/00000/00316
d D 4.9 84/08/31 09:30:55 ralph 9 8
c use new signal calls instead of compatibility routines.
e
s 00001/00001/00315
d D 4.8 83/07/01 03:50:55 sam 8 7
c include fix
e
s 00004/00002/00312
d D 4.7 83/06/11 16:49:06 sam 7 6
c different approach, try signal compatibility package
e
s 00003/00002/00311
d D 4.6 83/06/10 23:58:59 sam 6 5
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00000/00000/00313
d D 4.5 82/12/30 17:34:53 sam 5 4
c finally works (updated for 4.1c and merged with sun)
e
s 00001/00001/00312
d D 4.4 82/05/07 18:20:29 mckusick 4 3
c update to new fs
e
s 00013/00017/00300
d D 4.3 82/02/12 15:29:51 mckusic 3 2
c convret to new directory format
e
s 00001/00000/00316
d D 4.2 81/08/20 23:48:28 mckusic 2 1
c save history on "exec command
e
s 00316/00000/00000
d D 4.1 80/10/09 12:40:50 bill 1 0
c date and time created 80/10/09 12:40:50 by bill
e
u
U
t
T
I 12
D 21
/*
 * Copyright (c) 1980 Regents of the University of California.
D 13
 * All rights reserved.  The Berkeley software License Agreement
E 13
I 13
 * All rights reserved.  The Berkeley Software License Agreement
E 13
 * specifies the terms and conditions for redistribution.
E 21
I 21
/*-
D 22
 * Copyright (c) 1980 The Regents of the University of California.
E 22
I 22
D 34
 * Copyright (c) 1980, 1991 The Regents of the University of California.
E 22
 * All rights reserved.
E 34
I 34
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
 * %sccs.include.redist.c%
E 21
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
D 19
static char *sccsid = "%W% (Berkeley) %G%";
E 19
I 19
D 21
static char *sccsid = "@(#)sh.exec.c	5.7 (Berkeley) 5/27/90";
E 19
#endif
E 21
I 21
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 21
E 13
E 12
E 10

I 26
#include <sys/types.h>
I 30
#include <sys/param.h>
E 30
#include <dirent.h>
#include <fcntl.h>
I 30
#include <sys/stat.h>
E 30
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 27
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif 

E 27
E 26
D 24
#include "sh.h"
E 24
I 24
#include "csh.h"
#include "extern.h"
E 24
I 3
D 4
#include <ndir.h>
E 4
I 4
D 8
#include <dir.h>
E 8
I 8
D 23
#include <sys/dir.h>
I 18
#include <string.h>
E 18
I 16
D 17
#include <syspaths.h>
E 17
I 17
#include "pathnames.h"
E 23
E 17
E 16
E 8
E 4
E 3

/*
D 23
 * C shell
 */

/*
E 23
D 26
 * System level search and execute of a command.
 * We look in each directory for the specified command name.
 * If the name contains a '/' then we execute only the full path name.
 * If there is no search path then we execute only full path names.
E 26
I 26
 * System level search and execute of a command.  We look in each directory
 * for the specified command name.  If the name contains a '/' then we
 * execute only the full path name.  If there is no search path then we
 * execute only full path names.
E 26
 */
I 28
extern char **environ;
E 28

D 23
/* 
E 23
I 23
/*
E 23
 * As we search for the command we note the first non-trivial error
 * message for presentation to the user.  This allows us often
 * to show that a file has the wrong mode/no access when the file
 * is not in the last component of the search path, so we must
 * go on after first detecting the error.
 */
D 23
char	*exerr;			/* Execution error message */
char	*expath;		/* Path for exerr */
E 23
I 23
static char *exerr;		/* Execution error message */
static Char *expath;		/* Path for exerr */
E 23

/*
D 10
 * Xhash is an array of HSHSIZ chars, which are used to hash execs.
 * If it is allocated, then to tell whether ``name'' is (possibly)
 * present in the i'th component of the variable path, you look at
 * the i'th bit of xhash[hash("name")].  This is setup automatically
E 10
I 10
 * Xhash is an array of HSHSIZ bits (HSHSIZ / 8 chars), which are used
 * to hash execs.  If it is allocated (havhash true), then to tell
 * whether ``name'' is (possibly) present in the i'th component
 * of the variable path, you look at the bit in xhash indexed by
 * hash(hashname("name"), i).  This is setup automatically
E 10
 * after .login is executed, and recomputed whenever ``path'' is
 * changed.
I 10
 * The two part hash function is designed to let texec() call the
 * more expensive hashname() only once and the simple hash() several
 * times (once for each path component checked).
 * Byte size is assumed to be 8.
E 10
 */
D 10
int	havhash;
#define	HSHSIZ	511
char	xhash[HSHSIZ];
E 10
I 10
D 23
#define	HSHSIZ		8192			/* 1k bytes */
E 23
I 23
#define	HSHSIZ		8192	/* 1k bytes */
E 23
#define HSHMASK		(HSHSIZ - 1)
#define HSHMUL		243
D 23
char	xhash[HSHSIZ / 8];
E 23
I 23
static char xhash[HSHSIZ / 8];

E 23
D 33
#define hash(a, b)	((a) * HSHMUL + (b) & HSHMASK)
E 33
I 33
#define hash(a, b)	(((a) * HSHMUL + (b)) & HSHMASK)
E 33
#define bit(h, b)	((h)[(b) >> 3] & 1 << ((b) & 7))	/* bit test */
#define bis(h, b)	((h)[(b) >> 3] |= 1 << ((b) & 7))	/* bit set */
E 10
D 24
#ifdef VFORK
E 24
D 23
int	hits, misses;
E 23
I 23
static int hits, misses;

E 23
D 24
#endif

E 24
/* Dummy search path for just absolute search when no path */
D 23
char	*justabs[] =	{ "", 0 };
E 23
I 23
static Char *justabs[] = {STRNULL, 0};
E 23

I 23
D 25
static void pexerr();
static void texec();
static int hashname();
E 25
I 25
static void	pexerr __P((void));
static void	texec __P((Char *, Char **));
static int	hashname __P((Char *));
I 30
static void 	tellmewhat __P((struct wordent *));
static int	executable __P((Char *, Char *, bool));
static int	iscommand __P((Char *));
E 30
E 25

I 30

E 30
void
E 23
D 29
doexec(t)
D 23
	register struct command *t;
E 23
I 23
    register struct command *t;
E 29
I 29
/*ARGSUSED*/
doexec(v, t)
    Char **v;
    struct command *t;
E 29
E 23
{
D 23
	char *sav;
	register char *dp, **pv, **av;
	register struct varent *v;
D 19
	bool slash = any('/', t->t_dcom[0]);
E 19
I 19
	bool slash = (bool)index(t->t_dcom[0], '/');
E 19
D 10
	int hashval, i;
E 10
I 10
	int hashval, hashval1, i;
E 10
	char *blk[2];
E 23
I 23
    register Char *dp, **pv, **av, *sav;
D 29
    register struct varent *v;
E 29
I 29
    register struct varent *pathv;
E 29
    register bool slash;
    register int hashval = 0, hashval1, i;
    Char   *blk[2];
I 35
    sigset_t sigset;
E 35
E 23

D 23
	/*
	 * Glob the command name.  If this does anything, then we
	 * will execute the command only relative to ".".  One special
	 * case: if there is no PATH, then we execute only commands
	 * which start with '/'.
	 */
	dp = globone(t->t_dcom[0]);
	sav = t->t_dcom[0];
	exerr = 0; expath = t->t_dcom[0] = dp;
	xfree(sav);
	v = adrof("path");
	if (v == 0 && expath[0] != '/')
		pexerr();
	slash |= gflag;

	/*
	 * Glob the argument list, if necessary.
	 * Otherwise trim off the quote bits.
	 */
	gflag = 0; av = &t->t_dcom[1];
D 10
	rscan(av, tglob);
E 10
I 10
	tglob(av);
E 10
	if (gflag) {
D 19
		av = glob(av);
E 19
I 19
		av = globall(av);
E 19
		if (av == 0)
			error("No match");
E 23
I 23
    /*
     * Glob the command name. We will search $path even if this does something,
     * as in sh but not in csh.  One special case: if there is no PATH, then we
     * execute only commands which start with '/'.
     */
    blk[0] = t->t_dcom[0];
    blk[1] = 0;
    gflag = 0, tglob(blk);
    if (gflag) {
	pv = globall(blk);
	if (pv == 0) {
D 32
	    setname(short2str(blk[0]));
E 32
I 32
	    setname(vis_str(blk[0]));
E 32
	    stderror(ERR_NAME | ERR_NOMATCH);
E 23
	}
D 23
	blk[0] = t->t_dcom[0];
	blk[1] = 0;
	av = blkspl(blk, av);
E 23
I 23
	gargv = 0;
    }
    else
	pv = saveblk(blk);

    trim(pv);

    exerr = 0;
    expath = Strsave(pv[0]);
E 23
D 24
#ifdef VFORK
E 24
D 23
	Vav = av;
E 23
I 23
    Vexpath = expath;
E 23
D 24
#endif
E 24
D 10
	scan(av, trim);
E 10
I 10
D 23
	trim(av);
E 23
E 10

D 23
	xechoit(av);		/* Echo command if -x */
D 10
	closech();		/* Close random fd's */
E 10
I 10
	/*
	 * Since all internal file descriptors are set to close on exec,
	 * we don't need to close them explicitly here.  Just reorient
	 * ourselves for error messages.
	 */
	SHIN = 0; SHOUT = 1; SHDIAG = 2; OLDSTD = 0;
E 23
I 23
D 29
    v = adrof(STRpath);
    if (v == 0 && expath[0] != '/') {
E 29
I 29
    pathv = adrof(STRpath);
    if (pathv == 0 && expath[0] != '/') {
E 29
	blkfree(pv);
	pexerr();
    }
    slash = any(short2str(expath), '/');
E 23
E 10

D 23
	/*
D 6
	 * We must do this after any possible forking (like `foo`
E 6
I 6
	 * We must do this AFTER any possible forking (like `foo`
E 6
	 * in glob) so that this shell can still do subprocesses.
	 */
D 6
	sigsys(SIGCHLD, SIG_IGN);	/* sigsys for vforks sake */
E 6
I 6
D 7
	signal(SIGCHLD, SIG_IGN);
	sigsetmask(0);			/* sanity */
E 7
I 7
D 10
#ifdef notdef
	sigsys(SIGCHLD, SIG_IGN);	/* sigsys for vforks sake */
#endif
	sigsetmask(0);
E 10
I 10
D 14
	(void) sigsetmask(0);
E 14
I 14
	(void) sigsetmask(0L);
E 23
I 23
    /*
     * Glob the argument list, if necessary. Otherwise trim off the quote bits.
     */
    gflag = 0;
    av = &t->t_dcom[1];
    tglob(av);
    if (gflag) {
	av = globall(av);
	if (av == 0) {
	    blkfree(pv);
D 32
	    setname(short2str(expath));
E 32
I 32
	    setname(vis_str(expath));
E 32
	    stderror(ERR_NAME | ERR_NOMATCH);
	}
	gargv = 0;
    }
    else
	av = saveblk(av);
E 23
E 14
E 10
E 7
E 6

D 23
	/*
	 * If no path, no words in path, or a / in the filename
	 * then restrict the command search.
	 */
	if (v == 0 || v->vec[0] == 0 || slash)
		pv = justabs;
	else
		pv = v->vec;
	sav = strspl("/", *av);		/* / command name for postpending */
E 23
I 23
    blkfree(t->t_dcom);
    t->t_dcom = blkspl(pv, av);
    xfree((ptr_t) pv);
    xfree((ptr_t) av);
    av = t->t_dcom;
    trim(av);

D 25
    if (*av == (Char *) 0 || **av == '\0')
E 25
I 25
    if (*av == NULL || **av == '\0')
E 25
	pexerr();

    xechoit(av);		/* Echo command if -x */
    /*
     * Since all internal file descriptors are set to close on exec, we don't
     * need to close them explicitly here.  Just reorient ourselves for error
     * messages.
     */
    SHIN = 0;
    SHOUT = 1;
D 29
    SHDIAG = 2;
E 29
I 29
    SHERR = 2;
E 29
    OLDSTD = 0;
    /*
     * We must do this AFTER any possible forking (like `foo` in glob) so that
     * this shell can still do subprocesses.
     */
D 26
    (void) sigsetmask((sigmask_t) 0);
E 26
I 26
D 35
    (void) sigsetmask((sigset_t) 0);
E 35
I 35
    sigemptyset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
E 35
E 26
    /*
     * If no path, no words in path, or a / in the filename then restrict the
     * command search.
     */
D 29
    if (v == 0 || v->vec[0] == 0 || slash)
E 29
I 29
    if (pathv == 0 || pathv->vec[0] == 0 || slash)
E 29
	pv = justabs;
    else
D 29
	pv = v->vec;
E 29
I 29
	pv = pathv->vec;
E 29
    sav = Strspl(STRslash, *av);/* / command name for postpending */
E 23
D 24
#ifdef VFORK
E 24
D 23
	Vsav = sav;
E 23
I 23
    Vsav = sav;
E 23
D 24
#endif
E 24
D 23
	if (havhash)
D 10
		hashval = xhash[hash(*av)];
E 10
I 10
		hashval = hashname(*av);
E 10
	i = 0;
E 23
I 23
    if (havhash)
	hashval = hashname(*av);
    i = 0;
E 23
D 24
#ifdef VFORK
E 24
D 23
	hits++;
E 23
I 23
    hits++;
E 23
D 24
#endif
E 24
D 23
	do {
D 10
		if (!slash && pv[0][0] == '/' && havhash && (hashval & (1 << (i % 8))) == 0)
			goto cont;
E 10
I 10
		if (!slash && pv[0][0] == '/' && havhash) {
			hashval1 = hash(hashval, i);
			if (!bit(xhash, hashval1))
				goto cont;
		}
E 10
		if (pv[0][0] == 0 || eq(pv[0], "."))	/* don't make ./xxx */
			texec(*av, av);
		else {
			dp = strspl(*pv, sav);
E 23
I 23
    do {
	/*
	 * Try to save time by looking at the hash table for where this command
	 * could be.  If we are doing delayed hashing, then we put the names in
	 * one at a time, as the user enters them.  This is kinda like Korn
	 * Shell's "tracked aliases".
	 */
	if (!slash && pv[0][0] == '/' && havhash) {
	    hashval1 = hash(hashval, i);
	    if (!bit(xhash, hashval1))
		goto cont;
	}
	if (pv[0][0] == 0 || eq(pv[0], STRdot))	/* don't make ./xxx */
	    texec(*av, av);
	else {
	    dp = Strspl(*pv, sav);
E 23
D 24
#ifdef VFORK
E 24
D 23
			Vdp = dp;
E 23
I 23
	    Vdp = dp;
E 23
D 24
#endif
E 24
D 23
			texec(dp, av);
E 23
I 23
	    texec(dp, av);
E 23
D 24
#ifdef VFORK
E 24
D 23
			Vdp = 0;
E 23
I 23
	    Vdp = 0;
E 23
D 24
#endif
E 24
D 23
			xfree(dp);
		}
E 23
I 23
	    xfree((ptr_t) dp);
	}
E 23
D 24
#ifdef VFORK
E 24
D 23
		misses++;
E 23
I 23
	misses++;
E 23
D 24
#endif
E 24
cont:
D 23
		pv++;
		i++;
	} while (*pv);
E 23
I 23
	pv++;
	i++;
    } while (*pv);
E 23
D 24
#ifdef VFORK
E 24
D 23
	hits--;
E 23
I 23
    hits--;
E 23
D 24
#endif
#ifdef VFORK
E 24
D 23
	Vsav = 0;
	Vav = 0;
E 23
I 23
    Vsav = 0;
E 23
D 24
#endif
E 24
D 23
	xfree(sav);
D 10
	xfree(av);
E 10
I 10
	xfree((char *)av);
E 10
	pexerr();
E 23
I 23
    xfree((ptr_t) sav);
    pexerr();
E 23
}

I 23
static void
E 23
pexerr()
{
D 23

	/* Couldn't find the damn thing */
	setname(expath);
	/* xfree(expath); */
	if (exerr)
		bferr(exerr);
	bferr("Command not found");
E 23
I 23
    /* Couldn't find the damn thing */
    if (expath) {
D 32
	setname(short2str(expath));
E 32
I 32
	setname(vis_str(expath));
E 32
D 24
#ifdef VFORK
E 24
	Vexpath = 0;
D 24
#endif
E 24
	xfree((ptr_t) expath);
	expath = 0;
    }
    else
	setname("");
    if (exerr)
	stderror(ERR_NAME | ERR_STRING, exerr);
    stderror(ERR_NAME | ERR_COMMAND);
E 23
}

D 10
/* Last resort shell */
char	*lastsh[] =	{ SHELLPATH, 0 };

E 10
/*
 * Execute command f, arg list t.
 * Record error message if not found.
 * Also do shell scripts here.
 */
D 23
texec(f, t)
	char *f;
	register char **t;
E 23
I 23
static void
texec(sf, st)
    Char   *sf;
    register Char **st;
E 23
{
D 23
	register struct varent *v;
	register char **vp;
D 18
	extern char *sys_errlist[];
E 18
I 10
	char *lastsh[2];
E 23
I 23
    register char **t;
    register char *f;
    register struct varent *v;
    register Char **vp;
    Char   *lastsh[2];
    int     fd;
    unsigned char c;
    Char   *st0, **ost;
E 23
E 10

D 23
	execv(f, t);
	switch (errno) {
E 23
I 23
    /* The order for the conversions is significant */
    t = short2blk(st);
    f = short2str(sf);
D 24
#ifdef VFORK
E 24
    Vt = t;
D 24
#endif
E 24
    errno = 0;			/* don't use a previous error */
D 28
    (void) execv(f, t);
E 28
I 28
    (void) execve(f, t, environ);
E 28
D 24
#ifdef VFORK
E 24
    Vt = 0;
D 24
#endif
E 24
    blkfree((Char **) t);
    switch (errno) {
E 23

D 23
	case ENOEXEC:
		/*
		 * If there is an alias for shell, then
		 * put the words of the alias in front of the
		 * argument list replacing the command name.
		 * Note no interpretation of the words at this point.
		 */
		v = adrof1("shell", &aliases);
		if (v == 0) {
D 16
#ifdef OTHERSH
E 16
			register int ff = open(f, 0);
			char ch;
E 23
I 23
    case ENOEXEC:
	/*
	 * From: casper@fwi.uva.nl (Casper H.S. Dik) If we could not execute
	 * it, don't feed it to the shell if it looks like a binary!
	 */
	if ((fd = open(f, O_RDONLY)) != -1) {
	    if (read(fd, (char *) &c, 1) == 1) {
		if (!Isprint(c) && (c != '\n' && c != '\t')) {
		    (void) close(fd);
		    /*
		     * We *know* what ENOEXEC means.
		     */
		    stderror(ERR_ARCH, f, strerror(errno));
		}
	    }
#ifdef _PATH_BSHELL
	    else
		c = '#';
#endif
	    (void) close(fd);
	}
	/*
	 * If there is an alias for shell, then put the words of the alias in
	 * front of the argument list replacing the command name. Note no
	 * interpretation of the words at this point.
	 */
	v = adrof1(STRshell, &aliases);
	if (v == 0) {
	    vp = lastsh;
	    vp[0] = adrof(STRshell) ? value(STRshell) : STR_SHELLPATH;
	    vp[1] = NULL;
#ifdef _PATH_BSHELL
	    if (fd != -1 && c != '#')
		vp[0] = STR_BSHELL;
#endif
	}
	else
	    vp = v->vec;
	st0 = st[0];
	st[0] = sf;
	ost = st;
	st = blkspl(vp, st);	/* Splice up the new arglst */
	ost[0] = st0;
	sf = *st;
	/* The order for the conversions is significant */
	t = short2blk(st);
	f = short2str(sf);
	xfree((ptr_t) st);
D 24
#ifdef VFORK
E 24
	Vt = t;
D 24
#endif
E 24
D 28
	(void) execv(f, t);
E 28
I 28
	(void) execve(f, t, environ);
E 28
D 24
#ifdef VFORK
E 24
	Vt = 0;
D 24
#endif
E 24
	blkfree((Char **) t);
	/* The sky is falling, the sky is falling! */
E 23
D 16
#endif
E 16

D 23
			vp = lastsh;
D 16
			vp[0] = adrof("shell") ? value("shell") : SHELLPATH;
E 16
I 16
			vp[0] = adrof("shell") ? value("shell") : _PATH_CSHELL;
E 16
I 11
			vp[1] = (char *) NULL;
E 11
D 16
#ifdef OTHERSH
E 16
			if (ff != -1 && read(ff, &ch, 1) == 1 && ch != '#')
D 16
				vp[0] = OTHERSH;
E 16
I 16
				vp[0] = _PATH_BSHELL;
E 16
D 10
			close(ff);
E 10
I 10
			(void) close(ff);
E 10
D 16
#endif
E 16
		} else
			vp = v->vec;
		t[0] = f;
		t = blkspl(vp, t);		/* Splice up the new arglst */
		f = *t;
		execv(f, t);
		xfree((char *)t);
		/* The sky is falling, the sky is falling! */
E 23
I 23
    case ENOMEM:
	stderror(ERR_SYSTEM, f, strerror(errno));
E 23

D 23
	case ENOMEM:
		Perror(f);
E 23
I 23
    case ENOENT:
	break;
E 23

D 23
	case ENOENT:
		break;

	default:
		if (exerr == 0) {
D 18
			exerr = sys_errlist[errno];
E 18
I 18
			exerr = strerror(errno);
E 18
			expath = savestr(f);
		}
E 23
I 23
    default:
	if (exerr == 0) {
	    exerr = strerror(errno);
	    if (expath)
		xfree((ptr_t) expath);
	    expath = Strsave(sf);
D 24
#ifdef VFORK
E 24
	    Vexpath = expath;
D 24
#endif
E 24
E 23
	}
I 23
    }
E 23
}

I 10
/*ARGSUSED*/
I 23
void
E 23
E 10
D 29
execash(t, kp)
I 10
D 23
	char **t;
E 10
	register struct command *kp;
E 23
I 23
    char  **t;
    register struct command *kp;
E 29
I 29
D 31
execash(v, t)
    Char  **v;
    register struct command *t;
E 31
I 31
execash(t, kp)
    Char  **t;
    register struct command *kp;
E 31
E 29
E 23
{
I 31
    int     saveIN, saveOUT, saveDIAG, saveSTD;
    int     oSHIN;
    int     oSHOUT;
    int     oSHERR;
    int     oOLDSTD;
    jmp_buf osetexit;
    int	    my_reenter;
    int     odidfds;
    sig_t   osigint, osigquit, osigterm;

E 31
D 23

D 10
	didcch++;
E 10
I 2
	rechist();
E 2
D 10
	signal(SIGINT, parintr);
	signal(SIGQUIT, parintr);
	signal(SIGTERM, parterm);		/* if doexec loses, screw */
E 10
I 10
	(void) signal(SIGINT, parintr);
	(void) signal(SIGQUIT, parintr);
	(void) signal(SIGTERM, parterm);	/* if doexec loses, screw */
E 10
	lshift(kp->t_dcom, 1);
	exiterr++;
	doexec(kp);
	/*NOTREACHED*/
E 23
I 23
    if (chkstop == 0 && setintr)
	panystop(0);
I 31
    /*
     * Hmm, we don't really want to do that now because we might
     * fail, but what is the choice
     */
E 31
    rechist();
D 31
    (void) signal(SIGINT, parintr);
    (void) signal(SIGQUIT, parintr);
    (void) signal(SIGTERM, parterm);	/* if doexec loses, screw */
D 29
    lshift(kp->t_dcom, 1);
E 29
I 29
    lshift(t->t_dcom, 1);
E 29
    exiterr = 1;
D 29
    doexec(kp);
E 29
I 29
    doexec(NULL, t);
E 29
    /* NOTREACHED */
E 31
I 31

    osigint  = signal(SIGINT, parintr);
    osigquit = signal(SIGQUIT, parintr);
    osigterm = signal(SIGTERM, parterm);

    odidfds = didfds;
    oSHIN = SHIN;
    oSHOUT = SHOUT;
    oSHERR = SHERR;
    oOLDSTD = OLDSTD;

    saveIN = dcopy(SHIN, -1);
    saveOUT = dcopy(SHOUT, -1);
    saveDIAG = dcopy(SHERR, -1);
    saveSTD = dcopy(OLDSTD, -1);

    lshift(kp->t_dcom, 1);

    getexit(osetexit);

    if ((my_reenter = setexit()) == 0) {
	SHIN = dcopy(0, -1);
	SHOUT = dcopy(1, -1);
	SHERR = dcopy(2, -1);
	didfds = 0;
	doexec(t, kp);
    }

    (void) signal(SIGINT, osigint);
    (void) signal(SIGQUIT, osigquit);
    (void) signal(SIGTERM, osigterm);

    doneinp = 0;
    didfds = odidfds;
    (void) close(SHIN);
    (void) close(SHOUT);
    (void) close(SHERR);
    (void) close(OLDSTD);
    SHIN = dmove(saveIN, oSHIN);
    SHOUT = dmove(saveOUT, oSHOUT);
    SHERR = dmove(saveDIAG, oSHERR);
    OLDSTD = dmove(saveSTD, oOLDSTD);

    resexit(osetexit);
    if (my_reenter)
	stderror(ERR_SILENT);
E 31
E 23
}

I 23
void
E 23
xechoit(t)
D 23
	char **t;
E 23
I 23
    Char  **t;
E 23
{
D 23

	if (adrof("echo")) {
		flush();
		haderr = 1;
D 10
		blkpr(t), printf("\n");
E 10
I 10
D 15
		blkpr(t), putchar('\n');
E 15
I 15
		blkpr(t), cshputchar('\n');
E 15
E 10
		haderr = 0;
	}
E 23
I 23
    if (adrof(STRecho)) {
D 29
	flush();
	haderr = 1;
	blkpr(t), xputchar('\n');
	haderr = 0;
E 29
I 29
	(void) fflush(csherr);
	blkpr(csherr, t);
	(void) fputc('\n', csherr);
E 29
    }
E 23
}

D 10
dohash()
E 10
I 10
D 23
/*VARARGS0*//*ARGSUSED*/
E 23
I 23
D 29
/*VARARGS0*/
E 29
void
E 23
D 14
dohash(v)
	char **v;
E 14
I 14
D 29
dohash()
E 29
I 29
/*ARGSUSED*/
dohash(v, t)
    Char **v;
    struct command *t;
E 29
E 14
E 10
{
D 23
	struct stat stb;
D 3
	struct direct dirbuf[BUFSIZ / sizeof (struct direct)];
	char d_name[DIRSIZ + 1];
	register int dirf, cnt;
E 3
I 3
	DIR *dirp;
	register struct direct *dp;
	register int cnt;
E 3
	int i = 0;
	struct varent *v = adrof("path");
	char **pv;
I 10
	int hashval;
E 23
I 23
    DIR    *dirp;
    register struct dirent *dp;
    register int cnt;
    int     i = 0;
D 29
    struct varent *v = adrof(STRpath);
E 29
I 29
    struct varent *pathv = adrof(STRpath);
E 29
    Char  **pv;
    int     hashval;
E 23
E 10

D 23
	havhash = 1;
D 10
	for (cnt = 0; cnt < HSHSIZ; cnt++)
E 10
I 10
	for (cnt = 0; cnt < sizeof xhash; cnt++)
E 10
		xhash[cnt] = 0;
	if (v == 0)
		return;
D 10
	for (pv = v->vec; *pv; pv++, i = (i + 1) % 8) {
E 10
I 10
	for (pv = v->vec; *pv; pv++, i++) {
E 10
		if (pv[0][0] != '/')
			continue;
D 3
		dirf = open(*pv, 0);
		if (dirf < 0)
E 3
I 3
		dirp = opendir(*pv);
		if (dirp == NULL)
E 3
			continue;
D 3
		if (fstat(dirf, &stb) < 0 || !isdir(stb)) {
			close(dirf);
E 3
I 3
D 20
		if (fstat(dirp->dd_fd, &stb) < 0 || !isdir(stb)) {
E 20
I 20
		if (fstat(dirp->dd_fd, &stb) < 0 || !S_ISDIR(stb.st_mode)) {
E 20
			closedir(dirp);
E 3
			continue;
		}
D 3
		while ((cnt = read(dirf, (char *) dirbuf, sizeof dirbuf)) >= sizeof dirbuf[0]) {
			register struct direct *ep = dirbuf;

			for (cnt /= sizeof(struct direct); cnt > 0; cnt--, ep++) {
				if (ep->d_ino == 0)
					continue;
				copdent(d_name, ep->d_name);
				xhash[hash(d_name)] |= (1 << i);
			}
E 3
I 3
		while ((dp = readdir(dirp)) != NULL) {
			if (dp->d_ino == 0)
				continue;
D 10
			xhash[hash(dp->d_name)] |= (1 << i);
E 10
I 10
			if (dp->d_name[0] == '.' &&
			    (dp->d_name[1] == '\0' ||
			     dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
				continue;
			hashval = hash(hashname(dp->d_name), i);
			bis(xhash, hashval);
E 10
E 3
		}
D 3
		close(dirf);
E 3
I 3
		closedir(dirp);
E 23
I 23
    havhash = 1;
    for (cnt = 0; cnt < sizeof xhash; cnt++)
	xhash[cnt] = 0;
D 29
    if (v == 0)
E 29
I 29
    if (pathv == 0)
E 29
	return;
D 29
    for (pv = v->vec; *pv; pv++, i++) {
E 29
I 29
    for (pv = pathv->vec; *pv; pv++, i++) {
E 29
	if (pv[0][0] != '/')
	    continue;
	dirp = opendir(short2str(*pv));
	if (dirp == NULL)
	    continue;
	while ((dp = readdir(dirp)) != NULL) {
	    if (dp->d_ino == 0)
		continue;
	    if (dp->d_name[0] == '.' &&
		(dp->d_name[1] == '\0' ||
D 33
		 dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
E 33
I 33
		 (dp->d_name[1] == '.' && dp->d_name[2] == '\0')))
E 33
		continue;
	    hashval = hash(hashname(str2short(dp->d_name)), i);
	    bis(xhash, hashval);
	    /* tw_add_comm_name (dp->d_name); */
E 23
E 3
	}
I 23
	(void) closedir(dirp);
    }
E 23
}

I 23
void
E 23
D 29
dounhash()
E 29
I 29
/*ARGSUSED*/
dounhash(v, t)
    Char **v;
    struct command *t;
E 29
{
D 23

	havhash = 0;
E 23
I 23
    havhash = 0;
E 23
}

D 24
#ifdef VFORK
E 24
I 23
void
E 23
D 29
hashstat()
E 29
I 29
/*ARGSUSED*/
hashstat(v, t)
    Char **v;
    struct command *t;
E 29
{
D 23

	if (hits+misses)
D 10
	printf("%d hits, %d misses, %2d%%\n", hits, misses, 100 * hits / (hits + misses));
E 10
I 10
		printf("%d hits, %d misses, %d%%\n",
			hits, misses, 100 * hits / (hits + misses));
E 23
I 23
    if (hits + misses)
D 29
	xprintf("%d hits, %d misses, %d%%\n",
		hits, misses, 100 * hits / (hits + misses));
E 29
I 29
	(void) fprintf(cshout, "%d hits, %d misses, %d%%\n",
		       hits, misses, 100 * hits / (hits + misses));
E 29
E 23
E 10
}
I 23
D 24

E 23
#endif
E 24

D 10
hash(cp)
E 10
I 10
/*
 * Hash a command name.
 */
I 23
static int
E 23
hashname(cp)
E 10
D 23
	register char *cp;
E 23
I 23
    register Char *cp;
E 23
{
D 10
	register long hash = 0;
	int retval;
E 10
I 10
D 23
	register long h = 0;
E 23
I 23
    register long h = 0;
E 23
E 10

D 23
	while (*cp)
D 10
		hash += hash + *cp++;
	if (hash < 0)
		hash = -hash;
	retval = hash % HSHSIZ;
	return (retval);
E 10
I 10
		h = hash(h, *cp++);
	return ((int) h);
E 23
I 23
    while (*cp)
	h = hash(h, *cp++);
    return ((int) h);
I 30
}

static int
iscommand(name)
    Char   *name;
{
    register Char **pv;
    register Char *sav;
    register struct varent *v;
    register bool slash = any(short2str(name), '/');
    register int hashval = 0, hashval1, i;

    v = adrof(STRpath);
    if (v == 0 || v->vec[0] == 0 || slash)
	pv = justabs;
    else
	pv = v->vec;
    sav = Strspl(STRslash, name);	/* / command name for postpending */
    if (havhash)
	hashval = hashname(name);
    i = 0;
    do {
	if (!slash && pv[0][0] == '/' && havhash) {
	    hashval1 = hash(hashval, i);
	    if (!bit(xhash, hashval1))
		goto cont;
	}
	if (pv[0][0] == 0 || eq(pv[0], STRdot)) {	/* don't make ./xxx */
	    if (executable(NULL, name, 0)) {
		xfree((ptr_t) sav);
		return i + 1;
	    }
	}
	else {
	    if (executable(*pv, sav, 0)) {
		xfree((ptr_t) sav);
		return i + 1;
	    }
	}
cont:
	pv++;
	i++;
    } while (*pv);
    xfree((ptr_t) sav);
    return 0;
}

/* Also by:
 *  Andreas Luik <luik@isaak.isa.de>
 *  I S A  GmbH - Informationssysteme fuer computerintegrierte Automatisierung
 *  Azenberstr. 35
 *  D-7000 Stuttgart 1
 *  West-Germany
 * is the executable() routine below and changes to iscommand().
 * Thanks again!!
 */

/*
 * executable() examines the pathname obtained by concatenating dir and name
 * (dir may be NULL), and returns 1 either if it is executable by us, or
 * if dir_ok is set and the pathname refers to a directory.
 * This is a bit kludgy, but in the name of optimization...
 */
static int
executable(dir, name, dir_ok)
    Char   *dir, *name;
    bool    dir_ok;
{
    struct stat stbuf;
    Char    path[MAXPATHLEN + 1], *dp, *sp;
    char   *strname;

    if (dir && *dir) {
	for (dp = path, sp = dir; *sp; *dp++ = *sp++)
	    if (dp == &path[MAXPATHLEN + 1]) {
		*--dp = '\0';
		break;
	    }
	for (sp = name; *sp; *dp++ = *sp++)
	    if (dp == &path[MAXPATHLEN + 1]) {
		*--dp = '\0';
		break;
	    }
	*dp = '\0';
	strname = short2str(path);
    }
    else
	strname = short2str(name);
    return (stat(strname, &stbuf) != -1 &&
	    ((S_ISREG(stbuf.st_mode) &&
    /* save time by not calling access() in the hopeless case */
	      (stbuf.st_mode & (S_IXOTH | S_IXGRP | S_IXUSR)) &&
	      access(strname, X_OK) == 0) ||
	     (dir_ok && S_ISDIR(stbuf.st_mode))));
}

/* The dowhich() is by:
 *  Andreas Luik <luik@isaak.isa.de>
 *  I S A  GmbH - Informationssysteme fuer computerintegrierte Automatisierung
 *  Azenberstr. 35
 *  D-7000 Stuttgart 1
 *  West-Germany
 * Thanks!!
 */
/*ARGSUSED*/
void
dowhich(v, c)
    register Char **v;
    struct command *c;
{
    struct wordent lex[3];
    struct varent *vp;

    lex[0].next = &lex[1];
    lex[1].next = &lex[2];
    lex[2].next = &lex[0];

    lex[0].prev = &lex[2];
    lex[1].prev = &lex[0];
    lex[2].prev = &lex[1];

    lex[0].word = STRNULL;
    lex[2].word = STRret;

    while (*++v) {
D 33
	if (vp = adrof1(*v, &aliases)) {
E 33
I 33
	if ((vp = adrof1(*v, &aliases)) != NULL) {
E 33
D 32
	    (void) fprintf(cshout, "%s: \t aliased to ", short2str(*v));
E 32
I 32
	    (void) fprintf(cshout, "%s: \t aliased to ", vis_str(*v));
E 32
	    blkpr(cshout, vp->vec);
	    (void) fputc('\n', cshout);
	}
	else {
	    lex[1].word = *v;
	    tellmewhat(lex);
	}
    }
}

static void
tellmewhat(lex)
    struct wordent *lex;
{
    register int i;
    register struct biltins *bptr;
    register struct wordent *sp = lex->next;
    bool    aliased = 0;
D 36
    Char   *s0, *s1, *s2;
E 36
I 36
    Char   *s0, *s1, *s2, *cmd;
E 36
    Char    qc;

    if (adrof1(sp->word, &aliases)) {
	alias(lex);
	sp = lex->next;
	aliased = 1;
    }

    s0 = sp->word;		/* to get the memory freeing right... */

    /* handle quoted alias hack */
    if ((*(sp->word) & (QUOTE | TRIM)) == QUOTE)
	(sp->word)++;

    /* do quoting, if it hasn't been done */
    s1 = s2 = sp->word;
    while (*s2)
	switch (*s2) {
	case '\'':
	case '"':
	    qc = *s2++;
	    while (*s2 && *s2 != qc)
		*s1++ = *s2++ | QUOTE;
	    if (*s2)
		s2++;
	    break;
	case '\\':
	    if (*++s2)
		*s1++ = *s2++ | QUOTE;
	    break;
	default:
	    *s1++ = *s2++;
	}
    *s1 = '\0';

    for (bptr = bfunc; bptr < &bfunc[nbfunc]; bptr++) {
	if (eq(sp->word, str2short(bptr->bname))) {
	    if (aliased)
		prlex(cshout, lex);
	    (void) fprintf(cshout, "%s: shell built-in command.\n", 
D 32
			   short2str(sp->word));
E 32
I 32
			   vis_str(sp->word));
E 32
	    sp->word = s0;	/* we save and then restore this */
	    return;
	}
    }

I 36
    sp->word = cmd = globone(sp->word, G_IGNORE);

E 36
D 33
    if (i = iscommand(strip(sp->word))) {
E 33
I 33
    if ((i = iscommand(strip(sp->word))) != 0) {
E 33
	register Char **pv;
	register struct varent *v;
	bool    slash = any(short2str(sp->word), '/');

	v = adrof(STRpath);
	if (v == 0 || v->vec[0] == 0 || slash)
	    pv = justabs;
	else
	    pv = v->vec;

	while (--i)
	    pv++;
	if (pv[0][0] == 0 || eq(pv[0], STRdot)) {
D 36
	    sp->word = Strspl(STRdotsl, sp->word);
	    prlex(cshout, lex);
	    xfree((ptr_t) sp->word);
E 36
I 36
	    if (!slash) {
		sp->word = Strspl(STRdotsl, sp->word);
		prlex(cshout, lex);
		xfree((ptr_t) sp->word);
	    }
	    else
		prlex(cshout, lex);
E 36
	    sp->word = s0;	/* we save and then restore this */
I 36
	    xfree((ptr_t) cmd);
E 36
	    return;
	}
	s1 = Strspl(*pv, STRslash);
	sp->word = Strspl(s1, sp->word);
	xfree((ptr_t) s1);
	prlex(cshout, lex);
	xfree((ptr_t) sp->word);
    }
    else {
	if (aliased)
	    prlex(cshout, lex);
D 32
	(void) fprintf(csherr, "%s: Command not found.\n", short2str(sp->word));
E 32
I 32
	(void) fprintf(csherr, "%s: Command not found.\n", vis_str(sp->word));
E 32
    }
    sp->word = s0;		/* we save and then restore this */
I 36
    xfree((ptr_t) cmd);
E 36
E 30
E 23
E 10
}
E 1
