/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	idp.h,v $
 * Revision 2.4  90/07/03  16:44:52  mrt
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17            emg]
 * 
 */
/*
 * Copyright (c) 1984, 1985, 1986, 1987 Regents of the University of California.
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
 *	@(#)idp.h	7.3 (Berkeley) 6/29/88
 */

/*
 * Definitions for NS(tm) Internet Datagram Protocol
 */
struct idp {
	u_short	idp_sum;	/* Checksum */
	u_short	idp_len;	/* Length, in bytes, including header */
	u_char	idp_tc;		/* Transport Crontrol (i.e. hop count) */
	u_char	idp_pt;		/* Packet Type (i.e. level 2 protocol) */
	struct ns_addr	idp_dna;	/* Destination Network Address */
	struct ns_addr	idp_sna;	/* Source Network Address */
};
