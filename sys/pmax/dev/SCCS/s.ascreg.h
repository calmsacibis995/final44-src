h59142
s 00002/00002/00313
d D 8.1 93/06/10 22:38:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00290
d D 7.3 92/12/20 11:36:40 ralph 3 2
c changes from Rick Macklem
e
s 00004/00007/00286
d D 7.2 92/11/15 15:49:15 ralph 2 1
c changes for maxine from Rick Macklem.
e
s 00293/00000/00000
d D 7.1 92/03/09 14:24:27 bostic 1 0
c date and time created 92/03/09 14:24:27 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Ralph Campbell.
E 2
I 2
 * Ralph Campbell and Rick Macklem.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
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
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	scsi_53C94.h,v $
 * Revision 2.4  91/02/05  17:44:59  mrt
 * 	Added author notices
 * 	[91/02/04  11:18:32  mrt]
 * 
 * 	Changed to use new Mach copyright
 * 	[91/02/02  12:17:11  mrt]
 * 
 * Revision 2.3  90/12/05  23:34:46  af
 * 	Documented max DMA xfer size.
 * 	[90/12/03  23:39:36  af]
 * 
 * Revision 2.1.1.1  90/11/01  03:38:54  af
 * 	Created, from the DEC specs:
 * 	"PMAZ-AA TURBOchannel SCSI Module Functional Specification"
 * 	Workstation Systems Engineering, Palo Alto, CA. Aug 27, 1990.
 * 	And from the NCR data sheets
 * 	"NCR 53C94, 53C95, 53C96 Advanced SCSI Controller"
 * 	[90/09/03            af]
 */

/*
 *	File: scsi_53C94.h
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	9/90
 *
 *	Defines for the NCR 53C94 ASC (SCSI interface)
 * 	Some gotcha came from the "86C01/53C94 DMA lab work" written
 * 	by Ken Stewart (NCR MED Logic Products Applications Engineer)
 * 	courtesy of NCR.  Thanks Ken !
 */

I 3
#define ASC_OFFSET_53C94	0x0		/* from module base */
#define ASC_OFFSET_DMAR		0x40000		/* DMA Address Register */
#define ASC_OFFSET_RAM		0x80000		/* SRAM Buffer */
#define ASC_OFFSET_ROM		0xc0000		/* Diagnostic ROM */

#define	ASC_RAM_SIZE		0x20000		/* 128k (32k*32) */
#define PER_TGT_DMA_SIZE	((ASC_RAM_SIZE/7) & ~(sizeof(int)-1))
#define ASC_NCMD		7

/*
 * DMA Address Register
 */
#define ASC_DMAR_MASK		0x1ffff		/* 17 bits, 128k */
#define ASC_DMAR_WRITE		0x80000000	/* DMA direction bit */
#define	ASC_DMA_ADDR(x)		((unsigned)(x) & ASC_DMAR_MASK)

/*
 * Synch xfer parameters, and timing conversions
 */
#define SCSI_MIN_PERIOD		50	/* in 4 nsecs units */
#define ASC_MIN_PERIOD25	5	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MIN_PERIOD12	3	/* in CLKS/BYTE, 1 CLK = 80nsecs */
#define ASC_MAX_PERIOD25	35	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MAX_PERIOD12	18	/* in CLKS/BYTE, 1 CLK = 80nsecs */
#define ASC_MAX_OFFSET		15	/* pure number */
E 3
/*
 * Register map, padded as needed
 */

typedef volatile struct {
	u_char	asc_tc_lsb;	/* rw: Transfer Counter LSB */
	char	pad0[3];
	u_char	asc_tc_msb;	/* rw: Transfer Counter MSB */
	char	pad1[3];
	u_char	asc_fifo;	/* rw: FIFO top */
	char	pad2[3];
	u_char	asc_cmd;	/* rw: Command */
	char	pad3[3];
	u_char	asc_status;	/* r:  Status */
#define asc_dbus_id asc_status	/* w: Destination Bus ID */
	char	pad4[3];
	u_char	asc_intr;	/* r:  Interrupt */
#define asc_sel_timo asc_intr	/* w: (re)select timeout */
	char	pad5[3];
	u_char	asc_ss;		/* r:  Sequence Step */
#define asc_syn_p asc_ss	/* w: synchronous period */
	char	pad6[3];
	u_char	asc_flags;	/* r:  FIFO flags + seq step */
#define asc_syn_o asc_flags	/* w: synchronous offset */
	char	pad7[3];
	u_char	asc_cnfg1;	/* rw: Configuration 1 */
	char	pad8[3];
	u_char	asc_ccf;	/* w:  Clock Conv. Factor */
	char	pad9[3];
	u_char	asc_test;	/* w:  Test Mode */
	char	pad10[3];
	u_char	asc_cnfg2;	/* rw: Configuration 2 */
	char	pad11[3];
	u_char	asc_cnfg3;	/* rw: Configuration 3 */
	char	pad12[3];
	u_char	asc_res_fifo;	/* w: Reserve FIFO byte */
} asc_regmap_t;

/*
 * Transfer Count: access macros
 * That a NOP is required after loading the dma counter
 * I learned on the NCR test code. Sic.
 */

#define	ASC_TC_MAX	0x10000

#define ASC_TC_GET(ptr, val)				\
	val = (ptr)->asc_tc_lsb | ((ptr)->asc_tc_msb << 8)
#define ASC_TC_PUT(ptr, val)				\
	(ptr)->asc_tc_lsb = (val);			\
	(ptr)->asc_tc_msb = (val) >> 8;			\
D 2
	(ptr)->asc_cmd = ASC_CMD_NOP;
E 2
I 2
	(ptr)->asc_cmd = ASC_CMD_NOP | ASC_CMD_DMA;
E 2

/*
 * Command register (command codes)
 */

#define ASC_CMD_DMA		0x80
					/* Miscellaneous */
#define ASC_CMD_NOP		0x00
#define ASC_CMD_FLUSH		0x01
#define ASC_CMD_RESET		0x02
#define ASC_CMD_BUS_RESET	0x03
					/* Initiator state */
#define ASC_CMD_XFER_INFO	0x10
#define ASC_CMD_I_COMPLETE	0x11
#define ASC_CMD_MSG_ACPT	0x12
#define ASC_CMD_XFER_PAD	0x18
#define ASC_CMD_SET_ATN		0x1a
#define ASC_CMD_CLR_ATN		0x1b
					/* Target state */
#define ASC_CMD_SND_MSG		0x20
#define ASC_CMD_SND_STATUS	0x21
#define ASC_CMD_SND_DATA	0x22
#define ASC_CMD_DISC_SEQ	0x23
#define ASC_CMD_TERM		0x24
#define ASC_CMD_T_COMPLETE	0x25
#define ASC_CMD_DISC		0x27
#define ASC_CMD_RCV_MSG		0x28
#define ASC_CMD_RCV_CDB		0x29
#define ASC_CMD_RCV_DATA	0x2a
#define ASC_CMD_RCV_CMD		0x2b
#define ASC_CMD_ABRT_DMA	0x04
					/* Disconnected state */
#define ASC_CMD_RESELECT	0x40
#define ASC_CMD_SEL		0x41
#define ASC_CMD_SEL_ATN		0x42
#define ASC_CMD_SEL_ATN_STOP	0x43
#define ASC_CMD_ENABLE_SEL	0x44
#define ASC_CMD_DISABLE_SEL	0x45
#define ASC_CMD_SEL_ATN3	0x46

/*
 * Status register, and phase encoding
 */

#define ASC_CSR_INT		0x80
#define ASC_CSR_GE		0x40
#define ASC_CSR_PE		0x20
#define ASC_CSR_TC		0x10
#define ASC_CSR_VGC		0x08
#define ASC_CSR_MSG		0x04
#define ASC_CSR_CD		0x02
#define ASC_CSR_IO		0x01

#define	ASC_PHASE(csr)		((csr) & 0x7)
#define ASC_PHASE_DATAO		0x0
#define ASC_PHASE_DATAI		0x1
#define ASC_PHASE_COMMAND	0x2
#define ASC_PHASE_STATUS	0x3
				/* 4..5 ANSI reserved */
#define ASC_PHASE_MSG_OUT	0x6
#define ASC_PHASE_MSG_IN	0x7

/*
 * Destination Bus ID
 */

#define ASC_DEST_ID_MASK	0x07

/*
 * Interrupt register
 */

#define ASC_INT_RESET		0x80
#define ASC_INT_ILL		0x40
#define ASC_INT_DISC		0x20
#define ASC_INT_BS		0x10
#define ASC_INT_FC		0x08
#define ASC_INT_RESEL		0x04
#define ASC_INT_SEL_ATN		0x02
#define ASC_INT_SEL		0x01

/*
 * Timeout register:
 *
 *	val = (timeout * CLK_freq) / (8192 * CCF);
 */

D 2
#define	ASC_TIMEOUT_250		0x99	/* 250 msecs at 25 Mhz */
E 2
I 2
#define	ASC_TIMEOUT_250(clk, ccf)	(((clk) * 31) / (ccf))
E 2

/*
 * Sequence Step register
 */

#define ASC_SS_RESERVED		0xf0
#define ASC_SS_SOM		0x08
#define ASC_SS_MASK		0x07
#define	ASC_SS(ss)		((ss) & ASC_SS_MASK)

/*
 * Synchronous Transfer Period
 */

#define ASC_STP_MASK		0x1f
#define ASC_STP_MIN		0x05		/* 5 clk per byte */
#define ASC_STP_MAX		0x04		/* after ovfl, 35 clk/byte */

/*
 * FIFO flags
 */

#define ASC_FLAGS_SEQ_STEP	0xe0
#define ASC_FLAGS_FIFO_CNT	0x1f

/*
 * Synchronous offset
 */

#define ASC_SYNO_MASK		0x0f		/* 0 -> asyn */

/*
 * Configuration 1
 */

#define ASC_CNFG1_SLOW		0x80
#define ASC_CNFG1_SRD		0x40
#define ASC_CNFG1_P_TEST	0x20
#define ASC_CNFG1_P_CHECK	0x10
#define ASC_CNFG1_TEST		0x08
#define ASC_CNFG1_MY_BUS_ID	0x07

/*
 * CCF register
 */

D 2
#define ASC_CCF_10MHz		0x2
#define ASC_CCF_15MHz		0x3
#define ASC_CCF_20MHz		0x4
#define ASC_CCF_25MHz		0x5
E 2
I 2
#define	ASC_CCF(clk)		((((clk) - 1) / 5) + 1)
E 2

/*
 * Test register
 */

#define ASC_TEST_XXXX		0xf8
#define ASC_TEST_HI_Z		0x04
#define ASC_TEST_I		0x02
#define ASC_TEST_T		0x01

/*
 * Configuration 2
 */

#define ASC_CNFG2_RFB		0x80
#define ASC_CNFG2_EPL		0x40
#define ASC_CNFG2_EBC		0x20
#define ASC_CNFG2_DREQ_HIZ	0x10
#define ASC_CNFG2_SCSI2		0x08
#define ASC_CNFG2_BPA		0x04
#define ASC_CNFG2_RPE		0x02
#define ASC_CNFG2_DPE		0x01

/*
 * Configuration 3
 */

#define ASC_CNFG3_RESERVED	0xf8
#define ASC_CNFG3_SRB		0x04
#define ASC_CNFG3_ALT_DMA	0x02
#define ASC_CNFG3_T8		0x01
E 1
