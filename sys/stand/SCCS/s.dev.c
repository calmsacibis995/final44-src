h50577
s 00002/00002/00024
d D 8.1 93/06/11 16:00:51 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 7.1 93/06/11 14:35:13 mckusick 1 0
c date and time created 93/06/11 14:35:13 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <stand/stand.h>

/* ARGSUSED */
nodev(io)
	struct iob *io;
{
	return (ENXIO);
}

/* ARGSUSED */
noioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{
	return (EINVAL);
}
E 1
