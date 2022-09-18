h63869
s 00002/00002/00087
d D 8.1 93/06/06 11:51:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00088
d D 5.4 92/02/09 08:30:58 pendry 4 3
c merge in new release
e
s 00003/00002/00086
d D 5.3 91/05/12 15:58:50 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00087
d D 5.2 91/03/17 13:49:14 pendry 2 1
c from amd5.3 alpha11
e
s 00088/00000/00000
d D 5.1 90/06/29 12:41:00 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mtab_ultrix.c,v 5.2 90/06/23 22:20:57 jsp Rel $
E 2
I 2
D 3
 * $Id: mtab_ultrix.c,v 5.2.1.1 90/10/21 22:31:08 jsp Exp $
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
 * $Id: mtab_ultrix.c,v 5.2.1.2 91/05/07 22:20:02 jsp Alpha $
E 4
I 4
 * $Id: mtab_ultrix.c,v 5.2.2.1 1992/02/09 15:10:50 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef READ_MTAB_ULTRIX_STYLE

#include <sys/mount.h>
#include <sys/fs_types.h>

static struct mntent *mnt_dup(mp)
struct fs_data *mp;
{
	struct mntent *new_mp = ALLOC(mntent);

	new_mp->mnt_fsname = strdup(mp->fd_devname);
	new_mp->mnt_dir = strdup(mp->fd_path);
        if (mp->fd_fstype >= GT_NUMTYPES)
                mp->fd_fstype = GT_UNKWN;
        else if (gt_names[mp->fd_fstype] == 0)
                mp->fd_fstype = GT_UNKWN;
        new_mp->mnt_type = strdup(gt_names[mp->fd_fstype]);
	new_mp->mnt_opts = strdup("unset");

	new_mp->mnt_freq = 0;
	new_mp->mnt_passno = mp->fd_dev;

	return new_mp;
}

/*
 * Read a mount table into memory
 */
mntlist *read_mtab(fs)
char *fs;
{
	mntlist **mpp, *mhp;

/* From: Piete Brooks <pb@cl.cam.ac.uk> */

	int loc=0;
#undef	NMOUNT
#define	NMOUNT	20
	struct fs_data mountbuffer[NMOUNT], *fs_data;
	int ret;

	mpp = &mhp;
	while ((ret = getmountent(&loc, mountbuffer, NMOUNT)) > 0) {
	        for (fs_data = mountbuffer; fs_data < &mountbuffer[ret]; fs_data++) {
			/*
			 * Allocate a new slot
			 */
			*mpp = ALLOC(mntlist);

			/*
			 * Copy the data returned by getmntent
			 */
			(*mpp)->mnt = mnt_dup(fs_data);

			/*
			 * Move to next pointer
			 */
			mpp = &(*mpp)->mnext;
		}
	}
	if (ret < 0) {
		plog(XLOG_ERROR, "getmountent: %m");
		return 0;
	}
	*mpp = 0;

	return mhp;
}

#endif /* READ_MTAB_ULTRIX_STYLE */
E 1
