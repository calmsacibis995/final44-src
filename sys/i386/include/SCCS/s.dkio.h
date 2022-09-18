h22206
s 00002/00002/00020
d D 8.1 93/06/11 15:47:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00021
d D 5.2 91/01/18 14:32:02 william 3 2
c fixed just which copyright notice is included.
e
s 00012/00001/00010
d D 5.1 90/04/24 18:52:05 william 2 1
c 1st Berkeley Release
e
s 00011/00000/00000
d D 1.1 90/03/12 15:47:50 bill 1 0
c date and time created 90/03/12 15:47:50 by bill
e
u
U
t
T
I 1
D 2
/*	dkio.h	1.1	86/01/05	*/
E 2
I 2
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

E 2
/*
 * Structures and definitions for disk io control commands
 *
 * THIS WHOLE AREA NEEDS MORE THOUGHT.  FOR NOW JUST IMPLEMENT
 * ENOUGH TO READ AND WRITE HEADERS ON MASSBUS DISKS.  EVENTUALLY
 * SHOULD BE ABLE TO DETERMINE DRIVE TYPE AND DO OTHER GOOD STUFF.
 */

/* disk io control commands */
#define DKIOCHDR	_IO(d, 1)	/* next I/O will read/write header */
E 1
