h03898
s 00050/00007/00251
d D 8.3 95/05/03 13:44:17 mckusick 23 22
c add -t (track skew) and -N (just list current settings)
e
s 00078/00082/00180
d D 8.2 94/04/19 00:00:22 mckusick 22 21
c cleanups from cgd
e
s 00005/00005/00257
d D 8.1 93/06/05 11:25:53 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00259
d D 5.16 93/02/15 10:46:44 ralph 20 19
c use unistd.h to declare lseek properly.
e
s 00002/00002/00259
d D 5.15 92/09/07 20:08:22 hibler 19 18
c cast SBOFF to daddr_t (from 8-byte off_t)
e
s 00003/00000/00258
d D 5.14 92/07/24 12:12:47 bostic 18 17
c needs errno.h
e
s 00003/00005/00255
d D 5.13 92/07/24 12:11:32 bostic 17 16
c add space after message, before perror stuff
e
s 00001/00001/00259
d D 5.12 91/11/11 11:38:25 bostic 16 15
c break UFS up into FFS/UFS/LFS/MFS
e
s 00001/00011/00259
d D 5.11 90/06/01 16:30:21 bostic 15 14
c new copyright notice
e
s 00000/00003/00270
d D 5.10 90/05/04 12:45:41 mckusick 14 13
c delete unneeded headers
e
s 00004/00002/00269
d D 5.9 89/07/30 11:01:06 bostic 13 12
c vnodes
e
s 00003/00003/00268
d D 5.8 89/05/11 14:02:16 bostic 12 11
c file reorg, pathnames.h, paths.h
e
s 00017/00007/00254
d D 5.7 88/09/12 22:26:48 bostic 11 10
c Berkeley code; add appropriate copyright notice
e
s 00000/00002/00261
d D 5.6 88/01/03 19:25:31 mckusick 10 9
c allow negative rotational delays (for torek)
e
s 00002/00002/00261
d D 5.5 87/10/22 10:51:09 bostic 9 8
c ANSI C; sprintf now returns an int.
e
s 00006/00004/00257
d D 5.4 87/02/23 17:40:09 mckusick 8 7
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00012/00000/00249
d D 5.3 85/09/11 23:34:13 mckusick 7 6
c add warnings relating to optimization
e
s 00029/00002/00220
d D 5.2 85/09/11 22:31:23 mckusick 6 5
c allow users to specify optimization preference
e
s 00014/00002/00208
d D 5.1 85/05/28 15:41:47 dist 5 4
c Add copyright
e
s 00001/00001/00209
d D 4.4 83/07/01 03:19:52 sam 4 3
c correct spelling 
e
s 00007/00001/00203
d D 4.3 83/06/14 22:19:06 sam 3 2
c take file system names as well
e
s 00001/00001/00203
d D 4.2 83/02/26 13:24:07 sam 2 1
c oversight
e
s 00204/00000/00000
d D 4.1 83/02/26 00:19:48 mckusick 1 0
c date and time created 83/02/26 00:19:48 by mckusick
e
u
U
t
T
I 5
/*
D 11
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 21
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
 */

E 5
I 1
#ifndef lint
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
#endif lint
E 5
I 5
D 21
char copyright[] =
D 11
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 21
I 21
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 21
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 5

/*
 * tunefs: change layout parameters to an existing file system.
 */
D 11

E 11
D 3
#include <stdio.h>
E 3
#include <sys/param.h>
#include <sys/stat.h>
I 18

I 23
#include <ufs/ufs/dinode.h>
E 23
E 18
D 13
#include <sys/fs.h>
#include <sys/inode.h>
E 13
I 13
D 14
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 14
D 16
#include <ufs/fs.h>
E 16
I 16
#include <ufs/ffs/fs.h>
I 18

I 20
D 22
#include <unistd.h>
E 22
E 20
#include <errno.h>
I 22
#include <err.h>
#include <fcntl.h>
E 22
E 18
E 16
E 13
D 12

I 3
#include <stdio.h>
E 12
#include <fstab.h>
I 12
#include <stdio.h>
#include <paths.h>
I 22
#include <stdlib.h>
#include <unistd.h>
E 22
E 12

I 22
/* the optimization warning string template */
#define	OPTWARN	"should optimize for %s with minfree %s %d%%"

E 22
E 3
union {
	struct	fs sb;
	char pad[MAXBSIZE];
} sbun;
#define	sblock sbun.sb

int fi;
I 8
long dev_bsize = 1;
E 8

I 22
void bwrite(daddr_t, char *, int);
int bread(daddr_t, char *, int);
void getsb(struct fs *, char *);
void usage __P((void));

int
E 22
main(argc, argv)
	int argc;
	char *argv[];
{
	char *cp, *special, *name;
	struct stat st;
	int i;
D 23
	int Aflag = 0;
E 23
I 23
	int Aflag = 0, Nflag = 0;
E 23
D 6
	char device[MAXPATHLEN];
	extern char *sprintf();
E 6
I 3
	struct fstab *fs;
I 6
	char *chg[2], device[MAXPATHLEN];
D 9
	extern char *sprintf();
E 9
E 6
E 3

	argc--, argv++; 
	if (argc < 2)
D 22
		goto usage;
E 22
I 22
		usage();
E 22
	special = argv[argc - 1];
I 3
	fs = getfsfile(special);
	if (fs)
		special = fs->fs_spec;
E 3
again:
	if (stat(special, &st) < 0) {
		if (*special != '/') {
			if (*special == 'r')
				special++;
D 9
			special = sprintf(device, "/dev/%s", special);
E 9
I 9
D 12
			(void)sprintf(device, "/dev/%s", special);
E 12
I 12
			(void)sprintf(device, "%s/%s", _PATH_DEV, special);
E 12
			special = device;
E 9
			goto again;
		}
D 22
		fprintf(stderr, "tunefs: "); perror(special);
		exit(1);
E 22
I 22
		err(1, "%s", special);
E 22
	}
	if ((st.st_mode & S_IFMT) != S_IFBLK &&
	    (st.st_mode & S_IFMT) != S_IFCHR)
D 22
		fatal("%s: not a block or character device", special);
E 22
I 22
		errx(10, "%s: not a block or character device", special);
E 22
	getsb(&sblock, special);
I 23
	chg[FS_OPTSPACE] = "space";
	chg[FS_OPTTIME] = "time";
E 23
	for (; argc > 0 && argv[0][0] == '-'; argc--, argv++) {
		for (cp = &argv[0][1]; *cp; cp++)
			switch (*cp) {

			case 'A':
				Aflag++;
				continue;

I 23
			case 'N':
				Nflag++;
				continue;

E 23
			case 'a':
				name = "maximum contiguous block count";
				if (argc < 1)
D 22
					fatal("-a: missing %s", name);
E 22
I 22
					errx(10, "-a: missing %s", name);
E 22
				argc--, argv++;
				i = atoi(*argv);
				if (i < 1)
D 22
					fatal("%s: %s must be >= 1",
						*argv, name);
				fprintf(stdout, "%s changes from %d to %d\n",
					name, sblock.fs_maxcontig, i);
E 22
I 22
					errx(10, "%s must be >= 1 (was %s)",
					    name, *argv);
				warnx("%s changes from %d to %d",
				    name, sblock.fs_maxcontig, i);
E 22
				sblock.fs_maxcontig = i;
				continue;

			case 'd':
				name =
				   "rotational delay between contiguous blocks";
				if (argc < 1)
D 22
					fatal("-d: missing %s", name);
E 22
I 22
					errx(10, "-d: missing %s", name);
E 22
				argc--, argv++;
				i = atoi(*argv);
D 10
				if (i < 0)
					fatal("%s: bad %s", *argv, name);
E 10
D 22
				fprintf(stdout,
					"%s changes from %dms to %dms\n",
					name, sblock.fs_rotdelay, i);
E 22
I 22
				warnx("%s changes from %dms to %dms",
				    name, sblock.fs_rotdelay, i);
E 22
				sblock.fs_rotdelay = i;
				continue;

			case 'e':
				name =
				  "maximum blocks per file in a cylinder group";
				if (argc < 1)
D 22
					fatal("-e: missing %s", name);
E 22
I 22
					errx(10, "-e: missing %s", name);
E 22
				argc--, argv++;
				i = atoi(*argv);
				if (i < 1)
D 22
					fatal("%s: %s must be >= 1",
						*argv, name);
				fprintf(stdout, "%s changes from %d to %d\n",
					name, sblock.fs_maxbpg, i);
E 22
I 22
					errx(10, "%s must be >= 1 (was %s)",
					    name, *argv);
				warnx("%s changes from %d to %d",
				    name, sblock.fs_maxbpg, i);
E 22
				sblock.fs_maxbpg = i;
				continue;

			case 'm':
				name = "minimum percentage of free space";
				if (argc < 1)
D 22
					fatal("-m: missing %s", name);
E 22
I 22
					errx(10, "-m: missing %s", name);
E 22
				argc--, argv++;
				i = atoi(*argv);
				if (i < 0 || i > 99)
D 22
					fatal("%s: bad %s", *argv, name);
				fprintf(stdout,
					"%s changes from %d%% to %d%%\n",
					name, sblock.fs_minfree, i);
E 22
I 22
					errx(10, "bad %s (%s)", name, *argv);
				warnx("%s changes from %d%% to %d%%",
				    name, sblock.fs_minfree, i);
E 22
				sblock.fs_minfree = i;
I 7
D 22
				if (i >= 10 && sblock.fs_optim == FS_OPTSPACE)
					fprintf(stdout, "should optimize %s",
					    "for time with minfree >= 10%\n");
				if (i < 10 && sblock.fs_optim == FS_OPTTIME)
					fprintf(stdout, "should optimize %s",
					    "for space with minfree < 10%\n");
E 22
I 22
				if (i >= MINFREE &&
				    sblock.fs_optim == FS_OPTSPACE)
					warnx(OPTWARN, "time", ">=", MINFREE);
				if (i < MINFREE &&
				    sblock.fs_optim == FS_OPTTIME)
					warnx(OPTWARN, "space", "<", MINFREE);
E 22
E 7
				continue;

I 6
			case 'o':
				name = "optimization preference";
				if (argc < 1)
D 22
					fatal("-o: missing %s", name);
E 22
I 22
					errx(10, "-o: missing %s", name);
E 22
				argc--, argv++;
D 23
				chg[FS_OPTSPACE] = "space";
				chg[FS_OPTTIME] = "time";
E 23
				if (strcmp(*argv, chg[FS_OPTSPACE]) == 0)
					i = FS_OPTSPACE;
				else if (strcmp(*argv, chg[FS_OPTTIME]) == 0)
					i = FS_OPTTIME;
				else
D 22
					fatal("%s: bad %s (options are `space' or `time')",
						*argv, name);
E 22
I 22
					errx(10, "bad %s (options are `space' or `time')",
					    name);
E 22
				if (sblock.fs_optim == i) {
D 22
					fprintf(stdout,
						"%s remains unchanged as %s\n",
						name, chg[i]);
E 22
I 22
					warnx("%s remains unchanged as %s",
					    name, chg[i]);
E 22
					continue;
				}
D 22
				fprintf(stdout,
					"%s changes from %s to %s\n",
					name, chg[sblock.fs_optim], chg[i]);
E 22
I 22
				warnx("%s changes from %s to %s",
				    name, chg[sblock.fs_optim], chg[i]);
E 22
				sblock.fs_optim = i;
I 7
D 22
				if (sblock.fs_minfree >= 10 && i == FS_OPTSPACE)
					fprintf(stdout, "should optimize %s",
					    "for time with minfree >= 10%\n");
				if (sblock.fs_minfree < 10 && i == FS_OPTTIME)
					fprintf(stdout, "should optimize %s",
					    "for space with minfree < 10%\n");
E 22
I 22
				if (sblock.fs_minfree >= MINFREE &&
				    i == FS_OPTSPACE)
					warnx(OPTWARN, "time", ">=", MINFREE);
				if (sblock.fs_minfree < MINFREE &&
				    i == FS_OPTTIME)
					warnx(OPTWARN, "space", "<", MINFREE);
E 22
E 7
				continue;

I 23
			case 't':
				name = "track skew in sectors";
				if (argc < 1)
					errx(10, "-t: missing %s", name);
				argc--, argv++;
				i = atoi(*argv);
				if (i < 0)
					errx(10, "%s: %s must be >= 0",
						*argv, name);
				warnx("%s changes from %d to %d",
					name, sblock.fs_trackskew, i);
				sblock.fs_trackskew = i;
				continue;

E 23
E 6
			default:
D 22
				fatal("-%c: unknown flag", *cp);
E 22
I 22
				usage();
E 22
			}
	}
	if (argc != 1)
D 22
		goto usage;
E 22
I 22
		usage();
I 23
	if (Nflag) {
		fprintf(stdout, "tunefs: current settings\n");
		fprintf(stdout, "\tmaximum contiguous block count %d\n",
		    sblock.fs_maxcontig);
		fprintf(stdout,
		    "\trotational delay between contiguous blocks %dms\n",
		    sblock.fs_rotdelay);
		fprintf(stdout,
		    "\tmaximum blocks per file in a cylinder group %d\n",
		    sblock.fs_maxbpg);
		fprintf(stdout, "\tminimum percentage of free space %d%%\n",
		    sblock.fs_minfree);
		fprintf(stdout, "\toptimization preference: %s\n",
		    chg[sblock.fs_optim]);
		fprintf(stdout, "\ttrack skew %d sectors\n",
			sblock.fs_trackskew);
		fprintf(stdout, "tunefs: no changes made\n");
		exit(0);
	}
	fi = open(special, 1);
	if (fi < 0)
		err(3, "cannot open %s for writing", special);
E 23
E 22
D 8
	bwrite(SBLOCK, (char *)&sblock, SBSIZE);
E 8
I 8
D 19
	bwrite(SBOFF / dev_bsize, (char *)&sblock, SBSIZE);
E 19
I 19
	bwrite((daddr_t)SBOFF / dev_bsize, (char *)&sblock, SBSIZE);
E 19
E 8
	if (Aflag)
		for (i = 0; i < sblock.fs_ncg; i++)
			bwrite(fsbtodb(&sblock, cgsblock(&sblock, i)),
			    (char *)&sblock, SBSIZE);
	close(fi);
	exit(0);
D 22
usage:
E 22
I 22
}

void
usage()
{

E 22
D 23
	fprintf(stderr, "Usage: tunefs tuneup-options special-device\n");
E 23
I 23
	fprintf(stderr, "Usage: tunefs [-AN] tuneup-options special-device\n");
E 23
	fprintf(stderr, "where tuneup-options are:\n");
D 4
	fprintf(stderr, "\t-a maximum contigouous blocks\n");
E 4
I 4
D 23
	fprintf(stderr, "\t-a maximum contiguous blocks\n");
E 23
E 4
	fprintf(stderr, "\t-d rotational delay between contiguous blocks\n");
I 23
	fprintf(stderr, "\t-a maximum contiguous blocks\n");
E 23
	fprintf(stderr, "\t-e maximum blocks per file in a cylinder group\n");
	fprintf(stderr, "\t-m minimum percentage of free space\n");
I 6
	fprintf(stderr, "\t-o optimization preference (`space' or `time')\n");
I 23
	fprintf(stderr, "\t-t track skew in sectors\n");
E 23
E 6
	exit(2);
}

I 22
void
E 22
getsb(fs, file)
	register struct fs *fs;
	char *file;
{

D 23
	fi = open(file, 2);
E 23
I 23
	fi = open(file, 0);
E 23
D 22
	if (fi < 0) {
D 17
		fprintf(stderr, "cannot open");
		perror(file);
E 17
I 17
		fprintf(stderr, "tunefs: %s: %s\n", file, strerror(errno));
E 17
		exit(3);
	}
D 8
	if (bread(SBLOCK, (char *)fs, SBSIZE)) {
E 8
I 8
D 19
	if (bread(SBOFF, (char *)fs, SBSIZE)) {
E 19
I 19
	if (bread((daddr_t)SBOFF, (char *)fs, SBSIZE)) {
E 19
E 8
D 17
		fprintf(stderr, "bad super block");
		perror(file);
E 17
I 17
		fprintf(stderr, "tunefs: %s: bad super block\n", file);
E 17
		exit(4);
	}
	if (fs->fs_magic != FS_MAGIC) {
D 17
		fprintf(stderr, "%s: bad magic number\n", file);
E 17
I 17
		fprintf(stderr, "tunefs: %s: bad magic number\n", file);
E 17
		exit(5);
	}
E 22
I 22
	if (fi < 0)
D 23
		err(3, "cannot open %s", file);
E 23
I 23
		err(3, "cannot open %s for reading", file);
E 23
	if (bread((daddr_t)SBOFF, (char *)fs, SBSIZE))
		err(4, "%s: bad super block", file);
	if (fs->fs_magic != FS_MAGIC)
		err(5, "%s: bad magic number", file);
E 22
I 8
	dev_bsize = fs->fs_fsize / fsbtodb(fs, 1);
I 23
	close(fi);
E 23
E 8
}

I 22
void
E 22
bwrite(blk, buf, size)
D 22
	char *buf;
E 22
	daddr_t blk;
D 22
	register size;
E 22
I 22
	char *buf;
	int size;
E 22
{
D 8
	if (lseek(fi, blk * DEV_BSIZE, 0) < 0) {
E 8
I 8
D 20
	if (lseek(fi, blk * dev_bsize, 0) < 0) {
E 20
I 20
D 22
	if (lseek(fi, (off_t)blk * dev_bsize, SEEK_SET) < 0) {
E 20
E 8
		perror("FS SEEK");
		exit(6);
	}
	if (write(fi, buf, size) != size) {
		perror("FS WRITE");
		exit(7);
	}
E 22
I 22

	if (lseek(fi, (off_t)blk * dev_bsize, SEEK_SET) < 0)
		err(6, "FS SEEK");
	if (write(fi, buf, size) != size)
		err(7, "FS WRITE");
E 22
}

I 22
int
E 22
bread(bno, buf, cnt)
	daddr_t bno;
	char *buf;
I 22
	int cnt;
E 22
{
D 22
	register i;
E 22
I 22
	int i;
E 22

D 8
	if (lseek(fi, bno * DEV_BSIZE, 0) < 0)
E 8
I 8
D 20
	if (lseek(fi, bno * dev_bsize, 0) < 0)
E 20
I 20
	if (lseek(fi, (off_t)bno * dev_bsize, SEEK_SET) < 0)
E 20
E 8
		return(1);
	if ((i = read(fi, buf, cnt)) != cnt) {
		for(i=0; i<sblock.fs_bsize; i++)
			buf[i] = 0;
		return (1);
	}
	return (0);
D 22
}

/* VARARGS1 */
fatal(fmt, arg1, arg2)
	char *fmt, *arg1, *arg2;
{

D 2
	fprintf(stderr, "newfs: ");
E 2
I 2
	fprintf(stderr, "tunefs: ");
E 2
	fprintf(stderr, fmt, arg1, arg2);
	putc('\n', stderr);
	exit(10);
E 22
}
E 1
