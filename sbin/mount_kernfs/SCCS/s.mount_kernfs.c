h51655
s 00002/00002/00072
d D 8.3 95/05/04 16:31:03 mckusick 4 3
c MOUNT types become names
e
s 00028/00015/00046
d D 8.2 94/03/27 09:04:42 bostic 3 2
c Jan-Simon Pendry's and my new mount code
e
s 00002/00002/00059
d D 8.1 93/06/05 11:02:18 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00061/00000/00000
d D 5.1 92/07/18 15:46:34 pendry 1 0
c date and time created 92/07/18 15:46:34 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
D 2
 * Copyright (c) 1992 The Regents of the University of California
 * All rights reserved.
E 2
I 2
D 3
 * Copyright (c) 1992, 1993
E 3
I 3
 * Copyright (c) 1992, 1993, 1994
E 3
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
D 3
 * %sccs.redist.c.%
 *
 *	%W% (Berkeley) %G%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

I 3
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
#include <sys/param.h>
#include <sys/mount.h>

D 3
#include <errno.h>
E 3
I 3
#include <err.h>
E 3
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

D 3
void usage __P((void));
E 3
I 3
#include "mntopts.h"
E 3

I 3
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

void	usage __P((void));

E 3
int
main(argc, argv)
	int argc;
	char *argv[];
{
	int ch, mntflags;

	mntflags = 0;
D 3
	while ((ch = getopt(argc, argv, "F:")) != EOF)
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
E 3
I 3
	while ((ch = getopt(argc, argv, "o:")) != EOF)
		switch (ch) {
		case 'o':
D 4
			getmntopts(optarg, mopts, &mntflags);
E 4
I 4
			getmntopts(optarg, mopts, &mntflags, 0);
E 4
E 3
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

D 3
	if (mount(MOUNT_KERNFS, argv[1], mntflags, NULL)) {
		(void)fprintf(stderr, "mount_kernfs: %s\n", strerror(errno));
		exit(1);
	}
E 3
I 3
D 4
	if (mount(MOUNT_KERNFS, argv[1], mntflags, NULL))
E 4
I 4
	if (mount("kernfs", argv[1], mntflags, NULL))
E 4
		err(1, NULL);
E 3
	exit(0);
}

void
usage()
{
	(void)fprintf(stderr,
D 3
	    "usage: mount_kernfs [ -F fsoptions ] /kern mount_point\n");
E 3
I 3
		"usage: mount_kernfs [-o options] /kern mount_point\n");
E 3
	exit(1);
}
E 1
