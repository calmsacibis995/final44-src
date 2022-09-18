h21072
s 00009/00018/00070
d D 8.2 95/04/29 10:12:07 bostic 8 7
c Basically err(3)ification + an include fix.
c From: Adam Glass  <glass@netbsd.org>
e
s 00005/00005/00083
d D 8.1 93/06/06 14:25:09 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00054/00025/00034
d D 5.4 91/07/26 13:00:04 bostic 6 5
c ANSI/getopt/cleanup time
e
s 00001/00011/00058
d D 5.3 90/06/01 16:37:31 bostic 5 4
c new copyright notice
e
s 00017/00007/00052
d D 5.2 88/09/15 14:35:05 bostic 4 3
c add Berkeley specific copyright
e
s 00015/00002/00044
d D 5.1 85/05/31 09:07:07 dist 3 2
c Add copyright
e
s 00003/00001/00043
d D 4.2 83/07/02 00:54:22 sam 2 1
c include fixes
e
s 00044/00000/00000
d D 4.1 80/10/18 23:36:40 bill 1 0
c date and time created 80/10/18 23:36:40 by bill
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

E 3
I 2
#ifndef lint
E 2
I 1
D 3
static char *sccsid ="%W% (Berkeley) %G%";
I 2
#endif
E 3
I 3
D 7
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 3
E 2
D 6
/*
 * biff
 */
E 6
D 4

E 4
#include <sys/types.h>
D 2
#include <stat.h>
E 2
I 2
#include <sys/stat.h>
I 8

#include <err.h>
E 8
I 6
#include <errno.h>
D 8
#include <unistd.h>
E 8
E 6
E 2
#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
I 8
#include <unistd.h>
E 8
E 6

D 6
char	*ttyname();
E 6
I 6
static void usage __P((void));
D 8
static void err __P((char *));
E 8
E 6

I 8
int
E 8
main(argc, argv)
	int argc;
D 6
	char **argv;
E 6
I 6
	char *argv[];
E 6
{
D 6
	char *cp = ttyname(2);
	struct stat stb;
E 6
I 6
	struct stat sb;
	int ch;
	char *name;
E 6

D 6
	argc--, argv++;
	if (cp == 0)
		fprintf(stderr, "Where are you?\n"), exit(1);
	if (stat(cp, &stb) < 0)
		perror(cp), exit(1);
	if (argc == 0) {
		printf("is %s\n", stb.st_mode&0100 ? "y" : "n");
		exit((stb.st_mode&0100) ? 0 : 1);
E 6
I 6
D 8

E 8
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 8
	if ((name = ttyname(STDERR_FILENO)) == NULL) {
		(void)fprintf(stderr, "biff: unknown tty\n");
		exit(2);
E 6
	}
E 8
I 8
	if ((name = ttyname(STDERR_FILENO)) == NULL)
		err(2, "tty");
E 8
D 6
	switch (argv[0][0]) {
E 6

D 6
	case 'y':
		if (chmod(cp, stb.st_mode|0100) < 0)
			perror(cp);
		break;
E 6
I 6
	if (stat(name, &sb))
D 8
		err(name);
E 8
I 8
		err(2, "stat");
E 8
E 6

I 6
	if (*argv == NULL) {
		(void)printf("is %s\n", sb.st_mode&0100 ? "y" : "n");
		exit(sb.st_mode & 0100 ? 0 : 1);
	}

	switch(argv[0][0]) {
E 6
	case 'n':
D 6
		if (chmod(cp, stb.st_mode&~0100) < 0)
			perror(cp);
E 6
I 6
		if (chmod(name, sb.st_mode & ~0100) < 0)
D 8
			err(name);
E 8
I 8
			err(2, name);
E 8
E 6
		break;
D 6

E 6
I 6
	case 'y':
		if (chmod(name, sb.st_mode | 0100) < 0)
D 8
			err(name);
E 8
I 8
			err(2, name);
E 8
		break;
E 6
	default:
D 6
		fprintf(stderr, "usage: biff [y] [n]\n");
E 6
I 6
		usage();
E 6
	}
D 6
	exit((stb.st_mode&0100) ? 0 : 1);
E 6
I 6
	exit(sb.st_mode & 0100 ? 0 : 1);
D 8
}

static void
err(name)
	char *name;
{
	(void)fprintf(stderr, "biff: %s: %s\n", name, strerror(errno));
	exit(2);
E 8
}

static void
usage()
{
	(void)fprintf(stderr, "usage: biff [y | n]\n");
	exit(2);
E 6
}
E 1
