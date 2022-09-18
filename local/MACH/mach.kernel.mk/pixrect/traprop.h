/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	traprop.h,v $
 * Revision 2.4  89/03/09  20:57:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:13:02  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)traprop.h 1.2 86/10/08 SMI	*/

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

#ifndef	TRAPROP_H_
#define TRAPROP_H_

struct pr_chain {
	struct pr_chain	*next;
	struct pr_size	size;		/* size of bounding box */
	int		*bits;		/* chain-encoding bits */
};

struct pr_fall {
	struct pr_pos	pos;		/* position of top of fall */
	struct pr_chain	*chain;		/* trajectory of fall */
};

struct pr_trap {
	struct pr_fall	*left, *right;	/* falls = left+right boundaries */
	int y0, y1;			/* top+bottom boundaries */
};

#endif	TRAPROP_H_
