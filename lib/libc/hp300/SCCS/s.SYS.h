h21873
s 00002/00002/00050
d D 8.1 93/06/04 12:13:43 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00009/00026
d D 5.6 93/05/03 16:10:54 hibler 6 5
c add STDC versions for both gcc1 and gcc2, eliminate non-gcc versions
e
s 00002/00001/00033
d D 5.5 91/05/07 14:02:01 bostic 5 4
c can't add rts to SYSCALL, expected to fall through; add RSYSCALL
e
s 00002/00007/00032
d D 5.4 91/04/28 15:09:52 bostic 4 3
c make SYSCALL and PSEUDO do the return
e
s 00002/00000/00037
d D 5.3 90/05/30 12:19:06 bostic 3 2
c add ASMSTR #define
e
s 00001/00001/00036
d D 5.2 90/05/26 11:54:58 bostic 2 1
c add .even to guarantee jmp instruction is on even address
e
s 00037/00000/00000
d D 5.1 90/05/12 16:51:29 bostic 1 0
c date and time created 90/05/12 16:51:29 by bostic
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/syscall.h>

I 6
#ifdef __STDC__
E 6
D 4
/* vax/tahoe compat */
#define	ret	rts
#define	r0	d0
#define	r1	d1

E 4
#ifdef PROF
D 6
#ifdef __GNUC__
#define	ENTRY(x)	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; \
			.long 0; .text; link a6,#0; lea PROF/**/x,a0; \
E 6
I 6
#if __GNUC__ >= 2
#define	ENTRY(x)	.globl _ ## x; .even; _ ## x:; .data; PROF ## x:; \
			.long 0; .text; link a6,\#0; lea PROF ## x,a0; \
E 6
			jbsr mcount; unlk a6
#else
D 6
#define	ENTRY(x)	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; \
			.long 0; .text; lea PROF/**/x,a0; jbsr mcount
E 6
I 6
#define	ENTRY(x)	.globl _ ## x; .even; _ ## x:; .data; PROF ## x:; \
			.long 0; .text; link a6,#0; lea PROF ## x,a0; \
			jbsr mcount; unlk a6
E 6
#endif
#else
I 6
#define	ENTRY(x)	.globl _ ## x; .even; _ ## x:
#endif
#if __GNUC__ >= 2
#define SYSTRAP(x)	movl \#SYS_ ## x,d0; trap \#0
#else
#define SYSTRAP(x)	movl #SYS_ ## x,d0; trap #0
#endif
#else
#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; .even; _/**/x:; .data; PROF/**/x:; \
			.long 0; .text; link a6,#0; lea PROF/**/x,a0; \
			jbsr mcount; unlk a6
#else
E 6
#define	ENTRY(x)	.globl _/**/x; .even; _/**/x:
D 6
#endif PROF
D 2
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); movl #SYS_/**/x,d0; \
E 2
I 2
#define	SYSCALL(x)	.even; err: jmp cerror; ENTRY(x); movl #SYS_/**/x,d0; \
E 2
D 4
			trap #0; jcs err
#define	PSEUDO(x,y)	ENTRY(x); movl #SYS_/**/y,d0; trap #0;
E 4
I 4
D 5
			trap #0; jcs err; rts
E 5
I 5
			trap #0; jcs err
E 6
I 6
#endif
#define SYSTRAP(x)	movl #SYS_/**/x,d0; trap #0
#endif

#define	SYSCALL(x)	.even; err: jmp cerror; ENTRY(x); SYSTRAP(x); jcs err
E 6
#define	RSYSCALL(x)	SYSCALL(x); rts
E 5
D 6
#define	PSEUDO(x,y)	ENTRY(x); movl #SYS_/**/y,d0; trap #0; rts
E 6
I 6
#define	PSEUDO(x,y)	ENTRY(x); SYSTRAP(y); rts
E 6
E 4

I 3
#define	ASMSTR		.asciz

E 3
	.globl	cerror
E 1
