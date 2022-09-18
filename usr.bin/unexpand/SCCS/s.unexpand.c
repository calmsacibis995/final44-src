h14081
s 00005/00005/00100
d D 8.1 93/06/06 16:40:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00103
d D 5.3 91/04/18 18:34:39 bostic 5 4
c new copyright; att/bsd/shared
e
s 00017/00006/00098
d D 5.2 88/10/26 21:22:13 bostic 4 3
c written by Bill Joy; add Berkeley copyright
e
s 00016/00001/00088
d D 5.1 85/05/31 09:35:55 dist 3 2
c Add copyright
e
s 00005/00005/00084
d D 4.2 83/02/09 15:19:56 sam 2 1
c from sun
e
s 00089/00000/00000
d D 4.1 80/10/01 17:29:09 bill 1 0
c date and time created 80/10/01 17:29:09 by bill
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
D 5
/*
E 5
I 5
/*-
E 5
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

#ifndef lint
D 6
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 3
/*
 * unexpand - put tabs into a file replacing blanks
 */
#include <stdio.h>

char	genbuf[BUFSIZ];
char	linebuf[BUFSIZ];
int	all;

main(argc, argv)
	int argc;
	char *argv[];
{
	register char *cp;

	argc--, argv++;
D 2
	if (argv[0][0] == '-') {
E 2
I 2
	if (argc > 0 && argv[0][0] == '-') {
E 2
		if (strcmp(argv[0], "-a") != 0) {
			fprintf(stderr, "usage: unexpand [ -a ] file ...\n");
			exit(1);
		}
		all++;
		argc--, argv++;
	}
	do {
		if (argc > 0) {
			if (freopen(argv[0], "r", stdin) == NULL) {
				perror(argv[0]);
				exit(1);
			}
			argc--, argv++;
		}
		while (fgets(genbuf, BUFSIZ, stdin) != NULL) {
			for (cp = linebuf; *cp; cp++)
				continue;
			if (cp > linebuf)
				cp[-1] = 0;
			tabify(all);
			printf("%s", linebuf);
		}
	} while (argc > 0);
	exit(0);
}

tabify(c)
	char c;
{
	register char *cp, *dp;
	register int dcol;
	int ocol;

	ocol = 0;
	dcol = 0;
	cp = genbuf, dp = linebuf;
	for (;;) {
		switch (*cp) {

		case ' ':
			dcol++;
			break;

		case '\t':
D 2
			dcol =+ 8;
			dcol =& ~07;
E 2
I 2
			dcol += 8;
			dcol &= ~07;
E 2
			break;

		default:
			while (((ocol + 8) &~ 07) <= dcol) {
				if (ocol + 1 == dcol)
					break;
				*dp++ = '\t';
D 2
				ocol =+ 8;
				ocol =& ~07;
E 2
I 2
				ocol += 8;
				ocol &= ~07;
E 2
			}
			while (ocol < dcol) {
				*dp++ = ' ';
				ocol++;
			}
			if (*cp == 0 || c == 0) {
				strcpy(dp, cp);
				return;
			}
			*dp++ = *cp;
			ocol++, dcol++;
		}
		cp++;
	}
}
E 1
