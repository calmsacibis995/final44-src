h06827
s 00002/00002/00125
d D 8.1 93/06/11 15:08:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00126
d D 7.3 93/04/20 05:43:34 torek 3 2
c spelling
e
s 00005/00000/00122
d D 7.2 92/07/21 16:37:54 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00122/00000/00000
d D 7.1 92/07/13 00:41:27 torek 1 0
c date and time created 92/07/13 00:41:27 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: bsd_audioreg.h,v 1.3 92/06/07 21:12:50 mccanne Exp $ (LBL)
 */

/*
 * Bit encodings for chip commands from "Microprocessor Access Guide for
 * Indirect Registers", p.19 Am79C30A/32A Advanced Micro Devices spec 
 * sheet (preliminary).
 *
 * Indirect register numbers (the value written into cr to select a given
 * chip registers) have the form AMDR_*.  Register fields look like AMD_*.
 */

struct amd7930 {
	u_char	cr;		/* command register (wo) */
#define ir cr			/* interrupt register (ro) */
	u_char	dr;		/* data register (rw) */
	u_char	dsr1;		/* D-channel status register 1 (ro) */
	u_char	der;		/* D-channel error register (ro) */
	u_char	dctb;		/* D-channel transmit register (wo) */
#define dcrb dctb		/* D-channel receive register (ro) */
	u_char	bbtb;		/* Bb-channel transmit register (wo) */
#define bbrb bbtb		/* Bb-channel receive register (ro) */
	u_char	bctb;		/* Bc-channel transmit register (wo) */
#define bcrb bctb		/* Bc-channel receive register (ro) */
	u_char	dsr2;		/* D-channel status register 2 (ro) */
};

#define AMDR_INIT	0x21
#define 	AMD_INIT_PMS_IDLE		0x00
#define 	AMD_INIT_PMS_ACTIVE		0x01
#define 	AMD_INIT_PMS_ACTIVE_DATA	0x02
#define 	AMD_INIT_INT_DISABLE		(0x01 << 2)
#define 	AMD_INIT_CDS_DIV2		(0x00 << 3)
#define 	AMD_INIT_CDS_DIV1		(0x01 << 3)
#define 	AMD_INIT_CDS_DIV4		(0x02 << 3)
#define 	AMD_INIT_AS_RX			(0x01 << 6)
#define 	AMD_INIT_AS_TX			(0x01 << 7)

#define AMDR_LIU_LSR	0xa1
#define AMDR_LIU_LPR	0xa2
#define AMDR_LIU_LMR1	0xa3
#define AMDR_LIU_LMR2	0xa4
#define AMDR_LIU_2_4	0xa5
#define AMDR_LIU_MF	0xa6
#define AMDR_LIU_MFSB	0xa7
#define AMDR_LIU_MFQB	0xa8

#define AMDR_MUX_MCR1	0x41
#define AMDR_MUX_MCR2	0x42
#define AMDR_MUX_MCR3	0x43
#define 	AMD_MCRCHAN_NC		0x00
#define 	AMD_MCRCHAN_B1		0x01
#define 	AMD_MCRCHAN_B2		0x02
#define 	AMD_MCRCHAN_BA		0x03
#define 	AMD_MCRCHAN_BB		0x04
#define 	AMD_MCRCHAN_BC		0x05
#define 	AMD_MCRCHAN_BD		0x06
#define 	AMD_MCRCHAN_BE		0x07
#define 	AMD_MCRCHAN_BF		0x08
#define AMDR_MUX_MCR4	0x44
#define		AMD_MCR4_INT_ENABLE	(1 << 3)
#define		AMD_MCR4_SWAPBB		(1 << 4)
#define		AMD_MCR4_SWAPBC		(1 << 5)

#define AMDR_MUX_1_4	0x45

#define AMDR_MAP_X	0x61
#define AMDR_MAP_R	0x62
#define AMDR_MAP_GX	0x63
#define AMDR_MAP_GR	0x64
#define AMDR_MAP_GER	0x65
#define AMDR_MAP_STG	0x66
#define AMDR_MAP_FTGR	0x67
#define AMDR_MAP_ATGR	0x68
#define AMDR_MAP_MMR1	0x69
#define		AMD_MMR1_ALAW	0x01
#define		AMD_MMR1_GX	0x02
#define		AMD_MMR1_GR	0x04
#define		AMD_MMR1_GER	0x08
#define		AMD_MMR1_X	0x10
#define		AMD_MMR1_R	0x20
#define		AMD_MMR1_STG	0x40
#define		AMD_MMR1_LOOP	0x80
#define AMDR_MAP_MMR2	0x6a
#define		AMD_MMR2_AINB	0x01
#define		AMD_MMR2_LS	0x02
#define		AMD_MMR2_DTMF	0x04
#define		AMD_MMR2_GEN	0x08
#define		AMD_MMR2_RNG		0x10
#define		AMD_MMR2_DIS_HPF	0x20
#define		AMD_MMR2_DIS_AZ		0x40
#define AMDR_MAP_1_10	0x6b

#define AMDR_DLC_FRAR123 0x81
#define AMDR_DLC_SRAR123 0x82
#define AMDR_DLC_TAR	0x83
#define AMDR_DLC_DRLR	0x84
#define AMDR_DLC_DTCR	0x85
#define AMDR_DLC_DMR1	0x86
#define AMDR_DLC_DMR2	0x87
#define AMDR_DLC_1_7	0x88
#define AMDR_DLC_DRCR	0x89
#define AMDR_DLC_RNGR1	0x8a
#define AMDR_DLC_RNGR2	0x8b
#define AMDR_DLC_FRAR4	0x8c
#define AMDR_DLC_SRAR4	0x8d
#define AMDR_DLC_DMR3	0x8e
#define AMDR_DLC_DMR4	0x8f
#define AMDR_DLC_12_15	0x90
#define AMDR_DLC_ASR	0x91
E 1
