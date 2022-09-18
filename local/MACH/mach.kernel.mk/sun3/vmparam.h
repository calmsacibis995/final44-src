/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmparam.h,v $
 * Revision 2.4  89/03/09  21:39:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:48:44  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 02-Mar-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed MAXDSIZ and MAXSSIZ to split the memory leftover
 *	after subtracting MAXTSIZ.
 *
 * 30-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved user stack to top of user area for MACH (no UAREA).
 *
 * 28-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Made compile outside of kernel.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed limits to be in terms of bytes (instead of clicks)
 *	to match 4.3.
 *
 *  4-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added default data and stack size limits.
 *
 */

/*      @(#)vmparam.h 1.1 86/02/03 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Machine dependent constants for Sun-3
 */

/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.  LOWPAGES and HIGHPAGES are
 * the number of pages from the beginning of the P0 region to the
 * beginning of the text and from the end of the stack to the end of the P1
 * region respectively.
 */
#define USRTEXT		NBPG			/* start of users text */
#define OUSRTEXT	0x8000			/*   ... for old Sun-2 a.outs */
#define USRSTACK	KERNELBASE		/* start of users stack */
#define BTOPUSRSTACK	(btop(USRSTACK))

#define P1PAGES		btoc(USRSTACK)		/* no of pages in P1 region */
#define LOWPAGES	btoc(USRTEXT)		/* no pages from P0 to text */
#define HIGHPAGES	0			/* no pages from P1 to stack */

/*
 * Virtual memory related constants
 */
#define SLOP		32
#ifndef	DFLDSIZ
#define DFLDSIZ		(6*1024*1024)		/* initial data size limit */
#endif
#ifndef	DFLSSIZ
#define DFLSSIZ		(512*1024)		/* initial stack size limit */
#endif
#ifndef	MAXTSIZ
#define MAXTSIZ		(32*1024*1024)		/* max text size (bytes) */
#endif
#ifndef	MAXDSIZ
#define MAXDSIZ		(USRSTACK-MAXTSIZ)/2	/* max data size (bytes) */
#endif
#ifndef	MAXSSIZ
#define MAXSSIZ		(USRSTACK-MAXTSIZ)/2	/* max stack size (clicks) */
#endif

/*
 * Sizes of the system and user portions of the system page table.
 * Note that they point into the kernel virtual address space, hence
 *   what they describe is the size of the table space, not the size of
 *   the space which can be mapped.
 */
#define SYSPTSIZE	(0x100000/NBPG)
#define USRPTSIZE 	(0xa00000/NBPG)
/*
 * The size of the clock loop.
 */
#define LOOPPAGES	(maxfree - firstfree)

/*
 * The time for a process to be blocked before being very swappable.
 * This is a number of seconds which the system takes as being a non-trivial
 * amount of real time.  You probably shouldn't change this;
 * it is used in subtle ways (fractions and multiples of it are, that is, like
 * half of a ``long time'', almost a long time, etc.)
 * It is related to human patience and other factors which don't really
 * change over time.
 */
#define MAXSLP 		20

/*
 * A swapped in process is given a small amount of core without being bothered
 * by the page replacement algorithm.  Basically this says that if you are
 * swapped in you deserve some resources.  We protect the last SAFERSS
 * pages against paging and will just swap you out rather than paging you.
 * Note that each process has at least UPAGES+CLSIZE pages which are not
 * paged anyways (this is currently 1+1=2 pages or 16k bytes), so this
 * number just means a swapped in process is given around 40k bytes.
 */
#define SAFERSS		3		/* nominal ``small'' resident set size
					   protected against replacement */

/*
 * DISKRPM is used to estimate the number of paging i/o operations
 * which one can expect from a single disk controller.
 */
#define DISKRPM		60

/*
 * Klustering constants.  Klustering is the gathering
 * of pages together for pagein/pageout, while clustering
 * is the treatment of hardware page size as though it were
 * larger than it really is.
 *
 * KLMAX gives maximum cluster size in CLSIZE page (cluster-page)
 * units.  Note that KLMAX*CLSIZE must be a divisor of DMMIN in
 * autoconf.c and <= MAXPHYS/CLBYTES in vm_swp.c.
 */

#define KLMAX	(2/CLSIZE)
#define KLSEQL	(2/CLSIZE)		/* in klust if vadvise(VA_SEQL) */
#define KLIN	(1/CLSIZE)		/* default data/stack in klust */
#define KLTXT	(1/CLSIZE)		/* default text in klust */
#define KLOUT	(2/CLSIZE)

/*
 * KLSDIST is the advance or retard of the fifo reclaim for sequential
 * processes data space.
 */
#define KLSDIST	2		/* klusters advance/retard for seq. fifo */

/*
 * Paging thresholds (see vm_sched.c).
 * Strategy of 3/17/83:
 *	lotsfree is 1/8 of memory free.
 *	desfree is 100k bytes, but at most 1/16 of memory
 *	minfree is 32k bytes, but at most 1/2 of desfree
 */
#define LOTSFREEFRACT	8
#define DESFREE		(100 * 1024)
#define DESFREEFRACT	16
#define MINFREE		(32 * 1024)
#define MINFREEFRACT	2

/*
 * Paged text files that are less than PGTHRESH bytes may be swapped
 * in instead of paged in.
 */
#define PGTHRESH	(200 * 1024)
