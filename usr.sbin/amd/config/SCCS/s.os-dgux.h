h27754
s 00002/00002/00086
d D 8.1 93/06/06 11:51:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00087
d D 5.4 92/02/09 08:31:15 pendry 4 3
c merge in new release
e
s 00004/00004/00084
d D 5.3 91/05/12 15:58:58 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00087
d D 5.2 91/03/17 13:49:29 pendry 2 1
c from amd5.3 alpha11
e
s 00100/00000/00000
d D 5.1 91/03/17 11:49:01 pendry 1 0
c date and time created 91/03/17 11:49:01 by pendry
e
u
U
t
T
I 1
D 3
/* $Id: os-dgux.h,v 5.2.1.1 90/10/21 22:30:50 jsp Exp $ */

E 3
/*
D 3
 * dg/ux definitions for Amd (automounter)
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: os-dgux.h,v 5.2.1.2 91/05/07 22:19:39 jsp Alpha $
E 4
I 4
 * $Id: os-dgux.h,v 5.2.2.1 1992/02/09 15:10:18 jsp beta $
E 4
 *
 * dg/ux definitions for Amd (automounter)
E 3
 */

/*
 * Does the compiler grok void *
 */
#define VOIDP

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define RPC_4

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define NFS_4

/*
 * Name of filesystem types
 */
#define MOUNT_TYPE_NFS	"nfs"
#define MOUNT_TYPE_UFS	"dg/ux"
#undef MTAB_TYPE_UFS
#define MTAB_TYPE_UFS	"dg/ux"

/*
 * Need the following in more places than just NFS_HDR
 */
#include <sys/dg_mount.h>
/*
 * This is braindead
 * dg/ux has nfs 4.0 but doesn't have the following options
 */
#define NFSMNT_HOSTNAME 0x0
#define NFSMNT_INT 0x0
#define M_NEWTYPE 0

/*
 * DG have their own filesystem.
 */
#define ufs_args dgux_args

/*
 * Byte ordering
 */

#undef ARCH_ENDIAN
#define ARCH_ENDIAN "big"

#define _BSD_WAIT_FLAVOR
#define _BSD_TTY_FLAVOR
#define _BSD_SIGNAL_FLAVOR
#define _DGUX_SOURCE

/*
 * Use fcntl() rather than flock()
 */
#define LOCK_FCNTL

#define bzero(ptr, len) memset(ptr, 0, len)
#define bcopy(from, to, len) memcpy(to, from, len)
#undef MOUNT_TRAP
#define MOUNT_TRAP(type, mnt, flags, mnt_data) \
	((struct nfs_args *)mnt_data)->version = !strcmp(type, MOUNT_TYPE_UFS)?\
	     DG_MOUNT_DGUX_VERSION:DG_MOUNT_NFS_VERSION, \
	dg_mount(type, mnt->mnt_dir, flags, mnt_data)
#undef UNMOUNT_TRAP
#define UNMOUNT_TRAP(mnt)	umount(mnt->mnt_dir)
E 1
