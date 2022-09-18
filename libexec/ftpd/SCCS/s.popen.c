h47967
s 00001/00001/00144
d D 8.3 94/04/06 11:04:03 pendry 15 14
c fix globbing - need NOCHECK flag
e
s 00041/00034/00104
d D 8.2 94/04/04 12:35:59 pendry 14 13
c eliminate local version of glob (cf ftp)
c clean up yacc grammar.  prettiness police.
e
s 00002/00002/00136
d D 8.1 93/06/04 18:48:45 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00137
d D 5.11 93/05/17 10:09:10 bostic 12 11
c bzero -> memset
e
s 00003/00001/00135
d D 5.10 92/06/27 16:54:19 andrew 11 10
c (bostic) changes for prototyping
e
s 00007/00004/00129
d D 5.9 91/02/25 16:46:25 bostic 10 9
c ANSI fixes, struct direct -> struct dirent, rename glob() -> ftpglob()
e
s 00001/00011/00132
d D 5.8 90/06/01 15:52:49 bostic 9 8
c new copyright notice
e
s 00001/00002/00142
d D 5.7 89/02/14 21:47:11 rick 8 7
c correct spelling of merchantAbility
e
s 00001/00000/00143
d D 5.6 88/12/19 16:32:11 bostic 7 6
c dup stderr, so get error messages from ls
e
s 00004/00002/00139
d D 5.5 88/12/16 17:08:49 bostic 6 4
c globbing allocation/freeing wrong; bug report 4.3BSD/etc/149
e
s 00003/00001/00140
d R 5.5 88/12/14 15:38:23 bostic 5 4
c globbing allocation/freeing wrong; bug report 4.3BSD/etc/149
e
s 00011/00011/00130
d D 5.4 88/12/07 11:35:51 karels 4 3
c fix user/pass to reset all on failure (*don't* leave failed anonymous
c login as root!), limit login attempts, sleep after failures to slow down
c guessing, correct telnet option processing, various cleanups
e
s 00001/00001/00140
d D 5.3 88/11/30 20:25:42 bostic 3 2
c Rick Adams for Bill Scherlis, the night that MilNet died
e
s 00040/00012/00101
d D 5.2 88/09/22 15:10:41 bostic 2 1
c change to do globbing and call program directly rather than shell
e
s 00113/00000/00000
d D 5.1 88/09/22 15:09:26 bostic 1 0
c version 5.7 of popen from the library
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
D 14
 * Copyright (c) 1988, 1993
E 14
I 14
 * Copyright (c) 1988, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software written by Ken Arnold and
 * published in UNIX Review, Vol. 6, No. 8.
 *
D 9
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
D 8
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
 *
D 8
 * static char sccsid[] = "@(#)popen.c	5.7 (Berkeley) 9/1/88";
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include <sys/param.h>
E 2
I 2
#include <sys/types.h>
E 2
D 10
#include <sys/signal.h>
E 10
I 4
#include <sys/wait.h>
I 11

I 14
#include <errno.h>
#include <glob.h>
E 14
E 11
I 10
#include <signal.h>
D 14
#include <unistd.h>
E 14
E 10
E 4
D 2
#include <sys/wait.h>
E 2
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
I 14
#include <unistd.h>

E 14
I 11
#include "extern.h"
E 11
E 10

I 2
/*
D 14
 * Special version of popen which avoids call to shell.  This insures noone
E 14
I 14
 * Special version of popen which avoids call to shell.  This ensures noone
E 14
 * may create a pipe to a hidden program as a side effect of a list or dir
 * command.
 */
E 2
D 4
static uid_t *pids;
E 4
I 4
static int *pids;
E 4
static int fds;

FILE *
D 3
popen(program, type)
E 3
I 3
ftpd_popen(program, type)
E 3
	char *program, *type;
{
I 2
D 14
	register char *cp;
E 14
I 14
	char *cp;
E 14
E 2
	FILE *iop;
D 2
	int pdes[2], pid;
	char *malloc();
E 2
I 2
	int argc, gargc, pdes[2], pid;
D 14
	char **pop, *argv[100], *gargv[1000], *vv[2];
E 14
I 14
	char **pop, *argv[100], *gargv[1000];
E 14
D 4
	extern char **glob(), **copyblk(), *strtok();
E 4
I 4
D 10
	extern char **glob(), **copyblk(), *strtok(), *malloc();
E 10
I 10
D 11
	extern char **ftpglob(), **copyblk();
E 11
E 10
E 4
E 2

	if (*type != 'r' && *type != 'w' || type[1])
D 14
		return(NULL);
E 14
I 14
		return (NULL);
E 14

	if (!pids) {
		if ((fds = getdtablesize()) <= 0)
D 14
			return(NULL);
E 14
I 14
			return (NULL);
E 14
D 4
		if (!(pids =
		    (uid_t *)malloc((u_int)(fds * sizeof(uid_t)))))
E 4
I 4
		if ((pids = (int *)malloc((u_int)(fds * sizeof(int)))) == NULL)
E 4
D 14
			return(NULL);
E 14
I 14
			return (NULL);
E 14
D 4
		bzero(pids, fds * sizeof(uid_t));
E 4
I 4
D 12
		bzero((char *)pids, fds * sizeof(int));
E 12
I 12
		memset(pids, 0, fds * sizeof(int));
E 12
E 4
	}
	if (pipe(pdes) < 0)
D 14
		return(NULL);
E 14
I 14
		return (NULL);
E 14
I 2

	/* break up string into pieces */
	for (argc = 0, cp = program;; cp = NULL)
		if (!(argv[argc++] = strtok(cp, " \t\n")))
			break;

	/* glob each piece */
	gargv[0] = argv[0];
	for (gargc = argc = 1; argv[argc]; argc++) {
D 10
		if (!(pop = glob(argv[argc]))) {	/* globbing failed */
E 10
I 10
D 14
		if (!(pop = ftpglob(argv[argc]))) {	/* globbing failed */
E 10
			vv[0] = argv[argc];
			vv[1] = NULL;
			pop = copyblk(vv);
		}
		argv[argc] = (char *)pop;		/* save to free later */
		while (*pop && gargc < 1000)
			gargv[gargc++] = *pop++;
E 14
I 14
		glob_t gl;
D 15
		int flags = GLOB_BRACE|GLOB_QUOTE|GLOB_TILDE;
E 15
I 15
		int flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
E 15

		memset(&gl, 0, sizeof(gl));
		if (glob(argv[argc], flags, NULL, &gl))
			gargv[gargc++] = strdup(argv[argc]);
		else
			for (pop = gl.gl_pathv; *pop; pop++)
				gargv[gargc++] = strdup(*pop);
		globfree(&gl);
E 14
	}
	gargv[gargc] = NULL;

	iop = NULL;
E 2
	switch(pid = vfork()) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
D 2
		return(NULL);
E 2
I 2
D 6
		goto free;
E 6
I 6
		goto pfree;
E 6
E 2
		/* NOTREACHED */
	case 0:				/* child */
		if (*type == 'r') {
D 14
			if (pdes[1] != 1) {
				dup2(pdes[1], 1);
I 7
				dup2(pdes[1], 2);	/* stderr, too! */
E 14
I 14
			if (pdes[1] != STDOUT_FILENO) {
				dup2(pdes[1], STDOUT_FILENO);
E 14
E 7
				(void)close(pdes[1]);
			}
I 14
			dup2(STDOUT_FILENO, STDERR_FILENO); /* stderr too! */
E 14
			(void)close(pdes[0]);
		} else {
D 14
			if (pdes[0] != 0) {
				dup2(pdes[0], 0);
E 14
I 14
			if (pdes[0] != STDIN_FILENO) {
				dup2(pdes[0], STDIN_FILENO);
E 14
				(void)close(pdes[0]);
			}
			(void)close(pdes[1]);
		}
D 2
		execl("/bin/sh", "sh", "-c", program, NULL);
		_exit(127);
		/* NOTREACHED */
E 2
I 2
		execv(gargv[0], gargv);
		_exit(1);
E 2
	}
	/* parent; assume fdopen can't fail...  */
	if (*type == 'r') {
		iop = fdopen(pdes[0], type);
		(void)close(pdes[1]);
	} else {
		iop = fdopen(pdes[1], type);
		(void)close(pdes[0]);
	}
	pids[fileno(iop)] = pid;
I 2

D 6
free:	for (argc = 1; argv[argc] != NULL; argc++)
E 6
I 6
D 14
pfree:	for (argc = 1; argv[argc] != NULL; argc++) {
E 6
		blkfree((char **)argv[argc]);
I 6
		free((char *)argv[argc]);
	}
E 6
E 2
	return(iop);
E 14
I 14
pfree:	for (argc = 1; gargv[argc] != NULL; argc++)
		free(gargv[argc]);

	return (iop);
E 14
}

I 11
int
E 11
D 4
pclose(iop)
E 4
I 4
ftpd_pclose(iop)
E 4
	FILE *iop;
{
D 14
	register int fdes;
D 4
	long omask;
D 2
	int stat_loc;
	pid_t waitpid();
E 2
I 2
	int pid, stat_loc;
	u_int waitpid();
E 4
I 4
	int omask;
	union wait stat_loc;
	int pid;
E 14
I 14
	int fdes, omask, status;
	pid_t pid;
E 14
E 4
E 2

	/*
	 * pclose returns -1 if stream is not associated with a
	 * `popened' command, or, if already `pclosed'.
	 */
D 4
	if (pids[fdes = fileno(iop)] == 0)
E 4
I 4
	if (pids == 0 || pids[fdes = fileno(iop)] == 0)
E 4
D 14
		return(-1);
E 14
I 14
		return (-1);
E 14
	(void)fclose(iop);
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
D 2
	stat_loc = waitpid(pids[fdes], &stat_loc, 0) == -1 ?
	    -1 : WEXITSTATUS(stat_loc);
E 2
I 2
D 10
	while ((pid = wait(&stat_loc)) != pids[fdes] && pid != -1);
E 10
I 10
D 14
	while ((pid = wait((int *)&stat_loc)) != pids[fdes] && pid != -1);
E 14
I 14
	while ((pid = waitpid(pids[fdes], &status, 0)) < 0 && errno == EINTR)
		continue;
E 14
E 10
E 2
	(void)sigsetmask(omask);
	pids[fdes] = 0;
D 4
	return(stat_loc);
E 4
I 4
D 14
	return(pid == -1 ? -1 : stat_loc.w_status);
E 14
I 14
	if (pid < 0)
		return (pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
E 14
E 4
}
E 1
