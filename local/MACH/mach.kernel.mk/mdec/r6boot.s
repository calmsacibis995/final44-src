/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * HISTORY
 * $Log:	r6boot.s,v $
 * Revision 2.3  89/02/26  14:14:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.1.1.1  88/08/08  16:48:53  rvb
 * Radical revision to pass all the registers r0-r9,ap,fp thru to
 * the 15 sector boot.  r10 and r11 are set to the device and flags
 * as is the Unix convention.  (sp) can not be saved.
 * I believe this is a good model for the 0 sector boots that assume
 * the "r6" contains the eeprom boot device block read routine.
 * Lastly, I can not understand why this boot should zero any memory
 * as previous versions did.
 * 
 *
 */

/*	raboot.s	6.1	83/07/29	*/

/*
 * loads next 7.5Kbytes using "r6" block loader from
 * boot sector of file system and sets it up to run.
 */
	.set	RELOC,0xc0000
	.set	BOOTSIZE,15		/* last boot sector */
	.set	BPSECT,512		/* bytes per sector */

init:
	.word	0
	nop;nop;nop;nop;nop
	nop;nop;nop;nop;nop;
	
start:
	movl	$RELOC,sp
	pushr	$0x33ff			/* fp, ap and r0-r9 => 12 words*/
	pushr	$0x3f			/* for movc3 => 6 words */
	moval	init,r10
	movc3	$end,(r10),4*(12+6)(sp)	/* back to reloc */
	popr	$0x3f			/* got state back */
	jmp	*$RELOC+start2

start2:					/* running relocated */
	clrl	r0
	movl	$1,r4			/* first boot sector */
	clrl	r5			/* transfer address */
	clrl	-(sp)			/* transfer address */
1:
	movl	r4,r8			/* requested sector # */
	jsb	(r6)			/* call ROM-based driver */
	blbs	r0,2f
	halt				/* read error */
2:
	addl2	$BPSECT,r5		/* bump address */
	movl	r5,(sp)
	aobleq	$BOOTSIZE,r4,1b

	tstl	(sp)+			/* pop transfer address */

	popr	$0x13ff
	movl	r5,r11			/* unix convention */
	movl	$9,r10			/* major("/dev/ra0a") */
	calls	$0,*$0			/* where unix is */
end:
