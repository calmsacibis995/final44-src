h26199
s 00000/00001/00016
d D 5.5 91/04/28 14:44:05 torek 5 4
c PSEUDO now does the return
e
s 00009/00019/00008
d D 5.4 90/05/30 12:23:18 bostic 4 3
c new copyright notice; use ASMSTR instead of .ascsiz
e
s 00001/00001/00026
d D 5.3 90/05/12 16:32:16 bostic 3 2
c don't use hash mark for comments
e
s 00004/00002/00023
d D 5.2 89/08/26 17:02:34 karels 2 1
c rename to *login (from *logname), invalidate getlogin cache
c from setlogin
e
s 00025/00000/00000
d D 5.1 89/02/21 16:39:34 kfall 1 0
c date and time created 89/02/21 16:39:34 by kfall
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1989 Regents of the University of California.
E 4
I 4
/*-
 * Copyright (c) 1983 The Regents of the University of California.
E 4
 * All rights reserved.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
SYSCALL(getlogname)
	ret		# getlogname(buf, buflen)
E 2
I 2
/* internal version of getlogin() */

D 4
PSEUDO(_getlogin,getlogin)
D 3
	ret		# _getlogin(buf, buflen)
E 3
I 3
	ret		/* _getlogin(buf, buflen) */
E 4
I 4
PSEUDO(_getlogin,getlogin)	/* _getlogin(buf, buflen) */
D 5
	ret
E 5
E 4
E 3
E 2
E 1
