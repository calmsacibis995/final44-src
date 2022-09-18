h11090
s 00002/00002/00153
d D 8.1 93/06/06 11:51:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00152
d D 5.5 92/05/31 10:41:57 pendry 5 4
c code refresh
e
s 00001/00001/00153
d D 5.4 92/02/09 08:31:03 pendry 4 3
c merge in new release
e
s 00004/00004/00150
d D 5.3 91/05/12 15:58:52 pendry 3 2
c checkpoint for network tape
e
s 00003/00003/00151
d D 5.2 91/03/17 13:49:18 pendry 2 1
c from amd5.3 alpha11
e
s 00154/00000/00000
d D 5.1 90/06/29 12:41:08 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-aix3.h,v 5.2 90/06/23 22:20:33 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-aix3.h,v 5.2.1.1 90/10/21 22:30:38 jsp Exp $ */
E 2

E 3
/*
D 3
 * AIX 3.1 definitions for Amd (automounter)
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
 * $Id: os-aix3.h,v 5.2.1.2 91/05/07 22:19:25 jsp Alpha $
E 4
I 4
D 5
 * $Id: os-aix3.h,v 5.2.2.1 1992/02/09 15:10:03 jsp beta $
E 5
I 5
 * $Id: os-aix3.h,v 5.2.2.2 1992/05/31 16:38:49 jsp Exp $
E 5
E 4
 *
 * AIX 3.1 definitions for Amd (automounter)
E 3
 */

/*
 * Does the compiler grok void *
 */
#define	VOIDP

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	RPC_4

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_AIX3

/*
 * Does this OS have NDBM support?
 */
#define OS_HAS_NDBM

/*
 * The mount table is obtained from the kernel
 */
#undef	UPDATE_MTAB

/*
 * Pick up BSD bits from include files
I 5
 * Try for 4.4 compatibility if available (AIX 3.2 and later)
E 5
 */
D 5
#define	_BSD
E 5
I 5
#define	_BSD 44
E 5

/*
 * No mntent info on AIX 3
 */
#undef	MNTENT_HDR
#define	MNTENT_HDR <sys/mntctl.h>

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	MNT_NFS
#define	MOUNT_TYPE_UFS	MNT_JFS
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"jfs"

/*
 * How to unmount filesystems
 */
#undef MOUNT_TRAP
#define	MOUNT_TRAP(type, mnt, flag, mnt_data) \
	aix3_mount(mnt->mnt_fsname, mnt->mnt_dir, flag, type, mnt_data, mnt->mnt_opts)
#undef	UNMOUNT_TRAP
#define	UNMOUNT_TRAP(mnt)	uvmount(mnt->mnt_passno, 0)


/*
 * Byte ordering
 */
#ifndef BYTE_ORDER
#include <sys/machine.h>
#endif /* BYTE_ORDER */

#undef ARCH_ENDIAN
#if BYTE_ORDER == LITTLE_ENDIAN
#define ARCH_ENDIAN "little"
#else
#if BYTE_ORDER == BIG_ENDIAN
#define ARCH_ENDIAN "big"
#else
XXX - Probably no hope of running Amd on this machine!
#endif /* BIG */
#endif /* LITTLE */

/*
 * Miscellaneous AIX 3 bits
 */
#define	NEED_MNTOPT_PARSER
#define	SHORT_MOUNT_NAME

#define	MNTMAXSTR       128

#define	MNTTYPE_UFS	"jfs"		/* Un*x file system */
#define	MNTTYPE_NFS	"nfs"		/* network file system */
#define	MNTTYPE_IGNORE	"ignore"	/* No type specified, ignore this entry */

struct mntent {
	char	*mnt_fsname;	/* name of mounted file system */
	char	*mnt_dir;	/* file system path prefix */
	char	*mnt_type;	/* MNTTYPE_* */
	char	*mnt_opts;	/* MNTOPT* */
	int	mnt_freq;	/* dump frequency, in days */
	int	mnt_passno;	/* pass number on parallel fsck */
};

#define	NFS_HDR "misc-aix3.h"
#define	UFS_HDR "misc-aix3.h"
#undef NFS_FH_DREF
D 2
#define	NFS_FH_DREF(dst, src) { (dst).addr = *(src); }
E 2
I 2
#define	NFS_FH_DREF(dst, src) { (dst) = *(src); }
E 2
#undef NFS_SA_DREF
#define	NFS_SA_DREF(dst, src) { (dst).addr = *(src); }
#define	M_RDONLY MNT_READONLY

/*
 * How to get a mount list
 */
#undef	READ_MTAB_FROM_FILE
#define	READ_MTAB_AIX3_STYLE

/*
 * The data for the mount syscall needs the path in addition to the
 * host name since that is the only source of information about the
 * mounted filesystem.
#define	NFS_ARGS_NEEDS_PATH
 */

#define	NFS_LOMAP	34
#define	NFS_HIMAP	99
#define NFS_ERROR_MAPPING \
static nfs_errormap[] = {	     0,75,77,99,99,99, \
			99,99,99,99,99,78,99,99,99,79, \
			99,99,70,99,35,36,37,38,39,40, \
			41,42,43,44,45,46,47,48,49,50, \
			51,52,53,54,55,56,57,58,60,61, \
			64,65,99,67,68,62,63,66,69,68, \
			99,99,99,71,99,99,99,99,99,99 \
			};

D 2
#define	MOUNT_AIX3
E 2
I 2
#define	MOUNT_HELPER_SOURCE "mount_aix.c"
E 2

/*
 * Need this too
 */
#include <time.h>
E 1
