h44768
s 00006/00005/00347
d D 7.1 91/05/09 20:18:13 bostic 6 5
c new copyright; att/bsd/shared
e
s 00000/00061/00352
d D 1.5 88/06/14 14:07:10 marc 5 4
c lint, code cleanup, make less yucky
e
s 00003/00005/00410
d D 1.4 88/06/03 17:54:15 marc 4 3
c tahoe release
e
s 00009/00004/00406
d D 1.3 88/05/27 19:56:28 marc 3 2
c add header
e
s 00002/00000/00408
d D 1.2 87/08/07 15:54:56 marc 2 1
c first 4.3 version
e
s 00408/00000/00000
d D 1.1 87/07/09 18:17:49 marc 1 0
c date and time created 87/07/09 18:17:49 by marc
e
u
U
t
T
I 1
D 3

E 3
D 6
/*
I 2
D 3
 *		%W%  Berkeley  %G%
E 2
 *	@(#)qdreg.h	1.5	(ULTRIX)	5/21/86
E 3
I 3
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 6
 *
D 6
 * 		%W%  Berkeley  %G%
E 6
I 6
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 6
D 4
 *
 *	derived from: qdreg.h	1.5	(ULTRIX)	5/21/86
E 4
E 3
 */
I 4
D 5
/* derived from: @(#)qdreg.h	6.1	(ULTRIX)	11/24/87       */
E 5
E 4

I 3
D 4

E 4
E 3
/************************************************************************
 *									*
 *			Copyright (c) 1985, 1986 by			*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

D 5
/*
 * qdreg.h
 *
D 3
 * Modification history
E 3
I 3
D 4
 * Modification history (belongs in sccs)
E 4
I 4
 * Modification history
E 4
E 3
 *
 * QDSS registers/data structures and definitions
 *
 *  4-Feb-85 - longo
 *
 *	Created file.
 *
 * 18-Mar-85 - longo
 *
 *	Added DGA CSR bit definitions.
 *
 * 20-Mar-85 - longo
 *
 *	Revised register naming conventions.
 *
 * 28-Mar-85 - longo
 *
 *	Added DUART register struct.
 *
 * 19-Apr-85 - longo
 *
 *	Removed "base" entry from 'struct qdmap'.
 *
 *  1-May-85 - longo
 *
 *	Changed layout of DUART device map data structure and
 *	added command/intrpt/status bit definitions.
 *
 *  4-Jun-85 - longo
 *
 *	Added bit definitions for ADDER registers.
 *
 * 10-Sep-85 - longo
 *
 *	Changed dga struct DMA address entry names.
 *
 * 25-Sep-85 - longo
 *
 *	Changed ADDER status bit constant.
 *
 * 20-May-86 - ricky palmer
 *
 *	Added new DEVIOCGET ioctl request code. V2.0
 *
 */
I 4
#define DEV_SIZE 8	/*XXX*/
E 4

E 5
/* Dragon ADDER reg map */
/* ADDER register bit definitions */
/* Y_SCROLL_CONSTANT */

#define SCROLL_ERASE		0x2000
#define ADDER_SCROLL_DOWN	0x1000

/* ADDER status and interrupt enable registers [1], [2], [3] */

#define DISABLE 		0x0000
#define PAUSE_COMPLETE		0x0001
#define FRAME_SYNC		0x0002
#define INIT_COMPLETE		0x0004
#define RASTEROP_COMPLETE	0x0008

#define ADDRESS_COMPLETE	0x0010
#define RX_READY		0x0020
#define TX_READY		0x0040
#define ID_SCROLL_READY 	0x0080

#define TOP_CLIP		0x0100
#define BOTTOM_CLIP		0x0200
#define LEFT_CLIP		0x0400
#define RIGHT_CLIP		0x0800
#define NO_CLIP 		0x1000
#define VSYNC			0x2000

/* ADDER command register [8], [10] */

#define OCR_zero		0x0000
#define Z_BLOCK0		0x0000
#define OCRA			0x0000
#define OCRB			0x0004
#define RASTEROP		0x02c0
#define PBT			0x03c0
#define BTPZ			0x0bb0
#define PTBZ			0x07a0
#define DTE			0x0400
#define S1E			0x0800
#define S2E			0x1000
#define VIPER_Z_LOAD		0x01A0
#define ID_LOAD 		0x0100
#define CANCEL			0x0000
#define LF_R1			0x0000
#define LF_R2			0x0010
#define LF_R3			0x0020
#define LF_R4			0x0030

/* ADDER rasterop mode register [9] */

#define NORMAL			0x0000
#define LINEAR_PATTERN		0x0002
#define X_FILL			0x0003
#define Y_FILL			0x0007
#define BASELINE		0x0008
#define HOLE_ENABLE		0x0010
#define SRC_1_INDEX_ENABLE	0x0020
#define DST_INDEX_ENABLE	0x0040
#define DST_WRITE_ENABLE	0x0080

/* ADDER source 2 size register */

#define NO_TILE 		0x0080

/* External registers base addresses */

#define CS_UPDATE_MASK		0x0060
#define CS_SCROLL_MASK		0x0040

/* VIPER registers */

#define RESOLUTION_MODE 	0x0080
#define MEMORY_BUS_WIDTH	0x0081
#define PLANE_ADDRESS		0x0083
#define LU_FUNCTION_R1		0x0084
#define LU_FUNCTION_R2		0x0085
#define LU_FUNCTION_R3		0x0086
#define LU_FUNCTION_R4		0x0087
#define MASK_1			0x0088
#define MASK_2			0x0089
#define SOURCE			0x008a
#define SOURCE_Z		0x0000
#define BACKGROUND_COLOR	0x008e
#define BACKGROUND_COLOR_Z	0x000C
#define FOREGROUND_COLOR	0x008f
#define FOREGROUND_COLOR_Z	0x0004
#define SRC1_OCR_A		0x0090
#define SRC2_OCR_A		0x0091
#define DST_OCR_A		0x0092
#define SRC1_OCR_B		0x0094
#define SRC2_OCR_B		0x0095
#define DST_OCR_B		0x0096

/* VIPER scroll registers */

#define SCROLL_CONSTANT 	0x0082
#define SCROLL_FILL		0x008b
#define SCROLL_FILL_Z		0x0008
#define LEFT_SCROLL_MASK	0x008c
#define RIGHT_SCROLL_MASK	0x008d

/* VIPER register bit definitions */

#define EXT_NONE		0x0000
#define EXT_SOURCE		0x0001
#define EXT_M1_M2		0x0002
#define INT_NONE		0x0000
#define INT_SOURCE		0x0004
#define INT_M1_M2		0x0008
#define ID			0x0010
#define NO_ID			0x0000
#define WAIT			0x0020
#define NO_WAIT 		0x0000
#define BAR_SHIFT_DELAY 	WAIT
#define NO_BAR_SHIFT_DELAY	NO_WAIT


/* VIPER logical function unit codes */

#define LF_ZEROS		0x0000
#define LF_D_XOR_S		0x0006
#define LF_SOURCE		0x000A
#define LF_D_OR_S		0x000E
#define LF_ONES 		0x000F
#define INV_M1_M2		0x0030
#define FULL_SRC_RESOLUTION	0X00C0 /* makes second pass like first pass */

/* VIPER scroll register [2] */

#define SCROLL_DISABLE		0x0040
#define SCROLL_ENABLE		0x0020
#define VIPER_LEFT		0x0000
#define VIPER_RIGHT		0x0010
#define VIPER_UP		0x0040
#define VIPER_DOWN		0x0000

/* Adder scroll register */

#define ADDER_UP		0x0000
#define ADDER_DOWN		0x1000

/* Misc scroll definitions */

#define UP		0
#define DOWN		1
#define LEFT		2
#define RIGHT		3
#define NODIR		4
#define SCROLL_VMAX	31
#define SCROLL_HMAX	15
#define NEW		2
#define OLD		1
#define BUSY		1
#define DRAG		1
#define SCROLL		0

/* miscellaneous defines */

#define ALL_PLANES	0xffffffff
#define UNITY		0x1fff		 /* Adder scale factor */
#define MAX_SCREEN_X	1024
#define MAX_SCREEN_Y	864
#define FONT_HEIGHT	32

	struct adder {

	    /* adder control registers */

	    u_short register_address;	/* ADDER reg pntr for use by DGA */
	    u_short request_enable;	/* DMA request enables */
	    u_short interrupt_enable;	/* interrupt enables */
	    u_short status;		/* ADDER status bits */
	    u_short reserved1;		/* test function only */
	    u_short spare1;		/* spare address (what else?) */

	    u_short reserved2;		/* test function only */
	    u_short id_data;		/* data path to I/D bus */
	    u_short command;		/* ADDER chip command register */
	    u_short rasterop_mode;	/* sets rasterop execution modes */
	    u_short cmd;		/* duplicate path to above cmd reg */
	    u_short reserved3;		/* test function only */

	    /* scroll registers */

	    u_short ID_scroll_data;	/* I/D bus scroll data */
	    u_short ID_scroll_command;	/* I/D bus scroll command */
	    u_short scroll_x_min;	/* X scroll min - left boundary */
	    u_short scroll_x_max;	/* X scroll max - right boundary */
	    u_short scroll_y_min;	/* Y scroll min - upper boundary */
	    u_short scroll_y_max;	/* Y scroll max - lower boundary */
	    u_short pause;		/* Y coord to set stat when scanned */
	    u_short y_offset_pending;	/* vertical scroll control */
	    u_short y_scroll_constant;

	    /* update control registers */

	    u_short x_index_pending;	/* x pending index */
	    u_short y_index_pending;	/* y pending index */
	    u_short x_index_new;	/* new x index */
	    u_short y_index_new;		/* new y index */
	    u_short x_index_old;		/* old x index */
	    u_short y_index_old;		/* old y index */
	    u_short x_clip_min; 	/* left clipping boundary */
	    u_short x_clip_max; 	/* right clipping boundary */
	    u_short y_clip_min; 	/* upper clipping boundary */
	    u_short y_clip_max; 	/* lower clipping boundary */
	    u_short spare2;		/* spare address (another!) */

	    /* rasterop control registers */

	    u_short source_1_dx;	/* source #1 x vector */
	    u_short source_1_dy;	/* source #1 y vector*/
	    u_short source_1_x; 	/* source #1 x origin */
	    u_short source_1_y; 	/* source #1 y origin */
	    u_short destination_x;	/* destination x origin */
	    u_short destination_y;	/* destination y origin */
	    u_short fast_dest_dx;	/* destination x fast vector */
	    u_short fast_dest_dy;	/* destination y fast vector */
	    u_short slow_dest_dx;	/* destination x slow vector */
	    u_short slow_dest_dy;	/* destination y slow vector */
	    u_short fast_scale; 	/* scale factor for fast vector */
	    u_short slow_scale; 	/* scale factor for slow vector */
	    u_short source_2_x; 	/* source #2 x origin */
	    u_short source_2_y; 	/* source #2 y origin */
	    u_short source_2_size;	/* source #2 height & width */
	    u_short error_1;		/* error regs (?) */
	    u_short error_2;

	    /* screen format control registers */

	    u_short y_scan_count_0;	/* y scan counts for vert timing */
	    u_short y_scan_count_1;
	    u_short y_scan_count_2;
	    u_short y_scan_count_3;
	    u_short x_scan_conf;	/* x scan configuration */
	    u_short x_limit;
	    u_short y_limit;
	    u_short x_scan_count_0;	/* x scan count for horiz timing */
	    u_short x_scan_count_1;
	    u_short x_scan_count_2;
	    u_short x_scan_count_3;
	    u_short x_scan_count_4;
	    u_short x_scan_count_5;
	    u_short x_scan_count_6;
	    u_short sync_phase_adj;	/* sync phase (horiz sync count) */
	};

/*---------------------
* DUART definitions */

	/* command definitions */

#define EN_RCV		0x01
#define DIS_RCV 	0x02
#define EN_XMT		0x04
#define DIS_XMT 	0x08
#define RESET_M 	0x10
#define RESET_RCV	0x20
#define RESET_XMT	0x30
#define RESET_ERR	0x40
#define RESET_BD	0x50
#define START_BREAK	0x60
#define STOP_BREAK	0x70

	/* interupt bit definitions */

#define EI_XMT_A	0x01
#define EI_RCV_A	0x02
#define EI_XMT_B	0x10
#define EI_RCV_B	0x20

#define XMT_RDY_A	0x01
#define RCV_RDY_A	0x02
#define XMT_RDY_B	0x10
#define RCV_RDY_B	0x20

	/* status register bit defintions */

#define RCV_RDY 	0x01
#define FIFO_FULL	0x02
#define XMT_RDY 	0x04
#define XMT_EMT 	0x08
#define OVER_ERR	0x10
#define ERR_PARITY	0x20
#define FRAME_ERR	0x40
#define RCVD_BREAK	0x80


	struct duart {

	    /* channel A - LK201 */

	    short modeA;		/* ch.A mode reg (read/write) */
	    short statusA;		/* ch.A status reg (read) */
#define clkselA statusA 		/* ch.A clock slect reg (write) */
	    short cmdA; 		/* ch.A command reg (write) */
	    short dataA;		/* rcv/xmt data ch.A (read/write) */
	    short inchng;		/* input change state reg (read) */
#define auxctl inchng			/* auxiliary control reg (write) */
	    short istatus;		/* interrupt status reg (read) */
#define imask istatus			/* interrupt mask reg (write) */
	    short CThi; 		/* counter/timer hi byte (read) */
#define CTRhi CThi			/* counter/timer hi reg (write) */
	    short CTlo; 		/* counter/timer lo byte (read) */
#define CTRlo CTlo			/* counter/timer lo reg (write) */

	    /* channel B - pointing device */

	    short modeB;		/* ch.B mode reg (read/write) */
	    short statusB;		/* ch.B status reg (read) */
#define clkselB statusB 		/* ch.B clock select reg (write) */
	    short cmdB; 		/* ch.B command reg (write) */
	    short dataB;		/* ch.B rcv/xmt data (read/write) */
	    short rsrvd;
	    short inport;		/* input port (read) */
#define outconf inport			/* output port config reg (write) */
	    short strctr;		/* start counter command (read) */
#define setbits setctr			/* output bits set command (write) */
	    short stpctr;		/* stop counter command (read) */
#define resetbits stpctr		/* output bits reset cmd (write) */

D 5
	};

/* Driver and data specific structure */
I 2
D 4
#define DEV_SIZE 8  /* from ultrix - i don't see where its used ! - marc */
E 4
E 2
struct	qd_softc {
	long	sc_flags;		/* Flags			*/
	long	sc_category_flags;	/* Category flags		*/
	u_long	sc_softcnt;		/* Soft error count total	*/
	u_long	sc_hardcnt;		/* Hard error count total	*/
	char	sc_device[DEV_SIZE];	/* Device type string		*/
E 5
};
E 1
