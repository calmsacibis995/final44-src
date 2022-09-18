h60720
s 00024/00016/00015
d D 5.2 90/03/11 17:02:58 bostic 2 1
c add Berkeley specific copyright notice
e
s 00031/00000/00000
d D 5.1 90/03/11 16:53:40 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * lstFake.c --
 *	This is a file whose sole purpose is to force ranlib to
 *	place enough entries in the library's table of contents to
 *	prevent it (the table of contents) from looking like an object
 *	file. As of this writing, the table had 0410 (shared text) entries
 *	in it, so we define five junk variables to up the number beyond
 *	the range of the magic numbers.
D 2
 *
 * Copyright (c) 1988 by the Regents of the University of California
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California nor
 * Adam de Boor makes any representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 *
E 2
 */
D 2
#ifndef lint
static char *rcsid =
"$Id: lstFake.c,v 1.2 88/11/17 20:52:30 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

int _junk_one__ = 1;
int _junk_two__ = 2;
int _junk_three__ = 3;
int _junk_four__ = 4;
int _junk_five__ = 5;
E 1
