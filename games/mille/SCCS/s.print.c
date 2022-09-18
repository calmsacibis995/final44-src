h44885
s 00002/00002/00141
d D 8.1 93/05/31 17:25:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00142
d D 5.4 90/06/01 13:08:22 bostic 4 3
c new copyright notice
e
s 00010/00006/00143
d D 5.3 88/06/18 19:38:30 bostic 3 2
c install approved copyright notice
e
s 00010/00003/00139
d D 5.2 87/12/29 17:14:52 bostic 2 1
c Berkeley header
e
s 00142/00000/00000
d D 5.1 86/11/26 13:35:57 bostic 1 0
c date and time created 86/11/26 13:35:57 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
D 3

E 3
E 2

# include	"mille.h"

/*
 * @(#)print.c	1.1 (Berkeley) 4/1/82
 */

# define	COMP_STRT	20
# define	CARD_STRT	2

prboard() {

	reg PLAY	*pp;
	reg int		i, j, k, temp;

	for (k = 0; k < 2; k++) {
		pp = &Player[k];
		temp = k * COMP_STRT + CARD_STRT;
		for (i = 0; i < NUM_SAFE; i++)
			if (pp->safety[i] == S_PLAYED && !pp->sh_safety[i]) {
				mvaddstr(i, temp, C_name[i + S_CONV]);
				if (pp->coups[i])
					mvaddch(i, temp - CARD_STRT, '*');
				pp->sh_safety[i] = TRUE;
			}
		show_card(14, temp, pp->battle, &pp->sh_battle);
		show_card(16, temp, pp->speed, &pp->sh_speed);
		for (i = C_25; i <= C_200; i++) {
			reg char	*name;
			reg int		end;

			if (pp->nummiles[i] == pp->sh_nummiles[i])
				continue;

			name = C_name[i];
			temp = k * 40;
			end = pp->nummiles[i];
			for (j = pp->sh_nummiles[i]; j < end; j++)
				mvwaddstr(Miles, i + 1, (j << 2) + temp, name);
			pp->sh_nummiles[i] = end;
		}
	}
	prscore(TRUE);
	temp = CARD_STRT;
	pp = &Player[PLAYER];
	for (i = 0; i < HAND_SZ; i++)
		show_card(i + 6, temp, pp->hand[i], &pp->sh_hand[i]);
	mvprintw(6, COMP_STRT + CARD_STRT, "%2d", Topcard - Deck);
	show_card(8, COMP_STRT + CARD_STRT, Discard, &Sh_discard);
	if (End == 1000) {
		move(EXT_Y, EXT_X);
		standout();
		addstr("Extension");
		standend();
	}
	wrefresh(Board);
	wrefresh(Miles);
	wrefresh(Score);
}

/*
 * show_card:
 *	Show the given card if it is different from the last one shown
 */
show_card(y, x, c, lc)
int		y, x;
register CARD	c, *lc;
{
	if (c == *lc)
		return;

	mvprintw(y, x, C_fmt, C_name[c]);
	*lc = c;
}

static char	Score_fmt[] = "%4d";

prscore(for_real)
reg bool	for_real; {

	reg PLAY	*pp;
	reg int		x;

	stdscr = Score;
	for (pp = Player; pp < &Player[2]; pp++) {
		x = (pp - Player) * 6 + 21;
		show_score(1, x, pp->mileage, &pp->sh_mileage);
		if (pp->safescore != pp->sh_safescore) {
			mvprintw(2, x, Score_fmt, pp->safescore);
			if (pp->safescore == 400)
				mvaddstr(3, x + 1, "300");
			else
				mvaddstr(3, x + 1, "  0");
			mvprintw(4, x, Score_fmt, pp->coupscore);
			pp->sh_safescore = pp->safescore;
		}
		if (Window == W_FULL || Finished) {
#ifdef EXTRAP
			if (for_real)
				finalscore(pp);
			else
				extrapolate(pp);
#else
			finalscore(pp);
#endif
			show_score(11, x, pp->hand_tot, &pp->sh_hand_tot);
			show_score(13, x, pp->total, &pp->sh_total);
			show_score(14, x, pp->games, &pp->sh_games);
		}
		else {
			show_score(6, x, pp->hand_tot, &pp->sh_hand_tot);
			show_score(8, x, pp->total, &pp->sh_total);
			show_score(9, x, pp->games, &pp->sh_games);
		}
	}
	stdscr = Board;
}

/*
 * show_score:
 *	Show a score value if it is different from the last time we
 *	showed it.
 */
show_score(y, x, s, ls)
int		y, x;
register int	s, *ls;
{
	if (s == *ls)
		return;

	mvprintw(y, x, Score_fmt, s);
	*ls = s;
}
E 1
