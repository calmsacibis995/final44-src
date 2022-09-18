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
 * $Log:	mach_timer.h,v $
 * Revision 2.2  94/12/16  10:55:18  dbg
 * 	Renamed to 'mach_timer.h'.  Renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:48:46  dbg
 * 	Changed 'flags' to 'overruns'.
 * 	[93/05/06            dbg]
 * 
 * 	64 bit cleanup.
 * 	[93/02/19            dbg]
 * 
 * 	Fixed to put in kernel.  Based on kernel timer elements.
 * 
 * 	Changed time_values_t to time_spec_t to account for timer hardware skew.
 * 	[92/07/18	savage]
 * 	Redefined timer structure for user exportation.  Forced to define
 * 	it as mach_timer_t instead of timer_t...  I'd love to change timer_t
 * 	into counter_t but I'm sure the political headache isn't worth it.
 * 	[92/06/12	savage]
 * 	changed locks to work on multiprocessor (one hopes...)
 * 	[92/06/10]	savage]
 * 	Created
 * 	[92/05/01	savage]
 * 
 */

/*
 *	File:		mach/timer.h
 *	Authors:	Stefan Savage and David Golub, 1992
 *
 *	Definitions of the exported timer interface and
 *	data structures.
 */

#ifndef	_MACH_TIMER_H_
#define _MACH_TIMER_H_

#include <mach/timespec.h>
#include <mach/boolean.h>
#include <mach/message.h>

/*
 *	Timers are identified by ports externally.
 */
#ifndef	KERNEL
typedef mach_port_t	mach_timer_t;
#endif

/*
 *	Flags to timer calls:
 */
#define TIMER_ABSOLUTE		0x01	/* expiration time is absolute */
#define TIMER_PERIODIC		0x02	/* timer is periodic */
#define TIMER_THREAD_SUSPEND	0x04	/* suspend thread when timer expires */
#define TIMER_EVENT		0x08	/* signal event when timer expires */

/*
 *	A timer sends an expiration message when the time is up.
 *	This message can be interpreted directly, or received
 *	through the 'timer_expire' interface.
 */

struct timer_expire_message {
	mach_msg_header_t	Head;
	mach_msg_type_t		timeType;
	timespec_t		time;
};

typedef struct timer_expire_message	*timer_expire_message_t;
typedef struct timer_expire_message	timer_expire_message_data_t;

/*
 *	Information that can be requested about timers.
 */
typedef natural_t	*mach_timer_info_t;

/*
 *	Basic timer information:
 */
#define MACH_TIMER_BASIC_INFO	1
struct mach_timer_basic_info {
	natural_t	type;		/* message | event | suspend,
					   periodic */
	timespec_t	expire_time;	/* expiration time */
	timespec_t	interval_time;	/* period, for periodic timers */
	natural_t	event;		/* event ID if assigned */
	natural_t	overruns;	/* how many times a periodic
					   timer has expired and failed
					   to deliver a message to a
					   full port */
	/* boolean_t */
	    natural_t	enqueued;	/* is timer on queue? */
};

typedef struct mach_timer_basic_info	*mach_timer_basic_info_t;
typedef struct mach_timer_basic_info	mach_timer_basic_info_data_t;

#define MACH_TIMER_BASIC_INFO_COUNT	\
		(sizeof(mach_timer_basic_info_data_t) / sizeof(natural_t))

#endif	/* _MACH_TIMER_H_ */

