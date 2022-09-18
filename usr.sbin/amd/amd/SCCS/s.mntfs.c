h49479
s 00002/00002/00339
d D 8.1 93/06/06 11:40:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00335
d D 5.5 92/08/01 15:56:09 bostic 5 4
c header corruption
e
s 00022/00015/00317
d D 5.4 92/02/09 08:48:33 pendry 4 3
c merge in new release
e
s 00015/00002/00317
d D 5.3 91/05/12 15:55:42 pendry 3 2
c checkpoint for network tape
e
s 00042/00018/00277
d D 5.2 91/03/17 13:33:29 pendry 2 1
c from amd5.3 alpha11
e
s 00295/00000/00000
d D 5.1 90/06/29 12:01:10 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
/*-
E 5
D 2
 * $Id: mntfs.c,v 5.2 90/06/23 22:19:40 jsp Rel $
E 2
I 2
D 3
 * $Id: mntfs.c,v 5.2.1.4 91/03/17 17:46:40 jsp Alpha $
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
 *	@(#)mntfs.c	1.2 (Berkeley) 6/25/91
E 4
I 3
 *
E 5
D 4
 * $Id: mntfs.c,v 5.2.1.7 91/05/07 22:18:11 jsp Alpha $
E 4
I 4
 * $Id: mntfs.c,v 5.2.2.1 1992/02/09 15:08:42 jsp beta $
E 4
D 5
 *
E 5
E 3
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5

#include "am.h"

extern qelem mfhead;
qelem mfhead = { &mfhead, &mfhead };

int mntfs_allocated;

I 2
#ifdef notdef
E 2
/*
 * This is the default attributes field which
 * is copied into every new node to be created.
 * The individual filesystem fs_init() routines
 * patch the copy to represent the particular
 * details for the relevant filesystem type
 */
static struct fattr gen_fattr = {
	NFDIR,				/* type */
	NFSMODE_DIR | 0555,		/* mode */
	2,				/* nlink */
	0,				/* uid */
	0,				/* gid */
	512,				/* size */
	4096,				/* blocksize */
	0,				/* rdev */
	1,				/* blocks */
	0,				/* fsid */
	0,				/* fileid */
	{ 0, 0 },			/* atime */
	{ 0, 0 },			/* mtime */
	{ 0, 0 },			/* ctime */
};
I 2
#endif /* notdef */
E 2

mntfs *dup_mntfs(mf)
mntfs *mf;
{
	if (mf->mf_refc == 0) {
D 2
		untimeout(mf->mf_cid);
E 2
I 2
		if (mf->mf_cid)
			untimeout(mf->mf_cid);
E 2
		mf->mf_cid = 0;
I 2
#ifdef notdef
E 2
		mf->mf_error = -1;
		mf->mf_flags &= ~MFF_ERROR;
I 2
#endif
E 2
	}
	mf->mf_refc++;
	return mf;
}

D 2
static init_mntfs(mf, ops, mo, mp, info, opts)
E 2
I 2
D 4
static int init_mntfs P((mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts));
static int init_mntfs(mf, ops, mo, mp, info, auto_opts, mopts)
E 4
I 4
static void init_mntfs P((mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts));
static void init_mntfs(mf, ops, mo, mp, info, auto_opts, mopts, remopts)
E 4
E 2
mntfs *mf;
am_ops *ops;
am_opts *mo;
char *mp;
char *info;
D 2
char *opts;
E 2
I 2
char *auto_opts;
char *mopts;
I 4
char *remopts;
E 4
E 2
{
	mf->mf_ops = ops;
	mf->mf_fo = mo;
	mf->mf_mount = strdup(mp);
	mf->mf_info = strdup(info);
D 2
	mf->mf_opts = strdup(opts);
E 2
I 2
	mf->mf_auto = strdup(auto_opts);
	mf->mf_mopts = strdup(mopts);
I 4
	mf->mf_remopts = strdup(remopts);
E 4
E 2
	mf->mf_refc = 1;
	mf->mf_flags = 0;
	mf->mf_error = -1;
	mf->mf_cid = 0;
	mf->mf_private = 0;
	mf->mf_prfree = 0;
I 2
#ifdef notdef
E 2
	mf->mf_attr.status = NFS_OK;
	mf->mf_fattr = gen_fattr;
	mf->mf_fattr.fsid = 42;
	mf->mf_fattr.fileid = 0;
	mf->mf_fattr.atime.seconds = clocktime();
	mf->mf_fattr.atime.useconds = 0;
	mf->mf_fattr.mtime = mf->mf_fattr.ctime = mf->mf_fattr.atime;
I 2
#endif
E 2

	if (ops->ffserver)
		mf->mf_server = (*ops->ffserver)(mf);
	else
		mf->mf_server = 0;
}

D 2
static mntfs *alloc_mntfs(ops, mo, mp, info, opts)
E 2
I 2
D 4
static mntfs *alloc_mntfs P((am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts));
static mntfs *alloc_mntfs(ops, mo, mp, info, auto_opts, mopts)
E 4
I 4
static mntfs *alloc_mntfs P((am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts));
static mntfs *alloc_mntfs(ops, mo, mp, info, auto_opts, mopts, remopts)
E 4
E 2
am_ops *ops;
am_opts *mo;
char *mp;
char *info;
D 2
char *opts;
E 2
I 2
char *auto_opts;
char *mopts;
I 4
char *remopts;
E 4
E 2
{
	mntfs *mf = ALLOC(mntfs);
D 2
	init_mntfs(mf, ops, mo, mp, info, opts);
E 2
I 2
D 4
	init_mntfs(mf, ops, mo, mp, info, auto_opts, mopts);
E 4
I 4
	init_mntfs(mf, ops, mo, mp, info, auto_opts, mopts, remopts);
E 4
E 2
	ins_que(&mf->mf_q, &mfhead);
	mntfs_allocated++;

	return mf;
}

D 2
mntfs *find_mntfs(ops, mo, mp, info, opts)
E 2
I 2
D 4
mntfs *find_mntfs P((am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts));
mntfs *find_mntfs(ops, mo, mp, info, auto_opts, mopts)
E 4
I 4
mntfs *find_mntfs P((am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts));
mntfs *find_mntfs(ops, mo, mp, info, auto_opts, mopts, remopts)
E 4
E 2
am_ops *ops;
am_opts *mo;
char *mp;
char *info;
D 2
char *opts;
E 2
I 2
char *auto_opts;
char *mopts;
I 4
char *remopts;
E 4
E 2
{
	mntfs *mf;

#ifdef DEBUG
	dlog("Locating mntfs reference to %s", mp);
#endif /* DEBUG */
	ITER(mf, mntfs, &mfhead) {
		if (STREQ(mf->mf_mount, mp)) {
			/*
			 * Handle cases where error ops are involved
			 */
			if (ops == &efs_ops) {
				/*
				 * If the existing ops are not efs_ops
				 * then continue...
				 */
				if (mf->mf_ops != &efs_ops)
					continue;
			} else /* ops != &efs_ops */ {
				/*
				 * If the existing ops are efs_ops
				 * then continue...
				 */
				if (mf->mf_ops == &efs_ops)
					continue;
			}

			if ((mf->mf_flags & MFF_RESTART) && amd_state == Run) {
				/*
				 * Restart a previously mounted filesystem.
				 */
D 2
				mntfs *mf2 = alloc_mntfs(&ifs_ops, mo, mp, info, opts);
E 2
I 2
D 4
				mntfs *mf2 = alloc_mntfs(&ifs_ops, mo, mp, info, auto_opts, mopts);
E 4
I 4
				mntfs *mf2 = alloc_mntfs(&ifs_ops, mo, mp, info, auto_opts, mopts, remopts);
E 4
E 2
#ifdef DEBUG
				dlog("Restarting filesystem %s", mf->mf_mount);
#endif /* DEBUG */
				/*
				 * Remember who we are restarting
				 */
				mf2->mf_private = (voidp) dup_mntfs(mf);
				mf2->mf_prfree = free_mntfs;
				return mf2;
			}
			mf->mf_fo = mo;
			if (!(mf->mf_flags & (MFF_MOUNTED|MFF_MOUNTING|MFF_UNMOUNTING))) {
				fserver *fs;
D 2
				mf->mf_opts = strealloc(mf->mf_opts, opts);
E 2
I 2
				mf->mf_flags &= ~MFF_ERROR;
				mf->mf_error = -1;
				mf->mf_auto = strealloc(mf->mf_auto, auto_opts);
				mf->mf_mopts = strealloc(mf->mf_mopts, mopts);
I 4
				mf->mf_remopts = strealloc(mf->mf_remopts, remopts);
E 4
E 2
				mf->mf_info = strealloc(mf->mf_info, info);
I 2
				if (mf->mf_private && mf->mf_prfree) {
					(*mf->mf_prfree)(mf->mf_private);
					mf->mf_private = 0;
				}
E 2
				fs = ops->ffserver ? (*ops->ffserver)(mf) : (fserver *) 0;
				if (mf->mf_server)
					free_srvr(mf->mf_server);
				mf->mf_server = fs;
			}
			return dup_mntfs(mf);
		}
	}

D 2
	return alloc_mntfs(ops, mo, mp, info, opts);
E 2
I 2
D 4
	return alloc_mntfs(ops, mo, mp, info, auto_opts, mopts);
E 4
I 4
	return alloc_mntfs(ops, mo, mp, info, auto_opts, mopts, remopts);
E 4
E 2
}

mntfs *new_mntfs()
{
D 2
	return alloc_mntfs(&efs_ops, (am_opts *) 0, "//nil//", ".", "");
E 2
I 2
D 4
	return alloc_mntfs(&efs_ops, (am_opts *) 0, "//nil//", ".", "", "");
E 4
I 4
	return alloc_mntfs(&efs_ops, (am_opts *) 0, "//nil//", ".", "", "", "");
E 4
E 2
}

static void uninit_mntfs(mf, rmd)
mntfs *mf;
int rmd;
{
	if (mf->mf_mount) free((voidp) mf->mf_mount);
D 2
	if (mf->mf_opts) free((voidp) mf->mf_opts);
E 2
I 2
	if (mf->mf_auto) free((voidp) mf->mf_auto);
	if (mf->mf_mopts) free((voidp) mf->mf_mopts);
I 4
	if (mf->mf_remopts) free((voidp) mf->mf_remopts);
E 4
E 2
	if (mf->mf_info) free((voidp) mf->mf_info);
	if (mf->mf_private && mf->mf_prfree)
		(*mf->mf_prfree)(mf->mf_private);
	/*
	 * Clean up any directories that were made
	 */
	if (rmd && (mf->mf_flags & MFF_MKMNT))
		rmdirs(mf->mf_mount);

	/*
	 * Clean up the file server
	 */
	if (mf->mf_server)
		free_srvr(mf->mf_server);

	/*
	 * Don't do a callback on this mount
	 */
	if (mf->mf_cid) {
		untimeout(mf->mf_cid);
		mf->mf_cid = 0;
	}
}

static void discard_mntfs(mf)
mntfs *mf;
{
	rem_que(&mf->mf_q);
	/*
	 * Free memory
	 */
	uninit_mntfs(mf, TRUE);
	free((voidp) mf);

	--mntfs_allocated;
}

void flush_mntfs()
{
	mntfs *mf;

	mf = FIRST(mntfs, &mfhead);
	while (mf != HEAD(mntfs, &mfhead)) {
		mntfs *mf2 = mf;
		mf = NEXT(mntfs, mf);
		if (mf2->mf_refc == 0 && mf2->mf_cid)
			discard_mntfs(mf2);
	}
}

void free_mntfs(mf)
mntfs *mf;
{
	if (--mf->mf_refc == 0) {
		if (mf->mf_flags & MFF_MOUNTED) {
			int quoted;
			mf->mf_flags &= ~MFF_MOUNTED;

			/*
			 * Record for posterity
			 */
			quoted = strchr(mf->mf_info, ' ') != 0;	/* cheap */
			plog(XLOG_INFO, "%s%s%s %sed fstype %s from %s",
				quoted ? "\"" : "",
				mf->mf_info,
				quoted ? "\"" : "",
				mf->mf_error ? "discard" : "unmount",
				mf->mf_ops->fs_type, mf->mf_mount);
		}

		if (mf->mf_ops->fs_flags & FS_DISCARD) {
#ifdef DEBUG
			dlog("Immediately discarding mntfs for %s", mf->mf_mount);
#endif /* DEBUG */
			discard_mntfs(mf);
		} else {
#ifdef DEBUG
			if (mf->mf_flags & MFF_RESTART) {
				dlog("Discarding remount hook for %s", mf->mf_mount);
			} else {
				dlog("Discarding last mntfs reference to %s fstype %s",
					mf->mf_mount, mf->mf_ops->fs_type);
			}
			if (mf->mf_flags & (MFF_MOUNTED|MFF_MOUNTING|MFF_UNMOUNTING))
				dlog("mntfs reference for %s still active", mf->mf_mount);
#endif /* DEBUG */
			mf->mf_cid = timeout(ALLOWED_MOUNT_TIME, discard_mntfs, (voidp) mf);
		}
	}
}

D 2
mntfs *realloc_mntfs(mf, ops, mo, mp, info, opts)
E 2
I 2
D 4
mntfs *realloc_mntfs P((mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts));
mntfs *realloc_mntfs(mf, ops, mo, mp, info, auto_opts, mopts)
E 4
I 4
mntfs *realloc_mntfs P((mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts));
mntfs *realloc_mntfs(mf, ops, mo, mp, info, auto_opts, mopts, remopts)
E 4
E 2
mntfs *mf;
am_ops *ops;
am_opts *mo;
char *mp;
char *info;
D 2
char *opts;
E 2
I 2
char *auto_opts;
char *mopts;
I 4
char *remopts;
E 4
E 2
{
	mntfs *mf2;
	if (mf->mf_refc == 1 && mf->mf_ops == &ifs_ops && STREQ(mf->mf_mount, mp)) {
		/*
		 * If we are inheriting then just return
		 * the same node...
		 */
		return mf;
	}
I 3

	/*
	 * Re-use the existing mntfs if it is mounted.
	 * This traps a race in nfsx.
	 */
	if (mf->mf_ops != &efs_ops &&
			(mf->mf_flags & MFF_MOUNTED) &&
			!FSRV_ISDOWN(mf->mf_server)) {
		mf->mf_fo = mo;
		return mf;
	}

E 3
D 2
	mf2 = find_mntfs(ops, mo, mp, info, opts);
E 2
I 2
D 4
	mf2 = find_mntfs(ops, mo, mp, info, auto_opts, mopts);
E 4
I 4
	mf2 = find_mntfs(ops, mo, mp, info, auto_opts, mopts, remopts);
E 4
E 2
	free_mntfs(mf);
	return mf2;
}
E 1
