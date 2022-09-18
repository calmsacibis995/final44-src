/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	af.h,v $
 * Revision 2.4  89/03/09  20:38:25  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:53:30  gm0w
 * 	Changed to new copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  89/01/23  22:19:39  af
 * 	Made the afswitch[] decl an extern one, to satisfy the Mips
 * 	compiler.
 * 	[89/01/05            af]
 * 
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)af.h	7.1 (Berkeley) 6/4/86
 */

/*
 * Address family routines,
 * used in handling generic sockaddr structures.
 *
 * Hash routine is called
 *	af_hash(addr, h);
 *	struct sockaddr *addr; struct afhash *h;
 * producing an afhash structure for addr.
 *
 * Netmatch routine is called
 *	af_netmatch(addr1, addr2);
 * where addr1 and addr2 are sockaddr *.  Returns 1 if network
 * values match, 0 otherwise.
 */
struct afswitch {
	int	(*af_hash)();
	int	(*af_netmatch)();
};

struct afhash {
	u_int	afh_hosthash;
	u_int	afh_nethash;
};

#ifdef	KERNEL
extern struct	afswitch afswitch[];
#endif
