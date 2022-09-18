h41728
s 00002/00002/00047
d D 8.1 93/06/04 12:39:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00047
d D 5.5 91/03/18 18:44:22 bostic 5 4
c use right sccs strings
e
s 00001/00001/00048
d D 5.4 91/03/16 20:48:18 bostic 4 3
c restore sccs id string
e
s 00000/00008/00049
d D 5.3 91/03/16 20:47:27 bostic 3 2
c remove /APP, /NO_APP
e
s 00035/00014/00022
d D 5.2 90/12/17 15:14:04 william 2 1
c turn C files into asm form due to obnoxious gcc "template" bug
e
s 00033/00000/00000
d D 5.1 90/04/23 19:57:05 william 1 0
c date and time created 90/04/23 19:57:05 by william
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Sean Eric Fagan
E 5
I 5
 * Sean Eric Fagan.
E 5
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 4
.asciz  "@(#)modf.c	5.1 (Berkeley) 4/23/90"
E 4
I 4
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
	.asciz "%W% (Berkeley) %G%"
E 5
E 4
E 2
#endif /* LIBC_SCCS and not lint */

/*
 * modf(value, iptr): return fractional part of value, and stores the
 * integral part into iptr (a pointer to double).
 *
 * Written by Sean Eric Fagan (sef@kithrup.COM)
 * Sun Mar 11 20:27:30 PST 1990
 */

/* With CHOP mode on, frndint behaves as TRUNC does.  Useful. */
D 2
double
modf(double value, double *iptr)
{
	double temp;
	short i87flag, i87temp;
	__asm ("fnstcw %0" : "=g" (i87flag) : );
	i87temp = i87flag | 0xc00 ; /* turn on chop mode [truncation] */
	__asm ("fldcw %0" : : "g" (i87temp));
	__asm ("frndint" : "=f" (temp) : "0" (value)); /* temp = int of value */
	__asm ("fldcw %0" : : "g" (i87flag));
	*iptr = temp;
	return (value - temp);
}
E 2
I 2
.text
.globl _modf
_modf:
	pushl %ebp
	movl %esp,%ebp
	subl $16,%esp
D 3
/APP
E 3
	fnstcw -12(%ebp)
D 3
/NO_APP
E 3
	movw -12(%ebp),%dx
	orw $3072,%dx
	movw %dx,-16(%ebp)
D 3
/APP
E 3
	fldcw -16(%ebp)
D 3
/NO_APP
E 3
	fldl 8(%ebp)
D 3
/APP
E 3
	frndint
D 3
/NO_APP
E 3
	fstpl -8(%ebp)
D 3
/APP
E 3
	fldcw -12(%ebp)
D 3
/NO_APP
E 3
	movl 16(%ebp),%eax
	movl -8(%ebp),%edx
	movl -4(%ebp),%ecx
	movl %edx,(%eax)
	movl %ecx,4(%eax)
	fldl 8(%ebp)
	fsubl -8(%ebp)
	jmp L1
L1:
	leave
	ret
E 2
E 1
