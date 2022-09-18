h37204
s 00002/00002/00018
d D 8.1 93/06/04 12:39:02 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00018
d D 5.4 91/04/12 12:39:14 bostic 4 3
c SCCS id got lost along the way
e
s 00007/00008/00013
d D 5.3 90/12/17 15:14:03 william 3 2
c turn C files into asm form due to obnoxious gcc "template" bug
e
s 00001/00001/00018
d D 5.2 90/05/14 15:16:08 karels 2 1
c Release 0.1 changes
e
s 00019/00000/00000
d D 5.1 90/04/23 19:57:00 william 1 0
c date and time created 90/04/23 19:57:00 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1991 The Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 4
	.asciz "@(#)fixdfsi.s	5.1 (Berkeley) 5/15/90"
E 4
I 4
	.asciz "%W% (Berkeley) %G%"
E 4
E 3
#endif /* LIBC_SCCS and not lint */

D 3
__fixdfsi(d)
double d;
{
	int val;
D 2
	asm("fistl %0" : "=g" (val) : "f" (d) );
E 2
I 2
	asm("fldl %1 ; fistpl %0" : "=g" (val) : "g" (d) );
E 2
	return(val);
}
E 3
I 3
	.globl ___fixdfsi
___fixdfsi:
	fldl	4(%esp)
	fistpl	4(%esp)
	movl	4(%esp),%eax
	ret
E 3
E 1
