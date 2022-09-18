h41798
s 00002/00002/00026
d D 8.1 93/06/17 07:17:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00026
d D 5.3 93/06/16 16:29:11 mckusick 4 2
c __indir => __syscall
e
s 00002/00002/00026
d R 8.1 93/06/04 13:17:00 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00026
d D 5.2 93/05/25 14:56:38 mckusick 2 1
c __ goes away
e
s 00028/00000/00000
d D 5.1 92/07/09 15:59:33 mckusick 1 0
c date and time created 92/07/09 15:59:33 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/syscall.h>

/*
 * This function provides 64-bit offset padding that
 * is not supplied by GCC 1.X but is supplied by GCC 2.X.
 */
off_t
D 2
__lseek(fd, offset, whence)
E 2
I 2
lseek(fd, offset, whence)
E 2
	int	fd;
	off_t	offset;
	int	whence;
{
D 4
	extern off_t __indir();
E 4
I 4
	extern off_t __syscall();
E 4

D 2
	return(__indir((quad_t)SYS___lseek, fd, 0, offset, whence));
E 2
I 2
D 4
	return(__indir((quad_t)SYS_lseek, fd, 0, offset, whence));
E 4
I 4
	return(__syscall((quad_t)SYS_lseek, fd, 0, offset, whence));
E 4
E 2
}
E 1
