h29090
s 00030/00010/01968
d D 8.5 94/11/30 10:52:06 mckusick 18 17
c fix problem with disconnects (from ralph)
e
s 00002/00000/01976
d D 8.4 94/10/09 21:06:49 mckusick 17 16
c Fix for the case when DEBUG isn't defined (from Ralph)
e
s 00046/00005/01930
d D 8.3 94/07/03 14:44:12 mckusick 16 15
c Ralph says: important bug fix
e
s 00045/00042/01890
d D 8.2 94/01/04 17:33:58 mckusick 15 14
c This fixes a bug where if a device disconnects, connects, and then
c disconnects, connects again without a data phase inbetween, the
c transfer count is wrong and the device driver panics. (from Ralph)
e
s 00002/00002/01930
d D 8.1 93/06/10 22:37:57 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00007/01920
d D 7.13 93/05/24 18:15:09 ralph 13 12
c fixes from Rick Macklem
e
s 00051/00034/01876
d D 7.12 93/03/23 18:41:00 ralph 12 11
c fix a bug when reading a tape with an odd number of bytes in the
c record size or any device that disconnects on an odd byte offset.
e
s 00088/00029/01822
d D 7.11 93/03/13 15:44:00 ralph 11 10
c fix bug with reconnect hanging if right after aborting reselect enable
e
s 00005/00012/01846
d D 7.10 93/03/08 18:52:39 ralph 10 9
c fix debug info dumps.
e
s 00041/00056/01817
d D 7.9 92/12/20 11:23:56 ralph 9 8
c changes from Rick Macklem
e
s 00332/00078/01541
d D 7.8 92/11/15 15:49:10 ralph 8 7
c changes for maxine from Rick Macklem.
e
s 00000/00003/01619
d D 7.7 92/10/24 14:04:44 ralph 7 6
c remove unneeded include files
e
s 00003/00003/01619
d D 7.6 92/10/11 11:24:33 bostic 6 5
c use pmax as top directory, not mips
e
s 00009/00009/01613
d D 7.5 92/10/11 11:13:25 bostic 5 4
c make kernel includes standard
e
s 00017/00017/01605
d D 7.4 92/06/20 12:13:59 ralph 4 3
c changes to make gcc happy.
e
s 00083/00067/01539
d D 7.3 92/03/29 20:36:12 ralph 3 2
c fixes for tapes.
e
s 00241/00094/01365
d D 7.2 92/03/14 14:00:50 ralph 2 1
c fixed disk writes
e
s 01459/00000/00000
d D 7.1 92/03/09 14:24:21 bostic 1 0
c date and time created 92/03/09 14:24:21 by bostic
e
u
U
t
T
I 1
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Ralph Campbell.
E 8
I 8
 * Ralph Campbell and Rick Macklem.
E 8
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
 * $Log:	scsi_53C94_hdw.c,v $
 * Revision 2.5  91/02/05  17:45:07  mrt
 * 	Added author notices
 * 	[91/02/04  11:18:43  mrt]
 * 
 * 	Changed to use new Mach copyright
 * 	[91/02/02  12:17:20  mrt]
 * 
 * Revision 2.4  91/01/08  15:48:24  rpd
 * 	Added continuation argument to thread_block.
 * 	[90/12/27            rpd]
 * 
 * Revision 2.3  90/12/05  23:34:48  af
 * 	Recovered from pmax merge.. and from the destruction of a disk.
 * 	[90/12/03  23:40:40  af]
 * 
 * Revision 2.1.1.1  90/11/01  03:39:09  af
 * 	Created, from the DEC specs:
 * 	"PMAZ-AA TURBOchannel SCSI Module Functional Specification"
 * 	Workstation Systems Engineering, Palo Alto, CA. Aug 27, 1990.
 * 	And from the NCR data sheets
 * 	"NCR 53C94, 53C95, 53C96 Advances SCSI Controller"
 * 	[90/09/03            af]
 */

/*
 *	File: scsi_53C94_hdw.h
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	9/90
 *
 *	Bottom layer of the SCSI driver: chip-dependent functions
 *
 *	This file contains the code that is specific to the NCR 53C94
 *	SCSI chip (Host Bus Adapter in SCSI parlance): probing, start
 *	operation, and interrupt routine.
 */

/*
 * This layer works based on small simple 'scripts' that are installed
 * at the start of the command and drive the chip to completion.
 * The idea comes from the specs of the NCR 53C700 'script' processor.
 *
 * There are various reasons for this, mainly
 * - Performance: identify the common (successful) path, and follow it;
 *   at interrupt time no code is needed to find the current status
 * - Code size: it should be easy to compact common operations
 * - Adaptability: the code skeleton should adapt to different chips without
 *   terrible complications.
 * - Error handling: and it is easy to modify the actions performed
 *   by the scripts to cope with strange but well identified sequences
 *
 */

D 8
#include "asc.h"
E 8
I 8
#include <asc.h>
E 8
#if NASC > 0

D 5
#include "param.h"
#include "systm.h"
#include "dkstat.h"
#include "buf.h"
#include "conf.h"
#include "errno.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
I 8
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/conf.h>
E 8
D 7
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/conf.h>
E 7
#include <sys/errno.h>
E 5

I 8
#include <machine/machConst.h>

E 8
D 5
#include "device.h"
#include "scsi.h"
#include "ascreg.h"
E 5
I 5
D 6
#include <mips/dev/device.h>
#include <mips/dev/scsi.h>
#include <mips/dev/ascreg.h>
E 6
I 6
#include <pmax/dev/device.h>
#include <pmax/dev/scsi.h>
#include <pmax/dev/ascreg.h>
E 6
E 5

I 8
#include <pmax/pmax/asic.h>
#include <pmax/pmax/kmin.h>
#include <pmax/pmax/pmaxtype.h>

E 8
D 9
#define ASC_OFFSET_53C94	0x0		/* from module base */
#define ASC_OFFSET_DMAR		0x40000		/* DMA Address Register */
#define ASC_OFFSET_RAM		0x80000		/* SRAM Buffer */
#define ASC_OFFSET_ROM		0xc0000		/* Diagnostic ROM */

#define	ASC_RAM_SIZE		0x20000		/* 128k (32k*32) */

E 9
I 8
#define	readback(a)	{ register int foo; foo = (a); }
E 8
D 9
/*
 * DMA Address Register
 */
#define ASC_DMAR_MASK		0x1ffff		/* 17 bits, 128k */
#define ASC_DMAR_WRITE		0x80000000	/* DMA direction bit */
D 3
#define	ASC_DMA_ADDR(x)		((unsigned)(x)) & ASC_DMAR_MASK
E 3
I 3
#define	ASC_DMA_ADDR(x)		((unsigned)(x) & ASC_DMAR_MASK)
E 3

/*
 * Synch xfer parameters, and timing conversions
 */
D 8
#define SCSI_MIN_PERIOD	50	/* in 4 nsecs units */
#define ASC_MIN_PERIOD	5	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MAX_PERIOD	35	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MAX_OFFSET	15	/* pure number */
E 8
I 8
#define SCSI_MIN_PERIOD		50	/* in 4 nsecs units */
#define ASC_MIN_PERIOD25	5	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MIN_PERIOD12	3	/* in CLKS/BYTE, 1 CLK = 80nsecs */
#define ASC_MAX_PERIOD25	35	/* in CLKS/BYTE, 1 CLK = 40nsecs */
#define ASC_MAX_PERIOD12	18	/* in CLKS/BYTE, 1 CLK = 80nsecs */
#define ASC_MAX_OFFSET		15	/* pure number */
E 8

E 9
I 8
extern int pmax_boardtype;

/*
 * In 4ns ticks.
 */
E 8
int	asc_to_scsi_period[] = {
D 8
	320,
	330,
	340,
	350,
	50,
	50,
	60,
	70,
	80,
	90,
	100,
	110,
	120,
	130,
	140,
	150,
	160,
	170,
	180,
	190,
	200,
	210,
	220,
	230,
	240,
	250,
	260,
	270,
	280,
	290,
	300,
	310,
E 8
I 8
	32,
	33,
	34,
	35,
	5,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
E 8
};

/*
 * Internal forward declarations.
 */
static void asc_reset();
static void asc_startcmd();

#ifdef DEBUG
int	asc_debug = 1;
int	asc_debug_cmd;
int	asc_debug_bn;
int	asc_debug_sz;
D 11
#define NLOG 16
E 11
I 11
#define NLOG 32
E 11
struct asc_log {
	u_int	status;
	u_char	state;
	u_char	msg;
	int	target;
I 11
	int	resid;
E 11
} asc_log[NLOG], *asc_logp = asc_log;
#define PACK(unit, status, ss, ir) \
	((unit << 24) | (status << 16) | (ss << 8) | ir)
#endif

/*
 * Scripts are entries in a state machine table.
 * A script has four parts: a pre-condition, an action, a command to the chip,
 * and an index into asc_scripts for the next state. The first triggers error
 * handling if not satisfied and in our case it is formed by the
 * values of the interrupt register and status register, this
 * basically captures the phase of the bus and the TC and BS
 * bits.  The action part is just a function pointer, and the
 * command is what the 53C94 should be told to do at the end
 * of the action processing.  This command is only issued and the
 * script proceeds if the action routine returns TRUE.
 * See asc_intr() for how and where this is all done.
 */
typedef struct script {
	int		condition;	/* expected state at interrupt time */
	int		(*action)();	/* extra operations */
	int		command;	/* command to the chip */
	struct script	*next;		/* index into asc_scripts for next state */
} script_t;

/* Matching on the condition value */
D 11
#define	SCRIPT_MATCH(ir, csr)		((ir) | (ASC_PHASE(csr) << 8))
E 11
I 11
#define	SCRIPT_MATCH(ir, csr)		((ir) | (((csr) & 0x67) << 8))
E 11

/* forward decls of script actions */
D 4
int	script_nop();			/* when nothing needed */
int	asc_end();			/* all come to an end */
int	asc_get_status();		/* get status from target */
int	asc_dma_in();			/* start reading data from target */
int	asc_last_dma_in();		/* cleanup after all data is read */
I 2
int	asc_resume_in();		/* resume data in after a message */
E 2
int	asc_resume_dma_in();		/* resume DMA after a disconnect */
int	asc_dma_out();			/* send data to target via dma */
int	asc_last_dma_out();		/* cleanup after all data is written */
I 2
int	asc_resume_out();		/* resume data out after a message */
E 2
int	asc_resume_dma_out();		/* resume DMA after a disconnect */
int	asc_sendsync();			/* negotiate sync xfer */
int	asc_replysync();		/* negotiate sync xfer */
D 2
int	asc_recvmsg();			/* process a message byte */
E 2
I 2
int	asc_msg_in();			/* process a message byte */
int	asc_disconnect();		/* process an expected disconnect */
E 4
I 4
D 8
static int	script_nop();		/* when nothing needed */
static int	asc_end();		/* all come to an end */
static int	asc_get_status();	/* get status from target */
static int	asc_dma_in();		/* start reading data from target */
static int	asc_last_dma_in();	/* cleanup after all data is read */
static int	asc_resume_in();	/* resume data in after a message */
static int	asc_resume_dma_in();	/* resume DMA after a disconnect */
static int	asc_dma_out();		/* send data to target via dma */
static int	asc_last_dma_out();	/* cleanup after all data is written */
static int	asc_resume_out();	/* resume data out after a message */
static int	asc_resume_dma_out();	/* resume DMA after a disconnect */
static int	asc_sendsync();		/* negotiate sync xfer */
static int	asc_replysync();	/* negotiate sync xfer */
static int	asc_msg_in();		/* process a message byte */
static int	asc_disconnect();	/* process an expected disconnect */
E 8
I 8
static int script_nop();		/* when nothing needed */
static int asc_end();			/* all come to an end */
static int asc_get_status();		/* get status from target */
static int asc_dma_in();		/* start reading data from target */
static int asc_last_dma_in();		/* cleanup after all data is read */
static int asc_resume_in();		/* resume data in after a message */
static int asc_resume_dma_in();		/* resume DMA after a disconnect */
static int asc_dma_out();		/* send data to target via dma */
static int asc_last_dma_out();		/* cleanup after all data is written */
static int asc_resume_out();		/* resume data out after a message */
static int asc_resume_dma_out();	/* resume DMA after a disconnect */
static int asc_sendsync();		/* negotiate sync xfer */
static int asc_replysync();		/* negotiate sync xfer */
static int asc_msg_in();		/* process a message byte */
static int asc_disconnect();		/* process an expected disconnect */
E 8
E 4
E 2

/* Define the index into asc_scripts for various state transitions */
#define	SCRIPT_DATA_IN		0
D 2
#define	SCRIPT_DATA_OUT		2
#define	SCRIPT_SIMPLE		4
#define	SCRIPT_GET_STATUS	5
#define	SCRIPT_MSG_IN		7
#define	SCRIPT_REPLY_SYNC	9
#define	SCRIPT_RESUME_IN	10
#define	SCRIPT_RESUME_OUT	11
E 2
I 2
#define	SCRIPT_CONTINUE_IN	2
#define	SCRIPT_DATA_OUT		3
#define	SCRIPT_CONTINUE_OUT	5
#define	SCRIPT_SIMPLE		6
#define	SCRIPT_GET_STATUS	7
I 18
#define	SCRIPT_DONE		8
E 18
#define	SCRIPT_MSG_IN		9
#define	SCRIPT_REPLY_SYNC	11
E 2
#define	SCRIPT_TRY_SYNC		12
D 2
#define	SCRIPT_RESEL		15
#define	SCRIPT_RESUME_DMA_IN	16
#define	SCRIPT_RESUME_DMA_OUT	17
E 2
I 2
#define	SCRIPT_DISCONNECT	15
#define	SCRIPT_RESEL		16
#define	SCRIPT_RESUME_IN	17
#define	SCRIPT_RESUME_DMA_IN	18
#define	SCRIPT_RESUME_OUT	19
#define	SCRIPT_RESUME_DMA_OUT	20
#define	SCRIPT_RESUME_NO_DATA	21
E 2

/*
 * Scripts
 */
script_t asc_scripts[] = {
D 2
	/* data in */
E 2
I 2
	/* start data in */
E 2
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_DATAI),	/*  0 */
		asc_dma_in, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
D 2
		&asc_scripts[SCRIPT_DATA_IN + 1] },
E 2
I 2
		&asc_scripts[SCRIPT_DATA_IN + 1]},
E 2
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_STATUS),			/*  1 */
		asc_last_dma_in, ASC_CMD_I_COMPLETE,
D 2
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2

D 2
	/* data out */
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_DATAO),	/*  2 */
E 2
I 2
D 10
	/* continue data in after a chuck is finished */
E 10
I 10
	/* continue data in after a chunk is finished */
E 10
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAI),			/*  2 */
		asc_dma_in, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_IN + 1]},

	/* start data out */
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_DATAO),	/*  3 */
E 2
		asc_dma_out, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
D 2
		&asc_scripts[SCRIPT_DATA_OUT + 1] },
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_STATUS),			/*  3 */
E 2
I 2
		&asc_scripts[SCRIPT_DATA_OUT + 1]},
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_STATUS),			/*  4 */
E 2
		asc_last_dma_out, ASC_CMD_I_COMPLETE,
D 2
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2

I 2
D 10
	/* continue data out after a chuck is finished */
E 10
I 10
	/* continue data out after a chunk is finished */
E 10
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAO),			/*  5 */
		asc_dma_out, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_OUT + 1]},

E 2
	/* simple command with no data transfer */
D 2
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_STATUS),	/*  4 */
E 2
I 2
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_STATUS),	/*  6 */
E 2
		script_nop, ASC_CMD_I_COMPLETE,
D 2
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2

	/* get status and finish command */
D 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/*  5 */
E 2
I 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/*  7 */
E 2
		asc_get_status, ASC_CMD_MSG_ACPT,
D 2
		&asc_scripts[SCRIPT_GET_STATUS + 1] },
	{SCRIPT_MATCH(ASC_INT_DISC, 0),					/*  6 */
E 2
I 2
D 18
		&asc_scripts[SCRIPT_GET_STATUS + 1]},
E 18
I 18
		&asc_scripts[SCRIPT_DONE]},
E 18
	{SCRIPT_MATCH(ASC_INT_DISC, 0),					/*  8 */
E 2
		asc_end, ASC_CMD_NOP,
D 2
		&asc_scripts[SCRIPT_GET_STATUS + 1] },
E 2
I 2
D 18
		&asc_scripts[SCRIPT_GET_STATUS + 1]},
E 18
I 18
		&asc_scripts[SCRIPT_DONE]},
E 18
E 2

	/* message in */
D 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/*  7 */
		asc_recvmsg, ASC_CMD_MSG_ACPT,
		&asc_scripts[SCRIPT_MSG_IN + 1] },
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_MSG_IN),			/*  8 */
E 2
I 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/*  9 */
		asc_msg_in, ASC_CMD_MSG_ACPT,
		&asc_scripts[SCRIPT_MSG_IN + 1]},
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_MSG_IN),			/* 10 */
E 2
		script_nop, ASC_CMD_XFER_INFO,
D 2
		&asc_scripts[SCRIPT_MSG_IN] },
E 2
I 2
		&asc_scripts[SCRIPT_MSG_IN]},
E 2

	/* send synchonous negotiation reply */
D 2
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_MSG_OUT),			/*  9 */
E 2
I 2
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_MSG_OUT),			/* 11 */
E 2
		asc_replysync, ASC_CMD_XFER_INFO,
D 2
		&asc_scripts[SCRIPT_REPLY_SYNC] },
E 2
I 2
		&asc_scripts[SCRIPT_REPLY_SYNC]},
E 2

D 2
	/* resume data in after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAI),			/* 10 */
		asc_dma_in, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_IN + 1] },

	/* resume data out after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAO),			/* 11 */
		asc_dma_out, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_OUT + 1] },

E 2
	/* try to negotiate synchonous transfer parameters */
	{SCRIPT_MATCH(ASC_INT_FC | ASC_INT_BS, ASC_PHASE_MSG_OUT),	/* 12 */
		asc_sendsync, ASC_CMD_XFER_INFO,
D 2
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
D 3
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/* 13 */
E 3
I 3
		&asc_scripts[SCRIPT_TRY_SYNC + 1]},
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_MSG_IN),			/* 13 */
E 3
		script_nop, ASC_CMD_XFER_INFO,
D 2
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
D 3
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2
	{SCRIPT_MATCH(ASC_INT_FC, ASC_PHASE_MSG_IN),			/* 14 */
D 2
		asc_recvmsg, ASC_CMD_MSG_ACPT,
		&asc_scripts[SCRIPT_GET_STATUS] },
E 2
I 2
		asc_msg_in, ASC_CMD_MSG_ACPT,
		&asc_scripts[SCRIPT_GET_STATUS]},
E 3
I 3
		&asc_scripts[SCRIPT_MSG_IN]},
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_COMMAND),			/* 14 */
		script_nop, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_RESUME_NO_DATA]},
E 3
E 2

I 2
	/* handle a disconnect */
	{SCRIPT_MATCH(ASC_INT_DISC, ASC_PHASE_DATAO),			/* 15 */
		asc_disconnect, ASC_CMD_ENABLE_SEL,
		&asc_scripts[SCRIPT_RESEL]},

E 2
	/* reselect sequence: this is just a placeholder so match fails */
D 2
	{SCRIPT_MATCH(0, ASC_PHASE_MSG_IN),				/* 15 */
E 2
I 2
	{SCRIPT_MATCH(0, ASC_PHASE_MSG_IN),				/* 16 */
E 2
		script_nop, ASC_CMD_MSG_ACPT,
D 2
		&asc_scripts[SCRIPT_RESEL] },
E 2
I 2
		&asc_scripts[SCRIPT_RESEL]},
E 2

D 2
	/* resume data in after a disconnect */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAI),			/* 16 */
E 2
I 2
	/* resume data in after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAI),			/* 17 */
		asc_resume_in, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_IN + 1]},

	/* resume partial DMA data in after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAI),			/* 18 */
E 2
		asc_resume_dma_in, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
D 2
		&asc_scripts[SCRIPT_DATA_IN + 1] },
E 2
I 2
		&asc_scripts[SCRIPT_DATA_IN + 1]},
E 2

D 2
	/* resume data out after a disconnect */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAO),			/* 17 */
E 2
I 2
	/* resume data out after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAO),			/* 19 */
		asc_resume_out, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
		&asc_scripts[SCRIPT_DATA_OUT + 1]},

	/* resume partial DMA data out after a message */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_DATAO),			/* 20 */
E 2
		asc_resume_dma_out, ASC_CMD_XFER_INFO | ASC_CMD_DMA,
D 2
		&asc_scripts[SCRIPT_DATA_OUT + 1] },
E 2
I 2
		&asc_scripts[SCRIPT_DATA_OUT + 1]},

	/* resume after a message when there is no more data */
	{SCRIPT_MATCH(ASC_INT_BS, ASC_PHASE_STATUS),			/* 21 */
		script_nop, ASC_CMD_I_COMPLETE,
		&asc_scripts[SCRIPT_GET_STATUS]},
E 2
};

/*
 * State kept for each active SCSI device.
 */
typedef struct scsi_state {
	script_t *script;	/* saved script while processing error */
	int	statusByte;	/* status byte returned during STATUS_PHASE */
	int	error;		/* errno to pass back to device driver */
	u_char	*dmaBufAddr;	/* DMA buffer address */
	u_int	dmaBufSize;	/* DMA buffer size */
	int	dmalen;		/* amount to transfer in this chunk */
	int	dmaresid;	/* amount not transfered if chunk suspended */
	int	buflen;		/* total remaining amount of data to transfer */
	char	*buf;		/* current pointer within scsicmd->buf */
	int	flags;		/* see below */
	int	msglen;		/* number of message bytes to read */
	int	msgcnt;		/* number of message bytes received */
	u_char	sync_period;	/* DMA synchronous period */
	u_char	sync_offset;	/* DMA synchronous xfer offset or 0 if async */
	u_char	msg_out;	/* next MSG_OUT byte to send */
	u_char	msg_in[16];	/* buffer for multibyte messages */
} State;

/* state flags */
#define DISCONN		0x01	/* true if currently disconnected from bus */
D 3
#define FIRST_DMA	0x02	/* true if no data DMA started yet */
E 3
I 3
#define DMA_IN_PROGRESS	0x02	/* true if data DMA started */
E 3
#define DMA_IN		0x04	/* true if reading from SCSI device */
#define DMA_OUT		0x10	/* true if writing to SCSI device */
#define DID_SYNC	0x20	/* true if synchronous offset was negotiated */
#define TRY_SYNC	0x40	/* true if try neg. synchronous offset */
I 11
#define PARITY_ERR	0x80	/* true if parity error seen */
E 11

D 9
#define ASC_NCMD	7
E 9
/*
 * State kept for each active SCSI host interface (53C94).
 */
struct asc_softc {
	asc_regmap_t	*regs;		/* chip address */
	volatile int	*dmar;		/* DMA address register address */
D 4
	volatile u_char	*buff;		/* RAM buffer address */
E 4
I 4
D 8
	u_char		*buff;		/* RAM buffer address */
E 8
I 8
	u_char		*buff;		/* RAM buffer address (uncached) */
E 8
E 4
	int		myid;		/* SCSI ID of this interface */
	int		myidmask;	/* ~(1 << myid) */
	int		state;		/* current SCSI connection state */
	int		target;		/* target SCSI ID if busy */
	script_t	*script;	/* next expected interrupt & action */
	ScsiCmd		*cmd[ASC_NCMD];	/* active command indexed by SCSI ID */
	State		st[ASC_NCMD];	/* state info for each active command */
I 8
	void		(*dma_start)();	/* Start dma routine */
	void		(*dma_end)();	/* End dma routine */
	u_char		*dma_next;
	int		dma_xfer;	/* Dma len still to go */
	int		min_period;	/* Min transfer period clk/byte */
	int		max_period;	/* Max transfer period clk/byte */
	int		ccf;		/* CCF, whatever that really is? */
	int		timeout_250;	/* 250ms timeout */
	int		tb_ticks;	/* 4ns. ticks/tb channel ticks */
E 8
} asc_softc[NASC];

#define	ASC_STATE_IDLE		0	/* idle state */
#define	ASC_STATE_BUSY		1	/* selecting or currently connected */
#define ASC_STATE_TARGET	2	/* currently selected as target */
#define ASC_STATE_RESEL		3	/* currently waiting for reselect */

typedef struct asc_softc *asc_softc_t;

/*
I 8
 * Dma operations.
 */
#define	ASCDMA_READ	1
#define	ASCDMA_WRITE	2
static void tb_dma_start(), tb_dma_end(), asic_dma_start(), asic_dma_end();
D 9
u_long asc_iobuf[33792];
E 9
I 9
extern u_long asc_iomem;
extern u_long asic_base;
E 9

/*
E 8
 * Definition of the controller for the auto-configuration program.
 */
int	asc_probe();
void	asc_start();
void	asc_intr();
struct	driver ascdriver = {
	"asc", asc_probe, asc_start, 0, asc_intr,
};

/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
asc_probe(cp)
	register struct pmax_ctlr *cp;
{
	register asc_softc_t asc;
	register asc_regmap_t *regs;
	int unit, id, s, i;
I 8
D 9
	u_int bufadr;
E 9
I 9
	int bufsiz;
E 9
E 8

	if ((unit = cp->pmax_unit) >= NASC)
		return (0);
	if (badaddr(cp->pmax_addr + ASC_OFFSET_53C94, 1))
		return (0);
	asc = &asc_softc[unit];

	/*
	 * Initialize hw descriptor, cache some pointers
	 */
	asc->regs = (asc_regmap_t *)(cp->pmax_addr + ASC_OFFSET_53C94);
D 8
	asc->dmar = (volatile int *)(cp->pmax_addr + ASC_OFFSET_DMAR);
D 4
	asc->buff = (volatile u_char *)(cp->pmax_addr + ASC_OFFSET_RAM);
E 4
I 4
	asc->buff = (u_char *)(cp->pmax_addr + ASC_OFFSET_RAM);
E 8
E 4

I 8
	/*
	 * Set up machine dependencies.
	 * 1) how to do dma
	 * 2) timing based on turbochannel frequency
	 */
	switch (pmax_boardtype) {
	case DS_3MIN:
	case DS_MAXINE:
I 9
	case DS_3MAXPLUS:
E 9
	    if (unit == 0) {
D 9
		bufadr = MACH_PHYS_TO_UNCACHED(MACH_CACHED_TO_PHYS(asc_iobuf));
		bufadr = (bufadr + NBPG - 1) & ~(NBPG - 1);
		asc->buff = (u_char *)bufadr;
		*((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMAPTR))
			= -1;
		*((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMANPTR))
			= -1;
		*((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_SCR)) = 0;
E 9
I 9
		asc->buff = (u_char *)MACH_PHYS_TO_UNCACHED(asc_iomem);
		bufsiz = 8192;
		*((volatile int *)ASIC_REG_SCSI_DMAPTR(asic_base)) = -1;
		*((volatile int *)ASIC_REG_SCSI_DMANPTR(asic_base)) = -1;
		*((volatile int *)ASIC_REG_SCSI_SCR(asic_base)) = 0;
E 9
		asc->dma_start = asic_dma_start;
		asc->dma_end = asic_dma_end;
		break;
	    }
	    /*
	     * Fall through for turbochannel option.
	     */
	case DS_3MAX:
	default:
	    asc->dmar = (volatile int *)(cp->pmax_addr + ASC_OFFSET_DMAR);
	    asc->buff = (u_char *)(cp->pmax_addr + ASC_OFFSET_RAM);
I 9
	    bufsiz = PER_TGT_DMA_SIZE;
E 9
	    asc->dma_start = tb_dma_start;
	    asc->dma_end = tb_dma_end;
	};
	/*
	 * Now for timing. The 3max has a 25Mhz tb whereas the 3min and
	 * maxine are 12.5Mhz.
	 */
	switch (pmax_boardtype) {
	case DS_3MAX:
I 9
	case DS_3MAXPLUS:
E 9
		asc->min_period = ASC_MIN_PERIOD25;
		asc->max_period = ASC_MAX_PERIOD25;
		asc->ccf = ASC_CCF(25);
		asc->timeout_250 = ASC_TIMEOUT_250(25, asc->ccf);
		asc->tb_ticks = 10;
		break;
	case DS_3MIN:
	case DS_MAXINE:
	default:
		asc->min_period = ASC_MIN_PERIOD12;
		asc->max_period = ASC_MAX_PERIOD12;
		asc->ccf = ASC_CCF(13);
		asc->timeout_250 = ASC_TIMEOUT_250(13, asc->ccf);
		asc->tb_ticks = 20;
		break;
	};

E 8
	asc->state = ASC_STATE_IDLE;
	asc->target = -1;

	regs = asc->regs;

	/*
	 * Reset chip, fully.  Note that interrupts are already enabled.
	 */
	s = splbio();

	/* preserve our ID for now */
	asc->myid = regs->asc_cnfg1 & ASC_CNFG1_MY_BUS_ID;
	asc->myidmask = ~(1 << asc->myid);

	asc_reset(asc, regs);

	/*
	 * Our SCSI id on the bus.
	 * The user can set this via the prom on 3maxen/pmaxen.
	 * If this changes it is easy to fix: make a default that
	 * can be changed as boot arg.
	 */
#ifdef	unneeded
	regs->asc_cnfg1 = (regs->asc_cnfg1 & ~ASC_CNFG1_MY_BUS_ID) |
			      (scsi_initiator_id[unit] & 0x7);
#endif
	id = regs->asc_cnfg1 & ASC_CNFG1_MY_BUS_ID;
	splx(s);

	/*
	 * Statically partition the DMA buffer between targets.
	 * This way we will eventually be able to attach/detach
	 * drives on-fly.  And 18k/target is plenty for normal use.
	 */
D 9
#define PER_TGT_DMA_SIZE	((ASC_RAM_SIZE/7) & ~(sizeof(int)-1))
E 9

	/*
	 * Give each target its own DMA buffer region.
	 * We may want to try ping ponging buffers later.
	 */
	for (i = 0; i < ASC_NCMD; i++) {
D 9
		asc->st[i].dmaBufAddr = asc->buff + PER_TGT_DMA_SIZE * i;
		asc->st[i].dmaBufSize = PER_TGT_DMA_SIZE;
E 9
I 9
		asc->st[i].dmaBufAddr = asc->buff + bufsiz * i;
		asc->st[i].dmaBufSize = bufsiz;
E 9
	}
	printf("asc%d at nexus0 csr 0x%x priority %d SCSI id %d\n",
		unit, cp->pmax_addr, cp->pmax_pri, id);
	return (1);
}

/*
 * Start activity on a SCSI device.
 * We maintain information on each device separately since devices can
 * connect/disconnect during an operation.
 */
void
asc_start(scsicmd)
	register ScsiCmd *scsicmd;	/* command to start */
{
	register struct scsi_device *sdp = scsicmd->sd;
	register asc_softc_t asc = &asc_softc[sdp->sd_ctlr];
	int s;

	s = splbio();
	/*
	 * Check if another command is already in progress.
	 * We may have to change this if we allow SCSI devices with
	 * separate LUNs.
	 */
	if (asc->cmd[sdp->sd_drive]) {
		printf("asc%d: device %s busy at start\n", sdp->sd_ctlr,
			sdp->sd_driver->d_name);
		(*sdp->sd_driver->d_done)(scsicmd->unit, EBUSY,
			scsicmd->buflen, 0);
		splx(s);
	}
	asc->cmd[sdp->sd_drive] = scsicmd;
	asc_startcmd(asc, sdp->sd_drive);
	splx(s);
}

static void
asc_reset(asc, regs)
	asc_softc_t asc;
	asc_regmap_t *regs;
{

	/*
	 * Reset chip and wait till done
	 */
	regs->asc_cmd = ASC_CMD_RESET;
	MachEmptyWriteBuffer(); DELAY(25);

	/* spec says this is needed after reset */
	regs->asc_cmd = ASC_CMD_NOP;
	MachEmptyWriteBuffer(); DELAY(25);

	/*
	 * Set up various chip parameters
	 */
D 8
	regs->asc_ccf = ASC_CCF_25MHz;	/* 25 MHz clock */
E 8
I 8
	regs->asc_ccf = asc->ccf;
E 8
	MachEmptyWriteBuffer(); DELAY(25);
D 8
	regs->asc_sel_timo = ASC_TIMEOUT_250;
E 8
I 8
	regs->asc_sel_timo = asc->timeout_250;
E 8
	/* restore our ID */
	regs->asc_cnfg1 = asc->myid | ASC_CNFG1_P_CHECK;
D 8
	regs->asc_cnfg2 = /* ASC_CNFG2_RFB | */ ASC_CNFG2_EPL;
E 8
I 8
D 9
	regs->asc_cnfg2 = /* ASC_CNFG2_RFB | */ ASC_CNFG2_SCSI2;
E 9
I 9
	/* include ASC_CNFG2_SCSI2 if you want to allow SCSI II commands */
	regs->asc_cnfg2 = /* ASC_CNFG2_RFB | ASC_CNFG2_SCSI2 | */ ASC_CNFG2_EPL;
E 9
E 8
	regs->asc_cnfg3 = 0;
	/* zero anything else */
	ASC_TC_PUT(regs, 0);
D 8
	regs->asc_sel_timo = ASC_TIMEOUT_250;
	regs->asc_syn_p = ASC_MIN_PERIOD;
E 8
I 8
	regs->asc_syn_p = asc->min_period;
E 8
	regs->asc_syn_o = 0;	/* async for now */
	MachEmptyWriteBuffer();
}

/*
 * Start a SCSI command on a target.
 */
static void
asc_startcmd(asc, target)
	asc_softc_t asc;
	int target;
{
	register asc_regmap_t *regs;
	register ScsiCmd *scsicmd;
	register State *state;
	int len;

	/*
	 * See if another target is currently selected on this SCSI bus.
	 */
	if (asc->target >= 0)
		return;

	regs = asc->regs;

	/*
D 11
	 * Check to see if a reselection is in progress and if so,
	 * try to cancel it or respond to the reselection if it won.
E 11
I 11
	 * If a reselection is in progress, it is Ok to ignore it since
	 * the ASC will automatically cancel the command and flush
	 * the FIFO if the ASC is reselected before the command starts.
	 * If we try to use ASC_CMD_DISABLE_SEL, we can hang the system if
	 * a reselect occurs before starting the command.
E 11
	 */
D 11
	if (asc->state == ASC_STATE_RESEL) {
		regs->asc_cmd = ASC_CMD_DISABLE_SEL;
I 8
		readback(regs->asc_cmd);
E 8
		while (!(regs->asc_status & ASC_CSR_INT))
			DELAY(1);
		asc_intr(asc - asc_softc);
		/* we will be busy if a reselecting device won */
		if (asc->state == ASC_STATE_BUSY)
			return;
	}
E 11

	asc->state = ASC_STATE_BUSY;
	asc->target = target;

	/* cache some pointers */
	scsicmd = asc->cmd[target];
	state = &asc->st[target];

#ifdef DEBUG
	if (asc_debug > 1) {
		printf("asc_startcmd: %s target %d cmd %x len %d\n",
			scsicmd->sd->sd_driver->d_name, target,
			scsicmd->cmd[0], scsicmd->buflen);
	}
D 12
	asc_debug_cmd = scsicmd->cmd[0];
	if (scsicmd->cmd[0] == SCSI_READ_EXT) {
		asc_debug_bn = (scsicmd->cmd[2] << 24) |
			(scsicmd->cmd[3] << 16) |
			(scsicmd->cmd[4] << 8) |
			scsicmd->cmd[5];
		asc_debug_sz = (scsicmd->cmd[7] << 8) | scsicmd->cmd[8];
	}
D 3
	asc_logp->status = PACK(asc - asc_softc, 0, 0, 0);
E 3
I 3
	asc_logp->status = PACK(asc - asc_softc, 0, 0, asc_debug_cmd);
E 3
	asc_logp->target = asc->target;
	asc_logp->state = 0;
I 3
	asc_logp->msg = 0xff;
I 11
	asc_logp->resid = scsicmd->buflen;
E 11
E 3
	if (++asc_logp >= &asc_log[NLOG])
		asc_logp = asc_log;
E 12
#endif

	/*
	 * Init the chip and target state.
	 */
D 11
	regs->asc_cmd = ASC_CMD_FLUSH;
I 8
	readback(regs->asc_cmd);
	DELAY(2);
E 11
E 8
D 3
	state->flags = FIRST_DMA | (state->flags & DID_SYNC);
E 3
I 3
	state->flags = state->flags & DID_SYNC;
E 3
	state->error = 0;
	state->script = (script_t *)0;
	state->msg_out = SCSI_NO_OP;

	/*
	 * Copy command data to the DMA buffer.
	 */
D 12
	len = scsicmd->cmdlen;
E 12
I 12
D 13
	len = scsicmd->cmdlen + 1;
E 13
I 13
	len = scsicmd->cmdlen;
E 13
E 12
	state->dmalen = len;
D 12
	bcopy(scsicmd->cmd, state->dmaBufAddr, len);
E 12
I 12
D 13
	state->dmaBufAddr[0] = SCSI_DIS_REC_IDENTIFY;
	bcopy(scsicmd->cmd, state->dmaBufAddr + 1, len);
E 13
I 13
	bcopy(scsicmd->cmd, state->dmaBufAddr, len);
E 13
E 12

	/* check for simple SCSI command with no data transfer */
	if ((state->buflen = scsicmd->buflen) == 0) {
		/* check for sync negotiation */
		if ((scsicmd->flags & SCSICMD_USE_SYNC) &&
		    !(state->flags & DID_SYNC)) {
			asc->script = &asc_scripts[SCRIPT_TRY_SYNC];
			state->flags |= TRY_SYNC;
		} else
			asc->script = &asc_scripts[SCRIPT_SIMPLE];
		state->buf = (char *)0;
	} else if (scsicmd->flags & SCSICMD_DATA_TO_DEVICE) {
D 3
		int cnt;

E 3
		asc->script = &asc_scripts[SCRIPT_DATA_OUT];
D 3

		/* setup to write first chunk */
		state->flags |= DMA_OUT;
E 3
		state->buf = scsicmd->buf;
D 3
		cnt = state->dmaBufSize - len;
		if (cnt > state->buflen)
			cnt = state->buflen;
		else printf("can't write in one chunk cnt %d buflen %d\n",
			cnt, state->buflen); /* XXX */
		state->dmalen = cnt;
		bcopy(state->buf, state->dmaBufAddr + len, cnt);
E 3
I 3
		state->flags |= DMA_OUT;
E 3
	} else {
		asc->script = &asc_scripts[SCRIPT_DATA_IN];
		state->buf = scsicmd->buf;
		state->flags |= DMA_IN;
	}

D 12
	/* preload the FIFO with the message to be sent */
D 2
	regs->asc_fifo = /* SCSI_IDENTIFY */ SCSI_DIS_REC_IDENTIFY;
E 2
I 2
	regs->asc_fifo = SCSI_DIS_REC_IDENTIFY;
I 8
	MachEmptyWriteBuffer();
E 12
I 12
#ifdef DEBUG
	asc_debug_cmd = scsicmd->cmd[0];
	if (scsicmd->cmd[0] == SCSI_READ_EXT) {
		asc_debug_bn = (scsicmd->cmd[2] << 24) |
			(scsicmd->cmd[3] << 16) |
			(scsicmd->cmd[4] << 8) |
			scsicmd->cmd[5];
		asc_debug_sz = (scsicmd->cmd[7] << 8) | scsicmd->cmd[8];
	}
	asc_logp->status = PACK(asc - asc_softc, 0, 0, asc_debug_cmd);
	asc_logp->target = asc->target;
	asc_logp->state = asc->script - asc_scripts;
	asc_logp->msg = SCSI_DIS_REC_IDENTIFY;
	asc_logp->resid = scsicmd->buflen;
	if (++asc_logp >= &asc_log[NLOG])
		asc_logp = asc_log;
#endif
E 12
E 8
E 2

I 13
	/* preload the FIFO with the message to be sent */
	regs->asc_fifo = SCSI_DIS_REC_IDENTIFY;
	MachEmptyWriteBuffer();

E 13
D 12
	/* start the asc */
E 12
I 12
	/* initialize the DMA */
E 12
D 8
	*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(state->dmaBufAddr);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr, ASCDMA_WRITE);
E 8
	ASC_TC_PUT(regs, len);
I 8
	readback(regs->asc_cmd);
E 8

	regs->asc_dbus_id = target;
I 8
	readback(regs->asc_dbus_id);
E 8
	regs->asc_syn_p = state->sync_period;
I 8
	readback(regs->asc_syn_p);
E 8
	regs->asc_syn_o = state->sync_offset;
I 8
	readback(regs->asc_syn_o);
E 8

	if (state->flags & TRY_SYNC)
D 3
		regs->asc_cmd = ASC_CMD_SEL_ATN_STOP | ASC_CMD_DMA;
E 3
I 3
		regs->asc_cmd = ASC_CMD_SEL_ATN_STOP;
E 3
	else
		regs->asc_cmd = ASC_CMD_SEL_ATN | ASC_CMD_DMA;
I 8
	readback(regs->asc_cmd);
E 8
}

/*
 * Interrupt routine
 *	Take interrupts from the chip
 *
 * Implementation:
 *	Move along the current command's script if
 *	all is well, invoke error handler if not.
 */
void
asc_intr(unit)
	int unit;
{
	register asc_softc_t asc = &asc_softc[unit];
	register asc_regmap_t *regs = asc->regs;
	register State *state;
	register script_t *scpt;
	register int ss, ir, status;

D 3
again:
E 3
	/* collect ephemeral information */
	status = regs->asc_status;
I 3
again:
E 3
	ss = regs->asc_ss;
	ir = regs->asc_intr;	/* this resets the previous two */
	scpt = asc->script;

#ifdef DEBUG
	asc_logp->status = PACK(unit, status, ss, ir);
	asc_logp->target = (asc->state == ASC_STATE_BUSY) ? asc->target : -1;
	asc_logp->state = scpt - asc_scripts;
	asc_logp->msg = -1;
I 11
	asc_logp->resid = 0;
E 11
	if (++asc_logp >= &asc_log[NLOG])
		asc_logp = asc_log;
	if (asc_debug > 2)
		printf("asc_intr: status %x ss %x ir %x cond %d:%x\n",
			status, ss, ir, scpt - asc_scripts, scpt->condition);
#endif

	/* check the expected state */
	if (SCRIPT_MATCH(ir, status) == scpt->condition) {
		/*
		 * Perform the appropriate operation, then proceed.
		 */
		if ((*scpt->action)(asc, status, ss, ir)) {
			regs->asc_cmd = scpt->command;
I 8
			readback(regs->asc_cmd);
E 8
			asc->script = scpt->next;
		}
		goto done;
	}

I 11
	/*
	 * Check for parity error.
	 * Hardware will automatically set ATN
	 * to request the device for a MSG_OUT phase.
	 */
	if (status & ASC_CSR_PE) {
		printf("asc%d: SCSI device %d: incomming parity error seen\n",
			asc - asc_softc, asc->target);
		asc->st[asc->target].flags |= PARITY_ERR;
	}

	/*
	 * Check for gross error.
	 * Probably a bug in a device driver.
	 */
	if (status & ASC_CSR_GE) {
		printf("asc%d: SCSI device %d: gross error\n",
			asc - asc_softc, asc->target);
		goto abort;
	}

E 11
	/* check for message in or out */
	if ((ir & ~ASC_INT_FC) == ASC_INT_BS) {
		register int len, fifo;

		state = &asc->st[asc->target];
		switch (ASC_PHASE(status)) {
I 3
		case ASC_PHASE_DATAI:
		case ASC_PHASE_DATAO:
			ASC_TC_GET(regs, len);
			fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
			printf("asc_intr: data overrun: buflen %d dmalen %d tc %d fifo %d\n",
				state->buflen, state->dmalen, len, fifo);
			goto abort;

E 3
		case ASC_PHASE_MSG_IN:
			break;

		case ASC_PHASE_MSG_OUT:
I 11
			/*
			 * Check for parity error.
			 * Hardware will automatically set ATN
			 * to request the device for a MSG_OUT phase.
			 */
			if (state->flags & PARITY_ERR) {
				state->flags &= ~PARITY_ERR;
				state->msg_out = SCSI_MESSAGE_PARITY_ERROR;
				/* reset message in counter */
				state->msglen = 0;
			} else
				state->msg_out = SCSI_NO_OP;
E 11
			regs->asc_fifo = state->msg_out;
D 11
			state->msg_out = SCSI_NO_OP;
E 11
			regs->asc_cmd = ASC_CMD_XFER_INFO;
I 8
			readback(regs->asc_cmd);
E 8
			goto done;

		case ASC_PHASE_STATUS:
I 2
D 3
			asc_DumpLog("asc_intr: status"); /* XXX */
E 3
E 2
			/* probably an error in the SCSI command */
			asc->script = &asc_scripts[SCRIPT_GET_STATUS];
			regs->asc_cmd = ASC_CMD_I_COMPLETE;
I 8
			readback(regs->asc_cmd);
E 8
			goto done;

		default:
			goto abort;
		}

		if (state->script)
			goto abort;

		/* check for DMA in progress */
		ASC_TC_GET(regs, len);
		fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
		/* flush any data in the FIFO */
		if (fifo) {
D 3
			printf("asc_intr: suspend flags %x dmalen %d len %d fifo %d\n",
				state->flags, state->dmalen,
				len, fifo); /* XXX */
			len += fifo;
E 3
I 3
			if (state->flags & DMA_OUT)
				len += fifo;
			else if (state->flags & DMA_IN) {
				u_char *cp;

				printf("asc_intr: IN: dmalen %d len %d fifo %d\n",
					state->dmalen, len, fifo); /* XXX */
				len += fifo;
				cp = state->dmaBufAddr + (state->dmalen - len);
				while (fifo-- > 0)
					*cp++ = regs->asc_fifo;
			} else
				printf("asc_intr: dmalen %d len %d fifo %d\n",
					state->dmalen, len, fifo); /* XXX */
E 3
			regs->asc_cmd = ASC_CMD_FLUSH;
I 8
			readback(regs->asc_cmd);
E 8
D 10
			MachEmptyWriteBuffer();
E 10
I 8
			DELAY(2);
E 8
		}
D 15
		if (len) {
E 15
I 15
		if (len && (state->flags & DMA_IN_PROGRESS)) {
E 15
			/* save number of bytes still to be sent or received */
			state->dmaresid = len;
I 15
			state->flags &= ~DMA_IN_PROGRESS;
I 16
			ASC_TC_PUT(regs, 0);
E 16
E 15
I 12
#ifdef DEBUG
			if (asc_logp == asc_log)
				asc_log[NLOG - 1].resid = len;
			else
				asc_logp[-1].resid = len;
#endif
E 12
			/* setup state to resume to */
D 12
			if (state->flags & DMA_IN)
E 12
I 12
			if (state->flags & DMA_IN) {
				/*
				 * Since the ASC_CNFG3_SRB bit of the
				 * cnfg3 register bit is not set,
				 * we just transferred an extra byte.
				 * Since we can't resume on an odd byte
				 * boundary, we copy the valid data out
				 * and resume DMA at the start address.
				 */
				if (len & 1) {
					printf("asc_intr: msg in len %d (fifo %d)\n",
D 15
						len, fifo);
E 15
I 15
						len, fifo); /* XXX */
E 15
					len = state->dmalen - len;
					goto do_in;
				}
E 12
				state->script =
					&asc_scripts[SCRIPT_RESUME_DMA_IN];
D 12
			else if (state->flags & DMA_OUT)
E 12
I 12
			} else if (state->flags & DMA_OUT)
E 12
				state->script =
					&asc_scripts[SCRIPT_RESUME_DMA_OUT];
			else
				state->script = asc->script;
I 11
D 12
#ifdef DEBUG
			if (asc_logp == asc_log)
				asc_log[NLOG - 1].resid = len;
			else
				asc_logp[-1].resid = len;
#endif
E 12
E 11
D 15
		} else {
E 15
I 15
		} else if (state->flags & DMA_IN) {
D 16
			if (len)
				printf("asc_intr: 1: len %d (fifo %d)\n", len,
					fifo); /* XXX */
E 16
I 16
			if (len) {
				printf("asc_intr: 1: bn %d len %d (fifo %d)\n",
					asc_debug_bn, len, fifo); /* XXX */
				goto abort;
			}
E 16
E 15
			/* setup state to resume to */
D 2
			if (state->flags & DMA_IN)
				state->script = &asc_scripts[SCRIPT_RESUME_IN];
			else if (state->flags & DMA_OUT)
				state->script = &asc_scripts[SCRIPT_RESUME_OUT];
			else
E 2
I 2
D 15
			if (state->flags & DMA_IN) {
D 3
				if (!(state->flags & FIRST_DMA)) {
E 3
I 3
				if (state->flags & DMA_IN_PROGRESS) {
I 12
					len = state->dmalen;
				do_in:
E 12
					state->flags &= ~DMA_IN_PROGRESS;
I 8
					(*asc->dma_end)(asc, state, ASCDMA_READ);
E 8
E 3
D 12
					len = state->dmalen;
E 12
					bcopy(state->dmaBufAddr, state->buf,
						len);
					state->buf += len;
					state->buflen -= len;
D 3
				} else
					state->flags &= ~FIRST_DMA;
E 3
I 3
				}
E 3
				if (state->buflen)
					state->script =
					    &asc_scripts[SCRIPT_RESUME_IN];
				else
					state->script =
					    &asc_scripts[SCRIPT_RESUME_NO_DATA];
			} else if (state->flags & DMA_OUT) {
				/*
				 * If this is the last chunk, the next expected
				 * state is to get status.
				 */
D 3
				len = state->dmalen;
				state->buf += len;
				state->buflen -= len;
E 3
I 3
				if (state->flags & DMA_IN_PROGRESS) {
					state->flags &= ~DMA_IN_PROGRESS;
I 8
					(*asc->dma_end)(asc, state, ASCDMA_WRITE);
E 8
					len = state->dmalen;
					state->buf += len;
					state->buflen -= len;
				}
E 3
				if (state->buflen)
					state->script =
					    &asc_scripts[SCRIPT_RESUME_OUT];
				else
					state->script =
					    &asc_scripts[SCRIPT_RESUME_NO_DATA];
D 3
			} else
E 3
I 3
			} else if (asc->script == &asc_scripts[SCRIPT_SIMPLE])
E 15
I 15
			if (state->flags & DMA_IN_PROGRESS) {
				len = state->dmalen;
				state->flags &= ~DMA_IN_PROGRESS;
			do_in:
				(*asc->dma_end)(asc, state, ASCDMA_READ);
				bcopy(state->dmaBufAddr, state->buf, len);
				state->buf += len;
				state->buflen -= len;
			}
			if (state->buflen)
E 15
				state->script =
D 11
					    &asc_scripts[SCRIPT_RESUME_NO_DATA];
E 11
I 11
D 15
					&asc_scripts[SCRIPT_RESUME_NO_DATA];
E 15
I 15
				    &asc_scripts[SCRIPT_RESUME_IN];
E 15
E 11
			else
E 3
E 2
D 15
				state->script = asc->script;
		}
E 15
I 15
				state->script =
				    &asc_scripts[SCRIPT_RESUME_NO_DATA];
		} else if (state->flags & DMA_OUT) {
D 16
			if (len)
E 16
I 16
			if (len) {
E 16
				printf("asc_intr: 2: len %d (fifo %d)\n", len,
					fifo); /* XXX */
I 16
				goto abort;
			}
E 16
			/*
			 * If this is the last chunk, the next expected
			 * state is to get status.
			 */
			if (state->flags & DMA_IN_PROGRESS) {
				state->flags &= ~DMA_IN_PROGRESS;
				(*asc->dma_end)(asc, state, ASCDMA_WRITE);
				len = state->dmalen;
				state->buf += len;
				state->buflen -= len;
			}
			if (state->buflen)
				state->script =
				    &asc_scripts[SCRIPT_RESUME_OUT];
			else
				state->script =
				    &asc_scripts[SCRIPT_RESUME_NO_DATA];
		} else if (asc->script == &asc_scripts[SCRIPT_SIMPLE])
			state->script = &asc_scripts[SCRIPT_RESUME_NO_DATA];
		else
			state->script = asc->script;
E 15

		/* setup to receive a message */
		asc->script = &asc_scripts[SCRIPT_MSG_IN];
		state->msglen = 0;
		regs->asc_cmd = ASC_CMD_XFER_INFO;
I 8
		readback(regs->asc_cmd);
E 8
		goto done;
	}

	/* check for SCSI bus reset */
	if (ir & ASC_INT_RESET) {
		register int i;

		printf("asc%d: SCSI bus reset!!\n", asc - asc_softc);
		/* need to flush any pending commands */
		for (i = 0; i < ASC_NCMD; i++) {
			if (!asc->cmd[i])
				continue;
			asc->st[i].error = EIO;
			asc_end(asc, 0, 0, 0);
		}
		/* rearbitrate synchronous offset */
		for (i = 0; i < ASC_NCMD; i++) {
			asc->st[i].sync_offset = 0;
			asc->st[i].flags = 0;
		}
		asc->target = -1;
		return;
	}

	/* check for command errors */
	if (ir & ASC_INT_ILL)
		goto abort;

	/* check for disconnect */
	if (ir & ASC_INT_DISC) {
		state = &asc->st[asc->target];
D 2
		if (state->flags & DISCONN) {
			if (state->script)
				goto abort;
			state->script = asc->script;
			asc->target = -1;
			asc->state = ASC_STATE_RESEL;
			asc->script = &asc_scripts[SCRIPT_RESEL];
			regs->asc_cmd = ASC_CMD_ENABLE_SEL;
			goto done;
		}

E 2
D 18
		switch (ASC_SS(ss)) {
		case 0: /* device did not respond */
D 11
			state->error = ENXIO;
			asc_end(asc, status, ss, ir);
			return;
E 11
I 11
			/* check for one of the starting scripts */
			switch (asc->script - asc_scripts) {
			case SCRIPT_TRY_SYNC:
			case SCRIPT_SIMPLE:
			case SCRIPT_DATA_IN:
			case SCRIPT_DATA_OUT:
E 18
I 18
		switch (asc->script - asc_scripts) {
		case SCRIPT_DONE:
		case SCRIPT_DISCONNECT:
			/*
			 * Disconnects can happen normally when the
			 * command is complete with the phase being
			 * either ASC_PHASE_DATAO or ASC_PHASE_MSG_IN.
			 * The SCRIPT_MATCH() only checks for one phase
			 * so we can wind up here.
			 * Perform the appropriate operation, then proceed.
			 */
			if ((*scpt->action)(asc, status, ss, ir)) {
				regs->asc_cmd = scpt->command;
				readback(regs->asc_cmd);
				asc->script = scpt->next;
			}
			goto done;

		case SCRIPT_TRY_SYNC:
		case SCRIPT_SIMPLE:
		case SCRIPT_DATA_IN:
		case SCRIPT_DATA_OUT: /* one of the starting scripts */
			if (ASC_SS(ss) == 0) {
				/* device did not respond */
E 18
				if (regs->asc_flags & ASC_FLAGS_FIFO_CNT) {
					regs->asc_cmd = ASC_CMD_FLUSH;
					readback(regs->asc_cmd);
				}
				state->error = ENXIO;
				asc_end(asc, status, ss, ir);
				return;
			}
			/* FALLTHROUGH */
E 11

		default:
I 11
			printf("asc%d: SCSI device %d: unexpected disconnect\n",
				asc - asc_softc, asc->target);
I 18
#ifdef DEBUG
			asc_DumpLog("asc_disc");
#endif
E 18
E 11
D 9
			goto abort;
E 9
I 9
			/*
			 * On rare occasions my RZ24 does a disconnect during
			 * data in phase and the following seems to keep it
			 * happy.
			 * XXX Should a scsi disk ever do this??
			 */
			asc->script = &asc_scripts[SCRIPT_RESEL];
			asc->state = ASC_STATE_RESEL;
			state->flags |= DISCONN;
			regs->asc_cmd = ASC_CMD_ENABLE_SEL;
			readback(regs->asc_cmd);
			return;
E 9
		}
	}

	/* check for reselect */
	if (ir & ASC_INT_RESEL) {
		unsigned fifo, id, msg;

		fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
		if (fifo < 2)
			goto abort;
		/* read unencoded SCSI ID and convert to binary */
		msg = regs->asc_fifo & asc->myidmask;
		for (id = 0; (msg & 1) == 0; id++)
			msg >>= 1;
		/* read identify message */
		msg = regs->asc_fifo;
#ifdef DEBUG
		if (asc_logp == asc_log)
			asc_log[NLOG - 1].msg = msg;
		else
			asc_logp[-1].msg = msg;
#endif
D 11
		if (asc->state != ASC_STATE_RESEL)
			goto abort;
E 11
		asc->state = ASC_STATE_BUSY;
		asc->target = id;
		state = &asc->st[id];
		asc->script = state->script;
		state->script = (script_t *)0;
		if (!(state->flags & DISCONN))
			goto abort;
		state->flags &= ~DISCONN;
I 3
		regs->asc_syn_p = state->sync_period;
		regs->asc_syn_o = state->sync_offset;
E 3
		regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
		readback(regs->asc_cmd);
E 8
		goto done;
	}

	/* check if we are being selected as a target */
	if (ir & (ASC_INT_SEL | ASC_INT_SEL_ATN))
		goto abort;

D 11
	/* must be just a ASC_INT_FC */
E 11
I 11
	/*
	 * 'ir' must be just ASC_INT_FC.
	 * This is normal if canceling an ASC_ENABLE_SEL.
	 */

E 11
done:
	MachEmptyWriteBuffer();
D 3
	if (regs->asc_status & ASC_CSR_INT)
E 3
I 3
	/* watch out for HW race conditions and setup & hold time violations */
	ir = regs->asc_status;
	while (ir != (status = regs->asc_status))
		ir = status;
	if (status & ASC_CSR_INT)
E 3
		goto again;
	return;

abort:
#ifdef DEBUG
	asc_DumpLog("asc_intr");
#endif
#if 0
	panic("asc_intr");
#else
D 16
	for (;;);
E 16
I 16
	boot(4); /* XXX */
E 16
#endif
}

/*
 * All the many little things that the interrupt
 * routine might switch to.
 */

/* ARGSUSED */
static int
script_nop(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	return (1);
}

/* ARGSUSED */
static int
asc_get_status(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register int data;

	/*
	 * Get the last two bytes in the FIFO.
	 */
	if ((data = regs->asc_flags & ASC_FLAGS_FIFO_CNT) != 2) {
		printf("asc_get_status: fifo cnt %d\n", data); /* XXX */
I 17
#ifdef DEBUG
E 17
I 11
		asc_DumpLog("get_status"); /* XXX */
I 17
#endif
E 17
E 11
		if (data < 2) {
			asc->regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
			readback(asc->regs->asc_cmd);
E 8
			return (0);
		}
		do {
			data = regs->asc_fifo;
		} while ((regs->asc_flags & ASC_FLAGS_FIFO_CNT) > 2);
	}

	/* save the status byte */
	asc->st[asc->target].statusByte = data = regs->asc_fifo;
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].msg = data;
	else
		asc_logp[-1].msg = data;
#endif

	/* get the (presumed) command_complete message */
	if ((data = regs->asc_fifo) == SCSI_COMMAND_COMPLETE)
		return (1);

#ifdef DEBUG
	printf("asc_get_status: status %x cmd %x\n",
		asc->st[asc->target].statusByte, data);
	asc_DumpLog("asc_get_status");
#endif
	return (0);
}

/* ARGSUSED */
static int
asc_end(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register ScsiCmd *scsicmd;
	register State *state;
	register int i, target;

	asc->state = ASC_STATE_IDLE;
	target = asc->target;
	asc->target = -1;
	scsicmd = asc->cmd[target];
	asc->cmd[target] = (ScsiCmd *)0;
	state = &asc->st[target];

#ifdef DEBUG
	if (asc_debug > 1) {
		printf("asc_end: %s target %d cmd %x err %d resid %d\n",
			scsicmd->sd->sd_driver->d_name, target,
			scsicmd->cmd[0], state->error, state->buflen);
	}
#endif
#ifdef DIAGNOSTIC
	if (target < 0 || !scsicmd)
		panic("asc_end");
#endif

	/* look for disconnected devices */
	for (i = 0; i < ASC_NCMD; i++) {
		if (!asc->cmd[i] || !(asc->st[i].flags & DISCONN))
			continue;
		asc->regs->asc_cmd = ASC_CMD_ENABLE_SEL;
I 8
		readback(asc->regs->asc_cmd);
E 8
		asc->state = ASC_STATE_RESEL;
		asc->script = &asc_scripts[SCRIPT_RESEL];
		break;
	}

D 11
	/* look for another device that is ready */
E 11
I 11
	/*
	 * Look for another device that is ready.
	 * May want to keep last one started and increment for fairness
	 * rather than always starting at zero.
	 */
E 11
	for (i = 0; i < ASC_NCMD; i++) {
		/* don't restart a disconnected command */
		if (!asc->cmd[i] || (asc->st[i].flags & DISCONN))
			continue;
		asc_startcmd(asc, i);
		break;
	}

	/* signal device driver that the command is done */
	(*scsicmd->sd->sd_driver->d_done)(scsicmd->unit, state->error,
		state->buflen, state->statusByte);

	return (0);
}

/* ARGSUSED */
static int
asc_dma_in(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
D 3
	register int len, fifo;
E 3
I 3
	register int len;
E 3

	/* check for previous chunk in buffer */
D 3
	if (!(state->flags & FIRST_DMA)) {
E 3
I 3
	if (state->flags & DMA_IN_PROGRESS) {
E 3
		/*
		 * Only count bytes that have been copied to memory.
		 * There may be some bytes in the FIFO if synchonous transfers
		 * are in progress.
		 */
I 8
		(*asc->dma_end)(asc, state, ASCDMA_READ);
E 8
		ASC_TC_GET(regs, len);
		len = state->dmalen - len;
		bcopy(state->dmaBufAddr, state->buf, len);
		state->buf += len;
		state->buflen -= len;
D 3
	} else
		state->flags &= ~FIRST_DMA;
E 3
I 3
	}
E 3

D 2
	/* setup to start reading next chunk */
E 2
I 2
	/* setup to start reading the next chunk */
E 2
	len = state->buflen;
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
	if (len > state->dmaBufSize)
		len = state->dmaBufSize;
	state->dmalen = len;
D 8
	*asc->dmar = ASC_DMA_ADDR(state->dmaBufAddr);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr, ASCDMA_READ);
E 8
	ASC_TC_PUT(regs, len);
I 2
#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_dma_in: buflen %d, len %d\n", state->buflen, len);
#endif

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
E 2
	if (len != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
D 2
		asc->script = &asc_scripts[SCRIPT_RESUME_IN];
E 2
I 2
		asc->script = &asc_scripts[SCRIPT_CONTINUE_IN];
E 2
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
asc_last_dma_in(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len, fifo;

	/* copy data from buffer to main memory */
I 8
	(*asc->dma_end)(asc, state, ASCDMA_READ);
E 8
	ASC_TC_GET(regs, len);
	fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
#ifdef DEBUG
I 2
D 3
#if 0
E 3
	if (asc_debug > 2)
D 3
#else
E 2
	if (asc_debug > 2 || len || fifo) /* XXX */
I 2
#endif
E 3
E 2
		printf("asc_last_dma_in: buflen %d dmalen %d tc %d fifo %d\n",
			state->buflen, state->dmalen, len, fifo);
#endif
	if (fifo) {
I 2
		/* device must be trying to send more than we expect */
E 2
		regs->asc_cmd = ASC_CMD_FLUSH;
I 8
		readback(regs->asc_cmd);
E 8
D 10
		MachEmptyWriteBuffer();
E 10
	}
I 3
	state->flags &= ~DMA_IN_PROGRESS;
E 3
	len = state->dmalen - len;
	state->buflen -= len;
	bcopy(state->dmaBufAddr, state->buf, len);

	return (1);
}

/* ARGSUSED */
static int
I 2
asc_resume_in(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len;

	/* setup to start reading the next chunk */
	len = state->buflen;
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
	if (len > state->dmaBufSize)
		len = state->dmaBufSize;
	state->dmalen = len;
D 8
	*asc->dmar = ASC_DMA_ADDR(state->dmaBufAddr);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr, ASCDMA_READ);
E 8
	ASC_TC_PUT(regs, len);
#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_resume_in: buflen %d, len %d\n", state->buflen,
			len);
#endif

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
	if (len != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
		asc->script = &asc_scripts[SCRIPT_CONTINUE_IN];
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
E 2
asc_resume_dma_in(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len, off;

	/* setup to finish reading the current chunk */
	len = state->dmaresid;
	off = state->dmalen - len;
	if ((off & 1) && state->sync_offset) {
		printf("asc_resume_dma_in: odd xfer dmalen %d len %d off %d\n",
			state->dmalen, len, off); /* XXX */
		regs->asc_res_fifo = state->dmaBufAddr[off];
	}
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
D 8
	*asc->dmar = ASC_DMA_ADDR(state->dmaBufAddr + off);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr + off, ASCDMA_READ);
E 8
	ASC_TC_PUT(regs, len);
I 2
#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_resume_dma_in: buflen %d dmalen %d len %d off %d\n",
			state->dmalen, state->buflen, len, off);
#endif

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
E 2
	if (state->dmalen != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
D 2
		asc->script = &asc_scripts[SCRIPT_RESUME_IN];
E 2
I 2
		asc->script = &asc_scripts[SCRIPT_CONTINUE_IN];
E 2
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
asc_dma_out(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len, fifo;

D 3
	if (!(state->flags & FIRST_DMA)) {
E 3
I 3
	if (state->flags & DMA_IN_PROGRESS) {
E 3
		/* check to be sure previous chunk was finished */
		ASC_TC_GET(regs, len);
		fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
		if (len || fifo)
			printf("asc_dma_out: buflen %d dmalen %d tc %d fifo %d\n",
				state->buflen, state->dmalen, len, fifo); /* XXX */
		len += fifo;
		len = state->dmalen - len;
D 3
		state->buflen -= len;
E 3
		state->buf += len;
I 3
		state->buflen -= len;
	}
E 3

D 3
		/* setup for this chunck */
		len = state->buflen;
		if (len > state->dmaBufSize)
			len = state->dmaBufSize;
		state->dmalen = len;
		bcopy(state->buf, state->dmaBufAddr, len);
		*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(state->dmaBufAddr);
	} else
		state->flags &= ~FIRST_DMA;

I 2
	len = state->dmalen;
E 3
I 3
D 12
	/* setup for this chunck */
E 12
I 12
	/* setup for this chunk */
E 12
	len = state->buflen;
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
	if (len > state->dmaBufSize)
		len = state->dmaBufSize;
	state->dmalen = len;
	bcopy(state->buf, state->dmaBufAddr, len);
D 8
	*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(state->dmaBufAddr);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr, ASCDMA_WRITE);
E 8
E 3
	ASC_TC_PUT(regs, len);
E 2
#ifdef DEBUG
	if (asc_debug > 2)
D 2
		printf("asc_dma_out: dmalen %d fifo %d\n",
			state->dmalen,
			regs->asc_flags & ASC_FLAGS_FIFO_CNT);
E 2
I 2
		printf("asc_dma_out: buflen %d, len %d\n", state->buflen, len);
E 2
#endif
D 2
	len = state->dmalen;
	ASC_TC_PUT(regs, len);
E 2

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
	if (len != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
D 2
		asc->script = &asc_scripts[SCRIPT_RESUME_OUT];
E 2
I 2
		asc->script = &asc_scripts[SCRIPT_CONTINUE_OUT];
E 2
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
asc_last_dma_out(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len, fifo;

D 2
	len = state->dmalen;
E 2
	ASC_TC_GET(regs, len);
	fifo = regs->asc_flags & ASC_FLAGS_FIFO_CNT;
D 2

E 2
#ifdef DEBUG
I 2
D 3
#if 0
E 3
E 2
	if (asc_debug > 2)
D 2
		printf("asc_last_dma_out: dmalen %d tc %d fifo %d\n",
			state->dmalen, len, fifo);
E 2
I 2
D 3
#else
	if (asc_debug > 2 || len || fifo) /* XXX */
E 2
#endif
E 3
D 2

	if (len || fifo)
E 2
		printf("asc_last_dma_out: buflen %d dmalen %d tc %d fifo %d\n",
D 3
			state->buflen, state->dmalen, len, fifo); /* XXX */
E 3
I 3
			state->buflen, state->dmalen, len, fifo);
E 3
D 2
	len += fifo;
E 2
I 2
#endif
	if (fifo) {
		len += fifo;
		regs->asc_cmd = ASC_CMD_FLUSH;
I 8
		readback(regs->asc_cmd);
I 12
		printf("asc_last_dma_out: buflen %d dmalen %d tc %d fifo %d\n",
			state->buflen, state->dmalen, len, fifo);
E 12
E 8
D 10
		MachEmptyWriteBuffer();
E 10
	}
I 3
	state->flags &= ~DMA_IN_PROGRESS;
E 3
E 2
	len = state->dmalen - len;
	state->buflen -= len;
	return (1);
}

/* ARGSUSED */
static int
I 2
asc_resume_out(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len;

D 12
	/* setup for this chunck */
E 12
I 12
	/* setup for this chunk */
E 12
	len = state->buflen;
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
	if (len > state->dmaBufSize)
		len = state->dmaBufSize;
	state->dmalen = len;
	bcopy(state->buf, state->dmaBufAddr, len);
D 8
	*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(state->dmaBufAddr);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr, ASCDMA_WRITE);
E 8
	ASC_TC_PUT(regs, len);
#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_resume_out: buflen %d, len %d\n", state->buflen,
			len);
#endif

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
	if (len != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
		asc->script = &asc_scripts[SCRIPT_CONTINUE_OUT];
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
E 2
asc_resume_dma_out(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int len, off;

	/* setup to finish writing this chunk */
	len = state->dmaresid;
	off = state->dmalen - len;
	if (off & 1) {
		printf("asc_resume_dma_out: odd xfer dmalen %d len %d off %d\n",
			state->dmalen, len, off); /* XXX */
		regs->asc_fifo = state->dmaBufAddr[off];
		off++;
		len--;
	}
I 16
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].resid = len;
	else
		asc_logp[-1].resid = len;
#endif
E 16
D 8
	*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(state->dmaBufAddr + off);
E 8
I 8
	(*asc->dma_start)(asc, state, state->dmaBufAddr + off, ASCDMA_WRITE);
E 8
	ASC_TC_PUT(regs, len);
I 2
#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_resume_dma_out: buflen %d dmalen %d len %d off %d\n",
			state->dmalen, state->buflen, len, off);
#endif

	/* check for next chunk */
I 3
	state->flags |= DMA_IN_PROGRESS;
E 3
E 2
	if (state->dmalen != state->buflen) {
		regs->asc_cmd = ASC_CMD_XFER_INFO | ASC_CMD_DMA;
I 8
		readback(regs->asc_cmd);
E 8
D 2
		asc->script = &asc_scripts[SCRIPT_RESUME_OUT];
E 2
I 2
		asc->script = &asc_scripts[SCRIPT_CONTINUE_OUT];
E 2
		return (0);
	}
	return (1);
}

/* ARGSUSED */
static int
asc_sendsync(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
I 3
	register State *state = &asc->st[asc->target];
E 3

D 3
	/*
	 * Phase is MSG_OUT here.
	 * Try sync negotiation, unless prohibited
	 */
E 3
I 3
	/* send the extended synchronous negotiation message */
E 3
	regs->asc_fifo = SCSI_EXTENDED_MSG;
	MachEmptyWriteBuffer();
	regs->asc_fifo = 3;
	MachEmptyWriteBuffer();
	regs->asc_fifo = SCSI_SYNCHRONOUS_XFER;
	MachEmptyWriteBuffer();
	regs->asc_fifo = SCSI_MIN_PERIOD;
	MachEmptyWriteBuffer();
	regs->asc_fifo = ASC_MAX_OFFSET;
I 3
	/* state to resume after we see the sync reply message */
	state->script = asc->script + 2;
	state->msglen = 0;
E 3
	return (1);
}

/* ARGSUSED */
static int
asc_replysync(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];

#ifdef DEBUG
	if (asc_debug > 2)
		printf("asc_replysync: %x %x\n",
D 8
			asc_to_scsi_period[state->sync_period],
E 8
I 8
			asc_to_scsi_period[state->sync_period] * asc->tb_ticks,
E 8
			state->sync_offset);
#endif
	/* send synchronous transfer in response to a request */
	regs->asc_fifo = SCSI_EXTENDED_MSG;
	MachEmptyWriteBuffer();
	regs->asc_fifo = 3;
	MachEmptyWriteBuffer();
	regs->asc_fifo = SCSI_SYNCHRONOUS_XFER;
	MachEmptyWriteBuffer();
D 8
	regs->asc_fifo = asc_to_scsi_period[state->sync_period];
E 8
I 8
	regs->asc_fifo = asc_to_scsi_period[state->sync_period] * asc->tb_ticks;
E 8
	MachEmptyWriteBuffer();
	regs->asc_fifo = state->sync_offset;
	regs->asc_cmd = ASC_CMD_XFER_INFO;
I 8
	readback(regs->asc_cmd);
E 8

	/* return to the appropriate script */
	if (!state->script) {
#ifdef DEBUG
		asc_DumpLog("asc_replsync");
#endif
		panic("asc_replysync");
	}
	asc->script = state->script;
	state->script = (script_t *)0;
	return (0);
}

/* ARGSUSED */
static int
D 2
asc_recvmsg(asc, status, ss, ir)
E 2
I 2
asc_msg_in(asc, status, ss, ir)
E 2
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register asc_regmap_t *regs = asc->regs;
	register State *state = &asc->st[asc->target];
	register int msg;
	int i;

	/* read one message byte */
	msg = regs->asc_fifo;
#ifdef DEBUG
	if (asc_logp == asc_log)
		asc_log[NLOG - 1].msg = msg;
	else
		asc_logp[-1].msg = msg;
#endif

	/* check for multi-byte message */
	if (state->msglen != 0) {
		/* first byte is the message length */
		if (state->msglen < 0) {
			state->msglen = msg;
			return (1);
		}
		if (state->msgcnt >= state->msglen)
			goto abort;
		state->msg_in[state->msgcnt++] = msg;

		/* did we just read the last byte of the message? */
		if (state->msgcnt != state->msglen)
			return (1);

		/* process an extended message */
#ifdef DEBUG
		if (asc_debug > 2)
D 2
			printf("asc_recvmsg: msg %x %x %x\n",
E 2
I 2
			printf("asc_msg_in: msg %x %x %x\n",
E 2
				state->msg_in[0],
				state->msg_in[1],
				state->msg_in[2]);
#endif
		switch (state->msg_in[0]) {
		case SCSI_SYNCHRONOUS_XFER:
			state->flags |= DID_SYNC;
			state->sync_offset = state->msg_in[2];

			/* convert SCSI period to ASC period */
D 8
			i = state->msg_in[1] / 10;
			if (i < ASC_MIN_PERIOD)
				i = ASC_MIN_PERIOD;
			else if (i >= ASC_MAX_PERIOD) {
E 8
I 8
			i = state->msg_in[1] / asc->tb_ticks;
			if (i < asc->min_period)
				i = asc->min_period;
			else if (i >= asc->max_period) {
E 8
				/* can't do sync transfer, period too long */
				printf("asc%d: SCSI device %d: sync xfer period too long (%d)\n",
					asc - asc_softc, asc->target, i);
D 8
				i = ASC_MAX_PERIOD;
E 8
I 8
				i = asc->max_period;
E 8
				state->sync_offset = 0;
			}
D 8
			if ((i * 10) != state->msg_in[1])
E 8
I 8
			if ((i * asc->tb_ticks) != state->msg_in[1])
E 8
				i++;
			state->sync_period = i & 0x1F;

			/*
			 * If this is a request, check minimums and
			 * send back an acknowledge.
			 */
			if (!(state->flags & TRY_SYNC)) {
				regs->asc_cmd = ASC_CMD_SET_ATN;
I 8
				readback(regs->asc_cmd);
E 8
D 10
				MachEmptyWriteBuffer();
E 10

D 8
				if (state->sync_period < ASC_MIN_PERIOD)
E 8
I 8
				if (state->sync_period < asc->min_period)
E 8
					state->sync_period =
D 8
						ASC_MIN_PERIOD;
E 8
I 8
						asc->min_period;
E 8
				if (state->sync_offset > ASC_MAX_OFFSET)
					state->sync_offset =
						ASC_MAX_OFFSET;
				asc->script = &asc_scripts[SCRIPT_REPLY_SYNC];
				regs->asc_syn_p = state->sync_period;
I 8
				readback(regs->asc_syn_p);
E 8
				regs->asc_syn_o = state->sync_offset;
I 8
				readback(regs->asc_syn_o);
E 8
				regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
				readback(regs->asc_cmd);
E 8
				return (0);
			}

			regs->asc_syn_p = state->sync_period;
I 8
			readback(regs->asc_syn_p);
E 8
			regs->asc_syn_o = state->sync_offset;
I 8
			readback(regs->asc_syn_o);
E 8
			goto done;

		default:
			printf("asc%d: SCSI device %d: rejecting extended message 0x%x\n",
				asc - asc_softc, asc->target,
				state->msg_in[0]);
			goto reject;
		}
	}

	/* process first byte of a message */
#ifdef DEBUG
	if (asc_debug > 2)
D 2
		printf("asc_recvmsg: msg %x\n", msg);
E 2
I 2
		printf("asc_msg_in: msg %x\n", msg);
E 2
#endif
	switch (msg) {
#if 0
	case SCSI_MESSAGE_REJECT:
		printf(" did not like SYNCH xfer "); /* XXX */
		state->flags |= DID_SYNC;
		regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
		readback(regs->asc_cmd);
E 8
		status = asc_wait(regs, ASC_CSR_INT);
		ir = regs->asc_intr;
		/* some just break out here, some dont */
		if (ASC_PHASE(status) == ASC_PHASE_MSG_OUT) {
			regs->asc_fifo = SCSI_ABORT;
			regs->asc_cmd = ASC_CMD_XFER_INFO;
I 8
			readback(regs->asc_cmd);
E 8
			status = asc_wait(regs, ASC_CSR_INT);
			ir = regs->asc_intr;
		}
		if (ir & ASC_INT_DISC) {
			asc_end(asc, status, 0, ir);
			return (0);
		}
		goto status;
#endif

	case SCSI_EXTENDED_MSG: /* read an extended message */
		/* setup to read message length next */
		state->msglen = -1;
		state->msgcnt = 0;
		return (1);

	case SCSI_NO_OP:
		break;

	case SCSI_SAVE_DATA_POINTER:
		/* expect another message */
		return (1);

	case SCSI_RESTORE_POINTERS:
		/*
		 * Need to do the following if resuming synchonous data in
		 * on an odd byte boundary.
		regs->asc_cnfg2 |= ASC_CNFG2_RFB;
		 */
		break;

	case SCSI_DISCONNECT:
		if (state->flags & DISCONN)
			goto abort;
		state->flags |= DISCONN;
D 2
		break;
E 2
I 2
		regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
		readback(regs->asc_cmd);
E 8
		asc->script = &asc_scripts[SCRIPT_DISCONNECT];
		return (0);
E 2

	default:
		printf("asc%d: SCSI device %d: rejecting message 0x%x\n",
			asc - asc_softc, asc->target, msg);
	reject:
		/* request a message out before acknowledging this message */
		state->msg_out = SCSI_MESSAGE_REJECT;
		regs->asc_cmd = ASC_CMD_SET_ATN;
I 8
		readback(regs->asc_cmd);
E 8
D 10
		MachEmptyWriteBuffer();
E 10
	}

done:
	/* return to original script */
	regs->asc_cmd = ASC_CMD_MSG_ACPT;
I 8
	readback(regs->asc_cmd);
E 8
	if (!state->script) {
	abort:
#ifdef DEBUG
D 2
		asc_DumpLog("asc_recvmsg");
E 2
I 2
		asc_DumpLog("asc_msg_in");
E 2
#endif
D 2
		panic("asc_recvmsg");
E 2
I 2
		panic("asc_msg_in");
E 2
	}
	asc->script = state->script;
	state->script = (script_t *)0;
	return (0);
I 2
}

/* ARGSUSED */
static int
asc_disconnect(asc, status, ss, ir)
	register asc_softc_t asc;
	register int status, ss, ir;
{
	register State *state = &asc->st[asc->target];

I 11
#ifdef DIAGNOSTIC
	if (!(state->flags & DISCONN)) {
		printf("asc_disconnect: device %d: DISCONN not set!\n",
			asc->target);
	}
#endif
E 11
	asc->target = -1;
	asc->state = ASC_STATE_RESEL;
	return (1);
I 8
}

/*
D 12
 * DMA handling routines. For a turbochannel device, just set the dmar
 * for the I/O ASIC, handle the actual DMA interface.
E 12
I 12
 * DMA handling routines. For a turbochannel device, just set the dmar.
 * For the I/O ASIC, handle the actual DMA interface.
E 12
 */
static void
tb_dma_start(asc, state, cp, flag)
	asc_softc_t asc;
	State *state;
	caddr_t cp;
	int flag;
{

	if (flag == ASCDMA_WRITE)
		*asc->dmar = ASC_DMAR_WRITE | ASC_DMA_ADDR(cp);
	else
		*asc->dmar = ASC_DMA_ADDR(cp);
}

static void
tb_dma_end(asc, state, flag)
	asc_softc_t asc;
	State *state;
	int flag;
{

}

static void
asic_dma_start(asc, state, cp, flag)
	asc_softc_t asc;
	State *state;
	caddr_t cp;
	int flag;
{
	register volatile u_int *ssr = (volatile u_int *)
D 9
		MACH_PHYS_TO_UNCACHED(KMIN_REG_CSR);
E 9
I 9
		ASIC_REG_CSR(asic_base);
E 9
	u_int phys, nphys;

	/* stop DMA engine first */
	*ssr &= ~ASIC_CSR_DMAEN_SCSI;
D 9
	* ((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_SCR)) = 0;
E 9
I 9
D 11
	* ((volatile int *)ASIC_REG_SCSI_SCR(asic_base)) = 0;
E 11
I 11
	*((volatile int *)ASIC_REG_SCSI_SCR(asic_base)) = 0;
E 11
E 9

	phys = MACH_CACHED_TO_PHYS(cp);
	cp = (caddr_t)pmax_trunc_page(cp + NBPG);
	nphys = MACH_CACHED_TO_PHYS(cp);

	asc->dma_next = cp;
	asc->dma_xfer = state->dmalen - (nphys - phys);

D 9
	*(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMAPTR) =
E 9
I 9
	*(volatile int *)ASIC_REG_SCSI_DMAPTR(asic_base) =
E 9
		ASIC_DMA_ADDR(phys);
D 9
	*(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMANPTR) =
E 9
I 9
	*(volatile int *)ASIC_REG_SCSI_DMANPTR(asic_base) =
E 9
		ASIC_DMA_ADDR(nphys);
	if (flag == ASCDMA_READ)
		*ssr |= ASIC_CSR_SCSI_DIR | ASIC_CSR_DMAEN_SCSI;
	else
		*ssr = (*ssr & ~ASIC_CSR_SCSI_DIR) | ASIC_CSR_DMAEN_SCSI;
	MachEmptyWriteBuffer();
}

static void
asic_dma_end(asc, state, flag)
	asc_softc_t asc;
	State *state;
	int flag;
{
	register volatile u_int *ssr = (volatile u_int *)
D 9
		MACH_PHYS_TO_UNCACHED(KMIN_REG_CSR);
E 9
I 9
		ASIC_REG_CSR(asic_base);
I 13
	register volatile u_int *dmap = (volatile u_int *)
		ASIC_REG_SCSI_DMAPTR(asic_base);
	register u_short *to;
	register int w;
E 13
E 9
	int nb;

	*ssr &= ~ASIC_CSR_DMAEN_SCSI;
D 9
	*((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMAPTR)) = -1;
	*((volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMANPTR)) = -1;
E 9
I 9
D 13
	*((volatile int *)ASIC_REG_SCSI_DMAPTR(asic_base)) = -1;
E 13
I 13
	to = (u_short *)MACH_PHYS_TO_CACHED(*dmap >> 3);
	*dmap = -1;
E 13
	*((volatile int *)ASIC_REG_SCSI_DMANPTR(asic_base)) = -1;
E 9
	MachEmptyWriteBuffer();

	if (flag == ASCDMA_READ) {
		MachFlushDCache(MACH_PHYS_TO_CACHED(
		    MACH_UNCACHED_TO_PHYS(state->dmaBufAddr)), state->dmalen);
D 9
		if (nb = *((int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_SCR))) {
E 9
I 9
		if (nb = *((int *)ASIC_REG_SCSI_SCR(asic_base))) {
E 9
			/* pick up last upto6 bytes, sigh. */
D 13
			register u_short *to;
			register int w;
E 13
	
			/* Last byte really xferred is.. */
D 13
			to = (u_short *)(state->dmaBufAddr + state->dmalen - (nb << 1));
E 13
D 9
			w = *(int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_SDR0);
E 9
I 9
			w = *(int *)ASIC_REG_SCSI_SDR0(asic_base);
E 9
			*to++ = w;
			if (--nb > 0) {
				w >>= 16;
				*to++ = w;
			}
			if (--nb > 0) {
D 9
				w = *(int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_SDR1);
E 9
I 9
				w = *(int *)ASIC_REG_SCSI_SDR1(asic_base);
E 9
				*to++ = w;
			}
		}
	}
}

I 9
#ifdef notdef
E 9
/*
 * Called by asic_intr() for scsi dma pointer update interrupts.
 */
void
asc_dma_intr()
{
	asc_softc_t asc = &asc_softc[0];
	u_int next_phys;

	asc->dma_xfer -= NBPG;
	if (asc->dma_xfer <= -NBPG) {
		volatile u_int *ssr = (volatile u_int *)
D 9
			MACH_PHYS_TO_UNCACHED(KMIN_REG_CSR);
E 9
I 9
			ASIC_REG_CSR(asic_base);
E 9
		*ssr &= ~ASIC_CSR_DMAEN_SCSI;
	} else {
		asc->dma_next += NBPG;
		next_phys = MACH_CACHED_TO_PHYS(asc->dma_next);
	}
D 9
#ifdef notdef
	else
		next_phys = MACH_CACHED_TO_PHYS(asc_iobuf);
#endif
	*(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DMANPTR) =
E 9
I 9
	*(volatile int *)ASIC_REG_SCSI_DMANPTR(asic_base) =
E 9
		ASIC_DMA_ADDR(next_phys);
	MachEmptyWriteBuffer();
E 8
E 2
}
I 9
#endif
E 9

#ifdef DEBUG
asc_DumpLog(str)
	char *str;
{
	register struct asc_log *lp;
	register u_int status;

	printf("asc: %s: cmd %x bn %d cnt %d\n", str, asc_debug_cmd,
		asc_debug_bn, asc_debug_sz);
D 10
	lp = asc_logp + 1;
	if (lp > &asc_log[NLOG])
		lp = asc_log;
	while (lp != asc_logp) {
E 10
I 10
	lp = asc_logp;
	do {
E 10
		status = lp->status;
D 11
		printf("asc%d tgt %d status %x ss %x ir %x cond %d:%x msg %x\n",
E 11
I 11
		printf("asc%d tgt %d status %x ss %x ir %x cond %d:%x msg %x resid %d\n",
E 11
			status >> 24,
			lp->target,
			(status >> 16) & 0xFF,
			(status >> 8) & 0xFF,
			status & 0XFF,
			lp->state,
			asc_scripts[lp->state].condition,
D 11
			lp->msg);
E 11
I 11
			lp->msg, lp->resid);
E 11
		if (++lp >= &asc_log[NLOG])
			lp = asc_log;
D 10
	}
E 10
I 10
	} while (lp != asc_logp);
E 10
}
#endif

#endif	/* NASC > 0 */
E 1
