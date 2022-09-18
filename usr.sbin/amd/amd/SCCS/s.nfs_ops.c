h53764
s 00005/00003/00780
d D 8.2 95/05/10 05:38:47 pendry 9 8
c add support for new nfs code (not v3 though)
e
s 00002/00002/00781
d D 8.1 93/06/06 11:40:41 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00778
d D 5.7 93/05/06 12:50:48 hibler 7 6
c add support for "maxgroups" option
e
s 00005/00004/00773
d D 5.6 92/08/01 15:57:12 bostic 6 5
c header corruption
e
s 00038/00001/00739
d D 5.5 92/05/31 10:42:21 pendry 5 4
c code refresh
e
s 00014/00004/00726
d D 5.4 92/02/09 08:48:40 pendry 4 3
c merge in new release
e
s 00025/00005/00705
d D 5.3 91/05/12 15:55:49 pendry 3 2
c checkpoint for network tape
e
s 00070/00028/00640
d D 5.2 91/03/17 13:33:38 pendry 2 1
c from amd5.3 alpha11
e
s 00668/00000/00000
d D 5.1 90/06/29 12:01:12 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 6
/*
E 6
I 6
/*-
E 6
D 2
 * $Id: nfs_ops.c,v 5.2 90/06/23 22:19:45 jsp Rel $
E 2
I 2
D 3
 * $Id: nfs_ops.c,v 5.2.1.4 91/03/17 17:45:55 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
D 6
 *	@(#)nfs_ops.c	1.3 (Berkeley) 6/26/91
E 4
I 3
 *
E 6
D 4
 * $Id: nfs_ops.c,v 5.2.1.6 91/05/07 22:18:16 jsp Alpha $
E 4
I 4
D 5
 * $Id: nfs_ops.c,v 5.2.2.1 1992/02/09 15:08:47 jsp beta $
E 5
I 5
 * $Id: nfs_ops.c,v 5.2.2.2 1992/05/31 16:35:05 jsp Exp $
E 5
E 4
D 6
 *
E 6
E 3
 */
I 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

#include "am.h"
I 5
#include <sys/stat.h>
E 5

#ifdef HAS_NFS

#define NFS
#define NFSCLIENT
#ifdef NFS_3
typedef nfs_fh fhandle_t;
#endif /* NFS_3 */
I 9
#include <sys/mount.h>
E 9
#ifdef NFS_HDR
#include NFS_HDR
#endif /* NFS_HDR */
D 9
#include <sys/mount.h>
E 9
#include "mount.h"

/*
 * Network file system
 */

/*
 * Convert from nfsstat to UN*X error code
 */
#define unx_error(e)	((int)(e))

/*
 * The NFS layer maintains a cache of file handles.
 * This is *fundamental* to the implementation and
 * also allows quick remounting when a filesystem
 * is accessed soon after timing out.
 *
 * The NFS server layer knows to flush this cache
 * when a server goes down so avoiding stale handles.
 *
 * Each cache entry keeps a hard reference to
 * the corresponding server.  This ensures that
 * the server keepalive information is maintained.
 *
 * The copy of the sockaddr_in here is taken so
 * that the port can be twiddled to talk to mountd
 * instead of portmap or the NFS server as used
 * elsewhere.
 * The port# is flushed if a server goes down.
 * The IP address is never flushed - we assume
 * that the address of a mounted machine never
 * changes.  If it does, then you have other
 * problems...
 */
typedef struct fh_cache fh_cache;
struct fh_cache {
	qelem	fh_q;			/* List header */
	voidp	fh_wchan;		/* Wait channel */
	int	fh_error;		/* Valid data? */
	int	fh_id;			/* Unique id */
	int	fh_cid;			/* Callout id */
	struct fhstatus fh_handle;	/* Handle on filesystem */
	struct sockaddr_in fh_sin;	/* Address of mountd */
	fserver *fh_fs;			/* Server holding filesystem */
	char	*fh_path;		/* Filesystem on host */
};

/*
 * FH_TTL is the time a file handle will remain in the cache since
 * last being used.  If the file handle becomes invalid, then it
 * will be flushed anyway.
 */
#define	FH_TTL		(5 * 60)		/* five minutes */
#define	FH_TTL_ERROR	(30)			/* 30 seconds */

static int fh_id = 0;
#define	FHID_ALLOC()	(++fh_id)
extern qelem fh_head;
qelem fh_head = { &fh_head, &fh_head };

static int call_mountd P((fh_cache*, unsigned long, fwd_fun, voidp));

AUTH *nfs_auth;

static fh_cache *find_nfs_fhandle_cache P((voidp idv, int done));
static fh_cache *find_nfs_fhandle_cache(idv, done)
voidp idv;
int done;
{
	fh_cache *fp, *fp2 = 0;
	int id = (int) idv;

	ITER(fp, fh_cache, &fh_head) {
		if (fp->fh_id == id) {
			fp2 = fp;
			break;
		}
	}

#ifdef DEBUG
	if (fp2) {
		dlog("fh cache gives fp %#x, fs %s", fp2, fp2->fh_path);
	} else {
		dlog("fh cache search failed");
	}
#endif /* DEBUG */

	if (fp2 && !done) {
		fp2->fh_error = ETIMEDOUT;
		return 0;
	}

	return fp2;
}

/*
 * Called when a filehandle appears
 */
static void got_nfs_fh P((voidp pkt, int len, struct sockaddr_in *sa,
				struct sockaddr_in *ia, voidp idv, int done));
static void got_nfs_fh(pkt, len, sa, ia, idv, done)
voidp pkt;
int len;
struct sockaddr_in *sa, *ia;
voidp idv;
int done;
{
	fh_cache *fp = find_nfs_fhandle_cache(idv, done);
	if (fp) {
		fp->fh_error = pickup_rpc_reply(pkt, len, (voidp) &fp->fh_handle, xdr_fhstatus);
		if (!fp->fh_error) {
#ifdef DEBUG
			dlog("got filehandle for %s:%s", fp->fh_fs->fs_host, fp->fh_path);
#endif /* DEBUG */
			/*
			 * Wakeup anything sleeping on this filehandle
			 */
			if (fp->fh_wchan) {
#ifdef DEBUG
				dlog("Calling wakeup on %#x", fp->fh_wchan);
#endif /* DEBUG */
				wakeup(fp->fh_wchan);
			}
		}
	}
}

void flush_nfs_fhandle_cache P((fserver *fs));
void flush_nfs_fhandle_cache(fs)
fserver *fs;
{
	fh_cache *fp;
	ITER(fp, fh_cache, &fh_head) {
D 2
		if (fp->fh_fs == fs) {
E 2
I 2
		if (fp->fh_fs == fs || fs == 0) {
E 2
			fp->fh_sin.sin_port = (u_short) 0;
			fp->fh_error = -1;
		}
	}
}

static void discard_fh P((fh_cache *fp));
static void discard_fh(fp)
fh_cache *fp;
{
	rem_que(&fp->fh_q);
#ifdef DEBUG
	dlog("Discarding filehandle for %s:%s", fp->fh_fs->fs_host, fp->fh_path);
#endif /* DEBUG */
	free_srvr(fp->fh_fs);
	free((voidp) fp->fh_path);
	free((voidp) fp);
}

/*
 * Determine the file handle for a node
 */
static int prime_nfs_fhandle_cache P((char *path, fserver *fs, struct fhstatus *fhbuf, voidp wchan));
static int prime_nfs_fhandle_cache(path, fs, fhbuf, wchan)
char *path;
fserver *fs;
struct fhstatus *fhbuf;
voidp wchan;
{
	fh_cache *fp, *fp_save = 0;
	int error;
	int reuse_id = FALSE;

#ifdef DEBUG
	dlog("Searching cache for %s:%s", fs->fs_host, path);
#endif /* DEBUG */

	/*
	 * First search the cache
	 */
	ITER(fp, fh_cache, &fh_head) {
		if (fs == fp->fh_fs && strcmp(path, fp->fh_path) == 0) {
			switch (fp->fh_error) {
			case 0:
				error = fp->fh_error = unx_error(fp->fh_handle.fhs_status);
				if (error == 0) {
					if (fhbuf)
						bcopy((voidp) &fp->fh_handle, (voidp) fhbuf,
							sizeof(fp->fh_handle));
					if (fp->fh_cid)
						untimeout(fp->fh_cid);
					fp->fh_cid = timeout(FH_TTL, discard_fh, (voidp) fp);
				} else if (error == EACCES) {
					/*
					 * Now decode the file handle return code.
					 */
					plog(XLOG_INFO, "Filehandle denied for \"%s:%s\"",
						fs->fs_host, path);
				} else {
					errno = error;	/* XXX */
					plog(XLOG_INFO, "Filehandle error for \"%s:%s\": %m",
						fs->fs_host, path);
				}

				/*
				 * The error was returned from the remote mount daemon.
				 * Policy: this error will be cached for now...
				 */
				return error;

			case -1:
				/*
				 * Still thinking about it, but we can re-use.
				 */
				fp_save = fp;
				reuse_id = TRUE;
				break;

			default:
				/*
				 * Return the error.
				 * Policy: make sure we recompute if required again
				 * in case this was caused by a network failure.
				 * This can thrash mountd's though...  If you find
				 * your mountd going slowly then:
				 * 1.  Add a fork() loop to main.
				 * 2.  Remove the call to innetgr() and don't use
				 *     netgroups, especially if you don't use YP.
				 */
				error = fp->fh_error;
				fp->fh_error = -1;
				return error;
			}
			break;
		}
	}

	/*
	 * Not in cache
	 */
	if (fp_save) {
		fp = fp_save;
		/*
		 * Re-use existing slot
		 */
		untimeout(fp->fh_cid);
		free_srvr(fp->fh_fs);
		free(fp->fh_path);
	} else {
		fp = ALLOC(fh_cache);
		bzero((voidp) fp, sizeof(*fp));
		ins_que(&fp->fh_q, &fh_head);
	}
	if (!reuse_id)
		fp->fh_id = FHID_ALLOC();
	fp->fh_wchan = wchan;
	fp->fh_error = -1;
	fp->fh_cid = timeout(FH_TTL, discard_fh, (voidp) fp);

	/*
	 * If the address has changed then don't try to re-use the
	 * port information
	 */
	if (fp->fh_sin.sin_addr.s_addr != fs->fs_ip->sin_addr.s_addr) {
		fp->fh_sin = *fs->fs_ip;
		fp->fh_sin.sin_port = 0;
	}
	fp->fh_fs = dup_srvr(fs);
	fp->fh_path = strdup(path);

	error = call_mountd(fp, MOUNTPROC_MNT, got_nfs_fh, wchan);
	if (error) {
		/*
		 * Local error - cache for a short period
		 * just to prevent thrashing.
		 */
		untimeout(fp->fh_cid);
		fp->fh_cid = timeout(error < 0 ? 2 * ALLOWED_MOUNT_TIME : FH_TTL_ERROR,
						discard_fh, (voidp) fp);
		fp->fh_error = error;
	} else {
		error = fp->fh_error;
	}
	return error;
}

I 3
int make_nfs_auth P((void))
{
#ifdef HAS_NFS_QUALIFIED_NAMES
	/*
	 * From: Chris Metcalf <metcalf@masala.lcs.mit.edu>
	 * Use hostd, not just hostname.  Note that uids
	 * and gids and the gidlist are type *int* and not the
	 * system uid_t and gid_t types.
	 */
	static int group_wheel = 0;
	nfs_auth = authunix_create(hostd, 0, 0, 1, &group_wheel);
#else
	nfs_auth = authunix_create_default();
#endif
	if (!nfs_auth)
		return ENOBUFS;
	return 0;
}

E 3
static int call_mountd P((fh_cache *fp, u_long proc, fwd_fun f, voidp wchan));
static int call_mountd(fp, proc, f, wchan)
fh_cache *fp;
u_long proc;
fwd_fun f;
voidp wchan;
{
	struct rpc_msg mnt_msg;
	int len;
	char iobuf[8192];
	int error;

	if (!nfs_auth) {
D 3
		nfs_auth = authunix_create_default();
		if (!nfs_auth)
			return ENOBUFS;
E 3
I 3
		error = make_nfs_auth();
		if (error)
			return error;
E 3
	}

	if (fp->fh_sin.sin_port == 0) {
		u_short port;
		error = nfs_srvr_port(fp->fh_fs, &port, wchan);
		if (error)
			return error;
		fp->fh_sin.sin_port = port;
	}

	rpc_msg_init(&mnt_msg, MOUNTPROG, MOUNTVERS, (unsigned long) 0);
	len = make_rpc_packet(iobuf, sizeof(iobuf), proc,
			&mnt_msg, (voidp) &fp->fh_path, xdr_nfspath,  nfs_auth);

	if (len > 0) {
		error = fwd_packet(MK_RPC_XID(RPC_XID_MOUNTD, fp->fh_id),
			(voidp) iobuf, len, &fp->fh_sin, &fp->fh_sin, (voidp) fp->fh_id, f);
	} else {
		error = -len;
	}
I 5
/*
 * It may be the case that we're sending to the wrong MOUNTD port.  This
 * occurs if mountd is restarted on the server after the port has been
 * looked up and stored in the filehandle cache somewhere.  The correct
 * solution, if we're going to cache port numbers is to catch the ICMP
 * port unreachable reply from the server and cause the portmap request
 * to be redone.  The quick solution here is to invalidate the MOUNTD
 * port.
 */
      fp->fh_sin.sin_port = 0;

E 5
	return error;
}

/*-------------------------------------------------------------------------*/

/*
 * NFS needs the local filesystem, remote filesystem
 * remote hostname.
 * Local filesystem defaults to remote and vice-versa.
 */
D 2
static int nfs_match(fo)
E 2
I 2
static char *nfs_match(fo)
E 2
am_opts *fo;
{
I 2
	char *xmtab;
E 2
	if (fo->opt_fs && !fo->opt_rfs)
		fo->opt_rfs = fo->opt_fs;
	if (!fo->opt_rfs) {
		plog(XLOG_USER, "nfs: no remote filesystem specified");
		return FALSE;
	}
	if (!fo->opt_rhost) {
		plog(XLOG_USER, "nfs: no remote host specified");
		return FALSE;
	}
	/*
	 * Determine magic cookie to put in mtab
	 */
D 2
	fo->fs_mtab = (char *) xrealloc(fo->fs_mtab, strlen(fo->opt_rhost) +
				strlen(fo->opt_rfs) + 2);
	sprintf(fo->fs_mtab, "%s:%s", fo->opt_rhost, fo->opt_rfs);
E 2
I 2
	xmtab = (char *) xmalloc(strlen(fo->opt_rhost) + strlen(fo->opt_rfs) + 2);
	sprintf(xmtab, "%s:%s", fo->opt_rhost, fo->opt_rfs);
E 2
#ifdef DEBUG
	dlog("NFS: mounting remote server \"%s\", remote fs \"%s\" on \"%s\"",
		fo->opt_rhost, fo->opt_rfs, fo->opt_fs);
#endif /* DEBUG */

D 2
	return TRUE;
E 2
I 2
	return xmtab;
E 2
}

/*
 * Initialise am structure for nfs
 */
static int nfs_init(mf)
mntfs *mf;
{
D 2
	int error;
	char *colon = strchr(mf->mf_info, ':');
	if (colon == 0)
		return ENOENT;
E 2
I 2
	if (!mf->mf_private) {
		int error;
		struct fhstatus fhs;
	
		char *colon = strchr(mf->mf_info, ':');
		if (colon == 0)
			return ENOENT;
E 2

D 2
	error = prime_nfs_fhandle_cache(colon+1, mf->mf_server, (struct fhstatus *) 0, (voidp) mf);
E 2
I 2
		error = prime_nfs_fhandle_cache(colon+1, mf->mf_server, &fhs, (voidp) mf);
		if (!error) {
			mf->mf_private = (voidp) ALLOC(fhstatus);
			mf->mf_prfree = (void (*)()) free;
			bcopy((voidp) &fhs, mf->mf_private, sizeof(fhs));
		}
		return error;
	}
E 2

D 2
	return error;
E 2
I 2
	return 0;
E 2
}

I 4
int mount_nfs_fh P((struct fhstatus *fhp, char *dir, char *fs_name, char *opts, mntfs *mf));
E 4
D 2
mount_nfs_fh(fhp, dir, fs_name, opts, mf)
E 2
I 2
int mount_nfs_fh(fhp, dir, fs_name, opts, mf)
E 2
struct fhstatus *fhp;
char *dir;
char *fs_name;
char *opts;
mntfs *mf;
{
	struct nfs_args nfs_args;
	struct mntent mnt;
	int retry;
	char *colon;
D 2
	char *path;
E 2
I 2
	/*char *path;*/
E 2
	char host[MAXHOSTNAMELEN + MAXPATHLEN + 2];
	fserver *fs = mf->mf_server;
	int flags;
I 4
	char *xopts;
	int error;
E 4
#ifdef notdef
	unsigned short port;
#endif /* notdef */

	MTYPE_TYPE type = MOUNT_TYPE_NFS;

	bzero((voidp) &nfs_args, sizeof(nfs_args));	/* Paranoid */

	/*
	 * Extract host name to give to kernel
	 */
	if (!(colon = strchr(fs_name, ':')))
		return ENOENT;
#ifndef NFS_ARGS_NEEDS_PATH
	*colon = '\0';
#endif
	strncpy(host, fs_name, sizeof(host));
#ifndef NFS_ARGS_NEEDS_PATH
	*colon = ':';
#endif /* NFS_ARGS_NEEDS_PATH */
D 2
	path = colon + 1;
E 2
I 2
	/*path = colon + 1;*/
E 2

I 4
	if (mf->mf_remopts && *mf->mf_remopts && !islocalnet(fs->fs_ip->sin_addr.s_addr))
		xopts = strdup(mf->mf_remopts);
	else
		xopts = strdup(opts);

E 4
D 9
	bzero((voidp) &nfs_args, sizeof(nfs_args));

E 9
	mnt.mnt_dir = dir;
	mnt.mnt_fsname = fs_name;
	mnt.mnt_type = MTAB_TYPE_NFS;
D 4
	mnt.mnt_opts = opts;
E 4
I 4
	mnt.mnt_opts = xopts;
E 4
	mnt.mnt_freq = 0;
	mnt.mnt_passno = 0;

	retry = hasmntval(&mnt, "retry");
	if (retry <= 0)
		retry = 1;	/* XXX */

/*again:*/

	/*
	 * set mount args
	 */
I 9
#ifdef NFS_ARGSVERSION
	nfs_args.version = NFS_ARGSVERSION;
#endif

E 9
	NFS_FH_DREF(nfs_args.fh, (NFS_FH_TYPE) fhp->fhstatus_u.fhs_fhandle);

#ifdef ULTRIX_HACK
	nfs_args.optstr = mnt.mnt_opts;
#endif /* ULTRIX_HACK */

	nfs_args.hostname = host;
	nfs_args.flags |= NFSMNT_HOSTNAME;
#ifdef HOSTNAMESZ
	/*
	 * Most kernels have a name length restriction.
	 */
	if (strlen(host) >= HOSTNAMESZ)
		strcpy(host + HOSTNAMESZ - 3, "..");
#endif /* HOSTNAMESZ */

	if (nfs_args.rsize = hasmntval(&mnt, "rsize"))
		nfs_args.flags |= NFSMNT_RSIZE;

	if (nfs_args.wsize = hasmntval(&mnt, "wsize"))
		nfs_args.flags |= NFSMNT_WSIZE;

	if (nfs_args.timeo = hasmntval(&mnt, "timeo"))
		nfs_args.flags |= NFSMNT_TIMEO;

	if (nfs_args.retrans = hasmntval(&mnt, "retrans"))
		nfs_args.flags |= NFSMNT_RETRANS;

#ifdef NFSMNT_BIODS
	if (nfs_args.biods = hasmntval(&mnt, "biods"))
		nfs_args.flags |= NFSMNT_BIODS;

#endif /* NFSMNT_BIODS */

I 7
#ifdef NFSMNT_MAXGRPS
	if (nfs_args.maxgrouplist = hasmntval(&mnt, "maxgroups"))
		nfs_args.flags |= NFSMNT_MAXGRPS;
#endif /* NFSMNT_MAXGRPS */

E 7
#ifdef notdef
/*
 * This isn't supported by the ping algorithm yet.
 * In any case, it is all done in nfs_init().
 */
 	if (port = hasmntval(&mnt, "port"))
		sin.sin_port = htons(port);
	else
		sin.sin_port = htons(NFS_PORT);	/* XXX should use portmapper */
#endif /* notdef */

	if (hasmntopt(&mnt, MNTOPT_SOFT) != NULL)
		nfs_args.flags |= NFSMNT_SOFT;

I 2
#ifdef NFSMNT_SPONGY
	if (hasmntopt(&mnt, "spongy") != NULL) {
		nfs_args.flags |= NFSMNT_SPONGY;
		if (nfs_args.flags & NFSMNT_SOFT) {
			plog(XLOG_USER, "Mount opts soft and spongy are incompatible - soft ignored");
			nfs_args.flags &= ~NFSMNT_SOFT;
		}
	}
#endif /* MNTOPT_SPONGY */

E 2
#ifdef MNTOPT_INTR
	if (hasmntopt(&mnt, MNTOPT_INTR) != NULL)
		nfs_args.flags |= NFSMNT_INT;
#endif /* MNTOPT_INTR */

#ifdef MNTOPT_NODEVS
	if (hasmntopt(&mnt, MNTOPT_NODEVS) != NULL)
		nfs_args.flags |= NFSMNT_NODEVS;
#endif /* MNTOPT_NODEVS */

I 2
#ifdef MNTOPT_COMPRESS
	if (hasmntopt(&mnt, "compress") != NULL)
		nfs_args.flags |= NFSMNT_COMPRESS;
#endif /* MNTOPT_COMPRESS */

#ifdef MNTOPT_NOCONN
	if (hasmntopt(&mnt, "noconn") != NULL)
		nfs_args.flags |= NFSMNT_NOCONN;
#endif /* MNTOPT_NOCONN */

E 2
#ifdef NFSMNT_PGTHRESH
	if (nfs_args.pg_thresh = hasmntval(&mnt, "pgthresh"))
		nfs_args.flags |= NFSMNT_PGTHRESH;
#endif /* NFSMNT_PGTHRESH */

	NFS_SA_DREF(nfs_args, fs->fs_ip);

	flags = compute_mount_flags(&mnt);

I 2
#ifdef NFSMNT_NOCTO
	if (hasmntopt(&mnt, "nocto") != NULL)
		nfs_args.flags |= NFSMNT_NOCTO;
#endif /* NFSMNT_NOCTO */

E 2
#ifdef HAS_TCP_NFS
	if (hasmntopt(&mnt, "tcp") != NULL)
		nfs_args.sotype = SOCK_STREAM;
#endif /* HAS_TCP_NFS */


#ifdef ULTRIX_HACK
	/*
	 * Ultrix passes the flags argument as part of the
	 * mount data structure, rather than using the
	 * flags argument to the system call.  This is
	 * confusing...
	 */
	if (!(nfs_args.flags & NFSMNT_PGTHRESH)) {
		nfs_args.pg_thresh = 64; /* 64k - XXX */
		nfs_args.flags |= NFSMNT_PGTHRESH;
	}
	nfs_args.gfs_flags = flags;
	flags &= M_RDONLY;
	if (flags & M_RDONLY)
		nfs_args.flags |= NFSMNT_RONLY;
#endif /* ULTRIX_HACK */

D 4
	return mount_fs(&mnt, flags, (caddr_t) &nfs_args, retry, type);
E 4
I 4
	error = mount_fs(&mnt, flags, (caddr_t) &nfs_args, retry, type);
	free(xopts);
	return error;
E 4
}

D 2
static mount_nfs(dir, fs_name, opts, mf)
E 2
I 2
static int mount_nfs(dir, fs_name, opts, mf)
E 2
char *dir;
char *fs_name;
char *opts;
mntfs *mf;
{
I 2
#ifdef notdef
E 2
	int error;
	struct fhstatus fhs;
	char *colon;

	if (!(colon = strchr(fs_name, ':')))
		return ENOENT;

#ifdef DEBUG
	dlog("locating fhandle for %s", fs_name);
#endif /* DEBUG */
	error = prime_nfs_fhandle_cache(colon+1, mf->mf_server, &fhs, (voidp) 0);

	if (error)
		return error;

	return mount_nfs_fh(&fhs, dir, fs_name, opts, mf);
I 2
#endif
	if (!mf->mf_private) {
		plog(XLOG_ERROR, "Missing filehandle for %s", fs_name);
		return EINVAL;
	}

	return mount_nfs_fh((struct fhstatus *) mf->mf_private, dir, fs_name, opts, mf);
E 2
}

D 2
static int nfs_mount(mp)
am_node *mp;
E 2
I 2
static int nfs_fmount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;
E 2
I 2
	int error;
E 2

D 2
	int error = mount_nfs(mf->mf_mount, mf->mf_info,
			mf->mf_fo->opt_opts, mf);
E 2
I 2
	error = mount_nfs(mf->mf_mount, mf->mf_info, mf->mf_mopts, mf);
E 2

#ifdef DEBUG
	if (error) {
		errno = error;
		dlog("mount_nfs: %m");
	}
#endif /* DEBUG */
	return error;
}

D 2
static int nfs_umount(mp)
am_node *mp;
E 2
I 2
static int nfs_fumount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	int error = UMOUNT_FS(mf->mf_mount);
	if (error)
		return error;

	return 0;
}

static void nfs_umounted(mp)
am_node *mp;
{
#ifdef INFORM_MOUNTD
	/*
	 * Don't bother to inform remote mountd
	 * that we are finished.  Until a full
	 * track of filehandles is maintained
	 * the mountd unmount callback cannot
	 * be done correctly anyway...
	 */

	mntfs *mf = mp->am_mnt;
	fserver *fs;
	char *colon, *path;

	if (mf->mf_error || mf->mf_refc > 1)
		return;

	fs = mf->mf_server;

	/*
	 * Call the mount daemon on the server to
	 * announce that we are not using the fs any more.
	 *
	 * This is *wrong*.  The mountd should be called
	 * when the fhandle is flushed from the cache, and
	 * a reference held to the cached entry while the
	 * fs is mounted...
	 */
	colon = path = strchr(mf->mf_info, ':');
	if (fs && colon) {
		fh_cache f;
#ifdef DEBUG
		dlog("calling mountd for %s", mf->mf_info);
#endif /* DEBUG */
		*path++ = '\0';
		f.fh_path = path;
		f.fh_sin = *fs->fs_ip;
		f.fh_sin.sin_port = (u_short) 0;
		f.fh_fs = fs;
		f.fh_id = 0;
		f.fh_error = 0;
		(void) prime_nfs_fhandle_cache(colon+1, mf->mf_server, (struct fhstatus *) 0, (voidp) mf);
		(void) call_mountd(&f, MOUNTPROC_UMNT, (fwd_fun) 0, (voidp) 0);
		*colon = ':';
	}
#endif /* INFORM_MOUNTD */
I 5

#ifdef KICK_KERNEL
	/* This should go into the mainline code, not in nfs_ops... */

	/*
	 * Run lstat over the underlying directory in
	 * case this was a direct mount.  This will
	 * get the kernel back in sync with reality.
	 */
	if (mp->am_parent && mp->am_parent->am_path &&
	    STREQ(mp->am_parent->am_mnt->mf_ops->fs_type, "direct")) {
		struct stat stb;
		int pid;
		if ((pid = background()) == 0) {
			if (lstat(mp->am_parent->am_path, &stb) < 0) {
				plog(XLOG_ERROR, "lstat(%s) after unmount: %m", mp->am_parent->am_path);
#ifdef DEBUG
			} else {
				dlog("hack lstat(%s): ok", mp->am_parent->am_path);
#endif /* DEBUG */
			}
			_exit(0);
		}
	}
#endif /* KICK_KERNEL */
E 5
}

/*
 * Network file system
 */
am_ops nfs_ops = {
	"nfs",
	nfs_match,
	nfs_init,
D 2
	nfs_mount,
	nfs_umount,
E 2
I 2
	auto_fmount,
	nfs_fmount,
	auto_fumount,
	nfs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* nfs_readlink */
	0, /* nfs_mounted */
	nfs_umounted,
	find_nfs_srvr,
	FS_MKMNT|FS_BACKGROUND|FS_AMQINFO
};

#endif /* HAS_NFS */
E 1
