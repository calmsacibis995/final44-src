h53704
s 00004/00002/00167
d D 8.2 94/06/30 20:05:23 sklower 11 10
c fix bugs about binding to a specific NSAP ignoring NSEL
e
s 00002/00002/00167
d D 8.1 93/06/10 23:19:33 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00167
d D 7.9 93/05/25 11:51:38 bostic 9 8
c trailing comment after #else or #endif
e
s 00005/00000/00164
d D 7.8 92/11/25 20:06:19 sklower 8 7
c assign socket and NLPID numbers for IDRP, also tcp & udp
e
s 00001/00001/00163
d D 7.7 92/10/11 12:21:50 bostic 7 6
c make kernel includes standard
e
s 00009/00001/00155
d D 7.6 91/05/06 19:24:02 bostic 6 5
c new copyright; att/bsd/shared
e
s 00009/00002/00147
d D 7.5 91/02/22 09:59:57 donn 5 4
c Prototype declarations.
e
s 00002/00000/00147
d D 7.4 90/06/22 15:39:32 sklower 4 3
c merge in UW isis changes; my merge is untested, but SCCS id's
c must be assigned before I leave today :-(
e
s 00018/00182/00129
d D 7.3 89/08/29 13:44:21 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00024/00003/00287
d D 7.2 89/04/22 11:54:09 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00290/00000/00000
d D 7.1 88/12/14 15:29:41 sklower 1 0
c date and time created 88/12/14 15:29:41 by sklower
e
u
U
t
T
I 6
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 11
 * Copyright (c) 1991, 1993
E 11
I 11
 * Copyright (c) 1991, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 6
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/* $Header: iso.h,v 4.9 88/09/11 18:06:38 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/iso.h,v $ */
I 2
D 6
/*	%W% (Berkeley) %G% */
E 6
E 2

#ifndef __ISO__
#define __ISO__

/*
 *	Return true if this is a multicast address
 *	This assumes that the bit transmission is lsb first. This 
 *	assumption is valid for 802.3 but not 802.5. There is a
 *	kludge to get around this for 802.5 -- see if_lan.c
 *	where subnetwork header is setup.
 */
#define	IS_MULTICAST(snpa)\
	((snpa)[0] & 0x01)
	
/*
 * Protocols
 */
I 8
#define	ISOPROTO_TCP	6		/* IETF experiment */
#define	ISOPROTO_UDP	17		/* IETF experiment */
E 8
#define	ISOPROTO_TP0	25		/* connection oriented transport protocol */
#define	ISOPROTO_TP1	26		/* not implemented */
#define	ISOPROTO_TP2	27		/* not implemented */
#define	ISOPROTO_TP3	28		/* not implemented */
#define	ISOPROTO_TP4	29		/* connection oriented transport protocol */
#define	ISOPROTO_TP		ISOPROTO_TP4	 /* tp-4 with negotiation */
#define	ISOPROTO_CLTP	30		/* connectionless transport (not yet impl.) */
#define	ISOPROTO_CLNP	31		/* connectionless internetworking protocol */
#define	ISOPROTO_X25	32		/* cons */
#define	ISOPROTO_INACT_NL	33	/* inactive network layer! */
#define	ISOPROTO_ESIS	34		/* ES-IS protocol */
I 4
#define	ISOPROTO_INTRAISIS	35		/* IS-IS protocol */
I 8
#define	ISOPROTO_IDRP	36		/* Interdomain Routing Protocol */
E 8
E 4

#define	ISOPROTO_RAW	255		/* raw clnp */
#define	ISOPROTO_MAX	256

#define	ISO_PORT_RESERVED		1024
#define	ISO_PORT_USERRESERVED	5000
/*
 * Port/socket numbers: standard network functions
 * NOT PRESENTLY USED
 */
#define	ISO_PORT_MAINT		501
#define	ISO_PORT_ECHO		507
#define	ISO_PORT_DISCARD	509
#define	ISO_PORT_SYSTAT		511
#define	ISO_PORT_NETSTAT	515
/*
 * Port/socket numbers: non-standard application functions
 */
#define ISO_PORT_LOGIN		513
/*
 * Port/socket numbers: public use
 */
#define ISO_PORT_PUBLIC		1024		/* high bit set --> public */

/*
 *	Network layer protocol identifiers
 */
#define ISO8473_CLNP	0x81
#define	ISO9542_ESIS	0x82
#define ISO9542X25_ESIS	0x8a
I 4
#define ISO10589_ISIS		0x83
I 8
#define ISO8878A_CONS		0x84
#define ISO10747_IDRP		0x85
E 8
E 4

I 3

E 3
#ifndef IN_CLASSA_NET
D 7
#include "../netinet/in.h"
E 7
I 7
#include <netinet/in.h>
E 7
D 9
#endif IN_CLASSA_NET
E 9
I 9
#endif /* IN_CLASSA_NET */
E 9

D 3
/*
 *	Type 37 Address
 *
 *	This address is named for the value of its AFI (37). This format
 *	supports an X.121 address. A type 37 address has the following format:
 *
 *  <----- idp -------> <- dsp ->
 *  <- afi -> <- idi -> <- dsp ->
 *  | "37"   | 7 bytes | 9 bytes |
 *
 *	The idi contains 14 bcd digits of X.121 address.
 *	The use of the dsp part is unknown.
 *
 *	The afi is considered the "network" portion of the address.
 *  This means that you can't have multihoming in the x.25 environment.
 *  Makes loopback a bear.
 */
I 2
#define BIGSOCKADDRS
E 2
#ifdef BIGSOCKADDRS
#define	ADDR37_IDI_LEN		7			/* 14 bcd digits == 7 octets */
#define	ADDR37_DSP_LEN		9
#else
#define	ADDR37_IDI_LEN		7			/* 14 bcd digits == 7 octets */
#define	ADDR37_DSP_LEN		3			/* this is a lie to fit in sockaddr */
#endif BIGSOCKADDRS
struct addr_37 {
	u_char a37_idi[ADDR37_IDI_LEN];		/* initial domain identifier */
	u_char a37_dsp[ADDR37_DSP_LEN];		/* domain specific part */
};
E 3

D 3
struct ovl_37 {	/* overlay for type 37 address */
	u_char	o37_afi;					/* afi */
	u_char	o37_x121[ADDR37_IDI_LEN];	/* X.121 address */
	u_char	o37_dsp[ADDR37_DSP_LEN];	/* unknown use at this time */
};
E 3

D 3
/*
 *	OSINET address
 *
 *	This style address is used by the OSINET group
 *	An OSINET address has the following (variable-length) format
 *
 *  <----- idp ------->  <---------------- dsp --------------------------->
 *  <- afi -> <- idi ->  <---------------- dsp --------------------------->
 *  | "47"   | "0004"   |             11 bytes                            |
 *  |  afi(1)| osinetid | orgid(2) | subnet id(2) | (4-8) | nsap sel(1) |
 *
 *	the afi, orgid, and subnet id are considered the "network" portion of
 *	the address.
 */
#ifdef BIGSOCKADDRS
#define ADDROSINET_IDI_LEN		2
#define ADDROSINET_DSP_LEN		11
#else
#define ADDROSINET_IDI_LEN		2
#define ADDROSINET_DSP_LEN		8		/* this is a lie to fit in sockaddr */
#endif BIGSOCKADDRS
struct addr_osinet {
	u_char aosi_idi[ADDROSINET_IDI_LEN];		/* initial domain identifier */
	u_char aosi_dsp[ADDROSINET_DSP_LEN];		/* domain specific part */
};

#define	OVLOSINET_ID_LEN		2
#ifdef BIGSOCKADDRS
#define	OVLOSINET_ORGID_LEN		2
#define	OVLOSINET_SNETID_LEN	2
#define	OVLOSINET_SNPA_LEN		8
#define	OVLOSINET_NSAP_LEN		1
#else
#define	OVLOSINET_ORGID_LEN		2
#define	OVLOSINET_SNETID_LEN	2
#define	OVLOSINET_SNPA_LEN		5		/* this is a lie to fit in sockaddr */
#define	OVLOSINET_NSAP_LEN		1
#endif BIGSOCKADDRS
struct ovl_osinet { /* overlay for osinet address */
	u_char	oosi_afi;							/* afi */
	u_char	oosi_id[OVLOSINET_ID_LEN];			/* osinet id */
	u_char	oosi_orgid[OVLOSINET_ORGID_LEN];	/* orgid */
	u_char	oosi_snetid[OVLOSINET_SNETID_LEN];	/* subnet id */
	u_char	oosi_snpa[OVLOSINET_SNPA_LEN];		/* snpa */
	u_char	oosi_nsap[OVLOSINET_NSAP_LEN];		/* nsap sel */
};

/*
 *	RFC 986 address
 *
 *	This style address is used when DOD internet addresses are used
 *	The format of rfc986 addresses is:
 *
 *  <----- idp -------> <---------------- dsp -------------------->
 *  <- afi -> <- idi -> <---------------- dsp -------------------->
 *  | "47"   | "0006"  |             6 bytes                       |
 *  |  afi(1)| idi(2)  | version (1) | inet addr (4) | proto id(1) |
 *
 *	the afi, idi, and network portion of the inet address are considered 
 *	the "network" portion of the address.
 */
#define ADDRRFC986_IDI_LEN		2
#define ADDRRFC986_DSP_LEN		6
struct addr_rfc986 {
	u_char	a986_idi[ADDRRFC986_IDI_LEN];		/* initial domain identifier */
	u_char	a986_dsp[ADDRRFC986_DSP_LEN];		/* domain specific part */
};

#define	OVLRFC986_INET_LEN		4
struct ovl_rfc986 {
	u_char	o986_afi;							/* afi */
	u_char	o986_idi[ADDRRFC986_IDI_LEN];		/* idi */
	u_char	o986_vers;							/* version */
	u_char	o986_inetaddr[OVLRFC986_INET_LEN];	/* internet address */
	u_char	o986_upid;							/* upper protocol id */
};
#define RFC986V1				0x01			/* version of 986 addr */

#define	AFI_37		0x37	/* bcd of "37" */
#define AFI_OSINET	0x47	/* bcd of "47" */
#define AFI_RFC986	0x47	/* bcd of "47" */
#define	AFI_SNA		0x00	/* SubNetwork Address; invalid really...
								- used by ES-IS */

/* the idi for type 37 addresses is very different than the others */
#define	IDI_OSINET	0x0004	/* bcd of "0004" */	
#define	IDI_RFC986	0x0006	/* bcd of "0006" */

/*
 *	This address type is used to store a subnetwork address in a 
 *	sockaddr_iso. The isoa_len field should contain the length of the
 *	subnetwork address plus the length of the afi (ie +1 ).
 *
 *	This address format is used only by the ES-IS protocol
 */
#define	ADDRSNA_IDI_LEN		7
struct addr_sn {
	char	sna_addr[ADDRSNA_IDI_LEN];		/* subnetwork address */
};

/* 
 *	Type 47 is the biggest address: 11 bytes. The length of iso_addr
 *	is 13 bytes.
 */
D 2
struct iso_addr {
E 2
I 2
struct old_iso_addr {
E 2
	u_char	isoa_afi;						/* authority and format id */
	union {
		struct addr_37		addr_37;		/* type 37 */
		struct addr_osinet	addr_osinet;	/* type osinet */
		struct addr_rfc986	addr_rfc986;	/* type rfc986 */
		struct addr_sn		addr_sn;		/* subnetwork address */
	} 		isoa_u;
	u_char	isoa_len;						/* length (in bytes) */
};

E 3
I 2
/* The following looks like a sockaddr
D 3
 * in case we decide to use tree routines */
E 3
I 3
 * to facilitate using tree lookup routines */
E 3
struct iso_addr {
	u_char	isoa_len;						/* length (in bytes) */
	char	isoa_genaddr[20];				/* general opaque address */
};

E 2
D 3
#define t37_idi		isoa_u.addr_37.a37_idi
#define	t37_dsp		isoa_u.addr_37.a37_dsp
#define osinet_idi	isoa_u.addr_osinet.aosi_idi
#define	osinet_dsp	isoa_u.addr_osinet.aosi_dsp
#define	rfc986_idi	isoa_u.addr_rfc986.a986_idi
#define	rfc986_dsp	isoa_u.addr_rfc986.a986_dsp
#define sna_idi		isoa_u.addr_sn.sna_addr

/*
 *	An iso_addr is 18 bytes, a sockaddr_iso is therefore 20 bytes.
 *	the struct sockaddr data field has been changed to 22 bytes.
 *
 * severly changed osinet and t37 addresses from argo code, we don't want
 * sockaddrs to grow bigger than the original 16 bytes so we changed the 
 * t37 and osinet addresses so that they were only 10 bytes long
 */
E 3
struct sockaddr_iso {
D 2
	u_short 			siso_family;		/* family */
	u_short 			siso_tsuffix;		/* transport suffix */
E 2
I 2
	u_char	 			siso_len;			/* length */
	u_char	 			siso_family;		/* family */
D 3
	u_char				siso_ssuffixlen;	/* session suffix len */
	u_char				siso_tsuffixlen;	/* transport suffix len */
/*  u_char				siso_nsaptype;		/* someday?? */
E 3
I 3
	u_char				siso_plen;			/* presentation selector length */
	u_char				siso_slen;			/* session selector length */
	u_char				siso_tlen;			/* transport selector length */
E 3
E 2
	struct 	iso_addr	siso_addr;			/* network address */
I 2
D 3
	u_char				siso_pad[3];		/* make multiple of sizeof long */
E 3
I 3
	u_char				siso_pad[6];		/* space for gosip v2 sels */
											/* makes struct 32 bytes long */
E 3
E 2
};
D 3

I 2
#define siso_data siso_addr.isoa_genaddr
E 3
#define siso_nlen siso_addr.isoa_len
I 3
#define siso_data siso_addr.isoa_genaddr

E 3
#define TSEL(s) ((caddr_t)((s)->siso_data + (s)->siso_nlen))

#define SAME_ISOADDR(a, b) \
D 11
	(bcmp((a)->siso_data, (b)->siso_data, (unsigned)(a)->siso_nlen)==0)
E 11
I 11
	(bcmp((a)->siso_data, (b)->siso_data, (unsigned)(a)->siso_nlen) == 0)
#define SAME_ISOIFADDR(a, b)  (bcmp((a)->siso_data, (b)->siso_data, \
	(unsigned)((b)->siso_nlen - (b)->siso_tlen)) == 0)
E 11
I 3
/*
 * The following are specific values for siso->siso_data[0],
 * otherwise known as the AFI:
 */
#define	AFI_37		0x37	/* bcd of "37" */
#define AFI_OSINET	0x47	/* bcd of "47" */
#define AFI_RFC986	0x47	/* bcd of "47" */
#define	AFI_SNA		0x00	/* SubNetwork Address; invalid really...*/
E 3

E 2
D 3
#define NSAPTYPE_UNKNOWN	-1
#define NSAPTYPE_INET 		0
#define NSAPTYPE_X121BCD	1
#define NSAPTYPE_X121BIN	2
#define NSAPTYPE_DCCBCD		3
#define NSAPTYPE_DCCBIN		4
#define NSAPTYPE_OSINET 	5
#define NSAPTYPE_RFC986 	6

E 3
#ifdef KERNEL

extern int iso_netmatch();
extern int iso_hash(); 
extern int iso_addrmatch();
extern struct iso_ifaddr *iso_iaonnetof();
extern	struct domain isodomain;
extern	struct protosw isosw[];

#else
/* user utilities definitions from the iso library */

D 5
char *iso_ntoa();
E 5
I 5
#include <sys/cdefs.h>

__BEGIN_DECLS
struct iso_addr *iso_addr __P((const char *));
char *iso_ntoa __P((const struct iso_addr *));

/* THESE DON'T EXIST YET */
E 5
struct hostent *iso_gethostbyname(), *iso_gethostbyaddr();
I 5
__END_DECLS
E 5

D 5
#endif KERNEL
E 5
I 5
#endif /* KERNEL */
E 5

D 3
#endif __ISO__
E 3
I 2
#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
I 3
D 9
#endif __ISO__
E 9
I 9
#endif /* __ISO__ */
E 9
E 3
E 2
E 1
