h44012
s 00002/00002/00109
d D 8.1 93/06/11 16:27:25 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00110
d D 7.9 92/12/10 14:20:47 margo 13 12
c Use di_inumber, not di_inum to get on-disk inode number.
e
s 00010/00005/00101
d D 7.8 92/07/23 16:25:46 bostic 12 11
c Print out new fields in superblock.
e
s 00001/00001/00105
d D 7.7 92/07/05 14:36:37 bostic 11 10
c needs <sys/mount.h>
e
s 00000/00074/00106
d D 7.6 92/06/23 00:06:22 bostic 10 9
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00001/00001/00179
d D 7.5 92/04/08 15:08:01 bostic 9 8
c remove the rest of the typedef's
e
s 00003/00003/00177
d D 7.4 91/12/31 14:19:46 bostic 8 7
c fix printf types for disk inode dump routien
e
s 00001/00001/00179
d D 7.3 91/12/19 12:58:28 mckusick 7 6
c must cast di_size passed to printf
e
s 00004/00004/00176
d D 7.2 91/12/06 16:42:49 bostic 6 5
c LFS version 2; minor cleanups, nothing important
e
s 00006/00006/00174
d D 7.1 91/11/01 17:42:14 bostic 5 4
c don't typedef struct lfs
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00080/00019/00100
d D 5.4 91/11/01 17:30:09 bostic 4 3
c checkpoint before integration, clean up printfs, but leave
c debugging routines
e
s 00002/00000/00117
d D 5.3 91/10/09 11:20:15 bostic 3 2
c lint
e
s 00011/00000/00106
d D 5.2 91/10/02 09:00:27 bostic 2 1
c checkpoint
e
s 00106/00000/00000
d D 5.1 91/09/25 14:33:58 bostic 1 0
c date and time created 91/09/25 14:33:58 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989, 1991 The Regents of the University of California.
E 5
I 5
D 14
 * Copyright (c) 1991 The Regents of the University of California.
E 5
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 4
#ifdef LOGFS
E 2
#include "param.h"
#include "namei.h"
#include "vnode.h"
#include "../ufs/quota.h"
#include "../ufs/inode.h"
#include "lfs.h"
E 4
I 4
#ifdef DEBUG
#include <sys/param.h>
#include <sys/namei.h>
#include <sys/vnode.h>
I 11
#include <sys/mount.h>
E 11
E 4

I 4
D 5
#include <ufs/quota.h>
#include <ufs/inode.h>
E 5
I 5
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 5
D 11

E 11
D 5
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 5
I 5
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 5

E 4
void 
D 4
dump_super(lfsp)
E 4
I 4
lfs_dump_super(lfsp)
E 4
D 5
	LFS *lfsp;
E 5
I 5
	struct lfs *lfsp;
E 5
{
	int i;

	(void)printf("%s%lx\t%s%lx\t%s%d\t%s%d\n",
		"magic    ", lfsp->lfs_magic,
		"version  ", lfsp->lfs_version,
		"size     ", lfsp->lfs_size,
		"ssize    ", lfsp->lfs_ssize);
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
		"dsize    ", lfsp->lfs_dsize,
		"bsize    ", lfsp->lfs_bsize,
		"fsize    ", lfsp->lfs_fsize,
		"frag     ", lfsp->lfs_frag);

	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
		"minfree  ", lfsp->lfs_minfree,
		"inopb    ", lfsp->lfs_inopb,
		"ifpb     ", lfsp->lfs_ifpb,
		"nindir   ", lfsp->lfs_nindir);

D 12
	(void)printf("%s%d\t%s%d\t%s%d\n",
E 12
I 12
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
E 12
		"nseg     ", lfsp->lfs_nseg,
		"nspf     ", lfsp->lfs_nspf,
I 12
		"cleansz  ", lfsp->lfs_cleansz,
E 12
		"segtabsz ", lfsp->lfs_segtabsz);

	(void)printf("%s%lx\t%s%d\t%s%lx\t%s%d\n",
		"segmask  ", lfsp->lfs_segmask,
		"segshift ", lfsp->lfs_segshift,
		"bmask    ", lfsp->lfs_bmask,
		"bshift   ", lfsp->lfs_bshift);

	(void)printf("%s%lx\t%s%d\t%s%lx\t%s%d\n",
		"ffmask   ", lfsp->lfs_ffmask,
		"ffshift  ", lfsp->lfs_ffshift,
		"fbmask   ", lfsp->lfs_fbmask,
		"fbshift  ", lfsp->lfs_fbshift);

D 12
	(void)printf("%s%d\t%s%lx\n", 
E 12
I 12
	(void)printf("%s%d\t%s%d\t%s%lx\t%s%qx\n", 
		"sushift  ", lfsp->lfs_sushift,
E 12
		"fsbtodb  ", lfsp->lfs_fsbtodb,
D 12
		"cksum    ", lfsp->lfs_cksum);
E 12
I 12
		"cksum    ", lfsp->lfs_cksum,
		"maxfilesize ", lfsp->lfs_maxfilesize);
E 12

	(void)printf("Superblock disk addresses:");
	for (i = 0; i < LFS_MAXNUMSB; i++)
		(void)printf(" %lx", lfsp->lfs_sboffs[i]);
	(void)printf("\n");

	(void)printf("Checkpoint Info\n");
	(void)printf("%s%d\t%s%lx\t%s%d\n",
		"free     ", lfsp->lfs_free,
		"idaddr   ", lfsp->lfs_idaddr,
		"ifile    ", lfsp->lfs_ifile);
D 12
	(void)printf("%s%lx\t%s%d\t%s%lx\t%s%lx\n",
E 12
I 12
	(void)printf("%s%lx\t%s%d\t%s%lx\t%s%lx\t%s%lx\t%s%lx\n",
E 12
		"bfree    ", lfsp->lfs_bfree,
		"nfiles   ", lfsp->lfs_nfiles,
		"lastseg  ", lfsp->lfs_lastseg,
D 12
		"nextseg  ", lfsp->lfs_nextseg);
E 12
I 12
		"nextseg  ", lfsp->lfs_nextseg,
		"curseg   ", lfsp->lfs_curseg,
		"offset   ", lfsp->lfs_offset);
E 12
	(void)printf("tstamp   %lx\n", lfsp->lfs_tstamp);
}

I 3
void
E 3
D 4
dump_dinode(dip)
E 4
I 4
lfs_dump_dinode(dip)
E 4
D 9
	DINODE *dip;
E 9
I 9
	struct dinode *dip;
E 9
{
	int i;

D 8
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\t%s%d\n",
E 8
I 8
	(void)printf("%s%u\t%s%d\t%s%u\t%s%u\t%s%lu\n",
E 8
		"mode  ", dip->di_mode,
		"nlink ", dip->di_nlink,
		"uid   ", dip->di_uid,
		"gid   ", dip->di_gid,
D 7
		"size  ", dip->di_size);
E 7
I 7
D 8
		"size  ", (u_long)dip->di_size);
E 7
	(void)printf("inum  %d\n", dip->di_inum);
E 8
I 8
		"size  ", dip->di_size);
D 13
	(void)printf("inum  %ld\n", dip->di_inum);
E 13
I 13
	(void)printf("inum  %ld\n", dip->di_inumber);
E 13
E 8
	(void)printf("Direct Addresses\n");
	for (i = 0; i < NDADDR; i++) {
		(void)printf("\t%lx", dip->di_db[i]);
		if ((i % 6) == 5)
			(void)printf("\n");
	}
	for (i = 0; i < NIADDR; i++)
		(void)printf("\t%lx", dip->di_ib[i]);
	(void)printf("\n");
}
D 10

I 3
D 4
void
E 3
lfs_print_inumber(vp)
	VNODE *vp;
E 4
I 4
/* XXX TEMPORARY */
#include <sys/buf.h>
#include <sys/mount.h>
int
lfs_umountdebug(mp)
	struct mount *mp;
E 4
{
D 4
	(void)printf("%d\n", VTOI(vp)->i_number);
E 4
I 4
	struct vnode *vp;
	int dirty;

	dirty = 0;
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
		panic("umountdebug: not busy");
loop:
	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
		if (vget(vp))
			goto loop;
		dirty += lfs_vinvalbuf(vp);
		vput(vp);
		if (vp->v_mount != mp)
			goto loop;
	}
	return (dirty);
E 4
}
I 2

D 4
void
lfs_spin()
E 4
I 4
int
lfs_vinvalbuf(vp)
	register struct vnode *vp;
E 4
{
D 4
	u_long i, j;
E 4
I 4
	register struct buf *bp;
	struct buf *nbp, *blist;
	int s, dirty = 0;
E 4

D 4
	for (i = 0; i < 10; ++i)
		for (j = 0; j < 1000000; ++j);
E 4
I 4
	for (;;) {
		if (blist = vp->v_dirtyblkhd)
			/* void */;
		else if (blist = vp->v_cleanblkhd)
			/* void */;
		else
			break;
		for (bp = blist; bp; bp = nbp) {
D 6
printf("lfs_vinvalbuf: ino %d, lblkno %d, blkno %lx flags %xl\n",
VTOI(vp)->i_number, bp->b_lblkno, bp->b_blkno, bp->b_flags);
E 6
I 6
	printf("lfs_vinvalbuf: ino %d, lblkno %d, blkno %lx flags %xl\n",
	     VTOI(vp)->i_number, bp->b_lblkno, bp->b_blkno, bp->b_flags);
E 6
			nbp = bp->b_blockf;
			s = splbio();
			if (bp->b_flags & B_BUSY) {
D 6
printf("lfs_vinvalbuf: buffer busy, would normally sleep\n");
E 6
I 6
	printf("lfs_vinvalbuf: buffer busy, would normally sleep\n");
E 6
/*
				bp->b_flags |= B_WANTED;
				sleep((caddr_t)bp, PRIBIO + 1);
*/
				splx(s);
				break;
			}
			bremfree(bp);
			bp->b_flags |= B_BUSY;
			splx(s);
			if (bp->b_flags & B_DELWRI) {
				dirty++;			/* XXX */
D 6
printf("lfs_vinvalbuf: buffer dirty (DELWRI). would normally write\n");
E 6
I 6
	printf("lfs_vinvalbuf: buffer dirty (DELWRI). would normally write\n");
E 6
				break;
			}
			if (bp->b_vp != vp)
				reassignbuf(bp, bp->b_vp);
			else
				bp->b_flags |= B_INVAL;
			brelse(bp);
		}
	}
	if (vp->v_dirtyblkhd || vp->v_cleanblkhd)
		panic("lfs_vinvalbuf: flush failed");
	return (dirty);
E 4
}
E 10
D 4
#endif /* LOGFS */
E 4
I 4
#endif /* DEBUG */
E 4
E 2
E 1
