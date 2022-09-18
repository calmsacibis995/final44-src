h56655
s 00009/00009/00466
d D 8.13 95/03/21 00:53:23 mckusick 68 67
c daddr_t => ufs_daddr_t
e
s 00002/00002/00473
d D 8.12 95/01/02 23:35:33 mckusick 67 66
c minor cleanup
e
s 00005/00006/00470
d D 8.11 94/12/13 16:04:12 bostic 66 65
c nits (from mycroft)
e
s 00005/00002/00471
d D 8.10 94/10/27 20:39:53 mckusick 65 64
c add fs_maxcluster to track cluster sizes per cylinder group
e
s 00005/00005/00468
d D 8.9 94/08/14 16:12:35 mckusick 64 63
c rename fisrt field to be more descriptive
e
s 00142/00132/00331
d D 8.8 94/07/08 23:42:58 mckusick 63 62
c changes for 64-bit machines (from bostic)
e
s 00001/00001/00462
d D 8.7 94/04/19 07:51:33 bostic 62 61
c spelling
e
s 00015/00000/00448
d D 8.6 94/04/19 00:01:25 mckusick 61 60
c move in definition of MINFREE from newfs so it can be used by tunefs(8)
e
s 00002/00001/00446
d D 8.5 94/02/27 00:43:59 mkm 60 59
c including cluster map info in CGSIZE is dependent on fs->fs_contigsumsize
e
s 00015/00000/00432
d D 8.4 94/02/01 23:46:15 mkm 59 58
c CGSIZE macro moves in from mkfs.c (for use by fsck in converting filesystems)
e
s 00018/00002/00414
d D 8.3 94/02/01 20:01:04 mkm 58 57
c add fields for improving cluster allocation
e
s 00009/00009/00407
d D 8.2 93/09/23 16:11:23 bostic 57 56
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00414
d D 8.1 93/06/11 16:21:43 bostic 56 55
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00414
d D 7.17 92/06/21 14:35:25 mckusick 55 54
c add fs_maxsymlinklen
e
s 00016/00010/00399
d D 7.16 92/06/04 22:51:05 mckusick 54 53
c add new fields for inode format
e
s 00003/00000/00406
d D 7.15 92/05/27 22:57:57 mckusick 53 52
c declarations needed by utilities moved from ffs_extern.h to fs.h
e
s 00002/00002/00404
d D 7.14 91/12/19 12:45:21 mckusick 52 51
c quad => quad_t
e
s 00000/00008/00406
d D 7.13 91/11/01 16:52:49 bostic 51 50
c UFS/FFS split for LFS version 1; move ROOTINO into ufsmount.h
e
s 00001/00001/00413
d D 7.12 91/05/08 18:08:33 mckusick 50 49
c minor nits
e
s 00000/00004/00414
d D 7.11 90/10/24 11:37:15 mckusick 49 48
c lint
e
s 00001/00011/00417
d D 7.10 90/06/28 22:29:37 bostic 48 47
c new copyright notice
e
s 00003/00001/00425
d D 7.9 90/04/03 16:39:36 mckusick 47 46
c add fs_state field to validate fs_clean
e
s 00002/00000/00424
d D 7.8 90/01/13 21:05:24 mckusick 46 45
c new macro to calculate multiplication by fs_bsize
e
s 00001/00002/00423
d D 7.7 89/05/09 17:10:38 mckusick 45 44
c lint
e
s 00010/00005/00415
d D 7.6 88/06/27 18:51:31 bostic 44 43
c install approved copyright notice
e
s 00008/00002/00412
d D 7.5 88/05/23 20:12:02 bostic 43 42
c added Berkeley specific header
e
s 00080/00057/00334
d D 7.4 88/05/01 23:52:52 mckusick 42 40
c convert cylinder groups to have dynamic arrays;
c provide macros to access the dynamic arrays
e
s 00002/00001/00390
d R 7.4 87/09/09 16:12:47 mckusick 41 40
c allow cg's to start at frag instead of block boundries
e
s 00005/00001/00386
d D 7.3 87/04/02 15:36:24 karels 40 38
c working again
e
s 00007/00001/00386
d D 7.2.1.1 87/04/02 15:17:35 karels 39 38
c ifdef for dev_bsize
e
s 00013/00004/00374
d D 7.2 87/01/13 18:05:02 mckusick 38 37
c add trackskew, interleave, npsect, headswitch, and trackseek
c use first three to more completely calculate rotational position
c reduce size of fs_fsmnt to make space for more spare constants
e
s 00001/00001/00377
d D 7.1 86/06/04 23:23:02 mckusick 37 36
c 4.3BSD release version
e
s 00002/00002/00376
d D 6.6 86/05/02 11:21:06 mckusick 36 35
c some disks put bad sector replacements at the end of each cylinder,
c so one cannot assume that (tracks * sectors) == fs_spc
e
s 00007/00001/00371
d D 6.5 85/09/11 21:13:53 mckusick 35 34
c add optimization preference field
e
s 00007/00001/00365
d D 6.4 85/06/08 14:57:43 mckusick 34 33
c Add copyright
e
s 00003/00003/00363
d D 6.3 85/02/08 19:52:35 mckusick 33 32
c fix comment; parenthesize use of args in blkmap() macro
e
s 00004/00000/00362
d D 6.2 84/09/28 15:49:27 mckusick 32 31
c add macros to manipulate fragments
e
s 00000/00000/00362
d D 6.1 83/07/29 06:12:22 sam 31 30
c 4.2 distribution
e
s 00014/00002/00348
d D 4.8 83/03/21 19:55:20 sam 30 29
c add freespace macro and macros which use fs_fragshift
e
s 00016/00050/00334
d D 4.7 83/01/09 19:10:23 mckusick 29 28
c speed-ups using the new constants
e
s 00009/00001/00375
d D 4.6 83/01/02 14:43:16 mckusick 28 26
c add new useful constants
e
s 00010/00001/00375
d R 4.6 83/01/02 13:30:42 mckusick 27 26
c make provision for new constants
e
s 00003/00001/00373
d D 4.5 82/11/13 23:08:11 sam 26 25
c merge 4.1b and 4.1c
e
s 00001/00001/00373
d D 4.4 82/10/17 21:42:54 root 25 24
c cg_free is (u_char)
e
s 00000/00002/00374
d D 4.3 82/10/10 17:12:15 root 24 23
c header file cleanup while moving vax files to their own directory
e
s 00001/00000/00375
d D 4.2 82/06/14 22:54:06 root 23 22
c mountfs declared
e
s 00001/00001/00374
d D 4.1 82/04/19 19:29:49 mckusic 22 21
c bring up to version 4.1
e
s 00001/00001/00374
d D 2.4 82/04/19 19:27:16 mckusic 21 20
c merge in the new file system
e
s 00008/00004/00367
d D 2.3 82/04/12 20:26:57 mckusick 20 19
c add link fields to fs and cg, move magic number to end of struct
e
s 00032/00036/00339
d D 2.2 82/04/11 17:03:33 mckusick 19 18
c float the cylinder group info => no extra boot blocks, spare super
c blocks are placed on separate tracks (hence spiral down through cyl groups)
e
s 00000/00000/00375
d D 2.1 82/03/25 01:04:43 mckusick 18 17
c put into the kernel!
e
s 00001/00001/00374
d D 1.17 82/03/25 01:01:11 mckusick 17 16
c increase boot block to 8K
e
s 00005/00001/00370
d D 1.16 82/03/24 23:39:15 mckusick 16 15
c update with the current system on monet
e
s 00027/00017/00344
d D 1.15 82/03/23 14:43:48 mckusick 15 14
c incorporate sam's changes
e
s 00026/00004/00335
d D 1.14 82/02/25 14:49:58 mckusic 14 13
c define speed-up macros
e
s 00013/00013/00326
d D 1.13 82/01/12 22:13:48 mckusic 13 12
c change all macros taking "fs" to have it as their first argument
e
s 00012/00031/00327
d D 1.12 82/01/12 19:36:52 mckusic 12 11
c add cg_btot to summarize cg_b
e
s 00049/00037/00309
d D 1.11 82/01/10 18:20:52 mckusic 11 10
c fix rotational layout code to work with disks with nsect % bsize != 0
e
s 00185/00086/00161
d D 1.10 82/01/06 23:26:42 mckusic 10 9
c take in stuffed moved out of param.h
e
s 00078/00044/00169
d D 1.9 82/01/05 01:22:32 mckusic 9 8
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00001/00001/00212
d D 1.8 81/12/09 15:29:17 mckusic 8 7
c lint cleanup
e
s 00001/00007/00212
d D 1.7 81/11/19 22:41:03 mckusic 7 6
c conversion of ino_t from u_short to u_long (making dir entries 32 bytes each)
e
s 00023/00027/00196
d D 1.6 81/11/07 16:45:37 mckusic 6 5
c reorganize and remove some restrictions on sizes
e
s 00005/00002/00218
d D 1.5 81/10/31 19:49:01 mckusic 5 4
c to be compatible with past dump tapes ROOTINO is 2 not 1
e
s 00018/00015/00202
d D 1.4 81/10/29 00:30:14 mckusic 4 3
c put in optimal rotational block allocation
e
s 00001/00001/00216
d D 1.3 81/10/07 18:30:35 mckusic 3 2
c fix unsigned char problem to get FRAG == 8 to work
e
s 00004/00000/00213
d D 1.2 81/10/05 20:42:58 mckusic 2 1
c maintaining and using cg_frsum to do intelligent allocation of FRAGs
e
s 00213/00000/00000
d D 1.1 81/09/09 16:50:25 mckusick 1 0
c date and time created 81/09/09 16:50:25 by mckusick
e
u
U
f b 
t
T
I 1
D 24
/* Copyright (c) 1981 Regents of the University of California */

E 24
D 21
/*	%M%	%I%	%G%	*/
E 21
I 21
D 22
/*	fs.h	2.3	4/12/82	*/
E 22
I 22
D 34
/*	%M%	%I%	%E%	*/
E 34
I 34
/*
D 37
 * Copyright (c) 1982 Regents of the University of California.
E 37
I 37
D 56
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 37
D 43
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 43
I 43
 * All rights reserved.
E 56
I 56
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 56
 *
D 48
 * Redistribution and use in source and binary forms are permitted
D 44
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 44
I 44
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 45
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 45
I 45
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 48
I 48
 * %sccs.include.redist.c%
E 48
E 45
E 44
E 43
 *
 *	%W% (Berkeley) %G%
 */
E 34
E 22
E 21

/*
 * Each disk drive contains some number of file systems.
 * A file system consists of a number of cylinder groups.
 * Each cylinder group has inodes and data.
 *
 * A file system is described by its super-block, which in turn
 * describes the cylinder groups.  The super-block is critical
 * data and is replicated in each cylinder group to protect against
D 42
 * catastrophic loss.  This is done at mkfs time and the critical
E 42
I 42
 * catastrophic loss.  This is done at `newfs' time and the critical
E 42
 * super-block data does not change, so the copies need not be
 * referenced further unless disaster strikes.
 *
D 11
 * For file system fs and a cylinder group number cg:
D 10
 *	[BBLOCK]	Boot sector and bad block information
E 10
I 10
 *	[BBLOCK]	Boot sector
E 10
 *	[SBLOCK]	Super-block
D 9
 *	[CBLOCK]	Cylinder group block
 *	[IBLOCK..IBLOCK+fs.fs_ipg/INOPB)
E 9
I 9
 *	[CBLOCK(fs)]	Cylinder group block
 *	[IBLOCK(fs)..IBLOCK(fs)+fs.fs_ipg/INOPB(fs))
E 9
 *			Inode blocks
D 9
 *	[IBLOCK+fs.fs_ipg/INOPB..fs.fs_fpg/FRAG)
E 9
I 9
 *	[IBLOCK(fs)+fs.fs_ipg/INOPB(fs)..fs.fs_fpg/fs.fs_frag)
E 9
 *			Data blocks
D 9
 * The beginning of data blocks for cg in fs is also given by cgdmin(cg,fs).
E 9
I 9
 * The beginning of data blocks for cg in fs is also given by
 * the ``cgdmin(cg,fs)'' macro.
E 11
I 11
 * For file system fs, the offsets of the various blocks of interest
 * are given in the super block as:
D 19
 *	[fs->fs_bblkno]		Boot sector
E 19
 *	[fs->fs_sblkno]		Super-block
 *	[fs->fs_cblkno]		Cylinder group block
 *	[fs->fs_iblkno]		Inode blocks
 *	[fs->fs_dblkno]		Data blocks
 * The beginning of cylinder group cg in fs, is given by
D 13
 * the ``cgbase(cg, fs)'' macro.
E 13
I 13
 * the ``cgbase(fs, cg)'' macro.
E 13
E 11
 *
D 11
 * The boot and super blocks are given in absolute disk addresses.
E 11
I 11
 * The first boot and super blocks are given in absolute disk addresses.
I 40
 * The byte-offset forms are preferred, as they don't imply a sector size.
E 40
I 39
 * The byte-offset forms are preferred, as they don't imply a sector size.
E 39
E 11
E 9
 */
D 9
#define	BBLOCK	((daddr_t)(0*FRAG))
#define	SBLOCK	((daddr_t)(1*FRAG))
#define	CBLOCK	((daddr_t)(2*FRAG))
#define	IBLOCK	((daddr_t)(3*FRAG))
E 9
I 9
D 10
#define	BBLOCK		((daddr_t)(0 * (MAXBSIZE / DEV_BSIZE)))
#define	SBLOCK		((daddr_t)(1 * (MAXBSIZE / DEV_BSIZE)))
E 10
I 10
D 17
#define BBSIZE		1024
E 17
I 17
#define BBSIZE		8192
E 17
#define SBSIZE		8192
I 40
#define	BBOFF		((off_t)(0))
#define	SBOFF		((off_t)(BBOFF + BBSIZE))
E 40
I 39
#define	BBOFF		((off_t)(0))
#define	SBOFF		((off_t)(BBOFF + BBSIZE))
#ifndef SECSIZE
E 39
D 68
#define	BBLOCK		((daddr_t)(0))
#define	SBLOCK		((daddr_t)(BBLOCK + BBSIZE / DEV_BSIZE))
E 68
I 68
#define	BBLOCK		((ufs_daddr_t)(0))
#define	SBLOCK		((ufs_daddr_t)(BBLOCK + BBSIZE / DEV_BSIZE))
E 68
I 39
#endif SECSIZE
E 39
E 10
D 11
/*
 * The cylinder group and inode blocks are given in file system
 * addresses, and hence must be converted to disk addresses by
 * the ``fsbtodb(fs, bno)'' macro.
 */
D 10
#define	CBLOCK(fs)	((daddr_t)(dbtofsb(fs, 2 * (MAXBSIZE / DEV_BSIZE))))
E 10
I 10
#define	CBLOCK(fs) \
  ((daddr_t)(roundup(howmany(BBSIZE + SBSIZE, (fs)->fs_fsize), (fs)->fs_frag)))
E 10
#define	IBLOCK(fs)	((daddr_t)(CBLOCK(fs) + (fs)->fs_frag))
E 11
E 9

/*
D 9
 * Addresses stored in inodes are capable of addressing fragments of `blocks.'
 * File system blocks of size BSIZE can be broken into FRAG pieces,
 * each of which is addressible; these pieces may be sectors, or some
 * multiple of a sector size (e.g. 1k byte units).
E 9
I 9
 * Addresses stored in inodes are capable of addressing fragments
 * of `blocks'. File system blocks of at most size MAXBSIZE can 
 * be optionally broken into 2, 4, or 8 pieces, each of which is
 * addressible; these pieces may be DEV_BSIZE, or some multiple of
 * a DEV_BSIZE unit.
E 9
 *
D 9
 * Large files consist of exclusively large (BSIZE) data blocks.  To avoid
 * undue fragmentation, the last data block of a small file may be
 * allocated as only as many pieces
 * of a large block as are necessary.  The file system format retains
 * only a single pointer to such a fragment, which is a piece of a single
 * BSIZE block which has been divided.  The size of such a fragment is
 * determinable from information in the inode.
E 9
I 9
 * Large files consist of exclusively large data blocks.  To avoid
 * undue wasted disk space, the last data block of a small file may be
 * allocated as only as many fragments of a large block as are
 * necessary.  The file system format retains only a single pointer
 * to such a fragment, which is a piece of a single large block that
 * has been divided.  The size of such a fragment is determinable from
 * information in the inode, using the ``blksize(fs, ip, lbn)'' macro.
E 9
 *
 * The file system records space availability at the fragment level;
 * to determine block availability, aligned fragments are examined.
D 4
 */ 
E 4
I 4
D 51
 *
I 10
 * The root inode is the root of the file system.
 * Inode 0 can't be used for normal purposes and
 * historically bad blocks were linked to inode 1,
 * thus the root inode is 2. (inode 1 is no longer used for
 * this purpose, however numerous dump tapes make this
 * assumption, so we are stuck with it)
E 51
D 42
 * The lost+found directory is given the next available
 * inode when it is created by ``mkfs''.
E 42
 */
D 50
#define	ROOTINO		((ino_t)2)	/* i number of all roots */
E 50
I 50
D 51
#define	ROOTINO		((ino_t)2)
E 51
E 50
D 42
#define LOSTFOUNDINO	(ROOTINO + 1)
E 42

/*
D 29
 * MINFREE gives the minimum acceptable percentage of file system
 * blocks which may be free. If the freelist drops below this level
 * only the superuser may continue to allocate blocks. This may
 * be set to 0 if no reserve of free blocks is deemed necessary,
 * however severe performance degredations will be observed if the
 * file system is run at greater than 90% full; thus the default
 * value of fs_minfree is 10%.
 *
 * Empirically the best trade-off between block fragmentation and
 * overall disk utilization at a loading of 90% comes with a
 * fragmentation of 4, thus the default fragment size is a fourth
 * of the block size.
 */
#define MINFREE		10
#define DESFRAG		4

/*
 * Under current technology, most 300MB disks have 32 sectors and
D 19
 * 19 tracks, thus these are the defaults used for fs_nsect and 
E 19
I 19
 * 16 tracks, thus these are the defaults used for fs_nsect and 
E 19
 * fs_ntrak respectively.
 */
#define DFLNSECT	32
D 19
#define DFLNTRAK	19
E 19
I 19
#define DFLNTRAK	16
E 19

/*
E 29
D 42
 * Cylinder group related limits.
 *
E 10
 * For each cylinder we keep track of the availability of blocks at different
 * rotational positions, so that we can lay out the data to be picked
 * up with minimum rotational latency.  NRPOS is the number of rotational
 * positions which we distinguish.  With NRPOS 8 the resolution of our
 * summary information is 2ms for a typical 3600 rpm drive.
I 10
D 29
 *
 * ROTDELAY gives the minimum number of milliseconds to initiate
 * another disk transfer on the same cylinder. It is used in
 * determining the rotationally optimal layout for disk blocks
 * within a file; the default of fs_rotdelay is 2ms.
E 29
E 10
 */
D 10
#define	NRPOS	8		/* number distinct rotational positions */
E 10
I 10
#define	NRPOS		8	/* number distinct rotational positions */
D 29
#define ROTDELAY	2
E 29
E 10
E 4

/*
D 10
 * Information per cylinder group summarized in blocks allocated
 * from first cylinder group data blocks.  These blocks have to be
D 9
 * specially noticed in mkfs, icheck and fsck.
E 9
I 9
 * read in from fs_csaddr (size fs_cssize) in addition to the
 * super block.
 * N.B. sizeof(struct csum) must be a power of two in order for
 * the ``fs_cs'' macro to work (see below).
E 9
 */
struct csum {
D 6
	short	cs_ndir;	/* number of directories */
	short	cs_nbfree;	/* number of free blocks */
	short	cs_nifree;	/* number of free inodes */
	short	cs_xx;		/* for later use... */
E 6
I 6
	long	cs_ndir;	/* number of directories */
	long	cs_nbfree;	/* number of free blocks */
	long	cs_nifree;	/* number of free inodes */
	long	cs_nffree;	/* number of free frags */
E 6
};
D 9
#define	cssize(fs)	((fs)->fs_ncg*sizeof(struct csum))
#define	csaddr(fs)	(cgdmin(0, fs))
E 9

/*
E 10
D 29
 * Each file system has a number of inodes statically allocated.
D 10
 * We allocate one inode slot per NBPI data bytes, expecting this
E 10
I 10
 * We allocate one inode slot per NBPI bytes, expecting this
E 10
D 7
 * to be far more than we will ever need.  Actually, the directory
 * structure has inode numbers kept in 16 bits, so no more than
 * 65K inodes are possible, and this usually cuts off well above
 * the number suggested by NBPI.
 * 
 * THE DIRECTORY STRUCTURE SHOULD BE CHANGED SOON TO ALLOW
 * LARGER INODE NUMBERS (SEE DIR.H).
E 7
I 7
 * to be far more than we will ever need.
I 10
 *
E 29
 * MAXIPG bounds the number of inodes per cylinder group, and
 * is needed only to keep the structure simpler by having the
 * only a single variable size element (the free bit map).
 *
 * N.B.: MAXIPG must be a multiple of INOPB(fs).
E 10
E 7
 */
D 10
#define	NBPI	2048
E 10
I 10
D 29
#define	NBPI		2048
E 29
#define	MAXIPG		2048	/* max number inodes/cyl group */
E 10

D 4
#define	DESCPG	8			/* desired fs_cpg */
#define	MAXCPG	16			/* maximum fs_cpg */
E 4
I 4
D 9
#define	DESCPG	16			/* desired fs_cpg */
#define	MAXCPG	32			/* maximum fs_cpg */
E 4
/* MAXCPG is limited only to dimension an array in (struct cg); */
/* it can be made larger as long as that structures size remains sane. */
E 9
I 9
/*
E 42
 * MINBSIZE is the smallest allowable block size.
 * In order to insure that it is possible to create files of size
 * 2^32 with only two levels of indirection, MINBSIZE is set to 4096.
 * MINBSIZE must be big enough to hold a cylinder group block,
 * thus changes to (struct cg) must keep its size within MINBSIZE.
D 42
 * MAXCPG is limited only to dimension an array in (struct cg);
 * it can be made larger as long as that structures size remains
 * within the bounds dictated by MINBSIZE.
E 42
D 33
 * Note that super blocks are always of size MAXBSIZE,
 * and that MAXBSIZE must be >= MINBSIZE.
E 33
I 33
 * Note that super blocks are always of size SBSIZE,
 * and that both SBSIZE and MAXBSIZE must be >= MINBSIZE.
E 33
 */
#define MINBSIZE	4096
D 29
#define	DESCPG		16	/* desired fs_cpg */
E 29
D 42
#define	MAXCPG		32	/* maximum fs_cpg */
E 42
E 9
D 10
 
E 10
I 10

E 10
/*
I 15
 * The path name on which the file system is mounted is maintained
 * in fs_fsmnt. MAXMNTLEN defines the amount of space allocated in 
 * the super block for this name.
I 63
 */
#define MAXMNTLEN	512

/*
E 63
I 16
 * The limit on the amount of summary information per file system
D 19
 * is defined by MAXCSBUFS. It is currently parameterized for 1Meg
 * cylinders maximum.
E 19
I 19
 * is defined by MAXCSBUFS. It is currently parameterized for a
D 63
 * maximum of two million cylinders.
E 63
I 63
 * size of 128 bytes (2 million cylinder groups on machines with
D 65
 * 32-bit pointers, and 1 million on 64-bit machines).
E 65
I 65
 * 32-bit pointers, and 1 million on 64-bit machines). One pointer
 * is taken away to point to an array of cluster sizes that is
 * computed as cylinder groups are inspected.
E 65
E 63
E 19
E 16
 */
D 19
#define MAXMNTLEN 34
I 16
#define MAXCSBUFS 16
E 19
I 19
D 38
#define MAXMNTLEN 512
E 38
I 38
D 42
#define MAXMNTLEN 384
E 42
I 42
D 63
#define MAXMNTLEN 512
E 42
E 38
#define MAXCSBUFS 32
E 63
I 63
D 65
#define	MAXCSBUFS	(128 / sizeof(void *))
E 65
I 65
#define	MAXCSBUFS	((128 / sizeof(void *)) - 1)
E 65
E 63
E 19
E 16

/*
I 58
 * A summary of contiguous blocks of various sizes is maintained
 * in each cylinder group. Normally this is set by the initial
 * value of fs_maxcontig. To conserve space, a maximum summary size
 * is set by FS_MAXCONTIG.
 */
#define FS_MAXCONTIG	16

/*
I 61
 * MINFREE gives the minimum acceptable percentage of file system
 * blocks which may be free. If the freelist drops below this level
 * only the superuser may continue to allocate blocks. This may
 * be set to 0 if no reserve of free blocks is deemed necessary,
 * however throughput drops by fifty percent if the file system
 * is run at between 95% and 100% full; thus the minimum default
 * value of fs_minfree is 5%. However, to get good clustering
 * performance, 10% is a better choice. hence we use 10% as our
 * default value. With 10% free space, fragmentation is not a
 * problem, so we choose to optimize for time.
 */
#define MINFREE		5
#define DEFAULTOPT	FS_OPTTIME

/*
E 61
E 58
E 15
D 10
 * Super block for a file system.
E 10
I 10
 * Per cylinder group information; summarized in blocks allocated
 * from first cylinder group data blocks.  These blocks have to be
 * read in from fs_csaddr (size fs_cssize) in addition to the
 * super block.
E 10
 *
D 9
 * The super block is nominally located at disk block 1 although
 * this is naive due to bad blocks.  Inode 0 can't be used for normal
D 5
 * purposes, thus the root inode is inode 1.
E 5
I 5
 * purposes, historically bad blocks were linked to inode 1,
E 9
I 9
D 10
 * The super block is nominally located at disk block SBLOCK.
 * Inode 0 can't be used for normal purposes,
 * historically bad blocks were linked to inode 1,
E 9
 * thus the root inode is 2. (inode 1 is no longer used for
 * this purpose, however numerous dump tapes make this
 * assumption, so we are stuck with it)
E 10
I 10
 * N.B. sizeof(struct csum) must be a power of two in order for
 * the ``fs_cs'' macro to work (see below).
E 10
E 5
 */
D 5
#define	ROOTINO	((ino_t)1)	/* i number of all roots */
E 5
I 5
D 10
#define	ROOTINO	((ino_t)2)	/* i number of all roots */
E 10
I 10
struct csum {
D 63
	long	cs_ndir;	/* number of directories */
	long	cs_nbfree;	/* number of free blocks */
	long	cs_nifree;	/* number of free inodes */
	long	cs_nffree;	/* number of free frags */
E 63
I 63
	int32_t	cs_ndir;		/* number of directories */
	int32_t	cs_nbfree;		/* number of free blocks */
	int32_t	cs_nifree;		/* number of free inodes */
	int32_t	cs_nffree;		/* number of free frags */
E 63
};
E 10
E 5

I 10
/*
D 63
 * Super block for a file system.
E 63
I 63
 * Super block for an FFS file system.
E 63
 */
E 10
D 20
#define	FS_MAGIC	0x110854
E 20
I 20
D 54
#define	FS_MAGIC	0x011954
I 47
#define	FSOKAY		0x7c269d38
E 47
E 20
struct	fs
{
E 54
I 54
struct fs {
E 54
D 20
	long	fs_magic;		/* magic number */
E 20
I 20
D 63
	struct	fs *fs_link;		/* linked list of file systems */
	struct	fs *fs_rlink;		/*     used for incore super blocks */
E 20
D 11
	daddr_t	fs_sblkno;		/* offset of super-block in filesys */
E 11
I 11
D 19
	daddr_t	fs_bblkno;		/* abs addr of boot-block in filesys */
	daddr_t	fs_sblkno;		/* abs addr of super-block in filesys */
E 19
I 19
	daddr_t	fs_sblkno;		/* addr of super-block in filesys */
E 19
	daddr_t	fs_cblkno;		/* offset of cyl-block in filesys */
	daddr_t	fs_iblkno;		/* offset of inode-blocks in filesys */
D 19
	daddr_t	fs_dblkno;		/* offset of data-blocks in filesys */
E 19
I 19
	daddr_t	fs_dblkno;		/* offset of first data after cg */
	long	fs_cgoffset;		/* cylinder group offset in cylinder */
	long	fs_cgmask;		/* used to calc mod fs_ntrak */
E 19
E 11
	time_t 	fs_time;    		/* last time written */
D 6
	daddr_t	fs_size;		/* number of blocks in fs */
	short	fs_ncg;			/* number of cylinder groups */
E 6
I 6
	long	fs_size;		/* number of blocks in fs */
	long	fs_dsize;		/* number of data blocks in fs */
	long	fs_ncg;			/* number of cylinder groups */
I 9
	long	fs_bsize;		/* size of basic blocks in fs */
	long	fs_fsize;		/* size of frag blocks in fs */
D 11
	long	fs_frag;		/* number of frags in a block in fs */
E 11
I 11
D 19
	short	fs_frag;		/* number of frags in a block in fs */
E 11
	short	fs_minfree;		/* minimum percentage of free blocks */
	short	fs_rotdelay;		/* num of ms for optimal next block */
I 11
	short	fs_rps;			/* disk revolutions per second */
E 19
I 19
	long	fs_frag;		/* number of frags in a block in fs */
E 63
I 63
D 64
	int32_t	 unused_1;		/* historic file system linked list, */
	int32_t	 unused_2;		/*     used for incore super blocks */
E 64
I 64
	int32_t	 fs_firstfield;		/* historic file system linked list, */
	int32_t	 fs_unused_1;		/*     used for incore super blocks */
E 64
D 68
	daddr_t	 fs_sblkno;		/* addr of super-block in filesys */
	daddr_t	 fs_cblkno;		/* offset of cyl-block in filesys */
	daddr_t	 fs_iblkno;		/* offset of inode-blocks in filesys */
	daddr_t	 fs_dblkno;		/* offset of first data after cg */
E 68
I 68
	ufs_daddr_t fs_sblkno;		/* addr of super-block in filesys */
	ufs_daddr_t fs_cblkno;		/* offset of cyl-block in filesys */
	ufs_daddr_t fs_iblkno;		/* offset of inode-blocks in filesys */
	ufs_daddr_t fs_dblkno;		/* offset of first data after cg */
E 68
	int32_t	 fs_cgoffset;		/* cylinder group offset in cylinder */
	int32_t	 fs_cgmask;		/* used to calc mod fs_ntrak */
	time_t 	 fs_time;		/* last time written */
	int32_t	 fs_size;		/* number of blocks in fs */
	int32_t	 fs_dsize;		/* number of data blocks in fs */
	int32_t	 fs_ncg;		/* number of cylinder groups */
	int32_t	 fs_bsize;		/* size of basic blocks in fs */
	int32_t	 fs_fsize;		/* size of frag blocks in fs */
	int32_t	 fs_frag;		/* number of frags in a block in fs */
E 63
I 29
/* these are configuration parameters */
E 29
D 63
	long	fs_minfree;		/* minimum percentage of free blocks */
	long	fs_rotdelay;		/* num of ms for optimal next block */
	long	fs_rps;			/* disk revolutions per second */
E 63
I 63
	int32_t	 fs_minfree;		/* minimum percentage of free blocks */
	int32_t	 fs_rotdelay;		/* num of ms for optimal next block */
	int32_t	 fs_rps;		/* disk revolutions per second */
E 63
I 29
/* these fields can be computed from the others */
E 29
E 19
I 14
D 63
	long	fs_bmask;		/* ``blkoff'' calc of blk offsets */
	long	fs_fmask;		/* ``fragoff'' calc of frag offsets */
D 19
	short	fs_bshift;		/* ``lblkno'' calc of logical blkno */
	short	fs_fshift;		/* ``numfrags'' calc number of frags */
E 19
I 19
	long	fs_bshift;		/* ``lblkno'' calc of logical blkno */
	long	fs_fshift;		/* ``numfrags'' calc number of frags */
E 63
I 63
	int32_t	 fs_bmask;		/* ``blkoff'' calc of blk offsets */
	int32_t	 fs_fmask;		/* ``fragoff'' calc of frag offsets */
	int32_t	 fs_bshift;		/* ``lblkno'' calc of logical blkno */
	int32_t	 fs_fshift;		/* ``numfrags'' calc number of frags */
E 63
I 29
/* these are configuration parameters */
E 29
D 26
	long	fs_sparecon[16];	/* reserved for future constants */
E 26
I 26
D 63
	long	fs_maxcontig;		/* max number of contiguous blks */
	long	fs_maxbpg;		/* max number of blks per cyl group */
E 63
I 63
	int32_t	 fs_maxcontig;		/* max number of contiguous blks */
	int32_t	 fs_maxbpg;		/* max number of blks per cyl group */
E 63
I 29
/* these fields can be computed from the others */
E 29
D 28
	long	fs_sparecon[14];	/* reserved for future constants */
E 28
I 28
D 63
	long	fs_fragshift;		/* block to frag shift */
	long	fs_fsbtodb;		/* fsbtodb and dbtofsb shift constant */
	long	fs_sbsize;		/* actual size of super block */
	long	fs_csmask;		/* csum block offset */
	long	fs_csshift;		/* csum block number */
	long	fs_nindir;		/* value of NINDIR */
	long	fs_inopb;		/* value of INOPB */
	long	fs_nspf;		/* value of NSPF */
E 63
I 63
	int32_t	 fs_fragshift;		/* block to frag shift */
	int32_t	 fs_fsbtodb;		/* fsbtodb and dbtofsb shift constant */
	int32_t	 fs_sbsize;		/* actual size of super block */
	int32_t	 fs_csmask;		/* csum block offset */
	int32_t	 fs_csshift;		/* csum block number */
	int32_t	 fs_nindir;		/* value of NINDIR */
	int32_t	 fs_inopb;		/* value of INOPB */
	int32_t	 fs_nspf;		/* value of NSPF */
E 63
I 38
/* yet another configuration parameter */
E 38
D 35
	long	fs_sparecon[6];		/* reserved for future constants */
E 35
I 35
D 63
	long	fs_optim;		/* optimization preference, see below */
E 63
I 63
	int32_t	 fs_optim;		/* optimization preference, see below */
E 63
D 38
	long	fs_sparecon[5];		/* reserved for future constants */
E 38
I 38
/* these fields are derived from the hardware */
D 63
	long	fs_npsect;		/* # sectors/track including spares */
	long	fs_interleave;		/* hardware sector interleave */
	long	fs_trackskew;		/* sector 0 skew, per track */
	long	fs_headswitch;		/* head switch time, usec */
	long	fs_trkseek;		/* track-to-track seek, usec */
E 63
I 63
	int32_t	 fs_npsect;		/* # sectors/track including spares */
	int32_t	 fs_interleave;		/* hardware sector interleave */
	int32_t	 fs_trackskew;		/* sector 0 skew, per track */
	int32_t	 fs_headswitch;		/* head switch time, usec */
	int32_t	 fs_trkseek;		/* track-to-track seek, usec */
E 63
E 38
E 35
E 28
E 26
E 19
E 14
E 11
E 9
E 6
/* sizes determined by number of cylinder groups and their sizes */
I 9
D 63
	daddr_t fs_csaddr;		/* blk addr of cyl grp summary area */
E 9
D 6
	short	fs_cssize;		/* size of cyl grp summary area */
	short	fs_cgsize;		/* cylinder group size */
E 6
I 6
	long	fs_cssize;		/* size of cyl grp summary area */
	long	fs_cgsize;		/* cylinder group size */
E 63
I 63
D 68
	daddr_t  fs_csaddr;		/* blk addr of cyl grp summary area */
E 68
I 68
	ufs_daddr_t fs_csaddr;		/* blk addr of cyl grp summary area */
E 68
	int32_t	 fs_cssize;		/* size of cyl grp summary area */
	int32_t	 fs_cgsize;		/* cylinder group size */
E 63
E 6
D 38
/* these fields should be derived from the hardware */
E 38
I 38
/* these fields are derived from the hardware */
E 38
D 19
	short	fs_ntrak;		/* tracks per cylinder */
	short	fs_nsect;		/* sectors per track */
E 19
I 19
D 63
	long	fs_ntrak;		/* tracks per cylinder */
	long	fs_nsect;		/* sectors per track */
E 19
D 6
	short  	fs_spc;   		/* sectors per cylinder */
E 6
I 6
	long  	fs_spc;   		/* sectors per cylinder */
E 63
I 63
	int32_t	 fs_ntrak;		/* tracks per cylinder */
	int32_t	 fs_nsect;		/* sectors per track */
	int32_t  fs_spc;			/* sectors per cylinder */
E 63
E 6
/* this comes from the disk driver partitioning */
D 6
	short	fs_ncyl;   		/* cylinders in file system */
E 6
I 6
D 63
	long	fs_ncyl;   		/* cylinders in file system */
E 63
I 63
	int32_t	 fs_ncyl;		/* cylinders in file system */
E 63
E 6
/* these fields can be computed from the others */
D 19
	short	fs_cpg;			/* cylinders per group */
D 6
	short	fs_fpg;			/* blocks per group*FRAG */
E 6
	short	fs_ipg;			/* inodes per group */
E 19
I 19
D 63
	long	fs_cpg;			/* cylinders per group */
	long	fs_ipg;			/* inodes per group */
E 19
D 6
/* these fields must be re-computed after crashes */
	daddr_t	fs_nffree;   		/* total free fragments */
	daddr_t	fs_nbfree;		/* free data blocks */
	ino_t  	fs_nifree;  		/* total free inodes */
E 6
I 6
D 9
	long	fs_fpg;			/* blocks per group*FRAG */
E 9
I 9
	long	fs_fpg;			/* blocks per group * fs_frag */
E 63
I 63
	int32_t	 fs_cpg;			/* cylinders per group */
	int32_t	 fs_ipg;			/* inodes per group */
	int32_t	 fs_fpg;			/* blocks per group * fs_frag */
E 63
E 9
/* this data must be re-computed after crashes */
	struct	csum fs_cstotal;	/* cylinder summary information */
E 6
/* these fields are cleared at mount time */
D 63
	char   	fs_fmod;    		/* super block modified flag */
I 19
	char   	fs_clean;    		/* file system is clean flag */
E 19
	char   	fs_ronly;   		/* mounted read-only flag */
I 19
	char   	fs_flags;   		/* currently unused flag */
E 19
D 6
	char	fs_fsmnt[32];		/* name mounted on */
E 6
I 6
D 15
	char	fs_fsmnt[34];		/* name mounted on */
E 15
I 15
	char	fs_fsmnt[MAXMNTLEN];	/* name mounted on */
E 63
I 63
	int8_t   fs_fmod;		/* super block modified flag */
	int8_t   fs_clean;		/* file system is clean flag */
	int8_t 	 fs_ronly;		/* mounted read-only flag */
	int8_t   fs_flags;		/* currently unused flag */
	u_char	 fs_fsmnt[MAXMNTLEN];	/* name mounted on */
E 63
I 38
D 39
D 40
	long	fs_sparecon[32];	/* reserved for future constants */
E 40
I 40
D 42
	long	fs_dbsize;		/* hardware sector size */
	long	fs_sparecon[31];	/* reserved for future constants */
E 42
E 40
E 39
I 39
	long	fs_dbsize;		/* hardware sector size */
	long	fs_sparecon[31];	/* reserved for future constants */
E 39
E 38
E 15
E 6
D 4
	struct	csum *fs_cs;
E 4
I 4
/* these fields retain the current block allocation info */
D 6
	short	fs_cgrotor;		/* last cg searched */
E 6
I 6
D 63
	long	fs_cgrotor;		/* last cg searched */
E 63
I 63
	int32_t	 fs_cgrotor;		/* last cg searched */
E 63
E 6
D 15
	struct	csum *fs_csp[NBUF];	/* list of fs_cs info buffers */
E 15
I 15
D 16
	struct	csum *fs_csp[NBUF / 2];	/* list of fs_cs info buffers */
E 16
I 16
	struct	csum *fs_csp[MAXCSBUFS];/* list of fs_cs info buffers */
I 65
	int32_t	 *fs_maxcluster;	/* max cluster in each cyl group */
E 65
E 16
E 15
D 11
	short	fs_postbl[NRPOS];	/* head of blocks for each rotation */
	short	fs_rotbl[1];		/* list of blocks for each rotation */
E 11
I 11
D 19
	short	fs_cpc;			/* cyl per cycle in postbl */
E 19
I 19
D 63
	long	fs_cpc;			/* cyl per cycle in postbl */
E 19
D 42
	short	fs_postbl[MAXCPG][NRPOS];/* head of blocks for each rotation */
E 42
I 42
	short	fs_opostbl[16][8];	/* old rotation block list head */
D 47
	long	fs_sparecon[56];	/* reserved for future constants */
E 47
I 47
D 54
	long	fs_sparecon[55];	/* reserved for future constants */
	long	fs_state;		/* validate fs_clean field */
E 54
I 54
D 55
	long	fs_sparecon[52];	/* reserved for future constants */
E 55
I 55
D 58
	long	fs_sparecon[51];	/* reserved for future constants */
E 58
I 58
	long	fs_sparecon[50];	/* reserved for future constants */
	long	fs_contigsumsize;	/* size of cluster summary array */ 
E 58
	long	fs_maxsymlinklen;	/* max length of an internal symlink */
E 55
	long	fs_inodefmt;		/* format of on-disk inodes */
E 63
I 63
	int32_t	 fs_cpc;		/* cyl per cycle in postbl */
	int16_t	 fs_opostbl[16][8];	/* old rotation block list head */
	int32_t	 fs_sparecon[50];	/* reserved for future constants */
	int32_t	 fs_contigsumsize;	/* size of cluster summary array */ 
	int32_t	 fs_maxsymlinklen;	/* max length of an internal symlink */
	int32_t	 fs_inodefmt;		/* format of on-disk inodes */
E 63
D 66
	u_quad_t fs_maxfilesize;	/* maximum representable file size */
E 54
E 47
D 52
	quad	fs_qbmask;		/* ~fs_bmask - for use with quad size */
	quad	fs_qfmask;		/* ~fs_fmask - for use with quad size */
E 52
I 52
D 63
	quad_t	fs_qbmask;		/* ~fs_bmask - for use with quad size */
	quad_t	fs_qfmask;		/* ~fs_fmask - for use with quad size */
I 54
	long	fs_state;		/* validate fs_clean field */
E 54
E 52
	long	fs_postblformat;	/* format of positional layout tables */
D 62
	long	fs_nrpos;		/* number of rotaional positions */
E 62
I 62
	long	fs_nrpos;		/* number of rotational positions */
E 62
	long	fs_postbloff;		/* (short) rotation block list head */
	long	fs_rotbloff;		/* (u_char) blocks for each rotation */
E 42
I 20
	long	fs_magic;		/* magic number */
E 20
D 42
	u_char	fs_rotbl[1];		/* list of blocks for each rotation */
E 42
I 42
	u_char	fs_space[1];		/* list of blocks for each rotation */
E 63
I 63
	quad_t	 fs_qbmask;		/* ~fs_bmask - for use with quad size */
	quad_t	 fs_qfmask;		/* ~fs_fmask - for use with quad size */
E 66
I 66
	u_int64_t fs_maxfilesize;	/* maximum representable file size */
D 67
	int64_t	 fs_qbmask;		/* ~fs_bmask - for use with quad size */
	int64_t	 fs_qfmask;		/* ~fs_fmask - for use with quad size */
E 67
I 67
	int64_t	 fs_qbmask;		/* ~fs_bmask for use with 64-bit size */
	int64_t	 fs_qfmask;		/* ~fs_fmask for use with 64-bit size */
E 67
E 66
	int32_t	 fs_state;		/* validate fs_clean field */
	int32_t	 fs_postblformat;	/* format of positional layout tables */
	int32_t	 fs_nrpos;		/* number of rotational positions */
	int32_t	 fs_postbloff;		/* (u_int16) rotation block list head */
	int32_t	 fs_rotbloff;		/* (u_int8) blocks for each rotation */
	int32_t	 fs_magic;		/* magic number */
	u_int8_t fs_space[1];		/* list of blocks for each rotation */
E 63
E 42
E 11
/* actually longer */
E 4
};
I 63

E 63
I 35
/*
I 54
D 63
 * Filesystem idetification
E 63
I 63
 * Filesystem identification
E 63
 */
#define	FS_MAGIC	0x011954	/* the fast filesystem magic number */
#define	FS_OKAY		0x7c269d38	/* superblock checksum */
#define FS_42INODEFMT	-1		/* 4.2BSD inode format */
#define FS_44INODEFMT	2		/* 4.4BSD inode format */
/*
E 54
 * Preference for optimization.
 */
#define FS_OPTTIME	0	/* minimize allocation time */
#define FS_OPTSPACE	1	/* minimize disk fragmentation */
E 35
I 4
D 9
#define fs_cs(indx) fs_csp[(indx) / (BSIZE / sizeof(struct csum))] \
			  [(indx) % (BSIZE / sizeof(struct csum))]
E 9
E 4

/*
I 42
 * Rotational layout table format types
 */
#define FS_42POSTBLFMT		-1	/* 4.2BSD rotational table format */
#define FS_DYNAMICPOSTBLFMT	1	/* dynamic rotational table format */
/*
 * Macros for access to superblock array structures
 */
#define fs_postbl(fs, cylno) \
    (((fs)->fs_postblformat == FS_42POSTBLFMT) \
    ? ((fs)->fs_opostbl[cylno]) \
D 63
    : ((short *)((char *)(fs) + (fs)->fs_postbloff) + (cylno) * (fs)->fs_nrpos))
E 63
I 63
    : ((int16_t *)((u_int8_t *)(fs) + \
	(fs)->fs_postbloff) + (cylno) * (fs)->fs_nrpos))
E 63
#define fs_rotbl(fs) \
    (((fs)->fs_postblformat == FS_42POSTBLFMT) \
    ? ((fs)->fs_space) \
D 63
    : ((u_char *)((char *)(fs) + (fs)->fs_rotbloff)))
E 63
I 63
    : ((u_int8_t *)((u_int8_t *)(fs) + (fs)->fs_rotbloff)))
E 63

/*
I 59
 * The size of a cylinder group is calculated by CGSIZE. The maximum size
 * is limited by the fact that cylinder groups are at most one block.
 * Its size is derived from the size of the maps maintained in the 
 * cylinder group and the (struct cg) size.
 */
#define CGSIZE(fs) \
D 63
    /* base cg */	(sizeof(struct cg) + sizeof(long) + \
    /* blktot size */	(fs)->fs_cpg * sizeof(long) + \
    /* blks size */	(fs)->fs_cpg * (fs)->fs_nrpos * sizeof(short) + \
E 63
I 63
    /* base cg */	(sizeof(struct cg) + sizeof(int32_t) + \
    /* blktot size */	(fs)->fs_cpg * sizeof(int32_t) + \
    /* blks size */	(fs)->fs_cpg * (fs)->fs_nrpos * sizeof(int16_t) + \
E 63
    /* inode map */	howmany((fs)->fs_ipg, NBBY) + \
    /* block map */	howmany((fs)->fs_cpg * (fs)->fs_spc / NSPF(fs), NBBY) +\
I 60
    /* if present */	((fs)->fs_contigsumsize <= 0 ? 0 : \
E 60
D 63
    /* cluster sum */	(fs)->fs_contigsumsize * sizeof(long) + \
E 63
I 63
    /* cluster sum */	(fs)->fs_contigsumsize * sizeof(int32_t) + \
E 63
D 60
    /* cluster map */	howmany((fs)->fs_cpg * (fs)->fs_spc / NSPB(fs), NBBY))
E 60
I 60
    /* cluster map */	howmany((fs)->fs_cpg * (fs)->fs_spc / NSPB(fs), NBBY)))
E 60

/*
E 59
E 42
I 9
D 15
 * convert cylinder group to base address of its global summary info.
E 15
I 15
 * Convert cylinder group to base address of its global summary info.
E 15
I 10
 *
E 10
 * N.B. This macro assumes that sizeof(struct csum) is a power of two.
 */
#define fs_cs(fs, indx) \
D 29
	fs_csp[(indx) / ((fs)->fs_bsize / sizeof(struct csum))] \
	[(indx) % ((fs)->fs_bsize / sizeof(struct csum))]
E 29
I 29
	fs_csp[(indx) >> (fs)->fs_csshift][(indx) & ~(fs)->fs_csmask]
E 29

/*
E 9
D 10
 * Cylinder group macros to locate things in cylinder groups.
E 10
I 10
D 11
 * MAXBPC bounds the number of blocks of data per cylinder,
 * and is limited by the fact that the super block is of size SBSIZE.
 * Its size is derived from the size of blocks and the (struct fs) size,
 * by the number of remaining bits.
E 11
I 11
D 42
 * MAXBPC bounds the size of the rotational layout tables and
 * is limited by the fact that the super block is of size SBSIZE.
 * The size of these tables is INVERSELY proportional to the block
 * size of the file system. It is aggravated by sector sizes that
 * are not powers of two, as this increases the number of cylinders
 * included before the rotational pattern repeats (fs_cpc).
 * Its size is derived from the number of bytes remaining in (struct fs)
E 11
E 10
 */
I 10
D 11
#define	MAXBPC	((SBSIZE - sizeof (struct fs)) / sizeof(short))
E 11
I 11
#define	MAXBPC	(SBSIZE - sizeof (struct fs))
E 11
E 10

D 10
/* cylinder group to disk block at very beginning */
#define	cgbase(c,fs)	((daddr_t)((fs)->fs_fpg*(c)))

/* cylinder group to spare super block address */
#define	cgsblock(c,fs)	\
D 9
	(cgbase(c,fs) + SBLOCK)
E 9
I 9
	(cgbase(c,fs) + dbtofsb(fs, SBLOCK))
E 9

/* convert cylinder group to index of its cg block */
#define	cgtod(c,fs)	\
D 9
	(cgbase(c,fs) + CBLOCK)
E 9
I 9
	(cgbase(c,fs) + CBLOCK(fs))
E 9

/* give address of first inode block in cylinder group */
#define	cgimin(c,fs)	\
D 9
	(cgbase(c,fs) + IBLOCK)
E 9
I 9
	(cgbase(c,fs) + IBLOCK(fs))
E 9

/* give address of first data block in cylinder group */
D 9
#define	cgdmin(c,fs)	(cgimin(c,fs) + (fs)->fs_ipg / INOPF)
E 9
I 9
#define	cgdmin(c,fs)	(cgimin(c,fs) + (fs)->fs_ipg / INOPF(fs))
E 9

/* turn inode number into cylinder group number */
#define	itog(x,fs)	((x)/(fs)->fs_ipg)

D 9
/* turn inode number into disk block address */
D 8
#define	itod(x,fs)	(cgimin(itog(x,fs),fs)+FRAG*((x)%(fs)->fs_ipg/INOPB))
E 8
I 8
#define	itod(x,fs)	((daddr_t)(cgimin(itog(x,fs),fs)+FRAG*((x)%(fs)->fs_ipg/INOPB)))
E 9
I 9
/* turn inode number into file system block address */
#define	itod(x,fs)	((daddr_t)(cgimin(itog(x,fs),fs)+(fs)->fs_frag*((x)%(fs)->fs_ipg/INOPB(fs))))
E 9
E 8

D 9
/* turn inode number into disk block offset */
#define	itoo(x)		((x)%INOPB)
E 9
I 9
/* turn inode number into file system block offset */
#define	itoo(x,fs)	((x)%INOPB(fs))
E 9

D 9
/* give cylinder group number for a disk block */
E 9
I 9
/* give cylinder group number for a file system block */
E 9
#define	dtog(d,fs)	((d)/(fs)->fs_fpg)

D 9
/* give cylinder group block number for a disk block */
E 9
I 9
/* give cylinder group block number for a file system block */
E 9
#define	dtogd(d,fs)	((d)%(fs)->fs_fpg)

E 10
/*
E 42
D 10
 * Cylinder group related limits.
E 10
I 10
 * Cylinder group block for a file system.
E 10
 */
D 10

/*
D 4
 * For each cylinder we keep track of the availability of blocks at different
 * rotational positions, so that we can lay out the data to be picked
 * up with minimum rotational latency.  NRPOS is the number of rotational
 * positions which we distinguish.  With NRPOS 16 the resolution of our
 * summary information is 1ms for a typical 3600 rpm drive.
 */
#define	NRPOS	16		/* number distinct rotational positions */

/*
E 4
 * MAXIPG bounds the number of inodes per cylinder group, and
 * is needed only to keep the structure simpler by having the
 * only a single variable size element (the free bit map).
 *
 * N.B.: MAXIPG must be a multiple of INOPB.
 */
#define	MAXIPG	2048		/* max number inodes/cyl group */

/*
 * MAXBPG bounds the number of blocks of data per cylinder group,
 * and is limited by the fact that cylinder groups are at most one block.
 * Its size is derived from the size of blocks and the (struct cg) size,
 * by the number of remaining bits.
 */
D 9
#define	MAXBPG	(NBBY*(BSIZE-(sizeof (struct cg)))/FRAG)
E 9
I 9
#define	MAXBPG(fs) \
	(NBBY*((fs)->fs_bsize-(sizeof (struct cg)))/(fs)->fs_frag)
E 9

E 10
D 20
#define	CG_MAGIC	0x092752
E 20
I 20
#define	CG_MAGIC	0x090255
E 20
D 63
struct	cg {
D 20
	long	cg_magic;		/* magic number */
E 20
I 20
	struct	cg *cg_link;		/* linked list of cyl groups */
D 42
	struct	cg *cg_rlink;		/*     used for incore cyl groups */
E 42
I 42
	long	cg_magic;		/* magic number */
E 42
E 20
	time_t	cg_time;		/* time last written */
D 6
	short	cg_cgx;			/* we are the cgx'th cylinder group */
E 6
I 6
	long	cg_cgx;			/* we are the cgx'th cylinder group */
E 6
	short	cg_ncyl;		/* number of cyl's this cg */
	short	cg_niblk;		/* number of inode blocks this cg */
D 6
	short	cg_ndblk;		/* number of data blocks this cg */
	short	cg_nifree;		/* free inodes */
	short	cg_ndir;		/* allocated directories */
	short	cg_nffree;		/* free block fragments */
	short	cg_nbfree;		/* free blocks */
	short	cg_rotor;		/* position of last used block */
	short	cg_irotor;		/* position of last used inode */
I 2
	short	cg_frotor;		/* position of last used frag */
	short	cg_frsum[FRAG];		/* counts of available frags */
E 6
I 6
	long	cg_ndblk;		/* number of data blocks this cg */
E 63
I 63
struct cg {
D 64
	int32_t	 unused_1;		/* historic cyl groups linked list */
E 64
I 64
	int32_t	 cg_firstfield;		/* historic cyl groups linked list */
E 64
	int32_t	 cg_magic;		/* magic number */
	time_t	 cg_time;		/* time last written */
	int32_t	 cg_cgx;		/* we are the cgx'th cylinder group */
	int16_t	 cg_ncyl;		/* number of cyl's this cg */
	int16_t	 cg_niblk;		/* number of inode blocks this cg */
	int32_t	 cg_ndblk;		/* number of data blocks this cg */
E 63
	struct	csum cg_cs;		/* cylinder summary information */
D 63
	long	cg_rotor;		/* position of last used block */
	long	cg_frotor;		/* position of last used frag */
	long	cg_irotor;		/* position of last used inode */
D 9
	long	cg_frsum[FRAG];		/* counts of available frags */
E 9
I 9
	long	cg_frsum[MAXFRAG];	/* counts of available frags */
I 12
D 42
	long	cg_btot[MAXCPG];	/* block totals per cylinder */
E 12
E 9
E 6
E 2
	short	cg_b[MAXCPG][NRPOS];	/* positions of free blocks */
	char	cg_iused[MAXIPG/NBBY];	/* used inode map */
I 20
	long	cg_magic;		/* magic number */
E 20
D 25
	char	cg_free[1];		/* free block map */
E 25
I 25
	u_char	cg_free[1];		/* free block map */
E 42
I 42
	long	cg_btotoff;		/* (long) block totals per cylinder */
	long	cg_boff;		/* (short) free block positions */
	long	cg_iusedoff;		/* (char) used inode map */
	long	cg_freeoff;		/* (u_char) free block map */
	long	cg_nextfreeoff;		/* (u_char) next available space */
D 58
	long	cg_sparecon[16];	/* reserved for future use */
E 58
I 58
	long	cg_clustersumoff;	/* (long) counts of avail clusters */
	long	cg_clusteroff;		/* (char) free cluster map */
	long	cg_nclusterblks;	/* number of clusters this cg */
	long	cg_sparecon[13];	/* reserved for future use */
E 58
	u_char	cg_space[1];		/* space for cylinder group maps */
E 63
I 63
	int32_t	 cg_rotor;		/* position of last used block */
	int32_t	 cg_frotor;		/* position of last used frag */
	int32_t	 cg_irotor;		/* position of last used inode */
	int32_t	 cg_frsum[MAXFRAG];	/* counts of available frags */
	int32_t	 cg_btotoff;		/* (int32) block totals per cylinder */
	int32_t	 cg_boff;		/* (u_int16) free block positions */
	int32_t	 cg_iusedoff;		/* (u_int8) used inode map */
	int32_t	 cg_freeoff;		/* (u_int8) free block map */
	int32_t	 cg_nextfreeoff;	/* (u_int8) next available space */
	int32_t	 cg_clustersumoff;	/* (u_int32) counts of avail clusters */
	int32_t	 cg_clusteroff;		/* (u_int8) free cluster map */
	int32_t	 cg_nclusterblks;	/* number of clusters this cg */
	int32_t	 cg_sparecon[13];	/* reserved for future use */
	u_int8_t cg_space[1];		/* space for cylinder group maps */
E 63
E 42
E 25
/* actually longer */
};
I 63

E 63
I 42
/*
 * Macros for access to cylinder group array structures
 */
#define cg_blktot(cgp) \
    (((cgp)->cg_magic != CG_MAGIC) \
    ? (((struct ocg *)(cgp))->cg_btot) \
D 63
    : ((long *)((char *)(cgp) + (cgp)->cg_btotoff)))
E 63
I 63
    : ((int32_t *)((u_int8_t *)(cgp) + (cgp)->cg_btotoff)))
E 63
#define cg_blks(fs, cgp, cylno) \
    (((cgp)->cg_magic != CG_MAGIC) \
    ? (((struct ocg *)(cgp))->cg_b[cylno]) \
D 63
    : ((short *)((char *)(cgp) + (cgp)->cg_boff) + (cylno) * (fs)->fs_nrpos))
E 63
I 63
    : ((int16_t *)((u_int8_t *)(cgp) + \
	(cgp)->cg_boff) + (cylno) * (fs)->fs_nrpos))
E 63
#define cg_inosused(cgp) \
    (((cgp)->cg_magic != CG_MAGIC) \
    ? (((struct ocg *)(cgp))->cg_iused) \
D 63
    : ((char *)((char *)(cgp) + (cgp)->cg_iusedoff)))
E 63
I 63
    : ((u_int8_t *)((u_int8_t *)(cgp) + (cgp)->cg_iusedoff)))
E 63
#define cg_blksfree(cgp) \
    (((cgp)->cg_magic != CG_MAGIC) \
    ? (((struct ocg *)(cgp))->cg_free) \
D 63
    : ((u_char *)((char *)(cgp) + (cgp)->cg_freeoff)))
E 63
I 63
    : ((u_int8_t *)((u_int8_t *)(cgp) + (cgp)->cg_freeoff)))
E 63
#define cg_chkmagic(cgp) \
    ((cgp)->cg_magic == CG_MAGIC || ((struct ocg *)(cgp))->cg_magic == CG_MAGIC)
I 58
#define cg_clustersfree(cgp) \
D 63
    ((u_char *)((char *)(cgp) + (cgp)->cg_clusteroff))
E 63
I 63
    ((u_int8_t *)((u_int8_t *)(cgp) + (cgp)->cg_clusteroff))
E 63
#define cg_clustersum(cgp) \
D 63
    ((long *)((char *)(cgp) + (cgp)->cg_clustersumoff))
E 63
I 63
    ((int32_t *)((u_int8_t *)(cgp) + (cgp)->cg_clustersumoff))
E 63
E 58
E 42
D 10
#define	cgsize(fp)	(sizeof (struct cg) + ((fp)->fs_fpg+NBBY-1)/NBBY)
E 10
I 10

/*
D 42
 * MAXBPG bounds the number of blocks of data per cylinder group,
 * and is limited by the fact that cylinder groups are at most one block.
 * Its size is derived from the size of blocks and the (struct cg) size,
 * by the number of remaining bits.
E 42
I 42
 * The following structure is defined
 * for compatibility with old file systems.
E 42
 */
D 42
#define	MAXBPG(fs) \
D 29
	(NBBY * ((fs)->fs_bsize - (sizeof (struct cg))) / (fs)->fs_frag)
E 29
I 29
D 30
	(NBBY * ((fs)->fs_bsize - (sizeof (struct cg))) >> (fs)->fs_fragshift)
E 30
I 30
	(fragstoblks((fs), (NBBY * ((fs)->fs_bsize - (sizeof (struct cg))))))
E 42
I 42
D 63
struct	ocg {
	struct	ocg *cg_link;		/* linked list of cyl groups */
	struct	ocg *cg_rlink;		/*     used for incore cyl groups */
	time_t	cg_time;		/* time last written */
	long	cg_cgx;			/* we are the cgx'th cylinder group */
	short	cg_ncyl;		/* number of cyl's this cg */
	short	cg_niblk;		/* number of inode blocks this cg */
	long	cg_ndblk;		/* number of data blocks this cg */
E 63
I 63
struct ocg {
D 64
	int32_t	 unused_1;		/* historic linked list of cyl groups */
	int32_t	 unused_2;		/*     used for incore cyl groups */
E 64
I 64
	int32_t	 cg_firstfield;		/* historic linked list of cyl groups */
D 66
	int32_t	 unused_1;		/*     used for incore cyl groups */
E 66
I 66
	int32_t	 cg_unused_1;		/*     used for incore cyl groups */
E 66
E 64
	time_t	 cg_time;		/* time last written */
	int32_t	 cg_cgx;		/* we are the cgx'th cylinder group */
	int16_t	 cg_ncyl;		/* number of cyl's this cg */
	int16_t	 cg_niblk;		/* number of inode blocks this cg */
	int32_t	 cg_ndblk;		/* number of data blocks this cg */
E 63
	struct	csum cg_cs;		/* cylinder summary information */
D 63
	long	cg_rotor;		/* position of last used block */
	long	cg_frotor;		/* position of last used frag */
	long	cg_irotor;		/* position of last used inode */
	long	cg_frsum[8];		/* counts of available frags */
	long	cg_btot[32];		/* block totals per cylinder */
	short	cg_b[32][8];		/* positions of free blocks */
	char	cg_iused[256];		/* used inode map */
	long	cg_magic;		/* magic number */
	u_char	cg_free[1];		/* free block map */
E 63
I 63
	int32_t	 cg_rotor;		/* position of last used block */
	int32_t	 cg_frotor;		/* position of last used frag */
	int32_t	 cg_irotor;		/* position of last used inode */
	int32_t	 cg_frsum[8];		/* counts of available frags */
	int32_t	 cg_btot[32];		/* block totals per cylinder */
	int16_t	 cg_b[32][8];		/* positions of free blocks */
	u_int8_t cg_iused[256];		/* used inode map */
	int32_t	 cg_magic;		/* magic number */
	u_int8_t cg_free[1];		/* free block map */
E 63
/* actually longer */
};
E 42
E 30
E 29

/*
 * Turn file system block numbers into disk block addresses.
 * This maps file system blocks to device size blocks.
 */
D 29
#define fsbtodb(fs, b)	((b) * ((fs)->fs_fsize / DEV_BSIZE))
#define	dbtofsb(fs, b)	((b) / ((fs)->fs_fsize / DEV_BSIZE))
E 29
I 29
#define fsbtodb(fs, b)	((b) << (fs)->fs_fsbtodb)
#define	dbtofsb(fs, b)	((b) >> (fs)->fs_fsbtodb)
E 29

/*
 * Cylinder group macros to locate things in cylinder groups.
D 19
 *
D 11
 * cylinder group to disk block at very beginning
E 11
I 11
D 15
 * cylinder group to disk block address of spare boot block
 * and super block
E 15
I 15
 * Cylinder group to disk block address of spare boot block
 * and super block.
E 15
 * Note that these are in absolute addresses, and can NOT
 * in general be expressable in terms of file system addresses.
E 19
I 19
 * They calc file system addresses of cylinder group data structures.
E 19
E 11
 */
D 11
#define	cgbase(c,fs)	((daddr_t)((fs)->fs_fpg * (c)))
E 11
I 11
D 13
#define	cgbblock(c,fs)	(fsbtodb(fs, cgbase(c,fs)) + (fs)->fs_bblkno)
#define	cgsblock(c,fs)	(fsbtodb(fs, cgbase(c,fs)) + (fs)->fs_sblkno)
E 13
I 13
D 19
#define	cgbblock(fs, c)	(fsbtodb(fs, cgbase(fs, c)) + (fs)->fs_bblkno)
#define	cgsblock(fs, c)	(fsbtodb(fs, cgbase(fs, c)) + (fs)->fs_sblkno)
E 13
E 11

/*
D 11
 * cylinder group to spare super block address
E 11
I 11
D 12
 * cylinder group to disk block at very beginning
E 12
I 12
D 15
 * file system addresses of cylinder group data structures
E 15
I 15
 * File system addresses of cylinder group data structures.
E 15
E 12
E 11
 */
D 11
#define	cgsblock(c,fs)	(cgbase(c,fs) + dbtofsb(fs, SBLOCK))
E 11
I 11
D 12
#define	cgbase(c,fs)	((daddr_t)((fs)->fs_fpg * (c)))
E 12
I 12
D 13
#define	cgbase(c,fs)	((daddr_t)((fs)->fs_fpg * (c)))		/* base addr */
#define	cgtod(c,fs)	(cgbase(c,fs) + (fs)->fs_cblkno)	/* cg block */
#define	cgimin(c,fs)	(cgbase(c,fs) + (fs)->fs_iblkno)	/* inode blk */
#define	cgdmin(c,fs)	(cgbase(c,fs) + (fs)->fs_dblkno)	/* 1st data */
E 13
I 13
#define	cgbase(fs, c)	((daddr_t)((fs)->fs_fpg * (c)))		/* base addr */
#define	cgtod(fs, c)	(cgbase(fs, c) + (fs)->fs_cblkno)	/* cg block */
#define	cgimin(fs, c)	(cgbase(fs, c) + (fs)->fs_iblkno)	/* inode blk */
#define	cgdmin(fs, c)	(cgbase(fs, c) + (fs)->fs_dblkno)	/* 1st data */
E 19
I 19
D 68
#define	cgbase(fs, c)	((daddr_t)((fs)->fs_fpg * (c)))
E 68
I 68
#define	cgbase(fs, c)	((ufs_daddr_t)((fs)->fs_fpg * (c)))
E 68
D 57
#define cgstart(fs, c) \
	(cgbase(fs, c) + (fs)->fs_cgoffset * ((c) & ~((fs)->fs_cgmask)))
E 57
I 57
#define	cgdmin(fs, c)	(cgstart(fs, c) + (fs)->fs_dblkno)	/* 1st data */
#define	cgimin(fs, c)	(cgstart(fs, c) + (fs)->fs_iblkno)	/* inode blk */
E 57
#define	cgsblock(fs, c)	(cgstart(fs, c) + (fs)->fs_sblkno)	/* super blk */
#define	cgtod(fs, c)	(cgstart(fs, c) + (fs)->fs_cblkno)	/* cg block */
D 57
#define	cgimin(fs, c)	(cgstart(fs, c) + (fs)->fs_iblkno)	/* inode blk */
#define	cgdmin(fs, c)	(cgstart(fs, c) + (fs)->fs_dblkno)	/* 1st data */
E 57
I 57
#define cgstart(fs, c)							\
	(cgbase(fs, c) + (fs)->fs_cgoffset * ((c) & ~((fs)->fs_cgmask)))
E 57
E 19
E 13
E 12
E 11

/*
D 12
 * convert cylinder group to index of its cg block
E 12
I 12
D 15
 * macros for handling inode numbers
 *     inode number to file system block offset
 *     inode number to cylinder group number
 *     inode number to file system block address
E 15
I 15
 * Macros for handling inode numbers:
 *     inode number to file system block offset.
 *     inode number to cylinder group number.
 *     inode number to file system block address.
E 15
E 12
 */
D 11
#define	cgtod(c,fs)	(cgbase(c,fs) + CBLOCK(fs))
E 11
I 11
D 12
#define	cgtod(c,fs)	(cgbase(c,fs) + (fs)->fs_cblkno)
E 11

/*
 * give address of first inode block in cylinder group
 */
D 11
#define	cgimin(c,fs)	(cgbase(c,fs) + IBLOCK(fs))
E 11
I 11
#define	cgimin(c,fs)	(cgbase(c,fs) + (fs)->fs_iblkno)
E 11

/*
 * give address of first data block in cylinder group
 */
D 11
#define	cgdmin(c,fs)	(cgimin(c,fs) + (fs)->fs_ipg / INOPF(fs))
E 11
I 11
#define	cgdmin(c,fs)	(cgbase(c,fs) + (fs)->fs_dblkno)
E 11

/*
 * turn inode number into cylinder group number
 */
E 12
I 12
D 13
#define	itoo(x,fs)	((x) % INOPB(fs))
E 12
#define	itog(x,fs)	((x) / (fs)->fs_ipg)
D 12

/*
 * turn inode number into file system block address
 */
E 12
#define	itod(x,fs) \
D 11
	((daddr_t)(cgimin(itog(x,fs),fs) + (fs)->fs_frag * \
	((x) % (fs)->fs_ipg / INOPB(fs))))
E 11
I 11
	((daddr_t)(cgimin(itog(x,fs),fs) + \
E 13
I 13
D 57
#define	itoo(fs, x)	((x) % INOPB(fs))
#define	itog(fs, x)	((x) / (fs)->fs_ipg)
#define	itod(fs, x) \
	((daddr_t)(cgimin(fs, itog(fs, x)) + \
E 13
D 29
	(x) % (fs)->fs_ipg / INOPB(fs) * (fs)->fs_frag))
E 29
I 29
D 30
	((((x) % (fs)->fs_ipg) / INOPB(fs)) << (fs)->fs_fragshift)))
E 30
I 30
	(blkstofrags((fs), (((x) % (fs)->fs_ipg) / INOPB(fs))))))
E 57
I 57
#define	ino_to_cg(fs, x)	((x) / (fs)->fs_ipg)
#define	ino_to_fsba(fs, x)						\
D 68
	((daddr_t)(cgimin(fs, ino_to_cg(fs, x)) +			\
E 68
I 68
	((ufs_daddr_t)(cgimin(fs, ino_to_cg(fs, x)) +			\
E 68
	    (blkstofrags((fs), (((x) % (fs)->fs_ipg) / INOPB(fs))))))
#define	ino_to_fsbo(fs, x)	((x) % INOPB(fs))
E 57
E 30
E 29
E 11

/*
D 12
 * turn inode number into file system block offset
 */
#define	itoo(x,fs)	((x) % INOPB(fs))

/*
E 12
D 15
 * give cylinder group number for a file system block
D 12
 */
#define	dtog(d,fs)	((d) / (fs)->fs_fpg)

/*
E 12
 * give cylinder group block number for a file system block
E 15
I 15
 * Give cylinder group number for a file system block.
 * Give cylinder group block number for a file system block.
E 15
 */
I 12
D 13
#define	dtog(d,fs)	((d) / (fs)->fs_fpg)
E 12
#define	dtogd(d,fs)	((d) % (fs)->fs_fpg)
E 13
I 13
#define	dtog(fs, d)	((d) / (fs)->fs_fpg)
#define	dtogd(fs, d)	((d) % (fs)->fs_fpg)
E 13
I 11

/*
D 15
 * compute the cylinder and rotational position of a cyl block addr
E 15
I 15
 * Extract the bits for a block from a map.
 * Compute the cylinder and rotational position of a cyl block addr.
E 15
 */
I 15
#define blkmap(fs, map, loc) \
D 33
    (((map)[loc / NBBY] >> (loc % NBBY)) & (0xff >> (NBBY - (fs)->fs_frag)))
E 33
I 33
    (((map)[(loc) / NBBY] >> ((loc) % NBBY)) & (0xff >> (NBBY - (fs)->fs_frag)))
E 33
E 15
#define cbtocylno(fs, bno) \
D 36
	((bno) * NSPF(fs) / (fs)->fs_spc)
E 36
I 36
    ((bno) * NSPF(fs) / (fs)->fs_spc)
E 36
#define cbtorpos(fs, bno) \
D 36
	((bno) * NSPF(fs) % (fs)->fs_nsect * NRPOS / (fs)->fs_nsect)
E 36
I 36
D 38
    ((bno) * NSPF(fs) % (fs)->fs_spc % (fs)->fs_nsect * NRPOS / (fs)->fs_nsect)
E 38
I 38
    (((bno) * NSPF(fs) % (fs)->fs_spc / (fs)->fs_nsect * (fs)->fs_trackskew + \
     (bno) * NSPF(fs) % (fs)->fs_spc % (fs)->fs_nsect * (fs)->fs_interleave) % \
D 42
     (fs)->fs_nsect * NRPOS / (fs)->fs_npsect)
E 42
I 42
     (fs)->fs_nsect * (fs)->fs_nrpos / (fs)->fs_npsect)
E 42
E 38
E 36
E 11

/*
I 14
 * The following macros optimize certain frequently calculated
 * quantities by using shifts and masks in place of divisions
 * modulos and multiplications.
 */
#define blkoff(fs, loc)		/* calculates (loc % fs->fs_bsize) */ \
D 54
	((loc) & ~(fs)->fs_bmask)
E 54
I 54
	((loc) & (fs)->fs_qbmask)
E 54
#define fragoff(fs, loc)	/* calculates (loc % fs->fs_fsize) */ \
D 54
	((loc) & ~(fs)->fs_fmask)
E 54
I 54
	((loc) & (fs)->fs_qfmask)
E 54
I 46
#define lblktosize(fs, blk)	/* calculates (blk * fs->fs_bsize) */ \
	((blk) << (fs)->fs_bshift)
E 46
#define lblkno(fs, loc)		/* calculates (loc / fs->fs_bsize) */ \
	((loc) >> (fs)->fs_bshift)
#define numfrags(fs, loc)	/* calculates (loc / fs->fs_fsize) */ \
	((loc) >> (fs)->fs_fshift)
#define blkroundup(fs, size)	/* calculates roundup(size, fs->fs_bsize) */ \
D 54
	(((size) + (fs)->fs_bsize - 1) & (fs)->fs_bmask)
E 54
I 54
	(((size) + (fs)->fs_qbmask) & (fs)->fs_bmask)
E 54
#define fragroundup(fs, size)	/* calculates roundup(size, fs->fs_fsize) */ \
D 54
	(((size) + (fs)->fs_fsize - 1) & (fs)->fs_fmask)
E 54
I 54
	(((size) + (fs)->fs_qfmask) & (fs)->fs_fmask)
E 54
I 30
#define fragstoblks(fs, frags)	/* calculates (frags / fs->fs_frag) */ \
	((frags) >> (fs)->fs_fragshift)
#define blkstofrags(fs, blks)	/* calculates (blks * fs->fs_frag) */ \
	((blks) << (fs)->fs_fragshift)
I 32
#define fragnum(fs, fsb)	/* calculates (fsb % fs->fs_frag) */ \
	((fsb) & ((fs)->fs_frag - 1))
#define blknum(fs, fsb)		/* calculates rounddown(fsb, fs->fs_frag) */ \
	((fsb) &~ ((fs)->fs_frag - 1))
E 32

/*
 * Determine the number of available frags given a
D 66
 * percentage to hold in reserve
E 66
I 66
 * percentage to hold in reserve.
E 66
 */
#define freespace(fs, percentreserved) \
	(blkstofrags((fs), (fs)->fs_cstotal.cs_nbfree) + \
	(fs)->fs_cstotal.cs_nffree - ((fs)->fs_dsize * (percentreserved) / 100))
E 30

/*
E 14
D 15
 * determining the size of a file block in the file system
E 15
I 15
 * Determining the size of a file block in the file system.
E 15
 */
#define blksize(fs, ip, lbn) \
D 29
	(((lbn) >= NDADDR || (ip)->i_size >= ((lbn) + 1) * (fs)->fs_bsize) \
E 29
I 29
	(((lbn) >= NDADDR || (ip)->i_size >= ((lbn) + 1) << (fs)->fs_bshift) \
E 29
D 14
		? (fs)->fs_bsize \
		: (roundup((ip)->i_size % (fs)->fs_bsize, (fs)->fs_fsize)))
E 14
I 14
	    ? (fs)->fs_bsize \
	    : (fragroundup(fs, blkoff(fs, (ip)->i_size))))
E 14
#define dblksize(fs, dip, lbn) \
D 29
	(((lbn) >= NDADDR || (dip)->di_size >= ((lbn) + 1) * (fs)->fs_bsize) \
E 29
I 29
	(((lbn) >= NDADDR || (dip)->di_size >= ((lbn) + 1) << (fs)->fs_bshift) \
E 29
D 14
		? (fs)->fs_bsize \
		: (roundup((dip)->di_size % (fs)->fs_bsize, (fs)->fs_fsize)))
E 14
I 14
	    ? (fs)->fs_bsize \
	    : (fragroundup(fs, blkoff(fs, (dip)->di_size))))
E 14
D 66

E 66
I 63

E 63
/*
D 15
 * number of disk sectors per block; assumes DEV_BSIZE byte sector size
E 15
I 15
D 63
 * Number of disk sectors per block; assumes DEV_BSIZE byte sector size.
E 63
I 63
 * Number of disk sectors per block/fragment; assumes DEV_BSIZE byte
 * sector size.
E 63
E 15
 */
D 29
#define	NSPB(fs)	((fs)->fs_bsize / DEV_BSIZE)
#define	NSPF(fs)	((fs)->fs_fsize / DEV_BSIZE)
E 29
I 29
#define	NSPB(fs)	((fs)->fs_nspf << (fs)->fs_fragshift)
#define	NSPF(fs)	((fs)->fs_nspf)
E 29

/*
D 15
 * INOPB is the number of inodes in a secondary storage block
E 15
I 15
D 63
 * INOPB is the number of inodes in a secondary storage block.
E 63
I 63
 * Number of inodes in a secondary storage block/fragment.
E 63
E 15
 */
D 29
#define	INOPB(fs)	((fs)->fs_bsize / sizeof (struct dinode))
#define	INOPF(fs)	((fs)->fs_fsize / sizeof (struct dinode))
E 29
I 29
#define	INOPB(fs)	((fs)->fs_inopb)
#define	INOPF(fs)	((fs)->fs_inopb >> (fs)->fs_fragshift)
E 29

/*
D 15
 * NINDIR is the number of indirects in a file system block
E 15
I 15
D 63
 * NINDIR is the number of indirects in a file system block.
E 63
I 63
 * Number of indirects in a file system block.
E 63
E 15
 */
D 29
#define	NINDIR(fs)	((fs)->fs_bsize / sizeof (daddr_t))
E 29
I 29
#define	NINDIR(fs)	((fs)->fs_nindir)
I 53

extern int inside[], around[];
extern u_char *fragtbl[];
E 53
E 29
E 10
D 49

#ifdef KERNEL
struct	fs *getfs();
I 23
D 45
struct	fs *mountfs();
E 45
E 23
I 2
D 4
int inside[], around[];
D 3
char fragtbl[];
E 3
I 3
unsigned char fragtbl[];
E 4
E 3
E 2
#endif
E 49
E 1
