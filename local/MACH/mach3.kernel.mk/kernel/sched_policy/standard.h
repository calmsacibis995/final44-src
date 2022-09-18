/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	standard.h,v $
 * Revision 2.2  93/11/17  18:38:33  dbg
 * 	Created.
 * 	[93/09/03  15:42:52  dbg]
 * 
 */

#ifndef	_SCHED_POLICY_STANDARD_H_
#define	_SCHED_POLICY_STANDARD_H_

/*
 *	Standard Mach scheduling policies:
 *
 *	fixed priority
 *	timesharing
 *	background
 */

#include <kern/sched_policy.h>

extern struct sched_policy	bg_sched_policy,
				ts_sched_policy,
				fp_sched_policy;

/*
 *	Base priority for timesharing policy.
 */
#define	TS_BASEPRI_USER		12

/*
 *	Base priority for fixed-priority policy.
 */
#define	FP_BASEPRI_USER		31
#define	FP_BASEPRI_SYSTEM	12	/* XXX */

#endif	/* _SCHED_POLICY_STANDARD_H_ */
