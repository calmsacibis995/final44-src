/* 
 * Mach Operating System
 * Copyright (c) 1993,1991 Carnegie Mellon University
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
 * $Log:	timer.h,v $
 * Revision 2.3  93/11/17  16:40:16  dbg
 * 	Added TIMER_TO_TIMESPEC.
 * 	[93/04/15            dbg]
 * 
 * 	Changed TIMER_RATE to USAGE_RATE.
 * 	[93/02/23            dbg]
 * 
 * Revision 2.2  91/07/31  17:41:51  dbg
 * 	Created.
 * 	[91/07/30  16:58:38  dbg]
 * 
 */

#ifndef	_I386_TIMER_H_
#define _I386_TIMER_H_

/*
 *	Machine dependent timer definitions.
 */

#include <platforms.h>

#ifdef	SYMMETRY

/*
 *	TIMER_MAX is not used on the Sequent because a 32-bit rollover
 *	timer does not need to be adjusted for maximum value.
 */

/*
 *	USAGE_RATE is the rate of the timer in ticks per second.
 *	It is used to calculate percent cpu usage.
 */

#define USAGE_RATE	1000000

/*
 *	TIMER_HIGH_UNIT is the unit for high_bits in terms of low_bits.
 *	Setting it to USAGE_RATE makes the high unit seconds.
 */

#define TIMER_HIGH_UNIT	USAGE_RATE

/*
 *	These routines convert the components of a timer
 *	to USAGE_RATE.
 *
 *	For the Sequent, since the low unit is microseconds,
 *	TIMER_LOW_TO_USAGE is the identity function.
 */
#define	TIMER_LOW_TO_USAGE(micros)	(micros)
#define	TIMER_HIGH_TO_USAGE(secs)	((secs)*TIMER_HIGH_UNIT)

/*
 *	TIMER_TO_TIMESPEC is used to adjust the value of a timer after
 *	it has been copied into a time_spec_t.
 *
 *	We convert the low word from microseconds to nanoseconds.
 *	The high word is already in seconds.
 *
 *	We normalize the result before conversion, since the
 *	multiplication may overflow 32 bits.
 */
#define	TIMER_TO_TIMESPEC(timer) \
	((timer)->high += (timer)->low / TIMER_HIGH_UNIT, \
	 (timer)->low = ((timer)->low % TIMER_HIGH_UNIT) * 1000)
	
/*
 *	MACHINE_TIMER_ROUTINES should be defined if the timer routines are
 *	implemented in machine-dependent code (e.g. assembly language).
 */
#define	MACHINE_TIMER_ROUTINES

#endif

#endif	/* _I386_TIMER_H_ */
