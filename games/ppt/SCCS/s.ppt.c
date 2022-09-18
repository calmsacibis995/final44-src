h40936
s 00005/00005/00052
d D 8.1 93/05/31 17:42:43 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 5.5 93/02/03 17:43:15 torek 5 4
c declare static functions as static (for gcc2)
e
s 00001/00011/00056
d D 5.4 90/06/01 13:12:37 bostic 4 3
c new copyright notice
e
s 00010/00005/00057
d D 5.3 88/06/27 16:33:38 bostic 3 2
c install approved copyright notice
e
s 00006/00002/00056
d D 5.2 88/02/08 16:09:32 bostic 2 1
c make ppt handle args, so it and bcd work the same way
e
s 00058/00000/00000
d D 5.1 88/02/08 14:02:00 bostic 1 0
c date and time created 88/02/08 14:02:00 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>

D 5
void	putppt();
E 5
I 5
static void	putppt();
E 5

D 2
/*ARGSUSED*/
E 2
main(argc, argv)
	int argc;
	char **argv;
{
	register int c;
I 2
	register char *p;
E 2

	(void) puts("___________");
D 2
	while ((c = getchar()) != EOF)
E 2
I 2
	if (argc > 1)
		while (p = *++argv)
			for (; *p; ++p)
				putppt((int)*p);
	else while ((c = getchar()) != EOF)
E 2
		putppt(c);
	(void) puts("___________");
	exit(0);
}

static void
putppt(c)
	register int c;
{
	register int i;

	(void) putchar('|');
	for (i = 7; i >= 0; i--) {
		if (i == 2)
			(void) putchar('.');	/* feed hole */
		if ((c&(1<<i)) != 0)
			(void) putchar('o');
		else
			(void) putchar(' ');
	}
	(void) putchar('|');
	(void) putchar('\n');
}
E 1
