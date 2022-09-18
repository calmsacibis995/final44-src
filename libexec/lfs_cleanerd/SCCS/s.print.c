h26338
s 00017/00007/00185
d D 8.2 95/05/24 19:42:05 margo 4 3
c Check summary magic numbers and print them out.
e
s 00002/00002/00190
d D 8.1 93/06/04 18:55:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00186
d D 5.2 92/08/21 12:01:09 bostic 2 1
c Change markv calling convention to take a single array containing
c both blocks and inodes.
e
s 00188/00000/00000
d D 5.1 92/08/06 12:33:33 bostic 1 0
c date and time created 92/08/06 12:33:33 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/mount.h>
#include <sys/time.h>

#include <ufs/ufs/dinode.h>
#include <ufs/lfs/lfs.h>

#include <stdlib.h>
#include <stdio.h>
#include "clean.h"

/*
 * Print out a summary block; return number of blocks in segment; 0
 * for empty segment or corrupt segment.
 * Returns a pointer to the array of inode addresses.
 */
int
dump_summary(lfsp, sp, flags, iaddrp)
	struct lfs *lfsp;
	SEGSUM *sp;
	u_long flags;
	daddr_t **iaddrp;
{
	int i, j, numblocks;
	daddr_t *dp;

	FINFO *fp;
	int ck;

I 4
	if (sp->ss_magic != SS_MAGIC)
		return(-1);

E 4
	if (sp->ss_sumsum != (ck = cksum(&sp->ss_datasum, 
	    LFS_SUMMARY_SIZE - sizeof(sp->ss_sumsum))))
		return(-1);

I 4
	numblocks = (sp->ss_ninos + INOPB(lfsp) - 1) / INOPB(lfsp);

	/* Do some basic sanity checking. */
	if (sp->ss_nfinfo > LFS_SUMMARY_SIZE / sizeof(FINFO) ||
	    numblocks > lfsp->lfs_ssize ||
	    numblocks > LFS_SUMMARY_SIZE / sizeof(daddr_t))
		return(-1);

E 4
	if (flags & DUMP_SUM_HEADER) {
D 4
		(void)printf("    %s0x%X\t%s%d\t%s%d\n    %s0x%X\t%s0x%X",
E 4
I 4
		(void)printf("  %s0x%X\t%s%d\t%s%d\n  %s0x%X\t%s0x%X\t%s0x%X\n",
E 4
			"next     ", sp->ss_next,
			"nfinfo   ", sp->ss_nfinfo,
			"ninos    ", sp->ss_ninos,
			"sumsum   ", sp->ss_sumsum,
D 4
			"datasum  ", sp->ss_datasum );
		(void)printf("\tcreate   %s", ctime((time_t *)&sp->ss_create));
E 4
I 4
			"datasum  ", sp->ss_datasum,
			"magic    ", sp->ss_magic);
		(void)printf("  create   %s", ctime((time_t *)&sp->ss_create));
E 4
	}

D 4
	numblocks = (sp->ss_ninos + INOPB(lfsp) - 1) / INOPB(lfsp);

E 4
	/* Dump out inode disk addresses */
	if (flags & DUMP_INODE_ADDRS)
		printf("    Inode addresses:");

	dp = (daddr_t *)((caddr_t)sp + LFS_SUMMARY_SIZE);
	for (--dp, i = 0; i < sp->ss_ninos; --dp)
		if (flags & DUMP_INODE_ADDRS) {
			(void)printf("\t0x%lx", *dp);
			if (++i % 7 == 0)
				(void)printf("\n");
		} else
			++i;
	if (iaddrp)
		*iaddrp = ++dp;
	if (flags & DUMP_INODE_ADDRS)
		printf("\n");

	for (fp = (FINFO *)(sp + 1), i = 0; i < sp->ss_nfinfo; ++i) {
		numblocks += fp->fi_nblocks;
		if (flags & DUMP_FINFOS) {
			(void)printf("    %s%d version %d nblocks %d\n",
			    "FINFO for inode: ", fp->fi_ino,
			    fp->fi_version, fp->fi_nblocks);
			dp = &(fp->fi_blocks[0]);
			for (j = 0; j < fp->fi_nblocks; j++, dp++) {
				(void)printf("\t%d", *dp);
				if ((j % 8) == 7)
					(void)printf("\n");
			}
			if ((j % 8) != 0)
				(void)printf("\n");
			fp = (FINFO *)dp;
		} else {
			fp = (FINFO *)(&fp->fi_blocks[fp->fi_nblocks]);
		}
	}
	return (numblocks);
}

#ifdef VERBOSE
void
dump_cleaner_info(ipage)
	void *ipage;
{
	CLEANERINFO *cip;

	cip = (CLEANERINFO *)ipage;
	(void)printf("segments clean\t%d\tsegments dirty\t%d\n\n",
	    cip->clean, cip->dirty);
}

void
dump_super(lfsp)
	struct lfs *lfsp;
{
	int i;

	(void)printf("%s0x%X\t%s0x%X\t%s%d\t%s%d\n",
		"magic    ", lfsp->lfs_magic,
		"version  ", lfsp->lfs_version,
		"size     ", lfsp->lfs_size,
		"ssize    ", lfsp->lfs_ssize);
	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
		"dsize    ", lfsp->lfs_dsize,
		"bsize    ", lfsp->lfs_bsize,
		"fsize    ", lfsp->lfs_fsize,
		"frag     ", lfsp->lfs_frag);

	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
		"minfree  ", lfsp->lfs_minfree,
		"inopb    ", lfsp->lfs_inopb,
		"ifpb     ", lfsp->lfs_ifpb,
		"nindir   ", lfsp->lfs_nindir);

	(void)printf("%s%d\t\t%s%d\t%s%d\t%s%d\n",
		"nseg     ", lfsp->lfs_nseg,
		"nspf     ", lfsp->lfs_nspf,
		"cleansz  ", lfsp->lfs_cleansz,
		"segtabsz ", lfsp->lfs_segtabsz);

D 4
	(void)printf("%s0x%X\t%s%d\t%s0x%X\t%s%d\n",
E 4
I 4
	(void)printf("%s0x%X\t%s%d\t%s0x%qX\t%s%d\n",
E 4
		"segmask  ", lfsp->lfs_segmask,
		"segshift ", lfsp->lfs_segshift,
		"bmask    ", lfsp->lfs_bmask,
		"bshift   ", lfsp->lfs_bshift);

D 4
	(void)printf("%s0x%X\t\t%s%d\t%s0x%X\t%s%d\n",
E 4
I 4
	(void)printf("%s0x%qX\t\t%s%d\t%s0x%qX\t%s%d\n",
E 4
		"ffmask   ", lfsp->lfs_ffmask,
		"ffshift  ", lfsp->lfs_ffshift,
		"fbmask   ", lfsp->lfs_fbmask,
		"fbshift  ", lfsp->lfs_fbshift);

	(void)printf("%s%d\t\t%s0x%X\t%s0x%qx\n",
		"fsbtodb  ", lfsp->lfs_fsbtodb,
		"cksum    ", lfsp->lfs_cksum,
		"maxfilesize  ", lfsp->lfs_maxfilesize);

	(void)printf("Superblock disk addresses:\t");
	for (i = 0; i < LFS_MAXNUMSB; i++) {
		(void)printf(" 0x%X", lfsp->lfs_sboffs[i]);
		if ( i == (LFS_MAXNUMSB >> 1))
			(void)printf("\n\t\t\t\t");
	}
	(void)printf("\n");

	(void)printf("Checkpoint Info\n");
	(void)printf("%s%d\t%s0x%X\t%s%d\n",
		"free     ", lfsp->lfs_free,
		"idaddr   ", lfsp->lfs_idaddr,
		"ifile    ", lfsp->lfs_ifile);
D 2
	(void)printf("%s0x%X\t%s%d\t%s0x%X\t%s0x%X\n%s0x%X\t%s0x%X\t",
E 2
I 2
	(void)printf("%s%d\t%s%d\t%s%d\n",
E 2
		"bfree    ", lfsp->lfs_bfree,
I 2
		"avail    ", lfsp->lfs_avail,
		"uinodes  ", lfsp->lfs_uinodes);
	(void)printf("%s%d\t%s0x%X\t%s0x%X\n%s0x%X\t%s0x%X\t",
E 2
		"nfiles   ", lfsp->lfs_nfiles,
		"lastseg  ", lfsp->lfs_lastseg,
		"nextseg  ", lfsp->lfs_nextseg,
		"curseg   ", lfsp->lfs_curseg,
		"offset   ", lfsp->lfs_offset);
	(void)printf("tstamp   %s", ctime((time_t *)&lfsp->lfs_tstamp));
	(void)printf("\nIn-Memory Information\n");
	(void)printf("%s%d\t%s0x%X\t%s%d\t%s%d\t%s%d\n",
		"seglock  ", lfsp->lfs_seglock,
		"iocount  ", lfsp->lfs_iocount,
		"writer   ", lfsp->lfs_writer,
		"dirops   ", lfsp->lfs_dirops,
		"doifile  ", lfsp->lfs_doifile );
D 2
	(void)printf("%s%d\t%s0x%X\t%s%d\n",
E 2
I 2
	(void)printf("%s%d\t%s%d\t%s0x%X\t%s%d\n",
		"nactive  ", lfsp->lfs_nactive,
E 2
		"fmod     ", lfsp->lfs_fmod,
		"clean    ", lfsp->lfs_clean,
		"ronly    ", lfsp->lfs_ronly);
}
#endif /* VERBOSE */
E 1
