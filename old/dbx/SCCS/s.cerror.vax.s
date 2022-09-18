h57959
s 00001/00011/00031
d D 5.4 90/06/01 16:01:21 bostic 8 7
c new copyright notice
e
s 00017/00006/00025
d D 5.3 89/05/23 10:20:20 bostic 7 6
c add Berkeley specific copyright notice
e
s 00018/00019/00013
d D 5.2 88/01/12 00:11:19 donn 6 5
c merge in latest Linton version
e
s 00006/00002/00026
d D 5.1 85/05/31 11:29:01 dist 5 4
c Add copyright
e
s 00002/00000/00026
d D 1.3 85/03/01 20:19:00 linton 4 3
c update to version 3.0
e
s 00000/00000/00026
d D 1.2 84/06/23 11:39:36 sam 3 1
i 2
c merge linton branch delta trail
e
s 00000/00000/00026
d D 1.1.1.1 84/06/23 10:44:47 sam 2 1
c branch delta of linton changes from net.sources
e
s 00026/00000/00000
d D 1.1 84/06/23 10:32:46 sam 1 0
c date and time created 84/06/23 10:32:46 by sam
e
u
U
f b 
t
T
I 1
D 5
# Copyright (c) 1982 Regents of the University of California
E 5
I 5
D 6
#!/bin/csh -f
E 5
#
D 5
# static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
E 5
#
I 4
# static char rcsid[] = "$Header: cerror.s,v 1.5 84/12/26 10:38:33 linton Exp $";
#
E 4
# modified version of cerror
#
# The idea is that every time an error occurs in a system call
# I want a special function "syserr" called.  This function will
# either print a message and exit or do nothing depending on
# defaults and use of "onsyserr".
#
E 6
I 6
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 7
 *
D 7
 *	%W% (Berkeley) %G%
E 7
I 7
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 *
D 7
 * static char rcsid[] = "$Header: cerror.s,v 1.1 87/03/25 19:27:44 donn Rel $";
 *
E 7
I 7
 *	%W% (Berkeley) %G%
 */

/*
E 7
 * modified version of cerror
 *
 * The idea is that every time an error occurs in a system call
 * I want a special function "syserr" called.  This function will
 * either print a message and exit or do nothing depending on
 * defaults and use of "onsyserr".
 */
E 6

.globl	cerror
.comm	_errno,4

cerror:
	movl	r0,_errno
D 6
	calls	$0,_syserr	# new code
E 6
I 6
	calls	$0,_syserr	/* new code */
E 6
	mnegl	$1,r0
	ret

D 6
.globl	__mycerror		# clumsy way to get this loaded
E 6
I 6
.globl	__mycerror		/* clumsy way to get this loaded */
E 6

__mycerror:
	.word	0
	ret
E 1
