h02858
s 00002/00002/00022
d D 8.1 93/06/04 15:11:17 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00022
d D 5.6 91/02/24 13:57:47 bostic 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00022
d D 5.5 90/06/01 14:45:32 bostic 6 5
c new copyright notice
e
s 00002/00000/00031
d D 5.4 90/05/17 12:05:36 bostic 5 4
c keep string.h and source in sync
e
s 00024/00016/00007
d D 5.3 88/07/18 15:55:54 bostic 4 3
c rewritten from the manual page; add Berkeley specific copyright
e
s 00002/00002/00021
d D 5.2 86/03/09 19:57:23 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00019
d D 5.1 85/06/05 12:36:20 mckusick 2 1
c Add copyright
e
s 00020/00000/00000
d D 4.1 80/12/21 16:40:07 wnj 1 0
c date and time created 80/12/21 16:40:07 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
D 4
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif LIBC_SCCS and not lint
E 3

E 4
E 2
/*
D 4
 * Concatenate s2 on the end of s1.  S1's space must be large enough.
 * Return s1.
E 4
I 4
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
 */

I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 5
#include <string.h>

E 5
E 4
char *
D 4
strcat(s1, s2)
register char *s1, *s2;
E 4
I 4
strcat(s, append)
D 7
	register char *s, *append;
E 7
I 7
	register char *s;
	register const char *append;
E 7
E 4
{
D 4
	register char *os1;
E 4
I 4
	char *save = s;
E 4

D 4
	os1 = s1;
	while (*s1++)
		;
	--s1;
	while (*s1++ = *s2++)
		;
	return(os1);
E 4
I 4
	for (; *s; ++s);
	while (*s++ = *append++);
	return(save);
E 4
}
E 1
