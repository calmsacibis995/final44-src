h25431
s 00002/00002/00040
d D 8.1 93/06/06 14:56:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00033
d D 4.4 91/04/17 18:00:35 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00001/00033
d D 4.3 91/03/01 14:33:06 bostic 3 2
c ANSI
e
s 00000/00000/00034
d D 4.2 83/04/25 23:58:53 mckusick 2 1
c 
e
s 00034/00000/00000
d D 4.1 83/02/24 12:55:51 mckusick 1 0
c date and time created 83/02/24 12:55:51 by mckusick
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "stdio.h"
#include "lrnref.h"
#include "signal.h"

int istop;

list(r)
char *r;
{
D 3
	int stop(), intrpt();
E 3
I 3
	void stop(), intrpt();
E 3
	FILE *ft;
	char s[100];

	if (r==0)
		return;
	istop = 1;
	signal(SIGINT, stop);
	ft = fopen(r, "r");
	if (ft != NULL) {
		while (fgets(s, 100, ft) && istop)
			fputs(s, stdout);
		fclose(ft);
	}
	signal(SIGINT, intrpt);
}

I 3
void
E 3
stop()
{
	istop=0;
}
E 1
