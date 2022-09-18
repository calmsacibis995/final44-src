/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	movc.s,v $
 * Revision 2.13  91/04/05  15:39:54  mbj
 * 	Fix to bzero code in the cases of length <= 0 or == 2 or 3 bytes.
 * 	Bug found by Benjamin Britt of ISI
 * 	[91/02/26            mrt]
 * 
 * Revision 2.12  90/08/15  15:40:38  mrt
 * 	Added include of sys/errno.h for EFAULT
 * 	[90/08/15            mrt]
 * 
 * Revision 2.11  90/08/15  15:12:27  mrt
 * 	Wrote careful_bcopy() for careful_copy_to_physical().
 * 	[90/08/14            jjc]
 * 
 * Revision 2.10  90/07/20  10:08:21  mrt
 * 	It's back and working this time.  New bcopy and ovbcopy.
 * 	[90/05/07            rwd]
 * 
 * Revision 2.9  90/05/01  14:47:49  jjc
 * 	Backed out Randy Dean's new versions of bcopy() and ovbcopy() until the
 * 	bug associated with it is found.
 * 	[90/05/01  14:45:30  jjc]
 * 
 * Revision 2.5  89/02/25  19:45:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/17  21:35:04  rpd
 * 	Moved to sun3/.
 * 
 * Revision 2.3  89/01/17  02:16:37  rpd
 * 	Bzero was wrong if given a count < 3 and a non aligned pointer.
 * 	[89/01/16            rvb]
 * 
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Speed up bzero by using a sequence of moveml's to spray zeros.
 *
 */

	.data
	.asciz	"@(#)movc.s 1.1 86/02/03 Copyr 1984 Sun Micro"
	.even
	.text

|	Copyright (c) 1984 by Sun Microsystems, Inc.

#include <sun3/asm_linkage.h>
#include <assym.s>
#include <sys/errno.h>

| Copy a block of storage - must not overlap ( from + len <= to)
| Usage: bcopy(from, to, count)
	ENTRY(bcopy)
	link	a6,#0
	movl	a6@(8),a0
	movl	a6@(12),a1
	movl	a6@(16),d1
	beq	Done

	moveq	#64,d0
	cmpl	d1,d0
	bgt	Ints

Megas:	movl	d1,d0
	lsrl	#6,d1
	subql	#1,d1
LMega:	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	dbra	d1,LMega
	clrw	d1
	subql	#1,d1
	bcc	LMega
	moveq	#63,d1
	andl	d0,d1
	beq	Done

Ints:	moveq	#4,d0
	cmpl	d1,d0
	bgt	Bytes

	movl	d1,d0
	lsrl	#2,d1
	subql	#1,d1
LInts:	movl	a0@+,a1@+
	dbra	d1,LInts
	clrw	d1
	subql	#1,d1
	bcc 	LInts
	moveq	#3,d1
	andl	d0,d1
	beq	Done


Bytes:	subql	#1,d1
LBytes:	movb	a0@+,a1@+
	dbra	d1,LBytes
	clrw	d1
	subql	#1,d1
	bcc	LBytes
	bra	Done



	ENTRY(ovbcopy)
	link	a6,#0
	movl	a6@(8),a0
	movl	a6@(12),a1
	movl	a6@(16),d1
	beq	Done

	cmpl	a0,a1
	blt	Bytes

Back:	addl	d1,a0
	addl	d1,a1
	subql	#1,d1
LBack:	movb	a0@-,a1@-
	dbra	d1,LBack
	clrw	d1
	subql	#1,d1
	bcc	LBack

Done:	unlk	a6
	rts


| Zero block of storage
| Usage: bzero(addr, length)
	ENTRY2(bzero,blkclr)
	movl	sp@(4),a0	| address
	movl	sp@(8),d0	| length
	ble	5$
	clrl	d1		| use zero register to avoid clr fetches

	btst	#0, sp@(7)
	beqs	8f
		movb	d1, a0@+
		subql	#1, d0
		beq	5$	| bzero 1 byte -- silly
8:	btst	#1, sp@(7)
	beqs	9f
		movb	d1, a0@+
		subql	#1, d0
		beq	5$	| bzero 2 bytes -- silly
		movb	d1, a0@+
		subql	#1, d0
		beq	5$	| bzero 3 bytes -- silly

	| Now long word aligned
9:	cmpl	#512, d0
	blts	1$		| small move
		| a cycle clears 512 bytes
		addw	#-0x20, sp
		moveml	#0x78f0, sp@
		clrl	d7; clrl d6; clrl d5; clrl d4
		movl	d7, a6; movl d7, a5; movl d7, a4; movl d7, a3

		bras	6f
7:		moveml	#0x78f0, a0@
		moveml	#0x78f0, a0@(0x20)
		moveml	#0x78f0, a0@(0x40)
		moveml	#0x78f0, a0@(0x60)
		moveml	#0x78f0, a0@(0x80)
		moveml	#0x78f0, a0@(0xa0)
		moveml	#0x78f0, a0@(0xc0)
		moveml	#0x78f0, a0@(0xe0)
		addl	#0x100, a0
6:		subl	#0x100, d0
		bges	7b

		moveml	sp@, #0x78f0
		addw	#0x20, sp

		addl	#0x100, d0
		bgts	1$	| 255 or less to do
		rts		| no
		| end loop

1$:	movl	d0,a1		| save possibly adjusted count
	lsrl	#2,d0		| get count of longs
	beqs	0f		| less than 3 bytes left
	jra	3$		| go to loop test
		| Here is the fast inner loop - loop mode on 68010
2$:	movl	d1,a0@+		| store long
3$:	dbra	d0,2$		| decr count; br until done

| Now up to 3 bytes remain to be cleared
0:	movl	a1,d0		| restore count
	btst	#1,d0		| need a short word?
	jeq	4$		| no, skip
		movw	d1,a0@+	| do a short
4$:	btst	#0,d0		| need another byte
	jeq	5$		| no, skip
		movb	d1,a0@+	| do a byte
5$:	rts			| all done


|
| Set the thread recovery address to catch faults and then call bcopy().
| Returns 0 if successful.  EFAULT otherwise.
|
	ENTRY(careful_bcopy)
	linkw	a6, #-4
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
        movl    _active_threads,a0      | active thread on cpu
#endif  NCPUS > 1
	movl	#c_bcopy_err,a0@(THREAD_RECOVER)	| catch faults
	movl	a0, sp@			| save active thread
	movl	a6@(16),sp@-
	movl	a6@(12),sp@-
	movl	a6@(8),sp@-
	jsr	_bcopy
done:
	clrl	d0			| return success
	movl	a6@(-4),a0
	clrl	a0@(THREAD_RECOVER)	| clear recovery address
	unlk	a6
	rts
c_bcopy_err:
	movl	#EFAULT,d0		| return error
	movl	a6@(-4),a0
	clrl	a0@(THREAD_RECOVER)	| clear recovery address
	unlk	a6
	rts
