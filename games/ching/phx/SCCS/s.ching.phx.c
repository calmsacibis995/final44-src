h45543
s 00005/00005/00284
d D 8.1 93/05/31 16:46:07 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00288
d D 5.3 90/06/01 13:04:09 bostic 3 2
c new copyright notice
e
s 00003/00003/00296
d D 5.2 90/04/30 22:06:30 bostic 2 1
c  move data files to /usr/share/games/ching
e
s 00299/00000/00000
d D 5.1 88/10/19 19:55:11 bostic 1 0
c date and time created 88/10/19 19:55:11 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Guy Harris.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
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

/*
 * phx - Print NROFF/TROFF source of change, given the line values.
D 2
 * Assumes that the "hexagrams" file is in the current directory.
E 2
 */
#include <stdio.h>
#include "ching.h"
I 2
#include "pathnames.h"
E 2

struct {
	int	lines;		/* encoded value of lines */
	int	trinum;		/* trigram number */
} table[] = {
	{ 777, 0 },		/* 1 */
	{ 887, 1 },		/* 4 */
	{ 878, 2 },		/* 6 */
	{ 788, 3 },		/* 7 */
	{ 888, 4 },		/* 8 */
	{ 778, 5 },		/* 5 */
	{ 787, 6 },		/* 3 */
	{ 877, 7 },		/* 2 */
};

/*
 * Gives hexagram number from two component trigrams.
 */
int	crosstab[8][8] = {
	1,  34, 5,  26, 11, 9,  14, 43,
	25, 51, 3,  27, 24, 42, 21, 17,
	6,  40, 29, 4,  7,  59, 64, 47,
	33, 62, 39, 52, 15, 53, 56, 31,
	12, 16, 8,  23, 2,  20, 35, 45,
	44, 32, 48, 18, 46, 57, 50, 28,
	13, 55, 63, 22, 36, 37, 30, 49,
	10, 54, 60, 41, 19, 61, 38, 58,
};

int	trigrams[6];
int	moving[6];

FILE	*chingf;		/* stream to read the hexagram file */

char	*gets();

main(argc, argv)
int argc;
char **argv;
{
	register int hexagram;		/* hexagram number */
	register char *hexptr;		/* pointer to string of lines */
	char hexstr[6+1];		/* buffer for reading lines in */
	register int i;

	if (argc < 2)
		hexptr = gets(hexstr);
	else
		hexptr = argv[1];
	if (hexptr == (char *)NULL || strlen(hexptr) != 6) {
		fprintf(stderr, "What kind of a change is THAT?!?\n");
		exit(1);
	}
	for (i = 0; i < 6; i++) {
		trigrams[i] = hexptr[i] - '0';
		if (trigrams[i] == 6 || trigrams[i] == 9)
			moving[i] = 1;
		else
			moving[i] = 0;
	}
D 2
	if ((chingf = fopen("hexagrams", "r")) == (FILE *)NULL) {
		fprintf(stderr, "ching: Can't find hexagram file\n");
E 2
I 2
	if ((chingf = fopen(_PATH_HEX, "r")) == (FILE *)NULL) {
		fprintf(stderr, "ching: can't read %s\n", _PATH_HEX);
E 2
		exit(2);
	}
	phx(doahex(), 0);
	if (changes())
		phx(doahex(), 1);
}

/*
 * Compute the hexagram number, given the trigrams.
 */
int
doahex()
{
	int lower, upper;	/* encoded values of lower and upper trigrams */
	int lnum, unum;		/* indices of upper and lower trigrams */
	register int i;

	lower = codem(0);
	upper = codem(3);
	for (i = 0; i < 8; i++) {
		if (table[i].lines == lower)
			 lnum = table[i].trinum;
		if (table[i].lines == upper)
			 unum = table[i].trinum;
	}
	return(crosstab[lnum][unum]);
}

/*
 * Encode a trigram as a 3-digit number; the digits, from left to right,
 * represent the lines.  7 is a solid (yang) line, 8 is a broken (yin) line.
 */
codem(a)
int a;
{
	register int code, i;
	int factor[3];

	factor[0] = 1;
	factor[1] = 10;
	factor[2] = 100;
	code = 0;

	for (i = a; i < a + 3; i++) {
		switch(trigrams[i]) {

		case YYANG:
		case OYANG:
			code += factor[i%3]*7;
			break;

		case OYIN:
		case YYIN:
			code += factor[i%3]*8;
			break;
		}
	}
	return(code);
}

/*
 * Compute the changes based on moving lines; return 1 if any lines moved,
 * 0 if no lines moved.
 */
changes()
{
	register int cflag;
	register int i;

	cflag = 0;
	for (i = 0; i < 6; i++) {
		if (trigrams[i] == OYIN) {
			trigrams[i] = YYANG;
			cflag++;
		} else if (trigrams[i] == OYANG) {
			trigrams[i] = YYIN;
			cflag++;
		}
	}
	return(cflag);
}

/*
 * Print the NROFF/TROFF source of a hexagram, given the hexagram number;
 * if flag is 0, print the entire source; if flag is 1, ignore the meanings
 * of the lines.
 */
phx(hexagram, flag)
int hexagram;
int flag;
{
	char textln[128+1];		/* buffer for text line */
	register char *lp;		/* pointer into buffer */
	register int thishex;		/* number of hexagram just read */
	int lineno;			/* number of line read in */
	int allmoving;			/* 1 if all lines are moving */
	register int i;

	/*
	 * Search for the hexagram; it begins with a line of the form
	 * .H <hexagram number> <other data>.
	 */
	rewind(chingf);
	for (;;) {
		if (fgets(textln, sizeof(textln), chingf) == (char *)NULL) {
			fprintf(stderr, "ching: Hexagram %d missing\n",
			    hexagram);
			exit(3);
		}
		lp = &textln[0];
		if (*lp++ != '.' || *lp++ != 'H')
			continue;
		while (*lp++ == ' ')
			;
		lp--;
		thishex = atoi(lp);
		if (thishex < 1 || thishex > 64)
			continue;
		if (thishex == hexagram)
			break;
	}

	/*
	 * Print up to the line commentary, which ends with a line of the form
	 * .L <position> <value>
	 */
	fputs(textln, stdout);
	for (;;) {
		if (fgets(textln, sizeof(textln), chingf) == (char *)NULL) {
			fprintf(stderr, "ching: Hexagram %d malformed\n",
			    hexagram);
			exit(3);
		}
		lp = &textln[0];
		if (*lp++ == '.') {
			if (*lp++ == 'L')
				break;
		}
		fputs(textln, stdout);
	}

	/*
	 * Now print the line commentaries, if this is the first hexagram.
	 */
	if (flag)
		return;

	/*
	 * If a line is moving, print its commentary.
	 * The text of the commentary ends with a line either of the form
	 * .L <position> <value>
	 * or of the form
	 * .LA <value>
	 * or of the form
	 * .H <hexagram number> <other arguments>
	 */
	allmoving = 1;
	for (i = 0; i < 6; i++) {
		while (*lp++ == ' ')
			;
		lp--;
		lineno = atoi(lp);
		if (i + 1 != lineno) {
			fprintf(stderr, "ching: Hexagram %d malformed\n",
			    hexagram);
			exit(3);
		}
		if (moving[i])
			fputs(textln, stdout);
		else
			allmoving = 0;
		for (;;) {
			if (fgets(textln, sizeof(textln), chingf) == (char *)NULL)
				break;
			lp = &textln[0];
			if (*lp++ == '.' && (*lp == 'L' || *lp == 'H')) {
				lp++;
				break;
			}
			if (moving[i])
				fputs(textln, stdout);
		}
	}

	/*
	 * If all the lines are moving, print the commentary for that; it
	 * ends with a line of the form
	 * .H <hexagram number> <other arguments>
	 */
	if (*lp == 'A' && allmoving) {
		fputs(textln, stdout);
		for (;;) {
			if (fgets(textln, sizeof(textln), chingf) == (char *)NULL)
				break;
			lp = &textln[0];
			if (*lp++ == '.' || *lp++ == 'H')
				break;
			fputs(textln, stdout);
		}
	}
}
E 1
