h06408
s 00000/00000/00369
d D 8.1 93/06/11 15:53:05 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00005/00366
d D 7.8 93/06/11 15:52:58 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00370
d D 7.7 92/10/11 10:20:04 bostic 12 11
c make kernel includes standard
e
s 00103/00079/00268
d D 7.6 92/05/11 17:04:01 bostic 11 10
c Don't send an EOI to the slave interrupt controller if the interrupt
c came from the master; Insure that no hardware interrupts are allowed between
c deciding to return to user mode and the "iret".  This will be necessary for a
c future change that will fix floating point error reporting.  From Pace Willison
e
s 00003/00007/00344
d D 7.5 92/05/11 17:00:17 bostic 10 9
c fix header
e
s 00040/00264/00311
d D 7.4 92/02/28 18:43:43 sklower 9 8
c This likely represents cleanups done by Bill Jolitz Sept 3 '91
e
s 00007/00000/00568
d D 7.3 91/09/03 08:57:19 sklower 8 7
c added ISO network software interrupts
e
s 00001/00001/00567
d D 7.2 91/05/21 10:41:19 bostic 7 6
c format cleanup
e
s 00029/00017/00539
d D 7.1 91/05/09 21:34:02 william 6 5
c newer versions
e
s 00000/00000/00556
d D 5.5 91/01/08 19:13:20 william 5 4
c  npx.c wd.c wt.c
e
s 00273/00119/00283
d D 5.4 90/11/18 11:32:11 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00033/00009/00369
d D 5.3 90/11/08 19:57:16 bill 3 2
c reworked interrupt code for network interrupt
e
s 00021/00014/00357
d D 5.2 90/06/23 18:49:44 donahn 2 1
c improvements to decrease interrupt latency
e
s 00371/00000/00000
d D 5.1 90/04/24 12:59:26 william 1 0
c date and time created 90/04/24 12:59:26 by william
e
u
U
t
T
I 1
/*-
I 7
D 9
 * Copyright (c) 1989, 1990 William F. Jolitz.
E 9
E 7
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 10
I 10
D 13
 * Copyright (C) 1989,90 W. Jolitz
 * Copyright (c) 1992 The Regents of the University of California.
E 10
 * All rights reserved.
E 13
I 13
 * Copyright (C) 1989, 1990 W. Jolitz
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 6
 * %sccs.include.386.c%
E 6
I 6
D 9
 * %sccs.include.redist.c%
E 9
I 9
D 10
 * %sccs.include.386.c%
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 6
 *
 *	%W% (Berkeley) %G%
 */

D 10
/*
 * AT/386
 * Vector interrupt control section
I 9
 * Copyright (C) 1989,90 W. Jolitz
E 9
D 3
 * W. Jolitz	8/89
E 3
I 3
D 7
 * Copyright (C) 1989,90 W. Jolitz
E 7
E 3
 */
E 10
D 13

E 13
	.data
	.globl	_imen
	.globl	_cpl
D 2
_cpl:	.long	15			# current priority level (all off)
E 2
I 2
_cpl:	.long	0xffff			# current priority level (all off)
E 2
_imen:	.long	0xffff			# interrupt mask enable (all off)
I 4
	.globl	_highmask
_highmask:	.long	0xffff
E 4
I 2
	.globl	_ttymask
D 3
_ttymask:	.long	IRQ1+IRQ3+IRQ4
E 3
I 3
_ttymask:	.long	0
E 3
	.globl	_biomask
D 3
_biomask:	.long	IRQ14+IRQ6
E 3
I 3
_biomask:	.long	0
	.globl	_netmask
_netmask:	.long	0
I 6
	.globl	_isa_intr
_isa_intr:	.space	16*4
E 6
I 4

E 4
E 3
E 2
	.text
I 11
D 12
#include "../net/netisr.h"
E 12
I 12
#include <net/netisr.h>
E 12

#define DONET(s, c)	; \
	.globl	c ;  \
	btrl	$ s ,_netisr ;  \
	jnb	1f ; \
	call	c ; \
1:

E 11
I 4
/*
 * Handle return from interrupt after device handler finishes
I 11
 *
 * register usage:
 *
 * %ebx is cpl we are going back to
 * %esi is 0 if returning to kernel mode
 *
 * Note that these registers will be preserved though C calls,
 * such as the network interrupt routines.
E 11
 */
doreti:
	cli
D 11
	popl	%ebx			# remove intr number
I 9
	nop
E 9
	popl	%eax			# get previous priority
I 9
	nop
E 11
I 11
	popl	%ebx			# flush unit number
	popl	%ebx			# get previous priority
E 11
E 9
	# now interrupt frame is a trap frame!
D 11
	movw	%ax,%cx
E 11
I 11

	/* compensate for drivers that return with non-zero cpl */
	movl	0x34(%esp), %esi /* cs */
	andl	$3, %esi
	jz	1f

return_to_user_mode: /* entry point from trap and syscall return */

	/* return cs is for user mode: force 0 cpl */
	xorl	%ebx,%ebx
1:

	/* like splx(%ebx), except without special 0 handling */
	cli
	movl	%ebx, %eax
E 11
	movw	%ax,_cpl
	orw	_imen,%ax
D 9
	NOP
E 9
D 11
	outb	%al,$ IO_ICU1+1		# re-enable intr?
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
	outb	%al,$ IO_ICU2+1
E 11
I 11
	outb	%al, $ IO_ICU1+1
	movb	%ah, %al
	outb	%al, $ IO_ICU2+1
E 11
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
E 4

D 4
	.globl	_iml0			# masks off all interrupts
E 4
I 4
D 9
	andw	$0xffff,%cx	
E 9
I 9
D 11
	# andw	$0xffff,%cx	
E 9
	cmpw	$0,%cx			# returning to zero?
	je	1f
E 11
I 11
	/* return immediately if previous cpl was non-zero */
	cmpw	$0, %bx
	jnz	just_return
E 11

D 9
	pop	%es			# nope, going to non-zero level
	pop	%ds
	popa
E 9
I 9
D 11
2:	popl	%es			# nope, going to non-zero level
	nop
E 11
I 11
	/* do network stuff, if requested, even if returning to kernel mode */
	cmpl	$0,_netisr
	jne	donet

	/* if (returning to user mode && astpending), go back to trap
	 * (check astpending first since it is more likely to be false)
	 */
	cmpl	$0,_astpending
	je	just_return

	testl	%esi, %esi
	jz	just_return

	/* we need to go back to trap */
	popl	%es
E 11
	popl	%ds
D 11
	nop
E 11
	popal
D 11
	nop
E 11
E 9
	addl	$8,%esp
D 11
	iret
E 11

D 11
1:	cmpl	$0,_netisr		# check for softint s/traps
D 9
	jne	1f
E 9
I 9
	je	2b
E 11
I 11
	pushl	$0
	TRAP (T_ASTFLT)
	/* this doesn't return here ... instead it goes though
	 * calltrap in locore.s
	 */
E 11
E 9

D 9
	pop	%es			# none, going back to base pri
	pop	%ds
	popa
	addl	$8,%esp
	iret
	
E 9
D 11
#include "../net/netisr.h"
E 11
I 11
donet:
	/* like splnet(), except we know the current pri is 0 */
	cli
	movw _netmask, %ax
	movw %ax,_cpl
	orw _imen,%ax
	outb %al, $ IO_ICU1+1
	movb %ah, %al
	outb %al, $ IO_ICU2+1
	sti
E 11

D 11
1:

#define DONET(s, c)	; \
	.globl	c ;  \
D 9
	movl	$ s ,%eax ; 	\
	btrl	%eax,_netisr ;  \
E 9
I 9
	btrl	$ s ,_netisr ;  \
E 9
	jnb	1f ; \
	call	c ; \
1:

	call	_splnet
	pushl	%eax

I 9

E 11
E 9
	DONET(NETISR_RAW,_rawintr)
#ifdef INET
	DONET(NETISR_IP,_ipintr)
I 8
	DONET(NETISR_ARP,_arpintr)
E 8
#endif
#ifdef IMP
	DONET(NETISR_IMP,_impintr)
#endif
#ifdef NS
	DONET(NETISR_NS,_nsintr)
I 8
#endif
#ifdef ISO
	DONET(NETISR_ISO,_clnlintr)
#endif
#ifdef CCITT
	DONET(NETISR_CCITT,_hdintr)
E 8
#endif

I 9
D 11
	/* restore interrupt state, but don't turn them on just yet */
E 11
I 11
	btrl	$ NETISR_SCLK,_netisr
	jnb	return_to_user_mode

	/* like splsoftclock */
E 11
	cli
E 9
D 11
	popl	%eax
I 9
	nop
E 9
	movw	%ax,_cpl
	orw	_imen,%ax
D 9
	NOP
E 9
	outb	%al,$ IO_ICU1+1		# re-enable intr?
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
	outb	%al,$ IO_ICU2+1
E 11
I 11
	movw $0x8000, %ax
	movw %ax,_cpl
	orw _imen,%ax
	outb %al, $ IO_ICU1+1
	movb %ah, %al
	outb %al, $ IO_ICU2+1
	sti
E 11
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6

D 9
	# btrl	$ NETISR_SCLK,_netisr
	movl	$ NETISR_SCLK,%eax	# stupid assembler, as usual
	btrl	%eax,_netisr
E 9
I 9
D 11
	btrl	$ NETISR_SCLK,_netisr
E 9
	jnb	1f
E 11
	# back to an interrupt frame for a moment
D 11
	call	_splsoftclock
E 11
	pushl	%eax
	pushl	$0xff	# dummy intr
	call	_softclock
D 11
	popl	%eax
I 9
	nop
E 9
	call	_splx
	popl	%eax
I 9
	nop
E 11
I 11
	leal	8(%esp), %esp
	jmp	return_to_user_mode
E 11
E 9

D 11
	jmp	2f

D 9
	/* 1:	btrl	$NETISR_AST,_netisr*/
E 9
1:
	cmpw	$0x1f,13*4(%esp)	# to user?
	jne	2f			# nope, leave
D 9
	movl	$ NETISR_AST,%eax	# stupid assembler, as usual
	btrl	%eax,_netisr
E 9
I 9
	btrl	$ NETISR_AST ,_netisr
E 9
	jnb	2f
	call	_trap

2:	pop	%es
I 9
	nop
E 11
I 11
just_return:
	pop	%es
E 11
E 9
	pop	%ds
I 9
D 11
	nop
E 9
	popal
I 9
	nop
E 9
	addl	$8,%esp
E 11
I 11
	popa
	leal	8(%esp),%esp
E 11
	iret

/*
 * Interrupt priority mechanism
 *
 * Two flavors	-- imlXX masks relative to ISA noemenclature (for PC compat sw)
 *		-- splXX masks with group mechanism for BSD purposes
 */

E 4
	.globl	_splhigh
	.globl	_splclock
D 4
	.globl	_spl6
_iml0:
_spl6:
E 4
_splhigh:
_splclock:
	cli				# disable interrupts
	movw	$0xffff,%ax		# set new priority level
	movw	%ax,%dx
D 2
	orw	_imen,%ax		# mask off those not enabled yet
E 2
I 2
	# orw	_imen,%ax		# mask off those not enabled yet
E 2
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl	_iml1			# mask off all but irq0
E 4
	.globl	_spltty			# block clists
D 4
_iml1:
E 4
_spltty:
	cli				# disable interrupts
D 2
	movw	$0xfffe,%ax		# set new priority level
E 2
I 2
D 3
	# movw	$0xfffe,%ax		# set new priority level
E 3
	movw	_cpl,%ax
	orw	_ttymask,%ax
E 2
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl	_iml8			# mask off all but irq0-1
_iml8:
E 4
I 4
	.globl	_splimp
	.globl	_splnet
_splimp:
_splnet:
E 4
	cli				# disable interrupts
D 4
	movw	$0xfffc,%ax		# set new priority level
E 4
I 4
	movw	_cpl,%ax
	orw	_netmask,%ax
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl	_iml9			# mask off all but irq0-1,8
	.globl	_iml2			# alias for PC hardware level 2
	.globl	_splimp
	.globl	_splnet
_iml9:
_iml2:
_splimp:
_splnet:
E 4
I 4
	.globl	_splbio	
_splbio:
E 4
	cli				# disable interrupts
D 2
	movw	$0xfef8,%ax		# set new priority level
E 2
I 2
D 3
	# movw	$0xfef8,%ax		# set new priority level
	movw	$0xffff,%ax		# set new priority level
E 3
I 3
	movw	_cpl,%ax
D 4
	orw	_netmask,%ax
E 4
I 4
	orw	_biomask,%ax
E 4
E 3
E 2
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl	_iml10			# mask off all but irq0-1,8-9
_iml10:
E 4
I 4
	.globl	_splsoftclock
_splsoftclock:
E 4
	cli				# disable interrupts
D 4
	movw	$0xfcf8,%ax		# set new priority level
E 4
I 4
	movw	_cpl,%ax
	orw	$0x8000,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml11			# mask off all but irq0-1,8-10
_iml11:
E 4
I 4
	.globl _splnone
	.globl _spl0
_splnone:
_spl0:
E 4
	cli				# disable interrupts
D 4
	movw	$0xf8f8,%ax		# set new priority level
	movw	%ax,%dx
E 4
I 4
	pushl	_cpl			# save old priority
	movw	_cpl,%ax
	orw	_netmask,%ax		# mask off those network devices
	movw	%ax,_cpl		# set new priority level
E 4
	orw	_imen,%ax		# mask off those not enabled yet
D 4
	movw	%ax,%cx
E 4
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
D 4
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
E 4
	sti				# enable interrupts
D 4
	ret
E 4

D 4
	.globl	_iml12			# mask off all but irq0-1,8-11
_iml12:
E 4
I 4
	DONET(NETISR_RAW,_rawintr)
#ifdef INET
	DONET(NETISR_IP,_ipintr)
I 9
	DONET(NETISR_ARP,_arpintr)
E 9
#endif
I 9
#ifdef IMP
	DONET(NETISR_IMP,_impintr)
#endif
#ifdef NS
	DONET(NETISR_NS,_nsintr)
#endif
#ifdef ISO
	DONET(NETISR_ISO,_clnlintr)
#endif
#ifdef CCITT
	DONET(NETISR_CCITT,_hdintr)
#endif

E 9
E 4
	cli				# disable interrupts
D 4
	movw	$0xf0f8,%ax		# set new priority level
E 4
I 4
	popl	_cpl			# save old priority
I 9
	nop

E 9
	movw	$0,%ax			# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml13			# mask off all but irq0-1,8-12
_iml13:
E 4
I 4
	.globl _splx
_splx:
E 4
	cli				# disable interrupts
D 4
	movw	$0xe0f8,%ax		# set new priority level
E 4
I 4
	movw	4(%esp),%ax		# new priority level
E 4
	movw	%ax,%dx
I 4
	cmpw	$0,%dx
	je	_spl0			# going to "zero level" is special

E 4
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
D 9
	NOP
E 9
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
D 9
	NOP
E 9
	movb	%ah,%al
D 9
	NOP
E 9
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
D 9
	NOP
I 6
	inb	$0x84,%al
E 9
E 6
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret
D 9

D 4
	.globl	_iml14			# mask off all but irq0-1,8-13
	.globl	_splbio	
_iml14:
_splbio:
E 4
I 4
#ifdef notyet
	.globl	_iml8			# mask off all but irq0-1
_iml8:
E 4
	cli				# disable interrupts
D 2
	movw	$0xc0f8,%ax		# set new priority level
E 2
I 2
D 4
	movw	_cpl,%ax
	orw	_biomask,%ax
E 4
I 4
	movw	$0xfffc,%ax		# set new priority level
E 4
D 3
	# movw	$0xffff,%ax		# set new priority level XXX
	# movw	$0xc0f8,%ax		# set new priority level
E 3
E 2
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl	_iml15			# mask off all but irq0-1,8-14
_iml15:
E 4
I 4
	.globl	_iml10			# mask off all but irq0-1,8-9
_iml10:
E 4
	cli				# disable interrupts
D 4
	movw	$0x80f8,%ax		# set new priority level
E 4
I 4
	movw	$0xfcf8,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml3			# mask off all but irq0-1,8-15
_iml3:
E 4
I 4
	.globl	_iml11			# mask off all but irq0-1,8-10
_iml11:
E 4
	cli				# disable interrupts
D 4
	movw	$0x00f8,%ax		# set new priority level
E 4
I 4
	movw	$0xf8f8,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml4			# mask off all but irq0-1,8-15,3
_iml4:
E 4
I 4
	.globl	_iml12			# mask off all but irq0-1,8-11
_iml12:
E 4
	cli				# disable interrupts
D 4
	movw	$0x00f0,%ax		# set new priority level
E 4
I 4
	movw	$0xf0f8,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml5			# mask off all but irq0-1,8-15,3-4
_iml5:
E 4
I 4
	.globl	_iml13			# mask off all but irq0-1,8-12
_iml13:
E 4
	cli				# disable interrupts
D 4
	movw	$0x00e0,%ax		# set new priority level
E 4
I 4
	movw	$0xe0f8,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml6			# mask off all but irq0-1,8-15,3-5
_iml6:
E 4
I 4
	.globl	_iml15			# mask off all but irq0-1,8-14
_iml15:
E 4
	cli				# disable interrupts
D 4
	movw	$0x00c0,%ax		# set new priority level
E 4
I 4
	movw	$0x80f8,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl	_iml7,_splsoftclock	# mask off all but irq0-1,8-15,3-7
_iml7:
_splsoftclock:
E 4
I 4
	.globl	_iml3			# mask off all but irq0-1,8-15
_iml3:
E 4
	cli				# disable interrupts
D 3
	movw	$0x0080,%ax		# set new priority level
E 3
I 3
D 4
	movw	_cpl,%ax
	orw	$0x8000,%ax		# set new priority level
E 4
I 4
	movw	$0x00f8,%ax		# set new priority level
E 4
E 3
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
#	sti				# enable interrupts
E 2
I 2
	sti				# enable interrupts
E 2
	ret

D 4
	.globl _imlnone			# masks off no interrupts
	.globl _splnone
	.globl _spl0
_imlnone:
_splnone:
_spl0:
E 4
I 4
	.globl	_iml4			# mask off all but irq0-1,8-15,3
_iml4:
E 4
	cli				# disable interrupts
I 3
D 4
	pushl	_cpl			# save old priority
	movw	_cpl,%ax
	orw	_netmask,%ax		# mask off those network devices
	movw	%ax,_cpl		# set new priority level
E 4
I 4
	movw	$0x00f0,%ax		# set new priority level
	movw	%ax,%dx
E 4
	orw	_imen,%ax		# mask off those not enabled yet
I 4
	movw	%ax,%cx
E 4
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
I 4
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
E 4
	sti				# enable interrupts
I 4
	ret
E 4

D 4
	DONET(NETISR_RAW,_rawintr)
#ifdef INET
	DONET(NETISR_IP,_ipintr)
#endif
E 4
I 4
	.globl	_iml5			# mask off all but irq0-1,8-15,3-4
_iml5:
E 4
	cli				# disable interrupts
D 4
	popl	_cpl			# save old priority
E 3
	movw	$0,%ax			# set new priority level
E 4
I 4
	movw	$0x00e0,%ax		# set new priority level
E 4
	movw	%ax,%dx
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
	sti				# enable interrupts
	ret

D 4
	.globl _splx
_splx:
E 4
I 4
	.globl	_iml6			# mask off all but irq0-1,8-15,3-5
_iml6:
E 4
	cli				# disable interrupts
D 4
	movw	4(%esp),%ax		# new priority level
E 4
I 4
	movw	$0x00c0,%ax		# set new priority level
E 4
	movw	%ax,%dx
I 3
D 4
	cmpw	$0,%dx
	je	_spl0

E 4
E 3
	orw	_imen,%ax		# mask off those not enabled yet
	movw	%ax,%cx
	NOP
D 4
	outb	%al,$0x21		/* update icu's */
E 4
I 4
	outb	%al,$ IO_ICU1+1		/* update icu's */
E 4
	NOP
	movb	%ah,%al
	NOP
D 4
	outb	%al,$0xA1
E 4
I 4
	outb	%al,$ IO_ICU2+1
E 4
	NOP
	movzwl	_cpl,%eax		# return old priority
	movw	%dx,_cpl		# set new priority level
D 2
	cmpw	$0,%dx		# XXX
	jne	1f		# XXX
E 2
	sti				# enable interrupts
D 2
1:
E 2
	ret
I 4

#endif	notyet
E 9

	/* hardware interrupt catcher (IDT 32 - 47) */
	.globl	_isa_strayintr

IDTVEC(intr0)
D 6
	INTR(0) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(0, _highmask, 0) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(0, _highmask, 0) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr1)
D 6
	INTR(1) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(1, _highmask, 1) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(1, _highmask, 1) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr2)
D 6
	INTR(2) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(2, _highmask, 2) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(2, _highmask, 2) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr3)
D 6
	INTR(3) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(3, _highmask, 3) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(3, _highmask, 3) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr4)
D 6
	INTR(4) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(4, _highmask, 4) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(4, _highmask, 4) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr5)
D 6
	INTR(5) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(5, _highmask, 5) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(5, _highmask, 5) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr6)
D 6
	INTR(6) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(6, _highmask, 6) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(6, _highmask, 6) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6

IDTVEC(intr7)
D 6
	INTR(7) ; call	_isa_strayintr ; INTREXT1
E 6
I 6
D 11
	INTR(7, _highmask, 7) ; call	_isa_strayintr ; INTREXIT1
E 11
I 11
	INTR1(7, _highmask, 7) ; call	_isa_strayintr ; INTREXIT1
E 11
E 6


IDTVEC(intr8)
D 6
	INTR(8) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(8, _highmask, 8) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(8, _highmask, 8) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr9)
D 6
	INTR(9) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(9, _highmask, 9) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(9, _highmask, 9) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr10)
D 6
	INTR(10) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(10, _highmask, 10) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(10, _highmask, 10) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr11)
D 6
	INTR(11) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(11, _highmask, 11) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(11, _highmask, 11) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr12)
D 6
	INTR(12) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(12, _highmask, 12) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(12, _highmask, 12) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr13)
D 6
	INTR(13) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(13, _highmask, 13) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(13, _highmask, 13) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr14)
D 6
	INTR(14) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(14, _highmask, 14) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(14, _highmask, 14) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6

IDTVEC(intr15)
D 6
	INTR(15) ; call	_isa_strayintr ; INTREXT2
E 6
I 6
D 11
	INTR(15, _highmask, 15) ; call	_isa_strayintr ; INTREXIT2
E 11
I 11
	INTR2(15, _highmask, 15) ; call	_isa_strayintr ; INTREXIT2
E 11
E 6
E 4
I 3
D 13

E 13
E 3
E 1
