/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pr_dblbuf.h,v $
 * Revision 2.4  89/03/09  20:57:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:21  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pr_dblbuf.h 1.2 87/01/08 SMI	*/

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	PR_DBLBUF_H_
#define PR_DBLBUF_H_

/* Attributes
   Unless otherwise indicated, attributes can be used for gets and sets.
*/


#define PR_DBL_AVAIL	1	/* AVAIL is get only. */
#define PR_DBL_DISPLAY	2
#define PR_DBL_WRITE	3
#define PR_DBL_READ	4
#define PR_DBL_DISPLAY_DONTBLOCK	5
    /* Similar to PR_DBL_DISPLAY, but DONTBLOCK is for set only. */


/* Attribute values:
*/

#define PR_DBL_EXISTS	1	/* Value for AVAIL only */
#define PR_DBL_A	2
#define PR_DBL_B	3
#define PR_DBL_BOTH	4	/* for PR_DBL_WRITE only. */
#define PR_DBL_NONE	5
    /* can only be returned by pr_dbl_get with PR_DBL_WRITE attribute. */

#endif	PR_DBLBUF_H_
