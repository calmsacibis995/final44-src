h24674
s 00002/00002/00029
d D 8.1 93/06/04 12:41:58 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00030
d D 5.6 91/07/15 09:17:22 bostic 6 5
c syscall is in /sys/sys, not /usr/include
e
s 00002/00001/00029
d D 5.5 91/05/07 14:04:13 bostic 5 4
c can't add ret to SYSCALL, expected to fall through; add RSYSCALL
e
s 00002/00002/00028
d D 5.4 91/04/28 15:08:17 torek 4 3
c make SYSCALL and PSEUDO do the return
e
s 00002/00002/00028
d D 5.3 90/12/17 14:59:15 william 3 2
c .align BEFORE symbol def, not after, only do word align
e
s 00002/00000/00028
d D 5.2 90/05/30 12:19:29 bostic 2 1
c add ASMSTR #define
e
s 00029/00000/00000
d D 5.1 90/04/23 19:38:28 william 1 0
c date and time created 90/04/23 19:38:28 by william
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 6
#include <syscall.h>
E 6
I 6
#include <sys/syscall.h>
E 6

#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; \
D 3
			.data; 1:; .long 0; .text; _/**/x:	.align 4; \
E 3
I 3
			.data; 1:; .long 0; .text; .align 2; _/**/x: \
E 3
			movl $1b,%eax; call mcount
#else
D 3
#define	ENTRY(x)	.globl _/**/x; .text; .align 4; _/**/x: 
E 3
I 3
#define	ENTRY(x)	.globl _/**/x; .text; .align 2; _/**/x: 
E 3
#endif PROF
D 4
#define	SYSCALL(x)	2: jmp cerror; ENTRY(x); lea SYS_/**/x,%eax; LCALL(7,0); jb 2b
#define	PSEUDO(x,y)	ENTRY(x); lea SYS_/**/y, %eax; ; LCALL(7,0)
E 4
I 4
D 5
#define	SYSCALL(x)	2: jmp cerror; ENTRY(x); lea SYS_/**/x,%eax; LCALL(7,0); jb 2b; ret
E 5
I 5
#define	SYSCALL(x)	2: jmp cerror; ENTRY(x); lea SYS_/**/x,%eax; LCALL(7,0); jb 2b
#define	RSYSCALL(x)	SYSCALL(x); ret
E 5
#define	PSEUDO(x,y)	ENTRY(x); lea SYS_/**/y, %eax; ; LCALL(7,0); ret
E 4
#define	CALL(x,y)	call _/**/y; addl $4*x,%esp
/* gas fucks up offset -- although we don't currently need it, do for BCS */
#define	LCALL(x,y)	.byte 0x9a ; .long y; .word x

I 2
#define	ASMSTR		.asciz

E 2
	.globl	cerror
E 1
