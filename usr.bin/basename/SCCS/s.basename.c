h20761
s 00001/00000/00112
d D 8.4 95/05/04 15:33:45 bostic 12 11
c optarg/optind moved to unistd.h
e
s 00002/00002/00110
d D 8.3 94/04/02 10:04:40 pendry 11 10
c add 1994 copyright
e
s 00010/00004/00102
d D 8.2 94/04/01 05:20:35 pendry 10 9
c prettyness police
e
s 00005/00005/00101
d D 8.1 93/06/06 14:23:01 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00081/00020/00025
d D 5.1 91/03/09 12:36:22 bostic 8 7
c POSIX.2, Draft 11
e
s 00001/00011/00044
d D 4.7 90/06/01 16:37:10 bostic 7 6
c new copyright notice
e
s 00006/00004/00049
d D 4.6 88/11/29 17:22:35 bostic 6 5
c add usage message on incorrect invocation
e
s 00010/00005/00043
d D 4.5 88/06/29 21:54:27 bostic 5 4
c install approved copyright notice
e
s 00025/00022/00023
d D 4.4 87/12/05 18:23:08 bostic 4 3
c bug report usr.bin/118; rewrote, now Berkeley code
e
s 00018/00004/00027
d D 4.3 87/12/02 16:10:53 bostic 3 2
c bug report 4.3BSD/usr.bin/106; handle 1st arg as suffix of 2nd arg 
c new header
e
s 00002/00001/00029
d D 4.2 82/10/20 16:30:14 mckusick 2 1
c use <> for standard include files
e
s 00030/00000/00000
d D 4.1 80/10/01 17:25:06 bill 1 0
c date and time created 80/10/01 17:25:06 by bill
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
D 8
/*
 * Copyright (c) 1987 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
E 8
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 9
I 9
D 11
 * Copyright (c) 1991, 1993
E 11
I 11
 * Copyright (c) 1991, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
E 4
 */
E 3
D 2
#include	"stdio.h"
E 2
I 2

D 3
#include	<stdio.h>
E 3
I 3
#ifndef lint
D 9
char copyright[] =
D 8
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
D 11
"%Z% Copyright (c) 1991, 1993\n\
E 11
I 11
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 11
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */
E 3
E 2

I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 6
#include <stdio.h>
I 8
#include <stdlib.h>
#include <string.h>
I 12
#include <unistd.h>
E 12
E 8

I 10
void usage __P((void));

int
E 10
E 6
D 4
#include <stdio.h>

E 4
E 3
main(argc, argv)
D 4
char **argv;
E 4
I 4
	int argc;
	char **argv;
E 4
{
D 4
	register char *p1, *p2, *p3;
E 4
I 4
D 8
	register char *p, *t;
	char *base;
E 8
I 8
D 10
	extern int optind;
	register char *p;
E 10
I 10
	char *p;
E 10
	int ch;
E 8
E 4

D 4
	if (argc < 2) {
E 4
I 4
D 6
	if (argc <= 1) {	/* backward compatible */
E 4
		putchar('\n');
E 6
I 6
D 8
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "usage: basename string [suffix]\n");
E 6
		exit(1);
E 8
I 8
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1 && argc != 2)
		usage();

	/*
	 * (1) If string is // it is implementation defined whether steps (2)
	 *     through (5) are skipped or processed.
	 *
	 * (2) If string consists entirely of slash characters, string shall
	 *     be set to a single slash character.  In this case, skip steps
	 *     (3) through (5).
	 */
	for (p = *argv;; ++p) {
		if (!*p) {
			if (p > *argv)
				(void)printf("/\n");
			else
				(void)printf("\n");
			exit(0);
		}
		if (*p != '/')
			break;
E 8
	}
D 4
	p1 = argv[1];
	p2 = p1;
	while (*p1) {
		if (*p1++ == '/')
			p2 = p1;
E 4
I 4
D 8
	for (p = base = *++argv; *p;)
		if (*p++ == '/')
			base = p;
D 6
	if (argc > 2) {		/* original version allows any # of args */
E 6
I 6
	if (argc == 3) {
E 6
		for (t = *++argv; *t; ++t);
		do {
			if (t == *argv) {
				*p = '\0';
				break;
			}
		} while (p >= base && *--t == *--p);
E 8
I 8

	/*
	 * (3) If there are any trailing slash characters in string, they
	 *     shall be removed.
	 */
D 10
	for (; *p; ++p);
	while (*--p == '/');
E 10
I 10
	for (; *p; ++p)
		continue;
	while (*--p == '/')
		continue;
E 10
	*++p = '\0';

	/*
	 * (4) If there are any slash characters remaining in string, the
	 *     prefix of string up to an including the last slash character
	 *     in string shall be removed.
	 */
	while (--p >= *argv)
		if (*p == '/')
			break;
	++p;

	/*
	 * (5) If the suffix operand is present, is not identical to the
	 *     characters remaining in string, and is identical to a suffix
	 *     of the characters remaining in string, the suffix suffix
	 *     shall be removed from string.
	 */
	if (*++argv) {
		int suffixlen, stringlen, off;

		suffixlen = strlen(*argv);
		stringlen = strlen(p);

		if (suffixlen < stringlen) {
			off = stringlen - suffixlen;
			if (!strcmp(p + off, *argv))
				p[off] = '\0';
		}
E 8
E 4
	}
D 4
	if (argc>2) {
		for(p3=argv[2]; *p3; p3++) 
			;
D 3
		while(p1>p2 && p3>argv[2])
			if(*--p3 != *--p1)
E 3
I 3
		while(p3>argv[2])
			if(p1 <= p2 || *--p3 != *--p1)
E 3
				goto output;
		*p1 = '\0';
	}
output:
	puts(p2, stdout);
E 4
I 4
D 6
	puts(base);
E 6
I 6
D 8
	printf("%s\n", base);
E 8
I 8
	(void)printf("%s\n", p);
E 8
E 6
E 4
	exit(0);
I 8
}

I 10
void
E 10
usage()
{
I 10

E 10
	(void)fprintf(stderr, "usage: basename string [suffix]\n");
	exit(1);
E 8
}
E 1
