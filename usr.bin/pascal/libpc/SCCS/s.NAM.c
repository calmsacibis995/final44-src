h64714
s 00002/00002/00028
d D 8.1 93/06/06 15:17:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00021
d D 1.5 90/04/09 18:26:48 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00001/00023
d D 1.4 89/01/09 15:38:48 mckusick 4 3
c update from John Gilmore for gcc
e
s 00002/00002/00022
d D 1.3 81/06/10 00:38:43 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00004/00003/00020
d D 1.2 81/03/07 15:58:31 mckusic 2 1
c merge in onyx changes
e
s 00023/00000/00000
d D 1.1 80/10/30 00:33:52 mckusick 1 0
c date and time created 80/10/30 00:33:52 by mckusick
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

#include "h00vars.h"
D 3
#include "h01errs.h"
E 3

char *
D 2
NAM(value, name)
E 2
I 2
NAM(val, name)
E 2

D 2
	register int	value;	/* internal enumerated type value */
E 2
I 2
	long		val;	/* internal enumerated type value */
E 2
	char		*name;	/* ptr to enumerated type name descriptor */
{
I 2
	register int	value = val;
E 2
	register short	*sptr;

	sptr = (short *)name;
	if (value < 0 || value >= *sptr) {
D 2
		ERROR(ENAMRNG, value);
E 2
I 2
D 3
		ERROR(ENAMRNG, val);
E 3
I 3
		ERROR("Enumerated type value of %D is out of range on output\n",
			val);
E 3
E 2
D 4
		return;
E 4
	}
	sptr++;
	return	name + 2 + sptr[value];
}
E 1
