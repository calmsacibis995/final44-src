h31075
s 00002/00002/00016
d D 8.1 93/06/04 15:41:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00016/00012
d D 5.4 90/05/30 12:23:27 bostic 4 3
c new copyright notice; use ASMSTR instead of .ascsiz
e
s 00001/00001/00027
d D 5.3 90/05/12 16:58:03 bostic 3 2
c don't use hash marks for comments
e
s 00005/00002/00023
d D 5.2 89/08/26 17:02:35 karels 2 1
c rename to *login (from *logname), invalidate getlogin cache
c from setlogin
e
s 00025/00000/00000
d D 5.1 89/02/21 16:39:41 kfall 1 0
c date and time created 89/02/21 16:39:41 by kfall
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1983 The Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
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
 * %sccs.include.redist.c%
E 4
 */

D 4
#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

E 4
#include "SYS.h"
I 4

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 4

D 2
SYSCALL(setlogname)
	ret		# setlogname(name, len)
E 2
I 2
.globl	__logname_valid		/* in getlogin() */

SYSCALL(setlogin)
	movl	$0,__logname_valid
D 3
	ret				# setlogin(name)
E 3
I 3
	ret			/* setlogin(name); */
E 3
E 2
E 1
