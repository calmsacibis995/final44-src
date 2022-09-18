h12022
s 00002/00002/00034
d D 8.1 93/06/04 13:18:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 6.1 91/02/01 13:13:32 donn 1 0
c date and time created 91/02/01 13:13:32 by donn
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
 * Unsigned divide for GCC.
 *
 * __udivsi3(dividend, divisor)
 */
#include "DEFS.h"

ENTRY(__udivsi3, 0)
	bitl	$0x80000000,8(fp)	#  if (divisor & 0x80000000){
	jeql	1f			  
	cmpl	8(fp),4(fp)		#  if (divisor > dividend )
	jlequ	2f
	clrl	r0			#      return(0);
	ret
2:					#  else
	movl	$1,r0			#      return(1);}
	ret
1:
	clrl	r2			#  return(dividend/divisor);
	movl	4(fp),r3
	ediv	8(fp),r2,r0,r1
	ret
E 1
