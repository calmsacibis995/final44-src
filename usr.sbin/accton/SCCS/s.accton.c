h40753
s 00005/00005/00064
d D 8.1 93/06/06 11:36:53 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00066
d D 5.2 91/12/15 16:21:44 bostic 5 4
c off-by-the-usual
e
s 00044/00008/00025
d D 5.1 91/12/15 16:19:36 bostic 4 3
c It's an ANSI kind of world
e
s 00001/00011/00032
d D 4.3 90/06/01 18:37:14 bostic 3 2
c new copyright notice
e
s 00036/00008/00007
d D 4.2 88/06/30 11:46:58 bostic 2 1
c rewritten from manual page; add Berkeley specific header
e
s 00015/00000/00000
d D 4.1 80/10/01 17:24:37 bill 1 0
c date and time created 80/10/01 17:24:37 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
/*
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
D 6
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 4
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
E 4
#include <stdio.h>
I 4
#include <string.h>
E 4

I 4
void usage __P((void));

int
E 4
E 2
main(argc, argv)
D 2
char **argv;
E 2
I 2
	int argc;
D 4
	char **argv;
E 4
I 4
	char *argv[];
E 4
E 2
{
D 2
	extern errno;
	if (argc > 1)
		acct(argv[1]);
	else
		acct((char *)0);
	if (errno) {
E 2
I 2
D 4
	if (argc > 2) {
		fputs("usage: accton [file]\n", stderr);
		exit(1);
E 4
I 4
	int ch;

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	switch(argc) {
D 5
	case 1: 
E 5
I 5
	case 0: 
E 5
		if (acct(NULL)) {
			(void)fprintf(stderr,
			    "accton: %s\n", strerror(errno));
			exit(1);
		}
		break;
D 5
	case 2:
		if (acct(*++argv)) {
E 5
I 5
	case 1:
		if (acct(*argv)) {
E 5
			(void)fprintf(stderr,
			    "accton: %s: %s\n", *argv, strerror(errno));
			exit(1);
		}
		break;
	default:
		usage();
E 4
	}
D 4
	if (acct(argc == 2 ? argv[1] : (char *)NULL)) {
E 2
		perror("accton");
		exit(1);
	}
E 4
	exit(0);
I 4
}

void
usage()
{
	(void)fprintf(stderr, "usage: accton [file]\n");
	exit(1);
E 4
}
E 1
