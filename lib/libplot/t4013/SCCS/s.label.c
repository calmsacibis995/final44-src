h14122
s 00002/00002/00017
d D 8.1 93/06/04 17:51:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00013
d D 5.2 91/04/22 16:03:39 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00011
d D 5.1 85/06/07 08:26:37 dist 2 1
c Add copyright
e
s 00012/00000/00000
d D 1.1 85/01/02 20:10:40 jak 1 0
c date and time created 85/01/02 20:10:40 by jak
e
u
U
t
T
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

label(s)
char *s;
{
	register i,c;
	putch(037);	/* alpha mode */
	for(i=0; c=s[i]; i++)
		putch(c);
}
E 1
