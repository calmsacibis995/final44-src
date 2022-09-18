/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	thread.h,v $
 * Revision 2.4  89/03/09  21:38:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:47:55  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Rather than have "u" expand to current_thread()->u_address, have
 *	it expand to the constant U_ADDRESS which is updated by load_context
 *	when the thread changes.  If "u" is defined then user.h won't define
 *	it.  U_ADDRESS is extern because when we are included by sys/thread.h
 *	u_address has not been defined yet.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created, no defintions here yet.
 *
 */
/*
 *	File:	sun3/thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	This file defines machine specific, thread related structures,
 *	variables and macros.
 */

#ifndef	SUN3_THREAD_H_
#define SUN3_THREAD_H_

#ifdef	KERNEL
extern	struct	u_address	U_ADDRESS;
#define u			U_ADDRESS
#endif	KERNEL

#endif	SUN3_THREAD_H_
