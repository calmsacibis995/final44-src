h18341
s 00002/00002/00032
d D 8.1 93/06/04 12:39:05 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 90/12/17 15:12:42 william 1 0
c date and time created 90/12/17 15:12:42 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W%	%G%"
#endif /* LIBC_SCCS and not lint */

	.globl ___fixunsdfsi
___fixunsdfsi:
	fldl	4(%esp)		/* argument double to accum stack */
	frndint			/* create integer */
	fcoml	fbiggestsigned	/* bigger than biggest signed? */
	fstsw	%ax
	sahf
	jnb	1f
	
	fistpl	4(%esp)
	movl	4(%esp),%eax
	ret

1:	fsubl	fbiggestsigned	/* reduce for proper conversion */
	fistpl	4(%esp)		/* convert */
	movl	4(%esp),%eax
	orl	$0x80000000,%eax	/* restore bias */
	ret

fbiggestsigned:	.double	0r2147483648.0
E 1
