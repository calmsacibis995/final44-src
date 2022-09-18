h35713
s 00002/00002/00079
d D 8.1 93/06/06 15:40:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00074
d D 5.2 91/04/16 15:26:26 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00071
d D 5.1 85/06/06 11:27:17 dist 2 1
c Add copyright
e
s 00074/00000/00000
d D 1.1 82/01/18 19:20:37 linton 1 0
c date and time created 82/01/18 19:20:37 by linton
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
E 3
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";

E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */

E 3
E 2
/*
 * lookup the source line number nearest from below to an address
 */

#include "defs.h"
#include "mappings.h"
#include "object.h"
#include "linetab.h"

LINENO srcline(addr)
ADDRESS addr;
{
	register ADDRESS i, j, k;
	ADDRESS a;

	if (nlhdr.nlines == 0) {
		return(0);
	}
	i = 0;
	j = nlhdr.nlines - 1;
	if (addr <= linetab[i].addr) {
		return(linetab[i].line);
	} else if (addr >= linetab[j].addr) {
		return(linetab[j].line);
	}
	while (i <= j) {
		k = (i + j) / 2;
		if ((a = linetab[k].addr) == addr) {
			return(linetab[k].line);
		} else if (addr > a) {
			i = k+1;
		} else {
			j = k-1;
		}
	}
	if (addr > linetab[i].addr) {
		return(linetab[i].line);
	} else {
		return(linetab[i-1].line);
	}
	/*NOTREACHED*/
}

/*
 * look for a line exactly corresponding to the given address
 */

LINENO linelookup(addr)
ADDRESS addr;
{
	register ADDRESS i, j, k;
	ADDRESS a;

	if (nlhdr.nlines == 0 || addr < linetab[0].addr) {
		return(0);
	}
	i = 0;
	j = nlhdr.nlines - 1;
	while (i <= j) {
		k = (i + j) / 2;
		if ((a = linetab[k].addr) == addr) {
			return(linetab[k].line);
		} else if (addr > a) {
			i = k+1;
		} else {
			j = k-1;
		}
	}
	return(0);
}
E 1
