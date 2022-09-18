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
 * $Log:	time_stamp.c,v $
 * Revision 2.4  89/03/10  02:11:06  rpd
 * 	Moved kern/time_stamp.h to mach/.
 * 
 * Revision 2.3  89/03/09  20:17:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:10:29  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Jun-87  David Black (dlb) at Carnegie-Mellon University
 *	machtimer.h --> timer.h  Changed to cpp symbols for multimax.
 *
 *  5-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	ts.h -> time_stamp.h
 *
 * 30-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Created.
 */ 

#include <mach/kern_return.h>
#include <mach/time_stamp.h>

/*
 *	ts.c - kern_timestamp system call.
 */

#ifdef	multimax
#include <mmax/timer.h>
#endif	multimax

unsigned ts_tick_count;

kern_return_t
kern_timestamp(tsp)
struct	tsval	*tsp;
{
	struct	tsval	temp;
#ifdef	multimax
	temp.low_val = FRcounter;
	temp.high_val = 0;
#else	multimax
	temp.low_val = 0;
	temp.high_val = ts_tick_count;
#endif	multimax

	if (copyout(&temp, tsp, sizeof(struct tsval)) != KERN_SUCCESS)
		return(KERN_INVALID_ADDRESS);
	return(KERN_SUCCESS);
}

/*
 *	Initialization procedure.
 */

timestamp_init()
{
#ifdef	multimax
#else	multimax
	ts_tick_count = 0;
#endif	multimax
}
