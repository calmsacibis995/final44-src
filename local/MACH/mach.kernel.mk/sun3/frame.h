/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	frame.h,v $
 * Revision 2.2  89/02/25  19:34:11  gm0w
 * 	Changes for cleanup.
 * 
 */

/*	@(#)frame.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

/*
 * Definition of the sun stack frame
 */
struct frame {
	struct frame	*fr_savfp;	/* saved frame pointer */
	int	fr_savpc;		/* saved program counter */
	int	fr_arg[1];		/* array of arguments */
};
