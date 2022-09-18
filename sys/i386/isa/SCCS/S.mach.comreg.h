h53778
s 00000/00002/00123
d D 5.2 90/11/07 11:57:10 bill 2 1
c config include does not belong here
e
s 00125/00000/00000
d D 5.1 90/06/23 19:13:14 donahn 1 0
c date and time created 90/06/23 19:13:14 by donahn
e
u
U
t
T
I 1
D 2
#include "com.h"
#if NCOM > 0
E 2
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Hacked up to work on BSD/386 by Don Ahn.
 *
 *	%W% (Berkeley) %G%
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	comreg.h,v $
 * Revision 2.3.1.2  90/02/28  15:49:16  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 2.3.1.1  90/01/08  13:30:02  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.3  89/09/09  15:21:09  rvb
 * 	com.h -> comreg.h; com.h is now used vs pccom.h for
 * 	configuration.
 * 	[89/09/09            rvb]
 * 
 * Revision 2.2  89/07/17  10:39:48  rvb
 * 	New from Oilvetti.
 * 
 */

/* 
 *	Olivetti serial port driver v1.0
 *	Copyright Ing. C. Olivetti & C. S.p.A. 1988, 1989
 *	All rights reserved.
 *
 */ 
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define MAX_COM_PORTS 	2
#define COM_PORTS	2
#define MAXTIME         2               /* 2 sec */

#define	uchar	u_char
#define	ushort	u_short

/* line control register */
#define		iWLS0	0x01		/*word length select bit 0 */	
#define		iWLS1	0x02		/*word length select bit 2 */	
#define		iSTB	0x04		/* number of stop bits */
#define		iPEN	0x08		/* parity enable */
#define		iEPS	0x10		/* even parity select */
#define		iSP	0x20		/* stick parity */
#define		iSETBREAK 0x40		/* break key */
#define		iDLAB	0x80		/* divisor latch access bit */
#define		i5BITS	0x00		/* 5 bits per char */
#define		i6BITS	0x01		/* 6 bits per char */
#define		i7BITS	0x02		/* 7 bits per char */
#define		i8BITS	0x03		/* 8 bits per char */

/* line status register */
#define		iDR	0x01		/* data ready */
#define		iOR	0x02		/* overrun error */
#define		iPE	0x04		/* parity error */
#define		iFE	0x08		/* framing error */
#define		iBRKINTR 0x10		/* a break has arrived */
#define		iTHRE	0x20		/* tx hold reg is now empty */
#define		iTSRE	0x40		/* tx shift reg is now empty */

/* interrupt id regisger */
#define		iMODEM_INTR	0x01
#define		iTX_INTR	0x02
#define		iRX_INTR	0x04
#define		iERROR_INTR	0x08

/* interrupt enable register */
#define		iRX_ENAB	0x01
#define		iTX_ENAB	0x02
#define		iERROR_ENAB	0x04
#define		iMODEM_ENAB	0x08

/* modem control register */
#define		iDTR		0x01	/* data terminal ready */
#define		iRTS		0x02	/* request to send */
#define		iOUT1		0x04	/* COM aux line -not used */
#define		iOUT2		0x08	/* turns intr to 386 on/off */	
#define		iLOOP		0x10	/* loopback for diagnostics */

/* modem status register */
#define		iDCTS		0x01	/* delta clear to send */
#define		iDDSR		0x02	/* delta data set ready */
#define		iTERI		0x04	/* trail edge ring indicator */
#define		iDRLSD		0x08	/* delta rx line sig detect */
#define		iCTS		0x10	/* clear to send */
#define		iDSR		0x20	/* data set ready */
#define		iRI		0x40	/* ring indicator */
#define		iRLSD		0x80	/* rx line sig detect */

E 1
