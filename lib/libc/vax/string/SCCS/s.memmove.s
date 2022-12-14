h02077
s 00002/00002/00065
d D 8.1 93/06/04 15:40:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00067/00000/00000
d D 5.1 90/05/15 21:29:49 bostic 1 0
c date and time created 90/05/15 21:29:49 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/*
 * void *memmove(dst, src, size)
 * returns dst
 *
 * This optimises the usual case (count < 65536) at the expense
 * of some extra memory references and branches when count >= 65536.
 */

#include "DEFS.h"

ENTRY(memmove, 0)
	movzwl	$65535,r0	/* r0 = 64K (needed below) */
	movq	8(ap),r1	/* r1 = src, r2 = length */
	movl	4(ap),r3	/* r3 = dst */
	cmpl	r1,r3
	bgtru	1f		/* normal forward case */
	beql	2f		/* equal, nothing to do */
	addl2	r2,r1		/* overlaps iff src<dst but src+len>dst */
	cmpl	r1,r3
	bgtru	4f		/* overlapping, must move backwards */
	subl2	r2,r1

1:	/* move forward */
	cmpl	r2,r0
	bgtru	3f		/* stupid movc3 limitation */
	movc3	r2,(r1),(r3)	/* move it all */
2:
	movl	4(ap),r0	/* return original dst */
	ret
3:
	subl2	r0,12(ap)	/* adjust length by 64K */
	movc3	r0,(r1),(r3)	/* move 64K */
	movl	12(ap),r2
	decw	r0		/* from 0 to 65535 */
	brb	1b		/* retry */

4:	/* move backward */
	addl2	r2,r3
5:
	cmpl	r2,r0
	bgtru	6f		/* stupid movc3 limitation */
	subl2	r2,r1
	subl2	r2,r3
	movc3	r2,(r1),(r3)	/* move it all */
	movl	4(ap),r0	/* return original dst */
	ret
6:
	subl2	r0,12(ap)	/* adjust length by 64K */
	subl2	r0,r1
	subl2	r0,r3
	movc3	r0,(r1),(r3)	/* move 64K */
	movl	12(ap),r2
	decw	r0
	subl2	r0,r1
	subl2	r0,r3
	brb	5b
E 1
