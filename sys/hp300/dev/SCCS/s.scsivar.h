h33556
s 00002/00002/00029
d D 8.1 93/06/10 21:34:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00029
d D 7.2 92/06/05 15:31:44 hibler 2 1
c merge latest Utah hp300 code including 68040 support
e
s 00030/00000/00000
d D 7.1 90/05/08 22:06:49 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct	scsi_softc {
	struct	hp_ctlr *sc_hc;
	struct	devqueue sc_dq;
	struct	devqueue sc_sq;
	u_char	sc_flags;
	u_char	sc_sync;
	u_char	sc_scsi_addr;
	u_char	sc_stat[2];
	u_char	sc_msg[7];
};

/* sc_flags */
#define	SCSI_IO		0x80	/* DMA I/O in progress */
#define	SCSI_DMA32	0x40	/* 32-bit DMA should be used */
D 2
#define	SCSI_ALIVE	0x01	/* controller initialized */
E 2
I 2
#define	SCSI_HAVEDMA	0x04	/* controller has DMA channel */
E 2
#ifdef DEBUG
#define	SCSI_PAD	0x02	/* 'padded' transfer in progress */
#endif
I 2
#define	SCSI_ALIVE	0x01	/* controller initialized */
E 2
E 1
