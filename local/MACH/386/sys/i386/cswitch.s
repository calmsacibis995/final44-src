/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	cswitch.s,v $
 * Revision 1.4.1.4  90/02/28  15:47:39  rvb
 * 	Added a comment to save_context and fixed some indentation
 * 	[kupfer]
 * 
 * Revision 1.4.1.3  90/01/08  13:29:19  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4.1.2  89/12/21  17:49:28  rvb
 * 	Well, the fix below was not quite correct.  And the change is
 * 	just as clever.
 * 	[89/12/14            rvb]
 * 
 * Revision 1.4.1.1  89/10/22  11:29:50  rvb
 * 	BIG BUG FIX (found by lance).  longjmp only gets one arg in the
 * 	kernel,  Not 2.  (kdblongjmp does get 2).  So longjmp/setjmpe was
 * 	returning with a random value.  This fixes a bunch of things.
 * 	[89/10/19            rvb]
 * 
 * 	New a.out and coff compatible .s files.
 * 	Some cleanup.
 * 	[89/10/16            rvb]
 * 
 * Revision 1.4  89/09/25  12:20:34  rvb
 * 	Use curr_ipl vs ipl to mesh with the prime's code.
 * 	[89/09/23            rvb]
 * 
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 * Revision 1.3  89/02/26  12:30:54  gm0w
 * 	Changes for cleanup.
 * 
 */
 
 /*
  *  Copyright 1988, 1989 by Intel Corporation
  */

#include <i386/asm.h>

	.text

#define	O_EDI	0
#define	O_ESI	4
#define	O_EBX	8
#define	O_EBP	12
#define	O_ESP	16
#define O_EIP	20
#define	O_IPL	24

ENTRY(save_context)
	/*
	 * We would like to do an "fwait" here so that any pending
	 * floating point exceptions happen before the context switch.
	 * Unfortunately, at least on an AT, this can cause the system
	 * to hang.
	 */
	call	EXT(get_pcb_context)
	movl	%eax,%edx		/ address of save area
	movl	EXT(curr_ipl), %eax
	movl	%eax, O_IPL(%edx)	/ save ipl level for longjmp
	call	EXT(splhi)
	movl	%edi, O_EDI(%edx)
	movl	%esi, O_ESI(%edx)
	movl	%ebx, O_EBX(%edx)
	movl	%ebp, O_EBP(%edx)
	movl	%esp, O_ESP(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, O_EIP(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

ENTRY(setjmp)
	movl	4(%esp), %edx		/ address of save area
	movl	EXT(curr_ipl), %eax
	movl	%eax, O_IPL(%edx)	/ save ipl level for longjmp
	movl	%edi, O_EDI(%edx)
	movl	%esi, O_ESI(%edx)
	movl	%ebx, O_EBX(%edx)
	movl	%ebp, O_EBP(%edx)
	movl	%esp, O_ESP(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, O_EIP(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

ENTRY(longjmp)
	call	EXT(splhi)
	movl	4(%esp), %edx		/ address of save area
	movl	O_EDI(%edx), %edi
	movl	O_ESI(%edx), %esi
	movl	O_EBX(%edx), %ebx
	movl	O_EBP(%edx), %ebp
	movl	O_ESP(%edx), %esp
	movl	O_EIP(%edx), %eax	/ %eip (return address)
	movl	%eax, 0(%esp)
	pushl	O_IPL(%edx)
	call	EXT(splx)		/ restore ipl level
	popl	%edx
	popl	%eax			/ ret addr != 0
	jmp	*%eax			/ indirect

ENTRY(kdbsetjmp)
	movl	4(%esp), %edx		/ address of save area
	movl	%edi, O_EDI(%edx)
	movl	%esi, O_ESI(%edx)
	movl	%ebx, O_EBX(%edx)
	movl	%ebp, O_EBP(%edx)
	movl	%esp, O_ESP(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, O_EIP(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

ENTRY(kdblongjmp)
	movl	8(%esp), %eax		/ return value
	movl	4(%esp), %edx		/ address of save area
	movl	O_EDI(%edx), %edi
	movl	O_ESI(%edx), %esi
	movl	O_EBX(%edx), %ebx
	movl	O_EBP(%edx), %ebp
	movl	O_ESP(%edx), %esp
	movl	O_EIP(%edx), %ecx		/ %eip (return address)
	addl	$4, %esp		/ pop ret adr
	jmp	*%ecx			/ indirect

