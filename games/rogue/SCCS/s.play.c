h09240
s 00002/00002/00270
d D 8.1 93/05/31 17:47:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00271
d D 5.3 90/06/01 13:18:07 bostic 3 2
c new copyright notice
e
s 00024/00004/00258
d D 5.2 89/02/07 17:13:06 bostic 2 1
c add Berkeley copyright notice; add Tim's copyright notice to random.c
e
s 00262/00000/00000
d D 5.1 87/11/25 15:24:52 bostic 1 0
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
 * play.c
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

boolean interrupted = 0;
char *unknown_command = "unknown command";

extern short party_room, bear_trap;
extern char hit_message[];
extern boolean wizard, trap_door;

play_level()
{
	short ch;
	int count;

	for (;;) {
		interrupted = 0;
		if (hit_message[0]) {
			message(hit_message, 1);
			hit_message[0] = 0;
		}
		if (trap_door) {
			trap_door = 0;
			return;
		}
		move(rogue.row, rogue.col);
		refresh();

		ch = rgetchar();
CMCH:
		check_message();
		count = 0;
CH:
		switch(ch) {
		case '.':
			rest((count > 0) ? count : 1);
			break;
		case 's':
			search(((count > 0) ? count : 1), 0);
			break;
		case 'i':
			inventory(&rogue.pack, ALL_OBJECTS);
			break;
		case 'f':
			fight(0);
			break;
		case 'F':
			fight(1);
			break;
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		case 'y':
		case 'u':
		case 'n':
		case 'b':
			(void) one_move_rogue(ch, 1);
			break;
		case 'H':
		case 'J':
		case 'K':
		case 'L':
		case 'B':
		case 'Y':
		case 'U':
		case 'N':
		case '\010':
		case '\012':
		case '\013':
		case '\014':
		case '\031':
		case '\025':
		case '\016':
		case '\002':
			multiple_move_rogue(ch);
			break;
		case 'e':
			eat();
			break;
		case 'q':
			quaff();
			break;
		case 'r':
			read_scroll();
			break;
		case 'm':
			move_onto();
			break;
		case ',':
			kick_into_pack();
			break;
		case 'd':
			drop();
			break;
		case 'P':
			put_on_ring();
			break;
		case 'R':
			remove_ring();
			break;
		case '\020':
			do {
				remessage(count++);
				ch = rgetchar();
			} while (ch == '\020');
			goto CMCH;
			break;
		case '\027':
			wizardize();
			break;
		case '>':
			if (drop_check()) {
				return;
			}
			break;
		case '<':
			if (check_up()) {
				return;
			}
			break;
		case ')':
		case ']':
			inv_armor_weapon(ch == ')');
			break;
		case '=':
			inv_rings();
			break;
		case '^':
			id_trap();
			break;
		case '/':
			id_type();
			break;
		case '?':
			id_com();
			break;
		case '!':
			do_shell();
			break;
		case 'o':
			edit_opts();
			break;
		case 'I':
			single_inv(0);
			break;
		case 'T':
			take_off();
			break;
		case 'W':
			wear();
			break;
		case 'w':
			wield();
			break;
		case 'c':
			call_it();
			break;
		case 'z':
			zapp();
			break;
		case 't':
			throw();
			break;
		case 'v':
			message("rogue-clone: Version III. (Tim Stoehr was here), tektronix!zeus!tims", 0);
			break;
		case 'Q':
			quit(0);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			move(rogue.row, rogue.col);
			refresh();
			do {
				if (count < 100) {
					count = (10 * count) + (ch - '0');
				}
				ch = rgetchar();
			} while (is_digit(ch));
			if (ch != CANCEL) {
				goto CH;
			}
			break;
		case ' ':
			break;
		case '\011':
			if (wizard) {
				inventory(&level_objects, ALL_OBJECTS);
			} else {
				message(unknown_command, 0);
			}
			break;
		case '\023':
			if (wizard) {
				draw_magic_map();
			} else {
				message(unknown_command, 0);
			}
			break;
		case '\024':
			if (wizard) {
				show_traps();
			} else {
				message(unknown_command, 0);
			}
			break;
		case '\017':
			if (wizard) {
				show_objects();
			} else {
				message(unknown_command, 0);
			}
			break;
		case '\001':
			show_average_hp();
			break;
		case '\003':
			if (wizard) {
				c_object_for_wizard();
			} else {
				message(unknown_command, 0);
			}
			break;
		case '\015':
			if (wizard) {
				show_monsters();
			} else {
				message(unknown_command, 0);
			}
			break;
		case 'S':
			save_game();
			break;
		default:
			message(unknown_command, 0);
			break;
		}
	}
}
E 1
