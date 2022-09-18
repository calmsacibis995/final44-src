h19090
s 00002/00002/00596
d D 8.1 93/05/31 16:49:34 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00323/00339/00275
d D 5.13 93/04/26 10:34:38 bostic 28 27
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00003/00003/00611
d D 5.12 93/02/03 17:32:47 torek 27 26
c CTRL(X) => CTRL('X'), for sanity
e
s 00004/00002/00610
d D 5.11 93/02/03 17:28:48 torek 26 25
c more ANSI happiness for gcc2
e
s 00001/00000/00611
d D 5.10 92/08/31 10:11:03 elan 25 23
c Added termios.h
e
s 00001/00000/00611
d R 5.10 92/06/16 20:28:41 bostic 24 23
c curses.h can require termios.h, now
e
s 00024/00002/00587
d D 5.9 92/02/16 00:25:57 torek 23 22
c squeaky clean stdarg usage, for sparc gcc
e
s 00002/00002/00587
d D 5.8 91/02/28 13:09:01 bostic 22 21
c ANSI
e
s 00018/00009/00571
d D 5.7 91/02/04 23:25:46 bostic 21 20
c remove stdio dependencies; still doesn't work, but not stdio
e
s 00001/00011/00579
d D 5.6 90/06/01 13:05:48 bostic 20 19
c new copyright notice
e
s 00010/00003/00580
d D 5.5 90/05/01 21:04:50 bostic 19 18
c move into /var, /usr/games
e
s 00010/00005/00573
d D 5.4 88/06/18 14:39:30 bostic 18 17
c install approved copyright notice
e
s 00009/00003/00569
d D 5.3 88/03/10 16:31:51 bostic 17 16
c add Berkeley specific header, Ken Arnold says written @ Berkeley
e
s 00002/00002/00570
d D 5.2 87/10/07 07:49:00 bostic 16 15
c erasechar/killchar already defined in curses.h
e
s 00009/00001/00563
d D 5.1 85/05/30 19:45:14 mckusick 15 14
c Add copyright
e
s 00000/00001/00564
d D 1.13 83/09/26 21:44:43 karels 14 13
c no uncntl.h now
e
s 00015/00000/00550
d D 1.12 83/09/06 12:54:28 arnold 13 12
c make scorehand know what really is a crib and how to deal with flushes
e
s 00002/00000/00548
d D 1.11 83/05/19 12:21:29 arnold 12 11
c add sccs keywords
e
s 00007/00002/00541
d D 1.10 83/05/08 18:47:41 arnold 11 10
c set Mpos properly in endmsg()
e
s 00037/00010/00506
d D 1.9 83/05/07 14:06:50 arnold 10 9
c add a scrolling region
e
s 00036/00027/00480
d D 1.8 83/05/01 15:30:56 arnold 9 8
c make a scrolling region for cribbage
e
s 00001/00001/00506
d D 1.7 83/05/01 13:26:08 arnold 8 7
c swap the board and the cards on the screen
e
s 00006/00004/00501
d D 1.6 82/09/06 14:58:55 arnold 7 5
c show back of computer's hand during play
e
s 00147/00113/00392
d R 1.6 82/08/28 17:06:25 arnold 6 5
c reformatting and obvious optimization
e
s 00001/00001/00504
d D 1.5 82/08/27 23:04:49 arnold 5 4
c simplify infrom() prompt mechanism
e
s 00009/00006/00496
d D 1.4 82/08/27 22:55:16 arnold 4 3
c print blank turnover card to indicate crib
e
s 00032/00034/00470
d D 1.3 82/08/27 14:23:29 arnold 3 2
c make simple <RETURN> not be the same as typing "0"
e
s 00417/00260/00087
d D 1.2 82/08/24 18:34:07 arnold 2 1
c first "working" visual version
e
s 00347/00000/00000
d D 1.1 82/08/11 16:35:59 arnold 1 0
c date and time created 82/08/11 16:35:59 by arnold
e
u
U
t
T
I 12
D 15
static char	*sccsid = "%W% (Berkeley) %G%";
E 15
I 15
D 28
/*
 * Copyright (c) 1980 Regents of the University of California.
E 28
I 28
/*-
D 29
 * Copyright (c) 1980 The Regents of the University of California.
E 28
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 20
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 18
I 18
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 18
E 17
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17
E 15

E 12
I 2
D 28
# include	<curses.h>
# include	<ctype.h>
I 13
# include	<signal.h>
I 25
# include       <termios.h>
E 25
I 23
# if __STDC__
E 23
I 21
# include	<stdarg.h>
I 23
# else
# include	<varargs.h>
# endif
E 23
E 21
E 13
D 14
# include	<unctrl.h>
E 14
# include	"deck.h"
# include	"cribbage.h"
I 9
# include	"cribcur.h"
E 28
I 28
#include <ctype.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
E 28
E 9
E 2
I 1

D 2
#include	<stdio.h>
#include	"deck.h"
E 2
I 2
D 28
# define	LINESIZE		128
E 28
I 28
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 28
E 2

I 9
D 28
# ifdef CTRL
# undef CTRL
# endif
E 9
D 2
#define		LINESIZE		128
E 2
I 2
D 27
# define	CTRL(X)			('X' - 'A' + 1)
E 27
I 27
# define	CTRL(X)			(X - 'A' + 1)
E 28
I 28
#include "deck.h"
#include "cribbage.h"
#include "cribcur.h"
E 28
E 27
E 2

I 2
D 16
# ifndef	attron
E 16
I 16
D 28
# ifdef	notdef				/* defined in curses.h */
E 16
#	define	erasechar()	_tty.sg_erase
#	define	killchar()	_tty.sg_kill
D 16
# endif		attron
E 16
I 16
# endif
E 28
I 28
#define	LINESIZE		128
E 28
E 16

E 2
D 28
char		linebuf[ LINESIZE ];
E 28
I 28
#ifdef CTRL
#undef CTRL
#endif
#define	CTRL(X)			(X - 'A' + 1)
E 28

D 28
char		*rankname[ RANKS ]	= { "ACE", "TWO", "THREE", "FOUR",
D 2
				            "FIVE", "SIX", "SEVEN", "EIGHT",
                                            "NINE", "TEN", "JACK", "QUEEN",
                                            "KING" };
E 2
I 2
					    "FIVE", "SIX", "SEVEN", "EIGHT",
					    "NINE", "TEN", "JACK", "QUEEN",
					    "KING" };
E 28
I 28
char    linebuf[LINESIZE];
E 28
E 2

D 28
char            *rankchar[ RANKS ]      = { "A", "2", "3", "4", "5", "6", "7",
D 2
                                            "8", "9", "T", "J", "Q", "K" };
E 2
I 2
					    "8", "9", "T", "J", "Q", "K" };
E 28
I 28
char   *rankname[RANKS] = {
	"ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
	"EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"
};
E 28
E 2

D 28
char            *suitname[ SUITS ]      = { "SPADES", "HEARTS", "DIAMONDS",
D 2
                                            "CLUBS" };
E 2
I 2
					    "CLUBS" };
E 28
I 28
char   *rankchar[RANKS] = {
	"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"
};
E 28
E 2

D 28
char            *suitchar[ SUITS ]      = { "S", "H", "D", "C" };
E 28
I 28
char   *suitname[SUITS] = {"SPADES", "HEARTS", "DIAMONDS", "CLUBS"};
E 28

I 28
char   *suitchar[SUITS] = {"S", "H", "D", "C"};
E 28

D 28

E 28
/*
D 2
 * call prcard in one of two forms
E 2
I 2
 * msgcard:
 *	Call msgcrd in one of two forms
E 2
 */
I 28
int
E 28
D 2

printcard( c, brief )

    CARD                c;
    BOOLEAN             brief;
E 2
I 2
msgcard(c, brief)
D 28
CARD		c;
BOOLEAN		brief;
E 28
I 28
	CARD c;
	BOOLEAN brief;
E 28
E 2
{
D 2
        if( brief )  return(  prcard( c, TRUE, (char *) NULL, TRUE )  );
        else         return(  prcard( c, FALSE, " of ", FALSE )  );
E 2
I 2
	if (brief)
D 28
		return msgcrd(c, TRUE, (char *) NULL, TRUE);
E 28
I 28
		return (msgcrd(c, TRUE, NULL, TRUE));
E 28
	else
D 28
		return msgcrd(c, FALSE, " of ", FALSE);
E 28
I 28
		return (msgcrd(c, FALSE, " of ", FALSE));
E 28
E 2
}

D 28


E 28
/*
D 2
 * print the value of a card in ascii
E 2
I 2
 * msgcrd:
 *	Print the value of a card in ascii
E 2
 */
I 28
int
E 28
I 2
msgcrd(c, brfrank, mid, brfsuit)
D 28
CARD		c;
char		*mid;
BOOLEAN		brfrank,  brfsuit;
E 28
I 28
	CARD c;
	BOOLEAN brfrank, brfsuit;
	char *mid;
E 28
{
	if (c.rank == EMPTY || c.suit == EMPTY)
D 28
	    return FALSE;
E 28
I 28
		return (FALSE);
E 28
	if (brfrank)
D 28
	    addmsg("%1.1s", rankchar[c.rank]);
E 28
I 28
		addmsg("%1.1s", rankchar[c.rank]);
E 28
	else
D 28
	    addmsg(rankname[c.rank]);
E 28
I 28
		addmsg(rankname[c.rank]);
E 28
	if (mid != NULL)
D 28
	    addmsg(mid);
E 28
I 28
		addmsg(mid);
E 28
	if (brfsuit)
D 28
	    addmsg("%1.1s", suitchar[c.suit]);
E 28
I 28
		addmsg("%1.1s", suitchar[c.suit]);
E 28
	else
D 28
	    addmsg(suitname[c.suit]);
	return TRUE;
E 28
I 28
		addmsg(suitname[c.suit]);
	return (TRUE);
E 28
}
E 2

D 2
prcard( c, brfrank, mid, brfsuit )

    CARD                c;
    char                *mid;
    BOOLEAN             brfrank,  brfsuit;
E 2
I 2
/*
 * printcard:
 *	Print out a card.
 */
I 28
void
E 28
D 7
printcard(win, cardno, c)
E 7
I 7
printcard(win, cardno, c, blank)
E 7
D 28
WINDOW		*win;
int		cardno;
CARD		c;
I 7
BOOLEAN		blank;
E 28
I 28
	WINDOW *win;
	int     cardno;
	CARD    c;
	BOOLEAN blank;
E 28
E 7
E 2
{
D 2
        if(  c.rank == -1  ||  c.suit == -1  )  return( FALSE );
        if( brfrank )  {
            printf( "%1.1s",  rankchar[ c.rank ] );
        }
        else  {
            printf( "%s",  rankname[ c.rank ] );
        }
        if( mid != NULL )  printf( "%s", mid );
        if( brfsuit )  {
            printf( "%1.1s",  suitchar[ c.suit ] );
        }
        else  {
            printf( "%s",  suitname[ c.suit ] );
        }
        return( TRUE );
E 2
I 2
D 4
	prcard(win, cardno * 2, cardno, c);
E 4
I 4
D 7
	prcard(win, cardno * 2, cardno, c, FALSE);
E 7
I 7
	prcard(win, cardno * 2, cardno, c, blank);
E 7
E 4
E 2
}

D 2


E 2
/*
D 2
 * prhand prints a hand of n cards
E 2
I 2
 * prcard:
 *	Print out a card on the window at the specified location
E 2
 */
I 28
void
E 28
I 2
D 4
prcard(win, y, x, c)
E 4
I 4
prcard(win, y, x, c, blank)
E 4
D 28
WINDOW		*win;
int		y, x;
CARD		c;
I 4
BOOLEAN		blank;
E 28
I 28
	WINDOW *win;
	int y, x;
	CARD c;
	BOOLEAN blank;
E 28
E 4
{
	if (c.rank == EMPTY)
D 28
	    return;
E 28
I 28
		return;

E 28
	mvwaddstr(win, y + 0, x, "+-----+");
	mvwaddstr(win, y + 1, x, "|     |");
	mvwaddstr(win, y + 2, x, "|     |");
	mvwaddstr(win, y + 3, x, "|     |");
	mvwaddstr(win, y + 4, x, "+-----+");
D 4
	mvwaddch(win, y + 1, x + 1, rankchar[c.rank][0]);
	waddch(win, suitchar[c.suit][0]);
	mvwaddch(win, y + 3, x + 4, rankchar[c.rank][0]);
	waddch(win, suitchar[c.suit][0]);
E 4
I 4
	if (!blank) {
		mvwaddch(win, y + 1, x + 1, rankchar[c.rank][0]);
		waddch(win, suitchar[c.suit][0]);
		mvwaddch(win, y + 3, x + 4, rankchar[c.rank][0]);
		waddch(win, suitchar[c.suit][0]);
	}
E 4
}
E 2

D 2
prhand( h, n, brief )

    CARD                h[];
    int                 n;
    BOOLEAN             brief;
E 2
I 2
/*
 * prhand:
 *	Print a hand of n cards
 */
I 28
void
E 28
D 7
prhand(h, n, win)
E 7
I 7
prhand(h, n, win, blank)
E 7
D 28
CARD		h[];
int		n;
WINDOW		*win;
I 7
BOOLEAN		blank;
E 28
I 28
	CARD h[];
	int n;
	WINDOW *win;
	BOOLEAN blank;
E 28
E 7
E 2
{
D 2
        register  int           i;
E 2
I 2
D 28
	register int	i;
E 28
I 28
	register int i;
E 28
E 2

D 2
        --n;
        for( i = 0; i < n; i++ )  {
            if(  printcard( h[i], brief )  )  {
                if( brief )  printf( ", " );
                else     printf( "\n" );
            }
        }
        printcard( h[i], brief );
E 2
I 2
	werase(win);
	for (i = 0; i < n; i++)
D 7
	    printcard(win, i, h[i]);
E 7
I 7
D 28
	    printcard(win, i, *h++, blank);
E 28
I 28
		printcard(win, i, *h++, blank);
E 28
E 7
	wrefresh(win);
E 2
}

D 28


E 28
/*
D 2
 * infrom reads a card, supposedly in hand, accepting unambigous brief input
 * returns the index of the card found...
E 2
I 2
 * infrom:
 *	reads a card, supposedly in hand, accepting unambigous brief
 *	input, returns the index of the card found...
E 2
 */
I 28
int
E 28
D 2

infrom( hand, n )

    CARD                hand[];
    int                 n;
E 2
I 2
infrom(hand, n, prompt)
D 28
CARD		hand[];
int		n;
char		*prompt;
E 28
I 28
	CARD hand[];
	int n;
	char *prompt;
E 28
E 2
{
D 2
        register  int           i, j;
        CARD                    crd;
E 2
I 2
D 28
	register int           i, j;
	CARD                    crd;
E 28
I 28
	register int i, j;
	CARD crd;
E 28
E 2

D 2
        if(  n < 1  )  {
            printf( "\nINFROM: %d = n < 1!!\n", n );
            exit( 74 );
        }
        do  {
            if(  incard( &crd )  )  {           /* if card is full card */
                if(  !isone( crd, hand, n )  )  {
                    printf( "That's not in your hand.  Play one of ( " );
                    prhand( hand, n, TRUE );
                    printf( " ): " );
                }
                else  {
                    for( i = 0; i < n; i++ )  {
                        if(  hand[i].rank == crd.rank  &&
                             hand[i].suit == crd.suit      )  break;
                    }
                    if(  i >= n  )  {
                        printf( "\nINFROM: isone or something messed up\n" );
                        exit( 77 );
                    }
                    return( i );
                }
            }
            else  {                             /* if not full card... */
                if(  crd.rank  !=  -1  )  {
                    for( i = 0; i < n; i++ )  {
                        if(  hand[i].rank == crd.rank  )  break;
                    }
                    if(  i >= n  )  {
                        printf( "No such rank in your hand.  Play one of ( " );
                        prhand( hand, n, TRUE );
                        printf( " ): " );
                    }
                    else  {
                        for( j = i + 1; j < n; j++ )  {
                            if(  hand[j].rank == crd.rank  )  break;
                        }
                        if(  j < n  )  {
                            printf( "Ambiguous rank.  Play one of ( " );
                            prhand( hand, n, TRUE );
                            printf( " ): " );
                        }
                        else  {
                            return( i );
                        }
                    }
                }
                else  {
                    printf( "Sorry, I missed that.  Play one of ( " );
                    prhand( hand, n, TRUE );
                    printf( " ): " );
                }
            }
        }  while( TRUE );
	return( 0 );   /*  Useless:  keeps lint quiet  */
}
E 2
I 2
	if (n < 1) {
D 28
	    printf("\nINFROM: %d = n < 1!!\n", n);
	    exit(74);
E 28
I 28
		printf("\nINFROM: %d = n < 1!!\n", n);
		exit(74);
E 28
	}
	for (;;) {
I 5
D 28
	    msg(prompt);
E 5
	    if (incard(&crd)) {			/* if card is full card */
		if (!isone(crd, hand, n))
		    msg("That's not in your hand");
		else {
		    for (i = 0; i < n; i++)
			if (hand[i].rank == crd.rank &&
			    hand[i].suit == crd.suit)
				break;
		    if (i >= n) {
E 28
I 28
		msg(prompt);
		if (incard(&crd)) {	/* if card is full card */
			if (!isone(crd, hand, n))
				msg("That's not in your hand");
			else {
				for (i = 0; i < n; i++)
					if (hand[i].rank == crd.rank &&
					    hand[i].suit == crd.suit)
						break;
				if (i >= n) {
E 28
			printf("\nINFROM: isone or something messed up\n");
D 28
			exit(77);
		    }
		    return i;
		}
	    }
	    else				/* if not full card... */
		if (crd.rank != EMPTY) {
		    for (i = 0; i < n; i++)
			if (hand[i].rank == crd.rank)
				break;
		    if (i >= n)
			msg("No such rank in your hand");
		    else {
			for (j = i + 1; j < n; j++)
			    if (hand[j].rank == crd.rank)
				break;
			if (j < n)
			    msg("Ambiguous rank");
			else
			    return i;
		    }
		}
		else
		    msg("Sorry, I missed that");
E 28
I 28
					exit(77);
				}
				return (i);
			}
		} else			/* if not full card... */
			if (crd.rank != EMPTY) {
				for (i = 0; i < n; i++)
					if (hand[i].rank == crd.rank)
						break;
				if (i >= n)
					msg("No such rank in your hand");
				else {
					for (j = i + 1; j < n; j++)
						if (hand[j].rank == crd.rank)
							break;
					if (j < n)
						msg("Ambiguous rank");
					else
						return (i);
				}
			} else
				msg("Sorry, I missed that");
E 28
D 5
	    msg(prompt);
E 5
	}
	/* NOTREACHED */
}
E 2

D 28


E 28
/*
D 2
 * incard inputs a card in any format
 * it reads a line ending with a CR and then parses it
E 2
I 2
 * incard:
 *	Inputs a card in any format.  It reads a line ending with a CR
 *	and then parses it.
E 2
 */
I 28
int
E 28
D 2

incard( crd )

    CARD                *crd;
E 2
I 2
incard(crd)
D 28
CARD		*crd;
E 28
I 28
	CARD *crd;
E 28
E 2
{
D 2
        char                    *getline();
        register  int           i;
        int                     rnk, sut;
        char                    *line, *p, *p1;
        BOOLEAN                 retval;
E 2
I 2
D 28
	char		*getline();
	register int	i;
	int		rnk, sut;
	char		*line, *p, *p1;
	BOOLEAN		retval;
E 28
I 28
	register int i;
	int rnk, sut;
	char *line, *p, *p1;
	BOOLEAN retval;
E 28
E 2

D 2
        retval = FALSE;
        rnk = sut = -1;
        if(  !( line = getline() )  )  goto  gotit;
        p = p1 = line;
        while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
        *p1++ = NULL;
        if(  *p == NULL  )  goto  gotit;
                        /* IMPORTANT: no real card has 2 char first name */
        if(  strlen(p) == 2  )  {               /* check for short form */
            rnk = -1;
            for( i = 0; i < RANKS; i++ )  {
                if(  *p == *rankchar[i]  )  {
                    rnk = i;
                    break;
                }
            }
            if(  rnk == -1  )  goto  gotit;     /* it's nothing... */
            ++p;                                /* advance to next char */
            sut = -1;
            for( i = 0; i < SUITS; i++ )  {
                if(  *p == *suitchar[i]  )  {
                    sut = i;
                    break;
                }
            }
            if(  sut != -1  )  retval = TRUE;
            goto  gotit;
        }
        rnk = -1;
        for( i = 0; i < RANKS; i++ )  {
            if(  !strcmp( p, rankname[i] )  ||  !strcmp( p, rankchar[i] )  )  {
                rnk = i;
                break;
            }
        }
        if(  rnk == -1  )  goto  gotit;
        p = p1;
        while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
        *p1++ = NULL;
        if(  *p == NULL  )  goto  gotit;
        if(  !strcmp( "OF", p )  )  {
            p = p1;
            while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
            *p1++ = NULL;
            if(  *p == NULL  )  goto  gotit;
        }
        sut = -1;
        for( i = 0; i < SUITS; i++ )  {
            if(  !strcmp( p, suitname[i] )  ||  !strcmp( p, suitchar[i] )  )  {
                sut = i;
                break;
            }
        }
        if(  sut != -1  )  retval = TRUE;
E 2
I 2
	retval = FALSE;
	rnk = sut = EMPTY;
	if (!(line = getline()))
		goto gotit;
	p = p1 = line;
D 28
	while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
E 28
I 28
	while (*p1 != ' ' && *p1 != NULL)
		++p1;
E 28
	*p1++ = NULL;
D 28
	if(  *p == NULL  )  goto  gotit;
			/* IMPORTANT: no real card has 2 char first name */
	if(  strlen(p) == 2  )  {               /* check for short form */
	    rnk = EMPTY;
	    for( i = 0; i < RANKS; i++ )  {
		if(  *p == *rankchar[i]  )  {
		    rnk = i;
		    break;
E 28
I 28
	if (*p == NULL)
		goto gotit;

	/* IMPORTANT: no real card has 2 char first name */
	if (strlen(p) == 2) {	/* check for short form */
		rnk = EMPTY;
		for (i = 0; i < RANKS; i++) {
			if (*p == *rankchar[i]) {
				rnk = i;
				break;
			}
E 28
		}
D 28
	    }
	    if(  rnk == EMPTY  )  goto  gotit;     /* it's nothing... */
	    ++p;                                /* advance to next char */
	    sut = EMPTY;
	    for( i = 0; i < SUITS; i++ )  {
		if(  *p == *suitchar[i]  )  {
		    sut = i;
		    break;
E 28
I 28
		if (rnk == EMPTY)
			goto gotit;	/* it's nothing... */
		++p;		/* advance to next char */
		sut = EMPTY;
		for (i = 0; i < SUITS; i++) {
			if (*p == *suitchar[i]) {
				sut = i;
				break;
			}
E 28
		}
D 28
	    }
	    if(  sut != EMPTY  )  retval = TRUE;
	    goto  gotit;
E 28
I 28
		if (sut != EMPTY)
			retval = TRUE;
		goto gotit;
E 28
	}
	rnk = EMPTY;
D 28
	for( i = 0; i < RANKS; i++ )  {
	    if(  !strcmp( p, rankname[i] )  ||  !strcmp( p, rankchar[i] )  )  {
		rnk = i;
		break;
	    }
E 28
I 28
	for (i = 0; i < RANKS; i++) {
		if (!strcmp(p, rankname[i]) || !strcmp(p, rankchar[i])) {
			rnk = i;
			break;
		}
E 28
	}
D 28
	if(  rnk == EMPTY  )  goto  gotit;
E 28
I 28
	if (rnk == EMPTY)
		goto gotit;
E 28
	p = p1;
D 28
	while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
E 28
I 28
	while (*p1 != ' ' && *p1 != NULL)
		++p1;
E 28
	*p1++ = NULL;
D 28
	if(  *p == NULL  )  goto  gotit;
	if(  !strcmp( "OF", p )  )  {
	    p = p1;
	    while(  *p1 != ' '  &&  *p1 != NULL  )  ++p1;
	    *p1++ = NULL;
	    if(  *p == NULL  )  goto  gotit;
E 28
I 28
	if (*p == NULL)
		goto gotit;
	if (!strcmp("OF", p)) {
		p = p1;
		while (*p1 != ' ' && *p1 != NULL)
			++p1;
		*p1++ = NULL;
		if (*p == NULL)
			goto gotit;
E 28
	}
	sut = EMPTY;
D 28
	for( i = 0; i < SUITS; i++ )  {
	    if(  !strcmp( p, suitname[i] )  ||  !strcmp( p, suitchar[i] )  )  {
		sut = i;
		break;
	    }
E 28
I 28
	for (i = 0; i < SUITS; i++) {
		if (!strcmp(p, suitname[i]) || !strcmp(p, suitchar[i])) {
			sut = i;
			break;
		}
E 28
	}
D 28
	if(  sut != EMPTY  )  retval = TRUE;
E 28
I 28
	if (sut != EMPTY)
		retval = TRUE;
E 28
E 2
gotit:
D 2
        (*crd).rank = rnk;
        (*crd).suit = sut;
        return( retval );
E 2
I 2
	(*crd).rank = rnk;
	(*crd).suit = sut;
D 28
	return( retval );
E 28
I 28
	return (retval);
E 28
E 2
}

D 28


E 28
/*
D 2
 * getuchar reads and converts to upper case
E 2
I 2
 * getuchar:
 *	Reads and converts to upper case
E 2
 */
I 28
int
E 28
D 2

E 2
getuchar()
{
D 2
        register  int           c;
E 2
I 2
D 28
	register int		c;
E 28
I 28
	register int c;
E 28
E 2

D 2
        c = getchar();
        if(  c < 'a'  ||  c > 'z'  )  return( c );
        else                          return(  c + ('A' - 'a')  );
E 2
I 2
	c = readchar();
	if (islower(c))
D 28
	    c = toupper(c);
E 28
I 28
		c = toupper(c);
E 28
D 9
	addch(c);
E 9
I 9
	waddch(Msgwin, c);
E 9
D 28
	return c;
E 28
I 28
	return (c);
E 28
E 2
}

D 3


E 3
/*
D 3
 * number reads in a decimal number and makes sure it is between
 * lo and hi inclusive
 * a cr counts as lo
E 3
I 3
 * number:
 *	Reads in a decimal number and makes sure it is between "lo" and
 *	"hi" inclusive.
E 3
 */
I 28
int
E 28
D 3

number( lo, hi )

    int         lo, hi;
E 3
I 3
number(lo, hi, prompt)
D 28
int		lo, hi;
char		*prompt;
E 28
I 28
	int lo, hi;
	char *prompt;
E 28
E 3
{
D 2
        char                    *getline();
        register  char          *p;
        register  int            sum;
E 2
I 2
D 3
	char                    *getline();
	register  char          *p;
	register  int            sum;
E 3
I 3
D 28
	char			*getline();
	register char		*p;
	register int		sum;
E 28
I 28
	register char *p;
	register int sum;
E 28
E 3
E 2

D 2
        sum = 0;
        do  {
            if(  !( p = getline() )  )  return( lo );   /* no line = lo */
            if(  *p == NULL  )  return( lo );
            sum = 0;
            while(  *p == ' '  ||  *p == '\t'  )  ++p;
            if(  *p < '0'  ||  *p > '9'  )  {
                sum = lo - 1;
            }
            else  {
                do  {
                    sum = 10*sum + (*p - '0');
                    ++p;
                }  while(  '0' <= *p  &&  *p <= '9'  );
            }
            if(  *p != ' '  &&  *p != '\t'  &&  *p != NULL  )  sum = lo - 1;
            if(  sum >= lo  &&  sum <= hi  )  break;
            if(  sum == lo - 1  )  {
                printf( "that doesn't look like a number, try again --> " );
            }
            else  {
                printf( "%d is not between %d and %d inclusive, try again --> ",
                                                                sum, lo, hi );
            }
        }  while( TRUE );
        return( sum );
E 2
I 2
D 28
	sum = 0;
D 3
	do  {
	    if(  !( p = getline() )  )  return( lo );   /* no line = lo */
	    if(  *p == NULL  )  return( lo );
E 3
I 3
	for (;;) {
	    msg(prompt);
	    if(!(p = getline()) || *p == NULL) {
		msg(quiet ? "Not a number" : "That doesn't look like a number");
		continue;
	    }
E 3
	    sum = 0;
D 3
	    while(  *p == ' '  ||  *p == '\t'  )  ++p;
	    if(  *p < '0'  ||  *p > '9'  )  {
E 3
I 3

	    if (!isdigit(*p))
E 3
		sum = lo - 1;
D 3
	    }
	    else  {
		do  {
		    sum = 10*sum + (*p - '0');
E 3
I 3
	    else
		while (isdigit(*p)) {
		    sum = 10 * sum + (*p - '0');
E 3
		    ++p;
E 28
I 28
	for (sum = 0;;) {
		msg(prompt);
		if (!(p = getline()) || *p == NULL) {
			msg(quiet ? "Not a number" :
			    "That doesn't look like a number");
			continue;
E 28
D 3
		}  while(  '0' <= *p  &&  *p <= '9'  );
	    }
	    if(  *p != ' '  &&  *p != '\t'  &&  *p != NULL  )  sum = lo - 1;
	    if(  sum >= lo  &&  sum <= hi  )  break;
	    if(  sum == lo - 1  )  {
		printf( "that doesn't look like a number, try again --> " );
	    }
	    else  {
		printf( "%d is not between %d and %d inclusive, try again --> ",
								sum, lo, hi );
	    }
	}  while( TRUE );
	return( sum );
E 3
I 3
		}
I 28
		sum = 0;
E 28

D 28
	    if (*p != ' ' && *p != '\t' && *p != NULL)
		sum = lo - 1;
	    if (sum >= lo && sum <= hi)
		return sum;
	    if (sum == lo - 1)
		msg("that doesn't look like a number, try again --> ");
	    else
E 28
I 28
		if (!isdigit(*p))
			sum = lo - 1;
		else
			while (isdigit(*p)) {
				sum = 10 * sum + (*p - '0');
				++p;
			}

		if (*p != ' ' && *p != '\t' && *p != NULL)
			sum = lo - 1;
		if (sum >= lo && sum <= hi)
			break;
		if (sum == lo - 1)
			msg("that doesn't look like a number, try again --> ");
		else
E 28
		msg("%d is not between %d and %d inclusive, try again --> ",
D 28
								sum, lo, hi);
E 28
I 28
			    sum, lo, hi);
E 28
	}
I 28
	return (sum);
E 28
E 3
E 2
}

I 2
/*
 * msg:
 *	Display a message at the top of the screen.
 */
D 8
char		Msgbuf[BUFSIZ] = "";
E 8
I 8
D 28
char		Msgbuf[BUFSIZ] = { '\0' };
E 28
I 28
char    Msgbuf[BUFSIZ] = {'\0'};
int     Mpos = 0;
static int Newpos = 0;
E 28
E 8
E 2

I 2
D 28
int		Mpos = 0;
E 2

I 2
static int	Newpos = 0;

/* VARARGS1 */
E 28
I 26
void
E 26
D 21
msg(fmt, args)
char	*fmt;
int	args;
E 21
I 21
D 23
msg(fmt)
E 23
I 23
#if __STDC__
D 26
msg(char *fmt, ...)
E 26
I 26
msg(const char *fmt, ...)
E 26
#else
msg(fmt, va_alist)
E 23
	char *fmt;
I 23
	va_dcl
#endif
E 23
E 21
{
D 9
    /*
     * if the string is "", just clear the line
     */
    if (*fmt == '\0') {
	move(LINES - 1, 0);
	clrtoeol();
	Mpos = 0;
	Hasread = TRUE;
	return;
    }
    /*
     * otherwise add to the message and flush it out
     */
E 9
D 21
    doadd(fmt, &args);
    endmsg();
E 21
I 21
	va_list ap;

I 23
#if __STDC__
E 23
	va_start(ap, fmt);
I 23
#else
	va_start(ap);
#endif
E 23
D 22
	(void)vsprintf(Msgbuf[Newpos], fmt, ap);
E 22
I 22
	(void)vsprintf(&Msgbuf[Newpos], fmt, ap);
E 22
	va_end(ap);
	endmsg();
E 21
}

E 2
/*
D 2
 * getline reads the next line up to '\n' or EOF
 * multiple spaces are compressed to one space
 * a space is inserted before a ','
E 2
I 2
 * addmsg:
 *	Add things to the current message
E 2
 */
I 2
D 28
/* VARARGS1 */
E 28
I 26
void
E 26
D 21
addmsg(fmt, args)
char	*fmt;
int	args;
E 21
I 21
D 23
addmsg(fmt)
E 23
I 23
#if __STDC__
D 26
addmsg(char *fmt, ...)
E 26
I 26
addmsg(const char *fmt, ...)
E 26
#else
addmsg(fmt, va_alist)
E 23
	char *fmt;
I 23
	va_dcl
#endif
E 23
E 21
{
D 21
    doadd(fmt, &args);
E 21
I 21
	va_list ap;

I 23
#if __STDC__
E 23
	va_start(ap, fmt);
I 23
#else
	va_start(ap);
#endif
E 23
D 22
	(void)vsprintf(Msgbuf[Newpos], fmt, ap);
E 22
I 22
	(void)vsprintf(&Msgbuf[Newpos], fmt, ap);
E 22
	va_end(ap);
E 21
}
E 2

D 2
char  *getline()
E 2
I 2
/*
 * endmsg:
D 9
 *	Display a new msg (giving him a chance to see the previous one
 *	if it is up there with the --More--)
E 9
I 9
 *	Display a new msg.
E 9
 */
I 28
int     Lineno = 0;
E 28
I 10

D 28
int	Lineno = 0;

E 28
I 28
void
E 28
E 10
endmsg()
E 2
{
D 2
        register  char                  c, *p;
E 2
I 2
D 9
    if (!Hasread) {
	move(LINES - 1, Mpos);
	addstr("--More--");
	refresh();
	wait_for(' ');
    }
E 9
I 9
D 28
    register int	len;
    register char	*mp, *omp;
D 10
    static int		lineno = 0;
E 10
I 10
    static int		lastline = 0;
E 28
I 28
	static int lastline = 0;
	register int len;
	register char *mp, *omp;
E 28
E 10

E 9
D 28
    /*
D 10
     * All messages should start with uppercase, except ones that
     * start with a pack addressing character
E 10
I 10
     * All messages should start with uppercase
E 10
     */
I 10
    mvaddch(lastline + Y_MSG_START, SCORE_X, ' ');
E 10
    if (islower(Msgbuf[0]) && Msgbuf[1] != ')')
	Msgbuf[0] = toupper(Msgbuf[0]);
D 9
    mvaddstr(LINES - 1, 0, Msgbuf);
    clrtoeol();
E 9
I 9
    mp = Msgbuf;
    len = strlen(mp);
D 10
    if (len / MSG_X + lineno > MSG_Y)
	lineno = 0;
E 10
I 10
D 11
    if (len / MSG_X + Lineno >= MSG_Y)
E 11
I 11
    if (len / MSG_X + Lineno >= MSG_Y) {
	while (Lineno < MSG_Y) {
	    wmove(Msgwin, Lineno++, 0);
	    wclrtoeol(Msgwin);
E 28
I 28
	/* All messages should start with uppercase */
	mvaddch(lastline + Y_MSG_START, SCORE_X, ' ');
	if (islower(Msgbuf[0]) && Msgbuf[1] != ')')
		Msgbuf[0] = toupper(Msgbuf[0]);
	mp = Msgbuf;
	len = strlen(mp);
	if (len / MSG_X + Lineno >= MSG_Y) {
		while (Lineno < MSG_Y) {
			wmove(Msgwin, Lineno++, 0);
			wclrtoeol(Msgwin);
		}
		Lineno = 0;
E 28
	}
E 11
D 28
	Lineno = 0;
I 11
    }
E 11
    mvaddch(Lineno + Y_MSG_START, SCORE_X, '*');
    lastline = Lineno;
E 10
    do {
D 10
	mvwaddstr(Msgwin, lineno, 0, mp);
E 10
I 10
	mvwaddstr(Msgwin, Lineno, 0, mp);
E 10
	if ((len = strlen(mp)) > MSG_X) {
	    omp = mp;
	    for (mp = &mp[MSG_X-1]; *mp != ' '; mp--)
	    	continue;
	    while (*mp == ' ')
		mp--;
	    mp++;
D 10
	    wmove(Msgwin, lineno, mp - omp);
E 10
I 10
	    wmove(Msgwin, Lineno, mp - omp);
E 10
	    wclrtoeol(Msgwin);
	}
D 10
	if (++lineno >= MSG_Y)
	    lineno = 0;
E 10
I 10
	if (++Lineno >= MSG_Y)
	    Lineno = 0;
E 10
    } while (len > MSG_X);
    wclrtoeol(Msgwin);
E 9
D 10
    Mpos = Newpos;
E 10
I 10
D 11
    Mpos = Newpos % MSG_X;
E 11
I 11
    Mpos = len;
E 11
E 10
    Newpos = 0;
I 9
    wrefresh(Msgwin);
E 9
    refresh();
D 9
    Hasread = FALSE;
E 9
I 9
    wrefresh(Msgwin);
E 28
I 28
	mvaddch(Lineno + Y_MSG_START, SCORE_X, '*');
	lastline = Lineno;
	do {
		mvwaddstr(Msgwin, Lineno, 0, mp);
		if ((len = strlen(mp)) > MSG_X) {
			omp = mp;
			for (mp = &mp[MSG_X - 1]; *mp != ' '; mp--)
				continue;
			while (*mp == ' ')
				mp--;
			mp++;
			wmove(Msgwin, Lineno, mp - omp);
			wclrtoeol(Msgwin);
		}
		if (++Lineno >= MSG_Y)
			Lineno = 0;
	} while (len > MSG_X);
	wclrtoeol(Msgwin);
	Mpos = len;
	Newpos = 0;
	wrefresh(Msgwin);
	refresh();
	wrefresh(Msgwin);
E 28
E 9
}
E 2

I 21
D 28
#ifdef notdef
E 28
E 21
D 2
        do  {
            c = getuchar();
            if(  c < 0  )  return( NULL );
        }  while(  c == ' '  ||  c == '\t'  );
        if(  c == '\n'  )  {
            linebuf[0] = NULL;
            return( linebuf );
        }
        p = linebuf;
        *p = c;                                         /* first non-blank */
        while(  ( c = getuchar() )  >= 0  )  {          /* read one line */
            if(  c == '\n'  )  break;
            if(  c == ','  )  if(  *p != ' '  )  *++p = ' ';
            if(  *p == ' '  )  {                        /* compress spaces */
                if(  c == ' '  ||  c == '\t'  )  continue;
                else  *++p = c;
            }
            else  {
                if(  c == ' '  ||  c == '\t'  )  *++p = ' ';
                else  *++p = c;
            }
            if(  p - linebuf  >=  (LINESIZE - 2)  )  {
                do  {
                    c = getuchar();
                    if(  c < 0  )  return( NULL );
                }  while(  c != '\n'  );
                break;
            }
        }
        if(  c < 0  )  return( NULL );
        *++p = NULL;
        *++p = NULL;
        return( linebuf );
E 2
I 2
/*
D 28
 * doadd:
 *	Perform an add onto the message buffer
 */
doadd(fmt, args)
char	*fmt;
int	*args;
{
    static FILE	junk;

    /*
     * Do the printf into Msgbuf
     */
    junk._flag = _IOWRT + _IOSTRG;
    junk._ptr = &Msgbuf[Newpos];
    junk._cnt = 32767;
    _doprnt(fmt, args, &junk);
    putc('\0', &junk);
    Newpos = strlen(Msgbuf);
I 10
}
I 21
#endif
E 21

/*
E 28
 * do_wait:
 *	Wait for the user to type ' ' before doing anything else
 */
I 28
void
E 28
do_wait()
{
D 28
    register int line;
    static char prompt[] = { '-', '-', 'M', 'o', 'r', 'e', '-', '-', '\0' };
E 28
I 28
	static char prompt[] = {'-', '-', 'M', 'o', 'r', 'e', '-', '-', '\0'};
E 28

D 28
    if (Mpos + sizeof prompt < MSG_X)
	wmove(Msgwin, Lineno > 0 ? Lineno - 1 : MSG_Y - 1, Mpos);
    else {
	mvwaddch(Msgwin, Lineno, 0, ' ');
	wclrtoeol(Msgwin);
	if (++Lineno >= MSG_Y)
	    Lineno = 0;
    }
    waddstr(Msgwin, prompt);
    wrefresh(Msgwin);
    wait_for(' ');
E 28
I 28
	if (Mpos + sizeof prompt < MSG_X)
		wmove(Msgwin, Lineno > 0 ? Lineno - 1 : MSG_Y - 1, Mpos);
	else {
		mvwaddch(Msgwin, Lineno, 0, ' ');
		wclrtoeol(Msgwin);
		if (++Lineno >= MSG_Y)
			Lineno = 0;
	}
	waddstr(Msgwin, prompt);
	wrefresh(Msgwin);
	wait_for(' ');
E 28
E 10
E 2
}

I 2
/*
 * wait_for
 *	Sit around until the guy types the right key
 */
I 28
void
E 28
wait_for(ch)
D 28
register char	ch;
E 28
I 28
	register int ch;
E 28
{
D 28
    register char	c;
E 28
I 28
	register char c;
E 28
E 2

I 2
D 28
    if (ch == '\n')
	while ((c = readchar()) != '\n')
	    continue;
    else
	while (readchar() != ch)
	    continue;
E 28
I 28
	if (ch == '\n')
		while ((c = readchar()) != '\n')
			continue;
	else
		while (readchar() != ch)
			continue;
E 28
}
E 2

I 2
/*
 * readchar:
 *	Reads and returns a character, checking for gross input errors
 */
I 28
int
E 28
readchar()
{
D 28
    register int	cnt, y, x;
    auto char		c;
E 28
I 28
	register int cnt;
	char c;
E 28
E 2

I 2
over:
D 28
    cnt = 0;
    while (read(0, &c, 1) <= 0)
D 19
	if (cnt++ > 100)	/* if we are getting infinite EOFs */
	    bye();		/* quit the game */
E 19
I 19
	if (cnt++ > 100) {	/* if we are getting infinite EOFs */
		bye();		/* quit the game */
		exit(1);
E 28
I 28
	cnt = 0;
	while (read(STDIN_FILENO, &c, sizeof(char)) <= 0)
		if (cnt++ > 100) {	/* if we are getting infinite EOFs */
			bye();		/* quit the game */
			exit(1);
		}
	if (c == CTRL('L')) {
		wrefresh(curscr);
		goto over;
E 28
	}
E 19
D 27
    if (c == CTRL(L)) {
E 27
I 27
D 28
    if (c == CTRL('L')) {
E 27
	wrefresh(curscr);
	goto over;
    }
D 9
    Hasread = TRUE;
E 9
    if (c == '\r')
	return '\n';
    else
	return c;
E 28
I 28
	if (c == '\r')
		return ('\n');
	else
		return (c);
E 28
}

/*
 * getline:
 *      Reads the next line up to '\n' or EOF.  Multiple spaces are
 *	compressed to one space; a space is inserted before a ','
 */
char *
getline()
{
D 28
    register char	*sp;
    register int	c, oy, ox;
I 9
    register WINDOW	*oscr;
E 28
I 28
	register char *sp;
	register int c, oy, ox;
	register WINDOW *oscr;
E 28
E 9

I 9
D 28
    oscr = stdscr;
    stdscr = Msgwin;
E 9
    getyx(stdscr, oy, ox);
    refresh();
    /*
     * loop reading in the string, and put it in a temporary buffer
     */
    for (sp = linebuf; (c = readchar()) != '\n'; clrtoeol(), refresh()) {
	if (c == -1)
	    continue;
	else if (c == erasechar()) {	/* process erase character */
	    if (sp > linebuf) {
		register int i;
E 28
I 28
	oscr = stdscr;
	stdscr = Msgwin;
	getyx(stdscr, oy, ox);
	refresh();
	/* loop reading in the string, and put it in a temporary buffer */
	for (sp = linebuf; (c = readchar()) != '\n'; clrtoeol(), refresh()) {
		if (c == -1)
			continue;
		else
			if (c == erasechar()) {	/* process erase character */
				if (sp > linebuf) {
					register int i;
E 28

D 28
		sp--;
		for (i = strlen(unctrl(*sp)); i; i--)
		    addch('\b');
	    }
	    continue;
E 28
I 28
					sp--;
					for (i = strlen(unctrl(*sp)); i; i--)
						addch('\b');
				}
				continue;
			} else
				if (c == killchar()) {	/* process kill
							 * character */
					sp = linebuf;
					move(oy, ox);
					continue;
				} else
					if (sp == linebuf && c == ' ')
						continue;
		if (sp >= &linebuf[LINESIZE - 1] || !(isprint(c) || c == ' '))
			putchar(CTRL('G'));
		else {
			if (islower(c))
				c = toupper(c);
			*sp++ = c;
			addstr(unctrl(c));
			Mpos++;
		}
E 28
	}
D 28
	else if (c == killchar()) {	/* process kill character */
	    sp = linebuf;
	    move(oy, ox);
	    continue;
	}
	else if (sp == linebuf && c == ' ')
	    continue;
	if (sp >= &linebuf[LINESIZE-1] || !(isprint(c) || c == ' '))
D 27
	    putchar(CTRL(G));
E 27
I 27
	    putchar(CTRL('G'));
E 27
	else {
	    if (islower(c))
		c = toupper(c);
	    *sp++ = c;
	    addstr(unctrl(c));
D 9
/*###366 [cc] Mpos undefined %%%*/
E 9
	    Mpos++;
	}
    }
    *sp = '\0';
I 9
    stdscr = oscr;
E 9
    return linebuf;
E 28
I 28
	*sp = '\0';
	stdscr = oscr;
	return (linebuf);
E 28
I 13
}

I 19
D 28
rint()
E 28
I 28
void
rint(signo)
	int signo;
E 28
{
	bye();
	exit(1);
}

E 19
/*
 * bye:
 *	Leave the program, cleaning things up as we go.
 */
I 28
void
E 28
bye()
{
	signal(SIGINT, SIG_IGN);
	mvcur(0, COLS - 1, LINES - 1, 0);
	fflush(stdout);
	endwin();
	putchar('\n');
D 19
	exit(1);
E 19
E 13
}
E 2
E 1
