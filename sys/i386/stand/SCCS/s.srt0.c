h04932
s 00002/00002/00252
d D 8.1 93/06/11 15:58:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00253
d D 7.3 91/04/28 17:21:12 william 3 2
c redist
e
s 00094/00056/00160
d D 7.2 91/04/28 17:20:27 william 2 1
c major cleanup
e
s 00216/00000/00000
d D 7.1 90/04/24 19:57:16 william 1 0
c date and time created 90/04/24 19:57:16 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Startup code for standalone system
 * Non-relocating version -- for programs which are loaded by boot
 * Relocating version for boot
I 2
 * Small relocating version for "micro" boot
E 2
 */

	.globl	_end
	.globl	_edata
	.globl	_main
	.globl	__rtt
	.globl	_exit
D 2
	.globl	_howto
E 2
	.globl	_bootdev
D 2
	.globl	_unit
E 2
I 2
	.globl	_cyloffset
E 2

I 2
#ifdef SMALL
	/* where the disklabel goes if we have one */
	.globl	_disklabel
_disklabel:
	.space 512
#endif
E 2

entry:	.globl	entry
D 2
	cli				# no interrupts
#ifdef REL
	movl	$RELOC,%esp
#else
	movl	%esp,savearea
	movl	%ebp,savearea+4
	movl	$RELOC-0x2400,%esp
#endif
	movl	%esp,%ecx
start:
	movl	$_edata,%eax
#ifndef foo
#else
	subl	%eax,%ecx
1:
	movl	$0,(%eax)
	addl	$4,%eax
	loopnz	1f
#endif
#ifdef REL
	# movl	$entry-RELOC,%esi	# from beginning of ram
E 2
I 2
	.globl	start

#if	defined(REL) && !defined(SMALL)

	/* relocate program and enter at symbol "start" */

	#movl	$entry-RELOC,%esi	# from beginning of ram
E 2
	movl	$0,%esi
D 2
	movl	$entry,%edi		# to relocated area
E 2
I 2
	#movl	$entry,%edi		# to relocated area
	movl	$ RELOC,%edi		# to relocated area
E 2
	# movl	$_edata-RELOC,%ecx	# this much
	movl	$64*1024,%ecx
	cld
	rep
	movsb
D 2
	.globl	begin
	# jmp	*$begin	-- does not work, why!?
	pushl	$begin
E 2
I 2
	# relocate program counter to relocation base
	pushl	$start
E 2
	ret
D 2
begin:
E 2
#endif
D 2
	# movl	%esi,_howto
	# movl	%edi,_bootdev
	# movl	%ebx,_unit
1:
	# calls	$0,_configure
	movl	$1,_openfirst
E 2
I 2

start:

	/* setup stack pointer */

#ifdef REL
	leal	4(%esp),%eax	/* ignore old pc */
	movl	$ RELOC-4*4,%esp
	/* copy down boot parameters */
	movl	%esp,%ebx
	pushl	$3*4
	pushl	%ebx
	pushl	%eax
	call	_bcopy
	movl	%ebx,%esp
#else
	/* save old stack state */
	movl	%esp,savearea
	movl	%ebp,savearea+4
	movl	$ RELOC-0x2400,%esp
#endif

	/* clear memory as needed */

	movl	%esp,%esi
#ifdef	REL

	/*
	 * Clear Bss and up to 64K heap
	 */
	movl	$64*1024,%ebx
	movl	$_end,%eax	# should be movl $_end-_edata but ...
	subl	$_edata,%eax
	addl	%ebx,%eax
	pushl	%eax
	pushl	$_edata
	call	_bzero

	/*
	 * Clear 64K of stack
	 */
	movl	%esi,%eax
	subl	%ebx,%eax
	subl	$5*4,%ebx
	pushl	%ebx
	pushl	%eax
	call	_bzero
#else
	movl	$_edata,%edx
	movl	%esp,%eax
	subl	%edx,%eax
	pushl	%edx
	pushl	%esp
	call	_bzero
#endif
	movl	%esi,%esp

E 2
	pushl	$0
	popf
I 2

#ifndef	SMALL
	call	_kbdreset	/* resets keyboard and gatea20 brain damage */
#endif

E 2
	call	_main
D 2
#ifdef REL
	jmp	1b
#else
E 2
	jmp	1f
D 2
#endif
E 2

	.data
D 2
_openfirst:	.long	0
E 2
_bootdev:	.long	0
D 2
_howto:		.long	0
_unit:		.long	0
E 2
I 2
_cyloffset:	.long	0
E 2
savearea:	.long	0,0	# sp & bp to return to
	.text
I 2
#ifndef	SMALL
E 2
	.globl _getchar
I 2
#endif
E 2
	.globl _wait

__rtt:
I 2
#ifndef	SMALL
E 2
	call	_getchar
I 2
#else
_exit:
E 2
	pushl	$1000000
	call	_wait
	popl	%eax
I 2
#endif
E 2
	movl	$-7,%eax
	jmp	1f
I 2
#ifndef	SMALL
E 2
_exit:
	call	_getchar
D 2
	pushl	$1000000
	call	_wait
	popl	%eax
	movl	4(sp),%eax
E 2
I 2
#endif
	movl	4(%esp),%eax
E 2
1:
#ifdef	REL
I 2
#ifndef SMALL
	call	_reset_cpu
#endif
E 2
	movw	$0x1234,%ax
	movw	%ax,0x472	# warm boot
	movl	$0,%esp		# segment violation
	ret
D 2
	# jump	PA_Monitor		# jump to startup code in ROM
E 2
#else
	movl	savearea,%esp
	movl	savearea+4,%ebp
	ret
#endif
D 2
	.globl _setregs
_setregs:
	movl	_howto,%esi
	movl	_bootdev,%edi
	movl	_unit,%ebx
	ret
E 2

	.globl	_inb
_inb:	movl	4(%esp),%edx
	subl	%eax,%eax	# clr eax
D 2
	nop
E 2
	inb	%dx,%al
D 2
	nop
E 2
	ret

	.globl	_outb
_outb:	movl	4(%esp),%edx
	movl	8(%esp),%eax
D 2
	nop
E 2
	outb	%al,%dx
D 2
	nop
E 2
	ret

	.globl ___udivsi3
___udivsi3:
	movl 4(%esp),%eax
	xorl %edx,%edx
	divl 8(%esp)
	ret

	.globl ___divsi3
___divsi3:
	movl 4(%esp),%eax
	xorl %edx,%edx
	cltd
	idivl 8(%esp)
	ret

	#
	# bzero (base,cnt)
	#

	.globl _bzero
_bzero:
	pushl	%edi
	movl	8(%esp),%edi
	movl	12(%esp),%ecx
	movb	$0x00,%al
	cld
	rep
	stosb
	popl	%edi
	ret

	#
	# bcopy (src,dst,cnt)
	# NOTE: does not (yet) handle overlapped copies
	#

	.globl	_bcopy
_bcopy:
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
	cld
	rep
	movsb
	popl	%edi
	popl	%esi
	ret

	# insw(port,addr,cnt)
	.globl	_insw
_insw:
	pushl	%edi
	movw	8(%esp),%dx
	movl	12(%esp),%edi
	movl	16(%esp),%ecx
	cld
	nop
	.byte 0x66,0xf2,0x6d	# rep insw
	nop
	movl	%edi,%eax
	popl	%edi
	ret

	# outsw(port,addr,cnt)
	.globl	_outsw
_outsw:
	pushl	%esi
	movw	8(%esp),%dx
	movl	12(%esp),%esi
	movl	16(%esp),%ecx
	cld
	nop
	.byte 0x66,0xf2,0x6f	# rep outsw
	nop
	movl	%esi,%eax
	popl	%esi
	ret

E 1
