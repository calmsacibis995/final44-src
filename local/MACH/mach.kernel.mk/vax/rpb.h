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
 * $Log:	rpb.h,v $
 * Revision 2.3  89/03/09  22:21:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:28:07  gm0w
 * 	Changes for cleanup.
 * 
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)rpb.h	7.1 (Berkeley) 6/5/86
 */

/*
 * The restart parameter block, which is a page in (very) low
 * core which runs after a crash.  Currently, the restart
 * procedure takes a dump.
 */
struct rpb {
	struct	rpb *rp_selfref;	/* self-reference */
	int	(*rp_dumprout)();	/* routine to be called */
	long	rp_checksum;		/* checksum of 31 words of dumprout */
	long	rp_flag;		/* set to 1 when dumprout runs */
/* the dump stack grows from the end of the rpb page not to reach here */
};
#ifdef	KERNEL
extern	struct rpb rpb;
#endif
