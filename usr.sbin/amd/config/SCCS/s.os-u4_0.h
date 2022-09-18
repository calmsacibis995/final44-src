h43815
s 00002/00002/00130
d D 8.1 93/06/06 11:52:16 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00131
d D 5.4 92/02/09 08:31:38 pendry 4 3
c merge in new release
e
s 00010/00006/00122
d D 5.3 91/05/12 15:59:05 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00127
d D 5.2 91/03/17 13:49:54 pendry 2 1
c from amd5.3 alpha11
e
s 00140/00000/00000
d D 5.1 91/03/17 11:49:07 pendry 1 0
c date and time created 91/03/17 11:49:07 by pendry
e
u
U
t
T
I 1
D 3
/* $Id: os-u4_0.h,v 5.2 91/03/03 20:22:45 jsp Alpha $ */

E 3
/*
D 3
 * Ultrix 4.0 definitions for Amd (automounter)
 *		from Chris Lindblad <cjl@ai.mit.edu>
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
 * $Id: os-u4_0.h,v 5.2.1.1 91/05/07 22:20:04 jsp Alpha $
E 4
I 4
 * $Id: os-u4_0.h,v 5.2.2.1 1992/02/09 15:10:53 jsp beta $
E 4
 *
 * Ultrix 4.0 definitions for Amd (automounter)
 *		from Chris Lindblad <cjl@ai.mit.edu>
E 3
 */

/*
 * Does the compiler grok void *
 */
D 3
#undef	VOIDP
E 3
I 3
#ifdef __STDC__
#define VOIDP
#else
#undef VOIDP
#endif
E 3

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
#if defined(vax) || defined(mips)
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
#define	HAS_SYSLOG

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

#define	MNTMAXSTR	128

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

#define	NEED_CLNT_SPERRNO

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
