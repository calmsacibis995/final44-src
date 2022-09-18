h34449
s 00002/00002/00042
d D 8.1 93/06/04 15:41:52 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00000/00000
d D 5.1 90/05/15 21:34:45 bostic 1 0
c date and time created 90/05/15 21:34:45 by bostic
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
 * Span the string s2 (skip characters that are in s2).
 * Return the number of characters in s1 that were skipped.
 *
 * size_t
 * strspn(s1, s2)
 *	const char *s1, *s2;
 */
#include "DEFS.h"

ENTRY(strspn, 0)
	subl2	$32,sp		/* make 256 bit table */
	movc5	$0,(sp),$0,$32,(sp)
	movq	4(ap),r1	/* r1 = s1, r2 = s2 */

	/* turn on bit for each character in s2, including '\0' */
1:
	movzbl	(r2)+,r0
	bbss	r0,(sp),1b
	bneq	1b

	/* now clear bit for '\0' */
	/* (this is easier than avoiding setting it in the first place) */
	bicb2	$1,(sp)		/* stop at '\0' */
	movl	r1,r0		/* r0 = s (current pos in s1) */

	/* look for a character that is not in s2 */
2:
	movzbl	(r0)+,r2	/* c = *s++ */
	bbs	r2,(sp),2b	/* loop while c is in table */
	decl	r0		/* s-- */
	subl2	r1,r0		/* r0 = s - s1 = count */
	ret
E 1
