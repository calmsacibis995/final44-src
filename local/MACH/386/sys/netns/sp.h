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
 * $Log:	sp.h,v $
 * Revision 2.3  89/03/09  20:53:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:08:22  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)sp.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Definitions for Xerox NS style sequenced packet protocol
 */

struct sphdr {
	u_char	sp_cc;		/* connection control */
	u_char	sp_dt;		/* datastream type */
#define SP_SP	0x80		/* system packet */
#define SP_SA	0x40		/* send acknowledgement */
#define SP_OB	0x20		/* attention (out of band data) */
#define SP_EM	0x10		/* end of message */
	u_short	sp_sid;		/* source connection identifier */
	u_short	sp_did;		/* destination connection identifier */
	u_short	sp_seq;		/* sequence number */
	u_short	sp_ack;		/* acknowledge number */
	u_short	sp_alo;		/* allocation number */
};
