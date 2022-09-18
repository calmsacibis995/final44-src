h58701
s 00013/00003/00532
d D 8.5 95/06/10 05:55:07 margo 17 16
c Fix cleaning criteria so that we clean soon enough on very 
c tiny partitions.
e
s 00089/00026/00446
d D 8.4 95/05/24 19:41:28 margo 16 15
c Add more statistics gathering in cleaner.  Also, provide 
c alternative cleaning parameters such as cleaning by number of active 
c bytes instead of number of segments per invocation.
e
s 00001/00001/00471
d D 8.3 95/05/04 16:24:19 mckusick 15 14
c MOUNT types become names
e
s 00025/00024/00447
d D 8.2 94/01/13 18:52:19 bostic 14 13
c the Sparc isn't handling structures passed to the kernel correctly
c change LFS routines that take fsid_t's to take fsid_t *'s.
e
s 00005/00005/00466
d D 8.1 93/06/04 18:55:42 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00004/00460
d D 5.11 93/06/04 18:44:20 cgd 12 11
c if -d flag is not given, become a system daemon w/daemon()
e
s 00019/00012/00445
d D 5.10 93/06/04 17:33:57 cgd 11 10
c require an argument for hfs_cleanerd which specifies fs to clean.
e
s 00009/00009/00448
d D 5.9 93/05/17 11:11:51 bostic 10 9
c unsigned subtraction is never less than 0; bad assignment statements
e
s 00082/00014/00375
d D 5.8 92/12/18 06:35:53 margo 9 8
c Add statistics, add flags to allow caller to specify use of mmap.  
c catch signals to report errors.
e
s 00002/00002/00387
d D 5.7 92/11/01 11:15:35 bostic 8 7
c Add more information on printf when cleaner runs.
e
s 00000/00002/00389
d D 5.6 92/10/06 20:41:21 margo 7 6
c Always report what segment is cleaned.
e
s 00003/00002/00388
d D 5.5 92/09/02 13:21:17 margo 6 5
c Don't clean if its not possible for us to generate any new segments.
e
s 00007/00003/00383
d D 5.4 92/08/26 18:19:46 bostic 5 4
c Add printf and fix error message.
e
s 00011/00004/00375
d D 5.3 92/08/25 14:56:45 bostic 4 3
c If you cleaned some segments, keep cleaning in case other processes 
c wrote a bunch of stuff just after you finished your cleaning spurt.
e
s 00007/00016/00372
d D 5.2 92/08/21 12:00:45 bostic 3 2
c Change markv calling convention to take a single array containing
c both blocks and inodes.
e
s 00019/00000/00369
d D 5.1 92/08/06 12:38:24 bostic 2 1
c integrate into the source tree, yank to 5.1, minor lint
e
s 00369/00000/00000
d D 1.1 92/08/06 12:27:52 bostic 1 0
c date and time created 92/08/06 12:27:52 by bostic
e
u
U
t
T
I 2
/*-
D 13
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/time.h>
I 10

E 10
I 2
D 9

E 9
E 2
#include <ufs/ufs/dinode.h>
#include <ufs/lfs/lfs.h>
D 9

E 9
I 9
D 10
#include <machine/param.h>
E 10
I 10

#include <signal.h>
E 10
E 9
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
I 9
D 10
#include <signal.h>
E 10
E 9

#include "clean.h"
char *special = "cleanerd";
I 9
int do_small = 0;
int do_mmap = 0;
I 16
int stat_report = 0;
E 16
struct cleaner_stats {
I 16
	double	util_tot;
	double	util_sos;
E 16
	int	blocks_read;
	int	blocks_written;
	int	segs_cleaned;
	int	segs_empty;
	int	segs_error;
} cleaner_stats;
E 9

struct seglist { 
	int sl_id;	/* segment number */
	int sl_cost; 	/* cleaning cost */
D 16
	char sl_empty;	/* is segment empty */
E 16
I 16
	char sl_bytes;	/* bytes in segment */
E 16
};

struct tossstruct {
	struct lfs *lfs;
	int seg;
};

I 16
#define	CLEAN_BYTES	0x1

E 16
/* function prototypes for system calls; not sure where they should go */
D 14
int	 lfs_segwait __P((fsid_t, struct timeval *));
int	 lfs_segclean __P((fsid_t, u_long));
int	 lfs_bmapv __P((fsid_t, BLOCK_INFO *, int));
D 3
int	 lfs_markv __P((fsid_t, BLOCK_INFO *, int, INODE_INFO *, int));
E 3
I 3
int	 lfs_markv __P((fsid_t, BLOCK_INFO *, int));
E 14
I 14
int	 lfs_segwait __P((fsid_t *, struct timeval *));
int	 lfs_segclean __P((fsid_t *, u_long));
int	 lfs_bmapv __P((fsid_t *, BLOCK_INFO *, int));
int	 lfs_markv __P((fsid_t *, BLOCK_INFO *, int));
E 14
E 3

/* function prototypes */
int	 bi_tossold __P((const void *, const void *, const void *));
int	 choose_segments __P((FS_INFO *, struct seglist *, 
	     int (*)(FS_INFO *, SEGUSE *)));
D 16
void	 clean_fs __P((FS_INFO	*, int (*)(FS_INFO *, SEGUSE *)));
int	 clean_loop __P((FS_INFO *));
E 16
I 16
void	 clean_fs __P((FS_INFO	*, int (*)(FS_INFO *, SEGUSE *), int, long));
int	 clean_loop __P((FS_INFO *, int, long));
E 16
int	 clean_segment __P((FS_INFO *, int));
int	 cost_benefit __P((FS_INFO *, SEGUSE *));
int	 cost_compare __P((const void *, const void *));
I 9
void	 sig_report __P((int));
E 9

/*
 * Cleaning Cost Functions:
 *
 * These return the cost of cleaning a segment.  The higher the cost value
 * the better it is to clean the segment, so empty segments have the highest
 * cost.  (It is probably better to think of this as a priority value
 * instead).
 *
 * This is the cost-benefit policy simulated and described in Rosenblum's
 * 1991 SOSP paper.
 */

int
cost_benefit(fsp, su)
	FS_INFO *fsp;		/* file system information */
	SEGUSE *su;
{
	struct lfs *lfsp;
	struct timeval t;
	int age;
	int live;

	gettimeofday(&t, NULL);

	live = su->su_nbytes;	
D 10
	age = t.tv_sec - su->su_lastmod < 0 ? 0 : t.tv_sec - su->su_lastmod;
E 10
I 10
	age = t.tv_sec < su->su_lastmod ? 0 : t.tv_sec - su->su_lastmod;
E 10
	
	lfsp = &fsp->fi_lfs;
D 14
	if (live == 0) 
E 14
I 14
	if (live == 0)
E 14
		return (t.tv_sec * lblkno(lfsp, seg_size(lfsp)));
	else {
		/* 
		 * from lfsSegUsage.c (Mendel's code).
		 * priority calculation is done using INTEGER arithmetic.
		 * sizes are in BLOCKS (that is why we use lblkno below).
		 * age is in seconds.
		 *
D 14
		 * priority = ((seg_size - live) * age) / (seg_size + live) 
E 14
I 14
		 * priority = ((seg_size - live) * age) / (seg_size + live)
E 14
		 */
#ifdef VERBOSE
		if (live < 0 || live > seg_size(lfsp)) {
			err(0, "Bad segusage count: %d", live);
			live = 0;
		}
#endif
		return (lblkno(lfsp, seg_size(lfsp) - live) * age)
			/ lblkno(lfsp, seg_size(lfsp) + live);
	}
}

I 2
int
E 2
main(argc, argv)
	int argc;
	char *argv[];
{
D 11
	FS_INFO	*lfp, *fsp;
E 11
I 11
	FS_INFO	*fsp;
E 11
	struct statfs *lstatfsp;	/* file system stats */
	struct timeval timeout;		/* sleep timeout */
	fsid_t fsid;
D 11
	int count;			/* number of file systems */
D 4
	int i;
E 4
I 4
	int i, nclean;
E 11
I 11
D 12
	int i;
E 12
I 12
D 16
	int i, nodaemon;
E 16
I 16
	long clean_opts;		/* cleaning options */
	int i, nodaemon, segs_per_clean;
E 16
E 12
E 11
E 4
D 9
	
E 9
I 9
	int opt, cmd_err;
I 11
	char *fs_name;			/* name of filesystem to clean */
	extern int optind;
E 11
D 10
	extern char *optarg;
E 10

D 12
	cmd_err = 0;
	while ((opt = getopt(argc, argv, "sm")) != EOF) {
E 12
I 12
	cmd_err = nodaemon = 0;
D 16
	while ((opt = getopt(argc, argv, "smd")) != EOF) {
E 16
I 16
	clean_opts = 0;
	segs_per_clean = 1;
	while ((opt = getopt(argc, argv, "bdmn:r:s")) != EOF) {
E 16
E 12
		switch (opt) {
D 16
			case 's':	/* small writes */
				do_small = 1;
E 16
I 16
			case 'b':	/*
					 * Use live bytes to determine
					 * how many segs to clean.
					 */
				clean_opts |= CLEAN_BYTES;
E 16
				break;
D 16
			case 'm':
E 16
I 16
			case 'd':	/* Debug mode. */
				nodaemon = 1;
				break;
			case 'm':	/* Use mmap instead of read/write */
E 16
				do_mmap = 1;
				break;
I 12
D 16
			case 'd':
				nodaemon = 1;
E 16
I 16
			case 'n':	/* How many segs to clean at once */
				segs_per_clean = atoi(optarg);
E 16
				break;
I 16
			case 'r':	/* Report every stat_report segments */
				stat_report = atoi(optarg);
				break;
			case 's':	/* small writes */
				do_small = 1;
				break;
E 16
E 12
			default:
				++cmd_err;
		}
	}
D 11
	if (cmd_err)
		err(1, "usage: lfs_cleanerd [-su]");
E 11
I 11
	argc -= optind;
	argv += optind;
	if (cmd_err || (argc != 1))
D 12
		err(1, "usage: lfs_cleanerd [-sm] fs_name");
E 12
I 12
		err(1, "usage: lfs_cleanerd [-smd] fs_name");
E 12
E 11

I 11
	fs_name = argv[0];

E 11
D 14
	signal (SIGINT, sig_report);
	signal (SIGUSR1, sig_report);
	signal (SIGUSR2, sig_report);
E 14
I 14
	signal(SIGINT, sig_report);
	signal(SIGUSR1, sig_report);
	signal(SIGUSR2, sig_report);
E 14
E 9
D 11
	count = fs_getmntinfo(&lstatfsp, MOUNT_LFS);
E 11
I 11
D 15
	if (fs_getmntinfo(&lstatfsp, fs_name, MOUNT_LFS) == 0) {
E 15
I 15
	if (fs_getmntinfo(&lstatfsp, fs_name, "lfs") == 0) {
E 15
		/* didn't find the filesystem */
		err(1, "lfs_cleanerd: filesystem %s isn't an LFS!", fs_name);
	}
I 12

	if (!nodaemon)	/* should we become a daemon, chdir to / & close fd's */
		if (daemon(0, 0) == -1)
			err(1, "lfs_cleanerd: couldn't become a daemon!");
E 12
E 11

	timeout.tv_sec = 5*60; /* five minutes */
	timeout.tv_usec = 0;
	fsid.val[0] = 0;
	fsid.val[1] = 0;

D 9
	for (fsp = get_fs_info(lstatfsp, count); ; reread_fs_info(fsp, count)) {
E 9
I 9
D 11
	for (fsp = get_fs_info(lstatfsp, count, do_mmap); ;
	    reread_fs_info(fsp, count, do_mmap)) {
E 9
D 4
		for (lfp = fsp, i = 0; i < count; ++lfp, ++i)
			clean_loop(lfp);
E 4
I 4
		for (nclean = 0, lfp = fsp, i = 0; i < count; ++lfp, ++i)
			nclean += clean_loop(lfp);
E 11
I 11
	for (fsp = get_fs_info(lstatfsp, do_mmap); ;
	    reread_fs_info(fsp, do_mmap)) {
E 11
		/*
D 11
		 * If some file systems were actually cleaned, run again
E 11
I 11
		 * clean the filesystem, and, if it needed cleaning
		 * (i.e. it returned nonzero) try it again
E 11
		 * to make sure that some nasty process hasn't just
		 * filled the disk system up.
		 */
D 11
		if (nclean)
E 11
I 11
D 16
		if (clean_loop(fsp))
E 16
I 16
		if (clean_loop(fsp, segs_per_clean, clean_opts))
E 16
E 11
			continue;
E 4

#ifdef VERBOSE
		(void)printf("Cleaner going to sleep.\n");
#endif
D 14
		if (lfs_segwait(fsid, &timeout) < 0)
E 14
I 14
		if (lfs_segwait(&fsid, &timeout) < 0)
E 14
			err(0, "lfs_segwait: returned error\n");	
#ifdef VERBOSE
		(void)printf("Cleaner waking up.\n");
#endif
	}
}

/* return the number of segments cleaned */
int
D 16
clean_loop(fsp)
E 16
I 16
clean_loop(fsp, nsegs, options)
E 16
	FS_INFO	*fsp;	/* file system information */
I 16
	int nsegs;
	long options;
E 16
{
	double loadavg[MAXLOADS];
	time_t	now;
	u_long max_free_segs;
I 17
	u_long db_per_seg;
E 17

        /*
	 * Compute the maximum possible number of free segments, given the
	 * number of free blocks.
	 */
D 17
	max_free_segs = fsp->fi_statfsp->f_bfree / fsp->fi_lfs.lfs_ssize;
E 17
I 17
	db_per_seg = fsbtodb(&fsp->fi_lfs, fsp->fi_lfs.lfs_ssize);
	max_free_segs = fsp->fi_lfs.lfs_bfree / db_per_seg;
E 17
	
	/* 
	 * We will clean if there are not enough free blocks or total clean
	 * space is less than BUSY_LIM % of possible clean space.
	 */
	now = time((time_t *)NULL);
D 6
	if (fsp->fi_cip->clean <= MIN_SEGS(&fsp->fi_lfs) ||
	    fsp->fi_cip->clean < max_free_segs * BUSY_LIM) {
E 6
I 6
D 17
	if (fsp->fi_cip->clean < max_free_segs &&
E 17
I 17
#ifdef VERBOSE
	printf("db_er_seg = %d max_free_segs = %d, bfree = %d avail = %d ",
	    db_per_seg, max_free_segs, fsp->fi_lfs.lfs_bfree,
	    fsp->fi_lfs.lfs_avail);
	printf("clean = %d\n", fsp->fi_cip->clean);
#endif
	if ((fsp->fi_lfs.lfs_bfree - fsp->fi_lfs.lfs_avail > db_per_seg &&
	    fsp->fi_lfs.lfs_avail < db_per_seg) ||
	    (fsp->fi_cip->clean < max_free_segs &&
E 17
	    (fsp->fi_cip->clean <= MIN_SEGS(&fsp->fi_lfs) ||
D 17
	    fsp->fi_cip->clean < max_free_segs * BUSY_LIM)) {
E 17
I 17
	    fsp->fi_cip->clean < max_free_segs * BUSY_LIM))) {
E 17
E 6
D 4
		clean_fs(fsp, cost_benefit);
E 4
D 8
		printf("Cleaner Running  at %s (need space)\n",
		    ctime(&now));
E 8
I 8
		printf("Cleaner Running  at %s (%d of %d segments available)\n",
		    ctime(&now), fsp->fi_cip->clean, max_free_segs);
E 8
I 4
D 16
		clean_fs(fsp, cost_benefit);
E 16
I 16
		clean_fs(fsp, cost_benefit, nsegs, options);
E 16
E 4
		return (1);
	} else {
	        /* 
		 * We will also clean if the system is reasonably idle and
		 * the total clean space is less then IDLE_LIM % of possible
		 * clean space.
		 */
		if (getloadavg(loadavg, MAXLOADS) == -1) {
			perror("getloadavg: failed\n");
			return (-1);
		}
		if (loadavg[ONE_MIN] == 0.0 && loadavg[FIVE_MIN] &&
		    fsp->fi_cip->clean < max_free_segs * IDLE_LIM) {
D 16
		        clean_fs(fsp, cost_benefit);
E 16
I 16
		        clean_fs(fsp, cost_benefit, nsegs, options);
E 16
			printf("Cleaner Running  at %s (system idle)\n",
			    ctime(&now));
			return (1);
		}
	} 
	printf("Cleaner Not Running at %s\n", ctime(&now));
	return (0);
}


void
D 16
clean_fs(fsp, cost_func)
E 16
I 16
clean_fs(fsp, cost_func, nsegs, options)
E 16
	FS_INFO	*fsp;	/* file system information */
	int (*cost_func) __P((FS_INFO *, SEGUSE *));
I 16
	int nsegs;
	long options;
E 16
{
	struct seglist *segs, *sp;
I 16
	int to_clean, cleaned_bytes;
E 16
	int i;

D 14
	if ((segs = malloc(fsp->fi_lfs.lfs_nseg * sizeof(struct seglist)))
	    == NULL) {
E 14
I 14
	if ((segs =
	    malloc(fsp->fi_lfs.lfs_nseg * sizeof(struct seglist))) == NULL) {
E 14
		err(0, "malloc failed");
		return;
	}
	i = choose_segments(fsp, segs, cost_func);
#ifdef VERBOSE
D 5
	printf("clean_fs: cleaning %d segments in file system %s\n",
E 5
I 5
	printf("clean_fs: found %d segments to clean in file system %s\n",
E 5
		i, fsp->fi_statfsp->f_mntonname);
	fflush(stdout);
#endif
D 16
	if (i)
D 5
		for (i = MIN(i, NUM_TO_CLEAN(fsp)), sp = segs; i-- ; ++sp)
E 5
I 5
		for (i = MIN(i, NUM_TO_CLEAN(fsp)), sp = segs; i-- ; ++sp) {
E 5
			if (clean_segment(fsp, sp->sl_id) < 0)
				perror("clean_segment failed");
D 14
			else if (lfs_segclean (fsp->fi_statfsp->f_fsid,
E 14
I 14
			else if (lfs_segclean(&fsp->fi_statfsp->f_fsid,
E 14
			    sp->sl_id) < 0)
				perror("lfs_segclean failed");
I 5
D 7
#ifdef VERBOSE
E 7
			printf("Completed cleaning segment %d\n", sp->sl_id);
D 7
#endif
E 7
		}
E 16
I 16
	if (i) {
		/* Check which cleaning algorithm to use. */
		if (options & CLEAN_BYTES) {
			cleaned_bytes = 0;
			to_clean = nsegs <<
			    (fsp->fi_lfs.lfs_segshift + fsp->fi_lfs.lfs_bshift);
			for (sp = segs; i && cleaned_bytes < to_clean;
			    i--, ++sp) {
				if (clean_segment(fsp, sp->sl_id) < 0)
					perror("clean_segment failed");
				else if (lfs_segclean(&fsp->fi_statfsp->f_fsid,
				    sp->sl_id) < 0)
					perror("lfs_segclean failed");
				printf("Cleaned segment %d (%d bytes)\n",
				    sp->sl_id, sp->sl_bytes);
				cleaned_bytes += sp->sl_bytes;
			}
		} else
			for (i = MIN(i, nsegs), sp = segs; i-- ; ++sp) {
				if (clean_segment(fsp, sp->sl_id) < 0)
					perror("clean_segment failed");
				else if (lfs_segclean(&fsp->fi_statfsp->f_fsid,
				    sp->sl_id) < 0)
					perror("lfs_segclean failed");
				printf("Completed cleaning segment %d\n", sp->sl_id);
			}
	}
E 16
E 5
	free(segs);
}

/*
 * Segment with the highest priority get sorted to the beginning of the
 * list.  This sort assumes that empty segments always have a higher
 * cost/benefit than any utilized segment.
 */
int
cost_compare(a, b)
	const void *a;
	const void *b;
{
	return (((struct seglist *)b)->sl_cost -
	    ((struct seglist *)a)->sl_cost);
}


/*
 * Returns the number of segments to be cleaned with the elements of seglist
 * filled in.
 */
int
choose_segments(fsp, seglist, cost_func)
	FS_INFO *fsp;
	struct seglist *seglist;
	int (*cost_func) __P((FS_INFO *, SEGUSE *));
{
	struct lfs *lfsp;
	struct seglist *sp;
	SEGUSE *sup;
	int i, nsegs;

	lfsp = &fsp->fi_lfs;

#ifdef VERBOSE
D 14
	(void) printf("Entering choose_segments\n");
E 14
I 14
	(void)printf("Entering choose_segments\n");
E 14
#endif
	dump_super(lfsp);
	dump_cleaner_info(fsp->fi_cip);

	for (sp = seglist, i = 0; i < lfsp->lfs_nseg; ++i) {
		sup = SEGUSE_ENTRY(lfsp, fsp->fi_segusep, i);
		 PRINT_SEGUSE(sup, i);
		if (!(sup->su_flags & SEGUSE_DIRTY) ||
		    sup->su_flags & SEGUSE_ACTIVE)
			continue;
#ifdef VERBOSE
D 14
		(void) printf("\tchoosing segment %d\n", i);
E 14
I 14
		(void)printf("\tchoosing segment %d\n", i);
E 14
#endif
		sp->sl_cost = (*cost_func)(fsp, sup);
		sp->sl_id = i;
D 16
		sp->sl_empty = sup->su_nbytes ? 0 : 1;
E 16
I 16
		sp->sl_bytes = sup->su_nbytes;
E 16
		++sp;
	}
	nsegs = sp - seglist;
	qsort(seglist, nsegs, sizeof(struct seglist), cost_compare);
#ifdef VERBOSE
	(void)printf("Returning %d segments\n", nsegs);
#endif
	return (nsegs);
}


int
clean_segment(fsp, id)
	FS_INFO *fsp;	/* file system information */
	int id;		/* segment number */
{
D 9
	BLOCK_INFO *block_array;
E 9
I 9
	BLOCK_INFO *block_array, *bp;
E 9
D 3
	INODE_INFO *inode_array;
E 3
	SEGUSE *sp;
	struct lfs *lfsp;
	struct tossstruct t;
	caddr_t seg_buf;
I 16
	double util;
E 16
D 3
	int num_inodes, num_blocks;
E 3
I 3
D 9
	int num_blocks;
E 9
I 9
	int num_blocks, maxblocks, clean_blocks;
E 9
E 3

	lfsp = &fsp->fi_lfs;
	sp = SEGUSE_ENTRY(lfsp, fsp->fi_segusep, id);

#ifdef VERBOSE
D 14
	(void) printf("cleaning segment %d: contains %lu bytes\n", id,
E 14
I 14
	(void)printf("cleaning segment %d: contains %lu bytes\n", id,
E 14
	    sp->su_nbytes);
	fflush(stdout);
#endif
	/* XXX could add debugging to verify that segment is really empty */
D 9
	if (sp->su_nbytes == sp->su_nsums * LFS_SUMMARY_SIZE)
E 9
I 9
	if (sp->su_nbytes == sp->su_nsums * LFS_SUMMARY_SIZE) {
		++cleaner_stats.segs_empty;
E 9
		return (0);
I 9
	}
E 9

	/* map the segment into a buffer */
D 9
	if (mmap_segment(fsp, id, &seg_buf) < 0) {
E 9
I 9
	if (mmap_segment(fsp, id, &seg_buf, do_mmap) < 0) {
E 9
		err(0, "mmap_segment failed");
I 9
		++cleaner_stats.segs_error;
E 9
		return (-1);
	}
	/* get a list of blocks that are contained by the segment */
D 3
	if (lfs_segmapv(fsp, id, seg_buf, &block_array, &num_blocks, 
	    &inode_array, &num_inodes) < 0) {
E 3
I 3
	if (lfs_segmapv(fsp, id, seg_buf, &block_array, &num_blocks) < 0) {
E 3
		err(0, "clean_segment: lfs_segmapv failed");
I 9
		++cleaner_stats.segs_error;
E 9
		return (-1);
	}
I 9
	cleaner_stats.blocks_read += fsp->fi_lfs.lfs_ssize;
E 9

#ifdef VERBOSE
D 3
	(void) printf("lfs_segmapv returned %d blocks and %d inodes\n",
	    num_blocks, num_inodes);
E 3
I 3
D 14
	(void) printf("lfs_segmapv returned %d blocks\n", num_blocks);
E 3
	fflush (stdout);
E 14
I 14
	(void)printf("lfs_segmapv returned %d blocks\n", num_blocks);
	fflush(stdout);
E 14
#endif

	/* get the current disk address of blocks contained by the segment */
D 14
	if (lfs_bmapv(fsp->fi_statfsp->f_fsid, block_array, num_blocks) < 0) {
E 14
I 14
	if (lfs_bmapv(&fsp->fi_statfsp->f_fsid, block_array, num_blocks) < 0) {
E 14
		perror("clean_segment: lfs_bmapv failed\n");
I 9
		++cleaner_stats.segs_error;
E 9
		return -1;
	}

	/* Now toss any blocks not in the current segment */
	t.lfs = lfsp;
	t.seg = id;
	toss(block_array, &num_blocks, sizeof(BLOCK_INFO), bi_tossold, &t);

	/* Check if last element should be tossed */
	if (num_blocks && bi_tossold(&t, block_array + num_blocks - 1, NULL))
		--num_blocks;

#ifdef VERBOSE
	{
		BLOCK_INFO *_bip;
D 3
		INODE_INFO *_iip;
E 3
		u_long *lp;
		int i;

D 14
		(void) printf("after bmapv still have %d blocks\n", num_blocks);
		fflush (stdout);
E 14
I 14
		(void)printf("after bmapv still have %d blocks\n", num_blocks);
		fflush(stdout);
E 14
		if (num_blocks)
			printf("BLOCK INFOS\n");
		for (_bip = block_array, i=0; i < num_blocks; ++_bip, ++i) {
			PRINT_BINFO(_bip);
			lp = (u_long *)_bip->bi_bp;
		}
D 3
		if (num_inodes)
			printf("INODE INFOS\n");
		for (_iip = inode_array, i=0; i < num_inodes; ++_iip, ++i)
			PRINT_IINFO(1, _iip);
E 3
	}
I 16

E 16
#endif
I 16
	++cleaner_stats.segs_cleaned;
E 16
D 9
	/* rewrite the live data */
D 3
	if (num_blocks > 0 || num_inodes > 0)
		if (lfs_markv(fsp->fi_statfsp->f_fsid, block_array, num_blocks,
		    inode_array, num_inodes) < 0) {
E 3
I 3
	if (num_blocks > 0)
		if (lfs_markv(fsp->fi_statfsp->f_fsid, block_array, num_blocks)
		    < 0 ) {
E 9
I 9
	cleaner_stats.blocks_written += num_blocks;
I 16
	util = ((double)num_blocks / fsp->fi_lfs.lfs_ssize);
	cleaner_stats.util_tot += util;
	cleaner_stats.util_sos += util * util;

E 16
	if (do_small)
		maxblocks = MAXPHYS / fsp->fi_lfs.lfs_bsize - 1;
	else
		maxblocks = num_blocks;

	for (bp = block_array; num_blocks > 0; bp += clean_blocks) {
		clean_blocks = maxblocks < num_blocks ? maxblocks : num_blocks;
D 14
		if (lfs_markv(fsp->fi_statfsp->f_fsid, bp, clean_blocks) < 0 ) {
E 14
I 14
		if (lfs_markv(&fsp->fi_statfsp->f_fsid,
		    bp, clean_blocks) < 0) {
E 14
E 9
E 3
D 5
			err(0, "clean_segment: lfs_bmapv failed");
E 5
I 5
			err(0, "clean_segment: lfs_markv failed");
I 9
			++cleaner_stats.segs_error;
E 9
E 5
			return (-1);
		}
I 9
		num_blocks -= clean_blocks;
	}
		
E 9
	free(block_array);
D 3
	free(inode_array);
E 3
D 9
	munmap_segment(fsp, seg_buf);

E 9
I 9
D 14
	munmap_segment (fsp, seg_buf, do_mmap);
E 14
I 14
	munmap_segment(fsp, seg_buf, do_mmap);
E 14
D 16
	++cleaner_stats.segs_cleaned;
E 16
I 16
	if (stat_report && cleaner_stats.segs_cleaned % stat_report == 0)
		sig_report(SIGUSR1);
E 16
E 9
	return (0);
}


int
bi_tossold(client, a, b)
	const void *client;
	const void *a;
	const void *b;
{
	const struct tossstruct *t;

	t = (struct tossstruct *)client;

	return (((BLOCK_INFO *)a)->bi_daddr == LFS_UNUSED_DADDR ||
	    datosn(t->lfs, ((BLOCK_INFO *)a)->bi_daddr) != t->seg);
I 9
}

void
sig_report(sig)
	int sig;
{
I 16
	double avg;

E 16
D 14
	printf ("lfs_cleanerd:\t%s%d\n\t\t%s%d\n\t\t%s%d\n\t\t%s%d\n\t\t%s%d\n",
E 14
I 14
	printf("lfs_cleanerd:\t%s%d\n\t\t%s%d\n\t\t%s%d\n\t\t%s%d\n\t\t%s%d\n",
E 14
		"blocks_read    ", cleaner_stats.blocks_read,
		"blocks_written ", cleaner_stats.blocks_written,
		"segs_cleaned   ", cleaner_stats.segs_cleaned,
		"segs_empty     ", cleaner_stats.segs_empty,
		"seg_error      ", cleaner_stats.segs_error);
I 16
	printf("\t\t%s%5.2f\n\t\t%s%5.2f\n",
		"util_tot       ", cleaner_stats.util_tot,
		"util_sos       ", cleaner_stats.util_sos);
	printf("\t\tavg util: %4.2f std dev: %9.6f\n",
		avg = cleaner_stats.util_tot / cleaner_stats.segs_cleaned,
		cleaner_stats.util_sos / cleaner_stats.segs_cleaned - avg * avg);
		
		
E 16
	if (sig == SIGUSR2) {
D 10
		cleaner_stats.blocks_read == 0;
		cleaner_stats.blocks_written == 0;
		cleaner_stats.segs_cleaned == 0;
		cleaner_stats.segs_empty == 0;
		cleaner_stats.segs_error == 0;
E 10
I 10
		cleaner_stats.blocks_read = 0;
		cleaner_stats.blocks_written = 0;
		cleaner_stats.segs_cleaned = 0;
		cleaner_stats.segs_empty = 0;
		cleaner_stats.segs_error = 0;
I 16
		cleaner_stats.util_tot = 0.0;
		cleaner_stats.util_sos = 0.0;
E 16
E 10
	}
	if (sig == SIGINT)
		exit(0);
E 9
}
E 1
