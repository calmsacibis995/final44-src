h16598
s 00002/00002/00080
d D 8.1 93/06/04 13:02:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00033/00053
d D 5.2 92/07/06 17:27:37 torek 2 1
c use proper entry protocol
e
s 00086/00000/00000
d D 5.1 92/06/25 06:34:22 torek 1 0
c date and time created 92/06/25 06:34:22 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: $Header: ffs.s,v 1.1 91/07/07 05:29:48 torek Exp $
E 2
I 2
 * from: $Header: ffs.s,v 1.3 92/07/07 00:23:57 torek Exp $
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif  /* LIBC_SCCS and not lint */

I 2
#include "DEFS.h"

E 2
/*
 * ffs returns the number of the rightmost bit set in its argument,
 * i.e., the lowest value such that (x & (ffs(x) - 1)) is nonzero.
 * If no bits are set, ffs returns 0.
 *
D 2
 * We use a table lookup, one byte at a time.
 * Note that the table has a special value in slot 0.
 */

ffstab:
	.byte	-24,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1 /* 00-0f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 10-1f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 20-2f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 30-3f */
	.byte	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 40-4f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 50-5f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 60-6f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 70-7f */
	.byte	8,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 80-8f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 10-9f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* a0-af */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* b0-bf */
	.byte	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* c0-cf */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* d0-df */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* e0-ef */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* f0-ff */

/*
E 2
 * We use a table lookup on each byte.
 *
 * In each section below, %o1 is the current byte (0, 1, 2, or 3).
 * The last byte is handled specially: for the first three,
 * if that byte is nonzero, we return the table value
 * (plus 0, 8, or 16 for the byte number), but for the last
 * one, we just return the table value plus 24.  This means
 * that ffstab[0] must be -24 so that ffs(0) will return 0.
 */
D 2
	.global	_ffs
_ffs:
E 2
I 2
ENTRY(ffs)
E 2
	set	ffstab, %o2
	andcc	%o0, 0xff, %o1	! get low byte
	be,a	1f		! try again if 0
D 2
	srl	%o0, 8, %o0	! delay slot, get ready for next byte
E 2
I 2
	 srl	%o0, 8, %o0	! delay slot, get ready for next byte
E 2

	retl			! return ffstab[%o1]
D 2
	ldsb	[%o2 + %o1], %o0
E 2
I 2
	 ldsb	[%o2 + %o1], %o0
E 2

1:
	andcc	%o0, 0xff, %o1	! byte 1 like byte 0...
	be,a	2f
D 2
	srl	%o0, 8, %o0	! (use delay to prepare for byte 2)
E 2
I 2
	 srl	%o0, 8, %o0	! (use delay to prepare for byte 2)
E 2

	ldsb	[%o2 + %o1], %o0
	retl			! return ffstab[%o1] + 8
D 2
	add	%o0, 8, %o0
E 2
I 2
	 add	%o0, 8, %o0
E 2

2:
	andcc	%o0, 0xff, %o1
	be,a	3f
D 2
	srl	%o0, 8, %o0	! (prepare for byte 3)
E 2
I 2
	 srl	%o0, 8, %o0	! (prepare for byte 3)
E 2

	ldsb	[%o2 + %o1], %o0
	retl			! return ffstab[%o1] + 16
D 2
	add	%o0, 16, %o0
E 2
I 2
	 add	%o0, 16, %o0
E 2

3:				! just return ffstab[%o0] + 24
	ldsb	[%o2 + %o0], %o0
	retl
D 2
	add	%o0, 24, %o0
E 2
I 2
	 add	%o0, 24, %o0

ffstab:
	.byte	-24,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1 /* 00-0f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 10-1f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 20-2f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 30-3f */
	.byte	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 40-4f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 50-5f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 60-6f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 70-7f */
	.byte	8,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 80-8f */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* 10-9f */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* a0-af */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* b0-bf */
	.byte	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* c0-cf */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* d0-df */
	.byte	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* e0-ef */
	.byte	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1	/* f0-ff */
E 2
E 1
