h03592
s 00002/00002/00015
d D 8.1 93/06/11 16:01:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00000/00000
d D 7.1 93/06/11 14:35:22 mckusick 1 0
c date and time created 93/06/11 14:35:22 by mckusick
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

int	ufs_open __P((char *path, struct open_file *f));
int	ufs_close __P((struct open_file *f));
int	ufs_read __P((struct open_file *f, char *buf,
		u_int size, u_int *resid));
int	ufs_write __P((struct open_file *f, char *buf,
		u_int size, u_int *resid));
off_t	ufs_seek __P((struct open_file *f, off_t offset, int where));
int	ufs_stat __P((struct open_file *f, struct stat *sb));
E 1
