h26683
s 00008/00009/01334
d D 8.4 95/04/29 13:09:04 christos 69 68
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00038/00021/01305
d D 8.3 95/03/22 14:12:40 christos 68 67
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00032/00000/01294
d D 8.2 93/10/12 20:42:26 christos 67 66
c Kill foreground process group upon exit in phup()
e
s 00005/00005/01289
d D 8.1 93/05/31 16:41:29 bostic 66 65
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/01285
d D 5.38 93/05/22 19:06:18 christos 65 64
c Fixed gcc -Wall warnings
e
s 00013/00002/01281
d D 5.37 92/07/19 11:46:23 marc 64 63
c check in for Marc by TK
e
s 00008/00002/01275
d D 5.36 92/05/06 16:29:59 christos 63 62
c check PATH for relative pathnames when running as root (should probably only check for "." - marc)
e
s 00007/00002/01270
d D 5.35 92/03/02 00:13:12 christos 62 61
c Fixed and documented $histfile
e
s 00031/00012/01241
d D 5.34 92/02/05 16:30:05 christos 61 60
c Use vis(3) to print unprintable characters
e
s 00020/00002/01233
d D 5.33 91/11/06 16:09:26 christos 60 59
c Added support for displaying non-printable characters
e
s 00003/00000/01232
d D 5.32 91/11/04 18:21:55 christos 59 58
c Onintr would reset SIGINT if found in /etc/csh.{cshrc,login}
e
s 00015/00014/01217
d D 5.31 91/10/28 21:27:49 leres 58 57
c Fix gcc "bodyless for/while" warnings.
e
s 00001/00001/01230
d D 5.30 91/10/27 16:01:10 christos 57 56
c Loops were broken again. (Michael Schroeder's fix)
e
s 00001/00001/01230
d D 5.29 91/08/30 21:23:38 christos 56 55
c Bugfix for loops in aliases.
e
s 00001/00001/01230
d D 5.28 91/07/22 11:46:41 christos 55 54
c comment typos
e
s 00121/00048/01110
d D 5.27 91/07/19 17:30:22 christos 54 53
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/01152
d D 5.26 91/06/08 17:08:34 christos 53 52
c More prototype fixes, Removed TERMIOS define
e
s 00016/00006/01136
d D 5.25 91/06/08 12:20:07 bostic 52 51
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00026/00025/01116
d D 5.24 91/06/07 20:57:09 christos 51 50
c static function prototypes
e
s 00010/00004/01131
d D 5.23 91/06/07 11:13:13 bostic 50 49
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00000/00008/01135
d D 5.22 91/06/05 16:33:14 christos 49 48
c Removed -DTELL V6 compatibility flag
e
s 00898/00709/00245
d D 5.21 91/06/04 13:31:08 bostic 48 47
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00013/00006/00941
d D 5.20 91/04/04 18:17:30 bostic 47 46
c new copyright; att/bsd/shared
e
s 00007/00007/00940
d D 5.19 91/04/01 17:37:06 bostic 46 45
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00002/00002/00945
d D 5.18 91/03/14 12:26:00 bostic 45 44
c copy -> bcopy (more than vax and tahoe now)
e
s 00002/00001/00945
d D 5.17 91/02/25 08:11:49 bostic 44 43
c ANSI fixes
e
s 00003/00001/00943
d D 5.16 91/02/25 07:21:56 bostic 43 42
c ANSI fixess
e
s 00013/00013/00931
d D 5.15 90/11/09 15:50:07 bostic 42 41
c remove vestiges of AT&T shell
e
s 00001/00001/00943
d D 5.14 90/06/30 16:09:29 marc 41 40
c set proc in pgrp before setting terminal
e
s 00003/00001/00941
d D 5.13 89/09/24 16:49:12 bostic 40 39
c POSIX signals
e
s 00000/00018/00942
d D 5.12 89/08/14 18:14:15 karels 39 38
c we've only got one tty discipline now.
e
s 00001/00001/00959
d D 5.11 89/05/08 12:58:09 bostic 38 37
c file system reorg and pathnames.h
e
s 00001/00002/00959
d D 5.10 89/04/02 11:57:52 bostic 37 36
c rest of pathnames
e
s 00001/00001/00960
d D 5.9 89/03/05 22:01:13 bostic 36 35
c add search path names
e
s 00019/00001/00942
d D 5.8 89/02/15 11:06:31 bostic 35 34
c use pathname include files; remove IIASA commands; remove newgrp
c command; add globall .cshrc, .login, and .logout files; minor cleanups
e
s 00009/00009/00934
d D 5.7 88/12/30 12:09:57 bostic 34 32
c add -m flag for su
e
s 00011/00011/00932
d R 5.7 88/10/09 19:59:12 bostic 33 32
c add -m flag for su, remove INGRES hack
e
s 00001/00001/00942
d D 5.6 88/05/19 15:38:34 bostic 32 31
c install C version of _doprnt
e
s 00004/00000/00939
d D 5.5 88/01/20 11:55:40 bostic 31 30
c Bug involving csh and the "source" command; 4.3BSD/bin/115
e
s 00005/00004/00934
d D 5.4 87/06/25 09:15:07 bostic 30 29
c csh long/int mismatches; bug report 4.3BSD/bin/45
e
s 00003/00000/00935
d D 5.3 86/03/29 07:16:36 lepreau 29 28
c lint
e
s 00003/00003/00932
d D 5.2 85/06/06 13:10:57 edward 28 27
c cleaning up after bozos
e
s 00008/00002/00927
d D 5.1 85/06/04 10:54:40 dist 27 26
c Add copyright
e
s 00001/00001/00928
d D 4.23 85/03/24 17:09:33 edward 26 25
c check for set group id as well as setuid
e
s 00001/00001/00928
d D 4.22 85/03/19 17:54:38 mckusick 25 24
c load history after sourcing .login file in case .login sets history variable
e
s 00001/00003/00928
d D 4.21 85/01/16 10:29:03 edward 24 23
c can't use environ SHELL as variable shell
e
s 00072/00087/00859
d D 4.20 84/12/13 14:41:53 edward 23 22
c performance
e
s 00013/00007/00933
d D 4.19 84/09/07 15:25:00 ralph 22 21
c added -b flag to force next arg as shell input file for setuid scripts.
e
s 00023/00027/00917
d D 4.18 84/08/31 09:30:33 ralph 21 20
c use new signal calls instead of compatibility routines.
e
s 00006/00002/00938
d D 4.17 84/07/06 22:42:12 sam 20 19
c fix up profiling; correct last hack
e
s 00020/00020/00920
d D 4.16 84/07/06 21:13:45 sam 19 18
c restore prior formatting
e
s 00001/00001/00939
d D 4.15 84/06/06 16:51:07 layer 18 17
c create .history with mode 666 not 777 (should use umask, too, but
c it doesn't)
e
s 00001/00001/00939
d D 4.14 83/11/02 14:52:35 layer 17 16
c is called with -c, then don't print the prompt
e
s 00023/00015/00917
d D 4.13 83/11/02 13:45:33 layer 16 14
c move the prompt printing stuff to a function
c (for the filename completion stuff)
e
s 00001/00001/00931
d R 4.13 83/06/27 22:01:11 sam 15 14
c move loadhist down so setting history in .login works
e
s 00015/00015/00917
d D 4.12 83/06/11 16:48:49 sam 14 13
c different approach, try signal compatibility package
e
s 00018/00017/00914
d D 4.11 83/06/10 23:58:43 sam 13 12
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00001/00001/00930
d D 4.10 83/02/03 09:12:39 sam 12 11
c use high precision time calls
e
s 00003/00001/00928
d D 4.9 82/06/06 13:06:15 mckusick 11 10
c fix to allow shell scripts to run in background
e
s 00001/00001/00928
d D 4.8 82/03/28 18:24:45 wnj 10 9
c signal handling bug fix
e
s 00015/00011/00914
d D 4.7 82/02/17 14:33:00 mckusic 9 8
c only save history if "savehist" is specified
e
s 00004/00001/00921
d D 4.6 82/02/12 15:28:50 mckusic 8 7
c save history if exceed cpu time or file size limits in shell
e
s 00002/00001/00920
d D 4.5 81/11/22 15:38:06 mckusic 7 6
c fix bug with HIST not being reset correctly
e
s 00055/00016/00866
d D 4.4 81/11/19 21:03:32 mckusic 6 3
c add ``history -h >file'' and ``source -h file'' to 
c implement history save and restore.
e
s 00034/00012/00870
d R 4.4 81/08/21 00:36:03 mckusic 5 3
c put in history save and restore
e
s 00033/00012/00870
d R 4.4 81/08/20 23:47:32 mckusic 4 3
c put in history save and restore
e
s 00024/00004/00858
d D 4.3 81/08/18 17:00:18 mckusic 3 2
c save history in ~/.history at logout and restore at login
e
s 00007/00001/00855
d D 4.2 81/03/11 18:51:44 wnj 2 1
c minor bug fixes
e
s 00856/00000/00000
d D 4.1 80/10/09 12:40:21 bill 1 0
c date and time created 80/10/09 12:40:21 by bill
e
u
U
t
T
I 27
D 47
/*
 * Copyright (c) 1980 Regents of the University of California.
D 28
 * All rights reserved.  The Berkeley software License Agreement
E 28
I 28
 * All rights reserved.  The Berkeley Software License Agreement
E 28
 * specifies the terms and conditions for redistribution.
E 47
I 47
/*-
D 66
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 66
I 66
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 66
 *
 * %sccs.include.redist.c%
E 47
 */

E 27
I 1
D 23
static	char *sccsid = "%Z%%M% %I% %G%";
E 23
I 23
#ifndef lint
D 27
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 27
I 27
D 28
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 28
I 28
D 47
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 47
I 47
D 66
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 66
I 66
static char copyright[] =
"%Z% Copyright (c) 1980, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 66
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 47
E 28
E 27
E 23

I 52
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
I 60
#include <vis.h>
E 60
I 53
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 53
E 52
D 50
#include "sh.h"
D 48
#include <sys/ioctl.h>
I 35
#include <sys/file.h>
D 37
#include <syspaths.h>
#include <pathnames.h>
E 37
I 37
#include "pathnames.h"
E 48
I 48
#include "sh.dir.h"
E 50
I 50
#include "csh.h"
I 67
#include "proc.h"
E 67
D 52
#include "dir.h"
E 52
#include "extern.h"
I 52
#include "pathnames.h"
E 52
E 50
E 48
E 37

I 48
extern bool MapsAreInited;
extern bool NLSMapsAreInited;

E 48
E 35
/*
 * C Shell
 *
 * Bill Joy, UC Berkeley, California, USA
 * October 1978, May 1980
 *
 * Jim Kulp, IIASA, Laxenburg, Austria
 * April 1980
I 50
 *
 * Christos Zoulas, Cornell University
 * June, 1991
E 50
 */

D 36
char	*pathlist[] =	{ ".", "/usr/ucb", "/bin", "/usr/bin", 0 };
E 36
I 36
D 38
char	*pathlist[] =	{ ".", _PATH_UCB, _PATH_BIN, _PATH_USRBIN, 0 };
E 38
I 38
D 48
char	*pathlist[] =	{ ".", _PATH_BIN, _PATH_USRBIN, 0 };
E 38
E 36
I 3
D 6
char	*dumphist[] =	{ "history", "-c", "+1000" };
E 6
I 6
D 9
char	*dumphist[] =	{ "history", "-h", 0 };
E 9
I 9
char	*dumphist[] =	{ "history", "-h", 0, 0 };
E 9
char	*loadhist[] =	{ "source", "-h", "~/.history", 0 };
E 6
E 3
char	HIST = '!';
char	HISTSUB = '^';
I 34
bool	mflag;
E 34
bool	nofile;
bool	reenter;
bool	nverbose;
bool	nexececho;
bool	quitit;
bool	fast;
I 22
bool	batch;
E 22
bool	prompt = 1;
I 3
bool	enterhist = 0;
E 48
I 48
Char   *dumphist[] = {STRhistory, STRmh, 0, 0};
D 62
Char   *loadhist[] = {STRsource, STRmh, STRhistfile, 0};
E 62
I 62
Char   *loadhist[] = {STRsource, STRmh, STRtildothist, 0};
E 62
E 48
E 3

I 29
D 48
extern	gid_t getegid(), getgid();
extern	uid_t geteuid(), getuid();
E 48
I 48
int     nofile = 0;
bool    reenter = 0;
bool    nverbose = 0;
bool    nexececho = 0;
bool    quitit = 0;
bool    fast = 0;
bool    batch = 0;
bool    mflag = 0;
bool    prompt = 1;
bool    enterhist = 0;
bool    tellwhat = 0;
E 48

I 43
D 44
static void srcunit();
E 44
I 44
D 48
void pintr(), pchild(), srcunit();
E 48
I 48
extern char **environ;
E 48
E 44

I 54
static int	readf __P((void *, char *, int));
static fpos_t	seekf __P((void *, fpos_t, int));
static int	writef __P((void *, const char *, int));
static int	closef __P((void *));
E 54
I 48
D 51
static int srccat();
static int srcfile();
static void phup();
static void srcunit();
static void mailchk();
static Char **defaultpath();
E 51
I 51
static int	srccat __P((Char *, Char *));
static int	srcfile __P((char *, bool, bool));
static void	phup __P((int));
static void	srcunit __P((int, bool, bool));
static void	mailchk __P((void));
static Char   **defaultpath __P((void));
E 51

int
E 48
E 43
E 29
D 42
main(c, av)
	int c;
	char **av;
E 42
I 42
main(argc, argv)
D 48
	int argc;
	char **argv;
E 48
I 48
    int     argc;
    char  **argv;
E 48
E 42
{
D 48
	register char **v, *cp;
	register int f;
I 21
	struct sigvec osv;
E 48
I 48
    register Char *cp;
    register char *tcp;
    register int f;
    register char **tempv;
D 68
    struct sigvec osv;
E 68
I 68
    struct sigaction oact;
    sigset_t sigset;
E 68
E 48
E 21

I 54
    cshin = stdin;
    cshout = stdout;
    csherr = stderr;
E 54
D 48
	settimes();			/* Immed. estab. timing base */
D 42
	v = av;
E 42
I 42
	v = argv;
E 42
	if (eq(v[0], "a.out"))		/* A.out's are quittable */
		quitit = 1;
	uid = getuid();
D 21
	loginsh = **v == '-';
E 21
I 21
D 42
	loginsh = **v == '-' && c == 1;
E 42
I 42
	loginsh = **v == '-' && argc == 1;
E 42
E 21
	if (loginsh)
D 23
		time(&chktim);
E 23
I 23
		(void) time(&chktim);
E 48
E 23

D 48
	/*
	 * Move the descriptors to safe places.
	 * The variable didfds is 0 while we have only FSH* to work with.
	 * When didfds is true, we have 0,1,2 and prefer to use these.
	 */
	initdesc();
E 48
I 48
    settimes();			/* Immed. estab. timing base */
E 48

D 48
	/*
	 * Initialize the shell variables.
	 * ARGV and PROMPT are initialized later.
	 * STATUS is also munged in several places.
	 * CHILD is munged when forking/waiting
	 */
E 48
I 48
    /*
     * Initialize non constant strings
     */
#ifdef _PATH_BSHELL
    STR_BSHELL = SAVE(_PATH_BSHELL);
#endif
#ifdef _PATH_CSHELL
    STR_SHELLPATH = SAVE(_PATH_CSHELL);
#endif
    STR_environ = blk2short(environ);
    environ = short2blk(STR_environ);	/* So that we can free it */
    STR_WORD_CHARS = SAVE(WORD_CHARS);
E 48

D 48
	set("status", "0");
	dinit(cp = getenv("HOME"));	/* dinit thinks that HOME == cwd in a
					 * login shell */
	if (cp == NOSTR)
		fast++;			/* No home -> can't read scripts */
	else
		set("home", savestr(cp));
	/*
	 * Grab other useful things from the environment.
	 * Should we grab everything??
	 */
	if ((cp = getenv("USER")) != NOSTR)
		set("user", savestr(cp));
	if ((cp = getenv("TERM")) != NOSTR)
		set("term", savestr(cp));
	/*
	 * Re-initialize path if set in environment
	 */
	if ((cp = getenv("PATH")) == NOSTR)
		set1("path", saveblk(pathlist), &shvhed);
D 23
	else {
		register unsigned i = 0;
		register char *dp;
		register char **pv;
E 23
I 23
	else
		importpath(cp);
D 24
	if ((cp = getenv("SHELL")) == NOSTR)
		cp = SHELLPATH;
	set("shell", savestr(cp));
E 24
I 24
D 35
	set("shell", SHELLPATH);
E 35
I 35
	set("shell", _PATH_CSHELL);
E 48
I 48
    HIST = '!';
    HISTSUB = '^';
    word_chars = STR_WORD_CHARS;
E 48
E 35
E 24
E 23

D 23
		for (dp = cp; *dp; dp++)
			if (*dp == ':')
				i++;
		pv = (char **)calloc(i+2, sizeof (char **));
		for (dp = cp, i = 0; ;)
			if (*dp == ':') {
				*dp = 0;
				pv[i++] = savestr(*cp ? cp : ".");
				*dp++ = ':';
				cp = dp;
			} else if (*dp++ == 0) {
				pv[i++] = savestr(*cp ? cp : ".");
				break;
			}
		pv[i] = 0;
		set1("path", pv, &shvhed);
	}
	set("shell", SHELLPATH);

E 23
D 48
	doldol = putn(getpid());		/* For $$ */
	shtemp = strspl("/tmp/sh", doldol);	/* For << */
E 48
I 48
    tempv = argv;
    if (eq(str2short(tempv[0]), STRaout))	/* A.out's are quittable */
	quitit = 1;
    uid = getuid();
    gid = getgid();
I 63
    euid = geteuid();
    egid = getegid();
E 63
    /*
     * We are a login shell if: 1. we were invoked as -<something> and we had
     * no arguments 2. or we were invoked only with the -l flag
     */
    loginsh = (**tempv == '-' && argc == 1) ||
	(argc == 2 && tempv[1][0] == '-' && tempv[1][1] == 'l' &&
	 tempv[1][2] == '\0');
E 48

I 48
    if (loginsh && **tempv != '-') {
E 48
	/*
D 48
	 * Record the interrupt states from the parent process.
	 * If the parent is non-interruptible our hand must be forced
	 * or we (and our children) won't be either.
	 * Our children inherit termination from our parent.
	 * We catch it only if we are the login shell.
E 48
I 48
	 * Mangle the argv space
E 48
	 */
D 21
	parintr = signal(SIGINT, SIG_IGN);	/* parents interruptibility */
D 13
	sigset(SIGINT, parintr);			/* ... restore */
E 13
I 13
D 14
	signal(SIGINT, parintr);			/* ... restore */
E 14
I 14
	sigset(SIGINT, parintr);			/* ... restore */
E 14
E 13
	parterm = signal(SIGTERM, SIG_IGN);	/* parents terminability */
	signal(SIGTERM, parterm);			/* ... restore */
E 21
I 21
D 23
	sigvec(SIGINT, 0, &osv);		/* parents interruptibility */
E 23
I 23
D 48
		/* parents interruptibility */
	(void) sigvec(SIGINT, (struct sigvec *)0, &osv);
E 23
	parintr = osv.sv_handler;
D 23
	sigvec(SIGTERM, 0, &osv);		/* parents terminability */
E 23
I 23
		/* parents terminability */
	(void) sigvec(SIGTERM, (struct sigvec *)0, &osv);
E 23
	parterm = osv.sv_handler;
E 21
I 6
D 8
	if (loginsh)
E 8
I 8
	if (loginsh) {
I 40
		sig_t phup;
E 48
I 48
	tempv[1][0] = '\0';
	tempv[1][1] = '\0';
	tempv[1] = NULL;
D 58
	for (tcp = *tempv; *tcp++;);
E 58
I 58
	for (tcp = *tempv; *tcp++;)
	    continue;
E 58
	for (tcp--; tcp >= *tempv; tcp--)
	    tcp[1] = tcp[0];
	*++tcp = '-';
	argc--;
    }
    if (loginsh)
	(void) time(&chktim);
E 48

E 40
E 8
D 23
		signal(SIGHUP, phup);		/* exit processing on HUP */
I 8
		signal(SIGXCPU, phup);		/* ...and on XCPU */
		signal(SIGXFSZ, phup);		/* ...and on XFSZ */
E 23
I 23
D 48
		(void) signal(SIGHUP, phup);	/* exit processing on HUP */
		(void) signal(SIGXCPU, phup);	/* ...and on XCPU */
		(void) signal(SIGXFSZ, phup);	/* ...and on XFSZ */
E 23
	}
E 48
I 48
    AsciiOnly = 1;
#ifdef NLS
    (void) setlocale(LC_ALL, "");
    {
	int     k;
E 48
E 8
E 6

D 48
	/*
	 * Process the arguments.
	 *
	 * Note that processing of -v/-x is actually delayed till after
	 * script processing.
D 22
	 *
	 * We set the first character of our name to be '-' if we are
	 * a shell running interruptible commands.  Many programs which
	 * examine ps'es use this to filter such shells out.
E 22
	 */
D 42
	c--, v++;
D 22
	while (c > 0 && (cp = v[0])[0] == '-') {
I 21
		cp++;
E 22
I 22
	while (c > 0 && (cp = v[0])[0] == '-' && *++cp != '\0' && !batch) {
E 42
I 42
	argc--, v++;
	while (argc > 0 && (cp = v[0])[0] == '-' && *++cp != '\0' && !batch) {
E 42
E 22
E 21
		do switch (*cp++) {
E 48
I 48
D 58
	for (k = 0200; k <= 0377 && !Isprint(k); k++);
E 58
I 58
	for (k = 0200; k <= 0377 && !Isprint(k); k++)
	    continue;
E 58
	AsciiOnly = k > 0377;
    }
#else
    AsciiOnly = getenv("LANG") == NULL && getenv("LC_CTYPE") == NULL;
#endif				/* NLS */
E 48

I 22
D 48
		case 'b':		/* -b	Next arg is input file */
			batch++;
			break;
E 48
I 48
    /*
     * Move the descriptors to safe places. The variable didfds is 0 while we
     * have only FSH* to work with. When didfds is true, we have 0,1,2 and
     * prefer to use these.
     */
    initdesc();
I 64
    /*
     * XXX: This is to keep programs that use stdio happy.
     *	    what we really want is freunopen() ....
     *	    Closing cshin cshout and csherr (which are really stdin stdout
     *	    and stderr at this point and then reopening them in the same order
     *	    gives us again stdin == cshin stdout == cshout and stderr == csherr.
     *	    If that was not the case builtins like printf that use stdio
     *	    would break. But in any case we could fix that with memcpy and
     *	    a bit of pointer manipulation...
     *	    Fortunately this is not needed under the current implementation
     *	    of stdio.
     */
E 64
I 54
    (void) fclose(cshin);
    (void) fclose(cshout);
    (void) fclose(csherr);
    if (!(cshin  = funopen((void *) &SHIN,  readf, writef, seekf, closef)))
	exit(1);
    if (!(cshout = funopen((void *) &SHOUT, readf, writef, seekf, closef)))
	exit(1);
    if (!(csherr = funopen((void *) &SHERR, readf, writef, seekf, closef)))
	exit(1);
    (void) setvbuf(cshin,  NULL, _IOLBF, 0);
    (void) setvbuf(cshout, NULL, _IOLBF, 0);
    (void) setvbuf(csherr, NULL, _IOLBF, 0);
E 54
E 48

I 54
D 64

E 64
E 54
E 22
D 21
		case 0:			/* -	Interruptible, no prompt */
			prompt = 0;
			setintr++;
			nofile++;
			break;

E 21
D 48
		case 'c':		/* -c	Command input from arg */
D 42
			if (c == 1)
E 42
I 42
			if (argc == 1)
E 42
				exit(0);
D 42
			c--, v++;
E 42
I 42
			argc--, v++;
E 42
			arginp = v[0];
			prompt = 0;
			nofile++;
			break;
E 48
I 48
    /*
     * Initialize the shell variables. ARGV and PROMPT are initialized later.
     * STATUS is also munged in several places. CHILD is munged when
     * forking/waiting
     */
    set(STRstatus, Strsave(STR0));
E 48

D 48
		case 'e':		/* -e	Exit on any error */
			exiterr++;
			break;
E 48
I 48
D 51
    if ((tcp = getenv("HOME")) != (char *) 0)
E 51
I 51
    if ((tcp = getenv("HOME")) != NULL)
E 51
	cp = SAVE(tcp);
    else
	cp = NULL;
E 48

D 48
		case 'f':		/* -f	Fast start */
			fast++;
			break;
E 48
I 48
    if (cp == NULL)
	fast = 1;		/* No home -> can't read scripts */
    else
	set(STRhome, cp);
    dinit(cp);			/* dinit thinks that HOME == cwd in a login
				 * shell */
    /*
     * Grab other useful things from the environment. Should we grab
     * everything??
     */
D 51
    if ((tcp = getenv("LOGNAME")) != (char *) 0 ||
	(tcp = getenv("USER")) != (char *) 0)
E 51
I 51
    if ((tcp = getenv("LOGNAME")) != NULL ||
	(tcp = getenv("USER")) != NULL)
E 51
	set(STRuser, SAVE(tcp));
D 51
    if ((tcp = getenv("TERM")) != (char *) 0)
E 51
I 51
    if ((tcp = getenv("TERM")) != NULL)
E 51
	set(STRterm, SAVE(tcp));
E 48

D 48
		case 'i':		/* -i	Interactive, even if !intty */
			intact++;
			nofile++;
			break;
E 48
I 48
    /*
     * Re-initialize path if set in environment
     */
D 51
    if ((tcp = getenv("PATH")) == (char *) 0)
E 51
I 51
    if ((tcp = getenv("PATH")) == NULL)
E 51
	set1(STRpath, defaultpath(), &shvhed);
    else
	importpath(SAVE(tcp));
E 48

I 34
D 48
		case 'm':		/* -m	read .cshrc (from su) */
			mflag++;
			break;
E 48
I 48
    set(STRshell, Strsave(STR_SHELLPATH));
E 48

E 34
D 48
		case 'n':		/* -n	Don't execute */
			noexec++;
			break;
E 48
I 48
    doldol = putn((int) getpid());	/* For $$ */
    shtemp = Strspl(STRtmpsh, doldol);	/* For << */
E 48

D 48
		case 'q':		/* -q	(Undoc'd) ... die on quit */
			quitit = 1;
			break;
E 48
I 48
    /*
     * Record the interrupt states from the parent process. If the parent is
     * non-interruptible our hand must be forced or we (and our children) won't
     * be either. Our children inherit termination from our parent. We catch it
     * only if we are the login shell.
     */
    /* parents interruptibility */
D 51
    (void) sigvec(SIGINT, (struct sigvec *) 0, &osv);
E 51
I 51
D 68
    (void) sigvec(SIGINT, NULL, &osv);
E 51
    parintr = (void (*) ()) osv.sv_handler;
D 51
    (void) sigvec(SIGTERM, (struct sigvec *) 0, &osv);
E 51
I 51
    (void) sigvec(SIGTERM, NULL, &osv);
E 51
    parterm = (void (*) ()) osv.sv_handler;
E 68
I 68
    (void) sigaction(SIGINT, NULL, &oact);
    parintr = oact.sa_handler;
    (void) sigaction(SIGTERM, NULL, &oact);
    parterm = oact.sa_handler;
E 68
E 48

D 48
		case 's':		/* -s	Read from std input */
			nofile++;
			break;
E 48
I 48
D 69
    if (loginsh) {
	(void) signal(SIGHUP, phup);	/* exit processing on HUP */
	(void) signal(SIGXCPU, phup);	/* ...and on XCPU */
	(void) signal(SIGXFSZ, phup);	/* ...and on XFSZ */
    }
E 69
I 69
    (void) signal(SIGHUP, phup);	/* exit processing on HUP */
    (void) signal(SIGXCPU, phup);	/* ...and on XCPU */
    (void) signal(SIGXFSZ, phup);	/* ...and on XFSZ */
E 69
E 48

D 48
		case 't':		/* -t	Read one line from input */
			onelflg = 2;
			prompt = 0;
			nofile++;
			break;
E 48
I 48
    /*
     * Process the arguments.
D 58
     * 
E 58
I 58
     *
E 58
     * Note that processing of -v/-x is actually delayed till after script
     * processing.
D 58
     * 
E 58
I 58
     *
E 58
D 54
     * We set the first character of our name to be '-' if we are a shell running
     * interruptible commands.  Many programs which examine ps'es use this to
     * filter such shells out.
E 54
I 54
     * We set the first character of our name to be '-' if we are a shell
D 58
     * running interruptible commands.  Many programs which examine ps'es 
E 58
I 58
     * running interruptible commands.  Many programs which examine ps'es
E 58
     * use this to filter such shells out.
E 54
     */
    argc--, tempv++;
    while (argc > 0 && (tcp = tempv[0])[0] == '-' && *++tcp != '\0' && !batch) {
	do
	    switch (*tcp++) {
E 48

D 48
		case 'v':		/* -v	Echo hist expanded input */
			nverbose = 1;			/* ... later */
			break;
E 48
I 48
	    case 0:		/* -	Interruptible, no prompt */
		prompt = 0;
		setintr = 1;
		nofile = 1;
		break;
E 48

D 48
		case 'x':		/* -x	Echo just before execution */
			nexececho = 1;			/* ... later */
			break;
E 48
I 48
	    case 'b':		/* -b	Next arg is input file */
		batch = 1;
		break;
E 48

D 48
		case 'V':		/* -V	Echo hist expanded input */
			setNS("verbose");		/* NOW! */
			break;
E 48
I 48
	    case 'c':		/* -c	Command input from arg */
		if (argc == 1)
		    xexit(0);
		argc--, tempv++;
		arginp = SAVE(tempv[0]);
		prompt = 0;
		nofile = 1;
		break;
E 48

D 48
		case 'X':		/* -X	Echo just before execution */
			setNS("echo");			/* NOW! */
			break;
E 48
I 48
	    case 'e':		/* -e	Exit on any error */
		exiterr = 1;
		break;
E 48

D 48
		} while (*cp);
D 42
		v++, c--;
E 42
I 42
		v++, argc--;
E 42
	}
E 48
I 48
	    case 'f':		/* -f	Fast start */
		fast = 1;
		break;
E 48
I 22
D 23
argsdone:
E 23
E 22

D 48
	if (quitit)			/* With all due haste, for debugging */
D 23
		signal(SIGQUIT, SIG_DFL);
E 23
I 23
		(void) signal(SIGQUIT, SIG_DFL);
E 48
I 48
	    case 'i':		/* -i	Interactive, even if !intty */
		intact = 1;
		nofile = 1;
		break;
E 48
E 23

D 48
	/*
D 22
	 * Unless prevented by -, -c, -i, -s, or -t, if there
E 22
I 22
	 * Unless prevented by -c, -i, -s, or -t, if there
E 22
	 * are remaining arguments the first of them is the name
	 * of a shell file from which to read commands.
	 */
D 42
	if (nofile == 0 && c > 0) {
E 42
I 42
	if (nofile == 0 && argc > 0) {
E 42
		nofile = open(v[0], 0);
		if (nofile < 0) {
			child++;		/* So this ... */
			Perror(v[0]);		/* ... doesn't return */
		}
		file = v[0];
		SHIN = dmove(nofile, FSHIN);	/* Replace FSHIN */
I 23
		(void) ioctl(SHIN, FIOCLEX, (char *)0);
E 48
I 48
	    case 'm':		/* -m	read .cshrc (from su) */
		mflag = 1;
		break;

	    case 'n':		/* -n	Don't execute */
		noexec = 1;
		break;

	    case 'q':		/* -q	(Undoc'd) ... die on quit */
		quitit = 1;
		break;

	    case 's':		/* -s	Read from std input */
		nofile = 1;
		break;

	    case 't':		/* -t	Read one line from input */
		onelflg = 2;
E 48
E 23
		prompt = 0;
D 42
		c--, v++;
E 42
I 42
D 48
		argc--, v++;
E 48
I 48
		nofile = 1;
		break;

	    case 'v':		/* -v	Echo hist expanded input */
		nverbose = 1;	/* ... later */
		break;

	    case 'x':		/* -x	Echo just before execution */
		nexececho = 1;	/* ... later */
		break;

	    case 'V':		/* -V	Echo hist expanded input */
		setNS(STRverbose);	/* NOW! */
		break;

	    case 'X':		/* -X	Echo just before execution */
		setNS(STRecho);	/* NOW! */
		break;

	} while (*tcp);
	tempv++, argc--;
    }

    if (quitit)			/* With all due haste, for debugging */
	(void) signal(SIGQUIT, SIG_DFL);

    /*
     * Unless prevented by -, -c, -i, -s, or -t, if there are remaining
     * arguments the first of them is the name of a shell file from which to
     * read commands.
     */
    if (nofile == 0 && argc > 0) {
	nofile = open(tempv[0], O_RDONLY);
	if (nofile < 0) {
	    child = 1;		/* So this doesn't return */
	    stderror(ERR_SYSTEM, tempv[0], strerror(errno));
E 48
E 42
I 22
	}
D 23
	if (uid != geteuid() && !batch) {
E 23
I 23
D 26
	if (!batch && uid != geteuid()) {
E 26
I 26
D 48
	if (!batch && (uid != geteuid() || getgid() != getegid())) {
E 26
E 23
		errno = EACCES;
		child++;			/* So this ... */
		Perror("csh");			/* ... doesn't return */
E 22
	}
	/*
	 * Consider input a tty if it really is or we are interactive.
E 48
I 48
	ffile = SAVE(tempv[0]);
D 58
	/* 
E 58
I 58
	/*
E 58
	 * Replace FSHIN. Handle /dev/std{in,out,err} specially
	 * since once they are closed we cannot open them again.
	 * In that case we use our own saved descriptors
E 48
	 */
D 48
	intty = intact || isatty(SHIN);
	/*
	 * Decide whether we should play with signals or not.
	 * If we are explicitly told (via -i, or -) or we are a login
	 * shell (arg0 starts with -) or the input and output are both
	 * the ttys("csh", or "csh</dev/ttyx>/dev/ttyx")
	 * Note that in only the login shell is it likely that parent
	 * may have set signals to be ignored
	 */
D 10
	if (loginsh || intact || intty && isatty(SHOUT))
E 10
I 10
D 11
	if (loginsh || intact || intty && isatty(SHOUT) || parintr == SIG_DFL)
E 11
I 11
	if (loginsh || intact || intty && isatty(SHOUT))
E 11
E 10
		setintr = 1;
E 48
I 48
D 58
	if ((SHIN = dmove(nofile, FSHIN)) < 0) 
E 58
I 58
	if ((SHIN = dmove(nofile, FSHIN)) < 0)
E 58
	    switch(nofile) {
	    case 0:
		SHIN = FSHIN;
		break;
	    case 1:
		SHIN = FSHOUT;
		break;
	    case 2:
D 54
		SHIN = FSHDIAG;
E 54
I 54
		SHIN = FSHERR;
E 54
		break;
	    default:
		stderror(ERR_SYSTEM, tempv[0], strerror(errno));
		break;
	    }
D 51
	(void) ioctl(SHIN, FIOCLEX, (ioctl_t) 0);
E 51
I 51
	(void) ioctl(SHIN, FIOCLEX, NULL);
E 51
	prompt = 0;
	 /* argc not used any more */ tempv++;
    }
I 54

E 54
    intty = isatty(SHIN);
    intty |= intact;
    if (intty || (intact && isatty(SHOUT))) {
D 63
	if (!batch && (uid != geteuid() || gid != getegid())) {
E 63
I 63
	if (!batch && (uid != euid || gid != egid)) {
E 63
	    errno = EACCES;
	    child = 1;		/* So this doesn't return */
	    stderror(ERR_SYSTEM, "csh", strerror(errno));
	}
    }
    /*
     * Decide whether we should play with signals or not. If we are explicitly
     * told (via -i, or -) or we are a login shell (arg0 starts with -) or the
     * input and output are both the ttys("csh", or "csh</dev/ttyx>/dev/ttyx")
     * Note that in only the login shell is it likely that parent may have set
     * signals to be ignored
     */
D 65
    if (loginsh || intact || intty && isatty(SHOUT))
E 65
I 65
    if (loginsh || intact || (intty && isatty(SHOUT)))
E 65
	setintr = 1;
E 48
D 49
#ifdef TELL
E 49
D 48
	settell();
E 48
I 48
    settell();
E 48
D 49
#endif
E 49
D 48
	/*
	 * Save the remaining arguments in argv.
	 */
	setq("argv", v, &shvhed);
E 48
I 48
    /*
     * Save the remaining arguments in argv.
     */
    setq(STRargv, blk2short(tempv), &shvhed);
E 48

D 48
	/*
	 * Set up the prompt.
	 */
	if (prompt)
		set("prompt", uid == 0 ? "# " : "% ");
E 48
I 48
    /*
     * Set up the prompt.
     */
    if (prompt) {
	set(STRprompt, Strsave(uid == 0 ? STRsymhash : STRsymcent));
	/* that's a meta-questionmark */
	set(STRprompt2, Strsave(STRmquestion));
    }
E 48

D 48
	/*
	 * If we are an interactive shell, then start fiddling
	 * with the signals; this is a tricky game.
	 */
	shpgrp = getpgrp(0);
	opgrp = tpgrp = -1;
D 39
	oldisc = -1;
E 39
	if (setintr) {
D 42
		**av = '-';
E 42
I 42
		**argv = '-';
E 42
		if (!quitit)		/* Wary! */
D 23
			signal(SIGQUIT, SIG_IGN);
D 13
		sigset(SIGINT, pintr);
		sighold(SIGINT);
E 13
I 13
D 14
		sigblock(mask(SIGINT));
		signal(SIGINT, pintr);
E 14
I 14
D 21
		sigset(SIGINT, pintr);
		sighold(SIGINT);
E 21
I 21
		signal(SIGINT, pintr);
		sigblock(sigmask(SIGINT));
E 21
E 14
E 13
		signal(SIGTERM, SIG_IGN);
E 23
I 23
			(void) signal(SIGQUIT, SIG_IGN);
		(void) signal(SIGINT, pintr);
		(void) sigblock(sigmask(SIGINT));
		(void) signal(SIGTERM, SIG_IGN);
E 23
		if (quitit == 0 && arginp == 0) {
D 23
			signal(SIGTSTP, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
E 23
I 23
			(void) signal(SIGTSTP, SIG_IGN);
			(void) signal(SIGTTIN, SIG_IGN);
			(void) signal(SIGTTOU, SIG_IGN);
E 23
			/*
			 * Wait till in foreground, in case someone
			 * stupidly runs
			 *	csh &
			 * dont want to try to grab away the tty.
			 */
			if (isatty(FSHDIAG))
				f = FSHDIAG;
			else if (isatty(FSHOUT))
				f = FSHOUT;
			else if (isatty(OLDSTD))
				f = OLDSTD;
			else
				f = -1;
retry:
D 23
			if (ioctl(f, TIOCGPGRP, &tpgrp) == 0 && tpgrp != -1) {
E 23
I 23
			if (ioctl(f, TIOCGPGRP, (char *)&tpgrp) == 0 &&
			    tpgrp != -1) {
E 23
				int ldisc;
				if (tpgrp != shpgrp) {
D 13
					int old = sigsys(SIGTTIN, SIG_DFL);
E 13
I 13
D 14
					int (*old)() = signal(SIGTTIN, SIG_DFL);
E 14
I 14
D 21
					int (*old)() = sigsys(SIGTTIN, SIG_DFL);
E 21
I 21
D 40
					int (*old)() = signal(SIGTTIN, SIG_DFL);
E 40
I 40
					sig_t old = signal(SIGTTIN, SIG_DFL);
E 40
E 21
E 14
E 13
D 23
					kill(0, SIGTTIN);
D 13
					sigsys(SIGTTIN, old);
E 13
I 13
D 14
					signal(SIGTTIN, old);
E 14
I 14
D 21
					sigsys(SIGTTIN, old);
E 21
I 21
					signal(SIGTTIN, old);
E 23
I 23
					(void) kill(0, SIGTTIN);
					(void) signal(SIGTTIN, old);
E 23
E 21
E 14
E 13
					goto retry;
				}
D 23
				if (ioctl(f, TIOCGETD, &oldisc) != 0) 
E 23
I 23
D 39
				if (ioctl(f, TIOCGETD, (char *)&oldisc) != 0) 
E 23
					goto notty;
				if (oldisc != NTTYDISC) {
D 6
			printf("Switching to new tty driver...\n");
E 6
I 6
#ifdef DEBUG
					printf("Switching to new tty driver...\n");
#endif DEBUG
E 6
					ldisc = NTTYDISC;
D 23
					ioctl(f, TIOCSETD, &ldisc);
E 23
I 23
					(void) ioctl(f, TIOCSETD,
						(char *)&ldisc);
E 23
				} else
					oldisc = -1;
E 39
				opgrp = shpgrp;
				shpgrp = getpid();
				tpgrp = shpgrp;
D 23
				ioctl(f, TIOCSPGRP, &shpgrp);
				setpgrp(0, shpgrp);
				dcopy(f, FSHTTY);
				ioctl(FSHTTY, FIOCLEX, 0);
E 23
I 23
D 41
				(void) ioctl(f, TIOCSPGRP, (char *)&shpgrp);
E 41
				(void) setpgrp(0, shpgrp);
I 41
				(void) ioctl(f, TIOCSPGRP, (char *)&shpgrp);
E 41
				(void) ioctl(dcopy(f, FSHTTY), FIOCLEX,
					(char *)0);
E 23
			} else {
notty:
  printf("Warning: no access to tty; thus no job control in this shell...\n");
				tpgrp = -1;
			}
E 48
I 48
    /*
     * If we are an interactive shell, then start fiddling with the signals;
     * this is a tricky game.
     */
    shpgrp = getpgrp();
    opgrp = tpgrp = -1;
    if (setintr) {
	**argv = '-';
	if (!quitit)		/* Wary! */
	    (void) signal(SIGQUIT, SIG_IGN);
	(void) signal(SIGINT, pintr);
D 68
	(void) sigblock(sigmask(SIGINT));
E 68
I 68
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
E 68
	(void) signal(SIGTERM, SIG_IGN);
	if (quitit == 0 && arginp == 0) {
	    (void) signal(SIGTSTP, SIG_IGN);
	    (void) signal(SIGTTIN, SIG_IGN);
	    (void) signal(SIGTTOU, SIG_IGN);
	    /*
	     * Wait till in foreground, in case someone stupidly runs csh &
	     * dont want to try to grab away the tty.
	     */
D 54
	    if (isatty(FSHDIAG))
		f = FSHDIAG;
E 54
I 54
	    if (isatty(FSHERR))
		f = FSHERR;
E 54
	    else if (isatty(FSHOUT))
		f = FSHOUT;
	    else if (isatty(OLDSTD))
		f = OLDSTD;
	    else
		f = -1;
    retry:
	    if ((tpgrp = tcgetpgrp(f)) != -1) {
		if (tpgrp != shpgrp) {
		    sig_t old = signal(SIGTTIN, SIG_DFL);
		    (void) kill(0, SIGTTIN);
		    (void) signal(SIGTTIN, old);
		    goto retry;
E 48
		}
I 48
		opgrp = shpgrp;
		shpgrp = getpid();
		tpgrp = shpgrp;
		/*
D 58
		 * Setpgid will fail if we are a session leader and 
E 58
I 58
		 * Setpgid will fail if we are a session leader and
E 58
		 * mypid == mypgrp (POSIX 4.3.3)
		 */
		if (opgrp != shpgrp)
		    if (setpgid(0, shpgrp) == -1)
			goto notty;
		/*
		 * We do that after we set our process group, to make sure
		 * that the process group belongs to a process in the same
		 * session as the tty (our process and our group) (POSIX 7.2.4)
		 */
		if (tcsetpgrp(f, shpgrp) == -1)
		    goto notty;
D 51
		(void) ioctl(dcopy(f, FSHTTY), FIOCLEX, (ioctl_t) 0);
E 51
I 51
		(void) ioctl(dcopy(f, FSHTTY), FIOCLEX, NULL);
E 51
	    }
	    if (tpgrp == -1) {
notty:
D 54
		xprintf("Warning: no access to tty (%s).\n", strerror(errno));
		xprintf("Thus no job control in this shell.\n");
E 54
I 54
D 58
		(void) fprintf(csherr, "Warning: no access to tty (%s).\n", 
E 58
I 58
		(void) fprintf(csherr, "Warning: no access to tty (%s).\n",
E 58
			       strerror(errno));
		(void) fprintf(csherr, "Thus no job control in this shell.\n");
E 54
	    }
E 48
	}
I 11
D 48
	if (setintr == 0 && parintr == SIG_DFL)
		setintr++;
E 11
D 13
	sigset(SIGCHLD, pchild);		/* while signals not ready */
E 13
I 13
D 14
	signal(SIGCHLD, pchild);		/* while signals not ready */
E 14
I 14
D 21
	sigset(SIGCHLD, pchild);		/* while signals not ready */
E 21
I 21
D 23
	signal(SIGCHLD, pchild);	/* while signals not ready */
E 23
I 23
	(void) signal(SIGCHLD, pchild);	/* while signals not ready */
E 48
I 48
    }
    if ((setintr == 0) && (parintr == SIG_DFL))
	setintr = 1;
    (void) signal(SIGCHLD, pchild);	/* while signals not ready */
E 48
E 23
E 21
E 14
E 13

D 48
	/*
	 * Set an exit here in case of an interrupt or error reading
	 * the shell start-up scripts.
	 */
D 46
	setexit();
E 46
I 46
	(void)setjmp(reslab);
E 46
	haderr = 0;		/* In case second time through */
	if (!fast && reenter == 0) {
		reenter++;
I 35
		{
		int osetintr, omask;
			osetintr = setintr;
			omask = sigblock(sigmask(SIGINT));
			setintr = 0;
			srcunit(open(_PATH_DOTCSHRC, O_RDONLY), 0, 0);
			if (!fast && !arginp && !onelflg)
				dohash();
			if (loginsh)
				srcunit(open(_PATH_DOTLOGIN, O_RDONLY), 0, 0);
			(void)sigsetmask(omask);
			setintr = osetintr;
		}
E 35
		/* Will have value("home") here because set fast if don't */
		srccat(value("home"), "/.cshrc");
D 23
		if (!fast && !arginp && !onelflg)
E 23
I 23
		if (!fast && !arginp && !onelflg && !havhash)
E 23
			dohash();
I 6
D 25
		dosource(loadhist);
E 25
E 6
		if (loginsh) {
D 3
			int ldisc;
E 3
			srccat(value("home"), "/.login");
I 3
D 6
			enterhist = 1;
			srccat(value("home"), "/.history");
			enterhist = 0;
E 6
E 3
		}
I 25
		dosource(loadhist);
E 48
I 48
    /*
     * Set an exit here in case of an interrupt or error reading the shell
     * start-up scripts.
     */
    reenter = setexit();	/* PWP */
    haderr = 0;			/* In case second time through */
    if (!fast && reenter == 0) {
	/* Will have value(STRhome) here because set fast if don't */
	{
	    int     osetintr = setintr;
I 59
	    sig_t   oparintr = parintr;
E 59
D 52
	    sigmask_t omask = sigblock(sigmask(SIGINT));
E 52
I 52
D 68
	    sigset_t omask = sigblock(sigmask(SIGINT));
E 68
I 68
	    sigset_t osigset;
E 68
E 52

I 68
	    sigemptyset(&sigset);
	    sigaddset(&sigset, SIGINT);
	    sigprocmask(SIG_BLOCK, &sigset, &osigset);

E 68
	    setintr = 0;
I 59
	    parintr = SIG_IGN;	/* Disable onintr */
E 59
#ifdef _PATH_DOTCSHRC
	    (void) srcfile(_PATH_DOTCSHRC, 0, 0);
#endif
	    if (!fast && !arginp && !onelflg)
D 54
		dohash();
E 54
I 54
		dohash(NULL, NULL);
E 54
#ifdef _PATH_DOTLOGIN
	    if (loginsh)
		(void) srcfile(_PATH_DOTLOGIN, 0, 0);
#endif
D 68
	    (void) sigsetmask(omask);
E 68
I 68
	    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 68
	    setintr = osetintr;
I 59
	    parintr = oparintr;
E 59
E 48
E 25
	}
I 48
	(void) srccat(value(STRhome), STRsldotcshrc);
E 48

D 48
	/*
	 * Now are ready for the -v and -x flags
	 */
	if (nverbose)
		setNS("verbose");
	if (nexececho)
		setNS("echo");
E 48
I 48
	if (!fast && !arginp && !onelflg && !havhash)
D 54
	    dohash();
E 54
I 54
	    dohash(NULL, NULL);
I 62
	/*
	 * Source history before .login so that it is available in .login
	 */
	if ((cp = value(STRhistfile)) != STRNULL)
	    loadhist[2] = cp;
	dosource(loadhist, NULL);
E 62
E 54
        if (loginsh)
	      (void) srccat(value(STRhome), STRsldotlogin);
D 54
	dosource(loadhist);
E 54
I 54
D 62
	dosource(loadhist, NULL);
E 62
E 54
    }
E 48

D 48
	/*
	 * All the rest of the world is inside this call.
	 * The argument to process indicates whether it should
	 * catch "error unwinds".  Thus if we are a interactive shell
	 * our call here will never return by being blown past on an error.
	 */
	process(setintr);
E 48
I 48
    /*
     * Now are ready for the -v and -x flags
     */
    if (nverbose)
	setNS(STRverbose);
    if (nexececho)
	setNS(STRecho);
E 48

D 48
	/*
	 * Mop-up.
	 */
E 48
I 48
    /*
     * All the rest of the world is inside this call. The argument to process
     * indicates whether it should catch "error unwinds".  Thus if we are a
     * interactive shell our call here will never return by being blown past on
     * an error.
     */
    process(setintr);

    /*
     * Mop-up.
     */
    if (intty) {
E 48
	if (loginsh) {
D 48
		printf("logout\n");
D 23
		close(SHIN);
E 23
I 23
		(void) close(SHIN);
E 23
		child++;
		goodbye();
E 48
I 48
D 54
	    xprintf("logout\n");
E 54
I 54
	    (void) fprintf(cshout, "logout\n");
E 54
	    (void) close(SHIN);
	    child = 1;
	    goodbye();
E 48
	}
I 6
D 48
	rechist();
E 6
	exitstat();
E 48
I 48
	else {
D 54
	    xprintf("exit\n");
E 54
I 54
	    (void) fprintf(cshout, "exit\n");
E 54
	}
    }
    rechist();
    exitstat();
    return (0);
E 48
}

I 48
void
E 48
untty()
{
D 48

	if (tpgrp > 0) {
D 23
		setpgrp(0, opgrp);
		ioctl(FSHTTY, TIOCSPGRP, &opgrp);
E 23
I 23
		(void) setpgrp(0, opgrp);
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&opgrp);
E 23
D 39
		if (oldisc != -1 && oldisc != NTTYDISC) {
I 6
#ifdef DEBUG
E 6
			printf("\nReverting to old tty driver...\n");
I 6
#endif DEBUG
E 6
D 23
			ioctl(FSHTTY, TIOCSETD, &oldisc);
E 23
I 23
			(void) ioctl(FSHTTY, TIOCSETD, (char *)&oldisc);
E 23
		}
E 39
	}
E 48
I 48
    if (tpgrp > 0) {
	(void) setpgid(0, opgrp);
	(void) tcsetpgrp(FSHTTY, opgrp);
    }
E 48
}

I 48
void
E 48
importpath(cp)
D 13
char *cp;
E 13
I 13
D 48
	char *cp;
E 48
I 48
    Char   *cp;
E 48
E 13
{
D 48
	register int i = 0;
	register char *dp;
	register char **pv;
	int c;
	static char dot[2] = {'.', 0};
E 48
I 48
    register int i = 0;
    register Char *dp;
    register Char **pv;
    int     c;
E 48

D 48
	for (dp = cp; *dp; dp++)
		if (*dp == ':')
			i++;
	/*
	 * i+2 where i is the number of colons in the path.
	 * There are i+1 directories in the path plus we need
	 * room for a zero terminator.
	 */
D 23
	pv = (char **) calloc(i+2, sizeof (char **));
E 23
I 23
	pv = (char **) calloc((unsigned) (i + 2), sizeof (char **));
E 23
	dp = cp;
	i = 0;
	if (*dp)
E 48
I 48
    for (dp = cp; *dp; dp++)
	if (*dp == ':')
	    i++;
    /*
     * i+2 where i is the number of colons in the path. There are i+1
     * directories in the path plus we need room for a zero terminator.
     */
    pv = (Char **) xcalloc((size_t) (i + 2), sizeof(Char **));
    dp = cp;
    i = 0;
    if (*dp)
E 48
	for (;;) {
D 48
		if ((c = *dp) == ':' || c == 0) {
			*dp = 0;
			pv[i++] = savestr(*cp ? cp : dot);
			if (c) {
				cp = dp + 1;
				*dp = ':';
			} else
				break;
E 48
I 48
	    if ((c = *dp) == ':' || c == 0) {
		*dp = 0;
I 63
		if ((*cp != '/' || *cp == '\0') && (euid == 0 || uid == 0)) 
		    (void) fprintf(csherr,
	    "Warning: imported path contains relative components\n");
E 63
		pv[i++] = Strsave(*cp ? cp : STRdot);
		if (c) {
		    cp = dp + 1;
		    *dp = ':';
E 48
		}
D 48
		dp++;
E 48
I 48
		else
		    break;
	    }
	    dp++;
E 48
	}
D 48
	pv[i] = 0;
	set1("path", pv, &shvhed);
E 48
I 48
    pv[i] = 0;
    set1(STRpath, pv, &shvhed);
E 48
}

/*
 * Source to the file which is the catenation of the argument names.
 */
I 48
static int
E 48
srccat(cp, dp)
D 48
	char *cp, *dp;
E 48
I 48
    Char   *cp, *dp;
E 48
{
D 48
	register char *ep = strspl(cp, dp);
	register int unit = dmove(open(ep, 0), -1);
E 48
I 48
    register Char *ep = Strspl(cp, dp);
    char   *ptr = short2str(ep);
E 48

D 23
	/* ioctl(unit, FIOCLEX, NULL); */
E 23
I 23
D 48
	(void) ioctl(unit, FIOCLEX, (char *)0);
E 23
	xfree(ep);
D 34
#ifdef INGRES
D 6
	srcunit(unit, 0);
E 6
I 6
	srcunit(unit, 0, 0);
E 6
#else
D 6
	srcunit(unit, 1);
E 6
I 6
	srcunit(unit, 1, 0);
E 6
#endif
E 34
I 34
	srcunit(unit, mflag ? 0 : 1, 0);
E 48
I 48
    xfree((ptr_t) ep);
    return srcfile(ptr, mflag ? 0 : 1, 0);
E 48
E 34
}

/*
D 34
 * Source to a unit.  If onlyown it must be our file or our group or
 * we don't chance it.	This occurs on ".cshrc"s and the like.
E 34
I 34
D 48
 * Source to a unit.
 * This occurs on ".cshrc"s and the like.
E 48
I 48
 * Source to a file putting the file descriptor in a safe place (> 2).
E 48
E 34
 */
I 31
D 48
int	insource;
E 48
I 48
static int
srcfile(f, onlyown, flag)
    char   *f;
    bool    onlyown, flag;
{
    register int unit;

    if ((unit = open(f, O_RDONLY)) == -1)
	return 0;
    unit = dmove(unit, -1);

D 51
    (void) ioctl(unit, FIOCLEX, (ioctl_t) 0);
E 51
I 51
    (void) ioctl(unit, FIOCLEX, NULL);
E 51
    srcunit(unit, onlyown, flag);
    return 1;
}

/*
 * Source to a unit.  If onlyown it must be our file or our group or
 * we don't chance it.	This occurs on ".cshrc"s and the like.
 */
int     insource;
E 48
D 43
static
E 43
I 43
static void
E 43
E 31
D 6
srcunit(unit, onlyown)
E 6
I 6
srcunit(unit, onlyown, hflg)
E 6
D 48
	register int unit;
D 34
	bool onlyown;
I 6
	bool hflg;
E 34
I 34
	bool onlyown, hflg;
E 48
I 48
    register int unit;
    bool    onlyown, hflg;
E 48
E 34
E 6
{
D 48
	/* We have to push down a lot of state here */
	/* All this could go into a structure */
	int oSHIN = -1, oldintty = intty;
	struct whyle *oldwhyl = whyles;
	char *ogointr = gointr, *oarginp = arginp;
	char *oevalp = evalp, **oevalvec = evalvec;
	int oonelflg = onelflg;
I 6
	bool oenterhist = enterhist;
	char OHIST = HIST;
E 48
I 48
    /* We have to push down a lot of state here */
    /* All this could go into a structure */
    int     oSHIN = -1, oldintty = intty, oinsource = insource;
    struct whyle *oldwhyl = whyles;
    Char   *ogointr = gointr, *oarginp = arginp;
    Char   *oevalp = evalp, **oevalvec = evalvec;
    int     oonelflg = onelflg;
    bool    oenterhist = enterhist;
    char    OHIST = HIST;
E 48
E 6
D 49
#ifdef TELL
E 49
D 48
	bool otell = cantell;
E 48
I 48
    bool    otell = cantell;
E 48
D 49
#endif
E 49
D 48
	struct Bin saveB;
E 48

D 48
	/* The (few) real local variables */
	jmp_buf oldexit;
D 21
	int reenter;
E 21
I 21
D 30
	int reenter, omask;
E 30
I 30
	int reenter;
	long omask;
E 48
I 48
    struct Bin saveB;
D 52
    sigmask_t omask;
E 52
I 52
D 54
    sigset_t omask;
E 54
I 54
D 68
    volatile sigset_t omask;
E 68
I 68
    sigset_t sigset, osigset;
E 68
E 54
E 52
    jmp_buf oldexit;
E 48
E 30
E 21

D 48
	if (unit < 0)
		return;
	if (didfds)
		donefds();
	if (onlyown) {
		struct stat stb;
E 48
I 48
    /* The (few) real local variables */
    int     my_reenter;
E 48

D 13
		if (fstat(unit, &stb) < 0 || (stb.st_uid != uid && stb.st_gid != getgid())) {
E 13
I 13
D 48
		if (fstat(unit, &stb) < 0 ||
		    (stb.st_uid != uid && stb.st_gid != getgid())) {
E 13
D 23
			close(unit);
E 23
I 23
			(void) close(unit);
E 23
			return;
		}
E 48
I 48
    if (unit < 0)
	return;
    if (didfds)
	donefds();
    if (onlyown) {
	struct stat stb;

	if (fstat(unit, &stb) < 0) {
	    (void) close(unit);
	    return;
E 48
	}
I 48
    }
E 48

D 48
	/*
	 * There is a critical section here while we are pushing down the
	 * input stream since we have stuff in different structures.
	 * If we weren't careful an interrupt could corrupt SHIN's Bin
	 * structure and kill the shell.
	 *
	 * We could avoid the critical region by grouping all the stuff
	 * in a single structure and pointing at it to move it all at
	 * once.  This is less efficient globally on many variable references
	 * however.
	 */
I 31
	insource = 1;
E 31
	getexit(oldexit);
	reenter = 0;
	if (setintr)
D 13
		sighold(SIGINT);
E 13
I 13
D 14
		(void) sigblock(mask(SIGINT));
E 14
I 14
D 21
		sighold(SIGINT);
E 21
I 21
		omask = sigblock(sigmask(SIGINT));
E 21
E 14
E 13
D 46
	setexit();
E 46
I 46
	(void)setjmp(reslab);
E 46
	reenter++;
	if (reenter == 1) {
		/* Setup the new values of the state stuff saved above */
D 45
		copy((char *)&saveB, (char *)&B, sizeof saveB);
E 45
I 45
		bcopy((char *)&B, (char *)&saveB, sizeof saveB);
E 45
		fbuf = (char **) 0;
		fseekp = feobp = fblocks = 0;
		oSHIN = SHIN, SHIN = unit, arginp = 0, onelflg = 0;
		intty = isatty(SHIN), whyles = 0, gointr = 0;
		evalvec = 0; evalp = 0;
I 6
		enterhist = hflg;
		if (enterhist)
			HIST = '\0';
E 6
		/*
		 * Now if we are allowing commands to be interrupted,
		 * we let ourselves be interrupted.
		 */
		if (setintr)
D 13
			sigrelse(SIGINT);
E 13
I 13
D 14
			(void) sigrelse(mask(SIGINT));
E 14
I 14
D 21
			sigrelse(SIGINT);
E 21
I 21
D 23
			sigsetmask(omask);
E 23
I 23
			(void) sigsetmask(omask);
E 48
I 48
    /*
     * There is a critical section here while we are pushing down the input
     * stream since we have stuff in different structures. If we weren't
     * careful an interrupt could corrupt SHIN's Bin structure and kill the
     * shell.
D 58
     * 
E 58
I 58
     *
E 58
     * We could avoid the critical region by grouping all the stuff in a single
     * structure and pointing at it to move it all at once.  This is less
     * efficient globally on many variable references however.
     */
    insource = 1;
    getexit(oldexit);
D 68
    omask = 0;
E 68

D 68
    if (setintr)
	omask = sigblock(sigmask(SIGINT));
E 68
I 68
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_BLOCK, &sigset, &osigset);
    }
E 68
    /* Setup the new values of the state stuff saved above */
D 69
    bcopy((char *) &B, (char *) &(saveB), sizeof(B));
E 69
I 69
    memmove(&saveB, &B, sizeof(B));
E 69
D 51
    fbuf = (Char **) 0;
E 51
I 51
    fbuf = NULL;
E 51
    fseekp = feobp = fblocks = 0;
    oSHIN = SHIN, SHIN = unit, arginp = 0, onelflg = 0;
    intty = isatty(SHIN), whyles = 0, gointr = 0;
    evalvec = 0;
    evalp = 0;
    enterhist = hflg;
    if (enterhist)
	HIST = '\0';

    /*
     * Now if we are allowing commands to be interrupted, we let ourselves be
     * interrupted.
     */
    if (setintr)
D 68
	(void) sigsetmask(omask);
E 68
I 68
	sigprocmask(SIG_SETMASK, &osigset, NULL);
E 68
E 48
E 23
E 21
E 14
E 13
D 49
#ifdef TELL
E 49
D 48
		settell();
E 48
I 48
    settell();
E 48
D 49
#endif
E 49
D 48
		process(0);		/* 0 -> blow away on errors */
	}
	if (setintr)
D 13
		sigrelse(SIGINT);
E 13
I 13
D 14
		(void) sigrelse(mask(SIGINT));
E 14
I 14
D 21
		sigrelse(SIGINT);
E 21
I 21
D 23
		sigsetmask(omask);
E 23
I 23
		(void) sigsetmask(omask);
E 23
E 21
E 14
E 13
	if (oSHIN >= 0) {
		register int i;
E 48

D 48
		/* We made it to the new state... free up its storage */
		/* This code could get run twice but xfree doesn't care */
		for (i = 0; i < fblocks; i++)
			xfree(fbuf[i]);
		xfree((char *)fbuf);
E 48
I 48
    if ((my_reenter = setexit()) == 0)
	process(0);		/* 0 -> blow away on errors */
E 48

D 48
		/* Reset input arena */
D 45
		copy((char *)&B, (char *)&saveB, sizeof B);
E 45
I 45
		bcopy((char *)&saveB, (char *)&B, sizeof B);
E 48
I 48
    if (setintr)
D 68
	(void) sigsetmask(omask);
E 68
I 68
	sigprocmask(SIG_SETMASK, &osigset, NULL);
E 68
    if (oSHIN >= 0) {
	register int i;
E 48
E 45

D 23
		close(SHIN), SHIN = oSHIN;
E 23
I 23
D 48
		(void) close(SHIN), SHIN = oSHIN;
E 23
		arginp = oarginp, onelflg = oonelflg;
		evalp = oevalp, evalvec = oevalvec;
		intty = oldintty, whyles = oldwhyl, gointr = ogointr;
I 7
		if (enterhist)
			HIST = OHIST;
E 7
I 6
		enterhist = oenterhist;
E 48
I 48
	/* We made it to the new state... free up its storage */
	/* This code could get run twice but xfree doesn't care */
	for (i = 0; i < fblocks; i++)
	    xfree((ptr_t) fbuf[i]);
	xfree((ptr_t) fbuf);

	/* Reset input arena */
D 69
	bcopy((char *) &(saveB), (char *) &B, sizeof(B));
E 69
I 69
	memmove(&B, &saveB, sizeof(B));
E 69

	(void) close(SHIN), SHIN = oSHIN;
	arginp = oarginp, onelflg = oonelflg;
	evalp = oevalp, evalvec = oevalvec;
	intty = oldintty, whyles = oldwhyl, gointr = ogointr;
	if (enterhist)
	    HIST = OHIST;
	enterhist = oenterhist;
E 48
D 7
		HIST = OHIST;
E 7
E 6
D 49
#ifdef TELL
E 49
D 48
		cantell = otell;
E 48
I 48
	cantell = otell;
E 48
D 49
#endif
E 49
D 48
	}
E 48
I 48
    }
E 48

D 48
	resexit(oldexit);
	/*
	 * If process reset() (effectively an unwind) then
	 * we must also unwind.
	 */
	if (reenter >= 2)
		error(NOSTR);
I 31
	insource = 0;
E 48
I 48
    resexit(oldexit);
    /*
     * If process reset() (effectively an unwind) then we must also unwind.
     */
    if (my_reenter)
	stderror(ERR_SILENT);
    insource = oinsource;
E 48
E 31
}

I 48
void
E 48
D 6
goodbye()
E 6
I 6
rechist()
E 6
{
I 3
D 48
	char buf[BUFSIZ];
	int fp, ftmp, oldidfds;
E 48
I 48
D 61
    Char    buf[BUFSIZ];
E 61
I 61
    Char    buf[BUFSIZ], hbuf[BUFSIZ], *hfile;
E 61
    int     fp, ftmp, oldidfds;
I 61
    struct  varent *shist;
E 61
E 48
E 3

D 6
	if (loginsh) {
E 6
I 6
D 48
	if (!fast) {
I 9
		if (value("savehist")[0] == '\0')
			return;
E 9
E 6
I 3
D 23
		strcpy(buf, value("home"));
		strcat(buf, "/.history");
E 23
I 23
		(void) strcpy(buf, value("home"));
		(void) strcat(buf, "/.history");
E 23
D 18
		fp = creat(buf, 0777);
E 18
I 18
		fp = creat(buf, 0666);
E 18
D 9
		if (fp != -1) {
			oldidfds = didfds;
			didfds = 0;
			ftmp = SHOUT;
			SHOUT = fp;
			dohist(dumphist);
			close(fp);
			SHOUT = ftmp;
			didfds = oldidfds;
		}
E 9
I 9
		if (fp == -1)
			return;
		oldidfds = didfds;
		didfds = 0;
		ftmp = SHOUT;
		SHOUT = fp;
D 23
		strcpy(buf, value("savehist"));
E 23
I 23
		(void) strcpy(buf, value("savehist"));
E 23
		dumphist[2] = buf;
		dohist(dumphist);
D 23
		close(fp);
E 23
I 23
		(void) close(fp);
E 23
		SHOUT = ftmp;
		didfds = oldidfds;
E 9
I 6
	}
E 48
I 48
    if (!fast) {
D 61
	if (value(STRsavehist)[0] == '\0')
	    return;
	(void) Strcpy(buf, value(STRhome));
	(void) Strcat(buf, STRsldthist);
	fp = creat(short2str(buf), 0600);
	if (fp == -1)
	    return;
E 61
I 61
	/*
	 * If $savehist is just set, we use the value of $history
	 * else we use the value in $savehist
	 */
D 65
	if (shist = adrof(STRsavehist)) {
E 65
I 65
	if ((shist = adrof(STRsavehist)) != NULL) {
E 65
	    if (shist->vec[0][0] != '\0')
		(void) Strcpy(hbuf, shist->vec[0]);
	    else if ((shist = adrof(STRhistory)) && shist->vec[0][0] != '\0')
		(void) Strcpy(hbuf, shist->vec[0]);
	    else
		return;
	}
	else
  	    return;

  	if ((hfile = value(STRhistfile)) == STRNULL) {
  	    hfile = Strcpy(buf, value(STRhome));
  	    (void) Strcat(buf, STRsldthist);
  	}

D 69
  	if ((fp = creat(short2str(hfile), 0600)) == -1) 
E 69
I 69
  	if ((fp = open(short2str(hfile), O_WRONLY | O_CREAT | O_TRUNC,
	    0600)) == -1) 
E 69
  	    return;

E 61
	oldidfds = didfds;
	didfds = 0;
	ftmp = SHOUT;
	SHOUT = fp;
D 61
	(void) Strcpy(buf, value(STRsavehist));
	dumphist[2] = buf;
E 61
I 61
	dumphist[2] = hbuf;
E 61
D 54
	dohist(dumphist);
	(void) close(fp);
E 54
I 54
	dohist(dumphist, NULL);
E 54
	SHOUT = ftmp;
I 54
	(void) close(fp);
E 54
	didfds = oldidfds;
    }
E 48
}

I 48
void
E 48
goodbye()
{
D 48
	if (loginsh) {
E 6
E 3
D 23
		signal(SIGQUIT, SIG_IGN);
D 13
		sigset(SIGINT, SIG_IGN);
E 13
I 13
D 14
		signal(SIGINT, SIG_IGN);
E 14
I 14
D 21
		sigset(SIGINT, SIG_IGN);
E 21
I 21
		signal(SIGINT, SIG_IGN);
E 21
E 14
E 13
		signal(SIGTERM, SIG_IGN);
E 23
I 23
		(void) signal(SIGQUIT, SIG_IGN);
		(void) signal(SIGINT, SIG_IGN);
		(void) signal(SIGTERM, SIG_IGN);
E 23
		setintr = 0;		/* No interrupts after "logout" */
I 35
		srcunit(open(_PATH_DOTLOGOUT, O_RDONLY), 0, 0);
E 35
		if (adrof("home"))
			srccat(value("home"), "/.logout");
	}
I 6
	rechist();
E 6
	exitstat();
E 48
I 48
    rechist();

    if (loginsh) {
	(void) signal(SIGQUIT, SIG_IGN);
	(void) signal(SIGINT, SIG_IGN);
	(void) signal(SIGTERM, SIG_IGN);
	setintr = 0;		/* No interrupts after "logout" */
	if (!(adrof(STRlogout)))
	    set(STRlogout, STRnormal);
#ifdef _PATH_DOTLOGOUT
	(void) srcfile(_PATH_DOTLOGOUT, 0, 0);
#endif
	if (adrof(STRhome))
	    (void) srccat(value(STRhome), STRsldtlogout);
    }
    exitstat();
E 48
}

I 48
void
E 48
exitstat()
{
D 54

E 54
I 54
    Char *s;
E 54
I 23
#ifdef PROF
D 48
	monitor(0);
E 48
I 48
    monitor(0);
E 48
#endif
E 23
D 48
	/*
	 * Note that if STATUS is corrupted (i.e. getn bombs)
	 * then error will exit directly because we poke child here.
	 * Otherwise we might continue unwarrantedly (sic).
	 */
	child++;
	exit(getn(value("status")));
E 48
I 48
    /*
     * Note that if STATUS is corrupted (i.e. getn bombs) then error will exit
     * directly because we poke child here. Otherwise we might continue
     * unwarrantedly (sic).
     */
    child = 1;
D 54
    xexit(getn(value(STRstatus)));
E 54
I 54
    s = value(STRstatus);
    xexit(s ? getn(s) : 0);
E 54
E 48
}

I 6
/*
 * in the event of a HUP we want to save the history
 */
I 48
static void
E 48
D 51
phup()
E 51
I 51
phup(sig)
int sig;
E 51
{
D 48
	rechist();
	exit(1);
E 48
I 48
    rechist();
I 67

    /*
     * We kill the last foreground process group. It then becomes
     * responsible to propagate the SIGHUP to its progeny. 
     */
    {
	struct process *pp, *np;

	for (pp = proclist.p_next; pp; pp = pp->p_next) {
	    np = pp;
	    /* 
	     * Find if this job is in the foreground. It could be that
	     * the process leader has exited and the foreground flag
	     * is cleared for it.
	     */
	    do
		/*
		 * If a process is in the foreground; we try to kill
		 * it's process group. If we succeed, then the 
		 * whole job is gone. Otherwise we keep going...
		 * But avoid sending HUP to the shell again.
		 */
		if ((np->p_flags & PFOREGND) != 0 && np->p_jobid != shpgrp &&
		    killpg(np->p_jobid, SIGHUP) != -1) {
		    /* In case the job was suspended... */
		    (void) killpg(np->p_jobid, SIGCONT);
		    break;
		}
	    while ((np = np->p_friends) != pp);
	}
    }
E 67
D 51
    xexit(1);
E 51
I 51
D 64
    xexit(sig);
E 64
I 64
D 69
    _exit(sig);
E 69
I 69
    xexit(sig);
E 69
E 64
E 51
E 48
}

E 6
D 48
char	*jobargv[2] = { "jobs", 0 };
E 48
I 48
Char   *jobargv[2] = {STRjobs, 0};

E 48
/*
 * Catch an interrupt, e.g. during lexical input.
 * If we are an interactive shell, we reset the interrupt catch
 * immediately.  In any case we drain the shell output,
 * and finally go through the normal error mechanism, which
 * gets a chance to make the shell go away.
 */
I 50
/* ARGSUSED */
E 50
I 44
void
E 44
D 50
pintr()
E 50
I 50
pintr(notused)
	int notused;
E 50
{
I 2
D 48
	pintr1(1);
E 48
I 48
    pintr1(1);
E 48
}

I 48
void
E 48
pintr1(wantnl)
D 48
	bool wantnl;
E 48
I 48
    bool    wantnl;
E 48
{
E 2
D 48
	register char **v;
I 21
D 30
	int omask;
E 30
I 30
	long omask;
E 48
I 48
D 54
    register Char **v;
E 54
I 54
    Char **v;
E 54
D 52
    sigmask_t omask;
E 52
I 52
D 68
    sigset_t omask;
E 68
I 68
    sigset_t sigset, osigset;
E 68
E 52
E 48
E 30
E 21

I 21
D 30
	omask = sigblock(0);
E 30
I 30
D 48
	omask = sigblock(0L);
E 30
E 21
	if (setintr) {
D 13
		sigrelse(SIGINT);
E 13
I 13
D 14
		(void) sigrelse(mask(SIGINT));
E 14
I 14
D 21
		sigrelse(SIGINT);
E 21
I 21
D 23
		sigsetmask(omask & ~sigmask(SIGINT));
E 23
I 23
		(void) sigsetmask(omask & ~sigmask(SIGINT));
E 23
E 21
E 14
E 13
		if (pjobs) {
			pjobs = 0;
			printf("\n");
			dojobs(jobargv);
			bferr("Interrupted");
		}
E 48
I 48
D 52
    omask = sigblock((sigmask_t) 0);
E 52
I 52
D 68
    omask = sigblock((sigset_t) 0);
E 68
I 68
    sigemptyset(&sigset);
    sigprocmask(SIG_BLOCK, &sigset, &osigset);
E 68
E 52
    if (setintr) {
D 68
	(void) sigsetmask(omask & ~sigmask(SIGINT));
E 68
I 68
	sigset = osigset;
	sigdelset(&sigset, SIGINT);
	sigprocmask(SIG_SETMASK, &sigset, NULL);
E 68
	if (pjobs) {
	    pjobs = 0;
D 54
	    xprintf("\n");
	    dojobs(jobargv);
E 54
I 54
	    (void) fprintf(cshout, "\n");
	    dojobs(jobargv, NULL);
E 54
	    stderror(ERR_NAME | ERR_INTR);
E 48
	}
D 21
	if (setintr)
D 13
		sighold(SIGINT);
	sigrelse(SIGCHLD);
E 13
I 13
D 14
		sigblock(mask(SIGINT));
	sigrelse(mask(SIGCHLD));
E 14
I 14
		sighold(SIGINT);
	sigrelse(SIGCHLD);
E 21
I 21
D 23
	sigsetmask(omask & ~sigmask(SIGCHLD));
E 23
I 23
D 48
	(void) sigsetmask(omask & ~sigmask(SIGCHLD));
E 23
E 21
E 14
E 13
	draino();
E 48
I 48
    }
D 68
    (void) sigsetmask(omask & ~sigmask(SIGCHLD));
E 68
I 68
    sigdelset(&osigset, SIGCHLD);
    sigprocmask(SIG_SETMASK, &osigset, NULL);
E 68
D 54
    draino();
E 54
I 54
    (void) fpurge(cshout);
E 54
    (void) endpwent();
E 48

D 48
	/*
	 * If we have an active "onintr" then we search for the label.
	 * Note that if one does "onintr -" then we shan't be interruptible
	 * so we needn't worry about that here.
	 */
	if (gointr) {
D 46
		search(ZGOTO, 0, gointr);
E 46
I 46
		search(T_GOTO, 0, gointr);
E 46
		timflg = 0;
		if (v = pargv)
			pargv = 0, blkfree(v);
		if (v = gargv)
			gargv = 0, blkfree(v);
D 46
		reset();
E 46
I 46
		longjmp(reslab, 0);
E 46
D 2
	} else if (intty)
E 2
I 2
	} else if (intty && wantnl)
E 2
		printf("\n");		/* Some like this, others don't */
	error(NOSTR);
E 48
I 48
    /*
     * If we have an active "onintr" then we search for the label. Note that if
     * one does "onintr -" then we shan't be interruptible so we needn't worry
     * about that here.
     */
    if (gointr) {
D 57
	search(T_GOTO, 0, gointr);
E 57
I 57
	gotolab(gointr);
E 57
	timflg = 0;
D 65
	if (v = pargv)
E 65
I 65
	if ((v = pargv) != NULL)
E 65
	    pargv = 0, blkfree(v);
D 65
	if (v = gargv)
E 65
I 65
	if ((v = gargv) != NULL)
E 65
	    gargv = 0, blkfree(v);
	reset();
    }
    else if (intty && wantnl) {
D 54
	(void) putraw('\r');
	(void) putraw('\n');
E 54
I 54
	(void) fputc('\r', cshout);
	(void) fputc('\n', cshout);
E 54
    }
    stderror(ERR_SILENT);
E 48
}

/*
 * Process is the main driving routine for the shell.
 * It runs all command processing, except for those within { ... }
 * in expressions (which is run by a routine evalav in sh.exp.c which
 * is a stripped down process), and `...` evaluation which is run
 * also by a subset of this code in sh.glob.c in the routine backeval.
 *
 * The code here is a little strange because part of it is interruptible
 * and hence freeing of structures appears to occur when none is necessary
 * if this is ignored.
 *
 * Note that if catch is not set then we will unwind on any error.
 * If an end-of-file occurs, we return.
 */
I 54
static struct command *savet = NULL;
E 54
I 48
void
E 48
process(catch)
D 48
	bool catch;
E 48
I 48
    bool    catch;
E 48
{
D 23
	register char *cp;
E 23
D 48
	jmp_buf osetexit;
D 23
	struct command *t;
E 23
I 23
	register struct command *t;
E 48
I 48
    jmp_buf osetexit;
D 54
    struct command *t;
E 54
I 54
    struct command *t = savet;
I 68
    sigset_t sigset;
E 68
E 54
E 48
E 23

I 54
    savet = NULL;
E 54
D 48
	getexit(osetexit);
	for (;;) {
		pendjob();
		paraml.next = paraml.prev = &paraml;
		paraml.word = "";
		t = 0;
D 46
		setexit();
E 46
I 46
		(void)setjmp(reslab);
E 46
D 3
		justpr = 0;			/* A chance to execute */
E 3
I 3
		justpr = enterhist;	/* execute if not entering history */
E 48
I 48
    getexit(osetexit);
    for (;;) {
	pendjob();
	paraml.next = paraml.prev = &paraml;
	paraml.word = STRNULL;
D 54
	t = 0;
E 54
	(void) setexit();
	justpr = enterhist;	/* execute if not entering history */
E 48
E 3

D 48
		/*
		 * Interruptible during interactive reads
		 */
		if (setintr)
D 13
			sigrelse(SIGINT);
E 13
I 13
D 14
			(void) sigrelse(mask(SIGINT));
E 14
I 14
D 21
			sigrelse(SIGINT);
E 21
I 21
D 23
			sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 23
I 23
D 30
			(void) sigsetmask(sigblock(0) & ~sigmask(SIGINT));
E 30
I 30
			(void) sigsetmask(sigblock(0L) & ~sigmask(SIGINT));
E 48
I 48
	/*
	 * Interruptible during interactive reads
	 */
D 68
	if (setintr)
D 52
	    (void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 52
I 52
	    (void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 68
I 68
	if (setintr) {
	    sigemptyset(&sigset);
	    sigaddset(&sigset, SIGINT);
	    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	}
E 68
E 52
E 48
E 30
E 23
E 21
E 14
E 13

D 48
		/*
		 * For the sake of reset()
		 */
		freelex(&paraml), freesyn(t), t = 0;
E 48
I 48
	/*
	 * For the sake of reset()
	 */
	freelex(&paraml);
D 54
	freesyn(t);
	t = 0;
E 54
I 54
	if (savet)
	    freesyn(savet), savet = NULL;
E 54
E 48

D 48
		if (haderr) {
			if (!catch) {
				/* unwind */
				doneinp = 0;
				resexit(osetexit);
D 46
				reset();
E 46
I 46
				longjmp(reslab, 0);
E 46
			}
			haderr = 0;
			/*
			 * Every error is eventually caught here or
			 * the shell dies.  It is at this
			 * point that we clean up any left-over open
			 * files, by closing all but a fixed number
			 * of pre-defined files.  Thus routines don't
			 * have to worry about leaving files open due
			 * to deeper errors... they will get closed here.
			 */
			closem();
			continue;
		}
		if (doneinp) {
			doneinp = 0;
			break;
		}
		if (chkstop)
			chkstop--;
		if (neednote)
			pnote();
D 17
		if (intty && evalvec == 0) {
E 17
I 17
		if (intty && prompt && evalvec == 0) {
E 17
			mailchk();
			/*
			 * If we are at the end of the input buffer
			 * then we are going to read fresh stuff.
			 * Otherwise, we are rereading input and don't
			 * need or want to prompt.
			 */
			if (fseekp == feobp)
D 16
				if (!whyles)
					for (cp = value("prompt"); *cp; cp++)
						if (*cp == HIST)
							printf("%d", eventno + 1);
						else {
							if (*cp == '\\' && cp[1] == HIST)
								cp++;
							putchar(*cp | QUOTE);
						}
				else
					/*
					 * Prompt for forward reading loop
					 * body content.
					 */
					printf("? ");
E 16
I 16
D 19
			    printprompt();
E 19
I 19
				printprompt();
E 19
E 16
D 23
			flush();
E 23
		}
		err = 0;
E 48
I 48
	if (haderr) {
	    if (!catch) {
		/* unwind */
		doneinp = 0;
		resexit(osetexit);
I 54
		savet = t;
E 54
		reset();
	    }
	    haderr = 0;
	    /*
	     * Every error is eventually caught here or the shell dies.  It is
	     * at this point that we clean up any left-over open files, by
	     * closing all but a fixed number of pre-defined files.  Thus
	     * routines don't have to worry about leaving files open due to
	     * deeper errors... they will get closed here.
	     */
	    closem();
	    continue;
	}
	if (doneinp) {
	    doneinp = 0;
	    break;
	}
	if (chkstop)
	    chkstop--;
	if (neednote)
	    pnote();
	if (intty && prompt && evalvec == 0) {
	    mailchk();
	    /*
	     * If we are at the end of the input buffer then we are going to
	     * read fresh stuff. Otherwise, we are rereading input and don't
	     * need or want to prompt.
	     */
D 56
	    if (fseekp == feobp)
E 56
I 56
	    if (aret == F_SEEK && fseekp == feobp)
E 56
		printprompt();
D 54
	    flush();
E 54
I 54
	    (void) fflush(cshout);
E 54
	}
	if (seterr) {
	    xfree((ptr_t) seterr);
D 51
	    seterr = (char *) 0;
E 51
I 51
	    seterr = NULL;
E 51
	}
E 48

D 48
		/*
		 * Echo not only on VERBOSE, but also with history expansion.
		 * If there is a lexical error then we forego history echo.
		 */
D 6
		if (lex(&paraml) && !err && intty || adrof("verbose")) {
E 6
I 6
		if (lex(&paraml) && !err && intty ||
		    adrof("verbose")) {
E 6
			haderr = 1;
			prlex(&paraml);
			haderr = 0;
		}
E 48
I 48
	/*
	 * Echo not only on VERBOSE, but also with history expansion. If there
	 * is a lexical error then we forego history echo.
	 */
D 65
	if (lex(&paraml) && !seterr && intty || adrof(STRverbose)) {
E 65
I 65
	if ((lex(&paraml) && !seterr && intty) || adrof(STRverbose)) {
E 65
D 54
	    haderr = 1;
	    prlex(&paraml);
	    haderr = 0;
E 54
I 54
	    prlex(csherr, &paraml);
E 54
	}
E 48

D 48
		/*
		 * The parser may lose space if interrupted.
		 */
		if (setintr)
D 13
			sighold(SIGINT);
E 13
I 13
D 14
			sigblock(mask(SIGINT));
E 14
I 14
D 21
			sighold(SIGINT);
E 21
I 21
D 23
			sigblock(sigmask(SIGINT));
E 23
I 23
			(void) sigblock(sigmask(SIGINT));
E 48
I 48
	/*
	 * The parser may lose space if interrupted.
	 */
	if (setintr)
D 68
	    (void) sigblock(sigmask(SIGINT));
E 68
I 68
	    sigprocmask(SIG_BLOCK, &sigset, NULL);
E 68
E 48
E 23
E 21
E 14
E 13

D 48
		/*
D 3
		 * Save input text on the history list if it
E 3
I 3
		 * Save input text on the history list if 
		 * reading in old history, or it
E 3
		 * is from the terminal at the top level and not
		 * in a loop.
		 */
D 3
		if (catch && intty && !whyles)
E 3
I 3
		if (enterhist || catch && intty && !whyles)
E 3
			savehist(&paraml);
E 48
I 48
	/*
	 * Save input text on the history list if reading in old history, or it
	 * is from the terminal at the top level and not in a loop.
D 58
	 * 
E 58
I 58
	 *
E 58
	 * PWP: entry of items in the history list while in a while loop is done
	 * elsewhere...
	 */
D 65
	if (enterhist || catch && intty && !whyles)
E 65
I 65
	if (enterhist || (catch && intty && !whyles))
E 65
	    savehist(&paraml);
E 48

D 48
		/*
D 6
		 * Print lexical error messages.
E 6
I 6
		 * Print lexical error messages, except when sourcing
		 * history lists.
E 6
		 */
D 6
		if (err)
E 6
I 6
		if (!enterhist && err)
E 6
			error(err);
E 48
I 48
	/*
	 * Print lexical error messages, except when sourcing history lists.
	 */
	if (!enterhist && seterr)
	    stderror(ERR_OLD);
E 48

D 48
		/*
		 * If had a history command :p modifier then
		 * this is as far as we should go
		 */
		if (justpr)
D 46
			reset();
E 46
I 46
			longjmp(reslab, 0);
E 48
I 48
	/*
	 * If had a history command :p modifier then this is as far as we
	 * should go
	 */
	if (justpr)
	    reset();
E 48
E 46

D 48
		alias(&paraml);
E 48
I 48
	alias(&paraml);
E 48

D 48
		/*
		 * Parse the words of the input into a parse tree.
		 */
		t = syntax(paraml.next, &paraml, 0);
		if (err)
			error(err);
E 48
I 48
	/*
	 * Parse the words of the input into a parse tree.
	 */
D 54
	t = syntax(paraml.next, &paraml, 0);
E 54
I 54
	savet = syntax(paraml.next, &paraml, 0);
E 54
	if (seterr)
	    stderror(ERR_OLD);
E 48

D 48
		/*
		 * Execute the parse tree
		 */
		execute(t, tpgrp);
E 48
I 48
D 50
	execute(t, (tpgrp > 0 ? tpgrp : -1));
E 50
I 50
D 54
	execute(t, (tpgrp > 0 ? tpgrp : -1), NULL, NULL);
E 54
I 54
D 58
	execute(savet, (tpgrp > 0 ? tpgrp : -1), NULL, NULL); 
E 58
I 58
	execute(savet, (tpgrp > 0 ? tpgrp : -1), NULL, NULL);
E 58
E 54
E 50
E 48

D 48
		/*
		 * Made it!
		 */
		freelex(&paraml), freesyn(t);
	}
	resexit(osetexit);
E 48
I 48
	/*
	 * Made it!
	 */
	freelex(&paraml);
D 54
	freesyn(t);
E 54
I 54
	freesyn((struct command *) savet), savet = NULL;
E 54
    }
    resexit(osetexit);
I 54
    savet = t;
E 54
E 48
}

I 48
void
E 48
D 54
dosource(t)
D 48
	register char **t;
E 48
I 48
    register Char **t;
E 54
I 54
/*ARGSUSED*/
dosource(v, t)
    Char **v;
    struct command *t;

E 54
E 48
{
D 48
	register char *f;
	register int u;
I 6
	bool hflg = 0;
	char buf[BUFSIZ];
E 48
I 48
    register Char *f;
    bool    hflg = 0;
    Char    buf[BUFSIZ];
E 48
E 6

D 48
	t++;
D 6
	f = globone(*t);
E 6
I 6
	if (*t && eq(*t, "-h")) {
		t++;
		hflg++;
	}
D 23
	strcpy(buf, *t);
E 23
I 23
	(void) strcpy(buf, *t);
E 23
	f = globone(buf);
E 6
	u = dmove(open(f, 0), -1);
	xfree(f);
D 6
	if (u < 0)
E 6
I 6
	if (u < 0 && !hflg)
E 6
		Perror(f);
I 23
	(void) ioctl(u, FIOCLEX, (char *)0);
E 23
D 6
	srcunit(u, 0);
E 6
I 6
	srcunit(u, 0, hflg);
E 48
I 48
D 54
    t++;
    if (*t && eq(*t, STRmh)) {
	if (*++t == NULL)
E 54
I 54
    v++;
    if (*v && eq(*v, STRmh)) {
	if (*++v == NULL)
E 54
	    stderror(ERR_NAME | ERR_HFLAG);
	hflg++;
    }
D 54
    (void) Strcpy(buf, *t);
E 54
I 54
    (void) Strcpy(buf, *v);
E 54
    f = globone(buf, G_ERROR);
    (void) strcpy((char *) buf, short2str(f));
    xfree((ptr_t) f);
    if (!srcfile((char *) buf, 0, hflg) && !hflg)
	stderror(ERR_SYSTEM, (char *) buf, strerror(errno));
E 48
E 6
}

/*
 * Check for mail.
 * If we are a login shell, then we don't want to tell
 * about any mail file unless its been modified
 * after the time we started.
 * This prevents us from telling the user things he already
 * knows, since the login program insists on saying
 * "You have mail."
 */
I 48
static void
E 48
mailchk()
{
D 48
	register struct varent *v;
	register char **vp;
	time_t t;
	int intvl, cnt;
	struct stat stb;
	bool new;
E 48
I 48
    register struct varent *v;
    register Char **vp;
    time_t  t;
    int     intvl, cnt;
    struct stat stb;
    bool    new;
E 48

D 48
	v = adrof("mail");
	if (v == 0)
		return;
D 23
	time(&t);
E 23
I 23
	(void) time(&t);
E 23
	vp = v->vec;
	cnt = blklen(vp);
	intvl = (cnt && number(*vp)) ? (--cnt, getn(*vp++)) : MAILINTVL;
	if (intvl < 1)
		intvl = 1;
	if (chktim + intvl > t)
		return;
	for (; *vp; vp++) {
		if (stat(*vp, &stb) < 0)
			continue;
D 12
		new = stb.st_mtime > time0;
E 12
I 12
		new = stb.st_mtime > time0.tv_sec;
E 12
		if (stb.st_size == 0 || stb.st_atime > stb.st_mtime ||
		    (stb.st_atime < chktim && stb.st_mtime < chktim) ||
		    loginsh && !new)
			continue;
		if (cnt == 1)
			printf("You have %smail.\n", new ? "new " : "");
		else
			printf("%s in %s.\n", new ? "New mail" : "Mail", *vp);
	}
	chktim = t;
E 48
I 48
    v = adrof(STRmail);
    if (v == 0)
	return;
    (void) time(&t);
    vp = v->vec;
    cnt = blklen(vp);
    intvl = (cnt && number(*vp)) ? (--cnt, getn(*vp++)) : MAILINTVL;
    if (intvl < 1)
	intvl = 1;
    if (chktim + intvl > t)
	return;
    for (; *vp; vp++) {
	if (stat(short2str(*vp), &stb) < 0)
	    continue;
	new = stb.st_mtime > time0.tv_sec;
	if (stb.st_size == 0 || stb.st_atime > stb.st_mtime ||
	    (stb.st_atime < chktim && stb.st_mtime < chktim) ||
D 65
	    loginsh && !new)
E 65
I 65
	    (loginsh && !new))
E 65
	    continue;
	if (cnt == 1)
D 54
	    xprintf("You have %smail.\n", new ? "new " : "");
E 54
I 54
	    (void) fprintf(cshout, "You have %smail.\n", new ? "new " : "");
E 54
	else
D 54
	    xprintf("%s in %s.\n", new ? "New mail" : "Mail", short2str(*vp));
E 54
I 54
D 58
	    (void) fprintf(cshout, "%s in %s.\n", new ? "New mail" : "Mail", 
E 58
I 58
	    (void) fprintf(cshout, "%s in %s.\n", new ? "New mail" : "Mail",
E 58
D 60
			   short2str(*vp));
E 60
I 60
			   vis_str(*vp));
E 60
E 54
    }
    chktim = t;
E 48
}

D 48
#include <pwd.h>
E 48
/*
 * Extract a home directory from the password file
 * The argument points to a buffer where the name of the
 * user whose home directory is sought is currently.
 * We write the home directory of the user back there.
 */
I 48
int
E 48
gethdir(home)
D 48
	char *home;
E 48
I 48
    Char   *home;
E 48
{
D 48
	register struct passwd *pp = getpwnam(home);
E 48
I 48
    Char   *h;
    struct passwd *pw;
E 48

D 48
	if (pp == 0)
		return (1);
D 23
	strcpy(home, pp->pw_dir);
E 23
I 23
	(void) strcpy(home, pp->pw_dir);
E 23
	return (0);
E 48
I 48
    /*
     * Is it us?
     */
    if (*home == '\0') {
D 65
	if (h = value(STRhome)) {
E 65
I 65
	if ((h = value(STRhome)) != NULL) {
E 65
	    (void) Strcpy(home, h);
	    return 0;
	}
	else
	    return 1;
    }

D 65
    if (pw = getpwnam(short2str(home))) {
E 65
I 65
    if ((pw = getpwnam(short2str(home))) != NULL) {
E 65
	(void) Strcpy(home, str2short(pw->pw_dir));
	return 0;
    }
    else
	return 1;
E 48
}

/*
I 54
 * When didfds is set, we do I/O from 0, 1, 2 otherwise from 15, 16, 17
D 55
 * We alsocheck if the shell has already chenged the decriptor to point to
E 55
I 55
 * We also check if the shell has already changed the decriptor to point to
E 55
 * 0, 1, 2 when didfds is set.
 */
#define DESC(a) (*((int *) (a)) - (didfds && *((int *) a) >= FSHIN ? FSHIN : 0))

static int
readf(oreo, buf, siz)
    void *oreo;
    char *buf;
    int siz;
{
    return read(DESC(oreo), buf, siz);
}


static int
writef(oreo, buf, siz)
    void *oreo;
    const char *buf;
    int siz;
{
    return write(DESC(oreo), buf, siz);
}

static fpos_t
seekf(oreo, off, whence)
    void *oreo;
    fpos_t off;
    int whence;
{
    return lseek(DESC(oreo), off, whence);
}


static int
closef(oreo)
    void *oreo;
{
    return close(DESC(oreo));
}


/*
I 60
 * Print the visible version of a string.
 */
int
vis_fputc(ch, fp)
    int ch;
    FILE *fp;
{
    char uenc[5];	/* 4 + NULL */

    if (ch & QUOTE) 
	return fputc(ch & TRIM, fp);
D 61
    (void) vis(uenc, ch & TRIM, 
	       AsciiOnly ? VIS_NOSLASH : (VIS_NLS | VIS_NOSLASH), 0);
E 61
I 61
    /* 
     * XXX: When we are in AsciiOnly we want all characters >= 0200 to
     * be encoded, but currently there is no way in vis to do that.
     */
    (void) vis(uenc, ch & TRIM, VIS_NOSLASH, 0);
E 61
    return fputs(uenc, fp);
}

/*
E 60
E 54
 * Move the initial descriptors to their eventual
 * resting places, closin all other units.
 */
I 48
void
E 48
initdesc()
{

D 23
	didcch = 0;			/* Havent closed for child */
E 23
D 48
	didfds = 0;			/* 0, 1, 2 aren't set up */
D 23
	SHIN = dcopy(0, FSHIN);
	SHOUT = dcopy(1, FSHOUT);
	SHDIAG = dcopy(2, FSHDIAG);
	OLDSTD = dcopy(SHIN, FOLDSTD);
E 23
I 23
	(void) ioctl(SHIN = dcopy(0, FSHIN), FIOCLEX, (char *)0);
	(void) ioctl(SHOUT = dcopy(1, FSHOUT), FIOCLEX, (char *)0);
	(void) ioctl(SHDIAG = dcopy(2, FSHDIAG), FIOCLEX, (char *)0);
	(void) ioctl(OLDSTD = dcopy(SHIN, FOLDSTD), FIOCLEX, (char *)0);
E 23
	closem();
E 48
I 48
    didfds = 0;			/* 0, 1, 2 aren't set up */
D 51
    (void) ioctl(SHIN = dcopy(0, FSHIN), FIOCLEX, (ioctl_t) 0);
    (void) ioctl(SHOUT = dcopy(1, FSHOUT), FIOCLEX, (ioctl_t) 0);
    (void) ioctl(SHDIAG = dcopy(2, FSHDIAG), FIOCLEX, (ioctl_t) 0);
    (void) ioctl(OLDSTD = dcopy(SHIN, FOLDSTD), FIOCLEX, (ioctl_t) 0);
E 51
I 51
    (void) ioctl(SHIN = dcopy(0, FSHIN), FIOCLEX, NULL);
    (void) ioctl(SHOUT = dcopy(1, FSHOUT), FIOCLEX, NULL);
D 54
    (void) ioctl(SHDIAG = dcopy(2, FSHDIAG), FIOCLEX, NULL);
E 54
I 54
    (void) ioctl(SHERR = dcopy(2, FSHERR), FIOCLEX, NULL);
E 54
    (void) ioctl(OLDSTD = dcopy(SHIN, FOLDSTD), FIOCLEX, NULL);
E 51
    closem();
E 48
}

I 48

void
E 48
I 20
#ifdef PROF
done(i)
#else
E 20
D 48
exit(i)
E 48
I 48
xexit(i)
E 48
I 20
#endif
E 20
D 48
	int i;
E 48
I 48
    int     i;
E 48
{
I 48
    untty();
    _exit(i);
}
E 48

D 48
	untty();
D 23
#ifdef PROF
D 20
	IEH3exit(i);
E 20
I 20
	monitor(0);
E 20
#else
E 23
	_exit(i);
E 48
I 48
static Char **
defaultpath()
{
    char   *ptr;
    Char  **blk, **blkp;
    struct stat stb;

    blkp = blk = (Char **) xmalloc((size_t) sizeof(Char *) * 10);

#define DIRAPPEND(a)  \
	if (stat(ptr = a, &stb) == 0 && (stb.st_mode & S_IFMT) == S_IFDIR) \
		*blkp++ = SAVE(ptr)

    DIRAPPEND(_PATH_BIN);
    DIRAPPEND(_PATH_USRBIN);

#undef DIRAPPEND

D 63
    *blkp++ = Strsave(STRdot);
E 63
I 63
    if (euid != 0 && uid != 0)
	*blkp++ = Strsave(STRdot);
E 63
D 51
    *blkp = (Char *) 0;
E 51
I 51
    *blkp = NULL;
E 51
    return (blk);
E 48
D 23
#endif
E 23
I 16
}

I 48
void
E 48
D 19
printprompt ()
E 19
I 19
printprompt()
E 19
{
D 19
    register char *cp;
    if (!whyles)
	for (cp = value ("prompt"); *cp; cp++)
	    if (*cp == HIST)
		printf ("%d", eventno + 1);
	    else
	    {
		if (*cp == '\\' && cp[1] == HIST)
		    cp++;
		putchar (*cp | QUOTE);
	    }
    else
    /* 
     * Prompt for forward reading loop
     * body content.
     */
	printf ("? ");
    flush ();
E 19
I 19
D 48
	register char *cp;
E 48
I 48
    register Char *cp;
E 48

D 20
	if (whyles) {
E 20
I 20
D 48
	if (!whyles) {
E 20
		for (cp = value("prompt"); *cp; cp++)
			if (*cp == HIST)
				printf("%d", eventno + 1);
			else {
				if (*cp == '\\' && cp[1] == HIST)
					cp++;
D 32
				putchar(*cp | QUOTE);
E 32
I 32
				cshputchar(*cp | QUOTE);
E 32
			}
	} else
		/* 
		 * Prompt for forward reading loop
		 * body content.
		 */
		printf("? ");
	flush();
E 48
I 48
    if (!whyles) {
	for (cp = value(STRprompt); *cp; cp++)
	    if (*cp == HIST)
D 54
		xprintf("%d", eventno + 1);
E 54
I 54
		(void) fprintf(cshout, "%d", eventno + 1);
E 54
	    else {
		if (*cp == '\\' && cp[1] == HIST)
		    cp++;
D 54
		xputchar(*cp | QUOTE);
E 54
I 54
D 60
		(void) fputc(*cp | QUOTE, cshout);
E 60
I 60
		(void) vis_fputc(*cp | QUOTE, cshout);
E 60
E 54
	    }
    }
    else
	/*
	 * Prompt for forward reading loop body content.
	 */
D 54
	xprintf("? ");
    flush();
E 54
I 54
	(void) fprintf(cshout, "? ");
    (void) fflush(cshout);
E 54
E 48
E 19
E 16
}
I 54
D 58

E 58
E 54
E 1
