h10968
s 00002/00002/00043
d D 8.1 93/06/11 16:01:41 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00045/00000/00000
d D 7.1 93/06/11 14:35:19 mckusick 1 0
c date and time created 93/06/11 14:35:19 by mckusick
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

fstat(fd, sb)
	int fd;
	struct stat *sb;
{
	register struct open_file *f = &files[fd];

	if ((unsigned)fd >= SOPEN_MAX || f->f_flags == 0) {
		errno = EBADF;
		return (-1);
	}

	/* operation not defined on raw devices */
	if (f->f_flags & F_RAW) {
		errno = EOPNOTSUPP;
		return (-1);
	}

	errno = (f->f_ops->stat)(f, sb);
	return (0);
}

stat(str, sb)
	const char *str;
	struct stat *sb;
{
	int fd, rv;

	fd = open(str, 0);
	if (fd < 0)
		return (-1);
	rv = fstat(fd, sb);
	(void)close(fd);
	return (rv);
}
E 1
