h42629
s 00002/00002/00557
d D 8.3 95/05/04 16:59:17 mckusick 17 16
c di_?time is no longer a structure
e
s 00006/00004/00553
d D 8.2 93/09/23 19:37:39 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00552
d D 8.1 93/06/06 14:02:42 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00552
d D 5.10 92/06/18 18:26:51 bostic 14 13
c on-disk inode is now a timespec
e
s 00003/00002/00551
d D 5.9 92/06/18 17:38:53 bostic 13 12
c di_[acm]time are now struct timeval's
e
s 00002/00002/00551
d D 5.8 92/03/07 11:10:23 bostic 12 11
c break ufs up
e
s 00008/00007/00545
d D 5.7 91/04/19 13:48:01 bostic 11 10
c new copyright; att/bsd/shared
e
s 00062/00059/00490
d D 5.6 89/11/01 10:26:36 mckusick 10 9
c update to use dinode.h
e
s 00005/00003/00544
d D 5.5 89/07/30 11:10:33 bostic 9 8
c vnodes
e
s 00009/00008/00538
d D 5.4 88/05/31 17:54:04 mckusick 8 7
c convert to understand dynamic file systems
e
s 00016/00014/00530
d D 5.3 87/12/26 12:57:11 bostic 7 6
c fix declarations for ANSI C; minor lint cleanups
e
s 00006/00005/00538
d D 5.2 87/02/23 17:39:57 mckusick 6 5
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00013/00001/00530
d D 5.1 85/05/28 14:59:18 dist 5 4
c Add copyright
e
s 00003/00003/00528
d D 4.4 83/08/11 22:51:39 sam 4 3
c standardize sccs keyword lines
e
s 00004/00004/00527
d D 4.3 83/05/03 20:53:02 sam 3 2
c fix name conflict with kernel
e
s 00001/00001/00530
d D 4.2 82/10/13 17:29:44 mckusick 2 1
c fix creation of block and character devices
e
s 00531/00000/00000
d D 4.1 82/09/10 00:09:25 mckusick 1 0
c date and time created 82/09/10 00:09:25 by mckusick
e
u
U
t
T
I 5
D 11
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
/*-
D 15
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.proprietary.c%
E 11
 */

E 5
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */

static char sccsid[] = "%W%	(Berkeley)	%G%";
E 4
I 4
#ifndef lint
I 5
D 15
char copyright[] =
D 11
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11

#ifndef lint
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 5
E 4

/*
 * Make a file system prototype.
 * usage: mkproto filsys proto
 */
D 9
#include <stdio.h>
E 9
#include <sys/param.h>
I 13
#include <sys/time.h>
E 13
D 9
#include <sys/inode.h>
#include <sys/fs.h>
E 9
I 9
D 10
#include <sys/time.h>
#include <sys/vnode.h>
E 10
E 9
#include <sys/dir.h>
I 16

E 16
I 9
D 10
#include <ufs/inode.h>
E 10
I 10
D 12
#include <ufs/dinode.h>
E 10
#include <ufs/fs.h>
E 12
I 12
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
I 16

E 16
E 12
#include <stdio.h>
E 9

union {
	struct	fs fs;
	char	fsx[SBSIZE];
} ufs;
#define sblock	ufs.fs
union {
	struct	cg cg;
	char	cgx[MAXBSIZE];
} ucg;
#define	acg	ucg.cg
struct	fs *fs;
struct	csum *fscs;
int	fso, fsi;
FILE	*proto;
char	token[BUFSIZ];
int	errs;
I 6
long	dev_bsize = 1;
E 6
int	ino = 10;
long	getnum();
char	*strcpy();
I 10
ino_t	ialloc();
E 10

main(argc, argv)
	int argc;
	char *argv[];
{
	int i;
I 7
	char *calloc();
E 7

	if (argc != 3) {
		fprintf(stderr, "usage: mkproto filsys proto\n");
		exit(1);
	}
	fso = open(argv[1], 1);
	fsi = open(argv[1], 0);
	if (fso < 0 || fsi < 0) {
		perror(argv[1]);
		exit(1);
	}
	fs = &sblock;
D 6
	rdfs(SBLOCK, SBSIZE, (char *)fs);
E 6
I 6
	rdfs(SBOFF, SBSIZE, (char *)fs);
	dev_bsize = fs->fs_fsize / fsbtodb(fs, 1);
E 6
D 7
	fscs = (struct csum *)calloc(1, fs->fs_cssize);
E 7
I 7
	fscs = (struct csum *)calloc(1, (u_int)fs->fs_cssize);
E 7
	for (i = 0; i < fs->fs_cssize; i += fs->fs_bsize)
		rdfs(fsbtodb(fs, fs->fs_csaddr + numfrags(fs, i)),
			(int)(fs->fs_cssize - i < fs->fs_bsize ?
			    fs->fs_cssize - i : fs->fs_bsize),
			((char *)fscs) + i);
	proto = fopen(argv[2], "r");
D 10
	descend((struct inode *)0);
E 10
I 10
	descend((struct dinode *)0, ROOTINO);
E 10
D 6
	wtfs(SBLOCK, SBSIZE, (char *)fs);
E 6
I 6
	wtfs(SBOFF / dev_bsize, SBSIZE, (char *)fs);
E 6
	for (i = 0; i < fs->fs_cssize; i += fs->fs_bsize)
		wtfs(fsbtodb(&sblock, fs->fs_csaddr + numfrags(&sblock, i)),
			(int)(fs->fs_cssize - i < fs->fs_bsize ?
			    fs->fs_cssize - i : fs->fs_bsize),
			((char *)fscs) + i);
	exit(errs);
}

D 10
descend(par)
	struct inode *par;
E 10
I 10
descend(par, parinum)
	struct dinode *par;
	ino_t parinum;
E 10
{
D 10
	struct inode in;
E 10
I 10
	struct dinode in;
	ino_t inum;
E 10
	int ibc = 0;
	int i, f, c;
	struct dinode *dip, inos[MAXBSIZE / sizeof (struct dinode)];
	daddr_t ib[MAXBSIZE / sizeof (daddr_t)];
	char buf[MAXBSIZE];

	getstr();
D 10
	in.i_mode = gmode(token[0], "-bcd", IFREG, IFBLK, IFCHR, IFDIR);
	in.i_mode |= gmode(token[1], "-u", 0, ISUID, 0, 0);
	in.i_mode |= gmode(token[2], "-g", 0, ISGID, 0, 0);
E 10
I 10
	in.di_mode = gmode(token[0], "-bcd", IFREG, IFBLK, IFCHR, IFDIR);
	in.di_mode |= gmode(token[1], "-u", 0, ISUID, 0, 0);
	in.di_mode |= gmode(token[2], "-g", 0, ISGID, 0, 0);
E 10
	for (i = 3; i < 6; i++) {
		c = token[i];
		if (c < '0' || c > '7') {
			printf("%c/%s: bad octal mode digit\n", c, token);
			errs++;
			c = 0;
		}
D 10
		in.i_mode |= (c-'0')<<(15-3*i);
E 10
I 10
		in.di_mode |= (c-'0')<<(15-3*i);
E 10
	}
D 10
	in.i_uid = getnum(); in.i_gid = getnum();
E 10
I 10
	in.di_uid = getnum(); in.di_gid = getnum();
E 10
	for (i = 0; i < fs->fs_bsize; i++)
		buf[i] = 0;
	for (i = 0; i < NINDIR(fs); i++)
		ib[i] = (daddr_t)0;
D 10
	in.i_nlink = 1;
	in.i_size = 0;
E 10
I 10
	in.di_nlink = 1;
	in.di_size = 0;
E 10
	for (i = 0; i < NDADDR; i++)
D 10
		in.i_db[i] = (daddr_t)0;
E 10
I 10
		in.di_db[i] = (daddr_t)0;
E 10
	for (i = 0; i < NIADDR; i++)
D 10
		in.i_ib[i] = (daddr_t)0;
	if (par != (struct inode *)0) {
		ialloc(&in);
E 10
I 10
		in.di_ib[i] = (daddr_t)0;
	if (par != (struct dinode *)0) {
		inum = ialloc(&in);
E 10
	} else {
		par = &in;
D 16
		i = itod(fs, ROOTINO);
E 16
I 16
		i = ino_to_fsba(fs, ROOTINO);
E 16
		rdfs(fsbtodb(fs, i), fs->fs_bsize, (char *)inos);
		dip = &inos[ROOTINO % INOPB(fs)];
D 10
		in.i_number = ROOTINO;
		in.i_nlink = dip->di_nlink;
		in.i_size = dip->di_size;
		in.i_db[0] = dip->di_db[0];
		rdfs(fsbtodb(fs, in.i_db[0]), fs->fs_bsize, buf);
E 10
I 10
		inum = ROOTINO;
		in.di_nlink = dip->di_nlink;
		in.di_size = dip->di_size;
		in.di_db[0] = dip->di_db[0];
		rdfs(fsbtodb(fs, in.di_db[0]), fs->fs_bsize, buf);
E 10
	}

D 10
	switch (in.i_mode&IFMT) {
E 10
I 10
	switch (in.di_mode&IFMT) {
E 10

	case IFREG:
		getstr();
		f = open(token, 0);
		if (f < 0) {
			printf("%s: cannot open\n", token);
			errs++;
			break;
		}
		while ((i = read(f, buf, (int)fs->fs_bsize)) > 0) {
D 10
			in.i_size += i;
			newblk(buf, &ibc, ib, (int)blksize(fs, &in, ibc));
E 10
I 10
			in.di_size += i;
			newblk(buf, &ibc, ib, (int)dblksize(fs, &in, ibc));
E 10
		}
		close(f);
		break;

	case IFBLK:
	case IFCHR:
		/*
		 * special file
		 * content is maj/min types
		 */

		i = getnum() & 0377;
		f = getnum() & 0377;
D 2
		in.i_dev = (i << 8) | f;
E 2
I 2
D 10
		in.i_rdev = (i << 8) | f;
E 10
I 10
		in.di_rdev = (i << 8) | f;
E 10
E 2
		break;

	case IFDIR:
		/*
		 * directory
		 * put in extra links
		 * call recursively until
		 * name of "$" found
		 */

D 10
		if (in.i_number != ROOTINO) {
			par->i_nlink++;
			in.i_nlink++;
			entry(&in, in.i_number, ".", buf);
			entry(&in, par->i_number, "..", buf);
E 10
I 10
		if (inum != ROOTINO) {
			par->di_nlink++;
			in.di_nlink++;
			entry(&in, inum, ".", buf);
			entry(&in, parinum, "..", buf);
E 10
		}
		for (;;) {
			getstr();
			if (token[0]=='$' && token[1]=='\0')
				break;
			entry(&in, (ino_t)(ino+1), token, buf);
D 10
			descend(&in);
E 10
I 10
			descend(&in, inum);
E 10
		}
D 10
		if (in.i_number != ROOTINO)
			newblk(buf, &ibc, ib, (int)blksize(fs, &in, 0));
E 10
I 10
		if (inum != ROOTINO)
			newblk(buf, &ibc, ib, (int)dblksize(fs, &in, 0));
E 10
		else
D 10
			wtfs(fsbtodb(fs, in.i_db[0]), (int)fs->fs_bsize, buf);
E 10
I 10
			wtfs(fsbtodb(fs, in.di_db[0]), (int)fs->fs_bsize, buf);
E 10
		break;
	}
D 10
	iput(&in, &ibc, ib);
E 10
I 10
	iput(&in, &ibc, ib, inum);
E 10
}

/*ARGSUSED*/
gmode(c, s, m0, m1, m2, m3)
	char c, *s;
{
	int i;

	for (i = 0; s[i]; i++)
		if (c == s[i])
			return((&m0)[i]);
	printf("%c/%s: bad mode\n", c, token);
	errs++;
	return(0);
}

long
getnum()
{
	int i, c;
	long n;

	getstr();
	n = 0;
	i = 0;
	for (i = 0; c=token[i]; i++) {
		if (c<'0' || c>'9') {
			printf("%s: bad number\n", token);
			errs++;
			return((long)0);
		}
		n = n*10 + (c-'0');
	}
	return(n);
}

getstr()
{
	int i, c;

loop:
	switch (c = getc(proto)) {

	case ' ':
	case '\t':
	case '\n':
		goto loop;

	case EOF:
		printf("Unexpected EOF\n");
		exit(1);

	case ':':
		while (getc(proto) != '\n')
			;
		goto loop;

	}
	i = 0;
	do {
		token[i++] = c;
		c = getc(proto);
	} while (c != ' ' && c != '\t' && c != '\n' && c != '\0');
	token[i] = 0;
}

entry(ip, inum, str, buf)
D 10
	struct inode *ip;
E 10
I 10
	struct dinode *ip;
E 10
	ino_t inum;
	char *str;
	char *buf;
{
	register struct direct *dp, *odp;
D 3
	int oldsize, newsize, freespace;
E 3
I 3
	int oldsize, newsize, spacefree;
E 3

	odp = dp = (struct direct *)buf;
D 10
	while ((int)dp - (int)buf < ip->i_size) {
E 10
I 10
	while ((int)dp - (int)buf < ip->di_size) {
E 10
		odp = dp;
		dp = (struct direct *)((int)dp + dp->d_reclen);
	}
	if (odp != dp)
		oldsize = DIRSIZ(odp);
	else
		oldsize = 0;
D 3
	freespace = odp->d_reclen - oldsize;
E 3
I 3
	spacefree = odp->d_reclen - oldsize;
E 3
	dp = (struct direct *)((int)odp + oldsize);
	dp->d_ino = inum;
	dp->d_namlen = strlen(str);
	newsize = DIRSIZ(dp);
D 3
	if (freespace >= newsize) {
E 3
I 3
	if (spacefree >= newsize) {
E 3
		odp->d_reclen = oldsize;
D 3
		dp->d_reclen = freespace;
E 3
I 3
		dp->d_reclen = spacefree;
E 3
	} else {
		dp = (struct direct *)((int)odp + odp->d_reclen);
		if ((int)dp - (int)buf >= fs->fs_bsize) {
			printf("directory too large\n");
			exit(1);
		}
		dp->d_ino = inum;
		dp->d_namlen = strlen(str);
		dp->d_reclen = DIRBLKSIZ;
	}
	strcpy(dp->d_name, str);
D 10
	ip->i_size = (int)dp - (int)buf + newsize;
E 10
I 10
	ip->di_size = (int)dp - (int)buf + newsize;
E 10
}

newblk(buf, aibc, ib, size)
	int *aibc;
	char *buf;
	daddr_t *ib;
	int size;
{
	int i;
D 7
	daddr_t bno;
E 7
I 7
	daddr_t bno, alloc();
E 7

	bno = alloc(size);
	wtfs(fsbtodb(fs, bno), (int)fs->fs_bsize, buf);
	for (i = 0; i < fs->fs_bsize; i++)
		buf[i] = 0;
	ib[(*aibc)++] = bno;
	if (*aibc >= NINDIR(fs)) {
		printf("indirect block full\n");
		errs++;
		*aibc = 0;
	}
}

D 10
iput(ip, aibc, ib)
	struct inode *ip;
E 10
I 10
iput(ip, aibc, ib, inum)
	struct dinode *ip;
E 10
	int *aibc;
	daddr_t *ib;
I 10
	ino_t inum;
E 10
{
I 14
	struct dinode buf[MAXBSIZE / sizeof (struct dinode)];
E 14
D 7
	daddr_t d;
E 7
I 7
	daddr_t d, alloc();
E 7
	int i;
D 14
	struct dinode buf[MAXBSIZE / sizeof (struct dinode)];
E 14
I 14
	struct timeval t;
E 14
I 7
D 13
	time_t time();
E 13
E 7

D 7
	ip->i_atime = ip->i_mtime = ip->i_ctime = time((long *)0);
E 7
I 7
D 10
	ip->i_atime = ip->i_mtime = ip->i_ctime = time((time_t *)NULL);
E 7
	switch (ip->i_mode&IFMT) {
E 10
I 10
D 13
	ip->di_atime = ip->di_mtime = ip->di_ctime = time((time_t *)NULL);
E 13
I 13
D 14
	(void)gettimeofday(&ip->di_atime.tv_sec, NULL);
E 14
I 14
	(void)gettimeofday(&t, NULL);
D 17
	ip->di_atime.ts_sec = t.tv_sec;
	ip->di_atime.ts_nsec = 0;
E 17
I 17
	ip->di_atime = t.tv_sec;
	ip->di_atimensec = 0;
E 17
E 14
	ip->di_mtime = ip->di_ctime = ip->di_atime;
E 13
	switch (ip->di_mode&IFMT) {
E 10

	case IFDIR:
	case IFREG:
		for (i = 0; i < *aibc; i++) {
			if (i >= NDADDR)
				break;
D 10
			ip->i_db[i] = ib[i];
E 10
I 10
			ip->di_db[i] = ib[i];
E 10
		}
		if (*aibc > NDADDR) {
D 10
			ip->i_ib[0] = alloc((int)fs->fs_bsize);
E 10
I 10
			ip->di_ib[0] = alloc((int)fs->fs_bsize);
E 10
			for (i = 0; i < NINDIR(fs) - NDADDR; i++) {
				ib[i] = ib[i+NDADDR];
				ib[i+NDADDR] = (daddr_t)0;
			}
D 10
			wtfs(fsbtodb(fs, ip->i_ib[0]),
E 10
I 10
			wtfs(fsbtodb(fs, ip->di_ib[0]),
E 10
			    (int)fs->fs_bsize, (char *)ib);
		}
		break;

	case IFBLK:
	case IFCHR:
		break;

	default:
D 10
		printf("bad mode %o\n", ip->i_mode);
E 10
I 10
		printf("bad mode %o\n", ip->di_mode);
E 10
		exit(1);
	}
D 10
	d = fsbtodb(fs, itod(fs, ip->i_number));
E 10
I 10
D 16
	d = fsbtodb(fs, itod(fs, inum));
E 16
I 16
	d = fsbtodb(fs, ino_to_fsba(fs, inum));
E 16
E 10
	rdfs(d, (int)fs->fs_bsize, (char *)buf);
D 10
	buf[itoo(fs, ip->i_number)].di_ic = ip->i_ic;
E 10
I 10
D 16
	buf[itoo(fs, inum)] = *ip;
E 16
I 16
	buf[ino_to_fsbo(fs, inum)] = *ip;
E 16
E 10
	wtfs(d, (int)fs->fs_bsize, (char *)buf);
}

daddr_t
alloc(size)
	int size;
{
	int i, frag;
	daddr_t d;
	static int cg = 0;

again:
	rdfs(fsbtodb(&sblock, cgtod(&sblock, cg)), (int)sblock.fs_cgsize,
	    (char *)&acg);
D 8
	if (acg.cg_magic != CG_MAGIC) {
E 8
I 8
	if (!cg_chkmagic(&acg)) {
E 8
		printf("cg %d: bad magic number\n", cg);
		return (0);
	}
	if (acg.cg_cs.cs_nbfree == 0) {
		cg++;
		if (cg >= fs->fs_ncg) {
			printf("ran out of space\n");
			return (0);
		}
		goto again;
	}
	for (d = 0; d < acg.cg_ndblk; d += sblock.fs_frag)
D 8
		if (isblock(&sblock, (u_char *)acg.cg_free, d / sblock.fs_frag))
E 8
I 8
		if (isblock(&sblock, (u_char *)cg_blksfree(&acg),
		    d / sblock.fs_frag))
E 8
			goto goth;
	printf("internal error: can't find block in cyl %d\n", cg);
	return (0);
goth:
D 8
	clrblock(&sblock, (u_char *)acg.cg_free, d / sblock.fs_frag);
E 8
I 8
	clrblock(&sblock, (u_char *)cg_blksfree(&acg), d / sblock.fs_frag);
E 8
	acg.cg_cs.cs_nbfree--;
	sblock.fs_cstotal.cs_nbfree--;
	fscs[cg].cs_nbfree--;
D 8
	acg.cg_btot[cbtocylno(&sblock, d)]--;
	acg.cg_b[cbtocylno(&sblock, d)][cbtorpos(&sblock, d)]--;
E 8
I 8
	cg_blktot(&acg)[cbtocylno(&sblock, d)]--;
	cg_blks(&sblock, &acg, cbtocylno(&sblock, d))[cbtorpos(&sblock, d)]--;
E 8
	if (size != sblock.fs_bsize) {
		frag = howmany(size, sblock.fs_fsize);
		fscs[cg].cs_nffree += sblock.fs_frag - frag;
		sblock.fs_cstotal.cs_nffree += sblock.fs_frag - frag;
		acg.cg_cs.cs_nffree += sblock.fs_frag - frag;
		acg.cg_frsum[sblock.fs_frag - frag]++;
		for (i = frag; i < sblock.fs_frag; i++)
D 8
			setbit(acg.cg_free, d + i);
E 8
I 8
			setbit(cg_blksfree(&acg), d + i);
E 8
	}
	wtfs(fsbtodb(&sblock, cgtod(&sblock, cg)), (int)sblock.fs_cgsize,
	    (char *)&acg);
	return (acg.cg_cgx * fs->fs_fpg + d);
}

/*
 * Allocate an inode on the disk
 */
I 10
ino_t
E 10
ialloc(ip)
D 10
	register struct inode *ip;
E 10
I 10
	register struct dinode *ip;
E 10
{
I 10
	ino_t inum;
E 10
D 7
	struct dinode buf[MAXBSIZE / sizeof (struct dinode)];
	daddr_t d;
E 7
	int c;

D 10
	ip->i_number = ++ino;
	c = itog(&sblock, ip->i_number);
E 10
I 10
	inum = ++ino;
D 16
	c = itog(&sblock, inum);
E 16
I 16
	c = ino_to_cg(&sblock, inum);
E 16
E 10
	rdfs(fsbtodb(&sblock, cgtod(&sblock, c)), (int)sblock.fs_cgsize,
	    (char *)&acg);
D 8
	if (acg.cg_magic != CG_MAGIC) {
E 8
I 8
	if (!cg_chkmagic(&acg)) {
E 8
		printf("cg %d: bad magic number\n", c);
		exit(1);
	}
D 10
	if (ip->i_mode & IFDIR) {
E 10
I 10
	if (ip->di_mode & IFDIR) {
E 10
		acg.cg_cs.cs_ndir++;
		sblock.fs_cstotal.cs_ndir++;
		fscs[c].cs_ndir++;
	}
	acg.cg_cs.cs_nifree--;
D 8
	setbit(acg.cg_iused, ip->i_number);
E 8
I 8
D 10
	setbit(cg_inosused(&acg), ip->i_number);
E 10
I 10
	setbit(cg_inosused(&acg), inum);
E 10
E 8
	wtfs(fsbtodb(&sblock, cgtod(&sblock, c)), (int)sblock.fs_cgsize,
	    (char *)&acg);
	sblock.fs_cstotal.cs_nifree--;
	fscs[c].cs_nifree--;
D 10
	if(ip->i_number >= sblock.fs_ipg * sblock.fs_ncg) {
D 7
		printf("fsinit: inode value out of range (%d).\n",
E 7
I 7
		printf("fsinit: inode value out of range (%lu).\n",
E 7
		    ip->i_number);
E 10
I 10
	if(inum >= sblock.fs_ipg * sblock.fs_ncg) {
		printf("fsinit: inode value out of range (%lu).\n", inum);
E 10
		exit(1);
	}
D 7
	return (ip->i_number);
E 7
I 7
D 10
	/* return (ip->i_number); */
E 10
I 10
	return (inum);
E 10
E 7
}

/*
 * read a block from the file system
 */
rdfs(bno, size, bf)
	int bno, size;
	char *bf;
{
	int n;
I 7
	off_t lseek();
E 7

D 6
	if (lseek(fsi, bno * DEV_BSIZE, 0) < 0) {
E 6
I 6
	if (lseek(fsi, bno * dev_bsize, 0) < 0) {
E 6
D 7
		printf("seek error: %ld\n", bno);
E 7
I 7
		printf("seek error: %d\n", bno);
E 7
		perror("rdfs");
		exit(1);
	}
	n = read(fsi, bf, size);
	if(n != size) {
D 7
		printf("read error: %ld\n", bno);
E 7
I 7
		printf("read error: %d\n", bno);
E 7
		perror("rdfs");
		exit(1);
	}
}

/*
 * write a block to the file system
 */
wtfs(bno, size, bf)
	int bno, size;
	char *bf;
{
	int n;
I 7
	off_t lseek();
E 7

D 6
	lseek(fso, bno * DEV_BSIZE, 0);
	if (lseek(fso, bno * DEV_BSIZE, 0) < 0) {
E 6
I 6
	if (lseek(fso, bno * dev_bsize, 0) < 0) {
E 6
D 7
		printf("seek error: %ld\n", bno);
E 7
I 7
		printf("seek error: %d\n", bno);
E 7
		perror("wtfs");
		exit(1);
	}
	n = write(fso, bf, size);
	if(n != size) {
D 7
		printf("write error: %D\n", bno);
E 7
I 7
		printf("write error: %d\n", bno);
E 7
		perror("wtfs");
		exit(1);
	}
}
/*
 * check if a block is available
 */
isblock(fs, cp, h)
	struct fs *fs;
	unsigned char *cp;
	int h;
{
	unsigned char mask;

	switch (fs->fs_frag) {
	case 8:
		return (cp[h] == 0xff);
	case 4:
		mask = 0x0f << ((h & 0x1) << 2);
		return ((cp[h >> 1] & mask) == mask);
	case 2:
		mask = 0x03 << ((h & 0x3) << 1);
		return ((cp[h >> 2] & mask) == mask);
	case 1:
		mask = 0x01 << (h & 0x7);
		return ((cp[h >> 3] & mask) == mask);
	default:
D 7
		fprintf(stderr, "isblock bad fs_frag %d\n", fs->fs_frag);
E 7
I 7
		fprintf(stderr, "isblock bad fs_frag %ld\n", fs->fs_frag);
E 7
		return (0);
	}
	/*NOTREACHED*/
}

/*
 * take a block out of the map
 */
clrblock(fs, cp, h)
	struct fs *fs;
	unsigned char *cp;
	int h;
{
	switch ((fs)->fs_frag) {
	case 8:
		cp[h] = 0;
		return;
	case 4:
		cp[h >> 1] &= ~(0x0f << ((h & 0x1) << 2));
		return;
	case 2:
		cp[h >> 2] &= ~(0x03 << ((h & 0x3) << 1));
		return;
	case 1:
		cp[h >> 3] &= ~(0x01 << (h & 0x7));
		return;
	default:
D 7
		fprintf(stderr, "clrblock bad fs_frag %d\n", fs->fs_frag);
E 7
I 7
		fprintf(stderr, "clrblock bad fs_frag %ld\n", fs->fs_frag);
E 7
		return;
	}
}

E 1
