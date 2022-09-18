h61533
s 00002/00002/00015
d D 8.1 93/06/01 23:15:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00012/00013
d D 5.1 91/02/25 15:46:13 bostic 4 3
c ANSI fixes, yank to rev 5.1, fix the copyright notices
e
s 00000/00000/00025
d D 1.3 90/06/22 18:55:17 kfall 3 2
c no delta
e
s 00019/00000/00006
d D 1.2 89/05/17 22:42:48 kfall 2 1
c add UCB header, and a couple of defs
e
s 00006/00000/00000
d D 1.1 88/12/12 20:55:06 kfall 1 0
c date and time created 88/12/12 20:55:06 by kfall
e
u
U
t
T
I 2
D 4
/*
E 4
I 4
/*-
E 4
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 4
 */

E 2
I 1
#define	APPEND_DB	0x01
I 2
#define	ABORT		0x02
E 2

I 2
#define	GOTKEY_MSG	"GOTKEY"
E 2

struct	keyfile_data {
	C_Block		kf_key;
};
E 1
