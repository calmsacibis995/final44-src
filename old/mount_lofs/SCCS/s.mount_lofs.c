h42303
s 00035/00028/00069
d D 8.4 94/03/27 09:08:36 bostic 8 7
c Jan-Simon Pendry's and my new mount code
e
s 00006/00006/00091
d D 8.3 94/02/22 02:02:14 pendry 7 6
c ensure mounts use disjoint parts of the namespace
e
s 00033/00001/00064
d D 8.2 94/02/17 07:24:17 pendry 6 4
c apply realpath to the target directory to avoid loops
e
s 00035/00002/00063
d R 8.2 94/02/17 06:34:31 pendry 5 4
c add subdirectory check
e
s 00002/00002/00063
d D 8.1 93/06/05 11:02:44 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 5.3 92/07/12 15:14:12 bostic 3 2
c move file systems into misclfs
e
s 00038/00048/00029
d D 5.2 92/07/05 15:46:16 bostic 2 1
c integrate into the source tree, minor cleanups, bug fixes
e
s 00077/00000/00000
d D 5.1 92/07/05 15:36:28 bostic 1 0
c date and time created 92/07/05 15:36:28 by bostic
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
D 8
 * Copyright (c) 1992, 1993
E 8
I 8
 * Copyright (c) 1992, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 4
D 8
 * All rights reserved.
E 8
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 8
 *
 *	%W% (Berkeley) %G%
E 8
 */

I 8
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 8
D 2
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
E 2
#include <sys/param.h>
#include <sys/mount.h>
I 8

E 8
D 3
#include <lofs/lofs.h>
E 3
I 3
#include <miscfs/lofs/lofs.h>
E 3

D 2
main(c, v)
int c;
char *v[];
E 2
I 2
D 8
#include <errno.h>
E 8
I 8
#include <err.h>
E 8
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

I 6
D 7
static int subdir __P((char *, char *));
E 7
I 7
D 8
static int subdir __P((const char *, const char *));
E 7
E 6
void usage __P((void));
E 8
I 8
#include "mntopts.h"
E 8

I 8
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

int	subdir __P((const char *, const char *));
void	usage __P((void));

E 8
int
main(argc, argv)
	int argc;
	char *argv[];
E 2
{
D 2
	extern char *optarg;
	extern int optind;
	int ch;
	int usage = 0;
	int mntflags;
	char *target;
	char *mountpt;
E 2
	struct lofs_args args;
D 2
	int rc;
E 2
I 2
	int ch, mntflags;
I 6
	char target[MAXPATHLEN];
E 6
E 2

D 2
	/*
	 * Crack -F option
	 */
	while ((ch = getopt(c, v, "F:")) != EOF)
	switch (ch) {
	case 'F':
		mntflags = atoi(optarg);
		break;
	default:
	case '?':
		usage++;
		break;
	}
E 2
I 2
	mntflags = 0;
D 8
	while ((ch = getopt(argc, argv, "F:")) != EOF)
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
E 8
I 8
	while ((ch = getopt(argc, argv, "o:")) != EOF)
		switch (ch) {
		case 'o':
			getmntopts(optarg, mopts, &mntflags);
E 8
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 2

D 2
	/*
	 * Need two more arguments
	 */
	if (optind != (c - 2))
		usage++;
E 2
I 2
	if (argc != 2)
		usage();
E 2

D 2
	if (usage) {
		fputs("usage: mount_lofs [ fsoptions ] target-fs mount-point\n", stderr);
		exit(1);
	}
E 2
I 2
D 6
	args.target = argv[0];
E 6
I 6
D 8
	if (realpath(argv[0], target) == 0) {
		(void)fprintf(stderr, "mount_lofs: %s: %s\n",
				target, strerror(errno));
		exit(1);
	}
E 8
I 8
	if (realpath(argv[0], target) == 0)
		err(1, "%s", target);
E 8
E 6
E 2

I 6
D 7
	if (subdir(target, argv[1])) {
E 7
I 7
D 8
	if (subdir(target, argv[1]) || subdir(argv[1], target)) {
E 7
		(void)fprintf(stderr,
D 7
			"mount_lofs: %s (%s) is a sub directory of %s\n",
E 7
I 7
			"mount_lofs: %s (%s) and %s are not distinct paths\n",
E 7
				argv[0], target, argv[1]);
		exit(1);
	}
E 8
I 8
	if (subdir(target, argv[1]) || subdir(argv[1], target))
		errx(1, "%s (%s) and %s are not distinct paths",
		    argv[0], target, argv[1]);
E 8

	args.target = target;

E 6
D 2
	/*
	 * Get target and mount point
	 */
	target = v[optind];
	mountpt = v[optind+1];

	args.target = target;

	rc = mount(MOUNT_LOFS, mountpt, mntflags, &args);
	if (rc < 0) {
		perror("mount_lofs");
E 2
I 2
D 8
	if (mount(MOUNT_LOFS, argv[1], mntflags, &args)) {
		(void)fprintf(stderr, "mount_lofs: %s\n", strerror(errno));
E 2
		exit(1);
	}
E 8
I 8
	if (mount(MOUNT_LOFS, argv[1], mntflags, &args))
		err(1, NULL);
E 8
	exit(0);
I 6
}

D 8
static int
E 8
I 8
int
E 8
subdir(p, dir)
D 7
	char *p;
	char *dir;
E 7
I 7
	const char *p;
	const char *dir;
E 7
{
	int l;

	l = strlen(dir);
	if (l <= 1)
		return (1);

D 7
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/'))
E 7
I 7
	if ((strncmp(p, dir, l) == 0) && (p[l] == '/' || p[l] == '\0'))
E 7
		return (1);

	return (0);
E 6
I 2
}

void
usage()
{
	(void)fprintf(stderr,
D 8
	    "usage: mount_lofs [ -F fsoptions ] target_fs mount_point\n");
E 8
I 8
		"usage: mount_lofs [-o options] target_fs mount_point\n");
E 8
	exit(1);
E 2
}
E 1
