h38980
s 00002/00002/00241
d D 8.1 93/05/31 17:26:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00242
d D 5.5 90/06/01 13:11:25 bostic 5 4
c new copyright notice
e
s 00011/00006/00242
d D 5.4 88/06/18 14:54:38 bostic 4 3
c install approved copyright notice
e
s 00013/00001/00235
d D 5.3 88/01/02 20:51:25 bostic 3 2
c add Berkeley header
e
s 00005/00003/00231
d D 5.2 87/10/22 11:37:23 bostic 2 1
c ANSI C; sprintf now returns an int.
e
s 00234/00000/00000
d D 5.1 87/10/22 11:35:09 bostic 1 0
c date and time created 87/10/22 11:35:09 by bostic
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1987 Regents of the University of California.
E 4
I 4
D 6
 * Copyright (c) 1980 Regents of the University of California.
E 4
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

# include	"monop.ext"

static char	*names[N_MON+2],
		cur_prop[80];

static MON	*monops[N_MON];

/*
 *	These routines deal with buying and selling houses
 */
buy_houses() {

	reg int num_mon;
	reg MON	*mp;
	reg OWN	*op;
	bool	good,got_morg;
	int	i,p;

over:
	num_mon = 0;
	good = TRUE;
	got_morg = FALSE;
	for (op = cur_p->own_list; op && op->sqr->type != PRPTY; op = op->next)
		continue;
	while (op)
		if (op->sqr->desc->monop) {
			mp = op->sqr->desc->mon_desc;
			names[num_mon] = (monops[num_mon]=mp)->name;
			num_mon++;
			got_morg = good = FALSE;
			for (i = 0; i < mp->num_in; i++) {
				if (op->sqr->desc->morg)
					got_morg++;
				if (op->sqr->desc->houses != 5)
					good++;
				op = op->next;
			}
			if (!good || got_morg)
				--num_mon;
		}
		else
			op = op->next;
	if (num_mon == 0) {
		if (got_morg)
			printf("You can't build on mortgaged monopolies.\n");
		else if (!good)
			printf("You can't build any more.\n");
		else
			printf("But you don't have any monopolies!!\n");
		return;
	}
	if (num_mon == 1)
		buy_h(monops[0]);
	else {
		names[num_mon++] = "done";
		names[num_mon--] = 0;
		if ((p=getinp("Which property do you wish to buy houses for? ", names)) == num_mon)
			return;
		buy_h(monops[p]);
		goto over;
	}
}

buy_h(mnp)
MON	*mnp; {

	reg int	i;
	reg MON	*mp;
	reg int	price;
	shrt	input[3],temp[3];
	int	tot;
	PROP	*pp;

	mp = mnp;
	price = mp->h_cost * 50;
blew_it:
	list_cur(mp);
	printf("Houses will cost $%d\n", price);
	printf("How many houses do you wish to buy for\n");
	for (i = 0; i < mp->num_in; i++) {
		pp = mp->sq[i]->desc;
over:
		if (pp->houses == 5) {
			printf("%s (H):\n", mp->sq[i]->name);
			input[i] = 0;
			temp[i] = 5;
			continue;
		}
D 2
		sprintf(cur_prop, "%s (%d): ", mp->sq[i]->name, pp->houses);
E 2
I 2
		(void)sprintf(cur_prop, "%s (%d): ",
			mp->sq[i]->name, pp->houses);
E 2
		input[i] = get_int(cur_prop);
		temp[i] = input[i] + pp->houses;
		if (temp[i] > 5) {
			printf("That's too many.  The most you can buy is %d\n",
				5 - pp->houses);
				goto over;
			}
	}
	if (mp->num_in == 3 && (abs(temp[0] - temp[1]) > 1 ||
	    abs(temp[0] - temp[2]) > 1 || abs(temp[1] - temp[2]) > 1)) {
err:		printf("That makes the spread too wide.  Try again\n");
		goto blew_it;
	}
	else if (mp->num_in == 2 && abs(temp[0] - temp[1]) > 1)
		goto err;
	for (tot = i = 0; i < mp->num_in; i++)
		tot += input[i];
	if (tot) {
		printf("You asked for %d houses for $%d\n", tot, tot * price);
		if (getyn("Is that ok? ", yn) == 0) {
			cur_p->money -= tot * price;
			for (tot = i = 0; i < mp->num_in; i++)
				mp->sq[i]->desc->houses = temp[i];
		}
	}
}

/*
 *	This routine sells houses.
 */
sell_houses() {

	reg int	num_mon;
	reg MON	*mp;
	reg OWN	*op;
	bool	good;
	int	p;

over:
	num_mon = 0;
	good = TRUE;
	for (op = cur_p->own_list; op; op = op->next)
		if (op->sqr->type == PRPTY && op->sqr->desc->monop) {
			mp = op->sqr->desc->mon_desc;
			names[num_mon] = (monops[num_mon]=mp)->name;
			num_mon++;
			good = 0;
			do
				if (!good && op->sqr->desc->houses != 0)
					good++;
			while (op->next && op->sqr->desc->mon_desc == mp
			    && (op=op->next));
			if (!good)
				--num_mon;
		}
	if (num_mon == 0) {
		printf("You don't have any houses to sell!!\n");
		return;
	}
	if (num_mon == 1)
		sell_h(monops[0]);
	else {
		names[num_mon++] = "done";
		names[num_mon--] = 0;
		if ((p=getinp("Which property do you wish to sell houses from? ", names)) == num_mon)
			return;
		sell_h(monops[p]);
		notify();
		goto over;
	}
}

sell_h(mnp)
MON	*mnp; {

	reg int	i;
	reg MON	*mp;
	reg int	price;
	shrt	input[3],temp[3];
	int	tot;
	PROP	*pp;

	mp = mnp;
	price = mp->h_cost * 25;
blew_it:
	printf("Houses will get you $%d apiece\n", price);
	list_cur(mp);
	printf("How many houses do you wish to sell from\n");
	for (i = 0; i < mp->num_in; i++) {
		pp = mp->sq[i]->desc;
over:
		if (pp->houses == 0) {
			printf("%s (0):\n", mp->sq[i]->name);
			input[i] = temp[i] = 0;
			continue;
		}
		if (pp->houses < 5)
D 2
			sprintf(cur_prop,"%s (%d): ",mp->sq[i]->name,pp->houses);
E 2
I 2
			(void)sprintf(cur_prop,"%s (%d): ",
				mp->sq[i]->name,pp->houses);
E 2
		else
D 2
			sprintf(cur_prop,"%s (H): ",mp->sq[i]->name);
E 2
I 2
			(void)sprintf(cur_prop,"%s (H): ",mp->sq[i]->name);
E 2
		input[i] = get_int(cur_prop);
		temp[i] = pp->houses - input[i];
		if (temp[i] < 0) {
			printf("That's too many.  The most you can sell is %d\n", pp->houses);
				goto over;
			}
	}
	if (mp->num_in == 3 && (abs(temp[0] - temp[1]) > 1 ||
	    abs(temp[0] - temp[2]) > 1 || abs(temp[1] - temp[2]) > 1)) {
err:		printf("That makes the spread too wide.  Try again\n");
		goto blew_it;
	}
	else if (mp->num_in == 2 && abs(temp[0] - temp[1]) > 1)
		goto err;
	for (tot = i = 0; i < mp->num_in; i++)
		tot += input[i];
	if (tot) {
		printf("You asked to sell %d houses for $%d\n",tot,tot * price);
		if (getyn("Is that ok? ", yn) == 0) {
			cur_p->money += tot * price;
			for (tot = i = 0; i < mp->num_in; i++)
				mp->sq[i]->desc->houses = temp[i];
		}
	}
}

list_cur(mp)
reg MON	*mp; {

	reg int		i;
	reg SQUARE	*sqp;

	for (i = 0; i < mp->num_in; i++) {
		sqp = mp->sq[i];
		if (sqp->desc->houses == 5)
			printf("%s (H) ", sqp->name);
		else
			printf("%s (%d) ", sqp->name, sqp->desc->houses);
	}
	putchar('\n');
}
E 1
