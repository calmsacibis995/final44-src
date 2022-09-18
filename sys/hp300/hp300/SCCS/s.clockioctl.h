h09080
s 00002/00002/00017
d D 8.1 93/06/10 21:40:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00018
d D 7.2 90/11/02 16:22:19 mckusick 2 1
c update Utah reference identifier
e
s 00019/00000/00000
d D 7.1 90/05/08 17:51:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 University of Utah.
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
 *
D 2
 * from: Utah $Hdr: clockioctl.h 1.0 89/11/05$
E 2
I 2
 * from: Utah $Hdr: clockioctl.h 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define	CLOCKMAP	_IOWR('C', 1, int)
#define	CLOCKUNMAP	_IOW('C', 2, int)
#define	CLOCKGETRES	_IOR('C', 3, int)
E 1
