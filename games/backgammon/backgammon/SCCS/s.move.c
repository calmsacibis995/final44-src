h28625
s 00002/00002/00523
d D 8.1 93/05/31 16:09:00 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00521
d D 5.7 92/08/31 14:08:49 elan 9 8
c Fixed return value buf in nextfree().
e
s 00001/00011/00524
d D 5.6 90/06/01 12:56:40 bostic 8 7
c new copyright notice
e
s 00003/00003/00532
d D 5.5 89/09/26 11:33:19 bostic 7 6
c bcopy conflicts with the C library; bug report 4.3BSD-tahoe/games/4
e
s 00010/00005/00525
d D 5.4 88/06/18 19:47:13 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00520
d D 5.3 88/02/16 11:15:13 bostic 5 4
c authored by Alan Char; add Berkeley specific header
c fix random casting problems
e
s 00009/00009/00515
d D 5.2 87/12/26 13:20:28 bostic 4 3
c pointers use 0, not -1; fix for ANSI C
e
s 00009/00001/00515
d D 5.1 85/05/29 11:35:24 dist 3 2
c Add copyright
e
s 00000/00000/00516
d D 4.1 82/05/11 15:02:16 rrh 2 1
c bringing to release 4.1
e
s 00516/00000/00000
d D 1.1 82/05/11 14:53:50 rrh 1 0
c date and time created 82/05/11 14:53:50 by rrh
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
D 10
 * Copyright (c) 1980 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 3

#include "back.h"

#ifdef DEBUG
#include <stdio.h>
FILE	*trace;
static char	tests[20];
#endif

struct BOARD  {				/* structure of game position */
	int	b_board[26];			/* board position */
	int	b_in[2];			/* men in */
	int	b_off[2];			/* men off */
	int	b_st[4], b_fn[4];		/* moves */

	struct BOARD	*b_next;		/* forward queue pointer */
};

D 4
struct BOARD *freeq = -1;
struct BOARD *checkq = -1;
E 4
I 4
struct BOARD *freeq = 0;
struct BOARD *checkq = 0;
E 4
struct BOARD *bsave();
struct BOARD *nextfree();

					/* these variables are values for the
					 * candidate move */
static int	ch;				/* chance of being hit */
static int	op;				/* computer's open men */
static int	pt;				/* comp's protected points */
static int	em;				/* farthest man back */
static int	frc;				/* chance to free comp's men */
static int	frp;				/* chance to free pl's men */

					/* these values are the values for the
					 * move chosen (so far) */
static int	chance;				/* chance of being hit */
static int	openmen;			/* computer's open men */
static int	points;				/* comp's protected points */
static int	endman;				/* farthest man back */
static int	barmen;				/* men on bar */
static int	menin;				/* men in inner table */
static int	menoff;				/* men off board */
static int	oldfrc;				/* chance to free comp's men */
static int	oldfrp;				/* chance to free pl's men */

static int	cp[5];				/* candidate start position */
static int	cg[5];				/* candidate finish position */

static int	race;				/* game reduced to a race */

move (okay)
int	okay;					/* zero if first move */
{
	register int	i;		/* index */
	register int	l;		/* last man */

	if (okay)  {
						/* see if comp should double */
		if (gvalue < 64 && dlast != cturn && dblgood())  {
			writel (*Colorptr);
			dble();			    /* double */
						    /* return if declined */
			if (cturn != 1 && cturn != -1)
				return;
		}
		roll();
	}

	race = 0;
	for (i = 0; i < 26; i++)  {
		if (board[i] < 0)
			l = i;
	}
	for (i = 0; i < l; i++)  {
		if (board[i] > 0)
			break;
	}
	if (i == l)
		race = 1;

						/* print roll */
	if (tflag)
		curmove (cturn == -1? 18: 19,0);
	writel (*Colorptr);
	writel (" rolls ");
	writec (D0+'0');
	writec (' ');
	writec (D1+'0');
						/* make tty interruptable
						 * while thinking */
	if (tflag)
		cline();
	fixtty (noech);

						/* find out how many moves */
	mvlim = movallow();
	if (mvlim == 0)  {
		writel (" but cannot use it.\n");
		nexturn();
		fixtty (raw);
		return;
	}

						/* initialize */
	for (i = 0; i < 4; i++)
		cp[i] = cg[i] = 0;

						/* strategize */
	trymove (0,0);
	pickmove();

						/* print move */
	writel (" and moves ");
	for (i = 0; i < mvlim; i++)  {
		if (i > 0)
			writec (',');
		wrint (p[i] = cp[i]);
		writec ('-');
		wrint (g[i] = cg[i]);
		makmove (i);
	}
	writec ('.');

						/* print blots hit */
	if (tflag)
		curmove (20,0);
	else
		writec ('\n');
	for (i = 0; i < mvlim; i++)
		if (h[i])
			wrhit(g[i]);
						/* get ready for next move */
	nexturn();
	if (!okay)  {
		buflush();
		sleep (3);
	}
	fixtty (raw);				/* no more tty interrupt */
}

trymove (mvnum,swapped)
register int	mvnum;				/* number of move (rel zero) */
int		swapped;			/* see if swapped also tested */

{
	register int	pos;			/* position on board */
	register int	rval;			/* value of roll */

						/* if recursed through all dice
						 * values, compare move */
	if (mvnum == mvlim)  {
		binsert (bsave());
		return;
	}

						/* make sure dice in always
						 * same order */
	if (d0 == swapped)
		swap;
						/* choose value for this move */
	rval = dice[mvnum != 0];

						/* find all legitimate moves */
	for (pos = bar; pos != home; pos += cturn)  {
						/* fix order of dice */
		if (d0 == swapped)
			swap;
						/* break if stuck on bar */
		if (board[bar] != 0 && pos != bar)
			break;
						/* on to next if not occupied */
		if (board[pos]*cturn <= 0)
			continue;
						/* set up arrays for move */
		p[mvnum] = pos;
		g[mvnum] = pos+rval*cturn;
		if (g[mvnum]*cturn >= home)  {
			if (*offptr < 0)
				break;
			g[mvnum] = home;
		}
						/* try to move */
		if (makmove (mvnum))
			continue;
		else
			trymove (mvnum+1,2);
						/* undo move to try another */
		backone (mvnum);
	}

						/* swap dice and try again */
	if ((!swapped) && D0 != D1)
		trymove (0,1);
}

struct BOARD *
bsave ()  {
	register int	i;		/* index */
	struct BOARD	*now;		/* current position */

	now = nextfree ();		/* get free BOARD */

					/* store position */
	for (i = 0; i < 26; i++)
		now->b_board[i] = board[i];
	now->b_in[0] = in[0];
	now->b_in[1] = in[1];
	now->b_off[0] = off[0];
	now->b_off[1] = off[1];
	for (i = 0; i < mvlim; i++)  {
		now->b_st[i] = p[i];
		now->b_fn[i] = g[i];
	}
	return (now);
}

binsert (new)
struct BOARD	*new;					/* item to insert */
{
	register struct BOARD	*p = checkq;		/* queue pointer */
	register int		result;			/* comparison result */

D 4
	if (p == -1)  {				/* check if queue empty */
E 4
I 4
	if (p == 0)  {				/* check if queue empty */
E 4
		checkq = p = new;
D 4
		p->b_next = -1;
E 4
I 4
		p->b_next = 0;
E 4
		return;
	}

	result = bcomp (new,p);			/* compare to first element */
	if (result < 0)  {				/* insert in front */
		new->b_next = p;
		checkq = new;
		return;
	}
	if (result == 0)  {				/* duplicate entry */
		mvcheck (p,new);
		makefree (new);
		return;
	}

D 4
	while (p->b_next != -1)  {		/* traverse queue */
E 4
I 4
	while (p->b_next != 0)  {		/* traverse queue */
E 4
		result = bcomp (new,p->b_next);
		if (result < 0)  {			/* found place */
			new->b_next = p->b_next;
			p->b_next = new;
			return;
		}
		if (result == 0)  {			/* duplicate entry */
			mvcheck (p->b_next,new);
			makefree (new);
			return;
		}
		p = p->b_next;
	}
						/* place at end of queue */
	p->b_next = new;
D 4
	new->b_next = -1;
E 4
I 4
	new->b_next = 0;
E 4
}

bcomp (a,b)
struct BOARD	*a;
struct BOARD	*b;
{
	register int	*aloc = a->b_board;	/* pointer to board a */
	register int	*bloc = b->b_board;	/* pointer to board b */
	register int	i;			/* index */
	int		result;			/* comparison result */

	for (i = 0; i < 26; i++)  {		/* compare boards */
		result = cturn*(aloc[i]-bloc[i]);
		if (result)
			return (result);		/* found inequality */
	}
	return (0);				/* same position */
}

mvcheck (incumbent,candidate)
register struct BOARD 	*incumbent;
register struct BOARD 	*candidate;
{
	register int	i;
	register int	result;

	for (i = 0; i < mvlim; i++)  {
		result = cturn*(candidate->b_st[i]-incumbent->b_st[i]);
		if (result > 0)
			return;
		if (result < 0)
			break;
	}
	if (i == mvlim)
		return;
	for (i = 0; i < mvlim; i++)  {
		incumbent->b_st[i] = candidate->b_st[i];
		incumbent->b_fn[i] = candidate->b_fn[i];
	}
}

makefree (dead)
struct BOARD	*dead;			/* dead position */
{
	dead->b_next = freeq;			/* add to freeq */
	freeq = dead;
}

struct BOARD *
nextfree ()  {
	struct BOARD	*new;

D 4
	if (freeq == -1)  {
E 4
I 4
	if (freeq == 0)  {
E 4
D 5
		new = calloc (1,sizeof (struct BOARD));
E 5
I 5
		new = (struct BOARD *)calloc (1,sizeof (struct BOARD));
E 5
		if (new == 0)  {
			writel ("\nOut of memory\n");
			getout();
		}
D 4
		new->b_next = -1;
E 4
I 4
		new->b_next = 0;
E 4
D 9
		return (new);
E 9
I 9
	} else {
		new = freeq;
		freeq = freeq->b_next;
E 9
	}
D 9

	new = freeq;
	freeq = freeq->b_next;
E 9
I 9
	return (new);
E 9
}

pickmove ()  {
						/* current game position */
	register struct BOARD	*now = bsave();
	register struct BOARD	*next;		/* next move */

#ifdef DEBUG
	if (trace == NULL)
		trace = fopen ("bgtrace","w");
	fprintf (trace,"\nRoll:  %d %d%s\n",D0,D1,race? " (race)": "");
	fflush (trace);
#endif
	do  {				/* compare moves */
D 7
		bcopy (checkq);
E 7
I 7
		boardcopy (checkq);
E 7
		next = checkq->b_next;
		makefree (checkq);
		checkq = next;
		movcmp();
D 4
	} while (checkq != -1);
E 4
I 4
	} while (checkq != 0);
E 4

D 7
	bcopy (now);
E 7
I 7
	boardcopy (now);
E 7
}

D 7
bcopy (s)
E 7
I 7
boardcopy (s)
E 7
register struct BOARD	*s;			/* game situation */
{
	register int	i;			/* index */

	for (i = 0; i < 26; i++)
		board[i] = s->b_board[i];
	for (i = 0; i < 2; i++)  {
		in[i] = s->b_in[i];
		off[i] = s->b_off[i];
	}
	for (i = 0; i < mvlim; i++)  {
		p[i] = s->b_st[i];
		g[i] = s->b_fn[i];
	}
}

movcmp ()  {
	register int	i;
	register int	c;

#ifdef DEBUG
	if (trace == NULL)
		trace = fopen ("bgtrace","w");
#endif

	odds (0,0,0);
	if (!race)  {
		ch = op = pt = 0;
		for (i = 1; i < 25; i++)  {
			if (board[i] == cturn)
				ch = canhit (i,1);
				op += abs (bar-i);
		}
		for (i = bar+cturn; i != home; i += cturn)
			if (board[i]*cturn > 1)
				pt += abs(bar-i);
		frc = freemen (bar)+trapped (bar,cturn);
		frp = freemen (home)+trapped (home,-cturn);
	}
	for (em = bar; em != home; em += cturn)
		if (board[em]*cturn > 0)
			break;
	em = abs(home-em);
#ifdef DEBUG
	fputs ("Board: ",trace);
	for (i = 0; i < 26; i++)
		fprintf (trace, " %d",board[i]);
	if (race)
		fprintf (trace,"\n\tem = %d\n",em);
	else
		fprintf (trace,
			"\n\tch = %d, pt = %d, em = %d, frc = %d, frp = %d\n",
			ch,pt,em,frc,frp);
	fputs ("\tMove: ",trace);
	for (i = 0; i < mvlim; i++)
		fprintf (trace," %d-%d",p[i],g[i]);
	fputs ("\n",trace);
	fflush (trace);
	strcpy (tests,"");
#endif
	if ((cp[0] == 0 && cg[0] == 0) || movegood())  {
#ifdef DEBUG
		fprintf (trace,"\t[%s] ... wins.\n",tests);
		fflush (trace);
#endif
		for (i = 0; i < mvlim; i++)  {
			cp[i] = p[i];
			cg[i] = g[i];
		}
		if (!race)  {
			chance = ch;
			openmen = op;
			points = pt;
			endman = em;
			barmen = abs(board[home]);
			oldfrc = frc;
			oldfrp = frp;
		}
		menin = *inptr;
		menoff = *offptr;
	}
#ifdef DEBUG
	else  {
		fprintf (trace,"\t[%s] ... loses.\n",tests);
		fflush (trace);
	}
#endif
}

movegood ()  {
	register int	n;

	if (*offptr == 15)
		return (1);
	if (menoff == 15)
		return (0);
	if (race)  {
#ifdef DEBUG
		strcat (tests,"o");
#endif
		if (*offptr-menoff)
			return (*offptr > menoff);
#ifdef DEBUG
		strcat (tests,"e");
#endif
		if (endman-em)
			return (endman > em);
#ifdef DEBUG
		strcat (tests,"i");
#endif
		if (menin == 15)
			return (0);
		if (*inptr == 15)
			return (1);
#ifdef DEBUG
		strcat (tests,"i");
#endif
		if (*inptr-menin)
			return (*inptr > menin);
		return (rnum(2));
	} else  {
		n = barmen-abs(board[home]);
#ifdef DEBUG
		strcat (tests,"c");
#endif
		if (abs(chance-ch)+25*n > rnum(150))
			return (n? (n < 0): (ch < chance));
#ifdef DEBUG
		strcat (tests,"o");
#endif
		if (*offptr-menoff)
			return (*offptr > menoff);
#ifdef DEBUG
		strcat (tests,"o");
#endif
		if (abs(openmen-op) > 7+rnum(12))
			return (openmen > op);
#ifdef DEBUG
		strcat (tests,"b");
#endif
		if (n)
			return (n < 0);
#ifdef DEBUG
		strcat (tests,"e");
#endif
		if (abs(endman-em) > rnum(2))
			return (endman > em);
#ifdef DEBUG
		strcat (tests,"f");
#endif
		if (abs(frc-oldfrc) > rnum(2))
			return (frc < oldfrc);
#ifdef DEBUG
		strcat (tests,"p");
#endif
		if (abs(n = pt-points) > rnum(4))
			return (n > 0);
#ifdef DEBUG
		strcat (tests,"i");
#endif
		if (*inptr-menin)
			return (*inptr > menin);
#ifdef DEBUG
		strcat (tests,"f");
#endif
		if (abs(frp-oldfrp) > rnum(2))
			return (frp > oldfrp);
		return (rnum(2));
	}
}
E 1
