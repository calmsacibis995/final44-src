h09964
s 00002/00002/00017
d D 8.1 93/06/06 15:37:16 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00014
d D 5.4 91/04/16 15:42:39 bostic 6 5
c new copyright; att/bsd/shared
e
s 00003/00003/00015
d D 5.3 88/01/03 00:33:25 bostic 5 4
c neither K&R or ANSI C allow untyped function declarations
e
s 00001/00001/00017
d D 5.2 85/06/07 19:55:45 mckusick 4 3
c cleanup after dist
e
s 00008/00004/00010
d D 5.1 85/06/06 16:11:26 dist 3 2
c Add copyright
e
s 00001/00001/00013
d D 1.2 82/01/18 22:15:16 linton 2 1
c sccsid
e
s 00014/00000/00000
d D 1.1 82/01/18 19:02:50 linton 1 0
c date and time created 82/01/18 19:02:50 by linton
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
E 2

E 3
D 6
/*
I 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

D 4
*
E 4
I 4
/*
E 4
E 3
 * Definitions for interfacing with source management routines.
 */

char *cursource;		/* current source file name */
LINENO lastlinenum;		/* last source line number */

D 5
skimsource();			/* get seek pointers to source lines */
chkline();			/* checks to see that a line number is valid */
printlines();			/* print out from first line to second */
E 5
I 5
int skimsource();		/* get seek pointers to source lines */
int chkline();			/* checks to see that a line number is valid */
int printlines();		/* print out from first line to second */
E 5
E 1
