h29176
s 00002/00002/00033
d D 8.1 93/06/04 13:15:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00034
d D 1.3 90/06/01 14:49:07 bostic 3 2
c new copyright notice
e
s 00023/00003/00022
d D 1.2 89/02/17 17:35:45 bostic 2 1
c add Berkeley specific copyright notice
e
s 00025/00000/00000
d D 1.1 86/07/02 16:25:55 sam 1 0
c date and time created 86/07/02 16:25:55 by sam
e
u
U
t
T
I 1
D 2
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS
E 2
I 2
/*
D 4
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 3
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 2

#include <tahoemath/fp.h>
#include "DEFS.h"

XENTRY(negd, 0)
	andl3	$EXPMASK,4(fp),r0	/* check for reserved operand,zero. */
	beql	isreserved
	movl	4(fp),r0		/* fetch operand. */
	movl	8(fp),r1
	bbc	$31,r0,seton
	andl2	$(0!SIGNBIT),r0		/* turn it off. */
	ret
seton:	orl2	$SIGNBIT,r0		/* turn it on. */
	ret
isreserved:
	bbc	$31,4(fp),retzero
	callf	$4,fpresop
	ret
retzero:
	clrl	r0
	clrl	r1
	ret
E 1
