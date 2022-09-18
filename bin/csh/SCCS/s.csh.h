h21996
s 00002/00002/00524
d D 8.2 95/04/29 13:09:06 christos 40 39
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00002/00002/00524
d D 8.1 93/05/31 16:41:34 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00525
d D 5.26 93/05/23 12:24:26 christos 38 37
c Removed comment reference to non-existing file local.h
e
s 00006/00000/00521
d D 5.25 93/05/22 19:06:20 christos 37 36
c Fixed gcc -Wall warnings
e
s 00006/00001/00515
d D 5.24 93/03/30 13:55:02 christos 36 35
c Changed f_seek to a union of off_t and Char* to avoid a ggc warning
e
s 00001/00000/00515
d D 5.23 92/05/28 16:30:38 mckusick 35 34
c need to include types.h for resource.h
e
s 00002/00006/00513
d D 5.22 92/05/15 00:13:31 christos 34 33
c get rid of useless SIGN_EXTEND_CHAR macro
e
s 00000/00007/00519
d D 5.21 92/02/12 20:07:55 christos 33 32
c Use the system's version of malloc
e
s 00002/00001/00524
d D 5.20 91/11/04 18:50:27 christos 32 31
c Couple of new variables...
e
s 00020/00003/00505
d D 5.19 91/08/30 21:23:41 christos 31 30
c Bugfix for loops in aliases.
e
s 00000/00005/00508
d D 5.18 91/08/04 17:36:29 christos 30 29
c Signal names from libc; /bin/kill compatible builtin
e
s 00002/00002/00511
d D 5.17 91/07/22 11:46:58 christos 29 28
c no short strings bug fix
e
s 00030/00028/00483
d D 5.16 91/07/19 17:30:28 christos 28 27
c stdio based version; brace glob fix; builtin prototypes
e
s 00007/00026/00504
d D 5.15 91/06/08 12:20:09 bostic 27 26
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00028/00001/00502
d D 5.14 91/06/07 20:57:12 christos 26 25
c static function prototypes
e
s 00036/00059/00467
d D 5.13 91/06/07 11:13:15 bostic 25 24
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00000/00003/00526
d D 5.12 91/06/05 16:33:20 christos 24 23
c Removed -DTELL V6 compatibility flag
e
s 00303/00243/00226
d D 5.11 91/06/04 13:31:36 bostic 23 22
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00464
d D 5.10 91/04/04 18:17:44 bostic 22 21
c new copyright; att/bsd/shared
e
s 00069/00074/00399
d D 5.9 91/04/01 17:37:14 bostic 21 20
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00002/00001/00471
d D 5.8 91/03/14 12:31:45 bostic 20 19
c lost the SCCS id's...
e
s 00007/00007/00465
d D 5.7 91/03/14 12:30:58 bostic 19 18
c use the library globbing routines instead of rolling our own 
c copy -> bcopy (more than vax and tahoe now)
e
s 00002/00002/00470
d D 5.6 91/02/25 08:11:53 bostic 18 17
c ANSI fixes
e
s 00002/00002/00470
d D 5.5 89/09/24 16:48:49 bostic 17 16
c POSIX signals
e
s 00000/00001/00472
d D 5.4 89/08/14 18:14:19 karels 16 15
c we've only got one tty discipline now.
e
s 00005/00000/00468
d D 5.3 86/03/29 07:36:58 lepreau 15 14
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00001/00001/00467
d D 5.2 85/06/06 13:09:19 edward 14 13
c cleaning up after bozos
e
s 00007/00001/00461
d D 5.1 85/06/04 11:11:04 dist 13 12
c Add copyright
e
s 00045/00025/00417
d D 4.12 84/12/13 14:42:52 edward 12 11
c performance
e
s 00000/00007/00442
d D 4.11 84/08/31 09:32:45 ralph 11 10
c use new signal calls instead of compatibility routines.
e
s 00002/00002/00447
d D 4.10 83/07/01 23:28:10 wnj 10 9
c include fixes
e
s 00006/00000/00443
d D 4.9 83/06/11 16:49:29 sam 9 8
c different approach, try signal compatibility package
e
s 00001/00000/00442
d D 4.8 83/06/11 00:00:56 sam 8 7
c new signals; no libjobs
e
s 00003/00003/00439
d D 4.7 83/02/09 14:17:19 sam 7 6
c cleanups from sun
e
s 00001/00001/00441
d D 4.6 83/02/03 09:12:47 sam 6 5
c use high precision time calls
e
s 00004/00012/00438
d D 4.5 82/12/30 17:35:07 sam 5 4
c finally works (updated for 4.1c and merged with sun)
e
s 00001/00001/00449
d D 4.4 82/05/07 18:23:10 mckusick 4 3
c update to new fs
e
s 00000/00001/00450
d D 4.3 82/02/12 14:27:16 mckusic 3 2
c convert to new directory format
e
s 00001/00000/00450
d D 4.2 81/11/19 21:03:57 mckusic 2 1
c add ``history -h >file'' and ``source -h file'' to 
c implement history save and restore.
e
s 00450/00000/00000
d D 4.1 80/10/09 12:41:08 bill 1 0
c date and time created 80/10/09 12:41:08 by bill
e
u
U
t
T
I 1
D 5
/* %M% %I% %G% */
E 5
I 5
D 12
/* %M% %I% %E% */
E 12
I 12
D 13
/* %W% (Berkeley) %G% */
E 13
I 13
D 22
/*
 * Copyright (c) 1980 Regents of the University of California.
D 14
 * All rights reserved.  The Berkeley software License Agreement
E 14
I 14
 * All rights reserved.  The Berkeley Software License Agreement
E 14
 * specifies the terms and conditions for redistribution.
E 22
I 22
/*-
D 39
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
 * %sccs.include.redist.c%
E 22
 *
D 19
 *	%W% (Berkeley) %G%
E 19
I 19
D 20
 *	@(#)sh.h	5.6 (Berkeley) 2/25/91
E 20
I 20
 *	%W% (Berkeley) %G%
E 20
E 19
 */
I 20

I 23
D 25
#ifdef SHORT_STRINGS
typedef short Char;

#define SAVE(a) (Strsave(str2short(a)))
#else
typedef char Char;

#define SAVE(a) (strsave(a))
#endif

typedef void *ioctl_t;		/* Third arg of ioctl */
typedef long sigmask_t;		/* What a signal mask is */

#include <sys/types.h>
E 25
E 23
E 20
E 13
E 12
E 5
D 19

E 19
I 19
D 27
#include <sys/param.h>
I 23
#include <sys/stat.h>
E 23
E 19
D 12
#include "sh.local.h"
E 12
D 5
#ifdef VMUNIX
#include <sys/vtimes.h>
#endif
E 5
I 5
D 10
#include <time.h>
#include <resource.h>
E 10
I 10
#include <sys/time.h>
#include <sys/resource.h>
I 12
D 19
#include <sys/param.h>
E 19
D 23
#include <sys/stat.h>
#include <sys/signal.h>
E 23
I 23
#include <sys/ioctl.h>
D 25
#include <sys/file.h>
E 25
I 25
#include <fcntl.h>
E 25

#ifdef NLS
#include <locale.h>
#endif
#include <time.h>
D 25
#include <unistd.h>
#include <stdlib.h>
E 25
#include <limits.h>
#include <termios.h>
E 23
#include <errno.h>
#include <setjmp.h>
I 23
#include <dirent.h>
#include <pwd.h>
I 25
#include <unistd.h>
#include <stdlib.h>
E 25
#include <string.h>
I 25
#include "pathnames.h"
E 25

E 27
I 26
/*
 * Fundamental definitions which may vary from system to system.
 *
 *	BUFSIZ		The i/o buffering size; also limits word size
 *	MAILINTVL	How often to mailcheck; more often is more expensive
 */
#ifndef BUFSIZ
#define	BUFSIZ	1024		/* default buffer size */
#endif				/* BUFSIZ */

#define FORKSLEEP	10	/* delay loop on non-interactive fork failure */
#define	MAILINTVL	600	/* 10 minutes */

/*
 * The shell moves std in/out/diag and the old std input away from units
 * 0, 1, and 2 so that it is easy to set up these standards for invoked
 * commands.
 */
#define	FSHTTY	15		/* /dev/tty when manip pgrps */
#define	FSHIN	16		/* Preferred desc for shell input */
#define	FSHOUT	17		/* ... shell output */
D 28
#define	FSHDIAG	18		/* ... shell diagnostics */
E 28
I 28
#define	FSHERR	18		/* ... shell diagnostics */
E 28
#define	FOLDSTD	19		/* ... old std input */

#ifdef PROF
#define	xexit(n)	done(n)
#endif

E 26
I 25
#ifdef SHORT_STRINGS
typedef short Char;

#define SAVE(a) (Strsave(str2short(a)))
#else
typedef char Char;

#define SAVE(a) (strsave(a))
#endif

I 37
/*
 * Make sure a variable is not stored in a register by taking its address
 * This is used where variables might be clobbered by longjmp.
 */
#define UNREGISTER(a)	(void) &a

E 37
typedef void *ioctl_t;		/* Third arg of ioctl */
D 27
typedef long sigmask_t;		/* What a signal mask is */
E 27

E 25
typedef void *ptr_t;

I 25
D 27
#include "tc.const.h"
E 27
I 27
#include "const.h"
E 27
D 26
#include "local.h"
E 26
#include "char.h"
#include "err.h"

E 25
D 33
#ifdef SYSMALLOC
E 33
D 25
#define xmalloc(i)  	Malloc(i)
E 25
I 25
#define xmalloc(i)	Malloc(i)
E 25
#define xrealloc(p, i)	Realloc(p, i)
#define xcalloc(n, s)	Calloc(n, s)
D 25
#define xfree(p)    	Free(p)
E 25
I 25
#define xfree(p)	Free(p)
E 25
D 33
#else
D 25
#define xmalloc(i)  	malloc(i)
E 25
I 25
#define xmalloc(i)	malloc(i)
E 25
#define xrealloc(p, i)	realloc(p, i)
#define xcalloc(n, s)	calloc(n, s)
D 25
#define xfree(p)    	free(p)
E 25
I 25
#define xfree(p)	free(p)
E 25
#endif				/* SYSMALLOC */
E 33

I 28
#include <stdio.h>
FILE *cshin, *cshout, *csherr;

E 28
D 25
#include "tc.const.h"

E 23
#include "sh.local.h"
I 15
#include "sh.char.h"
I 23
#include "sh.err.h"
#include "pathnames.h"
E 23
E 15
E 12
E 10
E 5

I 23

E 23
/*
 * C shell
 *
 * Bill Joy, UC Berkeley
 * October, 1978; May 1980
 *
 * Jim Kulp, IIASA, Laxenburg Austria
 * April, 1980
 */
D 4
#include <sys/types.h>
E 4
I 4
D 12
#include <sys/param.h>
E 4
#include <sys/stat.h>
E 12
D 3
#include <sys/dir.h>
E 3

E 25
D 21
#define	isdir(d)	((d.st_mode & S_IFMT) == S_IFDIR)

E 21
D 12
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/times.h>

E 12
D 23
typedef	char	bool;
E 23
I 23
#define	isdir(d)	((d.st_mode & S_IFMT) == S_IFDIR)
E 23

D 23
#define	eq(a, b)	(strcmp(a, b) == 0)
E 23
I 23
D 34
#define SIGN_EXTEND_CHAR(a) \
	((a) & 0x80 ? ((int) (a)) | 0xffffff00 : ((int) a) & 0x000000ff)
E 23
I 9

I 23

E 34
D 25

E 25
typedef int bool;

#define	eq(a, b)	(Strcmp(a, b) == 0)

/* globone() flags */
#define G_ERROR		0	/* default action: error if multiple words */
D 25
#define G_IGNORE	1	/* ignore the rest of the words		   */
#define G_APPEND	2	/* make a sentence by cat'ing the words    */
E 25
I 25
#define G_IGNORE	1	/* ignore the rest of the words */
#define G_APPEND	2	/* make a sentence by cat'ing the words */
E 25

E 23
/*
D 11
 * For 4.2bsd signals.
 */
E 9
I 8
#define	mask(s)		(1 << ((s)-1))
I 9
#define	sigsys(s, a)	signal(s, a)
#define	sighold(s)	sigblock(mask(s))
E 9
E 8

/*
E 11
 * Global flags
 */
D 23
bool	chkstop;		/* Warned of stopped jobs... allow exit */
D 12
bool	didcch;			/* Have closed unused fd's for child */
E 12
bool	didfds;			/* Have setup i/o fd's for child */
bool	doneinp;		/* EOF indicator after reset from readc */
bool	exiterr;		/* Exit if error or non-zero exit status */
bool	child;			/* Child shell ... errors cause exit */
bool	haderr;			/* Reset was because of an error */
bool	intty;			/* Input is a tty */
bool	intact;			/* We are interactive... therefore prompt */
bool	justpr;			/* Just print because of :p hist mod */
bool	loginsh;		/* We are a loginsh -> .login/.logout */
bool	neednote;		/* Need to pnotify() */
bool	noexec;			/* Don't execute, just syntax check */
bool	pjobs;			/* want to print jobs if interrupted */
bool	setintr;		/* Set interrupts on/off -> Wait intr... */
bool	timflg;			/* Time the next waited for command */
I 12
bool	havhash;		/* path hashing is available */
E 23
I 23
bool    chkstop;		/* Warned of stopped jobs... allow exit */
bool    didfds;			/* Have setup i/o fd's for child */
bool    doneinp;		/* EOF indicator after reset from readc */
bool    exiterr;		/* Exit if error or non-zero exit status */
bool    child;			/* Child shell ... errors cause exit */
bool    haderr;			/* Reset was because of an error */
bool    intty;			/* Input is a tty */
bool    intact;			/* We are interactive... therefore prompt */
bool    justpr;			/* Just print because of :p hist mod */
bool    loginsh;		/* We are a loginsh -> .login/.logout */
bool    neednote;		/* Need to pnotify() */
bool    noexec;			/* Don't execute, just syntax check */
bool    pjobs;			/* want to print jobs if interrupted */
bool    setintr;		/* Set interrupts on/off -> Wait intr... */
bool    timflg;			/* Time the next waited for command */
bool    havhash;		/* path hashing is available */

E 23
#ifdef FILEC
D 23
bool	filec;			/* doing filename expansion */
E 23
I 23
bool    filec;			/* doing filename expansion */
D 27

E 27
E 23
#endif
E 12

/*
 * Global i/o info
 */
D 23
char	*arginp;		/* Argument input for sh -c and internal `xx` */
int	onelflg;		/* 2 -> need line for -t, 1 -> exit on read */
char	*file;			/* Name of shell file for $0 */
E 23
I 23
Char   *arginp;			/* Argument input for sh -c and internal `xx` */
int     onelflg;		/* 2 -> need line for -t, 1 -> exit on read */
Char   *ffile;			/* Name of shell file for $0 */
E 23

D 23
char	*err;			/* Error message from scanner/parser */
int	errno;			/* Error from C library routines */
char	*shtemp;		/* Temp name for << shell files in /tmp */
D 6
time_t	time0;			/* Time at which the shell started */
E 6
I 6
struct	timeval time0;		/* Time at which the shell started */
E 6
I 5
struct	rusage ru0;
E 23
I 23
char   *seterr;			/* Error message from scanner/parser */
Char   *shtemp;			/* Temp name for << shell files in /tmp */
E 23
E 5

I 35
#include <sys/types.h>
E 35
I 27
#include <sys/time.h>
#include <sys/resource.h>

E 27
I 23
struct timeval time0;		/* Time at which the shell started */
struct rusage ru0;

E 23
/*
 * Miscellany
 */
D 23
char	*doldol;		/* Character pid for $$ */
int	uid;			/* Invokers uid */
time_t	chktim;			/* Time mail last checked */
D 7
short	shpgrp;			/* Pgrp of shell */
short	tpgrp;			/* Terminal process group */
E 7
I 7
int	shpgrp;			/* Pgrp of shell */
int	tpgrp;			/* Terminal process group */
E 23
I 23
Char   *doldol;			/* Character pid for $$ */
I 32
int	backpid;		/* Pid of the last background process */
E 32
D 34
int     uid;			/* Invokers uid */
int     gid;			/* Invokers gid */
E 34
I 34
int     uid, euid;		/* Invokers uid */
int     gid, egid;		/* Invokers gid */
E 34
time_t  chktim;			/* Time mail last checked */
int     shpgrp;			/* Pgrp of shell */
int     tpgrp;			/* Terminal process group */

E 23
E 7
/* If tpgrp is -1, leave tty alone! */
D 7
short	opgrp;			/* Initial pgrp and tty pgrp */
E 7
I 7
D 23
int	opgrp;			/* Initial pgrp and tty pgrp */
E 23
I 23
int     opgrp;			/* Initial pgrp and tty pgrp */
E 23
E 7
D 16
int	oldisc;			/* Initial line discipline or -1 */
E 16
D 12
struct	tms shtimes;		/* shell and child times for process timing */
E 12

D 28
/*
 * These are declared here because they want to be
 * initialized in sh.init.c (to allow them to be made readonly)
 */
E 28

D 21
struct	biltins {
E 21
I 21
D 23
struct biltins {
E 21
	char	*bname;
	int	(*bfunct)();
	short	minargs, maxargs;
} bfunc[];
E 23
I 23
D 28
extern struct biltins {
    char   *bname;
    void    (*bfunct) ();
    short   minargs, maxargs;
}       bfunc[];
E 23
I 12
extern int nbfunc;
E 12

D 12
#define	INF	1000

E 12
D 23
struct srch {
	char	*s_name;
	short	s_value;
} srchn[];
E 23
I 23
extern struct srch {
    char   *s_name;
    short   s_value;
}       srchn[];
E 23
I 12
extern int nsrchn;
E 12

E 28
/*
 * To be able to redirect i/o for builtins easily, the shell moves the i/o
 * descriptors it uses away from 0,1,2.
 * Ideally these should be in units which are closed across exec's
 * (this saves work) but for version 6, this is not usually possible.
D 38
 * The desired initial values for these descriptors are defined in
D 25
 * sh.local.h.
E 25
I 25
 * local.h.
E 38
I 38
 * The desired initial values for these descriptors are F{SHIN,...}.
E 38
E 25
 */
D 23
short	SHIN;			/* Current shell input (script) */
short	SHOUT;			/* Shell output */
short	SHDIAG;			/* Diagnostic output... shell errs go here */
short	OLDSTD;			/* Old standard input (def for cmds) */
E 23
I 23
D 28
short   SHIN;			/* Current shell input (script) */
short   SHOUT;			/* Shell output */
short   SHDIAG;			/* Diagnostic output... shell errs go here */
short   OLDSTD;			/* Old standard input (def for cmds) */
E 28
I 28
int   SHIN;			/* Current shell input (script) */
int   SHOUT;			/* Shell output */
int   SHERR;			/* Diagnostic output... shell errs go here */
int   OLDSTD;			/* Old standard input (def for cmds) */
E 28
E 23

/*
 * Error control
 *
 * Errors in scanning and parsing set up an error message to be printed
 * at the end and complete.  Other errors always cause a reset.
 * Because of source commands and .cshrc we need nested error catches.
 */

I 27
#include <setjmp.h>
E 27
D 23
jmp_buf	reslab;
E 23
I 23
jmp_buf reslab;
E 23

D 12
#define	setexit()	setjmp(reslab)
#define	reset()		longjmp(reslab)
E 12
I 12
D 21
#define	setexit()	((void) setjmp(reslab))
#define	reset()		longjmp(reslab, 0)
E 12
	/* Should use structure assignment here */
D 19
#define	getexit(a)	copy((char *)(a), (char *)reslab, sizeof reslab)
#define	resexit(a)	copy((char *)reslab, ((char *)(a)), sizeof reslab)
E 19
I 19
#define	getexit(a)	bcopy((char *)reslab, (char *)(a), sizeof reslab)
#define	resexit(a)	bcopy(((char *)(a)), (char *)reslab, sizeof reslab)
E 21
I 21
D 23
/* Should use structure assignment here. */
#define	getexit(a)	bcopy((void *)reslab, (void *)(a), sizeof(reslab))
#define	resexit(a)	bcopy(((void *)(a)), (void *)reslab, sizeof(reslab))
E 23
I 23
#define	setexit()	(setjmp(reslab))
#define	reset()		longjmp(reslab, 1)
 /* Should use structure assignment here */
D 40
#define	getexit(a)	bcopy((char *)reslab, ((char *)(a)), sizeof reslab)
#define	resexit(a)	bcopy((char *)(a), (char *)reslab, sizeof reslab)
E 40
I 40
#define	getexit(a)	memmove((a), reslab, sizeof reslab)
#define	resexit(a)	memmove(reslab, (a), sizeof reslab)
E 40
E 23
E 21
E 19

D 23
char	*gointr;		/* Label for an onintr transfer */
D 17
int	(*parintr)();		/* Parents interrupt catch */
int	(*parterm)();		/* Parents terminate catch */
E 17
I 17
sig_t	parintr;		/* Parents interrupt catch */
sig_t	parterm;		/* Parents terminate catch */
E 23
I 23
Char   *gointr;			/* Label for an onintr transfer */
E 23
E 17

I 27
#include <signal.h>
E 27
I 23
sig_t parintr;			/* Parents interrupt catch */
sig_t parterm;			/* Parents terminate catch */

E 23
/*
 * Lexical definitions.
 *
 * All lexical space is allocated dynamically.
D 23
 * The eighth bit of characters is used to prevent recognition,
E 23
I 23
D 29
 * The eighth/sizteenth bit of characters is used to prevent recognition,
E 29
I 29
 * The eighth/sixteenth bit of characters is used to prevent recognition,
E 29
E 23
 * and eventually stripped.
 */
D 23
#define	QUOTE 	0200		/* Eighth char bit used internally for 'ing */
#define	TRIM	0177		/* Mask to strip quote bit */
E 23
I 23
#define	META		0200
#define	ASCII		0177
#ifdef SHORT_STRINGS
#define	CHAR		0377
#define	QUOTE 		0100000	/* 16nth char bit used for 'ing */
#define	TRIM		0077777	/* Mask to strip quote bit */
#else
#define	CHAR		0177
#define	QUOTE 		0200	/* Eighth char bit used for 'ing */
#define	TRIM		0177	/* Mask to strip quote bit */
#endif
E 23

I 23
int     AsciiOnly;		/* If set only 7 bits is expected in characters */

E 23
/*
 * Each level of input has a buffered input structure.
 * There are one or more blocks of buffered input for each level,
 * exactly one if the input is seekable and tell is available.
 * In other cases, the shell buffers enough blocks to keep all loops
 * in the buffer.
 */
D 21
struct	Bin {
E 21
I 21
struct Bin {
E 21
D 23
	off_t	Bfseekp;		/* Seek pointer */
	off_t	Bfbobp;			/* Seekp of beginning of buffers */
	off_t	Bfeobp;			/* Seekp of end of buffers */
	short	Bfblocks;		/* Number of buffer blocks */
	char	**Bfbuf;		/* The array of buffer blocks */
} B;
E 23
I 23
    off_t   Bfseekp;		/* Seek pointer */
    off_t   Bfbobp;		/* Seekp of beginning of buffers */
    off_t   Bfeobp;		/* Seekp of end of buffers */
D 28
    short   Bfblocks;		/* Number of buffer blocks */
E 28
I 28
    int     Bfblocks;		/* Number of buffer blocks */
E 28
    Char  **Bfbuf;		/* The array of buffer blocks */
}       B;
E 23

I 31
/*
 * This structure allows us to seek inside aliases
 */
struct Ain {
    int type;
#define I_SEEK -1		/* Invalid seek */
#define A_SEEK	0		/* Alias seek */
#define F_SEEK	1		/* File seek */
#define E_SEEK	2		/* Eval seek */
D 36
    off_t f_seek;
E 36
I 36
    union {
	off_t _f_seek;
	Char* _c_seek;
    } fc;
#define f_seek fc._f_seek
#define c_seek fc._c_seek
E 36
    Char **a_seek;
} ;
extern int aret;		/* What was the last character returned */
#define SEEKEQ(a, b) ((a)->type == (b)->type && \
		      (a)->f_seek == (b)->f_seek && \
		      (a)->a_seek == (b)->a_seek)

E 31
#define	fseekp	B.Bfseekp
#define	fbobp	B.Bfbobp
#define	feobp	B.Bfeobp
#define	fblocks	B.Bfblocks
#define	fbuf	B.Bfbuf

I 15
D 25
#define btell()	fseekp

E 25
D 23
#ifndef btell
E 15
off_t	btell();
I 15
#endif
E 15

E 23
/*
 * The shell finds commands in loops by reseeking the input
 * For whiles, in particular, it reseeks to the beginning of the
 * line the while was on; hence the while placement restrictions.
 */
D 23
off_t	lineloc;
E 23
I 23
D 31
off_t   lineloc;
E 31
I 31
struct Ain lineloc;
E 31
E 23

D 24
#ifdef	TELL
E 24
D 12
off_t	tell();
E 12
D 23
bool	cantell;			/* Is current source tellable ? */
#endif
E 23
I 23
bool    cantell;		/* Is current source tellable ? */
E 23
D 24

I 23
#endif				/* TELL */
E 24

E 23
/*
 * Input lines are parsed into doubly linked circular
 * lists of words of the following form.
 */
D 21
struct	wordent {
E 21
I 21
struct wordent {
E 21
D 23
	char	*word;
	struct	wordent *prev;
	struct	wordent *next;
E 23
I 23
    Char   *word;
    struct wordent *prev;
    struct wordent *next;
E 23
};

/*
 * During word building, both in the initial lexical phase and
 * when expanding $ variable substitutions, expansion by `!' and `$'
 * must be inhibited when reading ahead in routines which are themselves
 * processing `!' and `$' expansion or after characters such as `\' or in
 * quotations.  The following flags are passed to the getC routines
 * telling them which of these substitutions are appropriate for the
 * next character to be returned.
 */
#define	DODOL	1
#define	DOEXCL	2
#define	DOALL	DODOL|DOEXCL

/*
 * Labuf implements a general buffer for lookahead during lexical operations.
D 21
 * Text which is to be placed in the input stream can be stuck here.
 * We stick parsed ahead $ constructs during initial input,
 * process id's from `$$', and modified variable values (from qualifiers
 * during expansion in sh.dol.c) here.
E 21
I 21
D 23
 * Text which is to be placed in the input stream can be stuck here.  We stick
 * parsed ahead $ constructs during initial input, process id's from `$$',
 * and modified variable values (from qualifiers during expansion in sh.dol.c)
 * here.
E 23
I 23
 * Text which is to be placed in the input stream can be stuck here.
 * We stick parsed ahead $ constructs during initial input,
 * process id's from `$$', and modified variable values (from qualifiers
 * during expansion in sh.dol.c) here.
E 23
E 21
 */
D 5
#ifdef VMUNIX
E 5
D 23
char	labuf[BUFSIZ];
E 23
I 23
Char   *lap;
E 23
D 5
#else
char	labuf[256];
#endif
E 5

D 23
char	*lap;

E 23
/*
 * Parser structure
 *
D 21
 * Each command is parsed to a tree of command structures and
 * flags are set bottom up during this process, to be propagated down
 * as needed during the semantics/exeuction pass (sh.sem.c).
E 21
I 21
D 23
 * Each command is parsed to a tree of command structures and flags are set
 * bottom up during this process, to be propagated down as needed during the
 * semantics/exeuction pass (sh.sem.c).
E 23
I 23
 * Each command is parsed to a tree of command structures and
 * flags are set bottom up during this process, to be propagated down
 * as needed during the semantics/exeuction pass (sh.sem.c).
E 23
E 21
 */
D 23
struct	command {
D 21
	short	t_dtyp;				/* Type of node */
	short	t_dflg;				/* Flags, e.g. FAND|... */
E 21
I 21
#define	NODE_COMMAND	1		/* t_dcom <t_dlef >t_drit	*/
#define	NODE_PAREN	2		/* ( t_dspr ) <t_dlef >t_drit	*/
#define	NODE_PIPE	3		/* t_dlef | t_drit		*/
#define	NODE_LIST	4		/* t_dlef ; t_drit		*/
#define	NODE_OR		5		/* t_dlef || t_drit		*/
#define	NODE_AND	6		/* t_dlef && t_drit		*/
	short t_dtyp;			/* Node type */
E 23
I 23
struct command {
    short   t_dtyp;		/* Type of node 		 */
#define	NODE_COMMAND	1	/* t_dcom <t_dlef >t_drit	 */
#define	NODE_PAREN	2	/* ( t_dspr ) <t_dlef >t_drit	 */
#define	NODE_PIPE	3	/* t_dlef | t_drit		 */
#define	NODE_LIST	4	/* t_dlef ; t_drit		 */
#define	NODE_OR		5	/* t_dlef || t_drit		 */
#define	NODE_AND	6	/* t_dlef && t_drit		 */
    short   t_dflg;		/* Flags, e.g. F_AMPERSAND|... 	 */
#define	F_SAVE	(F_NICE|F_TIME|F_NOHUP)	/* save these when re-doing 	 */
E 23

D 23
#define	F_SAVE	(F_NICE|F_TIME|F_NOHUP)	/* save these when re-doing */

#define	F_AMPERSAND	0x0001		/* executes in background	*/
#define	F_APPEND	0x0002		/* output is redirected >>	*/
#define	F_NICE		0x0004		/* t_nice is meaningful */
#define	F_NOFORK	0x0008		/* don't fork, last ()ized cmd	*/
#define	F_NOHUP		0x0010		/* nohup this command */
#define	F_NOINTERRUPT	0x0020		/* should be immune from intr's */
#define	F_OVERWRITE	0x0040		/* output was !			*/
#define	F_PIPEIN	0x0080		/* input is a pipe		*/
#define	F_PIPEOUT	0x0100		/* output is a pipe		*/
#define	F_READ		0x0200		/* input redirection is <<	*/
#define	F_REPEAT	0x0400		/* reexec aft if, repeat,...	*/
#define	F_STDERR	0x0800		/* redirect unit 2 with unit 1	*/
#define	F_TIME		0x1000		/* time this command */
	short t_dflg;			/* flags */

E 21
	union {
D 21
		char	*T_dlef;		/* Input redirect word */
		struct	command *T_dcar;	/* Left part of list/pipe */
E 21
I 21
		char *T_dlef;		/* Input redirect word */
		struct command *T_dcar;	/* Left part of list/pipe */
E 21
	} L;
	union {
D 21
		char	*T_drit;		/* Output redirect word */
		struct	command *T_dcdr;	/* Right part of list/pipe */
E 21
I 21
		char *T_drit;		/* Output redirect word */
		struct command *T_dcdr;	/* Right part of list/pipe */
E 21
	} R;
E 23
I 23
#define	F_AMPERSAND	(1<<0)	/* executes in background	 */
#define	F_APPEND	(1<<1)	/* output is redirected >>	 */
#define	F_PIPEIN	(1<<2)	/* input is a pipe		 */
#define	F_PIPEOUT	(1<<3)	/* output is a pipe		 */
#define	F_NOFORK	(1<<4)	/* don't fork, last ()ized cmd	 */
#define	F_NOINTERRUPT	(1<<5)	/* should be immune from intr's */
/* spare */
#define	F_STDERR	(1<<7)	/* redirect unit 2 with unit 1	 */
#define	F_OVERWRITE	(1<<8)	/* output was !			 */
#define	F_READ		(1<<9)	/* input redirection is <<	 */
#define	F_REPEAT	(1<<10)	/* reexec aft if, repeat,...	 */
#define	F_NICE		(1<<11)	/* t_nice is meaningful 	 */
#define	F_NOHUP		(1<<12)	/* nohup this command 		 */
#define	F_TIME		(1<<13)	/* time this command 		 */
    union {
	Char   *T_dlef;		/* Input redirect word 		 */
	struct command *T_dcar;	/* Left part of list/pipe 	 */
    }       L;
    union {
	Char   *T_drit;		/* Output redirect word 	 */
	struct command *T_dcdr;	/* Right part of list/pipe 	 */
    }       R;
E 23
#define	t_dlef	L.T_dlef
#define	t_dcar	L.T_dcar
#define	t_drit	R.T_drit
#define	t_dcdr	R.T_dcdr
D 21
	char	**t_dcom;			/* Command/argument vector */
	struct	command *t_dspr;		/* Pointer to ()'d subtree */
	short	t_nice;
E 21
I 21
D 23
	char **t_dcom;			/* Command/argument vector */
	struct command *t_dspr;		/* Pointer to ()'d subtree */
	short t_nice;
E 23
I 23
    Char  **t_dcom;		/* Command/argument vector 	 */
    struct command *t_dspr;	/* Pointer to ()'d subtree 	 */
D 28
    short   t_nice;
E 28
I 28
    int   t_nice;
E 28
E 23
E 21
};

D 21
#define	TCOM	1		/* t_dcom <t_dlef >t_drit	*/
#define	TPAR	2		/* ( t_dspr ) <t_dlef >t_drit	*/
#define	TFIL	3		/* t_dlef | t_drit		*/
#define	TLST	4		/* t_dlef ; t_drit		*/
#define	TOR	5		/* t_dlef || t_drit		*/
#define	TAND	6		/* t_dlef && t_drit		*/
E 21
I 21
D 23
/* Parser tokens. */
E 23
I 23

/*
I 28
 * These are declared here because they want to be
 * initialized in sh.init.c (to allow them to be made readonly)
 */

extern struct biltins {
    char   *bname;
    void    (*bfunct) __P((Char **, struct command *));
    short   minargs, maxargs;
}       bfunc[];
extern int nbfunc;

extern struct srch {
    char   *s_name;
    short   s_value;
}       srchn[];
extern int nsrchn;

/*
E 28
 * The keywords for the parser
 */
E 23
#define	T_BREAK		0
#define	T_BRKSW		1
#define	T_CASE		2
#define	T_DEFAULT 	3
#define	T_ELSE		4
#define	T_END		5
#define	T_ENDIF		6
#define	T_ENDSW		7
#define	T_EXIT		8
#define	T_FOREACH	9
#define	T_GOTO		10
#define	T_IF		11
#define	T_LABEL		12
#define	T_LET		13
#define	T_SET		14
#define	T_SWITCH	15
#define	T_TEST		16
#define	T_THEN		17
#define	T_WHILE		18
E 21

D 21
#define	FSAVE	(FNICE|FTIME|FNOHUP)	/* save these when re-doing */

#define	FAND	(1<<0)		/* executes in background	*/
#define	FCAT	(1<<1)		/* output is redirected >>	*/
#define	FPIN	(1<<2)		/* input is a pipe		*/
#define	FPOU	(1<<3)		/* output is a pipe		*/
#define	FPAR	(1<<4)		/* don't fork, last ()ized cmd	*/
#define	FINT	(1<<5)		/* should be immune from intr's */
/* spare */
#define	FDIAG	(1<<7)		/* redirect unit 2 with unit 1	*/
#define	FANY	(1<<8)		/* output was !			*/
#define	FHERE	(1<<9)		/* input redirection is <<	*/
#define	FREDO	(1<<10)		/* reexec aft if, repeat,...	*/
#define	FNICE	(1<<11)		/* t_nice is meaningful */
#define	FNOHUP	(1<<12)		/* nohup this command */
#define	FTIME	(1<<13)		/* time this command */

E 21
/*
D 21
 * The keywords for the parser
 */
#define	ZBREAK		0
#define	ZBRKSW		1
#define	ZCASE		2
#define	ZDEFAULT 	3
#define	ZELSE		4
#define	ZEND		5
#define	ZENDIF		6
#define	ZENDSW		7
#define	ZEXIT		8
#define	ZFOREACH	9
#define	ZGOTO		10
#define	ZIF		11
#define	ZLABEL		12
#define	ZLET		13
#define	ZSET		14
#define	ZSWITCH		15
#define	ZTEST		16
#define	ZTHEN		17
#define	ZWHILE		18

/*
E 21
 * Structure defining the existing while/foreach loops at this
 * source level.  Loops are implemented by seeking back in the
 * input.  For foreach (fe), the word list is attached here.
 */
D 23
struct	whyle {
	off_t	w_start;		/* Point to restart loop */
	off_t	w_end;			/* End of loop (0 if unknown) */
	char	**w_fe, **w_fe0;	/* Current/initial wordlist for fe */
	char	*w_fename;		/* Name for fe */
	struct	whyle *w_next;		/* Next (more outer) loop */
} *whyles;
E 23
I 23
struct whyle {
D 31
    off_t   w_start;		/* Point to restart loop */
    off_t   w_end;		/* End of loop (0 if unknown) */
E 31
I 31
    struct Ain   w_start;	/* Point to restart loop */
    struct Ain   w_end;		/* End of loop (0 if unknown) */
E 31
    Char  **w_fe, **w_fe0;	/* Current/initial wordlist for fe */
    Char   *w_fename;		/* Name for fe */
    struct whyle *w_next;	/* Next (more outer) loop */
}      *whyles;
E 23

/*
 * Variable structure
 *
D 12
 * Lists of aliases and variables are sorted alphabetically by name
E 12
I 12
 * Aliases and variables are stored in AVL balanced binary trees.
E 12
 */
D 23
struct	varent {
	char	**vec;		/* Array of words which is the value */
D 12
	char	*name;		/* Name of variable/alias */
	struct	varent *link;
E 12
I 12
	char	*v_name;	/* Name of variable/alias */
	struct	varent *v_link[3];	/* The links, see below */
	int	v_bal;		/* Balance factor */
E 12
} shvhed, aliases;
E 23
I 23
struct varent {
    Char  **vec;		/* Array of words which is the value */
    Char   *v_name;		/* Name of variable/alias */
    struct varent *v_link[3];	/* The links, see below */
    int     v_bal;		/* Balance factor */
}       shvhed, aliases;

E 23
I 12
#define v_left		v_link[0]
#define v_right		v_link[1]
#define v_parent	v_link[2]
E 12

I 12
struct varent *adrof1();
I 23

E 23
#define adrof(v)	adrof1(v, &shvhed)
#define value(v)	value1(v, &shvhed)

E 12
/*
 * The following are for interfacing redo substitution in
 * aliases to the lexical routines.
 */
D 23
struct	wordent *alhistp;		/* Argument list (first) */
struct	wordent *alhistt;		/* Node after last in arg list */
char	**alvec;			/* The (remnants of) alias vector */
E 23
I 23
struct wordent *alhistp;	/* Argument list (first) */
struct wordent *alhistt;	/* Node after last in arg list */
D 32
Char  **alvec;			/* The (remnants of) alias vector */
E 32
I 32
Char  **alvec, *alvecp;		/* The (remnants of) alias vector */
E 32
E 23

/*
 * Filename/command name expansion variables
 */
D 23
short	gflag;				/* After tglob -> is globbing needed? */
E 23
I 23
D 28
short   gflag;			/* After tglob -> is globbing needed? */
E 28
I 28
int   gflag;			/* After tglob -> is globbing needed? */
E 28
E 23

D 23
/*
 * A reasonable limit on number of arguments would seem to be
 * the maximum number of characters in an arg list / 6.
 */
#define	GAVSIZ	NCARGS / 6
E 23
I 23
#define MAXVARLEN 30		/* Maximum number of char in a variable name */
E 23

/*
 * Variables for filename expansion
 */
D 23
char	**gargv;			/* Pointer to the (stack) arglist */
short	gargc;				/* Number args in gargv */
E 23
I 23
extern Char **gargv;		/* Pointer to the (stack) arglist */
extern long gargc;		/* Number args in gargv */
E 23
D 19
short	gnleft;
E 19

/*
 * Variables for command expansion.
 */
D 23
char	**pargv;			/* Pointer to the argv list space */
char	*pargs;				/* Pointer to start current word */
short	pargc;				/* Count of arguments in pargv */
short	pnleft;				/* Number of chars left in pargs */
char	*pargcp;			/* Current index into pargs */
E 23
I 23
extern Char **pargv;		/* Pointer to the argv list space */
extern long pargc;		/* Count of arguments in pargv */
Char   *pargs;			/* Pointer to start current word */
long    pnleft;			/* Number of chars left in pargs */
Char   *pargcp;			/* Current index into pargs */
E 23

/*
 * History list
 *
 * Each history list entry contains an embedded wordlist
 * from the scanner, a number for the event, and a reference count
 * to aid in discarding old entries.
 *
 * Essentially "invisible" entries are put on the history list
 * when history substitution includes modifiers, and thrown away
 * at the next discarding since their event numbers are very negative.
 */
D 23
struct	Hist {
	struct	wordent Hlex;
	int	Hnum;
	int	Href;
	struct	Hist *Hnext;
} Histlist;
E 23
I 23
struct Hist {
    struct wordent Hlex;
    int     Hnum;
    int     Href;
D 28
    long    Htime;
E 28
    struct Hist *Hnext;
}       Histlist;
E 23

D 23
struct	wordent	paraml;			/* Current lexical word list */
int	eventno;			/* Next events number */
int	lastev;				/* Last event reference (default) */
E 23
I 23
struct wordent paraml;		/* Current lexical word list */
int     eventno;		/* Next events number */
int     lastev;			/* Last event reference (default) */
E 23

D 23
char	HIST;				/* history invocation character */
char	HISTSUB;			/* auto-substitute character */
E 23
I 23
Char    HIST;			/* history invocation character */
Char    HISTSUB;		/* auto-substitute character */
E 23

I 12
/*
D 23
 * In lines for frequently called functions
E 23
I 23
 * strings.h:
E 23
 */
D 23
#define XFREE(cp) { \
	extern char end[]; \
	char stack; \
	if ((cp) >= end && (cp) < &stack) \
		free(cp); \
}
char	*alloctmp;
D 21
#define xalloc(i) ((alloctmp = malloc(i)) ? alloctmp : (char *)nomem(i))
I 19
#define xrealloc(p, i) ((alloctmp = realloc(p, i)) ? alloctmp : (char *)nomem(i))
E 21
I 21
#define xalloc(i) \
	((alloctmp = malloc(i)) ? alloctmp : (char *)nomem(i))
#define xrealloc(p, i) \
	((alloctmp = realloc(p, i)) ? alloctmp : (char *)nomem(i))
E 23
I 23
#ifndef SHORT_STRINGS
D 25
#define Strchr(a, b)  		strchr(a, b)
#define Strrchr(a, b)  	strrchr(a, b)
#define Strcat(a, b)  		strcat(a, b)
E 25
I 25
#define Strchr(a, b)		strchr(a, b)
#define Strrchr(a, b)		strrchr(a, b)
#define Strcat(a, b)		strcat(a, b)
E 25
#define Strncat(a, b, c) 	strncat(a, b, c)
D 25
#define Strcpy(a, b)  		strcpy(a, b)
E 25
I 25
#define Strcpy(a, b)		strcpy(a, b)
E 25
#define Strncpy(a, b, c) 	strncpy(a, b, c)
#define Strlen(a)		strlen(a)
#define Strcmp(a, b)		strcmp(a, b)
#define Strncmp(a, b, c)	strncmp(a, b, c)
E 23
E 21
E 19

E 12
D 23
char	*Dfix1();
D 12
struct	varent *adrof(), *adrof1();
E 12
char	**blkcat();
char	**blkcpy();
char	**blkend();
char	**blkspl();
char	*calloc();
I 12
char	*malloc();
I 19
char	*realloc();
E 19
E 12
char	*cname();
char	**copyblk();
char	**dobackp();
char	*domod();
struct	wordent *dosub();
char	*exp3();
char	*exp3a();
char	*exp4();
char	*exp5();
char	*exp6();
struct	Hist *enthist();
struct	Hist *findev();
struct	wordent *freenod();
char	*getenv();
char	*getinx();
struct	varent *getvx();
struct	passwd *getpwnam();
struct	wordent *gethent();
struct	wordent *getsub();
char	*getwd();
I 12
D 19
char	**glob();
E 19
I 19
char	**globall();
E 19
E 12
char	*globone();
I 12
char	*index();
E 12
struct	biltins *isbfunc();
D 12
char	**glob();
E 12
I 12
off_t	lseek();
E 12
char	*operate();
I 2
int	phup();
E 2
D 18
int	pintr();
int	pchild();
E 18
I 18
void	pintr();
void	pchild();
E 18
char	*putn();
I 12
char	*rindex();
E 12
char	**saveblk();
char	*savestr();
char	*strcat();
char	*strcpy();
char	*strend();
char	*strings();
char	*strip();
char	*strspl();
char	*subword();
struct	command *syntax();
struct	command *syn0();
struct	command *syn1();
struct	command *syn1a();
struct	command *syn1b();
struct	command *syn2();
struct	command *syn3();
D 12
int	tglob();
int	trim();
char	*value(), *value1();
E 12
I 12
char	*value1();
E 12
char	*xhome();
char	*xname();
char	*xset();
E 23
I 23
#define Strspl(a, b)		strspl(a, b)
#define Strsave(a)		strsave(a)
#define Strend(a)		strend(a)
#define Strstr(a, b)		strstr(a, b)
E 23

D 23
#define	NOSTR	((char *) 0)
E 23
I 23
#define str2short(a) 		(a)
#define blk2short(a) 		saveblk(a)
#define short2blk(a) 		saveblk(a)
D 28
#define short2str(a) 		(a)
#define short2qstr(a)		(a)
E 28
I 28
D 29
#define short2str(a) 		trim(a)
E 29
I 29
#define short2str(a) 		strip(a)
E 29
E 28
#else
D 25
#define Strchr(a, b)   	s_strchr(a, b)
E 25
I 25
#define Strchr(a, b)		s_strchr(a, b)
E 25
#define Strrchr(a, b) 		s_strrchr(a, b)
D 25
#define Strcat(a, b)  		s_strcat(a, b)
E 25
I 25
#define Strcat(a, b)		s_strcat(a, b)
E 25
#define Strncat(a, b, c) 	s_strncat(a, b, c)
D 25
#define Strcpy(a, b)  		s_strcpy(a, b)
E 25
I 25
#define Strcpy(a, b)		s_strcpy(a, b)
E 25
#define Strncpy(a, b, c)	s_strncpy(a, b, c)
#define Strlen(a)		s_strlen(a)
#define Strcmp(a, b)		s_strcmp(a, b)
#define Strncmp(a, b, c)	s_strncmp(a, b, c)
E 23

I 23
#define Strspl(a, b)		s_strspl(a, b)
#define Strsave(a)		s_strsave(a)
#define Strend(a)		s_strend(a)
#define Strstr(a, b)		s_strstr(a, b)
#endif

E 23
/*
 * setname is a macro to save space (see sh.err.c)
 */
D 23
char	*bname;
E 23
I 23
char   *bname;

E 23
D 12
#define	setname(a)	bname = (a);
E 12
I 12
#define	setname(a)	(bname = (a))
E 12

D 25
#ifdef VFORK
E 25
D 23
char	*Vsav;
char	**Vav;
char	*Vdp;
E 23
I 23
Char   *Vsav;
Char   *Vdp;
Char   *Vexpath;
char  **Vt;

D 25
#endif				/* VFORK */

E 25
Char  **evalvec;
Char   *evalp;

D 30
extern struct mesg {
    char   *iname;		/* name from /usr/include */
    char   *pname;		/* print name */
}       mesg[];

E 30
/* word_chars is set by default to WORD_CHARS but can be overridden by
   the worchars variable--if unset, reverts to WORD_CHARS */

Char   *word_chars;

#define WORD_CHARS "*?_-.[]~="	/* default chars besides alnums in words */

Char   *STR_SHELLPATH;

I 27
#include <paths.h>
E 27
#ifdef _PATH_BSHELL
Char   *STR_BSHELL;
D 27

E 27
E 23
D 5
#endif

#ifdef VMUNIX
struct	vtimes zvms;
E 5
#endif
I 23
Char   *STR_WORD_CHARS;
Char  **STR_environ;
E 23
D 25

D 23
char	**evalvec;
char	*evalp;
E 23
I 23
#include "sh.decls.h"
E 23

D 23
struct	mesg {
	char	*iname;		/* name from /usr/include */
	char	*pname;		/* print name */
} mesg[];
E 23
I 23
extern char *getwd();
E 25
E 23
E 1
