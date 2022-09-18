h42983
s 00002/00002/00197
d D 8.1 93/06/06 11:41:40 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00198
d D 5.5 93/01/22 16:18:19 mckusick 5 4
c MNT_NOFORCE is gone
e
s 00078/00005/00123
d D 5.4 92/02/09 08:49:10 pendry 4 3
c merge in new release
e
s 00003/00002/00125
d D 5.3 91/05/12 15:56:22 pendry 3 2
c checkpoint for network tape
e
s 00003/00005/00124
d D 5.2 91/03/17 13:34:16 pendry 2 1
c from amd5.3 alpha11
e
s 00129/00000/00000
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
 * $Id: umount_fs.c,v 5.2 90/06/23 22:20:04 jsp Rel $
E 2
I 2
D 3
 * $Id: umount_fs.c,v 5.2.1.2 91/03/03 20:34:23 jsp Alpha $
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
 * $Id: umount_fs.c,v 5.2.1.3 91/05/07 22:18:39 jsp Alpha $
E 4
I 4
 * $Id: umount_fs.c,v 5.2.2.1 1992/02/09 15:09:10 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef NEED_UMOUNT_BSD

D 5
#include <sys/mount.h>		/* For MNT_NOFORCE */

E 5
I 2
int umount_fs P((char *fs_name));
E 2
int umount_fs(fs_name)
char *fs_name;
{
	int error;

eintr:
D 5
	error = unmount(fs_name, MNT_NOFORCE);
E 5
I 5
	error = unmount(fs_name, 0);
E 5
	if (error < 0)
		error = errno;

	switch (error) {
	case EINVAL:
	case ENOTBLK:
I 2
	case ENOENT:
E 2
		plog(XLOG_WARNING, "unmount: %s is not mounted", fs_name);
		error = 0;	/* Not really an error */
D 2
		break;

	case ENOENT:
		plog(XLOG_ERROR, "mount point %s: %m", fs_name);
E 2
		break;

	case EINTR:
#ifdef DEBUG
		/* not sure why this happens, but it does.  ask kirk one day... */
		dlog("%s: unmount: %m", fs_name);
#endif /* DEBUG */
		goto eintr;

#ifdef DEBUG
	default:
		dlog("%s: unmount: %m", fs_name);
		break;
#endif /* DEBUG */
	}

	return error;
}

#endif /* NEED_UMOUNT_BSD */

I 4
#ifdef NEED_UMOUNT_OSF

#include <sys/mount.h>		/* For MNT_NOFORCE */

int umount_fs(fs_name)
char *fs_name;
{
	int error;

eintr:
	error = umount(fs_name, MNT_NOFORCE);
	if (error < 0)
		error = errno;

	switch (error) {
	case EINVAL:
	case ENOTBLK:
		plog(XLOG_WARNING, "unmount: %s is not mounted", fs_name);
		error = 0;	/* Not really an error */
		break;

	case ENOENT:
		plog(XLOG_ERROR, "mount point %s: %m", fs_name);
		break;

	case EINTR:
#ifdef DEBUG
		/* not sure why this happens, but it does.  ask kirk one day... */
		dlog("%s: unmount: %m", fs_name);
#endif /* DEBUG */
		goto eintr;

#ifdef DEBUG
	default:
		dlog("%s: unmount: %m", fs_name);
		break;
#endif /* DEBUG */
	}

	return error;
}

#endif /* NEED_UMOUNT_OSF */

E 4
#ifdef NEED_UMOUNT_FS

int umount_fs(fs_name)
char *fs_name;
{
	mntlist *mlist, *mp, *mp_save = 0;
	int error = 0;

	mp = mlist = read_mtab(fs_name);

	/*
	 * Search the mount table looking for
	 * the correct (ie last) matching entry
	 */
	while (mp) {
		if (strcmp(mp->mnt->mnt_fsname, fs_name) == 0 ||
				strcmp(mp->mnt->mnt_dir, fs_name) == 0)
			mp_save = mp;
		mp = mp->mnext;
	}

	if (mp_save) {
#ifdef DEBUG
		dlog("Trying unmount(%s)", mp_save->mnt->mnt_dir);
#endif /* DEBUG */
I 4
		/*
		 * This unmount may hang leaving this
		 * process with an exlusive lock on
		 * /etc/mtab. Therefore it is necessary
		 * to unlock mtab, do the unmount, then
		 * lock mtab (again) and reread it and
		 * finally update it.
		 */
		unlock_mntlist();
E 4
		if (UNMOUNT_TRAP(mp_save->mnt) < 0) {
			switch (error = errno) {
			case EINVAL:
			case ENOTBLK:
				plog(XLOG_WARNING, "unmount: %s is not mounted", mp_save->mnt->mnt_dir);
				error = 0;	/* Not really an error */
				break;

			case ENOENT:
				plog(XLOG_ERROR, "mount point %s: %m", mp_save->mnt->mnt_dir);
				break;

			default:
#ifdef DEBUG
				dlog("%s: unmount: %m", mp_save->mnt->mnt_dir);
#endif /* DEBUG */
				break;
			}
		}
I 4
#ifdef DEBUG
		dlog("Finished unmount(%s)", mp_save->mnt->mnt_dir);
#endif
E 4

I 4

E 4
#ifdef UPDATE_MTAB
		if (!error) {
D 4
			mnt_free(mp_save->mnt);
			mp_save->mnt = 0;

			rewrite_mtab(mlist);
E 4
I 4
		        free_mntlist(mlist);
			mp = mlist = read_mtab(fs_name);
			
			/*
			 * Search the mount table looking for
			 * the correct (ie last) matching entry
			 */
			mp_save = 0;
			while (mp) {
				if (strcmp(mp->mnt->mnt_fsname, fs_name) == 0 ||
						strcmp(mp->mnt->mnt_dir, fs_name) == 0)
					mp_save = mp;
				mp = mp->mnext;
			}
			
			if (mp_save) {
				mnt_free(mp_save->mnt);
				mp_save->mnt = 0;
				rewrite_mtab(mlist);
			}
E 4
		}
#endif /* UPDATE_MTAB */
	} else {
		plog(XLOG_ERROR, "Couldn't find how to unmount %s", fs_name);
		/*
		 * Assume it is already unmounted
		 */
		error = 0;
	}

	free_mntlist(mlist);

	return error;
}

#endif /* NEED_UMOUNT_FS */
E 1
