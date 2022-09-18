h30188
s 00001/00001/00200
d D 8.4 95/05/08 12:24:20 mckusick 68 67
c missing decl
e
s 00118/00027/00083
d D 8.3 95/05/08 12:15:04 mckusick 67 66
c update from margo
e
s 00002/00002/00108
d D 8.2 95/03/21 00:27:49 mckusick 66 65
c daddr_t => ufs_daddr_t
e
s 00002/00002/00108
d D 8.1 93/06/11 16:27:15 bostic 65 64
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00107
d D 7.42 93/02/02 21:05:38 mckusick 64 63
c parameter to indicate interrupt
e
s 00001/00001/00108
d D 7.41 92/12/10 14:14:32 margo 63 62
c Change != to |= to assign flag values!
e
s 00002/00000/00107
d D 7.40 92/11/17 13:20:10 margo 62 61
c Seg read flag.
e
s 00053/00276/00054
d D 7.39 92/10/22 18:41:00 margo 61 60
c Do indirect block allocation in balloc instead of bmap.
e
s 00003/00002/00327
d D 7.38 92/10/01 08:56:24 margo 60 59
c Don't change inode and superblock free count until bwrite succeeds.
e
s 00020/00007/00309
d D 7.37 92/09/02 08:03:26 margo 59 58
c Check for free space during allocation (need to figure out where 
c to get the cred from still).
e
s 00030/00007/00286
d D 7.36 92/08/21 17:30:33 bostic 58 57
c Create indirect blocks as soon as the associated data blocks are 
c created, so we can do correct bookkeeping.
e
s 00000/00010/00293
d D 7.35 92/08/01 15:40:38 bostic 57 56
c delete VERBOSE #ifdef's
e
s 00001/00000/00302
d D 7.34 92/07/23 16:29:40 bostic 56 55
c Do block accounting when lfs_balloc allocates an indirect block.
e
s 00003/00001/00299
d D 7.33 92/07/20 16:22:07 bostic 55 54
c NULL pointer deref fix; fix block counts
e
s 00002/00001/00298
d D 7.32 92/07/12 16:15:01 mckusick 54 52
c new include location for specdev.h
e
s 00002/00001/00298
d R 7.32 92/07/12 15:59:50 mckusick 53 52
c new location for specdev.h
e
s 00016/00009/00283
d D 7.31 92/07/05 14:36:22 bostic 52 51
c describe ap structure (Kirk); Melton fix for NULL indirection from
c lfs_getlbns(); delete USES_VOP_whatever (Kirk)
e
s 00004/00012/00288
d D 7.30 92/05/15 13:55:10 heideman 51 50
c vnodeop argument macro expansion
e
s 00008/00001/00292
d D 7.29 92/05/15 12:21:16 heideman 50 49
c direct vop calls cleaned up by hand
e
s 00012/00006/00281
d D 7.28 92/05/14 17:28:53 heideman 49 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 17:05:12 heideman 48 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 16:46:06 heideman 47 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 16:36:00 heideman 46 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 15:55:56 heideman 45 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 15:42:07 heideman 44 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 14:48:01 heideman 43 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 12:51:25 heideman 42 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 11:48:47 heideman 41 36
c vnode interface conversion
e
s 00012/00006/00281
d R 7.28 92/05/14 10:29:12 heideman 40 36
c vnode interface conversion
e
s 00017/00006/00281
d R 7.28 92/05/13 23:07:37 heideman 39 36
c vnode interface conversion
e
s 00017/00006/00281
d R 7.28 92/05/13 18:54:25 heideman 38 36
c vnode interface conversion
e
s 00017/00006/00281
d R 7.28 92/05/13 18:26:31 heideman 37 36
c vnode interface conversion
e
s 00015/00023/00272
d D 7.27 92/03/18 11:08:30 bostic 36 35
c incorrect bmap array processing on double-indirect blocks
e
s 00002/00002/00293
d D 7.26 92/01/10 15:28:29 bostic 35 34
c lfs_bmap uses UNASSIGNED (-1), not LFS_UNUSED_DADDR (0); from Carl
e
s 00041/00000/00254
d D 7.25 91/12/31 14:15:37 bostic 34 33
c add lfs_balloc, routine to allocate a block for writing
e
s 00001/00001/00253
d D 7.24 91/12/15 16:10:43 bostic 33 32
c don't make routines static
e
s 00142/00064/00112
d D 7.23 91/12/06 16:40:10 bostic 32 31
c LFS version 2; break bmap into three routines, using lfs_getlbns for
c real mapping
e
s 00037/00065/00139
d D 7.22 91/12/06 16:18:51 bostic 31 30
c new addressing conventions, using negative numbers off first block number
e
s 00104/00037/00100
d D 7.21 91/12/06 16:17:21 bostic 30 29
c make triply indirected blocks work
e
s 00015/00004/00122
d D 7.20 91/11/05 15:32:05 mckusick 29 28
c reorganization to move ufsmount ops to be vnode ops; 
c bmap becomes entirely filesystem specific
e
s 00007/00007/00119
d D 7.19 91/11/01 17:37:26 bostic 28 27
c don't typedef struct lfs for now
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00037/00046/00089
d D 7.18 91/11/01 17:29:10 bostic 27 26
c checkpoint before integration
e
s 00004/00003/00131
d D 7.17 91/10/09 11:24:15 root 26 25
c lint, use UNASSIGNED, not -1
e
s 00003/00001/00131
d D 7.16 91/10/02 09:00:25 bostic 25 24
c checkpoint
e
s 00057/00022/00075
d D 7.15 91/09/25 14:30:05 bostic 24 23
c checkpoint, but not because it's working
e
s 00012/00249/00085
d D 7.14 91/09/20 13:47:32 bostic 23 22
c checkpoint before lfs_iupdat -> ITIMES; reads almost work...
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
D 28
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 28
I 28
D 65
 * Copyright (c) 1989, 1991 Regents of the University of California.
E 28
 * All rights reserved.
E 65
I 65
 * Copyright (c) 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 65
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
D 61

E 61
I 25
D 27
#ifdef LOGFS
E 25
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
I 24
#include "time.h"
#include "resource.h"
#include "resourcevar.h"
E 24
#include "proc.h"
D 12
#include "fs.h"
E 12
I 12
#include "file.h"
#include "vnode.h"
I 24
#include "mount.h"
#include "specdev.h"
E 27
I 27
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/resourcevar.h>
D 54
#include <sys/specdev.h>
E 54
#include <sys/trace.h>
I 54

#include <miscfs/specfs/specdev.h>
E 54
E 27
E 24
I 17
D 21
#include "../ufs/quota.h"
E 17
#include "../ufs/inode.h"
#include "../ufs/fs.h"
E 21
I 21

D 23
#include "quota.h"
#include "inode.h"
#include "fs.h"
E 23
I 23
D 27
#include "../ufs/quota.h"
#include "../ufs/inode.h"
I 24
#include "../ufs/ufsmount.h"
#include "trace.h"
E 24
#include "lfs.h"
#include "lfs_extern.h"
E 27
I 27
D 28
#include <ufs/quota.h>
#include <ufs/inode.h>
#include <ufs/ufsmount.h>
E 28
I 28
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
E 28
E 27
E 23
E 21
E 12
E 6

I 27
D 28
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 28
I 28
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 28

I 32
D 33
static int lfs_getlbns __P((struct vnode *, daddr_t, INDIR *, int *));
E 33
I 33
D 61
int lfs_getlbns __P((struct vnode *, daddr_t, INDIR *, int *));
E 33

E 32
E 27
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
D 27
 * Bmap converts a the logical block number of a file
 * to its physical block number on the disk. The conversion
 * is done by using the logical block number to index into
 * the array of block pointers described by the dinode.
E 27
I 27
 * Bmap converts a the logical block number of a file to its physical block
 * number on the disk. The conversion is done by using the logical block
 * number to index into the array of block pointers described by the dinode.
I 30
D 32
 *
E 32
I 32
 */
E 61
int
D 49
lfs_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	register daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 49
I 49
D 52
lfs_bmap (ap)
	struct vop_bmap_args *ap;
E 52
I 52
D 61
lfs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
	} */ *ap;
E 52
D 51
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 51
E 49
{
D 57
#ifdef VERBOSE
	printf("lfs_bmap\n");
#endif
E 57
	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
D 51
	if (vpp != NULL)
		*vpp = VTOI(vp)->i_devvp;
	if (bnp == NULL)
E 51
I 51
	if (ap->a_vpp != NULL)
		*ap->a_vpp = VTOI(ap->a_vp)->i_devvp;
	if (ap->a_bnp == NULL)
E 51
		return (0);

D 51
	return (lfs_bmaparray(vp, bn, bnp, NULL, NULL));
E 51
I 51
	return (lfs_bmaparray(ap->a_vp, ap->a_bn, ap->a_bnp, NULL, NULL));
E 51
}
I 49
D 51
#undef vp
#undef bn
#undef vpp
#undef bnp
E 51
E 49

/*
E 32
 * LFS has a different version of bmap from FFS because of a naming conflict.
 * In FFS, meta blocks are given real disk addresses at allocation time, and
 * are linked into the device vnode, using a logical block number which is
 * the same as the physical block number.  This can't be done by LFS because
 * blocks aren't given disk addresses until they're written, so there's no
 * way to distinguish the meta-data blocks for one file from any other file.
 * This means that meta-data blocks have to be on the vnode for the file so
 * they can be found, and have to have "names" different from the standard
 * data blocks.  To do this, we divide the name space into positive and
 * negative block numbers, and give the meta-data blocks negative logical
D 31
 * numbers.
 *
 * The mapping for meta-data blocks is as follows (assuming a 4K block size):
 *
 * -1 -- single indirect
 * -2 -- double indirect:
 *		single indirect blocks -4, -1027
 * -3 -- triple indirect:
 *		double indirect blocks -1028, -2051
 *		single indirect blocks -2052, -(1M + 2052 - 1)
E 31
I 31
 * numbers.  Indirect blocks are addressed by the negative address of the
 * first data block to which they point.  Double indirect blocks are addressed
 * by one less than the address of the first indirect block to which they
 * point.  Triple indirect blocks are addressed by one less than the address
 * of the first double indirect block to which they point.
E 31
E 30
E 27
E 22
E 15
 */
I 26
int
E 26
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
D 29
lfs_bmap(ip, bn, bnp)
E 23
E 15
E 12
	register struct inode *ip;
E 29
I 29
D 32
lfs_bmap(vp, bn, vpp, bnp)
E 32
I 32
lfs_bmaparray(vp, bn, bnp, ap, nump)
E 32
	struct vnode *vp;
E 29
D 12
	daddr_t bn;
	int rwflg;
	int size;	/* supplied only when rwflg == B_WRITE */
E 12
I 12
	register daddr_t bn;
D 29
	daddr_t	*bnp;
E 29
I 29
D 32
	struct vnode **vpp;
E 32
	daddr_t *bnp;
I 32
	INDIR *ap;
	int *nump;
E 32
E 29
D 15
	daddr_t	*rablockp;
	int *rasizep;
E 15
E 12
{
I 50
D 52
	USES_VOP_STRATEGY;
E 52
E 50
I 29
	register struct inode *ip;
E 29
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
D 23
	register struct fs *fs;
E 23
I 23
D 27
	register LFS *fs;					/* LFS */
E 27
I 27
D 28
	register LFS *fs;
E 28
I 28
D 32
	register struct lfs *fs;
E 28
E 27
E 23
	register daddr_t nb;
E 32
I 24
D 29
	struct vnode *devvp, *vp;
E 29
I 29
D 30
	struct vnode *devvp;
E 30
E 29
E 24
	struct buf *bp;
I 32
	struct lfs *fs;
E 32
D 24
	daddr_t *bap;
	int i, j, sh;
E 24
I 24
D 30
	daddr_t *bap, daddr;
	daddr_t lbn_ind;
D 26
	int i, j, off, sh;
E 26
I 26
	int j, off, sh;
E 26
E 24
	int error;
E 30
I 30
	struct vnode *devvp;
D 31
	daddr_t *bap, daddr, lbn_ind, doing_a_triple;
	int error, j, off, sh, sh_ind;
E 31
I 31
D 32
	daddr_t *bap, daddr, metalbn;
	long realbn;
	int error, j, off, sh;
E 32
I 32
	INDIR a[NIADDR], *xap;
	daddr_t *bap, daddr;
	long metalbn;
D 59
	int error, num, off;
E 59
I 59
	int bb, error, num, off;
E 59
I 52
	struct vop_strategy_args vop_strategy_a;
E 52
E 32
E 31
E 30
E 12
E 2

I 29
D 32
	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
	ip = VTOI(vp);
	if (vpp != NULL)
		*vpp = ip->i_devvp;
	if (bnp == NULL)
		return (0);
E 32
E 29
I 23
D 30
printf("lfs_bmap: block number %d, inode %d\n", bn, ip->i_number);
E 23
D 12
	if (bn < 0) {
		u.u_error = EFBIG;
		return ((daddr_t)0);
E 12
I 12
D 24
	if (bn < 0)
		return (EFBIG);
E 24
D 23
	fs = ip->i_fs;
E 23
I 23
D 27
	fs = ip->i_lfs;						/* LFS */
E 27
I 27
	fs = ip->i_lfs;
E 30
E 27
E 23
D 52

E 52
I 32
	ip = VTOI(vp);
E 32
D 30
	/*
I 24
D 27
	 * We access all blocks in the cache, even indirect blocks by means of
	 * a logical address. Indirect blocks (single, double, triple) all have
	 * negative block numbers. The first NDADDR blocks are direct blocks,
	 * the first NIADDR negative blocks are the indirect block pointers.
	 * The single, double and triple indirect blocks in the inode
	 * are addressed: -1, -2 and -3 respectively.  
	 * XXX we don't handle triple indirect at all.
E 27
I 27
	 * We access all blocks in the cache, even indirect blocks by means
	 * of a logical address. Indirect blocks (single, double, triple) all
	 * have negative block numbers. The first NDADDR blocks are direct
	 * blocks, the first NIADDR negative blocks are the indirect block
	 * pointers.  The single, double and triple indirect blocks in the
	 * inode * are addressed: -1, -2 and -3 respectively.  
	 *
	 * XXX
	 * We don't handle triple indirect at all.
	 *
	 * XXX
	 * This panic shouldn't be here???
E 27
	 */
D 27
	if (bn < 0) {
		/* Shouldn't be here -- we don't think */
		printf("lfs_bmap: NEGATIVE indirect block number %d\n", bn);
		panic("negative indirect block number");
	}
E 27
I 27
	if (bn < 0)
		panic("lfs_bmap: negative indirect block number %d", bn);
E 27

E 30
I 30
D 57
#ifdef VERBOSE
D 32
printf("lfs_bmap: block number %d, inode %d\n", bn, ip->i_number);
E 32
I 32
	printf("lfs_bmap: block number %d, inode %d\n", bn, ip->i_number);
E 32
#endif
E 57
I 31
D 32
	realbn = bn;
	if ((long)bn < 0)
		bn = -(long)bn;
E 32
I 32
#ifdef DIAGNOSTIC
	if (ap != NULL && nump == NULL || ap == NULL && nump != NULL)
		panic("lfs_bmaparray: invalid arguments");
#endif
E 32

E 31
E 30
D 27
	/*
E 24
	 * The first NDADDR blocks are direct blocks
	 */
E 27
I 27
D 32
	/* The first NDADDR blocks are direct blocks. */
E 27
	if (bn < NDADDR) {
		nb = ip->i_db[bn];
D 30
		if (nb == 0) {
E 30
I 30
D 31
		if (nb == LFS_UNUSED_DADDR)
E 31
I 31
		if (nb == 0) {
E 32
I 32
	xap = ap == NULL ? a : ap;
I 55
	if (!nump)
		nump = &num;
E 55
	if (error = lfs_getlbns(vp, bn, xap, nump))
		return (error);

	num = *nump;
D 36
	fs = ip->i_lfs;
E 36
I 36
D 57

E 57
E 36
	if (num == 0) {
		*bnp = ip->i_db[bn];
		if (*bnp == 0)
E 32
E 31
E 30
D 26
			*bnp = (daddr_t)-1;
E 26
I 26
			*bnp = UNASSIGNED;
E 26
D 30
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
D 23
		*bnp = fsbtodb(fs, nb);
E 23
I 23
		*bnp = nb;
E 30
I 30
D 31
		else
			*bnp = nb;
E 31
I 31
D 32
			return (0);
		}
		*bnp = nb;
E 32
E 31
E 30
E 23
		return (0);
E 12
	}
I 12
D 15

E 15
D 27
	/*
D 15
	 * Determine how many levels of indirection.
E 15
I 15
	 * Determine the number of levels of indirection.
E 15
	 */
E 27
I 27

I 36

	/* Get disk address out of indirect block array */
	daddr = ip->i_ib[xap->in_off];

E 36
D 30
	/* Determine the number of levels of indirection. */
E 30
I 30
D 32
	/* 
D 31
	 * The first NIADDR negative blocks are the indirect block pointers.
E 31
	 * Determine the number of levels of indirection.  After this loop
	 * is done, sh indicates the number of data blocks possible at the
D 31
	 * given level of indirection, lbn_ind is the logical block number
	 * of the next indirect block to retrieve, and NIADDR - j is the
	 * number of levels of indirection needed to locate the requested
	 * block.
E 31
I 31
	 * given level of indirection, and NIADDR - j is the number of levels
	 * of indirection needed to locate the requested block.
E 31
	 */
I 31
	bn -= NDADDR;
E 31
	fs = ip->i_lfs;
E 30
E 27
	sh = 1;
D 31
	bn -= NDADDR;
I 24
	lbn_ind = 0;
E 31
E 24
	for (j = NIADDR; j > 0; j--) {
I 24
D 30
		lbn_ind--;
E 30
I 30
D 31
		--lbn_ind;
E 31
E 30
E 24
		sh *= NINDIR(fs);
		if (bn < sh)
			break;
		bn -= sh;
	}
	if (j == 0)
		return (EFBIG);
D 15

E 15
D 27
	/*
D 15
	 * fetch the first indirect block
E 15
I 15
	 * Fetch through the indirect blocks.
E 15
	 */
E 27
D 24
	nb = ip->i_ib[NIADDR - j];
	if (nb == 0) {
		*bnp = (daddr_t)-1;
		return (0);
	}
D 15

	/*
	 * fetch through the indirect blocks
	 */
E 15
	for (; j <= NIADDR; j++) {
D 23
		if (error = bread(ip->i_devvp, fsbtodb(fs, nb),
D 14
		    (int)fs->fs_bsize, &bp)) {
E 14
I 14
		    (int)fs->fs_bsize, NOCRED, &bp)) {
E 23
I 23
		if (error = bread(ip->i_devvp, nb, (int)fs->lfs_bsize,
		    NOCRED, &bp)) {		/* LFS */
E 24
I 24

I 31
	/* Calculate the address of the first meta-block. */
	if (realbn >= 0)
		metalbn = -(realbn - bn + NIADDR - j);
	else
		metalbn = -(-realbn - bn + NIADDR - j);

E 31
I 27
D 30
	/* Fetch through the indirect blocks. */
E 27
	vp = ITOV(ip);
E 30
I 30
	/* 
	 * Fetch through the indirect blocks.  At each iteration, off is the
	 * offset into the bap array which is an array of disk addresses at
	 * the current level of indirection.
	 */
E 32
I 32
	/* Fetch through the indirect blocks. */
E 32
D 31
	bap = ip->i_ib;
E 31
D 36
	bp = NULL;
E 36
I 36
	fs = ip->i_lfs;
E 36
E 30
	devvp = VFSTOUFS(vp->v_mount)->um_devvp;
D 30
	for (off = NIADDR - j, bap = ip->i_ib; j <= NIADDR; j++) {
		if((daddr = bap[off]) == 0) {
E 30
I 30
D 31
	off = NIADDR - j;
	doing_a_triple = 0;
	for (; j <= NIADDR; j++) {
E 31
I 31
D 32
	for (off = NIADDR - j, bap = ip->i_ib; j <= NIADDR; j++) {
E 32
I 32
D 36
	for (bap = ip->i_ib; num--; off = xap->in_off, ++xap) {
		off = xap->in_off;
		metalbn = xap->in_lbn;
E 36

E 32
E 31
D 36
		/*
		 * In LFS, it's possible to have a block appended to a file
		 * for which the meta-blocks have not yet been allocated.
		 * This is a win if the file never gets written or if the
		 * file's growing.
		 */
		if ((daddr = bap[off]) == 0) {
E 30
D 26
			daddr = (daddr_t)-1;
E 26
I 26
			daddr = UNASSIGNED;
E 26
			break;
		}
I 31

		/* If searching for a meta-data block, quit when found. */
E 36
I 36
D 58
	for (bp = NULL, ++xap; daddr && --num; ++xap) {
E 58
I 58
	for (bp = NULL, ++xap; --num; ++xap) {
		/*
		 * If we were called explicitly then we don't want to create
		 * indirect blocks.  Since BMAP calls pass NULL for the ap,
		 * we can use that to detect if we are called from BMAP or not.
		 */
		if (daddr == 0 && ap != NULL)
			break;

E 58
		/* If looking for a meta-block, break out when we find it. */
		metalbn = xap->in_lbn;
E 36
D 32
		if (metalbn == realbn)
E 32
I 32
		if (metalbn == bn)
E 32
			break;

E 31
I 30
		/*
		 * Read in the appropriate indirect block.  LFS can't do a
		 * bread because bread knows that FFS will hand it the device
		 * vnode, not the file vnode, so the b_dev and b_blkno would
		 * be wrong.
		 *
		 * XXX
		 * This REALLY needs to be fixed, at the very least it needs
D 32
		 * to be rethought when the buffer cache goes away.
E 32
I 32
		 * to be rethought when the buffer cache goes away.  When it's
		 * fixed, change lfs_bmaparray and lfs_getlbns to take an ip,
		 * not a vp.
E 32
		 */
E 30
		if (bp)
E 24
E 23
E 14
			brelse(bp);
D 24
			return (error);
E 24
I 24
D 31
		bp = getblk(vp, lbn_ind, fs->lfs_bsize);
E 31
I 31
		bp = getblk(vp, metalbn, fs->lfs_bsize);
E 31
		if (bp->b_flags & (B_DONE | B_DELWRI)) {
D 31
			trace(TR_BREADHIT, pack(vp, size), lbn_ind);
E 31
I 31
			trace(TR_BREADHIT, pack(vp, size), metalbn);
I 58
		} else if (!daddr) {
			/* Need to create an indirect block */
			trace(TR_BREADMISS, pack(vp, size), metalbn);
			bzero(bp->b_un.b_addr, fs->lfs_bsize);
			*bnp = UNASSIGNED;
D 59
			ip->i_blocks += fsbtodb(fs, 1);
			fs->lfs_bfree -= fsbtodb(fs, 1);
E 59
I 59
			bb = fsbtodb(fs, 1);
			/* XXX Need to figure out how to get a cred */
			if (!ISSPACE_XXX(fs, bb)) {
				bp->b_flags |= B_INVAL;
				brelse (bp);
				return (ENOSPC);
			}
D 60
			ip->i_blocks += bb;
			fs->lfs_bfree -= bb;
E 60
E 59
			daddr = bp->b_un.b_daddr[xap->in_off];
			if (error = VOP_BWRITE(bp))
				return (error);
I 60
			ip->i_blocks += bb;
			fs->lfs_bfree -= bb;
E 60
			bp = NULL;
			continue;
E 58
E 31
		} else {
D 30
			trace(TR_BREADMISS, pack(vp, size), lbn_ind);
			bp->b_blkno = daddr;
E 30
D 31
			bp->b_flags |= B_READ;
E 31
I 31
			trace(TR_BREADMISS, pack(vp, size), metalbn);
E 31
I 30
			bp->b_blkno = daddr;
I 31
			bp->b_flags |= B_READ;
E 31
E 30
			bp->b_dev = devvp->v_rdev;
D 25
			(*(devvp->v_op->vop_strategy))(bp);
E 25
I 25
D 50
			(devvp->v_op->vop_strategy)(bp);
E 50
I 50
			/*
			 * Call a strategy VOP by hand.
			 */
			vop_strategy_a.a_desc = VDESC(vop_strategy);
			vop_strategy_a.a_bp=bp;
			VOCALL(devvp->v_op, VOFFSET(vop_strategy), \
			       &vop_strategy_a);
E 50
I 30
D 31
			trace(TR_BREADMISS, pack(vp, size), lbn_ind);
E 31
E 30
E 25
			curproc->p_stats->p_ru.ru_inblock++;	/* XXX */
			if (error = biowait(bp)) {
				brelse(bp);
				return (error);
			}
E 24
		}
I 31
D 32

E 32
E 31
I 15
D 16
		if ((bp->b_flags & B_CACHE) == 0)
			reassignbuf(bp, ITOV(ip));
E 16
E 15
D 36
		bap = bp->b_un.b_daddr;
E 36
I 36
		daddr = bp->b_un.b_daddr[xap->in_off];
E 36
D 32
		sh /= NINDIR(fs);
D 24
		i = (bn / sh) % NINDIR(fs);
		nb = bap[i];
		if (nb == 0) {
			*bnp = (daddr_t)-1;
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
E 24
I 24
		off = (bn / sh) % NINDIR(fs);
D 30
		lbn_ind  = -(NIADDR + 1 + off);
E 30
I 30
D 31

		/*
		 * Ahem.  Now the disgusting part.  We have to figure out
		 * the logical block number for the next meta-data block.
		 * There are really three equations...  Note the clever
		 * use of the doing_a_triple variable to hold the last
		 * offset into the block of pointers.
		 */
		switch(j) {
		case 1:
			/* The triple indirect block found in the inode. */
			doing_a_triple = off;
			lbn_ind = -(NIADDR + 1 + off + NINDIR(fs));
			break;
		case 2:
			/*
			 * The double indirect block found after indirecting
			 * through a triple indirect block.
			 */
			if (doing_a_triple)
				lbn_ind = -((doing_a_triple + 2) * NINDIR(fs) +
				    NIADDR + 1);

			/* The double indirect block found in the inode. */
			else
				lbn_ind = -(NIADDR + 1 + off);
			break;
		case 3:
			/*
			 * A single indirect block; lbn_ind isn't used again,
			 * so don't do anything.
			 */
			break;
		}
E 31
I 31
		metalbn -= -1 + off * sh;
E 32
E 31
E 30
E 24
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
D 23
	*bnp = fsbtodb(fs, nb);
D 15
	brelse(bp);
E 15
	return (0);
}

/*
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
balloc(ip, bn, size, bpp, flags)
E 15
	register struct inode *ip;
	register daddr_t bn;
	int size;
D 15
	daddr_t	*bnp;
E 15
I 15
	struct buf **bpp;
E 15
	int flags;
{
	register struct fs *fs;
	register daddr_t nb;
	struct buf *bp, *nbp;
I 15
	struct vnode *vp = ITOV(ip);
E 15
	int osize, nsize, i, j, sh, error;
D 15
	daddr_t lbn, *bap, pref, blkpref();
E 15
I 15
	daddr_t newb, lbn, *bap, pref, blkpref();
E 15

I 15
	*bpp = (struct buf *)0;
E 15
	if (bn < 0)
		return (EFBIG);
E 12
	fs = ip->i_fs;
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
	if (nb < NDADDR && nb < bn) {
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
D 12
				osize, (int)fs->fs_bsize);
I 4
			if (bp == NULL)
				return ((daddr_t)-1);
E 12
I 12
				osize, (int)fs->fs_bsize, &bp);
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
			vnode_pager_setsize(ITOV(ip), (u_long)ip->i_size);
E 20
			ip->i_db[nb] = dbtofsb(fs, bp->b_blkno);
			ip->i_flag |= IUPD|ICHG;
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
				error = bread(vp, bn, osize, NOCRED, &bp);
				if (error) {
					brelse(bp);
					return (error);
				}
			} else {
				error = realloccg(ip, bn,
					blkpref(ip, bn, (int)bn, &ip->i_db[0]),
					osize, nsize, &bp);
				if (error)
					return (error);
			}
		} else {
			if (ip->i_size < (bn + 1) * fs->fs_bsize)
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
			error = alloc(ip, bn,
				blkpref(ip, bn, (int)bn, &ip->i_db[0]),
				nsize, &newb);
			if (error)
				return (error);
			bp = getblk(vp, bn, nsize);
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
		ip->i_db[bn] = dbtofsb(fs, bp->b_blkno);
		ip->i_flag |= IUPD|ICHG;
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
	nb = ip->i_ib[NIADDR - j];
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
		bp = getblk(ip->i_devvp, fsbtodb(fs, nb), fs->fs_bsize);
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
		if (error = bwrite(bp)) {
			blkfree(ip, nb, fs->fs_bsize);
			return (error);
		}
E 15
E 12
		ip->i_ib[NIADDR - j] = nb;
		ip->i_flag |= IUPD|ICHG;
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
	for (; ; j++) {
		error = bread(ip->i_devvp, fsbtodb(fs, nb),
		    (int)fs->fs_bsize, NOCRED, &bp);
		if (error) {
E 15
E 14
E 12
			brelse(bp);
D 12
			return ((daddr_t)0);
E 12
I 12
			return (error);
E 12
		}
I 15
D 16
		if ((bp->b_flags & B_CACHE) == 0)
			reassignbuf(bp, vp);
E 16
E 15
		bap = bp->b_un.b_daddr;
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
			break;
		if (nb != 0) {
			brelse(bp);
			continue;
		}
		if (pref == 0)
			pref = blkpref(ip, lbn, 0, (daddr_t *)0);
		if (error = alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
			brelse(bp);
			return (error);
		}
		nb = newb;
		nbp = getblk(ip->i_devvp, fsbtodb(fs, nb), fs->fs_bsize);
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
			blkfree(ip, nb, fs->fs_bsize);
			brelse(bp);
			return (error);
		}
		bap[i] = nb;
D 16
		if (flags & B_SYNC)
E 16
I 16
		/*
		 * If required, write synchronously, otherwise use
		 * delayed write. If this is the first instance of
		 * the delayed write, reassociate the buffer with the
		 * file so it will be written if the file is sync'ed.
		 */
		if (flags & B_SYNC) {
E 16
			bwrite(bp);
D 16
		else
E 16
I 16
		} else if (bp->b_flags & B_DELWRI) {
E 16
E 15
			bdwrite(bp);
I 16
		} else {
			bdwrite(bp);
			reassignbuf(bp, vp);
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
		pref = blkpref(ip, lbn, i, &bap[0]);
		if (error = alloc(ip, lbn, pref, (int)fs->fs_bsize, &newb)) {
E 15
			brelse(bp);
I 15
			return (error);
		}
		nb = newb;
		nbp = getblk(vp, lbn, fs->fs_bsize);
		nbp->b_blkno = fsbtodb(fs, nb);
		if (flags & B_CLRBUF)
			clrbuf(nbp);
		bap[i] = nb;
D 16
		if (flags & B_SYNC)
E 16
I 16
		/*
		 * If required, write synchronously, otherwise use
		 * delayed write. If this is the first instance of
		 * the delayed write, reassociate the buffer with the
		 * file so it will be written if the file is sync'ed.
		 */
		if (flags & B_SYNC) {
E 16
			bwrite(bp);
D 16
		else
E 16
I 16
		} else if (bp->b_flags & B_DELWRI) {
E 16
			bdwrite(bp);
I 16
		} else {
			bdwrite(bp);
			reassignbuf(bp, vp);
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
			return (error);
		}
I 18
	} else {
		nbp = getblk(vp, lbn, fs->fs_bsize);
		nbp->b_blkno = fsbtodb(fs, nb);
E 18
	}
	*bpp = nbp;
E 23
I 23
D 24
	*bnp = nb;
E 24
I 24
	if (bp)
		brelse(bp);

D 36
	*bnp = daddr;
E 36
I 36
	*bnp = daddr == 0 ? UNASSIGNED : daddr;
E 36
I 32
	return (0);
}

/*
 * Create an array of logical block number/offset pairs which represent the
 * path of indirect blocks required to access a data block.  The first "pair"
 * contains the logical block number of the appropriate single, double or
 * triple indirect block and the offset into the inode indirect block array.
 * Note, the logical block number of the inode single/double/triple indirect
 * block appears twice in the array, once with the offset into the i_ib and
 * once with the offset into the page itself.
 */
int
lfs_getlbns(vp, bn, ap, nump)
	struct vnode *vp;
	register daddr_t bn;
	INDIR *ap;
	int *nump;
{
	struct lfs *fs;
	long metalbn, realbn;
D 52
	int j, off, sh;
E 52
I 52
	int j, numlevels, off, sh;
E 52

D 57
#ifdef VERBOSE
	printf("lfs_getlbns: bn %d, inode %d\n", bn, VTOI(vp)->i_number);
#endif
E 57
D 52
	*nump = 0;
E 52
I 52
	if (nump)
		*nump = 0;
	numlevels = 0;
E 52
	realbn = bn;
	if ((long)bn < 0)
		bn = -(long)bn;

	/* The first NDADDR blocks are direct blocks. */
	if (bn < NDADDR)
D 36
		return(0);
E 36
I 36
		return (0);
E 36

	/* 
	 * Determine the number of levels of indirection.  After this loop
	 * is done, sh indicates the number of data blocks possible at the
	 * given level of indirection, and NIADDR - j is the number of levels
	 * of indirection needed to locate the requested block.
	 */
	bn -= NDADDR;
	fs = VTOI(vp)->i_lfs;
	sh = 1;
	for (j = NIADDR; j > 0; j--) {
		sh *= NINDIR(fs);
		if (bn < sh)
			break;
		bn -= sh;
	}
	if (j == 0)
		return (EFBIG);

	/* Calculate the address of the first meta-block. */
	if (realbn >= 0)
		metalbn = -(realbn - bn + NIADDR - j);
	else
		metalbn = -(-realbn - bn + NIADDR - j);

	/* 
	 * At each iteration, off is the offset into the bap array which is
	 * an array of disk addresses at the current level of indirection.
	 * The logical block number and the offset in that block are stored
	 * into the argument array.
	 */
D 52
	++*nump;
E 52
I 52
	++numlevels;
E 52
	ap->in_lbn = metalbn;
	ap->in_off = off = NIADDR - j;
	ap++;
	for (; j <= NIADDR; j++) {
		/* If searching for a meta-data block, quit when found. */
		if (metalbn == realbn)
			break;

		sh /= NINDIR(fs);
		off = (bn / sh) % NINDIR(fs);

D 52
		++*nump;
E 52
I 52
		++numlevels;
E 52
		ap->in_lbn = metalbn;
		ap->in_off = off;
		++ap;

		metalbn -= -1 + off * sh;
	}
I 52
	if (nump)
		*nump = numlevels;
E 52
E 32
E 24
E 23
E 15
	return (0);
E 12
}
I 34

int
E 61
D 67
lfs_balloc(vp, iosize, lbn, bpp)
E 67
I 67
lfs_balloc(vp, offset, iosize, lbn, bpp)
E 67
	struct vnode *vp;
I 67
	int offset;
E 67
	u_long iosize;
D 66
	daddr_t lbn;
E 66
I 66
	ufs_daddr_t lbn;
E 66
	struct buf **bpp;
{
I 49
D 52
	USES_VOP_BMAP;
E 52
E 49
D 61
	struct buf *bp;
E 61
I 61
	struct buf *ibp, *bp;
E 61
	struct inode *ip;
	struct lfs *fs;
I 61
	struct indir indirs[NIADDR+2];
E 61
D 66
	daddr_t daddr;
E 66
I 66
D 67
	ufs_daddr_t daddr;
E 66
D 58
	int error, newblock;
E 58
I 58
D 59
	int error;
E 59
I 59
D 61
	int bb, error;
E 61
I 61
	int bb, error, i, num;
E 67
I 67
D 68
	ufs_daddr_t	lastblock;
E 68
I 68
	ufs_daddr_t	daddr, lastblock;
E 68
 	int bb;		/* number of disk blocks in a block disk blocks */
 	int error, frags, i, nsize, osize, num;
E 67
E 61
E 59
E 58

	ip = VTOI(vp);
	fs = ip->i_lfs;

	/* 
	 * Three cases: it's a block beyond the end of file, it's a block in
	 * the file that may or may not have been assigned a disk address or
	 * we're writing an entire block.  Note, if the daddr is unassigned,
D 61
	 * the block might still have existed in the cache.  If it did, make
	 * sure we don't count it as a new block or zero out its contents.
I 58
	 * Note that we always call bmap, even if it's a new block beyond
	 * the end of file. The reason is so that we can allocate any new
	 * indirect blocks that are necessary.
E 61
I 61
	 * the block might still have existed in the cache (if it was read
	 * or written earlier).  If it did, make sure we don't count it as a
	 * new block or zero out its contents.  If it did not, make sure
	 * we allocate any necessary indirect blocks.
I 67
	 * If we are writing a block beyond the end of the file, we need to
	 * check if the old last block was a fragment.  If it was, we need
	 * to rewrite it.
E 67
E 61
E 58
	 */
D 58
	newblock = ip->i_size <= lbn << fs->lfs_bshift;
D 49
	if (!newblock && (error = lfs_bmap(vp, lbn, NULL, &daddr)))
E 49
I 49
	if (!newblock && (error = VOP_BMAP(vp, lbn, NULL, &daddr)))
E 58
I 58

	*bpp = NULL;
D 61
	if (error = VOP_BMAP(vp, lbn, NULL, &daddr))
E 61
I 61
	if (error = ufs_bmaparray(vp, lbn, &daddr, &indirs[0], &num, NULL ))
E 61
E 58
E 49
D 36
		return(error);
E 36
I 36
		return (error);
E 36

D 35
	if (newblock || daddr == LFS_UNUSED_DADDR || iosize == fs->lfs_bsize) {
E 35
I 35
D 58
	if (newblock || daddr == UNASSIGNED || iosize == fs->lfs_bsize) {
E 58
I 58
D 61
	if (daddr == UNASSIGNED || iosize == fs->lfs_bsize) {
E 58
E 35
		*bpp = bp = getblk(vp, lbn, fs->lfs_bsize);
D 58
		if (newblock ||
D 35
		    daddr == LFS_UNUSED_DADDR && !(bp->b_flags & B_CACHE)) {
E 35
I 35
		    daddr == UNASSIGNED && !(bp->b_flags & B_CACHE)) {
E 58
I 58
		if (daddr == UNASSIGNED && !(bp->b_flags & B_CACHE)) {
E 58
E 35
D 55
			++ip->i_blocks;
E 55
I 55
D 59
			ip->i_blocks += btodb(fs->lfs_bsize);
I 56
			fs->lfs_bfree -= btodb(fs->lfs_bsize);
E 59
I 59
			bb = fsbtodb(fs, 1);
			if (!ISSPACE_XXX(fs, bb)) {
I 60
				/* Pretend we never allocated the buffer */
E 61
I 61
D 64
	*bpp = bp = getblk(vp, lbn, fs->lfs_bsize);
E 64
I 64
D 67
	*bpp = bp = getblk(vp, lbn, fs->lfs_bsize, 0, 0);
E 67
I 67
	/* Check for block beyond end of file and fragment extension needed. */
	lastblock = lblkno(fs, ip->i_size);
	if (lastblock < NDADDR && lastblock < lbn) {
		osize = blksize(fs, ip, lastblock);
		if (osize < fs->lfs_bsize && osize > 0) {
			if (error = lfs_fragextend(vp, osize, fs->lfs_bsize,
			    lastblock, &bp))
				return(error);
			ip->i_size = (lastblock + 1) * fs->lfs_bsize;
			vnode_pager_setsize(vp, (u_long)ip->i_size);
			ip->i_flag |= IN_CHANGE | IN_UPDATE;
			VOP_BWRITE(bp);
		}
	}

E 67
E 64
	bb = VFSTOUFS(vp->v_mount)->um_seqinc;
	if (daddr == UNASSIGNED)
		/* May need to allocate indirect blocks */
		for (i = 1; i < num; ++i)
			if (!indirs[i].in_exists) {
D 67
				ibp =
D 64
				    getblk(vp, indirs[i].in_lbn, fs->lfs_bsize);
E 64
I 64
				    getblk(vp, indirs[i].in_lbn, fs->lfs_bsize,
					0, 0);
E 64
				if (!(ibp->b_flags & (B_DONE | B_DELWRI))) {
					if (!ISSPACE(fs, bb, curproc->p_ucred)){
						ibp->b_flags |= B_INVAL;
						brelse(ibp);
						error = ENOSPC;
					} else {
						ip->i_blocks += bb;
						ip->i_lfs->lfs_bfree -= bb;
						clrbuf(ibp);
						error = VOP_BWRITE(ibp);
					}
				} else
E 67
I 67
				ibp = getblk(vp, indirs[i].in_lbn, fs->lfs_bsize,
				    0, 0);
				if ((ibp->b_flags & (B_DONE | B_DELWRI))) 
E 67
					panic ("Indirect block should not exist");
I 67

				if (!ISSPACE(fs, bb, curproc->p_ucred)){
					ibp->b_flags |= B_INVAL;
					brelse(ibp);
					return(ENOSPC);
				} else {
					ip->i_blocks += bb;
					ip->i_lfs->lfs_bfree -= bb;
					clrbuf(ibp);
					if(error = VOP_BWRITE(ibp))
						return(error);
				}
E 67
			}
D 67
	if (error) {
		if (bp)
			brelse(bp);
		return(error);
E 67
I 67

	/*
	 * If the block we are writing is a direct block, it's the last
	 * block in the file, and offset + iosize is less than a full
	 * block, we can write one or more fragments.  There are two cases:
	 * the block is brand new and we should allocate it the correct
	 * size or it already exists and contains some fragments and
	 * may need to extend it.
	 */
	if (lbn < NDADDR && lblkno(fs, ip->i_size) == lbn) {
		nsize = fragroundup(fs, offset + iosize);
		frags = numfrags(fs, nsize);
		bb = fragstodb(fs, frags);
		if (lblktosize(fs, lbn) == ip->i_size)
			/* Brand new block or fragment */
			*bpp = bp = getblk(vp, lbn, nsize, 0, 0);
		else {
			/* Extend existing block */
			if (error = lfs_fragextend(vp, (int)blksize(fs, ip, lbn), 
			    nsize, lbn, &bp))
				return(error);
			*bpp = bp;
		}
	} else {
		/*
		 * Get the existing block from the cache either because the
		 * block is 1) not a direct block or because it's not the last
		 * block in the file.
		 */
		frags = dbtofrags(fs, bb);
		*bpp = bp = getblk(vp, lbn, blksize(fs, ip, lbn), 0, 0);
E 67
	}

D 67

	/* Now, we may need to allocate the data block */
E 67
I 67
	/* 
	 * The block we are writing may be a brand new block
	 * in which case we need to do accounting (i.e. check
	 * for free space and update the inode number of blocks.
	 */
E 67
	if (!(bp->b_flags & (B_CACHE | B_DONE | B_DELWRI))) {
		if (daddr == UNASSIGNED) 
			if (!ISSPACE(fs, bb, curproc->p_ucred)) {
E 61
E 60
				bp->b_flags |= B_INVAL;
D 61
				*bpp = NULL;
E 61
				brelse(bp);
D 61
				return (ENOSPC);
E 61
I 61
				return(ENOSPC);
			} else {
				ip->i_blocks += bb;
				ip->i_lfs->lfs_bfree -= bb;
				if (iosize != fs->lfs_bsize)
					clrbuf(bp);
E 61
			}
D 61
			ip->i_blocks += bb;
			fs->lfs_bfree -= bb;
E 59
E 56
E 55
			if (iosize != fs->lfs_bsize)
				clrbuf(bp);
E 61
I 61
		else if (iosize == fs->lfs_bsize)
D 67
			bp->b_blkno = daddr;		/* Skip the I/O */
E 67
I 67
			/* Optimization: I/O is unnecessary. */
			bp->b_blkno = daddr;
E 67
		else  {
I 67
			/*
			 * We need to read the block to preserve the
			 * existing bytes.
			 */
E 67
			bp->b_blkno = daddr;
I 62
D 63
			bp->b_flags != B_READ;
E 63
I 63
			bp->b_flags |= B_READ;
E 63
E 62
			VOP_STRATEGY(bp);
I 62
			return(biowait(bp));
E 62
E 61
		}
D 36
		return(0);
E 36
I 36
D 61
		return (0);
E 61
E 36
	}
D 36
	return(bread(vp, lbn, fs->lfs_bsize, NOCRED, bpp));
E 36
I 36
D 61
	return (bread(vp, lbn, fs->lfs_bsize, NOCRED, bpp));
E 61
I 61
D 67
	return (error);
E 67
I 67
	return (0);
}

lfs_fragextend(vp, osize, nsize, lbn, bpp)
	struct vnode *vp;
	int osize;
	int nsize;
	daddr_t lbn;
	struct buf **bpp;
{
	struct inode *ip;
	struct lfs *fs;
	long bb;
	int error;

	ip = VTOI(vp);
	fs = ip->i_lfs;
	bb = (long)fragstodb(fs, numfrags(fs, nsize - osize));
	if (!ISSPACE(fs, bb, curproc->p_ucred)) {
		return(ENOSPC);
	}

	if (error = bread(vp, lbn, osize, NOCRED, bpp)) {
		brelse(*bpp);
		return(error);
	}
#ifdef QUOTA
	if (error = chkdq(ip, bb, curproc->p_ucred, 0)) {
		brelse(*bpp);
		return (error);
	}
#endif
	ip->i_blocks += bb;
	ip->i_flag |= IN_CHANGE | IN_UPDATE;
	fs->lfs_bfree -= fragstodb(fs, numfrags(fs, (nsize - osize)));
	allocbuf(*bpp, nsize);
	bzero((char *)((*bpp)->b_data) + osize, (u_int)(nsize - osize));
	return(0);
E 67
E 61
E 36
D 59

E 59
}
E 34
I 25
D 27
#endif /* LOGFS */
E 27
E 25
E 1
