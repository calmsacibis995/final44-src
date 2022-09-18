h60010
s 00014/00042/00042
d D 8.2 94/01/05 13:30:34 bostic 5 4
c delete the -p flag from mkfifo
e
s 00005/00005/00079
d D 8.1 93/06/06 15:31:54 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00083
d D 5.3 90/06/01 17:00:53 bostic 3 2
c new copyright notice
e
s 00001/00001/00093
d D 5.2 90/05/15 19:56:48 bostic 2 1
c string.h is ANSI C include file
e
s 00094/00000/00000
d D 5.1 90/05/05 00:00:58 mckusick 1 0
c date and time created 90/05/05 00:00:58 by mckusick
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
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
"%Z% Copyright (c) 1990 Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 5

E 5
#include <errno.h>
#include <stdio.h>
D 2
#include <strings.h>
E 2
I 2
#include <string.h>
E 2

I 5
int
E 5
main(argc, argv)
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
{
D 5
	extern int errno, optind;
	int ch, exitval, pflag;
E 5
I 5
	extern int optind;
	int ch, exitval;
E 5

D 5
	pflag = 0;
	while ((ch = getopt(argc, argv, "p")) != EOF)
E 5
I 5
	while ((ch = getopt(argc, argv, "")) != EOF)
E 5
		switch(ch) {
D 5
		case 'p':
			pflag = 1;
			break;
E 5
		case '?':
		default:
			usage();
		}
D 5

	if (!*(argv += optind))
E 5
I 5
	argc -= optind;
	argv += optind;
	if (argv[0] == NULL)
E 5
		usage();

D 5
	for (exitval = 0; *argv; ++argv) {
		if (pflag && build(*argv)) {
			exitval |= 1;
			continue;
E 5
I 5
	for (exitval = 0; *argv != NULL; ++argv)
		if (mkfifo(*argv, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
			warn("%s", *argv);
			exitval = 1;
E 5
		}
D 5
		if (mkfifo(*argv, 0777) < 0) {
			(void)fprintf(stderr, "mkfifo: %s: %s\n",
			    *argv, strerror(errno));
			exitval |= 1;
		}
	}
E 5
	exit(exitval);
}

D 5
build(path)
	char *path;
{
	register char *p;
	struct stat sb;

	for (p = path; *p; p++) {
		if (*p  != '/')
			continue;
		if (stat(path, &sb)) {
			if (errno != ENOENT || mkdir(path, 0777) < 0) {
				(void)fprintf(stderr, "mkdir: %s: %s\n",
				    path, strerror(errno));
				return(1);
			}
		}
		*p = '/';
	}
	return(0);
}

E 5
usage()
{
D 5
	(void)fprintf(stderr, "usage: mkfifo [-p] fifoname ...\n");
E 5
I 5
	(void)fprintf(stderr, "usage: mkfifo fifoname ...\n");
E 5
	exit(1);
}
E 1
