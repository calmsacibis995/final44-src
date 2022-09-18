h28643
s 00002/00002/00037
d D 8.1 93/06/10 22:29:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00000/00000
d D 7.1 92/12/13 03:50:14 akito 1 0
c date and time created 92/12/13 03:50:14 by akito
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

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <luna68k/stand/device.h>


#define C (caddr_t)
#define D (struct driver *)

extern struct driver scdriver;
extern struct driver sddriver;
extern struct driver stdriver;

struct hp_ctlr hp_cinit[] = {
/*	driver,		unit,	alive,	addr,	flags */
	{ &scdriver,	0,	0,	C 0x0,	0x0 },
	0
};

struct hp_device hp_dinit[] = {
/*driver,	cdriver,	unit,	ctlr,	slave,	addr,	dk,	flags*/
{ &sddriver,	&scdriver,	0,	0,	6,	C 0x0,	1,	0x0 },
{ &sddriver,	&scdriver,	1,	0,	5,	C 0x0,	1,	0x0 },
{ &stdriver,	&scdriver,	0,	0,	4,	C 0x0,	0,	0x0 },
0
};
E 1
