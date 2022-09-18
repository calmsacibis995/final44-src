h04007
s 00001/00000/00118
d D 8.4 95/05/04 15:36:01 bostic 10 9
c optarg/optind moved to unistd.h
e
s 00002/00002/00116
d D 8.3 94/04/02 10:09:05 pendry 9 8
c add 1994 copyright
e
s 00008/00003/00110
d D 8.2 94/04/01 13:04:25 pendry 8 7
c prettyness police
e
s 00005/00005/00108
d D 8.1 93/06/06 14:36:43 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00089/00015/00024
d D 5.6 91/03/09 12:36:33 bostic 6 5
c POSIX.2, Draft 11
e
s 00001/00011/00038
d D 5.5 90/06/01 16:48:03 bostic 5 4
c new copyright notice
e
s 00002/00000/00047
d D 5.4 88/10/12 11:11:02 bostic 4 3
c if no slashes in the name, return "."
e
s 00012/00004/00035
d D 5.3 88/09/26 15:00:53 bostic 3 2
c fix indirect through NULL, add usage; bug report 4.3BSD-tahoe/usr.bin/5
e
s 00010/00005/00029
d D 5.2 88/06/29 21:54:28 bostic 2 1
c install approved copyright notice
e
s 00034/00000/00000
d D 5.1 87/12/05 18:34:52 bostic 1 0
c date and time created 87/12/05 18:34:52 by bostic
e
u
U
t
T
I 1
D 6
/*
 * Copyright (c) 1987 Regents of the University of California.
E 6
I 6
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
E 6
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1991, 1993
E 9
I 9
 * Copyright (c) 1991, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
 */

#ifndef lint
D 7
char copyright[] =
D 6
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
D 9
"%Z% Copyright (c) 1991, 1993\n\
E 9
I 9
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 9
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 3
#include <stdio.h>
I 6
#include <stdlib.h>
I 10
#include <unistd.h>
E 10
E 6

I 8
void usage __P((void));

int
E 8
E 3
main(argc, argv)
	int argc;
	char **argv;
{
D 6
	char *p, *rindex();
E 6
I 6
D 8
	extern int optind;
	register char *p;
E 8
I 8
	char *p;
E 8
	int ch;
E 6

D 3
	p = rindex(*++argv, '/');
	if (p && p > *argv)
		*p = '\0';
	puts(*argv);
E 3
I 3
D 6
	if (argc != 2) {
		fprintf(stderr, "usage: dirname path\n");
		exit(1);
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

	/*
	 * (1) If string is //, skip steps (2) through (5).
	 * (2) If string consists entirely of slash characters, string
	 *     shall be set to a single slash character.  In this case,
	 *     skip steps (3) through (8).
	 */
	for (p = *argv;; ++p) {
		if (!*p) {
			if (p > *argv)
				(void)printf("/\n");
			else
				(void)printf(".\n");
			exit(0);
		}
		if (*p != '/')
			break;
E 6
	}
D 6
	if (p = rindex(*++argv, '/'))
		if (p > *argv)
			*p = '\0';
		else
			*++p = '\0';
I 4
	else
		*argv = ".";
E 4
	printf("%s\n", *argv);
E 6
I 6

	/*
	 * (3) If there are any trailing slash characters in string, they
	 *     shall be removed.
	 */
	for (; *p; ++p);
D 8
	while (*--p == '/');
E 8
I 8
	while (*--p == '/')
		continue;
E 8
	*++p = '\0';

	/*
	 * (4) If there are no slash characters remaining in string,
	 *     string shall be set to a single period character.  In this
	 *     case skip steps (5) through (8).
	 *
	 * (5) If there are any trailing nonslash characters in string,
	 *     they shall be removed.
	 */
	while (--p >= *argv)
		if (*p == '/')
			break;
	++p;
	if (p == *argv) {
		(void)printf(".\n");
		exit(0);
	}

	/*
	 * (6) If the remaining string is //, it is implementation defined
	 *     whether steps (7) and (8) are skipped or processed.
	 *
	 * This case has already been handled, as part of steps (1) and (2).
	 */
	
	/*
	 * (7) If there are any trailing slash characters in string, they
	 *     shall be removed.
	 */
	while (--p >= *argv)
		if (*p != '/')
			break;
	++p;

	/*
	 * (8) If the remaining string is empty, string shall be set to
	 *     a single slash character.
	 */
	*p = '\0';
	(void)printf("%s\n", p == *argv ? "/" : *argv);
E 6
E 3
	exit(0);
I 6
}

I 8
void
E 8
usage()
{
I 8

E 8
	(void)fprintf(stderr, "usage: dirname path\n");
	exit(1);
E 6
}
E 1
