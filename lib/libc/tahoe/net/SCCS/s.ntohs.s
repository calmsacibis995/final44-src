h09752
s 00002/00002/00016
d D 8.1 93/06/04 13:19:27 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00018
d D 5.1 91/04/12 12:56:02 bostic 5 4
c yank to rev 5.1
e
s 00001/00011/00017
d D 1.4 90/06/01 15:09:46 bostic 4 3
c new copyright notice
e
s 00020/00003/00008
d D 1.3 88/06/27 17:06:45 bostic 3 2
c install approved copyright notice
e
s 00001/00001/00010
d D 1.2 86/08/01 09:19:24 sam 2 1
c use common ENTRY macro definition
e
s 00011/00000/00000
d D 1.1 86/07/02 15:58:56 sam 1 0
c date and time created 86/07/02 15:58:56 by sam
e
u
U
t
T
I 1
D 3
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS
E 3
I 3
/*
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 3

/* hostorder = ntohs(netorder) */

#include "DEFS.h"

D 2
ENTRY(ntohs)
E 2
I 2
ENTRY(ntohs, 0)
E 2
	movzwl	6(fp),r0
	ret
E 1
