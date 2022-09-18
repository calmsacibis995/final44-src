/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pit.h,v $
 * Revision 2.2.1.3  90/07/27  11:24:50  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.2.1.2  90/07/10  11:42:43  rvb
 * 	Add iPSC2
 * 	Flush EXL references
 * 	[90/06/15            rvb]
 * 
 * Revision 2.2.1.1  90/01/08  13:29:00  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.2  89/09/25  12:32:44  rvb
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */

/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifdef	AT386
/* Definitions for 8254 Programmable Interrupt Timer ports on AT 386 */
#define PITCTR0_PORT	0x40		/* counter 0 port */	
#define PITCTR1_PORT	0x41		/* counter 1 port */	
#define PITCTR2_PORT	0x42		/* counter 2 port */	
#define PITCTL_PORT	0x43		/* PIT control port */
#define PITAUX_PORT	0x61		/* PIT auxiliary port */
#define CLKNUM		1193167		/* clock speed for timer */
#endif	AT386

#ifdef iPSC2
/* Definitions for 8254 Programmable Interrupt Timer ports on iPSC/2 */
#define PITCTR0_PORT    0xD0            /* counter 0 port */
#define PITCTR1_PORT    0xD2            /* counter 1 port */
#define PITCTR2_PORT    0xD4            /* counter 2 port */
#define PITCTL_PORT     0xD6            /* PIT control port */
#define CLKNUM          1000000         /* clock speed for timer */
#endif iPSC2

/* bits used in auxiliary control port for timer 2 */
#define PITAUX_GATE2	0x01		/* aux port, PIT gate 2 input */
#define PITAUX_OUT2	0x02		/* aux port, PIT clock out 2 enable */


/* Definitions for 8254 commands */

/* Following are used for Timer 0 */
#define PIT_C0          0x00            /* select counter 0 */
#define PIT_LOADMODE	0x30		/* load least significant byte followed
					 * by most significant byte */
#define PIT_NDIVMODE	0x04		/*divide by N counter */
#define PIT_SQUAREMODE	0x06		/* square-wave mode */

/* Used for Timer 1. Used for delay calculations in countdown mode */
#define PIT_C1          0x40            /* select counter 1 */
#define PIT_READMODE	0x30		/* read or load least significant byte
					 * followed by most significant byte */
#define PIT_RATEMODE	0x06		/* square-wave mode for USART */
