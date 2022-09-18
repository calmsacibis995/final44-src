h57049
s 00002/00002/00017
d D 8.1 93/06/04 13:06:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00017
d D 5.2 90/05/17 11:57:20 bostic 2 1
c might as well keep header and source in sync
e
s 00017/00000/00000
d D 5.1 90/05/15 22:43:01 bostic 1 0
c date and time created 90/05/15 22:43:01 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
#include <stdlib.h>

E 2
long
labs(j)
	long j;
{
	return(j < 0 ? -j : j);
}
E 1
