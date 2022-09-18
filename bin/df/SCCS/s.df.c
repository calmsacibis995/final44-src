h18370
s 00035/00095/00300
d D 8.9 95/05/08 16:17:05 mckusick 67 66
c use vfslist from mount rather than rolling our own syntax
e
s 00002/00001/00393
d D 8.8 94/07/12 16:04:50 mckusick 66 65
c add -t type to usage output
e
s 00002/00002/00392
d D 8.7 94/04/02 09:55:51 pendry 65 64
c add 1994 copyright
e
s 00008/00010/00386
d D 8.6 94/04/01 02:04:51 pendry 64 62
c prettyness police
e
s 00007/00008/00388
d R 8.6 94/04/01 01:56:54 pendry 63 62
c prettyness police
e
s 00004/00004/00392
d D 8.5 94/01/24 06:36:07 bostic 62 61
c Mirror Kirk's 8.9 change to /sys/sys/mount.h; ISOFS => CD9660
e
s 00000/00001/00396
d D 8.4 94/01/21 16:53:23 bostic 61 60
c typo
e
s 00006/00000/00391
d D 8.3 94/01/21 16:48:41 bostic 60 59
c add USL's coypright notice
e
s 00009/00005/00382
d D 8.2 94/01/13 13:03:01 hibler 59 58
c new filesystems
e
s 00005/00005/00382
d D 8.1 93/06/02 18:08:03 mckusick 58 57
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00387
d D 5.36 93/06/02 17:58:24 mckusick 57 54
c getbsize moves to libc
e
s 00001/00001/00387
d D 5.35 93/05/06 14:36:25 mckusick 54 53
c avoid unnecessary hangs
e
s 00128/00010/00260
d D 5.34 93/05/05 00:28:11 mckusick 53 52
c update from Mike Hibler to add -t type
e
s 00016/00021/00254
d D 5.33 93/04/28 17:28:11 bostic 52 51
c use err/warn; delete -k; bcopy -> memmove; getbsize no longer needs the
c program name; lint
e
s 00001/00001/00274
d D 5.32 93/01/22 16:11:43 mckusick 51 50
c MNT_NOFORCE is gone
e
s 00016/00017/00259
d D 5.31 92/10/02 15:49:38 bostic 50 49
c remove last vestiges of AT&T proprietary code
e
s 00003/00003/00273
d D 5.30 92/04/23 17:42:32 bostic 49 48
c don't let fields meet under any circumstances
e
s 00003/00002/00273
d D 5.29 92/03/09 14:31:32 bostic 48 47
c make block size a long
e
s 00026/00025/00249
d D 5.28 92/03/01 16:58:27 bostic 47 46
c replace -k with the BLOCKSIZE environmental variable
e
s 00005/00005/00269
d D 5.27 91/12/14 21:35:50 mckusick 46 45
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00001/00001/00273
d D 5.26 91/11/10 13:01:05 bostic 45 43
c break ufs into multiple parts
e
s 00001/00002/00272
d R 5.26 91/11/05 16:08:57 bostic 44 43
c create kernel /usr/include symlink
e
s 00021/00019/00253
d D 5.25 91/09/14 10:31:40 bostic 43 42
c make the headers POSIX-like, ANSI stuff
e
s 00001/00001/00271
d D 5.24 91/03/06 00:11:51 donn 42 41
c Don't mktemp() string constants.
e
s 00002/00002/00270
d D 5.23 91/02/25 07:34:42 bostic 41 40
c ANSI fixes
e
s 00010/00005/00262
d D 5.22 91/01/31 17:22:11 torek 40 39
c gcc-detected lint: now clean under -Wall once /usr/include is fixed
e
s 00022/00076/00245
d D 5.21 90/06/24 19:14:55 karels 39 38
c this is what I meant (make df work on raw disks, remove other compat stuff)
e
s 00001/00011/00320
d D 5.20 90/05/31 20:29:43 bostic 38 37
c new copyright notice
e
s 00001/00001/00330
d D 5.19 90/05/15 19:41:36 bostic 37 36
c string.h is ANSI C include file
e
s 00001/00001/00330
d D 5.18 90/05/04 22:47:29 mckusick 36 35
c mount flags change from M_ to MNT_
e
s 00002/00001/00329
d D 5.17 90/03/13 12:12:34 mckusick 35 34
c missing parenthesis (from hibler)
e
s 00035/00017/00295
d D 5.16 90/03/06 23:18:23 mckusick 34 33
c dynamically calculate the size of the "Filesystem" field
e
s 00013/00006/00299
d D 5.15 90/03/06 21:01:42 mckusick 33 32
c add -n flag to skip calls to underlying filesystem
e
s 00000/00036/00305
d D 5.14 89/10/17 15:19:25 mckusick 32 31
c getmntinfo becomes a C library routine
e
s 00001/00001/00340
d D 5.13 89/10/14 15:04:04 mckusick 31 30
c umount => unmount
e
s 00000/00001/00341
d D 5.12 89/08/22 11:57:33 bostic 30 29
c don't need pathnames.h any more
e
s 00040/00030/00302
d D 5.11 89/08/22 11:55:12 bostic 29 28
c add -k flag, change default output to 512 byte blocks
c move mount point to '/', use mktemp so multiple users works right
c minor formatting and lint, precede error messages with "df:"
e
s 00006/00002/00326
d D 5.10 89/08/16 18:17:27 mckusick 28 27
c print error when requested pathname cannot be stat'ed
e
s 00013/00000/00315
d D 5.9 89/08/16 18:01:11 mckusick 27 26
c allow printing of statistics for unmounted special devices
e
s 00069/00071/00246
d D 5.8 89/08/16 17:37:49 mckusick 26 25
c lint; allow specification of block devices
e
s 00156/00055/00161
d D 5.7 89/06/08 16:28:26 mckusick 25 24
c convert for vnodes (use new statfs system call)
e
s 00002/00002/00214
d D 5.6 89/05/23 16:56:03 bostic 24 23
c FSTAB -> _PATH_FSTAB; sys/fs.h -> ufs/fs.h
e
s 00003/00003/00213
d D 5.5 89/05/09 14:15:55 bostic 23 22
c add pathnames.h
e
s 00025/00021/00191
d D 5.4 89/03/06 08:24:36 bostic 22 21
c add pathnames.h, getopt(3); lint cleanups, error cleanups
e
s 00002/00002/00210
d D 5.3 88/01/10 15:37:03 bostic 21 20
c fix #endif lines for ANSI C
e
s 00009/00009/00203
d D 5.2 87/03/18 18:04:22 mckusick 20 19
c SBLOCK become SBOFF
e
s 00014/00002/00198
d D 5.1 85/04/30 14:55:36 dist 19 18
c Add copyright
e
s 00012/00004/00188
d D 4.18 84/02/02 11:19:32 ralph 18 17
c don't exit if df on a drive that is off-line.
e
s 00022/00024/00170
d D 4.17 83/06/19 18:09:05 sam 17 16
c new mtab
e
s 00002/00001/00192
d D 4.16 83/05/24 13:47:58 sam 16 15
c quotas
e
s 00002/00002/00191
d D 4.15 83/02/07 15:47:52 sam 15 14
c only show file systems of interest
e
s 00001/00001/00192
d D 4.14 83/01/02 14:13:19 sam 14 13
c from sun
e
s 00001/00000/00192
d D 4.13 82/06/15 12:40:11 mckusick 13 12
c sync() before printing so as to get up to date info
e
s 00039/00032/00153
d D 4.12 82/05/07 16:27:46 mckusick 12 11
c update to new fs
e
s 00003/00001/00182
d D 4.11 82/04/01 06:53:17 root 11 10
c fix sccsid
e
s 00002/00002/00181
d D 4.10 82/03/15 14:23:55 root 10 9
c bug in deciding which not to print
e
s 00001/00002/00182
d D 4.9 82/02/28 23:25:44 wnj 9 8
c remove traces of -l option
e
s 00078/00125/00106
d D 4.8 82/02/26 14:02:46 root 8 7
c new version cleaned up
e
s 00001/00001/00230
d D 4.7 81/07/10 15:19:58 bugs 7 6
c s/-il/-i -l/
e
s 00002/00001/00229
d D 4.6 81/07/08 16:11:51 wnj 6 5
c sync() less
e
s 00001/00001/00229
d D 4.5 81/03/22 21:11:14 wnj 5 4
c s/blocks/kbytes/
e
s 00004/00002/00226
d D 4.4 81/03/10 07:01:28 wnj 4 3
c miscellaneous minor fixups
e
s 00033/00014/00195
d D 4.3 80/10/15 23:35:38 bill 3 2
c put back in df dir
e
s 00002/00000/00207
d D 4.2 80/10/13 17:14:05 bill 2 1
c adding calls to fstab routines
e
s 00207/00000/00000
d D 4.1 80/10/01 17:26:18 bill 1 0
c date and time created 80/10/01 17:26:18 by bill
e
u
U
t
T
I 19
/*
D 25
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
D 39
 * Copyright (c) 1980 The Regents of the University of California.
E 39
I 39
D 58
 * Copyright (c) 1980, 1990 The Regents of the University of California.
E 39
 * All rights reserved.
E 58
I 58
D 65
 * Copyright (c) 1980, 1990, 1993
E 65
I 65
 * Copyright (c) 1980, 1990, 1993, 1994
E 65
 *	The Regents of the University of California.  All rights reserved.
E 58
D 61
 *
E 61
I 60
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
E 60
D 38
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
E 38
I 38
 * %sccs.include.redist.c%
E 38
E 25
 */

E 19
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
D 11
static	char *sccsid = "%W% (Berkeley) %G%";
E 11
I 11
#ifndef lint
D 19
static	char *sccsid = "%W% %G%";
#endif
E 19
I 19
D 58
char copyright[] =
D 25
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 25
I 25
D 39
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 39
I 39
"%Z% Copyright (c) 1980, 1990 The Regents of the University of California.\n\
E 39
E 25
 All rights reserved.\n";
E 58
I 58
static char copyright[] =
D 65
"%Z% Copyright (c) 1980, 1990, 1993\n\
E 65
I 65
"%Z% Copyright (c) 1980, 1990, 1993, 1994\n\
E 65
	The Regents of the University of California.  All rights reserved.\n";
E 58
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21
E 19
E 11
I 8

E 8
E 3
D 17
#include <stdio.h>
#include <fstab.h>
E 17
D 25
#include <sys/param.h>
D 12
#include <sys/filsys.h>
#include <sys/fblk.h>
E 12
I 12
D 24
#include <sys/fs.h>
E 24
I 24
#include <ufs/fs.h>
E 24
E 12
I 3
#include <sys/stat.h>
I 18
#include <errno.h>
E 18
I 8
D 22

E 22
I 17
#include <stdio.h>
#include <fstab.h>
#include <mtab.h>
I 22
#include "pathnames.h"
E 22

E 25
E 17
E 8
D 43
/*
 * df
 */
E 43
E 3
D 8

E 8
D 17
#define NFS	20	/* Max number of filesystems */

D 3

E 3
struct {
	char path[32];
	char spec[32];
} mtab[NFS];
E 17
I 17
D 25
struct	mtab mtab[NMOUNT];
E 17
D 8
char root[32];

char *mpath();

E 8
I 8
char	root[32];
char	*mpath();
E 25
I 25
D 29
#include <stdio.h>
#include <sys/types.h>
E 29
I 29
#include <sys/param.h>
E 29
I 26
#include <sys/stat.h>
E 26
#include <sys/mount.h>
I 67
#include <ufs/ufs/ufsmount.h>
E 67
I 52

#include <err.h>
E 52
I 43
#include <errno.h>
E 43
I 29
D 41
#include <sys/file.h>
E 41
I 41
#include <fcntl.h>
E 41
#include <stdio.h>
I 40
#include <stdlib.h>
E 40
D 37
#include <strings.h>
E 37
I 37
#include <string.h>
E 37
#include <unistd.h>
E 29
D 30
#include "pathnames.h"
E 30
E 25
E 8
D 12
daddr_t	blkno	= 1;
E 12

I 53
D 67
/* XXX assumes MOUNT_MAXTYPE < 32 */
#define MT(m)		(1 << (m))
E 67
I 67
int	  checkvfsname __P((const char *, char **));
char	**makevfslist __P((char *));
long	  regetmntinfo __P((struct statfs **, long, char **));
int	  bread __P((off_t, void *, int));
char	 *getmntpt __P((char *));
void	  prtstat __P((struct statfs *, int));
void	  ufs_df __P((char *, int));
void	  usage __P((void));
E 67

D 67
/* fixed values */
#define MT_NONE		(0)
#define MT_ALL		(MT(MOUNT_MAXTYPE+1)-1)

/* subject to change */
D 59
#define MT_AMDNFS	(1)	/* XXX automounted NFS FSes return type 0 */
#define MT_LOCAL	(MT(MOUNT_UFS)|MT(MOUNT_MFS)|MT(MOUNT_LFS))
E 59
I 59
#define MT_LOCAL \
D 62
    (MT(MOUNT_UFS)|MT(MOUNT_MFS)|MT(MOUNT_LFS)|MT(MOUNT_MSDOS)|MT(MOUNT_ISOFS))
E 62
I 62
    (MT(MOUNT_UFS)|MT(MOUNT_MFS)|MT(MOUNT_LFS)|MT(MOUNT_MSDOS)|MT(MOUNT_CD9660))
E 62
E 59
#define MT_DEFAULT	MT_ALL

struct typetab {
	char *str;
	long types;
} typetab[] = {
	"ufs",		MT(MOUNT_UFS),
	"local",	MT_LOCAL,
	"all",		MT_ALL,
D 59
	"nfs",		MT(MOUNT_NFS)|MT_AMDNFS,
E 59
I 59
	"nfs",		MT(MOUNT_NFS),
E 59
	"mfs",		MT(MOUNT_MFS),
	"lfs",		MT(MOUNT_LFS),
D 59
	"pc",		MT(MOUNT_PC),
E 59
I 59
	"msdos",	MT(MOUNT_MSDOS),
E 59
	"fdesc",	MT(MOUNT_FDESC),
	"portal",	MT(MOUNT_PORTAL),
#if 0
	/* return fsid of underlying FS */
	"lofs",		MT(MOUNT_LOFS),
	"null",		MT(MOUNT_NULL),
	"umap",		MT(MOUNT_UMAP),
#endif
	"kernfs",	MT(MOUNT_KERNFS),
I 59
	"procfs",	MT(MOUNT_PROCFS),
	"afs",		MT(MOUNT_AFS),
D 62
	"isofs",	MT(MOUNT_ISOFS),
	"cdfs",		MT(MOUNT_ISOFS),
E 62
I 62
	"iso9660fs",	MT(MOUNT_CD9660),
	"cdfs",		MT(MOUNT_CD9660),
E 62
E 59
	"misc",		MT(MOUNT_LOFS)|MT(MOUNT_FDESC)|MT(MOUNT_PORTAL)|
D 59
			MT(MOUNT_NULL)|MT(MOUNT_UMAP)|MT(MOUNT_KERNFS),
E 59
I 59
			MT(MOUNT_KERNFS)|MT(MOUNT_PROCFS),
E 59
D 62
	(char *)0,	0
E 62
I 62
	NULL,		0
E 62
};

long	addtype __P((long, char *));
long	regetmntinfo __P((struct statfs **, long, long));
E 53
I 26
D 43
char	*getmntpt();
I 40
void	ufs_df(), prtstat();
E 43
I 43
D 50
int	 bread __P((long, char *, int));
E 50
I 50
int	 bread __P((off_t, void *, int));
E 50
I 47
D 48
char	*getbsize __P((char *, int *, int *));
E 48
I 48
D 53
char	*getbsize __P((char *, int *, long *));
E 53
I 53
D 57
char	*getbsize __P((int *, long *));
E 57
E 53
E 48
E 47
char	*getmntpt __P((char *));
D 52
void	 prtstat __P((struct statfs *, long));
void	 ufs_df __P((char *, long));
E 52
I 52
void	 prtstat __P((struct statfs *, int));
void	 ufs_df __P((char *, int));
E 52
void	 usage __P((void));

E 43
E 40
E 26
D 9
int	lflag;
E 9
D 29
int	iflag;
E 29
I 29
D 33
int	iflag, kflag;
E 33
I 33
D 47
int	iflag, kflag, nflag;
E 47
I 47
D 53
int	iflag, nflag;
E 53
I 53
int	iflag, nflag, tflag;
E 67
I 67
int	iflag, nflag;
E 67
E 53
E 47
E 33
E 29
I 25
D 39
#ifdef COMPAT_43
int	oflag;
#endif /* COMPAT_43 */
E 39
I 39
struct	ufs_args mdev;
E 39
E 25

I 40
int
E 40
D 12
struct	filsys sblock;
E 12
I 12
D 25
union {
	struct fs iu_fs;
	char dummy[SBSIZE];
} sb;
#define sblock sb.iu_fs
E 12

int	fi;
daddr_t	alloc();
I 12
char	*strcpy();
E 12

E 25
main(argc, argv)
D 8
char **argv;
E 8
I 8
	int argc;
D 47
	char **argv;
E 47
I 47
	char *argv[];
E 47
E 8
{
D 22
	int i;
E 22
I 22
D 43
	extern int errno, optind;
D 28
	int ch, i;
E 28
I 28
	int err, ch, i;
E 28
D 25
	char *strerror();
E 25
I 25
D 29
	long mntsize;
I 26
	char *mntpt;
E 29
I 29
D 34
	long mntsize, getmntinfo();
E 34
I 34
D 41
	long width, maxwidth, mntsize, getmntinfo();
E 41
I 41
	long width, maxwidth, mntsize;
E 41
E 34
	char *mntpt, *mktemp();
E 43
E 29
	struct stat stbuf;
E 26
	struct statfs statfsbuf, *mntbuf;
I 43
D 52
	long width, maxwidth, mntsize;
	int err, ch, i;
E 52
I 52
D 64
	long mntsize;
	int err, ch, i, maxwidth, width;
E 64
I 64
D 67
	long fsmask, mntsize;
E 67
I 67
	long mntsize;
E 67
	int ch, err, i, maxwidth, width;
E 64
E 52
D 67
	char *mntpt;
E 67
I 67
	char *mntpt, **vfslist;
E 67
I 53
D 64
	long fsmask;
E 64
E 53
E 43
I 27
D 39
	struct ufs_args mdev;
E 39
E 27
E 25
E 22
D 3
	FILE *f = fopen(FSTAB, "r");
E 3
D 8
	char buf[128];
E 8
D 3
	struct	fstab	fs;
E 3

I 67
	vfslist = NULL;
E 67
D 14
	while (argc >= 1 && argv[1][0]=='-') {
E 14
I 14
D 22
	while (argc > 1 && argv[1][0]=='-') {
E 14
D 8
		switch(argv[1][1]) {
E 8
I 8
D 17
	switch (argv[1][1]) {
E 17
I 17
		switch (argv[1][1]) {
E 17
E 8

E 22
I 22
D 25
	while ((ch = getopt(argc, argv, "i")) != EOF)
E 25
I 25
D 29
	while ((ch = getopt(argc, argv, "io")) != EOF)
E 29
I 29
D 33
	while ((ch = getopt(argc, argv, "iko")) != EOF)
E 33
I 33
D 39
	while ((ch = getopt(argc, argv, "ikon")) != EOF)
E 39
I 39
D 52
	while ((ch = getopt(argc, argv, "ikn")) != EOF)
E 52
I 52
D 53
	while ((ch = getopt(argc, argv, "in")) != EOF)
E 53
I 53
	while ((ch = getopt(argc, argv, "int:")) != EOF)
E 53
E 52
E 39
E 33
E 29
E 25
D 64
		switch(ch) {
E 64
I 64
		switch (ch) {
E 64
E 22
D 8
		case 'l':
			lflag++;
			break;
E 8
I 8
D 17
	case 'i':
		iflag++;
		break;
E 17
I 17
		case 'i':
D 29
			iflag++;
E 29
I 29
			iflag = 1;
E 29
			break;
I 29
D 47
		case 'k':
			kflag = 1;
E 47
I 47
D 52
		case 'k':		/* Delete before 4.4BSD. */
			(void)fprintf(stderr, "df: -k no longer supported\n");
E 47
			break;
E 52
I 33
		case 'n':
			nflag = 1;
			break;
I 53
		case 't':
D 67
			fsmask = addtype(fsmask, optarg);
			tflag = 1;
E 67
I 67
			if (vfslist != NULL)
				errx(1, "only one -t option may be specified.");
			vfslist = makevfslist(optarg);
E 67
			break;
E 53
E 33
E 29
I 25
D 39
#ifdef COMPAT_43
		case 'o':
D 29
			oflag++;
E 29
I 29
			oflag = 1;
E 29
			break;
#endif /* COMPAT_43 */
E 39
E 25
E 17
E 8
D 22

E 22
I 22
		case '?':
E 22
D 8
		case 'i':
			iflag++;
			break;

		default:
D 7
			fprintf(stderr, "usage: df [ -il ] [ filsys... ]\n");
E 7
I 7
			fprintf(stderr, "usage: df [ -i ] [ -l ] [ filsys... ]\n");
E 7
			exit(0);
		}
		argc--, argv++;
E 8
I 8
D 17
	default:
D 9
		fprintf(stderr, "usage: df [ -i ] [ -l ] [ filsys... ]\n");
E 9
I 9
		fprintf(stderr, "usage: df [ -i ] [ filsys... ]\n");
E 9
		exit(0);
E 17
I 17
		default:
D 22
			fprintf(stderr, "usage: df [ -i ] [ filsys... ]\n");
			exit(0);
E 22
I 22
D 29
			fprintf(stderr, "usage: df [-i] [filsys ...]\n");
E 29
I 29
D 43
			fprintf(stderr,
D 33
			    "usage: df [-ik] [file | file_system ...]\n");
E 33
I 33
			    "usage: df [-ikn] [file | file_system ...]\n");
E 33
E 29
			exit(1);
E 43
I 43
			usage();
E 43
E 22
		}
D 22
		argc--, argv++;
E 22
I 22
	argc -= optind;
	argv += optind;

I 25
D 29
	printf("Filesystem    kbytes    used   avail capacity");
E 29
I 29
D 34
	printf("Filesystem  %s    used   avail capacity",
	    kflag ? "  kbytes" : "512-blks");
E 29
	if (iflag)
		printf(" iused   ifree  %%iused");
	printf("  Mounted on\n");
E 34
I 34
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	maxwidth = 0;
	for (i = 0; i < mntsize; i++) {
		width = strlen(mntbuf[i].f_mntfromname);
		if (width > maxwidth)
			maxwidth = width;
	}
I 53

E 53
E 34
D 39
#ifdef COMPAT_43
	if (oflag) {
D 34
		olddf(argv);
E 34
I 34
		olddf(argv, maxwidth);
E 34
		exit(0);
	}
#endif /* COMPAT_43 */
E 39
	if (!*argv) {
D 26
		if ((mntsize = getfsstat(0, 0)) < 0) {
			perror("df");
			exit(1);
		}
		mntbuf = 0;
		do {
			if (mntbuf)
				free(mntbuf);
			i = (mntsize + 1) * sizeof(struct statfs);
			if ((mntbuf = (struct statfs *)malloc(i)) == 0) {
				fprintf(stderr,
					"no space for mount table buffer\n");
				exit(1);
			}
			if ((mntsize = getfsstat(mntbuf, i)) < 0) {
				perror("df");
				exit(1);
			}
		} while (i == mntsize * sizeof(struct statfs));
E 26
I 26
D 33
		mntsize = getmntinfo(&mntbuf);
E 33
I 33
D 53
		mntsize = getmntinfo(&mntbuf, (nflag ? MNT_NOWAIT : MNT_WAIT));
E 53
I 53
D 67
		if (!tflag)
			fsmask = MT_DEFAULT;
		mntsize = regetmntinfo(&mntbuf, mntsize, fsmask);
		if (fsmask != MT_ALL) {
E 67
I 67
		mntsize = regetmntinfo(&mntbuf, mntsize, vfslist);
		if (vfslist != NULL) {
E 67
			maxwidth = 0;
			for (i = 0; i < mntsize; i++) {
				width = strlen(mntbuf[i].f_mntfromname);
				if (width > maxwidth)
					maxwidth = width;
			}
		}
E 53
E 33
E 26
		for (i = 0; i < mntsize; i++)
D 34
			prtstat(&mntbuf[i]);
E 34
I 34
			prtstat(&mntbuf[i], maxwidth);
E 34
		exit(0);
	}
I 53

E 53
	for (; *argv; argv++) {
D 26
		if (statfs(*argv, &statfsbuf) < 0) {
			perror(*argv);
E 26
I 26
		if (stat(*argv, &stbuf) < 0) {
D 28
			if ((mntpt = getmntpt(*argv)) == 0)
E 28
I 28
			err = errno;
			if ((mntpt = getmntpt(*argv)) == 0) {
D 29
				errno = err;
				perror(*argv);
E 29
I 29
D 52
				fprintf(stderr, "df: %s: %s\n", *argv,
				    strerror(err));
E 52
I 52
				warn("%s", *argv);
E 52
E 29
E 28
				continue;
I 28
			}
I 39
		} else if ((stbuf.st_mode & S_IFMT) == S_IFCHR) {
			ufs_df(*argv, maxwidth);
			continue;
E 39
E 28
		} else if ((stbuf.st_mode & S_IFMT) == S_IFBLK) {
D 35
			if ((mntpt = getmntpt(*argv)) == 0)
E 35
I 35
			if ((mntpt = getmntpt(*argv)) == 0) {
E 35
I 27
D 29
				mntpt = "/tmp/.mnt";
E 29
I 29
D 33
				mntpt = mktemp("/df.XXXXXX");
E 33
I 33
D 42
				mntpt = mktemp("/tmp/df.XXXXXX");
E 42
I 42
				mntpt = mktemp(strdup("/tmp/df.XXXXXX"));
E 42
E 33
E 29
				mdev.fspec = *argv;
D 39
				if (!mkdir(mntpt) &&
D 36
				    !mount(MOUNT_UFS, mntpt, M_RDONLY, &mdev) &&
E 36
I 36
				    !mount(MOUNT_UFS, mntpt, MNT_RDONLY, &mdev) &&
E 36
				    !statfs(mntpt, &statfsbuf)) {
E 39
I 39
D 40
				if (mkdir(mntpt) != 0) {
E 40
I 40
				if (mkdir(mntpt, DEFFILEMODE) != 0) {
E 40
D 52
					fprintf(stderr, "df: %s: %s\n",
					    mntpt, strerror(errno));
E 52
I 52
					warn("%s", mntpt);
E 52
					continue;
				}
D 67
				if (mount(MOUNT_UFS, mntpt, MNT_RDONLY,
E 67
I 67
				if (mount("ufs", mntpt, MNT_RDONLY,
E 67
				    &mdev) != 0) {
					ufs_df(*argv, maxwidth);
					(void)rmdir(mntpt);
					continue;
				} else if (statfs(mntpt, &statfsbuf)) {
E 39
					statfsbuf.f_mntonname[0] = '\0';
D 34
					prtstat(&statfsbuf);
E 34
I 34
					prtstat(&statfsbuf, maxwidth);
E 34
D 29
				} else {
					perror(*argv);
				}
				umount(mntpt, MNT_NOFORCE);
				rmdir(mntpt);
E 29
I 29
				} else
D 52
					fprintf(stderr, "df: %s: %s\n",
					    *argv, strerror(errno));
E 52
I 52
					warn("%s", *argv);
E 52
D 31
				(void)umount(mntpt, MNT_NOFORCE);
E 31
I 31
D 51
				(void)unmount(mntpt, MNT_NOFORCE);
E 51
I 51
				(void)unmount(mntpt, 0);
E 51
E 31
				(void)rmdir(mntpt);
E 29
E 27
				continue;
I 35
			}
E 35
		} else
			mntpt = *argv;
I 33
		/*
		 * Statfs does not take a `wait' flag, so we cannot
		 * implement nflag here.
		 */
E 33
		if (statfs(mntpt, &statfsbuf) < 0) {
D 29
			perror(mntpt);
E 29
I 29
D 52
			fprintf(stderr,
			    "df: %s: %s\n", mntpt, strerror(errno));
E 52
I 52
			warn("%s", mntpt);
E 52
E 29
E 26
			continue;
		}
D 34
		prtstat(&statfsbuf);
E 34
I 34
		if (argc == 1)
			maxwidth = strlen(statfsbuf.f_mntfromname) + 1;
		prtstat(&statfsbuf, maxwidth);
E 34
	}
D 40
	exit(0);
E 40
I 40
	return (0);
E 40
}

I 29
D 32
long
E 29
I 26
getmntinfo(mntbufp)
	struct statfs **mntbufp;
{
	int i;
	static long mntsize;
	static struct statfs *mntbuf = 0;
	char *malloc();

	if (mntbuf) {
		*mntbufp = mntbuf;
		return (mntsize);
	}
	if ((mntsize = getfsstat((struct statfs *)0, 0)) < 0) {
		perror("df");
		exit(1);
	}
	mntbuf = 0;
	do {
		if (mntbuf)
			free((char *)mntbuf);
		i = (mntsize + 1) * sizeof(struct statfs);
		if ((mntbuf = (struct statfs *)malloc((unsigned)i)) == 0) {
			fprintf(stderr,
D 29
				"no space for mount table buffer\n");
E 29
I 29
			    "df: no space for mount table buffer\n");
E 29
			exit(1);
		}
		if ((mntsize = getfsstat(mntbuf, i)) < 0) {
			perror("df");
			exit(1);
		}
	} while (i == mntsize * sizeof(struct statfs));
	*mntbufp = mntbuf;
	return (mntsize);
}

E 32
char *
getmntpt(name)
	char *name;
{
	long mntsize, i;
	struct statfs *mntbuf;

D 33
	mntsize = getmntinfo(&mntbuf);
E 33
I 33
D 54
	mntsize = getmntinfo(&mntbuf, (nflag ? MNT_NOWAIT : MNT_WAIT));
E 54
I 54
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
E 54
E 33
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, name))
			return (mntbuf[i].f_mntonname);
	}
	return (0);
}

I 53
D 67
long
addtype(omask, str)
	long omask;
	char *str;
{
	struct typetab *tp;

	/*
	 * If it is one of our known types, add it to the current mask
	 */
	for (tp = typetab; tp->str; tp++)
		if (strcmp(str, tp->str) == 0)
			return (tp->types | (tflag ? omask : MT_NONE));
	/*
	 * See if it is the negation of one of the known values
	 */
	if (strlen(str) > 2 && str[0] == 'n' && str[1] == 'o')
		for (tp = typetab; tp->str; tp++)
			if (strcmp(str+2, tp->str) == 0)
				return (~tp->types & (tflag ? omask : MT_ALL));
D 64
	(void)fprintf(stderr, "df: unknown type `%s'\n", str);
	exit(1);
E 64
I 64
	errx(1, "unknown type `%s'", str);
E 64
}

E 67
E 53
E 26
/*
I 53
 * Make a pass over the filesystem info in ``mntbuf'' filtering out
D 67
 * filesystem types not in ``fsmask'' and possibly re-stating to get
E 67
I 67
 * filesystem types not in vfslist and possibly re-stating to get
E 67
 * current (not cached) info.  Returns the new count of valid statfs bufs.
 */
long
D 67
regetmntinfo(mntbufp, mntsize, fsmask)
E 67
I 67
regetmntinfo(mntbufp, mntsize, vfslist)
E 67
	struct statfs **mntbufp;
D 67
	long mntsize, fsmask;
E 67
I 67
	long mntsize;
	char **vfslist;
E 67
{
D 64
	register int i, j;
	register struct statfs *mntbuf;
E 64
I 64
	int i, j;
	struct statfs *mntbuf;
E 64

D 67
	if (fsmask == MT_ALL)
E 67
I 67
	if (vfslist == NULL)
E 67
		return (nflag ? mntsize : getmntinfo(mntbufp, MNT_WAIT));

	mntbuf = *mntbufp;
D 67
	j = 0;
	for (i = 0; i < mntsize; i++) {
		if (fsmask & MT(mntbuf[i].f_type)) {
			if (!nflag)
				(void)statfs(mntbuf[i].f_mntonname,&mntbuf[j]);
			else if (i != j)
				mntbuf[j] = mntbuf[i];
			j++;
		}
E 67
I 67
	for (j = 0, i = 0; i < mntsize; i++) {
		if (checkvfsname(mntbuf[i].f_fstypename, vfslist))
			continue;
		if (!nflag)
			(void)statfs(mntbuf[i].f_mntonname,&mntbuf[j]);
		else if (i != j)
			mntbuf[j] = mntbuf[i];
		j++;
E 67
	}
	return (j);
}

/*
 * Convert statfs returned filesystem size into BLOCKSIZE units.
 * Attempts to avoid overflow for large filesystems.
 */
#define fsbtoblk(num, fsbs, bs) \
	(((fsbs) != 0 && (fsbs) < (bs)) ? \
		(num) / ((bs) / (fsbs)) : (num) * ((fsbs) / (bs)))

/*
E 53
 * Print out status about a filesystem.
 */
I 40
void
E 40
D 34
prtstat(sfsp)
E 34
I 34
prtstat(sfsp, maxwidth)
E 34
D 64
	register struct statfs *sfsp;
E 64
I 64
	struct statfs *sfsp;
E 64
I 34
D 52
	long maxwidth;
E 52
I 52
	int maxwidth;
E 52
E 34
{
I 47
D 48
	static int blocksize, headerlen, timesthrough;
E 48
I 48
	static long blocksize;
	static int headerlen, timesthrough;
E 48
	static char *header;
E 47
	long used, availblks, inodes;
I 34
D 47
	static int timesthrough;
E 47
E 34

D 34
	printf("%-12.12s", sfsp->f_mntfromname);
E 34
I 34
	if (maxwidth < 11)
		maxwidth = 11;
	if (++timesthrough == 1) {
D 43
		printf("%-*.*s%s    used   avail capacity",
E 43
I 43
D 47
		printf("%-*.*s%s    Used   Avail Capacity",
E 43
		    maxwidth, maxwidth, "Filesystem",
D 43
		    kflag ? "  kbytes" : "512-blks");
E 43
I 43
		    kflag ? "1024-blocks" : " 512-blocks");
E 47
I 47
D 53
		header = getbsize("df", &headerlen, &blocksize);
		(void)printf("%-*.*s %s    Used   Avail Capacity",
E 53
I 53
		header = getbsize(&headerlen, &blocksize);
		(void)printf("%-*.*s %s     Used    Avail Capacity",
E 53
		    maxwidth, maxwidth, "Filesystem", header);
E 47
E 43
		if (iflag)
D 47
			printf(" iused   ifree  %%iused");
		printf("  Mounted on\n");
E 47
I 47
			(void)printf(" iused   ifree  %%iused");
		(void)printf("  Mounted on\n");
E 47
	}
D 47
	printf("%-*.*s", maxwidth, maxwidth, sfsp->f_mntfromname);
E 47
I 47
	(void)printf("%-*.*s", maxwidth, maxwidth, sfsp->f_mntfromname);
E 47
E 34
	used = sfsp->f_blocks - sfsp->f_bfree;
	availblks = sfsp->f_bavail + used;
D 29
	printf("%8ld%8ld%8ld", sfsp->f_blocks * sfsp->f_fsize / 1024,
	    used * sfsp->f_fsize / 1024, sfsp->f_bavail * sfsp->f_fsize / 1024);
E 29
I 29
D 43
	printf("%8ld%8ld%8ld",
E 43
I 43
D 47
	printf("   %8ld%8ld%8ld",
E 43
D 46
	    sfsp->f_blocks * sfsp->f_fsize / (kflag ? 1024 : 512),
	    used * sfsp->f_fsize / (kflag ? 1024 : 512),
	    sfsp->f_bavail * sfsp->f_fsize / (kflag ? 1024 : 512));
E 46
I 46
	    sfsp->f_blocks * sfsp->f_bsize / (kflag ? 1024 : 512),
	    used * sfsp->f_bsize / (kflag ? 1024 : 512),
	    sfsp->f_bavail * sfsp->f_bsize / (kflag ? 1024 : 512));
E 46
E 29
	printf("%6.0f%%",
E 47
I 47
D 49
	(void)printf(" %*ld%8ld%8ld", headerlen,
E 49
I 49
D 53
	(void)printf(" %*ld %7ld %7ld", headerlen,
E 49
	    sfsp->f_blocks * sfsp->f_bsize / blocksize,
	    used * sfsp->f_bsize / blocksize,
	    sfsp->f_bavail * sfsp->f_bsize / blocksize);
E 53
I 53
	(void)printf(" %*ld %8ld %8ld", headerlen,
	    fsbtoblk(sfsp->f_blocks, sfsp->f_bsize, blocksize),
	    fsbtoblk(used, sfsp->f_bsize, blocksize),
	    fsbtoblk(sfsp->f_bavail, sfsp->f_bsize, blocksize));
E 53
D 49
	(void)printf("%6.0f%%",
E 49
I 49
	(void)printf(" %5.0f%%",
E 49
E 47
	    availblks == 0 ? 100.0 : (double)used / (double)availblks * 100.0);
	if (iflag) {
		inodes = sfsp->f_files;
		used = inodes - sfsp->f_ffree;
D 47
		printf("%8ld%8ld%6.0f%% ", used, sfsp->f_ffree,
E 47
I 47
D 49
		(void)printf("%8ld%8ld%6.0f%% ", used, sfsp->f_ffree,
E 49
I 49
		(void)printf(" %7ld %7ld %5.0f%% ", used, sfsp->f_ffree,
E 49
E 47
		   inodes == 0 ? 100.0 : (double)used / (double)inodes * 100.0);
	} else 
D 47
		printf("  ");
	printf("  %s\n", sfsp->f_mntonname);
E 47
I 47
		(void)printf("  ");
	(void)printf("  %s\n", sfsp->f_mntonname);
E 47
}

D 39
#ifdef COMPAT_43
E 39
/*
D 50
 * This code constitutes the old df code for extracting
E 50
I 50
 * This code constitutes the pre-system call Berkeley df code for extracting
E 50
 * information from filesystem superblocks.
 */
I 67
#include <ufs/ufs/dinode.h>
E 67
D 29
#include <sys/param.h>
E 29
D 45
#include <ufs/fs.h>
E 45
I 45
#include <ufs/ffs/fs.h>
E 45
D 26
#include <sys/stat.h>
E 26
#include <errno.h>
#include <fstab.h>
D 26
#include <mtab.h>
E 26

D 26
struct	mtab mtab[NMOUNT];
E 26
D 29
char	root[32];
E 29
I 29
D 39
char	root[MAXPATHLEN];
E 29
D 26
char	*mpath();
E 26

E 39
union {
	struct fs iu_fs;
	char dummy[SBSIZE];
} sb;
#define sblock sb.iu_fs

D 50
int	fi;
E 50
I 50
int	rfd;
E 50
D 40
char	*strcpy();
E 40
I 40
D 43
int	bread();
E 43
E 40

I 40
void
E 40
D 34
olddf(argv)
E 34
I 34
D 39
olddf(argv, maxwidth)
E 34
	char *argv[];
I 34
	long maxwidth;
E 34
{
	struct fstab *fsp;
D 29
	char *strerror();
E 29
D 26
	int i;
E 26

E 25
D 26
	if ((i = open(_PATH_MTAB, 0)) < 0) {
D 25
		fprintf(stderr, "df: %s: %s\n", _PATH_MTAB, strerror(errno));
E 25
I 25
		fprintf(stderr, "df: %s: %s\n", _PATH_MTAB,
			strerror(errno));
E 25
		exit(1);
E 22
E 17
E 8
	}
D 8

	if ((i=open("/etc/mtab", 0)) >= 0) {
E 8
I 8
D 17
	argc--, argv++;
	}
E 17
D 22
	i = open("/etc/mtab", 0);
	if (i >= 0) {
E 8
D 12
		read(i, mtab, sizeof mtab);	/* Probably returns short */
		close(i);
E 12
I 12
D 17
		(void) read(i, (char *)mtab, sizeof mtab);
E 17
I 17
		(void) read(i, (char *)mtab, sizeof (mtab));
E 17
		(void) close(i);
E 12
	}
E 22
I 22
	(void) read(i, (char *)mtab, sizeof (mtab));
	(void) close(i);
E 26
E 22
I 13
	sync();
E 13
D 5
	printf("Filesystem  Mounted on  blocks\t  used\t  free");
E 5
I 5
D 8
	printf("Filesystem  Mounted on  kbytes\t  used\t  free");
E 5
	if (lflag)
		printf("\thardway");
	printf("\t%% used");
E 8
I 8
D 12
	printf("Filesystem  Mounted on      kbytes    used    free");
	printf("   %% used");
E 12
I 12
D 25
	printf("Filesystem    kbytes    used   avail capacity");
E 12
E 8
	if (iflag)
D 8
		printf("\tiused\tifree\t%%iused");
E 8
I 8
D 12
		printf("   iused   ifree  %%iused");
E 8
	putchar('\n');
E 12
I 12
		printf(" iused   ifree  %%iused");
	printf("  Mounted on\n");
E 25
E 12
D 8
	if(argc <= 1) {
D 3
		if (f == NULL)
E 3
I 3
		struct	fstab	*fsp;
E 8
I 8
D 22
	if (argc <= 1) {
E 22
I 22
	if (!*argv) {
E 22
D 25
		struct fstab *fsp;

E 25
E 8
		if (setfsent() == 0)
E 3
D 24
			perror(FSTAB), exit(1);
E 24
I 24
			perror(_PATH_FSTAB), exit(1);
E 24
D 3
		while (!feof(f)){
			fscanf(f, FSTABFMT, FSTABARG(&fs));
I 2
			if (strcmp(fs.fs_type, "rw") && strcmp(fs.fs_type, "ro"))
E 3
I 3
D 8
		while( (fsp = getfsent()) != 0){
			if (  (strcmp(fsp->fs_type, FSTAB_RW) != 0)
			    &&(strcmp(fsp->fs_type, FSTAB_RO) != 0) )
E 8
I 8
		while (fsp = getfsent()) {
D 10
			if (!strcmp(fsp->fs_type, FSTAB_RW) &&
			    !(strcmp(fsp->fs_type, FSTAB_RO)))
E 10
I 10
D 12
			if (strcmp(fsp->fs_type, FSTAB_RW) &&
			    strcmp(fsp->fs_type, FSTAB_RO))
E 12
I 12
D 15
			if (!strcmp(fsp->fs_type, FSTAB_RW) &&
			    !(strcmp(fsp->fs_type, FSTAB_RO)))
E 15
I 15
			if (strcmp(fsp->fs_type, FSTAB_RW) &&
D 16
			    strcmp(fsp->fs_type, FSTAB_RO))
E 16
I 16
			    strcmp(fsp->fs_type, FSTAB_RO) &&
			    strcmp(fsp->fs_type, FSTAB_RQ))
E 16
E 15
E 12
E 10
E 8
E 3
				continue;
E 2
			if (root[0] == 0)
D 3
				strcpy(root, fs.fs_spec);
			dfree(fs.fs_spec);
E 3
I 3
D 12
				strcpy(root, fsp->fs_spec);
E 12
I 12
				(void) strcpy(root, fsp->fs_spec);
E 12
D 8
			dfree(fsp->fs_spec);
E 8
I 8
D 34
			dfree(fsp->fs_spec, 1);
E 34
I 34
			dfree(fsp->fs_spec, 1, maxwidth);
E 34
E 8
E 3
		}
I 3
D 20
		endfsent();
E 20
I 20
		(void)endfsent();
E 20
E 3
		exit(0);
	}
D 8

D 3
	if (f){
		fscanf(f, FSTABFMT, FSTABARG(&fs));
		strcpy(root, fs.fs_spec);
	}
E 3
	for(i=1; i<argc; i++) {
		dfree(argv[i]);
	}
E 8
I 8
D 22
	for (i=1; i<argc; i++)
		dfree(argv[i], 0);
E 22
I 22
	while (*argv)
D 34
		dfree(*argv++, 0);
E 34
I 34
		dfree(*argv++, 0, maxwidth);
E 34
I 25
	exit(0);
E 25
E 22
E 8
}

D 8
dfree(file)
char *file;
E 8
I 8
D 34
dfree(file, infsent)
E 34
I 34
dfree(file, infsent, maxwidth)
E 39
I 39
ufs_df(file, maxwidth)
E 39
E 34
	char *file;
D 39
	int infsent;
E 39
I 34
D 52
	long maxwidth;
E 52
I 52
	int maxwidth;
E 52
E 34
E 8
{
I 22
D 47
	extern int errno;
E 47
E 22
D 12
	daddr_t i;
D 8
	long	blocks;
	long	free;
	long	used;
	long	hardway;
	char	*mp;
I 3
	struct	stat stbuf;
E 8
I 8
	long blocks, free, used, hardway;
	char *mp;
E 12
I 12
D 25
	long totalblks, availblks, avail, free, used;
E 25
E 12
D 40
	struct stat stbuf;
E 40
I 25
	struct statfs statfsbuf;
D 64
	register struct statfs *sfsp;
E 64
I 64
	struct statfs *sfsp;
E 64
E 25
D 40
	struct fstab *fsp;
E 40
I 22
D 26
	char *strerror();
E 26
I 26
D 29
	char *mntpt, *strerror();
E 29
I 29
	char *mntpt;
I 39
	static int synced;
E 39
E 29
E 26
E 22
E 8
E 3

I 3
D 8
	if(stat(file, &stbuf) == 0 && (stbuf.st_mode&S_IFMT) != S_IFCHR
	  && (stbuf.st_mode&S_IFMT) != S_IFBLK) {
		int mt = open("/etc/mtab", 0), len;
		char *str = "/dev/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		char mtab[32];
		struct stat mstbuf;
		while((len = read(mt, mtab, 32)) == 32) {
			read(mt, &str[5], 32);
			if(stat(str, &mstbuf) == 0 && mstbuf.st_rdev == stbuf.st_dev) {
				file = str;
				break;
			}
		}
		close(mt);
		if(len == 0) {
			fprintf(stderr, "%s: mounted on unknown device\n", file);
E 8
I 8
D 39
	if (stat(file, &stbuf) == 0 &&
	    (stbuf.st_mode&S_IFMT) != S_IFCHR &&
	    (stbuf.st_mode&S_IFMT) != S_IFBLK) {
		if (infsent) {
D 23
			fprintf(stderr, "%s: screwy /etc/fstab entry\n", file);
E 23
I 23
D 29
			fprintf(stderr, "%s: screwy fstab entry\n", file);
E 29
I 29
			fprintf(stderr, "df: %s: screwy fstab entry\n", file);
E 29
E 23
E 8
			return;
		}
I 8
D 20
		setfsent();
E 20
I 20
		(void)setfsent();
E 20
		while (fsp = getfsent()) {
			struct stat stb;
E 39
I 39
	if (synced++ == 0)
		sync();
E 39

D 39
			if (stat(fsp->fs_spec, &stb) == 0 &&
			    stb.st_rdev == stbuf.st_dev) {
				file = fsp->fs_spec;
D 20
				endfsent();
E 20
I 20
				(void)endfsent();
E 20
				goto found;
			}
		}
D 20
		endfsent();
E 20
I 20
		(void)endfsent();
E 20
D 29
		fprintf(stderr, "%s: mounted on unknown device\n", file);
E 29
I 29
		fprintf(stderr, "df: %s: mounted on unknown device\n", file);
E 29
		return;
E 8
	}
I 8
found:
E 39
E 8
E 3
D 22
	fi = open(file, 0);
D 8
	if(fi < 0) {
		fprintf(stderr,"cannot open %s\n", file);
E 8
I 8
	if (fi < 0) {
		perror(file);
E 22
I 22
D 29
	if ((fi = open(file, 0)) < 0) {
E 29
I 29
D 50
	if ((fi = open(file, O_RDONLY)) < 0) {
E 50
I 50
	if ((rfd = open(file, O_RDONLY)) < 0) {
E 50
E 29
D 47
		fprintf(stderr, "df: %s: %s\n", file, strerror(errno));
E 47
I 47
D 52
		(void)fprintf(stderr, "df: %s: %s\n", file, strerror(errno));
E 52
I 52
		warn("%s", file);
E 52
E 47
E 22
E 8
		return;
	}
D 6
	sync();
E 6
I 6
D 8
	if (lflag)
		sync();
E 6
	bread(1L, (char *)&sblock, sizeof(sblock));
	printf("%-12.12s%s", file, mp = mpath(file));
	if (strlen(mp) < 4)
		putchar('\t');

E 8
I 8
D 12
	bread((long) 1, (char *)&sblock, sizeof (sblock));
	printf("%-12.12s%-14.14s", file, mp = mpath(file));
E 8
	blocks = (long) sblock.s_fsize - (long)sblock.s_isize;
	free = sblock.s_tfree;
	used = blocks - free;
D 8

	printf("\t%6ld", blocks);
	printf("\t%6ld", used);
	printf("\t%6ld", free);
	if (lflag) {
		hardway = 0;
		while(alloc())
			hardway++;
		printf("\t%6ld", free=hardway);
	}
D 4
	printf("\t%5.0f%%", (double) used / (double)blocks * 100.0);
E 4
I 4
	printf("\t%5.0f%%", 
E 8
I 8
	printf("%8d%8d%8d", blocks, used, free);
	printf("%8.0f%%", 
E 8
	    blocks == 0 ? 0.0 : (double) used / (double)blocks * 100.0);
E 12
I 12
D 18
	bread(SBLOCK, (char *)&sblock, SBSIZE);
E 18
I 18
D 20
	if (bread(SBLOCK, (char *)&sblock, SBSIZE) == 0) {
E 20
I 20
D 50
	if (bread((long)SBOFF, (char *)&sblock, SBSIZE) == 0) {
E 20
D 47
		(void) close(fi);
E 47
I 47
		(void)close(fi);
E 50
I 50
	if (bread((off_t)SBOFF, &sblock, SBSIZE) == 0) {
		(void)close(rfd);
E 50
E 47
		return;
	}
E 18
D 25
	printf("%-12.12s", file);
	totalblks = sblock.fs_dsize;
	free = sblock.fs_cstotal.cs_nbfree * sblock.fs_frag +
	    sblock.fs_cstotal.cs_nffree;
	used = totalblks - free;
	availblks = totalblks * (100 - sblock.fs_minfree) / 100;
	avail = availblks > used ? availblks - used : 0;
D 22
	printf("%8d%8d%8d", totalblks * sblock.fs_fsize / 1024,
E 22
I 22
	printf("%8ld%8ld%8ld", totalblks * sblock.fs_fsize / 1024,
E 22
	    used * sblock.fs_fsize / 1024, avail * sblock.fs_fsize / 1024);
	printf("%6.0f%%",
	    availblks == 0 ? 0.0 : (double) used / (double) availblks * 100.0);
E 12
E 4
	if (iflag) {
D 12
		int inodes = (sblock.s_isize - 2) * INOPB;
		used = inodes - sblock.s_tinode;
D 4
		printf("\t%5ld\t%5ld\t%5.0f%%", used, sblock.s_tinode, (double)used/(double)inodes*100.0);
E 4
I 4
D 8
		printf("\t%5ld\t%5ld\t%5.0f%%", used, sblock.s_tinode, 
E 8
I 8
		printf("%8ld%8ld%8.0f%%", used, sblock.s_tinode, 
E 8
		    inodes == 0 ? 0.0 : (double)used/(double)inodes*100.0);
E 4
	}
	printf("\n");
	close(fi);
E 12
I 12
		int inodes = sblock.fs_ncg * sblock.fs_ipg;
		used = inodes - sblock.fs_cstotal.cs_nifree;
		printf("%8ld%8ld%6.0f%% ", used, sblock.fs_cstotal.cs_nifree,
		    inodes == 0 ? 0.0 : (double)used / (double)inodes * 100.0);
	} else 
		printf("  ");
	printf("  %s\n", mpath(file));
E 25
I 25
	sfsp = &statfsbuf;
D 67
	sfsp->f_type = MOUNT_UFS;
E 67
I 67
	sfsp->f_type = 1;
	strcpy(sfsp->f_fstypename, "ufs");
E 67
	sfsp->f_flags = 0;
D 46
	sfsp->f_fsize = sblock.fs_fsize;
	sfsp->f_bsize = sblock.fs_bsize;
E 46
I 46
	sfsp->f_bsize = sblock.fs_fsize;
	sfsp->f_iosize = sblock.fs_bsize;
E 46
	sfsp->f_blocks = sblock.fs_dsize;
	sfsp->f_bfree = sblock.fs_cstotal.cs_nbfree * sblock.fs_frag +
		sblock.fs_cstotal.cs_nffree;
	sfsp->f_bavail = (sblock.fs_dsize * (100 - sblock.fs_minfree) / 100) -
		(sblock.fs_dsize - sfsp->f_bfree);
	if (sfsp->f_bavail < 0)
		sfsp->f_bavail = 0;
	sfsp->f_files =  sblock.fs_ncg * sblock.fs_ipg;
	sfsp->f_ffree = sblock.fs_cstotal.cs_nifree;
	sfsp->f_fsid.val[0] = 0;
	sfsp->f_fsid.val[1] = 0;
D 26
	bcopy((caddr_t)mpath(file), (caddr_t)&sfsp->f_mntonname[0], MNAMELEN);
E 26
I 26
	if ((mntpt = getmntpt(file)) == 0)
		mntpt = "";
D 52
	bcopy((caddr_t)mntpt, (caddr_t)&sfsp->f_mntonname[0], MNAMELEN);
E 26
	bcopy((caddr_t)file, (caddr_t)&sfsp->f_mntfromname[0], MNAMELEN);
E 52
I 52
	memmove(&sfsp->f_mntonname[0], mntpt, MNAMELEN);
	memmove(&sfsp->f_mntfromname[0], file, MNAMELEN);
E 52
D 34
	prtstat(sfsp);
E 34
I 34
	prtstat(sfsp, maxwidth);
E 34
E 25
D 50
	(void) close(fi);
E 50
I 50
	(void)close(rfd);
E 50
E 12
}

I 12
D 43
long lseek();

E 43
I 40
int
E 40
E 12
D 8
daddr_t
alloc()
{
	int i;
	daddr_t b;
	struct fblk buf;

	i = --sblock.s_nfree;
	if(i<0 || i>=NICFREE) {
		printf("bad free count, b=%D\n", blkno);
		return(0);
	}
	b = sblock.s_free[i];
	if(b == 0)
		return(0);
	if(b<sblock.s_isize || b>=sblock.s_fsize) {
		printf("bad free block (%D)\n", b);
		return(0);
	}
	if(sblock.s_nfree <= 0) {
		bread(b, (char *)&buf, sizeof(buf));
		blkno = b;
		sblock.s_nfree = buf.df_nfree;
		for(i=0; i<NICFREE; i++)
			sblock.s_free[i] = buf.df_free[i];
	}
	return(b);
}

E 8
D 20
bread(bno, buf, cnt)
D 8
daddr_t bno;
char *buf;
E 8
I 8
	daddr_t bno;
E 20
I 20
bread(off, buf, cnt)
D 50
	long off;
E 20
	char *buf;
E 50
I 50
	off_t off;
	void *buf;
E 50
I 40
	int cnt;
E 40
E 8
{
D 50
	int n;
E 50
I 50
	int nr;
E 50
D 43
	extern errno;
E 43

D 12
	lseek(fi, bno<<BSHIFT, 0);
E 12
I 12
D 20
	(void) lseek(fi, (long)(bno * DEV_BSIZE), 0);
E 20
I 20
D 29
	(void) lseek(fi, off, 0);
E 29
I 29
D 50
	(void) lseek(fi, off, SEEK_SET);
E 29
E 20
E 12
D 8
	if((n=read(fi, buf, cnt)) != cnt) {
E 8
I 8
	if ((n=read(fi, buf, cnt)) != cnt) {
E 8
D 18
		printf("\nread error bno = %ld\n", bno);
		printf("count = %d; errno = %d\n", n, errno);
		exit(0);
E 18
I 18
		/* probably a dismounted disk if errno == EIO */
		if (errno != EIO) {
D 20
			printf("\nread error bno = %ld\n", bno);
E 20
I 20
D 47
			printf("\nread error off = %ld\n", off);
E 20
			printf("count = %d; errno = %d\n", n, errno);
E 47
I 47
			(void)printf("\nread error off = %ld\n", off);
			(void)printf("count = %d: %s\n", n, strerror(errno));
E 47
		}
E 50
I 50
	(void)lseek(rfd, off, SEEK_SET);
	if ((nr = read(rfd, buf, cnt)) != cnt) {
		/* Probably a dismounted disk if errno == EIO. */
		if (errno != EIO)
			(void)fprintf(stderr, "\ndf: %qd: %s\n",
			    off, strerror(nr > 0 ? EIO : errno));
E 50
		return (0);
E 18
	}
I 18
	return (1);
I 43
}

void
usage()
{
D 47
	(void)fprintf(stderr, "usage: df [-ikn] [file | file_system ...]\n");
E 47
I 47
D 66
	(void)fprintf(stderr, "usage: df [-in] [file | file_system ...]\n");
E 66
I 66
	(void)fprintf(stderr,
	    "usage: df [-in] [-t type] [file | file_system ...]\n");
E 66
E 47
	exit(1);
E 43
E 18
D 26
}

/*
 * Given a name like /dev/rrp0h, returns the mounted path, like /usr.
 */
D 17
char *mpath(file)
E 17
I 17
char *
mpath(file)
E 17
D 8
char *file;
E 8
I 8
	char *file;
E 8
{
D 17
	register int i;
E 17
I 17
	register struct mtab *mp;
E 17

	if (eq(file, root))
D 17
		return "/";
	for (i=0; i<NFS; i++)
		if (eq(file, mtab[i].spec))
D 8
			return mtab[i].path;
E 8
I 8
			return (mtab[i].path);
E 17
I 17
		return ("/");
	for (mp = mtab; mp < mtab + NMOUNT; mp++)
		if (eq(file, mp->m_dname))
			return (mp->m_path);
E 17
E 8
	return "";
}

eq(f1, f2)
D 8
char *f1, *f2;
E 8
I 8
	char *f1, *f2;
E 8
{
I 8

E 8
D 23
	if (strncmp(f1, "/dev/", 5) == 0)
E 23
I 23
	if (strncmp(f1, _PATH_DEV, sizeof(_PATH_DEV) - 1) == 0)
E 23
		f1 += 5;
D 23
	if (strncmp(f2, "/dev/", 5) == 0)
E 23
I 23
	if (strncmp(f2, _PATH_DEV, sizeof(_PATH_DEV) - 1) == 0)
E 23
		f2 += 5;
D 8
	if (strcmp(f1, f2) == 0)
		return 1;
	if (*f1 == 'r' && strcmp(f1+1, f2) == 0)
		return 1;
	if (*f2 == 'r' && strcmp(f1, f2+1) == 0)
		return 1;
E 8
I 8
	if (!strcmp(f1, f2))
		return (1);
	if (*f1 == 'r' && !strcmp(f1+1, f2))
		return (1);
	if (*f2 == 'r' && !strcmp(f1, f2+1))
		return (1);
E 8
	if (*f1 == 'r' && *f2 == 'r' && strcmp(f1+1, f2+1) == 0)
D 8
		return 1;
	return 0;
E 8
I 8
		return (1);
	return (0);
E 26
E 8
}
I 25
D 39
#endif /* COMPAT_43 */
E 39
E 25
E 1
