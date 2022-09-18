h22589
s 00002/00002/00180
d D 8.1 93/05/31 17:26:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00181
d D 5.4 90/06/01 13:10:56 bostic 4 3
c new copyright notice
e
s 00002/00001/00190
d D 5.3 90/05/12 15:27:01 bostic 3 2
c move to /usr/share, move pathnames to pathnames.h
e
s 00011/00006/00180
d D 5.2 88/06/18 14:54:27 bostic 2 1
c install approved copyright notice
e
s 00186/00000/00000
d D 5.1 88/01/02 20:53:21 bostic 1 0
c date and time created 88/01/02 20:53:21 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1980 Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"monop.ext"
I 3
# include	"pathnames.h"
E 3

/*
 *	These routine deal with the card decks
 */

# define	GOJF	'F'	/* char for get-out-of-jail-free cards	*/

# ifndef DEV
D 3
static char	*cardfile	= "/usr/games/lib/cards.pck";
E 3
I 3
static char	*cardfile	= _PATH_CARDS;
E 3
# else
static char	*cardfile	= "cards.pck";
# endif

static FILE	*deckf;

/*
 *	This routine initializes the decks from the data file,
 * which it opens.
 */
init_decks() {

	if ((deckf=fopen(cardfile, "r")) == NULL) {
file_err:
		perror(cardfile);
		exit(1);
	}
	if (fread(deck, sizeof (DECK), 2, deckf) != 2)
		goto file_err;
	set_up(&CC_D);
	set_up(&CH_D);
}
/*
 *	This routine sets up the offset pointers for the given deck.
 */
set_up(dp)
DECK	*dp; {

	reg int	r1, r2;
	int	i;

	dp->offsets = (long *) calloc(sizeof (long), dp->num_cards);
	if (fread(dp->offsets, sizeof(long), dp->num_cards, deckf) != dp->num_cards) {
		perror(cardfile);
		exit(1);
	}
	dp->last_card = 0;
	dp->gojf_used = FALSE;
	for (i = 0; i < dp->num_cards; i++) {
		reg long	temp;

		r1 = roll(1, dp->num_cards) - 1;
		r2 = roll(1, dp->num_cards) - 1;
		temp = dp->offsets[r2];
		dp->offsets[r2] = dp->offsets[r1];
		dp->offsets[r1] = temp;
	}
}
/*
 *	This routine draws a card from the given deck
 */
get_card(dp)
DECK	*dp; {

	reg char	type_maj, type_min;
	reg int		num;
	int		i, per_h, per_H, num_h, num_H;
	OWN		*op;

	do {
		fseek(deckf, dp->offsets[dp->last_card], 0);
		dp->last_card = ++(dp->last_card) % dp->num_cards;
		type_maj = getc(deckf);
	} while (dp->gojf_used && type_maj == GOJF);
	type_min = getc(deckf);
	num = getw(deckf);
	printmes();
	switch (type_maj) {
	  case '+':		/* get money		*/
		if (type_min == 'A') {
			for (i = 0; i < num_play; i++)
				if (i != player)
					play[i].money -= num;
			num = num * (num_play - 1);
		}
		cur_p->money += num;
		break;
	  case '-':		/* lose money		*/
		if (type_min == 'A') {
			for (i = 0; i < num_play; i++)
				if (i != player)
					play[i].money += num;
			num = num * (num_play - 1);
		}
		cur_p->money -= num;
		break;
	  case 'M':		/* move somewhere	*/
		switch (type_min) {
		  case 'F':		/* move forward	*/
			num -= cur_p->loc;
			if (num < 0)
				num += 40;
			break;
		  case 'J':		/* move to jail	*/
			goto_jail();
			return;
		  case 'R':		/* move to railroad	*/
			spec = TRUE;
			num = (int)((cur_p->loc + 5)/10)*10 + 5 - cur_p->loc;
			break;
		  case 'U':		/* move to utility	*/
			spec = TRUE;
			if (cur_p->loc >= 12 && cur_p->loc < 28)
				num = 28 - cur_p->loc;
			else {
				num = 12 - cur_p->loc;
				if (num < 0)
					num += 40;
			}
			break;
		  case 'B':
			num = -num;
			break;
		}
		move(num);
		break;
	  case 'T':			/* tax			*/
		if (dp == &CC_D) {
			per_h = 40;
			per_H = 115;
		}
		else {
			per_h = 25;
			per_H = 100;
		}
		num_h = num_H = 0;
		for (op = cur_p->own_list; op; op = op->next)
			if (op->sqr->type == PRPTY)
				if (op->sqr->desc->houses == 5)
					++num_H;
				else
					num_h += op->sqr->desc->houses;
		num = per_h * num_h + per_H * num_H;
		printf("You had %d Houses and %d Hotels, so that cost you $%d\n", num_h, num_H, num);
		if (num == 0)
			lucky("");
		else
			cur_p->money -= num;
		break;
	  case GOJF:		/* get-out-of-jail-free card	*/
		cur_p->num_gojf++;
		dp->gojf_used = TRUE;
		break;
	}
	spec = FALSE;
}
/*
 *	This routine prints out the message on the card
 */
printmes() {

	reg char	c;

	printline();
	fflush(stdout);
	while ((c = getc(deckf)) != '\0')
		putchar(c);
	printline();
	fflush(stdout);
}
E 1
