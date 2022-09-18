h42703
s 00002/00002/00030
d D 8.1 93/06/06 22:33:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00029
d D 3.5 90/06/06 21:46:06 bostic 5 4
c fix contrib notice (Edward Wang)
e
s 00001/00011/00028
d D 3.4 90/06/02 15:26:11 bostic 4 3
c new copyright notice
e
s 00002/00000/00037
d D 3.3 89/08/24 04:42:17 edward 3 2
c new compression algorithm
e
s 00002/00002/00035
d D 3.2 89/08/23 21:43:31 edward 2 1
c insert mode bug fix and cleanup
e
s 00037/00000/00000
d D 3.1 89/08/02 19:14:19 edward 1 0
c date and time created 89/08/02 19:14:19 by edward
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 5
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

struct xx {
D 2
	enum { xc_move, xc_scroll, xc_delchar, xc_inschar, xc_clear, xc_clreos,
		xc_clreol, xc_write } cmd;
E 2
I 2
	enum { xc_move, xc_scroll, xc_inschar, xc_insspace, xc_delchar,
		xc_clear, xc_clreos, xc_clreol, xc_write } cmd;
E 2
	int arg0;
	int arg1;
	int arg2;
	int arg3;
	char *buf;
	struct xx *link;
};

struct xx *xxalloc();

struct xx *xx_head, *xx_tail;
struct xx *xx_freelist;

char *xxbuf, *xxbufp, *xxbufe;
int xxbufsize;
I 3

#define char_sep '\0'
E 3
E 1
