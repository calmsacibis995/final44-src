h11102
s 00000/00003/00213
d D 8.2 94/04/22 15:07:16 mckusick 5 4
c get rid of unused MINFREE parameter
e
s 00002/00002/00214
d D 8.1 93/06/10 23:03:14 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00004/00214
d D 7.3 93/05/09 16:08:37 ralph 3 2
c fix definitions for USRTEXT and LOWPAGES for a.out programs.
e
s 00001/00001/00217
d D 7.2 93/02/04 19:41:34 ralph 2 1
c a.out programs begin at virt. address 0x1000
e
s 00218/00000/00000
d D 7.1 92/01/07 20:35:54 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: vmparam.h 1.16 91/01/18$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent constants for DEC Station 3100.
 */
/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.  LOWPAGES and HIGHPAGES are
 * the number of pages from the beginning of the P0 region to the
 * beginning of the text and from the beginning of the P1 region to the
 * beginning of the stack respectively.
 */
D 3
#define	USRTEXT		0x00400000
#define	USRDATA		0x10000000
E 3
I 3
#define	USRTEXT		0x00001000
E 3
#define	USRSTACK	0x80000000	/* Start of user stack */
#define	BTOPUSRSTACK	0x80000		/* btop(USRSTACK) */
D 3
#define	LOWPAGES	0x00400
#define	MIDPAGES	0x10000
E 3
I 3
#define	LOWPAGES	0x00001
E 3
#define	HIGHPAGES	0

/*
 * Virtual memory related constants, all in bytes
 */
#ifndef MAXTSIZ
#define	MAXTSIZ		(24*1024*1024)		/* max text size */
#endif
#ifndef DFLDSIZ
#define	DFLDSIZ		(32*1024*1024)		/* initial data size limit */
#endif
#ifndef MAXDSIZ
#define	MAXDSIZ		(32*1024*1024)		/* max data size */
#endif
#ifndef	DFLSSIZ
#define	DFLSSIZ		(1024*1024)		/* initial stack size limit */
#endif
#ifndef	MAXSSIZ
#define	MAXSSIZ		MAXDSIZ			/* max stack size */
#endif

/*
 * Default sizes of swap allocation chunks (see dmap.h).
 * The actual values may be changed in vminit() based on MAXDSIZ.
 * With MAXDSIZ of 16Mb and NDMAP of 38, dmmax will be 1024.
 * DMMIN should be at least ctod(1) so that vtod() works.
 * vminit() insures this.
 */
#define	DMMIN	32			/* smallest swap allocation */
#define	DMMAX	4096			/* largest potential swap allocation */

/*
 * Sizes of the system and user portions of the system page table.
 */
/* SYSPTSIZE IS SILLY; (really number of buffers for I/O) */
#define	SYSPTSIZE	1228
#define	USRPTSIZE 	1024

/*
 * PTEs for mapping user space into the kernel for phyio operations.
 * 16 pte's are enough to cover 8 disks * MAXBSIZE.
 */
#ifndef USRIOSIZE
#define USRIOSIZE	32
#endif

/*
 * PTEs for system V style shared memory.
 * This is basically slop for kmempt which we actually allocate (malloc) from.
 */
#ifndef SHMMAXPGS
#define SHMMAXPGS	1024		/* 4mb */
#endif

/*
 * Boundary at which to place first MAPMEM segment if not explicitly
 * specified.  Should be a power of two.  This allows some slop for
 * the data segment to grow underneath the first mapped segment.
 */
#define MMSEG		0x200000

/*
 * The size of the clock loop.
 */
#define	LOOPPAGES	(maxfree - firstfree)

/*
 * The time for a process to be blocked before being very swappable.
 * This is a number of seconds which the system takes as being a non-trivial
 * amount of real time.  You probably shouldn't change this;
 * it is used in subtle ways (fractions and multiples of it are, that is, like
 * half of a ``long time'', almost a long time, etc.)
 * It is related to human patience and other factors which don't really
 * change over time.
 */
#define	MAXSLP 		20

/*
 * A swapped in process is given a small amount of core without being bothered
 * by the page replacement algorithm.  Basically this says that if you are
 * swapped in you deserve some resources.  We protect the last SAFERSS
 * pages against paging and will just swap you out rather than paging you.
 * Note that each process has at least UPAGES+CLSIZE pages which are not
 * paged anyways (this is currently 8+2=10 pages or 5k bytes), so this
 * number just means a swapped in process is given around 25k bytes.
 * Just for fun: current memory prices are 4600$ a megabyte on VAX (4/22/81),
 * so we loan each swapped in process memory worth 100$, or just admit
 * that we don't consider it worthwhile and swap it out to disk which costs
 * $30/mb or about $0.75.
 */
#define	SAFERSS		4		/* nominal ``small'' resident set size
					   protected against replacement */

/*
 * DISKRPM is used to estimate the number of paging i/o operations
 * which one can expect from a single disk controller.
 */
#define	DISKRPM		60

/*
 * Klustering constants.  Klustering is the gathering
 * of pages together for pagein/pageout, while clustering
 * is the treatment of hardware page size as though it were
 * larger than it really is.
 *
 * KLMAX gives maximum cluster size in CLSIZE page (cluster-page)
 * units.  Note that ctod(KLMAX*CLSIZE) must be <= DMMIN in dmap.h.
 * ctob(KLMAX) should also be less than MAXPHYS (in vm_swp.c)
 * unless you like "big push" panics.
 */

#ifdef notdef /* XXX */
#define	KLMAX	(4/CLSIZE)
#define	KLSEQL	(2/CLSIZE)		/* in klust if vadvise(VA_SEQL) */
#define	KLIN	(4/CLSIZE)		/* default data/stack in klust */
#define	KLTXT	(4/CLSIZE)		/* default text in klust */
#define	KLOUT	(4/CLSIZE)
#else
#define	KLMAX	(1/CLSIZE)
#define	KLSEQL	(1/CLSIZE)
#define	KLIN	(1/CLSIZE)
#define	KLTXT	(1/CLSIZE)
#define	KLOUT	(1/CLSIZE)
#endif

/*
 * KLSDIST is the advance or retard of the fifo reclaim for sequential
 * processes data space.
 */
#define	KLSDIST	3		/* klusters advance/retard for seq. fifo */

/*
 * Paging thresholds (see vm_sched.c).
 * Strategy of 1/19/85:
 *	lotsfree is 512k bytes, but at most 1/4 of memory
 *	desfree is 200k bytes, but at most 1/8 of memory
D 5
 *	minfree is 64k bytes, but at most 1/2 of desfree
E 5
 */
#define	LOTSFREE	(512 * 1024)
#define	LOTSFREEFRACT	4
#define	DESFREE		(200 * 1024)
#define	DESFREEFRACT	8
D 5
#define	MINFREE		(64 * 1024)
#define	MINFREEFRACT	2
E 5

/*
 * There are two clock hands, initially separated by HANDSPREAD bytes
 * (but at most all of user memory).  The amount of time to reclaim
 * a page once the pageout process examines it increases with this
 * distance and decreases as the scan rate rises.
 */
#define	HANDSPREAD	(2 * 1024 * 1024)

/*
 * The number of times per second to recompute the desired paging rate
 * and poke the pagedaemon.
 */
#define	RATETOSCHEDPAGING	4

/*
 * Believed threshold (in megabytes) for which interleaved
 * swapping area is desirable.
 */
#define	LOTSOFMEM	2

#define	mapin(pte, v, pfnum, prot) \
	(*(int *)(pte) = ((pfnum) << PG_SHIFT) | (prot), MachTLBFlushAddr(v))

/*
 * Mach derived constants
 */

/* user/kernel map constants */
D 2
#define VM_MIN_ADDRESS		((vm_offset_t)0)
E 2
I 2
#define VM_MIN_ADDRESS		((vm_offset_t)0x1000)
E 2
#define VM_MAXUSER_ADDRESS	((vm_offset_t)0x80000000)
#define VM_MAX_ADDRESS		((vm_offset_t)0x80000000)
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t)0xC0000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t)0xFFFFC000)

/* virtual sizes (bytes) for various kernel submaps */
#define VM_MBUF_SIZE		(NMBCLUSTERS*MCLBYTES)
#define VM_KMEM_SIZE		(NKMEMCLUSTERS*CLBYTES)
#define VM_PHYS_SIZE		(USRIOSIZE*CLBYTES)

/* pcb base */
#define	pcbb(p)		((u_int)(p)->p_addr)
E 1
