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
 * $Log:	ns.h,v $
 * Revision 2.3  89/03/09  20:52:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:07:22  gm0w
 * 	Updated copyright.  Updated host byte order macros.
 * 	[89/02/12            gm0w]
 * 
 * 07-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Added net <--> host byte order macros for ns32000
 *
 */ 
/*
 * Copyright (c) 1984, 1985, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ns.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Constants and Structures defined by the Xerox Network Software
 * per "Internet Transport Protocols", XSIS 028112, December 1981
 */

/*
 * Protocols
 */
#define NSPROTO_RI	1		/* Routing Information */
#define NSPROTO_ECHO	2		/* Echo Protocol */
#define NSPROTO_ERROR	3		/* Error Protocol */
#define NSPROTO_PE	4		/* Packet Exchange */
#define NSPROTO_SPP	5		/* Sequenced Packet */
#define NSPROTO_RAW	255		/* Placemarker*/
#define NSPROTO_MAX	256		/* Placemarker*/


/*
 * Port/Socket numbers: network standard functions
 */

#define NSPORT_RI	1		/* Routing Information */
#define NSPORT_ECHO	2		/* Echo */
#define NSPORT_RE	3		/* Router Error */

/*
 * Ports < NSPORT_RESERVED are reserved for priveleged
 * processes (e.g. root).
 */
#define NSPORT_RESERVED		3000

/* flags passed to ns_output as last parameter */

#define NS_FORWARDING		0x1	/* most of idp header exists */
#define NS_ROUTETOIF		0x10	/* same as SO_DONTROUTE */
#define NS_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets */

#define NS_MAXHOPS		15

/* flags passed to get/set socket option */
#define SO_HEADERS_ON_INPUT	1
#define SO_HEADERS_ON_OUTPUT	2
#define SO_DEFAULT_HEADERS	3
#define SO_LAST_HEADER		4
#define SO_NSIP_ROUTE		5
#define SO_SEQNO		6
#define SO_ALL_PACKETS		7
#define SO_MTU			8


/*
 * NS addressing
 */
union ns_host {
	u_char	c_host[6];
	u_short	s_host[3];
};

union ns_net {
	u_char	c_net[4];
	u_short	s_net[2];
};

union ns_net_u {
	union ns_net	net_e;
	u_long		long_e;
};

struct ns_addr {
	union ns_net	x_net;
	union ns_host	x_host;
	u_short	x_port;
};

/*
 * Socket address, Xerox style
 */
struct sockaddr_ns {
	u_short		sns_family;
	struct ns_addr	sns_addr;
	char		sns_zero[2];
};
#define sns_port sns_addr.x_port

#ifdef	vax
#define ns_netof(a) (*(long *) & ((a).x_net)) /* XXX - not needed */
#endif
#define ns_neteqnn(a,b) (((a).s_net[0]==(b).s_net[0]) && \
					((a).s_net[1]==(b).s_net[1]))
#define ns_neteq(a,b) ns_neteqnn((a).x_net, (b).x_net)
#define satons_addr(sa)	(((struct sockaddr_ns *)&(sa))->sns_addr)
#define ns_hosteqnh(s,t) ((s).s_host[0] == (t).s_host[0] && \
	(s).s_host[1] == (t).s_host[1] && (s).s_host[2] == (t).s_host[2])
#define ns_hosteq(s,t) (ns_hosteqnh((s).x_host,(t).x_host))
#define ns_nullhost(x) (((x).x_host.s_host[0]==0) && \
	((x).x_host.s_host[1]==0) && ((x).x_host.s_host[2]==0))

/*
 * Macros for number representation conversion.
 */
#if	!defined(ntohl) && !defined(lint)
#if	BYTE_MSF
#define ntohl(x)	(x)
#define ntohs(x)	(x)
#define htonl(x)	(x)
#define htons(x)	(x)
#else	BYTE_MSF
#if	defined(ns32000)
/* VAX does these in assembler (sed/inline).  Perhaps we will also someday. */
#define ntohl(x)	((0xff & (x)>>24) | (0xff00 & (x)>>8) | \
			(0xff0000 & (x)<<8) | (0xff000000 & (x)<<24))
#define ntohs(x)	((0xff & (x)>>8) | (0xff00 & (x)<<8))
#define htonl(x)	ntohl(x)
#define htons(x)	ntohs(x)
#endif	ns32000
#endif	BYTE_MSF
#endif	!defined(ntohl) && !defined(lint)

#if	!defined(ntohl)
u_short	ntohs(), htons();
u_long	ntohl(), htonl();
#endif	!defined(ntohl)

#ifdef	KERNEL
extern struct domain nsdomain;
union ns_host ns_thishost;
union ns_host ns_zerohost;
union ns_host ns_broadhost;
union ns_net ns_zeronet;
union ns_net ns_broadnet;
u_short ns_cksum();
#endif
