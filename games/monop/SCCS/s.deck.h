h45332
s 00002/00002/00020
d D 8.1 93/05/31 17:26:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00021
d D 5.3 90/06/01 13:11:05 bostic 3 2
c new copyright notice
e
s 00011/00006/00021
d D 5.2 88/06/18 14:54:30 bostic 2 1
c install approved copyright notice
e
s 00027/00000/00000
d D 5.1 88/01/02 20:53:22 bostic 1 0
c date and time created 88/01/02 20:53:22 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 4
 * Copyright (c) 1980 Regents of the University of California.
E 2
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

# define	bool	char

# define	CC_D	deck[0]
# define	CH_D	deck[1]

struct dk_st {			/* deck description structure		*/
	int	num_cards;		/* number of cards in deck	*/
	int	last_card;		/* number of last card picked	*/
	bool	gojf_used;		/* set if gojf card out of deck	*/
	long	*offsets;		/* offests for start of cards	*/
};

typedef struct dk_st	DECK;
E 1
