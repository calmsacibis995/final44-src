/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 **********************************************************************
 * HISTORY
 * $Log:	subr_rmap.h,v $
 * Revision 2.2  92/01/03  20:33:50  dbg
 * 	Moved here from device directory.  It's not license-free.
 * 	[91/12/23  16:43:42  dbg]
 * 
 * Revision 2.1  89/08/03  15:30:53  rwd
 * Created.
 * 
 * 11-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_KERNEL version.
 *
 * 17-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: Replaced user_pt_map by kernel_pageable_map.
 *	Removed swapmap, nswapmap, argmap (not used).
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 ************************************************************************
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)map.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_MAP_
#define	_MAP_

/*
 * Resource Allocation Maps.
 *
 * Associated routines manage sub-allocation of an address space using
 * an array of segment descriptors.  The first element of this array
 * is a map structure, describing the arrays extent and the name
 * of the controlled object.  Each additional structure represents
 * a free segment of the address space.
 *
 * A call to rminit initializes a resource map and may also be used
 * to free some address space for the map.  Subsequent calls to rmalloc
 * and rmfree allocate and free space in the resource map.  If the resource
 * map becomes too fragmented to be described in the available space,
 * then some of the resource is discarded.  This may lead to critical
 * shortages, but is better than not checking (as the previous versions
 * of these routines did) or giving up and calling panic().  The routines
 * could use linked lists and call a memory allocator when they run
 * out of space, but that would not solve the out of space problem when
 * called at interrupt time.
 *
 * N.B.: The address 0 in the resource address space is not available
 * as it is used internally by the resource map routines.
 */
struct map {
	struct	mapent *m_limit;	/* address of last slot in map */
	char	*m_name;		/* name of resource */
/* we use m_name when the map overflows, in warning messages */
};
struct mapent
{
	int	m_size;		/* size of this segment of the map */
	int	m_addr;		/* resource-space addr of start of segment */
};

void rminit();
long rmalloc();
long rmget();
void rmfree();

#endif	_MAP_
