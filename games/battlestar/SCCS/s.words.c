h49057
s 00001/00001/00179
d D 8.2 95/04/28 15:42:22 bostic 8 7
c externs.h -> extern.h
e
s 00002/00002/00178
d D 8.1 93/05/31 16:13:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00179
d D 5.3 90/06/01 13:03:36 bostic 6 5
c new copyright notice
e
s 00010/00005/00180
d D 5.2 88/06/19 14:11:34 bostic 5 4
c install approved copyright notice
e
s 00011/00005/00174
d D 5.1 88/05/08 15:49:59 bostic 4 3
c add Berkeley header; yank to 5.1
e
s 00006/00000/00173
d D 1.3 85/04/24 15:30:49 edward 3 2
c copyright messages
e
s 00164/00164/00009
d D 1.2 85/04/23 10:03:51 edward 2 1
c use macros in place of literal constants
e
s 00173/00000/00000
d D 1.1 85/04/22 15:42:08 edward 1 0
c date and time created 85/04/22 15:42:08 by edward
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 4
I 4
D 7
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

E 3
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

D 8
#include "externs.h"
E 8
I 8
#include "extern.h"
E 8

struct wlist wlist[] = {
D 2
	{ "knife", 0, 1 },
	{ "sword", 1, 2 },
	{ "scabbard", 1, 1 },
	{ "fine", 1, 1 },
	{ "two-handed", 4, 1 },
	{ "cleaver", 5, 1 },
	{ "broadsword", 6, 1 },
	{ "mail", 7, 1 },
	{ "coat", 7, 1 },
	{ "helmet", 8, 1 },
	{ "shield", 9, 1 },
	{ "maid", 10, 1 },
	{ "maid's", 10, 1 },
	{ "body", 10, 2 },
	{ "viper", 11, 1 },
	{ "lamp", 12, 1 },
	{ "lantern", 12, 1 },
	{ "shoes", 13, 1 },
	{ "pajamas", 15, 1 },
	{ "robe", 16, 1 },
	{ "amulet", 17, 2 },
	{ "medallion", 18, 2 },
	{ "talisman", 19, 2 },
	{ "woodsman", 20, 1 },
	{ "woodsman's", 20, 1 },
	{ "mallet", 21, 1 },
	{ "laser", 22, 1 },
	{ "pistol", 22, 1 },
	{ "blaster", 22, 1 },
	{ "gun", 22, 1 },
	{ "goddess", 24, 2 },
	{ "grenade", 25, 1 },
	{ "chain", 26, 1 },
	{ "rope", 27, 1 },
	{ "levis", 28, 1 },
	{ "pants", 28, 1 },
	{ "mace", 29, 1 },
	{ "shovel", 30, 1 },
	{ "halberd", 31, 1 },
	{ "compass", 32, 1 },
	{ "elf", 34, 1 },
	{ "coins", 36, 1 },
	{ "matches", 37, 1 },
	{ "match", 37, 1 },
	{ "book", 37, 1 },
	{ "man", 38, 2 },
	{ "papayas", 39, 1 },
	{ "pineapple", 40, 1 },
	{ "kiwi", 41, 1 },
	{ "coconuts", 42, 1 },
	{ "mango", 43, 1 },
	{ "ring", 44, 1 },
	{ "potion", 45, 1 },
	{ "bracelet", 46, 1 },
	{ "timer", 50, 2 },
	{ "bomb", 54, 1 },
	{ "warhead", 54, 1 },
	{ "girl", 58, 2 },
	{ "native", 58, 2 },
	{ "horse", 59, 1 },
	{ "stallion", 59, 1 },
	{ "car", 60, 1 },
	{ "volare", 60, 1 },
	{ "pot", 61, 1 },
	{ "jewels", 61, 1 },
	{ "bar", 62, 1 },
	{ "diamond", 63, 1 },
	{ "block", 63, 1 },
	{ "up", 1000, 0 },
	{ "u", 1000, 0 },
	{ "down", 1001, 0 },
	{ "d", 1001, 0 },
	{ "ahead", 1002, 0 },
	{ "a", 1002, 0 },
	{ "back", 1003, 0 },
	{ "b", 1003, 0 },
	{ "right", 1004, 0 },
	{ "r", 1004, 0 },
	{ "left", 1005, 0 },
	{ "l", 1005, 0 },
	{ "take", 1006, 0 },
	{ "get", 1006, 0 },
	{ "use", 1007, 0 },
	{ "look", 1008, 0 },
	{ "lo", 1008, 0 },
	{ "quit", 1009, 0 },
	{ "q", 1009, 0 },
	{ "su", 1014, 0 },
	{ "drop", 1015, 0 },
	{ "draw", 1017, 0 },
	{ "pull", 1017, 0 },
	{ "carry", 1017, 0 },
	{ "wear", 1019, 0 },
	{ "sheathe", 1019, 0 },
	{ "put", 1020, 0 },
	{ "buckle", 1020, 0 },
	{ "strap", 1020, 0 },
	{ "tie", 1020, 0 },
	{ "inven", 1021, 0 },
	{ "i", 1021, 0 },
	{ "everything", 1022, 1 },
	{ "all", 1022, 1 },
	{ "and", 1023, 5 },
	{ "kill", 1024, 0 },
	{ "fight", 1024, 0 },
	{ "ravage", 1025, 0 },
	{ "rape", 1025, 0 },
	{ "undress", 1026, 0 },
	{ "throw", 1027, 0 },
	{ "launch", 1028, 0 },
	{ "land", 1029, 0 },
	{ "light", 1030, 0 },
	{ "strike", 1030, 0 },
	{ "follow", 1031, 0 },
	{ "chase", 1031, 0 },
	{ "kiss", 1032, 0 },
	{ "love", 1033, 0 },
	{ "fuck", 1033, 0 },
	{ "give", 1034, 0 },
	{ "smite", 1035, 0 },
	{ "attack", 1035, 0 },
	{ "swing", 1035, 0 },
	{ "stab", 1035, 0 },
	{ "slice", 1035, 0 },
	{ "cut", 1035, 0 },
	{ "hack", 1035, 0 },
	{ "shoot", 1036, 0 },
	{ "blast", 1036, 0 },
	{ "on", 1037, 3 },
	{ "off", 1038, 3 },
	{ "time", 1039, 0 },
	{ "sleep", 1040, 0 },
	{ "dig", 1041, 0 },
	{ "eat", 1042, 0 },
	{ "swim", 1043, 0 },
	{ "drink", 1044, 0 },
	{ "door", 1045, 2 },
	{ "save", 1046, 0 },
	{ "ride", 1047, 0 },
	{ "mount", 1047, 0 },
	{ "drive", 1048, 0 },
	{ "start", 1048, 0 },
	{ "score", 1049, 0 },
	{ "points", 1049, 0 },
	{ "bury", 1050, 0 },
	{ "jump", 1051, 0 },
	{ "kick", 1052, 0 },
	{ "kerosene", 0, 4 },
	{ "plumed", 0, 4 },
	{ "ancient", 0, 4 },
	{ "golden", 0, 4 },
	{ "gold", 0, 4 },
	{ "ostrich", 0, 4 },
	{ "rusty", 0, 4 },
	{ "old", 0, 4 },
	{ "dented", 0, 4 },
	{ "blue", 0, 4 },
	{ "purple", 0, 4 },
	{ "kingly", 0, 4 },
	{ "the", 0, 4 },
	{ "climb", 0, 4 },
	{ "move", 0, 4 },
	{ "make", 0, 4 },
	{ "to", 0, 4 },
E 2
I 2
	{ "knife",	KNIFE,		OBJECT },
	{ "sword",	SWORD,		NOUNS },
	{ "scabbard",	SWORD,		OBJECT },
	{ "fine",	SWORD,		OBJECT },
	{ "two-handed",	TWO_HANDED,	OBJECT },
	{ "cleaver",	CLEAVER,	OBJECT },
	{ "broadsword",	BROAD,		OBJECT },
	{ "mail",	MAIL,		OBJECT },
	{ "coat",	MAIL,		OBJECT },
	{ "helmet",	HELM,		OBJECT },
	{ "shield",	SHIELD,		OBJECT },
	{ "maid",	MAID,		OBJECT },
	{ "maid's",	MAID,		OBJECT },
	{ "body",	BODY,		NOUNS },
	{ "viper",	VIPER,		OBJECT },
	{ "lamp",	LAMPON,		OBJECT },
	{ "lantern",	LAMPON,		OBJECT },
	{ "shoes",	SHOES,		OBJECT },
	{ "pajamas",	PAJAMAS,	OBJECT },
	{ "robe",	ROBE,		OBJECT },
	{ "amulet",	AMULET,		NOUNS },
	{ "medallion",	MEDALION,	NOUNS },
	{ "talisman",	TALISMAN,	NOUNS },
	{ "woodsman",	DEADWOOD,	OBJECT },
	{ "woodsman's",	DEADWOOD,	OBJECT },
	{ "mallet",	MALLET,		OBJECT },
	{ "laser",	LASER,		OBJECT },
	{ "pistol",	LASER,		OBJECT },
	{ "blaster",	LASER,		OBJECT },
	{ "gun",	LASER,		OBJECT },
	{ "goddess",	NORMGOD,	NOUNS },
	{ "grenade",	GRENADE,	OBJECT },
	{ "chain",	CHAIN,		OBJECT },
	{ "rope",	ROPE,		OBJECT },
	{ "levis",	LEVIS,		OBJECT },
	{ "pants",	LEVIS,		OBJECT },
	{ "mace",	MACE,		OBJECT },
	{ "shovel",	SHOVEL,		OBJECT },
	{ "halberd",	HALBERD,	OBJECT },
	{ "compass",	COMPASS,	OBJECT },
	{ "elf",	ELF,		OBJECT },
	{ "coins",	COINS,		OBJECT },
	{ "matches",	MATCHES,	OBJECT },
	{ "match",	MATCHES,	OBJECT },
	{ "book",	MATCHES,	OBJECT },
	{ "man",	MAN,		NOUNS },
	{ "papayas",	PAPAYAS,	OBJECT },
	{ "pineapple",	PINEAPPLE,	OBJECT },
	{ "kiwi",	KIWI,		OBJECT },
	{ "coconuts",	COCONUTS,	OBJECT },
	{ "mango",	MANGO,		OBJECT },
	{ "ring",	RING,		OBJECT },
	{ "potion",	POTION,		OBJECT },
	{ "bracelet",	BRACELET,	OBJECT },
	{ "timer",	TIMER,		NOUNS },
	{ "bomb",	BOMB,		OBJECT },
	{ "warhead",	BOMB,		OBJECT },
	{ "girl",	NATIVE,		NOUNS },
	{ "native",	NATIVE,		NOUNS },
	{ "horse",	HORSE,		OBJECT },
	{ "stallion",	HORSE,		OBJECT },
	{ "car",	CAR,		OBJECT },
	{ "volare",	CAR,		OBJECT },
	{ "pot",	POT,		OBJECT },
	{ "jewels",	POT,		OBJECT },
	{ "bar",	BAR,		OBJECT },
	{ "diamond",	BLOCK,		OBJECT },
	{ "block",	BLOCK,		OBJECT },
	{ "up",		UP,		VERB },
	{ "u",		UP,		VERB },
	{ "down",	DOWN,		VERB },
	{ "d",		DOWN,		VERB },
	{ "ahead",	AHEAD,		VERB },
	{ "a",		AHEAD,		VERB },
	{ "back",	BACK,		VERB },
	{ "b",		BACK,		VERB },
	{ "right",	RIGHT,		VERB },
	{ "r",		RIGHT,		VERB },
	{ "left",	LEFT,		VERB },
	{ "l",		LEFT,		VERB },
	{ "take",	TAKE,		VERB },
	{ "get",	TAKE,		VERB },
	{ "use",	USE,		VERB },
	{ "look",	LOOK,		VERB },
	{ "lo",		LOOK,		VERB },
	{ "quit",	QUIT,		VERB },
	{ "q",		QUIT,		VERB },
	{ "su",		SU,		VERB },
	{ "drop",	DROP,		VERB },
	{ "draw",	DRAW,		VERB },
	{ "pull",	DRAW,		VERB },
	{ "carry",	DRAW,		VERB },
	{ "wear",	WEARIT,		VERB },
	{ "sheathe",	WEARIT,		VERB },
	{ "put",	PUT,		VERB },
	{ "buckle",	PUT,		VERB },
	{ "strap",	PUT,		VERB },
	{ "tie",	PUT,		VERB },
	{ "inven",	INVEN,		VERB },
	{ "i",		INVEN,		VERB },
	{ "everything",	EVERYTHING,	OBJECT },
	{ "all",	EVERYTHING,	OBJECT },
	{ "and",	AND,		CONJ },
	{ "kill",	KILL,		VERB },
	{ "fight",	KILL,		VERB },
	{ "ravage",	RAVAGE,		VERB },
	{ "rape",	RAVAGE,		VERB },
	{ "undress",	UNDRESS,	VERB },
	{ "throw",	THROW,		VERB },
	{ "launch",	LAUNCH,		VERB },
	{ "land",	LANDIT,		VERB },
	{ "light",	LIGHT,		VERB },
	{ "strike",	LIGHT,		VERB },
	{ "follow",	FOLLOW,		VERB },
	{ "chase",	FOLLOW,		VERB },
	{ "kiss",	KISS,		VERB },
	{ "love",	LOVE,		VERB },
	{ "fuck",	LOVE,		VERB },
	{ "give",	GIVE,		VERB },
	{ "smite",	SMITE,		VERB },
	{ "attack",	SMITE,		VERB },
	{ "swing",	SMITE,		VERB },
	{ "stab",	SMITE,		VERB },
	{ "slice",	SMITE,		VERB },
	{ "cut",	SMITE,		VERB },
	{ "hack",	SMITE,		VERB },
	{ "shoot",	SHOOT,		VERB },
	{ "blast",	SHOOT,		VERB },
	{ "on",		ON,		PREPS },
	{ "off",	OFF,		PREPS },
	{ "time",	TIME,		VERB },
	{ "sleep",	SLEEP,		VERB },
	{ "dig",	DIG,		VERB },
	{ "eat",	EAT,		VERB },
	{ "swim",	SWIM,		VERB },
	{ "drink",	DRINK,		VERB },
	{ "door",	DOOR,		NOUNS },
	{ "save",	SAVE,		VERB },
	{ "ride",	RIDE,		VERB },
	{ "mount",	RIDE,		VERB },
	{ "drive",	DRIVE,		VERB },
	{ "start",	DRIVE,		VERB },
	{ "score",	SCORE,		VERB },
	{ "points",	SCORE,		VERB },
	{ "bury",	BURY,		VERB },
	{ "jump",	JUMP,		VERB },
	{ "kick",	KICK,		VERB },
	{ "kerosene",	0,		ADJS },
	{ "plumed",	0,		ADJS },
	{ "ancient",	0,		ADJS },
	{ "golden",	0,		ADJS },
	{ "gold",	0,		ADJS },
	{ "ostrich",	0,		ADJS },
	{ "rusty",	0,		ADJS },
	{ "old",	0,		ADJS },
	{ "dented",	0,		ADJS },
	{ "blue",	0,		ADJS },
	{ "purple",	0,		ADJS },
	{ "kingly",	0,		ADJS },
	{ "the",	0,		ADJS },
	{ "climb",	0,		ADJS },
	{ "move",	0,		ADJS },
	{ "make",	0,		ADJS },
	{ "to",		0,		ADJS },
E 2
	0
};
E 1
