h19729
s 00002/00002/00017
d D 8.1 93/06/04 17:19:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00010/00008
d D 5.2 90/05/15 12:22:01 bostic 2 1
c from scratch, rename; add Berkeley specific copyright notice
e
s 00018/00000/00000
d D 5.1 85/08/09 21:45:44 mckusick 1 0
c date and time created 85/08/09 21:45:44 by mckusick
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
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
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

D 2
# include <stdio.h>
E 2
I 2
#include <stdio.h>
E 2

D 2
yyerror(s)
	char *s;
E 2
I 2
yyerror(msg)
char *msg;
E 2
{
D 2

	fprintf(stderr, "%s\n", s);
E 2
I 2
	(void)fprintf(stderr, "%s\n", msg);
	return(0);
E 2
}
E 1
