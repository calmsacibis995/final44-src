/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	getidprom.s,v $
 * Revision 2.2  89/07/12  00:24:32  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)getidprom.s 1.2 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
 	.seg	"text"
 	.align	4

IDPROMBASE=0x00000000		! base address of idprom in CTL space
IDPROMSIZE=0x20			! size of idprom
ASI_CTL=2			! address space indentifier for CTL space
!
! getidprom(addr, size)
!
! Read the ID prom.
! This is mapped from IDPROMBASE for IDPROMSIZE bytes in the
! ASI_CTL address space for byte access only.
! 
	.global _getidprom
_getidprom:
	set     IDPROMBASE, %g1
	clr     %g2
1:
	lduba   [%g1 + %g2]ASI_CTL, %g7 ! get id prom byte
	add     %g2, 1, %g2		! interlock
	stb     %g7, [%o0]		! put it out
	cmp     %g2, %o1		! done yet?
	bne,a   1b
	add     %o0, 1, %o0		! delay slot
	retl				! leaf routine return
	nop				! delay slot
