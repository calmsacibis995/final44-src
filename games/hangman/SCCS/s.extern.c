h52276
s 00002/00002/00046
d D 8.1 93/05/31 17:22:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00047
d D 5.3 90/06/01 13:06:54 bostic 3 2
c new copyright notice
e
s 00011/00006/00047
d D 5.2 88/06/18 14:44:33 bostic 2 1
c install approved copyright notice
e
s 00053/00000/00000
d D 5.1 87/12/22 13:08:06 bostic 1 0
c date and time created 87/12/22 13:08:06 by bostic
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
 * Copyright (c) 1983 Regents of the University of California.
E 2
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"hangman.h"

bool	Guessed[26];

char	Word[BUFSIZ],
	Known[BUFSIZ],
	*Noose_pict[] = {
		"     ______",
		"     |    |",
		"     |",
		"     |",
		"     |",
		"     |",
		"   __|_____",
		"   |      |___",
		"   |_________|",
		NULL
	};

int	Errors,
	Wordnum = 0;

double	Average = 0.0;

ERR_POS	Err_pos[MAXERRS] = {
	{  2, 10, 'O' },
	{  3, 10, '|' },
	{  4, 10, '|' },
	{  5,  9, '/' },
	{  3,  9, '/' },
	{  3, 11, '\\' },
	{  5, 11, '\\' }
};

FILE	*Dict = NULL;

off_t	Dict_size;
E 1
