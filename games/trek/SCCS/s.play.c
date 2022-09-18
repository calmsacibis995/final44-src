h53126
s 00002/00002/00082
d D 8.1 93/05/31 17:57:28 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00002/00074
d D 5.6 90/06/26 21:43:23 bostic 8 7
c setexit and reset are gone; use setjmp/longjmp
e
s 00001/00011/00075
d D 5.5 90/06/01 13:25:24 bostic 7 6
c new copyright notice
e
s 00001/00002/00085
d D 5.4 90/05/03 11:42:12 bostic 6 5
c remove subshell command
e
s 00010/00005/00077
d D 5.3 88/06/18 15:08:05 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00073
d D 5.2 88/05/05 18:34:29 bostic 4 3
c written by Eric Allman; add Berkeley header
e
s 00007/00001/00069
d D 5.1 86/01/29 16:36:51 mckusick 3 2
c add copyright
e
s 00029/00025/00041
d D 4.2 83/05/27 00:34:31 layer 2 1
c finished conversion to 4.1c
e
s 00066/00000/00000
d D 4.1 83/03/23 15:00:48 mckusick 1 0
c date and time created 83/03/23 15:00:48 by mckusick
e
u
U
t
T
I 3
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
E 4
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

# include	"trek.h"
# include	"getpar.h"
I 8
# include	<setjmp.h>
E 8

/*
**  INSTRUCTION READ AND MAIN PLAY LOOP
**
**	Well folks, this is it.  Here we have the guts of the game.
**	This routine executes moves.  It sets up per-move variables,
**	gets the command, and executes the command.  After the command,
**	it calls events() to use up time, attack() to have Klingons
**	attack if the move was not free, and checkcond() to check up
**	on how we are doing after the move.
*/
I 2
extern int	abandon(), capture(), shield(), computer(), dcrept(),
		destruct(), dock(), help(), impulse(), lrscan(),
D 6
		warp(), dumpgame(), rest(), shell(), srscan(),
E 6
I 6
		warp(), dumpgame(), rest(), srscan(),
E 6
D 8
		reset(), torped(), visual(), setwarp(), undock(), phaser();
E 8
I 8
		myreset(), torped(), visual(), setwarp(), undock(), phaser();
E 8
E 2

D 2
struct cvntab	Comtab[]
E 2
I 2
struct cvntab	Comtab[] =
E 2
{
D 2
	"abandon",		"",			&abandon,		0,
	"ca",			"pture",		&capture,		0,
	"cl",			"oak",			&shield,		-1,
	"c",			"omputer",		&computer,		0,
	"da",			"mages",		&dcrept,		0,
	"destruct",		"",			&destruct,		0,
	"do",			"ck",			&dock,			0,
	"help",			"",			&help,			0,
	"i",			"mpulse",		&impulse,		0,
	"l",			"rscan",		&lrscan,		0,
	"m",			"ove",			&warp,			0,
	"p",			"hasers",		&phaser,		0,
	"ram",			"",			&warp,			1,
	"dump",			"",			&dumpgame,		0,
	"r",			"est",			&rest,			0,
	"shell",		"",			&shell,			0,
	"sh",			"ield",			&shield,		0,
	"s",			"rscan",		&srscan,		0,
	"st",			"atus",			&srscan,		-1,
	"terminate",		"",			&reset,			0,
	"t",			"orpedo",		&torped,		0,
	"u",			"ndock",		&undock,		0,
	"v",			"isual",		&visual,		0,
	"w",			"arp",			&setwarp,		0,
E 2
I 2
	"abandon",		"",			abandon,	0,
	"ca",			"pture",		capture,	0,
	"cl",			"oak",			shield,	-1,
	"c",			"omputer",		computer,	0,
	"da",			"mages",		dcrept,	0,
	"destruct",		"",			destruct,	0,
	"do",			"ck",			dock,		0,
	"help",			"",			help,		0,
	"i",			"mpulse",		impulse,	0,
	"l",			"rscan",		lrscan,	0,
	"m",			"ove",			warp,		0,
	"p",			"hasers",		phaser,	0,
	"ram",			"",			warp,		1,
	"dump",			"",			dumpgame,	0,
	"r",			"est",			rest,		0,
D 6
	"shell",		"",			shell,		0,
E 6
	"sh",			"ield",			shield,	0,
	"s",			"rscan",		srscan,	0,
	"st",			"atus",			srscan,	-1,
D 8
	"terminate",		"",			reset,		0,
E 8
I 8
	"terminate",		"",			myreset,	0,
E 8
	"t",			"orpedo",		torped,	0,
	"u",			"ndock",		undock,	0,
	"v",			"isual",		visual,	0,
	"w",			"arp",			setwarp,	0,
E 2
	0
};
I 8

myreset()
{
	extern jmp_buf env;

	longjmp(env, 1);
}
E 8

play()
{
	struct cvntab		*r;

	while (1)
	{
		Move.free = 1;
		Move.time = 0.0;
		Move.shldchg = 0;
		Move.newquad = 0;
		Move.resting = 0;
		skiptonl(0);
		r = getcodpar("\nCommand", Comtab);
		(*r->value)(r->value2);
		events(0);
		attack(0);
		checkcond();
	}
}
E 1
