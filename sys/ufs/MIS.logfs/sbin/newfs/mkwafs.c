#ifdef CLFS
/*
 * CLFS
 * $Log: mkwafs.c,v $
 * Revision 1.8  1994/12/20  21:04:03  margo
 * Add inchkpt field (in checkpoint).
 *
 * Revision 1.7  1994/11/29  16:35:01  margo
 * Remove extraneous debugging messages
 *
 * Revision 1.6  1994/10/04  19:42:16  margo
 * Incorporate merged BSD/AIX wafs code.  Still has compiler error.
 *
 * Revision 1.1  1994/09/21  18:33:49  jat
 * Initial working version for WAFS.
 *
 */
#endif

/*
 * Copyright (c) 1994 The President and Fellows of Harvard University.
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
static char *rcsid = "$Id";

#ifdef AIX
#include <sys/cdefs.h>
#include <sys/bsd_param.h>
#else
#include <sys/param.h>
#endif
#include <sys/disklabel.h>
#include <sys/time.h>
#include <sys/mount.h>

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

static struct wafs wafs_default =  {
	/* *wafs_link */	NULL,
	/* *wafs_rlink */	NULL,
	/* wafs_magic */	WAFS_MAGIC,
	/* wafs_version */	WAFS_DEF_VERSION,
	/* wafs_sblkno */	WAFS_DEF_SBLKNO,
	/* wafs_interval */	WAFS_DEF_INTERVAL,
	/* wafs_int_shift */	WAFS_DEF_INT_SHIFT,
	/* wafs_time */		0,
	/* wafs_rtime */	0,
	/* wafs_size */		0,
	/* wafs_dsize */	0,
	/* wafs_bsize */	WAFS_DEF_BSIZE,
	/* wafs_minfree */	0,
	/* wafs_maxthreads */	WAFS_DEF_MAX_THREADS,
	/* wafs_bmask */	WAFS_DEF_BMASK,
	/* wafs_bshift */	WAFS_DEF_BSHIFT,
	/* wafs_fsbtodb */	WAFS_DEF_FSBTODB,
	/* wafs_sbsize */	WAFS_SBSIZE,
	/* wafs_sbshift */	0,
	/* wafs_bfree */	0,
	/* wafs_tinfopb */	WAFS_DEF_BSIZE / sizeof(struct tinfo),
	/* wafs_lsn */		0,
	/* wafs_check */	0,
	/* wafs_head */		0,
	/* wafs_tail */		0,
	/* wafs_state */	1,
	/* wafs_inchkpt */	0,
	/* wafs_fmod */		0,
	/* wafs_clean */	1,
	/* wafs_ronly */	0,
	/* wafs_flags */	0,
	/* wafs_fsmnt[MAXMNTLEN] */	{ 0 },
	/* wafs_pad */		{ 0 },
	/* wafs_id */		0,
	/* wafs_cksum */	0
};


int
mkwafs(fd, lp, partp, minfree, block_size, num_threads, id)
	int fd;
	struct disklabel *lp;
	struct partition *partp;
	int minfree;
	int block_size;
	int num_threads;
	long id;
{
	struct wafs *wafsp;	/* Superblock */
	struct wafs_header *rechdrp;	/* Log record header */
	wafs_page_header_t *page_headerp;	/* Header on a wafs data page */
	daddr_t	sb_addr;	/* Address of superblocks */
	char *page;		/* Temporary buffer */
	int bsize;		/* Block size */
	int threads;		/* Number of log threads */
	int db_per_fb;		/* Disk blocks per file block */
	int off;		/* Offset at which to write */
	int num_sbblocks;	/* Number of sbblocks in the file system */

#ifdef DIAGNOSTIC
	printf("Making WAFS filesystem on %s\n", special);
#endif
	wafsp = &wafs_default;

	if (!(bsize = block_size))
		bsize = WAFS_DEF_BSIZE;
	if (!(threads = num_threads))
		threads = WAFS_DEF_MAX_THREADS;

	/* Modify parts of superblock overridden by command line arguments */
	if (bsize != WAFS_DEF_BSIZE) {
		wafsp->wafs_bshift = log2(bsize);
		if (1 << wafsp->wafs_bshift != bsize)
			fatal("%d: block size not a power of 2", bsize);
		wafsp->wafs_bsize = bsize;
		wafsp->wafs_bmask = bsize - 1;
		wafsp->wafs_tinfopb = bsize / sizeof(struct tinfo);
	}

	if (minfree)
		wafsp->wafs_minfree = minfree;
	wafsp->wafs_maxthreads = threads;
	wafsp->wafs_id = id;

	/*
	 * Fill in parts of superblock that can be computed from file system
	 * size, disk geometry and current time.
	 */
	db_per_fb = bsize/lp->d_secsize;
	wafsp->wafs_fsbtodb = log2(db_per_fb);
	wafsp->wafs_size = partp->p_size >> wafsp->wafs_fsbtodb;

	/*
	 * To set the number of data blocks in the file system, we have
	 * subtract off the LABEL, the superblocks, and any thread-id
	 * blocks.
	 */
	wafsp->wafs_dsize =
	    wafsp->wafs_size - (SBOFF >> wafsp->wafs_bshift);

	/*
	 * Figure out how many superblocks are in the whole file system.
	 * We want to compute the ceiling of the number of blocks divided
	 * by the size of the interval expressed in blocks.  SBSHIFT is
	 * used to convert from superblocks to file system blocks.  The
	 * computation is the ceiling of the number of superblocks in
	 * the entire file system divided by the size of the interval.
	 */
	wafsp->wafs_sbshift = log2(WAFS_SBSIZE >> wafsp->wafs_bshift);
	num_sbblocks = 1 + ((wafsp->wafs_dsize >> wafsp->wafs_sbshift)  - 1
	    >> wafsp->wafs_int_shift);
	/* Subtract enough file system blocks to account for the superblocks */
	wafsp->wafs_dsize -= (num_sbblocks << wafsp->wafs_sbshift);

	/* Now substract blocks to hold thread info */
/* Not Yet Supported
	wafsp->wafs_dsize -=
	    max_threads + wafsp->wafs_tinfopb - 1 / wafsp->wafs_tinfopb;
*/
	wafsp->wafs_bfree = wafsp->wafs_dsize;

	if ((wafsp->wafs_time = time(NULL)) == -1)
		fatal("time: %s", strerror(errno));
	wafsp->wafs_rtime = wafsp->wafs_time;

	/*
	 * Figure out where the superblocks are going to live.
	 * sb_addr is expressed in disk blocks.
	 */
	for (sb_addr = SBLOCK;
	    num_sbblocks--;
	    sb_addr += SB_INTERVAL_DB(wafsp)) {

		off = sb_addr * lp->d_secsize;

		/* Calculate checksum */
		wafsp->wafs_cksum = cksum(wafsp,
		    sizeof(struct wafs) - sizeof(wafsp->wafs_cksum));

		printf("0x%x(byte 0x%x) ", sb_addr, off);
		if (num_sbblocks % 6 == 0)
			printf("\n");
		put(fd, off, wafsp, WAFS_SBSIZE);
	}
#ifdef DIAGNOSTIC
	printf("head: %lx tail: %lx\n", wafsp->wafs_head,
	    wafsp->wafs_tail);
#endif

	/*
	 * Now write first page of the log.  We identify the log end by
	 * a log record with record type NO_RECORD and length 0 so that
	 * zero'd pages look like the end of log.
	 */
	sb_addr = SBLOCK + (1 << wafsp->wafs_sbshift + wafsp->wafs_fsbtodb);
	off = sb_addr * lp->d_secsize;

	/* Now create a blank page that we can initialize. */
	if ((page = (char *)malloc(wafsp->wafs_bsize)) == NULL) {
		perror("new_wafs:");
		return(1);
	}

#ifdef DIAGNOSTIC
	printf("Writing Page and record header\n");
#endif
	page_headerp = (wafs_page_header_t *)page;
	page_headerp->tv_usec = wafsp->wafs_time;
	page_headerp->tv_sec = 0;
	rechdrp = (struct wafs_header *)
	    (page + sizeof(wafs_page_header_t));
	rechdrp->length = 0;
	rechdrp->rectype = WAFS_NORECORD;
	put(fd, off, page, wafsp->wafs_bsize);
	free(page);

	/* Now write the thread information */

	close(fd);
	return (0);
}

void
wafsinit()
{}

