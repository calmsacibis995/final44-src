h62453
s 00002/00002/00064
d D 8.1 93/06/04 13:16:49 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00064
d D 5.1 91/01/30 14:34:45 bostic 5 4
c make the copyright look right, yank to 5.1
e
s 00001/00011/00065
d D 1.4 90/06/01 14:53:29 bostic 4 3
c new copyright notice
e
s 00013/00008/00063
d D 1.3 88/06/27 17:46:47 bostic 3 2
c install approved copyright notice
e
s 00018/00003/00053
d D 1.2 88/05/23 21:33:14 bostic 2 1
c add Berkeley/CCI specific header; fix sccsid
e
s 00056/00000/00000
d D 1.1 86/08/01 08:49:30 sam 1 0
c date and time created 86/08/01 08:49:30 by sam
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
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 3
D 4
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
E 4
I 4
D 5
 * %sccs.include.redist.c%
E 4
 *
E 5
E 3
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
I 5
 *
 * %sccs.include.redist.c%
E 5
D 3
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 3
_sccsid:.asciz	"%W% (Berkeley) %G%"
E 3
I 3
	.asciz "%W% (Berkeley) %G%"
E 3
#endif /* LIBC_SCCS and not lint */
E 2

/*
 * C library -- _setjmp, _longjmp
 *
 *	_longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	_setjmp(a)
 * by restoring registers from the stack,
 * The previous signal state is NOT restored.
 */

#include "DEFS.h"

ENTRY(_setjmp, 0)
	movl	4(fp),r0
	movl	(fp),(r0)		# save frame pointer of caller
	movl	-8(fp),4(r0)		# save pc of caller
	clrl	r0
	ret

ENTRY(_longjmp, 0)
	movl	8(fp),r0		# return(v)
	movl	4(fp),r1		# fetch buffer
	tstl	(r1)
	beql	botch
loop:
	cmpl	(r1),(fp)
	beql	done
	blssu	botch
	movl	$loop,-8(fp)
	ret				# pop another frame

done:
	cmpb	*-8(fp),reiins		# returning to an "rei"?
	bneq	1f
	movab	3f,-8(fp)		# do return w/ psl-pc pop
	brw	2f
1:
	movab	4f,-8(fp)		# do standard return
2:
	ret				# unwind stack before signals enabled
3:
	addl2	$8,sp			# compensate for PSL-PC push
4:
	jmp	*4(r1)			# done, return....

botch:
	callf	$4,_longjmperror
	halt

	.data
reiins:	rei
E 1
