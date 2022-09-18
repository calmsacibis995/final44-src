h13783
s 00002/00002/00029
d D 8.1 93/06/04 13:24:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00030
d D 5.4 90/06/01 15:35:18 bostic 4 3
c new copyright notice
e
s 00011/00006/00030
d D 5.3 88/06/27 18:42:27 bostic 3 2
c install approved copyright notice
e
s 00010/00004/00026
d D 5.2 88/05/20 15:55:20 bostic 2 1
c add Berkeley specific header
e
s 00030/00000/00000
d D 5.1 86/07/02 16:23:59 sam 1 0
c date and time created 86/07/02 16:23:59 by sam
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1983 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

D 2
#ifdef SYSLIBC_SCCS
E 2
I 2
#if defined(SYSLIBC_SCCS) && !defined(lint)
E 2
D 3
_sccsid:.asciz	"%W% (Berkeley) %G%"
E 3
I 3
	.asciz "%W% (Berkeley) %G%"
E 3
D 2
#endif SYSLIBC_SCCS
E 2
I 2
#endif /* SYSLIBC_SCCS and not lint */
E 2

#include "SYS.h"

ENTRY(syscall)
	pushl	4(fp)		# syscall number
	movl	fp,r0		# point to the arg list
	movl	-4(fp),r1	# (arg_count + 1) (bytes) | mask
	andl2	$0xFFFF,r1	# clear the mask bits
	shrl	$2,r1,r1	# convert to words
	subl2	$2,r1		# don't count the first arg
1:
	addl2	$4,r0		# point to the next arg
	movl	4(r0),(r0)	# move an arg down
	decl	r1		# count it
	jgtr	1b		# any more?
	movl	(sp)+,r0	# no, get the syscall number back
	kcall	r0
	jcs	1f
	ret
1:
	jmp	cerror
E 1
