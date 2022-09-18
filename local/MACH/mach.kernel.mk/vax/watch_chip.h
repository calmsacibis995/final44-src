/*  
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	watch_chip.h,v $
 * Revision 2.3  89/03/09  22:23:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  10:50:14  gm0w
 * 	Changes for cleanup.
 * 
 * 29-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added definitions for rotated control registers.
 *
 * 20-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/watch_chip.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Header file for VAX Watch Chip.
 */
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
	short	csra;
	short	csrb;
	short	csrc;
	short	csrd;
	short   ram[64-14];
};
/*
 *	Bit definitions for watch chip CSRs.
 */

/*
 *	flavor 1: not rotated (MicroVAX)
 */
#define WATCH_CSRA_BUSY		0x80		/* csr A busy bit */
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

struct watch_chip	*watch_chip;
