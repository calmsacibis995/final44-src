/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992 Carnegie Mellon University
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
 * $Log:	timespec.h,v $
 * Revision 2.2  94/12/16  10:57:08  dbg
 * 	RT-MACH integration: renamed time_spec_t to timespec_t (ignoring
 * 	POSIX incompatibility issues).  Renamed timespec_leq to
 * 	timespec_le; added timespec_ge, timespec_min, timespec_max.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:48:14  dbg
 * 	Added time_spec_infinite, time_spec_set_infinite.
 * 	[93/05/12            dbg]
 * 
 * 	Added mapped_time_spec_read.
 * 	[93/03/26            dbg]
 * 
 * 	64 bit cleanup.
 * 	[93/02/19            dbg]
 * 
 * 	Merged into microkernel mainline.
 * 
 * 	Created
 * 	[92/07/02	savage]
 * 
 */

/*
 *	Type definitions to measure time in seconds and nanoseconds.
 *
 *	Authors:	Stefan Savage and David Golub, 1992
 */

#ifndef _MACH_TIMESPEC_H_
#define _MACH_TIMESPEC_H_

#include <mach/machine/vm_types.h>

/*
 *	Time values are represented as seconds and nanoseconds.
 *	Both fields are unsigned.
 */
struct timespec {
	natural_t	seconds;
	natural_t	nanoseconds;
};
typedef struct timespec		timespec_t;

/*
 *	Time value available by mapping time.
 *	This contains a check field to allow
 *	asynchronous updates.
 */
struct mapped_timespec {
	volatile natural_t	seconds;
	volatile natural_t	nanoseconds;
	volatile natural_t	check_seconds;
};
typedef struct mapped_timespec	mapped_timespec_t;

/*
 *	void mapped_timespec_read(timespec_t&		result,
 *				  mapped_timespec_t *	mtime)
 *
 *	Read the mapped timespec value and produce a
 *	consistent time reading.
 *
 *	Results are passed by lvalue.
 */
#define	mapped_timespec_read(result, mtime) \
	do { \
		(result).seconds = (mtime)->seconds; \
		(result).nanoseconds = (mtime)->nanoseconds; \
	} while ((result).seconds != (mtime)->check_seconds)

/*
 *	Macros to manipulate time values.
 *	Assume that all time values are normalized
 *	(nanoseconds <= 999,999,999).
 *
 *	Results are passed by lvalue.
 */
#define NANOSEC_PER_SEC		(1000000000)

/*
 *	void timespec_add_nsec(timespec_t&  result,
 *			       unsigned int nanosec)
 *
 *	Add number of nanoseconds to a time value.
 */
#define	timespec_add_nsec(result, nanosec)				\
    (									\
      (void)(								\
	(((result).nanoseconds += (nanosec)) >= NANOSEC_PER_SEC)	\
	&& (								\
	    (result).nanoseconds -= NANOSEC_PER_SEC,			\
	    (result).seconds++						\
	)								\
      )									\
    )

/*
 *	void timespec_add(timespec_t& result,
 *			  timespec_t  addend)
 *
 *	Add addend to result.
 */
#define timespec_add(result, addend)					\
    (									\
      (void)(								\
	(result).seconds += (addend).seconds,				\
	(((result).nanoseconds += (addend).nanoseconds)			\
	 >= NANOSEC_PER_SEC)						\
	&& (								\
	    (result).nanoseconds -= NANOSEC_PER_SEC,			\
	    (result).seconds++						\
	)								\
      )									\
    )

/*
 *	void timespec_subtract(timespec_t& result,
 *			       timespec_t  minuend)
 *
 *	Subtract minuend from result.
 */
#define timespec_subtract(result, minuend)				\
    (									\
      (void)(								\
	/*								\
	 *	Use comparison - fields are unsigned.			\
	 */								\
	(((result).nanoseconds < (minuend).nanoseconds)			\
	&& (								\
	    (result).nanoseconds += NANOSEC_PER_SEC,			\
	    (result).seconds--						\
	)),								\
	(result).nanoseconds -= (minuend).nanoseconds,			\
	(result).seconds -= (minuend).seconds				\
      )									\
    )

/*
 *	void timespec_set(timespec_t& time,
 *			  timespec_t  newtime)
 *
 *	Set time to newtime.
 */
#define timespec_set(time, newtime)					\
    (									\
	(time).seconds = (newtime).seconds,				\
	(time).nanoseconds = (newtime).nanoseconds			\
    )

/*
 *	boolean_t timespec_lt(timespec_t time1,
 *			      timespec_t time2)
 *
 *	Return TRUE if time1 < time2.
 */
#define timespec_lt(time1, time2)					\
	((time1).seconds < (time2).seconds ||				\
	    ((time1).seconds == (time2).seconds &&			\
	     (time1).nanoseconds < (time2).nanoseconds))

/*
 *	boolean_t timespec_le(timespec_t time1,
 *			      timespec_t time2)
 *
 *	Return TRUE if time1 <= time2.
 */
#define timespec_le(time1, time2)					\
	((time1).seconds < (time2).seconds ||				\
	    ((time1).seconds == (time2).seconds &&			\
	     (time1).nanoseconds <= (time2).nanoseconds))


/*
 *	boolean_t timespec_gt(timespec_t time1,
 *			      timespec_t time2)
 *
 *	Return TRUE if time1 > time2.
 */
#define timespec_gt(time1, time2)					\
	((time1).seconds > (time2).seconds ||				\
	    ((time1).seconds == (time2).seconds &&			\
	     (time1).nanoseconds > (time2).nanoseconds))

/*
 *	boolean_t timespec_ge(timespec_t time1,
 *			      timespec_t time2)
 *
 *	Return TRUE if time1 >= time2.
 */
#define timespec_ge(time1, time2)					\
	((time1).seconds > (time2).seconds ||				\
	    ((time1).seconds == (time2).seconds &&			\
	     (time1).nanoseconds >= (time2).nanoseconds))


/*
 *	timespec_t timespec_min(timespec_t time1,
 *				timespec_t time2)
 *
 *	Returns the earlier of time1 or time2.
 */
#define timespec_min(time1, time2)					\
	(timespec_le((time1),(time2)) ? (time1) : (time2))	

/*
 *	timespec_t timespec_man(timespec_t time1,
 *				timespec_t time2)
 *
 *	Returns the later of time1 or time2.
 */
#define timespec_max(time1, time2)					\
	(timespec_ge((time1),(time2)) ? (time1) : (time2))	

/*
 *	void timespec_set_infinite(timespec_t& time)
 *
 *	Set time to an "infinite" value.  Infinity
 *	is used to denote no time for periodic timers.
 */
#define timespec_set_infinite(time)					\
    (									\
	(time).seconds = ~0,						\
	(time).nanoseconds = NANOSEC_PER_SEC - 1			\
    )

/*
 *	boolean_t timespec_infinite(timespec_t time)
 *
 *	Return TRUE if timespec is "infinite".
 */
#define	timespec_infinite(time)						\
	((time).seconds == ~0 &&					\
	 (time).nanoseconds == NANOSEC_PER_SEC - 1)

/*
 *	boolean_t timespec_nonzero(timespec_t time)
 *
 *	Return TRUE if timespec is not zero.
 */
#define timespec_nonzero(time)						\
	((time).nanoseconds || (time).seconds)

/*
 *	boolean_t timespec_valid(timespec_t time)
 *
 *	Return TRUE if time is a valid time representation.
 */
#define timespec_valid(time)						\
	((time).nanoseconds < NANOSEC_PER_SEC)

#endif	/* _MACH_TIMESPEC_H_ */
