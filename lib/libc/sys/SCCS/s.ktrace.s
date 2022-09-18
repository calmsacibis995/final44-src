h33819
s 00001/00001/00024
d D 5.2 90/05/12 16:39:25 bostic 2 1
c don't use hash mark for comments.
e
s 00025/00000/00000
d D 5.1 88/12/14 03:49:53 marc 1 0
c date and time created 88/12/14 03:49:53 by marc
e
u
U
t
T
I 1
/*
 * Copyright (c) 1983 Regents of the University of California.
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

SYSCALL(ktrace)
D 2
	ret		#
E 2
I 2
	ret		/* err = ktrace(file, ops, trpoints, pid); */
E 2
E 1
