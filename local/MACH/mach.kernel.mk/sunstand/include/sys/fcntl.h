/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fcntl.h,v $
 * Revision 2.2  89/07/12  00:12:17  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)fcntl.h 1.6 88/02/08 SMI	*/

#ifndef _FCNTL_
#define _FCNTL_

#include <sys/fcntlcom.h>

#define	O_NDELAY	FNDELAY	/* Non-blocking I/O (4.2 style) */

#endif !_FCNTL_
