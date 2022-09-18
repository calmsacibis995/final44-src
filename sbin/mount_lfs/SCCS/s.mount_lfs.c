h59631
s 00003/00002/00119
d D 8.4 95/04/26 12:46:44 mckusick 5 4
c update for new kernel filesystem structure (vfsconf)
e
s 00035/00037/00086
d D 8.3 94/03/27 09:06:32 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00003/00003/00120
d D 8.2 94/01/23 12:29:43 bostic 3 2
c match rev 8.6 of /sys/sys/mount.h from Mike Hibler
c reorganization for generic support of export information
e
s 00005/00005/00118
d D 8.1 93/06/08 19:13:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00123/00000/00000
d D 5.1 93/06/08 18:48:14 bostic 1 0
c date and time created 93/06/08 18:48:14 by bostic
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
D 4
 * Copyright (c) 1993
E 4
I 4
 * Copyright (c) 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
D 4
"%Z% Copyright (c) 1993\n\
E 4
I 4
"%Z% Copyright (c) 1993, 1994\n\
E 4
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mount.h>
I 5
#include <ufs/ufs/ufsmount.h>
E 5

#include <err.h>
D 4
#include <errno.h>
E 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

I 4
#include "mntopts.h"
E 4
#include "pathnames.h"

D 4
#define DEFAULT_ROOTUID -2	/* copied from mount's UFS code */
E 4
I 4
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	MOPT_UPDATE,
	{ NULL }
};
E 4

D 4
void usage __P((void));
void invoke_cleaner __P((char *));
E 4
I 4
void	usage __P((void));
void	invoke_cleaner __P((char *));
E 4

int short_rds, cleaner_debug;

int
main(argc, argv)
	int argc;
	char *argv[];
{
	struct ufs_args args;
D 4
	int ch, mntflags;
	int noclean;
	char *fs_name;
E 4
I 4
	int ch, mntflags, noclean;
	char *fs_name, *options;
E 4

I 4
	options = NULL;
E 4
	mntflags = noclean = 0;
D 4
	while ((ch = getopt(argc, argv, "F:nsd")) != EOF)
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
E 4
I 4
	while ((ch = getopt(argc, argv, "dno:s")) != EOF)
		switch (ch) {
		case 'd':
			cleaner_debug = 1;
E 4
			break;
		case 'n':
			noclean = 1;
			break;
I 4
		case 'o':
D 5
			getmntopts(optarg, mopts, &mntflags);
E 5
I 5
			getmntopts(optarg, mopts, &mntflags, 0);
E 5
			break;
E 4
		case 's':
			short_rds = 1;
			break;
D 4
		case 'd':
			cleaner_debug = 1;
			break;
E 4
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

        args.fspec = argv[0];	/* the name of the device file */
	fs_name = argv[1];	/* the mount point */

D 4
	/* copied from mount's UFS code */
E 4
I 4
#define DEFAULT_ROOTUID	-2
E 4
D 3
	args.exroot = DEFAULT_ROOTUID;
E 3
I 3
	args.export.ex_root = DEFAULT_ROOTUID;
E 3
	if (mntflags & MNT_RDONLY)
D 3
		args.exflags = MNT_EXRDONLY;
E 3
I 3
		args.export.ex_flags = MNT_EXRDONLY;
E 3
	else
D 3
		args.exflags = 0;
E 3
I 3
		args.export.ex_flags = 0;
E 3

D 4
	if (mount(MOUNT_LFS, fs_name, mntflags, &args)) {
		(void)fprintf(stderr, "mount_lfs: %s\n", strerror(errno));
		exit(1);
	}
E 4
I 4
D 5
	if (mount(MOUNT_LFS, fs_name, mntflags, &args))
E 5
I 5
	if (mount("lfs", fs_name, mntflags, &args))
E 5
		err(1, NULL);
E 4

D 4
	if (!noclean) {
		/*
		 * invoke the lfs_cleanerd for this filesystem as its arg!
		 */
E 4
I 4
	if (!noclean)
E 4
		invoke_cleaner(fs_name);
D 4
		/* never returns */
	}
E 4
I 4
		/* NOTREACHED */
E 4

	exit(0);
}

void
D 4
usage()
{
	(void)fprintf(stderr,
	    "usage: mount_lfs [ -nsd ] [ -F fsoptions ] device mount_point\n");
	exit(1);
}

void
E 4
invoke_cleaner(name)
	char *name;
{
	char *args[6], **ap = args;

D 4
	/* build the argument list */
E 4
I 4
	/* Build the argument list. */
E 4
	*ap++ = _PATH_LFS_CLEANERD;
	if (short_rds)
		*ap++ = "-s";
	if (cleaner_debug)
		*ap++ = "-d";
	*ap++ = name;
	*ap = NULL;

	execv(args[0], args);
D 4
	err(1, "exec of %x failed", _PATH_LFS_CLEANERD);
E 4
I 4
	err(1, "exec %s", _PATH_LFS_CLEANERD);
}

void
usage()
{
	(void)fprintf(stderr,
		"usage: mount_lfs [-dns] [-o options] special node\n");
	exit(1);
E 4
}
E 1
