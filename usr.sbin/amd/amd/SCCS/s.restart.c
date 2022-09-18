h42249
s 00002/00002/00153
d D 8.1 93/06/06 11:41:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00151
d D 5.5 92/08/01 15:59:29 bostic 5 4
c header corruption
e
s 00003/00003/00150
d D 5.4 92/02/09 08:48:55 pendry 4 3
c merge in new release
e
s 00003/00002/00150
d D 5.3 91/05/12 15:56:00 pendry 3 2
c checkpoint for network tape
e
s 00005/00003/00147
d D 5.2 91/03/17 13:33:55 pendry 2 1
c from amd5.3 alpha11
e
s 00150/00000/00000
d D 5.1 90/06/29 12:01:16 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: restart.c,v 5.2 90/06/23 22:19:55 jsp Rel $
E 2
I 2
D 3
 * $Id: restart.c,v 5.2.1.2 90/11/04 23:17:27 jsp Exp $
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
D 4
 *	%W% (Berkeley) %G%
E 4
I 4
D 5
 *	@(#)restart.c	1.2 (Berkeley) 6/25/91
E 4
I 3
 *
E 5
D 4
 * $Id: restart.c,v 5.2.1.3 91/05/07 22:18:29 jsp Alpha $
E 4
I 4
 * $Id: restart.c,v 5.2.2.1 1992/02/09 15:08:59 jsp beta $
E 4
 *
E 3
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "am.h"

/*
 * Handle an amd restart.
 *
 * Scan through the mount list finding all "interesting" mount points.
 * Next hack up partial data structures and add the mounted file
 * system to the list of known filesystems.  This will leave a
 * dangling reference to that filesystems, so when the filesystem is
 * finally inherited, an extra "free" must be done on it.
 *
 * This module relies on internal details of other components.  If
 * you change something else make *sure* restart() still works.
 */
void restart()
{
	/*
	 * Read the existing mount table
	 */
	mntlist *ml, *mlp;

	/*
	 * For each entry, find nfs, ufs or auto mounts
	 * and create a partial am_node to represent it.
	 */
	for (mlp = ml = read_mtab("restart"); mlp; mlp = mlp->mnext) {
		struct mntent *me = mlp->mnt;
		am_ops *fs_ops = 0;
		if (STREQ(me->mnt_type, MTAB_TYPE_UFS)) {
			/*
			 * UFS entry
			 */
			fs_ops = &ufs_ops;
		} else if (STREQ(me->mnt_type, MTAB_TYPE_NFS)) {
			/*
			 * NFS entry, or possibly an Amd entry...
			 */
			int au_pid;
			char *colon = strchr(me->mnt_fsname, ':');
			if (colon && sscanf(colon, ":(pid%d)", &au_pid) == 1) {
				plog(XLOG_WARNING, "%s is an existing automount point", me->mnt_dir);
				fs_ops = &sfs_ops;
			} else {
				fs_ops = &nfs_ops;
			}
#ifdef MTAB_TYPE_MFS
		} else if (STREQ(me->mnt_type, MTAB_TYPE_MFS)) {
			/*
			 * MFS entry.  Fake with a symlink.
			 */
			fs_ops = &sfs_ops;
#endif /* MTAB_TYPE_MFS */
		} else {
			/*
			 * Catch everything else with symlinks to
			 * avoid recursive mounts.  This is debatable...
			 */
			fs_ops = &sfs_ops;
		}

		/*
		 * If we found something to do
		 */
		if (fs_ops) {
			mntfs *mf;
			am_opts mo;
			char *cp;
			cp = strchr(me->mnt_fsname, ':');
			/*
			 * Partially fake up an opts structure
			 */
			mo.opt_rhost = 0;
			mo.opt_rfs = 0;
			if (cp) {
				*cp = '\0';
				mo.opt_rhost = strdup(me->mnt_fsname);
				mo.opt_rfs = strdup(cp+1);
				*cp = ':';
			} else if (fs_ops->ffserver == find_nfs_srvr) {
				/* 
				 * Prototype 4.4 BSD used to end up here -
				 * might as well keep the workaround for now
				 */
				plog(XLOG_WARNING, "NFS server entry assumed to be %s:/", me->mnt_fsname);
				mo.opt_rhost = strdup(me->mnt_fsname);
				mo.opt_rfs = strdup("/");
				me->mnt_fsname = str3cat(me->mnt_fsname, mo.opt_rhost, ":", "/");
			}
			mo.opt_fs = me->mnt_dir;
I 2
			mo.opt_opts = me->mnt_opts;
E 2

			/*
			 * Make a new mounted filesystem
			 */
			mf = find_mntfs(fs_ops, &mo, me->mnt_dir,
D 2
				me->mnt_fsname, me->mnt_opts);
E 2
I 2
D 4
				me->mnt_fsname, "", me->mnt_opts);
E 4
I 4
				me->mnt_fsname, "", me->mnt_opts, "");
E 4
E 2
			if (mf->mf_refc == 1) {
				mf->mf_flags |= MFF_RESTART|MFF_MOUNTED;
				mf->mf_error = 0;	/* Already mounted correctly */
I 2
				mf->mf_fo = 0;
E 2
				/*
				 * If the restarted type is a link then
				 * don't time out.
				 */
D 2
				if (fs_ops == &sfs_ops)
E 2
I 2
				if (fs_ops == &sfs_ops || fs_ops == &ufs_ops)
E 2
					mf->mf_flags |= MFF_RSTKEEP;
				if (fs_ops->fs_init) {
					/*
					 * Don't care whether this worked since
					 * it is checked again when the fs is
					 * inherited.
					 */
					(void) (*fs_ops->fs_init)(mf);
				}

				plog(XLOG_INFO, "%s restarted fstype %s on %s",
					me->mnt_fsname, fs_ops->fs_type, me->mnt_dir);
			} else {
				/* Something strange happened - two mounts at the same place! */
				free_mntfs(mf);
			}
			/*
			 * Clean up mo
			 */
			if (mo.opt_rhost)
				free(mo.opt_rhost);
			if (mo.opt_rfs)
				free(mo.opt_rfs);
		}
	}

	/*
	 * Free the mount list
	 */
	free_mntlist(ml);
}
E 1
