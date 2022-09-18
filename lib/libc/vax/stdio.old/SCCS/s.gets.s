h21964
s 00013/00008/00107
d D 5.4 88/06/27 17:51:57 bostic 4 3
c install approved copyright notice
e
s 00009/00003/00106
d D 5.3 88/05/23 20:26:17 bostic 3 2
c add Berkeley specific header
e
s 00002/00002/00107
d D 5.2 86/03/09 21:30:18 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00109/00000/00000
d D 5.1 85/08/23 18:57:29 mckusick 1 0
c date and time created 85/08/23 18:57:29 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1985 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 4
E 3
 */

D 2
#ifndef lint
E 2
I 2
D 4
#ifdef LIBC_SCCS
E 2
_sccsid:.asciz	"%W% (Berkeley) %G%"
D 2
#endif not lint
E 2
I 2
D 3
#endif LIBC_SCCS
E 3
I 3
#endif /* LIBC_SCCS */
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

/*
 * char *gets(s);
 * char *s;
 *
 * argument: a target string
 * side effects: reads bytes up to and including a newline from the
 *	standard input into the target string and replaces the newline
 *	with a null to null-terminate the string.
 * result: the target string if successful, 0 otherwise.
 */

#include "DEFS.h"

#define		NL	0xa

ENTRY(gets, R11|R10)

#define		S	r11
	movl	4(ap),S
#define		IPTR	r10
#define		_CNT
#define		_PTR	4
#define		_BASE	8
#define		_BUFSIZ	12
#define		_FLAG	16
	movab	__iob,IPTR

#define		OLD_S	4(ap)

	/*
	 * If no characters, call _filbuf() to get some.
	 */
	tstl	_CNT(IPTR)
	jgtr	Lscan

Lloop:
	pushl	IPTR
	calls	$1,__filbuf
	tstl	r0			/* What did _filbuf() return? */
	jlss	Leof
	cmpb	r0,$NL
	jneq	1f
	clrb	(S)
	jbr	Lret
1:
	movb	r0,(S)+			/* Save the returned character */
	tstl	_BASE(IPTR)		/* Is input buffered? */
	jeql	Lloop

	/*
	 * Look for a newline in the buffer.
	 */
Lscan:
	locc	$NL,_CNT(IPTR),*_PTR(IPTR)
	jeql	Lagain

	/*
	 * Success -- copy the data and return.
	 */
	subl3	r0,_CNT(IPTR),r2
	subl2	r2,_CNT(IPTR)
	movc3	r2,*_PTR(IPTR),(S)	/* Copy the data */
	clrb	(r3)
	movl	r1,_PTR(IPTR)
	decl	_CNT(IPTR)		/* Skip the newline */
	incl	_PTR(IPTR)

	/*
	 * Normal return.
	 */
Lret:
	movl	OLD_S,r0
	ret

	/*
	 * If we run out of characters, copy the buffer and loop.
	 */
Lagain:
	movc3	_CNT(IPTR),*_PTR(IPTR),(S)	/* Copy the data */
	movl	r3,S
	movl	_BASE(IPTR),_PTR(IPTR)		/* Reset stdio */
	clrl	_CNT(IPTR)
	jbr	Lloop

	/*
	 * End of file?  Check to see if we copied any data.
	 */
Leof:
	cmpl	S,OLD_S
	jeql	Lerror
	clrb	(S)
	jbr	Lret

	/*
	 * Error/eof return -- null pointer.
	 */
Lerror:
	clrl	r0
	ret
E 1
