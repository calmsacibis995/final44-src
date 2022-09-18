h64280
s 00025/00009/00169
d D 8.4 95/04/28 17:12:44 bostic 10 9
c vipw was hanging on stop signals
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00177
d D 8.3 94/04/02 10:05:37 pendry 9 8
c add 1994 copyright
e
s 00046/00053/00132
d D 8.2 94/04/01 06:49:59 pendry 8 7
c prettyness police
e
s 00002/00002/00183
d D 8.1 93/07/23 08:28:19 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00007/00176
d D 5.5 93/07/23 08:25:43 bostic 6 4
c Set the close-on-exec bit so that users can't get at the
c encrypted passwords while editing.
e
s 00002/00002/00181
d R 8.1 93/06/06 14:12:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00175
d D 5.4 91/05/21 10:57:15 bostic 4 3
c unlimit stack, data, rss; ignore SIG{ALRM,PIPE,TTOU}: sheer paranoia
e
s 00005/00008/00172
d D 5.3 91/03/13 12:36:38 bostic 3 2
c ignore the signals, don't just block them.
e
s 00004/00003/00176
d D 5.2 91/03/03 16:14:32 bostic 2 1
c make pw_edit fail for good when it fails; don't wait for db lock
e
s 00179/00000/00000
d D 5.1 91/02/12 21:34:43 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 21:34:43 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1990, 1993
E 9
I 9
 * Copyright (c) 1990, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * This file is used by all the "password" programs; vipw(8), chpass(1),
 * and passwd(1).
 */

#include <sys/param.h>
D 8
#include <sys/wait.h>
E 8
#include <sys/time.h>
#include <sys/resource.h>
I 8
#include <sys/stat.h>
#include <sys/wait.h>
E 8
D 6
#include <signal.h>
E 6
I 6

I 8
#include <err.h>
E 8
#include <errno.h>
E 6
#include <fcntl.h>
I 6
#include <paths.h>
E 6
#include <pwd.h>
D 6
#include <errno.h>
E 6
I 6
#include <signal.h>
E 6
#include <stdio.h>
D 6
#include <paths.h>
#include <string.h>
E 6
#include <stdlib.h>
I 6
#include <string.h>
I 8
#include <unistd.h>
E 8
E 6

D 8
extern char *progname;
E 8
I 8
#include "pw_util.h"

E 8
extern char *tempname;
I 10
static pid_t editpid = -1;
static int lockfd;
E 10

I 8
void
I 10
pw_cont(sig)
	int sig;
{

	if (editpid != -1)
		kill(editpid, sig);
}

void
E 10
E 8
pw_init()
{
	struct rlimit rlim;
D 3
	sigset_t set;
E 3

D 4
	/* Unlimited cpu, file size. */
E 4
I 4
	/* Unlimited resource limits. */
E 4
	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	(void)setrlimit(RLIMIT_CPU, &rlim);
	(void)setrlimit(RLIMIT_FSIZE, &rlim);
I 4
	(void)setrlimit(RLIMIT_STACK, &rlim);
	(void)setrlimit(RLIMIT_DATA, &rlim);
	(void)setrlimit(RLIMIT_RSS, &rlim);
E 4

	/* Don't drop core (not really necessary, but GP's). */
	rlim.rlim_cur = rlim.rlim_max = 0;
	(void)setrlimit(RLIMIT_CORE, &rlim);

D 4
	/* Turn off usual signals. */
E 4
I 4
	/* Turn off signals. */
	(void)signal(SIGALRM, SIG_IGN);
E 4
D 3
	sigemptyset(&set);
	(void)sigaddset(&set, SIGTSTP);
	(void)sigaddset(&set, SIGHUP);
	(void)sigaddset(&set, SIGINT);
	(void)sigaddset(&set, SIGQUIT);
	(void)sigaddset(&set, SIGTERM);
	(void)sigprocmask(SIG_BLOCK, &set, (sigset_t *)NULL);
E 3
I 3
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
I 4
	(void)signal(SIGPIPE, SIG_IGN);
E 4
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTERM, SIG_IGN);
D 10
	(void)signal(SIGTSTP, SIG_IGN);
I 4
	(void)signal(SIGTTOU, SIG_IGN);
E 10
I 10
	(void)signal(SIGCONT, pw_cont);
E 10
E 4
E 3

	/* Create with exact permissions. */
	(void)umask(0);
}

D 10
static int lockfd;
I 8

E 10
int
E 8
pw_lock()
{
	/* 
	 * If the master password file doesn't exist, the system is hosed.
D 6
	 * Might as well try to build one.
E 6
I 6
	 * Might as well try to build one.  Set the close-on-exec bit so
	 * that users can't get at the encrypted passwords while editing.
E 6
	 * Open should allow flock'ing the file; see 4.4BSD.	XXX
	 */
	lockfd = open(_PATH_MASTERPASSWD, O_RDONLY, 0);
D 6
	if (lockfd < 0) {
E 6
I 6
D 8
	if (lockfd < 0 || fcntl(lockfd, F_SETFD, 1) == -1) {
E 6
		(void)fprintf(stderr, "%s: %s: %s\n",
		    progname, _PATH_MASTERPASSWD, strerror(errno));
		exit(1);
	}
D 2
	if (flock(lockfd, LOCK_EX)) {
E 2
I 2
	if (flock(lockfd, LOCK_EX|LOCK_NB)) {
E 2
		(void)fprintf(stderr,
		    "%s: the password db is busy.\n", progname);
		exit(1);
	}
	return(lockfd);
E 8
I 8
	if (lockfd < 0 || fcntl(lockfd, F_SETFD, 1) == -1)
		err(1, "%s", _PATH_MASTERPASSWD);
	if (flock(lockfd, LOCK_EX|LOCK_NB))
		errx(1, "the password db file is busy");
	return (lockfd);
E 8
}

I 8
int
E 8
pw_tmp()
{
	static char path[MAXPATHLEN] = _PATH_MASTERPASSWD;
	int fd;
	char *p;

D 8
	if (p = rindex(path, '/'))
E 8
I 8
	if (p = strrchr(path, '/'))
E 8
		++p;
	else
		p = path;
D 6
	(void)sprintf(p, "%s.XXXXXX", progname);
E 6
I 6
D 8
	(void)snprintf(p, sizeof(path), "%s.XXXXXX", progname);
E 6
	if ((fd = mkstemp(path)) == -1) {
		(void)fprintf(stderr,
		    "%s: %s: %s\n", progname, path, strerror(errno));
		exit(1);
	}
E 8
I 8
	strcpy(p, "pw.XXXXXX");
	if ((fd = mkstemp(path)) == -1)
		err(1, "%s", path);
E 8
	tempname = path;
D 8
	return(fd);
E 8
I 8
	return (fd);
E 8
}

I 8
int
E 8
pw_mkdb()
{
D 8
	union wait pstat;
E 8
I 8
	int pstat;
E 8
	pid_t pid;

D 8
	(void)printf("%s: rebuilding the database...\n", progname);
	(void)fflush(stdout);
E 8
I 8
	warnx("rebuilding the database...");
	(void)fflush(stderr);
E 8
	if (!(pid = vfork())) {
		execl(_PATH_PWD_MKDB, "pwd_mkdb", "-p", tempname, NULL);
		pw_error(_PATH_PWD_MKDB, 1, 1);
	}
D 8
	pid = waitpid(pid, (int *)&pstat, 0);
	if (pid == -1 || pstat.w_status)
		return(0);
	(void)printf("%s: done\n", progname);
	return(1);
E 8
I 8
	pid = waitpid(pid, &pstat, 0);
	if (pid == -1 || !WIFEXITED(pstat) || WEXITSTATUS(pstat) != 0)
		return (0);
	warnx("done");
	return (1);
E 8
}

I 8
void
E 8
pw_edit(notsetuid)
	int notsetuid;
{
D 8
	union wait pstat;
E 8
I 8
	int pstat;
E 8
D 10
	pid_t pid;
E 10
	char *p, *editor;

	if (!(editor = getenv("EDITOR")))
		editor = _PATH_VI;
D 8
	if (p = rindex(editor, '/'))
E 8
I 8
	if (p = strrchr(editor, '/'))
E 8
		++p;
	else 
		p = editor;

D 10
	if (!(pid = vfork())) {
E 10
I 10
	if (!(editpid = vfork())) {
E 10
		if (notsetuid) {
			(void)setgid(getgid());
			(void)setuid(getuid());
		}
		execlp(editor, p, tempname, NULL);
D 2
		pw_error(editor, 1, 1);
E 2
I 2
		_exit(1);
E 2
	}
D 10
	pid = waitpid(pid, (int *)&pstat, 0);
D 2
	return (pid == -1 ? 1 : pstat.w_status);
E 2
I 2
D 8
	if (pid == -1 || pstat.w_status)
E 8
I 8
	if (pid == -1 || !WIFEXITED(pstat) || WEXITSTATUS(pstat) != 0)
E 8
		pw_error(editor, 1, 1);
E 10
I 10
	for (;;) {
		editpid = waitpid(editpid, (int *)&pstat, WUNTRACED);
		if (editpid == -1)
			pw_error(editor, 1, 1);
		else if (WIFSTOPPED(pstat))
			raise(WSTOPSIG(pstat));
		else if (WIFEXITED(pstat) && WEXITSTATUS(pstat) == 0)
			break;
		else
			pw_error(editor, 1, 1);
	}
	editpid = -1;
E 10
E 2
}

I 8
void
E 8
pw_prompt()
{
D 8
	register int c;
E 8
I 8
	int c;
E 8

D 8
	for (;;) {
		(void)printf("re-edit the password file? [y]: ");
		(void)fflush(stdout);
		c = getchar();
		if (c != EOF && c != (int)'\n')
			while (getchar() != (int)'\n');
		if (c == (int)'n')
			pw_error((char *)NULL, 0, 0);
		break;
	}
E 8
I 8
	(void)printf("re-edit the password file? [y]: ");
	(void)fflush(stdout);
	c = getchar();
	if (c != EOF && c != '\n')
		while (getchar() != '\n');
	if (c == 'n')
		pw_error(NULL, 0, 0);
E 8
}

I 8
void
E 8
pw_error(name, err, eval)
	char *name;
	int err, eval;
{
D 8
	int sverrno;
E 8
I 8
	if (err)
		warn(name);
E 8

D 8
	if (err) {
		sverrno = errno;
		(void)fprintf(stderr, "%s: ", progname);
		if (name)
			(void)fprintf(stderr, "%s: ", name);
		(void)fprintf(stderr, "%s\n", strerror(sverrno));
	}
	(void)fprintf(stderr,
	    "%s: %s unchanged\n", progname, _PATH_MASTERPASSWD);
E 8
I 8
	warnx("%s: unchanged", _PATH_MASTERPASSWD);
E 8
	(void)unlink(tempname);
	exit(eval);
}
E 1
