/* 
 * Mach Operating System
 * Copyright (c) 1993,1992 Carnegie Mellon University
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
 * $Log:	clock_status.h,v $
 * Revision 2.2  93/11/17  16:30:42  dbg
 * 	Renamed to device/clock_status.h.
 * 	[93/06/02            dbg]
 * 
 * 	64 bit cleanup.
 * 	[93/02/19            dbg]
 * 
 * 	Moved kernel definitions to kern/clock.h.  Generalized
 * 	clockres_request_t to clock_resolution_t, to return
 * 	skew for devices with odd clock frequencies.
 * 
 * 	Created
 * 	[92/07/12	savage]
 * 
 */

/*
 *	Exported clock device abstraction.
 */
#ifndef	_DEVICE_CLOCK_STATUS_H_
#define _DEVICE_CLOCK_STATUS_H_

#include <mach/time_spec.h>
#include <device/device_types.h>

/*
 *	A clock exports three items of status:
 *	current time
 *	resolution
 *	correction factor
 */

/*
 *	Time is measured as a time_spec.
 */
#define CLOCK_TIME		1
#define	CLOCK_TIME_COUNT	(sizeof(time_spec_t) / sizeof(int))

/*
 *	Resolution is defined as the resolution of
 *	the clock, and an allowable skew from that resolution.
 */
struct clock_resolution {
	int		resolution;	/* in nsecs */
	int		skew;		/* in nsecs */
};
#define	CLOCK_RESOLUTION_COUNT	\
		(sizeof(clock_resolution_data_t) / sizeof(int))

#define CLOCK_RESOLUTION	2

typedef struct clock_resolution	clock_resolution_data_t;
typedef struct clock_resolution	*clock_resolution_t;

/*
 *	The clock correction factor is an increment
 *	to be added to the clock time every clock
 *	tick (every 'clock_resolution' nanoseconds),
 *	and the number of clock ticks over which it
 *	should be added.
 */
struct clock_correction {
	int		delta;		/* correction, in nanoseconds */
	int		count;		/* number of clock periods over
					   which correction is applied */
};
#define	CLOCK_CORRECTION_COUNT \
		(sizeof(clock_correction_data_t) / sizeof(int))

#define	CLOCK_CORRECTION	3

typedef	struct clock_correction	clock_correction_data_t;
typedef	struct clock_correction	*clock_correction_t;

#endif	/* _DEVICE_CLOCK_STATUS_H_ */








