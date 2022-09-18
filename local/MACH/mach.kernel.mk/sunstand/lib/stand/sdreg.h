/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sdreg.h,v $
 * Revision 2.2  89/07/12  00:23:12  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/* @(#)sdreg.h	1.2 88/02/08	Copyr 1987 Sun Micro */

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
 * SCSI disk controller specific stuff.
 */

/*
 * Error code fields for MD21 extended sense struct.
 * Not exhaustive - just those we treat specially.
 */

#define	SC_ERR_READ_RECOV_RETRIES 0x17	/* ctlr corrected read error w/retry */
#define	SC_ERR_READ_RECOV_ECC     0x18	/* ctlr corrected read error w/ECC */

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
 * Disk defect list - used by format command.
 */

/******************** NOTE: this should be cleaned up! ***********************/
#define ST506_NDEFECT	127     /* must fit in 1K controller buffer... */
#define ESDI_NDEFECT	ST506_NDEFECT	/* hack??? */

#define RDEF_ALL	0	/* read all defects */
#define RDEF_MANUF	1	/* read manufacturer's defects */
#define RDEF_CKLEN	2	/* check length of manufacturer's list */

struct format_parms {		/* physical BFI format */
	u_short	reserved;
	u_short	list_len;
	struct defect {
		unsigned cyl  : 24;
		unsigned head : 8;
		long	bytes_from_index;
	} defect[ESDI_NDEFECT];
};

/*
 * Defect list returned by READ_DEFECT_LIST command.
 */

struct md21_defect_hdr {	/* defect list header */
	u_char	reserved_0;
	u_char	descrip;
	u_short	len;
};

struct md21_bfi_defect {		/* defect in bytes from index format */
	unsigned cyl  : 24;
	unsigned head : 8;
	long	bytes_from_index;
};

struct md21_bfi_defect_list {		/* defect list, BFI format */
	struct md21_defect_hdr		md21_defect_hdr;
	struct md21_bfi_defect 		md21_bfi_defect[ESDI_NDEFECT];
};

/*
 * Defect list expected by REASSIGN_BLOCK command (logical block format).
 * This defect list is limited to 1 defect, as that is the only way
 * we use it.
 */

struct md21_rab_defect_list {		/* defect list for reassign block */ 
	u_short	reserved;		/* cruft */
	u_short len;			/* length, in bytes of defects */
					/* does not include reserved, len */
	u_int 	lba;			/* defect, in logical blk format */
};
