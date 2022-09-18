h20360
s 00002/00002/00122
d D 8.1 93/06/10 21:21:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00068/00109
d D 5.3 93/02/01 11:28:43 torek 3 2
c rm bitfields; move mode select to common
e
s 00005/00000/00172
d D 5.2 92/07/23 14:00:56 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00172/00000/00000
d D 5.1 92/07/10 00:03:10 torek 1 0
c date and time created 92/07/10 00:03:10 by torek
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
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: tape.h,v 1.2 92/05/15 11:24:06 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: tape.h,v 1.3 92/12/02 03:53:14 torek Exp $ (LBL)
E 3
 */

/*
 * SCSI definitions for Sequential Access Devices (tapes).
I 3
 *
 * Commands defined in common headers (scsi.h or disktape.h) are omitted.
E 3
 */
#define	CMD_REWIND		0x01	/* rewind */
#define	CMD_READ_BLOCK_LIMITS	0x05	/* read block limits */
#define	CMD_READ		0x08	/* read */
#define	CMD_WRITE		0x0a	/* write */
#define	CMD_TRACK_SELECT	0x0b	/* track select */
#define	CMD_READ_REVERSE	0x0f	/* read reverse */
#define	CMD_WRITE_FILEMARK	0x10	/* write file marks */
#define	CMD_SPACE		0x11	/* space */
#define	CMD_VERIFY		0x13	/* verify */
#define	CMD_RBD			0x14	/* recover buffered data */
D 3
#define	CMD_MODE_SELECT		0x15	/* mode select */
E 3
#define	CMD_RESERVE_UNIT	0x16	/* reserve unit */
#define	CMD_RELEASE_UNIT	0x17	/* release unit */
/*	CMD_COPY		0x18	   copy (common to all scsi devs) */
#define	CMD_ERASE		0x19	/* erase */
D 3
#define	CMD_MODE_SENSE		0x1a	/* mode sense */
E 3
#define	CMD_LOAD_UNLOAD		0x1b	/* load/unload */
#define	CMD_PAMR		0x1e	/* prevent/allow medium removal */

/*
 * Structure of READ, WRITE, READ REVERSE, RECOVER BUFFERED DATA
 * commands (i.e., the cdb).
 * Also used for VERIFY commands.
 */
struct scsi_cdb_rw {
	u_char	cdb_cmd,	/* 0x08 or 0x0a or 0x0f or 0x13 or 0x14 */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx:3,	/* reserved */
		cdb_bytecmp:1,	/* byte-by-byte comparison (VERIFY only) */
		cdb_fixed:1,	/* fixed length blocks */
E 3
I 3
		cdb_lun_bf,	/* LUN + reserved + bytecmp + fixed */
E 3
		cdb_lenh,	/* transfer length (MSB) */
		cdb_lenm,	/* transfer length */
		cdb_lenl,	/* transfer length (LSB) */
		cdb_ctrl;	/* control byte */
};
I 3
#define	SCSI_RW_BYTECMP		0x02	/* byte compare flag if verify */
#define	SCSI_RW_FIXEDBLK	0x01	/* fixed block size for read/write */
E 3

/*
 * Structure of a TRACK SELECT command.
 */
struct scsi_cdb_ts {
	u_char	cdb_cmd,	/* 0x0b */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:5,	/* reserved */
E 3
I 3
		cdb_lun_xxx,	/* logical unit number + reserved */
E 3
		cdb_xxx1,	/* reserved */
		cdb_xxx2,	/* reserved */
		cdb_track,	/* track value */
		cdb_ctrl;	/* control byte */
};

/*
 * Structure of a WRITE FILEMARKS command.
 */
struct scsi_cdb_wfm {
	u_char	cdb_cmd,	/* 0x0b */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:5,	/* reserved */
E 3
I 3
		cdb_lun_xxx,	/* logical unit number + reserved */
E 3
		cdb_nfh,	/* number of filemarks (MSB) */
		cdb_nfm,	/* number of filemarks */
		cdb_nfl,	/* number of filemarks (LSB) */
		cdb_ctrl;	/* control byte */
};

/*
 * Structure of a SPACE command.
 */
struct scsi_cdb_space {
	u_char	cdb_cmd,	/* 0x0b */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:3,	/* reserved */
		cdb_code:2,	/* code (see below) */
E 3
I 3
		cdb_lun_code,	/* LUN + reserved + 2-bit code */
E 3
		cdb_counth,	/* count (MSB) */
		cdb_countm,	/* count */
		cdb_countl,	/* count (LSB) */
		cdb_ctrl;	/* control byte */
};
#define	SCSI_CMD_SPACE_BLOCKS	0	/* skip blocks */
#define	SCSI_CMD_SPACE_FMS	1	/* skip file marks */
#define	SCSI_CMD_SPACE_SFMS	2	/* skip sequential file marks */
#define	SCSI_CMD_SPACE_PEOD	3	/* skip to physical end of data */

/*
D 3
 * Mode Select parameters (data).
 */
struct scsi_msel {
	u_short	msel_xxx0;	/* reserved */
	u_char	msel_xxx1:1,	/* reserved */
		msel_bm:3,	/* buffered mode */
		msel_speed:4,	/* speed */
		msel_bdl;	/* block descriptor length */
	struct scsi_msel_bdesc {
		u_char	dc,	/* density code */
			nbh,	/* number of blocks (MSB) */
			nbm,	/* number of blocks */
			nbl,	/* number of blocks (LSB) */
			xxx,	/* reserved */
			blh,	/* block length (MSB) */
			blm,	/* block length */
			bll;	/* block length (LSB) */
	} msel_bd[1];		/* actually longer */
	/* followed by Vendor Unique bytes */
};

/* buffered mode and speed */
#define	SCSI_MSEL_BM_UNBUFFERED	0	/* unbuffered writes */
#define	SCSI_MSEL_BM_BUFFERED	1	/* buffered writes allowed */
#define	SCSI_MSEL_SPEED_DEFAULT	0	/* use device default speed */
#define	SCSI_MSEL_SPEED_LOW	1	/* use lowest speed */
#define	SCSI_MSEL_SPEED_HIGH	15	/* use highest speed */

/* density codes */
#define	SCSI_MSEL_DC_DEFAULT	0	/* use device default density */
#define	SCSI_MSEL_DC_9T_800BPI	1	/* 9 track, 800 bpi */
#define	SCSI_MSEL_DC_9T_1600BPI	2	/* 9 track, 1600 bpi */
#define	SCSI_MSEL_DC_9T_6250BPI	3	/* 9 track, 6250 bpi */
#define	SCSI_MSEL_DC_QIC_XX1	4	/* QIC-11? 4 or 9 track, 8000 bpi */
#define	SCSI_MSEL_DC_QIC_XX2	5	/* QIC-11? 4 or 9 track, 8000 bpi */
#define	SCSI_MSEL_DC_9T_3200BPI	6	/* 9 track, 3200 bpi */
#define	SCSI_MSEL_DC_QIC_XX3	7	/* QIC, 4 track, 6400 bpi */
#define	SCSI_MSEL_DC_CS_XX4	8	/* cassette 4 track, 8000 bpi 8/
#define	SCSI_MSEL_DC_HIC_XX5	9	/* half inch cartridge, 18 track */
#define	SCSI_MSEL_DC_HIC_XX6	10	/* HIC, 22 track, 6667 bpi */
#define	SCSI_MSEL_DC_QIC_XX7	11	/* QIC, 4 track, 1600 bpi */
#define	SCSI_MSEL_DC_HIC_XX8	12	/* HIC, 24 track, 12690 bpi */
#define	SCSI_MSEL_DC_HIC_XX9	13	/* HIC, 24 track, 25380 bpi */

/*
E 3
 * Structure of an ERASE command.
 */
struct scsi_cdb_erase {
	u_char	cdb_cmd,	/* 0x0b */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:4,	/* reserved */
		cdb_long:1,	/* long erase */
E 3
I 3
		cdb_lun_long,	/* LUN + reserved + long-erase flag */
E 3
		cdb_xxx1,	/* reserved */
		cdb_xxx2,	/* reserved */
		cdb_xxx3,	/* reserved */
		cdb_ctrl;	/* control byte */
};

/*
 * Structure of a LOAD/UNLOAD command.
 */
struct scsi_cdb_lu {
	u_char	cdb_cmd,	/* 0x1b */
D 3
		cdb_lun:3,	/* logical unit number */
		cdb_xxx0:4,	/* reserved */
		cdb_immed:1,	/* return status immediately */
E 3
I 3
		cdb_lun_immed,	/* LUN + reserved + immediate flag */
E 3
		cdb_xxx1,	/* reserved */
		cdb_xxx2,	/* reserved */
D 3
		cdb_xxx3:6,	/* reserved */
		cdb_reten:1,	/* retension tape */
		cdb_load:1,	/* load (else unload) */
E 3
I 3
		cdb_rl,		/* reserved + retension flag + load flag */
E 3
		cdb_ctrl;	/* control byte */
};
I 3
#define	SCSI_LU_RL_RETEN	0x02	/* retension */
#define	SCSI_LU_RL_LOAD		0x01	/* load */
#define	SCSI_LU_RL_UNLOAD	0x00	/* unload (pseudo flag) */
E 3
E 1
