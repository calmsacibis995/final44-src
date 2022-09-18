h14866
s 00002/00002/00024
d D 8.1 93/06/04 16:52:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00026
d D 5.2 92/07/03 00:24:01 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00026/00000/00000
d D 5.1 92/06/22 18:08:41 bostic 1 0
c date and time created 92/06/22 18:08:41 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * termcap.h: I cannot find those in any include files...
 */
#ifndef _h_termcap
#define _h_termcap

int   tgetent	__P((char *, char *));
char *tgetstr	__P((char *, char **));
int   tgetflag	__P((char *));
int   tgetnum	__P((char *));
char *tgoto	__P((char *, int, int));
char *tputs	__P((char *, int, void (*)(int)));

#endif /* _h_termcap */
E 1
