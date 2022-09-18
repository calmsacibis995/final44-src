h27299
s 00002/00002/00026
d D 8.1 93/06/04 17:44:53 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00022
d D 5.2 91/04/22 15:55:16 bostic 2 1
c new copyright; att/bsd/shared
e
s 00027/00000/00000
d D 5.1 85/09/21 15:05:52 sam 1 0
c date and time created 85/09/21 15:05:52 by sam
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

#include "imPcodes.h"
#include "imp.h"
extern imPcsize;
label(s)
char *s;
{
	register i,c;
	putch(imP_SET_ABS_H);
	putwd((int)((imPx-obotx)*scalex+botx)-imPcsize/2);
	putch(imP_SET_ABS_V);
	putwd((int)((imPy-oboty)*scaley+boty-(imPcsize/1.6)));
	for(i=0; c=s[i]; i++)
	{
		imPx += imPcsize/scalex;
		putch((c == ' ')?imP_SP:c);
	}
}
E 1
