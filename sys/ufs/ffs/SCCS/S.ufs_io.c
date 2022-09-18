h14177
s 00047/00148/00254
d D 7.13 89/11/22 22:41:31 mckusick 38 37
c rdwri is gone; read/write locking now handled at the vnode layer;
c readip/writeip are now ufs_read/ufs_write; 
e
s 00006/00006/00396
d D 7.12 89/08/26 14:12:32 mckusick 37 36
c generalize the buffer pool so that NFS can become a client
e
s 00001/00001/00401
d D 7.11 89/08/26 00:20:58 mckusick 36 35
c ruid no longer in credentials, so use uid != root to clear
c setuid and setgid bits when writing an inode
e
s 00306/00508/00096
d D 7.10 89/05/09 17:22:20 mckusick 35 34
c merge in vnodes
e
s 00005/00005/00599
d D 7.9 89/05/01 22:58:03 marc 34 33
c rwip() takes flag argument and passes to driver
e
s 00001/00001/00603
d D 7.8 89/04/26 19:51:48 mckusick 33 32
c use new form of suser()
e
s 00003/00001/00601
d D 7.7 88/10/18 15:14:54 marc 32 31
c posix style job control - new process groups
e
s 00001/00000/00601
d D 7.6 88/05/22 15:07:12 karels 31 29
c lint
e
s 00000/00000/00601
d D 7.5.1.1 87/11/24 16:18:45 karels 30 29
x 28
c tahoe distribution (no malloc)
e
s 00009/00000/00592
d D 7.5 87/10/06 12:06:34 karels 29 28
c can't return device errors on close yet
e
s 00001/00001/00591
d D 7.4 87/06/21 15:30:55 mckusick 28 27
c geteblk => malloc, so m_bufp => m_fs as it should be
e
s 00079/00036/00513
d D 7.3 87/04/02 15:49:03 karels 27 25
c working with pack labels
e
s 00113/00036/00513
d D 7.2.1.1 87/04/02 15:41:01 karels 26 25
c add ifdefs for dev_bsize (almost working)
e
s 00011/00009/00538
d D 7.2 87/03/17 18:02:27 mckusick 25 24
c must avoid race between use and updating of f_offset pointer
e
s 00001/00001/00546
d D 7.1 86/06/05 00:08:01 mckusick 24 23
c 4.3BSD release version
e
s 00002/00001/00545
d D 6.14 86/02/23 23:10:23 karels 23 22
c lint
e
s 00003/00002/00543
d D 6.13 85/08/04 08:02:08 kre 22 21
c fix for posting to hosts where dev_t and daddr_t are not the same
c size when passed as an arg to a function (off the net from ecrcvax!pete).
e
s 00007/00001/00538
d D 6.12 85/06/08 14:43:43 mckusick 21 20
c Add copyright
e
s 00026/00022/00513
d D 6.11 85/05/28 12:08:03 mckusick 20 19
c flock is restarted after signals;
c remove bogus panic that finds a shared lock request already in place;
c must recheck all conditions after wakeup from wait for exclusive lock
e
s 00001/00002/00534
d D 6.10 85/05/22 19:46:40 mckusick 19 18
c eliminate double meaning of SOUSIG
e
s 00004/00001/00532
d D 6.9 85/03/12 13:53:34 mckusick 18 17
c add another bit to sigvec() flags to disable system call restart
e
s 00001/00001/00532
d D 6.8 85/02/28 14:18:53 mckusick 17 16
c fix from sun!shannon
e
s 00005/00005/00528
d D 6.7 84/11/27 16:27:23 karels 16 15
c off-by-one in fcntl-DUPFD; avoid panic on flock(f,0) if holding shared
c lock; don't fail when changing lock types without blocking if we hold the only
c lock
e
s 00017/00017/00516
d D 6.6 84/08/29 20:22:06 bloom 15 14
c Change to includes.  no more ../h
e
s 00003/00001/00530
d D 6.5 84/07/19 16:23:19 karels 14 13
c mfind/munhash pairs protected by splimp
e
s 00005/00007/00526
d D 6.4 84/03/27 16:16:05 karels 13 12
c don't hold pointer to released inode in file table (XXX)
e
s 00003/00004/00530
d D 6.3 83/11/18 17:03:43 karels 12 11
c shared locks don't wait for pending exclusive locks (for now,
c anyway), otherwise interrupted requests for EXLOCK hang things.
e
s 00017/00006/00517
d D 6.2 83/11/18 10:04:40 karels 11 10
c Zero file f_count exactly once (in closef only);
c catch interrupted device close routines so ino_close always returns
c to closef
e
s 00000/00000/00523
d D 6.1 83/07/29 06:37:22 sam 10 9
c 4.2 distribution
e
s 00005/00003/00518
d D 4.9 83/06/29 03:18:23 sam 9 8
c more cases where u.u_error is lost
e
s 00004/00002/00517
d D 4.8 83/06/25 17:16:00 sam 8 7
c guess who doesn't return a value when should
e
s 00001/00001/00518
d D 4.7 83/06/25 02:56:07 sam 7 6
c correct errno
e
s 00002/00001/00517
d D 4.6 83/06/20 19:03:16 sam 6 5
c need flag for certain ioctl's, so keep passing it
e
s 00024/00022/00494
d D 4.5 83/06/14 01:37:17 sam 5 4
c revamp locking to be done at the file table level
e
s 00040/00063/00476
d D 4.4 83/06/12 14:30:07 sam 4 3
c cleanup locking a bit; fix problem with close not unlocking
e
s 00002/00002/00537
d D 4.3 83/06/09 21:59:15 sam 3 2
c locking cleanup
e
s 00001/00001/00538
d D 4.2 83/06/02 15:57:26 sam 2 1
c new signals
e
s 00539/00000/00000
d D 4.1 83/05/27 14:02:50 sam 1 0
c date and time created 83/05/27 14:02:50 by sam
e
u
U
f b 
t
T
I 1
D 21
/*	%M%	%I%	%E%	*/
E 21
I 21
/*
D 24
 * Copyright (c) 1982 Regents of the University of California.
E 24
I 24
D 35
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 24
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 35
I 35
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 35
 *
I 35
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
E 35
 *	%W% (Berkeley) %G%
 */
E 21

I 35
/*
 * Converted to vnode ops for a vfs entry
 */

E 35
D 15
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/proc.h"
#include "../h/fs.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/mount.h"
#include "../h/file.h"
#include "../h/uio.h"
#include "../h/ioctl.h"
#include "../h/tty.h"
#include "../h/cmap.h"
#include "../h/stat.h"
#include "../h/kernel.h"
E 15
I 15
#include "param.h"
#include "systm.h"
D 35
#include "dir.h"
E 35
#include "user.h"
D 35
#include "inode.h"
E 35
#include "proc.h"
D 35
#include "fs.h"
E 35
I 35
#include "mount.h"
#include "vnode.h"
#include "../ufs/inode.h"
#include "../ufs/fs.h"
#include "../ufs/ufsmount.h"
E 35
#include "conf.h"
#include "buf.h"
D 35
#include "mount.h"
E 35
#include "file.h"
#include "uio.h"
#include "ioctl.h"
#include "tty.h"
#include "cmap.h"
#include "stat.h"
#include "kernel.h"
I 27
#include "disklabel.h"
E 27
I 26
#include "disklabel.h"
E 26
E 15

D 4
int	ino_rw(), ino_ioctl(), ino_select(), ino_stat(), ino_close();
E 4
I 4
D 35
int	ino_rw(), ino_ioctl(), ino_select(), ino_close();
E 4
struct 	fileops inodeops =
D 4
	{ ino_rw, ino_ioctl, ino_select, ino_stat, ino_close };
E 4
I 4
	{ ino_rw, ino_ioctl, ino_select, ino_close };
E 35
I 35
/*
D 38
 * Vnode op for read and write
E 38
I 38
 * Vnode op for reading.
E 38
 */
D 38
ufs_read(vp, uio, offp, ioflag, cred)
	register struct vnode *vp;
	struct uio *uio;
	off_t *offp;
	int ioflag;
	struct ucred *cred;
{
	register struct inode *ip = VTOI(vp);
	int count, error;
E 35
E 4

D 35
ino_rw(fp, rw, uio)
	struct file *fp;
	enum uio_rw rw;
E 35
I 35
	if ((ioflag & IO_NODELOCKED) == 0)
		ILOCK(ip);
	uio->uio_offset = *offp;
	count = uio->uio_resid;
	error = readip(ip, uio, cred);
	*offp += count - uio->uio_resid;
	if ((ioflag & IO_NODELOCKED) == 0)
		IUNLOCK(ip);
	return (error);
}

/*
 * Vnode op for read and write
 */
ufs_write(vp, uio, offp, ioflag, cred)
	register struct vnode *vp;
E 35
	struct uio *uio;
I 35
	off_t *offp;
	int ioflag;
	struct ucred *cred;
E 35
{
D 35
	register struct inode *ip = (struct inode *)fp->f_data;
E 35
I 35
	register struct inode *ip = VTOI(vp);
E 35
I 8
D 25
	int error;
E 25
I 25
	int count, error;
I 35
	u_long osize;
E 35
E 25
E 8

D 25
	if ((ip->i_mode&IFMT) == IFREG) {
		ILOCK(ip);
		if (fp->f_flag&FAPPEND && rw == UIO_WRITE)
			uio->uio_offset = fp->f_offset = ip->i_size;
D 8
		u.u_error = rwip(ip, uio, rw);
E 8
I 8
		error = rwip(ip, uio, rw);
E 8
		IUNLOCK(ip);
	} else
D 8
		u.u_error = rwip(ip, uio, rw);
E 8
I 8
		error = rwip(ip, uio, rw);
E 25
I 25
D 26
D 27
	ILOCK(ip);
E 27
I 27
D 35
	if ((ip->i_mode&IFMT) != IFCHR)
E 35
I 35
	if ((ioflag & IO_NODELOCKED) == 0)
E 35
		ILOCK(ip);
E 27
E 26
I 26
	if ((ip->i_mode&IFMT) != IFCHR)
		ILOCK(ip);
E 26
D 35
	if ((ip->i_mode&IFMT) == IFREG &&
	    (fp->f_flag&FAPPEND) &&
	    rw == UIO_WRITE)
		fp->f_offset = ip->i_size;
	uio->uio_offset = fp->f_offset;
E 35
I 35
	if (vp->v_type == VREG && (ioflag & IO_APPEND))
		*offp = ip->i_size;
	uio->uio_offset = *offp;
E 35
	count = uio->uio_resid;
D 34
	error = rwip(ip, uio, rw);
E 34
I 34
D 35
	error = rwip(ip, uio, rw, fp->f_flag);
E 34
	fp->f_offset += count - uio->uio_resid;
D 26
D 27
	IUNLOCK(ip);
E 27
I 27
	if ((ip->i_mode&IFMT) != IFCHR)
E 35
I 35
	osize = ip->i_size;
	error = writeip(ip, uio, cred);
	if (error && (ioflag & IO_UNIT))
		(void) itrunc(ip, osize);
	else
		*offp += count - uio->uio_resid;
	if ((ioflag & IO_NODELOCKED) == 0)
E 35
		IUNLOCK(ip);
E 27
E 26
I 26
	if ((ip->i_mode&IFMT) != IFCHR)
		IUNLOCK(ip);
E 26
E 25
	return (error);
E 8
}

D 35
rdwri(rw, ip, base, len, offset, segflg, aresid)
E 35
I 35
rdwri(rw, ip, base, len, offset, segflg, cred, aresid)
E 35
	struct inode *ip;
	caddr_t base;
D 23
	int len, offset, segflg;
E 23
I 23
D 35
	int len, segflg;
E 35
I 35
	int len;
	enum uio_seg segflg;
E 35
	off_t offset;
I 35
	struct ucred *cred;
E 35
E 23
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
D 34
	error = rwip(ip, &auio, rw);
E 34
I 34
D 35
	error = rwip(ip, &auio, rw, 0);
E 35
I 35
	auio.uio_rw = rw;
	if (rw == UIO_READ)
		error = readip(ip, &auio, cred);
	else
		error = writeip(ip, &auio, cred);
E 35
E 34
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid)
			error = EIO;
	return (error);
}

E 38
D 34
rwip(ip, uio, rw)
E 34
I 34
D 35
rwip(ip, uio, rw, fflag)
E 35
I 35
/* ARGSUSED */
D 38
readip(ip, uio, cred)
E 35
E 34
	register struct inode *ip;
E 38
I 38
ufs_read(vp, uio, ioflag, cred)
	struct vnode *vp;
E 38
	register struct uio *uio;
I 38
	int ioflag;
E 38
D 35
	enum uio_rw rw;
E 35
I 35
	struct ucred *cred;
E 35
{
I 38
	register struct inode *ip = VTOI(vp);
E 38
D 35
	dev_t dev = (dev_t)ip->i_rdev;
D 26
D 27
	struct buf *bp;
E 27
I 27
	register struct buf *bp;
E 27
E 26
I 26
	register struct buf *bp;
E 26
	struct fs *fs;
	daddr_t lbn, bn;
	register int n, on, type;
	int size;
	long bsize;
I 27
	struct partinfo dpart;
E 27
I 26
#ifdef SECSIZE
	long secsize;
#endif SECSIZE
	struct partinfo dpart;
E 26
	extern int mem_no;
	int error = 0;
E 35
I 35
	register struct fs *fs;
	struct buf *bp;
	daddr_t lbn, bn, rablock;
	int size, rasize, diff, error = 0;
	long n, on, type;
E 35

D 35
	if (rw != UIO_READ && rw != UIO_WRITE)
		panic("rwip");
	if (rw == UIO_READ && uio->uio_resid == 0)
E 35
I 35
	if (uio->uio_rw != UIO_READ)
D 38
		panic("readip mode");
E 38
I 38
		panic("ufs_read mode");
E 38
	type = ip->i_mode & IFMT;
	if (type != IFDIR && type != IFREG && type != IFLNK)
D 38
		panic("readip type");
E 38
I 38
		panic("ufs_read type");
E 38
	if (uio->uio_resid == 0)
E 35
		return (0);
D 26
D 27
	if (uio->uio_offset < 0 &&
E 27
I 27
D 35
	if (uio->uio_offset < 0 &&				/* XXX */
E 27
E 26
I 26
	if (uio->uio_offset < 0 &&				/* XXX */
E 26
	    ((ip->i_mode&IFMT) != IFCHR || mem_no != major(dev)))
E 35
I 35
	if (uio->uio_offset < 0)
E 35
		return (EINVAL);
D 35
	if (rw == UIO_READ)
		ip->i_flag |= IACC;
	type = ip->i_mode&IFMT;
	if (type == IFCHR) {
		if (rw == UIO_READ)
D 9
			u.u_error = (*cdevsw[major(dev)].d_read)(dev, uio);
E 9
I 9
D 34
			error = (*cdevsw[major(dev)].d_read)(dev, uio);
E 34
I 34
			error = (*cdevsw[major(dev)].d_read)(dev, uio, fflag);
E 34
E 9
		else {
			ip->i_flag |= IUPD|ICHG;
D 9
			u.u_error = (*cdevsw[major(dev)].d_write)(dev, uio);
E 9
I 9
D 34
			error = (*cdevsw[major(dev)].d_write)(dev, uio);
E 34
I 34
			error = (*cdevsw[major(dev)].d_write)(dev, uio, fflag);
E 35
I 35
	ip->i_flag |= IACC;
	fs = ip->i_fs;
	do {
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
		diff = ip->i_size - uio->uio_offset;
		if (diff <= 0)
			return (0);
		if (diff < n)
			n = diff;
		if (error = bmap(ip, lbn, &bn, &rablock, &rasize))
			return (error);
		size = blksize(fs, ip, lbn);
		if ((long)bn < 0) {
			bp = geteblk(size);
			clrbuf(bp);
		} else if (ip->i_lastr + 1 == lbn)
			error = breada(ip->i_devvp, bn, size, rablock, rasize,
D 37
				&bp);
E 37
I 37
				NOCRED, &bp);
E 37
		else
D 37
			error = bread(ip->i_devvp, bn, size, &bp);
E 37
I 37
			error = bread(ip->i_devvp, bn, size, NOCRED, &bp);
E 37
		ip->i_lastr = lbn;
		n = MIN(n, size - bp->b_resid);
		if (error) {
			brelse(bp);
			return (error);
E 35
E 34
E 9
		}
D 9
		return (u.u_error);
E 9
I 9
D 35
		return (error);
E 9
	}
E 35
I 35
		error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
		if (n + on == fs->fs_bsize || uio->uio_offset == ip->i_size)
			bp->b_flags |= B_AGE;
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	return (error);
}

D 38
writeip(ip, uio, cred)
	register struct inode *ip;
	register struct uio *uio;
E 38
I 38
/*
 * Vnode op for writing.
 */
ufs_write(vp, uio, ioflag, cred)
	register struct vnode *vp;
	struct uio *uio;
	int ioflag;
E 38
	struct ucred *cred;
{
I 38
	register struct inode *ip = VTOI(vp);
E 38
	register struct fs *fs;
	struct buf *bp;
	daddr_t lbn, bn;
D 38
	int i, n, on, type;
	int flags, count, size;
	int error = 0;
E 38
I 38
	u_long osize;
	int i, n, on, flags;
	int count, size, resid, error = 0;
E 38

	if (uio->uio_rw != UIO_WRITE)
D 38
		panic("writeip mode");
	type = ip->i_mode & IFMT;
	if (type != IFDIR && type != IFREG && type != IFLNK)
		panic("writeip type");
E 38
I 38
		panic("ufs_write mode");
	switch (vp->v_type) {
	case VREG:
		if (ioflag & IO_APPEND)
			uio->uio_offset = ip->i_size;
		/* fall through */
	case VLNK:
		break;

	case VDIR:
		if ((ioflag & IO_SYNC) == 0)
			panic("ufs_write nonsync dir write");
		break;

	default:
		panic("ufs_write type");
	}
E 38
	if (uio->uio_offset < 0)
		return (EINVAL);
E 35
	if (uio->uio_resid == 0)
		return (0);
D 35
	if (rw == UIO_WRITE && type == IFREG &&
E 35
I 35
	/*
	 * Maybe this should be above the vnode op call, but so long as
	 * file servers have no limits, i don't think it matters
	 */
D 38
	if (type == IFREG &&
E 38
I 38
	if (vp->v_type == VREG &&
E 38
E 35
	    uio->uio_offset + uio->uio_resid >
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(u.u_procp, SIGXFSZ);
D 7
		return (EMFILE);
E 7
I 7
		return (EFBIG);
E 7
	}
I 38
	resid = uio->uio_resid;
	osize = ip->i_size;
E 38
D 35
	if (type != IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
D 26
D 27
	} else
E 27
I 27
	} else {
E 27
E 26
I 26
#ifdef SECSIZE
		secsize = fs->fs_dbsize;
#endif
	} else {
E 26
		bsize = BLKDEV_IOSIZE;
I 27
		if ((*bdevsw[major(dev)].d_ioctl)(dev, DIOCGPART,
		    (caddr_t)&dpart, FREAD) == 0) {
			if (dpart.part->p_fstype == FS_BSDFFS &&
			    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
				bsize =
				    dpart.part->p_frag * dpart.part->p_fsize;
		}
	}
E 35
I 35
	fs = ip->i_fs;
E 35
E 27
I 26
#ifdef SECSIZE
		secsize = DEV_BSIZE;
#endif SECSIZE
		if ((*bdevsw[major(dev)].d_ioctl)(dev, DIOCGPART,
		    (caddr_t)&dpart, FREAD) == 0) {
#ifdef SECSIZE
			if (dpart.disklab->d_secsize != 0)
				secsize = dpart.disklab->d_secsize;
#endif SECSIZE
			if (dpart.part->p_fstype == FS_BSDFFS &&
			    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
				bsize =
				    dpart.part->p_frag * dpart.part->p_fsize;
		}
	}
E 26
	do {
D 35
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
D 26
D 27
			    bmap(ip, lbn, rw == UIO_WRITE ? B_WRITE: B_READ, (int)(on+n)));
			if (u.u_error || rw == UIO_WRITE && (long)bn<0)
E 27
I 27
			    bmap(ip, lbn, rw == UIO_WRITE ? B_WRITE: B_READ,
				(int)(on + n)));
			if (u.u_error || rw == UIO_WRITE && (long)bn < 0)
E 27
E 26
I 26
			    bmap(ip, lbn, rw == UIO_WRITE ? B_WRITE: B_READ,
				(int)(on + n)));
			if (u.u_error || rw == UIO_WRITE && (long)bn < 0)
E 26
				return (u.u_error);
D 26
D 27
			if (rw == UIO_WRITE && uio->uio_offset + n > ip->i_size &&
E 27
I 27
			if (rw == UIO_WRITE &&
			   uio->uio_offset + n > ip->i_size &&
E 27
E 26
I 26
			if (rw == UIO_WRITE &&
			   uio->uio_offset + n > ip->i_size &&
E 26
			   (type == IFDIR || type == IFREG || type == IFLNK))
				ip->i_size = uio->uio_offset + n;
			size = blksize(fs, ip, lbn);
		} else {
D 26
D 27
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
			rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
E 27
I 27
			bn = lbn * (bsize / DEV_BSIZE);
			rablock = bn + (bsize / DEV_BSIZE);
E 27
E 26
I 26
#ifdef SECSIZE
			bn = lbn * (bsize / secsize);
			rablock = bn + (bsize / secsize);
#else SECSIZE
			bn = lbn * (bsize / DEV_BSIZE);
			rablock = bn + (bsize / DEV_BSIZE);
#endif SECSIZE
E 26
			rasize = size = bsize;
		}
		if (rw == UIO_READ) {
			if ((long)bn<0) {
				bp = geteblk(size);
				clrbuf(bp);
			} else if (ip->i_lastr + 1 == lbn)
I 26
#ifdef SECSIZE
				bp = breada(dev, bn, size, secsize,
				    rablock, rasize);
			else
				bp = bread(dev, bn, size, secsize);
#else SECSIZE
E 26
				bp = breada(dev, bn, size, rablock, rasize);
			else
				bp = bread(dev, bn, size);
I 26
#endif SECSIZE
E 26
			ip->i_lastr = lbn;
		} else {
D 14
			int i, count;
E 14
I 14
D 26
D 27
			int i, count, s;
E 14
			extern struct cmap *mfind();
E 27
I 27
			int i, count;
E 27
E 26
I 26
			int i, count;
E 26

D 26
D 27
			count = howmany(size, DEV_BSIZE);
I 14
			s = splimp();
E 14
D 17
			for (i = 0; i < count; i += CLSIZE)
E 17
I 17
			for (i = 0; i < count; i += CLBYTES / DEV_BSIZE)
E 17
				if (mfind(dev, bn + i))
					munhash(dev, bn + i);
I 14
			splx(s);
E 27
I 27
			count = howmany(size, CLBYTES);
			for (i = 0; i < count; i++)
				munhash(dev, bn + i * CLBYTES / DEV_BSIZE);
E 27
E 26
I 26
			count = howmany(size, CLBYTES);
#ifdef SECSIZE
			for (i = 0; i < count; i++)
				munhash(dev, bn + i * CLBYTES / secsize);
E 26
E 14
			if (n == bsize) 
I 26
				bp = getblk(dev, bn, size, secsize);
			else
				bp = bread(dev, bn, size, secsize);
#else SECSIZE
			for (i = 0; i < count; i++)
				munhash(dev, bn + i * CLBYTES / DEV_BSIZE);
			if (n == bsize) 
E 26
				bp = getblk(dev, bn, size);
			else
				bp = bread(dev, bn, size);
I 26
#endif SECSIZE
E 26
		}
E 35
I 35
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
		if (n < fs->fs_bsize)
			flags = B_CLRBUF;
		else
			flags = 0;
D 38
		error = balloc(ip, lbn, (int)(on + n), &bn, flags);
		if (error || (long)bn < 0)
			return (error);
E 38
I 38
		if (error = balloc(ip, lbn, (int)(on + n), &bn, flags))
			break;
E 38
		if (uio->uio_offset + n > ip->i_size)
			ip->i_size = uio->uio_offset + n;
		size = blksize(fs, ip, lbn);
		count = howmany(size, CLBYTES);
		for (i = 0; i < count; i++)
			munhash(ip->i_devvp, bn + i * CLBYTES / DEV_BSIZE);
		if (n == fs->fs_bsize)
			bp = getblk(ip->i_devvp, bn, size);
		else
D 37
			error = bread(ip->i_devvp, bn, size, &bp);
E 37
I 37
			error = bread(ip->i_devvp, bn, size, NOCRED, &bp);
E 37
E 35
		n = MIN(n, size - bp->b_resid);
D 35
		if (bp->b_flags & B_ERROR) {
			error = EIO;
E 35
I 35
		if (error) {
E 35
			brelse(bp);
D 35
			goto bad;
E 35
I 35
D 38
			return (error);
E 38
I 38
			break;
E 38
E 35
		}
D 35
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
I 9
	if (error == 0)				/* XXX */
		error = u.u_error;		/* XXX */
E 9
bad:
E 35
I 35
		error = uiomove(bp->b_un.b_addr + on, n, uio);
D 38
		if (type == IFDIR)
E 38
I 38
		if (ioflag & IO_SYNC)
E 38
			(void) bwrite(bp);
		else if (n + on == fs->fs_bsize) {
			bp->b_flags |= B_AGE;
			bawrite(bp);
		} else
			bdwrite(bp);
		ip->i_flag |= IUPD|ICHG;
D 36
		if (cred->cr_ruid != 0)
E 36
I 36
		if (cred->cr_uid != 0)
E 36
			ip->i_mode &= ~(ISUID|ISGID);
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
I 38
	if (error && (ioflag & IO_UNIT)) {
		(void) itrunc(ip, osize);
		uio->uio_offset -= resid - uio->uio_resid;
		uio->uio_resid = resid;
	}
E 38
E 35
	return (error);
}

D 35
ino_ioctl(fp, com, data)
	struct file *fp;
	register int com;
	caddr_t data;
E 35
I 35
/* ARGSUSED */
readblkvp(vp, uio, cred, fflag)
	register struct vnode *vp;
	register struct uio *uio;
	struct ucred *cred;
	int fflag;
E 35
{
D 35
	register struct inode *ip = ((struct inode *)fp->f_data);
	register int fmt = ip->i_mode & IFMT;
	dev_t dev;

	switch (fmt) {

	case IFREG:
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
I 27
	case IFBLK:
E 27
I 26
	case IFBLK:
E 26
		dev = ip->i_rdev;
		u.u_r.r_val1 = 0;
D 2
		if ((u.u_procp->p_flag&SNUSIG) && setjmp(&u.u_qsave)) {
E 2
I 2
D 18
		if ((u.u_procp->p_flag&SOUSIG) == 0 && setjmp(&u.u_qsave)) {
E 18
I 18
		if (setjmp(&u.u_qsave)) {
D 19
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0 ||
			    (u.u_procp->p_flag & SOUSIG) != 0)
E 19
I 19
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
E 19
				return(EINTR);
E 18
E 2
			u.u_eosys = RESTARTSYS;
			return (0);
		}
D 6
		return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data, 0));
E 6
I 6
D 26
D 27
		return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data,
		    fp->f_flag));
E 27
I 27
		if (fmt == IFCHR)
			return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data,
			    fp->f_flag));
		if (fmt == IFBLK)
			return ((*bdevsw[major(dev)].d_ioctl)(dev, com, data,
			    fp->f_flag));
E 27
E 26
I 26
		if (fmt == IFCHR)
			return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data,
			    fp->f_flag));
		if (fmt == IFBLK)
			return ((*bdevsw[major(dev)].d_ioctl)(dev, com, data,
			    fp->f_flag));
E 26
E 6
	}
I 31
	/* NOTREACHED */
E 31
}

ino_select(fp, which)
	struct file *fp;
	int which;
{
	register struct inode *ip = (struct inode *)fp->f_data;
I 22
	register dev_t dev;
E 22

	switch (ip->i_mode & IFMT) {

	default:
		return (1);		/* XXX */

	case IFCHR:
D 22
		return
		    (*cdevsw[major(ip->i_rdev)].d_select)(ip->i_rdev, which);
E 22
I 22
		dev = ip->i_rdev;
		return (*cdevsw[major(dev)].d_select)(dev, which);
E 22
	}
}

#ifdef notdef
ino_clone()
{

	return (EOPNOTSUPP);
}
#endif

D 4
ino_stat(fp, sb)
	struct file *fp;
	register struct stat *sb;
{

	return (statinode((struct inode *)fp->f_data, sb));
}

statinode(ip, sb)
E 4
I 4
ino_stat(ip, sb)
E 35
E 4
	register struct inode *ip;
D 35
	register struct stat *sb;
{
E 35
I 35
	struct buf *bp;
	daddr_t bn;
	long bsize, bscale;
	struct partinfo dpart;
D 38
	extern int mem_no;
E 38
	int n, on, error = 0;
E 35

D 13
	IUPDAT(ip, &time, &time, 0);
E 13
I 13
D 35
	ITIMES(ip, &time, &time);
E 35
I 35
D 38
	if (uio->uio_rw != UIO_READ)
		panic("readblkip mode");
	if (vp->v_type != VCHR && vp->v_type != VBLK)
		panic("readblkip type");
E 38
E 35
E 13
	/*
D 35
	 * Copy from inode table
E 35
I 35
	 * XXX Only set ip for the case of the local filesystem.
E 35
	 */
D 35
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
E 35
I 35
	if (vp->v_mount && vp->v_mount->m_fsid.val[1] == MOUNT_UFS)
		ip = VTOI(vp);
E 35
	else
D 35
		sb->st_blksize = ip->i_fs->fs_bsize;
	sb->st_blocks = ip->i_blocks;
	sb->st_spare4[0] = sb->st_spare4[1] = 0;
	return (0);
}

D 4
ino_close(fp, flags)
E 4
I 4
ino_close(fp)
E 4
D 11
	struct file *fp;
E 11
I 11
	register struct file *fp;
E 11
D 4
	int flags;				/* XXX */
E 4
{
D 26
D 27
	register struct inode *ip = (struct inode *)fp->f_data;
I 11
D 13
	register struct file *ffp;
E 13
E 11
	register struct mount *mp;
	int flag, mode;
E 27
I 27
	struct inode *ip = (struct inode *)fp->f_data;
E 27
E 26
I 26
	struct inode *ip = (struct inode *)fp->f_data;
E 26
	dev_t dev;
D 26
D 27
	register int (*cfunc)();
E 27
I 27
	int flag, mode;
E 27
E 26
I 26
	int flag, mode;
E 26

I 5
	if (fp->f_flag & (FSHLOCK|FEXLOCK))
		ino_unlock(fp, FSHLOCK|FEXLOCK);
E 5
	flag = fp->f_flag;
I 27
	/*
	 * Must delete inode reference from this file entry
	 * before closei, so that only other references
	 * will prevent close.
	 */
	fp->f_data = (caddr_t) 0;
E 27
I 26
	/*
	 * Must delete inode reference from this file entry
	 * before closei, so that only other references
	 * will prevent close.
	 */
	fp->f_data = (caddr_t) 0;
E 26
	dev = (dev_t)ip->i_rdev;
	mode = ip->i_mode & IFMT;
D 4
	flags &= UF_SHLOCK|UF_EXLOCK;
	if (flags)
		funlocki(ip, flags);
E 4
	ilock(ip);
	iput(ip);
I 13
D 26
D 27
	fp->f_data = (caddr_t) 0;		/* XXX */
E 27
I 27
	u.u_error = closei(dev, mode, flag);
}

/*
 * Close internally or externally open file.
 * Should take pointer to inode, but inode should be released
 * before calling if the close may block.
 */
closei(dev, mode, flag)
	register dev_t dev;
	int mode, flag;
{
	register struct mount *mp;
	register struct file *fp;
	register struct swdevt *swp;
	struct inode *ip;
	int error = 0;
	register int (*cfunc)();

E 27
E 26
I 26
	u.u_error = closei(dev, mode, flag);
}

/*
 * Close internally or externally open file.
 * Should take pointer to inode, but inode should be released
 * before calling if the close may block.
 */
closei(dev, mode, flag)
	register dev_t dev;
	int mode, flag;
{
	register struct mount *mp;
	register struct file *fp;
	register struct swdevt *swp;
	struct inode *ip;
	int error = 0;
	register int (*cfunc)();

E 26
E 13
D 11
	fp->f_count = 0;			/* XXX Should catch */
E 11
	switch (mode) {

	case IFCHR:
		cfunc = cdevsw[major(dev)].d_close;
		break;

	case IFBLK:
		/*
		 * We don't want to really close the device if it is mounted
I 27
		 * or if we're swapping on it.
E 27
I 26
		 * or if we're swapping on it.
E 26
		 */
/* MOUNT TABLE SHOULD HOLD INODE */
		for (mp = mount; mp < &mount[NMOUNT]; mp++)
D 28
			if (mp->m_bufp != NULL && mp->m_dev == dev)
E 28
I 28
			if (mp->m_fs != NULL && mp->m_dev == dev)
E 28
D 26
D 27
				return;
E 27
I 27
				return (0);
		for (swp = swdevt; swp->sw_dev; swp++)
			if (swp->sw_dev == dev && swp->sw_freed)
				return (0);
E 27
E 26
I 26
				return (0);
		for (swp = swdevt; swp->sw_dev; swp++)
			if (swp->sw_dev == dev && swp->sw_freed)
				return (0);
E 26
		cfunc = bdevsw[major(dev)].d_close;
		break;

	default:
E 35
I 35
		ip = (struct inode *)0;
D 38
	if (uio->uio_resid == 0)
E 35
D 26
D 27
		return;
E 27
I 27
		return (0);
I 35
	if (uio->uio_offset < 0 &&				/* XXX */
	    (vp->v_type != VCHR || mem_no != major(vp->v_rdev)))
		return (EINVAL);
	if (ip)
		ip->i_flag |= IACC;
	if (vp->v_type == VCHR)
		return ((*cdevsw[major(vp->v_rdev)].d_read)
			(vp->v_rdev, uio, fflag));
E 38
	bsize = BLKDEV_IOSIZE;
	if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
	    (caddr_t)&dpart, FREAD) == 0) {
		if (dpart.part->p_fstype == FS_BSDFFS &&
		    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
			bsize = dpart.part->p_frag * dpart.part->p_fsize;
E 35
E 27
E 26
I 26
		return (0);
E 26
	}
D 35

	/*
	 * Check that another inode for the same device isn't active.
	 * This is because the same device can be referenced by
	 * two different inodes.
	 */
D 11
	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_type == DTYPE_SOCKET)		/* XXX */
E 11
I 11
D 13
	for (ffp = file; ffp < fileNFILE; ffp++) {
		if (ffp == fp)
E 13
I 13
	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_type != DTYPE_INODE)		/* XXX */
E 13
E 11
			continue;
D 11
		if (fp->f_count && (ip = (struct inode *)fp->f_data) &&
E 11
I 11
D 13
		if (ffp->f_type == DTYPE_SOCKET)		/* XXX */
			continue;
		if (ffp->f_count && (ip = (struct inode *)ffp->f_data) &&
E 13
I 13
		if (fp->f_count && (ip = (struct inode *)fp->f_data) &&
E 13
E 11
		    ip->i_rdev == dev && (ip->i_mode&IFMT) == mode)
D 26
D 27
			return;
E 27
I 27
			return (0);
E 27
E 26
I 26
			return (0);
E 26
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
D 11
	(*cfunc)(dev, flag, fp);
E 11
I 11
D 26
D 27
	if (setjmp(&u.u_qsave)) {
E 27
I 27
	if (setjmp(&u.u_qsave)) {			/* XXX */
E 27
E 26
I 26
	if (setjmp(&u.u_qsave)) {			/* XXX */
E 26
		/*
		 * If device close routine is interrupted,
		 * must return so closef can clean up.
		 */
D 26
D 27
		if (u.u_error == 0)
			u.u_error = EINTR;	/* ??? */
		return;
	}
	(*cfunc)(dev, flag);
E 27
I 27
		error = u.u_error;			/* XXX */
		u.u_error = 0;
		if (error == 0)
			error = EINTR;
	} else
I 29
#ifdef notyet
E 29
		error = (*cfunc)(dev, flag, mode);
E 35
I 35
	bscale = bsize / DEV_BSIZE;
	do {
		bn = (uio->uio_offset / DEV_BSIZE) &~ (bscale - 1);
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uio->uio_resid);
		if (ip && ip->i_lastr + bscale == bn)
			error = breada(vp, bn, (int)bsize, bn + bscale,
D 37
				(int)bsize, &bp);
E 37
I 37
				(int)bsize, NOCRED, &bp);
E 37
		else
D 37
			error = bread(vp, bn, (int)bsize, &bp);
E 37
I 37
			error = bread(vp, bn, (int)bsize, NOCRED, &bp);
E 37
		if (ip)
			ip->i_lastr = bn;
		n = MIN(n, bsize - bp->b_resid);
		if (error) {
			brelse(bp);
			return (error);
		}
		error = uiomove(bp->b_un.b_addr + on, n, uio);
		if (n + on == bsize)
			bp->b_flags |= B_AGE;
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 35
	return (error);
I 29
D 35
#else
	/*
	 * Most device close routines don't return errors,
	 * and dup2() doesn't work right on error.
	 */
		(void) (*cfunc)(dev, flag, mode);
	return (0);
#endif
E 35
E 29
E 27
E 26
I 26
		error = u.u_error;			/* XXX */
		u.u_error = 0;
		if (error == 0)
			error = EINTR;
	} else
		error = (*cfunc)(dev, flag, mode);
	return (error);
E 26
E 11
}

D 35
/*
D 4
 * Lock a file:
 * Ip is the inode associated with the file to be locked,
 * flags is the current "locking state" of the file relative
 * to the process' file descriptor (i.e. u_pofile), and cmd
 * is the new action to be applied.  We need flags in case
 * we're changing a shared lock to a exclusive lock, or vice versa.
E 4
I 4
 * Place an advisory lock on an inode.
E 4
D 5
 *
D 4
 * NB: the inode should't be ilocked before the call as the
 *     only fields we modify are private to the flocki and
 *     funlocki; and later accesses to the inode would block
 *     in ilock where they're not interruptible.
E 4
I 4
 * NB: the inode needn't be ilocked before the call
E 5
E 4
 */
D 4
flocki(ip, flags, cmd)
E 4
I 4
D 5
ino_lock(ip, pf, cmd)
E 4
	register struct inode *ip;
D 4
	int flags, cmd;
E 4
I 4
	register u_char *pf;
E 5
I 5
ino_lock(fp, cmd)
	register struct file *fp;
E 5
	int cmd;
E 35
I 35
/* ARGSUSED */
writeblkvp(vp, uio, cred, fflag)
	register struct vnode *vp;
	register struct uio *uio;
	struct ucred *cred;
	int fflag;
E 35
E 4
{
D 35
	register int priority = PLOCK;
I 5
	register struct inode *ip = (struct inode *)fp->f_data;
E 35
I 35
D 38
	struct inode *ip;
E 38
	struct buf *bp;
	daddr_t bn;
	int bsize, blkmask;
	struct partinfo dpart;
D 38
	extern int mem_no;
E 38
	int n, on, i, count, error = 0;
E 35
E 5

D 4
	if (cmd&LOCK_EX)
E 4
I 4
D 12
	if (cmd & LOCK_EX)
E 12
I 12
D 35
	if ((cmd & LOCK_EX) == 0)
E 12
E 4
D 16
		priority++;
E 16
I 16
		priority += 4;
I 20
	if (setjmp(&u.u_qsave)) {
		if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
			return(EINTR);
		u.u_eosys = RESTARTSYS;
		return (0);
	}
E 35
I 35
D 38
	if (uio->uio_rw != UIO_WRITE)
		panic("writeblkip mode");
	if (vp->v_type != VCHR && vp->v_type != VBLK)
		panic("writeblkip type");
E 35
E 20
E 16
	/*
D 35
	 * If there's a exclusive lock currently applied
D 12
	 * to the file, or someone waiting to get a
	 * exclusive lock, then we've gotta wait for the
E 12
I 12
	 * to the file, then we've gotta wait for the
E 12
	 * lock with everyone else.
E 35
I 35
	 * XXX Only set ip for the case of the local filesystem.
E 35
	 */
D 35
again:
D 4
	while (ip->i_flag&(IEXLOCK|ILWAIT)) {
D 3
		if (cmd&FNDELAY) {
E 3
I 3
		if (cmd&LOCK_NB) {
E 3
			u.u_error = EWOULDBLOCK;
			return (flags);
		}
E 4
I 4
D 12
	while (ip->i_flag & (IEXLOCK|ILWAIT)) {
E 12
I 12
	while (ip->i_flag & IEXLOCK) {
E 12
D 16
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
E 16
E 4
		/*
D 5
		 * If we're holding a write
E 5
I 5
		 * If we're holding an exclusive
E 5
		 * lock, then release it.
		 */
D 4
		if (flags&UF_EXLOCK) {
			funlocki(ip, UF_EXLOCK);
			flags &= ~UF_EXLOCK;
E 4
I 4
D 5
		if (*pf & UF_EXLOCK) {
			ino_unlock(ip, UF_EXLOCK);
			*pf &= ~UF_EXLOCK;
E 5
I 5
		if (fp->f_flag & FEXLOCK) {
			ino_unlock(fp, FEXLOCK);
E 5
E 4
D 20
			goto again;
E 20
I 20
			continue;
E 20
		}
I 16
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
E 16
		ip->i_flag |= ILWAIT;
		sleep((caddr_t)&ip->i_exlockc, priority);
E 35
I 35
	if (vp->v_mount && vp->v_mount->m_fsid.val[1] == MOUNT_UFS)
		ip = VTOI(vp);
	else
		ip = (struct inode *)0;
	if (uio->uio_offset < 0 &&				/* XXX */
	    (vp->v_type != VCHR || mem_no != major(vp->v_rdev)))
		return (EINVAL);
	if (vp->v_type == VCHR) {
		if (ip)
			ip->i_flag |= IUPD|ICHG;
		return ((*cdevsw[major(vp->v_rdev)].d_write)
			(vp->v_rdev, uio, fflag));
E 35
	}
D 4
	if (cmd&LOCK_EX) {
E 4
I 4
D 20
	if (cmd & LOCK_EX) {
E 4
		cmd &= ~LOCK_SH;
E 20
I 20
D 35
	if ((cmd & LOCK_EX) && (ip->i_flag & ISHLOCK)) {
E 20
		/*
		 * Must wait for any shared locks to finish
		 * before we try to apply a exclusive lock.
I 20
		 *
		 * If we're holding a shared
		 * lock, then release it.
E 20
		 */
D 4
		while (ip->i_flag&ISHLOCK) {
D 3
			if (cmd&FNDELAY) {
E 3
I 3
			if (cmd&LOCK_NB) {
E 3
				u.u_error = EWOULDBLOCK;
				return (flags);
			}
E 4
I 4
D 20
		while (ip->i_flag & ISHLOCK) {
D 16
			if (cmd & LOCK_NB)
				return (EWOULDBLOCK);
E 16
E 4
			/*
			 * If we're holding a shared
			 * lock, then release it.
			 */
D 4
			if (flags&UF_SHLOCK) {
				funlocki(ip, UF_SHLOCK);
				flags &= ~UF_SHLOCK;
E 4
I 4
D 5
			if (*pf & UF_SHLOCK) {
				ino_unlock(ip, UF_SHLOCK);
				*pf &= ~UF_SHLOCK;
E 5
I 5
			if (fp->f_flag & FSHLOCK) {
				ino_unlock(fp, FSHLOCK);
E 5
E 4
				goto again;
			}
I 16
			if (cmd & LOCK_NB)
				return (EWOULDBLOCK);
E 16
			ip->i_flag |= ILWAIT;
			sleep((caddr_t)&ip->i_shlockc, PLOCK);
E 20
I 20
		if (fp->f_flag & FSHLOCK) {
			ino_unlock(fp, FSHLOCK);
			goto again;
E 20
		}
I 20
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		ip->i_flag |= ILWAIT;
		sleep((caddr_t)&ip->i_shlockc, PLOCK);
		goto again;
E 35
I 35
	if (uio->uio_resid == 0)
		return (0);
E 38
	bsize = BLKDEV_IOSIZE;
	if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
	    (caddr_t)&dpart, FREAD) == 0) {
		if (dpart.part->p_fstype == FS_BSDFFS &&
		    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
			bsize = dpart.part->p_frag * dpart.part->p_fsize;
E 35
E 20
	}
D 4
	if (flags&(UF_SHLOCK|UF_EXLOCK))
		panic("flocki");
	if (cmd&LOCK_SH) {
E 4
I 4
D 5
	if (*pf & (UF_SHLOCK|UF_EXLOCK))
E 5
I 5
D 20
	if (fp->f_flag & (FSHLOCK|FEXLOCK))
E 20
I 20
D 35
	if (fp->f_flag & FEXLOCK)
E 20
E 5
		panic("ino_lock");
D 20
	if (cmd & LOCK_SH) {
E 4
		ip->i_shlockc++;
		ip->i_flag |= ISHLOCK;
D 4
		flags |= UF_SHLOCK;
E 4
I 4
D 5
		*pf |= UF_SHLOCK;
E 5
I 5
		fp->f_flag |= FSHLOCK;
E 5
E 4
	}
E 20
D 4
	if (cmd&LOCK_EX) {
E 4
I 4
	if (cmd & LOCK_EX) {
I 20
		cmd &= ~LOCK_SH;
E 20
E 4
		ip->i_exlockc++;
		ip->i_flag |= IEXLOCK;
D 4
		flags |= UF_EXLOCK;
E 4
I 4
D 5
		*pf |= UF_EXLOCK;
E 5
I 5
		fp->f_flag |= FEXLOCK;
I 20
	}
	if ((cmd & LOCK_SH) && (fp->f_flag & FSHLOCK) == 0) {
		ip->i_shlockc++;
		ip->i_flag |= ISHLOCK;
		fp->f_flag |= FSHLOCK;
E 20
E 5
E 4
	}
D 4
	return (flags);
E 4
I 4
	return (0);
E 4
}

/*
 * Unlock a file.
 */
D 4
funlocki(ip, locktype)
E 4
I 4
D 5
ino_unlock(ip, locktype)
E 4
	register struct inode *ip;
	int locktype;
E 5
I 5
ino_unlock(fp, kind)
	register struct file *fp;
	int kind;
E 5
{
I 5
	register struct inode *ip = (struct inode *)fp->f_data;
E 5
	int flags;

D 5
	if (ip == NULL)
D 4
		panic("funlocki");
E 4
I 4
		panic("ino_unlock");
E 5
I 5
	kind &= fp->f_flag;
	if (ip == NULL || kind == 0)
		return;
E 5
E 4
	flags = ip->i_flag;
D 4
	if (locktype&UF_SHLOCK) {
		if ((flags&ISHLOCK) == 0)
			panic("no shared lock");
E 4
I 4
D 5
	if (locktype & UF_SHLOCK) {
E 5
I 5
	if (kind & FSHLOCK) {
E 5
		if ((flags & ISHLOCK) == 0)
			panic("ino_unlock: SHLOCK");
E 4
		if (--ip->i_shlockc == 0) {
			ip->i_flag &= ~ISHLOCK;
D 4
			if (flags&ILWAIT)
E 4
I 4
			if (flags & ILWAIT)
E 4
				wakeup((caddr_t)&ip->i_shlockc);
E 35
I 35
	blkmask = (bsize / DEV_BSIZE) - 1;
	do {
		bn = (uio->uio_offset / DEV_BSIZE) &~ blkmask;
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uio->uio_resid);
		count = howmany(bsize, CLBYTES);
		for (i = 0; i < count; i++)
			munhash(vp, bn + i * (CLBYTES / DEV_BSIZE));
		if (n == bsize)
			bp = getblk(vp, bn, bsize);
		else
D 37
			error = bread(vp, bn, bsize, &bp);
E 37
I 37
			error = bread(vp, bn, bsize, NOCRED, &bp);
E 37
		n = MIN(n, bsize - bp->b_resid);
		if (error) {
			brelse(bp);
			return (error);
E 35
		}
I 5
D 35
		fp->f_flag &= ~FSHLOCK;
E 5
	}
D 4
	if (locktype&UF_EXLOCK) {
		if ((flags&IEXLOCK) == 0)
			panic("no exclusive lock");
E 4
I 4
D 5
	if (locktype & UF_EXLOCK) {
E 5
I 5
	if (kind & FEXLOCK) {
E 5
		if ((flags & IEXLOCK) == 0)
			panic("ino_unlock: EXLOCK");
E 4
		if (--ip->i_exlockc == 0) {
			ip->i_flag &= ~(IEXLOCK|ILWAIT);
D 4
			if (flags&ILWAIT)
E 4
I 4
			if (flags & ILWAIT)
E 4
				wakeup((caddr_t)&ip->i_exlockc);
		}
I 5
		fp->f_flag &= ~FEXLOCK;
E 5
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
D 26
D 27
		return ((*cdevsw[maj].d_open)(dev, mode));
E 27
I 27
		return ((*cdevsw[maj].d_open)(dev, mode, S_IFCHR));
E 27
E 26
I 26
		return ((*cdevsw[maj].d_open)(dev, mode, S_IFCHR));
E 26

	case IFBLK:
		if ((u_int)maj >= nblkdev)
			return (ENXIO);
D 26
D 27
		return ((*bdevsw[maj].d_open)(dev, mode));
E 27
I 27
		return ((*bdevsw[maj].d_open)(dev, mode, S_IFBLK));
E 27
E 26
I 26
		return ((*bdevsw[maj].d_open)(dev, mode, S_IFBLK));
E 26
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

D 33
	if (!suser())
E 33
I 33
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 33
		return;
	if (u.u_ttyp == NULL)
		return;
	forceclose(u.u_ttyd);
	if ((u.u_ttyp->t_state) & TS_ISOPEN)
D 32
		gsignal(u.u_ttyp->t_pgrp, SIGHUP);
E 32
I 32
		gsignal(u.u_ttyp->t_pgid, SIGHUP);
	u.u_ttyp->t_session = 0;
	u.u_ttyp->t_pgid = 0;
E 32
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
E 35
I 35
		error = uiomove(bp->b_un.b_addr + on, n, uio);
		if (n + on == bsize) {
			bp->b_flags |= B_AGE;
			bawrite(bp);
		} else
			bdwrite(bp);
D 38
		if (ip)
			ip->i_flag |= IUPD|ICHG;
E 38
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	return (error);
E 35
}
E 1
