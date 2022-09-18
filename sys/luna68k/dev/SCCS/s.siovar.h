h02619
s 00002/00002/00027
d D 8.1 93/06/10 22:17:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00028
d D 7.2 93/05/02 05:45:13 akito 2 1
c add member save port number
e
s 00028/00000/00000
d D 7.1 92/11/17 16:23:33 akito 1 0
c date and time created 92/11/17 16:23:33 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * siovar.h --
 */


struct	sio_portc {
	int	pc_major;
	int	pc_unit;
I 2
	int	pc_port;
E 2
	struct siodevice *pc_addr;
	int	(*pc_intr)();
};

struct	sio_softc {
	struct sio_portc *sc_pc;
};
E 1
