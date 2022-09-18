h14969
s 00001/00011/00031
d D 5.4 90/06/01 16:01:16 bostic 5 4
c new copyright notice
e
s 00017/00005/00025
d D 5.3 89/05/23 10:20:19 bostic 4 3
c add Berkeley specific copyright notice
e
s 00017/00017/00013
d D 5.2 88/01/12 00:04:43 donn 3 2
c merge in latest Linton version
e
s 00000/00000/00030
d D 5.1 86/02/22 22:24:32 sam 2 1
c update sccsid
e
s 00030/00000/00000
d D 1.1 86/02/22 22:23:35 sam 1 0
c date and time created 86/02/22 22:23:35 by sam
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1985 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
#
# modified version of cerror
#
# The idea is that every time an error occurs in a system call
# I want a special function "syserr" called.  This function will
# either print a message and exit or do nothing depending on
# defaults and use of "onsyserr".
#
E 3
I 3
/*
D 4
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
 *
D 4
 *	%W% (Berkeley) %G%
E 4
I 4
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 *
D 4
 *
E 4
I 4
 *	%W% (Berkeley) %G%
 */

/* 
E 4
 * modified version of cerror
 *
 * The idea is that every time an error occurs in a system call
 * I want a special function "syserr" called.  This function will
 * either print a message and exit or do nothing depending on
 * defaults and use of "onsyserr".
 */
E 3

.globl	cerror
.comm	_errno,4

cerror:
	movl	r0,_errno
D 3
	callf	$0,_syserr	# new code
E 3
I 3
	callf	$0,_syserr	/* new code */
E 3
	mnegl	$1,r0
	ret

D 3
.globl	__mycerror		# clumsy way to get this loaded
E 3
I 3
.globl	__mycerror		/* clumsy way to get this loaded */
E 3

__mycerror:
	.word	0
	ret
E 1
