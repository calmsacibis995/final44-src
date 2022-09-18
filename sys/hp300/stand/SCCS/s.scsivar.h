h42077
s 00002/00002/00021
d D 8.1 93/06/10 21:47:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00022
d D 7.2 92/08/14 09:16:55 hibler 2 1
c increase MESG_IN/OUT field to 7 bytes.  Most drives only return 1 byte
c but some (MO) return more.  If the MESG_IN phase code fails to read all
c the pending bytes, it throws the controller out of sync leading to a
c variety of odd behaviors:
c         boot program failures on warm reboot (ixfer_start failures)
c         read requests that silently do nothing (VJ's old printf in sd.c)
c 
e
s 00023/00000/00000
d D 7.1 90/05/08 23:27:56 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory and the Systems
 * Programming Group of the University of Utah Computer Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct	scsi_softc {
	int	sc_ba;
	char	*sc_addr;
	char	sc_alive;
	char	sc_scsi_addr;
	char	sc_stat;
D 2
	char	sc_msg;
E 2
I 2
	char	sc_msg[7];
E 2
};

extern	struct scsi_softc scsi_softc[];
E 1
