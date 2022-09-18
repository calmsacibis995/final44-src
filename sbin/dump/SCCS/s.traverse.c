h22352
s 00002/00002/00579
d D 8.7 95/06/15 14:30:12 mckusick 54 53
c proper check for lseek failure
e
s 00002/00002/00579
d D 8.6 95/05/02 00:11:12 mckusick 53 52
c lint
e
s 00001/00006/00580
d D 8.5 95/05/01 23:40:23 mckusick 52 51
c changes for new dinode definitions
e
s 00003/00004/00583
d D 8.4 95/04/28 10:29:28 bostic 51 50
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00585
d D 8.3 95/03/27 14:03:35 mckusick 50 49
c lint
e
s 00001/00001/00586
d D 8.2 93/09/23 19:36:49 bostic 49 48
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00585
d D 8.1 93/06/05 10:53:01 bostic 48 47
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00021/00552
d D 5.25 93/05/11 13:59:15 torek 47 46
c less-hairy maxino logic; compat for SunOS and other 4.2/4.3 systems;`
e
s 00001/00001/00572
d D 5.24 93/03/11 15:30:33 sklower 46 45
c NODUMP -> UF_NODUMP
e
s 00043/00024/00530
d D 5.23 93/01/25 15:35:04 mckusick 45 44
c make more portable; cleanups from leres@lbl
e
s 00001/00001/00553
d D 5.22 93/01/25 12:49:48 mckusick 44 43
c may miss dumping last inode
e
s 00020/00015/00534
d D 5.21 92/07/19 16:58:51 mckusick 43 42
c must scan whole directory for subdirs or modified files;
c misc cleanups; keep those off_t's consistent
e
s 00001/00001/00548
d D 5.20 92/07/16 12:40:04 bostic 42 41
c fix the prototypes, minor cleanup to signal handlers
e
s 00042/00009/00507
d D 5.19 92/07/02 16:22:19 mckusick 41 40
c have to extricate short symlinks and put their data inline like long symlinks
e
s 00037/00036/00479
d D 5.18 92/06/18 19:03:04 mckusick 40 39
c lint; bug fix for missing indirection on parameter; timeval => timespec
e
s 00003/00002/00512
d D 5.17 92/05/26 10:09:42 mckusick 39 37
c add <sys/time.h> for dinode.h; need to select tv_sec field of times
e
s 00001/00000/00514
d R 5.17 92/05/26 10:07:02 mckusick 38 37
c add <sys/time.h> for dinode.h
e
s 00004/00003/00510
d D 5.16 91/12/12 17:26:27 mckusick 37 36
c ignore files with NODUMP flag set
e
s 00004/00003/00509
d D 5.15 91/11/10 13:05:10 bostic 36 35
c break UFS up into FFS/UFS/LFS/MFS
e
s 00001/00001/00511
d D 5.14 91/10/17 14:58:48 mckusick 35 34
c ensure that the root inode is dumped
e
s 00015/00005/00497
d D 5.13 91/08/28 14:40:24 mckusick 34 32
c more informative error messages
e
s 00000/00001/00501
d R 5.13 91/07/23 21:09:54 mckusick 33 32
c delete unneeded include of dir.h
e
s 00011/00000/00491
d D 5.12 91/07/23 16:57:48 mckusick 32 31
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00005/00004/00486
d D 5.11 91/03/07 17:49:54 mckusick 31 30
c verified to be free of AT&T code
e
s 00021/00021/00469
d D 5.10 91/03/07 12:01:09 mckusick 30 29
c lint, misc cleanups
e
s 00007/00003/00483
d D 5.9 91/02/28 19:50:45 mckusick 29 28
c have to deal with directories that are shorter than a block
e
s 00009/00000/00477
d D 5.8 91/02/28 19:33:55 bostic 28 27
c ANSI; break #includes out of dump.h into separate files
e
s 00273/00215/00204
d D 5.7 91/02/28 18:54:58 mckusick 27 26
c new faster and more accurate algorithm to calculate dumpset;
c add comments to describe what is being done; KNF
e
s 00080/00023/00339
d D 5.6 91/02/23 16:14:19 torek 26 25
c avoid multiply and divide when possible; fix gcc warnings;
c dump size estimate functions move here from dumpitime.c
e
s 00017/00004/00345
d D 5.5 88/05/20 10:03:02 karels 25 23
c update 'bread error' message, attempt read a sector at a time after error,
c don't return old stuff in buffer after read failure
e
s 00001/00001/00348
d R 5.5 87/06/18 10:13:12 mckusick 24 23
c must dump last inode! bug report 4.3BSD/etc/69
e
s 00004/00004/00345
d D 5.4 87/02/23 18:06:26 mckusick 23 22
c convert SBLOCK to SBOFF; generalize dev_bsize
e
s 00013/00014/00336
d D 5.3 86/01/09 21:28:29 mckusick 22 21
c speedup and cleanup by Chris Torek
e
s 00005/00002/00345
d D 5.2 85/08/05 14:43:13 mckusick 21 20
c optimization (from speck@cit-vlsi)
e
s 00009/00001/00338
d D 5.1 85/06/05 08:47:37 dist 20 19
c Add copyright
e
s 00011/00000/00328
d D 1.17 84/10/05 15:56:11 mckusick 19 18
c maintain consistent dump tapes on active systems (decvax!watmath!srradia)
e
s 00002/00009/00326
d D 1.16 84/03/08 16:26:18 mckusick 18 17
c always dump entire map, not just the non-zero portion
e
s 00034/00024/00301
d D 1.15 83/09/25 16:46:13 mckusick 17 16
c kludge to handle case where we need to read the last fragment in a file system
e
s 00018/00010/00307
d D 1.14 83/09/08 11:09:57 mckusick 16 15
c do not depend on unused portions of directories being zero
e
s 00001/00008/00316
d D 1.13 83/02/11 12:58:45 sam 15 14
c merge from sun
e
s 00001/00001/00323
d D 1.12 82/12/02 17:52:24 mckusick 14 13
c fix to properly dump 4096/512 byte file systems
e
s 00002/00002/00322
d D 1.11 82/10/14 12:52:46 mckusick 13 12
c fix to properly dump file systems with 512 byte frags
e
s 00000/00001/00324
d D 1.10 82/10/07 19:28:16 mckusick 12 11
c move struct itime out of dumprestor.h into dump.h
e
s 00001/00001/00324
d D 1.9 82/10/07 18:22:06 mckusick 11 10
c update to new magic number
e
s 00001/00001/00324
d D 1.8 82/05/20 15:11:20 sam 10 9
c convert to calder
e
s 00002/00002/00323
d D 1.7 82/03/23 12:53:03 mckusick 9 8
c add symbolic links
e
s 00016/00014/00309
d D 1.6 82/02/23 12:59:25 mckusic 8 7
c convert to new directory format
e
s 00001/00001/00322
d D 1.5 82/01/12 22:33:02 mckusic 7 6
c change all macros taking "fs" to have it as their first argument
e
s 00084/00109/00239
d D 1.4 82/01/05 01:37:35 mckusic 6 5
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00096/00038/00252
d D 1.3 81/11/07 15:05:58 mckusic 5 2
c dump from "standard" (ie 1K file system) dump tapes
e
s 00090/00032/00258
d R 1.3 81/11/07 14:55:18 mckusic 4 2
c dump to "standard" (ie 1K file system) dump tapes
e
s 00095/00031/00259
d R 1.3 81/11/07 14:53:23 mckusic 3 2
c dump to "standard" (ie 1K file system) dump tapes
e
s 00051/00045/00239
d D 1.2 81/10/31 18:30:56 mckusic 2 1
c 8K only dump/restor
e
s 00284/00000/00000
d D 1.1 80/10/13 17:30:31 root 1 0
c date and time created 80/10/13 17:30:31 by root
e
u
U
t
T
I 1
D 20
static	char *sccsid = "%W% (Berkeley) %G%";
E 20
I 20
D 31
/*
D 25
 * Copyright (c) 1980 Regents of the University of California.
E 25
I 25
 * Copyright (c) 1980, 1988 Regents of the University of California.
E 25
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
/*-
D 48
 * Copyright (c) 1980, 1988, 1991 The Regents of the University of California.
 * All rights reserved.
E 48
I 48
 * Copyright (c) 1980, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 48
 *
 * %sccs.include.redist.c%
E 31
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26
E 20
I 6

I 32
D 45
#ifdef sunos
#include <stdio.h>
#include <ctype.h>
E 45
E 32
I 28
#include <sys/param.h>
I 45
#include <sys/time.h>
#include <sys/stat.h>
#ifdef sunos
#include <sys/vnode.h>

E 45
I 32
D 37
#include <sys/stat.h>
E 37
D 40
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 40
I 36
#include <ufs/fs.h>
I 45
#include <ufs/fsdir.h>
#include <ufs/inode.h>
E 45
E 36
#else
D 45
#include <sys/param.h>
E 45
I 39
D 40
#include <sys/time.h>
E 39
E 32
D 36
#include <ufs/dir.h>
#include <ufs/dinode.h>
E 36
I 36
#include <ufs/ufs/dir.h>
#include <ufs/ufs/dinode.h>
E 40
D 52
#include <ufs/ffs/fs.h>
E 52
E 36
I 32
D 45
#endif
I 40
#include <sys/time.h>
E 40
I 37
#include <sys/stat.h>
E 45
I 40
#include <ufs/ufs/dir.h>
#include <ufs/ufs/dinode.h>
I 52
#include <ufs/ffs/fs.h>
E 52
I 45
#endif

E 45
E 40
E 37
E 32
D 36
#include <ufs/fs.h>
E 36
#include <protocols/dumprestore.h>
I 45

#include <ctype.h>
#include <stdio.h>
E 45
#ifdef __STDC__
D 45
#include <unistd.h>
E 45
#include <string.h>
I 45
#include <unistd.h>
E 45
#endif
I 45

E 45
E 28
E 6
#include "dump.h"
I 8
D 10
#include <ndir.h>
E 10
I 10
D 12
#include <dir.h>
E 12
E 10
E 8

I 26
D 27
void	indir(), dmpindir(), dsrch();
E 27
I 27
D 45
void	dmpindir();
E 45
#define	HASDUMPEDFILE	0x1
#define	HASSUBDIRS	0x2
E 27

I 47
#ifdef	FS_44INODEFMT
typedef	quad_t fsizeT;
#else
typedef	long fsizeT;
#endif

E 47
I 45
static	int dirindir __P((ino_t ino, daddr_t blkno, int level, long *size));
D 47
static	void dmpindir __P((ino_t ino, daddr_t blk, int level, quad_t *size));
E 47
I 47
static	void dmpindir __P((ino_t ino, daddr_t blk, int level, fsizeT *size));
E 47
static	int searchdir __P((ino_t ino, daddr_t blkno, long size, long filesize));

E 45
/*
 * This is an estimation of the number of TP_BSIZE blocks in the file.
 * It estimates the number of blocks in files with holes by assuming
 * that all of the blocks accounted for by di_blocks are data blocks
 * (when some of the blocks are usually used for indirect pointers);
 * hence the estimate may be high.
 */
D 27
void
est(ip)
E 27
I 27
long
D 30
blockest(ip)
E 27
	struct dinode *ip;
E 30
I 30
blockest(dp)
	register struct dinode *dp;
E 30
{
D 27
	long s, t;
E 27
I 27
	long blkest, sizeest;
E 27

	/*
D 30
	 * ip->di_size is the size of the file in bytes.
	 * ip->di_blocks stores the number of sectors actually in the file.
E 30
I 30
	 * dp->di_size is the size of the file in bytes.
	 * dp->di_blocks stores the number of sectors actually in the file.
E 30
	 * If there are more sectors than the size would indicate, this just
	 *	means that there are indirect blocks in the file or unused
	 *	sectors in the last file block; we can safely ignore these
D 27
	 *	(s = t below).
E 27
I 27
	 *	(blkest = sizeest below).
E 27
	 * If the file is bigger than the number of sectors would indicate,
	 *	then the file has holes in it.	In this case we must use the
	 *	block count to estimate the number of data blocks used, but
	 *	we use the actual size for estimating the number of indirect
D 27
	 *	dump blocks (t vs. s in the indirect block calculation).
E 27
I 27
	 *	dump blocks (sizeest vs. blkest in the indirect block
	 *	calculation).
E 27
	 */
D 27
	esize++;
	s = howmany(dbtob(ip->di_blocks), TP_BSIZE);
	t = howmany(ip->di_size, TP_BSIZE);
	if (s > t)
		s = t;
E 27
I 27
D 30
	blkest = howmany(dbtob(ip->di_blocks), TP_BSIZE);
	sizeest = howmany(ip->di_size, TP_BSIZE);
E 30
I 30
	blkest = howmany(dbtob(dp->di_blocks), TP_BSIZE);
	sizeest = howmany(dp->di_size, TP_BSIZE);
E 30
	if (blkest > sizeest)
		blkest = sizeest;
E 27
D 30
	if (ip->di_size > sblock->fs_bsize * NDADDR) {
E 30
I 30
	if (dp->di_size > sblock->fs_bsize * NDADDR) {
E 30
		/* calculate the number of indirect blocks on the dump tape */
D 27
		s += howmany(t - NDADDR * sblock->fs_bsize / TP_BSIZE,
E 27
I 27
		blkest +=
			howmany(sizeest - NDADDR * sblock->fs_bsize / TP_BSIZE,
E 27
			TP_NINDIR);
	}
D 27
	esize += s;
E 27
I 27
	return (blkest + 1);
E 27
}

I 47
/* Auxiliary macro to pick up files changed since previous dump. */
D 52
#ifdef FS_44INODEFMT
E 52
#define	CHANGEDSINCE(dp, t) \
D 52
	((dp)->di_mtime.ts_sec >= (t) || (dp)->di_ctime.ts_sec >= (t))
#else
#define	CHANGEDSINCE(dp, t) \
E 52
	((dp)->di_mtime >= (t) || (dp)->di_ctime >= (t))
D 52
#endif
E 52

/* The WANTTODUMP macro decides whether a file should be dumped. */
#ifdef UF_NODUMP
#define	WANTTODUMP(dp) \
	(CHANGEDSINCE(dp, spcl.c_ddate) && \
	 (nonodump || ((dp)->di_flags & UF_NODUMP) != UF_NODUMP))
#else
#define	WANTTODUMP(dp) CHANGEDSINCE(dp, spcl.c_ddate)
#endif

E 47
D 27
void
bmapest(map)
	char *map;
E 27
I 27
/*
 * Dump pass 1.
 *
 * Walk the inode list for a filesystem to find all allocated inodes
 * that have been modified since the previous dump time. Also, find all
 * the directories in the filesystem.
 */
I 45
int
E 45
mapfiles(maxino, tapesize)
	ino_t maxino;
	long *tapesize;
E 27
{
I 27
	register int mode;
	register ino_t ino;
	register struct dinode *dp;
	int anydirskipped = 0;
E 27

D 27
	esize += howmany(msiz * sizeof map[0], TP_BSIZE) + 1;
E 27
I 27
D 44
	for (ino = 0; ino < maxino; ino++) {
E 44
I 44
D 47
	for (ino = 0; ino <= maxino; ino++) {
E 47
I 47
	for (ino = ROOTINO; ino < maxino; ino++) {
E 47
E 44
		dp = getino(ino);
		if ((mode = (dp->di_mode & IFMT)) == 0)
			continue;
		SETINO(ino, usedinomap);
		if (mode == IFDIR)
			SETINO(ino, dumpdirmap);
D 37
		if (dp->di_mtime >= spcl.c_ddate ||
		    dp->di_ctime >= spcl.c_ddate) {
E 37
I 37
D 39
		if ((dp->di_mtime >= spcl.c_ddate ||
		    dp->di_ctime >= spcl.c_ddate) &&
E 39
I 39
D 40
		if ((dp->di_mtime.tv_sec >= spcl.c_ddate ||
		    dp->di_ctime.tv_sec >= spcl.c_ddate) &&
E 39
		    (dp->di_flags & NODUMP) != NODUMP) {
E 40
I 40
D 45
		if ((dp->di_mtime.ts_sec >= spcl.c_ddate ||
		    dp->di_ctime.ts_sec >= spcl.c_ddate)
#ifndef sunos
E 45
I 45
D 47
		if (
#ifdef FS_44INODEFMT
		    (dp->di_mtime.ts_sec >= spcl.c_ddate ||
		     dp->di_ctime.ts_sec >= spcl.c_ddate)
E 45
D 46
		    && (dp->di_flags & NODUMP) != NODUMP
E 46
I 46
		    && (dp->di_flags & UF_NODUMP) != UF_NODUMP
E 46
I 45
#else
		    dp->di_mtime >= spcl.c_ddate ||
		     dp->di_ctime >= spcl.c_ddate
E 45
#endif
		    ) {
E 47
I 47
		if (WANTTODUMP(dp)) {
E 47
E 40
E 37
			SETINO(ino, dumpinomap);
D 47
			if (mode != IFREG && mode != IFDIR && mode != IFLNK) {
E 47
I 47
			if (mode != IFREG && mode != IFDIR && mode != IFLNK)
E 47
				*tapesize += 1;
D 47
				continue;
			}
			*tapesize += blockest(dp);
E 47
I 47
			else
				*tapesize += blockest(dp);
E 47
			continue;
		}
		if (mode == IFDIR)
			anydirskipped = 1;
	}
	/*
	 * Restore gets very upset if the root is not dumped,
	 * so ensure that it always is dumped.
	 */
D 35
	SETINO(ROOTINO, usedinomap);
E 35
I 35
	SETINO(ROOTINO, dumpinomap);
E 35
	return (anydirskipped);
E 27
}

D 27
void
E 26
D 2
struct	filsys	sblock;
struct	dinode	itab[INOPB * NI];
E 2
I 2
D 6
struct	fs	sblock;
E 2

E 6
pass(fn, map)
D 2
int (*fn)();
short *map;
E 2
I 2
D 22
	int (*fn)();
D 6
	short *map;
E 6
I 6
	char *map;
E 22
I 22
	register int (*fn)();
	register char *map;
E 22
E 6
E 2
{
D 2
	register i, j;
E 2
I 2
D 22
	struct dinode *dp;
E 2
	int bits;
E 22
I 22
D 26
	register int bits;
E 26
I 26
	register int bits = 0;	/* this value not used, but keeps gcc happy */
E 27
I 27
/*
 * Dump pass 2.
 *
 * Scan each directory on the filesystem to see if it has any modified
 * files in it. If it does, and has not already been added to the dump
 * list (because it was itself modified), then add it. If a directory
 * has not been modified itself, contains no modified files and has no
 * subdirectories, then it can be deleted from the dump list and from
 * the list of directories. By deleting it from the list of directories,
 * its parent may now qualify for the same treatment on this or a later
 * pass using this algorithm.
 */
I 45
int
E 45
mapdirs(maxino, tapesize)
E 27
E 26
E 22
D 2
	ino_t mino;
	daddr_t d;
E 2
I 2
	ino_t maxino;
I 27
	long *tapesize;
{
	register struct	dinode *dp;
D 30
	register int i, bits;
E 30
I 30
D 43
	register int i, dirty;
E 43
I 43
	register int i, isdir;
E 43
E 30
	register char *map;
	register ino_t ino;
D 40
	long filesize, blkcnt = 0;
E 40
I 40
	long filesize;
E 40
	int ret, change = 0;
E 27
E 2

D 6
	sync();
D 2
	bread((daddr_t)1, (char *)&sblock, sizeof(sblock));
	mino = (sblock.s_isize-2) * INOPB;
	ino = 0;
	for(i=2;; i+=NI) {
		if(ino >= mino)
			break;
		d = (unsigned)i;
		for(j=0; j<INOPB*NI; j++) {
			if(ino >= mino)
				break;
			if((ino % MLEN) == 0) {
				bits = ~0;
				if(map != NULL)
					bits = *map++;
			}
			ino++;
			if(bits & 1) {
				if(d != 0) {
					bread(d, (char *)itab, sizeof(itab));
					d = 0;
				}
				(*fn)(&itab[j]);
			}
			bits >>= 1;
E 2
I 2
	bread(SBLOCK, &sblock, sizeof sblock);
	if (sblock.fs_magic != FS_MAGIC) {
		msg("bad sblock magic number\n");
		dumpabort();
	}
	maxino = sblock.fs_ipg * sblock.fs_ncg;
E 6
I 6
D 27
	maxino = sblock->fs_ipg * sblock->fs_ncg - 1;
E 6
	for (ino = 0; ino < maxino; ) {
E 27
I 27
D 47
	for (map = dumpdirmap, ino = 0; ino < maxino; ) {
E 27
D 6
		if((ino % MLEN) == 0) {
E 6
I 6
D 22
		if((ino % NBBY) == 0) {
E 22
I 22
D 26
		if ((ino % NBBY) == 0) {
E 22
E 6
			bits = ~0;
D 22
			if(map != NULL)
E 22
I 22
			if (map != NULL)
E 22
				bits = *map++;
E 2
		}
E 26
I 26
		if ((ino % NBBY) == 0)
E 47
I 47
	isdir = 0;		/* XXX just to get gcc to shut up */
	for (map = dumpdirmap, ino = 1; ino < maxino; ino++) {
		if (((ino - 1) % NBBY) == 0)	/* map is offset by 1 */
E 47
D 27
			bits = map ? *map++ : ~0;
E 27
I 27
D 30
			bits = *map++;
E 30
I 30
D 43
			dirty = *map++;
E 43
I 43
			isdir = *map++;
E 43
E 30
		else
D 30
			bits >>= 1;
E 30
I 30
D 43
			dirty >>= 1;
E 43
I 43
			isdir >>= 1;
E 43
E 30
E 27
E 26
I 2
D 47
		ino++;
E 47
D 22
		if(bits & 1) {
			dp = getino(ino);
			(*fn)(dp);
		}
E 22
I 22
D 27
		if (bits & 1)
			(*fn)(getino(ino));
E 22
		bits >>= 1;
E 27
I 27
D 30
		if ((bits & 1) == 0 || TSTINO(ino, dumpinomap))
E 30
I 30
D 43
		if ((dirty & 1) == 0 || TSTINO(ino, dumpinomap))
E 43
I 43
		if ((isdir & 1) == 0 || TSTINO(ino, dumpinomap))
E 43
E 30
			continue;
		dp = getino(ino);
		filesize = dp->di_size;
		for (ret = 0, i = 0; filesize > 0 && i < NDADDR; i++) {
			if (dp->di_db[i] != 0)
				ret |= searchdir(ino, dp->di_db[i],
D 29
					dblksize(sblock, dp, i));
E 29
I 29
D 43
					dblksize(sblock, dp, i), filesize);
E 43
I 43
					(long)dblksize(sblock, dp, i),
					filesize);
E 43
E 29
			if (ret & HASDUMPEDFILE)
				filesize = 0;
			else
				filesize -= sblock->fs_bsize;
		}
		for (i = 0; filesize > 0 && i < NIADDR; i++) {
			if (dp->di_ib[i] == 0)
				continue;
			ret |= dirindir(ino, dp->di_ib[i], i, &filesize);
		}
		if (ret & HASDUMPEDFILE) {
D 43
			if (!TSTINO(ino, dumpinomap)) {
				SETINO(ino, dumpinomap);
				*tapesize += blockest(dp);
			}
E 43
I 43
			SETINO(ino, dumpinomap);
			*tapesize += blockest(dp);
E 43
			change = 1;
			continue;
		}
		if ((ret & HASSUBDIRS) == 0) {
			if (!TSTINO(ino, dumpinomap)) {
				CLRINO(ino, dumpdirmap);
				change = 1;
			}
		}
E 27
E 2
	}
I 27
	return (change);
E 27
}

I 26
D 27
void
E 26
D 2
icat(ip, fn1, fn2)
struct	dinode	*ip;
int (*fn1)(), (*fn2)();
E 2
I 2
D 5
icat(dp, fn1, fn2)
E 5
I 5
D 6
icat(dp, fn1)
E 5
	register struct	dinode	*dp;
D 5
	int (*fn1)(), (*fn2)();
E 5
I 5
	int (*fn1)();
E 5
E 2
{
D 2
	register i;
	daddr_t d[NADDR];
E 2
I 2
	register int i;
E 2

D 2
	l3tol(&d[0], &ip->di_addr[0], NADDR);
	(*fn2)(d, NADDR-3);
	for(i=0; i<NADDR; i++) {
		if(d[i] != 0) {
			if(i < NADDR-3)
				(*fn1)(d[i]); else
				indir(d[i], fn1, fn2, i-(NADDR-3));
		}
E 2
I 2
D 5
	(*fn2)(dp->di_db, NDADDR);
E 5
	for (i = 0; i < NDADDR; i++) {
		if (dp->di_db[i] != 0)
			(*fn1)(dp->di_db[i]);
E 2
	}
I 2
	for (i = 0; i < NIADDR; i++) {
		if (dp->di_ib[i] != 0)
D 5
			indir(dp->di_ib[i], fn1, fn2, i);
E 5
I 5
			indir(dp->di_ib[i], fn1, i);
E 5
	}
E 2
}

D 5
indir(d, fn1, fn2, n)
daddr_t d;
int (*fn1)(), (*fn2)();
E 5
I 5
indir(d, fn1, n)
	daddr_t d;
	int (*fn1)();
	int n;
E 5
{
	register i;
	daddr_t	idblk[NINDIR];

	bread(d, (char *)idblk, sizeof(idblk));
	if(n <= 0) {
D 5
		spcl.c_type = TS_ADDR;
		(*fn2)(idblk, NINDIR);
E 5
		for(i=0; i<NINDIR; i++) {
			d = idblk[i];
			if(d != 0)
				(*fn1)(d);
		}
	} else {
		n--;
		for(i=0; i<NINDIR; i++) {
			d = idblk[i];
			if(d != 0)
D 5
				indir(d, fn1, fn2, n);
E 5
I 5
				indir(d, fn1, n);
E 5
		}
	}
}

E 6
mark(ip)
D 5
struct dinode *ip;
E 5
I 5
	struct dinode *ip;
E 27
I 27
/*
 * Read indirect blocks, and pass the data blocks to be searched
 * as directories. Quit as soon as any entry is found that will
 * require the directory to be dumped.
 */
I 45
static int
E 45
D 40
dirindir(ino, blkno, level, filesize)
E 40
I 40
dirindir(ino, blkno, ind_level, filesize)
E 40
	ino_t ino;
	daddr_t blkno;
D 40
	int level, *filesize;
E 40
I 40
	int ind_level;
	long *filesize;
E 40
E 27
E 5
{
D 22
	register f;
E 22
I 22
D 27
	register int f;
	extern int anydskipped;
E 22

	f = ip->di_mode & IFMT;
D 22
	if(f == 0)
E 22
I 22
	if (f == 0)
E 22
		return;
	BIS(ino, clrmap);
D 22
	if(f == IFDIR)
E 22
I 22
	if (f == IFDIR)
E 22
		BIS(ino, dirmap);
D 6
	if(ip->di_mtime >= spcl.c_ddate ||
	   ip->di_ctime >= spcl.c_ddate) {
E 6
I 6
	if ((ip->di_mtime >= spcl.c_ddate || ip->di_ctime >= spcl.c_ddate) &&
	    !BIT(ino, nodmap)) {
E 6
		BIS(ino, nodmap);
D 6
		if (f != IFREG){
E 6
I 6
D 9
		if (f != IFREG && f != IFDIR) {
E 9
I 9
		if (f != IFREG && f != IFDIR && f != IFLNK) {
E 9
E 6
			esize += 1;
			return;
		}
		est(ip);
D 22
	}
E 22
I 22
	} else if (f == IFDIR)
		anydskipped = 1;
E 22
}

I 26
void
E 26
add(ip)
D 5
struct dinode *ip;
E 5
I 5
D 6
	struct dinode *ip;
E 6
I 6
	register struct	dinode	*ip;
E 6
E 5
{
E 27
I 27
	int ret = 0;
E 27
I 6
	register int i;
I 16
D 27
	long filesize;
E 27
I 27
	daddr_t	idblk[MAXNINDIR];
E 27
E 16
E 6

D 27
	if(BIT(ino, nodmap))
		return;
	nsubdir = 0;
	dadded = 0;
I 16
	filesize = ip->di_size;
E 16
D 5
	icat(ip, dsrch, nullf);
E 5
I 5
D 6
	icat(ip, dsrch);
E 6
I 6
	for (i = 0; i < NDADDR; i++) {
		if (ip->di_db[i] != 0)
D 16
			dsrch(ip->di_db[i], dblksize(sblock, ip, i));
E 16
I 16
			dsrch(ip->di_db[i], dblksize(sblock, ip, i), filesize);
		filesize -= sblock->fs_bsize;
E 16
	}
	for (i = 0; i < NIADDR; i++) {
		if (ip->di_ib[i] != 0)
D 16
			indir(ip->di_ib[i], i);
E 16
I 16
			indir(ip->di_ib[i], i, &filesize);
E 16
	}
E 6
E 5
	if(dadded) {
D 6
		BIS(ino, nodmap);
		est(ip);
E 6
		nadded++;
I 6
		if (!BIT(ino, nodmap)) {
			BIS(ino, nodmap);
			est(ip);
E 27
I 27
D 40
	bread(fsbtodb(sblock, blkno), (char *)idblk, sblock->fs_bsize);
	if (level <= 0) {
E 40
I 40
	bread(fsbtodb(sblock, blkno), (char *)idblk, (int)sblock->fs_bsize);
	if (ind_level <= 0) {
E 40
		for (i = 0; *filesize > 0 && i < NINDIR(sblock); i++) {
			blkno = idblk[i];
			if (blkno != 0)
D 29
				ret |= searchdir(ino, blkno, sblock->fs_bsize);
E 29
I 29
				ret |= searchdir(ino, blkno, sblock->fs_bsize,
D 40
					filesize);
E 40
I 40
					*filesize);
E 40
E 29
			if (ret & HASDUMPEDFILE)
				*filesize = 0;
			else
				*filesize -= sblock->fs_bsize;
E 27
		}
I 27
		return (ret);
E 27
E 6
	}
D 27
	if(nsubdir == 0)
		if(!BIT(ino, nodmap))
			BIC(ino, dirmap);
E 27
I 27
D 40
	level--;
E 40
I 40
	ind_level--;
E 40
	for (i = 0; *filesize > 0 && i < NINDIR(sblock); i++) {
		blkno = idblk[i];
		if (blkno != 0)
D 40
			ret |= dirindir(ino, blkno, level, filesize);
E 40
I 40
			ret |= dirindir(ino, blkno, ind_level, filesize);
E 40
	}
	return (ret);
E 27
}

I 26
D 27
void
E 26
I 6
D 16
indir(d, n)
E 16
I 16
indir(d, n, filesize)
E 16
	daddr_t d;
D 16
	int n;
E 16
I 16
	int n, *filesize;
E 27
I 27
/*
 * Scan a disk block containing directory information looking to see if
 * any of the entries are on the dump list and to see if the directory
 * contains any subdirectories.
 */
I 45
static int
E 45
D 29
searchdir(ino, blkno, size)
E 29
I 29
searchdir(ino, blkno, size, filesize)
E 29
	ino_t ino;
	daddr_t blkno;
D 40
	register int size;
I 29
	int filesize;
E 40
I 40
	register long size;
	long filesize;
E 40
E 29
E 27
E 16
{
D 27
	register i;
	daddr_t	idblk[MAXNINDIR];
E 27
I 27
	register struct direct *dp;
D 43
	register long loc;
E 43
I 43
	register long loc, ret = 0;
E 43
	char dblk[MAXBSIZE];
E 27

D 27
	bread(fsbtodb(sblock, d), (char *)idblk, sblock->fs_bsize);
	if(n <= 0) {
		for(i=0; i < NINDIR(sblock); i++) {
			d = idblk[i];
			if(d != 0)
D 16
				dsrch(d, sblock->fs_bsize);
E 16
I 16
				dsrch(d, sblock->fs_bsize, *filesize);
			*filesize -= sblock->fs_bsize;
E 27
I 27
D 40
	bread(fsbtodb(sblock, blkno), dblk, size);
E 40
I 40
	bread(fsbtodb(sblock, blkno), dblk, (int)size);
E 40
I 29
	if (filesize < size)
		size = filesize;
E 29
	for (loc = 0; loc < size; ) {
		dp = (struct direct *)(dblk + loc);
		if (dp->d_reclen == 0) {
			msg("corrupted directory, inumber %d\n", ino);
			break;
E 27
E 16
		}
D 27
	} else {
		n--;
		for(i=0; i < NINDIR(sblock); i++) {
			d = idblk[i];
			if(d != 0)
D 16
				indir(d, n);
E 16
I 16
				indir(d, n, filesize);
E 27
I 27
		loc += dp->d_reclen;
		if (dp->d_ino == 0)
			continue;
		if (dp->d_name[0] == '.') {
			if (dp->d_name[1] == '\0')
				continue;
			if (dp->d_name[1] == '.' && dp->d_name[2] == '\0')
				continue;
E 27
E 16
		}
I 27
D 43
		if (TSTINO(dp->d_ino, dumpinomap))
			return (HASDUMPEDFILE);
		if (TSTINO(dp->d_ino, dumpdirmap))
			return (HASSUBDIRS);
E 43
I 43
		if (TSTINO(dp->d_ino, dumpinomap)) {
			ret |= HASDUMPEDFILE;
			if (ret & HASSUBDIRS)
				break;
		}
		if (TSTINO(dp->d_ino, dumpdirmap)) {
			ret |= HASSUBDIRS;
			if (ret & HASDUMPEDFILE)
				break;
		}
E 43
E 27
	}
I 27
D 43
	return (0);
E 43
I 43
	return (ret);
E 43
E 27
}

I 27
/*
 * Dump passes 3 and 4.
 *
 * Dump the contents of an inode to tape.
 */
E 27
I 26
void
E 26
I 19
D 27
dirdump(ip)
E 27
I 27
D 30
dumpino(ip, ino)
E 27
	struct dinode *ip;
E 30
I 30
dumpino(dp, ino)
	register struct dinode *dp;
E 30
I 27
	ino_t ino;
E 27
{
D 27
	/* watchout for dir inodes deleted and maybe reallocated */
	if ((ip->di_mode & IFMT) != IFDIR)
		return;
	dump(ip);
}

I 26
void
E 26
E 19
E 6
dump(ip)
D 5
struct dinode *ip;
E 5
I 5
	struct dinode *ip;
E 5
{
D 5
	register i;
E 5
I 5
	register int i;
E 27
I 27
D 40
	int mode, level, cnt;
E 40
I 40
D 41
	int mode, ind_level, cnt;
E 41
I 41
	int ind_level, cnt;
E 41
E 40
E 27
D 45
	long size;
E 45
I 45
D 47
	quad_t size;
E 47
I 47
	fsizeT size;
E 47
E 45
I 41
	char buf[TP_BSIZE];
E 41
E 5

D 27
	if(newtape) {
E 27
I 27
	if (newtape) {
E 27
		newtape = 0;
D 27
		bitmap(nodmap, TS_BITS);
E 27
I 27
		dumpmap(dumpinomap, TS_BITS, ino);
E 27
	}
D 27
	BIC(ino, nodmap);
E 27
I 27
	CLRINO(ino, dumpinomap);
E 27
D 30
	spcl.c_dinode = *ip;
E 30
I 30
	spcl.c_dinode = *dp;
E 30
	spcl.c_type = TS_INODE;
	spcl.c_count = 0;
D 27
	i = ip->di_mode & IFMT;
I 19
	if (i == 0) /* free inode */
E 27
I 27
D 41
	/*
	 * Check for freed inode.
	 */
D 30
	if ((mode = (ip->di_mode & IFMT)) == 0)
E 30
I 30
	if ((mode = (dp->di_mode & IFMT)) == 0)
E 41
I 41
D 45
	switch (IFTODT(dp->di_mode)) {
E 45
I 45
	switch (dp->di_mode & S_IFMT) {
E 45

D 45
	case DT_UNKNOWN:
E 45
I 45
	case 0:
E 45
		/*
		 * Freed inode.
		 */
E 41
E 30
E 27
		return;
E 19
D 5
	if(i != IFDIR && i != IFREG) {
E 5
I 5
D 9
	if ((i != IFDIR && i != IFREG) || ip->di_size == 0) {
E 9
I 9
D 27
	if ((i != IFDIR && i != IFREG && i != IFLNK) || ip->di_size == 0) {
E 9
E 5
		spclrec();
E 27
I 27
D 41
	if ((mode != IFDIR && mode != IFREG && mode != IFLNK) ||
D 30
	    ip->di_size == 0) {
E 30
I 30
	    dp->di_size == 0) {
E 41
I 41

D 45
	case DT_LNK:
E 45
I 45
	case S_IFLNK:
E 45
		/*
		 * Check for short symbolic link.
		 */
I 45
#ifdef FS_44INODEFMT
E 45
		if (dp->di_size > 0 &&
		    dp->di_size < sblock->fs_maxsymlinklen) {
			spcl.c_addr[0] = 1;
			spcl.c_count = 1;
			writeheader(ino);
D 51
			bcopy((caddr_t)dp->di_shortlink, buf,
			    (u_long)dp->di_size);
E 51
I 51
			memmove(buf, dp->di_shortlink, (u_long)dp->di_size);
E 51
			buf[dp->di_size] = '\0';
			writerec(buf, 0);
			return;
		}
I 45
#endif
E 45
		/* fall through */

D 45
	case DT_DIR:
	case DT_REG:
E 45
I 45
	case S_IFDIR:
	case S_IFREG:
E 45
		if (dp->di_size > 0)
			break;
		/* fall through */

D 45
	case DT_FIFO:
	case DT_SOCK:
	case DT_CHR:
	case DT_BLK:
E 45
I 45
	case S_IFIFO:
	case S_IFSOCK:
	case S_IFCHR:
	case S_IFBLK:
E 45
E 41
E 30
		writeheader(ino);
E 27
		return;
I 41

	default:
		msg("Warning: undefined file type 0%o\n", dp->di_mode & IFMT);
		return;
E 41
	}
D 5
	icat(ip, tapsrec, dmpspc);
E 5
I 5
D 6
	if (ip->di_size > NDADDR * BSIZE)
		i = NDADDR * FRAG;
E 6
I 6
D 30
	if (ip->di_size > NDADDR * sblock->fs_bsize)
E 30
I 30
	if (dp->di_size > NDADDR * sblock->fs_bsize)
E 30
D 27
		i = NDADDR * sblock->fs_frag;
E 27
I 27
		cnt = NDADDR * sblock->fs_frag;
E 27
E 6
	else
D 6
		i = howmany(ip->di_size, FSIZE);
E 6
I 6
D 27
		i = howmany(ip->di_size, sblock->fs_fsize);
E 6
	blksout(&ip->di_db[0], i);
D 6
	size = ip->di_size - NDADDR * BSIZE;
E 6
I 6
	size = ip->di_size - NDADDR * sblock->fs_bsize;
E 6
	if (size <= 0)
E 27
I 27
D 30
		cnt = howmany(ip->di_size, sblock->fs_fsize);
	blksout(&ip->di_db[0], cnt, ino);
	if ((size = ip->di_size - NDADDR * sblock->fs_bsize) <= 0)
E 30
I 30
		cnt = howmany(dp->di_size, sblock->fs_fsize);
	blksout(&dp->di_db[0], cnt, ino);
	if ((size = dp->di_size - NDADDR * sblock->fs_bsize) <= 0)
E 30
E 27
		return;
D 27
	for (i = 0; i < NIADDR; i++) {
		dmpindir(ip->di_ib[i], i, &size);
E 27
I 27
D 40
	for (level = 0; level < NIADDR; level++) {
D 30
		dmpindir(ino, ip->di_ib[level], level, &size);
E 30
I 30
		dmpindir(ino, dp->di_ib[level], level, &size);
E 40
I 40
	for (ind_level = 0; ind_level < NIADDR; ind_level++) {
		dmpindir(ino, dp->di_ib[ind_level], ind_level, &size);
E 40
E 30
E 27
		if (size <= 0)
			return;
	}
E 5
}

I 27
/*
 * Read indirect blocks, and pass the data blocks to be dumped.
 */
E 27
I 26
D 45
void
E 45
I 45
static void
E 45
E 26
D 5
dmpspc(dp, n)
daddr_t *dp;
E 5
I 5
D 27
dmpindir(blk, lvl, size)
E 27
I 27
D 40
dmpindir(ino, blk, level, size)
E 40
I 40
dmpindir(ino, blk, ind_level, size)
E 40
	ino_t ino;
E 27
	daddr_t blk;
D 27
	int lvl;
E 27
I 27
D 40
	int level;
E 40
I 40
	int ind_level;
E 40
E 27
D 45
	long *size;
E 45
I 45
D 47
	quad_t *size;
E 47
I 47
	fsizeT *size;
E 47
E 45
E 5
{
D 5
	register i, t;
E 5
I 5
	int i, cnt;
D 6
	daddr_t idblk[NINDIR];
E 6
I 6
	daddr_t idblk[MAXNINDIR];
E 6
E 5

D 5
	spcl.c_count = n;
	for(i=0; i<n; i++) {
		t = 0;
		if(dp[i] != 0)
			t++;
		spcl.c_addr[i] = t;
E 5
I 5
	if (blk != 0)
D 6
		bread(blk, (char *)idblk, sizeof(idblk));
E 6
I 6
D 40
		bread(fsbtodb(sblock, blk), (char *)idblk, sblock->fs_bsize);
E 40
I 40
		bread(fsbtodb(sblock, blk), (char *)idblk, (int) sblock->fs_bsize);
E 40
E 6
	else
D 6
		blkclr(idblk, sizeof(idblk));
E 6
I 6
D 15
		blkclr(idblk, sblock->fs_bsize);
E 15
I 15
D 26
		bzero(idblk, sblock->fs_bsize);
E 26
I 26
D 40
		bzero((char *)idblk, sblock->fs_bsize);
E 26
E 15
E 6
D 27
	if (lvl <= 0) {
E 27
I 27
	if (level <= 0) {
E 40
I 40
D 51
		bzero((char *)idblk, (int)sblock->fs_bsize);
E 51
I 51
		memset(idblk, 0, (int)sblock->fs_bsize);
E 51
	if (ind_level <= 0) {
E 40
E 27
D 6
		if (*size < NINDIR * BSIZE)
			cnt = howmany(*size, TP_BSIZE);
E 6
I 6
		if (*size < NINDIR(sblock) * sblock->fs_bsize)
			cnt = howmany(*size, sblock->fs_fsize);
E 6
		else
D 6
			cnt = NINDIR * BLKING * FRAG;
		*size -= NINDIR * BSIZE;
E 6
I 6
			cnt = NINDIR(sblock) * sblock->fs_frag;
		*size -= NINDIR(sblock) * sblock->fs_bsize;
E 6
D 27
		blksout(&idblk[0], cnt);
E 27
I 27
		blksout(&idblk[0], cnt, ino);
E 27
		return;
E 5
	}
D 5
	spclrec();
E 5
I 5
D 27
	lvl--;
E 27
I 27
D 40
	level--;
E 40
I 40
	ind_level--;
E 40
E 27
D 6
	for (i = 0; i < NINDIR; i++) {
E 6
I 6
	for (i = 0; i < NINDIR(sblock); i++) {
E 6
D 27
		dmpindir(idblk[i], lvl, size);
E 27
I 27
D 40
		dmpindir(ino, idblk[i], level, size);
E 40
I 40
		dmpindir(ino, idblk[i], ind_level, size);
E 40
E 27
		if (*size <= 0)
			return;
	}
E 5
}

I 27
/*
 * Collect up the data into tape record sized buffers and output them.
 */
E 27
I 26
void
E 26
I 5
D 27
blksout(blkp, frags)
E 27
I 27
blksout(blkp, frags, ino)
E 27
	daddr_t *blkp;
	int frags;
I 27
	ino_t ino;
E 27
{
I 26
	register daddr_t *bp;
E 26
D 6
	int i, j, count, blks;
E 6
I 6
	int i, j, count, blks, tbperdb;
E 6

D 6
	blks = frags * BLKING;
E 6
I 6
D 13
	blks = frags * BLKING(sblock);
	tbperdb = BLKING(sblock) * sblock->fs_frag;
E 13
I 13
D 14
	blks = frags * sblock->fs_fsize / TP_BSIZE;
E 14
I 14
	blks = howmany(frags * sblock->fs_fsize, TP_BSIZE);
E 14
D 26
	tbperdb = sblock->fs_bsize / TP_BSIZE;
E 26
I 26
	tbperdb = sblock->fs_bsize >> tp_bshift;
E 26
E 13
E 6
	for (i = 0; i < blks; i += TP_NINDIR) {
		if (i + TP_NINDIR > blks)
			count = blks;
		else
			count = i + TP_NINDIR;
		for (j = i; j < count; j++)
D 6
			if (blkp[j / (BLKING * FRAG)] != 0)
E 6
I 6
			if (blkp[j / tbperdb] != 0)
E 6
				spcl.c_addr[j - i] = 1;
			else
				spcl.c_addr[j - i] = 0;
		spcl.c_count = count - i;
D 27
		spclrec();
E 27
I 27
		writeheader(ino);
E 27
D 6
		for (j = i; j < count; j += (BLKING * FRAG))
			if (blkp[j / (BLKING * FRAG)] != 0)
				if (j + (BLKING * FRAG) <= count)
					dmpblk(blkp[j / (BLKING * FRAG)],
					    BSIZE);
E 6
I 6
D 26
		for (j = i; j < count; j += tbperdb)
			if (blkp[j / tbperdb] != 0)
E 26
I 26
		bp = &blkp[i / tbperdb];
		for (j = i; j < count; j += tbperdb, bp++)
			if (*bp != 0)
E 26
				if (j + tbperdb <= count)
D 26
					dmpblk(blkp[j / tbperdb],
					    sblock->fs_bsize);
E 26
I 26
D 27
					dmpblk(*bp, sblock->fs_bsize);
E 27
I 27
D 40
					dumpblock(*bp, sblock->fs_bsize);
E 40
I 40
					dumpblock(*bp, (int)sblock->fs_bsize);
E 40
E 27
E 26
E 6
				else
D 6
					dmpblk(blkp[j / (BLKING * FRAG)],
E 6
I 6
D 26
					dmpblk(blkp[j / tbperdb],
E 6
					    (count - j) * TP_BSIZE);
E 26
I 26
D 27
					dmpblk(*bp, (count - j) * TP_BSIZE);
E 27
I 27
					dumpblock(*bp, (count - j) * TP_BSIZE);
E 27
E 26
		spcl.c_type = TS_ADDR;
	}
}

I 27
/*
 * Dump a map to the tape.
 */
E 27
I 26
void
E 26
E 5
D 27
bitmap(map, typ)
E 27
I 27
dumpmap(map, type, ino)
E 27
D 5
short *map;
E 5
I 5
D 6
	short *map;
E 6
I 6
	char *map;
I 26
D 27
	int typ;
E 27
I 27
	int type;
	ino_t ino;
E 27
E 26
E 6
E 5
{
D 18
	register i, n;
E 18
I 18
D 27
	register i;
E 27
I 27
	register int i;
E 27
E 18
	char *cp;

D 18
	n = -1;
D 6
	for(i=0; i<MSIZ; i++)
E 6
I 6
	for (i = 0; i < msiz; i++)
E 6
		if(map[i])
			n = i;
D 6
	if(n < 0)
E 6
I 6
	if (n < 0)
E 6
		return;
I 6
	n++;
E 18
E 6
D 27
	spcl.c_type = typ;
D 5
	spcl.c_count = (n*sizeof(map[0]) + BSIZE)/BSIZE;
E 5
I 5
D 6
	spcl.c_count = (n*sizeof(map[0]) + TP_BSIZE)/TP_BSIZE;
E 6
I 6
D 18
	spcl.c_count = howmany(n * sizeof(map[0]), TP_BSIZE);
E 18
I 18
	spcl.c_count = howmany(msiz * sizeof(map[0]), TP_BSIZE);
E 18
E 6
E 5
	spclrec();
E 27
I 27
	spcl.c_type = type;
	spcl.c_count = howmany(mapsize * sizeof(char), TP_BSIZE);
	writeheader(ino);
E 27
D 6
	cp = (char *)map;
	for(i=0; i<spcl.c_count; i++) {
E 6
I 6
	for (i = 0, cp = map; i < spcl.c_count; i++, cp += TP_BSIZE)
E 6
D 27
		taprec(cp);
E 27
I 27
D 41
		writerec(cp);
E 41
I 41
		writerec(cp, 0);
E 41
E 27
D 5
		cp += BSIZE;
E 5
I 5
D 6
		cp += TP_BSIZE;
E 5
	}
E 6
}

I 27
/*
 * Write a header record to the dump tape.
 */
E 27
I 26
void
E 26
D 27
spclrec()
E 27
I 27
writeheader(ino)
	ino_t ino;
E 27
{
D 5
	register i, *ip, s;
E 5
I 5
D 27
	register int s, i, *ip;
E 27
I 27
	register long sum, cnt, *lp;
E 27
E 5

	spcl.c_inumber = ino;
D 11
	spcl.c_magic = MAGIC;
E 11
I 11
	spcl.c_magic = NFS_MAGIC;
E 11
	spcl.c_checksum = 0;
D 27
	ip = (int *)&spcl;
	s = 0;
D 5
	for(i=0; i<BSIZE/sizeof(*ip); i++)
E 5
I 5
D 21
	for(i = 0; i < sizeof(union u_spcl)/sizeof(int); i++)
E 5
		s += *ip++;
E 21
I 21
	i = sizeof(union u_spcl) / (4*sizeof(int));
	while (--i >= 0) {
		s += *ip++; s += *ip++;
		s += *ip++; s += *ip++;
E 27
I 27
	lp = (long *)&spcl;
	sum = 0;
	cnt = sizeof(union u_spcl) / (4 * sizeof(long));
	while (--cnt >= 0) {
		sum += *lp++;
		sum += *lp++;
		sum += *lp++;
		sum += *lp++;
E 27
	}
E 21
D 27
	spcl.c_checksum = CHECKSUM - s;
	taprec((char *)&spcl);
E 27
I 27
	spcl.c_checksum = CHECKSUM - sum;
D 41
	writerec((char *)&spcl);
E 41
I 41
	writerec((char *)&spcl, 1);
E 41
E 27
}

I 26
D 27
void
E 26
D 6
dsrch(d)
E 6
I 6
D 16
dsrch(d, size)
E 16
I 16
dsrch(d, size, filesize)
E 16
E 6
D 5
daddr_t d;
E 5
I 5
	daddr_t d;
I 6
D 16
	int size;
E 16
I 16
	int size, filesize;
E 16
E 6
E 5
{
D 8
	register char *cp;
	register i;
	register ino_t in;
D 6
	struct direct dblk[DIRPB];
E 6
I 6
	struct direct dblk[MAXDIRPB];
E 8
I 8
	register struct direct *dp;
	long loc;
	char dblk[MAXBSIZE];
E 8
E 6

	if(dadded)
		return;
D 6
	bread(d, (char *)dblk, sizeof(dblk));
	for(i=0; i<DIRPB; i++) {
E 6
I 6
D 8
	bread(fsbtodb(sblock, d), (char *)dblk, size);
	for(i=0; i < DIRPB(sblock); i++) {
E 6
		in = dblk[i].d_ino;
		if(in == 0)
E 8
I 8
D 17
	bread(fsbtodb(sblock, d), dblk, size);
E 17
D 16
	for (loc = 0; loc < size; ) {
E 16
I 16
	if (filesize > size)
		filesize = size;
I 17
	bread(fsbtodb(sblock, d), dblk, filesize);
E 17
	for (loc = 0; loc < filesize; ) {
E 16
		dp = (struct direct *)(dblk + loc);
D 16
		if (dp->d_reclen == 0)
E 16
I 16
		if (dp->d_reclen == 0) {
			msg("corrupted directory, inumber %d\n", ino);
E 16
			break;
I 16
		}
E 16
		loc += dp->d_reclen;
		if(dp->d_ino == 0)
E 8
			continue;
D 8
		cp = dblk[i].d_name;
		if(cp[0] == '.') {
			if(cp[1] == '\0')
E 8
I 8
		if(dp->d_name[0] == '.') {
			if(dp->d_name[1] == '\0')
E 8
				continue;
D 8
			if(cp[1] == '.' && cp[2] == '\0')
E 8
I 8
			if(dp->d_name[1] == '.' && dp->d_name[2] == '\0')
E 8
				continue;
		}
D 8
		if(BIT(in, nodmap)) {
E 8
I 8
		if(BIT(dp->d_ino, nodmap)) {
E 8
			dadded++;
			return;
		}
D 8
		if(BIT(in, dirmap))
E 8
I 8
		if(BIT(dp->d_ino, dirmap))
E 8
			nsubdir++;
	}
}

E 27
D 5
nullf()
{
}

E 5
I 2
struct dinode *
D 27
getino(ino)
	daddr_t ino;
E 27
I 27
getino(inum)
	ino_t inum;
E 27
{
	static daddr_t minino, maxino;
D 6
	static struct dinode itab[INOPB];
E 6
I 6
D 27
	static struct dinode itab[MAXINOPB];
E 27
I 27
	static struct dinode inoblock[MAXINOPB];
E 27
E 6

D 26
	if (ino >= minino && ino < maxino) {
E 26
I 26
D 27
	if (ino >= minino && ino < maxino)
E 26
		return (&itab[ino - minino]);
D 26
	}
E 26
D 6
	bread(itod(ino, &sblock), itab, BSIZE);
	minino = ino - (ino % INOPB);
	maxino = minino + INOPB;
E 6
I 6
D 7
	bread(fsbtodb(sblock, itod(ino, sblock)), itab, sblock->fs_bsize);
E 7
I 7
	bread(fsbtodb(sblock, itod(sblock, ino)), itab, sblock->fs_bsize);
E 7
	minino = ino - (ino % INOPB(sblock));
E 27
I 27
	curino = inum;
	if (inum >= minino && inum < maxino)
		return (&inoblock[inum - minino]);
D 40
	bread(fsbtodb(sblock, itod(sblock, inum)), inoblock, sblock->fs_bsize);
E 40
I 40
D 49
	bread(fsbtodb(sblock, itod(sblock, inum)), (char *)inoblock,
E 49
I 49
	bread(fsbtodb(sblock, ino_to_fsba(sblock, inum)), (char *)inoblock,
E 49
	    (int)sblock->fs_bsize);
E 40
	minino = inum - (inum % INOPB(sblock));
E 27
	maxino = minino + INOPB(sblock);
E 6
D 27
	return (&itab[ino - minino]);
E 27
I 27
	return (&inoblock[inum - minino]);
E 27
}

I 27
/*
 * Read a chunk of data from the disk.
 * Try to recover from hard errors by reading in sector sized pieces.
 * Error recovery is attempted at most BREADEMAX times before seeking
 * consent from the operator to continue.
 */
E 27
E 2
int	breaderrors = 0;		
#define	BREADEMAX 32

I 26
void
E 26
D 17
bread(da, ba, c)
E 17
I 17
D 27
bread(da, ba, cnt)
E 17
	daddr_t da;
	char *ba;
D 17
	int	c;	
E 17
I 17
	int	cnt;	
E 27
I 27
bread(blkno, buf, size)
	daddr_t blkno;
	char *buf;
	int size;	
E 27
E 17
{
D 17
	register n;
	register	regc;
E 17
I 17
D 25
	int n;
E 25
I 25
D 27
	int n, i;
E 27
I 27
	int cnt, i;
E 27
	extern int errno;
E 25
E 17

I 17
loop:
E 17
D 2
	if (lseek(fi, (long)(da*BSIZE), 0) < 0){
E 2
I 2
D 6
	if (lseek(fi, (long)(da*FSIZE), 0) < 0){
E 6
I 6
D 23
	if (lseek(fi, (long)(da * DEV_BSIZE), 0) < 0){
E 23
I 23
D 26
	if (lseek(fi, (long)(da * dev_bsize), 0) < 0){
E 26
I 26
D 27
	if (lseek(fi, (long)(da << dev_bshift), 0) < 0)
E 27
I 27
D 40
	if (lseek(diskfd, (long)(blkno << dev_bshift), 0) < 0)
E 40
I 40
D 50
	if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 50
I 50
D 53
	if (lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 53
I 53
D 54
	if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 54
I 54
	if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) == -1)
E 54
E 53
E 50
E 40
E 27
E 26
E 23
E 6
E 2
		msg("bread: lseek fails\n");
D 26
	}
E 26
D 17
	regc = c;	/* put c someplace safe; it gets clobbered */
	n = read(fi, ba, c);
D 6
	if(n != c || regc != c){
E 6
I 6
	if (n != c || regc != c) {
E 6
		msg("(This should not happen)bread from %s [block %d]: c=0x%x, regc=0x%x, &c=0x%x, n=0x%x\n",
			disk, da, c, regc, &c, n);
#ifdef ERNIE
		msg("Notify Robert Henry of this error.\n");
#endif
		if (++breaderrors > BREADEMAX){
			msg("More than %d block read errors from %d\n",
				BREADEMAX, disk);
			broadcast("DUMP IS AILING!\n");
			msg("This is an unrecoverable error.\n");
			if (!query("Do you want to attempt to continue?")){
				dumpabort();
				/*NOTREACHED*/
			} else
				breaderrors = 0;
		}
E 17
I 17
D 27
	n = read(fi, ba, cnt);
	if (n == cnt)
E 27
I 27
	if ((cnt = read(diskfd, buf, size)) == size)
E 27
		return;
D 23
	if (da + (cnt / DEV_BSIZE) > fsbtodb(sblock, sblock->fs_size)) {
E 23
I 23
D 27
	if (da + (cnt / dev_bsize) > fsbtodb(sblock, sblock->fs_size)) {
E 27
I 27
	if (blkno + (size / dev_bsize) > fsbtodb(sblock, sblock->fs_size)) {
E 27
E 23
		/*
		 * Trying to read the final fragment.
		 *
		 * NB - dump only works in TP_BSIZE blocks, hence
D 23
		 * rounds DEV_BSIZE fragments up to TP_BSIZE pieces.
E 23
I 23
		 * rounds `dev_bsize' fragments up to TP_BSIZE pieces.
E 23
		 * It should be smarter about not actually trying to
		 * read more than it can get, but for the time being
		 * we punt and scale back the read only when it gets
		 * us into trouble. (mkm 9/25/83)
		 */
D 23
		cnt -= DEV_BSIZE;
E 23
I 23
D 27
		cnt -= dev_bsize;
E 27
I 27
		size -= dev_bsize;
E 27
E 23
		goto loop;
	}
D 25
	msg("(This should not happen)bread from %s [block %d]: count=%d, got=%d\n",
		disk, da, cnt, n);
E 25
I 25
D 26
	msg("read error from %s [block %d]: count=%d, got=%d, errno=%d\n",
		disk, da, cnt, n, errno);
E 25
	if (++breaderrors > BREADEMAX){
E 26
I 26
D 34
	msg("read error from %s [block %d]: count=%d, got=%d, errno=%d (%s)\n",
D 27
		disk, da, cnt, n, errno, strerror(errno));
E 27
I 27
		disk, blkno, size, cnt, errno, strerror(errno));
E 34
I 34
	if (cnt == -1)
		msg("read error from %s: %s: [block %d]: count=%d\n",
			disk, strerror(errno), blkno, size);
	else
		msg("short read error from %s: [block %d]: count=%d, got=%d\n",
			disk, blkno, size, cnt);
E 34
E 27
	if (++breaderrors > BREADEMAX) {
E 26
		msg("More than %d block read errors from %d\n",
			BREADEMAX, disk);
		broadcast("DUMP IS AILING!\n");
		msg("This is an unrecoverable error.\n");
		if (!query("Do you want to attempt to continue?")){
D 42
			dumpabort();
E 42
I 42
			dumpabort(0);
E 42
			/*NOTREACHED*/
		} else
			breaderrors = 0;
I 25
	}
	/*
	 * Zero buffer, then try to read each sector of buffer separately.
	 */
D 27
	bzero(ba, cnt);
	for (i = 0; i < cnt; i += dev_bsize, ba += dev_bsize, da++) {
D 26
		if (lseek(fi, (long)(da * dev_bsize), 0) < 0)
E 26
I 26
		if (lseek(fi, (long)(da << dev_bshift), 0) < 0)
E 27
I 27
D 51
	bzero(buf, size);
E 51
I 51
	memset(buf, 0, size);
E 51
	for (i = 0; i < size; i += dev_bsize, buf += dev_bsize, blkno++) {
D 40
		if (lseek(diskfd, (long)(blkno << dev_bshift), 0) < 0)
E 40
I 40
D 50
		if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 50
I 50
D 53
		if (lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 53
I 53
D 54
		if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) < 0)
E 54
I 54
		if ((int)lseek(diskfd, ((off_t)blkno << dev_bshift), 0) == -1)
E 54
E 53
E 50
E 40
E 27
E 26
			msg("bread: lseek2 fails!\n");
D 27
		n = read(fi, ba, dev_bsize);
		if (n != dev_bsize)
E 27
I 27
D 34
		if ((cnt = read(diskfd, buf, dev_bsize)) != dev_bsize)
E 27
			msg("    read error from %s [sector %d, errno %d]\n",
D 27
			    disk, da, errno);
E 27
I 27
			    disk, blkno, errno);
E 34
I 34
D 40
		if ((cnt = read(diskfd, buf, dev_bsize)) == dev_bsize)
E 40
I 40
		if ((cnt = read(diskfd, buf, (int)dev_bsize)) == dev_bsize)
E 40
			continue;
		if (cnt == -1) {
			msg("read error from %s: %s: [sector %d]: count=%d\n",
				disk, strerror(errno), blkno, dev_bsize);
			continue;
		}
		msg("short read error from %s: [sector %d]: count=%d, got=%d\n",
			disk, blkno, dev_bsize, cnt);
E 34
E 27
E 25
E 17
	}
D 6
}

CLR(map)
D 5
register short *map;
E 5
I 5
	register short *map;
E 5
{
	register n;

	n = MSIZ;
	do
		*map++ = 0;
	while(--n);
E 6
D 15
}

I 5
blkclr(cp, size)
	char *cp;
	long size;
{
	asm("movc5	$0,(r0),$0,8(ap),*4(ap)");
E 15
}
E 5
E 1
