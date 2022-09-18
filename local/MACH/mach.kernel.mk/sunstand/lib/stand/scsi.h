/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	scsi.h,v $
 * Revision 2.2  89/07/12  00:23:02  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/* @(#)scsi.h     1.2 88/02/08 Copyr 1986 Sun Micro */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Standard SCSI control blocks.
 * These go in or out over the SCSI bus.
 */
struct	scsi_cdb {		/* scsi command description block */
	/*
	 * The first 11 bits of the command block are the same for all
	 * three defined command groups.  The first byte is an operation code
	 * which consists of a command code component and a group code 
	 * component.   The first 3 bits of the second byte are the unit
	 * number.
	 *
	 * The group code determines the length of the rest of
	 * the command. Group 0 commands are 6 bytes, Group 1 are 10 bytes, 
	 * and Group 5 are 12 bytes.  Groups 2-4 are reserved.  
	 * Groups 6 and 7 are vendor unique.
	 */
	union scsi_groups {
		/* 
		 * Sometimes we want to reference a certain byte in its 
		 * entirety.
		 */
		u_char  scsi_cdb[12];	
#define			scc_cmd		sg_un.scsi_cdb[0] /* opcode field */
#define			scc0_cntl	sg_un.scsi_cdb[5] /* Group 0 control
									byte */
#define			scc1_cntl	sg_un.scsi_cdb[9] /* Group 1 control 
									byte */
#define			scc5_cntl	sg_un.scsi_cdb[11] /* Group 5 control 
									byte */

		/* 
		 * Other times we want to reference the group, command, or
		 * unit fields as separate entities
		 */
		struct scsi_gen {
			u_char scgen_gcode :3;	/* group code */
			u_char scgen_ccode :5;	/* command code */
			u_char scgen_unit  :3;	/* unit number */
		}sc_common;

#define			scc_grpcode	sg_un.sc_common.scgen_gcode
#define			scc_cmdcode	sg_un.sc_common.scgen_ccode
#define			scc_lun		sg_un.sc_common.scgen_unit

			/*
			 * Sometimes it is better (for portability)
			 * to use SCSIGROUP and SCSICOMMAND macros to
			 * get at the components
			 */
#define			GROUPMASK 0xe0
#define			GROUPSHIFT 5
#define			COMMANDMASK 0x1f
#define			SCSIGROUP(c) (((c)&GROUPMASK) >>GROUPSHIFT)
#define			SCSICOMMAND(c) ((c)&COMMANDMASK)

		/* 
		 * And once we know what group the command is from,
		 * we can reference the individual fields through
		 * the following structures
		 *
		 *
	 	 *	G R O U P   0   F O R M A T
		 */
		struct scsi_g0 {	/* group 0 (6 byte) command format */
							/* first byte */
			u_char g0_cmd;		/* operation code */
							/* second byte */
			u_char g0_unit	:3;	/* logical unit number */
			u_char g0_addr2	:5;	/* high part of address */
							/* third byte */
			u_char g0_addr1;	/* middle part of address */
							/* fourth byte */
			u_char g0_addr0;	/* low part of address */
							/* fifth byte */
			u_char g0_count;	/* usually block count */
							/* sixth byte */
			u_char g0_v1	:1;	/* vendor unique (byte 5 bit 7*/
			u_char g0_v0	:1;	/* vendor unique (byte 5 bit 6*/
			u_char g0_x	:4;	/* reserved */
			u_char g0_flag	:1;	/* interrupt when done */
			u_char g0_link	:1;	/* another command follows */
		} g0;
#define			scc0_high_addr	sg_un.g0.g0_addr2
#define			scc0_mid_addr	sg_un.g0.g0_addr1
#define			scc0_low_addr	sg_un.g0.g0_addr0
#define			scc0_count	sg_un.g0.g0_count
#define 		scc0_vu_1	sg_un.g0.g0_v1
#define 		scc0_vu_0	sg_un.g0.g0_v0
#define 		scc0_flag	sg_un.g0.g0_flag
#define 		scc0_link	sg_un.g0.g0_link

		/*
		 *	G R O U P   1   F O R M A T
		 */
		struct scsi_g1 {	/* group 1 (10 byte) command format */
							/* first byte */
			u_char g1_cmd;		/* operation code */
							/* second byte */
			u_char g1_unit	:3;	/* logical unit number */
			u_char g1_rsvrd	:4;	/* reserved */
			u_char g1_relad	:1;	/* relative address bit */
							/* third byte */
			u_char g1_addr3;	/* most sig. byte of address*/
							/* fourth byte */
			u_char g1_addr2;
							/* fifth byte */
			u_char g1_addr1;
							/* sixth byte */
			u_char g1_addr0;
							/* seventh byte */
			u_char g1_x0;		/* reserved */
							/* eighth byte */
			u_char g1_count1;	/* msb of transfer length */
							/* ninth byte */
			u_char g1_count0;	/* lsb of transfer length */
							/* tenth byte */
			u_char g1_v1	:1;	/* vendor unique (byte 5 bit 7*/
			u_char g1_v0	:1;	/* vendor unique (byte 5 bit 6*/
			u_char g1_x	:4;	/* reserved */
			u_char g1_flag	:1;	/* interrupt when done */
			u_char g1_link	:1;	/* another command follows */
		} g1;

#define			scc1_reladdr	sg_un.g1.g1_relad
#define			scc1_reserved	sg_un.g1.g1_rsvrd
#define			scc1_addr3	sg_un.g1.g1_addr3	/* msb */
#define			scc1_addr2	sg_un.g1.g1_addr2
#define			scc1_addr1	sg_un.g1.g1_addr1
#define			scc1_addr0	sg_un.g1.g1_addr0
#define			scc1_count1	sg_un.g1.g1_count1	/* msb */
#define			scc1_count0	sg_un.g1.g1_count0
#define 		scc1_vu_1	sg_un.g1.g1_v1
#define 		scc1_vu_0	sg_un.g1.g1_v0
#define 		scc1_flag	sg_un.g1.g1_flag
#define 		scc1_link	sg_un.g1.g1_link

		/*
		 *	G R O U P   5   F O R M A T
		 */
		struct scsi_g5 {	/* group 5 (12 byte) command format */
							/* first byte */
			u_char g5_cmd;		/* operation code */
							/* second byte */
			u_char g5_unit	:3;	/* logical unit number */
			u_char g5_rsvrd	:4;	/* reserved */
			u_char g5_relad	:1;	/* relative address bit */
							/* third byte */
			u_char g5_addr3;	/* most sig. byte of address*/
							/* fourth byte */
			u_char g5_addr2;
							/* fifth byte */
			u_char g5_addr1;
							/* sixth byte */
			u_char g5_addr0;
							/* seventh byte */
			u_char g5_x2;		/* reserved */
							/* eighth byte */
			u_char g5_x1;		/* reserved */
							/* ninth byte */
			u_char g5_x0;		/* reserved */
							/* tenth byte */
			u_char g5_count1;	/* msb of transfer length */
							/* eleventh byte */
			u_char g5_count0;	/* lsb of transfer length */
							/* twelfth byte */
			u_char g5_v1	:1;	/* vendor unique (byte 5 bit 7*/
			u_char g5_v0	:1;	/* vendor unique (byte 5 bit 6*/
			u_char g5_x	:4;	/* reserved */
			u_char g5_flag	:1;	/* interrupt when done */
			u_char g5_link	:1;	/* another command follows */
		} g5;
#define			scc5_reladdr	sg_un.g5.g5_relad
#define			scc5_addr3	sg_un.g5.g5_addr3	/* msb */
#define			scc5_addr2	sg_un.g5.g5_addr2
#define			scc5_addr1	sg_un.g5.g5_addr1
#define			scc5_addr0	sg_un.g5.g5_addr0
#define			scc5_count1	sg_un.g5.g5_count1	/* msb */
#define			scc5_count0	sg_un.g5.g5_count0
#define 		scc5_vu_1	sg_un.g5.g5_v1
#define 		scc5_vu_0	sg_un.g5.g5_v0
#define 		scc5_flag	sg_un.g5.g5_flag
#define 		scc5_link	sg_un.g5.g5_link
	}sg_un;
};

/*
 * defines for group codes (see above).
 */
#define SC_GROUP_0	0
#define SC_GROUP_0_SIZE	6
#define SC_GROUP_1	1
#define SC_GROUP_1_SIZE	10
#define SC_GROUP_5	5
#define SC_GROUP_5_SIZE	12

/*
 * defines for SCSI tape cdb.
 */
#define	t_code		scc0_high_addr
#define	high_count	scc0_mid_addr
#define	mid_count	scc0_low_addr
#define low_count	scc0_count

/*
 * Defines for SCSI disk format cdb (group 0).
 */
#define fmt_parm_bits	scc0_high_addr
#define fmt_interleave	scc0_count	/* encode interleave in count field */

/*
 * defines for value of fmt_parm_bits.
 */
#define FPB_BFI		0x04		/* list in bytes-from-index fmt */
#define FPB_CMPLT	0x08		/* complete defect list provided */
#define FPB_DATA	0x10		/* defect list data provided */

/*
 * Defines for SCSI read defect list (group 1).
 */
#define	defect_list_descrip	scc1_addr3	/* list description bits */

/*
 * Defines for value of defect_list_descrip.
 */
#define	DLD_MAN_DEF_LIST	0x10		/* manufacturer's defect list */
#define	DLD_GROWN_DEF_LIST	0x08		/* grown defect list */
#define	DLD_BLOCK_FORMAT	0x00		/* block format */
#define	DLD_BFI_FORMAT		0x04		/* bytes-from-index format */
#define	DLD_PS_FORMAT		0x05		/* physical sector format */



struct	scsi_scb {		/* scsi status completion block */
	/* byte 0 */
	u_char	ext_st1	: 1;	/* extended status (next byte valid) */
	u_char	vu_06	: 1;	/* vendor unique */
	u_char	vu_05	: 1;	/* vendor unique */
	u_char	is	: 1;	/* intermediate status sent */
	u_char	busy	: 1;	/* device busy or reserved */
	u_char	cm	: 1;	/* condition met */
	u_char	chk	: 1;	/* check condition: sense data available */
	u_char	vu_00	: 1;	/* vendor unique */
	/* byte 1 */
	u_char	ext_st2	: 1;	/* extended status (next byte valid) */
	u_char	reserved: 6;	/* reserved */
	u_char	ha_er	: 1;	/* host adapter detected error */
	/* byte 2 */
	u_char	byte2;		/* third byte */
};

		/*
		 * Standard (Non Extended) SCSI Sense. Used mainly by the
  		 * Adaptec ACB 4000 which is the only controller that
		 * does not support the Extended sense format.
	         */
struct	scsi_sense {		/* scsi sense for error classes 0-6 */
	u_char	adr_val	: 1;	/* sense data is valid */
	u_char	class	: 3;	/* error class (0-6) */
	u_char	code	: 4;	/* error code */
	u_char	high_addr;	/* high byte of block addr */
	u_char	mid_addr;	/* middle byte of block addr */
	u_char	low_addr;	/* low byte of block addr */
	u_char	extra[12];	/* pad this struct so it can hold max num */
				/* of sense bytes we may receive */
};

/*
 * Value(s) of scsi_sense class field.
 */
#define SC_CLASS_EXTENDED_SENSE	0x7	/* indicates extended sense */

struct	scsi_ext_sense {	/* scsi extended sense for error class 7 */
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
	/* bytes 3 through 7 */
	u_char	info_1;		/* information byte 1 */
	u_char	info_2;		/* information byte 2 */
	u_char	info_3;		/* information byte 3 */
	u_char	info_4;		/* information byte 4 */
	u_char	add_len;	/* number of additional bytes */
	/* SCSI Commom Command Set Additional Implementation as Follows */
	u_char	optional_8;	/* CCS search and copy only */
	u_char	optional_9;	/* CCS search and copy only */
	u_char	optional_10;	/* CCS search and copy only */
	u_char	optional_11;	/* CCS search and copy only */
	u_char 		: 1;	/* reserved */
	u_char 	error_code : 7;	/* error class and code combined */
};

/*
 * Defines for Emulex MD21 SCSI/ESDI Controller. Extended sense for Format
 * command only.
 */
#define cyl_msb		info_1
#define cyl_lsb		info_2
#define head_num	info_3
#define sect_num	info_4

/* 
 * Sense key values for extended sense.
 */
#define	SC_NO_SENSE		0x0
#define	SC_RECOVERABLE_ERROR	0x1
#define	SC_NOT_READY		0x2
#define	SC_MEDIUM_ERROR		0x3
#define	SC_HARDWARE_ERROR	0x4
#define	SC_ILLEGAL_REQUEST	0x5
#define	SC_UNIT_ATTENTION	0x6
#define	SC_DATA_PROTECT		0x7
#define	SC_BLANK_CHECK		0x8 /* reserved on MD21 */
#define	SC_VENDOR_UNIQUE	0x9
#define	SC_COPY_ABORTED		0xa
#define	SC_ABORT_COMMAND	0xb
#define	SC_EQUAL		0xc
#define	SC_VOLUME_OVERFLOW	0xd /* reserved on MD21 */
#define SC_MISCOMPARE		0xe
#define SC_RESERVED		0xf /* reserved on MD21 */

struct	scsi_inquiry_data {	/* data returned as a result of CCS inquiry */
	u_char	dtype;		/* device type */
	/* byte 1 */
	u_char	rmb 	   : 1;	/* removable media */
	u_char  dtype_qual : 7;	/* device type qualifier */
	/* byte 2 */
	u_char iso 	   : 2;	/* ISO version */
	u_char ecma 	   : 3;	/* ECMA version */
	u_char ansi 	   : 3;	/* ANSI version */
	/* byte 3 */
	u_char reserv1 	   : 4;	/* reserved */
	u_char rdf 	   : 4;	/* response data format */
	u_char add_len;		/* additional length */
	u_char reserv2;		/* reserved */
	u_char reserv3;		/* reserved */
	char vid[8];		/* vendor ID */
	char pid[16];		/* product ID */
	char revision[4];	/* revision level */
};

/*
 * SCSI Operation codes. 
 */

	/*
	 * These two commands use identical command blocks for all
	 * controllers.
         */
#define	SC_TEST_UNIT_READY	0x00
#define	SC_REZERO_UNIT		0x01

	/*
	 * This command uses identical command blocks for all controllers,
	 * except for the length of requested sense bytes (byte 4).
	 * Emulex MT02 sends 11 bytes.
	 * Emulex MD21 sends 9 bytes.
	 */
#define	SC_REQUEST_SENSE	0x03

	/*
	 * This command is undoubtedly different between the two
	 * controllers.
	 */
#define SC_FORMAT		0x04

#define	SC_REASSIGN_BLOCK	0x07		/* CCS only */

	/* These two commands use identical command blocks for all
 	 * controllers except the Adaptec ACB 4000 which sets bit 1 of byte 1.
	 */
#define	SC_READ			0x08
#define	SC_WRITE		0x0a

#define	SC_SEEK			0x0b		/* disk only */

#define SC_QIC02		0x0d		/* tape only */

#define	SC_TRANSLATE		0x0f		/* ACB4000 only */

#define SC_WRITE_FILE_MARK	0x10		/* tape only */
#define SC_SPACE		0x11		/* tape only */

#define SC_INQUIRY		0x12		/* CCS only */
#define SC_MODE_SELECT		0x15

#define SC_ERASE_CARTRIDGE	0x19		/* tape only */
#define SC_MODE_SENSE		0x1a
#define SC_LOAD			0x1b		/* tape only */

#define SC_READ_DEFECT_LIST	0x37		/* CCS only, group 1 */

#define SC_READ_XSTATUS_CIPHER	0xe0	/* read xtend stat, Cipher tape only */

	/*
	 * Psuedo command to terminate search lists.
	 */
#define SC_UNKNOWN		0xff


/*
 * Definition of direction of data flow for commands.
 */
#define	SCSI_RECV_DATA_CMD(cmd)	(((cmd) == SC_READ) || \
				 ((cmd) == SC_REQUEST_SENSE) || \
				 ((cmd) == SC_INQUIRY) || \
				 ((cmd) == SC_READ_DEFECT_LIST) || \
				 ((cmd) == SC_MODE_SENSE) || \
				 ((cmd) == SC_READ_XSTATUS_CIPHER))

#define	SCSI_SEND_DATA_CMD(cmd)	(((cmd) == SC_WRITE) || \
				 ((cmd) == SC_MODE_SELECT) || \
				 ((cmd) == SC_REASSIGN_BLOCK) || \
				 ((cmd) == SC_FORMAT))

/*
 * Messages that SCSI can send.
 */
#define	SC_COMMAND_COMPLETE	0x00
#define SC_SAVE_DATA_PTR	0x02
#define SC_RESTORE_PTRS		0x03
#define SC_DISCONNECT		0x04
#define SC_IDENTIFY		0x80
#define SC_DR_IDENTIFY		0xc0

#define	MORE_STATUS 0x80	/* More status flag */
#define	STATUS_LEN  3		/* Max status len for SCSI */

/*
 * defines for setting fields within the various command groups
 */
#define FORMG0ADDR(cdb, addr) 	(cdb)->scc0_high_addr = (addr) >> 16;\
				(cdb)->scc0_mid_addr =  ((addr) >> 8) & 0xFF;\
				(cdb)->scc0_low_addr = (addr) & 0xFF
#define FORMG1ADDR(cdb, addr)	(cdb)->scc1_addr3 = (addr) >> 24;\
				(cdb)->scc1_addr2 =  ((addr) >> 16) & 0xFF;\
				(cdb)->scc1_addr1 =  ((addr) >> 8) & 0xFF;\
				(cdb)->scc1_addr0 = (addr) & 0xFF
#define FORMG5ADDR(cdb, addr)	(cdb)->scc5_addr3 = (addr) >> 24;\
				(cdb)->scc5_addr2 =  ((addr) >> 16) & 0xFF;\
				(cdb)->scc5_addr1 =  ((addr) >> 8) & 0xFF;\
				(cdb)->scc5_addr0 = (addr) & 0xFF
#define FORMG0COUNT(cdb, cnt)	(cdb)->scc0_count = (cnt)
#define FORMG1COUNT(cdb, cnt)	(cdb)->scc1_count1 = ((cnt) >> 8);\
				(cdb)->scc1_count0 = (cnt) & 0xFF
#define FORMG5COUNT(cdb, cnt)	(cdb)->scc5_count1 = ((cnt) >> 8);\
				(cdb)->scc5_count0 = (cnt) & 0xFF

#define NLPART	NDKMAP		/* number of logical partitions (8) */

/*
 * SCSI unit block.
 */
struct scsi_unit {
	char	un_target;		/* scsi bus address of controller */
	char	un_lun;			/* logical unit number of device */
	char	un_present;		/* unit is present */
	u_char	un_scmd;		/* special command */
	u_short un_unit;		/* real unit number of device */
	struct	scsi_unit_subr *un_ss;	/* scsi device subroutines */
	struct	scsi_ctlr *un_c;	/* scsi ctlr */
	struct	mb_device *un_md;	/* mb device */
	struct	mb_ctlr *un_mc;		/* mb controller */
	struct	buf un_utab;		/* queue of requests */
	struct	buf un_sbuf;		/* fake buffer for special commands */
	struct	buf un_rbuf;		/* buffer for raw i/o */
	/* current transfer: */
	u_short	un_flags;		/* misc flags relating to cur xfer */
	int	un_baddr;		/* virtual buffer address */
	daddr_t	un_blkno;		/* current block */
	short	un_sec_left;		/* sector count for single sectors */
	short	un_cmd;			/* command (for cdb) */
	short	un_count;		/* num sectors to xfer (for cdb) */
	int	un_dma_addr;		/* dma address */
	u_short	un_dma_count;		/* byte count expected */
	short	un_retries;		/* retry count */
	short	un_restores;		/* restore count */
	char	un_wantint;		/* expecting interrupt */
	u_char	un_cmd_len;		/* size of command for group 2,3,4,6,7*/
	/* the following save current dma information in case of disconnect */
	int	un_dma_curaddr;		/* current addr to start dma to/from */
	u_short	un_dma_curcnt;		/* current dma count */
	u_short	un_dma_curdir;		/* direction of dma transfer */
	u_short un_dma_curbcr;		/* bcr, saved at head of intr routine */
	/* the following is a copy of current unit command info */
	struct un_saved_cmd_info {
		struct scsi_cdb saved_cdb; 	/* saved cdb */
		struct scsi_scb saved_scb; 	/* saved scb */
		int saved_resid;		/* saved amt untransferred */
		int saved_dma_addr;		
		u_short saved_dma_count;
	} un_saved_cmd;
	caddr_t	un_scratch_addr;	/* address of scratch buffer for MT02 */
};

/* 
 * bits in the scsi unit flags field
 */
#define SC_UNF_DVMA		0x0001	/* set if cur xfer requires dvma */
#define SC_UNF_PREEMPT		0x0002	/* cur xfer was preempted by recon */
#define SC_UNF_DMA_ACTIVE	0x0004	/* DMA active on this unit */
#define SC_UNF_RECV_DATA	0x0008	/* direction of data xfer is recieve */
#define SC_UNF_GET_SENSE	0x0010	/* run get sense cmd for failed cmd */
#define SC_UNF_DMA_INITIALIZED	0x0020	/* initialized DMA hardware */
#define SC_UNF_TAPE_APPEND_TEST	0x0040	/* run special cmd for tape append */
/* ++mjacob 4/27/87 per bug #1004516 {*/
#define SC_UNF_NOMSGOUT         0x0080  /* don't attempt msg out (sysgen) */
/* } --mjacob                         */
#define SC_UNF_WORD_XFER	0x0100	/* Unaligned word transfer */

/*
 * Bits in the special command flags field.
 */
#define SC_SBF_SILENT		0x0001	/* don't print error messages */
#define SC_SBF_DIAGNOSE		0x0002	/* collect stats for diagnostic */
#define SC_SBF_DIR_IN		0x0004	/* need to copyin info */
#define SC_SBF_IOCTL		0x8000	/* cmd being run on behalf of ioctl */

struct scsi_ctlr {
	struct	scsi_ha_reg *c_har;	/* sc bus registers in i/o space */
	struct 	scsi_si_reg *c_sir;	/* si scsi ctlr logic regs */
	struct 	scsi_sw_reg *c_swr;	/* sw scsi ctlr logic regs */
	struct	scsi_cdb c_cdb;		/* command description block */
	struct	scsi_scb c_scb;		/* status completion block */
	struct	scsi_sense *c_sense;	/* sense info on errors */
	int	c_flags;		/* misc state flags */
	struct 	scsi_unit *c_un;	/* scsi unit using the bus */
	struct	scsi_ctlr_subr *c_ss;	/* scsi device subroutines */
	struct	udc_table c_udct;	/* scsi dma info for Sun3/50 */
	struct	buf *c_disqh;		/* ptr to head of disconnect q */
	struct	buf *c_disqt;		/* ptr to tail of disconnect q */
	struct	buf *c_flush;		/* ptr to last element to flush */
	u_int	c_recon_target;		/* target doing a reconnect */
	char	*c_name;		/* host adaptor name */
};

/* misc controller flags */
#define SCSI_PRESENT	0x0001		/* scsi bus is alive */
#define SCSI_ONBOARD	0x0002		/* scsi logic is onboard SCSI-3 */
#define SCSI_EN_RECON	0x0004		/* reconnect attempts are enabled */
#define SCSI_EN_DISCON	0x0008		/* disconnect attempts are enabled */
#define SCSI_FLUSH_DISQ	0x0010		/* flush disconnected tasks */
#define SCSI_FLUSHING	0x0020		/* flushing in progress */
#define SCSI_VME	0x0040		/* is a VME SCSI-3 */
#define SCSI_COBRA	0x0080		/* is a COBRA SCSI */

#define IS_ONBOARD(c)	(c->c_flags & SCSI_ONBOARD)
#define IS_VME(c)	(c->c_flags & SCSI_VME)
#define IS_SCSI3(c)	(IS_ONBOARD(c) || IS_VME(c))
#ifdef sun4
#define IS_COBRA(c)     (c->c_flags & SCSI_COBRA)
#define IS_SCSI4(c)	(IS_COBRA(c))
#endif
/* 
 * Unit specific subroutines called from controllers.
 */
struct	scsi_unit_subr {
	int	(*ss_attach)();
	int	(*ss_start)();
	int	(*ss_mkcdb)();
	int	(*ss_intr)();
	int	(*ss_unit_ptr)();
	char	*ss_devname;
};

/* 
 * Controller specific subroutines called from units.
 */
struct	scsi_ctlr_subr {
	int	(*scs_ustart)();
	int	(*scs_start)();
	int	(*scs_done)();
	int	(*scs_cmd)();
	int	(*scs_getstat)();
	int	(*scs_cmd_wait)();
	int	(*scs_off)();
	int	(*scs_reset)();
	int	(*scs_dmacount)();
	int	(*scs_go)();
};

/*
 * Defines for getting configuration parameters out of mb_device.
 */
#define	TYPE(flags)	(flags)
#define TARGET(slave)	((slave >> 3) & 07)
#define LUN(slave)	(slave & 07)

#define SCSI_DISK	0
#define SCSI_TAPE	1
#define SCSI_FLOPPY	2

#define NUNIT		8	/* max nubmer of units per controller */

/*
 * SCSI Error codes passed to device routines.
 * The codes refer to SCSI general errors, not to device
 * specific errors.  Device specific errors are discovered
 * by checking the sense data.
 * The distinction between retryable and fatal is somewhat ad hoc.
 */
#define	SE_NO_ERROR	0
#define	SE_RETRYABLE	1
#define	SE_FATAL	2

/*
 * Special command execution flags.
 */
#define SC_NOMSG	0x01		/* don't print error messages */
#define SC_DIAG		0x02		/* collect diagnostic info ??? */
#define SC_IOCTL	0x04		/* running cmd for ioctl */

struct scsi_disk {
	struct	dk_map un_map[NLPART];	/* logical partitions */
	struct	dk_geom un_g;		/* disk geometry */
	u_char	dk_ctype;		/* controller type */
};

/* different controller types */
#define CTYPE_UNKNOWN	0
#define CTYPE_MD21	1
#define CTYPE_ACB4000	2
#define CTYPE_CCS	3

struct scsi_tape {
	int	un_mspl;		/* ptr to mode select param list */
	int	un_bufcnt;		/* number of buffers in use */
	int	un_next_block;		/* next record on tape */
	int	un_last_block;		/* last record of file, if known */
	short	un_status;		/* status from last sense */
	short	un_retry_ct;		/* retry count */
	short	un_underruns;		/* number of underruns */
	u_char	un_openf;		/* tape is open */
	u_char	un_eof;			/* eof seen but not sent to user */
	u_char	un_read_only;		/* tape is read only */
	u_char	un_lastiow;		/* last i/o was write */
	u_char	un_lastior;		/* last i/o was read */
	u_char	un_reten_rewind;	/* retension on next rewind */
	u_char	un_qic;			/* qic format */
	u_char	un_ctype;		/* controller type */
	u_char	un_reset_occurred;	/* reset occured since last command */
	u_char	un_readmode;		/* sysgen left in read mode */
	u_char	un_err_pending;		/* illegal cmd error pending */
	u_char	un_last_cmd;		/* last scsi command issued */
#ifdef sun2
	u_char	un_cipher_test;		/* test for cipher drive in progres */
#endif
};

struct scsi_floppy {
	u_char	sf_flags;
	u_char	sf_mdb;			/* media descriptor byte */
	u_char	sf_spt;			/* sectors per track */
	u_char	sf_nhead;		/* number of heads */
	int	sf_nblk;		/* number of blocks on the disk */
};
