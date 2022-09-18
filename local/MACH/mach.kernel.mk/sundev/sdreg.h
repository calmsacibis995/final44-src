/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sdreg.h,v $
 * Revision 2.5  90/07/03  16:49:23  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:15:46  mrt]
 * 
 * Revision 2.4  89/03/09  21:45:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:54:39  gm0w
 * 	Added new copyright as part of kernel cleanup.
 * 	[89/02/12            jjc]
 * 
 * Revision 2.2  88/12/07  17:21:28  mikeg
 * 	Entered new version of this file from SunOS 3.5 into
 * 	the kernel source tree to support the new sd driver.
 * 	[88/12/01  14:21:53  mikeg]
 * 
 */
/* @(#)sdreg.h       1.1 87/12/21 Copyr 1987 Sun Micro */

/*
 * Defines for SCSI disk drives.
 */
#define SD_TIMEOUT		/* Enable command timeouts */
/*#define FORMAT  		/* Enable on-line formatting mods */
/*#define SD_REASSIGN		/* Enable auto disk repair */

/*
 * Driver state machine codes -- Do not change order!
 * Opening states:
 *	closed -> open 
 *
 *	closed -> opening         ||   -> open
 *
 *	closed -> opening         ||   -> open
 *                opening_delay   ||
 *
 *	closed -> opening -> opening-raw -> open-raw	(if no disk label)
 *
 * Closing states:
 *	open   -> closed
 *
 * Open states:
 *	open   -> open (passed command)
 *
 *	open   -> sensing -> open (failed command)
 *
 *	open   -> sensing -> retrying_cmd -> open
 */
#define CLOSED			 0
#define OPEN_FAILED		 1
#define OPENING_DELAY		 2
#define OPENING			 3
#define	OPENING_RAW		 4
#define MAPPING			 5
#define SENSING			 6
#define RETRYING		 7
#define OPEN			 8
#define	OPENRAW			 9

/*
 * SCSI disk controller specific stuff.
 */
#define CTYPE_UNKNOWN		0
#define CTYPE_MD21		1
#define CTYPE_ACB4000		2
#define CTYPE_CCS		3

/*
 * Special commands for internal use only.
 */
#define SC_READ_LABEL		0x80	/* phony - for int use only */
#define SC_SPECIAL_READ		0x81	/* phony - for int use only */
#define SC_SPECIAL_WRITE	0x82	/* phony - for int use only */

/*
 * Define various buffer and I/O block sizes
 */
#define SECSIZE		512		/* Bytes/sector */
#define SECDIV		9		/* log2 (SECSIZE) */
#define MAXBUFSIZE	(63 * 1024)	/* 63 KB max size of buffer */

/*
 * Defines for SCSI disk format cdb.
 */
#define b_cylin			b_resid
#define fmt_parm_bits		g0_addr2	/* for format options */
#define fmt_interleave		g0_count0	/* for encode interleave */
#define defect_list_descrip	g1_addr3	/* list description bits */

/*
 * Bits in the special command flags field.
 */
#define SD_SILENT		0x0001	/* don't print error messages */
#define SD_DVMA_IN		0x0002	/* ioctl needs DVMA (in) */
#define SD_DVMA_OUT		0x0004	/* ioctl needs DVMA (out) */
#define SC_SBF_SILENT		0x0001	/* don't print error messages */
#define SC_SBF_DIAGNOSE		0x0002	/* collect stats for diagnostic */
#define SC_SBF_DIR_IN		0x0004	/* need to copyin info */
#define SC_SBF_IOCTL		0x8000	/* cmd being run on behalf of ioctl */
#define SC_NOMSG		0x01	/* don't print error messages */
#define SC_DIAG			0x02	/* collect diagnostic info ??? */
#define SC_IOCTL		0x04	/* running cmd for ioctl */

/*
 * Error code fields for MD21 extended sense struct.
 * Not exhaustive - just those we treat specially.
 */
#define SC_ERR_READ_RECOV_RETRIES	0x17	/* ctlr fixed error w/retry */
#define SC_ERR_READ_RECOV_ECC		0x18	/* ctlr fixed error w/ECC */


/*
 * ACB4000 error codes.  
 * They are the concatenation of the class and code info.
 */

/* Class 0 - drive errors */
#define SC_ERR_ACB_NO_SENSE	0x00	/* no error or sense info */
#define SC_ERR_ACB_NO_INDEX	0x01	/* no index or sector pulse */
#define SC_ERR_ACB_NO_SEEK_CMPL	0x02	/* no seek complete signal */
#define SC_ERR_ACB_WRT_FAULT	0x03	/* write fault */
#define SC_ERR_ACB_NOT_READY	0x04	/* drive not ready */
#define SC_ERR_ACB_NO_TRACK_0	0x06	/* no track 0 */

/* Class 1 - target errors */
#define SC_ERR_ACB_ID_CRC	0x10	/* ID field not found after retry */
#define SC_ERR_ACB_UNCOR_DATA	0x11	/* uncorrectable data error */
#define SC_ERR_ACB_ID_ADDR_MK	0x12	/* missing ID address mark */
#define SC_ERR_ACB_REC_NOT_FND	0x14	/* record not found */
#define SC_ERR_ACB_SEEK		0x15	/* seek error */
#define SC_ERR_ACB_DATA_CHECK	0x18	/* data check */

/* Class 2 - system-related errors */
#define SC_ERR_ACB_ECC_VERIFY	0x19	/* ECC error detected during verify */
#define SC_ERR_ACB_INTERLEAVE	0x1A	/* specified interleave too large */
#define SC_ERR_ACB_BAD_FORMAT	0x1C	/* drive not properly formatted */
#define SC_ERR_ACB_ILLEGAL_CMD	0x20	/* illegal command */
#define SC_ERR_ACB_ILLEGAL_BLK	0x21	/* illegal block address */
#define SC_ERR_ACB_VOL_OVERFLOW	0x23	/* illegal block addr after 1st blk */
#define SC_ERR_ACB_BAD_ARG	0x24	/* bad argument */
#define SC_ERR_ACB_ILLEGAL_LUN	0x25	/* invalid logical unit number */
#define SC_ERR_ACB_CART_CHANGE	0x28	/* new cartridge inserted */
#define SC_ERR_ACB_ERR_OVERFLOW	0x2C	/* too many errors */

/* Unknown psuedo error - used for convenience */
#define SC_ERR_ACB_ERR_UNKNOWN	0xFF	/* unknown psuedo error */


/*
 * defines for value of fmt_parm_bits.
 */
#define FPB_BFI			0x04		/* bytes-from-index fmt */
#define FPB_CMPLT		0x08		/* full defect list provided */
#define FPB_DATA		0x10		/* defect list data provided */

/*
 * Defines for value of defect_list_descrip.
 */
#define DLD_MAN_DEF_LIST	0x10		/* manufacturer's defect list */
#define DLD_GROWN_DEF_LIST	0x08		/* grown defect list */
#define DLD_BLOCK_FORMAT	0x00		/* block format */
#define DLD_BFI_FORMAT		0x04		/* bytes-from-index format */
#define DLD_PS_FORMAT		0x05		/* physical sector format */


/*
 * Disk defect list - used by format command.
 */
/******************** NOTE: this should be cleaned up! ***********************/
#define ST506_NDEFECT	127     /* must fit in 1K controller buffer... */
#define ESDI_NDEFECT	ST506_NDEFECT	/* hack??? */

#define RDEF_ALL	0	/* read all defects */
#define RDEF_MANUF	1	/* read manufacturer's defects */
#define RDEF_CKLEN	2	/* check length of manufacturer's list */

struct scsi_bfi_defect {	/* defect in bytes from index format */
	unsigned cyl  : 24;
	unsigned head : 8;
	long	 bfi;
};

struct scsi_format_params {	/* BFI format list */
	u_short reserved;
	u_short length;
	struct  scsi_bfi_defect list[ESDI_NDEFECT];
};

/*
 * Defect list returned by READ_DEFECT_LIST command.
 */
struct scsi_defect_list {	/* BFI format list */
	u_char	reserved;
	u_char	descriptor;
	u_short	length;
	struct	scsi_bfi_defect list[ESDI_NDEFECT];
};

/*
 * Defect list format used by reassign block command (logical block format).
 * This defect list is limited to 1 defect, as that is the only way
 * we use it.
 */
struct scsi_reassign_blk {
	u_short	reserved;
	u_short length;		/* defect length in bytes ( defects * 4) */
	u_int 	defect;		/* Logical block address of defect */
};
