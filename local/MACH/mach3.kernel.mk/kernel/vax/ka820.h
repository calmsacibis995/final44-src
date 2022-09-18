/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	ka820.h,v $
 * Revision 2.3  91/05/14  17:44:08  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:18:31  dbg
 * 	Changed to new copyright.
 * 	[91/04/26  15:16:49  dbg]
 * 
 * Revision 2.1  89/08/03  16:36:50  rwd
 * Created.
 * 
 * Revision 2.2  88/08/10  10:50:33  rvb
 * Created.
 * 
 */

/*
 *	File:	ka820.h
 *	Author:	Robert V. Baron
 *
 *	Yet another strange new bus
 *	ALSO definitions for the cpu structures
 *
 */

#ifndef	_VAX_KA820_H_
#define	_VAX_KA820_H_

/*
 * 820 processor registers
 */
#define	TBDR	0x24		/* translation buffer disable register */
#define	CADR	0x25		/* cache disable register */
#define	MCESR	0x26		/* machine check error summary register */

#define IPIR	0x16		/* Interprocessor Interrupt Register */
#define RXCD	0x5c		/* Receive Console Data Register */
#define	CACHEX	0x5d		/* cache invalidate register */
#define BINID	0x5e		/* VAXBI node ID register */
#define BISTOP	0x5f		/* VAXBI stop register */

#define PCCSR_RSTRT_HLT		0x80000000
#define PCCSR_CNSL_LOG		0x40000000
#define PCCSR_CNSL_ENB		0x20000000
#define PCCSR_BI_RESET		0x10000000
#define PCCSR_SLO_ST		0x08000000
#define PCCSR_ENBAPT		0x04000000
#define PCCSR_STP		0x02000000
#define PCCSR_RUN		0x01000000
#define PCCSR_WWPE		0x00800000
#define PCCSR_EVLOCK		0x00400000
#define PCCSR_WRMEM		0x00200000
#define PCCSR_EVENT		0x001f0000
#define PCCSR_WWPO		0x00008000
#define PCCSR_PE		0x00004000
#define PCCSR_ENPIPE		0x00002000
#define PCCSR_TIMEOUT		0x00001000
#define PCCSR_CNSLIE		0x00000400
#define PCCSR_CLR_CNSL		0x00000200
#define PCCSR_CNSL_INTR		0x00000100
#define PCCSR_RXIE		0x00000080
#define PCCSR_CLRXIRQ		0x00000040
#define PCCSR_RXIRQ		0x00000020
#define PCCSR_CLRIPINTR		0x00000010
#define PCCSR_IPINTR		0x00000008
#define PCCSR_CRDIE		0x00000004
#define PCCSR_CLRCRD		0x00000002
#define PCCSR_CRD		0x00000001
#define PCCSR_ERR		0x00405000
#define PCCSR_RW		0x0380a482

#define PCCSR		"\20\40RSTRT_HLT\37CNSL_LOG\36CNSL_ENB\35BI_RESET\34SLO_ST\33ENBAPT\32STP\31RUN\
\30WWPE\27EVLOCK\26WRMEM\25\21EVENT\20WWPO\17PE\16ENPIPE\15TIMEOUT\13CNSLIE\12CLR_CNSL\11CNSL_INTR\
\10RXIE\07CLRXIRQ\06RXIRQ\05CLRIPINTR\04IPINTR\03CRDIE\02CLRCRD\01CRD"

#define KA820MCHK_NORETRY	0x40000000
#define KA820MCHK_BIERR		0x00400000
#define KA820MCHK_WRTMEM	0x00200000
#define KA820MCHK_EVENT		0x001f0000
#define KA820MCHK_DATAPE	0x00004000
#define KA820MCHK_BTBTAGPE	0x00000010
#define KA820MCHK_MTBMISS	0x00000008
#define KA820MCHK_CHETAGPE	0x00000004
#define KA820MCHK_PCERR		0x00000002
#define KA820MCHK_MARLCK	0x00000001

#define KA820MCHK	"\20\37NORETRY\27BIERR\26WRTMEM\25\21EVENT\17DATAPE\
\05BTBTAGPE\04MTBMISS\03CHETAGPE\02PCERR\01MARLCK"

#ifdef	KERNEL
#ifndef	ASSEMBLER

extern int *ka820_csr;
extern int *ka820_ber;

#endif	ASSEMBLER
#endif	KERNEL

#endif	/* _VAX_KA820_H_ */
