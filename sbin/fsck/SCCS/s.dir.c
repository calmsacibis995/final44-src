h45348
s 00013/00013/00686
d D 8.8 95/04/28 10:38:05 bostic 44 43
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00031/00007/00668
d D 8.7 95/04/27 11:33:04 mckusick 43 42
c add function prototypes
e
s 00002/00002/00673
d D 8.6 95/03/21 00:10:48 mckusick 42 41
c daddr_t => ufs_daddr_t
e
s 00019/00018/00656
d D 8.5 94/12/08 22:30:40 mckusick 41 40
c dircheck() shouldn't be looking at d_type or d_namlen in blank entries
c (from mycroft)
e
s 00020/00012/00654
d D 8.4 94/12/08 18:03:21 mckusick 40 39
c correct fix for LITTLE_ENDIAN in mkentry() (idea from mycroft)
e
s 00004/00000/00662
d D 8.3 94/10/27 15:40:31 mckusick 39 38
c do not recursively try to fix corrupted directories (from mycroft)
e
s 00012/00005/00650
d D 8.2 94/08/04 18:02:03 mckusick 38 37
c fix for little-endian machines (from mycroft)
e
s 00002/00002/00653
d D 8.1 93/06/05 10:56:12 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00653
d D 5.24 93/04/26 19:27:17 mckusick 36 35
c salvage the correct part of the directory
e
s 00004/00000/00651
d D 5.23 92/07/12 18:22:46 mckusick 35 34
c always have to initialize d_type
e
s 00065/00014/00586
d D 5.22 92/07/02 16:43:04 mckusick 34 33
c tricky code to convert old style directories to new style
e
s 00001/00000/00599
d D 5.21 92/05/27 22:42:07 mckusick 33 32
c add <sys/time.h> for dinode.h
e
s 00003/00003/00596
d D 5.20 91/11/04 22:20:26 bostic 32 31
c break FFS into UFS/FFS/LFS
e
s 00002/00000/00597
d D 5.19 91/07/26 16:30:00 mckusick 31 30
c have to make cache entries for new directory inodes
e
s 00010/00008/00587
d D 5.18 90/07/20 16:51:37 mckusick 30 29
c lint (from Torek)
e
s 00001/00011/00594
d D 5.17 90/06/01 16:16:21 bostic 29 28
c new copyright notice
e
s 00001/00001/00604
d D 5.16 90/04/29 12:36:46 mckusick 28 27
c do not expand in degenerate cases
e
s 00001/00001/00604
d D 5.15 90/03/27 18:09:29 mckusick 27 26
c do not mark dirs with eighth bit set as corrupt;
c do mark directories with names containing '/' as corrupt
e
s 00004/00005/00601
d D 5.14 90/03/27 18:05:08 mckusick 26 25
c initialize directory buffer pointer for each run
e
s 00012/00005/00594
d D 5.13 90/03/22 18:35:39 mckusick 25 24
c have to reset definition of direct pointer after printing message
e
s 00073/00083/00526
d D 5.12 90/02/07 00:15:54 mckusick 24 23
c add propogate to find directory connectivity;
c descend is gone, mostly moved into pass2;
c add fileerror similar to direrror, but giving current directory;
c pathnames are now calculated when needed rather than continuously maintained;
c add function changeino to change the inode number of an entry
e
s 00009/00003/00600
d D 5.11 90/02/01 23:36:18 mckusick 23 22
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00015/00004/00588
d D 5.10 90/02/01 17:17:36 mckusick 22 21
c convert to BSD only copyright
e
s 00054/00052/00538
d D 5.9 90/02/01 16:17:55 mckusick 21 20
c lint and other aesthetic cleanups
e
s 00001/00003/00589
d D 5.8 89/10/24 19:05:37 mckusick 20 19
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00004/00588
d D 5.7 89/06/30 16:50:14 mckusick 19 18
c ansi C changes from Torek
e
s 00005/00003/00587
d D 5.6 89/06/26 21:41:39 mckusick 18 17
c new include file locations engendered by vnodes
e
s 00006/00004/00584
d D 5.5 89/02/17 17:02:34 mckusick 17 16
c add -m flag to override default creation mode for lost+found
e
s 00051/00029/00537
d D 5.4 88/05/07 01:04:12 mckusick 16 15
c expand from three static buffer to a dynamic buffer pool;
c initial sizing of the buffer pool is 128K (For 8K fs == 16 buffers)
e
s 00009/00013/00557
d D 5.3 87/01/07 19:26:38 mckusick 15 14
c be more persistent in trying to read directories; 
c add FOUND return status for routines called from dirscan
e
s 00001/00001/00569
d D 5.2 86/11/24 20:54:40 mckusick 14 13
c get the right name
e
s 00008/00002/00562
d D 5.1 85/06/05 08:54:24 dist 13 12
c Add copyright
e
s 00026/00010/00538
d D 3.11 85/05/31 19:06:21 mckusick 12 10
c check for improper directory offsets; recover gracefully from read errors
e
s 00023/00008/00540
d R 3.11 85/05/31 00:19:14 mckusick 11 10
c check for improper directory offsets; recover gracefully from read errors
e
s 00007/00004/00541
d D 3.10 85/02/15 15:22:53 mckusick 10 9
c insure that entire directory block is checked;
c when making entries, upsize directory as needed
e
s 00024/00019/00521
d D 3.9 85/02/15 12:42:27 mckusick 9 8
c restructure function of makeentry()
e
s 00000/00006/00540
d D 3.8 85/02/15 12:06:40 mckusick 8 7
c filesize now set by ckinode(); pass1() uses id_entryno to calc block count
e
s 00037/00011/00509
d D 3.7 85/02/13 19:07:30 mckusick 7 6
c reallocate lost+found if it is not a directory
e
s 00092/00006/00428
d D 3.6 85/02/13 18:22:33 mckusick 6 5
c create lost+found directory if none already in existence
e
s 00071/00003/00363
d D 3.5 85/02/11 20:55:26 mckusick 5 4
c expand lost+found when running out of space
e
s 00020/00017/00346
d D 3.4 85/02/11 18:29:08 mckusick 4 3
c ginode() succeeds or exits
e
s 00006/00005/00357
d D 3.3 85/02/08 19:14:55 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00009/00009/00353
d D 3.2 85/02/07 17:51:26 mckusick 2 1
c code reorganization and cleanup
e
s 00362/00000/00000
d D 3.1 84/03/31 21:03:39 mckusick 1 0
c date and time created 84/03/31 21:03:39 by mckusick
e
u
U
t
T
I 13
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
D 29
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
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 22
 */

E 13
I 1
#ifndef lint
D 13
static char version[] = "%W% (Berkeley) %G%";
#endif
E 13
I 13
static char sccsid[] = "%W% (Berkeley) %G%";
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22
E 13

#include <sys/param.h>
I 33
#include <sys/time.h>
I 43

E 43
E 33
D 18
#include <sys/inode.h>
#include <sys/fs.h>
E 18
I 18
D 20
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 20
I 20
D 32
#include <ufs/dinode.h>
E 20
#include <ufs/fs.h>
E 32
I 32
#include <ufs/ufs/dinode.h>
E 32
E 18
D 34
#define KERNEL
E 34
D 18
#include <sys/dir.h>
E 18
I 18
D 32
#include <ufs/dir.h>
E 32
I 32
#include <ufs/ufs/dir.h>
E 32
E 18
D 34
#undef KERNEL
E 34
I 32
#include <ufs/ffs/fs.h>
E 32
I 30
D 43
#include <stdlib.h>
E 43
I 43

#include <err.h>
E 43
#include <string.h>
I 43

E 43
E 30
#include "fsck.h"

D 24
#define MINDIRSIZE	(sizeof (struct dirtemplate))

char	*endpathname = &pathname[BUFSIZ - 2];
E 24
char	*lfname = "lost+found";
I 17
int	lfmode = 01777;
E 17
I 5
struct	dirtemplate emptydir = { 0, DIRBLKSIZ };
I 6
D 34
struct	dirtemplate dirhead = { 0, 12, 1, ".", 0, DIRBLKSIZ - 12, 2, ".." };
E 34
I 34
struct	dirtemplate dirhead = {
	0, 12, DT_DIR, 1, ".",
	0, DIRBLKSIZ - 12, DT_DIR, 2, ".."
};
struct	odirtemplate odirhead = {
	0, 12, 1, ".",
	0, DIRBLKSIZ - 12, 2, ".."
};
E 34
E 6
E 5

D 21
DIRECT	*fsck_readdir();
I 16
BUFAREA	*getdirblk();
E 21
I 21
D 43
struct direct	*fsck_readdir();
struct bufarea	*getdirblk();
E 43
I 43
static int chgino __P((struct inodesc *));
static int dircheck __P((struct inodesc *, struct direct *));
static int expanddir __P((struct dinode *dp, char *name));
static void freedir __P((ino_t ino, ino_t parent));
static struct direct *fsck_readdir __P((struct inodesc *));
static struct bufarea *getdirblk __P((ufs_daddr_t blkno, long size));
static int lftempname __P((char *bufp, ino_t ino));
static int mkentry __P((struct inodesc *));
E 43
E 21
E 16

D 24
descend(parentino, inumber)
	struct inodesc *parentino;
	ino_t inumber;
E 24
I 24
/*
 * Propagate connected state through the tree.
 */
I 43
void
E 43
propagate()
E 24
{
D 21
	register DINODE *dp;
E 21
I 21
D 24
	register struct dinode *dp;
E 21
	struct inodesc curino;
E 24
I 24
	register struct inoinfo **inpp, *inp;
	struct inoinfo **inpend;
	long change;
E 24

D 24
	bzero((char *)&curino, sizeof(struct inodesc));
D 3
	statemap[inumber] = FSTATE;
E 3
I 3
	if (statemap[inumber] != DSTATE)
		errexit("BAD INODE %d TO DESCEND", statemap[inumber]);
	statemap[inumber] = DFOUND;
E 3
D 4
	if ((dp = ginode(inumber)) == NULL)
		return;
E 4
I 4
D 23
	dp = ginode(inumber);
E 23
I 23
	dp = getcacheino(inumber);
E 23
E 4
	if (dp->di_size == 0) {
D 21
		direrr(inumber, "ZERO LENGTH DIRECTORY");
E 21
I 21
		direrror(inumber, "ZERO LENGTH DIRECTORY");
E 21
		if (reply("REMOVE") == 1)
D 3
			statemap[inumber] = CLEAR;
E 3
I 3
			statemap[inumber] = DCLEAR;
E 3
		return;
	}
	if (dp->di_size < MINDIRSIZE) {
D 21
		direrr(inumber, "DIRECTORY TOO SHORT");
E 21
I 21
		direrror(inumber, "DIRECTORY TOO SHORT");
E 21
		dp->di_size = MINDIRSIZE;
D 23
		if (reply("FIX") == 1)
E 23
I 23
		if (reply("FIX") == 1) {
			dp = ginode(inumber);
			dp->di_size = MINDIRSIZE;
E 23
			inodirty();
E 24
I 24
	inpend = &inpsort[inplast];
	do {
		change = 0;
		for (inpp = inpsort; inpp < inpend; inpp++) {
			inp = *inpp;
			if (inp->i_parent == 0)
				continue;
			if (statemap[inp->i_parent] == DFOUND &&
			    statemap[inp->i_number] == DSTATE) {
				statemap[inp->i_number] = DFOUND;
				change++;
			}
E 24
I 23
		}
E 23
D 24
	}
I 12
	if ((dp->di_size & (DIRBLKSIZ - 1)) != 0) {
		pwarn("DIRECTORY %s: LENGTH %d NOT MULTIPLE OF %d",
			pathname, dp->di_size, DIRBLKSIZ);
		dp->di_size = roundup(dp->di_size, DIRBLKSIZ);
		if (preen)
			printf(" (ADJUSTED)\n");
D 23
		if (preen || reply("ADJUST") == 1)
E 23
I 23
		if (preen || reply("ADJUST") == 1) {
			dp = ginode(inumber);
			dp->di_size = roundup(dp->di_size, DIRBLKSIZ);
E 23
			inodirty();
I 23
		}
E 23
	}
E 12
	curino.id_type = DATA;
	curino.id_func = parentino->id_func;
	curino.id_parent = parentino->id_number;
	curino.id_number = inumber;
D 8
	curino.id_filesize = dp->di_size;
E 8
	(void)ckinode(dp, &curino);
I 15
	if (curino.id_entryno < 2) {
D 21
		direrr(inumber, "NULL DIRECTORY");
E 21
I 21
		direrror(inumber, "NULL DIRECTORY");
E 21
		if (reply("REMOVE") == 1)
			statemap[inumber] = DCLEAR;
	}
E 24
I 24
	} while (change > 0);
E 24
E 15
}

I 24
/*
 * Scan each entry in a directory block.
 */
I 43
int
E 43
E 24
dirscan(idesc)
	register struct inodesc *idesc;
{
D 21
	register DIRECT *dp;
I 16
	register BUFAREA *bp;
E 21
I 21
	register struct direct *dp;
	register struct bufarea *bp;
E 21
E 16
	int dsize, n;
	long blksiz;
	char dbuf[DIRBLKSIZ];

	if (idesc->id_type != DATA)
D 43
		errexit("wrong type to dirscan %d\n", idesc->id_type);
E 43
I 43
		errx(EEXIT, "wrong type to dirscan %d", idesc->id_type);
E 43
I 10
	if (idesc->id_entryno == 0 &&
	    (idesc->id_filesize & (DIRBLKSIZ - 1)) != 0)
		idesc->id_filesize = roundup(idesc->id_filesize, DIRBLKSIZ);
E 10
	blksiz = idesc->id_numfrags * sblock.fs_fsize;
D 21
	if (outrange(idesc->id_blkno, idesc->id_numfrags)) {
E 21
I 21
	if (chkrange(idesc->id_blkno, idesc->id_numfrags)) {
E 21
		idesc->id_filesize -= blksiz;
		return (SKIP);
	}
	idesc->id_loc = 0;
	for (dp = fsck_readdir(idesc); dp != NULL; dp = fsck_readdir(idesc)) {
		dsize = dp->d_reclen;
D 30
		bcopy((char *)dp, dbuf, dsize);
E 30
I 30
D 44
		bcopy((char *)dp, dbuf, (size_t)dsize);
E 44
I 44
		memmove(dbuf, dp, (size_t)dsize);
E 44
I 34
#		if (BYTE_ORDER == LITTLE_ENDIAN)
			if (!newinofmt) {
				struct direct *tdp = (struct direct *)dbuf;
				u_char tmp;

				tmp = tdp->d_namlen;
				tdp->d_namlen = tdp->d_type;
				tdp->d_type = tmp;
			}
#		endif
E 34
E 30
D 21
		idesc->id_dirp = (DIRECT *)dbuf;
E 21
I 21
		idesc->id_dirp = (struct direct *)dbuf;
E 21
		if ((n = (*idesc->id_func)(idesc)) & ALTERED) {
I 34
#			if (BYTE_ORDER == LITTLE_ENDIAN)
				if (!newinofmt && !doinglevel2) {
					struct direct *tdp;
					u_char tmp;

					tdp = (struct direct *)dbuf;
					tmp = tdp->d_namlen;
					tdp->d_namlen = tdp->d_type;
					tdp->d_type = tmp;
				}
#			endif
E 34
D 12
			if (getblk(&fileblk, idesc->id_blkno, blksiz) != NULL) {
E 12
I 12
D 16
			getblk(&fileblk, idesc->id_blkno, blksiz);
E 16
I 16
			bp = getdirblk(idesc->id_blkno, blksiz);
E 16
D 15
			if (fileblk.b_errs != NULL) {
				n &= ~ALTERED;
			} else {
E 12
				bcopy(dbuf, (char *)dp, dsize);
				dirty(&fileblk);
				sbdirty();
D 12
			} else
				n &= ~ALTERED;
E 12
I 12
			}
E 15
I 15
D 25
			bcopy(dbuf, (char *)dp, dsize);
E 25
I 25
D 44
			bcopy(dbuf, bp->b_un.b_buf + idesc->id_loc - dsize,
E 44
I 44
			memmove(bp->b_un.b_buf + idesc->id_loc - dsize, dbuf,
E 44
D 30
			    dsize);
E 30
I 30
			    (size_t)dsize);
E 30
E 25
D 16
			dirty(&fileblk);
E 16
I 16
			dirty(bp);
E 16
			sbdirty();
E 15
E 12
		}
		if (n & STOP) 
			return (n);
	}
	return (idesc->id_filesize > 0 ? KEEPON : STOP);
}

/*
 * get next entry in a directory.
 */
D 21
DIRECT *
E 21
I 21
D 43
struct direct *
E 43
I 43
static struct direct *
E 43
E 21
fsck_readdir(idesc)
	register struct inodesc *idesc;
{
D 21
	register DIRECT *dp, *ndp;
I 16
	register BUFAREA *bp;
E 21
I 21
	register struct direct *dp, *ndp;
	register struct bufarea *bp;
E 21
E 16
D 25
	long size, blksiz;
E 25
I 25
D 34
	long size, blksiz, fix;
E 34
I 34
	long size, blksiz, fix, dploc;
E 34
E 25

	blksiz = idesc->id_numfrags * sblock.fs_fsize;
D 12
	if (getblk(&fileblk, idesc->id_blkno, blksiz) == NULL) {
E 12
I 12
D 16
	getblk(&fileblk, idesc->id_blkno, blksiz);
E 16
I 16
	bp = getdirblk(idesc->id_blkno, blksiz);
E 16
D 15
	if (fileblk.b_errs != NULL) {
E 12
		idesc->id_filesize -= blksiz - idesc->id_loc;
		return NULL;
	}
E 15
	if (idesc->id_loc % DIRBLKSIZ == 0 && idesc->id_filesize > 0 &&
	    idesc->id_loc < blksiz) {
D 16
		dp = (DIRECT *)(dirblk.b_buf + idesc->id_loc);
E 16
I 16
D 21
		dp = (DIRECT *)(bp->b_un.b_buf + idesc->id_loc);
E 21
I 21
		dp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
E 21
E 16
		if (dircheck(idesc, dp))
			goto dpok;
I 39
		if (idesc->id_fix == IGNORE)
			return (0);
E 39
D 36
		idesc->id_loc += DIRBLKSIZ;
		idesc->id_filesize -= DIRBLKSIZ;
E 36
I 25
		fix = dofix(idesc, "DIRECTORY CORRUPTED");
		bp = getdirblk(idesc->id_blkno, blksiz);
		dp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
E 25
		dp->d_reclen = DIRBLKSIZ;
		dp->d_ino = 0;
I 34
		dp->d_type = 0;
E 34
		dp->d_namlen = 0;
		dp->d_name[0] = '\0';
D 2
		if (dofix(idesc))
E 2
I 2
D 25
		if (dofix(idesc, "DIRECTORY CORRUPTED"))
E 25
I 25
		if (fix)
E 25
E 2
D 16
			dirty(&fileblk);
E 16
I 16
			dirty(bp);
I 36
		idesc->id_loc += DIRBLKSIZ;
		idesc->id_filesize -= DIRBLKSIZ;
E 36
E 16
		return (dp);
	}
dpok:
	if (idesc->id_filesize <= 0 || idesc->id_loc >= blksiz)
		return NULL;
D 16
	dp = (DIRECT *)(dirblk.b_buf + idesc->id_loc);
E 16
I 16
D 21
	dp = (DIRECT *)(bp->b_un.b_buf + idesc->id_loc);
E 21
I 21
D 34
	dp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
E 34
I 34
	dploc = idesc->id_loc;
	dp = (struct direct *)(bp->b_un.b_buf + dploc);
E 34
E 21
E 16
	idesc->id_loc += dp->d_reclen;
	idesc->id_filesize -= dp->d_reclen;
	if ((idesc->id_loc % DIRBLKSIZ) == 0)
		return (dp);
D 16
	ndp = (DIRECT *)(dirblk.b_buf + idesc->id_loc);
E 16
I 16
D 21
	ndp = (DIRECT *)(bp->b_un.b_buf + idesc->id_loc);
E 21
I 21
	ndp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
E 21
E 16
	if (idesc->id_loc < blksiz && idesc->id_filesize > 0 &&
	    dircheck(idesc, ndp) == 0) {
		size = DIRBLKSIZ - (idesc->id_loc % DIRBLKSIZ);
D 25
		dp->d_reclen += size;
E 25
		idesc->id_loc += size;
		idesc->id_filesize -= size;
I 39
		if (idesc->id_fix == IGNORE)
			return (0);
E 39
D 2
		if (dofix(idesc))
E 2
I 2
D 25
		if (dofix(idesc, "DIRECTORY CORRUPTED"))
E 25
I 25
		fix = dofix(idesc, "DIRECTORY CORRUPTED");
		bp = getdirblk(idesc->id_blkno, blksiz);
D 34
		dp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
E 34
I 34
		dp = (struct direct *)(bp->b_un.b_buf + dploc);
E 34
		dp->d_reclen += size;
		if (fix)
E 25
E 2
D 16
			dirty(&fileblk);
E 16
I 16
			dirty(bp);
E 16
	}
	return (dp);
}

/*
 * Verify that a directory entry is valid.
 * This is a superset of the checks made in the kernel.
 */
I 43
static int
E 43
dircheck(idesc, dp)
	struct inodesc *idesc;
D 21
	register DIRECT *dp;
E 21
I 21
	register struct direct *dp;
E 21
{
	register int size;
	register char *cp;
I 34
	u_char namlen, type;
E 34
	int spaceleft;

D 34
	size = DIRSIZ(dp);
E 34
I 34
D 41
	size = DIRSIZ(!newinofmt, dp);
E 41
E 34
	spaceleft = DIRBLKSIZ - (idesc->id_loc % DIRBLKSIZ);
I 41
	if (dp->d_ino >= maxino ||
	    dp->d_reclen == 0 ||
	    dp->d_reclen > spaceleft ||
	    (dp->d_reclen & 0x3) != 0)
		return (0);
	if (dp->d_ino == 0)
		return (1);
	size = DIRSIZ(!newinofmt, dp);
E 41
I 34
#	if (BYTE_ORDER == LITTLE_ENDIAN)
		if (!newinofmt) {
			type = dp->d_namlen;
			namlen = dp->d_type;
		} else {
			namlen = dp->d_namlen;
			type = dp->d_type;
		}
#	else
		namlen = dp->d_namlen;
		type = dp->d_type;
#	endif
E 34
D 21
	if (dp->d_ino < imax &&
E 21
I 21
D 41
	if (dp->d_ino < maxino &&
E 21
	    dp->d_reclen != 0 &&
	    dp->d_reclen <= spaceleft &&
	    (dp->d_reclen & 0x3) == 0 &&
	    dp->d_reclen >= size &&
	    idesc->id_filesize >= size &&
D 34
	    dp->d_namlen <= MAXNAMLEN) {
E 34
I 34
	    namlen <= MAXNAMLEN &&
	    type <= 15) {
E 34
		if (dp->d_ino == 0)
			return (1);
D 34
		for (cp = dp->d_name, size = 0; size < dp->d_namlen; size++)
E 34
I 34
		for (cp = dp->d_name, size = 0; size < namlen; size++)
E 34
D 27
			if (*cp == 0 || (*cp++ & 0200))
E 27
I 27
			if (*cp == 0 || (*cp++ == '/'))
E 27
				return (0);
		if (*cp == 0)
			return (1);
	}
	return (0);
E 41
I 41
	if (dp->d_reclen < size ||
	    idesc->id_filesize < size ||
	    namlen > MAXNAMLEN ||
	    type > 15)
		return (0);
	for (cp = dp->d_name, size = 0; size < namlen; size++)
		if (*cp == '\0' || (*cp++ == '/'))
			return (0);
	if (*cp != '\0')
		return (0);
	return (1);
E 41
}

I 43
void
E 43
D 21
direrr(ino, s)
E 21
I 21
direrror(ino, errmesg)
E 21
	ino_t ino;
D 21
	char *s;
E 21
I 21
	char *errmesg;
E 21
{
I 24

	fileerror(ino, ino, errmesg);
}

I 43
void
E 43
fileerror(cwd, ino, errmesg)
	ino_t cwd, ino;
	char *errmesg;
{
E 24
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
I 24
	char pathbuf[MAXPATHLEN + 1];
E 24
E 21

D 21
	pwarn("%s ", s);
E 21
I 21
	pwarn("%s ", errmesg);
E 21
	pinode(ino);
	printf("\n");
I 24
	getpathname(pathbuf, cwd, ino);
E 24
D 4
	if ((dp = ginode(ino)) != NULL && ftypeok(dp))
E 4
I 4
D 21
	if (ino < ROOTINO || ino > imax) {
E 21
I 21
	if (ino < ROOTINO || ino > maxino) {
E 21
D 24
		pfatal("NAME=%s\n", pathname);
E 24
I 24
		pfatal("NAME=%s\n", pathbuf);
E 24
		return;
	}
	dp = ginode(ino);
	if (ftypeok(dp))
E 4
D 2
		pfatal("%s=%s\n", DIRCT?"DIR":"FILE", pathname);
E 2
I 2
D 21
		pfatal("%s=%s\n", DIRCT(dp) ? "DIR" : "FILE", pathname);
E 21
I 21
		pfatal("%s=%s\n",
D 24
		    (dp->di_mode & IFMT) == IFDIR ? "DIR" : "FILE", pathname);
E 24
I 24
		    (dp->di_mode & IFMT) == IFDIR ? "DIR" : "FILE", pathbuf);
E 24
E 21
E 2
	else
D 24
		pfatal("NAME=%s\n", pathname);
E 24
I 24
		pfatal("NAME=%s\n", pathbuf);
E 24
}

I 43
void
E 43
adjust(idesc, lcnt)
	register struct inodesc *idesc;
D 43
	short lcnt;
E 43
I 43
	int lcnt;
E 43
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
	if (dp->di_nlink == lcnt) {
		if (linkup(idesc->id_number, (ino_t)0) == 0)
			clri(idesc, "UNREF", 0);
D 3
	}
	else {
E 3
I 3
	} else {
E 3
D 2
		pwarn("LINK COUNT %s",
			(lfdir==idesc->id_number)?lfname:(DIRCT?"DIR":"FILE"));
E 2
I 2
		pwarn("LINK COUNT %s", (lfdir == idesc->id_number) ? lfname :
D 21
			(DIRCT(dp) ? "DIR" : "FILE"));
E 21
I 21
			((dp->di_mode & IFMT) == IFDIR ? "DIR" : "FILE"));
E 21
E 2
		pinode(idesc->id_number);
		printf(" COUNT %d SHOULD BE %d",
D 21
			dp->di_nlink, dp->di_nlink-lcnt);
E 21
I 21
			dp->di_nlink, dp->di_nlink - lcnt);
E 21
		if (preen) {
			if (lcnt < 0) {
				printf("\n");
D 2
				preendie();
E 2
I 2
				pfatal("LINK COUNT INCREASING");
E 2
			}
			printf(" (ADJUSTED)\n");
		}
		if (preen || reply("ADJUST") == 1) {
			dp->di_nlink -= lcnt;
			inodirty();
		}
	}
}

I 43
static int
E 43
mkentry(idesc)
	struct inodesc *idesc;
{
D 21
	register DIRECT *dirp = idesc->id_dirp;
	DIRECT newent;
E 21
I 21
	register struct direct *dirp = idesc->id_dirp;
	struct direct newent;
E 21
	int newlen, oldlen;

D 24
	newent.d_namlen = 11;
E 24
I 24
	newent.d_namlen = strlen(idesc->id_name);
E 24
D 34
	newlen = DIRSIZ(&newent);
E 34
I 34
	newlen = DIRSIZ(0, &newent);
E 34
	if (dirp->d_ino != 0)
D 34
		oldlen = DIRSIZ(dirp);
E 34
I 34
		oldlen = DIRSIZ(0, dirp);
E 34
	else
		oldlen = 0;
	if (dirp->d_reclen - oldlen < newlen)
		return (KEEPON);
	newent.d_reclen = dirp->d_reclen - oldlen;
	dirp->d_reclen = oldlen;
	dirp = (struct direct *)(((char *)dirp) + oldlen);
	dirp->d_ino = idesc->id_parent;	/* ino to be entered is in id_parent */
I 34
D 38
	if (newinofmt)
E 38
I 38
D 40
	if (newinofmt) {
E 38
		dirp->d_type = typemap[idesc->id_parent];
I 35
D 38
	else
		dirp->d_type = 0;
E 38
I 38
		dirp->d_namlen = newent.d_namlen;
	} else {
#		if (BYTE_ORDER == LITTLE_ENDIAN)
			dirp->d_type = newent.d_namlen;
			dirp->d_namlen = 0;
#		else
			dirp->d_type = 0;
			dirp->d_namlen = newent.d_namlen;
#		endif
	}
E 40
E 38
E 35
E 34
	dirp->d_reclen = newent.d_reclen;
I 40
	if (newinofmt)
		dirp->d_type = typemap[idesc->id_parent];
	else
		dirp->d_type = 0;
	dirp->d_namlen = newent.d_namlen;
E 40
D 6
	dirp->d_namlen = lftempname(dirp->d_name, idesc->id_parent);
E 6
I 6
D 24
	dirp->d_namlen = strlen(idesc->id_name);
E 24
I 24
D 38
	dirp->d_namlen = newent.d_namlen;
E 24
D 21
	bcopy(idesc->id_name, dirp->d_name, dirp->d_namlen + 1);
E 21
I 21
D 30
	bcopy(idesc->id_name, dirp->d_name, (int)dirp->d_namlen + 1);
E 30
I 30
	bcopy(idesc->id_name, dirp->d_name, (size_t)dirp->d_namlen + 1);
E 38
I 38
D 44
	bcopy(idesc->id_name, dirp->d_name, (size_t)newent.d_namlen + 1);
E 44
I 44
	memmove(dirp->d_name, idesc->id_name, (size_t)newent.d_namlen + 1);
E 44
I 40
#	if (BYTE_ORDER == LITTLE_ENDIAN)
		/*
		 * If the entry was split, dirscan() will only reverse the byte
		 * order of the original entry, and not the new one, before
		 * writing it back out.  So, we reverse the byte order here if
		 * necessary.
		 */
		if (oldlen != 0 && !newinofmt && !doinglevel2) {
			u_char tmp;

			tmp = dirp->d_namlen;
			dirp->d_namlen = dirp->d_type;
			dirp->d_type = tmp;
		}
#	endif
E 40
E 38
E 30
E 21
E 6
	return (ALTERED|STOP);
}

I 43
static int
E 43
D 7
chgdd(idesc)
E 7
I 7
chgino(idesc)
E 7
	struct inodesc *idesc;
{
D 21
	register DIRECT *dirp = idesc->id_dirp;
E 21
I 21
	register struct direct *dirp = idesc->id_dirp;
E 21

D 7
	if (dirp->d_name[0] == '.' && dirp->d_name[1] == '.' &&
	dirp->d_name[2] == 0) {
		dirp->d_ino = lfdir;
		return (ALTERED|STOP);
	}
	return (KEEPON);
E 7
I 7
D 21
	if (bcmp(dirp->d_name, idesc->id_name, dirp->d_namlen + 1))
E 21
I 21
D 44
	if (bcmp(dirp->d_name, idesc->id_name, (int)dirp->d_namlen + 1))
E 44
I 44
	if (memcmp(dirp->d_name, idesc->id_name, (int)dirp->d_namlen + 1))
E 44
E 21
		return (KEEPON);
D 21
	dirp->d_ino = idesc->id_parent;;
E 21
I 21
	dirp->d_ino = idesc->id_parent;
I 34
	if (newinofmt)
		dirp->d_type = typemap[idesc->id_parent];
I 35
	else
		dirp->d_type = 0;
E 35
E 34
E 21
	return (ALTERED|STOP);
E 7
}

I 43
int
E 43
D 21
linkup(orphan, pdir)
E 21
I 21
linkup(orphan, parentdir)
E 21
	ino_t orphan;
D 21
	ino_t pdir;
E 21
I 21
	ino_t parentdir;
E 21
{
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
E 21
D 24
	int lostdir, len;
E 24
I 24
	int lostdir;
E 24
I 6
	ino_t oldlfdir;
E 6
	struct inodesc idesc;
I 6
	char tempname[BUFSIZ];
I 7
	extern int pass4check();
E 7
E 6

D 44
	bzero((char *)&idesc, sizeof(struct inodesc));
E 44
I 44
	memset(&idesc, 0, sizeof(struct inodesc));
E 44
D 4
	if ((dp = ginode(orphan)) == NULL)
		return (0);
E 4
I 4
	dp = ginode(orphan);
E 4
D 2
	lostdir = DIRCT;
E 2
I 2
D 21
	lostdir = DIRCT(dp);
E 21
I 21
	lostdir = (dp->di_mode & IFMT) == IFDIR;
E 21
E 2
	pwarn("UNREF %s ", lostdir ? "DIR" : "FILE");
	pinode(orphan);
	if (preen && dp->di_size == 0)
		return (0);
	if (preen)
		printf(" (RECONNECTED)\n");
	else
		if (reply("RECONNECT") == 0)
			return (0);
D 24
	pathp = pathname;
	*pathp++ = '/';
	*pathp = '\0';
E 24
	if (lfdir == 0) {
D 4
		if ((dp = ginode(ROOTINO)) == NULL)
			return (0);
E 4
I 4
		dp = ginode(ROOTINO);
E 4
D 2
		srchname = lfname;
E 2
I 2
		idesc.id_name = lfname;
E 2
		idesc.id_type = DATA;
		idesc.id_func = findino;
		idesc.id_number = ROOTINO;
D 8
		idesc.id_filesize = dp->di_size;
E 8
D 15
		(void)ckinode(dp, &idesc);
D 4
		if ((lfdir = idesc.id_parent) == 0) {
E 4
I 4
D 6
		lfdir = idesc.id_parent;
		if (lfdir < ROOTINO || lfdir > imax)
			lfdir = 0;
E 6
I 6
		if (idesc.id_parent >= ROOTINO && idesc.id_parent < imax) {
E 15
I 15
		if ((ckinode(dp, &idesc) & FOUND) != 0) {
E 15
			lfdir = idesc.id_parent;
		} else {
			pwarn("NO lost+found DIRECTORY");
			if (preen || reply("CREATE")) {
D 9
				idesc.id_func = mkentry;
				idesc.id_parent = allocdir(ROOTINO, 0);
D 8
				idesc.id_filesize = dp->di_size;
E 8
				if (idesc.id_parent != 0) {
					if (makeentry(dp, &idesc) != 0) {
						lfdir = idesc.id_parent;
E 9
I 9
D 17
				lfdir = allocdir(ROOTINO, 0);
E 17
I 17
D 21
				lfdir = allocdir(ROOTINO, 0, lfmode);
E 21
I 21
				lfdir = allocdir(ROOTINO, (ino_t)0, lfmode);
E 21
E 17
				if (lfdir != 0) {
					if (makeentry(ROOTINO, lfdir, lfname) != 0) {
E 9
						if (preen)
							printf(" (CREATED)\n");
					} else {
D 9
						freedir(idesc.id_parent, ROOTINO);
E 9
I 9
						freedir(lfdir, ROOTINO);
						lfdir = 0;
E 9
						if (preen)
							printf("\n");
					}
				}
			}
		}
E 6
		if (lfdir == 0) {
E 4
D 6
			pfatal("SORRY. NO lost+found DIRECTORY");
E 6
I 6
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY");
E 6
			printf("\n\n");
			return (0);
		}
	}
D 4
	if ((dp = ginode(lfdir)) == NULL ||
D 2
	     !DIRCT || statemap[lfdir] != FSTATE) {
E 2
I 2
D 3
	     !DIRCT(dp) || statemap[lfdir] != FSTATE) {
E 3
I 3
	     !DIRCT(dp) || statemap[lfdir] != DFOUND) {
E 4
I 4
	dp = ginode(lfdir);
D 7
	if (!DIRCT(dp) || statemap[lfdir] != DFOUND) {
E 4
E 3
E 2
		pfatal("SORRY. NO lost+found DIRECTORY");
		printf("\n\n");
E 7
I 7
D 21
	if (!DIRCT(dp)) {
E 21
I 21
	if ((dp->di_mode & IFMT) != IFDIR) {
E 21
		pfatal("lost+found IS NOT A DIRECTORY");
		if (reply("REALLOCATE") == 0)
			return (0);
		oldlfdir = lfdir;
D 17
		if ((lfdir = allocdir(ROOTINO, 0)) == 0) {
E 17
I 17
D 21
		if ((lfdir = allocdir(ROOTINO, 0, lfmode)) == 0) {
E 21
I 21
		if ((lfdir = allocdir(ROOTINO, (ino_t)0, lfmode)) == 0) {
E 21
E 17
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY\n\n");
			return (0);
		}
D 24
		idesc.id_type = DATA;
		idesc.id_func = chgino;
		idesc.id_number = ROOTINO;
		idesc.id_parent = lfdir;	/* new inumber for lost+found */
		idesc.id_name = lfname;
		if ((ckinode(ginode(ROOTINO), &idesc) & ALTERED) == 0) {
E 24
I 24
		if ((changeino(ROOTINO, lfname, lfdir) & ALTERED) == 0) {
E 24
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY\n\n");
			return (0);
		}
		inodirty();
		idesc.id_type = ADDR;
		idesc.id_func = pass4check;
		idesc.id_number = oldlfdir;
		adjust(&idesc, lncntp[oldlfdir] + 1);
		lncntp[oldlfdir] = 0;
		dp = ginode(lfdir);
	}
	if (statemap[lfdir] != DFOUND) {
		pfatal("SORRY. NO lost+found DIRECTORY\n\n");
E 7
		return (0);
	}
D 5
	if (fragoff(&sblock, dp->di_size)) {
		dp->di_size = fragroundup(&sblock, dp->di_size);
E 5
I 5
D 10
	if (dp->di_size % DIRBLKSIZ) {
		dp->di_size = roundup(dp->di_size, DIRBLKSIZ);
E 5
		inodirty();
	}
E 10
D 24
	len = strlen(lfname);
	bcopy(lfname, pathp, len + 1);
	pathp += len;
D 9
	idesc.id_type = DATA;
	idesc.id_func = mkentry;
	idesc.id_number = lfdir;
D 8
	idesc.id_filesize = dp->di_size;
E 8
	idesc.id_parent = orphan;	/* this is the inode to enter */
	idesc.id_fix = DONTKNOW;
I 6
	idesc.id_name = tempname;
	len = lftempname(idesc.id_name, orphan);
E 6
D 5
	if ((ckinode(dp, &idesc) & ALTERED) == 0) {
E 5
I 5
	if (makeentry(dp, &idesc) == 0) {
E 9
I 9
	len = lftempname(tempname, orphan);
E 24
I 24
	(void)lftempname(tempname, orphan);
E 24
	if (makeentry(lfdir, orphan, tempname) == 0) {
E 9
E 5
		pfatal("SORRY. NO SPACE IN lost+found DIRECTORY");
		printf("\n\n");
		return (0);
	}
	lncntp[orphan]--;
D 24
	*pathp++ = '/';
D 6
	pathp += lftempname(pathp, orphan);
E 6
I 6
D 14
	bcopy(idesc.id_name, pathp, len + 1);
E 14
I 14
	bcopy(tempname, pathp, len + 1);
E 14
	pathp += len;
E 24
E 6
	if (lostdir) {
D 24
		dp = ginode(orphan);
		idesc.id_type = DATA;
D 7
		idesc.id_func = chgdd;
E 7
I 7
		idesc.id_func = chgino;
E 7
		idesc.id_number = orphan;
D 8
		idesc.id_filesize = dp->di_size;
E 8
		idesc.id_fix = DONTKNOW;
I 7
		idesc.id_name = "..";
		idesc.id_parent = lfdir;	/* new value for ".." */
E 7
		(void)ckinode(dp, &idesc);
E 24
I 24
		if ((changeino(orphan, "..", lfdir) & ALTERED) == 0 &&
		    parentdir != (ino_t)-1)
D 30
			makeentry(orphan, lfdir, "..");
E 30
I 30
			(void)makeentry(orphan, lfdir, "..");
E 30
E 24
D 4
		if ((dp = ginode(lfdir)) != NULL) {
			dp->di_nlink++;
			inodirty();
			lncntp[lfdir]++;
		}
E 4
I 4
		dp = ginode(lfdir);
		dp->di_nlink++;
		inodirty();
		lncntp[lfdir]++;
E 4
D 30
		pwarn("DIR I=%u CONNECTED. ", orphan);
E 30
I 30
		pwarn("DIR I=%lu CONNECTED. ", orphan);
E 30
D 21
		printf("PARENT WAS I=%u\n", pdir);
E 21
I 21
D 24
		printf("PARENT WAS I=%u\n", parentdir);
E 24
I 24
		if (parentdir != (ino_t)-1)
D 30
			printf("PARENT WAS I=%u\n", parentdir);
E 30
I 30
			printf("PARENT WAS I=%lu\n", parentdir);
E 30
E 24
E 21
		if (preen == 0)
			printf("\n");
	}
	return (1);
I 5
}

/*
I 24
 * fix an entry in a directory.
 */
I 43
int
E 43
changeino(dir, name, newnum)
	ino_t dir;
	char *name;
	ino_t newnum;
{
	struct inodesc idesc;

D 44
	bzero((char *)&idesc, sizeof(struct inodesc));
E 44
I 44
	memset(&idesc, 0, sizeof(struct inodesc));
E 44
	idesc.id_type = DATA;
	idesc.id_func = chgino;
	idesc.id_number = dir;
	idesc.id_fix = DONTKNOW;
	idesc.id_name = name;
	idesc.id_parent = newnum;	/* new value for name */
	return (ckinode(ginode(dir), &idesc));
}

/*
E 24
 * make an entry in a directory
 */
I 43
int
E 43
D 9
makeentry(dp, idesc)
	DINODE *dp;
	struct inodesc *idesc;
E 9
I 9
makeentry(parent, ino, name)
	ino_t parent, ino;
	char *name;
E 9
{
I 9
D 21
	DINODE *dp;
E 21
I 21
	struct dinode *dp;
E 21
	struct inodesc idesc;
I 24
	char pathbuf[MAXPATHLEN + 1];
E 24
E 9
	
D 9
	if ((ckinode(dp, idesc) & ALTERED) != 0)
E 9
I 9
D 21
	if (parent < ROOTINO || parent >= imax || ino < ROOTINO || ino >= imax)
E 21
I 21
	if (parent < ROOTINO || parent >= maxino ||
	    ino < ROOTINO || ino >= maxino)
E 21
		return (0);
D 21
	bzero(&idesc, sizeof(struct inodesc));
E 21
I 21
D 44
	bzero((char *)&idesc, sizeof(struct inodesc));
E 44
I 44
	memset(&idesc, 0, sizeof(struct inodesc));
E 44
E 21
	idesc.id_type = DATA;
	idesc.id_func = mkentry;
	idesc.id_number = parent;
	idesc.id_parent = ino;	/* this is the inode to enter */
	idesc.id_fix = DONTKNOW;
	idesc.id_name = name;
	dp = ginode(parent);
I 10
	if (dp->di_size % DIRBLKSIZ) {
		dp->di_size = roundup(dp->di_size, DIRBLKSIZ);
		inodirty();
	}
E 10
	if ((ckinode(dp, &idesc) & ALTERED) != 0)
E 9
		return (1);
D 24
	if (expanddir(dp) == 0)
E 24
I 24
	getpathname(pathbuf, parent, parent);
	dp = ginode(parent);
	if (expanddir(dp, pathbuf) == 0)
E 24
		return (0);
D 8
	idesc->id_filesize = dp->di_size;
E 8
D 9
	return (ckinode(dp, idesc) & ALTERED);
E 9
I 9
	return (ckinode(dp, &idesc) & ALTERED);
E 9
}

/*
 * Attempt to expand the size of a directory
 */
I 43
static int
E 43
D 24
expanddir(dp)
E 24
I 24
expanddir(dp, name)
E 24
D 21
	register DINODE *dp;
E 21
I 21
	register struct dinode *dp;
I 24
	char *name;
E 24
E 21
{
D 42
	daddr_t lastbn, newblk;
E 42
I 42
	ufs_daddr_t lastbn, newblk;
E 42
I 16
D 21
	register BUFAREA *bp;
E 21
I 21
	register struct bufarea *bp;
E 21
E 16
	char *cp, firstblk[DIRBLKSIZ];

	lastbn = lblkno(&sblock, dp->di_size);
D 28
	if (lastbn >= NDADDR - 1)
E 28
I 28
	if (lastbn >= NDADDR - 1 || dp->di_db[lastbn] == 0 || dp->di_size == 0)
E 28
		return (0);
	if ((newblk = allocblk(sblock.fs_frag)) == 0)
		return (0);
	dp->di_db[lastbn + 1] = dp->di_db[lastbn];
	dp->di_db[lastbn] = newblk;
	dp->di_size += sblock.fs_bsize;
	dp->di_blocks += btodb(sblock.fs_bsize);
D 12
	if (getblk(&fileblk, dp->di_db[lastbn + 1],
	    dblksize(&sblock, dp, lastbn + 1)) == NULL)
E 12
I 12
D 16
	getblk(&fileblk, dp->di_db[lastbn + 1],
	    dblksize(&sblock, dp, lastbn + 1));
	if (fileblk.b_errs != NULL)
E 16
I 16
	bp = getdirblk(dp->di_db[lastbn + 1],
D 30
		dblksize(&sblock, dp, lastbn + 1));
E 30
I 30
		(long)dblksize(&sblock, dp, lastbn + 1));
E 30
D 19
	if (bp->b_errs != NULL)
E 19
I 19
	if (bp->b_errs)
E 19
E 16
E 12
		goto bad;
D 16
	bcopy(dirblk.b_buf, firstblk, DIRBLKSIZ);
D 12
	if (getblk(&fileblk, newblk, sblock.fs_bsize) == NULL)
E 12
I 12
	getblk(&fileblk, newblk, sblock.fs_bsize);
	if (fileblk.b_errs != NULL)
E 16
I 16
D 44
	bcopy(bp->b_un.b_buf, firstblk, DIRBLKSIZ);
E 44
I 44
	memmove(firstblk, bp->b_un.b_buf, DIRBLKSIZ);
E 44
	bp = getdirblk(newblk, sblock.fs_bsize);
D 19
	if (bp->b_errs != NULL)
E 19
I 19
	if (bp->b_errs)
E 19
E 16
E 12
		goto bad;
D 16
	bcopy(firstblk, dirblk.b_buf, DIRBLKSIZ);
	for (cp = &dirblk.b_buf[DIRBLKSIZ];
	     cp < &dirblk.b_buf[sblock.fs_bsize];
E 16
I 16
D 44
	bcopy(firstblk, bp->b_un.b_buf, DIRBLKSIZ);
E 44
I 44
	memmove(bp->b_un.b_buf, firstblk, DIRBLKSIZ);
E 44
	for (cp = &bp->b_un.b_buf[DIRBLKSIZ];
	     cp < &bp->b_un.b_buf[sblock.fs_bsize];
E 16
	     cp += DIRBLKSIZ)
D 44
		bcopy((char *)&emptydir, cp, sizeof emptydir);
E 44
I 44
		memmove(cp, &emptydir, sizeof emptydir);
E 44
D 16
	dirty(&fileblk);
D 12
	if (getblk(&fileblk, dp->di_db[lastbn + 1],
	    dblksize(&sblock, dp, lastbn + 1)) == NULL)
E 12
I 12
	getblk(&fileblk, dp->di_db[lastbn + 1],
	    dblksize(&sblock, dp, lastbn + 1));
	if (fileblk.b_errs != NULL)
E 16
I 16
	dirty(bp);
	bp = getdirblk(dp->di_db[lastbn + 1],
D 30
		dblksize(&sblock, dp, lastbn + 1));
E 30
I 30
		(long)dblksize(&sblock, dp, lastbn + 1));
E 30
D 19
	if (bp->b_errs != NULL)
E 19
I 19
	if (bp->b_errs)
E 19
E 16
E 12
		goto bad;
D 16
	bcopy((char *)&emptydir, dirblk.b_buf, sizeof emptydir);
E 16
I 16
D 44
	bcopy((char *)&emptydir, bp->b_un.b_buf, sizeof emptydir);
E 44
I 44
	memmove(bp->b_un.b_buf, &emptydir, sizeof emptydir);
E 44
E 16
D 24
	pwarn("NO SPACE LEFT IN %s", pathname);
E 24
I 24
	pwarn("NO SPACE LEFT IN %s", name);
E 24
	if (preen)
		printf(" (EXPANDED)\n");
	else if (reply("EXPAND") == 0)
		goto bad;
D 16
	dirty(&fileblk);
E 16
I 16
	dirty(bp);
E 16
	inodirty();
	return (1);
bad:
	dp->di_db[lastbn] = dp->di_db[lastbn + 1];
	dp->di_db[lastbn + 1] = 0;
	dp->di_size -= sblock.fs_bsize;
	dp->di_blocks -= btodb(sblock.fs_bsize);
	freeblk(newblk, sblock.fs_frag);
	return (0);
I 6
}

/*
 * allocate a new directory
 */
I 43
ino_t
E 43
D 17
allocdir(parent, request)
E 17
I 17
allocdir(parent, request, mode)
E 17
	ino_t parent, request;
I 17
	int mode;
E 17
{
	ino_t ino;
	char *cp;
D 21
	DINODE *dp;
I 16
	register BUFAREA *bp;
E 21
I 21
	struct dinode *dp;
	register struct bufarea *bp;
I 34
	struct dirtemplate *dirp;
E 34
E 21
E 16

D 17
	ino = allocino(request, IFDIR|0755);
E 17
I 17
	ino = allocino(request, IFDIR|mode);
E 17
D 34
	dirhead.dot_ino = ino;
	dirhead.dotdot_ino = parent;
E 34
I 34
	if (newinofmt)
		dirp = &dirhead;
	else
		dirp = (struct dirtemplate *)&odirhead;
	dirp->dot_ino = ino;
	dirp->dotdot_ino = parent;
E 34
	dp = ginode(ino);
D 12
	if (getblk(&fileblk, dp->di_db[0], sblock.fs_fsize) == NULL) {
E 12
I 12
D 16
	getblk(&fileblk, dp->di_db[0], sblock.fs_fsize);
	if (fileblk.b_errs != NULL) {
E 16
I 16
	bp = getdirblk(dp->di_db[0], sblock.fs_fsize);
D 19
	if (bp->b_errs != NULL) {
E 19
I 19
	if (bp->b_errs) {
E 19
E 16
E 12
		freeino(ino);
		return (0);
	}
D 16
	bcopy((char *)&dirhead, dirblk.b_buf, sizeof dirhead);
	for (cp = &dirblk.b_buf[DIRBLKSIZ];
	     cp < &dirblk.b_buf[sblock.fs_fsize];
E 16
I 16
D 34
	bcopy((char *)&dirhead, bp->b_un.b_buf, sizeof dirhead);
E 34
I 34
D 44
	bcopy((char *)dirp, bp->b_un.b_buf, sizeof(struct dirtemplate));
E 44
I 44
	memmove(bp->b_un.b_buf, dirp, sizeof(struct dirtemplate));
E 44
E 34
	for (cp = &bp->b_un.b_buf[DIRBLKSIZ];
	     cp < &bp->b_un.b_buf[sblock.fs_fsize];
E 16
	     cp += DIRBLKSIZ)
D 44
		bcopy((char *)&emptydir, cp, sizeof emptydir);
E 44
I 44
		memmove(cp, &emptydir, sizeof emptydir);
E 44
D 16
	dirty(&fileblk);
E 16
I 16
	dirty(bp);
E 16
	dp->di_nlink = 2;
	inodirty();
	if (ino == ROOTINO) {
		lncntp[ino] = dp->di_nlink;
I 31
		cacheino(dp, ino);
E 31
		return(ino);
	}
	if (statemap[parent] != DSTATE && statemap[parent] != DFOUND) {
		freeino(ino);
		return (0);
	}
I 31
	cacheino(dp, ino);
E 31
	statemap[ino] = statemap[parent];
	if (statemap[ino] == DSTATE) {
		lncntp[ino] = dp->di_nlink;
		lncntp[parent]++;
	}
	dp = ginode(parent);
	dp->di_nlink++;
	inodirty();
	return (ino);
}

/*
 * free a directory inode
 */
I 43
static void
E 43
freedir(ino, parent)
	ino_t ino, parent;
{
D 21
	DINODE *dp;
E 21
I 21
	struct dinode *dp;
E 21

	if (ino != parent) {
		dp = ginode(parent);
		dp->di_nlink--;
		inodirty();
	}
	freeino(ino);
E 6
E 5
}

/*
 * generate a temporary name for the lost+found directory.
 */
I 43
static int
E 43
lftempname(bufp, ino)
	char *bufp;
	ino_t ino;
{
	register ino_t in;
	register char *cp;
	int namlen;

	cp = bufp + 2;
D 21
	for (in = imax; in > 0; in /= 10)
E 21
I 21
	for (in = maxino; in > 0; in /= 10)
E 21
		cp++;
	*--cp = 0;
	namlen = cp - bufp;
	in = ino;
	while (cp > bufp) {
		*--cp = (in % 10) + '0';
		in /= 10;
	}
	*cp = '#';
	return (namlen);
I 16
}

/*
 * Get a directory block.
 * Insure that it is held until another is requested.
 */
D 21
BUFAREA *
E 21
I 21
D 43
struct bufarea *
E 43
I 43
static struct bufarea *
E 43
E 21
getdirblk(blkno, size)
D 42
	daddr_t blkno;
E 42
I 42
	ufs_daddr_t blkno;
E 42
	long size;
{
D 21
	static BUFAREA *pbp = 0;
E 21
I 21
D 26
	static struct bufarea *pbp = 0;
E 26
E 21

D 26
	if (pbp != 0)
		pbp->b_flags &= ~B_INUSE;
	pbp = getdatablk(blkno, size);
	return (pbp);
E 26
I 26
	if (pdirbp != 0)
		pdirbp->b_flags &= ~B_INUSE;
	pdirbp = getdatablk(blkno, size);
	return (pdirbp);
E 26
E 16
}
E 1
