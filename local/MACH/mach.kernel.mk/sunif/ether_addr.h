/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ether_addr.h,v $
 * Revision 2.3  89/02/25  20:01:39  gm0w
 * 	Added new copyright as part of kernel cleanup.
 * 	[89/02/11            jjc]
 * 
 * Revision 2.2  89/01/18  01:13:04  jsb
 * 	Vnode support: use _ETHER_ADDR_ to prevent multiple definition of
 * 	struct ether_addr via netinet/if_ether.h.
 * 	[89/01/17  10:58:56  jsb]
 * 
 *
 *  8-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created to make Sun Ethernet drivers happy.
 */

#ifndef	_ETHER_ADDR_		/* needs to match name in netinet/if_ether.h */
#define _ETHER_ADDR_
/*
 * Ethernet address - 6 octets
 */
struct ether_addr {
	unsigned char  ether_addr_octet[6];
};
#endif	_ETHER_ADDR_
