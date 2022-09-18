h11521
s 00002/00002/00330
d D 8.1 93/05/31 16:49:43 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00180/00179/00152
d D 5.7 93/04/26 10:34:44 bostic 25 24
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00005/00005/00326
d D 5.6 91/02/28 13:09:02 bostic 24 23
c ANSI
e
s 00001/00011/00330
d D 5.5 90/06/01 13:06:06 bostic 23 22
c new copyright notice
e
s 00010/00005/00331
d D 5.4 88/06/18 14:39:36 bostic 22 21
c install approved copyright notice
e
s 00009/00003/00327
d D 5.3 88/03/10 16:31:56 bostic 21 20
c add Berkeley specific header, Ken Arnold says written @ Berkeley
e
s 00001/00001/00329
d D 5.2 87/10/22 11:30:42 bostic 20 19
c ANSI C; sprintf now returns an int.
e
s 00009/00001/00321
d D 5.1 85/05/30 19:46:11 mckusick 19 18
c Add copyright
e
s 00002/00002/00320
d D 1.14 83/09/06 12:54:36 arnold 18 17
c make scorehand know what really is a crib and how to deal with flushes
e
s 00002/00000/00320
d D 1.13 83/05/19 12:21:50 arnold 17 16
c add sccs keywords
e
s 00025/00025/00295
d D 1.12 83/05/07 14:16:34 arnold 16 15
c don't score 4-flush in player's crib
e
s 00002/00001/00318
d D 1.11 83/05/07 14:06:57 arnold 15 14
c add a scrolling region
e
s 00000/00001/00319
d D 1.10 83/05/01 15:31:05 arnold 14 12
c make a scrolling region for cribbage
e
s 00000/00000/00320
d R 1.10 83/05/01 13:26:14 arnold 13 12
c swap the board and the cards on the screen
e
s 00003/00001/00317
d D 1.9 83/03/03 21:56:55 arnold 12 9
c 
e
s 00014/00016/00302
d R 1.9 82/09/10 11:23:06 arnold 11 9
c if only one card in the hand is playable, just play it
e
s 00014/00016/00302
d R 1.9 82/09/09 16:24:28 arnold 10 9
c if only one card in the hand is playable, just play it.
e
s 00001/00000/00317
d D 1.8 82/09/09 15:32:37 arnold 9 8
c refresh() immediately after change scoreboard since it look nicer that way
e
s 00002/00002/00315
d D 1.7 82/09/06 14:59:14 arnold 8 7
c show back of computer's hand during play
e
s 00003/00003/00314
d D 1.6 82/08/31 23:01:20 arnold 7 5
c speed up scorehand() and fifteens()
e
s 00158/00159/00158
d R 1.6 82/08/28 17:06:47 arnold 6 5
c reformatting and obvious optimization
e
s 00022/00011/00295
d D 1.5 82/08/27 15:00:20 arnold 5 4
c print starting and ending peg positions
e
s 00001/00001/00305
d D 1.4 82/08/27 14:37:59 arnold 4 3
c test for scr being >= limit, not just >
e
s 00003/00002/00303
d D 1.3 82/08/27 14:23:43 arnold 3 2
c make simple <RETURN> not be the same as typing "0"
e
s 00079/00053/00226
d D 1.2 82/08/24 18:34:20 arnold 2 1
c first "working" visual version
e
s 00279/00000/00000
d D 1.1 82/08/11 16:36:06 arnold 1 0
c date and time created 82/08/11 16:36:06 by arnold
e
u
U
t
T
I 17
D 19
static char	*sccsid = "%W% (Berkeley) %G%";
E 19
I 19
D 25
/*
 * Copyright (c) 1980 Regents of the University of California.
E 25
I 25
/*-
D 26
 * Copyright (c) 1980 The Regents of the University of California.
E 25
D 21
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 21
I 21
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 22
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 22
I 22
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 22
E 21
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21
E 19

E 17
I 1
D 2

#include	<stdio.h>
E 2
I 2
D 25
#include	<curses.h>
E 2
#include	"deck.h"
#include	"cribbage.h"
I 2
#include	"cribcur.h"
E 25
I 25
#include <curses.h>
#include <string.h>
E 25
E 2

I 25
#include "deck.h"
#include "cribbage.h"
#include "cribcur.h"
E 25

D 25
#define		NTV		10		/* number scores to test */
E 25
I 25
#define	NTV	10		/* number scores to test */
E 25

/* score to test reachability of, and order to test them in */
D 25
int		tv[ NTV ]	= { 8, 7, 9, 6, 11, 12, 13, 14, 10, 5 };
E 25
I 25
int tv[NTV] = {8, 7, 9, 6, 11, 12, 13, 14, 10, 5};
E 25

D 25

E 25
/*
 * computer chooses what to play in pegging...
 * only called if no playable card will score points
 */
D 25

cchose( h, n, s )

    CARD		h[];
    int			n;
    int			s;
E 25
I 25
int
cchose(h, n, s)
	CARD h[];
	int n, s;
E 25
{
D 25
	register  int		i, j, l;
E 25
I 25
	register int i, j, l;
E 25

D 25
	if(  n <= 1  )  return( 0 );
	if(  s < 4  )  {		/* try for good value */
	    if(  ( j = anysumto(h, n, s, 4) )  >=  0  )  return( j );
	    if(  ( j = anysumto(h, n, s, 3) ) >= 0  &&  s == 0  )
								return( j );
E 25
I 25
	if (n <= 1)
		return (0);
	if (s < 4) {		/* try for good value */
		if ((j = anysumto(h, n, s, 4)) >= 0)
			return (j);
		if ((j = anysumto(h, n, s, 3)) >= 0 && s == 0)
			return (j);
E 25
	}
D 25
	if(  s > 0  &&  s < 20  )  {
	    for( i = 1; i <= 10; i++ )  {	/* try for retaliation to 31 */
		if(  ( j = anysumto(h, n, s, 21-i) )  >=  0  )  {
		    if(  ( l = numofval(h, n, i) )  >  0  )  {
			if(  l > 1  ||  VAL( h[j].rank ) != i  )  return( j );
		    }
E 25
I 25
	if (s > 0 && s < 20) {
				/* try for retaliation to 31 */
		for (i = 1; i <= 10; i++) {
			if ((j = anysumto(h, n, s, 21 - i)) >= 0) {
				if ((l = numofval(h, n, i)) > 0) {
					if (l > 1 || VAL(h[j].rank) != i)
						return (j);
				}
			}
E 25
		}
D 25
	    }
E 25
	}
D 25
	if(  s < 15  )  {
	    for( i = 0; i < NTV; i++ )  {	/* for retaliation after 15 */
		if(  ( j = anysumto(h, n, s, tv[i]) )  >=  0  )  {
		    if(  ( l = numofval(h, n, 15-tv[i]) )  >  0  )  {
			if(  l > 1  ||  VAL( h[j].rank ) != 15-tv[i]  )  return( j );
		    }
E 25
I 25
	if (s < 15) {
				/* for retaliation after 15 */
		for (i = 0; i < NTV; i++) {
			if ((j = anysumto(h, n, s, tv[i])) >= 0) {
				if ((l = numofval(h, n, 15 - tv[i])) > 0) {
					if (l > 1 ||
					    VAL(h[j].rank) != 15 - tv[i])
						return (j);
				}
			}
E 25
		}
D 25
	    }
E 25
	}
	j = -1;
D 25
	for( i = n - 1; i >= 0; --i )  {	/* remember: h is sorted */
	    l = s + VAL( h[i].rank );
	    if(  l > 31  )  continue;
	    if(  l != 5  &&  l != 10  &&  l != 21  )  {
		j = i;
		break;
	    }
E 25
I 25
				/* remember: h is sorted */
	for (i = n - 1; i >= 0; --i) {
		l = s + VAL(h[i].rank);
		if (l > 31)
			continue;
		if (l != 5 && l != 10 && l != 21) {
			j = i;
			break;
		}
E 25
	}
D 25
	if(  j >= 0  )  return( j );
	for( i = n - 1; i >= 0; --i )  {
	    l = s + VAL( h[i].rank );
	    if(  l > 31  )  continue;
	    if(  j < 0  )  j = i;
	    if(  l != 5  &&  l != 21  )  {
		j = i;
		break;
	    }
E 25
I 25
	if (j >= 0)
		return (j);
	for (i = n - 1; i >= 0; --i) {
		l = s + VAL(h[i].rank);
		if (l > 31)
			continue;
		if (j < 0)
			j = i;
		if (l != 5 && l != 21) {
			j = i;
			break;
		}
E 25
	}
D 25
	return( j );
E 25
I 25
	return (j);
E 25
}

D 25


E 25
/*
D 2
 * evaluate and score a player hand or crib
E 2
I 2
 * plyrhand:
 *	Evaluate and score a player hand or crib
E 2
 */
I 25
int
E 25
D 2

plyrhand( hand, s )

    CARD		hand[];
    char		*s;
E 2
I 2
plyrhand(hand, s)
D 25
CARD		hand[];
char		*s;
E 25
I 25
	CARD    hand[];
	char   *s;
E 25
E 2
{
D 2
	register  int		i, j;
E 2
I 2
D 16
	register int		i, j;
E 2
	BOOLEAN			win;
I 3
	static char		prompt[BUFSIZ];
E 16
I 16
D 25
    register int	i, j;
    register BOOLEAN	win;
    static char		prompt[BUFSIZ];
E 25
I 25
	static char prompt[BUFSIZ];
	register int i, j;
	register BOOLEAN win;
E 25
E 16
E 3

D 2
	printf( "Your %s is: ", s );
	prhand( hand, CINHAND, TRUE );
	printf( "  [" );
	printcard( turnover, TRUE );
	printf( "].   How many points? " );
	i = scorehand( hand, turnover, CINHAND, FALSE );	/* count */
	if(  ( j = number(0, 29) )  ==  19  )  j = 0;
	if(  i != j  )  {
	    if( i < j )  {
		win = chkscr( &pscore, i );
		printf( "It's really only %d points, I get %d.\n", i, 2 );
		if( !win )  win = chkscr( &cscore, 2 );
E 2
I 2
D 8
	prhand(hand, CINHAND, Playwin);
E 8
I 8
D 16
	prhand(hand, CINHAND, Playwin, FALSE);
E 8
D 3
	msg("Your %s scores ", s);
E 3
I 3
	sprintf(prompt, "Your %s scores ", s);
E 3
D 7
	i = scorehand(hand, turnover, CINHAND, FALSE);	/* count */
E 7
I 7
	i = scorehand(hand, turnover, CINHAND, FALSE, explain);	/* count */
E 7
D 3
	if ((j = number(0, 29)) == 19)
E 3
I 3
	if ((j = number(0, 29, prompt)) == 19)
E 3
	    j = 0;
	if (i != j) {
	    if (i < j) {
		win = chkscr(&pscore, i);
D 15
		msg("It's really only %d points, I get %d.", i, 2);
E 15
I 15
		msg("It's really only %d points; I get %d", i, 2);
E 15
		if (!win)
		    win = chkscr(&cscore, 2);
E 2
	    }
D 2
	    else  {
		win = chkscr( &pscore, j );
		printf( "You should have taken %d, not %d!\n", i, j );
E 2
I 2
	    else {
		win = chkscr(&pscore, j);
		msg("You should have taken %d, not %d!", i, j);
E 2
	    }
D 2
	    if( explain )  {
		printf( "Explanation: %s\n", expl );
	    }
E 2
I 2
	    if (explain)
		msg("Explanation: %s", expl);
I 15
	    do_wait();
E 15
E 2
	}
D 2
	else  {
	    win = chkscr( &pscore, i );
	}
	return(  win  );
E 2
I 2
	else
E 16
I 16
D 25
    prhand(hand, CINHAND, Playwin, FALSE);
D 20
    sprintf(prompt, "Your %s scores ", s);
E 20
I 20
    (void)sprintf(prompt, "Your %s scores ", s);
E 20
D 18
    i = scorehand(hand, turnover, CINHAND, strcmp(s, "crib"), explain);
E 18
I 18
    i = scorehand(hand, turnover, CINHAND, strcmp(s, "crib") == 0, explain);
E 18
    if ((j = number(0, 29, prompt)) == 19)
	j = 0;
    if (i != j) {
	if (i < j) {
E 16
	    win = chkscr(&pscore, i);
D 16
	return win;
E 16
I 16
	    msg("It's really only %d points; I get %d", i, 2);
	    if (!win)
		win = chkscr(&cscore, 2);
	}
	else {
	    win = chkscr(&pscore, j);
	    msg("You should have taken %d, not %d!", i, j);
	}
	if (explain)
	    msg("Explanation: %s", expl);
	do_wait();
    }
    else
	win = chkscr(&pscore, i);
    return win;
E 25
I 25
	prhand(hand, CINHAND, Playwin, FALSE);
	(void) sprintf(prompt, "Your %s scores ", s);
	i = scorehand(hand, turnover, CINHAND, strcmp(s, "crib") == 0, explain);
	if ((j = number(0, 29, prompt)) == 19)
		j = 0;
	if (i != j) {
		if (i < j) {
			win = chkscr(&pscore, i);
			msg("It's really only %d points; I get %d", i, 2);
			if (!win)
				win = chkscr(&cscore, 2);
		} else {
			win = chkscr(&pscore, j);
			msg("You should have taken %d, not %d!", i, j);
		}
		if (explain)
			msg("Explanation: %s", expl);
		do_wait();
	} else
		win = chkscr(&pscore, i);
	return (win);
E 25
E 16
E 2
}

I 2
/*
 * comphand:
 *	Handle scoring and displaying the computers hand
 */
I 25
int
E 25
comphand(h, s)
D 25
CARD		h[];
char		*s;
E 25
I 25
	CARD h[];
	char *s;
E 25
{
D 25
	register int		j;
E 25
I 25
	register int j;
E 25
E 2

I 2
D 7
	j = scorehand(h, turnover, CINHAND, FALSE);
E 7
I 7
D 18
	j = scorehand(h, turnover, CINHAND, FALSE, FALSE);
E 18
I 18
	j = scorehand(h, turnover, CINHAND, strcmp(s, "crib") == 0, FALSE);
E 18
E 7
D 8
	prhand(h, CINHAND, Compwin);
E 8
I 8
	prhand(h, CINHAND, Compwin, FALSE);
E 8
D 14
	Hasread = FALSE;
E 14
	msg("My %s scores %d", s, (j == 0 ? 19 : j));
D 25
	return chkscr(&cscore, j);
E 25
I 25
	return (chkscr(&cscore, j));
E 25
}
E 2

/*
D 2
 * handle scoring and displaying the computers hand
E 2
I 2
 * chkscr:
 *	Add inc to scr and test for > glimit, printing on the scoring
 *	board while we're at it.
E 2
 */
I 25
int Lastscore[2] = {-1, -1};
E 25

D 2
comphand( h, s )
E 2
I 2
D 5
int	Lastscore[2] = {0, 0};
E 5
I 5
D 25
int	Lastscore[2] = {-1, -1};
E 5
E 2

E 25
I 25
int
E 25
D 2
    CARD		h[];
    char		*s;
E 2
I 2
chkscr(scr, inc)
D 25
int		*scr, inc;
E 25
I 25
	int    *scr, inc;
E 25
E 2
{
D 2
	register  int		j;
E 2
I 2
D 25
	BOOLEAN		myturn;
E 25
I 25
	BOOLEAN myturn;
E 25
E 2

D 2
	j = scorehand( h, turnover, CINHAND, FALSE );
	printf( "My %s ( ", s );
	prhand( h, CINHAND, TRUE );
	printf( "  [" );
	printcard( turnover, TRUE );
	printf( "] ) scores %d.\n", (j == 0 ? 19 : j) );
	return(  chkscr( &cscore, j )  );
E 2
I 2
	myturn = (scr == &cscore);
	if (inc != 0) {
		prpeg(Lastscore[myturn], '.', myturn);
		Lastscore[myturn] = *scr;
I 5
		*scr += inc;
		prpeg(*scr, PEG, myturn);
I 9
		refresh();
E 9
E 5
	}
D 5
	*scr += inc;
	prpeg(*scr, PEG, myturn);
E 5
D 4
	return (*scr > glimit);
E 4
I 4
	return (*scr >= glimit);
E 4
E 2
}

D 2


E 2
/*
D 2
 * add inc to scr and test for > glimit
E 2
I 2
 * prpeg:
D 12
 *	put out the peg character on the score board
E 12
I 12
 *	Put out the peg character on the score board and put the
 *	score up on the board.
E 12
E 2
 */
I 25
void
E 25
D 2

chkscr( scr, inc )

    int			*scr, inc;
E 2
I 2
prpeg(score, peg, myturn)
D 25
register int	score;
char		peg;
BOOLEAN		myturn;
E 25
I 25
	register int score;
	int peg;
	BOOLEAN myturn;
E 25
E 2
{
D 2
	return(  ( (*scr += inc) >= glimit ? TRUE : FALSE )  );
}
E 2
I 2
D 25
	register int	y, x;
E 25
I 25
	register int y, x;
E 25
E 2

D 2

E 2
I 2
D 5
	if (score == 0 || score > glimit)
		return;
E 5
	if (!myturn)
		y = SCORE_Y + 2;
	else
		y = SCORE_Y + 5;
D 5
	x = (score - 1) % 30;
	if (score > 90 || (score > 30 && score <= 60)) {
		y++;
		x = 29 - x;
E 5
I 5

	if (score <= 0 || score >= glimit) {
		if (peg == '.')
			peg = ' ';
		if (score == 0)
			x = SCORE_X + 2;
		else {
			x = SCORE_X + 2;
			y++;
		}
E 5
D 25
	}
D 5
	x += x / 5;
	x += SCORE_X + 3;
E 5
I 5
	else {
E 25
I 25
	} else {
E 25
		x = (score - 1) % 30;
		if (score > 90 || (score > 30 && score <= 60)) {
			y++;
			x = 29 - x;
		}
		x += x / 5;
		x += SCORE_X + 3;
	}
E 5
	mvaddch(y, x, peg);
I 12
	mvprintw(SCORE_Y + (myturn ? 7 : 1), SCORE_X + 10, "%3d", score);
E 12
}
E 2

/*
 * cdiscard -- the computer figures out what is the best discard for
 * the crib and puts the best two cards at the end
 */
D 25

cdiscard( mycrib )

    BOOLEAN		mycrib;
E 25
I 25
void
cdiscard(mycrib)
	BOOLEAN mycrib;
E 25
{
D 25
	CARD			d[ CARDS ],  h[ FULLHAND ],  cb[ 2 ];
	register  int		i, j, k;
	int			nc, ns;
	long			sums[ 15 ];
	static  int		undo1[15]   = {0,0,0,0,0,1,1,1,1,2,2,2,3,3,4};
	static  int		undo2[15]   = {1,2,3,4,5,2,3,4,5,3,4,5,4,5,5};
E 25
I 25
	CARD    d[CARDS], h[FULLHAND], cb[2];
	register int i, j, k;
	int     nc, ns;
	long    sums[15];
	static int undo1[15] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
	static int undo2[15] = {1, 2, 3, 4, 5, 2, 3, 4, 5, 3, 4, 5, 4, 5, 5};
E 25

D 25
	makedeck( d );
E 25
I 25
	makedeck(d);
E 25
	nc = CARDS;
D 25
	for( i = 0; i < knownum; i++ )  {	/* get all other cards */
D 24
	    remove( known[i], d, nc-- );
E 24
I 24
	    cremove( known[i], d, nc-- );
E 25
I 25
	for (i = 0; i < knownum; i++) {	/* get all other cards */
		cremove(known[i], d, nc--);
E 25
E 24
	}
D 25
	for( i = 0; i < 15; i++ )  sums[i] = 0L;
E 25
I 25
	for (i = 0; i < 15; i++)
		sums[i] = 0L;
E 25
	ns = 0;
D 25
	for( i = 0; i < (FULLHAND - 1); i++ )  {
	    cb[0] = chand[i];
	    for( j = i + 1; j < FULLHAND; j++ )  {
		cb[1] = chand[j];
		for( k = 0; k < FULLHAND; k++ )  h[k] = chand[k];
D 24
		remove( chand[i], h, FULLHAND );
		remove( chand[j], h, FULLHAND - 1 );
E 24
I 24
		cremove( chand[i], h, FULLHAND );
		cremove( chand[j], h, FULLHAND - 1 );
E 24
		for( k = 0; k < nc; k++ )  {
D 7
		    sums[ns] += scorehand( h, d[k], CINHAND, TRUE );
E 7
I 7
		    sums[ns] += scorehand( h, d[k], CINHAND, TRUE, FALSE );
E 7
		    if( mycrib )  sums[ns] += adjust( cb, d[k] );
		    else	  sums[ns] -= adjust( cb, d[k] );
E 25
I 25
	for (i = 0; i < (FULLHAND - 1); i++) {
		cb[0] = chand[i];
		for (j = i + 1; j < FULLHAND; j++) {
			cb[1] = chand[j];
			for (k = 0; k < FULLHAND; k++)
				h[k] = chand[k];
			cremove(chand[i], h, FULLHAND);
			cremove(chand[j], h, FULLHAND - 1);
			for (k = 0; k < nc; k++) {
				sums[ns] +=
				    scorehand(h, d[k], CINHAND, TRUE, FALSE);
				if (mycrib)
					sums[ns] += adjust(cb, d[k]);
				else
					sums[ns] -= adjust(cb, d[k]);
			}
			++ns;
E 25
		}
D 25
		++ns;
	    }
E 25
	}
	j = 0;
D 25
	for( i = 1; i < 15; i++ )  if(  sums[i] > sums[j]  )  j = i;
	for( k = 0; k < FULLHAND; k++ )  h[k] = chand[k];
D 24
	remove( h[ undo1[j] ], chand, FULLHAND );
	remove( h[ undo2[j] ], chand, FULLHAND - 1 );
E 24
I 24
	cremove( h[ undo1[j] ], chand, FULLHAND );
	cremove( h[ undo2[j] ], chand, FULLHAND - 1 );
E 24
	chand[4] = h[ undo1[j] ];
	chand[5] = h[ undo2[j] ];
E 25
I 25
	for (i = 1; i < 15; i++)
		if (sums[i] > sums[j])
			j = i;
	for (k = 0; k < FULLHAND; k++)
		h[k] = chand[k];
	cremove(h[undo1[j]], chand, FULLHAND);
	cremove(h[undo2[j]], chand, FULLHAND - 1);
	chand[4] = h[undo1[j]];
	chand[5] = h[undo2[j]];
E 25
}

D 25


E 25
/*
 * returns true if some card in hand can be played without exceeding 31
 */
D 25

anymove( hand, n, sum )

    CARD		hand[];
    int			n;
    int			sum;
E 25
I 25
int
anymove(hand, n, sum)
	CARD hand[];
	int n, sum;
E 25
{
D 25
	register  int		i, j;
E 25
I 25
	register int i, j;
E 25

D 25
	if(  n < 1  )  return( FALSE );
E 25
I 25
	if (n < 1)
		return (FALSE);
E 25
	j = hand[0].rank;
D 25
	for( i = 1; i < n; i++ )  {
	    if(  hand[i].rank < j  )  j = hand[i].rank;
E 25
I 25
	for (i = 1; i < n; i++) {
		if (hand[i].rank < j)
			j = hand[i].rank;
E 25
	}
D 25
	return(  sum + VAL( j )  <=  31  );
E 25
I 25
	return (sum + VAL(j) <= 31);
E 25
}

D 25


E 25
/*
 * anysumto returns the index (0 <= i < n) of the card in hand that brings
 * the s up to t, or -1 if there is none
 */
D 25

anysumto( hand, n, s, t )

    CARD		hand[];
    int			n;
    int			s,  t;
E 25
I 25
int
anysumto(hand, n, s, t)
	CARD hand[];
	int n, s, t;
E 25
{
D 25
	register  int		i;
E 25
I 25
	register int i;
E 25

D 25
	for( i = 0; i < n; i++ )  {
	    if(  s + VAL( hand[i].rank )  ==  t  )  return( i );
E 25
I 25
	for (i = 0; i < n; i++) {
		if (s + VAL(hand[i].rank) == t)
			return (i);
E 25
	}
D 25
	return( -1 );
E 25
I 25
	return (-1);
E 25
}

D 25



E 25
/*
 * return the number of cards in h having the given rank value
 */
D 25

numofval( h, n, v )

    CARD		h[];
    int			n;
    int			v;
E 25
I 25
int
numofval(h, n, v)
	CARD h[];
	int n, v;
E 25
{
D 25
	register  int		i, j;
E 25
I 25
	register int i, j;
E 25

	j = 0;
D 25
	for( i = 0; i < n; i++ )  {
	    if(  VAL( h[i].rank )  ==  v  )  ++j;
E 25
I 25
	for (i = 0; i < n; i++) {
		if (VAL(h[i].rank) == v)
			++j;
E 25
	}
D 25
	return( j );
E 25
I 25
	return (j);
E 25
}

D 25


E 25
/*
 * makeknown remembers all n cards in h for future recall
 */
D 25

makeknown( h, n )

    CARD		h[];
    int			n;
E 25
I 25
void
makeknown(h, n)
	CARD h[];
	int n;
E 25
{
D 25
	register  int		i;
E 25
I 25
	register int i;
E 25

D 25
	for( i = 0; i < n; i++ )  {
	    known[ knownum++ ] = h[i];
	}
E 25
I 25
	for (i = 0; i < n; i++)
		known[knownum++] = h[i];
E 25
}
D 25

E 25
E 1
