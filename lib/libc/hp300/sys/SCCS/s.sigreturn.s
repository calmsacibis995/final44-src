h58826
s 00002/00002/00043
d D 8.1 93/06/04 12:36:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00001/00030
d D 5.2 93/05/03 16:17:54 hibler 2 1
c add STDC versions for both gcc1 and gcc2, eliminate non-gcc versions
e
s 00031/00000/00000
d D 5.1 90/05/12 16:51:55 bostic 1 0
c date and time created 90/05/12 16:51:55 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

/*
 * We must preserve the state of the registers as the user has set them up.
 */
#ifdef PROF
#undef ENTRY
I 2
#ifdef __STDC__
#if __GNUC__ >= 2
E 2
#define	ENTRY(x) \
I 2
	.globl _ ## x; .even; _ ## x:; moveml \#0xC0C0,sp@-; .data; \
	PROF ## x:; .long 0; .text; lea PROF ## x,a0; jbsr mcount; \
	moveml sp@+,\#0x0303
#else
#define	ENTRY(x) \
	.globl _ ## x; .even; _ ## x:; moveml #0xC0C0,sp@-; .data; \
	PROF ## x:; .long 0; .text; lea PROF ## x,a0; jbsr mcount; \
	moveml sp@+,#0x0303
#endif
#else
#define	ENTRY(x) \
E 2
	.globl _/**/x; .even; _/**/x:; moveml #0xC0C0,sp@-; .data; \
	PROF/**/x:; .long 0; .text; lea PROF/**/x,a0; jbsr mcount; \
	moveml sp@+,#0x0303
D 2
#endif PROF
E 2
I 2
#endif
#endif
E 2

ENTRY(sigreturn)
	trap	#1		/* signals sigreturn() */
	jmp	cerror
E 1
