h58794
s 00006/00015/00099
d D 8.3 95/04/28 10:14:55 bostic 19 18
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00004/00110
d D 8.2 93/09/23 19:36:44 bostic 18 17
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00109
d D 8.1 93/06/05 10:50:24 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00022/00094
d D 5.7 93/05/19 16:56:29 bostic 16 15
c lint
e
s 00004/00003/00112
d D 5.6 93/02/15 10:19:29 ralph 15 14
c change type of 'offset' to off_t to avoid truncation.
e
s 00002/00002/00113
d D 5.5 92/05/28 18:32:17 mckusick 14 13
c fix up includes
e
s 00003/00007/00112
d D 5.4 91/11/11 11:17:43 bostic 13 12
c break UFS up into FFS/UFS/LFS/MFS
e
s 00000/00002/00119
d D 5.3 91/06/29 23:12:12 bostic 12 11
c don't need sys/time.h or sys/vnode.h
e
s 00001/00001/00120
d D 5.2 90/06/11 14:54:42 bostic 11 10
c fix copyright
e
s 00098/00079/00023
d D 5.1 90/06/04 14:00:14 mckusick 10 9
c non-AT&T version from Rich Salz
e
s 00001/00003/00101
d D 2.6 90/05/04 13:53:11 mckusick 9 8
c delete unneeded headers
e
s 00004/00002/00100
d D 2.5 89/07/30 10:42:20 bostic 8 7
c vnodes
e
s 00000/00006/00102
d D 2.4 89/05/11 13:51:28 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00005/00003/00103
d D 2.3 87/02/23 17:39:46 mckusick 6 5
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00004/00000/00102
d D 2.2 82/04/11 17:36:00 mckusick 5 4
c minor changes to use "simfs"
e
s 00007/00002/00095
d D 2.1 82/04/08 15:39:43 mckusick 4 3
c merge into the new kernel
e
s 00003/00003/00094
d D 1.3 82/01/12 22:17:35 mckusic 3 2
c change all macros taking "fs" to have it as their first argument
e
s 00036/00023/00061
d D 1.2 82/01/06 23:31:57 mckusic 2 1
c convert to new file system format
e
s 00084/00000/00000
d D 1.1 82/01/06 21:38:43 mckusick 1 0
c date and time created 82/01/06 21:38:43 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1981 Regents of the University of California */

E 4
D 10
static char sccsid[] = "%Z%%M% %I% %G%";
E 10
I 10
/*
D 17
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
D 11
 * Rich Salz.
E 11
I 11
 * Rich $alz of BBN Inc.
E 11
 *
 * %sccs.include.redist.c%
 */
E 10

D 2
static char *sccsid = "@(#)clri.c	4.1 (Berkeley) 10/1/80";
E 2
I 2
D 10
/* static char *sccsid = "@(#)clri.c	4.1 (Berkeley) 10/1/80"; */
E 10
I 10
#ifndef lint
D 17
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 17
I 17
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 17
#endif /* not lint */
E 10
I 4

I 10
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 10
E 4
E 2
D 13
/*
D 10
 * clri filsys inumber ...
E 10
I 10
 * clri(8)
E 10
 */

E 13
I 4
D 7
#ifndef SIMFS
E 7
#include <sys/param.h>
D 8
#include <sys/inode.h>
#include <sys/fs.h>
E 8
I 8
D 9
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 9
I 9
D 10
#include <ufs/dinode.h>
E 10
I 10
D 12
#include <sys/time.h>
#include <sys/vnode.h>
E 12
D 13
#include <ufs/quota.h>
#include <ufs/inode.h>
E 10
E 9
#include <ufs/fs.h>
E 13
I 13
D 14
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 14
I 14
#include <sys/time.h>
I 16

E 16
#include <ufs/ufs/dinode.h>
E 14
#include <ufs/ffs/fs.h>
E 13
I 10
D 16
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
E 16
I 16

#include <err.h>
E 16
#include <errno.h>
I 16
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
E 16
E 10
E 8
D 7
#else
E 4
D 2
#include <sys/param.h>
#include <sys/ino.h>
E 2
I 2
#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"
I 4
#endif
E 7
E 4
E 2

D 10
#define ISIZE	(sizeof(struct dinode))
D 2
#define	NI	(BSIZE/ISIZE)
struct	ino
{
E 2
I 2
#define	NI	(MAXBSIZE/ISIZE)
struct	ino {
E 2
	char	junk[ISIZE];
};
struct	ino	buf[NI];
E 10
I 10
D 16
char *fs;
E 10
I 2

E 16
I 16
int
E 16
D 10
union {
	char		dummy[SBSIZE];
	struct fs	sblk;
} sb_un;
#define sblock sb_un.sblk

E 2
int	status;
I 6
long	dev_bsize = 1;
E 6

E 10
main(argc, argv)
D 2
char *argv[];
E 2
I 2
	int argc;
D 10
	char *argv[];
E 10
I 10
D 16
	char **argv;
E 16
I 16
	char *argv[];
E 16
E 10
E 2
{
D 10
	register i, f;
	unsigned n;
	int j, k;
	long off;
E 10
I 10
	register struct fs *sbp;
	register struct dinode *ip;
	register int fd;
	struct dinode ibuf[MAXBSIZE / sizeof (struct dinode)];
D 15
	long generation, offset, bsize;
E 15
I 15
	long generation, bsize;
	off_t offset;
E 15
	int inonum;
D 16
	char sblock[SBSIZE];
E 16
I 16
	char *fs, sblock[SBSIZE];
E 16
E 10

D 2
	if(argc < 3) {
E 2
I 2
	if (argc < 3) {
E 2
D 10
		printf("usage: clri filsys inumber ...\n");
		exit(4);
E 10
I 10
		(void)fprintf(stderr, "usage: clri filesystem inode ...\n");
		exit(1);
E 10
	}
D 10
	f = open(argv[1], 2);
D 2
	if(f < 0) {
E 2
I 2
	if (f < 0) {
E 2
		printf("cannot open %s\n", argv[1]);
		exit(4);
E 10
I 10

	fs = *++argv;

	/* get the superblock. */
	if ((fd = open(fs, O_RDWR, 0)) < 0)
D 16
		error();
E 16
I 16
		err(1, "%s", fs);
E 16
D 15
	if (lseek(fd, SBLOCK * DEV_BSIZE, SEEK_SET) < 0)
E 15
I 15
	if (lseek(fd, (off_t)(SBLOCK * DEV_BSIZE), SEEK_SET) < 0)
E 15
D 16
		error();
E 16
I 16
		err(1, "%s", fs);
E 16
D 19
	if (read(fd, sblock, sizeof(sblock)) != sizeof(sblock)) {
		(void)fprintf(stderr,
		    "clri: %s: can't read the superblock.\n", fs);
		exit(1);
E 10
	}
E 19
I 19
	if (read(fd, sblock, sizeof(sblock)) != sizeof(sblock))
		errx(1, "%s: can't read superblock", fs);
E 19
D 2
	for(i=2; i<argc; i++) {
		if(!isnumber(argv[i])) {
E 2
I 2
D 6
	lseek(f, SBLOCK * DEV_BSIZE, 0);
E 6
I 6
D 10
	lseek(f, SBOFF, 0);
E 6
	if (read(f, &sblock, SBSIZE) != SBSIZE) {
		printf("cannot read %s\n", argv[1]);
		exit(4);
E 10
I 10

	sbp = (struct fs *)sblock;
D 19
	if (sbp->fs_magic != FS_MAGIC) {
		(void)fprintf(stderr,
		    "clri: %s: superblock magic number 0x%x, not 0x%x.\n",
E 19
I 19
	if (sbp->fs_magic != FS_MAGIC)
		errx(1, "%s: superblock magic number 0x%x, not 0x%x",
E 19
		    fs, sbp->fs_magic, FS_MAGIC);
D 19
		exit(1);
E 10
	}
E 19
I 5
D 10
	if (sblock.fs_magic != FS_MAGIC) {
		printf("bad super block magic number\n");
		exit(4);
	}
I 6
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
E 6
E 5
	for (i = 2; i < argc; i++) {
		if (!isnumber(argv[i])) {
E 2
			printf("%s: is not a number\n", argv[i]);
			status = 1;
			continue;
E 10
I 10
	bsize = sbp->fs_bsize;

	/* remaining arguments are inode numbers. */
	while (*++argv) {
		/* get the inode number. */
D 19
		if ((inonum = atoi(*argv)) <= 0) {
			(void)fprintf(stderr,
			    "clri: %s is not a valid inode number.\n", *argv);
			exit(1);
E 10
		}
E 19
I 19
		if ((inonum = atoi(*argv)) <= 0)
			errx(1, "%s is not a valid inode number", *argv);
E 19
D 10
		n = atoi(argv[i]);
D 2
		if(n == 0) {
E 2
I 2
		if (n == 0) {
E 2
			printf("%s: is zero\n", argv[i]);
			status = 1;
			continue;
		}
D 2
		off = itod(n) * BSIZE;
E 2
I 2
D 3
		off = fsbtodb(&sblock, itod(n, &sblock)) * DEV_BSIZE;
E 3
I 3
D 6
		off = fsbtodb(&sblock, itod(&sblock, n)) * DEV_BSIZE;
E 6
I 6
		off = fsbtodb(&sblock, itod(&sblock, n)) * dev_bsize;
E 6
E 3
E 2
		lseek(f, off, 0);
D 2
		if(read(f, (char *)buf, BSIZE) != BSIZE) {
E 2
I 2
		if (read(f, (char *)buf, sblock.fs_bsize) != sblock.fs_bsize) {
E 2
			printf("%s: read error\n", argv[i]);
			status = 1;
		}
E 10
I 10
		(void)printf("clearing %d\n", inonum);

		/* read in the appropriate block. */
D 18
		offset = itod(sbp, inonum);	/* inode to fs block */
		offset = fsbtodb(sbp, offset);	/* fs block to disk block */
		offset *= DEV_BSIZE;		/* disk block to disk bytes */
E 18
I 18
		offset = ino_to_fsba(sbp, inonum);	/* inode to fs blk */
		offset = fsbtodb(sbp, offset);		/* fs blk disk blk */
		offset *= DEV_BSIZE;			/* disk blk to bytes */
E 18

		/* seek and read the block */
		if (lseek(fd, offset, SEEK_SET) < 0)
D 16
			error();
		if (read(fd, (char *)ibuf, bsize) != bsize)
			error();
E 16
I 16
			err(1, "%s", fs);
		if (read(fd, ibuf, bsize) != bsize)
			err(1, "%s", fs);
E 16

		/* get the inode within the block. */
D 18
		ip = &ibuf[itoo(sbp, inonum)];
E 18
I 18
		ip = &ibuf[ino_to_fsbo(sbp, inonum)];
E 18

		/* clear the inode, and bump the generation count. */
		generation = ip->di_gen + 1;
D 16
		bzero((char *)ip, sizeof *ip);
E 16
I 16
		memset(ip, 0, sizeof(*ip));
E 16
		ip->di_gen = generation;

		/* backup and write the block */
D 15
		if (lseek(fd, -bsize, SEEK_CUR) < 0)
E 15
I 15
		if (lseek(fd, (off_t)-bsize, SEEK_CUR) < 0)
E 15
D 16
			error();
		if (write(fd, (char *)ibuf, bsize) != bsize)
			error();
E 16
I 16
			err(1, "%s", fs);
		if (write(fd, ibuf, bsize) != bsize)
			err(1, "%s", fs);
E 16
		(void)fsync(fd);
E 10
	}
D 2
	if(status)
E 2
I 2
D 10
	if (status)
E 2
		exit(status);
D 2
	for(i=2; i<argc; i++) {
E 2
I 2
	for (i = 2; i < argc; i++) {
E 2
		n = atoi(argv[i]);
		printf("clearing %u\n", n);
D 2
		off = itod(n) * BSIZE;
E 2
I 2
D 3
		off = fsbtodb(&sblock, itod(n, &sblock)) * DEV_BSIZE;
E 3
I 3
D 6
		off = fsbtodb(&sblock, itod(&sblock, n)) * DEV_BSIZE;
E 6
I 6
		off = fsbtodb(&sblock, itod(&sblock, n)) * dev_bsize;
E 6
E 3
E 2
		lseek(f, off, 0);
D 2
		read(f, (char *)buf, BSIZE);
		j = itoo(n);
		for(k=0; k<ISIZE; k++)
E 2
I 2
		read(f, (char *)buf, sblock.fs_bsize);
D 3
		j = itoo(n, &sblock);
E 3
I 3
		j = itoo(&sblock, n);
E 3
		for (k = 0; k < ISIZE; k++)
E 2
			buf[j].junk[k] = 0;
		lseek(f, off, 0);
D 2
		write(f, (char *)buf, BSIZE);
E 2
I 2
		write(f, (char *)buf, sblock.fs_bsize);
E 2
	}
	exit(status);
E 10
I 10
	(void)close(fd);
	exit(0);
E 10
D 16
}

D 10
isnumber(s)
D 2
char *s;
E 2
I 2
	char *s;
E 10
I 10
error()
E 10
E 2
{
D 10
	register c;

	while(c = *s++)
D 2
		if(c < '0' || c > '9')
E 2
I 2
		if (c < '0' || c > '9')
E 2
			return(0);
	return(1);
E 10
I 10
	(void)fprintf(stderr, "clri: %s: %s\n", fs, strerror(errno));
	exit(1);
E 16
E 10
}
E 1
