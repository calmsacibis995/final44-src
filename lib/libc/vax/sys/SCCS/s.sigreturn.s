h37144
s 00002/00002/00023
d D 8.1 93/06/04 15:41:29 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00024
d D 5.6 90/06/01 15:11:35 bostic 8 7
c new copyright notice
e
s 00011/00006/00024
d D 5.5 88/06/27 18:22:55 bostic 7 6
c install approved copyright notice
e
s 00010/00004/00020
d D 5.4 88/05/20 17:15:09 bostic 6 5
c add Berkeley specific header
e
s 00002/00002/00022
d D 5.3 86/03/09 21:55:06 donn 5 4
c added SYSLIBC_SCCS condition for sccs ids
e
s 00001/00001/00023
d D 5.2 85/06/05 19:25:06 mckusick 4 3
c Fix copyright
e
s 00009/00001/00015
d D 5.1 85/06/03 10:22:05 dist 3 2
c Add copyright
e
s 00010/00000/00006
d D 4.2 85/05/27 14:21:18 mckusick 2 1
c must save all registers when using profiled routine
e
s 00006/00000/00000
d D 4.1 85/03/11 18:23:01 mckusick 1 0
c date and time created 85/03/11 18:23:01 by mckusick
e
u
U
t
T
I 1
D 3
/* %M% %I% %E% */
E 3
I 3
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
E 3

#include "SYS.h"

I 2
/*
 * We must preserve the state of the registers as the user has set them up.
 */
#ifdef PROF
#undef ENTRY
#define	ENTRY(x) \
	.globl _/**/x; .align 2; _/**/x: .word 0; pushr $0x3f; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount; popr $0x3f
#endif PROF

E 2
SYSCALL(sigreturn)
	ret
E 1
