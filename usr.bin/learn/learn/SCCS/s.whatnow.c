h58058
s 00002/00002/00055
d D 8.1 93/06/06 14:57:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00048
d D 4.3 91/04/17 18:00:42 bostic 3 2
c new copyright; att/bsd/shared
e
s 00019/00001/00031
d D 4.2 83/04/25 23:59:26 mckusick 2 1
c 
e
s 00032/00000/00000
d D 4.1 83/02/24 12:56:22 mckusick 1 0
c date and time created 83/02/24 12:56:22 by mckusick
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "stdio.h"
#include "lrnref.h"

I 2
extern	char	togo[];
extern	int	review;

E 2
whatnow()
{
I 2
	if (again) {
		if (!review)
			printf("\nOK.  That was lesson %s.\n\n", todo);
		fflush(stdout);
		strcpy(level, togo);
		return;
	}
	if (skip) {
		printf("\nOK.  That was lesson %s.\n", todo);
		printf("Skipping to next lesson.\n\n");
		fflush(stdout);
		strcpy(level, todo);
		skip = 0;
		return;
	}
E 2
	if (todo == 0) {
		more=0;
		return;
	}
	if (didok) {
		strcpy(level,todo);
		if (speed<=9) speed++;
	}
	else {
		speed -= 4;
		/* the 4 above means that 4 right, one wrong leave
		    you with the same speed. */
		if (speed <0) speed=0;
	}
	if (wrong) {
		speed -= 2;
		if (speed <0 ) speed = 0;
	}
	if (didok && more) {
D 2
		printf("\nGood.  Lesson %s (%d)\n\n",level, speed);
E 2
I 2
		printf("\nGood.  That was lesson %s.\n\n",level);
E 2
		fflush(stdout);
	}
}
E 1
