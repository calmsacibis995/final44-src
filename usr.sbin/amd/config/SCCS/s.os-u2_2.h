h27947
s 00002/00002/00133
d D 8.1 93/06/06 11:52:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00134
d D 5.4 92/02/09 08:31:35 pendry 4 3
c merge in new release
e
s 00004/00004/00131
d D 5.3 91/05/12 15:59:03 pendry 3 2
c checkpoint for network tape
e
s 00003/00002/00132
d D 5.2 91/03/17 13:49:50 pendry 2 1
c from amd5.3 alpha11
e
s 00134/00000/00000
d D 5.1 90/06/29 12:41:19 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-u2_2.h,v 5.2 90/06/23 22:20:55 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-u2_2.h,v 5.2.1.2 90/11/04 23:17:43 jsp Exp $ */
E 2

E 3
/*
D 3
 * Ultrix 2.2 definitions for Amd (automounter)
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: os-u2_2.h,v 5.2.1.3 91/05/07 22:19:59 jsp Alpha $
E 4
I 4
 * $Id: os-u2_2.h,v 5.2.2.1 1992/02/09 15:10:48 jsp beta $
E 4
 *
 * Ultrix 2.2 definitions for Amd (automounter)
E 3
 */

/*
 * Does the compiler grok void *
 */
#undef	VOIDP

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
#undef	ARCH_ENDIAN
#if defined(vax)
#define	ARCH_ENDIAN "little"
#endif

/*
 * The mount table is obtained from the kernel
 */
#undef	UPDATE_MTAB

/*
 * No mntent info on Ultrix
  */
#undef	MNTENT_HDR

/*
 * No support for syslog()
 */
#undef	HAS_SYSLOG

/*
 * No support for ndbm
 */
#undef	HAS_NDBM_MAPS

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	GT_NFS
#define	MOUNT_TYPE_UFS	GT_ULTRIX
#undef	MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"ufs"

/*
 * Name of mount & unmount system calls
 */
#undef	MOUNT_TRAP
#define	MOUNT_TRAP(type, mnt, flag, mnt_data) \
	mount(mnt->mnt_fsname, mnt->mnt_dir, flag, type, mnt_data)
#undef	UNMOUNT_TRAP
#define	UNMOUNT_TRAP(mnt)	umount(mnt->mnt_passno)

/*
 * Miscellaneous Ultrix bits
 */
#define	M_RDONLY	M_RONLY

#ifndef MNTMAXSTR
#define	MNTMAXSTR       128
#endif

#define	MNTTYPE_UFS	"ufs"		/* Un*x file system */
#define	MNTTYPE_NFS	"nfs"		/* network file system */
#define	MNTTYPE_IGNORE	"ignore"	/* No type specified, ignore this entry */

#define	MNTOPT_RO	"ro"		/* read only */
#define	MNTOPT_RW	"rw"		/* read/write */
#define	MNTOPT_QUOTA	"quota"		/* quotas */
#define	MNTOPT_NOQUOTA	"noquota"	/* no quotas */
#define	MNTOPT_HARD	"hard"		/* hard mount */
#define	MNTOPT_SOFT	"soft"		/* soft mount */
#define	MNTOPT_INTR	"intr"		/* interrupts allowed */

#define	MNTOPT_NOSUID	"nosuid"	/* no set uid allowed */

struct mntent {
	char	*mnt_fsname;	/* name of mounted file system */
	char	*mnt_dir;	/* file system path prefix */
	char	*mnt_type;	/* MNTTYPE_* */
	char	*mnt_opts;	/* MNTOPT* */
	int	mnt_freq;	/* dump frequency, in days */
	int	mnt_passno;	/* pass number on parallel fsck */
};
#define	MOUNTED		"/etc/mtab"

#define	NFS_HDR	"misc-ultrix.h"
#define	UFS_HDR	"misc-ultrix.h"

D 2
#define	MISC_RPC
E 2
I 2
#define NEED_XDR_POINTER
#define	NEED_CLNT_SPERRNO
E 2

#define	nfs_args	nfs_gfs_mount
#define	ULTRIX_HACK	/* Should be handled better than this !! */
#define	NEED_MNTOPT_PARSER

/*
 * How to get a mount list
 */
#undef	READ_MTAB_FROM_FILE
#define	READ_MTAB_ULTRIX_STYLE

/*
 * Need precise length links
 */
#define	PRECISE_SYMLINKS
E 1
