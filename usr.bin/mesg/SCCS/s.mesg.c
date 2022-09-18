h46451
s 00005/00000/00073
d D 8.2 94/01/21 17:37:02 bostic 13 12
c add USL's copyright notice
e
s 00005/00005/00068
d D 8.1 93/06/06 15:27:48 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00046/00063
d D 5.4 93/04/26 10:44:40 bostic 11 10
c usage standard err(3) routine
e
s 00010/00010/00099
d D 5.3 92/12/21 16:21:52 bostic 10 9
c use the right #defined constants
e
s 00003/00003/00106
d D 5.2 91/11/13 10:12:58 bostic 9 8
c redeclaration of err()
e
s 00067/00036/00042
d D 5.1 91/08/17 12:30:38 bostic 8 7
c Welcome to that ANSI thang!
e
s 00000/00001/00078
d D 4.7 91/03/01 15:08:36 bostic 7 6
c ANSI
e
s 00001/00011/00078
d D 4.6 90/06/01 17:00:08 bostic 6 5
c new copyright notice
e
s 00010/00005/00079
d D 4.5 88/06/29 21:54:31 bostic 5 4
c install approved copyright notice
e
s 00062/00036/00022
d D 4.4 87/11/24 18:03:05 bostic 4 3
c make all errors return -1; general cleanup/lint; add copyright
e
s 00003/00003/00055
d D 4.3 86/03/13 20:28:13 mckusick 3 2
c setgid to group "write" so that terminals need not be world writable
e
s 00002/00002/00056
d D 4.2 80/10/19 02:04:30 bill 2 1
c compat with biff
e
s 00058/00000/00000
d D 4.1 80/10/01 17:27:25 bill 1 0
c date and time created 80/10/01 17:27:25 by bill
e
u
U
t
T
I 1
D 4
static char *sccsid = "%W% (Berkeley) %G%";
E 4
/*
I 4
D 11
 * Copyright (c) 1987 Regents of the University of California.
E 11
I 11
D 12
 * Copyright (c) 1987, 1993 Regents of the University of California.
E 11
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
I 13
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 13
E 12
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 */

#ifndef lint
D 12
char copyright[] =
D 11
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1987, 1993 Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 8
/*
E 4
 * mesg -- set current tty to accept or
 *	forbid write permission.
 *
 *	mesg [y] [n]
 *		y allow messages
 *		n forbid messages
 */

E 8
D 4
#include <stdio.h>
E 4
#include <sys/types.h>
#include <sys/stat.h>
I 10

I 11
#include <err.h>
E 11
E 10
I 8
#include <errno.h>
D 10
#include <unistd.h>
E 10
E 8
I 4
#include <stdio.h>
I 8
#include <stdlib.h>
#include <string.h>
I 10
#include <unistd.h>
E 10
E 8
E 4

D 4
struct stat sbuf;
E 4
I 4
D 8
static char *tty;
E 8
I 8
D 9
static void err __P((const char *fmt, ...));
static void usage __P((void));
E 9
I 9
D 11
void err __P((const char *fmt, ...));
void usage __P((void));
E 9
E 8
E 4

E 11
I 8
int
E 8
D 4
char *tty;
char *ttyname();

E 4
main(argc, argv)
D 4
char *argv[];
E 4
I 4
	int argc;
D 8
	char **argv;
E 8
I 8
	char *argv[];
E 8
E 4
{
D 4
	int r=0;
	tty = ttyname(2);
	if (tty == 0)
		exit(13);
	if(stat(tty, &sbuf) < 0) error("cannot stat");
	if(argc < 2) {
D 3
		if(sbuf.st_mode & 02)
E 3
I 3
		if(sbuf.st_mode & 020)
E 3
			fprintf(stderr,"is y\n");
		else {	r=1;
			fprintf(stderr,"is n\n");
		}
	} else	switch(*argv[1]) {
		case 'y':
D 2
			newmode(0622); break;
E 2
I 2
D 3
			newmode(sbuf.st_mode|022); break;
E 3
I 3
			newmode(sbuf.st_mode|020); break;
E 4
I 4
D 10
	struct stat sbuf;
E 10
I 10
	struct stat sb;
E 10
D 8
	char *ttyname();
E 8
I 8
	char *tty;
	int ch;
E 8
E 4
E 3
E 2

D 4
		case 'n':
D 2
			newmode(0600); r=1; break;
E 2
I 2
D 3
			newmode(sbuf.st_mode&~022); r=1; break;
E 3
I 3
			newmode(sbuf.st_mode&~020); r=1; break;
E 3
E 2

		default:
			error("usage: mesg [y] [n]");
E 4
I 4
D 8
	if (!(tty = ttyname(2))) {
		fputs("mesg: not a device in /dev.\n", stderr);
		exit(-1);
	}
	if (stat(tty, &sbuf) < 0) {
		perror("mesg");
		exit(-1);
	}
	if (argc < 2) {
E 8
I 8
	while ((ch = getopt(argc, argv, "")) != EOF)
D 10
		switch(ch) {
E 10
I 10
		switch (ch) {
E 10
		case '?':
		default:
D 11
			usage();
E 11
I 11
			goto usage;
E 11
		}
	argc -= optind;
	argv += optind;

D 10
	if (!(tty = ttyname(2)))
E 10
I 10
	if ((tty = ttyname(STDERR_FILENO)) == NULL)
E 10
D 11
		err("ttyname: %s", strerror(errno));
E 11
I 11
		err(1, "ttyname");
E 11
D 10
	if (stat(tty, &sbuf) < 0)
E 10
I 10
	if (stat(tty, &sb) < 0)
E 10
D 11
		err("%s: %s", strerror(errno));
E 11
I 11
		err(1, "%s", tty);
E 11

	if (*argv == NULL) {
E 8
D 10
		if (sbuf.st_mode & 020) {
E 10
I 10
		if (sb.st_mode & S_IWGRP) {
E 10
D 8
			fputs("is y\n", stderr);
E 8
I 8
			(void)fprintf(stderr, "is y\n");
E 8
			exit(0);
E 4
		}
D 4
	exit(r);
E 4
I 4
D 8
		fputs("is n\n", stderr);
E 8
I 8
		(void)fprintf(stderr, "is n\n");
E 8
		exit(1);
	}
I 11

E 11
D 10
#define	OTHER_WRITE	020
D 8
	switch(*argv[1]) {
E 8
I 8
	switch(*argv[0]) {
E 10
I 10
	switch (*argv[0]) {
E 10
E 8
	case 'y':
D 8
		newmode(sbuf.st_mode | OTHER_WRITE);
E 8
I 8
D 10
		if (chmod(tty, sbuf.st_mode | OTHER_WRITE) < 0)
E 10
I 10
		if (chmod(tty, sb.st_mode | S_IWGRP) < 0)
E 10
D 11
			err("%s: %s", strerror(errno));
E 11
I 11
			err(1, "%s", tty);
E 11
E 8
		exit(0);
	case 'n':
D 8
		newmode(sbuf.st_mode &~ OTHER_WRITE);
E 8
I 8
D 10
		if (chmod(tty, sbuf.st_mode &~ OTHER_WRITE) < 0)
E 10
I 10
		if (chmod(tty, sb.st_mode & ~S_IWGRP) < 0)
E 10
D 11
			err("%s: %s", strerror(errno));
E 11
I 11
			err(1, "%s", tty);
E 11
E 8
		exit(1);
D 8
	default:
		fputs("usage: mesg [y] [n]\n", stderr);
		exit(-1);
E 8
	}
D 8
	/*NOTREACHED*/
E 8
I 8
D 11
	usage();
	/* NOTREACHED */
E 8
E 4
}
E 11

D 4
error(s)
char *s;
{
	fprintf(stderr,"mesg: %s\n",s);
	exit(-1);
}

E 4
I 4
D 7
static
E 7
E 4
D 8
newmode(m)
I 4
	u_short m;
E 8
I 8
D 9
static void
E 9
I 9
D 11
void
E 9
usage()
E 8
E 4
{
D 4
	if(chmod(tty,m)<0)
		error("cannot change mode");
E 4
I 4
D 8
	if (chmod(tty, m) < 0) {
		perror("mesg");
		exit(-1);
	}
E 8
I 8
	(void)fprintf(stderr, "usage: mesg [y | n]\n");
E 11
I 11
usage:	(void)fprintf(stderr, "usage: mesg [y | n]\n");
E 11
	exit(2);
D 11
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mesg: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(2);
	/* NOTREACHED */
E 11
E 8
E 4
}
E 1
