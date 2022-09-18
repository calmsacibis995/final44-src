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
 * $Log:	thread.h,v $
 * Revision 2.3  89/03/09  22:21:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:29:05  gm0w
 * 	Changes for cleanup.
 * 
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created by defining CURRENT_THREAD.
 *
 */
/*
 *	File:	vax/thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	This file defines machine specific, thread related structures,
 *	variables and macros.
 */

#ifndef	_VAX_THREAD_
#define _VAX_THREAD_

/*
 *	The current_thread is saved in the VAX supervisor stack pointer,
 *	so signifiy that there is a machine specific way to get this.
 */
struct thread	*current_thread();	/* handled by inline */
#define CURRENT_THREAD

#endif	_VAX_THREAD_
