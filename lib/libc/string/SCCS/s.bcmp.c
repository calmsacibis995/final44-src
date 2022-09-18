h63121
s 00002/00002/00031
d D 8.1 93/06/04 15:10:06 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00032
d D 5.7 92/10/04 13:08:46 bostic 7 6
c lint
e
s 00005/00002/00027
d D 5.6 91/02/24 13:57:42 bostic 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00028
d D 5.5 91/02/24 13:20:37 bostic 5 4
c bcmp, bzero take void *, not char *
e
s 00001/00011/00028
d D 5.4 90/06/01 14:44:49 bostic 4 3
c new copyright notice
e
s 00004/00002/00035
d D 5.3 90/05/16 16:02:15 bostic 3 2
c takes a size_t as argument
e
s 00014/00003/00023
d D 5.2 88/07/21 11:31:55 bostic 2 1
c add Berkeley specific copyright; written by Robert Elz
e
s 00026/00000/00000
d D 5.1 87/01/27 16:02:45 mckusick 1 0
c new addition for portability
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1987 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
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

I 3
#include <string.h>

E 3
/*
 * bcmp -- vax cmpc3 instruction
 */
I 7
int
E 7
bcmp(b1, b2, length)
D 5
	register char *b1, *b2;
E 5
I 5
D 6
	register void *b1, *b2;
E 6
I 6
	const void *b1, *b2;
E 6
E 5
D 3
	register int length;
E 3
I 3
	register size_t length;
E 3
{
I 6
	register char *p1, *p2;
E 6

	if (length == 0)
D 3
		return (0);
E 3
I 3
		return(0);
I 6
	p1 = (char *)b1;
	p2 = (char *)b2;
E 6
E 3
	do
D 6
		if (*b1++ != *b2++)
E 6
I 6
		if (*p1++ != *p2++)
E 6
			break;
	while (--length);
	return(length);
}
E 1
