/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	SYS.h,v $
 * Revision 2.2  89/07/12  01:17:14  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/* @(#)SYS.h 1.3 88/02/08 SMI; from UCB 4.1 83/05/10 */

#include <syscall.h>

#if vax
#ifdef PROF
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x)	.globl _/**/x; .align 2; _/**/x: .word 0
#endif PROF
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); chmk $SYS_/**/x; jcs err
#define	BSDSYSCALL(x)	err: jmp cerror; ENTRY(_/**/x); chmk $SYS_/**/x; jcs err
#define	PSEUDO(x,y)	ENTRY(x); chmk $SYS_/**/y
#define	CALL(x,y)	calls $x, _/**/y
#define	RET		ret

	.globl	cerror
#endif

#if sun
	.globl	cerror
#ifdef PROF
	.globl  mcount
#define	ENTRY(x)	.globl _/**/x;\
		 _/**/x: link a6,#0;\
			 lea x/**/1,a0;\
		 .data; x/**/1: .long 0; .text;\
			 jsr mcount;\
			 unlk a6
#else
#define	ENTRY(x)	.globl _/**/x; _/**/x:
#endif

#define PARAM		sp@(4)
#define PARAM2		sp@(8)
#define	PSEUDO(x,y)	ENTRY(x); pea SYS_/**/y; trap #0
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); pea SYS_/**/x; trap #0; jcs err
#define	BSDSYSCALL(x)	err: jmp cerror; ENTRY(_/**/x); pea SYS_/**/x; trap #0; jcs err
#define RET		rts
#endif
