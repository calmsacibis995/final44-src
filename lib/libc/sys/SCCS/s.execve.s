h60299
s 00001/00001/00024
d D 5.6 90/05/12 16:32:55 bostic 7 6
c don't use hash mark for comments
e
s 00011/00006/00014
d D 5.5 88/06/27 18:21:08 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00010
d D 5.4 88/05/20 17:13:24 bostic 5 4
c add Berkeley specific header
e
s 00002/00002/00012
d D 5.3 86/03/09 21:40:53 donn 4 3
c added SYSLIBC_SCCS condition for sccs ids
e
s 00001/00001/00013
d D 5.2 85/06/05 19:13:01 mckusick 3 2
c Fix copyright
e
s 00009/00001/00005
d D 5.1 85/06/03 09:22:51 dist 2 1
c Add copyright
e
s 00006/00000/00000
d D 4.1 82/12/04 16:17:11 mckusick 1 0
c date and time created 82/12/04 16:17:11 by mckusick
e
u
U
t
T
I 1
D 2
/* %M% %I% %E% */
E 2
I 2
/*
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
E 5
 */

D 4
#ifndef lint
E 4
I 4
D 5
#ifdef SYSLIBC_SCCS
E 5
I 5
#if defined(SYSLIBC_SCCS) && !defined(lint)
E 5
E 4
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 6
_sccsid:.asciz	"%W% (Berkeley) %G%"
E 6
I 6
	.asciz "%W% (Berkeley) %G%"
E 6
E 3
D 4
#endif not lint
E 4
I 4
D 5
#endif SYSLIBC_SCCS
E 5
I 5
#endif /* SYSLIBC_SCCS and not lint */
E 5
E 4
E 2

#include "SYS.h"

SYSCALL(execve)
D 7
	ret		# execve(file, argv, arge)
E 7
I 7
	ret		/* execve(file, argv, arge) */
E 7
E 1
