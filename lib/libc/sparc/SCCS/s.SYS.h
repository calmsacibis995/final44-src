h57119
s 00002/00002/00060
d D 8.1 93/06/04 13:02:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00056
d D 5.3 92/07/09 19:30:44 torek 3 2
c switch to %g2. maybe we should give in and use %o7+8
e
s 00007/00000/00053
d D 5.2 92/06/25 06:01:13 torek 2 1
c copyright
e
s 00053/00000/00000
d D 5.1 92/06/25 05:58:24 torek 1 0
c date and time created 92/06/25 05:58:24 by torek
e
u
U
t
T
I 1
/*-
I 2
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
 * from: $Header: SYS.h,v 1.2 92/07/03 18:57:00 torek Exp $
E 3
 */

#include <sys/syscall.h>
#include <machine/trap.h>

#ifdef PROF
#define	ENTRY(x) \
	.align 4; .globl _##x; .proc 1; _##x:; .data; .align 4; 1: .long 0; \
	.text; save %sp,-96,%sp; sethi %hi(1b),%o0; call mcount; \
	or %o0,%lo(1b),%o0; restore
#else
#define	ENTRY(x) \
	.align 4; .globl _##x; .proc 1; _##x:
#endif

/*
 * ERROR branches to cerror.  This is done with a macro so that I can
 * change it to be position independent later, if need be.
 */
#define	ERROR() \
	sethi %hi(cerror),%g1; or %lo(cerror),%g1,%g1; jmp %g1; nop

/*
 * SYSCALL is used when further action must be taken before returning.
 * Note that it adds a `nop' over what we could do, if we only knew what
 * came at label 1....
 */
#define	SYSCALL(x) \
	ENTRY(x); mov SYS_##x,%g1; t ST_SYSCALL; bcc 1f; nop; ERROR(); 1:

/*
 * RSYSCALL is used when the system call should just return.  Here
D 3
 * we use the SYSCALL_RFLAG to put the `success' return address in %g7
E 3
I 3
 * we use the SYSCALL_G2RFLAG to put the `success' return address in %g2
E 3
 * and avoid a branch.
 */
#define	RSYSCALL(x) \
D 3
	ENTRY(x); mov (SYS_##x)|SYSCALL_RFLAG,%g1; add %o7,8,%g7; \
E 3
I 3
	ENTRY(x); mov (SYS_##x)|SYSCALL_G2RFLAG,%g1; add %o7,8,%g2; \
E 3
	t ST_SYSCALL; ERROR()

/*
D 3
 * PSEUDO(x,y) is like  RSYSCALL(y) except that the name is x.
E 3
I 3
 * PSEUDO(x,y) is like RSYSCALL(y) except that the name is x.
E 3
 */
#define	PSEUDO(x,y) \
D 3
	ENTRY(x); mov (SYS_##y)|SYSCALL_RFLAG,%g1; add %o7,8,%g7; \
E 3
I 3
	ENTRY(x); mov (SYS_##y)|SYSCALL_G2RFLAG,%g1; add %o7,8,%g2; \
E 3
	t ST_SYSCALL; ERROR()

#define	ASMSTR		.asciz

	.globl	cerror
E 1
