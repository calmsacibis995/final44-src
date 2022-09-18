/*
 * Mach Operating System
 * Copyright (c) 1991,1989,1987 Carnegie Mellon University
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
 * $Log:	watch_chip.h,v $
 * Revision 2.4  91/06/19  12:01:55  rvb
 * 	Support for VaxStation 3100:	shift two bits
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/14  17:46:42  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:28:43  dbg
 * 	Added volatile declarations.
 * 	[91/03/28            dbg]
 * 
 * Revision 2.1  89/08/03  16:38:37  rwd
 * Created.
 * 
 * 29-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added definitions for rotated control registers.
 *
 * 20-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */

/*
 *	File:	vax/watch_chip.h
 *	Author:	Avadis Tevanian, Jr., 1986.
 *
 *	Header file for VAX Watch Chip.
 */

#ifndef	_VAX_WATCH_CHIP_H_
#define	_VAX_WATCH_CHIP_H_

struct watch_chip {
	short	seconds;
	short	unused1;
	short	minutes;
	short	unused2;
	short	hours;
	short	unused3;
	short	unused4;
	short	day;
	short	month;
	short	year;
    volatile
	short	csra;
	short	csrb;
	short	csrc;
	short	csrd;
	short   ram[64-14];
};

struct watch_chip_3100 {
	long	seconds;
	long	unused1;
	long	minutes;
	long	unused2;
	long	hours;
	long	unused3;
	long	dow;
	long	day;
	long	month;
	long	year;
    volatile
	long	csra;
	long	csrb;
	long	csrc;
	long	csrd;
	long	ram[64-14];
};

/*
 *	Bit definitions for watch chip CSRs.
 */

/*
 *	flavor 1: not rotated (MicroVAX)
 */
#define	WATCH_CSRA_BUSY		0x80		/* csr A busy bit */
#define WATCH_CSRA_SETUP	0x20		/* csr A setup bits */
#define WATCH_CSRB_OFF		0x80		/* csr B off bit */
#define WATCH_CSRB_SETUP	0x06		/* csr B setup bits */

/*
 *	flavor 2: rotated (KA820)
 */
#define WATCH_ROT_CSRA_BUSY	0x01		/* csr A busy bit */
#define WATCH_ROT_CSRA_SETUP	0x40		/* csr A setup bit */
#define WATCH_ROT_CSRB_OFF	0x01		/* csr B off bit */
#define WATCH_ROT_CSRB_SETUP	0x0c		/* csr B setup bits */
#define WATCH_ROT_CSRD_VALID	0x01		/* csr D clock-valid bit */

/*
 *	flavor 3: shifted (VAX3100)
 */
#define	WATCH_SHFT_CSRA_BUSY	(0x80<<2)	/* csr A busy bit */
#define WATCH_SHFT_CSRA_SETUP	(0x20<<2)	/* csr A setup bits */
#define WATCH_SHFT_CSRB_OFF	(0x80<<2)	/* csr B off bit */
#define WATCH_SHFT_CSRB_SETUP	(0x06<<2)	/* csr B setup bits */
#define WATCH_SHFT_CSRD_VALID	(0x80<<2)	/* csr D clock-valid bit */

struct watch_chip	*watch_chip;

#endif	/* _VAX_WATCH_CHIP_H_ */
