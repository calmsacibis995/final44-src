h44889
s 00002/00002/00046
d D 8.1 93/06/11 16:02:26 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00047
d D 7.4 93/05/25 11:39:03 bostic 4 3
c trailing comment after #else or #endif
e
s 00001/00001/00047
d D 7.3 93/05/24 22:44:03 mckusick 3 2
c new include location
e
s 00001/00001/00047
d D 7.2 92/10/11 10:01:08 bostic 2 1
c make kernel includes standard
e
s 00048/00000/00000
d D 7.1 91/05/05 17:01:10 bostic 1 0
c date and time created 91/05/05 17:01:10 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/stat.h>
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
fstat(fd, sb)
	int fd;
	struct stat *sb;
{
	register struct iob *io;

	fd -= 3;
	if (fd < 0 || fd >= SOPEN_MAX ||
	    ((io = &iob[fd])->i_flgs & F_ALLOC) == 0) {
		errno = EBADF;
		return (-1);
	}
	/* only important stuff */
	sb->st_mode = io->i_ino.di_mode;
	sb->st_uid = io->i_ino.di_uid;
	sb->st_gid = io->i_ino.di_gid;
	sb->st_size = io->i_ino.di_size;
	return (0);
}

stat(str, sb)
	const char *str;
	struct stat *sb;
{
	int fd, rv;

	fd = open(str, 0);
	if (fd < 0)
		return(-1);
	rv = fstat(fd, sb);
	close(fd);
	return(rv);
}
D 4
#endif SMALL
E 4
I 4
#endif /* SMALL */
E 4
E 1
