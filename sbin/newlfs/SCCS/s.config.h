h44407
s 00006/00000/00108
d D 8.3 95/05/24 19:44:29 margo 7 6
c Add support for fragments.
e
s 00014/00000/00094
d D 8.2 94/04/22 12:14:45 mckusick 6 5
c copy in things needed from <ufs/ffs/fs.h>
e
s 00002/00002/00092
d D 8.1 93/06/05 11:07:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00093
d D 5.4 92/11/17 12:53:05 margo 4 3
c Allow segments of 64K (still need to be able to create indirect 
c blocks in newfs).
e
s 00001/00001/00093
d D 5.3 92/06/22 23:48:16 bostic 3 2
c fix DFL_LFSBLOCK_MASK
e
s 00001/00001/00093
d D 5.2 91/12/06 16:50:50 bostic 2 1
c update DFL_LFSSEG_MASK
e
s 00094/00000/00000
d D 5.1 91/09/19 10:18:45 bostic 1 0
c date and time created 91/09/19 10:18:45 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
I 6
 * The first boot and super blocks are given in absolute disk addresses.
 * The byte-offset forms are preferred, as they don't imply a sector size.
 */
#define BBSIZE		8192
#define SBSIZE		8192

/*
E 6
 * The following two constants set the default block and fragment sizes.
 * Both constants must be a power of 2 and meet the following constraints:
 *	MINBSIZE <= DESBLKSIZE <= MAXBSIZE
 *	sectorsize <= DESFRAGSIZE <= DESBLKSIZE
 *	DESBLKSIZE / DESFRAGSIZE <= 8
 */
#define	DFL_FRAGSIZE	1024
#define	DFL_BLKSIZE	8192

/*
 * Cylinder groups may have up to many cylinders. The actual
 * number used depends upon how much information can be stored
 * on a single cylinder. The default is to use 16 cylinders
 * per group.
 */
#define	DESCPG		16	/* desired fs_cpg */

/*
 * MINFREE gives the minimum acceptable percentage of file system
 * blocks which may be free. If the freelist drops below this level
 * only the superuser may continue to allocate blocks. This may
 * be set to 0 if no reserve of free blocks is deemed necessary,
 * however throughput drops by fifty percent if the file system
 * is run at between 90% and 100% full; thus the default value of
 * fs_minfree is 10%. With 10% free space, fragmentation is not a
 * problem, so we choose to optimize for time.
 */
#define MINFREE		10
#define DEFAULTOPT	FS_OPTTIME
I 6

/*
 * Preference for optimization.
 */
#define FS_OPTTIME	0	/* minimize allocation time */
#define FS_OPTSPACE	1	/* minimize disk fragmentation */

E 6

/*
 * ROTDELAY gives the minimum number of milliseconds to initiate
 * another disk transfer on the same cylinder. It is used in
 * determining the rotationally optimal layout for disk blocks
 * within a file; the default of fs_rotdelay is 4ms.
 */
#define ROTDELAY	4

/*
 * MAXCONTIG sets the default for the maximum number of blocks
 * that may be allocated sequentially. Since UNIX drivers are
 * not capable of scheduling multi-block transfers, this defaults
 * to 1 (ie no contiguous blocks are allocated).
 */
#define MAXCONTIG	1

/*
 * MAXBLKPG determines the maximum number of data blocks which are
 * placed in a single cylinder group. The default is one indirect
 * block worth of data blocks.
 */
#define MAXBLKPG(bsize)	((bsize) / sizeof(daddr_t))

/*
 * Each file system has a number of inodes statically allocated.
 * We allocate one inode slot per NFPI fragments, expecting this
 * to be far more than we will ever need.
 */
#define	NFPI		4

/*
 * For each cylinder we keep track of the availability of blocks at different
 * rotational positions, so that we can lay out the data to be picked
 * up with minimum rotational latency.  NRPOS is the default number of
 * rotational positions that we distinguish.  With NRPOS of 8 the resolution
 * of our summary information is 2ms for a typical 3600 rpm drive.
 */
#define	NRPOS		8	/* number distinct rotational positions */

/*
 * The following constants set the default block and segment size for a log
 * structured file system.  Both must be powers of two and the segment size
 * must be a multiple of the block size.  We also set minimum block and segment
 * sizes.
 */
D 4
#define	LFS_MINSEGSIZE		(128*1024)
E 4
I 4
#define	LFS_MINSEGSIZE		(64*1024)
E 4
#define	DFL_LFSSEG		(1024 * 1024)
#define	DFL_LFSSEG_SHIFT	20
D 2
#define	DFL_LFSSEG_MASK		0x7FFFF
E 2
I 2
#define	DFL_LFSSEG_MASK		0xFFFFF
E 2

#define	LFS_MINBLOCKSIZE	1024
#define	DFL_LFSBLOCK		4096
#define	DFL_LFSBLOCK_SHIFT	12
D 3
#define	DFL_LFSBLOCK_MASK	0x7FF
E 3
I 3
#define	DFL_LFSBLOCK_MASK	0xFFF
I 7

#define	DFL_LFSFRAG		4096
#define	DFL_LFS_FFMASK		DFL_LFSBLOCK_MASK
#define	DFL_LFS_FFSHIFT		DFL_LFSBLOCK_SHIFT
#define	DFL_LFS_FBMASK		0
#define DFL_LFS_FBSHIFT		0
E 7
E 3
E 1
