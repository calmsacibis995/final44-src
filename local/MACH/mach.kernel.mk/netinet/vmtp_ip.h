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
 * $Log:	vmtp_ip.h,v $
 * Revision 2.3  89/03/09  20:49:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:55  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */

#include <mach_vmtp.h>

/*
 * $ Header: vmtp_ip.h,v 2.1 87/08/14 15:44:12 mrt Exp $
 */

/*
 * 	vmtp_ip.h	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#ifndef	VMTP_IPH
#define VMTP_IPH


/* 
 * The difference between vh_length in vmtphdr and vh_len in vmtp_header.
 * vh_len is the length of the packet excluding the checksum (and 
 * the vmtp_header).
 * vh_length is the length of the packet excluding the checksum and the 
 * vh_client field.
 */
#define VH_DELTALEN		(sizeof(struct vmtpeid))

/*
 * Generic header to use with multiple underlying protocols.
 * It has the same size as the IP header, and an ethernet header fits in it.
 */
struct vmtp_header {
	struct ifnet	*vh_ifp;
	union vmtp_addr vh_addr;
	u_short		vh_type;  	/* Packet type (IP or ETHER types) */
	u_short		vh_len;
	u_short		vh_ttl;
	u_short		vh_multicast;	/* Multicast flag on reception */
};
#define vh_src	vh_addr
#define vh_dst	vh_addr


/*
 * VMTP+IP header, or VMTP+Ethernet header
 */
struct vmtpiphdr {
	struct vmtp_header	vi_hdr;	
	struct vmtphdr		vi_vmtp;	/* vmtp header */
};

#define vi_ifp		vi_hdr.vh_ifp
#define vi_addr		vi_hdr.vh_addr
#define vi_type		vi_hdr.vh_type
#define vi_len		vi_hdr.vh_len
#define vi_ttl		vi_hdr.vh_ttl
#define vi_multicast	vi_hdr.vh_multicast
#define vi_src		vi_addr

#define vi_client	vi_vmtp.vh_client
#define vi_transid	vi_vmtp.vh_transid
#define vi_dlvrmsk	vi_vmtp.vh_dlvrmsk
#define vi_server	vi_vmtp.vh_server
#define vi_ucb		vi_vmtp.vh_ucb
#define vi_code		vi_vmtp.vh_ucb.vu_code
#define vi_lasttrans	vi_vmtp.vh_ucb.vu_longdata[0]
#define vi_usrdlvrmsk	vi_vmtp.vh_ucb.vu_dlvrmsk
#define vi_segsize	vi_vmtp.vh_ucb.vu_segsize

#define getvi_version(vi)	getvh_version((vi)->vi_vmtp)
#define getvi_domain(vi)	getvh_domain((vi)->vi_vmtp)
#define getvi_length(vi)	getvh_length((vi)->vi_vmtp)
#define getvi_inpktgap(vi)	getvh_inpktgap((vi)->vi_vmtp)
#define getvi_priority(vi)	getvh_priority((vi)->vi_vmtp)
#define getvi_control(vi)	getvh_control((vi)->vi_vmtp)
#define getvi_fnctcode(vi)	getvh_fnctcode((vi)->vi_vmtp)
#define setvi_version(vi,val)	setvh_version((vi)->vi_vmtp,val)
#define setvi_domain(vi,val)	setvh_domain((vi)->vi_vmtp,val)
#define setvi_length(vi,val)	setvh_length((vi)->vi_vmtp,val)
#define setvi_inpktgap(vi,val)	setvh_inpktgap((vi)->vi_vmtp,val)
#define setvi_priority(vi,val)	setvh_priority((vi)->vi_vmtp,val)
#define setvi_control(vi,val)	setvh_control((vi)->vi_vmtp,val)
#define setvi_fnctcode(vi,val)	setvh_fnctcode((vi)->vi_vmtp,val)

#define orvi_control(vi,val)	orvh_control((vi)->vi_vmtp,val)
#define andvi_control(vi,val)	andvh_control((vi)->vi_vmtp,val)

#define getvi_pgcount(vi)	getvh_inpktgap((vi)->vi_vmtp)
#define setvi_pgcount(vi,val)	setvh_inpktgap((vi)->vi_vmtp,val)

#endif
