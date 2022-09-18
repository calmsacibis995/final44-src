h05650
s 00004/00018/00011
d D 5.2 91/04/12 12:37:24 bostic 2 1
c never under SCCS!; check in with new copyright; att/bsd/shared
e
s 00029/00000/00000
d D 5.1 91/04/12 12:35:45 bostic 1 0
c date and time created 91/04/12 12:35:45 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1983 The Regents of the University of California.
E 2
I 2
 * Copyright (c) 1990 The Regents of the University of California.
E 2
 * All rights reserved.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

D 2
#include "SYS.h"

E 2
#if defined(LIBC_SCCS) && !defined(lint)
D 2
	ASMSTR "@(#)_getlogin.s	5.4 (Berkeley) 5/30/90"
E 2
I 2
	.asciz "%W% (Berkeley) %G%"
E 2
#endif /* LIBC_SCCS and not lint */

D 2
/* internal version of getlogin() */
E 2
I 2
#include "SYS.h"
E 2

PSEUDO(_getlogin,getlogin)	/* _getlogin(buf, buflen) */
	ret
E 1
