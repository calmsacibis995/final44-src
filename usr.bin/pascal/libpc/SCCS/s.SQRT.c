h40845
s 00002/00002/00021
d D 8.1 93/06/06 15:19:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00014
d D 1.5 90/04/09 18:27:51 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00001/00016
d D 1.4 89/01/09 15:39:18 mckusick 4 3
c update from John Gilmore for gcc
e
s 00001/00002/00016
d D 1.3 81/06/10 00:44:22 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00002/00001/00016
d D 1.2 80/11/20 03:02:04 mckusic 2 1
c put in include for <math.h> so they will return doubles
e
s 00017/00000/00000
d D 1.1 80/10/30 00:35:46 mckusick 1 0
c date and time created 80/10/30 00:35:46 by mckusick
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
/*-
D 6
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */
E 5

D 5
static char sccsid[] = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

D 3
#include "h01errs.h"
E 3
I 2
#include <math.h>
E 2

double
SQRT(value)

	double	value;
{
D 2
	if (value <= 0) {
E 2
I 2
	if (value < 0) {
E 2
D 3
		ERROR(ESQRT, value);
E 3
I 3
		ERROR("Negative argument of %e to sqrt\n", value);
E 3
D 4
		return;
E 4
	}
	return sqrt(value);
}
E 1
