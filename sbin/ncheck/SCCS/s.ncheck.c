h33249
s 00005/00005/00482
d D 8.1 93/06/05 11:05:47 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00485
d D 5.18 93/02/15 10:42:39 ralph 32 31
c use unistd.h to declare lseek properly.
e
s 00003/00002/00485
d D 5.17 93/01/15 16:05:38 hibler 31 30
c make it work again
e
s 00001/00000/00486
d D 5.16 92/05/28 18:40:48 mckusick 30 29
c need to include <sys/time.h> for <ufs/ufs/dinode.h>
e
s 00041/00034/00445
d D 5.15 92/03/19 21:54:25 bostic 29 28
c minor fix to argument parsing
c SBSIZE > sizeof(struct fs), was overwriting local varables in bread()
c from Craig Leres
e
s 00002/00002/00477
d D 5.14 91/11/11 11:35:28 bostic 28 27
c break UFS up into FFS/UFS/LFS/MFS
e
s 00008/00007/00471
d D 5.13 91/04/20 14:44:28 bostic 27 26
c new copyright; att/bsd/shared
e
s 00001/00003/00477
d D 5.12 90/05/04 12:47:11 mckusick 26 25
c delete unneeded headers
e
s 00001/00000/00479
d D 5.11 90/04/09 16:33:54 bostic 25 24
c check more than a single file system
e
s 00001/00001/00478
d D 5.10 90/02/20 16:11:31 bostic 24 23
c typo
e
s 00061/00038/00418
d D 5.9 90/01/30 18:00:08 mckusick 23 22
c lint; try small reads on error (4.3BSD-tahoe/sbin/5)
e
s 00004/00002/00452
d D 5.8 89/07/30 10:56:00 bostic 22 21
c vnodes
e
s 00031/00019/00423
d D 5.7 88/05/02 16:51:26 mckusick 21 20
c convert to understand dynamic file systems
e
s 00004/00002/00438
d D 5.6 87/02/23 17:39:59 mckusick 20 19
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00066/00011/00374
d D 5.5 86/12/01 19:27:06 bostic 19 17
c indirect block in a directory; bug report 4.3BSD/etc/23
e
s 00001/00001/00384
d R 5.5 86/11/18 21:05:28 bostic 18 17
c bug report 4.3BSD/etc/23
e
s 00002/00001/00383
d D 5.4 86/01/09 20:51:56 mckusick 17 16
c readdir is incorrectly implemented (from Chris Torek)
e
s 00016/00008/00368
d D 5.3 85/10/08 18:42:08 mckusick 16 15
c make HSIZE dynamic
e
s 00001/00001/00375
d D 5.2 85/09/24 16:16:11 bloom 15 14
c increase HSIZE (from blia!eric)
e
s 00015/00002/00361
d D 5.1 85/05/28 15:01:48 dist 14 13
c Add copyright
e
s 00001/00001/00362
d D 2.4 83/09/22 15:16:14 mosher 13 12
c increase HSIZE by factor of 2 - dm
e
s 00003/00007/00360
d D 2.3 83/07/01 03:19:06 sam 12 11
c include fix
e
s 00001/00001/00366
d D 2.2 82/09/10 00:45:32 mckusick 11 10
c ndir.h reverts to dir.h
e
s 00063/00029/00304
d D 2.1 82/04/08 15:29:28 mckusick 10 9
c add fixes per Jim Reeds, add -m flag to print out file modes
e
s 00002/00002/00331
d D 1.8 82/02/25 14:48:49 mckusic 9 8
c use speed-up macros in fs.h
e
s 00079/00075/00254
d D 1.7 82/02/23 22:48:02 mckusic 8 7
c convert to new directory format
e
s 00003/00003/00326
d D 1.6 82/01/12 22:21:22 mckusic 7 6
c change all macros taking "fs" to have it as their first argument
e
s 00002/00002/00327
d D 1.5 82/01/06 23:34:51 mckusic 6 5
c incorporate fs.h -r1.10, and param.h -r1.8 reorganization
e
s 00020/00018/00309
d D 1.4 82/01/05 01:33:56 mckusic 5 4
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00030/00012/00297
d D 1.3 81/09/22 21:55:49 mckusic 4 2
c allow files and directories to have FRAGS as their final block
e
s 00001/00001/00308
d R 1.3 81/09/22 21:24:11 mckusic 3 2
c allow files and directories to have FRAGS as their final block
e
s 00007/00008/00302
d D 1.2 81/08/28 21:22:34 mckusic 2 1
c put in new inode structure
e
s 00310/00000/00000
d D 1.1 81/08/26 23:47:55 mckusick 1 0
c date and time created 81/08/26 23:47:55 by mckusick
e
u
U
t
T
I 14
D 27
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 27
I 27
/*-
D 33
 * Copyright (c) 1988, 1990 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
 * %sccs.include.proprietary.c%
E 27
 */

E 14
I 12
#ifndef lint
E 12
I 1
D 14
static	char *sccsid = "%W% (Berkeley) %G%";
I 12
#endif
E 14
I 14
D 33
char copyright[] =
D 27
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 27
I 27
"%Z% Copyright (c) 1988, 1990 The Regents of the University of California.\n\
E 27
 All rights reserved.\n";
E 33
I 33
static char copyright[] =
"%Z% Copyright (c) 1988, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 33
D 27
#endif not lint
E 27
I 27
#endif /* not lint */
E 27

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 27
#endif not lint
E 27
I 27
#endif /* not lint */
E 27

E 14
E 12
/*
 * ncheck -- obtain file names from reading filesystem
 */

D 5
#define	NB	500
#define	HSIZE	2503
#define	NDIR	(BSIZE/sizeof(struct direct))
E 5
I 5
#define	NB		500
D 13
#define	HSIZE		2503
E 13
I 13
D 15
#define	HSIZE		5651
E 15
I 15
D 16
#define	HSIZE		20011
E 16
E 15
E 13
D 8
#define	NDIR(fs)	((fs)->fs_bsize/sizeof(struct direct))
#define	MAXNDIR		(MAXBSIZE/sizeof(struct direct))
E 8
D 6
#define	MAXNINDIR	(MAXBSIZE/sizeof(daddr_t))
E 6
I 6
#define	MAXNINDIR	(MAXBSIZE / sizeof (daddr_t))
E 6
E 5

I 31
#include <unistd.h>
E 31
I 10
D 12
#ifndef SIMFS
E 12
#include <sys/param.h>
D 22
#include <sys/inode.h>
#include <sys/fs.h>
E 22
I 22
D 24
#include <sys/time.h
E 24
I 24
D 26
#include <sys/time.h>
E 24
#include <sys/vnode.h>
#include <ufs/inode.h>
E 26
I 26
D 28
#include <ufs/dinode.h>
E 26
#include <ufs/fs.h>
E 28
E 22
D 12
#else
E 10
D 8
#include <stdio.h>
E 8
#include "../h/param.h"
#include "../h/inode.h"
D 2
#include "../h/ino.h"
E 2
D 8
#include "../h/dir.h"
E 8
#include "../h/fs.h"
I 10
#endif
E 12
I 12
#include <sys/dir.h>
I 30
#include <sys/time.h>
E 30
I 28
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
E 28
E 12
E 10
I 8
#include <stdio.h>
D 11
#include <ndir.h>
E 11
I 11
D 12
#include <dir.h>
E 12
E 11
E 8

D 29
struct	fs	sblock;
E 29
I 29
struct	fs	*sblockp;
E 29
D 21
struct	dinode	itab[MAXIPG];
E 21
I 21
struct	dinode	itab[MAXBSIZE/sizeof(struct dinode)];
E 21
D 2
daddr_t	iaddr[NDADDR+NIADDR];
E 2
I 2
D 29
struct 	dinode	*gip;
E 29
I 29
struct	dinode	*gip;
E 29
E 2
D 10
ino_t	ilist[NB];
E 10
I 10
struct ilist {
	ino_t	ino;
	u_short	mode;
	short	uid;
	short	gid;
} ilist[NB];
E 10
struct	htab
{
	ino_t	h_ino;
	ino_t	h_pino;
D 8
	char	h_name[DIRSIZ];
E 8
I 8
	char	*h_name;
E 8
D 16
} htab[HSIZE];
I 8
char strngtab[30 * HSIZE];
E 16
I 16
} *htab;
char *strngtab;
long hsize;
E 16
int strngloc;
E 8

I 8
struct dirstuff {
	int loc;
	struct dinode *ip;
	char dbuf[MAXBSIZE];
};

E 8
int	aflg;
int	sflg;
I 10
int	iflg; /* number of inodes being searched for */
int	mflg;
E 10
int	fi;
ino_t	ino;
int	nhent;
int	nxfile;
I 20
D 23
long	dev_bsize = 1;
E 23
I 23
int	dev_bsize = 1;
E 23
E 20

int	nerror;
daddr_t	bmap();
long	atol();
I 23
D 32
off_t	lseek();
E 32
char	*malloc(), *strcpy();
E 23
struct htab *lookup();
I 23
struct direct *nreaddir();
E 23

main(argc, argv)
D 4
char *argv[];
E 4
I 4
	int argc;
	char *argv[];
E 4
{
D 23
	register i;
E 23
	long n;

	while (--argc) {
		argv++;
		if (**argv=='-')
		switch ((*argv)[1]) {

		case 'a':
			aflg++;
			continue;

		case 'i':
D 10
			for(i=0; i<NB; i++) {
E 10
I 10
D 29
			for(iflg=0; iflg<NB; iflg++) {
E 29
I 29
			for(iflg=0; iflg<NB && argc >= 2; iflg++) {
E 29
E 10
				n = atol(argv[1]);
				if(n == 0)
					break;
D 10
				ilist[i] = n;
				nxfile = i;
E 10
I 10
				ilist[iflg].ino = n;
				nxfile = iflg;
E 10
				argv++;
				argc--;
			}
			continue;

I 10
		case 'm':
			mflg++;
			continue;

E 10
		case 's':
			sflg++;
			continue;

		default:
D 23
			fprintf(stderr, "ncheck: bad flag %c\n", (*argv)[1]);
E 23
I 23
			(void) fprintf(stderr, "ncheck: bad flag %c\n",
			    (*argv)[1]);
E 23
			nerror++;
		}
		check(*argv);
	}
	return(nerror);
}

check(file)
D 4
char *file;
E 4
I 4
	char *file;
E 4
{
D 4
	register i, j, c;
E 4
I 4
	register int i, j, c;
D 23
	int nfiles;
E 23
E 4

	fi = open(file, 0);
	if(fi < 0) {
D 23
		fprintf(stderr, "ncheck: cannot open %s\n", file);
E 23
I 23
		(void) fprintf(stderr, "ncheck: cannot open %s\n", file);
E 23
		nerror++;
		return;
	}
	nhent = 0;
D 23
	printf("%s:\n", file);
E 23
I 23
	(void) printf("%s:\n", file);
E 23
	sync();
I 25
	dev_bsize = 1;
E 25
D 5
	bread(SBLOCK, (char *)&sblock, sizeof(sblock));
E 5
I 5
D 6
	bread(SBLOCK, (char *)&sblock, MAXBSIZE);
E 6
I 6
D 20
	bread(SBLOCK, (char *)&sblock, SBSIZE);
E 20
I 20
D 23
	bread(SBOFF, (char *)&sblock, SBSIZE);
E 23
I 23
D 29
	bread(SBOFF, (char *)&sblock, (long)SBSIZE);
E 23
E 20
E 6
E 5
I 4
	if (sblock.fs_magic != FS_MAGIC) {
E 29
I 29
	sblockp = (struct fs *)malloc((unsigned)SBSIZE);
	if (sblockp == 0) {
		(void) printf("icheck: couldn't malloc superblock memory\n");
		nerror++;
		return;
	}
D 31
	bread(SBOFF, (char *)sblockp, (long)SBSIZE);
E 31
I 31
	bread((daddr_t)SBOFF, (char *)sblockp, (long)SBSIZE);
E 31
	if (sblockp->fs_magic != FS_MAGIC) {
E 29
D 23
		printf("%s: not a file system\n", file);
E 23
I 23
		(void) printf("%s: not a file system\n", file);
E 23
		nerror++;
		return;
	}
I 20
D 29
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
E 20
I 16
	hsize = sblock.fs_ipg * sblock.fs_ncg - sblock.fs_cstotal.cs_nifree + 1;
E 29
I 29
	dev_bsize = sblockp->fs_fsize / fsbtodb(sblockp, 1);
	hsize = sblockp->fs_ipg * sblockp->fs_ncg -
	    sblockp->fs_cstotal.cs_nifree + 1;
E 29
D 23
	htab = (struct htab *)malloc(hsize * sizeof(struct htab));
	strngtab = (char *)malloc(30 * hsize);
E 23
I 23
	htab = (struct htab *)malloc((unsigned)hsize * sizeof(struct htab));
	strngtab = malloc((unsigned)(30 * hsize));
E 23
	if (htab == 0 || strngtab == 0) {
D 23
		printf("not enough memory to allocate tables\n");
E 23
I 23
		(void) printf("not enough memory to allocate tables\n");
E 23
		nerror++;
		return;
	}
E 16
D 10
	nfiles = sblock.fs_ipg * sblock.fs_ncg;
	if (nfiles > 65535) {
		printf("%s: %d is a preposterous number of files\n",
		    file, nfiles);
		nerror++;
		return;
	}
E 10
E 4
	ino = 0;
D 29
	for (c = 0; c < sblock.fs_ncg; c++) {
E 29
I 29
	for (c = 0; c < sblockp->fs_ncg; c++) {
E 29
D 5
		bread(cgimin(c, &sblock), (char *)itab,
E 5
I 5
D 7
		bread(fsbtodb(&sblock, cgimin(c, &sblock)), (char *)itab,
E 7
I 7
D 21
		bread(fsbtodb(&sblock, cgimin(&sblock, c)), (char *)itab,
E 7
E 5
		    sblock.fs_ipg * sizeof (struct dinode));
D 10
		for(j=0; j<sblock.fs_ipg; j++) {
			pass1(&itab[j]);
E 10
I 10
		for(j = 0; j < sblock.fs_ipg; j++) {
			if (itab[j].di_mode != 0)
				pass1(&itab[j]);
E 10
			ino++;
E 21
I 21
		for (i = 0;
D 29
		     i < sblock.fs_ipg / INOPF(&sblock);
		     i += sblock.fs_frag) {
			bread(fsbtodb(&sblock, cgimin(&sblock, c) + i),
			    (char *)itab, sblock.fs_bsize);
			for (j = 0; j < INOPB(&sblock); j++) {
E 29
I 29
		     i < sblockp->fs_ipg / INOPF(sblockp);
		     i += sblockp->fs_frag) {
			bread(fsbtodb(sblockp, cgimin(sblockp, c) + i),
			    (char *)itab, sblockp->fs_bsize);
			for (j = 0; j < INOPB(sblockp); j++) {
E 29
				if (itab[j].di_mode != 0)
					pass1(&itab[j]);
				ino++;
			}
E 21
		}
	}
D 10
	ilist[nxfile+1] = 0;
E 10
I 10
	ilist[nxfile+1].ino = 0;
E 10
	ino = 0;
D 29
	for (c = 0; c < sblock.fs_ncg; c++) {
E 29
I 29
	for (c = 0; c < sblockp->fs_ncg; c++) {
E 29
D 5
		bread(cgimin(c, &sblock), (char *)itab,
E 5
I 5
D 7
		bread(fsbtodb(&sblock, cgimin(c, &sblock)), (char *)itab,
E 7
I 7
D 21
		bread(fsbtodb(&sblock, cgimin(&sblock, c)), (char *)itab,
E 7
E 5
		    sblock.fs_ipg * sizeof (struct dinode));
D 10
		for(j=0; j<sblock.fs_ipg; j++) {
			pass2(&itab[j]);
E 10
I 10
		for(j = 0; j < sblock.fs_ipg; j++) {
			if (itab[j].di_mode != 0)
				pass2(&itab[j]);
E 10
			ino++;
E 21
I 21
		for (i = 0;
D 29
		     i < sblock.fs_ipg / INOPF(&sblock);
		     i += sblock.fs_frag) {
			bread(fsbtodb(&sblock, cgimin(&sblock, c) + i),
			    (char *)itab, sblock.fs_bsize);
			for (j = 0; j < INOPB(&sblock); j++) {
E 29
I 29
		     i < sblockp->fs_ipg / INOPF(sblockp);
		     i += sblockp->fs_frag) {
			bread(fsbtodb(sblockp, cgimin(sblockp, c) + i),
			    (char *)itab, sblockp->fs_bsize);
			for (j = 0; j < INOPB(sblockp); j++) {
E 29
				if (itab[j].di_mode != 0)
					pass2(&itab[j]);
				ino++;
			}
E 21
		}
	}
	ino = 0;
D 29
	for (c = 0; c < sblock.fs_ncg; c++) {
E 29
I 29
	for (c = 0; c < sblockp->fs_ncg; c++) {
E 29
D 5
		bread(cgimin(c, &sblock), (char *)itab,
E 5
I 5
D 7
		bread(fsbtodb(&sblock, cgimin(c, &sblock)), (char *)itab,
E 7
I 7
D 21
		bread(fsbtodb(&sblock, cgimin(&sblock, c)), (char *)itab,
E 7
E 5
		    sblock.fs_ipg * sizeof (struct dinode));
D 10
		for(j=0; j<sblock.fs_ipg; j++) {
			pass3(&itab[j]);
E 10
I 10
		for(j = 0; j < sblock.fs_ipg; j++) {
			if (itab[j].di_mode != 0)
				pass3(&itab[j]);
E 10
			ino++;
E 21
I 21
		for (i = 0;
D 29
		     i < sblock.fs_ipg / INOPF(&sblock);
		     i += sblock.fs_frag) {
			bread(fsbtodb(&sblock, cgimin(&sblock, c) + i),
			    (char *)itab, sblock.fs_bsize);
			for (j = 0; j < INOPB(&sblock); j++) {
E 29
I 29
		     i < sblockp->fs_ipg / INOPF(sblockp);
		     i += sblockp->fs_frag) {
			bread(fsbtodb(sblockp, cgimin(sblockp, c) + i),
			    (char *)itab, sblockp->fs_bsize);
			for (j = 0; j < INOPB(sblockp); j++) {
E 29
				if (itab[j].di_mode != 0)
					pass3(&itab[j]);
				ino++;
			}
E 21
		}
	}
I 10
D 23
	close(fi);
E 23
I 23
	(void) close(fi);
E 23
D 16
	for (i = 0; i < HSIZE; i++)
E 16
I 16
	for (i = 0; i < hsize; i++)
E 16
		htab[i].h_ino = 0;
	for (i = iflg; i < NB; i++)
		ilist[i].ino = 0;
	nxfile = iflg;
E 10
}

pass1(ip)
D 4
register struct dinode *ip;
E 4
I 4
	register struct dinode *ip;
E 4
{
D 10
	if((ip->di_mode & IFMT) != IFDIR) {
E 10
I 10
	int i;

	if (mflg)
		for (i = 0; i < iflg; i++)
			if (ino == ilist[i].ino) {
				ilist[i].mode = ip->di_mode;
				ilist[i].uid = ip->di_uid;
				ilist[i].gid = ip->di_gid;
			}
	if ((ip->di_mode & IFMT) != IFDIR) {
E 10
		if (sflg==0 || nxfile>=NB)
			return;
		if ((ip->di_mode&IFMT)==IFBLK || (ip->di_mode&IFMT)==IFCHR
D 10
		  || ip->di_mode&(ISUID|ISGID))
			ilist[nxfile++] = ino;
E 10
I 10
		  || ip->di_mode&(ISUID|ISGID)) {
			ilist[nxfile].ino = ino;
			ilist[nxfile].mode = ip->di_mode;
			ilist[nxfile].uid = ip->di_uid;
			ilist[nxfile++].gid = ip->di_gid;
E 10
			return;
I 10
		}
E 10
	}
D 23
	lookup(ino, 1);
E 23
I 23
	(void) lookup(ino, 1);
E 23
}

pass2(ip)
D 4
register struct dinode *ip;
E 4
I 4
	register struct dinode *ip;
E 4
{
D 5
	struct direct dbuf[NDIR];
E 5
I 5
D 8
	struct direct dbuf[MAXNDIR];
E 5
	long doff;
	struct direct *dp;
	register i, j;
	int k;
E 8
I 8
	register struct direct *dp;
	struct dirstuff dirp;
E 8
	struct htab *hp;
D 8
	daddr_t d;
	ino_t kno;
E 8

	if((ip->di_mode&IFMT) != IFDIR)
		return;
I 8
	dirp.loc = 0;
	dirp.ip = ip;
E 8
D 2
	l3tol(iaddr, ip->di_addr, NDADDR);
E 2
I 2
	gip = ip;
E 2
D 8
	doff = 0;
	for(i=0;; i++) {
		if(doff >= ip->di_size)
			break;
		d = bmap(i);
		if(d == 0)
			break;
D 5
		bread(d, (char *)dbuf, sizeof(dbuf));
		for(j=0; j<NDIR; j++) {
E 5
I 5
		bread(fsbtodb(&sblock, d), (char *)dbuf, sizeof(dbuf));
		for(j=0; j < NDIR(&sblock); j++) {
E 5
			if(doff >= ip->di_size)
				break;
			doff += sizeof(struct direct);
			dp = dbuf+j;
			kno = dp->d_ino;
			if(kno == 0)
				continue;
			hp = lookup(kno, 0);
			if(hp == 0)
				continue;
			if(dotname(dp))
				continue;
			hp->h_pino = ino;
			for(k=0; k<DIRSIZ; k++)
				hp->h_name[k] = dp->d_name[k];
		}
E 8
I 8
D 23
	for (dp = readdir(&dirp); dp != NULL; dp = readdir(&dirp)) {
E 23
I 23
	for (dp = nreaddir(&dirp); dp != NULL; dp = nreaddir(&dirp)) {
E 23
		if(dp->d_ino == 0)
			continue;
		hp = lookup(dp->d_ino, 0);
		if(hp == 0)
			continue;
		if(dotname(dp))
			continue;
		hp->h_pino = ino;
		hp->h_name = &strngtab[strngloc];
		strngloc += strlen(dp->d_name) + 1;
D 23
		strcpy(hp->h_name, dp->d_name);
E 23
I 23
		(void) strcpy(hp->h_name, dp->d_name);
E 23
E 8
	}
}

pass3(ip)
D 4
register struct dinode *ip;
E 4
I 4
	register struct dinode *ip;
E 4
{
D 5
	struct direct dbuf[NDIR];
E 5
I 5
D 8
	struct direct dbuf[MAXNDIR];
E 5
	long doff;
	struct direct *dp;
	register i, j;
E 8
I 8
	register struct direct *dp;
	struct dirstuff dirp;
E 8
	int k;
D 8
	daddr_t d;
	ino_t kno;
E 8

	if((ip->di_mode&IFMT) != IFDIR)
		return;
I 8
	dirp.loc = 0;
	dirp.ip = ip;
E 8
D 2
	l3tol(iaddr, ip->di_addr, NDADDR);
E 2
I 2
	gip = ip;
E 2
D 8
	doff = 0;
	for(i=0;; i++) {
		if(doff >= ip->di_size)
			break;
		d = bmap(i);
		if(d == 0)
			break;
D 5
		bread(d, (char *)dbuf, sizeof(dbuf));
		for(j=0; j<NDIR; j++) {
E 5
I 5
		bread(fsbtodb(&sblock, d), (char *)dbuf, sizeof(dbuf));
		for(j=0; j < NDIR(&sblock); j++) {
E 5
			if(doff >= ip->di_size)
				break;
			doff += sizeof(struct direct);
			dp = dbuf+j;
			kno = dp->d_ino;
			if(kno == 0)
				continue;
			if(aflg==0 && dotname(dp))
				continue;
			if(ilist[0] == 0)
				goto pr;
			for(k=0; ilist[k] != 0; k++)
				if(ilist[k] == kno)
					goto pr;
E 8
I 8
D 23
	for(dp = readdir(&dirp); dp != NULL; dp = readdir(&dirp)) {
E 23
I 23
	for(dp = nreaddir(&dirp); dp != NULL; dp = nreaddir(&dirp)) {
E 23
D 10
		if(dp->d_ino == 0)
E 8
			continue;
E 10
D 8
		pr:
			printf("%u	", kno);
			pname(ino, 0);
			printf("/%.14s", dp->d_name);
			if (lookup(kno, 0))
				printf("/.");
			printf("\n");
E 8
I 8
		if(aflg==0 && dotname(dp))
			continue;
D 10
		if(ilist[0] == 0)
E 10
I 10
		if(sflg == 0 && iflg == 0)
E 10
			goto pr;
D 10
		for(k = 0; ilist[k] != 0; k++)
			if(ilist[k] == dp->d_ino)
				goto pr;
		continue;
E 10
I 10
		for(k = 0; ilist[k].ino != 0; k++)
			if(ilist[k].ino == dp->d_ino)
				break;
		if (ilist[k].ino == 0)
			continue;
		if (mflg)
D 23
			printf("mode %-6o uid %-5d gid %-5d ino ",
E 23
I 23
			(void) printf("mode %-6o uid %-5d gid %-5d ino ",
E 23
			    ilist[k].mode, ilist[k].uid, ilist[k].gid);
E 10
	pr:
D 10
		printf("%u	", dp->d_ino);
E 10
I 10
D 23
		printf("%-5u\t", dp->d_ino);
E 23
I 23
		(void) printf("%-5lu\t", dp->d_ino);
E 23
E 10
		pname(ino, 0);
D 23
		printf("/%s", dp->d_name);
E 23
I 23
		(void) printf("/%s", dp->d_name);
E 23
		if (lookup(dp->d_ino, 0))
D 23
			printf("/.");
		printf("\n");
E 23
I 23
			(void) printf("/.");
		(void) printf("\n");
E 23
	}
}

/*
 * get next entry in a directory.
 */
struct direct *
D 23
readdir(dirp)
E 23
I 23
nreaddir(dirp)
E 23
	register struct dirstuff *dirp;
{
	register struct direct *dp;
	daddr_t lbn, d;

	for(;;) {
		if (dirp->loc >= dirp->ip->di_size)
			return NULL;
D 9
		if ((lbn = dirp->loc / sblock.fs_bsize) == 0) {
E 9
I 9
D 17
		if ((lbn = lblkno(&sblock, dirp->loc)) == 0) {
E 17
I 17
D 29
		if (blkoff(&sblock, dirp->loc) == 0) {
			lbn = lblkno(&sblock, dirp->loc);
E 29
I 29
		if (blkoff(sblockp, dirp->loc) == 0) {
			lbn = lblkno(sblockp, dirp->loc);
E 29
E 17
E 9
			d = bmap(lbn);
			if(d == 0)
				return NULL;
D 29
			bread(fsbtodb(&sblock, d), dirp->dbuf,
			    dblksize(&sblock, dirp->ip, lbn));
E 29
I 29
			bread(fsbtodb(sblockp, d), dirp->dbuf,
D 31
			    dblksize(sblockp, dirp->ip, lbn));
E 31
I 31
			      (long)dblksize(sblockp, dirp->ip, lbn));
E 31
E 29
E 8
		}
I 8
		dp = (struct direct *)
D 9
		    (dirp->dbuf + dirp->loc % sblock.fs_bsize);
E 9
I 9
D 29
		    (dirp->dbuf + blkoff(&sblock, dirp->loc));
E 29
I 29
		    (dirp->dbuf + blkoff(sblockp, dirp->loc));
E 29
E 9
		dirp->loc += dp->d_reclen;
		if (dp->d_ino == 0)
			continue;
		return (dp);
E 8
	}
}

dotname(dp)
D 4
register struct direct *dp;
E 4
I 4
	register struct direct *dp;
E 4
{

	if (dp->d_name[0]=='.')
D 8
		if (dp->d_name[1]==0 || (dp->d_name[1]=='.' && dp->d_name[2]==0))
E 8
I 8
		if (dp->d_name[1]==0 ||
		   (dp->d_name[1]=='.' && dp->d_name[2]==0))
E 8
			return(1);
	return(0);
}

pname(i, lev)
D 4
ino_t i;
E 4
I 4
	ino_t i;
	int lev;
E 4
{
	register struct htab *hp;

	if (i==ROOTINO)
		return;
	if ((hp = lookup(i, 0)) == 0) {
D 23
		printf("???");
E 23
I 23
		(void) printf("???");
E 23
		return;
	}
	if (lev > 10) {
D 23
		printf("...");
E 23
I 23
		(void) printf("...");
E 23
		return;
	}
	pname(hp->h_pino, ++lev);
D 8
	printf("/%.14s", hp->h_name);
E 8
I 8
D 23
	printf("/%s", hp->h_name);
E 23
I 23
	(void) printf("/%s", hp->h_name);
E 23
E 8
}

struct htab *
lookup(i, ef)
D 4
ino_t i;
E 4
I 4
	ino_t i;
	int ef;
E 4
{
	register struct htab *hp;

D 16
	for (hp = &htab[i%HSIZE]; hp->h_ino;) {
E 16
I 16
	for (hp = &htab[i%hsize]; hp->h_ino;) {
E 16
		if (hp->h_ino==i)
			return(hp);
D 16
		if (++hp >= &htab[HSIZE])
E 16
I 16
		if (++hp >= &htab[hsize])
E 16
			hp = htab;
	}
	if (ef==0)
		return(0);
D 16
	if (++nhent >= HSIZE) {
		fprintf(stderr, "ncheck: out of core-- increase HSIZE\n");
E 16
I 16
	if (++nhent >= hsize) {
D 23
		fprintf(stderr, "ncheck: hsize of %d is too small\n", hsize);
E 23
I 23
		(void) fprintf(stderr, "ncheck: hsize of %ld is too small\n",
		    hsize);
E 23
E 16
		exit(1);
	}
	hp->h_ino = i;
	return(hp);
}

D 23
bread(bno, buf, cnt)
E 23
I 23
bread(bno, buf, lcount)
E 23
D 4
daddr_t bno;
char *buf;
E 4
I 4
	daddr_t bno;
D 23
	char *buf;
	int cnt;
E 23
I 23
	register char *buf;
	long lcount;
E 23
E 4
{
D 23
	register i;
E 23
I 23
	register int i, cnt = lcount;
	register off_t off = bno * dev_bsize;
E 23

D 4
	lseek(fi, bno*BSIZE, 0);
E 4
I 4
D 5
	lseek(fi, bno*FSIZE, 0);
E 5
I 5
D 20
	lseek(fi, bno * DEV_BSIZE, 0);
E 20
I 20
D 23
	lseek(fi, bno * dev_bsize, 0);
E 23
I 23
D 32
	(void) lseek(fi, off, 0);
E 32
I 32
	(void) lseek(fi, off, SEEK_SET);
E 32
E 23
E 20
E 5
E 4
	if (read(fi, buf, cnt) != cnt) {
D 23
		fprintf(stderr, "ncheck: read error %d\n", bno);
D 5
		for(i=0; i<BSIZE; i++)
E 5
I 5
		for(i=0; i < cnt; i++)
E 5
			buf[i] = 0;
E 23
I 23
		(void) fprintf(stderr, "ncheck: read error %ld\n", bno);
		if (cnt % dev_bsize) {
			/* THIS INDICATES A SERIOUS BUG */
			/* bzero is probably not correct, but will do */
			(void) fprintf(stderr,
			    "ncheck: bread: cnt %d not multiple of %d\n",
			    cnt, dev_bsize);
			bzero(buf, cnt);
			return;
		}
		for (i = 0; i < cnt; i += dev_bsize) {
D 32
			(void) lseek(fi, off, 0);
E 32
I 32
			(void) lseek(fi, off, SEEK_SET);
E 32
			if (read(fi, buf, dev_bsize) != dev_bsize) {
				(void) fprintf(stderr,
				    "ncheck: re-read error %ld\n", bno);
				bzero(buf, dev_bsize);
			}
			off += dev_bsize;
			buf += dev_bsize;
			bno++;
		}
E 23
	}
}

I 19
/*
 * Swiped from standalone sys.c.
 */
#define	NBUFS	4
char	b[NBUFS][MAXBSIZE];
daddr_t	blknos[NBUFS];

E 19
daddr_t
D 19
bmap(i)
I 4
	int i;
E 19
I 19
bmap(bn)
	register daddr_t bn;
E 19
E 4
{
D 5
	daddr_t ibuf[NINDIR];
E 5
I 5
D 19
	daddr_t ibuf[MAXNINDIR];
E 19
I 19
	register int j;
	int i, sh;
	daddr_t nb, *bap;
E 19
E 5

D 2
	if(i < NDADDR-3)
		return(iaddr[i]);
	i -= NDADDR-3;
E 2
I 2
D 19
	if(i < NDADDR)
		return(gip->di_db[i]);
	i -= NDADDR;
E 2
D 5
	if(i > NINDIR) {
E 5
I 5
	if(i > NINDIR(&sblock)) {
E 5
		fprintf(stderr, "ncheck: %u - huge directory\n", ino);
		return((daddr_t)0);
E 19
I 19
	if (bn < 0) {
D 23
		fprintf(stderr, "ncheck: bn %d negative\n", bn);
E 23
I 23
		(void) fprintf(stderr, "ncheck: bn %ld negative\n", bn);
E 23
		return ((daddr_t)0);
E 19
	}
D 2
	bread(iaddr[NDADDR-3], (char *)ibuf, sizeof(ibuf));
E 2
I 2
D 5
	bread(gip->di_ib[i], (char *)ibuf, sizeof(ibuf));
E 5
I 5
D 19
	bread(fsbtodb(&sblock, gip->di_ib[i]), (char *)ibuf, sizeof(ibuf));
E 5
E 2
	return(ibuf[i]);
E 19
I 19

	/*
	 * blocks 0..NDADDR are direct blocks
	 */
	if(bn < NDADDR)
		return(gip->di_db[bn]);

	/*
	 * addresses NIADDR have single and double indirect blocks.
	 * the first step is to determine how many levels of indirection.
	 */
	sh = 1;
	bn -= NDADDR;
	for (j = NIADDR; j > 0; j--) {
D 29
		sh *= NINDIR(&sblock);
E 29
I 29
		sh *= NINDIR(sblockp);
E 29
		if (bn < sh)
			break;
		bn -= sh;
	}
	if (j == 0) {
D 23
		printf("ncheck: bn %ld ovf, ino %u\n", bn, ino);
E 23
I 23
		(void) printf("ncheck: bn %ld ovf, ino %lu\n", bn, ino);
E 23
		return ((daddr_t)0);
	}

	/*
	 * fetch the first indirect block address from the inode
	 */
	nb = gip->di_ib[NIADDR - j];
	if (nb == 0) {
D 23
		printf("ncheck: bn %ld void1, ino %u\n", bn, ino);
E 23
I 23
		(void) printf("ncheck: bn %ld void1, ino %lu\n", bn, ino);
E 23
		return ((daddr_t)0);
	}

	/*
	 * fetch through the indirect blocks
	 */
	for (; j <= NIADDR; j++) {
		if (blknos[j] != nb) {
D 29
			bread(fsbtodb(&sblock, nb), b[j], sblock.fs_bsize);
E 29
I 29
			bread(fsbtodb(sblockp, nb), b[j], sblockp->fs_bsize);
E 29
			blknos[j] = nb;
		}
		bap = (daddr_t *)b[j];
D 29
		sh /= NINDIR(&sblock);
		i = (bn / sh) % NINDIR(&sblock);
E 29
I 29
		sh /= NINDIR(sblockp);
		i = (bn / sh) % NINDIR(sblockp);
E 29
		nb = bap[i];
		if(nb == 0) {
D 23
			printf("ncheck: bn %ld void2, ino %u\n", bn, ino);
E 23
I 23
			(void) printf("ncheck: bn %ld void2, ino %lu\n", bn,
			    ino);
E 23
			return ((daddr_t)0);
		}
	}
	return (nb);
E 19
}
E 1
