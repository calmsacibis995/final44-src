h06050
s 00002/00002/00056
d D 8.1 93/06/04 13:15:30 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00057
d D 1.3 90/06/01 14:49:24 bostic 3 2
c new copyright notice
e
s 00023/00003/00045
d D 1.2 89/02/17 17:35:47 bostic 2 1
c add Berkeley specific copyright notice
e
s 00048/00000/00000
d D 1.1 86/07/02 16:25:56 sam 1 0
c date and time created 86/07/02 16:25:56 by sam
e
u
U
t
T
I 1
D 2
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS
E 2
I 2
/*
D 4
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 2

#include <tahoemath/fp.h>
#include "DEFS.h"

XENTRY(sfnorm, R2|R3|R4|R5|R6)
	clrl	r1
	movl	r0,r4		/* copy to temporary. */
	jeql	retzero
	clrl	r3		/* r3 - pos of m.s.b */
inr00:	ffs	r4,r6
	incl	r6
	addl2	r6,r3
	shrl	r6,r4,r4
	jneq	inr00

cmpshift:
				/* compute the shift (r4). */
	subl3	r3,$HID_POS,r4
	jlss	shiftr		/* if less then zero we shift right. */
	shll	r4,r0,r0	/* else we shift left. */
	subl2	r4,r2		/* uodate exponent. */
	jleq	underflow	/* if less then 0 (biased) it is underflow. */
	jmp	combine		/* go to combine exponent and fraction. */
shiftr:
	mnegl	r4,r4
	shrl	r4,r0,r0	/* shift right. */
	addl2	r4,r2		/* update exponent */
	cmpl	r2,$256
	jgeq	overflow	/* check for overflow. */
combine:
	andl2	$CLEARHID,r0	/* clear the hidden bit. */
	shal	$EXPSHIFT,r2,r2	/* shift the exponent to its proper place. */
	orl2	r2,r0
	ret

underflow:
	callf	$4,sfpunder
	ret

overflow:
	callf 	$4,sfpover
	ret
retzero:
	clrl	r0
	ret
E 1
