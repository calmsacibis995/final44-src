h25605
s 00002/00002/00017
d D 8.1 93/06/06 15:40:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00014
d D 5.2 91/04/16 15:26:23 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00003/00011
d D 5.1 85/06/06 16:17:32 dist 3 2
c Add copyright
e
s 00001/00001/00013
d D 1.2 82/01/18 21:56:01 linton 2 1
c sccsid
e
s 00014/00000/00000
d D 1.1 82/01/18 19:20:33 linton 1 0
c date and time created 82/01/18 19:20:33 by linton
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 3
I 3
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * definition of line number information table
 */

typedef struct {
	LINENO line;
	ADDRESS addr;
} LINETAB;

LINETAB *linetab;
E 1
