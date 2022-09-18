h20661
s 00001/00001/00041
d D 5.2 90/11/15 10:47:46 bostic 2 1
c lint
e
s 00042/00000/00000
d D 5.1 90/05/12 15:29:57 bostic 1 0
c date and time created 90/05/12 15:29:57 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>

/*
 * oldsyntax --
 *	move the path names to the beginning of the argv array, and return
 *	a pointer to them.  The old find syntax assumes all command arguments
 *	up to the first one beginning with a '-', '(' or '!' are pathnames.
 */
D 2
char **
E 2
I 2
void
E 2
oldsyntax(argvp)
	char ***argvp;
{
	register char **argv;

	/*
	 * find first '-', '(' or '!' to delimit paths; if no paths, it's
	 * an error.  Shift the array back one at the same time, creating
	 * a separate array of pathnames.
	 */
	for (argv = *argvp + 1;; ++argv) {
		argv[-1] = argv[0];
		if (!*argv || **argv == '-' || **argv == '!' || **argv == '(')
			break;
	}

	if (argv == *argvp + 1)
		usage();

	argv[-1] = NULL;
	*argvp = argv;			/* move argv value */
}
E 1
