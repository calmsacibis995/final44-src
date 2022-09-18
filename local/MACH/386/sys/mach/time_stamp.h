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
 * $Log:	time_stamp.h,v $
 * Revision 2.7  89/03/10  13:33:55  rpd
 * 	Moved the machine-dependent file to mach/machine/.
 * 
 * Revision 2.6  89/03/10  02:08:20  rpd
 * 	Moved from kern/.
 * 
 * Revision 2.5  89/03/09  20:17:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:10:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  01:06:01  mwyoung
 * Relocated from sys/time_stamp.h
 * 
 * Revision 2.2  88/08/24  02:48:50  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:25:27  mwyoung]
 *
 *  5-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Isolate machine dependencies - machine/time_stamp chooses a
 *	TS_FORMAT, if not choosed this module defaults it to 1.  Also
 *	guarded against multiple inclusion.
 *
 * 30-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Created.
 *
 */ 

#ifndef	_MACH_TIME_STAMP_H_
#define _MACH_TIME_STAMP_H_

#include <mach/machine/time_stamp.h>

/*
 *	time_stamp.h -- definitions for low-overhead timestamps.
 */

struct tsval {
	unsigned	low_val;	/* least significant word */
	unsigned	high_val;	/* most significant word */
};

/*
 *	Format definitions.
 */

#ifndef	TS_FORMAT
/*
 *	Default case - Just return a tick count for machines that
 *	don't support or haven't implemented this.  Assume 100Hz ticks.
 *
 *	low_val - Always 0.
 *	high_val - tick count.
 */
#define TS_FORMAT	1

#ifdef	KERNEL
extern unsigned	ts_tick_count;
#endif	KERNEL
#endif	TS_FORMAT

/*
 *	List of all format definitions for convert_ts_to_tv.
 */

#define TS_FORMAT_DEFAULT	1
#define TS_FORMAT_MMAX		2

#endif	_MACH_TIME_STAMP_H_
