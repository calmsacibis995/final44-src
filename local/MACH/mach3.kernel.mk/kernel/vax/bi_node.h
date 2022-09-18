/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987,1986 Carnegie Mellon University
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
 * $Log:	bi_node.h,v $
 * Revision 2.3  91/05/14  17:41:30  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:13:37  dbg
 * 	Changed to new copyright.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.1  89/08/03  16:36:55  rwd
 * Created.
 * 
 * Revision 2.3  88/08/10  10:13:07  rvb
 * Added all the bi register bit field names as per official names
 * in KA820 manual.
 * 
 *
 * 30-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Relocated NMI specific definitions to vax/nmi.h.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for 8800, some NMI specific stuff is here now.  This
 *	should probably be in a separate NMI file.
 *
 *  7-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed definition for BI memory boards.  They all seem to have
 *	device type 1.
 *
 * 13-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added padding in bi_node structure to map the entire BI node,
 *	so that the BI bus can be described as an array of bi_nodes.
 *
 *  3-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.  (Assumes Mach Virtual Memory).
 *
 */

/*
 *	File:	bi_node.h
 *	Author:	Avadis Tevanian, Jr., 1986.
 *
 *	BI node definitions.
 */

#ifndef	_BI_NODE_
#define	_BI_NODE_ 1

#define	BI_NODE_SIZE	0x2000		/* 8K per node */
#define	BI_MAX_NODE	16		/* 16 nodes per BI */
#define MAX_BI		4		/* 4 BI's per machine */

#define	BI_ADDR(i)	((struct bi_node *)(0x20000000 + 0x2000000*i))
#define BI_NODE_LOCAL	((struct bi_node *) 0x20080000)

#ifndef	ASSEMBLER
struct bi_node {
	short	dev_type;		/* device type */
	short	dev_rev;		/* device revision */
	long	bicsr;			/* BI Control and Status */
	long	ber;			/* Bus error register */
	long	eintrcsr;		/* Error Intr control register */
	long	intrdes;		/* interrupt dest register */
	long	ipintrmsk;		/* IPINTR Mask register */
	long	fipdes;			/* force-bit IPINTR/STOP dest. */
	long	ipintrsrc;		/* IPINTR source */
	long	sadr;			/* starting address */
	long	eadr;			/* ending address */
	long	bcicsr;			/* BCI CSR */
	long	wstat;			/* write status */
	long	fipscmd;		/* force-bit IPINTR/STOP command */
	long	pad1[3];		/* empty */
	long	uintrcsr;		/* user interface */
	long	pad2[43];		/* empty */
	long	gpr[4];			/* general purpose registers (0xf0) */
	long	sosr;			/* slave only status register */
	long	pad3[63];		/* empty */
	long	rxcd;			/* receive console data register (0x200) */
	long	pad4[1919];		/* empty */
};

#endif	ASSEMBLER

/*
 *	Node device types.
 */

#define BI_MEM		0x0001		/* memory board */
#define BI_DR32		0x0101
#define	BI_UBA		0x0102		/* Unibus adaptor */
#define BI_KLESI	0x0103
#define BI_KA820	0x0105		/* KA820 cpu */
#define BI_NBI		0x0106		/* NMI - BI adaptor */
#define BI_XMI		0x0107
#define BI_CI		0x0108
#define BI_DXX32	0x0109
#define BI_CIOBS	0x010b
#define BI_KDB50	0x010e		/* KDB50 disk controller */
#define BI_TK50		0x410e
#define BI_DEBNA	0x410f

/*
 *	Bit definitions.
 */


#define BICSR_REV	0xff000000
#define BICSR_TYPE	0x00ff0000
#define BICSR_HES	0x00008000
#define BICSR_SES	0x00004000
#define BICSR_INIT	0x00002000	/* initialize */
#define BICSR_BROKE	0x00001000	/* node broke */
#define BICSR_STS	0x00000800	/* self-test status bit */
#define BICSR_NRST	0x00000400	/* node reset (initialize) */
#define BICSR_UWP	0x00000100
#define BICSR_HEIE	0x00000080	/* hard error interrupt enable */
#define BICSR_SEIE	0x00000040	/* soft error interrupt enable */
#define BICSR_ARB	0x00000030
#define BICSR_ARB_RR	0x00		/* Round robin */
#define BICSR_ARB_HIGH	0x10		/* Fixed-high priority */
#define BICSR_ARB_LOW	0x20		/* Fixed-low priority */
#define BICSR_ARB_NONE	0x30		/* no arbitration */
#define BICSR_ARB_MASK	0x30		/* arb mask */
#define BICSR_NODE	0x0000000f

#define BICSR	"\20\40\31REV\30\21TYPE\20HES\17SES\16INIT\15BROKE\14STS\13NRST\12z\11UWP\10HEIE\07SEIE\06\05ARB\04\01NODE"

#define BER_NMR		0x40000000
#define BER_MTCE	0x20000000
#define BER_CTE 	0x10000000
#define BER_MPE		0x08000000
#define BER_ISE		0x04000000
#define BER_TDF		0x02000000
#define BER_IVE		0x01000000
#define BER_CPE		0x00800000
#define BER_SPE		0x00400000
#define BER_RDS		0x00200000
#define BER_RTO		0x00100000
#define BER_STO		0x00080000
#define BER_BTO		0x00040000
#define BER_NEX		0x00020000
#define BER_ICE		0x00010000
#define BER_UPEN	0x00000008
#define BER_IPE		0x00000004
#define BER_CRD		0x00000002
#define BER_NPE		0x00000001
#define BER_HRDERR	0xffff0000
#define BER_SFTERR	0x00000007
#define BER_ERR		0xffff0007

#define BER	"\20\37NMR\36MTCE\35CTE\34MPE\33ISE\32TDF\31IVE\30CPE\27SPE\26RDS\25RTO\24STO\23BTO\22NEX\21ICE\04UPEN\03IPE\02CRD\01NPE"

#define EINTRCSR_INTRAB		0x01000000
#define EINTRCSR_INTRC		0x00800000
#define EINTRCSR_INTRSENT	0x00200000
#define EINTRCSR_FORCE		0x00100000
#define EINTRCSR_LEVEL		0x000f0000
#define	EINTRCSR_VECTOR		0x00003fff

#define EINTRCSR	"\20\31INTRAB\30INTRC\26INTRSENT\25FORCE\24\21LEVEL\16\01VECTOR"

#define BCI_BURSTEN	0x00020000	/* burst enable */
#define BCI_IPSTFR	0x00010000	/* IPINTR/STOP force */
#define BCI_MSEN	0x00008000	/* multicast space enable */
#define BCI_BDCSTEN	0x00004000	/* broadcast enable */
#define BCI_STOPEN	0x00002000	/* stop enable */
#define BCI_RESEN	0x00001000	/* reserved enable */
#define BCI_IDENTEN	0x00000800	/* ident enable */
#define BCI_INVALEN	0x00000400	/* inval enable */
#define BCI_WINVALEN	0x00000200	/* Write inval. enable */
#define BCI_UCSREN	0x00000100	/* User Int. CSR enable */
#define BCI_BICSREN	0x00000080	/* BIIC CSR space enable */
#define BCI_INTREN	0x00000040	/* INTR enable */
#define BCI_IPINTREN	0x00000020	/* IPINTR enable */
#define BCI_PNXTEN	0x00000010	/* Pipeline xnt enable */
#define BCI_RTOEVEN	0x00000008	/* RTO EV enable */

#define BCI	"\20\22BURSTEN\21IPSTFR\20MSEN\17BDCSTEN\16STOPEN\15RESEN\14IDENTEN\13INVALEN\12WINVALEN\11UCSREN\10BICSREN\07INTREN\06IPINTREN\05PNXTEN\04RTOEVEN"

#define WSTAT_R0	0x80000000
#define WSTAT_R1	0x40000000
#define WSTAT_R2	0x20000000
#define WSTAT_R3	0x10000000
#define WSTAT	"\20\40R0\37R1\36R2\35R3"

#define FIPSCMD_CMD	0x0000f000
#define FIPSCMD_IDEN	0x00000800
#define FIPSCMD	"\20\20\15CMD\14IDEN"

#define UINTRCSR_INTRAB	0xf0000000
#define UINTRCSR_INTRC	0x0f000000
#define UINTRCSR_SENT	0x00f00000
#define UINTRCSR_FORCE	0x000f0000
#define UINTRCSR_EXTR	0x00008000
#define UINTRCSR_VECTOR	0x00003fff

#define UINTRCSR	"\20\40\35INTRAB\34\31INTRC\30\23SENT\24\21FORCE\20EXTR\16\01VECTOR"

#endif	_BI_NODE_
