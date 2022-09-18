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
 * $Log:	ubareg.h,v $
 * Revision 2.3  89/03/09  22:40:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:09:19  gm0w
 * 	Changes for cleanup.
 * 
 * 10-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for VAX650.
 *
 *  2-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for VAX-8800.
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush CS_NEWCPU.
 *
 * 28-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_NEWCPU:  Added UMEM1 definition for uVax-1.
 *
 *  5-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for BI Unibus adaptor (DWBUA).  Mainly defintion of
 *	dwbua structure.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ubareg.h	7.1 (Berkeley) 6/5/86
 */

#ifdef	MACH
#include <cputypes.h>
#endif	MACH

#include <bi.h>

/*
 * VAX UNIBUS adapter registers
 */

/*
 * size of unibus address space in pages
 */
#define UBAPAGES 512

/*
 * Number of UNIBUS map registers.  We can't use the last 8k of UNIBUS
 * address space for i/o transfers since it is used by the devices,
 * hence have slightly less than 256K of UNIBUS address space.
 */
#define NUBMREG	496

#ifndef	LOCORE
/*
 * UBA hardware registers
 */
#if	NBI > 0
/*
 *	The DWBUA has a sufficiently different layout of registers that
 *	different structure is used.
 *
 *	NOTE:  Since the mapping registers are at the same location in
 *	both types of adaptors, we only use the "old" definition for
 *	simplicity.
 */
struct dwbua_regs {
	char	pad1[0x720];		/* offset from beginning of node */
	int	csr;			/* control and status register */
	int	vec_offset;		/* vector offse register */
	int	fubar;			/* Failed Unibus address register (FUBAR) */
	int	bifar;			/* BI failed address register (BIFAR) */
	int	udiag[5];		/* Micro-diagnostics */
	int	pad2[3];		/* reserved to DEC */
	int	dpr[6];			/* data path control/status */
	int	pad3[10];		/* not used */
	int	bdps[20];		/* buffered data path space */
	int	pad4[8];		/* more not used */
	struct	pte map[NUBMREG];	/* unibus map registers */
	int	pad5[16];		/* device address space */
};
#endif	NBI > 0
struct uba_regs
{
	int	uba_cnfgr;		/* configuration register */
	int	uba_cr;			/* control register */
	int	uba_sr;			/* status register */
	int	uba_dcr;		/* diagnostic control register */
	int	uba_fmer;		/* failed map entry register */
	int	uba_fubar;		/* failed UNIBUS address register */
	int	pad1[2];
	int	uba_brsvr[4];
	int	uba_brrvr[4];		/* receive vector registers */
	int	uba_dpr[16];		/* buffered data path register */
	int	pad2[480];
	struct	pte uba_map[NUBMREG];	/* unibus map register */
	int	pad3[16];		/* no maps for device address space */
};
#endif

#if	defined(VAX780) || defined(VAX8600)
/* uba_cnfgr */
#define UBACNFGR_UBINIT	0x00040000	/* unibus init asserted */
#define UBACNFGR_UBPDN	0x00020000	/* unibus power down */
#define UBACNFGR_UBIC	0x00010000	/* unibus init complete */

#define UBACNFGR_BITS \
"\40\40PARFLT\37WSQFLT\36URDFLT\35ISQFLT\34MXTFLT\33XMTFLT\30ADPDN\27ADPUP\23UBINIT\22UBPDN\21UBIC"

/* uba_cr */
#define UBACR_MRD16	0x40000000	/* map reg disable bit 4 */
#define UBACR_MRD8	0x20000000	/* map reg disable bit 3 */
#define UBACR_MRD4	0x10000000	/* map reg disable bit 2 */
#define UBACR_MRD2	0x08000000	/* map reg disable bit 1 */
#define UBACR_MRD1	0x04000000	/* map reg disable bit 0 */
#define UBACR_IFS	0x00000040	/* interrupt field switch */
#define UBACR_BRIE	0x00000020	/* BR interrupt enable */
#define UBACR_USEFIE	0x00000010	/* UNIBUS to SBI error field IE */
#define UBACR_SUEFIE	0x00000008	/* SBI to UNIBUS error field IE */
#define UBACR_CNFIE	0x00000004	/* configuration IE */
#define UBACR_UPF	0x00000002	/* UNIBUS power fail */
#define UBACR_ADINIT	0x00000001	/* adapter init */

/* uba_sr */
#define UBASR_BR7FULL	0x08000000	/* BR7 receive vector reg full */
#define UBASR_BR6FULL	0x04000000	/* BR6 receive vector reg full */
#define UBASR_BR5FULL	0x02000000	/* BR5 receive vector reg full */
#define UBASR_BR4FULL	0x01000000	/* BR4 receive vector reg full */
#define UBASR_RDTO	0x00000400	/* UNIBUS to SBI read data timeout */
#define UBASR_RDS	0x00000200	/* read data substitute */
#define UBASR_CRD	0x00000100	/* corrected read data */
#define UBASR_CXTER	0x00000080	/* command transmit error */
#define UBASR_CXTMO	0x00000040	/* command transmit timeout */
#define UBASR_DPPE	0x00000020	/* data path parity error */
#define UBASR_IVMR	0x00000010	/* invalid map register */
#define UBASR_MRPF	0x00000008	/* map register parity failure */
#define UBASR_LEB	0x00000004	/* lost error */
#define UBASR_UBSTO	0x00000002	/* UNIBUS select timeout */
#define UBASR_UBSSYNTO	0x00000001	/* UNIBUS slave sync timeout */

#define UBASR_BITS \
"\20\13RDTO\12RDS\11CRD\10CXTER\7CXTMO\6DPPE\5IVMR\4MRPF\3LEB\2UBSTO\1UBSSYNTO"

/* uba_brrvr[] */
#define UBABRRVR_AIRI	0x80000000	/* adapter interrupt request */
#define UBABRRVR_DIV	0x0000ffff	/* device interrupt vector field */
#endif
 
/* uba_dpr */
#if	NBI > 0
#define DWBUA_CSR_UPI	0x00020000	/* initialize Unibus */
#define DWBUA_DPR_PURGE	0x00000001	/* purge bdp */
#endif	NBI > 0
#if	defined(VAX780) || defined(VAX8600)
#define UBADPR_BNE	0x80000000	/* buffer not empty - purge */
#define UBADPR_BTE	0x40000000	/* buffer transfer error */
#define UBADPR_DPF	0x20000000	/* DP function (RO) */
#define UBADPR_BS	0x007f0000	/* buffer state field */
#define UBADPR_BUBA	0x0000ffff	/* buffered UNIBUS address */
#define UBA_PURGE780(uba, bdp) \
    ((uba)->uba_dpr[bdp] |= UBADPR_BNE)
#else
#define UBA_PURGE780(uba, bdp)
#endif
#if	VAX750
#define UBADPR_ERROR	0x80000000	/* error occurred */
#define UBADPR_NXM	0x40000000	/* nxm from memory */
#define UBADPR_UCE	0x20000000	/* uncorrectable error */
#define UBADPR_PURGE	0x00000001	/* purge bdp */
/* the DELAY is for a hardware problem */
#define UBA_PURGE750(uba, bdp) { \
    ((uba)->uba_dpr[bdp] |= (UBADPR_PURGE|UBADPR_NXM|UBADPR_UCE)); \
    DELAY(8); \
}
#else
#define UBA_PURGE750(uba, bdp)
#endif

/*
 * Macros for fast buffered data path purging in time-critical routines.
 *
 * Too bad C pre-processor doesn't have the power of LISP in macro
 * expansion...
 */

#if	defined(VAX8600) || defined(VAX780) || defined(VAX750)
#define UBAPURGE(uba, bdp) { \
	switch (cpu) { \
	case VAX_8600: case VAX_780: UBA_PURGE780((uba), (bdp)); break; \
	case VAX_750: UBA_PURGE750((uba), (bdp)); break; \
	} \
}
#endif
#if	!defined(VAX8600) && !defined(VAX780) && !defined(VAX750)
#define UBAPURGE(uba, bdp)
#endif



/* uba_mr[] */
#define UBAMR_MRV	0x80000000	/* map register valid */
#define UBAMR_BO	0x02000000	/* byte offset bit */
#define UBAMR_DPDB	0x01e00000	/* data path designator field */
#define UBAMR_SBIPFN	0x000fffff	/* SBI page address field */

#define UBAMR_DPSHIFT	21		/* shift to data path designator */

/*
 * Number of unibus buffered data paths and possible uba's per cpu type.
 */
#if	NBI > 0
#define NBDPBI	5
#endif	NBI > 0
#define NBDP8600	15
#define NBDP780	15
#define NBDP750	3
#define NBDP730	0
#define NBDP650 0
#define NBDP630	0
#if	VAX1
#define NBDP1	0
#endif	VAX1
#define MAXNBDP	15

/*
 * Symbolic BUS addresses for UBAs.
 */
#if	VAX1
#define UMEM1		((u_short *)(0x20000000-0760000))
#endif	VAX1

#if	VAX650
#define UMEM650		((u_short *)(0x30000000))
#endif	VAX650

#if	VAX630
#define UMEM630		((u_short *)(0x1ffc2000))
#endif

#if	VAX730
#define UMEM730		((u_short *)(0xfc0000))
#endif

#if	VAX750
#define UMEM750(i)	((u_short *)(0xfc0000-(i)*0x40000))
#endif

#if	VAX780
#define UMEM780(i)	((u_short *)(0x20100000+(i)*0x40000))
#endif

#if	VAX820
#define UMEM820(i)	((u_short *)(0x20400000+(i)*0x40000))
#endif	VAX820

#if	VAX8600
#define UMEMA8600(i)	((u_short *)(0x20100000+(i)*0x40000))
#define UMEMB8600(i)	((u_short *)(0x22100000+(i)*0x40000))
#endif


#if	VAX8800
#define UMEM8800(i)	((u_short *)(0x20400000+(i)*0x40000))
#endif	VAX8800
/*
 * Macro to offset a UNIBUS device address, often expressed as
 * something like 0172520 by forcing it into the last 8K of UNIBUS memory
 * space.
 */
#define ubdevreg(addr)	(0760000|((addr)&017777))

