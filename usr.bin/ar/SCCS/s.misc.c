h33689
s 00003/00002/00120
d D 8.4 95/04/27 16:37:17 bostic 11 10
c error() wasn't printing the error string, even though it should
c always (well, unless write returns short) contain an interesting value.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00121
d D 8.3 94/04/02 10:04:01 pendry 10 9
c add 1994 copyright
e
s 00026/00022/00096
d D 8.2 94/04/01 04:59:38 pendry 9 8
c prettyness police
e
s 00002/00002/00116
d D 8.1 93/06/06 14:19:34 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00006/00116
d D 5.7 91/05/27 11:10:04 bostic 7 6
c block every signal that we can block
e
s 00001/00001/00121
d D 5.6 91/03/21 12:16:05 bostic 6 5
c rename -s option to -T (Sys V. compatibility)
e
s 00019/00004/00103
d D 5.5 91/03/11 21:18:11 bostic 5 4
c add orphans function; files() bug fix -- return the argv matched.
c 
e
s 00001/00001/00106
d D 5.4 91/03/11 10:27:49 bostic 4 3
c get truncated names right -- it's 15 chars, not 16
e
s 00002/00000/00105
d D 5.3 91/03/10 16:26:06 bostic 3 2
c add -s option which inserts/matches truncated member names
e
s 00003/00002/00102
d D 5.2 91/03/10 15:37:04 bostic 2 1
c ANSI
e
s 00104/00000/00000
d D 5.1 91/01/17 18:23:53 bostic 1 0
c date and time created 91/01/17 18:23:53 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 10
 * Copyright (c) 1990, 1993
E 10
I 10
 * Copyright (c) 1990, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 8
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
D 2
#include <sys/signal.h>
E 2
D 9
#include <sys/errno.h>
I 2
#include <signal.h>
E 9
I 9

E 9
E 2
#include <dirent.h>
I 2
D 9
#include <unistd.h>
E 9
I 9
#include <err.h>
#include <errno.h>
#include <signal.h>
E 9
E 2
#include <stdio.h>
I 5
#include <stdlib.h>
#include <string.h>
I 9
#include <unistd.h>

E 9
E 5
D 2
#include "pathnames.h"
E 2
#include "archive.h"
I 5
#include "extern.h"
E 5
I 2
#include "pathnames.h"
E 2

D 9
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */
E 9
char *tname = "temporary file";		/* temporary file "name" */

I 9
int
E 9
tmp()
{
	extern char *envtmp;
	sigset_t set, oset;
	static int first;
	int fd;
	char path[MAXPATHLEN];

	if (!first && !envtmp) {
		envtmp = getenv("TMPDIR");
		first = 1;
	}

	if (envtmp)
		(void)sprintf(path, "%s/%s", envtmp, _NAME_ARTMP);
	else
D 9
		bcopy(_PATH_ARTMP, path, sizeof(_PATH_ARTMP));
E 9
I 9
		strcpy(path, _PATH_ARTMP);
E 9
	
D 7
	sigemptyset(&set);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGTERM);
E 7
I 7
	sigfillset(&set);
E 7
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	if ((fd = mkstemp(path)) == -1)
		error(tname);
        (void)unlink(path);
D 7
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
E 7
I 7
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
E 7
D 9
	return(fd);
E 9
I 9
	return (fd);
E 9
}

/*
 * files --
 *	See if the current file matches any file in the argument list; if it
 * 	does, remove it from the argument list.
 */
I 5
char *
E 5
files(argv)
	char **argv;
{
D 9
	register char **list;
I 5
	char *p;
E 9
I 9
	char **list, *p;
E 9
E 5

	for (list = argv; *list; ++list)
		if (compare(*list)) {
I 5
			p = *list;
E 5
D 9
			for (; list[0] = list[1]; ++list);
D 5
			return(1);
E 5
I 5
			return(p);
E 9
I 9
			for (; list[0] = list[1]; ++list)
				continue;
			return (p);
E 9
E 5
		}
D 5
	return(0);
E 5
I 5
D 9
	return(NULL);
E 9
I 9
	return (NULL);
E 9
E 5
}

I 5
void
orphans(argv)
	char **argv;
{
I 9

E 9
	for (; *argv; ++argv)
D 9
		(void)fprintf(stderr,
		    "ar: %s: not found in archive.\n", *argv);
E 9
I 9
		warnx("%s: not found in archive", *argv);
E 9
}

E 5
char *
rname(path)
	char *path;
{
D 9
	register char *ind;
E 9
I 9
	char *ind;
E 9

D 9
	return((ind = rindex(path, '/')) ? ind + 1 : path);
E 9
I 9
	return ((ind = strrchr(path, '/')) ? ind + 1 : path);
E 9
}

I 9
int
E 9
compare(dest)
	char *dest;
{
I 9

E 9
D 5
	char *rname();

E 5
I 3
D 6
	if (options & AR_S)
E 6
I 6
	if (options & AR_TR)
E 6
D 4
		return(!strncmp(chdr.name, rname(dest), ARNAMEMAX));
E 4
I 4
D 9
		return(!strncmp(chdr.name, rname(dest), OLDARMAXNAME));
E 4
E 3
	return(!strcmp(chdr.name, rname(dest)));
E 9
I 9
		return (!strncmp(chdr.name, rname(dest), OLDARMAXNAME));
	return (!strcmp(chdr.name, rname(dest)));
E 9
}

I 5
void
E 5
badfmt()
{
D 9
	errno = EFTYPE;
	error(archive);
E 9
I 9

D 11
	errx(1, "%s: %s", archive, strerror(EFTYPE));
E 11
I 11
	errno = EFTYPE;
	err(1, "%s", archive);
E 11
E 9
}

I 5
void
E 5
error(name)
	char *name;
{
D 9
	(void)fprintf(stderr, "ar: %s: %s\n", name, strerror(errno));
	exit(1);
E 9
I 9

D 11
	errx(1, "%s", name);
E 11
I 11
	err(1, "%s", name);
E 11
E 9
}
E 1
