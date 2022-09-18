h04745
s 00002/00002/00080
d D 8.1 93/06/06 11:52:05 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00016/00078
d D 5.2 92/07/21 13:22:57 bostic 2 1
c fix copyright
e
s 00094/00000/00000
d D 5.1 92/07/21 13:21:51 bostic 1 0
c date and time created 92/07/21 13:21:51 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Amd (automounter) definitions for Stellix.
 * From Stephen C. Pope <scp@acl.lanl.gov>
 *
E 2
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
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
I 2
 *
 * Amd (automounter) definitions for Stellix.
 * From Stephen C. Pope <scp@acl.lanl.gov>
E 2
 *
 * $Id: os-stellix.h,v 5.2.2.1 1992/02/09 15:10:43 jsp beta $
 */

#define RPC_3

#define NFS_3

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
#define	ARCH_ENDIAN	"big"

#define HAS_SYSLOG

#define OS_HAS_NDBM

#define UPDATE_MTAB

#define USE_FCNTL

#define LOCK_FCNTL

/*
 * Name of filesystem types
 */
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"sfs"

#define MOUNT_TYPE_UFS sysfs(GETFSIND, "SFS1")
#define MOUNT_TYPE_NFS sysfs(GETFSIND, "NFS")

#define SYS5_SIGNALS
#define HAS_SVR3_SIGNALS

#define MOUNT_HELPER_SOURCE "mount_stellix.c"

/*
 * Name of mount & unmount system calls
 *
 * NOTE:
 *  UNMOUNT_TRAP takes a struct mntent *
 */
#undef MOUNT_TRAP
#define	MOUNT_TRAP(type, mnt, flags, mnt_data) \
	stellix_mount(mnt->mnt_fsname, mnt->mnt_dir, flags, type, mnt_data)
#undef UNMOUNT_TRAP
#define	UNMOUNT_TRAP(mnt)	umount(mnt->mnt_dir)

/*
 * How to unmount filesystems.
 * NEED_UMOUNT_FS includes code to scan the mount table
 * to find the correct information for the unmount system
 * call.  Some systems, such as 4.4bsd, do not require
 * this - they can just do an unmount system call directly.
 */
/* #define	NEED_UMOUNT_FS */
/* #define	UMOUNT_FS(dir)	umount_fs(dir) */

#define NFS_HDR "misc-stellix.h"
#define UFS_HDR "misc-stellix.h"

#define M_RDONLY        0x01            /* mount fs read only */

#define bzero(ptr, len) memset(ptr, 0, len)
#define bcopy(from, to, len) memcpy(to, from, len)
E 1
