h49082
s 00002/00002/00112
d D 8.6 95/04/26 13:14:23 mckusick 6 5
c update for new kernel filesystem structure (vfsconf)
e
s 00003/00014/00111
d D 8.5 94/03/27 12:32:38 bostic 5 4
c replace -above, -below, -replace with -b, -r, (-above was the
c default)
e
s 00049/00055/00076
d D 8.4 94/03/27 11:57:32 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00007/00007/00124
d D 8.3 94/02/22 02:01:47 pendry 3 2
c ensure mounts use disjoint parts of the namespace
e
s 00033/00001/00098
d D 8.2 94/02/17 07:25:14 pendry 2 1
c apply realpath to the target directory to avoid loops
e
s 00099/00000/00000
d D 8.1 94/02/11 19:20:27 pendry 1 0
c date and time created 94/02/11 19:20:27 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 4
 *
 *	%W% (Berkeley) %G%
E 4
 */

I 4
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
#include <sys/param.h>
#include <sys/mount.h>
I 4

E 4
#include <miscfs/union/union.h>

D 4
#include <errno.h>
E 4
I 4
#include <err.h>
E 4
#include <stdio.h>
D 4
#include <unistd.h>
E 4
#include <stdlib.h>
#include <string.h>
I 4
#include <unistd.h>
E 4

I 2
D 3
static int subdir __P((char *, char *));
E 3
I 3
D 4
static int subdir __P((const char *, const char *));
E 3
E 2
void usage __P((void));
E 4
I 4
#include "mntopts.h"
E 4

I 4
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

int	subdir __P((const char *, const char *));
void	usage __P((void));

E 4
int
main(argc, argv)
	int argc;
	char *argv[];
{
	struct union_args args;
	int ch, mntflags;
I 2
	char target[MAXPATHLEN];
E 2
D 4
	int error = 0;
E 4

	mntflags = 0;
	args.mntflags = UNMNT_ABOVE;
D 5

D 4
	while ((ch = getopt(argc, argv, "F:a:b:r:")) != EOF) {
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
			break;
E 4
I 4
	while ((ch = getopt(argc, argv, "a:b:o:r:")) != EOF) {
E 5
I 5
	while ((ch = getopt(argc, argv, "bo:r")) != EOF)
E 5
		switch (ch) {
E 4
D 5
		case 'a':
D 4
			if (strcmp(optarg, "bove") == 0) {
				args.mntflags &= ~UNMNT_OPMASK;
				args.mntflags |= UNMNT_ABOVE;
			} else {
				error = 1;
			}
E 4
I 4
			if (strcmp(optarg, "bove") != 0)
				usage();
			args.mntflags &= ~UNMNT_OPMASK;
			args.mntflags |= UNMNT_ABOVE;
E 4
			break;
E 5
D 4

E 4
		case 'b':
D 4
			if (strcmp(optarg, "elow") == 0) {
				args.mntflags &= ~UNMNT_OPMASK;
				args.mntflags |= UNMNT_BELOW;
			} else {
				error = 1;
			}
E 4
I 4
D 5
			if (strcmp(optarg, "elow") != 0)
				usage();
E 5
			args.mntflags &= ~UNMNT_OPMASK;
			args.mntflags |= UNMNT_BELOW;
E 4
			break;
D 4

E 4
I 4
		case 'o':
D 6
			getmntopts(optarg, mopts, &mntflags);
E 6
I 6
			getmntopts(optarg, mopts, &mntflags, 0);
E 6
			break;
E 4
		case 'r':
D 4
			if (strcmp(optarg, "eplace") == 0) {
				args.mntflags &= ~UNMNT_OPMASK;
				args.mntflags |= UNMNT_REPLACE;
			} else {
				error = 1;
			}
E 4
I 4
D 5
			if (strcmp(optarg, "eplace") != 0)
				usage();
E 5
			args.mntflags &= ~UNMNT_OPMASK;
			args.mntflags |= UNMNT_REPLACE;
E 4
			break;
D 4

E 4
		case '?':
		default:
D 4
			error = 1;
			break;
E 4
I 4
			usage();
I 5
			/* NOTREACHED */
E 5
E 4
		}
D 5
	}
E 5
	argc -= optind;
	argv += optind;

	if (argc != 2)
D 4
		error = 1;

	if (error)
E 4
		usage();

D 2
	args.target = argv[0];
E 2
I 2
D 4
	if (realpath(argv[0], target) == 0) {
		(void)fprintf(stderr, "mount_union: %s: %s\n",
				target, strerror(errno));
		exit(1);
	}
E 4
I 4
	if (realpath(argv[0], target) == 0)
		err(1, "%s", target);
E 4
E 2

I 2
D 3
	if (subdir(target, argv[1])) {
E 3
I 3
D 4
	if (subdir(target, argv[1]) || subdir(argv[1], target)) {
E 3
		(void)fprintf(stderr,
D 3
			"mount_union: %s is a sub-directory of %s\n",
				argv[0], argv[1]);
E 3
I 3
			"mount_union: %s (%s) and %s are not distinct paths\n",
				argv[0], target, argv[1]);
E 3
		exit(1);
	}
E 4
I 4
	if (subdir(target, argv[1]) || subdir(argv[1], target))
		errx(1, "%s (%s) and %s are not distinct paths",
		    argv[0], target, argv[1]);
E 4

	args.target = target;

E 2
D 4
	if (mount(MOUNT_UNION, argv[1], mntflags, &args)) {
		(void)fprintf(stderr, "mount_union: %s\n", strerror(errno));
		exit(1);
	}
E 4
I 4
D 6
	if (mount(MOUNT_UNION, argv[1], mntflags, &args))
E 6
I 6
	if (mount("union", argv[1], mntflags, &args))
E 6
		err(1, NULL);
E 4
	exit(0);
I 2
}

D 4
static int
E 4
I 4
int
E 4
subdir(p, dir)
D 3
	char *p;
	char *dir;
E 3
I 3
	const char *p;
	const char *dir;
E 3
{
	int l;

	l = strlen(dir);
	if (l <= 1)
		return (1);

D 3
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/'))
E 3
I 3
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/' || p[l] == '\0'))
E 3
		return (1);

	return (0);
E 2
}

void
usage()
{
	(void)fprintf(stderr,
D 4
	    "usage: mount_union [ -F fsoptions ] target_fs mount_point\n");
E 4
I 4
D 5
		"usage: mount_union [-o options] target_fs mount_point\n");
E 5
I 5
		"usage: mount_union [-br] [-o options] target_fs mount_point\n");
E 5
E 4
	exit(1);
}
E 1
