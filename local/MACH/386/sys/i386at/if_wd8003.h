/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	if_wd8003.h,v $
 * Revision 2.1.1.4  91/01/11  08:59:12  rvb
 * 	wd8003 definitions only.  flush ns8390 stuff
 * 
 * 
 * Revision 2.3.1.1  91/01/04  12:20:35  rvb
 * 	Flush generic NS8390 defines to an NS8390 header file.
 * 
 * Revision 2.1.1.3  90/11/27  13:43:32  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.1.1.3) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/10/01  14:23:27  jeffreyh
 * Revision 2.1  90/09/26  10:33:25  jeffreyh
 * Created.
 * 	[90/09/26  10:34:39  jeffreyh]

 * Revision 2.1.1.2  90/07/27  11:25:45  rvb
 * 	Add boardID definitions.		[rweiss]
 * 
 * Revision 2.1.1.1  90/07/10  11:45:00  rvb
 * 	Added to system.
 * 	[90/07/06            rvb]
 * 
 */

/*
 * Western Digital Mach Ethernet driver
 * Copyright (c) 1990 OSF Research Institute 
 */
/*
  Copyright 1990 by Open Software Foundation,
Cambridge, MA.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appears in all copies and
that both the copyright notice and this permission notice appear in
supporting documentation, and that the name of OSF or Open Software
Foundation not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

  OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/


/***********************************************************/
/*  Defines for the 583 chip.                              */
/***********************************************************/

/*--- 8390 Registers ---*/
#define OFF_8390	0x10	/* offset of the 8390 chip */


/*--- 83c583 registers ---*/
#define MSR	0x00		/* memory select register */
#define ICR	0x01		/* interface configuration register */
#define IAR	0x02		/* io address register */
#define BIO	0x03		/* bios ROM address register */
#define IRR	0x04		/* interrupt request register */
#define GP1	0x05		/* general purpose register 1 */
#define IOD	0x06		/* io data latch */
#define GP2	0x07		/* general purpose register 2 */
#define LAR	0x08		/* LAN address register	*/
#define LAR2	0x09		/*			*/
#define LAR3	0x0A		/*			*/
#define LAR4	0x0B		/*			*/
#define LAR5	0x0C		/*			*/
#define LAR6	0x0D		/*			*/
#define LAR7	0x0E		/*			*/
#define LAR8	0x0F		/* LAN address register */

/********************* Register Bit Definitions **************************/
/* MSR definitions */
/* defined: #define RST	     0x80	        1 => reset */
#define MENB	0x40		/* 1 => memory enable */
#define SA18	0x20		/* Memory enable bits	*/
#define	SA17	0x10		/*	telling where shared	*/
#define	SA16	0x08		/*	mem is to start.	*/
#define SA15	0x04		/*	Assume SA19 = 1		*/
#define SA14	0x02		/*				*/
#define	SA13	0x01		/*				*/

/* ICR definitions */
#define	STR	0x80		/* Non-volatile EEPROM store	*/
#define	RCL	0x40		/* Recall I/O Address from EEPROM */
#define	RX7	0x20		/* Recall all but I/O and LAN address */
#define RLA	0x10		/* Recall LAN Address	*/
#define	MSZ	0x08		/* Shared Memory Size	*/
#define	DMAE	0x04		/* DMA Enable	*/
#define	IOPE	0x02		/* I/O Port Enable */
/* defined #define WTS	     0x01		 Word Transfer Select */

/* IAR definitions */
#define	IA15	0x80		/* I/O Address Bits	*/
/*	.		*/
/*	.		*/
/*	.		*/
#define	IA5	0x01		/*			*/

/* BIO definitions */
#define	RS1	0x80		/* BIOS size bit 1 */
#define	RS0	0x40		/* BIOS size bit 0 */
#define	BA18	0x20		/* BIOS ROM Memory Address Bits */
#define	BA17	0x10		/*				*/
#define	BA16	0x08		/*				*/
#define	BA15	0x04		/*				*/
#define BA14	0x02		/* BIOS ROM Memory Address Bits */
#define	WINT	0x01		/* W8003 interrupt	*/

/* IRR definitions */
#define	IEN	0x80		/* Interrupt Enable	*/
#define	IR1	0x40		/* Interrupt request bit 1	*/
#define	IR0	0x20		/* Interrupt request bit 0	*/
#define	AMD	0x10		/* Alternate mode	*/
#define AINT	0x08		/* Alternate interrupt	*/
#define BW1	0x04		/* BIOS Wait State Control bit 1	*/
#define BW0	0x02		/* BIOS Wait State Control bit 0	*/
#define OWS	0x01		/* Zero Wait State Enable	*/

/* GP1 definitions */

/* IOD definitions */

/* GP2 definitions */


/*************************************************************/
/*   Shared RAM buffer definitions                           */
/*************************************************************/


/**** Western digital node bytes ****/
#define	WD_NODE_ADDR_0	0x00
#define	WD_NODE_ADDR_1	0x00
#define	WD_NODE_ADDR_2	0xC0

/**** NIC definitions ****/
#define NIC_8003_SRAM_SIZE 0x2000       /* size of shared RAM buffer */
#define	NIC_HEADER_SIZE	4		/* size of receive header */
#define	NIC_PAGE_SIZE	0x100		/* each page of rcv ring is 256 byte */

/* #define NWD8003         1 */
#define ETHER_ADDR_SIZE	6	/* size of a MAC address */

#ifndef TRUE
#define TRUE		1
#endif	TRUE

#ifdef MACH
#define	HZ		100
#endif

#define	DSF_LOCK	1
#define DSF_RUNNING	2

#define MOD_ENAL 1
#define MOD_PROM 2



/*****************************************************************************
 *                                                                           *
 *   Definitions for board ID.                                               *
 *                                                                           *
 *   note: board ID should be ANDed with the STATIC_ID_MASK                  *
 *         before comparing to a specific board ID                           *
 *	   The high order 16 bits correspond to the Extra Bits which do not  *
 *         change the boards ID.                                             *
 *                                                                           *
 *   Note: not all are implemented.  Rest are here for future enhancements...*
 *                                                                           *
 *****************************************************************************/


#define	STARLAN_MEDIA		0x00000001
#define	ETHERNET_MEDIA		0x00000002
#define	TWISTED_PAIR_MEDIA	0x00000003
#define	MICROCHANNEL		0x00000008
#define	INTERFACE_CHIP		0x00000010
#define	INTELLIGENT		0x00000020
#define	BOARD_16BIT		0x00000040
#define	RAM_SIZE_UNKNOWN	0x00000000	/* 000 => Unknown RAM Size */
#define	RAM_SIZE_RESERVED_1	0x00010000	/* 001 => Reserved */
#define	RAM_SIZE_8K		0x00020000	/* 010 => 8k RAM */
#define	RAM_SIZE_16K		0x00030000	/* 011 => 16k RAM */
#define	RAM_SIZE_32K		0x00040000	/* 100 => 32k RAM */
#define	RAM_SIZE_64K		0x00050000	/* 101 => 64k RAM */ 
#define	RAM_SIZE_RESERVED_6	0x00060000	/* 110 => Reserved */ 
#define	RAM_SIZE_RESERVED_7	0x00070000	/* 111 => Reserved */ 
#define	SLOT_16BIT		0x00080000
#define	NIC_690_BIT		0x00100000
#define	ALTERNATE_IRQ_BIT	0x00200000

#define	MEDIA_MASK		0x00000007
#define	RAM_SIZE_MASK		0x00070000
#define	STATIC_ID_MASK		0x0000FFFF

/* Word definitions for board types */
#define	WD8003E		ETHERNET_MEDIA
#define	WD8003EBT	WD8003E		/* functionally identical to WD8003E */
#define	WD8003S		STARLAN_MEDIA
#define	WD8003SH	WD8003S		/* functionally identical to WD8003S */
#define	WD8003WT	TWISTED_PAIR_MEDIA
#define	WD8003W		(TWISTED_PAIR_MEDIA | INTERFACE_CHIP)
#define	WD8003EB	(ETHERNET_MEDIA | INTERFACE_CHIP)
#define	WD8003ETA	(ETHERNET_MEDIA | MICROCHANNEL)
#define	WD8003STA	(STARLAN_MEDIA | MICROCHANNEL)
#define	WD8003EA	(ETHERNET_MEDIA | MICROCHANNEL | INTERFACE_CHIP)
#define	WD8003SHA	(STARLAN_MEDIA | MICROCHANNEL | INTERFACE_CHIP)
#define	WD8003WA	(TWISTED_PAIR_MEDIA | MICROCHANNEL | INTERFACE_CHIP)
#define	WD8013EBT	(ETHERNET_MEDIA | BOARD_16BIT)
#define	WD8013EB	(ETHERNET_MEDIA | BOARD_16BIT | INTERFACE_CHIP)
#define	WD8023E		(ETHERNET_MEDIA | INTELLIGENT | INTERFACE_CHIP)

#define BID_SIXTEEN_BIT_BIT  0x01

#define REG_0            0x00
#define REG_1            0x01
#define REG_2            0x02

#define BOARD_ID_BYTE    0x0E
#define BID_REV_MASK     0x1E
#define BID_MSZ_583      0x08    /* memory size mask for 583 interface chip */
#define BID_RAM_SIZE_BIT 0x40


/***************************/
/* Specific to the 8013EBT */
/****************************/

/***** 83c583 registers *****/

#define BSR        0x01         /* Bus Size Register (read only) */
#define LAAR       0x05         /* LA Address Register */

/***** BSR Defs ****/

#define BUS16BIT   0x01         /* Bit 0 tells if the bus is 16 bit */


/**** LAAR Definitions ****/
#define	MEM16ENB	0x80		/* Enables 16bit shrd RAM for host */
#define	LAN16ENB	0x40		/* Enables 16bit shrd RAM for LAN */
#define SOFTINT         0x20            /* Enable interrupt from pc */
#define	LA23		0x10		/* Address lines for enabling */
#define	LA22		0x08		/*    shared RAM above 1Mbyte */
#define	LA21		0x04		/*    in host memory */
#define	LA20		0x02
#define	LA19		0x01
