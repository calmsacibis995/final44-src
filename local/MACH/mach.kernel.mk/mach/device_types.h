/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	device_types.h,v $
 * Revision 2.4  89/03/09  20:19:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:13:13  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/15  16:29:33  rpd
 * 	Moved from kern/ to mach/.
 * 	[89/01/15  14:34:58  rpd]
 * 
 * Revision 2.2  89/01/12  11:14:32  rpd
 * 	Created.
 * 	[89/01/12  11:13:03  rpd]
 * 
 */
/*
 *	Mach kernel device interface type declarations
 *
 */

#ifndef	_MACH_DEVICE_TYPES_H_
#define _MACH_DEVICE_TYPES_H_

typedef char		* io_buf_t;	
typedef io_buf_t	* io_buf_ptr_t;

#endif	_MACH_DEVICE_TYPES_H_
