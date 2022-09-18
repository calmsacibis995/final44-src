h54064
s 00002/00002/00653
d D 8.1 93/06/06 11:39:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00072/00001/00583
d D 5.5 92/05/31 10:42:18 pendry 5 4
c code refresh
e
s 00006/00012/00578
d D 5.4 92/02/09 08:48:07 pendry 4 3
c merge in new release
e
s 00009/00007/00581
d D 5.3 91/05/12 15:55:14 pendry 3 2
c checkpoint for network tape
e
s 00111/00034/00477
d D 5.2 91/03/17 13:33:08 pendry 2 1
c from amd5.3 alpha11
e
s 00511/00000/00000
d D 5.1 90/06/29 12:01:03 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: host_ops.c,v 5.2 90/06/23 22:19:26 jsp Rel $
E 2
I 2
D 3
 * $Id: host_ops.c,v 5.2.1.3 91/03/03 20:42:25 jsp Alpha $
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
 * $Id: host_ops.c,v 5.2.1.6 91/05/07 22:17:53 jsp Alpha $
E 4
I 4
D 5
 * $Id: host_ops.c,v 5.2.2.1 1992/02/09 15:08:24 jsp beta $
E 5
I 5
 * $Id: host_ops.c,v 5.2.2.2 1992/05/31 16:36:08 jsp Exp $
E 5
E 4
 *
E 3
 */

#include "am.h"

#ifdef HAS_HOST

#include "mount.h"
#include <sys/stat.h>

/*
D 2
 * NFS host file system
E 2
I 2
 * NFS host file system.
 * Mounts all exported filesystems from a given host.
 * This has now degenerated into a mess but will not
 * be rewritten.  Amd 6 will support the abstractions
 * needed to make this work correctly.
E 2
 */

/*
 * Define HOST_RPC_UDP to use dgram instead of stream RPC.
 * Datagrams are generally much faster.
 */
D 4
#define	HOST_RPC_UDP
E 4
I 4
/*#define	HOST_RPC_UDP*/
E 4

/*
 * Define HOST_MKDIRS to make Amd automatically try
 * to create the mount points.
 */
#define HOST_MKDIRS

/*
I 2
 * Determine the mount point
 */
#define MAKE_MNTPT(mntpt, ex, mf) { \
			if (strcmp((ex)->ex_dir, "/") == 0) \
				strcpy((mntpt), (mf)->mf_mount); \
			else \
				sprintf((mntpt), "%s%s", (mf)->mf_mount, (ex)->ex_dir); \
}

/*
E 2
 * Execute needs the same as NFS plus a helper command
 */
D 2
static int host_match(fo)
E 2
I 2
static char *host_match P((am_opts *fo));
static char *host_match(fo)
E 2
am_opts *fo;
{
#ifdef HOST_EXEC
	if (!host_helper) {
		plog(XLOG_USER, "No host helper command given");
		return FALSE;
	}
#endif /* HOST_EXEC */

	/*
	 * Make sure rfs is specified to keep nfs_match happy...
	 */
	if (!fo->opt_rfs)
		fo->opt_rfs = "/";

D 2
	if (!(*nfs_ops.fs_match)(fo))
		return FALSE;

	return TRUE;
E 2
I 2
	
	return (*nfs_ops.fs_match)(fo);
E 2
}

static int host_init(mf)
mntfs *mf;
{
	if (strchr(mf->mf_info, ':') == 0)
		return ENOENT;
	return 0;
}

/*
 * Two implementations:
 * HOST_EXEC gets you the external version.  The program specified with
 * the -h option is called.  The external program is not published...
 * roll your own.
 *
 * Otherwise you get the native version.  Faster but makes the program
 * bigger.
 */

#ifndef HOST_EXEC

static bool_t
xdr_pri_free(xdr_args, args_ptr)
xdrproc_t xdr_args;
caddr_t args_ptr;
{
	XDR xdr;
	xdr.x_op = XDR_FREE;
	return ((*xdr_args)(&xdr, args_ptr));
}

I 2
static int do_mount P((fhstatus *fhp, char *dir, char *fs_name, char *opts, mntfs *mf));
E 2
static int do_mount(fhp, dir, fs_name, opts, mf)
fhstatus *fhp;
char *dir;
char *fs_name;
char *opts;
mntfs *mf;
{
	struct stat stb;
#ifdef DEBUG
	dlog("host: mounting fs %s on %s\n", fs_name, dir);
#endif /* DEBUG */
#ifdef HOST_MKDIRS
	(void) mkdirs(dir, 0555);
#endif /* HOST_MKDIRS */
	if (stat(dir, &stb) < 0 || (stb.st_mode & S_IFMT) != S_IFDIR) {
		plog(XLOG_ERROR, "No mount point for %s - skipping", dir);
		return ENOENT;
	}

	return mount_nfs_fh(fhp, dir, fs_name, opts, mf);
}

D 2
static sortfun(a, b)
E 2
I 2
static int sortfun P((exports *a, exports *b));
static int sortfun(a, b)
E 2
exports *a,*b;
{
	return strcmp((*a)->ex_dir, (*b)->ex_dir);
}

/*
 * Get filehandle
 */
I 2
static int fetch_fhandle P((CLIENT *client, char *dir, fhstatus *fhp));
E 2
static int fetch_fhandle(client, dir, fhp)
CLIENT *client;
char *dir;
fhstatus *fhp;
{
	struct timeval tv;
	enum clnt_stat clnt_stat;

	/*
	 * Pick a number, any number...
	 */
D 3
	tv.tv_sec = 10;
E 3
I 3
	tv.tv_sec = 20;
E 3
	tv.tv_usec = 0;

#ifdef DEBUG
	dlog("Fetching fhandle for %s", dir);
#endif /* DEBUG */
	/*
	 * Call the mount daemon on the remote host to
	 * get the filehandle.
	 */
	clnt_stat = clnt_call(client, MOUNTPROC_MNT, xdr_dirpath, &dir, xdr_fhstatus, fhp, tv);
	if (clnt_stat != RPC_SUCCESS) {
		extern char *clnt_sperrno();
		char *msg = clnt_sperrno(clnt_stat);
		plog(XLOG_ERROR, "mountd rpc failed: %s", msg);
		return EIO;
	}
	/*
	 * Check status of filehandle
	 */
	if (fhp->fhs_status) {
#ifdef DEBUG
		errno = fhp->fhs_status;
		dlog("fhandle fetch failed: %m");
#endif /* DEBUG */
		return fhp->fhs_status;
	}
	return 0;
}

/*
I 2
 * Scan mount table to see if something already mounted
 */
static int already_mounted P((mntlist *mlist, char*dir));
static int already_mounted(mlist, dir)
mntlist *mlist;
char *dir;
{
	mntlist *ml;

	for (ml = mlist; ml; ml = ml->mnext)
		if (strcmp(ml->mnt->mnt_dir, dir) == 0)
			return 1;
	return 0;
}

/*
E 2
 * Mount the export tree from a host
 */
D 2
static int host_mount(mp)
am_node *mp;
E 2
I 2
static int host_fmount P((mntfs *mf));
static int host_fmount(mf)
mntfs *mf;
E 2
{
	struct timeval tv2;
	CLIENT *client;
	enum clnt_stat clnt_stat;
	int n_export;
D 2
	int j;
E 2
I 2
	int j, k;
E 2
	exports exlist = 0, ex;
	exports *ep = 0;
	fhstatus *fp = 0;
D 2
	mntfs *mf = mp->am_mnt;
E 2
	char *host = mf->mf_server->fs_host;
	int error = 0;
	struct sockaddr_in sin;
	int sock = RPC_ANYSOCK;
	int ok = FALSE;
D 2
	
E 2
I 2
	mntlist *mlist;
	char fs_name[MAXPATHLEN], *rfs_dir;
	char mntpt[MAXPATHLEN];
D 4

E 2
#ifdef HOST_RPC_UDP
E 4
	struct timeval tv;
	tv.tv_sec = 10; tv.tv_usec = 0;
D 4
#endif /* HOST_RPC_UDP */
E 4

	/*
I 2
	 * Read the mount list
	 */
	mlist = read_mtab(mf->mf_mount);

	/*
	 * Unlock the mount list
	 */
	unlock_mntlist();

	/*
E 2
	 * Take a copy of the server address
	 */
	sin = *mf->mf_server->fs_ip;

	/*
	 * Zero out the port - make sure we recompute
	 */
	sin.sin_port = 0;
	/*
D 4
	 * Make a client end-point
E 4
I 4
	 * Make a client end-point.
	 * Try TCP first
E 4
	 */
D 4
#ifdef HOST_RPC_UDP
	if ((client = clntudp_create(&sin, MOUNTPROG, MOUNTVERS, tv, &sock)) == NULL)
#else
	if ((client = clnttcp_create(&sin, MOUNTPROG, MOUNTVERS, &sock, 0, 0)) == NULL)
#endif /* HOST_RPC_UDP */
	{
E 4
I 4
	if ((client = clnttcp_create(&sin, MOUNTPROG, MOUNTVERS, &sock, 0, 0)) == NULL &&
		(client = clntudp_create(&sin, MOUNTPROG, MOUNTVERS, tv, &sock)) == NULL) {
E 4
		plog(XLOG_ERROR, "Failed to make rpc connection to mountd on %s", host);
		error = EIO;
		goto out;
	}

	if (!nfs_auth) {
D 3
		nfs_auth = authunix_create_default();
		if (!nfs_auth) {
			error = ENOBUFS;
E 3
I 3
		error = make_nfs_auth();
		if (error)
E 3
			goto out;
D 3
		}
E 3
	}

	client->cl_auth = nfs_auth;

#ifdef DEBUG
	dlog("Fetching export list from %s", host);
#endif /* DEBUG */

	/*
	 * Fetch the export list
	 */
	tv2.tv_sec = 10; tv2.tv_usec = 0;
	clnt_stat = clnt_call(client, MOUNTPROC_EXPORT, xdr_void, 0, xdr_exports, &exlist, tv2);
	if (clnt_stat != RPC_SUCCESS) {
		/*clnt_perror(client, "rpc");*/
		error = EIO;
		goto out;
	}

	/*
	 * Figure out how many exports were returned
	 */
	for (n_export = 0, ex = exlist; ex; ex = ex->ex_next) {
		/*printf("export %s\n", ex->ex_dir);*/
		n_export++;
	}
#ifdef DEBUG
	/*dlog("%d exports returned\n", n_export);*/
#endif /* DEBUG */

	/*
	 * Allocate an array of pointers into the list
D 2
	 * so that they can be sorted.
E 2
I 2
	 * so that they can be sorted.  If the filesystem
	 * is already mounted then ignore it.
E 2
	 */
	ep = (exports *) xmalloc(n_export * sizeof(exports));
D 2
	for (j = 0, ex = exlist; ex; ex = ex->ex_next, j++)
		ep[j] = ex;
E 2
I 2
	for (j = 0, ex = exlist; ex; ex = ex->ex_next) {
		MAKE_MNTPT(mntpt, ex, mf);
		if (!already_mounted(mlist, mntpt))
			ep[j++] = ex;
	}
	n_export = j;
E 2

	/*
	 * Sort into order.
	 * This way the mounts are done in order down the tree,
	 * instead of any random order returned by the mount
	 * daemon (the protocol doesn't specify...).
	 */
	qsort(ep, n_export, sizeof(exports), sortfun);

	/*
	 * Allocate an array of filehandles
	 */
	fp = (fhstatus *) xmalloc(n_export * sizeof(fhstatus));

	/*
	 * Try to obtain filehandles for each directory.
	 * If a fetch fails then just zero out the array
	 * reference but discard the error.
	 */
D 2
	for (j = 0; j < n_export; j++) {
		if (error = fetch_fhandle(client, ep[j]->ex_dir, &fp[j]))
E 2
I 2
	for (j = k = 0; j < n_export; j++) {
		/* Check and avoid a duplicated export entry */
		if (j > k && ep[k] && strcmp(ep[j]->ex_dir, ep[k]->ex_dir) == 0) {
#ifdef DEBUG
			dlog("avoiding dup fhandle requested for %s", ep[j]->ex_dir);
#endif
E 2
			ep[j] = 0;
I 2
		} else {
			k = j;
			if (error = fetch_fhandle(client, ep[j]->ex_dir, &fp[j]))
				ep[j] = 0;
		}
E 2
	}

	/*
	 * Mount each filesystem for which we have a filehandle.
	 * If any of the mounts succeed then mark "ok" and return
	 * error code 0 at the end.  If they all fail then return
	 * the last error code.
	 */
I 2
	strncpy(fs_name, mf->mf_info, sizeof(fs_name));
	if ((rfs_dir = strchr(fs_name, ':')) == (char *) 0) {
		plog(XLOG_FATAL, "host_fmount: mf_info has no colon");
		error = EINVAL;
		goto out;
	}
	++rfs_dir;
E 2
	for (j = 0; j < n_export; j++) {
		ex = ep[j];
		if (ex) {
D 2
			char fs_name[MAXPATHLEN];
			char mntpt[MAXPATHLEN];
			sprintf(fs_name, "%s:%s", host, ex->ex_dir);
			if (strcmp(ex->ex_dir, "/") == 0)
				strcpy(mntpt, mf->mf_mount);
			else
				sprintf(mntpt, "%s%s", mf->mf_mount, ex->ex_dir);
			error = do_mount(&fp[j], mntpt, fs_name, mf->mf_fo->opt_opts, mf);
			if (!error)
E 2
I 2
			strcpy(rfs_dir, ex->ex_dir);
			MAKE_MNTPT(mntpt, ex, mf);
			if (do_mount(&fp[j], mntpt, fs_name, mf->mf_mopts, mf) == 0)
E 2
				ok = TRUE;
		}
	}

	/*
	 * Clean up and exit
	 */
out:
I 2
	discard_mntlist(mlist);
E 2
	if (ep)
		free(ep);
	if (fp)
		free(fp);
	if (client)
		clnt_destroy(client);
	if (exlist)
		xdr_pri_free(xdr_exports, &exlist);
	if (ok)
		return 0;
	return error;
}

/*
 * Return true if pref is a directory prefix of dir.
 *
 * TODO:
 * Does not work if pref is "/".
 */
I 2
static int directory_prefix P((char *pref, char *dir));
E 2
static int directory_prefix(pref, dir)
char *pref;
char *dir;
{
	int len = strlen(pref);
	if (strncmp(pref, dir, len) != 0)
		return FALSE;
	if (dir[len] == '/' || dir[len] == '\0')
		return TRUE;
	return FALSE;
}

/*
 * Unmount a mount tree
 */
D 2
static int host_umount(mp)
am_node *mp;
E 2
I 2
static int host_fumount P((mntfs *mf));
static int host_fumount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;
E 2
	mntlist *ml, *mprev;
	int xerror = 0;

	/*
	 * Read the mount list
	 */
	mntlist *mlist = read_mtab(mf->mf_mount);

	/*
	 * Unlock the mount list
	 */
	unlock_mntlist();

	/*
	 * Reverse list...
	 */
	ml = mlist;
	mprev = 0;
	while (ml) {
		mntlist *ml2 = ml->mnext;
		ml->mnext = mprev;
		mprev = ml;
		ml = ml2;
	}
	mlist = mprev;

	/*
	 * Unmount all filesystems...
	 */
D 2
	for (ml = mlist; ml; ml = ml->mnext) {
E 2
I 2
	for (ml = mlist; ml && !xerror; ml = ml->mnext) {
E 2
		char *dir = ml->mnt->mnt_dir;
		if (directory_prefix(mf->mf_mount, dir)) {
			int error;
#ifdef DEBUG
			dlog("host: unmounts %s", dir);
#endif /* DEBUG */
			/*
			 * Unmount "dir"
			 */
			error = UMOUNT_FS(dir);
			/*
			 * Keep track of errors
			 */
			if (error) {
				if (!xerror)
					xerror = error;
				if (error != EBUSY) {
					errno = error;
					plog("Tree unmount of %s failed: %m", ml->mnt->mnt_dir);
				}
			} else {
#ifdef HOST_MKDIRS
				(void) rmdirs(dir);
#endif /* HOST_MKDIRS */
			}
		}
	}

	/*
	 * Throw away mount list
	 */
	discard_mntlist(mlist);

I 2
	/*
	 * Try to remount, except when we are shutting down.
	 */
	if (xerror && amd_state != Finishing) {
		xerror = host_fmount(mf);
		if (!xerror) {
I 3
			/*
			 * Don't log this - it's usually too verbose
E 3
			plog(XLOG_INFO, "Remounted host %s", mf->mf_info);
I 3
			 */
E 3
			xerror = EBUSY;
		}
	}
E 2
	return xerror;
}

I 5
/*
 * Tell mountd we're done.
 * This is not quite right, because we may still
 * have other filesystems mounted, but the existing
 * mountd protocol is badly broken anyway.
 */
static void host_umounted(mp)
am_node *mp;
{
#ifdef INFORM_MOUNTD
	mntfs *mf = mp->am_mnt;
	char *host;
	CLIENT *client;
	enum clnt_stat clnt_stat;
	struct sockaddr_in sin;
	int sock = RPC_ANYSOCK;
	struct timeval tv;
	tv.tv_sec = 10; tv.tv_usec = 0;

	if (mf->mf_error || mf->mf_refc > 1 || ! mf->mf_server)
		return;

	host = mf->mf_server->fs_host;
	sin = *mf->mf_server->fs_ip;

	/*
	 * Zero out the port - make sure we recompute
	 */
	sin.sin_port = 0;
	/*
	 * Make a client end-point.
	 * Try TCP first
	 */
	if ((client = clnttcp_create(&sin, MOUNTPROG, MOUNTVERS, &sock, 0, 0)) == NULL &&
		(client = clntudp_create(&sin, MOUNTPROG, MOUNTVERS, tv, &sock)) == NULL) {
		plog(XLOG_ERROR, "Failed to make rpc connection to mountd on %s", host);
		goto out;
	}

	if (!nfs_auth) {
		if (make_nfs_auth())
			goto out;
	}

	client->cl_auth = nfs_auth;

#ifdef DEBUG
	dlog("Unmounting all from %s", host);
#endif /* DEBUG */

	clnt_stat = clnt_call(client, MOUNTPROC_UMNTALL, xdr_void, 0, xdr_void, 0, tv);
	if (clnt_stat != RPC_SUCCESS && clnt_stat != RPC_SYSTEMERROR) {
		/* RPC_SYSTEMERROR seems to be returned for no good reason ...*/
		extern char *clnt_sperrno();
		char *msg = clnt_sperrno(clnt_stat);
		plog(XLOG_ERROR, "unmount all from %s rpc failed: %s", host, msg, clnt_stat);
		goto out;
	}

out:
	if (client)
		clnt_destroy(client);

#endif /* INFORM_MOUNTD */
}


E 5
#else /* HOST_EXEC */

I 2
static int host_exec P((char*op, char*host, char*fs, char*opts));
E 2
static int host_exec(op, host, fs, opts)
char *op;
char *host;
char *fs;
char *opts;
{
	int error;
	char *argv[7];

	/*
	 * Build arg vector
	 */
	argv[0] = host_helper;
	argv[1] = host_helper;
	argv[2] = op;
	argv[3] = host;
	argv[4] = fs;
	argv[5] = opts && *opts ? opts : "rw,default";
	argv[6] = 0;

	/*
	 * Put stdout to stderr
	 */
	(void) fclose(stdout);
	(void) dup(fileno(logfp));
	if (fileno(logfp) != fileno(stderr)) {
		(void) fclose(stderr);
		(void) dup(fileno(logfp));
	}
	/*
	 * Try the exec
	 */
#ifdef DEBUG
	Debug(D_FULL) {
		char **cp = argv;
		plog(XLOG_DEBUG, "executing (un)mount command...");
		while (*cp) {
	  		plog(XLOG_DEBUG, "arg[%d] = '%s'", cp-argv, *cp);
			cp++;
		}
	}
#endif /* DEBUG */
	if (argv[0] == 0 || argv[1] == 0) {
		errno = EINVAL;
		plog(XLOG_USER, "1st/2nd args missing to (un)mount program");
	} else {
		(void) execv(argv[0], argv+1);
	}
	/*
	 * Save error number
	 */
	error = errno;
	plog(XLOG_ERROR, "exec %s failed: %m", argv[0]);

	/*
	 * Return error
	 */
	return error;
}

I 2
static int host_mount P((am_node *mp));
E 2
static int host_mount(mp)
am_node *mp;
{
	mntfs *mf = mp->am_mnt;

D 2
	return host_exec("mount", mf->mf_server->fs_host, mf->mf_mount, mf->mf_fo->opt_opts);
E 2
I 2
	return host_exec("mount", mf->mf_server->fs_host, mf->mf_mount, mf->mf_opts);
E 2
}

I 2
static int host_umount P((am_node *mp));
E 2
static int host_umount(mp)
am_node *mp;
{
	mntfs *mf = mp->am_mnt;

	return host_exec("unmount", mf->mf_server->fs_host, mf->mf_mount, "xxx");
}

#endif /* HOST_EXEC */

/*
 * Ops structure
 */
am_ops host_ops = {
	"host",
	host_match,
	host_init,
D 2
	host_mount,
	host_umount,
E 2
I 2
	auto_fmount,
	host_fmount,
	auto_fumount,
	host_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* host_readlink */
	0, /* host_mounted */
I 5
#ifdef HOST_EXEC
E 5
	0, /* host_umounted */
I 5
#else
	host_umounted,
#endif
E 5
	find_nfs_srvr,
	FS_MKMNT|FS_BACKGROUND|FS_AMQINFO
};

#endif /* HAS_HOST */
E 1
