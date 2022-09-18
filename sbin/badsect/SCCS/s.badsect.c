h61695
s 00001/00001/00182
d D 8.2 95/05/04 16:25:20 mckusick 17 16
c include ordering
e
s 00005/00005/00178
d D 8.1 93/06/05 10:49:01 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00003/00172
d D 5.12 93/05/19 16:47:11 bostic 15 14
c lint
e
s 00005/00003/00170
d D 5.11 93/02/15 10:16:42 ralph 14 13
c use unistd.h to declare lseek properly.
e
s 00002/00002/00171
d D 5.10 91/11/11 11:17:11 bostic 13 12
c break UFS up into FFS/UFS/LFS/MFS
e
s 00001/00011/00172
d D 5.9 90/06/01 16:14:15 bostic 12 11
c new copyright notice
e
s 00001/00003/00182
d D 5.8 90/05/04 13:55:15 mckusick 11 10
c delete unneeded headers
e
s 00004/00002/00181
d D 5.7 89/07/30 10:40:27 bostic 10 9
c vnodes
e
s 00004/00003/00179
d D 5.6 89/05/11 13:51:08 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00017/00006/00165
d D 5.5 88/11/01 18:16:06 bostic 8 7
c add Berkeley specific copyright
e
s 00002/00002/00169
d D 5.4 88/05/31 17:54:01 mckusick 7 6
c convert to understand dynamic file systems
e
s 00004/00002/00167
d D 5.3 87/02/23 17:39:44 mckusick 6 5
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00001/00001/00168
d D 5.2 85/06/24 09:37:04 bloom 5 4
c fix a return value
e
s 00015/00001/00154
d D 5.1 85/06/06 11:00:48 dist 4 3
c Add copyright
e
s 00134/00008/00021
d D 4.3 83/02/24 14:28:27 mckusick 3 2
c update for new file system
e
s 00000/00000/00029
d D 4.2 81/05/11 03:25:16 root 2 1
c new version
e
s 00029/00000/00000
d D 4.1 81/05/10 19:24:43 root 1 0
c date and time created 81/05/10 19:24:43 by root
e
u
U
t
T
I 1
D 4
static	char *sccsid = "%W% (Berkeley) %E%";
E 4
I 4
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 16
 * Copyright (c) 1981, 1983 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1981, 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 12
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 8
 */

#ifndef lint
D 16
char copyright[] =
D 8
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1981, 1983 The Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1981, 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 4

/*
 * badsect
 *
 * Badsect takes a list of file-system relative sector numbers
 * and makes files containing the blocks of which these sectors are a part.
 * It can be used to contain sectors which have problems if these sectors
 * are not part of the bad file for the pack (see bad144).  For instance,
 * this program can be used if the driver for the file system in question
 * does not support bad block forwarding.
 */
I 3
D 9
#include <stdio.h>
E 9
E 3
#include <sys/param.h>
I 3
D 9
#include <sys/fs.h>
E 9
#include <sys/dir.h>
#include <sys/stat.h>
I 15

E 15
I 9
D 10
#include <sys/fs.h>
E 9
#include <sys/inode.h>
E 10
I 10
D 11
#include <sys/time.h>
#include <sys/vnode.h>
E 11
D 13
#include <ufs/fs.h>
D 11
#include <ufs/inode.h>
E 11
I 11
#include <ufs/dinode.h>
E 13
I 13
D 17
#include <ufs/ffs/fs.h>
E 17
#include <ufs/ufs/dinode.h>
I 17
#include <ufs/ffs/fs.h>
E 17
I 14
D 15
#include <unistd.h>
E 14
E 13
E 11
E 10
I 9
#include <stdio.h>
E 15
I 15

#include <fcntl.h>
E 15
#include <paths.h>
I 15
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
E 15
E 9
E 3

I 3
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
int	fso, fsi;
int	errs;
I 6
long	dev_bsize = 1;
E 6

char buf[MAXBSIZE];

I 15
void	rdfs __P((daddr_t, int, char *));
int	chkuse __P((daddr_t, int));
E 15

I 15
int
E 15
E 3
main(argc, argv)
	int argc;
D 3
	char **argv;
E 3
I 3
	char *argv[];
E 3
{
D 3
	char nambuf[32];
	int errs = 0;
E 3
I 3
	daddr_t number;
	struct stat stbuf, devstat;
	register struct direct *dp;
	DIR *dirp;
D 15
	int fd;
E 15
	char name[BUFSIZ];
E 3

D 3
	--argc, argv++;
	while (argc > 0) {
		if (mknod(*argv, 0, atoi(*argv) / CLSIZE))
			perror("mknod"), errs++;
		argc--, argv++;
E 3
I 3
	if (argc < 3) {
		fprintf(stderr, "usage: badsect bbdir blkno [ blkno ]\n");
		exit(1);
E 3
	}
I 3
	if (chdir(argv[1]) < 0 || stat(".", &stbuf) < 0) {
		perror(argv[1]);
		exit(2);
	}
D 9
	strcpy(name, "/dev/");
E 9
I 9
	strcpy(name, _PATH_DEV);
E 9
	if ((dirp = opendir(name)) == NULL) {
		perror(name);
		exit(3);
	}
	while ((dp = readdir(dirp)) != NULL) {
		strcpy(&name[5], dp->d_name);
		if (stat(name, &devstat) < 0) {
			perror(name);
			exit(4);
		}
		if (stbuf.st_dev == devstat.st_rdev &&
		    (devstat.st_mode & IFMT) == IFBLK)
			break;
	}
	closedir(dirp);
	if (dp == NULL) {
		printf("Cannot find dev 0%o corresponding to %s\n",
			stbuf.st_rdev, argv[1]);
		exit(5);
	}
	if ((fsi = open(name, 0)) < 0) {
		perror(name);
		exit(6);
	}
	fs = &sblock;
D 6
	rdfs(SBLOCK, SBSIZE, (char *)fs);
E 6
I 6
	rdfs(SBOFF, SBSIZE, (char *)fs);
	dev_bsize = fs->fs_fsize / fsbtodb(fs, 1);
E 6
	for (argc -= 2, argv += 2; argc > 0; argc--, argv++) {
		number = atoi(*argv);
		if (chkuse(number, 1))
			continue;
		if (mknod(*argv, IFMT|0600, dbtofsb(fs, number)) < 0) {
			perror(*argv);
			errs++;
		}
	}
	printf("Don't forget to run ``fsck %s''\n", name);
E 3
	exit(errs);
I 3
}

I 15
int
E 15
chkuse(blkno, cnt)
	daddr_t blkno;
	int cnt;
{
	int cg;
	daddr_t fsbn, bn;

	fsbn = dbtofsb(fs, blkno);
	if ((unsigned)(fsbn+cnt) > fs->fs_size) {
		printf("block %d out of range of file system\n", blkno);
		return (1);
	}
	cg = dtog(fs, fsbn);
	if (fsbn < cgdmin(fs, cg)) {
		if (cg == 0 || (fsbn+cnt) > cgsblock(fs, cg)) {
			printf("block %d in non-data area: cannot attach\n",
				blkno);
			return (1);
		}
	} else {
		if ((fsbn+cnt) > cgbase(fs, cg+1)) {
			printf("block %d in non-data area: cannot attach\n",
				blkno);
			return (1);
		}
	}
	rdfs(fsbtodb(fs, cgtod(fs, cg)), (int)sblock.fs_cgsize,
	    (char *)&acg);
D 7
	if (acg.cg_magic != CG_MAGIC) {
E 7
I 7
	if (!cg_chkmagic(&acg)) {
E 7
		fprintf(stderr, "cg %d: bad magic number\n", cg);
		errs++;
D 5
		return;
E 5
I 5
		return (1);
E 5
	}
	bn = dtogd(fs, fsbn);
D 7
	if (isclr(acg.cg_free, bn))
E 7
I 7
	if (isclr(cg_blksfree(&acg), bn))
E 7
		printf("Warning: sector %d is in use\n", blkno);
	return (0);
}

/*
 * read a block from the file system
 */
I 15
void
E 15
rdfs(bno, size, bf)
D 14
	int bno, size;
E 14
I 14
	daddr_t bno;
	int size;
E 14
	char *bf;
{
	int n;

D 6
	if (lseek(fsi, bno * DEV_BSIZE, 0) < 0) {
E 6
I 6
D 14
	if (lseek(fsi, bno * dev_bsize, 0) < 0) {
E 14
I 14
	if (lseek(fsi, (off_t)bno * dev_bsize, SEEK_SET) < 0) {
E 14
E 6
		printf("seek error: %ld\n", bno);
		perror("rdfs");
		exit(1);
	}
	n = read(fsi, bf, size);
D 14
	if(n != size) {
E 14
I 14
	if (n != size) {
E 14
		printf("read error: %ld\n", bno);
		perror("rdfs");
		exit(1);
	}
E 3
}
E 1
