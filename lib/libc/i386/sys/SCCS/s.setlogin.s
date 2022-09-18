h26475
s 00002/00002/00019
d D 8.1 93/06/04 12:42:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00015/00018
d D 5.2 91/04/12 12:42:47 bostic 2 1
c no SCCS id!!; new copyright; att/bsd/shared
e
s 00033/00000/00000
d D 5.1 91/04/12 12:42:01 bostic 1 0
c date and time created 91/04/12 12:42:01 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1991 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
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

#if defined(LIBC_SCCS) && !defined(lint)
D 2
	.asciz "@(#)setlogin.s	5.1 (Berkeley) 5/12/90"
E 2
I 2
	.asciz "%W% (Berkeley) %G%"
E 2
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

.globl	__logname_valid		/* in getlogin() */

SYSCALL(setlogin)
	movl	$0,__logname_valid
	ret				/* setlogin(name) */
E 1
