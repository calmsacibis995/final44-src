h03627
s 00002/00002/00017
d D 8.1 93/06/04 12:24:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00018
d D 5.2 90/06/22 19:07:00 bostic 2 1
c not an assembly file...
e
s 00019/00000/00000
d D 5.1 90/06/07 17:50:23 bostic 1 0
c date and time created 90/06/07 17:50:23 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 2
	.asciz "%W% (Berkeley) %G%"
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
#endif /* LIBC_SCCS and not lint */

__builtin_saveregs()
{
	abort();
}
E 1
