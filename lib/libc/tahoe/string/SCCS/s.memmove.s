h34003
s 00002/00002/00053
d D 8.1 93/06/04 13:23:39 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00054
d D 5.2 90/06/01 15:29:57 bostic 2 1
c new copyright notice
e
s 00065/00000/00000
d D 5.1 90/05/15 21:23:07 bostic 1 0
c date and time created 90/05/15 21:23:07 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* void *memmove(to, from, size) */
#include "DEFS.h"

ENTRY(memmove, 0)
	movl	4(fp),r1
	movl	8(fp),r0
	movl	12(fp),r2
	cmpl	r0,r1
	bgtru	1f		/* normal forward case */
	beql	2f		/* equal, nothing to do */
	addl2	r2,r0		/* may be overlapping */
	cmpl	r0,r1
	bgtru	3f
	subl2	r2,r0		/* normal forward case */
1:
	movblk
2:
	movl	4(fp),r0	/* this can probably be optimised */
	ret
3:
	addl2	r2,r1		/* overlapping, must do backwards */
	subl3	r0,r1,r3
	movl	r2,r4
	jbr	5f
4:
	subl2	r3,r0
	subl2	r3,r1
	movl	r3,r2
	movblk
	subl2	r3,r0
	subl2	r3,r1
	subl2	r3,r4
5:
	cmpl	r4,r3
	jgtr	4b
	movl	r4,r2
	subl2	r2,r0
	subl2	r2,r1
	movblk
	movl	4(fp),r0
	ret
E 1
