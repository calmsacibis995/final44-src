h19101
s 00002/00002/00030
d D 8.1 93/06/11 15:30:00 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00010/00030
d D 5.2 91/05/09 19:01:32 bostic 2 1
c use right header
e
s 00040/00000/00000
d D 5.1 91/05/09 18:57:47 bostic 1 0
c date and time created 91/05/09 18:57:47 by bostic
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
I 2
 *
 *	%W% (Berkeley) %G%
E 2
 */
D 2

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	if (argc != 3) {
		err("usage: mv file1 file2", 0);
		_exit(1);
	}
	if (rename(argv[0], argv[1])) {
		err(argv[1], 1);
		_exit(1);
	}
	_exit(0);
}

#define	PROGNAME	"mv: "
#include "errfunction"
E 1
