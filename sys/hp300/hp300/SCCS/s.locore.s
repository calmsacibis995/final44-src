h47210
s 00002/00002/02754
d D 8.6 94/05/27 08:51:37 hibler 32 31
c forgot to account for new stack alignment in initial startup code
c (from mycroft@sun-lamp.cs.berkeley.edu)
e
s 00081/00043/02675
d D 8.5 93/11/14 14:18:32 hibler 31 30
c cleanups, new copypage routine, MAPPEDCOPY code for copyin/out
e
s 00031/00031/02687
d D 8.4 93/09/23 16:20:10 bostic 30 29
c changes for 4.4BSD-Lite requested by USL
e
s 00023/00035/02695
d D 8.3 93/09/21 07:38:50 mckusick 29 28
c changes for 4.4BSD-Lite requested by USL
c NOT SEMANTIC SUGAR -- change to exec init, not hand-craft it
e
s 00007/00008/02723
d D 8.2 93/09/20 21:52:36 bostic 28 27
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/02729
d D 8.1 93/06/10 21:41:09 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/02726
d D 7.26 93/05/09 11:50:53 mckusick 26 25
c correctly define idle loop
e
s 00012/00014/02719
d D 7.25 93/04/30 18:20:35 mckusick 25 24
c replace dbf with subql/jne to get around 64K limit
e
s 00005/00000/02728
d D 7.24 93/04/18 18:50:23 mckusick 24 23
c allow for old variants of cpp
e
s 00009/00004/02719
d D 7.23 93/03/17 08:19:30 hibler 23 22
c make safe for ANSI cpp
e
s 00018/00011/02705
d D 7.22 93/02/18 21:18:49 hibler 22 21
c tighten up clock interrupt handling
e
s 00027/00000/02689
d D 7.21 92/12/30 12:56:18 hibler 21 20
c LED heartbeat code
e
s 00000/00006/02689
d D 7.20 92/12/28 09:14:40 hibler 20 19
c get rid of some garbage nops
e
s 00232/00174/02463
d D 7.19 92/12/27 09:48:22 hibler 19 18
c massive changes mostly related to stack alignment
e
s 00001/00001/02636
d D 7.18 92/10/11 09:42:37 bostic 18 17
c make kernel includes standard
e
s 00002/00001/02635
d D 7.17 92/08/03 13:57:59 hibler 17 16
c label trap instruction in sigcode to make it easier to locate
e
s 00021/00152/02615
d D 7.16 92/07/08 01:13:39 torek 16 15
c delete timebomb; more of clock code done in clock.c; 
c swtch => cpu_swtch; profiling clock no longer turned on and off;
c addupc now done in subr_prof.c; 
e
s 00029/00001/02738
d D 7.15 92/06/30 13:28:41 torek 15 14
c add fuswintr and suswintr
e
s 00001/00219/02738
d D 7.14 92/06/15 14:51:28 hibler 14 13
c get rid of BOOTDEBUG code
e
s 00468/00177/02489
d D 7.13 92/06/05 15:36:47 hibler 13 12
c merge latest Utah hp300 code including 68040 support
e
s 00002/00000/02664
d D 7.12 91/07/25 22:49:41 mckusick 12 11
c have to set the page size early on as it is needed in pmap_bootstrap
e
s 00002/00010/02662
d D 7.11 91/05/09 17:52:49 karels 11 10
c remove firstaddr parameter to main; if p->p_vmspace isn't null,
c chances are &p->p_vmspace.vm_pmap won't be either
e
s 00281/00277/02391
d D 7.10 91/05/07 09:57:26 hibler 10 9
c DIO-II support
c masterpaddr -> curpcb
c new stack adjustment code
c code reorganization
c got rid of special non-gcc GPROF spls
e
s 00045/00103/02623
d D 7.9 91/05/04 19:35:36 karels 9 8
c rm resume, merge into swtch; new savectx saves into new pcb/stack,
c pushing in new return value; spl's now in-line
e
s 00165/00097/02561
d D 7.8 91/05/01 12:05:59 karels 8 7
c remove _u: use p_addr for pcb, use _kstack for stack, merge swtch &
c resume (resume needed to know both old and new procs, now save all before
c restoring); change savectx to snapshot pcb and (optionally, for fork)
c arrange for alternate return by saving only alternate pc)
e
s 00040/00021/02618
d D 7.7 91/04/20 17:25:49 karels 7 6
c new kgdb_trap_glue; change icode for new gas notion of ".", and move initflags
c to main; maintain curproc, no noproc; runrun => want_resched; new proc struct
e
s 00002/00000/02637
d D 7.6 91/01/28 17:35:35 mckusick 6 5
c icode must live in data space so initflags can be written
e
s 00462/00351/02175
d D 7.5 90/12/05 18:53:45 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00003/00003/02523
d D 7.4 90/10/19 16:32:17 mckusick 4 3
c copyinstr/copyoutstr now return ENAMETOOLONG when name is too long
e
s 00002/00002/02524
d D 7.3 90/06/22 09:32:32 hibler 3 2
c T_AST -> T_ASTFLT to be more consisent with VAX
e
s 00015/00010/02511
d D 7.2 90/05/25 15:52:46 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 02521/00000/00000
d D 7.1 90/05/08 18:15:40 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 27
 * Copyright (c) 1980, 1990 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: locore.s 1.47 89/10/08$
E 5
I 5
D 10
 * from: Utah $Hdr: locore.s 1.2 90/07/14$
E 10
I 10
D 13
 * from: Utah $Hdr: locore.s 1.58 91/04/22$
E 13
I 13
D 19
 * from: Utah $Hdr: locore.s 1.62 92/01/20$
E 19
I 19
 * from: Utah $Hdr: locore.s 1.66 92/12/22$
E 19
E 13
E 10
E 5
 *
 *	%W% (Berkeley) %G%
 */

I 19
/*
 * STACKCHECK enables two types of kernel stack checking:
 *	1. stack "overflow".  On every clock interrupt we ensure that
 *	   the current kernel stack has not grown into the user struct
 *	   page, i.e. size exceeded UPAGES-1 pages.
 *	2. stack "underflow".  Before every rte to user mode we ensure
 *	   that we will be exactly at the base of the stack after the
 *	   exception frame has been popped.
 * Both checks are performed at splclock since they operate on the
 * global temporary stack.
 */
/* #define	STACKCHECK */

E 19
I 8
#include "assym.s"
D 18
#include "vectors.s"
E 18
I 18
#include <hp300/hp300/vectors.s>
E 18

E 8
I 5
#define MMUADDR(ar)	movl	_MMUbase,ar
#define CLKADDR(ar)	movl	_CLKbase,ar

I 19
/*
 * Temporary stack for a variety of purposes.
 * Try and make this the first thing is the data segment so it
 * is page aligned.  Note that if we overflow here, we run into
 * our text segment.
 */
	.data
	.space	NBPG
tmpstk:

E 19
E 5
	.text
/*
 * This is where we wind up if the kernel jumps to location 0.
 * (i.e. a bogus PC)  This is known to immediately follow the vector
 * table and is hence at 0x400 (see reset vector in vectors.s).
 */
	.globl	_panic
	pea	Ljmp0panic
	jbsr	_panic
	/* NOTREACHED */
Ljmp0panic:
	.asciz	"kernel jump to zero"
	.even

/*
 * Do a dump.
 * Called by auto-restart.
 */
	.globl	_dumpsys
	.globl	_doadump
_doadump:
	jbsr	_dumpsys
	jbsr	_doboot
	/*NOTREACHED*/

/*
 * Trap/interrupt vector routines
 */ 

	.globl	_trap, _nofault, _longjmp
_buserr:
	tstl	_nofault		| device probe?
D 13
	jeq	_addrerr		| no, handle as usual
E 13
I 13
	jeq	Lberr			| no, handle as usual
E 13
	movl	_nofault,sp@-		| yes,
	jbsr	_longjmp		|  longjmp(nofault)
I 13
Lberr:
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	_addrerr		| no, skip
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	clrl	sp@-			| stack adjust count
E 19
	moveml	#0xFFFF,sp@-		| save user registers
	movl	usp,a0			| save the user SP
D 19
	movl	a0,sp@(60)		|   in the savearea
	lea	sp@(64),a1		| grab base of HW berr frame
E 19
I 19
	movl	a0,sp@(FR_SP)		|   in the savearea
	lea	sp@(FR_HW),a1		| grab base of HW berr frame
E 19
	moveq	#0,d0
D 19
	movw	a1@(14),d0		| grab SSW
	movl	a1@(22),d1		| and fault VA
E 19
I 19
	movw	a1@(12),d0		| grab SSW
	movl	a1@(20),d1		| and fault VA
E 19
	btst	#11,d0			| check for mis-aligned access
	jeq	Lberr2			| no, skip
	addl	#3,d1			| yes, get into next page
	andl	#PG_FRAME,d1		| and truncate
Lberr2:
	movl	d1,sp@-			| push fault VA
	movl	d0,sp@-			| and padded SSW
	btst	#10,d0			| ATC bit set?
	jeq	Lisberr			| no, must be a real bus error
	movc	dfc,d1			| yes, get MMU fault
	movc	d0,dfc			| store faulting function code
	movl	sp@(4),a0		| get faulting address
	.word	0xf568			| ptestr a0@
	movc	d1,dfc
	.long	0x4e7a0805		| movc mmusr,d0
	movw	d0,sp@			| save (ONLY LOW 16 BITS!)
	jra	Lismerr
#endif
E 13
_addrerr:
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	clrl	sp@-			| stack adjust count
E 19
	moveml	#0xFFFF,sp@-		| save user registers
	movl	usp,a0			| save the user SP
D 19
	movl	a0,sp@(60)		|   in the savearea
	lea	sp@(64),a1		| grab base of HW berr frame
E 19
I 19
	movl	a0,sp@(FR_SP)		|   in the savearea
	lea	sp@(FR_HW),a1		| grab base of HW berr frame
E 19
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lbenot040		| no, skip
D 19
	movl	a1@(10),sp@-		| yes, push fault address
E 19
I 19
	movl	a1@(8),sp@-		| yes, push fault address
E 19
	clrl	sp@-			| no SSW for address fault
	jra	Lisaerr			| go deal with it
Lbenot040:
#endif
E 13
I 10
	moveq	#0,d0
E 10
D 19
	movw	a1@(12),d0		| grab SSW for fault processing
E 19
I 19
	movw	a1@(10),d0		| grab SSW for fault processing
E 19
	btst	#12,d0			| RB set?
	jeq	LbeX0			| no, test RC
	bset	#14,d0			| yes, must set FB
D 19
	movw	d0,a1@(12)		| for hardware too
E 19
I 19
	movw	d0,a1@(10)		| for hardware too
E 19
LbeX0:
	btst	#13,d0			| RC set?
	jeq	LbeX1			| no, skip
	bset	#15,d0			| yes, must set FC
D 19
	movw	d0,a1@(12)		| for hardware too
E 19
I 19
	movw	d0,a1@(10)		| for hardware too
E 19
LbeX1:
	btst	#8,d0			| data fault?
	jeq	Lbe0			| no, check for hard cases
D 19
	movl	a1@(18),d1		| fault address is as given in frame
E 19
I 19
	movl	a1@(16),d1		| fault address is as given in frame
E 19
	jra	Lbe10			| thats it
Lbe0:
D 19
	btst	#4,a1@(8)		| long (type B) stack frame?
E 19
I 19
	btst	#4,a1@(6)		| long (type B) stack frame?
E 19
	jne	Lbe4			| yes, go handle
D 19
	movl	a1@(4),d1		| no, can use save PC
E 19
I 19
	movl	a1@(2),d1		| no, can use save PC
E 19
	btst	#14,d0			| FB set?
	jeq	Lbe3			| no, try FC
	addql	#4,d1			| yes, adjust address
	jra	Lbe10			| done
Lbe3:
	btst	#15,d0			| FC set?
	jeq	Lbe10			| no, done
	addql	#2,d1			| yes, adjust address
	jra	Lbe10			| done
Lbe4:
D 19
	movl	a1@(38),d1		| long format, use stage B address
E 19
I 19
	movl	a1@(36),d1		| long format, use stage B address
E 19
	btst	#15,d0			| FC set?
	jeq	Lbe10			| no, all done
	subql	#2,d1			| yes, adjust address
Lbe10:
	movl	d1,sp@-			| push fault VA
D 10
	movw	d0,sp@-			| and SSW
	clrw	sp@-			|   padded to longword
E 10
I 10
	movl	d0,sp@-			| and padded SSW
E 10
D 19
	movw	a1@(8),d0		| get frame format/vector offset
E 19
I 19
	movw	a1@(6),d0		| get frame format/vector offset
E 19
	andw	#0x0FFF,d0		| clear out frame format
	cmpw	#12,d0			| address error vector?
	jeq	Lisaerr			| yes, go to it
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lbehpmmu		| yes, skip
	movl	d1,a0			| fault address
D 5
	.long	0xf0109e11		| ptestr #1,a0@,#7
	.long	0xf0176200		| pmove psr,sp@
E 5
I 5
	ptestr	#1,a0@,#7		| do a table search
	pmove	psr,sp@			| save result
E 5
	btst	#7,sp@			| bus error bit set?
	jeq	Lismerr			| no, must be MMU fault
	clrw	sp@			| yes, re-clear pad word
	jra	Lisberr			| and process as normal bus error
Lbehpmmu:
#endif
#if defined(HP320) || defined(HP350)
D 5
	lea	_IObase+MMUSTAT,a0	| no, get addr of MMU status
	movl	a0@,d0			| read status
E 5
I 5
	MMUADDR(a0)
	movl	a0@(MMUSTAT),d0		| read status
E 5
	btst	#3,d0			| MMU fault?
	jeq	Lisberr			| no, just a non-MMU bus error so skip
D 5
	andl	#~MMU_FAULT,a0@		| yes, clear fault bits
E 5
I 5
	andl	#~MMU_FAULT,a0@(MMUSTAT)| yes, clear fault bits
E 5
	movw	d0,sp@			| pass MMU stat in upper half of code
#endif
Lismerr:
	movl	#T_MMUFLT,sp@-		| show that we are an MMU fault
D 10
	jra	Lbexit			| and deal with it
E 10
I 10
	jra	Ltrapnstkadj		| and deal with it
E 10
Lisaerr:
	movl	#T_ADDRERR,sp@-		| mark address error
D 10
	jra	Lbexit			| and deal with it
E 10
I 10
	jra	Ltrapnstkadj		| and deal with it
E 10
Lisberr:
	movl	#T_BUSERR,sp@-		| mark bus error
D 10
Lbexit:
E 10
I 10
Ltrapnstkadj:
E 10
	jbsr	_trap			| handle the error
	lea	sp@(12),sp		| pop value args
D 19
	movl	sp@(60),a0		| restore user SP
E 19
I 19
	movl	sp@(FR_SP),a0		| restore user SP
E 19
	movl	a0,usp			|   from save area
D 10
	moveml	sp@+,#0x7FFF		| restore most user regs
	addql	#4,sp			| toss SSP
	tstw	sp@+			| do we need to clean up stack?
	jeq	rei			| no, just continue
	btst	#7,sp@(6)		| type 9/10/11 frame?
	jeq	rei			| no, nothing to do
	btst	#5,sp@(6)		| type 9?
	jne	Lbex1			| no, skip
	movw	sp@,sp@(12)		| yes, push down SR
	movl	sp@(2),sp@(14)		| and PC
	clrw	sp@(18)			| and mark as type 0 frame
	lea	sp@(12),sp		| clean the excess
E 10
I 10
D 19
	movw	sp@(64),d0		| need to adjust stack?
E 19
I 19
	movw	sp@(FR_ADJ),d0		| need to adjust stack?
E 19
	jne	Lstkadj			| yes, go to it
	moveml	sp@+,#0x7FFF		| no, restore most user regs
D 19
	addql	#6,sp			| toss SSP and pad
E 19
I 19
	addql	#8,sp			| toss SSP and stkadj
E 19
E 10
	jra	rei			| all done
D 10
Lbex1:
	btst	#4,sp@(6)		| type 10?
	jne	Lbex2			| no, skip
	movw	sp@,sp@(24)		| yes, push down SR
	movl	sp@(2),sp@(26)		| and PC
	clrw	sp@(30)			| and mark as type 0 frame
	lea	sp@(24),sp		| clean the excess
E 10
I 10
Lstkadj:
D 19
	lea	sp@(66),a1		| pointer to HW frame
E 19
I 19
	lea	sp@(FR_HW),a1		| pointer to HW frame
E 19
	addql	#8,a1			| source pointer
	movl	a1,a0			| source
	addw	d0,a0			|  + hole size = dest pointer
	movl	a1@-,a0@-		| copy
	movl	a1@-,a0@-		|  8 bytes
D 19
	movl	a0,sp@(60)		| new SSP
E 19
I 19
	movl	a0,sp@(FR_SP)		| new SSP
E 19
	moveml	sp@+,#0x7FFF		| restore user registers
	movl	sp@,sp			| and our SP
E 10
	jra	rei			| all done
D 10
Lbex2:
	movw	sp@,sp@(84)		| type 11, push down SR
	movl	sp@(2),sp@(86)		| and PC
	clrw	sp@(90)			| and mark as type 0 frame
	lea	sp@(84),sp		| clean the excess
	jra	rei			| all done
E 10

D 10
_illinst:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_ILLINST,d0
	jra	_fault
E 10
I 10
/*
 * FP exceptions.
 */
_fpfline:
I 13
#if defined(HP380)
	cmpw	#0x202c,sp@(6)		| format type 2?
	jne	_illinst		| no, not an FP emulation
#ifdef HPFPLIB
	.globl fpsp_unimp
	jmp	fpsp_unimp		| yes, go handle it
#else
D 19
	clrw	sp@-			| yes, pad SR
E 19
I 19
	clrl	sp@-			| stack adjust count
E 19
	moveml	#0xFFFF,sp@-		| save registers
	moveq	#T_FPEMULI,d0		| denote as FP emulation trap
	jra	fault			| do it
#endif
#else
E 13
	jra	_illinst
I 13
#endif
E 13
E 10

D 10
_zerodiv:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_ZERODIV,d0
	jra	_fault
E 10
I 10
_fpunsupp:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	_illinst		| no, treat as illinst
#ifdef HPFPLIB
	.globl	fpsp_unsupp
	jmp	fpsp_unsupp		| yes, go handle it
#else
D 19
	clrw	sp@-			| yes, pad SR
E 19
I 19
	clrl	sp@-			| stack adjust count
E 19
	moveml	#0xFFFF,sp@-		| save registers
	moveq	#T_FPEMULD,d0		| denote as FP emulation trap
	jra	fault			| do it
#endif
#else
E 13
	jra	_illinst
I 13
#endif
E 13
E 10

D 10
_chkinst:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_CHKINST,d0
	jra	_fault

_trapvinst:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_TRAPVINST,d0
	jra	_fault

_privinst:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_PRIVINST,d0
	jra	_fault

_coperr:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_COPERR,d0
	jra	_fault

_fmterr:
	clrw	sp@-
	moveml	#0xFFFF,sp@-
	moveq	#T_FMTERR,d0
	jra	_fault

_fptrap:
E 10
I 10
/*
 * Handles all other FP coprocessor exceptions.
 * Note that since some FP exceptions generate mid-instruction frames
 * and may cause signal delivery, we need to test for stack adjustment
 * after the trap call.
 */
_fpfault:
E 10
#ifdef FPCOPROC
D 19
	clrw	sp@-		| pad SR to longword
E 19
I 19
	clrl	sp@-		| stack adjust count
E 19
	moveml	#0xFFFF,sp@-	| save user registers
	movl	usp,a0		| and save
D 19
	movl	a0,sp@(60)	|   the user stack pointer
E 19
I 19
	movl	a0,sp@(FR_SP)	|   the user stack pointer
E 19
	clrl	sp@-		| no VA arg
D 8
	lea	_u+PCB_FPCTX,a0	| address of FP savearea
E 8
I 8
D 10
	movl	_masterpaddr,a0	| current pcb
E 10
I 10
	movl	_curpcb,a0	| current pcb
E 10
	lea	a0@(PCB_FPCTX),a0 | address of FP savearea
E 8
D 5
	.word	0xf310		| fsave a0@
E 5
I 5
	fsave	a0@		| save state
E 5
	tstb	a0@		| null state frame?
	jeq	Lfptnull	| yes, safe
	clrw	d0		| no, need to tweak BIU
	movb	a0@(1),d0	| get frame size
	bset	#3,a0@(0,d0:w)	| set exc_pend bit of BIU
Lfptnull:
D 5
	.word	0xf227,0xa800	| fmovem fpsr,sp@- (code arg)
	.word	0xf350		| frestore a0@
E 5
I 5
	fmovem	fpsr,sp@-	| push fpsr as code argument
	frestore a0@		| restore state
E 5
	movl	#T_FPERR,sp@-	| push type arg
D 10
	jbsr	_trap		| call trap
	lea	sp@(12),sp	| pop value args
	movl	sp@(60),a0	| restore
	movl	a0,usp		|   user SP
	moveml	sp@+,#0x7FFF	| and remaining user registers
	addql	#6,sp		| pop SSP and align word
	jra	rei		| all done
E 10
I 10
	jra	Ltrapnstkadj	| call trap and deal with stack cleanup
E 10
#else
	jra	_badtrap	| treat as an unexpected trap
#endif

I 13
#ifdef HPFPLIB
E 13
D 10
	.globl	_fault
_fault:
E 10
I 10
/*
I 13
 * We wind up here from the 040 FP emulation library after
 * the exception has been processed.
 */
	.globl	_fault
_fault:
	subql	#4,sp		| space for rts addr
	movl	d0,sp@-		| scratch register
	movw	sp@(14),d0	| get vector offset
	andl	#0xFFF,d0	| mask out frame type and clear high word
	cmpl	#0x100,d0	| HP-UX style reschedule trap?
	jne	Lfault1		| no, skip
	movl	sp@+,d0		| restore scratch register
	addql	#4,sp		| pop space
	jra	Lrei1		| go do AST
Lfault1:
	cmpl	#0xC0,d0	| FP exception?
	jlt	Lfault2		| no, skip
	movl	sp@+,d0		| yes, backoff
	addql	#4,sp		|  and prepare for normal trap frame
	jra	_fpfault	| go to it
Lfault2:
	addl	#Lvectab,d0	| convert to vector table offset
	exg	d0,a0
D 19
	movl	a0@,sp@(8) 	| get exception vector and save for rts
E 19
I 19
	movl	a0@,sp@(4) 	| get exception vector and save for rts
E 19
	exg	d0,a0
	movl	sp@+,d0		|   scratch registers
	rts			| return to handler from vectab
#endif

/*
E 13
 * Coprocessor and format errors can generate mid-instruction stack
 * frames and cause signal delivery hence we need to check for potential
 * stack adjustment.
 */
_coperr:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-		| stack adjust count
E 19
	moveml	#0xFFFF,sp@-
E 10
	movl	usp,a0		| get and save
D 19
	movl	a0,sp@(60)	|   the user stack pointer
E 19
I 19
	movl	a0,sp@(FR_SP)	|   the user stack pointer
E 19
	clrl	sp@-		| no VA arg
	clrl	sp@-		| or code arg
D 10
	movl	d0,sp@-		| push trap type
	jbsr	_trap		| handle trap
	lea	sp@(12),sp	| pop value args
	movl	sp@(60),a0	| restore
	movl	a0,usp		|   user SP
	moveml	sp@+,#0x7FFF	| restore most user regs
	addql	#6,sp		| pop SP and pad word
	jra	rei		| all done
E 10
I 10
	movl	#T_COPERR,sp@-	| push trap type
	jra	Ltrapnstkadj	| call trap and deal with stack adjustments
E 10

I 10
_fmterr:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-		| stack adjust count
E 19
	moveml	#0xFFFF,sp@-
	movl	usp,a0		| get and save
D 19
	movl	a0,sp@(60)	|   the user stack pointer
E 19
I 19
	movl	a0,sp@(FR_SP)	|   the user stack pointer
E 19
	clrl	sp@-		| no VA arg
	clrl	sp@-		| or code arg
	movl	#T_FMTERR,sp@-	| push trap type
	jra	Ltrapnstkadj	| call trap and deal with stack adjustments

/*
 * Other exceptions only cause four and six word stack frame and require
 * no post-trap stack adjustment.
 */
_illinst:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
	moveq	#T_ILLINST,d0
	jra	fault

_zerodiv:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
	moveq	#T_ZERODIV,d0
	jra	fault

_chkinst:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
	moveq	#T_CHKINST,d0
	jra	fault

_trapvinst:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
	moveq	#T_TRAPVINST,d0
	jra	fault

_privinst:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
	moveq	#T_PRIVINST,d0
	jra	fault

	.globl	fault
fault:
	movl	usp,a0			| get and save
D 19
	movl	a0,sp@(60)		|   the user stack pointer
E 19
I 19
	movl	a0,sp@(FR_SP)		|   the user stack pointer
E 19
	clrl	sp@-			| no VA arg
	clrl	sp@-			| or code arg
	movl	d0,sp@-			| push trap type
	jbsr	_trap			| handle trap
	lea	sp@(12),sp		| pop value args
D 19
	movl	sp@(60),a0		| restore
E 19
I 19
	movl	sp@(FR_SP),a0		| restore
E 19
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| restore most user regs
D 19
	addql	#6,sp			| pop SP and pad word
E 19
I 19
	addql	#8,sp			| pop SP and stack adjust
E 19
	jra	rei			| all done

E 10
	.globl	_straytrap
_badtrap:
I 10
D 19
	clrw	sp@-			| pad SR
E 19
	moveml	#0xC0C0,sp@-		| save scratch regs
D 19
	movw	sp@(24),sp@-		| push exception vector info
E 19
I 19
	movw	sp@(22),sp@-		| push exception vector info
E 19
E 10
	clrw	sp@-
D 10
	moveml	#0xC0C0,sp@-
	movw	sp@(24),sp@-
	clrw	sp@-
	jbsr	_straytrap
	addql	#4,sp
	moveml	sp@+,#0x0303
	addql	#2,sp
	jra	rei
E 10
I 10
D 19
	movl	sp@(24),sp@-		| and PC
E 19
I 19
	movl	sp@(22),sp@-		| and PC
E 19
	jbsr	_straytrap		| report
	addql	#8,sp			| pop args
	moveml	sp@+,#0x0303		| restore regs
D 19
	addql	#2,sp			| pop padding
E 19
	jra	rei			| all done
E 10

	.globl	_syscall
_trap0:
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	clrl	sp@-			| stack adjust count
E 19
	moveml	#0xFFFF,sp@-		| save user registers
	movl	usp,a0			| save the user SP
D 19
	movl	a0,sp@(60)		|   in the savearea
E 19
I 19
	movl	a0,sp@(FR_SP)		|   in the savearea
E 19
	movl	d0,sp@-			| push syscall number
	jbsr	_syscall		| handle it
	addql	#4,sp			| pop syscall arg
D 19
	movl	sp@(60),a0		| grab and restore
E 19
I 19
	movl	sp@(FR_SP),a0		| grab and restore
E 19
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| restore most registers
D 19
	addql	#6,sp			| pop SSP and align word
E 19
I 19
	addql	#8,sp			| pop SP and stack adjust
E 19
	jra	rei			| all done

/*
 * Routines for traps 1 and 2.  The meaning of the two traps depends
 * on whether we are an HPUX compatible process or a native 4.3 process.
 * Our native 4.3 implementation uses trap 1 as sigreturn() and trap 2
 * as a breakpoint trap.  HPUX uses trap 1 for a breakpoint, so we have
 * to make adjustments so that trap 2 is used for sigreturn.
 */
_trap1:
D 8
	btst	#PCB_TRCB,_u+PCB_FLAGS+1| being traced by an HPUX process?
E 8
I 8
D 19
	btst	#PCB_TRCB,pcbflag	| being traced by an HPUX process?
E 19
I 19
	btst	#MDP_TRCB,mdpflag	| being traced by an HPUX process?
E 19
E 8
	jeq	sigreturn		| no, trap1 is sigreturn
	jra	_trace			| yes, trap1 is breakpoint

_trap2:
D 8
	btst	#PCB_TRCB,_u+PCB_FLAGS+1| being traced by an HPUX process?
E 8
I 8
D 19
	btst	#PCB_TRCB,pcbflag	| being traced by an HPUX process?
E 19
I 19
	btst	#MDP_TRCB,mdpflag	| being traced by an HPUX process?
E 19
E 8
	jeq	_trace			| no, trap2 is breakpoint
	jra	sigreturn		| yes, trap2 is sigreturn

/*
I 10
 * Trap 12 is the entry point for the cachectl "syscall" (both HPUX & BSD)
 *	cachectl(command, addr, length)
 * command in d0, addr in a1, length in d1
 */
	.globl	_cachectl
_trap12:
	movl	d1,sp@-			| push length
	movl	a1,sp@-			| push addr
	movl	d0,sp@-			| push command
	jbsr	_cachectl		| do it
	lea	sp@(12),sp		| pop args
	jra	rei			| all done

/*
E 10
 * Trap 15 is used for:
 *	- KGDB traps
 *	- trace traps for SUN binaries (not fully supported yet)
 * We just pass it on and let trap() sort it all out
 */
I 7
D 10
	.globl	_kgdb_trap_glue
E 10
E 7
_trap15:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
I 7
#ifdef KGDB
E 7
	moveq	#T_TRAP15,d0
I 7
D 19
	movl	sp@(64),d1		| from user mode?
	andl	#PSL_S,d1
D 10
	jeq	_fault
E 10
I 10
	jeq	fault
E 19
I 19
	movw	sp@(FR_HW),d1		| get PSW
	andw	#PSL_S,d1		| from user mode?
	jeq	fault			| yes, just a regular fault
E 19
E 10
	movl	d0,sp@-
I 10
	.globl	_kgdb_trap_glue
E 10
	jbsr	_kgdb_trap_glue		| returns if no debugger
	addl	#4,sp
#endif
	moveq	#T_TRAP15,d0
E 7
D 10
	jra	_fault
E 10
I 10
	jra	fault
E 10

/*
 * Hit a breakpoint (trap 1 or 2) instruction.
 * Push the code and treat as a normal fault.
 */
_trace:
D 19
	clrw	sp@-
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-
I 7
#ifdef KGDB
E 7
	moveq	#T_TRACE,d0
I 7
D 19
	movl	sp@(64),d1		| from user mode?
	andl	#PSL_S,d1
D 10
	jeq	_fault
E 10
I 10
	jeq	fault
E 19
I 19
	movw	sp@(FR_HW),d1		| get SSW
	andw	#PSL_S,d1		| from user mode?
	jeq	fault			| no, regular fault
E 19
E 10
	movl	d0,sp@-
	jbsr	_kgdb_trap_glue		| returns if no debugger
	addl	#4,sp
#endif
	moveq	#T_TRACE,d0
E 7
D 10
	jra	_fault
E 10
I 10
	jra	fault
E 10

/*
 * The sigreturn() syscall comes here.  It requires special handling
 * because we must open a hole in the stack to fill in the (possibly much
 * larger) original stack frame.
 */
sigreturn:
	lea	sp@(-84),sp		| leave enough space for largest frame
	movl	sp@(84),sp@		| move up current 8 byte frame
	movl	sp@(88),sp@(4)
D 10
	movw	#0xFFFF,sp@-		| default: must clean stack
E 10
I 10
D 19
	movw	#84,sp@-		| default: adjust by 84 bytes
E 19
I 19
	movl	#84,sp@-		| default: adjust by 84 bytes
E 19
E 10
	moveml	#0xFFFF,sp@-		| save user registers
	movl	usp,a0			| save the user SP
D 19
	movl	a0,sp@(60)		|   in the savearea
E 19
I 19
	movl	a0,sp@(FR_SP)		|   in the savearea
E 19
	movl	#SYS_sigreturn,sp@-	| push syscall number
	jbsr	_syscall		| handle it
	addql	#4,sp			| pop syscall#
D 19
	movl	sp@(60),a0		| grab and restore
E 19
I 19
	movl	sp@(FR_SP),a0		| grab and restore
E 19
	movl	a0,usp			|   user SP
D 19
	lea	sp@(64),a1		| pointer to HW frame
D 10
	tstw	a1@+			| do we need to clean up stack?
E 10
I 10
	movw	a1@+,d0			| do we need to adjust the stack?
E 19
I 19
	lea	sp@(FR_HW),a1		| pointer to HW frame
	movw	sp@(FR_ADJ),d0		| do we need to adjust the stack?
E 19
E 10
	jeq	Lsigr1			| no, just continue
D 10
	movb	a1@(6),d0		| grab format byte
	lsrb	#4,d0			| get rid of excess
	cmpb	#10,d0			| type 10 frame?
	jne	Lsigr2			| no, continue
	movw	#32,d1			| yes, frame size is 32 bytes
	jra	Lsigrcp			| go to it
Lsigr2:
	cmpb	#9,d0			| type 9?
	jne	Lsigr3			| no, continue
	movw	#20,d1			| yes, frame size is 20 bytes
	jra	Lsigrcp			| go to it
Lsigr3:
	cmpb	#2,d0			| type 2?
	jne	Lsigr4			| no, continue
	movw	#12,d1			| yes, frame size is 12 bytes
	jra	Lsigrcp			| go to it
Lsigr4:
	movw	#8,d1			| must be type 0/1, size is 8 bytes
Lsigrcp:
E 10
I 10
	moveq	#92,d1			| total size
	subw	d0,d1			|  - hole size = frame size
E 10
	lea	a1@(92),a0		| destination
	addw	d1,a1			| source
	lsrw	#1,d1			| convert to word count
	subqw	#1,d1			| minus 1 for dbf
Lsigrlp:
	movw	a1@-,a0@-		| copy a word
	dbf	d1,Lsigrlp		| continue
	movl	a0,a1			| new HW frame base
Lsigr1:
D 19
	movl	a1,sp@(60)		| new SP value
E 19
I 19
	movl	a1,sp@(FR_SP)		| new SP value
E 19
	moveml	sp@+,#0x7FFF		| restore user registers
	movl	sp@,sp			| and our SP
	jra	rei			| all done

/*
 * Interrupt handlers.
 * All DIO device interrupts are auto-vectored.  Most can be configured
 * to interrupt in the range IPL3 to IPL5.  Here are our assignments:
 *
 *	Level 0:	Spurious: ignored.
 *	Level 1:	HIL
 *	Level 2:
D 13
 *	Level 3:	Internal HP-IB
E 13
I 13
 *	Level 3:	Internal HP-IB, DCM
E 13
 *	Level 4:	"Fast" HP-IBs, SCSI
D 13
 *	Level 5:	DMA, Ethernet, Built-in RS232
E 13
I 13
 *	Level 5:	DMA, Ethernet, Built-in RS232 (DCA)
E 13
 *	Level 6:	Clock
 *	Level 7:	Non-maskable: parity errors, RESET key
 */
D 19
	.globl	_hilint, _intrhand, _hardclock, _nmihand
E 19
I 19
	.globl	_hilint, _intrhand, _hardclock, _nmihand, _dmaintr
	.globl	_dcafastservice
E 19

_spurintr:
	addql	#1,_intrcnt+0
	addql	#1,_cnt+V_INTR
	jra	rei

_lev1intr:
D 19
	addql	#1,_intrcnt+4
	clrw	sp@-
E 19
	moveml	#0xC0C0,sp@-
	jbsr	_hilint
	moveml	sp@+,#0x0303
D 19
	addql	#2,sp
E 19
I 19
	addql	#1,_intrcnt+4
E 19
	addql	#1,_cnt+V_INTR
	jra	rei

D 19
/* check for DMA first to reduce overhead */
E 19
I 19
/*
 * Check for unbuffered serial port (DCA) interrupts first in an attempt
 * to minimize received character lossage.  Then we check for DMA activity
 * to reduce overhead there.
 */
E 19
_lev5intr:
D 19
	clrw	sp@-
E 19
	moveml	#0xC0C0,sp@-
D 19
	jbsr	_dmaintr
	tstl	d0
	jeq	Lnotdma
	addql	#1,_intrcnt+24
E 19
I 19
	tstl	_dcafastservice		| unbuffered port active?
	jeq	Ltrydma			| no, check DMA
	clrl	sp@-			| yes, check DCA port 0
	jbsr	_dcaintr		|    first to avoid overflow
	addql	#4,sp
	tstl	d0			| did it belong to DCA?
	jeq	Ltrydma			| no, go try DMA
E 19
	moveml	sp@+,#0x0303
D 19
	addql	#2,sp
E 19
I 19
	addql	#1,_intrcnt+20
E 19
	addql	#1,_cnt+V_INTR
	jra	rei
I 19
Ltrydma:
	jbsr	_dmaintr		| check DMA channels
	tstl	d0 			| was it ours?
	jeq	Lnotdma			| no, go poll other devices
	moveml	sp@+,#0x0303
	addql	#1,_intrcnt+24
	addql	#1,_cnt+V_INTR
	jra	rei
E 19

_lev2intr:
_lev3intr:
_lev4intr:
D 19
	clrw	sp@-
E 19
	moveml	#0xC0C0,sp@-
Lnotdma:
	lea	_intrcnt,a0
D 19
	movw	sp@(24),d0		| use vector offset
E 19
I 19
	movw	sp@(22),d0		| use vector offset
E 19
	andw	#0xfff,d0		|   sans frame type
	addql	#1,a0@(-0x60,d0:w)	|     to increment apropos counter
	movw	sr,sp@-			| push current SR value
	clrw	sp@-			|    padded to longword
	jbsr	_intrhand		| handle interrupt
	addql	#4,sp			| pop SR
	moveml	sp@+,#0x0303
D 19
	addql	#2,sp
E 19
	addql	#1,_cnt+V_INTR
	jra	rei

_lev6intr:
D 16
	clrw	sp@-
E 16
I 16
D 19
	clrw	sp@-			| pad ps
E 16
	moveml	#0xC0C0,sp@-
#ifdef DEBUG
	.globl	_panicstr, _regdump, _panic
D 16
	tstl	timebomb		| set to go off?
	jeq	Lnobomb			| no, skip it
	subql	#1,timebomb		| decrement
	jne	Lnobomb			| not ready to go off
	moveml	sp@+,#0x0303		| temporarily restore regs
D 9
	jra	Luseours		| go die
E 9
I 9
	jra	Lbomb			| go die
E 9
Lnobomb:
E 16
D 5
	cmpl	#_u+NBPG+NBPG,sp	| our we still in stack page?
E 5
I 5
D 8
	cmpl	#_u+NBPG,sp		| our we still in stack pages?
E 8
I 8
	cmpl	#_kstack+NBPG,sp	| are we still in stack pages?
E 19
I 19
#ifdef STACKCHECK
	.globl	_panicstr,_badkstack
	cmpl	#_kstack+NBPG,sp	| are we still in stack page?
E 19
E 8
E 5
	jcc	Lstackok		| yes, continue normally
I 9
D 10
	tstl	_curproc		| if !curproc, could have swtch_exit'ed,
E 10
I 10
D 23
	tstl	_curproc		| if !curproc could have swtch_exit'ed,
E 23
I 23
D 30
	tstl	_curproc		| if !curproc could have swtch_exited,
E 30
I 30
	tstl	_curproc		| if !curproc could have switch_exited,
E 30
E 23
E 10
	jeq	Lstackok		|     might be on tmpstk
E 9
	tstl	_panicstr		| have we paniced?
	jne	Lstackok		| yes, do not re-panic
D 5
	moveml	sp@+,#0x0303		| no, temporarily restore regs
	cmpl	#_u+NBPG+0x400,sp	| our we safely in redzone?
	jcc	Luseours		| yes, panic with this stack
E 5
D 19
	lea	tmpstk,sp		| no, switch to tmpstk
D 9
Luseours:
E 9
	moveml	#0xFFFF,sp@-		| push all registers
I 9
	movl	#Lstkrip,sp@-		| push panic message
	jbsr	_printf			| preview
E 19
I 19
	movl	sp@(4),tmpstk-4		| no, copy common
	movl	sp@,tmpstk-8		|  frame info
	movl	sp,tmpstk-16		| no, save original SP
	lea	tmpstk-16,sp		| switch to tmpstk
	moveml	#0xFFFE,sp@-		| push remaining registers
	movl	#1,sp@-			| is an overflow
	jbsr	_badkstack		| badkstack(1, frame)
E 19
	addql	#4,sp
E 9
D 19
	movl	sp,a0			| remember this spot
	movl	#256,sp@-		| longword count
	movl	a0,sp@-			| and reg pointer
	jbsr	_regdump		| dump core
	addql	#8,sp			| pop params
	movl	#Lstkrip,sp@-		| push panic message
	jbsr	_panic			| ES and D
I 9
D 16
Lbomb:
	moveml	#0xFFFF,sp@-		| push all registers
	movl	sp,a0			| remember this spot
	movl	#256,sp@-		| longword count
	movl	a0,sp@-			| and reg pointer
	jbsr	_regdump		| dump core
	addql	#8,sp			| pop params
	movl	#Lbomrip,sp@-		| push panic message
	jbsr	_panic			| ES and D
E 16
E 9
Lstkrip:
	.asciz	"k-stack overflow"
D 9
	.even
E 9
I 9
D 16
Lbomrip:
	.asciz	"timebomb"
E 16
I 10
	.even
E 19
I 19
	moveml	sp@+,#0x7FFF		| restore most registers
	movl	sp@,sp			| and SP
E 19
E 10
E 9
Lstackok:
#endif
I 19
	moveml	#0xC0C0,sp@-		| save scratch registers
E 19
D 5
	movb	_IObase+CLKSR,d0	| read clock status
E 5
I 5
	CLKADDR(a0)
I 16
D 22
	lea	sp@(16),a1		| a1 = &clockframe
E 22
E 16
	movb	a0@(CLKSR),d0		| read clock status
I 22
Lclkagain:
	btst	#0,d0			| clear timer1 int immediately to
	jeq	Lnotim1			|  minimize chance of losing another
	movpw	a0@(CLKMSB1),d1		|  due to statintr processing delay
Lnotim1:
E 22
E 5
D 16
#ifdef PROFTIMER
	.globl  _profon
	tstb	_profon			| profile clock on?
	jeq     Ltimer1			| no, then must be timer1 interrupt
E 16
	btst	#2,d0			| timer3 interrupt?
D 16
	jeq     Ltimer1			| no, must be timer1
D 5
	movb	_IObase+CLKMSB3,d1	| clear timer3 interrupt
E 5
I 5
	movb	a0@(CLKMSB3),d1		| clear timer3 interrupt
E 5
	lea	sp@(16),a1		| get pointer to PS
#ifdef GPROF
	.globl	_profclock
	movl	d0,sp@-			| save status so jsr will not clobber
	movl	a1@,sp@-		| push padded PS
	movl	a1@(4),sp@-		| push PC
	jbsr	_profclock		| profclock(pc, ps)
	addql	#8,sp			| pop params
#else
	btst	#5,a1@(2)		| saved PS in user mode?
	jne	Lttimer1		| no, go check timer1
D 8
	tstl	_u+U_PROFSCALE		| process being profiled?
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	tstl	a0@(U_PROFSCALE)	| process being profiled?
E 8
	jeq	Lttimer1		| no, go check timer1
	movl	d0,sp@-			| save status so jsr will not clobber
	movl	#1,sp@-
D 8
	movl	#_u+U_PROF,sp@-
E 8
I 8
	pea	a0@(U_PROF)
E 8
	movl	a1@(4),sp@-
	jbsr    _addupc			| addupc(pc, &u.u_prof, 1)
	lea	sp@(12),sp		| pop params
#endif
	addql	#1,_intrcnt+32		| add another profile clock interrupt
	movl	sp@+,d0			| get saved clock status
E 16
I 16
D 22
	jeq	1f			| no, skip statintr
I 19
	movb	a0@(CLKMSB3),d1		| clear timer3 interrupt
E 19
	addql	#1,_intrcnt+32		| count statclock interrupts
E 22
I 22
	jeq	Lnotim3			| no, skip statclock
	movpw	a0@(CLKMSB3),d1		| clear timer3 interrupt
	addql	#1,_intrcnt+32		| count clock interrupts
	lea	sp@(16),a1		| a1 = &clockframe
E 22
	movl	d0,sp@-			| save status
	movl	a1,sp@-
	jbsr	_statintr		| statintr(&frame)
	addql	#4,sp
D 19
	movl	sp@+,d0			| restore registers
E 19
I 19
D 22
	movl	sp@+,d0			| restore status
E 22
I 22
	movl	sp@+,d0			| restore pre-statintr status
E 22
E 19
E 16
I 5
	CLKADDR(a0)
E 5
D 16
Lttimer1:
E 16
I 16
D 22
	lea	sp@(16),a1
1:
E 22
I 22
Lnotim3:
E 22
E 16
	btst	#0,d0			| timer1 interrupt?
D 16
	jeq     Ltimend		        | no, check state of kernel profiling
Ltimer1:
#endif
E 16
I 16
D 22
	jeq	2f			| no, skip hardclock
E 16
D 5
	movb	_IObase+CLKMSB1,d1	| clear timer1 interrupt
E 5
I 5
	movb	a0@(CLKMSB1),d1		| clear timer1 interrupt
E 22
I 22
	jeq	Lrecheck		| no, skip hardclock
E 22
E 5
D 16
	lea	sp@(16),a1		| get pointer to PS
	movl	a1@,sp@-		| push padded PS
	movl	a1@(4),sp@-		| push PC
	jbsr	_hardclock		| call generic clock int routine
	addql	#8,sp			| pop params
	addql	#1,_intrcnt+28		| add another system clock interrupt
#ifdef PROFTIMER
Ltimend:
#ifdef GPROF
	.globl	_profiling, _startprofclock
	tstl	_profiling		| kernel profiling desired?
	jne	Ltimdone		| no, all done
	bset	#7,_profon		| mark continuous timing
	jne	Ltimdone		| was already enabled, all done
	jbsr	_startprofclock		| else turn it on
Ltimdone:
#endif
#endif
E 16
I 16
	addql	#1,_intrcnt+28		| count hardclock interrupts
I 22
	lea	sp@(16),a1		| a1 = &clockframe
E 22
	movl	a1,sp@-
I 21
#ifdef USELEDS
	.globl	_ledaddr, _inledcontrol, _ledcontrol, _hz
	tstl	_ledaddr		| using LEDs?
	jeq	Lnoled0			| no, skip this code
	movl	heartbeat,d0		| get tick count
	addql	#1,d0			|  increment
	movl	_hz,d1
	lsrl	#1,d1			| throb twice a second
	cmpl	d0,d1			| are we there yet?
	jne	Lnoled1			| no, nothing to do
	tstl	_inledcontrol		| already updating LEDs?
	jne	Lnoled2			| yes, skip it
	movl	#LED_PULSE,sp@-
	movl	#LED_DISK+LED_LANRCV+LED_LANXMT,sp@-
	clrl	sp@-
	jbsr	_ledcontrol		| toggle pulse, turn all others off
	lea	sp@(12),sp
Lnoled2:
	movql	#0,d0
Lnoled1:
	movl	d0,heartbeat
Lnoled0:
#endif
E 21
	jbsr	_hardclock		| hardclock(&frame)
	addql	#4,sp
D 22
2:
E 16
D 19
	moveml	sp@+,#0x0303		| restore scratch regs
	addql	#2,sp			| pop pad word
E 19
I 19
	moveml	sp@+,#0x0303		| restore scratch registers
E 22
I 22
	CLKADDR(a0)
Lrecheck:
E 22
E 19
	addql	#1,_cnt+V_INTR		| chalk up another interrupt
I 22
	movb	a0@(CLKSR),d0		| see if anything happened
	jmi	Lclkagain		|  while we were in hardclock/statintr
	moveml	sp@+,#0x0303		| restore scratch registers
E 22
	jra	rei			| all done

_lev7intr:
D 16
#ifdef PROFTIMER
E 16
	addql	#1,_intrcnt+36
D 16
#else
	addql	#1,_intrcnt+32
#endif
E 16
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	clrl	sp@-
E 19
	moveml	#0xFFFF,sp@-		| save registers
	movl	usp,a0			| and save
D 19
	movl	a0,sp@(60)		|   the user stack pointer
E 19
I 19
	movl	a0,sp@(FR_SP)		|   the user stack pointer
E 19
	jbsr	_nmihand		| call handler
D 19
	movl	sp@(60),a0		| restore
E 19
I 19
	movl	sp@(FR_SP),a0		| restore
E 19
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| and remaining registers
D 19
	addql	#6,sp			| pop SSP and align word
E 19
I 19
	addql	#8,sp			| pop SP and stack adjust
E 19
	jra	rei			| all done

/*
 * Emulation of VAX REI instruction.
 *
 * This code deals with checking for and servicing ASTs
 * (profiling, scheduling) and software interrupts (network, softclock).
 * We check for ASTs first, just like the VAX.  To avoid excess overhead
D 3
 * the T_AST handling code will also check for software interrupts so we
E 3
I 3
 * the T_ASTFLT handling code will also check for software interrupts so we
E 3
D 19
 * do not have to do it here.
E 19
I 19
 * do not have to do it here.  After identifing that we need an AST we
 * drop the IPL to allow device interrupts.
E 19
 *
 * This code is complicated by the fact that sendsig may have been called
D 13
 * necessitating a stack cleanup.  A cleanup should only be needed at this
 * point for coprocessor mid-instruction frames (type 9), but we also test
 * for bus error frames (type 10 and 11).
E 13
I 13
 * necessitating a stack cleanup.
E 13
 */
	.comm	_ssir,1
I 8
	.globl	_astpending
E 8
rei:
D 19
#ifdef DEBUG
E 19
I 19
#ifdef STACKCHECK
E 19
	tstl	_panicstr		| have we paniced?
D 19
	jne	Ldorte			| yes, do not make matters worse
E 19
I 19
	jne	Ldorte1			| yes, do not make matters worse
E 19
#endif
D 8
	btst	#PCB_ASTB,_u+PCB_FLAGS+1| AST pending?
E 8
I 8
	tstl	_astpending		| AST pending?
E 8
	jeq	Lchksir			| no, go check for SIR
I 13
Lrei1:
E 13
	btst	#5,sp@			| yes, are we returning to user mode?
	jne	Lchksir			| no, go check for SIR
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	movw	#PSL_LOWIPL,sr		| lower SPL
	clrl	sp@-			| stack adjust
E 19
	moveml	#0xFFFF,sp@-		| save all registers
	movl	usp,a1			| including
D 19
	movl	a1,sp@(60)		|    the users SP
E 19
I 19
	movl	a1,sp@(FR_SP)		|    the users SP
E 19
	clrl	sp@-			| VA == none
	clrl	sp@-			| code == none
D 3
	movl	#T_AST,sp@-		| type == async system trap
E 3
I 3
	movl	#T_ASTFLT,sp@-		| type == async system trap
E 3
	jbsr	_trap			| go handle it
	lea	sp@(12),sp		| pop value args
D 13
	movl	sp@(60),a0		| restore
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| and all remaining registers
	addql	#4,sp			| toss SSP
	tstw	sp@+			| do we need to clean up stack?
	jeq	Ldorte			| no, just continue
	btst	#7,sp@(6)		| type 9/10/11 frame?
	jeq	Ldorte			| no, nothing to do
	btst	#5,sp@(6)		| type 9?
	jne	Last1			| no, skip
	movw	sp@,sp@(12)		| yes, push down SR
	movl	sp@(2),sp@(14)		| and PC
	clrw	sp@(18)			| and mark as type 0 frame
	lea	sp@(12),sp		| clean the excess
	jra	Ldorte			| all done
Last1:
	btst	#4,sp@(6)		| type 10?
	jne	Last2			| no, skip
	movw	sp@,sp@(24)		| yes, push down SR
	movl	sp@(2),sp@(26)		| and PC
	clrw	sp@(30)			| and mark as type 0 frame
	lea	sp@(24),sp		| clean the excess
	jra	Ldorte			| all done
Last2:
	movw	sp@,sp@(84)		| type 11, push down SR
	movl	sp@(2),sp@(86)		| and PC
	clrw	sp@(90)			| and mark as type 0 frame
	lea	sp@(84),sp		| clean the excess
	jra	Ldorte			| all done
E 13
I 13
D 19
	movl	sp@(60),a0		| restore user SP
E 19
I 19
	movl	sp@(FR_SP),a0		| restore user SP
E 19
	movl	a0,usp			|   from save area
D 19
	movw	sp@(64),d0		| need to adjust stack?
E 19
I 19
	movw	sp@(FR_ADJ),d0		| need to adjust stack?
E 19
	jne	Laststkadj		| yes, go to it
	moveml	sp@+,#0x7FFF		| no, restore most user regs
D 19
	addql	#6,sp			| toss SSP and pad
E 19
I 19
	addql	#8,sp			| toss SP and stack adjust
#ifdef STACKCHECK
	jra	Ldorte
#else
E 19
	rte				| and do real RTE
I 19
#endif
E 19
Laststkadj:
D 19
	lea	sp@(66),a1		| pointer to HW frame
E 19
I 19
	lea	sp@(FR_HW),a1		| pointer to HW frame
E 19
	addql	#8,a1			| source pointer
	movl	a1,a0			| source
	addw	d0,a0			|  + hole size = dest pointer
	movl	a1@-,a0@-		| copy
	movl	a1@-,a0@-		|  8 bytes
D 19
	movl	a0,sp@(60)		| new SSP
E 19
I 19
	movl	a0,sp@(FR_SP)		| new SSP
E 19
	moveml	sp@+,#0x7FFF		| restore user registers
	movl	sp@,sp			| and our SP
D 19
	rte				| and return
E 19
I 19
#ifdef STACKCHECK
	jra	Ldorte
#else
	rte				| and do real RTE
#endif
E 19
E 13
Lchksir:
	tstb	_ssir			| SIR pending?
	jeq	Ldorte			| no, all done
	movl	d0,sp@-			| need a scratch register
	movw	sp@(4),d0		| get SR
	andw	#PSL_IPL7,d0		| mask all but IPL
	jne	Lnosir			| came from interrupt, no can do
	movl	sp@+,d0			| restore scratch register
Lgotsir:
	movw	#SPL1,sr		| prevent others from servicing int
	tstb	_ssir			| too late?
	jeq	Ldorte			| yes, oh well...
D 19
	clrw	sp@-			| pad SR to longword
E 19
I 19
	clrl	sp@-			| stack adjust
E 19
	moveml	#0xFFFF,sp@-		| save all registers
	movl	usp,a1			| including
D 19
	movl	a1,sp@(60)		|    the users SP
E 19
I 19
	movl	a1,sp@(FR_SP)		|    the users SP
E 19
	clrl	sp@-			| VA == none
	clrl	sp@-			| code == none
	movl	#T_SSIR,sp@-		| type == software interrupt
	jbsr	_trap			| go handle it
	lea	sp@(12),sp		| pop value args
D 19
	movl	sp@(60),a0		| restore
E 19
I 19
	movl	sp@(FR_SP),a0		| restore
E 19
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| and all remaining registers
D 19
	addql	#6,sp			| pop SSP and align word
E 19
I 19
	addql	#8,sp			| pop SP and stack adjust
#ifdef STACKCHECK
	jra	Ldorte
#else
E 19
	rte
I 19
#endif
E 19
Lnosir:
	movl	sp@+,d0			| restore scratch register
Ldorte:
I 19
#ifdef STACKCHECK
	movw	#SPL6,sr		| avoid trouble
	btst	#5,sp@			| are we returning to user mode?
	jne	Ldorte1			| no, skip it
	movl	a6,tmpstk-20
	movl	d0,tmpstk-76
	moveq	#0,d0
	movb	sp@(6),d0		| get format/vector
	lsrl	#3,d0			| convert to index
	lea	_exframesize,a6		|  into exframesize
	addl	d0,a6			|  to get pointer to correct entry
	movw	a6@,d0			| get size for this frame
	addql	#8,d0			| adjust for unaccounted for bytes
	lea	_kstackatbase,a6	| desired stack base
	subl	d0,a6			|   - frame size == our stack
	cmpl	a6,sp			| are we where we think?
	jeq	Ldorte2			| yes, skip it
	lea	tmpstk,a6		| will be using tmpstk
	movl	sp@(4),a6@-		| copy common
	movl	sp@,a6@-		|   frame info
	clrl	a6@-
	movl	sp,a6@-			| save sp
	subql	#4,a6			| skip over already saved a6
	moveml	#0x7FFC,a6@-		| push remaining regs (d0/a6/a7 done)
	lea	a6@(-4),sp		| switch to tmpstk (skip saved d0)
	clrl	sp@-			| is an underflow
	jbsr	_badkstack		| badkstack(0, frame)
	addql	#4,sp
	moveml	sp@+,#0x7FFF		| restore most registers
	movl	sp@,sp			| and SP
	rte
Ldorte2:
	movl	tmpstk-76,d0
	movl	tmpstk-20,a6
Ldorte1:
#endif
E 19
	rte				| real return

/*
D 5
 * System page table
 * Mbmap, Usrptmap, and Usriomap are enlarged by CLSIZE entries
 * as they are managed by resource maps starting with index 1 or CLSIZE.
 * Usrptmap is allocated last so that we can also use the pad space up
 * to eSysmap. (no point in wasting it!)
 */ 
#define	vaddr(x)	x-_Sysmap/4*NBPG
#define SYSMAP(mname,vname,size) \
	.globl	_/**/mname,_/**/vname; \
_/**/mname: \
	.space	size*4; \
	_/**/vname = vaddr(_/**/mname)
#define	ADDMAP(npte)	.space	npte*4

E 5
I 5
D 8
 * Kernel access to the current processes user struct is via a fixed
E 8
I 8
 * Kernel access to the current processes kernel stack is via a fixed
E 8
 * virtual address.  It is at the same address as in the users VA space.
D 8
 * Umap contains the KVA of the first of UPAGES PTEs mapping VA _u.
E 8
I 8
 * Umap contains the KVA of the first of UPAGES PTEs mapping VA _kstack.
E 8
 */
E 5
	.data
D 5
	SYSMAP(Sysmap	,Sysbase	,SYSPTSIZE	)
	SYSMAP(Forkmap	,forkutl	,UPAGES		)
	SYSMAP(Xswapmap	,xswaputl	,UPAGES		)
	SYSMAP(Xswap2map,xswap2utl	,UPAGES		)
	SYSMAP(Swapmap	,swaputl	,UPAGES		)
	SYSMAP(Pushmap	,pushutl	,UPAGES		)
	SYSMAP(Vfmap	,vfutl		,UPAGES		)
	SYSMAP(CMAP1	,CADDR1		,1		)
	SYSMAP(CMAP2	,CADDR2		,1		)
	SYSMAP(mmap	,vmmap		,1		)
	SYSMAP(msgbufmap,msgbuf		,MSGBUFPTECNT	)
	SYSMAP(Umap	,u		,UPAGES		)
	SYSMAP(Mbmap	,mbutl		,NMBCLUSTERS*MCLBYTES/NBPG+CLSIZE )
	/*
	 * This is the map used by the kernel memory allocator.
	 * It is expanded as necessary by the special features
	 * that use it.
	 *
	 * XXX: NEED way to compute kmem size from maxusers,
	 * device complement
	 */
	SYSMAP(kmempt	,kmembase	,NKMEMCLUSTERS*CLSIZE )
#ifdef	SYSVSHM
				ADDMAP(	SHMMAXPGS	)
#endif
#ifdef	GPROF
				ADDMAP(	768*1024/NBPG	)
#endif
	SYSMAP(ekmempt	,kmemlimit	,0		)
	SYSMAP(IOmap	,IObase		,IOMAPSIZE	)   /* map DIO space */
	SYSMAP(eIOmap	,IOlimit	,0		)
#if defined(HP360) || defined(HP370)
	SYSMAP(Grfmap	,grfregs	,1024		)   /* 340 @ SC132 */
#endif
	SYSMAP(Usriomap	,usrio		,USRIOSIZE+CLSIZE ) /* for PHYSIO */
	SYSMAP(Usrptmap	,usrpt		,USRPTSIZE+CLSIZE )
	. = . + NBPG - 1 & -NBPG	/* align to page boundry */
eSysmap:
E 5
I 5
D 8
	.set	_u,USRSTACK
E 8
I 8
	.set	_kstack,USRSTACK
I 19
	.set	_kstackatbase,USRSTACK+UPAGES*NBPG-4
	.globl	_kstackatbase
E 19
E 8
_Umap:	.long	0
D 8
	.globl	_u, _Umap
E 8
I 8
	.globl	_kstack, _Umap
E 8
E 5

D 5
/*
 * System segment table.  1 page is sufficient to map the entire
 * 4Gb address space. (funny how that works out...)
 */
	.globl	_Sysseg
_Sysseg:
	.space	NBPG
eSysseg:
E 5
I 5
#define	RELOC(var, ar)	\
	lea	var,ar;	\
	addl	a5,ar
E 5

D 5
	.globl	_Syssize, _Usrptsize
_Syssize	= eSysmap-_Sysmap/4
_Usrptsize	= eSysmap-_Usrptmap/4

E 5
/*
 * Initialization
 *
 * A5 contains physical load point from boot
 * VBR contains zero from ROM.  Exceptions will continue to vector
 * through ROM until MMU is turned on at which time they will vector
 * through our table (vectors.s).
 */
	.comm	_lowram,4

	.text
	.globl	_edata
	.globl	_etext,_end
	.globl	start
start:
	movw	#PSL_HIGHIPL,sr		| no interrupts
D 5
	lea	_lowram,a0
	addl	a5,a0
E 5
I 5
	RELOC(tmpstk, a0)
	movl	a0,sp			| give ourselves a temporary stack
	RELOC(_lowram, a0)
E 5
	movl	a5,a0@			| store start of physical memory
	movl	#CACHE_OFF,d0
	movc	d0,cacr			| clear and disable on-chip cache(s)

/* determine our CPU/MMU combo - check for all regardless of kernel config */
I 5
D 10
	movl	#IOBASE+MMUBASE,a1
E 10
I 10
	movl	#INTIOBASE+MMUBASE,a1
E 10
E 5
	movl	#0x200,d0		| data freeze bit
	movc	d0,cacr			|   only exists on 68030
	movc	cacr,d0			| read it back
	tstl	d0			| zero?
D 13
	jeq	Lis68020		| yes, we have 68020
E 13
I 13
	jeq	Lnot68030		| yes, we have 68020/68040
E 13
D 5
	lea	_mmutype,a0		| no, we have 68030
	addl	a5,a0
E 5
I 5
	RELOC(_mmutype, a0)		| no, we have 68030
E 5
	movl	#-1,a0@			| set to reflect 68030 PMMU
D 5
	lea	_machineid,a0
	addl	a5,a0
D 2
	movl	#3,a0@			| type is at least a 360
E 2
	movl	#0x80,IOBASE+MMUCMD	| set magic cookie
	movl	IOBASE+MMUCMD,d0	| read it back
E 5
I 5
	RELOC(_machineid, a0)
	movl	#0x80,a1@(MMUCMD)	| set magic cookie
	movl	a1@(MMUCMD),d0		| read it back
E 5
	btst	#7,d0			| cookie still on?
D 2
	jeq	Lstart1			| no, just a 360
E 2
I 2
	jeq	Lnot370			| no, 360 or 375
E 2
D 5
	movl	#0,IOBASE+MMUCMD	| clear magic cookie
	movl	IOBASE+MMUCMD,d0	| read it back
E 5
I 5
	movl	#0,a1@(MMUCMD)		| clear magic cookie
	movl	a1@(MMUCMD),d0		| read it back
E 5
	btst	#7,d0			| still on?
	jeq	Lisa370			| no, must be a 370
	movl	#5,a0@			| yes, must be a 340
	jra	Lstart1
I 2
Lnot370:
	movl	#3,a0@			| type is at least a 360
D 5
	movl	#0,IOBASE+MMUCMD	| clear magic cookie2
	movl	IOBASE+MMUCMD,d0	| read it back
E 5
I 5
	movl	#0,a1@(MMUCMD)		| clear magic cookie2
	movl	a1@(MMUCMD),d0		| read it back
E 5
	btst	#16,d0			| still on?
	jeq	Lstart1			| no, must be a 360
	movl	#6,a0@			| yes, must be a 345/375
	jra	Lhaspac
E 2
Lisa370:
	movl	#4,a0@			| set to 370
I 2
Lhaspac:
E 2
D 5
	lea	_ectype,a0
	addl	a5,a0
E 5
I 5
	RELOC(_ectype, a0)
E 5
	movl	#-1,a0@			| also has a physical address cache
	jra	Lstart1
I 13
Lnot68030:
	bset	#31,d0			| data cache enable bit
	movc	d0,cacr			|   only exists on 68040
	movc	cacr,d0			| read it back
	tstl	d0			| zero?
	beq	Lis68020		| yes, we have 68020
	moveq	#0,d0			| now turn it back off
	movec	d0,cacr			|   before we access any data
D 19
	RELOC(_machineid, a0)
	movl	#7,a0@			| we have a 380
E 19
	RELOC(_mmutype, a0)
	movl	#-2,a0@			| with a 68040 MMU
	RELOC(_ectype, a0)
	movl	#0,a0@			| and no cache (for now XXX)
#ifdef HPFPLIB
	RELOC(_processor, a0)
	movl	#3,a0@			| HP-UX style processor id
#endif
I 19
	RELOC(_machineid, a0)
	movl	a1@(MMUCMD),d0		| read MMU register
	lsrl	#8,d0			| get apparent ID
	cmpb	#6,d0			| id == 6?
	jeq	Lis33mhz		| yes, we have a 433s
	movl	#7,a0@			| no, we have a 380/425t
E 19
	jra	Lstart1
I 19
Lis33mhz:
	movl	#8,a0@			| 433s (XXX 425s returns same ID, ugh!)
	jra	Lstart1
E 19
E 13
Lis68020:
D 5
	movl	#1,IOBASE+MMUCMD	| a 68020, write HP MMU location
	movl	IOBASE+MMUCMD,d0	| read it back
E 5
I 5
	movl	#1,a1@(MMUCMD)		| a 68020, write HP MMU location
	movl	a1@(MMUCMD),d0		| read it back
E 5
	btst	#0,d0			| non-zero?
	jne	Lishpmmu		| yes, we have HP MMU
D 5
	lea	_mmutype,a0
	addl	a5,a0
E 5
I 5
	RELOC(_mmutype, a0)
E 5
	movl	#1,a0@			| no, we have PMMU
D 5
	lea	_machineid,a0
	addl	a5,a0
E 5
I 5
	RELOC(_machineid, a0)
E 5
	movl	#1,a0@			| and 330 CPU
	jra	Lstart1
Lishpmmu:
D 5
	lea	_ectype,a0		| 320 or 350
	addl	a5,a0
E 5
I 5
	RELOC(_ectype, a0)		| 320 or 350
E 5
	movl	#1,a0@			| both have a virtual address cache
D 5
	movl	#0x80,IOBASE+MMUCMD	| set magic cookie
	movl	IOBASE+MMUCMD,d0	| read it back
E 5
I 5
	movl	#0x80,a1@(MMUCMD)	| set magic cookie
	movl	a1@(MMUCMD),d0		| read it back
E 5
	btst	#7,d0			| cookie still on?
	jeq	Lstart1			| no, just a 320
D 5
	lea	_machineid,a0
	addl	a5,a0
E 5
I 5
	RELOC(_machineid, a0)
E 5
	movl	#2,a0@			| yes, a 350

Lstart1:
D 5
	movl	#0,IOBASE+MMUCMD	| clear out MMU again
E 5
I 5
	movl	#0,a1@(MMUCMD)		| clear out MMU again
E 5
/* initialize source/destination control registers for movs */
	moveq	#FC_USERD,d0		| user space
	movc	d0,sfc			|   as source
	movc	d0,dfc			|   and destination of transfers
I 13
/* initialize memory sizes (for pmap_bootstrap) */
	movl	#MAXADDR,d1		| last page
	moveq	#PGSHIFT,d2
	lsrl	d2,d1			| convert to page (click) number
	RELOC(_maxmem, a0)
	movl	d1,a0@			| save as maxmem
	movl	a5,d0			| lowram value from ROM via boot
	lsrl	d2,d0			| convert to page number
	subl	d0,d1			| compute amount of RAM present
	RELOC(_physmem, a0)
	movl	d1,a0@			| and physmem
/* configure kernel and proc0 VA space so we can get going */
	.globl	_Sysseg, _pmap_bootstrap, _avail_start
	movl	#_end,d5		| end of static kernel text/data
	addl	#NBPG-1,d5
	andl	#PG_FRAME,d5		| round to a page
	movl	d5,a4
	addl	a5,a4			| convert to PA
	pea	a5@			| firstpa
	pea	a4@			| nextpa
	RELOC(_pmap_bootstrap,a0)
D 14
	jbsr	a0@			| bootstrap(firstpa, nextpa)
E 14
I 14
	jbsr	a0@			| pmap_bootstrap(firstpa, nextpa)
E 14
	addql	#8,sp
E 13
D 5
/* initialize proc. 0 (system) page table */
	movl	#_Sysmap,a0		| SYSPT map addr
	addl	a5,a0			| relocate
E 5
I 5
D 14

I 13
#ifdef BOOTDEBUG
E 13
/*
I 13
 * If we are debugging the pmap_bootstrap code, we ignore what it has
 * just done (without clobbering it) and do it ourselves here with the
 * code we know works.
 */
	.globl	_Xavail_start
	RELOC(_Xavail_start,a0)
	movl	a0@,a4			| grab new first avail PA
	movl	a4,d1			| new firstpa
	movl	d5,d0
	addl	a5,d0			| old firstpa
	subl	d0,d1			| new - old == amount allocated
	addl	d1,d5			| update firstva
/*
E 13
 * Allocate kernel segment/page table resources.
 *	a5 contains the PA of lowest RAM page
 *	a4 contains the PA of first available page at any time
 *	d5 contains the VA of first available page at any time
 *	   (since we assume a zero load point, it is also the size of
 *	   allocated space at any time)
 * We assume (i.e. do not check) that the initial page table size
 * (Sysptsize) is big enough to map everything we allocate here.
 *
D 10
 * We allocate the DIO map here since the 320/350 MMU registers are
E 10
I 10
 * We allocate the IO maps here since the 320/350 MMU registers are
E 10
 * mapped in this range and it would be nice to be able to access them
 * after the MMU is turned on.
 */
	.globl	_Sysseg, _Sysmap, _Sysptmap, _Sysptsize
I 13
#if 0
E 13
	movl	#_end,d5		| end of static kernel text/data
	addl	#NBPG-1,d5
	andl	#PG_FRAME,d5		| round to a page
	movl	d5,a4
	addl	a5,a4
I 13
#endif
E 13
/* allocate kernel segment table */
	RELOC(_Sysseg, a0)
	movl	d5,a0@			| remember VA for pmap module
	movl	a4,sp@-			| remember PA for loading MMU
	addl	#NBPG,a4
	addl	#NBPG,d5
D 10
/* allocate initial page table pages (including IO map) */
E 10
I 10
/* allocate initial page table pages (including internal IO map) */
E 10
	RELOC(_Sysptsize, a0)
	movl	a0@,d0			| initial system PT size (pages)
D 10
	addl	#(IOMAPSIZE+NPTEPG-1)/NPTEPG,d0	| add pages for IO map
E 10
I 10
	addl	#(IIOMAPSIZE+EIOMAPSIZE+NPTEPG-1)/NPTEPG,d0
					| add pages for IO maps
E 10
	movl	#PGSHIFT,d1
	lsll	d1,d0			| convert to bytes
	movl	a4,sp@-			| remember PA for ST load
	addl	d0,a4
	addl	d0,d5
/* allocate kernel page table map */
	RELOC(_Sysptmap, a0)
	movl	d5,a0@			| remember VA for pmap module
	movl	a4,sp@-			| remember PA for PT map load
	addl	#NBPG,a4
	addl	#NBPG,d5
/* compute KVA of Sysptmap; mapped after page table pages */
	movl	d0,d2			| remember PT size (bytes)
	moveq	#SG_ISHIFT-PGSHIFT,d1
	lsll	d1,d0			| page table size serves as seg index
	RELOC(_Sysmap, a0)
	movl	d0,a0@			| remember VA for pmap module
/* initialize ST and PT map: PT pages + PT map */
	movl	sp@+,a1			| PT map PA
	movl	sp@+,d4			| start of PT pages
	movl	sp@+,a0			| ST phys addr
	lea	a0@(NBPG-4),a2		| (almost) end of ST
	movl	d4,d3
	orl	#SG_RW+SG_V,d4		| create proto STE for ST
	orl	#PG_RW+PG_CI+PG_V,d3	| create proto PTE for PT map
List1:
	movl	d4,a0@+
	movl	d3,a1@+
	addl	#NBPG,d4
	addl	#NBPG,d3
	cmpl	a4,d4			| sleezy, but works ok
	jcs	List1
/* initialize ST and PT map: invalidate up to last entry */
List2:
	movl	#SG_NV,a0@+
	movl	#PG_NV,a1@+
	cmpl	a2,a0
	jcs	List2
/*
 * Portions of the last segment of KVA space (0xFFF00000 - 0xFFFFFFFF)
 * are mapped for a couple of purposes. 0xFFF00000 for UPAGES is used
 * for mapping the current process u-area (u + kernel stack).  The
 * very last page (0xFFFFF000) is mapped to the last physical page of
 * RAM to give us a region in which PA == VA.  We use this page for
 * enabling/disabling mapping.
 */
	movl	a4,d1			| grab next available for PT page
	andl	#SG_FRAME,d1		| mask to frame number
	orl	#SG_RW+SG_V,d1		| RW and valid
	movl	d1,a0@+			| store in last ST entry
	movl	a0,a2			| remember addr for PT load
	andl	#PG_FRAME,d1
D 13
	orl	#PG_RW+PG_V,d1		| convert to PTE
E 13
I 13
	orl	#PG_RW+PG_CI+PG_V,d1	| convert to PTE
E 13
	movl	d1,a1@+			| store in PT map
	movl	a4,a0			| physical beginning of PT page
	lea	a0@(NBPG-4),a1		| (almost) end of page
Lispt7:
	movl	#PG_NV,a0@+		| invalidate
	cmpl	a1,a0
	jcs	Lispt7
	movl	#MAXADDR,d1		| get last phys page addr
	andl	#PG_FRAME,d1
D 13
	orl	#PG_RW+PG_V,d1
E 13
I 13
	orl	#PG_RW+PG_CI+PG_V,d1
E 13
	movl	d1,a0@+			| map to last virt page
	addl	#NBPG,a4
	addl	#NBPG,d5
/* record KVA at which to access current u-area PTEs */
	RELOC(_Sysmap, a0)
	movl	a0@,d0			| get system PT address
	addl	#NPTEPG*NBPG,d0		| end of system PT
	subl	#HIGHPAGES*4,d0		| back up to first PTE for u-area
	RELOC(_Umap, a0)
	movl	d0,a0@			| remember location
/* initialize page table pages */
	movl	a2,a0			| end of ST is start of PT
	addl	d2,a2			| add size to get end of PT
E 5
/* text pages are read-only */
	clrl	d0			| assume load at VA 0
	movl	a5,d1			| get load PA
	andl	#PG_FRAME,d1		| convert to a page frame
D 5
	orl	#PG_RO+PG_V,d1		| mark as valid and RO
E 5
I 5
#ifdef KGDB
	orl	#PG_RW+PG_V,d1		| XXX: RW for now
#else
	orl	#PG_RO+PG_V,d1		| create proto PTE
#endif
E 5
	movl	#_etext,a1		| go til end of text
D 5
Lispt1:
E 5
I 5
Lipt1:
E 5
	movl	d1,a0@+			| load PTE
	addl	#NBPG,d1		| increment page frame number
	addl	#NBPG,d0		| and address counter
	cmpl	a1,d0			| done yet?
D 5
	jcs	Lispt1			| no, keep going
/* data and bss are read/write */
E 5
I 5
	jcs	Lipt1			| no, keep going
/* data, bss and dynamic tables are read/write */
E 5
	andl	#PG_FRAME,d1		| mask out old prot bits
	orl	#PG_RW+PG_V,d1		| mark as valid and RW
D 5
	movl	#_end,a1		| go til end of data/bss
Lispt2:
E 5
I 5
	movl	d5,a1			| go til end of data allocated so far
	addl	#(UPAGES+1)*NBPG,a1	| and proc0 PT/u-area (to be allocated)
Lipt2:
E 5
	movl	d1,a0@+			| load PTE
	addl	#NBPG,d1		| increment page frame number
	addl	#NBPG,d0		| and address counter
	cmpl	a1,d0			| done yet?
D 5
	jcs	Lispt2			| no, keep going
/* invalidate remainder of system page table */
	movl	#eSysmap,a1		| end of map
	addl	a5,a1			| relocate
Lispt3:
E 5
I 5
	jcs	Lipt2			| no, keep going
/* invalidate remainder of kernel PT */
	movl	a2,a1			| end of PT
Lipt3:
E 5
	movl	#PG_NV,a0@+		| invalidate PTE
	cmpl	a1,a0			| done yet?
D 5
	jcs	Lispt3			| no, keep going
/* go back and initialize IOmap */
	movl	#_IOmap,a0		| IO map addr
	addl	a5,a0			| relocate
	movl	#_eIOmap,a1		| end of map
	addl	a5,a1			| relocate
E 5
I 5
	jcs	Lipt3			| no, keep going
D 10
/* go back and validate IO PTEs at end of allocated PT space */
E 10
I 10
/* go back and validate internal IO PTEs at end of allocated PT space */
E 10
	movl	a2,a0			| end of allocated PT space
D 10
	subl	#IOMAPSIZE*4,a0		| back up IOMAPSIZE PTEs
E 5
	movl	#IOBASE,d1		| physical IO base
E 10
I 10
	subl	#(IIOMAPSIZE+EIOMAPSIZE)*4,a0	| back up IOMAPSIZE PTEs
	subl	#EIOMAPSIZE*4,a2	| only initialize internal IO PTEs
	movl	#INTIOBASE,d1		| physical internal IO base
E 10
D 5
	andl	#PG_FRAME,d1		| mask to frame number
	orl	#PG_RW+PG_CI+PG_V,d1	| mark valid, RW and CI
Lispt4:
E 5
I 5
	orl	#PG_RW+PG_CI+PG_V,d1	| create proto PTE
Lipt4:
E 5
	movl	d1,a0@+			| load PTE
	addl	#NBPG,d1		| increment page frame number
D 5
	cmpl	a1,a0			| done yet?
	jcs	Lispt4			| no, keep going
/* initialize proc. 0 (system) segment table */
	movl	#_Sysseg,a0		| segment table
	addl	a5,a0			| relocate
	movl	#eSysmap-_Sysmap/NBPG*4,a1 | bytes of PTEs for Sysmap
	addl	a0,a1			| make an end count
	movl	#_Sysmap,d1		| system PT addr
	addl	a5,d1			| relocate
	andl	#SG_FRAME,d1		| mask to frame number
	orl	#SG_RW+SG_V,d1		| mark as RW and valid
Lispt5:
	movl	d1,a0@+			| load STE
	addl	#NBPG,d1		| increment page frame number
	cmpl	a1,a0			| done yet?
	jcs	Lispt5			| no, keep going
/* invalidate the unused part */
	movl	#eSysseg,a1		| end of segment table
	addl	a5,a1			| relocate
Lispt6:
	movl	#SG_NV,a0@+		| invalidate STE
	cmpl	a1,a0			| done yet?
	jcs	Lispt6			| no, keep going
E 5
I 5
	cmpl	a2,a0			| done yet?
	jcs	Lipt4			| no, keep going
D 10
/* record base KVA of IO space which is just before Sysmap */
E 10
I 10
/* record base KVA of IO spaces which are just before Sysmap */
E 10
	RELOC(_Sysmap, a0)
	movl	a0@,d0			| Sysmap VA
D 10
	subl	#IOMAPSIZE*NBPG,d0	| Back up size of IO space
	RELOC(_DIObase, a0)
	movl	d0,a0@
E 10
I 10
	subl	#EIOMAPSIZE*NBPG,d0	| back up size of external IO space
	RELOC(_extiobase, a0)
	movl	d0,a0@			| and record
	RELOC(_intiolimit, a0)
	movl	d0,a0@			| external base is also internal limit
	subl	#IIOMAPSIZE*NBPG,d0	| back up size of internal IO space
	RELOC(_intiobase, a0)
	movl	d0,a0@			| and record
E 10
/* also record base of clock and MMU registers for fast access */
	addl	#CLKBASE,d0
	RELOC(_CLKbase, a0)
	movl	d0,a0@
	subl	#CLKBASE,d0
	addl	#MMUBASE,d0
	RELOC(_MMUbase, a0)
	movl	d0,a0@
E 5

/*
 * Setup page table for process 0.
 *
D 13
 * We set up page table access for the kernel via Usrptmap (usrpt)
D 5
 * and access to the u-area itself via Umap (u).  First page beyond
 * kernel BSS (d0) is used for proc0 page table.  Next UPAGES pages
 * following are for u-area.
E 5
I 5
 * and access to the u-area itself via Umap (u).  First available
 * page (VA: d5, PA: a4) is used for proc0 page table.  Next UPAGES
 * pages following are for u-area.
E 13
I 13
 * We set up page table access for the kernel via Umap and access to
 * the u-area itself via `u'.  First available UPAGES pages (start at
 * VA: d5, PA: a4) are used for the u-area.
E 13
E 5
 */
D 5
	addl	a5,d0			| relocate PT address
E 5
I 5
	movl	a4,d0
E 5
D 13
	movl	d0,d1
	andl	#PG_FRAME,d1		| mask to page frame number
	orl	#PG_RW+PG_V,d1		| RW and valid
D 5
	movl	#_Usrptmap,a1		| get PT map address
	addl	a5,a1			| relocate
	movl	d1,a1@			| validate PTE for proc0 PT
E 5
I 5
	movl	d1,d4			| remember for later Usrptmap load
E 5
	movl	d0,a0			| base of proc0 PT
D 5
	addl	#NBPG,d0		| plus one page yields
	movl	d0,a2			| base of u-area
E 5
I 5
	addl	#NBPG,d0		| plus one page yields base of u-area
	movl	d0,a2			|   and end of PT
	addl	#NBPG,d5		| keep VA in sync
E 5
/* invalidate entire page table */
Liudot1:
	movl	#PG_NV,a0@+		| invalidate PTE
	cmpl	a2,a0			| done yet?
	jcs	Liudot1			| no, keep going
D 5
/* now go back and validate u-area PTEs */
	subl	#HIGHPAGES*4,a0		| base of PTEs for u-area (p_addr)
	movl	a0,a1
	addl	#UPAGES*4,a1		| end of PTEs for u-area
E 5
I 5
/* now go back and validate u-area PTEs in PT and in Umap */
	lea	a0@(-HIGHPAGES*4),a0	| base of PTEs for u-area (p_addr)
E 13
I 13
	movl	a4,a2
	lea	a4@(-HIGHPAGES*4),a0	| u-area PTE base in Umap PT
E 13
	lea	a0@(UPAGES*4),a1	| end of PTEs for u-area
D 13
	lea	a4@(-HIGHPAGES*4),a3	| u-area PTE base in Umap PT
E 13
E 5
	movl	d0,d1			| get base of u-area
	andl	#PG_FRAME,d1		| mask to page frame number
	orl	#PG_RW+PG_V,d1		| add valid and writable
D 5
	movl	#_Umap,a3		| address of u
	addl	a5,a3			| relocate
E 5
Liudot2:
	movl	d1,a0@+			| validate p_addr PTE
D 13
	movl	d1,a3@+			| validate u PTE
E 13
	addl	#NBPG,d1		| to next page
	cmpl	a1,a0			| done yet?
	jcs	Liudot2			| no, keep going
/* clear process 0 u-area */
	addl	#NBPG*UPAGES,d0		| end of u-area
Lclru1:
	clrl	a2@+			| clear
	cmpl	d0,a2			| done yet?
	jcs	Lclru1			| no, keep going
D 5
	movl	a2,a4			| save addr of first avail page
E 5
I 5
	movl	a2,a4			| save phys addr of first avail page
	RELOC(_proc0paddr, a0)
	movl	d5,a0@			| save KVA of proc0 u-area
D 7
	addl	#UPAGES*NBPG,d5		| and virtual addr as well
E 7
I 7
	addl	#UPAGES*NBPG,d5		| increment virtual addr as well
I 13
#endif
E 14
E 13
E 7
E 5

/*
 * Prepare to enable MMU.
 * Since the kernel is not mapped logical == physical we must insure
 * that when the MMU is turned on, all prefetched addresses (including
D 5
 * the PC) are valid.  In order guarentee that, we map the last page of
 * memory logical == physical and load up that page with enough code to
 * defeat the prefetch, then we execute the jump back to here.
E 5
I 5
 * the PC) are valid.  In order guarentee that, we use the last physical
 * page (which is conveniently mapped == VA) and load it up with enough
 * code to defeat the prefetch, then we execute the jump back to here.
E 5
 *
 * Is this all really necessary, or am I paranoid??
 */
D 5
	movl	#_Sysseg,d1		| system segment table addr
	addl	a5,d1			| relocate
	lea	_mmutype,a0
	addl	a5,a0
E 5
I 5
	RELOC(_Sysseg, a0)		| system segment table addr
D 13
	movl	a0@,a1			| read value (a KVA)
	addl	a5,a1			| convert to PA
E 13
I 13
	movl	a0@,d1			| read value (a KVA)
	addl	a5,d1			| convert to PA
E 13
	RELOC(_mmutype, a0)
E 5
	tstl	a0@			| HP MMU?
	jeq	Lhpmmu2			| yes, skip
I 13
	cmpl	#-2,a0@			| 68040?
	jne	Lmotommu1		| no, skip
	.long	0x4e7b1807		| movc d1,srp
	jra	Lstploaddone
Lmotommu1:
E 13
D 5
	lea	_protorp,a0
	addl	a5,a0
E 5
I 5
	RELOC(_protorp, a0)
E 5
	movl	#0x80000202,a0@		| nolimit + share global + 4 byte PTEs
D 5
	movl	d1,a0@(4)		| + segtable address
	.long	0xf0104800		| pmove a0@,srp
E 5
I 5
D 13
	movl	a1,a0@(4)		| + segtable address
E 13
I 13
	movl	d1,a0@(4)		| + segtable address
E 13
	pmove	a0@,srp			| load the supervisor root pointer
E 5
	movl	#0x80000002,a0@		| reinit upper half for CRP loads
	jra	Lstploaddone		| done
Lhpmmu2:
I 5
D 13
	movl	a1,d1
E 13
E 5
	moveq	#PGSHIFT,d2
	lsrl	d2,d1			| convert to page frame
D 5
	movl	d1,IOBASE+MMUSSTP	| load in sysseg table register
E 5
I 5
D 10
	movl	d1,IOBASE+MMUBASE+MMUSSTP | load in sysseg table register
E 10
I 10
	movl	d1,INTIOBASE+MMUBASE+MMUSSTP | load in sysseg table register
E 10
E 5
Lstploaddone:
D 5
	movl	#eSysseg-4,a1		| last entry in sysseg table
	addl	a5,a1			| relocate
	movl	d0,d1			| use page after proc0 u for tmp PT
	andl	#SG_FRAME,d1		| mask to page frame
	orl	#SG_RW+SG_V,d1		| mark valid and writable
	movl	d1,a1@			| load in segment table
	movl	d0,a1			| page table address
	addl	#NBPG-4,a1		| move to last entry
	movl	#MAXADDR,d1		| address of last page of memory
	movl	d1,a2
	andl	#PG_FRAME,d1		| mask to page frame
	orl	#PG_RW+PG_V,d1		| mark valid and writable
	movl	d1,a1@			| store PTE in table
	movl	#Lhighcode,a1		| addr of high code
	addl	a5,a1			| relocate
	movl	#Lehighcode,a3		| end addr
	addl	a5,a3			| relocate
E 5
I 5
	lea	MAXADDR,a2		| PA of last RAM page
	RELOC(Lhighcode, a1)		| addr of high code
	RELOC(Lehighcode, a3)		| end addr
E 5
Lcodecopy:
	movw	a1@+,a2@+		| copy a word
	cmpl	a3,a1			| done yet?
	jcs	Lcodecopy		| no, keep going
	jmp	MAXADDR			| go for it!

Lhighcode:
D 5
	lea	_mmutype,a0
	addl	a5,a0
	tstl	a0@				| HP MMU?
	jeq	Lhpmmu3				| yes, skip
	movl	#MMU_IEN+MMU_FPE,IOBASE+MMUCMD	| enable 68881 and i-cache
E 5
I 5
	RELOC(_mmutype, a0)
	tstl	a0@			| HP MMU?
	jeq	Lhpmmu3			| yes, skip
I 13
	cmpl	#-2,a0@			| 68040?
	jne	Lmotommu2		| no, skip
	movw	#0,INTIOBASE+MMUBASE+MMUCMD+2
	movw	#MMU_IEN+MMU_CEN+MMU_FPE,INTIOBASE+MMUBASE+MMUCMD+2
					| enable FPU and caches
	moveq	#0,d0			| ensure TT regs are disabled
	.long	0x4e7b0004		| movc d0,itt0
	.long	0x4e7b0005		| movc d0,itt1
	.long	0x4e7b0006		| movc d0,dtt0
	.long	0x4e7b0007		| movc d0,dtt1
	.word	0xf4d8			| cinva bc
	.word	0xf518			| pflusha
	movl	#0x8000,d0
	.long	0x4e7b0003		| movc d0,tc
	movl	#0x80008000,d0
	movc	d0,cacr			| turn on both caches
	jmp	Lenab1
Lmotommu2:
E 13
D 10
	movl	#MMU_IEN+MMU_FPE,IOBASE+MMUBASE+MMUCMD | enable 68881 and i-cache
E 5
	movl	#0x82c0aa00,a2@			| value to load TC with
D 5
	.long	0xf0124000			| pmove a2@,tc
E 5
I 5
	pmove	a2@,tc				| load it
E 10
I 10
	movl	#MMU_IEN+MMU_FPE,INTIOBASE+MMUBASE+MMUCMD
					| enable 68881 and i-cache
	movl	#0x82c0aa00,a2@		| value to load TC with
	pmove	a2@,tc			| load it
E 10
E 5
	jmp	Lenab1
Lhpmmu3:
D 5
	movl	#0,IOBASE+MMUCMD		| clear external cache
	movl	#MMU_ENAB,IOBASE+MMUCMD		| turn on MMU
E 5
I 5
D 10
	movl	#0,IOBASE+MMUBASE+MMUCMD	| clear external cache
	movl	#MMU_ENAB,IOBASE+MMUBASE+MMUCMD	| turn on MMU
E 10
I 10
	movl	#0,INTIOBASE+MMUBASE+MMUCMD	| clear external cache
	movl	#MMU_ENAB,INTIOBASE+MMUBASE+MMUCMD | turn on MMU
E 10
E 5
	jmp	Lenab1				| jmp to mapped code
Lehighcode:

/*
 * Should be running mapped from this point on
 */
Lenab1:
I 2
D 5
/* while the ROM scratch page is mapped, check for internal HP-IB in SYSFLAG */
E 5
I 5
/* check for internal HP-IB in SYSFLAG */
E 5
	btst	#5,0xfffffed2		| internal HP-IB?
D 5
	jeq	Linitmem		| yes, have HP-IB continue normally
	clrl	_internalhpib		| no, clear associated address
E 5
I 5
D 13
	jeq	Linitmem		| yes, have HP-IB just continue
E 13
I 13
	jeq	Lfinish			| yes, have HP-IB just continue
E 13
D 10
	clrl	_internalhpib		| no, clear flag
E 10
I 10
	clrl	_internalhpib		| no, clear associated address
E 10
E 5
E 2
D 13
/* init mem sizes */
I 2
Linitmem:
E 2
	movl	#MAXADDR,d1		| last page
	moveq	#PGSHIFT,d2
	lsrl	d2,d1			| convert to page (click) number
	movl	d1,_maxmem		| save as maxmem
	movl	_lowram,d0		| lowram value from ROM via boot
	lsrl	d2,d0			| convert to page number
	subl	d0,d1			| compute amount of RAM present
D 5
	movl	d1,_freemem		| save as freemem
E 5
	movl	d1,_physmem		| and physmem
I 5
/*
I 12
 * First we have to select the software page size, then set up the pmap.
E 12
 * pmap_bootstrap is supposed to be called with mapping off early on
 * to set up the kernel VA space.  However, this only works easily if
 * you have a kernel PA == VA mapping.  Since we do not, we just set
 * up and enable mapping here and then call the bootstrap routine to
 * get the pmap module in sync with reality.
 */
	.globl	_avail_start
E 13
I 13
Lfinish:
/* select the software page size now */
E 13
	lea	tmpstk,sp		| temporary stack
I 12
	jbsr	_vm_set_page_size	| select software page size
I 13
D 19
#ifdef BOOTDEBUG
E 13
E 12
	movl	a5,sp@-			| phys load address (assumes VA 0)
	movl	a4,sp@-			| first available PA
D 13
	jbsr	_pmap_bootstrap		| sync up pmap module
E 13
I 13
	jbsr	_Opmap_bootstrap	| sync up pmap module
E 13
	addql	#8,sp
D 13
|	movl	_avail_start,a4		| pmap_bootstrap may need RAM
E 13
I 13
#endif
E 19
E 13
E 5
D 7
/* initialize (slightly) the pcb */
E 7
I 7
/* set kernel stack, user SP, and initial pcb */
E 7
D 5
	movl	#_u,a1			| proc0 u-area
	movl	a1,sp
	addl	#UPAGES*NBPG-4,sp	| set kernel stack to end of u-area
E 5
I 5
D 8
	lea	_u,a1			| proc0 u-area
	lea	a1@(UPAGES*NBPG-4),sp	| set kernel stack to end of u-area
E 8
I 8
	lea	_kstack,a1		| proc0 kernel stack
	lea	a1@(UPAGES*NBPG-4),sp	| set kernel stack to end of area
E 8
E 5
	movl	#USRSTACK-4,a2
	movl	a2,usp			| init user SP
I 8
	movl	_proc0paddr,a1		| get proc0 pcb addr
D 10
	movl	a1,_masterpaddr		| proc0 is running
E 10
I 10
	movl	a1,_curpcb		| proc0 is running
E 10
E 8
D 5
	movl	#_usrpt,a1@(PCB_P0BR)	| p0br: SVA of text/data user PT
	clrl	a1@(PCB_P0LR)		| p0lr: 0 (does not really exist)
	movl	#_usrpt+NBPG,d0		| addr of end of PT
	subl	#P1PAGES*4,d0		| backup size of P1 region
	movl	d0,a1@(PCB_P1BR)	| p1br: P1PAGES from end of PT
	movl	#P1PAGES-HIGHPAGES,a1@(PCB_P1LR)	| p1lr: vax style
	movl	#CLSIZE,a1@(PCB_SZPT)	| page table size
E 5
D 19
	clrw	a1@(PCB_FLAGS)		| clear flags
E 19
#ifdef FPCOPROC
	clrl	a1@(PCB_FPCTX)		| ensure null FP context
	movl	a1,sp@-
	jbsr	_m68881_restore		| restore it (does not kill a1)
	addql	#4,sp
#endif
D 8
	addl	#PCB_SIGC,a1		| address of proc0 sig trampoline code
	movl	#Lsigcode,a2		| address of sig trampoline proto
Lsigc:
	movw	a2@+,a1@+		| copy
	cmpl	#Lesigcode,a2		| done yet?
	jcs	Lsigc			| no, keep going
E 8
/* flush TLB and turn on caches */
D 5
	movl	#PG_NV,eSysseg-4	| invalidate last page
E 5
	jbsr	_TBIA			| invalidate TLB
I 13
	cmpl	#-2,_mmutype		| 68040?
	jeq	Lnocache0		| yes, cache already on
E 13
	movl	#CACHE_ON,d0
	movc	d0,cacr			| clear cache(s)
	tstl	_ectype
	jeq	Lnocache0
D 5
	orl	#MMU_CEN,_IObase+MMUCMD	| turn on external cache
E 5
I 5
	MMUADDR(a0)
	orl	#MMU_CEN,a0@(MMUCMD)	| turn on external cache
E 5
Lnocache0:
/* final setup for C code */
I 19
	jbsr	_isrinit		| be ready for stray ints
E 19
	movw	#PSL_LOWIPL,sr		| lower SPL
	movl	d7,_boothowto		| save reboot flags
	movl	d6,_bootdev		|   and boot device
D 11
	movl	a4,d1			| addr of first available RAM
	moveq	#PGSHIFT,d2
	lsrl	d2,d1			| convert to click
	movl	d1,sp@-			| param to main
	jbsr	_main			| main(firstaddr)
	addql	#4,sp
E 11
I 11
D 29
	jbsr	_main			| call main()

E 11
/* proc[1] == init now running here;
 * create a null exception frame and return to user mode in icode
E 29
I 29
/*
 * Create a fake exception frame that returns to user mode,
 * make space for the rest of a fake saved register set, and
 * pass the first available RAM and a pointer to the register
 * set to "main()".  "main()" will call "icode()", which fakes
 * an "execve()" system call, which is why we need to do that
 * ("main()" sets "u.u_ar0" to point to the register set).
 * When "main()" returns, we're running in process 1 and have
 * successfully faked the "execve()".  We load up the registers from
 * that set; the "rte" loads the PC and PSR, which jumps to "init".
E 29
 */
I 29
  	clrw	sp@-			| vector offset/frame type
	clrl	sp@-			| PC - filled in by "execve"
  	movw	#PSL_USER,sp@-		| in user mode
D 32
	clrw	sp@-			| pad SR to longword
E 32
I 32
	clrl	sp@-			| pad word
E 32
	lea	sp@(-64),sp		| construct space for D0-D7/A0-A7
	pea	sp@			| addr of space for D0
	jbsr	_main			| main(firstaddr, r0)
	addql	#4,sp			| pop args
E 29
I 13
	cmpl	#-2,_mmutype		| 68040?
	jne	Lnoflush		| no, skip
	.word	0xf478			| cpusha dc
	.word	0xf498			| cinva ic
Lnoflush:
E 13
D 29
	clrw	sp@-			| vector offset/frame type
	clrl	sp@-			| return to icode location 0
	movw	#PSL_USER,sp@-		| in user mode
	rte
E 29
I 29
	movl	sp@(60),a0		| grab and load
	movl	a0,usp			|   user SP
	moveml	sp@+,#0x7FFF		| load most registers (all but SSP)
D 32
	addql	#6,sp			| pop SSP and align word
E 32
I 32
	addql	#8,sp			| pop SSP and pad word
E 32
  	rte
E 29

/*
 * Signal "trampoline" code (18 bytes).  Invoked from RTE setup by sendsig().
 * 
 * Stack looks like:
 *
 *	sp+0 ->	signal number
 *	sp+4	signal specific code
 *	sp+8	pointer to signal context frame (scp)
 *	sp+12	address of handler
 *	sp+16	saved hardware state
 *			.
 *			.
 *	scp+0->	beginning of signal context frame
 */
D 8
Lsigcode:
E 8
I 8
D 17
	.globl	_sigcode, _esigcode
E 17
I 17
	.globl	_sigcode, _esigcode, _sigcodetrap
E 17
	.data
_sigcode:
E 8
	movl	sp@(12),a0		| signal handler addr	(4 bytes)
	jsr	a0@			| call signal handler	(2 bytes)
	addql	#4,sp			| pop signo		(2 bytes)
I 17
_sigcodetrap:
E 17
	trap	#1			| special syscall entry	(2 bytes)
	movl	d0,sp@(4)		| save errno		(4 bytes)
	moveq	#1,d0			| syscall == exit	(2 bytes)
	trap	#0			| exit(errno)		(2 bytes)
I 10
	.align	2
E 10
D 8
Lesigcode:
E 8
I 8
_esigcode:
E 8
D 29

/*
 * Icode is copied out to process 1 to exec init.
 * If the exec fails, process 1 exits.
 */
D 5
	argv1 = argv-_icode
	init1 = init-_icode
E 5
D 7
	.globl	_icode,_initflags,_szicode
I 6
	.data
E 7
I 7
	.globl	_icode,_szicode
	.text
E 7
E 6
_icode:
D 5
	movl	#argv1,sp@-
	movl	#init1,sp@-
E 5
I 5
D 7
	pea	pc@(argv-.-2)
	pea	pc@(init-.-2)
E 7
E 5
	clrl	sp@-
D 7
	moveq	#SYS_execv,d0
E 7
I 7
	pea	pc@((argv-.)+2)
	pea	pc@((init-.)+2)
	clrl	sp@-
	moveq	#SYS_execve,d0
E 7
	trap	#0
	moveq	#SYS_exit,d0
	trap	#0
D 5

E 5
init:
D 2
#ifdef COMPAT_UTAH
	.asciz	"/etc/init"
#else
E 2
	.asciz	"/sbin/init"
D 2
#endif
E 2
	.even
D 7
_initflags:
	.long	0
E 7
argv:
D 2
#ifdef COMPAT_UTAH
	.long	init+5-_icode
#else
E 2
D 7
	.long	init+6-_icode
D 2
#endif
E 2
	.long	_initflags-_icode
E 7
I 7
	.long	init+6-_icode		| argv[0] = "init" ("/sbin/init" + 6)
	.long	eicode-_icode		| argv[1] follows icode after copyout
E 7
	.long	0
I 7
eicode:

E 7
_szicode:
	.long	_szicode-_icode
E 29
I 6
D 7
	.text
E 7
E 6

/*
 * Primitives
 */ 

I 23
#ifdef __STDC__
D 31
#define EXPORT(name)	.globl _ ## name; _ ## name:
E 31
I 31
#define EXPORT(name)		.globl _ ## name; _ ## name:
E 31
#else
D 31
#define EXPORT(name)	.globl _/**/name; _/**/name:
E 31
I 31
#define EXPORT(name)		.globl _/**/name; _/**/name:
E 31
#endif
E 23
#ifdef GPROF
I 24
#if __GNUC__ >= 2
E 24
D 10
#ifdef __GNUC__
E 10
D 31
#define	ENTRY(name) \
D 23
	.globl _/**/name; _/**/name: link a6,#0; jbsr mcount; unlk a6
E 23
I 23
	EXPORT(name) link a6,\#0; jbsr mcount; unlk a6
E 31
I 31
#define	ENTRY(name)		EXPORT(name) link a6,\#0; jbsr mcount; unlk a6
E 31
I 24
#else
D 31
#define	ENTRY(name) \
	EXPORT(name) link a6,#0; jbsr mcount; unlk a6
E 31
I 31
#define	ENTRY(name)		EXPORT(name) link a6,#0; jbsr mcount; unlk a6
E 31
#endif
E 24
E 23
D 31
#define ALTENTRY(name, rname) \
	ENTRY(name); jra rname+12
E 31
I 31
#define ALTENTRY(name, rname)	ENTRY(name); jra rname+12
E 31
#else
D 31
#define	ENTRY(name) \
D 10
	.globl _/**/name; _/**/name: jbsr mcount
#define ALTENTRY(name, rname) \
	ENTRY(name); jra rname+6
#endif
#else
#define	ENTRY(name) \
E 10
D 23
	.globl _/**/name; _/**/name:
E 23
I 23
	EXPORT(name)
E 23
#define ALTENTRY(name, rname) \
D 23
	.globl _/**/name; _/**/name:
E 23
I 23
	ENTRY(name)
E 31
I 31
#define	ENTRY(name)		EXPORT(name)
#define ALTENTRY(name, rname) 	ENTRY(name)
E 31
E 23
#endif

/*
I 19
 * For gcc2
 */
ENTRY(__main)
	rts

/*
I 31
 * copypage(fromaddr, toaddr)
 *
 * Optimized version of bcopy for a single page-aligned NBPG byte copy.
 */
ENTRY(copypage)
	movl	sp@(4),a0		| source address
	movl	sp@(8),a1		| destination address
	movl	#NBPG/32,d0		| number of 32 byte chunks
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lmlloop			| no, use movl
Lm16loop:
	.long	0xf6209000		| move16 a0@+,a1@+
	.long	0xf6209000		| move16 a0@+,a1@+
	subql	#1,d0
	jne	Lm16loop
	rts
#endif
Lmlloop:
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	movl	a0@+,a1@+
	subql	#1,d0
	jne	Lmlloop
	rts

/*
E 31
E 19
D 16
 * update profiling information for the user
 * addupc(pc, &u.u_prof, ticks)
 */
ENTRY(addupc)
	movl	a2,sp@-			| scratch register
	movl	sp@(12),a2		| get &u.u_prof
	movl	sp@(8),d0		| get user pc
	subl	a2@(8),d0		| pc -= pr->pr_off
	jlt	Lauexit			| less than 0, skip it
	movl	a2@(12),d1		| get pr->pr_scale
	lsrl	#1,d0			| pc /= 2
	lsrl	#1,d1			| scale /= 2
	mulul	d1,d0			| pc /= scale
	moveq	#14,d1
	lsrl	d1,d0			| pc >>= 14
	bclr	#0,d0			| pc &= ~1
	cmpl	a2@(4),d0		| too big for buffer?
	jge	Lauexit			| yes, screw it
	addl	a2@,d0			| no, add base
	movl	d0,sp@-			| push address
	jbsr	_fusword		| grab old value
	movl	sp@+,a0			| grab address back
	cmpl	#-1,d0			| access ok
	jeq	Lauerror		| no, skip out
	addw	sp@(18),d0		| add tick to current value
	movl	d0,sp@-			| push value
	movl	a0,sp@-			| push address
	jbsr	_susword		| write back new value
	addql	#8,sp			| pop params
	tstl	d0			| fault?
	jeq	Lauexit			| no, all done
Lauerror:
	clrl	a2@(12)			| clear scale (turn off prof)
Lauexit:
	movl	sp@+,a2			| restore scratch reg
	rts

/*
E 16
 * copyinstr(fromaddr, toaddr, maxlength, &lencopied)
 *
 * Copy a null terminated string from the user address space into
 * the kernel address space.
D 31
 * NOTE: maxlength must be < 64K
E 31
I 31
 *
 * NOTE: maxlength must be < 64K (due to use of DBcc)
E 31
 */
ENTRY(copyinstr)
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	movl	#Lcisflt1,a0@(PCB_ONFAULT) | set up to catch faults
E 8
	movl	sp@(4),a0		| a0 = fromaddr
	movl	sp@(8),a1		| a1 = toaddr
	moveq	#0,d0
	movw	sp@(14),d0		| d0 = maxlength
	jlt	Lcisflt1		| negative count, error
	jeq	Lcisdone		| zero count, all done
D 8
	movl	#Lcisflt1,_u+PCB_ONFAULT | set up to catch faults
E 8
	subql	#1,d0			| set up for dbeq
Lcisloop:
	movsb	a0@+,d1			| grab a byte
I 13
	nop
E 13
	movb	d1,a1@+			| copy it
	dbeq	d0,Lcisloop		| if !null and more, continue
	jne	Lcisflt2		| ran out of room, error
	moveq	#0,d0			| got a null, all done
Lcisdone:
	tstl	sp@(16)			| return length desired?
	jeq	Lcisret			| no, just return
	subl	sp@(4),a0		| determine how much was copied
	movl	sp@(16),a1		| return location
	movl	a0,a1@			| stash it
Lcisret:
D 8
	clrl	_u+PCB_ONFAULT		| clear fault addr
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	clrl	a0@(PCB_ONFAULT) 	| clear fault addr
E 8
	rts
Lcisflt1:
	moveq	#EFAULT,d0		| copy fault
	jra	Lcisdone
Lcisflt2:
D 4
	moveq	#ENOENT,d0		| ran out of space
E 4
I 4
	moveq	#ENAMETOOLONG,d0	| ran out of space
E 4
	jra	Lcisdone	

/*
 * copyoutstr(fromaddr, toaddr, maxlength, &lencopied)
 *
 * Copy a null terminated string from the kernel
 * address space to the user address space.
D 31
 * NOTE: maxlength must be < 64K
E 31
I 31
 *
 * NOTE: maxlength must be < 64K (due to use of DBcc)
E 31
 */
ENTRY(copyoutstr)
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	movl	#Lcosflt1,a0@(PCB_ONFAULT) | set up to catch faults
E 8
	movl	sp@(4),a0		| a0 = fromaddr
	movl	sp@(8),a1		| a1 = toaddr
	moveq	#0,d0
	movw	sp@(14),d0		| d0 = maxlength
	jlt	Lcosflt1		| negative count, error
	jeq	Lcosdone		| zero count, all done
D 8
	movl	#Lcosflt1,_u+PCB_ONFAULT| set up to catch faults
E 8
	subql	#1,d0			| set up for dbeq
Lcosloop:
	movb	a0@+,d1			| grab a byte
	movsb	d1,a1@+			| copy it
I 13
	nop
E 13
	dbeq	d0,Lcosloop		| if !null and more, continue
	jne	Lcosflt2		| ran out of room, error
	moveq	#0,d0			| got a null, all done
Lcosdone:
	tstl	sp@(16)			| return length desired?
	jeq	Lcosret			| no, just return
	subl	sp@(4),a0		| determine how much was copied
	movl	sp@(16),a1		| return location
	movl	a0,a1@			| stash it
Lcosret:
D 8
	clrl	_u+PCB_ONFAULT		| clear fault addr
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	clrl	a0@(PCB_ONFAULT) 	| clear fault addr
E 8
	rts
Lcosflt1:
	moveq	#EFAULT,d0		| copy fault
	jra	Lcosdone
Lcosflt2:
D 4
	moveq	#ENOENT,d0		| ran out of space
E 4
I 4
	moveq	#ENAMETOOLONG,d0	| ran out of space
E 4
	jra	Lcosdone	

/*
 * copystr(fromaddr, toaddr, maxlength, &lencopied)
 *
 * Copy a null terminated string from one point to another in
 * the kernel address space.
D 31
 * NOTE: maxlength must be < 64K
E 31
I 31
 *
 * NOTE: maxlength must be < 64K (due to use of DBcc)
E 31
 */
ENTRY(copystr)
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
	movl	#Lcsflt1,a0@(PCB_ONFAULT) | set up to catch faults
E 10
E 8
	movl	sp@(4),a0		| a0 = fromaddr
	movl	sp@(8),a1		| a1 = toaddr
	moveq	#0,d0
	movw	sp@(14),d0		| d0 = maxlength
	jlt	Lcsflt1			| negative count, error
	jeq	Lcsdone			| zero count, all done
D 8
	movl	#Lcsflt1,_u+PCB_ONFAULT	| set up to catch faults
E 8
	subql	#1,d0			| set up for dbeq
Lcsloop:
	movb	a0@+,a1@+		| copy a byte
	dbeq	d0,Lcsloop		| if !null and more, continue
	jne	Lcsflt2			| ran out of room, error
	moveq	#0,d0			| got a null, all done
Lcsdone:
	tstl	sp@(16)			| return length desired?
	jeq	Lcsret			| no, just return
	subl	sp@(4),a0		| determine how much was copied
	movl	sp@(16),a1		| return location
	movl	a0,a1@			| stash it
Lcsret:
D 8
	clrl	_u+PCB_ONFAULT		| clear fault addr
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
	clrl	a0@(PCB_ONFAULT) 	| clear fault addr
E 10
E 8
	rts
Lcsflt1:
	moveq	#EFAULT,d0		| copy fault
	jra	Lcsdone
Lcsflt2:
D 4
	moveq	#ENOENT,d0		| ran out of space
E 4
I 4
	moveq	#ENAMETOOLONG,d0	| ran out of space
E 4
	jra	Lcsdone	

/* 
D 19
 * Copyin(from, to, len)
E 19
I 19
 * Copyin(from_user, to_kernel, len)
 * Copyout(from_kernel, to_user, len)
E 19
 *
D 19
 * Copy specified amount of data from user space into the kernel.
 * NOTE: len must be < 64K
E 19
I 19
 * Copy specified amount of data between kernel and user space.
 *
 * XXX both use the DBcc instruction which has 16-bit limitation so only
 * 64k units can be copied, where "unit" is either a byte or a longword
 * depending on alignment.  To be safe, assume it can copy at most
 * 64k bytes.  Don't make MAXBSIZE or MAXPHYS larger than 64k without
 * fixing this code!
E 19
 */
ENTRY(copyin)
I 31
	movl	sp@(12),d0		| get size
#ifdef MAPPEDCOPY
	.globl	_mappedcopysize,_mappedcopyin
	cmpl	_mappedcopysize,d0	| size >= mappedcopysize
	jcc	_mappedcopyin		| yes, go do it the new way
#endif
E 31
	movl	d2,sp@-			| scratch register
D 8
	movl	#Lciflt,_u+PCB_ONFAULT	| catch faults
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	movl	#Lciflt,a0@(PCB_ONFAULT) | set up to catch faults
E 8
D 31
	movl	sp@(16),d2		| check count
E 31
I 31
	tstl	d0			| check count
E 31
	jlt	Lciflt			| negative, error
	jeq	Lcidone			| zero, done
	movl	sp@(8),a0		| src address
	movl	sp@(12),a1		| dest address
D 31
	movl	a0,d0
	btst	#0,d0			| src address odd?
E 31
I 31
	movl	a0,d2
	btst	#0,d2			| src address odd?
E 31
	jeq	Lcieven			| no, go check dest
	movsb	a0@+,d1			| yes, get a byte
I 13
	nop
E 13
	movb	d1,a1@+			| put a byte
D 31
	subql	#1,d2			| adjust count
E 31
I 31
	subql	#1,d0			| adjust count
E 31
	jeq	Lcidone			| exit if done
Lcieven:
D 31
	movl	a1,d0
	btst	#0,d0			| dest address odd?
E 31
I 31
	movl	a1,d2
	btst	#0,d2			| dest address odd?
E 31
D 25
	jne	Lcibyte			| yes, must copy by bytes
E 25
I 25
	jne	Lcibloop		| yes, must copy by bytes
E 25
D 31
	movl	d2,d0			| no, get count
	lsrl	#2,d0			| convert to longwords
E 31
I 31
	movl	d0,d2			| no, get count
	lsrl	#2,d2			| convert to longwords
E 31
D 25
	jeq	Lcibyte			| no longwords, copy bytes
	subql	#1,d0			| set up for dbf
E 25
I 25
	jeq	Lcibloop		| no longwords, copy bytes
E 25
Lcilloop:
	movsl	a0@+,d1			| get a long
I 13
	nop
E 13
	movl	d1,a1@+			| put a long
D 25
	dbf	d0,Lcilloop		| til done
E 25
I 25
D 31
	subql	#1,d0
E 31
I 31
	subql	#1,d2
E 31
	jne	Lcilloop		| til done
E 25
D 31
	andl	#3,d2			| what remains
E 31
I 31
	andl	#3,d0			| what remains
E 31
	jeq	Lcidone			| all done
D 25
Lcibyte:
	subql	#1,d2			| set up for dbf
E 25
Lcibloop:
	movsb	a0@+,d1			| get a byte
I 13
	nop
E 13
	movb	d1,a1@+			| put a byte
D 25
	dbf	d2,Lcibloop		| til done
E 25
I 25
D 31
	subql	#1,d2
E 31
I 31
	subql	#1,d0
E 31
	jne	Lcibloop		| til done
E 25
Lcidone:
D 31
	moveq	#0,d0			| success
Lciexit:
E 31
D 8
	clrl	_u+PCB_ONFAULT		| reset fault catcher
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	clrl	a0@(PCB_ONFAULT) 	| clear fault catcher
E 8
	movl	sp@+,d2			| restore scratch reg
	rts
Lciflt:
	moveq	#EFAULT,d0		| got a fault
D 31
	jra	Lciexit
E 31
I 31
	jra	Lcidone
E 31

D 19
/* 
 * Copyout(from, to, len)
 *
 * Copy specified amount of data from kernel to the user space
 * NOTE: len must be < 64K
 */
E 19
ENTRY(copyout)
I 31
	movl	sp@(12),d0		| get size
#ifdef MAPPEDCOPY
	.globl	_mappedcopysize,_mappedcopyout
	cmpl	_mappedcopysize,d0	| size >= mappedcopysize
	jcc	_mappedcopyout		| yes, go do it the new way
#endif
E 31
	movl	d2,sp@-			| scratch register
D 8
	movl	#Lcoflt,_u+PCB_ONFAULT	| catch faults
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	movl	#Lcoflt,a0@(PCB_ONFAULT) | catch faults
E 8
D 31
	movl	sp@(16),d2		| check count
E 31
I 31
	tstl	d0			| check count
E 31
	jlt	Lcoflt			| negative, error
	jeq	Lcodone			| zero, done
	movl	sp@(8),a0		| src address
	movl	sp@(12),a1		| dest address
D 31
	movl	a0,d0
	btst	#0,d0			| src address odd?
E 31
I 31
	movl	a0,d2
	btst	#0,d2			| src address odd?
E 31
	jeq	Lcoeven			| no, go check dest
	movb	a0@+,d1			| yes, get a byte
	movsb	d1,a1@+			| put a byte
I 13
	nop
E 13
D 31
	subql	#1,d2			| adjust count
E 31
I 31
	subql	#1,d0			| adjust count
E 31
	jeq	Lcodone			| exit if done
Lcoeven:
D 31
	movl	a1,d0
	btst	#0,d0			| dest address odd?
E 31
I 31
	movl	a1,d2
	btst	#0,d2			| dest address odd?
E 31
D 25
	jne	Lcobyte			| yes, must copy by bytes
E 25
I 25
	jne	Lcobloop		| yes, must copy by bytes
E 25
D 31
	movl	d2,d0			| no, get count
	lsrl	#2,d0			| convert to longwords
E 31
I 31
	movl	d0,d2			| no, get count
	lsrl	#2,d2			| convert to longwords
E 31
D 25
	jeq	Lcobyte			| no longwords, copy bytes
	subql	#1,d0			| set up for dbf
E 25
I 25
	jeq	Lcobloop		| no longwords, copy bytes
E 25
Lcolloop:
	movl	a0@+,d1			| get a long
	movsl	d1,a1@+			| put a long
I 13
	nop
E 13
D 25
	dbf	d0,Lcolloop		| til done
E 25
I 25
D 31
	subql	#1,d0
E 31
I 31
	subql	#1,d2
E 31
	jne	Lcolloop		| til done
E 25
D 31
	andl	#3,d2			| what remains
E 31
I 31
	andl	#3,d0			| what remains
E 31
	jeq	Lcodone			| all done
D 25
Lcobyte:
	subql	#1,d2			| set up for dbf
E 25
Lcobloop:
	movb	a0@+,d1			| get a byte
	movsb	d1,a1@+			| put a byte
I 13
	nop
E 13
D 25
	dbf	d2,Lcobloop		| til done
E 25
I 25
D 31
	subql	#1,d2
E 31
I 31
	subql	#1,d0
E 31
	jne	Lcobloop		| til done
E 25
Lcodone:
D 31
	moveq	#0,d0			| success
Lcoexit:
E 31
D 8
	clrl	_u+PCB_ONFAULT		| reset fault catcher
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	clrl	a0@(PCB_ONFAULT) 	| clear fault catcher
E 8
	movl	sp@+,d2			| restore scratch reg
	rts
Lcoflt:
	moveq	#EFAULT,d0		| got a fault
D 31
	jra	Lcoexit
E 31
I 31
	jra	Lcodone
E 31

/*
 * non-local gotos
 */
D 8
ALTENTRY(savectx, _setjmp)
E 8
ENTRY(setjmp)
	movl	sp@(4),a0	| savearea pointer
	moveml	#0xFCFC,a0@	| save d2-d7/a2-a7
	movl	sp@,a0@(48)	| and return address
	moveq	#0,d0		| return 0
	rts

D 19
ENTRY(qsetjmp)
	movl	sp@(4),a0	| savearea pointer
	lea	a0@(40),a0	| skip regs we do not save
	movl	a6,a0@+		| save FP
	movl	sp,a0@+		| save SP
	movl	sp@,a0@		| and return address
	moveq	#0,d0		| return 0
	rts

E 19
ENTRY(longjmp)
	movl	sp@(4),a0
	moveml	a0@+,#0xFCFC
	movl	a0@,sp@
	moveq	#1,d0
	rts

/*
D 28
 * The following primitives manipulate the run queues.
 * _whichqs tells which of the 32 queues _qs
 * have processes in them.  Setrq puts processes into queues, Remrq
 * removes them from queues.  The running process is on no queue,
 * other processes are on a queue related to p->p_pri, divided by 4
E 28
I 28
 * The following primitives manipulate the run queues.  _whichqs tells which
 * of the 32 queues _qs have processes in them.  Setrunqueue puts processes
 * into queues, Remrq removes them from queues.  The running process is on
D 30
 * no queue, other processes are on a queue related to p->p_pri, divided by 4
E 28
 * actually to shrink the 0-127 range of priorities into the 32 available
E 30
I 30
 * no queue, other processes are on a queue related to p->p_priority, divided
 * by 4 actually to shrink the 0-127 range of priorities into the 32 available
E 30
 * queues.
 */

	.globl	_whichqs,_qs,_cnt,_panic
D 7
	.comm	_noproc,4
	.comm	_runrun,4
E 7
I 7
D 13
	.globl	_curproc
	.comm	_want_resched,4
E 13
I 13
	.globl	_curproc,_want_resched
E 13
E 7

/*
D 28
 * Setrq(p)
E 28
I 28
 * Setrunqueue(p)
E 28
 *
 * Call should be made at spl6(), and p->p_stat should be SRUN
 */
D 28
ENTRY(setrq)
E 28
I 28
ENTRY(setrunqueue)
E 28
	movl	sp@(4),a0
D 30
	tstl	a0@(P_RLINK)
E 30
I 30
	tstl	a0@(P_BACK)
E 30
	jeq	Lset1
	movl	#Lset2,sp@-
	jbsr	_panic
Lset1:
	clrl	d0
D 30
	movb	a0@(P_PRI),d0
E 30
I 30
	movb	a0@(P_PRIORITY),d0
E 30
	lsrb	#2,d0
	movl	_whichqs,d1
	bset	d0,d1
	movl	d1,_whichqs
	lslb	#3,d0
	addl	#_qs,d0
D 30
	movl	d0,a0@(P_LINK)
E 30
I 30
	movl	d0,a0@(P_FORW)
E 30
	movl	d0,a1
D 30
	movl	a1@(P_RLINK),a0@(P_RLINK)
	movl	a0,a1@(P_RLINK)
	movl	a0@(P_RLINK),a1
	movl	a0,a1@(P_LINK)
E 30
I 30
	movl	a1@(P_BACK),a0@(P_BACK)
	movl	a0,a1@(P_BACK)
	movl	a0@(P_BACK),a1
	movl	a0,a1@(P_FORW)
E 30
	rts

Lset2:
D 28
	.asciz	"setrq"
E 28
I 28
	.asciz	"setrunqueue"
E 28
	.even

/*
 * Remrq(p)
 *
 * Call should be made at spl6().
 */
ENTRY(remrq)
	movl	sp@(4),a0
	clrl	d0
D 30
	movb	a0@(P_PRI),d0
E 30
I 30
	movb	a0@(P_PRIORITY),d0
E 30
	lsrb	#2,d0
	movl	_whichqs,d1
	bclr	d0,d1
	jne	Lrem1
	movl	#Lrem3,sp@-
	jbsr	_panic
Lrem1:
	movl	d1,_whichqs
D 30
	movl	a0@(P_LINK),a1
	movl	a0@(P_RLINK),a1@(P_RLINK)
	movl	a0@(P_RLINK),a1
	movl	a0@(P_LINK),a1@(P_LINK)
E 30
I 30
	movl	a0@(P_FORW),a1
	movl	a0@(P_BACK),a1@(P_BACK)
	movl	a0@(P_BACK),a1
	movl	a0@(P_FORW),a1@(P_FORW)
E 30
	movl	#_qs,a1
	movl	d0,d1
	lslb	#3,d1
	addl	d1,a1
D 30
	cmpl	a1@(P_LINK),a1
E 30
I 30
	cmpl	a1@(P_FORW),a1
E 30
	jeq	Lrem2
	movl	_whichqs,d1
	bset	d0,d1
	movl	d1,_whichqs
Lrem2:
D 30
	clrl	a0@(P_RLINK)
E 30
I 30
	clrl	a0@(P_BACK)
E 30
	rts

Lrem3:
	.asciz	"remrq"
Lsw0:
D 30
	.asciz	"swtch"
E 30
I 30
	.asciz	"switch"
E 30
	.even

D 10
/*
I 5
 * Masterpaddr is the p->p_addr of the running process on the master
 * processor.  When a multiprocessor system, the slave processors will have
 * an array of slavepaddrs (on an HP it only exists for the benefit of adb).
 */
	.globl	_masterpaddr
E 10
I 10
	.globl	_curpcb
	.globl	_masterpaddr	| XXX compatibility (debuggers)
E 10
	.data
D 10
_masterpaddr:
E 10
I 10
_masterpaddr:			| XXX compatibility (debuggers)
_curpcb:
E 10
	.long	0
I 8
D 19
pcbflag:
	.byte	0		| copy of pcb_flags low byte
E 19
I 19
mdpflag:
	.byte	0		| copy of proc md_flags low byte
E 19
	.align	2
D 9
	.comm	_nullpcb,SIZEOF_PCB
E 9
I 9
	.comm	nullpcb,SIZEOF_PCB
E 9
E 8
	.text

/*
I 8
D 30
 * At exit of a process, do a swtch for the last time.
E 30
I 30
 * At exit of a process, do a switch for the last time.
E 30
I 9
 * The mapping of the pcb at p->p_addr has already been deleted,
 * and the memory for the pcb+stack has been freed.
 * The ipl is high enough to prevent the memory from being reallocated.
E 9
 */
D 30
ENTRY(swtch_exit)
E 30
I 30
ENTRY(switch_exit)
E 30
D 9
	movl	#_nullpcb,_masterpaddr
E 9
I 9
D 10
	movl	#nullpcb,_masterpaddr	| save state into garbage pcb
E 10
I 10
	movl	#nullpcb,_curpcb	| save state into garbage pcb
E 10
E 9
	lea	tmpstk,sp		| goto a tmp stack
D 16
	jra	_swtch
E 16
I 16
D 30
	jra	_cpu_swtch
E 30
I 30
	jra	_cpu_switch
E 30
I 19
D 20
#ifdef GPROF
	nop
	nop
	nop
	nop
#endif
E 20
E 19
E 16

/*
E 8
E 5
D 26
 * When no processes are on the runq, Swtch branches to idle
E 26
I 26
 * When no processes are on the runq, Swtch branches to Idle
E 26
 * to wait for something to come ready.
 */
D 19
	.globl	Idle
E 19
I 19
	.globl	idle
E 19
I 10
D 26
Lidle:
	stop	#PSL_LOWIPL
E 26
E 10
D 19
Idle:
E 19
idle:
I 26
	stop	#PSL_LOWIPL
Idle:
E 26
D 10
	movw	#PSL_LOWIPL,sr
E 10
I 10
	movw	#PSL_HIGHIPL,sr
E 10
	tstl	_whichqs
D 10
	jne	Lsw1
	stop	#PSL_LOWIPL
	jra	idle
E 10
I 10
D 26
	jeq	Lidle
E 26
I 26
	jeq	idle
E 26
	movw	#PSL_LOWIPL,sr
	jra	Lsw1
E 10

Lbadsw:
	movl	#Lsw0,sp@-
	jbsr	_panic
	/*NOTREACHED*/

/*
D 16
 * Swtch()
E 16
I 16
D 30
 * cpu_swtch()
E 30
I 30
 * cpu_switch()
E 30
E 16
I 10
 *
 * NOTE: On the mc68851 (318/319/330) we attempt to avoid flushing the
 * entire ATC.  The effort involved in selective flushing may not be
 * worth it, maybe we should just flush the whole thing?
 *
 * NOTE 2: With the new VM layout we now no longer know if an inactive
 * user's PTEs have been changed (formerly denoted by the SPTECHG p_flag
 * bit).  For now, we just always flush the full ATC.
E 10
 */
D 15
ENTRY(swtch)
E 15
I 15
D 16
ENTRY(Swtch)
E 16
I 16
D 30
ENTRY(cpu_swtch)
E 30
I 30
ENTRY(cpu_switch)
E 30
E 16
E 15
D 8
	movw	sr,_u+PCB_PS
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
E 10
I 10
	movl	_curpcb,a0		| current pcb
E 10
	movw	sr,a0@(PCB_PS)		| save sr before changing ipl
#ifdef notyet
	movl	_curproc,sp@-		| remember last proc running
#endif
E 8
D 7
	movl	#1,_noproc
E 7
I 7
	clrl	_curproc
E 7
	addql	#1,_cnt+V_SWTCH
I 15

E 15
Lsw1:
I 8
	/*
	 * Find the highest-priority queue that isn't empty,
	 * then take the first proc from that queue.
	 */
E 8
	clrl	d0
D 10
	movl	_whichqs,d1
E 10
I 10
	lea	_whichqs,a0
	movl	a0@,d1
E 10
Lswchk:
	btst	d0,d1
	jne	Lswfnd
	addqb	#1,d0
	cmpb	#32,d0
	jne	Lswchk
D 26
	jra	idle
E 26
I 26
	jra	Idle
E 26
Lswfnd:
D 10
	movw	#PSL_HIGHIPL,sr
	movl	_whichqs,d1
E 10
I 10
	movw	#PSL_HIGHIPL,sr		| lock out interrupts
	movl	a0@,d1			| and check again...
E 10
	bclr	d0,d1
D 10
	jeq	Lsw1
	movl	d1,_whichqs
E 10
I 10
	jeq	Lsw1			| proc moved, rescan
	movl	d1,a0@			| update whichqs
	moveq	#1,d1			| double check for higher priority
	lsll	d0,d1			| process (which may have snuck in
	subql	#1,d1			| while we were finding this one)
	andl	a0@,d1
	jeq	Lswok			| no one got in, continue
	movl	a0@,d1
	bset	d0,d1			| otherwise put this one back
	movl	d1,a0@
	jra	Lsw1			| and rescan
Lswok:
E 10
	movl	d0,d1
D 10
	lslb	#3,d1
	addl	#_qs,d1
E 10
I 10
	lslb	#3,d1			| convert queue number to index
	addl	#_qs,d1			| locate queue (q)
E 10
	movl	d1,a1
D 10
	cmpl	a1@(P_LINK),a1
	jeq	Lbadsw
D 8
	movl	a1@(P_LINK),a0
E 8
I 8
	movl	a1@(P_LINK),a0		| a0 is selected proc
E 8
	movl	a0@(P_LINK),a1@(P_LINK)
	movl	a0@(P_LINK),a1
	movl	a0@(P_RLINK),a1@(P_RLINK)
	cmpl	a0@(P_LINK),d1
	jeq	Lsw2
E 10
I 10
D 30
	cmpl	a1@(P_LINK),a1		| anyone on queue?
E 30
I 30
	cmpl	a1@(P_FORW),a1		| anyone on queue?
E 30
	jeq	Lbadsw			| no, panic
D 30
	movl	a1@(P_LINK),a0			| p = q->p_link
	movl	a0@(P_LINK),a1@(P_LINK)		| q->p_link = p->p_link
	movl	a0@(P_LINK),a1			| q = p->p_link
	movl	a0@(P_RLINK),a1@(P_RLINK)	| q->p_rlink = p->p_rlink
	cmpl	a0@(P_LINK),d1		| anyone left on queue?
E 30
I 30
	movl	a1@(P_FORW),a0		| p = q->p_forw
	movl	a0@(P_FORW),a1@(P_FORW)	| q->p_forw = p->p_forw
	movl	a0@(P_FORW),a1		| q = p->p_forw
	movl	a0@(P_BACK),a1@(P_BACK)	| q->p_back = p->p_back
	cmpl	a0@(P_FORW),d1		| anyone left on queue?
E 30
	jeq	Lsw2			| no, skip
E 10
	movl	_whichqs,d1
D 10
	bset	d0,d1
E 10
I 10
	bset	d0,d1			| yes, reset bit
E 10
	movl	d1,_whichqs
Lsw2:
D 7
	clrl	_noproc
	clrl	_runrun
E 7
I 7
	movl	a0,_curproc
	clrl	_want_resched
I 8
#ifdef notyet
	movl	sp@+,a1
	cmpl	a0,a1			| switching to same proc?
	jeq	Lswdone			| yes, skip save and restore
#endif
	/*
	 * Save state of previous process in its pcb.
	 */
D 10
	movl	_masterpaddr,a1
E 10
I 10
	movl	_curpcb,a1
E 10
D 9
	movl	usp,a0			| grab USP
	movl	a0,a1@(PCB_USP)		| and save it
E 9
	moveml	#0xFCFC,a1@(PCB_REGS)	| save non-scratch registers
I 9
	movl	usp,a2			| grab USP (a2 has been saved)
	movl	a2,a1@(PCB_USP)		| and save it
E 9
D 13
	movl	_CMAP2,a1@(PCB_CMAP2)	| save temporary map PTE
E 13
#ifdef FPCOPROC
D 9
	lea	a1@(PCB_FPCTX),a0	| pointer to FP save area
	fsave	a0@			| save FP state
	tstb	a0@			| null state frame?
E 9
I 9
	lea	a1@(PCB_FPCTX),a2	| pointer to FP save area
	fsave	a2@			| save FP state
	tstb	a2@			| null state frame?
E 9
	jeq	Lswnofpsave		| yes, all done
D 9
	fmovem	fp0-fp7,a0@(216)	| save FP general registers
	fmovem	fpcr/fpsr/fpi,a0@(312)	| save FP control registers
E 9
I 9
	fmovem	fp0-fp7,a2@(216)	| save FP general registers
	fmovem	fpcr/fpsr/fpi,a2@(312)	| save FP control registers
E 9
Lswnofpsave:
#endif

D 9
	movl	_curproc,a0
E 9
#ifdef DIAGNOSTIC
E 8
E 7
	tstl	a0@(P_WCHAN)
	jne	Lbadsw
	cmpb	#SRUN,a0@(P_STAT)
	jne	Lbadsw
I 8
#endif
E 8
D 10
	clrl	a0@(P_RLINK)
D 8
	movl	a0@(P_ADDR),d0
I 5
	movl	d0,_masterpaddr
D 7
	movl	a0@(P_MAP),a1		| map = p->p_map
	tstl	a1			| map == VM_MAP_NULL?
E 7
I 7
	movl	a0@(P_VMSPACE),a1	| map = p->p_vmspace
	tstl	a1			| map == VM_MAP_NULL? ???
E 8
I 8
	movl	a0@(P_ADDR),a1
	movl	a1,_masterpaddr
E 10
I 10
D 30
	clrl	a0@(P_RLINK)		| clear back link
E 30
I 30
	clrl	a0@(P_BACK)		| clear back link
E 30
I 19
	movb	a0@(P_MDFLAG+3),mdpflag	| low byte of p_md.md_flags
E 19
	movl	a0@(P_ADDR),a1		| get p_addr
	movl	a1,_curpcb
E 10
D 19
	movb	a1@(PCB_FLAGS+1),pcbflag | copy of pcb_flags low byte
E 19
D 9
	movl	a0@(P_VMSPACE),a0	| map = p->p_vmspace
	tstl	a0			| map == VM_MAP_NULL? ???
E 8
E 7
	jeq	Lswnochg		| yes, skip
D 8
	movl	a1@(PMAP),a1		| pmap = map->pmap
D 7
	tstl	a1			| pmap == PMAP_NULL?
E 7
I 7
	tstl	a1			| pmap == PMAP_NULL? ???
E 8
I 8
	movl	a0@(PMAP),a0		| pmap = map->pmap
	tstl	a0			| pmap == PMAP_NULL? ???
E 8
E 7
	jeq	Lswnochg		| yes, skip
E 9
I 9

	/* see if pmap_activate needs to be called; should remove this */
	movl	a0@(P_VMSPACE),a0	| vmspace = p->p_vmspace
I 10
#ifdef DIAGNOSTIC
	tstl	a0			| map == VM_MAP_NULL?
	jeq	Lbadsw			| panic
#endif
E 10
	lea	a0@(VM_PMAP),a0		| pmap = &vmspace.vm_pmap
I 10
D 11
#ifdef DIAGNOSTIC
	tstl	a0			| pmap == PMAP_NULL?
	jeq	Lbadsw			| panic
#endif
E 11
E 10
E 9
D 8
	tstl	a1@(PM_STCHG)		| pmap->st_changed?
E 8
I 8
	tstl	a0@(PM_STCHG)		| pmap->st_changed?
E 8
	jeq	Lswnochg		| no, skip
D 8
	movl	d0,sp@-			| push pcb (at p_addr)
	pea	a1@			| push pmap
E 8
I 8
	pea	a1@			| push pcb (at p_addr)
	pea	a0@			| push pmap
E 8
	jbsr	_pmap_activate		| pmap_activate(pmap, pcb)
	addql	#8,sp
D 8
	movl	_masterpaddr,d0		| restore p_addr for resume below
E 8
I 8
D 10
	movl    _masterpaddr,a1         | restore p_addr
E 10
I 10
	movl	_curpcb,a1		| restore p_addr
E 10
E 8
Lswnochg:
E 5
D 8
	jra	Lres0
E 8

D 10
/*
D 8
 * Resume(p_addr)
 *
E 8
 * NOTE: on the PMMU we attempt to avoid flushing the entire TAC.
 * The effort involved in selective flushing may not be worth it,
 * maybe we should just flush the whole thing?
 */
E 10
D 8
ENTRY(resume)
	movw	sr,_u+PCB_PS
	movl	sp@(4),d0
Lres0:
	lea	_u,a1			| &u
	movl	usp,a0			| grab USP
	movl	a0,a1@(PCB_USP)		| and save it
	moveml	#0xFCFC,a1@(PCB_REGS)	| save non-scratch registers
#ifdef FPCOPROC
	lea	a1@(PCB_FPCTX),a0	| pointer to FP save area
D 5
	.word	0xf310			| fsave a0@
E 5
I 5
	fsave	a0@			| save FP state
E 5
	tstb	a0@			| null state frame?
	jeq	Lresnofpsave		| yes, all done
D 5
	.word	0xf228,0xf0ff,0x00d8	| fmovem fp0-fp7,a0@(216)
	.word	0xf228,0xbc00,0x0138	| fmovem fpcr/fpsr/fpiar,a0@(312)
E 5
I 5
	fmovem	fp0-fp7,a0@(216)	| save FP general registers
	fmovem	fpcr/fpsr/fpi,a0@(312)	| save FP control registers
E 5
Lresnofpsave:
#endif
E 8
D 16
#ifdef PROFTIMER
I 9
#ifdef notdef
E 9
	movw	#SPL6,sr		| protect against clock interrupts
I 9
#endif
E 9
	bclr	#0,_profon		| clear user profiling bit, was set?
	jeq	Lskipoff		| no, clock off or doing kernel only
#ifdef GPROF
	tstb	_profon			| kernel profiling also enabled?
	jlt	Lskipoff		| yes, nothing more to do
#endif
D 5
	movb	#0,_IObase+CLKCR2	| no, just user, select CR3
	movb	#0,_IObase+CLKCR3	| and turn it off
E 5
I 5
	CLKADDR(a0)
	movb	#0,a0@(CLKCR2)		| no, just user, select CR3
	movb	#0,a0@(CLKCR3)		| and turn it off
E 5
Lskipoff:
#endif
E 16
D 8
	movl	_CMAP2,a1@(PCB_CMAP2)	| save temporary map PTE
E 8
I 5
	movl	#PGSHIFT,d1
I 8
	movl	a1,d0
E 8
	lsrl	d1,d0			| convert p_addr to page number
D 13
	lsll	#2,d0			| and now to Systab offset
	addl	_Sysmap,d0		| add Systab base to get PTE addr
E 13
I 13
	lsll	#2,d0			| and now to Sysmap offset
	addl	_Sysmap,d0		| add Sysmap base to get PTE addr
E 13
I 9
#ifdef notdef
E 9
E 5
	movw	#PSL_HIGHIPL,sr		| go crit while changing PTEs
I 9
#endif
E 9
	lea	tmpstk,sp		| now goto a tmp stack for NMI
	movl	d0,a0			| address of new context
D 5
	lea	_Umap,a1		| address of PTEs for u
E 5
I 5
D 8
	movl	_Umap,a1		| address of PTEs for u
E 5
	moveq	#UPAGES-1,d0		| sizeof u
E 8
I 8
D 9
	movl	_Umap,a1		| address of PTEs for kstack
E 9
I 9
	movl	_Umap,a2		| address of PTEs for kstack
E 9
	moveq	#UPAGES-1,d0		| sizeof kstack
E 8
Lres1:
	movl	a0@+,d1			| get PTE
	andl	#~PG_PROT,d1		| mask out old protection
	orl	#PG_RW+PG_V,d1		| ensure valid and writable
D 9
	movl	d1,a1@+			| load it up
E 9
I 9
	movl	d1,a2@+			| load it up
E 9
	dbf	d0,Lres1		| til done
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lres1a			| no, skip
	.word	0xf518			| yes, pflusha
	movl	a1@(PCB_USTP),d0	| get USTP
	moveq	#PGSHIFT,d1
	lsll	d1,d0			| convert to addr
	.long	0x4e7b0806		| movc d0,urp
	jra	Lcxswdone
Lres1a:
#endif
E 13
D 8
	lea	_u,a1			| reload &u
E 8
I 8
D 9
	movl	_masterpaddr,a1		| reload pcb pointer
E 9
E 8
	movl	#CACHE_CLR,d0
	movc	d0,cacr			| invalidate cache(s)
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu4			| yes, skip
D 10
	jmi	Lnot68851a		| must flush all on 68030 MMU
#ifdef DEBUG
D 5
	tstl	fullflush		| 68851, conservative?
E 5
I 5
	tstl	fulltflush		| 68851, conservative?
E 5
	jne	Lnot68851a		| yes, go flush all
#endif
D 5
	.long	0xf0003494		| no, pflushs #4,#4 (flush super side)
E 5
I 5
	pflushs	#4,#4			| flush only supervisor side
E 5
	jra	Lres2
Lnot68851a:
E 10
D 5
	.long	0xf0002400		| pflusha
E 5
I 5
	pflusha				| flush entire TLB
E 5
D 10
Lres2:
E 10
	movl	a1@(PCB_USTP),d0	| get USTP
	moveq	#PGSHIFT,d1
	lsll	d1,d0			| convert to addr
	lea	_protorp,a0		| CRP prototype
	movl	d0,a0@(4)		| stash USTP
D 5
	.long	0xf0104C00		| pmove a0@,crp
E 5
I 5
	pmove	a0@,crp			| load new user root pointer
E 5
	jra	Lcxswdone		| thats it
Lhpmmu4:	
#endif
#if defined(HP320) || defined(HP350)
D 5
	movl	_IObase+MMUTBINVAL,d1	| invalidate TLB
E 5
I 5
	MMUADDR(a0)
	movl	a0@(MMUTBINVAL),d1	| invalidate TLB
E 5
	tstl	_ectype			| got external VAC?
	jle	Lnocache1		| no, skip
D 5
	movl	#_IObase+MMUCMD,a0	| addr of MMU command register
	andl	#~MMU_CEN,a0@		| toggle cache enable
	orl	#MMU_CEN,a0@		| to clear data cache
E 5
I 5
	andl	#~MMU_CEN,a0@(MMUCMD)	| toggle cache enable
	orl	#MMU_CEN,a0@(MMUCMD)	| to clear data cache
E 5
Lnocache1:
D 5
	movl	a1@(PCB_USTP),_IObase+MMUUSTP	| context switch
E 5
I 5
	movl	a1@(PCB_USTP),a0@(MMUUSTP) | context switch
E 5
#endif
Lcxswdone:
D 7
	movl	a1@(U_PROCP),a0		| u.u_procp
E 7
I 7
D 8
	movl	_curproc,a0		| curproc
E 7
	bclr	#SPTECHGB-24,a0@(P_FLAG)| clear SPTECHG bit
E 8
D 9
#if defined(HP330)
	jeq	Lnot68851b		| if set need to flush user TLB
	tstl	_mmutype		| 68851 PMMU?
	jle	Lnot68851b		| no, skip
D 5
	.long	0xf0003490		| pflushs #0,#4
E 5
I 5
	pflushs	#0,#4			| user PT changed, flush user TLB
E 5
Lnot68851b:
#endif
E 9
D 13
	movl	a1@(PCB_CMAP2),_CMAP2	| reload tmp map
E 13
	moveml	a1@(PCB_REGS),#0xFCFC	| and registers
	movl	a1@(PCB_USP),a0
	movl	a0,usp			| and USP
D 16
#ifdef PROFTIMER
	tstl	a1@(U_PROFSCALE)	| process being profiled?
	jeq	Lskipon			| no, do nothing
	orb	#1,_profon		| turn on user profiling bit
#ifdef GPROF
	jlt	Lskipon			| already profiling kernel, all done
#endif
D 5
	lea	_IObase+CLKMSB3,a0	| address timer 3 counter
E 5
I 5
	CLKADDR(a0)
E 5
	movl	_profint,d1		| profiling interval
	subql	#1,d1			|   adjusted
D 5
	movepw	d1,a0@(0)		| set interval
	movb	#0,_IObase+CLKCR2	| select CR3
	movb	#64,_IObase+CLKCR3	| turn it on
E 5
I 5
	movepw	d1,a0@(CLKMSB3)		| set interval
	movb	#0,a0@(CLKCR2)		| select CR3
	movb	#64,a0@(CLKCR3)		| turn it on
E 5
Lskipon:
#endif
E 16
#ifdef FPCOPROC
	lea	a1@(PCB_FPCTX),a0	| pointer to FP save area
	tstb	a0@			| null state frame?
	jeq	Lresfprest		| yes, easy
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lresnot040		| no, skip
	clrl	sp@-			| yes...
	frestore sp@+			| ...magic!
Lresnot040:
#endif
E 13
D 5
	.word	0xf228,0x9c00,0x0138	| fmovem a0@(312),fpcr/fpsr/fpiar
	.word	0xf228,0xd0ff,0x00d8	| fmovem a0@(216),fp0-fp7
E 5
I 5
	fmovem	a0@(312),fpcr/fpsr/fpi	| restore FP control registers
	fmovem	a0@(216),fp0-fp7	| restore FP general registers
E 5
Lresfprest:
D 5
	.word	0xf350			| frestore a0@
E 5
I 5
	frestore a0@			| restore state
E 5
#endif
D 9
	tstl	a1@(PCB_SSWAP)		| do an alternate return?
D 8
	jne	Lres3			| yes, go reload regs
E 8
I 8
	jne	Lres3			| yes, do non-local goto
E 9
E 8
	movw	a1@(PCB_PS),sr		| no, restore PS
D 9
	rts
I 8

E 9
D 10
	/*
D 9
	 * simulate longjmp returning from savectx;
	 * that frame wasn't active when this stack was copied,
	 * although savectx's caller's stack was active,
	 * and savectx will have saved sp while it was active.
	 * Construct fake frame from which to "return".
E 9
I 9
	 * For savectx to work correctly, we need to "return" a non-zero
	 * value; d0 was set above, so do nothing.
E 9
	 */
E 10
I 10
	moveq	#1,d0			| return 1 (for alternate returns)
E 10
E 8
D 9
Lres3:
D 8
	movl	a1@(PCB_SSWAP),a0	| addr of saved context
E 8
I 8
	movl	a1@(PCB_SSWAP),sp@	| alternate return pc; fake call frame
E 8
	clrl	a1@(PCB_SSWAP)		| clear flag
D 8
	moveml	a0@+,#0x7CFC		| restore registers
	movl	a0@+,a1			| and SP
	cmpl	sp,a1			| paranoia...
	jge	Lres4			| ...must be popping, yes?
	lea	tmpstk,sp		| no! set up a legit stack
	movl	#Lres5,sp@-		| push a panic message
	jbsr	_panic			| and panic
	/* NOTREACHED */
Lres4:
	movl	a1,sp			| restore SP
	movl	a0@,sp@			| and PC
	moveq	#1,d0			| arrange for non-zero return
	movw	#PSL_LOWIPL,sr		| lower SPL
E 8
I 8
	movw	a1@(PCB_PS),sr		| restore PS
	moveq	#1,d0			| return 1
E 9
E 8
	rts

D 8
Lres5:
	.asciz	"ldctx"
	.even
E 8
I 8
/*
 * savectx(pcb, altreturn)
 * Update pcb, saving current processor state and arranging
D 30
 * for alternate return ala longjmp in swtch if altreturn is true.
E 30
I 30
 * for alternate return ala longjmp in switch if altreturn is true.
E 30
 */
ENTRY(savectx)
	movl	sp@(4),a1
	movw	sr,a1@(PCB_PS)
	movl	usp,a0			| grab USP
	movl	a0,a1@(PCB_USP)		| and save it
	moveml	#0xFCFC,a1@(PCB_REGS)	| save non-scratch registers
D 13
	movl	_CMAP2,a1@(PCB_CMAP2)	| save temporary map PTE
E 13
#ifdef FPCOPROC
	lea	a1@(PCB_FPCTX),a0	| pointer to FP save area
	fsave	a0@			| save FP state
	tstb	a0@			| null state frame?
	jeq	Lsvnofpsave		| yes, all done
	fmovem	fp0-fp7,a0@(216)	| save FP general registers
	fmovem	fpcr/fpsr/fpi,a0@(312)	| save FP control registers
Lsvnofpsave:
#endif
	tstl	sp@(8)			| altreturn?
	jeq	Lsavedone
D 9
	movl	sp@,a1@(PCB_SSWAP)	| alternate return address
E 9
I 9
	movl	sp,d0			| relocate current sp relative to a1
	subl	#_kstack,d0		|   (sp is relative to kstack):
	addl	d0,a1			|   a1 += sp - kstack;
	movl	sp@,a1@			| write return pc at (relocated) sp@
E 9
Lsavedone:
	moveq	#0,d0			| return 0
	rts
E 8

/*
 * {fu,su},{byte,sword,word}
 */
ALTENTRY(fuiword, _fuword)
ENTRY(fuword)
D 10
	movl	sp@(4),d0		| address to read
	btst	#0,d0			| is it odd?
	jne	Lfserr			| yes, a fault
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 8
	movl	d0,a0
E 10
I 10
	movl	sp@(4),a0		| address to read
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	movsl	a0@,d0			| do read from user space
I 13
	nop
E 13
	jra	Lfsdone

ENTRY(fusword)
D 10
	movl	sp@(4),d0
	btst	#0,d0			| is address odd?
	jne	Lfserr			| yes, a fault
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 8
	movl	d0,a0			| address to read
E 10
I 10
	movl	sp@(4),a0
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	moveq	#0,d0
	movsw	a0@,d0			| do read from user space
I 13
	nop
E 13
	jra	Lfsdone

I 15
/* Just like fusword, but tells trap code not to page in. */
ENTRY(fuswintr)
	movl	sp@(4),a0
	movl	_curpcb,a1
	movl	#_fswintr,a1@(PCB_ONFAULT)
	moveq	#0,d0
	movsw	a0@,d0
	nop
	jra	Lfsdone

E 15
ALTENTRY(fuibyte, _fubyte)
ENTRY(fubyte)
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 10
E 8
	movl	sp@(4),a0		| address to read
I 10
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	moveq	#0,d0
	movsb	a0@,d0			| do read from user space
I 13
	nop
E 13
	jra	Lfsdone

Lfserr:
	moveq	#-1,d0			| error indicator
Lfsdone:
D 8
	clrl	_u+PCB_ONFAULT		| clear fault address
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
	clrl	a0@(PCB_ONFAULT) 	| clear fault address
E 10
I 10
	clrl	a1@(PCB_ONFAULT) 	| clear fault address
E 10
E 8
	rts

I 15
/* Just like Lfserr, but the address is different (& exported). */
	.globl	_fswintr
_fswintr:
	moveq	#-1,d0
	jra	Lfsdone


E 15
D 13
ALTENTRY(suiword, _suword)
E 13
I 13
/*
 * Write a longword in user instruction space.
 * Largely the same as suword but with a final i-cache purge on those
 * machines with split caches.
 */
ENTRY(suiword)
	movl	sp@(4),a0		| address to write
	movl	sp@(8),d0		| value to put there
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
	movsl	d0,a0@			| do write to user space
	nop
	moveq	#0,d0			| indicate no fault
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lsuicpurge		| no, skip
	.word	0xf498			| cinva ic (XXX overkill)
	jra	Lfsdone
Lsuicpurge:
#endif
	movl	#IC_CLEAR,d1
	movc	d1,cacr			| invalidate i-cache
	jra	Lfsdone

E 13
ENTRY(suword)
D 10
	movl	sp@(4),d0		| address to write
	btst	#0,d0			| is it odd?
	jne	Lfserr			| yes, a fault
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 8
	movl	d0,a0			| address to write
E 10
I 10
	movl	sp@(4),a0		| address to write
E 10
	movl	sp@(8),d0		| value to put there
I 10
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	movsl	d0,a0@			| do write to user space
I 13
	nop
E 13
	moveq	#0,d0			| indicate no fault
	jra	Lfsdone

ENTRY(susword)
D 10
	movl	sp@(4),d0		| address to write
	btst	#0,d0			| is it odd?
	jne	Lfserr			| yes, a fault
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 8
	movl	d0,a0			| address to write
E 10
I 10
	movl	sp@(4),a0		| address to write
E 10
	movw	sp@(10),d0		| value to put there
I 10
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	movsw	d0,a0@			| do write to user space
I 13
	nop
E 13
	moveq	#0,d0			| indicate no fault
I 15
	jra	Lfsdone

ENTRY(suswintr)
	movl	sp@(4),a0
	movw	sp@(10),d0
	movl	_curpcb,a1
	movl	#_fswintr,a1@(PCB_ONFAULT)
	movsw	d0,a0@
	nop
	moveq	#0,d0
E 15
	jra	Lfsdone

ALTENTRY(suibyte, _subyte)
ENTRY(subyte)
D 8
	movl	#Lfserr,_u+PCB_ONFAULT	| where to return to on a fault
E 8
I 8
D 10
	movl	_masterpaddr,a0		| current pcb
	movl	#Lfserr,a0@(PCB_ONFAULT) | where to return to on a fault
E 10
E 8
	movl	sp@(4),a0		| address to write
	movb	sp@(11),d0		| value to put there
I 10
	movl	_curpcb,a1		| current pcb
	movl	#Lfserr,a1@(PCB_ONFAULT) | where to return to on a fault
E 10
	movsb	d0,a0@			| do write to user space
I 13
	nop
E 13
	moveq	#0,d0			| indicate no fault
	jra	Lfsdone

D 13
/*
 * Copy 1 relocation unit (NBPG bytes)
 * from user virtual address to physical address
 */
ENTRY(copyseg)
I 8
D 10
	movl	_masterpaddr,a0			| current pcb
	movl	#Lcpydone,a0@(PCB_ONFAULT)	| where to return to on a fault
E 10
I 10
	movl	_curpcb,a1			| current pcb
	movl	#Lcpydone,a1@(PCB_ONFAULT)	| where to return to on a fault
E 10
E 8
	movl	sp@(8),d0			| destination page number
	moveq	#PGSHIFT,d1
	lsll	d1,d0				| convert to address
	orl	#PG_CI+PG_RW+PG_V,d0		| make sure valid and writable
D 5
	movl	d0,_CMAP2			| load in page table
	movl	#_CADDR2,sp@-			| destination kernel VA
E 5
I 5
	movl	_CMAP2,a0
	movl	_CADDR2,sp@-			| destination kernel VA
	movl	d0,a0@				| load in page table
E 5
	jbsr	_TBIS				| invalidate any old mapping
	addql	#4,sp
D 5
	movl	#_CADDR2,a1			| destination addr
E 5
I 5
	movl	_CADDR2,a1			| destination addr
E 5
	movl	sp@(4),a0			| source addr
	movl	#NBPG/4-1,d0			| count
D 8
	movl	#Lcpydone,_u+PCB_ONFAULT	| where to go on a fault
E 8
Lcpyloop:
	movsl	a0@+,d1				| read longword
	movl	d1,a1@+				| write longword
	dbf	d0,Lcpyloop			| continue until done
Lcpydone:
D 8
	clrl	_u+PCB_ONFAULT			| clear error catch
E 8
I 8
D 10
	movl	_masterpaddr,a0			| current pcb
	clrl	a0@(PCB_ONFAULT) 		| clear error catch
E 10
I 10
	movl	_curpcb,a1			| current pcb
	clrl	a1@(PCB_ONFAULT) 		| clear error catch
E 13
I 13
#if defined(HP380)
ENTRY(suline)
	movl	sp@(4),a0		| address to write
	movl	_curpcb,a1		| current pcb
	movl	#Lslerr,a1@(PCB_ONFAULT) | where to return to on a fault
	movl	sp@(8),a1		| address of line
	movl	a1@+,d0			| get lword
	movsl	d0,a0@+			| put lword
	nop				| sync
	movl	a1@+,d0			| get lword
	movsl	d0,a0@+			| put lword
	nop				| sync
	movl	a1@+,d0			| get lword
	movsl	d0,a0@+			| put lword
	nop				| sync
	movl	a1@+,d0			| get lword
	movsl	d0,a0@+			| put lword
	nop				| sync
	moveq	#0,d0			| indicate no fault
	jra	Lsldone
Lslerr:
	moveq	#-1,d0
Lsldone:
	movl	_curpcb,a1		| current pcb
	clrl	a1@(PCB_ONFAULT) 	| clear fault address
E 13
E 10
E 8
	rts
I 13
#endif
E 13

/*
I 5
D 13
 * Copy 1 relocation unit (NBPG bytes)
 * from physical address to physical address
 */
ENTRY(physcopyseg)
	movl	sp@(4),d0			| source page number
	moveq	#PGSHIFT,d1
	lsll	d1,d0				| convert to address
	orl	#PG_CI+PG_RW+PG_V,d0		| make sure valid and writable
	movl	_CMAP1,a0
	movl	d0,a0@				| load in page table
	movl	_CADDR1,sp@-			| destination kernel VA
	jbsr	_TBIS				| invalidate any old mapping
	addql	#4,sp

	movl	sp@(8),d0			| destination page number
	moveq	#PGSHIFT,d1
	lsll	d1,d0				| convert to address
	orl	#PG_CI+PG_RW+PG_V,d0		| make sure valid and writable
	movl	_CMAP2,a0
	movl	d0,a0@				| load in page table
	movl	_CADDR2,sp@-			| destination kernel VA
	jbsr	_TBIS				| invalidate any old mapping
	addql	#4,sp

	movl	_CADDR1,a0			| source addr
	movl	_CADDR2,a1			| destination addr
	movl	#NBPG/4-1,d0			| count
Lpcpy:
	movl	a0@+,a1@+			| copy longword
	dbf	d0,Lpcpy			| continue until done
	rts

/*
E 5
 * zero out physical memory
 * specified in relocation units (NBPG bytes)
 */
ENTRY(clearseg)
	movl	sp@(4),d0			| destination page number
	moveq	#PGSHIFT,d1
	lsll	d1,d0				| convert to address
	orl	#PG_CI+PG_RW+PG_V,d0		| make sure valid and writable
D 5
	movl	d0,_CMAP1			| load in page map
	movl	#_CADDR1,sp@-			| destination kernel VA
E 5
I 5
	movl	_CMAP1,a0
	movl	_CADDR1,sp@-			| destination kernel VA
	movl	d0,a0@				| load in page map
E 5
	jbsr	_TBIS				| invalidate any old mapping
	addql	#4,sp
D 5
	movl	#_CADDR1,a1			| destination addr
E 5
I 5
	movl	_CADDR1,a1			| destination addr
E 5
	movl	#NBPG/4-1,d0			| count
/* simple clear loop is fastest on 68020 */
Lclrloop:
	clrl	a1@+				| clear a longword
	dbf	d0,Lclrloop			| continue til done
	rts

/*
E 13
 * Invalidate entire TLB.
 */
ENTRY(TBIA)
__TBIA:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lmotommu3		| no, skip
	.word	0xf518			| yes, pflusha
	rts
Lmotommu3:
#endif
E 13
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu6			| yes, skip
D 5
	.long	0xf0002400		| no, pflusha
E 5
I 5
	pflusha				| flush entire TLB
E 5
#if defined(HP360) || defined(HP370)
	jpl	Lmc68851a		| 68851 implies no d-cache
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
Lmc68851a:
#endif
	rts
Lhpmmu6:
#endif
#if defined(HP320) || defined(HP350)
D 5
	movl	_IObase+MMUTBINVAL,sp@-	| do not ask me, this
E 5
I 5
	MMUADDR(a0)
	movl	a0@(MMUTBINVAL),sp@-	| do not ask me, this
E 5
	addql	#4,sp			|   is how hpux does it
D 5
	jra	__DCIA			| XXX: invalidate entire cache
E 5
I 5
#ifdef DEBUG
	tstl	fullcflush
	jne	__DCIA			| XXX: invalidate entire cache
E 5
#endif
I 5
#endif
E 5
	rts

/*
 * Invalidate any TLB entry for given VA (TB Invalidate Single)
 */
ENTRY(TBIS)
#ifdef DEBUG
D 5
	tstl	fullflush		| being conservative?
E 5
I 5
	tstl	fulltflush		| being conservative?
E 5
	jne	__TBIA			| yes, flush entire TLB
#endif
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lmotommu4		| no, skip
	movl	sp@(4),a0
	movc	dfc,d1
	moveq	#1,d0			| user space
	movc	d0,dfc
	.word	0xf508			| pflush a0@
	moveq	#5,d0			| super space
	movc	d0,dfc
	.word	0xf508			| pflush a0@
	movc	d1,dfc
	rts
Lmotommu4:
#endif
E 13
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu5			| yes, skip
	movl	sp@(4),a0		| get addr to flush
#if defined(HP360) || defined(HP370)
	jpl	Lmc68851b		| is 68851?
D 5
	.long	0xf0103810		| pflush #0,#0,a0@
E 5
I 5
	pflush	#0,#0,a0@		| flush address from both sides
E 5
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip data cache
	rts
Lmc68851b:
#endif
D 5
	.long	0xf0103c10		| pflushs #0,#0,a0@
E 5
I 5
	pflushs	#0,#0,a0@		| flush address from both sides
E 5
	rts
Lhpmmu5:
#endif
#if defined(HP320) || defined(HP350)
	movl	sp@(4),d0		| VA to invalidate
	bclr	#0,d0			| ensure even
	movl	d0,a0
	movw	sr,d1			| go critical
	movw	#PSL_HIGHIPL,sr		|   while in purge space
	moveq	#FC_PURGE,d0		| change address space
	movc	d0,dfc			|   for destination
	moveq	#0,d0			| zero to invalidate?
	movsl	d0,a0@			| hit it
	moveq	#FC_USERD,d0		| back to old
	movc	d0,dfc			|   address space
	movw	d1,sr			| restore IPL
#endif
	rts

/*
 * Invalidate supervisor side of TLB
 */
ENTRY(TBIAS)
#ifdef DEBUG
D 5
	tstl	fullflush		| being conservative?
E 5
I 5
	tstl	fulltflush		| being conservative?
E 5
	jne	__TBIA			| yes, flush everything
#endif
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lmotommu5		| no, skip
	.word	0xf518			| yes, pflusha (for now) XXX
	rts
Lmotommu5:
#endif
E 13
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu7			| yes, skip
#if defined(HP360) || defined(HP370)
	jpl	Lmc68851c		| 68851?
D 5
	.long	0xf0003094		| pflush #4,#4
E 5
I 5
	pflush #4,#4			| flush supervisor TLB entries
E 5
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
	rts
Lmc68851c:
#endif
D 5
	.long	0xf0003494		| pflushs #4,#4
E 5
I 5
	pflushs #4,#4			| flush supervisor TLB entries
E 5
	rts
Lhpmmu7:
#endif
#if defined(HP320) || defined(HP350)
I 5
	MMUADDR(a0)
E 5
	movl	#0x8000,d0		| more
D 5
	movl	d0,_IObase+MMUTBINVAL	|   HP magic
	jra	__DCIS			| XXX: invalidate entire sup. cache
E 5
I 5
	movl	d0,a0@(MMUTBINVAL)	|   HP magic
#ifdef DEBUG
	tstl	fullcflush
	jne	__DCIS			| XXX: invalidate entire sup. cache
E 5
#endif
I 5
#endif
E 5
	rts

/*
 * Invalidate user side of TLB
 */
ENTRY(TBIAU)
#ifdef DEBUG
D 5
	tstl	fullflush		| being conservative?
E 5
I 5
	tstl	fulltflush		| being conservative?
E 5
	jne	__TBIA			| yes, flush everything
#endif
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	Lmotommu6		| no, skip
	.word	0xf518			| yes, pflusha (for now) XXX
	rts
Lmotommu6:
#endif
E 13
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu8			| yes, skip
#if defined(HP360) || defined(HP370)
	jpl	Lmc68851d		| 68851?
D 5
	.long	0xf0003090		| pflush #0,#4
E 5
I 5
	pflush	#0,#4			| flush user TLB entries
E 5
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
	rts
Lmc68851d:
#endif
D 5
	.long	0xf0003490		| pflushs #0,#4
E 5
I 5
	pflushs	#0,#4			| flush user TLB entries
E 5
	rts
Lhpmmu8:
#endif
#if defined(HP320) || defined(HP350)
I 5
	MMUADDR(a0)
E 5
	moveq	#0,d0			| more
D 5
	movl	d0,_IObase+MMUTBINVAL	|   HP magic
	jra	__DCIU			| XXX: invalidate entire user cache
E 5
I 5
	movl	d0,a0@(MMUTBINVAL)	|   HP magic
#ifdef DEBUG
	tstl	fullcflush
	jne	__DCIU			| XXX: invalidate entire user cache
E 5
#endif
I 5
#endif
E 5
	rts

/*
 * Invalidate instruction cache
 */
ENTRY(ICIA)
I 13
#if defined(HP380)
ENTRY(ICPA)
	cmpl	#-2,_mmutype		| 68040
	jne	Lmotommu7		| no, skip
	.word	0xf498			| cinva ic
	rts
Lmotommu7:
#endif
E 13
	movl	#IC_CLEAR,d0
	movc	d0,cacr			| invalidate i-cache
	rts

/*
 * Invalidate data cache.
 * HP external cache allows for invalidation of user/supervisor portions.
I 5
 * NOTE: we do not flush 68030 on-chip cache as there are no aliasing
 * problems with DC_WA.  The only cases we have to worry about are context
 * switch and TLB changes, both of which are handled "in-line" in resume
 * and TBI*.
E 5
 */
ENTRY(DCIA)
__DCIA:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040
	jne	Lmotommu8		| no, skip
	/* XXX implement */
	rts
Lmotommu8:
#endif
E 13
D 5
#if defined(HP360) || defined(HP370)
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
#endif
E 5
#if defined(HP320) || defined(HP350)
	tstl	_ectype			| got external VAC?
	jle	Lnocache2		| no, all done
D 5
	movl	#_IObase+MMUCMD,a0	| MMU control reg
	andl	#~MMU_CEN,a0@		| disable cache
	orl	#MMU_CEN,a0@		| reenable cache
E 5
I 5
	MMUADDR(a0)
	andl	#~MMU_CEN,a0@(MMUCMD)	| disable cache in MMU control reg
	orl	#MMU_CEN,a0@(MMUCMD)	| reenable cache in MMU control reg
E 5
Lnocache2:
#endif
	rts

ENTRY(DCIS)
__DCIS:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040
	jne	Lmotommu9		| no, skip
	/* XXX implement */
	rts
Lmotommu9:
#endif
E 13
D 5
#if defined(HP360) || defined(HP370)
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
#endif
E 5
#if defined(HP320) || defined(HP350)
	tstl	_ectype			| got external VAC?
	jle	Lnocache3		| no, all done
D 5
	movl	_IObase+MMUSSTP,d0	| read the supervisor STP
	movl	d0,_IObase+MMUSSTP	| write it back
E 5
I 5
	MMUADDR(a0)
	movl	a0@(MMUSSTP),d0		| read the supervisor STP
	movl	d0,a0@(MMUSSTP)		| write it back
E 5
Lnocache3:
#endif
	rts

ENTRY(DCIU)
__DCIU:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040
	jne	LmotommuA		| no, skip
	/* XXX implement */
	rts
LmotommuA:
#endif
E 13
D 5
#if defined(HP360) || defined(HP370)
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
#endif
E 5
#if defined(HP320) || defined(HP350)
	tstl	_ectype			| got external VAC?
	jle	Lnocache4		| no, all done
D 5
	movl	_IObase+MMUUSTP,d0	| read the user STP
	movl	d0,_IObase+MMUUSTP	| write it back
E 5
I 5
	MMUADDR(a0)
	movl	a0@(MMUUSTP),d0		| read the user STP
	movl	d0,a0@(MMUUSTP)		| write it back
E 5
Lnocache4:
#endif
	rts

I 13
#if defined(HP380)
ENTRY(ICPL)
	movl	sp@(4),a0		| address
	.word	0xf488			| cinvl ic,a0@
	rts
ENTRY(ICPP)
	movl	sp@(4),a0		| address
	.word	0xf490			| cinvp ic,a0@
	rts
ENTRY(DCPL)
	movl	sp@(4),a0		| address
	.word	0xf448			| cinvl dc,a0@
	rts
ENTRY(DCPP)
	movl	sp@(4),a0		| address
	.word	0xf450			| cinvp dc,a0@
	rts
ENTRY(DCPA)
	.word	0xf458			| cinva dc
	rts
ENTRY(DCFL)
	movl	sp@(4),a0		| address
	.word	0xf468			| cpushl dc,a0@
	rts
ENTRY(DCFP)
	movl	sp@(4),a0		| address
	.word	0xf470			| cpushp dc,a0@
	rts
#endif

E 13
D 5
#if defined(HP370)
E 5
ENTRY(PCIA)
I 13
#if defined(HP380)
ENTRY(DCFA)
	cmpl	#-2,_mmutype		| 68040
	jne	LmotommuB		| no, skip
	.word	0xf478			| cpusha dc
	rts
LmotommuB:
#endif
E 13
I 5
#if defined(HP360) || defined(HP370)
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
E 5
	tstl	_ectype			| got external PAC?
	jge	Lnocache6		| no, all done
D 5
	movl	#_IObase+MMUCMD,a0	| MMU control reg
	andl	#~MMU_CEN,a0@		| disable cache
	orl	#MMU_CEN,a0@		| reenable cache
E 5
I 5
	MMUADDR(a0)
	andl	#~MMU_CEN,a0@(MMUCMD)	| disable cache in MMU control reg
	orl	#MMU_CEN,a0@(MMUCMD)	| reenable cache in MMU control reg
E 5
Lnocache6:
D 5
	rts
E 5
#endif
I 5
	rts
E 5

ENTRY(ecacheon)
	tstl	_ectype
	jeq	Lnocache7
D 5
	movl	#_IObase+MMUCMD,a0
	orl	#MMU_CEN,a0@
E 5
I 5
	MMUADDR(a0)
	orl	#MMU_CEN,a0@(MMUCMD)
E 5
Lnocache7:
	rts

ENTRY(ecacheoff)
	tstl	_ectype
	jeq	Lnocache8
D 5
	movl	#_IObase+MMUCMD,a0
	andl	#~MMU_CEN,a0@
E 5
I 5
	MMUADDR(a0)
	andl	#~MMU_CEN,a0@(MMUCMD)
E 5
Lnocache8:
	rts

I 10
/*
 * Get callers current SP value.
 * Note that simply taking the address of a local variable in a C function
 * doesn't work because callee saved registers may be outside the stack frame
 * defined by A6 (e.g. GCC generated code).
 */
	.globl	_getsp
_getsp:
	movl	sp,d0			| get current SP
	addql	#4,d0			| compensate for return address
	rts

E 10
	.globl	_getsfc, _getdfc
_getsfc:
	movc	sfc,d0
	rts
_getdfc:
	movc	dfc,d0
	rts

/*
 * Load a new user segment table pointer.
 */
ENTRY(loadustp)
D 13
#if defined(HP330) || defined(HP360) || defined(HP370)
E 13
I 13
#if defined(HP330) || defined(HP360) || defined(HP370) || defined(HP380)
E 13
	tstl	_mmutype		| HP MMU?
	jeq	Lhpmmu9			| yes, skip
	movl	sp@(4),d0		| new USTP
	moveq	#PGSHIFT,d1
	lsll	d1,d0			| convert to addr
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	LmotommuC		| no, skip
	.long	0x4e7b0806		| movc d0,urp
	rts
LmotommuC:
#endif
E 13
	lea	_protorp,a0		| CRP prototype
	movl	d0,a0@(4)		| stash USTP
D 5
	.long	0xf0104C00		| pmove a0@,crp
E 5
I 5
	pmove	a0@,crp			| load root pointer
E 5
	movl	#DC_CLEAR,d0
	movc	d0,cacr			| invalidate on-chip d-cache
	rts				|   since pmove flushes TLB
Lhpmmu9:
#endif
#if defined(HP320) || defined(HP350)
D 5
	movl	sp@(4),_IObase+MMUUSTP	| load a new USTP
E 5
I 5
	MMUADDR(a0)
	movl	sp@(4),a0@(MMUUSTP)	| load a new USTP
E 5
#endif
	rts

D 19
/*
 * Flush any hardware context associated with given USTP.
 * Only does something for HP330 where we must flush RPT
 * and ATC entries in PMMU.
 */
ENTRY(flushustp)
#if defined(HP330)
	tstl	_mmutype		| 68851 PMMU?
	jle	Lnot68851		| no, nothing to do
	movl	sp@(4),d0		| get USTP to flush
	moveq	#PGSHIFT,d1
	lsll	d1,d0			| convert to address
	movl	d0,_protorp+4		| stash USTP
D 5
	.long	0xf039a000,_protorp	| pflushr _protorp
E 5
I 5
	pflushr	_protorp		| flush RPT/TLB entries
E 5
Lnot68851:
#endif
	rts

E 19
ENTRY(ploadw)
#if defined(HP330) || defined(HP360) || defined(HP370)
	movl	sp@(4),a0		| address to load
D 5
	.long	0xf0102011		| pload #1,a0@
E 5
I 5
	ploadw	#1,a0@			| pre-load translation
E 5
#endif
	rts

/*
D 10
 * Set processor priority level calls.  Most could (should) be replaced
 * by inline asm expansions.  However, SPL0 and SPLX require special
 * handling.  If we are returning to the base processor priority (SPL0)
 * we need to check for our emulated software interrupts.
E 10
I 10
 * Set processor priority level calls.  Most are implemented with
 * inline asm expansions.  However, spl0 requires special handling
 * as we need to check for our emulated software interrupts.
E 10
 */

ENTRY(spl0)
	moveq	#0,d0
	movw	sr,d0			| get old SR for return
	movw	#PSL_LOWIPL,sr		| restore new SR
D 9
	jra	Lsplsir

ENTRY(splx)
	moveq	#0,d0
	movw	sr,d0			| get current SR for return
	movw	sp@(6),d1		| get new value
	movw	d1,sr			| restore new SR
	andw	#PSL_IPL7,d1		| mask all but PSL_IPL
	jne	Lspldone		| non-zero, all done
Lsplsir:
E 9
	tstb	_ssir			| software interrupt pending?
	jeq	Lspldone		| no, all done
	subql	#4,sp			| make room for RTE frame
	movl	sp@(4),sp@(2)		| position return address
	clrw	sp@(6)			| set frame type 0
	movw	#PSL_LOWIPL,sp@		| and new SR
	jra	Lgotsir			| go handle it
Lspldone:
D 9
	rts

ALTENTRY(splsoftclock, _spl1)
ALTENTRY(splnet, _spl1)
ENTRY(spl1)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL1,sr
	rts

ENTRY(spl2)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL2,sr
	rts

ENTRY(spl3)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL3,sr
	rts

ENTRY(spl4)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL4,sr
	rts

ALTENTRY(splimp, _spl5)
ALTENTRY(splbio, _spl5)
ALTENTRY(spltty, _spl5)
ENTRY(spl5)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL5,sr
	rts

ALTENTRY(splclock, _spl6)
ENTRY(spl6)
	moveq	#0,d0
	movw	sr,d0
	movw	#SPL6,sr
	rts

ALTENTRY(splhigh, _spl7)
ENTRY(spl7)
	moveq	#0,d0
	movw	sr,d0
	movw	#PSL_HIGHIPL,sr
E 9
	rts

D 10
#ifdef GPROF
/*
 * Special versions of splhigh and splx called by mcount().
 * Note that __splx does not check for software interrupts.
 */
	.globl	__splhigh, __splx
__splhigh:
	moveq	#0,d0
	movw	sr,d0
	movw	#PSL_HIGHIPL,sr
	rts

__splx:
	moveq	#0,d0
	movw	sr,d0			| get current SR for return
	movw	sp@(6),d1		| get new value
	movw	d1,sr			| restore new SR
	rts
#endif

E 10
ENTRY(_insque)
	movw	sr,d0
	movw	#PSL_HIGHIPL,sr		| atomic
	movl	sp@(8),a0		| where to insert (after)
	movl	sp@(4),a1		| element to insert (e)
	movl	a0@,a1@			| e->next = after->next
	movl	a0,a1@(4)		| e->prev = after
	movl	a1,a0@			| after->next = e
	movl	a1@,a0
	movl	a1,a0@(4)		| e->next->prev = e
	movw	d0,sr
	rts

ENTRY(_remque)
	movw	sr,d0
	movw	#PSL_HIGHIPL,sr		| atomic
	movl	sp@(4),a0		| element to remove (e)
	movl	a0@,a1
	movl	a0@(4),a0
	movl	a0,a1@(4)		| e->next->prev = e->prev
	movl	a1,a0@			| e->prev->next = e->next
	movw	d0,sr
	rts

I 5
/*
 * bzero(addr, count)
 */
E 5
ALTENTRY(blkclr, _bzero)
ENTRY(bzero)
D 5
	movl	sp@(4),a0
	movl	sp@(8),d0
	jeq	1$
E 5
I 5
	movl	sp@(4),a0	| address
	movl	sp@(8),d0	| count
	jeq	Lbzdone		| if zero, nothing to do
E 5
	movl	a0,d1
D 5
	btst	#0,d1
	jeq	2$
	clrb	a0@+
	subql	#1,d0
	jeq	1$
2$:
E 5
I 5
	btst	#0,d1		| address odd?
	jeq	Lbzeven		| no, can copy words
	clrb	a0@+		| yes, zero byte to get to even boundary
	subql	#1,d0		| decrement count
	jeq	Lbzdone		| none left, all done
Lbzeven:
E 5
	movl	d0,d1
	andl	#31,d0
D 5
	lsrl	#5,d1
	jeq	3$
4$:
E 5
I 5
	lsrl	#5,d1		| convert count to 8*longword count
	jeq	Lbzbyte		| no such blocks, zero byte at a time
Lbzloop:
E 5
	clrl	a0@+; clrl	a0@+; clrl	a0@+; clrl	a0@+;
	clrl	a0@+; clrl	a0@+; clrl	a0@+; clrl	a0@+;
D 5
	subql	#1,d1
	jne	4$
	tstl	d0
	jeq	1$
3$:
E 5
I 5
	subql	#1,d1		| one more block zeroed
	jne	Lbzloop		| more to go, do it
	tstl	d0		| partial block left?
	jeq	Lbzdone		| no, all done
Lbzbyte:
E 5
	clrb	a0@+
D 5
	subql	#1,d0
	jne	3$
1$:
E 5
I 5
	subql	#1,d0		| one more byte cleared
	jne	Lbzbyte		| more to go, do it
Lbzdone:
E 5
	rts

/*
 * strlen(str)
 */
ENTRY(strlen)
	moveq	#-1,d0
	movl	sp@(4),a0	| string
Lslloop:
	addql	#1,d0		| increment count
	tstb	a0@+		| null?
	jne	Lslloop		| no, keep going
	rts

/*
 * bcmp(s1, s2, len)
 *
 * WARNING!  This guy only works with counts up to 64K
 */
ENTRY(bcmp)
	movl	sp@(4),a0		| string 1
	movl	sp@(8),a1		| string 2
	moveq	#0,d0
	movw	sp@(14),d0		| length
	jeq	Lcmpdone		| if zero, nothing to do
	subqw	#1,d0			| set up for DBcc loop
Lcmploop:
	cmpmb	a0@+,a1@+		| equal?
	dbne	d0,Lcmploop		| yes, keep going
	addqw	#1,d0			| +1 gives zero on match
Lcmpdone:
	rts
	
/*
 * {ov}bcopy(from, to, len)
 *
 * Works for counts up to 128K.
 */
ALTENTRY(ovbcopy, _bcopy)
ENTRY(bcopy)
	movl	sp@(12),d0		| get count
	jeq	Lcpyexit		| if zero, return
	movl	sp@(4),a0		| src address
	movl	sp@(8),a1		| dest address
	cmpl	a1,a0			| src before dest?
	jlt	Lcpyback		| yes, copy backwards (avoids overlap)
	movl	a0,d1
	btst	#0,d1			| src address odd?
	jeq	Lcfeven			| no, go check dest
	movb	a0@+,a1@+		| yes, copy a byte
	subql	#1,d0			| update count
	jeq	Lcpyexit		| exit if done
Lcfeven:
	movl	a1,d1
	btst	#0,d1			| dest address odd?
	jne	Lcfbyte			| yes, must copy by bytes
	movl	d0,d1			| no, get count
	lsrl	#2,d1			| convert to longwords
	jeq	Lcfbyte			| no longwords, copy bytes
	subql	#1,d1			| set up for dbf
Lcflloop:
	movl	a0@+,a1@+		| copy longwords
	dbf	d1,Lcflloop		| til done
	andl	#3,d0			| get remaining count
	jeq	Lcpyexit		| done if none
Lcfbyte:
	subql	#1,d0			| set up for dbf
Lcfbloop:
	movb	a0@+,a1@+		| copy bytes
	dbf	d0,Lcfbloop		| til done
Lcpyexit:
	rts
Lcpyback:
	addl	d0,a0			| add count to src
	addl	d0,a1			| add count to dest
	movl	a0,d1
	btst	#0,d1			| src address odd?
	jeq	Lcbeven			| no, go check dest
	movb	a0@-,a1@-		| yes, copy a byte
	subql	#1,d0			| update count
	jeq	Lcpyexit		| exit if done
Lcbeven:
	movl	a1,d1
	btst	#0,d1			| dest address odd?
	jne	Lcbbyte			| yes, must copy by bytes
	movl	d0,d1			| no, get count
	lsrl	#2,d1			| convert to longwords
	jeq	Lcbbyte			| no longwords, copy bytes
	subql	#1,d1			| set up for dbf
Lcblloop:
	movl	a0@-,a1@-		| copy longwords
	dbf	d1,Lcblloop		| til done
	andl	#3,d0			| get remaining count
	jeq	Lcpyexit		| done if none
Lcbbyte:
	subql	#1,d0			| set up for dbf
Lcbbloop:
	movb	a0@-,a1@-		| copy bytes
	dbf	d0,Lcbbloop		| til done
	rts

/*
 * Emulate fancy VAX string operations:
 *	scanc(count, startc, table, mask)
 *	skpc(mask, count, startc)
 *	locc(mask, count, startc)
 */
ENTRY(scanc)
	movl	sp@(4),d0	| get length
	jeq	Lscdone		| nothing to do, return
	movl	sp@(8),a0	| start of scan
	movl	sp@(12),a1	| table to compare with
	movb	sp@(19),d1	| and mask to use
	movw	d2,sp@-		| need a scratch register
	clrw	d2		| clear it out
	subqw	#1,d0		| adjust for dbra
Lscloop:
	movb	a0@+,d2		| get character
	movb	a1@(0,d2:w),d2	| get table entry
	andb	d1,d2		| mask it
	dbne	d0,Lscloop	| keep going til no more or non-zero
	addqw	#1,d0		| overshot by one
	movw	sp@+,d2		| restore scratch
Lscdone:
	rts

ENTRY(skpc)
	movl	sp@(8),d0	| get length
	jeq	Lskdone		| nothing to do, return
	movb	sp@(7),d1	| mask to use
	movl	sp@(12),a0	| where to start
	subqw	#1,d0		| adjust for dbcc
Lskloop:
	cmpb	a0@+,d1		| compate with mask
	dbne	d0,Lskloop	| keep going til no more or zero
	addqw	#1,d0		| overshot by one
Lskdone:
	rts

ENTRY(locc)
	movl	sp@(8),d0	| get length
	jeq	Llcdone		| nothing to do, return
	movb	sp@(7),d1	| mask to use
	movl	sp@(12),a0	| where to start
	subqw	#1,d0		| adjust for dbcc
Llcloop:
	cmpb	a0@+,d1		| compate with mask
	dbeq	d0,Llcloop	| keep going til no more or non-zero
	addqw	#1,d0		| overshot by one
Llcdone:
	rts

/*
 * Emulate VAX FFS (find first set) instruction.
 */
ENTRY(ffs)
	moveq	#-1,d0
	movl	sp@(4),d1
D 5
	beq	Lffsdone
E 5
I 5
	jeq	Lffsdone
E 5
Lffsloop:
	addql	#1,d0
	btst	d0,d1
D 5
	beq	Lffsloop
E 5
I 5
	jeq	Lffsloop
E 5
Lffsdone:
	addql	#1,d0
	rts

#ifdef FPCOPROC
/*
 * Save and restore 68881 state.
 * Pretty awful looking since our assembler does not
 * recognize FP mnemonics.
 */
ENTRY(m68881_save)
	movl	sp@(4),a0		| save area pointer
D 5
	.word	0xf310			| fsave a0@
E 5
I 5
	fsave	a0@			| save state
E 5
	tstb	a0@			| null state frame?
	jeq	Lm68881sdone		| yes, all done
D 5
	.word	0xf228,0xf0ff,0x00d8	| fmovem fp0-fp7,a0@(216)
	.word	0xf228,0xbc00,0x0138	| fmovem fpcr/fpsr/fpiar,a0@(312)
E 5
I 5
	fmovem fp0-fp7,a0@(216)		| save FP general registers
	fmovem fpcr/fpsr/fpi,a0@(312)	| save FP control registers
E 5
Lm68881sdone:
	rts

ENTRY(m68881_restore)
	movl	sp@(4),a0		| save area pointer
	tstb	a0@			| null state frame?
	jeq	Lm68881rdone		| yes, easy
D 5
	.word	0xf228,0x9c00,0x0138	| fmovem a0@(312),fpcr/fpsr/fpiar
	.word	0xf228,0xd0ff,0x00d8	| fmovem a0@(216),fp0-fp7
E 5
I 5
	fmovem	a0@(312),fpcr/fpsr/fpi	| restore FP control registers
	fmovem	a0@(216),fp0-fp7	| restore FP general registers
E 5
Lm68881rdone:
D 5
	.word	0xf350			| frestore a0@
E 5
I 5
	frestore a0@			| restore state
E 5
	rts
#endif

/*
 * Handle the nitty-gritty of rebooting the machine.
 * Basically we just turn off the MMU and jump to the appropriate ROM routine.
 * Note that we must be running in an address range that is mapped one-to-one
 * logical to physical so that the PC is still valid immediately after the MMU
D 5
 * is turned off.
E 5
I 5
 * is turned off.  We have conveniently mapped the last page of physical
 * memory this way.
E 5
 */
	.globl	_doboot
_doboot:
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jeq	Lnocache5		| yes, skip
#endif
E 13
	movl	#CACHE_OFF,d0
	movc	d0,cacr			| disable on-chip cache(s)
#if defined(HP320) || defined(HP350) || defined(HP370)
	tstl	_ectype
	jeq	Lnocache5
D 5
	andl	#~MMU_CEN,_IObase+MMUCMD| disable external cache
E 5
I 5
	MMUADDR(a0)
	andl	#~MMU_CEN,a0@(MMUCMD)	| disable external cache
E 5
D 13
Lnocache5:
E 13
#endif
I 13
Lnocache5:
E 13
D 5
/* one-to-one map the last page of memory */
	movl	#MAXADDR,d0		| last page of RAM used to pass params
	orl	#PG_RW+PG_V,d0		| create a PTE
	movl	d0,_mmap		|   to access that page
	jbsr	_TBIA			| invalidate TLB
	movl	#MAXADDR,d0		| last page of RAM is also used
	orl	#SG_RW+SG_V,d0		|   as the page table for itself
	movl	d0,eSysseg-4		|   (ok since it needs only last word)
	movl	_vmmap+NBPG-4,d2	| save old contents
	movl	_mmap,_vmmap+NBPG-4	| store PTE in new page table
	jbsr	_TBIA			| invalidate again
	lea	MAXADDR,a0		| can now access last page
E 5
I 5
	lea	MAXADDR,a0		| last page of physical memory
E 5
	movl	_boothowto,a0@+		| store howto
	movl	_bootdev,a0@+		| and devtype
	lea	Lbootcode,a1		| start of boot code
	lea	Lebootcode,a3		| end of boot code
Lbootcopy:
	movw	a1@+,a0@+		| copy a word
	cmpl	a3,a1			| done yet?
	jcs	Lbootcopy		| no, keep going
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	LmotommuE		| no, skip
	.word	0xf4f8			| cpusha bc
LmotommuE:
#endif
E 13
	jmp	MAXADDR+8		| jump to last page

Lbootcode:
	lea	MAXADDR+0x800,sp	| physical SP in case of NMI
I 13
#if defined(HP380)
	cmpl	#-2,_mmutype		| 68040?
	jne	LmotommuF		| no, skip
	movl	#0,d0
	movc	d0,cacr			| caches off
	.long	0x4e7b0003		| movc d0,tc
	movl	d2,MAXADDR+NBPG-4	| restore old high page contents
	jmp	0x1A4			| goto REQ_REBOOT
LmotommuF:
#endif
E 13
#if defined(HP330) || defined(HP360) || defined(HP370)
	tstl	_mmutype		| HP MMU?
	jeq	LhpmmuB			| yes, skip
	movl	#0,a0@			| value for pmove to TC (turn off MMU)
D 5
	.long	0xf0104000		| pmove a0@,tc
	movl	d2,MAXADDR+NBPG-4	| restore old high page contents
E 5
I 5
	pmove	a0@,tc			| disable MMU
E 5
	jmp	0x1A4			| goto REQ_REBOOT
LhpmmuB:
#endif
#if defined(HP320) || defined(HP350)
D 5
	movl	#0xFFFF0000,_IObase+MMUCMD	| totally disable MMU
E 5
I 5
	MMUADDR(a0)
	movl	#0xFFFF0000,a0@(MMUCMD)	| totally disable MMU
E 5
	movl	d2,MAXADDR+NBPG-4	| restore old high page contents
	jmp	0x1A4			| goto REQ_REBOOT
#endif
Lebootcode:

	.data
D 19
	.space	NBPG
tmpstk:
E 19
	.globl	_machineid
_machineid:
	.long	0		| default to 320
	.globl	_mmutype,_protorp
_mmutype:
	.long	0		| default to HP MMU
_protorp:
	.long	0,0		| prototype root pointer
	.globl	_ectype
_ectype:
	.long	0		| external cache type, default to none
I 5
	.globl	_internalhpib
_internalhpib:
	.long	1		| has internal HP-IB, default to yes
E 5
	.globl	_cold
_cold:
	.long	1		| cold start flag
I 13
	.globl	_want_resched
_want_resched:
	.long	0
E 13
I 5
D 10
	.globl	_DIObase, _CLKbase, _MMUbase, _proc0paddr
E 10
I 10
	.globl	_intiobase, _intiolimit, _extiobase, _CLKbase, _MMUbase
	.globl	_proc0paddr
E 10
_proc0paddr:
	.long	0		| KVA of proc0 u-area
D 10
_DIObase:
	.long	0		| KVA of base of IO space
E 10
I 10
_intiobase:
	.long	0		| KVA of base of internal IO space
_intiolimit:
	.long	0		| KVA of end of internal IO space
_extiobase:
	.long	0		| KVA of base of external IO space
E 10
_CLKbase:
	.long	0		| KVA of base of clock registers
_MMUbase:
	.long	0		| KVA of base of HP MMU registers
I 21
#ifdef USELEDS
heartbeat:
	.long	0		| clock ticks since last pulse of heartbeat
#endif
E 21
E 5
#ifdef DEBUG
D 5
	.globl	fullflush
fullflush:
E 5
I 5
	.globl	fulltflush, fullcflush
fulltflush:
	.long	0
fullcflush:
E 5
D 19
	.long	0
	.globl	timebomb
timebomb:
E 19
	.long	0
I 13
#endif
#ifdef HPFPLIB
/*
 * Undefined symbols from hpux_float.o:
 *
 * kdb_printf:	A kernel debugger print routine, we just use printf instead.
 * processor:	HP-UX equiv. of machineid, set to 3 if it is a 68040.
 * u:		Ye ole u-area.  The code wants to grab the first longword
 *		indirect off of that and clear the 0x40000 bit there.
 *		Oddly enough this was incorrect even in HP-UX!
 * runrun:	Old name for want_resched.
 */
	.globl	_kdb_printf,_processor,_u,_runrun
_kdb_printf:
	.long	_printf
_processor:
	.long	0
_u:
	.long	.+4
	.long	0
	.set	_runrun,_want_resched
E 13
#endif
/* interrupt counters */
	.globl	_intrcnt,_eintrcnt,_intrnames,_eintrnames
_intrnames:
	.asciz	"spur"
	.asciz	"hil"
	.asciz	"lev2"
	.asciz	"lev3"
	.asciz	"lev4"
	.asciz	"lev5"
	.asciz	"dma"
	.asciz	"clock"
D 16
#ifdef PROFTIMER
	.asciz  "pclock"
#endif
E 16
I 16
	.asciz  "statclock"
E 16
	.asciz	"nmi"
_eintrnames:
	.even
_intrcnt:
D 16
#ifdef PROFTIMER
E 16
	.long	0,0,0,0,0,0,0,0,0,0
D 16
#else
	.long	0,0,0,0,0,0,0,0,0
#endif
E 16
_eintrcnt:
E 1
