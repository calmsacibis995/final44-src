h23960
s 00005/00005/00033
d D 8.1 93/05/31 17:25:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00037
d D 5.4 90/06/01 13:08:39 bostic 4 3
c new copyright notice
e
s 00010/00006/00038
d D 5.3 88/06/18 19:38:34 bostic 3 2
c install approved copyright notice
e
s 00016/00003/00028
d D 5.2 87/12/29 17:17:22 bostic 2 1
c Berkeley header
e
s 00031/00000/00000
d D 5.1 86/11/26 13:36:34 bostic 1 0
c date and time created 86/11/26 13:36:34 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

#ifndef lint
I 2
D 5
char copyright[] =
"%Z% Copyright (c) 1982 Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1982, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
D 3

E 3
E 2

# define	DEBUG

/*
 * @(#)table.c	1.1 (Berkeley) 4/1/82
 */

# include	"mille.h"

main() {

	reg int	i, j, count;

	printf("   %16s -> %5s %5s %4s %s\n", "Card", "cards", "count", "need", "opposite");
	for (i = 0; i < NUM_CARDS - 1; i++) {
		for (j = 0, count = 0; j < DECK_SZ; j++)
			if (Deck[j] == i)
				count++;
		printf("%2d %16s -> %5d %5d %4d %s\n", i, C_name[i], Numcards[i], count, Numneed[i], C_name[opposite(i)]);
	}
}

E 1
