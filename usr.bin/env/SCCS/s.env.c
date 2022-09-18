h35465
s 00002/00002/00054
d D 8.3 94/04/02 10:09:14 pendry 6 5
c add 1994 copyright
e
s 00010/00008/00046
d D 8.2 94/04/01 13:07:36 pendry 5 4
c prettyness police
e
s 00005/00005/00049
d D 8.1 93/06/06 14:37:16 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00053
d D 5.3 90/06/01 16:48:18 bostic 3 2
c new copyright notice
e
s 00001/00001/00063
d D 5.2 90/05/15 19:57:03 bostic 2 1
c string.h is ANSI C include file
e
s 00061/00000/00000
d D 5.1 88/09/27 13:52:30 bostic 1 0
c date and time created 88/09/27 13:52:30 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 1988, 1993
E 6
I 6
 * Copyright (c) 1988, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
D 6
"%Z% Copyright (c) 1988, 1993\n\
E 6
I 6
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 6
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 5
#include <err.h>
E 5
#include <stdio.h>
D 2
#include <strings.h>
E 2
I 2
#include <string.h>
I 5
#include <stdlib.h>
#include <unistd.h>
E 5
E 2

I 5
extern char **environ;

int
E 5
main(argc, argv)
	int argc;
	char **argv;
{
D 5
	extern char **environ;
	extern int errno, optind;
	register char **ep, *p;
E 5
I 5
	char **ep, *p;
E 5
	char *cleanenv[1];
	int ch;

	while ((ch = getopt(argc, argv, "-")) != EOF)
D 5
		switch((char)ch) {
E 5
I 5
		switch(ch) {
E 5
		case '-':
			environ = cleanenv;
			cleanenv[0] = NULL;
			break;
		case '?':
		default:
			(void)fprintf(stderr,
			    "usage: env [-] [name=value ...] [command]\n");
			exit(1);
		}
D 5
	for (argv += optind; *argv && (p = index(*argv, '=')); ++argv)
E 5
I 5
	for (argv += optind; *argv && (p = strchr(*argv, '=')); ++argv)
E 5
		(void)setenv(*argv, ++p, 1);
	if (*argv) {
		execvp(*argv, argv);
D 5
		(void)fprintf(stderr, "env: %s: %s\n", *argv,
		    strerror(errno));
		exit(1);
E 5
I 5
		err(1, "%s", *argv);
E 5
	}
	for (ep = environ; *ep; ep++)
		(void)printf("%s\n", *ep);
	exit(0);
}
E 1
