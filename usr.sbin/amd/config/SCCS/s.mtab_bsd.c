h04531
s 00004/00000/00088
d D 8.2 95/05/10 05:38:06 pendry 7 6
c get fstype from mount entry
e
s 00002/00002/00086
d D 8.1 93/06/06 11:50:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00083
d D 5.5 92/11/12 15:27:46 pendry 5 4
c make sure the mount list is null terminated
e
s 00001/00001/00082
d D 5.4 92/02/09 08:30:55 pendry 4 3
c merge in new release
e
s 00003/00002/00080
d D 5.3 91/05/12 15:58:48 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00081
d D 5.2 91/03/17 13:49:09 pendry 2 1
c from amd5.3 alpha11
e
s 00082/00000/00000
d D 5.1 90/06/29 12:40:58 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mtab_bsd.c,v 5.2 90/06/23 22:20:40 jsp Rel $
E 2
I 2
D 3
 * $Id: mtab_bsd.c,v 5.2.1.1 90/10/21 22:30:46 jsp Exp $
E 2
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
 * $Id: mtab_bsd.c,v 5.2.1.2 91/05/07 22:19:35 jsp Alpha $
E 4
I 4
 * $Id: mtab_bsd.c,v 5.2.2.1 1992/02/09 15:10:13 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef READ_MTAB_BSD_STYLE

#include <sys/mount.h>

static struct mntent *mnt_dup(mp)
struct statfs *mp;
{
	struct mntent *new_mp = ALLOC(mntent);
	char *ty;

	new_mp->mnt_fsname = strdup(mp->f_mntfromname);
	new_mp->mnt_dir = strdup(mp->f_mntonname);
I 7
#if BSD >= 199506
	ty = mp->f_fstypename;
#else
E 7
	switch (mp->f_type) {
	case MOUNT_UFS:  ty = MTAB_TYPE_UFS; break;
	case MOUNT_NFS:  ty = MTAB_TYPE_NFS; break;
	case MOUNT_MFS:  ty = MTAB_TYPE_MFS; break;
	default:  ty = "unknown"; break;
	}
I 7
#endif
E 7
	new_mp->mnt_type = strdup(ty);
	new_mp->mnt_opts = strdup("unset");
	new_mp->mnt_freq = 0;
	new_mp->mnt_passno = 0;

	return new_mp;
}

/*
 * Read a mount table into memory
 */
mntlist *read_mtab(fs)
char *fs;
{
	mntlist **mpp, *mhp;
	struct statfs *mntbufp, *mntp;

	int nloc = getmntinfo(&mntbufp, MNT_NOWAIT);

	if (nloc == 0) {
		plog(XLOG_ERROR, "Can't read mount table");
		return 0;
	}

	mpp = &mhp;
	for (mntp = mntbufp; mntp < mntbufp + nloc; mntp++) {
		/*
		 * Allocate a new slot
		 */
		*mpp = ALLOC(mntlist);

		/*
		 * Copy the data returned by getmntent
		 */
		(*mpp)->mnt = mnt_dup(mntp);

		/*
		 * Move to next pointer
		 */
		mpp = &(*mpp)->mnext;
	}

I 5
	/*
	 * Terminate the list
	 */
	*mpp = 0;

E 5
	return mhp;
}

#endif /* READ_MTAB_BSD_STYLE */
E 1
