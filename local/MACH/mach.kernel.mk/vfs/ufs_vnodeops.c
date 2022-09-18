/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ufs_vnodeops.c,v $
 * Revision 2.17  90/10/18  12:55:42  mrt
 * 	16-Oct-90 Bennet Yee (bsy) at Carnegie-Mellon University
 * 	Changed ufs_setattr to allow owner to set sticky bit on a 
 * 	directory.
 * 	[90/10/18  12:42:01  mrt]
 * 
 * Revision 2.16  90/02/09  12:34:06  berman
 * 	Added manipulation of u_VOPuid in ufs_rdwr() to carry the 
 * 	credentials down to the file system code in the u-area.
 * 	from jsb
 * 	[90/02/09            berman]
 * 
 * Revision 2.15  89/12/22  16:29:20  rpd
 * 	Fixed NBC typo in fast symlink code.
 * 	[89/12/01  13:54:29  rpd]
 * 
 * Revision 2.14  89/12/22  15:55:05  rpd
 * 	Fix fastlink code in rfs_make_symlink, and put under
 * 	MACH_FASTLINK switch.
 * 	[89/11/16            dlb]
 * 
 * Revision 2.13  89/10/10  11:02:19  mwyoung
 * 	Add the MACH_VFS form of rfs_make_symlink.
 * 	[89/05/14  22:37:54  mwyoung]
 * 
 * 	Make fast symbolic links an architecture-independent option.
 * 	[89/05/12  16:05:03  mwyoung]
 * 
 * Revision 2.12  89/10/03  19:27:56  rpd
 * 	Merged with my version at NeXT.  Summary:
 * 	Added ufs_nlinks.  Fixed EINVAL check in rwip.
 * 	Various NBC fixes.  Revamped ufs_page_read,
 * 	to be more efficient and use B_USELESS.
 * 	[89/10/02  16:09:09  rpd]
 * 
 * 	Fixed check for IC_FASTLINK in ufs_readlink.
 * 	When creating a fastlink in ufs_symlink, don't mark with IACC.
 * 	[89/09/08  16:46:32  rpd]
 * 
 * 	Fixed ufs_page_read to use unix_master/unix_release,
 * 	lock the inode, and mark it with IACC.
 * 	[89/08/21  03:01:10  rpd]
 * 
 * Revision 2.11  89/08/02  08:10:45  jsb
 * 	Eliminated MACH conditionals. Use zalloc instead of kalloc.
 * 	[89/07/31  15:58:32  jsb]
 * 
 * Revision 2.10  89/06/30  22:33:55  rpd
 * 	Fixed the ISVDEV macro.
 * 	[89/06/30  22:15:40  rpd]
 * 
 * Revision 2.9  89/06/25  00:00:37  jsb
 * 	This file didn't get merged in last time?
 * 	[89/06/24  23:27:18  jsb]
 * 
 * Revision 2.8.1.3  89/06/12  14:52:42  jsb
 * 	Replaced ufs_page_init routine with ufs_page_write.
 * 	[89/06/12  11:46:44  jsb]
 * 
 * Revision 2.8  89/05/11  14:44:44  gm0w
 * 	Added ufs_readdir entry for vn_read1dir vnodeop.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.7  89/05/06  15:43:19  rpd
 * 	From jsb: When checking for text-busy, use inode_uncache_try.
 * 
 * Revision 2.6  89/04/22  15:33:41  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	Added inode_pager VOP's for page_read and page_init.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  22:43:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:12:25  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/31  01:22:03  rpd
 * 	Added support for fast symbolic links (multimax only for now).
 * 	[88/10/14            dlb]
 * 
 * Revision 2.2  89/01/18  01:23:58  jsb
 * 	Include file references; eliminate incorrect type cast in ufs_setattr;
 * 	get rid of VPAGER conditionals.
 * 	[89/01/17  15:47:44  jsb]
 * 
 */

/* @(#)ufs_vnodeops.c	1.9 87/09/10 3.2/4.3NFSSRC */
/*	@(#)ufs_vnodeops.c 1.1 86/09/25 SMI	*/

#include <mach_fastlink.h>
#include <xpr_debug.h>
#include <mach_nbc.h>

#include <sys/param.h>
#include <mach/vm_param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <mach/boolean.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/fs.h>
#include <sys/mount.h>
#ifdef	QUOTA
#include <sys/quota.h>
#endif

#include <krpc/lockmgr.h>

#include <kern/xpr.h>
#include <kern/kalloc.h>
#include <kern/mfs.h>
#include <kern/parallel.h>

#define ISVDEV(t) (((t) == VCHR) || ((t) == VBLK))

zone_t ufs_fid_zone;

extern int ufs_open();
extern int ufs_close();
extern int ufs_rdwr();
extern int ufs_ioctl();
extern int ufs_select();
extern int ufs_getattr();
extern int ufs_setattr();
extern int ufs_access();
extern int ufs_lookup();
extern int ufs_create();
extern int ufs_remove();
extern int ufs_link();
extern int ufs_rename();
extern int ufs_mkdir();
extern int ufs_rmdir();
extern int ufs_readdir();
extern int ufs_symlink();
extern int ufs_readlink();
extern int ufs_fsync();
extern int ufs_inactive();
extern int ufs_bmap();
extern int ufs_badop();
extern int ufs_bread();
extern int ufs_brelse();
extern int ufs_lockctl();
extern int ufs_fid();
extern int ufs_page_read();
extern int ufs_page_write();
extern int ufs_freefid();
extern int ufs_nlinks();

struct vnode *specvp();

struct vnodeops ufs_vnodeops = {
	ufs_open,
	ufs_close,
	ufs_rdwr,
	ufs_ioctl,
	ufs_select,
	ufs_getattr,
	ufs_setattr,
	ufs_access,
	ufs_lookup,
	ufs_create,
	ufs_remove,
	ufs_link,
	ufs_rename,
	ufs_mkdir,
	ufs_rmdir,
	ufs_readdir,
	ufs_symlink,
	ufs_readlink,
	ufs_fsync,
	ufs_inactive,
	ufs_bmap,
	ufs_badop,
	ufs_bread,
	ufs_brelse,
	ufs_lockctl,
	ufs_fid,
	ufs_page_read,
	ufs_page_write,
	ufs_readdir,		/* read1dir */
	ufs_freefid,
	ufs_nlinks,
};

/*ARGSUSED*/
int
ufs_open(vpp, flag, cred)
	struct vnode **vpp;
	int flag;
	struct ucred *cred;
{
	return (0);
}

/*ARGSUSED*/
int
ufs_close(vp, flag, cred)
	struct vnode *vp;
	int flag;
	struct ucred *cred;
{
	return (0);
}

/*
 * read or write a vnode
 */
/*ARGSUSED*/
int
ufs_rdwr(vp, uiop, rw, ioflag, cred)
	struct vnode *vp;
	struct uio *uiop;
	enum uio_rw rw;
	int ioflag;
	struct ucred *cred;
{
	register struct inode *ip;
	int error;
	uid_t old_VOPuid = u.u_VOPuid;

	u.u_VOPuid = cred->cr_uid;
	ip = VTOI(vp);
	if ((ip->i_mode&IFMT) == IFREG) {
		ILOCK(ip);
		if ((ioflag & IO_APPEND) && (rw == UIO_WRITE)) {
			/*
			 * in append mode start at end of file.
			 */
			uiop->uio_offset = ip->i_size;
		}
		error = rwip(ip, uiop, rw, ioflag);
		IUNLOCK(ip);
	} else {
		error = rwip(ip, uiop, rw, ioflag);
	}
	u.u_VOPuid = old_VOPuid;
	return (error);
}

/*
 * Don't cache blocks in non-executable files with the sticky bit
 * set. Used to keep swap files from blowing the data cache
 */
int stickyhack = 1;
rwip(ip, uio, rw, ioflag)
	register struct inode *ip;
	register struct uio *uio;
	enum uio_rw rw;
	int ioflag;
{
	struct vnode *devvp;
	struct buf *bp;
	struct fs *fs;
	daddr_t lbn, bn;
	register int n, on, type;
	int size;
	long bsize;
	extern int mem_no;
	int error = 0;
	int iupdat_flag = 0;		/* delayed update */
	u_short execmask = (IEXEC | (IEXEC >> 3) | (IEXEC >> 6));

	if (rw != UIO_READ && rw != UIO_WRITE)
		panic("rwip");
	if (rw == UIO_READ && uio->uio_resid == 0)
		return (0);
	if (((int) uio->uio_offset < 0 ||
	     (int) (uio->uio_offset + uio->uio_resid) < 0))
		return (EINVAL);
	if (rw == UIO_READ)
		imark(ip, IACC);
	if (uio->uio_resid == 0)
		return (0);
	type = ip->i_mode&IFMT;
	if (type == IFCHR || type == IFBLK) {
		panic("rwip dev inode");
	}
	if (rw == UIO_WRITE && type == IFREG &&
	    uio->uio_offset + uio->uio_resid >
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(u.u_procp, SIGXFSZ);
		return (EFBIG);
	}
	devvp = ITOV(ip->i_devp);
	fs = ip->i_fs;
	bsize = fs->fs_bsize;
	u.u_error = 0;
	do {
		lbn = uio->uio_offset / bsize;
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uio->uio_resid);
		if (rw == UIO_READ) {
			int diff = ip->i_size - uio->uio_offset;
			if (diff <= 0)
				return (0);
			if (diff < n)
				n = diff;
		}
		bn =
		    fsbtodb(fs, bmap(ip, lbn,
			 rw == UIO_WRITE ? B_WRITE: B_READ,
			 (int)(on+n),
			 (ioflag & IO_SYNC ? &iupdat_flag : 0) ));
		if (u.u_error || rw == UIO_WRITE && (long)bn<0)
			return (u.u_error);
		if (rw == UIO_WRITE &&
		   (uio->uio_offset + n > ip->i_size) &&
		   (type == IFDIR || type == IFREG || type == IFLNK)) {
			ip->i_size = uio->uio_offset + n;
			if (ioflag & IO_SYNC) {
				iupdat_flag = 1;
			}
		}
		size = blksize(fs, ip, lbn);
		if (rw == UIO_READ) {
			if ((long)bn<0) {
				bp = geteblk(size);
				clrbuf(bp);
			} else if (ip->i_lastr + 1 == lbn)
				bp = breada(devvp, bn, size, rablock, rasize);
			else
				bp = bread(devvp, bn, size);
			ip->i_lastr = lbn;
		} else {
			if (ip->i_vm_info->pager != MEMORY_OBJECT_NULL)
			        inode_uncache(ITOV(ip));
			if (n == bsize) 
				bp = getblk(devvp, bn, size);
			else
				bp = bread(devvp, bn, size);
		}
		n = MIN(n, bp->b_bcount - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			error = EIO;
			brelse(bp);
			goto bad;
		}
		u.u_error = uiomove(bp->b_un.b_addr+on, n, rw, uio);
		if ((ioflag & IO_SYNC) && (ip->i_mode & ISVTX) && stickyhack
		  && (ip->i_mode & execmask) == 0)
		      bp->b_flags |= B_NOCACHE;
		if (rw == UIO_READ) {
			if (n + on == bsize || uio->uio_offset == ip->i_size)
				bp->b_flags |= B_AGE;
			brelse(bp);
		} else {
			if ((ioflag & IO_SYNC) || (ip->i_mode&IFMT) == IFDIR)
				bwrite(bp);
			else if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
			imark(ip, IUPD|ICHG);
			if (u.u_ruid != 0)
				ip->i_mode &= ~(ISUID|ISGID);
		}
	} while (u.u_error == 0 && uio->uio_resid > 0 && n != 0);
	if (iupdat_flag) {
		iupdat(ip, &time, &time, 1);
	}
	if (error == 0)				/* XXX */
		error = u.u_error;		/* XXX */
bad:
	return (error);
}

/*ARGSUSED*/
int
ufs_ioctl(vp, com, data, flag, cred)
	struct vnode *vp;
	int com;
	caddr_t data;
	int flag;
	struct ucred *cred;
{
	return (EINVAL);
}

/*ARGSUSED*/
int
ufs_select(vp, which, cred)
	struct vnode *vp;
	int which;
	struct ucred *cred;
{
	return (EINVAL);
}

/*ARGSUSED*/
int
ufs_getattr(vp, vap, cred)
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	register struct inode *ip;

	ip = VTOI(vp);
	/*
	 * Copy from inode table.
	 */
	vap->va_mode = ip->i_mode;
	vap->va_uid = ip->i_uid;
	vap->va_gid = ip->i_gid;
	vap->va_fsid = ip->i_dev;
	vap->va_nodeid = ip->i_number;
	vap->va_nlink = ip->i_nlink;
#if	MACH_NBC
	if ((vp->v_mode&VFMT) == VREG)
		vap->va_size = ip->i_vm_info->inode_size;
	else
#endif	MACH_NBC
	vap->va_size = ip->i_size;
	vap->va_atime.tv_sec = ip->i_atime;
	vap->va_atime.tv_usec = 0;
	vap->va_mtime.tv_sec = ip->i_mtime;
	vap->va_mtime.tv_usec = 0;
	vap->va_ctime.tv_sec = ip->i_ctime;
	vap->va_ctime.tv_usec = 0;
	vap->va_rdev = ip->i_rdev;
	vap->va_blocks = ip->i_blocks;
	switch(ip->i_mode & IFMT) {

	case IFBLK:
		vap->va_blocksize = BLKDEV_IOSIZE;
		break;

	case IFCHR:
		vap->va_blocksize = MAXBSIZE;
		break;

	default:
		vap->va_blocksize = vp->v_vfsp->vfs_bsize;
		break;
	}
	return (0);
}

int
ufs_setattr(vp, vap, cred)
	register struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	register struct inode *ip;
	int chtime = 0;
	int error = 0;

	/*
	 * cannot set these attributes
	 */
	if ((vap->va_nlink != -1) || (vap->va_blocksize != -1) ||
	    (vap->va_rdev != -1) || (vap->va_blocks != -1) ||
	    (vap->va_fsid != -1) || (vap->va_nodeid != -1)) {
		return (EINVAL);
	}

	ip = VTOI(vp);
	ilock(ip);
	/*
	 * Change file access modes. Must be owner or su.
	 */
	if (vap->va_mode != (u_short)-1) {
		error = OWNER(cred, ip);
		if (error)
			goto out;
		ip->i_mode &= IFMT;
		ip->i_mode |= vap->va_mode & ~IFMT;
		if (cred->cr_uid != 0) {
			if ((ip->i_mode & IFMT) != IFDIR)
				ip->i_mode &= ~ISVTX;
			if (!groupmember(ip->i_gid))
				ip->i_mode &= ~ISGID;
		}
		imark(ip, ICHG);
		if ((vp->v_flag & VTEXT) && ((ip->i_mode & ISVTX) == 0)) {
			if (ip->i_vm_info->pager != MEMORY_OBJECT_NULL)
			        inode_uncache(ITOV(ip));
		}
	}
	/*
	 * To change file ownership, must be su.
	 * To change group ownership, must be su or owner and in target group.
	 * This is now enforced in chown1() below.
	 */
	/* va_uid and va_gid are short, not unsigned (ie uid_t and gid_t) */
	if ((vap->va_uid != -1) || (vap->va_gid != -1)) {
		error = chown1(ip, vap->va_uid, vap->va_gid);
		if (error)
			goto out;
	}
	/*
	 * Truncate file. Must have write permission and not be a directory.
	 */
	if (vap->va_size != (u_long)-1) {
		if ((ip->i_mode & IFMT) == IFDIR) {
			error = EISDIR;
			goto out;
		}
		if (iaccess(ip, IWRITE)) {
			error = u.u_error;
			goto out;
		}
		itrunc(ip, vap->va_size);
	}
#if	MACH_NBC
	/*
	 *	Sync out all blocks to prevent delayed writes from
	 *	changing the modified time later.  Need to unlock
	 *	the inode so the pager can page out the pages... this
	 *	is a bit hokey but we'll fix it when we fix
	 *	the rest of the filesystem.
	 */
	iunlock(ip);
	(void) mfs_fsync(vp);
	ilock(ip);
#endif	MACH_NBC
	/*
	 * Change file access or modified times.
	 */
	if (vap->va_atime.tv_sec != -1) {
		error = OWNER(cred, ip);
		if (error)
			goto out;
		ip->i_atime = vap->va_atime.tv_sec;
		chtime++;
	}
	if (vap->va_mtime.tv_sec != -1) {
		error = OWNER(cred, ip);
		if (error)
			goto out;
		ip->i_mtime = vap->va_mtime.tv_sec;
		chtime++;
	}
	if (chtime) {
		ip->i_flag |= IACC|IUPD|ICHG;
		ip->i_ctime = time.tv_sec;
	}
out:
	iupdat(ip, &time, &time, 1);	/* XXX should be asyn for perf */
	iunlock(ip);
	return (error);
}

/*
 * Perform chown operation on inode ip;
 * inode must be locked prior to call.
 */
chown1(ip, uid, gid)
	register struct inode *ip;
	register uid_t uid;
	gid_t gid;
{
#ifdef	QUOTA
	register long change;
#endif

	if (uid == (uid_t) -1)
		uid = ip->i_uid;
	if (gid == (gid_t) -1)
		gid = ip->i_gid;

	if ((uid == ip->i_uid) && (gid == ip->i_gid))
		return(0);      /* no change at all */

	/* error if not super-user and:
	 *	1) trying to change owner
	 *	2) not current owner
	 *	3) new group is not a member of process group set
	 */
	if ( (u.u_uid != 0) &&
	    ((uid != ip->i_uid) || (u.u_uid != uid) || (!groupmember(gid))) ) {
		return(EPERM);
	}

#ifdef	QUOTA
	if (ip->i_uid == uid)		/* this just speeds things a little */
		change = 0;
	else
		change = ip->i_blocks;
	(void) chkdq(ip, -change, 1);
	(void) chkiq(VFSTOM(ip->i_vnode.v_vfsp), ip, ip->i_uid, 1);
	dqrele(ip->i_dquot);
#endif
	ip->i_uid = uid;
	ip->i_gid = gid;
	imark(ip, ICHG);
	if (u.u_uid != 0)
		ip->i_mode &= ~(ISUID|ISGID);
#ifdef	QUOTA
	ip->i_dquot = getinoquota(ip);
	(void) chkdq(ip, change, 1);
	(void) chkiq(VFSTOM(ip->i_vnode.v_vfsp), (struct inode *)NULL, uid, 1);
	return (u.u_error);		/* should == 0 ALWAYS !! */
#else
	return (0);
#endif
}

/*ARGSUSED*/
int
ufs_access(vp, mode, cred)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
{
	register struct inode *ip;
	int error;

	ip = VTOI(vp);
	ilock(ip);
	error = iaccess(ip, mode);
	iunlock(ip);
	return (error);
}

/*ARGSUSED*/
int
ufs_readlink(vp, uiop, cred)
	struct vnode *vp;
	struct uio *uiop;
	struct ucred *cred;
{
	register struct inode *ip;
	register int error;

	if ((vp->v_mode&VFMT) != VLNK)
		return (EINVAL);
	ip = VTOI(vp);
	ilock(ip);
#if	MACH_FASTLINK
	/*
	 *	Handle fast symbolic links
	 */
	if (((ip->i_icflags & IC_FASTLINK) != 0) && use_fastlinks) {
		error = uiomove(ip->i_symlink, ip->i_size, UIO_READ, uiop);
		imark(ip, IACC);
	}
	else {
		error = rwip(ip, uiop, UIO_READ, 0);
	}
#else	MACH_FASTLINK
	error = rwip(ip, uiop, UIO_READ, 0);
#endif	MACH_FASTLINK
	iunlock(ip);
	return (error);
}

/*ARGSUSED*/
int
ufs_fsync(vp, cred)
	struct vnode *vp;
	struct ucred *cred;
{
	register struct inode *ip;

	ip = VTOI(vp);
	ilock(ip);
	syncip(ip);
	iunlock(ip);
	return (0);
}

/*ARGSUSED*/
int
ufs_inactive(vp, cred)
	struct vnode *vp;
	struct ucred *cred;
{

	irele(VTOI(vp));
	return (0);
}

/*
 * Unix file system operations having to do with directory manipulation.
 */
/*ARGSUSED*/
ufs_lookup(dvp, nm, vpp, cred)
	struct vnode *dvp;
	char *nm;
	struct vnode **vpp;
	struct ucred *cred;
{
	struct inode *ip;
	register int error;

	error = dirlook(VTOI(dvp), nm, &ip);
	if (error == 0) {
		*vpp = ITOV(ip);
		iunlock(ip);
		/*
		 * If vnode is a device return special vnode instead
		 */
		if (ISVDEV(((*vpp)->v_mode&VFMT))) {
			struct vnode *newvp;

			newvp = specvp(*vpp, (*vpp)->v_rdev);
			VN_RELE(*vpp);
			*vpp = newvp;
		}
	}
	return (error);
}

ufs_create(dvp, nm, vap, exclusive, mode, vpp, cred)
	struct vnode *dvp;
	char *nm;
	struct vattr *vap;
	enum vcexcl exclusive;
	int mode;
	struct vnode **vpp;
	struct ucred *cred;
{
	register int error;
	struct inode *ip;

	/*
	 * can't create directories. use ufs_mkdir.
	 */
	if ((vap->va_mode&IFMT) == VDIR)
		return (EISDIR);
	ip = (struct inode *) 0;
	error = direnter(VTOI(dvp), nm, DE_CREATE,
		(struct inode *)0, (struct inode *)0, vap, &ip);
	/*
	 * if file exists and this is a nonexclusive create,
	 * check for not directory and access permissions
	 * If create/read-only an existing directory, allow it.
	 */
	if (error == EEXIST) {
		if (exclusive == NONEXCL) {
			if (((ip->i_mode & IFMT) == IFDIR) && (mode & IWRITE)) {
				error = EISDIR;
			} else if (mode) {
				error = iaccess(ip, mode);
			} else {
				error = 0;
			}
		}
		if (error) {
			iput(ip);
		} else if (((ip->i_mode&IFMT) == IFREG) && (vap->va_size == 0)){
			/*
			 * truncate regular files, if required
			 */
			itrunc(ip, (u_long) 0);
		}
	} 
	if (error) {
		return (error);
	}
	*vpp = ITOV(ip);
	iunlock(ip);
	/*
	 * If vnode is a device return special vnode instead
	 */
	if (ISVDEV(((*vpp)->v_mode&VFMT))) {
		struct vnode *newvp;

		newvp = specvp(*vpp, (*vpp)->v_rdev);
		VN_RELE(*vpp);
		*vpp = newvp;
	}

	if (vap != (struct vattr *)0) {
		(void) VOP_GETATTR(*vpp, vap, cred);
	}
	return (error);
}

/*ARGSUSED*/
ufs_remove(vp, nm, cred)
	struct vnode *vp;
	char *nm;
	struct ucred *cred;
{
	register int error;

	error = dirremove(VTOI(vp), nm, (struct inode *)0, 0);
	return (error);
}

/*
 * link a file or a directory
 * If source is a directory, must be superuser
 */
/*ARGSUSED*/
ufs_link(vp, tdvp, tnm, cred)
	struct vnode *vp;
	struct vnode *tdvp;
	char *tnm;
	struct ucred *cred;
{
	register struct inode *sip;
	register int error;

	sip = VTOI(vp);
	if (((sip->i_mode & IFMT) == IFDIR) && !suser()) {
		return (EPERM);
	}
	error =
	    direnter(VTOI(tdvp), tnm, DE_LINK,
		(struct inode *)0, sip, (struct vattr *)0, (struct inode **)0);
	return (error);
}

/*
 * Rename a file or directory
 * We are given the vnode and entry string of the source and the
 * vnode and entry string of the place we want to move the source to
 * (the target). The essential operation is:
 *	unlink(target);
 *	link(source, target);
 *	unlink(source);
 * but "atomically". Can't do full commit without saving state in the inode
 * on disk, which isn't feasible at this time. Best we can do is always
 * guarantee that the TARGET exists.
 */
/*ARGSUSED*/
ufs_rename(sdvp, snm, tdvp, tnm, cred)
	struct vnode *sdvp;		/* old (source) parent vnode */
	char *snm;			/* old (source) entry name */
	struct vnode *tdvp;		/* new (target) parent vnode */
	char *tnm;			/* new (target) entry name */
	struct ucred *cred;
{
	struct inode *sip;		/* source inode */
	register struct inode *sdp;	/* old (source) parent inode */
	register struct inode *tdp;	/* new (target) parent inode */
	register int error;

	sdp = VTOI(sdvp);
	tdp = VTOI(tdvp);
	/*
	 * make sure we can delete the source entry
	 */
	error = iaccess(sdp, IWRITE);
	if (error) {
		return (error);
	}
	/*
	 * look up inode of file we're supposed to rename.
	 */
	error = dirlook(sdp, snm, &sip);
	if (error) {
		return (error);
	}

	iunlock(sip);			/* unlock inode (it's held) */
	/*
	 * check for renaming '.' or '..' or alias of '.'
	 */
	if ((strcmp(snm, ".") == 0) || (strcmp(snm, "..") == 0) ||
	    (sdp == sip)) {
		error = EINVAL;
		goto out;
	}
	/*
	 * link source to the target
	 */
	error =
	    direnter(tdp, tnm, DE_RENAME,
		sdp, sip, (struct vattr *)0, (struct inode **)0);
	if (error)
		goto out;

	/*
	 * Unlink the source
	 * Remove the source entry. Dirremove checks that the entry
	 * still reflects sip, and returns an error if it doesn't.
	 * If the entry has changed just forget about it. 
	 * Release the source inode.
	 */
	error = dirremove(sdp, snm, sip, 0);
	if (error == ENOENT) {
		error = 0;
	} else if (error) {
		goto out;
	}

out:
	irelease(sip);
	return (error);
}

/*ARGSUSED*/
ufs_mkdir(dvp, nm, vap, vpp, cred)
	struct vnode *dvp;
	char *nm;
	register struct vattr *vap;
	struct vnode **vpp;
	struct ucred *cred;
{
	struct inode *ip;
	register int error;

	error =
	    direnter(VTOI(dvp), nm, DE_CREATE,
		(struct inode *)0, (struct inode *)0, vap, &ip);
	if (error == 0) {
		*vpp = ITOV(ip);
		iunlock(ip);
	} else if (error == EEXIST) {
		iput(ip);
	}
	return (error);
}

/*ARGSUSED*/
ufs_rmdir(vp, nm, cred)
	struct vnode *vp;
	char *nm;
	struct ucred *cred;
{
	register int error;

	error = dirremove(VTOI(vp), nm, (struct inode *)0, 1);
	return (error);
}

/*ARGSUSED*/
ufs_readdir(vp, uiop, cred)
	struct vnode *vp;
	register struct uio *uiop;
	struct ucred *cred;
{
	register struct iovec *iovp;
	register unsigned count;

	iovp = uiop->uio_iov;
	count = iovp->iov_len;
	if ((uiop->uio_iovcnt != 1) || (count < DIRBLKSIZ) ||
	    (uiop->uio_offset & (DIRBLKSIZ -1)))
		return (EINVAL);
	count &= ~(DIRBLKSIZ - 1);
	uiop->uio_resid -= iovp->iov_len - count;
	iovp->iov_len = count;
	return (rwip(VTOI(vp), uiop, UIO_READ, 0));
}

/*ARGSUSED*/
ufs_symlink(dvp, lnm, vap, tnm, cred)
	struct vnode *dvp;
	char *lnm;
	struct vattr *vap;
	char *tnm;
	struct ucred *cred;
{
	struct inode *ip;
	register int error;
#if	MACH_FASTLINK
	register int	len;
#endif	MACH_FASTLINK

	ip = (struct inode *) 0;
	vap->va_mode &= ~IFMT;
	vap->va_mode |= VLNK;
	vap->va_rdev = 0;
	error =
	    direnter(VTOI(dvp), lnm, DE_CREATE,
		(struct inode *)0, (struct inode *)0, vap, &ip);
	if (error == 0) {
#if	MACH_FASTLINK
	    if (create_fastlinks) {
		/*
		 *	Make a fast link if name fits.
		 */
		len = strlen(tnm);
		if (len <= MAX_FASTLINK_SIZE) {
		    bcopy(tnm, ip->i_symlink, len);
		    ip->i_size = len;
#if	MACH_NBC
		    /* for stat */
		    ip->i_vm_info->inode_size = len;
#endif	MACH_NBC
		    ip->i_icflags |= IC_FASTLINK;
		    imark(ip, IUPD|ICHG);
		}
		else {
			error = rdwri(UIO_WRITE, ip,
				tnm, len, 0, UIO_SYSSPACE, (int *)0);
		}
	    } else
#endif	MACH_FASTLINK
		error =
		    rdwri(UIO_WRITE, ip,
			tnm, strlen(tnm), 0, UIO_SYSSPACE, (int *)0);
		iput(ip);
	} else if (error == EEXIST) {
		iput(ip);
	}
	return (error);
}

#if	MACH_NBC
/*
 * Version of rdwri with ioflag passed on:
 */
ufs_rdwri(rw, ip, base, len, offset, seg, ioflag, aresid)
	enum uio_rw rw;
	struct inode *ip;
	caddr_t base;
	int len;
	int offset;
	int seg;
	int ioflag;
	int *aresid;
{
	struct uio auio;
	struct iovec aiov;
	register int error;

	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = offset;
	auio.uio_segflg = seg;
	auio.uio_resid = len;
	error = ufs_rdwr(ITOV(ip), &auio, rw, ioflag, u.u_cred);
	if (aresid) {
		*aresid = auio.uio_resid;
	} else if (auio.uio_resid) {
	    	if (error == 0)	error = EIO;
	}
	return (error);
}
#endif	MACH_NBC

rdwri(rw, ip, base, len, offset, seg, aresid)
	enum uio_rw rw;
	struct inode *ip;
	caddr_t base;
	int len;
	int offset;
	int seg;
	int *aresid;
{
	struct uio auio;
	struct iovec aiov;
	register int error;

	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = offset;
	auio.uio_segflg = seg;
	auio.uio_resid = len;
	error = ufs_rdwr(ITOV(ip), &auio, rw, 0, u.u_cred);
	if (aresid) {
		*aresid = auio.uio_resid;
	} else if (auio.uio_resid) {
		error = EIO;
	}
	return (error);
}

int
ufs_bmap(vp, lbn, vpp, bnp)
	struct vnode *vp;
	daddr_t lbn;
	struct vnode **vpp;
	daddr_t *bnp;
{
	register struct inode *ip;

	ip = VTOI(vp);
	if (vpp)
		*vpp = ITOV(ip->i_devp);
	if (bnp)
		*bnp = fsbtodb(ip->i_fs, bmap(ip, lbn, B_READ));
	return (0);
}

/*
 * read a logical block and return it in a buffer
 */
/*ARGSUSED*/
int
ufs_bread(vp, lbn, bpp, sizep)
	struct vnode *vp;
	daddr_t lbn;
	struct buf **bpp;
	long *sizep;
{
	register struct inode *ip;
	register struct buf *bp;
	register daddr_t bn;
	register int size;

	ip = VTOI(vp);
	size = blksize(ip->i_fs, ip, lbn);
	bn = fsbtodb(ip->i_fs, bmap(ip, lbn, B_READ));
	if ((long)bn < 0) {
		bp = geteblk(size);
		clrbuf(bp);
	} else if (ip->i_lastr + 1 == lbn) {
		bp = breada(ip->i_devp, bn, size, rablock, rasize);
	} else {
		bp = bread(ip->i_devp, bn, size);
	}
	ip->i_lastr = lbn;
	imark(ip, IACC);
	if (bp->b_flags & B_ERROR) {
		brelse(bp);
		return (EIO);
	} else {
		*bpp = bp;
		return (0);
	}
}

/*
 * release a block returned by ufs_bread
 */
/*ARGSUSED*/
ufs_brelse(vp, bp)
	struct vnode *vp;
	struct buf *bp;
{
	bp->b_flags |= B_AGE;
	bp->b_resid = 0;
	brelse(bp);
}

int
ufs_badop()
{
	panic("ufs_badop");
}

#if	SUN_LOCK
/*
 * Record-locking requests are passed to the local Lock-Manager daemon.
 */
int
ufs_lockctl(vp, ld, cmd, cred)
	struct vnode *vp;
	struct flock *ld;
	int cmd;
	struct ucred *cred;
{
	lockhandle_t lh;
	struct fid *fidp;

	/* Convert vnode into lockhandle-id. This is awfully like makefh(). */
	if (VOP_FID(vp, &fidp) || fidp == NULL) {
		return (EINVAL);
	}
	bzero((caddr_t)&lh.lh_id, sizeof (lh.lh_id));	/* clear extra bytes */
	lh.lh_fsid.val[0] = vp->v_vfsp->vfs_fsid.val[0];
	lh.lh_fsid.val[1] = vp->v_vfsp->vfs_fsid.val[1];
	lh.lh_fid.fid_len = fidp->fid_len;
	bcopy(fidp->fid_data, lh.lh_fid.fid_data, fidp->fid_len);
	freefid(fidp);

	/* Add in vnode and server and call to common code */
	lh.lh_vp = vp;
	lh.lh_servername = hostname;
	return (klm_lockctl(&lh, ld, cmd, cred));
}
#else	SUN_LOCK
int
ufs_lockctl()
{
    return(EINVAL);
}
#endif	SUN_LOCK

ufs_fid(vp, fidpp)
	struct vnode *vp;
	struct fid **fidpp;
{
	register struct ufid *ufid;

	ZALLOC(ufs_fid_zone, ufid, struct ufid *);
	bzero((caddr_t)ufid, sizeof(struct ufid));
	ufid->ufid_len = sizeof(struct ufid) - (sizeof(struct fid) - MAXFIDSZ);
	ufid->ufid_ino = VTOI(vp)->i_number;
	ufid->ufid_gen = VTOI(vp)->i_gen;
	*fidpp = (struct fid *)ufid;
	return (0);
}

ufs_freefid(vp, fidp)
	struct vnode *vp;
	struct fid *fidp;
{
	ZFREE(ufs_fid_zone, fidp);
	return (0);
}

/*
 * Check mode permission on inode.
 * Mode is READ, WRITE or EXEC.
 * In the case of WRITE, the
 * read-only status of the file
 * system is checked.
 * Also in WRITE, prototype text
 * segments cannot be written.
 * The mode is shifted to select
 * the owner/group/other fields.
 * The super user is granted all
 * permissions.
 */
iaccess(ip, m)
	register struct inode *ip;
	register int m;
{
	register gid_t *gp;

	if (m & IWRITE) {
		/*
		 * Disallow write attempts on read-only
		 * file systems; unless the file is a block
		 * or character device resident on the
		 * file system.
		 */
		if (ip->i_fs->fs_ronly != 0) {
			if ((ip->i_mode & IFMT) != IFCHR &&
			    (ip->i_mode & IFMT) != IFBLK) {
				u.u_error = EROFS;
				return (EROFS);
			}
		}
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
		if ((ip->i_flag & ITEXT) && !inode_uncache_try(ip)) {
			u.u_error = ETXTBSY;
			return (ETXTBSY);
		}
	}
	/*
	 * If you're the super-user,
	 * you always get access.
	 */
	if (u.u_uid == 0)
		return (0);
	/*
	 * Access check is based on only
	 * one of owner, group, public.
	 * If not owner, then check group.
	 * If not a member of the group, then
	 * check public access.
	 */
	if (u.u_uid != ip->i_uid) {
		m >>= 3;
		if (u.u_gid == ip->i_gid)
			goto found;
		gp = u.u_groups;
		for (; gp < &u.u_groups[NGROUPS] && *gp != NOGROUP; gp++)
			if (ip->i_gid == *gp)
				goto found;
		m >>= 3;
	}
found:
	if ((ip->i_mode & m) == m)
		return (0);
	u.u_error = EACCES;
	return (EACCES);
}

int	inode_read_aheads = 0;
int	inode_read_individuals = 0;

ufs_page_read(vp, buffer, size, offset, cred)
	struct vnode *vp;
	caddr_t buffer;
	int size;
	vm_offset_t offset;
	struct ucred *cred;
{
	register struct inode *ip = VTOI(vp);
	INODE_DEV_TYPE devvp;	/* vnode for block IO */
	struct fs *fs;		/* filesystem */
	int bsize;		/* size of logical blocks */
	int limit;		/* can't read more bytes than this */
	int amount;		/* bytes left to read */
	int sofar;		/* bytes read so far */
	int error;		/* our error return */

	u.u_error = 0;		/* bmap returns errors in this */
	error = EINVAL;		/* initially, no data read */

	ilock(ip);
	imark(ip, IACC);

	/*
	 *	Check that we are trying to read data that
	 *	lies within the file.
	 */

	limit = ip->i_size - offset;
	if ((limit <= 0) || (size <= 0))
		goto done;

	devvp = INODE_DEV(ip);
	fs = ip->i_fs;
	bsize = fs->fs_bsize;

	sofar = 0;
	amount = (size <= limit) ? size : limit;

	do {
		daddr_t lbn;	/* logical block where our data lies */
		int on;		/* byte offset within that logical block */
		daddr_t bn;	/* disk block where our data lies */
		int n;		/* the number of bytes read this time */

		/*
		 *	Find block and offset within it for our data.
		 */

		lbn = lblkno(fs, offset);
		on  = blkoff(fs, offset);

		/*
		 *	Don't read beyond the end of a logical block.
		 *	We handle logical blocks one at a time.
		 */

		n = MIN(bsize - on, amount);

		/*
		 *	Convert the logical block number into
		 *	a disk block, via bmap magic.
		 */

		bn = fsbtodb(fs, BMAP(ip, lbn, B_READ, 0));

		if (u.u_error) {
			vp->v_vm_info->error = error = u.u_error;
			printf("error %d on pagein (bmap)\n", error);
			error = EIO;
			goto done;
		}

		if ((long)bn < 0) {
			/*
			 *	The file has a hole in it; we should
			 *	return zeros.  However, only bother
			 *	to actually zero the buffer if it
			 *	has good data in it.
			 */

			if (error == 0)
				bzero(buffer + sofar, n);
		} else {
			int fsize;	/* size of fragment/block */
			struct buf *bp;	/* our buffer with the data */

			/*
			 *	We might be reading from a fragment
			 *	instead of a full block.
			 */

			fsize = blksize(fs, ip, lbn);
			n = MIN(n, fsize);

			/*
			 *	If we're doing sequential IO, try
			 *	read-ahead using rablock/rasize from bmap.
			 */

			if ((ip->i_lastr + 1) == lbn) {
				inode_read_aheads++;
				bp = breada(devvp, bn, fsize, rablock, rasize);
			} else {
				inode_read_individuals++;
				bp = bread(devvp, bn, fsize);
			}
			ip->i_lastr = lbn;

			if (bp->b_flags & B_ERROR) {
				vp->v_vm_info->error = error = geterror(bp);
				brelse(bp);
				printf("error %d on pagein (bread)\n", error);
				error = EIO;
				goto done;
			}

			assert(bp->b_resid == 0);
			assert(bp->b_bcount == fsize);

			bcopy(bp->b_un.b_addr+on, buffer + sofar, n);
			bp->b_flags |= B_USELESS;
			brelse(bp);

			/*
			 *	If we finally put good data
			 *	into the buffer, we have to zero
			 *	the initial portion that we skipped.
			 */

			if (error != 0) {
				if (sofar > 0)
					bzero(buffer, sofar);
				error = 0;
			}
		}

		sofar += n;
		offset += n;
		amount -= n;
	} while (amount > 0);

	/*
	 *	If we are returning real data in the buffer,
	 *	and we ran up against the file size,
	 *	we must zero the remainder of the buffer.
	 */

	if ((error == 0) && (limit < size))
		bzero(buffer + limit, size - limit);

    done:
	iunlock(ip);
	return error;
}

/*
 *  Determines whether page has been paged out before.
 *  Must have called unix_master, and ip must be locked.
 */
boolean_t
ufs_page_exists(ip, size, offset)
	register struct inode	*ip;
	int size;
	vm_offset_t	offset;
{
	register struct fs	*fs;
	daddr_t		lbn, bn;
	long		bsize;
	int		on, n, save_error, error;
	u_long		diff;

	fs = ip->i_fs;
	bsize = fs->fs_bsize;

	/*
	 *	Find block and offset within it for our data.
	 */
	lbn = lblkno(fs, offset);	/* logical block number */
	on  = blkoff(fs, offset);	/* byte offset within block */

	/*
	 *	Find the size we can read - don't go beyond the
	 *	end of a block.
	 */
	n = MIN((unsigned)(bsize - on), size);
	diff = ip->i_size - offset;

	/*
	 *	Entire block beyond end of file -- doesn't exist
	 */
	if (ip->i_size <= offset) {
		return FALSE;
	}

	if (diff < n)
		n = diff;

	/*
	 *	Read the index to find the disk block to read
	 *	from.  If there is no block, report that we don't
	 *	have this data.
	 *
	 *	!!! Assumes that:
	 *		1) Any offset will be on a fragment boundary
	 *		2) The inode won't have just part of a page
	 */
	save_error = u.u_error;
	u.u_error = 0;
	/* changes u.u_error! */
	bn = fsbtodb(fs,
		BMAP(ip, lbn, B_READ, (int)(on+n) ));
	error = u.u_error;
	u.u_error = save_error;

	/*
	 *	On error, we assume that the page is not there.
	 */
	if (error) {
		printf("error %d on pagein (fsbtodb)\n", error);
		return FALSE;
	}

	/*
	 *	If we know that we have at least part of the page,
	 *	assume it is all there.
	 */
	return ((long)bn >= 0);
}

ufs_page_write(vp, buffer, size, offset, cred, init)
	struct vnode *vp;
	caddr_t buffer;
	int size;
	vm_offset_t	offset;
	struct ucred *cred;
	boolean_t init;
{
	register struct inode *ip = VTOI(vp);
	int		error;
	struct uio 	uiop;
	struct iovec	iov;

	/*
	 *  The init flag means 'page out only if never paged out before'.
	 */
	if (init) {
		boolean_t exists;

		ilock(ip);
		exists = ufs_page_exists(ip, size, offset);
		iunlock(ip);

		if (exists)
			return 0;
	}

	iov.iov_base = buffer;
	iov.iov_len = size;
	uiop.uio_iov = &iov;
	uiop.uio_iovcnt = 1;
	uiop.uio_offset = offset;
	uiop.uio_segflg = UIO_SYSSPACE;
	uiop.uio_resid = size;
	error = ufs_rdwr(vp, &uiop, UIO_WRITE, 0, cred);
	if (error) {
		printf("error %d on pageout (ufs_rdwr)\n", error);
	}
	return error;
}

int
ufs_nlinks(vp, l, cred)
    struct vnode *vp;
    int		 *l;
    struct ucred *cred;
{
#ifdef	lint
    cred++;
#endif	lint

    *l = VTOI(vp)->i_nlink;
    return (0);
}

ufs_zone_init()
{
	ufs_fid_zone		= zinit(sizeof(struct ufid), 1024*1024,
					PAGE_SIZE, FALSE, "ufs fid");
}

#include <mach_rfs.h>

#if	MACH_RFS

#include <vfs/pathname.h>

rfs_make_symlink(linkname, target, nc)
	char	*linkname;
	char	*target;
	int	nc;
{
	struct vnode *dvp;
	struct vattr vattr;
	struct pathname tpn;
	struct pathname lpn;
	struct inode *ip;

	if ((nc < 0) || (nc >= 0)) {
		uprintf("rfs_make_symlink not supported under VFS yet\n");
		return(1);
	}

	u.u_error = pn_get(linkname, UIO_USERSPACE, &lpn);
	if (u.u_error)
		return;
	u.u_error = lookuppn(&lpn, NO_FOLLOW, &dvp, (struct vnode **)0);
	if (u.u_error) {
		pn_free(&lpn);
		return;
	}
	if (dvp->v_vfsp->vfs_flag & VFS_RDONLY) {
		u.u_error = EROFS;
		pn_free(&lpn);
		VN_RELE(dvp);
		return;
	}

	vattr_null(&vattr);
	vattr.va_mode = 0744 | VLNK;
	vattr.va_rdev = 0;
	vattr.va_uid = 0;
	vattr.va_gid = 64;

	ip = (struct inode *) 0;

	u.u_error = direnter(VTOI(dvp), lpn.pn_path, DE_CREATE,
		(struct inode *)0, (struct inode *) 0,
		&vattr, &ip);

	if (u.u_error == EEXIST)
		iput(ip);
	if (u.u_error != 0) {
		pn_free(&lpn);
		VN_RELE(dvp);
		return(u.u_error);
	}

	ip->i_uid = 0;
	ip->i_gid = 64;

#if	MACH_FASTLINK
	if (create_fastlinks && (nc <= MAX_FASTLINK_SIZE)) {
		    (void) copyin(target, ip->i_symlink, nc);
		    ip->i_size = nc;
		    ip->i_icflags |= IC_FASTLINK;
		    imark(ip, IUPD|ICHG);
		}
	else {
#endif	MACH_FASTLINK
		u.u_error = rdwri(UIO_WRITE, ip,
			target, nc, 0, UIO_USERSPACE, (int *)0);
#if	MACH_FASTLINK
	}
#endif	MACH_FASTLINK

	iput(ip);
	pn_free(&lpn);
	VN_RELE(dvp);
	return(0);
}
#endif	MACH_RFS
