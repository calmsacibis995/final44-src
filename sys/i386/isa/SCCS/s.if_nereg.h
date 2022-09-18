h23854
s 00002/00002/00022
d D 8.1 93/06/11 15:54:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 7.2 92/10/11 10:20:09 bostic 3 2
c make kernel includes standard
e
s 00009/00001/00015
d D 7.1 91/05/09 23:32:49 bostic 2 1
c new copyright; att/bsd/shared
e
s 00016/00000/00000
d D 1.1 90/11/08 19:33:06 bill 1 0
c date and time created 90/11/08 19:33:06 by bill
e
u
U
t
T
I 2
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * NE2000 Ethernet Card registers
D 2
 * %W% (Berkeley) %G%
E 2
 */

/* The NE2000 uses a DS8390 Ethernet controller in at the beginning of
   its i/o space */
D 3
#include "ic/ds8390.h"
E 3
I 3
#include <i386/isa/ic/ds8390.h>
E 3

#define ne_data		0x10	/* Data Transfer port */
#define ne_reset	0x1f	/* Card Reset port */

#define	PKTSZ	3*512
#define	TBUF	(16*1024)	/* Starting location of Transmit Buffer */
#define	RBUF	(16*1024+PKTSZ)	/* Starting location of Receive Buffer */
#define	RBUFEND	(32*1024)	/* Ending location of Transmit Buffer */
E 1
