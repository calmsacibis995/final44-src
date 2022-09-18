h56691
s 00003/00001/00052
d D 7.1 88/05/21 18:36:03 karels 2 1
c bring up to revision 7 for tahoe release
e
s 00053/00000/00000
d D 1.1 86/01/05 18:46:21 sam 1 0
c date and time created 86/01/05 18:46:21 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * Memory controller registers
 *
 */


/*
 * Some bits definition for MCR
 */

#define	EED	0x01		/* Enable error detection */
#define	EEC	0x02		/* Enable error correction */
#define	WMD	0x04		/* Write memory diagnostic */
#define	RMD	0x08		/* Read memory diagnostic */
#define	INT	0x20		/* Init = power on bit */
#define	CEC	0x40		/* Clear error count */
#define	CME	0x80		/* Clear memory error */
#define	CMEC	0xff00		/* Corrected memory error count (mask) */

/* shifts to get the values of MCR fields. */
 
#define	EECSHFT		0x01		/* Enable error correction */
#define	WMDSHFT		0x02		/* Write memory diagnostic */
#define	RMDSHFT		0x03		/* Read memory diagnostic */
#define	INTSHFT		0x05		/* Init = power on bit */
#define	CECSHFT		0x06		/* Clear error count */
#define	CMESHFT		0x07		/* Clear memory error */
#define	CMECSHFT	0x08		/* Corrected memory error count (mask) */
/*
 * MER bits
 */

#define	ERRCD	0x07		/* Error code (mask) */
#define    APE	1	/* Address parity error */
#define    DPE	2	/* Data parity error */
#define    DCE	3	/* Data check error */
#define    VTO	4	/* Versabus timeout */
#define    VBE	5	/* Versabus error */
#define    NEM	6	/* Non-existent memory */

#define	AXE	0x08		/* Adapter external error */
#define	ERM	0x10		/* Error master (0=CPU, 1=Versabus) */
#define	IVV	0x100		/* Illegal Versabus vector */

/*
 * MCBR bits
 */

#define	MCBR	0xffff0000
#define	MEAR	0xffff0000

E 1
