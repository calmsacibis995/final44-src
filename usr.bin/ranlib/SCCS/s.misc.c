h05687
s 00002/00002/00076
d D 8.1 93/06/06 16:03:43 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00075
d D 5.4 93/04/10 00:04:19 torek 4 3
c make $TMPDIR actually work; print actual temp name on mkstemp() error
e
s 00010/00011/00068
d D 5.3 92/02/04 18:19:46 bostic 3 2
c use TMPDIR to specify the tmp directory; handle signals better
c when creating the temp file
e
s 00002/00001/00077
d D 5.2 91/02/26 14:53:13 bostic 2 1
c ANSI fixes (one real bug!)
e
s 00078/00000/00000
d D 5.1 91/01/18 18:45:37 bostic 1 0
c date and time created 91/01/18 18:45:37 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/signal.h>
D 2
#include <sys/errno.h>
E 2
I 2
#include <errno.h>
#include <unistd.h>
E 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathnames.h"

extern char *archive;			/* archive name */
char *tname = "temporary file";		/* temporary file "name" */

tmp()
{
	sigset_t set, oset;
	int fd;
D 3
	char path[MAXPATHLEN];
E 3
I 3
	char *envtmp, path[MAXPATHLEN];
E 3

D 3
	bcopy(_PATH_RANTMP, path, sizeof(_PATH_RANTMP));

	sigemptyset(&set);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGTERM);
E 3
I 3
D 4
	if (envtmp = getenv("TMPDIR"))
		(void)sprintf(path, "%s/%s", envtmp, _PATH_RANTMP);
E 4
I 4
	if ((envtmp = getenv("TMPDIR")) != NULL)
		(void)sprintf(path, "%s%s", envtmp, strrchr(_PATH_RANTMP, '/'));
E 4
	else
		bcopy(_PATH_RANTMP, path, sizeof(_PATH_RANTMP));
	
	sigfillset(&set);
E 3
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	if ((fd = mkstemp(path)) == -1)
D 4
		error(tname);
E 4
I 4
		error(path);
E 4
        (void)unlink(path);
D 3
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
E 3
I 3
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
E 3
	return(fd);
}

void *
emalloc(len)
	int len;
{
D 3
	char *p;
E 3
I 3
	void *p;
E 3

D 3
	if (!(p = malloc((u_int)len)))
E 3
I 3
	if ((p = malloc((u_int)len)) == NULL)
E 3
		error(archive);
	return(p);
}

char *
rname(path)
	char *path;
{
	register char *ind;

	return((ind = rindex(path, '/')) ? ind + 1 : path);
}

badfmt()
{
	errno = EFTYPE;
	error(archive);
}

error(name)
	char *name;
{
	(void)fprintf(stderr, "ranlib: %s: %s\n", name, strerror(errno));
	exit(1);
}
E 1
