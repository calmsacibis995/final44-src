h45274
s 00004/00003/00022
d D 5.7 91/02/24 13:57:44 bostic 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00024
d D 5.6 91/02/24 13:20:38 bostic 6 5
c bcmp, bzero take void *, not char *
e
s 00001/00011/00024
d D 5.5 90/06/01 14:44:59 bostic 5 4
c new copyright notice
e
s 00004/00001/00031
d D 5.4 90/05/16 16:34:20 bostic 4 3
c update to ANSI types
e
s 00002/00005/00030
d D 5.3 89/04/01 14:32:54 bostic 3 2
c bcopy and bzero don't return any value
e
s 00014/00003/00021
d D 5.2 88/07/21 11:31:58 bostic 2 1
c add Berkeley specific copyright; written by Robert Elz
e
s 00024/00000/00000
d D 5.1 87/01/27 16:02:47 mckusick 1 0
c new addition for portability
e
u
U
t
T
I 1
/*
 * Copyright (c) 1987 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
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
 * bzero -- vax movc5 instruction
 */
I 4
void
E 4
bzero(b, length)
D 6
	register char *b;
E 6
I 6
D 7
	register void *b;
E 7
I 7
	void *b;
E 7
E 6
D 4
	register int length;
E 4
I 4
	register size_t length;
E 4
{
I 7
	register char *p;
E 7

D 3
	if (length)
		do
			*b++ = '\0';
		while (--length);
	return(length);
E 3
I 3
D 7
	while (length--)
		*b++ = '\0';
E 7
I 7
	for (p = b; length--;)
		*p++ = '\0';
E 7
E 3
}
E 1
