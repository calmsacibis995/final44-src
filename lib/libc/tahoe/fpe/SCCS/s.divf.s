h59675
s 00002/00002/00086
d D 8.1 93/06/04 13:14:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00087
d D 1.3 90/06/01 14:48:20 bostic 3 2
c new copyright notice
e
s 00023/00003/00075
d D 1.2 89/02/17 17:35:36 bostic 2 1
c add Berkeley specific copyright notice
e
s 00078/00000/00000
d D 1.1 86/07/02 16:25:52 sam 1 0
c date and time created 86/07/02 16:25:52 by sam
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

#define	HIDDEN	23	/* here we count from 0 not from 1 as in fp.h */

XENTRY(divf, R2|R3|R4|R5|R6|R7|R8|R9)
	clrl	r1
	clrl	r3		# r3 - sign: 0 for positive,1 for negative.
	movl	4(fp),r0
	jgeq	1f
	movl	$1,r3
1:	movl	12(fp),r2
	jgeq	2f
	bbc	$0,r3,1f	# seconed operand is negative.
	clrl	r3		# if first was negative, make result positive.
	jmp	2f
1:	movl	$1,r3		# if first was positive, make result negative.
2:	andl2	$EXPMASK,r0	# compute first 'pure'exponent.
	jeql	is_res1
	shrl	$EXPSHIFT,r0,r0
	subl2	$BIAS,r0	
	andl2	$EXPMASK,r2	# compute seconed 'pure'exponent.
	jeql	is_res2
	shrl	$EXPSHIFT,r2,r2
	subl2	$BIAS,r2
	subl3	r2,r0,r2	# subtruct the exponents.
	addl2	$BIAS,r2
	jleq	underf
				# normalization can make the exp. smaller.
 #
 #	We have the sign in r3,the exponent in r2,now is the time to
 # 	perform the division...
 #
	# fetch dividend. (r0)
	andl3	$(0!(EXPMASK | SIGNBIT)),4(fp),r0
	orl2	$(0!CLEARHID),r0
	clrl	r1
 
	# fetch divisor : (r6)
	andl3	$(0!(EXPMASK | SIGNBIT)),12(fp),r6
	orl2	$(0!CLEARHID),r6

	shll	$2,r6,r6	# make the divisor bigger so we will not
				# get overflow at the divission.
	ediv	r6,r0,r0,r7	# quo to r0, rem to r7
	subl2	$6,r2		# to compensate for: normalization (-24),
				# ediv (+32), shifting r6 (-2).
	
over:
	callf	$4,fnorm	# we can use fnorm because we have data
				# at r1 as well.(sfnorm takes care only 
				# of r0).
sign:
1:	bbc	$0,r3,done
	orl2	$SIGNBIT,r0
done:	ret

is_res1:
	bbc 	$31,4(fp),retz
	callf	$4,sfpresop
	ret
is_res2:
	bbc 	$31,12(fp),z_div
	callf	$4,sfpresop
	ret
retz:
	  clrl	r0
	  ret
underf:
	callf	$4,sfpunder
	ret
z_div:
	callf	$4,sfpzdiv
	ret
E 1
