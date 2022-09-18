h42872
s 00001/00001/00031
d D 8.2 94/10/09 22:21:33 mckusick 11 10
c fix checksum so it does not use illegal lvalue cast (from mycroft)
e
s 00002/00002/00030
d D 8.1 93/06/11 16:27:22 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00031
d D 7.5 92/06/22 22:53:13 bostic 9 8
c fix the includes
e
s 00001/00000/00035
d D 7.4 92/05/14 16:26:09 heideman 8 6
c lfs_extern.h requires #include <sys/vnode.h>
e
s 00001/00000/00035
d R 7.4 92/05/14 16:23:17 heideman 7 6
c lfs_extern.h requires lfs_cksum.c
e
s 00004/00002/00031
d D 7.3 92/05/04 17:23:20 bostic 6 5
c some compilers can't handle the appended increment (MIPS)
e
s 00000/00000/00033
d D 7.2 91/12/06 16:40:28 bostic 5 4
c LFS version 2; no changes required
e
s 00002/00002/00031
d D 7.1 91/11/01 17:38:04 bostic 4 3
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00007/00003/00026
d D 5.3 91/11/01 17:29:25 bostic 3 2
c checkpoint before integration
e
s 00004/00002/00025
d D 5.2 91/10/02 09:00:26 bostic 2 1
c checkpoint
e
s 00027/00000/00000
d D 5.1 91/09/25 14:31:38 bostic 1 0
c date and time created 91/09/25 14:31:38 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 3
#ifdef LOGFS
E 2
#include <sys/types.h>
E 3
I 3
D 9
#include <sys/param.h>
I 8
#include <sys/vnode.h>
E 8
E 3

I 3
D 4
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 4
I 4
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 9
I 9
#include <sys/types.h>
E 9
E 4

E 3
/*
D 2
 * cksum --
 *	Simple, general purpose, fast checksum.
E 2
I 2
 * Simple, general purpose, fast checksum.  Data must be short-aligned.
 * Returns a u_long in case we ever want to do something more rigorous.
I 3
 *
 * XXX
 * Use the TCP/IP checksum instead.
E 3
E 2
 */
u_long
cksum(str, len)
	register void *str;
	register size_t len;
{
	register u_long sum;
	
	len &= ~(sizeof(u_short) - 1);
D 6
	for (sum = 0; len; len -= sizeof(u_short))
		sum ^= *((u_short *)str)++;
E 6
I 6
	for (sum = 0; len; len -= sizeof(u_short)) {
		sum ^= *(u_short *)str;
D 11
		++(u_short *)str;
E 11
I 11
		str = (void *)((u_short *)str + 1);
E 11
	}
E 6
	return (sum);
}
I 2
D 3
#endif /* LOGFS */
E 3
E 2
E 1
