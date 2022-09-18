/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_syscalls.c,v $
 * Revision 2.14  92/02/06  00:28:13  mja
 * 	Added hooks for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.13  90/02/11  00:23:15  berman
 * 	Added MACH_RFS code to fsyc(), fchown(), fchmod(),
 * 	and ftruncate() to make these syscalls work properly 
 * 	with RFS files.
 * 	[90/02/10            berman]
 * 
 * Revision 2.12  89/09/09  16:24:11  rvb
 * 	Add VFMT case for mknod for badsect.
 * 	[89/08/29            rvb]
 * 
 * Revision 2.11  89/09/05  20:45:32  jsb
 * 	Made chown follow symbolic links.
 * 	[89/09/05  15:08:52  jsb]
 * 
 * Revision 2.10  89/08/06  13:13:22  gm0w
 * 	Added missing code to subtract the size of the offset pointer
 * 	from the f_offset and return value in getdirentries() for rfs
 * 	directories.
 * 	[89/08/05            gm0w]
 * 
 * Revision 2.9  89/08/02  08:40:02  jsb
 * 	Eliminated MACH conditionals.
 * 	[89/07/31  16:12:21  jsb]
 * 
 * Revision 2.8  89/07/30  18:37:16  gm0w
 * 	Changed to only use VOP_READDIR from getdirentries.  This means
 * 	that old SUNOS binaries may have problems with seeking in active
 * 	directories, but that was previously true in NFS anyway...
 * 	[89/07/29            gm0w]
 * 
 * Revision 2.7  89/05/11  14:45:19  gm0w
 * 	Changed back to original getdirentries code.  Added check for
 * 	FOKDIR flag to use VOP_READ1DIR or VOP_READDIR.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.6  89/04/22  15:34:43  gm0w
 * 	Minor changes for HC.
 * 	[89/04/22            gm0w]
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  22:45:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:13:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/20  17:48:28  jsb
 * 	Have getdirentries work by calling read. This is the easiest way to
 * 	get getdirentries to work for afs directories, given that we finally
 * 	got read to work for afs directories.
 * 
 * Revision 2.2  89/01/18  01:26:51  jsb
 * 	Include file references; MACH_RFS: add rfs support;
 * 	MACH: make vhangup call ttydetach.
 * 	[89/01/17  17:31:09  jsb]
 * 
 * 17-Aug-87  Peter King (king) at NeXT
 *	Original Sun source, upgraded to Mach
 */ 

/* @(#)vfs_syscalls.c	1.3 87/06/25 3.2/4.3NFSSRC */
/*	@(#)vfs_syscalls.c 1.1 86/09/25 SMI	*/

#include <mach_nbc.h>
#include <mach_rfs.h>
#include <dfstrace.h>

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/inode.h>
#include <sys/proc.h>

#if DFSTRACE > 0
#include <dfs/dfs_log.h>
#endif DFSTRACE

extern	struct fileops vnodefops;

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
 * System call routines for operations on files other
 * than read, write and ioctl.  These calls manipulate
 * the per-process file table which references the
 * networkable version of normal UNIX inodes, called vnodes.
 *
 * Many operations take a pathname, which is read
 * into a kernel buffer by pn_get (see vfs_pathname.c).
 * After preparing arguments for an operation, a simple
 * operation proceeds:
 *
 *	error = lookupname(pname, seg, followlink, &dvp, &vp, &vattr)
 *
 * where pname is the pathname operated on, seg is the segment that the
 * pathname is in (UIO_USERSPACE or UIO_SYSSPACE), followlink specifies
 * whether to follow symbolic links, dvp is a pointer to the vnode that
 * represents the parent directory of vp, the pointer to the vnode
 * referenced by the pathname. vattr is a vattr structure which hold the
 * attributes of the final component. The lookupname routine fetches the
 * pathname string into an internal buffer using pn_get (vfs_pathname.c),
 * and iteratively running down each component of the path until the
 * the final vnode and/or it's parent are found. If either of the addresses
 * for dvp or vp are NULL, then it assumes that the caller is not interested
 * in that vnode. If the pointer to the vattr structure is NULL then attributes
 * are not returned. Once the vnode or its parent is found, then a vnode
 * operation (e.g. VOP_OPEN) may be applied to it.
 *
 * One important point is that the operations on vnode's are atomic, so that
 * vnode's are never locked at this level.  Vnode locking occurs
 * at lower levels either on this or a remote machine. Also permission
 * checking is generally done by the specific filesystem. The only
 * checks done by the vnode layer is checks involving file types
 * (e.g. VREG, VDIR etc.), since this is static over the life of the vnode.
 *
 */

/*
 * Change current working directory (".").
 */
chdir()
{
	register struct a {
		char *dirnamep;
	} *uap = (struct a *)u.u_ap;

	u.u_error = chdirec(uap->dirnamep, &u.u_cdir);
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_CHDIR, uap->dirnamep, u.u_cdir);
#endif DFSTRACE
}

/*
 * Change notion of root ("/") directory.
 */
chroot()
{
	register struct a {
		char *dirnamep;
	} *uap = (struct a *)u.u_ap;

	if (!suser())
		return;
	u.u_error = chdirec(uap->dirnamep, &u.u_rdir);
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_CHROOT, uap->dirnamep, u.u_rdir);
#endif DFSTRACE
}

/*
 * Common code for chdir and chroot.
 * Translate the pathname and insist that it
 * is a directory to which we have execute access.
 * If it is replace u.u_[cr]dir with new vnode.
 */
chdirec(dirnamep, vpp)
	char *dirnamep;
	struct vnode **vpp;
{
	struct vnode *vp;		/* new directory vnode */
	register int error;

	error =
	    lookupname(dirnamep, UIO_USERSPACE, FOLLOW_LINK,
		(struct vnode **)0, &vp);
	if (error)
		return (error);
	if ((vp->v_mode&VFMT) != VDIR) {
		error = ENOTDIR;
	} else {
		error = VOP_ACCESS(vp, VEXEC, u.u_cred);
	}
	if (error) {
		VN_RELE(vp);
	} else {
#if	MACH_RFS
		if (vpp == (struct vnode **)&u.u_cdir)
			u.u_rfs &= ~URFS_CDIR;
		else if (vpp == (struct vnode **)&u.u_rdir)
			u.u_rfs &= ~URFS_RDIR;
#endif	MACH_RFS
		if (*vpp)
			VN_RELE(*vpp);
		*vpp = vp;
	}
	return (error);
}

/*
 * Open system call.
 */
open()
{
	register struct a {
		char *fnamep;
		int fmode;
		int cmode;
	} *uap = (struct a *)u.u_ap;

#if DFSTRACE > 0
	u.u_error = copen(uap->fnamep, uap->fmode - FOPEN, uap->cmode, 
			  DFS_OPEN);
	if (traceon) dfs_log(DFS_OPEN, DFS_POST, (u_short) uap->fmode - FOPEN, 
			     (u_short) uap->cmode, uap->fnamep);
#else DFSTRACE
	u.u_error = copen(uap->fnamep, uap->fmode - FOPEN, uap->cmode);
#endif DFSTRACE
}

/*
 * Creat system call.
 */
creat()
{
	register struct a {
		char *fnamep;
		int cmode;
	} *uap = (struct a *)u.u_ap;

#if DFSTRACE > 0
	u.u_error = copen(uap->fnamep, FWRITE|FCREAT|FTRUNC, 
			  uap->cmode, DFS_CREAT);
	if (traceon) dfs_log(DFS_CREAT, DFS_POST,
			     (u_short) uap->cmode, uap->fnamep);
#else DFSTRACE
	u.u_error = copen(uap->fnamep, FWRITE|FCREAT|FTRUNC, uap->cmode);
#endif DFSTRACE
}

/*
 * Common code for open, creat.
 */
#if DFSTRACE > 0
copen(pnamep, filemode, createmode, opcode)
#else DFSTRACE
copen(pnamep, filemode, createmode)
#endif DFSTRACE
	char *pnamep;
	int filemode;
	int createmode;
#if DFSTRACE > 0
	u_char opcode;
#endif DFSTRACE
{
	register struct file *fp;
	struct vnode *vp;
	register int error;
	register int i;

	/*
	 * allocate a user file descriptor and file table entry.
	 */
	fp = falloc();
	if (fp == NULL)
		return(u.u_error);
	i = u.u_r.r_val1;		/* this is bullshit */
	/*
	 * open the vnode.
	 */
	error =
	    vn_open(pnamep, UIO_USERSPACE,
#if DFSTRACE > 0
		filemode, ((createmode & 07777) & ~u.u_cmask), &vp, opcode);
#else DFSTRACE
		filemode, ((createmode & 07777) & ~u.u_cmask), &vp);
#endif DFSTRACE

	/*
	 * If there was an error, deallocate the file descriptor.
	 * Otherwise fill in the file table entry to point to the vnode.
	 */
	if (error) {
#if	MACH_RFS
		if (error == ERFSREMOTE)
			return error;
#endif	MACH_RFS
		u.u_ofile[i] = NULL;
		crfree(fp->f_cred);
		fp->f_count = 0;
	} else {
		fp->f_flag = filemode & FMASK;
		fp->f_type = DTYPE_VNODE;
		fp->f_data = (caddr_t)vp;
		fp->f_ops = &vnodefops;
#if	FIFOS
		/*
		 * For named-pipes, the FNDELAY flag must propagate to
		 * the rdwr layer.  Also, FAPPEND must always be set so
		 * that fp->f_offset is correctly maintained.
		 */
		if ((vp->v_mode&VFMT) == VFIFO) {
			fp->f_offset = 0;
			fp->f_flag |= FAPPEND | (filemode & FNDELAY);
		}
#endif	FIFOS
	}
	return(error);
}

/*
 * Create a special (or regular) file.
 */
mknod()
{
	register struct a {
		char		*pnamep;
		int		fmode;
		int		dev;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;
	struct vattr vattr;

	/* map 0 type into regular file, as other versions of UNIX do */
	if ((uap->fmode & IFMT) == 0)
		uap->fmode |= IFREG;

#if	FIFOS
	/* Must be super-user unless making a FIFO node */
	if (((uap->fmode & IFMT) != IFIFO) && !suser())
#else	FIFOS
	if (!suser())
#endif	FIFOS
		return;

	/*
	 * Setup desired attributes and vn_create the file.
	 */
	vattr_null(&vattr);
	vattr.va_mode = (uap->fmode&IFMT) | ((uap->fmode & 07777)&~u.u_cmask);

	switch (vattr.va_mode&IFMT) {
	case VDIR:
		u.u_error = EISDIR;	/* Can't mknod directories: use mkdir */
#if DFSTRACE > 0
		if (traceon) dfs_log(DFS_MKNOD, DFS_POST, (u_short) uap->fmode,
				     uap->dev, 
				     uap->pnamep, NULL); /* catch this case */
#endif DFSTRACE
		return;

	case VCHR:
#if	STREAMS
	case VSTR:
#endif	STREAMS
	case VBLK:
		vattr.va_rdev = uap->dev;
		break;
	case VFMT:				/* need 32 bit field for bad block */
		vattr.va_fsid = uap->dev;
		break;

	default:
		break;
	}

#if DFSTRACE > 0
	u.u_error = vn_create(uap->pnamep, UIO_USERSPACE, &vattr, EXCL, 0, 
			      &vp, DFS_MKNOD);
	if (traceon) dfs_log(DFS_MKNOD, DFS_POST, (u_short) uap->fmode, 
			     uap->dev, uap->pnamep, vp);
#else DFSTRACE
	u.u_error = vn_create(uap->pnamep, UIO_USERSPACE, &vattr, EXCL, 0, &vp);
#endif DFSTRACE
	if (u.u_error == 0)
		VN_RELE(vp);
}

/*
 * Make a directory.
 */
mkdir()
{
	struct a {
		char	*dirnamep;
		int	dmode;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;
	struct vattr vattr;

	vattr_null(&vattr);
	vattr.va_mode = VDIR | (uap->dmode & 0777) & ~u.u_cmask;

#if DFSTRACE > 0
	u.u_error = vn_create(uap->dirnamep, UIO_USERSPACE, &vattr, EXCL, 0, 
			      &vp, DFS_MKDIR);
	if (traceon) dfs_log(DFS_MKDIR, DFS_POST, uap->dmode, 
			     uap->dirnamep, vp);
#else DFSTRACE
	u.u_error = vn_create(uap->dirnamep, UIO_USERSPACE, &vattr, EXCL, 0, &vp);
#endif DFSTRACE
	if (u.u_error == 0)
		VN_RELE(vp);
}

/*
 * make a hard link
 */
link()
{
	register struct a {
		char	*from;
		char	*to;
	} *uap = (struct a *)u.u_ap;

	u.u_error = vn_link(uap->from, uap->to, UIO_USERSPACE);
}

/*
 * rename or move an existing file
 */
rename()
{
	register struct a {
		char	*from;
		char	*to;
	} *uap = (struct a *)u.u_ap;

	u.u_error = vn_rename(uap->from, uap->to, UIO_USERSPACE);
}

/*
 * Create a symbolic link.
 * Similar to link or rename except target
 * name is passed as string argument, not
 * converted to vnode reference.
 */
symlink()
{
	register struct a {
		char	*target;
		char	*linkname;
	} *uap = (struct a *)u.u_ap;
	struct vnode *dvp;
	struct vattr vattr;
	struct pathname tpn;
	struct pathname lpn;

	u.u_error = pn_get(uap->linkname, UIO_USERSPACE, &lpn);
	if (u.u_error)
		return;
	u.u_error = lookuppn(&lpn, NO_FOLLOW, &dvp, (struct vnode **)0);
	if (u.u_error) {
#if DFSTRACE > 0
		if (traceon) /* catch this case */
			dfs_log(DFS_SYMLINK, uap->target, uap->linkname, NULL);
#endif DFSTRACE
		pn_free(&lpn);
		return;
	}
	if (dvp->v_vfsp->vfs_flag & VFS_RDONLY) {
		u.u_error = EROFS;
		goto out;
	}
	u.u_error = pn_get(uap->target, UIO_USERSPACE, &tpn);
	vattr_null(&vattr);
	vattr.va_mode = 0777;
	if (u.u_error == 0) {
		u.u_error =
		   VOP_SYMLINK(dvp, lpn.pn_path, &vattr, tpn.pn_path, u.u_cred);
		pn_free(&tpn);
	}
out:
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_SYMLINK, uap->target, uap->linkname, dvp);
#endif DFSTRACE
	pn_free(&lpn);
	VN_RELE(dvp);
}

/*
 * Unlink (i.e. delete) a file.
 */
unlink()
{
	struct a {
		char	*pnamep;
	} *uap = (struct a *)u.u_ap;

	u.u_error = vn_remove(uap->pnamep, UIO_USERSPACE, FILE);
#if DFSTRACE > 0
	if (traceon) 
		dfs_log(DFS_UNLINK, DFS_POST, uap->pnamep);  /* prelog in vn_remove */
#endif DFSTRACE
}

/*
 * Remove a directory.
 */
rmdir()
{
	struct a {
		char	*dnamep;
	} *uap = (struct a *)u.u_ap;

	u.u_error = vn_remove(uap->dnamep, UIO_USERSPACE, DIRECTORY);
#if DFSTRACE > 0
	if (traceon) 
		dfs_log(DFS_RMDIR, DFS_POST, uap->dnamep);  /* prelog in vn_remove */
#endif DFSTRACE
}

/*
 * get directory entries in a file system independent format
 */
getdirentries()
{
	register struct a {
		int	fd;
		char	*buf;
		unsigned count;
		long	*basep;
	} *uap = (struct a *)u.u_ap;
	struct file *fp;
	struct uio auio;
	struct iovec aiov[2];

#if	MACH_RFS
	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		aiov[0].iov_base = (char *)uap->basep;
		aiov[0].iov_len = sizeof(long);
		aiov[1].iov_base = uap->buf;
		aiov[1].iov_len = uap->count;
		auio.uio_iov = aiov;
		auio.uio_iovcnt = 2;
		rwuio(&auio, UIO_READ);
		if (u.u_error)
			return;
		if (u.u_r.r_val1 < sizeof(long)) {
			u.u_error = EINVAL;
			return;
		}
		u.u_r.r_val1 -= sizeof(long);
		fp->f_offset -= sizeof(long);
		return;
	}
#endif	MACH_RFS
	u.u_error = getvnodefp(uap->fd, &fp);
	if (u.u_error)
		return;
	if ((fp->f_flag & FREAD) == 0) {
		u.u_error = EBADF;
		return;
	}
	aiov[0].iov_base = uap->buf;
	aiov[0].iov_len = uap->count;
	auio.uio_iov = aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = fp->f_offset;
	auio.uio_seg = UIO_USERSPACE;
	auio.uio_resid = uap->count;
	u.u_error = VOP_READDIR((struct vnode *)fp->f_data, &auio, fp->f_cred);
	if (u.u_error)
		return;
	u.u_error =
	    copyout((caddr_t)&fp->f_offset, (caddr_t)uap->basep, sizeof(long));
	u.u_r.r_val1 = uap->count - auio.uio_resid;
	fp->f_offset = auio.uio_offset;
}

/*
 * Seek on file.  Only hard operation
 * is seek relative to end which must
 * apply to vnode for current file size.
 * 
 * Note: lseek(0, 0, L_XTND) costs much more than it did before.
 */
lseek()
{
	register struct a {
		int	fd;
		off_t	off;
		int	sbase;
	} *uap = (struct a *)u.u_ap;
	struct file *fp;

#if	MACH_RFS
	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		extern struct file *rfs_finode();

		(void) rfs_finode(fp);
		return;
	}
#endif	MACH_RFS
	u.u_error = getvnodefp(uap->fd, &fp);
	if (u.u_error) {
		if (u.u_error == EINVAL)
			u.u_error = ESPIPE;	/* be compatible */
		return;
	}

#if	FIFOS
	if ((((struct vnode *)fp->f_data)->v_mode&VFMT) == VFIFO) {
		u.u_error = ESPIPE;
		return;
	}
#endif	FIFOS

	switch (uap->sbase) {

	case L_INCR:
		fp->f_offset += uap->off;
		break;

	case L_XTND: {
		struct vattr vattr;

		u.u_error =
		    VOP_GETATTR((struct vnode *)fp->f_data, &vattr, u.u_cred);
		if (u.u_error)
			return;
		fp->f_offset = uap->off + vattr.va_size;
		break;
	}

	case L_SET:
		fp->f_offset = uap->off;
		break;

	default:
		u.u_error = EINVAL;
	}
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_SEEK, fp, (short) uap->fd); 
#endif DFSTRACE
	u.u_r.r_off = fp->f_offset;
}

/*
 * Determine accessibility of file, by
 * reading its attributes and then checking
 * against our protection policy.
 */
access()
{
	register struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;
	register u_short mode;
	struct ucred *savcred = (struct ucred *)NULL;
	struct ucred *tcred;	   /* Temp cred structure for access checking */

	/*
	 * If necessary, use the real uid and gid to check access.
	 */
	if (u.u_uid != u.u_ruid || u.u_gid != u.u_rgid) {
		tcred = crdup(u.u_cred);
		tcred->cr_uid = tcred->cr_ruid;
		tcred->cr_gid = tcred->cr_rgid;
		savcred = u.u_cred;
		u.u_cred = tcred;
	}

	/*
	 * Lookup file
	 */
	u.u_error =
	    lookupname(uap->fname, UIO_USERSPACE, FOLLOW_LINK,
		(struct vnode **)0, &vp);
	if (u.u_error) {
#if DFSTRACE > 0
		if (traceon) dfs_log(DFS_ACCESS, /* catch this case */
				     (u_short) uap->fmode, uap->fname, NULL);
#endif DFSTRACE
		if (savcred) {
			u.u_cred = savcred;
			crfree(tcred);
		}
		return;
	}

	mode = 0;
	/*
	 * fmode == 0 means only check for exist
	 */
	if (uap->fmode) {
		if (uap->fmode & R_OK)
			mode |= VREAD;
		if (uap->fmode & W_OK) {
			if(vp->v_vfsp->vfs_flag & VFS_RDONLY) {
				u.u_error = EROFS;
				goto out;
			}
			mode |= VWRITE;
		}
		if (uap->fmode & X_OK)
			mode |= VEXEC;
		u.u_error = VOP_ACCESS(vp, mode, u.u_cred);
	}

	/*
	 * release the vnode and free the temp cred structure.
	 */
out:
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_ACCESS, (u_short) uap->fmode, uap->fname, vp);
#endif DFSTRACE
	VN_RELE(vp);
	if (savcred) {
		u.u_cred = savcred;
		crfree(tcred);
	}
}

/*
 * Get attributes from file or file descriptor.
 * Argument says whether to follow links, and is
 * passed through in flags.
 */
stat()
{
	caddr_t uap = (caddr_t)u.u_ap;

	u.u_error = stat1(uap, FOLLOW_LINK);
}

lstat()
{
	caddr_t uap = (caddr_t)u.u_ap;

	u.u_error = stat1(uap, NO_FOLLOW);
}

stat1(uap0, follow)
	caddr_t uap0;
	enum symfollow follow;
{
	struct vnode *vp;
	struct stat sb;
	register int error;
	register struct a {
		char	*fname;
		struct	stat *ub;
	} *uap = (struct a *)uap0;

	error =
	    lookupname(uap->fname, UIO_USERSPACE, follow,
		(struct vnode **)0, &vp);
#if DFSTRACE > 0
	if (error) { /* catch this case */
		if (traceon) dfs_log((follow == FOLLOW_LINK)?DFS_STAT:DFS_LSTAT, 
			     uap->fname, NULL, (u_char) error); 
		return (error);
	}
#else DFSTRACE
	if (error)
		return (error);
#endif DFSTRACE
	error = vno_stat(vp, &sb);
#if DFSTRACE > 0
	if (traceon) dfs_log((follow == FOLLOW_LINK)?DFS_STAT:DFS_LSTAT, 
			     uap->fname, vp, (u_char) error);
#endif DFSTRACE
	VN_RELE(vp);
	if (error)
		return (error);
	return (copyout((caddr_t)&sb, (caddr_t)uap->ub, sizeof (sb)));
}

/*
 * Read contents of symbolic link.
 */
readlink()
{
	register struct a {
		char	*name;
		char	*buf;
		int	count;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;
	struct iovec aiov;
	struct uio auio;

	u.u_error =
	    lookupname(uap->name, UIO_USERSPACE, NO_FOLLOW,
		(struct vnode **)0, &vp);
#if DFSTRACE > 0
	if (u.u_error) {  /* catch this case */
		if (traceon) dfs_log(DFS_READLINK, uap->name, NULL);
		return;
	}
#else DFSTRACE
	if (u.u_error)
		return;
#endif DFSTRACE
	if ((vp->v_mode&VFMT) != VLNK) {
		u.u_error = EINVAL;
		goto out;
	}
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->count;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_seg = UIO_USERSPACE;
	auio.uio_resid = uap->count;
	u.u_error = VOP_READLINK(vp, &auio, u.u_cred);
out:
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_READLINK, uap->name, vp);
#endif DFSTRACE
	VN_RELE(vp);
	u.u_r.r_val1 = uap->count - auio.uio_resid;
}

/*
 * Change mode of file given path name.
 */
chmod()
{
	register struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	struct vattr vattr;

	vattr_null(&vattr);
	vattr.va_mode = uap->fmode & 07777;
#if DFSTRACE > 0
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr, DFS_CHMOD);
#else DFSTRACE
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr);
#endif DFSTRACE
}

/*
 * Change mode of file given file descriptor.
 */
fchmod()
{
	register struct a {
		int	fd;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	struct vattr vattr;
#if	MACH_RFS
	struct file *fp;

	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		extern struct file *rfs_finode();

		(void) rfs_finode(fp);
		return;
	}
#endif	MACH_RFS

	vattr_null(&vattr);
	vattr.va_mode = uap->fmode & 07777;
	u.u_error = fdsetattr(uap->fd, &vattr);
}

/*
 * Change ownership of file given file name.
 */
chown()
{
	register struct a {
		char	*fname;
		int	uid;
		int	gid;
	} *uap = (struct a *)u.u_ap;
	struct vattr vattr;

	vattr_null(&vattr);
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
#if DFSTRACE > 0
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK,  &vattr, DFS_CHOWN);
#else DFSTRACE
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK,  &vattr);
#endif DFSTRACE
}

/*
 * Change ownership of file given file descriptor.
 */
fchown()
{
	register struct a {
		int	fd;
		int	uid;
		int	gid;
	} *uap = (struct a *)u.u_ap;
	struct vattr vattr;
#if	MACH_RFS
	struct file *fp;

	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		extern struct file *rfs_finode();

		(void) rfs_finode(fp);
		return;
	}
#endif	MACH_RFS
	vattr_null(&vattr);
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
	u.u_error = fdsetattr(uap->fd, &vattr);
}

/*
 * Set access/modify times on named file.
 */
utimes()
{
	register struct a {
		char	*fname;
		struct	timeval *tptr;
	} *uap = (struct a *)u.u_ap;
	struct timeval tv[2];
	struct vattr vattr;

	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error)
		return;
	vattr_null(&vattr);
	vattr.va_atime = tv[0];
	vattr.va_mtime = tv[1];
#if DFSTRACE > 0
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr, DFS_UTIMES);
#else DFSTRACE
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr);
#endif DFSTRACE
}

/*
 *  xutimes() - extended utimes() call to update inode creation time
 *
 *  This call is identical to the normal utimes() call except that it expects
 *  three elements in the time value array rather than two.  If the caller is
 *  privileged, the third element is used to set the inode creation time of the
 *  corresponding inode.  If the caller is not privileged, the operation
 *  performs the same funtion as the standard utimes() call to update only the
 *  access and modification times.
 */
xutimes()
{
	register struct a {
		char	*fname;
		struct	timeval *tptr;
	} *uap = (struct a *)u.u_ap;
	struct timeval tv[3];
	struct vattr vattr;

	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error)
		return;
	vattr_null(&vattr);
	vattr.va_atime = tv[0];
	vattr.va_mtime = tv[1];
	if (u.u_uid == 0)
		vattr.va_ctime = tv[2];
#if DFSTRACE > 0
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr, DFS_UNUSED);
#else DFSTRACE
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr);
#endif DFSTRACE
}

/*
 * Truncate a file given its path name.
 */
truncate()
{
	register struct a {
		char	*fname;
		int	length;
	} *uap = (struct a *)u.u_ap;
	struct vattr vattr;

	vattr_null(&vattr);
	vattr.va_size = uap->length;
#if DFSTRACE > 0
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr, DFS_TRUNCATE);
#else DFSTRACE
	u.u_error = namesetattr(uap->fname, FOLLOW_LINK, &vattr);
#endif DFSTRACE
}

/*
 * Truncate a file given a file descriptor.
 */
ftruncate()
{
	register struct a {
		int	fd;
		int	length;
	} *uap = (struct a *)u.u_ap;
	register struct vnode *vp;
	struct file *fp;

#if	MACH_RFS
	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		extern struct file *rfs_finode();

		(void) rfs_finode(fp);
		return;
	}
#endif	MACH_RFS
	u.u_error = getvnodefp(uap->fd, &fp);
	if (u.u_error)
		return;
	vp = (struct vnode *)fp->f_data;
	if ((fp->f_flag & FWRITE) == 0) {
		u.u_error = EINVAL;
	} else if (vp->v_vfsp->vfs_flag & VFS_RDONLY) {
		u.u_error = EROFS;
	} else {
		struct vattr vattr;

		vattr_null(&vattr);
		vattr.va_size = uap->length;
		u.u_error = VOP_SETATTR(vp, &vattr, fp->f_cred);
	}
}

/*
 * Common routine for modifying attributes
 * of named files.
 */
#if DFSTRACE > 0
namesetattr(fnamep, followlink, vap, opcode)
	char *fnamep;
	enum symfollow followlink;
	struct vattr *vap;
	u_char opcode;
#else DFSTRACE
namesetattr(fnamep, followlink, vap)
	char *fnamep;
	enum symfollow followlink;
	struct vattr *vap;
#endif DFSTRACE
{
	struct vnode *vp;
	register int error;

	error =
	    lookupname(fnamep, UIO_USERSPACE, followlink,
		 (struct vnode **)0, &vp);
#if DFSTRACE > 0
	if (error) {
		if (traceon) /* catch this case */
			dfs_log(opcode, DFS_POST, fnamep, NULL, vap, (u_char) error);
		return(error);	
	} else {
		if ((traceon)  && (opcode == DFS_TRUNCATE))  /* ugh. to get old size */
			dfs_log(DFS_TRUNCATE, 0, vp);
	}
#else DFSTRACE
	if (error)
		return(error);	
#endif DFSTRACE
	if(vp->v_vfsp->vfs_flag & VFS_RDONLY)
		error = EROFS;
	else
		error = VOP_SETATTR(vp, vap, u.u_cred);
#if DFSTRACE > 0
	if (traceon) dfs_log(opcode, DFS_POST, fnamep, vp, vap, (u_char) error);
#endif DFSTRACE
	VN_RELE(vp);
	return(error);
}

/*
 * Common routine for modifying attributes
 * of file referenced by descriptor.
 */
fdsetattr(fd, vap)
	int fd;
	struct vattr *vap;
{
	struct file *fp;
	register struct vnode *vp;
	register int error;

	error = getvnodefp(fd, &fp);
	if (error == 0) {
		vp = (struct vnode *)fp->f_data;
		if(vp->v_vfsp->vfs_flag & VFS_RDONLY)
			return(EROFS);
		error = VOP_SETATTR(vp, vap, fp->f_cred);
	}
	return(error);
}

/*
 * Flush output pending for file.
 */
fsync()
{
	struct a {
		int	fd;
	} *uap = (struct a *)u.u_ap;
	struct file *fp;
	int error;

#if	MACH_RFS
	GETF(fp, uap->fd);
	if (fp->f_type == DTYPE_RFSINO) {
		extern struct file *rfs_finode();

		(void) rfs_finode(fp);
		return;
	}
#endif	MACH_RFS
	error = getvnodefp(uap->fd, &fp);
#if	MACH_NBC
	if (error == 0)
		error = mfs_fsync((struct vnode *)fp->f_data);
#endif	MACH_NBC
	if (error == 0)
		error = VOP_FSYNC((struct vnode *)fp->f_data, fp->f_cred);
	u.u_error = error;
}

/*
 * Set file creation mask.
 */
umask()
{
	register struct a {
		int mask;
	} *uap = (struct a *)u.u_ap;
	u.u_r.r_val1 = u.u_cmask;
	u.u_cmask = uap->mask & 07777;
}

/*
 * Revoke access the current tty by all processes.
 * Used only by the super-user in init
 * to give ``clean'' terminals at login.
 */
vhangup()
{

	if (!suser())
		return;
	if (u.u_ttyp == NULL)
		return;
	ttydetach(u.u_ttyd, u.u_ttyp);
}

forceclose(dev)
	dev_t dev;
{
	register struct file *fp;
	register struct vnode *vp;

	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_count == 0)
			continue;
		if (fp->f_type != DTYPE_VNODE)
			continue;
		vp = (struct vnode *)fp->f_data;
		if (vp == 0)
			continue;
		if ((vp->v_mode&VFMT) != VCHR)
			continue;
		if (vp->v_rdev != dev)
			continue;
		fp->f_flag &= ~(FREAD|FWRITE);
	}
}

/*
 * Get the file structure entry for the file descrpitor, but make sure
 * its a vnode.
 */
int
getvnodefp(fd, fpp)
	int fd;
	struct file **fpp;
{
	register struct file *fp;

	fp = getf(fd);
	if (fp == (struct file *)0)
		return(EBADF);
	if (fp->f_type != DTYPE_VNODE)
		return(EINVAL);
	*fpp = fp;
	return(0);
}
