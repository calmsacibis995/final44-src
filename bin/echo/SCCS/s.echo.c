h00040
s 00005/00005/00040
d D 8.1 93/05/31 14:24:59 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00043
d D 5.5 93/04/28 17:29:52 bostic 7 6
c lint
e
s 00004/00002/00041
d D 5.4 91/04/03 08:33:40 bostic 6 5
c don't indirect through a NULL on echo w/o arguments
e
s 00001/00011/00042
d D 5.3 90/05/31 20:30:05 bostic 5 4
c new copyright notice
e
s 00009/00014/00044
d D 5.2 89/07/30 10:03:58 bostic 4 3
c something did (lint).  POSIX .2 doesn't plan on defining echo's
c behavior for options, so go back to the original behavior.
e
s 00048/00014/00010
d D 5.1 89/05/28 18:01:39 bostic 3 2
c from scratch, add Berkeley specific copyright
c treat -n as a real argument, see if anything breaks
e
s 00001/00001/00023
d D 4.2 85/05/27 21:44:51 serge 2 1
c don't accept -nANYTHING in place of -n
e
s 00024/00000/00000
d D 4.1 80/10/01 17:26:28 bill 1 0
c date and time created 80/10/01 17:26:28 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
E 6

I 4
D 7
/* ARGSUSED */
E 7
I 7
int
E 7
E 4
main(argc, argv)
D 3
int argc;
char *argv[];
E 3
I 3
	int argc;
D 7
	char **argv;
E 7
I 7
	char *argv[];
E 7
E 3
{
D 3
	register int i, nflg;
E 3
I 3
D 4
	extern int optind;
	int ch, nflag;
E 4
I 4
	int nflag;
E 4
E 3

D 3
	nflg = 0;
D 2
	if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') {
E 2
I 2
	if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n' && !argv[1][2]) {
E 2
		nflg++;
		argc--;
		argv++;
	}
	for(i=1; i<argc; i++) {
		fputs(argv[i], stdout);
		if (i < argc-1)
E 3
I 3
D 4
	nflag = 0;
	while ((ch = getopt(argc, argv, "n")) != EOF)
		switch(ch) {
		case 'n':
			nflag = 1;
			break;
		case '?':
		default:
			(void)fprintf(stderr, "usage: echo [-n] [arg ...]\n");
			exit(1);
		}
	argv += optind;
E 4
I 4
D 6
	++argv;
	if (!strcmp(*argv, "-n")) {
E 6
I 6
	/* This utility may NOT do getopt(3) option parsing. */
	if (*++argv && !strcmp(*argv, "-n")) {
E 6
		++argv;
		nflag = 1;
	}
	else
		nflag = 0;
E 4

	while (*argv) {
		(void)printf("%s", *argv);
		if (*++argv)
E 3
			putchar(' ');
	}
D 3
	if(nflg == 0)
E 3
I 3
	if (!nflag)
E 3
		putchar('\n');
	exit(0);
}
E 1
