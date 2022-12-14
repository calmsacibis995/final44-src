h03760
s 00000/00003/00221
d D 8.3 94/04/22 15:06:30 mckusick 5 4
c get rid of unused MINFREE parameter
e
s 00004/00004/00220
d D 8.2 93/08/15 11:24:53 mckusick 4 3
c final update from Akito Fujita
e
s 00002/00002/00222
d D 8.1 93/06/10 22:22:29 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00223
d D 7.2 93/01/02 13:39:32 akito 2 1
c sync up to hp300/include/vmparam.h   7.4
e
s 00226/00000/00000
d D 7.1 92/06/15 06:28:32 fujita 1 0
c date and time created 92/06/15 06:28:32 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 3
 * Copyright (c) 1982, 1986, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1986, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: vmparam.h 1.16 91/01/18$
D 2
 * OMRON: $Id: vmparam.h,v 1.3 92/06/14 18:08:16 moti Exp $
 *
 * from: hp300/include/vmparam.h	7.3 (Berkeley) 5/7/91
E 2
I 2
D 4
 * from: hp300/include/vmparam.h	7.4 (Berkeley) 6/5/92
E 4
I 4
 * from: hp300/include/vmparam.h	8.1 (Berkeley) 6/10/93
E 4
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent constants for HP300
 */
/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.  LOWPAGES and HIGHPAGES are
 * the number of pages from the beginning of the P0 region to the
 * beginning of the text and from the beginning of the P1 region to the
 * beginning of the stack respectively.
 *
 * NOTE: the ONLY reason that HIGHPAGES is 0x100 instead of UPAGES (3)
 * is for HPUX compatibility.  Why??  Because HPUX's debuggers
 * have the user's stack hard-wired at FFF00000 for post-mortems,
 * and we must be compatible...
 */
#define	USRTEXT		0
#define	USRSTACK	(-HIGHPAGES*NBPG)	/* Start of user stack */
#define	BTOPUSRSTACK	(0x100000-HIGHPAGES)	/* btop(USRSTACK) */
#define P1PAGES		0x100000
#define	LOWPAGES	0
#define HIGHPAGES	(0x100000/NBPG)

/* 
 * In kernel address space, user stack and user structure is mapped at 
 * KERNELSTACK(LUNA only). Because LUNA has only 0x80000000 kernel 
 * address space and last 1G(0x40000000-0x7FFFFFFF) is IO mapping space.
 * See below VM_MAX_KERNEL_ADDRESS define.
 */
#define	KERNELSTACK	0x3FF00000		

/*
 * Virtual memory related constants, all in bytes
 */
#ifndef MAXTSIZ
D 4
#define	MAXTSIZ		(6*1024*1024)		/* max text size */
E 4
I 4
#define	MAXTSIZ		(8*1024*1024)		/* max text size */
E 4
#endif
#ifndef DFLDSIZ
D 4
#define	DFLDSIZ		(8*1024*1024)		/* initial data size limit */
E 4
I 4
#define	DFLDSIZ		(16*1024*1024)		/* initial data size limit */
E 4
#endif
#ifndef MAXDSIZ
D 4
#define	MAXDSIZ		(16*1024*1024)		/* max data size */
E 4
I 4
#define	MAXDSIZ		(64*1024*1024)		/* max data size */
E 4
#endif
#ifndef	DFLSSIZ
#define	DFLSSIZ		(512*1024)		/* initial stack size limit */
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
/* SYSPTSIZE IS SILLY; IT SHOULD BE COMPUTED AT BOOT TIME */
#define	SYSPTSIZE	(2 * NPTEPG)	/* 8mb */
#define	USRPTSIZE 	(1 * NPTEPG)	/* 4mb */

/*
 * PTEs for mapping user space into the kernel for phyio operations.
 * One page is enough to handle 4Mb of simultaneous raw IO operations.
 */
#ifndef USRIOSIZE
#define USRIOSIZE	(1 * NPTEPG)	/* 4mb */
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

#define	KLMAX	(4/CLSIZE)
#define	KLSEQL	(2/CLSIZE)		/* in klust if vadvise(VA_SEQL) */
#define	KLIN	(4/CLSIZE)		/* default data/stack in klust */
#define	KLTXT	(4/CLSIZE)		/* default text in klust */
#define	KLOUT	(4/CLSIZE)

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

/*
 * Mach derived constants
 */

/* user/kernel map constants */
#define VM_MIN_ADDRESS		((vm_offset_t)0)
#define VM_MAXUSER_ADDRESS	((vm_offset_t)0xFFF00000)
#define VM_MAX_ADDRESS		((vm_offset_t)0xFFF00000)
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t)0)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t)0x7FFFF000)

/* virtual sizes (bytes) for various kernel submaps */
#define VM_MBUF_SIZE		(NMBCLUSTERS*MCLBYTES)
#define VM_KMEM_SIZE		(NKMEMCLUSTERS*CLBYTES)
#define VM_PHYS_SIZE		(USRIOSIZE*CLBYTES)

/* # of kernel PT pages (initial only, can grow dynamically) */
#define VM_KERNEL_PT_PAGES	((vm_size_t)2)		/* XXX: SYSPTSIZE */

/* pcb base */
#define	pcbb(p)		((u_int)(p)->p_addr)
E 1
