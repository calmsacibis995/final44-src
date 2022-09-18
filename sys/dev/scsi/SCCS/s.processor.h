h07992
s 00002/00002/00035
d D 8.1 93/06/10 21:20:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00035
d D 5.3 93/02/01 11:17:29 torek 3 2
c rm bitfields
e
s 00005/00000/00033
d D 5.2 92/07/23 14:00:46 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00033/00000/00000
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
 * from: $Header: processor.h,v 1.2 92/05/15 11:24:01 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: processor.h,v 1.3 92/12/02 03:52:27 torek Exp $ (LBL)
E 3
 */

/*
 * SCSI definitions for Processor Devices.
 */
#define	CMD_RECEIVE		0x08	/* receive */
#define	CMD_SEND		0x0a	/* send */

/*
 * Structure of a RECEIVE or SEND command (i.e., the cdb).
 */
struct scsi_cdb_rs {
	u_char	cdb_cmd,		/* 0x8 or 0xa */
D 3
		cdb_lun:3,		/* logical unit number */
		cdb_xxx:5,		/* reserved */
E 3
I 3
		cdb_lun_xxx,		/* logical unit number + reserved */
E 3
		cdb_lenh,		/* buffer or data length (MSB) */
		cdb_lenm,		/* buffer or data length */
		cdb_lenl,		/* buffer or data length (LSB) */
		cdb_ctrl;		/* control byte */
};
E 1
