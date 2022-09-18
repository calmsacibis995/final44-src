h28300
s 00001/00011/00034
d D 5.3 90/06/01 16:01:11 bostic 3 2
c new copyright notice
e
s 00017/00006/00028
d D 5.2 89/05/23 10:20:17 bostic 2 1
c add Berkeley specific copyright notice
e
s 00034/00000/00000
d D 5.1 88/01/12 00:42:45 donn 1 0
c date and time created 88/01/12 00:42:45 by donn
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 2
 *
D 2
 *	%W% (Berkeley) %G%
E 2
I 2
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
E 2
 *
D 2
 * static char rcsid[] = "$Header: cerror.s,v 1.2 87/03/25 19:32:31 donn Exp $";
 *
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * modified version of cerror
 *
 * The idea is that every time an error occurs in a system call
 * I want a special function "syserr" called.  This function will
 * either print a message and exit or do nothing depending on
 * defaults and use of "onsyserr".
 */

.data
.globl	_errno
_errno:
	.long	0
.text

.globl	cerror
cerror:
	movl	d0,_errno
	jbsr	_syserr		/* new code */
	moveq	#-1,d0
	rts

.globl	__mycerror		/* clumsy way to get this loaded */

__mycerror:
	rts
E 1
