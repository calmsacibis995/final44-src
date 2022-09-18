h06013
s 00002/00002/00122
d D 8.1 93/06/06 11:51:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00123
d D 5.4 92/02/09 08:31:21 pendry 4 3
c merge in new release
e
s 00004/00004/00120
d D 5.3 91/05/12 15:58:59 pendry 3 2
c checkpoint for network tape
e
s 00022/00012/00102
d D 5.2 91/03/17 13:49:37 pendry 2 1
c from amd5.3 alpha11
e
s 00114/00000/00000
d D 5.1 90/06/29 12:41:16 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-hpux.h,v 5.2 90/06/23 22:20:47 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-hpux.h,v 5.2.1.4 91/03/03 20:49:43 jsp Alpha $ */
E 2

E 3
/*
D 3
 * HP/9000 HP-UX definitions for Amd (automounter)
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 * $Id: os-hpux.h,v 5.2.1.5 91/05/07 22:19:44 jsp Alpha $
E 4
I 4
 * $Id: os-hpux.h,v 5.2.2.1 1992/02/09 15:10:23 jsp beta $
E 4
 *
 * HP/9000 HP-UX definitions for Amd (automounter)
E 3
 */

/*
 * Does the compiler grok void *
 */
#ifdef __GNUC__
#define	VOIDP
#endif

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	RPC_3

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_3

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
D 2
#if defined(hp9000s200) || defined(hp9000s300)
E 2
I 2
#if defined(hp9000s200) || defined(hp9000s300) || defined(hp9000s800)
E 2
#define	ARCH_ENDIAN	"big"
#endif
D 2
/*
#if defined(hp9000s800)
#define ARCH_ENDIAN	"unknown"
E 2
I 2

#ifndef __hpux
#define	HPUX_VERSION_6
E 2
#endif
D 2
*/
E 2

/*
D 2
 * No support for syslog()
E 2
I 2
 * No support for syslog() prior to 7.0
E 2
 */
I 2
#ifdef HPUX_VERSION_6
E 2
#undef HAS_SYSLOG
I 2
#endif
E 2

/*
 * No support for ndbm
 */
#undef OS_HAS_NDBM

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_UFS	MOUNT_UFS
#define MOUNT_TYPE_NFS MOUNT_NFS
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"hfs"

/*
 * Where to get NFS definitions
 */
#define	NFS_HDR "misc-hpux.h"

/*
 * Where to get union wait
 */
#undef WAIT
#define	WAIT	"uwait.h"
D 2
#ifndef SIGCHLD
E 2
I 2
#ifdef HPUX_VERSION_6
E 2
#define SIGCHLD	SIGCLD
#endif
#define	SYS5_SIGNALS

/*
 * Miscellaneous HP-UX definitions
 */

D 2
#define	MISC_RPC
E 2
I 2
#define NEED_XDR_POINTER
#define	NEED_CLNT_SPERRNO
E 2

/*
 * Use <fcntl.h> rather than <sys/file.h>
 */
#define USE_FCNTL

/*
 * Use fcntl() rather than flock()
 */
#define LOCK_FCNTL

D 2
#ifdef __GNUC__
#define alloca(sz) __builtin_alloca(sz)
#endif
E 2
I 2
/*
 * Additional fields in struct mntent
 * are fixed up here
 */
#define FIXUP_MNTENT(mntp) { \
	(mntp)->mnt_time = clocktime(); \
}
#define FIXUP_MNTENT_DUP(mntp, mp) { \
	(mntp)->mnt_time = (mp)->mnt_time; \
}

E 2
#define	bzero(ptr, len)	memset(ptr, 0, len)
#define bcopy(from, to, len) memcpy(to, from, len)
#define getpagesize() (2048)
#undef MOUNT_TRAP
#define MOUNT_TRAP(type, mnt, flags, mnt_data) \
	vfsmount(type, mnt->mnt_dir, flags, mnt_data)
#undef UNMOUNT_TRAP
#define	UNMOUNT_TRAP(mnt)	umount(mnt->mnt_dir)
#define NFDS	30	/* conservative */
#define	MOUNTED MNT_MNTTAB
E 1
