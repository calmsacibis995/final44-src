/* 
 * Mach Operating System
 * Copyright (c) 1994,1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
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
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	clockstat.h,v $
 * Revision 2.2  94/12/15  15:31:40  dbg
 * 	Added to mainline kernel.
 * 	[94/12/07            dbg]
 * 
 * 	Created from the Alpha Logic manual:
 * 	"STAT! System Timing Analysis Tool User Guide"
 * 	Ref. 62-0010001A  12/91  
 * 	Alpha Logic Technolgies, Inc.
 * 	Redmond, WA
 * 	[93/03/21            savage]
 * 
 */

#ifndef _I386AT_CLOCK_STAT_H_
#define _I386AT_CLOCK_STAT_H_

/*
 *	Description of the STAT! System Timing Analysis Tool
 */

#define CLOCKSTAT_DEFAULT_RESOLUTION	(1000)

#define STAT_DATA_PORT(addr)		(addr)
#define STAT_CONTROL_PORT(addr)		(addr+2)
#define STAT_INTERRUPT_PORT(addr)	(addr+3)

/*
 *	Timer flags
 */
#define TF1		0x01
#define TF2		0x02
#define TF3		0x04
#define TF4		0x08
#define TF5		0x10
#define TFALL		0x1f

/*
 *	Timer group numbers
 */
#define TG1		0x01
#define TG2		0x02
#define TG3		0x03
#define TG4		0x04
#define TG5		0x05


/*
 *	Command Register (write only)
 */
#define STAT_CMD_RESET		0xff	/* Master reset */
#define STAT_CMD_INITPTR	0xe8	/* Init data pointer */

#define STAT_CMD_LOADPTR_MODE		0x00	/* combined with TG */
#define STAT_CMD_LOADPTR_LOAD		0x08	/* combined with TG */
#define STAT_CMD_LOADPTR_HOLD		0x10	/* combined with TG */
#define STAT_CMD_LOADPTR_MASTER		0x17	
#define STAT_CMD_LOADPTR_ALARMT2	0x0f	
#define STAT_CMD_LOADPTR_ALARMT1	0x07	

#define STAT_CMD_LOADTIMERS		0x40	/* combined with TF */
#define STAT_CMD_SAVETIMERS		0xa0	/* combined with TF */
#define STAT_CMD_ARMTIMERS		0x20	/* combined with TF */
#define STAT_CMD_DISARMTIMERS		0xc0	/* combined with TF */

#define STAT_CMD_STEPTIMER		0xf0	/* combined with TG */
#define STAT_CMD_SETOUTPUT		0xe8	/* combined with TG */
#define STAT_CMD_CLEAROUTPUT		0xe0	/* combined with TG */

/*
 *	Status register (read only)
 *      Bits in TF positions report output conditions of respective timer
 *	TF1 & TF2 will show output state of Alarm Comparator if enabled
 */

/*
 *	Interrupt Register
 */
#define STAT_INT_NMI		0x80	/* board generated NMI */
#define STAT_INT_NMI_ENABLE	0x00	
#define STAT_INT_NMI_DISABLE	0x80	

#define STAT_INT_INT		0x40	/* board generated interrupt */
#define STAT_INT_INT_ENABLE	0x40
#define STAT_INT_INT_DISABLE	0x00

#define STAT_INT_STATSWTCH	0x20	/* status of switch (read-only) */
#define STAT_INT_STATINT	0x10	/* status of int (read-only) */

   					/* Interrupt sources */
#define STAT_INT_SRCSOFT	0x07	/* from software */
#define STAT_INT_SRCSWTCH	0x06	/* switch */
					/* From TG1-5 */
#define STAT_INT_SRCNONE	0x00	/* none... off */


/* 
 *	Master Mode Register
 */
#define STAT_MSTR_SCALE		0x8000
#define STAT_MSTR_SCALE_BCD	0x8000
#define STAT_MSTR_SCALE_BIN	0x0000

#define STAT_MSTR_DPTR		0x4000
#define STAT_MSTR_DPTR_INIT	0x4000
#define STAT_MSTR_DPTR_UNINIT	0x0000

#define STAT_MSTR_F6		0x1000
#define STAT_MSTR_F6_ENABLE	0x0000	/* Marked incorrectly in the manual */
#define STAT_MSTR_F6_DISABLE	0x1000

#define STAT_MSTR_F6SCALE	0x0f00
#define STAT_MSTR_F6SCALE_16	0x0000
#define STAT_MSTR_F6SCALE_15	0x0f00
#define STAT_MSTR_F6SCALE_14	0x0e00
#define STAT_MSTR_F6SCALE_13	0x0d00
#define STAT_MSTR_F6SCALE_12	0x0c00
#define STAT_MSTR_F6SCALE_11	0x0b00
#define STAT_MSTR_F6SCALE_10	0x0a00
#define STAT_MSTR_F6SCALE_09	0x0900
#define STAT_MSTR_F6SCALE_08	0x0800
#define STAT_MSTR_F6SCALE_07	0x0700
#define STAT_MSTR_F6SCALE_06	0x0600
#define STAT_MSTR_F6SCALE_05	0x0500
#define STAT_MSTR_F6SCALE_04	0x0400
#define STAT_MSTR_F6SCALE_03	0x0300
#define STAT_MSTR_F6SCALE_02	0x0200
#define STAT_MSTR_F6SCALE_01	0x0100

#define STAT_MSTR_F6SOURCE	0x00f0
#define STAT_MSTR_F6SOURCE_F1D	0x0000
#define STAT_MSTR_F6SOURCE_F1	0x00b0
#define STAT_MSTR_F6SOURCE_F2	0x00c0
#define STAT_MSTR_F6SOURCE_F3	0x00d0
#define STAT_MSTR_F6SOURCE_F4	0x00e0
#define STAT_MSTR_F6SOURCE_F5	0x00f0

#define STAT_MSTR_ALRM2		0x0008
#define STAT_MSTR_ALRM2_ENABLE	0x0008
#define STAT_MSTR_ALRM2_DISABLE	0x0000

#define STAT_MSTR_ALRM1		0x0004
#define STAT_MSTR_ALRM1_ENABLE	0x0004
#define STAT_MSTR_ALRM1_DISABLE	0x0000


/* 
 *	Timer Mode Register
 */
#define STAT_TIMER_SOURCE	0x0f00
#define STAT_TIMER_SOURCE_F6	0x0100
#define STAT_TIMER_SOURCE_F5	0x0f00          
#define STAT_TIMER_SOURCE_F4	0x0e00          
#define STAT_TIMER_SOURCE_F3	0x0d00          
#define STAT_TIMER_SOURCE_F2	0x0c00          
#define STAT_TIMER_SOURCE_F1	0x0b00          
#define STAT_TIMER_SOURCE_T5	0x0a00          
#define STAT_TIMER_SOURCE_T4	0x0900          
#define STAT_TIMER_SOURCE_T3	0x0800          
#define STAT_TIMER_SOURCE_T2	0x0700          
#define STAT_TIMER_SOURCE_T1	0x0600          
#define STAT_TIMER_SOURCE_TNM1	0x0000          

#define STAT_TIMER_CYCLE	0x0020          
#define STAT_TIMER_CYCLE_REPEAT	0x0020          
#define STAT_TIMER_CYCLE_ONCE	0x0000          

#define STAT_TIMER_BASE		0x0010          
#define STAT_TIMER_BASE_BCD	0x0010          
#define STAT_TIMER_BASE_BIN	0x0000          

#define STAT_TIMER_DIR		0x0008          
#define STAT_TIMER_DIR_UP	0x0008          
#define STAT_TIMER_DIR_DOWN	0x0000          

#define STAT_TIMER_OUT		0x0007
#define STAT_TIMER_OUT_TOGGLE	0x0002
#define STAT_TIMER_OUT_PULSE	0x0001
#define STAT_TIMER_OUT_OFF	0x0000

#endif	/* _I386AT_CLOCK_STAT_H_ */
