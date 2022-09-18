h24231
s 00034/00008/00325
d D 8.9 95/05/08 12:14:16 mckusick 46 45
c update from margo
e
s 00015/00015/00318
d D 8.8 95/03/21 00:27:51 mckusick 45 44
c daddr_t => ufs_daddr_t
e
s 00001/00001/00332
d D 8.7 95/01/02 23:39:52 mckusick 44 43
c quad => int64_t 
e
s 00002/00000/00331
d D 8.6 95/01/02 23:25:27 mckusick 43 42
c Pad struct lfs out to 512 bytes so we don't try to write an odd
c block size (from mycroft)
e
s 00119/00116/00212
d D 8.5 94/07/08 23:45:07 mckusick 42 41
c changes for 64-bit machines (from bostic)
e
s 00001/00000/00327
d D 8.4 94/06/15 16:29:18 mkm 41 40
c add lfs_maxsymlinklen (from mycroft)
e
s 00035/00034/00292
d D 8.3 93/09/23 16:14:04 bostic 40 39
c changes for 4.4BSD-Lite requested by USL
e
s 00006/00006/00320
d D 8.2 93/09/21 07:25:30 bostic 39 38
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00324
d D 8.1 93/06/11 16:27:07 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00006/00303
d D 7.27 92/12/10 14:16:25 margo 37 36
c add segment pointer and locking pid insuperblock.  Get rid of old 
c di_inum field (it now unions with the old gid and uid fields).  Add statistics
c structure for LFS.
e
s 00000/00006/00309
d D 7.26 92/10/08 13:42:52 margo 36 35
c Merge ffs/lfs bmap into ufs_bmap.  Move structures into ufsmount.h.
e
s 00003/00003/00312
d D 7.25 92/10/01 08:23:53 margo 35 34
c Make lfs_avail signed since it can temporarily go negative.
e
s 00001/00007/00314
d D 7.24 92/09/03 08:23:48 margo 34 33
c Remove INODE_INFOs.  Add version to BLOCK_INFOs.
e
s 00013/00002/00308
d D 7.23 92/09/02 07:57:19 margo 33 32
c Add macros to determine if there are enough free blocks for a 
c requested allocation.
e
s 00001/00000/00309
d D 7.22 92/08/25 14:31:40 bostic 32 31
c Add vnode pointer to segment structure so that updatemeta knows 
c what file to finish off when it runs out of space in a partial or segment.
e
s 00043/00009/00266
d D 7.21 92/08/21 17:20:04 bostic 31 30
c Add fields in struct lfs for available space accounting, and number of active 
c segments since last checkpoint.  Add error information for ifile panics. 
c Get rid of the macro UBWRITE and do everything in lfs_bwrite.  Add all the 
c dynamic fields to segment structure so cleaner can use it.
e
s 00002/00002/00273
d D 7.20 92/07/30 16:56:21 bostic 30 29
c Fix SEGUPD and SEGTABSZ macros.
e
s 00001/00001/00274
d D 7.19 92/07/24 14:19:07 bostic 29 28
c Logical block number in BLOCK_INFO should be daddr_t not off_t.
e
s 00010/00006/00265
d D 7.18 92/07/23 16:18:41 bostic 28 27
c Add number of summary blocks and number of inode blocks to the 
c segment usage table for free space accounting.  Do block free accouting 
c in terms of disk sectors rather than file system blocks.  New segment usage 
c table size is power of 2, so do fast arithmetic.
e
s 00016/00000/00255
d D 7.17 92/07/22 17:45:02 bostic 27 26
c add LFS_SYNC, so that "synchronous" operations don't cause deadlock
e
s 00001/00000/00254
d D 7.16 92/07/20 16:17:26 bostic 26 25
c add lfs_maxfilesize
e
s 00002/00006/00252
d D 7.15 92/07/05 14:33:46 bostic 25 24
c minor cleanups, add seglock to synchronize segment writer;
c Kirk deleted USES_VOP_whatever.
e
s 00011/00002/00247
d D 7.14 92/06/23 00:06:17 bostic 24 23
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00002/00001/00247
d D 7.13 92/05/14 14:05:05 heideman 23 21
c lfs_ubwrite change to for new vnode interface
e
s 00002/00001/00247
d R 7.13 92/05/14 12:44:04 heideman 22 21
c lfs_ubwrite fixed
e
s 00001/00009/00247
d D 7.12 92/04/08 15:07:58 bostic 21 20
c remove the rest of the typedef's
e
s 00002/00002/00254
d D 7.11 92/03/18 12:59:55 staelin 20 19
c typo
e
s 00001/00001/00255
d D 7.10 92/03/18 11:06:24 bostic 19 18
c typo
e
s 00001/00001/00255
d D 7.9 92/01/08 17:55:56 bostic 18 17
c put in a real magic number
e
s 00017/00022/00239
d D 7.8 91/12/31 14:05:45 bostic 17 16
c minor reorg; delete if_st_atime field, not used; move datosn and sntoda
c into lfs.h from lfs_segment.c, used by lfs_truncate code; rework IFILE macros
e
s 00020/00006/00241
d D 7.7 91/12/14 18:47:19 bostic 16 15
c create LFS_IRELEASE/LFS_IWRITE macros so ifile times get updated
e
s 00000/00002/00247
d D 7.6 91/12/14 16:51:40 bostic 15 14
c CLEANINFO didn't need last_seg, last_time for now
e
s 00011/00004/00238
d D 7.5 91/12/14 16:22:16 bostic 14 13
c add LFS_CLEANERINFO macro for access to cleaner ifile block
e
s 00004/00002/00238
d D 7.4 91/12/13 12:40:30 bostic 13 12
c add SEGUSE flags
e
s 00066/00047/00174
d D 7.3 91/12/06 16:36:26 bostic 12 11
c LFS version 2; describe partial segments, new framing structure, add
c cleaner system calls
e
s 00002/00004/00219
d D 7.2 91/11/05 12:30:28 bostic 11 10
c ROOTINO is in common code
e
s 00000/00001/00223
d D 7.1 91/11/01 17:34:56 bostic 10 9
c don't typedef struct lfs for now
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00009/00000/00215
d D 5.8 91/11/01 17:25:04 bostic 9 8
c move LFS_IENTRY into lfs.h; checkpoint before integration
e
s 00013/00010/00202
d D 5.7 91/10/09 11:25:08 bostic 8 7
c add UNASSIGNED for nonexistent disk address in bmap;
c satosn -> datosn, sntosa -> sntoda
e
s 00021/00021/00191
d D 5.6 91/10/03 10:48:50 bostic 7 6
c prettiness patrol
e
s 00003/00001/00209
d D 5.5 91/10/02 09:00:21 bostic 6 5
c checkpoint
e
s 00063/00018/00147
d D 5.4 91/09/25 14:30:01 bostic 5 4
c checkpoint, but not because it's working
e
s 00059/00084/00106
d D 5.3 91/09/20 13:47:28 bostic 4 3
c checkpoint before lfs_iupdat -> ITIMES; reads almost work...
e
s 00033/00009/00157
d D 5.2 91/09/18 10:07:03 bostic 3 1
c fold Margo's and mine together
e
s 00033/00009/00157
d R 5.2 91/09/18 10:06:24 bostic 2 1
c fold Margo's and mine together
e
s 00166/00000/00000
d D 5.1 91/09/18 10:05:41 bostic 1 0
c date and time created 91/09/18 10:05:41 by bostic
e
u
U
t
T
I 1
/*-
D 38
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 5
D 21
typedef struct buf	BUF;
typedef struct dinode	DINODE;
typedef struct inode	INODE;
typedef struct mount	MOUNT;
typedef struct ucred	UCRED;
typedef struct ufsmount	UFSMOUNT;
typedef struct vnode	VNODE;

E 21
E 5
D 3
#define	MAXMNTLEN	512		/* XXX move from fs.h to mount.h */
#define	LFSBLKSIZE	(4*1024)
E 3
I 3
#define	LFS_LABELPAD	8192		/* LFS label size */
#define	LFS_SBPAD	8192		/* LFS superblock size */
D 25
#define MAXMNTLEN	512		/* XXX move from fs.h to mount.h */
E 25
D 4
#define	LFS_BLKSIZE	4096		/* LFS block size */
E 4
E 3

I 27
/*
 * XXX
 * This is a kluge and NEEDS to go away.
 *
 * Right now, ufs code handles most of the calls for directory operations
 * such as create, mkdir, link, etc.  As a result VOP_UPDATE is being
 * called with waitfor set (since ffs does these things synchronously).
 * Since LFS does not want to do these synchronously, we treat the last
 * argument to lfs_update as a set of flags.  If LFS_SYNC is set, then
 * the update should be synchronous, if not, do it asynchronously.
 * Unfortunately, this means that LFS won't work with NFS yet because
 * NFS goes through paths that will make normal calls to ufs which will
 * call lfs with a last argument of 1.
 */
#define	LFS_SYNC	0x02

E 27
D 4
/* On-disk super block. */
typedef struct lfs_super {
D 3
#define	LFS_MAGIC	0xabababab
E 3
I 3
#define	LFS_MAGIC	0xdeadbeef
E 4
I 4
/* On-disk and in-memory checkpoint segment usage structure. */
D 5
typedef struct segusage {
E 5
I 5
typedef struct segusage SEGUSE;
struct segusage {
E 5
D 42
	u_long	su_nbytes;		/* number of live bytes */
D 8
	u_long	su_lastmod;		/* last modified timestamp */
E 8
I 8
	u_long	su_lastmod;		/* SEGUSE last modified timestamp */
I 28
	u_short	su_nsums;		/* number of summaries in segment */
	u_short	su_ninos;		/* number of inode blocks in seg */
E 28
E 8
D 5
#define	SEGUSE_DIRTY			0x1
E 5
I 5
D 13
#define	SEGUSE_DIRTY	0x1		/* XXX fill in comment */
E 13
I 13
#define	SEGUSE_ACTIVE		0x1	/* segment is currently being written */
#define	SEGUSE_DIRTY		0x2	/* segment has data in it */
#define	SEGUSE_SUPERBLOCK	0x4	/* segment contains a superblock */
I 24
D 28
#define	SEGUSE_LIVELOG		0x8	/* segment has not been checkpointed */
E 28
E 24
E 13
E 5
	u_long	su_flags;
E 42
I 42
	u_int32_t su_nbytes;		/* number of live bytes */
	u_int32_t su_lastmod;		/* SEGUSE last modified timestamp */
	u_int16_t su_nsums;		/* number of summaries in segment */
	u_int16_t su_ninos;		/* number of inode blocks in seg */

#define	SEGUSE_ACTIVE		0x01	/* segment is currently being written */
#define	SEGUSE_DIRTY		0x02	/* segment has data in it */
#define	SEGUSE_SUPERBLOCK	0x04	/* segment contains a superblock */
	u_int32_t su_flags;
E 42
D 5
} SEGUSE;
E 5
I 5
};
E 5

I 28
D 30
#define	SEGUPB(fs)	(1 << (fs)->lfs_sushift);
E 30
I 30
#define	SEGUPB(fs)	(1 << (fs)->lfs_sushift)
E 30
E 28
I 12
D 40
#define	SEGTABSIZE_SU(fs) \
E 40
I 40
#define	SEGTABSIZE_SU(fs)						\
E 40
D 28
	(((fs)->lfs_nseg * sizeof(SEGUSE) + \
	((fs)->lfs_bsize - 1)) >> (fs)->lfs_bshift)
E 28
I 28
D 30
	((fs)->lfs_nseg >> ((fs)->lfs_bshift - (fs)->lfs_sushift))
E 30
I 30
	(((fs)->lfs_nseg + SEGUPB(fs) - 1) >> (fs)->lfs_sushift)
E 30
E 28

E 12
I 5
/* On-disk file information.  One per file with data blocks in the segment. */
typedef struct finfo FINFO;
struct finfo {
D 42
	u_long	fi_nblocks;		/* number of blocks */
	u_long	fi_version;		/* version number */
D 6
	ino_t	fi_ino;			/* inode number */
E 6
I 6
	u_long	fi_ino;			/* inode number */
E 6
	long	fi_blocks[1];		/* array of logical block numbers */
E 42
I 42
	u_int32_t fi_nblocks;		/* number of blocks */
	u_int32_t fi_version;		/* version number */
	u_int32_t fi_ino;		/* inode number */
I 46
	u_int32_t fi_lastlength;	/* length of last block in array */
E 46
D 45
	daddr_t	  fi_blocks[1];		/* array of logical block numbers */
E 45
I 45
	ufs_daddr_t	  fi_blocks[1];	/* array of logical block numbers */
E 45
E 42
};

D 12
/* In-memory description of a segment about to be written */
typedef struct segment SEGMENT;
struct segment {
D 7
	SEGMENT	*nextp;			/* Links segments together */
	BUF	**bpp;			/* Pointer to buffer array */
	BUF	**cbpp;			/* Pointer to next available bp */
I 6
	BUF	*ibp;			/* Buffer pointer to inode page */
	BUF	*sbp;			/* Segment summary buffer pointer */
E 6
	void	*segsum;		/* Segment Summary info */
	u_long	sum_bytes_left;		/* Bytes left in summary */
	u_long	seg_bytes_left;		/* Bytes left in segment */
	daddr_t	saddr;			/* Current disk address */
	daddr_t	sum_addr;		/* Address of current summary */
	u_long	ninodes;		/* Number of inodes in this segment */
	u_long	sum_num;		/* Number of current summary block */
	u_long	seg_number;		/* Number of this segment */
	FINFO	*fip;			/* Current fileinfo pointer */
E 7
I 7
	SEGMENT	*nextp;			/* links segments together */
	BUF	**bpp;			/* pointer to buffer array */
	BUF	**cbpp;			/* pointer to next available bp */
	BUF	*ibp;			/* buffer pointer to inode page */
	BUF	*sbp;			/* segment summary buffer pointer */
	void	*segsum;		/* segment Summary info */
D 8
	u_long	sum_bytes_left;		/* bytes left in summary */
E 8
	u_long	seg_bytes_left;		/* bytes left in segment */
I 8
	u_long	sum_bytes_left;		/* bytes left in summary block */
E 8
	daddr_t	saddr;			/* current disk address */
	daddr_t	sum_addr;		/* address of current summary */
	u_long	ninodes;		/* number of inodes in this segment */
D 8
	u_long	sum_num;		/* number of current summary block */
E 8
I 8
	u_long	nsums;			/* number of SEGSUMs in this segment */
E 8
	u_long	seg_number;		/* number of this segment */
	FINFO	*fip;			/* current fileinfo pointer */
E 7
};

E 12
E 5
/* On-disk and in-memory super block. */
D 5
typedef struct lfs {
E 5
I 5
D 10
typedef struct lfs LFS;
E 10
struct lfs {
E 5
D 18
#define	LFS_MAGIC	0xbedead
E 18
I 18
#define	LFS_MAGIC	0x070162
E 18
E 4
E 3
D 42
	u_long	lfs_magic;		/* magic number */
E 42
I 42
	u_int32_t lfs_magic;		/* magic number */
E 42
I 3
#define	LFS_VERSION	1
E 3
D 42
	u_long	lfs_version;		/* version number */
E 42
I 42
	u_int32_t lfs_version;		/* version number */
E 42

D 42
	u_long	lfs_size;		/* number of blocks in fs */
	u_long	lfs_ssize;		/* number of blocks per segment */
D 33
	u_long	lfs_dsize;		/* number of data blocks in fs */
	u_long	lfs_bsize;		/* size of basic blocks in fs */
E 33
I 33
	u_long	lfs_dsize;		/* number of disk blocks in fs */
	u_long	lfs_bsize;		/* file system block size */
E 33
	u_long	lfs_fsize;		/* size of frag blocks in fs */
	u_long	lfs_frag;		/* number of frags in a block in fs */
E 42
I 42
	u_int32_t lfs_size;		/* number of blocks in fs */
	u_int32_t lfs_ssize;		/* number of blocks per segment */
	u_int32_t lfs_dsize;		/* number of disk blocks in fs */
	u_int32_t lfs_bsize;		/* file system block size */
	u_int32_t lfs_fsize;		/* size of frag blocks in fs */
	u_int32_t lfs_frag;		/* number of frags in a block in fs */
E 42
D 4
	u_long	lfs_sbsize;		/* actual size of super block */
E 4

/* Checkpoint region. */
D 42
	ino_t	lfs_free;		/* start of the free list */
I 4
D 28
	u_long	lfs_bfree;		/* number of free blocks */
E 28
I 28
	u_long	lfs_bfree;		/* number of free disk blocks */
E 28
	u_long	lfs_nfiles;		/* number of allocated inodes */
I 31
D 35
	u_long	lfs_avail;		/* blocks available for writing */
E 35
I 35
	long	lfs_avail;		/* blocks available for writing */
E 35
	u_long  lfs_uinodes;		/* inodes in cache not yet on disk */
E 31
E 4
	daddr_t	lfs_idaddr;		/* inode file disk address */
	ino_t	lfs_ifile;		/* inode file inode number */
D 7
	daddr_t	lfs_lastseg;		/* last segment written */
I 4
	daddr_t	lfs_nextseg;		/* next segment to write */
E 7
I 7
	daddr_t	lfs_lastseg;		/* address of last segment written */
	daddr_t	lfs_nextseg;		/* address of next segment to write */
I 12
D 13
	daddr_t	lfs_curseg;		/* Current segment being written */
E 13
I 13
	daddr_t	lfs_curseg;		/* current segment being written */
E 13
	daddr_t	lfs_offset;		/* offset in curseg for next partial */
I 24
	daddr_t	lfs_lastpseg;		/* address of last partial written */
E 24
E 12
E 7
E 4
	u_long	lfs_tstamp;		/* time stamp */
E 42
I 42
	ino_t	  lfs_free;		/* start of the free list */
	u_int32_t lfs_bfree;		/* number of free disk blocks */
	u_int32_t lfs_nfiles;		/* number of allocated inodes */
	int32_t	  lfs_avail;		/* blocks available for writing */
	u_int32_t lfs_uinodes;		/* inodes in cache not yet on disk */
D 45
	daddr_t	  lfs_idaddr;		/* inode file disk address */
E 45
I 45
	ufs_daddr_t lfs_idaddr;		/* inode file disk address */
E 45
	ino_t	  lfs_ifile;		/* inode file inode number */
D 45
	daddr_t	  lfs_lastseg;		/* address of last segment written */
	daddr_t	  lfs_nextseg;		/* address of next segment to write */
	daddr_t	  lfs_curseg;		/* current segment being written */
	daddr_t	  lfs_offset;		/* offset in curseg for next partial */
	daddr_t	  lfs_lastpseg;		/* address of last partial written */
E 45
I 45
	ufs_daddr_t lfs_lastseg;	/* address of last segment written */
	ufs_daddr_t lfs_nextseg;	/* address of next segment to write */
	ufs_daddr_t lfs_curseg;		/* current segment being written */
	ufs_daddr_t lfs_offset;		/* offset in curseg for next partial */
	ufs_daddr_t lfs_lastpseg;	/* address of last partial written */
E 45
	u_int32_t lfs_tstamp;		/* time stamp */
E 42

/* These are configuration parameters. */
D 42
	u_long	lfs_minfree;		/* minimum percentage of free blocks */
E 42
I 42
	u_int32_t lfs_minfree;		/* minimum percentage of free blocks */
E 42

/* These fields can be computed from the others. */
I 26
D 42
	u_quad_t lfs_maxfilesize;	/* maximum representable file size */
E 26
I 12
	u_long	lfs_dbpseg;		/* disk blocks per segment */
E 12
	u_long	lfs_inopb;		/* inodes per block */
	u_long	lfs_ifpb;		/* IFILE entries per block */
I 12
	u_long	lfs_sepb;		/* SEGUSE entries per block */
E 12
	u_long	lfs_nindir;		/* indirect pointers per block */
	u_long	lfs_nseg;		/* number of segments */
	u_long	lfs_nspf;		/* number of sectors per fragment */
I 12
	u_long	lfs_cleansz;		/* cleaner info size in blocks */
E 12
	u_long	lfs_segtabsz;		/* segment table size in blocks */
E 42
I 42
D 44
	u_quad_t  lfs_maxfilesize;	/* maximum representable file size */
E 44
I 44
	u_int64_t lfs_maxfilesize;	/* maximum representable file size */
E 44
	u_int32_t lfs_dbpseg;		/* disk blocks per segment */
	u_int32_t lfs_inopb;		/* inodes per block */
	u_int32_t lfs_ifpb;		/* IFILE entries per block */
	u_int32_t lfs_sepb;		/* SEGUSE entries per block */
	u_int32_t lfs_nindir;		/* indirect pointers per block */
	u_int32_t lfs_nseg;		/* number of segments */
	u_int32_t lfs_nspf;		/* number of sectors per fragment */
	u_int32_t lfs_cleansz;		/* cleaner info size in blocks */
	u_int32_t lfs_segtabsz;		/* segment table size in blocks */
E 42

D 42
	u_long	lfs_segmask;		/* calculate offset within a segment */
	u_long	lfs_segshift;		/* fast mult/div for segments */
	u_long	lfs_bmask;		/* calc block offset from file offset */
	u_long	lfs_bshift;		/* calc block number from file offset */
	u_long	lfs_ffmask;		/* calc frag offset from file offset */
	u_long	lfs_ffshift;		/* fast mult/div for frag from file */
	u_long	lfs_fbmask;		/* calc frag offset from block offset */
	u_long	lfs_fbshift;		/* fast mult/div for frag from block */
	u_long	lfs_fsbtodb;		/* fsbtodb and dbtofsb shift constant */
I 28
	u_long	lfs_sushift;		/* fast mult/div for segusage table */
E 42
I 42
	u_int32_t lfs_segmask;		/* calculate offset within a segment */
	u_int32_t lfs_segshift;		/* fast mult/div for segments */
D 46
	u_int32_t lfs_bmask;		/* calc block offset from file offset */
E 46
I 46
	u_int64_t lfs_bmask;		/* calc block offset from file offset */
E 46
	u_int32_t lfs_bshift;		/* calc block number from file offset */
D 46
	u_int32_t lfs_ffmask;		/* calc frag offset from file offset */
E 46
I 46
	u_int64_t lfs_ffmask;		/* calc frag offset from file offset */
E 46
	u_int32_t lfs_ffshift;		/* fast mult/div for frag from file */
D 46
	u_int32_t lfs_fbmask;		/* calc frag offset from block offset */
E 46
I 46
	u_int64_t lfs_fbmask;		/* calc frag offset from block offset */
E 46
	u_int32_t lfs_fbshift;		/* fast mult/div for frag from block */
	u_int32_t lfs_fsbtodb;		/* fsbtodb and dbtofsb shift constant */
	u_int32_t lfs_sushift;		/* fast mult/div for segusage table */
E 42
E 28

I 42
	int32_t	  lfs_maxsymlinklen;	/* max length of an internal symlink */

E 42
D 3
#define	MAXNUMSB	10
	daddr_t	lfs_sboffs[MAXNUMSB];	/* super-block disk offsets */
E 3
I 3
D 4
#define	LFS_MAXNUMSB		10
#define	LFS_MIN_SBINTERVAL	5
	daddr_t	lfs_sboffs[LFS_MAXNUMSB];	/* super-block disk offsets */
E 3
} LFS_SUPER;
E 4
I 4
#define	LFS_MIN_SBINTERVAL	5	/* minimum superblock segment spacing */
#define	LFS_MAXNUMSB		10	/* superblock disk offsets */
D 42
	daddr_t	lfs_sboffs[LFS_MAXNUMSB];
E 42
I 42
D 45
	daddr_t	  lfs_sboffs[LFS_MAXNUMSB];
E 45
I 45
	ufs_daddr_t lfs_sboffs[LFS_MAXNUMSB];
E 45
E 42
E 4

D 4
#define	blksize(fs, ip, lbn)	LFSBLKSIZE
#define	blkoff(fs, loc)		/* calculates (loc % fs->fs_bsize) */ \
	((loc) & ~(fs)->fs_bmask)
#define	fsbtodb(fs, b)		((b) << (fs)->fs_fsbtodb)
#define	lblkno(fs, loc)		/* calculates (loc / fs->fs_bsize) */ \
	((loc) >> (fs)->fs_bshift)
#define	itoo(fs, x)		((x) % INOPB(fs))
#define	itod(fs, x)		LFS -- IMPLEMENT
E 4
I 4
D 42
/* These fields are set at mount time and are meaningless on disk. */
I 37
	struct	segment *lfs_sp;	/* current segment being written */
E 37
D 5
	struct vnode *lfs_ivnode;	/* vnode for the ifile */
E 5
I 5
D 21
	VNODE	*lfs_ivnode;		/* vnode for the ifile */
E 21
I 21
	struct	vnode *lfs_ivnode;	/* vnode for the ifile */
E 21
E 5
D 25
	SEGUSE	*lfs_segtab;		/* in-memory segment usage table */
I 5
D 12
	SEGMENT	*lfs_seglist;		/* list of segments being written */
E 12
I 12
					/* XXX NOT USED */
	void	*XXXlfs_seglist;	/* list of segments being written */
E 25
I 25
	u_long	lfs_seglock;		/* single-thread the segment writer */
I 37
	pid_t	lfs_lockpid;		/* pid of lock holder */
E 37
E 25
E 12
D 7
	u_long	lfs_iocount;		/* Number of ios pending */
E 7
I 7
	u_long	lfs_iocount;		/* number of ios pending */
I 24
	u_long	lfs_writer;		/* don't allow any dirops to start */
	u_long	lfs_dirops;		/* count of active directory ops */
	u_long	lfs_doifile;		/* Write ifile blocks on next write */
I 31
	u_long	lfs_nactive;		/* Number of segments since last ckp */
E 31
E 24
E 7
E 5
	u_char	lfs_fmod;		/* super block modified flag */
	u_char	lfs_clean;		/* file system is clean flag */
	u_char	lfs_ronly;		/* mounted read-only flag */
	u_char	lfs_flags;		/* currently unused flag */
D 25
	u_char	lfs_fsmnt[MAXMNTLEN];	/* name mounted on */
E 25
I 25
	u_char	lfs_fsmnt[MNAMELEN];	/* name mounted on */
E 25
	u_char	pad[3];			/* long-align */
E 42
I 42
/* Checksum -- last valid disk field. */
	u_int32_t lfs_cksum;		/* checksum for superblock checking */
E 42
E 4

D 4
/* In-memory super block. */
typedef struct lfs {
	struct	fs *fs_link;		/* linked list of file systems */
	struct	fs *fs_rlink;		/*     used for incore super blocks */
	time_t	fs_time;		/* last time written */

/* These fields are cleared at mount time. */
	u_char	fs_fmod;		/* super block modified flag */
	u_char	fs_clean;		/* file system is clean flag */
	u_char	fs_ronly;		/* mounted read-only flag */
	u_char	fs_flags;		/* currently unused flag */
	u_char	fs_fsmnt[MAXMNTLEN];	/* name mounted on */

/* On-disk structure. */
	LFS_SUPER fs_super;
E 4
I 4
D 42
/* Checksum; valid on disk. */
	u_long	lfs_cksum;		/* checksum for superblock checking */
I 41
	long	lfs_maxsymlinklen;	/* max length of an internal symlink */
E 42
I 42
/* These fields are set at mount time and are meaningless on disk. */
	struct segment *lfs_sp;		/* current segment being written */
	struct vnode *lfs_ivnode;	/* vnode for the ifile */
	u_long	  lfs_seglock;		/* single-thread the segment writer */
	pid_t	  lfs_lockpid;		/* pid of lock holder */
	u_long	  lfs_iocount;		/* number of ios pending */
	u_long	  lfs_writer;		/* don't allow any dirops to start */
	u_long	  lfs_dirops;		/* count of active directory ops */
	u_long	  lfs_doifile;		/* Write ifile blocks on next write */
	u_long	  lfs_nactive;		/* Number of segments since last ckp */
	int8_t	  lfs_fmod;		/* super block modified flag */
	int8_t	  lfs_clean;		/* file system is clean flag */
	int8_t	  lfs_ronly;		/* mounted read-only flag */
	int8_t	  lfs_flags;		/* currently unused flag */
	u_char	  lfs_fsmnt[MNAMELEN];	/* name mounted on */
I 43

	int32_t	  lfs_pad[40];		/* round to 512 bytes */
E 43
E 42
E 41
E 4
D 5
} LFS;
E 5
I 5
};
E 5

D 4
#define	fs_bmask	fs_super.lfs_bmask
#define	fs_bshift	fs_super.lfs_bshift
#define	fs_bsize	fs_super.lfs_bsize
#define	fs_dsize	fs_super.lfs_dsize
#define	fs_fbmask	fs_super.lfs_fbmask
#define	fs_fbshift	fs_super.lfs_fbshift
#define	fs_ffmask	fs_super.lfs_ffmask
#define	fs_ffshift	fs_super.lfs_ffshift
#define	fs_frag		fs_super.lfs_frag
#define	fs_free		fs_super.lfs_free
#define	fs_fsbtodb	fs_super.lfs_fsbtodb
#define	fs_fsize	fs_super.lfs_fsize
#define	fs_idaddr	fs_super.lfs_idaddr
#define	fs_ifile	fs_super.lfs_ifile
#define	fs_ifpb		fs_super.lfs_ifpb
#define	fs_inopb	fs_super.lfs_inopb
#define	fs_lastseg	fs_super.lfs_lastseg
#define	fs_magic	fs_super.lfs_magic
#define	fs_minfree	fs_super.lfs_minfree
#define	fs_nindir	fs_super.lfs_nindir
#define	fs_nseg		fs_super.lfs_nseg
#define	fs_nspf		fs_super.lfs_nspf
#define	fs_sboffs	fs_super.lfs_sboffs
#define	fs_sbsize	fs_super.lfs_sbsize
#define	fs_segmask	fs_super.lfs_segmask
#define	fs_segshift	fs_super.lfs_segshift
#define	fs_segtabsz	fs_super.lfs_segtabsz
#define	fs_size		fs_super.lfs_size
#define	fs_ssize	fs_super.lfs_ssize
#define	fs_tstamp	fs_super.lfs_tstamp
#define	fs_version	fs_super.lfs_version
E 4
I 4
/*
D 11
 * The root inode is the root of the file system.  Inode 0 is the out-of-band
 * inode, and inode 1 is the inode number for the ifile.  Thus the root inode
 * is 2.
E 11
I 11
D 17
 * Inode 0 is the out-of-band inode, and inode 1 is the inode number for the
 * ifile.  Thus the root inode is 2, and the lost+found inode is 3.
E 17
I 17
D 42
 * Inode 0 is the out-of-band inode number, inode 1 is the inode number for
 * the IFILE, the root inode is 2 and the lost+found inode is 3.
E 42
I 42
 * Inode 0:	out-of-band inode number
 * Inode 1:	IFILE inode number
 * Inode 2:	root inode
 * Inode 3:	lost+found inode number
E 42
E 17
E 11
 */
D 11
#define ROOTINO         ((ino_t)2)
E 11
D 17
#define	LOSTFOUNDINO	((ino_t)3)
E 17
E 4
D 42

D 3
/* Data structures in the ifile */
#define	IFILE_NUM	1		/* inode number of the ifile */
E 3
I 3
/* Fixed inode numbers. */
E 42
D 7
#define	LFS_UNUSED_INUM	0		/* Out of band inode number. */
#define	LFS_IFILE_INUM	1		/* Inode number of the ifile. */
D 4
#define	LFS_FIRST_INUM	2		/* First free inode number. */
E 4
I 4
					/* First free inode number. */
E 7
I 7
#define	LFS_UNUSED_INUM	0		/* out of band inode number */
D 17
#define	LFS_IFILE_INUM	1		/* inode number of the ifile */
					/* first free inode number */
E 7
#define	LFS_FIRST_INUM	(LOSTFOUNDINO + 1)
E 17
I 17
#define	LFS_IFILE_INUM	1		/* IFILE inode number */
#define	LOSTFOUNDINO	3		/* lost+found inode number */
#define	LFS_FIRST_INUM	4		/* first free inode number */
E 17
E 4
E 3

I 3
D 4
/* 
E 4
I 4
D 37
/*
E 4
 * Used to access the first spare of the dinode which we use to store
 * the ifile number so we can identify them
 */
#define	di_inum	di_spare[0]

E 37
E 3
D 5
typedef struct ifile {
E 5
I 5
D 8
/*
 * Logical block numbers of indirect blocks.
 */
E 8
I 8
D 12
/* Logical block numbers of indirect blocks. */
E 8
#define S_INDIR	-1
#define D_INDIR -2
#define T_INDIR -3
E 12
I 12
/* Address calculations for metadata located in the inode */
#define	S_INDIR(fs)	-NDADDR
D 20
#define	D_INDIR(fs)	(S_INDIR - NINDIR(fs) - 1)
#define	T_INDIR(fs)	(D_INDIR - NINDIR(fs) * NINDIR(fs) - 1)
E 20
I 20
#define	D_INDIR(fs)	(S_INDIR(fs) - NINDIR(fs) - 1)
#define	T_INDIR(fs)	(D_INDIR(fs) - NINDIR(fs) * NINDIR(fs) - 1)
E 20
E 12

I 12
D 36
/* Structure used to pass around logical block paths. */
typedef struct _indir {
	long	in_lbn;			/* logical block number */
	int	in_off;			/* offset in buffer */
} INDIR;

E 36
E 12
I 8
/* Unassigned disk address. */
#define	UNASSIGNED	-1

I 31
/* Unused logical block number */
#define LFS_UNUSED_LBN	-1

E 31
E 8
typedef struct ifile IFILE;
struct ifile {
E 5
D 42
	u_long	if_version;		/* inode version number */
E 42
I 42
	u_int32_t if_version;		/* inode version number */
E 42
D 4
#define	UNUSED_DADDR	0		/* out-of-band daddr */
E 4
I 4
#define	LFS_UNUSED_DADDR	0	/* out-of-band daddr */
E 4
D 42
	daddr_t	if_daddr;		/* inode disk address */
D 17
	union {
		ino_t	nextfree;	/* next-unallocated inode */
		time_t	st_atime;	/* access time */
	} __ifile_u;
D 3
#define	if_st_atime	__ifile_u.st_atime;
#define	if_nextfree	__ifile_u.nextfree;
E 3
I 3
#define	if_st_atime	__ifile_u.st_atime
#define	if_nextfree	__ifile_u.nextfree
E 17
I 17
	ino_t	if_nextfree;		/* next-unallocated inode */
E 42
I 42
D 45
	daddr_t	  if_daddr;		/* inode disk address */
E 45
I 45
	ufs_daddr_t if_daddr;		/* inode disk address */
E 45
	ino_t	  if_nextfree;		/* next-unallocated inode */
E 42
E 17
E 3
D 5
} IFILE;
E 5
I 5
};
E 5

D 12
/* Segment table size, in blocks. */
#define	SEGTABSIZE(fs) \
D 4
	(((fs)->fs_nseg * sizeof(SEGUSAGE) + \
	    ((fs)->fs_bsize - 1)) << (fs)->fs_bshift)
E 4
I 4
	(((fs)->fs_nseg * sizeof(SEGUSE) + \
	    ((fs)->fs_bsize - 1)) >> (fs)->fs_bshift)
E 12
I 12
/*
 * Cleaner information structure.  This resides in the ifile and is used
 * to pass information between the cleaner and the kernel.
 */
typedef struct _cleanerinfo {
D 42
	u_long	clean;			/* K: number of clean segments */
	u_long	dirty;			/* K: number of dirty segments */
E 42
I 42
	u_int32_t clean;		/* K: number of clean segments */
	u_int32_t dirty;		/* K: number of dirty segments */
E 42
D 15
	u_long	last_seg;		/* K: index of last seg written */
	time_t	last_time;		/* K: timestamp of last seg written */
E 15
} CLEANERINFO;
E 12
E 4

I 3
D 12
#define	SEGTABSIZE_SU(fs) \
D 4
	(((fs)->lfs_nseg * sizeof(SEGUSAGE) + \
E 4
I 4
	(((fs)->lfs_nseg * sizeof(SEGUSE) + \
E 4
	    ((fs)->lfs_bsize - 1)) >> (fs)->lfs_bshift)
E 12
I 12
D 40
#define	CLEANSIZE_SU(fs) \
E 40
I 40
#define	CLEANSIZE_SU(fs)						\
E 40
	((sizeof(CLEANERINFO) + (fs)->lfs_bsize - 1) >> (fs)->lfs_bshift)
E 12

E 3
D 4
/* In-memory and on-disk checkpoint segment usage structure. */
typedef struct segusage {
	u_long	su_nbytes;		/* number of live bytes */
	u_long	su_lastmod;		/* last modified timestamp */
I 3
#define	SEGUSAGE_DIRTY			0x1
	u_long	su_flags;
E 3
} SEGUSAGE;
I 3

E 4
/*
 * All summary blocks are the same size, so we can always read a summary
D 7
 * block easily from a segment
E 7
I 7
 * block easily from a segment.
E 7
 */
#define	LFS_SUMMARY_SIZE	512
E 3

/* On-disk segment summary information */
D 5
typedef struct segsum {
E 5
I 5
typedef struct segsum SEGSUM;
struct segsum {
E 5
I 4
D 12
	u_long	ss_cksum;		/* check sum */
E 12
I 12
D 42
	u_long	ss_sumsum;		/* check sum of summary block */
	u_long	ss_datasum;		/* check sum of data */
E 12
E 4
	daddr_t	ss_next;		/* next segment */
D 12
	daddr_t	ss_prev;		/* next segment */
	daddr_t	ss_nextsum;		/* next summary block */
E 12
	u_long	ss_create;		/* creation time stamp */
D 24
	u_long	ss_nfinfo;		/* number of file info structures */
D 4
	u_long	ss_niinfo;		/* number of inode info structures */
	u_long	ss_cksum;		/* check sum */
E 4
I 4
D 12
	u_long	ss_ninos;		/* number of inode blocks */
E 12
I 12
	u_long	ss_ninos;		/* number of inodes in summary */
E 24
I 24
	u_short	ss_nfinfo;		/* number of file info structures */
	u_short	ss_ninos;		/* number of inodes in summary */
E 42
I 42
	u_int32_t ss_sumsum;		/* check sum of summary block */
	u_int32_t ss_datasum;		/* check sum of data */
I 46
	u_int32_t ss_magic;		/* segment summary magic number */
#define SS_MAGIC	0x061561
E 46
D 45
	daddr_t	  ss_next;		/* next segment */
E 45
I 45
	ufs_daddr_t ss_next;		/* next segment */
E 45
	u_int32_t ss_create;		/* creation time stamp */
	u_int16_t ss_nfinfo;		/* number of file info structures */
	u_int16_t ss_ninos;		/* number of inodes in summary */

E 42
#define	SS_DIROP	0x01		/* segment begins a dirop */
#define	SS_CONT		0x02		/* more partials to finish this write*/
D 42
	u_short	ss_flags;		/* used for directory operations */
	u_short	ss_pad;			/* extra space */
E 42
I 42
	u_int16_t ss_flags;		/* used for directory operations */
	u_int16_t ss_pad;		/* extra space */
E 42
E 24
E 12
D 19
	/* FINFO's... */
E 19
I 19
	/* FINFO's and inode daddr's... */
E 19
E 4
D 5
} SEGSUM;
E 5
I 5
};
E 5

D 5
/* On-disk file information.  One per file with data blocks in the segment. */
typedef struct finfo {
	u_long	fi_nblocks;		/* number of blocks */
	u_long	fi_version;		/* version number */
	ino_t	fi_ino;			/* inode number */
	u_long	fi_blocks[1];		/* array of logical block numbers */
} FINFO;

E 5
D 4
/* On-disk inode information.  One per block of inodes in the segment. */
typedef struct iinfo {
	u_long	ii_ninodes;		/* number of inodes */
	ino_t	ii_inodes;		/* array of inode numbers */
} IINFO;
E 4
I 4
/* NINDIR is the number of indirects in a file system block. */
#define	NINDIR(fs)	((fs)->lfs_nindir)

/* INOPB is the number of inodes in a secondary storage block. */
#define	INOPB(fs)	((fs)->lfs_inopb)

D 12
/* IFPB -- IFILE's per block */
#define	IFPB(fs)	((fs)->lfs_ifpb)

E 12
D 46
#define	blksize(fs)		((fs)->lfs_bsize)
#define	blkoff(fs, loc)		((loc) & (fs)->lfs_bmask)
E 46
I 46
#define blksize(fs, ip, lbn) \
	(((lbn) >= NDADDR || (ip)->i_size >= ((lbn) + 1) << (fs)->lfs_bshift) \
	    ? (fs)->lfs_bsize \
	    : (fragroundup(fs, blkoff(fs, (ip)->i_size))))
#define	blkoff(fs, loc)		((int)((loc) & (fs)->lfs_bmask))
#define fragoff(fs, loc)	/* calculates (loc % fs->lfs_fsize) */ \
	((int)((loc) & (fs)->lfs_ffmask))
E 46
#define	fsbtodb(fs, b)		((b) << (fs)->lfs_fsbtodb)
I 28
#define	dbtofsb(fs, b)		((b) >> (fs)->lfs_fsbtodb)
I 46
#define	fragstodb(fs, b)	((b) << (fs)->lfs_fsbtodb - (fs)->lfs_fbshift)
#define	dbtofrags(fs, b)	((b) >> (fs)->lfs_fsbtodb - (fs)->lfs_fbshift)
E 46
E 28
#define	lblkno(fs, loc)		((loc) >> (fs)->lfs_bshift)
#define	lblktosize(fs, blk)	((blk) << (fs)->lfs_bshift)
I 5
D 40
#define numfrags(fs, loc)	/* calculates (loc / fs->fs_fsize) */ \
E 40
I 40
D 46
#define numfrags(fs, loc)	/* calculates (loc / fs->fs_fsize) */	\
E 40
	((loc) >> (fs)->lfs_bshift)
D 8
#define satosn(fs, saddr) \
	((int)((saddr - fs->lfs_sboffs[0]) / fsbtodb(fs, fs->lfs_ssize)))
#define sntosa(fs, sn) \
	((daddr_t)(sn * (fs->lfs_ssize << fs->lfs_fsbtodb) + fs->lfs_sboffs[0]))
E 8
I 8

E 46
I 46
#define numfrags(fs, loc)	/* calculates (loc / fs->lfs_fsize) */ \
	((loc) >> (fs)->lfs_ffshift)
#define blkroundup(fs, size)	/* calculates roundup(size, fs->lfs_bsize) */ \
	((int)(((size) + (fs)->lfs_bmask) & (~(fs)->lfs_bmask)))
#define fragroundup(fs, size)	/* calculates roundup(size, fs->lfs_fsize) */ \
	((int)(((size) + (fs)->lfs_ffmask) & (~(fs)->lfs_ffmask)))
#define fragstoblks(fs, frags)	/* calculates (frags / fs->lfs_frag) */ \
	((frags) >> (fs)->lfs_fbshift)
#define blkstofrags(fs, blks)	/* calculates (blks * fs->lfs_frag) */ \
	((blks) << (fs)->lfs_fbshift)
#define fragnum(fs, fsb)	/* calculates (fsb % fs->lfs_frag) */ \
	((fsb) & ((fs)->lfs_frag - 1))
#define blknum(fs, fsb)		/* calculates rounddown(fsb, fs->lfs_frag) */ \
	((fsb) &~ ((fs)->lfs_frag - 1))
#define dblksize(fs, dip, lbn) \
	(((lbn) >= NDADDR || (dip)->di_size >= ((lbn) + 1) << (fs)->lfs_bshift)\
	    ? (fs)->lfs_bsize \
	    : (fragroundup(fs, blkoff(fs, (dip)->di_size))))
E 46
I 17
D 40
#define	datosn(fs, daddr)	/* disk address to segment number */ \
E 40
I 40
#define	datosn(fs, daddr)	/* disk address to segment number */	\
E 40
	(((daddr) - (fs)->lfs_sboffs[0]) / fsbtodb((fs), (fs)->lfs_ssize))
D 40
#define sntoda(fs, sn) 		/* segment number to disk address */ \
	((daddr_t)((sn) * ((fs)->lfs_ssize << (fs)->lfs_fsbtodb) + \
E 40
I 40
#define sntoda(fs, sn) 		/* segment number to disk address */	\
D 45
	((daddr_t)((sn) * ((fs)->lfs_ssize << (fs)->lfs_fsbtodb) +	\
E 45
I 45
	((ufs_daddr_t)((sn) * ((fs)->lfs_ssize << (fs)->lfs_fsbtodb) +	\
E 45
E 40
	    (fs)->lfs_sboffs[0]))

E 17
I 14
/* Read in the block with the cleaner info from the ifile. */
D 40
#define LFS_CLEANERINFO(CP, F, BP) { \
I 17
D 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACC; \
E 39
I 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACCESS; \
E 39
E 17
D 16
	if (bread((F)->lfs_ivnode, (daddr_t)0, (F)->lfs_bsize, NOCRED, &BP)) \
E 16
I 16
	if (bread((F)->lfs_ivnode, (daddr_t)0, (F)->lfs_bsize, NOCRED, &(BP))) \
E 16
		panic("lfs: ifile read"); \
D 16
	(CP) = (CLEANERINFO *)BP->b_un.b_addr; \
E 16
I 16
D 39
	(CP) = (CLEANERINFO *)(BP)->b_un.b_addr; \
E 39
I 39
	(CP) = (CLEANERINFO *)(BP)->b_data; \
E 40
I 40
#define LFS_CLEANERINFO(CP, F, BP) {					\
	VTOI((F)->lfs_ivnode)->i_flag |= IN_ACCESS;			\
	if (bread((F)->lfs_ivnode,					\
D 45
	    (daddr_t)0, (F)->lfs_bsize, NOCRED, &(BP)))			\
E 45
I 45
	    (ufs_daddr_t)0, (F)->lfs_bsize, NOCRED, &(BP)))		\
E 45
		panic("lfs: ifile read");				\
	(CP) = (CLEANERINFO *)(BP)->b_data;				\
E 40
E 39
E 16
}

E 14
D 12
#define	datosn(fs, daddr)	/* disk address to segment number */ \
	(((daddr) - (fs)->lfs_sboffs[0]) / fsbtodb((fs), (fs)->lfs_ssize))
#define sntoda(fs, sn) 		/* segment number to disk address */ \
	((daddr_t)((sn) * ((fs)->lfs_ssize << (fs)->lfs_fsbtodb) + \
	    (fs)->lfs_sboffs[0]))
I 9

/* Read in the block containing a specific inode from the ifile. */
E 12
I 12
/* Read in the block with a specific inode from the ifile. */
E 12
D 14
#define	LFS_IENTRY(I, F, IN, BP) { \
E 14
I 14
D 40
#define	LFS_IENTRY(IP, F, IN, BP) { \
I 31
	int _e; \
E 31
I 16
D 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACC; \
E 39
I 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACCESS; \
E 39
E 16
E 14
D 12
	if (bread((F)->lfs_ivnode, (IN) / IFPB(F) + (F)->lfs_segtabsz, \
E 12
I 12
D 31
	if (bread((F)->lfs_ivnode, \
E 31
I 31
	if (_e = bread((F)->lfs_ivnode, \
E 31
	    (IN) / (F)->lfs_ifpb + (F)->lfs_cleansz + (F)->lfs_segtabsz, \
E 12
D 16
	    (F)->lfs_bsize, NOCRED, &BP)) \
E 16
I 16
	    (F)->lfs_bsize, NOCRED, &(BP))) \
E 16
D 31
		panic("lfs: ifile read"); \
E 31
I 31
		panic("lfs: ifile read %d", _e); \
E 31
D 12
	(I) = (IFILE *)BP->b_un.b_addr + IN % IFPB(F); \
E 12
I 12
D 14
	(I) = (IFILE *)BP->b_un.b_addr + IN % (F)->lfs_ifpb; \
E 14
I 14
D 16
	(IP) = (IFILE *)BP->b_un.b_addr + IN % (F)->lfs_ifpb; \
E 16
I 16
D 39
	(IP) = (IFILE *)(BP)->b_un.b_addr + (IN) % (F)->lfs_ifpb; \
E 39
I 39
	(IP) = (IFILE *)(BP)->b_data + (IN) % (F)->lfs_ifpb; \
E 40
I 40
#define	LFS_IENTRY(IP, F, IN, BP) {					\
	int _e;								\
	VTOI((F)->lfs_ivnode)->i_flag |= IN_ACCESS;			\
	if (_e = bread((F)->lfs_ivnode,					\
	    (IN) / (F)->lfs_ifpb + (F)->lfs_cleansz + (F)->lfs_segtabsz,\
	    (F)->lfs_bsize, NOCRED, &(BP)))				\
		panic("lfs: ifile read %d", _e);			\
	(IP) = (IFILE *)(BP)->b_data + (IN) % (F)->lfs_ifpb;		\
E 40
E 39
E 16
E 14
E 12
}

I 12
/* Read in the block with a specific segment usage entry from the ifile. */
D 14
#define	LFS_SEGENTRY(I, F, IN, BP) { \
E 14
I 14
D 40
#define	LFS_SEGENTRY(SP, F, IN, BP) { \
I 31
	int _e; \
E 31
I 16
D 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACC; \
E 39
I 39
	VTOI((F)->lfs_ivnode)->i_flag |= IACCESS; \
E 39
E 16
E 14
D 28
	if (bread((F)->lfs_ivnode, (IN) / (F)->lfs_sepb + (F)->lfs_cleansz, \
E 28
I 28
D 31
	if (bread((F)->lfs_ivnode, \
E 31
I 31
	if (_e = bread((F)->lfs_ivnode, \
E 31
	    ((IN) >> (F)->lfs_sushift) + (F)->lfs_cleansz, \
E 28
D 16
	    (F)->lfs_bsize, NOCRED, &BP)) \
E 16
I 16
	    (F)->lfs_bsize, NOCRED, &(BP))) \
E 16
D 31
		panic("lfs: ifile read"); \
E 31
I 31
		panic("lfs: ifile read: %d", _e); \
E 31
D 14
	(I) = (SEGUSE *)BP->b_un.b_addr + IN % (F)->lfs_sepb; \
E 14
I 14
D 16
	(SP) = (SEGUSE *)BP->b_un.b_addr + IN % (F)->lfs_sepb; \
E 16
I 16
D 28
	(SP) = (SEGUSE *)(BP)->b_un.b_addr + (IN) % (F)->lfs_sepb; \
E 28
I 28
D 39
	(SP) = (SEGUSE *)(BP)->b_un.b_addr + ((IN) & (F)->lfs_sepb - 1); \
E 39
I 39
	(SP) = (SEGUSE *)(BP)->b_data + ((IN) & (F)->lfs_sepb - 1); \
E 40
I 40
#define	LFS_SEGENTRY(SP, F, IN, BP) {					\
	int _e;								\
	VTOI((F)->lfs_ivnode)->i_flag |= IN_ACCESS;			\
	if (_e = bread((F)->lfs_ivnode,					\
	    ((IN) >> (F)->lfs_sushift) + (F)->lfs_cleansz,		\
	    (F)->lfs_bsize, NOCRED, &(BP)))				\
		panic("lfs: ifile read: %d", _e);			\
	(SP) = (SEGUSE *)(BP)->b_data + ((IN) & (F)->lfs_sepb - 1);	\
E 40
E 39
E 28
E 16
E 14
}

I 16
D 17
/* Release the ifile block, updating the access time. */
#define	LFS_IRELEASE(F, BP) { \
	VTOI((F)->lfs_ivnode)->i_flag |= IACC; \
	brelse((BP)); \
E 17
I 17
D 31
/* Write a block and update the inode change times. */
#define	LFS_UBWRITE(BP) { \
I 23
D 25
	USES_VOP_BWRITE; \
E 25
E 23
	VTOI((BP)->b_vp)->i_flag |= ICHG | IUPD; \
D 23
	lfs_bwrite(BP); \
E 23
I 23
	VOP_BWRITE(BP); \
E 23
E 17
}
E 31
I 31
/* 
 * Determine if there is enough room currently available to write db
 * disk blocks.  We need enough blocks for the new blocks, the current,
 * inode blocks, a summary block, plus potentially the ifile inode and
 * the segment usage table, plus an ifile page.
 */
#define LFS_FITS(fs, db)						\
D 35
	((db + ((fs)->lfs_uinodes + INOPB((fs))) / INOPB((fs)) +	\
	fsbtodb(fs, 1) + LFS_SUMMARY_SIZE / DEV_BSIZE + (fs)->lfs_segtabsz)\
E 35
I 35
D 42
	((long)((db + ((fs)->lfs_uinodes + INOPB((fs))) / INOPB((fs)) +	\
D 40
	fsbtodb(fs, 1) + LFS_SUMMARY_SIZE / DEV_BSIZE + (fs)->lfs_segtabsz))\
E 35
	< (fs)->lfs_avail)
E 40
I 40
	fsbtodb(fs, 1) + LFS_SUMMARY_SIZE / DEV_BSIZE +			\
E 42
I 42
	((int32_t)((db + ((fs)->lfs_uinodes + INOPB((fs))) / 		\
	INOPB((fs)) + fsbtodb(fs, 1) + LFS_SUMMARY_SIZE / DEV_BSIZE +	\
E 42
	(fs)->lfs_segtabsz)) < (fs)->lfs_avail)
E 40
E 31

I 31
/* Determine if a buffer belongs to the ifile */
#define IS_IFILE(bp)	(VTOI(bp->b_vp)->i_number == LFS_IFILE_INUM)
I 40

E 40
E 31
D 17
/* Release the ifile block, scheduling it for writing. */
#define	LFS_IWRITE(F, BP) { \
	VTOI((F)->lfs_ivnode)->i_flag |= ICHG | IUPD; \
	lfs_bwrite((BP)); \
}
	
E 17
E 16
/*
 * Structures used by lfs_bmapv and lfs_markv to communicate information
 * about inodes and data blocks.
 */
typedef struct block_info {
	ino_t	bi_inode;		/* inode # */
D 29
	off_t	bi_lbn;			/* logical block w/in file */
E 29
I 29
D 45
	daddr_t	bi_lbn;			/* logical block w/in file */
E 29
	daddr_t	bi_daddr;		/* disk address of block */
E 45
I 45
	ufs_daddr_t bi_lbn;		/* logical block w/in file */
	ufs_daddr_t bi_daddr;		/* disk address of block */
E 45
	time_t	bi_segcreate;		/* origin segment create time */
I 34
	int	bi_version;		/* file version number */
E 34
	void	*bi_bp;			/* data buffer */
I 46
	int     bi_size;                /* size of the block (if fragment) */
E 46
} BLOCK_INFO;
D 34

typedef struct inode_info {
	ino_t	ii_inode;		/* inode # */
	daddr_t	ii_daddr;		/* disk address of block */
	time_t	ii_segcreate;		/* origin segment create time */
	struct dinode *ii_dinode;	/* data buffer */
} INODE_INFO;
E 34
I 31

/* In-memory description of a segment about to be written. */
struct segment {
D 42
	struct lfs	*fs;		/* file system pointer */
E 42
I 42
	struct lfs	 *fs;		/* file system pointer */
E 42
	struct buf	**bpp;		/* pointer to buffer array */
	struct buf	**cbpp;		/* pointer to next available bp */
	struct buf	**start_bpp;	/* pointer to first bp in this set */
D 42
	struct buf	*ibp;		/* buffer pointer to inode page */
	struct finfo	*fip;		/* current fileinfo pointer */
I 32
	struct vnode	*vp;		/* vnode being gathered */
E 32
	void	*segsum;		/* segment summary info */
	u_long	ninodes;		/* number of inodes in this segment */
	u_long	seg_bytes_left;		/* bytes left in segment */
	u_long	sum_bytes_left;		/* bytes left in summary block */
	u_long	seg_number;		/* number of this segment */
	daddr_t *start_lbp;		/* beginning lbn for this set */
E 42
I 42
	struct buf	 *ibp;		/* buffer pointer to inode page */
	struct finfo	 *fip;		/* current fileinfo pointer */
	struct vnode	 *vp;		/* vnode being gathered */
	void	 *segsum;		/* segment summary info */
	u_int32_t ninodes;		/* number of inodes in this segment */
	u_int32_t seg_bytes_left;	/* bytes left in segment */
	u_int32_t sum_bytes_left;	/* bytes left in summary block */
	u_int32_t seg_number;		/* number of this segment */
D 45
	daddr_t  *start_lbp;		/* beginning lbn for this set */
E 45
I 45
	ufs_daddr_t *start_lbp;		/* beginning lbn for this set */
E 45

E 42
#define	SEGM_CKP	0x01		/* doing a checkpoint */
#define	SEGM_CLEAN	0x02		/* cleaner call; don't sort */
I 37
#define	SEGM_SYNC	0x04		/* wait for segment */
E 37
D 42
	u_long	seg_flags;		/* run-time flags for this segment */
E 42
I 42
	u_int16_t seg_flags;		/* run-time flags for this segment */
E 42
};
I 33

D 40
#define ISSPACE(F, BB, C) \
	(((C)->cr_uid == 0 && (F)->lfs_bfree >= (BB)) || \
E 40
I 40
#define ISSPACE(F, BB, C)						\
	(((C)->cr_uid == 0 && (F)->lfs_bfree >= (BB)) ||		\
E 40
	((C)->cr_uid != 0 && IS_FREESPACE(F, BB)))

D 40
#define IS_FREESPACE(F, BB) \
E 40
I 40
#define IS_FREESPACE(F, BB)						\
E 40
	((F)->lfs_bfree > ((F)->lfs_dsize * (F)->lfs_minfree / 100 + (BB)))

D 40
#define ISSPACE_XXX(F, BB) \
E 40
I 40
#define ISSPACE_XXX(F, BB)						\
E 40
	((F)->lfs_bfree >= (BB))
I 37

#define DOSTATS
#ifdef DOSTATS
/* Statistics Counters */
struct lfs_stats {
D 42
	int	segsused;
	int	psegwrites;
	int	psyncwrites;
	int	pcleanwrites;
	int	blocktot;
	int	cleanblocks;
	int	ncheckpoints;
	int	nwrites;
	int	nsync_writes;
	int	wait_exceeded;
	int	write_exceeded;
	int	flush_invoked;
E 42
I 42
	u_int	segsused;
	u_int	psegwrites;
	u_int	psyncwrites;
	u_int	pcleanwrites;
	u_int	blocktot;
	u_int	cleanblocks;
	u_int	ncheckpoints;
	u_int	nwrites;
	u_int	nsync_writes;
	u_int	wait_exceeded;
	u_int	write_exceeded;
	u_int	flush_invoked;
E 42
};
extern struct lfs_stats lfs_stats;
#endif
E 37
D 40

E 40
E 33
E 31
E 12
E 9
E 8
E 5
E 4
E 1
