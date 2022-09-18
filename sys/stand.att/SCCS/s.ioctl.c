h41835
s 00002/00002/00055
d D 8.1 93/06/11 16:01:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 7.3 93/05/24 22:44:06 mckusick 3 2
c new include location
e
s 00001/00001/00056
d D 7.2 92/10/11 10:01:03 bostic 2 1
c make kernel includes standard
e
s 00057/00000/00000
d D 7.1 91/05/05 13:20:08 bostic 1 0
c date and time created 91/05/05 13:20:08 by bostic
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

#ifndef SMALL
ioctl(fdesc, cmd, arg)
	int fdesc, cmd;
	char *arg;
{
	register struct iob *file;
	int error = 0;

	fdesc -= 3;
	if (fdesc < 0 || fdesc >= SOPEN_MAX ||
	    ((file = &iob[fdesc])->i_flgs&F_ALLOC) == 0) {
		errno = EBADF;
		return (-1);
	}
	switch (cmd) {

	case SAIOHDR:
		file->i_flgs |= F_HDR;
		break;

	case SAIOCHECK:
		file->i_flgs |= F_CHECK;
		break;

	case SAIOHCHECK:
		file->i_flgs |= F_HCHECK;
		break;

	case SAIONOBAD:
		file->i_flgs |= F_NBSF;
		break;

	case SAIODOBAD:
		file->i_flgs &= ~F_NBSF;
		break;

	default:
		error = devioctl(file, cmd, arg);
		break;
	}
	if (error < 0)
		errno = file->i_error;
	return (error);
}
#endif /* SMALL */
E 1
