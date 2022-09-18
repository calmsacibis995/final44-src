h09588
s 00002/00002/00041
d D 8.1 93/06/11 15:29:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00043/00000/00000
d D 5.1 91/05/09 18:47:58 bostic 1 0
c date and time created 91/05/09 18:47:58 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/mount.h>

#define	DEFAULT_ROOTUID	-2

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	struct ufs_args args;

	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	if (argc != 3) {
		err("usage: mount dev dir", 0);
		_exit(1);
	}
	args.fspec = argv[0];
	args.exflags = 0;
	args.exroot = DEFAULT_ROOTUID;;
		
	if (mount(MOUNT_UFS, argv[1], 0, &args)) {
		err(argv[0], 1);
		_exit(1);
	}
	_exit(0);
}

#define	PROGNAME	"mount: "
#include "errfunction"
E 1
