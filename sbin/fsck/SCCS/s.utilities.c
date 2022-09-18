h11209
s 00005/00003/00597
d D 8.6 95/05/19 13:57:07 mckusick 51 50
c give marked clean message rather than modified if that is the only change
e
s 00010/00002/00590
d D 8.5 95/05/09 15:45:07 mckusick 50 49
c check and act on the clean flag
e
s 00004/00004/00588
d D 8.4 95/04/28 10:38:16 bostic 49 48
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00095/00043/00497
d D 8.3 95/04/27 11:32:57 mckusick 48 47
c add function prototypes
e
s 00007/00007/00533
d D 8.2 95/03/21 00:10:42 mckusick 47 46
c daddr_t => ufs_daddr_t
e
s 00002/00002/00538
d D 8.1 93/06/05 10:56:57 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00537
d D 5.37 93/06/04 11:42:21 bostic 45 44
c rename devname to cdevname, devname(3) now in the C library
e
s 00012/00006/00528
d D 5.36 93/05/31 01:00:27 mckusick 44 43
c calculate lseek offset in 64-bit precision
e
s 00000/00001/00534
d D 5.35 93/05/10 16:59:48 mckusick 43 42
c delete bogus lseek definition
e
s 00005/00001/00530
d D 5.34 92/11/15 11:58:28 mckusick 42 41
c avoid core dumps and panics when interrupting fsck early
e
s 00006/00001/00525
d D 5.33 92/07/02 16:34:02 mckusick 41 40
c print name of ROOTINO properly; don't write superblock if aborting conversion
e
s 00001/00000/00525
d D 5.32 92/05/27 22:45:21 mckusick 40 39
c add <sys/time.h> for dinode.h
e
s 00003/00003/00522
d D 5.31 91/11/04 22:20:39 bostic 39 38
c break FFS into UFS/FFS/LFS
e
s 00004/00006/00521
d D 5.30 91/07/26 16:28:39 mckusick 38 37
c give as much of partial pathnames as possible
e
s 00009/00003/00518
d D 5.29 90/07/27 14:48:42 mckusick 37 36
c check I/O size against requested I/O size for errors;
c avoid recursion in getpathname; handle IGNORE state
e
s 00023/00023/00498
d D 5.28 90/07/20 16:51:27 mckusick 36 35
c lint (from Torek)
e
s 00001/00000/00520
d D 5.27 90/06/06 17:11:26 mckusick 35 34
c add FIFO as file type
e
s 00001/00011/00519
d D 5.26 90/06/01 16:18:04 bostic 34 33
c new copyright notice
e
s 00002/00000/00528
d D 5.25 90/03/27 18:05:42 mckusick 33 32
c initialize inode and directory buffer pointers for each run
e
s 00002/00002/00526
d D 5.24 90/03/27 17:42:51 mckusick 32 31
c use proper defined constant (from fuller@prisma.com)
e
s 00003/00003/00525
d D 5.23 90/02/07 00:09:28 mckusick 31 30
c check correct variable; have to use slow but safe ginode when printing pathnames
e
s 00002/00002/00526
d D 5.22 90/02/01 23:36:14 mckusick 30 29
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00015/00004/00513
d D 5.21 90/02/01 17:17:28 mckusick 29 28
c convert to BSD only copyright
e
s 00020/00034/00497
d D 5.20 90/02/01 17:08:18 mckusick 28 27
c eliminate last vestages of AT&T code
e
s 00066/00067/00465
d D 5.19 90/02/01 16:17:43 mckusick 27 26
c lint and other aesthetic cleanups
e
s 00001/00003/00531
d D 5.18 89/10/24 19:05:30 mckusick 26 25
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00005/00003/00529
d D 5.17 89/09/15 20:57:56 bostic 25 24
c POSIX signals
e
s 00004/00003/00528
d D 5.16 89/06/30 17:02:14 mckusick 24 23
c ANSI C cleanups from Torek
e
s 00006/00002/00525
d D 5.15 89/06/27 17:44:54 mckusick 23 22
c free up buffer space after use
e
s 00005/00003/00522
d D 5.14 89/06/26 21:42:17 mckusick 22 21
c new include file locations engendered by vnodes
e
s 00005/00004/00520
d D 5.13 88/06/07 18:52:04 mckusick 21 19
c must be sure to always convert b_bno to disk block (db) units
e
s 00002/00001/00523
d R 5.13 88/06/07 15:45:16 mckusick 20 19
c missing fsbtodb!
e
s 00009/00003/00515
d D 5.12 88/05/25 17:21:12 mckusick 19 18
c add firewall to check for lost buffers; fine tune cache statistics
e
s 00078/00006/00440
d D 5.11 88/05/07 01:04:19 mckusick 18 17
c expand from three static buffer to a dynamic buffer pool;
c initial sizing of the buffer pool is 128K (For 8K fs == 16 buffers)
e
s 00002/00002/00444
d D 5.10 87/04/07 19:49:22 karels 17 16
c fix alternate superblock location again; don't offer to rewrite
c standard superblock if we haven't found a good one yet; standardize units
c for -b (sectors! as before); kernel may change fs_dbsize
e
s 00018/00010/00428
d D 5.9 87/03/11 20:06:28 karels 16 15
c use physical sector size for partial buffer reads;
c -n implies "yes" answer for "CONTINUE?"
e
s 00006/00006/00432
d D 5.8 87/02/23 15:54:08 mckusick 15 14
c eliminate dbtob macro (which uses DEV_BSIZE)
e
s 00002/00002/00436
d D 5.7 87/02/23 14:42:21 mckusick 14 13
c use SBOFF instead of SBLOCK
e
s 00011/00010/00427
d D 5.6 87/02/18 18:14:45 mckusick 13 12
c intuit the appropriate DEV_BSIZE from fsbtodb macro
e
s 00001/00001/00436
d D 5.5 87/02/11 16:38:19 mckusick 12 11
c must zero the buffer
e
s 00005/00002/00432
d D 5.4 87/01/15 11:09:38 mckusick 11 10
c must do lseek after read or write failure
e
s 00003/00003/00431
d D 5.3 87/01/07 19:26:45 mckusick 10 9
c be more persistent in trying to read directories; 
c add FOUND return status for routines called from dirscan
e
s 00026/00000/00408
d D 5.2 85/09/10 20:14:29 karels 9 8
c allow a single sigquit to force exit(2) after completing checks
c if preening
e
s 00008/00002/00400
d D 5.1 85/06/05 08:58:37 dist 8 7
c Add copyright
e
s 00017/00006/00385
d D 3.7 85/06/02 16:46:27 mckusick 7 6
c persist in writing back bad sectors; be more informative about the errors
e
s 00022/00009/00369
d D 3.6 85/05/31 00:19:43 mckusick 6 5
c check for improper directory offsets; recover gracefully from read errors
e
s 00001/00000/00377
d D 3.5 85/02/18 16:27:05 mckusick 5 4
c must remember to flush out cylinder group block when done
e
s 00053/00000/00324
d D 3.4 85/02/15 12:09:17 mckusick 4 3
c calc and print out pathname of offending hard links to directories
e
s 00044/00000/00280
d D 3.3 85/02/11 20:55:35 mckusick 3 2
c expand lost+found when running out of space
e
s 00029/00024/00251
d D 3.2 85/02/07 17:52:26 mckusick 2 1
c code reorganization and cleanup
e
s 00275/00000/00000
d D 3.1 84/03/31 21:03:55 mckusick 1 0
c date and time created 84/03/31 21:03:55 by mckusick
e
u
U
t
T
I 8
/*
D 29
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 29
I 29
D 46
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 46
I 46
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
D 34
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
E 34
I 34
 * %sccs.include.redist.c%
E 34
E 29
 */

E 8
I 1
#ifndef lint
D 8
static char version[] = "%W% (Berkeley) %G%";
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 29
#endif not lint
E 29
I 29
#endif /* not lint */
E 29
E 8

D 25
#include <stdio.h>
#include <ctype.h>
E 25
#include <sys/param.h>
I 40
#include <sys/time.h>
I 48

E 48
E 40
D 22
#include <sys/inode.h>
#include <sys/fs.h>
I 4
#include <sys/dir.h>
E 22
I 22
D 26
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 26
I 26
D 39
#include <ufs/dinode.h>
E 26
#include <ufs/fs.h>
#include <ufs/dir.h>
E 39
I 39
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
#include <ufs/ffs/fs.h>
E 39
I 25
D 48
#include <stdio.h>
I 36
#include <stdlib.h>
#include <string.h>
E 48
I 48

E 48
E 36
#include <ctype.h>
I 48
#include <err.h>
#include <string.h>

E 48
E 25
E 22
E 4
#include "fsck.h"

I 18
long	diskreads, totalreads;	/* Disk cache statistics */
E 18
D 43
long	lseek();
E 43
I 24
D 36
char	*malloc();
E 36
E 24

I 48
static void rwerror __P((char *mesg, ufs_daddr_t blk));

int
E 48
ftypeok(dp)
D 27
	DINODE *dp;
E 27
I 27
	struct dinode *dp;
E 27
{
	switch (dp->di_mode & IFMT) {

	case IFDIR:
	case IFREG:
	case IFBLK:
	case IFCHR:
	case IFLNK:
	case IFSOCK:
I 35
	case IFIFO:
E 35
		return (1);

	default:
		if (debug)
			printf("bad file type 0%o\n", dp->di_mode);
		return (0);
	}
}

I 48
int
E 48
D 27
reply(s)
	char *s;
E 27
I 27
D 28
reply(mesg)
	char *mesg;
E 28
I 28
reply(question)
	char *question;
E 28
E 27
{
D 28
	char line[80];
I 16
D 27
	int cont = (strcmp(s, "CONTINUE") == 0);
E 27
I 27
	int cont = (strcmp(mesg, "CONTINUE") == 0);
E 28
I 28
	int persevere;
	char c;
E 28
E 27
E 16

	if (preen)
		pfatal("INTERNAL ERROR: GOT TO reply()");
D 2
	rplyflag = 1;
E 2
D 27
	printf("\n%s? ", s);
D 16
	if (nflag || dfile.wfdes < 0) {
E 16
I 16
	if (!cont && (nflag || dfile.wfdes < 0)) {
E 27
I 27
D 28
	printf("\n%s? ", mesg);
	if (!cont && (nflag || fswritefd < 0)) {
E 27
E 16
		printf(" no\n\n");
E 28
I 28
	persevere = !strcmp(question, "CONTINUE");
	printf("\n");
	if (!persevere && (nflag || fswritefd < 0)) {
		printf("%s? no\n\n", question);
E 28
		return (0);
	}
D 16
	if (yflag) {
E 16
I 16
D 28
	if (yflag || (cont && nflag)) {
E 16
		printf(" yes\n\n");
E 28
I 28
	if (yflag || (persevere && nflag)) {
		printf("%s? yes\n\n", question);
E 28
		return (1);
	}
D 28
	if (getline(stdin, line, sizeof(line)) == EOF)
		errexit("\n");
E 28
I 28
	do	{
		printf("%s? [yn] ", question);
		(void) fflush(stdout);
		c = getc(stdin);
		while (c != '\n' && getc(stdin) != '\n')
			if (feof(stdin))
				return (0);
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
E 28
	printf("\n");
D 28
	if (line[0] == 'y' || line[0] == 'Y')
E 28
I 28
	if (c == 'y' || c == 'Y')
E 28
		return (1);
D 28
	else
		return (0);
}

getline(fp, loc, maxlen)
	FILE *fp;
	char *loc;
I 27
	int maxlen;
E 27
{
D 27
	register n;
E 27
I 27
	register long n;
E 27
	register char *p, *lastloc;

	p = loc;
	lastloc = &p[maxlen-1];
	while ((n = getc(fp)) != '\n') {
		if (n == EOF)
			return (EOF);
		if (!isspace(n) && p < lastloc)
			*p++ = n;
	}
	*p = 0;
	return (p - loc);
E 28
I 28
	return (0);
E 28
}

I 18
/*
 * Malloc buffers and set up cache.
 */
I 48
void
E 48
bufinit()
{
D 27
	register BUFAREA *bp;
E 27
I 27
	register struct bufarea *bp;
E 27
	long bufcnt, i;
	char *bufp;

I 33
	pbp = pdirbp = (struct bufarea *)0;
E 33
D 24
	bufp = (char *)malloc(sblock.fs_bsize);
E 24
I 24
D 27
	bufp = malloc(sblock.fs_bsize);
E 27
I 27
	bufp = malloc((unsigned int)sblock.fs_bsize);
E 27
E 24
	if (bufp == 0)
D 48
		errexit("cannot allocate buffer pool\n");
E 48
I 48
		errx(EEXIT, "cannot allocate buffer pool");
E 48
	cgblk.b_un.b_buf = bufp;
	initbarea(&cgblk);
	bufhead.b_next = bufhead.b_prev = &bufhead;
	bufcnt = MAXBUFSPACE / sblock.fs_bsize;
	if (bufcnt < MINBUFS)
		bufcnt = MINBUFS;
	for (i = 0; i < bufcnt; i++) {
D 27
		bp = (BUFAREA *)malloc(sizeof(BUFAREA));
D 24
		bufp = (char *)malloc(sblock.fs_bsize);
		if (bp == 0 || bufp == 0) {
E 24
I 24
		bufp = malloc(sblock.fs_bsize);
E 27
I 27
		bp = (struct bufarea *)malloc(sizeof(struct bufarea));
		bufp = malloc((unsigned int)sblock.fs_bsize);
E 27
		if (bp == NULL || bufp == NULL) {
E 24
			if (i >= MINBUFS)
				break;
D 48
			errexit("cannot allocate buffer pool\n");
E 48
I 48
			errx(EEXIT, "cannot allocate buffer pool");
E 48
		}
		bp->b_un.b_buf = bufp;
		bp->b_prev = &bufhead;
		bp->b_next = bufhead.b_next;
		bufhead.b_next->b_prev = bp;
		bufhead.b_next = bp;
		initbarea(bp);
	}
I 19
	bufhead.b_size = i;	/* save number of buffers */
E 19
}

/*
 * Manage a cache of directory blocks.
 */
E 18
D 27
BUFAREA *
E 27
I 27
struct bufarea *
E 27
I 18
getdatablk(blkno, size)
D 47
	daddr_t blkno;
E 47
I 47
	ufs_daddr_t blkno;
E 47
	long size;
{
D 27
	register BUFAREA *bp;
E 27
I 27
	register struct bufarea *bp;
E 27

	for (bp = bufhead.b_next; bp != &bufhead; bp = bp->b_next)
D 21
		if (bp->b_bno == blkno)
E 21
I 21
		if (bp->b_bno == fsbtodb(&sblock, blkno))
E 21
			goto foundit;
	for (bp = bufhead.b_prev; bp != &bufhead; bp = bp->b_prev)
		if ((bp->b_flags & B_INUSE) == 0)
			break;
	if (bp == &bufhead)
D 48
		errexit("deadlocked buffer pool\n");
E 48
I 48
		errx(EEXIT, "deadlocked buffer pool");
E 48
	getblk(bp, blkno, size);
	/* fall through */
foundit:
	totalreads++;
	bp->b_prev->b_next = bp->b_next;
	bp->b_next->b_prev = bp->b_prev;
	bp->b_prev = &bufhead;
	bp->b_next = bufhead.b_next;
	bufhead.b_next->b_prev = bp;
	bufhead.b_next = bp;
	bp->b_flags |= B_INUSE;
	return (bp);
}

D 27
BUFAREA *
E 27
I 27
D 36
struct bufarea *
E 36
I 36
void
E 36
E 27
E 18
getblk(bp, blk, size)
D 27
	register BUFAREA *bp;
E 27
I 27
	register struct bufarea *bp;
E 27
D 47
	daddr_t blk;
E 47
I 47
	ufs_daddr_t blk;
E 47
	long size;
{
D 27
	register struct filecntl *fcp;
E 27
D 47
	daddr_t dblk;
E 47
I 47
	ufs_daddr_t dblk;
E 47

D 27
	fcp = &dfile;
E 27
D 18
	dblk = fsbtodb(&sblock, blk);
	if (bp->b_bno == dblk)
E 18
I 18
D 21
	if (bp->b_bno == blk)
E 21
I 21
	dblk = fsbtodb(&sblock, blk);
D 36
	if (bp->b_bno == dblk)
E 21
E 18
		return (bp);
D 27
	flush(fcp, bp);
E 27
I 27
	flush(fswritefd, bp);
E 27
D 6
	if (bread(fcp, bp->b_un.b_buf, dblk, size) != 0) {
		bp->b_bno = dblk;
		bp->b_size = size;
		return (bp);
	}
	bp->b_bno = (daddr_t)-1;
	return (NULL);
E 6
I 6
D 18
	bp->b_errs = bread(fcp, bp->b_un.b_buf, dblk, size);
	bp->b_bno = dblk;
E 18
I 18
	diskreads++;
D 21
	bp->b_errs = bread(fcp, bp->b_un.b_buf, fsbtodb(&sblock, blk), size);
	bp->b_bno = blk;
E 21
I 21
D 27
	bp->b_errs = bread(fcp, bp->b_un.b_buf, dblk, size);
E 27
I 27
	bp->b_errs = bread(fsreadfd, bp->b_un.b_buf, dblk, size);
E 27
	bp->b_bno = dblk;
E 21
E 18
	bp->b_size = size;
	return (bp);
E 36
I 36
	if (bp->b_bno != dblk) {
		flush(fswritefd, bp);
		diskreads++;
		bp->b_errs = bread(fsreadfd, bp->b_un.b_buf, dblk, size);
		bp->b_bno = dblk;
		bp->b_size = size;
	}
E 36
E 6
}

I 48
void
E 48
D 27
flush(fcp, bp)
	struct filecntl *fcp;
	register BUFAREA *bp;
E 27
I 27
flush(fd, bp)
	int fd;
	register struct bufarea *bp;
E 27
{
I 2
	register int i, j;
E 2

D 2
	if (bp->b_dirty)
		(void)bwrite(fcp, bp->b_un.b_buf, bp->b_bno, (long)bp->b_size);
E 2
I 2
	if (!bp->b_dirty)
		return;
I 6
	if (bp->b_errs != 0)
D 16
		pfatal("WRITING ZERO'ED BLOCK %d TO DISK\n", bp->b_bno);
E 16
I 16
		pfatal("WRITING %sZERO'ED BLOCK %d TO DISK\n",
		    (bp->b_errs == bp->b_size / dev_bsize) ? "" : "PARTIALLY ",
		    bp->b_bno);
E 16
E 6
E 2
	bp->b_dirty = 0;
I 6
	bp->b_errs = 0;
E 6
I 2
D 7
	(void)bwrite(fcp, bp->b_un.b_buf, bp->b_bno, (long)bp->b_size);
E 7
I 7
D 27
	bwrite(fcp, bp->b_un.b_buf, bp->b_bno, (long)bp->b_size);
E 27
I 27
	bwrite(fd, bp->b_un.b_buf, bp->b_bno, (long)bp->b_size);
E 27
E 7
	if (bp != &sblk)
		return;
	for (i = 0, j = 0; i < sblock.fs_cssize; i += sblock.fs_bsize, j++) {
D 7
		(void)bwrite(&dfile, (char *)sblock.fs_csp[j],
E 7
I 7
D 27
		bwrite(&dfile, (char *)sblock.fs_csp[j],
E 27
I 27
		bwrite(fswritefd, (char *)sblock.fs_csp[j],
E 27
E 7
		    fsbtodb(&sblock, sblock.fs_csaddr + j * sblock.fs_frag),
		    sblock.fs_cssize - i < sblock.fs_bsize ?
		    sblock.fs_cssize - i : sblock.fs_bsize);
	}
E 2
}

I 48
static void
E 48
D 27
rwerr(s, blk)
	char *s;
E 27
I 27
rwerror(mesg, blk)
	char *mesg;
E 27
D 47
	daddr_t blk;
E 47
I 47
	ufs_daddr_t blk;
E 47
{

	if (preen == 0)
		printf("\n");
D 27
	pfatal("CANNOT %s: BLK %ld", s, blk);
E 27
I 27
	pfatal("CANNOT %s: BLK %ld", mesg, blk);
E 27
	if (reply("CONTINUE") == 0)
D 48
		errexit("Program terminated\n");
E 48
I 48
		exit(EEXIT);
E 48
}

I 48
void
E 48
D 50
ckfini()
E 50
I 50
ckfini(markclean)
	int markclean;
E 50
{
I 18
D 23
	register BUFAREA *bp;
E 23
I 23
D 27
	register BUFAREA *bp, *nbp;
E 27
I 27
	register struct bufarea *bp, *nbp;
E 27
E 23
I 19
D 51
	int cnt = 0;
E 51
I 51
	int ofsmodified, cnt = 0;
E 51
E 19
E 18

I 42
	if (fswritefd < 0) {
		(void)close(fsreadfd);
		return;
	}
E 42
D 18
	flush(&dfile, &fileblk);
E 18
D 27
	flush(&dfile, &sblk);
E 27
I 27
	flush(fswritefd, &sblk);
E 27
D 13
	if (sblk.b_bno != SBLOCK) {
		sblk.b_bno = SBLOCK;
E 13
I 13
D 14
	if (sblk.b_bno != SBLOCK * DEV_BSIZE / dev_bsize &&
E 14
I 14
D 16
	if (sblk.b_bno != SBOFF / dev_bsize &&
E 16
I 16
D 17
	if (dev_bsize && sblk.b_bno != SBOFF / dev_bsize &&
E 17
I 17
	if (havesb && sblk.b_bno != SBOFF / dev_bsize &&
E 17
E 16
E 14
	    !preen && reply("UPDATE STANDARD SUPERBLOCK")) {
D 14
		sblk.b_bno = SBLOCK * DEV_BSIZE / dev_bsize;
E 14
I 14
		sblk.b_bno = SBOFF / dev_bsize;
E 14
E 13
		sbdirty();
D 27
		flush(&dfile, &sblk);
E 27
I 27
		flush(fswritefd, &sblk);
E 27
	}
D 18
	flush(&dfile, &inoblk);
E 18
I 5
D 27
	flush(&dfile, &cgblk);
E 27
I 27
	flush(fswritefd, &cgblk);
E 27
I 18
D 19
	for (bp = bufhead.b_prev; bp != &bufhead; bp = bp->b_prev)
E 19
I 19
D 23
	for (bp = bufhead.b_prev; bp != &bufhead; bp = bp->b_prev) {
E 23
I 23
	free(cgblk.b_un.b_buf);
D 42
	for (bp = bufhead.b_prev; bp != &bufhead; bp = nbp) {
E 42
I 42
	for (bp = bufhead.b_prev; bp && bp != &bufhead; bp = nbp) {
E 42
E 23
		cnt++;
E 19
D 27
		flush(&dfile, bp);
E 27
I 27
		flush(fswritefd, bp);
E 27
I 23
		nbp = bp->b_prev;
		free(bp->b_un.b_buf);
		free((char *)bp);
E 23
I 19
	}
	if (bufhead.b_size != cnt)
D 48
		errexit("Panic: lost %d buffers\n", bufhead.b_size - cnt);
E 48
I 48
		errx(EEXIT, "Panic: lost %d buffers", bufhead.b_size - cnt);
E 48
I 33
	pbp = pdirbp = (struct bufarea *)0;
I 50
	if (markclean && sblock.fs_clean == 0) {
D 51
		if (debug)
			pwarn("MARKING FILE SYSTEM CLEAN\n");
E 51
		sblock.fs_clean = 1;
		sbdirty();
I 51
		ofsmodified = fsmodified;
E 51
		flush(fswritefd, &sblk);
I 51
		fsmodified = ofsmodified;
		if (!preen)
			printf("\n***** FILE SYSTEM MARKED CLEAN *****\n");
E 51
	}
E 50
E 33
E 19
	if (debug)
D 19
		printf("cache hit %d of %d (%d%%)\n", totalreads - diskreads,
		    totalreads, (totalreads - diskreads) * 100 / totalreads);
E 19
I 19
D 36
		printf("cache missed %d of %d (%d%%)\n", diskreads,
		    totalreads, diskreads * 100 / totalreads);
E 36
I 36
		printf("cache missed %ld of %ld (%d%%)\n", diskreads,
		    totalreads, (int)(diskreads * 100 / totalreads));
E 36
E 19
E 18
E 5
D 27
	(void)close(dfile.rfdes);
	(void)close(dfile.wfdes);
E 27
I 27
	(void)close(fsreadfd);
	(void)close(fswritefd);
E 27
}

I 48
int
E 48
D 27
bread(fcp, buf, blk, size)
	register struct filecntl *fcp;
E 27
I 27
bread(fd, buf, blk, size)
	int fd;
E 27
	char *buf;
D 47
	daddr_t blk;
E 47
I 47
	ufs_daddr_t blk;
E 47
	long size;
{
I 6
	char *cp;
	int i, errs;
I 44
	off_t offset;
E 44

E 6
D 15
	if (lseek(fcp->rfdes, (long)dbtob(blk), 0) < 0)
E 15
I 15
D 27
	if (lseek(fcp->rfdes, blk * dev_bsize, 0) < 0)
E 15
		rwerr("SEEK", blk);
	else if (read(fcp->rfdes, buf, (int)size) == size)
E 27
I 27
D 44
	if (lseek(fd, blk * dev_bsize, 0) < 0)
E 44
I 44
	offset = blk;
	offset *= dev_bsize;
	if (lseek(fd, offset, 0) < 0)
E 44
		rwerror("SEEK", blk);
	else if (read(fd, buf, (int)size) == size)
E 27
D 6
		return (1);
E 6
I 6
		return (0);
E 6
D 27
	rwerr("READ", blk);
D 6
	return (0);
E 6
I 6
D 15
	if (lseek(fcp->rfdes, (long)dbtob(blk), 0) < 0)
E 15
I 15
	if (lseek(fcp->rfdes, blk * dev_bsize, 0) < 0)
E 15
		rwerr("SEEK", blk);
E 27
I 27
	rwerror("READ", blk);
D 44
	if (lseek(fd, blk * dev_bsize, 0) < 0)
E 44
I 44
	if (lseek(fd, offset, 0) < 0)
E 44
		rwerror("SEEK", blk);
E 27
	errs = 0;
I 11
D 12
	bzero(cp, size);
E 12
I 12
D 27
	bzero(buf, size);
E 27
I 27
D 36
	bzero(buf, (int)size);
E 36
I 36
D 49
	bzero(buf, (size_t)size);
E 49
I 49
	memset(buf, 0, (size_t)size);
E 49
E 36
E 27
E 12
E 11
I 7
D 16
	pfatal("THE FOLLOWING SECTORS COULD NOT BE READ:");
E 7
D 13
	for (cp = buf, i = 0; i < size; i += DEV_BSIZE, cp += DEV_BSIZE) {
		if (read(fcp->rfdes, cp, DEV_BSIZE) < 0) {
I 11
			lseek(fcp->rfdes, (long)dbtob(blk) + i + DEV_BSIZE, 0);
E 11
I 7
			printf(" %d,", blk + i / DEV_BSIZE);
E 13
I 13
	for (cp = buf, i = 0; i < size; i += dev_bsize, cp += dev_bsize) {
		if (read(fcp->rfdes, cp, dev_bsize) < 0) {
D 15
			lseek(fcp->rfdes, (long)dbtob(blk) + i + dev_bsize, 0);
E 15
I 15
			lseek(fcp->rfdes, blk * dev_bsize + i + dev_bsize, 0);
E 15
			printf(" %d,", blk + i / dev_bsize);
E 16
I 16
	printf("THE FOLLOWING DISK SECTORS COULD NOT BE READ:");
	for (cp = buf, i = 0; i < size; i += secsize, cp += secsize) {
D 27
		if (read(fcp->rfdes, cp, secsize) < 0) {
			lseek(fcp->rfdes, blk * dev_bsize + i + secsize, 0);
E 27
I 27
D 37
		if (read(fd, cp, (int)secsize) < 0) {
E 37
I 37
		if (read(fd, cp, (int)secsize) != secsize) {
E 37
D 36
			lseek(fd, blk * dev_bsize + i + secsize, 0);
E 36
I 36
D 44
			(void)lseek(fd, blk * dev_bsize + i + secsize, 0);
E 44
I 44
			(void)lseek(fd, offset + i + secsize, 0);
E 44
E 36
E 27
D 17
			if (secsize != dev_bsize)
E 17
I 17
			if (secsize != dev_bsize && dev_bsize != 1)
E 17
D 36
				printf(" %d (%d),",
E 36
I 36
				printf(" %ld (%ld),",
E 36
				    (blk * dev_bsize + i) / secsize,
				    blk + i / dev_bsize);
			else
D 36
				printf(" %d,", blk + i / dev_bsize);
E 36
I 36
				printf(" %ld,", blk + i / dev_bsize);
E 36
E 16
E 13
E 7
D 11
			bzero(cp, DEV_BSIZE);
E 11
			errs++;
		}
	}
D 7
	pwarn("%d SECTORS REPLACED WITH ZERO'ED BLOCKS\n", errs);
E 7
I 7
	printf("\n");
E 7
	return (errs);
E 6
}

I 48
void
E 48
D 27
bwrite(fcp, buf, blk, size)
	register struct filecntl *fcp;
E 27
I 27
bwrite(fd, buf, blk, size)
	int fd;
E 27
	char *buf;
D 47
	daddr_t blk;
E 47
I 47
	ufs_daddr_t blk;
E 47
	long size;
{
I 7
	int i;
	char *cp;
I 44
	off_t offset;
E 44
E 7

D 27
	if (fcp->wfdes < 0)
E 27
I 27
	if (fd < 0)
E 27
D 7
		return (0);
E 7
I 7
		return;
E 7
D 15
	if (lseek(fcp->wfdes, (long)dbtob(blk), 0) < 0)
E 15
I 15
D 27
	if (lseek(fcp->wfdes, blk * dev_bsize, 0) < 0)
E 15
		rwerr("SEEK", blk);
	else if (write(fcp->wfdes, buf, (int)size) == size) {
		fcp->mod = 1;
E 27
I 27
D 44
	if (lseek(fd, blk * dev_bsize, 0) < 0)
E 44
I 44
	offset = blk;
	offset *= dev_bsize;
	if (lseek(fd, offset, 0) < 0)
E 44
		rwerror("SEEK", blk);
	else if (write(fd, buf, (int)size) == size) {
		fsmodified = 1;
E 27
D 7
		return (1);
E 7
I 7
		return;
E 7
	}
D 27
	rwerr("WRITE", blk);
D 7
	return (0);
E 7
I 7
D 15
	if (lseek(fcp->wfdes, (long)dbtob(blk), 0) < 0)
E 15
I 15
	if (lseek(fcp->wfdes, blk * dev_bsize, 0) < 0)
E 15
		rwerr("SEEK", blk);
E 27
I 27
	rwerror("WRITE", blk);
D 44
	if (lseek(fd, blk * dev_bsize, 0) < 0)
E 44
I 44
	if (lseek(fd, offset, 0) < 0)
E 44
		rwerror("SEEK", blk);
E 27
D 16
	pfatal("THE FOLLOWING SECTORS COULD NOT BE WRITTEN:");
E 16
I 16
	printf("THE FOLLOWING SECTORS COULD NOT BE WRITTEN:");
E 16
D 13
	for (cp = buf, i = 0; i < size; i += DEV_BSIZE, cp += DEV_BSIZE)
D 11
		if (write(fcp->wfdes, cp, DEV_BSIZE) < 0)
E 11
I 11
		if (write(fcp->wfdes, cp, DEV_BSIZE) < 0) {
			lseek(fcp->rfdes, (long)dbtob(blk) + i + DEV_BSIZE, 0);
E 11
			printf(" %d,", blk + i / DEV_BSIZE);
E 13
I 13
	for (cp = buf, i = 0; i < size; i += dev_bsize, cp += dev_bsize)
D 27
		if (write(fcp->wfdes, cp, dev_bsize) < 0) {
D 15
			lseek(fcp->rfdes, (long)dbtob(blk) + i + dev_bsize, 0);
E 15
I 15
			lseek(fcp->rfdes, blk * dev_bsize + i + dev_bsize, 0);
E 27
I 27
D 37
		if (write(fd, cp, (int)dev_bsize) < 0) {
E 37
I 37
		if (write(fd, cp, (int)dev_bsize) != dev_bsize) {
E 37
D 36
			lseek(fd, blk * dev_bsize + i + dev_bsize, 0);
E 27
E 15
			printf(" %d,", blk + i / dev_bsize);
E 36
I 36
D 44
			(void)lseek(fd, blk * dev_bsize + i + dev_bsize, 0);
E 44
I 44
			(void)lseek(fd, offset + i + dev_bsize, 0);
E 44
			printf(" %ld,", blk + i / dev_bsize);
E 36
E 13
I 11
		}
E 11
	printf("\n");
	return;
E 7
}

I 3
/*
 * allocate a data block with the specified number of fragments
 */
I 48
ufs_daddr_t
E 48
allocblk(frags)
D 27
	int frags;
E 27
I 27
	long frags;
E 27
{
	register int i, j, k;

	if (frags <= 0 || frags > sblock.fs_frag)
		return (0);
D 27
	for (i = 0; i < fmax - sblock.fs_frag; i += sblock.fs_frag) {
E 27
I 27
	for (i = 0; i < maxfsblock - sblock.fs_frag; i += sblock.fs_frag) {
E 27
		for (j = 0; j <= sblock.fs_frag - frags; j++) {
D 27
			if (getbmap(i + j))
E 27
I 27
			if (testbmap(i + j))
E 27
				continue;
			for (k = 1; k < frags; k++)
D 27
				if (getbmap(i + j + k))
E 27
I 27
				if (testbmap(i + j + k))
E 27
					break;
			if (k < frags) {
				j += k;
				continue;
			}
			for (k = 0; k < frags; k++)
				setbmap(i + j + k);
			n_blks += frags;
			return (i + j);
		}
	}
	return (0);
}

/*
 * Free a previously allocated block
 */
I 48
void
E 48
freeblk(blkno, frags)
D 47
	daddr_t blkno;
E 47
I 47
	ufs_daddr_t blkno;
E 47
D 27
	int frags;
E 27
I 27
	long frags;
E 27
{
	struct inodesc idesc;

	idesc.id_blkno = blkno;
	idesc.id_numfrags = frags;
D 36
	pass4check(&idesc);
E 36
I 36
	(void)pass4check(&idesc);
E 36
I 4
}

/*
 * Find a pathname
 */
I 48
void
E 48
getpathname(namebuf, curdir, ino)
	char *namebuf;
	ino_t curdir, ino;
{
	int len;
	register char *cp;
	struct inodesc idesc;
I 37
	static int busy = 0;
E 37
	extern int findname();

I 41
	if (curdir == ino && ino == ROOTINO) {
		(void)strcpy(namebuf, "/");
		return;
	}
E 41
D 31
	if (statemap[ino] != DSTATE && statemap[ino] != DFOUND) {
E 31
I 31
D 37
	if (statemap[curdir] != DSTATE && statemap[curdir] != DFOUND) {
E 37
I 37
	if (busy ||
	    (statemap[curdir] != DSTATE && statemap[curdir] != DFOUND)) {
E 37
E 31
D 36
		strcpy(namebuf, "?");
E 36
I 36
		(void)strcpy(namebuf, "?");
E 36
		return;
	}
I 37
	busy = 1;
E 37
D 27
	bzero(&idesc, sizeof(struct inodesc));
E 27
I 27
D 49
	bzero((char *)&idesc, sizeof(struct inodesc));
E 49
I 49
	memset(&idesc, 0, sizeof(struct inodesc));
E 49
E 27
	idesc.id_type = DATA;
I 37
	idesc.id_fix = IGNORE;
E 37
D 32
	cp = &namebuf[BUFSIZ - 1];
E 32
I 32
	cp = &namebuf[MAXPATHLEN - 1];
E 32
D 10
	*cp-- = '\0';
E 10
I 10
	*cp = '\0';
E 10
	if (curdir != ino) {
		idesc.id_parent = curdir;
		goto namelookup;
	}
	while (ino != ROOTINO) {
		idesc.id_number = ino;
		idesc.id_func = findino;
		idesc.id_name = "..";
D 10
		if ((ckinode(ginode(ino), &idesc) & STOP) == 0)
E 10
I 10
D 30
		if ((ckinode(ginode(ino), &idesc) & FOUND) == 0)
E 30
I 30
D 31
		if ((ckinode(getcacheino(ino), &idesc) & FOUND) == 0)
E 31
I 31
		if ((ckinode(ginode(ino), &idesc) & FOUND) == 0)
E 31
E 30
E 10
			break;
	namelookup:
		idesc.id_number = idesc.id_parent;
		idesc.id_parent = ino;
		idesc.id_func = findname;
		idesc.id_name = namebuf;
D 10
		if ((ckinode(ginode(idesc.id_number), &idesc) & STOP) == 0)
E 10
I 10
D 30
		if ((ckinode(ginode(idesc.id_number), &idesc) & FOUND) == 0)
E 30
I 30
D 31
		if ((ckinode(getcacheino(idesc.id_number), &idesc)&FOUND) == 0)
E 31
I 31
		if ((ckinode(ginode(idesc.id_number), &idesc)&FOUND) == 0)
E 31
E 30
E 10
			break;
		len = strlen(namebuf);
		cp -= len;
D 38
		if (cp < &namebuf[MAXNAMLEN])
			break;
E 38
D 36
		bcopy(namebuf, cp, len);
E 36
I 36
D 49
		bcopy(namebuf, cp, (size_t)len);
E 49
I 49
		memmove(cp, namebuf, (size_t)len);
E 49
E 36
		*--cp = '/';
I 38
		if (cp < &namebuf[MAXNAMLEN])
			break;
E 38
		ino = idesc.id_number;
	}
I 37
	busy = 0;
E 37
D 38
	if (ino != ROOTINO) {
D 36
		strcpy(namebuf, "?");
E 36
I 36
		(void)strcpy(namebuf, "?");
E 36
		return;
	}
E 38
I 38
	if (ino != ROOTINO)
		*--cp = '?';
E 38
D 32
	bcopy(cp, namebuf, &namebuf[BUFSIZ] - cp);
E 32
I 32
D 36
	bcopy(cp, namebuf, &namebuf[MAXPATHLEN] - cp);
E 36
I 36
D 49
	bcopy(cp, namebuf, (size_t)(&namebuf[MAXPATHLEN] - cp));
E 49
I 49
	memmove(namebuf, cp, (size_t)(&namebuf[MAXPATHLEN] - cp));
E 49
E 36
E 32
E 4
}

I 25
void
E 25
E 3
D 48
catch()
E 48
I 48
catch(sig)
	int sig;
E 48
{
D 25

E 25
D 41
	ckfini();
E 41
I 41
	if (!doinglevel2)
D 50
		ckfini();
E 50
I 50
		ckfini(0);
E 50
E 41
	exit(12);
}

/*
I 9
 * When preening, allow a single quit to signal
 * a special exit after filesystem checks complete
 * so that reboot sequence may be interrupted.
 */
I 25
void
E 25
D 48
catchquit()
E 48
I 48
catchquit(sig)
	int sig;
E 48
{
	extern returntosingle;

	printf("returning to single-user after filesystem check\n");
	returntosingle = 1;
	(void)signal(SIGQUIT, SIG_DFL);
}

/*
 * Ignore a single quit signal; wait and flush just in case.
 * Used by child processes in preen.
 */
I 25
void
E 25
D 48
voidquit()
E 48
I 48
voidquit(sig)
	int sig;
E 48
{

	sleep(1);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGQUIT, SIG_DFL);
}

/*
E 9
 * determine whether an inode should be fixed.
 */
I 48
int
E 48
D 2
dofix(idesc)
E 2
I 2
dofix(idesc, msg)
E 2
	register struct inodesc *idesc;
I 2
	char *msg;
E 2
{

	switch (idesc->id_fix) {

	case DONTKNOW:
D 2
		direrr(idesc->id_number, "DIRECTORY CORRUPTED");
E 2
I 2
		if (idesc->id_type == DATA)
D 27
			direrr(idesc->id_number, msg);
E 27
I 27
			direrror(idesc->id_number, msg);
E 27
		else
			pwarn(msg);
		if (preen) {
			printf(" (SALVAGED)\n");
			idesc->id_fix = FIX;
			return (ALTERED);
		}
E 2
		if (reply("SALVAGE") == 0) {
			idesc->id_fix = NOFIX;
			return (0);
		}
		idesc->id_fix = FIX;
		return (ALTERED);

	case FIX:
		return (ALTERED);

	case NOFIX:
I 37
	case IGNORE:
E 37
		return (0);

	default:
D 48
		errexit("UNKNOWN INODESC FIX MODE %d\n", idesc->id_fix);
E 48
I 48
		errx(EEXIT, "UNKNOWN INODESC FIX MODE %d", idesc->id_fix);
E 48
	}
	/* NOTREACHED */
I 48
	return (0);
E 48
}

D 48
/* VARARGS1 */
D 2
error(s1, s2, s3, s4)
	char *s1;
{

	printf(s1, s2, s3, s4);
}

/* VARARGS1 */
E 2
errexit(s1, s2, s3, s4)
	char *s1;
{
D 2
	error(s1, s2, s3, s4);
E 2
I 2
	printf(s1, s2, s3, s4);
E 2
	exit(8);
}
E 48
I 48
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 48

/*
D 27
 * An inconsistency occured which shouldn't during normal operations.
 * Die if preening, otherwise just printf.
E 27
I 27
 * An unexpected inconsistency occured.
 * Die if preening, otherwise just print message and continue.
E 27
 */
D 48
/* VARARGS1 */
pfatal(s, a1, a2, a3)
	char *s;
E 48
I 48
void
#if __STDC__
pfatal(const char *fmt, ...)
#else
pfatal(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 48
{
D 48

	if (preen) {
D 45
		printf("%s: ", devname);
E 45
I 45
		printf("%s: ", cdevname);
E 45
		printf(s, a1, a2, a3);
		printf("\n");
D 2
		preendie();
E 2
I 2
		printf("%s: UNEXPECTED INCONSISTENCY; RUN fsck MANUALLY.\n",
D 45
			devname);
E 45
I 45
			cdevname);
E 45
		exit(8);
E 48
I 48
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	if (!preen) {
		(void)vfprintf(stderr, fmt, ap);
		va_end(ap);
		return;
E 48
E 2
	}
D 48
	printf(s, a1, a2, a3);
E 48
I 48
	(void)fprintf(stderr, "%s: ", cdevname);
	(void)vfprintf(stderr, fmt, ap);
	(void)fprintf(stderr,
	    "\n%s: UNEXPECTED INCONSISTENCY; RUN fsck MANUALLY.\n",
	    cdevname);
	exit(EEXIT);
E 48
}

D 2
preendie()
{

	printf("%s: UNEXPECTED INCONSISTENCY; RUN fsck MANUALLY.\n", devname);
	exit(8);
}

E 2
/*
D 27
 * Pwarn is like printf when not preening,
E 27
I 27
 * Pwarn just prints a message when not preening,
E 27
 * or a warning (preceded by filename) when preening.
 */
D 48
/* VARARGS1 */
pwarn(s, a1, a2, a3, a4, a5, a6)
	char *s;
E 48
I 48
void
#if __STDC__
pwarn(const char *fmt, ...)
#else
pwarn(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 48
{
D 48

E 48
I 48
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 48
	if (preen)
D 45
		printf("%s: ", devname);
E 45
I 45
D 48
		printf("%s: ", cdevname);
E 45
	printf(s, a1, a2, a3, a4, a5, a6);
E 48
I 48
		(void)fprintf(stderr, "%s: ", cdevname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
E 48
}

D 48
#ifndef lint
E 48
/*
 * Stub for routines from kernel.
 */
D 48
panic(s)
	char *s;
E 48
I 48
void
#if __STDC__
panic(const char *fmt, ...)
#else
panic(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 48
{
D 48

E 48
I 48
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 48
D 2
	pfatal("INTERNAL INCONSISTENCY: %s\n", s);
	exit(12);
E 2
I 2
	pfatal("INTERNAL INCONSISTENCY:");
D 48
	errexit(s);
E 48
I 48
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(EEXIT);
E 48
E 2
}
D 48
#endif
E 48
E 1
