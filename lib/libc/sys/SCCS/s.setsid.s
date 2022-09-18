h43721
s 00001/00001/00024
d D 5.2 90/05/12 16:42:40 bostic 3 2
c don't use hash mark for comments.
e
s 00001/00001/00024
d D 5.1 89/08/27 15:48:41 karels 2 1
c rev 5; copyright when created
e
s 00025/00000/00000
d D 1.1 88/10/07 17:34:13 marc 1 0
c date and time created 88/10/07 17:34:13 by marc
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1983 Regents of the University of California.
E 2
I 2
 * Copyright (c) 1988 Regents of the University of California.
E 2
 * All rights reserved.
 *
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
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

SYSCALL(setsid)
D 3
	ret		#
E 3
I 3
	ret		/* sid = setsid(); */
E 3
E 1
