/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kalloc.c,v $
 * Revision 2.8  90/08/14  15:32:42  mrt
 * 	Increased size of 512 zone, the new pager seems to use much more of it.
 * 	[90/08/13  14:29:05  af]
 * 
 * Revision 2.7  89/10/11  14:09:58  dlb
 * 	Rewrite kallocinit() to allow the k_zones to be individually
 * 	sized with the sizes in a static (patchable) array.  Loosely
 * 	based on code from Joe Boykin (boykin@encore).
 * 	[89/09/01  17:28:36  dlb]
 * 
 * Revision 2.6  89/08/02  08:03:28  jsb
 * 	Make all kalloc zones 8 MB big. (No more kalloc panics!)
 * 	[89/08/01  14:10:17  jsb]
 * 
 * Revision 2.4  89/04/05  13:03:10  rvb
 * 	Guarantee a zone max of at least 100 elements or 10 pages
 * 	which ever is greater.  Afs (AllocDouble()) puts a great demand
 * 	on the 2048 zone and used to blow away.
 * 	[89/03/09            rvb]
 * 
 * Revision 2.3  89/02/25  18:04:39  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  02:07:04  jsb
 * 	Give each kalloc zone a meaningful name (for panics);
 * 	create a zone for each power of 2 between MINSIZE
 * 	and PAGE_SIZE, instead of using (obsoleted) NQUEUES.
 * 	[89/01/17  10:16:33  jsb]
 * 
 *
 * 13-Feb-88  John Seamons (jks) at NeXT
 *	Updated to use kmem routines instead of vmem routines.
 *
 * 21-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	kern/kalloc.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	General kernel memory allocator.  This allocator is designed
 *	to be used by the kernel to manage dynamic memory fast.
 */

#include <sys/types.h>
#include <mach/vm_param.h>

#include <kern/zalloc.h>
#include <kern/kalloc.h>
#include <vm/vm_kern.h>
#include <vm/vm_object.h>

/*
 *	All allocations of size less than PAGE_SIZE are rounded to the
 *	next highest power of 2.  This allocator is built on top of
 *	the zone allocator.  A zone is created for each potential size
 *	that we are willing to get in small blocks.
 *
 *	We assume that PAGE_SIZE is not greater than 64K;
 *	thus 16 is a safe array size for k_zone and k_zone_name.
 */

int first_k_zone = -1;
struct zone *k_zone[16];
static char *k_zone_name[16] = {
	"kalloc.1",		"kalloc.2",
	"kalloc.4",		"kalloc.8",
	"kalloc.16",		"kalloc.32",
	"kalloc.64",		"kalloc.128",
	"kalloc.256",		"kalloc.512",
	"kalloc.1024",		"kalloc.2048",
	"kalloc.4096",		"kalloc.8192",
	"kalloc.16384",		"kalloc.32768"
};

/*
 *  Max number of elements per zone.  zinit rounds things up correctly
 *  Doing things this way permits each zone to have a different maximum size
 *  based on need, rather than just guessing; it also
 *  means its patchable in case you're wrong!
 */
unsigned long k_zone_max[16] = {
      1024,		/*      1 Byte  */
      1024,		/*      2 Byte  */
      1024,		/*      4 Byte  */
      1024,		/*      8 Byte  */
      1024,		/*     16 Byte  */
      1024,		/*     32 Byte  */
      1024,		/*     64 Byte  */
      1024,		/*    128 Byte  */
      4096,		/*    256 Byte  */
      512,		/*    512 Byte  */
      128,		/*   1024 Byte  */
      128,		/*   2048 Byte  */
      64,		/*   4096 Byte  */
      64,		/*   8192 Byte  */
      64,		/*  16384 Byte  */
      64,		/*  32768 Byte  */
};

/*
 *	Initialize the memory allocator.  This should be called only
 *	once on a system wide basis (i.e. first processor to get here
 *	does the initialization).
 *
 *	This initializes all of the zones.
 */

kallocinit()
{
	register int i, size;

	/*
	 *	Allocate a zone for each size we are going to handle.
	 *	We specify non-paged memory.
	 */
	for (i = 0, size = 1; size < PAGE_SIZE; i++, size <<= 1) {
		if (size < MINSIZE) {
			k_zone[i] = 0;
			continue;
		}
		if (size == MINSIZE) {
			first_k_zone = i;
		}
		k_zone[i] = zinit(size, k_zone_max[i] * size, PAGE_SIZE,
			FALSE, k_zone_name[i]);
	}
}

caddr_t kalloc(size)
{
	register zindex, allocsize;
	caddr_t addr;

	/* compute the size of the block that we will actually allocate */

	allocsize = size;
	if (size < PAGE_SIZE) {
		allocsize = MINSIZE;
		zindex = first_k_zone;
		while (allocsize < size) {
			allocsize <<= 1;
			zindex++;
		}
	}

	/*
	 * If our size is still small enough, check the queue for that size
	 * and allocate.
	 */

	if (allocsize < PAGE_SIZE) {
		addr = (caddr_t) zalloc(k_zone[zindex]);
	} else {
		addr = (caddr_t) kmem_alloc(kernel_map, allocsize);
	}
	return(addr);
}

caddr_t kget(size)
{
	register zindex, allocsize;
	caddr_t addr;

	/* compute the size of the block that we will actually allocate */

	allocsize = size;
	if (size < PAGE_SIZE) {
		allocsize = MINSIZE;
		zindex = first_k_zone;
		while (allocsize < size) {
			allocsize <<= 1;
			zindex++;
		}
	}

	/*
	 * If our size is still small enough, check the queue for that size
	 * and allocate.
	 */

	if (allocsize < PAGE_SIZE) {
		addr = (caddr_t) zget(k_zone[zindex]);
	} else {
		/* This will never work, so we might as well panic */
		panic("kget: oversized request");
	}
	return(addr);
}

kfree(data, size)
	caddr_t	data;
	long	size;
{
	register freesize, zindex;

	freesize = size;
	if (size < PAGE_SIZE) {
		freesize = MINSIZE;
		zindex = first_k_zone;
		while (freesize < size) {
			freesize <<= 1;
			zindex++;
		}
	}

	if (freesize < PAGE_SIZE) {
		zfree(k_zone[zindex], data);
	} else {
		kmem_free(kernel_map, data, freesize);
	}
}
