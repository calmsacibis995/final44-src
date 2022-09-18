h17046
s 00002/00002/00047
d D 8.1 93/06/04 13:23:36 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00048
d D 5.2 90/06/01 15:29:52 bostic 2 1
c new copyright notice
e
s 00059/00000/00000
d D 5.1 90/05/15 21:23:02 bostic 1 0
c date and time created 90/05/15 21:23:02 by bostic
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

/*
 * int
 * memcmp(s1, s2, n)
 *	void const *s1, const *s2;
 *	size_t n;
 *
 * Compare up to n bytes from s1/s2.
 * Return
 *	= 0 if s1 == s2
 *	< 0 if s1 < s2		(unsigned character comparison)
 *	> 0 if s1 > s2
 */
#include "DEFS.h"

ENTRY(memcmp, 0)
	movl	4(fp),r0
	movl	8(fp),r1
	mnegl	12(fp),r2
	jeql	2f
1:
	cmpb	(r0),(r1)
	jneq	3f
	incl	r0
	incl	r1
	aoblss	$0,r2,1b
2:
	clrl	r0
	ret
3:
	jlssu	4f
	movl	$1,r0
	ret
4:
	mnegl	$1,r0
	ret
E 1
