h37434
s 00004/00003/00055
d D 8.4 95/04/28 16:30:15 bostic 14 13
c LONG_MIN and LONG_MAX need suffixes, and ULONG_MAX must either
c be spelled in decimal, or suffixed.
c From: Chris Torek <torek@BSDI.COM>
e
s 00007/00003/00051
d D 8.3 94/01/04 15:11:04 bostic 13 12
c reorder the defines to hopefully get standards conformance right
e
s 00003/00004/00051
d D 8.2 94/01/04 14:56:16 bostic 12 10
c add max value for SSIZE_T_MAX
e
s 00004/00003/00052
d R 8.2 94/01/04 14:05:18 bostic 11 10
c add _POSIX_SSIZE_MAX
e
s 00002/00002/00053
d D 8.1 93/06/10 21:44:47 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00053
d D 7.9 93/05/26 14:00:48 bostic 9 8
c rune support from Paul Borman
e
s 00003/00003/00051
d D 7.8 93/05/21 12:42:52 bostic 8 7
c parenthesize the negative numbers so "256-CHAR_MIN" works
e
s 00004/00003/00050
d D 7.7 93/05/07 09:54:28 bostic 7 6
c shut gcc up about large integer constants
e
s 00007/00000/00046
d D 7.6 92/06/25 08:46:00 bostic 6 5
c add quad constants
e
s 00005/00000/00041
d D 7.5 92/06/24 09:27:47 bostic 5 4
c add #define for max size_t value
e
s 00012/00002/00029
d D 7.4 92/03/09 16:15:28 bostic 4 3
c explain what is really happening
e
s 00014/00014/00017
d D 7.3 92/03/09 14:48:22 bostic 3 2
c from Chris Torek; see ANSI C, section 2.2.4.2.1
e
s 00001/00011/00030
d D 7.2 90/06/28 22:32:52 bostic 2 1
c new copyright notice
e
s 00041/00000/00000
d D 7.1 89/02/15 18:28:51 bostic 1 0
c date and time created 89/02/15 18:28:51 by bostic
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define	CHAR_BIT	8		/* number of bits in a char */
D 4
#define	CLK_TCK		60		/* ticks per second */
E 4
D 9
#define	MB_LEN_MAX	1		/* no multibyte characters */
E 9
I 9
#define	MB_LEN_MAX	6		/* Allow 31 bit UTF2 */

E 9

I 4
#define	CLK_TCK		60		/* ticks per second */

/*
 * According to ANSI (section 2.2.4.2), the values below must be usable by
 * #if preprocessing directives.  Additionally, the expression must have the
 * same type as would an expression that is an object of the corresponding
 * type converted according to the integral promotions.  The subtraction for
 * INT_MIN and LONG_MIN is so the value is not unsigned; 2147483648 is an
 * unsigned int for 32-bit two's complement ANSI compilers (section 3.1.3.2).
D 7
 * These numbers work for pcc as well.
E 7
I 7
 * These numbers work for pcc as well.  The UINT_MAX and ULONG_MAX values
 * are written as hex so that GCC will be quiet about large integer constants.
E 7
 */
E 4
D 3
#define	SCHAR_MIN	0x80		/* max value for a signed char */
#define	SCHAR_MAX	0x7f		/* min value for a signed char */
E 3
I 3
#define	SCHAR_MAX	127		/* min value for a signed char */
D 8
#define	SCHAR_MIN	-128		/* max value for a signed char */
E 8
I 8
#define	SCHAR_MIN	(-128)		/* max value for a signed char */
E 8
E 3

D 3
#define	UCHAR_MAX	0xff		/* max value for an unsigned char */
#define	CHAR_MAX	0x7f		/* max value for a char */
#define	CHAR_MIN	0x80		/* min value for a char */
E 3
I 3
#define	UCHAR_MAX	255		/* max value for an unsigned char */
#define	CHAR_MAX	127		/* max value for a char */
D 4
#define	CHAR_MIN	128		/* min value for a char */
E 4
I 4
D 8
#define	CHAR_MIN	-128		/* min value for a char */
E 8
I 8
#define	CHAR_MIN	(-128)		/* min value for a char */
E 8
E 4
E 3

D 3
#define	USHRT_MAX	0xffff		/* max value for an unsigned short */
#define	SHRT_MAX	0x7fff		/* max value for a short */
#define	SHRT_MIN	0x8000		/* min value for a short */
E 3
I 3
#define	USHRT_MAX	65535		/* max value for an unsigned short */
#define	SHRT_MAX	32767		/* max value for a short */
D 8
#define	SHRT_MIN	-32768		/* min value for a short */
E 8
I 8
#define	SHRT_MIN	(-32768)	/* min value for a short */
E 8
E 3

D 3
#define	UINT_MAX	0xffffffff	/* max value for an unsigned int */
#define	INT_MAX		0x7fffffff	/* max value for an int */
#define	INT_MIN		0x80000000	/* min value for an int */
E 3
I 3
D 7
#define	UINT_MAX	4294967295	/* max value for an unsigned int */
E 7
I 7
#define	UINT_MAX	0xffffffff	/* max value for an unsigned int */
E 7
#define	INT_MAX		2147483647	/* max value for an int */
#define	INT_MIN		(-2147483647-1)	/* min value for an int */
E 3

D 3
#define	ULONG_MAX	0xffffffff	/* max value for an unsigned long */
#define	LONG_MAX	0x7fffffff	/* max value for a long */
#define	LONG_MIN	0x80000000	/* min value for a long */
E 3
I 3
D 7
#define	ULONG_MAX	4294967295	/* max value for an unsigned long */
E 7
I 7
D 14
#define	ULONG_MAX	0xffffffff	/* max value for an unsigned long */
E 7
#define	LONG_MAX	2147483647	/* max value for a long */
#define	LONG_MIN	(-2147483647-1)	/* min value for a long */
E 14
I 14
#define	ULONG_MAX	0xffffffffL	/* max value for an unsigned long */
#define	LONG_MAX	2147483647L	/* max value for a long */
					/* min value for a long */
#define	LONG_MIN	(-2147483647L-1L)
E 14
I 5

D 12
/* Maximum/minimum values for types from <machine/include/ansi.h>. */
E 12
D 13
#ifndef _ANSI_SOURCE
E 13
I 13
#if !defined(_ANSI_SOURCE)
#define	SSIZE_MAX	INT_MAX		/* max value for a ssize_t */

#if !defined(_POSIX_SOURCE)
E 13
I 12
#define	SIZE_T_MAX	UINT_MAX	/* max value for a size_t */
D 13
#define	SSIZE_T_MAX	INT_MAX		/* max value for a ssize_t */
E 13
E 12
I 6

D 12
/* Quad constants must be written as expressions; #define GCC_ME_HARDER. */
E 12
I 12
/* GCC requires that quad constants be written as expressions. */
E 12
#define	UQUAD_MAX	((u_quad_t)0-1)	/* max value for a uquad_t */
					/* max value for a quad_t */
#define	QUAD_MAX	((quad_t)(UQUAD_MAX >> 1))
#define	QUAD_MIN	(-QUAD_MAX-1)	/* min value for a quad_t */
D 12

E 6
#define	SIZE_T_MAX	UINT_MAX
E 12
D 13
#endif
E 13
I 13

#endif /* !_POSIX_SOURCE */
#endif /* !_ANSI_SOURCE */
E 13
E 5
E 3
E 1
