h49493
s 00002/00002/00059
d D 8.1 93/06/06 16:23:18 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00061/00000/00000
d D 5.1 93/06/01 16:44:55 bostic 1 0
c date and time created 93/06/01 16:44:55 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Peter McIlroy.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pathnames.h"

#define _NAME_TMP "sort.XXXXXXXX"

FILE *
ftmp()
{
	static char *envtmp;
	sigset_t set, oset;
	static int first = 0;
	FILE *fd;
	char pathb[_POSIX_PATH_MAX], *path;

	path = pathb;
	if (!first && !envtmp) {
		envtmp = getenv("TMPDIR");
		first = 1;
	}
	if (envtmp)
		(void)snprintf(path,
		    sizeof(pathb), "%s/%s", envtmp, _NAME_TMP);
	else {
		memmove(path, _PATH_SORTTMP, sizeof(_PATH_SORTTMP));
	}
	sigfillset(&set);
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	path = mktemp(path);
	if (!path)
		err(2, "%s");
	if (!(fd = fopen(path, "w+")))
		err(2, "%s", path);
	(void)unlink(path);

	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
	return (fd);
};
E 1
