h57785
s 00002/00002/00017
d D 8.1 93/05/31 17:56:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00018
d D 5.4 90/06/01 13:23:57 bostic 6 5
c new copyright notice
e
s 00010/00005/00019
d D 5.3 88/06/18 15:07:40 bostic 5 4
c install approved copyright notice
e
s 00008/00002/00016
d D 5.2 88/05/05 18:33:57 bostic 4 2
c written by Eric Allman; add Berkeley header
e
s 00001/00001/00017
d R 5.2 86/01/29 16:30:05 mckusick 3 2
c add copyright
e
s 00007/00001/00011
d D 5.1 85/05/30 09:07:32 dist 2 1
c Add copyright
e
s 00012/00000/00000
d D 4.1 83/03/23 15:25:36 mckusick 1 0
c date and time created 83/03/23 15:25:36 by mckusick
e
u
U
t
T
I 1
D 2
/*	%W%	(Berkeley)	%E%	*/
E 2
I 2
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 2

struct cvntab		/* used for getcodpar() paramater list */
{
	char	*abrev;
	char	*full;
	int	(*value)();
	int	value2;
};

extern double		getfltpar();
extern struct cvntab	*getcodpar();
E 1
