h08417
s 00002/00002/00144
d D 8.1 93/05/31 17:25:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00145
d D 5.5 90/06/01 13:07:38 bostic 5 4
c new copyright notice
e
s 00010/00005/00146
d D 5.4 88/06/18 19:38:20 bostic 4 3
c install approved copyright notice
e
s 00001/00001/00150
d D 5.3 88/04/24 15:21:18 bostic 3 2
c fix for ANSI C
e
s 00009/00003/00142
d D 5.2 87/12/29 17:10:19 bostic 2 1
c Berkeley header
e
s 00145/00000/00000
d D 5.1 86/11/26 13:34:45 bostic 1 0
c date and time created 86/11/26 13:34:45 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1993
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
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"mille.h"

/*
 * @(#)extern.c	1.1 (Berkeley) 4/1/82
 */

bool	Debug,			/* set if debugging code on		*/
	Finished,		/* set if current hand is finished	*/
	Next,			/* set if changing players		*/
	On_exit,		/* set if game saved on exiting		*/
	Order,			/* set if hand should be sorted		*/
	Saved;			/* set if game just saved		*/

char	*C_fmt = "%-18.18s",	/* format for printing cards		*/
	*Fromfile = NULL,	/* startup file for game		*/
	Initstr[100],		/* initial string for error field	*/
	*_cn[NUM_CARDS] = {	/* Card name buffer			*/
		"",
		"25",
		"50",
		"75",
		"100",
		"200",
		"Out of Gas",
		"Flat Tire",
		"Accident",
		"Stop",
		"Speed Limit", 
		"Gasoline",
		"Spare Tire",
		"Repairs",
		"Go",
		"End of Limit",
		"Extra Tank",
		"Puncture Proof",
		"Driving Ace",
		"Right of Way"
	},
	**C_name = &_cn[1];	/* Card names				*/

int	Card_no,		/* Card number for current move		*/
	End,			/* End value for current hand		*/
	Handstart = COMP,	/* Player who starts hand		*/
	Movetype,		/* Current move type			*/
	Play,			/* Current player			*/
	Numgos,			/* Number of Go cards used by computer	*/
	Window = W_SMALL,	/* Current window wanted		*/
	Numseen[NUM_CARDS],	/* Number of cards seen in current hand	*/
	Value[NUM_MILES] = {	/* Value of mileage cards		*/
		25, 50, 75, 100, 200
	},
	Numcards[NUM_CARDS] = {	/* Number of cards in deck		*/
		10,	/* C_25 */
		10,	/* C_50 */
		10,	/* C_75 */
		12,	/* C_100 */
		4,	/* C_200 */
		2,	/* C_EMPTY */
		2,	/* C_FLAT */
		2,	/* C_CRASH */
		4,	/* C_STOP */
		3,	/* C_LIMIT */
		6,	/* C_GAS */
		6,	/* C_SPARE */
		6,	/* C_REPAIRS */
		14,	/* C_GO */
		6,	/* C_END_LIMIT */
		1,	/* C_GAS_SAFE */
		1,	/* C_SPARE_SAFE */
		1,	/* C_DRIVE_SAFE */
		1,	/* C_RIGHT_WAY */
		0	/* C_INIT */
D 3
	};
E 3
I 3
	},
E 3
	Numneed[NUM_CARDS] = {	/* number of cards needed per hand	*/
		0,	/* C_25 */
		0,	/* C_50 */
		0,	/* C_75 */
		0,	/* C_100 */
		0,	/* C_200 */
		2,	/* C_EMPTY */
		2,	/* C_FLAT */
		2,	/* C_CRASH */
		4,	/* C_STOP */
		3,	/* C_LIMIT */
		2,	/* C_GAS */
		2,	/* C_SPARE */
		2,	/* C_REPAIRS */
		10,	/* C_GO */
		3,	/* C_END_LIMIT */
		1,	/* C_GAS_SAFE */
		1,	/* C_SPARE_SAFE */
		1,	/* C_DRIVE_SAFE */
		1,	/* C_RIGHT_WAY */
		0	/* C_INIT */
	};

CARD	Discard,		/* Top of discard pile			*/
	Sh_discard,		/* Last discard card shown		*/
	*Topcard,		/* Pointer to next card to be picked	*/
	Opposite[NUM_CARDS] = {	/* Opposites of each card		*/
		C_25, C_50, C_75, C_100, C_200, C_GAS, C_SPARE,
		C_REPAIRS, C_GO, C_END_LIMIT, C_EMPTY, C_FLAT, C_CRASH,
		C_STOP, C_LIMIT, C_EMPTY, C_FLAT, C_CRASH, C_STOP, C_INIT
	},
	Deck[DECK_SZ] = {	/* Current deck				*/
		C_25, C_25, C_25, C_25, C_25, C_25, C_25, C_25, C_25, C_25,
		C_50, C_50, C_50, C_50, C_50, C_50, C_50, C_50, C_50, C_50,
		C_75, C_75, C_75, C_75, C_75, C_75, C_75, C_75, C_75, C_75,
		C_100, C_100, C_100, C_100, C_100, C_100, C_100, C_100, C_100,
		C_100, C_100, C_100,
		C_200, C_200, C_200, C_200,
		C_EMPTY, C_EMPTY,
		C_FLAT, C_FLAT,
		C_CRASH, C_CRASH,
		C_STOP, C_STOP, C_STOP, C_STOP,
		C_LIMIT, C_LIMIT, C_LIMIT,
		C_GAS, C_GAS, C_GAS, C_GAS, C_GAS, C_GAS,
		C_SPARE, C_SPARE, C_SPARE, C_SPARE, C_SPARE, C_SPARE,
		C_REPAIRS, C_REPAIRS, C_REPAIRS, C_REPAIRS, C_REPAIRS,
			C_REPAIRS,
		C_END_LIMIT, C_END_LIMIT, C_END_LIMIT, C_END_LIMIT, C_END_LIMIT,
			C_END_LIMIT,
		C_GO, C_GO, C_GO, C_GO, C_GO, C_GO, C_GO, C_GO, C_GO, C_GO,
			C_GO, C_GO, C_GO, C_GO,
		C_GAS_SAFE, C_SPARE_SAFE, C_DRIVE_SAFE, C_RIGHT_WAY
	};

FILE	*outf;

PLAY	Player[2];		/* Player descriptions			*/

WINDOW	*Board,			/* Playing field screen			*/
	*Miles,			/* Mileage screen			*/
	*Score;			/* Score screen				*/

E 1
