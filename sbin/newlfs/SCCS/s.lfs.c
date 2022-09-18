h14037
s 00023/00008/00634
d D 8.5 95/05/24 19:46:52 margo 29 28
c Set segment summary magic numbers and add support for fragments.
e
s 00002/00004/00640
d D 8.4 95/05/01 23:51:28 mckusick 28 27
c new dinode format
e
s 00010/00010/00634
d D 8.3 95/04/28 10:46:41 bostic 27 26
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00005/00642
d D 8.2 94/06/14 16:52:39 mkm 26 25
c add lfs_maxsymlinklen (from mycroft)
e
s 00002/00002/00645
d D 8.1 93/06/05 11:07:16 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00644
d D 5.24 92/11/18 14:23:17 bostic 24 23
c 2^31 doesn't work in C
e
s 00001/00000/00646
d D 5.23 92/11/17 13:05:40 margo 23 22
c Add lock pid to lfs structure.
e
s 00004/00002/00642
d D 5.22 92/11/17 12:52:36 margo 22 21
c Use union for inode number.  Compute disk blocks per seg correctly.
e
s 00004/00002/00640
d D 5.21 92/09/03 08:26:02 margo 21 20
c Initialize dsize in terms of number of segments (i.e. don't count 
c extra space that doesn't live in any segment).
e
s 00022/00008/00620
d D 5.20 92/08/25 15:02:27 bostic 20 19
c Add available space accounting, so that the cleaner can be woken 
c up explicitly when we need space and so we can return ENOSPC accurately.
e
s 00001/00001/00627
d D 5.19 92/07/27 11:26:34 bostic 19 18
c Initialize empty segment "nsum" field to 0 so that bytes don't go 
c negative as soon as you reclaim the segment.
e
s 00001/00001/00627
d D 5.18 92/07/24 10:59:15 bostic 18 17
c fix checksum
e
s 00000/00005/00628
d D 5.17 92/07/23 23:07:59 bostic 17 16
c rip out unnecessary includes
e
s 00011/00004/00622
d D 5.16 92/07/23 16:30:33 bostic 16 15
c Add number of segment summary blocks and number of inodes to segment 
c usage table.  Since SEGUSE is now power of 2, allow fast arithmetic.  Change 
c block accounting to use sectors rather than file system blocks.
e
s 00008/00003/00618
d D 5.15 92/07/21 10:49:26 bostic 15 14
c Write an empty summary block after the first complete partial 
e
s 00002/00002/00619
d D 5.14 92/07/20 14:30:09 bostic 14 13
c block sizes in inodes (dinodes too) are measured in disk blocks not file system
c blocks.  Fix make_dinode to perform this calculation.
e
s 00036/00004/00585
d D 5.13 92/07/19 16:51:15 bostic 13 12
c add lfs_maxfilesize in the superblock
e
s 00012/00009/00577
d D 5.12 92/07/06 15:02:26 bostic 12 11
c struct direct now contains a type; times are now quad
e
s 00002/00002/00584
d D 5.11 92/07/06 14:52:17 bostic 11 10
c DIRSIZ now takes two args
e
s 00001/00002/00585
d D 5.10 92/07/06 14:05:00 bostic 10 9
c add lfs_seglock, delete lfs_segtab, lfs_seglist
e
s 00004/00000/00583
d D 5.9 92/06/22 23:48:27 bostic 9 8
c add directory ops
e
s 00001/00001/00582
d D 5.8 92/04/22 14:06:21 bostic 8 7
c typo
e
s 00001/00000/00582
d D 5.7 92/01/14 20:20:30 bostic 7 6
c needs moutn.h
e
s 00000/00003/00582
d D 5.6 91/12/31 15:19:14 bostic 6 5
c delete if_st_atime
e
s 00003/00005/00582
d D 5.5 91/12/31 15:01:23 bostic 5 4
c nbytes shouldn't include superblocks or summary blocks
e
s 00009/00005/00578
d D 5.4 91/12/14 17:06:15 bostic 4 3
c add cleaner info, set SEGUSE_SUPERBLOCK on segments with superblocks
e
s 00151/00125/00432
d D 5.3 91/12/06 17:00:21 bostic 3 2
c LFS version 2
e
s 00266/00095/00291
d D 5.2 91/12/06 16:50:58 bostic 2 1
c checkpoint
e
s 00386/00000/00000
d D 5.1 91/09/19 10:18:48 bostic 1 0
c date and time created 91/09/19 10:18:48 by bostic
e
u
U
t
T
I 1
/*-
D 25
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 2
D 17
#include <sys/uio.h>
E 17
E 2
#include <sys/disklabel.h>
I 2
#include <sys/time.h>
D 17
#include <sys/resource.h>
#include <sys/proc.h>
#include <sys/vnode.h>
E 17
I 7
#include <sys/mount.h>
E 7
E 2
D 3
#include <ufs/dinode.h>
I 2
#include <ufs/dir.h>
E 3
I 3

#include <ufs/ufs/dir.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/dinode.h>
D 17
#include <ufs/ufs/ufsmount.h>
E 17
#include <ufs/lfs/lfs.h>

E 3
E 2
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
D 3
#include "lfs.h"				/* XXX move to <sys/lfs.h> */
E 3
#include "config.h"
#include "extern.h"

I 13
/*
 * This table is indexed by the log base 2 of the block size.
 * It returns the maximum file size allowed in a file system
 * with the specified block size.  For block sizes smaller than
 * 8K, the size is limited by tha maximum number of blocks that
 * can be reached by triply indirect blocks:
 *	NDADDR + INOPB(bsize) + INOPB(bsize)^2 + INOPB(bsize)^3
 * For block size of 8K or larger, the file size is limited by the
 * number of blocks that can be represented in the file system.  Since
 * we use negative block numbers to represent indirect blocks, we can
 * have a maximum of 2^31 blocks.
 */

u_quad_t maxtable[] = {
	/*    1 */ -1,
	/*    2 */ -1,
	/*    4 */ -1,
	/*    8 */ -1,
	/*   16 */ -1,
	/*   32 */ -1,
	/*   64 */ -1,
	/*  128 */ -1,
	/*  256 */ -1,
	/*  512 */ NDADDR + 128 + 128 * 128 + 128 * 128 * 128,
	/* 1024 */ NDADDR + 256 + 256 * 256 + 256 * 256 * 256,
	/* 2048 */ NDADDR + 512 + 512 * 512 + 512 * 512 * 512,
	/* 4096 */ NDADDR + 1024 + 1024 * 1024 + 1024 * 1024 * 1024,
D 24
	/* 8192 */ 2 ^ 31,
	/* 16 K */ 2 ^ 31,
	/* 32 K */ 2 ^ 31
E 24
I 24
	/* 8192 */ 1 << 31,
	/* 16 K */ 1 << 31,
	/* 32 K */ 1 << 31,
E 24
};

E 13
D 2
static LFS_SUPER lfs_default =  {
E 2
I 2
D 3
static LFS lfs_default =  {
E 3
I 3
static struct lfs lfs_default =  {
E 3
E 2
	/* lfs_magic */		LFS_MAGIC,
	/* lfs_version */	LFS_VERSION,
	/* lfs_size */		0,
D 3
	/* lfs_ssize */		0,
E 3
I 3
	/* lfs_ssize */		DFL_LFSSEG/DFL_LFSBLOCK,
E 3
	/* lfs_dsize */		0,
	/* lfs_bsize */		DFL_LFSBLOCK,
D 2
	/* lfs_fsize */		0,
	/* lfs_frag */		0,
E 2
I 2
D 29
	/* lfs_fsize */		DFL_LFSBLOCK,
E 29
I 29
	/* lfs_fsize */		DFL_LFSFRAG,
E 29
	/* lfs_frag */		1,
E 2
	/* lfs_free */		LFS_FIRST_INUM,
I 2
	/* lfs_bfree */		0,
	/* lfs_nfiles */	0,
I 20
	/* lfs_avail */		0,
	/* lfs_uinodes */	0,
E 20
E 2
	/* lfs_idaddr */	0,
	/* lfs_ifile */		LFS_IFILE_INUM,
	/* lfs_lastseg */	0,
I 2
	/* lfs_nextseg */	0,
I 3
	/* lfs_curseg */	0,
	/* lfs_offset */	0,
I 9
	/* lfs_lastpseg */	0,
E 9
E 3
E 2
	/* lfs_tstamp */	0,
	/* lfs_minfree */	MINFREE,
I 13
	/* lfs_maxfilesize */	0,
E 13
I 3
	/* lfs_dbpseg */	DFL_LFSSEG/DEV_BSIZE,
E 3
	/* lfs_inopb */		DFL_LFSBLOCK/sizeof(struct dinode),
	/* lfs_ifpb */		DFL_LFSBLOCK/sizeof(IFILE),
I 3
	/* lfs_sepb */		DFL_LFSBLOCK/sizeof(SEGUSE),
E 3
	/* lfs_nindir */	DFL_LFSBLOCK/sizeof(daddr_t),
	/* lfs_nseg */		0,
	/* lfs_nspf */		0,
I 3
	/* lfs_cleansz */	0,
E 3
	/* lfs_segtabsz */	0,
	/* lfs_segmask */	DFL_LFSSEG_MASK,
	/* lfs_segshift */	DFL_LFSSEG_SHIFT,
	/* lfs_bmask */		DFL_LFSBLOCK_MASK,
	/* lfs_bshift */	DFL_LFSBLOCK_SHIFT,
D 29
	/* lfs_ffmask */	0,
	/* lfs_ffshift */	0,
	/* lfs_fbmask */	0,
	/* lfs_fbshift */	0,
E 29
I 29
	/* lfs_ffmask */	DFL_LFS_FFMASK,
	/* lfs_ffshift */	DFL_LFS_FFSHIFT,
	/* lfs_fbmask */	DFL_LFS_FBMASK,
	/* lfs_fbshift */	DFL_LFS_FBSHIFT,
E 29
	/* lfs_fsbtodb */	0,
I 16
	/* lfs_sushift */	0,
E 16
	/* lfs_sboffs */	{ 0 },
I 22
	/* lfs_sp */		NULL,
E 22
I 2
	/* lfs_ivnode */	NULL,
D 10
	/* lfs_segtab */	NULL,
	/* lfs_seglist */	NULL,
E 10
I 10
	/* lfs_seglock */	0,
I 23
	/* lfs_lockpid */	0,
E 23
E 10
	/* lfs_iocount */	0,
I 9
	/* lfs_writer */	0,
	/* lfs_dirops */	0,
	/* lfs_doifile */	0,
I 20
	/* lfs_nactive */	0,
E 20
E 9
E 2
	/* lfs_fmod */		0,
	/* lfs_clean */		0,
	/* lfs_ronly */		0,
	/* lfs_flags */		0,
	/* lfs_fsmnt */		{ 0 },
I 2
	/* lfs_pad */		{ 0 },
E 2
D 26
	/* lfs_cksum */		0
E 26
I 26
	/* lfs_cksum */		0,
	/* lfs_maxsymlinklen */ MAXSYMLINKLEN
E 26
};

I 2

struct direct lfs_root_dir[] = {
D 12
	{ ROOTINO, sizeof(struct direct), 1, "."},
	{ ROOTINO, sizeof(struct direct), 2, ".."},
I 3
	{ LFS_IFILE_INUM, sizeof(struct direct), 5, "ifile"},
E 3
	{ LOSTFOUNDINO, sizeof(struct direct), 10, "lost+found"},
E 12
I 12
	{ ROOTINO, sizeof(struct direct), DT_DIR, 1, "."},
	{ ROOTINO, sizeof(struct direct), DT_DIR, 2, ".."},
	{ LFS_IFILE_INUM, sizeof(struct direct), DT_REG, 5, "ifile"},
	{ LOSTFOUNDINO, sizeof(struct direct), DT_DIR, 10, "lost+found"},
E 12
};

struct direct lfs_lf_dir[] = {
D 12
        { LOSTFOUNDINO, sizeof(struct direct), 1, "." },
        { ROOTINO, sizeof(struct direct), 2, ".." },
E 12
I 12
        { LOSTFOUNDINO, sizeof(struct direct), DT_DIR, 1, "." },
        { ROOTINO, sizeof(struct direct), DT_DIR, 2, ".." },
E 12
};

static daddr_t make_dinode 
D 3
	__P((ino_t, struct dinode *, int, daddr_t, LFS *));
E 3
I 3
	__P((ino_t, struct dinode *, int, daddr_t, struct lfs *));
E 3
static void make_dir __P(( void *, struct direct *, int));
E 2
static void put __P((int, off_t, void *, size_t));

int
D 29
make_lfs(fd, lp, partp, minfree, block_size, seg_size)
E 29
I 29
make_lfs(fd, lp, partp, minfree, block_size, frag_size, seg_size)
E 29
	int fd;
	struct disklabel *lp;
	struct partition *partp;
	int minfree;
	int block_size;
I 29
	int frag_size;
E 29
	int seg_size;
{
	struct dinode *dip;	/* Pointer to a disk inode */
I 2
	struct dinode *dpagep;	/* Pointer to page of disk inodes */
I 3
	CLEANERINFO *cleaninfo;	/* Segment cleaner information table */
E 3
E 2
	FINFO file_info;	/* File info structure in summary blocks */
	IFILE *ifile;		/* Pointer to array of ifile structures */
	IFILE *ip;		/* Pointer to array of ifile structures */
D 2
	LFS_SUPER *lfsp;	/* Superblock */
	SEGUSAGE *segp;		/* Segment usage table */
	SEGUSAGE *segtable;	/* Segment usage table */
E 2
I 2
D 3
	LFS *lfsp;		/* Superblock */
E 3
I 3
	struct lfs *lfsp;	/* Superblock */
E 3
	SEGUSE *segp;		/* Segment usage table */
	SEGUSE *segtable;	/* Segment usage table */
E 2
	SEGSUM summary;		/* Segment summary structure */
D 2
	SEGSUM *sp;		/* Segment summary pointer */
E 2
I 2
D 3
	SEGSUM *sp, *sp1, *sp2;	/* Segment summary pointer */
E 3
I 3
	SEGSUM *sp;		/* Segment summary pointer */
E 3
E 2
	daddr_t	last_sb_addr;	/* Address of superblocks */
I 2
	daddr_t last_addr;	/* Previous segment address */
E 2
	daddr_t	sb_addr;	/* Address of superblocks */
I 2
	daddr_t	seg_addr;	/* Address of current segment */
E 2
D 3
	void *pagep;		/* Pointer to the page we use to write stuff */
E 3
I 3
	void *ipagep;		/* Pointer to the page we use to write stuff */
E 3
	void *sump;		/* Used to copy stuff into segment buffer */
	u_long *block_array;	/* Array of logical block nos to put in sum */
I 3
	u_long blocks_used;	/* Number of blocks in first segment */
	u_long *dp;		/* Used to computed checksum on data */
	u_long *datasump;	/* Used to computed checksum on data */
E 3
	int block_array_size;	/* How many entries in block array */
	int bsize;		/* Block size */
I 29
	int fsize;		/* Fragment size */
E 29
	int db_per_fb;		/* Disk blocks per file block */
D 2
	int i;
E 2
I 2
	int i, j;
I 3
	int off;		/* Offset at which to write */
E 3
E 2
D 13
	int sb_to_sum;		/* offset between superblock and summary */
E 13
	int sb_interval;	/* number of segs between super blocks */
	int seg_seek;		/* Seek offset for a segment */
	int ssize;		/* Segment size */
	int sum_size;		/* Size of the summary block */
D 13
	int wbytes;		/* Number of bytes returned by write */
E 13

	lfsp = &lfs_default;

	if (!(bsize = block_size))
		bsize = DFL_LFSBLOCK;
I 29
	if (!(fsize = frag_size))
		fsize = DFL_LFSFRAG;
E 29
	if (!(ssize = seg_size))
		ssize = DFL_LFSSEG;

	/* Modify parts of superblock overridden by command line arguments */
D 29
	if (bsize != DFL_LFSBLOCK) {
E 29
I 29
	if (bsize != DFL_LFSBLOCK || fsize != DFL_LFSFRAG) {
E 29
		lfsp->lfs_bshift = log2(bsize);
		if (1 << lfsp->lfs_bshift != bsize)
			fatal("%d: block size not a power of 2", bsize);
		lfsp->lfs_bsize = bsize;
I 2
D 29
		lfsp->lfs_fsize = bsize;
E 29
I 29
		lfsp->lfs_fsize = fsize;
E 29
E 2
		lfsp->lfs_bmask = bsize - 1;
		lfsp->lfs_inopb = bsize / sizeof(struct dinode);
I 29
		lfsp->lfs_ffmask = fsize - 1;
		lfsp->lfs_ffshift = log2(fsize);
		if (1 << lfsp->lfs_ffshift != fsize)
			fatal("%d: frag size not a power of 2", fsize);
		lfsp->lfs_frag = numfrags(lfsp, bsize);
		lfsp->lfs_fbmask = lfsp->lfs_frag - 1;
		lfsp->lfs_fbshift = log2(lfsp->lfs_frag);
E 29
/* MIS -- should I round to power of 2 */
		lfsp->lfs_ifpb = bsize / sizeof(IFILE);
I 3
		lfsp->lfs_sepb = bsize / sizeof(SEGUSE);
E 3
		lfsp->lfs_nindir = bsize / sizeof(daddr_t);
	}

	if (ssize != DFL_LFSSEG) {
		lfsp->lfs_segshift = log2(ssize);
		if (1 << lfsp->lfs_segshift != ssize)
			fatal("%d: segment size not power of 2", ssize);
		lfsp->lfs_ssize = ssize;
		lfsp->lfs_segmask = ssize - 1;
I 22
		lfsp->lfs_dbpseg = ssize / DEV_BSIZE;
E 22
	}
	lfsp->lfs_ssize = ssize >> lfsp->lfs_bshift;

	if (minfree)
		lfsp->lfs_minfree = minfree;

	/*
	 * Fill in parts of superblock that can be computed from file system
	 * size, disk geometry and current time.
	 */
	db_per_fb = bsize/lp->d_secsize;
	lfsp->lfs_fsbtodb = log2(db_per_fb);
I 16
	lfsp->lfs_sushift = log2(lfsp->lfs_sepb);
E 16
	lfsp->lfs_size = partp->p_size >> lfsp->lfs_fsbtodb;
	lfsp->lfs_dsize = lfsp->lfs_size - (LFS_LABELPAD >> lfsp->lfs_bshift);
	lfsp->lfs_nseg = lfsp->lfs_dsize / lfsp->lfs_ssize;
I 13
	lfsp->lfs_maxfilesize = maxtable[lfsp->lfs_bshift] << lfsp->lfs_bshift;
E 13
I 2

	/* 
D 20
	 * The number of free blocks is set from the total data size (lfs_dsize)
D 16
	 * minus one block for each segment (for the segment summary).  Then 
E 16
I 16
	 * minus one sector for each segment (for the segment summary).  Then 
E 16
D 3
	 * we'll dubstract off the room for the superblocks, ifile entries and
	 * segment usage table 
E 3
I 3
	 * we'll subtract off the room for the superblocks, ifile entries and
	 * segment usage table.
E 20
I 20
	 * The number of free blocks is set from the number of segments times
D 21
	 * the segment size.  Then we'll subtract off the room for the
E 21
I 21
	 * the segment size - 2 (that we never write because we need to make
	 * sure the cleaner can run).  Then we'll subtract off the room for the
E 21
	 * superblocks ifile entries and segment usage table.
E 20
E 3
	 */
D 16
	lfsp->lfs_bfree = lfsp->lfs_dsize - lfsp->lfs_nseg;
E 16
I 16
D 20
	lfsp->lfs_bfree = lfsp->lfs_dsize * db_per_fb - lfsp->lfs_nseg;
E 20
I 20
D 21
	lfsp->lfs_bfree = fsbtodb(lfsp, lfsp->lfs_nseg * lfsp->lfs_ssize);
E 21
I 21
	lfsp->lfs_dsize = fsbtodb(lfsp, (lfsp->lfs_nseg - 2) * lfsp->lfs_ssize);
	lfsp->lfs_bfree = lfsp->lfs_dsize;
E 21
E 20
E 16
E 2
	lfsp->lfs_segtabsz = SEGTABSIZE_SU(lfsp);
I 3
	lfsp->lfs_cleansz = CLEANSIZE_SU(lfsp);
E 3
	if ((lfsp->lfs_tstamp = time(NULL)) == -1)
		fatal("time: %s", strerror(errno));
	if ((sb_interval = lfsp->lfs_nseg / LFS_MAXNUMSB) < LFS_MIN_SBINTERVAL)
		sb_interval = LFS_MIN_SBINTERVAL;

	/*
	 * Now, lay out the file system.  We need to figure out where
	 * the superblocks go, initialize the checkpoint information
	 * for the first two superblocks, initialize the segment usage
	 * information, put the segusage information in the ifile, create
	 * the first block of IFILE structures, and link all the IFILE
	 * structures into a free list.
	 */

	/* Figure out where the superblocks are going to live */
	lfsp->lfs_sboffs[0] = LFS_LABELPAD/lp->d_secsize;
	for (i = 1; i < LFS_MAXNUMSB; i++) {
		sb_addr = ((i * sb_interval) << 
		    (lfsp->lfs_segshift - lfsp->lfs_bshift + lfsp->lfs_fsbtodb))
		    + lfsp->lfs_sboffs[0];
		if (sb_addr > partp->p_size)
			break;
		lfsp->lfs_sboffs[i] = sb_addr;
	}
	last_sb_addr = lfsp->lfs_sboffs[i - 1];
	lfsp->lfs_lastseg = lfsp->lfs_sboffs[0];
I 2
	lfsp->lfs_nextseg = 
	    lfsp->lfs_sboffs[1] ? lfsp->lfs_sboffs[1] : lfsp->lfs_sboffs[0];
I 3
	lfsp->lfs_curseg = lfsp->lfs_lastseg;
E 3
E 2

	/*
	 * Initialize the segment usage table.  The first segment will
D 3
	 * contain the superblock, the segusage table (segtabsz), 1
D 2
	 * block's worth of IFILE entries, and one block's worth of inodes
	 * (containing the ifile inode).
E 2
I 2
	 * block's worth of IFILE entries, the root directory, the lost+found
	 * directory and one block's worth of inodes (containing the ifile,
	 * root, and l+f inodes).
E 3
I 3
	 * contain the superblock, the cleanerinfo (cleansz), the segusage 
	 * table * (segtabsz), 1 block's worth of IFILE entries, the root 
	 * directory, the lost+found directory and one block's worth of 
	 * inodes (containing the ifile, root, and l+f inodes).
E 3
E 2
	 */
I 3
	if (!(cleaninfo = malloc(lfsp->lfs_cleansz << lfsp->lfs_bshift)))
		fatal("%s", strerror(errno));
D 4
	/* XXX When Carl has defined the cleanerinfo, initialize it here */
E 4
I 4
	cleaninfo->clean = lfsp->lfs_nseg - 1;
	cleaninfo->dirty = 1;

E 4
E 3
	if (!(segtable = malloc(lfsp->lfs_segtabsz << lfsp->lfs_bshift)))
		fatal("%s", strerror(errno));
	segp = segtable;
D 2
	segp->su_nbytes =
	    LFS_SBPAD + (lfsp->lfs_segtabsz + 2 << lfsp->lfs_bshift);
E 2
I 2
D 3
	segp->su_nbytes = LFS_SBPAD + 
	    ((lfsp->lfs_segtabsz + 4) << lfsp->lfs_bshift);
E 3
I 3
	blocks_used = lfsp->lfs_segtabsz + lfsp->lfs_cleansz + 4;
D 5
	segp->su_nbytes = LFS_SBPAD + (blocks_used << lfsp->lfs_bshift);
E 5
I 5
D 20
	segp->su_nbytes = blocks_used << lfsp->lfs_bshift;
E 20
I 20
	segp->su_nbytes = ((blocks_used - 1) << lfsp->lfs_bshift) +
	    3 * sizeof(struct dinode) + LFS_SUMMARY_SIZE;
E 20
E 5
E 3
E 2
	segp->su_lastmod = lfsp->lfs_tstamp;
I 16
	segp->su_nsums = 1;	/* 1 summary blocks */
	segp->su_ninos = 1;	/* 1 inode block */
E 16
D 2
	segp->su_flags = SEGUSAGE_DIRTY;
E 2
I 2
D 4
	segp->su_flags = SEGUSE_DIRTY;
D 3
	lfsp->lfs_bfree -= (lfsp->lfs_segtabsz + 4);
E 3
I 3
	lfsp->lfs_bfree -= (lfsp->lfs_cleansz + lfsp->lfs_segtabsz + 4);
E 4
I 4
	segp->su_flags = SEGUSE_SUPERBLOCK | SEGUSE_DIRTY;
D 16
	lfsp->lfs_bfree -= lfsp->lfs_cleansz + lfsp->lfs_segtabsz + 4;
E 16
I 16
D 20
	lfsp->lfs_bfree -= db_per_fb *
	     (lfsp->lfs_cleansz + lfsp->lfs_segtabsz + 4);
E 20
I 20
	lfsp->lfs_bfree -= LFS_SUMMARY_SIZE / lp->d_secsize;
	lfsp->lfs_bfree -=
	     fsbtodb(lfsp, lfsp->lfs_cleansz + lfsp->lfs_segtabsz + 4);
E 20
E 16
E 4
E 3
E 2

D 3
	/* Now use su_nbytes to figure out the daddr of the ifile inode */
	lfsp->lfs_idaddr = (((segp->su_nbytes >> lfsp->lfs_bshift) - 1) <<
	    lfsp->lfs_fsbtodb) + lfsp->lfs_sboffs[0];
E 3
I 3
	/* 
	 * Now figure out the address of the ifile inode. The inode block
	 * appears immediately after the segment summary.
	 */
	lfsp->lfs_idaddr = (LFS_LABELPAD + LFS_SBPAD + LFS_SUMMARY_SIZE) /
	    lp->d_secsize;
E 3

	for (segp = segtable + 1, i = 1; i < lfsp->lfs_nseg; i++, segp++) {
D 2
		if ((i % sb_interval) == (sb_interval - 1))
E 2
I 2
		if ((i % sb_interval) == 0) {
I 4
			segp->su_flags = SEGUSE_SUPERBLOCK;
E 4
E 2
D 5
			segp->su_nbytes = LFS_SBPAD;
E 5
D 2
		else
E 2
I 2
D 16
			lfsp->lfs_bfree -= (LFS_SBPAD >> lfsp->lfs_bshift);
E 16
I 16
			lfsp->lfs_bfree -= (LFS_SBPAD / lp->d_secsize);
E 16
D 4
		} else
E 4
I 4
D 5
		} else {
E 5
I 5
		} else
E 5
			segp->su_flags = 0;
E 4
E 2
D 5
			segp->su_nbytes = 0;
I 4
		}
E 5
E 4
		segp->su_lastmod = 0;
I 5
		segp->su_nbytes = 0;
I 16
		segp->su_ninos = 0;
D 19
		segp->su_nsums = 1;
E 19
I 19
		segp->su_nsums = 0;
E 19
E 16
E 5
D 4
		segp->su_flags = 0;
E 4
	}

I 20
	/* 
	 * Initialize dynamic accounting.  The blocks available for
	 * writing are the bfree blocks minus 1 segment summary for
	 * each segment since you can't write any new data without
	 * creating a segment summary - 2 segments that the cleaner
	 * needs.
	 */
	lfsp->lfs_avail = lfsp->lfs_bfree - lfsp->lfs_nseg - 
		fsbtodb(lfsp, 2 * lfsp->lfs_ssize);
	lfsp->lfs_uinodes = 0;
E 20
	/*
	 * Ready to start writing segments.  The first segment is different
	 * because it contains the segment usage table and the ifile inode
D 2
	 * as well as a superblock.  We don't have to write any segments which
	 * don't contain superblocks since they are marked as clean and do not
	 * containing any live bytes, so the only other segments we need to
	 * write are those containing superblock info.  For all these segments,
	 * set the time stamp to be 0 so that the first superblock looks like
	 * the most recent.
E 2
I 2
	 * as well as a superblock.  For the rest of the segments, set the 
	 * time stamp to be 0 so that the first segment is the most recent.
	 * For each segment that is supposed to contain a copy of the super
	 * block, initialize its first few blocks and its segment summary 
	 * to indicate this.
E 2
	 */
I 2
	lfsp->lfs_nfiles = LFS_FIRST_INUM - 1;
E 2
	lfsp->lfs_cksum = 
D 2
	    cksum(lfsp, sizeof(LFS_SUPER) - sizeof(lfsp->lfs_cksum));
	put(fd, LFS_LABELPAD, lfsp, sizeof(LFS_SUPER));
E 2
I 2
D 3
	    cksum(lfsp, sizeof(LFS) - sizeof(lfsp->lfs_cksum));
	put(fd, LFS_LABELPAD, lfsp, sizeof(LFS));
E 2
	put(fd, LFS_LABELPAD + LFS_SBPAD, segtable,
	    lfsp->lfs_segtabsz << lfsp->lfs_bshift);
	(void)free(segtable);
E 3
I 3
	    cksum(lfsp, sizeof(struct lfs) - sizeof(lfsp->lfs_cksum));
E 3

D 2
	/* Create the first block of the ifile. */
E 2
I 2
	/* Now create a block of disk inodes */
	if (!(dpagep = malloc(lfsp->lfs_bsize)))
		fatal("%s", strerror(errno));
	dip = (struct dinode *)dpagep;
D 27
	bzero(dip, lfsp->lfs_bsize);
E 27
I 27
	memset(dip, 0, lfsp->lfs_bsize);
E 27

D 3
	/* Create a block of the IFILES. */
E 2
	if (!(pagep = malloc(lfsp->lfs_bsize)))
E 3
I 3
	/* Create a block of IFILE structures. */
	if (!(ipagep = malloc(lfsp->lfs_bsize)))
E 3
		fatal("%s", strerror(errno));
D 3
	ifile = (IFILE *)pagep;
E 3
I 3
	ifile = (IFILE *)ipagep;
E 3
D 2
	for (ip = &ifile[2], i = 2; i < lfsp->lfs_ifpb; ++ip) {
E 2
I 2

D 3
	/* Initialize IFILE */
	sb_addr = (LFS_LABELPAD + LFS_SBPAD) / lp->d_secsize;
	sb_addr = make_dinode(LFS_IFILE_INUM, dip, lfsp->lfs_segtabsz+1, 
	    sb_addr, lfsp);
E 3
I 3
	/* 
	 * Initialize IFILE.  It is the next block following the
	 * block of inodes (whose address has been calculated in
	 * lfsp->lfs_idaddr;
	 */
	sb_addr = lfsp->lfs_idaddr + lfsp->lfs_bsize / lp->d_secsize;
	sb_addr = make_dinode(LFS_IFILE_INUM, dip, 
	    lfsp->lfs_cleansz + lfsp->lfs_segtabsz+1, sb_addr, lfsp);
E 3
	dip->di_mode = IFREG|IREAD|IWRITE;
	ip = &ifile[LFS_IFILE_INUM];
	ip->if_version = 1;
	ip->if_daddr = lfsp->lfs_idaddr;
D 6
	ip->if_st_atime = lfsp->lfs_tstamp;
E 6

	/* Initialize the ROOT Directory */
	sb_addr = make_dinode(ROOTINO, ++dip, 1, sb_addr, lfsp);
	dip->di_mode = IFDIR|IREAD|IWRITE|IEXEC;
	dip->di_size = DIRBLKSIZ;
	dip->di_nlink = 3;
	ip = &ifile[ROOTINO];
	ip->if_version = 1;
	ip->if_daddr = lfsp->lfs_idaddr;
D 6
	ip->if_st_atime = lfsp->lfs_tstamp;
E 6

	/* Initialize the lost+found Directory */
	sb_addr = make_dinode(LOSTFOUNDINO, ++dip, 1, sb_addr, lfsp);
	dip->di_mode = IFDIR|IREAD|IWRITE|IEXEC;
	dip->di_size = DIRBLKSIZ;
	dip->di_nlink = 2;
	ip = &ifile[LOSTFOUNDINO];
	ip->if_version = 1;
	ip->if_daddr = lfsp->lfs_idaddr;
D 6
	ip->if_st_atime = lfsp->lfs_tstamp;
E 6

	/* Make all the other dinodes invalid */
	for (i = INOPB(lfsp)-3, dip++; i; i--, dip++)
D 22
		dip->di_inum = LFS_UNUSED_INUM;
E 22
I 22
		dip->di_inumber = LFS_UNUSED_INUM;
E 22
	

	/* Link remaining IFILE entries in free list */
	for (ip = &ifile[LFS_FIRST_INUM], i = LFS_FIRST_INUM; 
	    i < lfsp->lfs_ifpb; ++ip) {
E 2
		ip->if_version = 1;
		ip->if_daddr = LFS_UNUSED_DADDR;
		ip->if_nextfree = ++i;
	}
	ifile[lfsp->lfs_ifpb - 1].if_nextfree = LFS_UNUSED_INUM;
D 2
	ip = &ifile[LFS_IFILE_INUM];
	ip->if_version = 1;
	ip->if_daddr = lfsp->lfs_idaddr;
	ip->if_st_atime = lfsp->lfs_tstamp;
E 2

I 2
D 3
	/* Now, write the ifile */
E 2
	if ((wbytes = write(fd, ifile, lfsp->lfs_bsize)) < 0)
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != lfsp->lfs_bsize)
		fatal("%s: short write (%d, not %d)",
		    special, wbytes, lfsp->lfs_bsize);
E 3
I 3
	/* Now, write the segment */
E 3

I 3
	/* Compute a checksum across all the data you're writing */
	dp = datasump = malloc (blocks_used * sizeof(u_long));
D 18
	*dp++ = ((u_long *)dip)[0];		/* inode block */
E 18
I 18
	*dp++ = ((u_long *)dpagep)[0];		/* inode block */
E 18
	for (i = 0; i < lfsp->lfs_cleansz; i++)
		*dp++ = ((u_long *)cleaninfo)[(i << lfsp->lfs_bshift) / 
		    sizeof(u_long)];		/* Cleaner info */
	for (i = 0; i < lfsp->lfs_segtabsz; i++)
		*dp++ = ((u_long *)segtable)[(i << lfsp->lfs_bshift) / 
		    sizeof(u_long)];		/* Segusage table */
	*dp++ = ((u_long *)ifile)[0];		/* Ifile */

	/* Still need the root and l+f bytes; get them later */

	/* Write out the inode block */
	off = LFS_LABELPAD + LFS_SBPAD + LFS_SUMMARY_SIZE;
	put(fd, off, dpagep, lfsp->lfs_bsize);
	free(dpagep);
	off += lfsp->lfs_bsize;

	/* Write out the ifile */

	put(fd, off, cleaninfo, lfsp->lfs_cleansz << lfsp->lfs_bshift);
	off += (lfsp->lfs_cleansz << lfsp->lfs_bshift);
	(void)free(cleaninfo);

	put(fd, off, segtable, lfsp->lfs_segtabsz << lfsp->lfs_bshift);
	off += (lfsp->lfs_segtabsz << lfsp->lfs_bshift);
	(void)free(segtable);

	put(fd, off, ifile, lfsp->lfs_bsize);
	off += lfsp->lfs_bsize;

	/*
	 * use ipagep for space for writing out other stuff.  It used to 
	 * contain the ifile, but we're done with it.
	 */

E 3
D 2
	/* Now create a block of disk inodes */
	dip = (struct dinode *)pagep;
	bzero(dip, sizeof(struct dinode));
	dip->di_mode = IFREG;
	dip->di_nlink = 1;
	dip->di_blocks = lfsp->lfs_segtabsz + 1;
	/* If we ever need something longer than 32 bits, this changes */
	dip->di_size = (dip->di_blocks << lfsp->lfs_bshift);
	dip->di_atime = dip->di_mtime = dip->di_ctime = lfsp->lfs_tstamp;
	dip->di_inum = LFS_IFILE_INUM;
#define	SEGERR \
"Segusage table requires too many blocks; increase block or segment size."
	if (NDADDR < lfsp->lfs_segtabsz)
		fatal("%s", SEGERR);
	sb_addr = (LFS_LABELPAD + LFS_SBPAD) / lp->d_secsize;
E 2
I 2
	/* Write out the root and lost and found directories */
D 3
	bzero(pagep, lfsp->lfs_bsize);
	make_dir(pagep, lfs_root_dir, 
E 3
I 3
D 27
	bzero(ipagep, lfsp->lfs_bsize);
E 27
I 27
	memset(ipagep, 0, lfsp->lfs_bsize);
E 27
	make_dir(ipagep, lfs_root_dir, 
E 3
	    sizeof(lfs_root_dir) / sizeof(struct direct));
D 3
	if ((wbytes = write(fd, pagep, lfsp->lfs_bsize)) < 0)
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != lfsp->lfs_bsize)
		fatal("%s: short write (%d, not %d)",
		    special, wbytes, lfsp->lfs_bsize);
E 3
I 3
	*dp++ = ((u_long *)ipagep)[0];
	put(fd, off, ipagep, lfsp->lfs_bsize);
	off += lfsp->lfs_bsize;
E 3
E 2

D 2
	/* Assign the block addresses for the ifile */
	for (i = 0; i < dip->di_blocks; i++, sb_addr += db_per_fb)
		dip->di_db[i] = sb_addr;
E 2
I 2
D 3
	bzero(pagep, lfsp->lfs_bsize);
	make_dir(pagep, lfs_lf_dir, 
E 3
I 3
D 27
	bzero(ipagep, lfsp->lfs_bsize);
E 27
I 27
	memset(ipagep, 0, lfsp->lfs_bsize);
E 27
	make_dir(ipagep, lfs_lf_dir, 
E 3
		sizeof(lfs_lf_dir) / sizeof(struct direct));
D 3
	if ((wbytes = write(fd, pagep, lfsp->lfs_bsize)) < 0)
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != lfsp->lfs_bsize)
		fatal("%s: short write (%d, not %d)",
		    special, wbytes, lfsp->lfs_bsize);
E 3
I 3
	*dp++ = ((u_long *)ipagep)[0];
	put(fd, off, ipagep, lfsp->lfs_bsize);
E 3
E 2

D 2
	/* Make all the other dinodes invalid */
	for (i = 1, dip++; i < lfsp->lfs_inopb; i++, dip++)
		dip->di_inum = LFS_UNUSED_INUM;

E 2
D 3
	/* Finally, write out the inode block */
D 2
	if ((wbytes = write(fd, pagep, lfsp->lfs_bsize)) < 0)
E 2
I 2
	if ((wbytes = write(fd, dpagep, lfsp->lfs_bsize)) < 0)
E 2
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != lfsp->lfs_bsize)
		fatal("%s: short write (%d, not %d)",
		    special, wbytes, lfsp->lfs_bsize);
E 3
I 3
	/* Write Supberblock */
	lfsp->lfs_offset = (off + lfsp->lfs_bsize) / lp->d_secsize;
	put(fd, LFS_LABELPAD, lfsp, sizeof(struct lfs));
E 3

D 3
	/* MIS -- probably want to replace with "write block code" */
	/* Now it's time to write the summary for the first segment. */
E 3
I 3
	/* 
	 * Finally, calculate all the fields for the summary structure
	 * and write it.
	 */

E 3
D 2
	summary.ss_next =
	    lfsp->lfs_sboffs[1] ? lfsp->lfs_sboffs[1] : lfsp->lfs_sboffs[0];
E 2
I 2
	summary.ss_next = lfsp->lfs_nextseg;
E 2
D 3
	summary.ss_prev = last_sb_addr;
	summary.ss_nextsum = -1;
E 3
	summary.ss_create = lfsp->lfs_tstamp;
D 2
	summary.ss_nfinfo = 2;
E 2
I 2
D 3
	summary.ss_nfinfo = 4;
E 2
	summary.ss_ninos = 1;
E 3
I 3
	summary.ss_nfinfo = 3;
	summary.ss_ninos = 3;
I 29
	summary.ss_magic = SS_MAGIC;
E 29
	summary.ss_datasum = cksum(datasump, sizeof(u_long) * blocks_used);
E 3

D 2
	/* Superblock and disk label */
E 2
I 2
D 3
	/* Superblock */
E 2
	file_info.fi_nblocks = LFS_SBPAD >> lfsp->lfs_bshift;
	file_info.fi_version = 1;
	file_info.fi_ino = LFS_UNUSED_INUM;

E 3
D 2
	/* Make sure that we don't overflow a summary block. */
	sum_size = 2*sizeof(FINFO) + sizeof(SEGSUM) +
	    file_info.fi_nblocks * sizeof(u_long) +
	    (lfsp->lfs_segtabsz + 1) * sizeof(u_long);
E 2
I 2
	/*
	 * Make sure that we don't overflow a summary block. We have to
D 3
	 * record: FINFO structures for superblock, ifile, root, l+f.
E 3
I 3
	 * record: FINFO structures for ifile, root, and l+f.  The number
	 * of blocks recorded for the ifile is determined by the size of
	 * the cleaner info and the segments usage table.  There is room
	 * for one block included in sizeof(FINFO) so we don't need to add
	 * any extra space for the ROOT and L+F, and one block of the ifile
	 * is already counted.  Finally, we leave room for 1 inode block
	 * address.
E 3
	 */
D 3
	sum_size = 4*sizeof(FINFO) + sizeof(SEGSUM) +
	    file_info.fi_nblocks * sizeof(u_long) +	/* sb blocks */
	    (lfsp->lfs_segtabsz + 1) * sizeof(u_long) +	/* ifile blocks */
	    2 * sizeof(u_long);				/* root and l+f block */
E 3
I 3
D 8
	sum_size = 3*sizeof(FINFO) + sizeof(SEGSUM) + sizeof(daddr_t);
E 8
I 8
	sum_size = 3*sizeof(FINFO) + sizeof(SEGSUM) + sizeof(daddr_t) +
E 8
	    (lfsp->lfs_cleansz + lfsp->lfs_segtabsz) * sizeof(u_long);
E 3
E 2
#define	SUMERR \
"Multiple summary blocks in segment 1 not yet implemented\nsummary is %d bytes."
	if (sum_size > LFS_SUMMARY_SIZE)
		fatal(SUMERR, sum_size);

D 3
	block_array_size = file_info.fi_nblocks;
	if ((lfsp->lfs_segtabsz + 1) > block_array_size)
		block_array_size = lfsp->lfs_segtabsz + 1;
E 3
I 3
		block_array_size = lfsp->lfs_cleansz + lfsp->lfs_segtabsz + 1;
E 3

	if (!(block_array = malloc(block_array_size *sizeof(int))))
		fatal("%s: %s", special, strerror(errno));

	/* fill in the array */
D 3
	for (i = 0; i < file_info.fi_nblocks; i++)
E 3
I 3
	for (i = 0; i < block_array_size; i++)
E 3
		block_array[i] = i;

	/* copy into segment */
D 3
	sump = pagep;
E 3
I 3
	sump = ipagep;
E 3
D 27
	bcopy(&summary, sump, sizeof(SEGSUM));
E 27
I 27
	memmove(sump, &summary, sizeof(SEGSUM));
E 27
	sump += sizeof(SEGSUM);
D 3
	bcopy(&file_info, sump, sizeof(FINFO) - sizeof(u_long));
	sump += sizeof(FINFO) - sizeof(u_long);
	bcopy(block_array, sump, sizeof(u_long) * file_info.fi_nblocks);
	sump += sizeof(u_long) * file_info.fi_nblocks;
E 3

	/* Now, add the ifile */
D 3
	file_info.fi_nblocks = lfsp->lfs_segtabsz + 1;
E 3
I 3
	file_info.fi_nblocks = block_array_size;
E 3
	file_info.fi_version = 1;
I 29
	file_info.fi_lastlength = lfsp->lfs_bsize;
E 29
	file_info.fi_ino = LFS_IFILE_INUM;

D 3
	for (i = 0; i < file_info.fi_nblocks; i++)
		block_array[i] = i;

E 3
D 27
	bcopy(&file_info, sump, sizeof(FINFO) - sizeof(u_long));
E 27
I 27
	memmove(sump, &file_info, sizeof(FINFO) - sizeof(u_long));
E 27
	sump += sizeof(FINFO) - sizeof(u_long);
D 27
	bcopy(block_array, sump, sizeof(u_long) * file_info.fi_nblocks);
E 27
I 27
	memmove(sump, block_array, sizeof(u_long) * file_info.fi_nblocks);
E 27
I 2
	sump += sizeof(u_long) * file_info.fi_nblocks;
E 2

I 2
	/* Now, add the root directory */
	file_info.fi_nblocks = 1;
	file_info.fi_version = 1;
I 29
	file_info.fi_lastlength = lfsp->lfs_bsize;
E 29
	file_info.fi_ino = ROOTINO;
	file_info.fi_blocks[0] = 0;
D 27
	bcopy(&file_info, sump, sizeof(FINFO));
E 27
I 27
	memmove(sump, &file_info, sizeof(FINFO));
E 27
	sump += sizeof(FINFO);

	/* Now, add the lost and found */
	file_info.fi_ino = LOSTFOUNDINO;
D 27
	bcopy(&file_info, sump, sizeof(FINFO));
E 27
I 27
	memmove(sump, &file_info, sizeof(FINFO));
E 27

I 3
	((daddr_t *)ipagep)[LFS_SUMMARY_SIZE / sizeof(daddr_t) - 1] = 
	    lfsp->lfs_idaddr;
	((SEGSUM *)ipagep)->ss_sumsum = cksum(ipagep+sizeof(summary.ss_sumsum), 
	    LFS_SUMMARY_SIZE - sizeof(summary.ss_sumsum));
	put(fd, LFS_LABELPAD + LFS_SBPAD, ipagep, LFS_SUMMARY_SIZE);
E 3

E 2
D 3
	sb_to_sum = (lfsp->lfs_ssize << lfsp->lfs_bshift) - LFS_SUMMARY_SIZE;
	((SEGSUM *)pagep)->ss_cksum = cksum(pagep+sizeof(summary.ss_cksum), 
	    LFS_SUMMARY_SIZE - sizeof(summary.ss_cksum));
	put(fd, LFS_LABELPAD + sb_to_sum, pagep, LFS_SUMMARY_SIZE);
E 3
I 3
	sp = (SEGSUM *)ipagep;
	sp->ss_create = 0;
	sp->ss_nfinfo = 0;
	sp->ss_ninos = 0;
	sp->ss_datasum = 0;
I 29
	sp->ss_magic = SS_MAGIC;
E 29
E 3

D 2
	summary.ss_nextsum = -1;
	summary.ss_create = 0;
	summary.ss_nfinfo = 1;
	summary.ss_ninos = 0;
E 2
I 2
D 3
	/* 
	 * The first FINFO structure from above is good, just need to change
	 * the pointers
	 */
	sp1 = (SEGSUM *)pagep;
	sp1->ss_nextsum = -1;
	sp1->ss_create = 0;
	sp1->ss_nfinfo = 1;
	sp1->ss_ninos = 0;
E 2

D 2
	/* Superblock */
	file_info.fi_nblocks = LFS_SBPAD >> lfsp->lfs_bshift;
	file_info.fi_version = 1;
	file_info.fi_ino = LFS_UNUSED_INUM;
E 2
I 2
	sp2 = (SEGSUM *)dpagep;
	sp2->ss_nextsum = -1;
	sp2->ss_create = 0;
	sp2->ss_nfinfo = 0;
	sp2->ss_ninos = 0;
E 2

E 3
D 2
	for (i = 0; i < file_info.fi_nblocks; i++)
		block_array[i] = i;

	sump = pagep;
	bcopy (&summary, sump, sizeof(SEGSUM));
	sump += sizeof(SEGSUM);
	bcopy(&file_info, sump, sizeof(FINFO) - sizeof(u_long));
	sump += sizeof(FINFO) - sizeof(u_long);
	bcopy(block_array, sump, sizeof(u_long) * file_info.fi_nblocks);

E 2
D 15
	/* Now, write rest of segments containing superblocks */
E 15
I 15
	/* Now write the summary block for the next partial so it's invalid */
E 15
	lfsp->lfs_tstamp = 0;
I 15
	off += lfsp->lfs_bsize;
	sp->ss_sumsum =
	    cksum(&sp->ss_datasum, LFS_SUMMARY_SIZE - sizeof(sp->ss_sumsum));
	put(fd, off, sp, LFS_SUMMARY_SIZE);

	/* Now, write rest of segments containing superblocks */
E 15
D 2
	for (sp = (SEGSUM *)pagep, i = 1; i < LFS_MAXNUMSB; i++) {
		if (!lfsp->lfs_sboffs[i])
			break;
		sp->ss_prev = lfsp->lfs_sboffs[i - 1];
		if (i < (LFS_MAXNUMSB - 1))
			sp->ss_next = lfsp->lfs_sboffs[i + 1];
		else
			sp->ss_next = lfsp->lfs_sboffs[0];
E 2
I 2
	lfsp->lfs_cksum = 
D 3
	    cksum(lfsp, sizeof(LFS) - sizeof(lfsp->lfs_cksum));
E 3
I 3
	    cksum(lfsp, sizeof(struct lfs) - sizeof(lfsp->lfs_cksum));
E 3
	for (seg_addr = last_addr = lfsp->lfs_sboffs[0], j = 1, i = 1; 
	    i < lfsp->lfs_nseg; i++) {
E 2

D 2
		/* Superblock */
		seg_seek = lfsp->lfs_sboffs[i] * lp->d_secsize;
		lfsp->lfs_cksum = 
		    cksum(lfsp, sizeof(LFS_SUPER) - sizeof(lfsp->lfs_cksum));
		put(fd, seg_seek, lfsp, sizeof(LFS_SUPER));
E 2
I 2
		seg_addr += lfsp->lfs_ssize << lfsp->lfs_fsbtodb;
D 3
		if (seg_addr == lfsp->lfs_sboffs[j]) {
			sp = sp1;		/* It's a superblock */
			if (j < (LFS_MAXNUMSB - 2))
				j++;
		} else
			sp = sp2;
E 2

E 3
I 2
		sp->ss_next = last_addr;
		last_addr = seg_addr;
D 3

E 3
		seg_seek = seg_addr * lp->d_secsize;
D 3
		if (sp == sp1)
			put(fd, seg_seek, lfsp, sizeof(LFS));
E 3

I 3
		if (seg_addr == lfsp->lfs_sboffs[j]) {
			if (j < (LFS_MAXNUMSB - 2))
				j++;
			put(fd, seg_seek, lfsp, sizeof(struct lfs));
			seg_seek += LFS_SBPAD;
		} 

E 3
E 2
		/* Summary */
D 2
		sp->ss_cksum = cksum(&sp->ss_cksum, 
E 2
I 2
D 3
		sp->ss_cksum = cksum(&sp->ss_next, 
E 2
		    LFS_SUMMARY_SIZE - sizeof(sp->ss_cksum));
D 2
		put(fd, sb_to_sum + seg_seek, pagep, LFS_SUMMARY_SIZE);
E 2
I 2
		put(fd, sb_to_sum + seg_seek, sp, LFS_SUMMARY_SIZE);
E 3
I 3
		sp->ss_sumsum = cksum(&sp->ss_datasum, 
		    LFS_SUMMARY_SIZE - sizeof(sp->ss_sumsum));
		put(fd, seg_seek, sp, LFS_SUMMARY_SIZE);
E 3
E 2
	}
D 2
	(void)free(pagep);
	(void)close(fd);
E 2
I 2
D 3
	free(dpagep);
	free(pagep);
E 3
I 3
	free(ipagep);
E 3
	close(fd);
E 2
	return (0);
}

static void
put(fd, off, p, len)
	int fd;
	off_t off;
	void *p;
	size_t len;
{
	int wbytes;

	if (lseek(fd, off, SEEK_SET) < 0)
		fatal("%s: %s", special, strerror(errno));
	if ((wbytes = write(fd, p, len)) < 0)
		fatal("%s: %s", special, strerror(errno));
	if (wbytes != len)
		fatal("%s: short write (%d, not %d)", special, wbytes, len);
I 2
}

/*
 * Create the root directory for this file system and the lost+found
 * directory.
 */

D 26
	u_long	d_ino;			/* inode number of entry */
	u_short	d_reclen;		/* length of this record */
	u_short	d_namlen;		/* length of string in d_name */
	char	d_name[MAXNAMLEN + 1];	/* name with length <= MAXNAMLEN */
E 26
I 13
void
E 13
lfsinit()
D 13
{
}
E 13
I 13
{}
E 13

static daddr_t
make_dinode(ino, dip, nblocks, saddr, lfsp)
	ino_t ino;				/* inode we're creating */
	struct dinode *dip;			/* disk inode */
	int nblocks;				/* number of blocks in file */
	daddr_t saddr;				/* starting block address */
D 3
	LFS *lfsp;				/* superblock */
E 3
I 3
	struct lfs *lfsp;			/* superblock */
E 3
{
	int db_per_fb, i;

	dip->di_nlink = 1;
D 14
	dip->di_blocks = nblocks;
E 14
I 14
	dip->di_blocks = nblocks << lfsp->lfs_fsbtodb;
E 14

D 15
	/* If we ever need something longer than 32 bits, this changes */
	dip->di_size = (dip->di_blocks << lfsp->lfs_bshift);
E 15
I 15
	dip->di_size = (nblocks << lfsp->lfs_bshift);
E 15
D 12
	dip->di_atime = dip->di_mtime = dip->di_ctime = lfsp->lfs_tstamp;
E 12
I 12
D 28
	dip->di_atime.ts_sec = dip->di_mtime.ts_sec =
	    dip->di_ctime.ts_sec = lfsp->lfs_tstamp;
	dip->di_atime.ts_nsec = dip->di_mtime.ts_nsec =
	    dip->di_ctime.ts_nsec = 0;
E 28
I 28
	dip->di_atime = dip->di_mtime = dip->di_ctime = lfsp->lfs_tstamp;
	dip->di_atimensec = dip->di_mtimensec = dip->di_ctimensec = 0;
E 28
E 12
D 22
	dip->di_inum = ino;
E 22
I 22
	dip->di_inumber = ino;
E 22

#define	SEGERR \
"File requires more than the number of direct blocks; increase block or segment size."
	if (NDADDR < nblocks)
		fatal("%s", SEGERR);

	/* Assign the block addresses for the ifile */
	db_per_fb = 1 << lfsp->lfs_fsbtodb;
D 14
	for (i = 0; i < dip->di_blocks; i++, saddr += db_per_fb)
E 14
I 14
	for (i = 0; i < nblocks; i++, saddr += db_per_fb)
E 14
		dip->di_db[i] = saddr;

	return (saddr);
}


/*
 * Construct a set of directory entries in "bufp".  We assume that all the
 * entries in protodir fir in the first DIRBLKSIZ.  
 */
static void
make_dir(bufp, protodir, entries)
	void *bufp;
	register struct direct *protodir;
	int entries;
{
	char *cp;
	int i, spcleft;

	spcleft = DIRBLKSIZ;
	for (cp = bufp, i = 0; i < entries - 1; i++) {
D 11
		protodir[i].d_reclen = DIRSIZ(&protodir[i]);
E 11
I 11
D 12
		protodir[i].d_reclen = DIRSIZ(0, &protodir[i]);
E 12
I 12
		protodir[i].d_reclen = DIRSIZ(NEWDIRFMT, &protodir[i]);
E 12
E 11
D 27
		bcopy(&protodir[i], cp, protodir[i].d_reclen);
E 27
I 27
		memmove(cp, &protodir[i], protodir[i].d_reclen);
E 27
		cp += protodir[i].d_reclen;
		if ((spcleft -= protodir[i].d_reclen) < 0)
			fatal("%s: %s", special, "directory too big");
	}
	protodir[i].d_reclen = spcleft;
D 11
	bcopy(&protodir[i], cp, DIRSIZ(&protodir[i]));
E 11
I 11
D 12
	bcopy(&protodir[i], cp, DIRSIZ(0, &protodir[i]));
E 12
I 12
D 27
	bcopy(&protodir[i], cp, DIRSIZ(NEWDIRFMT, &protodir[i]));
E 27
I 27
	memmove(cp, &protodir[i], DIRSIZ(NEWDIRFMT, &protodir[i]));
E 27
E 12
E 11
E 2
}
E 1
