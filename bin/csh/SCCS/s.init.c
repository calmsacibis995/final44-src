h63560
s 00002/00002/00107
d D 8.1 93/05/31 16:42:24 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00077/00076/00032
d D 5.16 93/05/22 19:06:37 christos 23 22
c Fixed gcc -Wall warnings
e
s 00000/00036/00108
d D 5.15 91/08/04 17:36:31 christos 22 21
c Signal names from libc; /bin/kill compatible builtin
e
s 00002/00000/00142
d D 5.14 91/07/28 14:14:23 christos 21 20
c Added dowhich() and doprintf() builtins.
e
s 00000/00000/00142
d D 5.13 91/07/19 17:31:06 christos 20 19
c stdio based version; brace glob fix; builtin prototypes
e
s 00000/00000/00142
d D 5.12 91/06/26 23:41:38 christos 19 18
c unsetenv can take more than one pattern
e
s 00006/00000/00136
d D 5.11 91/06/08 17:08:51 christos 18 17
c More prototype fixes, Removed TERMIOS define
e
s 00000/00001/00136
d D 5.10 91/06/07 20:57:29 christos 17 16
c static function prototypes
e
s 00003/00004/00134
d D 5.9 91/06/07 11:13:31 bostic 16 15
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00116/00173/00022
d D 5.8 91/06/04 13:31:40 bostic 15 14
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00188
d D 5.7 91/04/04 18:17:47 bostic 14 13
c new copyright; att/bsd/shared
e
s 00017/00017/00177
d D 5.6 91/04/01 17:37:15 bostic 13 12
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00004/00034/00190
d D 5.5 91/03/18 12:05:17 bostic 12 11
c this can be simplified a lot by including sh.h.
e
s 00000/00015/00224
d D 5.4 89/02/15 11:06:45 bostic 11 10
c use pathname include files; remove IIASA commands; remove newgrp
c command; add globall .cshrc, .login, and .logout files; minor cleanups
e
s 00004/00004/00235
d D 5.3 87/09/16 14:47:51 bostic 10 9
c use "Suspended", not "Stopped"; bug report 4.3BSD/bin/56
e
s 00003/00003/00236
d D 5.2 85/06/06 13:09:56 edward 9 8
c cleaning up after bozos
e
s 00008/00002/00231
d D 5.1 85/06/04 11:02:49 dist 8 7
c Add copyright
e
s 00001/00001/00232
d D 4.7 85/06/01 16:55:45 edward 7 6
c allow setenv with 0 and 1 arugments:
c 	setenv -> printenv
c 	setenv x -> setenv x ''
e
s 00002/00002/00231
d D 4.6 85/05/22 19:27:43 mckusick 6 5
c add SIGUSR1 and SIGUSR2
e
s 00001/00001/00232
d D 4.5 85/01/30 12:10:42 edward 5 4
c SIGWINCH added
e
s 00009/00009/00224
d D 4.4 84/12/13 14:40:22 edward 4 3
c performance
e
s 00004/00000/00229
d D 4.3 83/06/11 00:01:04 sam 3 2
c new signals; no libjobs
e
s 00001/00001/00228
d D 4.2 81/08/20 23:47:48 mckusic 2 1
c put in history save and restore
e
s 00229/00000/00000
d D 4.1 80/10/09 12:41:13 bill 1 0
c date and time created 80/10/09 12:41:13 by bill
e
u
U
t
T
I 8
D 14
/*
 * Copyright (c) 1980 Regents of the University of California.
D 9
 * All rights reserved.  The Berkeley software License Agreement
E 9
I 9
 * All rights reserved.  The Berkeley Software License Agreement
E 9
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 24
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
 * %sccs.include.redist.c%
E 14
 */

E 8
I 1
D 4
static	char *sccsid = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
I 23
/*###9 [cc] warning: `sccsid' defined but not used%%%*/
E 23
D 8
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 8
I 8
D 9
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 9
I 9
D 14
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 14
I 14
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 14
E 9
E 8
E 4

I 18
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 18
D 12
#include "sh.local.h"
E 12
I 12
D 16
#include "sh.h"
I 15
#include "sh.local.h"
E 16
I 16
#include "csh.h"
D 17
#include "local.h"
E 17
#include "extern.h"
E 16
E 15
E 12

D 15
/*
 * C shell
 */

extern	int doalias();
extern	int dobg();
extern	int dobreak();
extern	int dochngd();
extern	int docontin();
extern	int dodirs();
extern	int doecho();
extern	int doelse();
extern	int doend();
extern	int doendif();
extern	int doendsw();
extern	int doeval();
extern	int doexit();
extern	int dofg();
extern	int doforeach();
extern	int doglob();
extern	int dogoto();
extern	int dohash();
extern	int dohist();
extern	int doif();
extern	int dojobs();
extern	int dokill();
extern	int dolet();
extern	int dolimit();
extern	int dologin();
extern	int dologout();
I 3
D 11
#ifdef NEWGRP
E 3
extern	int donewgrp();
I 3
#endif
E 11
E 3
extern	int donice();
extern	int donotify();
extern	int donohup();
extern	int doonintr();
extern	int dopopd();
extern	int dopushd();
extern	int dorepeat();
extern	int doset();
extern	int dosetenv();
extern	int dosource();
extern	int dostop();
extern	int dosuspend();
extern	int doswbrk();
extern	int doswitch();
extern	int dotime();
extern	int dounlimit();
extern	int doumask();
extern	int dowait();
extern	int dowhile();
extern	int dozip();
extern	int execash();
extern	int goodbye();
#ifdef VFORK
extern	int hashstat();
#endif
extern	int shift();
extern	int showall();
extern	int unalias();
extern	int dounhash();
extern	int unset();
extern	int dounsetenv();

E 15
#define	INF	1000

D 12
struct	biltins {
	char	*bname;
	int	(*bfunct)();
	short	minargs, maxargs;
} bfunc[] = {
E 12
I 12
D 15
struct biltins bfunc[] = {
E 12
	"@",		dolet,		0,	INF,
	"alias",	doalias,	0,	INF,
D 4
#ifdef debug
E 4
	"alloc",	showall,	0,	1,
D 4
#endif
E 4
	"bg",		dobg,		0,	INF,
	"break",	dobreak,	0,	0,
	"breaksw",	doswbrk,	0,	0,
D 11
#ifdef IIASA
	"bye",		goodbye,	0,	0,
#endif
E 11
	"case",		dozip,		0,	1,
	"cd",		dochngd,	0,	1,
	"chdir",	dochngd,	0,	1,
	"continue",	docontin,	0,	0,
	"default",	dozip,		0,	0,
	"dirs",		dodirs,		0,	1,
	"echo",		doecho,		0,	INF,
	"else",		doelse,		0,	INF,
	"end",		doend,		0,	0,
	"endif",	dozip,		0,	0,
	"endsw",	dozip,		0,	0,
	"eval",		doeval,		0,	INF,
	"exec",		execash,	1,	INF,
	"exit",		doexit,		0,	INF,
	"fg",		dofg,		0,	INF,
	"foreach",	doforeach,	3,	INF,
D 11
#ifdef IIASA
	"gd",		dopushd,	0,	1,
#endif
E 11
	"glob",		doglob,		0,	INF,
	"goto",		dogoto,		1,	1,
E 15
I 15
struct biltins bfunc[] =
{
D 23
    "@", 	dolet, 		0, INF,
    "alias", 	doalias, 	0, INF,
    "alloc", 	showall, 	0, 1,
    "bg", 	dobg, 		0, INF,
    "break", 	dobreak, 	0, 0,
    "breaksw", 	doswbrk, 	0, 0,
    "case", 	dozip, 		0, 1,
    "cd", 	dochngd, 	0, INF,
    "chdir", 	dochngd, 	0, INF,
    "continue", docontin, 	0, 0,
    "default", 	dozip, 		0, 0,
    "dirs", 	dodirs,		0, INF,
    "echo", 	doecho,		0, INF,
    "else", 	doelse,		0, INF,
    "end", 	doend, 		0, 0,
    "endif", 	dozip, 		0, 0,
    "endsw", 	dozip, 		0, 0,
    "eval", 	doeval, 	0, INF,
    "exec", 	execash, 	1, INF,
    "exit", 	doexit, 	0, INF,
    "fg", 	dofg, 		0, INF,
    "foreach", 	doforeach, 	3, INF,
    "glob", 	doglob, 	0, INF,
    "goto", 	dogoto, 	1, 1,
E 15
D 16
#ifdef VFORK
E 16
D 15
	"hashstat",	hashstat,	0,	0,
E 15
I 15
    "hashstat", hashstat, 	0, 0,
E 15
D 16
#endif
E 16
D 15
	"history",	dohist,		0,	2,
	"if",		doif,		1,	INF,
	"jobs",		dojobs,		0,	1,
	"kill",		dokill,		1,	INF,
	"limit",	dolimit,	0,	3,
	"login",	dologin,	0,	1,
	"logout",	dologout,	0,	0,
I 3
D 11
#ifdef NEWGRP
E 3
	"newgrp",	donewgrp,	1,	1,
I 3
#endif
E 11
E 3
	"nice",		donice,		0,	INF,
	"nohup",	donohup,	0,	INF,
	"notify",	donotify,	0,	INF,
	"onintr",	doonintr,	0,	2,
	"popd",		dopopd,		0,	1,
	"pushd",	dopushd,	0,	1,
D 11
#ifdef IIASA
	"rd",		dopopd,		0,	1,
#endif
E 11
	"rehash",	dohash,		0,	0,
	"repeat",	dorepeat,	2,	INF,
	"set",		doset,		0,	INF,
D 7
	"setenv",	dosetenv,	2,	2,
E 7
I 7
	"setenv",	dosetenv,	0,	2,
E 7
	"shift",	shift,		0,	1,
D 2
	"source",	dosource,	1,	1,
E 2
I 2
	"source",	dosource,	1,	2,
E 2
	"stop",		dostop,		1,	INF,
	"suspend",	dosuspend,	0,	0,
	"switch",	doswitch,	1,	INF,
	"time",		dotime,		0,	INF,
	"umask",	doumask,	0,	1,
	"unalias",	unalias,	1,	INF,
	"unhash",	dounhash,	0,	0,
	"unlimit",	dounlimit,	0,	INF,
	"unset",	unset,		1,	INF,
	"unsetenv",	dounsetenv,	1,	INF,
	"wait",		dowait,		0,	0,
	"while",	dowhile,	1,	INF,
E 15
I 15
    "history", 	dohist, 	0, 2,
    "if", 	doif, 		1, INF,
    "jobs", 	dojobs, 	0, 1,
    "kill", 	dokill, 	1, INF,
    "limit", 	dolimit, 	0, 3,
    "linedit", 	doecho, 	0, INF,
    "login", 	dologin, 	0, 1,
    "logout", 	dologout, 	0, 0,
    "nice", 	donice, 	0, INF,
    "nohup", 	donohup, 	0, INF,
    "notify", 	donotify, 	0, INF,
    "onintr", 	doonintr, 	0, 2,
    "popd", 	dopopd, 	0, INF,
I 21
    "printf",	doprintf,	1, INF,
E 21
    "pushd", 	dopushd, 	0, INF,
    "rehash", 	dohash, 	0, 0,
    "repeat", 	dorepeat, 	2, INF,
    "set", 	doset, 		0, INF,
    "setenv", 	dosetenv, 	0, 2,
    "shift", 	shift, 		0, 1,
    "source", 	dosource, 	1, 2,
    "stop", 	dostop, 	1, INF,
    "suspend", 	dosuspend, 	0, 0,
    "switch", 	doswitch, 	1, INF,
    "time", 	dotime, 	0, INF,
    "umask", 	doumask, 	0, 1,
    "unalias", 	unalias, 	1, INF,
    "unhash", 	dounhash, 	0, 0,
    "unlimit", 	dounlimit, 	0, INF,
    "unset", 	unset, 		1, INF,
    "unsetenv", dounsetenv, 	1, INF,
    "wait", 	dowait, 	0, 0,
I 21
    "which", 	dowhich, 	1, INF,
E 21
    "while", 	dowhile, 	1, INF,
E 23
I 23
    { "@", 		dolet, 		0, INF	},
    { "alias", 		doalias, 	0, INF	},
    { "alloc", 		showall, 	0, 1	},
    { "bg", 		dobg, 		0, INF	},
    { "break", 		dobreak, 	0, 0	},
    { "breaksw", 	doswbrk, 	0, 0	},
    { "case", 		dozip, 		0, 1	},
    { "cd", 		dochngd, 	0, INF	},
    { "chdir", 		dochngd, 	0, INF	},
    { "continue", 	docontin, 	0, 0	},
    { "default", 	dozip, 		0, 0	},
    { "dirs", 		dodirs,		0, INF	},
    { "echo", 		doecho,		0, INF	},
    { "else", 		doelse,		0, INF	},
    { "end", 		doend, 		0, 0	},
    { "endif", 		dozip, 		0, 0	},
    { "endsw", 		dozip, 		0, 0	},
    { "eval", 		doeval, 	0, INF	},
    { "exec", 		execash, 	1, INF	},
    { "exit", 		doexit, 	0, INF	},
    { "fg", 		dofg, 		0, INF	},
    { "foreach", 	doforeach, 	3, INF	},
    { "glob", 		doglob, 	0, INF	},
    { "goto", 		dogoto, 	1, 1	},
    { "hashstat", 	hashstat, 	0, 0	},
    { "history", 	dohist, 	0, 2	},
    { "if", 		doif, 		1, INF	},
    { "jobs", 		dojobs, 	0, 1	},
    { "kill", 		dokill, 	1, INF	},
    { "limit", 		dolimit, 	0, 3	},
    { "linedit", 	doecho, 	0, INF	},
    { "login", 		dologin, 	0, 1	},
    { "logout", 	dologout, 	0, 0	},
    { "nice", 		donice, 	0, INF	},
    { "nohup", 		donohup, 	0, INF	},
    { "notify", 	donotify, 	0, INF	},
    { "onintr", 	doonintr, 	0, 2	},
    { "popd", 		dopopd, 	0, INF	},
    { "printf",		doprintf,	1, INF	},
    { "pushd", 		dopushd, 	0, INF	},
    { "rehash", 	dohash, 	0, 0	},
    { "repeat", 	dorepeat, 	2, INF	},
    { "set", 		doset, 		0, INF	},
    { "setenv", 	dosetenv, 	0, 2	},
    { "shift", 		shift, 		0, 1	},
    { "source", 	dosource, 	1, 2	},
    { "stop", 		dostop, 	1, INF	},
    { "suspend", 	dosuspend, 	0, 0	},
    { "switch", 	doswitch, 	1, INF	},
    { "time", 		dotime, 	0, INF	},
    { "umask", 		doumask, 	0, 1	},
    { "unalias", 	unalias, 	1, INF	},
    { "unhash", 	dounhash, 	0, 0	},
    { "unlimit", 	dounlimit, 	0, INF	},
    { "unset", 		unset, 		1, INF	},
    { "unsetenv", 	dounsetenv, 	1, INF	},
    { "wait",		dowait, 	0, 0	},
    { "which",		dowhich, 	1, INF	},
    { "while", 		dowhile, 	1, INF	}
E 23
E 15
D 4
	0,		0,		0,	0,
E 4
};
I 4
D 15
int nbfunc = sizeof bfunc / sizeof *bfunc;
E 15
I 15
int     nbfunc = sizeof bfunc / sizeof *bfunc;
E 15
E 4

D 12
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

struct srch {
	char	*s_name;
	short	s_value;
} srchn[] = {
E 12
I 12
D 15
struct srch srchn[] = {
E 12
D 13
	"@",		ZLET,
	"break",	ZBREAK,
	"breaksw",	ZBRKSW,
	"case",		ZCASE,
	"default", 	ZDEFAULT,
	"else",		ZELSE,
	"end",		ZEND,
	"endif",	ZENDIF,
	"endsw",	ZENDSW,
	"exit",		ZEXIT,
	"foreach", 	ZFOREACH,
	"goto",		ZGOTO,
	"if",		ZIF,
	"label",	ZLABEL,
	"set",		ZSET,
	"switch",	ZSWITCH,
	"while",	ZWHILE,
E 13
I 13
	"@",		T_LET,
	"break",	T_BREAK,
	"breaksw",	T_BRKSW,
	"case",		T_CASE,
	"default", 	T_DEFAULT,
	"else",		T_ELSE,
	"end",		T_END,
	"endif",	T_ENDIF,
	"endsw",	T_ENDSW,
	"exit",		T_EXIT,
	"foreach", 	T_FOREACH,
	"goto",		T_GOTO,
	"if",		T_IF,
	"label",	T_LABEL,
	"set",		T_SET,
	"switch",	T_SWITCH,
	"while",	T_WHILE,
E 15
I 15
struct srch srchn[] =
{
D 23
    "@", 	T_LET,
    "break", 	T_BREAK,
    "breaksw", 	T_BRKSW,
    "case", 	T_CASE,
    "default", 	T_DEFAULT,
    "else", 	T_ELSE,
    "end", 	T_END,
    "endif", 	T_ENDIF,
    "endsw", 	T_ENDSW,
    "exit", 	T_EXIT,
    "foreach", 	T_FOREACH,
    "goto", 	T_GOTO,
    "if", 	T_IF,
    "label", 	T_LABEL,
    "set", 	T_SET,
    "switch", 	T_SWITCH,
    "while", 	T_WHILE,
E 23
I 23
    { "@", 		T_LET		},
    { "break", 		T_BREAK		},
    { "breaksw", 	T_BRKSW		},
    { "case", 		T_CASE		},
    { "default", 	T_DEFAULT	},
    { "else", 		T_ELSE		},
    { "end", 		T_END		},
    { "endif", 		T_ENDIF		},
    { "endsw", 		T_ENDSW		},
    { "exit", 		T_EXIT		},
    { "foreach", 	T_FOREACH	},
    { "goto", 		T_GOTO		},
    { "if", 		T_IF		},
    { "label", 		T_LABEL		},
    { "set", 		T_SET		},
    { "switch", 	T_SWITCH	},
    { "while", 		T_WHILE		}
E 23
E 15
E 13
D 4
	0,		0,
E 4
};
I 4
D 15
int nsrchn = sizeof srchn / sizeof *srchn;
E 15
I 15
int     nsrchn = sizeof srchn / sizeof *srchn;
E 15
E 4

D 12
struct	mesg {
	char	*iname;
	char	*pname;
} mesg[] = {
E 12
I 12
D 15
struct mesg mesg[] = {
E 12
	0,	0,
	"HUP",	"Hangup",
	"INT",	"Interrupt",	
	"QUIT",	"Quit",
	"ILL",	"Illegal instruction",
	"TRAP",	"Trace/BPT trap",
	"IOT",	"IOT trap",
	"EMT",	"EMT trap",
	"FPE",	"Floating exception",
	"KILL",	"Killed",
	"BUS",	"Bus error",
	"SEGV",	"Segmentation fault",
	"SYS",	"Bad system call",
	"PIPE",	"Broken pipe",
	"ALRM",	"Alarm clock",
	"TERM",	"Terminated",
D 4
	0,	"Signal 16",
E 4
I 4
	"URG",	"Urgent I/O condition",
E 4
D 10
	"STOP",	"Stopped (signal)",
	"TSTP",	"Stopped",
E 10
I 10
	"STOP",	"Suspended (signal)",
	"TSTP",	"Suspended",
E 10
	"CONT",	"Continued",
	"CHLD",	"Child exited",
D 10
	"TTIN", "Stopped (tty input)",
	"TTOU", "Stopped (tty output)",
E 10
I 10
	"TTIN", "Suspended (tty input)",
	"TTOU", "Suspended (tty output)",
E 10
D 4
	"TINT", "Tty input interrupt",
E 4
I 4
	"IO",	"I/O possible",
E 4
	"XCPU",	"Cputime limit exceeded",
	"XFSZ", "Filesize limit exceeded",
D 4
	0,	"Signal 26",
	0,	"Signal 27",
E 4
I 4
	"VTALRM","Virtual timer expired",
	"PROF",	"Profiling timer expired",
E 4
D 5
	0,	"Signal 28",
E 5
I 5
	"WINCH","Window size changed",
E 5
	0,	"Signal 29",
D 6
	0,	"Signal 30",
	0,	"Signal 31",
E 6
I 6
	"USR1",	"User defined signal 1",
	"USR2",	"User defined signal 2",
E 6
	0,	"Signal 32"
E 15
I 15
D 22
struct mesg mesg[] =
{
     /*  0 */ 	0, 		"",
     /*  1 */ 	"HUP", 		"Hangup",
     /*  2 */ 	"INT", 		"Interrupt",
     /*  3 */ 	"QUIT", 	"Quit",
     /*  4 */ 	"ILL", 		"Illegal instruction",
     /*  5 */ 	"TRAP", 	"Trace/BPT trap",
     /*  6 */ 	"IOT", 		"IOT trap",
     /*  7 */ 	"EMT", 		"EMT trap",
     /*  8 */ 	"FPE", 		"Floating exception",
     /*  9 */ 	"KILL", 	"Killed",
     /* 10 */ 	"BUS", 		"Bus error",
     /* 11 */ 	"SEGV", 	"Segmentation fault",
     /* 12 */ 	"SYS", 		"Bad system call",
     /* 13 */ 	"PIPE", 	"Broken pipe",
     /* 14 */ 	"ALRM", 	"Alarm clock",
     /* 15 */ 	"TERM", 	"Terminated",
     /* 16 */ 	"URG", 		"Urgent condition on IO channel",
     /* 17 */ 	"STOP", 	"Suspended (signal)",
     /* 18 */ 	"TSTP", 	"Suspended",
     /* 19 */ 	"CONT", 	"Continued",
     /* 20 */ 	"CHLD", 	"Child exited",
     /* 21 */ 	"TTIN", 	"Suspended (tty input)",
     /* 22 */ 	"TTOU", 	"Suspended (tty output)",
     /* 23 */ 	"IO", 		"IO possible interrupt",
     /* 24 */ 	"XCPU", 	"Cputime limit exceeded",
     /* 25 */ 	"XFSZ", 	"Filesize limit exceeded",
     /* 26 */ 	"VTALRM", 	"Virtual time alarm",
     /* 27 */ 	"PROF", 	"Profiling time alarm",
     /* 28 */ 	"WINCH", 	"Window changed",
     /* 29 */ 	"INFO", 	"Information request",
     /* 30 */ 	"USR1", 	"User signal 1",
     /* 31 */ 	"USR2", 	"User signal 2",
     /* 32 */ 	0, 		"Signal 32",
E 15
};
E 22
E 1
