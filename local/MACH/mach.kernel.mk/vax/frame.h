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
 * $Log:	frame.h,v $
 * Revision 2.2  89/02/25  20:18:50  gm0w
 * 	Changes for cleanup.
 * 
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)frame.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Definition of the vax calls/callg frame.
 */
struct frame {
	int	fr_handler;
	u_int	fr_psw:16,		/* saved psw */
		fr_mask:12,		/* register save mask */
		:1,
		fr_s:1,			/* call was a calls, not callg */
		fr_spa:2;		/* stack pointer alignment */
	int	fr_savap;		/* saved arg pointer */
	int	fr_savfp;		/* saved frame pointer */
	int	fr_savpc;		/* saved program counter */
};
