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
 * $Log:	ip_var.h,v $
 * Revision 2.5  89/05/30  10:39:08  rvb
 * 	Keyed byte-order dependecnies on BYTE_MSF.
 * 	[89/04/20            af]
 * 
 * Revision 2.4  89/03/09  20:45:40  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:00:41  gm0w
 * 	Updated copyright. Changed romp to ibmrt
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  89/01/23  22:20:47  af
 * 	Added definitions of ip_hl and ip_v for the Mips architecture(s).
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: byte order
 * 	[89/01/09            rvb]
 * 
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in code for IP multicast.
 *
 * 21-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added definitions of ip_hl and ip_v for the 68000.
 *
 * 07-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Added ip_hl and ip_v definitions for ns32000
 *
 * 17-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added definitions of ip_hl and ip_v for romp.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ip_var.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 */
struct ipovly {
	caddr_t	ih_next, ih_prev;	/* for protocol sequence q's */
	u_char	ih_x1;			/* (unused) */
	u_char	ih_pr;			/* protocol */
	short	ih_len;			/* protocol length */
	struct	in_addr ih_src;		/* source internet address */
	struct	in_addr ih_dst;		/* destination internet address */
};

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	ipasfrag *ipq_next,*ipq_prev;
					/* to ip headers of fragments */
	struct	in_addr ipq_src,ipq_dst;
};

/*
 * Ip header, when holding a fragment.
 *
 * Note: ipf_next must be at same offset as ipq_next above
 */
struct	ipasfrag {
#if	BYTE_MSF
	u_char	ip_v:4,
		ip_hl:4;
#else
	u_char	ip_hl:4,
		ip_v:4;
#endif
	u_char	ipf_mff;		/* copied from (ip_off&IP_MF) */
	short	ip_len;
	u_short	ip_id;
	short	ip_off;
	u_char	ip_ttl;
	u_char	ip_p;
	u_short	ip_sum;
	struct	ipasfrag *ipf_next;	/* next fragment */
	struct	ipasfrag *ipf_prev;	/* previous fragment */
};

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
#define MAX_IPOPTLEN	40

struct ipoption {
	struct	in_addr ipopt_dst;	/* first-hop dst if source routed */
	char	ipopt_list[MAX_IPOPTLEN];	/* options proper */
};

struct ip_multicastopt {
	struct	in_addr ipopt_dst;	/* dst of remote agent */
	char	ipopt_list[IPOPT_MULTICAST_OPTLEN]; /* options proper */
};

struct	ipstat {
	long	ips_total;		/* total packets received */
	long	ips_badsum;		/* checksum bad */
	long	ips_tooshort;		/* packet too short */
	long	ips_toosmall;		/* not enough data */
	long	ips_badhlen;		/* ip header length < data size */
	long	ips_badlen;		/* ip length < ip header length */
	long	ips_fragments;		/* fragments received */
	long	ips_fragdropped;	/* frags dropped (dups, out of space) */
	long	ips_fragtimeout;	/* fragments timed out */
	long	ips_forward;		/* packets forwarded */
	long	ips_cantforward;	/* packets rcvd for unreachable dest */
	long	ips_redirectsent;	/* packets forwarded on same net */
};

#ifdef	KERNEL
/* flags passed to ip_output as last parameter */
#define IP_FORWARDING		0x1		/* most of ip header exists */
#define IP_NOLOOPBACK		0x2		/* don't loop to ip_input */
#define IP_AGENTFORWARDING	0x4		/* agent forwarding packet */
#define IP_ROUTETOIF		SO_DONTROUTE	/* bypass routing tables */
#define IP_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets */

struct	ipstat	ipstat;
struct	ipq	ipq;			/* ip reass. queue */
u_short	ip_id;				/* ip packet ctr, for ids */

struct	mbuf *ip_srcroute();
#endif	KERNEL
