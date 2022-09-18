/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	srt0.c,v $
 * Revision 2.4  89/03/09  21:17:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:35:43  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:46:37  rvb
 * Add bzero(addr, len) for calloc()
 * r0..r9,ap,fp
 * are passed intact to the program to be booted.  r10 & r11 are
 * handled as before.  To accomplish this main() now is also passed
 * all registers (so it can manipulate r10 and r11) and
 * main now returns and we do popr then call "r0"
 * Also, eliminate the zeroing of memory from _end to $RELOC,
 * (I don't understand why this was ever done.) and make sure
 * to zero bss again if we load another standalone pgm.
 * Support for KA62a.
 * 
 *
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Saved R0-R12 for possible use by configure().
 *	[ V5.1(F8) ]
 *
 *  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush conditionals and requirement of features.h
 *
 * 28-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_NEWCPU: revised badloc() to dynamically determine
 *	whether or not a second size parameter has been provided.
 *	CS_BOOT: reimplemented simplified support for position
 *	independence and remembering boot parameters (especially
 *	for uVax-2).
 *
 *  2-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.  Added KA820 support.
 *
 **********************************************************************
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)srt0.c	7.1 (Berkeley) 6/5/86
 */

#include <vax/mtpr.h>
#define LOCORE
#include <vax/cpu.h>

/*
 * Startup code for standalone system
 * Non-relocating version -- for programs which are loaded by boot
 * Relocating version for boot*
 */

	.globl	_end
	.globl	_edata
	.globl	_main
	.globl	__rtt
	.globl	_configure
	.globl	_cpu
	.globl	_openfirst

	.set	HIGH,31			# mask for total disable

entry:	.globl	entry
	.word	0x0
	mtpr	$HIGH,$IPL		# just in case
	movl	r10, _unit_part_dev
#ifdef	REL
	/*
	 *  We need this portion of the code to be position independent so that
	 *  it can be loaded anywhere before relocating itself to RELOC.  In
	 *  particular, the secondary bootstrap loaded by the uVax-2 (bootrq)
	 *  will not be at location 0.  This code does assume, however, that it
	 *  will be loaded somewhere well below RELOC.
	 *
	 *  Also, save the general registers and the argument pointer so that
	 *  they will be on the stack when configure() is called and can be
	 *  treated as value-result parameters.  And what's good for configure()
	 *  is also good for main().  We've changed things so that main returns
	 *  to us, then we pop the registers and call the pgm that was loaded.
	 *  Thus the loaded program sees all the register values that the boot
	 *  rom set up.  (Except of course for r10, r11)
	 */
	movl	$RELOC,sp
	pushr	$0x1fff
	movab	_edata,r0
	movab	entry,r1
	subl2	r1,r0
	movc3	r0,entry,4*13(sp)
/*
 * Clear bss segment. r3 left setup by movc3
 */
clr:
	clrl	(r3)+
	cmpl	r3,$_end
	jlss	clr

	movpsl	-(sp)		/* psl */
	pushl	abegin		/* pc */
	rei			/* goto start and clear cache */
#else
	pushr	$0x1fff
	movab	_edata,r3
clr:
	clrl	(r3)+
	cmpl	r3,$_end
	jlss	clr
#endif
start:
	mtpr	$HIGH,$IPL		# we may "loop" load/exec'ing several standalone pgms
	mtpr	$0,$SCBB
	calls	$0,_configure
	movl	4*10(sp), _unit_part_dev
	movl	$1,_openfirst
#ifdef	REL
	clrl	_argv			/* 1st wd is count => 0 */
	calls	$0,_main
	movl	r0, entry_addr		/* save entry somewhere safe ... sigh */
	popr	$0x1fff
	pushr	$0x1fff			/* leave sp at RELOC-4*13 */
	callg	_argv,*entry_addr
#else	REL
	callg	_argv,_main
	ret				/* to reloc version */
#endif	REL
#ifndef	TP
	movl	$RELOC-4*13,sp		/* we should even get our regs back */
	movl	$_edata,r3		/* we need to zero bss again to forget state */
	jmp	clr
#else
	ret
#endif

	.data
entry_addr:	.long	0

	.comm	_argv, 4*15

/* No longer need data location with position independent change above */
#ifdef	REL
abegin:	.long	start
#endif

	.text
__rtt:					/* exit pgm to "monitor" */
	.word	0x0
#ifdef	REL
	halt
#else
	ret
#endif

	.globl	_bzero
_bzero:
	.word	0x0
	movl	4(ap), r0
	movl	8(ap), r1
	ashl	$-3, r1, r1
	clrl	r2
1:	clrq	(r0)[r2]
	aoblss	r1, r2, 1b
	ret

	.globl	_badloc
_badloc:
	.word	0
	/*
	 * Clean things up in case someone (bootrom?) left a mchk active
	 * Is presently known to be a problem with 82xx
	 */
	cmpl	_cpu, $VAX_820
	bneq	1f
	mtpr	$0xf,$MCESR
1:

	movl	$1,r0
	movl	4(ap),r3
	movl	$4,r2
	movab	9f,(r2)
	/*
	 *  Default to longword test if less than two arguments, otherwise
	 *  interpret the second argument as the target size (1=>byte, 2=>word,
	 *  4=>longword).  This variable size feature is used by the QVSS
	 *  driver to test for the presence of a display controller.
	 */
	cmpl	(ap),$2
	blss	2f
	bbc	$0,8(ap),1f; tstb (r3)
1:	bbc	$1,8(ap),1f; tstw (r3)
1:	bbc	$2,8(ap),1f;
2:
	tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	movl	$4,r2
	clrl	(r2)
	ret
	.align	2
9:
	casel	_cpu,$1,$VAX_MAX
0:
	.word	8f-0b		# 1 is 780
	.word	5f-0b		# 2 is 750
	.word	5f-0b		# 3 is 730
	.word	7f-0b		# 4 is 8600
	.word	5f-0b		# 5 is KA820 (8200)
	.word	5f-0b		# 6 is 8800
	.word	5f-0b		# 7 is K???? (uVAX-1)
	.word	5f-0b		# 8 is KA630 (uVAX-2)
	.word	1f-0b		# 9 is unknown
	.word	1f-0b		# 10 is KA650 (3x00)
	.word	1f-0b		# 11 is ka62a
5:
	mtpr	$0xf,$MCESR
	brb	1f
7:
	mtpr	$0,$EHSR
	brb	1f
8:
	mtpr	$0,$SBIFS
1:
	addl2	(sp)+,sp		# discard mchchk trash
	movab	2b,(sp)
	rei
