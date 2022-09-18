h04441
s 00002/00002/00031
d D 8.1 93/06/10 21:20:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00032
d D 5.3 93/02/01 11:16:09 torek 3 2
c update rcsid
e
s 00005/00000/00028
d D 5.2 92/07/23 14:00:43 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00028/00000/00000
d D 5.1 92/07/10 00:03:04 torek 1 0
c date and time created 92/07/10 00:03:04 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: printer.h,v 1.2 92/05/15 11:24:00 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: printer.h,v 1.3 92/12/02 03:52:03 torek Exp $ (LBL)
E 3
 */

/*
 * SCSI definitions for Printer Devices.
 */
#define	CMD_FORMAT		0x04	/* (set) format */
#define	CMD_PRINT		0x0a	/* print */
#define	CMD_SLEW_PRINT		0x0b	/* slew and print */
#define	CMD_FLUSH_BUFFER	0x10	/* flush buffer */
#define	CMD_RBD			0x14	/* recover buffered data */
#define	CMD_MODE_SELECT		0x15	/* mode select */
#define	CMD_RESERVE_UNIT	0x16	/* reserve unit */
#define	CMD_RELEASE_UNIT	0x17	/* release unit */
#define	CMD_MODE_SENSE		0x1a	/* mode sense */
#define	CMD_STOP_PRINT		0x1b	/* stop print */
E 1
