h49520
s 00005/00005/00153
d D 8.1 93/05/31 17:26:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00157
d D 5.5 90/06/01 13:11:34 bostic 5 4
c new copyright notice
e
s 00005/00005/00163
d D 5.4 90/05/02 14:38:07 bostic 4 3
c off by one on argument processing
e
s 00012/00007/00156
d D 5.3 88/06/18 14:54:41 bostic 3 2
c install approved copyright notice
e
s 00004/00003/00159
d D 5.2 88/01/02 20:59:15 bostic 2 1
c John Gilmore's changes for ANSI C and general cleanup
e
s 00162/00000/00000
d D 5.1 88/01/02 20:53:24 bostic 1 0
c date and time created 88/01/02 20:53:24 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1987 Regents of the University of California.
E 3
I 3
D 6
 * Copyright (c) 1980 Regents of the University of California.
E 3
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
 */

#ifndef lint
D 6
char copyright[] =
D 3
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 3
I 3
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	<stdio.h>
# include	"deck.h"

/*
 *	This program initializes the card files for monopoly.
 * It reads in a data file with Com. Chest cards, followed by
 * the Chance card.  The two are seperated by a line of "%-".
 * All other cards are seperated by lines of "%%".  In the front
 * of the file is the data for the decks in the same order.
 * This includes the seek pointer for the start of each card.
 * All cards start with their execution code, followed by the
 * string to print, terminated with a null byte.
 */

# define	TRUE	1
# define	FALSE	0

# define	bool	char
# define	reg	register

char	*infile		= "cards.inp",		/* input file		*/
	*outfile	= "cards.pck";		/* "packed" file	*/

D 2
long	ftell();
E 2
I 2
extern long	ftell();
extern char *calloc();
E 2

DECK	deck[2];

FILE	*inf, *outf;

main(ac, av)
int	ac;
char	*av[]; {

	getargs(ac, av);
	if ((inf = fopen(infile, "r")) == NULL) {
		perror(infile);
		exit(1);
	}
	count();
	/*
	 * allocate space for pointers.
	 */
D 2
	CC_D.offsets = calloc(CC_D.num_cards + 1, sizeof (long));
	CH_D.offsets = calloc(CH_D.num_cards + 1, sizeof (long));
E 2
I 2
	CC_D.offsets = (long *)calloc(CC_D.num_cards + 1, sizeof (long));
	CH_D.offsets = (long *)calloc(CH_D.num_cards + 1, sizeof (long));
E 2
	fseek(inf, 0L, 0);
	if ((outf = fopen(outfile, "w")) == NULL) {
		perror(outfile);
		exit(0);
	}

	fwrite(deck, sizeof (DECK), 2, outf);
	fwrite(CC_D.offsets, sizeof (long), CC_D.num_cards, outf);
	fwrite(CH_D.offsets, sizeof (long), CH_D.num_cards, outf);
	putem();

	fclose(inf);
	fseek(outf, 0, 0L);
	fwrite(deck, sizeof (DECK), 2, outf);
	fwrite(CC_D.offsets, sizeof (long), CC_D.num_cards, outf);
	fwrite(CH_D.offsets, sizeof (long), CH_D.num_cards, outf);
	fclose(outf);
	printf("There were %d com. chest and %d chance cards\n", CC_D.num_cards, CH_D.num_cards);
	exit(0);
}

getargs(ac, av)
int	ac;
char	*av[]; {

D 4
	if (ac > 2) {
		infile = av[2] ? av[2] : infile;
		if (ac > 3)
			outfile = av[3];
	}
E 4
I 4
	if (ac > 1)
		infile = av[1];
	if (ac > 2)
		outfile = av[2];
E 4
}
I 4

E 4
/*
 * count the cards
 */
count() {

	reg bool	newline;
	reg DECK	*in_deck;
	reg char	c;

	newline = TRUE;
	in_deck = &CC_D;
	while ((c=getc(inf)) != EOF)
		if (newline && c == '%') {
			newline = FALSE;
			in_deck->num_cards++;
			if (getc(inf) == '-')
				in_deck = &CH_D;
		}
		else
			newline = (c == '\n');
	in_deck->num_cards++;
}
/*
 *	put strings in the file
 */
putem() {

	reg bool	newline;
	reg DECK	*in_deck;
	reg char	c;
	reg int		num;

	in_deck = &CC_D;
	CC_D.num_cards = 1;
	CH_D.num_cards = 0;
	CC_D.offsets[0] = ftell(outf);
	putc(getc(inf), outf);
	putc(getc(inf), outf);
	for (num = 0; (c=getc(inf)) != '\n'; )
		num = num * 10 + (c - '0');
	putw(num, outf);
	newline = FALSE;
	while ((c=getc(inf)) != EOF)
		if (newline && c == '%') {
			putc('\0', outf);
			newline = FALSE;
			if (getc(inf) == '-')
				in_deck = &CH_D;
			while (getc(inf) != '\n')
				continue;
			in_deck->offsets[in_deck->num_cards++] = ftell(outf);
			if ((c=getc(inf)) == EOF)
				break;
			putc(c, outf);
			putc(c = getc(inf), outf);
			for (num = 0; (c=getc(inf)) != EOF && c != '\n'; )
				num = num * 10 + (c - '0');
			putw(num, outf);
		}
		else {
			putc(c, outf);
			newline = (c == '\n');
		}
	putc('\0', outf);
}
E 1
