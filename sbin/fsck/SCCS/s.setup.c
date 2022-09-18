h20599
s 00013/00002/00461
d D 8.10 95/05/09 15:45:12 mckusick 59 58
c check and act on the clean flag
e
s 00008/00011/00455
d D 8.9 95/04/28 10:38:15 bostic 58 57
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00021/00011/00445
d D 8.8 95/04/27 11:33:09 mckusick 57 56
c add function prototypes
e
s 00001/00001/00455
d D 8.7 95/03/21 00:10:52 mckusick 56 55
c daddr_t => ufs_daddr_t
e
s 00003/00001/00453
d D 8.6 95/01/06 17:35:45 mckusick 55 54
c paranoia (from mycroft)
e
s 00015/00000/00439
d D 8.5 94/11/23 14:30:43 mckusick 54 53
c have to copy fs_maxcluster
e
s 00002/00004/00437
d D 8.4 94/08/14 16:38:14 mckusick 53 52
c cg_link => cg_firstfield; fs_link => fs_firstfield
e
s 00001/00000/00440
d D 8.3 94/05/06 17:00:41 mckusick 52 51
c copy fs_state before checking alternate superblock to keep SunOS happy
e
s 00000/00014/00440
d D 8.2 94/02/21 06:50:27 mkm 51 50
c get rid of redundant CGSIZE definition
e
s 00002/00002/00452
d D 8.1 93/06/05 10:56:54 bostic 50 49
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00453
d D 5.43 93/06/04 11:42:19 bostic 49 48
c rename devname to cdevname, devname(3) now in the C library
e
s 00001/00000/00453
d D 5.42 92/11/15 11:58:26 mckusick 48 47
c avoid core dumps and panics when interrupting fsck early
e
s 00002/00001/00451
d D 5.41 92/07/16 12:50:18 mckusick 47 46
c have to reset newinofmt flag
e
s 00045/00066/00407
d D 5.40 92/06/26 10:14:27 mckusick 46 45
c add support for converting to and checking new inode format filesystems;
c eliminate conversion back to pre-fat filesystems
e
s 00011/00000/00462
d D 5.39 92/06/22 15:35:03 mckusick 45 44
c calculate important constants if needed
e
s 00004/00000/00458
d D 5.38 92/06/17 10:04:16 mckusick 44 43
c allow for new fields
e
s 00001/00000/00457
d D 5.37 92/05/27 22:45:29 mckusick 43 42
c add <sys/time.h> for dinode.h
e
s 00004/00004/00453
d D 5.36 92/05/17 16:21:33 mckusick 42 41
c do not have to have alternate superblock if -b is specified
e
s 00011/00012/00446
d D 5.35 91/12/19 12:51:30 mckusick 41 40
c add quad support
e
s 00002/00002/00456
d D 5.34 91/11/04 22:20:37 bostic 40 39
c break FFS into UFS/FFS/LFS
e
s 00008/00000/00450
d D 5.33 91/02/22 18:20:04 mckusick 39 38
c On tahoe, must use secsize of 1024, even though the disk label claims 512
e
s 00004/00002/00446
d D 5.32 90/07/22 19:30:15 mckusick 38 37
c additional sanity checks
e
s 00015/00015/00433
d D 5.31 90/07/20 16:51:30 mckusick 37 36
c lint (from Torek)
e
s 00001/00001/00447
d D 5.30 90/06/26 14:59:31 mckusick 36 35
c missing newline in error message
e
s 00001/00011/00447
d D 5.29 90/06/01 16:17:56 bostic 35 34
c new copyright notice
e
s 00005/00010/00453
d D 5.28 90/05/05 13:04:48 mckusick 34 33
c do not need to check for root device as blockcheck has done so already;
c complain when presented with a block device
e
s 00001/00000/00462
d D 5.27 90/03/07 15:30:05 mckusick 33 32
c initialize inplast (from shumway@sun.com)
e
s 00011/00001/00451
d D 5.26 90/02/07 00:10:14 mckusick 32 31
c allocate hash headers and sort list
e
s 00015/00004/00437
d D 5.25 90/02/01 17:17:31 mckusick 31 30
c convert to BSD only copyright
e
s 00028/00032/00413
d D 5.24 90/02/01 16:17:47 mckusick 30 29
c lint and other aesthetic cleanups
e
s 00001/00003/00444
d D 5.23 89/10/24 19:05:32 mckusick 29 28
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00007/00007/00440
d D 5.22 89/06/30 17:00:34 mckusick 28 27
c ANSI C cleanups from Torek
e
s 00004/00002/00443
d D 5.21 89/06/26 21:51:46 mckusick 27 26
c new include file locations engendered by vnodes
e
s 00017/00000/00428
d D 5.20 89/06/26 21:51:04 mckusick 26 25
c recalculate size of cylinder group block when changing formats
e
s 00006/00004/00422
d D 5.19 88/05/07 01:04:16 mckusick 25 24
c expand from three static buffer to a dynamic buffer pool;
c initial sizing of the buffer pool is 128K (For 8K fs == 16 buffers)
e
s 00029/00017/00397
d D 5.18 88/05/02 15:56:10 mckusick 24 23
c conversion (in either direction) is only done when requested with -c
e
s 00070/00020/00344
d D 5.17 88/05/01 23:40:39 mckusick 23 22
c conversion between static and dynamic cylinder group tables;
c force write of last alternate super block when adding new constants
c (to avoid comparison errors during normal super block checking)
e
s 00008/00003/00356
d D 5.16 88/04/06 18:52:11 mckusick 22 21
c recover from trashed summary information
e
s 00001/00000/00358
d D 5.15 87/12/21 12:43:38 bostic 21 20
c make ANSI C compatible
e
s 00028/00012/00330
d D 5.14 87/04/07 19:49:20 karels 20 19
c fix alternate superblock location again; don't offer to rewrite
c standard superblock if we haven't found a good one yet; standardize units
c for -b (sectors! as before); kernel may change fs_dbsize
e
s 00000/00008/00342
d D 5.13 87/03/11 20:10:23 karels 19 18
c huh? where did this come from?
e
s 00015/00005/00327
d D 5.12 87/03/11 20:06:26 karels 18 17
c use physical sector size for partial buffer reads;
c -n implies "yes" answer for "CONTINUE?"
e
s 00008/00003/00329
d D 5.11 87/03/09 14:49:59 mckusick 17 16
c make fixing interleave non-fatal
e
s 00004/00006/00328
d D 5.10 87/03/05 12:46:53 mckusick 16 15
c allow fsck to proceed even when not setting default psect and interleave
e
s 00012/00056/00322
d D 5.9 87/02/26 17:44:54 karels 15 14
c update disk labels to ioctl's; check the file the user specified!;
c don't try to check "." if a named file doesn't exist;
c don't check spare constants in superblock against alternate;
c make the "TRASHED VALUES" message understandable
e
s 00003/00003/00375
d D 5.8 87/02/23 14:42:19 mckusick 14 13
c use SBOFF instead of SBLOCK
e
s 00003/00000/00375
d D 5.7 87/02/18 18:14:43 mckusick 13 12
c intuit the appropriate DEV_BSIZE from fsbtodb macro
e
s 00002/00000/00373
d D 5.6 87/01/17 11:35:23 mckusick 12 11
c must copy fs_npsect and fs_interleave to cope for old file systems
e
s 00016/00000/00357
d D 5.5 87/01/15 21:29:06 mckusick 11 10
c add sanity checks for new values used in calculating rotational layout
e
s 00230/00064/00127
d D 5.4 87/01/15 21:28:08 mckusick 10 9
c reorganize to allow use of disk labels to search for alternate
c super-blocks when the standard super-block is unusable
e
s 00018/00000/00173
d D 5.3 86/05/15 13:40:24 mckusick 9 8
c add error messages for bad minfree and optimization values
e
s 00001/00000/00172
d D 5.2 85/09/11 21:22:38 mckusick 8 7
c must account for fs_optim field in check
e
s 00008/00002/00164
d D 5.1 85/06/05 08:58:18 dist 7 6
c Add copyright
e
s 00000/00001/00166
d D 3.6 85/06/02 16:47:16 mckusick 6 5
c dynamically allocate zero link count table
e
s 00000/00001/00167
d D 3.5 85/05/31 20:08:51 mckusick 5 4
c dynamically allocate the duplicate block table
e
s 00004/00004/00164
d D 3.4 85/05/31 00:19:38 mckusick 4 3
c check for improper directory offsets; recover gracefully from read errors
e
s 00000/00008/00168
d D 3.3 85/02/08 19:15:55 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00003/00014/00173
d D 3.2 85/02/07 17:52:21 mckusick 2 1
c code reorganization and cleanup
e
s 00187/00000/00000
d D 3.1 84/03/31 21:03:54 mckusick 1 0
c date and time created 84/03/31 21:03:54 by mckusick
e
u
U
t
T
I 7
/*
D 31
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
D 50
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 50
I 50
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 50
 *
D 35
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
E 35
I 35
 * %sccs.include.redist.c%
E 35
E 31
 */

E 7
I 1
#ifndef lint
D 7
static char version[] = "%W% (Berkeley) %G%";
#endif
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 31
#endif not lint
E 31
I 31
#endif /* not lint */
E 31
E 7

I 10
#define DKTYPENAMES
E 10
#include <sys/param.h>
I 43
#include <sys/time.h>
E 43
D 27
#include <sys/inode.h>
#include <sys/fs.h>
E 27
I 27
D 29
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 29
I 29
D 40
#include <ufs/dinode.h>
E 29
#include <ufs/fs.h>
E 40
I 40
D 57
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
E 57
E 40
E 27
#include <sys/stat.h>
I 10
#include <sys/ioctl.h>
#include <sys/disklabel.h>
#include <sys/file.h>
I 57

#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>

#include <ctype.h>
#include <err.h>
E 57
I 23
D 37
#include <machine/endian.h>
E 37
I 37
#include <errno.h>
D 57
#include <stdlib.h>
E 57
#include <string.h>
E 37
E 23
D 57
#include <ctype.h>
E 57
I 57

E 57
E 10
#include "fsck.h"

I 23
D 30
BUFAREA asblk;
E 30
I 30
struct bufarea asblk;
E 30
D 25
#define altsblock asblk.b_un.b_fs
E 25
I 25
#define altsblock (*asblk.b_un.b_fs)
E 25
E 23
I 10
#define POWEROF2(num)	(((num) & ((num) - 1)) == 0)

I 26
D 51
/*
 * The size of a cylinder group is calculated by CGSIZE. The maximum size
 * is limited by the fact that cylinder groups are at most one block.
 * Its size is derived from the size of the maps maintained in the 
 * cylinder group and the (struct cg) size.
 */
#define CGSIZE(fs) \
    /* base cg */	(sizeof(struct cg) + \
    /* blktot size */	(fs)->fs_cpg * sizeof(long) + \
    /* blks size */	(fs)->fs_cpg * (fs)->fs_nrpos * sizeof(short) + \
    /* inode map */	howmany((fs)->fs_ipg, NBBY) + \
    /* block map */	howmany((fs)->fs_cpg * (fs)->fs_spc / NSPF(fs), NBBY))

E 26
E 10
D 28
char	*calloc();
E 28
I 28
D 37
char	*malloc(), *calloc();
E 37
E 28
I 10
char	*index();
E 51
I 28
D 57
struct	disklabel *getdisklabel();
E 57
I 57
static void badsb __P((int listerr, char *s));
static int calcsb __P((char *dev, int devfd, struct fs *fs));
static struct disklabel *getdisklabel __P((char *s, int fd));
static int readsb __P((int listerr));
E 57
E 28
E 10

I 59
/*
 * Read in a superblock finding an alternate if necessary.
 * Return 1 if successful, 0 if unsuccessful, -1 if filesystem
 * is already clean (preen mode only).
 */
E 59
I 57
int
E 57
setup(dev)
	char *dev;
{
D 34
	dev_t rootdev;
E 34
I 10
D 22
	long cg, ncg, size, i, j;
E 22
I 22
D 30
	long cg, ncg, size, asked, i, j;
E 30
I 30
	long cg, size, asked, i, j;
D 59
	long bmapsize;
E 59
I 59
	long skipclean, bmapsize;
E 59
E 30
E 22
I 20
D 28
	struct disklabel *getdisklabel(), *lp;
E 28
I 28
	struct disklabel *lp;
I 45
	off_t sizepb;
E 45
E 28
E 20
E 10
	struct stat statb;
D 10
	daddr_t super = bflag ? bflag : SBLOCK;
D 2
	int i, j, c, d, cgd;
E 2
I 2
	int i, j;
E 2
	long size;
	BUFAREA asblk;
#	define altsblock asblk.b_un.b_fs
E 10
I 10
	struct fs proto;
E 10

I 20
	havesb = 0;
I 48
	fswritefd = -1;
I 59
	skipclean = preen;
E 59
E 48
E 20
D 34
	if (stat("/", &statb) < 0)
		errexit("Can't stat root\n");
	rootdev = statb.st_dev;
E 34
	if (stat(dev, &statb) < 0) {
I 15
D 37
		perror(dev);
E 15
D 2
		error("Can't stat %s\n", dev);
E 2
I 2
		printf("Can't stat %s\n", dev);
E 37
I 37
		printf("Can't stat %s: %s\n", dev, strerror(errno));
E 37
E 2
		return (0);
	}
D 30
	rawflg = 0;
	if ((statb.st_mode & S_IFMT) == S_IFBLK)
		;
	else if ((statb.st_mode & S_IFMT) == S_IFCHR)
		rawflg++;
	else {
		if (reply("file is not a block or character device; OK") == 0)
			return (0);
	}
E 30
I 30
D 34
	if ((statb.st_mode & S_IFMT) != S_IFBLK &&
	    (statb.st_mode & S_IFMT) != S_IFCHR &&
	    reply("file is not a block or character device; OK") == 0)
		return (0);
E 30
	if (rootdev == statb.st_rdev)
		hotroot++;
E 34
I 34
	if ((statb.st_mode & S_IFMT) != S_IFCHR) {
		pfatal("%s is not a character device", dev);
		if (reply("CONTINUE") == 0)
			return (0);
	}
E 34
D 10
	if ((dfile.rfdes = open(dev, 0)) < 0) {
E 10
I 10
D 30
	if ((dfile.rfdes = open(dev, O_RDONLY)) < 0) {
E 30
I 30
	if ((fsreadfd = open(dev, O_RDONLY)) < 0) {
E 30
I 15
D 37
		perror(dev);
E 15
E 10
D 2
		error("Can't open %s\n", dev);
E 2
I 2
		printf("Can't open %s\n", dev);
E 37
I 37
		printf("Can't open %s: %s\n", dev, strerror(errno));
E 37
E 2
		return (0);
	}
	if (preen == 0)
		printf("** %s", dev);
D 10
	if (nflag || (dfile.wfdes = open(dev, 1)) < 0) {
E 10
I 10
D 30
	if (nflag || (dfile.wfdes = open(dev, O_WRONLY)) < 0) {
E 10
		dfile.wfdes = -1;
E 30
I 30
	if (nflag || (fswritefd = open(dev, O_WRONLY)) < 0) {
		fswritefd = -1;
E 30
		if (preen)
			pfatal("NO WRITE ACCESS");
		printf(" (NO WRITE)");
	}
	if (preen == 0)
		printf("\n");
D 3
	fixcg = 0; inosumbad = 0; offsumbad = 0; frsumbad = 0; sbsumbad = 0;
E 3
D 30
	dfile.mod = 0;
E 30
I 30
	fsmodified = 0;
E 30
D 3
	n_files = n_blks = n_ffree = n_bfree = 0;
E 3
D 5
	muldup = enddup = &duplist[0];
E 5
D 6
	badlnp = &badlncnt[0];
E 6
	lfdir = 0;
D 2
	rplyflag = 0;
E 2
	initbarea(&sblk);
D 25
	initbarea(&fileblk);
	initbarea(&inoblk);
	initbarea(&cgblk);
E 25
I 23
	initbarea(&asblk);
I 25
D 28
	sblk.b_un.b_buf = (char *)malloc(SBSIZE);
	asblk.b_un.b_buf = (char *)malloc(SBSIZE);
	if (sblk.b_un.b_buf == 0 || asblk.b_un.b_buf == 0)
E 28
I 28
	sblk.b_un.b_buf = malloc(SBSIZE);
	asblk.b_un.b_buf = malloc(SBSIZE);
	if (sblk.b_un.b_buf == NULL || asblk.b_un.b_buf == NULL)
E 28
D 57
		errexit("cannot allocate space for superblock\n");
E 25
E 23
I 20
D 30
	if (lp = getdisklabel((char *)NULL, dfile.rfdes))
E 30
I 30
	if (lp = getdisklabel((char *)NULL, fsreadfd))
E 57
I 57
		errx(EEXIT, "cannot allocate space for superblock");
	if (lp = getdisklabel(NULL, fsreadfd))
E 57
E 30
		dev_bsize = secsize = lp->d_secsize;
D 23
	else {
		dev_bsize = DEV_BSIZE;
		secsize = 0;			/* guess later */
	}
E 23
I 23
	else
		dev_bsize = secsize = DEV_BSIZE;
I 39
D 46
#ifdef tahoe
E 46
	/*
D 46
	 * On the tahoe, the disk label and the disk driver disagree.
	 * The label knows that sectors are 512 bytes, but the disk
	 * drivers will only transfer in 1024 sized pieces.
	 */
	secsize = 1024;
#endif
E 39
E 23
E 20
D 10
	initbarea(&asblk);
E 10
	/*
E 46
D 10
	 * Read in the super block and its summary info.
E 10
I 10
	 * Read in the superblock, looking for alternates if necessary
E 10
	 */
D 4
	if (bread(&dfile, (char *)&sblock, super, (long)SBSIZE) == 0)
E 4
I 4
D 10
	if (bread(&dfile, (char *)&sblock, super, (long)SBSIZE) != 0)
E 4
		return (0);
	sblk.b_bno = super;
	sblk.b_size = SBSIZE;
E 10
I 10
	if (readsb(1) == 0) {
I 59
		skipclean = 0;
E 59
D 20
		if (bflag || calcsb(dev, dfile.rfdes, &proto) == 0 || preen)
E 20
I 20
D 30
		if (bflag || preen || calcsb(dev, dfile.rfdes, &proto) == 0)
E 30
I 30
		if (bflag || preen || calcsb(dev, fsreadfd, &proto) == 0)
E 30
E 20
			return(0);
		if (reply("LOOK FOR ALTERNATE SUPERBLOCKS") == 0)
			return (0);
		for (cg = 0; cg < proto.fs_ncg; cg++) {
			bflag = fsbtodb(&proto, cgsblock(&proto, cg));
			if (readsb(0) != 0)
				break;
		}
		if (cg >= proto.fs_ncg) {
			printf("%s %s\n%s %s\n%s %s\n",
				"SEARCH FOR ALTERNATE SUPER-BLOCK",
				"FAILED. YOU MUST USE THE",
				"-b OPTION TO FSCK TO SPECIFY THE",
				"LOCATION OF AN ALTERNATE",
				"SUPER-BLOCK TO SUPPLY NEEDED",
				"INFORMATION; SEE fsck(8).");
			return(0);
		}
		pwarn("USING ALTERNATE SUPERBLOCK AT %d\n", bflag);
	}
I 59
	if (skipclean && sblock.fs_clean) {
		pwarn("FILESYSTEM CLEAN; SKIPPING CHECKS\n");
		return (-1);
	}
E 59
D 30
	fmax = sblock.fs_size;
	imax = sblock.fs_ncg * sblock.fs_ipg;
E 30
I 30
	maxfsblock = sblock.fs_size;
	maxino = sblock.fs_ncg * sblock.fs_ipg;
E 30
E 10
	/*
D 10
	 * run a few consistency checks of the super block
	 */
	if (sblock.fs_magic != FS_MAGIC)
		{ badsb("MAGIC NUMBER WRONG"); return (0); }
	if (sblock.fs_ncg < 1)
		{ badsb("NCG OUT OF RANGE"); return (0); }
	if (sblock.fs_cpg < 1 || sblock.fs_cpg > MAXCPG)
		{ badsb("CPG OUT OF RANGE"); return (0); }
	if (sblock.fs_ncg * sblock.fs_cpg < sblock.fs_ncyl ||
	    (sblock.fs_ncg - 1) * sblock.fs_cpg >= sblock.fs_ncyl)
		{ badsb("NCYL DOES NOT JIVE WITH NCG*CPG"); return (0); }
	if (sblock.fs_sbsize > SBSIZE)
		{ badsb("SIZE PREPOSTEROUSLY LARGE"); return (0); }
	/*
E 10
I 9
	 * Check and potentially fix certain fields in the super block.
	 */
	if (sblock.fs_optim != FS_OPTTIME && sblock.fs_optim != FS_OPTSPACE) {
		pfatal("UNDEFINED OPTIMIZATION IN SUPERBLOCK");
		if (reply("SET TO DEFAULT") == 1) {
			sblock.fs_optim = FS_OPTTIME;
			sbdirty();
		}
	}
	if ((sblock.fs_minfree < 0 || sblock.fs_minfree > 99)) {
		pfatal("IMPOSSIBLE MINFREE=%d IN SUPERBLOCK",
			sblock.fs_minfree);
		if (reply("SET TO DEFAULT") == 1) {
			sblock.fs_minfree = 10;
			sbdirty();
		}
	}
I 11
D 38
	if (sblock.fs_interleave < 1) {
E 38
I 38
	if (sblock.fs_interleave < 1 || 
	    sblock.fs_interleave > sblock.fs_nsect) {
E 38
D 17
D 18
		pfatal("IMPOSSIBLE INTERLEAVE=%d IN SUPERBLOCK",
E 18
I 18
		pwarn("IMPOSSIBLE INTERLEAVE=%d IN SUPERBLOCK",
E 18
E 17
I 17
D 19
		pwarn("IMPOSSIBLE INTERLEAVE=%d IN SUPERBLOCK",
E 19
E 17
			sblock.fs_interleave);
D 16
		if (reply("SET TO DEFAULT") == 1) {
			sblock.fs_interleave = 1;
E 16
I 16
		sblock.fs_interleave = 1;
D 17
D 18
		if (reply("SET TO DEFAULT") == 1)
E 18
I 18
		if (preen)
			printf(" (FIXED)\n");
D 23
		if (preen || reply("SET TO DEFAULT") == 1)
E 23
I 23
		if (preen || reply("SET TO DEFAULT") == 1) {
E 23
E 18
E 17
I 17
D 19
		if (preen)
			printf(" (FIXED)\n");
		if (preen || reply("SET TO DEFAULT") == 1)
E 19
E 17
E 16
			sbdirty();
I 23
			dirty(&asblk);
		}
E 23
D 16
		}
E 16
	}
D 38
	if (sblock.fs_npsect < sblock.fs_nsect) {
E 38
I 38
	if (sblock.fs_npsect < sblock.fs_nsect || 
	    sblock.fs_npsect > sblock.fs_nsect*2) {
E 38
D 17
D 18
		pfatal("IMPOSSIBLE NPSECT=%d IN SUPERBLOCK",
E 18
I 18
		pwarn("IMPOSSIBLE NPSECT=%d IN SUPERBLOCK",
E 18
E 17
I 17
D 19
		pwarn("IMPOSSIBLE NPSECT=%d IN SUPERBLOCK",
E 19
E 17
			sblock.fs_npsect);
D 16
		if (reply("SET TO DEFAULT") == 1) {
			sblock.fs_npsect = sblock.fs_nsect;
E 16
I 16
		sblock.fs_npsect = sblock.fs_nsect;
I 17
D 19
		if (preen)
			printf(" (FIXED)\n");
		if (preen || reply("SET TO DEFAULT") == 1)
E 19
E 17
D 17
D 18
		if (reply("SET TO DEFAULT") == 1)
E 18
I 18
		if (preen)
			printf(" (FIXED)\n");
D 23
		if (preen || reply("SET TO DEFAULT") == 1)
E 23
I 23
		if (preen || reply("SET TO DEFAULT") == 1) {
E 23
E 18
E 17
E 16
			sbdirty();
I 23
			dirty(&asblk);
		}
I 45
	}
D 46
	if (sblock.fs_inodefmt < FS_44INODEFMT) {	
E 46
I 46
	if (sblock.fs_inodefmt >= FS_44INODEFMT) {
D 47
		newinofmt++;
E 47
I 47
		newinofmt = 1;
E 47
	} else {
		sblock.fs_qbmask = ~sblock.fs_bmask;
		sblock.fs_qfmask = ~sblock.fs_fmask;
I 47
		newinofmt = 0;
E 47
	}
	/*
	 * Convert to new inode format.
	 */
	if (cvtlevel >= 2 && sblock.fs_inodefmt < FS_44INODEFMT) {
		if (preen)
			pwarn("CONVERTING TO NEW INODE FORMAT\n");
		else if (!reply("CONVERT TO NEW INODE FORMAT"))
			return(0);
		doinglevel2++;
		sblock.fs_inodefmt = FS_44INODEFMT;
E 46
		sizepb = sblock.fs_bsize;
		sblock.fs_maxfilesize = sblock.fs_bsize * NDADDR - 1;
		for (i = 0; i < NIADDR; i++) {
			sizepb *= NINDIR(&sblock);
			sblock.fs_maxfilesize += sizepb;
		}
I 46
		sblock.fs_maxsymlinklen = MAXSYMLINKLEN;
E 46
		sblock.fs_qbmask = ~sblock.fs_bmask;
		sblock.fs_qfmask = ~sblock.fs_fmask;
I 46
		sbdirty();
		dirty(&asblk);
E 46
E 45
E 23
D 16
		}
E 16
	}
I 23
D 24
	if (sblock.fs_postblformat == FS_42POSTBLFMT) {
		pwarn("OLD FILE SYSTEM FORMAT\n");
		if (!preen && reply("CONVERT TO NEW FILE SYSTEM FORMAT") == 1) {
			cvtflag++;
E 24
I 24
D 46
	if (cvtflag) {
		if (sblock.fs_postblformat == FS_42POSTBLFMT) {
			/*
			 * Requested to convert from old format to new format
			 */
			if (preen)
				pwarn("CONVERTING TO NEW FILE SYSTEM FORMAT\n");
			else if (!reply("CONVERT TO NEW FILE SYSTEM FORMAT"))
				return(0);
E 24
			sblock.fs_postblformat = FS_DYNAMICPOSTBLFMT;
			sblock.fs_nrpos = 8;
			sblock.fs_postbloff =
			    (char *)(&sblock.fs_opostbl[0][0]) -
			    (char *)(&sblock.fs_link);
			sblock.fs_rotbloff = &sblock.fs_space[0] -
			    (u_char *)(&sblock.fs_link);
I 26
			sblock.fs_cgsize =
				fragroundup(&sblock, CGSIZE(&sblock));
E 26
			/*
			 * Planning now for future expansion.
			 */
D 41
#			if (BYTE_ORDER == BIG_ENDIAN)
				sblock.fs_qbmask.val[0] = 0;
				sblock.fs_qbmask.val[1] = ~sblock.fs_bmask;
				sblock.fs_qfmask.val[0] = 0;
				sblock.fs_qfmask.val[1] = ~sblock.fs_fmask;
#			endif /* BIG_ENDIAN */
#			if (BYTE_ORDER == LITTLE_ENDIAN)
				sblock.fs_qbmask.val[0] = ~sblock.fs_bmask;
				sblock.fs_qbmask.val[1] = 0;
				sblock.fs_qfmask.val[0] = ~sblock.fs_fmask;
				sblock.fs_qfmask.val[1] = 0;
#			endif /* LITTLE_ENDIAN */
E 41
I 41
#			ifdef _NOQUAD
				sblock.fs_qbmask.val[_QUAD_HIGHWORD] = 0;
				sblock.fs_qbmask.val[_QUAD_LOWWORD] =
				    ~sblock.fs_bmask;
				sblock.fs_qfmask.val[_QUAD_HIGHWORD] = 0;
				sblock.fs_qfmask.val[_QUAD_LOWWORD] =
				    ~sblock.fs_fmask;
#			else /* QUAD */
				sblock.fs_qbmask = ~sblock.fs_bmask;
				sblock.fs_qfmask = ~sblock.fs_fmask;
#			endif /* QUAD */
E 41
			sbdirty();
			dirty(&asblk);
I 24
		} else if (sblock.fs_postblformat == FS_DYNAMICPOSTBLFMT) {
			/*
			 * Requested to convert from new format to old format
			 */
			if (sblock.fs_nrpos != 8 || sblock.fs_ipg > 2048 ||
			    sblock.fs_cpg > 32 || sblock.fs_cpc > 16) {
				printf(
				"PARAMETERS OF CURRENT FILE SYSTEM DO NOT\n\t");
				errexit(
				"ALLOW CONVERSION TO OLD FILE SYSTEM FORMAT\n");
			}
			if (preen)
				pwarn("CONVERTING TO OLD FILE SYSTEM FORMAT\n");
			else if (!reply("CONVERT TO OLD FILE SYSTEM FORMAT"))
				return(0);
			sblock.fs_postblformat = FS_42POSTBLFMT;
I 26
			sblock.fs_cgsize = fragroundup(&sblock,
			    sizeof(struct ocg) + howmany(sblock.fs_fpg, NBBY));
E 26
			sbdirty();
			dirty(&asblk);
		} else {
			errexit("UNKNOWN FILE SYSTEM FORMAT\n");
E 24
		}
E 46
I 46
	/*
	 * Convert to new cylinder group format.
	 */
	if (cvtlevel >= 1 && sblock.fs_postblformat == FS_42POSTBLFMT) {
		if (preen)
			pwarn("CONVERTING TO NEW CYLINDER GROUP FORMAT\n");
		else if (!reply("CONVERT TO NEW CYLINDER GROUP FORMAT"))
			return(0);
		doinglevel1++;
		sblock.fs_postblformat = FS_DYNAMICPOSTBLFMT;
		sblock.fs_nrpos = 8;
		sblock.fs_postbloff =
		    (char *)(&sblock.fs_opostbl[0][0]) -
D 53
		    (char *)(&sblock.fs_link);
E 53
I 53
		    (char *)(&sblock.fs_firstfield);
E 53
		sblock.fs_rotbloff = &sblock.fs_space[0] -
D 53
		    (u_char *)(&sblock.fs_link);
E 53
I 53
		    (u_char *)(&sblock.fs_firstfield);
E 53
		sblock.fs_cgsize =
			fragroundup(&sblock, CGSIZE(&sblock));
		sbdirty();
		dirty(&asblk);
E 46
D 24
	} else if (cvtflag) {
		/*
		 * Requested to convert from new format to old format
		 */
		if (sblock.fs_nrpos != 8 || sblock.fs_ipg > 2048 ||
		    sblock.fs_cpg > 32) {
			printf("PARAMETERS OF CURRENT FILE SYSTEM DO NOT\n\t");
			errexit("ALLOW CONVERSION TO OLD FILE SYSTEM FORMAT\n");
		}
		pwarn("CONVERTING TO OLD FILE SYSTEM FORMAT\n");
		sblock.fs_postblformat = FS_42POSTBLFMT;
		sbdirty();
		dirty(&asblk);
E 24
	}
D 55
	if (asblk.b_dirty) {
E 55
I 55
	if (asblk.b_dirty && !bflag) {
E 55
D 30
		bcopy((char *)&sblock, (char *)&altsblock, sblock.fs_sbsize);
		flush(&dfile, &asblk);
E 30
I 30
D 58
		bcopy((char *)&sblock, (char *)&altsblock,
D 37
			(int)sblock.fs_sbsize);
E 37
I 37
			(size_t)sblock.fs_sbsize);
E 58
I 58
		memmove(&altsblock, &sblock, (size_t)sblock.fs_sbsize);
E 58
E 37
		flush(fswritefd, &asblk);
E 30
	}
E 23
E 11
	/*
E 9
D 10
	 * Set all possible fields that could differ, then do check
	 * of whole super block against an alternate super block.
	 * When an alternate super-block is specified this check is skipped.
	 */
	if (bflag)
		goto sbok;
D 4
	if (getblk(&asblk, cgsblock(&sblock, sblock.fs_ncg - 1),
	    sblock.fs_sbsize) == 0)
E 4
I 4
	getblk(&asblk, cgsblock(&sblock, sblock.fs_ncg - 1), sblock.fs_sbsize);
	if (asblk.b_errs != NULL)
E 4
		return (0);
	altsblock.fs_link = sblock.fs_link;
	altsblock.fs_rlink = sblock.fs_rlink;
	altsblock.fs_time = sblock.fs_time;
	altsblock.fs_cstotal = sblock.fs_cstotal;
	altsblock.fs_cgrotor = sblock.fs_cgrotor;
	altsblock.fs_fmod = sblock.fs_fmod;
	altsblock.fs_clean = sblock.fs_clean;
	altsblock.fs_ronly = sblock.fs_ronly;
	altsblock.fs_flags = sblock.fs_flags;
	altsblock.fs_maxcontig = sblock.fs_maxcontig;
	altsblock.fs_minfree = sblock.fs_minfree;
I 8
	altsblock.fs_optim = sblock.fs_optim;
E 8
	altsblock.fs_rotdelay = sblock.fs_rotdelay;
	altsblock.fs_maxbpg = sblock.fs_maxbpg;
	bcopy((char *)sblock.fs_csp, (char *)altsblock.fs_csp,
		sizeof sblock.fs_csp);
	bcopy((char *)sblock.fs_fsmnt, (char *)altsblock.fs_fsmnt,
		sizeof sblock.fs_fsmnt);
	if (bcmp((char *)&sblock, (char *)&altsblock, (int)sblock.fs_sbsize))
		{ badsb("TRASHED VALUES IN SUPER BLOCK"); return (0); }
sbok:
	fmax = sblock.fs_size;
	imax = sblock.fs_ncg * sblock.fs_ipg;
D 3
	n_bad = cgsblock(&sblock, 0); /* boot block plus dedicated sblock */
E 3
	/*
E 10
	 * read in the summary info.
	 */
I 22
	asked = 0;
E 22
	for (i = 0, j = 0; i < sblock.fs_cssize; i += sblock.fs_bsize, j++) {
		size = sblock.fs_cssize - i < sblock.fs_bsize ?
		    sblock.fs_cssize - i : sblock.fs_bsize;
		sblock.fs_csp[j] = (struct csum *)calloc(1, (unsigned)size);
D 30
		if (bread(&dfile, (char *)sblock.fs_csp[j],
E 30
I 30
		if (bread(fsreadfd, (char *)sblock.fs_csp[j],
E 30
		    fsbtodb(&sblock, sblock.fs_csaddr + j * sblock.fs_frag),
D 4
		    size) == 0)
E 4
I 4
D 22
		    size) != 0)
E 4
			return (0);
E 22
I 22
		    size) != 0 && !asked) {
			pfatal("BAD SUMMARY INFORMATION");
			if (reply("CONTINUE") == 0)
D 57
				errexit("");
E 57
I 57
				exit(EEXIT);
E 57
			asked++;
		}
E 22
	}
	/*
	 * allocate and initialize the necessary maps
	 */
D 30
	bmapsz = roundup(howmany(fmax, NBBY), sizeof(short));
	blockmap = calloc((unsigned)bmapsz, sizeof (char));
E 30
I 30
	bmapsize = roundup(howmany(maxfsblock, NBBY), sizeof(short));
	blockmap = calloc((unsigned)bmapsize, sizeof (char));
E 30
	if (blockmap == NULL) {
D 30
		printf("cannot alloc %d bytes for blockmap\n", bmapsz);
E 30
I 30
D 37
		printf("cannot alloc %d bytes for blockmap\n", bmapsize);
E 37
I 37
		printf("cannot alloc %u bytes for blockmap\n",
		    (unsigned)bmapsize);
E 37
E 30
D 3
		goto badsb;
	}
	freemap = calloc((unsigned)bmapsz, sizeof (char));
	if (freemap == NULL) {
		printf("cannot alloc %d bytes for freemap\n", bmapsz);
E 3
		goto badsb;
	}
D 30
	statemap = calloc((unsigned)(imax + 1), sizeof(char));
E 30
I 30
	statemap = calloc((unsigned)(maxino + 1), sizeof(char));
E 30
	if (statemap == NULL) {
D 30
		printf("cannot alloc %d bytes for statemap\n", imax + 1);
E 30
I 30
D 37
		printf("cannot alloc %d bytes for statemap\n", maxino + 1);
E 37
I 37
		printf("cannot alloc %u bytes for statemap\n",
I 46
		    (unsigned)(maxino + 1));
		goto badsb;
	}
	typemap = calloc((unsigned)(maxino + 1), sizeof(char));
	if (typemap == NULL) {
		printf("cannot alloc %u bytes for typemap\n",
E 46
		    (unsigned)(maxino + 1));
E 37
E 30
		goto badsb;
	}
D 30
	lncntp = (short *)calloc((unsigned)(imax + 1), sizeof(short));
E 30
I 30
	lncntp = (short *)calloc((unsigned)(maxino + 1), sizeof(short));
E 30
	if (lncntp == NULL) {
D 37
		printf("cannot alloc %d bytes for lncntp\n", 
D 30
		    (imax + 1) * sizeof(short));
E 30
I 30
		    (maxino + 1) * sizeof(short));
E 37
I 37
		printf("cannot alloc %u bytes for lncntp\n", 
		    (unsigned)(maxino + 1) * sizeof(short));
E 37
E 30
		goto badsb;
D 2
	}
	for (c = 0; c < sblock.fs_ncg; c++) {
		cgd = cgdmin(&sblock, c);
		if (c == 0) {
			d = cgbase(&sblock, c);
			cgd += howmany(sblock.fs_cssize, sblock.fs_fsize);
		} else
			d = cgsblock(&sblock, c);
		for (; d < cgd; d++)
			setbmap(d);
E 2
	}
D 32

E 32
I 32
	numdirs = sblock.fs_cstotal.cs_ndir;
I 33
	inplast = 0;
E 33
	listmax = numdirs + 10;
	inpsort = (struct inoinfo **)calloc((unsigned)listmax,
	    sizeof(struct inoinfo *));
	inphead = (struct inoinfo **)calloc((unsigned)numdirs,
	    sizeof(struct inoinfo *));
	if (inpsort == NULL || inphead == NULL) {
D 37
		printf("cannot alloc %d bytes for inphead\n", 
		    numdirs * sizeof(struct inoinfo *));
E 37
I 37
		printf("cannot alloc %u bytes for inphead\n", 
		    (unsigned)numdirs * sizeof(struct inoinfo *));
E 37
		goto badsb;
	}
E 32
I 25
	bufinit();
E 25
	return (1);

badsb:
D 59
	ckfini();
E 59
I 59
	ckfini(0);
E 59
	return (0);
I 10
}

/*
 * Read in the super block and its summary info.
 */
I 57
static int
E 57
readsb(listerr)
	int listerr;
{
D 23
	BUFAREA asblk;
I 18
D 20
	struct disklabel *getdisklabel(), *lp;
E 20
E 18
#	define altsblock asblk.b_un.b_fs
E 23
D 14
	daddr_t super = bflag ? bflag : SBLOCK;
E 14
I 14
D 20
	daddr_t super = bflag ? bflag * DEV_BSIZE : SBOFF;
E 20
I 20
D 30
	off_t sboff;
E 30
D 56
	daddr_t super = bflag ? bflag : SBOFF / dev_bsize;
E 56
I 56
	ufs_daddr_t super = bflag ? bflag : SBOFF / dev_bsize;
E 56
E 20
E 14

D 23
	initbarea(&asblk);
E 23
I 13
D 14
	dev_bsize = DEV_BSIZE;
E 14
I 14
D 20
	dev_bsize = 1;
E 20
E 14
E 13
D 30
	if (bread(&dfile, (char *)&sblock, super, (long)SBSIZE) != 0)
E 30
I 30
	if (bread(fsreadfd, (char *)&sblock, super, (long)SBSIZE) != 0)
E 30
		return (0);
	sblk.b_bno = super;
	sblk.b_size = SBSIZE;
	/*
	 * run a few consistency checks of the super block
	 */
	if (sblock.fs_magic != FS_MAGIC)
		{ badsb(listerr, "MAGIC NUMBER WRONG"); return (0); }
	if (sblock.fs_ncg < 1)
		{ badsb(listerr, "NCG OUT OF RANGE"); return (0); }
D 23
	if (sblock.fs_cpg < 1 || sblock.fs_cpg > MAXCPG)
E 23
I 23
	if (sblock.fs_cpg < 1)
E 23
		{ badsb(listerr, "CPG OUT OF RANGE"); return (0); }
	if (sblock.fs_ncg * sblock.fs_cpg < sblock.fs_ncyl ||
	    (sblock.fs_ncg - 1) * sblock.fs_cpg >= sblock.fs_ncyl)
		{ badsb(listerr, "NCYL LESS THAN NCG*CPG"); return (0); }
	if (sblock.fs_sbsize > SBSIZE)
		{ badsb(listerr, "SIZE PREPOSTEROUSLY LARGE"); return (0); }
	/*
I 20
	 * Compute block size that the filesystem is based on,
	 * according to fsbtodb, and adjust superblock block number
	 * so we can tell if this is an alternate later.
	 */
D 23
	if (sblock.fs_dbsize && secsize == 0)
		secsize = sblock.fs_dbsize;
E 23
	super *= dev_bsize;
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
	sblk.b_bno = super / dev_bsize;
I 42
	if (bflag) {
		havesb = 1;
		return (1);
	}
E 42
	/*
E 20
	 * Set all possible fields that could differ, then do check
	 * of whole super block against an alternate super block.
	 * When an alternate super-block is specified this check is skipped.
	 */
I 23
	getblk(&asblk, cgsblock(&sblock, sblock.fs_ncg - 1), sblock.fs_sbsize);
D 28
	if (asblk.b_errs != NULL)
E 28
I 28
	if (asblk.b_errs)
E 28
		return (0);
I 55
	altsblock.fs_firstfield = sblock.fs_firstfield;
	altsblock.fs_unused_1 = sblock.fs_unused_1;
E 55
E 23
I 13
D 20
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
I 18
	if (lp = getdisklabel((char *)NULL, dfile.rfdes))
		secsize = lp->d_secsize;
	else
		secsize = dev_bsize;
E 18
D 14
	sblk.b_bno = sblk.b_bno * DEV_BSIZE / dev_bsize;
E 14
I 14
	sblk.b_bno = sblk.b_bno / dev_bsize;
E 14
E 13
	if (bflag)
E 20
I 20
D 42
	if (bflag) {
		havesb = 1;
E 20
		return (1);
I 20
	}
E 42
E 20
D 23
	getblk(&asblk, cgsblock(&sblock, sblock.fs_ncg - 1), sblock.fs_sbsize);
	if (asblk.b_errs != NULL)
		return (0);
I 15
	altsblock.fs_fsbtodb = sblock.fs_fsbtodb;
I 20
	altsblock.fs_dbsize = sblock.fs_dbsize;
E 23
E 20
E 15
D 53
	altsblock.fs_link = sblock.fs_link;
	altsblock.fs_rlink = sblock.fs_rlink;
E 53
	altsblock.fs_time = sblock.fs_time;
	altsblock.fs_cstotal = sblock.fs_cstotal;
	altsblock.fs_cgrotor = sblock.fs_cgrotor;
	altsblock.fs_fmod = sblock.fs_fmod;
	altsblock.fs_clean = sblock.fs_clean;
	altsblock.fs_ronly = sblock.fs_ronly;
	altsblock.fs_flags = sblock.fs_flags;
	altsblock.fs_maxcontig = sblock.fs_maxcontig;
	altsblock.fs_minfree = sblock.fs_minfree;
	altsblock.fs_optim = sblock.fs_optim;
	altsblock.fs_rotdelay = sblock.fs_rotdelay;
	altsblock.fs_maxbpg = sblock.fs_maxbpg;
I 12
D 23
	altsblock.fs_npsect = sblock.fs_npsect;
	altsblock.fs_interleave = sblock.fs_interleave;
E 23
E 12
D 58
	bcopy((char *)sblock.fs_csp, (char *)altsblock.fs_csp,
		sizeof sblock.fs_csp);
E 58
I 58
	memmove(altsblock.fs_csp, sblock.fs_csp, sizeof sblock.fs_csp);
E 58
I 54
	altsblock.fs_maxcluster = sblock.fs_maxcluster;
E 54
D 58
	bcopy((char *)sblock.fs_fsmnt, (char *)altsblock.fs_fsmnt,
		sizeof sblock.fs_fsmnt);
D 15
	if (bcmp((char *)&sblock, (char *)&altsblock, (int)sblock.fs_sbsize))
		{ badsb(listerr, "TRASHED VALUES IN SUPER BLOCK"); return (0); }
E 15
I 15
	bcopy((char *)sblock.fs_sparecon, (char *)altsblock.fs_sparecon,
		sizeof sblock.fs_sparecon);
E 58
I 58
	memmove(altsblock.fs_fsmnt, sblock.fs_fsmnt, sizeof sblock.fs_fsmnt);
	memmove(altsblock.fs_sparecon,
		sblock.fs_sparecon, sizeof sblock.fs_sparecon);
E 58
I 23
	/*
	 * The following should not have to be copied.
	 */
	altsblock.fs_fsbtodb = sblock.fs_fsbtodb;
	altsblock.fs_interleave = sblock.fs_interleave;
	altsblock.fs_npsect = sblock.fs_npsect;
	altsblock.fs_nrpos = sblock.fs_nrpos;
I 52
	altsblock.fs_state = sblock.fs_state;
E 52
I 44
	altsblock.fs_qbmask = sblock.fs_qbmask;
	altsblock.fs_qfmask = sblock.fs_qfmask;
	altsblock.fs_state = sblock.fs_state;
	altsblock.fs_maxfilesize = sblock.fs_maxfilesize;
E 44
E 23
D 58
	if (bcmp((char *)&sblock, (char *)&altsblock, (int)sblock.fs_sbsize)) {
E 58
I 58
	if (memcmp(&sblock, &altsblock, (int)sblock.fs_sbsize)) {
E 58
I 54
		if (debug) {
			long *nlp, *olp, *endlp;

			printf("superblock mismatches\n");
			nlp = (long *)&altsblock;
			olp = (long *)&sblock;
			endlp = olp + (sblock.fs_sbsize / sizeof *olp);
			for ( ; olp < endlp; olp++, nlp++) {
				if (*olp == *nlp)
					continue;
				printf("offset %d, original %d, alternate %d\n",
				    olp - (long *)&sblock, *olp, *nlp);
			}
		}
E 54
		badsb(listerr,
		"VALUES IN SUPER BLOCK DISAGREE WITH THOSE IN FIRST ALTERNATE");
		return (0);
	}
I 20
	havesb = 1;
E 20
E 15
	return (1);
E 10
D 23
#	undef altsblock
E 23
}

I 57
static void
E 57
D 10
badsb(s)
E 10
I 10
badsb(listerr, s)
	int listerr;
E 10
	char *s;
{

I 10
	if (!listerr)
		return;
E 10
	if (preen)
D 49
		printf("%s: ", devname);
E 49
I 49
		printf("%s: ", cdevname);
E 49
D 10
	printf("BAD SUPER BLOCK: %s\n", s);
	pwarn("USE -b OPTION TO FSCK TO SPECIFY LOCATION OF AN ALTERNATE\n");
	pfatal("SUPER-BLOCK TO SUPPLY NEEDED INFORMATION; SEE fsck(8).\n");
E 10
I 10
	pfatal("BAD SUPER BLOCK: %s\n", s);
E 10
}
I 10

/*
 * Calculate a prototype superblock based on information in the disk label.
 * When done the cgsblock macro can be calculated and the fs_ncg field
 * can be used. Do NOT attempt to use other macros without verifying that
 * their needed information is available!
 */
I 57
static int
E 57
calcsb(dev, devfd, fs)
	char *dev;
	int devfd;
	register struct fs *fs;
{
	register struct disklabel *lp;
	register struct partition *pp;
	register char *cp;
D 18
	struct disklabel *getdisklabel();
E 18
	int i;
I 21
D 28
	struct disklabel *getdisklabel();
E 28
E 21

D 58
	cp = index(dev, '\0') - 1;
E 58
I 58
	cp = strchr(dev, '\0') - 1;
E 58
D 57
	if (cp == (char *)-1 || (*cp < 'a' || *cp > 'h') && !isdigit(*cp)) {
E 57
I 57
	if (cp == (char *)-1 || ((*cp < 'a' || *cp > 'h') && !isdigit(*cp))) {
E 57
		pfatal("%s: CANNOT FIGURE OUT FILE SYSTEM PARTITION\n", dev);
		return (0);
	}
	lp = getdisklabel(dev, devfd);
	if (isdigit(*cp))
		pp = &lp->d_partitions[0];
	else
		pp = &lp->d_partitions[*cp - 'a'];
	if (pp->p_fstype != FS_BSDFFS) {
D 20
		pfatal("%s: NOT FORMATTED AS A BSD FILE SYSTEM (%s)\n",
E 20
I 20
		pfatal("%s: NOT LABELED AS A BSD FILE SYSTEM (%s)\n",
E 20
			dev, pp->p_fstype < FSMAXTYPES ?
			fstypenames[pp->p_fstype] : "unknown");
		return (0);
	}
D 30
	bzero(fs, sizeof(struct fs));
E 30
I 30
D 58
	bzero((char *)fs, sizeof(struct fs));
E 58
I 58
	memset(fs, 0, sizeof(struct fs));
E 58
E 30
	fs->fs_fsize = pp->p_fsize;
	fs->fs_frag = pp->p_frag;
	fs->fs_cpg = pp->p_cpg;
	fs->fs_size = pp->p_size;
	fs->fs_ntrak = lp->d_ntracks;
	fs->fs_nsect = lp->d_nsectors;
	fs->fs_spc = lp->d_secpercyl;
	fs->fs_nspf = fs->fs_fsize / lp->d_secsize;
	fs->fs_sblkno = roundup(
		howmany(lp->d_bbsize + lp->d_sbsize, fs->fs_fsize),
		fs->fs_frag);
	fs->fs_cgmask = 0xffffffff;
	for (i = fs->fs_ntrak; i > 1; i >>= 1)
		fs->fs_cgmask <<= 1;
	if (!POWEROF2(fs->fs_ntrak))
		fs->fs_cgmask <<= 1;
	fs->fs_cgoffset = roundup(
		howmany(fs->fs_nsect, NSPF(fs)), fs->fs_frag);
	fs->fs_fpg = (fs->fs_cpg * fs->fs_spc) / NSPF(fs);
	fs->fs_ncg = howmany(fs->fs_size / fs->fs_spc, fs->fs_cpg);
	for (fs->fs_fsbtodb = 0, i = NSPF(fs); i > 1; i >>= 1)
		fs->fs_fsbtodb++;
I 20
	dev_bsize = lp->d_secsize;
E 20
	return (1);
}

D 15
#ifdef byioctl
E 15
D 57
struct disklabel *
E 57
I 57
static struct disklabel *
E 57
getdisklabel(s, fd)
	char *s;
	int	fd;
{
	static struct disklabel lab;

	if (ioctl(fd, DIOCGDINFO, (char *)&lab) < 0) {
I 18
		if (s == NULL)
			return ((struct disklabel *)NULL);
E 18
I 15
D 37
		pwarn("");
E 15
		perror("ioctl (GDINFO)");
E 37
I 37
		pwarn("ioctl (GCINFO): %s\n", strerror(errno));
E 37
D 15
		fatal("%s: can't read disk label", s);
E 15
I 15
D 36
		errexit("%s: can't read disk label", s);
E 36
I 36
D 57
		errexit("%s: can't read disk label\n", s);
E 57
I 57
		errx(EEXIT, "%s: can't read disk label", s);
E 57
E 36
E 15
	}
	return (&lab);
}
D 15
#else byioctl
char specname[64];
char boot[BBSIZE];

struct disklabel *
getdisklabel(s, fd)
	char *s;
	int	fd;
{
	char *cp;
	u_long magic = htonl(DISKMAGIC);
	register struct disklabel *lp;
	int cfd;

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
	}

	if (read(cfd, boot, BBSIZE) < BBSIZE) {
		perror(specname);
		exit(2);
	}
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
		printf("Bad pack magic number %s\n",
			"(label is damaged, or pack is unlabeled)");
		exit(1);
	}
#if ENDIAN != BIG
	swablabel(lp);
#endif
	return (lp);
}
#endif byioctl
E 15
E 10
E 1
