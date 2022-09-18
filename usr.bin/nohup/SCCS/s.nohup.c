h50727
s 00005/00005/00086
d D 8.1 93/06/06 15:48:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00012/00073
d D 5.5 93/02/10 22:51:13 bostic 5 4
c ANSI C
e
s 00001/00011/00084
d D 5.4 90/06/01 17:28:06 bostic 4 3
c new copyright notice
e
s 00002/00001/00093
d D 5.3 90/03/05 11:20:00 bostic 3 2
c fix errno for ANSI C variable scoping
e
s 00006/00003/00088
d D 5.2 89/12/02 12:23:07 bostic 2 1
c append, don't truncate the nohup.out file
e
s 00091/00000/00000
d D 5.1 89/05/20 14:21:29 bostic 1 0
c date and time created 89/05/20 14:21:29 by bostic
c from scratch, POSIX.2 compatible
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 5
#include <sys/signal.h>
#include <sys/file.h>
#include <unistd.h>
E 5
I 5
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
E 5
#include <stdio.h>
I 5
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 5

I 3
D 5
extern int errno;
E 5
I 5
void dofile __P((void));
void usage __P((void));
E 5

I 5
int
E 5
E 3
main(argc, argv)
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
{
D 3
	extern int errno;
E 3
D 5
	char *strerror();

E 5
	if (argc < 2)
		usage();

	if (isatty(STDOUT_FILENO))
		dofile();
	if (isatty(STDERR_FILENO) && dup2(STDOUT_FILENO, STDERR_FILENO) == -1) {
		/* may have just closed stderr */
		(void)fprintf(stdin, "nohup: %s\n", strerror(errno));
		exit(1);
	}

	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);

	execvp(argv[1], &argv[1]);
	(void)fprintf(stderr,
	    "nohup: %s: %s\n", argv[1], strerror(errno));
	exit(1);
}

I 5
void
E 5
dofile()
{
	int fd;
	char *p, path[MAXPATHLEN];
I 2
D 5
	off_t lseek();
E 2
	char *getenv(), *strcpy(), *strcat(), *strerror();
E 5

#define	FILENAME	"nohup.out"
	p = FILENAME;
D 2
	if ((fd = open(p, O_RDWR|O_CREAT|O_TRUNC, 0600)) >= 0)
E 2
I 2
D 5
	if ((fd = open(p, O_RDWR|O_CREAT, 0600)) >= 0)
E 5
I 5
	if ((fd = open(p, O_RDWR|O_CREAT, S_IRUSR | S_IWUSR)) >= 0)
E 5
E 2
		goto dupit;
	if (p = getenv("HOME")) {
		(void)strcpy(path, p);
		(void)strcat(path, "/");
		(void)strcat(path, FILENAME);
D 2
		if ((fd = open(p = path, O_RDWR|O_CREAT|O_TRUNC, 0600)) >= 0)
E 2
I 2
D 5
		if ((fd = open(p = path, O_RDWR|O_CREAT, 0600)) >= 0)
E 5
I 5
		if ((fd = open(p = path,
		    O_RDWR|O_CREAT, S_IRUSR | S_IWUSR)) >= 0)
E 5
E 2
			goto dupit;
	}
	(void)fprintf(stderr, "nohup: can't open a nohup.out file.\n");
	exit(1);
D 2
dupit:	if (dup2(fd, STDOUT_FILENO) == -1) {
E 2
I 2

D 5
dupit:	(void)lseek(fd, 0L, SEEK_END);
E 5
I 5
dupit:	(void)lseek(fd, (off_t)0, SEEK_END);
E 5
	if (dup2(fd, STDOUT_FILENO) == -1) {
E 2
		(void)fprintf(stderr, "nohup: %s\n", strerror(errno));
		exit(1);
	}
	(void)fprintf(stderr, "sending output to %s\n", p);
}

I 5
void
E 5
usage()
{
	(void)fprintf(stderr, "usage: nohup command\n");
	exit(1);
}
E 1
