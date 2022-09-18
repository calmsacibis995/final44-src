h53394
s 00002/00002/00019
d D 8.1 93/05/31 15:18:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00000/00000
d D 5.1 91/03/07 20:27:21 bostic 1 0
c date and time created 91/03/07 20:27:21 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define E_OPEN 01
#define E_CREAT 02
#define E_EXEC 04

#ifdef __STDC__
char *errmsg(int, int);
#else
char *errmsg();
#endif
E 1
