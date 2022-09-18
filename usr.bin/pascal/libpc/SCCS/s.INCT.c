h65473
s 00002/00002/00038
d D 8.1 93/06/06 15:16:44 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00031
d D 1.3 90/04/09 18:26:34 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00006/00006/00027
d D 1.2 81/03/07 15:57:05 mckusic 2 1
c merge in onyx changes
e
s 00033/00000/00000
d D 1.1 80/10/30 00:33:34 mckusick 1 0
c date and time created 80/10/30 00:33:34 by mckusick
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1979 Regents of the University of California */
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "h00vars.h"

I 2
bool
E 2
INCT(element, paircnt, singcnt, data)

D 2
	register int	element;	/* element to find */
	int		paircnt;	/* number of pairs to check */
	int		singcnt;	/* number of singles to check */
	int		data;		/* paircnt plus singcnt bounds */
E 2
I 2
	register long	element;	/* element to find */
	long		paircnt;	/* number of pairs to check */
	long		singcnt;	/* number of singles to check */
	long		data;		/* paircnt plus singcnt bounds */
E 2
{
D 2
	register int	*dataptr;
E 2
I 2
	register long	*dataptr = &data;
E 2
	register int	cnt;

D 2
	dataptr = &data;
E 2
	for (cnt = 0; cnt < paircnt; cnt++) {
		if (element > *dataptr++) {
			dataptr++;
			continue;
		}
		if (element >= *dataptr++) {
			return TRUE;
		}
	}
	for (cnt = 0; cnt < singcnt; cnt++) {
		if (element == *dataptr++) {
			return TRUE;
		}
	}
	return FALSE;
}
E 1
