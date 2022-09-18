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
 * $Log:	if_lan.h,v $
 * Revision 2.3  89/03/09  20:43:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:16  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * 5799-CGZ (C) COPYRIGHT IBM CORPORATION 1987
 * LICENSED MATERIALS - PROPERTY OF IBM
 * REFER TO COPYRIGHT INSTRUCTIONS FORM NUMBER G120-2083
 */
/* $ Header: if_lan.h,v 2.1 87/10/01 08:18:33 mrt Exp $ */
/* $ ACIS:if_lan.h 9.0$ */
/* $ Source: /afs/cs/os/source/rcs/kernel/netinet/if_lan.h,v $ */

#if	!defined(lint) && !defined(LOCORE) && defined(RCS_HDRS)
static char *rcsidif_lan = "$ Header: if_lan.h,v 2.1 87/10/01 08:18:33 mrt Exp $";
#endif


/* Bridge and routing field parameters */
#define LAN_MAX_BRIDGE		8	/* maximum hop count */
#define LAN_RI_PRESENT		0x80	/* bit 0, byte 0 source address on for ri */
#define LAN_RCF_BROADCAST	0x8000	/* all-rings broadcast */
#define LAN_RCF_LEN_MASK 	0x1f00	/* length field in routing control */
#define LAN_RCF_DIRECTION	0x0080	/* routing direction bit */
#define LAN_RCF_FRAME2K		0x0020	/* max frame size */

#define LAN_L_ADDR	6
/* Lan header includes control fields, source and destination
 addresses, and llc fields: */
struct mac_hdr {
	char pcf0;
	char pcf1;
	char to_addr[LAN_L_ADDR];
	char from_addr[LAN_L_ADDR];
	unsigned short rcf;
	unsigned short rseg[LAN_MAX_BRIDGE];
};

#define MIN_MAC_HDR_SIZE 14	/* mac header size if no routing info */

