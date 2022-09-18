h22621
s 00002/00002/00059
d D 8.1 93/05/31 16:49:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00053
d D 5.3 93/04/26 10:34:37 bostic 3 2
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00006/00004/00049
d D 5.2 91/02/28 13:09:00 bostic 2 1
c ANSI
e
s 00053/00000/00000
d D 5.1 90/06/01 13:04:51 bostic 1 0
c date and time created 90/06/01 13:04:51 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/stat.h>
D 2
#include <sys/file.h>
E 2
I 2
D 3
#include <unistd.h>
E 3
I 3

#include <curses.h>
E 3
E 2
#include <stdio.h>
I 2
#include <stdlib.h>
#include <string.h>
I 3
#include <unistd.h>

#include "deck.h"
#include "cribbage.h"
E 3
E 2
#include "pathnames.h"

I 3
void
E 3
instructions()
{
	extern int errno;
	struct stat sb;
	union wait pstat;
D 2
	pid_t pid, waitpid();
	char *pager, *path, *getenv(), *rindex(), *strerror();
E 2
I 2
	pid_t pid;
	char *pager, *path;
E 2

	if (stat(_PATH_INSTR, &sb)) {
		(void)fprintf(stderr, "cribbage: %s: %s.\n", _PATH_INSTR,
		    strerror(errno));
		exit(1);
	}
D 3
	switch(pid = vfork()) {
E 3
I 3
	switch (pid = vfork()) {
E 3
	case -1:
		(void)fprintf(stderr, "cribbage: %s.\n", strerror(errno));
		exit(1);
	case 0:
		if (!(path = getenv("PAGER")))
			path = _PATH_MORE;
		if (pager = rindex(path, '/'))
			++pager;
		pager = path;
		execlp(path, pager, _PATH_INSTR, (char *)NULL);
		(void)fprintf(stderr, "cribbage: %s.\n", strerror(errno));
		_exit(1);
	default:
		do {
D 2
			pid = waitpid(pid, &pstat, 0);
E 2
I 2
			pid = waitpid(pid, (int *)&pstat, 0);
E 2
		} while (pid == -1 && errno == EINTR);
		if (pid == -1 || pstat.w_status)
			exit(1);
	}
}
E 1
