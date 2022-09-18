#ifdef CLFS
/*
 * CLFS
 * $Log: dumpwafs.c,v $
 * Revision 1.5  1994/10/04  17:57:59  margo
 * 4.4Lite implementation of dumpwafs
 *
 */
#endif

/*
 * Copyright (c) 1993, 1994 The President and Fellows of Harvard University
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
#include <sys/ucred.h>
#endif
#include <sys/time.h>
#include <sys/mount.h>

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>

#include <fcntl.h>
#include <fstab.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

static void dump_records __P((int, struct wafs *, int, int));
static void dump_super __P((struct wafs *, int));
static void dump_thread_info __P((int, struct wafs *, int));
static void print_page_header __P((daddr_t, wafs_page_header_t *));
static int  print_record __P((off_t, char *, wafs_type *));
static void usage __P((void));

int daddr_shift;
char *special;

char *progname = "dumpwafs";

int
main(argc, argv)
	int argc;
	char *argv[];
{
	struct wafs wafs_sb1, wafs_sb2, *wafs_master, *wafsp, *tmp_wp;
	daddr_t sb_addr;
	int do_allsb, do_allrecords, do_liverecords, do_thread;
	int ch, fd;

#ifdef DIAGNOSTIC
	printf("Entering main\n");
#endif

	do_allsb = 0;
	do_allrecords = 0;
	do_liverecords = 0;
	while ((ch = getopt(argc, argv, "afFt")) != EOF)
		switch(ch) {
		case 'a':		/* Dump all superblocks */
			do_allsb = 1;
			break;
		case 'F':		/* Really full dump; display all recs */
			do_allrecords = 1;
			do_liverecords = 1;
			break;
		case 'f':		/* Full dump; display live records */
			do_liverecords = 1;
			break;
		case 't':		/* Print thread table */
			do_thread = 1;
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
		fatal("%s: %s", special, strerror(errno));
#ifdef DIAGNOSTIC
	printf("Opening file %s\n", special);
#endif
	/* Read the first superblock */
	get(fd, SBOFF, &wafs_sb1, sizeof(struct wafs));
#ifdef DIAGNOSTIC
	printf("Read superblock\n");
#endif
	daddr_shift = wafs_sb1.wafs_bshift - wafs_sb1.wafs_fsbtodb;

	/*
	 * Compute address of next superblock, verify that the filesyste
	 * is large enough to support multiple superblocks, then read the
	 * alternate superblocks, checking for consistency.
	 */
	wafs_master = &wafs_sb1;
	wafsp = &wafs_sb2;
	for (sb_addr = SBLOCK + SB_INTERVAL_DB(wafs_master);
	    sb_addr < wafs_master->wafs_size << wafs_master->wafs_fsbtodb;
	    sb_addr += SB_INTERVAL_DB(wafs_master)) {
#ifdef DIAGNOSTIC
		printf("Reading superblock at disk address 0x%x\n", sb_addr);
#endif
		get(fd, sb_addr << daddr_shift, wafsp, sizeof(struct wafs));
		dump_super(wafsp, 0);
		if (wafs_master->wafs_time < wafsp->wafs_time) {
			tmp_wp = wafs_master;
			wafs_master = wafsp;
			wafsp = tmp_wp;
		}
		if (!do_allsb)
			break;
	}

	dump_super(wafs_master, 1);

	dump_thread_info(fd, wafs_master, do_thread);
	dump_records(fd, wafs_master, do_liverecords, do_allrecords);
	(void)close(fd);
	exit(0);
}

static void
dump_records(fd, wafsp, doit, doitall)
	int fd;
	struct wafs *wafsp;
	int doit;
	int doitall;
{
	wafs_page_header_t	page_header;
	struct wafs_header	rec_header;
	wafs_type	rectype;
	daddr_t	lbn;
	daddr_t	blocknum;
	caddr_t	page;
	off_t lsn;
	char *rp;
	int nbytes;

	if (!doit)
		return;
#ifdef DIAGNOSTIC
	printf("About to read log records\n");
#endif

	/* Create page buffer. */
	page = (caddr_t)malloc(wafsp->wafs_bsize);
	if (page == NULL) {
		perror("dumpwafs: ");
		return;
	}

	/* 
	 * Read from head, to tail and then on until you
	 * find the last log record (a record followed by
	 * a WAFS_NORECORD).
	 */
	lbn = wafsp->wafs_tail >> wafsp->wafs_bshift;

	do {
		lsn = (off_t) (lbn << wafsp->wafs_bsize);
		blocknum = logical_to_physical(wafsp, lbn);
		get(fd, (blocknum << wafsp->wafs_bshift), page,
		    wafsp->wafs_bsize);
#ifdef DIAGNOSTIC
#ifdef AIX
		printf("Reading logical block %d, physical block 0x%lx, lsn = 0x%x\n", lbn, blocknum, lsn);
#else
		printf("Reading logical block %d, physical block 0x%lx, lsn = 0x%qx\n", lbn, blocknum, lsn);
#endif
#endif
		bcopy(page, &page_header, sizeof(page_header));
		print_page_header(lsn, &page_header);
		rp = page + sizeof(page_header);
		printf("Page pointer = %x\n", rp);
		lsn += sizeof(page_header);
		do {
			nbytes = print_record(lsn, rp, &rectype);
			rp += nbytes;
			lsn += nbytes;
		} while (rectype != WAFS_NORECORD && rp <
		    page + wafsp->wafs_bsize - sizeof(struct wafs_header));

		if (!doitall && lsn >= wafsp->wafs_tail)
			return;
		lbn++;
	} while (rectype != WAFS_NORECORD);
}

static void
dump_super(wafsp, master)
	struct wafs *wafsp;
	int master;
{
	(void)printf("%s Superblock:\n", master ? "Master" : "Alternate");
	(void)printf("%s0x%06X   %s0x%06X   %s  %6d   %s  %6d\n",
		"magic    ", wafsp->wafs_magic,
		"version  ", wafsp->wafs_version,
		"size     ", wafsp->wafs_size,
		"dsize    ", wafsp->wafs_dsize);

	(void)printf("%s  %6d   %s  %6d   %s  %6d   %s  %6d\n",
		"sbsize   ", wafsp->wafs_sbsize,
		"bsize    ", wafsp->wafs_bsize,
		"bmask    ", wafsp->wafs_bmask,
		"bshift   ", wafsp->wafs_bshift);

	(void)printf("%s  %6d   %s  %6d   %s  %6d   %s  %6d\n",
		"minfree  ", wafsp->wafs_minfree,
		"maxthread", wafsp->wafs_maxthreads,
		"tinfopb  ", wafsp->wafs_tinfopb,
		"bfree    ", wafsp->wafs_bfree);

#ifdef AIX
	(void)printf("%s0x%08X %s0x%06X   %s0x%06x   %s0x%06X\n",
#else
	(void)printf("%s%08qx   %s  %6qx   %s  %6qx   %s  %6qx\n",
#endif
		"lsn      ", wafsp->wafs_lsn,
		"check    ", wafsp->wafs_check,
		"head     ", wafsp->wafs_head,
		"tail     ", wafsp->wafs_tail);

	(void)printf("%s0x%06lx   %s  %6d   %s0x%06lx   %s0x%06lx\n",
		"sblkno   ", wafsp->wafs_sblkno,
		"interval ", wafsp->wafs_interval,
		"intshift ", wafsp->wafs_int_shift,
		"sbshift  ", wafsp->wafs_sbshift);

	(void)printf("%s  %6d   %s  %6d   %s%08x   %s0x%08X\n",
		"state    ", wafsp->wafs_state,
		"fsbtodb  ", wafsp->wafs_fsbtodb,
		"id       ", wafsp->wafs_id,
		"cksum    ", wafsp->wafs_cksum);

	(void)printf("%s0x%06X   %s0x%06X   %s0x%06X   %s0x%06X   %s0x%06X\n",
		"flags    ", wafsp->wafs_flags,
		"inchkpt  ", wafsp->wafs_inchkpt,
		"fmod     ", wafsp->wafs_fmod,
		"clean    ", wafsp->wafs_clean,
		"ronly    ", wafsp->wafs_ronly);
	(void)printf("%s   %s", "time       ",
	    ctime((time_t *)&(wafsp)->wafs_time));
	(void)printf("%s   %s\n", "read time  ",
	    ctime((time_t *)&(wafsp)->wafs_rtime));
}

static void
dump_thread_info(fd, wafsp, dostuff)
int fd;
struct wafs *wafsp;
int dostuff;
{
	if (!dostuff)
		return;
}

static void
usage()
{
	(void)fprintf(stderr, "usage: dumpwafs [-af] file\n");
	exit(1);
}

static void
print_page_header(lbn, headerp)
	daddr_t lbn;
	wafs_page_header_t *headerp;
{
	printf("Page %d: 0x%X 0x%X\n", lbn, headerp->tv_sec, headerp->tv_usec);
}

static int
print_record(lsn, recp, rectype)
	off_t lsn;
	char *recp;
	wafs_type *rectype;
{
	struct wafs_header hp;
	char *typestr;

	bcopy(recp, (char *)&hp, sizeof(struct wafs_header));
	switch(hp.rectype) {
	case WAFS_NORECORD:   typestr="NO RECORD"; break;
	case WAFS_RECORD:     typestr="RECORD"; break;
	case WAFS_BEGINREC:   typestr="NBEGIN RECORD"; break;
	case WAFS_ENDREC:     typestr="END RECORD"; break;
	case WAFS_CONTINUE:   typestr="CONTINUE"; break;
	case WAFS_COMMIT:     typestr="COMMIT"; break;
	case WAFS_CHECKPOINT: typestr="CHECKPOINT"; break;
	}

#ifdef AIX
	printf("\tLSN:0x%x %s %d\n", lsn, typestr, hp.length);
#else
	printf("\tLSN:0x%qx %s %d\n", lsn, typestr, hp.length);
#endif
	*rectype = hp.rectype;
	return(hp.length + sizeof(struct wafs_header)); 
}
