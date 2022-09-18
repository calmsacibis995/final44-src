h59389
s 00002/00002/00278
d D 8.1 93/05/31 17:27:22 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00279
d D 5.5 90/06/01 13:13:00 bostic 5 4
c new copyright notice
e
s 00001/00001/00289
d D 5.4 90/02/21 10:17:05 bostic 4 3
c gcc fix; keyword "static" unnecessary
e
s 00011/00006/00279
d D 5.3 88/06/18 14:55:15 bostic 3 2
c install approved copyright notice
e
s 00002/00004/00283
d D 5.2 88/01/02 20:59:22 bostic 2 1
c John Gilmore's changes for ANSI C and general cleanup
e
s 00287/00000/00000
d D 5.1 88/01/02 20:53:32 bostic 1 0
c date and time created 88/01/02 20:53:32 by bostic
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
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"monop.ext"

D 4
static struct	trd_st {	/* how much to give to other player	*/
E 4
I 4
struct trd_st {			/* how much to give to other player	*/
E 4
	int	trader;			/* trader number		*/
	int	cash;			/* amount of cash 		*/
	int	gojf;			/* # get-out-of-jail-free cards	*/
	OWN	*prop_list;		/* property list		*/
};

typedef	struct trd_st	TRADE;

static char	*list[MAX_PRP+2];

static int	used[MAX_PRP];

static TRADE	trades[2];

trade() {

	reg int	tradee, i;

	trading = TRUE;
	for (i = 0; i < 2; i++) {
		trades[i].cash = 0;
		trades[i].gojf = FALSE;
		trades[i].prop_list = NULL;
	}
over:
	if (num_play == 1) {
		printf("There ain't no-one around to trade WITH!!\n");
		return;
	}
	if (num_play > 2) {
		tradee = getinp("Which player do you wish to trade with? ",
		    name_list);
		if (tradee == num_play)
			return;
		if (tradee == player) {
			printf("You can't trade with yourself!\n");
			goto over;
		}
	}
	else
		tradee = 1 - player;
	get_list(0, player);
	get_list(1, tradee);
	if (getyn("Do you wish a summary? ") == 0)
		summate();
	if (getyn("Is the trade ok? ") == 0)
		do_trade();
}
/*
 *	This routine gets the list of things to be trader for the
 * player, and puts in the structure given.
 */
get_list(struct_no, play_no)
int	struct_no, play_no; {

	reg int		sn, pn;
	reg PLAY	*pp;
	int		numin, prop, num_prp;
	OWN		*op;
	TRADE		*tp;

	for (numin = 0; numin < MAX_PRP; numin++)
		used[numin] = FALSE;
	sn = struct_no, pn = play_no;
	pp = &play[pn];
	tp = &trades[sn];
	tp->trader = pn;
	printf("player %s (%d):\n", pp->name, pn+1);
	if (pp->own_list) {
		numin = set_list(pp->own_list);
		for (num_prp = numin; num_prp; ) {
			prop = getinp("Which property do you wish to trade? ",
			    list);
			if (prop == numin)
				break;
			else if (used[prop])
				printf("You've already allocated that.\n");
			else {
				num_prp--;
				used[prop] = TRUE;
				for (op = pp->own_list; prop--; op = op->next)
					continue;
				add_list(pn, &(tp->prop_list), sqnum(op->sqr));
			}
		}
	}
	if (pp->money > 0) {
		printf("You have $%d.  ", pp->money);
		tp->cash = get_int("How much are you trading? ");
	}
	if (pp->num_gojf > 0) {
once_more:
		printf("You have %d get-out-of-jail-free cards. ",pp->num_gojf);
		tp->gojf = get_int("How many are you trading? ");
		if (tp->gojf > pp->num_gojf) {
			printf("You don't have that many.  Try again.\n");
			goto once_more;
		}
	}
}
/*
 *	This routine sets up the list of tradable property.
 */
set_list(the_list)
reg OWN	*the_list; {

	reg int	i;
	reg OWN	*op;

	i = 0;
	for (op = the_list; op; op = op->next)
		if (!used[i])
			list[i++] = op->sqr->name;
	list[i++] = "done";
	list[i--] = 0;
	return i;
}
/*
 *	This routine summates the trade.
 */
summate() {

	reg bool	some;
	reg int		i;
	reg TRADE	*tp;
	OWN	*op;

	for (i = 0; i < 2; i++) {
		tp = &trades[i];
		some = FALSE;
		printf("Player %s (%d) gives:\n", play[tp->trader].name,
			tp->trader+1);
		if (tp->cash > 0)
			printf("\t$%d\n", tp->cash), some++;
		if (tp->gojf > 0)
			printf("\t%d get-out-of-jail-free card(s)\n", tp->gojf),
			some++;
		if (tp->prop_list) {
			for (op = tp->prop_list; op; op = op->next)
				putchar('\t'), printsq(sqnum(op->sqr), TRUE);
			some++;
		}
		if (!some)
			printf("\t-- Nothing --\n");
	}
}
/*
 *	This routine actually executes the trade.
 */
do_trade() {

	move_em(&trades[0], &trades[1]);
	move_em(&trades[1], &trades[0]);
}
/*
 *	This routine does a switch from one player to another
 */
move_em(from, to)
TRADE	*from, *to; {

	reg PLAY	*pl_fr, *pl_to;
	reg OWN		*op;

	pl_fr = &play[from->trader];
	pl_to = &play[to->trader];

	pl_fr->money -= from->cash;
	pl_to->money += from->cash;
	pl_fr->num_gojf -= from->gojf;
	pl_to->num_gojf += from->gojf;
	for (op = from->prop_list; op; op = op->next) {
		add_list(to->trader, &(pl_to->own_list), sqnum(op->sqr));
		op->sqr->owner = to->trader;
		del_list(from->trader, &(pl_fr->own_list), sqnum(op->sqr));
	}
	set_ownlist(to->trader);
}
/*
 *	This routine lets a player resign
 */
resign() {

	reg int	i, new_own;
	reg OWN	*op;
	SQUARE	*sqp;

	if (cur_p->money <= 0) {
		switch (board[cur_p->loc].type) {
		  case UTIL:
		  case RR:
		  case PRPTY:
			new_own = board[cur_p->loc].owner;
			break;
D 2
		  case SPEC:
		  case CC:
		  case CHANCE:
E 2
I 2
		  default:		/* Chance, taxes, etc */
E 2
			new_own = num_play;
			break;
		}
		if (new_own == num_play)
			printf("You would resign to the bank\n");
		else
			printf("You would resign to %s\n", name_list[new_own]);
	}
	else if (num_play == 1) {
		new_own = num_play;
		printf("You would resign to the bank\n");
	}
	else {
		name_list[num_play] = "bank";
		do {
			new_own = getinp("Who do you wish to resign to? ",
			    name_list);
			if (new_own == player)
				printf("You can't resign to yourself!!\n");
		} while (new_own == player);
		name_list[num_play] = "done";
	}
	if (getyn("Do you really want to resign? ", yn) != 0)
		return;
	if (num_play == 1) {
		printf("Then NOBODY wins (not even YOU!)\n");
		exit(0);
	}
	if (new_own < num_play) {	/* resign to player		*/
		printf("resigning to player\n");
		trades[0].trader = new_own;
		trades[0].cash = trades[0].gojf = 0;
		trades[0].prop_list = NULL;
		trades[1].trader = player;
		trades[1].cash = cur_p->money > 0 ? cur_p->money : 0;
		trades[1].gojf = cur_p->num_gojf;
		trades[1].prop_list = cur_p->own_list;
		do_trade();
	}
	else {				/* resign to bank		*/
		printf("resigning to bank\n");
		for (op = cur_p->own_list; op; op = op->next) {
			sqp = op->sqr;
			sqp->owner = -1;
			sqp->desc->morg = FALSE;
D 2
			if (op->type == PRPTY) {
E 2
I 2
			if (sqp->type == PRPTY) {
E 2
				isnot_monop(sqp->desc->mon_desc);
				sqp->desc->houses = 0;
			}
		}
		if (cur_p->num_gojf)
			ret_card(cur_p);
	}
	for (i = player; i < num_play; i++) {
		name_list[i] = name_list[i+1];
		if (i + 1 < num_play)
			cpy_st(&play[i], &play[i+1], sizeof (PLAY));
	}
	name_list[num_play--] = 0;
	for (i = 0; i < N_SQRS; i++)
		if (board[i].owner > player)
			--board[i].owner;
	player = --player < 0 ? num_play - 1 : player;
	next_play();
	if (num_play < 2) {
		printf("\nThen %s WINS!!!!!\n", play[0].name);
		printhold(0);
		printf("That's a grand worth of $%d.\n",
			play[0].money+prop_worth(&play[0]));
		exit(0);
	}
}
E 1
