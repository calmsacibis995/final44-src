h24505
s 00002/00002/00028
d D 8.1 93/05/31 17:54:10 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00027
d D 5.2 92/12/23 10:16:47 bostic 2 1
c update copyright notice with contrib notice
e
s 00027/00000/00000
d D 5.1 92/12/22 11:50:41 bostic 1 0
c date and time created 92/12/22 11:50:41 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Chris Torek and Darren F. Provine.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Capabilities from TERMCAP (used in the score code).
 */
char *SEstr;			/* end standout mode */
char *SOstr;			/* begin standout mode */

/*
 * putpad() is for padded strings with count=1.
 */
#define	putpad(s)	tputs(s, 1, put)

int	put __P((int));		/* just calls putchar; for tputs */
void	scr_clear __P((void));
void	scr_end __P((void));
void	scr_init __P((void));
void	scr_msg __P((char *, int));
void	scr_set __P((void));
void	scr_update __P((void));
E 1
