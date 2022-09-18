/* 
 * Mach Operating System
 * Copyright (c) 1994,1993 Carnegie Mellon University
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
 * $Log:	realtime_policy.h,v $
 * Revision 2.3  94/12/16  10:56:38  dbg
 * 	RT-MACH merge: renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:46:32  dbg
 * 	Made policy_param_realtime always include start_time and
 * 	start_when.
 * 	[93/06/21            dbg]
 * 
 * 	Now has just real-time thread attributes.
 * 	[93/03/31            dbg]
 * 
 * 	Removed task_attributes.
 * 	[93/03/26            dbg]
 * 
 * 	Included extended rt_thread attributes.
 * 	[93/03/24            dbg]
 * 
 * 	64 bit cleanup.
 * 	[93/02/19            dbg]
 * 
 * 	Pulled together from pset_attributes.h, task_attributes.h,
 * 	thread_attributes.h.
 * 	[93/02/04            dbg]
 * 
 */

/*
 *	Real-time scheduling policies and parameters.
 */

#ifndef	_MACH_REALTIME_POLICY_H_
#define	_MACH_REALTIME_POLICY_H_

#include <mach/boolean.h>
#include <mach/timespec.h>
#include <mach/policy.h>

#define	POLICY_RATE_MONOTONIC		3
#define	POLICY_DEADLINE_MONOTONIC	4
#define	POLICY_EARLIEST_DEADLINE_FIRST	5

struct policy_param_realtime {
	timespec_t	start_time;
	natural_t	start_when;
	timespec_t	period;
	timespec_t	deadline;
};
typedef	struct policy_param_realtime	policy_param_realtime_t;

#define POLICY_PARAM_REALTIME_COUNT \
	(sizeof(struct policy_param_realtime) / sizeof(natural_t))

/*
 *	Values for start_when:
 */
#define	START_TIME_ABSOLUTE	0	/* start time is absolute */
#define	START_TIME_RELATIVE	1	/* start time is relative to
					   current time */
#define	START_TIME_NO_CHANGE	2	/* use current start time -
					   just change period and deadline */

#endif	/* _MACH_REALTIME_POLICY_H_ */
