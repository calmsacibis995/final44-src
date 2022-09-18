/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	thread_status.h,v $
 * Revision 2.4  93/01/14  17:48:44  danner
 * 	Standardized include symbol name.
 * 	[92/06/10            pds]
 * 
 * Revision 2.3  91/05/14  17:02:17  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/02/05  17:37:11  mrt
 * 	Moved vax_saved_state to vax/thread.h.  Left only user-visible
 * 	definitions in this file.
 * 	[89/03/02            dbg]
 * 
 * Revision 2.1  89/08/03  16:01:38  rwd
 * Created.
 * 
 * Revision 2.3  89/02/25  18:42:01  gm0w
 * 	Changes for cleanup.
 * 
 * 28-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added flavor code for new thread_status interface.
 *
 * 27-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	mach/vax/thread_status.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1985
 *
 *	This file contains the structure definitions for the thread
 *	state as applied to VAX processors.
 */

#ifndef	_MACH_VAX_THREAD_STATUS_H_
#define	_MACH_VAX_THREAD_STATUS_H_

/*
 *	vax_thread_state	this is the structure that is exported
 *				to user threads for use in status/mutate
 *				calls.  This structure should never
 *				change.
 */
#define	VAX_THREAD_STATE	(1)
				/* only one set of registers */

struct vax_thread_state {
	int	r0;		/* general registers */
	int	r1;
	int	r2;
	int	r3;
	int	r4;
	int	r5;
	int	r6;
	int	r7;
	int	r8;
	int	r9;
	int	r10;
	int	r11;
	int	ap;		/* user's arg pointer */
	int	fp;		/* user's frame pointer */
	int	sp;		/* user's stack pointer */
	int	pc;		/* user's program counter */
	int	ps;		/* user's processor status longword */
};

#define	VAX_THREAD_STATE_COUNT	(sizeof(struct vax_thread_state)/sizeof(int))

#endif	/* _MACH_VAX_THREAD_STATUS_H_ */
