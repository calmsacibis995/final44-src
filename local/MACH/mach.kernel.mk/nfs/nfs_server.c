/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	nfs_server.c,v $
 * Revision 2.13  89/10/03  19:26:18  rpd
 * 	Merged with NeXT.  Summary:
 * 	Fixed rfs_setattr to handle file extension properly.
 * 	Use vn_rdwr instead of VOP_RDWR/VOP_BREAD, so in NBC systems
 * 	VM caching will happen on NFS servers.
 * 	[89/10/02  15:54:59  rpd]
 * 
 * Revision 2.12  89/08/09  09:13:32  jsb
 * 	Added missing test in handle_server_link.
 * 	[89/08/08  09:46:32  jsb]
 * 
 * Revision 2.11  89/08/02  08:04:27  jsb
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	Use VOP_FREEFID (vnode-dependent macro) in place of freefid.
 * 	[89/07/31  16:19:48  jsb]
 * 
 * Revision 2.10  89/06/03  15:36:47  jsb
 * 	Moved all AFS gateway support to afs/nfs_gateway.c. Conditionalized
 * 	out nfs_svc under MACH_AFS since it has been replaced by afs_xnfs_svc.
 * 	Brought back VOP_BREAD-using code in rfs_read.  Picked up fix to
 * 	rfs_create from gm0w to set vnode type to regular file when no other
 * 	type is specified. Condensed history.
 * 
 * 	Condensed history:
 * 	[89/06/02  14:14:38  jsb]
 * 
 *	Define EREMOTE as ENFSREMOTE if necessary. Change rfs_readdir
 *	so that memory allocated is released all at once rather than in
 *	chunks. First pass at AFS gateway support.
 *	Disabled call to BOP_BREAD because of problems with sun ethernet
 *	interfaces and with afs. Added use of new inode macros (gm0w).
 *
 * 28-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach.
 */ 
/* @(#)nfs_server.c	1.10 87/09/11 3.2/4.3NFSSRC */

#define NFSSERVER
#include <mach_afs.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/auth.h>
#include <rpc/auth_unix.h>
#include <rpc/svc.h>
#include <rpc/xdr.h>
#include <nfs/nfs.h>
#include <sys/mbuf.h>

#ifndef	EREMOTE
#define EREMOTE		ENFSREMOTE
#endif	EREMOTE

extern struct vnodeops nfs_vnodeops;
/*
 * rpc service program version range supported
 */
#define VERSIONMIN	2
#define VERSIONMAX	2

/*
 * Returns true iff filesystem for a given fsid is exported read-only
 */
#define rdonly(vp)	(((vp)->v_vfsp->vfs_flag & VFS_EXPORTED) && \
			 ((vp)->v_vfsp->vfs_exflags & EX_RDONLY))

struct vnode	*fhtovp();
struct file	*getsock();
void		svcerr_progvers();
void		rfs_dispatch();

#ifdef	NFSDEBUG
extern int nfsdebug;
#endif

struct {
	int	ncalls;		/* number of calls received */
	int	nbadcalls;	/* calls that failed */
	int	reqs[32];	/* count for each request */
} svstat;

#if	MACH_AFS
/*
 *  Replaced by afs_xnfs_svc in afs/nfs_gateway.c
 */
#else	MACH_AFS
/*
 * NFS Server system call.
 * Does all of the work of running a NFS server.
 * sock is the fd of an open UDP socket.
 */
nfs_svc()
{
	struct a {
		int     sock;
	} *uap = (struct a *)u.u_ap;
	struct vnode	*rdir;
	struct vnode	*cdir;
	struct socket   *so;
	struct file	*fp;
	SVCXPRT *xprt;
	u_long vers;
	int	error;
 
	fp = getsock(uap->sock);
	if (fp == 0) {
		u.u_error = EBADF;
		return;
	}
	so = (struct socket *)fp->f_data;

	/*
	 *	  Allocate extra space for this socket, to minimize
	 *	lost requests for NFS.  We don't want everyone to do
	 *	this, so do it here, rather than in udp_usrreq().
	 */

	error = soreserve(so, 18000, 18000 + 2 *(sizeof(struct sockaddr)));
	if (error)	{
		u.u_error = error;
		return;
	}
	 
	/*
	 * Be sure that rdir (the server's root vnode) is set.
	 * Save the current directory and restore it again when
	 * the call terminates.  rfs_lookup uses u.u_cdir for lookupname.
	 */
	rdir = ITOV(u.u_rdir);
	cdir = ITOV(u.u_cdir);
	if (ITOV(u.u_rdir) == (struct vnode *)0) {
		u.u_rdir = u.u_cdir;
	}
	xprt = svckudp_create(so, NFS_PORT);
	for (vers = VERSIONMIN; vers <= VERSIONMAX; vers++) {
		(void) svc_register(xprt, NFS_PROGRAM, vers, rfs_dispatch,
		    FALSE);
	}
	if (setjmp(&u.u_qsave)) {
		for (vers = VERSIONMIN; vers <= VERSIONMAX; vers++) {
			svc_unregister(NFS_PROGRAM, vers);
		}
		SVC_DESTROY(xprt);
		u.u_error = EINTR;
	} else {
		svc_run(xprt);  /* never returns */
	}
	u.u_rdir = VTOI(rdir);
	u.u_cdir = VTOI(cdir);
}
#endif	MACH_AFS


/*
 * Get file handle system call.
 * Takes open file descriptor and returns a file handle for it.
 */
nfs_getfh()
{
	register struct a {
		int	fdes;
		fhandle_t	*fhp;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	fhandle_t fh;
	struct vnode *vp;

	if (!suser()) {
		return;
	}
	fp = getf(uap->fdes);
	if (fp == NULL) {
		return;
	}
	vp = (struct vnode *)fp->f_data;
	u.u_error = makefh(&fh, vp);
	if (!u.u_error) {
		u.u_error =
		    copyout((caddr_t)&fh, (caddr_t)uap->fhp, sizeof(fh));
	}
	return;
}

	
/*
 * These are the interface routines for the server side of the
 * Networked File System.  See the NFS protocol specification
 * for a description of this interface.
 */


#include <nfs/rnode.h>

/*
 * Get file attributes.
 * Returns the current attributes of the file with the given fhandle.
 */
int
rfs_getattr(fhp, ns)
	fhandle_t *fhp;
	register struct nfsattrstat *ns;
{
	int error;
	register struct vnode *vp;
	struct vattr va;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_getattr fh %x %x %d\n",
	    fhp->fh_fsid.val[0], fhp->fh_fsid.val[1], fhp->fh_len);
#endif
	vp = fhtovp(fhp);
	if (vp == NULL) {
		ns->ns_status = NFSERR_STALE;
		return;
	}
	error = VOP_GETATTR(vp, &va, u.u_cred);
	if (!error) {
		vattr_to_nattr(&va, &ns->ns_attr);
	}
	ns->ns_status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_getattr: returning %d\n", error);
#endif
}

/*
 * Set file attributes.
 * Sets the attributes of the file with the given fhandle.  Returns
 * the new attributes.
 */
int
rfs_setattr(args, ns)
	struct nfssaargs *args;
	register struct nfsattrstat *ns;
{
	int error;
	register struct vnode *vp;
	struct vattr va;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_setattr fh %x %x %d\n",
	    args->saa_fh.fh_fsid.val[0], args->saa_fh.fh_fsid.val[1],
	    args->saa_fh.fh_len);
#endif
	vp = fhtovp(&args->saa_fh);
	if (vp == NULL) {
		ns->ns_status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else {
		sattr_to_vattr(&args->saa_sa, &va);
		error = 0;
		/*
		 *  Handle case where we are extending a file via setattr.
		 *  The case we have to watch out for is when there are no
		 *  blocks currently allocated to the file.
		 *  For now, just invoke VOP_RDWR to write a single zero
		 *  at the end of the file.
		 */
		if ((vp->v_mode&VFMT) == VREG && va.va_size != (u_long)-1) {
			struct vattr tva;
			char zero = 0;

			/* get current attributes */
			error = VOP_GETATTR(vp, &tva, u.u_cred);
			if (!error && va.va_size > tva.va_size) {
				/* need to extend the file */
				error = vn_rdwr(UIO_WRITE, vp, &zero, 1,
						va.va_size - 1, UIO_SYSSPACE,
						IO_SYNC, 0);
				ILOCK(VTOI(vp));
				iupdat(VTOI(vp), TRUE);
				IUNLOCK(VTOI(vp));
			}
		}
		if (!error) {
			error = VOP_SETATTR(vp, &va, u.u_cred);
		}
		if (!error) {
			error = VOP_GETATTR(vp, &va, u.u_cred);
			if (!error) {
				vattr_to_nattr(&va, &ns->ns_attr);
			}
		}
	}
	ns->ns_status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_setattr: returning %d\n", error);
#endif
}

/*
 * Directory lookup.
 * Returns an fhandle and file attributes for file name in a directory.
 */
int
rfs_lookup(da, dr)
	struct nfsdiropargs *da;
	register struct  nfsdiropres *dr;
{
	int error;
	register struct vnode *dvp;
	struct vnode *vp;
	struct vattr va;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_lookup %s fh %x %x %x %d\n",
	    da->da_name, da->da_fhandle.fh_fsid.val[0],
	    da->da_fhandle.fh_fsid.val[1], da->da_fhandle.fh_len);
#endif
	dvp = fhtovp(&da->da_fhandle);
	if (dvp == NULL) {
		dr->dr_status = NFSERR_STALE;
		return;
	}

	/*
	 * do lookup.
	 */
	error = VOP_LOOKUP(dvp, da->da_name, &vp, u.u_cred);
	if (error) {
		vp = (struct vnode *)0;
	} else {
		error = VOP_GETATTR(vp, &va, u.u_cred);
		if (!error) {
			error = handle_server_link(dvp, &vp, &va);
		}
		if (!error) {
			vattr_to_nattr(&va, &dr->dr_attr);
			error = makefh(&dr->dr_fhandle, vp);
		}
	}
	dr->dr_status = puterrno(error);
	if (vp) {
		VN_RELE(vp);
	}
	VN_RELE(dvp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_lookup: returning %d\n", error);
#endif
}

/*
 * Read symbolic link.
 * Returns the string in the symbolic link at the given fhandle.
 */
int
rfs_readlink(fhp, rl)
	fhandle_t *fhp;
	register struct nfsrdlnres *rl;
{
	int error;
	struct iovec iov;
	struct uio uio;
	struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_readlink fh %x %x %d\n",
	    fhp->fh_fsid.val[0], fhp->fh_fsid.val[1], fhp->fh_len);
#endif
	vp = fhtovp(fhp);
	if (vp == NULL) {
		rl->rl_status = NFSERR_STALE;
		return;
	}

	/*
	 * Allocate data for pathname.  This will be freed by rfs_rlfree.
	 */
	ZALLOC(nfs_path_zone, rl->rl_data, char *);
	bzero(rl->rl_data, (u_int)NFS_MAXPATHLEN);
	/*
	 * Set up io vector to read sym link data
	 */
	iov.iov_base = rl->rl_data;
	iov.iov_len = NFS_MAXPATHLEN;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_seg = UIO_SYSSPACE;
	uio.uio_offset = 0;
	uio.uio_resid = NFS_MAXPATHLEN;

	/*
	 * read link
	 */
	error = VOP_READLINK(vp, &uio, u.u_cred);

	/*
	 * Clean up
	 */
	if (error) {	
		ZFREE(nfs_path_zone, rl->rl_data);
		rl->rl_count = 0;
		rl->rl_data = NULL;
	} else {
		rl->rl_count = NFS_MAXPATHLEN - uio.uio_resid;
	}
	rl->rl_status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_readlink: returning '%s' %d\n",
	    rl->rl_data, error);
#endif
}

/*
 * Free data allocated by rfs_readlink
 */
rfs_rlfree(rl)
	struct nfsrdlnres *rl;
{
	if (rl->rl_data) {
		ZFREE(nfs_path_zone, rl->rl_data);
	}
}

/*
 * Read data.
 * Returns some data read from the file at the given fhandle.
 */
int
rfs_read(ra, rr)
	struct nfsreadargs *ra;
	register struct nfsrdresult *rr;
{
	int error;
	struct vnode *vp;
	struct vattr va;
	int resid;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_read %d from fh %x %x %d\n",
	    ra->ra_count, ra->ra_fhandle.fh_fsid.val[0],
	    ra->ra_fhandle.fh_fsid.val[1], ra->ra_fhandle.fh_len);
#endif
	rr->rr_data = NULL;
	rr->rr_count = 0;
	vp = fhtovp(&ra->ra_fhandle);
	if (vp == NULL) {
		rr->rr_status = NFSERR_STALE;
		return;
	}
	if (!INODE_TYPE(vp,REG)) {
		printf("rfs_read: attempt to read from non-file\n");
		error = EISDIR;
	} else {
		error = VOP_GETATTR(vp, &va, u.u_cred);
	}
	if (error) {
		goto bad;
	}
	/*
	 * This is a kludge to allow reading of files created
	 * with no read permission.  The owner of the file
	 * is always allowed to read it.
	 */
	if (u.u_uid != va.va_uid) {
		error = VOP_ACCESS(vp, VREAD, u.u_cred);
		if (error) {
			/*
			 * Exec is the same as read over the net because
			 * of demand loading.
			 */
			error = VOP_ACCESS(vp, VEXEC, u.u_cred);
		}
		if (error) {
			goto bad;
		}
	}

	rr->rr_bp = (struct buf *) 0;
			
	/*
	 * Allocate space for data.  This will be freed by xdr_rdresult
	 * when it is called with x_op = XDR_FREE.
	 */
	rr->rr_kalloc_size = ra->ra_count + sizeof(u_int);
	rr->rr_data = kalloc(rr->rr_kalloc_size);

	error = vn_rdwr(UIO_READ, vp, rr->rr_data, ra->ra_count, ra->ra_offset,
			UIO_SYSSPACE, IO_SYNC, &resid);
	if (error) {
		goto bad;
	}
	vattr_to_nattr(&va, &rr->rr_attr);
	rr->rr_count = ra->ra_count - resid;
bad:
	if (error && rr->rr_data != NULL) {
		kfree(rr->rr_data, rr->rr_kalloc_size);
		rr->rr_data = NULL;
		rr->rr_count = 0;
	}
done:
	rr->rr_status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_read returning %d, count = %d\n",
	    error, rr->rr_count);
#endif
}

/*
 * Free data allocated by rfs_read.
 */
rfs_rdfree(rr)
	struct nfsrdresult *rr;
{
	if (rr->rr_bp == 0 && rr->rr_data) {
		kfree(rr->rr_data, rr->rr_kalloc_size);
	}
}

/*
 * Write data to file.
 * Returns attributes of a file after writing some data to it.
 */
int
rfs_write(wa, ns)
	struct nfswriteargs *wa;
	struct nfsattrstat *ns;
{
	register int error;
	register struct vnode *vp;
	struct vattr va;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_write: %d bytes fh %x %x %d\n",
	    wa->wa_count, wa->wa_fhandle.fh_fsid.val[0],
	    wa->wa_fhandle.fh_fsid.val[1], wa->wa_fhandle.fh_len);
#endif
	vp = fhtovp(&wa->wa_fhandle);
	if (vp == NULL) {
		ns->ns_status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else if (!INODE_TYPE(vp,REG)) {
		printf("rfs_read: attempt to write to non-file\n");
		error = EISDIR;
	} else {
		error = VOP_GETATTR(vp, &va, u.u_cred);
	}
	if (!error) {
		if (u.u_uid != va.va_uid) {
			/*
			 * This is a kludge to allow writes of files created
			 * with read only permission.  The owner of the file
			 * is always allowed to write it.
			 */
			error = VOP_ACCESS(vp, VWRITE, u.u_cred);
		}
		if (!error) {
			error = vn_rdwr(UIO_WRITE, vp, wa->wa_data,
					wa->wa_count, wa->wa_offset,
					UIO_SYSSPACE, IO_SYNC, 0);
			/*
			 * XXX - Guarantee that the inode information
			 * is on the disk.
			 */
			ILOCK(VTOI(vp));
			iupdat(VTOI(vp), TRUE);
			IUNLOCK(VTOI(vp));
		}
	}
	if (!error) {
		/*
		 * Get attributes again so we send the latest mod
		 * time to the client side for his cache.
		 */
		error = VOP_GETATTR(vp, &va, u.u_cred);
	}
	ns->ns_status = puterrno(error);
	if (!error) {
		vattr_to_nattr(&va, &ns->ns_attr);
	}
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_write: returning %d\n", error);
#endif
}

/*
 * Create a file.
 * Creates a file with given attributes and returns those attributes
 * and an fhandle for the new file.
 */
int
rfs_create(args, dr, req)
	struct nfscreatargs *args;
	struct  nfsdiropres *dr;
	struct svc_req *req;
{
	register int error;
	struct vattr va;
	struct vnode *vp;
	register struct vnode *dvp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_create: %s dfh %x %x %d\n",
	    args->ca_da.da_name, args->ca_da.da_fhandle.fh_fsid.val[0],
	    args->ca_da.da_fhandle.fh_fsid.val[1], args->ca_da.da_fhandle.fh_len);
#endif
	sattr_to_vattr(&args->ca_sa, &va);
	/* 
	 * This is a completely gross hack to make mknod
	 * work over the wire until we can wack the protocol
	 */
	if ((va.va_mode & IFMT) == IFCHR || (va.va_mode & IFMT) == IFBLK) {
		va.va_rdev = (dev_t)va.va_size;
		va.va_size = 0;
	} else if ((va.va_mode & IFMT) != IFSOCK)
		va.va_mode = IFREG | (va.va_mode & ~IFMT);

	/*
	 * XXX Should get exclusive flag and use it.
	 */
	dvp = fhtovp(&args->ca_da.da_fhandle);
	if (dvp == NULL) {
		dr->dr_status = NFSERR_STALE;
		return;
	}
	if (rdonly(dvp)) {
		error = EROFS;
	} else {
		error = VOP_CREATE(dvp, args->ca_da.da_name,
		    &va, NONEXCL, VWRITE, &vp, u.u_cred);
		if (error == EACCES) {
			/*
			 * check for dup request
			 */
			if (svckudp_dup(req)) { 
				error = VOP_LOOKUP(dvp,
				    args->ca_da.da_name, &vp, u.u_cred);
			}
		}
	}
	if (!error) {
		error = VOP_GETATTR(vp, &va, u.u_cred);
		if (!error) {
			error = handle_server_link(dvp, &vp, &va);
		}
		if (!error) {
			vattr_to_nattr(&va, &dr->dr_attr);
			error = makefh(&dr->dr_fhandle, vp);
		}
		VN_RELE(vp);
	}
	dr->dr_status = puterrno(error);
	VN_RELE(dvp);
	if (!error) {
		svckudp_dupsave(req);
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_create: returning %d\n", error);
#endif
}

/*
 * Remove a file.
 * Remove named file from parent directory.
 */
int
rfs_remove(da, status, req)
	struct nfsdiropargs *da;
	enum nfsstat *status;
	struct svc_req *req;
{
	int error;
	register struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_remove %s dfh %x %x %d\n",
	    da->da_name, da->da_fhandle.fh_fsid.val[0],
	    da->da_fhandle.fh_fsid.val[1], da->da_fhandle.fh_len);
#endif
	vp = fhtovp(&da->da_fhandle);
	if (vp == NULL) {
		*status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else {
		error = VOP_REMOVE(vp, da->da_name, u.u_cred);
		if (error == ENOENT) {
			/*
			 * check for dup request
			 */
			if (svckudp_dup(req)) { 
				error = 0;
			}
		}
	}
	*status = puterrno(error);
	VN_RELE(vp);
	if (!error) {
		svckudp_dupsave(req);
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_remove: %s returning %d\n",
	    da->da_name, error);
#endif
}

/*
 * rename a file
 * Give a file (from) a new name (to).
 */
int
rfs_rename(args, status)
	struct nfsrnmargs *args;
	enum nfsstat *status; 
{
	int error;
	register struct vnode *fromvp;
	register struct vnode *tovp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_rename %s ffh %x %x %d -> %s tfh %x %x %d\n",
	    args->rna_from.da_name,
	    args->rna_from.da_fhandle.fh_fsid.val[0],
	    args->rna_from.da_fhandle.fh_fsid.val[1],
	    args->rna_from.da_fhandle.fh_len,
	    args->rna_to.da_name,
	    args->rna_to.da_fhandle.fh_fsid.val[0],
	    args->rna_to.da_fhandle.fh_fsid.val[1],
	    args->rna_to.da_fhandle.fh_len);
#endif
	fromvp = fhtovp(&args->rna_from.da_fhandle);
	if (fromvp == NULL) {
		*status = NFSERR_STALE;
		return;
	}
	if (rdonly(fromvp)) {
		error = EROFS;
		goto fromerr;
	}
	tovp = fhtovp(&args->rna_to.da_fhandle);
	if (tovp == NULL) {
		*status = NFSERR_STALE;
		VN_RELE(fromvp);
		return;
	}
	if (rdonly(tovp)) {
		error = EROFS;
	} else {
		error = VOP_RENAME(fromvp, args->rna_from.da_name,
		    tovp, args->rna_to.da_name, u.u_cred);
	}
	VN_RELE(tovp);
fromerr:
	VN_RELE(fromvp);
	*status = puterrno(error); 
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_rename: returning %d\n", error);
#endif
} 

/*
 * Link to a file.
 * Create a file (to) which is a hard link to the given file (from).
 */
int
rfs_link(args, status, req) 
	struct nfslinkargs *args;
	enum nfsstat *status;  
	struct svc_req *req;
{
	int error;
	register struct vnode *fromvp;
	register struct vnode *tovp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_link ffh %x %x %d -> %s tfh %x %x %d\n",
	    args->la_from.fh_fsid.val[0], args->la_from.fh_fsid.val[1],
	    args->la_from.fh_len, args->la_to.da_name,
	    args->la_to.da_fhandle.fh_fsid.val[0],args->la_to.da_fhandle.fh_fsid.val[1],
	    args->la_to.da_fhandle.fh_len);
#endif
	fromvp = fhtovp(&args->la_from);
	if (fromvp == NULL) {
		*status = NFSERR_STALE;
		return;
	}
	tovp = fhtovp(&args->la_to.da_fhandle);
	if (tovp == NULL) {
		*status = NFSERR_STALE;
		VN_RELE(fromvp);
		return;
	}
	if (rdonly(tovp)) {
		error = EROFS;
	} else {
		error = VOP_LINK(fromvp, tovp, args->la_to.da_name, u.u_cred);
		if (error == EEXIST) {
			/*
			 * check for dup request
			 */
			if (svckudp_dup(req)) { 
				error = 0;
			}
		}
	}
	*status = puterrno(error);
	VN_RELE(fromvp);
	VN_RELE(tovp);
	if (!error) {
		svckudp_dupsave(req);
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_link: returning %d\n", error);
#endif
} 
 
/*
 * Symbolicly link to a file.
 * Create a file (to) with the given attributes which is a symbolic link
 * to the given path name (to).
 */
int
rfs_symlink(args, status) 
	struct nfsslargs *args;
	enum nfsstat *status;   
{		  
	int error;
	struct vattr va;
	register struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_symlink %s ffh %x %x %d -> %s\n",
	    args->sla_from.da_name,
	    args->sla_from.da_fhandle.fh_fsid.val[0],
	    args->sla_from.da_fhandle.fh_fsid.val[1],
	    args->sla_from.da_fhandle.fh_len,
	    args->sla_tnm);
#endif
	sattr_to_vattr(&args->sla_sa, &va);
	va.va_mode &= ~IFMT;
	va.va_mode |= VLNK;
	vp = fhtovp(&args->sla_from.da_fhandle);
	if (vp == NULL) {
		*status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else {
		error = VOP_SYMLINK(vp, args->sla_from.da_name,
		    &va, args->sla_tnm, u.u_cred);
	}
	*status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_symlink: returning %d\n", error);
#endif
}  
  
/*
 * Make a directory.
 * Create a directory with the given name, parent directory, and attributes.
 * Returns a file handle and attributes for the new directory.
 */
int
rfs_mkdir(args, dr, req)
	struct nfscreatargs *args;
	struct  nfsdiropres *dr;
	struct svc_req *req;
{
	int error;
	struct vattr va;
	struct vnode *dvp;
	register struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_mkdir %s fh %x %x %d\n",
	    args->ca_da.da_name, args->ca_da.da_fhandle.fh_fsid.val[0],
	    args->ca_da.da_fhandle.fh_fsid.val[1], args->ca_da.da_fhandle.fh_len);
#endif
	sattr_to_vattr(&args->ca_sa, &va);
	va.va_mode &= ~IFMT;
	va.va_mode |= VDIR;
	/*
	 * Should get exclusive flag and pass it on here
	 */
	vp = fhtovp(&args->ca_da.da_fhandle);
	if (vp == NULL) {
		dr->dr_status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else {
		error = VOP_MKDIR(vp, args->ca_da.da_name, &va, &dvp, u.u_cred);
		if (error == EEXIST) {
			/*
			 * check for dup request
			 */
			if (svckudp_dup(req)) { 
				error = VOP_LOOKUP(vp,
				    args->ca_da.da_name, &dvp, u.u_cred);
				if (!error) {
		/* changed the vnode pointer from vp to dvp */
					error = VOP_GETATTR(dvp, &va, u.u_cred);
				}
			}
		}
	}
	if (!error) {
		vattr_to_nattr(&va, &dr->dr_attr);
		error = makefh(&dr->dr_fhandle, dvp);
		VN_RELE(dvp);
	}
	dr->dr_status = puterrno(error);
	VN_RELE(vp);
	if (!error) {
		svckudp_dupsave(req);
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_mkdir: returning %d\n", error);
#endif
}

/*
 * Remove a directory.
 * Remove the given directory name from the given parent directory.
 */
int
rfs_rmdir(da, status, req)
	struct nfsdiropargs *da;
	enum nfsstat *status;
	struct svc_req *req;
{
	int error;
	register struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_rmdir %s fh %x %x %d\n",
	    da->da_name, da->da_fhandle.fh_fsid.val[0],
	    da->da_fhandle.fh_fsid.val[1], da->da_fhandle.fh_len);
#endif
	vp = fhtovp(&da->da_fhandle);
	if (vp == NULL) {
		*status = NFSERR_STALE;
		return;
	}
	if (rdonly(vp)) {
		error = EROFS;
	} else {
		error = VOP_RMDIR(vp, da->da_name, u.u_cred);
		if (error == ENOENT) {
			/*
			 * check for dup request
			 */
			if (svckudp_dup(req)) { 
				error = 0;
			}
		}
	}
	*status = puterrno(error);
	VN_RELE(vp);
	if (!error) {
		svckudp_dupsave(req);
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "nfs_rmdir returning %d\n", error);
#endif
}

int
rfs_readdir(rda, rd)
	struct nfsrddirargs *rda;
	register struct nfsrddirres  *rd;
{
	int error;
	u_long offset;
	u_long skipped;
	struct iovec iov;
	struct uio uio;
	register struct vnode *vp;
	struct direct *dp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_readdir fh %x %x %d count %d\n",
	    rda->rda_fh.fh_fsid.val[0], rda->rda_fh.fh_fsid.val[1],
	    rda->rda_fh.fh_len, rda->rda_count);
#endif
	vp = fhtovp(&rda->rda_fh);
	if (vp == NULL) {
		rd->rd_entries = NULL;
		rd->rd_status = NFSERR_STALE;
		return;
	}
	/*
	 * check cd access to dir.  we have to do this here because
	 * the opendir doesn't go over the wire.
	 */
	error = VOP_ACCESS(vp, VEXEC, u.u_cred);
	if (error) {
		goto bad;
	}

	/*
	 * Allocate data for entries.  This will be freed by rfs_rddirfree.
	 */
	rd->rd_kalloc_size = (u_int)rda->rda_count;
	rd->rd_kalloc_base = (caddr_t)kalloc(rd->rd_kalloc_size);
nxtblk:
	rd->rd_entries  = (struct direct *)rd->rd_kalloc_base;
	rd->rd_bufsize = rd->rd_kalloc_size;
	rd->rd_offset = offset = rda->rda_offset & ~(DIRBLKSIZ -1);

	/*
	 * Set up io vector to read directory data
	 */
	iov.iov_base = (caddr_t)rd->rd_entries;
	iov.iov_len = rda->rda_count;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_seg = UIO_SYSSPACE;
	uio.uio_offset = offset;
	uio.uio_resid = rda->rda_count;

	/*
	 * read directory
	 */
	error = VOP_READDIR(vp, &uio, u.u_cred);

	/*
	 * Clean up
	 */
	if (error) {	
		rd->rd_size = 0;
		goto bad;
	}

	/*
	 * set size and eof
	 */
	if (uio.uio_resid) {
		rd->rd_size = rda->rda_count - uio.uio_resid;
		rd->rd_eof = TRUE;
	} else {
		rd->rd_size = rda->rda_count;
		rd->rd_eof = FALSE;
	}
	/*
	 * if client request was in the middle of a block
	 * or block begins with null entries skip entries
	 * til we are on a valid entry >= client's requested
	 * offset.
	 */
	dp = rd->rd_entries;
	skipped = 0;
	while ((skipped < rd->rd_size) &&
	    ((offset + dp->d_reclen <= rda->rda_offset) || (dp->d_ino == 0))) {
		skipped += dp->d_reclen;
		offset += dp->d_reclen;
		dp = (struct direct *)((int)dp + dp->d_reclen);
	}
	/*
	 * Reset entries pointer and free space we are skipping
	 */
	if (skipped) {
		rd->rd_size -= skipped;
		rd->rd_bufsize -= skipped;
		rd->rd_offset = offset;
		rd->rd_entries = (struct direct *)
		    ((int)rd->rd_entries + skipped);
		if (rd->rd_size == 0 && !rd->rd_eof) {
			/*
			 * we have skipped a whole block, reset offset
			 * and read another block (unless eof)
			 */
			rda->rda_offset = rd->rd_offset;
			goto nxtblk;
		}
	}
bad:
	rd->rd_status = puterrno(error);
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_readdir: returning %d\n", error);
#endif
}

rfs_rddirfree(rd)
	struct nfsrddirres *rd;
{
	if (rd->rd_entries != NULL) {
		kfree(rd->rd_kalloc_base, rd->rd_kalloc_size);
	}
}

rfs_statfs(fh, fs)
	fhandle_t *fh;
	register struct nfsstatfs *fs;
{
	int error;
	struct statfs sb;
	register struct vnode *vp;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "rfs_statfs fh %x %x %d\n",
	    fh->fh_fsid.val[0], fh->fh_fsid.val[1], fh->fh_len);
#endif
	vp = fhtovp(fh);
	if (vp == NULL) {
		fs->fs_status = NFSERR_STALE;
		return;
	}
	error = VFS_STATFS(vp->v_vfsp, &sb);
	fs->fs_status = puterrno(error);
	if (!error) {
		fs->fs_tsize = nfstsize();
		fs->fs_bsize = sb.f_bsize;
		fs->fs_blocks = sb.f_blocks;
		fs->fs_bfree = sb.f_bfree;
		fs->fs_bavail = sb.f_bavail;
	}
	VN_RELE(vp);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 5, "rfs_statfs returning %d\n", error);
#endif
}

/*ARGSUSED*/
rfs_null(argp, resp)
	caddr_t *argp;
	caddr_t *resp;
{
	/* do nothing */
	return (0);
}

/*ARGSUSED*/
rfs_error(argp, resp)
	caddr_t *argp;
	caddr_t *resp;
{
	return (EOPNOTSUPP);
}

int
nullfree()
{
}

/*
 * rfs dispatch table
 * Indexed by version,proc
 */

struct rfsdisp {
	int	  (*dis_proc)();	/* proc to call */
	xdrproc_t dis_xdrargs;		/* xdr routine to get args */
	int	  dis_argsz;		/* sizeof args */
	xdrproc_t dis_xdrres;		/* xdr routine to put results */
	int	  dis_ressz;		/* size of results */
	int	  (*dis_resfree)();	/* frees space allocated by proc */
} rfsdisptab[][RFS_NPROC]  = {
	{
	/*
	 * VERSION 2
	 * Changed rddirres to have eof at end instead of beginning
	 */
	/* RFS_NULL = 0 */
	{rfs_null, xdr_void, 0,
	    xdr_void, 0, nullfree},
	/* RFS_GETATTR = 1 */
	{rfs_getattr, xdr_fhandle, sizeof(fhandle_t),
	    xdr_attrstat, sizeof(struct nfsattrstat), nullfree},
	/* RFS_SETATTR = 2 */
	{rfs_setattr, xdr_saargs, sizeof(struct nfssaargs),
	    xdr_attrstat, sizeof(struct nfsattrstat), nullfree},
	/* RFS_ROOT = 3 *** NO LONGER SUPPORTED *** */
	{rfs_error, xdr_void, 0,
	    xdr_void, 0, nullfree},
	/* RFS_LOOKUP = 4 */
	{rfs_lookup, xdr_diropargs, sizeof(struct nfsdiropargs),
	    xdr_diropres, sizeof(struct nfsdiropres), nullfree},
	/* RFS_READLINK = 5 */
	{rfs_readlink, xdr_fhandle, sizeof(fhandle_t),
	    xdr_rdlnres, sizeof(struct nfsrdlnres), rfs_rlfree},
	/* RFS_READ = 6 */
	{rfs_read, xdr_readargs, sizeof(struct nfsreadargs),
	    xdr_rdresult, sizeof(struct nfsrdresult), rfs_rdfree},
	/* RFS_WRITECACHE = 7 *** NO LONGER SUPPORTED *** */
	{rfs_error, xdr_void, 0,
	    xdr_void, 0, nullfree},
	/* RFS_WRITE = 8 */
	{rfs_write, xdr_writeargs, sizeof(struct nfswriteargs),
	    xdr_attrstat, sizeof(struct nfsattrstat), nullfree},
	/* RFS_CREATE = 9 */
	{rfs_create, xdr_creatargs, sizeof(struct nfscreatargs),
	    xdr_diropres, sizeof(struct nfsdiropres), nullfree},
	/* RFS_REMOVE = 10 */
	{rfs_remove, xdr_diropargs, sizeof(struct nfsdiropargs), 
	    xdr_enum, sizeof(enum nfsstat), nullfree},
	/* RFS_RENAME = 11 */
	{rfs_rename, xdr_rnmargs, sizeof(struct nfsrnmargs), 
	    xdr_enum, sizeof(enum nfsstat), nullfree},
	/* RFS_LINK = 12 */
	{rfs_link, xdr_linkargs, sizeof(struct nfslinkargs), 
	    xdr_enum, sizeof(enum nfsstat), nullfree},
	/* RFS_SYMLINK = 13 */
	{rfs_symlink, xdr_slargs, sizeof(struct nfsslargs), 
	    xdr_enum, sizeof(enum nfsstat), nullfree},
	/* RFS_MKDIR = 14 */
	{rfs_mkdir, xdr_creatargs, sizeof(struct nfscreatargs),
	    xdr_diropres, sizeof(struct nfsdiropres), nullfree},
	/* RFS_RMDIR = 15 */
	{rfs_rmdir, xdr_diropargs, sizeof(struct nfsdiropargs), 
	    xdr_enum, sizeof(enum nfsstat), nullfree},
	/* RFS_READDIR = 16 */
	{rfs_readdir, xdr_rddirargs, sizeof(struct nfsrddirargs),
	    xdr_putrddirres, sizeof(struct nfsrddirres), rfs_rddirfree},
	/* RFS_STATFS = 17 */
	{rfs_statfs, xdr_fhandle, sizeof(fhandle_t),
	    xdr_statfs, sizeof(struct nfsstatfs), nullfree},
	}
};

struct rfsspace {
	struct rfsspace *rs_next;
	caddr_t		rs_dummy;
};

struct rfsspace *rfsfreesp = NULL;

int rfssize = 0;

caddr_t
rfsget()
{
	int i;
	struct rfsdisp *dis;
	caddr_t ret;
	static zone_t nfs_rfs_zone;

	if (rfssize == 0) {
		for (i = 0; i < 1 + VERSIONMAX - VERSIONMIN; i++) {
			for (dis = &rfsdisptab[i][0];
			     dis < &rfsdisptab[i][RFS_NPROC];
			     dis++) {
				rfssize = MAX(rfssize, dis->dis_argsz);
				rfssize = MAX(rfssize, dis->dis_ressz);
			}
		}
		nfs_rfs_zone = zinit(rfssize, 1024*1024, 0, FALSE, "nfs rfs");
	}

	if (rfsfreesp) {
		ret = (caddr_t)rfsfreesp;
		rfsfreesp = rfsfreesp->rs_next;
	} else {
		ZALLOC(nfs_rfs_zone, ret, caddr_t);
	}
	return (ret);
}

rfsput(rs)
	struct rfsspace *rs;
{
	rs->rs_next = rfsfreesp;
	rfsfreesp = rs;
}


int nobody = -2;

/*
 * If nfs_portmon is set, then clients are required to use
 * privileged ports (ports < IPPORT_RESERVED) in order to get NFS services.
 */
int nfs_portmon = 0;


void
rfs_dispatch(req, xprt)
	struct svc_req *req;
	register SVCXPRT *xprt;
{
	int which;
	int vers;
	caddr_t	*args = NULL;
	caddr_t	*res = NULL;
	register struct rfsdisp *disp;
	struct authunix_parms *aup;
	register int i;
	struct ucred *tmpcr;
	struct ucred *newcr = NULL;
	int error;

	svstat.ncalls++;
	error = 0;
	which = req->rq_proc;
	if (which < 0 || which >= RFS_NPROC) {
#ifdef	NFSDEBUG
		dprint(nfsdebug, 2,
		    "rfs_dispatch: bad proc %d\n", which);
#endif
		svcerr_noproc(req->rq_xprt);
		error++;
		goto done;
	}
	vers = req->rq_vers;
	if (vers < VERSIONMIN || vers > VERSIONMAX) {
#ifdef	NFSDEBUG
		dprint(nfsdebug, 2,
		    "rfs_dispatch: bad vers %d low %d high %d\n",
		    vers, VERSIONMIN, VERSIONMAX);
#endif
		svcerr_progvers(req->rq_xprt, (u_long)VERSIONMIN,
		    (u_long)VERSIONMAX);
		error++;
		goto done;
	}
	vers -= VERSIONMIN;
	disp = &rfsdisptab[vers][which];

	/*
	 * Clean up as if a system call just started
	 */
	u.u_error = 0;

	/*
	 * Allocate args struct and deserialize into it.
	 */
	args = (caddr_t *)rfsget();
	bzero((caddr_t)args, (u_int)rfssize);
	if ( ! SVC_GETARGS(xprt, disp->dis_xdrargs, args)) {
		svcerr_decode(xprt);
		error++;
		goto done;
	}

	/*
	 * Check for unix style credentials
	 */
	if (req->rq_cred.oa_flavor != AUTH_UNIX && which != RFS_NULL) {
		svcerr_weakauth(xprt);
		error++;
		goto done;
	}

	if (nfs_portmon) {
		/*
		* Check for privileged port number
		*/
       	static count = 0;
		if (ntohs(xprt->xp_raddr.sin_port) >= IPPORT_RESERVED) {
			svcerr_weakauth(xprt);
			if (count == 0) {
				printf("NFS request from unprivileged port, ");
				printf("source IP address = %x\n",
					xprt->xp_raddr.sin_addr.s_addr);
			}
			count++;
			count %= 256;
			error++;
			goto done;
		}
	}


	/*
	 * Set uid, gid, and gids to auth params
	 */
	if (which != RFS_NULL) {
		aup = (struct authunix_parms *)req->rq_clntcred;
		newcr = crget();
		if (aup->aup_uid == 0) {
			/*
			 * root over the net becomes other on the server (uid -2)
			 */
			newcr->cr_uid = (uid_t)nobody;
		} else {
			newcr->cr_uid = (uid_t)aup->aup_uid;
		}
		newcr->cr_gid = (gid_t)aup->aup_gid;
		for (i=0; i < aup->aup_len; i++)
			newcr->cr_groups[i] = (gid_t)aup->aup_gids[i];
		for (; i < NGROUPS; i++)
			newcr->cr_groups[i] = NOGROUP;
		tmpcr = u.u_cred;
		u.u_cred = newcr;
	}

	/*
	 * Allocate results struct.
	 */
	res = (caddr_t *)rfsget();
	bzero((caddr_t)res, (u_int)rfssize);

	svstat.reqs[which]++;

	/*
	 * Call service routine with arg struct and results struct
	 */
	(*disp->dis_proc)(args, res, req);

done:
	/*
	 * Free arguments struct
	 */
	if (!SVC_FREEARGS(xprt, disp->dis_xdrargs, args) ) {
		error++;
	}
	if (args != NULL) {
		rfsput((struct rfsspace *)args);
	}

	/*
	 * Serialize and send results struct
	 */
	if (!error) {
		if (!svc_sendreply(xprt, disp->dis_xdrres, (caddr_t)res)) {
			error++;
		}
	}

	/*
	 * Free results struct
	 */
	if (res != NULL) {
		if ( disp->dis_resfree != nullfree ) {
			(*disp->dis_resfree)(res);
		}
		rfsput((struct rfsspace *)res);
	}
	/*
	 * restore original credentials
	 */
	if (newcr) {
		u.u_cred = tmpcr;
		crfree(newcr);
	}
	svstat.nbadcalls += error;
}

enum nfsftype
modetonfsftype(mode)
u_short mode;
{
	switch (mode) {
	case IFCHR:
		return(NFCHR);
	case IFDIR:
		return(NFDIR);
	case IFBLK:
		return(NFBLK);
	case IFREG:
		return(NFREG);
	case IFLNK:
		return(NFLNK);
	case IFSOCK:
	default:
		return(NFREG);	/* XXX */
	}
}

vattr_to_nattr(vap, na)
	register struct vattr *vap;
	register struct nfsfattr *na;
{
	na->na_type = modetonfsftype(vap->va_mode&IFMT);
	na->na_mode = vap->va_mode;
	na->na_uid = (u_long)vap->va_uid;
	na->na_gid = (u_long)vap->va_gid;
	na->na_fsid = vap->va_fsid;
	na->na_nodeid = vap->va_nodeid;
	na->na_nlink = vap->va_nlink;
	na->na_size = vap->va_size;
	na->na_atime.tv_sec  = vap->va_atime.tv_sec;
	na->na_atime.tv_usec = vap->va_atime.tv_usec;
	na->na_mtime.tv_sec  = vap->va_mtime.tv_sec;
	na->na_mtime.tv_usec = vap->va_mtime.tv_usec;
	na->na_ctime.tv_sec  = vap->va_ctime.tv_sec;
	na->na_ctime.tv_usec = vap->va_ctime.tv_usec;
	na->na_rdev = vap->va_rdev;
	na->na_blocks = vap->va_blocks;
	na->na_blocksize = vap->va_blocksize;
}

sattr_to_vattr(sa, vap)
	register struct nfssattr *sa;
	register struct vattr *vap;
{
	vattr_null(vap);
	vap->va_mode = sa->sa_mode;
	vap->va_uid = (uid_t)sa->sa_uid;
	vap->va_gid = (gid_t)sa->sa_gid;
	vap->va_size = sa->sa_size;
	vap->va_atime.tv_sec  = sa->sa_atime.tv_sec;
	vap->va_atime.tv_usec = sa->sa_atime.tv_usec;
	vap->va_mtime.tv_sec  = sa->sa_mtime.tv_sec;
	vap->va_mtime.tv_usec = sa->sa_mtime.tv_usec;
}

/*
 * Make an fhandle from a vnode
 */
makefh(fh, vp)
	register fhandle_t *fh;
	struct vnode *vp;
{
	struct fid *fidp;
	int error;

	if (vp->v_type == ITYPE_NFS) {
		return (EREMOTE);
	}
	error = VOP_FID(vp, &fidp);
	if (error || fidp == NULL) {
		/*
		 * Should be something other than EREMOTE
		 */
		return (EREMOTE);
	}
	if (fidp->fid_len > NFS_FHMAXDATA) {
		VOP_FREEFID(vp, fidp);
		return (EREMOTE);
	}
	bzero((caddr_t)fh, NFS_FHSIZE);
	fh->fh_fsid.val[0] = vp->v_vfsp->vfs_fsid.val[0];
	fh->fh_fsid.val[1] = vp->v_vfsp->vfs_fsid.val[1];
	fh->fh_len = fidp->fid_len;
	bcopy(fidp->fid_data, fh->fh_data, fidp->fid_len);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 4, "makefh: vp %x fsid %x %x len %d data %d %d\n",
	    vp, fh->fh_fsid.val[0], fh->fh_fsid.val[1], fh->fh_len,
	    *(int *)fh->fh_data, *(int *)&fh->fh_data[sizeof(int)]);
#endif
	VOP_FREEFID(vp, fidp);
	return (0);
}

/*
 * Convert an fhandle into a vnode.
 * Uses the file id (fh_len + fh_data) in the fhandle to get the vnode.
 * WARNING: users of this routine must do a VN_RELE on the vnode when they
 * are done with it.
 */
struct vnode *
fhtovp(fh)
	fhandle_t *fh;
{
	register struct vfs *vfsp;
	struct vnode *vp;
	int error;

	vfsp = getvfs(&fh->fh_fsid);
	if (vfsp == NULL) {
		return (NULL);
	}
	error = VFS_VGET(vfsp, &vp, (struct fid *)&(fh->fh_len));
	if (error || vp == NULL) {
#ifdef	NFSDEBUG
		dprint(nfsdebug, 1, "fhtovp(%x) couldn't vget\n", fh);
#endif
		return (NULL);
	}
	if (u.u_cred->cr_uid == (uid_t)nobody
	  && (vfsp->vfs_flag & VFS_EXPORTED)) {
		/*
		 * We assume here that the uid is already set to "nobody"
		 * if the uid in the credentials with the call was 0.
		 */
#ifdef	NFSDEBUG
		dprint(nfsdebug, 3, "fhtovp: root -> %d\n",
		    vp->v_vfsp->vfs_exroot);
#endif
		u.u_cred->cr_uid = vfsp->vfs_exroot;
	}
	return (vp);
}

/*
 * Exportfs system call
 */
exportfs()
{
	register struct a {
		char *dname;
		int rootid;
		int flags;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;
	register int error;

	error = lookupname(uap->dname, UIO_USERSPACE, FOLLOW_LINK,
	    (struct vnode **)0, &vp);
	if (error) {
		return (error);
	}
	vp->v_vfsp->vfs_exroot = (u_short)uap->rootid;
	vp->v_vfsp->vfs_exflags = (short)uap->flags;
	vp->v_vfsp->vfs_flag |= VFS_EXPORTED;
#ifdef	NFSDEBUG
	dprint(nfsdebug, 3, "exportfs: root %d flags %x\n",
	    vp->v_vfsp->vfs_exroot, vp->v_vfsp->vfs_exflags);
#endif
	VN_RELE(vp);
	return (0);
}

/*
 *  This routine handles server-expanded symbolic links,
 *  currently represented as symbolic links with a group id of 64.
 */
int handle_server_link(dvp, vpp, vap)
struct vnode *dvp;	/* should be held */
struct vnode **vpp;	/* should be held; new vnode returned held */
struct vattr *vap;	/* should be valid; returned valid */
{
	struct pathname linkpath;
	struct inode *cdir;
	int error;

	/* if not a symbolic link, or not 'symlink' group, then return */
	if (((*vpp)->v_mode & VFMT) != VLNK || vap->va_gid != 64) {
		return 0;
	}
	/*
	 *  This is a server-expand symlink, so read the symlink and look it
	 *  up here.  We set u.u_cdir to dvp so that relative symlinks work.
	 *  Saving and restoring u.u_cdir may not be necessary.
	 */
	error = getsymlink(*vpp, &linkpath);
	if (error) {
		return error;
	}
	if (pn_pathleft(&linkpath) == 0) {
		(void) pn_set(&linkpath, ".");
	}
	VN_RELE(*vpp);
	cdir = u.u_cdir;
	u.u_cdir = VTOI(dvp);
	error = lookuppn(&linkpath, FOLLOW_LINK, 0, vpp);
	u.u_cdir = cdir;
	pn_free(&linkpath);
	if (error) {
		*vpp = (struct vnode *)0;
		return error;
	}
	return VOP_GETATTR(*vpp, vap, u.u_cred);
}
