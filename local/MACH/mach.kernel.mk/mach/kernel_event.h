/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kernel_event.h,v $
 * Revision 2.3  89/10/15  02:05:36  rpd
 * 	Minor cleanups.
 * 
 * Revision 2.2  89/10/11  14:37:21  dlb
 * 	Add constants from kern_mon_param.h. Cleanup.
 * 	[89/08/02            dlb]
 * 
 * 	Added the kern_mon_data_t and kern_mon_buffer_t types for the
 * 	structure.
 * 	[89/02/16            tfl]
 * 
 * Revision 2.1.1.2  89/08/02  23:44:50  dlb
 * 	Add constants from kern_mon_param.h. Cleanup.
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.1  89/07/26  12:04:21  dlb
 * 	Added the kern_mon_data_t and kern_mon_buffer_t types for the
 * 	structure.
 * 	[89/02/16            tfl]
 * 
 * 	Created.
 * 	[88/04/15            tfl]
 * 
 */
/*
 *	File:	kernel_event.h
 *	Author:	Ted Lehr
 *
 *	Copyright (C) 1987, Ted Lehr
 *
 * 	Kernel Monitoring header file to be exported to user.  Contains
 *	the the definition of a kernel event.  
 *
 */

#ifndef _MACH_KERNEL_EVENT_H_
#define _MACH_KERNEL_EVENT_H_

/*
 * The kern_mon_data_t and kern_mon_buffer_t are used by MIG
 * to generate the interfaces correctly.  They are not
 * "necessary" but fulfill stylistic conventions.
 */

typedef
struct 	kernel_event {	/* unit kernel event */
	 unsigned 	event_type;	 /* the type of kernel event	*/
	 unsigned	first_element;	 /* the stopped thread 		*/
	 unsigned	second_element;  /* the started thread 		*/
	 unsigned	third_element;   /* flag and cpu number 	*/
	 unsigned 	hi_time;         /* hi time stamp 		*/
	 unsigned 	lo_time;         /* lo time stamp 		*/
} kern_mon_event, *kern_mon_event_t, kern_mon_data_t, *kern_mon_buffer_t;

#define MONITOR_MIG_BUF_SIZE    320             /* ONLY allowable size of   *
						 * buffer passed to monitor *
						 * calls                    */


/***************************************************************************
 *
 *	Kernel Sensor types:
 */
#define MONITOR_CNTXT_SWTCH	0x0;

#endif _MACH_KERNEL_EVENT_H_
