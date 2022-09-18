h43422
s 00002/00002/00023
d D 8.1 93/06/04 13:13:24 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00023
d D 5.8 91/05/07 14:05:19 bostic 8 7
c can't add ret to SYSCALL, expected to fall through; add RSYSCALL
e
s 00003/00002/00022
d D 5.7 91/04/28 15:05:58 torek 7 6
c make SYSCALL and PSEUDO do the return
e
s 00001/00011/00023
d D 5.6 90/06/01 14:45:26 bostic 6 5
c new copyright notice
e
s 00002/00000/00032
d D 5.5 90/05/30 12:20:02 bostic 5 4
c add ASMSTR #define
e
s 00010/00005/00022
d D 5.4 88/06/27 18:28:52 bostic 4 3
c install approved copyright notice
e
s 00008/00002/00019
d D 5.3 88/05/20 15:27:31 bostic 3 2
c add Berkeley specific header
e
s 00001/00001/00020
d D 5.2 88/05/19 13:50:36 bostic 2 1
c move syscall.h to /sys/h
e
s 00021/00000/00000
d D 5.1 86/07/02 16:22:57 sam 1 0
c date and time created 86/07/02 16:22:57 by sam
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
I 6
 * %sccs.include.redist.c%
E 6
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include <syscall.h>
E 2
I 2
#include <sys/syscall.h>
E 2

#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0; \
			.data; 1:; .long 0; .text; pushl $1b; callf $8,mcount
#else
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0
#endif PROF
D 7
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); kcall $SYS_/**/x; jcs err
#define	PSEUDO(x,y)	ENTRY(x); kcall $SYS_/**/y
E 7
I 7
D 8
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); kcall $SYS_/**/x; jcs err; \
			ret
E 8
I 8
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); kcall $SYS_/**/x; jcs err
#define	RSYSCALL(x)	SYSCALL(x); ret
E 8
#define	PSEUDO(x,y)	ENTRY(x); kcall $SYS_/**/y; ret
E 7
#define	CALL(x,y)	calls $x, _/**/y

I 5
#define	ASMSTR		.asciz

E 5
	.globl	cerror
E 1
