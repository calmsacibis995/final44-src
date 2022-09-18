h60722
s 00002/00002/00021
d D 8.1 93/06/06 15:19:22 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00014
d D 1.6 90/04/09 18:27:46 bostic 6 5
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00001/00016
d D 1.5 89/01/09 15:39:15 mckusick 5 4
c update from John Gilmore for gcc
e
s 00005/00005/00012
d D 1.4 82/11/12 18:58:49 mckusick 4 3
c make error message global var, so routine can be inline expanded
e
s 00001/00002/00016
d D 1.3 81/06/10 00:44:16 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00003/00003/00015
d D 1.2 81/03/07 16:03:16 mckusic 2 1
c merge in onyx changes
e
s 00018/00000/00000
d D 1.1 80/10/30 00:35:33 mckusick 1 0
c date and time created 80/10/30 00:35:33 by mckusick
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

I 4
extern char ERANG[];	/* ERANG is defined in RANG4.c */
E 4
D 2

E 2
D 3
#include "h01errs.h"
E 3

I 2
long
E 2
RSNG4(value, upper)
D 4

D 2
	int	value;
	int	upper;
E 2
I 2
	long	value;
	long	upper;
E 4
I 4
	long		value;
	unsigned long	upper;
E 4
E 2
{
D 4
	if (value < 0 || value > upper) {
D 3
		ERROR(ERANGE, value);
E 3
I 3
		ERROR("Value of %D is out of range\n", value);
E 4
I 4
	if (value > upper) {
		ERROR(ERANG, value);
E 4
E 3
D 5
		return;
E 5
	}
	return	value;
}
E 1
