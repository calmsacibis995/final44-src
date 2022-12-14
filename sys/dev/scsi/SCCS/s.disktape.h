h14179
s 00002/00002/00232
d D 8.1 93/06/10 21:20:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00010/00223
d D 5.4 93/04/29 17:07:00 torek 4 3
c seems more convenient to make the block descriptors and scsi mode page
c headers separate from their associated surrounding structures.
e
s 00189/00026/00044
d D 5.3 93/02/01 11:14:35 torek 3 2
c mode sense, select; rm bitfields; fix comments
e
s 00005/00000/00065
d D 5.2 92/07/23 14:00:44 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00065/00000/00000
d D 5.1 92/07/10 00:03:04 torek 1 0
c date and time created 92/07/10 00:03:04 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: disktape.h,v 1.2 92/05/15 11:24:00 torek Exp $ (LBL)
E 3
I 3
D 4
 * from: $Header: disktape.h,v 1.3 92/12/02 03:44:07 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: disktape.h,v 1.4 93/04/30 00:02:16 torek Exp $ (LBL)
E 4
E 3
 */

/*
 * Commands common to disk and tape devices, but not other SCSI devices.
 */
I 3
#define	CMD_MODE_SELECT6	0x15	/* mode select (6 byte cdb) */
#define	CMD_MODE_SENSE6		0x1a	/* mode sense (6 byte cdb) */
E 3

I 3
#define	CMD_MODE_SELECT10	0x55	/* mode select (10 byte cdb) */
#define	CMD_MODE_SENSE10	0x5a	/* mode sense (10 byte cdb) */

E 3
/*
D 3
 * Structure of a MODE SENSE command (i.e., the cdb).
E 3
I 3
 * Structure of MODE SELECT commands (i.e., the cdb; 6 & 10 byte flavors).
 * The only difference is that the 10-byte version can give more parameter
 * bytes.
E 3
 */
D 3
struct scsi_cdb_modesense {
	u_char	cdb_cmd,	/* command */
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:5,	/* reserved */
		cdb_xxx1,	/* reserved */
		cdb_xxx2,	/* reserved */
E 3
I 3
struct scsi_cdb_modeselect6 {
	u_char	cdb_cmd,	/* 0x15 */
		cdb_lun_flags,	/* LUN + flags */
		cdb_xxx[2],	/* reserved */
		cdb_len,	/* parameter list length */
		cdb_ctrl;	/* control byte */
};
struct scsi_cdb_modeselect10 {
	u_char	cdb_cmd,	/* 0x55 */
		cdb_lun_flags,	/* LUN + flags */
		cdb_xxx[5],	/* reserved */
		cdb_lenh,	/* parameter list length (MSB) */
		cdb_lenl,	/* parameter list length (LSB) */
		cdb_ctrl;	/* control byte */
};
/* flags in SCSI_MODESELECT commands */
#define	SCSI_MSEL_SCSI1_DATA	0x00	/* SCSI-1 data format */
#define	SCSI_MSEL_SCSI2_DATA	0x10	/* SCSI-2 data format */
#define	SCSI_MSEL_DONTSAVE	0x00	/* don't save pages */
#define	SCSI_MSEL_SAVEPAGES	0x01	/* save mode pages */

/*
 * Structure of MODE SENSE command (i.e., the cdb; 6 & 10 byte flavors).
 * Again, the 10-byte version merely allows more parameter bytes.
I 4
 * Note that these lengths include the MODE SENSE headers, while those
 * for individual mode pages do not.  (Consistency?  What's that?)
E 4
 */
struct scsi_cdb_modesense6 {
	u_char	cdb_cmd,	/* 0x1a */
		cdb_lun_flags,	/* logical unit number + flags */
		cdb_pcc,	/* page control & code */
		cdb_xxx,	/* reserved */
E 3
		cdb_len,	/* allocation length */
		cdb_ctrl;	/* control byte */
};
I 3
struct scsi_cdb_modesense10 {
	u_char	cdb_cmd,	/* 0x5a */
		cdb_lun_flags,	/* logical unit number + flags */
		cdb_pcc,	/* page control & code */
		cdb_xxx[4],	/* reserved */
		cdb_lenh,	/* allocation length (MSB) */
		cdb_lenl,	/* allocation length (MSB) */
		cdb_ctrl;	/* control byte */
};
/* flags in SCSI_MODESENSE commands */
#define	SCSI_MSENSE_DBD		0x08	/* device returns db descriptors */
E 3

I 3
/* page controls */
#define	SCSI_MSENSE_PCTL_CUR	0x00	/* return current parameters */
#define	SCSI_MSENSE_PCTL_VAR	0x40	/* return variable parameters */
#define	SCSI_MSENSE_PCTL_DFLT	0x80	/* return default parameters */
#define	SCSI_MSENSE_PCTL_SAVED	0xc0	/* return saved parameters */

E 3
/*
D 3
 * Structure of returned mode sense data.
E 3
I 3
 * Both MODE_SENSE and MODE_SELECT use a Mode Parameter Header,
 * followed by an array of Block Descriptors, followed by an array
 * of Pages.  We define structures for the Block Descriptor and Page
D 4
 * first, then the two (6 and 10 byte) headers.
E 4
I 4
 * header first, then the two (6 and 10 byte) Mode Parameter headers
 * (not including the Block Descriptor(s) and any mode pages themselves).
E 4
E 3
 */
D 3
struct scsi_modesense {
E 3
I 3
struct scsi_ms_bd {		/* mode sense/select block descriptor */
	u_char	bd_dc,		/* density code (tapes only) */
		bd_nbh,		/* number of blocks (MSB) */
		bd_nbm,		/* number of blocks */
		bd_nbl,		/* number of blocks (LSB) */
		bd_xxx,		/* reserved */
		bd_blh,		/* block length (MSB) */
		bd_blm,		/* block length */
		bd_bll;		/* block length (LSB) */
};
D 4
struct scsi_ms_page {		/* mode sense/select page */
E 4
I 4
struct scsi_ms_page_hdr {	/* mode sense/select page header */
E 4
	u_char	mp_psc,		/* saveable flag + code */
D 4
		mp_len,		/* parameter length */
		mp_parm[1];	/* parameters (actual size mp_len) */
E 4
I 4
		mp_len;		/* parameter length (excludes this header) */
		/* followed by parameters */
E 4
};
#define	SCSI_MS_MP_SAVEABLE	0x80	/* page can be saved */
/*				0x40	   reserved */
#define	SCSI_MS_PC_MASK		0x3f	/* page code mask */

/*
 * Structure of returned mode sense6 / mode select6 (hence "ms6") data.
 */
struct scsi_ms6 {
E 3
	u_char	ms_len,		/* total sense data length */
D 3
		ms_mt,		/* medium type */
		ms_wbs,		/* write protect, buffered mode, & speed */
		ms_bdl;		/* block descriptor length */
	struct scsi_ms_bdesc {
		u_char	dc,	/* density code */
			nbh,	/* number of blocks (MSB) */
			nbm,	/* number of blocks */
			nbl,	/* number of blocks (LSB) */
			xxx,	/* reserved */
			blh,	/* block length (MSB) */
			blm,	/* block length */
			bll;	/* block length (LSB) */
	} ms_bd[1];
	/* followed by Vendor Unique bytes */
E 3
I 3
		ms_mt,		/* medium type (disks only?) */
		ms_dsp,		/* device specific parameter */
		ms_bdl;		/* block descriptor length (bytes) */
D 4
	struct	scsi_ms_bd ms_bd[1];	/* actually varies */
E 4
I 4
	/* followed by block descriptors, if any */
E 4
	/* followed by pages, if any */
E 3
};
I 3
/*
 * Same, but for ms10.
 */
struct scsi_ms10 {
	u_char	ms_lenh,	/* total sense length (MSB) */
		ms_lenl,	/* total sense length (LSB) */
		ms_mt,		/* medium type (disks only?) */
		ms_dsp,		/* device specific parameter */
		ms_xxx[2],	/* reserved */
		ms_bdlh,	/* block descriptor length (bytes) (MSB) */
		ms_bdll;	/* block descriptor length (bytes) (LSB) */
D 4
	struct	scsi_ms_bd ms_bd[1];	/* actually varies */
E 4
I 4
	/* followed by block descriptors, if any */
E 4
	/* followed by pages, if any */
};
E 3

I 3
/* values for the Medium Type field - disks */
#define	SCSI_MS_MT_DEFAULT	0x00	/* whatever is current */
#define	SCSI_MS_MT_SS		0x01	/* single sided, unspecified medium */
#define	SCSI_MS_MT_DS		0x02	/* double sided, unspecified medium */
#define	SCSI_MS_MT_8SSSD	0x05	/* 8" floppy, SSSD (X3.73-1980) */
#define	SCSI_MS_MT_8DSSD	0x06	/* 8" floppy, DSSD (X3B8-140) */
#define	SCSI_MS_MT_8SSDD	0x09	/* 8" floppy, SSDD (X3B8/78-139) */
#define	SCSI_MS_MT_8DSDD	0x0a	/* 8" floppy, DSDD (X3.121-1984) */
#define	SCSI_MS_MT_5SSSD	0x0d	/* 5.25" floppy, SSSD (X3.82-1980) */
#define	SCSI_MS_MT_5DSDD	0x12	/* 5.25" floppy, DSDD (X3.125-1984) */
#define	SCSI_MS_MT_5DSDD96	0x16	/* 5.25", DSDD, 96tpi (X3.126-198X) */
#define	SCSI_MS_MT_5DSQD	0x1a	/* 5.25", DSQD, 96tpi (DIS 8630) */
#define	SCSI_MS_MT_3DS		0x1e	/* 3.5", double sided (X3.137-198X) */

/* values for the Medium Type field - tapes */
#define	SCSI_MS_MT_QIC_12T	0x40	/* 0.25", 12 tracks */
#define	SCSI_MS_MT_QIC_24T	0x44	/* 0.25", 24 tracks */

/* values for the Device Specific Parameter field */
#define	SCSI_MS_DSP_WP		0x80	/* write protect (both disk & tape) */

	/* if disk */
#define	SCSI_MS_DSP_DPO_FUA	0x10	/* cache flags DPO, FUA supported */

	/* if tape */
#define	SCSI_MS_DSP_UNBUFFERED	0x00	/* unbuffered writes */
#define	SCSI_MS_DSP_BUFFERED	0x10	/* buffered writes */
#define	SCSI_MS_DSP_BUF2	0x20	/* buffered, for shared tapes */
/*				0x30..0x70 reserved */
#define	SCSI_MS_DSP_SPEED_DFLT	0x00	/* use device default speed */
#define	SCSI_MS_DSP_SPEED_MASK	0x0f	/* mask for non-default speeds */

/* values for the Density Code field - tapes */
#define	SCSI_MS_DC_DEFAULT	0	/* use device default density */
#define	SCSI_MS_DC_9T_800BPI	1	/* 9 track, 800 bpi */
#define	SCSI_MS_DC_9T_1600BPI	2	/* 9 track, 1600 bpi */
#define	SCSI_MS_DC_9T_6250BPI	3	/* 9 track, 6250 bpi */
#define	SCSI_MS_DC_QIC_XX1	4	/* QIC-11? 4 or 9 track, 8000 bpi */
#define	SCSI_MS_DC_QIC_XX2	5	/* QIC-11? 4 or 9 track, 8000 bpi */
#define	SCSI_MS_DC_9T_3200BPI	6	/* 9 track, 3200 bpi */
#define	SCSI_MS_DC_QIC_XX3	7	/* QIC, 4 track, 6400 bpi */
#define	SCSI_MS_DC_CS_XX4	8	/* cassette 4 track, 8000 bpi */
#define	SCSI_MS_DC_HIC_XX5	9	/* half inch cartridge, 18 track */
#define	SCSI_MS_DC_HIC_XX6	10	/* HIC, 22 track, 6667 bpi */
#define	SCSI_MS_DC_QIC_XX7	11	/* QIC, 4 track, 1600 bpi */
#define	SCSI_MS_DC_HIC_XX8	12	/* HIC, 24 track, 12690 bpi */
#define	SCSI_MS_DC_HIC_XX9	13	/* HIC, 24 track, 25380 bpi */

E 3
/*
I 3
 * Common page codes.
 */
/*				0x01	   device specific */
#define	SCSI_MS_PC_DR		0x02	/* disconnect/reconnect control */
/*				0x03..0x08 device specific */
#define	SCSI_MS_PC_PDEV		0x09	/* peripheral device page */
#define	SCSI_MS_PC_CTLMODE	0x0a	/* control mode page */
/*				0x0b..0x1f device specific */
/*				0x20..0x3e vendor specific */
#define	SCSI_MS_PC_ALL		0x3f	/* all pages */

/*
 * Structure of a Disconnect/Reconnect Control mode page.
 */
struct scsi_page_dr {
D 4
	u_char	dr_psc,		/* saveable flag + code (0x02) */
		dr_len,		/* length (0x0e) */
		dr_full,	/* buffer full ratio */
E 4
I 4
	u_char	dr_full,	/* buffer full ratio */
E 4
		dr_empty,	/* buffer empty ratio */
		dr_inacth,	/* bus inactivity timeout (MSB) */
		dr_inactl,	/* bus inactivity timeout (LSB) */
		dr_disconh,	/* disconnect time limit (MSB) */
		dr_disconl,	/* disconnect time limit (LSB) */
		dr_conh,	/* connect time limit (MSB) */
		dr_conl,	/* connect time limit (LSB) */
		dr_bursth,	/* maximum burst size (MSB) */
		dr_burstl,	/* maximum burst size (LSB) */
		dr_dtdc,	/* Data Transfer Disconnect Control (below) */
		dr_xxx[3];	/* reserved */
};
/* Data Transfer Disconnect Control */
#define	SCSI_DR_DTDC_MASK	0x03	/* mask for valid bits */
#define	SCSI_DR_DTDC_NONE	0x00	/* no control */
#define	SCSI_DR_DTDC_NOTDATA	0x01	/* never during data transfer */
#define	SCSI_DR_DTDC_RSVD	0x02	/* reserved */
#define	SCSI_DR_DTDC_NOTD2	0x03	/* never during/after data transfer */

/*
E 3
 * Structure of a PREVENT/ALLOW MEDIUM REMOVAL command.
 */
struct scsi_cdb_pamr {
	u_char	cdb_cmd,	/* 0x1e */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:5,	/* reserved */
E 3
I 3
		cdb_lun_xxx,	/* logical unit number + reserved */
E 3
		cdb_xxx1,	/* reserved */
		cdb_xxx2,	/* reserved */
		cdb_prevent,	/* 1=prevent, 0=allow */
		cdb_ctrl;
};
E 1
