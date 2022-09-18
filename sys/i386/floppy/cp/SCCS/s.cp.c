h17118
s 00002/00002/00044
d D 8.1 93/06/11 15:28:26 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00046/00000/00000
d D 5.1 91/05/09 18:47:20 bostic 1 0
c date and time created 91/05/09 18:47:20 by bostic
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

#include <fcntl.h>

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	register int from, to, nr;
	char buf[2048];

	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	if (argc != 3) {
		err("usage: cp file1 file2", 0);
		_exit(1);
	}
	if ((from = open(argv[0], O_RDONLY, 0)) < 0)
		err(argv[0], 1);
	else if ((to = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0666)) < 0)
		err(argv[1], 1);
	else {
		while ((nr = read(from, buf, sizeof(buf))) > 0)
			if (write(to, buf, nr) != nr) {
				err(argv[1], 1);
				break;
			}
		if (nr == -1)
			err(argv[0], 1);
	}
	_exit(eval);
}

#define	PROGNAME	"cp: "
#include "errfunction"
E 1
