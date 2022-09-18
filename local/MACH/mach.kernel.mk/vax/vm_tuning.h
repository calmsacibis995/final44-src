/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_tuning.h,v $
 * Revision 2.2  89/03/15  15:48:12  gm0w
 * 	Created.  Took a guess at a good inactive target.
 * 	[89/02/23            mwyoung]
 * 
 */
/*
 *	File:	vax/vm_tuning.h
 *
 *	VM tuning parameters for the Vax.
 */

#define	VM_PAGE_INACTIVE_TARGET(free)	(5 + (free) / 50)
