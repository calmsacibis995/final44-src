h60641
s 00010/00007/00045
d D 8.2 94/04/03 16:31:05 bostic 3 2
c prettiness police
e
s 00005/00005/00047
d D 8.1 93/06/09 22:45:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00052/00000/00000
d D 5.1 91/06/28 11:25:25 bostic 1 0
c date and time created 91/06/28 11:25:25 by bostic
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
D 3
 * Copyright (c) 1991, 1993
E 3
I 3
 * Copyright (c) 1991, 1993, 1994
E 3
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
D 3
"%Z% Copyright (c) 1991, 1993\n\
E 3
I 3
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 3
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 3
#include <err.h>
E 3
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

I 3
void usage __P((void));

int
E 3
main(argc, argv)
	int argc;
	char *argv[];
{
	int ch;
	char *p;

	while ((ch = getopt(argc, argv, "")) != EOF)
D 3
		switch(ch) {
E 3
I 3
		switch (ch) {
E 3
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 3
	if ((p = getlogin()) == NULL) {
		(void)fprintf(stderr, "logname: %s\n", strerror(errno));
		exit(1);
	}
E 3
I 3
	if ((p = getlogin()) == NULL)
		err(1, NULL);
E 3
	(void)printf("%s\n", p);
	exit(0);
}

I 3
void
E 3
usage()
{
	(void)fprintf(stderr, "usage: logname\n");
	exit(1);
}
E 1
