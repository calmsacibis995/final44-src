h44232
s 00007/00001/00140
d D 5.1 91/04/16 18:38:17 bostic 3 2
c new copyright; att/bsd/shared
e
s 00011/00002/00130
d D 1.2 90/04/17 09:58:26 mckusick 2 1
c add mfs_args struct to Appendix
e
s 00132/00000/00000
d D 1.1 90/04/13 16:55:32 mckusick 1 0
c date and time created 90/04/13 16:55:32 by mckusick
e
u
U
t
T
I 1
D 3
.\"	%W%	(Copyright 1990 M. K. McKusick)	%E%
E 3
I 3
.\" Copyright (c) 1990 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 3
.bp
.nr PS 10
.nr VS 12
.SH
Appendix A - Implementation Details
.LP
.nf
.vS
/*
 * This structure defines the control data for the memory
 * based file system.
 */
struct mfsnode {
	struct	vnode *mfs_vnode;	/* vnode associated with this mfsnode */
	caddr_t	mfs_baseoff;		/* base of file system in memory */
	long	mfs_size;		/* size of memory file system */
	pid_t	mfs_pid;		/* supporting process pid */
	struct	buf *mfs_buflist;	/* list of I/O requests */
};

/*
 * Convert between mfsnode pointers and vnode pointers
 */
D 2
#define VTOMFS(vp)	((struct mfsnode *)(vp)->v_data)
#define MFSTOV(mfsp)	((mfsp)->mfs_vnode)
E 2
I 2
#define	VTOMFS(vp)	((struct mfsnode *)(vp)->v_data)
#define	MFSTOV(mfsp)	((mfsp)->mfs_vnode)
E 2
#define	MFS_EXIT	(struct buf *)-1
I 2

/*
 * Arguments to mount MFS
 */
struct mfs_args {
	char	*name;		/* name to export for statfs */
	caddr_t	base;		/* base address of file system in memory */
	u_long	size;		/* size of file system */
};
E 2
.bp
/*
 * Mount an MFS filesystem.
 */
mfs_mount(mp, path, data)
	struct mount *mp;
	char *path;
	caddr_t data;
{
	struct vnode *devvp;
	struct mfsnode *mfsp;
	struct buf *bp;
	struct mfs_args args;

	/*
	 * Create a block device to represent the disk.
	 */
	devvp = getnewvnode(VT_MFS, VBLK, &mfs_vnodeops);
	mfsp = VTOMFS(devvp);
	/*
	 * Save base address of the filesystem from the supporting process.
	 */
	copyin(data, &args, (sizeof mfs_args));
	mfsp->mfs_baseoff = args.base;
	mfsp->mfs_size = args.size;
	/*
	 * Record the process identifier of the supporting process.
	 */
	mfsp->mfs_pid = u.u_procp->p_pid;
	/*
	 * Mount the filesystem.
	 */
	mfsp->mfs_buflist = NULL;
	mountfs(devvp, mp);
	/*
	 * Loop processing I/O requests.
	 */
	while (mfsp->mfs_buflist != MFS_EXIT) {
		while (mfsp->mfs_buflist != NULL) {
			bp = mfsp->mfs_buflist;
			mfsp->mfs_buflist = bp->av_forw;
			offset = mfsp->mfs_baseoff + (bp->b_blkno * DEV_BSIZE);
			if (bp->b_flags & B_READ)
				copyin(offset, bp->b_un.b_addr, bp->b_bcount);
			else /* write_request */
				copyout(bp->b_un.b_addr, offset, bp->b_bcount);
			biodone(bp);
		}
		sleep((caddr_t)devvp, PWAIT);
	}
}
.bp
/*
 * If the MFS process requests the I/O then we must do it directly.
 * Otherwise put the request on the list and request the MFS process
 * to be run.
 */
mfs_strategy(bp)
	struct buf *bp;
{
	struct vnode *devvp;
	struct mfsnode *mfsp;
	off_t offset;

	devvp = bp->b_vp;
	mfsp = VTOMFS(devvp);
	if (mfsp->mfs_pid == u.u_procp->p_pid) {
		offset = mfsp->mfs_baseoff + (bp->b_blkno * DEV_BSIZE);
		if (bp->b_flags & B_READ)
			copyin(offset, bp->b_un.b_addr, bp->b_bcount);
		else /* write_request */
			copyout(bp->b_un.b_addr, offset, bp->b_bcount);
		biodone(bp);
	} else {
		bp->av_forw = mfsp->mfs_buflist;
		mfsp->mfs_buflist = bp;
		wakeup((caddr_t)bp->b_vp);
	}
}

/*
 * The close routine is called by unmount after the filesystem
 * has been successfully unmounted.
 */
mfs_close(devvp)
	struct vnode *devvp;
{
	struct mfsnode *mfsp = VTOMFS(vp);
	struct buf *bp;

	/*
	 * Finish any pending I/O requests.
	 */
	while (bp = mfsp->mfs_buflist) {
		mfsp->mfs_buflist = bp->av_forw;
		mfs_doio(bp, mfsp->mfs_baseoff);
		wakeup((caddr_t)bp);
	}
	/*
	 * Send a request to the filesystem server to exit.
	 */
	mfsp->mfs_buflist = MFS_EXIT;
	wakeup((caddr_t)vp);
}
.vE
E 1
