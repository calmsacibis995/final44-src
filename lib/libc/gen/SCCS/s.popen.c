h14377
s 00015/00009/00123
d D 8.3 95/05/03 17:54:46 mckusick 27 26
c allow popen to use openmode "r+" to specify two way communication
e
s 00011/00013/00121
d D 8.2 95/04/27 14:09:08 bostic 26 25
c set errno to EINVAL if arguments incorrect
c make pstat an int, not a union wait
c don't close the file descriptor if we can't find it on our list
c POSIX.2 explicitly disallows blocking SIGINT, SIGQUIT, SIGHUP (see the
c Rationale)
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00132
d D 8.1 93/06/04 12:04:21 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00037/00070
d D 5.17 92/04/14 13:44:32 bostic 24 23
c number of file descriptors may be infinite, don't use an array
e
s 00001/00001/00106
d D 5.16 92/04/14 09:55:15 bostic 23 22
c KNF
e
s 00007/00005/00100
d D 5.15 91/02/23 19:49:57 donn 22 21
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00104
d D 5.14 90/06/01 14:13:03 bostic 21 20
c new copyright notice
e
s 00021/00022/00094
d D 5.13 90/04/10 11:30:34 karels 20 19
c fds can be local; KNF
e
s 00005/00001/00111
d D 5.12 90/04/06 15:18:54 bostic 19 18
c waitpid may return EINTR if another signal is received, reissue call.
e
s 00005/00004/00107
d D 5.11 89/11/28 15:08:01 bostic 18 17
c use standard names for stdin/stdout
e
s 00002/00001/00109
d D 5.10 89/10/09 16:36:21 bostic 17 16
c use paths.h for Bourne shell path
e
s 00006/00006/00104
d D 5.9 88/12/07 18:35:43 bostic 16 15
c waitpid real, make this work
e
s 00007/00008/00103
d D 5.8 88/12/06 21:08:00 karels 15 14
c pids in a uid_t? other cleanups (but still not posix!)
e
s 00068/00067/00043
d D 5.7 88/09/01 12:41:40 bostic 14 13
c reformat; fixed to check for pipe call opening stdout before dup2'ing
c use getdtablesize() and malloc instead of a define'd limit of open files;
c fix to use the waitpid() call, rather than wait()'ing for anyone and saving
c the status; this version doesn't work, can't test it until waitpid() is done
e
s 00088/00058/00022
d D 5.6 88/08/31 15:18:59 bostic 13 12
c Ken Arnold's version from UNIX Review
e
s 00002/00001/00078
d D 5.5 87/09/30 12:18:02 bostic 12 11
c long/int bug; bug report 4.3BSD/lib/26
e
s 00000/00001/00079
d D 5.4 86/03/26 10:21:18 bloom 11 10
c param.h no longer needed
e
s 00002/00002/00078
d D 5.3 86/03/09 19:52:30 donn 10 9
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00071
d D 5.2 85/06/05 12:29:39 mckusick 9 8
c Add copyright
e
s 00000/00000/00072
d D 5.1 85/05/30 10:47:42 dist 8 7
c Add copyright
e
s 00020/00006/00052
d D 4.7 85/03/04 14:50:00 serge 7 6
c dynamically allocate process id array
e
s 00002/00001/00056
d D 4.6 84/11/10 18:23:18 lepreau 6 5
c use NOFILE from param.h
e
s 00021/00024/00036
d D 4.5 84/07/06 20:20:43 sam 5 4
c remove signal calls in favor of sigblock/sigsetmask
e
s 00004/00001/00056
d D 4.4 83/09/25 11:59:03 karels 4 3
c don't lose fd's if fork fails
e
s 00004/00002/00053
d D 4.3 83/08/18 16:50:32 sam 3 2
c bug fix from dlw: can't unconditionally close, must check if needed
e
s 00001/00001/00054
d D 4.2 82/11/14 14:08:44 sam 2 1
c vfork is on the way out, don't perpetuate binaries w/ sys call
e
s 00055/00000/00000
d D 4.1 80/12/21 16:50:45 wnj 1 0
c date and time created 80/12/21 16:50:45 by wnj
e
u
U
t
T
I 1
D 9
/* %W% (Berkeley) %G% */
E 9
I 9
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
D 25
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 14
 * This code is derived from software written by Ken Arnold and published
 * in UNIX Review, Vol. 6, No. 8.
E 14
I 14
 * This code is derived from software written by Ken Arnold and
 * published in UNIX Review, Vol. 6, No. 8.
E 14
 *
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 13
 */

D 10
#ifndef lint
E 10
I 10
#if defined(LIBC_SCCS) && !defined(lint)
E 10
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
D 13
#endif LIBC_SCCS and not lint
E 13
I 13
#endif /* LIBC_SCCS and not lint */
E 13
E 10
E 9
I 5

I 14
#include <sys/param.h>
D 24
#include <sys/signal.h>
E 24
#include <sys/wait.h>
I 27
#include <sys/socket.h>
E 27
I 24

#include <signal.h>
E 24
I 19
#include <errno.h>
I 24
#include <unistd.h>
E 24
E 19
E 14
E 5
#include <stdio.h>
I 22
#include <stdlib.h>
#include <string.h>
E 22
I 18
D 24
#include <unistd.h>
E 24
E 18
I 17
#include <paths.h>
E 17
D 13
#include <signal.h>
E 13
I 6
D 11
#include <sys/param.h>
E 11
E 6
I 5

E 5
D 13
#define	tst(a,b)	(*mode == 'r'? (b) : (a))
#define	RDR	0
#define	WTR	1
E 13
I 13
D 14
#define	MAXFILES	32
E 14
I 14
D 15
static uid_t *pids;
E 15
I 15
D 24
static pid_t *pids;
E 15
D 20
static int fds;
E 20
E 14
E 13
D 5
static	int	popen_pid[20];
E 5

E 24
I 24
static struct pid {
	struct pid *next;
	FILE *fp;
	pid_t pid;
} *pidlist; 
	
E 24
I 5
D 6
static	int popen_pid[20];
E 6
I 6
D 7
static	int popen_pid[NOFILE];
E 7
I 7
D 13
extern	char *malloc();
E 13
I 13
D 14
typedef struct {
	int pid;
	int status;
} PID_STRUCT;
E 13
E 7
E 6

I 7
D 13
static	int *popen_pid;
static	int nfiles;
E 13
I 13
PID_STRUCT pids[MAXFILES];
E 13

E 14
E 7
E 5
FILE *
D 13
popen(cmd,mode)
D 5
char	*cmd;
char	*mode;
E 5
I 5
	char *cmd;
	char *mode;
E 13
I 13
D 26
popen(program, type)
D 14
char *program, *type;
E 14
I 14
D 22
	char *program, *type;
E 22
I 22
	const char *program;
	const char *type;
E 26
I 26
popen(command, type)
	const char *command, *type;
E 26
E 22
E 14
E 13
E 5
{
I 24
	struct pid *cur;
E 24
D 13
	int p[2];
D 5
	register myside, hisside, pid;
E 5
I 5
	int myside, hisside, pid;
E 13
I 13
D 14
	char **argv;
	int pdes[2], pid;
E 14
	FILE *iop;
I 14
D 20
	int pdes[2], pid;
E 20
I 20
D 24
	int pdes[2], fds, pid;
E 24
I 24
D 27
	int pdes[2], pid;
E 27
I 27
	int pdes[2], pid, twoway;
E 27
E 24
E 20
D 22
	char *malloc();
E 22
E 14
E 13
E 5

I 7
D 13
	if (nfiles <= 0)
		nfiles = getdtablesize();
	if (popen_pid == NULL) {
		popen_pid = (int *)malloc(nfiles * sizeof *popen_pid);
		if (popen_pid == NULL)
			return (NULL);
		for (pid = 0; pid < nfiles; pid++)
			popen_pid[pid] = -1;
	}
E 7
D 5
	if(pipe(p) < 0)
		return NULL;
E 5
I 5
	if (pipe(p) < 0)
		return (NULL);
E 5
	myside = tst(p[WTR], p[RDR]);
	hisside = tst(p[RDR], p[WTR]);
D 2
	if((pid = vfork()) == 0) {
E 2
I 2
D 5
	if((pid = fork()) == 0) {
E 5
I 5
D 7
	if ((pid = fork()) == 0) {
E 7
I 7
	if ((pid = vfork()) == 0) {
E 7
E 5
E 2
		/* myside and hisside reverse roles in child */
		close(myside);
D 3
		dup2(hisside, tst(0, 1));
		close(hisside);
E 3
I 3
		if (hisside != tst(0, 1)) {
			dup2(hisside, tst(0, 1));
			close(hisside);
E 13
I 13
D 14
	if (*type != 'r' && *type != 'w')
		return NULL;
E 14
I 14
D 26
	if (*type != 'r' && *type != 'w' || type[1])
E 26
I 26
D 27
	if (*type != 'r' && *type != 'w' || type[1]) {
		errno = EINVAL;
E 26
D 20
		return(NULL);
E 20
I 20
		return (NULL);
E 27
I 27
	if (strchr(type, '+')) {
		twoway = 1;
		type = "r+";
		if (socketpair(AF_UNIX, SOCK_STREAM, 0, pdes) < 0)
			return (NULL);
	} else  {
		twoway = 0;
		if (*type != 'r' && *type != 'w' || type[1] ||
		    (pipe(pdes) < 0))
			return (NULL);
E 27
I 26
	}
E 26
E 20

D 15
	if (!pids) {
E 15
I 15
D 24
	if (pids == NULL) {
E 15
		if ((fds = getdtablesize()) <= 0)
D 20
			return(NULL);
E 20
I 20
			return (NULL);
E 20
D 15
		if (!(pids =
		    (uid_t *)malloc((u_int)(fds * sizeof(uid_t)))))
E 15
I 15
D 23
		if ((pids = (pid_t *)malloc((u_int)(fds * sizeof(int)))) == NULL)
E 23
I 23
		if ((pids = malloc((u_int)(fds * sizeof(int)))) == NULL)
E 23
E 15
D 20
			return(NULL);
E 20
I 20
			return (NULL);
E 20
D 15
		bzero(pids, fds * sizeof(uid_t));
E 15
I 15
		bzero((char *)pids, fds * sizeof(pid_t));
E 15
	}
E 14
	if (pipe(pdes) < 0)
E 24
I 24
	if ((cur = malloc(sizeof(struct pid))) == NULL)
E 24
D 14
		return NULL;
	switch(pid = fork()) {
	case -1:
		iop = NULL;
		break;
	case 0:			/* child */
		if (*type == 'r') {
			close(1);
			dup(pdes[1]);
E 13
		}
E 3
D 7
		execl("/bin/sh", "sh", "-c", cmd, 0);
		_exit(1);
E 7
I 7
D 13
		execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
		_exit(127);
E 13
I 13
		else {
			close(0);
			dup(pdes[0]);
		}
		close(pdes[1]);
		close(pdes[0]);
		execl("/bin/sh", "sh", "-c", program, NULL);
		exit(-1);
E 14
I 14
D 20
		return(NULL);
E 20
I 20
		return (NULL);
I 24

D 27
	if (pipe(pdes) < 0) {
		(void)free(cur);
		return (NULL);
	}

E 27
E 24
E 20
D 15
	switch(pid = vfork()) {
E 15
I 15
	switch (pid = vfork()) {
E 15
D 24
	case -1:			/* error */
D 20
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		return(NULL);
E 20
I 20
		(void) close(pdes[0]);
		(void) close(pdes[1]);
E 24
I 24
	case -1:			/* Error. */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		(void)free(cur);
E 24
		return (NULL);
E 20
E 14
		/* NOTREACHED */
D 14
	default:
E 14
I 14
D 24
	case 0:				/* child */
E 24
I 24
	case 0:				/* Child. */
E 24
E 14
		if (*type == 'r') {
D 14
			iop = fdopen(pdes[0], "r");
			close(pdes[1]);
E 14
I 14
D 18
			if (pdes[1] != 1) {
				dup2(pdes[1], 1);
E 18
I 18
			if (pdes[1] != STDOUT_FILENO) {
D 20
				(void)dup2(pdes[1], STDOUT_FILENO);
E 18
				(void)close(pdes[1]);
E 20
I 20
D 24
				(void) dup2(pdes[1], STDOUT_FILENO);
				(void) close(pdes[1]);
E 24
I 24
				(void)dup2(pdes[1], STDOUT_FILENO);
				(void)close(pdes[1]);
I 27
				pdes[1] = STDOUT_FILENO;
E 27
E 24
E 20
			}
D 20
			(void)close(pdes[0]);
E 20
I 20
			(void) close(pdes[0]);
I 27
			if (twoway && (pdes[1] != STDIN_FILENO))
				(void)dup2(pdes[1], STDIN_FILENO);
E 27
E 20
E 14
		} else {
D 14
			iop = fdopen(pdes[0], "w");
			close(pdes[0]);
E 14
I 14
D 18
			if (pdes[0] != 0) {
				dup2(pdes[0], 0);
E 18
I 18
			if (pdes[0] != STDIN_FILENO) {
D 20
				(void)dup2(pdes[0], STDIN_FILENO);
E 18
				(void)close(pdes[0]);
E 20
I 20
D 24
				(void) dup2(pdes[0], STDIN_FILENO);
				(void) close(pdes[0]);
E 24
I 24
				(void)dup2(pdes[0], STDIN_FILENO);
				(void)close(pdes[0]);
E 24
E 20
			}
D 20
			(void)close(pdes[1]);
E 20
I 20
D 24
			(void) close(pdes[1]);
E 24
I 24
			(void)close(pdes[1]);
E 24
E 20
E 14
		}
D 14
		break;
E 14
I 14
D 17
		execl("/bin/sh", "sh", "-c", program, NULL);
E 17
I 17
D 26
		execl(_PATH_BSHELL, "sh", "-c", program, NULL);
E 26
I 26
		execl(_PATH_BSHELL, "sh", "-c", command, NULL);
E 26
E 17
		_exit(127);
		/* NOTREACHED */
E 14
E 13
E 7
	}
D 4
	if(pid == -1)
E 4
I 4
D 5
	if(pid == -1) {
E 5
I 5
D 13
	if (pid == -1) {
E 5
		close(myside);
		close(hisside);
E 4
D 5
		return NULL;
E 5
I 5
		return (NULL);
E 13
I 13
D 14
	if (iop != NULL)
		pids[fileno(iop)].pid = pid;
	else {
		close(pdes[0]);
		close(pdes[1]);
E 14
I 14
D 24
	/* parent; assume fdopen can't fail...  */
E 24
I 24

	/* Parent; assume fdopen can't fail. */
E 24
	if (*type == 'r') {
		iop = fdopen(pdes[0], type);
D 20
		(void)close(pdes[1]);
E 20
I 20
D 24
		(void) close(pdes[1]);
E 24
I 24
		(void)close(pdes[1]);
E 24
E 20
	} else {
		iop = fdopen(pdes[1], type);
D 20
		(void)close(pdes[0]);
E 20
I 20
D 24
		(void) close(pdes[0]);
E 24
I 24
		(void)close(pdes[0]);
E 24
E 20
E 14
E 13
E 5
I 4
	}
E 4
D 13
	popen_pid[myside] = pid;
	close(hisside);
D 5
	return(fdopen(myside, mode));
E 5
I 5
	return (fdopen(myside, mode));
E 13
I 13
D 14
	return iop;
E 14
I 14
D 24
	pids[fileno(iop)] = pid;
E 24
I 24

	/* Link into list of file descriptors. */
	cur->fp = iop;
	cur->pid =  pid;
	cur->next = pidlist;
	pidlist = cur;

E 24
D 20
	return(iop);
E 20
I 20
	return (iop);
E 20
E 14
E 13
E 5
}

I 24
/*
 * pclose --
 *	Pclose returns -1 if stream is not associated with a `popened' command,
 *	if already `pclosed', or waitpid returns an error.
 */
E 24
I 22
int
E 22
D 13
pclose(ptr)
D 5
FILE *ptr;
E 5
I 5
	FILE *ptr;
E 13
I 13
pclose(iop)
D 14
FILE *iop;
E 14
I 14
	FILE *iop;
E 14
E 13
E 5
{
I 19
D 22
	extern int errno;
E 22
E 19
D 5
	register f, r, (*hstat)(), (*istat)(), (*qstat)();
	int status;
E 5
I 5
D 12
	int child, pid, status, omask;
E 12
I 12
D 13
	long omask;
	int child, pid, status;
E 13
I 13
D 14
	int status;
	int pid, fdes, i;
E 14
I 14
D 24
	register int fdes;
E 24
I 24
	register struct pid *cur, *last;
E 24
D 15
	long omask;
E 15
I 15
	int omask;
E 15
D 16
	int stat_loc;
	pid_t waitpid();
E 16
I 16
D 26
	union wait pstat;
E 26
I 26
	int pstat;
E 26
D 22
	pid_t pid, waitpid();
E 22
I 22
	pid_t pid;
E 22
E 16
E 14
E 13
E 12
E 5

D 5
	f = fileno(ptr);
E 5
I 5
D 13
	child = popen_pid[fileno(ptr)];
I 7
	popen_pid[fileno(ptr)] = -1;
E 7
E 5
	fclose(ptr);
D 5
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	hstat = signal(SIGHUP, SIG_IGN);
	while((r = wait(&status)) != popen_pid[f] && r != -1)
E 5
I 5
D 7
#define	mask(s)	(1 << ((s)-1))
	omask = sigblock(mask(SIGINT)|mask(SIGQUIT)|mask(SIGHUP));
E 7
I 7
	if (child == -1)
		return (-1);
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
E 7
	while ((pid = wait(&status)) != child && pid != -1)
E 5
		;
D 5
	if(r == -1)
		status = -1;
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
	signal(SIGHUP, hstat);
	return(status);
E 5
I 5
	(void) sigsetmask(omask);
	return (pid == -1 ? -1 : status);
E 13
I 13
D 14
	fdes = fileno(iop);
	fclose(iop);
	if (pids[fdes].pid == 0)
		return pids[fdes].status;
	for (;;) {
		pid = wait(&status);
		if (pid < 0)
			return -1;
		if (pid == pids[fdes].pid) {
			pids[fdes].pid = 0;
			return status;
		}
		for (i = 0; i < MAXFILES; i++)
			if (pids[i].pid == pid) {
				pids[i].pid = 0;
				pids[i].status = status;
				break;
			}
	}
E 14
I 14
D 24
	/*
	 * pclose returns -1 if stream is not associated with a
D 16
	 * `popened' command, or, if already `pclosed'.
E 16
I 16
	 * `popened' command, if already `pclosed', or waitpid
	 * returns an error.
E 16
	 */
D 15
	if (pids[fdes = fileno(iop)] == 0)
E 15
I 15
	if (pids == NULL || pids[fdes = fileno(iop)] == 0)
E 24
I 24
D 26
	(void)fclose(iop);

E 26
	/* Find the appropriate file pointer. */
	for (last = NULL, cur = pidlist; cur; last = cur, cur = cur->next)
		if (cur->fp == iop)
			break;
	if (cur == NULL)
E 24
E 15
D 20
		return(-1);
	(void)fclose(iop);
E 20
I 20
		return (-1);
D 24
	(void) fclose(iop);
E 24
I 24

D 26
	/* Get the status of the process. */
E 24
E 20
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
E 26
I 26
	(void)fclose(iop);

E 26
D 16
	stat_loc = waitpid(pids[fdes], &stat_loc, 0) == -1 ?
	    -1 : WEXITSTATUS(stat_loc);
E 16
I 16
D 19
	pid = waitpid(pids[fdes], &pstat, 0);
E 19
I 19
	do {
D 22
		pid = waitpid(pids[fdes], &pstat, 0);
E 22
I 22
D 24
		pid = waitpid(pids[fdes], (int *) &pstat, 0);
E 24
I 24
D 26
		pid = waitpid(cur->pid, (int *) &pstat, 0);
E 26
I 26
		pid = waitpid(cur->pid, &pstat, 0);
E 26
E 24
E 22
	} while (pid == -1 && errno == EINTR);
E 19
E 16
D 20
	(void)sigsetmask(omask);
E 20
I 20
D 24
	(void) sigsetmask(omask);
E 20
	pids[fdes] = 0;
E 24
I 24
D 26
	(void)sigsetmask(omask);
E 26

	/* Remove the entry from the linked list. */
	if (last == NULL)
		pidlist = cur->next;
	else
		last->next = cur->next;
	free(cur);
		
E 24
D 16
	return(stat_loc);
E 16
I 16
D 20
	return(pid == -1 ? -1 : pstat.w_status);
E 20
I 20
D 26
	return (pid == -1 ? -1 : pstat.w_status);
E 26
I 26
	return (pid == -1 ? -1 : pstat);
E 26
E 20
E 16
E 14
E 13
E 5
}
E 1
