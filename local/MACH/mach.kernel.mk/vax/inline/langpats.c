/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	langpats.c,v $
 * Revision 2.7  89/03/09  22:15:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  20:19:44  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/15  16:36:38  rpd
 * 	Updated the complex lock substitutions for the new lock layout.
 * 	[89/01/15  15:22:03  rpd]
 * 
 * Revision 2.4  88/08/24  02:57:58  mwyoung
 * 	Further condensed conditionals into CMUCS.
 * 	[88/08/22            mwyoung]
 * 
 * Revision 2.3  88/08/10  10:24:10  rvb
 * 25-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Move splHIGH down to 1c  (to alloc VAX6200 WEI interrupts).
 * 	Same for splsched, save_context
 * 	Define splBLOCK to 1f (HIGH's old value) for use in probe code.
 * 
 *
 * 10-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Flush unused conditional include files and changed CS_KDB and
 *	CS_IPC conditionals to CS_GENERIC to prevent full
 *	recompilations when these options are altered.
 *	[ V5.1(XF21) ]
 *
 * 30-Sep-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed lock package replacements to match lock.c.  Simplified
 *	simple_lock and simple_unlock.
 *
 * 26-Sep-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add suword and fuword for MACH.
 *
 *  4-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	ESP isn't reliable between save_context and load_context.  Give
 *	up on using it for cpu_number.  Dispatch to model-dependent
 *	subroutine instead.
 *
 * 18-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Remove zalloc and zget.  These were depending on the location of
 *	fields in the zone structure (and likely to cause problems
 *	because of this).  If you can't spare the procedure call, you
 *	can use the ZALLOC and ZGET macros.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Define current_thread which uses the Vax supervisor stack
 *	pointer to save the current thread.
 *
 * 22-Mar-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add simple_lock_init.
 *	Add zalloc, zget.
 *
 * 13-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed lock_write to not clobber the can_sleep field.
 *
 *  4-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed old 'Queue' package (replaced by macros in h/queue.h)
 *	and flushed SPIN_LOCKS code.
 *
 * 26-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added remqueue.  Flushed MACH_ACC.
 *
 * 28-Jan-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fixed lock_write not to test no_sleep bit in lock - makes spin
 *	locks avoid C code.
 *
 * 29-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Updated to reflect recent changes elsewhere:
 *	removed mpqueue functions
 *	removed __queue, __dequeue (nowhere used)
 *	fixed enqueue_head to insert at the head of the queue - it had
 *	been inserting the new element as the second in the queue (!)
 *	Conditionalized several functions on MACH.
 *
 * 16-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added new bit field operators, to speed up IPC, and to eliminate
 *	the old obnoxious names.
 *
 * 14-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed "swtch" expansion on MACH.  Should probably
 *	remove other things destined for locore.
 *
 * 12-Sep-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added simple_lock_try, sleep locks, recursive locking.
 *
 * 24-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Documentation change.
 *
 * ??-Jul-86  Jim Wendorf (jww) at Carnegie-Mellon University
 *	(merged by dbg)
 *	Changed splvm from 0x18 to 0x17.
 * 
 * 29-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed copyin, copyout to always use jsb entries (as in old VM).
 *
 * 18-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Modified lock package to spin in the local cache on lock
 *	collisions.  This seems to be *necessary* for the KA820.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed new lock package and did some general cleanup.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#include <cpus.h>

#ifndef	lint
static char sccsid[] = "@(#)langpats.c	7.1 (Berkeley) 6/5/86";
#endif	not lint

#include <inline/inline.h>

/*
 * Pattern table for kernel specific routines.
 * These patterns are based on the old asm.sed script.
 */
struct pats language_ptab[] = {

	{ 0, "_spl0\n",
"	mfpr	$18,r0\n\
	mtpr	$0,$18\n" },

	{ 0, "_spl1\n",
"	mfpr	$18,r0\n\
	mtpr	$1,$18\n" },

	{ 0, "_splsoftclock\n",
"	mfpr	$18,r0\n\
	mtpr	$0x8,$18\n" },

	{ 0, "_splhdw\n",
"	mfpr	$18,r0\n\
	mtpr	$0xf,$18\n" },

	{ 0, "_splnet\n",
"	mfpr	$18,r0\n\
	mtpr	$0xc,$18\n" },

	{ 0, "_splimp\n",
"	mfpr	$18,r0\n\
	mtpr	$0x16,$18\n" },

	{ 0, "_spl4\n",
"	mfpr	$18,r0\n\
	mtpr	$0x14,$18\n" },

	{ 0, "_splbio\n",
"	mfpr	$18,r0\n\
	mtpr	$0x15,$18\n" },

	{ 0, "_spltty\n",
"	mfpr	$18,r0\n\
	mtpr	$0x15,$18\n" },

	{ 0, "_spl5\n",
"	mfpr	$18,r0\n\
	mtpr	$0x15,$18\n" },

	{ 0, "_spl6\n",
"	mfpr	$18,r0\n\
	mtpr	$0x16,$18\n" },

	{ 0, "_spl7\n",
"	mfpr	$18,r0\n\
	mtpr	$0x17,$18\n" },

	{ 0, "_splclock\n",
"	mfpr	$18,r0\n\
	mtpr	$0x18,$18\n" },

	{ 0, "_splblock\n",
"	mfpr	$18,r0\n\
	mtpr	$0x1f,$18\n" },

	{ 0, "_splhigh\n",
"	mfpr	$18,r0\n\
	mtpr	$0x1c,$18\n" },

	{ 1, "_splx\n",
"	movl	(sp)+,r0\n\
	mtpr	r0,$18\n" },

	{ 1, "_mfpr\n",
"	movl	(sp)+,r5\n\
	mfpr	r5,r0\n" },

	{ 2, "_mtpr\n",
"	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	mtpr	r5,r4\n" },

	{ 0, "_setsoftclock\n",
"	mtpr	$0x8,$0x14\n" },


	{ 3, "_copyin\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	jsb	_Copyin\n" },

	{ 3, "_copyout\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	jsb	_Copyout\n" },

	{ 1, "_fuword\n",
"	movl	(sp)+,r0\n\
	jsb	_Fuword\n" },

	{ 2, "_suword\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	jsb	_Suword\n" },



	{ 0, "_movpsl\n",		/* for kdb */
"	movpsl	r0\n" },

	{ 0, "_save_context\n",
"	movpsl	-(sp)\n\
	moval	2f,-(sp)\n\
	mtpr	$0x1c,$18\n\
	svpctx\n\
	clrl	r0\n\
	jbr	3f\n\
2:\n\
	movl	$1,r0\n\
3:\n"},

	{ 1, "_load_context\n",
"	movl	(sp)+,r0\n\
	jmp	_Load_context\n"},

	{ 0, "_cpu_number\n",
"	jsb	*_Cpu_number_ptr\n"},

	{ 0, "_current_thread\n",
"	mfpr	$0x2,r0\n"},
	{ 1, "_setjmp\n",
"	movl	(sp)+,r1\n\
	clrl	r0\n\
	movl	fp,(r1)+\n\
	moval	1(pc),(r1)\n" },

	{ 1, "_longjmp\n",
"	movl	(sp)+,r0\n\
	jsb	_Longjmp\n" },

	{ 1, "_ffs\n",
"	movl	(sp)+,r1\n\
	ffs	$0,$32,r1,r0\n\
	bneq	1f\n\
	mnegl	$1,r0\n\
1:\n\
	incl	r0\n" },

	{ 1, "_htons\n",
"	movl	(sp)+,r5\n\
	rotl	$8,r5,r0\n\
	rotl	$-8,r5,r1\n\
	movb	r1,r0\n\
	movzwl	r0,r0\n" },

	{ 1, "_ntohs\n",
"	movl	(sp)+,r5\n\
	rotl	$8,r5,r0\n\
	rotl	$-8,r5,r1\n\
	movb	r1,r0\n\
	movzwl	r0,r0\n" },

	{ 1, "_htonl\n",
"	movl	(sp)+,r5\n\
	rotl	$-8,r5,r0\n\
	insv	r0,$16,$8,r0\n\
	rotl	$8,r5,r1\n\
	movb	r1,r0\n" },

	{ 1, "_ntohl\n",
"	movl	(sp)+,r5\n\
	rotl	$-8,r5,r0\n\
	insv	r0,$16,$8,r0\n\
	rotl	$8,r5,r1\n\
	movb	r1,r0\n" },

	{ 2, "__insque\n",
"	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	insque	(r4),(r5)\n" },

	{ 1, "__remque\n",
"	movl	(sp)+,r5\n\
	remque	(r5),r0\n" },

	/*
	 *	Not used anywhere in kernel
	 */

	{ 2, "_imin\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r5\n\
	cmpl	r0,r5\n\
	bleq	1f\n\
	movl	r5,r0\n\
1:\n" },

	{ 2, "_imax\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r5\n\
	cmpl	r0,r5\n\
	bgeq	1f\n\
	movl	r5,r0\n\
1:\n" },

	{ 2, "_min\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r5\n\
	cmpl	r0,r5\n\
	blequ	1f\n\
	movl	r5,r0\n\
1:\n" },

	{ 2, "_max\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r5\n\
	cmpl	r0,r5\n\
	bgequ	1f\n\
	movl	r5,r0\n\
1:\n" },

	{ 2, "_enqueue_head\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	insque	(r1),(r0)\n" },

	{ 2, "_enqueue_tail\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	insque	(r1),*4(r0)\n" },

	{ 1, "_dequeue_head\n",
"	movl	(sp)+,r0\n\
	remque	*(r0),r0\n\
	bvc	1f\n\
	clrl	r0\n\
1:\n" },

	{ 1, "_dequeue_tail\n",
"	movl	(sp)+,r0\n\
	remque	*4(r0),r0\n\
	bvc	1f\n\
	clrl	r0\n\
1:\n" },

	{ 2, "_remqueue\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	remque	(r1),r0\n" },

	{ 2, "_SetBit\n",		/* for old IPC */
"	bbss	4(sp),*(sp),1f\n\
1:	addl2	$8,sp\n" },

	{ 2, "_ClearBit\n",		/* for old IPC */
"	bbcc	4(sp),*(sp),1f\n\
1:	addl2	$8,sp\n" },

	{ 2, "_TestBit\n",		/* for old IPC */
"	clrl	r0\n\
	bbc	4(sp),*(sp),1f\n\
	mcoml	r0,r0\n\
1:	addl2	$8,sp\n" },

	{ 3, "_bit_find_set\n",
"	movl	(sp)+, r0\n\
	subl3	r0, (sp)+, r1\n\
	movl	(sp)+, r2\n\
1:	cmpl	r1, $32\n\
	bleq	2f\n\
	ffs	r0, $32, (r2), r0\n\
	bneq	0f\n\
	subl2	$32, r1\n\
	bgtr	1b\n\
	jbr	0f\n\
2:	ffs	r0, r1, (r2), r0\n\
0:\n" },

	{ 2, "_bit_test\n",
"	extzv	(sp)+, $1, *(sp)+, r0\n" }, 

	{ 2, "_bit_set\n",
"	insv	$1, (sp)+, $1, *(sp)+\n" },

	{ 2, "_bit_clear\n",
"	insv	$0, (sp)+, $1, *(sp)+\n" },

	{ 0, "_splsched\n",
"	mfpr	$18,r0\n\
	mtpr	$0x1c,$18\n" },


	{ 0, "_splvm\n",
"	mfpr	$18,r0\n\
	mtpr	$0x17,$18\n" },
#if	NCPUS > 1
/*
 *	Lock module replacements... modeled after C code
 *	in ../kern/lock.c.  Does no waiting for stuck locks --
 *	calls C code unless the lock is easily obtained.
 */
	{ 1, "_simple_lock_init\n",
"	clrl	*(sp)+\n" },

	{ 1, "_simple_lock\n",		/* a write only lock */
"	movl	(sp)+,r0\n\
	brb	1f\n\
0:	blbs	(r0),0b\n\
1:	bbssi	$0,(r0),0b\n" },

	{ 1, "_simple_unlock\n",
"	movl	(sp)+,r0\n\
	bbcci	$0,(r0),0f\n\
0:\n" },

	{ 1, "_simple_lock_try\n",
"	movl	(sp)+,r0\n\
	bbssi	$0,(r0),1f\n\
	movl	$1,r0\n\
	brb	2f\n\
1:	clrl	r0\n\
2:\n" },


/*
 *	Sleep locks.  There are two versions, since sleep locks
 *	work even on uniprocessors.
 */

	{ 1, "_lock_write\n",
"	movl	(sp)+,r1\n\
	brb	1f\n\
0:	blbs	12(r1),0b\n\
1:	bbssi	$0,12(r1),0b\n\
	bitl	$0x3ffff,(r1)\n\
	beql	1f\n\
	bbcci	$0,12(r1),0f; 0:\n\
	pushl	r1\n\
	calls	$1,_lock_write\n\
	jbr	2f\n\
1:	bisl2	$0x020000,(r1)\n\
	bbcci	$0,12(r1),2f\n\
2:\n" },

	{ 1, "_lock_read\n",
"	movl	(sp)+,r1\n\
	brb	1f\n\
0:	blbs	12(r1),0b\n\
1:	bbssi	$0,12(r1),0b\n\
	bitl	$0x30000,(r1)\n\
	beql	1f\n\
	bbcci	$0,12(r1),0f; 0:\n\
	pushl	r1\n\
	calls	$1,_lock_read\n\
	jbr	2f\n\
1:	incl	(r1)\n\
	bbcci	$0,12(r1),2f\n\
2:\n" },

	{ 1, "_lock_done\n", 
"	movl	(sp)+,r1\n\
	brb	1f\n\
0:	blbs	12(r1),0b\n\
1:	bbssi	$0,12(r1),0b\n\
	tstw	(r1)\n\
	beql	0f\n\
	decl	(r1)\n\
	jbr	1f\n\
0:	tstl	8(r1)\n\
	beql	0f\n\
	decl	8(r1)\n\
	jbr	2f\n\
0:	bbsc	$16,(r1),1f\n\
	bicl2	$0x020000,(r1)\n\
1:\n\
	bbcc	$18,(r1),2f\n\
	pushl	r1\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
	movl	(sp)+,r1\n\
2:\n\
	bbcci	$0,12(r1),0f\n\
0:\n" },

	{ 1, "_lock_read_to_write\n",
"	movl	(sp)+,r1\n\
	brb	1f\n\
0:	blbs	12(r1),0b\n\
1:	bbssi	$0,12(r1),0b\n\
	mfpr	$0x2,r0\n\
	cmpl	r0,4(r1)\n\
	bneq	0f\n\
	decl	(r1)\n\
	incl	8(r1)\n\
	clrl	r0\n\
	jbr	3f\n\
0:\n\
	subl3	$1,(r1),r0\n\
	bbss	$16,r0,1f\n\
	tstw	r0\n\
	beql	2f\n\
	bbcci	$0,12(r1),0f; 0:\n\
	pushl	r1\n\
	calls	$1,_lock_read_to_write\n\
	jbr	0f\n\
2:	movl	r0,(r1)\n\
	clrl	r0\n\
	jbr	3f\n\
1:	movl	r0,(r1)\n\
	bbcc	$18,(r1),1f\n\
	pushl	r1\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
	movl	(sp)+,r1\n\
1:	movl	$1,r0\n\
3:	bbcci	$0,12(r1),0f; 0:\n" },

	{ 1, "_lock_write_to_read\n",
"	movl	(sp)+,r1\n\
	brb	1f\n\
0:	blbs	12(r1),0b\n\
1:	bbssi	$0,12(r1),0b\n\
	incl	(r1)\n\
	tstl	8(r1)\n\
	beql	0f\n\
	decl	8(r1)\n\
	jbr	2f\n\
0:	bbsc	$16,(r1),0f\n\
	bicl2	$0x020000,(r1)\n\
0:	bbcc	$18,(r1),2f\n\
	pushl	r1\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
	movl	(sp)+,r1\n\
2:\n\
	bbcci	$0,12(r1),0f; 0:\n" },

#else	NCPUS > 1
/*
 *	For a single cpu, spin locks aren't needed, but sleep locks are.
 *	They don't need the interlocks, however.
 */

	{ 1, "_lock_write\n",
"	movl	(sp)+,r1\n\
	bitl	$0x3ffff,(r1)\n\
	beql	1f\n\
	pushl	r1\n\
	calls	$1,_lock_write\n\
	jbr	2f\n\
1:	bisl2	$0x020000,(r1)\n\
2:\n" },

	{ 1, "_lock_read\n",
"	movl	(sp)+,r1\n\
	bitl	$0x30000,(r1)\n\
	beql	1f\n\
	pushl	r1\n\
	calls	$1,_lock_read\n\
	jbr	2f\n\
1:	incl	(r1)\n\
2:\n" },

	{ 1, "_lock_done\n", 
"	movl	(sp)+,r1\n\
	tstw	(r1)\n\
	beql	0f\n\
	decl	(r1)\n\
	jbr	1f\n\
0:	tstl	8(r1)\n\
	beql	0f\n\
	decl	8(r1)\n\
	jbr	2f\n\
0:	bbsc	$16,(r1),1f\n\
	bicl2	$0x020000,(r1)\n\
1:	bbcc	$18,(r1),2f\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
2:\n" },

	{ 1, "_lock_read_to_write\n",
"	movl	(sp)+,r1\n\
	mfpr	$0x2,r0\n\
	cmpl	r0,8(r1)\n\
	bneq	0f\n\
	decl	(r1)\n\
	incl	8(r1)\n\
	clrl	r0\n\
	jbr	3f\n\
0:\n\
	subl3	$1,(r1),r0\n\
	bbss	$16,r0,1f\n\
	tstw	r0\n\
	beql	2f\n\
	pushl	r1\n\
	calls	$1,_lock_read_to_write\n\
	jbr	3f\n\
2:	movl	r0,(r1)\n\
	clrl	r0\n\
	jbr	3f\n\
1:	movl	r0,(r1)\n\
	bbcc	$18,(r1),1f\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
1:	movl	$1,r0\n\
3:\n" },

	{ 1, "_lock_write_to_read\n",
"	movl	(sp)+,r1\n\
	incl	(r1)\n\
	tstl	8(r1)\n\
	beql	0f\n\
	decl	8(r1)\n\
	jbr	2f\n\
0:	bbsc	$16,(r1),0f\n\
	bicl2	$0x020000,(r1)\n\
0:	bbcc	$18,(r1),2f\n\
	pushl	r1\n\
	calls	$1,_thread_wakeup\n\
2:\n" },

#endif	NCPUS > 1

	{ 0, "", "" }
};
