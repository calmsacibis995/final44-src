h51623
s 00002/00002/00051
d D 8.1 93/06/06 15:37:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00052
d D 5.4 90/06/01 17:05:23 bostic 4 3
c new copyright notice
e
s 00001/00003/00063
d D 5.3 88/11/22 16:51:56 bostic 3 2
c less -> more
e
s 00002/00004/00064
d D 5.2 88/07/25 12:05:30 bostic 2 1
c update copyright notice
e
s 00068/00000/00000
d D 5.1 88/07/21 18:53:29 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 5
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 2
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 2
 * by the University of California, Berkeley.  The name of the
E 2
I 2
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 2
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Routines dealing with getting input from the keyboard (i.e. from the user).
 */

D 3
#include "less.h"
E 3
I 3
#include <less.h>
E 3

static int tty;

/*
 * Open keyboard for input.
 * (Just use file descriptor 2.)
 */
D 3
	public void
E 3
open_getchr()
{
	tty = 2;
}

/*
 * Get a character from the keyboard.
 */
D 3
	public int
E 3
getchr()
{
	char c;
	int result;

	do
	{
		result = iread(tty, &c, 1);
		if (result == READ_INTR)
			return (READ_INTR);
		if (result < 0)
		{
			/*
			 * Don't call error() here,
			 * because error calls getchr!
			 */
			quit();
		}
	} while (result != 1);
	return (c & 0177);
}
E 1
