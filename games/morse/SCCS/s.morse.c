h23546
s 00005/00005/00114
d D 8.1 93/05/31 17:30:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00119
d D 5.3 91/02/28 14:20:06 bostic 3 2
c ANSI
e
s 00001/00011/00120
d D 5.2 90/06/01 13:10:45 bostic 2 1
c new copyright notice
e
s 00130/00000/00000
d D 5.1 88/08/12 17:52:53 bostic 1 0
c date and time created 88/08/12 17:52:53 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>
#include <ctype.h>

static char
	*digit[] = {
	"-----",
	".----",
	"..---",
	"...--",
	"....-",
	".....",
	"-....",
	"--...",
	"---..",
	"----.",
},
	*alph[] = {
	".-",
	"-...",
	"-.-.",
	"-..",
	".",
	"..-.",
	"--.",
	"....",
	"..",
	".---",
	"-.-",
	".-..",
	"--",
	"-.",
	"---",
	".--.",
	"--.-",
	".-.",
	"...",
	"-",
	"..-",
	"...-",
	".--",
	"-..-",
	"-.--",
	"--..",
};

static int sflag;

main(argc, argv)
	int argc;
	char **argv;
{
	extern char *optarg;
	extern int optind;
	register int ch;
	register char *p;

	while ((ch = getopt(argc, argv, "s")) != EOF)
		switch((char)ch) {
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: morse [string ...]");
			exit(1);
		}
	argc -= optind;
	argv += optind;

	if (*argv)
		do {
			for (p = *argv; *p; ++p)
				morse((int)*p);
		} while (*++argv);
	else while ((ch = getchar()) != EOF)
		morse(ch);
}

D 3
static
E 3
morse(c)
	register int c;
{
	if (isalpha(c))
		show(alph[c - (isupper(c) ? 'A' : 'a')]);
	else if (isdigit(c))
		show(digit[c - '0']);
	else if (c == ',')
		show("--..--");
	else if (c == '.')
		show(".-.-.-");
	else if (isspace(c))
		show(" ...\n");
}

D 3
static
E 3
show(s)
	register char *s;
{
	if (sflag)
		printf(" %s", s);
	else for (; *s; ++s)
		printf(" %s", *s == '.' ? "dit" : "daw");
	printf(",\n");
}
E 1
