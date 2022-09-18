/*  
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/* 
 **********************************************************************
 * HISTORY
 * $Log:	88boot.s,v $
 * Revision 2.2  89/02/26  13:55:30  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */

/*
 *	File:	88boot.s
 *	Author:	Avadis Tevanian, Jr.
 *
 *	VAX 8800 bootstrap (called by VMB).  Reads in 7.5 K from sectors
 *	1-15 on the bootstrap device (as defined by VMB).
 */
	.set	RELOC,0xc0000
	.set	BOOTLAST,15		/* last boot sector */
	.set	RABPSECT,512
	.set	PROGADDR,0x100000	/* where to load prog */

init:
	.word	0  			/* entry mask for dec monitor */
start:
	movl	r11,r6			/* rpb address */
	movl	0x30(r6),r11		/* boot flags (r5 passed by VMB) */
	bicl2	$0x8,r11		/* clear VMB boot flag */
	movl	$RELOC,sp
	moval	init,r10
	movc3	$end,(r10),(sp)
	jmp	*$RELOC+start2
/* now running relocated */
/* bring in the boot program */
start2:					/* running relocated */
	pushr	$0xffff			/* BEGIN FIREWALL */
	movl	0x34(r6),r0		/* addr of driver */
	movl	0x38(r6),r1		/* size of driver */
	movl	$RELOC+64*1024,r5	/* where to put driver */
	movc3	r1,(r0),(r5)		/* copy driver */
	movl	$RELOC+64*1024,r11	/* addr of driver */
	addl2	(r11),r11		/* addr of routine in driver */
	movl	$1,r10			/* first boot sector */
	movl	$PROGADDR,r9		/* transfer address */
1:
	pushl	r6			/* RPB addr */
	pushl	$0			/* physical read mode */
	pushl	$33			/* logical block read */
	pushl	r10			/* block to read */
	pushl	$RABPSECT		/* size to read */
	pushl	r9			/* destination address */
	calls	$6,(r11)		/* call driver */
	blbs	r0,2f
	halt				/* read error */
2:
	addl2	$RABPSECT,r9		/* bump address */
	aobleq	$BOOTLAST,r10,1b

	.set	PROGSIZE,((BOOTLAST)*RABPSECT)
done:
/* copy program to low mem */
	movl	$PROGSIZE,r11
	movl	$PROGADDR,r1
	clrl	r3
0:	movl	$65535,r5
	cmpl	r11,r5
	bleq	1f
	subl2	r5,r11
	movc3	r5,(r1),(r3)		/* copy large chunk */
	brb	0b
1:	movc3	r11,(r1),(r3)		/* copy residual */
	popr	$0xffff			/* END FIREWALL */
	movl	$PROGSIZE,r3
clrcor:
	clrq	(r3)
	acbl	$RELOC,$8,r3,clrcor
/* start loaded program */
	movl	$9,r10			/* major("/dev/ra0a") */
	calls	$0,*$0
	brw	start2
end:
