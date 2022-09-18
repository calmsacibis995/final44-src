h40041
s 00002/00002/00031
d D 8.1 93/06/06 22:11:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00025
d D 5.5 91/04/24 17:33:48 bostic 5 4
c new copyright; att/bsd/shared
e
s 00008/00007/00018
d D 5.4 85/06/20 09:54:58 bloom 4 3
c fixes from rick adams
e
s 00001/00001/00024
d D 5.3 85/02/12 09:06:10 ralph 3 2
c return pointer to last name after '/' not '/name'.
e
s 00006/00005/00019
d D 5.2 85/01/22 14:09:19 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00024/00000/00000
d D 5.1 83/07/02 17:57:13 sam 1 0
c date and time created 83/07/02 17:57:13 by sam
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5

D 4
/*******
 *	char *
 *	lastpart(file)	find last part of file name
 *	char *file;
E 4
I 4
#include "uucp.h"

/*LINTLIBRARY*/

/*
 *	find last part of file name
E 4
 *
 *	return - pointer to last part
 */

char *
lastpart(file)
register char *file;
{
	register char *c;
I 2
D 4
	char *rindex();
E 4
E 2

D 2
	c = file + strlen(file);
	while (c >= file)
		if (*(--c) == '/')
			break;
	return(++c);
E 2
I 2
	c = rindex(file, '/');
D 4
	if (c)
D 3
		return c;
E 3
I 3
		return c + 1;
E 4
I 4
	if (c++)
		return c;
E 4
E 3
	else
		return file;
E 2
}
E 1
