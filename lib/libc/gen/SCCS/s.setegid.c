h08186
s 00001/00011/00016
d D 5.4 90/06/01 14:14:20 bostic 5 4
c new copyright notice
e
s 00014/00003/00013
d D 5.3 88/08/03 15:54:18 bostic 4 3
c written by Sam Leffler; add Berkeley specific copyright
e
s 00002/00002/00014
d D 5.2 86/03/09 19:55:06 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00007
d D 5.1 85/06/05 12:31:39 mckusick 2 1
c Add copyright
e
s 00008/00000/00000
d D 4.1 83/06/30 17:20:30 sam 1 0
c date and time created 83/06/30 17:20:30 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
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
E 4
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

setegid(egid)
	int egid;
{

	return (setregid(-1, egid));
}
E 1
