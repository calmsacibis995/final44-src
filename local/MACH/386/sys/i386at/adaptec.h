/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	adaptec.h,v $
 * Revision 2.1.1.1  91/03/28  08:45:15  rvb
 * 	Acquired from osf.
 * 	[91/03/25            rvb]
 * 
 */

/*
 * Adaptec AHA-1542A SCSI board description
 * Copyright (c) 1990 OSF Research Institute 
 */

/*
 * Copyright 1990 by Open Software Foundation,
 * Grenoble, FRANCE
 *
 * 		All Rights Reserved
 * 
 *   Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OSF or Open Software
 * Foundation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 *   OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <aha.h>
#define NTARGET NAHA	/* must be <= 7 */
#define PARTITION(z)	(minor(z) & 0x0f)
#define UNIT(z)		(  (minor(z) >> 4) )
typedef long paddr_t;
#define paddr(X)	(paddr_t)(X->b_un.b_addr)
#define WHOLE_DISK(unit) ( (unit << 4) + PART_DISK )
#define BAD_BLK		0x80			/* needed for V_VERIFY */

/*
 * I/O Port Interface
 */

#define	AHA_BASE		0x330
#define	AHA_CTRL_STAT_PORT	(AHA_BASE + 0x0)	/* control & status */
#define	AHA_CMD_DATA_PORT	(AHA_BASE + 0x1)	/* cmds and datas */
#define	AHA_INTR_PORT		(AHA_BASE + 0x2)	/* Intr. stat */

/*
 * AHA_CTRL_STAT bits (write)
 */

#define AHA_HRST		0x80	/* Hardware reset */
#define AHA_SRST		0x40	/* Software reset */
#define AHA_IRST		0x20	/* Interrupt reset */
#define AHA_SCRST		0x10	/* SCSI bus reset */

/*
 * AHA_CTRL_STAT bits (read)
 */

#define AHA_STST		0x80	/* Self test in Progress */
#define AHA_DIAGF		0x40	/* Diagnostic Failure */
#define AHA_INIT		0x20	/* Mbx Init required */
#define AHA_IDLE		0x10	/* Host Adapter Idle */
#define AHA_CDF			0x08	/* cmd/data out port full */
#define AHA_DF			0x04	/* Data in port full */
#define AHA_INVDCMD		0x01	/* Invalid command */

/*
 * AHA_CMD_DATA bits (write)
 */

#define	AHA_NOP			0x00	/* No operation */
#define AHA_MBX_INIT		0x01	/* Mbx initialization */
#define AHA_START_SCSI		0x02	/* start scsi command */
#define AHA_START_BIOS		0x03	/* start bios command */
#define AHA_INQUIRE		0x04	/* Adapter Inquiry */
#define AHA_MBO_INTR_EN		0x05	/* Enable MBO available interrupt */
#define AHA_SEL_TIMEOUT_SET	0x06	/* set selection time-out */
#define AHA_BUS_ON_TIME_SET	0x07	/* set bus-on time */
#define AHA_BUS_OFF_TIME_SET	0x08	/* set bus-off time */
#define AHA_SPEED_SET		0x09	/* set transfer speed */
#define AHA_DEV_GET		0x0a	/* return installed devices */
#define AHA_CONF_GET		0x0b	/* return configuration data */
#define AHA_TARGET_EN		0x0c	/* enable target mode */
#define AHA_SETUP_GET		0x0d	/* return setup data */
#define AHA_WRITE_CH2		0x1a	/* write channel 2 buffer *
#define AHA_READ_CH2		0x1b	/* read channel 2 buffer *
#define AHA_WRITE_FIFO		0x1c	/* write fifo buffer */
#define AHA_READ_FIFO		0x1d	/* read fifo buffer */
#define AHA_ECHO		0x1e	/* Echo command data */

struct aha_cmd_buf {
	 u_char byte[16];	
};

/*
 * AHA_INTR_PORT bits (read)
 */

#define AHA_ANY_INTR		0x80	/* Any interrupt */
#define AHA_SCRD		0x08	/* SCSI reset detected */
#define AHA_HACC		0x04	/* Command complete */
#define AHA_MBOA		0x02	/* MBX out empty */
#define AHA_MBIF		0x01	/* MBX in full */

/*
 * Mail box defs 
 */

#define AHA_MBX_SIZE		(2 * NTARGET)	/* mail box size */

struct aha_mbx {
	struct aha_mbx_out {
		unsigned char cmd;
		unsigned char ccb_addr[3];
	} mbo [AHA_MBX_SIZE];
	struct aha_mbx_in{
		unsigned char stat;
		unsigned char ccb_addr[3];
	} mbi[AHA_MBX_SIZE];
};

/*
 * mbo.cmd values
 */

#define AHA_MBO_FREE	0x0	/* MBO entry is free */
#define AHA_MBO_START	0x1	/* MBO activate entry */
#define AHA_MBO_ABORT	0x2	/* MBO abort entry */

#define AHA_MBI_FREE	0x0	/* MBI entry is free */
#define AHA_MBI_OK	0x1	/* completed without error */
#define AHA_MBI_ABORT	0x2	/* aborted ccb */
#define AHA_MBI_UNKNOWN	0x3	/* Tried to abort invalid CCB */
#define AHA_MBI_ERROR	0x4	/* Completed with error */

extern struct aha_mbx aha_mbx;

#define	AHA_NSEG	9	/* Number of scatter gather segments <= 16 */
				/* allow 32 K i/o */

struct aha_ccb {
	unsigned char	opcode;
	unsigned char	lun:3;
	unsigned char	data_in:1;		/* must be 0 */
	unsigned char	data_out:1;		/* must be 0 */
	unsigned char	target:3;
	unsigned char	scsi_cmd_length;
	unsigned char	req_sense_length;
	unsigned char	data_length[3];
	unsigned char	data_addr[3];
	unsigned char	link_addr[3];
	unsigned char	link_id;
	unsigned char	host_stat;
	unsigned char	target_stat;
	unsigned char	reserved[2];
	struct	scsi_cmd	scsi_cmd;
	struct	scsi_data	scsi_sense;
#ifndef	CBUS
	struct	aha_scat_gath {
		unsigned char seg_len[3];
		unsigned char seg_addr[3];
	} scat_gath[AHA_NSEG];
#else	CBUS
	int	window;		/* 1st cbus window # */
#endif	CBUS
	struct	aha_ccb	*next;
	struct	buf	*bp;
	struct	aha_mbx_out	*mbx;		/* pointer to mail box */

};

/*
 * opcode fields
 */

#define AHA_INITIATOR_CCB	0x00	/* SCSI Initiator CCB */
#define AHA_TARGET_CCB		0x01	/* SCSI Target CCB */
#define AHA_INIT_SCAT_GATH_CCB	0x02	/* SCSI Initiator with scattter gather*/
#define AFA_RESET_CCB		0x81	/* SCSI Bus reset */


/*
 * aha_ccb.host_stat values
 */

#define AHA_OK		0x00	/* cmd ok */
#define AHA_LINK_OK	0x0a	/* Link cmd ok */
#define AHA_LINK_IT	0x0b	/* Link cmd ok + int */
#define AHA_SEL_TIMEOUT	0x11	/* Selection time out */
#define AHA_OVER_UNDER	0x12	/* Data over/under run */
#define AHA_BUS_FREE	0x13	/* Bus dropped at unexpected time */
#define AHA_INV_BUS	0x14	/* Invalid bus phase/sequence */
#define AHA_BAD_MBO	0x15	/* Incorrect MBO cmd */
#define AHA_BAD_CCB	0x16	/* Incorrect ccb opcode */
#define AHA_BAD_LINK	0x17	/* Not same values of LUN for links */
#define AHA_INV_TARGET	0x18	/* Invalid target direction */
#define AHA_CCB_DUP	0x19	/* Duplicate CCB received */
#define AHA_INV_CCB	0x1a	/* Invalid CCB or segment list */


#define A_CMD	_IOWR(a,0,struct aha_cmd_buf)	/* Execute cmd command */
#define A_SCSI	_IOWR(a,1,struct scsi_cmd)	/* Execute scsi command */

/* the boot record partition table is documented in IBM AT Tech. Ref p. 9-6 */
struct 	boot_record	{
	u_char	boot_ind;	/* if it == 0x80, this partition is active */
	u_char	head;		/* driver does not look at this field */
	u_char	sector;		/* driver does not look at this field */
	u_char	cylinder;	/* driver does not look at this field */

	u_char	sys_ind;	/* driver does not look at this field */
	u_char	end_head;	/* driver does not look at this field */
	u_char	end_sector;	/* driver does not look at this field */
	u_char 	end_cylinder;	/* driver does not look at this field */

	u_int	rel_sect;	/* where unix starts if boot_ind == 0x80 */
	u_int	num_sects;	/* driver does not look at this field */
			};
