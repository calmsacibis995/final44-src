h27092
s 00002/00002/00345
d D 8.1 93/06/06 15:08:24 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00027/00311
d D 5.19 92/09/20 08:41:33 edward 30 29
c use close-on-exec and some other stuff to get rid of dtablesize dependency
e
s 00009/00002/00329
d D 5.18 92/08/23 18:41:11 bostic 29 28
c get rid of getdtablesize; this code should be rethought
e
s 00031/00013/00300
d D 5.17 92/06/26 12:03:22 bostic 28 27
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00003/00001/00310
d D 5.16 91/04/01 08:59:11 bostic 27 26
c ANSI
e
s 00084/00003/00227
d D 5.15 90/06/25 00:01:56 edward 26 25
c remove call of _fwalk
e
s 00001/00011/00229
d D 5.14 90/06/01 16:59:53 bostic 25 24
c new copyright notice
e
s 00000/00001/00240
d D 5.13 88/07/08 19:42:01 edward 24 23
c removed some functions in the C library
e
s 00114/00021/00127
d D 5.12 88/07/08 01:43:33 edward 23 22
c rationalized handling of child processes, cleaned up mail1 some more
e
s 00002/00002/00146
d D 5.11 88/07/07 04:16:32 edward 22 21
c compile with -R
e
s 00103/00037/00045
d D 5.10 88/07/07 02:48:22 edward 21 20
c rationalized calling of editors and starting processes in general
e
s 00012/00007/00070
d D 5.9 88/06/29 21:02:00 bostic 20 19
c install approved copyright notice
e
s 00006/00018/00071
d D 5.8 88/06/29 19:03:40 edward 19 18
c popen to Popen, pclose to Pclose, never call a shell in popen
e
s 00002/00002/00087
d D 5.7 88/06/19 03:44:55 edward 18 17
c use shell="" instead of shell=none for no shell,
c use SHELL instead of "/bin/csh"
e
s 00001/00001/00088
d D 5.6 88/06/17 16:47:28 edward 17 16
c wrong type for argv
e
s 00023/00006/00066
d D 5.5 88/06/10 21:16:49 edward 16 15
c check variables "shell" and "SHELL", from Tom Newcomb (newcomb@arpa)
e
s 00011/00005/00061
d D 5.4 88/02/18 17:04:16 bostic 15 14
c written by Kurt Shoens; added Berkeley specific header
e
s 00008/00016/00058
d D 5.3 87/05/18 12:28:37 edward 14 13
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00073
d D 5.2 85/06/21 17:13:38 mckusick 13 12
c botched copyright
e
s 00007/00001/00067
d D 5.1 85/06/06 10:40:47 dist 12 11
c Add copyright
e
s 00002/00004/00066
d D 1.8 85/01/09 10:18:18 ralph 11 10
c use sigmask() macro
e
s 00004/00001/00066
d D 1.7 83/08/13 11:35:06 sam 10 8
c standardize sccs keyword lines
e
s 00004/00000/00067
d R 1.7 83/08/11 22:19:07 sam 9 8
c standardize sccs keyword lines
e
s 00008/00010/00059
d D 1.6 83/06/12 11:17:03 sam 8 7
c new signals
e
s 00003/00000/00066
d D 1.5 82/10/21 05:45:47 carl 7 6
c Null definition of sigchild() added if SIGRETRO is undefined.
e
s 00001/00000/00065
d D 1.4 82/07/26 17:10:33 kurt 6 5
c added call on sigchild() after fork() to fix retrofit signals 
c 
e
s 00000/00000/00065
d D 1.3 82/03/15 09:44:35 kurt 5 2
i 4 3
c Included Eric's branch changes to remove vax and vmunix 
c dependencies. 
c 
e
s 00011/00001/00054
d D 1.2.1.2 82/03/15 09:34:10 kurt 4 3
c Eric Allman's fixes to remove VAX and VMUNIX dependencies
e
s 00000/00000/00055
d D 1.2.1.1 82/03/15 09:26:59 kurt 3 2
c branch-place-holder
e
s 00007/00007/00048
d D 1.2 81/09/19 16:52:04 kurt 2 1
c changed pclose() to sighold/sigrelse instead of old signal jazz. 
c 
e
s 00055/00000/00000
d D 1.1 81/09/10 08:13:29 kurt 1 0
c date and time created 81/09/10 08:13:29 by kurt
e
u
U
f b 
f i 
t
T
I 12
/*
D 31
 * Copyright (c) 1980 Regents of the University of California.
D 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 20
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 20
I 20
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
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 20
E 15
 */

E 12
I 10
D 15
#ifndef lint
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
E 13
I 13
static char *sccsid = "%W% (Berkeley) %G%";
E 13
D 12
#endif
E 12
I 12
#endif not lint
E 15
I 15
D 20
#ifdef notdef
E 20
I 20
#ifndef lint
E 20
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif /* notdef */
E 20
I 20
#endif /* not lint */
E 20
E 15
E 12

I 16
#include "rcv.h"
E 16
E 10
I 1
D 21
#include <stdio.h>
E 21
D 14
#include <signal.h>
E 14
I 14
D 28
#include <sys/signal.h>
E 28
D 21
#include <sys/types.h>
E 21
#include <sys/wait.h>
I 30
#include <fcntl.h>
E 30
I 28
#include "extern.h"
E 28
E 14
I 4
D 21
#include <errno.h>
E 21
I 14

E 14
E 4
D 21
#define	tst(a,b)	(*mode == 'r'? (b) : (a))
#define	RDR	0
#define	WTR	1
static	int	popen_pid[20];
E 21
I 21
#define READ 0
#define WRITE 1
D 22
static int *pid = NULL;
E 22
I 22
D 30
static int *pid;
E 30
E 22
E 21
D 10
static	char	*sccsid = "%W% %G%";
E 10

I 26
struct fp {
	FILE *fp;
	int pipe;
I 30
	int pid;
E 30
	struct fp *link;
};
static struct fp *fp_head;

I 28
struct child {
	int pid;
	char done;
	char free;
	union wait status;
	struct child *link;
};
static struct child *child;
static struct child *findchild __P((int));
static void delchild __P((struct child *));

E 28
E 26
I 4
D 8
# ifndef VMUNIX
# define vfork	fork
# endif VMUNIX
E 8
I 8
D 11
#ifdef VMUNIX
#define	mask(s)	(1<<((s)-1))
#else
E 11
I 11
D 14
#ifndef VMUNIX
E 11
#define vfork	fork
#endif VMUNIX
E 8
I 7
#ifndef	SIGRETRO
#define	sigchild()
#endif
E 7

E 14
E 4
FILE *
I 26
Fopen(file, mode)
	char *file, *mode;
{
	FILE *fp;

D 30
	if ((fp = fopen(file, mode)) != NULL)
		register_file(fp, 0);
E 30
I 30
	if ((fp = fopen(file, mode)) != NULL) {
		register_file(fp, 0, 0);
		(void) fcntl(fileno(fp), F_SETFD, 1);
	}
E 30
	return fp;
}

FILE *
Fdopen(fd, mode)
I 28
	int fd;
E 28
	char *mode;
{
	FILE *fp;

D 30
	if ((fp = fdopen(fd, mode)) != NULL)
		register_file(fp, 0);
E 30
I 30
	if ((fp = fdopen(fd, mode)) != NULL) {
		register_file(fp, 0, 0);
		(void) fcntl(fileno(fp), F_SETFD, 1);
	}
E 30
	return fp;
}

I 28
int
E 28
Fclose(fp)
	FILE *fp;
{
	unregister_file(fp);
	return fclose(fp);
}

I 29
D 30
/*
 * XXX
 * The old mail code used getdtablesize() to return the max number of
 * file descriptors.  That's a *real* big number now.  Fake it.
 */
#define	MAX_FILE_DESCRIPTORS		64
#define	MAX_FILE_DESCRIPTORS_TO_CLOSE	20
E 30
E 29
FILE *
E 26
D 19
popen(cmd,mode)
E 19
I 19
D 21
Popen(cmd,mode)
E 19
char	*cmd;
char	*mode;
E 21
I 21
Popen(cmd, mode)
	char *cmd;
	char *mode;
E 21
{
	int p[2];
D 16
	register myside, hisside, pid;
E 16
I 16
D 21
	register int myside, hisside;
D 19
	int pid, doshell;
D 17
	char *shell, buf[LINESIZE], **argv[MAXARGC];
E 17
I 17
	char *shell, buf[LINESIZE], *argv[MAXARGC];
E 19
I 19
	int pid;
	char *argv[MAXARGC];
E 21
I 21
	int myside, hisside, fd0, fd1;
I 30
	int pid;
E 30
I 26
	FILE *fp;
E 26
E 21
E 19
E 17
E 16

I 21
D 22
	if (pid == NULL)
E 22
I 22
D 30
	if (pid == 0)
E 22
D 29
		pid = (int *) malloc((unsigned) sizeof (int) * getdtablesize());
E 29
I 29
		pid = malloc((u_int)sizeof (int) * MAX_FILE_DESCRIPTORS);
E 30
E 29
E 21
D 16
	if(pipe(p) < 0)
E 16
I 16
D 19
	doshell = 1;
	if ((shell = value("shell")) || (shell = value("SHELL"))) {
D 18
		if (!strcmp(shell, "none"))
E 18
I 18
		if (!*shell)
E 18
			doshell = 0;
	} else
D 18
		shell = "/bin/csh";
E 18
I 18
		shell = SHELL;
E 19
E 18
	if (pipe(p) < 0)
E 16
		return NULL;
I 30
	(void) fcntl(p[READ], F_SETFD, 1);
	(void) fcntl(p[WRITE], F_SETFD, 1);
E 30
D 21
	myside = tst(p[WTR], p[RDR]);
	hisside = tst(p[RDR], p[WTR]);
D 16
	if((pid = vfork()) == 0) {
E 16
I 16
	if ((pid = vfork()) == 0) {
E 16
		/* myside and hisside reverse roles in child */
I 6
D 14
		sigchild();
E 14
E 6
		close(myside);
		dup2(hisside, tst(0, 1));
		close(hisside);
D 16
		execl("/bin/csh", "sh", "-c", cmd, 0);
E 16
I 16
D 19
		if (doshell) {
			sprintf(buf, "%s -c %s", shell, cmd);
			(void) getrawlist(buf, argv, MAXARGC);
			execvp(argv[0], argv);
		} else {
			(void) getrawlist(cmd, argv, MAXARGC);
			execvp(argv[0], argv);
		}
E 19
I 19
		(void) getrawlist(cmd, argv, MAXARGC);
		execvp(argv[0], argv);
E 19
		fprintf(stderr, "Cannot execute %s\n", argv[0]);
E 16
		_exit(1);
E 21
I 21
	if (*mode == 'r') {
		myside = p[READ];
		fd0 = -1;
		hisside = fd1 = p[WRITE];
	} else {
		myside = p[WRITE];
		hisside = fd0 = p[READ];
		fd1 = -1;
E 21
	}
D 16
	if(pid == -1)
E 16
I 16
D 21
	if (pid == -1)
E 21
I 21
D 28
	if ((pid[myside] = start_command(cmd, 0, fd0, fd1, NOSTR)) < 0) {
E 28
I 28
D 30
	if ((pid[myside] = start_command(cmd,
	    0, fd0, fd1, NOSTR, NOSTR, NOSTR)) < 0) {
E 30
I 30
	if ((pid = start_command(cmd, 0, fd0, fd1, NOSTR, NOSTR, NOSTR)) < 0) {
E 30
E 28
		close(p[READ]);
		close(p[WRITE]);
E 21
E 16
		return NULL;
D 21
	popen_pid[myside] = pid;
E 21
I 21
	}
E 21
D 26
	close(hisside);
D 16
	return(fdopen(myside, mode));
E 16
I 16
	return fdopen(myside, mode);
E 26
I 26
	(void) close(hisside);
	if ((fp = fdopen(myside, mode)) != NULL)
D 30
		register_file(fp, 1);
E 30
I 30
		register_file(fp, 1, pid);
E 30
	return fp;
E 26
E 16
}

I 28
int
E 28
D 19
pclose(ptr)
E 19
I 19
Pclose(ptr)
E 19
D 21
FILE *ptr;
E 21
I 21
	FILE *ptr;
E 21
{
D 2
	register f, r, (*hstat)(), (*istat)(), (*qstat)();
E 2
I 2
D 21
	register f, r;
E 21
I 21
	int i;
E 21
E 2
D 8
	int status;
E 8
I 8
D 14
	int status, omask;
E 14
I 14
	int omask;
D 21
	union wait status;
E 14
E 8
I 4
	extern int errno;
E 21
E 4

D 21
	f = fileno(ptr);
E 21
I 21
D 30
	i = fileno(ptr);
E 30
I 30
	i = file_pid(ptr);
E 30
E 21
D 26
	fclose(ptr);
E 26
I 26
	unregister_file(ptr);
	(void) fclose(ptr);
E 26
I 4
D 14
# ifdef VMUNIX
E 14
E 4
D 2
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	hstat = signal(SIGHUP, SIG_IGN);
E 2
I 2
D 8
	sighold(SIGINT);
	sighold(SIGQUIT);
	sighold(SIGHUP);
E 8
I 8
D 11
	omask = sigblock(mask(SIGINT)|mask(SIGQUIT)|mask(SIGHUP));
E 11
I 11
D 21
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
E 11
E 8
E 2
D 4
	while((r = wait(&status)) != popen_pid[f] && r != -1)
E 4
I 4
D 14
# endif VMUNIX
E 14
	while((r = wait(&status)) != popen_pid[f] && r != -1 && errno != EINTR)
E 4
		;
	if(r == -1)
D 14
		status = -1;
I 4
# ifdef VMUNIX
E 14
I 14
		status.w_status = -1;
E 21
I 21
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGHUP));
D 23
	i = wait_command(pid[i]);
E 23
I 23
D 30
	i = wait_child(pid[i]);
E 30
I 30
	i = wait_child(i);
E 30
E 23
E 21
E 14
E 4
D 2
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
	signal(SIGHUP, hstat);
E 2
I 2
D 8
	sigrelse(SIGINT);
	sigrelse(SIGQUIT);
	sigrelse(SIGHUP);
E 8
I 8
	sigsetmask(omask);
E 8
I 4
D 14
# endif VMUNIX
E 4
E 2
	return(status);
E 14
I 14
D 21
	return (status.w_status);
E 21
I 21
	return i;
I 26
}

I 28
void
E 28
close_all_files()
{

	while (fp_head)
		if (fp_head->pipe)
			(void) Pclose(fp_head->fp);
		else
			(void) Fclose(fp_head->fp);
}

I 28
void
E 28
D 30
register_file(fp, pipe)
E 30
I 30
register_file(fp, pipe, pid)
E 30
	FILE *fp;
I 28
D 30
	int pipe;
E 30
I 30
	int pipe, pid;
E 30
E 28
{
	struct fp *fpp;

	if ((fpp = (struct fp *) malloc(sizeof *fpp)) == NULL)
		panic("Out of memory");
	fpp->fp = fp;
	fpp->pipe = pipe;
I 30
	fpp->pid = pid;
E 30
	fpp->link = fp_head;
	fp_head = fpp;
}

I 28
void
E 28
unregister_file(fp)
	FILE *fp;
{
	struct fp **pp, *p;

	for (pp = &fp_head; p = *pp; pp = &p->link)
		if (p->fp == fp) {
			*pp = p->link;
			free((char *) p);
			return;
		}
D 30
	/* XXX
	 * Ignore this for now; there may still be uncaught
	 * duplicate closes.
E 30
	panic("Invalid file pointer");
D 30
	*/
E 30
E 26
}

I 30
file_pid(fp)
	FILE *fp;
{
	struct fp *p;

	for (p = fp_head; p; p = p->link)
		if (p->fp == fp)
			return (p->pid);
	panic("Invalid file pointer");
	/*NOTREACHED*/
}

E 30
/*
 * Run a command without a shell, with optional arguments and splicing
 * of stdin and stdout.  The command name can be a sequence of words.
 * Signals must be handled by the caller.
 * "Mask" contains the signals to ignore in the new process.
 * SIGINT is enabled unless it's in the mask.
 */
/*VARARGS4*/
I 28
int
E 28
run_command(cmd, mask, infd, outfd, a0, a1, a2)
	char *cmd;
D 23
	int infd, outfd;
E 23
I 23
	int mask, infd, outfd;
E 23
	char *a0, *a1, *a2;
{
	int pid;

	if ((pid = start_command(cmd, mask, infd, outfd, a0, a1, a2)) < 0)
		return -1;
	return wait_command(pid);
}

/*VARARGS4*/
I 28
int
E 28
start_command(cmd, mask, infd, outfd, a0, a1, a2)
	char *cmd;
D 23
	int infd, outfd;
E 23
I 23
	int mask, infd, outfd;
E 23
	char *a0, *a1, *a2;
{
	int pid;

	if ((pid = vfork()) < 0) {
		perror("fork");
		return -1;
	}
	if (pid == 0) {
		char *argv[100];
		int i = getrawlist(cmd, argv, sizeof argv / sizeof *argv);

		if ((argv[i++] = a0) != NOSTR &&
		    (argv[i++] = a1) != NOSTR &&
		    (argv[i++] = a2) != NOSTR)
			argv[i] = NOSTR;
D 23
		if (infd >= 0)
			dup2(infd, 0);
		if (outfd >= 0)
			dup2(outfd, 1);
		for (i = getdtablesize(); --i > 2;)
			close(i);
		for (i = 1; i <= NSIG; i++)
			if (mask & sigmask(i))
				(void) signal(i, SIG_IGN);
		if ((mask & sigmask(SIGINT)) == 0)
			(void) signal(SIGINT, SIG_DFL);
		(void) sigsetmask(0);
E 23
I 23
		prepare_child(mask, infd, outfd);
E 23
		execvp(argv[0], argv);
		perror(argv[0]);
		_exit(1);
	}
	return pid;
}

I 28
void
E 28
I 23
prepare_child(mask, infd, outfd)
	int mask, infd, outfd;
{
	int i;

I 30
	/*
	 * All file descriptors other than 0, 1, and 2 are supposed to be
	 * close-on-exec.
	 */
E 30
	if (infd >= 0)
		dup2(infd, 0);
	if (outfd >= 0)
		dup2(outfd, 1);
D 29
	for (i = getdtablesize(); --i > 2;)
E 29
I 29
D 30
	for (i = MAX_FILE_DESCRIPTORS_TO_CLOSE; --i > 2;)
E 29
		close(i);
E 30
	for (i = 1; i <= NSIG; i++)
		if (mask & sigmask(i))
			(void) signal(i, SIG_IGN);
	if ((mask & sigmask(SIGINT)) == 0)
		(void) signal(SIGINT, SIG_DFL);
	(void) sigsetmask(0);
}

I 28
int
E 28
E 23
wait_command(pid)
	int pid;
{
D 23
	union wait status;
E 23
D 24
	int r;
E 24

D 23
	while ((r = wait(&status)) >= 0 && r != pid)
		;
	if (r < 0)
		return -1;
	if (status.w_status != 0) {
E 23
I 23
	if (wait_child(pid) < 0) {
E 23
		printf("Fatal error in process.\n");
		return -1;
	}
	return 0;
I 23
}

D 28
struct child {
	int pid;
	char done;
	char free;
	union wait status;
	struct child *link;
};
static struct child *child;

struct child *
E 28
I 28
static struct child *
E 28
findchild(pid)
	int pid;
{
	register struct child **cpp;

	for (cpp = &child; *cpp != NULL && (*cpp)->pid != pid;
	     cpp = &(*cpp)->link)
			;
	if (*cpp == NULL) {
		*cpp = (struct child *) malloc(sizeof (struct child));
		(*cpp)->pid = pid;
		(*cpp)->done = (*cpp)->free = 0;
		(*cpp)->link = NULL;
	}
	return *cpp;
}

I 28
static void
E 28
delchild(cp)
	register struct child *cp;
{
	register struct child **cpp;

	for (cpp = &child; *cpp != cp; cpp = &(*cpp)->link)
		;
	*cpp = cp->link;
	free((char *) cp);
}

I 27
void
E 27
D 28
sigchild()
E 28
I 28
sigchild(signo)
	int signo;
E 28
{
	int pid;
	union wait status;
	register struct child *cp;

D 27
	while ((pid = wait3(&status, WNOHANG, (struct timeval *)0)) > 0) {
E 27
I 27
	while ((pid =
	    wait3((int *)&status, WNOHANG, (struct rusage *)0)) > 0) {
E 27
		cp = findchild(pid);
		if (cp->free)
			delchild(cp);
		else {
			cp->done = 1;
			cp->status = status;
		}
	}
}

union wait wait_status;

/*
 * Wait for a specific child to die.
 */
I 28
int
E 28
wait_child(pid)
	int pid;
{
	int mask = sigblock(sigmask(SIGCHLD));
	register struct child *cp = findchild(pid);

	while (!cp->done)
		sigpause(mask);
	wait_status = cp->status;
	delchild(cp);
	sigsetmask(mask);
	return wait_status.w_status ? -1 : 0;
}

/*
 * Mark a child as don't care.
 */
I 28
void
E 28
free_child(pid)
	int pid;
{
	int mask = sigblock(sigmask(SIGCHLD));
	register struct child *cp = findchild(pid);

	if (cp->done)
		delchild(cp);
	else
		cp->free = 1;
	sigsetmask(mask);
E 23
E 21
E 14
}
E 1
