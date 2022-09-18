h53515
s 00020/00016/00571
d D 8.5 95/05/24 19:43:46 margo 19 18
c Add support for fragments in lfs; check for segment 
c summary magic numbers.
e
s 00003/00003/00584
d D 8.4 95/05/04 16:27:51 mckusick 18 17
c di_?time is no longer a structure
e
s 00012/00011/00575
d D 8.3 95/04/28 10:19:56 bostic 17 16
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00585
d D 8.2 94/11/30 11:02:09 mckusick 16 15
c lint
e
s 00005/00005/00581
d D 8.1 93/06/05 10:54:42 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00583
d D 5.14 92/12/18 07:40:00 margo 14 13
c Use di_inumber, not di_inum.
e
s 00012/00008/00574
d D 5.13 92/08/25 15:03:36 bostic 13 12
c Initialize ifile address correctly, add available space accounting 
c fields.
e
s 00006/00004/00576
d D 5.12 92/07/23 16:30:54 bostic 12 11
c Print out additional fields in segment usage table.
e
s 00035/00029/00545
d D 5.11 92/07/21 10:48:37 bostic 11 10
c Get rid of free to unalloced structure; minor formatting cleanup.
e
s 00003/00002/00571
d D 5.10 92/07/19 16:49:36 bostic 10 9
c add maxfilesize to superblock
e
s 00011/00000/00562
d D 5.9 92/07/15 09:55:41 bostic 9 8
c display additional (in-memory) information
e
s 00005/00005/00557
d D 5.8 92/07/06 15:02:00 bostic 8 7
c time's are quads
e
s 00022/00007/00540
d D 5.7 92/02/11 10:27:24 staelin 7 6
c print more than one partial segment per segment; print out inode
c numbers for inodes in a partial segment
e
s 00007/00009/00540
d D 5.6 91/12/31 15:17:49 bostic 6 5
c delete if_st_atime, minor fixes
e
s 00010/00003/00539
d D 5.5 91/12/14 17:00:48 bostic 5 4
c display cleaner info
e
s 00001/00000/00541
d D 5.4 91/12/06 17:52:37 bostic 4 3
c <sys/mount.h> needs <sys/ucred.h>
e
s 00110/00053/00431
d D 5.3 91/12/06 16:48:50 bostic 3 2
c LFS version 2
e
s 00091/00049/00393
d D 5.2 91/12/06 16:46:48 bostic 2 1
c checkpoint
e
s 00442/00000/00000
d D 5.1 91/09/19 10:16:30 bostic 1 0
c date and time created 91/09/19 10:16:30 by bostic
e
u
U
t
T
I 1
/*-
D 15
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 15
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 4
#include <sys/ucred.h>
E 4
#include <sys/mount.h>
D 8
#include <sys/file.h>
E 8
I 8
#include <sys/time.h>
E 8
D 3
#include <ufs/dinode.h>
#include "lfs.h"				/* XXX fix this */
E 3
I 3

#include <ufs/ufs/dinode.h>
#include <ufs/lfs/lfs.h>

I 17
#include <err.h>
#include <errno.h>
E 17
E 3
D 8
#include <time.h>
E 8
I 8
#include <fcntl.h>
E 8
#include <fstab.h>
D 17
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
E 17
#include <stdio.h>
I 17
#include <stdlib.h>
E 17
#include <string.h>
I 17
#include <unistd.h>
E 17
#include "extern.h"

I 2
static void	addseg __P((char *));
I 3
static void	dump_cleaner_info __P((struct lfs *, void *));
E 3
E 2
static void	dump_dinode __P((struct dinode *));
D 2
static void	dump_ifile __P((int, LFS_SUPER *, int));
E 2
I 2
D 3
static void	dump_ifile __P((int, LFS *, int));
E 3
I 3
static void	dump_ifile __P((int, struct lfs *, int));
E 3
E 2
static int	dump_ipage_ifile __P((int, IFILE *, int));
D 2
static int	dump_ipage_segusage __P((LFS_SUPER *, int, IFILE *, int));
static daddr_t	dump_segment __P((int, daddr_t, LFS_SUPER *, int));
static int	dump_sum __P((SEGSUM *));
static void	dump_super __P((LFS_SUPER *));
E 2
I 2
D 3
static int	dump_ipage_segusage __P((LFS *, int, IFILE *, int));
static daddr_t	dump_segment __P((int, int, daddr_t, LFS *, int));
static int	dump_sum __P((SEGSUM *, int, daddr_t));
static void	dump_super __P((LFS *));
E 3
I 3
static int	dump_ipage_segusage __P((struct lfs *, int, IFILE *, int));
static void	dump_segment __P((int, int, daddr_t, struct lfs *, int));
D 7
static int	dump_sum __P((struct lfs *, SEGSUM *, int, daddr_t));
E 7
I 7
static int	dump_sum __P((int, struct lfs *, SEGSUM *, int, daddr_t));
E 7
static void	dump_super __P((struct lfs *));
E 3
E 2
static void	usage __P((void));

D 2
static int daddr_shift;
E 2
I 2
typedef struct seglist SEGLIST;
struct seglist {
        SEGLIST *next;
	int num;
};
SEGLIST	*seglist;

int daddr_shift;
E 2
char *special;

/* Segment Usage formats */
#define print_suheader \
D 12
	(void)printf("segnum\tstatus\tnbytes\t\tlastmod\n")
E 12
I 12
	(void)printf("segnum\tflags\tnbytes\tninos\tnsums\tlastmod\n")
E 12
I 5

E 5
#define print_suentry(i, sp) \
D 5
	(void)printf("%d\t%s\t%d\t%s", \
	    i, (((sp)->su_flags) ? "DIRTY" : "CLEAN"), \
E 5
I 5
D 12
	(void)printf("%d\t%c%c%c\t%d\t%s", i, \
E 12
I 12
	(void)printf("%d\t%c%c%c\t%d\t%d\t%d\t%s", i, \
E 12
	    (((sp)->su_flags & SEGUSE_ACTIVE) ? 'A' : ' '), \
	    (((sp)->su_flags & SEGUSE_DIRTY) ? 'D' : 'C'), \
	    (((sp)->su_flags & SEGUSE_SUPERBLOCK) ? 'S' : ' '), \
E 5
D 12
	    (sp)->su_nbytes, ctime((time_t *)&(sp)->su_lastmod))
E 12
I 12
	    (sp)->su_nbytes, (sp)->su_ninos, (sp)->su_nsums, \
	    ctime((time_t *)&(sp)->su_lastmod))
E 12

/* Ifile formats */
#define print_iheader \
D 6
	(void)printf("inum\tstatus\tversion\tdaddr\t\tatime\tfreeptr\n")
E 6
I 6
	(void)printf("inum\tstatus\tversion\tdaddr\t\tfreeptr\n")
E 6
#define print_ientry(i, ip) \
	if (ip->if_daddr == LFS_UNUSED_DADDR) \
D 6
		(void)printf("%d\tFREE\t%d\t \t\t \t%d\n", \
E 6
I 6
		(void)printf("%d\tFREE\t%d\t \t\t%d\n", \
E 6
		    i, ip->if_version, ip->if_nextfree); \
	else \
D 6
		(void)printf("%d\tINUSE\t%d\t%8X    \t%s\n", \
		    i, ip->if_version, ip->if_daddr, \
		    ctime((time_t *)&ip->if_st_atime))
E 6
I 6
		(void)printf("%d\tINUSE\t%d\t%8X    \n", \
		    i, ip->if_version, ip->if_daddr)
E 6
int
D 3
main (argc, argv)
E 3
I 3
main(argc, argv)
E 3
	int argc;
	char *argv[];
{
D 2
	LFS_SUPER lfs_sb1, lfs_sb2, *lfs_master;
	daddr_t seg_addr, next_seg;
	int ch, do_allsb, do_ientries, fd;
E 2
I 2
D 3
	LFS lfs_sb1, lfs_sb2, *lfs_master;
E 3
I 3
	struct lfs lfs_sb1, lfs_sb2, *lfs_master;
E 3
	daddr_t seg_addr;
	int ch, do_allsb, do_ientries, fd, segnum;
E 2

	do_allsb = 0;
	do_ientries = 0;
D 2
	while ((ch = getopt(argc, argv, "is")) != EOF)
E 2
I 2
D 17
	while ((ch = getopt(argc, argv, "ais:")) != EOF)
E 17
I 17
	while ((ch = getopt(argc, argv, "ais:")) != -1)
E 17
E 2
		switch(ch) {
I 2
		case 'a':		/* Dump all superblocks */
			do_allsb = 1;
			break;
E 2
		case 'i':		/* Dump ifile entries */
			do_ientries = 1;
			break;
D 2
		case 's':		/* Dump all superblocks */
			do_allsb = 1;
E 2
I 2
		case 's':		/* Dump out these segments */
			addseg(optarg);
E 2
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	special = argv[0];
	if ((fd = open(special, O_RDONLY, 0)) < 0)
D 17
		err("%s: %s", special, strerror(errno));
E 17
I 17
		err(1, "%s", special);
E 17

	/* Read the first superblock */
D 2
	get(fd, LFS_LABELPAD, &lfs_sb1, sizeof(LFS_SUPER));
E 2
I 2
D 3
	get(fd, LFS_LABELPAD, &lfs_sb1, sizeof(LFS));
E 3
I 3
	get(fd, LFS_LABELPAD, &lfs_sb1, sizeof(struct lfs));
E 3
E 2
	daddr_shift = lfs_sb1.lfs_bshift - lfs_sb1.lfs_fsbtodb;

	/*
	 * Read the second superblock and figure out which check point is
	 * most up to date.
	 */
D 2
	get(fd,
	    lfs_sb1.lfs_sboffs[1] << daddr_shift, &lfs_sb2, sizeof(LFS_SUPER));
	
E 2
I 2
D 3
	get(fd, lfs_sb1.lfs_sboffs[1] << daddr_shift, &lfs_sb2, sizeof(LFS));
E 3
I 3
	get(fd,
	    lfs_sb1.lfs_sboffs[1] << daddr_shift, &lfs_sb2, sizeof(struct lfs));
E 3

E 2
	lfs_master = &lfs_sb1;
	if (lfs_sb1.lfs_tstamp < lfs_sb2.lfs_tstamp)
		lfs_master = &lfs_sb2;

	(void)printf("Master Superblock:\n");
	dump_super(lfs_master);

	dump_ifile(fd, lfs_master, do_ientries);

D 2
	next_seg = LFS_UNUSED_DADDR;
	for (seg_addr = lfs_master->lfs_lastseg; 
	     seg_addr != LFS_UNUSED_DADDR && 
		next_seg != lfs_master->lfs_lastseg; 
	     seg_addr = next_seg)
		next_seg = dump_segment(fd, seg_addr, lfs_master, do_allsb);
	
E 2
I 2
	if (seglist != NULL)
		for (; seglist != NULL; seglist = seglist->next) {
			seg_addr = lfs_master->lfs_sboffs[0] + seglist->num *
			    (lfs_master->lfs_ssize << lfs_master->lfs_fsbtodb);
			dump_segment(fd,
			    seglist->num, seg_addr, lfs_master, do_allsb);
		}
	else
		for (segnum = 0, seg_addr = lfs_master->lfs_sboffs[0];
		    segnum < lfs_master->lfs_nseg; segnum++, seg_addr +=
		    lfs_master->lfs_ssize << lfs_master->lfs_fsbtodb)
			dump_segment(fd,
			    segnum, seg_addr, lfs_master, do_allsb);

E 2
	(void)close(fd);
	exit(0);
}

/*
 * We are reading all the blocks of an inode and dumping out the ifile table.
D 3
 * This code can be made tigher, but this is a first pass at getting the stuff
E 3
I 3
 * This code could be tighter, but this is a first pass at getting the stuff
E 3
 * printed out rather than making this code incredibly efficient.
 */
static void
dump_ifile(fd, lfsp, do_ientries)
	int fd;
D 2
	LFS_SUPER *lfsp;
E 2
I 2
D 3
	LFS *lfsp;
E 3
I 3
	struct lfs *lfsp;
E 3
E 2
	int do_ientries;
{
	IFILE *ipage;
	struct dinode *dip, *dpage;
D 3
	daddr_t addr, *addrp, *iaddrp;
	daddr_t	*dindir;
	daddr_t	*indir;
	int block_limit, nblocks;
	int i, j, inum, nsupb, psize;
E 3
I 3
	daddr_t addr, *addrp, *dindir, *iaddrp, *indir;
	int block_limit, i, inum, j, nblocks, nsupb, psize;
E 3

	psize = lfsp->lfs_bsize;
	addr = lfsp->lfs_idaddr;
D 2
	nsupb = lfsp->lfs_bsize / sizeof(SEGUSAGE);
E 2
I 2
D 3
	nsupb = lfsp->lfs_bsize / sizeof(SEGUSE);
E 3
E 2

D 13
	if (!(dip = dpage = malloc(psize)))
E 13
I 13
	if (!(dpage = malloc(psize)))
E 13
D 17
		err("%s", strerror(errno));
E 17
I 17
		err(1, NULL);
E 17
D 13
	get(fd, addr << daddr_shift, dip, psize);
E 13
I 13
	get(fd, addr << daddr_shift, dpage, psize);
E 13

D 13
	for (i = 0; i < lfsp->lfs_inopb; i++, dip++)
E 13
I 13
	for (dip = dpage + INOPB(lfsp) - 1; dip >= dpage; --dip)
E 13
D 14
		if (dip->di_inum == LFS_IFILE_INUM)
E 14
I 14
		if (dip->di_inumber == LFS_IFILE_INUM)
E 14
			break;

D 13
	if (i >= lfsp->lfs_inopb)
E 13
I 13
	if (dip < dpage)
E 13
D 17
		err("unable to locate ifile inode");
E 17
I 17
		errx(1, "unable to locate ifile inode");
E 17

	(void)printf("\nIFILE inode\n");
	dump_dinode(dip);
D 2
	
E 2
I 2

E 2
	(void)printf("\nIFILE contents\n");
D 6
	print_suheader;
E 6
	nblocks = dip->di_size >> lfsp->lfs_bshift;
	block_limit = MIN(nblocks, NDADDR);

	/* Get the direct block */
	if ((ipage = malloc(psize)) == NULL)
D 17
		err("%s", strerror(errno));
E 17
I 17
		err(1, NULL);
E 17
	for (inum = 0, addrp = dip->di_db, i = 0; i < block_limit;
	    i++, addrp++) {
		get(fd, *addrp << daddr_shift, ipage, psize);
I 3
		if (i < lfsp->lfs_cleansz) {
			dump_cleaner_info(lfsp, ipage);
I 6
			print_suheader;
E 6
			continue;
D 6
		} else 
			i -= lfsp->lfs_cleansz;
E 6
I 6
		} 
E 6
E 3

D 6
		if (i < lfsp->lfs_segtabsz) {
E 6
I 6
		if (i < (lfsp->lfs_segtabsz + lfsp->lfs_cleansz)) {
E 6
D 3
			inum = dump_ipage_segusage(lfsp, inum, ipage, nsupb);
E 3
I 3
			inum = dump_ipage_segusage(lfsp, inum, ipage, 
			    lfsp->lfs_sepb);
E 3
			if (!inum)
				if(!do_ientries)
D 3
					goto e0;
E 3
I 3
D 11
					goto e1;
E 11
I 11
					goto e0;
E 11
E 3
				else
					print_iheader;
		} else
			inum = dump_ipage_ifile(inum, ipage, lfsp->lfs_ifpb);
I 3

E 3
	}

	if (nblocks <= NDADDR)
		goto e0;

	/* Dump out blocks off of single indirect block */
	if (!(indir = malloc(psize)))
D 17
		err("%s", strerror(errno));
E 17
I 17
		err(1, NULL);
E 17
	get(fd, dip->di_ib[0] << daddr_shift, indir, psize);
	block_limit = MIN(i + lfsp->lfs_nindir, nblocks);
	for (addrp = indir; i < block_limit; i++, addrp++) {
		if (*addrp == LFS_UNUSED_DADDR)
			break;
		get(fd, *addrp << daddr_shift,ipage, psize);
I 3
		if (i < lfsp->lfs_cleansz) {
			dump_cleaner_info(lfsp, ipage);
			continue;
		} else 
			i -= lfsp->lfs_cleansz;

E 3
		if (i < lfsp->lfs_segtabsz) {
D 3
			inum = dump_ipage_segusage(lfsp, inum, ipage, nsupb);
E 3
I 3
			inum = dump_ipage_segusage(lfsp, inum, ipage, 
			    lfsp->lfs_sepb);
E 3
			if (!inum)
				if(!do_ientries)
					goto e1;
				else
					print_iheader;
		} else
			inum = dump_ipage_ifile(inum, ipage, lfsp->lfs_ifpb);
	}

	if (nblocks <= lfsp->lfs_nindir * lfsp->lfs_ifpb)
		goto e1;
D 2
	
E 2
I 2

E 2
	/* Get the double indirect block */
	if (!(dindir = malloc(psize)))
D 17
		err("%s", strerror(errno));
E 17
I 17
		err(1, NULL);
E 17
	get(fd, dip->di_ib[1] << daddr_shift, dindir, psize);
	for (iaddrp = dindir, j = 0; j < lfsp->lfs_nindir; j++, iaddrp++) {
		if (*iaddrp == LFS_UNUSED_DADDR)
			break;
		get(fd, *iaddrp << daddr_shift, indir, psize);
		block_limit = MIN(i + lfsp->lfs_nindir, nblocks);
		for (addrp = indir; i < block_limit; i++, addrp++) {
			if (*addrp == LFS_UNUSED_DADDR)
				break;
			get(fd, *addrp << daddr_shift, ipage, psize);
I 3
			if (i < lfsp->lfs_cleansz) {
				dump_cleaner_info(lfsp, ipage);
				continue;
			} else 
				i -= lfsp->lfs_cleansz;

E 3
			if (i < lfsp->lfs_segtabsz) {
				inum = dump_ipage_segusage(lfsp,
D 3
				    inum, ipage, nsupb);
E 3
I 3
				    inum, ipage, lfsp->lfs_sepb);
E 3
				if (!inum)
					if(!do_ientries)
						goto e2;
					else
						print_iheader;
			} else
				inum = dump_ipage_ifile(inum,
				    ipage, lfsp->lfs_ifpb);
		}
	}
e2:	free(dindir);
e1:	free(indir);
e0:	free(dpage);
	free(ipage);
}

static int
dump_ipage_ifile(i, pp, tot)
	int i;
	IFILE *pp;
	int tot;
{
	IFILE *ip;
	int cnt, max;

	max = i + tot;

	for (ip = pp, cnt = i; cnt < max; cnt++, ip++)
		print_ientry(cnt, ip);
	return (max);
}

static int
dump_ipage_segusage(lfsp, i, pp, tot)
D 2
	LFS_SUPER *lfsp;
E 2
I 2
D 3
	LFS *lfsp;
E 3
I 3
	struct lfs *lfsp;
E 3
E 2
	int i;
	IFILE *pp;
	int tot;
{
D 2
	SEGUSAGE *sp;
E 2
I 2
	SEGUSE *sp;
E 2
	int cnt, max;

	max = i + tot;
D 2
	for (sp = (SEGUSAGE *)pp, cnt = i; 
E 2
I 2
	for (sp = (SEGUSE *)pp, cnt = i;
E 2
	     cnt < lfsp->lfs_nseg && cnt < max; cnt++, sp++)
		print_suentry(cnt, sp);
	if (max >= lfsp->lfs_nseg)
		return (0);
	else
		return (max);
}

static void
dump_dinode(dip)
	struct dinode *dip;
{
	int i;

	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\t%s%d\n",
		"mode  ", dip->di_mode,
		"nlink ", dip->di_nlink,
		"uid   ", dip->di_uid,
		"gid   ", dip->di_gid,
		"size  ", dip->di_size);
	(void)printf("%s%s%s%s%s%s",
D 8
		"atime ", ctime(&dip->di_atime),
		"mtime ", ctime(&dip->di_mtime),
		"ctime ", ctime(&dip->di_ctime));
E 8
I 8
D 18
		"atime ", ctime(&dip->di_atime.ts_sec),
		"mtime ", ctime(&dip->di_mtime.ts_sec),
		"ctime ", ctime(&dip->di_ctime.ts_sec));
E 18
I 18
		"atime ", ctime(&dip->di_atime),
		"mtime ", ctime(&dip->di_mtime),
		"ctime ", ctime(&dip->di_ctime));
E 18
E 8
D 14
	(void)printf("inum  %d\n", dip->di_inum);
E 14
I 14
	(void)printf("inum  %d\n", dip->di_inumber);
E 14
	(void)printf("Direct Addresses\n");
	for (i = 0; i < NDADDR; i++) {
D 11
		(void)printf("\t%X", dip->di_db[i]);
E 11
I 11
		(void)printf("\t0x%X", dip->di_db[i]);
E 11
		if ((i % 6) == 5)
			(void)printf("\n");
	}
	for (i = 0; i < NIADDR; i++)
D 11
		(void)printf("\t%X", dip->di_ib[i]);
E 11
I 11
		(void)printf("\t0x%X", dip->di_ib[i]);
E 11
	(void)printf("\n");
}

static int
D 2
dump_sum(sp)
E 2
I 2
D 3
dump_sum(sp, segnum, addr)
E 3
I 3
D 7
dump_sum(lfsp, sp, segnum, addr)
E 7
I 7
dump_sum(fd, lfsp, sp, segnum, addr)
E 7
	struct lfs *lfsp;
E 3
E 2
	SEGSUM *sp;
I 2
D 7
	int segnum;
E 7
I 7
	int fd, segnum;
E 7
	daddr_t addr;
E 2
{
	FINFO *fp;
D 2
	u_long *dp;
E 2
I 2
D 16
	long *dp;
E 16
I 16
	daddr_t *dp;
E 16
E 2
D 3
	int i, j, sb;
E 3
I 3
	int i, j;
E 3
I 2
	int ck;
I 3
D 19
	int numblocks;
E 19
I 19
	int numbytes;
E 19
I 7
	struct dinode *inop;
E 7
E 3
E 2

I 2
D 3
	if (sp->ss_cksum != (ck = cksum(&sp->ss_next, 
	    LFS_SUMMARY_SIZE - sizeof(sp->ss_cksum))))
E 3
I 3
D 19
	if (sp->ss_sumsum != (ck = cksum(&sp->ss_datasum, 
E 19
I 19
	if (sp->ss_magic != SS_MAGIC ||
	    sp->ss_sumsum != (ck = cksum(&sp->ss_datasum, 
E 19
D 11
	    LFS_SUMMARY_SIZE - sizeof(sp->ss_sumsum))))
E 3
		(void)printf("dumplfs: %s %d address %lx\n",
E 11
I 11
	    LFS_SUMMARY_SIZE - sizeof(sp->ss_sumsum)))) {
		(void)printf("dumplfs: %s %d address 0x%lx\n",
E 11
		    "corrupt summary block; segment", segnum, addr);
I 11
		return(0);
	}
E 11

E 2
D 11
	(void)printf("Segment Summary Info\n");
D 3
	(void)printf("\t%s%X   \t%s%X   \t%s%X   \n",
E 3
I 3
	(void)printf("\t%s%X\t%s%d\t%s%d\t%s%X\t%s%X\n",
E 11
I 11
D 19
	(void)printf("Segment Summary Info at 0x%lx\n", addr);
E 19
I 19
	(void)printf("Segment Summary Info at 0x%lx\tmagic no: 0x%x\n",
	    addr, sp->ss_magic);
E 19
	(void)printf("    %s0x%X\t%s%d\t%s%d\n    %s0x%X\t%s0x%X",
E 11
E 3
		"next     ", sp->ss_next,
D 3
		"prev     ", sp->ss_prev,
		"nextsum  ", sp->ss_nextsum );
	(void)printf("\t%s%d\t%s%d\t%s%X\n",
E 3
		"nfinfo   ", sp->ss_nfinfo,
		"ninos    ", sp->ss_ninos,
D 3
		"cksum    ", sp->ss_cksum );
E 3
I 3
		"sumsum   ", sp->ss_sumsum,
		"datasum  ", sp->ss_datasum );
E 3
	(void)printf("\tcreate   %s", ctime((time_t *)&sp->ss_create));

D 3
	sb = 0;
E 3
I 3
D 19
	numblocks = (sp->ss_ninos + INOPB(lfsp) - 1) / INOPB(lfsp);

E 19
	/* Dump out inode disk addresses */
	dp = (daddr_t *)sp;
	dp += LFS_SUMMARY_SIZE / sizeof(daddr_t);
I 7
	inop = malloc(1 << lfsp->lfs_bshift);
E 7
D 11
	printf("\tInode addresses:");
E 11
I 11
	printf("    Inode addresses:");
I 19
	numbytes = 0;
E 19
E 11
D 7
	for (dp--, i = 0; i < numblocks; i += INOPB(lfsp))
		printf("\t%X", *dp--);
E 7
I 7
	for (dp--, i = 0; i < sp->ss_ninos; dp--) {
I 19
		numbytes += lfsp->lfs_bsize;	/* add bytes for inode block */
E 19
D 11
		printf("\t%X {", *dp);
E 11
I 11
		printf("\t0x%X {", *dp);
E 11
		get(fd, *dp << (lfsp->lfs_bshift - lfsp->lfs_fsbtodb), inop, 
		    (1 << lfsp->lfs_bshift));
		for (j = 0; i < sp->ss_ninos && j < INOPB(lfsp); j++, i++) {
			if (j > 0) 
				(void)printf(", ");
D 14
			(void)printf("%d", inop[j].di_inum);
E 14
I 14
			(void)printf("%d", inop[j].di_inumber);
E 14
		}
		(void)printf("}");
		if (((i/INOPB(lfsp)) % 4) == 3)
			(void)printf("\n");
	}
	free(inop);
E 7

	printf("\n");
E 3
	for (fp = (FINFO *)(sp + 1), i = 0; i < sp->ss_nfinfo; i++) {
D 3
		if (fp->fi_ino == LFS_UNUSED_INUM)
			sb = 1;
E 3
I 3
D 19
		numblocks += fp->fi_nblocks;
E 3
D 11
		(void)printf("File Info for file: %d version %d nblocks %d\n",
E 11
I 11
		(void)printf("    FINFO for inode: %d version %d nblocks %d\n",
E 11
		    fp->fi_ino, fp->fi_version, fp->fi_nblocks);
E 19
I 19
		(void)printf("    FINFO for inode: %d version %d nblocks %d lastlength %d\n",
		    fp->fi_ino, fp->fi_version, fp->fi_nblocks, fp->fi_lastlength);
E 19
		dp = &(fp->fi_blocks[0]);
		for (j = 0; j < fp->fi_nblocks; j++, dp++) {
			(void)printf("\t%d", *dp);
			if ((j % 8) == 7)
				(void)printf("\n");
I 19
			if (j == fp->fi_nblocks - 1)
				numbytes += fp->fi_lastlength;
			else
				numbytes += lfsp->lfs_bsize;
E 19
		}
		if ((j % 8) != 0)
			(void)printf("\n");
		fp = (FINFO *)dp;
	}
D 2
	return(sb);
E 2
I 2
D 3
	return (sb);
E 3
I 3
D 19
	return (numblocks);
E 19
I 19
	return (numbytes);
E 19
E 3
E 2
}

D 3
static daddr_t
E 3
I 3
static void
E 3
D 2
dump_segment(fd, addr, lfsp, dump_sb)
	int fd;
E 2
I 2
dump_segment(fd, segnum, addr, lfsp, dump_sb)
	int fd, segnum;
E 2
	daddr_t addr;
D 2
	LFS_SUPER *lfsp;
E 2
I 2
D 3
	LFS *lfsp;
E 3
I 3
	struct lfs *lfsp;
E 3
E 2
	int dump_sb;
{
D 2
	LFS_SUPER lfs_sb;
E 2
I 2
D 3
	LFS lfs_sb;
E 3
I 3
	struct lfs lfs_sb, *sbp;
E 3
E 2
	SEGSUM *sump;
	char sumblock[LFS_SUMMARY_SIZE];
D 3
	int sum_offset;
	int sb;
E 3
I 3
D 19
	int did_one, nblocks, sb;
E 19
I 19
	int did_one, nbytes, sb;
E 19
	off_t sum_offset, super_off;
E 3

D 2
	(void)printf("\nSegment Number %d (Disk Address %X)\n", 
E 2
I 2
D 11
	(void)printf("\nSegment Number %d (Disk Address %X)\n",
E 11
I 11
	(void)printf("\nSEGMENT %d (Disk Address 0x%X)\n",
E 11
E 2
	    addr >> (lfsp->lfs_segshift - daddr_shift), addr);
D 3
	sum_offset = (addr << (lfsp->lfs_bshift - lfsp->lfs_fsbtodb)) +
	    (lfsp->lfs_ssize << lfsp->lfs_bshift) - LFS_SUMMARY_SIZE;
E 3
I 3
	sum_offset = (addr << (lfsp->lfs_bshift - lfsp->lfs_fsbtodb));
E 3
D 2
	
E 2
I 2

E 2
	sb = 0;
I 3
	did_one = 0;
E 3
	do {
		get(fd, sum_offset, sumblock, LFS_SUMMARY_SIZE);
		sump = (SEGSUM *)sumblock;
D 2
		sb = sb || dump_sum(sump);
		sum_offset = (sump->ss_nextsum == -1 ? 0 :  
E 2
I 2
D 3
		sb = sb || dump_sum(sump, segnum, addr);
		sum_offset = (sump->ss_nextsum == -1 ? 0 :
E 2
		    sump->ss_nextsum << daddr_shift);
E 3
I 3
		if (sump->ss_sumsum != cksum (&sump->ss_datasum, 
			LFS_SUMMARY_SIZE - sizeof(sump->ss_sumsum))) {
			sbp = (struct lfs *)sump;
			if (sb = (sbp->lfs_magic == LFS_MAGIC)) {
				super_off = sum_offset;
				sum_offset += LFS_SBPAD;
			} else if (did_one)
				break;
			else {
D 11
				printf("Segment at %X corrupt\n", addr);
E 11
I 11
				printf("Segment at 0x%X corrupt\n", addr);
E 11
				break;
			}
		} else {
D 7
			nblocks = dump_sum(lfsp, sump, segnum, addr);
E 7
I 7
D 11
			nblocks = dump_sum(fd, lfsp, sump, segnum, addr);
E 11
I 11
D 19
			nblocks = dump_sum(fd, lfsp, sump, segnum, sum_offset >>
E 19
I 19
			nbytes = dump_sum(fd, lfsp, sump, segnum, sum_offset >>
E 19
			     (lfsp->lfs_bshift - lfsp->lfs_fsbtodb));
E 11
E 7
D 19
			if (nblocks)
D 7
				sum_offset += (nblocks << lfsp->lfs_bshift);
E 7
I 7
				sum_offset += LFS_SUMMARY_SIZE + 
					(nblocks << lfsp->lfs_bshift);
E 19
I 19
			if (nbytes)
				sum_offset += LFS_SUMMARY_SIZE + nbytes;
E 19
E 7
			else
				sum_offset = 0;
			did_one = 1;
		}
E 3
	} while (sum_offset);
I 3

E 3
	if (dump_sb && sb)  {
D 2
		get(fd, addr << daddr_shift, &lfs_sb, sizeof(LFS_SUPER));
E 2
I 2
D 3
		get(fd, addr << daddr_shift, &lfs_sb, sizeof(LFS));
E 3
I 3
		get(fd, super_off, &lfs_sb, sizeof(struct lfs));
E 3
E 2
		dump_super(&lfs_sb);
	}
D 3
	return (sump->ss_prev);
E 3
I 3
	return;
E 3
}

D 2
static void 
E 2
I 2
static void
E 2
dump_super(lfsp)
D 2
	LFS_SUPER *lfsp;
E 2
I 2
D 3
	LFS *lfsp;
E 3
I 3
	struct lfs *lfsp;
E 3
E 2
{
	int i;

D 11
	(void)printf("%s%X\t%s%X\t%s%d\t%s%d\n",
E 11
I 11
	(void)printf("%s0x%X\t%s0x%X\t%s%d\t%s%d\n",
E 11
		"magic    ", lfsp->lfs_magic,
		"version  ", lfsp->lfs_version,
		"size     ", lfsp->lfs_size,
		"ssize    ", lfsp->lfs_ssize);
D 11
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
E 11
I 11
	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
E 11
		"dsize    ", lfsp->lfs_dsize,
		"bsize    ", lfsp->lfs_bsize,
		"fsize    ", lfsp->lfs_fsize,
		"frag     ", lfsp->lfs_frag);

D 11
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
E 11
I 11
	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
E 11
		"minfree  ", lfsp->lfs_minfree,
		"inopb    ", lfsp->lfs_inopb,
		"ifpb     ", lfsp->lfs_ifpb,
		"nindir   ", lfsp->lfs_nindir);

D 3
	(void)printf("%s%d\t%s%d\t%s%d\n",
E 3
I 3
D 11
	(void)printf("%s%d\t%s%d\t%s%d\t%s%d\n",
E 11
I 11
	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
E 11
E 3
		"nseg     ", lfsp->lfs_nseg,
		"nspf     ", lfsp->lfs_nspf,
I 3
		"cleansz  ", lfsp->lfs_cleansz,
E 3
		"segtabsz ", lfsp->lfs_segtabsz);

D 11
	(void)printf("%s%X\t%s%d\t%s%X\t%s%d\n",
E 11
I 11
D 19
	(void)printf("%s0x%X\t%s%d\t%s0x%X\t%s%d\n",
E 19
I 19
	(void)printf("%s0x%X\t%s%d\t%s0x%qX\t%s%d\n",
E 19
E 11
		"segmask  ", lfsp->lfs_segmask,
		"segshift ", lfsp->lfs_segshift,
		"bmask    ", lfsp->lfs_bmask,
		"bshift   ", lfsp->lfs_bshift);

D 11
	(void)printf("%s%X\t%s%d\t%s%X\t%s%d\n",
E 11
I 11
D 19
	(void)printf("%s0x%X\t\t%s%d\t%s0x%X\t%s%d\n",
E 19
I 19
	(void)printf("%s0x%qX\t\t%s%d\t%s0x%qX\t%s%d\n",
E 19
E 11
		"ffmask   ", lfsp->lfs_ffmask,
		"ffshift  ", lfsp->lfs_ffshift,
		"fbmask   ", lfsp->lfs_fbmask,
		"fbshift  ", lfsp->lfs_fbshift);

D 2
	(void)printf("%s%d\t%s%X\n", 
E 2
I 2
D 10
	(void)printf("%s%d\t%s%X\n",
E 10
I 10
D 11
	(void)printf("%s%d\t%s%X\t%qd\n",
E 11
I 11
D 12
	(void)printf("%s%d\t\t%s0x%X\t%s0x%qx\n",
E 12
I 12
	(void)printf("%s%d\t%s%d\t%s0x%X\t%s0x%qx\n",
		"sushift  ", lfsp->lfs_sushift,
E 12
E 11
E 10
E 2
		"fsbtodb  ", lfsp->lfs_fsbtodb,
D 10
		"cksum    ", lfsp->lfs_cksum);
E 10
I 10
		"cksum    ", lfsp->lfs_cksum,
		"maxfilesize  ", lfsp->lfs_maxfilesize);
E 10

D 11
	(void)printf("Superblock disk addresses:");
	for (i = 0; i < LFS_MAXNUMSB; i++)
		(void)printf(" %X", lfsp->lfs_sboffs[i]);
E 11
I 11
	(void)printf("Superblock disk addresses:\t");
	for (i = 0; i < LFS_MAXNUMSB; i++) {
		(void)printf(" 0x%X", lfsp->lfs_sboffs[i]);
		if ( i == (LFS_MAXNUMSB >> 1))
			(void)printf("\n\t\t\t\t");
	}
E 11
	(void)printf("\n");

	(void)printf("Checkpoint Info\n");
D 2
	(void)printf("%s%d\t%s%X\t%s%d\t%s%d\n",
E 2
I 2
D 11
	(void)printf("%s%d\t%s%X\t%s%d\n",
E 11
I 11
	(void)printf("%s%d\t%s0x%X\t%s%d\n",
E 11
E 2
		"free     ", lfsp->lfs_free,
		"idaddr   ", lfsp->lfs_idaddr,
D 2
		"ifile    ", lfsp->lfs_ifile,
		"lastseg  ", lfsp->lfs_lastseg);
E 2
I 2
		"ifile    ", lfsp->lfs_ifile);
D 3
	(void)printf("%s%X\t%s%d\t%s%X\t%s%X\n",
E 3
I 3
D 11
	(void)printf("%s%X\t%s%d\t%s%X\t%s%X\t%s%X\t%s%X\n",
E 11
I 11
D 13
	(void)printf("%s0x%X\t%s%d\t%s0x%X\t%s0x%X\n%s0x%X\t%s0x%X\t",
E 13
I 13
	(void)printf("%s%d\t%s%d\t%s%d\n",
E 13
E 11
E 3
		"bfree    ", lfsp->lfs_bfree,
I 13
		"avail    ", lfsp->lfs_avail,
		"uinodes  ", lfsp->lfs_uinodes);
	(void)printf("%s%d\t%s0x%X\t%s0x%X\n%s0x%X\t%s0x%X\t",
E 13
		"nfiles   ", lfsp->lfs_nfiles,
		"lastseg  ", lfsp->lfs_lastseg,
D 3
		"nextseg  ", lfsp->lfs_nextseg);
E 3
I 3
		"nextseg  ", lfsp->lfs_nextseg,
		"curseg   ", lfsp->lfs_curseg,
		"offset   ", lfsp->lfs_offset);
E 3
E 2
	(void)printf("tstamp   %s", ctime((time_t *)&lfsp->lfs_tstamp));
I 9
D 11
	(void)printf("In-Memory Information\n");
	(void)printf("%s%d\t%s%X\t%s%d\t%s%d\t%s%d\n",
E 11
I 11
	(void)printf("\nIn-Memory Information\n");
D 13
	(void)printf("%s%d\t%s0x%X\t%s%d\t%s%d\t%s%d\n",
E 13
I 13
	(void)printf("%s%d\t%s0x%X\t%s%d%s%d\t%s%d\n",
E 13
E 11
		"seglock  ", lfsp->lfs_seglock,
		"iocount  ", lfsp->lfs_iocount,
		"writer   ", lfsp->lfs_writer,
		"dirops   ", lfsp->lfs_dirops,
D 13
		"doifile  ", lfsp->lfs_doifile );
D 11
	(void)printf("%s%d\t%s%X\t%s%d\n",
E 11
I 11
	(void)printf("%s%d\t%s0x%X\t%s%d\n",
E 13
I 13
		"doifile  ", lfsp->lfs_doifile);
	(void)printf("%s%d\t%s%d\t%s0x%X\t%s%d\n",
		"nactive  ", lfsp->lfs_nactive,
E 13
E 11
		"fmod     ", lfsp->lfs_fmod,
		"clean    ", lfsp->lfs_clean,
		"ronly    ", lfsp->lfs_ronly);
E 9
}

static void
I 2
addseg(arg)
	char *arg;
{
	SEGLIST *p;

	if ((p = malloc(sizeof(SEGLIST))) == NULL)
D 17
		err("%s", strerror(errno));
E 17
I 17
		err(1, NULL);
E 17
	p->next = seglist;
	p->num = atoi(arg);
	seglist = p;
I 3
}

static void
dump_cleaner_info(lfsp, ipage)
	struct lfs *lfsp;
	void *ipage;
{
D 5
	return;
E 5
I 5
	CLEANERINFO *cip;

	cip = (CLEANERINFO *)ipage;
D 11
	(void)printf("Cleaner Info\nclean\t%d\tdirty\t%d\n",
E 11
I 11
	(void)printf("segments clean\t%d\tsegments dirty\t%d\n\n",
E 11
	    cip->clean, cip->dirty);
E 5
E 3
}

static void
E 2
usage()
{
D 2
	(void)fprintf(stderr, "usage: dumplfs [-is] file\n");
E 2
I 2
	(void)fprintf(stderr, "usage: dumplfs [-ai] [-s segnum] file\n");
E 2
	exit(1);
}
E 1
