/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	start.s,v $
 * Revision 2.2.1.7  90/07/27  11:24:54  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.2.1.6  90/07/10  11:42:46  rvb
 * 	iPSC2: boot does not push everything that AT386 does.
 * 	[90/06/16            rvb]
 * 
 * Revision 2.2.1.5  90/02/28  15:48:34  rvb
 * 	Revision 1.3  90/02/26  17:54:39  kupfer
 * 	Synch with CMU.  h/w workarounds ifdef'd by h/w type.
 * 
 * Revision 2.2.1.3  90/01/08  13:26:41  rvb
 *	Add Intel copyright.
 *	[90/01/08            rvb]
 *   
 * Revision 2.2.1.2  89/12/21  17:14:55  rvb
 *	Pick up esym for a.out
 *    
 * Revision 2.2.1.1  89/10/22  11:31:35  rvb
 * 	New a.out and coff compatible .s files.
 * 	[89/10/16            rvb]
 * 
 * Revision 2.2  89/09/25  12:32:48  rvb
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */

#include <i386/asm.h>
#include <mach/vm_param.h>

/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
	
#ifndef	iPSC2
/ these are not needed for iPSC2
	.globl	EXT(cnvmem)
	.globl	EXT(extmem)
	.globl	EXT(boottype)
	.globl	EXT(boothowto)
#endif	iPSC2

#ifdef	wheeze
#else	wheeze
	.globl	EXT(esym)
#endif	wheeze
	.globl	EXT(pstart)
	.globl	EXT(gdt)
	.globl	EXT(idt)
	.globl	EXT(kpde)
	.globl	EXT(kpte)
	.globl	EXT(scall_dscr)
	.globl	EXT(sigret_dscr)

#ifdef	wheeze
	.set	GDTLIM, [8\*96-1]
	.set	IDTLIM, [8\*256-1]
#else	wheeze
	.set	GDTLIM, (Times(8,96)-1)
	.set	IDTLIM, (Times(8,256)-1)
#endif	wheeze
	.set    GDTSZ,   96
	.set    IDTSZ,   256
	.set	PAGEBIT, 0x80000000
	.set	MASK,	 0x0FFFFFFF	/ mask the top nibble
	.set	KV,	 0xC0000000

	.text
DATA(intstack)
DATA(df_stack)
/	.space	KERNEL_STACK_SIZE
	.set .,. + 4096

Entry(pstart)

#ifndef	iPSC2
	/ Retrieve the parameters passed from boot
	pop	%eax
	mov	$EXT(boottype), %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)

	pop	%eax
	mov	$EXT(extmem), %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)

	pop	%eax
	mov	$EXT(cnvmem), %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)
#endif	iPSC2

#ifdef	OLD_BOOT
	xorl	%eax, %eax
	movb	$0, %al
#else	OLD_BOOT
	pop	%eax
#endif	OLD_BOOT
	mov	$EXT(boothowto), %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)

#ifdef	wheeze
#else	wheeze
/*	leal	EXT(end), %eax*/
	pop	%eax
	orl	$KV, %eax
	mov	$EXT(esym), %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)
#endif	wheeze

	/ Turn off clock interrupt.
	/ This is due to a bug in p0init which enables interrupt
	/ before picinit.
	mov	$0x21, %edx		/ XXX - magic number
	INB
	orb	$1, %al			/ XXX - magic number
	OUTB

	/ Rearrange GDT
	mov	$EXT(gdt), %eax
	and	$MASK, %eax

	mov	$GDTLIM, %ecx

	mov	$GDTdscr, %ebx
	and	$MASK, %ebx
	movw	%cx, (%ebx)

	call	munge_table

	/ Rearrange IDT
	mov	$EXT(idt), %eax
	and	$MASK, %eax

	mov	$IDTLIM, %ecx

	call	munge_table

	/ Rearrange call gate for system call (scall_dscr)
	mov	$EXT(scall_dscr), %eax
	and	$MASK, %eax

	mov	$1, %ecx

	call	munge_table

	/ Rearrange call gate for signal return  (sigret_dscr)
	mov	$EXT(sigret_dscr), %eax
	and	$MASK, %eax

	mov	$1, %ecx

	call	munge_table

	/ Fix up the 1st, 3 giga and last entries in the page directory
	mov	$EXT(kpde), %ebx
	and	$MASK, %ebx

	mov	$EXT(kpte), %eax	
	and	$0xffff000, %eax
	or	$0x1, %eax

	mov	%eax, (%ebx)
	mov	%eax, 3072(%ebx)	/ 3 giga -- C0000000

	mov	$EXT(kpde), %edx
	and	$MASK, %edx

	/ Load IDTR
	mov	$IDTdscr, %eax
	and	$MASK, %eax

	lidt	(%eax)

	/ Load GDTR
	mov	$GDTdscr, %eax
	and	$MASK, %eax

	lgdt	(%eax)

	/ turn PG on
	mov	%cr0, %eax
	or	$PAGEBIT, %eax
	mov	%eax, %cr0

	mov	%edx, %cr3

	ljmp	$KTSSSEL, $0x0

/ *********************************************************************
/	munge_table:
/		This procedure will 'munge' a descriptor table to
/		change it from initialized format to runtime format.
/		Assumes:
/			%eax -- contains the base address of table.
/			%ecx -- contains size of table.
/ *********************************************************************

munge_table:
	mov	%eax, %ebx
	add	%ebx, %ecx
moretable:
	cmp	%ebx, %ecx
	jl	donetable		/ Have we done every descriptor??
	movb	7(%ebx), %al	/ Find the byte containing the type field
	testb	$0x10, %al	/ See if this descriptor is a segment
	jne	notagate
	testb	$0x04, %al	/ See if this destriptor is a gate
	je	notagate
				/ Rearrange a gate descriptor.
	movw	6(%ebx), %eax	/ Type (etc.) lifted out
	movw	4(%ebx), %edx	/ Selector lifted out.
	movw	%eax, 4(%ebx)	/ Type (etc.) put back
	movw	2(%ebx), %eax	/ Grab Offset 16..31
	movw	%edx, 2(%ebx)	/ Put back Selector
	movw	%eax, 6(%ebx)	/ Offset 16..31 now in right place
	jmp	descdone

notagate:			/ Rearrange a non gate descriptor.
	movw	4(%ebx), %edx	/ Limit 0..15 lifted out
	movb	%al, 5(%ebx)	/ type (etc.) put back
	movw	2(%ebx), %eax	/ Grab Base 16..31
	movb	%al, 4(%ebx)	/ put back Base 16..23
	movb	%ah, 7(%ebx)	/ put back Base 24..32
	movw	(%ebx), %eax	/ Get Base 0..15
	movw	%eax, 2(%ebx)	/ Base 0..15 now in right place
	movw	%edx, (%ebx)	/ Limit 0..15 in its proper place

descdone:
	addw	$8, %ebx	/ Go for the next descriptor
	jmp	moretable

donetable:
	ret

	.align	8
GDTdscr:
	Value  GDTLIM
	.long	EXT(gdt)

	.align	8
IDTdscr:
	Value	IDTLIM
	.long	EXT(idt)

