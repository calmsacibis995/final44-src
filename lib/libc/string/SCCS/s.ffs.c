h46667
s 00002/00002/00026
d D 8.1 93/06/04 15:10:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00027
d D 5.5 92/10/04 13:08:47 bostic 5 4
c lint
e
s 00002/00000/00025
d D 5.4 90/05/17 12:05:34 bostic 4 3
c keep string.h and source in sync
e
s 00007/00017/00018
d D 5.3 90/05/15 13:58:36 bostic 3 2
c minor cleanup, use int, not long
e
s 00014/00003/00021
d D 5.2 88/06/27 18:03:48 bostic 2 1
c written by Kirk McKusick; add Berkeley specific copyright
e
s 00024/00000/00000
d D 5.1 87/01/27 16:02:48 mckusick 1 0
c new addition for portability
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1987 Regents of the University of California.
E 3
I 3
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
E 3
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif LIBC_SCCS and not lint
E 2
I 2
#endif /* LIBC_SCCS and not lint */
E 2

I 4
#include <string.h>

E 4
/*
 * ffs -- vax ffs instruction
 */
I 5
int
E 5
ffs(mask)
D 3
	register long mask;
E 3
I 3
	register int mask;
E 3
{
D 3
	register int cnt;
E 3
I 3
	register int bit;
E 3

	if (mask == 0)
		return(0);
D 3
	for (cnt = 1; !(mask & 1); cnt++)
E 3
I 3
	for (bit = 1; !(mask & 1); bit++)
E 3
		mask >>= 1;
D 3
	return(cnt);
E 3
I 3
	return(bit);
E 3
}
E 1
