h15406
s 00002/00002/00024
d D 8.1 93/06/06 22:11:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00018
d D 5.4 91/04/24 17:33:53 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00000/00016
d D 5.3 85/06/23 13:06:19 bloom 3 2
c lint fixes from rick adams
e
s 00002/00004/00014
d D 5.2 85/01/22 14:11:06 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00018/00000/00000
d D 5.1 83/07/02 17:57:35 sam 1 0
c date and time created 83/07/02 17:57:35 by sam
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

#include <sys/types.h>

I 3
/*LINTLIBRARY*/

E 3
D 2
/*******
 *	sysacct(bytes, time)	output accounting info
 *	time_t time;
 *	long bytes;
E 2
I 2
/*
 *	output accounting info
E 2
 */

I 3
/*ARGSUSED*/
E 3
sysacct(bytes, time)
time_t time;
long bytes;
{
	return;
}
E 1
