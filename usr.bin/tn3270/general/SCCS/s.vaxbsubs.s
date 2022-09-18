h14301
s 00002/00002/00073
d D 8.1 93/06/06 16:52:04 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00072
d D 4.2 91/04/26 15:59:58 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00000/00085
d D 4.1 88/12/04 15:12:19 minshall 4 3
c Release 4.1
e
s 00010/00005/00075
d D 1.3 88/06/29 20:09:22 bostic 3 2
c install approved copyright notice
e
s 00010/00021/00070
d D 1.2 88/03/28 12:28:49 bostic 2 1
c add Berkeley specific headers
e
s 00091/00000/00000
d D 1.1 86/11/11 22:54:20 minshall 1 0
c date and time created 86/11/11 22:54:20 by minshall
e
u
U
t
T
I 1
D 5
/*
D 2
 *	@(#)vaxbsubs.s	3.1  10/29/86
 */

/*
 *	Copyright (c) 1984, 1985, 1986 by the Regents of the
 *	University of California and by Gregory Glenn Minshall.
E 2
I 2
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
/*-
D 6
 * Copyright (c) 1988 The Regents of the University of California.
E 5
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
E 2
 *
D 2
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 2
I 2
D 5
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 3
 *
 *	%W% (Berkeley) %G%
E 2
 */

/* This is taken from bcmp.s from 4.2.
 * The output of bunequal is the offset of the byte which didn't match;
 * if all the bytes match, then we return n.
 *
 * BUGNOTE:  This has no chance of working for lengths greater than 64K.
 *		(so, if you use this somewhere else, you may need to
 *		fix it...)
 */

/* bunequal(s1, s2, n) */

#include "defs.h"

ENTRY(bunequal)
	movl	4(ap),r1
	movl	8(ap),r3
	movl	12(ap),r4
1:
	movzwl	$65535,r0
	cmpl	r4,r0
	jleq	2f
	subl2	r0,r4
	cmpc3	r0,(r1),(r3)
	jeql	1b
	addl2	r4,r0
	/* changes... */
	subl3	r0,12(ap),r0
	/* end of changes for bunequal... */
	ret
2:
	cmpc3	r4,(r1),(r3)
	/* changes... */
	subl3	r0,12(ap),r0
	/* end of changes for bunequal... */
	ret




/* brand new code, using the above as base... */
/* bskip(s1, n, b) : finds the first occurrence of any byte != 'b' in the 'n'
 * bytes beginning at 's1'.
 *
 * BUGNOTE:  This has no chance of working for lengths greater than 64K.
 *		(so, if you use this somewhere else, you may need to
 *		fix it...)
 */

ENTRY(bskip)
	movl	4(ap),r1
	movl	8(ap),r3
	movl	12(ap),r4
1:
	movzwl	$65535,r0
	cmpl	r3,r0
	jleq	2f
	subl2	r0,r3
	skpc	r4,r0,(r1)
	jeql	1b
	addl2	r3,r0
	subl3	r0,8(ap),r0
	ret
2:
	skpc	r4,r3,(r1)
	subl3	r0,8(ap),r0
	ret
E 1
