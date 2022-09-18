h25353
s 00002/00002/00051
d D 8.1 93/05/31 17:22:48 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00053
d D 5.6 93/02/03 17:17:36 torek 6 5
c rm private bogus abs()
e
s 00001/00001/00054
d D 5.5 91/02/28 13:14:10 bostic 5 4
c ANSI
e
s 00001/00011/00054
d D 5.4 90/06/01 13:07:14 bostic 4 3
c new copyright notice
e
s 00001/00001/00064
d D 5.3 90/01/02 14:08:57 bostic 3 2
c extract absolute pathnames
e
s 00011/00006/00054
d D 5.2 88/06/18 14:44:36 bostic 2 1
c install approved copyright notice
e
s 00060/00000/00000
d D 5.1 87/12/22 13:07:46 bostic 1 0
c date and time created 87/12/22 13:07:46 by bostic
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
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 *
 *	%W% (Berkeley) %G%
 */

# include	<curses.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<ctype.h>
# include	<signal.h>
I 3
# include	"pathnames.h"
E 3

# define	MINLEN	6
# define	MAXERRS	7
D 3
# define	DICT	"/usr/dict/words"
E 3

# define	MESGY	12
# define	MESGX	0
# define	PROMPTY	11
# define	PROMPTX	0
# define	KNOWNY	10
# define	KNOWNX	1
# define	NUMBERY	4
# define	NUMBERX	(COLS - 1 - 26)
# define	AVGY	5
# define	AVGX	(COLS - 1 - 26)
# define	GUESSY	2
# define	GUESSX	(COLS - 1 - 26)


typedef struct {
	short	y, x;
	char	ch;
} ERR_POS;

extern bool	Guessed[];

extern char	Word[], Known[], *Noose_pict[];

extern int	Errors, Wordnum;

extern double	Average;

extern ERR_POS	Err_pos[];

extern FILE	*Dict;

extern off_t	Dict_size;

D 5
int	die();
E 5
I 5
void	die();
E 5
D 6

off_t	abs();
E 6
E 1
