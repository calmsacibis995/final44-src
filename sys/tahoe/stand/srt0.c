/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)srt0.c	7.2 (Berkeley) 5/8/91
 */

#include "../include/mtpr.h"
#define	LOCORE

/*
 * Startup code for standalone system
 */

	.globl	_end
	.globl	_main
	.globl	__rtt
	.globl	_firstopen
	.globl	_start
	.globl	_boothowto
	.globl	_bootdev

	.set	HIGH,31		# mask for total disable

#ifndef	REL
	.globl	_device_space
_device_space:			# Tapemaster config block, etc.
	.space	0x1000-RELOC

	.globl	_entry
_entry:
	.word	0x00			# 'call' by relsrt0.
#endif
_start:
	mtpr	$HIGH,$IPL		# just in case
#ifdef REL
	movl	$BOOTRELOC,sp

	movl	$RELOC,r0	/* source address to copy from */
	movl	$BOOTRELOC,r1	/* destination address */
	movl	tdlen,r2	/* length to copy */
	addl2	r2,r0
	addl2	r2,r1
mvloop:
	decl	r0
	decl	r1
	movb	(r0),(r1)
	decl	r2
	bgeq	mvloop

/*
 * zero bss
 */
	movl	aedata,r1		/* destination address */
	subl3	$_edata,$_end,r2	/* length to zero */
zloop:
	movb	$0,(r1)
	incl	r1
	decl	r2
	bgeq	zloop

	mtpr	$1,$PACC
	mtpr	$1,$PADC
	jmp	*abegin
#endif

begin:
	movl	fp,ofp
	movl	r11,_boothowto
	movl	r10,_bootdev
	movl	$1,_firstopen
	callf	$4,_main
#ifdef REL
	halt
#endif
	ret

__rtt:
	.word	0x0
#ifdef REL
	halt
#endif
	movl	ofp,fp
	ret

	.data
abegin:	.long	begin
#ifdef REL
aedata:	.long	_edata
tdlen:	.long	_edata-BOOTRELOC
#endif
ofp:	.long	0
_boothowto:	.long	0
_bootdev:	.long	0
