h26105
s 00000/00000/00028
d D 4.1 88/12/04 15:11:54 minshall 4 3
c Release 4.1
e
s 00010/00005/00018
d D 1.3 88/06/29 19:49:45 bostic 3 2
c install approved copyright notice
e
s 00011/00001/00012
d D 1.2 88/03/28 12:34:12 bostic 2 1
c add Berkeley specific header
e
s 00013/00000/00000
d D 1.1 86/11/11 22:54:10 minshall 1 0
c date and time created 86/11/11 22:54:10 by minshall
e
u
U
t
T
I 1
/*
D 2
 *	@(#)defs.h	3.1  10/29/86
E 2
I 2
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
 *
 *	%W% (Berkeley) %G%
E 2
 */

#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0
#define	ASENTRY(x)	.globl x; .align 2; x: .word 0
#endif
E 1
