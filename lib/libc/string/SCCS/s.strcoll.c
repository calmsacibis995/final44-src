h17045
s 00002/00002/00025
d D 8.1 93/06/04 15:11:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00026
d D 5.3 92/10/04 13:08:47 bostic 3 2
c lint
e
s 00001/00001/00025
d D 5.2 91/01/26 15:31:57 bostic 2 1
c stdc.h -> cdefs.h
e
s 00026/00000/00000
d D 5.1 90/05/15 14:44:05 bostic 1 0
c date and time created 90/05/15 14:44:05 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
#include <sys/cdefs.h>
E 2
#include <string.h>
D 2
#include <sys/stdc.h>
E 2

/*
 * Compare strings according to LC_COLLATE category of current locale.
 */
I 3
int
E 3
strcoll(s1, s2)
	const char *s1, *s2;
{
	/* LC_COLLATE is unimplemented, hence always "C" */
	return (strcmp(s1, s2));
}
E 1
