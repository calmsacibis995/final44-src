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
 * $Log:	mach_param.h,v $
 * Revision 2.9  89/03/10  01:59:14  rpd
 * 	Moved TASK_MAX, PORT_MAX, etc. here from mach/mach_param.h.
 * 
 * Revision 2.8  89/03/10  01:29:57  rpd
 * 	More cleanup.
 * 
 */
/*
 *	File:	kern/mach_param.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Mach system sizing parameters
 *
 */

#ifndef	_KERN_MACH_PARAM_H_
#define _KERN_MACH_PARAM_H_

#include <mach_np.h>

#include <mach/mach_param.h>		/* for backwards compatibility */

#define THREAD_MAX	1024		/* Max number of threads */
#define THREAD_CHUNK	64		/* Allocation chunk */

#define TASK_MAX	1024		/* Max number of tasks */
#define TASK_CHUNK	64		/* Allocation chunk */

#define PORT_MAX	((TASK_MAX * 3 + THREAD_MAX)	/* kernel */ \
				+ (THREAD_MAX * 2)	/* user */ \
				+ 20000)		/* slop for objects */
					/* Number of ports, system-wide */

#define SET_MAX		(TASK_MAX + THREAD_MAX + 200)
					/* Max number of port sets */

#if	MACH_NP
#define KERN_MSG_SMALL_SIZE	256	/* Size of small kernel message */
#else	MACH_NP
#define KERN_MSG_SMALL_SIZE	128	/* Size of small kernel message */
#endif	MACH_NP

#endif	_KERN_MACH_PARAM_H_
