h63601
s 00002/00002/00072
d D 8.3 95/04/26 12:45:28 mckusick 5 4
c update for new kernel filesystem structure (vfsconf)
e
s 00027/00014/00047
d D 8.2 94/03/27 08:59:53 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00002/00002/00059
d D 8.1 93/06/05 11:02:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00048/00025
d D 5.2 92/07/05 14:27:53 bostic 2 1
c integrate into the source tree, minor cleanups, bug fixes
e
s 00073/00000/00000
d D 5.1 92/07/05 14:15:17 bostic 1 0
c date and time created 92/07/05 14:15:17 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
D 3
 * Copyright (c) 1992 The Regents of the University of California
 * All rights reserved.
E 3
I 3
D 4
 * Copyright (c) 1992, 1993
E 4
I 4
 * Copyright (c) 1992, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 4
 *
 *	%W% (Berkeley) %G%
E 4
D 2
 *
 * $Id: mount_fdesc.c,v 1.1 1992/05/17 17:50:13 jsp Exp jsp $
E 2
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
D 2
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
E 2
#include <sys/param.h>
#include <sys/mount.h>

D 2
main(c, v)
int c;
char *v[];
{
	extern char *optarg;
	extern int optind;
	int ch;
	int usage = 0;
	int mntflags;
	char *dummy;
	char *mountpt;
	int rc;
E 2
I 2
D 4
#include <errno.h>
E 4
I 4
#include <err.h>
E 4
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
D 4
void usage __P((void));
E 4
I 4
#include "mntopts.h"
E 4
E 2

I 4
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

void	usage __P((void));

E 4
D 2
	/*
	 * Need two more arguments
	 */
	if (optind != (c - 2))
		usage++;
E 2
I 2
int
main(argc, argv)
	int argc;
	char *argv[];
{
	int ch, mntflags;
E 2

D 2
	if (usage) {
		fputs("usage: mount_fdesc [ fsoptions ] /dev/fd mount-point\n", stderr);
		exit(1);
	}
E 2
I 2
	mntflags = 0;
D 4
	while ((ch = getopt(argc, argv, "F:")) != EOF)
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
E 4
I 4
	while ((ch = getopt(argc, argv, "o:")) != EOF)
		switch (ch) {
		case 'o':
D 5
			getmntopts(optarg, mopts, &mntflags);
E 5
I 5
			getmntopts(optarg, mopts, &mntflags, 0);
E 5
E 4
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
	 * Get target and mount point
	 */
	dummy = v[optind];
	mountpt = v[optind+1];
E 2
I 2
	if (argc != 2)
		usage();
E 2

D 2
	rc = mount(MOUNT_FDESC, mountpt, mntflags, (caddr_t) 0);
	if (rc < 0) {
		perror("mount_fdesc");
E 2
I 2
D 4
	if (mount(MOUNT_FDESC, argv[1], mntflags, NULL)) {
		(void)fprintf(stderr, "mount_fdesc: %s\n", strerror(errno));
E 2
		exit(1);
	}
E 4
I 4
D 5
	if (mount(MOUNT_FDESC, argv[1], mntflags, NULL))
E 5
I 5
	if (mount("fdesc", argv[1], mntflags, NULL))
E 5
		err(1, NULL);
E 4
	exit(0);
I 2
}

void
usage()
{
	(void)fprintf(stderr,
D 4
	    "usage: mount_fdesc [ -F fsoptions ] /dev/fd mount_point\n");
E 4
I 4
		"usage: mount_fdesc [-o options] fdesc mount_point\n");
E 4
	exit(1);
E 2
}
E 1
