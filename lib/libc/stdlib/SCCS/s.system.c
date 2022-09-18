h48532
s 00002/00002/00048
d D 8.1 93/06/04 13:09:17 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00049
d D 5.11 91/11/12 11:56:48 bostic 13 12
c include user level signal.h
e
s 00004/00003/00046
d D 5.10 91/02/23 22:56:45 donn 12 11
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00011/00048
d D 5.9 90/06/01 14:44:52 bostic 11 10
c new copyright notice
e
s 00002/00001/00057
d D 5.8 90/05/16 13:52:52 bostic 10 9
c clean up includes
e
s 00004/00001/00054
d D 5.7 90/05/16 12:25:06 bostic 9 8
c ANSI requires NULL argument return if interpreter available
e
s 00008/00006/00047
d D 5.6 89/09/21 17:13:28 bostic 8 7
c POSIX signals, use paths.h for Bourne shell path
e
s 00008/00002/00045
d D 5.5 89/02/06 12:43:37 karels 7 6
c need to block SIGCHLD; ignore INT, QUIT, don't just block
e
s 00011/00011/00036
d D 5.4 89/02/05 15:43:05 bostic 6 5
c add waitpid
e
s 00038/00017/00009
d D 5.3 88/09/22 19:21:55 bostic 5 4
c rewrite to do wait correctly; should eventually use waitpid();
c add Berkeley copyright
e
s 00002/00002/00024
d D 5.2 86/03/09 19:59:42 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00022
d D 5.1 85/06/05 12:39:49 mckusick 3 1
c Add copyright
e
s 00001/00001/00022
d R 4.2 82/11/14 14:08:50 sam 2 1
c vfork is on the way out, don't perpetuate binaries w/ sys call
e
s 00023/00000/00000
d D 4.1 80/12/21 16:51:01 wnj 1 0
c date and time created 80/12/21 16:51:01 by wnj
e
u
U
t
T
I 5
/*
D 14
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

I 6
#include <sys/types.h>
E 6
E 3
D 5
#include	<signal.h>
E 5
I 5
D 10
#include <sys/wait.h>
E 10
D 13
#include <sys/signal.h>
E 13
I 10
#include <sys/wait.h>
I 13
#include <signal.h>
E 13
#include <stdlib.h>
E 10
D 9
#include <stdio.h>
E 9
I 9
#include <stddef.h>
I 12
#include <unistd.h>
E 12
E 9
I 8
#include <paths.h>
E 8
E 5

D 5
system(s)
char *s;
E 5
I 5
system(command)
D 12
	char *command;
E 12
I 12
	const char *command;
E 12
E 5
{
D 5
	int status, pid, w;
	register int (*istat)(), (*qstat)();
E 5
I 5
D 6
	int pid, wval, (*i)(), (*q)();
	union wait stat_loc;
E 6
I 6
	union wait pstat;
D 12
	pid_t pid, waitpid();
E 12
I 12
	pid_t pid;
E 12
D 7
	int omask;
E 7
I 7
D 8
	int omask, (*i)(), (*q)();
E 8
I 8
	int omask;
	sig_t intsave, quitsave;
I 9

	if (!command)		/* just checking... */
		return(1);
E 9
E 8
E 7
E 6
E 5

I 7
	omask = sigblock(sigmask(SIGCHLD));
E 7
D 5
	if ((pid = vfork()) == 0) {
		execl("/bin/sh", "sh", "-c", s, 0);
E 5
I 5
	switch(pid = vfork()) {
	case -1:			/* error */
I 7
		(void)sigsetmask(omask);
E 7
D 6
		stat_loc.w_status = 0;
		stat_loc.w_retcode = 127;
		return(stat_loc.w_status);
E 6
I 6
		pstat.w_status = 0;
		pstat.w_retcode = 127;
		return(pstat.w_status);
E 6
	case 0:				/* child */
I 7
		(void)sigsetmask(omask);
E 7
D 8
		execl("/bin/sh", "sh", "-c", command, (char *)NULL);
E 8
I 8
		execl(_PATH_BSHELL, "sh", "-c", command, (char *)NULL);
E 8
E 5
		_exit(127);
	}
D 5
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1)
		status = -1;
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
	return(status);
E 5
I 5
D 6
	i = signal(SIGINT, SIG_IGN);
	q = signal(SIGQUIT, SIG_IGN);
	while ((wval = wait(&stat_loc)) != pid && wval != -1);
	(void)signal(SIGINT, i);
	(void)signal(SIGQUIT, q);
	return(wval == -1 ? -1 : stat_loc.w_status);
E 6
I 6
D 7
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
E 7
I 7
D 8
	i = signal(SIGINT, SIG_IGN);
	q = signal(SIGQUIT, SIG_IGN);
E 8
I 8
	intsave = signal(SIGINT, SIG_IGN);
	quitsave = signal(SIGQUIT, SIG_IGN);
E 8
E 7
D 12
	pid = waitpid(pid, &pstat, 0);
E 12
I 12
	pid = waitpid(pid, (int *)&pstat, 0);
E 12
	(void)sigsetmask(omask);
I 7
D 8
	(void)signal(SIGINT, i);
	(void)signal(SIGQUIT, q);
E 8
I 8
	(void)signal(SIGINT, intsave);
	(void)signal(SIGQUIT, quitsave);
E 8
E 7
	return(pid == -1 ? -1 : pstat.w_status);
E 6
E 5
}
E 1
