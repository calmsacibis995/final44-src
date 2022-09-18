/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	policy.h,v $
 * Revision 2.3  89/10/15  02:05:50  rpd
 * 	Minor cleanups.
 * 
 * Revision 2.2  89/10/11  14:40:53  dlb
 * 	Cleanup changes.
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.2  89/08/02  23:12:03  dlb
 * 	Cleanup changes.
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.1  89/07/25  18:47:00  dlb
 * 	Created.
 * 
 */

#ifndef	_MACH_POLICY_H_
#define _MACH_POLICY_H_

/*
 *	mach/policy.h
 *
 *	Definitions for scheduing policy.
 */

/*
 *	Policy definitions.  Policies must be powers of 2.
 */
#define	POLICY_TIMESHARE	1
#define POLICY_FIXEDPRI		2
#define POLICY_LAST		2

#define invalid_policy(policy)	(((policy) <= 0) || ((policy) > POLICY_LAST))

#endif _MACH_POLICY_H_
