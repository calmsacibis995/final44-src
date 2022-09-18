h60850
s 00005/00001/01789
d D 8.2 95/05/10 05:38:49 pendry 8 7
c add support for new nfs code (not v3 though)
e
s 00002/00002/01788
d D 8.1 93/06/06 11:39:29 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/01785
d D 5.6 92/07/20 15:59:39 pendry 6 5
c apply workaround for (supposed) mystery nfs bug
e
s 00041/00017/01744
d D 5.5 92/05/31 10:42:27 pendry 5 4
c code refresh
e
s 00003/00003/01758
d D 5.4 92/02/09 08:47:48 pendry 4 3
c merge in new release
e
s 00019/00022/01742
d D 5.3 91/05/12 15:56:31 pendry 3 2
c checkpoint for network tape
e
s 00449/00229/01315
d D 5.2 91/03/17 13:32:44 pendry 2 1
c from amd5.3 alpha11
e
s 01544/00000/00000
d D 5.1 90/06/29 12:00:58 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: afs_ops.c,v 5.2 90/06/23 22:19:14 jsp Rel $
E 2
I 2
D 3
 * $Id: afs_ops.c,v 5.2.1.6 91/03/17 17:49:10 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
 * $Id: afs_ops.c,v 5.2.1.9 91/05/07 22:17:40 jsp Alpha $
E 4
I 4
D 5
 * $Id: afs_ops.c,v 5.2.2.1 1992/02/09 15:08:11 jsp beta $
E 5
I 5
 * $Id: afs_ops.c,v 5.2.2.4 1992/05/31 16:36:36 jsp Exp $
E 5
E 4
 *
E 3
 */

#include "am.h"

#define NFS
#define NFSCLIENT

#include <sys/stat.h>
#ifdef NFS_3
typedef nfs_fh fhandle_t;
#endif /* NFS_3 */
I 8
#include <sys/mount.h>
E 8
#ifdef NFS_HDR
#include NFS_HDR
#endif /* NFS_HDR */
D 8
#include <sys/mount.h>
E 8
#include "mount.h"

/*
 * Automount file system
I 2
 * Direct file system
 * Root file system
 * Top-level file system
E 2
 */

/*
 * Interval between forced retries of a mount.
 */
#define RETRY_INTERVAL	2

/*
 * AFS needs nothing in particular.
 */
D 2
static int afs_match(fo)
E 2
I 2
static char *afs_match P((am_opts *fo));
static char *afs_match(fo)
E 2
am_opts *fo;
{
	char *p = fo->opt_rfs;
	if (!fo->opt_rfs) {
		plog(XLOG_USER, "auto: no mount point named (rfs:=)");
		return 0;
	}
	if (!fo->opt_fs) {
		plog(XLOG_USER, "auto: no map named (fs:=)");
		return 0;
	}
	/*
	 * Swap round fs:= and rfs:= options
	 * ... historical (jsp)
	 */
	fo->opt_rfs = fo->opt_fs;
	fo->opt_fs = p;
	/*
D 2
	 * fs_mtab turns out to be the name of the mount map
E 2
I 2
	 * mtab entry turns out to be the name of the mount map
E 2
	 */
D 2
	fo->fs_mtab = strealloc(fo->fs_mtab, fo->opt_rfs ? fo->opt_rfs : ".");
	return 1;
E 2
I 2
	return strdup(fo->opt_rfs ? fo->opt_rfs : ".");
E 2
}

D 2
static int afs_init(mf)
mntfs *mf;
{
	/*
	 * Fill in attribute fields
	 */
	mf->mf_fattr.type = NFDIR;
	mf->mf_fattr.mode = NFSMODE_DIR | 0555;
	mf->mf_fattr.nlink = 2;
	mf->mf_fattr.size = 512;

	return 0;
}

E 2
/*
D 2
 * Mount the an automounter directory.
E 2
I 2
 * Mount an automounter directory.
E 2
 * The automounter is connected into the system
D 2
 * as a user-level NFS server.  mount_afs constructs
E 2
I 2
 * as a user-level NFS server.  mount_toplvl constructs
E 2
 * the necessary NFS parameters to be given to the
 * kernel so that it will talk back to us.
 */
D 2
static int mount_afs(dir, fs_name, opts)
E 2
I 2
static int mount_toplvl P((char *dir, char *opts));
static int mount_toplvl(dir, opts)
E 2
char *dir;
D 2
char *fs_name;
E 2
char *opts;
{
	struct nfs_args nfs_args;
	struct mntent mnt;
	int retry;
	struct sockaddr_in sin;
	unsigned short port;
	int flags;
	extern nfs_fh *root_fh();
	nfs_fh *fhp;
	char fs_hostname[MAXHOSTNAMELEN+MAXPATHLEN+1];

	MTYPE_TYPE type = MOUNT_TYPE_NFS;

	bzero((voidp) &nfs_args, sizeof(nfs_args));	/* Paranoid */

	mnt.mnt_dir = dir;
D 2
	mnt.mnt_fsname = fs_name;
E 2
I 2
	mnt.mnt_fsname = pid_fsname;
E 2
	mnt.mnt_type = MNTTYPE_AUTO;
	mnt.mnt_opts = opts;
	mnt.mnt_freq = 0;
	mnt.mnt_passno = 0;

	retry = hasmntval(&mnt, "retry");
	if (retry <= 0)
		retry = 2;	/* XXX */

	/*
	 * get fhandle of remote path for automount point
	 */
	
D 2
	fhp = root_fh(fs_name);
E 2
I 2
	fhp = root_fh(dir);
E 2
	if (!fhp) {
D 2
		plog(XLOG_FATAL, "Can't find root file handle for %s", fs_name);
E 2
I 2
		plog(XLOG_FATAL, "Can't find root file handle for %s", dir);
E 2
		return EINVAL;
	}
I 8

#ifdef NFS_ARGSVERSION
	nfs_args.version = NFS_ARGSVERSION;
#endif
E 8

	NFS_FH_DREF(nfs_args.fh, (NFS_FH_TYPE) fhp);

	/*
	 * Create sockaddr to point to the local machine.  127.0.0.1
	 * is not used since that will not work in HP-UX clusters and
	 * this is no more expensive.
	 */
	bzero((voidp) &sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr = myipaddr;
	if (port = hasmntval(&mnt, "port")) {
		sin.sin_port = htons(port);
	} else {
D 2
		plog(XLOG_ERROR, "no port number specified for %s", fs_name);
E 2
I 2
		plog(XLOG_ERROR, "no port number specified for %s", dir);
E 2
		return EINVAL;
	}

	/*
	 * set mount args
	 */
	NFS_SA_DREF(nfs_args, &sin);

	/*
	 * Make a ``hostname'' string for the kernel
	 */
#ifndef HOSTNAMESZ
#define	SHORT_MOUNT_NAME
#endif /* HOSTNAMESZ */
#ifdef SHORT_MOUNT_NAME
D 2
	sprintf(fs_hostname, "amd:%d", mypid);
E 2
I 2
	sprintf(fs_hostname, "amd:%d", foreground ? mypid : getppid());
E 2
#else
D 2
	sprintf(fs_hostname, "pid%d@%s:%s", mypid, hostname, dir);
E 2
I 2
	sprintf(fs_hostname, "pid%d@%s:%s", foreground ? mypid : getppid(), hostname, dir);
E 2
#endif /* SHORT_MOUNT_NAME */
	nfs_args.hostname = fs_hostname;
	nfs_args.flags |= NFSMNT_HOSTNAME;
#ifdef HOSTNAMESZ
	/*
	 * Most kernels have a name length restriction.
	 */
	if (strlen(fs_hostname) >= HOSTNAMESZ)
		strcpy(fs_hostname + HOSTNAMESZ - 3, "..");
#endif /* HOSTNAMESZ */

I 6
#ifdef NFSMNT_DUMBTIMR
	nfs_args.flags |= NFSMNT_DUMBTIMR;
	plog(XLOG_INFO, "defeating nfs window computation");
#endif

E 6
	/*
	 * Parse a subset of the standard nfs options.  The
	 * others are probably irrelevant for this application
	 */
	if (nfs_args.timeo = hasmntval(&mnt, "timeo"))
		nfs_args.flags |= NFSMNT_TIMEO;

	if (nfs_args.retrans = hasmntval(&mnt, "retrans"))
		nfs_args.flags |= NFSMNT_RETRANS;

#ifdef NFSMNT_BIODS
	if (nfs_args.biods = hasmntval(&mnt, "biods"))
		nfs_args.flags |= NFSMNT_BIODS;

#endif /* NFSMNT_BIODS */

#if defined(NFSMNT_ACREGMIN) && defined(NFSMNT_ACREGMAX)
	/*
	 * Don't cache attributes - they are changing under
	 * the kernel's feet...
	 */
	nfs_args.acregmin = nfs_args.acregmax = 1;
	nfs_args.flags |= NFSMNT_ACREGMIN|NFSMNT_ACREGMAX;
#endif /* defined(NFSMNT_ACREGMIN) && defined(NFSMNT_ACREGMAX) */
	/*
	 * These two are constructed internally by the calling routine
	 */
	if (hasmntopt(&mnt, MNTOPT_SOFT) != NULL)
		nfs_args.flags |= NFSMNT_SOFT;

#ifdef MNTOPT_INTR
	if (hasmntopt(&mnt, MNTOPT_INTR) != NULL)
		nfs_args.flags |= NFSMNT_INT;
#endif /* MNTOPT_INTR */

	flags = compute_mount_flags(&mnt);
#ifdef ULTRIX_HACK
	nfs_args.gfs_flags = flags;
	flags &= M_RDONLY;
	if (flags & M_RDONLY)
		nfs_args.flags |= NFSMNT_RONLY;
#endif /* ULTRIX_HACK */
	return mount_fs(&mnt, flags, (caddr_t) &nfs_args, retry, type);
}

I 2
static void afs_mkcacheref P((mntfs *mf));
static void afs_mkcacheref(mf)
mntfs *mf;
{
	/*
	 * Build a new map cache for this node, or re-use
	 * an existing cache for the same map.
	 */
	char *cache;
	if (mf->mf_fo && mf->mf_fo->opt_cache)
	  	cache = mf->mf_fo->opt_cache;
	else
	  	cache = "none";
	mf->mf_private = (voidp) mapc_find(mf->mf_info, cache);
	mf->mf_prfree = mapc_free;
}

/*
 * Mount the root...
 */
static int root_mount P((am_node *mp));
static int root_mount(mp)
am_node *mp;
{
	mntfs *mf = mp->am_mnt;
D 3
#ifdef notdef
	/*
	 * Make sure fattr is set up correctly
	 */
	mk_fattr(mp, NFDIR);
#endif
E 3

	mf->mf_mount = strealloc(mf->mf_mount, pid_fsname);
	mf->mf_private = (voidp) mapc_find(mf->mf_info, "");
	mf->mf_prfree = mapc_free;

	return 0;
}

/*
 * Mount a sub-mount
 */
static int afs_mount P((am_node *mp));
E 2
static int afs_mount(mp)
am_node *mp;
{
	mntfs *mf = mp->am_mnt;

I 2
D 3
#ifdef notdef
E 3
E 2
	/*
D 2
	 * There are two cases to consider...
E 2
I 2
D 3
	 * Make sure fattr is set up correctly
E 2
	 */
D 2
	if (mp->am_parent && mp->am_parent->am_parent) {
E 2
I 2
	mk_fattr(mp, NFDIR);
#endif

	/*
E 3
	 * Pseudo-directories are used to provide some structure
	 * to the automounted directories instead
	 * of putting them all in the top-level automount directory.
	 *
	 * Here, just increment the parent's link count.
	 */
	mp->am_parent->am_fattr.nlink++;
	/*
	 * Info field of . means use parent's info field.
	 * Historical - not documented.
	 */
	if (mf->mf_info[0] == '.' && mf->mf_info[1] == '\0')
		mf->mf_info = strealloc(mf->mf_info, mp->am_parent->am_mnt->mf_info);
	/*
	 * Compute prefix:
	 *
	 * If there is an option prefix then use that else
	 * If the parent had a prefix then use that with name
	 *	of this node appended else
	 * Use the name of this node.
	 *
	 * That means if you want no prefix you must say so
	 * in the map.
	 */
	if (mf->mf_fo->opt_pref) {
E 2
		/*
D 2
		 * If this am_node has a parent which is not the root node, in
		 * which case we are supplying a pseudo-directory, in which
		 * case no action is needed.  Pseudo-directories are used to
		 * provide some structure to the automounted directories instead
		 * of putting them all in the top-level automount directory.
E 2
I 2
		 * the prefix specified as an option
E 2
		 */
D 2
		mp->am_parent->am_mnt->mf_fattr.nlink++;
		/*
		 * Info field of . means use parent's info field.
		 */
		if (mf->mf_info[0] == '.' && mf->mf_info[1] == '\0')
			mf->mf_info = strealloc(mf->mf_info, mp->am_parent->am_mnt->mf_info);
		/*
		 * Compute prefix:
		 *
		 * If there is an option prefix then use that else
		 * If the parent had a prefix then use that with name
		 *	of this node appended else
		 * Use the name of this node.
		 *
		 * That means if you want no prefix you must say so
		 * in the map.
		 */
		if (mf->mf_fo->opt_pref) {
			/*
			 * the prefix specified as an option
			 */
			mp->am_pref = strdup(mf->mf_fo->opt_pref);
		} else {
			/*
			 * else the parent's prefix
			 * followed by the name
			 * followed by /
			 */
			char *ppref = mp->am_parent->am_pref;
			if (ppref == 0)
				ppref = "";
			mp->am_pref = str3cat((char *) 0, ppref, mp->am_name, "/");
		}
E 2
I 2
		mp->am_pref = strdup(mf->mf_fo->opt_pref);
E 2
	} else {
		/*
D 2
		 * Otherwise, we are mounting the automounter.  In which case
		 * we need to make sure the mount directory exists, construct
		 * the mount options and call the mount_afs routine.
E 2
I 2
		 * else the parent's prefix
		 * followed by the name
		 * followed by /
E 2
		 */
D 2
		struct stat stb;
		char opts[256];
		int error;
E 2
I 2
		char *ppref = mp->am_parent->am_pref;
		if (ppref == 0)
			ppref = "";
		mp->am_pref = str3cat((char *) 0, ppref, mp->am_name, "/");
	}
E 2

D 2
		/*
		 * Top-level mount - so make
		 * sure the mount point exists
		 * and is a directory.
		 */
		error = mkdirs(mp->am_path, 0555);
		if (error)
			return error;
		mp->am_flags |= AMF_MKPATH;
E 2
I 2
	/*
	 * Attach a map cache
	 */
	afs_mkcacheref(mf);
E 2

D 2
		if (stat(mp->am_path, &stb) < 0) {
			return errno;
		} else if ((stb.st_mode & S_IFMT) != S_IFDIR) {
			plog(XLOG_WARNING, "%s is not a directory", mp->am_path);
			return ENOTDIR;
		}
E 2
I 2
	return 0;
}
E 2

D 2
		mf->mf_mount = strealloc(mf->mf_mount, mp->am_path);
E 2
I 2
/*
 * Mount the top-level
 */
static int toplvl_mount P((am_node *mp));
static int toplvl_mount(mp)
am_node *mp;
{
	mntfs *mf = mp->am_mnt;
	struct stat stb;
	char opts[256];
	int error;
	char *mnttype;
E 2

D 2
		/*
		 * Construct some mount options
		 */
		sprintf(opts,
E 2
I 2
	/*
	 * Mounting the automounter.
	 * Make sure the mount directory exists, construct
	 * the mount options and call the mount_toplvl routine.
	 */

	if (stat(mp->am_path, &stb) < 0) {
		return errno;
	} else if ((stb.st_mode & S_IFMT) != S_IFDIR) {
		plog(XLOG_WARNING, "%s is not a directory", mp->am_path);
		return ENOTDIR;
	}

	if (mf->mf_ops == &toplvl_ops) mnttype = "indirect";
	else if (mf->mf_ops == &dfs_ops) mnttype = "direct";
#ifdef HAS_UNION_FS
	else if (mf->mf_ops == &union_ops) mnttype = "union";
#endif
	else mnttype = "auto";

	/*
	 * Construct some mount options
	 */
	sprintf(opts,
E 2
#ifdef MNTOPT_INTR
D 2
			"%s,%s,%s=%d,%s=%d,%s=%d,%sdirect",
			MNTOPT_INTR,
E 2
I 2
		"%s,%s,%s=%d,%s=%d,%s=%d,%s",
		MNTOPT_INTR,
E 2
#else
D 2
			"%s,%s=%d,%s=%d,%s=%d,%sdirect",
E 2
I 2
		"%s,%s=%d,%s=%d,%s=%d,%s",
E 2
#endif /* MNTOPT_INTR */
D 3
#ifdef AUTOMOUNT_RO
D 2
			MNTOPT_RO,	/* You don't really want this... */
E 2
I 2
		MNTOPT_RO,	/* You don't really want this... */
E 2
#else
E 3
D 2
			"rw",
E 2
I 2
		"rw",
E 2
D 3
#endif /* AUTOMOUNT_RO */
E 3
D 2
			"port", nfs_port,
			"timeo", afs_timeo,
			"retrans", afs_retrans,
			mf->mf_ops == &afs_ops ? "in" : "");
E 2
I 2
		"port", nfs_port,
		"timeo", afs_timeo,
		"retrans", afs_retrans,
		mnttype);
E 2

D 2
		error = mount_afs(mp->am_path, mp->am_name, opts);
		if (error) {
			errno = error;
			plog(XLOG_FATAL, "mount_afs: %m");
			return error;
E 2
I 2
	error = mount_toplvl(mf->mf_mount, opts);
	if (error) {
		errno = error;
		plog(XLOG_FATAL, "mount_toplvl: %m");
		return error;
	}

	return 0;
}

static void toplvl_mounted P((mntfs *mf));
static void toplvl_mounted(mf)
mntfs *mf;
{
	afs_mkcacheref(mf);
}

#ifdef HAS_UNION_FS
/*
 * Create a reference to a union'ed entry
 */
static int create_union_node P((char *dir, voidp arg));
static int create_union_node(dir, arg)
char *dir;
voidp arg;
{
	if (strcmp(dir, "/defaults") != 0) {
		int error = 0;
		(void) toplvl_ops.lookuppn(arg, dir, &error, VLOOK_CREATE);
		if (error > 0) {
			errno = error; /* XXX */
			plog(XLOG_ERROR, "Could not mount %s: %m", dir);
E 2
		}
D 2
		mp->am_name = pid_fsname;
E 2
I 2
		return error;
E 2
	}
I 2
	return 0;
}
E 2

I 2
static void union_mounted P((mntfs *mf));
static void union_mounted(mf)
mntfs *mf;
{
	int i;
	
	afs_mkcacheref(mf);

E 2
	/*
D 2
	 * Build a new map cache for this node, or re-use
	 * an existing cache for the same map.
E 2
I 2
	 * Having made the union mount point,
	 * populate all the entries...
E 2
	 */
D 2
	{ char *cache;
	  if (mf->mf_fo->opt_cache)
	  	cache = mf->mf_fo->opt_cache;
	  else
	  	cache = "none";
	  mf->mf_private = (voidp) mapc_find(mf->mf_info, cache);
	  mf->mf_prfree = mapc_free;
E 2
I 2
	for (i = 0; i <= last_used_map; i++) {
		am_node *mp = exported_ap[i];
		if (mp && mp->am_mnt == mf) {
			/* return value from create_union_node is ignored by mapc_keyiter */
			(void) mapc_keyiter((mnt_map *) mp->am_mnt->mf_private,
				(void (*)P((char*,void*))) create_union_node, mp);
			break;
		}
E 2
	}

D 2
	return 0;
E 2
I 2
#ifdef notdef
	/*
	 * would be nice to flush most of the cache, but we need to
	 * keep the wildcard and /defaults entries...
	 */
	mapc_free(mf->mf_private);
	mf->mf_private = (voidp) mapc_find(mf->mf_info, "inc");
/*	mapc_add_kv(mf->mf_private, strdup("/defaults"),
		strdup("type:=link;opts:=nounmount;sublink:=${key}")); */
#endif
E 2
}
I 2
#endif /* HAS_UNION_FS */
E 2

/*
D 2
 * Unmount an automount node
E 2
I 2
 * Unmount an automount sub-node
E 2
 */
I 2
static int afs_umount P((am_node *mp));
E 2
static int afs_umount(mp)
am_node *mp;
{
I 2
	return 0;
}

/*
 * Unmount a top-level automount node
 */
static int toplvl_umount P((am_node *mp));
static int toplvl_umount(mp)
am_node *mp;
{
E 2
	int error;

I 2
	struct stat stb;
again:
E 2
	/*
D 2
	 * If this is a pseudo-directory then just adjust the link count
	 * in the parent, otherwise call the generic unmount routine
E 2
I 2
	 * The lstat is needed if this mount is type=direct.
	 * When that happens, the kernel cache gets confused
	 * between the underlying type (dir) and the mounted
	 * type (link) and so needs to be re-synced before
	 * the unmount.  This is all because the unmount system
	 * call follows links and so can't actually unmount
	 * a link (stupid!).  It was noted that doing an ls -ld
	 * of the mount point to see why things were not working
	 * actually fixed the problem - so simulate an ls -ld here.
E 2
	 */
D 2
	if (!mp->am_parent) {
		error = 0;
	} else if (mp->am_parent && mp->am_parent->am_parent) {
		--mp->am_parent->am_mnt->mf_fattr.nlink;
		error = 0;
	} else {
		struct stat stb;
again:
		/*
		 * The lstat is needed if this mount is type=direct.
		 * When that happens, the kernel cache gets confused
		 * between the underlying type (dir) and the mounted
		 * type (link) and so needs to be re-synced before
		 * the unmount.  This is all because the unmount system
		 * call follows links and so can't actually unmount
		 * a link (stupid!).  It was noted that doing an ls -ld
		 * of the mount point to see why things were not working
		 * actually fixed the problem - so simulate an ls -ld here.
		 */
		if (lstat(mp->am_path, &stb) < 0) {
E 2
I 2
	if (lstat(mp->am_path, &stb) < 0) {
E 2
#ifdef DEBUG
D 2
			dlog("lstat(%s): %m", mp->am_path);
E 2
I 2
		dlog("lstat(%s): %m", mp->am_path);
E 2
#endif /* DEBUG */
D 2
		}
		error = UMOUNT_FS(mp->am_path);
		if (error == EBUSY) {
			plog(XLOG_WARNING, "afs_unmount retrying %s in 1s", mp->am_path);
			sleep(1);	/* XXX */
			goto again;
		}
E 2
	}
I 2
	error = UMOUNT_FS(mp->am_path);
	if (error == EBUSY) {
		plog(XLOG_WARNING, "afs_unmount retrying %s in 1s", mp->am_path);
		sleep(1);	/* XXX */
		goto again;
	}
E 2

	return error;
}

/*
 * Unmount an automount node
 */
I 2
static void afs_umounted P((am_node *mp));
E 2
static void afs_umounted(mp)
am_node *mp;
{
	/*
	 * If this is a pseudo-directory then just adjust the link count
	 * in the parent, otherwise call the generic unmount routine
	 */
	if (mp->am_parent && mp->am_parent->am_parent)
D 2
		--mp->am_parent->am_mnt->mf_fattr.nlink;
E 2
I 2
		--mp->am_parent->am_fattr.nlink;
E 2
}

/*
 * Mounting a file system may take a significant period of time.  The
 * problem is that if this is done in the main process thread then
 * the entire automounter could be blocked, possibly hanging lots of
 * processes on the system.  Instead we use a continuation scheme to
 * allow mounts to be attempted in a sub-process.  When the sub-process
 * exits we pick up the exit status (by convention a UN*X error number)
 * and continue in a notifier.  The notifier gets handed a data structure
 * and can then determine whether the mount was successful or not.  If
 * not, it updates the data structure and tries again until there are no
 * more ways to try the mount, or some other permanent error occurs.
 * In the mean time no RPC reply is sent, even after the mount is succesful.
 * We rely on the RPC retry mechanism to resend the lookup request which
 * can then be handled.
 */


struct continuation {
	char **ivec;		/* Current mount info */
	am_node *mp;		/* Node we are trying to mount */
	char *key;		/* Map key */
	char *info;		/* Info string */
	char **xivec;		/* Saved strsplit vector */
D 2
	char *opts;		/* Mount options */
E 2
I 2
	char *auto_opts;	/* Automount options */
E 2
	am_opts fs_opts;	/* Filesystem options */
D 2
	char *def_opts;		/* Default options */
E 2
I 2
	char *def_opts;		/* Default automount options */
E 2
	int retry;		/* Try again? */
	int tried;		/* Have we tried any yet? */
	time_t start;		/* Time we started this mount */
	int callout;		/* Callout identifier */
};

I 3
#define	IN_PROGRESS(cp) ((cp)->mp->am_mnt->mf_flags & MFF_MOUNTING)

E 3
/*
 * Discard an old continuation
 */
I 2
static void free_continuation P((struct continuation *cp));
E 2
static void free_continuation(cp)
struct continuation *cp;
{
	if (cp->callout)
		untimeout(cp->callout);
	free((voidp) cp->key);
	free((voidp) cp->xivec);
	free((voidp) cp->info);
D 2
	free((voidp) cp->opts);
E 2
I 2
	free((voidp) cp->auto_opts);
E 2
	free((voidp) cp->def_opts);
	free_opts(&cp->fs_opts);
	free((voidp) cp);
}

static int afs_bgmount P((struct continuation*, int));

/*
 * Discard the underlying mount point and replace
 * with a reference to an error filesystem.
 */
I 2
static void assign_error_mntfs P((am_node *mp));
E 2
static void assign_error_mntfs(mp)
am_node *mp;
{
	if (mp->am_error > 0) {
		/*
		 * Save the old error code
		 */
		int error = mp->am_error;
I 2
		if (error <= 0)
			error = mp->am_mnt->mf_error;
E 2
		/*
		 * Discard the old filesystem
		 */
		free_mntfs(mp->am_mnt);
		/*
		 * Allocate a new error reference
		 */
		mp->am_mnt = new_mntfs();
		/*
		 * Put back the error code
		 */
		mp->am_mnt->mf_error = error;
		mp->am_mnt->mf_flags |= MFF_ERROR;
		/*
		 * Zero the error in the mount point
		 */
		mp->am_error = 0;
	}
}

/*
 * The continuation function.  This is called by
 * the task notifier when a background mount attempt
 * completes.
 */
I 2
static void afs_cont P((int rc, int term, voidp closure));
E 2
static void afs_cont(rc, term, closure)
int rc;
int term;
voidp closure;
{
	struct continuation *cp = (struct continuation *) closure;
	mntfs *mf = cp->mp->am_mnt;

	/*
	 * Definitely not trying to mount at the moment
	 */
	mf->mf_flags &= ~MFF_MOUNTING;
	/*
	 * While we are mounting - try to avoid race conditions
	 */
	new_ttl(cp->mp);

	/*
	 * Wakeup anything waiting for this mount
	 */
	wakeup((voidp) mf);

	/*
	 * Check for termination signal or exit status...
	 */
	if (rc || term) {
I 5
		am_node *xmp;

E 5
		if (term) {
			/*
			 * Not sure what to do for an error code.
			 */
			mf->mf_error = EIO;	/* XXX ? */
			mf->mf_flags |= MFF_ERROR;
			plog(XLOG_ERROR, "mount for %s got signal %d", cp->mp->am_path, term);
		} else {
			/*
			 * Check for exit status...
			 */
			mf->mf_error = rc;
			mf->mf_flags |= MFF_ERROR;
			errno = rc;	/* XXX */
			plog(XLOG_ERROR, "%s: mount (afs_cont): %m", cp->mp->am_path);
		}

		/*
		 * If we get here then that attempt didn't work, so
		 * move the info vector pointer along by one and
		 * call the background mount routine again
		 */
		amd_stats.d_merr++;
		cp->ivec++;
I 5
		xmp = cp->mp;
E 5
		(void) afs_bgmount(cp, 0);
D 5
		assign_error_mntfs(cp->mp);
E 5
I 5
		assign_error_mntfs(xmp);
E 5
	} else {
		/*
		 * The mount worked.
		 */
		am_mounted(cp->mp);
		free_continuation(cp);
	}

	reschedule_timeout_mp();
}

/*
 * Retry a mount
 */
/*ARGSUSED*/
I 2
static void afs_retry P((int rc, int term, voidp closure));
E 2
static void afs_retry(rc, term, closure)
int rc;
int term;
voidp closure;
{
	struct continuation *cp = (struct continuation *) closure;
	int error = 0;

#ifdef DEBUG
	dlog("Commencing retry for mount of %s", cp->mp->am_path);
#endif /* DEBUG */

I 3
	new_ttl(cp->mp);

E 3
	if ((cp->start + ALLOWED_MOUNT_TIME) < clocktime()) {
		/*
		 * The entire mount has timed out.
		 * Set the error code and skip past
		 * all the info vectors so that
		 * afs_bgmount will not have any more
		 * ways to try the mount, so causing
		 * an error.
		 */
		plog(XLOG_INFO, "mount of \"%s\" has timed out", cp->mp->am_path);
		error = ETIMEDOUT;
D 3
		new_ttl(cp->mp);
E 3
		while (*cp->ivec)
			cp->ivec++;
	}

D 3
	(void) afs_bgmount(cp, error);
E 3
I 3
	if (error || !IN_PROGRESS(cp)) {
		(void) afs_bgmount(cp, error);
	}
E 3
	reschedule_timeout_mp();
}

/*
 * Try to mount a file system.  Can be called
 * directly or in a sub-process by run_task
 */
D 2
static int try_mount(mp)
am_node *mp;
E 2
I 2
static int try_mount P((voidp mvp));
static int try_mount(mvp)
voidp mvp;
E 2
{
	/*
	 * Mount it!
	 */
	int error;
I 2
	am_node *mp = (am_node *) mvp;
	mntfs *mf = mp->am_mnt;
E 2

I 2
	/*
	 * If the directory is not yet made and
	 * it needs to be made, then make it!
	 * This may be run in a backgroun process
	 * in which case the flag setting won't be
	 * noticed later - but it is set anyway
	 * just after run_task is called.  It
	 * should probably go away totally...
	 */
	if (!(mf->mf_flags & MFF_MKMNT) && mf->mf_ops->fs_flags & FS_MKMNT) {
		error = mkdirs(mf->mf_mount, 0555);
		if (!error)
			mf->mf_flags |= MFF_MKMNT;
	}

E 2
	error = mount_node(mp);
#ifdef DEBUG
D 2
	if (error) {
E 2
I 2
	if (error > 0) {
E 2
		errno = error;
		dlog("afs call to mount_node failed: %m");
	}
#endif /* DEBUG */
	return error;
}

/*
 * Pick a file system to try mounting and
 * do that in the background if necessary
 *
For each location:
	if it is new -defaults then
		extract and process
		continue;
	fi
	if it is a cut then
		if a location has been tried then
			break;
		fi
		continue;
	fi
	parse mount location
	discard previous mount location if required
	find matching mounted filesystem
	if not applicable then
		this_error = No such file or directory
		continue
	fi
	if the filesystem failed to be mounted then
		this_error = error from filesystem
	elif the filesystem is mounting or unmounting then
		this_error = -1
	elif the fileserver is down then
		this_error = -1
	elif the filesystem is already mounted
		this_error = 0
		break
	fi
	if no error on this mount then
		this_error = initialise mount point
	fi
	if no error on this mount and mount is delayed then
		this_error = -1
	fi
	if this_error < 0 then
		retry = true
	fi
	if no error on this mount then
		make mount point if required
	fi
	if no error on this mount then
		if mount in background then
			run mount in background
			return -1
		else
			this_error = mount in foreground
		fi
	fi
	if an error occured on this mount then
		update stats
		save error in mount point
	fi
endfor
 */

I 2
static int afs_bgmount P((struct continuation *cp, int mpe));
E 2
static int afs_bgmount(cp, mpe)
struct continuation *cp;
int mpe;
{
	mntfs *mf = cp->mp->am_mnt;	/* Current mntfs */
	mntfs *mf_retry = 0;		/* First mntfs which needed retrying */
	int this_error = -1;		/* Per-mount error */
	int hard_error = -1;
	int mp_error = mpe;

	/*
	 * Try to mount each location.
	 * At the end:
	 * hard_error == 0 indicates something was mounted.
	 * hard_error > 0 indicates everything failed with a hard error
	 * hard_error < 0 indicates nothing could be mounted now
	 */
	for (; this_error && *cp->ivec; cp->ivec++) {
		am_ops *p;
		am_node *mp = cp->mp;
		char *link_dir;
		int dont_retry;

		if (hard_error < 0)
			hard_error = this_error;

		this_error = -1;

		if (**cp->ivec == '-') {
			/*
			 * Pick up new defaults
			 */
D 2
			if (cp->opts && *cp->opts)
				cp->def_opts = str3cat(cp->def_opts, cp->opts, ";", *cp->ivec+1);
E 2
I 2
			if (cp->auto_opts && *cp->auto_opts)
				cp->def_opts = str3cat(cp->def_opts, cp->auto_opts, ";", *cp->ivec+1);
E 2
			else
				cp->def_opts = strealloc(cp->def_opts, *cp->ivec+1);
#ifdef DEBUG
			dlog("Setting def_opts to \"%s\"", cp->def_opts);
#endif /* DEBUG */
			continue;
		}

		/*
		 * If a mount has been attempted, and we find
		 * a cut then don't try any more locations.
		 */
		if (strcmp(*cp->ivec, "/") == 0 || strcmp(*cp->ivec, "||") == 0) {
			if (cp->tried) {
#ifdef DEBUG
				dlog("Cut: not trying any more locations for %s",
					mp->am_path);
#endif /* DEBUG */
				break;
			}
			continue;
		}

#ifdef SUNOS4_COMPAT
I 3
#ifdef nomore
E 3
		/*
		 * By default, you only get this bit on SunOS4.
		 * If you want this anyway, then define SUNOS4_COMPAT
		 * in the relevant "os-blah.h" file.
		 *
		 * We make the observation that if the local key line contains
		 * no '=' signs then either it is sick, or it is a SunOS4-style
		 * "host:fs[:link]" line.  In the latter case the am_opts field
		 * is also assumed to be in old-style, so you can't mix & match.
		 * You can use ${} expansions for the fs and link bits though...
		 *
		 * Actually, this doesn't really cover all the possibilities for
		 * the latest SunOS automounter and it is debatable whether there
		 * is any point bothering.
		 */
		if (strchr(*cp->ivec, '=') == 0)
			p = sunos4_match(&cp->fs_opts, *cp->ivec, cp->def_opts, mp->am_path, cp->key, mp->am_parent->am_mnt->mf_info);
		else
I 3
#endif
E 3
#endif /* SUNOS4_COMPAT */
			p = ops_match(&cp->fs_opts, *cp->ivec, cp->def_opts, mp->am_path, cp->key, mp->am_parent->am_mnt->mf_info);

		/*
		 * Find a mounted filesystem for this node.
		 */
		mp->am_mnt = mf = realloc_mntfs(mf, p, &cp->fs_opts, cp->fs_opts.opt_fs,
D 2
						cp->fs_opts.fs_mtab, cp->opts);
E 2
I 2
D 4
						cp->fs_opts.fs_mtab, cp->auto_opts, cp->fs_opts.opt_opts);
E 4
I 4
			cp->fs_opts.fs_mtab, cp->auto_opts, cp->fs_opts.opt_opts, cp->fs_opts.opt_remopts);
E 4
E 2

		p = mf->mf_ops;
#ifdef DEBUG
		dlog("Got a hit with %s", p->fs_type);
#endif /* DEBUG */
		/*
		 * Note whether this is a real mount attempt
		 */
		if (p == &efs_ops) {
			plog(XLOG_MAP, "Map entry %s for %s failed to match", *cp->ivec, mp->am_path);
			if (this_error <= 0)
				this_error = ENOENT;
			continue;
		} else {
			if (cp->fs_opts.fs_mtab) {
				plog(XLOG_MAP, "Trying mount of %s on %s fstype %s",
					cp->fs_opts.fs_mtab, mp->am_path, p->fs_type);
			}
			cp->tried = TRUE;
		}

		this_error = 0;
		dont_retry = FALSE;

		if (mp->am_link) {
			free(mp->am_link);
			mp->am_link = 0;
		}

		link_dir = mf->mf_fo->opt_sublink;

		if (link_dir && *link_dir) {
			if (*link_dir == '/') {
				mp->am_link = strdup(link_dir);
			} else {
				mp->am_link = str3cat((char *) 0,
					mf->mf_fo->opt_fs, "/", link_dir);
I 3
				normalize_slash(mp->am_link);
E 3
			}
		}

		if (mf->mf_error > 0) {
			this_error = mf->mf_error;
		} else if (mf->mf_flags & (MFF_MOUNTING|MFF_UNMOUNTING)) {
			/*
			 * Still mounting - retry later
			 */
#ifdef DEBUG
			dlog("Duplicate pending mount fstype %s", p->fs_type);
#endif /* DEBUG */
			this_error = -1;
		} else if (FSRV_ISDOWN(mf->mf_server)) {
			/*
			 * Would just mount from the same place
			 * as a hung mount - so give up
			 */
#ifdef DEBUG
			dlog("%s is already hung - giving up", mf->mf_mount);
#endif /* DEBUG */
			mp_error = EWOULDBLOCK;
			dont_retry = TRUE;
			this_error = -1;
		} else if (mf->mf_flags & MFF_MOUNTED) {
#ifdef DEBUG
			dlog("duplicate mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */
I 2
			/*
			 * Just call mounted()
			 */
			am_mounted(mp);

E 2
			this_error = 0;
D 2
			new_ttl(mp);
E 2
			break;
		}

		/*
		 * Will usually need to play around with the mount nodes
		 * file attribute structure.  This must be done here.
I 2
		 * Try and get things initialised, even if the fileserver
		 * is not known to be up.  In the common case this will
		 * progress things faster.
E 2
		 */
		if (!this_error) {
			/*
D 2
			 * Fill in attribute fields
E 2
I 2
			 * Fill in attribute fields.
E 2
			 */
D 2
			mf->mf_fattr.type = NFLNK;
			mf->mf_fattr.mode = NFSMODE_LNK | 0777;
			mf->mf_fattr.nlink = 1;
			mf->mf_fattr.size = MAXPATHLEN / 4;	/* Conservative */
			mf->mf_fattr.fileid = mp->am_gen;
E 2
I 2
			if (mf->mf_ops->fs_flags & FS_DIRECTORY)
				mk_fattr(mp, NFDIR);
			else
				mk_fattr(mp, NFLNK);
E 2

I 2
			mp->am_fattr.fileid = mp->am_gen;

E 2
			if (p->fs_init)
				this_error = (*p->fs_init)(mf);
		}

I 2
		/*
		 * Make sure the fileserver is UP before doing any more work
		 */
		if (!FSRV_ISUP(mf->mf_server)) {
#ifdef DEBUG
			dlog("waiting for server %s to become available", mf->mf_server->fs_host);
#endif
			this_error =  -1;
		}

E 2
		if (!this_error && mf->mf_fo->opt_delay) {
			/*
			 * If there is a delay timer on the mount
			 * then don't try to mount if the timer
			 * has not expired.
			 */
			int i = atoi(mf->mf_fo->opt_delay);
D 2
			if (i > 0 && (cp->start + i) < clocktime()) {
E 2
I 2
			if (i > 0 && clocktime() < (cp->start + i)) {
E 2
#ifdef DEBUG
D 2
				dlog("Mount of %s delayed by %ds", mf->mf_mount, i);
E 2
I 2
				dlog("Mount of %s delayed by %ds", mf->mf_mount, i - clocktime() + cp->start);
E 2
#endif /* DEBUG */
				this_error = -1;
			}
		}

		if (this_error < 0 && !dont_retry) {
			if (!mf_retry)
				mf_retry = dup_mntfs(mf);
			cp->retry = TRUE;
		}

D 2
		if (!this_error) {
			/*
			 * If the directory is not yet made and
			 * it needs to be made, then make it!
			 */
			 if (!(mf->mf_flags & MFF_MKMNT) &&
				 	p->fs_flags & FS_MKMNT) {
				this_error = mkdirs(mf->mf_mount, 0555);
				if (!this_error)
					mf->mf_flags |= MFF_MKMNT;
			}
		}

E 2
		if (!this_error)
		if (p->fs_flags & FS_MBACKGROUND) {
			mf->mf_flags |= MFF_MOUNTING;	/*XXX*/
#ifdef DEBUG
D 2
			dlog("backgrounding mount of \"%s\"", mf->mf_info);
E 2
I 2
			dlog("backgrounding mount of \"%s\"", mf->mf_mount);
E 2
#endif /* DEBUG */
			if (cp->callout) {
				untimeout(cp->callout);
				cp->callout = 0;
			}
			run_task(try_mount, (voidp) mp, afs_cont, (voidp) cp);
I 2
			mf->mf_flags |= MFF_MKMNT;	/* XXX */
E 2
			if (mf_retry) free_mntfs(mf_retry);
			return -1;
		} else {
#ifdef DEBUG
			dlog("foreground mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */
D 2
			this_error = try_mount(mp);
E 2
I 2
			this_error = try_mount((voidp) mp);
I 3
			if (this_error < 0) {
				if (!mf_retry)
					mf_retry = dup_mntfs(mf);
				cp->retry = TRUE;
			}
E 3
E 2
		}

		if (this_error >= 0) {
			if (this_error > 0) {
				amd_stats.d_merr++;
				if (mf != mf_retry) {
					mf->mf_error = this_error;
					mf->mf_flags |= MFF_ERROR;
				}
			}
			/*
			 * Wakeup anything waiting for this mount
			 */
			wakeup((voidp) mf);
		}
	}

	if (this_error && cp->retry) {
		free_mntfs(mf);
		mf = cp->mp->am_mnt = mf_retry;
		/*
		 * Not retrying again (so far)
		 */
		cp->retry = FALSE;
		cp->tried = FALSE;
		/*
		 * Start at the beginning.
		 * Rewind the location vector and
		 * reset the default options.
		 */
		cp->ivec = cp->xivec;
D 2
		cp->def_opts = strealloc(cp->def_opts, cp->opts);
E 2
I 2
		cp->def_opts = strealloc(cp->def_opts, cp->auto_opts);
E 2
		/*
		 * Arrange that afs_bgmount is called
		 * after anything else happens.
		 */
#ifdef DEBUG
		dlog("Arranging to retry mount of %s", cp->mp->am_path);
#endif /* DEBUG */
		sched_task(afs_retry, (voidp) cp, (voidp) mf);
		if (cp->callout)
			untimeout(cp->callout);
		cp->callout = timeout(RETRY_INTERVAL, wakeup, (voidp) mf);

		cp->mp->am_ttl = clocktime() + RETRY_INTERVAL;

		/*
		 * Not done yet - so don't return anything
		 */
		return -1;
	}

I 2
D 3
	if (hard_error < 0 || this_error != 0)
E 3
I 3
	if (hard_error < 0 || this_error == 0)
E 3
		hard_error = this_error;

E 2
	/*
	 * Discard handle on duff filesystem.
	 * This should never happen since it
	 * should be caught by the case above.
	 */
	if (mf_retry) {
D 2
		plog(XLOG_ERROR, "discarding a retry mntfs for %s", mf_retry->mf_mount);
E 2
I 2
		if (hard_error)
			plog(XLOG_ERROR, "discarding a retry mntfs for %s", mf_retry->mf_mount);
E 2
		free_mntfs(mf_retry);
	}

D 2
	if (hard_error < 0 || !this_error)
		hard_error = this_error;

E 2
	/*
	 * If we get here, then either the mount succeeded or
	 * there is no more mount information available.
	 */
	if (hard_error < 0 && mp_error)
		hard_error = cp->mp->am_error = mp_error;
	if (hard_error > 0) {
		/*
		 * Set a small(ish) timeout on an error node if
		 * the error was not a time out.
		 */
		switch (hard_error) {
		case ETIMEDOUT:
		case EWOULDBLOCK:
			cp->mp->am_timeo = 5;
			break;
		default:
			cp->mp->am_timeo = 17;
			break;
		}
D 4
		cp->mp->am_timeo_w = 0;
E 4
I 4
		new_ttl(cp->mp);
E 4
	}

	/*
	 * Make sure that the error value in the mntfs has a
	 * reasonable value.
	 */
	if (mf->mf_error < 0) {
		mf->mf_error = hard_error;
		if (hard_error)
			mf->mf_flags |= MFF_ERROR;
	}

	/*
	 * In any case we don't need the continuation any more
	 */
	free_continuation(cp);

	return hard_error;
}

/*
 * Automount interface to RPC lookup routine
 */
I 2
static am_node *afs_lookuppn P((am_node *mp, char *fname, int *error_return, int op));
E 2
static am_node *afs_lookuppn(mp, fname, error_return, op)
am_node *mp;
char *fname;
int *error_return;
int op;
{
#define ereturn(x) { *error_return = x; return 0; }

	/*
	 * Find the corresponding entry and return
	 * the file handle for it.
	 */
	am_node *ap, *new_mp, *ap_hung;
	char *info;			/* Mount info - where to get the file system */
	char **ivec, **xivec;		/* Split version of info */
D 2
	char *opts;			/* Mount options */
E 2
I 2
	char *auto_opts;		/* Automount options */
E 2
	int error = 0;			/* Error so far */
	char path_name[MAXPATHLEN];	/* General path name buffer */
	char *pfname;			/* Path for database lookup */
	struct continuation *cp;	/* Continuation structure if we need to mount */
	int in_progress = 0;		/* # of (un)mount in progress */
	char *dflts;
	mntfs *mf;

#ifdef DEBUG
	dlog("in afs_lookuppn");
#endif /* DEBUG */

	/*
	 * If the server is shutting down
	 * then don't return information
	 * about the mount point.
	 */
	if (amd_state == Finishing) {
#ifdef DEBUG
D 2
		dlog("%s/%s mount ignored - going down",
			mp->am_path, fname);
E 2
I 2
		if ((mf = mp->am_mnt) == 0 || mf->mf_ops == &dfs_ops)
			dlog("%s mount ignored - going down", fname);
		else
			dlog("%s/%s mount ignored - going down", mp->am_path, fname);
E 2
#endif /* DEBUG */
		ereturn(ENOENT);
	}

	/*
	 * Handle special case of "." and ".."
	 */
	if (fname[0] == '.') {
		if (fname[1] == '\0')
			return mp;	/* "." is the current node */
		if (fname[1] == '.' && fname[2] == '\0') {
			if (mp->am_parent) {
#ifdef DEBUG
				dlog(".. in %s gives %s", mp->am_path, mp->am_parent->am_path);
#endif /* DEBUG */
				return mp->am_parent;	/* ".." is the parent node */
			}
			ereturn(ESTALE);
		}
	}

	/*
	 * Check for valid key name.
	 * If it is invalid then pretend it doesn't exist.
	 */
	if (!valid_key(fname)) {
		plog(XLOG_WARNING, "Key \"%s\" contains a disallowed character", fname);
		ereturn(ENOENT);
	}

	/*
	 * Expand key name.
	 * fname is now a private copy.
	 */
	fname = expand_key(fname);

	for (ap_hung = 0, ap = mp->am_child; ap; ap = ap->am_osib) {
		/*
		 * Otherwise search children of this node
		 */
		if (FSTREQ(ap->am_name, fname)) {
			mf = ap->am_mnt;
			if (ap->am_error) {
				error = ap->am_error;
				continue;
			}

			/*
			 * If the error code is undefined then it must be
			 * in progress.
			 */
			if (mf->mf_error < 0)
				goto in_progrss;

			/*
			 * Check for a hung node
			 */
			if (FSRV_ISDOWN(mf->mf_server)) {
I 5
#ifdef DEBUG
				dlog("server hung");
#endif /* DEBUG */
				error = ap->am_error;
E 5
				ap_hung = ap;
				continue;
			}

			/*
			 * If there was a previous error with this node
			 * then return that error code.
			 */
			if (mf->mf_flags & MFF_ERROR) {
				error = mf->mf_error;
				continue;
			}

			if (!(mf->mf_flags & MFF_MOUNTED) /*|| (mf->mf_flags & MFF_UNMOUNTING)*/) {
in_progrss:
				/*
				 * If the fs is not mounted or it is unmounting then there
				 * is a background (un)mount in progress.  In this case
				 * we just drop the RPC request (return nil) and
				 * wait for a retry, by which time the (un)mount may
				 * have completed.
				 */
#ifdef DEBUG
				dlog("ignoring mount of %s in %s -- in progress",
					fname, mf->mf_mount);
#endif /* DEBUG */
				in_progress++;
				continue;
			}

			/*
			 * Otherwise we have a hit: return the current mount point.
			 */
#ifdef DEBUG
			dlog("matched %s in %s", fname, ap->am_path);
#endif /* DEBUG */
			free(fname);
			return ap;
		}
	}

	if (in_progress) {
#ifdef DEBUG
		dlog("Waiting while %d mount(s) in progress", in_progress);
#endif /* DEBUG */
		free(fname);
		ereturn(-1);
	}

	/*
	 * If an error occured then return it.
	 */
	if (error) {
#ifdef DEBUG
		errno = error; /* XXX */
		dlog("Returning error: %m", error);
#endif /* DEBUG */
		free(fname);
		ereturn(error);
	}

	/*
	 * If doing a delete then don't create again!
	 */
	switch (op) {
	case VLOOK_DELETE:
		ereturn(ENOENT);
		break;

	case VLOOK_CREATE:
		break;

	default:
		plog(XLOG_FATAL, "Unknown op to afs_lookuppn: 0x%x", op);
		ereturn(EINVAL);
		break;
	}

	/*
	 * If the server is going down then just return,
	 * don't try to mount any more file systems
	 */
	if ((int)amd_state >= (int)Finishing) {
#ifdef DEBUG
		dlog("not found - server going down anyway");
#endif /* DEBUG */
		free(fname);
		ereturn(ENOENT);
	}

	/*
	 * If we get there then this is a reference to an,
	 * as yet, unknown name so we need to search the mount
	 * map for it.
	 */
	if (mp->am_pref) {
		sprintf(path_name, "%s%s", mp->am_pref, fname);
		pfname = path_name;
	} else {
		pfname = fname;
	}

	mf = mp->am_mnt;

#ifdef DEBUG
	dlog("will search map info in %s to find %s", mf->mf_info, pfname);
#endif /* DEBUG */
	/*
	 * Consult the oracle for some mount information.
	 * info is malloc'ed and belongs to this routine.
	 * It ends up being free'd in free_continuation().
	 *
	 * Note that this may return -1 indicating that information
	 * is not yet available.
	 */
	error = mapc_search((mnt_map*) mf->mf_private, pfname, &info);
	if (error) {
D 2
		plog(XLOG_MAP, "No map entry for %s", pfname);
E 2
I 2
		if (error > 0)
			plog(XLOG_MAP, "No map entry for %s", pfname);
		else
			plog(XLOG_MAP, "Waiting on map entry for %s", pfname);
E 2
		free(fname);
		ereturn(error);
	}

#ifdef DEBUG
	dlog("mount info is %s", info);
#endif /* DEBUG */

	/*
	 * Split info into an argument vector.
	 * The vector is malloc'ed and belongs to
	 * this routine.  It is free'd in free_continuation()
	 */
D 2
	xivec = ivec = strsplit(info, '\"');
E 2
I 2
	xivec = ivec = strsplit(info, ' ', '\"');
E 2

	/*
	 * Default error code...
	 */
	if (ap_hung)
		error = EWOULDBLOCK;
	else
		error = ENOENT;

	/*
	 * Allocate a new map
	 */
	new_mp = exported_ap_alloc();
	if (new_mp == 0) {
		free((voidp) xivec);
		free((voidp) info);
		free((voidp) fname);
		ereturn(ENOSPC);
	}

D 2
	if (mf->mf_opts)
		opts = mf->mf_opts;
E 2
I 2
	if (mf->mf_auto)
		auto_opts = mf->mf_auto;
E 2
	else
D 2
		opts = "";
E 2
I 2
		auto_opts = "";
E 2

D 2
	opts = strdup(opts);
E 2
I 2
	auto_opts = strdup(auto_opts);
E 2

#ifdef DEBUG
	dlog("searching for /defaults entry");
#endif /* DEBUG */
	if (mapc_search((mnt_map*) mf->mf_private, "/defaults", &dflts) == 0) {
	  	char *dfl;
		char **rvec;
#ifdef DEBUG
		dlog("/defaults gave %s", dflts);
#endif /* DEBUG */
		if (*dflts == '-')
			dfl = dflts+1;
		else
			dfl = dflts;

		/*
		 * Chop the defaults up
		 */
D 2
		rvec = strsplit(dfl, '\"');
E 2
I 2
		rvec = strsplit(dfl, ' ', '\"');
E 2
		/*
		 * Extract first value
		 */
		dfl = rvec[0];

		/*
D 5
		 * Log error if there were other values
E 5
I 5
		 * If there were any values at all...
E 5
		 */
D 5
		if (rvec[1]) {
E 5
I 5
		if (dfl) {
			/*
			 * Log error if there were other values
			 */
			if (rvec[1]) {
E 5
#ifdef DEBUG
D 5
			dlog("/defaults chopped into %s", dfl);
E 5
I 5
				dlog("/defaults chopped into %s", dfl);
E 5
#endif /* DEBUG */
D 5
			plog(XLOG_USER, "More than a single value for /defaults in %s", mf->mf_info);
		}
E 5
I 5
				plog(XLOG_USER, "More than a single value for /defaults in %s", mf->mf_info);
			}
E 5

D 5
		/*
		 * Don't need info vector any more
		 */
		free((voidp) rvec);

		/*
		 * If there were any values at all...
		 */
		if (dfl) {
E 5
			/*
			 * Prepend to existing defaults if they exist,
			 * otherwise just use these defaults.
			 */
D 2
			if (*opts && *dfl) {
				char *nopts = (char *) xmalloc(strlen(opts)+strlen(dfl)+2);
				sprintf(nopts, "%s;%s", dfl, opts);
				free(opts);
				opts = nopts;
E 2
I 2
			if (*auto_opts && *dfl) {
				char *nopts = (char *) xmalloc(strlen(auto_opts)+strlen(dfl)+2);
				sprintf(nopts, "%s;%s", dfl, auto_opts);
				free(auto_opts);
				auto_opts = nopts;
E 2
			} else if (*dfl) {
D 2
				opts = strealloc(opts, dfl);
E 2
I 2
				auto_opts = strealloc(auto_opts, dfl);
E 2
			}
		}
		free(dflts);
I 5
		/*
		 * Don't need info vector any more
		 */
		free((voidp) rvec);
E 5
	}

	/*
	 * Fill it in
	 */
	init_map(new_mp, fname);

	/*
	 * Put it in the table
	 */
	insert_am(new_mp, mp);

	/*
	 * Fill in some other fields,
D 2
	 * path and mount point
E 2
I 2
	 * path and mount point.
	 *
	 * bugfix: do not prepend old am_path if direct map
	 *         <wls@astro.umd.edu> William Sebok
E 2
	 */
D 2
	new_mp->am_path = str3cat(new_mp->am_path, mp->am_path, *fname == '/' ? "" : "/", fname);
E 2
I 2
	new_mp->am_path = str3cat(new_mp->am_path,
		mf->mf_ops == &dfs_ops ? "" : mp->am_path,
		*fname == '/' ? "" : "/", fname);
E 2

#ifdef DEBUG
	dlog("setting path to %s", new_mp->am_path);
#endif /* DEBUG */

	/*
	 * Take private copy of pfname
	 */
	pfname = strdup(pfname);

	/*
	 * Construct a continuation
	 */
	cp = ALLOC(continuation);
	cp->mp = new_mp;
	cp->xivec = xivec;
	cp->ivec = ivec;
	cp->info = info;
	cp->key = pfname;
D 2
	cp->opts = opts;
E 2
I 2
	cp->auto_opts = auto_opts;
E 2
	cp->retry = FALSE;
	cp->tried = FALSE;
	cp->start = clocktime();
D 2
	cp->def_opts = strdup(opts);
E 2
I 2
	cp->def_opts = strdup(auto_opts);
E 2
	bzero((voidp) &cp->fs_opts, sizeof(cp->fs_opts));

	/*
	 * Try and mount the file system
	 * If this succeeds immediately (possible
	 * for a ufs file system) then return
	 * the attributes, otherwise just
	 * return an error.
	 */
	error = afs_bgmount(cp, error);
	reschedule_timeout_mp();
	if (!error) {
		free(fname);
		return new_mp;
	}

D 5
	assign_error_mntfs(cp->mp);
E 5
I 5
	if (error && (cp->mp->am_mnt->mf_ops == &efs_ops))
		cp->mp->am_error = error;
E 5

I 5
	assign_error_mntfs(new_mp);

E 5
	free(fname);

	ereturn(error);
#undef ereturn
}

/*
 * Locate next node in sibling list which is mounted
 * and is not an error node.
 */
I 2
static am_node *next_nonerror_node P((am_node *xp));
E 2
static am_node *next_nonerror_node(xp)
am_node *xp;
{
	mntfs *mf;

	/*
	 * Bug report (7/12/89) from Rein Tollevik <rein@ifi.uio.no>
	 * Fixes a race condition when mounting direct automounts.
	 * Also fixes a problem when doing a readdir on a directory
	 * containing hung automounts.
	 */
	while (xp &&
	       (!(mf = xp->am_mnt) ||			/* No mounted filesystem */
	        mf->mf_error != 0 ||			/* There was a mntfs error */
	        xp->am_error != 0 ||			/* There was a mount error */
	        !(mf->mf_flags & MFF_MOUNTED) ||	/* The fs is not mounted */
	        (mf->mf_server->fs_flags & FSF_DOWN))	/* The fs may be down */
		)
		xp = xp->am_osib;

	return xp;
}

D 2
static int afs_readdir(mp, cookie, dp, ep)
E 2
I 2
static int afs_readdir P((am_node *mp, nfscookie cookie, struct dirlist *dp, struct entry *ep, int count));
static int afs_readdir(mp, cookie, dp, ep, count)
E 2
am_node *mp;
nfscookie cookie;
struct dirlist *dp;
struct entry *ep;
I 2
int count;
E 2
{
	unsigned int gen = *(unsigned int*) cookie;
	am_node *xp;

	dp->eof = FALSE;

	if (gen == 0) {
		/*
		 * In the default instance (which is used to
		 * start a search) we return "." and "..".
		 *
		 * This assumes that the count is big enough
		 * to allow both "." and ".." to be returned in
		 * a single packet.  If it isn't (which would
		 * be fairly unbelievable) then tough.
		 */
#ifdef DEBUG
		dlog("default search");
#endif /* DEBUG */
I 5
		/*
		 * Check for enough room.  This is extremely
		 * approximate but is more than enough space.
		 * Really need 2 times:
		 * 	4byte fileid
		 * 	4byte cookie
		 * 	4byte name length
		 * 	4byte name
		 * plus the dirlist structure
		 */
		if (count <
			(2 * (2 * (sizeof(*ep) + sizeof("..") + 4)
					+ sizeof(*dp))))
			return EINVAL;

E 5
		xp = next_nonerror_node(mp->am_child);
		dp->entries = ep;

		/* construct "." */
		ep[0].fileid = mp->am_gen;
		ep[0].name = ".";
		ep[0].nextentry = &ep[1];
		*(unsigned int *) ep[0].cookie = 0;

		/* construct ".." */
		if (mp->am_parent)
			ep[1].fileid = mp->am_parent->am_gen;
		else
			ep[1].fileid = mp->am_gen;
		ep[1].name = "..";
		ep[1].nextentry = 0;
		*(unsigned int *) ep[1].cookie =
			xp ? xp->am_gen : ~(unsigned int)0;

		if (!xp) dp->eof = TRUE;
		return 0;
	}

#ifdef DEBUG
	dlog("real child");
#endif /* DEBUG */

	if (gen == ~(unsigned int)0) {
#ifdef DEBUG
		dlog("End of readdir in %s", mp->am_path);
#endif /* DEBUG */
		dp->eof = TRUE;
		dp->entries = 0;
		return 0;
	}

	xp = mp->am_child;
	while (xp && xp->am_gen != gen)
		xp = xp->am_osib;

	if (xp) {
D 2
		am_node *xp_next = next_nonerror_node(xp->am_osib);
E 2
I 2
		int nbytes = count / 2;		/* conservative */
		int todo = MAX_READDIR_ENTRIES;
		dp->entries = ep;
		do {
			am_node *xp_next = next_nonerror_node(xp->am_osib);
E 2

D 2
		if (xp_next) {
			*(unsigned int *) ep->cookie = xp_next->am_gen;
		} else {
			*(unsigned int *) ep->cookie = ~(unsigned int)0;
			dp->eof = TRUE;
		}
E 2
I 2
			if (xp_next) {
				*(unsigned int *) ep->cookie = xp_next->am_gen;
			} else {
				*(unsigned int *) ep->cookie = ~(unsigned int)0;
				dp->eof = TRUE;
			}
E 2

D 2
		ep->fileid = xp->am_gen;
		ep->name = xp->am_name;
E 2
I 2
			ep->fileid = xp->am_gen;
			ep->name = xp->am_name;
			nbytes -= sizeof(*ep) + strlen(xp->am_name) + 1;
E 2

I 2
			xp = xp_next;

			if (nbytes > 0 && !dp->eof && todo > 1) {
				ep->nextentry = ep + 1;
				ep++;
				--todo;
			} else {
				todo = 0;
			}
		} while (todo > 0);

E 2
		ep->nextentry = 0;
D 2
		dp->entries = ep;
E 2

		return 0;
	}

	return ESTALE;

}

I 2
static am_node *dfs_readlink P((am_node *mp, int *error_return));
E 2
static am_node *dfs_readlink(mp, error_return)
am_node *mp;
int *error_return;
{
	am_node *xp;
	int rc = 0;

	xp = next_nonerror_node(mp->am_child);
D 2
	if (!xp)
E 2
I 2
	if (!xp) {
		if (!mp->am_mnt->mf_private)
			afs_mkcacheref(mp->am_mnt);	/* XXX */
E 2
		xp = afs_lookuppn(mp, mp->am_path+1, &rc, VLOOK_CREATE);
I 2
	}
E 2

	if (xp) {
		new_ttl(xp);	/* (7/12/89) from Rein Tollevik */
		return xp;
	}
	if (amd_state == Finishing)
		rc = ENOENT;
	*error_return = rc;
	return 0;
}

/*
 * Ops structure
 */
I 2
am_ops root_ops = {
	"root",
	0, /* root_match */
	0, /* root_init */
	root_mount,
	0,
	afs_umount,
	0,
	afs_lookuppn,
	afs_readdir,
	0, /* root_readlink */
	0, /* root_mounted */
	0, /* root_umounted */
	find_afs_srvr,
	FS_NOTIMEOUT|FS_AMQINFO|FS_DIRECTORY
};

E 2
am_ops afs_ops = {
	"auto",
	afs_match,
D 2
	afs_init,
E 2
I 2
	0, /* afs_init */
E 2
	afs_mount,
I 2
	0,
E 2
	afs_umount,
I 2
	0,
E 2
	afs_lookuppn,
	afs_readdir,
	0, /* afs_readlink */
	0, /* afs_mounted */
	afs_umounted,
	find_afs_srvr,
D 2
	FS_NOTIMEOUT|FS_UBACKGROUND|FS_AMQINFO
E 2
I 2
	FS_AMQINFO|FS_DIRECTORY
E 2
};

I 2
am_ops toplvl_ops = {
	"toplvl",
	afs_match,
	0, /* afs_init */
	toplvl_mount,
	0,
	toplvl_umount,
	0,
	afs_lookuppn,
	afs_readdir,
	0, /* toplvl_readlink */
	toplvl_mounted,
	0, /* toplvl_umounted */
	find_afs_srvr,
	FS_MKMNT|FS_NOTIMEOUT|FS_BACKGROUND|FS_AMQINFO|FS_DIRECTORY
};

E 2
am_ops dfs_ops = {
	"direct",
	afs_match,
	0, /* dfs_init */
D 2
	afs_mount,
	afs_umount,
E 2
I 2
	toplvl_mount,
	0,
	toplvl_umount,
	0,
E 2
	efs_lookuppn,
	efs_readdir,
	dfs_readlink,
D 2
	0, /* afs_mounted */
	afs_umounted,
E 2
I 2
	toplvl_mounted,
	0, /* afs_umounted */
E 2
	find_afs_srvr,
D 2
	FS_NOTIMEOUT|FS_UBACKGROUND|FS_AMQINFO
E 2
I 2
	FS_MKMNT|FS_NOTIMEOUT|FS_BACKGROUND|FS_AMQINFO
E 2
};
I 2

#ifdef HAS_UNION_FS
am_ops union_ops = {
	"union",
	afs_match,
	0, /* afs_init */
	toplvl_mount,
	0,
	toplvl_umount,
	0,
	afs_lookuppn,
	afs_readdir,
	0, /* toplvl_readlink */
	union_mounted,
	0, /* toplvl_umounted */
	find_afs_srvr,
	FS_MKMNT|FS_NOTIMEOUT|FS_BACKGROUND|FS_AMQINFO|FS_DIRECTORY
};
#endif /* HAS_UNION_FS */
E 2
E 1
