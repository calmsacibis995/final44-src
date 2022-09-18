h18790
s 00002/00002/00026
d D 8.1 93/06/10 21:44:49 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 7.2 90/11/03 12:48:11 mckusick 2 1
c update identifier from Utah
e
s 00028/00000/00000
d D 7.1 90/05/08 17:51:18 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: mtpr.h 1.5 89/04/11$
E 2
I 2
 * from: Utah $Hdr: mtpr.h 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * simulated software interrupt register
 */

extern unsigned char ssir;

#define SIR_NET		0x1
#define SIR_CLOCK	0x2

#define siroff(x)	ssir &= ~(x)
#define setsoftnet()	ssir |= SIR_NET
#define setsoftclock()	ssir |= SIR_CLOCK
E 1
