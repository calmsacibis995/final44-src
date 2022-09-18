h21533
s 00002/00002/00013
d D 8.1 93/06/04 17:19:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00014
d D 5.3 91/01/13 10:17:18 bostic 3 2
c Chris Torek demands that it return the yyparse() value.
e
s 00009/00006/00009
d D 5.2 90/05/15 12:23:24 bostic 2 1
c from scratch, rename; add Berkeley specific copyright notice
e
s 00015/00000/00000
d D 5.1 85/08/09 21:45:43 mckusick 1 0
c date and time created 85/08/09 21:45:43 by mckusick
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
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

main()
{
I 2
D 3
	extern yyparse();
E 2

D 2
	yyparse();
E 2
I 2
	(void)yyparse();
	return(0);
E 3
I 3
	exit(yyparse());
E 3
E 2
}
E 1
