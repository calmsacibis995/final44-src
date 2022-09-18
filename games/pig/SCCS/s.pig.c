h50740
s 00001/00000/00100
d D 8.2 95/05/04 15:28:40 bostic 3 2
c optarg/optind moved to unistd.h
e
s 00005/00005/00095
d D 8.1 93/05/31 17:42:02 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00100/00000/00000
d D 5.1 92/08/18 10:56:05 bostic 1 0
c date and time created 92/08/18 10:56:05 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 3
#include <unistd.h>
E 3

void pigout __P((char *, int));
void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	register int len;
	int ch;
	char buf[1024];

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	for (len = 0; (ch = getchar()) != EOF;) {
		if (isalpha(ch)) {
			if (len >= sizeof(buf)) {
				(void)fprintf(stderr, "pig: ate too much!\n");
				exit(1);
			}
			buf[len++] = ch;
			continue;
		}
		if (len != 0) {
			pigout(buf, len);
			len = 0;
		}
		(void)putchar(ch);
	}
	exit(0);
}

void
pigout(buf, len)
	char *buf;
	int len;
{
	register int ch, start;
	int olen;

	/*
	 * If the word starts with a vowel, append "way".  Don't treat 'y'
	 * as a vowel if it appears first.
	 */
	if (index("aeiouAEIOU", buf[0]) != NULL) {
		(void)printf("%.*sway", len, buf);
		return;
	}

	/*
	 * Copy leading consonants to the end of the word.  The unit "qu"
	 * isn't treated as a vowel.
	 */
	for (start = 0, olen = len;
	    !index("aeiouyAEIOUY", buf[start]) && start < olen;) {
		ch = buf[len++] = buf[start++];
		if ((ch == 'q' || ch == 'Q') && start < olen &&
		    (buf[start] == 'u' || buf[start] == 'U'))
			buf[len++] = buf[start++];
	}
	(void)printf("%.*say", olen, buf + start);
}

void
usage()
{
	(void)fprintf(stderr, "usage: pig\n");
	exit(1);
}
E 1
