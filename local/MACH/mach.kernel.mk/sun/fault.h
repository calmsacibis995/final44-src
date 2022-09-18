/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fault.h,v $
 * Revision 2.2  89/02/25  19:28:32  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)fault.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Where to go on fault in kernel mode
 * Zero means fault was unexpected
 */
label_t	*nofault;	/* longjmp vector */
