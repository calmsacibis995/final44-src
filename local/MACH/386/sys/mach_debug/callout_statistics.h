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
 * $Log:	callout_statistics.h,v $
 * Revision 2.4  89/03/09  20:26:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:43:24  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/12  07:59:40  rpd
 * 	Created.
 * 	[89/01/12  04:22:24  rpd]
 * 
 */ 

#ifndef	_MACH_DEBUG_CALLOUT_STATISTICS_H_
#define _MACH_DEBUG_CALLOUT_STATISTICS_H_

/*
 *	Remember to update the mig type definition
 *	in mach_debug_types.defs when adding/removing fields.
 */

typedef struct callout_info {
	int	coi_time;
	char	*coi_arg;
	int	(*coi_func)();
} callout_info_t;

typedef callout_info_t *callout_info_array_t;


/*
 *	Remember to update the mig type definition
 *	in mach_debug_types.defs when adding/removing fields.
 */

typedef struct callout_statistics {
	int	cos_current_size;	/* current length of the queue */

	int	cos_num_timeout;	/* number of times timeout called */
	int	cos_cum_timeout_size;	/* cum. size when timeout called */
	int	cos_cum_timeout_pos;	/* cum. position of new event */

	int	cos_num_untimeout;	/* number of times untimeout called */
	int	cos_num_untimeout_hit;	/* num. times found an event */
	int	cos_cum_untimeout_size;	/* cum. size when untimeout called */
	int	cos_cum_untimeout_pos;	/* cum. position of old event */

	int	cos_num_softclock;	/* num. of events softclock removed */
	int	cos_cum_softclock_size;	/* cum. size when event removed */
} callout_statistics_t;

#ifdef	KERNEL
#include <mach_co_stats.h>

#if	MACH_CO_STATS
extern callout_statistics_t callout_statistics;
extern int callout_statistics_fudge;

#define callout_statistics_invariant()			\
((callout_statistics.cos_num_timeout -			\
  (callout_statistics.cos_num_softclock +		\
   callout_statistics.cos_num_untimeout_hit)) ==	\
 (callout_statistics.cos_current_size +			\
  callout_statistics_fudge))
#endif	MACH_CO_STATS

#endif	KERNEL
#endif	_MACH_DEBUG_CALLOUT_STATISTICS_H_
