h29501
s 00002/00002/00101
d D 8.6 95/04/26 13:07:31 mckusick 11 10
c update for new kernel filesystem structure (vfsconf)
e
s 00033/00027/00070
d D 8.5 94/03/27 09:13:06 bostic 10 9
c Jan-Simon Pendry's and my new mount code
e
s 00006/00006/00091
d D 8.4 94/02/22 02:02:06 pendry 9 8
c ensure mounts use disjoint parts of the namespace
e
s 00001/00001/00096
d D 8.3 94/02/18 10:19:08 pendry 8 7
c fix error message
e
s 00033/00001/00064
d D 8.2 94/02/17 07:24:38 pendry 7 4
c apply realpath to the target directory to avoid loops
e
s 00034/00002/00063
d R 8.2 94/02/17 06:34:21 pendry 6 4
c add subdirectory check
e
s 00030/00002/00063
d R 8.2 94/02/17 06:27:29 pendry 5 4
c add subdirectory check
e
s 00002/00002/00063
d D 8.1 93/06/05 11:03:13 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 5.3 92/07/12 15:48:46 bostic 3 2
c move misc file systems to miscfs
e
s 00005/00005/00060
d D 5.2 92/07/11 15:26:20 heideman 2 1
c 
e
s 00065/00000/00000
d D 5.1 92/07/09 13:58:53 heideman 1 0
c date and time created 92/07/09 13:58:53 by heideman
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
D 10
 * Copyright (c) 1992, 1993
E 10
I 10
 * Copyright (c) 1992, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 4
D 10
 * All rights reserved.
E 10
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 10
 *
 *	%W% (Berkeley) %G%
E 10
 */

I 10
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 10
#include <sys/param.h>
#include <sys/mount.h>
D 2
#include <lofs/lofs.h>
E 2
I 2
D 3
#include <nullfs/null.h>
E 3
I 3
#include <miscfs/nullfs/null.h>
E 3
E 2

D 10
#include <errno.h>
E 10
I 10
#include <err.h>
E 10
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

I 7
D 9
static int subdir __P((char *, char *));
E 9
I 9
D 10
static int subdir __P((const char *, const char *));
E 9
E 7
void usage __P((void));
E 10
I 10
#include "mntopts.h"
E 10

I 10
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

int	subdir __P((const char *, const char *));
void	usage __P((void));

E 10
int
main(argc, argv)
	int argc;
	char *argv[];
{
D 2
	struct lofs_args args;
E 2
I 2
	struct null_args args;
E 2
	int ch, mntflags;
I 7
	char target[MAXPATHLEN];
E 7

	mntflags = 0;
D 10
	while ((ch = getopt(argc, argv, "F:")) != EOF)
E 10
I 10
	while ((ch = getopt(argc, argv, "o:")) != EOF)
E 10
		switch(ch) {
D 10
		case 'F':
			mntflags = atoi(optarg);
E 10
I 10
		case 'o':
D 11
			getmntopts(optarg, mopts, &mntflags);
E 11
I 11
			getmntopts(optarg, mopts, &mntflags, 0);
E 11
E 10
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

D 7
	args.target = argv[0];
E 7
I 7
D 10
	if (realpath(argv[0], target) == 0) {
D 8
		(void)fprintf(stderr, "mount_lofs: %s: %s\n",
E 8
I 8
		(void)fprintf(stderr, "mount_null: %s: %s\n",
E 8
				target, strerror(errno));
		exit(1);
	}
E 10
I 10
	if (realpath(argv[0], target) == 0)
		err(1, "%s", target);
E 10
E 7

I 7
D 9
	if (subdir(target, argv[1])) {
E 9
I 9
D 10
	if (subdir(target, argv[1]) || subdir(argv[1], target)) {
E 9
		(void)fprintf(stderr,
D 9
			"mount_null: %s (%s) is a sub directory of %s\n",
E 9
I 9
			"mount_null: %s (%s) and %s are not distinct paths\n",
E 9
				argv[0], target, argv[1]);
		exit(1);
	}
E 10
I 10
	if (subdir(target, argv[1]) || subdir(argv[1], target))
		errx(1, "%s (%s) and %s are not distinct paths",
		    argv[0], target, argv[1]);
E 10

	args.target = target;

E 7
D 2
	if (mount(MOUNT_LOFS, argv[1], mntflags, &args)) {
		(void)fprintf(stderr, "mount_lofs: %s\n", strerror(errno));
E 2
I 2
D 10
	if (mount(MOUNT_NULL, argv[1], mntflags, &args)) {
		(void)fprintf(stderr, "mount_null: %s\n", strerror(errno));
E 2
		exit(1);
	}
E 10
I 10
D 11
	if (mount(MOUNT_NULL, argv[1], mntflags, &args))
E 11
I 11
	if (mount("loopback", argv[1], mntflags, &args))
E 11
		err(1, NULL);
E 10
	exit(0);
I 7
}

D 10
static int
E 10
I 10
int
E 10
subdir(p, dir)
D 9
	char *p;
	char *dir;
E 9
I 9
	const char *p;
	const char *dir;
E 9
{
	int l;

	l = strlen(dir);
	if (l <= 1)
		return (1);

D 9
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/'))
E 9
I 9
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/' || p[l] == '\0'))
E 9
		return (1);

	return (0);
E 7
}

void
usage()
{
	(void)fprintf(stderr,
D 2
	    "usage: mount_lofs [ -F fsoptions ] target_fs mount_point\n");
E 2
I 2
D 10
	    "usage: mount_null [ -F fsoptions ] target_fs mount_point\n");
E 10
I 10
		"usage: mount_null [-o options] target_fs mount_point\n");
E 10
E 2
	exit(1);
}
E 1
