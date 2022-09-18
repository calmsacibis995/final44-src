/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_slvar.h,v $
 * Revision 2.2  92/02/11  17:58:25  mja
 * 	Created for MACH sl support.
 * 	[92/02/05            berman]
 * 
 */
/*
 * Definitions for SLIP interface data structures
 * 
 * (this exists so programs like slstats can get at the definition
 *  of sl_softc.)
 *
 * $Header: if_slvar.h,v 2.2 92/02/11 17:58:25 mja Exp $
 *
 * Copyright (c) 1989 Regents of the University of California.
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
 *	Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
 *	- Initial distribution.
 */
struct sl_softc {
	struct ifnet sc_if;	/* network-visible interface */
	struct ifqueue sc_fastq; /* interactive output queue */
	struct tty *sc_ttyp;	/* pointer to tty structure */
	u_char *sc_mp;		/* pointer to next available buf char */
	u_char *sc_ep;		/* pointer to last available buf char */
	u_char *sc_buf;		/* input buffer */
	u_int sc_escape;	/* =1 if last char input was FRAME_ESCAPE */
	u_int sc_bytessent;
	u_int sc_bytesrcvd;
	struct slcompress sc_comp; /* tcp compression data */
};

/*
 * There are three per-line options kept in the device specific part
 * of the interface flags word:  IFF_D1 enables compression; IFF_D2
 * enables compression if a compressed packet is received from the
 * other side; IFF_D3 will drop (not send) ICMP packets.
 */
#ifndef IFF_D1
/*
 * This system doesn't have defines for device specific interface flags,
 * Define them.
 */
#define IFF_D1	0x8000
#define IFF_D2	0x4000
#define IFF_D3	0x2000
#endif
