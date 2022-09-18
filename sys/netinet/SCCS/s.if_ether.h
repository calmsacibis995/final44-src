h25527
s 00000/00001/00196
d D 8.3 95/05/02 00:01:04 mckusick 25 24
c delete unused prototype
e
s 00002/00003/00195
d D 8.2 95/04/28 17:30:03 bostic 24 23
c arpwhohas prototyped twice
e
s 00002/00002/00196
d D 8.1 93/06/10 23:03:58 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00021/00188
d D 7.10 93/06/04 17:22:47 bostic 22 21
c prototype everything
e
s 00000/00007/00209
d D 7.9 93/01/08 18:42:20 andrew 21 20
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00111/00006/00105
d D 7.8 92/07/06 15:08:16 sklower 20 19
c multicast changes from lbl
e
s 00010/00003/00101
d D 7.7 92/01/30 14:11:00 torek 19 18
c lint changes for sparc port (checked in by sklower)
e
s 00024/00002/00080
d D 7.6 91/06/25 22:15:49 sklower 18 17
c checkpoint working merge of routing and arp tables\;
e
s 00001/00011/00081
d D 7.5 90/06/28 21:36:14 bostic 17 16
c new copyright notice
e
s 00003/00002/00089
d D 7.4 89/02/17 10:11:16 karels 16 15
c variable length sockaddrs; rename en{_,}* to ether_
e
s 00010/00005/00081
d D 7.3 88/06/29 17:06:30 bostic 15 14
c install approved copyright notice
e
s 00008/00002/00078
d D 7.2 87/12/07 17:45:07 bostic 14 13
c use Berkeley specific header
e
s 00001/00001/00079
d D 7.1 86/06/05 00:24:49 mckusick 13 12
c 4.3BSD release version
e
s 00010/00010/00070
d D 6.7 86/01/13 16:52:25 karels 12 11
c separate ARP header from IP-specific portion; break out IP
c portion of the input code; add trailer negotiation
e
s 00001/00001/00079
d D 6.6 85/09/16 22:42:18 karels 11 10
c compact entries
e
s 00007/00001/00073
d D 6.5 85/06/08 12:36:51 mckusick 10 9
c Add copyright
e
s 00017/00027/00057
d D 6.4 85/04/16 09:57:12 karels 9 8
c purge struct ether_addr (not portable);
c change ETHERPUP_*TYPE's to ETHERTYPE_*'s;
c add inaddr to arpcom struct, as not in ifnet any longer
e
s 00030/00010/00054
d D 6.3 84/03/20 15:25:34 karels 8 7
c new ARP; arptab in header file
e
s 00001/00001/00063
d D 6.2 83/09/26 08:38:05 karels 7 6
c PUP type is 0x0200 (RFC 820)
e
s 00000/00000/00064
d D 6.1 83/07/29 07:11:02 sam 6 5
c 4.2 distribution
e
s 00002/00003/00062
d D 4.5 83/05/15 17:15:37 sam 5 4
c from sun
e
s 00041/00000/00024
d D 4.4 83/03/15 18:17:35 sam 4 3
c ARP ARP
e
s 00003/00003/00021
d D 4.3 82/12/16 15:47:11 sam 3 2
c the numbers really were right (sigh)
e
s 00013/00010/00011
d D 4.2 82/12/16 15:40:23 sam 2 1
c fix byte swapping problems in header
e
s 00021/00000/00000
d D 4.1 82/12/16 14:38:25 sam 1 0
c date and time created 82/12/16 14:38:25 by sam
e
u
U
t
T
I 1
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
/*
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
D 23
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 17
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 15
E 14
 *
 *	%W% (Berkeley) %G%
 */
E 10

/*
I 8
D 9
 * Ethernet address - 6 octets
 */
struct ether_addr {
	u_char	ether_addr_octet[6];
};

/*
E 9
E 8
 * Structure of a 10Mb/s Ethernet header.
 */
D 2
struct	eth_header {
	u_char	eth_dhost[6];
	u_char	eth_shost[6];
	u_short	eth_type;
E 2
I 2
struct	ether_header {
D 8
	u_char	ether_dhost[6];
	u_char	ether_shost[6];
E 8
I 8
D 9
	struct	ether_addr ether_dhost;
	struct	ether_addr ether_shost;
E 9
I 9
	u_char	ether_dhost[6];
	u_char	ether_shost[6];
E 9
E 8
	u_short	ether_type;
E 2
};

D 2
#define	ETHPUP_PUPTYPE	4		/* PUP protocol */
#define	ETHPUP_IPTYPE	8		/* IP protocol */
E 2
I 2
D 3
#define	ETHERPUP_PUPTYPE	4		/* PUP protocol */
#define	ETHERPUP_IPTYPE	8		/* IP protocol */
E 3
I 3
D 7
#define	ETHERPUP_PUPTYPE	0x0400		/* PUP protocol */
E 7
I 7
D 9
#define	ETHERPUP_PUPTYPE	0x0200		/* PUP protocol */
E 7
#define	ETHERPUP_IPTYPE		0x0800		/* IP protocol */
I 4
#define ETHERPUP_ARPTYPE	0x0806		/* Addr. resolution protocol */
E 9
I 9
D 20
#define	ETHERTYPE_PUP	0x0200		/* PUP protocol */
#define	ETHERTYPE_IP	0x0800		/* IP protocol */
#define ETHERTYPE_ARP	0x0806		/* Addr. resolution protocol */
E 20
I 20
#define	ETHERTYPE_PUP		0x0200	/* PUP protocol */
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#define ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#define ETHERTYPE_REVARP	0x8035	/* reverse Addr. resolution protocol */
E 20
E 9
E 4
E 3
E 2

/*
D 2
 * The ETHPUP_NTRAILER packet types starting at ETHPUP_TRAIL have
 * (type-ETHPUP_TRAIL)*512 bytes of data followed
E 2
I 2
D 9
 * The ETHERPUP_NTRAILER packet types starting at ETHERPUP_TRAIL have
E 9
I 9
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
E 9
D 12
 * (type-ETHERPUP_TRAIL)*512 bytes of data followed
E 2
 * by a PUP type (as given above) and then the (variable-length) header.
E 12
I 12
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
E 12
 */
D 2
#define	ETHPUP_TRAIL	16		/* Trailer PUP */
#define	ETHPUP_NTRAILER	16
E 2
I 2
D 3
#define	ETHERPUP_TRAIL	16		/* Trailer PUP */
E 3
I 3
D 9
#define	ETHERPUP_TRAIL		0x1000		/* Trailer PUP */
E 3
#define	ETHERPUP_NTRAILER	16
E 9
I 9
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16
E 9

#define	ETHERMTU	1500
#define	ETHERMIN	(60-14)
I 4

I 20
#ifdef KERNEL
E 20
D 5
u_char etherbroadcastaddr[6];			/* 6 bytes of 0xFF */

E 5
/*
I 20
 * Macro to map an IP multicast address to an Ethernet multicast address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address.
 */
#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr) \
	/* struct in_addr *ipaddr; */ \
	/* u_char enaddr[6];	   */ \
{ \
	(enaddr)[0] = 0x01; \
	(enaddr)[1] = 0x00; \
	(enaddr)[2] = 0x5e; \
	(enaddr)[3] = ((u_char *)ipaddr)[1] & 0x7f; \
	(enaddr)[4] = ((u_char *)ipaddr)[2]; \
	(enaddr)[5] = ((u_char *)ipaddr)[3]; \
}
#endif

/*
E 20
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to 
 * RFC 826.
 */
struct	ether_arp {
D 12
	u_short	arp_hrd;	/* format of hardware address */
#define ARPHRD_ETHER 	1	/* ethernet hardware address */
	u_short	arp_pro;	/* format of proto. address (ETHERPUP_IPTYPE) */
	u_char	arp_hln;	/* length of hardware address (6) */
	u_char	arp_pln;	/* length of protocol address (4) */
	u_short	arp_op;
#define	ARPOP_REQUEST	1	/* request to resolve address */
#define	ARPOP_REPLY	2	/* response to previous request */
E 12
I 12
	struct	arphdr ea_hdr;	/* fixed-size header */
E 12
D 8
	u_char	arp_sha[6];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[6];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
E 8
I 8
D 9
	u_char	arp_xsha[6];	/* sender hardware address */
	u_char	arp_xspa[4];	/* sender protocol address */
	u_char	arp_xtha[6];	/* target hardware address */
	u_char	arp_xtpa[4];	/* target protocol address */
E 9
I 9
	u_char	arp_sha[6];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[6];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
E 9
E 8
};
I 12
#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op
E 12
I 8
D 9
#define	arp_sha(ea)	(*(struct ether_addr *)(ea)->arp_xsha)
#define	arp_spa(ea)	(*(struct in_addr *)(ea)->arp_xspa)
#define	arp_tha(ea)	(*(struct ether_addr *)(ea)->arp_xtha)
#define	arp_tpa(ea)	(*(struct in_addr *)(ea)->arp_xtpa)
E 9
E 8

I 12

E 12
D 5
#ifdef	KERNEL
E 5
/*
 * Structure shared between the ethernet driver modules and
 * the address resolution code.  For example, each ec_softc or il_softc
 * begins with this structure.
 */
struct	arpcom {
D 9
	struct 	ifnet ac_if;	/* network-visible interface */
D 8
	u_char	ac_enaddr[6];	/* ethernet hardware address */
	struct	arpcom *ac_ac;	/* link to next ether driver */
E 8
I 8
	struct ether_addr ac_enaddr;	/* ethernet hardware address */
E 9
I 9
	struct 	ifnet ac_if;		/* network-visible interface */
	u_char	ac_enaddr[6];		/* ethernet hardware address */
D 20
	struct in_addr ac_ipaddr;	/* copy of ip address- XXX */
E 20
I 20
	struct	in_addr ac_ipaddr;	/* copy of ip address- XXX */
	struct	ether_multi *ac_multiaddrs; /* list of ether multicast addrs */
	int	ac_multicnt;		/* length of ac_multiaddrs list */	
E 20
E 9
E 8
};

I 8
D 22
/*
 * Internet to ethernet address resolution table.
 */
struct	arptab {
	struct	in_addr at_iaddr;	/* internet address */
D 9
	struct	ether_addr at_enaddr;	/* ethernet address */
E 9
I 9
	u_char	at_enaddr[6];		/* ethernet address */
E 9
D 11
	struct	mbuf *at_hold;		/* last packet until resolved/timeout */
E 11
	u_char	at_timer;		/* minutes since last reference */
	u_char	at_flags;		/* flags */
I 11
	struct	mbuf *at_hold;		/* last packet until resolved/timeout */
E 11
D 20
};
E 20
I 20
}; /* XXX: only used to define SIOCGARP, which is no longer supported */
E 20

E 22
I 18
struct llinfo_arp {				
	struct	llinfo_arp *la_next;
	struct	llinfo_arp *la_prev;
	struct	rtentry *la_rt;
	struct	mbuf *la_hold;		/* last packet until resolved/timeout */
	long	la_asked;		/* last time we QUERIED for this addr */
#define la_timer la_rt->rt_rmx.rmx_expire /* deletion time in seconds */
};

struct sockaddr_inarp {
	u_char	sin_len;
	u_char	sin_family;
	u_short sin_port;
	struct	in_addr sin_addr;
	struct	in_addr sin_srcaddr;
	u_short	sin_tos;
	u_short	sin_other;
#define SIN_PROXY 1
};
I 20
/*
 * IP and ethernet specific routing flags
 */
#define	RTF_USETRAILERS	RTF_PROTO1	/* use trailers */
#define RTF_ANNOUNCE	RTF_PROTO2	/* announce new arp entry */
E 20

E 18
E 8
I 5
#ifdef	KERNEL
D 8
u_char etherbroadcastaddr[6];			/* 6 bytes of 0xFF */
E 5
struct	in_addr arpmyaddr();
E 8
I 8
D 9
struct ether_addr etherbroadcastaddr;
E 9
I 9
D 16
u_char etherbroadcastaddr[6];
E 16
I 16
u_char	etherbroadcastaddr[6];
I 20
D 21
#if defined(ISO) && !defined(MULTICAST)
#define MULTICAST 1
#endif
#ifdef MULTICAST
E 21
u_char	ether_ipmulticast_min[6];
u_char	ether_ipmulticast_max[6];
I 22
struct	ifqueue arpintrq;
E 22
D 21
#endif
E 21

E 20
E 16
E 9
E 8
D 18
struct	arptab *arptnew();
I 12
D 16
char *ether_sprintf();
E 16
I 16
int	ether_output(), ether_input();
E 18
I 18
D 19
struct	llinfo_arp *arptnew();
E 19
I 19
D 25
struct	llinfo_arp *arptnew __P((struct in_addr *));
E 25
E 19
struct	llinfo_arp llinfo_arp;		/* head of the llinfo queue */
D 19
int	ether_output(), ether_input(), arp_rtrequest();
E 18
char	*ether_sprintf();
E 19
I 19
D 22
int	ether_output __P((struct ifnet *, struct mbuf *, struct sockaddr *,
			  struct rtentry *));
int	ether_input __P((struct ifnet *, struct ether_header *, struct mbuf *));
char	*ether_sprintf __P((u_char *));
D 20
int	arp_rtrequest __P((int, struct rtentry *, struct sockaddr *));
E 20
I 20
void	arp_rtrequest __P((int, struct rtentry *, struct sockaddr *));
E 20
E 19
I 18
struct	ifqueue arpintrq;
E 22
I 19

D 22
/* XXX These probably belong elsewhere */
void	in_arpinput __P((struct mbuf *));
E 22
D 24
void	arpwhohas __P((struct arpcom *, struct in_addr *));
E 24
I 24
void	arp_rtrequest __P((int, struct rtentry *, struct sockaddr *));
E 24
I 22
void	arpintr __P((void));
int	arpresolve __P((struct arpcom *,
D 24
	   struct rtentry *, struct mbuf *, struct sockaddr *, u_char *));
void	arp_rtrequest __P((int, struct rtentry *, struct sockaddr *));
E 24
I 24
	    struct rtentry *, struct mbuf *, struct sockaddr *, u_char *));
E 24
void	arpwhohas __P((struct arpcom *, struct in_addr *));
E 22
I 20

I 22
int	ether_addmulti __P((struct ifreq *, struct arpcom *));
int	ether_delmulti __P((struct ifreq *, struct arpcom *));

E 22
D 21
#ifdef MULTICAST
E 21
/*
 * Ethernet multicast address structure.  There is one of these for each
 * multicast address or range of multicast addresses that we are supposed
 * to listen to on a particular interface.  They are kept in a linked list,
 * rooted in the interface's arpcom structure.  (This really has nothing to
 * do with ARP, or with the Internet address family, but this appears to be
 * the minimally-disrupting place to put it.)
 */
struct ether_multi {
	u_char	enm_addrlo[6];		/* low  or only address of range */
	u_char	enm_addrhi[6];		/* high or only address of range */
	struct	arpcom *enm_ac;		/* back pointer to arpcom */
	u_int	enm_refcount;		/* no. claims to this addr/range */
	struct	ether_multi *enm_next;	/* ptr to next ether_multi */
};

D 22
#ifdef KERNEL
E 22
/*
 * Structure used by macros below to remember position when stepping through
 * all of the ether_multi records.
 */
struct ether_multistep {
	struct ether_multi  *e_enm;
};

/*
 * Macro for looking up the ether_multi record for a given range of Ethernet
 * multicast addresses connected to a given arpcom structure.  If no matching
 * record is found, "enm" returns NULL.
 */
#define ETHER_LOOKUP_MULTI(addrlo, addrhi, ac, enm) \
	/* u_char addrlo[6]; */ \
	/* u_char addrhi[6]; */ \
	/* struct arpcom *ac; */ \
	/* struct ether_multi *enm; */ \
{ \
	for ((enm) = (ac)->ac_multiaddrs; \
	    (enm) != NULL && \
	    (bcmp((enm)->enm_addrlo, (addrlo), 6) != 0 || \
	     bcmp((enm)->enm_addrhi, (addrhi), 6) != 0); \
		(enm) = (enm)->enm_next); \
}

/*
 * Macro to step through all of the ether_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  ETHER_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "enm" when there
 * are no remaining records.
 */
#define ETHER_NEXT_MULTI(step, enm) \
	/* struct ether_multistep step; */  \
	/* struct ether_multi *enm; */  \
{ \
	if (((enm) = (step).e_enm) != NULL) \
		(step).e_enm = (enm)->enm_next; \
}

#define ETHER_FIRST_MULTI(step, ac, enm) \
	/* struct ether_multistep step; */ \
	/* struct arpcom *ac; */ \
	/* struct ether_multi *enm; */ \
{ \
	(step).e_enm = (ac)->ac_multiaddrs; \
	ETHER_NEXT_MULTI((step), (enm)); \
}
D 21
#endif
E 21
D 22
#endif
E 22
I 22

E 22
E 20
E 19
E 18
E 16
E 12
#endif
E 4
E 2
E 1
