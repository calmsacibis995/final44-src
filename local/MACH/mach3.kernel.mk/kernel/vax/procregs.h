/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * VAX internal processor registers.
 */

#define	KSP	0x0		/* kernel stack pointer */
#define	ESP	0x1		/* executive stack pointer */
#define	SSP	0x2		/* supervisor stack pointer */
#define	USP	0x3		/* user stack pointer */
#define	ISP	0x4		/* interrupt stack pointer */
/*		0x5 */
/*		0x6 */
/*		0x7 */

#define	P0BR	0x8		/* p0 region base pointer */
#define	P0LR	0x9		/* p0 region length register */
#define	P1BR	0xa		/* p1 region base pointer */
#define	P1LR	0xb		/* p1 region length register */
#define	SBR	0xc		/* system base register */
#define	SLR	0xd		/* system length register */
/*		0xe */
/*		0xf */

#define	PCBB	0x10		/* process control block base */
#define	SCBB	0x11		/* system control block base */
#define	IPLR	0x12		/* interrupt priority level register */
#define	ASTLVL	0x13		/* asynchronous system trap level */
#define	SIRR	0x14		/* software interrupt request register */
#define	SISR	0x15		/* software interrupt summary register */
#define	IPIR	0x16		/* interprocessor interrupt register:
				   8200 only */
#define	CMIERR	0x17		/* CMI error register:
				   730/750 only */

#define	ICCS	0x18		/* interval clock control register:
				   enable-bit only on 630/650/6200 */
#define	NICR	0x19		/* next interval count register:
				   not on 630/650/6200 */
#define	ICR	0x1a		/* interval count register:
				   not on 630/650/6200 */
#define	TODR	0x1b		/* time-of-day counter register:
				   not on 630/8800 */
#define	CSRS	0x1c		/* console storage receiver status:
				   730/750 only */
#define	CSRD	0x1d		/* console storage receiver data:
				   730/750 only */
#define	CSTS	0x1e		/* console storage transmit status:
				   730/750 only */
#define	CSTD	0x1f		/* console storage transmit data:
				   730/750 only */

#define	RXCS	0x20		/* console receive control/status */
#define	RXDB	0x21		/* console receive data buffer */
#define	TXCS	0x22		/* console transmit control/status */
#define	TXDB	0x23		/* console transmit data buffer */
#define	TBDR	0x24		/* translation buffer disable register:
				   not on 630/650/6200 */
#define	CADR	0x25		/* cache disable register:
				   not on 780/8600/630 */
#define	MCESR	0x26		/* machine check error summary register:
				   not on 630/650/6200 */
#define	MCSTS	0x26		/* machine check status register:
				   8800 */
#define	CAER	0x27		/* cache error register:
				   750 only */
#define	MSER	0x27		/* memory system error:
				   650/6200 */
#define	ACCS	0x28		/* FP accelerator control/status:
				   780/8600/8200 only */
#define	ACCR	0x29		/* FP accelerator maintenance:
				   780 only */
#define	SAVISP	0x29		/* console saved ISP:
				   630 only */
#define	SAVPC	0x2a		/* console saved PC:
				   630/650/6200 */
#define	SAVPSL	0x2b		/* console saved PSL:
				   630/650/6200 */
#define	WCSA	0x2c		/* writeable control store address:
				   750/780/8600/8200 */
#define	WCSD	0x2d		/* writeable control store data:
				   750/780/8600/8200 */
#define	WCSL	0x2e		/* writeable control store load:
				   8200 only */
/*		0x2f */

#define	SBIFS	0x30		/* SBI fault/status:
				   780 only */
#define	SBIS	0x31		/* SBI silo:
				   780 only */
#define	SBISC	0x32		/* SBI silo comparator:
				   780 only */
#define	SBIMT	0x33		/* SBI maintenance:
				   780 only */
#define	SBIER	0x34		/* SBI error register:
				   780 only */
#define	SBITA	0x35		/* SBI timeout address register:
				   780 only */
#define	SBIQC	0x36		/* SBI quadword clear:
				   780 only */
#define	IORESET	0x37		/* IO bus reset */

#define	MAPEN	0x38		/* memory management enable */
#define	TBIA	0x39		/* translation buffer invalidate all */
#define	TBIS	0x3a		/* translation buffer invalidate single */
#define	TBDATA	0x3b		/* translation buffer data:
				/* not on 630/650/6200 */
#define	MBRK	0x3c		/* microprogram break:
				   750/780 only */
#define	PMR	0x3d		/* performance monitor enable:
				/* not on 630/650/6200 */
#define	SID	0x3e		/* system identification */
#define	TBCHK	0x3f		/* translation buffer check */

				/* IPRs 40..4f are only for the 8600 */
#define	PAMACC	0x40		/* PAMM access */
#define	PAMLOC	0x41		/* PAMM location */
#define	CSWP	0x42		/* cache sweep */
#define	MDECC	0x44		/* MBox data ECC register */
#define	MENA	0x44		/* MBox error enable register */
#define	MDCTL	0x45		/* MBox data control register */
#define	MCCTL	0x46		/* MBox mcc control register */
#define	MERG	0x47		/* MBox error generator register */
#define	CRBT	0x48		/* console reboot */
#define	DFI	0x49		/* diagnostic fault insertion register */
#define	EHSR	0x4a		/* error handling status register */
/*		0x4b */
#define	STXCS	0x4c		/* console block storage control/status */
#define	STXDB	0x4d		/* console block storage data buffer */
#define	ESPA	0x4e		/* EBox scratchpad address register */
#define	ESPD	0x4f		/* EBox scratchpad data register */

				/* registers 0x50..0x5f are only for 8200 */
#define	RXCS1	0x50		/* serial-line 1 receive control/status */
#define	RXDB1	0x51		/* serial-line 1 receive data buffer */
#define	TXCS1	0x52		/* serial-line 1 transmit control/status */
#define	TXDB1	0x53		/* serial-line 1 transmit data buffer */
#define	RXCS2	0x54		/* serial-line 2 receive control/status */
#define	RXDB2	0x55		/* serial-line 2 receive data buffer */
#define	TXCS2	0x56		/* serial-line 2 transmit control/status */
#define	TXDB2	0x57		/* serial-line 2 transmit data buffer */
#define	RXCS3	0x58		/* serial-line 3 receive control/status */
#define	RXDB3	0x59		/* serial-line 3 receive data buffer */
#define	TXCS3	0x5a		/* serial-line 3 transmit control/status */
#define	TXDB3	0x5b		/* serial-line 3 transmit data buffer */
#define	RXCD	0x5c		/* receive console data register */
#define	CACHEX	0x5d		/* cache invalidate register */
#define	BINID	0x5e		/* VAXBI node ID register */
#define	BISTOP	0x5f		/* VAXBI stop register */

				/* registers 80..88 are only for 8800 */
#define	NICTRL	0x80		/* NMI control register */
#define	INOP	0x81		/* interrupt other processor */
#define	NMIFSR	0x82		/* NMI Fault status register */
#define	NMISILO	0x83		/* NMI silo register */
#define	NMIEAR	0x84		/* NMI error address register */
#define	COR	0x85		/* cache-on register */
#define	REVR1	0x86		/* Revision register 1 */
#define	REVR2	0x87		/* Revision register 2 */
#define	TOSTS	0x88		/* time-out status */
