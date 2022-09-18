h56551
s 00002/00002/00025
d D 8.1 93/06/11 15:29:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 91/05/09 18:47:33 bostic 1 0
c date and time created 91/05/09 18:47:33 by bostic
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
		if (mkdir(*argv, 0777) < 0)
			err(*argv, 1);
	_exit(eval);
}

#define	PROGNAME	"mkdir: "
#include "errfunction"
E 1
