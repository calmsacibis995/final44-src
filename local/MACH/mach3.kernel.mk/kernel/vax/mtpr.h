/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mtpr.h,v $
 * Revision 2.3  91/06/19  12:01:30  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:50:07  rvb]
 * 
 * Revision 2.2  91/05/08  13:20:31  dbg
 * 	Add inline assembler definitions for GCC.
 * 	[91/02/19            dbg]
 * 
 * Revision 2.1.1.1  91/02/26  11:19:48  dbg
 * 	Add inline assembler definitions for GCC.
 * 	[91/02/19            dbg]
 * 
 * Revision 2.1  89/08/03  16:12:32  rwd
 * Created.
 * 
 * 11-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define all registers for independent of which VAXen the system
 *	is built for, since locore.s needs all the register definitions.
 *
 * 10-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	Changes for 650.
 *
 *  5-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	VAX-8800 support: added INOP register which is used to interrupt
 *	the other processor.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 15-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Define MicroVAX registers (same as those of 750 and 730).
 *
 */

#include <platforms.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mtpr.h	7.1 (Berkeley) 6/5/86
 */

#ifndef	_VAX_MTPR_H_
#define	_VAX_MTPR_H_

/*
 * VAX processor register numbers
 */

#define	KSP	0x0		/* kernel stack pointer */
#define	ESP	0x1		/* exec stack pointer */
#define	SSP	0x2		/* supervisor stack pointer */
#define	USP	0x3		/* user stack pointer */
#define	ISP	0x4		/* interrupt stack pointer */
#define	P0BR	0x8		/* p0 base register */
#define	P0LR	0x9		/* p0 length register */
#define	P1BR	0xa		/* p1 base register */
#define	P1LR	0xb		/* p1 length register */
#define	SBR	0xc		/* system segment base register */
#define	SLR	0xd		/* system segment length register */
#define	PCBB	0x10		/* process control block base */
#define	SCBB	0x11		/* system control block base */
#define	IPL	0x12		/* interrupt priority level */
#define	ASTLVL	0x13		/* async. system trap level */
#define	SIRR	0x14		/* software interrupt request */
#define	SISR	0x15		/* software interrupt summary */
#define	ICCS	0x18		/* interval clock control */
#define	NICR	0x19		/* next interval count */
#define	ICR	0x1a		/* interval count */
#define	TODR	0x1b		/* time of year (day) */
#define	RXCS	0x20		/* console receiver control and status */
#define	RXDB	0x21		/* console receiver data buffer */
#define	TXCS	0x22		/* console transmitter control and status */
#define	TXDB	0x23		/* console transmitter data buffer */
#define	MAPEN	0x38		/* memory management enable */
#define	TBIA	0x39		/* translation buffer invalidate all */
#define	TBIS	0x3a		/* translation buffer invalidate single */
#define	PMR	0x3d		/* performance monitor enable */
#define	SID	0x3e		/* system identification */

/*if defined(VAX780) || defined(VAX8600)*/
#define	ACCS	0x28		/* accelerator control and status */

/*if defined(VAX8600)*/
#define TBCHK	0x3f		/* Translation Buffer Check */
#define PAMACC	0x40		/* PAMM access */
#define PAMLOC	0x41		/* PAMM location */
#define CSWP	0x42		/* Cache sweep */
#define MDECC	0x43		/* MBOX data ecc register */
#define MENA	0x44		/* MBOX error enable register */
#define MDCTL	0x45		/* MBOX data control register */
#define MCCTL	0x46		/* MBOX mcc control register */
#define MERG	0x47		/* MBOX	error generator register */
#define CRBT	0x48		/* Console reboot */
#define DFI	0x49		/* Diag fault insertion register */
#define EHSR	0x4a		/* Error handling status register */
#define STXCS	0x4c		/* Console block storage C/S */
#define STXDB	0x4d		/* Console block storage D/B */
#define ESPA	0x4e		/* EBOX scratchpad address */
#define ESPD	0x4f		/* EBOX sratchpad data */

/*if defined(VAX780)*/
#define	ACCR	0x29		/* accelerator maintenance */
#define	WCSA	0x2c		/* WCS address */
#define	WCSD	0x2d		/* WCS data */
#define	SBIFS	0x30		/* SBI fault and status */
#define	SBIS	0x31		/* SBI silo */
#define	SBISC	0x32		/* SBI silo comparator */
#define	SBIMT	0x33		/* SBI maintenance */
#define	SBIER	0x34		/* SBI error register */
#define	SBITA	0x35		/* SBI timeout address */
#define	SBIQC	0x36		/* SBI quadword clear */
#define	MBRK	0x3c		/* micro-program breakpoint */

/*if 	defined(VAX650)*/
				/* the next four registers are class 5 */
				/* results may be UNPREDICTABLE */
#define	CSRS	0x1c		/* console storage receive status register */
#define	CSRD	0x1d		/* console storage receive data register */
#define	CSTS	0x1e		/* console storage transmit status register */
#define	CSTD	0x1f		/* console storage transmit data register */

#define	CADR	0x25		/* cache disable register */
#define MSER    0x27		/* memory system error register */
#define	IORESET	0x37		/* IO bus reset */
#define	IUR	0x37		/* IO bus reset -- used in some code */

/*if defined(VAX750) || defined(VAX730)*/
#define	MCSR	0x17		/* machine check status register */
#define	CSRS	0x1c		/* console storage receive status register */
#define	CSRD	0x1d		/* console storage receive data register */
#define	CSTS	0x1e		/* console storage transmit status register */
#define	CSTD	0x1f		/* console storage transmit data register */
#define	TBDR	0x24		/* translation buffer disable register */
#define	CADR	0x25		/* cache disable register */
#define	MCESR	0x26		/* machine check error summary register */
#define	CAER	0x27		/* cache error */
#define	IUR	0x37		/* init unibus register */
#define	TB	0x3b		/* translation buffer */

/*if	VAX820*/
/*if	!defined(VAX1) && !defined(VAX630) && !defined(VAX730) && !defined(VAX750)*/
#define	TBDR	0x24		/* translation buffer disable register */
#define	CADR	0x25		/* cache disable register */
#define	MCESR	0x26		/* machine check error summary register */

#define IPIR	0x16		/* Interprocessor Interrupt Register */
#define RXCD	0x5c		/* Receive Console Data Register */
#define	CACHEX	0x5d		/* cache invalidate register */
#define BINID	0x5e		/* VAXBI node ID register */
#define BISTOP	0x5f		/* VAXBI stop register */

/*if	VAX8800*/
#define MCSTS	0x26		/* machine check status register */
#define NMICTL	0x80		/* NMI control register */
#define INOP	0x81		/* 8800 interrupt other processor */
#define COR	0x85		/* Cache on register */
#define TOSTS	0x88		/* time out status */

#ifdef	__GNUC__

#define	mfpr(src) \
	({ int _value__; \
	asm volatile("mfpr %1, %0" \
		    : "=g" (_value__) \
		    : "g" ((int)(src)) ); \
	_value__; })

#define	mtpr(dst,value) \
	({ \
	asm volatile("mtpr %0, %1" \
		    : \
		    : "g" ((int)(value)), "g" ((int)(dst)) ); \
	0; })
				/* returns 0 to be thrown away */

#endif	/* __GNUC__ */

#endif	/* _VAX_MTPR_H_ */
