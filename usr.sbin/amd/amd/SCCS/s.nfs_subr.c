h05618
s 00002/00002/00524
d D 8.1 93/06/06 11:40:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00525
d D 5.4 92/02/09 08:48:46 pendry 4 3
c merge in new release
e
s 00003/00002/00523
d D 5.3 91/05/12 15:55:03 pendry 3 2
c checkpoint for network tape
e
s 00020/00020/00505
d D 5.2 91/03/17 13:33:50 pendry 2 1
c from amd5.3 alpha11
e
s 00525/00000/00000
d D 5.1 90/06/29 12:01:14 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: nfs_subr.c,v 5.2 90/06/23 22:19:50 jsp Rel $
E 2
I 2
D 3
 * $Id: nfs_subr.c,v 5.2.1.4 91/03/03 20:46:34 jsp Alpha $
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
 * $Id: nfs_subr.c,v 5.2.1.5 91/05/07 22:18:23 jsp Alpha $
E 4
I 4
 * $Id: nfs_subr.c,v 5.2.2.1 1992/02/09 15:08:53 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

/*
 * Convert from UN*X to NFS error code
 */
#ifdef NFS_ERROR_MAPPING
NFS_ERROR_MAPPING
#define nfs_error(e) \
        ((nfsstat)((e) > NFS_LOMAP && (e) < NFS_HIMAP ? \
        nfs_errormap[(e) - NFS_LOMAP] : (e)))
#else
#define nfs_error(e) ((nfsstat)(e))
#endif /* NFS_ERROR_MAPPING */

I 2
static char *do_readlink P((am_node *mp, int *error_return, struct attrstat **attrpp));
E 2
static char *do_readlink(mp, error_return, attrpp)
am_node *mp;
int *error_return;
struct attrstat **attrpp;
{
	char *ln;

	/*
	 * If there is a readlink method, then use
	 * that, otherwise if a link exists use
	 * that, otherwise use the mount point.
	 */
	if (mp->am_mnt->mf_ops->readlink) {
		int retry = 0;
		mp = (*mp->am_mnt->mf_ops->readlink)(mp, &retry);
		if (mp == 0) {
			*error_return = retry;
			return 0;
		}
		/*reschedule_timeout_mp();*/
	}
	if (mp->am_link) {
		ln = mp->am_link;
	} else {
		ln = mp->am_mnt->mf_mount;
	}
	if (attrpp)
D 2
		*attrpp = &mp->am_mnt->mf_attr;
E 2
I 2
		*attrpp = &mp->am_attr;
E 2
	return ln;
}

/*ARGSUSED*/
voidp 
nfsproc_null_2(argp, rqstp)
voidp argp;
struct svc_req *rqstp;
{
	static char res;

	return (voidp) &res;
}


/*ARGSUSED*/
struct attrstat *
nfsproc_getattr_2(argp, rqstp)
struct nfs_fh *argp;
struct svc_req *rqstp;
{
	static struct attrstat res;
	am_node *mp;
	int retry;

#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "gettattr:");
#endif /* DEBUG */

	mp = fh_to_mp2(argp, &retry);
	if (mp == 0) {
#ifdef PRECISE_SYMLINKS
getattr_retry:
#endif /* PRECISE_SYMLINKS */

		if (retry < 0)
			return 0;
		res.status = nfs_error(retry);
	} else {
D 2
		struct attrstat *attrp = &mp->am_mnt->mf_attr;
E 2
I 2
		struct attrstat *attrp = &mp->am_attr;
E 2
#ifdef PRECISE_SYMLINKS
D 2
		if (mp->am_mnt->mf_fattr.type == NFLNK) {
E 2
I 2
		if (mp->am_fattr.type == NFLNK) {
E 2
			/*
			 * Make sure we can read the link,
			 * and then determine the length.
			 */
			char *ln = do_readlink(mp, &retry, &attrp);
			if (ln == 0)
				goto getattr_retry;
		}
#endif /* PRECISE_SYMLINKS */
#ifdef DEBUG
		Debug(D_TRACE)
			plog(XLOG_DEBUG, "\tstat(%s), size = %d", mp->am_path, attrp->attrstat_u.attributes.size);
#endif /* DEBUG */
		mp->am_stats.s_getattr++;
		return attrp;
	}

	return &res;
}


/*ARGSUSED*/
struct attrstat *
nfsproc_setattr_2(argp, rqstp)
struct sattrargs *argp;
struct svc_req *rqstp;
{
	static struct attrstat res;

	if (!fh_to_mp(&argp->file))
		res.status = nfs_error(ESTALE);
	else
		res.status = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
voidp 
nfsproc_root_2(argp, rqstp)
voidp argp;
struct svc_req *rqstp;
{
	static char res;

	return (voidp)&res;
}


/*ARGSUSED*/
struct diropres *
nfsproc_lookup_2(argp, rqstp)
struct diropargs *argp;
struct svc_req *rqstp;
{
	static struct diropres res;
	am_node *mp;
	int retry;

#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "lookup:");
#endif /* DEBUG */

	mp = fh_to_mp2(&argp->dir, &retry);
	if (mp == 0) {
		if (retry < 0)
			return 0;
		res.status = nfs_error(retry);
	} else {
		int error;
		am_node *ap;
#ifdef DEBUG
		Debug(D_TRACE)
			plog(XLOG_DEBUG, "\tlookuppn(%s, %s)", mp->am_path, argp->name);
#endif /* DEBUG */
		ap = (*mp->am_mnt->mf_ops->lookuppn)(mp, argp->name, &error, VLOOK_CREATE);
		if (ap == 0) {
			if (error < 0) {
#ifdef DEBUG
				dlog("Not sending RPC reply");
#endif /* DEBUG */
				amd_stats.d_drops++;
				return 0;
			}
			res.status = nfs_error(error);
		} else {
D 2
#ifdef DEBUG
			if (ap->am_mnt->mf_fattr.size < 0)
				dlog("\tERROR: size = %d!", ap->am_mnt->mf_fattr.size);
#endif /* DEBUG */
E 2
			mp_to_fh(ap, &res.diropres_u.diropres.file);
D 2
			res.diropres_u.diropres.attributes = ap->am_mnt->mf_fattr;
E 2
I 2
			res.diropres_u.diropres.attributes = ap->am_fattr;
E 2
			res.status = NFS_OK;
		}
		mp->am_stats.s_lookup++;
		/*reschedule_timeout_mp();*/
	}

	return &res;
}


/*ARGSUSED*/
struct readlinkres *
nfsproc_readlink_2(argp, rqstp)
struct nfs_fh *argp;
struct svc_req *rqstp;
{
	static struct readlinkres res;
	am_node *mp;
	int retry;

#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "readlink:");
#endif /* DEBUG */

	mp = fh_to_mp2(argp, &retry);
	if (mp == 0) {
readlink_retry:
		if (retry < 0)
			return 0;
		res.status = nfs_error(retry);
	} else {
D 2
		char *ln = do_readlink(mp, &retry, (struct attrstat *) 0);
E 2
I 2
		char *ln = do_readlink(mp, &retry, (struct attrstat **) 0);
E 2
		if (ln == 0)
			goto readlink_retry;
		res.status = NFS_OK;
#ifdef DEBUG
		Debug(D_TRACE)
			if (ln)
				plog(XLOG_DEBUG, "\treadlink(%s) = %s", mp->am_path, ln);
#endif /* DEBUG */
		res.readlinkres_u.data = ln;
		mp->am_stats.s_readlink++;
	}

	return &res;
}


/*ARGSUSED*/
struct readres *
nfsproc_read_2(argp, rqstp)
struct readargs *argp;
struct svc_req *rqstp;
{
	static struct readres res;

	bzero((char *)&res, sizeof(res));

	res.status = nfs_error(EACCES);

	return &res;
}


/*ARGSUSED*/
voidp 
nfsproc_writecache_2(argp, rqstp)
voidp argp;
struct svc_req *rqstp;
{
	static char res;

	return (voidp) &res;
}


/*ARGSUSED*/
struct attrstat *
nfsproc_write_2(argp, rqstp)
writeargs *argp;
struct svc_req *rqstp;
{
	static struct attrstat res;

	if (!fh_to_mp(&argp->file))
		res.status = nfs_error(ESTALE);
	else
		res.status = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
struct diropres *
nfsproc_create_2(argp, rqstp)
createargs *argp;
struct svc_req *rqstp;
{
	static struct diropres res;

	if (!fh_to_mp(&argp->where.dir))
		res.status = nfs_error(ESTALE);
	else
		res.status = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
static nfsstat *
unlink_or_rmdir(argp, rqstp, unlinkp)
struct diropargs *argp;
struct svc_req *rqstp;
I 2
int unlinkp;
E 2
{
	static nfsstat res;
	int retry;
D 2
	mntfs *mf;
E 2
I 2
	/*mntfs *mf;*/
E 2
	am_node *mp = fh_to_mp3(&argp->dir, &retry, VLOOK_DELETE);
	if (mp == 0) {
		if (retry < 0)
			return 0;
		res = nfs_error(retry);
		goto out;
	}
D 2
	mf = mp->am_mnt;
	if (mf->mf_fattr.type != NFDIR) {
E 2
I 2
	/*mf = mp->am_mnt;*/
	if (mp->am_fattr.type != NFDIR) {
E 2
		res = nfs_error(ENOTDIR);
		goto out;
	}
#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "\tremove(%s, %s)", mp->am_path, argp->name);
#endif /* DEBUG */
	mp = (*mp->am_mnt->mf_ops->lookuppn)(mp, argp->name, &retry, VLOOK_DELETE);
	if (mp == 0) {
		/*
		 * Ignore retries...
		 */
		if (retry < 0)
			retry = 0;
		/*
		 * Usual NFS workaround...
		 */
		else if (retry == ENOENT)
			retry = 0;
		res = nfs_error(retry);
	} else {
		forcibly_timeout_mp(mp);
		res = NFS_OK;
	}

out:
	return &res;
}


/*ARGSUSED*/
nfsstat *
nfsproc_remove_2(argp, rqstp)
struct diropargs *argp;
struct svc_req *rqstp;
{
D 2
	return unlink_or_rmdir(argp, rqstp, 1);
E 2
I 2
	return unlink_or_rmdir(argp, rqstp, TRUE);
E 2
}

/*ARGSUSED*/
nfsstat *
nfsproc_rename_2(argp, rqstp)
renameargs *argp;
struct svc_req *rqstp;
{
	static nfsstat res;
	if (!fh_to_mp(&argp->from.dir) || !fh_to_mp(&argp->to.dir))
		res = nfs_error(ESTALE);
	/*
	 * If the kernel is doing clever things with referenced files
	 * then let it pretend...
	 */
	else if (strncmp(argp->to.name, ".nfs", 4) == 0)
		res = NFS_OK;
	/*
	 * otherwise a failure
	 */
	else
		res = nfs_error(EROFS);
	return &res;
}


/*ARGSUSED*/
nfsstat *
nfsproc_link_2(argp, rqstp)
linkargs *argp;
struct svc_req *rqstp;
{
	static nfsstat res;
	if (!fh_to_mp(&argp->from) || !fh_to_mp(&argp->to.dir))
		res = nfs_error(ESTALE);
	else
		res = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
nfsstat *
nfsproc_symlink_2(argp, rqstp)
symlinkargs *argp;
struct svc_req *rqstp;
{
	static nfsstat res;
	if (!fh_to_mp(&argp->from.dir))
		res = nfs_error(ESTALE);
	else
		res = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
struct diropres *
nfsproc_mkdir_2(argp, rqstp)
createargs *argp;
struct svc_req *rqstp;
{
	static struct diropres res;
	if (!fh_to_mp(&argp->where.dir))
		res.status = nfs_error(ESTALE);
	else
		res.status = nfs_error(EROFS);

	return &res;
}


/*ARGSUSED*/
nfsstat *
nfsproc_rmdir_2(argp, rqstp)
struct diropargs *argp;
struct svc_req *rqstp;
{
D 2
	return unlink_or_rmdir(argp, rqstp, 0);
E 2
I 2
	return unlink_or_rmdir(argp, rqstp, FALSE);
E 2
}


/*ARGSUSED*/
struct readdirres *
nfsproc_readdir_2(argp, rqstp)
readdirargs *argp;
struct svc_req *rqstp;
{
	static readdirres res;
D 2
	static entry e_res[2];
E 2
I 2
	static entry e_res[MAX_READDIR_ENTRIES];
E 2
	am_node *mp;
	int retry;

#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "readdir:");
#endif /* DEBUG */

	mp = fh_to_mp2(&argp->dir, &retry);
	if (mp == 0) {
		if (retry < 0)
			return 0;
		res.status = nfs_error(retry);
	} else {
#ifdef DEBUG
		Debug(D_TRACE)
			plog(XLOG_DEBUG, "\treaddir(%s)", mp->am_path);
#endif /* DEBUG */
		res.status = nfs_error((*mp->am_mnt->mf_ops->readdir)(mp, argp->cookie,
D 2
					&res.readdirres_u.reply, e_res));
E 2
I 2
					&res.readdirres_u.reply, e_res, argp->count));
E 2
		mp->am_stats.s_readdir++;
	}

D 2
	/* XXX - need to take argp->count into account */

E 2
	return &res;
}

/*ARGSUSED*/
struct statfsres *
nfsproc_statfs_2(argp, rqstp)
struct nfs_fh *argp;
struct svc_req *rqstp;
{
	static statfsres res;
	am_node *mp;
	int retry;

#ifdef DEBUG
	Debug(D_TRACE)
		plog(XLOG_DEBUG, "statfs:");
#endif /* DEBUG */

	mp = fh_to_mp2(argp, &retry);
	if (mp == 0) {
		if (retry < 0)
			return 0;
		res.status = nfs_error(retry);
	} else {
		statfsokres *fp;
#ifdef DEBUG
		Debug(D_TRACE)
			plog(XLOG_DEBUG, "\tstat_fs(%s)", mp->am_path);
#endif /* DEBUG */
		/*
		 * just return faked up file system information
		 */

		fp = &res.statfsres_u.reply;

		fp->tsize = 1024;
D 2
		fp->bsize = 4192;
E 2
I 2
		fp->bsize = 4096;
#ifdef HAS_EMPTY_AUTOMOUNTS
		fp->blocks = 0;
#else
E 2
		fp->blocks = 1;
I 2
#endif
E 2
		fp->bfree = 0;
		fp->bavail = 0;

		res.status = NFS_OK;
		mp->am_stats.s_statfs++;
	}

	return &res;
}
E 1
