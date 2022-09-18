/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mach_timedev.c,v $
 * Revision 2.2  89/09/05  20:42:08  jsb
 * 	Original check-in.
 * 	[89/09/05  19:58:25  jsb]
 * 
 */
/*
 *	File:	mach_timedev.c
 *	Author:	Joseph S. Barrera III, Randall Dean
 *
 *	Machine-independent time psuedo-device.
 */
#include <mach/vm_param.h>
#include <vm/vm_kern.h>
#include <sys/time.h>
#include <sys/errno.h>

struct timeval	*mach_tv = 0;
struct timezone	*mach_tz = 0;

int		mach_time_frame = 0;

timeopen()
{
	extern struct timeval time;
	extern struct timezone tz;
	struct tm {
		struct timeval	tv;
		struct timezone	tz;
	} *tm = 0;

	if (mach_tv) {
		return 0;
	}
	if (! (tm = (struct tm *) kmem_alloc(kernel_map, PAGE_SIZE))) {
		return ENOMEM;
	}
	mach_tv = &tm->tv;
	mach_tz = &tm->tz;
	*mach_tv = time;
	*mach_tz = tz;
	mach_time_frame = pmap_phys_to_frame(pmap_extract(pmap_kernel(), tm));
	return 0;
}

timeclose()
{
	return 0;
}

timemap(dev, offset, prot)
	dev_t		dev;
	vm_offset_t	offset;
	vm_prot_t	prot;
{
	if (prot & VM_PROT_WRITE) {
		return -1;
	}
	return mach_time_frame;
}
