h08263
s 00037/00000/00165
d D 8.2 95/05/10 05:38:23 pendry 7 6
c add support for new nfs code (not v3 though)
e
s 00002/00002/00163
d D 8.1 93/06/06 11:51:12 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00160
d D 5.5 93/05/22 02:34:23 pendry 5 4
c use strerror
e
s 00004/00001/00156
d D 5.4 92/02/09 08:31:07 pendry 4 3
c merge in new release
e
s 00004/00004/00153
d D 5.3 91/05/12 15:58:53 pendry 3 2
c checkpoint for network tape
e
s 00013/00003/00144
d D 5.2 91/03/17 13:49:22 pendry 2 1
c from amd5.3 alpha11
e
s 00147/00000/00000
d D 5.1 90/06/29 12:41:10 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-bsd44.h,v 5.2 90/06/23 22:20:38 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-bsd44.h,v 5.2.1.2 90/11/04 23:17:39 jsp Exp $ */
E 2

E 3
/*
D 3
 * 4.4 BSD definitions for Amd (automounter)
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
 * $Id: os-bsd44.h,v 5.2.1.4 91/05/07 22:19:32 jsp Alpha $
E 4
I 4
 * $Id: os-bsd44.h,v 5.2.2.1 1992/02/09 15:10:11 jsp beta $
E 4
 *
 * 4.4 BSD definitions for Amd (automounter)
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
D 2
#define	RPC_3
E 2
I 2
#define	RPC_4
E 2

I 7
#include <sys/param.h>
#if BSD >= 199506
#define NFS_HDR "misc-bsd44l.h"
#define UFS_HDR "misc-bsd44l.h"
#endif

E 7
/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_44
#define HAS_TCP_NFS

/*
 * Does this OS have NDBM support?
 */
#define OS_HAS_NDBM

/*
I 2
 * 4.4 doesn't provide NIS.
 */
#undef HAS_NIS_MAPS

/*
I 5
 * OS provides strerror()
 */
#define HAS_STRERROR

/*
E 5
E 2
 * The mount table is obtained from the kernel
 */
#undef	UPDATE_MTAB

/*
 * No mntent info on 4.4 BSD
 */
#undef	MNTENT_HDR

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	MOUNT_NFS
#define	MOUNT_TYPE_UFS	MOUNT_UFS
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"ufs"
#define	MTAB_TYPE_MFS	"mfs"

/*
 * How to unmount filesystems
 */
#undef UNMOUNT_TRAP
#undef	NEED_UMOUNT_FS
#define	NEED_UMOUNT_BSD

/*
 * How to copy an address into an NFS filehandle
 */
#undef NFS_SA_DREF
I 7
#if BSD >= 199506
E 7
#define	NFS_SA_DREF(dst, src) { \
		(dst).addr = (struct sockaddr *) (src); \
I 4
		(dst).addrlen = sizeof(*src); \
E 4
		(dst).sotype = SOCK_DGRAM; \
		(dst).proto = 0; \
I 7
		(dst).fhsize = FHSIZE; \
		(dst).wsize = NFS_WSIZE; \
		(dst).rsize =  NFS_RSIZE; \
		(dst).readdirsize =  NFS_READDIRSIZE; \
		(dst).timeo = 10; \
		(dst).retrans = NFS_RETRANS; \
		(dst).maxgrouplist = NFS_MAXGRPS; \
		(dst).readahead = NFS_DEFRAHEAD; \
		(dst).leaseterm = 0; \
		(dst).deadthresh = 0; \
E 7
	}
I 7
#else
#define	NFS_SA_DREF(dst, src) { \
		(dst).addr = (struct sockaddr *) (src); \
		(dst).addrlen = sizeof(*src); \
		(dst).sotype = SOCK_DGRAM; \
		(dst).proto = 0; \
	}
#endif
E 7

/*
 * Byte ordering
 */
#ifndef BYTE_ORDER
#include <machine/endian.h>
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
 * Miscellaneous 4.4 BSD bits
 */
D 2
#define MISC_RPC
E 2
#define	NEED_MNTOPT_PARSER
#define	SHORT_MOUNT_NAME

#define	MNTMAXSTR       128

#define	MNTTYPE_UFS	"ufs"		/* Un*x file system */
#define	MNTTYPE_NFS	"nfs"		/* network file system */
#define	MNTTYPE_MFS	"mfs"		/* memory file system */
#define	MNTTYPE_IGNORE	"ignore"	/* No type specified, ignore this entry */

#define	M_RDONLY	MNT_RDONLY
#define	M_SYNC		MNT_SYNCHRONOUS
#define	M_NOEXEC	MNT_NOEXEC
#define	M_NOSUID	MNT_NOSUID
#define	M_NODEV		MNT_NODEV

#define	MNTOPT_SOFT	"soft"		/* soft mount */
#define	MNTOPT_INTR	"intr"		/* interrupts allowed */
I 4

#define NFSMNT_HOSTNAME	0		/* hostname on 4.4 is not optional */
E 4

struct mntent {
	char	*mnt_fsname;	/* name of mounted file system */
	char	*mnt_dir;	/* file system path prefix */
	char	*mnt_type;	/* MNTTYPE_* */
	char	*mnt_opts;	/* MNTOPT* */
	int	mnt_freq;	/* dump frequency, in days */
	int	mnt_passno;	/* pass number on parallel fsck */
};

/*
 * Type of a file handle
 */
#undef NFS_FH_TYPE
I 7
#if BSD >= 199506
#define NFS_FH_TYPE	void *
#else
E 7
#define	NFS_FH_TYPE	nfsv2fh_t *
I 7
#endif
E 7

/*
 * How to get a mount list
 */
#undef	READ_MTAB_FROM_FILE
#define	READ_MTAB_BSD_STYLE

/*
 * The data for the mount syscall needs the path in addition to the
 * host name since that is the only source of information about the
 * mounted filesystem.
 */
#define	NFS_ARGS_NEEDS_PATH
I 2

/*
 * 4.4 has RE support built in
 */
#undef RE_HDR
#define RE_HDR <regexp.h>
I 7

#if BSD >= 199506
#undef MTYPE_TYPE
#define MTYPE_TYPE	char *
#define MOUNT_NFS "nfs"
#define MOUNT_UFS "ffs"
#define MOUNT_MFS "mfs"
#endif
E 7
E 2
E 1
