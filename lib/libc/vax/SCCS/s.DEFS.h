h23276
s 00002/00002/00033
d D 8.1 93/06/04 16:14:31 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00034
d D 5.3 90/06/01 14:45:36 bostic 6 5
c new copyright notice
e
s 00014/00003/00031
d D 5.2 89/02/15 13:56:32 bostic 5 4
c add Berkeley specific copyright notice
e
s 00007/00001/00027
d D 5.1 85/05/30 15:05:47 dist 4 3
c Add copyright
e
s 00024/00007/00004
d D 4.3 84/11/01 23:51:02 sam 3 2
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00003/00000/00008
d D 4.2 83/06/27 19:52:37 root 2 1
c need assembler entry point
e
s 00008/00000/00000
d D 4.1 82/12/15 15:33:46 sam 1 0
c date and time created 82/12/15 15:33:46 by sam
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
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 7
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 *
 *	%W% (Berkeley) %G%
 */
E 4
E 3

I 3
#define R0	0x001
#define R1	0x002
#define R2	0x004
#define R3	0x008
#define R4	0x010
#define R5	0x020
#define R6	0x040
#define	R7 	0x080
#define	R8	0x100
#define	R9	0x200
#define	R10	0x400
#define	R11	0x800

E 3
#ifdef PROF
D 3
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
I 2
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
E 3
I 3
#define	ENTRY(x, regs) \
	.globl _/**/x; .align 2; _/**/x: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
E 3
E 2
#else
D 3
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0
I 2
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0
E 3
I 3
#define	ENTRY(x, regs) \
	.globl _/**/x; .align 2; _/**/x: .word regs
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs
E 3
E 2
#endif
E 1
