/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	spec_vnodeops.c,v $
 * Revision 2.9  90/07/03  16:47:15  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:12:10  mrt]
 * 
 * Revision 2.8  89/10/03  19:27:29  rpd
 * 	Added spec_badop to vnodeops, for new VOP_NLINKS.
 * 	[89/10/02  16:03:35  rpd]
 * 
 * Revision 2.7  89/08/02  08:10:12  jsb
 * 	Eliminated MACH conditionals. Added freefid op. Use zalloc in place
 * 	of kalloc.
 * 	[89/07/31  16:43:58  jsb]
 * 
 * Revision 2.6  89/05/11  14:42:23  gm0w
 * 	Added vn_read1dir vnode op entry.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.5  89/04/22  15:30:38  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  21:01:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:17:18  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:09:31  jsb
 * 	Include file references.
 * 	[89/01/17  15:06:18  jsb]
 *
 *  9-Mar-88 John Seamons (jks) at NeXT
 *	Attach vm_info structure to snode.
 *
 * 18-Jan-88  Gregg Kellogg (gk) at Next, Inc.
 *	STREAMS: added support for SVR2.1 streams and VSTR vnode type.
 *
 * 27-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach.
 *
 */ 

#include <sun_lock.h>
#include <streams.h>

/* @(#)spec_vnodeops.c	1.3 87/06/30 3.2/4.3NFSSRC */
#ifndef	lint
static  char sccsid[] = "@(#)spec_vnodeops.c 1.1 86/09/25 Copyr 1986 Sun Micro";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#if	NeXT
#include <sys/xpr.h>
#endif	NeXT
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/kernel.h>
#include <sys/stat.h>
#include <sys/inode.h>
#include <sys/uio.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <specfs/snode.h>
#include <kern/mfs.h>
#if	STREAMS
#include <sys/stream.h>
#endif	STREAMS

#include <krpc/lockmgr.h>

int spec_open();
int spec_close();
int spec_rdwr();
int spec_ioctl();
int spec_select();
int spec_getattr();
int spec_setattr();
int spec_access();
int spec_link();
int spec_inactive();
int spec_badop();
int spec_noop();
#if	SUN_LOCK
int spec_lockctl();
#endif	SUN_LOCK
int spec_fsync();
int spec_fid();
int spec_freefid();

struct vnodeops spec_vnodeops = {
	spec_open,
	spec_close,
	spec_rdwr,
	spec_ioctl,
	spec_select,
	spec_getattr,
	spec_setattr,
	spec_access,
	spec_noop,	/* lookup */
	spec_noop,	/* create */
	spec_noop,	/* remove */
	spec_link,
	spec_noop,	/* rename */
	spec_noop,	/* mkdir */
	spec_noop,	/* rmdir */
	spec_noop,	/* readdir */
	spec_noop,	/* symlink */
	spec_noop,	/* readlink */
	spec_fsync,
	spec_inactive,
	spec_badop,	/* bmap */
	spec_badop,	/* badop */
	spec_badop,	/* bread */
	spec_badop,	/* brelse */
#if	SUN_LOCK
	spec_lockctl,
#else	SUN_LOCK
	spec_badop,
#endif	SUN_LOCK
	spec_fid,
	spec_badop,	/* page_read */
	spec_badop,	/* page_init */
	spec_badop,	/* read1dir */
	spec_freefid,
	spec_badop,	/* nlinks */
};

/*
 * open a special file (device)
 * some weird stuff here having to do with clone and indirect devices:
 * When a file open operation happens (e.g. ufs_open) and the vnode has
 * type VDEV the open routine makes a spec vnode and calls us. When we
 * do the device open routine there are two possible strange results:
 * 1) an indirect device will return an error on open and return a new
 *    dev number. we have to make that into a spec vnode and call open
 *    on it again.
 * 2) a clone device will return a new dev number on open but no error.
 *    in this case we just make a new spec vnode out of the new dev number
 *    and return that.
 */
/*ARGSUSED*/
int
spec_open(vpp, flag, cred)
	struct vnode **vpp;
	int flag;
	struct ucred *cred;
{
	dev_t dev;
	dev_t newdev;
	dev_t olddev;
	int error;

	/*
	 * Setjmp in case open is interrupted.
	 * If it is, close and return error.
	 */
	if (setjmp(&u.u_qsave)) {
		error = EINTR;
		(void) spec_close(*vpp, flag & FMASK, cred);
		return (error);
	}

	/*
	 * Do open protocol for special type.
	 */
	olddev = dev = (*vpp)->v_rdev;

	switch ((*vpp)->v_mode&VFMT) {

	case VCHR:
#if	STREAMS
	case VSTR:
#endif	STREAMS
		newdev = dev;
		error = 0;
		do {
			dev = newdev;
			if ((u_int)major(dev) >= nchrdev)
				return (ENXIO);

#if	STREAMS
			if (((*vpp)->v_mode&VFMT) == VSTR || cdevsw[major(dev)].d_str)
			{
				(*vpp)->v_mode = ((*vpp)->v_mode&~VFMT)|VSTR;
				error = str_open(dev, flag, *vpp, &newdev);
			} else
#endif	STREAMS
				error = (*cdevsw[major(dev)].d_open)(dev,
								     flag,
								     &newdev,
								     S_IFCHR);

			/*
			 * If this is an indirect device we need to do the
			 * open again.
			 */
		} while (newdev != dev && error == EAGAIN);

		if (olddev != newdev && error == 0) {
			register struct vnode *nvp;

			/*
			 * Allocate new snode with new minor device. Release
			 * old snode. Set vpp to point to new one.  This snode
			 * will go away when the last reference to it goes away.
			 * Warning: if you stat this, and try to match it with
			 * a name in the filesystem you will fail, unless you
			 * had previously put names in that match.
			 */
			nvp = specvp(*vpp, newdev);
			VN_RELE(*vpp);
			*vpp = nvp;
		}
		break;

	case VBLK:
		if ((u_int)major(dev) >= nblkdev)
			return (ENXIO);
		error = (*bdevsw[major(dev)].d_open)(dev, flag, NULL, S_IFBLK);
		break;

#if	FIFOS
	case VFIFO:
		printf("spec_open: got a VFIFO???\n");
#endif	FIFOS

	case VSOCK:
		error = EOPNOTSUPP;
		break;
	
	default:
		error = 0;
		break;
	}
	return (error);
}

/*ARGSUSED*/
int
spec_close(vp, flag, cred)
	struct vnode *vp;
	int flag;
	struct ucred *cred;
{
	int (*cfunc)();
	dev_t dev;
	int fmt = 0;

	/*
	 * setjmp in case close is interrupted
	 */
	if (setjmp(&u.u_qsave)) {
		return (EINTR);
	}
	dev = vp->v_rdev;
	switch(vp->v_mode&VFMT) {

	case VCHR:
		cfunc = cdevsw[major(dev)].d_close;
		fmt = S_IFCHR;
		break;

#if	STREAMS
	case VSTR:
		str_close(dev, flag, vp);
		return(0);
#endif	STREAMS

	case VBLK:
		cfunc = bdevsw[major(dev)].d_close;
		fmt = S_IFBLK;
		break;

#if	FIFOS
	case VFIFO:
		printf("spec_close: got a VFIFO???\n");
#endif	FIFOS

	default:
		return (0);
	}
	if ((vp->v_mode&VFMT) == VBLK) {
		/*
		 * On last close of a block device (that isn't mounted)
		 * we must invalidate any in core blocks, so that
		 * we can, for instance, change floppy disks.
		 */
		bflush(vp);
		binval(vp);
	}
	/*
	 * Close the device.
	 */
	(*cfunc)(dev, flag, fmt);
	return (0);
}

/*
 * read or write a vnode
 */
/*ARGSUSED*/
int
spec_rdwr(vp, uiop, rw, ioflag, cred)
	struct vnode *vp;
	struct uio *uiop;
	enum uio_rw rw;
	int ioflag;
	struct ucred *cred;
{
	register struct snode *sp;
	struct vnode *blkvp;
	dev_t dev;
	struct buf *bp;
	daddr_t lbn, bn;
	register int n, on;
	int size;
	long bsize;
	extern int mem_no;
	int error = 0;

	sp = VTOS(vp);
	dev = vp->v_rdev;
	if (rw != UIO_READ && rw != UIO_WRITE)
		panic("rwsp");
	if (rw == UIO_READ && uiop->uio_resid == 0)
		return (0);
	if ((uiop->uio_offset < 0 || (uiop->uio_offset + uiop->uio_resid) < 0)
	    && !((vp->v_mode&VFMT) == VCHR && mem_no == major(dev))) {
		return (EINVAL);
	}
	if (rw == UIO_READ) {
		smark(VTOS(vp), SACC);
	}
	if ((vp->v_mode&VFMT) == VCHR) {
		if (rw == UIO_READ) {
			error = (*cdevsw[major(dev)].d_read)(dev, uiop);
		} else {
			smark(VTOS(vp), SUPD|SCHG);
			error = (*cdevsw[major(dev)].d_write)(dev, uiop);
		}
		return (error);
#if	STREAMS
	} else if ((vp->v_mode&VFMT) == VSTR) {
		if (rw == UIO_READ) {
			error = str_read(dev, uiop, vp);
		} else {
			smark(VTOS(vp), SUPD|SCHG);
			error = str_write(dev, uiop, vp);
		}
		return(error);
#endif	STREAMS
	} else if ((vp->v_mode&VFMT) != VBLK) {
		return (EOPNOTSUPP);
	}
	if (uiop->uio_resid == 0)
		return (0);
	bsize = BLKDEV_IOSIZE;
	u.u_error = 0;
	blkvp = VTOS(vp)->s_bdevvp;
	do {
		lbn = uiop->uio_offset / bsize;
		on = uiop->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uiop->uio_resid);
		bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
		rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
		rasize = size = bsize;
		if (rw == UIO_READ) {
			if ((long)bn<0) {
				bp = geteblk(size);
				clrbuf(bp);
			} else if (sp->s_lastr + 1 == lbn)
				bp = breada(blkvp, bn, size, rablock,
					rasize);
			else
				bp = bread(blkvp, bn, size);
			sp->s_lastr = lbn;
		} else {
			if (n == bsize) 
				bp = getblk(blkvp, bn, size);
			else
				bp = bread(blkvp, bn, size);
		}
		n = MIN(n, bp->b_bcount - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			error = EIO;
			brelse(bp);
			goto bad;
		}
		u.u_error = uiomove(bp->b_un.b_addr+on, n, rw, uiop);
		if (rw == UIO_READ) {
			if (n + on == bsize)
				bp->b_flags |= B_AGE;
			brelse(bp);
		} else {
			if (ioflag & IO_SYNC)
				bwrite(bp);
			else if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
			smark(VTOS(vp), SUPD|SCHG);
		}
	} while (u.u_error == 0 && uiop->uio_resid > 0 && n != 0);
	if (error == 0)				/* XXX */
		error = u.u_error;		/* XXX */
bad:
	return (error);
}

/*ARGSUSED*/
int
spec_ioctl(vp, com, data, flag, cred)
	struct vnode *vp;
	int com;
	caddr_t data;
	int flag;
	struct ucred *cred;
{

#if	STREAMS
	if ((vp->v_mode&VFMT) == VSTR)
		return(str_ioctl(vp, com, data));
#endif	STREAMS
	if ((vp->v_mode&VFMT) != VCHR)
		panic("spec_ioctl");
	return ((*cdevsw[major(vp->v_rdev)].d_ioctl)
			(vp->v_rdev, com, data, flag));
}

/*ARGSUSED*/
int
spec_select(vp, which, cred)
	struct vnode *vp;
	int which;
	struct ucred *cred;
{

#if	STREAMS
	if ((vp->v_mode&VFMT) == VSTR)
		return(str_select(vp, which));
#endif	STREAMS
	if ((vp->v_mode&VFMT) != VCHR)
		panic("spec_select");
	return ((*cdevsw[major(vp->v_rdev)].d_select)(vp->v_rdev, which));
}

/*ARGSUSED*/
int
spec_inactive(vp, cred)
	struct vnode *vp;
	struct ucred *cred;
{

#if	NeXT
XPR(XPR_FS, ("spec_inactive: entered: thread = 0x%x sp = 0x%x\n", current_thread(), VTOS(vp)));
	/* We have to lock because spec_fsync can sleep doing NFS calls */
	SNLOCK(VTOS(vp));
#endif	NeXT
	(void) spec_fsync(vp, cred);
	/* XXX
	 * spec_fsync does a xxx_setattr which may set u.u_error. Blech.
	 */
#if	NeXT
	SNUNLOCK(VTOS(vp));
#endif	NeXT
	u.u_error = 0;
#if	NeXT
XPR(XPR_FS, ("spec_inactive: calling sunsave: thread = 0x%x sp = 0x%x\n", current_thread(), VTOS(vp)));
#endif	NeXT
	sunsave(VTOS(vp));
	zfree (vm_info_zone, vp->v_vm_info);
	ZFREE(specfs_snode_zone, VTOS(vp));
	return (0);
}

int
spec_getattr(vp, vap, cred)
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	int error;
	register struct snode *sp;

	sp = VTOS(vp);
	error = VOP_GETATTR(sp->s_realvp, vap, cred);
	if (!error) {
		/* set current times from snode, even if older than vnode */
		vap->va_atime = sp->s_atime;
		vap->va_mtime = sp->s_mtime;
		vap->va_ctime = sp->s_ctime;

		/* set device-dependent blocksizes */
		switch (vap->va_mode&IFMT) {
		case VBLK:
			vap->va_blocksize = BLKDEV_IOSIZE;
			break;

		case VCHR:
			vap->va_blocksize = MAXBSIZE;
			break;

#if	STREAMS
		case VSTR:
			vap->va_blocksize=str_block_size(str_block_maxclass());
			break;
#endif	STREAMS
		}
	}
	return (error);
}

int
spec_setattr(vp, vap, cred)
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	struct snode *sp;
	int error;
	register int chtime = 0;

	sp = VTOS(vp);
	error = VOP_SETATTR(sp->s_realvp, vap, cred);
	if (!error) {
		/* if times were changed, update snode */
		if (vap->va_atime.tv_sec != -1) {
			sp->s_atime = vap->va_atime;
			chtime++;
		}
		if (vap->va_mtime.tv_sec != -1) {
			sp->s_mtime = vap->va_mtime;
			chtime++;
		}
		if (chtime)
			sp->s_ctime = time;
	}
	return (error);
}

int
spec_access(vp, mode, cred)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
{

	return (VOP_ACCESS(VTOS(vp)->s_realvp, mode, cred));
}

spec_link(vp, tdvp, tnm, cred)
	struct vnode *vp;
	struct vnode *tdvp;
	char *tnm;
	struct ucred *cred;
{

	return (VOP_LINK(VTOS(vp)->s_realvp, tdvp, tnm, cred));
}

/*
 * In order to sync out the snode times without multi-client problems,
 * make sure the times written out are never earlier than the times
 * already set in the vnode.
 */
int
spec_fsync(vp, cred)
	struct vnode *vp;
	struct ucred *cred;
{
	register int error;
	register struct snode *sp;
	struct vattr *vatmp;
	struct vattr *vap;

	sp = VTOS(vp);
	/* if times didn't change, don't flush anything */
	if ((sp->s_flag & (SACC|SUPD|SCHG)) == 0)
		return (0);

	ZALLOC(specfs_vattr_zone, vatmp, struct vattr *);
	error = VOP_GETATTR(sp->s_realvp, vatmp, cred);
	if (!error) {
		ZALLOC(specfs_vattr_zone, vap, struct vattr *);
		vattr_null(vap);
		vap->va_atime = timercmp(&vatmp->va_atime, &sp->s_atime, >) ?
		    vatmp->va_atime : sp->s_atime;
		vap->va_mtime = timercmp(&vatmp->va_mtime, &sp->s_mtime, >) ?
		    vatmp->va_mtime : sp->s_mtime;
		VOP_SETATTR(sp->s_realvp, vap, cred);
		ZFREE(specfs_vattr_zone, vap);
	}
	ZFREE(specfs_vattr_zone, vatmp);
#if	NeXT
XPR(XPR_FS, ("spec_fsync: VOP_FSYNC: thread = 0x%x sp = 0x%x sp->s_realvp = 0x%x\n", current_thread(), sp, sp->s_realvp));
#endif	NeXT
	(void) VOP_FSYNC(sp->s_realvp, cred);
	return (0);
}

int
spec_badop()
{
	panic("spec_badop");
}

int
spec_noop()
{

	return (EINVAL);
}

#if	SUN_LOCK
/*
 * Record-locking requests are passed back to the real vnode handler.
 */
int
spec_lockctl(vp, ld, cmd, cred)
	struct vnode *vp;
	struct flock *ld;
	int cmd;
	struct ucred *cred;
{
	return (VOP_LOCKCTL(VTOS(vp)->s_realvp, ld, cmd, cred));
}
#endif	SUN_LOCK

spec_fid(vp, fidpp)
	struct vnode *vp;
	struct fid **fidpp;
{
	return (VOP_FID(VTOS(vp)->s_realvp, fidpp));
}

spec_freefid(vp, fidp)
	struct vnode *vp;
	struct fid *fidp;
{
	return (VOP_FREEFID(VTOS(vp)->s_realvp, fidp));
}

zone_t specfs_snode_zone;
zone_t specfs_vattr_zone;

specfs_zone_init()
{
	bdev_vnodeops_zone_init();
	fifo_vnodeops_zone_init();

	specfs_snode_zone	= zinit(sizeof(struct snode), 1024*1024,
					0, FALSE, "specfs snode");

	specfs_vattr_zone	= zinit(sizeof(struct vattr), 1024*1024,
					0, FALSE, "specfs vattr");
}
