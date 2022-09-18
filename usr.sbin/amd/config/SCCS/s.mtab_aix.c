h27846
s 00002/00002/00109
d D 8.1 93/06/06 11:50:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00110
d D 5.4 92/02/09 08:30:53 pendry 4 3
c merge in new release
e
s 00003/00002/00108
d D 5.3 91/05/12 15:59:17 pendry 3 2
c checkpoint for network tape
e
s 00007/00002/00103
d D 5.2 91/03/17 13:49:07 pendry 2 1
c from amd5.3 alpha11
e
s 00105/00000/00000
d D 5.1 90/06/29 12:40:57 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mtab_aix.c,v 5.2 90/06/23 22:20:36 jsp Rel $
E 2
I 2
D 3
 * $Id: mtab_aix.c,v 5.2.1.1 90/10/21 22:30:40 jsp Exp $
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
 * $Id: mtab_aix.c,v 5.2.1.2 91/05/07 22:19:29 jsp Alpha $
E 4
I 4
 * $Id: mtab_aix.c,v 5.2.2.1 1992/02/09 15:10:07 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef READ_MTAB_AIX3_STYLE

#include <sys/mntctl.h>
#include <sys/vmount.h>

static struct mntent *mnt_dup(mp)
struct vmount *mp;
{
	struct mntent *new_mp = ALLOC(mntent);

	char *ty;
	new_mp->mnt_fsname = strdup(vmt2dataptr(mp, VMT_OBJECT));
	new_mp->mnt_dir = strdup(vmt2dataptr(mp, VMT_STUB));
	new_mp->mnt_opts = strdup(vmt2dataptr(mp, VMT_ARGS));
	switch (mp->vmt_gfstype) {
	case MNT_JFS:  ty = MTAB_TYPE_UFS; break;
D 2
	case MNT_NFS:  ty = MTAB_TYPE_NFS; break;
E 2
I 2
	case MNT_NFS:
		ty = MTAB_TYPE_NFS;
		new_mp->mnt_fsname = str3cat(new_mp->mnt_fsname,
				vmt2dataptr(mp, VMT_HOSTNAME),
				":", new_mp->mnt_fsname);
		break;
E 2
	default:  ty = "unknown"; break;
	}
	new_mp->mnt_type = strdup(ty);
	new_mp->mnt_passno = mp->vmt_vfsnumber;
	new_mp->mnt_freq = 0;

	return new_mp;
}

/*
 * Read a mount table into memory
 */
mntlist *read_mtab(fs)
char *fs;
{
	mntlist **mpp, *mhp;

	int i;
	char *mntinfo = 0, *cp;
	struct vmount *vp;
	int ret;

	/*
	 * First figure out size of mount table
	 * and allocate space for a copy...
	 * Then get mount table for real.
	 */
	ret = mntctl(MCTL_QUERY, sizeof(i), &i);
	if (ret == 0) {
		mntinfo = xmalloc(i);
		ret = mntctl(MCTL_QUERY, i, mntinfo);
	}

	if (ret <= 0) {
		plog(XLOG_ERROR, "mntctl: %m");
		goto out;
	}
#ifdef DEBUG
	/*dlog("mntctl returns %d structures", ret);*/
#endif /* DEBUG */

	mpp = &mhp;
	for (i = 0, cp = mntinfo; i < ret; i++, cp += vp->vmt_length) {
		vp = (struct vmount *) cp;

		/*
		 * Allocate a new slot
		 */
		*mpp = ALLOC(mntlist);

		/*
		 * Copy the data returned by mntctl
		 */
		(*mpp)->mnt = mnt_dup(vp);

		/*
		 * Move to next pointer
		 */
		mpp = &(*mpp)->mnext;
	}

	*mpp = 0;

out:
	if (mntinfo)
		free(mntinfo);
	return mhp;
}

#endif /* READ_MTAB_AIX3_STYLE */
E 1
