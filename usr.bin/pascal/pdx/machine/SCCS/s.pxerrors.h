h30173
s 00002/00002/00008
d D 8.1 93/06/06 15:39:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00005
d D 5.3 91/04/16 15:32:01 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00007/00009
d D 5.2 87/04/07 15:53:35 mckusick 4 3
c port to tahoe by Nir peleg of CCI
e
s 00007/00003/00009
d D 5.1 85/06/07 10:13:16 dist 3 2
c Add copyright
e
s 00001/00001/00011
d D 1.2 82/01/18 21:56:45 linton 2 1
c sccsid
e
s 00012/00000/00000
d D 1.1 82/01/18 19:20:19 linton 1 0
c date and time created 82/01/18 19:20:19 by linton
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
E 3
E 2

D 4
#define NERRORS 39

char *pxerrmsg[];

E 4
#define ESIGNAL		SIGTRAP
D 4

#define ESTKOVER	37
#define EOVERFLOW	39
E 4
E 1
