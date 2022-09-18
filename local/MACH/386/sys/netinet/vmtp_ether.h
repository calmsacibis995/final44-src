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
 * $Log:	vmtp_ether.h,v $
 * Revision 2.3  89/03/09  20:48:22  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:27  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: vmtp_ether.h,v 2.1 87/08/14 15:43:16 mrt Exp $
 */

/*
 *    vmtp_ether.h
 *    Written by Erik Nordmark
 */

#define ETHERTYPE_LE_VMTP	0x8060	/* little-endian */
#define ETHERTYPE_BE_VMTP	0x805f	/* big-endian */
#define ETHERTYPE_LE_VMTPS	0x8062	/* little-endian secure */
#define ETHERTYPE_BE_VMTPS	0x8061	/* big-endian secure */

#define ETHER_VMTP_MULTICAST0	0x09	/* same as ETHER_IP_MULTICAST */
#define ETHER_VMTP_MULTICAST1	0x00	
#define ETHER_VMTP_MULTICAST2	0x56	

/*
 * Check if an in_addr is local i.e. accesible without using IP.
 */
#define vmtp_localnet(in)	in_localaddr(in)

/*
 * Find the interface to use for multicasting with raw ethernet packets. 
 * Just pick the first one. 
 */
#define vmtp_defaultifp	((in_ifaddr == NULL) ? NULL : in_ifaddr->ia_ifp)


#define vmtp_setmulticastaddr(addr, entity) 			\
	{ (addr).va_type = VAT_ETHER;				\
	  (addr).va_ether[0] = ETHER_VMTP_MULTICAST0;	 	\
	  (addr).va_ether[1] = ETHER_VMTP_MULTICAST1;		\
	  (addr).va_ether[2] = ETHER_VMTP_MULTICAST2;		\
	  (addr).va_ether[3] = (entity).ve_inaddr >> 16;	\
	  (addr).va_ether[4] = (entity).ve_inaddr >> 8;		\
	  (addr).va_ether[5] = (entity).ve_inaddr; }


#define ether_multicast(dhost) 				\
	((dhost)[0] == ETHER_VMTP_MULTICAST0 && 	\
	 (dhost)[1] == ETHER_VMTP_MULTICAST1 && 	\
	 (dhost)[2] == ETHER_VMTP_MULTICAST2)

#ifdef	KERNEL
struct ifqueue vmtpintrq;	/* queue for incoming packets */

struct ifnet *vmtp_findinterface();
struct ifnet *vmtp_route();
struct arptab *arptab_look();
#endif
