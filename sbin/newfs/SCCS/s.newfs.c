h04973
s 00006/00003/00649
d D 8.13 95/05/01 23:48:09 mckusick 69 68
c minor nits introduced by dinode changes
e
s 00001/00001/00651
d D 8.12 95/05/01 22:38:05 mckusick 68 67
c non-sense makes slightly more sense (from cgd)
e
s 00001/00001/00651
d D 8.11 95/04/28 14:21:45 bostic 67 66
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00004/00648
d D 8.10 95/04/28 10:46:01 bostic 66 65
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00651
d D 8.9 94/07/24 23:46:09 mckusick 65 64
c Mike Hibler sez we can nuke the round down on maxcontig
e
s 00000/00013/00652
d D 8.8 94/04/18 23:58:52 mckusick 64 63
c move definition of MINFREE to <ufs/ffs/fs.h> so it can be used by tunefs(8)
e
s 00003/00002/00662
d D 8.7 94/04/01 09:45:11 hibler 63 62
c make MNT_ASYNC the default for mfs, allow -T for mfs
e
s 00041/00035/00623
d D 8.6 94/03/27 13:47:34 bostic 62 61
c Jan-Simon Pendry's and my new mount code
e
s 00001/00001/00657
d D 8.5 94/02/05 02:00:53 mckusick 61 60
c match maxcontig with clustering goal size
e
s 00012/00010/00646
d D 8.4 94/01/27 21:06:43 pendry 60 59
c use warn()
c fatal() now handles the case where stderr has been closed (for mfs)
c so that you still get the error message.
e
s 00001/00001/00655
d D 8.3 94/01/26 13:47:05 hibler 59 58
c screwed up: lost an old bug fix in last delta
e
s 00007/00002/00649
d D 8.2 94/01/12 21:54:40 hibler 58 57
c fix usage check for mfs, reflect changes to mount.h
e
s 00005/00005/00646
d D 8.1 93/06/05 11:06:26 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00648
d D 6.35 93/05/05 17:33:01 mckusick 56 55
c add -O flag to usage message, tune minfree message
e
s 00017/00013/00633
d D 6.34 93/05/05 17:00:34 mckusick 55 54
c add -O flag to build old format filesystems;
c set default minfree to 5%; 
c set default maxcontig to MINPHYS / bsize
e
s 00003/00000/00643
d D 6.33 93/05/03 15:07:48 hibler 54 53
c disallow creation of filesystem on partition marked FS_BOOT
e
s 00029/00020/00614
d D 6.32 92/07/23 14:09:29 mckusick 53 52
c do not require valid disk when -T is specified
e
s 00001/00000/00633
d D 6.31 92/06/04 23:04:56 mckusick 52 51
c include <unistd.h> to get lseek prototype
e
s 00033/00005/00600
d D 6.30 92/05/27 23:53:40 mckusick 51 50
c check for newfs of mounted filesystem (from leres@lbl)
e
s 00002/00002/00603
d D 6.29 91/11/04 22:22:56 bostic 50 49
c break FFS into UFS/FFS/LFS
e
s 00022/00002/00583
d D 6.28 91/08/06 10:33:57 torek 49 48
c changes for sparc gcc
e
s 00001/00001/00584
d D 6.27 91/07/03 15:25:14 mckusick 48 47
c make Torek happy
e
s 00004/00001/00581
d D 6.26 91/05/04 13:08:54 bostic 47 46
c make the MFS #define work right -- note, MFS not used in mkfs.c!!
e
s 00003/00002/00579
d D 6.25 91/04/10 12:12:03 karels 46 44
c suppress "not a character device" if mfs; prepend prog name
e
s 00003/00000/00691
d D 6.22.1.1 90/12/18 17:48:56 bostic 45 42
c branch version to fix Reno distribution
e
s 00019/00016/00562
d D 6.24 90/12/18 17:46:06 karels 44 43
c fix to work on unlabeled disks; don't ignore the specified pathname;
c attempt to work on non-character devices; check return value on getdiskbyname
c (unlabeled disk problem is that bbsize, sbsize aren't set in faked-up label)
e
s 00197/00310/00381
d D 6.23 90/07/25 17:41:42 bostic 43 42
c add getopt(3); always display program name on error (use fatal());
c use varargs for error routine; some lint, but didn't fix variable declarations
e
s 00037/00025/00654
d D 6.22 90/06/19 23:14:25 mckusick 42 41
c update from Hibler to support MFS on non-labelled disks
e
s 00001/00011/00678
d D 6.21 90/06/01 16:19:00 bostic 41 40
c new copyright notice
e
s 00022/00010/00667
d D 6.20 89/10/18 11:09:27 mckusick 40 39
c memfs => mfs; add -F flag to pass in mount flags
e
s 00071/00025/00606
d D 6.19 89/09/06 11:11:49 mckusick 39 38
c add memory based filesystem; generate unique error codes;
c select number of bytes per inode based on fragment size
e
s 00002/00002/00629
d D 6.18 89/07/01 10:20:35 mckusick 38 37
c new header file locations
e
s 00002/00001/00629
d D 6.17 89/05/11 13:54:49 bostic 37 36
c file reorg, pathnames.h, paths.h
e
s 00025/00002/00605
d D 6.16 88/05/01 23:23:48 mckusick 36 35
c add -n flag to allow specification of number of rotational positions;
c set the default to be the old NRPOS of 8
e
s 00001/00001/00606
d D 6.15 87/12/07 17:06:08 mckusick 35 34
c fix error message
e
s 00002/00002/00605
d D 6.14 87/10/22 11:12:52 bostic 34 33
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00605
d D 6.13 87/10/01 22:45:13 mckusick 33 32
c cannot initialize maxbpg until bsize is set
e
s 00001/00001/00606
d D 6.12 87/10/01 19:25:14 bostic 32 31
c pointer typo
e
s 00055/00010/00552
d D 6.11 87/10/01 12:45:35 mckusick 31 30
c add remainder of tunable parameters (-a, -d, -e); 
c rename old -a to -x, old -d to -u so above can have same values as `tunefs'
e
s 00002/00000/00560
d D 6.10 87/09/10 00:37:27 mckusick 30 29
c need to know if cpg is specified
e
s 00045/00002/00515
d D 6.9 87/06/23 12:15:54 karels 29 28
c backward compat for unlabelled disks
e
s 00001/00000/00516
d D 6.8 87/05/08 10:59:43 sam 28 27
c missing definition for vax (from jim mckie)
e
s 00003/00003/00513
d D 6.7 87/04/07 20:15:01 karels 27 26
c use fsize, bsize from label if no args
e
s 00008/00008/00508
d D 6.6 87/04/02 11:42:13 karels 26 25
c print correct arg, more tolerant of omissions
e
s 00042/00073/00474
d D 6.5 87/03/29 15:58:13 karels 25 24
c update for new label ioctls, get bbsize/sbsize from label;
c tahoe hacks to use DEV_BSIZE
e
s 00016/00018/00531
d D 6.4 87/02/02 22:42:09 karels 24 23
c rm byte-swapping
e
s 00007/00007/00542
d D 6.3 87/01/15 21:23:11 mckusick 23 22
c reorder usage to correspond to manual page
e
s 00063/00006/00486
d D 6.2 87/01/13 19:33:22 mckusick 22 21
c add trackskew, interleave, npsect, headswitch, and trackseek
c use first three to more completely calculate rotational position
e
s 00307/00198/00186
d D 6.1 87/01/13 12:32:11 mckusick 21 20
c merge mkfs and newfs; add support for disk labels
e
s 00004/00000/00380
d D 5.3 86/10/13 15:06:15 sam 20 19
c make installboot conditional on BOOTDIR and that conditional on vax
e
s 00023/00000/00357
d D 5.2 85/09/11 23:20:46 mckusick 19 18
c allow specification of optimization preference
e
s 00014/00002/00343
d D 5.1 85/05/28 15:02:49 dist 18 17
c Add copyright
e
s 00011/00001/00334
d D 4.14 84/08/16 14:04:54 mckusick 17 15
c add -N flag to print out stats on file system without creating it
e
s 00011/00001/00334
d R 4.14 84/08/16 11:28:09 mckusick 16 15
c add -N flag to print out stats on file system without creating it
e
s 00001/00001/00334
d D 4.13 84/04/18 09:22:14 ralph 15 14
c pass the exit code from system() correctly.
e
s 00016/00000/00319
d D 4.12 83/08/28 15:56:28 mckusick 14 13
c add -i option to specify "number of bytes per inode"
e
s 00001/00001/00318
d D 4.11 83/08/01 12:25:05 sam 13 12
c what a hack, but it will suffice for now
e
s 00009/00010/00310
d D 4.10 83/07/22 15:03:55 mckusick 12 11
c strengthen up code for converting disk names to raw disk names
e
s 00002/00001/00318
d D 4.9 83/07/06 22:59:27 sam 11 10
c check for raw device name correctly according to kre
e
s 00001/00001/00318
d D 4.8 83/07/02 00:04:07 sam 10 9
c include fiox
e
s 00008/00003/00311
d D 4.7 83/05/08 21:18:13 helge 9 8
c new -n (noboot) flag, fix allowing zero reserved space
e
s 00004/00002/00310
d D 4.6 83/02/20 19:40:25 sam 8 7
c grab boot blocks out of /usr/mdec
e
s 00048/00012/00264
d D 4.5 83/02/15 16:07:16 sam 7 6
c add minfree and rps; change name to newfs
e
s 00004/00004/00272
d D 4.4 83/02/14 14:45:59 sam 6 5
c fix usage
e
s 00011/00007/00265
d D 4.3 83/02/10 18:59:31 sam 5 3
c use raw device
e
s 00007/00007/00265
d R 4.3 83/02/10 18:54:19 sam 4 3
c use raw device
e
s 00003/00007/00269
d D 4.2 83/02/08 14:57:49 sam 3 1
c enable dangerous code
e
s 00000/00004/00272
d R 4.2 83/02/08 14:54:01 sam 2 1
c enable dangerous code
e
s 00276/00000/00000
d D 4.1 83/02/08 14:50:22 sam 1 0
c date and time created 83/02/08 14:50:22 by sam
e
u
U
t
T
I 18
/*
D 39
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 39
I 39
D 57
 * Copyright (c) 1983, 1989 The Regents of the University of California.
 * All rights reserved.
E 57
I 57
D 62
 * Copyright (c) 1983, 1989, 1993
E 62
I 62
 * Copyright (c) 1983, 1989, 1993, 1994
E 62
 *	The Regents of the University of California.  All rights reserved.
E 57
 *
D 41
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
E 41
I 41
 * %sccs.include.redist.c%
E 41
E 39
 */

E 18
I 1
#ifndef lint
I 39
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifndef lint
E 39
D 18
static char sccsid[] = "%W% %G%";
#endif
E 18
I 18
D 57
char copyright[] =
D 39
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 39
I 39
"%Z% Copyright (c) 1983, 1989 Regents of the University of California.\n\
E 39
 All rights reserved.\n";
E 57
I 57
static char copyright[] =
D 62
"%Z% Copyright (c) 1983, 1989, 1993\n\
E 62
I 62
"%Z% Copyright (c) 1983, 1989, 1993, 1994\n\
E 62
	The Regents of the University of California.  All rights reserved.\n";
E 57
D 39
#endif not lint
E 39
I 39
#endif /* not lint */
E 39

D 39
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 18

E 39
/*
D 7
 * makefs: friendly front end to mkfs
E 7
I 7
 * newfs: friendly front end to mkfs
E 7
 */
#include <sys/param.h>
#include <sys/stat.h>
D 38
#include <sys/fs.h>
I 10
#include <sys/dir.h>
E 38
I 38
D 50
#include <ufs/fs.h>
#include <ufs/dir.h>
E 50
E 38
I 21
#include <sys/ioctl.h>
#include <sys/disklabel.h>
#include <sys/file.h>
I 39
#include <sys/mount.h>
I 62

E 62
I 50
#include <ufs/ufs/dir.h>
I 69
#include <ufs/ufs/dinode.h>
E 69
#include <ufs/ffs/fs.h>
I 69
#include <ufs/ufs/ufsmount.h>
E 69
E 50
E 39
E 21
E 10

I 62
#include <ctype.h>
E 62
I 43
#include <errno.h>
I 62
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

E 62
I 49
#if __STDC__
E 49
#include <stdarg.h>
I 49
#else
#include <varargs.h>
#endif
I 52
D 62
#include <unistd.h>
E 52
E 49
E 43
#include <stdio.h>
D 10
#include <dir.h>
E 10
D 21
#include <disktab.h>
E 21
I 21
#include <ctype.h>
I 43
#include <string.h>
#include <stdlib.h>
I 60
#include <syslog.h>
E 60
E 43
I 37
#include <paths.h>
E 62
E 37
E 21

I 62
#include "mntopts.h"

struct mntopt mopts[] = {
	MOPT_STDOPTS,
I 63
	MOPT_ASYNC,
E 63
	{ NULL },
};

E 62
I 49
#if __STDC__
void	fatal(const char *fmt, ...);
#else
void	fatal();
#endif

E 49
I 29
D 43
#define COMPAT			/* allow non-labeled disks */
E 43
I 43
#define	COMPAT			/* allow non-labeled disks */
E 43

E 29
I 20
D 21
#ifdef vax
E 20
I 8
#define	BOOTDIR	"/usr/mdec"	/* directory for boot blocks */
I 20
#endif
E 21
I 21
/*
 * The following two constants set the default block and fragment sizes.
 * Both constants must be a power of 2 and meet the following constraints:
 *	MINBSIZE <= DESBLKSIZE <= MAXBSIZE
 *	sectorsize <= DESFRAGSIZE <= DESBLKSIZE
 *	DESBLKSIZE / DESFRAGSIZE <= 8
 */
#define	DFL_FRAGSIZE	1024
#define	DFL_BLKSIZE	8192
E 21
E 20

I 17
D 21
int	Nflag;			/* run mkfs without writing file system */
E 17
E 8
int	verbose;		/* show mkfs line before exec */
I 9
int	noboot;			/* do not fill boot blocks */
E 21
I 21
/*
D 36
 * Cylinder groups may have up to MAXCPG cylinders. The actual
E 36
I 36
 * Cylinder groups may have up to many cylinders. The actual
E 36
 * number used depends upon how much information can be stored
D 36
 * on a single cylinder. The default is to used 16 cylinders
E 36
I 36
 * on a single cylinder. The default is to use 16 cylinders
E 36
 * per group.
 */
#define	DESCPG		16	/* desired fs_cpg */

/*
D 64
 * MINFREE gives the minimum acceptable percentage of file system
 * blocks which may be free. If the freelist drops below this level
 * only the superuser may continue to allocate blocks. This may
 * be set to 0 if no reserve of free blocks is deemed necessary,
 * however throughput drops by fifty percent if the file system
D 55
 * is run at between 90% and 100% full; thus the default value of
 * fs_minfree is 10%. With 10% free space, fragmentation is not a
E 55
I 55
 * is run at between 95% and 100% full; thus the default value of
 * fs_minfree is 5%. With 5% free space, fragmentation is not a
E 55
 * problem, so we choose to optimize for time.
 */
D 55
#define MINFREE		10
E 55
I 55
#define MINFREE		5
E 55
#define DEFAULTOPT	FS_OPTTIME

/*
E 64
 * ROTDELAY gives the minimum number of milliseconds to initiate
 * another disk transfer on the same cylinder. It is used in
 * determining the rotationally optimal layout for disk blocks
 * within a file; the default of fs_rotdelay is 4ms.
 */
#define ROTDELAY	4

/*
D 55
 * MAXCONTIG sets the default for the maximum number of blocks
 * that may be allocated sequentially. Since UNIX drivers are
 * not capable of scheduling multi-block transfers, this defaults
 * to 1 (ie no contiguous blocks are allocated).
 */
#define MAXCONTIG	1

/*
E 55
I 31
 * MAXBLKPG determines the maximum number of data blocks which are
 * placed in a single cylinder group. The default is one indirect
 * block worth of data blocks.
 */
#define MAXBLKPG(bsize)	((bsize) / sizeof(daddr_t))

/*
E 31
 * Each file system has a number of inodes statically allocated.
D 39
 * We allocate one inode slot per NBPI bytes, expecting this
E 39
I 39
 * We allocate one inode slot per NFPI fragments, expecting this
E 39
 * to be far more than we will ever need.
 */
D 39
#define	NBPI		2048
E 39
I 39
#define	NFPI		4
E 39

I 36
/*
 * For each cylinder we keep track of the availability of blocks at different
 * rotational positions, so that we can lay out the data to be picked
 * up with minimum rotational latency.  NRPOS is the default number of
 * rotational positions that we distinguish.  With NRPOS of 8 the resolution
 * of our summary information is 2ms for a typical 3600 rpm drive.
 */
#define	NRPOS		8	/* number distinct rotational positions */


I 39
D 40
int	memfs;			/* run as the memory based filesystem */
E 40
I 40
int	mfs;			/* run as the memory based filesystem */
E 40
E 39
E 36
int	Nflag;			/* run without writing file system */
I 55
int	Oflag;			/* format as an 4.3BSD file system */
E 55
E 21
E 9
int	fssize;			/* file system size */
D 21
int	fsize;			/* fragment size */
int	bsize;			/* block size */
E 21
int	ntracks;		/* # tracks/cylinder */
int	nsectors;		/* # sectors/track */
I 21
D 22
int	nspares = -1;		/* spare sectors per cylinder */
E 22
I 22
int	nphyssectors;		/* # sectors/track including spares */
E 22
int	secpercyl;		/* sectors per cylinder */
I 22
int	trackspares = -1;	/* spare sectors per track */
int	cylspares = -1;		/* spare sectors per cylinder */
E 22
E 21
int	sectorsize;		/* bytes/sector */
I 25
#ifdef tahoe
int	realsectorsize;		/* bytes/sector in hardware */
#endif
E 25
D 21
int	cpg;			/* cylinders/cylinder group */
I 7
D 9
int	minfree;		/* free space threshold */
E 9
I 9
int	minfree = -1;		/* free space threshold */
I 19
int	opt;			/* optimization preference (space or time) */
E 21
E 19
E 9
int	rpm;			/* revolutions/minute of drive */
I 22
int	interleave;		/* hardware sector interleave */
int	trackskew = -1;		/* sector 0 skew, per track */
int	headswitch;		/* head switch time, usec */
int	trackseek;		/* track-to-track seek, usec */
E 22
I 14
D 21
int	density;		/* number of bytes per inode */
E 21
I 21
D 27
int	fsize = DFL_FRAGSIZE;	/* fragment size */
int	bsize = DFL_BLKSIZE;	/* block size */
E 27
I 27
int	fsize = 0;		/* fragment size */
int	bsize = 0;		/* block size */
E 27
int	cpg = DESCPG;		/* cylinders/cylinder group */
I 30
int	cpgflg;			/* cylinders/cylinder group flag was given */
E 30
int	minfree = MINFREE;	/* free space threshold */
int	opt = DEFAULTOPT;	/* optimization preference (space or time) */
D 39
int	density = NBPI;		/* number of bytes per inode */
E 39
I 39
int	density;		/* number of bytes per inode */
E 39
D 55
int	maxcontig = MAXCONTIG;	/* max contiguous blocks to allocate */
E 55
I 55
int	maxcontig = 0;		/* max contiguous blocks to allocate */
E 55
int	rotdelay = ROTDELAY;	/* rotational delay between blocks */
I 31
int	maxbpg;			/* maximum blocks per file in a cyl group */
I 36
int	nrpos = NRPOS;		/* # of distinguished rotational positions */
E 36
E 31
I 25
int	bbsize = BBSIZE;	/* boot block size */
int	sbsize = SBSIZE;	/* superblock size */
I 40
D 63
int	mntflags;		/* flags to be passed to mount */
E 63
I 63
int	mntflags = MNT_ASYNC;	/* flags to be passed to mount */
E 63
E 40
I 39
u_long	memleft;		/* virtual memory available */
caddr_t	membase;		/* start address of memory based filesystem */
E 39
I 29
#ifdef COMPAT
I 42
char	*disktype;
E 42
D 43
int	unlabelled;
E 43
I 43
int	unlabeled;
E 43
#endif
E 29
E 25
E 21
E 14
E 7

D 21
char	*av[20];		/* argv array and buffers for exec */
char	a2[20];
char	a3[20];
char	a4[20];
char	a5[20];
char	a6[20];
char	a7[20];
I 7
char	a8[20];
char	a9[20];
I 14
char	a10[20];
E 21
E 14
E 7
char	device[MAXPATHLEN];
I 39
char	*progname;
E 39
D 21
char	cmd[BUFSIZ];
E 21

I 62
int
E 62
I 21
D 43
extern	int errno;
E 21
char	*index();
char	*rindex();
D 34
char	*sprintf();
E 34

E 43
main(argc, argv)
I 12
	int argc;
E 12
	char *argv[];
{
D 39
	char *cp, *special;
E 39
I 39
D 43
	char *cp, *special, *rindex();
E 43
I 43
	extern char *optarg;
	extern int optind;
	register int ch;
E 43
E 39
D 21
	register struct disktab *dp;
E 21
	register struct partition *pp;
I 21
	register struct disklabel *lp;
	struct disklabel *getdisklabel();
	struct partition oldpartition;
I 39
D 47
	struct mfs_args args;
E 47
E 39
E 21
	struct stat st;
I 21
D 62
	int fsi, fso;
E 21
D 43
	register int i;
	int status;
I 39
	char buf[BUFSIZ];
E 43
I 43
	char *cp, *special, *opstring, buf[BUFSIZ];
E 62
I 51
	struct statfs *mp;
D 62
	char *s1, *s2;
	int len, n;
E 62
I 62
	int fsi, fso, len, n;
	char *cp, *s1, *s2, *special, *opstring, buf[BUFSIZ];
E 62
E 51
E 43
E 39

I 39
D 43
	if ((progname = rindex(*argv, '/') + 1) == (char *)1)
E 43
I 43
D 66
	if (progname = rindex(*argv, '/'))
E 66
I 66
	if (progname = strrchr(*argv, '/'))
E 66
		++progname;
	else
E 43
		progname = *argv;
I 43

E 43
D 40
	if (!strcmp(progname, "memfs")) {
E 40
I 40
D 48
	if (!strcmp(progname, "mfs")) {
E 48
I 48
	if (strstr(progname, "mfs")) {
E 48
I 43
		mfs = 1;
E 43
E 40
		Nflag++;
D 40
		memfs++;
E 40
I 40
D 43
		mfs++;
E 43
E 40
	}
E 39
D 43
	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++)
			switch (*cp) {
E 43

I 40
D 43
			case 'F':
				if (!mfs)
					fatal("-F: unknown flag");
				if (argc < 1)
					fatal("-F: mount flags");
				argc--, argv++;
				mntflags = atoi(*argv);
				if (mntflags == 0)
					fatal("%s: bad mount flags", *argv);
				goto next;
E 43
I 43
D 55
	opstring = "F:NS:T:a:b:c:d:e:f:i:k:l:m:n:o:p:r:s:t:u:x:";
E 55
I 55
D 62
	opstring = "F:NOS:T:a:b:c:d:e:f:i:k:l:m:n:o:p:r:s:t:u:x:";
E 55
	if (!mfs)
		opstring += 2;		/* -F is mfs only */
E 43

E 62
I 62
	opstring = mfs ?
D 63
	    "Na:b:c:d:e:f:i:m:o:s:" :
E 63
I 63
	    "NT:a:b:c:d:e:f:i:m:o:s:" :
E 63
	    "NOS:T:a:b:c:d:e:f:i:k:l:m:n:o:p:r:s:t:u:x:";
E 62
E 40
D 21
			case 'v':
				verbose++;
				break;

E 21
I 17
D 43
			case 'N':
				Nflag++;
D 21
				/* fall through to */

E 17
I 9
			case 'n':
				noboot++;
E 21
				break;

E 9
D 21
			case 's':
E 21
I 21
			case 'S':
E 21
				if (argc < 1)
D 21
					fatal("-s: missing file system size");
E 21
I 21
					fatal("-S: missing sector size");
E 21
				argc--, argv++;
D 21
				fssize = atoi(*argv);
				if (fssize < 0)
					fatal("%s: bad file system size",
						*argv);
E 21
I 21
				sectorsize = atoi(*argv);
				if (sectorsize <= 0)
					fatal("%s: bad sector size", *argv);
E 21
				goto next;

E 43
I 43
	while ((ch = getopt(argc, argv, opstring)) != EOF)
D 62
		switch(ch) {
		case 'F':
			if ((mntflags = atoi(optarg)) == 0)
				fatal("%s: bad mount flags", optarg);
			break;
E 62
I 62
		switch (ch) {
E 62
		case 'N':
D 62
			Nflag++;
E 62
I 62
			Nflag = 1;
E 62
			break;
I 55
		case 'O':
D 62
			Oflag++;
E 62
I 62
			Oflag = 1;
E 62
			break;
E 55
		case 'S':
			if ((sectorsize = atoi(optarg)) <= 0)
				fatal("%s: bad sector size", optarg);
			break;
E 43
I 42
#ifdef COMPAT
D 43
			case 'T':
				if (argc < 1)
					fatal("-T: missing disk type");
				argc--, argv++;
				disktype = *argv;
				goto next;
E 43
I 43
		case 'T':
			disktype = optarg;
			break;
E 43
#endif
I 43
		case 'a':
			if ((maxcontig = atoi(optarg)) <= 0)
D 62
				fatal("%s: bad max contiguous blocks\n",
E 62
I 62
				fatal("%s: bad maximum contiguous blocks\n",
E 62
				    optarg);
			break;
		case 'b':
			if ((bsize = atoi(optarg)) < MINBSIZE)
				fatal("%s: bad block size", optarg);
			break;
		case 'c':
			if ((cpg = atoi(optarg)) <= 0)
				fatal("%s: bad cylinders/group", optarg);
			cpgflg++;
			break;
		case 'd':
			if ((rotdelay = atoi(optarg)) < 0)
				fatal("%s: bad rotational delay\n", optarg);
			break;
		case 'e':
			if ((maxbpg = atoi(optarg)) <= 0)
D 62
				fatal("%s: bad blocks per file in a cyl group\n",
E 62
I 62
		fatal("%s: bad blocks per file in a cylinder group\n",
E 62
				    optarg);
			break;
		case 'f':
			if ((fsize = atoi(optarg)) <= 0)
D 62
				fatal("%s: bad frag size", optarg);
E 62
I 62
				fatal("%s: bad fragment size", optarg);
E 62
			break;
		case 'i':
			if ((density = atoi(optarg)) <= 0)
				fatal("%s: bad bytes per inode\n", optarg);
			break;
		case 'k':
			if ((trackskew = atoi(optarg)) < 0)
				fatal("%s: bad track skew", optarg);
			break;
		case 'l':
			if ((interleave = atoi(optarg)) <= 0)
				fatal("%s: bad interleave", optarg);
			break;
		case 'm':
			if ((minfree = atoi(optarg)) < 0 || minfree > 99)
				fatal("%s: bad free space %%\n", optarg);
			break;
		case 'n':
			if ((nrpos = atoi(optarg)) <= 0)
				fatal("%s: bad rotational layout count\n",
				    optarg);
			break;
		case 'o':
D 62
			if (strcmp(optarg, "space") == 0)
				opt = FS_OPTSPACE;
			else if (strcmp(optarg, "time") == 0)
				opt = FS_OPTTIME;
			else
				fatal("%s: bad optimization preference %s",
				    optarg, "(options are `space' or `time')");
E 62
I 62
			if (mfs)
D 69
				getmntopts(optarg, mopts, &mntflags);
E 69
I 69
				getmntopts(optarg, mopts, &mntflags, 0);
E 69
			else {
				if (strcmp(optarg, "space") == 0)
					opt = FS_OPTSPACE;
				else if (strcmp(optarg, "time") == 0)
					opt = FS_OPTTIME;
				else
	fatal("%s: unknown optimization preference: use `space' or `time'.");
			}
E 62
			break;
		case 'p':
			if ((trackspares = atoi(optarg)) < 0)
				fatal("%s: bad spare sectors per track",
				    optarg);
			break;
		case 'r':
			if ((rpm = atoi(optarg)) <= 0)
D 62
				fatal("%s: bad revs/minute\n", optarg);
E 62
I 62
				fatal("%s: bad revolutions/minute\n", optarg);
E 62
			break;
		case 's':
			if ((fssize = atoi(optarg)) <= 0)
				fatal("%s: bad file system size", optarg);
			break;
		case 't':
			if ((ntracks = atoi(optarg)) <= 0)
				fatal("%s: bad total tracks", optarg);
			break;
		case 'u':
			if ((nsectors = atoi(optarg)) <= 0)
				fatal("%s: bad sectors/track", optarg);
			break;
		case 'x':
			if ((cylspares = atoi(optarg)) < 0)
				fatal("%s: bad spare sectors per cylinder",
				    optarg);
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 43

E 42
D 21
			case 't':
E 21
I 21
D 43
			case 'a':
E 21
				if (argc < 1)
D 21
					fatal("-t: missing track total");
E 21
I 21
D 31
					fatal("-a: spare sectors per cylinder");
E 31
I 31
					fatal("-a: missing max contiguous blocks\n");
E 31
E 21
				argc--, argv++;
D 21
				ntracks = atoi(*argv);
				if (ntracks < 0)
					fatal("%s: bad total tracks", *argv);
E 21
I 21
D 22
				nspares = atoi(*argv);
				if (nspares < 0)
E 22
I 22
D 31
				cylspares = atoi(*argv);
				if (cylspares < 0)
E 22
					fatal("%s: bad spare sectors per cylinder", *argv);
E 31
I 31
				maxcontig = atoi(*argv);
				if (maxcontig <= 0)
					fatal("%s: bad max contiguous blocks\n",
						*argv);
E 31
E 21
				goto next;
E 43
I 43
D 58
	if (argc != 2 && (mfs || argc != 1))
E 58
I 58
D 59
	if (argc != 2 && (!mfs || argc != 1))
E 59
I 59
	if (argc != 2 && (mfs || argc != 1))
E 59
E 58
		usage();
E 43

I 19
D 21
			case 'o':
				if (argc < 1)
					fatal("-o: missing optimization preference");
				argc--, argv++;
				if (strcmp(*argv, "space") == 0)
					opt = FS_OPTSPACE;
				else if (strcmp(*argv, "time") == 0)
					opt = FS_OPTTIME;
				else
					fatal("%s: bad optimization preference %s",
					    *argv,
					    "(options are `space' or `time')");
				goto next;

E 21
E 19
D 43
			case 'b':
				if (argc < 1)
					fatal("-b: missing block size");
				argc--, argv++;
				bsize = atoi(*argv);
D 21
				if (bsize < 0 || bsize < MINBSIZE)
E 21
I 21
				if (bsize < MINBSIZE)
E 21
					fatal("%s: bad block size", *argv);
				goto next;

D 21
			case 'f':
E 21
I 21
			case 'c':
E 21
				if (argc < 1)
D 21
					fatal("-f: missing frag size");
E 21
I 21
					fatal("-c: missing cylinders/group");
E 21
				argc--, argv++;
D 21
				fsize = atoi(*argv);
				if (fsize < 0)
					fatal("%s: bad frag size", *argv);
E 21
I 21
				cpg = atoi(*argv);
				if (cpg <= 0)
					fatal("%s: bad cylinders/group", *argv);
I 30
				cpgflg++;
E 30
E 21
				goto next;

D 21
			case 'S':
E 21
I 21
			case 'd':
E 21
				if (argc < 1)
D 21
					fatal("-S: missing sector size");
E 21
I 21
D 31
					fatal("-d: missing sectors/track");
E 31
I 31
					fatal("-d: missing rotational delay\n");
E 31
E 21
				argc--, argv++;
D 21
				sectorsize = atoi(*argv);
				if (sectorsize < 0)
					fatal("%s: bad sector size", *argv);
E 21
I 21
D 31
				nsectors = atoi(*argv);
				if (nsectors <= 0)
					fatal("%s: bad sectors/track", *argv);
E 31
I 31
				rotdelay = atoi(*argv);
				if (rotdelay < 0)
					fatal("%s: bad rotational delay\n",
						*argv);
E 31
E 21
				goto next;

I 31
			case 'e':
				if (argc < 1)
					fatal("-e: missing blocks pre file in a cyl group\n");
				argc--, argv++;
				maxbpg = atoi(*argv);
				if (maxbpg <= 0)
					fatal("%s: bad blocks per file in a cyl group\n",
						*argv);
				goto next;

E 31
D 21
			case 'c':
E 21
I 21
			case 'f':
E 21
				if (argc < 1)
D 21
					fatal("-c: missing cylinders/group");
E 21
I 21
					fatal("-f: missing frag size");
E 21
				argc--, argv++;
D 21
				cpg = atoi(*argv);
				if (cpg < 0)
					fatal("%s: bad cylinders/group", *argv);
E 21
I 21
				fsize = atoi(*argv);
				if (fsize <= 0)
					fatal("%s: bad frag size", *argv);
E 21
				goto next;

I 21
			case 'i':
				if (argc < 1)
					fatal("-i: missing bytes per inode\n");
				argc--, argv++;
				density = atoi(*argv);
				if (density <= 0)
					fatal("%s: bad bytes per inode\n",
						*argv);
				goto next;

I 22
			case 'k':
				if (argc < 1)
					fatal("-k: track skew");
				argc--, argv++;
				trackskew = atoi(*argv);
				if (trackskew < 0)
					fatal("%s: bad track skew", *argv);
				goto next;

			case 'l':
				if (argc < 1)
					fatal("-l: interleave");
				argc--, argv++;
				interleave = atoi(*argv);
				if (interleave <= 0)
					fatal("%s: bad interleave", *argv);
				goto next;

E 22
E 21
I 7
			case 'm':
				if (argc < 1)
					fatal("-m: missing free space %%\n");
				argc--, argv++;
				minfree = atoi(*argv);
				if (minfree < 0 || minfree > 99)
					fatal("%s: bad free space %%\n",
						*argv);
				goto next;

I 36
			case 'n':
				if (argc < 1)
					fatal("-n: missing rotational layout count\n");
				argc--, argv++;
				nrpos = atoi(*argv);
				if (nrpos <= 0)
					fatal("%s: bad rotational layout count\n",
						*argv);
				goto next;

E 36
I 21
			case 'o':
				if (argc < 1)
					fatal("-o: missing optimization preference");
				argc--, argv++;
				if (strcmp(*argv, "space") == 0)
					opt = FS_OPTSPACE;
				else if (strcmp(*argv, "time") == 0)
					opt = FS_OPTTIME;
				else
					fatal("%s: bad optimization preference %s",
					    *argv,
					    "(options are `space' or `time')");
				goto next;

I 22
			case 'p':
				if (argc < 1)
					fatal("-p: spare sectors per track");
				argc--, argv++;
				trackspares = atoi(*argv);
				if (trackspares < 0)
					fatal("%s: bad spare sectors per track", *argv);
				goto next;

E 22
E 21
			case 'r':
				if (argc < 1)
					fatal("-r: missing revs/minute\n");
				argc--, argv++;
				rpm = atoi(*argv);
D 21
				if (rpm < 0)
E 21
I 21
				if (rpm <= 0)
E 21
					fatal("%s: bad revs/minute\n", *argv);
				goto next;

I 14
D 21
			case 'i':
E 21
I 21
			case 's':
E 21
				if (argc < 1)
D 21
					fatal("-i: missing bytes per inode\n");
E 21
I 21
					fatal("-s: missing file system size");
E 21
				argc--, argv++;
D 21
				density = atoi(*argv);
				if (density < 0)
					fatal("%s: bad bytes per inode\n",
E 21
I 21
				fssize = atoi(*argv);
				if (fssize <= 0)
					fatal("%s: bad file system size",
E 21
						*argv);
				goto next;

I 21
			case 't':
				if (argc < 1)
					fatal("-t: missing track total");
				argc--, argv++;
				ntracks = atoi(*argv);
				if (ntracks <= 0)
					fatal("%s: bad total tracks", *argv);
				goto next;

I 31
			case 'u':
				if (argc < 1)
					fatal("-u: missing sectors/track");
				argc--, argv++;
				nsectors = atoi(*argv);
				if (nsectors <= 0)
					fatal("%s: bad sectors/track", *argv);
				goto next;

			case 'x':
				if (argc < 1)
					fatal("-x: spare sectors per cylinder");
				argc--, argv++;
				cylspares = atoi(*argv);
				if (cylspares < 0)
					fatal("%s: bad spare sectors per cylinder", *argv);
				goto next;

E 31
E 21
E 14
E 7
			default:
D 32
				fatal("-%c: unknown flag", cp);
E 32
I 32
				fatal("-%c: unknown flag", *cp);
E 32
			}
next:
		argc--, argv++;
	}
D 21
	if (argc < 2) {
D 7
		fprintf(stderr, "usage: makefs [ -v ] [ mkfs-options ] %s\n",
E 7
I 7
		fprintf(stderr, "usage: newfs [ -v ] [ mkfs-options ] %s\n",
E 7
			"special-device device-type");
		fprintf(stderr, "where mkfs-options are:\n");
E 21
I 21
	if (argc < 1) {
I 39
D 40
		if (memfs)
E 40
I 40
		if (mfs)
E 40
			fprintf(stderr,
D 40
			    "usage: memfs [ fsoptions ] special-device %s\n",
E 40
I 40
			    "usage: mfs [ fsoptions ] special-device %s\n",
E 40
			    "mount-point");
		else
E 39
I 29
#ifdef COMPAT
D 39
		fprintf(stderr,
		"usage: newfs [ fsoptions ] special-device [device-type]\n");
E 39
I 39
			fprintf(stderr, "usage: %s\n",
			    "newfs [ fsoptions ] special-device [device-type]");
E 39
#else
E 29
D 39
		fprintf(stderr, "usage: newfs [ fsoptions ] special-device\n");
E 39
I 39
			fprintf(stderr,
			    "usage: newfs [ fsoptions ] special-device\n");
E 39
I 29
#endif
E 29
		fprintf(stderr, "where fsoptions are:\n");
E 21
I 17
		fprintf(stderr, "\t-N do not create file system, %s\n",
			"just print out parameters");
I 42
#ifdef COMPAT
		fprintf(stderr, "\t-T disktype\n");
#endif
E 42
E 17
D 5
		fprintf(stderr, "-s sectors/track\n");
		fprintf(stderr, "-b block-size\n");
		fprintf(stderr, "-f frag-size\n");
		fprintf(stderr, "-t tracks/cylinder\n");
		fprintf(stderr, "-c cylinders/group\n");
		fprintf(stderr, "-S sector-size\n");
E 5
I 5
D 6
		fprintf(stderr, "\t-s sectors/track\n");
		fprintf(stderr, "\t-b block-size\n");
		fprintf(stderr, "\t-f frag-size\n");
E 6
I 6
D 23
		fprintf(stderr, "\t-s file system size (sectors)\n");
E 23
		fprintf(stderr, "\t-b block size\n");
		fprintf(stderr, "\t-f frag size\n");
I 21
D 23
		fprintf(stderr, "\t-d sectors/track\n");
E 21
E 6
		fprintf(stderr, "\t-t tracks/cylinder\n");
		fprintf(stderr, "\t-c cylinders/group\n");
E 23
I 7
		fprintf(stderr, "\t-m minimum free space %%\n");
I 19
		fprintf(stderr, "\t-o optimization preference %s\n",
			"(`space' or `time')");
I 31
		fprintf(stderr, "\t-a maximum contiguous blocks\n");
		fprintf(stderr, "\t-d rotational delay between %s\n",
			"contiguous blocks");
		fprintf(stderr, "\t-e maximum blocks per file in a %s\n",
			"cylinder group");
E 31
E 19
D 23
		fprintf(stderr, "\t-r revolutions/minute\n");
E 23
E 7
D 6
		fprintf(stderr, "\t-S sector-size\n");
E 6
I 6
D 21
		fprintf(stderr, "\t-S sector size\n");
E 21
I 14
		fprintf(stderr, "\t-i number of bytes per inode\n");
I 23
		fprintf(stderr, "\t-c cylinders/group\n");
I 36
		fprintf(stderr, "\t-n number of distinguished %s\n",
			"rotational positions");
E 36
		fprintf(stderr, "\t-s file system size (sectors)\n");
		fprintf(stderr, "\t-r revolutions/minute\n");
E 23
I 21
		fprintf(stderr, "\t-S sector size\n");
I 22
D 23
		fprintf(stderr, "\t-l hardware sector interleave\n");
		fprintf(stderr, "\t-k sector 0 skew, per track\n");
E 23
I 23
D 31
		fprintf(stderr, "\t-d sectors/track\n");
E 31
I 31
		fprintf(stderr, "\t-u sectors/track\n");
E 31
		fprintf(stderr, "\t-t tracks/cylinder\n");
E 23
		fprintf(stderr, "\t-p spare sectors per track\n");
E 22
D 31
		fprintf(stderr, "\t-a spare sectors per cylinder\n");
E 31
I 31
		fprintf(stderr, "\t-x spare sectors per cylinder\n");
E 31
I 23
		fprintf(stderr, "\t-l hardware sector interleave\n");
		fprintf(stderr, "\t-k sector 0 skew, per track\n");
E 23
E 21
E 14
E 6
E 5
		exit(1);
	}
E 43
I 31
D 33
	if (maxbpg == 0)
		maxbpg = MAXBLKPG(bsize);
E 33
E 31
	special = argv[0];
D 12
again:
E 12
I 12
D 66
	cp = rindex(special, '/');
E 66
I 66
	cp = strrchr(special, '/');
E 66
D 44
	if (cp != 0)
		special = cp + 1;
D 13
	if (*special == 'r')
E 13
I 13
D 42
	if (*special == 'r' && special[1] != 'a' && special[1] != 'b')
E 42
I 42
	if (*special == 'r'
#if defined(vax) || defined(tahoe)
D 43
	    && special[1] != 'a' && special[1] != 'b'
E 43
I 43
	    && special[1] != 'a' && special[1] != 'b')
E 43
#endif
#if defined(hp300)
D 43
	    && special[1] != 'd'
E 43
I 43
	    && special[1] != 'd')
E 43
#endif
D 43
	   )
E 43
E 42
E 13
		special++;
D 34
	special = sprintf(device, "/dev/r%s", special);
E 34
I 34
D 37
	(void)sprintf(device, "/dev/r%s", special);
E 37
I 37
	(void)sprintf(device, "%s/r%s", _PATH_DEV, special);
E 37
	special = device;
E 44
I 44
	if (cp == 0) {
		/*
		 * No path prefix; try /dev/r%s then /dev/%s.
		 */
		(void)sprintf(device, "%sr%s", _PATH_DEV, special);
		if (stat(device, &st) == -1)
			(void)sprintf(device, "%s%s", _PATH_DEV, special);
		special = device;
	}
E 44
E 34
E 12
D 21
	if (stat(special, &st) < 0) {
E 21
I 21
D 51
	if (!Nflag) {
E 51
I 51
	if (Nflag) {
		fso = -1;
	} else {
E 51
		fso = open(special, O_WRONLY);
D 43
		if (fso < 0) {
			perror(special);
D 39
			exit(1);
E 39
I 39
			exit(2);
E 39
		}
E 43
I 43
		if (fso < 0)
			fatal("%s: %s", special, strerror(errno));
E 43
D 51
	} else
		fso = -1;
E 51
I 51

		/* Bail if target special is mounted */
		n = getmntinfo(&mp, MNT_NOWAIT);
		if (n == 0)
			fatal("%s: getmntinfo: %s", special, strerror(errno));

		len = sizeof(_PATH_DEV) - 1;
		s1 = special;
		if (strncmp(_PATH_DEV, s1, len) == 0)
			s1 += len;

		while (--n >= 0) {
			s2 = mp->f_mntfromname;
			if (strncmp(_PATH_DEV, s2, len) == 0) {
				s2 += len - 1;
				*s2 = 'r';
			}
			if (strcmp(s1, s2) == 0 || strcmp(s1, &s2[1]) == 0)
				fatal("%s is mounted on %s",
				    special, mp->f_mntonname);
			++mp;
		}
	}
E 51
D 53
	fsi = open(special, O_RDONLY);
D 43
	if (fsi < 0) {
		perror(special);
D 39
		exit(1);
E 39
I 39
		exit(3);
E 39
	}
	if (fstat(fsi, &st) < 0) {
E 21
D 12
		if (*special != '/') {
D 5
			special = sprintf(device, "/dev/%s", argv[0]);
E 5
I 5
			if (*special == 'r')
				special++;
			special = sprintf(device, "/dev/r%s", special);
E 5
			goto again;
		}
E 12
D 7
		fprintf(stderr, "makefs: "); perror(special);
E 7
I 7
D 39
		fprintf(stderr, "newfs: "); perror(special);
E 7
		exit(2);
E 39
I 39
		fprintf(stderr, "%s: ", progname); perror(special);
		exit(4);
E 39
	}
E 43
I 43
	if (fsi < 0)
		fatal("%s: %s", special, strerror(errno));
	if (fstat(fsi, &st) < 0)
		fatal("%s: %s", special, strerror(errno));
E 43
D 12
	if ((st.st_mode & S_IFMT) != S_IFBLK &&
	    (st.st_mode & S_IFMT) != S_IFCHR)
		fatal("%s: not a block or character device", special);
E 12
I 12
D 46
	if ((st.st_mode & S_IFMT) != S_IFCHR)
D 44
		fatal("%s: not a character device", special);
E 44
I 44
		printf("%s: not a character device\n", special);
E 46
I 46
	if ((st.st_mode & S_IFMT) != S_IFCHR && !mfs)
		printf("%s: %s: not a character-special device\n",
		    progname, special);
E 46
E 44
E 12
D 21
	dp = getdiskbyname(argv[1]);
	if (dp == 0)
		fatal("%s: unknown disk type", argv[1]);
E 21
	cp = index(argv[0], '\0') - 1;
D 21
	if (cp == 0 || *cp < 'a' || *cp > 'h')
E 21
I 21
	if (cp == 0 || (*cp < 'a' || *cp > 'h') && !isdigit(*cp))
E 21
		fatal("%s: can't figure out file system partition", argv[0]);
E 53
I 53
	if (mfs && disktype != NULL) {
		lp = (struct disklabel *)getdiskbyname(disktype);
		if (lp == NULL)
			fatal("%s: unknown disk type", disktype);
		pp = &lp->d_partitions[1];
	} else {
		fsi = open(special, O_RDONLY);
		if (fsi < 0)
			fatal("%s: %s", special, strerror(errno));
		if (fstat(fsi, &st) < 0)
			fatal("%s: %s", special, strerror(errno));
		if ((st.st_mode & S_IFMT) != S_IFCHR && !mfs)
			printf("%s: %s: not a character-special device\n",
			    progname, special);
D 66
		cp = index(argv[0], '\0') - 1;
E 66
I 66
		cp = strchr(argv[0], '\0') - 1;
E 66
D 68
		if (cp == 0 || (*cp < 'a' || *cp > 'h') && !isdigit(*cp))
E 68
I 68
D 69
		if (cp == -1 || (*cp < 'a' || *cp > 'h') && !isdigit(*cp))
E 69
I 69
		if (cp == (char *)-1 ||
		    (*cp < 'a' || *cp > 'h') && !isdigit(*cp))
E 69
E 68
			fatal("%s: can't figure out file system partition",
			    argv[0]);
E 53
I 29
#ifdef COMPAT
D 42
	lp = getdisklabel(special, fsi, argv[1]);
#else
E 29
D 21
	pp = &dp->d_partitions[*cp - 'a'];
	if (fssize == 0) {
E 21
I 21
	lp = getdisklabel(special, fsi);
E 42
I 42
D 53
	if (!mfs && disktype == NULL)
		disktype = argv[1];
E 53
I 53
		if (!mfs && disktype == NULL)
			disktype = argv[1];
E 53
E 42
I 29
#endif
I 42
D 53
	lp = getdisklabel(special, fsi);
E 42
E 29
	if (isdigit(*cp))
		pp = &lp->d_partitions[0];
	else
		pp = &lp->d_partitions[*cp - 'a'];
	if (pp->p_size == 0)
		fatal("%s: `%c' partition is unavailable", argv[0], *cp);
E 53
I 53
		lp = getdisklabel(special, fsi);
		if (isdigit(*cp))
			pp = &lp->d_partitions[0];
		else
			pp = &lp->d_partitions[*cp - 'a'];
		if (pp->p_size == 0)
			fatal("%s: `%c' partition is unavailable",
			    argv[0], *cp);
I 54
		if (pp->p_fstype == FS_BOOT)
			fatal("%s: `%c' partition overlaps boot program",
			      argv[0], *cp);
E 54
	}
E 53
	if (fssize == 0)
E 21
		fssize = pp->p_size;
D 21
		if (fssize < 0)
			fatal("%s: no default size for `%c' partition",
				argv[1], *cp);
E 21
I 21
D 39
	if (fssize > pp->p_size)
E 39
I 39
D 40
	if (fssize > pp->p_size && !memfs)
E 40
I 40
	if (fssize > pp->p_size && !mfs)
E 40
E 39
	       fatal("%s: maximum file system size on the `%c' partition is %d",
			argv[0], *cp, pp->p_size);
	if (rpm == 0) {
		rpm = lp->d_rpm;
		if (rpm <= 0)
D 26
			fatal("%s: no default rpm", argv[1]);
E 26
I 26
			rpm = 3600;
E 26
E 21
	}
D 21
	if (nsectors == 0) {
		nsectors = dp->d_nsectors;
		if (nsectors < 0)
			fatal("%s: no default #sectors/track", argv[1]);
	}
E 21
	if (ntracks == 0) {
D 21
		ntracks = dp->d_ntracks;
		if (ntracks < 0)
E 21
I 21
		ntracks = lp->d_ntracks;
		if (ntracks <= 0)
E 21
D 26
			fatal("%s: no default #tracks", argv[1]);
E 26
I 26
			fatal("%s: no default #tracks", argv[0]);
E 26
	}
I 21
	if (nsectors == 0) {
		nsectors = lp->d_nsectors;
		if (nsectors <= 0)
D 26
			fatal("%s: no default #sectors/track", argv[1]);
E 26
I 26
			fatal("%s: no default #sectors/track", argv[0]);
E 26
	}
E 21
	if (sectorsize == 0) {
D 21
		sectorsize = dp->d_secsize;
		if (sectorsize < 0)
E 21
I 21
		sectorsize = lp->d_secsize;
		if (sectorsize <= 0)
E 21
D 26
			fatal("%s: no default sector size", argv[1]);
E 26
I 26
			fatal("%s: no default sector size", argv[0]);
E 26
	}
I 22
	if (trackskew == -1) {
		trackskew = lp->d_trackskew;
		if (trackskew < 0)
D 26
			fatal("%s: no default track skew", argv[1]);
E 26
I 26
			trackskew = 0;
E 26
	}
	if (interleave == 0) {
		interleave = lp->d_interleave;
		if (interleave <= 0)
D 26
			fatal("%s: no default interleave", argv[1]);
E 26
I 26
			interleave = 1;
E 26
	}
E 22
D 21
	if (bsize == 0) {
		bsize = pp->p_bsize;
		if (bsize < 0)
			fatal("%s: no default block size for `%c' partition",
				argv[1], *cp);
	}
E 21
	if (fsize == 0) {
		fsize = pp->p_fsize;
D 21
		if (fsize < 0)
			fatal("%s: no default frag size for `%c' partition",
				argv[1], *cp);
E 21
I 21
		if (fsize <= 0)
			fsize = MAX(DFL_FRAGSIZE, lp->d_secsize);
E 21
	}
I 7
D 21
	if (rpm == 0) {
		rpm = dp->d_rpm;
		if (rpm < 0)
			fatal("%s: no default revolutions/minute value",
				argv[1]);
E 21
I 21
	if (bsize == 0) {
		bsize = pp->p_frag * pp->p_fsize;
		if (bsize <= 0)
			bsize = MIN(DFL_BLKSIZE, 8 * fsize);
E 21
	}
I 55
	/*
	 * Maxcontig sets the default for the maximum number of blocks
	 * that may be allocated sequentially. With filesystem clustering
	 * it is possible to allocate contiguous blocks up to the maximum
	 * transfer size permitted by the controller or buffering.
	 */
	if (maxcontig == 0)
D 61
		maxcontig = MAX(1, MIN(MAXPHYS, MAXBSIZE) / bsize);
E 61
I 61
D 65
		maxcontig = MAX(1, MIN(MAXPHYS, MAXBSIZE) / bsize - 1);
E 65
I 65
		maxcontig = MAX(1, MIN(MAXPHYS, MAXBSIZE) / bsize);
E 65
E 61
E 55
I 39
	if (density == 0)
		density = NFPI * fsize;
E 39
I 14
D 21
	if (density <= 0)
		density = 2048;
E 14
D 9
	if (minfree == 0)
E 9
I 9
	if (minfree < 0)
E 9
		minfree = 10;
E 21
I 19
D 56
	if (minfree < 10 && opt != FS_OPTSPACE) {
E 56
I 56
	if (minfree < MINFREE && opt != FS_OPTSPACE) {
E 56
D 21
		fprintf(stderr, "setting optimization for space ");
		fprintf(stderr, "with minfree less than 10%\n");
E 21
I 21
		fprintf(stderr, "Warning: changing optimization to space ");
D 56
		fprintf(stderr, "because minfree is less than 10%%\n");
E 56
I 56
		fprintf(stderr, "because minfree is less than %d%%\n", MINFREE);
E 56
E 21
		opt = FS_OPTSPACE;
	}
E 19
D 21
	if (cpg == 0)
		cpg = 16;
E 7
	i = 0;
I 17
	if (Nflag)
		av[i++] = "-N";
	av[i++] = special;
E 17
	av[i++] = sprintf(a2, "%d", fssize);
	av[i++] = sprintf(a3, "%d", nsectors);
	av[i++] = sprintf(a4, "%d", ntracks);
	av[i++] = sprintf(a5, "%d", bsize);
	av[i++] = sprintf(a6, "%d", fsize);
D 7
	if (cpg != 0)
		av[i++] = sprintf(a7, "%d", cpg);
E 7
I 7
	av[i++] = sprintf(a7, "%d", cpg);
	av[i++] = sprintf(a8, "%d", minfree);
	av[i++] = sprintf(a9, "%d", rpm / 60);
I 14
	av[i++] = sprintf(a10, "%d", density);
I 19
	av[i++] = opt == FS_OPTSPACE ? "s" : "t";
E 19
E 14
E 7
	av[i++] = 0;
D 17
	sprintf(cmd, "/etc/mkfs %s", special);
E 17
I 17
	strcpy(cmd, "/etc/mkfs");
E 17
	for (i = 0; av[i] != 0; i++) {
		strcat(cmd, " ");
		strcat(cmd, av[i]);
E 21
I 21
D 22
	if (nspares == -1)
		nspares = lp->d_sparespercyl;
	secpercyl = nsectors * ntracks - nspares;
E 22
I 22
	if (trackspares == -1) {
		trackspares = lp->d_sparespertrack;
		if (trackspares < 0)
D 26
			fatal("%s: no default spares/track", argv[1]);
E 26
I 26
			trackspares = 0;
E 26
	}
	nphyssectors = nsectors + trackspares;
	if (cylspares == -1) {
		cylspares = lp->d_sparespercyl;
		if (cylspares < 0)
D 26
			fatal("%s: no default spares/cylinder", argv[1]);
E 26
I 26
			cylspares = 0;
E 26
	}
	secpercyl = nsectors * ntracks - cylspares;
E 22
	if (secpercyl != lp->d_secpercyl)
D 43
		fprintf(stderr, "%s (%d) %s (%d)\n",
E 43
I 43
		fprintf(stderr, "%s (%d) %s (%lu)\n",
E 43
			"Warning: calculated sectors per cylinder", secpercyl,
			"disagrees with disk label", lp->d_secpercyl);
I 33
	if (maxbpg == 0)
		maxbpg = MAXBLKPG(bsize);
E 33
I 22
	headswitch = lp->d_headswitch;
	trackseek = lp->d_trkseek;
I 45
	/* Reno fix: label may be 0 if faked up by kernel */
#ifdef notdef
E 45
I 44
#ifdef notdef /* label may be 0 if faked up by kernel */
E 44
I 25
	bbsize = lp->d_bbsize;
	sbsize = lp->d_sbsize;
I 45
#endif
E 45
I 44
#endif
E 44
E 25
E 22
	oldpartition = *pp;
I 25
#ifdef tahoe
	realsectorsize = sectorsize;
D 27
	if (sectorsize != DEV_BSIZE) {
E 27
I 27
	if (sectorsize != DEV_BSIZE) {		/* XXX */
E 27
		int secperblk = DEV_BSIZE / sectorsize;

		sectorsize = DEV_BSIZE;
		nsectors /= secperblk;
		nphyssectors /= secperblk;
		secpercyl /= secperblk;
		fssize /= secperblk;
		pp->p_size /= secperblk;
	}
#endif
E 25
	mkfs(pp, special, fsi, fso);
I 25
#ifdef tahoe
	if (realsectorsize != DEV_BSIZE)
		pp->p_size *= DEV_BSIZE / realsectorsize;
#endif
E 25
D 67
	if (!Nflag && bcmp(pp, &oldpartition, sizeof(oldpartition)))
E 67
I 67
	if (!Nflag && memcmp(pp, &oldpartition, sizeof(oldpartition)))
E 67
		rewritelabel(special, fso, lp);
I 39
	if (!Nflag)
		close(fso);
	close(fsi);
I 47
#ifdef MFS
E 47
D 40
	if (memfs) {
		sprintf(buf, "memfs:%d", getpid());
E 40
I 40
	if (mfs) {
I 47
		struct mfs_args args;

E 47
		sprintf(buf, "mfs:%d", getpid());
E 40
D 58
		args.name = buf;
E 58
I 58
		args.fspec = buf;
		args.export.ex_root = -2;
		if (mntflags & MNT_RDONLY)
			args.export.ex_flags = MNT_EXRDONLY;
		else
			args.export.ex_flags = 0;
E 58
		args.base = membase;
		args.size = fssize * sectorsize;
D 40
		if (mount(MOUNT_MFS, argv[1], 0, &args) < 0) {
			perror("memfs: mount");
E 40
I 40
D 43
		if (mount(MOUNT_MFS, argv[1], mntflags, &args) < 0) {
			perror("mfs: mount");
E 40
			exit(5);
		}
E 43
I 43
D 69
		if (mount(MOUNT_MFS, argv[1], mntflags, &args) < 0)
E 69
I 69
		if (mount("mfs", argv[1], mntflags, &args) < 0)
E 69
			fatal("%s: %s", argv[1], strerror(errno));
E 43
	}
I 47
#endif
E 47
E 39
	exit(0);
}

I 29
#ifdef COMPAT
E 29
D 25
#ifdef byioctl
E 25
D 42
struct disklabel *
I 29
getdisklabel(s, fd, type)
	char *s, *type;
	int fd;
{
	static struct disklabel lab;
	struct disklabel *getdiskbyname();

	if (ioctl(fd, DIOCGDINFO, (char *)&lab) < 0) {
		if (type == NULL) {
			perror("ioctl (GDINFO)");
			fatal(
		   "%s: can't read disk label; disk type must be specified", s);
		}
		unlabelled++;
		return (getdiskbyname(type));
	}
	return (&lab);
}
E 42
I 42
char lmsg[] = "%s: can't read disk label; disk type must be specified";
E 42
#else
I 42
char lmsg[] = "%s: can't read disk label";
#endif

E 42
struct disklabel *
E 29
getdisklabel(s, fd)
	char *s;
D 29
	int	fd;
E 29
I 29
	int fd;
E 29
{
	static struct disklabel lab;

	if (ioctl(fd, DIOCGDINFO, (char *)&lab) < 0) {
I 42
#ifdef COMPAT
		if (disktype) {
D 44
			struct disklabel *getdiskbyname();
E 44
I 44
			struct disklabel *lp, *getdiskbyname();
E 44

D 43
			unlabelled++;
E 43
I 43
			unlabeled++;
E 43
D 44
			return (getdiskbyname(disktype));
E 44
I 44
			lp = getdiskbyname(disktype);
			if (lp == NULL)
				fatal("%s: unknown disk type", disktype);
			return (lp);
E 44
		}
#endif
E 42
D 43
		perror("ioctl (GDINFO)");
E 43
I 43
D 60
		(void)fprintf(stderr,
		    "%s: ioctl (GDINFO): %s\n", progname, strerror(errno));
E 60
I 60
		warn("ioctl (GDINFO)");
E 60
E 43
D 42
		fatal("%s: can't read disk label", s);
E 42
I 42
		fatal(lmsg, s);
E 42
E 21
	}
D 21
	if (verbose)
		printf("%s\n", cmd);
D 3
#ifdef notdef
E 3
	if (status = system(cmd))
D 15
		exit(status);
E 15
I 15
		exit(status >> 8);
E 15
D 3
#endif
E 3
D 9
	if (*cp == 'a') {
E 9
I 9
	if (*cp == 'a' && !noboot) {
E 9
		char type[3];
I 11
		struct stat sb;
E 21
I 21
	return (&lab);
}
I 29
D 42
#endif
E 42
E 29
E 21
E 11

D 21
		cp = rindex(special, '/');
		if (cp == NULL)
			fatal("%s: can't figure out disk type from name",
				special);
I 5
D 11
		if (cp[1] == 'r')
E 11
I 11
		if (stat(special, &sb) >= 0 && (sb.st_mode & S_IFMT) == S_IFCHR)
E 11
			cp++;
E 5
		type[0] = *++cp;
		type[1] = *++cp;
		type[2] = '\0';
		installboot(special, type);
E 21
I 21
rewritelabel(s, fd, lp)
	char *s;
	int fd;
	register struct disklabel *lp;
{
D 43

E 43
I 29
#ifdef COMPAT
D 43
	if (unlabelled)
E 43
I 43
	if (unlabeled)
E 43
		return;
#endif
E 29
	lp->d_checksum = 0;
	lp->d_checksum = dkcksum(lp);
	if (ioctl(fd, DIOCWDINFO, (char *)lp) < 0) {
D 35
		perror("ioctl (GWINFO)");
E 35
I 35
D 43
		perror("ioctl (WDINFO)");
E 43
I 43
D 60
		(void)fprintf(stderr,
		    "%s: ioctl (WDINFO): %s\n", progname, strerror(errno));
E 60
I 60
		warn("ioctl (WDINFO)");
E 60
E 43
E 35
		fatal("%s: can't rewrite disk label", s);
E 21
	}
D 21
	exit(0);
E 21
D 25
}
I 21
#else byioctl
char specname[64];
char boot[BBSIZE];
E 21

D 21
installboot(dev, type)
	char *dev, *type;
E 21
I 21
struct disklabel *
getdisklabel(s, fd)
	char *s;
	int	fd;
E 21
{
I 20
D 21
#ifdef BOOTDIR
E 20
	int fd;
	char bootblock[MAXPATHLEN], standalonecode[MAXPATHLEN];
	char bootimage[BBSIZE];
E 21
I 21
	char *cp;
	u_long magic = htonl(DISKMAGIC);
	register struct disklabel *lp;
	int cfd;
E 21

D 8
	sprintf(bootblock, "/sys/mdec/%sboot", type);
	sprintf(standalonecode, "/sys/stand/boot%s", type);
E 8
I 8
D 21
	sprintf(bootblock, "%s/%sboot", BOOTDIR, type);
	sprintf(standalonecode, "%s/boot%s", BOOTDIR, type);
E 8
	if (verbose) {
		printf("installing boot code\n");
		printf("sector 0 boot = %s\n", bootblock);
		printf("1st level boot = %s\n", standalonecode);
E 21
I 21
	/*
	 * Make name for 'c' partition.
	 */
	strcpy(specname, s);
	cp = specname + strlen(specname) - 1;
	if (!isdigit(*cp))
		*cp = 'c';
	cfd = open(specname, O_RDONLY);
	if (cfd < 0) {
		perror(specname);
		exit(2);
E 21
	}
D 21
	fd = open(bootblock, 0);
	if (fd < 0) {
D 7
		fprintf(stderr, "makefs: "); perror(bootblock);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(bootblock);
E 7
		exit(1);
	}
	if (read(fd, bootimage, DEV_BSIZE) < 0) {
D 7
		fprintf(stderr, "makefs: "); perror(bootblock);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(bootblock);
E 21
I 21

	if (read(cfd, boot, BBSIZE) < BBSIZE) {
		perror(specname);
E 21
E 7
		exit(2);
	}
D 21
	close(fd);
	fd = open(standalonecode, 0);
	if (fd < 0) {
D 7
		fprintf(stderr, "makefs: "); perror(standalonecode);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(standalonecode);
E 21
I 21
	close(cfd);
	for (lp = (struct disklabel *)(boot + LABELOFFSET);
	    lp <= (struct disklabel *)(boot + BBSIZE -
	    sizeof(struct disklabel));
	    lp = (struct disklabel *)((char *)lp + 128))
		if (lp->d_magic == magic && lp->d_magic2 == magic)
			break;
	if (lp > (struct disklabel *)(boot + BBSIZE -
	    sizeof(struct disklabel)) ||
	    lp->d_magic != magic || lp->d_magic2 != magic ||
	    dkcksum(lp) != 0) {
		fprintf(stderr,
	"Bad pack magic number (label is damaged, or pack is unlabeled)\n");
E 21
E 7
		exit(1);
	}
D 21
	if (read(fd, &bootimage[DEV_BSIZE], BBSIZE - DEV_BSIZE) < 0) {
D 7
		fprintf(stderr, "makefs: "); perror(standalonecode);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(standalonecode);
E 21
I 21
D 24
#if ENDIAN != BIG
	swablabel(lp);
#endif
E 24
	return (lp);
}

rewritelabel(s, fd, lp)
	char *s;
	int fd;
	register struct disklabel *lp;
{
D 24
	daddr_t alt;
	register i;
	int secsize, cfd;
E 24
I 24
	int cfd;
E 24

D 24
	secsize = lp->d_secsize;
	alt = lp->d_ncylinders * lp->d_secpercyl - lp->d_nsectors;
#if ENDIAN != BIG
	swablabel(lp);
#endif
E 24
	lp->d_checksum = 0;
	lp->d_checksum = dkcksum(lp);
	cfd = open(specname, O_WRONLY);
	if (cfd < 0) {
		perror(specname);
E 21
E 7
		exit(2);
	}
D 21
	close(fd);
D 3
#ifdef notdef
	fd = open(special, 1);
E 3
I 3
	fd = open(dev, 1);
E 3
	if (fd < 0) {
D 3
		fprintf(stderr, "makefs: "); perror(special);
E 3
I 3
D 7
		fprintf(stderr, "makefs: "); perror(dev);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(dev);
E 7
E 3
		exit(1);
	}
	if (write(fd, bootimage, BBSIZE) != BBSIZE) {
D 3
		fprintf(stderr, "makefs: "); perror(special);
E 3
I 3
D 7
		fprintf(stderr, "makefs: "); perror(dev);
E 7
I 7
		fprintf(stderr, "newfs: "); perror(dev);
E 21
I 21
	lseek(cfd, (off_t)0, L_SET);
	if (write(cfd, boot, BBSIZE) < BBSIZE) {
		perror(specname);
E 21
E 7
E 3
		exit(2);
	}
E 25
D 21
	close(fd);
I 20
#endif
E 21
I 21
D 24
	for (i = 1; i < 11 && i < lp->d_nsectors; i += 2) {
		lseek(cfd, (off_t)(alt + i) * secsize, L_SET);
		if (write(cfd, boot, secsize) < secsize) {
			int oerrno = errno;
			fprintf(stderr, "alternate label %d ", i/2);
			errno = oerrno;
			perror("write");
E 24
I 24
#if vax
	if (lp->d_type == DTYPE_SMD && lp->d_flags & D_BADSECT) {
		register i;
I 25
		int cfd;
E 25
		daddr_t alt;
I 25
		char specname[64];
		char blk[1024];
I 28
		char *cp;
E 28
E 25

I 25
		/*
		 * Make name for 'c' partition.
		 */
		strcpy(specname, s);
		cp = specname + strlen(specname) - 1;
		if (!isdigit(*cp))
			*cp = 'c';
		cfd = open(specname, O_WRONLY);
D 43
		if (cfd < 0) {
			perror(specname);
D 39
			exit(2);
E 39
I 39
			exit(6);
E 39
		}
E 43
I 43
		if (cfd < 0)
			fatal("%s: %s", specname, strerror(errno));
E 43
D 66
		bzero(blk, sizeof(blk));
E 66
I 66
		memset(blk, 0, sizeof(blk));
E 66
		*(struct disklabel *)(blk + LABELOFFSET) = *lp;
E 25
		alt = lp->d_ncylinders * lp->d_secpercyl - lp->d_nsectors;
		for (i = 1; i < 11 && i < lp->d_nsectors; i += 2) {
D 29
			lseek(cfd, (off_t)(alt + i) * lp->d_secsize, L_SET);
E 29
I 29
D 44
			if (lseek(cfd, (off_t)(alt + i) * lp->d_secsize, L_SET) == -1) {
E 44
I 44
			if (lseek(cfd, (off_t)(alt + i) * lp->d_secsize,
			    L_SET) == -1)
E 44
D 43
				perror("lseek to badsector area");
D 39
				exit(30);
E 39
I 39
				exit(7);
E 39
			}
E 29
D 25
			if (write(cfd, boot, lp->d_secsize) < lp->d_secsize) {
E 25
I 25
			if (write(cfd, blk, lp->d_secsize) < lp->d_secsize) {
E 25
				int oerrno = errno;
				fprintf(stderr, "alternate label %d ", i/2);
				errno = oerrno;
				perror("write");
			}
E 43
I 43
				fatal("lseek to badsector area: %s",
				    strerror(errno));
			if (write(cfd, blk, lp->d_secsize) < lp->d_secsize)
D 60
				fprintf(stderr,
				    "%s: alternate label %d write: %s\n",
				    progname, i/2, strerror(errno));
E 60
I 60
				warn("alternate label %d write", i/2);
E 60
E 43
E 24
		}
I 39
		close(cfd);
E 39
	}
I 24
#endif
E 24
D 25
	close(cfd);
E 25
E 21
E 20
D 3
#endif
E 3
}
I 21
D 25
#endif byioctl
E 25
E 21

/*VARARGS*/
D 43
fatal(fmt, arg1, arg2)
E 43
I 43
D 49
fatal(fmt)
E 49
I 49
void
#if __STDC__
fatal(const char *fmt, ...)
#else
fatal(fmt, va_alist)
E 49
E 43
	char *fmt;
I 49
	va_dcl
#endif
E 49
{
I 43
	va_list ap;
E 43

D 7
	fprintf(stderr, "makefs: ");
E 7
I 7
D 39
	fprintf(stderr, "newfs: ");
E 39
I 39
D 49
	fprintf(stderr, "%s: ", progname);
E 49
I 49
#if __STDC__
E 49
E 39
E 7
D 43
	fprintf(stderr, fmt, arg1, arg2);
E 43
I 43
	va_start(ap, fmt);
I 49
#else
	va_start(ap);
#endif
D 60
	fprintf(stderr, "%s: ", progname);
E 49
	(void)vfprintf(stderr, fmt, ap);
E 60
I 60
	if (fcntl(STDERR_FILENO, F_GETFL) < 0) {
		openlog(progname, LOG_CONS, LOG_DAEMON);
		vsyslog(LOG_ERR, fmt, ap);
		closelog();
	} else {
		vwarnx(fmt, ap);
	}
E 60
	va_end(ap);
E 43
D 60
	putc('\n', stderr);
E 60
D 39
	exit(10);
E 39
I 39
D 43
	exit(8);
E 43
I 43
	exit(1);
I 60
	/*NOTREACHED*/
E 60
}

usage()
{
	if (mfs) {
		fprintf(stderr,
D 51
		    "usage: mfs [ -fsoptions ] special-device mount-point\n");
E 51
I 51
		    "usage: %s [ -fsoptions ] special-device mount-point\n",
			progname);
E 51
	} else
		fprintf(stderr,
D 51
		    "usage: newfs [ -fsoptions ] special-device%s\n",
E 51
I 51
		    "usage: %s [ -fsoptions ] special-device%s\n",
		    progname,
E 51
#ifdef COMPAT
		    " [device-type]");
#else
		    "");
#endif
	fprintf(stderr, "where fsoptions are:\n");
	fprintf(stderr,
	    "\t-N do not create file system, just print out parameters\n");
I 56
	fprintf(stderr, "\t-O create a 4.3BSD format filesystem\n");
E 56
	fprintf(stderr, "\t-S sector size\n");
#ifdef COMPAT
	fprintf(stderr, "\t-T disktype\n");
#endif
	fprintf(stderr, "\t-a maximum contiguous blocks\n");
	fprintf(stderr, "\t-b block size\n");
	fprintf(stderr, "\t-c cylinders/group\n");
	fprintf(stderr, "\t-d rotational delay between contiguous blocks\n");
	fprintf(stderr, "\t-e maximum blocks per file in a cylinder group\n");
	fprintf(stderr, "\t-f frag size\n");
	fprintf(stderr, "\t-i number of bytes per inode\n");
	fprintf(stderr, "\t-k sector 0 skew, per track\n");
	fprintf(stderr, "\t-l hardware sector interleave\n");
	fprintf(stderr, "\t-m minimum free space %%\n");
	fprintf(stderr, "\t-n number of distinguished rotational positions\n");
	fprintf(stderr, "\t-o optimization preference (`space' or `time')\n");
	fprintf(stderr, "\t-p spare sectors per track\n");
	fprintf(stderr, "\t-s file system size (sectors)\n");
	fprintf(stderr, "\t-r revolutions/minute\n");
	fprintf(stderr, "\t-t tracks/cylinder\n");
	fprintf(stderr, "\t-u sectors/track\n");
	fprintf(stderr, "\t-x spare sectors per cylinder\n");
	exit(1);
E 43
E 39
}
E 1
