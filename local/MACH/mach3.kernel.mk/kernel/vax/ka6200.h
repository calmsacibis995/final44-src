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
 * $Log:	ka6200.h,v $
 * Revision 2.3  91/05/14  17:43:34  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:17:45  dbg
 * 	Changed to new copyright.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.1  89/08/03  16:39:08  rwd
 * Created.
 * 
 * Revision 2.2  88/08/10  10:49:01  rvb
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	#ifdef's for inclusion in locore.s
 * 
 *  27-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Added ipintr and weipintr address bases.
 * 
 *   8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Created.  Week of 4/4.
 * 
 */

/*
 *	File:	ka62a.h
 *	Author:	Robert V. Baron, 1988
 *
 *	Yet another strange new bus
 *	ALSO definitions for the cpu structures
 *
 */

#ifndef	_KA6200_
#define	_KA6200_

#include <mach/vax/vm_types.h>

#define XMI_BUS		11
#define	XMI_NODE_SPACE	((vm_offset_t) 0x21800000)
#define XMI_NODES 	16
#define	XMI_NODE_SIZE	(512 * 1024)
#define XMI_IOA_RANGE1	((vm_offset_t) 0x22000000)
#define XMI_IOA_RANGE2	((vm_offset_t) 0x36000000)
#define XMI_IOA_SIZE	(32 * 1024 * 1024)

#define XMI_CPU	0x8000
#define XMI_MEM 0x4000
#define XMI_IOA 0x2000

#define IP_SPACE  0x21010000
#define WEI_SPACE 0x21020000

#ifndef	ASSEMBLER
struct xmi {
	unsigned short	dev;
	unsigned short	rev;
	unsigned long	ber;
	unsigned long	fadr;
};
#endif	ASSEMBLER

#define XMIBER_ES		0x80000000
#define XMIBER_NRST		0x40000000
#define XMIBER_NHALT		0x20000000
#define XMIBER_XBAD		0x10000000
#define XMIBER_CC		0x08000000
#define XMIBER_XFAULT		0x04000000
#define XMIBER_WEI		0x02000000
#define XMIBER_IPE		0x01000000
#define XMIBER_PE		0x00800000
#define XMIBER_WSE		0x00400000
#define XMIBER_RIDNAK		0x00200000
#define XMIBER_WDNAK		0x00100000
#define XMIBER_CRD		0x00080000
#define XMIBER_NRR		0x00040000
#define XMIBER_RSE		0x00020000
#define XMIBER_RER		0x00010000
#define XMIBER_CNAK		0x00008000
#define XMIBER_Z1		0x00004000
#define XMIBER_TTO		0x00002000
#define XMIBER_NSES		0x00001000
#define XMIBER_ETF		0x00000800
#define XMIBER_STF		0x00000400
#define XMIBER_FCID		0x000003c0
#define XMIBER_FCMD		0x0000000f
#define XMIBER_CMDERR		0x001fa000
#define XMIBER_RESERR 		0x01e00000
#define XMIBER_ERR  		0x01ffa000

#define XMIBER		 "\20\40ES\37NRST\36NHALT\35XBAD\34CC\33XFAULT\32WEI\
\31IPE\30PE\27WSE\26RIDNAK\25WDNAK\24CRD\23NRR\22RSE\21RER\20CNAK\
\17Z1\16TTO\15NSES\14ETF\13STF\12\07FCID\04\01FCMD"


#define XMIFADR_LEN		0xc0000000
#define XMIFADR_ADDR		0x30000000

#define XMIFADR		"\20\40\37LEN\36\01ADDR"

#ifndef	ASSEMBLER

#endif	ASSEMBLER
#define CADR_SEN2		0x00000080
#define CADR_SEN1		0x00000040
#define CADR_CEI		0x00000020
#define CADR_CED		0x00000010
#define CADR_O1			0x00000008
#define CADR_O2			0x00000004
#define CADR_WW			0x00000002
#define CADR_DIA		0x00000001
#define CADR_ON			0x000000e0
#define CADR_NORMAL		0x000000ec

#define CADR_B 		"\20\10SEN2\07SEN1\06CEI\05CED\04O1\03O2\02WW\01DIA"

#ifndef	MSER_DAT
/*
 * ka62a processor registers
 */
#define MSER_62A	0x27

#define MSER_HM			0x00000080
#define MSER_DAL		0x00000040
#define MSER_MCD		0x00000020
#define MSER_MCC		0x00000010
#define MSER_DAT		0x00000002
#define MSER_TAG		0x00000001
#define MSER_NORMAL		0x00000000

#define MSER_B		"\20\10HM\07DAL\06MCD\05MCC\02DAT\01TAG"
#endif	MSER_DAT

#ifndef	ASSEMBLER
struct ka62a {
	unsigned short	dev;
	unsigned short	rev;
	unsigned long	ber;
	unsigned long	fadr;
	unsigned long	gpr;
	unsigned long	csr2;
};
#endif	ASSEMBLER

#define CONSEL(x)	(consel[((x&8)>>1)|(x&3)])

/*
 * Control/status register 1
 */
#define	CSR1			0x20000000

#define ka62aCSR1_XSEC		0x80000000
#define ka62aCSR1_LATHIT	0x40000000
#define ka62aCSR1_LCKOUTDIS	0x02000000
#define ka62aCSR1_LED1		0x01000000
#define ka62aCSR1_FCACHEEN	0x00800000
#define ka62aCSR1_FPSEL		0x00400000
#define ka62aCSR1_CPUD		0x00200000
#define ka62aCSR1_FCI		0x00100000
#define ka62aCSR1_FBTP		0x00080000
#define ka62aCSR1_FMISS		0x00040000
#define ka62aCSR1_FHIT		0x00020000
#define ka62aCSR1_LED2		0x00010000
#define ka62aCSR1_LED3		0x00008000
#define ka62aCSR1_LED4		0x00004000
#define ka62aCSR1_LED5		0x00002000
#define ka62aCSR1_LED6		0x00001000
#define ka62aCSR1_LEDSTP	0x00000800
#define ka62aCSR1_DLCKOUTEN	0x00000400
#define ka62aCSR1_EEWADR	0x00000300
#define ka62aCSR1_STL		0x00000080
#define ka62aCSR1_XACLO		0x00000040
#define ka62aCSR1_FPEEU		0x00000020
#define ka62aCSR1_FPBD		0x00000010
#define	ka62aCSR1_NID		0x0000000f

#define ka62aCSR1 "\20\40XSEC\37LATHIT\32LCKOUTDIS\31LED1\
\30FCACHEEN\27FPSEL\26CPUD\25FCI\24FBTP\23FMISS\22FHIT\21LED2\20LED3\17LED4\
\16LED5\15LED6\14LEDSTP\13DLCKOUTEN\12\11EEWADR\10STL\07XACLO\06FPEEU\
\05FPBD\04\01NID"

#define ka62aCSR2_VPE		0x80000000
#define ka62aCSR2_TPE		0x40000000
#define ka62aCSR2_IQO		0x20000000
#define ka62aCSR2_WDPE		0x10000000
#define ka62aCSR2_CFE		0x08000000
#define ka62aCSR2_DTPE		0x04000000
#define ka62aCSR2_LOCKOUT	0x00600000
#define ka62aCSR2_UWP		0x00100000
#define ka62aCSR2_CNAKR		0x00080000
#define ka62aCSR2_BP		0x00040000
#define ka62aCSR2_BPD		0x00020000
#define ka62aCSR2_WS		0x00010000
#define ka62aCSR2_CCID		0x00008000
#define ka62aCSR2_CRDID		0x00004000
#define ka62aCSR2_TOS		0x00001000
#define ka62aCSR2_ERUP		0x00000800
#define ka62aCSR2_ESI		0x00000400
#define ka62aCSR2_ARD		0x00000200
#define ka62aCSR2_WBD		0x00000100
#define ka62aCSR2_FP1		0x00000070
#define	ka62aCSR2_GAREV		0x0000000f
#define	ka62aCSR2_ERR		0xfc000000

#define ka62aCSR2	"\20\40VPE\37TPE\36IQO\35WDPE\34CFE\33DTPE\27\26LOCKOUT\
\25UWP\24CNAKR\23BP\22BPD\21WS\20CCID\17CRDID\
\15TOS\14ERUP\13ESI\12ARD\11WBD\07\05FP\04\01GAREV"
#ifndef	ASSEMBLER

/*
 * System Support chip.
 */
struct ka62a_ssc {
	unsigned long	ssc_sscbr;	/* SSC Base Address Register */
	unsigned long	ssc_fl0[3];
	unsigned long	ssc_ssccr;	/* SSC Configuration Register */
	unsigned long	ssc_fl1[3];
	unsigned long	ssc_cbtcr;	/* CDAL Bus Timeout Control Register */
	unsigned long	ssc_fl2[3];
	unsigned long	ssc_consel;	/* Console Select */
	unsigned long	ssc_fl3[3];

	unsigned long	ssc_r1[64-16];

	unsigned long	ssc_tcr0;	/* Timer 0 Control Register */
	unsigned long 	ssc_tir0;	/* Timer 0 Interval Register */
	unsigned long	ssc_tnir0;	/* Timer 0 Next Interval Register */
	unsigned long	ssc_tivr0;	/* Timer 0 Interrupt Vector */

	unsigned long	ssc_tcr1;	/* Timer 1 Control Register */
	unsigned long	ssc_tir1;	/* Timer 1 Interval Register */
	unsigned long	ssc_tnir1;	/* Timer 1 Next Interval Register */
	unsigned long	ssc_tivr1;	/* Timer 1 Interrupt Vector */

	unsigned long	ssc_r2[4];

	unsigned long	ssc_csr1badr;	/* CSR1 Base Address */
	unsigned long	ssc_csr1admr;	/* CSR1 Address Decode Mask */
	unsigned long	ssc_fl4[2];
	unsigned long	ssc_eebadr;	/* EEPROM Base Address */
	unsigned long	ssc_eeadmr;	/* EEPROM Adress Decode Mask */
	unsigned long	ssc_fl5[2];

	unsigned long	ssc_r3[256-5*4-64];

	char		nv_bburam[1024];	/* Battery Backed-up RAM */
};
#endif	ASSEMBLER

#define	SSCC			0x20140000

#define SSCCR_BLO		0x80000000
#define SSCCR_IVD		0x08000000
#define SSCCR_IPL		0x03000000
#define SSCCR_RSP		0x00800000
#define SSCCR_ROM		0x00700000
#define SSCCR_HALT		0x00070000
#define SSCCR_CNTLP		0x00008000
#define SSCCR_CTBAUD		0x00007000
#define SSCCR_AXBAUD		0x00000700
#define SSCCR_EEEN		0x00000070
#define SSCCR_CSR1EN		0x00000007

#define SSCCR	"\20\40BLO\34IVD\32\31IPL\30RSP\27\25ROM\23\21HALT\20CNTLP\
\17\15CTBAUD\13\11AXBAUD\07\05EEEN\03\01CSR1EN"

#define TCR_ERR			0x80000000
#define TCR_INT			0x00000080
#define TCR_IE			0x00000040
#define TCR_SGL			0x00000020
#define TCR_XFR			0x00000010
#define TCR_STP			0x00000004
#define TCR_RUN			0x00000001

#define	TCR	"\20\40ERR\10INT\07IE\06SGL\05XFR\03STP\01RUN"
#ifndef	ASSEMBLER

struct ms62a {
	unsigned short	dev;
	unsigned short	rev;
	unsigned long	ber;
	unsigned long	fadr;
	unsigned long	fill1;
	unsigned long	seadr;			/* 0x10 */
	unsigned long	mctl1;			/* 0x14 */
	unsigned long	mecer;			/* 0x18 */
	unsigned long	mecea;			/* 0x1c */
	unsigned long	int0;			/* 0x20 */
	unsigned long	int1;			/* 0x24 */
	unsigned long	int2;			/* 0x28 */
	unsigned long	int3;			/* 0x2c */
	unsigned long	mctl2;			/* 0x30 */
	unsigned long	tcy;			/* 0x34 */
	unsigned long	fill[2];
	unsigned long	int4;			/* 0x40 */
	unsigned long	int5;			/* 0x44 */
	unsigned long	int6;			/* 0x48 */
	unsigned long	int7;			/* 0x4c */
	char		fill3[0x30];
	unsigned long	int8;			/* 0x80 */
	unsigned long	int9;			/* 0x84 */
	unsigned long	inta;			/* 0x88 */
	unsigned long	intb;			/* 0x8c */
	char		fill4[0x70];
	unsigned long	intc;			/* 0x100 */
	unsigned long	intd;			/* 0x104 */
	unsigned long	inte;			/* 0x108 */
	unsigned long	intf;			/* 0x10c */
};
#endif	ASSEMBLER

#define SEADR_ENDADR		0x3fe00000
#define SEADR_STADR		0x0000ff00
#define SEADR_INADR		0x000000e0
#define SEADR_INTM		0x00000003

#define SEADR	"\20\36\26ENDADR\20\11STADR\10\06INADR\02\01INTM<<"

#define M62aCTL1_ERRSUM		0x80000000
#define M62aCTL1_ECCDIAG	0x40000000
#define M62aCTL1_ECCDIS		0x20000000
#define M62aCTL1_MEMSIZ		0x1ffc0000
#define M62aCTL1_RAMTYP		0x00030000
#define M62aCTL1_ICRD		0x00008000
#define M62aCTL1_MEMVAL		0x00004000
#define M62aCTL1_EPM		0x00002000
#define M62aCTL1_LQERR		0x00001000
#define M62aCTL1_UNSEQ		0x00000800
#define M62aCTL1_MWRER		0x00000400
#define M62aCTL1_DC		0x000000ff
#define M62aCTL1_ERR		0x00001c00

#define M62aCTL1	"\20\40ERRSUM\37ECCDIAG\36ECCDIS\35\23MEMSIZ\22\21RAMTYP\
\20ICRD\17MEMVAL\16EPM\15LQERR\14UNSEQ\13MWRER\12Z\11Z\10\01DC"

#define M62aCTL2_RERR		0x00010000
#define M62aCTL2_DISH		0x00000020
#define M62aCTL2_RRB		0x0000001c
#define M62aCTL2_ARBSC		0x00000003
#define M62aCTL2_ERR		0x00010000

#define M62aCTL2	"\20\21RERR\06DISH\05\03RRB\02\01ARBSC"

#define M62aECER_RERER		0x80000000
#define M62aECER_HIERR		0x40000000
#define M62aECER_CRDER		0x20000000
#define M62aECER_Z		0x10000000
#define M62aECER_BWERR		0x08000000
#define M62aECER_RPER		0x04000000
#define M62aECER_CPER		0x02000000
#define M62aECER_ERSYN		0x000000ff
#define M62aECER_ERR		0xe0000000

#define M62aECER	"\20\40RERER\37HIERR\36CRDER\35Z\34BWERR\33RPER\32CPER\10\01ERSYN"
#ifndef	ASSEMBLER

struct dwmba {
	unsigned short	dev;
	unsigned short	rev;
	unsigned long	ber;
	unsigned long	fadr;
	unsigned long	arear;			/* 0x0c */
	unsigned long	aesr;			/* 0x10 */
	unsigned long	aimr;			/* 0x14 */
	unsigned long	aivintr;		/* 0x18 */
	unsigned long	adg1;			/* 0x1c */
	char		fill[0x20];
	unsigned long	bcsr;			/* 0x40 */
	unsigned long	besr;			/* 0x44 */
	unsigned long	bidr;			/* 0x48 */
	unsigned long	btim;			/* 0x4c */
	unsigned long	bvor;			/* 0x50 */
	unsigned long	bvr;			/* 0x54 */
	unsigned long	bdcr1;			/* 0x58 */
};
#endif	ASSEMBLER

#define AESR_XBIOK		0x80000000
#define AESR_EID		0x03c00000
#define AESR_ECMD		0x000f0000
#define AESR_INTRNL		0x00000080
#define AESR_IOWFAIL		0x00000040
#define AESR_ACLO		0x00000020
#define AESR_ADATA		0x00000010
#define AESR_ACA		0x00000008
#define AESR_BDATA		0x00000004
#define AESR_BCA		0x00000002
#define AESR_CPU		0x00000001
#define AESR_ERR		0x000000ff

#define AESR	"\20\40XBIOK\32\23EID\24\21ECMD\
\10INTRNL\07IOWFAIL\06ACLO\05ADATA\04ACA\03BDATA\02BCA\01CPU"

#define AIMR_IVNTRIE		0x80000000
#define AIMR_CCIE		0x08000000
#define AIMR_PEIE		0x00800000
#define AIMR_WSEIE		0x00400000
#define AIMR_RIDNAKIE		0x00200000
#define AIMR_WDNAKIE		0x00100000
#define AIMR_CRDIE		0x00080000
#define AIMR_NRRIE		0x00040000
#define AIMR_RSEIE		0x00020000
#define AIMR_RERIE		0x00010000
#define AIMR_CNAKIE		0x00008000
#define AIMR_ACAIE		0x00000008
#define AIMR_BCAIE		0x00000002
#define AIMR_CPUIE		0x00000001
#define AIMR_EN			0x88ff800b

#define AIMR	"\20\40IVNTRIE\34CCIE\30PEIE\27WSEIE\26RIDNAKIE\25WDNAKIE\
\24CRDIE\23NRRIE\22RSEIE\21RERIE\20CNAKIE\04ACAIE\02BCAIE\01CPUIE"

#define BCSR_ENINTR		0x80000000
#define BCSR_BIBAD		0x00000010
#define BCSR_BIINTLCK		0x00000004
#define BCSR_LED		0x00000002
#define BCSR_IBPE		0x00000001
#define BCSR_EN			0x00000005

#define BCSR	"\20\40ENINTR\05BIBAD\03BIINTLCK\02LED\01IBPE"

#define BESR_SEND		0x0001e000
#define BESR_XINTPEND		0x00001000
#define BESR_INTPEND		0x00000f00
#define BESR_MULTI		0x00000080
#define BESR_CAFAIL		0x00000040
#define BESR_SSFAIL		0x00000020
#define BESR_MSFAIL		0x00000010
#define BESR_ILCMD		0x00000008
#define BESR_BIFAIL		0x00000004
#define BESR_IDENT		0x00000002
#define BESR_IBPE		0x00000001
#define BESR_ERR		0x00000087
#define BESR	"\20\21\16SEND\15XINTPEND\14\11INTPEND\10MULTI\07CAFAIL\06SSFAIL\05MSFAIL\04ILCMD\03BIFAIL\02IDENT\01IBPE"


#ifdef	KERNEL
#ifndef	ASSEMBLER

extern struct ka62a_ssc * ka62a_ssc;
extern int *		  ka62a_csr1;
extern int		  last_cpu;
extern char *		  ip_space;
extern char *		  wei_space;
#endif	ASSEMBLER
#endif	KERNEL

#endif	_KA6200_
