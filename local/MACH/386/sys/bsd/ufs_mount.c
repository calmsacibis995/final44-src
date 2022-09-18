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
 * $Log:	ufs_mount.c,v $
 * Revision 2.11  89/09/22  13:53:55  af
 * 	A stupid typo.
 * 	[89/09/14  15:42:11  af]
 * 
 * Revision 2.10  89/08/28  22:32:21  af
 * 	Made smart fsck a separate conditional, and upgraded this file
 * 	from the NFS one that I was really only using. Sigh.
 * 	[89/08/05            af]
 * 
 * Revision 2.9  89/07/14  15:25:58  rvb
 * 	Added "smart fsck" support.  the fs_clean field (otherwise
 * 	unused) holds now a special value if the filesystem was
 * 	unmounted properly.  If so, there is no need to check it before
 * 	mounting it, and fsck(1) can find this out.
 * 	[89/07/11            af]
 * 
 * Revision 2.8  89/03/09  19:33:09  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:29:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:35:22  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:08:48  af
 * 	Changes for I386: EXL "open type" 3rd arg to switches
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  88/10/18  03:16:35  mwyoung
 * 	Should call the inode_pager to uncache objects on a
 * 	particular mounted device when unmounting.  Temporarily
 * 	do nothing.
 * 	[88/09/21  01:40:15  mwyoung]
 * 
 * Revision 2.3  88/08/24  01:36:01  mwyoung
 * 	Corrected include file references.
 * 	[88/08/23  00:40:32  mwyoung]
 * 
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Renamed FS_?NOSPC flag bits to URPW_?NOSPC; altered
 *	Vice rmt_mount() call interface to facilitate saving the
 *	file system name for resource pausing.
 *	[ V5.1(XF23) ]
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 17-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use kernel_map to allocate wired-down memory instead of
 *	user_pt_map.
 *
 * 25-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-type option.
 *
 * 17-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add mfs_cache_clear call to remove cached mapped files on an
 *	unmount.
 *
 *  8-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VICE changes -- include vice.h.  Rearranged some code for
 *	proper conditional compilation.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added hooks for ITC/Andrew remote file system;
 *
 * 29-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added swapping preference initialization (MACH).
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed water marks for new filesystems.
 *
 * 21-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Call vm_object_cache_clear to remove any cached objects that
 *	might be on device being dismounted.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE:  Changed to initialize file system low water mark
 *	fields on mount.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_mount.c	7.1 (Berkeley) 6/5/86
 */

#include <quota.h>
#include <cputypes.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/fs.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/file.h>
#include <sys/conf.h>

#include <vm/vm_kern.h>
#include <vm/vm_object.h>

#if	EXL
#include <machine/open.h>
#endif	EXL

#if	VICE
extern int	rmt_maj;	/* major device number of the remote file
				   system intermediary device driver */
#endif	VICE

struct	mount mount[NMOUNT];

smount()
{
	register struct a {
		char	*fspec;
		char	*freg;
		int	ronly;
	} *uap = (struct a *)u.u_ap;
	dev_t dev;
	register struct inode *ip;
	register struct fs *fs;
	register struct nameidata *ndp = &u.u_nd;
	u_int len;

	u.u_error = getmdev(&dev, uap->fspec);
	if (u.u_error)
		return;
#if	VICE
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKPARENT;
	/* N.B.  As indicated in the comment in namei, LOOKUP | LOCKPARENT does NOT
	         lock the parent. */
#else	VICE
	ndp->ni_nameiop = LOOKUP | FOLLOW;
#endif	VICE
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = (caddr_t)uap->freg;
	ip = namei(ndp);
	if (ip == NULL)
		return;
	if (ip->i_count != 1) {
		iput(ip);
#if	VICE
		irele(ndp->ni_pdir);
#endif	VICE
		u.u_error = EBUSY;
		return;
	}
	if ((ip->i_mode&IFMT) != IFDIR) {
		iput(ip);
#if	VICE
		irele(ndp->ni_pdir);
#endif	VICE
		u.u_error = ENOTDIR;
		return;
	}
#if	VICE
	if (major(dev) == rmt_maj) {
		extern struct fs *rmt_mount();

		fs = rmt_mount(dev, ip, ndp->ni_pdir);
		if (fs)
		    goto setname;
		return;
	}
	irele(ndp->ni_pdir);
#endif	VICE
	fs = mountfs(dev, uap->ronly, ip);
	if (fs == 0)
		return;
#if	VICE
setname:
#endif	VICE
	(void) copyinstr(uap->freg, fs->fs_fsmnt, sizeof(fs->fs_fsmnt)-1, &len);
	bzero(fs->fs_fsmnt + len, sizeof (fs->fs_fsmnt) - len);
}

#if	VICE
struct mount *getmountstruct(dev)
	dev_t dev;
{
	register struct mount *mp;
    	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if ((mp->m_bufp != 0 || mp->m_remote) && dev == mp->m_dev)
			return 0;
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)

		if (mp->m_bufp == 0 && mp->m_remote == 0)
			return mp;
	return 0;
}
#endif	VICE

/* this routine has races if running twice */
struct fs *
mountfs(dev, ronly, ip)
	dev_t dev;
	int ronly;
	struct inode *ip;
{
	register struct mount *mp = 0;
	struct buf *tp = 0;
	register struct buf *bp = 0;
	register struct fs *fs;
	int blks;
	caddr_t space;
	int i, size;
	register error;
	int needclose = 0;

	error =
#if	EXL
	    (*bdevsw[major(dev)].d_open)(dev, ronly ? FREAD : FREAD|FWRITE, OTYP_MNT);
#else	EXL
	    (*bdevsw[major(dev)].d_open)(dev, ronly ? FREAD : FREAD|FWRITE);
#endif	EXL
	if (error)
		goto out;
	needclose = 1;
	tp = bread(dev, SBLOCK, SBSIZE);
	if (tp->b_flags & B_ERROR)
		goto out;
#if	VICE
	mp = getmountstruct(dev);
	if (mp == 0) {
		error = EBUSY;	/* could be EMFILE, we don't know which! */
		goto out;
	}
#else	VICE
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp != 0 && dev == mp->m_dev) {
			mp = 0;
			error = EBUSY;
			needclose = 0;
			goto out;
		}
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp == 0)
			goto found;
	mp = 0;
	error = EMFILE;		/* needs translation */
	goto out;
found:
#endif	VICE
	mp->m_bufp = tp;	/* just to reserve this slot */
	mp->m_dev = NODEV;
	fs = tp->b_un.b_fs;
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE
	    || fs->fs_bsize < sizeof(struct fs)) {
		error = EINVAL;		/* also needs translation */
		goto out;
	}
#if	defined(SMART_FSCK) || defined(PMAX)
	if (fs->fs_clean != FS_CLEAN)
		printf("ufs_mount: file system not cleaned -- please fsck\n");
#endif	defined(SMART_FSCK) || defined(PMAX)
	bp = geteblk((int)fs->fs_sbsize);
	mp->m_bufp = bp;
	bcopy((caddr_t)tp->b_un.b_addr, (caddr_t)bp->b_un.b_addr,
	   (u_int)fs->fs_sbsize);
	brelse(tp);
	tp = 0;
	fs = bp->b_un.b_fs;
	fs->fs_ronly = (ronly != 0);
	if (ronly == 0) {
		fs->fs_fmod = 1;
#if	defined(SMART_FSCK) || defined(PMAX)
		fs->fs_clean = 0;	/* mounted writeable ==> dirty */
#endif	defined(SMART_FSCK) || defined(PMAX)
	}
	blks = howmany(fs->fs_cssize, fs->fs_fsize);
	space = (caddr_t)kmem_alloc(kernel_map, (vm_size_t)fs->fs_cssize);
	if (space == 0) {
		error = ENOMEM;
		goto out;
	}
	for (i = 0; i < blks; i += fs->fs_frag) {
		size = fs->fs_bsize;
		if (i + fs->fs_frag > blks)
			size = (blks - i) * fs->fs_fsize;
		tp = bread(dev, fsbtodb(fs, fs->fs_csaddr + i), size);
		if (tp->b_flags&B_ERROR) {
			kmem_free(kernel_map, (vm_offset_t)space,
					(vm_size_t)fs->fs_cssize);
			goto out;
		}
		bcopy((caddr_t)tp->b_un.b_addr, space, (u_int)size);
		fs->fs_csp[fragstoblks(fs, i)] = (struct csum *)space;
		space += size;
		brelse(tp);
		tp = 0;
	}
	/*
	 *  Enable first file system/inodes full console messages and calculate
	 *  low water pause/high water resume marks for fragments and inodes.
 	 *
	 *  Fragment water marks:
	 *  lo - (1 or minfree)% of total (but <= 100)
	 *  hi - 2* lo (but <= 200)
	 *
	 *  Inode water marks:
	 *  lo/hi - 1% of total (but <= 50)
	 */
	fs->fs_flags  &= ~(URPW_FNOSPC|URPW_INOSPC);
	FS_FLOWAT(fs) = ((fs->fs_dsize * fs->fs_minfree)/100);
	FS_FHIWAT(fs) = FS_FLOWAT(fs);
	if (FS_FHIWAT(fs) > 100)
		FS_FHIWAT(fs) += 100;
	else
		FS_FHIWAT(fs) *= 2;
	FS_ILOWAT(fs) = ((fs->fs_ncg * fs->fs_ipg)/100);
	if (FS_ILOWAT(fs) > 50)
	    FS_ILOWAT(fs) = 50;
	FS_IHIWAT(fs) = FS_ILOWAT(fs);
#ifdef	DEBUG
	printf("flowat=%d, fhiwat=%d, ilowat=%d, ihiwat=%d\n",
	       FS_FLOWAT(fs), FS_FHIWAT(fs), FS_ILOWAT(fs), FS_IHIWAT(fs));
#endif	DEBUG
	mp->m_inodp = ip;
	mp->m_dev = dev;
	if (ip) {
		ip->i_flag |= IMOUNT;
		cacheinval(ip);
		iunlock(ip);
	}
	inode_swap_preference(mp->m_dev, FALSE, FALSE);
	return (fs);
out:
	if (error == 0)
		error = EIO;
	if (ip)
		iput(ip);
	if (mp)
		mp->m_bufp = 0;
	if (bp)
		brelse(bp);
	if (tp)
		brelse(tp);
	if (needclose) {
#if	EXL
		(*bdevsw[major(dev)].d_close)(dev, ronly? FREAD : FREAD|FWRITE, OTYP_MNT);
#else	EXL
		(*bdevsw[major(dev)].d_close)(dev, ronly? FREAD : FREAD|FWRITE);
#endif	EXL
		binval(dev);
	}
	u.u_error = error;
	return (0);
}

umount()
{
	struct a {
		char	*fspec;
	} *uap = (struct a *)u.u_ap;

	u.u_error = unmount1(uap->fspec, 0);
}

unmount1(fname, forcibly)
	caddr_t fname;
	int forcibly;
{
	dev_t dev;
	register struct mount *mp;
	int stillopen, flag, error;
	register struct inode *ip;
	register struct fs *fs;

	error = getmdev(&dev, fname);
	if (error)
		return (error);
#if	VICE
	if (major(dev) == rmt_maj)
		return(rmt_unmount(dev));
#endif	VICE
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp != NULL && dev == mp->m_dev)
			goto found;
	return (EINVAL);
found:
#if	MACH_NBC
	mfs_cache_clear();		/* remove cached mapped files */
#endif	MACH_NBC
	nchinval(dev);	/* flush the name cache */
	update();
#if	QUOTA
	if ((stillopen = iflush(dev, mp->m_qinod)) < 0 && !forcibly)
#else	QUOTA
	if ((stillopen = iflush(dev)) < 0 && !forcibly)
#endif	QUOTA
		return (EBUSY);
	if (stillopen < 0)
		return (EBUSY);			/* XXX */
#if	QUOTA
	closedq(mp);
	/*
	 * Here we have to iflush again to get rid of the quota inode.
	 * A drag, but it would be ugly to cheat, & this doesn't happen often
	 */
	(void)iflush(dev, (struct inode *)NULL);
#endif	QUOTA
	ip = mp->m_inodp;
	ip->i_flag &= ~IMOUNT;
	irele(ip);
	fs = mp->m_bufp->b_un.b_fs;
#if	defined(SMART_FSCK) || defined(PMAX)
	/* mark the file system clean */
	if (!fs->fs_ronly) {
		struct buf *bp;
		/* This does "half" of an sbupdate() */
		bp = getblk(mp->m_devp, SBLOCK, (int)fs->fs_bsize);
		bcopy((caddr_t)fs, bp->b_un.b_addr, (u_int)fs->fs_sbsize);
		bp->b_un.b_fs->fs_flowat = 0;
		bp->b_un.b_fs->fs_fhiwat = 0;
		bp->b_un.b_fs->fs_ilowat = 0;
		bp->b_un.b_fs->fs_ihiwat = 0;
		bp->b_un.b_fs->fs_flags = 0;
		bp->b_un.b_fs->fs_clean = FS_CLEAN;
		bwrite(bp);
	}
#endif	defined(SMART_FSCK) || defined(PMAX)
	kmem_free(kernel_map, (vm_offset_t)fs->fs_csp[0],
			      (vm_size_t)fs->fs_cssize);
	flag = !fs->fs_ronly;
	brelse(mp->m_bufp);
	mp->m_bufp = 0;
	mp->m_dev = 0;
#if	VICE			/* DEBUG */
	if (mp->m_remote)
		panic("unmount1:  remote flag in mount structure!");
#endif	VICE
	if (!stillopen) {
#if	EXL
		(*bdevsw[major(dev)].d_close)(dev, flag, OTYP_MNT);
#else	EXL
		(*bdevsw[major(dev)].d_close)(dev, flag);
#endif	EXL
		binval(dev);
	}
	return (0);
}

sbupdate(mp)
	struct mount *mp;
{
	register struct fs *fs = mp->m_bufp->b_un.b_fs;
	register struct buf *bp;
	int blks;
	caddr_t space;
	int i, size;

	bp = getblk(mp->m_dev, SBLOCK, (int)fs->fs_sbsize);
	bcopy((caddr_t)fs, bp->b_un.b_addr, (u_int)fs->fs_sbsize);
	/*
	 *  These fields are supposed to be zero in 4.2 super-blocks and are
	 *  currently maintained only internally so we can just zero them here
	 *  (in the outgoing copy) for now.  Perhaps someday it will make sense
	 *  to record some of them on disk...
	 */
	bp->b_un.b_fs->fs_flowat = 0;
	bp->b_un.b_fs->fs_fhiwat = 0;
	bp->b_un.b_fs->fs_ilowat = 0;
	bp->b_un.b_fs->fs_ihiwat = 0;
	bp->b_un.b_fs->fs_flags = 0;
	bwrite(bp);
	blks = howmany(fs->fs_cssize, fs->fs_fsize);
	space = (caddr_t)fs->fs_csp[0];
	for (i = 0; i < blks; i += fs->fs_frag) {
		size = fs->fs_bsize;
		if (i + fs->fs_frag > blks)
			size = (blks - i) * fs->fs_fsize;
		bp = getblk(mp->m_dev, fsbtodb(fs, fs->fs_csaddr + i), size);
		bcopy(space, bp->b_un.b_addr, (u_int)size);
		space += size;
		bwrite(bp);
	}
}

/*
 * Common code for mount and umount.
 * Check that the user's argument is a reasonable
 * thing on which to mount, and return the device number if so.
 */
getmdev(pdev, fname)
	caddr_t fname;
	dev_t *pdev;
{
	dev_t dev;
	register struct inode *ip;
	register struct nameidata *ndp = &u.u_nd;

	if (!suser())
		return (u.u_error);
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
	ip = namei(ndp);
	if (ip == NULL) {
		if (u.u_error == ENOENT)
			return (ENODEV); /* needs translation */
		return (u.u_error);
	}
#if	VICE
	dev = (dev_t)ip->i_rdev;
	if (major(dev) != rmt_maj) {
#endif	VICE
	if ((ip->i_mode&IFMT) != IFBLK) {
		iput(ip);
		return (ENOTBLK);
	}
#if	VICE
	if (major(dev) >= nblkdev) {
		iput(ip);
		return (ENXIO);
	}
	}
	iput(ip);
#else	VICE
	dev = (dev_t)ip->i_rdev;
	iput(ip);
	if (major(dev) >= nblkdev) {
		return (ENXIO);
	}
#endif	VICE
	*pdev = dev;
	return (0);
}
