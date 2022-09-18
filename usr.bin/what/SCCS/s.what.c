h18650
s 00005/00005/00055
d D 8.1 93/06/06 22:23:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00060
d D 5.5 91/03/02 13:24:15 bostic 7 6
c ANSI
e
s 00001/00011/00060
d D 5.4 90/06/01 18:35:14 bostic 6 5
c new copyright notice
e
s 00004/00004/00067
d D 5.3 88/08/08 18:35:12 bostic 5 4
c handle "@@(#)routine.c"
e
s 00043/00039/00027
d D 5.2 88/07/21 22:23:13 bostic 4 3
c minor cleanups; add Berkeley specific header
e
s 00016/00001/00050
d D 5.1 85/05/31 09:39:30 dist 3 2
c Add copyright
e
s 00001/00000/00050
d D 4.2 81/11/08 13:19:24 root 2 1
c return reasonable exit status
e
s 00050/00000/00000
d D 4.1 80/10/16 06:07:06 root 1 0
c date and time created 80/10/16 06:07:06 by root
e
u
U
t
T
I 1
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
/*
D 8
 * Copyright (c) 1980, 1988 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1980, 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1980, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
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
#include <stdio.h>

/*
 * what
 */
D 4

char	*infile = "Standard input";

E 4
I 4
/* ARGSUSED */
E 4
main(argc, argv)
	int argc;
D 4
	char *argv[];
E 4
I 4
	char **argv;
E 4
{
D 4

	argc--, argv++;
	do {
		if (argc > 0) {
			if (freopen(argv[0], "r", stdin) == NULL) {
				perror(argv[0]);
				exit(1);
			}
			infile = argv[0];
			printf("%s\n", infile);
			argc--, argv++;
E 4
I 4
	if (!*++argv) 
		search();
	else do {
		if (!freopen(*argv, "r", stdin)) {
			perror(*argv);
			exit(1);
E 4
		}
D 4
		fseek(stdin, (long) 0, 0);
		find();
	} while (argc > 0);
E 4
I 4
		printf("%s\n", *argv);
		search();
	} while(*++argv);
E 4
I 2
	exit(0);
E 2
}

D 4
find()
E 4
I 4
D 7
static
E 7
search()
E 4
{
D 4
	static char buf[BUFSIZ];
	register char *cp;
	register int c, cc;
	register char *pat;
E 4
I 4
	register int c;
E 4

D 4
contin:
	while ((c = getchar()) != EOF)
		if (c == '@') {
			for (pat = "(#)"; *pat; pat++)
				if ((c = getchar()) != *pat)
					goto contin;
			putchar('\t');
			while ((c = getchar()) != EOF && c && c != '"' &&
			    c != '>' && c != '\n')
				putchar(c);
			putchar('\n');
		}
E 4
I 4
	while ((c = getchar()) != EOF) {
D 5
		if (c != '@') 
E 5
I 5
loop:		if (c != '@')
E 5
			continue;
		if ((c = getchar()) != '(')
D 5
			continue;
E 5
I 5
			goto loop;
E 5
		if ((c = getchar()) != '#')
D 5
			continue;
E 5
I 5
			goto loop;
E 5
		if ((c = getchar()) != ')')
D 5
			continue;
E 5
I 5
			goto loop;
E 5
		putchar('\t');
		while ((c = getchar()) != EOF && c && c != '"' &&
		    c != '>' && c != '\n')
			putchar(c);
		putchar('\n');
	}
E 4
}
E 1
