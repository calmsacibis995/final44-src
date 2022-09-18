h41804
s 00002/00002/00043
d D 8.1 93/06/04 15:40:27 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00019/00033
d D 5.7 91/03/22 16:57:49 torek 9 8
c avoid branches, make profiling work.  used a trick to shave off
c one instruction (a branch, at that).
e
s 00001/00011/00051
d D 5.6 90/06/01 15:10:07 bostic 8 7
c new copyright notice
e
s 00011/00006/00051
d D 5.5 88/06/27 18:20:33 bostic 7 6
c install approved copyright notice
e
s 00010/00004/00047
d D 5.4 88/05/20 17:12:47 bostic 6 5
c add Berkeley specific header
e
s 00002/00002/00049
d D 5.3 86/03/09 21:36:45 donn 5 4
c added SYSLIBC_SCCS condition for sccs ids
e
s 00001/00001/00050
d D 5.2 85/06/05 19:28:32 mckusick 4 2
c Add copyright
e
s 00001/00000/00051
d R 5.2 85/06/03 10:28:03 dist 3 2
c Add copyright
e
s 00010/00000/00041
d D 5.1 85/05/31 08:34:44 dist 2 1
c Add copyright
e
s 00041/00000/00000
d D 4.1 82/12/04 16:14:28 mckusick 1 0
c date and time created 82/12/04 16:14:28 by mckusick
e
u
U
t
T
I 1
/*
I 2
D 10
 * Copyright (c) 1983 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 6
 */

D 5
#ifndef lint
E 5
I 5
D 6
#ifdef SYSLIBC_SCCS
E 6
I 6
#if defined(SYSLIBC_SCCS) && !defined(lint)
E 6
E 5
D 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
I 4
D 7
_sccsid:.asciz	"%W% (Berkeley) %G%"
E 7
I 7
	.asciz "%W% (Berkeley) %G%"
E 7
E 4
D 5
#endif not lint
E 5
I 5
D 6
#endif SYSLIBC_SCCS
E 6
I 6
#endif /* SYSLIBC_SCCS and not lint */
E 6
E 5

/*
E 2
 * @(#)vfork.s	4.1 (Berkeley) 12/21/80
 * C library -- vfork
 */

I 9
#include "SYS.h"

E 9
/*
 * pid = vfork();
 *
 * r1 == 0 in parent process, r1 == 1 in child process.
 * r0 == pid of child in parent, r0 == pid of parent in child.
 *
 * trickery here, due to keith sklower, uses ret to clear the stack,
 * and then returns with a jump indirect, since only one person can return
 * with a ret off this stack... we do the ret before we vfork!
 */

D 9
	.set	vfork,66
.globl	_vfork

_vfork:
	.word	0x0000
	movl	16(fp),r2
E 9
I 9
ENTRY(vfork)
	movl	16(fp),r2	# save return address before we smash it
E 9
	movab	here,16(fp)
	ret
here:
D 9
	chmk	$vfork
	bcc	vforkok
	jmp	verror
vforkok:
	tstl	r1		# child process ?
	bneq	child	# yes
	bcc 	parent		# if c-bit not set, fork ok
.globl	_errno
verror:
E 9
I 9
	chmk	$SYS_vfork
	bcs	err		# if failed, set errno and return -1
	/* this next trick is Chris Torek's fault */
	mnegl	r1,r1		# r1 = 0xffffffff if child, 0 if parent
	bicl2	r1,r0		# r0 &= ~r1, i.e., 0 if child, else unchanged
	jmp	(r2)

err:
E 9
	movl	r0,_errno
	mnegl	$1,r0
D 9
	jmp	(r2)
child:
	clrl	r0
parent:
E 9
	jmp	(r2)
E 1
