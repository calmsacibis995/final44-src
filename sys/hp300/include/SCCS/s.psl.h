h35400
s 00002/00002/00043
d D 8.1 93/06/10 21:45:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00044
d D 7.4 92/12/27 09:28:49 hibler 4 3
c treat PSL as longword for MBZ bits
e
s 00002/00004/00043
d D 7.3 92/07/08 01:06:30 torek 3 2
c no one uses BASEPRI; add PSL_M
e
s 00008/00000/00039
d D 7.2 91/05/04 19:56:18 karels 2 1
c move USERMODE/BASEPRI here, protect from multiple inclusion
c (now included by machine/param.h for spl's)
e
s 00039/00000/00000
d D 7.1 90/05/08 17:51:20 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#ifndef PSL_C
E 2
/*
 * MC68000 program status word
 */

#define	PSL_C		0x0001		/* carry bit */
#define	PSL_V		0x0002		/* overflow bit */
#define	PSL_Z		0x0004		/* zero bit */
#define	PSL_N		0x0008		/* negative bit */
#define	PSL_X		0x0010		/* extend bit */
#define	PSL_ALLCC	0x001F		/* all cc bits - unlikely */
#define	PSL_IPL0	0x0000		/* interrupt priority level 0 */
#define	PSL_IPL1	0x0100		/* interrupt priority level 1 */
#define	PSL_IPL2	0x0200		/* interrupt priority level 2 */
#define	PSL_IPL3	0x0300		/* interrupt priority level 3 */
#define	PSL_IPL4	0x0400		/* interrupt priority level 4 */
#define	PSL_IPL5	0x0500		/* interrupt priority level 5 */
#define	PSL_IPL6	0x0600		/* interrupt priority level 6 */
#define	PSL_IPL7	0x0700		/* interrupt priority level 7 */
I 3
#define	PSL_M		0x1000		/* master (kernel) sp vs intr sp */
E 3
#define	PSL_S		0x2000		/* supervisor enable bit */
I 3
/*	PSL_T0		0x4000		   ??? T0 on 68020, 8000 is T1 */
E 3
#define	PSL_T		0x8000		/* trace enable bit */

#define	PSL_LOWIPL	(PSL_S)
#define	PSL_HIGHIPL	(PSL_S | PSL_IPL7)
#define PSL_IPL		(PSL_IPL7)
#define	PSL_USER	(0)

D 4
#define	PSL_MBZ		0x58E0		/* must be zero bits */
E 4
I 4
#define	PSL_MBZ		0xFFFF58E0	/* must be zero bits */
E 4

#define	PSL_USERSET	(0)
#define	PSL_USERCLR	(PSL_S | PSL_IPL7 | PSL_MBZ)
I 2

D 3
/*
 * Macros to decode processor status word.
 */
E 3
#define	USERMODE(ps)	(((ps) & PSL_S) == 0)
D 3
#define	BASEPRI(ps)	(((ps) & PSL_IPL7) == 0)
E 3
#endif
E 2
E 1
