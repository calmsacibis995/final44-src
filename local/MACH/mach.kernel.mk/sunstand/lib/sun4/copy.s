/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	copy.s,v $
 * Revision 2.2  89/07/12  00:24:25  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)copy.s 1.2 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
 	.seg	"text"
 	.align	4
/*
 * optimized bcopy and bzero for space
 */
	.global	_bzero
1:
	add	%o0,1,%o0	! point at next byte to clear
_bzero:
	subcc	%o1,1,%o1	! done yet?
	bge,a	1b		! loop till done
	clrb	[%o0]		! clear a byte in delay slot
leafout:
	retl			! leaf routine return
	.empty			! allow next instruction in delay slot

	.global	_bcopy
1:
	inc	%o0		! inc from address
	stb	%o4, [%o1]	! write to address
	inc	%o1		! delay slot, inc to address
_bcopy:
	subcc	%o2,1,%o2	! dec count
	bge,a	1b		! loop till done
	ldub	[%o0], %o4	! read from address
	b,a	leafout		! go do a leaf routine return
