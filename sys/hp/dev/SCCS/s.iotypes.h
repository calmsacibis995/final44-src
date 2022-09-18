h17853
s 00002/00002/00027
d D 8.1 93/06/10 21:24:09 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00000/00000
d D 7.1 92/06/05 15:25:47 hibler 1 0
c date and time created 92/06/05 15:25:47 by hibler
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 University of Utah.
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: iotypes.h 1.1 91/12/12$
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _IOTYPES_
#define	_IOTYPES_

/*
 * Where do these really belong?
 */
typedef volatile char			v_char;
typedef volatile unsigned char		vu_char;
typedef volatile short			v_short;
typedef volatile unsigned short		vu_short;
typedef volatile int			v_int;
typedef volatile unsigned int		vu_int;
#endif
E 1
