h36039
s 00011/00000/00004
d D 5.2 91/04/12 15:41:29 bostic 2 1
c new copyright; att/bsd/shared
e
s 00004/00000/00000
d D 5.1 90/06/25 14:07:13 bostic 1 0
c date and time created 90/06/25 14:07:13 by bostic
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
extern int errno;
serrno_(n)
long *n;
{	errno = *n; }
E 1
