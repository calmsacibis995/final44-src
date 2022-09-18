h61769
s 00002/00002/00027
d D 8.1 93/06/11 15:30:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00027
d D 5.2 91/05/09 19:00:37 bostic 2 1
c right header
e
s 00027/00000/00000
d D 5.1 91/05/09 19:00:17 bostic 1 0
c date and time created 91/05/09 19:00:17 by bostic
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

int eval;

main(argc, argv)
	int argc;
	char **argv;
{
	if (*++argv && **argv == '-') {
		err("no options available", 0);
		_exit(1);
	}
	for (eval = 0; *argv; ++argv)
		if (unlink(*argv)) {
			err(*argv, 1);
			eval = 1;
		}
	_exit(eval);
}

#define	PROGNAME	"rm: "
#include "errfunction"
E 1
