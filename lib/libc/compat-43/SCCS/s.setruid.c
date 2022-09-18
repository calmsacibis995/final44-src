h41176
s 00002/00002/00022
d D 8.1 93/06/02 00:04:23 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00000/00017
d D 5.5 91/02/23 19:50:03 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00016
d D 5.4 90/06/01 14:15:22 bostic 5 4
c new copyright notice
e
s 00014/00003/00013
d D 5.3 88/08/03 15:54:22 bostic 4 3
c written by Sam Leffler; add Berkeley specific copyright
e
s 00002/00002/00014
d D 5.2 86/03/09 19:55:52 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00007
d D 5.1 85/06/05 12:33:24 mckusick 2 1
c Add copyright
e
s 00008/00000/00000
d D 4.1 83/06/30 17:20:26 sam 1 0
c date and time created 83/06/30 17:20:26 by sam
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
D 7
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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

I 6
#include <unistd.h>

int
#ifdef __STDC__
setruid(uid_t ruid)
#else
E 6
setruid(ruid)
	int ruid;
I 6
#endif
E 6
{

	return (setreuid(ruid, -1));
}
E 1
