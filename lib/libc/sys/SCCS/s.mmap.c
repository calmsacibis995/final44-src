h63644
s 00002/00002/00030
d D 8.1 93/06/17 07:17:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00030
d D 5.4 93/06/16 16:29:12 mckusick 5 3
c __indir => __syscall
e
s 00002/00002/00030
d R 8.1 93/06/04 13:17:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00031
d D 5.3 93/06/03 13:49:24 mckusick 3 2
c have to cast SYS_mmap to quad_t when using __indir
e
s 00002/00001/00030
d D 5.2 93/06/01 16:53:58 ralph 2 1
c use __indir to maintain double alignment on stack for 'offset'.
e
s 00031/00000/00000
d D 5.1 92/06/23 17:55:33 mckusick 1 0
c date and time created 92/06/23 17:55:33 by mckusick
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/syscall.h>

/*
 * This function provides 64-bit offset padding that
 * is not supplied by GCC 1.X but is supplied by GCC 2.X.
 */
caddr_t
mmap(addr, len, prot, flags, fd, offset)
	caddr_t addr;
	size_t	len;
	int	prot;
	int	flags;
	int	fd;
	off_t	offset;
{

D 2
	return((caddr_t)indir(SYS_mmap, addr, len, prot, flags, fd, 0, offset));
E 2
I 2
D 3
	return((caddr_t)__indir(SYS_mmap, addr, len, prot, flags, fd, 0,
E 3
I 3
D 5
	return((caddr_t)__indir((quad_t)SYS_mmap, addr, len, prot, flags, fd, 0,
E 3
		offset));
E 5
I 5
	return((caddr_t)__syscall((quad_t)SYS_mmap, addr, len, prot, flags,
		fd, 0, offset));
E 5
E 2
}
E 1
