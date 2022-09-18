h17349
s 00005/00005/00093
d D 8.1 93/06/11 14:50:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00011/00068
d D 5.2 93/06/11 14:49:44 bostic 2 1
c integarte into 4.4BSD
e
s 00079/00000/00000
d D 5.1 93/06/11 11:28:14 bostic 1 0
c date and time created 93/06/11 11:28:14 by bostic
e
u
U
t
T
I 1
D 2
/* vi: set tabstop=4 : */
E 2
I 2
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
 */
E 2

I 2
#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
/*
 * Filter out words that:
 *	1) Are not completely made up of lower case letters
 *	2) Contain a 'q' not immediately followed by a 'u'
 *	3) Are less that 3 characters long
 *	4) Are greater than MAXWORDLEN characters long
 */

#include <ctype.h>
#include <stdio.h>
I 2
#include <stdlib.h>
#include <string.h>
E 2

#include "bog.h"

D 2
char *index();

E 2
I 2
int
E 2
main(argc, argv)
D 2
int argc;
char **argv;
E 2
I 2
	int argc;
	char *argv[];
E 2
{
D 2
	register char *p, *q, *r;
E 2
I 2
	register char *p, *q;
E 2
	register int ch, common, n, nwords;
	int current, len, prev, qcount;
	char buf[2][MAXWORDLEN + 1];

	prev = 0;
	current = 1;
	buf[prev][0] = '\0';
	if (argc == 2)
		n = atoi(argv[1]);

D 2
	nwords = 1;
	while (fgets(buf[current], MAXWORDLEN + 1, stdin) != (char *) NULL) {
E 2
I 2
	for (nwords = 1;
	    fgets(buf[current], MAXWORDLEN + 1, stdin) != NULL; ++nwords) {
E 2
		if ((p = index(buf[current], '\n')) == NULL) {
D 2
			fprintf(stderr, "mkdict: word too long: %s\n", buf[current]);
E 2
I 2
			fprintf(stderr,
			    "mkdict: word too long: %s\n", buf[current]);
E 2
			while ((ch = getc(stdin)) != EOF && ch != '\n')
				;
			if (ch == EOF)
				break;
			continue;
		}
		len = 0;
		for (p = buf[current]; *p != '\n'; p++) {
			if (!islower(*p))
				break;
			if (*p == 'q') {
				q = p + 1;
				if (*q != 'u')
					break;
				else {
					while (*q = *(q + 1))
						q++;
				}
				len++;
			}
			len++;
		}
		if (*p != '\n' || len < 3 || len > MAXWORDLEN)
			continue;
D 2
		if (nwords++ % n && argc == 2)
E 2
I 2
		if (argc == 2 && nwords % n)
E 2
			continue;

		*p = '\0';
		p = buf[current];
		q = buf[prev];
		qcount = 0;
		while ((ch = *p++) == *q++ && ch != '\0')
			if (ch == 'q')
				qcount++;
		common = p - buf[current] - 1;
		printf("%c%s", common + qcount, p - 1);
		prev = !prev;
		current = !current;
	}
	fprintf(stderr, "%d words\n", nwords);
	exit(0);
}
D 2

E 2
E 1
