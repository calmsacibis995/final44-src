/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	thread.h,v $
 * Revision 1.4.1.2  90/03/07  13:27:00  rvb
 * 	Make U_ADDRESS on by default.
 * 	[90/03/01            rvb]
 * 
 * Revision 1.4.1.1  89/11/21  12:45:33  rvb
 * 	NOTE: on the T5200 this optimization is detremental (to getpid())
 * 	but generally it is a win, so it is conditonal on NO_U_ADDRESS
 * 	Rather than have "u" expand to current_thread()->u_address, have
 * 	it expand to the constant U_ADDRESS which is updated by load_context
 * 	when the thread changes.  If "u" is defined then user.h won't define
 * 	it.
 * 	[88/01/25            rvb]
 * 
 * 	NO! NO! NO!
 * 	We are not a VAX; we don't get our current_thread from the
 * 	supervisor stack pointer!
 * 	[89/11/10            rvb]
 * 
 * Revision 1.4  89/03/09  20:04:15  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:34:30  gm0w
 * 	Changes for cleanup.
 * 
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created by defining CURRENT_THREAD.
 *
 */

/*
 *
 *	File:	thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	This file defines machine specific, thread related structures,
 *	variables and macros.
 *
 */

#ifndef	_I386_THREAD_
#define _I386_THREAD_

#ifndef	NO_U_ADDRESS
extern	struct	u_address	U_ADDRESS;
#define u			U_ADDRESS
#endif	NO_U_ADDRESS

#endif	_I386_THREAD_
