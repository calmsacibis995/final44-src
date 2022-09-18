h40034
s 00002/00002/00031
d D 8.1 93/06/04 13:01:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00000/00000
d D 5.1 92/06/25 06:17:01 torek 1 0
c date and time created 92/06/25 06:17:01 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: saveregs.s,v 1.1 91/07/06 17:22:33 torek Exp $
 */

/*
 * Save register arguments in caller's `arg dump' area, so that
 * stdarg functions work.
 *
 * This really should be done with a pointer to the arg dump area;
 * our caller should allocate that area, not our caller's caller.
 * But then, they did not let me invent the calling sequence....
 *
 * We assume the caller has executed a `save' instruction.
 */
#include "DEFS.h"

ENTRY(__builtin_saveregs)
	st	%i0, [%fp + 0x44]	! fr->fr_argd[0]
	st	%i1, [%fp + 0x48]	! fr->fr_argd[1]
	st	%i2, [%fp + 0x4c]	! fr->fr_argd[2]
	st	%i3, [%fp + 0x50]	! fr->fr_argd[3]
	st	%i4, [%fp + 0x54]	! fr->fr_argd[4]
	retl
	st	%i5, [%fp + 0x58]	! fr->fr_argd[5]
E 1
