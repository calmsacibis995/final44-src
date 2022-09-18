h09511
s 00002/00002/00028
d D 8.1 93/06/10 22:16:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 7.1 92/06/15 06:45:54 fujita 1 0
c date and time created 92/06/15 06:45:54 by fujita
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

/*
 * PIO definitions
 * OMRON: $Id: pioreg.h,v 1.1 92/05/27 14:33:18 moti Exp $
 * by Shigeto Mochida 
 */

#define	PIO0_ADDR      	0x49000000	/* pio0 address */
#define	PIO1_ADDR	0x4D000000	/* pio1 address */

#define	PIO_MODED	0xB6		/* pio mode set */

struct pio {
    unsigned char	a_port;
    unsigned char	b_port;
    unsigned char	c_port;
    unsigned char	control_port;
};
E 1
