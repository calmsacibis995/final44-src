h31735
s 00002/00002/00052
d D 8.3 94/04/02 10:02:06 pendry 10 9
c add 1994 copyright
e
s 00002/00001/00052
d D 8.2 94/04/01 03:24:27 pendry 9 8
c prettyness police
e
s 00005/00005/00048
d D 8.1 93/05/31 15:46:59 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00051
d D 5.7 93/04/29 14:50:58 bostic 7 6
c prettiness police
e
s 00024/00007/00028
d D 5.6 91/10/31 10:45:25 bostic 6 5
c use getopt(3)
e
s 00003/00001/00032
d D 5.5 91/04/08 11:32:51 bostic 5 4
c ANSI
e
s 00001/00011/00032
d D 5.4 90/05/31 20:39:20 bostic 4 3
c new copyright notice
e
s 00010/00005/00033
d D 5.3 88/06/29 21:54:33 bostic 3 2
c install approved copyright notice
e
s 00033/00017/00005
d D 5.2 88/06/06 15:58:18 bostic 2 1
c rewrite and add Berkeley specific header; atoi is in the C library
c yank to rev. level 5
e
s 00022/00000/00000
d D 4.1 80/10/01 17:28:26 bill 1 0
c date and time created 80/10/01 17:28:26 by bill
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
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 10
 * Copyright (c) 1988, 1993
E 10
I 10
 * Copyright (c) 1988, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
D 10
"%Z% Copyright (c) 1988, 1993\n\
E 10
I 10
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 10
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 5
D 9
#include <unistd.h>
E 9
E 5
#include <stdio.h>
I 5
#include <stdlib.h>
I 9
#include <unistd.h>
E 9
E 5

I 6
void usage __P((void));

I 7
int
E 7
E 6
E 2
main(argc, argv)
D 2
char **argv;
E 2
I 2
	int argc;
D 6
	char **argv;
E 6
I 6
	char *argv[];
E 6
E 2
{
D 2
	int c, n;
	char *s;
E 2
I 2
D 6
	int secs;
E 6
I 6
	int ch, secs;
E 6
E 2

D 2
	n = 0;
	if(argc < 2) {
		printf("arg count\n");
		exit(0);
E 2
I 2
D 6
	if (argc != 2) {
D 5
		fputs("usage: sleep time\n", stderr);
E 5
I 5
		(void)fprintf(stderr, "usage: sleep time\n");
E 5
		exit(1);
E 2
	}
D 2
	s = argv[1];
	while(c = *s++) {
		if(c<'0' || c>'9') {
			printf("bad character\n");
			exit(0);
		}
		n = n*10 + c - '0';
	}
	sleep(n);
E 2
I 2
	if ((secs = atoi(argv[1])) > 0)
E 6
I 6
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if ((secs = atoi(*argv)) > 0)
E 6
		(void)sleep(secs);
	exit(0);
I 6
}

void
usage()
{
I 9

E 9
D 7
	(void)fprintf(stderr, "usage: sleep time\n");
E 7
I 7
	(void)fprintf(stderr, "usage: sleep seconds\n");
E 7
	exit(1);
E 6
E 2
}
E 1
