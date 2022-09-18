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
 * $Log:	ka650.h,v $
 * Revision 2.5  89/03/09  22:16:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:20:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  02:59:55  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:59:29  mwyoung]
 * 
 * Revision 2.2  88/08/10  10:25:12  rvb
 * 	Moved processor registers here from mtpr.h
 * 	Created
 * 
 */

#include <cputypes.h>

/*
 * 650 processor registers
 */
				/* the next four registers are class 5 */
				/* results may be UNPREDICTABLE */
#define CSRS	0x1c		/* console storage receive status register */
#define CSRD	0x1d		/* console storage receive data register */
#define CSTS	0x1e		/* console storage transmit status register */
#define CSTD	0x1f		/* console storage transmit data register */

#define CADR	0x25		/* cache disable register */
#define MSER    0x27		/* memory system error register */
#define IORESET	0x37		/* IO bus reset */
#define IUR	0x37		/* IO bus reset -- used in some code */

#define ROM650_HALT	((caddr_t) 0x20040000)
#define ROM650_RUN	((caddr_t) 0x20060000)
#define ROM650_SIZE	(128*1024)

/* Bdr register bits */
#define KA650BDR_HLTENB	0x80
#define KA650BDR_BRS	0x70
#define KA650BDR_CPU	0x0c
#define KA650BDR_BDG	0x03

#define C2DIAG		((long)  0x10000000)
#define C2DIAG_SIZE	(64*1024)

#define SSC		((caddr_t) 0x20140000)
#define SSC_SIZE	0x800

#define C2CNTL		((struct ka650_cacr_bdr *)  0x20084000)
#define C2CNTL_SIZE	8

#define MEM_QBM		0xffff8000
#define MEM_QBM_SHFT	15

#define MEM_BANK	0x3c00000
#define MEM_BANK_SHFT	22
#define MEM_4MEG	4

#ifndef	MSER_DAT
	/* various cache, memory, qbus, dma, ... error bits used by the mayfair */
#define MSER_DAL	0x40
#define MSER_MCD	0x20
#define MSER_MCC	0x10
#define MSER_DAT	0x02
#define MSER_TAG	0x01
#define MSER_ERR	0x73
#endif	MSER_DAT

#define CACR_CPE	0x20
#define CACR_ERR	0x20

#define DSER_Q22NXM	0x80
#define DSER_Q22PE	0x20
#define DSER_MME	0x10
#define DSER_HIGH	0x08
#define DSER_Q22GRNT	0x04
#define DSER_DMANXM	0x01
#define DSER_ERR	0xbd

#define M16_RCS_LOG	0x80000000
#define M16_RCS_HIGH	0x40000000
#define M16_CRD_LOG	0x20000000
#define M16_CDAL_DMA	0x100
#define M16_CDAL_BUS	0x080
#define M16_ERR		0xe0000180
#define M16_PAGE	0x1ffffe00
#define M16_SHIFT	9
#define M16_SYNDROME	0x7f
#define M17_CRD		0x1000
	/* end various cache, memory, qbus, dma, ... error bits used by the mayfair */

struct ka650_mem {
	int mem_scr;		/* System Configuration Register */
	int mem_dser;		/* System Error Register */
	int mem_qbear;		/* Master Error Address Register */
	int mem_dear;		/* Slave Error Address Register */
	int mem_qbmbr;		/* q-22 Bus Map Base Register */
	int mem_r1[64-5];	/* whole to 0x100 byte boundary */
	int mem_csr[16];	/* Main Memory Configuration Reg */
	int mem_csr16;		/* Main Memory Error Status Register */
	int mem_csr17;		/* Main Memory Control/Diag Status Reg */
};

struct ka650_cacr_bdr {
	int cacr;		/* CAche Control Register */
	int bdr;		/* Boot and Diagnostic Register */
};

struct ka650_ssc {
	int ssc_sscbr;		/* SSC Base Address Register */
	int ssc_fl0[3];
	int ssc_ssccr;		/* SSC Configuration Register */
	int ssc_fl1[3];
	int ssc_cbtcr;		/* CDAL Bus Timeout Control Register */
	int ssc_fl2[3];
	int ssc_dledr;		/* Diagnostic LED Register */
	int ssc_fl3[3];

	int ssc_r1[64-16];

	int ssc_tcr0;		/* Timer 0 Control Register */
	int ssc_tir0;		/* Timer 0 Interval Register */
	int ssc_tnir0;		/* Timer 0 Next Interval Register */
	int ssc_tivr0;		/* Timer 0 Interrupt Vector */

	int ssc_tcr1;		/* Timer 1 Control Register */
	int ssc_tir1;		/* Timer 1 Interval Register */
	int ssc_tnir1;		/* Timer 1 Next Interval Register */
	int ssc_tivr1;		/* Timer 1 Interrupt Vector */

	int ssc_r2[4];

	int ssc_cdmtr;		/* CACR Address Decode Match Register */
	int ssc_cdmkr;		/* CACR Decode Mask Register */
	int ssc_fl4[2];
	int ssc_mdbtr;		/* BDR Address Decode Match Register */
	int ssc_bdmkr;		/* BDR Decode Mask Register */
	int ssc_fl5[2];

	int ssc_r3[256-5*4-64];

	char nv_ram[1024];	/* Battery Backed-up RAM */
};

#ifdef	KERNEL
extern	struct ka650_ssc *ssc;
extern	struct ka650_cacr_bdr *c2cntl;
extern	long *c2diag;
#endif	KERNEL
