h24984
s 00002/00002/00121
d D 8.1 93/05/31 16:49:11 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00069/00081/00054
d D 5.6 93/04/26 10:34:31 bostic 11 10
c ANSI C, prototypes, lint, reformatting to KNF
c still doesn't work, but at least it compiles cleanly
e
s 00001/00001/00134
d D 5.5 91/02/28 13:08:58 bostic 10 9
c ANSI
e
s 00001/00011/00134
d D 5.4 90/06/01 13:05:03 bostic 9 8
c new copyright notice
e
s 00010/00005/00135
d D 5.3 88/06/18 14:39:19 bostic 8 7
c install approved copyright notice
e
s 00009/00003/00131
d D 5.2 88/03/10 16:31:48 bostic 7 6
c add Berkeley specific header, Ken Arnold says written @ Berkeley
e
s 00009/00001/00125
d D 5.1 85/05/30 19:43:22 mckusick 6 5
c Add copyright
e
s 00001/00000/00125
d D 1.4 83/05/19 12:20:56 arnold 5 4
c add sccs keywords
e
s 00013/00016/00112
d D 1.3 82/08/31 23:00:19 arnold 4 2
c speed up sorthand
e
s 00067/00082/00046
d R 1.3 82/08/28 17:06:01 arnold 3 2
c reformatting and obvious optimization
e
s 00001/00001/00127
d D 1.2 82/08/24 18:33:42 arnold 2 1
c first "working" visual version
e
s 00128/00000/00000
d D 1.1 82/08/11 16:35:48 arnold 1 0
c date and time created 82/08/11 16:35:48 by arnold
e
u
U
t
T
I 5
D 6
static char	*sccsid = "%W% (Berkeley) %G%";
E 6
I 6
D 11
/*
 * Copyright (c) 1980 Regents of the University of California.
E 11
I 11
/*-
D 12
 * Copyright (c) 1980 The Regents of the University of California.
E 11
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 6
E 5
I 1

D 11
#include	<stdio.h>
#include	"deck.h"
E 11
I 11
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
E 11

I 11
#include "deck.h"
#include "cribbage.h"
E 11

I 11

E 11
/*
D 11
 * initialize a deck of cards to contain one of each type
E 11
I 11
 * Initialize a deck of cards to contain one of each type.
E 11
 */
D 11

makedeck( d )

    CARD	d[];
E 11
I 11
void
makedeck(d)
	CARD    d[];
E 11
{
D 11
	register  int		i, j, k;
	long			time();
E 11
I 11
	register int i, j, k;
E 11

D 11
	i = time( (long *) 0 );
	i = ( (i&0xff) << 8 ) | ( (i >> 8)&0xff ) | 1;
	srand( i );
E 11
I 11
	i = time(NULL);
	i = ((i & 0xff) << 8) | ((i >> 8) & 0xff) | 1;
	srand(i);
E 11
	k = 0;
D 11
	for( i = 0; i < RANKS; i++ )  {
	    for( j = 0; j < SUITS; j++ )  {
		d[k].suit = j;
		d[k++].rank = i;
	    }
	}
E 11
I 11
	for (i = 0; i < RANKS; i++)
		for (j = 0; j < SUITS; j++) {
			d[k].suit = j;
			d[k++].rank = i;
		}
E 11
}

D 11


E 11
/*
D 11
 * given a deck of cards, shuffle it -- i.e. randomize it
 * see Knuth, vol. 2, page 125
E 11
I 11
 * Given a deck of cards, shuffle it -- i.e. randomize it
 * see Knuth, vol. 2, page 125.
E 11
 */
D 11

shuffle( d )

    CARD	d[];
E 11
I 11
void
shuffle(d)
	CARD d[];
E 11
{
D 11
	register  int		j, k;
	CARD			c;
E 11
I 11
	register int j, k;
	CARD c;
E 11

D 11
	for( j = CARDS; j > 0; --j )  {
	    k = ( rand() >> 4 ) % j;		/* random 0 <= k < j */
	    c = d[j - 1];			/* exchange (j - 1) and k */
	    d[j - 1] = d[k];
	    d[k] = c;
E 11
I 11
	for (j = CARDS; j > 0; --j) {
		k = (rand() >> 4) % j;		/* random 0 <= k < j */
		c = d[j - 1];			/* exchange (j - 1) and k */
		d[j - 1] = d[k];
		d[k] = c;
E 11
	}
}

D 11


E 11
/*
 * return true if the two cards are equal...
 */
D 11

eq( a, b )

    CARD		a, b;
E 11
I 11
int
eq(a, b)
	CARD a, b;
E 11
{
D 11
	return(  ( a.rank == b.rank )  &&  ( a.suit == b.suit )  );
E 11
I 11
	return ((a.rank == b.rank) && (a.suit == b.suit));
E 11
}

D 11


E 11
/*
 * isone returns TRUE if a is in the set of cards b
 */
D 11

isone( a, b, n )

    CARD		a, b[];
    int			n;
E 11
I 11
int
isone(a, b, n)
	CARD a, b[];
	int n;
E 11
{
D 11
	register  int		i;
E 11
I 11
	register int i;
E 11

D 11
	for( i = 0; i < n; i++ )  {
	    if(  eq( a, b[i] )   )  return( TRUE );
	}
	return( FALSE );
E 11
I 11
	for (i = 0; i < n; i++)
		if (eq(a, b[i]))
			return (TRUE);
	return (FALSE);
E 11
}

D 11


E 11
/*
 * remove the card a from the deck d of n cards
 */
D 11

D 10
remove( a, d, n )
E 10
I 10
cremove( a, d, n )
E 10

    CARD		a, d[];
    int			n;
E 11
I 11
void
cremove(a, d, n)
	CARD a, d[];
	int n;
E 11
{
D 11
	register  int		i, j;
E 11
I 11
	register int i, j;
E 11

D 11
	j = 0;
	for( i = 0; i < n; i++ )  {
	    if(  !eq( a, d[i] )  )  d[j++] = d[i];
	}
D 2
	if(  j < n  )  d[j].suit = d[j].rank = -1;
E 2
I 2
	if(  j < n  )  d[j].suit = d[j].rank = EMPTY;
E 11
I 11
	for (i = j = 0; i < n; i++)
		if (!eq(a, d[i]))
			d[j++] = d[i];
	if (j < n)
		d[j].suit = d[j].rank = EMPTY;
E 11
E 2
}

D 11


E 11
/*
D 4
 * sorthand sorts a hand of n cards
E 4
I 4
 * sorthand:
 *	Sort a hand of n cards
E 4
 */
I 11
void
E 11
D 4

sorthand( h, n )

    CARD		h[];
    int			n;
E 4
I 4
sorthand(h, n)
D 11
register CARD		h[];
int			n;
E 11
I 11
	register CARD h[];
	int n;
E 11
E 4
{
D 4
	register  int		i, j;
E 4
I 4
D 11
	register CARD		*cp, *endp;
E 4
	CARD			c;
E 11
I 11
	register CARD *cp, *endp;
	CARD c;
E 11

D 4
	for( i = 0; i < (n - 1); i++ )  {
	    for( j = (i + 1); j < n; j++ )  {
		if(  ( h[j].rank < h[i].rank )  ||
		     ( h[j].rank == h[i].rank && h[j].suit < h[i].suit )  )  {
		    c = h[i];
		    h[i] = h[j];
		    h[j] = c;
E 4
I 4
	for (endp = &h[n]; h < endp - 1; h++)
D 11
	    for (cp = h + 1; cp < endp; cp++)
		if ((cp->rank < h->rank) ||
		     (cp->rank == h->rank && cp->suit < h->suit)) {
		    c = *h;
		    *h = *cp;
		    *cp = c;
E 4
		}
E 11
I 11
		for (cp = h + 1; cp < endp; cp++)
			if ((cp->rank < h->rank) ||
			    (cp->rank == h->rank && cp->suit < h->suit)) {
				c = *h;
				*h = *cp;
				*cp = c;
			}
E 11
D 4
	    }
	}
E 4
}
D 11

E 11
E 1
