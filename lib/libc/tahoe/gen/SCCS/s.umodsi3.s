h14784
s 00002/00002/00033
d D 8.1 93/06/04 13:18:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00000/00000
d D 6.1 91/02/01 13:11:55 donn 1 0
c date and time created 91/02/01 13:11:55 by donn
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/*
 * Unsigned remainder for GCC.
 *
 * __umodsi3(dividend, divisor)
 */
#include "DEFS.h"

ENTRY(__umodsi3, 0)
	bitl	$0x80000000,8(fp)	#  if (divisor & 0x80000000){
	jeql	1f			  
	movl	4(fp),r0
	cmpl	8(fp),r0		#  if (divisor <= dividend )
	jgtru	2f
	subl2	8(fp),r0		#       return(dividend-divisor);
2:					#  else return(dividend);}
	ret
1:
	clrl	r2			#  return(dividend%divisor);
	movl	4(fp),r3
	ediv	8(fp),r2,r1,r0
	ret
E 1
