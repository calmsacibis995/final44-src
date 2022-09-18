h61935
s 00005/00005/00591
d D 8.1 93/05/31 16:49:15 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00356/00345/00240
d D 5.8 93/04/26 10:34:32 bostic 28 27
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00003/00002/00582
d D 5.7 93/04/26 09:14:32 elan 27 26
c check in for Elan by TK -- my guess was to make work with new curses
e
s 00004/00004/00580
d D 5.6 91/02/28 13:08:59 bostic 26 25
c ANSI
e
s 00001/00011/00583
d D 5.5 90/06/01 13:05:10 bostic 25 24
c new copyright notice
e
s 00030/00034/00564
d D 5.4 90/05/01 21:04:53 bostic 24 23
c move into /var, /usr/games
e
s 00010/00005/00588
d D 5.3 88/06/18 14:39:20 bostic 23 22
c install approved copyright notice
e
s 00010/00004/00583
d D 5.2 88/03/10 16:29:12 bostic 22 21
c add Berkeley specific header, Ken Arnold says written @ Berkeley
e
s 00015/00001/00572
d D 5.1 85/05/30 19:49:55 mckusick 21 19
c add copyright
e
s 00009/00001/00572
d R 5.1 85/05/30 19:43:43 mckusick 20 19
c Add copyright
e
s 00000/00014/00573
d D 1.17 83/09/06 12:54:19 arnold 19 18
c make scorehand know what really is a crib and how to deal with flushes
e
s 00002/00000/00585
d D 1.16 83/05/19 12:21:02 arnold 18 17
c add sccs keywords
e
s 00020/00014/00565
d D 1.15 83/05/07 14:06:40 arnold 17 16
c add a scrolling region
e
s 00016/00012/00563
d D 1.14 83/05/01 15:30:46 arnold 16 15
c make a scrolling region for cribbage
e
s 00005/00005/00570
d D 1.13 83/05/01 13:25:59 arnold 15 14
c swap the board and the cards on the screen
e
s 00002/00003/00573
d D 1.12 83/03/03 21:56:45 arnold 14 12
c 
e
s 00021/00012/00564
d R 1.12 82/09/09 16:24:12 arnold 13 12
c if only one card in the hand is playable, just play it.
e
s 00009/00007/00567
d D 1.11 82/09/06 14:59:04 arnold 12 11
c show back of computer's hand during play
e
s 00006/00004/00568
d D 1.10 82/09/06 14:41:30 arnold 11 10
c print out last card play for hand
e
s 00006/00000/00566
d D 1.9 82/09/06 14:34:48 arnold 10 8
c make printing out instructions work properly
e
s 00135/00143/00423
d R 1.9 82/08/28 17:06:05 arnold 9 8
c reformatting and obvious optimization
e
s 00021/00005/00545
d D 1.8 82/08/28 12:38:47 arnold 8 7
c make things look a little nicer
e
s 00008/00003/00542
d D 1.7 82/08/27 23:45:00 arnold 7 6
c add game count and titles to board
e
s 00000/00003/00545
d D 1.6 82/08/27 23:04:57 arnold 6 5
c simplify infrom() prompt mechanism
e
s 00020/00005/00528
d D 1.5 82/08/27 22:55:24 arnold 5 4
c print blank turnover card to indicate crib
e
s 00006/00006/00527
d D 1.4 82/08/27 15:00:08 arnold 4 3
c print starting and ending peg positions
e
s 00010/00010/00523
d D 1.3 82/08/27 14:23:12 arnold 3 2
c make simple <RETURN> not be the same as typing "0"
e
s 00350/00317/00183
d D 1.2 82/08/24 18:33:47 arnold 2 1
c first "working" visual version
e
s 00500/00000/00000
d D 1.1 82/08/11 16:35:50 arnold 1 0
c date and time created 82/08/11 16:35:50 by arnold
e
u
U
t
T
I 18
D 21
static char	*sccsid = "%W% (Berkeley) %G%";
E 21
I 21
D 28
/*
 * Copyright (c) 1980 Regents of the University of California.
E 28
I 28
/*-
D 29
 * Copyright (c) 1980 The Regents of the University of California.
E 28
D 22
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 23
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 23
I 23
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
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 23
E 22
 */

#ifndef lint
D 29
char copyright[] =
D 28
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 28
I 28
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 28
 All rights reserved.\n";
E 29
I 29
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 29
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22
E 21

I 24
D 28
# include	<sys/signal.h>
E 24
E 18
I 2
# include	<curses.h>
D 24
# include	<signal.h>
E 24
# include	"deck.h"
# include	"cribbage.h"
# include	"cribcur.h"
I 24
# include	"pathnames.h"
E 28
I 28
#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 28
E 24
E 2
I 1

I 28
#include "deck.h"
#include "cribbage.h"
#include "cribcur.h"
#include "pathnames.h"

int
E 28
D 2
#include	<stdio.h>
#include	"deck.h"
E 2
D 24

I 2
# define	LOGFILE		"/usr/games/lib/criblog"
# define	INSTRCMD	"ul /usr/games/lib/crib.instr | more -f"
E 2

D 2
#define		LOGFILE		"/usr/games/lib/criblog"
#define		INSTRCMD	"ul /usr/games/lib/crib.instr | more -f"
E 2

E 24
D 2

CARD		deck[ CARDS ];			/* a deck */
CARD		phand[ FULLHAND ];		/* player's hand */
CARD		chand[ FULLHAND ];		/* computer's hand */
CARD		crib[ CINHAND ];		/* the crib */
CARD		turnover;			/* the starter */

CARD		known[ CARDS ];			/* cards we have seen */
int		knownum		= 0;		/* number of cards we know */

int		pscore		= 0;		/* player score in current game */
int		cscore		= 0;		/* comp score in current game */
int		pgames		= 0;		/* number games player won */
int		cgames		= 0;		/* number games comp won */
int		gamecount	= 0;		/* number games played */
int		glimit		= LGAME;	/* game playe to glimit */

BOOLEAN		iwon		= FALSE;	/* if comp won last game */
BOOLEAN		explain		= FALSE;	/* player mistakes explained */
BOOLEAN		rflag		= FALSE;	/* if all cuts random */
BOOLEAN		quiet		= FALSE;	/* if suppress random mess */

char		expl[ 128 ];			/* explanation */


main( argc, argv )

    int		argc;
    char	*argv[];
E 2
I 2
main(argc, argv)
D 28
int	argc;
char	*argv[];
E 28
I 28
	int argc;
	char *argv[];
E 28
E 2
{
I 24
D 28
	extern char *optarg;
	extern int optind;
E 24
D 2
	FILE			*fopen();
	FILE			*f;
	char			*getline();
E 2
	register  char		*p;
E 28
I 28
	BOOLEAN playing;
	FILE *f;
E 28
I 24
	int ch;
E 24
D 28
	BOOLEAN			playing;
	char			*s;		/* for reading arguments */
D 24
	char			bust;		/* flag for arg reader */
E 24
I 2
	FILE			*f;
	FILE			*fopen();
D 24
	char			*getline();
	int			bye();
E 24
I 24
	char			*getline(), *getlogin();
	void			rint();
E 28
E 24
E 2

D 2
	while( --argc > 0 )  {
	    if(  (*++argv)[0] != '-'  )  {
		fprintf( stderr, "\n\ncribbage: usage is 'cribbage [-eqr]'\n" );
		exit( 1 );
E 2
I 2
D 24
	while (--argc > 0) {
	    if ((*++argv)[0] != '-') {
		fprintf(stderr, "\n\ncribbage: usage is 'cribbage [-eqr]'\n");
		exit(1);
E 2
	    }
	    bust = FALSE;
D 2
	    for( s = argv[0] + 1; *s != NULL; s++ ) {
		switch( *s )  {

		    case  'e':
E 2
I 2
	    for (s = argv[0] + 1; *s != NULL; s++) {
		switch (*s) {
		    case 'e':
E 24
I 24
	while ((ch = getopt(argc, argv, "eqr")) != EOF)
D 28
		switch(ch) {
E 28
I 28
		switch (ch) {
E 28
		case 'e':
E 24
E 2
			explain = TRUE;
			break;
D 2

		    case  'q':
E 2
I 2
D 24
		    case 'q':
E 24
I 24
		case 'q':
E 24
E 2
			quiet = TRUE;
			break;
D 2

		    case  'r':
E 2
I 2
D 24
		    case 'r':
E 24
I 24
		case 'r':
E 24
E 2
			rflag = TRUE;
			break;
D 2

E 2
D 24
		    default:
D 2
			fprintf( stderr, "\n\ncribbage: usage is 'cribbage [-eqr]'\n" );
			exit( 2 );
E 2
I 2
			fprintf(stderr, "\n\ncribbage: usage is 'cribbage [-eqr]'\n");
			exit(2);
E 2
			break;
E 24
I 24
		case '?':
		default:
			(void) fprintf(stderr, "usage: cribbage [-eqr]\n");
			exit(1);
E 24
		}
D 2
		if( bust )  break;
E 2
I 2
D 24
		if (bust)
		    break;
E 2
	    }
	}
E 24
D 2
	if( !quiet )  {
	    printf( "\nDo you need instructions for cribbage? " );
	    p = getline();
	    if(  *p == 'Y'  )  {
		system( INSTRCMD );
		printf( "\nFor the rules of this game, do 'man cribbage'\n" );
E 2
I 2

	initscr();
D 24
	signal(SIGINT, bye);
E 24
I 24
D 28
	signal(SIGINT, rint);
E 28
I 28
	(void)signal(SIGINT, rint);
E 28
E 24
	crmode();
	noecho();
I 28

E 28
D 15
	Playwin = subwin(stdscr, PLAY_Y, PLAY_X, 0, 0);
	Tablewin = subwin(stdscr, TABLE_Y, TABLE_X, 0, PLAY_X);
	Compwin = subwin(stdscr, COMP_Y, COMP_X, 0, TABLE_X + PLAY_X);
E 15
I 15
D 16
	Playwin = subwin(stdscr, PLAY_Y, PLAY_X, 0, SCORE_SZ);
	Tablewin = subwin(stdscr, TABLE_Y, TABLE_X, 0, PLAY_X + SCORE_SZ);
	Compwin = subwin(stdscr, COMP_Y, COMP_X, 0, TABLE_X + PLAY_X + SCORE_SZ);
E 16
I 16
D 17
	Playwin = subwin(stdscr, PLAY_Y, PLAY_X, 0, X_SCORE_SZ);
	Tablewin = subwin(stdscr, TABLE_Y, TABLE_X, 0, PLAY_X + X_SCORE_SZ);
	Compwin = subwin(stdscr, COMP_Y, COMP_X, 0, TABLE_X + PLAY_X + X_SCORE_SZ);
	Msgwin = subwin(stdscr, MSG_Y, MSG_X, Y_SCORE_SZ + 1, 0);
E 17
I 17
	Playwin = subwin(stdscr, PLAY_Y, PLAY_X, 0, 0);
	Tablewin = subwin(stdscr, TABLE_Y, TABLE_X, 0, PLAY_X);
	Compwin = subwin(stdscr, COMP_Y, COMP_X, 0, TABLE_X + PLAY_X);
	Msgwin = subwin(stdscr, MSG_Y, MSG_X, Y_MSG_START, SCORE_X + 1);
E 17
E 16
E 15
	leaveok(Playwin, TRUE);
	leaveok(Tablewin, TRUE);
	leaveok(Compwin, TRUE);
I 16
	clearok(stdscr, FALSE);
E 16

	if (!quiet) {
D 28
	    msg("Do you need instructions for cribbage? ");
	    if (getuchar() == 'Y') {
I 10
		endwin();
I 24
		clear();
		mvcur(0, COLS - 1, LINES - 1, 0);
E 24
		fflush(stdout);
E 10
D 24
		system(INSTRCMD);
E 24
I 24
		instructions();
E 24
I 10
		crmode();
		noecho();
		clear();
		refresh();
E 10
		msg("For the rules of this program, do \"man cribbage\"");
E 2
	    }
E 28
I 28
		msg("Do you need instructions for cribbage? ");
		if (getuchar() == 'Y') {
			endwin();
			clear();
			mvcur(0, COLS - 1, LINES - 1, 0);
			fflush(stdout);
			instructions();
			crmode();
			noecho();
			clear();
			refresh();
			msg("For cribbage rules, use \"man cribbage\"");
		}
E 28
	}
	playing = TRUE;
D 2
	do  {
	    printf( quiet ? "\nL or S? " :
				"\nLong (to 121) or Short (to 61)? " );
	    p = getline();
	    glimit = ( *p == 'S' ? SGAME : LGAME );
E 2
I 2
	do {
I 17
D 28
	    wclrtobot(Msgwin);
E 17
D 8
	    makeboard();
E 8
	    msg(quiet ? "L or S? " : "Long (to 121) or Short (to 61)? ");
D 8
	    glimit = (getuchar() == 'S' ? SGAME : LGAME);
E 8
I 8
	    if (glimit == SGAME)
		glimit = (getuchar() == 'L' ? LGAME : SGAME);
	    else
		glimit = (getuchar() == 'S' ? SGAME : LGAME);
E 8
E 2
	    game();
D 2
	    printf( "\nAnother game? " );
	    p = getline();
	    playing = (*p == 'Y');
	}  while( playing );
	if(  ( f = fopen(LOGFILE, "a") ) != NULL  )  {
	    fprintf( f, "Won %5.5d, Lost %5.5d\n",  cgames, pgames );
	    fclose( f );
E 2
I 2
	    msg("Another game? ");
	    playing = (getuchar() == 'Y');
E 28
I 28
		wclrtobot(Msgwin);
		msg(quiet ? "L or S? " : "Long (to 121) or Short (to 61)? ");
		if (glimit == SGAME)
			glimit = (getuchar() == 'L' ? LGAME : SGAME);
		else
			glimit = (getuchar() == 'S' ? SGAME : LGAME);
		game();
		msg("Another game? ");
		playing = (getuchar() == 'Y');
E 28
	} while (playing);

D 24
	if ((f = fopen(LOGFILE, "a")) != NULL) {
	    fprintf(f, "Won %5.5d, Lost %5.5d\n",  cgames, pgames);
	    fclose(f);
E 24
I 24
	if (f = fopen(_PATH_LOG, "a")) {
		(void)fprintf(f, "%s: won %5.5d, lost %5.5d\n",
D 28
		   getlogin(), cgames, pgames);
		(void)fclose(f);
E 28
I 28
		    getlogin(), cgames, pgames);
		(void) fclose(f);
E 28
E 24
E 2
	}
I 2
D 24

E 24
	bye();
I 24
	if (!f) {
D 28
		(void)fprintf(stderr, "\ncribbage: can't open %s.\n",
E 28
I 28
		(void) fprintf(stderr, "\ncribbage: can't open %s.\n",
E 28
		    _PATH_LOG);
		exit(1);
	}
	exit(0);
E 24
E 2
}

I 2
/*
D 19
 * bye:
 *	Leave the program, cleaning things up as we go.
 */
bye()
{
	signal(SIGINT, SIG_IGN);
	mvcur(0, COLS - 1, LINES - 1, 0);
	fflush(stdout);
	endwin();
	putchar('\n');
	exit(1);
}
E 2

D 2

E 2
/*
E 19
D 2
 * play one game up to glimit points
E 2
I 2
 * makeboard:
 *	Print out the initial board on the screen
E 2
 */
I 28
void
E 28
I 2
makeboard()
{
D 8
    extern int	Lastscore[];
E 2

E 8
I 2
D 28
    mvaddstr(SCORE_Y + 0, SCORE_X, "+---------------------------------------+");
D 7
    mvaddstr(SCORE_Y + 1, SCORE_X, "|                                       |");
E 7
I 7
D 14
    mvaddstr(SCORE_Y + 1, SCORE_X, "|                 YOU                   |");
E 14
I 14
    mvaddstr(SCORE_Y + 1, SCORE_X, "|  Score:   0     YOU                   |");
E 14
E 7
D 4
    mvaddstr(SCORE_Y + 2, SCORE_X, "|  .....:.....:.....:.....:.....:.....  |");
    mvaddstr(SCORE_Y + 3, SCORE_X, "|  .....:.....:.....:.....:.....:.....  |");
E 4
I 4
    mvaddstr(SCORE_Y + 2, SCORE_X, "| *.....:.....:.....:.....:.....:.....  |");
    mvaddstr(SCORE_Y + 3, SCORE_X, "| *.....:.....:.....:.....:.....:.....  |");
E 4
    mvaddstr(SCORE_Y + 4, SCORE_X, "|                                       |");
D 4
    mvaddstr(SCORE_Y + 5, SCORE_X, "|  .....:.....:.....:.....:.....:.....  |");
    mvaddstr(SCORE_Y + 6, SCORE_X, "|  .....:.....:.....:.....:.....:.....  |");
E 4
I 4
    mvaddstr(SCORE_Y + 5, SCORE_X, "| *.....:.....:.....:.....:.....:.....  |");
    mvaddstr(SCORE_Y + 6, SCORE_X, "| *.....:.....:.....:.....:.....:.....  |");
E 4
D 7
    mvaddstr(SCORE_Y + 7, SCORE_X, "|                                       |");
E 7
I 7
D 14
    mvaddstr(SCORE_Y + 7, SCORE_X, "|                  ME                   |");
E 14
I 14
    mvaddstr(SCORE_Y + 7, SCORE_X, "|  Score:   0      ME                   |");
E 14
E 7
    mvaddstr(SCORE_Y + 8, SCORE_X, "+---------------------------------------+");
I 8
    gamescore();
E 28
I 28
	mvaddstr(SCORE_Y + 0, SCORE_X,
	    "+---------------------------------------+");
	mvaddstr(SCORE_Y + 1, SCORE_X,
	    "|  Score:   0     YOU                   |");
	mvaddstr(SCORE_Y + 2, SCORE_X,
	    "| *.....:.....:.....:.....:.....:.....  |");
	mvaddstr(SCORE_Y + 3, SCORE_X,
	    "| *.....:.....:.....:.....:.....:.....  |");
	mvaddstr(SCORE_Y + 4, SCORE_X,
	    "|                                       |");
	mvaddstr(SCORE_Y + 5, SCORE_X,
	    "| *.....:.....:.....:.....:.....:.....  |");
	mvaddstr(SCORE_Y + 6, SCORE_X,
	    "| *.....:.....:.....:.....:.....:.....  |");
	mvaddstr(SCORE_Y + 7, SCORE_X,
	    "|  Score:   0      ME                   |");
	mvaddstr(SCORE_Y + 8, SCORE_X,
	    "+---------------------------------------+");
	gamescore();
E 28
}

/*
 * gamescore:
 *	Print out the current game score
 */
I 28
void
E 28
gamescore()
{
D 28
    extern int	Lastscore[];
E 28
I 28
	extern int Lastscore[];
E 28

E 8
I 7
D 28
    if (pgames || cgames) {
	    mvprintw(SCORE_Y + 1, SCORE_X + 28, "Games: %3d", pgames);
	    mvprintw(SCORE_Y + 7, SCORE_X + 28, "Games: %3d", cgames);
    }
E 7
D 4
    Lastscore[0] = 0;
    Lastscore[1] = 0;
E 4
I 4
    Lastscore[0] = -1;
    Lastscore[1] = -1;
E 28
I 28
	if (pgames || cgames) {
		mvprintw(SCORE_Y + 1, SCORE_X + 28, "Games: %3d", pgames);
		mvprintw(SCORE_Y + 7, SCORE_X + 28, "Games: %3d", cgames);
	}
	Lastscore[0] = -1;
	Lastscore[1] = -1;
E 28
E 4
}

/*
 * game:
D 3
 *	Play one game up to glimit points
E 3
I 3
 *	Play one game up to glimit points.  Actually, we only ASK the
 *	player what card to turn.  We do a random one, anyway.
E 3
 */
I 28
void
E 28
E 2
game()
{
D 2
	register  int		i, j;
E 2
I 2
D 28
	register int		i, j;
E 2
	BOOLEAN			flag;
	BOOLEAN			compcrib;
E 28
I 28
	register int i, j;
	BOOLEAN flag;
	BOOLEAN compcrib;
E 28

I 8
D 27
	makeboard();
I 16
	refresh();
E 27
E 16
E 8
D 2
	makedeck( deck );
	shuffle( deck );
	if( gamecount == 0 )  {
E 2
I 2
	makedeck(deck);
	shuffle(deck);
	if (gamecount == 0) {
E 2
D 28
	    flag = TRUE;
D 2
	    do  {
		if( rflag )  {				/* player cuts deck */
		    i = ( rand() >>4 ) % CARDS;		/* random cut */
E 2
I 2
	    do {
D 3
		if (rflag)				/* player cuts deck */
		    i = (rand() >> 4) % CARDS;		/* random cut */
		else {
E 3
I 3
		if (!rflag) {				/* player cuts deck */
E 3
		    msg(quiet ? "Cut for crib? " :
			"Cut to see whose crib it is -- low card wins? ");
D 3
		    i = number(0, CARDS - 1);
E 3
I 3
		    getline();
E 3
E 2
		}
I 3
		i = (rand() >> 4) % CARDS;		/* random cut */
E 3
D 2
		else  {
		    printf( quiet ? "\nCut for crib? " :
			"\nCut to see whose crib it is -- low card wins? " );
		    i = number( 0, CARDS - 1 );
		}
		do  {					/* comp cuts deck */
		    j = ( rand() >> 4 ) % CARDS;
		}  while( j == i );
		printf( quiet ? "You cut " : "You cut the " );
		printcard( deck[i], FALSE );
		printf( quiet ? ", I cut " : ",  I cut the " );
		printcard( deck[j], FALSE );
		printf( ".\n" );
		flag = ( deck[i].rank == deck[j].rank );
		if( flag )  {
		    printf( quiet ? "We tied...\n" :
				"We tied and have to try again...\n" );
		    shuffle( deck );
E 2
I 2
		do {					/* comp cuts deck */
		    j = (rand() >> 4) % CARDS;
		} while (j == i);
		addmsg(quiet ? "You cut " : "You cut the ");
		msgcard(deck[i], FALSE);
		endmsg();
		addmsg(quiet ? "I cut " : "I cut the ");
		msgcard(deck[j], FALSE);
		endmsg();
		flag = (deck[i].rank == deck[j].rank);
		if (flag) {
		    msg(quiet ? "We tied..." :
			"We tied and have to try again...");
		    shuffle(deck);
E 2
		    continue;
		}
D 2
		else  {
		    compcrib = deck[i].rank > deck[j].rank;
		}
	    }  while( flag );
E 2
I 2
		else
		    compcrib = (deck[i].rank > deck[j].rank);
	    } while (flag);
I 27
	    clear();
	    makeboard();
	    refresh();
E 28
I 28
		flag = TRUE;
		do {
			if (!rflag) {			/* player cuts deck */
				msg(quiet ? "Cut for crib? " :
			    "Cut to see whose crib it is -- low card wins? ");
				getline();
			}
			i = (rand() >> 4) % CARDS;	/* random cut */
			do {	/* comp cuts deck */
				j = (rand() >> 4) % CARDS;
			} while (j == i);
			addmsg(quiet ? "You cut " : "You cut the ");
			msgcard(deck[i], FALSE);
			endmsg();
			addmsg(quiet ? "I cut " : "I cut the ");
			msgcard(deck[j], FALSE);
			endmsg();
			flag = (deck[i].rank == deck[j].rank);
			if (flag) {
				msg(quiet ? "We tied..." :
				    "We tied and have to try again...");
				shuffle(deck);
				continue;
			} else
				compcrib = (deck[i].rank > deck[j].rank);
		} while (flag);
		clear();
		makeboard();
		refresh();
	} else {
		werase(Tablewin);
		wrefresh(Tablewin);
		werase(Compwin);
		wrefresh(Compwin);
		msg("Loser (%s) gets first crib", (iwon ? "you" : "me"));
		compcrib = !iwon;
E 28
E 27
E 2
	}
D 2
	else  {
	    printf( "Loser (%s) gets first crib.\n",  (iwon ? "you" : "me") );
E 2
I 2
D 28
	else {
I 8
	    werase(Tablewin);
	    wrefresh(Tablewin);
	    werase(Compwin);
	    wrefresh(Compwin);
E 8
D 17
	    msg("Loser (%s) gets first crib.",  (iwon ? "you" : "me"));
E 17
I 17
	    msg("Loser (%s) gets first crib",  (iwon ? "you" : "me"));
E 17
E 2
	    compcrib = !iwon;
	}
E 28
I 2

E 2
	pscore = cscore = 0;
	flag = TRUE;
D 2
	do  {
	    shuffle( deck );
	    flag = !playhand( compcrib );
E 2
I 2
	do {
D 28
	    shuffle(deck);
	    flag = !playhand(compcrib);
E 2
	    compcrib = !compcrib;
E 28
I 28
		shuffle(deck);
		flag = !playhand(compcrib);
		compcrib = !compcrib;
E 28
D 2
	    printf( "\nYou have %d points, I have %d.\n", pscore, cscore );
	}  while( flag );
E 2
I 2
D 14
	    msg("You have %d points, I have %d.", pscore, cscore);
E 14
	} while (flag);
E 2
	++gamecount;
D 2
	if(  cscore < pscore  )  {
	    if(  glimit - cscore > 30  )  {
		if(  glimit - cscore > 60  )  {
		    printf( "\nYOU DOUBLE SKUNKED ME!\n\n" );
		    pgames += 4;
		}
		else  {
		    printf( "\nYOU SKUNKED ME!\n\n" );
		    pgames += 2;
		}
E 2
I 2
	if (cscore < pscore) {
D 28
	    if (glimit - cscore > 60) {
		msg("YOU DOUBLE SKUNKED ME!");
		pgames += 4;
E 2
	    }
D 2
	    else  {
		printf( "\nYOU WON!\n\n" );
E 2
I 2
	    else if (glimit - cscore > 30) {
		msg("YOU SKUNKED ME!");
		pgames += 2;
	    }
	    else {
		msg("YOU WON!");
E 2
		++pgames;
	    }
	    iwon = FALSE;
E 28
I 28
		if (glimit - cscore > 60) {
			msg("YOU DOUBLE SKUNKED ME!");
			pgames += 4;
		} else
			if (glimit - cscore > 30) {
				msg("YOU SKUNKED ME!");
				pgames += 2;
			} else {
				msg("YOU WON!");
				++pgames;
			}
		iwon = FALSE;
	} else {
		if (glimit - pscore > 60) {
			msg("I DOUBLE SKUNKED YOU!");
			cgames += 4;
		} else
			if (glimit - pscore > 30) {
				msg("I SKUNKED YOU!");
				cgames += 2;
			} else {
				msg("I WON!");
				++cgames;
			}
		iwon = TRUE;
E 28
	}
D 2
	else  {
	    if(  glimit - pscore > 30  )  {
		if(  glimit - pscore > 60  )  {
		    printf( "\nI DOUBLE SKUNKED YOU!\n\n" );
		    cgames += 4;
		}
		else  {
		    printf( "\nI SKUNKED YOU!\n\n" );
		    cgames += 2;
		}
E 2
I 2
D 28
	else {
	    if (glimit - pscore > 60) {
		msg("I DOUBLE SKUNKED YOU!");
		cgames += 4;
E 2
	    }
D 2
	    else  {
		printf( "\nI WON!\n\n" );
E 2
I 2
	    else if (glimit - pscore > 30) {
		msg("I SKUNKED YOU!");
		cgames += 2;
	    }
	    else {
		msg("I WON!");
E 2
		++cgames;
	    }
	    iwon = TRUE;
	}
E 28
D 2
	printf( "\nI have won %d games, you have won %d\n", cgames, pgames );
E 2
I 2
D 8
	msg("I have won %d games, you have won %d", cgames, pgames);
E 8
I 8
	gamescore();
E 8
E 2
}

D 2


E 2
/*
D 2
 * hand does up one hand of the game
E 2
I 2
 * playhand:
 *	Do up one hand of the game
E 2
 */
I 28
int
E 28
D 2

playhand( mycrib )

    BOOLEAN		mycrib;
E 2
I 2
playhand(mycrib)
D 28
BOOLEAN		mycrib;
E 28
I 28
	BOOLEAN mycrib;
E 28
E 2
{
D 2
	register  int			deckpos;
E 2
I 2
D 28
	register int		deckpos;
	extern char		Msgbuf[];
E 28
I 28
	register int deckpos;
E 28
E 2

I 2
	werase(Compwin);
D 16
	wrefresh(Compwin);
D 15
	move(CRIB_Y, 0);
E 15
I 15
	move(CRIB_Y, SCORE_SZ);
E 15
	clrtobot();
	mvaddstr(LINES - 1, 0, Msgbuf);
E 16

E 2
	knownum = 0;
D 2
	deckpos = deal( mycrib );
	sorthand( chand, FULLHAND );
	sorthand( phand, FULLHAND );
	makeknown( chand, FULLHAND );
	printf( "\nYour hand is: " );
	prhand( phand, FULLHAND, TRUE );
	printf( ".\n" );
	discard( mycrib );
	if(  cut( mycrib, deckpos )  )  return( TRUE );
	if(  peg( mycrib )  )  return( TRUE );
	if(  score( mycrib )  )  return( TRUE );
	return( FALSE );
E 2
I 2
	deckpos = deal(mycrib);
	sorthand(chand, FULLHAND);
	sorthand(phand, FULLHAND);
	makeknown(chand, FULLHAND);
D 12
	prhand(phand, FULLHAND, Playwin);
E 12
I 12
	prhand(phand, FULLHAND, Playwin, FALSE);
E 12
	discard(mycrib);
	if (cut(mycrib, deckpos))
D 28
	    return TRUE;
E 28
I 28
		return TRUE;
E 28
	if (peg(mycrib))
D 28
	    return TRUE;
E 28
I 28
		return TRUE;
E 28
	werase(Tablewin);
	wrefresh(Tablewin);
	if (score(mycrib))
D 28
	    return TRUE;
E 28
I 28
		return TRUE;
E 28
	return FALSE;
E 2
}

D 28


E 28
/*
 * deal cards to both players from deck
 */
D 28

deal( mycrib )
E 28
I 28
int
deal(mycrib)
	BOOLEAN mycrib;
E 28
{
D 28
	register  int		i, j;
E 28
I 28
	register int i, j;
E 28

D 28
	j = 0;
	for( i = 0; i < FULLHAND; i++ )  {
	    if( mycrib )  {
		phand[i] = deck[j++];
		chand[i] = deck[j++];
	    }
	    else  {
		chand[i] = deck[j++];
		phand[i] = deck[j++];
	    }
E 28
I 28
	for (i = j = 0; i < FULLHAND; i++) {
		if (mycrib) {
			phand[i] = deck[j++];
			chand[i] = deck[j++];
		} else {
			chand[i] = deck[j++];
			phand[i] = deck[j++];
		}
E 28
	}
D 28
	return( j );
E 28
I 28
	return (j);
E 28
}

D 2


E 2
/*
D 2
 * handle players discarding into the crib...
 * note: we call cdiscard() after prining first message so player doesn't wait
E 2
I 2
 * discard:
 *	Handle players discarding into the crib...
 * Note: we call cdiscard() after prining first message so player doesn't wait
E 2
 */
I 28
void
E 28
D 2

discard( mycrib )

    BOOLEAN		mycrib;
E 2
I 2
discard(mycrib)
D 28
BOOLEAN		mycrib;
E 28
I 28
	BOOLEAN mycrib;
E 28
E 2
{
I 2
D 28
	register char	*prompt;
	CARD		crd;
E 28
I 28
	register char *prompt;
	CARD crd;
E 28
E 2

D 2
	CARD			crd;

	printf( "It's %s crib...\n", (mycrib ? "my" : "your") );
	printf( quiet ? "Discard --> " : "Discard a card --> " );
	cdiscard( mycrib );			/* puts best discard at end */
	crd = phand[ infrom(phand, FULLHAND) ];
	remove( crd, phand, FULLHAND);
E 2
I 2
D 5
	msg("It's %s crib...", (mycrib ? "my" : "your"));
E 5
I 5
	prcrib(mycrib, TRUE);
E 5
	prompt = (quiet ? "Discard --> " : "Discard a card --> ");
D 6
	msg(prompt);
E 6
D 28
	cdiscard(mycrib);			/* puts best discard at end */
E 28
I 28
	cdiscard(mycrib);	/* puts best discard at end */
E 28
	crd = phand[infrom(phand, FULLHAND, prompt)];
D 26
	remove(crd, phand, FULLHAND);
E 26
I 26
	cremove(crd, phand, FULLHAND);
E 26
D 12
	prhand(phand, FULLHAND, Playwin);
E 12
I 12
	prhand(phand, FULLHAND, Playwin, FALSE);
E 12
E 2
	crib[0] = crd;
D 2
    /* next four lines same as last four except for cdiscard() */
	printf( quiet ? "Discard --> " : "Discard a card --> " );
	crd = phand[ infrom(phand, FULLHAND - 1) ];
	remove( crd, phand, FULLHAND - 1 );
E 2
I 2
D 28
/* next four lines same as last four except for cdiscard() */
E 28
I 28

	/* Next four lines same as last four except for cdiscard(). */
E 28
D 6
	msg(prompt);
E 6
	crd = phand[infrom(phand, FULLHAND - 1, prompt)];
D 26
	remove(crd, phand, FULLHAND - 1);
E 26
I 26
	cremove(crd, phand, FULLHAND - 1);
E 26
D 12
	prhand(phand, FULLHAND, Playwin);
E 12
I 12
	prhand(phand, FULLHAND, Playwin, FALSE);
E 12
E 2
	crib[1] = crd;
	crib[2] = chand[4];
	crib[3] = chand[5];
D 2
	chand[4].rank = chand[4].suit = chand[5].rank = chand[5].suit = -1;
E 2
I 2
	chand[4].rank = chand[4].suit = chand[5].rank = chand[5].suit = EMPTY;
E 2
}

D 2


E 2
/*
D 2
 * cut the deck and set turnover
E 2
I 2
 * cut:
D 3
 *	Cut the deck and set turnover
E 3
I 3
 *	Cut the deck and set turnover.  Actually, we only ASK the
 *	player what card to turn.  We do a random one, anyway.
E 3
E 2
 */
I 28
int
E 28
D 2

cut( mycrib, pos )

    BOOLEAN		mycrib;
    int			pos;
E 2
I 2
cut(mycrib, pos)
D 28
BOOLEAN		mycrib;
int		pos;
E 28
I 28
	BOOLEAN mycrib;
	int  pos;
E 28
E 2
{
D 2
	register  int		i;
E 2
I 2
D 28
	register int		i, cardx;
E 2
	BOOLEAN			win = FALSE;
E 28
I 28
	register int i;
	BOOLEAN win;
E 28

I 28
	win = FALSE;
E 28
D 2
	if( mycrib )  {
	    if( rflag )  {			/* random cut */
		i = ( rand() >> 4 ) % (CARDS - pos);
E 2
I 2
	if (mycrib) {
D 3
	    if (rflag)				/* random cut */
		i = (rand() >> 4) % (CARDS - pos);
	    else {
E 3
I 3
D 28
	    if (!rflag) {			/* random cut */
E 3
		msg(quiet ? "Cut the deck? " :
			"How many cards down do you wish to cut the deck? ");
D 3
		i = number(0, CARDS - pos - 1);
E 3
I 3
		getline();
E 3
E 2
	    }
I 3
	    i = (rand() >> 4) % (CARDS - pos);
E 3
D 2
	    else  {
		printf( quiet ? "Cut the deck? " :
			"How many cards down do you wish to cut the deck? " );
		i = number( 0, CARDS - pos - 1 );
	    }
E 2
	    turnover = deck[i + pos];
D 2
	    printf( quiet ? "You cut " : "You cut the " );
	    printcard( turnover, FALSE );
	    printf( ".\n" );
	    if(  turnover.rank == JACK  )  {
		printf( "I get two for his heels.\n" );
		win = chkscr( &cscore, 2 );
E 2
I 2
	    addmsg(quiet ? "You cut " : "You cut the ");
	    msgcard(turnover, FALSE);
	    endmsg();
	    if (turnover.rank == JACK) {
D 17
		msg("I get two for his heels.");
E 17
I 17
		msg("I get two for his heels");
E 17
		win = chkscr(&cscore,2 );
E 2
	    }
E 28
I 28
		if (!rflag) {	/* random cut */
			msg(quiet ? "Cut the deck? " :
		    "How many cards down do you wish to cut the deck? ");
			getline();
		}
		i = (rand() >> 4) % (CARDS - pos);
		turnover = deck[i + pos];
		addmsg(quiet ? "You cut " : "You cut the ");
		msgcard(turnover, FALSE);
		endmsg();
		if (turnover.rank == JACK) {
			msg("I get two for his heels");
			win = chkscr(&cscore, 2);
		}
	} else {
		i = (rand() >> 4) % (CARDS - pos) + pos;
		turnover = deck[i];
		addmsg(quiet ? "I cut " : "I cut the ");
		msgcard(turnover, FALSE);
		endmsg();
		if (turnover.rank == JACK) {
			msg("You get two for his heels");
			win = chkscr(&pscore, 2);
		}
E 28
I 2
D 5
	    cardx = CRIB_X;
E 5
E 2
	}
D 2
	else  {
	    i = ( rand() >> 4 ) % (CARDS - pos)  +  pos;
E 2
I 2
D 28
	else {
	    i = (rand() >> 4) % (CARDS - pos) + pos;
E 2
	    turnover = deck[i];
D 2
	    printf( quiet ? "I cut " : "I cut the " );
	    printcard( turnover, FALSE );
	    printf( ".\n" );
	    if(  turnover.rank == JACK  )  {
		printf( "You get two for his heels.\n" );
		win = chkscr( &pscore, 2 );
E 2
I 2
	    addmsg(quiet ? "I cut " : "I cut the ");
	    msgcard(turnover, FALSE);
	    endmsg();
	    if (turnover.rank == JACK) {
D 17
		msg("You get two for his heels.");
E 17
I 17
		msg("You get two for his heels");
E 17
		win = chkscr(&pscore, 2);
E 2
	    }
I 2
D 5
	    cardx = 0;
E 5
E 2
	}
E 28
D 2
	makeknown( &turnover, 1 );
	return( win );
E 2
I 2
	makeknown(&turnover, 1);
D 5
	mvaddstr(CRIB_Y, cardx + 1, "CRIB");
	prcard(stdscr, CRIB_Y + 1, cardx, turnover);
E 5
I 5
	prcrib(mycrib, FALSE);
E 5
D 28
	return win;
E 28
I 28
	return (win);
E 28
I 5
}

/*
 * prcrib:
 *	Print out the turnover card with crib indicator
 */
I 28
void
E 28
prcrib(mycrib, blank)
D 28
BOOLEAN		mycrib, blank;
E 28
I 28
	BOOLEAN mycrib, blank;
E 28
{
D 16
	register int	cardx;
E 16
I 16
D 28
	register int	y, cardx;
E 28
I 28
	register int y, cardx;
E 28
E 16

	if (mycrib)
D 28
	    cardx = CRIB_X;
E 28
I 28
		cardx = CRIB_X;
E 28
	else
D 15
	    cardx = 0;
E 15
I 15
D 16
	    cardx = SCORE_SZ;
E 16
I 16
D 17
	    cardx = X_SCORE_SZ;
E 17
I 17
D 28
	    cardx = 0;
E 28
I 28
		cardx = 0;
E 28
E 17
E 16
E 15

	mvaddstr(CRIB_Y, cardx + 1, "CRIB");
	prcard(stdscr, CRIB_Y + 1, cardx, turnover, blank);
I 16

	if (mycrib)
D 17
	    cardx = X_SCORE_SZ;
E 17
I 17
D 28
	    cardx = 0;
E 28
I 28
		cardx = 0;
E 28
E 17
	else
D 28
	    cardx = CRIB_X;
E 28
I 28
		cardx = CRIB_X;
E 28

	for (y = CRIB_Y; y <= CRIB_Y + 5; y++)
D 28
	    mvaddstr(y, cardx, "       ");
E 28
I 28
		mvaddstr(y, cardx, "       ");
E 28
E 16
E 5
E 2
}

D 2


E 2
/*
D 2
 * handle all the pegging...
E 2
I 2
 * peg:
 *	Handle all the pegging...
E 2
 */
I 28
static CARD Table[14];
static int Tcnt;
E 28

D 2
peg( mycrib )
E 2
I 2
D 28
static CARD		Table[14];
E 2

D 2
    BOOLEAN		mycrib;
E 2
I 2
static int		Tcnt;

E 28
I 28
int
E 28
peg(mycrib)
D 28
BOOLEAN		mycrib;
E 28
I 28
	BOOLEAN mycrib;
E 28
E 2
{
D 2
	static  CARD		ch[ CINHAND ],  ph[ CINHAND ];
	static  CARD		table[ 14 ];
E 2
I 2
D 28
	static CARD		ch[CINHAND], ph[CINHAND];
E 2
	CARD			crd;
D 2
	register  int		i, j, k;
E 2
I 2
	register int		i, j, k;
E 2
D 11
	int			l;
D 2
	int			cnum, pnum, tcnt, sum;
E 2
I 2
	int			cnum, pnum, sum;
E 2
	BOOLEAN			myturn, mego, ugo, last, played;
E 11
I 11
	register int		l;
	register int		cnum, pnum, sum;
	register BOOLEAN	myturn, mego, ugo, last, played;
E 28
I 28
	static CARD ch[CINHAND], ph[CINHAND];
	register int i, j, k;
	register int l;
	register int cnum, pnum, sum;
	register BOOLEAN myturn, mego, ugo, last, played;
	CARD crd;
E 28
E 11

	cnum = pnum = CINHAND;
D 2
	for( i = 0; i < CINHAND; i++ )  {	/* make copies of hands */
E 2
I 2
D 28
	for (i = 0; i < CINHAND; i++) {		/* make copies of hands */
E 2
	    ch[i] = chand[i];
	    ph[i] = phand[i];
E 28
I 28
	for (i = 0; i < CINHAND; i++) {	/* make copies of hands */
		ch[i] = chand[i];
		ph[i] = phand[i];
E 28
	}
D 2
	tcnt = 0;			/* index to table of cards played */
E 2
I 2
D 28
	Tcnt = 0;			/* index to table of cards played */
E 2
	sum = 0;			/* sum of cards played */
E 28
I 28
	Tcnt = 0;		/* index to table of cards played */
	sum = 0;		/* sum of cards played */
E 28
	mego = ugo = FALSE;
	myturn = !mycrib;
D 2
	do  {
E 2
I 2
	for (;;) {
E 2
D 28
	    last = TRUE;				/* enable last flag */
D 2
	    if(  myturn  )  {				/* my tyrn to play */
		if(  !anymove( ch, cnum, sum )  )  {	/* if no card to play */
		    if(  !mego  &&  cnum  )  {		/* go for comp? */
			printf( "GO.\n" );
E 2
I 2
D 11
	    prtable(sum);
E 11
D 12
	    prhand(ph, pnum, Playwin);
E 12
I 12
	    prhand(ph, pnum, Playwin, FALSE);
	    prhand(ch, cnum, Compwin, TRUE);
E 12
I 11
	    prtable(sum);
E 11
	    if (myturn) {				/* my tyrn to play */
		if (!anymove(ch, cnum, sum)) {		/* if no card to play */
		    if (!mego && cnum) {		/* go for comp? */
D 17
			msg("GO.");
E 17
I 17
			msg("GO");
E 17
E 2
			mego = TRUE;
		    }
D 2
		    if(  anymove( ph, pnum, sum )  )  {	/* can player move? */
E 2
I 2
		    if (anymove(ph, pnum, sum))		/* can player move? */
E 2
			myturn = !myturn;
D 2
		    }
		    else  {				/* give him his point */
			printf( quiet ? "You get one.\n" :
					"You get one point.\n" );
			if(  chkscr( &pscore, 1 )  )  return( TRUE );
E 2
I 2
		    else {				/* give him his point */
D 17
			msg(quiet ? "You get one." : "You get one point.");
E 17
I 17
			msg(quiet ? "You get one" : "You get one point");
E 17
			if (chkscr(&pscore, 1))
			    return TRUE;
E 2
			sum = 0;
			mego = ugo = FALSE;
D 2
			tcnt = 0;
E 2
I 2
			Tcnt = 0;
D 16
			Hasread = FALSE;
E 16
E 2
		    }
		}
D 2
		else  {
E 2
I 2
		else {
E 2
		    played = TRUE;
		    j = -1;
		    k = 0;
D 2
		    for( i = 0; i < cnum; i++ )  {	/* maximize score */
			l = pegscore( ch[i], table, tcnt, sum );
			if(  l > k  )  {
E 2
I 2
		    for (i = 0; i < cnum; i++) {	/* maximize score */
			l = pegscore(ch[i], Table, Tcnt, sum);
			if (l > k) {
E 2
			    k = l;
			    j = i;
E 28
I 28
		last = TRUE;	/* enable last flag */
		prhand(ph, pnum, Playwin, FALSE);
		prhand(ch, cnum, Compwin, TRUE);
		prtable(sum);
		if (myturn) {	/* my tyrn to play */
			if (!anymove(ch, cnum, sum)) {	/* if no card to play */
				if (!mego && cnum) {	/* go for comp? */
					msg("GO");
					mego = TRUE;
				}
							/* can player move? */
				if (anymove(ph, pnum, sum))
					myturn = !myturn;
				else {			/* give him his point */
					msg(quiet ? "You get one" :
					    "You get one point");
					if (chkscr(&pscore, 1))
						return TRUE;
					sum = 0;
					mego = ugo = FALSE;
					Tcnt = 0;
				}
			} else {
				played = TRUE;
				j = -1;
				k = 0;
							/* maximize score */
				for (i = 0; i < cnum; i++) {
					l = pegscore(ch[i], Table, Tcnt, sum);
					if (l > k) {
						k = l;
						j = i;
					}
				}
				if (j < 0)		/* if nothing scores */
					j = cchose(ch, cnum, sum);
				crd = ch[j];
				cremove(crd, ch, cnum--);
				sum += VAL(crd.rank);
				Table[Tcnt++] = crd;
				if (k > 0) {
					addmsg(quiet ? "I get %d playing " :
					    "I get %d points playing ", k);
					msgcard(crd, FALSE);
					endmsg();
					if (chkscr(&cscore, k))
						return TRUE;
				}
				myturn = !myturn;
E 28
			}
D 28
		    }
D 2
		    if(  j < 0  )  {			/* if nothing scores */
			j = cchose( ch, cnum, sum );
		    }
E 2
I 2
		    if (j < 0)				/* if nothing scores */
			j = cchose(ch, cnum, sum);
E 2
		    crd = ch[j];
D 2
		    printf( quiet ? "I play " : "I play the " );
		    printcard( crd, FALSE );
		    remove( crd, ch, cnum-- );
		    sum += VAL( crd.rank );
		    table[ tcnt++ ] = crd;
		    printf( ".  Total is %d", sum );
		    if( k > 0 )  {
			printf( quiet ? ".  I got %d" :
						".  I got %d points", k );
			if(  chkscr( &cscore, k )  )  return( TRUE );
E 2
I 2
D 26
		    remove(crd, ch, cnum--);
E 26
I 26
		    cremove(crd, ch, cnum--);
E 26
		    sum += VAL(crd.rank);
		    Table[Tcnt++] = crd;
		    if (k > 0) {
D 7
			addmsg(quiet ? "I get %d playing " : "I get %d points playing ", k);
E 7
I 7
			addmsg(quiet ? "I get %d playing " :
			    "I get %d points playing ", k);
E 7
			msgcard(crd, FALSE);
			endmsg();
			if (chkscr(&cscore, k))
			    return TRUE;
E 2
		    }
D 2
		    printf( ".\n" );
E 2
		    myturn = !myturn;
E 28
I 28
		} else {
			if (!anymove(ph, pnum, sum)) {	/* can player move? */
				if (!ugo && pnum) {	/* go for player */
					msg("You have a GO");
					ugo = TRUE;
				}
							/* can computer play? */
				if (anymove(ch, cnum, sum))
					myturn = !myturn;
				else {
					msg(quiet ? "I get one" :
					    "I get one point");
					do_wait();
					if (chkscr(&cscore, 1))
						return TRUE;
					sum = 0;
					mego = ugo = FALSE;
					Tcnt = 0;
				}
			} else {			/* player plays */
				played = FALSE;
				if (pnum == 1) {
					crd = ph[0];
					msg("You play your last card");
				} else
					for (;;) {
						prhand(ph,
						    pnum, Playwin, FALSE);
						crd = ph[infrom(ph,
						    pnum, "Your play: ")];
						if (sum + VAL(crd.rank) <= 31)
							break;
						else
					msg("Total > 31 -- try again");
					}
				makeknown(&crd, 1);
				cremove(crd, ph, pnum--);
				i = pegscore(crd, Table, Tcnt, sum);
				sum += VAL(crd.rank);
				Table[Tcnt++] = crd;
				if (i > 0) {
					msg(quiet ? "You got %d" :
					    "You got %d points", i);
					if (chkscr(&pscore, i))
						return TRUE;
				}
				myturn = !myturn;
			}
E 28
		}
D 28
	    }
D 2
	    else  {
		if(  !anymove( ph, pnum, sum )  )  {	/* can player move? */
		    if(  !ugo  &&  pnum  )  {		/* go for player */
			printf( "You have a GO.\n" );
E 2
I 2
	    else {
		if (!anymove(ph, pnum, sum)) {		/* can player move? */
		    if (!ugo && pnum) {			/* go for player */
D 17
			msg("You have a GO.");
E 17
I 17
			msg("You have a GO");
E 17
E 2
			ugo = TRUE;
		    }
D 2
		    if(  anymove( ch, cnum, sum )  )  {	/* can computer play? */
E 2
I 2
		    if (anymove(ch, cnum, sum))		/* can computer play? */
E 2
			myturn = !myturn;
D 2
		    }
		    else  {
			printf( quiet ? "I get one.\n" : "I get one point.\n" );
			if(  chkscr( &cscore, 1 )  )  return( TRUE );
E 2
I 2
		    else {
D 17
			msg(quiet ? "I get one." : "I get one point.");
E 17
I 17
			msg(quiet ? "I get one" : "I get one point");
			do_wait();
E 17
			if (chkscr(&cscore, 1))
			    return TRUE;
E 28
I 28
		if (sum >= 31) {
			if (!myturn)
				do_wait();
E 28
E 2
			sum = 0;
			mego = ugo = FALSE;
D 2
			tcnt = 0;
E 2
I 2
			Tcnt = 0;
D 16
			Hasread = FALSE;
E 16
E 2
D 28
		    }
E 28
I 28
			last = FALSE;			/* disable last flag */
E 28
		}
D 2
		else  {					/* player plays */
E 2
I 2
D 28
		else {					/* player plays */
E 2
		    played = FALSE;
D 2
		    if(  pnum == 1  )  {
E 2
I 2
		    if (pnum == 1) {
E 2
			crd = ph[0];
D 2
			printf( "You play your last card, the " );
			printcard( crd, TRUE );
			printf( ".  " );
E 2
I 2
			msg("You play your last card");
E 2
		    }
D 2
		    else  {
			do  {
			    printf( "Your play ( " );
			    prhand( ph, pnum, TRUE );
			    printf( " ): " );
			    crd = ph[ infrom(ph, pnum) ];
			    if(  sum + VAL( crd.rank )  <=  31  )  {
E 2
I 2
		    else
			for (;;) {
D 6
			    msg("Your play: ");
E 6
D 12
			    prhand(ph, pnum, Playwin);
E 12
I 12
			    prhand(ph, pnum, Playwin, FALSE);
E 12
			    crd = ph[infrom(ph, pnum, "Your play: ")];
			    if (sum + VAL(crd.rank) <= 31)
E 2
				break;
D 2
			    }
			    else  {
				printf( "Total > 31 -- try again.\n" );
			    }
			}  while( TRUE );
E 2
I 2
			    else
D 17
				msg("Total > 31 -- try again.");
E 17
I 17
				msg("Total > 31 -- try again");
E 17
			}
		    makeknown(&crd, 1);
D 26
		    remove(crd, ph, pnum--);
E 26
I 26
		    cremove(crd, ph, pnum--);
E 26
		    i = pegscore(crd, Table, Tcnt, sum);
		    sum += VAL(crd.rank);
		    Table[Tcnt++] = crd;
		    if (i > 0) {
			msg(quiet ? "You got %d" : "You got %d points", i);
			if (chkscr(&pscore, i))
			    return TRUE;
E 2
		    }
D 2
		    makeknown( &crd, 1 );
		    remove( crd, ph, pnum-- );
		    i = pegscore( crd, table, tcnt, sum );
		    sum += VAL( crd.rank );
		    table[ tcnt++ ] = crd;
		    printf( "Total is %d", sum );
		    if( i > 0 )  {
			printf( quiet ? ".  You got %d" :
						".  You got %d points", i );
			if(  chkscr( &pscore, i )  )  return( TRUE );
		    }
		    printf( ".\n" );
E 2
		    myturn = !myturn;
		}
	    }
D 2
	    if(  sum >= 31  )  {
E 2
I 2
	    if (sum >= 31) {
I 17
		if (!myturn)
		    do_wait();
E 17
E 2
		sum = 0;
		mego = ugo = FALSE;
D 2
		tcnt = 0;
E 2
I 2
		Tcnt = 0;
E 2
		last = FALSE;				/* disable last flag */
I 2
D 16
		Hasread = FALSE;
E 16
E 2
	    }
D 2
	    if(  !pnum  &&  !cnum  )  break;		/* both done */
	}  while( TRUE );
	if( last )  {
	    if( played )  {
		printf( quiet ? "I get one for last.\n" :
					"I get one point for last.\n" );
		if(  chkscr( &cscore, 1 )  )  return( TRUE );
E 2
I 2
	    if (!pnum && !cnum)
		break;					/* both done */
E 28
I 28
		if (!pnum && !cnum)
			break;				/* both done */
E 28
	}
I 11
D 12
	prhand(ph, pnum, Playwin);
E 12
I 12
	prhand(ph, pnum, Playwin, FALSE);
	prhand(ch, cnum, Compwin, TRUE);
E 12
	prtable(sum);
E 11
	if (last)
D 28
	    if (played) {
		msg(quiet ? "I get one for last" : "I get one point for last");
I 17
		do_wait();
E 17
		if (chkscr(&cscore, 1))
		    return TRUE;
E 2
	    }
D 2
	    else  {
		printf( quiet ? "You get one for last.\n" :
					"You get one point for last.\n" );
		if(  chkscr( &pscore, 1 )  )  return( TRUE );
E 2
I 2
	    else {
		msg(quiet ? "You get one for last" :
E 28
I 28
		if (played) {
			msg(quiet ? "I get one for last" :
			    "I get one point for last");
			do_wait();
			if (chkscr(&cscore, 1))
				return TRUE;
		} else {
			msg(quiet ? "You get one for last" :
E 28
			    "You get one point for last");
D 28
		if (chkscr(&pscore, 1))
		    return TRUE;
E 2
	    }
D 2
	}
	return( FALSE );
E 2
I 2
	return FALSE;
E 28
I 28
			if (chkscr(&pscore, 1))
				return TRUE;
		}
	return (FALSE);
E 28
E 2
}

D 2


E 2
/*
D 2
 * handle the scoring of the hands
E 2
I 2
 * prtable:
 *	Print out the table with the current score
E 2
 */
I 28
void
E 28
I 2
prtable(score)
D 28
int	score;
E 28
I 28
	int score;
E 28
{
D 12
	prhand(Table, Tcnt, Tablewin);
E 12
I 12
	prhand(Table, Tcnt, Tablewin, FALSE);
E 12
	mvwprintw(Tablewin, (Tcnt + 2) * 2, Tcnt + 1, "%2d", score);
	wrefresh(Tablewin);
}
E 2

D 2
score( mycrib )

    BOOLEAN		mycrib;
E 2
I 2
/*
 * score:
 *	Handle the scoring of the hands
 */
I 28
int
E 28
score(mycrib)
D 28
BOOLEAN		mycrib;
E 28
I 28
	BOOLEAN mycrib;
E 28
E 2
{
D 2
	if(  mycrib  )  {
	    if(  plyrhand( phand, "hand" )  )  return( TRUE );
	    if(  comphand( chand, "hand" )  )  return( TRUE );
	    if(  comphand( crib, "crib" )  )  return( TRUE );
E 2
I 2
	sorthand(crib, CINHAND);
	if (mycrib) {
D 28
	    if (plyrhand(phand, "hand"))
		return TRUE;
	    if (comphand(chand, "hand"))
		return TRUE;
I 17
	    do_wait();
E 17
	    if (comphand(crib, "crib"))
		return TRUE;
E 28
I 28
		if (plyrhand(phand, "hand"))
			return (TRUE);
		if (comphand(chand, "hand"))
			return (TRUE);
		do_wait();
		if (comphand(crib, "crib"))
			return (TRUE);
	} else {
		if (comphand(chand, "hand"))
			return (TRUE);
		if (plyrhand(phand, "hand"))
			return (TRUE);
		if (plyrhand(crib, "crib"))
			return (TRUE);
E 28
E 2
	}
D 2
	else  {
	    if(  comphand( chand, "hand" )  )  return( TRUE );
	    if(  plyrhand( phand, "hand" )  )  return( TRUE );
	    if(  plyrhand( crib, "crib" )  )  return( TRUE );
E 2
I 2
D 28
	else {
	    if (comphand(chand, "hand"))
		return TRUE;
	    if (plyrhand(phand, "hand"))
		return TRUE;
	    if (plyrhand(crib, "crib"))
		return TRUE;
E 2
	}
D 2
	return( FALSE );
E 2
I 2
	return FALSE;
E 28
I 28
	return (FALSE);
E 28
E 2
}
D 2

E 2
E 1
