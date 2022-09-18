h62275
s 00002/00002/00048
d D 8.1 93/06/06 15:40:16 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00044
d D 5.2 91/04/16 15:26:25 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00002/00041
d D 5.1 85/06/06 11:26:59 dist 2 1
c Add copyright
e
s 00043/00000/00000
d D 1.1 82/01/18 19:20:35 linton 1 0
c date and time created 82/01/18 19:20:35 by linton
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
 * get the source file name associated with a given address
 */

#include "defs.h"
#include "mappings.h"
#include "object.h"
#include "filetab.h"

char *srcfilename(addr)
ADDRESS addr;
{
	register ADDRESS i, j, k;
	ADDRESS a;
	FILETAB *ftp;

	if (addr < filetab[0].addr) {
		return(NIL);
	}
	i = 0;
	j = nlhdr.nfiles - 1;
	while (i < j) {
		k = (i + j) / 2;
		ftp = &filetab[k];
		if ((a = ftp->addr) == addr) {
			return(ftp->filename);
		} else if (addr > a) {
			i = k + 1;
		} else {
			j = k - 1;
		}
	}
	if (addr >= filetab[i].addr) {
		return(filetab[i].filename);
	} else {
		return(filetab[i-1].filename);
	}
	/*NOTREACHED*/
}
E 1
