/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_io.c,v $
 * Revision 2.10  90/08/30  11:51:28  bohman
 * 	Ioctl changes for STDC.  Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.9  89/11/16  11:51:43  mja
 * 	Exchange uses of multiply/divide in FIOCFSPARM call to fix bug
 * 	in adjusting blocks sizes for file systems with a non-1K
 * 	fragment size.
 * 
 * Revision 2.8  89/08/02  08:12:20  jsb
 * 	Eliminated MACH conditionals.
 * 	[89/07/31  16:08:33  jsb]
 * 
 * Revision 2.7  89/05/11  15:40:34  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.6  89/05/11  14:45:01  gm0w
 * 	Added code to set FOKDIR if a TIOCGPGRP (really FGETOWN fcntl) is
 * 	done on a directory.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.5  89/04/22  15:34:28  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:44:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:13:13  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:25:52  jsb
 * 	Include file references; (stupidly) removed SUN_LOCK code;
 * 	MACH: allow reading of directories by calling VOP_READDIR on
 * 	directories in vno_rw, and by borrowing code from FAPPEND case to
 * 	preserve offset; add support for FIOCFSPARAM inode ioctl; in
 * 	vno_close, don't vn_close mounted file system;
 * 	MACH_RFS: add rfs support.
 * 	[89/01/17  16:00:22  jsb]
 * 
 *
 * 17-Oct-88  David Black (dlb) at Carnegie-Mellon University
 *	Don't close a block device vnode that's been mounted as a
 *	filesystem.
 *
 * 26-Oct-87 Peter King (king) at NeXT, Inc.
 *	Original Sun source.  Upgraded to Mach.
 */ 

#include <mach_rfs.h>
#include <mach_nbc.h>

/* @(#)vfs_io.c	1.1 87/06/02 3.2/4.3NFSSRC */
/*	@(#)vfs_io.c 1.1 86/09/25 SMI	*/

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/fs.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mount.h>

#if	MACH_NBC
#include <kern/mfs.h>
#endif	MACH_NBC

#define sigmask(m)	(1 << ((m)-1))

int vno_rw();
int vno_ioctl();
int vno_select();
int vno_close();

struct fileops vnodefops = {
	vno_rw,
	vno_ioctl,
	vno_select,
	vno_close
};

int
vno_rw(fp, rw, uiop)
	struct file *fp;
	enum uio_rw rw;
	struct uio *uiop;
{
	register struct vnode *vp;
	register int count;
	register int error;

	vp = (struct vnode *)fp->f_data;
	/*
	 * In write make sure filesystem is writable
	 */
	if ((rw == UIO_WRITE) && (vp->v_vfsp->vfs_flag & VFS_RDONLY))
		return(EROFS);
	count = uiop->uio_resid;
	if ((vp->v_mode&VFMT) == VREG) {
#if	MACH_NBC
		if (vp->v_vm_info->mapped) {
			error = mfs_io(vp, uiop, rw,
				((fp->f_flag & FAPPEND) != 0?
				    IO_APPEND|IO_UNIT: IO_UNIT), fp->f_cred);
		} else
#endif	MACH_NBC
		error =
		    VOP_RDWR(vp, uiop, rw,
			((fp->f_flag & FAPPEND) != 0?
			    IO_APPEND|IO_UNIT: IO_UNIT), fp->f_cred);
	} else if ((vp->v_mode&VFMT) == VDIR && rw == UIO_READ) {
#if	defined(mac2)
	  	error = EISDIR;
#else	defined(mac2)
		error = VOP_READ1DIR(vp, uiop, fp->f_cred);
#endif	defined(mac2)
#if	FIFOS
	} else if ((vp->v_mode&VFMT) == VFIFO) {
		/*
		 * NOTE: Kludge to ensure that FAPPEND stays set.
		 *       This ensures that fp->f_offset is always accurate.
		 */
		fp->f_flag |= FAPPEND;

		/* NOTE: Kludge to ensure 'no delay' bit passes thru */
		error =
		    VOP_RDWR(vp, uiop, rw,
			((fp->f_flag & FNDELAY) != 0?
			    IO_APPEND|IO_NDELAY: IO_APPEND), fp->f_cred);
#endif	FIFOS
	} else {
		error =
		    VOP_RDWR(vp, uiop, rw,
			((fp->f_flag & FAPPEND) != 0?
			    IO_APPEND: 0), fp->f_cred);
	}
	if (error)
		return(error);
	if (fp->f_flag & FAPPEND || (vp->v_mode&VFMT) == VDIR) {
		/*
		 * In both of these cases, we need to save the offset
		 * as set by VOP_RDWR (in the append case) or VOP_READDIR.
		 * We do this by preemptively undoing the computation
		 * performed by rwuio.
		 */
		fp->f_offset = uiop->uio_offset - (count - uiop->uio_resid);
	}
	return(0);
}

int
vno_ioctl(fp, com, data)
	struct file *fp;
	int com;
	caddr_t data;
{
	struct vattr vattr;
	struct vnode *vp;
	int error = 0;

	vp = (struct vnode *)fp->f_data;
#ifdef	__STDC__
	if (com == _IOW('f', 100, int))	/* FIOCXMOD */
#else
	if (com == _IOW(f, 100, int))	/* FIOCXMOD */
#endif
		return(0);
	if (com == FIOCFSPARAM)
	{
		extern struct vnodeops ufs_vnodeops;

		if (vp->v_type == ITYPE_UFS) {
			struct inode *ip = VTOI(vp);
			struct fs *fs = ip->i_fs;
			struct fsparam *fsp = (struct fsparam *)data;
			int i;

			fsp->fsp_free = freefrags(fs);
			fsp->fsp_size = fs->fs_dsize;
			if (fs->fs_fsize > 1024)
			{
				i = (fs->fs_fsize/1024);
				fsp->fsp_free *= i;
				fsp->fsp_size *= i;
			}
			else if (fs->fs_fsize < 1024)
			{
				i = (1024/fs->fs_fsize);
				fsp->fsp_free /= i;
				fsp->fsp_size /= i;
			}
			fsp->fsp_ifree   = freeinodes(fs);
			fsp->fsp_isize   = fs->fs_ncg*fs->fs_ipg;
			fsp->fsp_minfree = fs->fs_minfree;
			bzero((caddr_t)fsp->fsp_unused,
				sizeof(fsp->fsp_unused));
			return(0);
		} else {
			return(EINVAL);
		}
	}

	switch(vp->v_mode&VFMT) {

	case VREG:
		if (com == FIOCNOSPC)
		{
		    int i = (fp->f_flag&FNOSPC);

		    switch (*(int *)data)
		    {
			case FIOCNOSPC_ERROR:
			    fp->f_flag |=  FNOSPC;
			    break;
			case FIOCNOSPC_PAUSE:
			    fp->f_flag &= ~FNOSPC;
			    break;
			case FIOCNOSPC_SAME:
			    break;
			default:
			    return(EINVAL);
		    }
		    *(int *)data = i?FIOCNOSPC_ERROR:FIOCNOSPC_PAUSE;
		    return(0);
		}
	case VDIR:
#if	FIFOS
	case VFIFO:
#endif	FIFOS
		switch (com) {

		case FIONREAD:
			error = VOP_GETATTR(vp, &vattr, u.u_cred);
			if (error == 0)
				*(off_t *)data = vattr.va_size - fp->f_offset;
			break;

		case FIONBIO:
		case FIOASYNC:
			break;

		case TIOCGPGRP:
			fp->f_flag |= FOKDIR;
		default:
			error = ENOTTY;
			break;
		}
		break;

	case VCHR:
#if	STREAMS
	case VSTR:
#endif	STREAMS
		u.u_r.r_val1 = 0;
		if (setjmp(&u.u_qsave)) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
		} else {
			error = VOP_IOCTL(vp, com, data, fp->f_flag,fp->f_cred);
		}
		break;

	default:
		error = ENOTTY;
		break;
	}
	return (error);
}

int
vno_select(fp, flag)
	struct file *fp;
	int flag;
{
	struct vnode *vp;

	vp = (struct vnode *)fp->f_data;
	switch(vp->v_mode&VFMT) {

	case VCHR:
#if	STREAMS
	case VSTR:
#endif	STREAMS
#if	FIFOS
	case VFIFO:
#endif	FIFOS
		return (VOP_SELECT(vp, flag, fp->f_cred));

	default:
		/*
		 * Always selected
		 */
		return (1);
	}
}

int
vno_stat(vp, sb)
	register struct vnode *vp;
	register struct stat *sb;
{
	register int error;
	struct vattr vattr;

	error = VOP_GETATTR(vp, &vattr, u.u_cred);
	if (error)
		return (error);
	sb->st_mode = vattr.va_mode;
	sb->st_uid = vattr.va_uid;
	sb->st_gid = vattr.va_gid;
	sb->st_dev = vattr.va_fsid;
	sb->st_ino = vattr.va_nodeid;
	sb->st_nlink = vattr.va_nlink;
	sb->st_size = vattr.va_size;
	sb->st_blksize = vattr.va_blocksize;
	sb->st_atime = vattr.va_atime.tv_sec;
	sb->st_spare1 = 0;
	sb->st_mtime = vattr.va_mtime.tv_sec;
	sb->st_spare2 = 0;
	sb->st_ctime = vattr.va_ctime.tv_sec;
	sb->st_spare3 = 0;
	sb->st_rdev = (dev_t)vattr.va_rdev;
	sb->st_blocks = vattr.va_blocks;
	sb->st_spare4[0] = sb->st_spare4[1] = 0;
	return (0);
}

int
vno_close(fp)
	register struct file *fp;
{
	register struct vnode *vp;
	register struct file *ffp;
	register struct vnode *tvp;
	register u_short type;
	register dev_t dev;

	vp = (struct vnode *)fp->f_data;
	if (fp->f_flag & (FSHLOCK | FEXLOCK))
		vno_bsd_unlock(fp, (FSHLOCK | FEXLOCK));

	type = (vp->v_mode&VFMT);
	if ((type == VBLK) || (type == VCHR)) {
		/*
		 * check that another vnode for the same device isn't active.
		 * This is because the same device can be referenced by two
		 * different vnodes.
		 */
		dev = vp->v_rdev;
		for (ffp = file; ffp < fileNFILE; ffp++) {
			if (ffp == fp)
				continue;
			if (ffp->f_type != DTYPE_VNODE)		/* XXX */
				continue;
			if (ffp->f_count &&
			    (tvp = (struct vnode *)ffp->f_data) &&
			    tvp->v_rdev == dev && (tvp->v_mode&VFMT) == type) {
				VN_RELE(vp);
				return (0);
			}
		}
	}
	/* I have no idea how this ever worked without this code -dlb */
	if (type == VBLK) {
		register struct vfs *vfsp;
		extern struct vfsops ufs_vfsops;
		/*
		 * Check that device has not been mounted as a ufs filesystem.
		 * Closing such a device makes the filesystem go away.
		 */
		for (vfsp = rootvfs; vfsp; vfsp = vfsp->vfs_next) {
		    	if ((vfsp->vfs_op == &ufs_vfsops) &&
			    (((struct mount *)(vfsp->vfs_data))->m_dev
					== dev)) {
				VN_RELE(vp);
				return(0);
			}
		}
	}
	u.u_error = vn_close(vp, fp->f_flag);
	VN_RELE(vp);
	return (u.u_error);
}

/*
 * Place an advisory lock on an inode.
 *
 * NOTE: This is left for compatibility with the BSD flock() system call.
 *	 It is functionally superceded by the SystemV fcntl()/lockf()
 *	 mechanism, which has slightly different semantics, but works
 *	 in the network environment.
 */
int
vno_bsd_lock(fp, cmd)
	register struct file *fp;
	int cmd;
{
	register int priority;
	register struct vnode *vp;

	/*
	 * Avoid work.
	 */
	if ((fp->f_flag & FEXLOCK) && (cmd & LOCK_EX) ||
	    (fp->f_flag & FSHLOCK) && (cmd & LOCK_SH))
		return (0);

	priority = PLOCK;
	vp = (struct vnode *)fp->f_data;

	if ((cmd & LOCK_EX) == 0)
		priority++;
	if (setjmp(&u.u_qsave)) {
		if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
			return (EINTR);
		u.u_eosys = RESTARTSYS;
		return (0);
	}
	/*
	 * If there's a exclusive lock currently applied
	 * to the file, then we've gotta wait for the
	 * lock with everyone else.
	 */
again:
	while (vp->v_flag & VEXLOCK) {
		/*
		 * If we're holding an exclusive
		 * lock, then release it.
		 */
		if (fp->f_flag & FEXLOCK) {
			vno_bsd_unlock(fp, FEXLOCK);
			continue;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		vp->v_flag |= VLWAIT;
		(void) sleep((caddr_t)&vp->v_exlockc, priority);
	}
	if ((cmd & LOCK_EX) && (vp->v_flag & VSHLOCK)) {
		/*
		 * Must wait for any shared locks to finish
		 * before we try to apply a exclusive lock.
		 * If we're holding a shared
		 * lock, then release it.
		 */
		if (fp->f_flag & FSHLOCK) {
			vno_bsd_unlock(fp, FSHLOCK);
			goto again;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		vp->v_flag |= VLWAIT;
		(void) sleep((caddr_t)&vp->v_shlockc, PLOCK);
		goto again;
	}
	if (fp->f_flag & FEXLOCK)
		panic("vno_bsd_lock");
	if (cmd & LOCK_EX) {
		vp->v_exlockc++;
		vp->v_flag |= VEXLOCK;
		fp->f_flag |= FEXLOCK;
	}
	if ((cmd & LOCK_SH) && (fp->f_flag & FSHLOCK) == 0) {
		vp->v_shlockc++;
		vp->v_flag |= VSHLOCK;
		fp->f_flag |= FSHLOCK;
	}
	return (0);
}

/*
 * Unlock a file.
 *
 * NOTE: This is left for compatibility with the BSD flock() system call.
 *	 It is functionally superceded by the SystemV fcntl()/lockf()
 *	 mechanism, which has slightly different semantics, but works
 *	 in the network environment.
 */
int
vno_bsd_unlock(fp, kind)
	register struct file *fp;
	int kind;
{
	register struct vnode *vp;
	register int flags;

	vp = (struct vnode *)fp->f_data;
	kind &= fp->f_flag;
	if (vp == NULL || kind == 0)
		return;
	flags = vp->v_flag;
	if (kind & FSHLOCK) {
		if ((flags & VSHLOCK) == 0)
			panic("vno_bsd_unlock: SHLOCK");
		if (--vp->v_shlockc == 0) {
			vp->v_flag &= ~VSHLOCK;
			if (flags & VLWAIT)
				wakeup((caddr_t)&vp->v_shlockc);
		}
		fp->f_flag &= ~FSHLOCK;
	}
	if (kind & FEXLOCK) {
		if ((flags & VEXLOCK) == 0)
			panic("vno_bsd_unlock: EXLOCK");
		if (--vp->v_exlockc == 0) {
			vp->v_flag &= ~(VEXLOCK|VLWAIT);
			if (flags & VLWAIT)
				wakeup((caddr_t)&vp->v_exlockc);
		}
		fp->f_flag &= ~FEXLOCK;
	}
}
