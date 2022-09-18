/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka820.h,v $
 * Revision 2.4  89/03/09  22:30:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  10:58:44  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:50:33  rvb
 * 	Created.
 *
 */
/*
 *	File:	ka88.h
 *	Author:	Robert V. Baron
 *
 *	Yet another strange new bus
 *	ALSO definitions for the cpu structures
 */
/*
 * 820 processor registers
 */
#define TBDR	0x24		/* translation buffer disable register */
#define CADR	0x25		/* cache disable register */
#define MCESR	0x26		/* machine check error summary register */

#define IPIR	0x16		/* Interprocessor Interrupt Register */
#define RXCD	0x5c		/* Receive Console Data Register */
#define CACHEX	0x5d		/* cache invalidate register */
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

#endif	ASSEMBLER
#endif	KERNEL
