h38655
s 00002/00002/00045
d D 8.1 93/06/06 14:27:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00003/00035
d D 5.2 91/11/27 12:57:54 bostic 2 1
c don't display a file name if using standard input (POSIX 1003.2, D11.2)
e
s 00038/00000/00000
d D 5.1 91/04/04 12:24:31 bostic 1 0
c date and time created 91/04/04 12:24:31 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <stdio.h>
#include "extern.h"

void
pcrc(fn, val, len)
	char *fn;
	u_long val, len;
{
D 2
	(void)printf("%lu %lu %s\n", val, len, fn);
E 2
I 2
	(void)printf("%lu %lu", val, len);
	if (fn)
		(void)printf(" %s", fn);
	(void)printf("\n");
E 2
}

void
psum1(fn, val, len)
	char *fn;
	u_long val, len;
{
D 2
	(void)printf("%lu %lu %s\n", val, (len + 1023) / 1024, fn);
E 2
I 2
	(void)printf("%lu %lu", val, (len + 1023) / 1024);
	if (fn)
		(void)printf(" %s", fn);
	(void)printf("\n");
E 2
}

void
psum2(fn, val, len)
	char *fn;
	u_long val, len;
{
D 2
	(void)printf("%lu %lu %s\n", val, (len + 511) / 512, fn);
E 2
I 2
	(void)printf("%lu %lu", val, (len + 511) / 512);
	if (fn)
		(void)printf(" %s", fn);
	(void)printf("\n");
E 2
}
E 1
