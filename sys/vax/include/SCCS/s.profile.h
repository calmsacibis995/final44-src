h31162
s 00013/00000/00000
d D 7.1 92/07/16 23:49:01 mckusick 1 0
c date and time created 92/07/16 23:49:01 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_MCOUNT_DECL static void _mcount

#define	MCOUNT \
asm(".text; .globl mcount; mcount: pushl 16(fp); calls $1,__mcount; rsb");
E 1
