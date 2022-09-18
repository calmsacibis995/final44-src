/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie-Mellon University
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	locore.s,v $
 * Revision 2.13  93/02/01  09:53:42  danner
 * 	Cpp fixups.
 * 
 * Revision 2.12  93/01/14  18:00:27  danner
 * 	Fixed ansi cpp complaints.
 * 	[93/01/13            danner]
 * 
 * Revision 2.11  92/01/03  20:32:58  dbg
 * 	Remove fixed lower bound on emulated system call number.
 * 	[91/11/01            dbg]
 * 
 * Revision 2.10  91/07/31  18:19:07  dbg
 * 	Fix switch_to_shutdown_context.
 * 	[91/07/30  17:23:35  dbg]
 * 
 * Revision 2.9  91/06/20  11:29:50  rvb
 * 	funny thing: before you could not build STD+BI because ka650.h was necessary to define ssc
 * 
 * Revision 2.8  91/06/19  12:01:15  rvb
 * 	Support for VaxStation 3100: new processor number added to tables
 * 	and ka42_<> interrupt trampoline.
 * 	[91/06/04            rvb]
 * 
 * Revision 2.7  91/05/08  13:19:04  dbg
 * 	Include rpb, scb, ubvec, ubglue explicitly.
 * 	[91/04/23            dbg]
 * 
 * 	Move initialization code to vax_init.s.
 * 	[91/04/11            dbg]
 * 
 * 	Move br and cvec to memory.
 * 	[91/03/26            dbg]
 * 
 * 	Stack switching support.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.6  91/01/08  16:41:31  rpd
 * 	Updated for new mach_trap_table layout.
 * 	[91/01/06            rpd]
 * 
 * Revision 2.5  90/05/29  18:38:24  rwd
 * 	Add code to allow syscalls up to 11 arguments.
 * 	[90/05/23            rwd]
 * 
 * Revision 2.4  90/05/03  15:51:44  dbg
 * 	Patch out code to route access violations thru emulator - it's
 * 	till broken.
 * 	[90/04/12            dbg]
 * 
 * Revision 2.3  90/01/11  11:45:53  dbg
 * 	Restore code to route access violations thru emulator.
 * 	[89/12/21            dbg]
 * 
 * 	Export start_lock.
 * 	[89/12/01            dbg]
 * 
 * Revision 2.2  89/08/31  16:19:53  rwd
 * 	Added copyright to file by dbg.  Changed syscall emulation to
 * 	push syscall number on stack.
 * 	[89/08/23            rwd]
 * 
 *
 */
/*
 * start on a new locore.s
 */
#define	LOCORE	1

#include <mach_kdb.h>
#include <emul.h>
#include <mach_load.h>
#include <mach_mpm.h>

#include <bi.h>
#include <dz.h>
#include <mba.h>
#include <ni.h>
#include <ps.h>
#include <ra.h>
#include <uba.h>
#include <uu.h>

#include <vax/asm.h>
#include <vax/ast.h>
#include <vax/clock.h>
#include <vax/cpu_data.h>
#include <vax/mtpr.h>
#include <vax/psl.h>
#include <vax/pte.h>
#include <vax/trap.h>
#include <mach/vax/vm_param.h>

#include <assym.s>

	.set	HIGH,0x1c	# mask for most disables; allows WEI
	.set	BLOCK,0x1f	# mask for total disable
	.set	MCKVEC,4	# offset into SCB for machine check vector
	.set	NBPG,512	# bytes per VAX page
	.set	PGSHIFT,9

/*
 * RPB and SCB must be at the start of the load file.
 */
#include <vax/rpb.s>
#include <vax/scb.s>
#include <ubvec.s>

#define	COUNT(x)

	.globl	_start_lock
_start_lock:			# squeeze this in here (R/W text)
	.long	0
	.globl	_intstack
_intstack:
	.space	INTSTACK_SIZE
	.globl	_eintstack
_eintstack:

	.globl	_start_text
_start_text:
	.text
	.align	2

#ifdef	__STDC__
#define	SCBVEC(name)	.align 2; .globl _X ## name; _X ## name
#else
#define	SCBVEC(name)	.align 2; .globl _X/**/name; _X/**/name
#endif	/* __STDC__ */
#define	PUSHR		pushr	$0x3f
#define	POPR		popr	$0x3f
#define	MSG(msg)	.data; 1: .asciz msg; .text
#define	PRINTF(n,msg)	pushab 1f; calls $ n+1,_printf; MSG(msg)
#define	PANIC(msg)	pushab 1f; calls $1,_panic; MSG(msg)

#define	TIM_PUSHR(n)	PUSHR
#define	TSREI_POPR	POPR; rei
#define	TIM(n)
#define	ENT_DATA	4+6*4
#define	TSREI		rei
#define	PROLOGUE	2

/*
 * Fault recovery.
 */
#define	RECOVER_TABLE_START	\
	.text	2		;\
	.globl	_recover_table	;\
_recover_table:			;\
	.text

#define	RECOVER(addr)		\
	.text	2		;\
	.long	9f		;\
	.long	addr		;\
	.text			;\
9:

#define	RECOVER_TABLE_END		\
	.text	2			;\
	.globl	_recover_table_end	;\
_recover_table_end:			;\
	.text

/*
 * Allocate recovery table.
 */
	RECOVER_TABLE_START

/*
 * Print stray interrupts.
 */
	.align 2
	.globl _Yprint
_Yprint:
	subl2	$_Ystray+8,(sp)
	ashl	$-1,(sp),(sp)
	mfpr	$ IPL,-(sp)
	PRINTF(2,"Interrupt at IPL %x SCB offset %x\n") ;
	POPR
	rei

	.align 2
	.globl _Ystray
_Ystray:

#define YY PUSHR; jsb _Yprint
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;

	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;
	YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY; YY;YY;YY;YY;

	.globl	_gimmeabreak
	.globl	_Bpt
_gimmeabreak:
_Bpt:
	.word	0xfff			# save all registers
	bispsw	$(PSL_T)		# set trace bit to trap to debugger
	ret

/*
 * Basic SCB vectors
 */

SCBVEC(machcheck):
	PUSHR
	pushab	6*4(sp)			# point to parameters
	calls	$1,_machinecheck	# call C code
	POPR
	addl2	(sp)+,sp		# clean parameters from stack
	rei

SCBVEC(kspnotval):
	PUSHR
	PANIC("KSP not valid")

SCBVEC(powfail):
	halt

SCBVEC(chme):
SCBVEC(chms):
SCBVEC(chmu):
	PUSHR
	PANIC("CHM? in kernel")

SCBVEC(stray):
	TIM_PUSHR(0)
	PRINTF(0, "stray scb interrupt\n")
	TSREI_POPR

SCBVEC(nexzvec):
	TIM_PUSHR(0)
	mfpr	$ IPL,-(sp)
	PRINTF(1, "nexus stray interrupt at ipl %x\n")
	TSREI_POPR

SCBVEC(cmrd):
	TIM_PUSHR(0)
	calls	$0,_memerr
	TSREI_POPR

SCBVEC(wtime):
	pushr	$0x3fff				/* everything */

	mfpr	$ USP, -(sp)
	mfpr	$ SSP, -(sp)
	mfpr	$ ESP, -(sp)
	mfpr	$ KSP, -(sp)

	subl2	$12, sp
	movq	4*21(sp), (sp)			/* pc/psl */
	moval	4*3(sp), 8(sp)			/* pcb !! */
	calls	$3, _wtime
	addl2	$4*4, sp
	popr	$0x3fff
	rei

#if	VAX650
SCBVEC(ssc0clock):
	TIM_PUSHR(0)
	mtpr	$0x16, $ IPL
	movl	_ssc,r3
	movl	$ ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,SSC_TCR0(r3)
	brb	hardclock_common
#endif	VAX650

#if	VAX6200 && !VAX650
SCBVEC(ssc0clock):
	TIM_PUSHR(0)
	mtpr	$0x16, $ IPL
	movl	_ka62a_ssc,r3
	movl	$ ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,SSC_TCR0(r3)
	brb	hardclock_common
#endif	VAX6200 && !VAX650

SCBVEC(hardclock):
	TIM_PUSHR(0)
	mtpr $ ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,$ ICCS

hardclock_common:
#if NPS > 0
	pushl	ENT_DATA(sp); pushl ENT_DATA(sp);
	calls	$2,_psextsync
#endif
	movl	ENT_DATA(sp),r0		# get psl
	bitl	$ PSL_IPL,r0		# at base priority?
	bneq	0f
	pushl	$1			# IPL == 0: base priority
	brb	1f
0:	pushl	$0
1:	cmpzv	$24,$2,r0,$3		# in user mode?
	bneq	0f
	pushl	$1			# (ps & PSL_CURMOD) == PSL_CURMOD
	brb	1f
0:	pushl	$0
1:	pushl	_tick			# push usec per tick
	calls	$3,_clock_interrupt	# handle clock interrupt
	TSREI_POPR

SCBVEC(softclock):
	TIM_PUSHR(0)
	calls	$0,_softclock
	TSREI_POPR

SCBVEC(netintr):
	rei				# not used yet

/*
 * Trap and fault vectors
 */

#define	TRAP1(a)	pushl $0; pushl $0; pushl $ a; jbr alltraps
#define	TRAP1X(a)		  pushl $0; pushl $ a; jbr alltraps
#define	TRAP2(a,b)	pushl $0; pushl $ b; pushl $ a; jbr alltraps
#define	TRAP2X(a,b)		  pushl $ b; pushl $ a; jbr alltraps

/*
 * ASTs are only taken from user mode, and trap directly
 * to ast_taken.
 */
SCBVEC(astflt):
	TIM(0)
	clrq	-(sp)			# null code/subcode
	pushl	$0			# null exception
	pushr	$0x3fff			# save r0..r13
	movl	sp,r11			# point to user registers
	mfpr	$ ESP,sp		# switch to kernel stack
	pushl	r11			# save user register pointer
	mtpr	$ HIGH,$ IPL		# splsched()
	mtpr	$ VAX_AST_NONE,$ ASTLVL	# turn off ASTs
	calls	$0,_ast_taken		# take the AST
	movl	(sp),sp			# restore user stack pointer
	popr	$0x3fff			# restore r0..r13
	addl2	$12,sp			# pop exc/code/subcode
	rei				# return

SCBVEC(privinflt):
	TIM(0)
#if	NEMUL > 0
	/*
	 *  Some of the more baroque instructions are not implemented on the
	 *  MicroVax and must be emulated in software.  If a process attempts
	 *  to use one, it will receive a Reserved/Privileged instruction
	 *  fault which will transfer here in kernel mode.  The emulation
	 *  routine (from ULTRIX-32) is then called to determine whether or
	 *  not the faulting instruction can be emulated.  If it can be
	 *  emulated, then control stays permanently in the emulator
	 *  which first switches back to the previous mode before proceeding
	 *  with the emulation. 
 	 *
	 *  Note:  We could make this check dependent on the CPU type so that
	 *  the emulation code only gets called on a MicroVax but this isn't
	 *  strictly necessary since the emulation code is going to reject any
	 *  instructions it doesn't understand back here anyway.  Thus the
	 *  fault path on the other CPU's is slightly longer but presumably
	 *  less frequent.  We can always just recompile without the "emul"
	 *  pseudo-device if it really matters in any case.
	 */
	jmp	vax$opcdec	# Transfer into ULTRIX-32M emulation handler

	/*
	 *  The emulation handler will transfer control back here if the
	 *  faulting instruction can/should not be emulated in which case we
	 *  simply proceed with the fault as normal.
	 */
	.globl	_Xprivinflt1
_Xprivinflt1:
	/*
	 *  The VMS exception handling facility used by the floating point
	 *  emulation may need to switch back into kernel mode to process an
	 *  exception (sorry, I'm not exactly sure why or if we even use it
	 *  without ULTRIX).  To do this it executes a HALT instruction at the
	 *  special halt address checked below.  When a HALT is seen at this
	 *  address, control is simply transferred back to the exception
	 *  handler in kernel mode at the special continue address.
	 */
	cmpl	$ vax$special_halt,(sp)
	bneq	1f			# not special
	addl2	$(2*4),sp		# pop the fault PC/PSL parameters
	jmp	vax$special_cont	#  before continuing
1:
	/*
	 *  What do you know, a REAL reserved/privileged instruction fault!
	 */
#endif	NEMUL > 0
	TRAP2(EXC_BAD_INSTRUCTION,EXC_VAX_PRIVINST)

SCBVEC(resopflt):
	TIM(0)
	TRAP2(EXC_BAD_INSTRUCTION,EXC_VAX_RESOPND)

SCBVEC(resadflt):
	TIM(0)
	TRAP2(EXC_BAD_INSTRUCTION,EXC_VAX_RESADDR)

SCBVEC(arithtrap):
	TIM(1)
	TRAP1X(EXC_ARITHMETIC)	# and take as arithmetic trap

SCBVEC(bptflt):
	TIM(0)
	TRAP2(EXC_BREAKPOINT,EXC_VAX_BPT)

SCBVEC(tracep):
	TIM(0)
	TRAP2(EXC_BREAKPOINT,EXC_VAX_TRACE)

SCBVEC(kdbintr):
#if	MACH_KDB
	TIM(0)
	TRAP1(T_KDB_ENTRY)
#else
	rei
#endif	MACH_KDB

SCBVEC(compatflt):
	TIM(1)
	TRAP2X(EXC_BAD_INSTRUCTION,EXC_VAX_COMPAT)

SCBVEC(xfcflt):
	TIM(1)
	TRAP2(EXC_EMULATION,0)

SCBVEC(protflt): 
SCBVEC(transflt): 
	TIM(2)
#if	NEMUL > 0
	/*
	 *  If we take a protection fault while the PC is in the instruction
	 *  emulation code, then it should be fielded by its fault handler
	 *  rather than directly by us.  This way, the handler can preserve the
	 *  appearance that the original instruction which was being emulated
	 *  was the one to receive the fault rather than its own code.
	 */
	brb	1f			# it`s broken!

	cmpl	8(sp),$ vax$emul_begin
	blssu	1f
	cmpl	8(sp),$ vax$emul_end
	bgequ	1f
	jmp	exe$acviolat		# fault was in the emulation code
1:
	/*
	 *  The protection fault handler in the emulation code will transfer
	 *  control back here when ready to proceed with the fault after
	 *  establishing the proper stack and register context as if the
	 *  fault had indeed occurred in the emulated instruction.
	 */
	.globl	_Xprotflt1
_Xprotflt1:
#endif	NEMUL > 0
#if	VAX8800
	/*
	 *	The VAX-8800 seems to have a bug... when a fault is caused
	 *	by an invalid system PTE the write intent bit can be wrong.
	 *	So, if the reason for the fault is an invalid system PTE,
	 *	then assume a read fault, this may generate an extra fault
	 *	but will produce correct faults (a write fault will only
	 *	occur if the system PTE is already available).
	 */
	cmpl	_cpu,$ VAX_8800		# are we an 8800?
	bneq	0f			# no, forget hack.
	bitl	$2,(sp)			# PTE access?
	beql	0f			# no, do normal handling
	addl2	$4,sp			# yes, pop value off stack
	brb	1f
0:
#endif	VAX8800
	bitl	$4,(sp)+		# check for modify attempt
	beql	1f
	pushl	$ (VM_PROT_READ|VM_PROT_WRITE)
	brb	2f
1:	pushl	$ VM_PROT_READ
2:	pushl	$ EXC_BAD_ACCESS

/*
 * Must check for fault in syscall_emul sequence, since that code
 * is using pcb stack, not kernel stack.
 */
	cmpl	12(sp),$sys_emul_1	# in syscall_emul sequence?
	beql	0f
	cmpl	12(sp),$sys_emul_2
	bneq	alltraps		# normal trap if not
0:	jmp	sys_emul_fault		# rearrange stack if so

/*
 * All traps (user or kernel) enter here with:
 * sp->	exception
 *	code
 *	subcode
 *	pc
 *	psl
 *
 * Save registers on stack, then switch to real kernel stack
 * if trap from user mode.
 */
alltraps:
	pushr	$0x3fff			# save r0..r13
	cmpzv	$24,$2,R_PSL(sp),$3	# user mode trap?
	bneq	trap_kernel		# if so:

	movl	sp,r11			#    point to registers
	mfpr	$ ESP,sp		#    switch to real kernel stack
	pushl	r11			#    save pointer to user registers
trap_user:
	pushl	r11			#    pass regs as argument
	calls	$1,user_trap_call	#    call user trap
	movl	(sp),sp			#    restore PCB stack pointer
	jmp	trap_return		#    return from trap

trap_kernel:				# trap from kernel mode:
	pushl	sp			#    pass regs as argument
	calls	$1,kernel_trap_call	#    call kernel trap

trap_return:
	popr	$0x3fff			# restore r0..r13
	addl2	$12,sp			# pop exc/code/subcode
	rei				# return

user_trap_call:
	.word	0			# registers already saved
	jmp	_user_trap+2		# call user_trap(regs)

kernel_trap_call:
	.word	0			# registers already saved
	jmp	_kernel_trap+2		# call kernel_trap(regs)


/*
 * System call trap (chmk).
 * System call number is on stack top.
 */
SCBVEC(syscall):
	TIM(1)

	/*
	 * Check for emulated system calls.
	 */
	movq	r0,-(sp)		# save some registers
syscall_restart:
	mfpr	$ SSP,r1		# get the thread
	movl	THREAD_TASK(r1),r1	# get the task
	movl	EML_DISPATCH(r1),r1	# get the emulation table
	beql	syscall_native		# none - native system call
	subl3	DISP_MIN(r1),8(sp),r0	# get displacement into syscall
					# vector table
	blss	syscall_native		# too low - native system call
	cmpl	r0,DISP_COUNT(r1)	# check range
	bgtr	syscall_native		# too high - native system call
	movl	DISP_VECTOR(r1)[r0],r1	# get the emulation vector
	beql	syscall_native
	jmp	syscall_emul		# emulated system call if not zero

syscall_native:
	movq	(sp),r0			# restore registers, leaving space for
					# exc/code

	/*
	 * Save registers on stack.  Make it look like trap's
	 * save area, so that the same get/put status code works
	 * for both.
	 */
	pushr	$0x3fff			# save r0..r13
	movl	sp,r11			# save user register pointer
	mfpr	$ ESP,sp		# switch to kernel stack
	pushl	r11			# save pointer to user registers

	mnegl	R_SUBCODE(r11),r0	# get system call number
	blss	mach_call_range		# error if it was positive
	cmpl	r0,_mach_trap_count	# check syscall table bounds
	bgtr	mach_call_range		# error if out of range

	ashl	$4,r0,r0		# trap table is 16 bytes/entry
	movq	_mach_trap_table(r0),r0	# move argument count to r0,
					# procedure address to r1
	tstl	r0			# any arguments?
	beql	mach_call_call		# skip copy if not

	moval	4-1(ap)[r0],r2		# get last byte of argument list
	blss	mach_call_addr		# error if in system space
	incl	r2			# correct for pushes

	caseb	r0,$1,$10		# switch on number of arguments
0:	.word	1f-0b
	.word	2f-0b
	.word	3f-0b
	.word	4f-0b
	.word	5f-0b
	.word	6f-0b
	.word	7f-0b
	.word	8f-0b
	.word	L09-0b
	.word	L10-0b
	.word	L11-0b
	RECOVER(mach_call_addr)
L11:	pushl	-(r2)			# push arg 11
	RECOVER(mach_call_addr)
L10:	pushl	-(r2)
	RECOVER(mach_call_addr)
L09:	pushl	-(r2)
	RECOVER(mach_call_addr)
8:	pushl	-(r2)
	RECOVER(mach_call_addr)
7:	pushl	-(r2)
	RECOVER(mach_call_addr)
6:	pushl	-(r2)
	RECOVER(mach_call_addr)
5:	pushl	-(r2)
	RECOVER(mach_call_addr)
4:	pushl	-(r2)
	RECOVER(mach_call_addr)
3:	pushl	-(r2)
	RECOVER(mach_call_addr)
2:	pushl	-(r2)
	RECOVER(mach_call_addr)
1:	pushl	-(r2)			# push arg 1

mach_call_call:
	calls	r0,mach_call_jump	# set number of arguments,
					# and call indirectly to avoid
					# saving registers again
	addl3	$4,(sp),sp		# restore pointer to user regs,
					# skipping r0 save slot (return value)
	popr	$0x3ffe			# restore r1..r13
	addl2	$12,sp			# pop exc/code/subcode
	rei				# return to user

mach_call_range:
	jbr	mach_call_range_error

/*
 * System call errors.
 */
mach_call_addr:
	movab	-4(r2),R_SUBCODE(r11)	# set ap as bad address
	movl	$ VM_PROT_READ,R_CODE(r11)
					# mark as read fault trap
	movl	$ EXC_BAD_ACCESS,R_EXC(r11)
	brb	mach_call_error

mach_call_range_error:
	movl	$ EXC_VAX_RESOPND,R_CODE(r11)
					# mark as 'bad operand' trap
	movl	$ EXC_BAD_INSTRUCTION,R_EXC(r11)
mach_call_error:
	jmp	trap_user

/*
 * Trampoline to call system call routine.  Avoids
 * saving registers a second time.
 */
mach_call_jump:
	.word	0			# don`t save registers
	jmp	2(r1)			# go to routine, skipping
					# register save mask

/*
 * User space emulation of system calls.
 * R0 is free; R1 holds user space emulation address.
 */
	.globl	syscall_emul
syscall_emul:
	/*
	 * Push the pc/psl onto the user's stack.  Change the
	 * pc so that we return to the user's handler itself and
	 * not to the call point.
	 */
	mfpr	$ USP,r0		# get user stack pointer
	blss	syscall_addr		# address error if not in user space

	RECOVER(syscall_addr)
sys_emul_1:
	movq	12(sp),-(r0)		# push pc/psl onto user`s stack
	RECOVER(syscall_addr)
sys_emul_2:
	movl	8(sp),-(r0)		# push syscall #
	mtpr	r0,$ USP		# update user`s stack pointer

	movl	r1,12(sp)		# change return address
	movq	(sp)+,r0		# restore registers
	addl2	$4,sp			# pop system call number
	rei				# return to user

/*
 * Bad user stack pointer
 */
syscall_addr:
	movl	r0,8(sp)		# set subcode == USP
	movq	(sp)+,r0		# restore registers
	TRAP2X(EXC_BAD_ACCESS,VM_PROT_READ|VM_PROT_WRITE)
					# report as write fault


/*
 * Page fault during syscall-emul pushes.
 * We are still on the PCB stack, since we have saved only
 * two registers.
 * The stack is:
 *
 * sp->	exception
 *	code
 *	subcode
 *	fault PC
 *	fault PSL
 *	user r0
 *	user r1
 *	syscall number
 *	user PC
 *	user PSL
 *
 * We rearrange the stack to put all of the user registers in the PCB
 * stack and take the fault on the kernel stack.  If the fault is successful,
 * we restart the syscall trap rather than undoing the register changes.
 */
sys_emul_fault:
	mfpr	$ ESP,r0		# get kernel stack
	movab	4*5-R_EXC(sp),-(r0)	# push (what will be) user reg pointer

	movq	12(sp),-(r0)		# push fault PC/PSL
	movq	4(sp),-(r0)		# push code/subcode
	movl	(sp),-(r0)		# push exception
	addl2	$(4*5),sp		# clear this stuff off PCB stack

	pushr	$0x3ffc			# save user r2..r13
	movq	R_EXC-R_R2(sp),-(sp)	# push real user r0/r1

	movl	r0,sp			# switch to kernel stack
	pushr	$0x3fff			# save r0..r13 (r0 wrong)
	pushl	sp			# point to kernel registers
	calls	$1,kernel_trap_call	# take kernel page fault

	cmpl	$syscall_addr,R_PC(sp)	# is rei PC changed to recovery addr?
	beql	syscall_fault_fail	# fault failed if so

	movl	R_PSL+4(sp),sp		# switch back to user stack
	popr	$0x3fff			# restore r0..r13
	jmp	syscall_restart		# restart system call

/*
 * Syscall_emul fault failed.
 */
syscall_fault_fail:
	movl	R_PSL+4(sp),r11		# point back to user registers
	movq	R_EXC(sp),R_EXC(r11)	# report user trap as write fault
	movl	R_SUBCODE(sp),R_SUBCODE(r11)
					# on user stack address
	movab	R_PSL+4(sp),sp		# clear everything off kernel stack
	jmp	trap_user		# report as write fault for user


/*
 * Thread_exception_return / thread_bootstrap_return
 * Return directly to user state.
 */
	.globl	_thread_exception_return
_thread_exception_return:
	.globl	_thread_bootstrap_return
_thread_bootstrap_return:
	.word	0
	bisl3	$(KERNEL_STACK_SIZE-1),sp,r1
					# point to top of stack
	movl	-3(r1),sp		# switch to PCB stack
	popr	$0x3fff			# restore r0..r13
	addl2	$12,sp			# clean stack
	rei				# restore PC/PSL

/*
 * Thread_syscall_return(kern_return_t kr)
 * Return directly to user state, returning kr as return value.
 */
	.globl	_thread_syscall_return
_thread_syscall_return:
	.word	0
	movl	4(ap),r0		# get return value
	bisl3	$(KERNEL_STACK_SIZE-1),sp,r1
					# point to top of stack
	addl3	$4,-3(r1),sp		# switch to PCB stack,
					# skipping r0 save slot (return value)
	popr	$0x3ffe			# restore r1..r13
	addl2	$12,sp			# clean stack
	rei				# restore PC/PSL

/*
 * Call_continuation(void (*continuation)())
 * Calls the continuation after popping everything off the kernel
 * stack, to avoid running out of stack.
 */
	.globl	_call_continuation
_call_continuation:
	.word	0			# save nothing (we discard frame, too)
	movl	4(ap),r0		# get continuation
	bisl3	$(KERNEL_STACK_SIZE-1),sp,r1
					# point to top of stack,
	subl3	$3,r1,sp		# leaving pointer to user registers
	clrq	ap			# clear fp/ap
	calls	$0,0f			# call routine, saving no registers
	halt	/*NOTREACHED*/
0:	.word	0
	jmp	2(r0)			# skip register save mask

/*
 * Context switching.
 */
/*
 * thread_t Switch_context(thread_t old_thread,
 *			   void (*continuation)(),
 *			   thread_t new_thread)
 * Switches to new thread,
 * returns old thread.
 */
	.globl	_Switch_context
_Switch_context:
	.word	0xfc0			# save r6..r11
	movl	4(ap),r1		# old thread
	movl	8(ap),TH_SWAP_FUNC(r1)	# save continuation
	movl	THREAD_PCB(r1),r0	# point to old thread`s PCB
	movl	fp,PCB_VKS(r0)		# save address of call frame
	mfpr	$ USP,PCB_VUSP(r0)	# save user stack pointer
#if	NCPUS > 1
	CPU_NUMBER_R0			# get our CPU number
	movl	_active_stacks[r0],THREAD_KERNEL_STACK(r1)
#else
	movl	_active_stacks,THREAD_KERNEL_STACK(r1)
#endif
					# save old kernel stack

	movl	12(ap),r3		# new thread
	movl	THREAD_KERNEL_STACK(r3),r2
					# get new kernel stack
#if	NCPUS > 1
	movl	r3,_active_threads[r0]	# make new thread current
	movl	r2,_active_stacks[r0]
#else
	movl	r3,_active_threads
	movl	r2,_active_stacks
#endif
	mtpr	r3,$ SSP		# save current_thread
	addl2	$ KERNEL_STACK_SIZE,r2
	mtpr	r2,$ ESP		# point to top of kernel stack

	movl	THREAD_PCB(r3),r0	# point to new thread`s PCB
	mtpr	PCB_VUSP(r0),$ USP	# get user stack pointer
	movl	PCB_VKS(r0),fp		# point to new thread`s frame
	movl	r1,r0			# return old thread
	ret				# return to new thread,
					# restoring its stack and regs

/*
 * Used to start the first thread on a processor.
 * Must switch from the interrupt stack to the kernel stack,
 * on which all threads run.
 */
	.globl	_Load_context
_Load_context:
	movl	r0,r3			# until inline is fixed
	brb	0f

	.globl	_load_context
_load_context:
	.word	0
	movl	4(ap),r3		# thread
0:
	movl	THREAD_KERNEL_STACK(r3),r2
					# get new kernel stack
#if	NCPUS > 1
	CPU_NUMBER_R0			# get our CPU number
	movl	r3,_active_threads[r0]	# make new thread current
	movl	r2,_active_stacks[r0]
#else
	movl	r3,_active_threads
	movl	r2,_active_stacks
#endif
	mtpr	r3,$ SSP		# save current thread
	addl2	$ KERNEL_STACK_SIZE,r2
	mtpr	r2,$ ESP		# point to top of kernel stack

	movl	THREAD_PCB(r3),r0	# point to new thread`s PCB
	mtpr	PCB_VUSP(r0),$ USP	# get user stack pointer
	movl	PCB_VKS(r0),fp		# point to new thread`s frame
	mtpr	fp,$ KSP			# set up kernel stack
	movpsl	-(sp)			# push PSL
	bicl2	$ PSL_IS,(sp)		# clear IStack bit
	pushab	0f			# REI to next instruction
	rei				# to switch to kernel stack
0:	clrl	r0			# return no old thread
	ret				# return to new thread

	.globl	_Thread_continue
_Thread_continue:
	pushl	r0			# pass old thread to continuation
	calls	$1,(r6)			# call continuation
	/*NOTREACHED*/
	halt

/*
 * void switch_to_shutdown_context(thread_t thread,
 *				   void (*routine)(processor_t),
 *				   processor_t processor)
 *
 * Saves the kernel context of the thread (the current thread),
 * switches to the interrupt stack,
 * dispatches the thread,
 * then runs routine on the interrupt stack.
 *
 * By a very important coincidence, has the same number
 * of parameters as switch_thread_context.
 */
	.globl	_switch_to_shutdown_context
_switch_to_shutdown_context:
	.word	0xfc0			# save r6..r11
	movl	4(ap),r1		# old thread
	clrl	TH_SWAP_FUNC(r1)	# no continuation
	movl	THREAD_PCB(r1),r0	# point to old thread`s PCB
	movl	fp,PCB_VKS(r0)		# save address of call frame
	mfpr	$ USP,PCB_VUSP(r0)	# save user stack pointer
#if	NCPUS > 1
	CPU_NUMBER_R0
	movl	_active_stacks[r0],THREAD_KERNEL_STACK(r1)
#else
	movl	_active_stacks,THREAD_KERNEL_STACK(r1)
#endif
	clrq	-(sp)			# clear PC/PSL for svpctx
	svpctx				# switch to interrupt stack

	movq	8(ap),r6		# save routine/processor
	
	pushl	r1			# push thread
	calls	$1,_thread_dispatch	# reschedule thread
	
	pushl	r7			# push processor
	calls	$1,(r6)			# call routine
	/*NOTREACHED*/
	halt				# (should never return)

/*
 * Primitives
 */ 


/*
 * badaddr(addr, len)
 *	see if access addr with a len type instruction causes a machine check
 *	len is length of access (1=byte, 2=short, 4=long)
 */
	.globl	_badaddr
_badaddr:
	.word	0
	movl	$1,r0
	mfpr	$ IPL,r1
	mtpr	$ BLOCK,$ IPL
	movl	4(ap),r3
	movl	8(ap),r4
	movl	_scb+MCKVEC,r2
	movab	9f+INTSTK,_scb+MCKVEC
	bbc	$0,r4,1f; tstb	(r3)
1:	bbc	$1,r4,1f; tstw	(r3)
1:	bbc	$2,r4,1f; tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	movl	r2,_scb+MCKVEC
	mtpr	r1,$ IPL
	ret
	.align	2
9:
	casel	_cpu,$1,$ VAX_MAX
0:
	.word	8f-0b		# 1 is 780
	.word	5f-0b		# 2 is 750
	.word	5f-0b		# 3 is 730
	.word	7f-0b		# 4 is 8600
	.word	6f-0b		# 5 is 8200
	.word	4f-0b		# 6 is 8800
	.word	5f-0b		# 7 is MicroVAX I
	.word	1f-0b		# 8 is 630 (MicroVAX II)
	.word	1f-0b		# 9 is unknown
	.word	9f-0b		# 10 is 650
	.word	9f-0b		# 11 is 6200
	.word	1f-0b		# not known yet
	.word	9f-0b		# 13 is 3100

9:
	mtpr	$0,MSER
	brb	1f
6:
#if	VAX820
	movl	*_ka820_csr,*_ka820_csr	# reset port controller error bits
	movl	*_ka820_ber,*_ka820_ber	# reset BI error bits
#endif	VAX820
5: 
	mtpr	$0xf,$ MCESR
	brb	1f
7:
	mtpr	$0,$ EHSR
	brb	1f
8:
	mtpr	$0,$ SBIFS
	brb	1f
4:
	mtpr	$0,$ TOSTS
	mtpr	$0,$ MCSTS
1:
	addl2	(sp)+,sp		# discard mchchk trash
	movab	2b,(sp)
	rei

/*
 * Copy specified amount of data from user space into the kernel
 * Copyin(from, to, len)
 *	r1 == from (user source address)
 *	r3 == to (kernel destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyin, R1|R3|R5)
	/*
	 *	Make the simple case of a short move really efficent.
	 */
	movab	-1(r1)[r5],r0		# source end must be non-negative
	blss	copy_error		# If source end is non-negative, but
					#  source start is not, start must be
					/*  >= 0xffff0000 (length is small). */
					#  This is never valid.
	cmpl	r5,$65535		# one movc3?
	bgtru	0f			# no
	RECOVER(copy_error)
	movc3	r5,(r1),(r3)		# do the copy
					# success (movc3 leaves r0 0)
	rsb

copy_error:
	movl	$1,r0			# bad copy
	rsb

	/*
	 *	Assume that user addresses == entire non-negative
	 *	address range
	 */
0:	tstl	r1			# source start must be non-negative
	jlss	copy_error		# fail if not in user space

copy_common:
	pushl	r6			# save r6
	movl	r5,r6			# save total length
	jleq	3f			# skip all if 0
1:
	movl	$65535,r5		# max length for movc3
	cmpl	r6,r5
	jleq	2f			# if length <= max, do it all
	subl2	r5,r6			# if too big, do only part
	RECOVER(copy_fail)
	movc3	r5,(r1),(r3)		# (advances r1,r3)
	jbr	1b
2:
	RECOVER(copy_fail)
	movc3	r6,(r1),(r3)		# move the rest
3:
	clrl	r0			# be sure to work for 0 bytes.
copy_exit:
	movl	(sp)+,r6		# restore r6
	rsb

copy_fail:
	movl	$1,r0			# fault
	jbr	copy_exit


/*
 * Copy specified amount of data from kernel to the user space
 * Copyout(from, to, len)
 *	r1 == from (kernel source address)
 *	r3 == to (user destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyout, R1|R3|R5)
	movab	-1(r3)[r5],r0		# source end must be non-negative
	blss	copy_error		# If source end is non-negative, but
					#  source start is not, start must be
					/*  >= 0xffff0000 (length is small). */
					#  This is never valid.
	cmpl	r5,$65535		# one movc3?
	bgtru	0f			# no
	RECOVER(copy_error)
	movc3	r5,(r1),(r3)		# do the copy
					# success (movc3 leaves r0 0)
	rsb
	/*
	 *	Assume that user addresses == entire non-negative
	 *	address range
	 */
0:	tstl	r3			# source start must be non-negative
	jlss	copy_error		# fail if not in user space
	jbr	copy_common


/*
 * No more moves needing fault recovery - finish recovery table.
 */
	RECOVER_TABLE_END

#if	NCPUS > 1
/*
 *	Since there are as many ways of getting the CPU number as there are
 *	multiprocessor Vaxen, we do an indirect jsb through this pointer
 *	to call the right routine.
 */
	.data
	.globl	_Cpu_number_ptr			# address of per-cpu routine
_Cpu_number_ptr:
	.long	cpu_number_zero		# starts out as 0
	.text

 # Return 0 for single CPU configurations.
	.globl	cpu_number_zero
cpu_number_zero:
	clrl	r0
	rsb

#if	VAX780 && NMACH_MPM > 0
 # Look in the multi-port memory on the 780 (if we have it).
	.data
	.globl	_mpm_port_addr
_mpm_port_addr:
	.long	zero
	.text
cpu_number_780:
	extzv	$0,$2,*_mpm_port_addr,r0	# low 2 bits
	rsb
zero:	.long	0
#else
	.set	cpu_number_780, cpu_number_zero
#endif

#if	VAX820
 # There`s a processor register on the 8200.
cpu_number_8200:
	mfpr	$ BINID,r0
	rsb
#else
	.set	cpu_number_8200, cpu_number_zero
#endif

#if	VAX8800
 # And it`s hidden somewhere else on the 8800.
cpu_number_8800:
	mfpr	$ SID,r0
	extzv	$23,$1,r0,r0			# it`s in bit 23
	rsb
#else
	.set	cpu_number_8800, cpu_number_zero
#endif


#if	VAX6200
 # And yet somewhere else on the 6200.
cpu_number_6200:
	.globl	_ka62a_csr1
	extzv	$0,$4,*_ka62a_csr1,r0
	rsb
#else
	.set	cpu_number_6200, cpu_number_zero
#endif

/*
 *	Set the CPU number routine.  Call before ANY use of cpu_number(),
 *	but after the cpu_number fields are set up.
 */
	.globl	_set_cpu_number_ptr
_set_cpu_number_ptr:
	.word	0
	movl	_cpu,r0
	movl	cpu_number_routine-4[r0],_Cpu_number_ptr
	ret

cpu_number_routine:
	.long	cpu_number_780		# 1 is 780
	.long	cpu_number_zero		# 2 is 750
	.long	cpu_number_zero		# 3 is 730
	.long	cpu_number_zero		# 4 is 8600
	.long	cpu_number_8200		# 5 is 8200
	.long	cpu_number_8800		# 6 is 8800
	.long	cpu_number_zero		# 7 is MicroVAX I
	.long	cpu_number_zero		# 8 is 630 (MicroVAX II)
	.long   cpu_number_zero         # 9 is unknown
	.long   cpu_number_zero         # 10 is 650
	.long	cpu_number_6200		# 11 is 6200
	.long   cpu_number_zero         # 12 is unknown
	.long   cpu_number_zero         # 13 is 3100

#endif	NCPUS > 1

#if	VAX6200
#include <vax/ka6200.h>
	.globl	_ka62a_csr1_quad_iqo_hack
	.globl	_ka62a_csr1
	.align 1
_ka62a_csr1_quad_iqo_hack:
	.word 	0x0
	movl	*_ka62a_csr1, r2
	bisl3	$(ka62aCSR1_FCI | ka62aCSR1_FMISS), r2, r0
	bicl3	$(ka62aCSR1_FCI | ka62aCSR1_FMISS), r2, r1
	bisl2	$ ka62aCSR1_DLCKOUTEN, r1
	movq	r0, *_ka62a_csr1
	ret

	.globl	_ka62a_rtm
_ka62a_rtm:
	.word 0x0
	CPU_NUMBER_R0
	movl	_interrupt_stack[r0],r0		# virtual stack
	addl2	$ INTSTACK_SIZE,r0		# start and end
	bbcc	$31, r0, 0f
0:	ashl	$-PGSHIFT, r0, r1		# page offset
	movl	*_vax_vsbr[r1], r2		# page num
	bicl2	$~0x1fffff, r2			# clear pg_xx
	ashl	$ PGSHIFT, r2, sp
	mtpr	$0, $ MAPEN			# will this help?
	halt
#endif	VAX6200

/*
 *	Device interrupt vectors
 */

#if	NBI > 0
/*
 *	Catch BI (or Unibus) passive release interrupts.
 *	Note:  This is meant to be super-fast, so timing is not done
 *	as the mere overhead of the timing code would be more than
 *	the interrupt itself!
 */
	.data
	.globl	_passive_release_count
_passive_release_count:
	.long	0
	.text
SCBVEC(pass_rel):
	incl	_passive_release_count
	rei

SCBVEC(kdb3int):
	TIM_PUSHR(0); pushl $3; brb 1f
SCBVEC(kdb2int):
	TIM_PUSHR(0); pushl $2; brb 1f
SCBVEC(kdb1int):
	TIM_PUSHR(0); pushl $1; brb 1f
SCBVEC(kdb0int):
	TIM_PUSHR(0); pushl $0
1:
#if	NRA > 0
	calls	$1,_udintr
#else	NRA > 0
	tstl	(sp)+
#endif	NRA > 0
	COUNT(V_INTR)
	TSREI_POPR

SCBVEC(bierr):
	TIM_PUSHR(0); calls $0,_bi_bus_error; TSREI_POPR

#if	VAX8800
SCBVEC(nmifault):
	TIM_PUSHR(0); calls $0,_nmi_fault; TSREI_POPR
SCBVEC(nbib0):
	TIM_PUSHR(0);
	pushl	$0
	brb	1f
SCBVEC(nbib1):
	TIM_PUSHR(0)
	pushl	$1
1:	calls	$1,_nbib_error
	TSREI_POPR
#else
SCBVEC(nmifault):
	rei			# should not get here
SCBVEC(nbib0):
	rei
SCBVEC(nbib1):
	rei
#endif	VAX8800
#if	VAX820
SCBVEC(rxcd):
	TIM_PUSHR(0); calls $0,_rxcd_intr; TSREI_POPR
#else
SCBVEC(rxcd):
	rei			# should not get here
#endif	VAX820
SCBVEC(ipintr):
	TIM_PUSHR(0); calls $0,_pmap_update_interrupt; TSREI_POPR

/*
 * Assembly glue routines for BI interrupts.
 */
#define	YB PUSHR; jsb _Ybi_call
				/* length must be 8 bytes */

	.align	2
	.globl	_Ybi_intr
_Ybi_intr:
	YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB
	YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB
	YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB
	YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB; YB;YB;YB;YB

_Ybi_call:
	subl3	$_Ybi_intr+8,(sp),(sp)
	ashl	$-3,(sp),(sp)		# (sp) is now interrupt number
	movq	4+6*4(sp),-(sp)		# push pc/psl
	calls	$3,_bi_err		# call error routine
	POPR
	rei

#if	VAX6200
SCBVEC(xmi0):
	TIM_PUSHR(0)
	pushl	$0
	brb	0f
SCBVEC(xmi1):
	TIM_PUSHR(0)
	pushl	$1
	brb	0f
SCBVEC(xmi2):
	TIM_PUSHR(0)
	pushl	$2
	brb	0f
SCBVEC(xmi3):
	TIM_PUSHR(0)
	pushl	$3
0:
	movq	4+ENT_DATA(sp),-(sp)	# push pc/psl
	calls	$3,_xmi_err
	TSREI_POPR
#endif	VAX6200

#else	NBI > 0
SCBVEC(pass_rel):
	rei
SCBVEC(nmifault):
	rei			# should not get here
SCBVEC(nbib0):
	rei
SCBVEC(nbib1):
	rei
SCBVEC(rxcd):
	rei
SCBVEC(ipintr):
	rei

#endif	NBI > 0

#if	NNI > 0
SCBVEC(ni0int):
	TIM_PUSHR(0); pushl $0
	calls	$1,_niintr
	COUNT(V_INTR)
	TSREI_POPR
#endif	NNI > 0

#if NMBA > 0
SCBVEC(mba3int): 
	TIM_PUSHR(0); incl _intrcnt+I_MBA3; pushl $3; brb 1f
SCBVEC(mba2int):
	TIM_PUSHR(0); incl _intrcnt+I_MBA2; pushl $2; brb 1f
SCBVEC(mba1int):
	TIM_PUSHR(0); incl _intrcnt+I_MBA1; pushl $1; brb 1f
SCBVEC(mba0int):
	TIM_PUSHR(0); incl _intrcnt+I_MBA0; pushl $0
1:	calls $1,_mbintr
	COUNT(V_INTR)
	TSREI_POPR
#endif

#if	NMACH_MPM > 0

SCBVEC(mpmc3int):
	TIM_PUSHR(0); pushl $3; brb 1f
SCBVEC(mpmc2int):
	TIM_PUSHR(0); pushl $2; brb 1f
SCBVEC(mpmc1int):
	TIM_PUSHR(0); pushl $1; brb 1f
SCBVEC(mpmc0int):
	TIM_PUSHR(0); pushl $0
1:	calls $1,_mpmcintr
	COUNT(V_INTR)
	TSREI_POPR

SCBVEC(mpm3int):
	TIM_PUSHR(0); pushl $3; brb 1f
SCBVEC(mpm2int):
	TIM_PUSHR(0); pushl $2; brb 1f
SCBVEC(mpm1int):
	TIM_PUSHR(0); pushl $1; brb 1f
SCBVEC(mpm0int):
	TIM_PUSHR(0); pushl $0
1:	calls $1,_mpmintr
	COUNT(V_INTR)
	TSREI_POPR


#endif	NMACH_MPM > 0

#if	NUBA > 0
#if defined(VAX780) || defined(VAX8600)
/*
 * Registers for the uba handling code
 */
#define	rUBANUM	r0
#define	rUBAHD	r1
#define	rUVEC	r3
#define	rUBA	r4
/* r2,r5 are scratch */

#define	I_UBA	I_UBA0		/* base of UBA interrupt counters */

#if NUBA > 4 
SCBVEC(ua7int): 
	TIM_PUSHR(0); movl $7,rUBANUM; moval _uba_hd+(7*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua6int):
	TIM_PUSHR(0); movl $6,rUBANUM; moval _uba_hd+(6*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua5int):
	TIM_PUSHR(0); movl $5,rUBANUM; moval _uba_hd+(5*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua4int):
	TIM_PUSHR(0); movl $4,rUBANUM; moval _uba_hd+(4*UH_SIZE),rUBAHD; brb 1f
#endif NUBA > 4
SCBVEC(ua3int):
	TIM_PUSHR(0); movl $3,rUBANUM; moval _uba_hd+(3*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua2int):
	TIM_PUSHR(0); movl $2,rUBANUM; moval _uba_hd+(2*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua1int):
	TIM_PUSHR(0); movl $1,rUBANUM; moval _uba_hd+(1*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua0int):
	TIM_PUSHR(0); movl $0,rUBANUM; moval _uba_hd+(0*UH_SIZE),rUBAHD;
1:
	mfpr	$ IPL,r2			/* r2 = mfpr(IPL); */
	movl	UH_UBA(rUBAHD),rUBA		/* uba = uhp->uh_uba; */
	movl	UBA_BRRVR-0x14*4(rUBA)[r2],rUVEC
					/* uvec = uba->uba_brrvr[r2-0x14] */
ubanorm:
	bleq	ubaerror 
	addl2	UH_VEC(rUBAHD),rUVEC		/* uvec += uh->uh_vec */
	bicl3	$3,(rUVEC),r1 
	jmp	PROLOGUE(r1)			/* 20 skips TIM_PUSHR(0) */
ubaerror:
	PUSHR; calls $0,_ubaerror; POPR		/* ubaerror r/w's r0-r5 */
	tstl rUVEC; jneq ubanorm		/* rUVEC contains result */
	incl _intrcnt+I_UBA[rUBANUM]
	COUNT(V_INTR)
	TSREI_POPR
#endif
#endif	NUBA > 0

SCBVEC(cnrint): 
	TIM_PUSHR(0); calls $0,_cnrint
	COUNT(V_INTR)
	incl _intrcnt+I_CNR
	TSREI_POPR
SCBVEC(cnxint):
	TIM_PUSHR(0); calls $0,_cnxint
	COUNT(V_INTR)
	incl _intrcnt+I_CNX
	TSREI_POPR

#if defined(VAX750) || defined(VAX730) || defined(VAX8600)
SCBVEC(consdin):
	TIM_PUSHR(0);
	incl _intrcnt+I_TUR
	casel	_cpu,$ VAX_750,$ VAX_8600
0:
	.word	5f-0b		# 2 is VAX_750
	.word	3f-0b		# 3 is VAX_730
	.word	6f-0b		# 4 is VAX_8600
	halt
5:
#if defined(VAX750) && !defined(MRSP)
	jsb	tudma
#endif
3:
	calls $0,_turintr
	brb 2f
6:
	calls $0, _crlintr
2:
	COUNT(V_INTR)
	TSREI_POPR;
#else
SCBVEC(consdin):
	PUSHR
	PRINTF(0, "consdin interrupt\n")
	POPR
	rei
	halt
#endif

#if defined(VAX750) || defined(VAX730)
SCBVEC(consdout):
	TIM_PUSHR(0); calls $0,_tuxintr
	COUNT(V_INTR)
	incl _intrcnt+I_TUX
	TSREI_POPR
#else
SCBVEC(consdout):
	halt
#endif

#if NDZ > 0
/*
 * DZ pseudo dma routine:
 *	r0 - controller number
 */
	.align	1
	.globl	dzdma
dzdma:
	mull2	$8*20,r0
	movab	_dzpdma(r0),r3		# pdma structure base
					# for this controller
dzploop:
	movl	r3,r0	
	movl	(r0)+,r1		# device register address
	movzbl	1(r1),r2		# get line number
	bitb	$0x80,r2		# TRDY on?
	beql	dzprei			# no	
	bicb2	$0xf8,r2		# clear garbage bits
	mull2	$20,r2
	addl2	r2,r0			# point at line`s pdma structure
	movl	(r0)+,r2		# p_mem
	cmpl	r2,(r0)+		# p_mem < p_end ?
	bgequ	dzpcall			# no, go call dzxint
	movb	(r2)+,6(r1)		# dztbuf = *p_mem++
	movl	r2,-8(r0)
	brb 	dzploop			# check for another line
dzprei:
	COUNT(V_PDMA)
	TSREI_POPR

dzpcall:
	pushl	r3
	pushl	(r0)+			# push tty address
	calls	$1,*(r0)		# call interrupt rtn
	movl	(sp)+,r3
	brb 	dzploop			# check for another line
#endif

#if NUU > 0 && defined(UUDMA)
/*
 * Pseudo DMA routine for tu58 (on DL11)
 *	r0 - controller number
 */
	.align	1
	.globl	uudma
uudma:
	movl	_uudinfo[r0],r2
	movl	16(r2),r2		# r2 = uuaddr
	mull3	$48,r0,r3
	movab	_uu_softc(r3),r5	# r5 = uuc

	cvtwl	2(r2),r1		# c = uuaddr->rdb
	bbc	$15,r1,1f		# if (c & UUDB_ERROR)
	movl	$13,16(r5)		#	uuc->tu_state = TUC_RCVERR;
	rsb				#	let uurintr handle it
1:
	tstl	4(r5)			# if (uuc->tu_rcnt) {
	beql	1f
	movb	r1,*0(r5)		#	*uuc->tu_rbptr++ = r1
	incl	(r5)
	decl	4(r5)			#	if (--uuc->tu_rcnt)
	beql	2f			#		done
	tstl	(sp)+
	TSREI_POPR			# 	registers saved in ubglue.s
2:
	cmpl	16(r5),$8		# if (uuc->tu_state != TUS_GETH)
	beql	2f			# 	let uurintr handle it
1:
	rsb
2:
	mull2	$14,r0			# sizeof(uudata[ctlr]) = 14
	movab	_uudata(r0),r4		# data = &uudata[ctlr];
	cmpb	$1,(r4)			# if (data->pk_flag != TUF_DATA)
	bneq	1b
#ifdef notdef
	/* this is for command packets */
	beql	1f			# 	r0 = uuc->tu_rbptr
	movl	(r5),r0
	brb	2f
1:					# else
#endif
	movl	24(r5),r0		# 	r0 = uuc->tu_addr
2:
	movzbl	1(r4),r3		# counter to r3 (data->pk_count)
	movzwl	(r4),r1			# first word of checksum (=header)
	mfpr	$ IPL,-(sp)		# s = spl5();
	mtpr	$0x15,$ IPL		# to keep disk interrupts out
	clrw	(r2)			# disable receiver interrupts
3:	bbc	$7,(r2),3b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),(r0)+		# *buffer = uuaddr->rdb & 0xff
	sobgtr	r3,1f			# continue with next byte ...
	addw2	2(r2),r1		# unless this was the last (odd count)
	brb	2f

1:	bbc	$7,(r2),1b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),(r0)+		# *buffer = uuaddr->rdb & 0xff
	addw2	-2(r0),r1		# add to checksum..
2:
	adwc	$0,r1			# get the carry
	sobgtr	r3,3b			# loop while r3 > 0
/*
 * We're ready to get the checksum
 */
1:	bbc	$7,(r2),1b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),12(r4)		# get first (lower) byte
1:	bbc	$7,(r2),1b
	cvtwb	2(r2),13(r4)		# ..and second
	cmpw	12(r4),r1		# is checksum ok?
	beql	1f
	movl	$14,16(r5)		# uuc->tu_state = TUS_CHKERR
	brb	2f			# exit
1:
	movl	$11,16(r5)		# uuc->tu_state = TUS_GET (ok)
2:
	movw	$0x40,(r2)		# enable receiver interrupts
	mtpr	(sp)+,$ IPL		# splx(s);
	rsb				# continue processing in uurintr
#endif

#if	VAX3100 > 0
SCBVEC(ka42_i0):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*0
	calls	$1, *(_ka42_int+4*0)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i1):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*1
	calls	$1, *(_ka42_int+4*1)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i2):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*2
	calls	$1, *(_ka42_int+4*2)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i3):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*3
	calls	$1, *(_ka42_int+4*3)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i4):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*4
	calls	$1, *(_ka42_int+4*4)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i5):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*5
	calls	$1, *(_ka42_int+4*5)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i6):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*6
	calls	$1, *(_ka42_int+4*6)
	COUNT(V_INTR)
	TSREI_POPR
SCBVEC(ka42_i7):
	TIM_PUSHR(0)
	pushl	_ka42_unt+4*7
	calls	$1, *(_ka42_int+4*7)
	COUNT(V_INTR)
	TSREI_POPR
	.data
	.align 2
	.globl	_ka42_glu
	.globl	_ka42_int
	.globl	_ka42_unt
	.globl	_ka42_stray_int
_ka42_glu:
	.long	_Xka42_i0, _Xka42_i1, _Xka42_i2, _Xka42_i3
	.long	_Xka42_i4, _Xka42_i5, _Xka42_i6, _Xka42_i7
_ka42_int:
	.long	_ka42_stray_int, _ka42_stray_int, _ka42_stray_int, _ka42_stray_int
	.long	_ka42_stray_int, _ka42_stray_int, _ka42_stray_int, _ka42_stray_int
_ka42_unt:
	.long	0, 1, 2, 3, 4, 5, 6, 7
	.text
#endif	VAX3100 > 0

#if defined(VAX750) && !defined(MRSP)
/*
 * Pseudo DMA routine for VAX-11/750 console tu58 
 *   	    (without MRSP)
 */
	.align	1
	.globl	tudma
tudma:
	movab	_tu,r5			# r5 = tu
	tstl	4(r5)			# if (tu.tu_rcnt) {
	beql	3f
	mfpr	$CSRD,r1		# get data from tu58
	movb	r1,*0(r5)		#	*tu.tu_rbptr++ = r1
	incl	(r5)
	decl	4(r5)			#	if (--tu.tu_rcnt)
	beql	1f			#		done
	tstl	(sp)+
	TSREI_POPR			# 	registers saved in ubglue.s
1:					# }
	cmpl	16(r5),$8		# if (tu.tu_state != TUS_GETH)
	beql	2f			# 	let turintr handle it
3:
	rsb
2:
	movab	_tudata,r4		# r4 = tudata
	cmpb	$1,(r4)			# if (tudata.pk_flag != TUF_DATA)
	bneq	3b			# 	let turintr handle it
1:					# else
	movl	24(r5),r1		# get buffer pointer to r1
	movzbl	1(r4),r3		# counter to r3
	movzwl	(r4),r0			# first word of checksum (=header)
	mtpr	$0,$CSRS		# disable receiver interrupts
3:
	bsbw	5f			# wait for next byte
	mfpr	$CSRD,r5
	movb	r5,(r1)+		# *buffer = rdb
	sobgtr	r3,1f			# continue with next byte ...
	mfpr	$CSRD,r2		# unless this was the last (odd count)
	brb	2f

1:	bsbw	5f			# wait for next byte
	mfpr	$CSRD,r5
	movb	r5,(r1)+		# *buffer = rdb
	movzwl	-2(r1),r2		# get the last word back from memory
2:
	addw2	r2,r0			# add to checksum..
	adwc	$0,r0			# get the carry
	sobgtr	r3,3b			# loop while r3 > 0
/*
 * We're ready to get the checksum.
 */
	bsbw	5f
	movab	_tudata,r4
	mfpr	$CSRD,r5
	movb	r5,12(r4)		# get first (lower) byte
	bsbw	5f
	mfpr	$CSRD,r5
	movb	r5,13(r4)		# ..and second
	movab	_tu,r5
	cmpw	12(r4),r0		# is checksum ok?
	beql	1f
	movl	$14,16(r5)		# tu.tu_state = TUS_CHKERR
	brb	2f			# exit
1:
	movl	$11,16(r5)		# tu.tu_state = TUS_GET
2:
	mtpr	$0x40,$CSRS		# enable receiver interrupts
	rsb				# continue processing in turintr
/*
 * Loop until a new byte is ready from
 * the tu58, make sure we don't loop forever
 */
5:
	movl	$5000,r5		# loop max 5000 times
1:
	mfpr	$CSRS,r2
	bbs	$7,r2,1f
	sobgtr	r5,1b
	movab	_tu,r5
	movl	$13,16(r5)		# return TUS_RCVERR
	tstl	(sp)+			# and let turintr handle it
1:
	rsb
#endif

#if	NUBA > 0
/*
 * Stray UNIBUS interrupt catch routines
 *
 * These aren't worth timing; stray interrupts during configuration
 *  will get charged to kernel anyway; otherwise they should never
 *  happen.
 */
	.data
	.align	2
#define	PJ	PUSHR;jsb _Xustray
	.globl	_catcher
_catcher:
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ

	.globl	_cold
_cold:	.long	1
	.data

	.text
SCBVEC(ustray):
	blbc	_cold,1f
	mfpr	$ IPL,_br
	subl3	$_catcher+8,(sp)+,r0
	ashl	$-1,r0,_cvec
	POPR
#if	MACH_TIME
/* if 780, pop regs again, and timestamp */
	cmpl	$ VAX_780,_cpu
	beql	2f
	cmpl	$ VAX_8600,_cpu
	bneq	3f
2:	POPR
	addl2	$4,sp
3:
#endif	MACH_TIME
	rei
1:
	subl3	$_catcher+8,(sp)+,r0
	ashl	$-1,r0,-(sp)
	mfpr	$ IPL,-(sp)
	PRINTF(2, "uba?: stray intr ipl %x vec %o\n")
	POPR
#if	MACH_TIME
/* if 780, pop regs again and timestamp */
	cmpl	$ VAX_780,_cpu
	beql	2f
	cmpl	$ VAX_8600,_cpu
	bneq	3f
2:	POPR
	addl2	$4,sp
3:
#endif	MACH_TIME
	rei

#endif	NUBA > 0

#include <ubglue.s>
