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
 * $Log:	esp_key.h,v $
 * Revision 2.3  89/03/09  20:41:53  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:51  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_key.h,v 2.1 87/08/18 16:30:51 mrt Exp $
 */

/*
 * 	esp_key.h			5/21/87
 * 	Written by Erik Nordmark
 */

/*
 * TODO
 */

/* 
 * The key storage/key cache
 */

struct espkeyst {
	struct princid	ek_clientp;	/* Client principal */
	struct princid	ek_serverp;	/* Server principal */
	int		ek_timelimit;
	int		ek_encryptqual;
	struct mbuf	*ek_authenticator;
	union vmtpkey	ek_key;
	u_char		ek_flags;	/* See below */
};

/*
 * Flags
 */
#define EKF_NONE	0
#define EKF_USED	0x1	/* Is entry used? */
#define EKF_HALFDEAD	0x2	/* For replacement */

#define ekf_used(ek)		((ek)->ek_flags & EKF_USED)
#define ekf_halfdead(ek)	((ek)->ek_flags & EKF_HALFDEAD)

#define ESP_KEYSTSIZE	16		/* Number of entries */

#ifdef	KERNEL
struct espkeyst 	ekeystorage[ESP_KEYSTSIZE];
#endif	KERNEL
