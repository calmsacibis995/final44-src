h46401
s 00002/00002/00021
d D 8.1 93/06/06 15:17:03 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00014
d D 1.6 90/04/09 18:26:42 bostic 6 5
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00001/00016
d D 1.5 89/01/09 15:38:42 mckusick 5 4
c update from John Gilmore for gcc
e
s 00001/00002/00016
d D 1.4 81/06/10 00:38:30 mckusic 4 3
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00001/00000/00017
d D 1.3 81/01/06 12:04:23 mckusic 3 2
c include math.h to insure correct return type
e
s 00000/00000/00017
d D 1.2 80/11/20 03:02:13 mckusic 2 1
c put in include for <math.h> so they will return doubles
e
s 00017/00000/00000
d D 1.1 80/10/30 00:33:45 mckusick 1 0
c date and time created 80/10/30 00:33:45 by mckusick
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

I 3
#include <math.h>
E 3
D 4
#include "h01errs.h"
E 4

double
LN(value)

	double	value;
{
	if (value <= 0) {
D 4
		ERROR(ELN, value);
E 4
I 4
		ERROR("Non-positive argument of %e to ln\n", value);
E 4
D 5
		return;
E 5
	}
	return log(value);
}
E 1
