h01730
s 00002/00002/00013
d D 8.1 93/06/06 14:59:43 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00014
d D 5.3 90/06/01 16:55:38 bostic 3 2
c new copyright notice
e
s 00001/00001/00024
d D 5.2 90/03/06 11:19:42 bostic 2 1
c rename fast find code to locate
e
s 00008/00000/00000
d D 5.1 89/05/04 13:30:18 jak 1 0
c date and time created 89/05/04 13:30:18 by jak
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
/* Symbolic constants shared by find.c and code.c */
E 2
I 2
/* Symbolic constants shared by locate.c and code.c */
E 2

#define	NBG		128		/* number of bigrams considered */
#define	OFFSET		14		/* abs value of max likely diff */
#define	PARITY		0200		/* parity bit */
#define	SWITCH		30		/* switch code */
E 1
