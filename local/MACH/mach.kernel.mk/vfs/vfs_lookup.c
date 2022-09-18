/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_lookup.c,v $
 * Revision 2.12  92/02/06  00:28:06  mja
 * 	Added hooks for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.11  90/07/03  16:55:54  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:26:03  mrt]
 * 
 * Revision 2.10  89/10/10  11:02:30  mwyoung
 * 	Allow RFS links to be either symbolic link nodes or regular
 * 	file nodes.
 * 	[89/05/12  16:05:19  mwyoung]
 * 
 * Revision 2.9  89/08/02  08:12:34  jsb
 * 	Eliminated MACH conditionals.
 * 	Picked up setmodes -nofollow fix from dlb.
 * 	[89/07/31  15:49:04  jsb]
 * 
 * Revision 2.8  89/05/01  18:02:13  rpd
 * 	Export getsymlink() so that nfs/nfs_server.c can use it for
 * 	server-expanded symbolic links.
 * 	[89/05/01  17:45:46  jsb]
 * 
 * Revision 2.7  89/04/22  15:34:35  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/09  22:44:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/26  11:13:20  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/01/27  10:23:04  rvb
 * 	Misplaced endif in change below.
 * 	[89/01/25            rvb]
 * 
 * Revision 2.3  89/01/23  15:32:29  rvb
 * 	No nfs_ops unless MACH_NFS
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.2  89/01/18  01:26:12  jsb
 * 	MACH_RFS: add rfs support;
 * 	MACH: add support for symbolic link quoting;
 * 	(stupidly) ripped out next_metalink.
 * 	[89/01/17  17:27:55  jsb]
 * 
 *
 * 27-Aug-87  Peter King (king) at NeXT
 *	Original Sun source, upgraded to Mach.
 */ 

#include <mach_rfs.h>
#include <mach_nfs.h>
#include <dfstrace.h>

/* @(#)vfs_lookup.c	1.2 87/06/25 3.2/4.3NFSSRC */
/*	@(#)vfs_lookup.c 1.1 86/09/25 SMI	*/

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/inode.h>
#include <sys/table.h>
#if DFSTRACE > 0
#include <dfs/dfs_log.h>
#endif DFSTRACE

#if	MACH_RFS
/*
 *  The following function is used to identify the special CMU file type
 *  which is currently used to implement remote node pointer files.
 *
 *  Yes, it is really horrible that we are doing a getattr here in the
 *  nfs case. However, I believe that right after the VOP_LOOKUP that
 *  we did, that the attrs are cached, so maybe it's not so horrible...
 */
boolean_t vnodeisrfslink(vp)
struct vnode *vp;
{
	extern struct vnodeops ufs_vnodeops;
#if	MACH_NFS
	extern struct vnodeops nfs_vnodeops;
#endif	MACH_NFS
	short gid;
	u_short mode;

	if (vp->v_type == ITYPE_UFS) {
		struct inode *ip = VTOI(vp);
		gid  = ip->i_gid;
		mode = ip->i_mode;
#if	MACH_NFS
#if	0
	} else if (vp->v_type == ITYPE_NFS) {
		struct vattr va;
		return FALSE;
		/*
		 *  We turn this off until we convert all of rfs
		 *  to be independent of inodes...
		 */
		if (nfs_getattr(vp, &va, u.u_cred)) {
			return FALSE;
		}
		gid  = va.va_gid;
		mode = va.va_mode;
#endif	0
#endif	MACH_NFS
	} else {
		return FALSE;
	}
	if (gid != 64) {
		return FALSE;
	}
	mode &= (IFMT|IEXEC|(IEXEC>>3)|(IEXEC>>6));
	return ( mode == (IFREG|IEXEC) || mode == (IFLNK|IEXEC) );
}
#endif	MACH_RFS

/*
 * lookup the user file name,
 * Handle allocation and freeing of pathname buffer, return error.
 */
#if	MACH_RFS
extended_lookupname(fnamep, seg, followlink, dirvpp, compvpp, okremote,
		    keepnamebuf)
#else	MACH_RFS
lookupname(fnamep, seg, followlink, dirvpp, compvpp)
#endif	MACH_RFS
	char *fnamep;			/* user pathname */
	int seg;			/* addr space that name is in */
	enum symfollow followlink;	/* follow sym links */
	struct vnode **dirvpp;		/* ret for ptr to parent dir vnode */
	struct vnode **compvpp;		/* ret for ptr to component vnode */
#if	MACH_RFS
	int okremote;
	struct pathname *keepnamebuf;
#endif	MACH_RFS
{
	struct pathname lookpn;
	register int error;

	error = pn_get(fnamep, seg, &lookpn);
	if (error)
		return (error);
#if	MACH_RFS
	error = extended_lookuppn(&lookpn, followlink, dirvpp, compvpp,
				  okremote);
#else	MACH_RFS
	error = lookuppn(&lookpn, followlink, dirvpp, compvpp);
#endif	MACH_RFS
#if	MACH_RFS
	if (keepnamebuf)
		*keepnamebuf = lookpn;
	else
		pn_free(&lookpn);
#else	MACH_RFS
	pn_free(&lookpn);
#endif	MACH_RFS
	return (error);
}

/*
 * Starting at current directory, translate pathname pnp to end.
 * Leave pathname of final component in pnp, return the vnode
 * for the final component in *compvpp, and return the vnode
 * for the parent of the final component in dirvpp.
 *
 * This is the central routine in pathname translation and handles
 * multiple components in pathnames, separating them at /'s.  It also
 * implements mounted file systems and processes symbolic links.
 */
#if	MACH_RFS
extended_lookuppn(pnp, followlink, dirvpp, compvpp, okremote)
#else	MACH_RFS
lookuppn(pnp, followlink, dirvpp, compvpp)
#endif	MACH_RFS
	register struct pathname *pnp;		/* pathaname to lookup */
	enum symfollow followlink;		/* (don't) follow sym links */
	struct vnode **dirvpp;			/* ptr for parent vnode */
	struct vnode **compvpp;			/* ptr for entry vnode */
#if	MACH_RFS
	int okremote;
#endif	MACH_RFS
{
	register struct vnode *vp;		/* current directory vp */
	register struct vnode *cvp;		/* current component vp */
	struct vnode *tvp;			/* non-reg temp ptr */
	register struct vfs *vfsp;		/* ptr to vfs for mount indir */
	char component[MAXNAMLEN+1];		/* buffer for component */
	register int error;
	register int nlink;
#if	MACH_RFS
	int nofollow = (u.u_modes & UMODE_NOFOLLOW);
	int urfs_flag = URFS_CDIR;
	short isquoted = 0;
#define QUOTED	3
#endif	/* MACH_RFS */

#if	MACH_RFS
	u.u_rfsncnt++;
#endif	MACH_RFS
	if (u.u_modes & UMODE_NOFOLLOW)
		followlink = NO_FOLLOW;
	nlink = 0;
	cvp = (struct vnode *)0;

	/*
	 * start at current directory.
	 */
	vp = ITOV(u.u_cdir);
	VN_HOLD(vp);

begin:
	/*
	 * Each time we begin a new name interpretation (e.g.
	 * when first called and after each symbolic link is
	 * substituted), we allow the search to start at the
	 * root directory if the name starts with a '/', otherwise
	 * continuing from the current directory.
	 */
	component[0] = 0;
	if (pn_peekchar(pnp) == '/') {
		VN_RELE(vp);
#if	MACH_RFS
		isquoted = (pn_skipslash(pnp) >= QUOTED);
#else	/* MACH_RFS */
		pn_skipslash(pnp);
#endif	/* MACH_RFS */
		if (u.u_rdir) {
			vp = ITOV(u.u_rdir);
#if	MACH_RFS
			urfs_flag = URFS_RDIR;
#endif	MACH_RFS
		} else
			vp = ITOV(rootdir);
		VN_HOLD(vp);
	}
#if	MACH_RFS
	/*
	 *  Check if base directory is remote.  If this lookup/system call is
	 *  not prepared to handle a remote name, we're out of luck (this will
	 *  be detected below when the remote file inode is found not to be a
	 *  directory).
	 */
	if ((u.u_rfs&urfs_flag) && okremote && !nofollow && u.u_rfscode != 0)
		goto rfsdir;
#endif	MACH_RFS

next:
	/*
	 * Make sure we have a directory.
	 */
	if ((vp->v_mode&VFMT) != VDIR) {
#if	MACH_RFS
		if (!okremote && !nofollow && !isquoted &&
		    u.u_rfscode != 0 && vnodeisrfslink(vp))
			error = EINVAL;
		else
#endif	MACH_RFS
		error = ENOTDIR;
		goto bad;
	}
	/*
	 * Process the next component of the pathname.
	 */
	error = pn_getcomponent(pnp, component);
	if (error)
		goto bad;
	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. "/." or ".".
	 */
	if (component[0] == 0) {
		/*
		 * If the caller was interested in the parent then
		 * return an error since we don't have the real parent
		 */
		if (dirvpp != (struct vnode **)0) {
			VN_RELE(vp);
			return(EINVAL);
		}
		(void) pn_set(pnp, ".");
		if (compvpp != (struct vnode **)0) {
			*compvpp = vp;
		} else {
			VN_RELE(vp);
		}
		return(0);
	}

	/*
	 * Handle "..": two special cases.
	 * 1. If at root directory (e.g. after chroot)
	 *    then ignore it so can't get out.
	 * 2. If this vnode is the root of a mounted
	 *    file system, then replace it with the
	 *    vnode which was mounted on so we take the
	 *    .. in the other file system.
	 */
	if (strcmp(component, "..") == 0) {
checkforroot:
		if (vp == ITOV(rootdir)) {
			cvp = vp;
			VN_HOLD(cvp);
			goto skip;
		}
		if (vp == ITOV(u.u_rdir)) {
#if	MACH_RFS
			extern struct inode *rfs_rdir;

			/*
			 *  If we are about to go above the logical root
			 *  directory and the process has indicated that it
			 *  does not want this to happen transparently, return
			 *  a designated error instead of continuing.  The
			 *  error used is chosen to not overlap any others
			 *  errors that may be legitimately returned so that
			 *  the process make take appropriate action as
			 *  required.
			 *
			 *  Normally, the calling process has set this flag in
			 *  order to specially processon the remainder of the
			 *  path name following the reference to the super-root
			 *  so, provided that the keep name buffer flag was
			 *  specified, update the name pointer and arrange to
			 *  save the buffer for the caller.
			 */
			if (u.u_rfs&URFS_EROOT) {
				error = ERANGE;
				goto bad;
			}
			/*
			 * If the kernel is configured for RFS and the
			 * filesystem is not, or the local root is not the
			 * original (post-rfs_initroot) root (i.e., if this
			 * process has done a chroot), don't allow
			 * references above the root.
			 */
			if (rfs_rdir == NULL || ITOV(rfs_rdir) != vp)
#endif	MACH_RFS
			{
				cvp = vp;
				VN_HOLD(cvp);
				goto skip;
			}
		}
		if (vp->v_flag & VROOT) {
			cvp = vp;
			vp = vp->v_vfsp->vfs_vnodecovered;
			VN_HOLD(vp);
			VN_RELE(cvp);
			cvp = (struct vnode *)0;
			goto checkforroot;
		}
	}

	/*
	 * Perform a lookup in the current directory.
	 */
	error = VOP_LOOKUP(vp, component, &tvp, u.u_cred);
	cvp = tvp;
#if DFSTRACE > 0  
	if (traceon & DFS_TRACE_NAMERES) 
		dfs_log(DFS_LOOKUP, vp, cvp, component, (u_char) error);
#endif DFSTRACE
	if (error) {
		cvp = (struct vnode *)0;
		/*
		 * On error, if more pathname or if caller was not interested
		 * in the parent directory then hard error.
		 * If the path is unreadable, fail now with the right error.
		 */
		if (pn_pathleft(pnp) || dirvpp == (struct vnode **)0 ||
		    (error == EACCES))
			goto bad;
		(void) pn_set(pnp, component);
		*dirvpp = vp;
		if (compvpp != (struct vnode **)0) {
			*compvpp = (struct vnode *)0;
		}
		return (0);
	}
#if	MACH_RFS
	/* 
	 *  Check for remote name.
	 */
	if (okremote && !nofollow &&
#if	MACH_RFS
            ! isquoted &&
#endif	/* MACH_RFS */
	    u.u_rfscode != 0 &&
	    vnodeisrfslink(cvp)) {
	  	extern struct inode *rfs_namei();
		struct inode *dp;
		char *s, *t;
 
		VN_RELE(vp);
		vp = cvp;
		cvp = (struct vnode *)0;
		/*
		 *  We enter here if the current/root directory was determined
		 *  to be remote and it is the base for the path name.  The
		 *  entire name will be interpreted remotely.
		 *
		 *  At this point, cvp is null, and vp is an rfsvnode.
		 */
rfsdir:
		/*
		 *  The only time we should pass the null string through is
		 *  when this was the entire original name.  Otherwise, if the
		 *  residual name is null at this point, it actually represents
		 *  the remote root (e.g.  from a name like "/../q").  Since
		 *  the remote file system code may pass a name back to us
		 *  through the same pointer, change the name to "/" in place
		 *  within the buffer rather than setting it to a constant
		 *  string.
		 */
		if (! pn_pathleft(pnp) && pnp->pn_path != pnp->pn_buf)
		    (void) pn_set(pnp, "/");
		u.u_nd.ni_iov = &u.u_nd.ni_iovec;
		u.u_nd.ni_dirp = pnp->pn_path;
		u.u_nd.ni_dirp[pnp->pn_pathlen] = '\0';
		u.u_nd.ni_nameiop = OKREMOTE | LOOKUP;
		if (followlink)
			u.u_nd.ni_nameiop |= FOLLOW;
		*ni_nbpp(&u.u_nd) = (struct buf *)u.u_nd.ni_dirp;
		dp = rfs_namei(vp, &u.u_nd);
		if (u.u_error == ELOCAL) {
			u.u_error = 0;
			pnp->pn_path[0] = '/';
			pnp->pn_path[1] = '.';
			pnp->pn_path[2] = '.';
			pnp->pn_pathlen = strlen(pnp->pn_path);
			vp = ITOV(u.u_cdir);
			urfs_flag = URFS_CDIR;
			VN_HOLD(vp);
			goto begin;
		}
		if (u.u_nd.ni_nameiop & KEEPNAMEBUF) {
			panic("KEEPNAMEBUF set by rfs_namei");
		}
		if (dp != (struct inode *)0) {
			vp = ITOV(dp);
			if (dirvpp != (struct vnode **)0) {
				VN_RELE(vp);
				return(EINVAL);
			}
			if (compvpp != (struct vnode **)0) {
/* XXXXXXXXXXXX fixme */
IUNLOCK(VTOI(vp));
				*compvpp = vp;
			} else {
				VN_RELE(vp);
			}
		}
		return u.u_error;
	}
#endif	MACH_RFS
	/*
	 * If we hit a symbolic link and there is more path to be
	 * translated or this operation does not wish to apply
	 * to a link, then place the contents of the link at the
	 * front of the remaining pathname.
	 */
	if ((cvp->v_mode&VFMT) == VLNK &&
#if	MACH_RFS
	    ! isquoted &&
#endif	/* MACH_RFS */
	    ((followlink == FOLLOW_LINK) || pn_pathleft(pnp))) {
		struct pathname linkpath;

		nlink++;
		if (nlink > MAXSYMLINKS) {
			error = ELOOP;
			goto bad;
		}
		error = getsymlink(cvp, &linkpath);
#if DFSTRACE > 0
		if (traceon & DFS_TRACE_NAMERES)
		       dfs_log(DFS_GETSYMLINK, cvp, &linkpath, 
			       component, (u_char) error);
#endif DFSTRACE
		if (error)
			goto bad;
		if (pn_pathleft(&linkpath) == 0)
			(void) pn_set(&linkpath, ".");
		error = pn_combine(pnp, &linkpath);	/* linkpath before pn */
		pn_free(&linkpath);
		if (error)
			goto bad;
		VN_RELE(cvp);
		cvp = (struct vnode *)0;
		goto begin;
	}

	/*
	 * If this vnode is mounted on, then we
	 * transparently indirect to the vnode which 
	 * is the root of the mounted file system.
	 * Before we do this we must check that an unmount is not
	 * in progress on this vnode. This maintains the fs status
	 * quo while a possibly lengthy unmount is going on.
	 */
mloop:
	/*
	 *  FIXME XXX FIXME XXX
	 *  Check execute permission on the vnode we have NOW
	 *  and NOT the vnode upon which this guy is mounted.
	 *  We fixed the latter part in ufs_dir, but we have to
	 *  do the same for afs and nfs, and we have to do the
	 *  former right here.
	 *  FIXME XXX FIXME XXX
	 */
	while (vfsp = cvp->v_vfsmountedhere) {
		while (vfsp->vfs_flag & VFS_MLOCK) {
			vfsp->vfs_flag |= VFS_MWAIT;
#define PVFS 0		/*MACH_NFS FIX ME */
			(void) sleep((caddr_t)vfsp, PVFS);
			goto mloop;
		}
		error = VFS_ROOT(cvp->v_vfsmountedhere, &tvp);
#if DFSTRACE > 0
		if (traceon & DFS_TRACE_NAMERES) 
			dfs_log(DFS_ROOT, cvp, tvp, component, (u_char) error);
#endif DFSTRACE
		if (error)
			goto bad;
		VN_RELE(cvp);
		cvp = tvp;
	}

skip:
	/*
	 * Skip to next component of the pathname.
	 * If no more components, return last directory (if wanted)  and
	 * last component (if wanted).
	 */
	if (pn_pathleft(pnp) == 0) {
		(void) pn_set(pnp, component);
		if (dirvpp != (struct vnode **)0) {
			/*
			 * check that we have the real parent and not
			 * an alias of the last component
			 */
			if (vp == cvp) {
				VN_RELE(vp);
				VN_RELE(cvp);
				return(EINVAL);
			}
			*dirvpp = vp;
		} else {
			VN_RELE(vp);
		}
		if (compvpp != (struct vnode **)0) {
			*compvpp = cvp;
		} else {
			VN_RELE(cvp);
		}
		return (0);
	}
	/*
	 * skip over slashes from end of last component
	 */
#if	MACH_RFS
		isquoted = (pn_skipslash(pnp) >= QUOTED);
#else	/* MACH_RFS */
		pn_skipslash(pnp);
#endif	/* MACH_RFS */

	/*
	 * Searched through another level of directory:
	 * release previous directory handle and save new (result
	 * of lookup) as current directory.
	 */
	VN_RELE(vp);
	vp = cvp;
	cvp = (struct vnode *)0;
	goto next;

bad:
	/*
	 * Error. Release vnodes and return.
	 */
	if (cvp)
		VN_RELE(cvp);
	VN_RELE(vp);
	vp = (struct vnode *)0;
	if (compvpp != (struct vnode **)0)
		*compvpp = (struct vnode *)0;
	return (error);
}

/*
 * Gets symbolic link into pathname.
 * This routine is used by nfs/nfs_server.c for server-expanded
 * symbolic links.
 */
getsymlink(vp, pnp)
	struct vnode *vp;
	struct pathname *pnp;
{
	struct iovec aiov;
	struct uio auio;
	register int error;

	pn_alloc(pnp);
	aiov.iov_base = pnp->pn_buf;
	aiov.iov_len = MAXPATHLEN;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_resid = MAXPATHLEN;
	error = VOP_READLINK(vp, &auio, u.u_cred);
	pnp->pn_pathlen = MAXPATHLEN - auio.uio_resid;
	if (error)
		pn_free(pnp);
	return (error);
}
