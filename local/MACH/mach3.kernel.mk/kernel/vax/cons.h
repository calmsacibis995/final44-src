/* 
 **********************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **********************************************************************
 *
 * HISTORY
 * $Log:	cons.h,v $
 * Revision 2.2  91/06/19  12:00:21  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:47:17  rvb]
 * 
 * Revision 2.1  89/08/03  16:18:54  rwd
 * Created.
 * 
 * 12-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added definition of vmaygetc.
 *
 *  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added definitions for vgetc, vputc and vpollc.
 *
 */ 
 
#ifdef	KERNEL
#include <platforms.h>
#else	KERNEL
#include <sys/features.h>
#endif	KERNEL
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)cons.h	7.1 (Berkeley) 6/5/86
 */

/*
 * VAX console interface registers
 */

#define	RXCS_IE		0x00000040	/* receiver interrupt enable */
#define	RXCS_DONE	0x00000080	/* receiver done */

#define	RXDB_DATA	0x000000ff	/* received character */
#define	RXDB_ID		0x00000f00	/* channel id */
#define	RXDB_ERR	0x80000000	/* receiver error */

#define	TXCS_IE		0x00000040	/* transmitter interrupt enable */
#define	TXCS_RDY	0x00000080	/* transmitter ready for next char */
#if VAX8600
#define	TXCS_ID		0x00000300	/* interrupt ID field */
#define	TXCS_WMASK	0x00008000	/* enable mask write */
#define	TXCS_TXMASK	0x00ff0000	/* transmit enable channel mask: */
#define	TXCS_CTERM	0x00010000	/*	console terminal */
#define	TXCS_RTERM	0x00020000	/*	remote diagnostic port */
#define	TXCS_EMM	0x00040000	/*	Environmental Monitor Module */
#define	TXCS_LCONS	0x00080000	/*	Logical console */
#endif

#define	TXDB_DATA	0x000000ff	/* transmitter byte */
#define	TXDB_ID		0x00000f00	/* channel id- not on 8600 */
#define	TXDB_CONS	0x00000f00	/* channel id for console subsystem */

#define	TXDB_DONE	0x01		/* software done */
#define	TXDB_BOOT	0x02		/* reboot */
#define	TXDB_CWSI	0x03		/* clear warm start inhibit */
#define	TXDB_CCSI	0x04		/* clear cold-start inhibit */

#ifndef	ASSEMBLER
extern int	(*vgetc)(), (*vputc)(), (*vpollc)(), (*vmaygetc)();
#endif	ASSEMBLER
