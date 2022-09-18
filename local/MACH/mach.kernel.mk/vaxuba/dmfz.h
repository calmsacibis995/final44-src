/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dmfz.h,v $
 * Revision 2.3  89/03/09  22:32:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:00:49  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Common structures and definitions
 * for merged DMF and DMZ drivers.
 */
struct octet {
	short	octcsr;			/* control-status register */
	short	octlpr;			/* line parameter register */
	short	octrbuf;		/* receiver buffer (ro) */
	union {
		u_short	octirw;		/* indirect register word */
		u_char	octirc[2];	/*    "         "    bytes */
	} octun;
};

#define octrsp	octrbuf		/* receive silo parameter register (wo) */
#define octtbuf	octun.octirc[0]	/* transmit buffer */
#define octtsc	octun.octirc[0]	/* transmit silo count */
#define octrms	octun.octirc[1]	/* receive modem status */
#define octlctms octun.octirw	/* line control, transmit modem status */
#define octtba	octun.octirw	/* transmit buffer address */
#define octtcc	octun.octirw	/* transmit character count */

/*
 * Software status per octet
 */

struct dfz_softc {
	char	dfz_flags;
	char	dfz_init;
};

