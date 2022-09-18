h60649
s 00002/00002/00041
d D 8.1 93/06/04 17:45:00 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00037
d D 5.4 91/04/22 15:55:18 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00000/00040
d D 5.3 85/09/21 16:24:57 sam 3 2
c need imp.h to reference imPcsize
e
s 00026/00000/00014
d D 5.2 85/09/21 16:21:42 sam 2 1
c bring in most up to date code; removes hardcoded printer resolution; 
c adds 2 pixels to effective plotting resolution; parameterizes font and point size; 
c make linemod a hack to set font from plot file
e
s 00014/00000/00000
d D 5.1 85/09/21 15:05:54 sam 1 0
c date and time created 85/09/21 15:05:54 by sam
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
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
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

I 3
#include "imp.h"

E 3
I 2
/*
 * Hack to set font.
 */
E 2
linemod(s)
char *s;
{
I 2
	register char *tit;
	register char *nam;
	int siz = 0;
	nam = s;
	for(tit = "charset="; *tit; )
		if (*tit++ != *nam++)
			return;
	s = nam;
	while(*nam) 
		switch(*nam++) {
		case ',':
		case '\n':
			*--nam = 0;
		}
	siz = atoi(++nam);
	if (siz == 0) {
		while (*--nam >= '0' && *nam <= '9')
			;
		siz = (atoi(++nam)*4)/3;
	}
	if (siz == 0)
		siz = imPcsize;
	setfont(s, siz);
E 2
}
E 1
