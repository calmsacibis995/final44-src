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
 * Revision 2.10  89/03/10  01:58:13  rpd
 * 	Moved TASK_MAX, PORT_MAX, etc. to kern/mach_param.h.
 * 
 * Revision 2.9  89/03/10  01:30:05  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/03/07  23:42:17  rpd
 * 	Moved KERNEL dependent constants to kern/mach_param.h.
 * 	Doubled TASK_MAX and THREAD_MAX, and adjusted
 * 	PORT_MAX and SET_MAX so that they are doubled too.
 * 
 * Revision 2.7  89/03/07  03:49:47  rpd
 * 	Moved to mach/.
 * 
 * Revision 2.6  89/02/25  18:06:05  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/07  01:03:02  mwyoung
 * Relocated from sys/mach_param.h
 * 
 * Revision 2.4  88/12/21  14:17:22  mja
 * 	Increased the number of PORT_MAX
 * 	[88/12/20  15:25:11  mrt]
 * 
 * Revision 2.3  88/08/24  02:33:34  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:16:09  mwyoung]
 * 
 * Revision 2.2  88/07/20  21:04:16  rpd
 *	Added definition of SET_MAX, the maximum number of sets allowed.
 * 
 * 19-Aug-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Made small kernel messages bigger under MACH_NP, because a lot
 *	of space is used by the netmsg header anyway.
 *
 * 14-Aug-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Reduced TASK_CHUNK and THREAD_CHUNK.
 *
 *  3-Mar-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added KERN_MSG_SMALL_SIZE.
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Calculate PORT_MAX as dependent upon TASK_MAX and THREAD_MAX.
 *
 * 21-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added PORT_BACKLOG_MAX.
 *
 * 21-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed number of registered ports, to make the task structure
 *	power-of-two sized.  Don't ask.
 *
 * 31-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added TASK_PORT_REGISTER_MAX.
 *
 * 10-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added port parameters.
 *
 *  8-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added number of ports definition.
 *
 * 24-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Increase TASK parameters.
 *
 * 29-Jan-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created
 *
 */
/*
 *	File:	mach/mach_param.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Mach system sizing parameters
 *
 */

#ifndef	_MACH_MACH_PARAM_H_
#define _MACH_MACH_PARAM_H_

#define PORT_BACKLOG_DEFAULT	5
#define PORT_BACKLOG_MAX	16

#define TASK_PORT_REGISTER_MAX	4	/* Number of "registered" ports */

#endif	_MACH_MACH_PARAM_H_
