h08368
s 00004/00002/00104
d D 8.4 95/04/26 12:41:05 mckusick 4 3
c update for new kernel filesystem structure (vfsconf)
e
s 00001/00000/00105
d D 8.3 94/07/07 15:53:16 mckusick 3 2
c mount allows use of the force option
e
s 00002/00000/00103
d D 8.2 94/03/27 14:59:47 bostic 2 1
c UFS supports sync, sync
e
s 00103/00000/00000
d D 8.1 94/03/27 08:07:46 bostic 1 0
c date and time created 94/03/27 08:07:46 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char copyright[] =
"%Z% Copyright (c) 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mount.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

I 4
#include <ufs/ufs/ufsmount.h>

E 4
#include "mntopts.h"

void	ufs_usage __P((void));

static struct mntopt mopts[] = {
	MOPT_STDOPTS,
I 2
	MOPT_ASYNC,
	MOPT_SYNC,
E 2
	MOPT_UPDATE,
I 3
	MOPT_FORCE,
E 3
	{ NULL }
};

int
mount_ufs(argc, argv)
	int argc;
	char * const argv[];
{
	extern int optreset;
	struct ufs_args args;
	int ch, mntflags;
	char *fs_name;

	mntflags = 0;
	optind = optreset = 1;		/* Reset for parse of new argv. */
	while ((ch = getopt(argc, argv, "o:")) != EOF)
		switch (ch) {
		case 'o':
D 4
			getmntopts(optarg, mopts, &mntflags);
E 4
I 4
			getmntopts(optarg, mopts, &mntflags, 0);
E 4
			break;
		case '?':
		default:
			ufs_usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		ufs_usage();

        args.fspec = argv[0];		/* The name of the device file. */
	fs_name = argv[1];		/* The mount point. */

#define DEFAULT_ROOTUID	-2
	args.export.ex_root = DEFAULT_ROOTUID;
	if (mntflags & MNT_RDONLY)
		args.export.ex_flags = MNT_EXRDONLY;
	else
		args.export.ex_flags = 0;

D 4
	if (mount(MOUNT_UFS, fs_name, mntflags, &args) < 0) {
E 4
I 4
	if (mount("ufs", fs_name, mntflags, &args) < 0) {
E 4
		(void)fprintf(stderr, "%s on %s: ", args.fspec, fs_name);
		switch (errno) {
		case EMFILE:
			(void)fprintf(stderr, "mount table full.\n");
			break;
		case EINVAL:
			if (mntflags & MNT_UPDATE)
				(void)fprintf(stderr,
		    "Specified device does not match mounted device.\n");
			else 
				(void)fprintf(stderr,
				    "Incorrect super block.\n");
			break;
		default:
			(void)fprintf(stderr, "%s\n", strerror(errno));
			break;
		}
		return (1);
	}
	return (0);
}

void
ufs_usage()
{
	(void)fprintf(stderr, "usage: mount_ufs [-o options] special node\n");
	exit(1);
}
E 1
