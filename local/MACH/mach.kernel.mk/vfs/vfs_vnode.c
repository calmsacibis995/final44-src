/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_vnode.c,v $
 * Revision 2.12  92/02/06  00:28:19  mja
 * 	Added hooks for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.11  89/10/03  19:28:27  rpd
 * 	Fix from NeXT:  in vn_open, check for sockets in all cases.
 * 	[89/08/21  19:53:38  rpd]
 * 
 * Revision 2.10  89/09/05  20:45:48  jsb
 * 	Moved @sys-handling code to vfs/vfs_sysnames.c.
 * 	[89/09/05  15:14:53  jsb]
 * 
 * Revision 2.9  89/08/02  08:13:04  jsb
 * 	Eliminated MACH conditionals. Corrected conditional around
 * 	afs_gateway_get_sysname so that STD-nfs will build.
 * 	Replaced kallocs with zallocs.
 * 	[89/07/31  15:45:50  jsb]
 * 
 * Revision 2.8  89/06/03  15:42:47  jsb
 * 	Added vop_lookup routine to support @sys expansion in all filesystems.
 * 	[89/06/02  13:08:26  jsb]
 * 
 * Revision 2.7  89/05/11  15:40:38  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.6  89/05/06  15:44:00  rpd
 * 	From jsb: When checking for text-busy, use inode_uncache_try.
 * 
 * Revision 2.5  89/04/22  15:34:51  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:45:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:13:45  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:27:11  jsb
 * 	Include file references; get rid of VPAGER conditionals;
 * 	MACH_RFS: add rfs support.
 * 	[89/01/17  17:32:59  jsb]
 *
 * 27-Aug-87  Peter King (king) at NeXT
 *	Original Sun source, upgraded to Mach
 */ 

/* @(#)vfs_vnode.c	1.1 87/06/02 3.2/4.3NFSSRC */
/*	@(#)vfs_vnode.c 1.1 86/09/25 SMI	*/

#include <mach_nbc.h>
#include <mach_rfs.h>
#include <dfstrace.h>

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <kern/mfs.h>
#include <builtin/inode_pager.h>

#if DFSTRACE > 0
#include <dfs/dfs_log.h>
#endif DFSTRACE

#if	MACH_RFS
/*
 *  Force all lookup() calls to permit remote names since this module has
 *  been updated.
 */
#undef	lookupname
#define lookupname	rlookupname
#undef	lookuppn
#define lookuppn	rlookuppn
#endif	MACH_RFS

/*
 * read or write a vnode
 */
int
vn_rdwr(rw, vp, base, len, offset, seg, ioflag, aresid)
	enum uio_rw rw;
	struct vnode *vp;
	caddr_t base;
	int len;
	int offset;
	int seg;
	int ioflag;
	int *aresid;
{
	struct uio auio;
	struct iovec aiov;
	int error;

	if ((rw == UIO_WRITE) && (vp->v_vfsp->vfs_flag & VFS_RDONLY)) {
		return (EROFS);
	}

	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = offset;
	auio.uio_seg = seg;
	auio.uio_resid = len;
#if	MACH_NBC
	if (MFS_ABLE(vp)) {
		map_inode(vp);
		error = mfs_io(vp, &auio, rw, ioflag, u.u_cred);
		unmap_inode(vp);
	} else
#endif	MACH_NBC
	error = VOP_RDWR(vp, &auio, rw, ioflag, u.u_cred);
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid)
		    if (error == 0)
			error = EIO;
	return (error);
}

/*
 * realease a vnode. Decrements reference count and
 * calls VOP_INACTIVE on last.
 */
void
vn_rele(vp)
	register struct vnode *vp;
{
	/*
	 * sanity check
	 */
	if (vp->v_count == 0)
		panic("vn_rele");
	if (--vp->v_count == 0) {
		(void)VOP_INACTIVE(vp, u.u_cred);
	}
}

/*
 * Open/create a vnode.
 * This may be callable by the kernel, the only known side effect being that
 * the current user uid and gid are used for permissions.
 */
int
#if DFSTRACE > 0
vn_open(pnamep, seg, filemode, createmode, vpp, opcode)
#else DFSTRACE
vn_open(pnamep, seg, filemode, createmode, vpp)
#endif DFSTRACE
	char *pnamep;
	register int filemode;
	int createmode;
	struct vnode **vpp;
#if DFSTRACE > 0
	u_char opcode;
#endif DFSTRACE
{
	struct vnode *vp;		/* ptr to file vnode */
	register int mode;
	register int error;

	mode = 0;
	if (filemode & FREAD)
		mode |= VREAD;
	if (filemode & (FWRITE | FTRUNC))
		mode |= VWRITE;
 
	if (filemode & FCREAT) {
		struct vattr vattr;
		enum vcexcl excl;

		/*
		 * Wish to create a file.
		 */
		vattr_null(&vattr);
		vattr.va_mode = VREG | (createmode&~VFMT);
		if (filemode & FTRUNC)
			vattr.va_size = 0;
		if (filemode & FEXCL)
			excl = EXCL;
		else
			excl = NONEXCL;
		filemode &= ~(FCREAT | FTRUNC | FEXCL);

#if DFSTRACE > 0
		error = vn_create(pnamep, seg, &vattr, excl, mode, &vp, opcode);
#else DFSTRACE
		error = vn_create(pnamep, seg, &vattr, excl, mode, &vp);
#endif DFSTRACE
		if (error)
			return (error);
	} else {
		/*
		 * Wish to open a file.
		 * Just look it up.
		 */
		error =
		    lookupname(pnamep, seg, FOLLOW_LINK,
			(struct vnode **)0, &vp);
		if (error)
			return (error);
		/*
		 * cannnot write directories, active texts or
		 * read only filesystems
		 */
		if (filemode & (FWRITE | FTRUNC)) {
			if ((vp->v_mode&VFMT) == VDIR) {
				error = EISDIR;
				goto out;
			}
			if (vp->v_vfsp->vfs_flag & VFS_RDONLY) {
				error = EROFS;
				goto out;
			}
			/*
			 * If there's shared text associated with
			 * the vnode, try to free it up once.
			 * If we fail, we can't allow writing.
			 */
			if (vp->v_flag & VTEXT) {
				if (!inode_uncache_try(vp)) {
					error = ETXTBSY;
					goto out;
				}
			}
		}
		/*
		 * check permissions
		 */
		error = VOP_ACCESS(vp, mode, u.u_cred);
		if (error)
			goto out;
#if DFSTRACE > 0
		if (traceon) {  /* get object size. indicates if object was already */
			struct vattr attr;   /* there, and needed if truncated */

			vattr_null(&attr);  /* fake a pre record. Gross! */
			if (vp != (struct vnode *)0) 
				error = VOP_GETATTR(vp, &attr, u.u_cred);
			dfs_log(opcode, 0, 0, attr.va_size, (u_char) error);
		}
#endif DFSTRACE		
	}
	/*
	 * Sockets in filesystem name space are not supported (yet?)
	 */
	if ((vp->v_mode&VFMT) == VSOCK) {
		error = EOPNOTSUPP;
		goto out;
	}
	/*
	 * do opening protocol.
	 */
	error = VOP_OPEN(&vp, filemode, u.u_cred);
	/*
	 * truncate if required
	 */
	if ((error == 0) && (filemode & FTRUNC)) {
		struct vattr vattr;

		filemode &= ~FTRUNC;
		vattr_null(&vattr);
		vattr.va_size = 0;
		error = VOP_SETATTR(vp, &vattr, u.u_cred);
	}
#if	MACH_NBC
	if (MFS_ABLE(vp))
		map_inode(vp);
#endif	MACH_NBC
out:
	if (error) {
		VN_RELE(vp);
	} else {
		*vpp = vp;
	}
	return (error);
}

/*
 * create a vnode (makenode)
 */
int
#if DFSTRACE > 0
vn_create(pnamep, seg, vap, excl, mode, vpp, opcode)
#else DFSTRACE
vn_create(pnamep, seg, vap, excl, mode, vpp)
#endif DFSTRACE
	char *pnamep;
	int seg;
	struct vattr *vap;
	enum vcexcl excl;
	int mode;
	struct vnode **vpp;
#if DFSTRACE > 0
	u_char opcode;
#endif DFSTRACE
{
	struct vnode *dvp;	/* ptr to parent dir vnode */
	struct pathname pn;
	register int error;
#if DFSTRACE > 0
	struct vattr attr;
#endif DFSTRACE

	/*
	 * Lookup directory.
	 * If new object is a file, call lower level to create it.
	 * Note that it is up to the lower level to enforce exclusive
	 * creation, if the file is already there.
	 * This allows the lower level to do whatever
	 * locking or protocol that is needed to prevent races.
	 * If the new object is directory call lower level to make
	 * the new directory, with "." and "..".
	 */
	dvp = (struct vnode *)0;
	*vpp = (struct vnode *)0;
	error = pn_get(pnamep, seg, &pn);
	if (error)
		return (error);
	/*
	 * lookup will find the parent directory for the vnode.
	 * When it is done the pn hold the name of the entry
	 * in the directory.
	 * If this is a non-exclusive create we also find the node itself.
	 */
	if (excl == EXCL) 
		error = lookuppn(&pn, NO_FOLLOW, &dvp, (struct vnode **)0); 
	else 
		error = lookuppn(&pn, FOLLOW_LINK, &dvp, vpp); 
	if (error) {
		pn_free(&pn);
		return (error);
	}
#if DFSTRACE > 0
	if (traceon) {
		vattr_null(&attr);
		if (*vpp != (struct vnode *)0)  /* if already there, get old size */
			(void) VOP_GETATTR(*vpp, &attr, u.u_cred); /* o.w. will be -1 */
	}
#endif DFSTRACE		
	/*
	 * Make sure filesystem is writeable
	 */
	if (dvp->v_vfsp->vfs_flag & VFS_RDONLY) {
		if (*vpp) {
			VN_RELE(*vpp);
		}
		error = EROFS;
	} else if (excl == NONEXCL && *vpp != (struct vnode *)0) {
		/*
		 * The file is already there.
		 * If we are writing, and there's a shared text
		 * associated with the vnode, try to free it up once.
		 * If we fail, we can't allow writing.
		 */
		if ((mode & VWRITE) && ((*vpp)->v_flag & VTEXT)) {
			if (!inode_uncache_try(*vpp)) {
				error = ETXTBSY;
			}
		}
		/*
		 * we throw the vnode away to let VOP_CREATE truncate the
		 * file in a non-racy manner.
		 */
		VN_RELE(*vpp);
	}
	if (error == 0) {
		/*
		 * call mkdir if directory or create if other
		 */
		if ((vap->va_mode&VFMT) == VDIR) {
			error = VOP_MKDIR(dvp, pn.pn_path, vap, vpp, u.u_cred);
		} else {
			error = VOP_CREATE(
			    dvp, pn.pn_path, vap, excl, mode, vpp, u.u_cred);
		}
	}
#if DFSTRACE > 0
	/* log a pre-record containing the dvp, among other things. */
	if (traceon)
		dfs_log(opcode, 0, dvp, attr.va_size, (u_char) error);
#endif DFSTRACE
	pn_free(&pn);
	VN_RELE(dvp);
	return (error);
}

/*
 * close a vnode
 */
int
vn_close(vp, flag)
register struct vnode *vp;
int flag;
{
	int	error;

#if	MACH_NBC
	if (MFS_ABLE(vp))
		unmap_inode(vp);
#endif	MACH_NBC
	error = VOP_CLOSE(vp, flag, u.u_cred);
#if	MACH_NBC
	if (vp->v_vm_info->error)
		error = vp->v_vm_info->error;
#endif	MACH_NBC
	return(error);
}

/*
 * Link.
 */
int
vn_link(from_p, to_p, seg)
	char *from_p;
	char *to_p;
	int seg;
{
	struct vnode *fvp;		/* from vnode ptr */
#if DFSTRACE > 0
	struct vnode *fdvp;             /* from director vnode ptr */
#endif DFSTRACE
	struct vnode *tdvp;		/* to directory vnode ptr */
	struct pathname pn;
	register int error;

	fvp = tdvp = (struct vnode *)0;
	error = pn_get(to_p, seg, &pn);
	if (error)
		return (error);
#if DFSTRACE > 0
	/*
	 * Get from dir vnode ptr if possible. Don't interfere with
	 * normal behavior of call.
         */
	if (traceon) {
		error = lookupname(from_p, seg, FOLLOW_LINK, &fdvp, (struct vnode **)0);
		if (error)
			fdvp = (struct vnode *) 0;
	}
#endif DFSTRACE	
	error = lookupname(from_p, seg, FOLLOW_LINK, (struct vnode **)0, &fvp);
	if (error)
		goto out;
	error = lookuppn(&pn, FOLLOW_LINK, &tdvp, (struct vnode **)0);
	if (error)
		goto out;
	/*
	 * Make sure both source vnode and target directory vnode are
	 * in the same vfs and that it is writeable.
	 */
	if (fvp->v_vfsp != tdvp->v_vfsp) {
		error = EXDEV;
		goto out;
	}
	if (tdvp->v_vfsp->vfs_flag & VFS_RDONLY) {
		error = EROFS;
		goto out;
	}
	/*
	 * do the link
	 */
	error = VOP_LINK(fvp, tdvp, pn.pn_path, u.u_cred);
out:
#if DFSTRACE > 0
	if (traceon) {
		dfs_log(DFS_LINK, seg, from_p, to_p, fvp, fdvp, tdvp, (u_char) error);
		if (fdvp)
			VN_RELE(fdvp);
	}
#endif DFSTRACE
	pn_free(&pn);
	if (fvp)
		VN_RELE(fvp);
	if (tdvp)
		VN_RELE(tdvp);
	return (error);
}

/*
 * Rename.
 */
int
vn_rename(from_p, to_p, seg)
	char *from_p;
	char *to_p;
	int seg;
{
	struct vnode *fdvp;		/* from directory vnode ptr */
	struct vnode *fvp;		/* from vnode ptr */
	struct vnode *tdvp;		/* to directory vnode ptr */
#if DFSTRACE > 0
	struct vnode *tvp;              /* target object, if any */
	struct pathname stpn;           /* to pathname, temporary copy */
#endif DFSTRACE
	struct pathname fpn;		/* from pathname */
	struct pathname tpn;		/* to pathname */
	register int error;

	fdvp = tdvp = fvp = (struct vnode *)0;
	/*
	 * get to and from pathnames
	 */
	error = pn_get(from_p, seg, &fpn);
	if (error)
		return (error);

	error = pn_get(to_p, seg, &tpn);
	if (error) {
		pn_free(&fpn);
		return (error);
	}

	/*
	 * lookup to and from directories
	 */
	error = lookuppn(&fpn, NO_FOLLOW, &fdvp, &fvp);
	if (error)
		goto out;
	/*
	 * make sure there is an entry
	 */
	if (fvp == (struct vnode *)0) {
		error = ENOENT;
		goto out;
	}

#if DFSTRACE > 0
	/* 
	 * get target vnode, if it exists. Don't interfere with
	 * normal behavior of call.
	 */
	if (traceon) {
		error = pn_get(to_p, seg, &stpn); /* stash a copy */
		if (!error) {
			error = lookuppn(&stpn, NO_FOLLOW, (struct vnode **)0, &tvp);
			pn_free(&stpn);
		}
		if (error) 
			tvp = (struct vnode *) 0;
		if (tvp) {
			dfs_log(DFS_RENAME, 0, tvp);
			VN_RELE(tvp);
		}
	}
#endif DFSTRACE
	error = lookuppn(&tpn, NO_FOLLOW, &tdvp, (struct vnode **)0);
	if (error)
		goto out;
	/*
	 * Make sure both the from vnode and the to directory are
	 * in the same vfs and that it is writeable.
	 */
	if (fvp->v_vfsp != tdvp->v_vfsp) {
		error = EXDEV;
		goto out;
	}
	if (tdvp->v_vfsp->vfs_flag & VFS_RDONLY) {
		error = EROFS;
		goto out;
	}
	/*
	 * do the rename
	 */
#if	MACH_NBC
	inode_uncache(tdvp);
#endif	MACH_NBC
	error = VOP_RENAME(fdvp, fpn.pn_path, tdvp, tpn.pn_path, u.u_cred);
out:
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_RENAME, DFS_POST, seg, from_p, to_p, 
			     fdvp, fvp, tdvp, (u_char) error);
#endif DFSTRACE
	pn_free(&fpn);
	pn_free(&tpn);
	if (fvp)
		VN_RELE(fvp);
	if (fdvp)
		VN_RELE(fdvp);
	if (tdvp)
		VN_RELE(tdvp);
	return (error);
}

/*
 * remove a file or directory.
 */
int
vn_remove(fnamep, seg, dirflag)
	char *fnamep;
	int seg;
	enum rm dirflag;
{
	struct vnode *vp;		/* entry vnode */
	struct vnode *dvp;		/* ptr to parent dir vnode */
	struct pathname pn;		/* name of entry */
	u_short vtype;
	register int error;

	error = pn_get(fnamep, seg, &pn);
	if (error)
		return (error);
	vp = (struct vnode *)0;
	error = lookuppn(&pn, NO_FOLLOW, &dvp, &vp);
	if (error) {
		pn_free(&pn);
		return (error);
	}
	/*
	 * make sure there is an entry
	 */
	if (vp == (struct vnode *)0) {
		error = ENOENT;
		goto out;
	}
#if DFSTRACE > 0
	if (traceon) dfs_log((dirflag==DIRECTORY)?DFS_RMDIR:DFS_UNLINK, 0, vp, dvp);
#endif DFSTRACE
	/*
	 * make sure filesystem is writeable
	 */
	if (vp->v_vfsp->vfs_flag & VFS_RDONLY) {
		error = EROFS;
		goto out;
	}
	/*
	 * don't unlink the root of a mounted filesystem.
	 */
	if (vp->v_flag & VROOT) {
		error = EBUSY;
		goto out;
	}
	/* XXX FIXME Should check for links = 0 and uncache only then */
	if (vp->v_vm_info->pager != MEMORY_OBJECT_NULL)
		inode_uncache(vp);
	/*
	 * release vnode before removing
	 */
	vtype = (vp->v_mode&VFMT);
	VN_RELE(vp);
	vp = (struct vnode *)0;
	if (vtype == VDIR) {
		/*
		 * if caller thought it was removing a directory, go ahead
		 */
		if (dirflag == DIRECTORY)
			error = VOP_RMDIR(dvp, pn.pn_path, u.u_cred);
		else
			error = EPERM;
	} else {
		/*
		 * if caller thought it was removing a directory, barf.
		 */
		if (dirflag == FILE)
			error = VOP_REMOVE(dvp, pn.pn_path, u.u_cred);
		else
			error = ENOTDIR;
	}
out:
	pn_free(&pn);
	if (vp != (struct vnode *)0)
		VN_RELE(vp);
	VN_RELE(dvp);
	return (error);
}

/*
 * Set vattr structure to a null value.
 * Boy is this machine dependent!
 */
void
vattr_null(vap)
struct vattr *vap;
{
	register int n;
	register char *cp;

	n = sizeof(struct vattr);
	cp = (char *)vap;
	while (n--) {
		*cp++ = -1;
	}
}

#ifdef	DEBUG
prvnode(vp)
	register struct vnode *vp;
{

	printf("vnode vp=0x%x ", vp);
	printf("flag=0x%x,count=%d,shlcnt=%d,exclcnt=%d\n",
		vp->v_flag,vp->v_count,vp->v_shlockc,vp->v_exlockc);
	printf("	vfsmnt=0x%x,vfsp=0x%x,type=%d,dev=0x%x\n",
		vp->v_vfsmountedhere,vp->v_vfsp,vp->v_mode,vp->v_rdev);
}

prvattr(vap)
	register struct vattr *vap;
{

	printf("vattr: vap=0x%x ", vap);
	printf("type=%d,mode=0%o,uid=%d,gid=%d\n",
		vap->va_mode,vap->va_uid,vap->va_gid);
	printf("fsid=%d,nodeid=%d,nlink=%d,size=%d,bsize=%d\n",
		vap->va_fsid,vap->va_nodeid,vap->va_nlink,
		vap->va_size,vap->va_blocksize);
	printf("atime=(%d,%d),mtime=(%d,%d),ctime=(%d,%d)\n",
		vap->va_atime.tv_sec,vap->va_atime.tv_usec,
		vap->va_mtime.tv_sec,vap->va_mtime.tv_usec,
		vap->va_ctime.tv_sec,vap->va_ctime.tv_usec);
	printf("rdev=0x%x, blocks=%d\n",vap->va_rdev,vap->va_blocks);
}
#endif
