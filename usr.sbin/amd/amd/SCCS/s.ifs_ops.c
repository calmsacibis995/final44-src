h27071
s 00002/00002/00167
d D 8.1 93/06/06 11:39:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00168
d D 5.4 92/02/09 08:48:09 pendry 4 3
c merge in new release
e
s 00003/00002/00166
d D 5.3 91/05/12 15:55:12 pendry 3 2
c checkpoint for network tape
e
s 00051/00022/00117
d D 5.2 91/03/17 13:33:03 pendry 2 1
c from amd5.3 alpha11
e
s 00139/00000/00000
d D 5.1 90/06/29 12:01:04 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: ifs_ops.c,v 5.2 90/06/23 22:19:28 jsp Rel $
E 2
I 2
D 3
 * $Id: ifs_ops.c,v 5.2.1.3 91/03/17 17:47:48 jsp Alpha $
E 2
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
 * $Id: ifs_ops.c,v 5.2.1.4 91/05/07 22:17:55 jsp Alpha $
E 4
I 4
 * $Id: ifs_ops.c,v 5.2.2.1 1992/02/09 15:08:26 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef HAS_IFS

/*
 * Inheritance file system.
 * This implements a filesystem restart.
 *
 * This is a *gross* hack - it knows far too
 * much about the way other parts of the
 * sytem work.  See restart.c too.
 */
static char not_a_filesystem[] = "Attempting to inherit not-a-filesystem";
/*
 * This should never be called.
 */
D 2
static int ifs_match()
E 2
I 2
/*ARGSUSED*/
static char *ifs_match P((am_opts *fo));
static char *ifs_match(fo)
am_opts *fo;
E 2
{
	plog(XLOG_FATAL, "ifs_match called!");
D 2
	return FALSE;
E 2
I 2
	return 0;
E 2
}

I 2
static int ifs_init P((mntfs *mf));
E 2
static int ifs_init(mf)
mntfs *mf;
{
	mntfs *mf_link = (mntfs *) mf->mf_private;
	if (mf_link == 0) {
		plog(XLOG_FATAL, not_a_filesystem);
		return EINVAL;
	}
I 2
#ifdef notdef
E 2
	/*
	 * Fill in attribute fields
	 */
	mf_link->mf_fattr.type = NFLNK;
	mf_link->mf_fattr.mode = NFSMODE_LNK | 0777;
	mf_link->mf_fattr.nlink = 1;
	mf_link->mf_fattr.size = MAXPATHLEN / 4;
I 2
#endif
E 2
	if (mf_link->mf_ops->fs_init)
		return (*mf_link->mf_ops->fs_init)(mf_link);
	return 0;
}

D 2
/*ARGSUSED*/
static int ifs_mount(mp)
am_node *mp;
E 2
I 2
static mntfs *ifs_inherit P((mntfs *mf));
static mntfs *ifs_inherit(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	/*
	 * Take the linked mount point and
	 * propogate.
	 */
	mntfs *mf_link = (mntfs *) mf->mf_private;
	if (mf_link == 0) {
		plog(XLOG_FATAL, not_a_filesystem);
D 2
		return EINVAL;	/*XXX*/
E 2
I 2
		return 0;	/*XXX*/
E 2
	}

	mf_link->mf_fo = mf->mf_fo;
I 2
#ifdef notdef
E 2
	mf_link->mf_fattr.fileid = mf->mf_fattr.fileid;
I 2
#endif /* notdef */
E 2

	/*
	 * Discard the old map.
	 * Don't call am_unmounted since this
	 * node was never really mounted in the
	 * first place.
	 */
	mf->mf_private = 0;
	free_mntfs(mf);
	/*
	 * Free the dangling reference
	 * to the mount link.
	 */
	free_mntfs(mf_link);
	/*
	 * Get a hold of the other entry
	 */
D 2
	mp->am_mnt = mf = mf_link;
	mf->mf_flags &= ~MFF_RESTART;
E 2
I 2
	mf_link->mf_flags &= ~MFF_RESTART;
E 2

	/* Say what happened */
D 2
	plog(XLOG_INFO, "restarting %s on %s", mf->mf_info, mf->mf_mount);
E 2
I 2
	plog(XLOG_INFO, "restarting %s on %s", mf_link->mf_info, mf_link->mf_mount);
E 2

D 2
	/*
	 * XXX - must do the am_mounted call here
	 */
	if (mf->mf_ops->fs_flags & FS_MBACKGROUND)
		am_mounted(mp);
E 2
I 2
	return mf_link;
}
E 2

D 2
	new_ttl(mp);
E 2
I 2
static int ifs_mount P((am_node *mp));
static int ifs_mount(mp)
am_node *mp;
{
	mntfs *newmf = ifs_inherit(mp->am_mnt);
	if (newmf) {
		mp->am_mnt = newmf;
		/*
		 * XXX - must do the am_mounted call here
		 */
		if (newmf->mf_ops->fs_flags & FS_MBACKGROUND)
			am_mounted(mp);
E 2

D 2
	return 0;
E 2
I 2
		new_ttl(mp);
		return 0;
	}
	return EINVAL;
E 2
}

I 2
static int ifs_fmount P((mntfs *mf));
static int ifs_fmount(mf)
mntfs *mf;
{
	am_node *mp = find_mf(mf);
	if (mp)
		return ifs_mount(mp);
	return ifs_inherit(mf) ? 0 : EINVAL;
}

E 2
/*ARGSUSED*/
D 2
static int ifs_umount(mp)
am_node *mp;
E 2
I 2
static int ifs_fumount P((mntfs *mf));
static int ifs_fumount(mf)
mntfs *mf;
E 2
{
	/*
	 * Always succeed
	 */
	return 0;
}

/*
 * Ops structure
 */
am_ops ifs_ops = {
	"inherit",
	ifs_match,
	ifs_init,
	ifs_mount,
D 2
	ifs_umount,
E 2
I 2
	ifs_fmount,
	auto_fumount,
	ifs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* ifs_readlink */
	0, /* ifs_mounted */
	0, /* ifs_umounted */
	find_afs_srvr,
	FS_DISCARD
};

#endif /* HAS_IFS */
E 1
