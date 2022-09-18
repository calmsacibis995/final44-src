h44234
s 00003/00004/00533
d D 8.8 95/04/28 10:38:06 bostic 44 43
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00026/00009/00511
d D 8.7 95/04/27 11:32:51 mckusick 43 42
c add function prototypes
e
s 00012/00012/00508
d D 8.6 95/03/21 00:10:40 mckusick 42 41
c daddr_t => ufs_daddr_t
e
s 00004/00001/00516
d D 8.5 95/02/08 20:14:08 mckusick 41 40
c note parent of root inode, so that replacing ".." will work
e
s 00003/00004/00514
d D 8.4 94/04/18 19:10:31 mckusick 40 39
c count the size of holes as well as blocks
e
s 00002/00000/00516
d D 8.3 94/02/27 00:22:18 mkm 39 38
c set maptype when allocating new inodes
e
s 00002/00002/00514
d D 8.2 93/09/23 19:36:54 bostic 38 37
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00514
d D 8.1 93/06/05 10:56:22 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00515
d D 5.25 93/06/04 11:42:14 bostic 36 35
c rename devname to cdevname, devname(3) now in the C library
e
s 00004/00001/00512
d D 5.24 92/07/02 16:27:18 mckusick 35 34
c treat short symlinks like BLK and CHR devices
e
s 00002/00002/00511
d D 5.23 92/06/18 18:56:05 mckusick 34 33
c timeval => timespec
e
s 00014/00008/00499
d D 5.22 92/06/02 23:31:35 mckusick 33 32
c properly calculate indirect block sizes
e
s 00006/00004/00501
d D 5.21 92/06/02 21:37:31 mckusick 32 31
c size now has to be printed out as a quad
e
s 00001/00001/00504
d D 5.20 92/03/16 20:41:42 mckusick 31 30
c file sizes are now 64-bits
e
s 00003/00003/00502
d D 5.19 91/11/04 22:20:28 bostic 30 29
c break FFS into UFS/FFS/LFS
e
s 00001/00001/00504
d D 5.18 91/03/19 15:33:49 mckusick 29 28
c eliminate bletcherous code
e
s 00002/00001/00503
d D 5.17 90/07/27 14:44:45 mckusick 28 27
c do not reset if IGNORE has been requested
e
s 00017/00015/00487
d D 5.16 90/07/20 16:51:39 mckusick 27 26
c lint (from Torek)
e
s 00001/00011/00501
d D 5.15 90/06/01 16:16:37 bostic 26 25
c new copyright notice
e
s 00002/00002/00510
d D 5.14 90/03/27 18:04:37 mckusick 25 24
c initialize startinum and inode buffer pointer for each run
e
s 00109/00042/00403
d D 5.13 90/02/07 00:19:52 mckusick 24 23
c struct inoinfo is promoted to fsck.h;
c add routines to manage pass1 inode buffer;
c getcacheino is merged into pass2;
c allow sortlist to grow if calculation of number of directories is wrong;
c simplify cleanup of inoinfo data structures
e
s 00078/00000/00367
d D 5.12 90/02/01 23:36:21 mckusick 23 22
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00015/00004/00352
d D 5.11 90/02/01 17:17:39 mckusick 22 21
c convert to BSD only copyright
e
s 00047/00042/00309
d D 5.10 90/02/01 16:17:58 mckusick 21 20
c lint and other aesthetic cleanups
e
s 00001/00003/00350
d D 5.9 89/10/24 19:05:39 mckusick 20 19
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00005/00003/00348
d D 5.8 89/06/26 21:41:45 mckusick 19 18
c new include file locations engendered by vnodes
e
s 00001/00001/00350
d D 5.7 89/03/05 14:07:48 bostic 18 17
c pwd.h needs types.h
e
s 00025/00012/00326
d D 5.6 88/05/07 01:04:14 mckusick 17 16
c expand from three static buffer to a dynamic buffer pool;
c initial sizing of the buffer pool is 128K (For 8K fs == 16 buffers)
e
s 00001/00001/00337
d D 5.5 87/12/21 12:41:34 bostic 16 15
c make ANSI C compatible
e
s 00001/00001/00337
d D 5.4 87/10/22 10:52:20 bostic 15 14
c ANSI C; sprintf now returns an int.
e
s 00002/00004/00336
d D 5.3 87/01/07 19:26:42 mckusick 14 13
c be more persistent in trying to read directories; 
c add FOUND return status for routines called from dirscan
e
s 00004/00001/00336
d D 5.2 85/07/17 16:46:04 mckusick 13 12
c more descriptive error message
e
s 00008/00002/00329
d D 5.1 85/06/05 08:54:49 dist 12 11
c Add copyright
e
s 00003/00005/00328
d D 3.11 85/05/31 00:19:28 mckusick 11 10
c check for improper directory offsets; recover gracefully from read errors
e
s 00005/00008/00328
d D 3.10 85/02/22 15:07:09 mckusick 10 9
c replace getpw with getpwuid
e
s 00003/00003/00333
d D 3.9 85/02/18 15:33:02 mckusick 9 8
c initialization bug in ckinode()
e
s 00014/00003/00322
d D 3.8 85/02/15 12:09:12 mckusick 8 7
c calc and print out pathname of offending hard links to directories
e
s 00001/00000/00324
d D 3.7 85/02/15 12:06:56 mckusick 7 6
c filesize now set by ckinode(); pass1() uses id_entryno to calc block count
e
s 00069/00000/00255
d D 3.6 85/02/13 18:22:43 mckusick 6 5
c create lost+found directory if none already in existence
e
s 00013/00000/00242
d D 3.5 85/02/13 15:26:12 mckusick 5 4
c check for blocks allocated past end of file in indirect blocks
e
s 00005/00008/00237
d D 3.4 85/02/11 18:29:16 mckusick 4 3
c ginode() succeeds or exits
e
s 00018/00002/00227
d D 3.3 85/02/08 19:15:09 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00009/00012/00220
d D 3.2 85/02/07 17:51:37 mckusick 2 1
c code reorganization and cleanup
e
s 00232/00000/00000
d D 3.1 84/03/31 21:03:42 mckusick 1 0
c date and time created 84/03/31 21:03:42 by mckusick
e
u
U
t
T
I 12
/*
D 22
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
D 37
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 37
I 37
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 22
 */

E 12
I 1
#ifndef lint
D 12
static char version[] = "%W% (Berkeley) %G%";
#endif
E 12
I 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22
E 12

I 10
D 18
#include <pwd.h>
E 18
E 10
#include <sys/param.h>
I 32
#include <sys/time.h>
I 43

E 43
E 32
D 19
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/dir.h>
E 19
I 19
D 20
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 20
I 20
D 30
#include <ufs/dinode.h>
E 20
#include <ufs/fs.h>
#include <ufs/dir.h>
E 30
I 30
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
#include <ufs/ffs/fs.h>
I 43

#include <err.h>
E 43
E 30
E 19
I 18
#include <pwd.h>
I 27
D 43
#include <stdlib.h>
E 43
#include <string.h>
I 43

E 43
E 27
E 18
#include "fsck.h"

I 17
D 21
BUFAREA *pbp = 0;
E 21
I 21
D 25
struct bufarea *pbp = 0;
E 25
I 25
static ino_t startinum;
E 25
I 23
D 24
/*
 * Inode cache data structures.
 */
struct inoinfo {
	struct	inoinfo *i_next;	/* next entry in hash chain */
	ino_t	i_number;		/* inode number of this entry */
	size_t	i_size;			/* size of inode */
	u_int	i_numblks;		/* size of block array */
	daddr_t	i_blks[1];		/* actually longer */
} **inphead;
long hashsize;
E 24
E 23
E 21

I 43
static int iblock __P((struct inodesc *, long ilevel, quad_t isize));

int
E 43
E 17
ckinode(dp, idesc)
D 21
	DINODE *dp;
E 21
I 21
	struct dinode *dp;
E 21
	register struct inodesc *idesc;
{
D 42
	register daddr_t *ap;
E 42
I 42
	ufs_daddr_t *ap;
E 42
D 21
	int ret, n, ndb, offset;
	DINODE dino;
E 21
I 21
	long ret, n, ndb, offset;
	struct dinode dino;
I 33
	quad_t remsize, sizepb;
I 35
	mode_t mode;
E 35
E 33
E 21

D 2
	if (SPECIAL)
E 2
I 2
D 9
	if (SPECIAL(dp))
E 2
		return (KEEPON);
	dino = *dp;
E 9
D 28
	idesc->id_fix = DONTKNOW;
E 28
I 28
	if (idesc->id_fix != IGNORE)
		idesc->id_fix = DONTKNOW;
E 28
	idesc->id_entryno = 0;
I 7
	idesc->id_filesize = dp->di_size;
I 9
D 21
	if (SPECIAL(dp))
E 21
I 21
D 35
	if ((dp->di_mode & IFMT) == IFBLK || (dp->di_mode & IFMT) == IFCHR)
E 35
I 35
	mode = dp->di_mode & IFMT;
	if (mode == IFBLK || mode == IFCHR || (mode == IFLNK &&
	    dp->di_size < sblock.fs_maxsymlinklen))
E 35
E 21
		return (KEEPON);
	dino = *dp;
E 9
E 7
	ndb = howmany(dino.di_size, sblock.fs_bsize);
	for (ap = &dino.di_db[0]; ap < &dino.di_db[NDADDR]; ap++) {
		if (--ndb == 0 && (offset = blkoff(&sblock, dino.di_size)) != 0)
			idesc->id_numfrags =
				numfrags(&sblock, fragroundup(&sblock, offset));
		else
			idesc->id_numfrags = sblock.fs_frag;
		if (*ap == 0)
			continue;
		idesc->id_blkno = *ap;
		if (idesc->id_type == ADDR)
			ret = (*idesc->id_func)(idesc);
		else
			ret = dirscan(idesc);
		if (ret & STOP)
			return (ret);
	}
	idesc->id_numfrags = sblock.fs_frag;
I 33
	remsize = dino.di_size - sblock.fs_bsize * NDADDR;
	sizepb = sblock.fs_bsize;
E 33
D 2
	for (ap = &dino.di_ib[0], n = 1; n <= 2; ap++, n++) {
E 2
I 2
	for (ap = &dino.di_ib[0], n = 1; n <= NIADDR; ap++, n++) {
E 2
		if (*ap) {
			idesc->id_blkno = *ap;
D 33
			ret = iblock(idesc, n,
				dino.di_size - sblock.fs_bsize * NDADDR);
E 33
I 33
			ret = iblock(idesc, n, remsize);
E 33
			if (ret & STOP)
				return (ret);
		}
I 33
		sizepb *= NINDIR(&sblock);
		remsize -= sizepb;
E 33
	}
	return (KEEPON);
}

I 43
static int
E 43
iblock(idesc, ilevel, isize)
	struct inodesc *idesc;
D 21
	register ilevel;
E 21
I 21
D 33
	register long ilevel;
E 33
I 33
	long ilevel;
E 33
E 21
D 27
	long isize;
E 27
I 27
D 31
	u_long isize;
E 31
I 31
	quad_t isize;
E 31
E 27
{
D 42
	register daddr_t *ap;
	register daddr_t *aplim;
D 2
	int i, n, (*func)(), nif;
E 2
I 2
D 32
	int i, n, (*func)(), nif, sizepb;
E 32
E 2
D 17
	BUFAREA ib;
E 17
I 17
D 21
	register BUFAREA *bp;
E 21
I 21
	register struct bufarea *bp;
E 42
I 42
	ufs_daddr_t *ap;
	ufs_daddr_t *aplim;
	struct bufarea *bp;
E 42
I 32
	int i, n, (*func)(), nif;
	quad_t sizepb;
E 32
E 21
E 17
I 13
	char buf[BUFSIZ];
E 13
I 5
D 16
	extern int pass1check();
E 16
I 16
D 43
	extern int dirscan(), pass1check();
E 43
E 16
E 5

	if (idesc->id_type == ADDR) {
		func = idesc->id_func;
		if (((n = (*func)(idesc)) & KEEPON) == 0)
			return (n);
	} else
		func = dirscan;
D 21
	if (outrange(idesc->id_blkno, idesc->id_numfrags)) /* protect thyself */
E 21
I 21
	if (chkrange(idesc->id_blkno, idesc->id_numfrags))
E 21
		return (SKIP);
D 17
	initbarea(&ib);
D 11
	if (getblk(&ib, idesc->id_blkno, sblock.fs_bsize) == NULL)
E 11
I 11
	getblk(&ib, idesc->id_blkno, sblock.fs_bsize);
E 17
I 17
	bp = getdatablk(idesc->id_blkno, sblock.fs_bsize);
E 17
D 14
	if (ib.b_errs != NULL)
E 11
		return (SKIP);
E 14
	ilevel--;
D 2
	if (ilevel == 0) {
		nif = lblkno(&sblock, isize) + 1;
	} else /* ilevel == 1 */ {
		nif = isize / (sblock.fs_bsize * NINDIR(&sblock)) + 1;
	}
E 2
I 2
	for (sizepb = sblock.fs_bsize, i = 0; i < ilevel; i++)
		sizepb *= NINDIR(&sblock);
D 33
	nif = isize / sizepb + 1;
E 33
I 33
	nif = howmany(isize , sizepb);
E 33
E 2
	if (nif > NINDIR(&sblock))
		nif = NINDIR(&sblock);
I 5
	if (idesc->id_func == pass1check && nif < NINDIR(&sblock)) {
D 17
		aplim = &ib.b_un.b_indir[NINDIR(&sblock)];
		for (ap = &ib.b_un.b_indir[nif]; ap < aplim; ap++) {
E 17
I 17
		aplim = &bp->b_un.b_indir[NINDIR(&sblock)];
		for (ap = &bp->b_un.b_indir[nif]; ap < aplim; ap++) {
E 17
			if (*ap == 0)
				continue;
D 13
			if (dofix(idesc, "PARTIALLY TRUNCATED INODE")) {
E 13
I 13
D 15
			sprintf(buf, "PARTIALLY TRUNCATED INODE I=%d",
E 15
I 15
D 27
			(void)sprintf(buf, "PARTIALLY TRUNCATED INODE I=%d",
E 27
I 27
			(void)sprintf(buf, "PARTIALLY TRUNCATED INODE I=%lu",
E 27
E 15
				idesc->id_number);
			if (dofix(idesc, buf)) {
E 13
				*ap = 0;
D 17
				dirty(&ib);
E 17
I 17
				dirty(bp);
E 17
			}
		}
D 17
		flush(&dfile, &ib);
E 17
I 17
D 21
		flush(&dfile, bp);
E 21
I 21
		flush(fswritefd, bp);
E 21
E 17
	}
E 5
D 17
	aplim = &ib.b_un.b_indir[nif];
	for (ap = ib.b_un.b_indir, i = 1; ap < aplim; ap++, i++)
E 17
I 17
	aplim = &bp->b_un.b_indir[nif];
D 33
	for (ap = bp->b_un.b_indir, i = 1; ap < aplim; ap++, i++) {
E 33
I 33
	for (ap = bp->b_un.b_indir; ap < aplim; ap++) {
E 33
E 17
		if (*ap) {
			idesc->id_blkno = *ap;
D 33
			if (ilevel > 0)
D 2
				n = iblock(idesc, ilevel,
				    isize - i*NINDIR(&sblock)*sblock.fs_bsize);
E 2
I 2
				n = iblock(idesc, ilevel, isize - i * sizepb);
E 2
			else
E 33
I 33
D 40
			if (ilevel == 0) {
E 40
I 40
			if (ilevel == 0)
E 40
E 33
				n = (*func)(idesc);
I 33
D 40
			} else {
E 40
I 40
			else
E 40
				n = iblock(idesc, ilevel, isize);
D 40
				isize -= sizepb;
			}
E 40
E 33
D 17
			if (n & STOP)
E 17
I 17
			if (n & STOP) {
				bp->b_flags &= ~B_INUSE;
E 17
				return (n);
I 17
			}
E 17
		}
I 40
		isize -= sizepb;
E 40
I 17
	}
	bp->b_flags &= ~B_INUSE;
E 17
	return (KEEPON);
}

D 21
outrange(blk, cnt)
E 21
I 21
/*
 * Check that a block in a legal block number.
 * Return 0 if in range, 1 if out of range.
 */
I 43
int
E 43
chkrange(blk, cnt)
E 21
D 42
	daddr_t blk;
E 42
I 42
	ufs_daddr_t blk;
E 42
	int cnt;
{
	register int c;

D 21
	if ((unsigned)(blk+cnt) > fmax)
E 21
I 21
	if ((unsigned)(blk + cnt) > maxfsblock)
E 21
		return (1);
	c = dtog(&sblock, blk);
	if (blk < cgdmin(&sblock, c)) {
D 21
		if ((blk+cnt) > cgsblock(&sblock, c)) {
E 21
I 21
		if ((blk + cnt) > cgsblock(&sblock, c)) {
E 21
			if (debug) {
D 27
				printf("blk %d < cgdmin %d;",
E 27
I 27
				printf("blk %ld < cgdmin %ld;",
E 27
				    blk, cgdmin(&sblock, c));
D 21
				printf(" blk+cnt %d > cgsbase %d\n",
				    blk+cnt, cgsblock(&sblock, c));
E 21
I 21
D 27
				printf(" blk + cnt %d > cgsbase %d\n",
E 27
I 27
				printf(" blk + cnt %ld > cgsbase %ld\n",
E 27
				    blk + cnt, cgsblock(&sblock, c));
E 21
			}
			return (1);
		}
	} else {
D 21
		if ((blk+cnt) > cgbase(&sblock, c+1)) {
E 21
I 21
		if ((blk + cnt) > cgbase(&sblock, c+1)) {
E 21
			if (debug)  {
D 27
				printf("blk %d >= cgdmin %d;",
E 27
I 27
				printf("blk %ld >= cgdmin %ld;",
E 27
				    blk, cgdmin(&sblock, c));
D 21
				printf(" blk+cnt %d > sblock.fs_fpg %d\n",
E 21
I 21
D 27
				printf(" blk + cnt %d > sblock.fs_fpg %d\n",
E 27
I 27
				printf(" blk + cnt %ld > sblock.fs_fpg %ld\n",
E 27
E 21
				    blk+cnt, sblock.fs_fpg);
			}
			return (1);
		}
	}
	return (0);
}

I 24
/*
 * General purpose interface for reading inodes.
 */
E 24
D 21
DINODE *
E 21
I 21
struct dinode *
E 21
ginode(inumber)
	ino_t inumber;
{
D 42
	daddr_t iblk;
E 42
I 42
	ufs_daddr_t iblk;
E 42
D 21
	static ino_t startinum = 0;	/* blk num of first in raw area */
E 21
I 21
D 25
	static ino_t startinum = 0;
E 25
E 21

D 11

E 11
D 4
	if (inumber < ROOTINO || inumber > imax) {
		if (debug && inumber > imax)
			printf("inumber out of range (%d)\n", inumber);
		return (NULL);
	}
E 4
I 4
D 21
	if (inumber < ROOTINO || inumber > imax)
E 21
I 21
	if (inumber < ROOTINO || inumber > maxino)
E 21
D 43
		errexit("bad inode number %d to ginode\n", inumber);
E 43
I 43
		errx(EEXIT, "bad inode number %d to ginode", inumber);
E 43
E 4
	if (startinum == 0 ||
	    inumber < startinum || inumber >= startinum + INOPB(&sblock)) {
D 38
		iblk = itod(&sblock, inumber);
E 38
I 38
		iblk = ino_to_fsba(&sblock, inumber);
E 38
D 11
		if (getblk(&inoblk, iblk, sblock.fs_bsize) == NULL) {
			return (NULL);
		}
E 11
I 11
D 17
		getblk(&inoblk, iblk, sblock.fs_bsize);
E 17
I 17
		if (pbp != 0)
			pbp->b_flags &= ~B_INUSE;
		pbp = getdatablk(iblk, sblock.fs_bsize);
E 17
E 11
		startinum = (inumber / INOPB(&sblock)) * INOPB(&sblock);
	}
D 17
	return (&inoblk.b_un.b_dinode[inumber % INOPB(&sblock)]);
E 17
I 17
	return (&pbp->b_un.b_dinode[inumber % INOPB(&sblock)]);
}

I 24
/*
 * Special purpose version of ginode used to optimize first pass
 * over all the inodes in numerical order.
 */
ino_t nextino, lastinum;
long readcnt, readpercg, fullcnt, inobufsize, partialcnt, partialsize;
struct dinode *inodebuf;

struct dinode *
getnextinode(inumber)
	ino_t inumber;
{
	long size;
D 42
	daddr_t dblk;
E 42
I 42
	ufs_daddr_t dblk;
E 42
	static struct dinode *dp;

	if (inumber != nextino++ || inumber > maxino)
D 43
		errexit("bad inode number %d to nextinode\n", inumber);
E 43
I 43
		errx(EEXIT, "bad inode number %d to nextinode", inumber);
E 43
	if (inumber >= lastinum) {
		readcnt++;
D 38
		dblk = fsbtodb(&sblock, itod(&sblock, lastinum));
E 38
I 38
		dblk = fsbtodb(&sblock, ino_to_fsba(&sblock, lastinum));
E 38
		if (readcnt % readpercg == 0) {
			size = partialsize;
			lastinum += partialcnt;
		} else {
			size = inobufsize;
			lastinum += fullcnt;
		}
D 27
		bread(fsreadfd, (char *)inodebuf, dblk, size);
E 27
I 27
		(void)bread(fsreadfd, (char *)inodebuf, dblk, size); /* ??? */
E 27
		dp = inodebuf;
	}
	return (dp++);
}

I 43
void
E 43
resetinodebuf()
{

I 25
	startinum = 0;
E 25
	nextino = 0;
	lastinum = 0;
	readcnt = 0;
	inobufsize = blkroundup(&sblock, INOBUFSIZE);
	fullcnt = inobufsize / sizeof(struct dinode);
	readpercg = sblock.fs_ipg / fullcnt;
	partialcnt = sblock.fs_ipg % fullcnt;
	partialsize = partialcnt * sizeof(struct dinode);
	if (partialcnt != 0) {
		readpercg++;
	} else {
		partialcnt = fullcnt;
		partialsize = inobufsize;
	}
	if (inodebuf == NULL &&
	    (inodebuf = (struct dinode *)malloc((unsigned)inobufsize)) == NULL)
D 43
		errexit("Cannot allocate space for inode buffer\n");
E 43
I 43
		errx(EEXIT, "Cannot allocate space for inode buffer");
E 43
	while (nextino < ROOTINO)
D 27
		getnextinode(nextino);
E 27
I 27
		(void)getnextinode(nextino);
E 27
}

I 43
void
E 43
freeinodebuf()
{

	if (inodebuf != NULL)
		free((char *)inodebuf);
	inodebuf = NULL;
}

/*
 * Routines to maintain information about directory inodes.
 * This is built during the first pass and used during the
 * second and third passes.
 *
 * Enter inodes into the cache.
 */
I 43
void
E 43
E 24
I 23
cacheino(dp, inumber)
	register struct dinode *dp;
	ino_t inumber;
{
	register struct inoinfo *inp;
	struct inoinfo **inpp;
	unsigned int blks;

D 24
	if (inphead == NULL) {
		hashsize = sblock.fs_cstotal.cs_ndir;
		inphead = (struct inoinfo **)malloc(hashsize * sizeof(daddr_t));
		if (inphead == NULL)
			return;
		bzero((char *)inphead, hashsize * sizeof(daddr_t));
	}
E 24
	blks = howmany(dp->di_size, sblock.fs_bsize);
	if (blks > NDADDR)
		blks = NDADDR + NIADDR;
	inp = (struct inoinfo *)
D 42
		malloc(sizeof(*inp) + (blks - 1) * sizeof(daddr_t));
E 42
I 42
		malloc(sizeof(*inp) + (blks - 1) * sizeof(ufs_daddr_t));
E 42
	if (inp == NULL)
		return;
D 24
	inpp = &inphead[inumber % hashsize];
	inp->i_next = *inpp;
E 24
I 24
	inpp = &inphead[inumber % numdirs];
	inp->i_nexthash = *inpp;
E 24
	*inpp = inp;
I 24
D 41
	inp->i_parent = (ino_t)0;
E 41
I 41
	if (inumber == ROOTINO)
		inp->i_parent = ROOTINO;
	else
		inp->i_parent = (ino_t)0;
E 41
	inp->i_dotdot = (ino_t)0;
E 24
	inp->i_number = inumber;
D 24
	inp->i_size = dp->di_size;
E 24
I 24
	inp->i_isize = dp->di_size;
E 24
D 42
	inp->i_numblks = blks * sizeof(daddr_t);
E 42
I 42
	inp->i_numblks = blks * sizeof(ufs_daddr_t);
E 42
D 24
	bcopy((char *)&dp->di_db[0], (char *)&inp->i_blks[0], inp->i_numblks);
E 24
I 24
D 44
	bcopy((char *)&dp->di_db[0], (char *)&inp->i_blks[0],
D 27
	    (int)inp->i_numblks);
E 27
I 27
	    (size_t)inp->i_numblks);
E 44
I 44
	memmove(&inp->i_blks[0], &dp->di_db[0], (size_t)inp->i_numblks);
E 44
E 27
	if (inplast == listmax) {
		listmax += 100;
		inpsort = (struct inoinfo **)realloc((char *)inpsort,
		    (unsigned)listmax * sizeof(struct inoinfo *));
		if (inpsort == NULL)
D 43
			errexit("cannot increase directory list");
E 43
I 43
			errx(EEXIT, "cannot increase directory list");
E 43
	}
	inpsort[inplast++] = inp;
E 24
}

D 24
struct dinode *
getcacheino(inumber)
E 24
I 24
/*
 * Look up an inode cache structure.
 */
struct inoinfo *
getinoinfo(inumber)
E 24
	ino_t inumber;
{
	register struct inoinfo *inp;
D 24
	static struct dinode dino;
	register struct dinode *dp = &dino;
E 24

D 24
	for (inp = inphead[inumber % hashsize]; inp; inp = inp->i_next) {
E 24
I 24
	for (inp = inphead[inumber % numdirs]; inp; inp = inp->i_nexthash) {
E 24
		if (inp->i_number != inumber)
			continue;
D 24
		dp->di_size = inp->i_size;
		bcopy((char *)&inp->i_blks[0], (char *)&dp->di_db[0],
			inp->i_numblks);
		return (dp);
E 24
I 24
		return (inp);
E 24
	}
D 24
	return (ginode(inumber));
E 24
I 24
D 43
	errexit("cannot find inode %d\n", inumber);
E 43
I 43
	errx(EEXIT, "cannot find inode %d", inumber);
E 43
	return ((struct inoinfo *)0);
E 24
}

I 24
/*
 * Clean up all the inode cache structure.
 */
I 43
void
E 43
E 24
inocleanup()
{
D 24
	register struct inoinfo *inp, **inpp;
	struct inoinfo *inpnext;
E 24
I 24
	register struct inoinfo **inpp;
E 24

	if (inphead == NULL)
		return;
D 24
	for (inpp = &inphead[hashsize - 1]; inpp >= inphead; inpp--) {
		for (inp = *inpp; inp; inp = inpnext) {
			inpnext = inp->i_next;
			free(inp);
		}
	}
	free(inphead);
	inphead = NULL;
E 24
I 24
	for (inpp = &inpsort[inplast - 1]; inpp >= inpsort; inpp--)
		free((char *)(*inpp));
	free((char *)inphead);
	free((char *)inpsort);
	inphead = inpsort = NULL;
E 24
}
	
I 43
void
E 43
E 23
inodirty()
{
	
	dirty(pbp);
E 17
}

I 43
void
E 43
D 21
clri(idesc, s, flg)
E 21
I 21
clri(idesc, type, flag)
E 21
	register struct inodesc *idesc;
D 21
	char *s;
	int flg;
E 21
I 21
	char *type;
	int flag;
E 21
{
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
E 21

D 4
	if ((dp = ginode(idesc->id_number)) == NULL)
		return;
E 4
I 4
	dp = ginode(idesc->id_number);
E 4
D 21
	if (flg == 1) {
D 2
		pwarn("%s %s", s, DIRCT?"DIR":"FILE");
E 2
I 2
		pwarn("%s %s", s, DIRCT(dp) ? "DIR" : "FILE");
E 21
I 21
	if (flag == 1) {
		pwarn("%s %s", type,
		    (dp->di_mode & IFMT) == IFDIR ? "DIR" : "FILE");
E 21
E 2
		pinode(idesc->id_number);
	}
	if (preen || reply("CLEAR") == 1) {
		if (preen)
			printf(" (CLEARED)\n");
		n_files--;
		(void)ckinode(dp, idesc);
D 21
		zapino(dp);
E 21
I 21
		clearinode(dp);
E 21
		statemap[idesc->id_number] = USTATE;
		inodirty();
D 3
		inosumbad++;
E 3
	}
}

I 43
int
E 43
I 8
findname(idesc)
	struct inodesc *idesc;
{
D 21
	register DIRECT *dirp = idesc->id_dirp;
E 21
I 21
	register struct direct *dirp = idesc->id_dirp;
E 21

	if (dirp->d_ino != idesc->id_parent)
		return (KEEPON);
D 21
	bcopy(dirp->d_name, idesc->id_name, dirp->d_namlen + 1);
E 21
I 21
D 27
	bcopy(dirp->d_name, idesc->id_name, (int)dirp->d_namlen + 1);
E 27
I 27
D 44
	bcopy(dirp->d_name, idesc->id_name, (size_t)dirp->d_namlen + 1);
E 44
I 44
	memmove(idesc->id_name, dirp->d_name, (size_t)dirp->d_namlen + 1);
E 44
E 27
E 21
D 14
	return (STOP);
E 14
I 14
	return (STOP|FOUND);
E 14
}

I 43
int
E 43
E 8
findino(idesc)
	struct inodesc *idesc;
{
D 21
	register DIRECT *dirp = idesc->id_dirp;
E 21
I 21
	register struct direct *dirp = idesc->id_dirp;
E 21

	if (dirp->d_ino == 0)
		return (KEEPON);
D 2
	if (!strcmp(dirp->d_name, srchname)) {
E 2
I 2
D 8
	if (!strcmp(dirp->d_name, idesc->id_name)) {
E 2
		if (dirp->d_ino >= ROOTINO && dirp->d_ino <= imax)
			idesc->id_parent = dirp->d_ino;
E 8
I 8
	if (strcmp(dirp->d_name, idesc->id_name) == 0 &&
D 21
	    dirp->d_ino >= ROOTINO && dirp->d_ino <= imax) {
E 21
I 21
	    dirp->d_ino >= ROOTINO && dirp->d_ino <= maxino) {
E 21
		idesc->id_parent = dirp->d_ino;
E 8
D 14
		return (STOP);
E 14
I 14
		return (STOP|FOUND);
E 14
	}
	return (KEEPON);
}

I 43
void
E 43
pinode(ino)
	ino_t ino;
{
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
E 21
	register char *p;
D 10
	char uidbuf[BUFSIZ];
E 10
I 10
	struct passwd *pw;
E 10
	char *ctime();

D 27
	printf(" I=%u ", ino);
E 27
I 27
	printf(" I=%lu ", ino);
E 27
D 4
	if ((dp = ginode(ino)) == NULL)
E 4
I 4
D 21
	if (ino < ROOTINO || ino > imax)
E 21
I 21
	if (ino < ROOTINO || ino > maxino)
E 21
E 4
		return;
I 4
	dp = ginode(ino);
E 4
	printf(" OWNER=");
D 10
	if (getpw((int)dp->di_uid, uidbuf) == 0) {
		for (p = uidbuf; *p != ':'; p++);
		*p = 0;
		printf("%s ", uidbuf);
	}
	else {
E 10
I 10
	if ((pw = getpwuid((int)dp->di_uid)) != 0)
		printf("%s ", pw->pw_name);
	else
E 10
D 27
		printf("%d ", dp->di_uid);
E 27
I 27
		printf("%u ", (unsigned)dp->di_uid);
E 27
D 10
	}
E 10
	printf("MODE=%o\n", dp->di_mode);
	if (preen)
D 36
		printf("%s: ", devname);
E 36
I 36
		printf("%s: ", cdevname);
E 36
D 27
	printf("SIZE=%ld ", dp->di_size);
E 27
I 27
D 32
	printf("SIZE=%lu ", dp->di_size);
E 27
	p = ctime(&dp->di_mtime);
E 32
I 32
	printf("SIZE=%qu ", dp->di_size);
D 34
	p = ctime(&dp->di_mtime.tv_sec);
E 34
I 34
D 42
	p = ctime(&dp->di_mtime.ts_sec);
E 42
I 42
	p = ctime(&dp->di_mtime);
E 42
E 34
E 32
D 21
	printf("MTIME=%12.12s %4.4s ", p+4, p+20);
E 21
I 21
D 29
	printf("MTIME=%12.12s %4.4s ", p + 4, p + 20);
E 29
I 29
	printf("MTIME=%12.12s %4.4s ", &p[4], &p[20]);
E 29
E 21
}

I 43
void
E 43
D 21
blkerr(ino, s, blk)
E 21
I 21
blkerror(ino, type, blk)
E 21
	ino_t ino;
D 21
	char *s;
E 21
I 21
	char *type;
E 21
D 42
	daddr_t blk;
E 42
I 42
	ufs_daddr_t blk;
E 42
{

D 21
	pfatal("%ld %s I=%u", blk, s, ino);
E 21
I 21
D 27
	pfatal("%ld %s I=%u", blk, type, ino);
E 27
I 27
	pfatal("%ld %s I=%lu", blk, type, ino);
E 27
E 21
	printf("\n");
D 3
	statemap[ino] = CLEAR;
E 3
I 3
	switch (statemap[ino]) {

	case FSTATE:
		statemap[ino] = FCLEAR;
		return;

	case DSTATE:
		statemap[ino] = DCLEAR;
		return;

	case FCLEAR:
	case DCLEAR:
		return;

	default:
D 43
		errexit("BAD STATE %d TO BLKERR", statemap[ino]);
E 43
I 43
		errx(EEXIT, "BAD STATE %d TO BLKERR", statemap[ino]);
E 43
		/* NOTREACHED */
	}
E 3
}
I 6

/*
 * allocate an unused inode
 */
ino_t
allocino(request, type)
	ino_t request;
	int type;
{
	register ino_t ino;
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
E 21

	if (request == 0)
		request = ROOTINO;
	else if (statemap[request] != USTATE)
		return (0);
D 21
	for (ino = request; ino < imax; ino++)
E 21
I 21
	for (ino = request; ino < maxino; ino++)
E 21
		if (statemap[ino] == USTATE)
			break;
D 21
	if (ino == imax)
E 21
I 21
	if (ino == maxino)
E 21
		return (0);
	switch (type & IFMT) {
	case IFDIR:
		statemap[ino] = DSTATE;
		break;
	case IFREG:
	case IFLNK:
		statemap[ino] = FSTATE;
		break;
	default:
		return (0);
	}
	dp = ginode(ino);
D 21
	dp->di_db[0] = allocblk(1);
E 21
I 21
	dp->di_db[0] = allocblk((long)1);
E 21
	if (dp->di_db[0] == 0) {
		statemap[ino] = USTATE;
		return (0);
	}
	dp->di_mode = type;
D 27
	time(&dp->di_atime);
E 27
I 27
D 32
	(void)time(&dp->di_atime);
E 32
I 32
D 34
	(void)time(&dp->di_atime.tv_sec);
E 34
I 34
D 42
	(void)time(&dp->di_atime.ts_sec);
E 42
I 42
	(void)time(&dp->di_atime);
E 42
E 34
E 32
E 27
	dp->di_mtime = dp->di_ctime = dp->di_atime;
	dp->di_size = sblock.fs_fsize;
	dp->di_blocks = btodb(sblock.fs_fsize);
	n_files++;
	inodirty();
I 39
	if (newinofmt)
		typemap[ino] = IFTODT(type);
E 39
	return (ino);
}

/*
 * deallocate an inode
 */
I 43
void
E 43
freeino(ino)
	ino_t ino;
{
	struct inodesc idesc;
D 43
	extern int pass4check();
E 43
D 21
	DINODE *dp;
E 21
I 21
	struct dinode *dp;
E 21

D 44
	bzero((char *)&idesc, sizeof(struct inodesc));
E 44
I 44
	memset(&idesc, 0, sizeof(struct inodesc));
E 44
	idesc.id_type = ADDR;
	idesc.id_func = pass4check;
	idesc.id_number = ino;
	dp = ginode(ino);
	(void)ckinode(dp, &idesc);
D 21
	zapino(dp);
E 21
I 21
	clearinode(dp);
E 21
	inodirty();
	statemap[ino] = USTATE;
	n_files--;
}
E 6
E 1
