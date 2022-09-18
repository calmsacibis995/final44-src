/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	trap.h,v $
 * Revision 2.2  90/10/25  14:49:22  rwd
 * 	Added watchpoint support.
 * 	[90/10/18            rpd]
 * 
 * Revision 2.1  89/08/03  16:24:10  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

#ifndef	_VAX_TRAP_H_
#define	_VAX_TRAP_H_

/*
 *	Trap numbers for VAX exceptions.
 *
 *	We use the standard exception codes for those exceptions that
 *	are visible to the user.  We use negative numbers for the
 *	rest, assuming that exception codes are positive.
 */

#include <mach/exception.h>

#define	T_ASTFLT	0		/* when nothing else happens */
#define	T_KDB_ENTRY	(-1)		/* entry to kernel debugger */
#define T_WATCHPOINT	(-2)		/* hit a watchpoint */

#endif	_VAX_TRAP_H_
