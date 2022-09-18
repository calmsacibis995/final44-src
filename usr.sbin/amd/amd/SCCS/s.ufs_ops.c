h51796
s 00002/00002/00150
d D 8.2 95/05/10 05:38:48 pendry 6 5
c add support for new nfs code (not v3 though)
e
s 00002/00002/00150
d D 8.1 93/06/06 11:41:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00151
d D 5.4 92/02/09 08:49:08 pendry 4 3
c merge in new release
e
s 00003/00002/00149
d D 5.3 91/05/12 15:56:11 pendry 3 2
c checkpoint for network tape
e
s 00019/00019/00132
d D 5.2 91/03/17 13:34:04 pendry 2 1
c from amd5.3 alpha11
e
s 00151/00000/00000
d D 5.1 90/06/29 12:01:21 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: ufs_ops.c,v 5.2 90/06/23 22:20:03 jsp Rel $
E 2
I 2
D 3
 * $Id: ufs_ops.c,v 5.2.1.1 90/10/21 22:29:47 jsp Exp $
E 2
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
 * $Id: ufs_ops.c,v 5.2.1.2 91/05/07 22:18:38 jsp Alpha $
E 4
I 4
 * $Id: ufs_ops.c,v 5.2.2.1 1992/02/09 15:09:08 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef HAS_UFS

#include <sys/stat.h>
#ifdef NFS_3
typedef nfs_fh fhandle_t;
#endif /* NFS_3 */
D 2
#include <sys/mount.h>
E 2

I 6
#include <sys/mount.h>

E 6
#ifdef UFS_HDR
#include UFS_HDR
#endif /* UFS_HDR */
D 6

I 2
#include <sys/mount.h>
E 6

E 2
/*
 * UN*X file system
 */

/*
 * UFS needs local filesystem and device.
 */
D 2
static int ufs_match(fo)
E 2
I 2
static char *ufs_match P((am_opts *fo));
static char *ufs_match(fo)
E 2
am_opts *fo;
{
	if (!fo->opt_dev) {
		plog(XLOG_USER, "ufs: no device specified");
		return 0;
	}
D 2
	/*
	 * Determine magic cookie to put in mtab
	 */
	fo->fs_mtab = strealloc(fo->fs_mtab, fo->opt_dev);
E 2
I 2

E 2
#ifdef DEBUG
	dlog("UFS: mounting device \"%s\" on \"%s\"",
		fo->opt_dev, fo->opt_fs);
#endif /* DEBUG */

D 2
	return 1;
E 2
I 2
	/*
	 * Determine magic cookie to put in mtab
	 */
	return strdup(fo->opt_dev);
E 2
}

static mount_ufs(dir, fs_name, opts)
char *dir;
char *fs_name;
char *opts;
{
	struct ufs_args ufs_args;
	struct mntent mnt;
	int flags;

	/*
	 * Figure out the name of the file system type.
	 */
#ifdef M_NEWTYPE
	char *type = MOUNT_TYPE_UFS;
#else
	int type = MOUNT_TYPE_UFS;
#endif /* M_NEWTYPE */

	bzero((voidp) &ufs_args, sizeof(ufs_args));	/* Paranoid */

	/*
	 * Fill in the mount structure
	 */
	mnt.mnt_dir = dir;
	mnt.mnt_fsname = fs_name;
	mnt.mnt_type = MTAB_TYPE_UFS;
	mnt.mnt_opts = opts;
	mnt.mnt_freq = 1;
	mnt.mnt_passno = 2;

	flags = compute_mount_flags(&mnt);

#ifdef ULTRIX_HACK
	ufs_args.ufs_flags = flags;
	ufs_args.ufs_pgthresh = 64; /* 64K - XXX */
	flags &= M_RDONLY;
#else
	ufs_args.fspec = fs_name;
#endif /* ULTRIX_HACK */

	/*
	 * Call generic mount routine
	 */
	return mount_fs(&mnt, flags, (caddr_t) &ufs_args, 0, type);
}

/*ARGSUSED*/
D 2
static int ufs_mount(mp)
am_node *mp;
E 2
I 2
static int ufs_fmount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	int error;

D 2
	error = mount_ufs(mf->mf_mount, mf->mf_info, mf->mf_fo->opt_opts);
E 2
I 2
	error = mount_ufs(mf->mf_mount, mf->mf_info, mf->mf_mopts);
E 2
	if (error) {
		errno = error;
		plog(XLOG_ERROR, "mount_ufs: %m");
		return error;
	}

	return 0;
}

D 2
static int ufs_umount(mp)
am_node *mp;
E 2
I 2
static int ufs_fumount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	return UMOUNT_FS(mf->mf_mount);
}

/*
 * Ops structure
 */
am_ops ufs_ops = {
	"ufs",
	ufs_match,
	0, /* ufs_init */
D 2
	ufs_mount,
	ufs_umount,
E 2
I 2
	auto_fmount,
	ufs_fmount,
	auto_fumount,
	ufs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* ufs_readlink */
	0, /* ufs_mounted */
	0, /* ufs_umounted */
	find_afs_srvr,
#ifdef FLUSH_KERNEL_NAME_CACHE
	FS_MKMNT|FS_NOTIMEOUT|FS_UBACKGROUND|FS_AMQINFO
#else /* FLUSH_KERNEL_NAME_CACHE */
	FS_MKMNT|FS_NOTIMEOUT|FS_UBACKGROUND|FS_AMQINFO
#endif /* FLUSH_KERNEL_NAME_CACHE */
};

#endif /* HAS_UFS */
E 1
