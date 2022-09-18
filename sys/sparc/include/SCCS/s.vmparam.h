h49846
s 00002/00002/00104
d D 8.1 93/06/11 15:13:00 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00102
d D 7.4 93/05/25 02:55:03 torek 4 3
c raise maximum memory size to 64M
e
s 00002/00002/00104
d D 7.3 93/04/20 18:56:41 torek 3 2
c spelling
e
s 00005/00000/00101
d D 7.2 92/07/21 16:41:44 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00101/00000/00000
d D 7.1 92/07/13 00:43:09 torek 1 0
c date and time created 92/07/13 00:43:09 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: vmparam.h,v 1.6 92/06/24 08:55:18 torek Exp $
E 3
I 3
D 4
 * from: $Header: vmparam.h,v 1.7 92/11/26 02:04:49 torek Exp $
E 4
I 4
 * from: $Header: vmparam.h,v 1.8 93/05/25 09:52:16 torek Exp $
E 4
E 3
 */

/*
 * Machine dependent constants for Sun-4c SPARC
 */

/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.
 */
#define	USRTEXT		0x2000			/* Start of user text */
#define	USRSTACK	KERNBASE		/* Start of user stack */

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
#define	DMTEXT	1024			/* swap allocation for text */

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
 * Mach derived constants
 */

/*
 * User/kernel map constants.  Note that sparc/vaddrs.h defines the
 * IO space virtual base, which must be the same as VM_MAX_KERNEL_ADDRESS:
 * tread with care.
 */
#define VM_MIN_ADDRESS		((vm_offset_t)0x2000)	/* texts start at 8K */
#define VM_MAX_ADDRESS		((vm_offset_t)KERNBASE)
#define VM_MAXUSER_ADDRESS	((vm_offset_t)KERNBASE)
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t)KERNBASE)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t)0xfe000000)

/* virtual sizes (bytes) for various kernel submaps */
#define VM_MBUF_SIZE		(NMBCLUSTERS*MCLBYTES)
#define VM_KMEM_SIZE		(NKMEMCLUSTERS*CLBYTES)
E 1
