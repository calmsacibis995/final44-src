/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)wafs.h	8.1 (Berkeley) 6/11/93
 */

/*
 * Each disk drive contains some number of file systems.
 *
 * A file system is described by its super-block.  The super-block is
 * critical data and is replicated every SB_INTERVAL WAFS_SBSIZE blocks
 * to protect from catastrophic loss.  This is done at `newfs' time and
 * the critical super-block data does not change, so the copies need not
 * be referenced further unless disaster strikes.
 *
 * The boot block and and first super blocks are given in absolute disk
 * addresses. The byte-offset forms are preferred, as they don't imply
 * a sector size.
 */

/* Number of SBSIZE units between superblocks */
#define WAFS_DEF_INTERVAL	1024
#define WAFS_DEF_INT_SHIFT	10

#define BBSIZE		8192
#define WAFS_SBSIZE		8192

/* Byte offset of boot block and first superblock */
#define	BBOFF		((off_t)(0))
#define	SBOFF		((off_t)(BBOFF + BBSIZE))

/* Sector address of boot block and first superblock */
#define	BBLOCK		((daddr_t)(0))
#define	SBLOCK		((daddr_t)(BBLOCK + BBSIZE / DEV_BSIZE))

/*
 * How to calculate if a block is a superlock.  First mask out the low
 * order bits of the disk address to convert it to a block address in
 * terms of superblocks.  Then take the resulting address modulo the
 * number of blocks between superblocks.  The offset inside a superblock
 * interval should be equal to the block address of the first superblock
 * located at SBOFF.
 * CHECK THIS
 */
#define is_sb(fs, addr)	\
    (((addr & (1 << fs->wafs_sb_shift) - 1) \
      & ((fs->wafs_interval << fs->wafs_sb_shift) - 1)) == \
      SBOFF >> fs->wafs_bshift)

/*
 * Compute the number of disk blocks (not file system blocks) between
 * two consecutive suberblocks.  int_shift defines the interval expressed
 * in numbers of superblocks, sbshift converts superblocks to file system
 * blocks, and fsbtodb converts file system blocks to disk blocks.
 */
#define SB_INTERVAL_DB(wp) \
	(1 << (wp)->wafs_int_shift + (wp)->wafs_sbshift + (wp)->wafs_fsbtodb)
/*
 * How to calculate the number of blocks between block address 1 and block
 * address 2.  Note that ba1 may be either less than or greater than ba2.
 */
#define diff(fs, a1, a2)	(a1 > a2 ? fs->wafs_dsize - a1 + a2 : a2 - a1)
/*
 * MINBSIZE is the smallest allowable block size.
 * Note that super blocks are always of size SBSIZE,
 * and that both SBSIZE and MAXBSIZE must be >= MINBSIZE.
 */
#define MINBSIZE	4096

/*
 * The path name on which the file system is mounted is maintained
 * in wafs_fsmnt. MAXMNTLEN defines the amount of space allocated in 
 * the super block for this name.
 */
#define MAXMNTLEN 512


/*
 * Super block for a write-ahead log file system.
 */
struct wafs {
	struct	wafs *wafs_link;		/* linked list of file systems */
	struct	wafs *wafs_rlink;		/* used for incore super blocks */
	long	wafs_magic;		/* magic number */
	long	wafs_version;		/* Version number */
	daddr_t	wafs_sblkno;		/* addr of super-block in filesys */
	u_long	wafs_interval;		/* interval between superlocks */
	u_long	wafs_int_shift;		/* shift for divide for wafs_interval */
	time_t 	wafs_time;    		/* last time written */
	time_t	wafs_rtime;		/* last read time */
	long	wafs_size;		/* number of blocks in fs */
	long	wafs_dsize;		/* size - num superblocks */
	long	wafs_bsize;		/* size of basic blocks in fs */
/* these are configuration parameters */
	long	wafs_minfree;		/* minimum percentage of free blocks */
	long	wafs_maxthreads;	/* maximum number of threads in log */
/* these fields can be computed from the others */
	long	wafs_bmask;		/* ``blkoff'' calc of blk offsets */
	long	wafs_bshift;		/* ``lblkno'' calc of logical blkno */
	long	wafs_fsbtodb;		/* fsbtodb and dbtofsb shift constant */
	long	wafs_sbsize;		/* actual size of super block */
	long	wafs_sbshift;		/* convert sb blocks to blocks */
	long	wafs_bfree;		/* number of free blocks */
	long	wafs_tinfopb;		/* Thread info per file system block */
/* these fields retain the current block allocation info */
	off_t	wafs_lsn;		/* last byte written in the log */
	off_t	wafs_check;		/* Last checkpoint record */
	off_t	wafs_head;		/* head of log */
	off_t	wafs_tail;		/* tail of log */
	long	wafs_state;		/* validate wafs_clean field */
/* these fields are cleared at mount time */
	u_char	wafs_inchkpt;		/* checkpoint in progress */
	u_char	wafs_fmod;    		/* super block modified flag */
	u_char	wafs_clean;    		/* file system is clean flag */
	u_char	wafs_ronly;   		/* mounted read-only flag */
	u_char	wafs_flags;   		/* currently unused flag */
	u_char	wafs_pad[3];		/* long align */
	u_char	wafs_fsmnt[MAXMNTLEN];	/* name mounted on */
	long	wafs_id;		/* unique ID for log correlation */
	long	wafs_cksum;		/* on-disk checksum */
};
/*
 * Filesystem idetification
 */
#define	WAFS_MAGIC	0x061561	/* the write-ahead log magic number */
#define	WAFS_DEF_VERSION	1	/* the write-ahead log magic number */

/* Flag values */
#define WAFS_MOD	1

/* Turn a number of file system blocks into a number of device sectors. */
#define fsbtodb(fs, b)	((b) << (fs)->wafs_fsbtodb)
#define	dbtofsb(fs, b)	((b) >> (fs)->wafs_fsbtodb)

/*
 * The following macros optimize certain frequently calculated
 * quantities by using shifts and masks in place of divisions
 * modulos and multiplications.
 */
#define blkoff(wafs, loc)	/* calculates (loc % fs->wafs_bsize) */ \
	((loc) & (wafs)->wafs_bmask)
#define lblktosize(wafs, blk)	/* calculates (blk * wafs->wafs_bsize) */ \
	((blk) << (wafs)->wafs_bshift)
#define lblkno(wafs, loc)	/* calculates (loc / wafs->wafs_bsize) */ \
	((loc) >> (wafs)->wafs_bshift)
#define blkroundup(wafs, size)	/* calculates roundup(size, fs->wafs_bsize) */ \
	(((size) + (wafs)->wafs_qbmask) & (wafs)->wafs_bmask)

/*
 * Number of disk sectors per block; assumes DEV_BSIZE byte sector size.
 */
#define	NSPB(wafs)	((wafs)->wafs_nspf << (wafs)->wafs_fragshift)

/*
 * Block difference macro (used to indicate log wrap).  Computes the
 * number of blocks between offset 1 and offset 2.
 */
#define BLOCK_DIFF(WP, OFF1, OFF2) (1 + lblkno(WP, OFF2 - OFF1))
/* Default superblock initialization values */
#define	WAFS_DEF_BSHIFT 12
#define	WAFS_DEF_BSIZE	4096
#define	WAFS_DEF_FSBTODB (WAFS_DEF_BSIZE / DEV_BSIZE)
#define WAFS_DEF_BMASK	0xFFF
#define	WAFS_DEF_SBLKNO	(SBOFF / WAFS_DEF_BSIZE)
#define	WAFS_DEF_MAX_THREADS		10

/* THIS SHOULD MOVE; thread information??? */
struct tinfo {
	int	info[32];
};
