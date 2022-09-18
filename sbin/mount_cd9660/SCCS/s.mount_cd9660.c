h20699
s 00005/00005/00098
d D 8.7 95/05/01 22:48:44 mckusick 7 6
c Get rid of the need for the readonly mandatory option - set readonly
c flags regardless of whether the user specified it (from David Greenman)
e
s 00003/00003/00100
d D 8.6 95/04/26 12:44:15 mckusick 6 5
c update for new kernel filesystem structure (vfsconf)
e
s 00002/00003/00101
d D 8.5 94/05/06 22:15:47 mckusick 5 4
c type in conversion
e
s 00048/00040/00056
d D 8.4 94/03/27 08:31:47 bostic 4 3
c Jan-Simon Pendry and my new mount code
c mount_cd9660 pretty much completely rewritten for cleanliness, KNF, and ANSI
e
s 00016/00011/00080
d D 8.3 94/02/18 10:24:41 pendry 3 2
c lint, KNF, fix error messages
e
s 00002/00002/00089
d D 8.2 94/01/23 23:54:42 mckusick 2 1
c ISOFS => CD9660
e
s 00091/00000/00000
d D 8.1 94/01/21 18:27:41 mckusick 1 0
c date and time created 94/01/21 18:27:41 by mckusick
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992, 1993
E 4
I 4
 * Copyright (c) 1992, 1993, 1994
E 4
 *      The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *      %W% (Berkeley) %G%
 */

#ifndef lint
static char copyright[] =
D 4
"%Z% Copyright (c) 1992, 1993\n\
E 4
I 4
"%Z% Copyright (c) 1992, 1993, 1994\n\
E 4
        The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 3
#include <stdio.h>
E 3
#include <sys/param.h>
D 2
#define ISOFS
E 2
I 2
D 6
#define CD9660
E 6
E 2
#include <sys/mount.h>
I 6
#include <sys/../isofs/cd9660/cd9660_mount.h>
E 6

I 3
D 4
#include <errno.h>
E 4
I 4
#include <err.h>
E 4
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

E 3
D 4
#define DEFAULT_ROOTUID	-2
E 4
I 4
#include "mntopts.h"
E 4

D 4
void
D 3
usage ()
E 3
I 3
usage()
E 3
{
E 4
I 4
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	MOPT_UPDATE,
	{ NULL }
};
E 4

D 3
	fprintf (stderr, "usage: mount_iso bdev dir\n");
	exit (1);
E 3
I 3
D 4
	fprintf(stderr,
		"usage: mount_cd9660 [-F fsoptions] [-norrip] [-gen] [-extattr] special node\n");
	exit(1);
E 3
}
		
E 4
I 4
void	usage __P((void));

E 4
int
D 3
main (argc, argv)
E 3
I 3
main(argc, argv)
E 3
	int argc;
	char **argv;
{
D 4
	char *dev;
	char *dir;
E 4
	struct iso_args args;
D 3
	int c;
	int opts = 0, mntflags = 0;
E 3
I 3
D 4
	int mntflags = 0, opts = 0;
E 4
I 4
	int ch, mntflags, opts;
D 5
	char *dev, *dir, *options;
E 5
I 5
	char *dev, *dir;
E 5
E 4
E 3

D 4
	argc--;
	argv++;
	while (argc > 2) {
		if (!strcmp("-F", argv[0])) {
			argc--; argv++;
			mntflags |= atoi(argv[0]);
			argc--; argv++;
		} else if (!strcmp(argv[0], "-norrip")) {
			opts |= ISOFSMNT_NORRIP;
			argc--; argv++;
		} else if (!strcmp(argv[0], "-gen")) {
			opts |= ISOFSMNT_GENS;
			argc--; argv++;
		} else if (!strcmp(argv[0], "-extattr")) {
E 4
I 4
D 5
	options = NULL;
E 5
	mntflags = opts = 0;
	while ((ch = getopt(argc, argv, "ego:r")) != EOF)
		switch (ch) {
		case 'e':
E 4
			opts |= ISOFSMNT_EXTATT;
D 4
			argc--; argv++;
		} else if (!strcmp(argv[0], "-notrans")) {
			opts |= ISOFSMNT_NOTRANS;
			argc--; argv++;
		} else
E 4
I 4
			break;
		case 'g':
			opts |= ISOFSMNT_GENS;
			break;
		case 'o':
D 5
			getmntopts(options, mopts, &mntflags);
E 5
I 5
D 6
			getmntopts(optarg, mopts, &mntflags);
E 6
I 6
			getmntopts(optarg, mopts, &mntflags, 0);
E 6
E 5
			break;
		case 'r':
			opts |= ISOFSMNT_NORRIP;
			break;
		case '?':
		default:
E 4
			usage();
D 4
	}
E 4
I 4
		}
	argc -= optind;
	argv += optind;
E 4

I 4
	if (argc != 2)
		usage();

E 4
	dev = argv[0];
	dir = argv[1];

I 4
#define DEFAULT_ROOTUID	-2
I 7
	/*
	 * ISO 9660 filesystems are not writeable.
	 */
	mntflags |= MNT_RDONLY;
	args.export.ex_flags = MNT_EXRDONLY;
E 7
E 4
	args.fspec = dev;
	args.export.ex_root = DEFAULT_ROOTUID;
I 4
D 7

E 4
	if (mntflags & MNT_RDONLY)
		args.export.ex_flags = MNT_EXRDONLY;
	else
		args.export.ex_flags = 0;
E 7
	args.flags = opts;

D 2
	if (mount (MOUNT_ISOFS, dir, mntflags, &args) < 0) {
E 2
I 2
D 3
	if (mount (MOUNT_CD9660, dir, mntflags, &args) < 0) {
E 2
		perror ("mount");
		exit (1);
E 3
I 3
D 4
	if (mount(MOUNT_CD9660, dir, mntflags, &args) < 0) {
		(void)fprintf(stderr, "mount_cd9660: %s\n", strerror(errno));
		exit(1);
E 3
	}

E 4
I 4
D 6
	if (mount(MOUNT_CD9660, dir, mntflags, &args) < 0)
E 6
I 6
	if (mount("cd9660", dir, mntflags, &args) < 0)
E 6
		err(1, NULL);
E 4
D 3
	exit (0);
E 3
I 3
	exit(0);
I 4
}

void
usage()
{
	(void)fprintf(stderr,
		"usage: mount_cd9660 [-egrt] [-o options] special node\n");
	exit(1);
E 4
E 3
}
E 1
