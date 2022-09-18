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
 * $Log:	thread_status.h,v $
 * Revision 2.6  89/03/10  02:24:31  rpd
 * 	Get FP stuff from mach/sun3/reg.h instead of sun3/reg.h.
 * 
 * Revision 2.5  89/03/09  20:23:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:40:50  gm0w
 * 	Changes for cleanup.
 * 
 *  2-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Stack format fields must be unsigned.  Apparently sun cc treats
 *	all (?) bit fields as unsigned.
 *
 * 28-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added floating-point registers.  Broke into several pieces for
 *	new thread-status interface.
 *
 * 21-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Cloned from Vax version.
 *
 * 27-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	mach/sun3/thread_status.h
 *	Author:	Avadis Tevanian, Jr.
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for the thread
 *	state as applied to SUN processors (mc68020).
 *
 */

#ifndef	_MACH_SUN3_THREAD_STATUS_H_
#define _MACH_SUN3_THREAD_STATUS_H_

#include <mach/sun3/reg.h>		/* FP declarations */

/*
 *	Two structures are defined:
 *
 *	sun_thread_state	this is the structure that is exported
 *				to user threads for use in status/mutate
 *				calls.  This structure should never
 *				change.
 *
 *	sun_saved_state		this structure corresponds to the state
 *				of the user registers as saved on the
 *				stack upon kernel entry.  This structure
 *				is used internally only.  Since this
 *				structure may change from version to
 *				version, it is hidden from the user.
 */

#define SUN_THREAD_STATE_REGS	1

struct sun_thread_state {
	int	d0;		/* data registers */
	int	d1;
	int	d2;
	int	d3;
	int	d4;
	int	d5;
	int	d6;
	int	d7;
	int	a0;		/* address registers */
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
	int	sp;		/* user's stack pointer */
	int	pc;		/* user's program counter */
	int	sr;		/* user's status register */
	struct fp_status fp;	/* floating point registers/status */
};
#define SUN_THREAD_STATE_REGS_COUNT \
			(sizeof(struct sun_thread_state) / sizeof(int))

/*
 *	Floating-point accelerator registers
 */
#define SUN_THREAD_STATE_FPA	2
/*
 *	structure is 'struct fpa_regs' in sun3/reg.h
 */
#define SUN_THREAD_STATE_FPA_COUNT \
			(sizeof(struct fpa_regs) / sizeof(int))

#ifdef	KERNEL
struct sun_saved_state {
	int	d0;		/* data registers */
	int	d1;
	int	d2;
	int	d3;
	int	d4;
	int	d5;
	int	d6;
	int	d7;
	int	a0;		/* address registers */
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
	int	sp;		/* user's stack pointer */
	int	sr;		/* user's status register */
	int	pc;		/* user's program counter */
	unsigned int	stkfmt	: 4;	/* rte stack frame format */
	unsigned int		: 2;
	unsigned int	vector	: 10;	/* vector number */
};

#define USER_REGS(thread)	((thread)->pcb->user_regs)

#endif	KERNEL
/*
 *	The saved floating-point registers are found in the PCB.
 */

#endif	_MACH_SUN3_THREAD_STATUS_H_
