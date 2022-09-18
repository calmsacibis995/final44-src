h47498
s 00002/00002/00267
d D 8.7 94/01/21 19:46:59 bostic 7 6
c copyright typo
e
s 00011/00014/00258
d D 8.6 94/01/13 09:20:13 bostic 6 5
c lint and KNF conversion
e
s 00010/00006/00262
d D 8.5 94/01/11 16:09:17 mckusick 5 4
c fix panic message to print a string rather than a function address
e
s 00002/00002/00266
d D 8.4 94/01/04 22:13:22 bostic 4 3
c lint
e
s 00002/00002/00266
d D 8.3 93/09/23 16:09:44 bostic 3 2
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00264
d D 8.2 93/09/21 07:24:18 bostic 2 1
c changes for 4.4BSD-Lite requested by USL
e
s 00268/00000/00000
d D 8.1 93/09/05 09:38:40 mckusick 1 0
c common version for ffs and lfs
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef LFS_READWRITE
#define	BLKSIZE(a, b, c)	blksize(a)
#define	FS			struct lfs
#define	I_FS			i_lfs
#define	READ			lfs_read
I 5
#define	READ_S			"lfs_read"
E 5
#define	WRITE			lfs_write
I 5
#define	WRITE_S			"lfs_write"
E 5
#define	fs_bsize		lfs_bsize
#define	fs_maxfilesize		lfs_maxfilesize
#else
#define	BLKSIZE(a, b, c)	blksize(a, b, c)
#define	FS			struct fs
#define	I_FS			i_fs
#define	READ			ffs_read
I 5
#define	READ_S			"ffs_read"
E 5
#define	WRITE			ffs_write
I 5
#define	WRITE_S			"ffs_write"
E 5
#endif

/*
 * Vnode op for reading.
 */
/* ARGSUSED */
READ(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	register struct vnode *vp;
	register struct inode *ip;
	register struct uio *uio;
	register FS *fs;
	struct buf *bp;
	daddr_t lbn, nextlbn;
	off_t bytesinfile;
	long size, xfersize, blkoffset;
D 4
	int type, nextsize, error;
E 4
I 4
D 6
	int nextsize, error;
E 6
I 6
	int error;
E 6
E 4
	u_short mode;

	vp = ap->a_vp;
	ip = VTOI(vp);
	mode = ip->i_mode;
	uio = ap->a_uio;

#ifdef DIAGNOSTIC
	if (uio->uio_rw != UIO_READ)
D 5
		panic("%s: mode", READ);
E 5
I 5
		panic("%s: mode", READ_S);
E 5

	if (vp->v_type == VLNK) {
		if ((int)ip->i_size < vp->v_mount->mnt_maxsymlinklen)
D 5
			panic("%s: short symlink", READ);
E 5
I 5
			panic("%s: short symlink", READ_S);
E 5
	} else if (vp->v_type != VREG && vp->v_type != VDIR)
D 5
		panic("%s: type", READ);
E 5
I 5
		panic("%s: type %d", READ_S, vp->v_type);
E 5
#endif
	fs = ip->I_FS;
	if ((u_quad_t)uio->uio_offset > fs->fs_maxfilesize)
		return (EFBIG);

	for (error = 0, bp = NULL; uio->uio_resid > 0; bp = NULL) {
		if ((bytesinfile = ip->i_size - uio->uio_offset) <= 0)
			break;
		lbn = lblkno(fs, uio->uio_offset);
		nextlbn = lbn + 1;
		size = BLKSIZE(fs, ip, lbn);
		blkoffset = blkoff(fs, uio->uio_offset);
		xfersize = fs->fs_bsize - blkoffset;
		if (uio->uio_resid < xfersize)
			xfersize = uio->uio_resid;
		if (bytesinfile < xfersize)
			xfersize = bytesinfile;

#ifdef LFS_READWRITE
		(void)lfs_check(vp, lbn);
		error = cluster_read(vp, ip->i_size, lbn, size, NOCRED, &bp);
#else
D 6
		if (lblktosize(fs, nextlbn) > ip->i_size) {
E 6
I 6
		if (lblktosize(fs, nextlbn) > ip->i_size)
E 6
			error = bread(vp, lbn, size, NOCRED, &bp);
D 6
		} else {
			if (doclusterread) {
				error = cluster_read(vp,
				    ip->i_size, lbn, size, NOCRED, &bp);
			} else if (lbn - 1 == vp->v_lastr) {
				nextsize = BLKSIZE(fs, ip, nextlbn);
				error = breadn(vp, lbn,
				    size, &nextlbn, &nextsize, 1, NOCRED, &bp);
			} else {
				error = bread(vp, lbn, size, NOCRED, &bp);
			}
		}
E 6
I 6
		else if (doclusterread)
			error = cluster_read(vp,
			    ip->i_size, lbn, size, NOCRED, &bp);
		else if (lbn - 1 == vp->v_lastr) {
			int nextsize = BLKSIZE(fs, ip, nextlbn);
			error = breadn(vp, lbn,
			    size, &nextlbn, &nextsize, 1, NOCRED, &bp);
		} else
			error = bread(vp, lbn, size, NOCRED, &bp);
E 6
#endif
		if (error)
			break;
		vp->v_lastr = lbn;

		/*
		 * We should only get non-zero b_resid when an I/O error
		 * has occurred, which should cause us to break above.
		 * However, if the short read did not cause an error,
		 * then we want to ensure that we do not uiomove bad
		 * or uninitialized data.
		 */
		size -= bp->b_resid;
		if (size < xfersize) {
			if (size == 0)
				break;
			xfersize = size;
		}
		if (error =
D 2
		    uiomove(bp->b_un.b_addr + blkoffset, (int)xfersize, uio))
E 2
I 2
		    uiomove((char *)bp->b_data + blkoffset, (int)xfersize, uio))
E 2
			break;

		if (S_ISREG(mode) && (xfersize + blkoffset == fs->fs_bsize ||
		    uio->uio_offset == ip->i_size))
			bp->b_flags |= B_AGE;
		brelse(bp);
	}
	if (bp != NULL)
		brelse(bp);
D 2
	ip->i_flag |= IACC;
E 2
I 2
D 3
	ip->i_flag |= IACCESS;
E 3
I 3
	ip->i_flag |= IN_ACCESS;
E 3
E 2
	return (error);
}

/*
 * Vnode op for writing.
 */
WRITE(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	register struct vnode *vp;
	register struct uio *uio;
	register struct inode *ip;
	register FS *fs;
	struct buf *bp;
	struct proc *p;
	daddr_t lbn;
	off_t osize;
D 4
	int blkoffset, error, flags, ioflag, newblock, resid, size, xfersize;
E 4
I 4
	int blkoffset, error, flags, ioflag, resid, size, xfersize;
E 4

	ioflag = ap->a_ioflag;
	uio = ap->a_uio;
	vp = ap->a_vp;
	ip = VTOI(vp);

#ifdef DIAGNOSTIC
	if (uio->uio_rw != UIO_WRITE)
D 5
		panic("%s: mode", WRITE);
E 5
I 5
		panic("%s: mode", WRITE_S);
E 5
#endif

	switch (vp->v_type) {
	case VREG:
		if (ioflag & IO_APPEND)
			uio->uio_offset = ip->i_size;
		if ((ip->i_flags & APPEND) && uio->uio_offset != ip->i_size)
			return (EPERM);
		/* FALLTHROUGH */
	case VLNK:
		break;
	case VDIR:
		if ((ioflag & IO_SYNC) == 0)
D 5
			panic("%s: nonsync dir write", WRITE);
E 5
I 5
			panic("%s: nonsync dir write", WRITE_S);
E 5
		break;
	default:
D 5
		panic("%s: type", WRITE);
E 5
I 5
		panic("%s: type", WRITE_S);
E 5
	}

	fs = ip->I_FS;
	if (uio->uio_offset < 0 ||
	    (u_quad_t)uio->uio_offset + uio->uio_resid > fs->fs_maxfilesize)
		return (EFBIG);
	/*
	 * Maybe this should be above the vnode op call, but so long as
	 * file servers have no limits, I don't think it matters.
	 */
	p = uio->uio_procp;
	if (vp->v_type == VREG && p &&
	    uio->uio_offset + uio->uio_resid >
	    p->p_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(p, SIGXFSZ);
		return (EFBIG);
	}

	resid = uio->uio_resid;
	osize = ip->i_size;
	flags = ioflag & IO_SYNC ? B_SYNC : 0;

	for (error = 0; uio->uio_resid > 0;) {
		lbn = lblkno(fs, uio->uio_offset);
		blkoffset = blkoff(fs, uio->uio_offset);
		xfersize = fs->fs_bsize - blkoffset;
		if (uio->uio_resid < xfersize)
			xfersize = uio->uio_resid;
#ifdef LFS_READWRITE
		(void)lfs_check(vp, lbn);
		error = lfs_balloc(vp, xfersize, lbn, &bp);
#else
		if (fs->fs_bsize > xfersize)
			flags |= B_CLRBUF;
		else
			flags &= ~B_CLRBUF;

		error = ffs_balloc(ip,
		    lbn, blkoffset + xfersize, ap->a_cred, &bp, flags);
#endif
		if (error)
			break;
		if (uio->uio_offset + xfersize > ip->i_size) {
			ip->i_size = uio->uio_offset + xfersize;
			vnode_pager_setsize(vp, (u_long)ip->i_size);
		}
		(void)vnode_pager_uncache(vp);

		size = BLKSIZE(fs, ip, lbn) - bp->b_resid;
		if (size < xfersize)
			xfersize = size;

		error =
D 2
		    uiomove(bp->b_un.b_addr + blkoffset, (int)xfersize, uio);
E 2
I 2
		    uiomove((char *)bp->b_data + blkoffset, (int)xfersize, uio);
E 2
#ifdef LFS_READWRITE
		(void)VOP_BWRITE(bp);
#else
		if (ioflag & IO_SYNC)
			(void)bwrite(bp);
		else if (xfersize + blkoffset == fs->fs_bsize)
			if (doclusterwrite)
				cluster_write(bp, ip->i_size);
			else {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			}
		else
			bdwrite(bp);
#endif
		if (error || xfersize == 0)
			break;
D 2
		ip->i_flag |= IUPD | ICHG;
E 2
I 2
D 3
		ip->i_flag |= IUPDATE | ICHANGE;
E 3
I 3
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 3
E 2
	}
	/*
	 * If we successfully wrote any data, and we are not the superuser
	 * we clear the setuid and setgid bits as a precaution against
	 * tampering.
	 */
	if (resid > uio->uio_resid && ap->a_cred && ap->a_cred->cr_uid != 0)
		ip->i_mode &= ~(ISUID | ISGID);
	if (error) {
		if (ioflag & IO_UNIT) {
			(void)VOP_TRUNCATE(vp, osize,
			    ioflag & IO_SYNC, ap->a_cred, uio->uio_procp);
			uio->uio_offset -= resid - uio->uio_resid;
			uio->uio_resid = resid;
		}
	} else if (resid > uio->uio_resid && (ioflag & IO_SYNC))
		error = VOP_UPDATE(vp, &time, &time, 1);
	return (error);
}
E 1
