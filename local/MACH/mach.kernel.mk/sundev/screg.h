/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	screg.h,v $
 * Revision 2.5  89/07/11  17:28:44  jjc
 * 	Commented out definition of dma_addr as a long in 
 * 	struct scsi_ha_reg.
 * 	[88/09/04            jjc]
 * 
 * Revision 2.4  89/03/09  21:44:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:54:02  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.2  88/12/07  17:20:18  mikeg
 * 	Entered new version of this file from SunOS 3.5 to support
 * 	new "sc.c" driver.
 * 	[88/12/01  14:05:04  mikeg]
 * 
 */
/* @(#)screg.h 1.1 87/12/21	Copyr 1987 Sun Micro	*/

#define HOST_ADDR	0x00	/* 0x80 is right but Sysgen violates spec */

#define SC_RESET_DELAY		4000000	/*  1 us  ( 4  Sec.) */
#define SC_LONG_WAIT		3000000	/* 10 us  (30  Sec.) */
#define SC_WAIT_COUNT		400000	/* 10 us  ( 4  Sec.) */
#define SC_SHORT_WAIT		25000	/* 10 us  (.25 Sec.) */


#if	defined(sun2)  ||  defined(sun3)
/* 
 * SCSI Sun host adapter control registers for Sun-2 and Sun-3.
 */
#define SET_DMA_ADDR(har,val)	(har)->dma_addr = val;
#define GET_DMA_ADDR(har)	(har)->dma_addr;

struct	scsi_ha_reg {		/* host adapter (I/O space) registers */
	u_char	data;		/* data register */
	u_char	unused;
	u_char	cmd_stat;	/* command/status register */
	u_char	unused2;
	u_short	icr;		/* interface control register */
	u_short	unused3;
	u_long	dma_addr;	/* dma base address */
	u_short	dma_count;	/* dma count register */
	u_char	unused4;
	u_char	intvec;		/* interrupt vector for VMEbus versions */
};
#endif	defined(sun2)  ||  defined(sun3)


#ifdef	sun4
/* 
 * SCSI Sun host adapter control registers for Sun-4.
 */
#define	SET_DMA_ADDR(har,val)	(har)->dma_addrh = (val >> 16);\
				(har)->dma_addrl = (val & 0xffff);
#define	GET_DMA_ADDR(har)	(((har)->dma_addrh  << 16) | ((har)->dma_addrl))

struct	scsi_ha_reg {		/* host adapter (I/O space) registers */
	u_char	data;		/* data register */
	u_char	unused;
	u_char	cmd_stat;	/* command/status register */
	u_char	unused2;
	u_short	icr;		/* interface control register */
	u_short	unused3;
#if	MACH
	/*
	 * Don't multiply define dma_addr as a long and as two shorts!
	 */
#else	MACH
	u_long	dma_addr;	/* dma base address */
#endif	MACH
	u_short	dma_addrh;	/* dma base address */
	u_short	dma_addrl;
	u_short	dma_count;	/* dma count register */
	u_char	unused4;
	u_char	intvec;		/* interrupt vector for VMEbus versions */
};
#endif	sun4


/*
 * bits in the interface control register 
 */
#define ICR_PARITY_ERROR	0x8000
#define ICR_BUS_ERROR		0x4000
#define ICR_ODD_LENGTH		0x2000
#define ICR_INTERRUPT_REQUEST	0x1000
#define ICR_REQUEST		0x0800
#define ICR_MESSAGE		0x0400
#define ICR_COMMAND_DATA	0x0200	/* command=1, data=0 */
#define ICR_INPUT_OUTPUT	0x0100	/* input=1, output=0 */
#define ICR_PARITY		0x0080
#define ICR_BUSY		0x0040
/* Only the following bits may usefully be set by the CPU */
#define ICR_SELECT		0x0020
#define ICR_RESET		0x0010
#define ICR_PARITY_ENABLE	0x0008
#define ICR_WORD_MODE		0x0004
#define ICR_DMA_ENABLE		0x0002
#define ICR_INTERRUPT_ENABLE	0x0001

/*
 * Compound conditions of icr bits message, command/data and input/output.
 */
#define ICR_COMMAND	(ICR_COMMAND_DATA)
#define ICR_STATUS	(ICR_COMMAND_DATA | ICR_INPUT_OUTPUT)
#define ICR_MESSAGE_IN	(ICR_MESSAGE | ICR_COMMAND_DATA | ICR_INPUT_OUTPUT)
#define ICR_BITS	(ICR_MESSAGE | ICR_COMMAND_DATA | ICR_INPUT_OUTPUT)
