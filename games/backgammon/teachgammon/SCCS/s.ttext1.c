h42062
s 00002/00002/00156
d D 8.1 93/05/31 16:11:17 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00157
d D 5.4 90/06/01 13:00:50 bostic 6 5
c new copyright notice
e
s 00010/00005/00158
d D 5.3 88/06/18 19:47:28 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00154
d D 5.2 88/02/16 11:16:48 bostic 4 3
c authored by Alan Char; add Berkeley specific header
e
s 00009/00001/00148
d D 5.1 85/05/29 11:39:30 dist 3 2
c Add copyright
e
s 00000/00000/00149
d D 4.1 82/05/11 15:02:51 rrh 2 1
c bringing to release 4.1
e
s 00149/00000/00000
d D 1.1 82/05/11 14:54:31 rrh 1 0
c date and time created 82/05/11 14:54:31 by rrh
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

#include "back.h"

char	*opts = " QIMRHEDSPT";
char	*prompt = "-->";

char *list[] = {
    "\n\n\tI\tIntroduction to Backgammon",
    "\tM\tMoves and Points",
    "\tR\tRemoving Men from the Board",
    "\tH\tHitting Blots",
    "\tE\tEnding the Game and Scoring",
    "\tD\tDoubling",
    "\tS\tStrategy",
    "\tP\tThe Program and How to Use It",
    "\nalso, you can type:",
    "\t?\tto get this list",
    "\tQ\tto go start playing",
    "\tT\tto go straight to the tutorial",
    0
};

char	*hello[] = {
    "\n\032   These rules consist of text describing how to play Backgammon",
    "followed by a tutorial session where you play a practice game",
    "against the computer.  When using this program, think carefuly",
    "before typing, since it reacts as soon as you type something.  In",
    "addition, the program presents text output, such as these rules,",
    "in small blocks that will not roll off the top of the screen.",
    "Frequently, you will see the characters '-->' indicating that the",
    "program is waiting for you to finish reading, and will continue",
    "printing when you type a space or newline.  Also, the rules are",
    "divided into sections, and although you should read them in or-",
    "der, you can go directly to any of them by typing one of the fol-",
    "lowing letters:",
    "(Remember to hit a space or a newline to continue.)",
    "",
    0
};

char	*intro1[] = {
    "\nIntroduction:",
    "\n   Backgammon is a game involving the skill of two players and",
    "the luck of two dice.  There are two players, red and white, and",
    "each player gets fifteen men.  The object of the game is to re-",
    "move all your men from the board before the opponent does.  The",
    "board consists of twenty-four positions, a 'bar' and a 'home' for",
    "each player.  It looks like this:",
    "",
    0};

char	*intro2[] = {
    "",
    "\n   Although not indicated on the board, the players' homes are",
    "located just to the right of the board.  A player's men are placed",
    "there when they are removed from the board.  The board you just",
    "saw was in it's initial position.  All games start with the board",
    "looking like this.  Notice that red's pieces are represented by the",
    "letter 'r' and white's pieces are represented by the letter 'w'.",
    "Also, a position may have zero or more pieces on it, e.g.  posi-",
    "tion 12 has five red pieces on it, while position 11 does not",
    "have any pieces of either color.",
    "",
    0};

char	*moves[] = {
    "\nMoves and Points:",
    "\n   Moves are made along the positions on the board according to",
    "their numbers.  Red moves in the positive direction (clockwise",
    "from 1 to 24), and white moves in the negative direction (coun-",
    "terclockwise from 24 to 1).",
    "\n   A turn consists of rolling the dice, and moving the number of",
    "positions indicated on each die.  The two numbers can be used to",
    "move one man the sum of the two rolls, or two men the number on",
    "each individual die.  For example, if red rolled 6 3 at the start",
    "of the game, he might move a man from 1 to 7 to 10, using both",
    "dice for one man, or he might move two men from position 12, one",
    "to 15 and one to 18.  (Red did not have to choose two men start-",
    "ing from the same position.)  In addition, doubles are treated",
    "specially in backgammon.  When a player rolls doubles, he gets to",
    "move as if he had four dice instead of two.  For instance, if you",
    "rolled double 2's, you could move one man eight positions, four",
    "men two positions each, or any permutation in between.",
    "",
    "\n   However, there are certain limitations, called 'points.'  A",
    "player has a point when he has two or more men on the same posi-",
    "tion.  This gives him custody of that position, and his opponent",
    "cannot place his men there, even if passing through on the way to",
    "another position.  When a player has six points in a row, it is",
    "called a 'wall,' since any of his opponent's men behind the wall",
    "cannot pass it and are trapped, at least for the moment.  Notice",
    "that this could mean that a player could not use part or all of",
    "his roll.  However, he must use as much of his roll as possible.",
    "",
    0};

char	*remove[] = {
    "\nRemoving Men from the Board:",
    "\n   The most important part of the game is removing men, since",
    "that is how you win the game.  Once a man is removed, he stays",
    "off the board for the duration of the game.  However, a player",
    "cannot remove men until all his men are on his 'inner table,' or",
    "the last six positions of the board (19-24 for red, 6-1 for",
    "white).",
    "\n   To get off the board, a player must roll the exact number to",
    "get his man one position past the last position on the board, or",
    "his 'home.'  Hence, if red wanted to remove a man from position",
    "23, he would have to roll a 2, anything else would be used for",
    "another man, or for another purpose.  However, there is one ex-",
    "ception.  If the player rolling has no men far enough to move the",
    "roll made, he may move his farthest man off the board.  For exam-",
    "ple, if red's farthest man back was on position 21, he could re-",
    "move men from that position if he rolled a 5 or a 6, as well as a",
    "4.  Since he does not have men on 20 (where he could use a 5) or",
    "on 19 (where he could use a 6), he can use these rolls for posi-",
    "tion 21.  A player never has to remove men, but he must make as",
    "many moves as possible.",
    "",
    0};

char	*hits[] = {
    "\nHitting Blots:",
    "\n   Although two men on a position form an impenetrable point, a",
    "lone man is not so secure.  Such a man is called a 'blot' and has",
    "the potential of getting hit by an opposing man.  When a player's",
    "blot is hit, he is placed on the bar, and the first thing that",
    "player must do is move the man off the bar.  Such moves are",
    "counted as if the bar is one position behind the first position",
    "on the board.  Thus if red has a man on the bar and rolls 2 3, he",
    "must move the man on the bar to position 2 or 3 before moving any",
    "other man.  If white had points on positions 2 and 3, then red",
    "would forfeit his turn.  Being on the bar is a very bad position,",
    "for often a player can lose many turns trying to move off the",
    "bar, as well as being set back the full distance of the board.",
    "",
    0};

char	*endgame[] = {
    "\nEnding the Game and Scoring:",
    "\n   Winning a game usually wins one point, the normal value of a",
    "game.  However, if the losing player has not removed any men yet,",
    "then the winning player wins double the game value, called a",
    "'gammon.'  If the losing player has a player on the bar or on the",
    "winner's inner table, then the winner gets triple the game value,",
    "which is called a 'backgammon.'  (So that's where the name comes",
    "from!)",
    "",
    0};
E 1
