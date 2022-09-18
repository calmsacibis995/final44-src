h63873
s 00013/00009/00128
d D 8.2 94/04/02 07:42:03 pendry 5 4
c rework susystem
e
s 00002/00002/00135
d D 8.1 93/05/31 15:08:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00017/00125
d D 5.3 93/04/29 13:39:33 bostic 3 2
c use err/warn from the C library
e
s 00003/00000/00139
d D 5.2 92/06/30 08:44:20 andrew 2 1
c allow filenames to start with :
e
s 00139/00000/00000
d D 5.1 92/06/20 12:24:45 bostic 1 0
c date and time created 92/06/20 12:24:45 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>

D 3
#include <signal.h>
E 3
I 3
#include <ctype.h>
#include <err.h>
E 3
#include <errno.h>
D 3
#include <unistd.h>
#include <stdlib.h>
E 3
I 3
#include <paths.h>
#include <signal.h>
E 3
#include <stdio.h>
D 3
#include <ctype.h>
E 3
I 3
#include <stdlib.h>
E 3
#include <string.h>
D 3
#include <paths.h>
E 3
I 3
#include <unistd.h>

E 3
#include "extern.h"

char *
colon(cp)
D 5
	register char *cp;
E 5
I 5
	char *cp;
E 5
{
I 2
	if (*cp == ':')		/* Leading colon is part of file name. */
		return (0);

E 2
	for (; *cp; ++cp) {
		if (*cp == ':')
			return (cp);
		if (*cp == '/')
			return (0);
	}
	return (0);
}

void
verifydir(cp)
	char *cp;
{
	struct stat stb;

	if (!stat(cp, &stb)) {
		if (S_ISDIR(stb.st_mode))
			return;
		errno = ENOTDIR;
	}
D 3
	err("%s: %s", cp, strerror(errno));
E 3
I 3
	run_err("%s: %s", cp, strerror(errno));
E 3
	exit(1);
}

int
okname(cp0)
	char *cp0;
{
D 5
	register int c;
	register char *cp;
E 5
I 5
	int c;
	char *cp;
E 5

	cp = cp0;
	do {
		c = *cp;
		if (c & 0200)
			goto bad;
		if (!isalpha(c) && !isdigit(c) && c != '_' && c != '-')
			goto bad;
	} while (*++cp);
	return (1);

D 3
bad:	(void)fprintf(stderr, "rcp: %s: invalid user name\n", cp0);
E 3
I 3
bad:	warnx("%s: invalid user name", cp0);
E 3
	return (0);
}

int
susystem(s, userid)
	int userid;
	char *s;
{
D 5
	register sig_t istat, qstat;
	int status, pid, w;
E 5
I 5
	sig_t istat, qstat;
	int status, w;
	pid_t pid;
E 5

D 5
	if ((pid = vfork()) == 0) {
E 5
I 5
	pid = vfork();
	switch (pid) {
	case -1:
		return (127);
	
	case 0:
E 5
		(void)setuid(userid);
		execl(_PATH_BSHELL, "sh", "-c", s, NULL);
		_exit(127);
	}
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
D 5
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1)
E 5
I 5
	if (waitpid(pid, &status, 0) < 0)
E 5
		status = -1;
	(void)signal(SIGINT, istat);
	(void)signal(SIGQUIT, qstat);
	return (status);
}

BUF *
allocbuf(bp, fd, blksize)
	BUF *bp;
	int fd, blksize;
{
	struct stat stb;
	size_t size;

	if (fstat(fd, &stb) < 0) {
D 3
		err("fstat: %s", strerror(errno));
E 3
I 3
		run_err("fstat: %s", strerror(errno));
E 3
		return (0);
	}
	size = roundup(stb.st_blksize, blksize);
	if (size == 0)
		size = blksize;
	if (bp->cnt >= size)
		return (bp);
	if ((bp->buf = realloc(bp->buf, size)) == NULL) {
		bp->cnt = 0;
D 3
		err("%s", strerror(errno));
E 3
I 3
		run_err("%s", strerror(errno));
E 3
		return (0);
	}
	bp->cnt = size;
	return (bp);
}

void
lostconn(signo)
	int signo;
{
	if (!iamremote)
D 3
		(void)fprintf(stderr, "rcp: lost connection\n");
	exit(1);
}

void
nospace()
{
	(void)fprintf(stderr, "rcp: %s\n", strerror(errno));
E 3
I 3
		warnx("lost connection");
E 3
	exit(1);
}
E 1
