h29329
s 00002/00002/00037
d D 8.1 93/06/11 16:02:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00037
d D 7.3 93/05/24 22:43:48 mckusick 3 2
c define return as off_t; new include location
e
s 00001/00001/00037
d D 7.2 92/10/11 10:01:05 bostic 2 1
c make kernel includes standard
e
s 00038/00000/00000
d D 7.1 91/05/05 13:20:15 bostic 1 0
c date and time created 91/05/05 13:20:15 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1982, 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
D 2
#include "saio.h"
E 2
I 2
D 3
#include <stand/saio.h>
E 3
I 3
#include <stand.att/saio.h>
E 3
E 2

I 3
off_t
E 3
lseek(fdesc, addr, ptr)
	int fdesc, ptr;
	off_t addr;
{
	register struct iob *io;

#ifndef SMALL
	if (ptr != L_SET) {
		printf("Seek not from beginning of file\n");
		errno = EOFFSET;
		return (-1);
	}
#endif
	fdesc -= 3;
#ifndef SMALL
	if (fdesc < 0 || fdesc >= SOPEN_MAX ||
	    ((io = &iob[fdesc])->i_flgs & F_ALLOC) == 0) {
		errno = EBADF;
		return (-1);
	}
#endif
	io->i_offset = addr;
	io->i_bn = addr / DEV_BSIZE;
	io->i_cc = 0;
	return (0);
}
E 1
