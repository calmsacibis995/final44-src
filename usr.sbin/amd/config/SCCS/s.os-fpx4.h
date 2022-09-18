h53139
s 00002/00002/00064
d D 8.1 93/06/06 11:51:29 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00062
d D 5.5 92/05/31 10:41:59 pendry 5 4
c code refresh
e
s 00001/00001/00063
d D 5.4 92/02/09 08:31:16 pendry 4 3
c merge in new release
e
s 00005/00005/00059
d D 5.3 91/05/12 15:59:11 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00063
d D 5.2 91/03/17 13:49:31 pendry 2 1
c from amd5.3 alpha11
e
s 00064/00000/00000
d D 5.1 90/06/29 12:41:12 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-fpx4.h,v 5.2 90/06/23 22:20:45 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-fpx4.h,v 5.2.1.1 90/10/21 22:30:51 jsp Exp $ */
E 2

E 3
/*
D 3
 * Celerity FPX 4.1/2 definitions for Amd (automounter)
 *      from Stephen Pope <scp@grizzly.acl.lanl.gov>
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: os-fpx4.h,v 5.2.1.2 91/05/07 22:19:40 jsp Alpha $
E 4
I 4
D 5
 * $Id: os-fpx4.h,v 5.2.2.1 1992/02/09 15:10:19 jsp beta $
E 5
I 5
 * $Id: os-fpx4.h,v 5.2.2.2 1992/05/31 16:39:34 jsp Exp $
E 5
E 4
 *
 * Celerity FPX 4.1/2 definitions for Amd (automounter)
 *      from Stephen Pope <scp@grizzly.acl.lanl.gov>
E 3
 */

/*
 * FPX wants to include sys headers multiple times
 */
#define INCLUDE_HEADERS

/*
 * FPX sys/mount.h includes sys/nfs.h; prevent this
 */
#define INCLUDED_nfs

/*
 * FPX doesn't define NMOUNT anywhere
 */
#define NMOUNT 40

/*
 * Does the compiler grok void *
 */
/* #define VOIDP */

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
D 5
#define RPC_3
E 5
I 5
#define	RPC_4
#define	svc_fdset svc_fds
#define	svc_getreqset(p) svc_getreq((*p).fds_bits[0])
E 5

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define NFS_3

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
#define ARCH_ENDIAN     "big"

/*
 * Name of filesystem types
 */
#define MOUNT_TYPE_NFS MOUNT_NFS
#define MOUNT_TYPE_UFS MOUNT_UFS
E 1
