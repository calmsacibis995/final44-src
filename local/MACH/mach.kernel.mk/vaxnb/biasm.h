/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	biasm.h,v $
 * Revision 2.4  89/03/09  22:30:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  10:57:42  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:42:56  rvb
 * 	Created.  Actually created very long ago and we could(should!) do
 * 	all this BI vector stuff better.  I know how just need some time.
 *
 */

#if	NBI > 0
#define XMI0		.long XMI_ERR0;
#define XMI0_GLUE	.align 2; XMI_ERR0: TIM_PUSHR(0); pushl $0; brw XMI_ERR;
#define BI0(node)	.long BI0_ERR/**/node;
#define BI0_GLUE(node)	.align 2; BI0_ERR/**/node: TIM_PUSHR(0); pushl $((0<<4)|0x/**/node); brw BI_ERR;
#else	NBI > 0
#define XMI0		.long XMI_ERR_STRAY
#define XMI0_GLUE
#define BI0(node)	.long BI_ERR_STRAY;
#define BI0_GLUE(node)
#endif	NBI > 0

#if	NBI > 1
#define XMI1		.long XMI_ERR1;
#define XMI1_GLUE	.align 2; XMI_ERR1: TIM_PUSHR(0); pushl $1; brw XMI_ERR;
#define BI1(node)	.long BI1_ERR/**/node;
#define BI1_GLUE(node)	.align 2; BI1_ERR/**/node: TIM_PUSHR(0); pushl $((1<<4)|0x/**/node); brw BI_ERR;
#else	NBI > 1
#define XMI1		.long XMI_ERR_STRAY
#define XMI1_GLUE
#define BI1(node)	.long BI_ERR_STRAY;
#define BI1_GLUE(node)
#endif	NBI > 1

#if	NBI > 2
#define XMI2		.long XMI_ERR2;
#define XMI2_GLUE	.align 2; XMI_ERR2: TIM_PUSHR(0); pushl $2; brw XMI_ERR;
#define BI2(node)	.long BI2_ERR/**/node;
#define BI2_GLUE(node)	.align 2; BI2_ERR/**/node: TIM_PUSHR(0); pushl $((2<<4)|0x/**/node); brw BI_ERR;
#else	NBI > 2
#define XMI2		.long XMI_ERR_STRAY
#define XMI2_GLUE
#define BI2(node)	.long BI_ERR_STRAY;
#define BI2_GLUE(node)
#endif	NBI > 2

#if	NBI > 3
#define XMI3		.long XMI_ERR3;	
#define XMI3_GLUE	.align 2; XMI_ERR3: TIM_PUSHR(0); pushl $3; brw XMI_ERR;
#define BI3(node)	.long BI3_ERR/**/node;
#define BI3_GLUE(node)	.align 2; BI3_ERR/**/node: TIM_PUSHR(0); pushl $((3<<4)|0x/**/node); brw BI_ERR;
#else	NBI > 3
#define XMI3		.long XMI_ERR_STRAY
#define XMI3_GLUE
#define BI3(node)	.long BI_ERR_STRAY;
#define BI3_GLUE(node)
#endif	NBI > 3
