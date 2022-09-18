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
 * $Log:	sys_inode.c,v $
 * Revision 2.12  90/08/30  10:59:04  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.11  90/07/03  16:32:41  mrt
 * 	Remove !MACH_XP code.  Use memory_object_lock_request instead of
 * 	pager_lock_request.
 * 	[90/06/28            dlb]
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:50:26  mrt]
 * 
 * Revision 2.10  89/05/05  11:35:49  mikeg
 * 	Exchange uses of multiply/divide in FIOCFSPARM call to fix bug
 * 	in adjusting blocks sizes for file systems with a non-1K
 * 	fragment size.
 * 	[89/04/17  17:32:54  mja]
 * 
 * Revision 2.9  89/04/22  15:21:27  gm0w
 * 	Changed inode vm_info field to i_vm_info.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.8  89/03/09  19:31:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  14:57:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:33:15  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:07:45  af
 * 	Changes for I386: EXL "open type" switch argument
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  88/08/24  01:29:54  mwyoung
 * 	Corrected include file references.
 * 	[88/08/23  00:39:52  mwyoung]
 * 
 *
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Moved terminal close down code from vhangup() into new
 *	ttydetach() routine which is called from here as well as from
 *	from ttylogout() and whenever the control side of a pseudo-
 *	terminal is closed down.
 *	[ V5.1(XF23) ]
 *
 * 26-Sep-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Minor bug fixes for NBC.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Coalese NBC code into normal VM based code.
 *
 *  4-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Eliminated pager_id's, and thus all dependance on MACH_XP and
 *	the include of mach_xp.h.
 *
 *  1-Jun-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added include of "builtin/inode_pager.h" to get inode_uncache.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 *  3-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use inode_uncache routine to properly maintain inode-object
 *	cache.
 *
 * 27-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added FIOCNOSPC call to prohibit/allow disk space resource
 *	pausing on a per-file basis.
 *	[ V5.1(F1) ]
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  Changed the test for open files when closing a
 *	device in ino_close to look at DTYPE_VICEINO inodes as
 *	well as DTYPE_INODE types.
 *
 * 19-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added FIOCFSPARAM call to retrieve file system parameters of an
 *	open file.
 *	[ V5.1(F1) ]
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted some things.
 *
 * 31-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use the new pager_id field of the inode to call
 *	vm_object_uncache.
 *
 *  1-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Remove inode from the object cache if it is truncated.
 *
 * 16-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added RT compatibility under switch romp.  Changes due to
 *	the fact that the RT character-special drivers take an inode
 *	pointer as an extra parameter.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 05-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Fix bug in rdwri() so that it only sets error EIO
 *	on a residual count when no other error was indicated.
 *	[V1(1)]
 *	
 */
 
#include <mach_nbc.h>
#include <vice.h>
#include <cputypes.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)sys_inode.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/fs.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <kern/mfs.h>
#include <mach/memory_object.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <vm/vm_page.h>
#include <builtin/inode_pager.h>
#if	MACH_NBC
int	nbc_debug = 0x0;
int	magic_dev = 0x1;
#endif	MACH_NBC
#include <sys/stat.h>
#include <sys/kernel.h>
#if	EXL
#include <machine/open.h>
#endif	EXL

int	ino_rw(), ino_ioctl(), ino_select(), ino_close();
struct 	fileops inodeops =
	{ ino_rw, ino_ioctl, ino_select, ino_close };

ino_rw(fp, rw, uio)
	struct file *fp;
	enum uio_rw rw;
	struct uio *uio;
{
	register struct inode *ip = (struct inode *)fp->f_data;
	int error;

	if ((ip->i_mode&IFMT) == IFREG) {
		ILOCK(ip);
		if (fp->f_flag&FAPPEND && rw == UIO_WRITE)
			uio->uio_offset = fp->f_offset = ip->i_size;
		error = rwip(ip, uio, rw);
		IUNLOCK(ip);
	} else
		error = rwip(ip, uio, rw);
	return (error);
}

rdwri(rw, ip, base, len, offset, segflg, aresid)
	struct inode *ip;
	caddr_t base;
	int len, segflg;
	off_t offset;
	int *aresid;
	enum uio_rw rw;
{
	struct uio auio;
	struct iovec aiov;
	int error;

	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_resid = len;
	auio.uio_offset = offset;
	auio.uio_segflg = segflg;
	error = rwip(ip, &auio, rw);
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid)
		    if (error == 0)
			error = EIO;
	return (error);
}

rwip(ip, uio, rw)
	register struct inode *ip;
	register struct uio *uio;
	enum uio_rw rw;
{
	dev_t dev = (dev_t)ip->i_rdev;
	struct buf *bp;
	struct fs *fs;
	daddr_t lbn, bn;
	register int n, on, type;
	int size;
	long bsize;
	extern int mem_no;
	int error = 0;

	if (rw != UIO_READ && rw != UIO_WRITE)
		panic("rwip");
	if (rw == UIO_READ && uio->uio_resid == 0)
		return (0);
#if	0
	/* XXX Here's where it's a bad idea to have off_t be unsigned */
	if (uio->uio_offset < 0 &&
	    ((ip->i_mode&IFMT) != IFCHR || mem_no != major(dev)))
		return (EINVAL);
#endif	0
	if (rw == UIO_READ)
		ip->i_flag |= IACC;
	type = ip->i_mode&IFMT;
	if (type == IFCHR) {
		if (rw == UIO_READ)
			error = (*cdevsw[major(dev)].d_read)(dev, uio);
		else {
			ip->i_flag |= IUPD|ICHG;
			error = (*cdevsw[major(dev)].d_write)(dev, uio);
		}
		return (error);
	}
	if (uio->uio_resid == 0)
		return (0);
	if (rw == UIO_WRITE && type == IFREG &&
	    uio->uio_offset + uio->uio_resid >
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(u.u_procp, SIGXFSZ);
		return (EFBIG);
	}
	if (type != IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
	} else
		bsize = BLKDEV_IOSIZE;
#if	MACH_NBC
	if (ip->i_vm_info->mapped) {
		register vm_offset_t	va;
		register struct vm_info	*vp;

		vp = ip->i_vm_info;
		if (nbc_debug & 4) {
			uprintf("rwip(%c): ip 0x%x, offset %d, size %d\n",
				rw == UIO_READ ? 'R' : 'W',
				ip, uio->uio_offset, uio->uio_resid);
		}
		/*
		 *	Since mfs_get can sleep waiting for the lock on
		 *	the vp structure, make sure we don't hold
		 *	the inode lock (which would block other paging
		 *	operations on this inode.
		 */
		IUNLOCK(ip);
		mfs_get(ip, uio->uio_offset, uio->uio_resid);
		ILOCK(ip);
		do {
			n = MIN((unsigned)bsize, uio->uio_resid);
			if (rw == UIO_READ) {
				int diff = ip->i_size - uio->uio_offset;
				if (diff <= 0) {
					mfs_put(ip);
					return (0);
				}
				if (diff < n)
					n = diff;
			}
			if ((rw == UIO_WRITE) &&
			   (uio->uio_offset + n > vp->inode_size) &&
			   (type == IFDIR || type == IFREG || type == IFLNK))
				vp->inode_size = uio->uio_offset + n;
			/*
			 *	Check to be sure we have a valid window
			 *	for the mapped file.
			 */
			IUNLOCK(ip);
			if ((uio->uio_offset < vp->offset) ||
			   ((uio->uio_offset + n) > (vp->offset + vp->size)))
				remap_inode(ip, uio->uio_offset, n);
			va = vp->va + uio->uio_offset - vp->offset;
			if (nbc_debug & 4) {
				uprintf("uiomove: va = 0x%x, n = %d.\n",
					va, n);
			}
			u.u_error = uiomove(va, n, rw, uio);
			ILOCK(ip);
			if (rw == UIO_WRITE) {
				ip->i_flag |= IUPD|ICHG;
				if (u.u_ruid != 0)
					ip->i_mode &= ~(ISUID|ISGID);
				/* put it on disk */
				IUNLOCK(ip);
				ino_push(ip, uio->uio_offset - n, n);
				ILOCK(ip);
			}
		} while (u.u_error == 0 && uio->uio_resid > 0 && n != 0);
		mfs_put(ip);
		return(u.u_error);
	}
#endif	MACH_NBC
	do {
		lbn = uio->uio_offset / bsize;
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uio->uio_resid);
		if (type != IFBLK) {
			if (rw == UIO_READ) {
				int diff = ip->i_size - uio->uio_offset;
				if (diff <= 0)
					return (0);
				if (diff < n)
					n = diff;
			}
			bn = fsbtodb(fs,
			    bmap(ip, lbn, rw == UIO_WRITE ? B_WRITE: B_READ, (int)(on+n)));
			if (u.u_error || rw == UIO_WRITE && (long)bn<0)
				return (u.u_error);
			if (rw == UIO_WRITE && uio->uio_offset + n > ip->i_size &&
			   (type == IFDIR || type == IFREG || type == IFLNK))
				ip->i_size = uio->uio_offset + n;
			size = blksize(fs, ip, lbn);
		} else {
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
			rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
			rasize = size = bsize;
		}
		if (rw == UIO_READ) {
			if ((long)bn<0) {
				bp = geteblk(size);
				clrbuf(bp);
			} else if (ip->i_lastr + 1 == lbn)
				bp = breada(dev, bn, size, rablock, rasize);
			else
				bp = bread(dev, bn, size);
			ip->i_lastr = lbn;
		} else {
			if (ip->i_vm_info->pager != MEMORY_OBJECT_NULL)
				inode_uncache(ip);
			if (n == bsize) 
				bp = getblk(dev, bn, size);
			else
				bp = bread(dev, bn, size);
		}
		n = MIN(n, size - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			error = EIO;
			brelse(bp);
			goto bad;
		}
		u.u_error =
		    uiomove(bp->b_un.b_addr+on, n, rw, uio);
		if (rw == UIO_READ) {
			if (n + on == bsize || uio->uio_offset == ip->i_size)
				bp->b_flags |= B_AGE;
			brelse(bp);
		} else {
			if ((ip->i_mode&IFMT) == IFDIR)
				bwrite(bp);
			else if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
			ip->i_flag |= IUPD|ICHG;
			if (u.u_ruid != 0)
				ip->i_mode &= ~(ISUID|ISGID);
		}
	} while (u.u_error == 0 && uio->uio_resid > 0 && n != 0);
	if (error == 0)				/* XXX */
		error = u.u_error;		/* XXX */
bad:
	return (error);
}

ino_ioctl(fp, com, data)
	struct file *fp;
	register int com;
	caddr_t data;
{
	register struct inode *ip = ((struct inode *)fp->f_data);
	register int fmt = ip->i_mode & IFMT;
	dev_t dev;

#ifdef	__STDC__
	if (com == _IOW('f', 100, int))	/* FIOCXMOD */
#else
	if (com == _IOW(f, 100, int))	/* FIOCXMOD */
#endif
		return(0);
	if (com == FIOCFSPARAM)
	{
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
		bzero((caddr_t)fsp->fsp_unused, sizeof(fsp->fsp_unused));
		return(0);
	}
	switch (fmt) {

	case IFREG:
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
	case IFDIR:
		if (com == FIONREAD) {
			*(off_t *)data = ip->i_size - fp->f_offset;
			return (0);
		}
		if (com == FIONBIO || com == FIOASYNC)	/* XXX */
			return (0);			/* XXX */
		/* fall into ... */

	default:
		return (ENOTTY);

	case IFCHR:
		dev = ip->i_rdev;
		u.u_r.r_val1 = 0;
		if (setjmp(&u.u_qsave)) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				return(EINTR);
			u.u_eosys = RESTARTSYS;
			return (0);
		}
		return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data,
		    fp->f_flag));
	}
}

ino_select(fp, which)
	struct file *fp;
	int which;
{
	register struct inode *ip = (struct inode *)fp->f_data;
	register dev_t dev;

	switch (ip->i_mode & IFMT) {

	default:
		return (1);		/* XXX */

	case IFCHR:
		dev = ip->i_rdev;
		return (*cdevsw[major(dev)].d_select)(dev, which);
	}
}

#ifdef	notdef
ino_clone()
{

	return (EOPNOTSUPP);
}
#endif

ino_stat(ip, sb)
	register struct inode *ip;
	register struct stat *sb;
{

	ITIMES(ip, &time, &time);
	/*
	 * Copy from inode table
	 */
	sb->st_dev = ip->i_dev;
	sb->st_ino = ip->i_number;
	sb->st_mode = ip->i_mode;
	sb->st_nlink = ip->i_nlink;
	sb->st_uid = ip->i_uid;
	sb->st_gid = ip->i_gid;
	sb->st_rdev = (dev_t)ip->i_rdev;
	sb->st_size = ip->i_size;
	sb->st_atime = ip->i_atime;
	sb->st_spare1 = 0;
	sb->st_mtime = ip->i_mtime;
	sb->st_spare2 = 0;
	sb->st_ctime = ip->i_ctime;
	sb->st_spare3 = 0;
	/* this doesn't belong here */
	if ((ip->i_mode&IFMT) == IFBLK)
		sb->st_blksize = BLKDEV_IOSIZE;
	else if ((ip->i_mode&IFMT) == IFCHR)
		sb->st_blksize = MAXBSIZE;
	else
		sb->st_blksize = ip->i_fs->fs_bsize;
	sb->st_blocks = ip->i_blocks;
	sb->st_spare4[0] = sb->st_spare4[1] = 0;
	return (0);
}

ino_close(fp)
	register struct file *fp;
{
	register struct inode *ip = (struct inode *)fp->f_data;
	register struct mount *mp;
	int flag, mode;
	dev_t dev;
	register int (*cfunc)();

	if (fp->f_flag & (FSHLOCK|FEXLOCK))
		ino_unlock(fp, FSHLOCK|FEXLOCK);
	flag = fp->f_flag;
	dev = (dev_t)ip->i_rdev;
	mode = ip->i_mode & IFMT;
	ilock(ip);
#if	MACH_NBC
	if (mode == IFREG) {
		unmap_inode(ip);
	}
#endif	MACH_NBC
	iput(ip);
	fp->f_data = (caddr_t) 0;		/* XXX */
	switch (mode) {

	case IFCHR:
		cfunc = cdevsw[major(dev)].d_close;
		break;

	case IFBLK:
		/*
		 * We don't want to really close the device if it is mounted
		 */
/* MOUNT TABLE SHOULD HOLD INODE */
		for (mp = mount; mp < &mount[NMOUNT]; mp++)
			if (mp->m_bufp != NULL && mp->m_dev == dev)
				return;
		cfunc = bdevsw[major(dev)].d_close;
		break;

	default:
		return;
	}

	/*
	 * Check that another inode for the same device isn't active.
	 * This is because the same device can be referenced by
	 * two different inodes.
	 */
	for (fp = file; fp < fileNFILE; fp++) {
#if	VICE
		if (fp->f_type != DTYPE_INODE && fp->f_type != DTYPE_VICEINO)
#else	VICE
		if (fp->f_type != DTYPE_INODE)		/* XXX */
#endif	VICE
			continue;
		if (fp->f_count && (ip = (struct inode *)fp->f_data) &&
		    ip->i_rdev == dev && (ip->i_mode&IFMT) == mode)
			return;
	}
	if (mode == IFBLK) {
		/*
		 * On last close of a block device (that isn't mounted)
		 * we must invalidate any in core blocks, so that
		 * we can, for instance, change floppy disks.
		 */
		bflush(dev);
		binval(dev);
	}
	if (setjmp(&u.u_qsave)) {
		/*
		 * If device close routine is interrupted,
		 * must return so closef can clean up.
		 */
		if (u.u_error == 0)
			u.u_error = EINTR;	/* ??? */
		return;
	}
#if	EXL
	(*cfunc)(dev, flag, mode==IFCHR ? OTYP_CHR: OTYP_BLK);
#else	EXL
	(*cfunc)(dev, flag, mode == IFCHR ? S_IFCHR : S_IFBLK);
#endif	EXL
}

/*
 * Place an advisory lock on an inode.
 */
ino_lock(fp, cmd)
	register struct file *fp;
	int cmd;
{
	register int priority = PLOCK;
	register struct inode *ip = (struct inode *)fp->f_data;

	if ((cmd & LOCK_EX) == 0)
		priority += 4;
	if (setjmp(&u.u_qsave)) {
		if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
			return(EINTR);
		u.u_eosys = RESTARTSYS;
		return (0);
	}
	/*
	 * If there's a exclusive lock currently applied
	 * to the file, then we've gotta wait for the
	 * lock with everyone else.
	 */
again:
	while (ip->i_flag & IEXLOCK) {
		/*
		 * If we're holding an exclusive
		 * lock, then release it.
		 */
		if (fp->f_flag & FEXLOCK) {
			ino_unlock(fp, FEXLOCK);
			continue;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		ip->i_flag |= ILWAIT;
		sleep((caddr_t)&ip->i_exlockc, priority);
	}
	if ((cmd & LOCK_EX) && (ip->i_flag & ISHLOCK)) {
		/*
		 * Must wait for any shared locks to finish
		 * before we try to apply a exclusive lock.
		 *
		 * If we're holding a shared
		 * lock, then release it.
		 */
		if (fp->f_flag & FSHLOCK) {
			ino_unlock(fp, FSHLOCK);
			goto again;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		ip->i_flag |= ILWAIT;
		sleep((caddr_t)&ip->i_shlockc, PLOCK);
		goto again;
	}
	if (fp->f_flag & FEXLOCK)
		panic("ino_lock");
	if (cmd & LOCK_EX) {
		cmd &= ~LOCK_SH;
		ip->i_exlockc++;
		ip->i_flag |= IEXLOCK;
		fp->f_flag |= FEXLOCK;
	}
	if ((cmd & LOCK_SH) && (fp->f_flag & FSHLOCK) == 0) {
		ip->i_shlockc++;
		ip->i_flag |= ISHLOCK;
		fp->f_flag |= FSHLOCK;
	}
	return (0);
}

/*
 * Unlock a file.
 */
ino_unlock(fp, kind)
	register struct file *fp;
	int kind;
{
	register struct inode *ip = (struct inode *)fp->f_data;
	int flags;

	kind &= fp->f_flag;
	if (ip == NULL || kind == 0)
		return;
	flags = ip->i_flag;
	if (kind & FSHLOCK) {
		if ((flags & ISHLOCK) == 0)
			panic("ino_unlock: SHLOCK");
		if (--ip->i_shlockc == 0) {
			ip->i_flag &= ~ISHLOCK;
			if (flags & ILWAIT)
				wakeup((caddr_t)&ip->i_shlockc);
		}
		fp->f_flag &= ~FSHLOCK;
	}
	if (kind & FEXLOCK) {
		if ((flags & IEXLOCK) == 0)
			panic("ino_unlock: EXLOCK");
		if (--ip->i_exlockc == 0) {
			ip->i_flag &= ~(IEXLOCK|ILWAIT);
			if (flags & ILWAIT)
				wakeup((caddr_t)&ip->i_exlockc);
		}
		fp->f_flag &= ~FEXLOCK;
	}
}

/*
 * Openi called to allow handler
 * of special files to initialize and
 * validate before actual IO.
 */
openi(ip, mode)
	register struct inode *ip;
{
	dev_t dev = (dev_t)ip->i_rdev;
	register int maj = major(dev);

	switch (ip->i_mode&IFMT) {

	case IFCHR:
		if ((u_int)maj >= nchrdev)
			return (ENXIO);
#if	EXL
		return ((*cdevsw[maj].d_open)(dev, mode, OTYP_CHR));
#else	EXL
		return ((*cdevsw[maj].d_open)(dev, mode,
						(dev_t *)NULL, S_IFCHR));
#endif	EXL
	case IFBLK:
		if ((u_int)maj >= nblkdev)
			return (ENXIO);
#if	EXL
		return ((*bdevsw[maj].d_open)(dev, mode, OTYP_BLK));
#else	EXL
		return ((*bdevsw[maj].d_open)(dev, mode,
						(dev_t *)NULL, S_IFBLK));
#endif	EXL

#if	MACH_NBC
	case IFREG:
/*		if (ip->i_dev != magic_dev) break;*/
		map_inode(ip);
#endif	MACH_NBC
	}
	return (0);
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
	register struct inode *ip;

	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_count == 0)
			continue;
		if (fp->f_type != DTYPE_INODE)
			continue;
		ip = (struct inode *)fp->f_data;
		if (ip == 0)
			continue;
		if ((ip->i_mode & IFMT) != IFCHR)
			continue;
		if (ip->i_rdev != dev)
			continue;
		fp->f_flag &= ~(FREAD|FWRITE);
	}
}

#if	MACH_NBC
/*
 *	Search for and flush pages in the specified range.  For now, it is
 *	unnecessary to flush to disk since I do that synchronously.
 */
ino_flush(ip, start, size)
	struct inode		*ip;
	register vm_offset_t	start;
	vm_size_t		size;
{
	register vm_offset_t	end;
	register vm_object_t	object;
	register vm_page_t	m;

	object = ip->i_vm_info->object;
	if (object == VM_OBJECT_NULL)
		return;

	vm_object_reference(object);
	memory_object_lock_request(object, start, size,
		FALSE, TRUE, VM_PROT_ALL, PORT_NULL);
}

/*
 *	Search for and push (to disk) pages in the specified range.
 */
ino_push(ip, start, size)
	struct inode		*ip;
	register vm_offset_t	start;
	vm_size_t		size;
{
	register vm_offset_t	end;
	register vm_object_t	object;
	register vm_page_t	m;

	object = ip->i_vm_info->object;
	if (object == VM_OBJECT_NULL)
		return;

	vm_object_reference(object);
	memory_object_lock_request(object, start, size,
		TRUE, TRUE, VM_PROT_ALL, PORT_NULL)
}
#endif	MACH_NBC
