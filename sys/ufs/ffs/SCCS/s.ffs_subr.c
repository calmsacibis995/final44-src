h34956
s 00001/00001/00215
d D 8.5 95/03/21 10:50:18 mckusick 61 60
c avoid double definition of ufs_daddr_t
e
s 00012/00008/00204
d D 8.4 95/03/21 00:53:27 mckusick 60 59
c daddr_t => ufs_daddr_t
e
s 00001/00001/00211
d D 8.3 95/01/02 23:38:57 mckusick 59 58
c convert quad => int64_t (from mycroft)
e
s 00001/00001/00211
d D 8.2 93/09/21 07:17:53 bostic 58 57
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00210
d D 8.1 93/06/11 16:21:24 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00211
d D 7.27 92/10/07 16:37:01 margo 56 55
c Add extra argument to VOP_BMAP.
e
s 00007/00003/00205
d D 7.26 92/07/03 01:47:51 mckusick 55 54
c add parameter declarations; delete USES
e
s 00001/00001/00207
d D 7.25 92/06/23 17:28:37 mckusick 54 53
c move systm.h into KERNEL only defines
e
s 00001/00000/00207
d D 7.24 92/06/21 01:21:58 torek 53 52
c need <sys/systm.h> for panic type (for gcc 2 warnings)
e
s 00000/00048/00207
d D 7.23 92/06/20 16:12:56 bostic 52 51
c break out library functions
e
s 00002/00002/00253
d D 7.22 92/06/04 14:54:12 mckusick 51 50
c add support for luna68k from Omron
e
s 00002/00002/00253
d D 7.21 92/05/27 22:58:56 mckusick 50 49
c reorg includes to avoid troubles with utilities that use this file
e
s 00007/00015/00248
d D 7.20 92/05/15 13:53:06 heideman 49 48
c vnodeop argument macro expansion
e
s 00011/00005/00252
d D 7.19 92/05/14 17:26:32 heideman 48 44
c vnode interface conversion
e
s 00011/00005/00252
d R 7.19 92/05/14 17:01:27 heideman 47 44
c vnode interface conversion
e
s 00011/00005/00252
d R 7.19 92/05/14 16:43:13 heideman 46 44
c vnode interface conversion
e
s 00011/00005/00252
d R 7.19 92/05/14 16:33:09 heideman 45 44
c vnode interface conversion
e
s 00001/00001/00256
d D 7.18 92/05/14 16:26:58 heideman 44 34
c ffs_extern.h requires #include <sys/vnode.h>
e
s 00011/00005/00252
d R 7.18 92/05/14 15:51:25 heideman 43 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/14 15:39:17 heideman 42 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/14 14:45:20 heideman 41 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/14 12:48:12 heideman 40 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/14 11:45:19 heideman 39 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/14 10:26:05 heideman 38 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/13 23:04:07 heideman 37 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/13 18:51:51 heideman 36 34
c vnode interface conversion
e
s 00011/00005/00252
d R 7.18 92/05/13 18:23:52 heideman 35 34
c vnode interface conversion
e
s 00003/00005/00254
d D 7.17 91/12/15 14:35:59 mckusick 34 33
c reorder includes to keep kernel and fsck happy
e
s 00005/00002/00254
d D 7.16 91/11/11 12:02:07 bostic 33 32
c make ffs_subr.c work with fsck(8) again
e
s 00005/00003/00251
d D 7.15 91/11/05 14:29:57 mckusick 32 31
c reorganization to move ufsmount ops to be vnode ops
e
s 00087/00017/00167
d D 7.14 91/11/01 16:57:51 bostic 31 30
c UFS/FFS split for LFS version 1; add ffs_blkatoff, ffs_checkoverlap
e
s 00001/00011/00183
d D 7.13 90/06/28 22:31:00 bostic 30 29
c new copyright notice
e
s 00003/00002/00191
d D 7.12 90/05/10 15:23:20 mckusick 29 28
c merge in support for hp300 from Utah
e
s 00000/00154/00193
d D 7.11 89/12/30 22:44:31 mckusick 28 27
c syncip is replaced by vflushbuf; badblock moves to ufs_alloc.c;
c getfs and getfsx move to quota_subr.c; no #ifdef KERNEL code left in this file
e
s 00006/00003/00341
d D 7.10 89/11/22 21:51:56 mckusick 27 26
c use new waitfor flag in syncip
e
s 00000/00009/00344
d D 7.9 89/10/24 19:27:06 mckusick 26 25
c get rid of unnecessary include files for non-kernel users
e
s 00052/00118/00301
d D 7.8 89/05/09 17:22:27 mckusick 25 24
c merge in vnodes
e
s 00001/00001/00418
d D 7.7 89/05/01 14:17:21 bostic 24 23
c add VAX650 to the processors needs scanc
e
s 00004/00002/00415
d D 7.6 88/05/19 22:09:46 karels 23 22
c avoid race between mountfs and update
e
s 00004/00004/00413
d D 7.5 87/06/21 15:30:51 mckusick 22 21
c geteblk => malloc, so m_bufp => m_fs as it should be
e
s 00000/00000/00417
d D 7.4 87/04/02 15:49:32 karels 21 19
c working with pack labels
e
s 00012/00000/00417
d D 7.3.1.1 87/04/02 15:41:25 karels 20 19
c add ifdefs for dev_bsize (almost working)
e
s 00000/00001/00417
d D 7.3 87/03/10 14:20:53 mckusick 19 18
c only set ICHG when fsync'ing a file descriptor that is open for writing
e
s 00005/00005/00413
d D 7.2 86/11/03 12:00:42 karels 18 17
c merge in tahoe support
e
s 00001/00001/00417
d D 7.1 86/06/05 00:14:23 mckusick 17 16
c 4.3BSD release version
e
s 00004/00001/00414
d D 6.11 86/04/28 09:25:12 kridle 16 15
c Added code to define scanc if VAX630 is defined.
e
s 00003/00003/00412
d D 6.10 86/02/21 11:35:50 karels 15 14
c make those switches int!
e
s 00004/00003/00411
d D 6.9 86/02/20 15:21:05 karels 14 13
c lint and cleanups from Sam
e
s 00007/00001/00407
d D 6.8 85/06/08 14:53:46 mckusick 13 12
c Add copyright
e
s 00041/00000/00367
d D 6.7 85/05/27 15:00:19 mckusick 12 11
c add C definitions of special vax hardware
e
s 00000/00002/00367
d D 6.6 85/03/19 20:49:46 mckusick 11 10
c eliminate extraneous include of conf.h
e
s 00011/00011/00358
d D 6.5 84/08/29 20:26:55 bloom 10 9
c Change to includes.  no more ../h
e
s 00038/00008/00331
d D 6.4 84/08/09 11:22:55 mckusick 9 8
c fix `fsync' to work efficiently with big files
e
s 00001/00001/00338
d D 6.3 84/07/10 15:17:13 mckusick 8 7
c parenthesis botch (from kre)
e
s 00002/00001/00337
d D 6.2 84/02/07 17:34:56 karels 7 6
c avoid iupdate/iput if unmodified (in update)
e
s 00000/00000/00338
d D 6.1 83/07/29 06:44:31 sam 6 5
c 4.2 distribution
e
s 00002/00000/00336
d D 4.5 83/03/21 19:52:36 sam 5 4
c don't forget the inode 
e
s 00001/00002/00335
d D 4.4 82/12/17 11:48:58 sam 4 3
c sun merge
e
s 00187/00000/00150
d D 4.3 82/11/13 22:53:31 sam 3 2
c merge of 4.1b and 4.1c
e
s 00001/00001/00149
d D 4.2 82/10/21 20:59:25 root 2 1
c lint
e
s 00150/00000/00000
d D 4.1 82/10/20 03:06:12 root 1 0
c date and time created 82/10/20 03:06:12 by root
e
u
U
f b 
t
T
I 1
D 13
/*	%M%	%I%	%E%	*/
E 13
I 13
/*
D 17
 * Copyright (c) 1982 Regents of the University of California.
E 17
I 17
D 25
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
D 57
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 57
I 57
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 57
E 25
 *
I 25
D 30
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
 *
E 25
 *	%W% (Berkeley) %G%
 */
E 13

D 31
#ifdef KERNEL
D 10
#include "../h/param.h"
I 3
#include "../h/systm.h"
#include "../h/mount.h"
E 3
#include "../h/fs.h"
I 3
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/inode.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/quota.h"
#include "../h/kernel.h"
E 10
I 10
#include "param.h"
D 28
#include "systm.h"
D 25
#include "mount.h"
#include "fs.h"
E 25
D 11
#include "conf.h"
E 11
#include "buf.h"
D 25
#include "inode.h"
#include "dir.h"
#include "user.h"
#include "quota.h"
E 25
I 25
#include "time.h"
E 25
#include "kernel.h"
I 25
#include "file.h"
#include "mount.h"
#include "vnode.h"
#include "../ufs/inode.h"
#include "../ufs/ufsmount.h"
E 28
#include "../ufs/fs.h"
D 28
#include "../ufs/quota.h"
E 28
E 25
E 10
E 3
#else
E 31
#include <sys/param.h>
I 60
#ifndef KERNEL
D 61
typedef u_int32_t ufs_daddr_t;
E 61
I 61
#include <ufs/ufs/dinode.h>
E 61
E 60
I 53
D 54
#include <sys/systm.h>
E 54
E 53
I 44
D 50
#include <sys/vnode.h>
E 50
E 44
I 3
D 26
#include <sys/systm.h>
D 25
#include <sys/mount.h>
E 3
#include <sys/fs.h>
E 25
I 3
D 11
#include <sys/conf.h>
E 11
#include <sys/buf.h>
D 25
#include <sys/inode.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/quota.h>
E 25
I 25
#include <sys/time.h>
#include <sys/file.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
#include <ufs/ufsmount.h>
E 26
D 31
#include <ufs/fs.h>
D 26
#include <ufs/quota.h>
E 26
E 25
D 4
#include <sys/kernel.h>
E 4
E 3
#endif
E 31
I 31
D 34
#include <sys/buf.h>
D 33
#include <sys/vnode.h>
E 33
E 31

I 3
D 28
#ifdef KERNEL
D 25
int	syncprt = 0;

E 25
/*
D 25
 * Update is the internal name of 'sync'.  It goes through the disk
 * queues to initiate sandbagged IO; goes through the inodes to write
 * modified nodes; and it goes through the mount table to initiate
 * the writing of the modified super blocks.
 */
update()
{
	register struct inode *ip;
	register struct mount *mp;
	struct fs *fs;

	if (syncprt)
		bufstats();
	if (updlock)
		return;
	updlock++;
	/*
	 * Write back modified superblocks.
	 * Consistency check that the superblock
	 * of each file system is still in the buffer cache.
	 */
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
D 4
		if (mp->m_bufp == NULL)
E 4
I 4
D 22
		if (mp->m_bufp == NULL || mp->m_dev == NODEV)
E 22
I 22
D 23
		if (mp->m_fs == NULL || mp->m_dev == NODEV)
E 23
I 23
		if (mp->m_fs == NULL || mp->m_fs == (struct fs *)1)   /* XXX */
E 23
E 22
E 4
			continue;
D 22
		fs = mp->m_bufp->b_un.b_fs;
E 22
I 22
		fs = mp->m_fs;
E 22
		if (fs->fs_fmod == 0)
			continue;
		if (fs->fs_ronly != 0) {		/* XXX */
			printf("fs = %s\n", fs->fs_fsmnt);
			panic("update: rofs mod");
		}
		fs->fs_fmod = 0;
		fs->fs_time = time.tv_sec;
		sbupdate(mp);
	}
	/*
	 * Write back each (modified) inode.
	 */
	for (ip = inode; ip < inodeNINODE; ip++) {
D 7
		if ((ip->i_flag & ILOCKED) != 0 || ip->i_count == 0)
E 7
I 7
		if ((ip->i_flag & ILOCKED) != 0 || ip->i_count == 0 ||
D 8
		    (ip->i_flag & (IACC|IUPD|ICHG) == 0))
E 8
I 8
		    (ip->i_flag & (IMOD|IACC|IUPD|ICHG)) == 0)
E 8
E 7
			continue;
		ip->i_flag |= ILOCKED;
		ip->i_count++;
		iupdat(ip, &time, &time, 0);
		iput(ip);
	}
	updlock = 0;
	/*
	 * Force stale buffer cache information to be flushed,
	 * for all devices.
	 */
	bflush(NODEV);
}

/*
E 25
 * Flush all the blocks associated with an inode.
D 9
 * Note that we make a more stringent check of
 * writing out any block in the buffer pool that may
 * overlap the inode. This brings the inode up to
 * date with recent mods to the cooked device.
E 9
I 9
 * There are two strategies based on the size of the file;
 * large files are those with more than (nbuf / 2) blocks.
 * Large files
 * 	Walk through the buffer pool and push any dirty pages
 *	associated with the device on which the file resides.
 * Small files
 *	Look up each block in the file to see if it is in the 
 *	buffer pool writing any that are found to disk.
 *	Note that we make a more stringent check of
 *	writing out any block in the buffer pool that may
 *	overlap the inode. This brings the inode up to
 *	date with recent mods to the cooked device.
E 9
 */
D 27
syncip(ip)
E 27
I 27
syncip(ip, waitfor)
E 27
	register struct inode *ip;
I 27
	int waitfor;
E 27
{
	register struct fs *fs;
D 9
	long lbn, lastlbn;
E 9
I 9
	register struct buf *bp;
	struct buf *lastbufp;
D 14
	long lbn, lastlbn, s;
E 14
I 14
	long lbn, lastlbn;
D 25
	int s;
E 25
I 25
	int s, error, allerror = 0;
E 25
E 14
E 9
	daddr_t blkno;

	fs = ip->i_fs;
	lastlbn = howmany(ip->i_size, fs->fs_bsize);
D 9
	for (lbn = 0; lbn < lastlbn; lbn++) {
		blkno = fsbtodb(fs, bmap(ip, lbn, B_READ));
		blkflush(ip->i_dev, blkno, blksize(fs, ip, lbn));
E 9
I 9
	if (lastlbn < nbuf / 2) {
I 20
#ifdef SECSIZE
		lastlbn--;
		s = fsbtodb(fs, fs->fs_frag);
E 20
		for (lbn = 0; lbn < lastlbn; lbn++) {
D 25
			blkno = fsbtodb(fs, bmap(ip, lbn, B_READ));
I 20
			blkflush(ip->i_dev, blkno, s);
		}
		if (lastlbn >= 0)
			blkflush(ip->i_dev, blkno, (int)fsbtodb(fs,
			    blksize(fs, ip, lbn) / fs->fs_fsize));
#else SECSIZE
		for (lbn = 0; lbn < lastlbn; lbn++) {
			blkno = fsbtodb(fs, bmap(ip, lbn, B_READ));
E 20
			blkflush(ip->i_dev, blkno, blksize(fs, ip, lbn));
E 25
I 25
			error = bmap(ip, lbn, &blkno, (daddr_t *)0, (int *)0);
			if (error)
				allerror = error;
			if (error = blkflush(ip->i_devvp, blkno,
			    blksize(fs, ip, lbn)))
				allerror = error;
E 25
		}
I 20
#endif SECSIZE
E 20
	} else {
		lastbufp = &buf[nbuf];
		for (bp = buf; bp < lastbufp; bp++) {
			if (bp->b_dev != ip->i_dev ||
			    (bp->b_flags & B_DELWRI) == 0)
				continue;
D 14
			s = spl6();
E 14
I 14
			s = splbio();
E 14
			if (bp->b_flags & B_BUSY) {
				bp->b_flags |= B_WANTED;
				sleep((caddr_t)bp, PRIBIO+1);
				splx(s);
				bp--;
				continue;
			}
			splx(s);
			notavail(bp);
D 25
			bwrite(bp);
E 25
I 25
D 27
			if (error = bwrite(bp))
E 27
I 27
			if (waitfor == MNT_NOWAIT)
				bawrite(bp);
			else if (error = bwrite(bp))
E 27
				allerror = error;
E 25
		}
E 9
	}
I 5
D 19
	ip->i_flag |= ICHG;
E 19
D 25
	iupdat(ip, &time, &time, 1);
E 25
I 25
D 27
	if (error = iupdat(ip, &time, &time, 1))
E 27
I 27
	if (error = iupdat(ip, &time, &time, waitfor == MNT_WAIT))
E 27
		allerror = error;
	return (allerror);
E 25
E 5
}
D 25
#endif
E 25
I 25
#endif KERNEL
E 25

E 28
E 3
D 31
extern	int around[9];
extern	int inside[9];
extern	u_char *fragtbl[];
E 31
I 31
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 31

E 34
I 31
#include <ufs/ffs/fs.h>
I 60
#else
E 60
D 50
#include <ufs/ffs/ffs_extern.h>
E 50

I 33
D 60
#ifdef KERNEL
E 60
I 54
#include <sys/systm.h>
E 54
I 50
#include <sys/vnode.h>
D 60
#include <ufs/ffs/ffs_extern.h>
E 60
E 50
I 34
#include <sys/buf.h>
E 34
D 44
#include <sys/vnode.h>
E 44
I 34
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
I 60
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>
E 60
E 34

E 33
E 31
/*
I 31
 * Return buffer with the contents of block "offset" from the beginning of
 * directory "ip".  If "res" is non-zero, fill it in with a pointer to the
 * remaining space in the directory.
 */
int
D 32
ffs_blkatoff(ip, offset, res, bpp)
	struct inode *ip;
E 32
I 32
D 48
ffs_blkatoff(vp, offset, res, bpp)
	struct vnode *vp;
E 32
	off_t offset;
	char **res;
	struct buf **bpp;
E 48
I 48
D 55
ffs_blkatoff (ap)
	struct vop_blkatoff_args *ap;
E 55
I 55
ffs_blkatoff(ap)
	struct vop_blkatoff_args /* {
		struct vnode *a_vp;
		off_t a_offset;
		char **a_res;
		struct buf **a_bpp;
	} */ *ap;
E 55
D 49
#define vp (ap->a_vp)
#define offset (ap->a_offset)
#define res (ap->a_res)
#define bpp (ap->a_bpp)
E 49
E 48
{
I 32
	struct inode *ip;
E 32
	register struct fs *fs;
	struct buf *bp;
D 60
	daddr_t lbn;
E 60
I 60
	ufs_daddr_t lbn;
E 60
	int bsize, error;

I 32
D 49
	ip = VTOI(vp);
E 49
I 49
	ip = VTOI(ap->a_vp);
E 49
E 32
	fs = ip->i_fs;
D 49
	lbn = lblkno(fs, offset);
E 49
I 49
	lbn = lblkno(fs, ap->a_offset);
E 49
	bsize = blksize(fs, ip, lbn);

D 49
	*bpp = NULL;
D 32
	if (error = bread(ITOV(ip), lbn, bsize, NOCRED, &bp)) {
E 32
I 32
	if (error = bread(vp, lbn, bsize, NOCRED, &bp)) {
E 49
I 49
	*ap->a_bpp = NULL;
	if (error = bread(ap->a_vp, lbn, bsize, NOCRED, &bp)) {
E 49
E 32
		brelse(bp);
		return (error);
	}
D 49
	if (res)
		*res = bp->b_un.b_addr + blkoff(fs, offset);
	*bpp = bp;
E 49
I 49
	if (ap->a_res)
D 58
		*ap->a_res = bp->b_un.b_addr + blkoff(fs, ap->a_offset);
E 58
I 58
		*ap->a_res = (char *)bp->b_data + blkoff(fs, ap->a_offset);
E 58
	*ap->a_bpp = bp;
E 49
	return (0);
}
I 48
D 49
#undef vp
#undef offset
#undef res
#undef bpp
E 49
E 48
I 33
#endif
E 33

/*
E 31
 * Update the frsum fields to reflect addition or deletion 
 * of some frags.
 */
D 31
fragacct(fs, fragmap, fraglist, cnt)
E 31
I 31
void
ffs_fragacct(fs, fragmap, fraglist, cnt)
E 31
	struct fs *fs;
	int fragmap;
D 59
	long fraglist[];
E 59
I 59
	int32_t fraglist[];
E 59
	int cnt;
{
	int inblk;
	register int field, subfield;
	register int siz, pos;

	inblk = (int)(fragtbl[fs->fs_frag][fragmap]) << 1;
	fragmap <<= 1;
	for (siz = 1; siz < fs->fs_frag; siz++) {
		if ((inblk & (1 << (siz + (fs->fs_frag % NBBY)))) == 0)
			continue;
		field = around[siz];
		subfield = inside[siz];
		for (pos = siz; pos <= fs->fs_frag; pos++) {
			if ((fragmap & field) == subfield) {
				fraglist[siz] += cnt;
				pos += siz;
				field <<= siz;
				subfield <<= siz;
			}
			field <<= 1;
			subfield <<= 1;
		}
	}
}

I 31
D 33
#ifdef DIAGNOSTIC
E 33
I 33
#if defined(KERNEL) && defined(DIAGNOSTIC)
E 33
void
ffs_checkoverlap(bp, ip)
	struct buf *bp;
	struct inode *ip;
{
I 48
D 55
	USES_VOP_BMAP;
E 55
E 48
	register struct buf *ebp, *ep;
D 60
	register daddr_t start, last;
E 60
I 60
	register ufs_daddr_t start, last;
E 60
	struct vnode *vp;

	ebp = &buf[nbuf];
	start = bp->b_blkno;
	last = start + btodb(bp->b_bcount) - 1;
	for (ep = buf; ep < ebp; ep++) {
		if (ep == bp || (ep->b_flags & B_INVAL) ||
		    ep->b_vp == NULLVP)
			continue;
D 56
		if (VOP_BMAP(ep->b_vp, (daddr_t)0, &vp, (daddr_t)0))
E 56
I 56
D 60
		if (VOP_BMAP(ep->b_vp, (daddr_t)0, &vp, (daddr_t)0, NULL))
E 60
I 60
		if (VOP_BMAP(ep->b_vp, (ufs_daddr_t)0, &vp, (ufs_daddr_t)0,
		    NULL))
E 60
E 56
			continue;
		if (vp != ip->i_devvp)
			continue;
		/* look for overlap */
		if (ep->b_bcount == 0 || ep->b_blkno > last ||
		    ep->b_blkno + btodb(ep->b_bcount) <= start)
			continue;
		vprint("Disk overlap", vp);
		(void)printf("\tstart %d, end %d overlap start %d, end %d\n",
			start, last, ep->b_blkno,
			ep->b_blkno + btodb(ep->b_bcount) - 1);
		panic("Disk buffer overlap");
	}
}
#endif /* DIAGNOSTIC */

E 31
D 28
#ifdef KERNEL
E 28
/*
D 28
 * Check that a specified block number is in range.
 */
badblock(fs, bn)
	register struct fs *fs;
	daddr_t bn;
{

	if ((unsigned)bn >= fs->fs_size) {
		printf("bad block %d, ", bn);
		fserr(fs, "bad block");
		return (1);
	}
	return (0);
}
#endif

/*
E 28
 * block operations
 *
 * check if a block is available
 */
D 31
isblock(fs, cp, h)
E 31
I 31
int
ffs_isblock(fs, cp, h)
E 31
	struct fs *fs;
	unsigned char *cp;
D 60
	daddr_t h;
E 60
I 60
	ufs_daddr_t h;
E 60
{
	unsigned char mask;

D 15
	switch (fs->fs_frag) {
E 15
I 15
	switch ((int)fs->fs_frag) {
E 15
	case 8:
		return (cp[h] == 0xff);
	case 4:
		mask = 0x0f << ((h & 0x1) << 2);
		return ((cp[h >> 1] & mask) == mask);
	case 2:
		mask = 0x03 << ((h & 0x3) << 1);
		return ((cp[h >> 2] & mask) == mask);
	case 1:
		mask = 0x01 << (h & 0x7);
		return ((cp[h >> 3] & mask) == mask);
	default:
D 31
		panic("isblock");
		return (NULL);
E 31
I 31
		panic("ffs_isblock");
E 31
	}
}

/*
 * take a block out of the map
 */
D 31
clrblock(fs, cp, h)
E 31
I 31
void
ffs_clrblock(fs, cp, h)
E 31
	struct fs *fs;
D 2
	unsigned char *cp;
E 2
I 2
	u_char *cp;
E 2
D 60
	daddr_t h;
E 60
I 60
	ufs_daddr_t h;
E 60
{

D 15
	switch ((fs)->fs_frag) {
E 15
I 15
	switch ((int)fs->fs_frag) {
E 15
	case 8:
		cp[h] = 0;
		return;
	case 4:
		cp[h >> 1] &= ~(0x0f << ((h & 0x1) << 2));
		return;
	case 2:
		cp[h >> 2] &= ~(0x03 << ((h & 0x3) << 1));
		return;
	case 1:
		cp[h >> 3] &= ~(0x01 << (h & 0x7));
		return;
	default:
D 31
		panic("clrblock");
E 31
I 31
		panic("ffs_clrblock");
E 31
	}
}

/*
 * put a block into the map
 */
D 31
setblock(fs, cp, h)
E 31
I 31
void
ffs_setblock(fs, cp, h)
E 31
	struct fs *fs;
	unsigned char *cp;
D 60
	daddr_t h;
E 60
I 60
	ufs_daddr_t h;
E 60
{

D 15
	switch (fs->fs_frag) {
E 15
I 15
	switch ((int)fs->fs_frag) {
E 15

	case 8:
		cp[h] = 0xff;
		return;
	case 4:
		cp[h >> 1] |= (0x0f << ((h & 0x1) << 2));
		return;
	case 2:
		cp[h >> 2] |= (0x03 << ((h & 0x3) << 1));
		return;
	case 1:
		cp[h >> 3] |= (0x01 << (h & 0x7));
		return;
	default:
D 31
		panic("setblock");
E 31
I 31
		panic("ffs_setblock");
E 31
	}
}
I 3
D 28

#ifdef KERNEL
/*
 * Getfs maps a device number into a pointer to the incore super block.
 *
 * The algorithm is a linear search through the mount table. A
 * consistency check of the super block magic number is performed.
I 23
 * Filesystems still working on a mount are skipped.
E 23
 *
 * panic: no fs -- the device is not mounted.
 *	this "cannot happen"
 */
struct fs *
getfs(dev)
	dev_t dev;
{
D 25
	register struct mount *mp;
E 25
I 25
	register struct ufsmount *mp;
E 25
	register struct fs *fs;

D 25
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
D 22
		if (mp->m_bufp == NULL || mp->m_dev != dev)
E 22
I 22
D 23
		if (mp->m_fs == NULL || mp->m_dev != dev)
E 23
I 23
		if (mp->m_dev != dev || mp->m_fs == NULL ||
		    mp->m_fs == (struct fs *)1)			/* XXX */
E 25
I 25
	for (mp = &mounttab[0]; mp < &mounttab[NMOUNT]; mp++) {
		if (mp->um_fs == NULL || mp->um_dev != dev ||
		    mp->um_fs == (struct fs *)1)		/* XXX */
E 25
E 23
E 22
			continue;
D 22
		fs = mp->m_bufp->b_un.b_fs;
E 22
I 22
D 25
		fs = mp->m_fs;
E 25
I 25
		fs = mp->um_fs;
E 25
E 22
		if (fs->fs_magic != FS_MAGIC) {
			printf("dev = 0x%x, fs = %s\n", dev, fs->fs_fsmnt);
			panic("getfs: bad magic");
		}
		return (fs);
	}
	printf("dev = 0x%x\n", dev);
	panic("getfs: no fs");
	return (NULL);
}

/*
 * Getfsx returns the index in the file system
 * table of the specified device.  The swap device
 * is also assigned a pseudo-index.  The index may
 * be used as a compressed indication of the location
 * of a block, recording
 *	<getfsx(dev),blkno>
 * rather than
 *	<dev, blkno>
 * provided the information need remain valid only
 * as long as the file system is mounted.
 */
getfsx(dev)
	dev_t dev;
{
D 25
	register struct mount *mp;
E 25
I 25
	register struct ufsmount *mp;
E 25

	if (dev == swapdev)
		return (MSWAPX);
D 25
	for(mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_dev == dev)
			return (mp - &mount[0]);
E 25
I 25
	for(mp = &mounttab[0]; mp < &mounttab[NMOUNT]; mp++)
		if (mp->um_dev == dev)
			return (mp - &mounttab[0]);
E 25
	return (-1);
D 25
}

/*
 * Print out statistics on the current allocation of the buffer pool.
 * Can be enabled to print out on every ``sync'' by setting "syncprt"
 * above.
 */
bufstats()
{
	int s, i, j, count;
	register struct buf *bp, *dp;
	int counts[MAXBSIZE/CLBYTES+1];
	static char *bname[BQUEUES] = { "LOCKED", "LRU", "AGE", "EMPTY" };

	for (bp = bfreelist, i = 0; bp < &bfreelist[BQUEUES]; bp++, i++) {
		count = 0;
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			counts[j] = 0;
D 14
		s = spl6();
E 14
I 14
		s = splbio();
E 14
		for (dp = bp->av_forw; dp != bp; dp = dp->av_forw) {
			counts[dp->b_bufsize/CLBYTES]++;
			count++;
		}
		splx(s);
		printf("%s: total-%d", bname[i], count);
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			if (counts[j] != 0)
				printf(", %d-%d", j * CLBYTES, counts[j]);
		printf("\n");
	}
E 25
}
#endif
E 28
I 12
D 52

D 16
#if !defined(vax)
E 16
I 16
D 18
#if !defined(vax) || defined(VAX630)
E 18
I 18
D 24
#if (!defined(vax) && !defined(tahoe)) || defined(VAX630)
E 24
I 24
D 29
#if (!defined(vax) && !defined(tahoe)) || defined(VAX630) || defined(VAX650)
E 29
I 29
D 51
#if (!defined(vax) && !defined(tahoe) && !defined(hp300)) \
E 51
I 51
#if (!defined(vax) && !defined(tahoe) && !defined(hp300) && !defined(luna68k)) \
E 51
	|| defined(VAX630) || defined(VAX650)
E 29
E 24
E 18
E 16
/*
D 18
 * C definitions of special vax instructions.
E 18
I 18
 * C definitions of special instructions.
 * Normally expanded with inline.
E 18
 */
I 31
int
E 31
scanc(size, cp, table, mask)
	u_int size;
	register u_char *cp, table[];
	register u_char mask;
{
	register u_char *end = &cp[size];

	while (cp < end && (table[*cp] & mask) == 0)
		cp++;
	return (end - cp);
}
I 16
D 18

E 18
#endif
D 18
#if !defined(vax)
E 18
E 16

I 18
D 29
#if !defined(vax) && !defined(tahoe)
E 29
I 29
D 51
#if !defined(vax) && !defined(tahoe) && !defined(hp300)
E 51
I 51
#if !defined(vax) && !defined(tahoe) && !defined(hp300) && !defined(luna68k)
E 51
I 31
int
E 31
E 29
E 18
skpc(mask, size, cp)
	register u_char mask;
	u_int size;
	register u_char *cp;
{
	register u_char *end = &cp[size];

	while (cp < end && *cp == mask)
		cp++;
	return (end - cp);
}

I 31
int
E 31
locc(mask, size, cp)
	register u_char mask;
	u_int size;
	register u_char *cp;
{
	register u_char *end = &cp[size];

	while (cp < end && *cp != mask)
		cp++;
	return (end - cp);
}
D 18
#endif vax
E 18
I 18
#endif
E 52
E 18
E 12
E 3
E 1
