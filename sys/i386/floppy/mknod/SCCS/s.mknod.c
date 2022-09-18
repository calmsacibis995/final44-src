h27755
s 00002/00002/00051
d D 8.1 93/06/11 15:29:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00000/00000
d D 5.1 91/05/09 18:47:49 bostic 1 0
c date and time created 91/05/09 18:47:49 by bostic
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
#include <sys/stat.h>

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	register char *p;
	register int major, minor;
	unsigned short mode;

	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	if (argc != 5) {
usage:		err("usage: mknod name [b|c] major minor", 0);
		_exit(1);
	}
		
	mode = 0666;
	if (argv[1][0] == 'c')
		mode |= S_IFCHR;
	else if (argv[1][0] == 'b')
		mode |= S_IFBLK;
	else
		goto usage;

	for (major = 0, p = argv[2]; *p; ++p)
                major = major * 10 + *p - '0';
	for (minor = 0, p = argv[3]; *p; ++p)
                minor = minor * 10 + *p - '0';

	if (mknod(argv[0], mode, makedev(major, minor)) < 0) {
		err(argv[0], 1);
		_exit(1);
	}
	_exit(0);
}

#define	PROGNAME	"mknod: "
#include "errfunction"
E 1
