h56983
s 00002/00002/00025
d D 8.1 93/06/06 15:18:07 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00003/00018
d D 1.6 90/04/09 18:27:09 bostic 6 5
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00002/00021
d D 1.5 89/01/09 15:38:54 mckusick 5 4
c update from John Gilmore for gcc
e
s 00000/00001/00023
d D 1.4 81/06/10 00:39:33 mckusic 4 3
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00005/00001/00019
d D 1.3 81/06/08 00:36:02 mckusic 3 2
c put in better error messages
e
s 00004/00003/00016
d D 1.2 81/03/07 15:59:36 mckusic 2 1
c merge in onyx changes
e
s 00019/00000/00000
d D 1.1 80/10/30 00:34:28 mckusick 1 0
c date and time created 80/10/30 00:34:28 by mckusick
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */
E 6
I 6
/*-
D 7
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */
E 6

D 6
static char sccsid[] = "%Z%%M% %I% %G%";

E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6
D 4
#include "h01errs.h"
E 4

I 2
long
E 2
PRED(value, lower, upper)

D 2
	int	value;
	int	lower;
	int	upper;
E 2
I 2
	long	value;
	long	lower;
	long	upper;
E 2
{
I 3
	if (value == lower) {
		ERROR("Cannot take pred of first element of a range\n");
D 5
		return;
E 5
	}
E 3
	value--;
	if (value < lower || value > upper) {
D 3
		ERROR(ERANGE, value);
E 3
I 3
		ERROR("Value of %D is out of range\n", value);
E 3
D 5
		return;
E 5
	}
	return	value;
}
E 1
