h24557
s 00002/00002/00022
d D 8.1 93/06/04 17:31:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00018
d D 5.2 91/04/22 14:59:34 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00016
d D 5.1 85/05/07 11:39:54 dist 2 1
c Add copyright notice
e
s 00017/00000/00000
d D 4.1 83/11/10 11:53:55 ralph 1 0
c date and time created 83/11/10 11:53:55 by ralph
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
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
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

#include "dumb.h"

label(string)
	char *string;
{
	while(*string != '\0' && currentx < COLS){
		screenmat[currentx][currenty] = *string++;
		currentx++;
	}
	if(currentx == COLS)
		currentx = currentx-1;

}
E 1
