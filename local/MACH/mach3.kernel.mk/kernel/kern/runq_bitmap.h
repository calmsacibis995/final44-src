/* 
 * Mach Operating System
 * Copyright (c) 1994 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	runq_bitmap.h,v $
 * Revision 2.2  94/12/16  10:50:29  dbg
 * 	Macros to manipulate bitmaps in run queues.
 * 	[94/03/09            dbg]
 * 
 */

#ifndef	_KERN_RUNQ_BITMAP_H_
#define	_KERN_RUNQ_BITMAP_H_
/*
 *	Macros to set, clear, and find the highest bit
 *	in the run queue bitmap.  They come in two
 *	different bit orderings, depending on the
 *	order of the machine`s "find first bit set"
 *	instruction (if it has one).
 */

#include <machine/bit.h>

#ifndef	BIT_SET
#define	BIT_SET(bitmap,index)	((bitmap) |= (1 << (index)))
#endif
#ifndef	BIT_CLEAR
#define	BIT_CLEAR(bitmap,index)	((bitmap) &=~(1 << (index)))
#endif

#ifdef	BIT_FIND_LOW
/*
 *	Scheduler bitmap macros for machines where FFS
 *	finds the first bit starting at low-order bit
 *
 *	We store bits right-to-left:
 *		bit 0 is policy NUM_POLICIES-1
 *		bit NUM_POLICIES-1 is policy 0
 *	so that FFS will have as few bits to search as possible.
 */

#define	RUNQ_BIT_SET(bitmap, index) \
	(BIT_SET(bitmap, NUM_POLICIES-1-(index)))
#define	RUNQ_BIT_CLEAR(bitmap, index) \
	(BIT_CLEAR(bitmap, NUM_POLICIES-1-(index)))
#define	RUNQ_BIT_FIND(bitmap, index) \
    MACRO_BEGIN \
	(index) = NUM_POLICIES-1-BIT_FIND_LOW(bitmap); \
    MACRO_END

#endif	/* BIT_FIND_LOW */

#ifdef	BIT_FIND_HIGH
/*
 *	Scheduler bitmap macros for machines where FFS
 *	finds first bit starting at high-order bit
 *
 *	We store bits left-to-right
 *		bit 31 is policy (NUM_POLICIES-1)
 *		bit 31-(NUM_POLICIES-1) is policy 0
 *	so that FFS will have as few bits to search as possible.
 */

#define	RUNQ_BIT_SET(bitmap, index) \
	(BIT_SET(bitmap, BITS_PER_BITMAP-NUM_POLICIES+(index)))
#define	RUNQ_BIT_CLEAR(bitmap, index) \
	(BIT_CLEAR(bitmap, BITS_PER_BITMAP-NUM_POLICIES+(index)))
#define	RUNQ_BIT_FIND(bitmap, index) \
    MACRO_BEGIN \
	(index) = NUM_POLICIES-1-BIT_FIND_HIGH(bitmap); \
    MACRO_END

#endif	/* BIT_FIND_HIGH */

#if	!defined(BIT_FIND_LOW) && !defined(BIT_FIND_HIGH)

/*
 *	Machine has no FFS.
 *
 *	We store bits right-to-left:
 *		bit 0 is policy NUM_POLICIES-1
 *		bit NUM_POLICIES-1 is policy 0
 *	so that FFS will have as few bits to search as possible.
 */

#define	RUNQ_BIT_SET(bitmap, index) \
	((bitmap) |= (1 << (NUM_POLICIES-1-(index))))
#define	RUNQ_BIT_CLEAR(bitmap, index) \
	((bitmap) &=~(1 << (NUM_POLICIES-1-(index))))
#define	RUNQ_BIT_FIND(bitmap, index) \
    MACRO_BEGIN \
        unsigned int	temp = (bitmap); \
	(index) = NUM_POLICIES-1; \
	while (((temp) & 0x1) == 0) \
	    (temp) >>= 1, (index)--; \
    MACRO_END

#endif	/* !defined(BIT_FIND_LOW) && !defined(BIT_FIND_HIGH) */

#endif	/* _KERN_RUNQ_BITMAP_H_ */

