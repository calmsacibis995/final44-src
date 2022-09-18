/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sainet.h,v $
 * Revision 2.2  89/07/12  00:22:46  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)sainet.h 1.2 88/02/08 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Standalone Internet Protocol State
 */
struct sainet {
	struct in_addr    sain_myaddr;	/* my host address */
	struct ether_addr sain_myether;	/* my Ethernet address */
	struct in_addr    sain_hisaddr;	/* his host address */
	struct ether_addr sain_hisether;/* his Ethernet address */
};
