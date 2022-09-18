h05425
s 00002/00002/00020
d D 8.1 93/06/10 22:30:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00000/00000
d D 7.1 92/12/13 03:50:35 akito 1 0
c date and time created 92/12/13 03:50:35 by akito
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

/* vectors.h */
/* by A.Fujita, Nov-18-1991 */

#define	NVECTBL		0x400	/* size of vector table */

#define ILLGINST	0x010	/* Illegal Instruction */
#define TRACEVEC	0x024	/* Trace Vector offset */
#define	NMIVEC		0x07c	/* Level 7 Interrupt Auto Vector (NMI) offset */
#define	EVTRAPF		0x0bc	/* Trap #15 Instraction Vector */
E 1
