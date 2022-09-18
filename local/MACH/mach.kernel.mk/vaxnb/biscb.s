/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	biscb.s,v $
 * Revision 2.3  89/02/26  10:58:04  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:45:34  rvb
 * 	Created.  Actually created very long ago and we could(should!) do
 * 	all this BI vector stuff better.  I know how just need some time.
 * 
 */

#if	NBI > 0

#include <vaxnb/biasm.h>

	.globl	_biscb
_biscb:
/*000*/	BI0(0)  BI0(1)  BI0(2)  BI0(3)  BI0(4)  BI0(5)  BI0(6)  BI0(7) 
	BI0(8)  BI0(9)  BI0(a)  BI0(b)  BI0(c)  BI0(d)  BI0(e)  BI0(f) 

/*040*/	BI1(0)  BI1(1)  BI1(2)  BI1(3)  BI1(4)  BI1(5)  BI1(6)  BI1(7) 
	BI1(8)  BI1(9)  BI1(a)  BI1(b)  BI1(c)  BI1(d)  BI1(e)  BI1(f) 

/*080*/	BI2(0)  BI2(1)  BI2(2)  BI2(3)  BI2(4)  BI2(5)  BI2(6)  BI2(7) 
	BI2(8)  BI2(9)  BI2(a)  BI2(b)  BI2(c)  BI2(d)  BI2(e)  BI2(f) 

/*0c0*/	BI3(0)  BI3(1)  BI3(2)  BI3(3)  BI3(4)  BI3(5)  BI3(6)  BI3(7) 
	BI3(8)  BI3(9)  BI3(a)  BI3(b)  BI3(c)  BI3(d)  BI3(e)  BI3(f) 
#if	VAX6200
/*100*/	 XMI0	XMI1	XMI2	XMI3
	.space 0x100 - 4*4
#else	VAX6200
/*100*/	.space 0x100
#endif	VAX6200
/*200*/

#if	VAX6200
#undef	XMI0
#undef	XMI0_GLUE
#undef	XMI1
#undef	XMI1_GLUE
#undef	XMI2
#undef	XMI2_GLUE
#undef	XMI3
#undef	XMI3_GLUE
#endif	VAX6200

#undef	BI0
#undef	BI0_GLUE
#undef	BI1
#undef	BI1_GLUE
#undef	BI2
#undef	BI2_GLUE
#undef	BI3
#undef	BI3_GLUE

#endif	NBI > 0
