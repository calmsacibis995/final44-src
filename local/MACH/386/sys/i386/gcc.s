/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	gcc.s,v $
 * Revision 2.1.1.2  90/02/28  15:47:46  rvb
 * 	Wheeze'ified [kupfer]
 * 
 * 	  Revision 2.1.1.1  89/12/21  17:58:40  rvb
 * 
 *	  Replacement for gnulib calls made from kernel.
 *     
 * 20-Dec-89  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created.
 */

#include <machine/asm.h>

#ifdef	wheeze
#define DIV(op,divisor) \
	op	divisor
#else	wheeze
#define DIV(op,divisor) \
	op	divisor, %eax
#endif	wheeze

ENTRY(__divsi3)
	movl	4(%esp), %eax
#ifdef	wheeze
	cltd
#else	wheeze
	cdq
#endif	wheeze
	DIV(idivl, 8(%esp))
	ret

ENTRY(__udivsi3)
	movl	4(%esp), %eax
	xorl	%edx, %edx
	DIV(divl, 8(%esp))
	ret

