h24998
s 00002/00002/00031
d D 8.1 93/06/10 22:29:46 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00000/00000
d D 7.1 92/12/13 03:50:21 akito 1 0
c date and time created 92/12/13 03:50:21 by akito
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
 * preset.h -- preset infomation
 *   by A.Fujita, Dec-12-1992
 */

/*
 * DIP SW-1
 */

#define	PS_AUTOBOOT	0x01				/* 1: PROM auto-boot */
#define	PS_BMC_CONS	0x02				/* 2: use bitmap display as console */
#define	PS_BW_DISP	0x04				/* 3: use B&W display (unused) */
							/* 4: HD write verify (???) */
#define	PS_COFF		0x10				/* 5: boot COFF format kernel */
#define	PS_PLAIN	0x20				/* 6: number of bitmap plain (unused) */
							/* NOTE: it has 4 plain, if turn it on, else 1 */
							/* 7: boot device (unused) */
							/* NOTE: it should be net-booting, if turn it on */
							/* 8: load diagnostic program (unused) */

E 1
