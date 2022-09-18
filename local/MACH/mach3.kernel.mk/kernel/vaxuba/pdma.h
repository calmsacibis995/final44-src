/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pdma.h,v $
 * Revision 2.3  91/05/14  17:47:15  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/13  06:08:31  af
 * 	Rid of the "CMU" conditional once and forall.
 * 	Fixed copyright notice.
 * 	[91/05/12  16:44:15  af]
 * 
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)pdma.h	7.1 (Berkeley) 6/5/86
 */

struct pdma {
	struct	dzdevice *p_addr;
	char	*p_mem;
	char	*p_end;
	int	p_arg;
	int	(*p_fcn)();
};
