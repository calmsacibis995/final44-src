/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	streg.h,v $
 * Revision 2.5  89/03/09  21:47:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:56:06  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.3  88/12/07  17:24:23  mikeg
 * 	Entered new version of this file from SunOS 3.5 into
 * 	the Mach kernel source tree.
 * 	[88/12/01  14:52:38  mikeg]
 * 
 */
/* @(#)streg.h	1.1	12/21/87 Copyright (c) 1987 Sun Microsystems, Inc. */


/*
 * Defines for SCSI tape drives.
 */
#define ST_SYSGEN   			/* Enable Sysgen controller support */
/* #define ST_AUTOPOSITION  		/* Enable seek support */
#define ST_TIMEOUT			/* Enable command timeouts */

#define MAX_ST_DEV_SIZE		65535	/* 64KB limit for variable length I/O */
#define MAX_AUTOLOAD_DELAY	60	/* 120 Sec. Auto-load maximum delay */

#ifdef	lint
#define ST_SYSGEN   			/* Enable Sysgen controller support */
#define ST_AUTOPOSITION  		/* Enable seek support */
#define ST_TIMEOUT			/* Enable command timeouts */
#define sun2				/* Enable sun2 support */
#define CPU_SUN2_120		2
#endif	lint

/*
 * Driver state machine codes -- Do not change order!
 * Opening states:
 *	closed -> opening         ||   -> open  (no tape change, no error)
 *		  opening_sysgen
 *
 *	closed -> opening         ||   -> open  (tape change, no error)
 *                opening_delay   ||
 *
 *	closed -> opening         ||   -> opening_sysgen  -> open  (sysgen)
 *                opening_delay   ||
 *
 *	closed -> opening         ||   -> open_failed_loading ||  -> closed
 *                opening_delay	          open_failed_tape    ||     (error)
 *			     	          open_failed
 *
 * Closing states:
 *	open   -> closing -> closed
 *
 * Open states:
 *	open   -> open (passed command)
 *
 *	open   -> sensing -> open (failed command)
 *
 *	open   -> sensing -> append_testing -> open  (failed write append)
 *
 *	open   -> sensing -> append_testing -> retrying_cmd -> open
 *					       (passed write append)
 */
#define CLOSED			 0
#define CLOSING			 1
#define OPEN_FAILED_LOADING	 2
#define OPEN_FAILED_TAPE	 3
#define OPEN_FAILED		 4
#define OPENING_SYSGEN		 5
#define OPENING_DELAY		 6
#define OPENING			 7
#define APPEND_TESTING		 8
#define RETRYING_CMD		 9
#define SENSING			10
#define OPEN			11

/*
 * Eof codes.
 */
#define ST_NO_EOF		0x00
#define ST_EOF			0x01
#define ST_EOF_PENDING		0x02
#define ST_EOT			ST_EOF

/*
 * Operation codes.
 */
#define SC_REWIND		0x01
#define SC_QIC02		0x0D
#define SC_READ_XSTATUS_CIPHER	0xe0		/* Sun-2, Cipher tape only */
#define SC_WRITE_FILE_MARK	0x10
#define SC_SPACE_REC		0x11
#define SC_ERASE_TAPE		0x19
#define SC_LOAD			0x1B
#define SC_UNLOAD		0x80		/* phony - for int use only */
#define SC_BSPACE_FILE		0x81		/* phony - for int use only */
#define SC_SPACE_FILE		0x82		/* phony - for int use only */
#define SC_RETENSION		0x83		/* phony - for int use only */
#define SC_DEN1600		0x84		/* phony - for int use only */
#define SC_DEN6250		0x85		/* phony - for int use only */
#define SC_READ_APPEND		0x86		/* phony - for int use only */
	/*
/* Define which commands have data-out DMA phase */
#define SC_IS_WRITE_COMMAND(cmd)	((cmd) == SC_WRITE_FILE_MARK  || \
					 (cmd) == SC_ERASE_TAPE       || \
					 (cmd) == SC_WRITE)

/*
 * Supported tape device types plus default type for opening.
 */
#define ST_TYPE_INVALID		 0
#define ST_TYPE_DEFAULT		 1
#define ST_TYPE_SYSGEN		 2
#define ST_TYPE_EMULEX		 3
#define ST_TYPE_ARCHIVE		 4
#define ST_TYPE_WANGTEK		 5
#define ST_TYPE_HP		 6
#define ST_TYPE_KENNEDY		 7
#define ST_TYPE_CDC		 8
#define ST_TYPE_ADAPTEC		 9
#define ST_TYPE_FUJI		10
#define ST_TYPE_EXABYTE		11

/* Defines for supported drive options */
#define ST_VARIABLE		0x01	/* supports variable length I/O */
#define ST_QIC			0x02	/* QIC tape drive */
#define ST_REEL			0x04	/* 1/2-inch reel tape drive */
#define ST_BSF			0x08	/* supports backspace file */
#define ST_BSR			0x10	/* supports backspace record */
#define ST_NODISCON		0x20	/* no disconnect/reconnect support */

/* 
 * Misc defines for unknown SCSI tape drives/controllers 
 */
#define ST_DEFAULT_BSIZE	512
#define ST_DEFAULT_DEN1600	0x00
#define ST_DEFAULT_DEN6250	0x00
#define ST_DEFAULT_SPEED	0x00
#define ST_DEFAULT_OPTIONS	(ST_QIC)
#define IS_DEFAULT(dsi)		(dsi->un_ctype == ST_TYPE_DEFAULT)

/* 
 * Misc defines specific to CDC 1/2-inch HI/TC Cartridge SCSI tape drive
 */
#define ST_CDC_BSIZE		512
#define ST_CDC_DEN1600		0x00
#define ST_CDC_DEN6250		0x00
#define ST_CDC_SPEED		0x00
#define ST_CDC_OPTIONS		(ST_QIC | ST_VARIABLE | ST_BSF)
#define IS_CDC(dsi)		(dsi->un_ctype == ST_TYPE_CDC)

/* 
 * Misc defines specific to FUJITSU 1/2-inch Cartridge SCSI tape drive
 */
#define ST_FUJI_BSIZE		1024
#define ST_FUJI_DEN1600		0x00
#define ST_FUJI_DEN6250		0x00
#define ST_FUJI_SPEED		0x00
#define ST_FUJI_OPTIONS		(ST_VARIABLE | ST_BSF | ST_BSR)
#define IS_FUJI(dsi)		(dsi->un_ctype == ST_TYPE_FUJI)

/* 
 * Misc defines specific to HP 88780A 1/2-inch reel SCSI-2 tape drive
 */
#define ST_HP_BSIZE		10240
#define ST_HP_DEN1600		0x02
#define ST_HP_DEN6250		0x03
#define ST_HP_SPEED		0x00
#define ST_HP_OPTIONS		(ST_REEL | ST_VARIABLE | ST_BSF | ST_BSR)
#define IS_HP(dsi)		(dsi->un_ctype == ST_TYPE_HP)

/* 
 * Misc defines specific to Kennedy 9600 1/2-inch reel SCSI tape drive
 */
#define ST_KENNEDY_BSIZE	10240
#define ST_KENNEDY_DEN1600	0x02
#define ST_KENNEDY_DEN6250	0x03
#define ST_KENNEDY_SPEED	0x00
#define ST_KENNEDY_OPTIONS	(ST_REEL | ST_VARIABLE | ST_BSF | ST_BSR)
#define IS_KENNEDY(dsi)		(dsi->un_ctype == ST_TYPE_KENNEDY)

/* 
 * Misc defines specific to Wangtek and Archive QIC-120
 * 1/4-inch cartridge SCSI tape drives
 */
#define ST_ARCHIVE_BSIZE	512
#define ST_ARCHIVE_DEN1600	0x00
#define ST_ARCHIVE_DEN6250	0x00
#define ST_ARCHIVE_SPEED	0x00
#define ST_ARCHIVE_OPTIONS	(ST_QIC | ST_BSF | ST_BSR)
#define IS_ARCHIVE(dsi)		(dsi->un_ctype == ST_TYPE_ARCHIVE)

/* 
 * Misc defines specific to Emulex MT-02 SCSI
 * 1/4-inch cartridge tape controller
 */
#define ST_EMULEX_BSIZE		512
#define ST_EMULEX_DEN1600	0x84
#define ST_EMULEX_DEN6250	0x00
#define ST_EMULEX_SPEED		0x00
#define ST_EMULEX_OPTIONS	(ST_QIC)
#define IS_EMULEX(dsi)		(dsi->un_ctype == ST_TYPE_EMULEX)

/* 
 * Misc defines specific to Adaptec ACB-3530A SCSI tape controller
 */
#define ST_ADAPTEC_BSIZE	512
#define ST_ADAPTEC_DEN1600	0x04
#define ST_ADAPTEC_DEN6250	0x00
#define ST_ADAPTEC_SPEED	0x00
#define ST_ADAPTEC_OPTIONS	(ST_QIC)
#define IS_ADAPTEC(dsi)		(dsi->un_ctype == ST_TYPE_ADAPTEC)

/* 
 * Misc defines specific to Sysgen SCSI-QIC tape controller
 */
#define ST_SYSGEN_BSIZE		512
#define ST_SYSGEN_DEN1600	0x26
#define ST_SYSGEN_DEN6250	0x27
#define ST_SYSGEN_SPEED		0x00
#define ST_SYSGEN_OPTIONS	(ST_QIC | ST_NODISCON)
#define IS_SYSGEN(dsi)		(dsi->un_ctype == ST_TYPE_SYSGEN)

/* 
 * Misc defines specific to Exabyte tape controller
 */
#define ST_EXABYTE_BSIZE	1024
#define ST_EXABYTE_DEN1600	0x00
#define ST_EXABYTE_DEN6250	0x00
#define ST_EXABYTE_SPEED	0x00
#define ST_EXABYTE_OPTIONS	(ST_QIC)
#define IS_EXABYTE(dsi)		(dsi->un_ctype == ST_TYPE_EXABYTE)

/*
 * defines for SCSI tape CDB.
 */
#undef	t_code
#undef	high_count
#undef	mid_count
#undef	low_count
struct	scsi_cdb6 {		/* scsi command description block */
	u_char	cmd;		/* command code */
	u_char	lun	: 3;	/* logical unit number */
	u_char	t_code	: 5;	/* high part of address */
	u_char	high_count;	/* middle part of address */
	u_char	mid_count;	/* low part of address */
	u_char	low_count;	/* block count */
	u_char	vu_57	: 1;	/* vendor unique (byte 5 bit 7) */
	u_char	vu_56	: 1;	/* vendor unique (byte 5 bit 6) */
	u_char		: 4;	/* reserved */
	u_char	fr	: 1;	/* flag request (interrupt at completion) */
	u_char	link	: 1;	/* link (another command follows) */
};


/*
 * Parameter list for the MODE_SELECT and MODE_SENSE commands.
 * The parameter list contains a header, followed by zero or more
 * block descriptors, followed by vendor unique parameters, if any.
 * Note, only one 8-byte block descriptor is used for 1/2-inch SCSI
 * tape devices (e.g. CDC HI/TC, HP SCSI-2, and Kennedy).
 */
#define MS_BD_LEN	8
struct st_ms_mspl {
	u_char	reserved1;	/* reserved, sense data length */
	u_char	reserved2;	/* reserved, medium type */
	u_char	wp	:1;	/* write protected */
	u_char	bufm	:3;	/* buffered mode */
	u_char	speed	:4;	/* speed */
	u_char	bd_len;		/* block length in bytes */
	u_char	density;	/* density code */
	u_char	high_nb;	/* number of logical blocks on the medium */
	u_char	mid_nb;		/* that are to be formatted with the density */
	u_char	low_nb;		/* code and block length in block descriptor */
	u_char	reserved;	/* reserved */
	u_char	high_bl;	/* block length */
	u_char	mid_bl;		/*   "      "   */
	u_char	low_bl;		/*   "      "   */
};

/*
 * SCSI tape REQUEST SENSE parameter block.  Note,
 * this structure should have an even number of bytes to
 * eliminate any byte packing problems with our host adapters.
 */
struct	st_sense {		/* scsi tape extended sense for error class 7 */
	/* byte 0 */
	u_char	adr_val	: 1;	/* sense data is valid */
	u_char		: 7;	/* fixed at binary 1110000 */
	/* byte 1 */
	u_char	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	u_char	fil_mk	: 1;	/* file mark on device */
	u_char	eom	: 1;	/* end of media */
	u_char	ili	: 1;	/* incorrect length indicator */
	u_char		: 1;	/* reserved */
	u_char	key	: 4;	/* sense key, see below */
	/* bytes 3 through 6 */
	u_char	info_0;		/* sense information byte 1 */
	u_char	info_1;		/* sense information byte 2 */
	u_char	info_2;		/* sense information byte 3 */
	u_char	info_3;		/* sense information byte 4 */
	/* bytes 7 through 13 */
	u_char	add_len;	/* number of additional bytes */
	u_char	optional_8;	/* search/copy src sense only */
	u_char	optional_9;	/* search/copy dst sense only */
	u_char	optional_10;	/* search/copy only */
	u_char	optional_11;	/* search/copy only */
	u_char	error;		/* error code */
	u_char	error1;		/* error code qualifier */
	/* bytes 14 through 15 */
	u_char	optional_14;	/* reserved */
	u_char	optional_15;	/* reserved */
};

#ifdef	ST_SYSGEN
/*
 * Sense info returned by sysgen controllers.  Note,
 * this structure should always be 16 bytes or the controller
 * will not clear it's error condition.  Also, you must
 * always follow an error condition with a request sense cmd.
 */
struct  sysgen_sense {
	/* Bytes 0 - 3  */
	u_char  disk_sense[4];		/* sense data from disk */
	/* byte 4 */
	u_char  valid4		:1;	/* some other bit set in this byte */
	u_char  no_cart		:1;	/* no cartrige, or removed */
	u_char  not_ready	:1;	/* drive not present */
	u_char  write_prot	:1;	/* write protected */
	u_char  eot		:1;	/* end of last track */
	u_char  data_err	:1;	/* unrecoverable data error */
	u_char  no_err		:1;	/* data transmitted not in error */
	u_char file_mark	:1;	/* file mark detected */
	/* byte 5 */
	u_char  valid5		:1;	/* some other bit set in this byte */
	u_char  illegal		:1;	/* illegal command */
	u_char  no_data		:1;	/* unable to find data */
	u_char  retries		:1;	/* 8 or more retries needed */
	u_char  bot		:1;	/* beginning of tape */
	u_char			:2;	/* reserved */
	u_char  reset		:1;	/* power-on or reset since last op */
	/* bytes 6 through 9 */
	short   retry_ct;		/* retry count */
	short   underruns;		/* number of underruns */
	/* bytes 10 through 15 */
	u_char   disk_xfer[3];		/* no. blks in last disk operation */
	u_char   tape_xfer[3];		/* no. blks in last tape operation */
};
#endif	ST_SYSGEN

/*
 * Macros for getting information from the sense data returned
 * by the various SCSI 1/2-inch tape controllers.  Note, this
 * use byte 2 of the extended sense descriptor block to mimimize
 * SCSI controller dependencies.
 */
#define ST_FILE_MARK(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->fil_mk) ? 1 : 0)

#define ST_END_OF_TAPE(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->eom) ? 1 : 0)

#define ST_LENGTH(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->ili) ? 1 : 0)

#define ST_WRITE_PROT(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_WRITE_PROTECT))

#define ST_ILLEGAL(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_ILLEGAL_REQUEST))

#define ST_NO_CART(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_NOT_READY))

#define ST_RESET(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_UNIT_ATTENTION))

#define ST_CORRECTABLE(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_RECOVERABLE_ERROR))

