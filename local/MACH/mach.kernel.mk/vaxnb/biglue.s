/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	biglue.s,v $
 * Revision 2.3  89/02/26  10:57:58  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:45:05  rvb
 * Created.  Actually created very long ago and we could(should!) do
 * all this BI vector stuff better.  I know how just need some time.
 * 
 */

#if	NBI > 0

#include <vaxnb/biasm.h>

BI0_GLUE(0)  BI0_GLUE(1)  BI0_GLUE(2)  BI0_GLUE(3) 
BI0_GLUE(4)  BI0_GLUE(5)  BI0_GLUE(6)  BI0_GLUE(7) 
BI0_GLUE(8)  BI0_GLUE(9)  BI0_GLUE(a)  BI0_GLUE(b) 
BI0_GLUE(c)  BI0_GLUE(d)  BI0_GLUE(e)  BI0_GLUE(f) 

BI1_GLUE(0)  BI1_GLUE(1)  BI1_GLUE(2)  BI1_GLUE(3) 
BI1_GLUE(4)  BI1_GLUE(5)  BI1_GLUE(6)  BI1_GLUE(7) 
BI1_GLUE(8)  BI1_GLUE(9)  BI1_GLUE(a)  BI1_GLUE(b) 
BI1_GLUE(c)  BI1_GLUE(d)  BI1_GLUE(e)  BI1_GLUE(f) 

BI2_GLUE(0)  BI2_GLUE(1)  BI2_GLUE(2)  BI2_GLUE(3) 
BI2_GLUE(4)  BI2_GLUE(5)  BI2_GLUE(6)  BI2_GLUE(7) 
BI2_GLUE(8)  BI2_GLUE(9)  BI2_GLUE(a)  BI2_GLUE(b) 
BI2_GLUE(c)  BI2_GLUE(d)  BI2_GLUE(e)  BI2_GLUE(f) 

BI3_GLUE(0)  BI3_GLUE(1)  BI3_GLUE(2)  BI3_GLUE(3) 
BI3_GLUE(4)  BI3_GLUE(5)  BI3_GLUE(6)  BI3_GLUE(7) 
BI3_GLUE(8)  BI3_GLUE(9)  BI3_GLUE(a)  BI3_GLUE(b) 
BI3_GLUE(c)  BI3_GLUE(d)  BI3_GLUE(e)  BI3_GLUE(f) 

BI_ERR:
	subl2	$8, sp
	movl	4*9(sp), 0(sp)		/* pc */
	movl	4*10(sp), 4(sp)	/* psl */
	calls	$3, _bi_err
	TSREI_POPR

BI_ERR_STRAY:
	TIM_PUSHR(0); mfpr $IPL,-(sp); PRINTF(1, "stray bi error intr ipl%x\n"); TSREI_POPR

#if	VAX6200
XMI0_GLUE     XMI1_GLUE	  XMI2_GLUE     XMI3_GLUE

XMI_ERR:
	subl2	$8, sp
	movl	4*9(sp), 0(sp)		/* pc */
	movl	4*10(sp), 4(sp)	/* psl */
	calls	$3, _xmi_err
	TSREI_POPR

XMI_ERR_STRAY:
	TIM_PUSHR(0); mfpr $IPL,-(sp); PRINTF(1, "stray xmi error intr ipl%x\n"); TSREI_POPR

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
