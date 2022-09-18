/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_en.h,v $
 * Revision 2.4  89/03/09  22:25:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  10:52:46  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/24  03:04:38  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  23:09:59  mwyoung]
 * 
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 13-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  Added ENTYPE_ARP definition.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)if_en.h	7.1 (Berkeley) 6/5/86
 */
 

/*
 * Structure of a Ethernet header.
 */
struct	en_header {
	u_char	en_shost;
	u_char	en_dhost;
	u_short	en_type;
};

#define ENTYPE_PUP	0x0200		/* PUP protocol */
#define ENTYPE_IP	0x0201		/* IP protocol */
#ifdef	MACH
#define ENTYPE_ARP	0x0207		/* ARP protocol (CMU) */
#endif	MACH

/*
 * The ENTYPE_NTRAILER packet types starting at
 * ENTYPE_TRAIL have (type-ENTYPE_TRAIL)*512 bytes
 * of data followed by an Ethernet type (as given above)
 * and then the (variable-length) header.
 */
#define ENTYPE_TRAIL	0x1000		/* Trailer type */
#define ENTYPE_NTRAILER	16

#define EN_BROADCAST	0		/* Hardware broadcast address */
