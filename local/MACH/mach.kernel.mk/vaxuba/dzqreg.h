/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dzqreg.h,v $
 * Revision 2.2  89/02/26  11:02:53  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*	dzqreg.h	0.1	85/10/14	*/

/* This device starts at 0160100, vec 300, ipl 7
 * device #35
 * This is the include file for the dzq-11 on RI-ASSY.
 * 85/10/14 - created by modifying dzreg.h - Phillip McKerrow.
 * dzq-11 registers and bits.
 */
struct dzqdevice {
	unsigned short dzqcsr;
	unsigned short dzqrbuf;
	unsigned short dzqtcr;
	unsigned short dzqtdr;
};

#define dzqlpr dzqrbuf
#define dzqmsr dzqtdr

/* interrupt request line numbers */
#define DZQ_LINE0	   0000
#define DZQ_LINE1	   0400
#define DZQ_LINE2	  01000
#define DZQ_LINE3	  01400

/* bits in dzqlpr - write only */
#define DZQ_7BIT	    020
#define DZQ_8BIT	    030
#define DZQ_STOPCODE	    040
#define DZQ_PARENAB	   0100
#define DZQ_ODDPAR	   0200
#define DZQ_SEL		     03		/* select line number */
#define DZQ_SEL0	     00		/* select line number */
#define DZQ_SEL1	     01
#define DZQ_SEL2	     02
#define DZQ_SEL3	     03
#define DZQ_B1200	  03400		/* baud rate selection */
#define DZQ_B9600	  07000
#define DZQ_B19200	  07400
#define DZQ_RXENAB	 010000

/* bits in dzqrbuf - read only */
#define DZQ_RXPE 	 010000
#define DZQ_RXFE	 020000
#define DZQ_RXDO	 040000
#define DZQ_RXERR	 070000		/* reception error */
#define DZQ_RXDVALD	0100000		/* valid data in buffer - fifo register */
#define DZQ_RXLINE	  01400		/* line character received on */
#define DZQ_RXDATA	   0377		/* received character */

/* bits in dzqcsr - read and write */
#define DZQ_MAINT	    010		/* loop back test only */
#define DZQ_CLR		    020		/* Reset dzq */
#define DZQ_MSE		    040		/* Master Scan Enable */
#define DZQ_RIE		   0100		/* Receiver Interrupt Enable */
#define DZQ_RDONE	   0200		/* Character Received */
#define DZQ_TLINE	  01400		/*Line number of the tx wanting service*/
#define DZQ_SAE		 010000		/* Silo Alarm Enable */
#define DZQ_SA		 020000		/* Silo Alarm */
#define DZQ_TIE		 040000		/* Transmit Interupt Enable */
#define DZQ_TRDY	0100000		/* Transmitter ready for next character */

/* bits in dzqtcr - read and write */
#define DZQ_TXEN0	     01		/* enable line 0 for transmission */
#define DZQ_TXEN1	     02
#define DZQ_TXEN2	     04
#define DZQ_TXEN3	    010
#define DZQ_TXDTR	  07400		/* data terminal ready for all lines */

/* flags for dzqmsr - read only */

/* flags for dzqtdr - write only */

#define DZQ_TXDATA	 000377		/* Character to be transmitted */
