h42702
s 00012/00019/00269
d D 8.8 95/06/16 11:28:04 mckusick 56 55
c tuneups on previous fix (from torek)
e
s 00040/00007/00248
d D 8.7 95/05/17 00:00:30 mckusick 55 54
c If we have failed part way through block allocation, we
c have to deallocate any indirect blocks that we have allocated
e
s 00006/00006/00249
d D 8.6 95/03/21 00:53:33 mckusick 54 53
c daddr_t => ufs_daddr_t
e
s 00019/00020/00236
d D 8.5 95/01/07 18:21:55 mckusick 53 52
c merge bn and lbn to make them consistent
e
s 00003/00003/00253
d D 8.4 93/09/23 16:13:33 bostic 52 51
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00252
d D 8.3 93/09/21 07:20:27 bostic 51 50
c changes for 4.4BSD-Lite requested by USL
e
s 00014/00014/00242
d D 8.2 93/09/05 09:41:50 bostic 50 49
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00254
d D 8.1 93/06/11 16:21:11 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00251
d D 7.25 93/02/02 21:05:15 mckusick 48 47
c getblk takes parameter to indicate interrupt
e
s 00001/00001/00255
d D 7.24 92/10/08 22:44:45 margo 47 46
c Place indirect block pointer at correct offset.
e
s 00028/00130/00228
d D 7.23 92/10/07 16:42:13 margo 46 45
c Remove ffs_bmap.  Modify ffs_balloc to use ufs_bmap.
e
s 00014/00008/00344
d D 7.22 92/07/03 01:47:22 mckusick 45 44
c add parameter declarations; streamline unmarshalling
e
s 00008/00007/00344
d D 7.21 92/06/04 09:50:05 heideman 44 43
c registerized vnodeop ops after vnode interface conversion
e
s 00016/00024/00335
d D 7.20 92/05/15 13:52:41 heideman 43 42
c vnodeop argument macro expansion
e
s 00010/00005/00349
d D 7.19 92/05/14 17:26:13 heideman 42 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 17:00:48 heideman 41 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 16:42:48 heideman 40 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 16:32:42 heideman 39 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 15:50:51 heideman 38 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 15:38:46 heideman 37 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 14:44:54 heideman 36 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 12:47:45 heideman 35 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 11:44:50 heideman 34 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/14 10:25:39 heideman 33 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/13 23:03:38 heideman 32 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/13 18:51:30 heideman 31 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/13 18:23:26 heideman 30 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/13 18:12:45 heideman 29 27
c vnode interface conversion
e
s 00010/00005/00349
d R 7.19 92/05/13 17:57:19 heideman 28 27
c vnode interface conversion
e
s 00002/00000/00352
d D 7.18 92/05/04 16:17:11 mckusick 27 26
c lint
e
s 00009/00007/00343
d D 7.17 92/04/21 14:44:04 mckusick 26 25
c have to pass down cred to block allocation routines
e
s 00001/00001/00349
d D 7.16 92/03/22 20:38:06 ralph 25 24
c remove ITOV and use vnode pointer instead.
e
s 00015/00003/00335
d D 7.15 91/11/05 14:29:38 mckusick 24 23
c reorganization to move ufsmount ops to be vnode ops
e
s 00032/00028/00306
d D 7.14 91/11/01 16:56:57 bostic 23 22
c UFS/FFS split for LFS version 1
e
s 00004/00003/00330
d D 7.13 91/05/08 19:29:32 mckusick 22 21
c make comments more precise
e
s 00004/00004/00329
d D 7.12 91/03/19 10:30:23 karels 21 20
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00001/00000/00332
d D 7.11 90/12/05 16:08:59 mckusick 20 19
c update for new VM
e
s 00001/00011/00331
d D 7.10 90/06/28 22:30:21 bostic 19 18
c new copyright notice
e
s 00004/00004/00338
d D 7.9 90/05/03 12:25:39 mckusick 18 17
c minor reorganization to support MP systems (from noemi@osf.org)
e
s 00001/00000/00341
d D 7.8 90/05/02 19:34:12 mckusick 17 16
c need quota.h with inode.h now
e
s 00024/00012/00317
d D 7.7 90/01/04 22:16:52 mckusick 16 15
c ensure that dirty indirect blocks are associated with their file vnode
e
s 00144/00138/00185
d D 7.6 89/11/30 23:06:44 mckusick 15 14
c major overhaul to handle logical buffer pool
e
s 00002/00002/00321
d D 7.5 89/08/26 14:12:49 mckusick 14 13
c generalize the buffer pool so that NFS can become a client
e
s 00002/00000/00321
d D 7.4 89/07/16 13:35:18 mckusick 13 12
c have to release those buffers when reading indirect blocks
e
s 00185/00077/00136
d D 7.3 89/05/09 17:22:07 mckusick 12 11
c merge in vnodes
e
s 00000/00000/00213
d D 7.2 87/04/02 15:49:18 karels 11 9
c working with pack labels
e
s 00005/00000/00213
d D 7.1.1.1 87/04/02 15:41:12 karels 10 9
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/00212
d D 7.1 86/06/05 00:12:18 mckusick 9 8
c 4.3BSD release version
e
s 00007/00001/00206
d D 6.4 85/06/08 14:50:46 mckusick 8 7
c Add copyright
e
s 00000/00001/00207
d D 6.3 85/03/19 20:48:38 mckusick 7 6
c eliminate extraneous include of conf.h
e
s 00009/00009/00199
d D 6.2 84/08/29 20:25:45 bloom 6 5
c Change to includes.  no more ../h
e
s 00000/00000/00208
d D 6.1 83/07/29 06:41:43 sam 5 4
c 4.2 distribution
e
s 00002/00000/00206
d D 5.4 83/03/15 09:48:22 sam 4 3
c watch return val from realloccg (from kre)
e
s 00010/00009/00196
d D 5.3 82/11/13 22:52:45 sam 3 2
c merge of 4.1b and 4.1c
e
s 00025/00021/00180
d D 5.2 82/09/25 22:49:31 mckusick 2 1
c rearrange blkpref to centralize and make smarter about block layout
e
s 00201/00000/00000
d D 5.1 82/07/15 20:54:13 root 1 0
c date and time created 82/07/15 20:54:13 by root
e
u
U
f b 
t
T
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 49
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
E 12
 *
I 12
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
 *
E 12
 *	%W% (Berkeley) %G%
 */
E 8

D 6
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/conf.h"
#include "../h/inode.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/buf.h"
#include "../h/proc.h"
#include "../h/fs.h"
E 6
I 6
D 23
#include "param.h"
#include "systm.h"
D 7
#include "conf.h"
E 7
D 12
#include "inode.h"
#include "dir.h"
E 12
D 21
#include "user.h"
E 21
#include "buf.h"
#include "proc.h"
D 12
#include "fs.h"
E 12
I 12
#include "file.h"
#include "vnode.h"
E 23
I 23
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/vnode.h>
E 23
I 17
D 21
#include "../ufs/quota.h"
E 17
#include "../ufs/inode.h"
#include "../ufs/fs.h"
E 21
I 21

I 27
#include <vm/vm.h>

E 27
D 23
#include "quota.h"
#include "inode.h"
#include "fs.h"
E 23
I 23
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
I 46
#include <ufs/ufs/ufs_extern.h>
E 46
E 23
E 21
E 12
E 6

I 23
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>

E 23
/*
D 22
 * Bmap defines the structure of file system storage
D 15
 * by returning the physical block number on a device given the
 * inode and the logical block number in a file.
 * When convenient, it also leaves the physical
 * block number of the next block of the file in rablock
 * for use in read-ahead.
E 15
I 15
 * by returning the physical block number on a device
 * given the inode and the logical block number in a file.
E 22
I 22
D 46
 * Bmap converts a the logical block number of a file
 * to its physical block number on the disk. The conversion
 * is done by using the logical block number to index into
 * the array of block pointers described by the dinode.
E 22
E 15
 */
D 12
/*VARARGS3*/
daddr_t
bmap(ip, bn, rwflg, size)
E 12
I 12
D 15
bmap(ip, bn, bnp, rablockp, rasizep)
E 15
I 15
D 23
bmap(ip, bn, bnp)
E 23
I 23
D 24
ffs_bmap(ip, bn, bnp)
E 23
E 15
E 12
	register struct inode *ip;
E 24
I 24
int
D 42
ffs_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
E 24
D 12
	daddr_t bn;
	int rwflg;
	int size;	/* supplied only when rwflg == B_WRITE */
E 12
I 12
	register daddr_t bn;
D 24
	daddr_t	*bnp;
E 24
I 24
	struct vnode **vpp;
	daddr_t *bnp;
E 42
I 42
D 45
ffs_bmap (ap)
	struct vop_bmap_args *ap;
E 45
I 45
ffs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
	} */ *ap;
E 45
D 43
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 43
E 42
E 24
D 15
	daddr_t	*rablockp;
	int *rasizep;
E 15
E 12
{
I 44
	register daddr_t bn = ap->a_bn;
I 45
	register daddr_t *bnp = ap->a_bnp;
E 45
E 44
I 24
	register struct inode *ip;
E 24
D 12
	register int i;
	int osize, nsize;
	struct buf *bp, *nbp;
	struct fs *fs;
	int j, sh;
D 2
	daddr_t nb, *bap, pref, blkpref();
E 2
I 2
	daddr_t nb, lbn, *bap, pref, blkpref();
E 12
I 12
	register struct fs *fs;
	register daddr_t nb;
	struct buf *bp;
	daddr_t *bap;
	int i, j, sh;
	int error;
E 12
E 2

I 24
	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
D 43
	ip = VTOI(vp);
	if (vpp != NULL)
		*vpp = ip->i_devvp;
	if (bnp == NULL)
E 43
I 43
	ip = VTOI(ap->a_vp);
	if (ap->a_vpp != NULL)
		*ap->a_vpp = ip->i_devvp;
D 45
	if (ap->a_bnp == NULL)
E 45
I 45
	if (bnp == NULL)
E 45
E 43
		return (0);
E 24
D 12
	if (bn < 0) {
		u.u_error = EFBIG;
		return ((daddr_t)0);
E 12
I 12
D 43
	if (bn < 0)
E 43
I 43
D 44
	if (ap->a_bn < 0)
E 44
I 44
	if (bn < 0)
E 44
E 43
		return (EFBIG);
	fs = ip->i_fs;

	/*
	 * The first NDADDR blocks are direct blocks
	 */
D 43
	if (bn < NDADDR) {
		nb = ip->i_db[bn];
E 43
I 43
D 44
	if (ap->a_bn < NDADDR) {
		nb = ip->i_db[ap->a_bn];
E 44
I 44
	if (bn < NDADDR) {
		nb = ip->i_db[bn];
E 44
E 43
		if (nb == 0) {
D 43
			*bnp = (daddr_t)-1;
E 43
I 43
D 45
			*ap->a_bnp = (daddr_t)-1;
E 45
I 45
			*bnp = (daddr_t)-1;
E 45
E 43
			return (0);
		}
D 15
		if (rablockp && rasizep) {
			if (bn < NDADDR - 1) {
				*rablockp = fsbtodb(fs, ip->i_db[bn + 1]);
				*rasizep = blksize(fs, ip, bn + 1);
			} else {
				*rablockp = 0;
				*rasizep = 0;
			}
		}
E 15
D 43
		*bnp = fsbtodb(fs, nb);
E 43
I 43
D 45
		*ap->a_bnp = fsbtodb(fs, nb);
E 45
I 45
		*bnp = fsbtodb(fs, nb);
E 45
E 43
		return (0);
E 12
	}
I 12
D 15

E 15
	/*
D 15
	 * Determine how many levels of indirection.
E 15
I 15
	 * Determine the number of levels of indirection.
E 15
	 */
	sh = 1;
D 43
	bn -= NDADDR;
E 43
I 43
D 44
	ap->a_bn -= NDADDR;
E 44
I 44
	bn -= NDADDR;
E 44
E 43
	for (j = NIADDR; j > 0; j--) {
		sh *= NINDIR(fs);
D 43
		if (bn < sh)
E 43
I 43
D 44
		if (ap->a_bn < sh)
E 44
I 44
		if (bn < sh)
E 44
E 43
			break;
D 43
		bn -= sh;
E 43
I 43
D 44
		ap->a_bn -= sh;
E 44
I 44
		bn -= sh;
E 44
E 43
	}
	if (j == 0)
		return (EFBIG);
D 15

E 15
	/*
D 15
	 * fetch the first indirect block
E 15
I 15
	 * Fetch through the indirect blocks.
E 15
	 */
	nb = ip->i_ib[NIADDR - j];
	if (nb == 0) {
D 43
		*bnp = (daddr_t)-1;
E 43
I 43
D 45
		*ap->a_bnp = (daddr_t)-1;
E 45
I 45
		*bnp = (daddr_t)-1;
E 45
E 43
		return (0);
	}
D 15

	/*
	 * fetch through the indirect blocks
	 */
E 15
	for (; j <= NIADDR; j++) {
		if (error = bread(ip->i_devvp, fsbtodb(fs, nb),
D 14
		    (int)fs->fs_bsize, &bp)) {
E 14
I 14
		    (int)fs->fs_bsize, NOCRED, &bp)) {
E 14
			brelse(bp);
			return (error);
		}
I 15
D 16
		if ((bp->b_flags & B_CACHE) == 0)
			reassignbuf(bp, ITOV(ip));
E 16
E 15
		bap = bp->b_un.b_daddr;
		sh /= NINDIR(fs);
D 43
		i = (bn / sh) % NINDIR(fs);
E 43
I 43
D 44
		i = (ap->a_bn / sh) % NINDIR(fs);
E 44
I 44
		i = (bn / sh) % NINDIR(fs);
E 44
E 43
		nb = bap[i];
		if (nb == 0) {
D 43
			*bnp = (daddr_t)-1;
E 43
I 43
D 45
			*ap->a_bnp = (daddr_t)-1;
E 45
I 45
			*bnp = (daddr_t)-1;
E 45
E 43
			brelse(bp);
			return (0);
		}
I 13
D 15
		if (j < NIADDR)
			brelse(bp);
E 15
I 15
		brelse(bp);
E 15
E 13
	}
D 15

	/*
	 * calculate read-ahead.
	 */
	if (rablockp && rasizep) {
		if (i < NINDIR(fs) - 1) {
			*rablockp = fsbtodb(fs, bap[i + 1]);
			*rasizep = fs->fs_bsize;
		} else {
			*rablockp = 0;
			*rasizep = 0;
		}
	}
E 15
D 43
	*bnp = fsbtodb(fs, nb);
E 43
I 43
D 45
	*ap->a_bnp = fsbtodb(fs, nb);
E 45
I 45
	*bnp = fsbtodb(fs, nb);
E 45
E 43
D 15
	brelse(bp);
E 15
	return (0);
}
I 42
D 43
#undef vp
#undef bn
#undef vpp
#undef bnp
E 43
E 42

/*
E 46
 * Balloc defines the structure of file system storage
D 15
 * by returning the physical block number on a device given the
 * inode and the logical block number in a file.
 * When unallocated entries are found, new physical blocks
 * are allocated.
E 15
I 15
 * by allocating the physical blocks on a device given
 * the inode and the logical block number in a file.
E 15
 */
D 15
balloc(ip, bn, size, bnp, flags)
E 15
I 15
D 23
balloc(ip, bn, size, bpp, flags)
E 23
I 23
D 26
ffs_balloc(ip, bn, size, bpp, flags)
E 26
I 26
D 53
ffs_balloc(ip, bn, size, cred, bpp, flags)
E 53
I 53
ffs_balloc(ip, lbn, size, cred, bpp, flags)
E 53
E 26
E 23
E 15
	register struct inode *ip;
D 53
	register daddr_t bn;
E 53
I 53
D 54
	register daddr_t lbn;
E 54
I 54
	register ufs_daddr_t lbn;
E 54
E 53
	int size;
I 26
	struct ucred *cred;
E 26
D 15
	daddr_t	*bnp;
E 15
I 15
	struct buf **bpp;
E 15
	int flags;
{
	register struct fs *fs;
D 54
	register daddr_t nb;
E 54
I 54
	register ufs_daddr_t nb;
E 54
	struct buf *bp, *nbp;
I 15
	struct vnode *vp = ITOV(ip);
E 15
D 46
	int osize, nsize, i, j, sh, error;
E 46
I 46
	struct indir indirs[NIADDR + 2];
D 50
	int osize, nsize, num, j, error;
E 50
E 46
D 15
	daddr_t lbn, *bap, pref, blkpref();
E 15
I 15
D 23
	daddr_t newb, lbn, *bap, pref, blkpref();
E 23
I 23
D 53
	daddr_t newb, lbn, *bap, pref;
E 53
I 53
D 54
	daddr_t newb, *bap, pref;
E 54
I 54
	ufs_daddr_t newb, *bap, pref;
E 54
E 53
I 50
D 55
	int osize, nsize, num, i, error;
E 55
I 55
	int deallocated, osize, nsize, num, i, error;
D 56
	ufs_daddr_t *allocib, *blkp, *allocblk, allociblk[NIADDR];
E 56
I 56
	ufs_daddr_t *allocib, *blkp, *allocblk, allociblk[NIADDR + 1];
E 56
E 55
E 50
E 23
E 15

I 15
D 50
	*bpp = (struct buf *)0;
E 50
I 50
	*bpp = NULL;
E 50
E 15
D 53
	if (bn < 0)
E 53
I 53
	if (lbn < 0)
E 53
		return (EFBIG);
E 12
	fs = ip->i_fs;
I 46
D 53
	lbn = bn;
E 53
E 46
D 12
	rablock = 0;
	rasize = 0;		/* conservative */
E 12

	/*
	 * If the next write will extend the file into a new block,
	 * and the file is currently composed of a fragment
	 * this fragment has to be extended to be a full block.
	 */
	nb = lblkno(fs, ip->i_size);
D 12
	if (rwflg == B_WRITE && nb < NDADDR && nb < bn) {
E 12
I 12
D 53
	if (nb < NDADDR && nb < bn) {
E 53
I 53
	if (nb < NDADDR && nb < lbn) {
E 53
E 12
		osize = blksize(fs, ip, nb);
		if (osize < fs->fs_bsize && osize > 0) {
D 12
			bp = realloccg(ip, ip->i_db[nb],
E 12
I 12
D 15
			error = realloccg(ip, ip->i_db[nb],
E 15
I 15
D 23
			error = realloccg(ip, nb,
E 15
E 12
D 2
				nb == 0 ? 0 : ip->i_db[nb - 1] + fs->fs_frag,
E 2
I 2
D 3
				blkpref(ip, nb, nb, &ip->i_db[0]),
E 2
				osize, fs->fs_bsize);
E 3
I 3
				blkpref(ip, nb, (int)nb, &ip->i_db[0]),
E 23
I 23
			error = ffs_realloccg(ip, nb,
				ffs_blkpref(ip, nb, (int)nb, &ip->i_db[0]),
E 23
D 12
				osize, (int)fs->fs_bsize);
I 4
			if (bp == NULL)
				return ((daddr_t)-1);
E 12
I 12
D 26
				osize, (int)fs->fs_bsize, &bp);
E 26
I 26
				osize, (int)fs->fs_bsize, cred, &bp);
E 26
D 15
			if (error) {
				*bnp = (daddr_t)-1;
E 15
I 15
			if (error)
E 15
				return (error);
D 15
			}
E 15
E 12
E 4
E 3
			ip->i_size = (nb + 1) * fs->fs_bsize;
I 20
D 25
			vnode_pager_setsize(ITOV(ip), (u_long)ip->i_size);
E 25
I 25
			vnode_pager_setsize(vp, (u_long)ip->i_size);
E 25
E 20
			ip->i_db[nb] = dbtofsb(fs, bp->b_blkno);
D 51
			ip->i_flag |= IUPD|ICHG;
E 51
I 51
D 52
			ip->i_flag |= IUPDATE | ICHANGE;
E 52
I 52
			ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 52
E 51
D 15
			bdwrite(bp);
E 15
I 15
			if (flags & B_SYNC)
				bwrite(bp);
			else
				bawrite(bp);
E 15
		}
	}
	/*
	 * The first NDADDR blocks are direct blocks
	 */
D 53
	if (bn < NDADDR) {
D 2
		i = bn;
		nb = ip->i_db[i];
E 2
I 2
		nb = ip->i_db[bn];
E 2
D 12
		if (rwflg == B_READ) {
			if (nb == 0)
				return ((daddr_t)-1);
			goto gotit;
		}
E 12
D 2
		if (nb == 0 || ip->i_size < (i + 1) * fs->fs_bsize) {
E 2
I 2
D 15
		if (nb == 0 || ip->i_size < (bn + 1) * fs->fs_bsize) {
E 2
			if (nb != 0) {
				/* consider need to reallocate a frag */
				osize = fragroundup(fs, blkoff(fs, ip->i_size));
				nsize = fragroundup(fs, size);
				if (nsize <= osize)
					goto gotit;
D 2
				bp = realloccg(ip, nb, i == 0 ?
					0 : ip->i_db[i - 1] + fs->fs_frag,
E 2
I 2
D 12
				bp = realloccg(ip, nb,
E 12
I 12
				error = realloccg(ip, nb,
E 12
D 3
					blkpref(ip, bn, bn, &ip->i_db[0]),
E 3
I 3
					blkpref(ip, bn, (int)bn, &ip->i_db[0]),
E 3
E 2
D 12
					osize, nsize);
E 12
I 12
					osize, nsize, &bp);
E 12
			} else {
D 2
				if (ip->i_size < (i + 1) * fs->fs_bsize)
E 2
I 2
				if (ip->i_size < (bn + 1) * fs->fs_bsize)
E 2
					nsize = fragroundup(fs, size);
				else
					nsize = fs->fs_bsize;
D 2
				bp = alloc(ip, i > 0 ?
					ip->i_db[i - 1] + fs->fs_frag : 0,
E 2
I 2
D 12
				bp = alloc(ip,
E 12
I 12
				error = alloc(ip,
E 12
D 3
					blkpref(ip, bn, bn, &ip->i_db[0]),
E 3
I 3
					blkpref(ip, bn, (int)bn, &ip->i_db[0]),
E 3
E 2
D 12
					nsize);
E 12
I 12
					nsize, &bp, flags);
E 12
			}
E 15
I 15
		if (nb != 0 && ip->i_size >= (bn + 1) * fs->fs_bsize) {
			error = bread(vp, bn, fs->fs_bsize, NOCRED, &bp);
E 53
I 53
	if (lbn < NDADDR) {
		nb = ip->i_db[lbn];
		if (nb != 0 && ip->i_size >= (lbn + 1) * fs->fs_bsize) {
			error = bread(vp, lbn, fs->fs_bsize, NOCRED, &bp);
E 53
E 15
D 12
			if (bp == NULL)
				return ((daddr_t)-1);
E 12
I 12
			if (error) {
D 15
				*bnp = (daddr_t)-1;
E 15
I 15
				brelse(bp);
E 15
				return (error);
			}
E 12
D 15
			nb = dbtofsb(fs, bp->b_blkno);
D 12
			if ((ip->i_mode&IFMT) == IFDIR)
E 12
I 12
			if ((ip->i_mode & IFMT) == IFDIR)
E 12
				/*
				 * Write directory blocks synchronously
				 * so they never appear with garbage in
				 * them on the disk.
I 12
				 * 
				 * NB: Should free space and return error
				 * if bwrite returns an error.
E 12
				 */
D 12
				bwrite(bp);
E 12
I 12
				error = bwrite(bp);
E 15
I 15
			*bpp = bp;
			return (0);
		}
		if (nb != 0) {
			/*
			 * Consider need to reallocate a fragment.
			 */
			osize = fragroundup(fs, blkoff(fs, ip->i_size));
			nsize = fragroundup(fs, size);
			if (nsize <= osize) {
D 53
				error = bread(vp, bn, osize, NOCRED, &bp);
E 53
I 53
				error = bread(vp, lbn, osize, NOCRED, &bp);
E 53
				if (error) {
					brelse(bp);
					return (error);
				}
			} else {
D 23
				error = realloccg(ip, bn,
					blkpref(ip, bn, (int)bn, &ip->i_db[0]),
					osize, nsize, &bp);
E 23
I 23
D 53
				error = ffs_realloccg(ip, bn,
				    ffs_blkpref(ip, bn, (int)bn, &ip->i_db[0]),
D 26
				    osize, nsize, &bp);
E 26
I 26
				    osize, nsize, cred, &bp);
E 53
I 53
				error = ffs_realloccg(ip, lbn,
				    ffs_blkpref(ip, lbn, (int)lbn,
					&ip->i_db[0]), osize, nsize, cred, &bp);
E 53
E 26
E 23
				if (error)
					return (error);
			}
		} else {
D 53
			if (ip->i_size < (bn + 1) * fs->fs_bsize)
E 53
I 53
			if (ip->i_size < (lbn + 1) * fs->fs_bsize)
E 53
				nsize = fragroundup(fs, size);
E 15
E 12
			else
D 15
				bdwrite(bp);
D 2
			ip->i_db[i] = nb;
E 2
I 2
			ip->i_db[bn] = nb;
E 2
			ip->i_flag |= IUPD|ICHG;
E 15
I 15
				nsize = fs->fs_bsize;
D 23
			error = alloc(ip, bn,
				blkpref(ip, bn, (int)bn, &ip->i_db[0]),
				nsize, &newb);
E 23
I 23
D 53
			error = ffs_alloc(ip, bn,
			    ffs_blkpref(ip, bn, (int)bn, &ip->i_db[0]),
E 53
I 53
			error = ffs_alloc(ip, lbn,
			    ffs_blkpref(ip, lbn, (int)lbn, &ip->i_db[0]),
E 53
D 26
			    nsize, &newb);
E 26
I 26
			    nsize, cred, &newb);
E 26
E 23
			if (error)
				return (error);
D 48
			bp = getblk(vp, bn, nsize);
E 48
I 48
D 53
			bp = getblk(vp, bn, nsize, 0, 0);
E 53
I 53
			bp = getblk(vp, lbn, nsize, 0, 0);
E 53
E 48
			bp->b_blkno = fsbtodb(fs, newb);
			if (flags & B_CLRBUF)
				clrbuf(bp);
E 15
		}
D 15
gotit:
D 2
		if (i < NDADDR - 1) {
			rablock = fsbtodb(fs, ip->i_db[i+1]);
			rasize = blksize(fs, ip, i+1);
E 2
I 2
D 12
		if (bn < NDADDR - 1) {
			rablock = fsbtodb(fs, ip->i_db[bn + 1]);
			rasize = blksize(fs, ip, bn + 1);
E 2
		}
		return (nb);
E 12
I 12
		*bnp = fsbtodb(fs, nb);
E 15
I 15
D 53
		ip->i_db[bn] = dbtofsb(fs, bp->b_blkno);
E 53
I 53
		ip->i_db[lbn] = dbtofsb(fs, bp->b_blkno);
E 53
D 51
		ip->i_flag |= IUPD|ICHG;
E 51
I 51
D 52
		ip->i_flag |= IUPDATE | ICHANGE;
E 52
I 52
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 52
E 51
		*bpp = bp;
E 15
		return (0);
E 12
	}
D 15

E 15
	/*
D 15
	 * Determine how many levels of indirection.
E 15
I 15
	 * Determine the number of levels of indirection.
E 15
	 */
I 2
	pref = 0;
E 2
D 46
	sh = 1;
I 2
	lbn = bn;
E 2
	bn -= NDADDR;
D 12
	for (j = NIADDR; j>0; j--) {
E 12
I 12
	for (j = NIADDR; j > 0; j--) {
E 12
		sh *= NINDIR(fs);
		if (bn < sh)
			break;
		bn -= sh;
	}
D 12
	if (j == 0) {
		u.u_error = EFBIG;
		return ((daddr_t)0);
	}
E 12
I 12
	if (j == 0)
		return (EFBIG);
E 46
I 46
D 53
	if (error = ufs_getlbns(vp, bn, indirs, &num))
E 53
I 53
	if (error = ufs_getlbns(vp, lbn, indirs, &num))
E 53
		return(error);
#ifdef DIAGNOSTIC
	if (num < 1)
		panic ("ffs_balloc: ufs_bmaparray returned indirect block\n");
#endif
E 46
E 12
D 15

E 15
	/*
D 15
	 * fetch the first indirect block
E 15
I 15
	 * Fetch the first indirect block allocating if necessary.
E 15
	 */
D 46
	nb = ip->i_ib[NIADDR - j];
E 46
I 46
	--num;
	nb = ip->i_ib[indirs[0].in_off];
I 55
D 56
	allocib = 0;
E 56
I 56
	allocib = NULL;
E 56
	allocblk = allociblk;
E 55
E 46
	if (nb == 0) {
D 2
		if (rwflg==B_READ ||
		    (bp = alloc(ip, (daddr_t)0, fs->fs_bsize)) == NULL)
E 2
I 2
D 12
		if (rwflg == B_READ)
E 2
			return ((daddr_t)-1);
E 12
I 2
D 3
		pref = blkpref(ip, lbn, 0, 0);
	        bp = alloc(ip, pref, fs->fs_bsize);
E 3
I 3
D 23
		pref = blkpref(ip, lbn, 0, (daddr_t *)0);
D 12
	        bp = alloc(ip, pref, (int)fs->fs_bsize);
E 3
		if (bp == NULL)
			return ((daddr_t)-1);
E 12
I 12
D 15
	        error = alloc(ip, pref, (int)fs->fs_bsize, &bp, B_CLRBUF);
		if (error) {
			*bnp = (daddr_t)-1;
E 15
I 15
	        if (error = alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb))
E 23
I 23
D 54
		pref = ffs_blkpref(ip, lbn, 0, (daddr_t *)0);
E 54
I 54
		pref = ffs_blkpref(ip, lbn, 0, (ufs_daddr_t *)0);
E 54
D 26
	        if (error = ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb))
E 26
I 26
	        if (error = ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize,
		    cred, &newb))
E 26
E 23
E 15
			return (error);
D 15
		}
E 12
E 2
		nb = dbtofsb(fs, bp->b_blkno);
E 15
I 15
		nb = newb;
I 56
		*allocblk++ = nb;
E 56
D 46
		bp = getblk(ip->i_devvp, fsbtodb(fs, nb), fs->fs_bsize);
E 46
I 46
D 48
		bp = getblk(vp, indirs[1].in_lbn, fs->fs_bsize);
E 48
I 48
		bp = getblk(vp, indirs[1].in_lbn, fs->fs_bsize, 0, 0);
E 48
D 56
		bp->b_blkno = fsbtodb(fs, newb);
E 56
I 56
		bp->b_blkno = fsbtodb(fs, nb);
E 56
E 46
		clrbuf(bp);
D 16
		if ((bp->b_flags & B_CACHE) == 0)
			reassignbuf(bp, vp);
E 16
E 15
		/*
		 * Write synchronously so that indirect blocks
		 * never point at garbage.
I 12
D 15
		 * 
		 * NB: Should free space and return error
		 * if bwrite returns an error.
E 15
E 12
		 */
D 12
		bwrite(bp);
E 12
I 12
D 15
		error = bwrite(bp);
E 15
I 15
D 56
		if (error = bwrite(bp)) {
D 23
			blkfree(ip, nb, fs->fs_bsize);
E 23
I 23
			ffs_blkfree(ip, nb, fs->fs_bsize);
E 23
			return (error);
		}
E 56
I 56
		if (error = bwrite(bp))
			goto fail;
E 56
I 55
		allocib = &ip->i_ib[indirs[0].in_off];
E 55
E 15
E 12
D 46
		ip->i_ib[NIADDR - j] = nb;
E 46
I 46
D 56
		ip->i_ib[indirs[0].in_off] = newb;
E 56
I 56
		*allocib = nb;
E 56
E 46
D 51
		ip->i_flag |= IUPD|ICHG;
E 51
I 51
D 52
		ip->i_flag |= IUPDATE | ICHANGE;
E 52
I 52
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 52
E 51
	}
D 15

E 15
	/*
D 15
	 * fetch through the indirect blocks
E 15
I 15
	 * Fetch through the indirect blocks, allocating as necessary.
E 15
	 */
D 15
	for (; j <= NIADDR; j++) {
I 10
#ifdef SECSIZE
		bp = bread(ip->i_dev, fsbtodb(fs, nb), (int)fs->fs_bsize,
		    fs->fs_dbsize);
#else SECSIZE
E 10
D 3
		bp = bread(ip->i_dev, fsbtodb(fs, nb), fs->fs_bsize);
E 3
I 3
D 12
		bp = bread(ip->i_dev, fsbtodb(fs, nb), (int)fs->fs_bsize);
I 10
#endif SECSIZE
E 10
E 3
		if (bp->b_flags & B_ERROR) {
E 12
I 12
		if (error = bread(ip->i_devvp, fsbtodb(fs, nb),
D 14
		    (int)fs->fs_bsize, &bp)) {
E 14
I 14
		    (int)fs->fs_bsize, NOCRED, &bp)) {
E 15
I 15
D 46
	for (; ; j++) {
		error = bread(ip->i_devvp, fsbtodb(fs, nb),
		    (int)fs->fs_bsize, NOCRED, &bp);
E 46
I 46
D 50
	for (j = 1; ; ) {
		error = bread(vp, indirs[j].in_lbn, (int)fs->fs_bsize, NOCRED,
		    &bp);
E 50
I 50
	for (i = 1;;) {
		error = bread(vp,
		    indirs[i].in_lbn, (int)fs->fs_bsize, NOCRED, &bp);
E 50
E 46
		if (error) {
E 15
E 14
E 12
			brelse(bp);
D 12
			return ((daddr_t)0);
E 12
I 12
D 55
			return (error);
E 55
I 55
			goto fail;
E 55
E 12
		}
I 15
D 16
		if ((bp->b_flags & B_CACHE) == 0)
			reassignbuf(bp, vp);
E 16
E 15
D 51
		bap = bp->b_un.b_daddr;
E 51
I 51
D 54
		bap = (daddr_t *)bp->b_data;
E 54
I 54
		bap = (ufs_daddr_t *)bp->b_data;
E 54
E 51
D 46
		sh /= NINDIR(fs);
		i = (bn / sh) % NINDIR(fs);
		nb = bap[i];
D 15
		if (nb == 0) {
D 12
			if (rwflg==B_READ) {
				brelse(bp);
				return ((daddr_t)-1);
			}
E 12
D 2
			if (i % (fs->fs_fsize / sizeof(daddr_t)) == 0 ||
			    bap[i - 1] == 0)
				pref = blkpref(ip->i_fs);
			else
				pref = bap[i - 1] + fs->fs_frag;
E 2
I 2
			if (pref == 0)
				if (j < NIADDR)
D 3
					pref = blkpref(ip, lbn, 0, 0);
E 3
I 3
					pref = blkpref(ip, lbn, 0,
						(daddr_t *)0);
E 3
				else
					pref = blkpref(ip, lbn, i, &bap[0]);
E 2
D 3
		        nbp = alloc(ip, pref, fs->fs_bsize);
E 3
I 3
D 12
		        nbp = alloc(ip, pref, (int)fs->fs_bsize);
E 3
			if (nbp == NULL) {
E 12
I 12
		        error = alloc(ip, pref, (int)fs->fs_bsize, &nbp,
				(j < NIADDR) ? B_CLRBUF : flags);
			if (error) {
E 12
				brelse(bp);
D 12
				return ((daddr_t)-1);
E 12
I 12
				*bnp = (daddr_t)-1;
				return (error);
E 12
			}
			nb = dbtofsb(fs, nbp->b_blkno);
D 12
			if (j < NIADDR || (ip->i_mode&IFMT) == IFDIR)
E 12
I 12
			if (j < NIADDR || (ip->i_mode & IFMT) == IFDIR)
E 12
				/*
				 * Write synchronously so indirect blocks
				 * never point at garbage and blocks
				 * in directories never contain garbage.
I 12
				 * 
				 * NB: Should free space and return error
				 * if bwrite returns an error.
E 12
				 */
D 12
				bwrite(nbp);
E 12
I 12
				error = bwrite(nbp);
E 12
			else
				bdwrite(nbp);
			bap[i] = nb;
E 15
I 15
		if (j == NIADDR)
E 46
I 46
D 50
		nb = bap[indirs[j].in_off];
		if (j == num)
E 50
I 50
		nb = bap[indirs[i].in_off];
		if (i == num)
E 50
E 46
			break;
I 46
D 50
		j += 1;
E 50
I 50
		i += 1;
E 50
E 46
		if (nb != 0) {
			brelse(bp);
			continue;
		}
		if (pref == 0)
D 23
			pref = blkpref(ip, lbn, 0, (daddr_t *)0);
		if (error = alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
E 23
I 23
D 54
			pref = ffs_blkpref(ip, lbn, 0, (daddr_t *)0);
E 54
I 54
			pref = ffs_blkpref(ip, lbn, 0, (ufs_daddr_t *)0);
E 54
		if (error =
D 26
		    ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
E 26
I 26
		    ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize, cred, &newb)) {
E 26
E 23
			brelse(bp);
D 55
			return (error);
E 55
I 55
			goto fail;
E 55
		}
I 55
D 56
		*allocblk++ = newb;
E 56
E 55
		nb = newb;
I 56
		*allocblk++ = nb;
E 56
D 46
		nbp = getblk(ip->i_devvp, fsbtodb(fs, nb), fs->fs_bsize);
E 46
I 46
D 48
		nbp = getblk(vp, indirs[j].in_lbn, fs->fs_bsize);
E 48
I 48
D 50
		nbp = getblk(vp, indirs[j].in_lbn, fs->fs_bsize, 0, 0);
E 50
I 50
		nbp = getblk(vp, indirs[i].in_lbn, fs->fs_bsize, 0, 0);
E 50
E 48
		nbp->b_blkno = fsbtodb(fs, nb);
E 46
		clrbuf(nbp);
D 16
		if ((nbp->b_flags & B_CACHE) == 0)
			reassignbuf(nbp, vp);
E 16
		/*
		 * Write synchronously so that indirect blocks
		 * never point at garbage.
		 */
		if (error = bwrite(nbp)) {
D 23
			blkfree(ip, nb, fs->fs_bsize);
E 23
I 23
D 55
			ffs_blkfree(ip, nb, fs->fs_bsize);
E 55
E 23
			brelse(bp);
D 55
			return (error);
E 55
I 55
			goto fail;
E 55
		}
D 46
		bap[i] = nb;
E 46
I 46
D 47
		bap[indirs[j].in_off] = nb;
E 47
I 47
D 50
		bap[indirs[j - 1].in_off] = nb;
E 50
I 50
		bap[indirs[i - 1].in_off] = nb;
E 50
E 47
E 46
D 16
		if (flags & B_SYNC)
E 16
I 16
		/*
		 * If required, write synchronously, otherwise use
D 46
		 * delayed write. If this is the first instance of
		 * the delayed write, reassociate the buffer with the
		 * file so it will be written if the file is sync'ed.
E 46
I 46
		 * delayed write.
E 46
		 */
		if (flags & B_SYNC) {
E 16
			bwrite(bp);
D 16
		else
E 16
I 16
D 46
		} else if (bp->b_flags & B_DELWRI) {
E 16
E 15
			bdwrite(bp);
E 46
I 16
		} else {
			bdwrite(bp);
D 46
			reassignbuf(bp, vp);
E 46
		}
E 16
D 15
		} else
E 15
I 15
	}
	/*
	 * Get the data block, allocating if necessary.
	 */
	if (nb == 0) {
D 23
		pref = blkpref(ip, lbn, i, &bap[0]);
		if (error = alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
E 23
I 23
D 46
		pref = ffs_blkpref(ip, lbn, i, &bap[0]);
E 46
I 46
D 50
		pref = ffs_blkpref(ip, lbn, indirs[j].in_off, &bap[0]);
E 46
		if (error =
D 26
		    ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
E 26
I 26
		    ffs_alloc(ip, lbn, pref, (int)fs->fs_bsize, cred, &newb)) {
E 50
I 50
		pref = ffs_blkpref(ip, lbn, indirs[i].in_off, &bap[0]);
		if (error = ffs_alloc(ip,
		    lbn, pref, (int)fs->fs_bsize, cred, &newb)) {
E 50
E 26
E 23
E 15
			brelse(bp);
I 15
D 55
			return (error);
E 55
I 55
			goto fail;
E 55
		}
I 55
D 56
		*allocblk++ = newb;
E 56
E 55
		nb = newb;
I 56
		*allocblk++ = nb;
E 56
D 48
		nbp = getblk(vp, lbn, fs->fs_bsize);
E 48
I 48
		nbp = getblk(vp, lbn, fs->fs_bsize, 0, 0);
E 48
		nbp->b_blkno = fsbtodb(fs, nb);
		if (flags & B_CLRBUF)
			clrbuf(nbp);
D 46
		bap[i] = nb;
E 46
I 46
D 50
		bap[indirs[j].in_off] = nb;
E 50
I 50
		bap[indirs[i].in_off] = nb;
E 50
E 46
D 16
		if (flags & B_SYNC)
E 16
I 16
		/*
		 * If required, write synchronously, otherwise use
D 46
		 * delayed write. If this is the first instance of
		 * the delayed write, reassociate the buffer with the
		 * file so it will be written if the file is sync'ed.
E 46
I 46
		 * delayed write.
E 46
		 */
		if (flags & B_SYNC) {
E 16
			bwrite(bp);
D 16
		else
E 16
I 16
D 46
		} else if (bp->b_flags & B_DELWRI) {
E 16
			bdwrite(bp);
E 46
I 16
		} else {
			bdwrite(bp);
D 46
			reassignbuf(bp, vp);
E 46
		}
E 16
		*bpp = nbp;
		return (0);
E 15
	}
D 15

D 12
	/*
	 * calculate read-ahead.
	 */
	if (i < NINDIR(fs) - 1) {
		rablock = fsbtodb(fs, bap[i+1]);
		rasize = fs->fs_bsize;
	}
	return (nb);
E 12
I 12
	*bnp = fsbtodb(fs, nb);
E 15
I 15
	brelse(bp);
D 18
	nbp = getblk(vp, lbn, fs->fs_bsize);
	nbp->b_blkno = fsbtodb(fs, nb);
	if ((flags & B_CLRBUF) && (nbp->b_flags & (B_DONE|B_DELWRI)) == 0) {
		brelse(nbp);
E 18
I 18
	if (flags & B_CLRBUF) {
E 18
		error = bread(vp, lbn, (int)fs->fs_bsize, NOCRED, &nbp);
		if (error) {
			brelse(nbp);
D 55
			return (error);
E 55
I 55
			goto fail;
E 55
		}
I 18
	} else {
D 48
		nbp = getblk(vp, lbn, fs->fs_bsize);
E 48
I 48
		nbp = getblk(vp, lbn, fs->fs_bsize, 0, 0);
E 48
		nbp->b_blkno = fsbtodb(fs, nb);
E 18
	}
	*bpp = nbp;
E 15
	return (0);
I 55
fail:
	/*
	 * If we have failed part way through block allocation, we
	 * have to deallocate any indirect blocks that we have allocated.
	 */
D 56
	if (allocib == 0) {
		deallocated = 0;
	} else {
		ffs_blkfree(ip, *allocib, fs->fs_bsize);
		*allocib = 0;
		deallocated = fs->fs_bsize;
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
	}
	for (blkp = allociblk; blkp < allocblk; blkp++) {
E 56
I 56
	for (deallocated = 0, blkp = allociblk; blkp < allocblk; blkp++) {
E 56
		ffs_blkfree(ip, *blkp, fs->fs_bsize);
		deallocated += fs->fs_bsize;
	}
I 56
	if (allocib != NULL)
		*allocib = 0;
E 56
	if (deallocated) {
#ifdef QUOTA
		/*
		 * Restore user's disk quota because allocation failed.
		 */
		(void) chkdq(ip, (long)-btodb(deallocated), cred, FORCE);
#endif
		ip->i_blocks -= btodb(deallocated);
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
	}
	return (error);
E 55
E 12
}
E 1
