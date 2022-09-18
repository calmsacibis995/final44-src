/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	in.h,v $
 * Revision 2.8  90/07/03  16:42:17  mrt
 * 	Added Multicast rel5 code
 * 	[90/06/26            jjk]
 * 
 * Revision 2.5.4.1  90/05/23  17:02:17  mrt
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17            emg]
 * 
 * Revision 2.7  90/01/11  16:49:35  berman
 * 	Added under __STDC__ conditionals the ansi C declarations for 
 * 	ntohs(), ntohl(), htons(), and htonl().
 * 	[90/01/11            berman]
 * 
 * Revision 2.6  89/10/11  14:49:27  dlb
 * 	Multimax uses inline for byte ordering.
 * 	[89/08/01            dlb]
 * 
 * Revision 2.5  89/03/09  20:44:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/27  21:04:47  mrt
 * 	Made MULTICAST code always true and removed the 
 * 	else code.
 * 	[89/02/27            mrt]
 * 
 * Revision 2.3  89/02/25  18:59:18  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  89/01/23  22:19:55  af
 * 	Changes for mips (MIPSEL and MIPSEB) ordering
 * 	[89/01/10            af]
 * 	
 * 	Changes for I386 -- little endian byte order
 * 	[89/01/09            rvb]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 04-Jun-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Put multicast features in #ifdef KERNEL.
 *
 * 28-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Added IPPROTO_VMTP.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in code for IP multicast.
 *
 * 08-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Defined byte order macros for ns32000.
 *
 */ 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)in.h	7.6 (Berkeley) 6/29/88
 */

#ifndef _IN_H_
#define	_IN_H_

#include <machine/endian.h>

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981.
 */

/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define	IPPROTO_IGMP		2		/* group mgmt protocol */
#define	IPPROTO_GGP		3		/* gateway^2 (deprecated) */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_EGP		8		/* exterior gateway protocol */
#define	IPPROTO_PUP		12		/* pup */
#define	IPPROTO_UDP		17		/* user datagram protocol */
#define	IPPROTO_IDP		22		/* xns idp */

#define	IPPROTO_RAW		255		/* raw IP packet */
#define	IPPROTO_MAX		256


/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */
#define	IPPORT_RESERVED		1024
#define	IPPORT_USERRESERVED	5000

/*
 * Link numbers
 */
#define	IMPLINK_IP		155
#define	IMPLINK_LOWEXPER	156
#define	IMPLINK_HIGHEXPER	158

/*
 * Internet address (a structure for historical reasons)
 */
struct in_addr {
	u_long s_addr;
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	IN_CLASSA(i)		(((long)(i) & 0x80000000) == 0)
#define	IN_CLASSA_NET		0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		0x00ffffff
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((long)(i) & 0xc0000000) == 0x80000000)
#define	IN_CLASSB_NET		0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		0x0000ffff
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((long)(i) & 0xe0000000) == 0xc0000000)
#define	IN_CLASSC_NET		0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		0x000000ff

#define	IN_CLASSD(i)		(((long)(i) & 0xf0000000) == 0xe0000000)
#define	IN_CLASSD_NET		0xf0000000	/* These ones aren't really */
#define	IN_CLASSD_NSHIFT	28		/* net and host fields, but */
#define	IN_CLASSD_HOST		0x0fffffff	/* routing needn't know.    */
#define	IN_MULTICAST(i)		IN_CLASSD(i)

#define	IN_EXPERIMENTAL(i)	(((long)(i) & 0xe0000000) == 0xe0000000)
#define	IN_BADCLASS(i)		(((long)(i) & 0xf0000000) == 0xf0000000)

#define	INADDR_ANY		(u_long)0x00000000
#define	INADDR_BROADCAST	(u_long)0xffffffff	/* must be masked */

#define	INADDR_UNSPEC_GROUP	(u_long)0xe0000000	/* 224.0.0.0   */
#define	INADDR_ALLHOSTS_GROUP	(u_long)0xe0000001	/* 224.0.0.1   */
#define	INADDR_MAX_LOCAL_GROUP 	(u_long)0xe00000ff	/* 224.0.0.255 */

#ifndef KERNEL
#define	INADDR_NONE		0xffffffff		/* -1 return */
#endif

#define	IN_LOOPBACKNET		127			/* official! */
#define	INADDR_LOOPBACK		(u_long)0x7f000001	/* 127.0.0.1 */

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	short	sin_family;
	u_short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};

/*
 * Options for use with [gs]etsockopt at the IP level.
 */
#define	IP_OPTIONS		1	/* set/get IP per-packet options   */
#define	IP_HDRINCL		2	/* set/get RAW packet header option */

#define	IP_MULTICAST_IF		3	/* set/get IP multicast interface  */
#define	IP_MULTICAST_TTL	4	/* set/get IP multicast timetolive */
#define	IP_MULTICAST_LOOP	5	/* set/get IP multicast loopback   */
#define	IP_ADD_MEMBERSHIP	6	/* add  an IP group membership     */
#define	IP_DROP_MEMBERSHIP	7	/* drop an IP group membership     */



#define	IP_DEFAULT_MULTICAST_TTL   1	/* normally limit m'casts to 1 hop  */
#define	IP_DEFAULT_MULTICAST_LOOP  1	/* normally hear sends if a member  */
#define	IP_MAX_MEMBERSHIPS         20	/* per socket; must fit in one mbuf */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct ip_mreq {
	struct in_addr	imr_multiaddr;	/* IP multicast address of group */
	struct in_addr	imr_interface;	/* local IP address of interface */
};

#ifdef	KERNEL
extern	struct domain inetdomain;
extern	struct protosw inetsw[];
struct	in_addr in_makeaddr();
u_long	in_netof(), in_lnaof();
#endif

#endif /* _IN_H_ */
