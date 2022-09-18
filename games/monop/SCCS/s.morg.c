h53374
s 00002/00002/00181
d D 8.1 93/05/31 17:26:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00011/00173
d D 5.4 93/03/25 05:38:37 bostic 4 3
c remove shell escape, since would be setuid games
e
s 00001/00011/00183
d D 5.3 90/06/01 13:12:11 bostic 3 2
c new copyright notice
e
s 00011/00006/00183
d D 5.2 88/06/18 14:55:00 bostic 2 1
c install approved copyright notice
e
s 00189/00000/00000
d D 5.1 88/01/02 20:53:29 bostic 1 0
c date and time created 88/01/02 20:53:29 by bostic
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
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"monop.ext"

/*
 *	These routines deal with mortgaging.
 */

static char	*names[MAX_PRP+2],
		*morg_coms[]	= {
			"quit",		/*  0 */
			"print",	/*  1 */
			"where",	/*  2 */
			"own holdings",	/*  3 */
			"holdings",	/*  4 */
D 4
			"shell",	/*  5 */
			"mortgage",	/*  6 */
			"unmortgage",	/*  7 */
			"buy",		/*  8 */
			"sell",		/*  9 */
			"card",		/* 10 */
			"pay",		/* 11 */
			"trade",	/* 12 */
			"resign",	/* 13 */
			"save game",	/* 14 */
			"restore game",	/* 15 */
E 4
I 4
			"mortgage",	/*  5 */
			"unmortgage",	/*  6 */
			"buy",		/*  7 */
			"sell",		/*  8 */
			"card",		/*  9 */
			"pay",		/* 10 */
			"trade",	/* 11 */
			"resign",	/* 12 */
			"save game",	/* 13 */
			"restore game",	/* 14 */
E 4
			0
		};

static shrt	square[MAX_PRP+2];

static int	num_good,got_houses;

/*
 *	This routine is the command level response the mortgage command.
 * it gets the list of mortgageable property and asks which are to
 * be mortgaged.
 */
mortgage() {

	reg int	prop;

	for (;;) {
		if (set_mlist() == 0) {
			if (got_houses)
				printf("You can't mortgage property with houses on it.\n");
			else
				printf("You don't have any un-mortgaged property.\n");
			return;
		}
		if (num_good == 1) {
			printf("Your only mortageable property is %s\n",names[0]);
			if (getyn("Do you want to mortgage it? ") == 0)
				m(square[0]);
			return;
		}
		prop = getinp("Which property do you want to mortgage? ",names);
		if (prop == num_good)
			return;
		m(square[prop]);
		notify(cur_p);
	}
}
/*
 *	This routine sets up the list of mortgageable property
 */
set_mlist() {

	reg OWN	*op;

	num_good = 0;
	for (op = cur_p->own_list; op; op = op->next)
		if (!op->sqr->desc->morg)
			if (op->sqr->type == PRPTY && op->sqr->desc->houses)
				got_houses++;
			else {
				names[num_good] = op->sqr->name;
				square[num_good++] = sqnum(op->sqr);
			}
	names[num_good++] = "done";
	names[num_good--] = 0;
	return num_good;
}
/*
 *	This routine actually mortgages the property.
 */
m(prop)
reg int	prop; {

	reg int	price;

	price = board[prop].cost/2;
	board[prop].desc->morg = TRUE;
	printf("That got you $%d\n",price);
	cur_p->money += price;
}
/*
 *	This routine is the command level repsponse to the unmortgage
 * command.  It gets the list of mortgaged property and asks which are
 * to be unmortgaged.
 */
unmortgage() {

	reg int	prop;

	for (;;) {
		if (set_umlist() == 0) {
			printf("You don't have any mortgaged property.\n");
			return;
		}
		if (num_good == 1) {
			printf("Your only mortaged property is %s\n",names[0]);
			if (getyn("Do you want to unmortgage it? ") == 0)
				unm(square[0]);
			return;
		}
		prop = getinp("Which property do you want to unmortgage? ",names);
		if (prop == num_good)
			return;
		unm(square[prop]);
	}
}
/*
 *	This routine sets up the list of mortgaged property
 */
set_umlist() {

	reg OWN	*op;

	num_good = 0;
	for (op = cur_p->own_list; op; op = op->next)
		if (op->sqr->desc->morg) {
			names[num_good] = op->sqr->name;
			square[num_good++] = sqnum(op->sqr);
		}
	names[num_good++] = "done";
	names[num_good--] = 0;
	return num_good;
}
/*
 *	This routine actually unmortgages the property
 */
unm(prop)
reg int	prop; {

	reg int	price;

	price = board[prop].cost/2;
	board[prop].desc->morg = FALSE;
	price += price/10;
	printf("That cost you $%d\n",price);
	cur_p->money -= price;
	set_umlist();
}
/*
 *	This routine forces the indebted player to fix his
 * financial woes.
 */
force_morg() {

	told_em = fixing = TRUE;
	while (cur_p->money <= 0)
		fix_ex(getinp("How are you going to fix it up? ",morg_coms));
	fixing = FALSE;
}
/*
 *	This routine is a special execute for the force_morg routine
 */
fix_ex(com_num)
reg int	com_num; {

	told_em = FALSE;
	(*func[com_num])();
	notify();
}
E 1
