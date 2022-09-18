h19477
s 00001/00001/00035
d D 8.2 95/04/28 15:42:05 bostic 7 6
c externs.h -> extern.h
e
s 00002/00002/00034
d D 8.1 93/05/31 16:13:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00035
d D 5.3 90/06/01 13:02:34 bostic 5 4
c new copyright notice
e
s 00010/00005/00036
d D 5.2 88/06/19 14:11:20 bostic 4 3
c install approved copyright notice
e
s 00011/00005/00030
d D 5.1 88/05/08 15:49:46 bostic 3 2
c add Berkeley header; yank to 5.1
e
s 00006/00000/00029
d D 1.2 85/04/24 15:31:15 edward 2 1
c copyright messages
e
s 00029/00000/00000
d D 1.1 84/11/18 18:59:06 edward 1 0
c date and time created 84/11/18 18:59:06 by edward
e
u
U
t
T
I 2
/*
D 3
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 3
I 3
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

E 2
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

D 7
#include "externs.h"
E 7
I 7
#include "extern.h"
E 7

card(array, size)		/* for beenthere, injuries */
	register char *array;
	int size;
{
	register char *end = array + size;
	register int i = 0;

	while (array < end)
		if (*array++)
			i++;
	return (i);
}

ucard(array)
	register unsigned *array;
{
	register int j = 0, n;

	for (n = 0; n < NUMOFOBJECTS; n++)
		if (testbit(array, n))
			    j++;
	return (j);
}
E 1
