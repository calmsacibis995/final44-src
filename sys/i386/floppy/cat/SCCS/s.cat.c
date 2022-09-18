h09524
s 00002/00002/00037
d D 8.1 93/06/11 15:27:56 bostic 3 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00039
d R 5.2 91/05/09 19:02:31 bostic 2 1
c use right header
e
s 00039/00000/00000
d D 5.1 91/05/09 18:47:01 bostic 1 0
c date and time created 91/05/09 18:47:01 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	register int fd, nr;
	char buf[2048];

	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	for (eval = 0; *argv; ++argv)
		if ((fd = open(*argv, 0, 0)) < 0)
			err(*argv, 1);
		else {
			while ((nr = read(fd, buf, sizeof(buf))) > 0)
				if (write(1, buf, nr) != nr) {
					err(*argv, 1);
					break;
				}
			if (nr == -1)
				err(*argv, 1);
		}
	_exit(eval);
}

#define	PROGNAME	"cat: "
#include "errfunction"
E 1
