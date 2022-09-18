h47028
s 00002/00002/00081
d D 8.1 93/06/04 12:05:13 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00081
d D 5.9 93/05/07 10:59:02 bostic 12 11
c make the sys_ arrays all `const char *const []' (for consistency,
c and for compatibility with GNU/Cygnus)
e
s 00003/00002/00080
d D 5.8 93/01/30 14:37:53 bostic 11 10
c make sys_signame, sys_siglist const
e
s 00038/00004/00044
d D 5.7 91/09/01 19:52:17 bostic 10 9
c add list of names, change "Stopped" to "Suspended"
e
s 00001/00000/00047
d D 5.6 91/02/23 19:50:04 donn 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00046
d D 5.5 90/06/01 14:15:52 bostic 8 7
c new copyright notice
e
s 00002/00002/00055
d D 5.4 89/08/26 16:58:34 karels 7 6
c rename IOT to ABRT (posix); add SIGINFO
e
s 00015/00004/00042
d D 5.3 88/07/26 13:18:26 bostic 6 5
c add Berkeley specific header; written by Sam Leffler
e
s 00002/00002/00044
d D 5.2 86/03/09 19:56:29 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00037
d D 5.1 85/05/30 10:50:50 dist 4 3
c Add copyright
e
s 00003/00003/00035
d D 4.3 85/05/22 18:40:20 mckusick 3 2
c add definitions for SIGWINCH, SIGUSR1, and SIGUSR2
e
s 00002/00000/00036
d D 4.2 83/02/10 22:48:35 sam 2 1
c must have signal.h
e
s 00036/00000/00000
d D 4.1 83/02/10 22:46:01 sam 1 0
c date and time created 83/02/10 22:46:01 by sam
e
u
U
t
T
I 1
D 4
/*	%W% (Berkeley) %G%	*/
E 4
I 4
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 13
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */

D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4

I 11
#include <sys/cdefs.h>
E 11
I 2
#include <signal.h>
I 9
D 10
#include <unistd.h>
E 10
E 9

E 2
D 10
char	*sys_siglist[NSIG] = {
E 10
I 10
D 11
char *sys_signame[NSIG] = {
E 11
I 11
D 12
char *const sys_signame[NSIG] = {
E 12
I 12
const char *const sys_signame[NSIG] = {
E 12
E 11
E 10
	"Signal 0",
I 10
	"hup",				/* SIGHUP */
	"int",				/* SIGINT */
	"quit",				/* SIGQUIT */
	"ill",				/* SIGILL */
	"trap",				/* SIGTRAP */
	"abrt",				/* SIGABRT */
	"emt",				/* SIGEMT */
	"fpe",				/* SIGFPE */
	"kill",				/* SIGKILL */
	"bus",				/* SIGBUS */
	"segv",				/* SIGSEGV */
	"sys",				/* SIGSYS */
	"pipe",				/* SIGPIPE */
	"alrm",				/* SIGALRM */
	"term",				/* SIGTERM */
	"urg",				/* SIGURG */
	"stop",				/* SIGSTOP */
	"tstp",				/* SIGTSTP */
	"cont",				/* SIGCONT */
	"chld",				/* SIGCHLD */
	"ttin",				/* SIGTTIN */
	"ttou",				/* SIGTTOU */
	"io",				/* SIGIO */
	"xcpu",				/* SIGXCPU */
	"xfsz",				/* SIGXFSZ */
	"vtalrm",			/* SIGVTALRM */
	"prof",				/* SIGPROF */
	"winch",			/* SIGWINCH */
	"info",				/* SIGINFO */
	"usr1",				/* SIGUSR1 */
	"usr2",				/* SIGUSR2 */
};

D 11
char *sys_siglist[NSIG] = {
E 11
I 11
D 12
char *const sys_siglist[NSIG] = {
E 12
I 12
const char *const sys_siglist[NSIG] = {
E 12
E 11
	"Signal 0",
E 10
	"Hangup",			/* SIGHUP */
	"Interrupt",			/* SIGINT */
	"Quit",				/* SIGQUIT */
	"Illegal instruction",		/* SIGILL */
	"Trace/BPT trap",		/* SIGTRAP */
D 7
	"IOT trap",			/* SIGIOT */
E 7
I 7
	"Abort trap",			/* SIGABRT */
E 7
	"EMT trap",			/* SIGEMT */
	"Floating point exception",	/* SIGFPE */
	"Killed",			/* SIGKILL */
	"Bus error",			/* SIGBUS */
	"Segmentation fault",		/* SIGSEGV */
	"Bad system call",		/* SIGSYS */
	"Broken pipe",			/* SIGPIPE */
	"Alarm clock",			/* SIGALRM */
	"Terminated",			/* SIGTERM */
	"Urgent I/O condition",		/* SIGURG */
D 10
	"Stopped (signal)",		/* SIGSTOP */
	"Stopped",			/* SIGTSTP */
E 10
I 10
	"Suspended (signal)",		/* SIGSTOP */
	"Suspended",			/* SIGTSTP */
E 10
	"Continued",			/* SIGCONT */
	"Child exited",			/* SIGCHLD */
	"Stopped (tty input)",		/* SIGTTIN */
	"Stopped (tty output)",		/* SIGTTOU */
	"I/O possible",			/* SIGIO */
	"Cputime limit exceeded",	/* SIGXCPU */
	"Filesize limit exceeded",	/* SIGXFSZ */
	"Virtual timer expired",	/* SIGVTALRM */
	"Profiling timer expired",	/* SIGPROF */
D 3
	"Signal 28",
E 3
I 3
	"Window size changes",		/* SIGWINCH */
E 3
D 7
	"Signal 29",
E 7
I 7
	"Information request",		/* SIGINFO */
E 7
D 3
	"Signal 30",
	"Signal 31"
E 3
I 3
	"User defined signal 1",	/* SIGUSR1 */
	"User defined signal 2"		/* SIGUSR2 */
E 3
};
E 1
