h24320
s 00005/00005/00121
d D 8.1 93/06/06 14:39:57 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00125
d D 5.5 90/06/01 16:50:06 bostic 8 7
c new copyright notice
e
s 00001/00001/00135
d D 5.4 90/05/15 19:56:18 bostic 7 6
c string.h is ANSI C include file
e
s 00081/00064/00055
d D 5.3 90/04/05 08:19:12 bostic 6 5
c use getopt, change -# to -w#, don't call function per character
e
s 00015/00004/00104
d D 5.2 88/06/29 21:50:42 bostic 5 4
c install approved copyright notice
e
s 00016/00001/00092
d D 5.1 85/05/31 09:13:04 dist 4 3
c Add copyright
e
s 00000/00002/00093
d D 4.3 84/09/17 10:46:23 ralph 3 2
c don't call setbuf.
e
s 00003/00003/00092
d D 4.2 83/02/09 15:15:50 sam 2 1
c silence warningsd
e
s 00095/00000/00000
d D 4.1 80/10/01 17:26:49 bill 1 0
c date and time created 80/10/01 17:26:49 by bill
e
u
U
t
T
I 1
D 4
static char *sccsid = "%W% (Berkeley) %G%";
E 4
I 4
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
E 6
I 6
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
E 6
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
I 6
 * This code is derived from software contributed to Berkeley by
 * Kevin Ruddy.
 *
E 6
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
D 6
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
E 5
 */

#ifndef lint
D 9
char copyright[] =
D 6
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

E 4
#include <stdio.h>
D 6
/*
 * fold - fold long lines for finite output devices
 *
 * Bill Joy UCB June 28, 1977
 */
E 6
I 6
D 7
#include <strings.h>
E 7
I 7
#include <string.h>
E 7
E 6

D 6
int	fold =  80;
E 6
I 6
#define	DEFLINEWIDTH	80
E 6

main(argc, argv)
	int argc;
D 6
	char *argv[];
E 6
I 6
	char **argv;
E 6
{
D 6
	register c;
	FILE *f;
E 6
I 6
	extern int errno, optind;
	extern char *optarg;
	register int ch;
	int width;
	char *p;
E 6
D 3
	char obuf[BUFSIZ];
E 3

D 6
	argc--, argv++;
D 3
	setbuf(stdout, obuf);
E 3
	if (argc > 0 && argv[0][0] == '-') {
		fold = 0;
		argv[0]++;
		while (*argv[0] >= '0' && *argv[0] <= '9')
D 2
			fold =* 10, fold =+ *argv[0]++ - '0';
E 2
I 2
			fold *= 10, fold += *argv[0]++ - '0';
E 2
		if (*argv[0]) {
			printf("Bad number for fold\n");
			exit(1);
		}
		argc--, argv++;
	}
	do {
		if (argc > 0) {
			if (freopen(argv[0], "r", stdin) == NULL) {
				perror(argv[0]);
E 6
I 6
	width = -1;
	while ((ch = getopt(argc, argv, "0123456789w:")) != EOF)
		switch (ch) {
		case 'w':
			if ((width = atoi(optarg)) <= 0) {
				(void)fprintf(stderr,
				    "fold: illegal width value.\n");
E 6
				exit(1);
			}
D 6
			argc--, argv++;
E 6
I 6
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (width == -1) {
				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					width = atoi(++p);
				else
					width = atoi(argv[optind] + 1);
			}
			break;
		default:
			(void)fprintf(stderr,
			    "usage: fold [-w width] [file ...]\n");
			exit(1);
E 6
		}
D 6
		for (;;) {
			c = getc(stdin);
			if (c == -1)
				break;
			putch(c);
		}
	} while (argc > 0);
E 6
I 6
	argv += optind;
	argc -= optind;

	if (width == -1)
		width = DEFLINEWIDTH;
	if (!*argv)
		fold(width);
	else for (; *argv; ++argv)
		if (!freopen(*argv, "r", stdin)) {
			(void)fprintf(stderr,
			    "fold: %s: %s\n", *argv, strerror(errno));
			exit(1);
		} else
			fold(width);
E 6
	exit(0);
}

D 6
int	col;

putch(c)
	register c;
E 6
I 6
fold(width)
	register int width;
E 6
{
D 6
	register ncol;
E 6
I 6
	register int ch, col, new;
E 6

D 6
	switch (c) {
E 6
I 6
	for (col = 0;;) {
		switch (ch = getchar()) {
		case EOF:
			return;
		case '\b':
			new = col ? col - 1 : 0;
			break;
E 6
		case '\n':
D 6
			ncol = 0;
E 6
I 6
		case '\r':
			new = 0;
E 6
			break;
		case '\t':
D 6
			ncol = (col + 8) &~ 7;
E 6
I 6
			new = (col + 8) & ~7;
E 6
			break;
I 6
		default:
			new = col + 1;
			break;
		}

		if (new > width) {
			putchar('\n');
			col = 0;
		}
		putchar(ch);

		switch (ch) {
E 6
		case '\b':
D 6
			ncol = col ? col - 1 : 0;
E 6
I 6
			if (col > 0)
				--col;
E 6
			break;
D 6
		case '\r':
			ncol = 0;
			break;
		default:
			ncol = col + 1;
	}
	if (ncol > fold)
		putchar('\n'), col = 0;
	putchar(c);
	switch (c) {
E 6
		case '\n':
I 6
		case '\r':
E 6
			col = 0;
			break;
		case '\t':
D 2
			col =+ 8;
			col =& ~7;
E 2
I 2
			col += 8;
			col &= ~7;
E 2
			break;
D 6
		case '\b':
			if (col)
				col--;
			break;
		case '\r':
			col = 0;
			break;
E 6
		default:
D 6
			col++;
E 6
I 6
			++col;
E 6
			break;
I 6
		}
E 6
	}
}
E 1
