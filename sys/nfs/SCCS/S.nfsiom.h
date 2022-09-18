h04084
s 00001/00011/00018
d D 7.3 90/06/28 21:53:35 bostic 3 2
c new copyright notice
e
s 00000/00006/00029
d D 7.2 90/06/21 11:14:18 mckusick 2 1
c "update from Rick Macklem"
e
s 00035/00000/00000
d D 7.1 89/08/30 20:26:15 macklem 1 0
c first buffer cache implementation
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Size of the resource map and system page table pte's that are mapped
 * by nfs for i/o much like a bus adapter
 */
#define	NFS_MAPREG	512	/* Num. of kernel pte's for i/o mapping */
				/* Must be >= MAXPHYS/NBPG */
#define	NFS_MSIZ	100	/* Size of alloc. map for pte's */
D 2

/*
 * Size of the bio buffers, must be a power of 2 <= MAX_BSIZE
 */
#define	NFS_BIOSIZE	8192
#define	NFS_BIOSHIFT	13	/* Bits for NFS_BIOSIZE */
E 2
E 1
