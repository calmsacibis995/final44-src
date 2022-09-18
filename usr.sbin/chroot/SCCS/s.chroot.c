h07052
s 00005/00005/00065
d D 8.1 93/06/09 13:22:24 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00020/00057
d D 5.10 93/06/09 13:22:16 bostic 11 9
c well, if I had brains, I'd be dangerous...
e
s 00005/00005/00072
d R 8.1 93/06/06 13:52:05 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00010/00043
d D 5.9 93/02/10 22:55:06 bostic 9 8
c ANSI C, prototypes
e
s 00001/00011/00052
d D 5.8 90/06/01 18:38:20 bostic 8 7
c new copyright notice
e
s 00001/00001/00062
d D 5.7 90/05/23 11:16:49 bostic 7 6
c allow chroot of non-absolute pathnames
e
s 00002/00003/00061
d D 5.6 90/02/21 12:51:01 bostic 6 5
c never installed setuid, so don't need to reset the uid
e
s 00001/00001/00063
d D 5.5 89/05/11 14:06:45 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00062
d D 5.4 89/03/05 21:21:28 bostic 4 3
c add pathnames.h
e
s 00024/00017/00039
d D 5.3 88/12/05 15:24:38 bostic 3 2
c allow command to be appended; redo perror messages to use strerror
e
s 00052/00020/00004
d D 5.2 88/09/15 11:16:59 bostic 2 1
c cleanup city
e
s 00024/00000/00000
d D 5.1 88/09/15 11:15:25 bostic 1 0
c date and time created 88/09/15 11:15:25 by bostic
e
u
U
t
T
I 1
D 2
main(argc,argv)
char *argv[];
E 2
I 2
/*
D 12
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
D 12
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 9
#include <stdio.h>
E 9
I 9
#include <sys/types.h>

I 11
#include <err.h>
E 11
#include <errno.h>
E 9
I 4
D 5
#include "pathnames.h"
E 5
I 5
#include <paths.h>
I 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 9
E 5
E 4

I 9
D 11
void fatal __P((char *));
E 11
void usage __P((void));

int
E 9
main(argc, argv)
	int argc;
D 9
	char **argv;
E 9
I 9
	char *argv[];
E 9
E 2
{
D 3
	char *shell, *getenv();
E 3
I 3
D 9
	extern int errno;
	char *shell, *getenv(), *strerror();
E 9
I 9
	int ch;
	char *shell;
E 9
E 3
D 2
	int code;
	if(argc!=2) error("Usage: chroot <dir>\n");
	code = chdir(argv[1]);
	if(code<0)
		perror(argv[1]),_exit(2);
	code = chroot(argv[1]);
	if(code<0)
		perror(argv[1]),_exit(2);
E 2
I 2

D 3
	if (argc != 2) {
		fprintf(stderr, "usage: chroot directory\n");
E 3
I 3
D 9
	if (argc < 2) {
D 6
		fprintf(stderr, "usage: chroot newroot [command]\n");
E 6
I 6
		(void)fprintf(stderr, "usage: chroot newroot [command]\n");
E 6
E 3
		exit(1);
	}
E 9
I 9
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 11
	if (argc < 2)
E 11
I 11
	if (argc < 1)
E 11
		usage();

E 9
D 3
	if (chdir(argv[1])) {
		fprintf(stderr, "chdir: %s: ", argv[1]);
		perror((char *)NULL);
		exit(1);
	}
	if (chroot(argv[1])) {
		fprintf(stderr, "chroot: %s: ", argv[1]);
		perror((char *)NULL);
		exit(1);
	}
E 3
I 3
D 7
	if (chdir(argv[1]) || chroot(argv[1]))
E 7
I 7
D 11
	if (chdir(argv[1]) || chroot("."))
E 7
		fatal(argv[1]);
E 3
E 2
D 6
	setuid(getuid());
E 6
D 2
	shell = getenv("SHELL");
	if(shell==0)shell = "sh";
	execlp(shell, shell, "-i", 0);
	error("Chroot: No shell\n");
}
error(mesg)
char *mesg;
{
	write(2,mesg,strlen(mesg));
	_exit(2);
E 2
I 2
D 3
	if (!(shell = getenv("SHELL")))
		shell = "/bin/sh";
	execlp(shell, shell, "-i", (char *)NULL);
	fprintf(stderr, "chroot: no shell %s", shell);
E 3
I 3
	if (argv[2]) {
		execvp(argv[2], &argv[2]);
		fatal(argv[2]);
	} else {
		if (!(shell = getenv("SHELL")))
D 4
			shell = "/bin/sh";
E 4
I 4
			shell = _PATH_BSHELL;
E 4
		execlp(shell, shell, "-i", (char *)NULL);
		fatal(shell);
E 11
I 11
	if (chdir(argv[0]) || chroot("."))
		err(1, "%s", argv[0]);

	if (argv[1]) {
		execvp(argv[1], &argv[1]);
		err(1, "%s", argv[1]);
E 11
	}
D 11
	/* NOTREACHED */
}
E 11

I 9
D 11
void
E 9
fatal(msg)
	char *msg;
{
D 9
	extern int errno;

E 9
D 6
	fprintf(stderr, "chroot: %s: %s\n", msg, strerror(errno));
E 6
I 6
	(void)fprintf(stderr, "chroot: %s: %s\n", msg, strerror(errno));
I 9
	exit(1);
E 11
I 11
	if (!(shell = getenv("SHELL")))
		shell = _PATH_BSHELL;
	execlp(shell, shell, "-i", NULL);
	err(1, "%s", shell);
	/* NOTREACHED */
E 11
}

void
usage()
{
	(void)fprintf(stderr, "usage: chroot newroot [command]\n");
E 9
E 6
E 3
	exit(1);
E 2
}
E 1
