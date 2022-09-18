h35657
s 00002/00002/00287
d D 8.1 93/05/31 16:11:10 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00288
d D 5.4 90/06/01 13:00:27 bostic 6 5
c new copyright notice
e
s 00010/00005/00289
d D 5.3 88/06/18 19:47:01 bostic 5 4
c install approved copyright notice
e
s 00033/00027/00261
d D 5.2 88/02/16 11:15:17 bostic 4 3
c authored by Alan Char; add Berkeley specific header
c fix random casting problems
e
s 00009/00001/00279
d D 5.1 85/05/29 11:31:49 dist 3 2
c Add copyright
e
s 00000/00000/00280
d D 4.1 82/05/11 15:01:46 rrh 2 1
c bringing to release 4.1
e
s 00280/00000/00000
d D 1.1 82/05/11 14:53:12 rrh 1 0
c date and time created 82/05/11 14:53:12 by rrh
e
u
U
t
T
I 1
D 3
static char sccsid[] = "	%M%	%I%	%E%	";
E 3
I 3
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
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

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

#include "tutor.h"

int	maxmoves = 23;

char  *text0[] = {
	"To start the game, I roll a 3, and you roll a 1.  This means",
	"that I get to start first.  I move 8-5,6-5 since this makes a",
	"new point and helps to trap your back men on 1.  You should be",
	"able to do a similar move with your roll.",
	0
};

char  *text1[] = {
	"Now you shall see a move using doubles.  I just rolled double",
	"5's.  I will move two men from position 13 to position 3.  The",
	"notation for this is 13-8,13-8,8-3,8-3.  You will also roll dou-",
	"bles, but you will be able to make a much stronger move.",
	0
};

char  *text2[] = {
	"Excellent!  As you can see, you are beginning to develop a wall",
	"which is trapping my men on position 24.  Also, moving your back",
	"men forward not only improves your board position safely, but it",
	"thwarts my effort to make a wall.",
	"",
	"My roll now is 5 6.  Normally, I would use that roll to move from",
	"position 24 to position 13 (24-18-13), but your new point prevents",
	"that.  Instead, I am forced to move from 13 to 2, where my man is",
	"open but cannot be hit.",
	0
};

char  *text3[] = {
	"As you can see, although you left a man open, it is a rela-",
	"tively safe move to an advantageous position, which might help",
	"you make a point later.  Only two rolls (4 5 or 5 4) will allow",
	"me to hit you.  With an unprecedented amount of luck, I happen",
	"to roll a 4 5 and hit you as just mentioned.",
	0
};

char  *text4[] = {
	"You're pretty lucky yourself, you know.  I follow by rolling 2 3",
	"and moving 25-22,24-22, forming a new point.",
	0
};

char  *text5[] = {
	"Not a spectacular move, but a safe one.  I follow by rolling 6 1.",
	"I decide to use this roll to move 22-16,16-17.  It leaves me with",
	"one man still open, but the blot is farther back on the board, and",
	"would suffer less of a loss by being hit.",
	0
};

char  *text6[] = {
	"By moving your two men from 17 to 20, you lessen my chance of",
	"getting my man off the board.  In fact, the odds are 5 to 4",
	"against me getting off.  I roll with the odds and helplessly",
	"receive a 3 5.",
	0
};

char  *text7[] = {
	"Note that the blot on 7 cannot be hit unless I get off the bar",
	"and have a 1 or a 6 left over, and doing so will leave two of",
	"my men open.  Also, the blot on 16 cannot be hit at all!  With",
	"a sigh of frustration, I roll double 6's and remain immobile.",
	0
};

char  *text8[] = {
	"See, you did not get hit and, you got to 'cover up' your open men.",
	"Quite an accomplishment.  Finally, I get off the bar by rolling",
	"6 2 and moving 25-23,23-17.",
	0
};

char  *text9[] = {
	"My venture off the bar did not last long.  However, I got lucky",
	"and rolled double 1's, allowing me to move 0-1,1-2,15-14,15-14.",
	0
};

char  *text10[] = {
	"You are improving your position greatly and safely, and are well",
	"on the way to winning the game.  I roll a 6 2 and squeak past",
	"your back man.  Now the game becomes a race to the finish.",
	0
};

char  *text11[] = {
	"Now that it is merely a race, you are trying to get as many men",
	"as possible into the inner table, so you can start removing them.",
	"I roll a 3 4 and move my two men farthest back to position 11",
	"(15-11,14-11).",
	0
};

char  *text12[] = {
	"The race is still on, and you have seem to be doing all right.",
	"I roll 6 1 and move 14-8,13-12.",
	0
};

char  *text13[] = {
	"Notice that you get to remove men the instant you have all of",
	"them at your inner table, even if it is the middle of a turn.",
	"I roll 1 2 and move 13-11,12-11.",
	0
};

char  *text14[] = {
	"Although you could have removed a man, this move illustrates two",
	"points:  1) You never have to remove men, and 2) You should try",
	"to spread out your men on your inner table.  Since you have one",
	"man on each position, you should be able to remove at least two",
	"men next turn.  I roll 2 5 and move 8-6,11-6.",
	0
};

char  *text15[] = {
	"This time you were able to remove men.  I roll 3 4 and move",
	"11-7,11-8.  The race continues.",
	0
};

char  *text16[] = {
	"More holes are opening up in your inner table, but you are",
	"still very much ahead.  If we were doubling, you would have",
	"doubled long ago.  I roll 2 6 and move 8-6,11-5.",
	0
};

char  *text17[] = {
	"It pays to spread out your men.  I roll 3 5 and move 7-4,8-3.",
	0
};

char  *text18[] = {
	"You can only remove some men, but you spread out more and",
	"more, in order to be able to remove men more efficiently.",
	"I roll double 3's, which help, but not that much.  I move",
	"8-5,3-0,3-0,3-0.",
	0
};

char  *text19[] = {
	"I roll 1 4 and move 5-4,4-0.",
	0
};

char  *text20[] = {
	"You are now nicely spread out to win a game.  I roll 5 6 and",
	"move 5-0,6-0.",
	0
};

char  *text21[] = {
	"Any minute now.  Just a few short steps from victory.  I roll",
	"2 4 and move 6-4,4-0.",
	0
};

char  *text22[] = {
	"It looks pretty hopeless for me, but I play on, rolling 1 3 and",
	"moving 4-3,3-0.",
	0
};

char  *text23[] = {
	"Congratulations!  You just won a game of backgammon against the",
	"computer!  You will now be able to play a game, but remember,",
	"when you start playing, that doubling will be enabled, which",
	"will add another factor to the game...  Good luck!!",
	"",
	0
};

struct situatn  test[] = {
	{
		{0,2,0,0,0,0,-5,0,-3,0,0,0,5,-5,0,0,0,3,0,5,0,0,0,0,-2,0},
D 4
		3, 1, {8,6,0,0}, {5,5,0,0}, 4, 2, &text0
E 4
I 4
		3, 1, {8,6,0,0}, {5,5,0,0}, 4, 2, text0
E 4
	},
	{
		{0,2,0,0,0,-2,-4,0,-2,0,0,0,5,-5,0,0,0,2,0,4,0,2,0,0,-2,0},
D 4
		5, 5, {13,13,8,8}, {8,8,3,3}, 6, 6, &text1
E 4
I 4
		5, 5, {13,13,8,8}, {8,8,3,3}, 6, 6, text1
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,2,-2,0,0,0,3,-3,0,0,0,2,2,4,0,2,0,0,-2,0},
D 4
		6, 5, {13,8,0,0}, {8,2,0,0}, 1, 2, &text2
E 4
I 4
		6, 5, {13,8,0,0}, {8,2,0,0}, 1, 2, text2
E 4
	},
	{
		{0,0,-1,-2,0,-2,-4,2,-2,0,0,0,2,-2,0,1,0,2,2,4,0,2,0,0,-2,0},
D 4
		4, 5, {24,20,0,0}, {20,15,0,0}, 2, 5, &text3
E 4
I 4
		4, 5, {24,20,0,0}, {20,15,0,0}, 2, 5, text3
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,3,-2,0,0,0,2,-2,0,-1,0,2,2,4,0,2,0,0,-1,-1},
D 4
		2, 3, {25,24,0,0}, {22,22,0,0}, 4, 1, &text4
E 4
I 4
		2, 3, {25,24,0,0}, {22,22,0,0}, 4, 1, text4
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,2,-2,0,0,0,3,-2,0,-1,0,2,2,4,0,2,-2,0,0,0},
D 4
		6, 1, {22,16,0,0}, {16,15,0,0}, 3, 3, &text5
E 4
I 4
		6, 1, {22,16,0,0}, {16,15,0,0}, 3, 3, text5
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,2,-2,0,0,0,3,-2,0,-2,0,0,2,2,2,2,2,0,0,-1},
D 4
		3, 5, {0,0,0,0}, {0,0,0,0}, 5, 4, &text6
E 4
I 4
		3, 5, {0,0,0,0}, {0,0,0,0}, 5, 4, text6
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,1,-2,0,0,0,3,-2,0,-2,1,0,2,2,2,2,2,0,0,-1},
D 4
		6, 6, {0,0,0,0}, {0,0,0,0}, 3, 6, &text7
E 4
I 4
		6, 6, {0,0,0,0}, {0,0,0,0}, 3, 6, text7
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-2,0,0,0,3,-2,0,-2,2,0,2,2,2,2,2,0,0,-1},
D 4
		2, 6, {25,23,0,0}, {23,17,0,0}, 5, 1, &text8
E 4
I 4
		2, 6, {25,23,0,0}, {23,17,0,0}, 5, 1, text8
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-2,0,0,0,2,-2,0,-2,2,0,3,2,2,2,2,0,0,-1},
D 4
		1, 1, {25,24,15,15}, {24,23,14,14}, 4, 6, &text9
E 4
I 4
		1, 1, {25,24,15,15}, {24,23,14,14}, 4, 6, text9
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-2,0,0,0,0,-2,-2,0,3,0,4,2,2,2,2,-1,0,0},
D 4
		6, 2, {23,17,0,0}, {17,15,0,0}, 1, 3, &text10
E 4
I 4
		6, 2, {23,17,0,0}, {17,15,0,0}, 1, 3, text10
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-2,0,0,0,0,-2,-2,-1,2,0,3,4,2,2,2,0,0,0},
D 4
		4, 3, {15,14,0,0}, {11,11,0,0}, 5, 3, &text11
E 4
I 4
		4, 3, {15,14,0,0}, {11,11,0,0}, 5, 3, text11
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-2,0,0,-2,0,-2,-1,0,0,0,3,5,2,3,2,0,0,0},
D 4
		6, 1, {14,13,0,0}, {8,12,0,0}, 4, 4, &text12
E 4
I 4
		6, 1, {14,13,0,0}, {8,12,0,0}, 4, 4, text12
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-3,0,0,-2,-1,-1,0,0,0,0,0,5,2,2,5,0,0,0},
D 4
		2, 1, {13,12,0,0}, {11,11,0,0}, 2, 1, &text13
E 4
I 4
		2, 1, {13,12,0,0}, {11,11,0,0}, 2, 1, text13
E 4
	},
	{
		{0,0,0,-2,0,-2,-4,0,-3,0,0,-4,0,0,0,0,0,0,0,5,2,2,3,1,1,0},
D 4
		2, 5, {8,11,0,0}, {6,6,0,0}, 6, 3, &text14
E 4
I 4
		2, 5, {8,11,0,0}, {6,6,0,0}, 6, 3, text14
E 4
	},
	{
		{0,0,0,-2,0,-2,-6,0,-2,0,0,-3,0,0,0,0,0,0,0,4,2,2,2,1,1,0},
D 4
		4, 3, {11,11,0,0}, {7,8,0,0}, 2, 5, &text15
E 4
I 4
		4, 3, {11,11,0,0}, {7,8,0,0}, 2, 5, text15
E 4
	},
	{
		{0,0,0,-2,0,-2,-6,-1,-3,0,0,-1,0,0,0,0,0,0,0,4,1,2,2,0,1,0},
D 4
		2, 6, {8,11,0,0}, {6,5,0,0}, 6, 1, &text16
E 4
I 4
		2, 6, {8,11,0,0}, {6,5,0,0}, 6, 1, text16
E 4
	},
	{
		{0,0,0,-2,0,-3,-7,-1,-2,0,0,0,0,0,0,0,0,0,0,3,1,2,2,0,0,0},
D 4
		5, 3, {8,7,0,0}, {3,4,0,0}, 5, 2, &text17
E 4
I 4
		5, 3, {8,7,0,0}, {3,4,0,0}, 5, 2, text17
E 4
	},
	{
		{0,0,0,-3,-1,-3,-7,0,-1,0,0,0,0,0,0,0,0,0,0,3,0,1,2,1,0,0},
D 4
		3, 3, {8,3,3,3}, {5,0,0,0}, 1, 6, &text18
E 4
I 4
		3, 3, {8,3,3,3}, {5,0,0,0}, 1, 6, text18
E 4
	},
	{
		{0,0,0,0,-1,-4,-7,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,0,0},
D 4
		1, 4, {4,5,0,0}, {0,4,0,0}, 2, 3, &text19
E 4
I 4
		1, 4, {4,5,0,0}, {0,4,0,0}, 2, 3, text19
E 4
	},
	{
		{0,0,0,0,-1,-3,-7,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
D 4
		5, 6, {6,5,0,0}, {0,0,0,0}, 1, 4, &text20
E 4
I 4
		5, 6, {6,5,0,0}, {0,0,0,0}, 1, 4, text20
E 4
	},
	{
		{0,0,0,0,-1,-2,-6,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0},
D 4
		2, 4, {4,6,0,0}, {0,4,0,0}, 6, 2, &text21
E 4
I 4
		2, 4, {4,6,0,0}, {0,4,0,0}, 6, 2, text21
E 4
	},
	{
		{0,0,0,0,-1,-2,-5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
D 4
		3, 1, {4,3,0,0}, {3,0,0,0}, 4, 3, &text22
E 4
I 4
		3, 1, {4,3,0,0}, {3,0,0,0}, 4, 3, text22
E 4
	},
	{
		{0,0,0,0,0,-2,-5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
D 4
		0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0, &text23
E 4
I 4
		0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0, text23
E 4
	}
};
E 1
