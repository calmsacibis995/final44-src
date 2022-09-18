h08761
s 00002/00002/00020
d D 8.1 93/06/04 13:09:07 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00021
d D 5.3 91/02/24 13:30:20 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00020
d D 5.2 91/02/05 00:26:40 torek 2 1
c repair arguments (add const)
e
s 00021/00000/00000
d D 5.1 91/01/20 21:34:58 bostic 1 0
c new stdio
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

I 3
#include <unistd.h>
E 3
#include <stdio.h>

remove(file)
D 2
	char *file;
E 2
I 2
	const char *file;
E 2
{
	return (unlink(file));
}
E 1
