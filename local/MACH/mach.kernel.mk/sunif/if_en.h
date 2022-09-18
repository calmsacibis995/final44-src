/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_en.h,v $
 * Revision 2.3  89/03/09  21:51:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:02:11  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)if_en.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Structure of a Ethernet header.
 */
struct	en_header {
	u_char	en_dhost;
	u_char	en_shost;
	u_short	en_type;
};

#define ENPUP_PUPTYPE	0x0200		/* PUP protocol */
#define ENPUP_IPTYPE	0x0201		/* IP protocol */

/*
 * The ENPUP_NTRAILER packet types starting at ENPUP_TRAIL have
 * (type-ENPUP_TRAIL)*512 bytes of data followed
 * by a PUP type (as given above) and then the (variable-length) header.
 */
#define ENPUP_TRAIL	0x1000		/* Trailer PUP */
#define ENPUP_NTRAILER	16
