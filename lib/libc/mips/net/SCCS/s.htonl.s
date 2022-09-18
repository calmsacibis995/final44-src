h58084
s 00002/00002/00039
d D 8.1 93/06/04 12:46:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00007/00038
d D 5.5 93/02/21 13:46:10 ralph 5 4
c use MIPSEB & MIPSEL instead of BYTE_ORDER
e
s 00001/00001/00044
d D 5.4 92/07/26 21:38:12 ralph 4 3
c removed DEFS.h
e
s 00012/00000/00033
d D 5.3 92/06/20 12:36:29 ralph 3 2
c add bigendian support
e
s 00002/00002/00031
d D 5.2 92/02/29 12:58:09 bostic 2 1
c need DEFS.h for ASMSTR macro
e
s 00033/00000/00000
d D 5.1 92/02/29 12:43:13 bostic 1 0
c date and time created 92/02/29 12:43:13 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 2
D 4
#include "DEFS.h"
E 4
I 4
#include <machine/machAsmDefs.h>
E 4

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include "DEFS.h"
E 2

I 3
D 5
#include <machine/endian.h>
#undef	 htonl
#undef	 ntohl

E 5
E 3
/*
 * netorder = htonl(hostorder)
 * hostorder = ntohl(netorder)
 */
D 5
LEAF(htonl)				# a0 = 0x11223344, return 0x44332211
E 5
I 5
NLEAF(htonl)				# a0 = 0x11223344, return 0x44332211
E 5
ALEAF(ntohl)
I 3
D 5
#if BYTE_ORDER == LITTLE_ENDIAN
E 5
I 5
#ifdef MIPSEL
E 5
E 3
	srl	v1, a0, 24		# v1 = 0x00000011
	sll	v0, a0, 24		# v0 = 0x44000000
	or	v0, v0, v1
	and	v1, a0, 0xff00
	sll	v1, v1, 8		# v1 = 0x00330000
	or	v0, v0, v1
	srl	v1, a0, 8
	and	v1, v1, 0xff00		# v1 = 0x00002200
	or	v0, v0, v1
I 3
#else
D 5
#if BYTE_ORDER == BIG_ENDIAN
E 5
I 5
#ifdef MIPSEB
E 5
	move	v0, a0
#else
	ERROR
#endif
#endif
E 3
	j	ra
END(htonl)
E 1
