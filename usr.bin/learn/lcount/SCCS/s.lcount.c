h27857
s 00005/00005/00024
d D 8.1 93/06/06 14:55:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00014
d D 4.3 91/04/17 17:57:21 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00016
d D 4.2 83/04/25 23:58:48 mckusick 2 1
c 
e
s 00016/00000/00000
d D 4.1 83/02/24 12:55:45 mckusick 1 0
c date and time created 83/02/24 12:55:45 by mckusick
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
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
D 4
char copyright[] =
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "stdio.h"

main()	/* count lines in something */
{
	register n, c;

	n = 0;
	while ((c = getchar()) != EOF)
		if (c == '\n')
			n++;
	printf("%d\n", n);
}
E 1
