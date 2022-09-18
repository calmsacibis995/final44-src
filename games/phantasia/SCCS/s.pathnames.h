h09715
s 00002/00012/00016
d D 8.2 94/04/02 14:43:51 bostic 4 3
c update the copyright
e
s 00002/00002/00026
d D 8.1 93/05/31 17:40:21 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00012/00019
d D 5.2 90/05/02 21:50:59 bostic 2 1
c move to /var/games, delete unnecessary items
e
s 00031/00000/00000
d D 5.1 90/03/05 12:19:04 bostic 1 0
c date and time created 90/03/05 12:19:04 by bostic
e
u
U
t
T
I 1
D 4
/*
E 4
I 4
/*-
E 4
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_ENEMY	"/usr/games/lib/phantasia/enemy"
#define	_PATH_GAMEPROG	"/usr/games/phantasia/phantasia"
#define	_PATH_GOLD	"/usr/games/lib/phantasia/gold"
#define	_PATH_HELP	"/usr/games/lib/phantasia/phant.help"
#define	_PATH_LASTDEAD	"/usr/games/lib/phantasia/lastdead"
#define	_PATH_MESS	"/usr/games/lib/phantasia/mess"
#define	_PATH_MONST	"/usr/games/lib/phantasia/monsters"
#define	_PATH_MOTD	"/usr/games/lib/phantasia/motd"
#define	_PATH_PEOPLE	"/usr/games/lib/phantasia/characs"
#define	_PATH_PHANTDIR	"/usr/games/lib/phantasia"
#define	_PATH_SCORE	"/usr/games/lib/phantasia/scoreboard"
#define	_PATH_VOID	"/usr/games/lib/phantasia/void"
E 2
I 2
#define	_PATH_GAMEPROG	"/usr/games/phantasia"
#define	_PATH_GOLD	"/var/games/phantasia/gold"
#define	_PATH_LASTDEAD	"/var/games/phantasia/lastdead"
#define	_PATH_MESS	"/var/games/phantasia/mess"
#define	_PATH_MONST	"/var/games/phantasia/monsters"
#define	_PATH_MOTD	"/var/games/phantasia/motd"
#define	_PATH_PEOPLE	"/var/games/phantasia/characs"
#define	_PATH_SCORE	"/var/games/phantasia/scoreboard"
#define	_PATH_VOID	"/var/games/phantasia/void"
E 2
E 1
