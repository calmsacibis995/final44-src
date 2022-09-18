/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	endian.h,v $
 * Revision 2.1.1.2  91/05/03  10:57:00  rvb
 * 	Handle multiple inclusion and function prototypes
 * 	[91/05/03            rvb]
 * 
 * Revision 2.2  90/07/03  16:37:02  mrt
 * 	Created this to match the other machine/endian.h files as
 * 	expected by the Tahoe release of BSD.
 * 	[90/06/28            mrt]
 * 
 */
/*
 * Copyright (c) 1987 Regents of the University of California.
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
 *	@(#)endian.h	7.3 (Berkeley) 6/29/88
 */

#ifndef	BYTE_ORDER
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

#define	BYTE_ORDER	LITTLE_ENDIAN	/* byte order on i386 */

/*
 * Macros for network/external number representation conversion.
 */
#if BYTE_ORDER == BIG_ENDIAN && !defined(lint)
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)
#else
#if	defined(__STDC__)
unsigned short ntohs(u_short), htons(u_short);
unsigned short ntohl(u_long), htonl(u_long);
#else	/* __STDC__ */
unsigned short	ntohs(), htons();
unsigned long	ntohl(), htonl();
#endif	/* __STDC__ */
#endif  /* BYTE_ORDER == BIG_ENDIAN */
#endif	/* BYTE_ORDER */
