/* 
 **********************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **********************************************************************
 * HISTORY
 * $Log:	ka630.h,v $
 * Revision 2.3  93/03/11  13:47:27  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.2  91/06/19  12:00:54  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:48:11  rvb]
 * 
 * Revision 2.1  89/08/03  16:28:43  rwd
 * Created.
 * 
 * 24-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *      Changes for VAX650: well actually the common stuff was taken
 *	from here and was put in uvax.h
 *
 * 11-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made cldevice a pointer for MACH.  Exported ka630cpu.
 *
 * 16-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Defined set_cpmbx() macro for setting the halt
 *	action code in the cpmbx RAM location while preserving the
 *	language; added definitions for remaining RAM locations to get
 *	a handle on number 15 which evidently indicates a video or SLU
 *	console; added KA630CLK_RSBOOT definition.
 *
 **********************************************************************
 */ 
 
#ifdef	KERNEL
#include <platforms.h>
#else	KERNEL
#include <sys/features.h>
#endif	KERNEL
/*
 *	@(#)ka630.h	7.1 (Berkeley) 6/5/86
 *
 * Definitions specific to the ka630 uvax2 cpu card. Includes the tod
 * clock chip and the cpu registers.
 */
#include <sys/types.h>

#ifdef VAX630

#define ROM630_HALT	((caddr_t) 0x20040000)
#define ROM630_RUN	((caddr_t) 0x20050000)
#define ROM630_SIZE	(64*1024)

/* Bdr register bits */
#define	KA630BDR_PWROK	0x8000
#define	KA630BDR_HLTENB	0x4000
#define	KA630BDR_CPU	0x0c00
#define	KA630BDR_BDG	0x0300
#define	KA630BDR_DSPL	0x000f

/* Memory system err reg. */
#define	KA630MSER_CD	0x00000300
#define	KA630MSER_NXM	0x00000080
#define	KA630MSER_LPE	0x00000040
#define	KA630MSER_QPE	0x00000020
#define	KA630MSER_MERR	0x000000f0
#define	KA630MSER_CPUER	0x00000060
#define	KA630MSER_DQPE	0x00000010
#define	KA630MSER_LEB	0x00000008
#define	KA630MSER_WRWP	0x00000002
#define	KA630MSER_PAREN	0x00000001

/* Mem. error address regs. */
#define	KA630CEAR_PG	0x00007fff
#define	KA630DEAR_PG	0x00007fff

/* Clock registers and constants */
#define	MINSEC	60
#define	HRSEC	3600

#define	KA630CLK_VRT	0200
#define	KA630CLK_UIP	0200
#define	KA630CLK_RATE	040
#define	KA630CLK_ENABLE	06
#define	KA630CLK_SET	0206
#ifndef LOCORE

extern struct cldevice	*cldevice;	/* allocated by VM */

struct cldevice {
	u_short	sec;
	u_short	secalrm;
	u_short	min;
	u_short	minalrm;
	u_short	hr;
	u_short	hralrm;
	u_short	dayofwk;
	u_short	day;
	u_short	mon;
	u_short	yr;
	u_short	csr0;
	u_short	csr1;
	u_short	csr2;
	u_short	csr3;
	u_short	cpmbx;	/* CPMBX is used by the boot rom. see ka630-ug-3.3.3 */
	u_short wcram[64-15];	/* special purpose RAM used by rom */
}; 

struct ka630cpu {
	u_short ka630_bdr;
	u_short ka630_xxx;
	u_int  ka630_mser;
	u_int  ka630_cear;
	u_int  ka630_dear;
};
extern	struct ka630cpu	*ka630cpu;

#endif
#endif
