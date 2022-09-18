h12169
s 00005/00005/00022
d D 8.1 93/06/06 16:09:50 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00006/00016
d D 5.2 91/04/16 16:04:37 bostic 6 5
c new copyright; att/bsd/shared
e
s 00009/00003/00013
d D 5.1 85/06/05 14:36:19 dist 5 4
c Add copyright
e
s 00000/00000/00016
d D 2.1 84/02/08 20:41:58 aoki 4 3
c synchronize to version 2
e
s 00000/00000/00016
d D 1.3 83/09/19 06:59:16 thien 3 2
c Restoring to unlinted version
e
s 00002/00000/00014
d D 1.2 83/08/19 04:59:00 thien 2 1
c The changes were made to allow successful linting
e
s 00014/00000/00000
d D 1.1 80/08/27 19:55:29 peter 1 0
c date and time created 80/08/27 19:55:29 by peter
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
D 6
/*
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
 */
E 5

I 2
#ifndef lint
E 2
D 5
static	char sccsid[] = "%Z%%M% %I% %G%";
I 2
#endif
E 5
I 5
D 7
char copyright[] =
D 6
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
D 6
#endif not lint
E 6
I 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6
E 5
E 2

#include "OPnames.h"

main()  {
	register int i;

	for (i = 0;  i < 256;  i++)
		if (otext[i])
			printf("#define O_%s %04o\n", otext[i]+1, i);
	exit(0);
}
E 1
