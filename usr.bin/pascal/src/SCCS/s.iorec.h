h65320
s 00002/00002/00024
d D 8.1 93/06/06 16:09:10 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00021
d D 5.2 91/04/16 16:25:19 bostic 5 4
c new copyright; att/bsd/shared
e
s 00007/00003/00018
d D 5.1 85/06/05 15:44:19 dist 4 3
c Add copyright
e
s 00000/00000/00021
d D 2.1 84/02/08 20:41:51 aoki 3 2
c synchronize to version 2
e
s 00000/00000/00021
d D 1.2 83/09/19 07:08:25 thien 2 1
c changing to unlinted source
e
s 00021/00000/00000
d D 1.1 80/08/27 19:54:11 peter 1 0
c date and time created 80/08/27 19:54:11 by peter
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1979 Regents of the University of California */

/* static	char sccsid[] = "%Z%%M% %I% %G%"; */
E 4
I 4
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */
E 4

#include <stdio.h>
#define NAMSIZ 76

struct iorec {
	char		*fileptr;	/* ptr to file window */
	long		lcount;		/* number of lines printed */
	long		llimit;		/* maximum number of text lines */
	FILE		*fbuf;		/* FILE ptr */
	struct iorec	*fchain;	/* chain to next file */
	long		*flev;		/* ptr to associated file variable */
	char		*pfname;	/* ptr to name of file */
	long		funit;		/* file status flags */
	long		size;		/* size of elements in the file */
	char		fname[NAMSIZ];	/* name of associated UNIX file */
	char		buf[BUFSIZ];	/* I/O buffer */
	char		window[1];	/* file window element */
};
E 1
