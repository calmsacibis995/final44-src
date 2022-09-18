h17786
s 00002/00002/00025
d D 8.1 93/06/04 12:47:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00026
d D 5.3 92/07/26 21:41:38 ralph 3 2
c removed DEFS.h
e
s 00002/00002/00025
d D 5.2 92/02/29 12:57:15 bostic 2 1
c DEFS.h needed for ASMSTR macro
e
s 00027/00000/00000
d D 5.1 92/02/29 12:49:00 bostic 1 0
c date and time created 92/02/29 12:49:00 by bostic
e
u
U
t
T
I 1
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
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 2
D 3
#include "DEFS.h"
E 3
I 3
#include <machine/machAsmDefs.h>
E 3

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include "DEFS.h"
E 2

LEAF(rindex)
	move	v0, zero		# default if not found
1:
	lbu	a3, 0(a0)		# get a byte
	addu	a0, a0, 1
	bne	a3, a1, 2f
	subu	v0, a0, 1		# save address of last match
2:
	bne	a3, zero, 1b		# continue if not end
	j	ra
END(rindex)
E 1
