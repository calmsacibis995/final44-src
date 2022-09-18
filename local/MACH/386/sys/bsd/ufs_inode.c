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
 * $Log:	ufs_inode.c,v $
 * Revision 2.12  89/08/28  22:32:12  af
 * 	When truncating an existing file, delay the disk update.
 * 	Comes from Ultrix, useful for defending against bogus benchmarks
 * 	(e.g. AIM) only.
 * 	[89/08/23            af]
 * 
 * Revision 2.11  89/08/08  21:46:10  jsb
 * 	Added Michael's fix to iflush() to clear the references that the
 * 	inode pager keeps for cached files.
 * 	[89/07/20            af]
 * 
 * Revision 2.10  89/04/22  15:22:10  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/03/09  19:33:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/26  11:29:08  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/02/09  04:35:16  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.6  89/01/31  01:20:55  rpd
 * 	Really fix fast symbolic links.  Must handle in itrunc.
 * 	[89/01/25            dlb]
 * 
 * Revision 2.5  89/01/18  00:43:51  jsb
 * 	Vnode support, including David Black's fixes for fast symbolic links.
 * 	[89/01/16            jsb]
 * 
 * Revision 2.4  88/07/17  17:28:06  mwyoung
 * Use new memory object types.
 * 
 * Revision 2.3.1.1  88/07/04  15:00:46  mwyoung
 * See below.
 * 
 *
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Installed bug fix from Jay Kistler to avoid problems when the
 *	iget() caller is not expecting to transfer into VICE (e.g. from
 *	the bind() call).
 *	[ V5.1(XF23) ]
 *
 *  9-Mar-88 John Seamons (jks) at NeXT
 *	MACH_VFS: attach vm_info structure to inode, move mfs_init() to main().
 *
 * 14-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed how irele() checks for active use by the inode pager.
 *	Reduced history.  Participants so far: avie, mwyoung, dbg,
 *	bolosky, jjk, dlb, mja.
 *
 * 28-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Add support for vnodes.
 */
 
#include <mach_nbc.h>
#include <quota.h>
#include <vice.h>
#include <xpr_debug.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_inode.c	7.1 (Berkeley) 6/5/86
 */


#include <mach/memory_object.h>
#include <builtin/inode_pager.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mount.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/fs.h>
#if	QUOTA
#include <sys/quota.h>
#endif	QUOTA
#include <sys/buf.h>
#include <kern/mfs.h>
#if	MACH_NBC
#include <kern/mfs.h>
#endif	MACH_NBC
#include <sys/kernel.h>
#if	NeXT
#include <kern/xpr.h>
#include <kern/thread.h>
#include <kern/task.h>
#include <sys/proc.h>
#endif	NeXT

#define INOHSZ	512
#if	((INOHSZ&(INOHSZ-1)) == 0)
#define INOHASH(dev,ino)	(((dev)+(ino))&(INOHSZ-1))
#else
#define INOHASH(dev,ino)	(((unsigned)((dev)+(ino)))%INOHSZ)
#endif

union ihead {				/* inode LRU cache, Chris Maltby */
	union  ihead *ih_head[2];
	struct inode *ih_chain[2];
} ihead[INOHSZ];

struct inode *ifreeh, **ifreet;

/* 
 *  Define these in one place to avoid string constant replication.
 */
char *PANICMSG_IINCR = "iincr";
char *PANICMSG_IDECR = "idecr";

/*
 * Initialize hash links for inodes
 * and build inode free list.
 */
ihinit()
{
	register int i;
	register struct inode *ip = inode;
	register union  ihead *ih = ihead;

	for (i = INOHSZ; --i >= 0; ih++) {
		ih->ih_head[0] = ih;
		ih->ih_head[1] = ih;
	}
	ifreeh = ip;
	ifreet = &ip->i_freef;
	ip->i_freeb = &ifreeh;
	ip->i_forw = ITOIH(ip);
	ip->i_back = ITOIH(ip);
	ip->i_type = ITYPE_UFS;
	ip->i_vm_info = VM_INFO_NULL;
	vm_info_init(ip);
	ip->i_vm_info->close_flush = FALSE;
	for (i = ninode; --i > 0; ) {
		++ip;
		ip->i_forw = ITOIH(ip);
		ip->i_back = ITOIH(ip);
		*ifreet = ip;
		ip->i_freeb = ifreet;
		ifreet = &ip->i_freef;
		ip->i_type = ITYPE_UFS;
		ip->i_vm_info = VM_INFO_NULL;
		vm_info_init(ip);
		ip->i_vm_info->close_flush = FALSE;
	}
	ip->i_freef = NULL;
}

#ifdef	notdef
/*
 * Find an inode if it is incore.
 * This is the equivalent, for inodes,
 * of ``incore'' in bio.c or ``pfind'' in subr.c.
 */
struct inode *
ifind(dev, ino)
	dev_t dev;
	ino_t ino;
{
	register struct inode *ip;
	register union  ihead *ih;

	ih = &ihead[INOHASH(dev, ino)];
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = IHTOI(ip->i_forw))
		if (ino==ip->i_number && dev==ip->i_dev)
			return (ip);
	return ((struct inode *)0);
}
#endif	notdef

/*
 * Look up an inode by device,inumber.
 * If it is in core (in the inode structure),
 * honor the locking protocol.
 * If it is not in core, read it in from the
 * specified device.
 * If the inode is mounted on, perform
 * the indicated indirection.
 * In all cases, a pointer to a locked
 * inode structure is returned.
 *
 * panic: no imt -- if the mounted file
 *	system is not in the mount table.
 *	"cannot happen"
 */
struct inode *
iget(dev, fs, ino)
	dev_t dev;
	register struct fs *fs;
	ino_t ino;
{
	register struct inode *ip;
	register union  ihead *ih;
	register struct mount *mp;
	register struct buf *bp;
	register struct dinode *dp;
	register struct inode *iq;

loop:
	CHECK_MOUNT_DEV(mp, dev, fs);
	ih = &ihead[INOHASH(dev, ino)];
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = IHTOI(ip->i_forw))
		if (ino == ip->i_number && dev == ip->i_dev) {
			/*
			 * Following is essentially an inline expanded
			 * copy of igrab(), expanded inline for speed,
			 * and so that the test for a mounted on inode
			 * can be deferred until after we are sure that
			 * the inode isn't busy.
			 */
			if ((ip->i_flag&ILOCKED) != 0) {
				ip->i_flag |= IWANT;
				sleep((caddr_t)ip, PINOD);
				goto loop;
			}
			CHECK_MOUNT_TABLE(ip);
			if (!INODE_REFERENCED(ip)) {	/* ino on free list */
				if (iq = ip->i_freef)
					iq->i_freeb = ip->i_freeb;
				else
					ifreet = ip->i_freeb;
				*ip->i_freeb = iq;
				ip->i_freef = NULL;
				ip->i_freeb = NULL;
#if	VICE
				ip->i_rmt_dev = NODEV;
#endif	VICE
				ip->i_vm_info->pager = MEMORY_OBJECT_NULL;
			}
			ip->i_flag |= ILOCKED;
			REFERENCE_INODE(ip);
			INCR_INODE(ip);
#if	NeXT
	XPR(XPR_FS, ("inode locked: ip 0x%x thread 0x%x proc 0x%x pid %d (iget from hash table)\n", ip, current_thread(), (int)u.u_procp, u.u_procp->p_pid));
#endif	NeXT
			return(ip);
		}
	PURGE_INODE_FREELIST;
	if ((ip = ifreeh) == NULL) {
		tablefull("inode");
		u.u_error = ENFILE;
		return(NULL);
	}
	if (INODE_REFERENCED(ip))
		panic("free inode isn't");
	if (iq = ip->i_freef)
		iq->i_freeb = &ifreeh;
	ifreeh = iq;
	ip->i_freef = NULL;
	ip->i_freeb = NULL;
#if	MACH_NBC
	/*
	 *	Flush the inode from the file map cache.
	 */
	mfs_uncache(ip);
#endif	MACH_NBC
	/*
	 * Now to take inode off the hash chain it was on
	 * (initially, or after an iflush, it is on a "hash chain"
	 * consisting entirely of itself, and pointed to by no-one,
	 * but that doesn't matter), and put it on the chain for
	 * its new (ino, dev) pair
	 */
	remque(ip);
	insque(ip, ih);
	ip->i_vm_info->pager = MEMORY_OBJECT_NULL;
#if	QUOTA
	dqrele(ip->i_dquot);
	ip->i_dquot = NULL;
#endif	QUOTA
	ip->i_dev = dev;
	INIT_DEV_MOUNT(ip, mp);
	ip->i_fs = fs;
	ip->i_number = ino;
	INVALIDATE_CACHE(ip);
	INIT_DIRECTORY(ip, 0);
	ip->i_flag |= ILOCKED;
	REFERENCE_INODE(ip);
	INIT_INCR_INODE(ip);
	ip->i_lastr = 0;
#if	VICE
	/* ? Do we still need this???? */
	ip->i_rmt_dev = NODEV;
#endif	VICE
	bp = bread(INODE_DEV(ip), fsbtodb(fs, itod(fs, ino)), (int)fs->fs_bsize);
	/*
	 * Check I/O errors
	 */
	if ((bp->b_flags&B_ERROR) != 0) {
		brelse(bp);
		/*
		 * the inode doesn't contain anything useful, so it would
		 * be misleading to leave it on its hash chain.
		 * 'iput' will take care of putting it back on the free list.
		 */
		remque(ip);
		ip->i_forw = ITOIH(ip);
		ip->i_back = ITOIH(ip);
		/*
		 *	Losing the inumber is sure to cause a panic.
		 *	Annoying printf is preferable.
		 */
		printf("iget: dev = 0x%x, ino = %d, fs = %s: bread error\n",
			INODE_DEV(ip), ip->i_number, fs->fs_fsmnt);
#if	QUOTA
		NO_DISK_QUOTA(ip);
#endif	QUOTA
		DONT_USE_INODE(ip);
		return(NULL);
	}
	dp = bp->b_un.b_dino;
	dp += itoo(fs, ino);
	ip->i_ic = dp->di_ic;
	INITIALIZE_INODE(ip, mp);
	brelse(bp);
#if	QUOTA
	if (ip->i_mode == 0)
		NO_DISK_QUOTA(ip);
	else
		ip->i_dquot = INODE_QUOTA(ip);
#endif	QUOTA
	ip->i_vm_info->pager = MEMORY_OBJECT_NULL;
#if	MACH_NBC
	ip->i_vm_info->inode_size = ip->i_size;
#endif	MACH_NBC
	return (ip);
}

/*
 * Convert a pointer to an inode into a reference to an inode.
 *
 * This is basically the internal piece of iget (after the
 * inode pointer is located) but without the test for mounted
 * filesystems.  It is caller's responsibility to check that
 * the inode pointer is valid.
 */
igrab(ip)
	register struct inode *ip;
{
	while ((ip->i_flag&ILOCKED) != 0) {
		ip->i_flag |= IWANT;
		sleep((caddr_t)ip, PINOD);
	}
	if (ip->i_count == 0) {		/* ino on free list */
		register struct inode *iq;

		if (iq = ip->i_freef)
			iq->i_freeb = ip->i_freeb;
		else
			ifreet = ip->i_freeb;
		*ip->i_freeb = iq;
		ip->i_freef = NULL;
		ip->i_freeb = NULL;
	}
	ip->i_count++;
	ip->i_flag |= ILOCKED;
}

/*
 * Decrement reference count of
 * an inode structure.
 * On the last reference,
 * write the inode out and if necessary,
 * truncate and deallocate the file.
 */
iput(ip)
	register struct inode *ip;
{

	if ((ip->i_flag & ILOCKED) == 0)
		panic("iput");
	IUNLOCK(ip);
	RELEASE_INODE(ip);
}

irele(ip)
	register struct inode *ip;
{
	int mode;
	int check;

	RELEASE_INODE_CHECK(ip, check);
	if (check) {
		ip->i_flag |= ILOCKED;
#if	NeXT
	XPR(XPR_FS, ("inode locked: ip 0x%x thread 0x%x proc 0x%x pid %d (iinactive)\n", ip, current_thread(), (int)u.u_procp, u.u_procp->p_pid));
#endif	NeXT
		if (ip->i_nlink <= 0 && !FS_READ_ONLY(ip)) {
			/*
			 * If this inode is in use by the inode pager,
			 * then do not truncate files used for paging (they
			 * are anonymous inodes created by the pager).
			 */
			if (!inode_pager_active(ip->i_vm_info->pager)) { /* might still not be right XXX */
			INCR_INODE_GEN(ip);
			itrunc(ip, (u_long)0);
			mode = ip->i_mode;
			ip->i_mode = 0;
			ip->i_rdev = 0;
			CHGUPD_INODE(ip);
			ifree(ip, ip->i_number, mode);
#if	QUOTA
			(void) chkiq(QUOTA_DEV(ip), ip, ip->i_uid, 0);
			dqrele(ip->i_dquot);
			ip->i_dquot = NODQUOT;
#endif	QUOTA
			}
		}
		IUPDAT(ip, &time, &time, 0);
		IUNLOCK(ip);
		CLEAR_INODE_FLAGS(ip);
		/*
		 * Put the inode on the end of the free list.
		 * Possibly in some cases it would be better to
		 * put the inode at the head of the free list,
		 * (eg: where i_mode == 0 || i_number == 0)
		 * but I will think about that later .. kre
		 * (i_number is rarely 0 - only after an i/o error in iget,
		 * where i_mode == 0, the inode will probably be wanted
		 * again soon for an ialloc, so possibly we should keep it)
		 */
		if (ifreeh) {
			*ifreet = ip;
			ip->i_freeb = ifreet;
		} else {
			ifreeh = ip;
			ip->i_freeb = &ifreeh;
		}
		ip->i_freef = NULL;
		ifreet = &ip->i_freef;
	}
	DECR_INODE(ip);
}

#if	VICE
/*
 * Really horrible fudge to allow us to drop an inode we got with iget but
 * which isn't really allocated.
 */
iforget(ip)
struct inode *ip;
{
	ip->i_count = 0;
	CLEAR_INODE_FLAGS(ip);
	if (ifreeh) {
		*ifreet = ip;
		ip->i_freeb = ifreet;
	} else {
		ifreeh = ip;
		ip->i_freeb = &ifreeh;
	}
	ip->i_freef = NULL;
	ifreet = &ip->i_freef;
}
#endif	VICE

int iupdnot = 0;	/* TEMP: suppress time updates if true */

/*
 * Check accessed and update flags on
 * an inode structure.
 * If any is on, update the inode
 * with the current time.
 * If waitfor is given, then must insure
 * i/o order so wait for write to complete.
 */
iupdat(ip, ta, tm, waitfor)
	register struct inode *ip;
	struct timeval *ta, *tm;
	int waitfor;
{
	register struct buf *bp;
	struct dinode *dp;
	register struct fs *fp;

	fp = ip->i_fs;
	if (INODE_CHANGED(ip)) {
		if (fp->fs_ronly)
			return;
		bp = bread(INODE_DEV(ip), fsbtodb(fp, itod(fp, ip->i_number)),
			(int)fp->fs_bsize);
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			return;
		}
		if (iupdnot)
			ip->i_flag &= ~(ICHG);
		CHANGE_INODE(ip, ta, tm);
		UNCHANGE_INODE(ip);
		dp = bp->b_un.b_dino + itoo(fp, ip->i_number);
		dp->di_ic = ip->i_ic;
		if (waitfor)
			bwrite(bp);
		else
			bdwrite(bp);
	}
}

#define SINGLE	0	/* index of single indirect block */
#define DOUBLE	1	/* index of double indirect block */
#define TRIPLE	2	/* index of triple indirect block */
/*
 * Truncate the inode ip to at most
 * length size.  Free affected disk
 * blocks -- the blocks of the file
 * are removed in reverse order.
 *
 * NB: triple indirect blocks are untested.
 */
itrunc(oip, length)
	register struct inode *oip;
	u_long length;
{
	register daddr_t lastblock;
	daddr_t bn, lbn, lastiblock[NIADDR];
	register struct fs *fs;
	register struct inode *ip;
	struct buf *bp;
	u_long osize, size;
	int offset, level;
	long nblocks, blocksreleased = 0;
	register int i;
	struct inode tip;
	extern long indirtrunc();

#ifdef	multimax
	/*
	 *	Fast symbolic links have no storage.  Can truncate in place.
	 */
	if (((oip->i_mode & IFMT) == IFLNK) &&
	    ((oip->i_icflags & IC_FASTLINK) != 0) &&
	    (oip->i_size > length)) {
		bzero(&(oip->i_symlink[length]), oip->i_size - length);
		oip->i_size = length;
	}
#endif	multimax
#if	MACH_NBC
	iunlock(oip);	/* ARGH!!! */
	mfs_trunc(oip, length);
	ilock(oip);
#endif	MACH_NBC
	if (oip->i_size <= length) {
		CHGUPD_INODE(oip);
		UPDATE_INODE(oip, 0);
		return;
	}
	/*
	 * Calculate index into inode's block list of
	 * last direct and indirect blocks (if any)
	 * which we want to keep.  Lastblock is -1 when
	 * the file is truncated to 0.
	 */
	fs = oip->i_fs;
	lastblock = lblkno(fs, length + fs->fs_bsize - 1) - 1;
	lastiblock[SINGLE] = lastblock - NDADDR;
	lastiblock[DOUBLE] = lastiblock[SINGLE] - NINDIR(fs);
	lastiblock[TRIPLE] = lastiblock[DOUBLE] - NINDIR(fs) * NINDIR(fs);
	nblocks = btodb(fs->fs_bsize);
	/*
	 * Update the size of the file. If the file is not being
	 * truncated to a block boundry, the contents of the
	 * partial block following the end of the file must be
	 * zero'ed in case it ever become accessable again because
	 * of subsequent file growth.
	 */
	osize = oip->i_size;
	offset = blkoff(fs, length);
	if (offset == 0) {
		oip->i_size = length;
	} else {
		lbn = lblkno(fs, length);
		bn = fsbtodb(fs, BMAP(oip, lbn, B_WRITE, offset));
		if (u.u_error || (long)bn < 0)
			return;
		oip->i_size = length;
		size = blksize(fs, oip, lbn);
		if (oip->i_vm_info->pager != MEMORY_OBJECT_NULL)
			inode_uncache(oip);
#if	MACH_NBC
		/* data flushed in mfs_trunc above */
#else	MACH_NBC
		bp = bread(INODE_DEV(oip), bn, size);
		if (bp->b_flags & B_ERROR) {
			u.u_error = EIO;
			oip->i_size = osize;
			brelse(bp);
			return;
		}
		bzero(bp->b_un.b_addr + offset, (unsigned)(size - offset));
		bdwrite(bp);
#endif	MACH_NBC
	}
	/*
	 * Update file and block pointers
	 * on disk before we start freeing blocks.
	 * If we crash before free'ing blocks below,
	 * the blocks will be returned to the free list.
	 * lastiblock values are also normalized to -1
	 * for calls to indirtrunc below.
	 */
	tip = *oip;
	tip.i_size = osize;
	for (level = TRIPLE; level >= SINGLE; level--)
		if (lastiblock[level] < 0) {
			oip->i_ib[level] = 0;
			lastiblock[level] = -1;
		}
	for (i = NDADDR - 1; i > lastblock; i--)
		oip->i_db[i] = 0;
	oip->i_size = length;
	CHGUPD_INODE(oip);
	syncip(oip);

	/*
	 * Indirect blocks first.
	 */
	ip = &tip;
	for (level = TRIPLE; level >= SINGLE; level--) {
		bn = ip->i_ib[level];
		if (bn != 0) {
			blocksreleased +=
			    indirtrunc(ip, bn, lastiblock[level], level);
			if (lastiblock[level] < 0) {
				ip->i_ib[level] = 0;
				free(ip, bn, (off_t)fs->fs_bsize);
				blocksreleased += nblocks;
			}
		}
		if (lastiblock[level] >= 0)
			goto done;
	}

	/*
	 * All whole direct blocks or frags.
	 */
	for (i = NDADDR - 1; i > lastblock; i--) {
		register off_t bsize;

		bn = ip->i_db[i];
		if (bn == 0)
			continue;
		ip->i_db[i] = 0;
		bsize = (off_t)blksize(fs, ip, i);
		free(ip, bn, bsize);
		blocksreleased += btodb(bsize);
	}
	if (lastblock < 0)
		goto done;

	/*
	 * Finally, look for a change in size of the
	 * last direct block; release any frags.
	 */
	bn = ip->i_db[lastblock];
	if (bn != 0) {
		off_t oldspace, newspace;

		/*
		 * Calculate amount of space we're giving
		 * back as old block size minus new block size.
		 */
		oldspace = blksize(fs, ip, lastblock);
		ip->i_size = length;
		newspace = blksize(fs, ip, lastblock);
		if (newspace == 0)
			panic("itrunc: newspace");
		if (oldspace - newspace > 0) {
			/*
			 * Block number of space to be free'd is
			 * the old block # plus the number of frags
			 * required for the storage we're keeping.
			 */
			bn += numfrags(fs, newspace);
			free(ip, bn, oldspace - newspace);
			blocksreleased += btodb(oldspace - newspace);
		}
	}
done:
/* BEGIN PARANOIA */
	for (level = SINGLE; level <= TRIPLE; level++)
		if (ip->i_ib[level] != oip->i_ib[level])
			panic("itrunc1");
	for (i = 0; i < NDADDR; i++)
		if (ip->i_db[i] != oip->i_db[i])
			panic("itrunc2");
/* END PARANOIA */
	oip->i_blocks -= blocksreleased;
	if (oip->i_blocks < 0)			/* sanity */
		oip->i_blocks = 0;
	CHG_INODE(oip);
#if	QUOTA
	(void) chkdq(oip, -blocksreleased, 0);
#endif	QUOTA
}

/*
 * Release blocks associated with the inode ip and
 * stored in the indirect block bn.  Blocks are free'd
 * in LIFO order up to (but not including) lastbn.  If
 * level is greater than SINGLE, the block is an indirect
 * block and recursive calls to indirtrunc must be used to
 * cleanse other indirect blocks.
 *
 * NB: triple indirect blocks are untested.
 */
long
indirtrunc(ip, bn, lastbn, level)
	register struct inode *ip;
	daddr_t bn, lastbn;
	int level;
{
	register int i;
	struct buf *bp, *copy;
	register daddr_t *bap;
	register struct fs *fs = ip->i_fs;
	daddr_t nb, last;
	long factor;
	int blocksreleased = 0, nblocks;

	/*
	 * Calculate index in current block of last
	 * block to be kept.  -1 indicates the entire
	 * block so we need not calculate the index.
	 */
	factor = 1;
	for (i = SINGLE; i < level; i++)
		factor *= NINDIR(fs);
	last = lastbn;
	if (lastbn > 0)
		last /= factor;
	nblocks = btodb(fs->fs_bsize);
	/*
	 * Get buffer of block pointers, zero those 
	 * entries corresponding to blocks to be free'd,
	 * and update on disk copy first.
	 */
	copy = geteblk((int)fs->fs_bsize);
	bp = bread(INODE_DEV(ip), fsbtodb(fs, bn), (int)fs->fs_bsize);
	if (bp->b_flags&B_ERROR) {
		brelse(copy);
		brelse(bp);
		return (0);
	}
	bap = bp->b_un.b_daddr;
	bcopy((caddr_t)bap, (caddr_t)copy->b_un.b_daddr, (u_int)fs->fs_bsize);
	bzero((caddr_t)&bap[last + 1],
	  (u_int)(NINDIR(fs) - (last + 1)) * sizeof (daddr_t));
	bwrite(bp);
#if	MACH_NBC
	/* indirect blocks don't need flushing */
#endif	MACH_NBC
	bp = copy, bap = bp->b_un.b_daddr;

	/*
	 * Recursively free totally unused blocks.
	 */
	for (i = NINDIR(fs) - 1; i > last; i--) {
		nb = bap[i];
		if (nb == 0)
			continue;
		if (level > SINGLE)
			blocksreleased +=
			    indirtrunc(ip, nb, (daddr_t)-1, level - 1);
		free(ip, nb, (off_t)fs->fs_bsize);
		blocksreleased += nblocks;
	}

	/*
	 * Recursively free last partial block.
	 */
	if (level > SINGLE && lastbn >= 0) {
		last = lastbn % factor;
		nb = bap[i];
		if (nb != 0)
			blocksreleased += indirtrunc(ip, nb, last, level - 1);
	}
	brelse(bp);
	return (blocksreleased);
}

/*
 * remove any inodes in the inode cache belonging to dev
 *
 * There should not be any active ones, return error if any are found
 * (nb: this is a user error, not a system err)
 *
 * Also, count the references to dev by block devices - this really
 * has nothing to do with the object of the procedure, but as we have
 * to scan the inode table here anyway, we might as well get the
 * extra benefit.
 *
 * this is called from sumount()/sys3.c when dev is being unmounted
 */
#if	QUOTA
iflush(dev, iq)
	dev_t dev;
	struct inode *iq;
#else	QUOTA
iflush(dev)
	dev_t dev;
#endif	QUOTA
{
	register struct inode *ip;
	register open = 0;

	for (ip = inode; ip < inodeNINODE; ip++) {
#if	QUOTA
		if (ip != iq && ip->i_dev == dev)
#else	QUOTA
		if (ip->i_dev == dev)
#endif	QUOTA
			if (INODE_REFERENCED(ip) &&
#if	MACH_XP
			    inode_uncache_try(ip) &&
			    INODE_REFERENCED(ip))
#else	MACH_XP
			    1)
#endif	MACH_XP
				return(-1);
			else {
				remque(ip);
				ip->i_forw = ITOIH(ip);
				ip->i_back = ITOIH(ip);
				/*
				 * as i_count == 0, the inode was on the free
				 * list already, just leave it there, it will
				 * fall off the bottom eventually. We could
				 * perhaps move it to the head of the free
				 * list, but as umounts are done so
				 * infrequently, we would gain very little,
				 * while making the code bigger.
				 */
#if	QUOTA
				dqrele(ip->i_dquot);
				ip->i_dquot = NODQUOT;
#endif	QUOTA
			}
		else if (INODE_REFERENCED(ip) && (ip->i_mode&IFMT)==IFBLK &&
		    ip->i_rdev == dev)
			open++;
	}
	return (open);
}

/*
 * Lock an inode. If its already locked, set the WANT bit and sleep.
 */
ilock(ip)
	register struct inode *ip;
{

	ILOCK(ip);
}

/*
 * Unlock an inode.  If WANT bit is on, wakeup.
 */
iunlock(ip)
	register struct inode *ip;
{

	IUNLOCK(ip);
}

/*
 * Mark the accessed, updated, or changed times in an inode
 * with the current (unique) time
 * XXX inode timeval doesn't include tv_usec, so may not be unique here
 */
imark(ip, flag)
	register struct inode *ip;
	register int flag;
{
	struct timeval ut;
  
#if	NeXT
	microtime(&ut);	/* Fixme MACH_VFS */
#else	NeXT
	microtime(&ut);
/*	uniqtime(&ut);*/
#endif	NeXT
	ip->i_flag |= flag;
	if (flag & IACC)
		ip->i_atime = ut.tv_sec;
	if (flag & IUPD)
		ip->i_mtime = ut.tv_sec;
	if (flag & ICHG) {
		ip->i_diroff = 0;
		ip->i_ctime = ut.tv_sec;
	}
}

/*
 * Drop inode without going through the normal chain of unlocking
 * and releasing.
 */
idrop(ip)
	register struct inode *ip;
{

	if ((ip->i_flag & ILOCKED) == 0)
		panic("idrop");
	IUNLOCK(ip);
	if (--ip->i_count == 0) {
		CLEAR_INODE_FLAGS(ip);
		/*
		 * Put the inode back on the end of the free list.
		 */
		if (ifreeh) {
			*ifreet = ip;
			ip->i_freeb = ifreet;
		} else {
			ifreeh = ip;
			ip->i_freeb = &ifreeh;
		}
		ip->i_freef = NULL;
		ifreet = &ip->i_freef;
	}
}

irelease(ip)
	register struct inode *ip;
{
	if (ip->i_flag & ILOCKED)
		panic("irele");
	RELEASE_INODE(ip);
}
