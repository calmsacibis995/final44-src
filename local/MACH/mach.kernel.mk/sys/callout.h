/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	callout.h,v $
 * Revision 2.6  89/03/09  22:02:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:52:11  gm0w
 * 	Got rid of conditional on CMUCS and MACH and the code that
 * 	was defined for non-CMUCS case
 * 	[89/02/13            mrt]
 * 
 * Revision 2.4  89/01/15  16:33:36  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:14:27  rpd]
 * 
 * Revision 2.3  88/11/14  14:33:35  gm0w
 * 	Placed kernel includes under #ifdef KERNEL.
 * 	[88/11/14            gm0w]
 * 
 * Revision 2.2  88/09/25  22:15:52  rpd
 * 	Added copyright, includes, etc.
 * 	Declared variables extern when CMUCS.
 * 	[88/09/09  04:49:09  rpd]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)callout.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_CALLOUT_H_
#define _SYS_CALLOUT_H_

#include <sys/types.h>

/*
 * The callout structure is for
 * a routine arranging
 * to be called by the clock interrupt
 * (clock.c) with a specified argument,
 * in a specified amount of time.
 * Used, for example, to time tab
 * delays on typewriters.
 */

struct	callout {
	int	c_time;		/* incremental time */
	caddr_t	c_arg;		/* argument to routine */
	int	(*c_func)();	/* routine */
	struct	callout *c_next;
};

#ifdef	KERNEL
#include <kern/lock.h>

extern struct callout *callfree, *callout, calltodo;
extern int ncallout;
decl_simple_lock_data(extern,callout_lock)

#endif	KERNEL
#endif	_SYS_CALLOUT_H_
