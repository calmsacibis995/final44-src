h61633
s 00002/00002/00255
d D 8.1 93/05/31 17:47:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00256
d D 5.3 90/06/01 13:19:49 bostic 3 2
c new copyright notice
e
s 00024/00004/00243
d D 5.2 89/02/07 17:13:27 bostic 2 1
c add Berkeley copyright notice; add Tim's copyright notice to random.c
e
s 00247/00000/00000
d D 5.1 87/11/25 15:25:02 bostic 1 0
c from Tim Stoehr
e
u
U
t
T
I 1
/*
I 2
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
 * Timothy C. Stoehr.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 2
 * trap.c
 *
 * This source herein may be modified and/or distributed by anybody who
 * so desires, with the following restrictions:
 *    1.)  No portion of this notice shall be removed.
 *    2.)  Credit shall not be taken for the creation of this source.
 *    3.)  This code is not to be traded, sold, or used for personal
 *         gain or profit.
 *
 */
D 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "rogue.h"

trap traps[MAX_TRAPS];
boolean trap_door = 0;
short bear_trap = 0;

char *trap_strings[TRAPS * 2] = {
	"trap door",
			"you fell down a trap",
	"bear trap",
			"you are caught in a bear trap",
	"teleport trap",
			"teleport",
	"poison dart trap",
			"a small dart just hit you in the shoulder",
	"sleeping gas trap",
			"a strange white mist envelops you and you fall asleep",
	"rust trap",
			"a gush of water hits you on the head"
};

extern short cur_level, party_room;
extern char *new_level_message;
extern boolean interrupted;
extern short ring_exp;
extern boolean sustain_strength;
extern short blind;

trap_at(row, col)
register row, col;
{
	short i;

	for (i = 0; ((i < MAX_TRAPS) && (traps[i].trap_type != NO_TRAP)); i++) {
		if ((traps[i].trap_row == row) && (traps[i].trap_col == col)) {
			return(traps[i].trap_type);
		}
	}
	return(NO_TRAP);
}

trap_player(row, col)
short row, col;
{
	short t;

	if ((t = trap_at(row, col)) == NO_TRAP) {
		return;
	}
	dungeon[row][col] &= (~HIDDEN);
	if (rand_percent(rogue.exp + ring_exp)) {
		message("the trap failed", 1);
		return;
	}
	switch(t) {
	case TRAP_DOOR:
		trap_door = 1;
		new_level_message = trap_strings[(t*2)+1];
		break;
	case BEAR_TRAP:
		message(trap_strings[(t*2)+1], 1);
		bear_trap = get_rand(4, 7);
		break;
	case TELE_TRAP:
		mvaddch(rogue.row, rogue.col, '^');
		tele();
		break;
	case DART_TRAP:
		message(trap_strings[(t*2)+1], 1);
		rogue.hp_current -= get_damage("1d6", 1);
		if (rogue.hp_current <= 0) {
			rogue.hp_current = 0;
		}
		if ((!sustain_strength) && rand_percent(40) &&
			(rogue.str_current >= 3)) {
			rogue.str_current--;
		}
		print_stats(STAT_HP | STAT_STRENGTH);
		if (rogue.hp_current <= 0) {
			killed_by((object *) 0, POISON_DART);
		}
		break;
	case SLEEPING_GAS_TRAP:
		message(trap_strings[(t*2)+1], 1);
		take_a_nap();
		break;
	case RUST_TRAP:
		message(trap_strings[(t*2)+1], 1);
		rust((object *) 0);
		break;
	}
}

add_traps()
{
	short i, n, tries = 0;
	short row, col;

	if (cur_level <= 2) {
		n = 0;
	} else if (cur_level <= 7) {
		n = get_rand(0, 2);
	} else if (cur_level <= 11) {
		n = get_rand(1, 2);
	} else if (cur_level <= 16) {
		n = get_rand(2, 3);
	} else if (cur_level <= 21) {
		n = get_rand(2, 4);
	} else if (cur_level <= (AMULET_LEVEL + 2)) {
		n = get_rand(3, 5);
	} else {
		n = get_rand(5, MAX_TRAPS);
	}
	for (i = 0; i < n; i++) {
		traps[i].trap_type = get_rand(0, (TRAPS - 1));

		if ((i == 0) && (party_room != NO_ROOM)) {
			do {
				row = get_rand((rooms[party_room].top_row+1),
						(rooms[party_room].bottom_row-1));
				col = get_rand((rooms[party_room].left_col+1),
						(rooms[party_room].right_col-1));
				tries++;
			} while (((dungeon[row][col] & (OBJECT|STAIRS|TRAP|TUNNEL)) ||
					(dungeon[row][col] == NOTHING)) && (tries < 15));
			if (tries >= 15) {
				gr_row_col(&row, &col, (FLOOR | MONSTER));
			}
		} else {
			gr_row_col(&row, &col, (FLOOR | MONSTER));
		}
		traps[i].trap_row = row;
		traps[i].trap_col = col;
		dungeon[row][col] |= (TRAP | HIDDEN);
	}
}

id_trap()
{
	short dir, row, col, d, t;

	message("direction? ", 0);

	while (!is_direction(dir = rgetchar(), &d)) {
		sound_bell();
	}
	check_message();

	if (dir == CANCEL) {
		return;
	}
	row = rogue.row;
	col = rogue.col;

	get_dir_rc(d, &row, &col, 0);

	if ((dungeon[row][col] & TRAP) && (!(dungeon[row][col] & HIDDEN))) {
		t = trap_at(row, col);
		message(trap_strings[t*2], 0);
	} else {
		message("no trap there", 0);
	}
}

show_traps()
{
	short i, j;

	for (i = 0; i < DROWS; i++) {
		for (j = 0; j < DCOLS; j++) {
			if (dungeon[i][j] & TRAP) {
				mvaddch(i, j, '^');
			}
		}
	}
}

search(n, is_auto)
short n;
boolean is_auto;
{
	short s, i, j, row, col, t;
	short shown = 0, found = 0;
	static boolean reg_search;

	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			row = rogue.row + i;
			col = rogue.col + j;
			if ((row < MIN_ROW) || (row >= (DROWS-1)) ||
					(col < 0) || (col >= DCOLS)) {
				continue;
			}
			if (dungeon[row][col] & HIDDEN) {
				found++;
			}
		}
	}
	for (s = 0; s < n; s++) {
		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				row = rogue.row + i;
				col = rogue.col + j ;
				if ((row < MIN_ROW) || (row >= (DROWS-1)) ||
						(col < 0) || (col >= DCOLS)) {
					continue;
				}
				if (dungeon[row][col] & HIDDEN) {
					if (rand_percent(17 + (rogue.exp + ring_exp))) {
						dungeon[row][col] &= (~HIDDEN);
						if ((!blind) && ((row != rogue.row) ||
								(col != rogue.col))) {
							mvaddch(row, col, get_dungeon_char(row, col));
						}
						shown++;
						if (dungeon[row][col] & TRAP) {
							t = trap_at(row, col);
							message(trap_strings[t*2], 1);
						}
					}
				}
				if (((shown == found) && (found > 0)) || interrupted) {
					return;
				}
			}
		}
		if ((!is_auto) && (reg_search = !reg_search)) {
			(void) reg_move();
		}
	}
}
E 1
