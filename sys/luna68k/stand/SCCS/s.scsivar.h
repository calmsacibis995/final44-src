h26993
s 00002/00002/00038
d D 8.1 93/06/10 22:30:10 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00000/00000
d D 7.1 92/12/13 03:50:26 akito 1 0
c date and time created 92/12/13 03:50:26 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct	scsi_softc {
	struct	hp_ctlr *sc_hc;
	u_char	*sc_buf;				/* Data Buffer Pointor*/
	u_char	*sc_cdb;				/* CDB Buffer Pointor */
	int	*sc_lock;				/* Lock Flag addres   */
	int	sc_flags;				/* SPC Status Flags   */
	int	sc_phase;				/* Current SCSI Phase */
	int	sc_target;				/* Current Target ID  */
	int	sc_len;					/* Buffer Length      */
	int	sc_cdblen;				/* CDB length         */
	u_char	sc_stat;
	u_char	sc_msg[7];
};


/* sc_lock  */

#define	SC_IN_PROGRESS		 0
#define SC_IO_COMPLETE		 1
#define	SC_DISCONNECTED		 2

#define	SC_IO_FAILED		-1
#define	SC_DEV_NOT_FOUND	-2

/* sc_flags */

#define	SC_SEL_TIMEOUT	0x00000001
E 1
