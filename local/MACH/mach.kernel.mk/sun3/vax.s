/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vax.s,v $
 * Revision 2.5  89/03/09  21:39:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:48:29  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	context number is now a long -- fix movw.
 *
 * 16-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed to test FPA_USED bit in pcb_fpa_flags to
 *	see if FPA is being used.
 *	Modified load_context() not to restore the FPA context if
 *	the context was stolen.  Let trap() allocate a new context
 *	and do the restore then instead.
 *	Also, changed save_context() not to save the FPA context if
 *	it's been saved already because it was stolen or forked.
 *
 * 29-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Sun must call mcount with frompc, and selfpc as args when we use
 *	gcc since regs get reorganized.  The compiler would emit mcount
 *	which would then call the "counting" code correctly.  BUT,
 *	gprof knows enough to only subtract out the time accumulated by
 *	mcount and not this new routine.  So for now I'll use pcc to build
 *	this file.  The "correct mcount" is found in vax.s
 *
 * 26-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Don't flush cacr at syscall end; do it in load_context.
 *
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Rather than have "u" expand to current_thread()->u_address, have
 *	it expand to the constant U_ADDRESS which is updated by load_context
 *	when the thread changes.  So have load_context, load this data.
 *
 * 16-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define np_splhigh and np_splx for mcount to not themselves call
 *	mcount.
 *
 * 11-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to save FPA state in pcb in save_context() and
 *	restore it in load_context().
 *
 * 12-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added splr() from Sun Unix 3.4 version of this file.
 *
 *  4-Aug-87  David Golub (dbg) and Jonathan J. Chew (jjc)
 *			at Carnegie-Mellon University
 *	Flush u-area in save_context() in non-TT kernel.
 *
 * 20-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Modified for MACH.
 *
 * 18-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified "insque" and "remque" to lock out interrupts.
 *
 * 29-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created "save_context" and "load_context" routines from
 *	"resume".
 *	Replaced PCB_P0LR with PCB_FLAG from thread.
 *
 */

	.data
	.asciz	"@(#)vax.s 1.1 86/02/03 Copyr 1986 Sun Micro"
	.even
	.text
/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Emulate VAX instructions on the 68020.
 */

#include <cpus.h>

#include <sun3/cpu.h>
#include <sys/param.h>
#include <sun3/asm_linkage.h>
#include <sun3/enable.h>
#include <sun3/mmu.h>
#include <sun3/psl.h>
#include <fpa.h>
#if	NFPA > 0
#include <sundev/fpareg.h>
#endif	NFPA > 0
#include <assym.s>

/*
 * MACH uses inline for spl's
 */

#ifdef	GPROF
#ifdef	xxx				/* what's up, RVB? */
	.even
	.globl	_mmax_mcount
	.globl	mcount
mcount:
	movel	a6@(4),	sp@-		| frompc
	subql	#4, sp
	movel	sp@(4), sp@		| self
		/*
		 * mmax_mcount(selfpc, frompcindex)
		 */
	jbsr	_mmax_mcount
	addql	#8, sp
	rts
#endif	xxx
	.even
	.globl	_np_splhigh
_np_splhigh:
	movw	sr,d0
	movw	#SR_HIGH,sr
	rts

	.even
	.globl	_np_splx
_np_splx:
	movw	sr,d0
	movw	sp@(6),sr
	rts
#endif	GPROF

	ENTRY(_insque)
	movw	sr,d1		| save status register
	movw	#SR_HIGH,sr	| lock out interrupts
	movl	sp@(4),a0
	movl	sp@(8),a1
	movl	a1@,a0@
	movl	a1,a0@(4)
	movl	a0,a1@
	movl	a0@,a1
	movl	a0,a1@(4)
	movw	d1,sr		| restore status register
	rts

	ENTRY(_remque)
	movw	sr,d1		| save status register
	movw	#SR_HIGH,sr	| lock out interrupts
	movl	sp@(4),a0
	movl	a0@,a1
	movl	a0@(4),a0
	movl	a1,a0@
	movl	a0,a1@(4)
	movw	d1,sr		| restore status register
	rts

	ENTRY(scanc)
	movl	sp@(8),a0	| string
	movl	sp@(12),a1	| table
	movl	sp@(16),d1	| mask
	movl	d2,sp@-
	clrw	d2
	movl	sp@(8),d0	| len
	subqw	#1,d0		| subtract one for dbxx
	jmi	1f
2:
	movb	a0@+,d2		| get the byte from the string
	movb	a1@(0,d2:w),d2	| get the corresponding table entry
	andb	d1,d2		| apply the mask
	dbne	d0,2b		| check for loop termination
1:
	addqw	#1,d0		| dbxx off by one
	movl	sp@+,d2
	rts



/*
 * Sun 3.4 has a comment about not using the optimized code to avoid
 * saving/restoring the same fpa state:
 *
 * XXX - temporary this is optimization is not used until
 * we have per process enabling and disabling of '81 since
 * an frestore of null state resets the external '81 state.
 *
 * Since we don't understand what they're talking about, but assume that
 * they have some reason for doing so (;-), we'll conditionalize that code
 * here.
 */
#define USE_FPP_OPTIMIZATION	0

.globl	_active_threads

/*
 *	save_context()
 *
 *	Save the context of the active thread and return 0.
 *	NOTE:  Saves registers a2-a7 and d2-d7.
 */

#define SAVREGS		d2-d7/a2-a7

	ENTRY(save_context)
#if	NCPUS > 1
	CPU_NUMBER_D0			| current cpu number
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread on cpu
#endif	NCPUS > 1
	movl	a0,d1			| save active thread
	movl	a0@(THREAD_PCB),a0	| pointer to PCB of active thread
	tstw	_fppstate		| is fpp present and enabled?
	jle	1f			| branch if not
	fsave	a0@(PCB_FP_ISTATE)	| save internal state
	tstw	a0@(PCB_FP_ISTATE)	| test for null state
	jeq	1f			| branch if so
	fmovem	fpc/fps/fpi,a0@(PCB_FPS_CTRL) | save control registers
	fmovem	fp0-fp7,a0@(PCB_FPS_REGS)| save fp data registers
#if	USE_FPP_OPTIMIZATION
#if	NCPUS > 1
	lea	_fp_threads,a1
	movl	d1,a1@(0,d0:l:4)	| remember whose regs are still loaded
#else	NCPUS > 1
	movl	d1,_fp_threads		| remember whose regs are still loaded
#endif	NCPUS > 1
#endif	USE_FPP_OPTIMIZATION
1:
	movl	sp@,a1			| save return pc
	movl	a1,a0@(PCB_PC)		| save return pc in pcb
	movw	sr,a0@(PCB_SR+2)	| save current psw
	orw	#SR_INTPRI,sr		| mask interrupts
	moveml	d2-d7,a0@(PCB_D2)	| save data regs
	moveml	a2-a7,a0@(PCB_A2)	| save address regs

#if	NFPA > 0
/*
 * fpa_save() is inlined here to moveml 12 regs in two instructions.
 * We use a2 to contain the fpa address so that it is preserved across
 * the call to fpa_shutdown and we pick out SAVEFPA regs so that a2
 * is not used and we have a total of 12 regs.
 */
#define SAVEFPA		d0-d7/a3-a6
#define FPA_MAXLOOP	512

	movw	a0@(PCB_FPA_FLAGS),d0
	andl	#FPA_USED,d0
	tstl	d0			| test if this process uses FPA
	jeq	1f			| FPA is not used skip saving FPA regs
	movw	a0@(PCB_FPA_FLAGS),d0
	andl	#FPA_CTX_SAVED,d0
	tstl	d0			| test if saved FPA state already
	jne	1f			| Yes, skip save, but turn off FPA.
| Begin of assembly fpa_save
	movl	#FPA_MAXLOOP-1,d1	| loop at most FPA_MAXLOOP times
	movl	_fpa,a2			| get fpa adddress
0:
	movl	a2@(FPA_PIPE_STATUS),d0	| get status
	andl	#FPA_STABLE,d0		| test for stability
	bne	2f			| != 0 means pipe is stable
	dbra	d1,0b			| busy, try again
	jsr	_fpa_shutdown		| timed out, shut it down
	jra	3f			| skip reg save
2:
	moveml	a2@(FPA_STATE),SAVEFPA	| load 12 FPA regs
	moveml	SAVEFPA,a0@(PCB_FPA_STATUS) | save to pcb->pcb_fpa_status
	moveml	a0@(PCB_A2),a2-a7	| restore registers since messed up
	moveml	a0@(PCB_D2),d2-d7	| saving FPA state
3:
	andb	#~ENA_FPA,_enablereg	| turn off FPA enable bit so FPA is
	movb	_enablereg,d0		| protected from unexpected accesses
	movsb	d0,ENABLEREG
1:
#endif	NFPA > 0

	lea	eintstack,sp		| use the interrupt stack
	movl	#0,d0			| return 0
	jmp	a1@			| return to caller

/*
 *	Load context for specified thread and return 1.
 *
 *	load_context(thread)
 *	thread_t	thread;
 */
	ENTRY(load_context)
	jbsr	_load_context_data	| load up per context variables
					| must be first, since clobbers a0,a1
	movl	#CACHE_CLEAR+CACHE_ENABLE,d0	| flush old user context
	movc	d0,cacr				| and kernel (sigh)

	movl	sp@(4),a0		| save thread pointer
	movl	a0@(THREAD_PCB),a1	| get PCB
	moveq	#KCONTEXT,d0
	movsb	d0,CONTEXTBASE		| invalidate context
/*
 * Check to see if we already have context.
 * If so, then set up the next context.
 */
	movl	a0@(THREAD_TASK),a2	| thread->task
	movl	a2@(TASK_MAP),a2	| thread->task->map
	movl	a2@(VM_MAP_PMAP),a2	| thread->task->map->pmap
	movl	a2@(PMAP_CTX),a2	| thread->task->map->pmap->ctx (phew!)
	tstl	a2			| check thread->task->map->pmap->ctx
	jeq	1f			| if zero, skip ahead
	movl	a2@(CTX_CONTEXT),d0	| get context number in d0
	movsb	d0,CONTEXTBASE		| set up the context
1:
	tstw	_fppstate		| is fpp present and enabled?
	jle	1f			| branch if not
	tstw	a1@(PCB_FP_ISTATE)	| test for null state
	jeq	0f			| branch if so
#if	USE_FPP_OPTIMIZATION
#if	NCPUS > 1
	CPU_NUMBER_D0			| current cpu number
	lea	_fp_threads,a3
	movl	a3@(0,d0:l:4),a3	| fp thread on current cpu
	cmpl	a3,a2			| were we last thread using fpp?
#else	NCPUS > 1
	cmpl	_fp_threads,a2		| were we last thread using fpp?
#endif	NCPUS > 1
	beq	0f			| if so, jump and skip loading ext regs
#endif	USE_FPP_OPTIMIZATION
	fmovem	a1@(PCB_FPS_REGS:w),fp0-fp7 | restore fp data registers
	fmovem	a1@(PCB_FPS_CTRL),fpc/fps/fpi | restore control registers
0:
	frestore a1@(PCB_FP_ISTATE)	| restore internal state
#if	NFPA > 0
	
	movw	a1@(PCB_FPA_FLAGS),d0
	andl	#FPA_USED,d0
	tstl	d0			| test if this process uses FPA
	jeq	1f			| no, skip restoring FPA context
	movw	a1@(PCB_FPA_FLAGS),d0	| 
	andl	#FPA_CTX_SAVED,d0	| test if someone stole our context
	tstl	d0			| if yes, fault in a context in trap()
	jne	1f			| and do restore then
	movl	#0,sp@-			| push 0 (ie. not full restore)
	movl	a0,sp@-			| push thread
	jsr	_fpa_restore		| yes, restore FPA context
#endif	NFPA > 0
1:
	moveml	a1@(PCB_D2),d2-d7	| restore data/address regs
	moveml	a1@(PCB_A2),a2-a7
| Note: we just changed stacks
	movw	a1@(PCB_SR+2),sr
	movl	a1@(PCB_PC),sp@
	movl	#1,d0
	rts

