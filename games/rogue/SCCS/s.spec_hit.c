h28709
s 00002/00002/00506
d D 8.1 93/05/31 17:47:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00507
d D 5.3 90/06/01 13:19:29 bostic 3 2
c new copyright notice
e
s 00024/00004/00494
d D 5.2 89/02/07 17:13:23 bostic 2 1
c add Berkeley copyright notice; add Tim's copyright notice to random.c
e
s 00498/00000/00000
d D 5.1 87/11/25 15:25:00 bostic 1 0
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
 * special_hit.c
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

short less_hp = 0;
boolean being_held;

extern short cur_level, max_level, blind, levitate, ring_exp;
extern long level_points[];
extern boolean detect_monster, mon_disappeared;
extern boolean sustain_strength, maintain_armor;
extern char *you_can_move_again;

special_hit(monster)
object *monster;
{
	if ((monster->m_flags & CONFUSED) && rand_percent(66)) {
		return;
	}
	if (monster->m_flags & RUSTS) {
		rust(monster);
	}
	if ((monster->m_flags & HOLDS) && !levitate) {
		being_held = 1;
	}
	if (monster->m_flags & FREEZES) {
		freeze(monster);
	}
	if (monster->m_flags & STINGS) {
		sting(monster);
	}
	if (monster->m_flags & DRAINS_LIFE) {
		drain_life();
	}
	if (monster->m_flags & DROPS_LEVEL) {
		drop_level();
	}
	if (monster->m_flags & STEALS_GOLD) {
		steal_gold(monster);
	} else if (monster->m_flags & STEALS_ITEM) {
		steal_item(monster);
	}
}

rust(monster)
object *monster;
{
	if ((!rogue.armor) || (get_armor_class(rogue.armor) <= 1) ||
		(rogue.armor->which_kind == LEATHER)) {
		return;
	}
	if ((rogue.armor->is_protected) || maintain_armor) {
		if (monster && (!(monster->m_flags & RUST_VANISHED))) {
			message("the rust vanishes instantly", 0);
			monster->m_flags |= RUST_VANISHED;
		}
	} else {
		rogue.armor->d_enchant--;
		message("your armor weakens", 0);
		print_stats(STAT_ARMOR);
	}
}

freeze(monster)
object *monster;
{
	short freeze_percent = 99;
	short i, n;

	if (rand_percent(12)) {
		return;
	}
	freeze_percent -= (rogue.str_current+(rogue.str_current / 2));
	freeze_percent -= ((rogue.exp + ring_exp) * 4);
	freeze_percent -= (get_armor_class(rogue.armor) * 5);
	freeze_percent -= (rogue.hp_max / 3);

	if (freeze_percent > 10) {
		monster->m_flags |= FREEZING_ROGUE;
		message("you are frozen", 1);

		n = get_rand(4, 8);
		for (i = 0; i < n; i++) {
			mv_mons();
		}
		if (rand_percent(freeze_percent)) {
			for (i = 0; i < 50; i++) {
				mv_mons();
			}
			killed_by((object *)0, HYPOTHERMIA);
		}
		message(you_can_move_again, 1);
		monster->m_flags &= (~FREEZING_ROGUE);
	}
}

steal_gold(monster)
object *monster;
{
	int amount;

	if ((rogue.gold <= 0) || rand_percent(10)) {
		return;
	}

	amount = get_rand((cur_level * 10), (cur_level * 30));

	if (amount > rogue.gold) {
		amount = rogue.gold;
	}
	rogue.gold -= amount;
	message("your purse feels lighter", 0);
	print_stats(STAT_GOLD);
	disappear(monster);
}

steal_item(monster)
object *monster;
{
	object *obj;
	short i, n, t;
	char desc[80];
	boolean has_something = 0;

	if (rand_percent(15)) {
		return;
	}
	obj = rogue.pack.next_object;

	if (!obj) {
		goto DSPR;
	}
	while (obj) {
		if (!(obj->in_use_flags & BEING_USED)) {
			has_something = 1;
			break;
		}
		obj = obj->next_object;
	}
	if (!has_something) {
		goto DSPR;
	}
	n = get_rand(0, MAX_PACK_COUNT);
	obj = rogue.pack.next_object;

	for (i = 0; i <= n; i++) {
		obj = obj->next_object;
		while ((!obj) || (obj->in_use_flags & BEING_USED)) {
			if (!obj) {
				obj = rogue.pack.next_object;
			} else {
				obj = obj->next_object;
			}
		}
	}
	(void) strcpy(desc, "she stole ");
	if (obj->what_is != WEAPON) {
		t = obj->quantity;
		obj->quantity = 1;
	}
	get_desc(obj, desc+10);
	message(desc, 0);

	obj->quantity = ((obj->what_is != WEAPON) ? t : 1);

	vanish(obj, 0, &rogue.pack);
DSPR:
	disappear(monster);
}

disappear(monster)
object *monster;
{
	short row, col;

	row = monster->row;
	col = monster->col;

	dungeon[row][col] &= ~MONSTER;
	if (rogue_can_see(row, col)) {
		mvaddch(row, col, get_dungeon_char(row, col));
	}
	take_from_pack(monster, &level_monsters);
	free_object(monster);
	mon_disappeared = 1;
}

cough_up(monster)
object *monster;
{
	object *obj;
	short row, col, i, n;

	if (cur_level < max_level) {
		return;
	}

	if (monster->m_flags & STEALS_GOLD) {
		obj = alloc_object();
		obj->what_is = GOLD;
		obj->quantity = get_rand((cur_level * 15), (cur_level * 30));
	} else {
		if (!rand_percent((int) monster->drop_percent)) {
			return;
		}
		obj = gr_object();
	}
	row = monster->row;
	col = monster->col;

	for (n = 0; n <= 5; n++) {
		for (i = -n; i <= n; i++) {
			if (try_to_cough(row+n, col+i, obj)) {
				return;
			}
			if (try_to_cough(row-n, col+i, obj)) {
				return;
			}
		}
		for (i = -n; i <= n; i++) {
			if (try_to_cough(row+i, col-n, obj)) {
				return;
			}
			if (try_to_cough(row+i, col+n, obj)) {
				return;
			}
		}
	}
	free_object(obj);
}

try_to_cough(row, col, obj)
short row, col;
object *obj;
{
	if ((row < MIN_ROW) || (row > (DROWS-2)) || (col < 0) || (col>(DCOLS-1))) {
		return(0);
	}
	if ((!(dungeon[row][col] & (OBJECT | STAIRS | TRAP))) &&
		(dungeon[row][col] & (TUNNEL | FLOOR | DOOR))) {
		place_at(obj, row, col);
		if (((row != rogue.row) || (col != rogue.col)) &&
			(!(dungeon[row][col] & MONSTER))) {
			mvaddch(row, col, get_dungeon_char(row, col));
		}
		return(1);
	}
	return(0);
}

seek_gold(monster)
object *monster;
{
	short i, j, rn, s;

	if ((rn = get_room_number(monster->row, monster->col)) < 0) {
		return(0);
	}
	for (i = rooms[rn].top_row+1; i < rooms[rn].bottom_row; i++) {
		for (j = rooms[rn].left_col+1; j < rooms[rn].right_col; j++) {
			if ((gold_at(i, j)) && !(dungeon[i][j] & MONSTER)) {
				monster->m_flags |= CAN_FLIT;
				s = mon_can_go(monster, i, j);
				monster->m_flags &= (~CAN_FLIT);
				if (s) {
					move_mon_to(monster, i, j);
					monster->m_flags |= ASLEEP;
					monster->m_flags &= (~(WAKENS | SEEKS_GOLD));
					return(1);
				}
				monster->m_flags &= (~SEEKS_GOLD);
				monster->m_flags |= CAN_FLIT;
				mv_1_monster(monster, i, j);
				monster->m_flags &= (~CAN_FLIT);
				monster->m_flags |= SEEKS_GOLD;
				return(1);
			}
		}
	}
	return(0);
}

gold_at(row, col)
short row, col;
{
	if (dungeon[row][col] & OBJECT) {
		object *obj;

		if ((obj = object_at(&level_objects, row, col)) &&
				(obj->what_is == GOLD)) {
			return(1);
		}
	}
	return(0);
}

check_gold_seeker(monster)
object *monster;
{
	monster->m_flags &= (~SEEKS_GOLD);
}

check_imitator(monster)
object *monster;
{
	char msg[80];

	if (monster->m_flags & IMITATES) {
		wake_up(monster);
		if (!blind) {
			mvaddch(monster->row, monster->col,
					get_dungeon_char(monster->row, monster->col));
			check_message();
			sprintf(msg, "wait, that's a %s!", mon_name(monster));
			message(msg, 1);
		}
		return(1);
	}
	return(0);
}

imitating(row, col)
register short row, col;
{
	if (dungeon[row][col] & MONSTER) {
		object *object_at(), *monster;

		if (monster = object_at(&level_monsters, row, col)) {
			if (monster->m_flags & IMITATES) {
				return(1);
			}
		}
	}
	return(0);
}

sting(monster)
object *monster;
{
	short sting_chance = 35;
	char msg[80];

	if ((rogue.str_current <= 3) || sustain_strength) {
		return;
	}
	sting_chance += (6 * (6 - get_armor_class(rogue.armor)));

	if ((rogue.exp + ring_exp) > 8) {
		sting_chance -= (6 * ((rogue.exp + ring_exp) - 8));
	}
	if (rand_percent(sting_chance)) {
		sprintf(msg, "the %s's bite has weakened you",
		mon_name(monster));
		message(msg, 0);
		rogue.str_current--;
		print_stats(STAT_STRENGTH);
	}
}

drop_level()
{
	int hp;

	if (rand_percent(80) || (rogue.exp <= 5)) {
		return;
	}
	rogue.exp_points = level_points[rogue.exp-2] - get_rand(9, 29);
	rogue.exp -= 2;
	hp = hp_raise();
	if ((rogue.hp_current -= hp) <= 0) {
		rogue.hp_current = 1;
	}
	if ((rogue.hp_max -= hp) <= 0) {
		rogue.hp_max = 1;
	}
	add_exp(1, 0);
}

drain_life()
{
	short n;

	if (rand_percent(60) || (rogue.hp_max <= 30) || (rogue.hp_current < 10)) {
		return;
	}
	n = get_rand(1, 3);		/* 1 Hp, 2 Str, 3 both */

	if ((n != 2) || (!sustain_strength)) {
		message("you feel weaker", 0);
	}
	if (n != 2) {
		rogue.hp_max--;
		rogue.hp_current--;
		less_hp++;
	}
	if (n != 1) {
		if ((rogue.str_current > 3) && (!sustain_strength)) {
			rogue.str_current--;
			if (coin_toss()) {
				rogue.str_max--;
			}
		}
	}
	print_stats((STAT_STRENGTH | STAT_HP));
}

m_confuse(monster)
object *monster;
{
	char msg[80];

	if (!rogue_can_see(monster->row, monster->col)) {
		return(0);
	}
	if (rand_percent(45)) {
		monster->m_flags &= (~CONFUSES);	/* will not confuse the rogue */
		return(0);
	}
	if (rand_percent(55)) {
		monster->m_flags &= (~CONFUSES);
		sprintf(msg, "the gaze of the %s has confused you", mon_name(monster));
		message(msg, 1);
		cnfs();
		return(1);
	}
	return(0);
}

flame_broil(monster)
object *monster;
{
	short row, col, dir;

	if ((!mon_sees(monster, rogue.row, rogue.col)) || coin_toss()) {
		return(0);
	}
	row = rogue.row - monster->row;
	col = rogue.col - monster->col;
	if (row < 0) {
		row = -row;
	}
	if (col < 0) {
		col = -col;
	}
	if (((row != 0) && (col != 0) && (row != col)) ||
		((row > 7) || (col > 7))) {
		return(0);
	}
	dir = get_dir(monster->row, monster->col, row, col);
	bounce(FIRE, dir, monster->row, monster->col, 0);

	return(1);
}

get_dir(srow, scol, drow, dcol)
short srow, scol, drow, dcol;
{
	if (srow == drow) {
		if (scol < dcol) {
			return(RIGHT);
		} else {
			return(LEFT);
		}
	}
	if (scol == dcol) {
		if (srow < drow) {
			return(DOWN);
		} else {
			return(UPWARD);
		}
	}
	if ((srow > drow) && (scol > dcol)) {
		return(UPLEFT);
	}
	if ((srow < drow) && (scol < dcol)) {
		return(DOWNRIGHT);
	}
	if ((srow < drow) && (scol > dcol)) {
		return(DOWNLEFT);
	}
	/*if ((srow > drow) && (scol < dcol)) {*/
		return(UPRIGHT);
	/*}*/
}
E 1
