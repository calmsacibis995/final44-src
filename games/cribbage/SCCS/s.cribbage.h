h48596
s 00002/00002/00084
d D 8.1 93/05/31 16:49:19 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00007/00035
d D 5.6 93/04/26 10:34:34 bostic 11 10
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00007/00000/00035
d D 5.5 93/02/03 17:28:47 torek 10 9
c more ANSI happiness for gcc2
e
s 00001/00011/00034
d D 5.4 90/06/01 13:05:20 bostic 9 8
c new copyright notice
e
s 00010/00005/00035
d D 5.3 88/06/18 14:39:23 bostic 8 7
c install approved copyright notice
e
s 00008/00002/00032
d D 5.2 88/03/10 16:30:12 bostic 7 6
c add Berkeley specific header, Ken Arnold says written @ Berkeley
e
s 00007/00001/00027
d D 5.1 85/05/30 19:46:58 mckusick 6 5
c Add copyright
e
s 00002/00000/00026
d D 1.4 83/05/19 12:22:05 arnold 5 4
c add sccs keywords
e
s 00000/00001/00026
d D 1.3 83/05/01 15:31:11 arnold 4 2
c make a scrolling region for cribbage
e
s 00021/00024/00003
d R 1.3 82/08/28 17:06:17 arnold 3 2
c reformatting and obvious optimization
e
s 00003/00001/00024
d D 1.2 82/08/24 18:34:00 arnold 2 1
c first "working" visual version
e
s 00025/00000/00000
d D 1.1 82/08/11 16:35:55 arnold 1 0
c date and time created 82/08/11 16:35:55 by arnold
e
u
U
t
T
I 5
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
/*
D 12
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 6

E 5
I 1
D 2

E 2
extern  CARD		deck[ CARDS ];		/* a deck */
extern  CARD		phand[ FULLHAND ];	/* player's hand */
extern  CARD		chand[ FULLHAND ];	/* computer's hand */
extern  CARD		crib[ CINHAND ];	/* the crib */
extern  CARD		turnover;		/* the starter */

extern  CARD		known[ CARDS ];		/* cards we have seen */
extern  int		knownum;		/* # of cards we know */

extern  int		pscore;			/* player's score */
extern  int		cscore;			/* comp's score */
extern  int		glimit;			/* points to win game */

extern  int		pgames;			/* player's games won */
extern  int		cgames;			/* comp's games won */
extern  int		gamecount;		/* # games played */
I 2
extern	int		Lastscore[2];		/* previous score for each */
E 2

extern  BOOLEAN		iwon;			/* if comp won last */
extern  BOOLEAN		explain;		/* player mistakes explained */
extern  BOOLEAN		rflag;			/* if all cuts random */
extern  BOOLEAN		quiet;			/* if suppress random mess */
I 2
D 4
extern  BOOLEAN		Hasread;		/* has had chance to read msg */
E 4
extern	BOOLEAN		playing;		/* currently playing game */
E 2

extern  char		expl[];			/* string for explanation */

I 10
D 11
#if __STDC__
void	msg(const char *fmt, ...);
void	addmsg(const char *fmt, ...);
#else
void	msg();
void	addmsg();
#endif
E 11
I 11
void	 addmsg __P((const char *, ...));
int	 adjust __P((CARD [], CARD));
int	 anymove __P((CARD [], int, int));
int	 anysumto __P((CARD [], int, int, int));
void	 bye __P((void));
int	 cchose __P((CARD [], int, int));
void	 cdiscard __P((BOOLEAN));
int	 chkscr __P((int *, int));
int	 comphand __P((CARD [], char *));
void	 cremove __P((CARD, CARD [], int));
int	 cut __P((BOOLEAN, int));
int	 deal __P((int));
void	 discard __P((BOOLEAN));
void	 do_wait __P((void));
void	 endmsg __P((void));
int	 eq __P((CARD, CARD));
int	 fifteens __P((CARD [], int));
void	 game __P((void));
void	 gamescore __P((void));
char	*getline __P((void));
int	 getuchar __P((void));
int	 incard __P((CARD *));
int	 infrom __P((CARD [], int, char *));
void	 instructions __P((void));
int	 isone __P((CARD, CARD [], int));
void	 makeboard __P((void));
void	 makedeck __P((CARD []));
void	 makeknown __P((CARD [], int));
void	 msg __P((const char *, ...));
int	 msgcard __P((CARD, BOOLEAN));
int	 msgcrd __P((CARD, BOOLEAN, char *, BOOLEAN));
int	 number __P((int, int, char *));
int	 numofval __P((CARD [], int, int));
int	 pairuns __P((CARD [], int));
int	 peg __P((BOOLEAN));
int	 pegscore __P((CARD, CARD [], int, int));
int	 playhand __P((BOOLEAN));
int	 plyrhand __P((CARD [], char *));
void	 prcard __P((WINDOW *, int, int, CARD, BOOLEAN));
void	 prcrib __P((BOOLEAN, BOOLEAN));
void	 prhand __P((CARD [], int, WINDOW *, BOOLEAN));
void	 printcard __P((WINDOW *, int, CARD, BOOLEAN));
void	 prpeg __P((int, int, BOOLEAN));
void	 prtable __P((int));
int	 readchar __P((void));
void	 rint __P((int));
int	 score __P((BOOLEAN));
int	 scorehand __P((CARD [], CARD, int, BOOLEAN, BOOLEAN));
void	 shuffle __P((CARD []));
void	 sorthand __P((CARD [], int));
void	 wait_for __P((int));
E 11
E 10
E 1
