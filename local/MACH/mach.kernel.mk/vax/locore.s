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
 * $Log:	locore.s,v $
 * Revision 2.10  89/03/09  04:50:23  rpd
 * 	More cleanup.  Ripped out MACH_TIME.
 * 
 * Revision 2.9  89/02/25  20:24:11  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  88/10/11  13:02:28  rpd
 * 	VAX6200: Try ssc timer chip.
 * 	[88/10/08            rvb]
 * 
 * Revision 2.7  88/09/29  15:34:17  mrt
 * 	29-Sep-88 Mary Thompson (mrt) at Carnegie Mellon
 * 	Made Dave Golub's fix for Copyout and Copyin
 * 	to check that the address range does not cross
 * 	from the user to kernel space.
 * 	[88/09/29  15:23:37  mrt]
 * 
 * Revision 2.6  88/08/26  14:59:22  mwyoung
 * 		Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * Revision 2.5  88/08/09  17:31:18  rvb
 * 24-Jun-88  Robert Baron (rvb)
 * 	Have Xwtime assembler interface make a pcb on the stack
 * 	so if this was a wei for debugging the state is saved.
 *  8-Jun-88  Robert Baron (rvb)
 * 	1.	VAX6200, ka62a_rtm() return to monitor, but leave him a stack.
 * 	2.	On kernel entry, save all registers into boot_regs[] array
 *  7-Jun-88  Robert Baron (rvb)
 * 	call start_processors(boothowto&RB_UNIPROC) with arg now.
 *  7-Jun-88  Robert Baron (rvb)
 * 	1.	For VAX_6200, update printing_cpu after cpu is known.
 * 	2.	Start slaves at HIGH vs 0x1f
 * 	3.	Start slaves by call in start_init to start_processors()
 * 	4.	Add gross hack for reseting level 2 cache on VAX_6200
 * 28-Apr-88  David Golub (dbg)
 * 	Handle MACH-only tasks (no proc structure).  Removed dead code.
 * 	Made Load_context translate the pcb virtual address itself.
 * 25-May-88  Robert Baron (rvb)
 * 	Move HIGH down to 1c  (to alloc VAX6200 WEI interrupts).
 * 	Define BLOCK to 1f (HIGH's old value) for use in probe code.
 *  9-May-88  Robert Baron (rvb)
 * 	Handle 8200 & 8800 badaddr clean up in bi_badaddr() now.
 *  2-May-88  Robert Baron (rvb)
 * 	VAX820:	Check that processor is initialized properly.
 * 
 *
 * 26-Apr-88  Alessandro Forin (af) at Carnegie-Mellon University
 *	Added syscall emulation code.
 *
 * 18-Apr-88  Steve Schwab (schwab) at Carnegie-Mellon University
 *	Add if_ni.c fore DEBNA == bi ethernet
 *
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Yet another way to determine cpu number.
 *
 *  4-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate uses of _cnt; provide a macro that will be used
 *	by glue routines as well.
 *
 * 12-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Give the 650's timer a different interrupt.  Fix bug in abnormal
 *	exit code that was taking an AST trap at every MACH call (I forgot
 *	the '$' for a literal! oops...).
 *
 * 11-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Must define nofault for MACH_LOAD off.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, use ssc timer 0 vs uVax timer
 *
 *  7-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Add abnormal exit code for mach_trap handler.
 *
 * 19-Nov-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Cataclysm:
 *		CS_GENERIC == TRUE
 *		MACH_TIME condensed via a few macros
 *		MACH_VM == TRUE (see MACH_HUH)
 *		MACH_TT == TRUE
 *		MACH_MP == TRUE || MACH_MP == NCPUS > 1
 *		MACH_SYSCALL == TRUE
 *
 * 24-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *      Changes for VAX650: treat like VAX630 and allow emulation code
 *
 * 20-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	CS_GENERIC: use symbols instead of numeric offsets for profiling
 *	buffer fields in addupc.
 *
 * 01-Oct-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Copyin/Copyout do not use THREAD_RECOVER - fault handler notices if
 *	they were executing based on PC and goes to proper recovery address.
 *
 * 26-Sep-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Implement Fuword and Suword in assembly language.  Enable 4.3
 *	NOSUBINST code for uVaxes (eliminates locc in copy string
 *	routines).
 *
 * 20-Aug-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Fixed up definitions of set_cpu_number and Cpu_number_ptr for
 *	NCPUS == 1 case.
 *
 *  4-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	ESP isn't reliable between save_context and load_context.  Give
 *	up using it for cpu_number and call model-dependent routine
 *	instead.  Add model-dependent routines here.
 *
 *  3-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_VM: Fixed addupc to use THREAD_RECOVER to probe monitor
 *	buffer.  VAX 'probew' instruction fails if the buffer is
 *	copy-on-write.
 *	
 *	Changed Load_context to set the new CPU number (ESP) and thread
 *	(SSP) fields before 'ldpctx', from the current CPU number and
 *	new thread.  Avoids two procedure calls in multi-CPU systems.
 *
 *  2-Jun-87  David Golub (dbg) at Carnegie-Mellon University
 *	Rewrote the ACALL handler.  Dropped ASETJMP and setting/testing
 *	of u_eosys (not used by any MACH system call).  Save registers
 *	correctly for all calls.  Post an AST trap if a signal is needed
 *	instead of calling the signal mechanism.
 *	Removed code to put sigcode in PCB under MACH_TT.
 *
 *  1-Jun-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Work around the 8800 MMU hardware bug.  See comments in code.
 *
 * 31-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed ACALL handler once again.  This time the fix was to be
 *	sure it puts a proper user saved state when doing all complex
 *	traps.  This keeps a program that mutates itself from trashing
 *	the kernel.  THE ACALL HANDLER NEEDS TO BE TOTALLY REWRITTEN.
 *
 * 27-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Export sigcode.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	General 8800 support for low level interrupt handling, machine
 *	check support, etc.
 *
 * 22-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *      NEMUL:  Added missing conditionals for non MACH_VM case.
 *      NRA:  Corrected misplaced conditionals for 8200 KDB50
 *      interrupt vector transfer when MACH_TIME is not enabled.
 *      [ V5.1(F9) ]
 *
 * 16-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make sure TBIA register is poked with a 0 to clear the TLB (this
 *	seems to be necessary on an 8800).
 *
 * 22-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_KDB:  corrected internal references to use "eintstack"
 *	rather than "_eintstack" which is only defined under this
 *	option.
 *	[ V5.1(F10) ]
 *
 * 10-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make sure SSP is cleared so we don't think we have a thread when
 *	we really don't during the boot sequence.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Put current thread in SSP in Load_context.
 *
 * 29-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed MACH_TT code in Load_context since it is no longer
 *	required.
 *
 *  6-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed unnecessary include of mach_only.h
 *
 *  3-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use same SCB for master and slave processors.  Remove slave MPM
 *	interrupts.   Add one more page to interrupt stack - many ISP
 *	faults seemed to run over the old slave_scb.
 *
 *  3-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed remaining Accent return codes to MACH return codes;
 *	included kern_return.h.
 *
 * 26-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed include of mach_acc.h.
 *
 * 23-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed TBIA for slave processors in Load_context, since pmap
 *	module should now correctly update translation buffers.
 *
 * 11-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added ipintr for VAX8200 interprocessor interrupts.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed loading of init for MACH_TT.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged in my bug fixes for real threads.
 *
 * 14-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_TT: Added call to load_init_program in setup_init.
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added jsb'able Current_Task, for inline expansion.
 *
 * 11-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	When running with Berkeley emulation code and Mach VM, be sure
 *	to make the entire text segment readable by the user so that he
 *	can execute the emulation code.
 *
 *  2-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed VAX1 check for emulation code as the uVax I doesn't need
 *	emulation support.  Also enabled 4.3 emulation code when Ultrix
 *	emulation (NEMUL) is not turned on.  Note that 4.3 emulation
 *	won't work (yet) on a kernel with Mach VM turned on because it
 *	depends on the fact that the kernel's text is user readable!
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush CS_NEWCPU.
 *
 * 14-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed trap table name.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make MACH_TT work.
 *
 * 27-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Fixed use of ENT_DATA to be conditional on MACH_TIME.
 *
 * 13-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Initialize timing code vectors to 'timing-off' case.
 *
 * 11-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed MACH_SHM.
 *
 *  6-Aug-86  Robert Baron and Richard Rashid (rvb & rfr) at Carnegie-Mellon University
 *  	Modified call to ACALLpsig to run faster and correctly
 *	handle signal returns.
 *
 * 25-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added a new trap code for KDB entry to avoid conflict with trace
 *	trap from user mode.  Zero frame and argument pointers at start,
 *	to keep debugger trace from blowing up.  (Change originally made 25-Jun-86).
 *
 * 22-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Added Ka630ROMmap definition and flushed old
 *	Ka630map special case since the memory registers are now
 *	in the nexus area.
 *	
 * 19-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	WB_LOAD: Fixed to set correct physical address in first word
 *	of RPB.
 *
 * 24-Jul-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	remove #ifdef from badaddr table.
 *	who_printf running process at Load_context time
 *
 * 10-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC: Added _INCLUDE_VERSION definition.
 *
 *  3-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Fixed ACALLs so that they operate fully in parallel and added
 *	call to ACALLpsig after and ACALLcmplx.
 *
 * 29-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed copyin, copyout to JSB calling sequences.
 *	Use page_mask in copystr.
 *
 * 25-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed slave_stacks (they are dynamically allocated in
 *	setup_main).
 *
 * 18-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Modified spin lock at kernel entry to not spin using an
 *	interlocked bbssi instruction.
 *
 * 14-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed separate slave console interrupt.  It is handled through
 *	the normal console interrupt system.
 *
 * 13-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	When starting up a slave, double map the kernel into P0 space
 *	before turning on memory mapping.  This seems to be important
 *	for the KA820.
 *
 * 10-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Relocated slave_proc definition to kern_synch.c
 *
 *  4-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	KA820 support.
 *
 * 30-Apr-86  David Golub (dbg) at Carnegie-Mellon University
 *	Fixed copystr to not clear THREAD_RECOVER - it doesn't set it.
 *	(Routine was crashing, or zeroing a random location!)
 *
 * 22-Apr-86  David Golub (dbg) at Carnegie-Mellon University
 *	Make a fake PCB, just long enough to hold the 4 stack pointers,
 *	to use while starting the system.  Some VAXes always store the
 *	stack pointers in memory, even if they're set with MTPR.
 *	We don't need a full PCB since the rest of its fields are
 *	touched only by LDPCTX and SVPCTX.
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 29-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 20-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	NB!!!!!! TIM_PUSHR() and TIM() use the label 9:
 *	be careful with sequences like that for the mba's
 *	which branch to a common point.  That point had better not be 9:
 *
 *  6-Dec-85  David L. Black (dlb) at CMU.  Added indirect addressing
 *	to timing and routines to enable/disable it.  Also cleaned
 *	up ugly catcher code.
 *
 *  3-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Fixed up doadump code to work when the OS is in shared memory.
 *	The big problem here is that doadump is called with virtual
 *	address mapping on, whereas it really should be using physical
 *	addresses. (Unmodified the call $0,_dump fails because it uses
 *	the virtual address for _dump even though the mapping is off.)
 *	My fix is ugly by having doadump turn off mapping and then jump
 *	to the "appropriate" shared memory address.  The latter is
 *	computed when the system comes up and `stored into the jmp
 *	instruction'.  (More elegant approaches don't work.  Apparently,
 *	there is a very small window; between when the mapping is
 *	disabled and when the PC had better right.)
 *
 * 11-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add support for non-zero load point in the D-Float check.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added icode in assembly language (Now we can tell why init
 *	failed.  FLushed the shmap initialization code.
 *
 * 18-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Put the "start_lock" in the text segment so that when Melange is
 *	loaded by the boot program, it will be guaranteed to be zeroed
 *	(as opposed to being a random value).
 *
 * 10-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Major changes... new scheduler hooks (save context, load
 *	context).  Scheduler is primarily in C now, returned the old
 *	scheduler to it's original form.  Also, it looks like Bob is
 *	trying to initialize shmap here again (sigh).  I left the code
 *	in, but it was obviously never completed, and hopefully will be
 *	done properly (i.e. NOT HERE).
 *
 *  8-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added Mike Accetta's kernel debugger support.
 *
 * 29-Aug-85 David L. Black (dlb) at CMU
 *	Massive changes to conditionally compile timing code. (NCMUTIME)
 *
 * 19-Aug-85 David L. Black (dlb) at CMU
 *	Forgot about 780 dispatch interaction with catcher array
 *	for autoconf.  Fixed to do timing, modified offset in
 *	autoconf.
 *
 * 30-Jul-85 David L. Black (dlb) at CMU
 *	Added code and macros to do user-mode timing.  VAX/780 uba dispatch
 *	code changed due to changes in ubglue.s, also fixed counting prob.
 * 
 * 15-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_KDB: Added SCB vector for KDB (software IPL 0xf)
 *	interrupt which provides the mechanism for switching the
 *	kernel debugger onto the interrupt stack to avoid kernel stack
 *	overflow problems.
 *	[V1(1)]
 *
 * 28-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated for uniprocessor handling... removed initialization
 *	of shmap (that was bogus being here in the first place) and
 *	reduced syspt size, it was 64K too big.
 *
 * 20-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_VAXM:  Support for MicroVAX-I and -II (a la ULTRIX-32).
 *	Hook reserved/privileged instruction and protection fault
 *	handlers into ULTRIX-32 instruction emulation code.  Expand
 *	system page table map space for nexus and UNIBUS/QBUS address
 *	space.  Disable interval clock on boot.  Extract physical
 *	memory size from well-known location instead of auto-sizing.
 *	Reset summary register after machine check on these CPU's.
 *	Enable emulation code for user access.  Test for D-float
 *	support.
 *
 * 15-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added check for floating point unit and setup code for emulation
 *	of instructions on MicroVAX II (all based on Ultrix).
 *
 * 25-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below.
 *	CS_BOOT: also save boot device from r10 and restore
 *	(possibly modified) boot flags to r11 before invoking
 *	/etc/init.
 *	[V1(1)]
 *
 * 26-Feb-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	U_ERROR and U_EOSYS are char's not longs
 *
 * 15-Nov-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	We also have to call psig() as the call exits.
 *
 * 13-Nov-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Fix new trap handler to use U_EOSYS to allow restarts in Setjmp
 *	context.  PS: only JUSTRETURN and RESTARTSYS are handled now.
 *
 * 21-Sep-84  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Modified Remqhi so that a NULL pointer is returned when there
 *	the queue is empty.
 *
 * 14-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Add mpmc?intr entry points that the scb dispatches to on MPM
 *	interrupts
 *
 * 13-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added a new trap handler which is activated for chmk's with negative
 *	arguments
 *
 * 13-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added code to catch and printout location of all stray SCB
 *	interrupts.
 *
 * 13-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added sh?utl to kernel's map to allocate shared memory in
 *
 * 17-Aug-84  Andy Gruss (gruss) at Carnegie-Mellon University
 *	NGFB:  Allocate system page table entries for the frame
 *	memory of a Gruss frame buffer device.
 *
 * 28-Jun-84  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Extend memory sizing constant to permit up to 16Mb
 *	(V3.07J).
 *
 * 31-Mar-84  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added subroutines to perform interlocked queue instructions and
 *	interlocked bit set/clear instructions.
 *
 */

#include <cputypes.h>

#include <cpus.h>
#include <mach_kdb.h>
#include <mach_load.h>
#include <mach_emulation.h>
 
#include <emul.h>
#include <gfb.h>
#include <mach_mpm.h>

/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)locore.s	7.1 (Berkeley) 6/5/86
 */

#if	VAX650 || VAX630
#define NOSUBSINST
#endif	VAX650 || VAX630
#include <vax/asm.h>
#include <vax/psl.h>
#include <vax/pte.h>

#include <sys/errno.h>

#include <vax/mtpr.h>
#include <vax/trap.h>
#include <vax/cpu.h>
#include <vax/nexus.h>
#include <vax/cons.h>
#include <vax/clock.h>
#include <vax/ioa.h>
#include <sys/reboot.h>
#include <mach/kern_return.h>
#include <kern/syscall_sw.h>
#if	NGFB > 0
#include <vax/gfbreg.h>
#endif	NGFB
#include <vaxuba/ubareg.h>

#include <mach/vm_param.h>
#include <dz.h>
#include <uu.h>
#include <ps.h>
#include <mba.h>
#include <uba.h>
#include <ni.h>

	.set	HIGH,0x1c	# mask for most disables allows WEI
	.set	BLOCK,0x1f	# mask for total disable
	.set	MCKVEC,4	# offset into scb of machine check vector
	.set	NBPG,512
	.set	PGSHIFT,9

	.set	NISP,4		# number of interrupt stack pages

	.data
	.globl	_HIGH
_HIGH:	.long	HIGH
	.text
#define COUNT(x)

/* 
 *  Arrange for the include file version number to appear directly in
 *  the name list.
 */
#include <sys/version.h>
	.globl	_INCLUDE_VERSION
	.set	_INCLUDE_VERSION,INCLUDE_VERSION
/*
 * User structure is UPAGES at top of user space.
 */

	.globl	_intstack
_intstack:
_start_lock:			# squeeze this in here (R/W text)
	.space	NISP*NBPG
eintstack:
#if	MACH_KDB
	.globl	_eintstack
_eintstack:
#endif	MACH_KDB

	.globl	_start_text
_start_text:
/*
 * Do a dump.
 * Called by auto-restart.
 * May be called manually.
 */
	.align	2
	.globl	_doadump
_doadump:
	nop; nop				# .word 0x0101
#define _rpbmap	_Sysmap				# rpb, scb, UNI*vec, istack*4
#if	MACH_LOAD
	mtpr	$0, $MAPEN			# !!!! avie, mja !!! please fix this
doajmp:	jmp	2f				# this is a horrible hack. we modify
2:						# the long at doajmp+2 by adding
						# loadpt.  Nothing else works
#endif	MACH_LOAD
	bicl2	$PG_PROT,_rpbmap
	bisl2	$PG_KW,_rpbmap
	mtpr	$0,$TBIA
	tstl	_rpb+RP_FLAG			# dump only once!
	bneq	1f
	incl	_rpb+RP_FLAG
	movl	sp,erpb
	movab	erpb,sp
	mfpr	$PCBB,-(sp)
/*	ashl	$(-PGSHIFT), (sp), _masterpaddr*/
	mfpr	$MAPEN,-(sp)
	mfpr	$IPL,-(sp)
	mtpr	$0,$MAPEN
	mtpr	$HIGH,$IPL
	pushr	$0x3fff
	calls	$0,_dumpsys
1:
	pushl	$TXDB_BOOT
	calls	$1,_tocons
	halt

/*
 * Interrupt vector routines
 */ 
	.globl	_waittime

#define SCBVEC(name)	.align 2; .globl _X/**/name; _X/**/name
#define PANIC(msg)	clrl _waittime; pushab 1f; \
			calls $1,_panic; 1: .asciz msg
#define PRINTF(n,msg)	pushab 1f; calls $n+1,_printf; MSG(msg)
#define MSG(msg)	.data; 1: .asciz msg; .text
#define PUSHR		pushr $0x3f
#define POPR		popr $0x3f
#if	MACH_LOAD
#else	MACH_LOAD
	.data
nofault: .long	0	# where to go on predicted machcheck
	.text
#endif	MACH_LOAD

#define TIM(x)	
#define TSREI		rei
#define TS		jmp	(r0)
#define TIM_PUSHR(x)	PUSHR
#define TSREI_POPR	POPR; rei
#define ENT_DATA	4+6*4
#define PROLOGUE	2
#define UT_FIND

	.align 2
	.globl _Yprint
_Yprint:
	subl2	$_Ystray+8,(sp)
	ashl	$-1,(sp),(sp)
	mfpr	$IPL,-(sp)
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
SCBVEC(machcheck):
#if	MACH_LOAD
	/*
	 * 4.3 used to take a machine check here when sizing
	 * memory... this is bogus because the machine check
	 * vector is a virtual address.  They were depending
	 * on the fact that the VAX masked off the "kernel mode"
	 * bit if memory mapping is off.  Well, this doesn't
	 * work for non-zero load based kernels.  Badaddr now
	 * puts its own vector in the machine check vector.
	 */
#else	MACH_LOAD
	tstl	nofault
	bneq	1f
#endif	MACH_LOAD
	PUSHR; pushab 6*4(sp); calls $1,_machinecheck; POPR;
	addl2 (sp)+,sp; rei
#if	MACH_LOAD
#else	MACH_LOAD
	.align	2
1:
	casel	_cpu,$1,$VAX_MAX
0:
	.word	8f-0b		# 1 is 780
	.word	5f-0b		# 2 is 750
	.word	5f-0b		# 3 is 730
	.word	7f-0b		# 4 is 8600
	.word	1f-0b		# ???
	.word	1f-0b		# ???
	.word	1f-0b		# ???
	.word	1f-0b		# 8 is 630
	.word	1f-0b		# ???
	.word	1f-0b		# 10 is 650
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
	movl	nofault,(sp)
	rei
#endif	MACH_LOAD
SCBVEC(kspnotval):
	PUSHR; PANIC("KSP not valid");
SCBVEC(powfail):
	halt
SCBVEC(chme): SCBVEC(chms): SCBVEC(chmu):
	PUSHR; PANIC("CHM? in kernel");
SCBVEC(stray): 
	TIM_PUSHR(0); PRINTF(0, "stray scb interrupt\n"); TSREI_POPR;
SCBVEC(nexzvec):
	TIM_PUSHR(0); mfpr $IPL,-(sp); PRINTF(1, "nexus stray intr ipl%x\n"); TSREI_POPR
SCBVEC(cmrd):
	TIM_PUSHR(0); calls $0,_memerr; TSREI_POPR
SCBVEC(wtime):
	pushr	$0x3fff				/* everything */

	mfpr	$USP, -(sp)
	mfpr	$SSP, -(sp)
	mfpr	$ESP, -(sp)
	mfpr	$KSP, -(sp)

	subl2	$12, sp
	movl	4*21(sp), 0(sp)			/* pc */
	movl	4*22(sp), 4(sp)			/* psl */
	moval	4*3(sp), 8(sp)			/* pcb !! */
	calls	$3, _wtime
	addl2	$4*4, sp
	popr	$0x3fff
	rei

#if	VAX820
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
#include <ra.h>
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
#endif	VAX820
#if	NNI > 0
SCBVEC(ni0int):
	TIM_PUSHR(0); pushl $0
	calls	$1,_niintr
	COUNT(V_INTR)
	TSREI_POPR
#endif	NNI > 0
#if	NMBA > 0
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

#if	VAX820
SCBVEC(bierr):
	TIM_PUSHR(0); calls $0,_bi_bus_error; TSREI_POPR
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
SCBVEC(rxcd):
	TIM_PUSHR(0); calls $0,_rxcd_intr; TSREI_POPR
SCBVEC(ipintr):
	TIM_PUSHR(0); calls $0,_ip_intr; TSREI_POPR
#endif	VAX820
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
#if	defined(VAX780) || defined(VAX8600)
/*
 * Registers for the uba handling code
 */
#define rUBANUM	r0
#define rUBAHD	r1
#define rUVEC	r3
#define rUBA	r4
/* r2,r5 are scratch */

#define I_UBA	I_UBA0		/* base of UBA interrupt counters */

#if	NUBA > 4 
SCBVEC(ua7int): 
	TIM_PUSHR(0); movl $7,rUBANUM; moval _uba_hd+(7*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua6int):
	TIM_PUSHR(0); movl $6,rUBANUM; moval _uba_hd+(6*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua5int):
	TIM_PUSHR(0); movl $5,rUBANUM; moval _uba_hd+(5*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua4int):
	TIM_PUSHR(0); movl $4,rUBANUM; moval _uba_hd+(4*UH_SIZE),rUBAHD; brb 1f
#endif	NUBA > 4
SCBVEC(ua3int):
	TIM_PUSHR(0); movl $3,rUBANUM; moval _uba_hd+(3*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua2int):
	TIM_PUSHR(0); movl $2,rUBANUM; moval _uba_hd+(2*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua1int):
	TIM_PUSHR(0); movl $1,rUBANUM; moval _uba_hd+(1*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua0int):
	TIM_PUSHR(0); movl $0,rUBANUM; moval _uba_hd+(0*UH_SIZE),rUBAHD;
1:
	mfpr	$IPL,r2				/* r2 = mfpr(IPL); */
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
#if	VAX650 || VAX6200
SCBVEC(ssc0clock):
	mtpr	$0x16, $IPL
	TIM_PUSHR(0)
	movl	_ssclock,r3
	movl	$ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,SSC_TCR0(r3)
	brb	hardclock_common
SCBVEC(ssc1clock):
	mtpr	$0x16, $IPL
	TIM_PUSHR(0)
	movl	_ssclock,r3
	movl	$ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,SSC_TCR0+0x10(r3)
	brb	hardclock_common
#endif	VAX650 || VAX6200
SCBVEC(hardclock):
	mtpr	$BLOCK, $IPL		/* else things could get messy */
	TIM_PUSHR(0)
	mtpr $ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,$ICCS
hardclock_common:
#if	NPS > 0
	pushl	ENT_DATA(sp); pushl ENT_DATA(sp);
	calls	$2,_psextsync
#endif
	pushl ENT_DATA(sp); pushl ENT_DATA(sp);
	calls $2,_hardclock			# hardclock(pc,psl)
	COUNT(V_INTR)
	incl	_intrcnt+I_CLOCK
	TSREI_POPR;
SCBVEC(softclock):
	TIM_PUSHR(0)
	pushl	ENT_DATA(sp); pushl ENT_DATA(sp);
	calls	$2,_softclock			# softclock(pc,psl)
	COUNT(V_SOFT)
	TSREI_POPR; 

#include <net/netisr.h>
	.globl	_netisr
SCBVEC(netintr):
	TIM_PUSHR(0)
#include <imp.h>
#if	NIMP > 0
	bbcc	$NETISR_IMP,_netisr,1f; calls $0,_impintr; 1:
#endif
#ifdef	INET
	bbcc	$NETISR_IP,_netisr,1f; calls $0,_ipintr; 1:
#endif
#ifdef	NS
	bbcc	$NETISR_NS,_netisr,1f; calls $0,_nsintr; 1:
#endif
	bbcc	$NETISR_RAW,_netisr,1f; calls $0,_rawintr; 1:
	COUNT(V_SOFT)
	TSREI_POPR

#if	defined(VAX750) || defined(VAX730) || defined(VAX8600)
SCBVEC(consdin):
	TIM_PUSHR(0);
	incl _intrcnt+I_TUR
	casel	_cpu,$VAX_750,$VAX_8600
0:
	.word	5f-0b		# 2 is VAX_750
	.word	3f-0b		# 3 is VAX_730
	.word	6f-0b		# 4 is VAX_8600
	halt
5:
#if	defined(VAX750) && !defined(MRSP)
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

#if	defined(VAX750) || defined(VAX730)
SCBVEC(consdout):
	TIM_PUSHR(0); calls $0,_tuxintr
	COUNT(V_INTR)
	incl _intrcnt+I_TUX
	TSREI_POPR
#else
SCBVEC(consdout):
	halt
#endif

#if	NDZ > 0
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
	addl2	r2,r0			# point at line's pdma structure
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

#if	NUU > 0 && defined(UUDMA)
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
#ifdef	notdef
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
	mfpr	$IPL,-(sp)		# s = spl5();
	mtpr	$0x15,$IPL		# to keep disk interrupts out
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
	mtpr	(sp)+,$IPL		# splx(s);
	rsb				# continue processing in uurintr
#endif

#if	defined(VAX750) && !defined(MRSP)
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

/*
 * Stray UNIBUS interrupt catch routines
 *
 * These aren't worth timing; stray interrupts during configuration
 *  will get charged to kernel anyway; otherwise they should never
 *  happen.
 */
	.data
	.align	2
#define PJ	PUSHR;jsb _Xustray
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
	mfpr	$IPL,r11
	subl3	$_catcher+8,(sp)+,r10
	ashl	$-1,r10,r10
	POPR
	rei
1:
	subl3	$_catcher+8,(sp)+,r0
	ashl	$-1,r0,-(sp)
	mfpr	$IPL,-(sp)
	PRINTF(2, "uba?: stray intr ipl %x vec %o\n")
	POPR
	rei

#if	NEMUL > 0
/*
 *  Use these only in the absence of ULTRIX version.
 */
#else	NEMUL > 0
#if	VAX650 || VAX630
/*
 * Emulation OpCode jump table:
 *	ONLY GOES FROM 0xf8 (-8) TO 0x3B (59)
 */
#define EMUTABLE	0x43
#define NOEMULATE	.long noemulate
#define EMULATE(a)	.long _EM/**/a
	.globl	_emJUMPtable
_emJUMPtable:
/* f8 */	EMULATE(ashp);	EMULATE(cvtlp);	NOEMULATE;	NOEMULATE
/* fc */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 00 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 04 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 08 */	EMULATE(cvtps);	EMULATE(cvtsp);	NOEMULATE;	EMULATE(crc)
/* 0c */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 10 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 14 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 18 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 1c */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 20 */	EMULATE(addp4);	EMULATE(addp6);	EMULATE(subp4);	EMULATE(subp6)
/* 24 */	EMULATE(cvtpt);	EMULATE(mulp);	EMULATE(cvttp);	EMULATE(divp)
/* 28 */	NOEMULATE;	EMULATE(cmpc3);	EMULATE(scanc);	EMULATE(spanc)
/* 2c */	NOEMULATE;	EMULATE(cmpc5);	EMULATE(movtc);	EMULATE(movtuc)
/* 30 */	NOEMULATE;	NOEMULATE;	NOEMULATE;	NOEMULATE
/* 34 */	EMULATE(movp);	EMULATE(cmpp3);	EMULATE(cvtpl);	EMULATE(cmpp4)
/* 38 */	EMULATE(editpc); EMULATE(matchc); EMULATE(locc); EMULATE(skpc)
#endif	VAX650 || VAX630
#endif	NEMUL > 0

/*
 * Trap and fault vector routines
 */ 
#define TRAP(a)	pushl $T_/**/a; jbr alltraps

/*
 * Ast delivery (profiling and/or reschedule)
 */
SCBVEC(astflt):
	TIM(0)
	pushl $0; TRAP(ASTFLT)
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
	cmpl	$vax$special_halt,(sp)
	bneq	1f			# not special
	addl2	$(2*4),sp		# pop the fault PC/PSL parameters
	jmp	vax$special_cont	#  before continuing
1:
	/*
	 *  What do you know, a REAL reserved/privileged instruction fault!
	 */
#endif	NEMUL > 0
	pushl $0; TRAP(PRIVINFLT)
SCBVEC(xfcflt): 
	TIM(0); pushl $0; TRAP(XFCFLT)
SCBVEC(resopflt):
	TIM(0); pushl $0; TRAP(RESOPFLT)
SCBVEC(resadflt):
	TIM(0); pushl $0; TRAP(RESADFLT)
SCBVEC(bptflt):
	TIM(0); pushl $0; TRAP(BPTFLT)
SCBVEC(compatflt):
	TIM(1); TRAP(COMPATFLT);
SCBVEC(tracep):
	TIM(0); pushl $0; TRAP(TRCTRAP)
#if	MACH_KDB
SCBVEC(kdbintr):
	TIM(0); pushl $0; TRAP(KDB_ENTRY)
#endif	MACH_KDB
SCBVEC(arithtrap):
	TIM(1); TRAP(ARITHTRAP)
SCBVEC(protflt): 
SCBVEC(transflt): 
	TIM(2)
#if	VAX8800
	/*
	 *	The VAX-8800 seems to have a bug... when a fault is caused
	 *	by an invalid system PTE the write intent bit can be wrong.
	 *	So, if the reason for the fault is an invalid system PTE,
	 *	then assume a read fault, this may generate an extra fault
	 *	but will produce correct faults (a write fault will only
	 *	occur if the system PTE is already available).
	 */
	cmpl	_cpu,$VAX_8800		# are we an 8800?
	bneq	0f			# no, forget hack.
	bitl	$2,(sp)			# PTE access?
	beql	0f			# no, do normal handling
	addl2	$4,sp			# yes, pop value off stack
	brb	1f
0:
#endif	VAX8800
	bitl	$4,(sp)+
	beql	1f
	TRAP(WRITE_FAULT)
1:	TRAP(READ_FAULT)
	.globl	_Xprotflt1		/* This is to keep emulation code happy */
_Xprotflt1:
#if	MACH_HUH
SCBVEC(protflt):
	TIM(2)
#if	NEMUL > 0
#if	VAX650 || VAX630
	/*
	 *  If we take a protection fault while the PC is in the instruction
	 *  emulation code, then it should be fielded by its fault handler
	 *  rather than directly by us.  This way, the handler can preserve the
	 *  appearance that the original instruction which was being emulated
	 *  was the one to receive the fault rather than its own code.
	 */
	cmpl	8(sp),$vax$emul_begin
	blssu	1f
	cmpl	8(sp),$vax$emul_end
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
#endif	VAX650 || VAX630
#endif	NEMUL > 0
	blbs	(sp)+,segflt
	TRAP(PROTFLT)
segflt:
	TRAP(SEGFLT)

/*
 * The following is called with the stack set up as follows:
 *
 *	  (sp):	Opcode
 *	 4(sp):	Instruction PC
 *	 8(sp):	Operand 1
 *	12(sp):	Operand 2
 *	16(sp):	Operand 3
 *	20(sp):	Operand 4
 *	24(sp):	Operand 5
 *	28(sp):	Operand 6
 *	32(sp):	Operand 7 (unused)
 *	36(sp):	Operand 8 (unused)
 *	40(sp):	Return PC
 *	44(sp):	Return PSL
 *	48(sp): TOS before instruction
 *
 * Each individual routine is called with the stack set up as follows:
 *
 *	  (sp):	Return address of trap handler
 *	 4(sp):	Opcode (will get return PSL)
 *	 8(sp):	Instruction PC
 *	12(sp):	Operand 1
 *	16(sp):	Operand 2
 *	20(sp):	Operand 3
 *	24(sp):	Operand 4
 *	28(sp):	Operand 5
 *	32(sp):	Operand 6
 *	36(sp):	saved register 11
 *	40(sp):	saved register 10
 *	44(sp):	Return PC
 *	48(sp):	Return PSL
 *	52(sp): TOS before instruction
 */

#endif	MACH_HUH
#if	NEMUL > 0
#else	NEMUL > 0
SCBVEC(emulate):
#if	VAX650 || VAX630
	movl	r11,32(sp)		# save register r11 in unused operand
	movl	r10,36(sp)		# save register r10 in unused operand
	cvtbl	(sp),r10		# get opcode
	addl2	$8,r10			# shift negative opcodes
	subl3	r10,$EMUTABLE,r11	# forget it if opcode is out of range
	bcs	noemulate
	movl	_emJUMPtable[r10],r10	# call appropriate emulation routine
	jsb	(r10)		# routines put return values into regs 0-5
	movl	32(sp),r11		# restore register r11
	movl	36(sp),r10		# restore register r10
	insv	(sp),$0,$4,44(sp)	# and condition codes in Opcode spot
	addl2	$40,sp			# adjust stack for return
	rei
noemulate:
	addl2	$48,sp			# adjust stack for
#endif	VAX650 || VAX630
	.word	0xffff			# "reserved instruction fault"
SCBVEC(emulateFPD):
	.word	0xffff			# "reserved instruction fault"
#endif	NEMUL > 0

	.globl	ALL_TRAPS
ALL_TRAPS:
alltraps:
	movpsl	-(sp)
	bitl	$PSL_IS,(sp)+
	bneq	1f
	mfpr	$USP,-(sp)
	calls	$0,_trap
	mtpr	(sp)+,$USP
	jbr	2f
1:	clrl	-(sp)
	calls 	$0,_trap
	tstl	(sp)+
2:
	COUNT(V_TRAP)
	addl2	$8,sp			# pop type, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	TSREI

SCBVEC(syscall):
	TIM(1)
	cmpl	(sp),$-9
	blss	alt_sys_call
#if	MACH_EMULATION
	/*
	 *	User space emulation of syscalls
	 */
	pushr	$(R0|R1|R2)
					# valid range: 0 - disp_count
	/* this test goes away when we take care of the -9-0 range */
	movl	12(sp),r0
	blss	norm_sys_call
					# check if emulated or not
	mfpr	$SSP,r1			# get the thread
	movl	THREAD_TASK(r1),r1	# get the task
	movl	EML_DISPATCH(r1),r1	# get the emulation structure
	beql	norm_sys_call		# no emulation!
	cmpl	DISP_COUNT(r1),r0	# a valid syscall ?
	blss	norm_sys_call
	movl	DISP_VECTOR(r1)[r0],r2	# get the emulation vector
	beql	norm_sys_call		# zero -> not emulated

	/*
	 * Emulated syscall: pass along the return program counter
	 * on the user stack;
	 * modify our stack so that we return to the
	 * user's handler itself and not to the call point.
	 */

	mfpr	$SSP,r1
	movab	8f, THREAD_RECOVER(r1)	# protection against bogus usp

	mfpr	$USP,r0			# get user stack
	movl	16(sp), -(r0)		# push return address
#ifdef	notdef
	/* We may decide later to also pass the trap number along,
	 * provided it is not too much hassle for the RTs
	 */
	movl	12(sp), -(r0)		# and trap number
#endif	notdef
	mtpr	r0, $USP
8:
	clrl	THREAD_RECOVER(r1)
	movl	r2,16(sp)		# change return address
	popr	$(R0|R1|R2)		# restore registers
	addl2	$4,sp			# pop syscall number
	TSREI
	
norm_sys_call:				# restore registers and stack
	popr	$(R0|R1|R2)

#endif	MACH_EMULATION
	pushl	$T_SYSCALL
	mfpr	$USP,-(sp); calls $0,_syscall; mtpr (sp)+,$USP
	COUNT(V_SYSCALL)
	addl2	$8,sp			# pop type, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	TSREI

	/*
	 *	Fast system call handler for native MACH system calls.
	 *	Doesn't worry about any of the stuff in syscall() except
	 *	for signals, and doesn't do much for those.
	 */
	.globl	_mach_trap_table
	.globl	_mach_trap_count
alt_sys_call:
2:	mnegl	(sp)+, r0		# Pop code; negate to get index.
	cmpl	r0, _mach_trap_count	# Check trap table bounds
	blss	1f
	movl	$KERN_FAILURE, r0	# OUT OF RANGE
	TSREI

	/*
	 *	Bring up Nth trap description.
	 *	Note that since we're using quadword move
	 *	here, things in the structure look reversed.
	 */
1:	movq	_mach_trap_table[r0], r2 # <flags,,length>, procedure
	movzwl	r2, r1			# length in bytes + 4
	prober	$0, r1, (ap)		# is arg list readable
	bneq	2f
	movl	$KERN_INVALID_ADDRESS, r0	# CANN'T READ ARGS
	TSREI

2:
	/*
	 *	Save the user's state properly in case a thread_mutate
	 *	is done.
	 */
	pushl	$0		# fake trap code
	pushl	$0		# fake trap type
	mfpr	$USP,-(sp);	# user's sp
	pushl	$0		# fake arg count
	pushr	$0xfff		# save user registers r0-r11
	pushl	$0		# pad
	pushl	fp		# user's fp
	pushl	ap		# user's ap
	callg	(ap), (r3)	# call routine

	movl	r0,3*4(sp)	# save syscall return in R0 save spot

	/*
	 *	Test whether a signal has been requested.  If it has,
	 *	schedule an AST, which will take effect as soon as we
	 *	leave the kernel.  (It's too messy to call psig() here.)
	 */
	mfpr	$SSP,r0		# get the thread
	cmpl	THREAD_EXIT_CODE(r0),$THREAD_EXIT	# abnormal exit?
	bneq	alt_call_AST	# take it with AST if so
	movl	UTASK(r0),r0	# point to task U-area
	movl	U_PROCP(r0),r0	# then to proc table slot
	beql	ACALLout	# skip if no proc table
	movzbl	P_CURSIG(r0),r1
	bisl2	P_SIG(r0),r1
	beql	ACALLout
alt_call_AST:
	mtpr	$3, $ASTLVL	# take AST trap (signal) on return to user

ACALLout:
	movl	(sp)+,ap	# pop ap
	movl	(sp)+,fp	# and fp
	addl2	$4,sp		# skip pad
	popr	$0xfff		# restore registers r0-r11
	addl2	$4,sp		# pop fake arg count
	mtpr	(sp)+,$USP	# restore user's sp
	addl2	$8,sp		# pop fake type and code
	TSREI	
/* 
 *	System page table is now allocated on the fly.
 */
	.text

/*
 * Initialization
 *
 * ipl 0x1f; mapen 0; scbb, pcbb, sbr, slr, isp, ksp not set
 */
	.data
	.globl	_cpu
_cpu:	.long	0
#if	MACH_KDB
	.globl	_esym
_esym:	.long	0
#endif	MACH_KDB
#if	MACH_LOAD
_loadpt:	.globl	_loadpt
	.long 	0
_loadpg:	.globl	_loadpg
	.long	0 
#endif	MACH_LOAD
	/*
	 *	The following variables are in the data segment so
	 *	that we don't lose their values when we clear
	 *	the bss segment later.
	 */
	.globl	_boothowto
	.globl	_bootdev
	.globl	_boot_regs
	.data
	.align	2
_boothowto:	.long	0
_bootdev:	.long	0
bootsp:		.long	0
_boot_regs:	.space	4*16

	/*
	 *	We need a "fake" PCB to hold the values of the other
	 *	stack pointers during initialization (before we have
	 *	a real PCB).  We need one per CPU.
	 */
	.set	FAKE_PCB_SIZE,(PCB_R0-PCB_KSP)	# 4 stack pointers only
_startup_pcb:
	.space	FAKE_PCB_SIZE

	.text
	.globl	start
start:
	.word	0
	mtpr	$0,$ICCS
	.globl	jmp_start
jmp_start:
try:	bbssi	$1,_start_lock,wait
	brb	0f
wait:	bbs	$1,_start_lock,wait
	brb	try
0:	bbssi	$0,_start_lock,1f
	brb	2f
1:	jmp	slave_start
2:
	movl	sp, bootsp
	moval	_boot_regs+4*15, sp
	pushr	$0x7fff
	movl	bootsp, sp
	movl	sp, _boot_regs+4*0xe
#if	MACH_LOAD
	moval	ZERO_PHYS, r1
	movl	r1,_loadpt
	addl2	r1, doajmp+2		#patch the jmp instruction address
	ashl	$-PGSHIFT,r1,_loadpg	#page address
#if	NCPUS > 1
	moval	cpu_number_zero,_Cpu_number_ptr	# set up for zero cpu number
#endif	NCPUS > 1
#endif	MACH_LOAD
/* set system control block base and system page table params */
	moval	_scb,r0
	mtpr	r0,$SCBB
	moval	eintstack,sp
	moval	_startup_pcb,r1		#address fake PCB
	mtpr	r1,$PCBB		#to store other stack pointers in
	mtpr	$0,$SSP			# no active thread yet.
	movl	r11,_boothowto
	movl	r10,_bootdev
#if	MACH_KDB
	movab	_end,_esym
	bbc	$2,r11,1f
	movl	r9,_esym
1:
#if	MACH_LOAD
	subl2	_loadpt,_esym
#endif	MACH_LOAD
	bbss	$31,_esym,0f
0:
#endif	MACH_KDB
	/*
	 *	Provide a clean traceback.
	 */
	clrl	fp
	clrl	ap

	calls	$0,_vax_init
#if	VAX820
#include <vaxnb/ka820.h>
	/*
	 * Ok, we have the cpu number.
	 * 8200's are special, since they may have not been reset properly.
	 * and if they are not, blow the system away by doing a reset.
	 */
	cmpl	_cpu, $VAX_820
	bneq	1f
	mfpr 	$BINID, r1		/* which Node am I */
	mull2	$0x2000, r1		/* 8k BIIC space */
	movl	0x2000000C(r1), r2	/* EINTRCSR -- Error Interrupt Control Register */
	bisl2	0x20000010(r1), r2	/* INTRDES  -- Interrupt Destination Register */
	beql	1f			/* have not been initialized yet -- good !! */
	pushal	0f
	calls	$1, _printf
	movl	$0x10000000, 0x20088000	/* BI RESET to Port controller */
1:
	.data
0:	.asciz	"\nYou forgot to reset the system before you did a reboot.\nNo problem, let me do it for you.\n"
	.text
#endif	VAX820
#if	defined(VAX630) || defined(VAX650) || defined(VAX6200)
#if	NEMUL > 0
	/*
	 * Adjust the page protections on the emulation code so that it is
	 * accessible from user mode. The emulation code begins with a 512
	 * byte buffer area to guarantee that nothing else occupies its first
	 * page and ends with a 511 byte buffer area to guarantee that nothing
	 * else occupies its last page.
	 */
	movl	$vax$emul_end+NBPG-1,r1		# compute last virtual address
	movl	$vax$emul_begin,r2		# compute first virtual address
#else	NEMUL > 0
	/*
	 *	For the Berkeley Emulation code, we need to make
	 *	the entire text segment readable by the user (or
	 *	we would have to rearrange the code so it was all
	 *	in one region).  If this was good enough for 4.3, we
	 *	can also live with it.  NOTE:  the last partial page
	 *	of text is not reprotected since we would end up with
	 *	data not writeable by the kernel.  However, it is
	 *	highly unlikely (impossible?) that the emulation code
	 *	will be in this page.
	 */
	movl	$_start_text,r2			# start of text segment
	movl	$_etext,r1			# end of text segment
#endif	NEMUL > 0
	bbcc	$31,r1,0f
0:	ashl	$-PGSHIFT,r1,r1			# convert to PFN
	bbcc	$31,r2,0f
0:	ashl	$-PGSHIFT,r2,r2			# convert to PFN
	mfpr	$SBR,r3				# get SPT base
1:
	bicl3	$PG_PROT,(r3)[r2],r0		# drop old protection code
	bisl3	$PG_URKR,r0,(r3)[r2]		# change protection to URKR
	aoblss	r1,r2,1b
#endif	defined(VAX630) || defined (VAX650) || defined(VAX6200)

	/*
	 *	Enable mapping, this works because the current p0
	 *	is set up so that addresses match the physical
	 *	matches.  XXX - This really only works for zero
	 *	based kernels, but is OK (probably due to prefetch).
	 *	This should be fixed.
	 */

	mtpr	$0,$TBIA
	mtpr	$1,$MAPEN
	jmp	*$0f
0:
	moval	eintstack,sp

#if	NCPUS > 1
	/*
	 *	Set up the cpu-number routine to return the model's
	 *	cpu number.  Set master_cpu also.
	 */
	jsb	set_cpu_number_ptr
	jsb	*_Cpu_number_ptr		# get the cpu number
	movl	r0,_master_cpu			# set master cpu number here
#if	VAX6200
	cmpl	_cpu, $VAX_6200
	bneq	1f
	movl	r0, _printing_cpu		# i.e. the master owns the console
1:
#endif	VAX6200
#endif	NCPUS > 1

#if	NEMUL > 0
#if	defined(VAX630) || defined(VAX650) || defined(VAX6200)
	/*
	 *	These two SCB vectors are reserved to DIGITAL and used by
	 *	the emulation code.
	 */
	moval	_scb,r1
	movl	$vax$emulate,0xc8(r1)
	movl	$vax$emulate_fpd,0xcc(r1)
#endif	defined(VAX630) || defined(VAX650) || defined(VAX6200)
#endif	NEMUL > 0

	mtpr	$1,$IPL			# Vax won't allow ipl 0 here
	calls	$0,_setup_main		# returns initial thread in r0

	/*
	 *	Set up initial PCB and change to kernel stack in context
	 *	of first thread
	 */

	movl	THREAD_PCB(r0),r1		# get virtual address of PCB

	movab	1f,PCB_PC(r1)			# initial pc
	jbr	_Load_context			# switch to initial thread

1:

/*
 *	Call "main" as though it were a system call handler.
 */
	calls	$0,_main		/* will never return */

	.globl	_start_init
_start_init:
	.word	0
/* reset reboot flags in r11 in case they've been adjusted */
 	movl	_boothowto,r11
/* proc[1] == /etc/init now running here; run icode */
	bbcci	$1,_start_lock,1f	# release the lock
1:
#if	NCPUS > 1
	pushl	r11
	bicl2	$(~RB_UNIPROC), (sp)
	calls	$1, _start_processors	# do the obvious
#endif	NCPUS > 1
	mfpr	$SSP,r0			# get the current thread
	addl3	THREAD_KERNEL_STACK(r0),$KERNEL_STACK_SIZE,sp
					# clear the stack, as if trapping
					# from user
	movl	UTHREAD(r0),r0
	movl	sp,U_AR0(r0)
	pushl	$PSL_CURMOD|PSL_PRVMOD	/* PSL */
	pushl	$0			/* PC */
	pushl	$0			/* CODE */
	pushl	$T_SYSCALL		/* TYPE */
	pushl	$0			/* user SP */
	calls	$0,_load_init_program
	mtpr	(sp)+,$USP		/* pop user SP */
	tstl	(sp)+			/* pop TYPE */
	tstl	(sp)+			/* pop CODE */
	rei

/* signal trampoline code: it is known that this code takes exactly 19 bytes */
/* in ../vax/pcb.h and in the movc3 above */
/* and in setregs() in the execx system call */
	.globl	_nsigcode
	.globl	_sigcode
_sigcode:
_nsigcode:
sigcode:
	calls	$4,8(pc)	# params pushed by sendsig
	movl	sp,ap		# calls frame built by sendsig
	chmk	$103		# cleanup mask and onsigstack
	halt			# sigreturn() does not return!
	.word	0x3f		# registers 0-5
	callg	(ap),*16(ap)	# call the signal handler
	ret			# return to code above

	.data
foo_stack:
	.space	512
efoo_stack:
	.text
slave_start:
#if	MACH_LOAD
	movl	_loadpt,r1
#else	MACH_LOAD
	clrl	r1
#endif	MACH_LOAD
	moval	_scb-0x80000000(r1),r0
	mtpr	r0,$SCBB
	/* go into mapped mode */
	mtpr	_vax_sbr,$SBR
	mtpr	_vax_slr,$SLR
	mtpr	_vax_vsbr,$P0BR			# double map for jmp below
	mtpr	_vax_slr,$P0LR

	moval	_startup_pcb,r1		#address fake PCB
	mtpr	r1,$PCBB		#to store other stack pointers in
	mtpr	$0,$SSP			# no active thread yet.
	mtpr	$0,$TBIA; mtpr $1,$MAPEN; jmp *$0f; 0:
	moval	efoo_stack,sp
	CPU_NUMBER_R0				# get the cpu number
	movl	_interrupt_stack[r0],sp		# virtual stack
	addl2	$INTSTACK_SIZE,sp		# start and end
	bbcci	$1,_start_lock,1f		# release the lock
1:
	mtpr	$HIGH,$IPL			# NOT 0x1f
	calls	$0,_slave_main
	halt
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
	mfpr	$IPL,r1
	mtpr	$BLOCK,$IPL
	movl	4(ap),r3
	movl	8(ap),r4
	movl	_scb+MCKVEC,r2
	movab	9f+INTSTK,_scb+MCKVEC
	bbc	$0,r4,1f; tstb	(r3)
1:	bbc	$1,r4,1f; tstw	(r3)
1:	bbc	$2,r4,1f; tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	movl	r2,_scb+MCKVEC
8:	mtpr	r1,$IPL
	ret
	.align	2
9:
	casel	_cpu,$1,$VAX_MAX
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
	.word	1f-0b		# 10 is 650
	.word	1f-0b		# 11 is ka62a
5: 
6:
	mtpr	$0xf,$MCESR
	brb	1f
7:
	mtpr	$0,$EHSR
	brb	1f
8:
	mtpr	$0,$SBIFS
	brb	1f
4:
#include <vaxnb/ka88.h>
	mtpr	$0,$TOSTS
	mtpr	$0,$MCSTS
1:
	addl2	(sp)+,sp		# discard mchchk trash
	movab	2b,(sp)
	rei

/*
 * update profiling information for the user
 * addupc(pc, &u.u_prof, ticks)
 */
ENTRY(addupc, 0)
	movl	8(ap),r2		# &u.u_prof
	subl3	PR_OFF(r2),4(ap),r0	# corrected pc
	blss	9f
	extzv	$1,$31,r0,r0		# logical right shift
	extzv	$1,$31,PR_SCALE(r2),r1	# ditto for scale
	emul	r1,r0,$0,r0
	ashq	$-14,r0,r0
	tstl	r1
	bneq	9f
	bicl2	$1,r0
	cmpl	r0,PR_SIZE(r2)		# length
	bgequ	9f
	addl2	PR_BASE(r2),r0		# base
	cmpl	r0,$(0x80000000-1)	# address out of user space?
	bgequ	7f			# buffer not writable if so
	mfpr	$SSP,r3			# point to current thread
	movab	8f,THREAD_RECOVER(r3)	# set recovery address to catch bad memory addr
	addw2	12(ap),(r0)		# add in tick count
	clrl	THREAD_RECOVER(r3)	# clear recovery address
9:
	ret
8:
					# buffer not writeable
	clrl	THREAD_RECOVER(r3)	# clear recovery address
7:
	clrl	PR_SCALE(r2)
	ret

/*
 * Copy a null terminated string from the user address space into
 * the kernel address space.
 *
 * copyinstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyinstr, R6|R11)
	mfpr	$SSP,r11		# get current thread
	movab	8f,THREAD_RECOVER(r11)	# set page-fault recovery address
	movl	12(ap),r6		# r6 = max length
	jlss	8f
	movl	4(ap),r1		# r1 = user address
	mcoml	_page_mask,r3
	bicl3	r3,r1,r2		# r2 = bytes on first page
	subl3	r2,_page_size,r2
	movl	8(ap),r3		# r3 = kernel address
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
					# last byte must be < &u
	addl3	r1,r2,r0		# point at first byte off end
 	cmpl	r0,$0x80000000	# must be user address
	bgtru	8f			# fail if not
	subl2	r2,r6			# update bytes left count
#ifdef	NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3f
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3f
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	_page_size,r2		# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9f
3:
	tstl	16(ap)			# return length?
	beql	4f
	subl3	r6,12(ap),r6		# actual len = maxlen - unused pages
	subl2	r0,r6			#	- unused on this page
	addl3	$1,r6,*16(ap)		#	+ the null byte
4:
	subl2	r0,r2			# r2 = number of bytes to move
	subl2	r2,r1			# back up pointer updated by `locc'
	incl	r2			# copy null byte as well
	movc3	r2,(r1),(r3)		# copy in last piece
	clrl	r0			# redundant
	tstl	r11
	beql	0f
	clrl	THREAD_RECOVER(r11)
0:
	ret
8:
	movl	$EFAULT,r0
9:
	tstl	16(ap)
	beql	1f
	subl3	r6,12(ap),*16(ap)
1:
	tstl	r11
	beql	0f
	clrl	THREAD_RECOVER(r11)
0:
	ret

/*
 * Copy a null terminated string from the kernel
 * address space to the user address space.
 *
 * copyoutstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyoutstr, R6|R11)
	mfpr	$SSP,r11
	movab	8b,THREAD_RECOVER(r11)
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = kernel address
	movl	8(ap),r3		# r3 = user address
	mcoml	_page_mask,r4
	bicl3	r4,r3,r2		# r2 = bytes on first page
	subl3	r2,_page_size,r2
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
					# last byte must be < &u
	addl3	r3,r2,r0		# point at first byte off end
	cmpl	r0,$0x80000000	# must be user address
	bgtru	8b			# fail if not
	subl2	r2,r6			# update bytes left count
#ifdef	NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	_page_size,r2		# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b

/*
 * Copy a null terminated string from one point to another in
 * the kernel address space.
 *
 * copystr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copystr, R6|R11)
	clrl	r11			# don't set recovery address
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = src address
	movl	8(ap),r3		# r3 = dest address
1:
	movzwl	$65535,r2		# r2 = bytes in first chunk
	cmpl	r6,r2			# r2 = min(bytes in chunk, length left);
	jgeq	2f
	movl	r6,r2
2:
	subl2	r2,r6			# update bytes left count
#ifdef	NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b
	.align	1
JSBENTRY(Current_Task, R1)
	mfpr	$SSP, r0
	movl	THREAD_TASK(r0), r0
	rsb

	.globl	_ALLOW_FAULT_START
_ALLOW_FAULT_START:
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
	 *      Make the simple case of a short move really efficent.
	 */
	cmpl	r5,$65535		# one movc3?
	bgtru	0f			# no
	movab	-1(r1)[r5],r0		# source end must be non-negative
	blss	copy_out_of_range

	movc3	r5,(r1),(r3)		# do the copy
/*	clrl	r0			# success (movc3 leaves r0 0) */
	rsb
	.globl	_FAULT_ERROR
_FAULT_ERROR:
	movl	$EFAULT,r0		# bad copy
	rsb
	/*
	 *	Assume that user addresses == entire non-negative
	 *	address range
	 */
0:	tstl	r1			# source start must be non-negative
	jlss	copy_out_of_range	# fail if not in user space
	addl3	r1,r5,r0		# source end (last byte) must be non-negative
	decl	r0
	jlss	copy_out_of_range	# fail if not in user space
copy_common:
	pushr	$(R6|R7)		# save registers
	mfpr	$SSP,r7
	movab	copy_fail,THREAD_RECOVER(r7)
	movl	r5,r6			# save total length
	jleq	3f			# skip all if 0
1:
	movl	$65535,r5		# max length for movc3
	cmpl	r6,r5
	jleq	2f			# if length <= max, do it all
	subl2	r5,r6			# if too big, do only part
	movc3	r5,(r1),(r3)		# (advances r1,r3)
	jbr	1b
2:
	movc3	r6,(r1),(r3)		# move the rest
3:
	clrl	r0			# be sure to work for 0 bytes.
copy_exit:
	clrl	THREAD_RECOVER(r7)
	popr	$(R6|R7)
	rsb

copy_fail:
	movl	$EFAULT,r0		# fault
	jbr	copy_exit

copy_out_of_range:
	movl	$EFAULT,r0
	rsb

/* 
 * Copy specified amount of data from kernel to the user space
 * Copyout(from, to, len)
 *	r1 == from (kernel source address)
 *	r3 == to (user destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyout, R1|R3|R5)
	cmpl	r5,$65535		# one movc3?
	bgtru	0f			# no
	movab	-1(r3)[r5],r0		# source end must be non-negative
					# If source end is positive, but
					# source start is negative,
					# source start must be >= 0xffff0000
					# which is never valid; thus we do
					# not have to test it.
	blss	copy_out_of_range
	movc3	r5,(r1),(r3)		# do the copy
/*	clrl	r0			# success (movc3 leaves r0 0) */
	rsb
	/*
	 *	Assume that user addresses == entire non-negative
	 *	address range
	 */
0:	tstl	r3			# source start must be non-negative
	jlss	copy_out_of_range	# fail if not in user space
	addl3	r3,r5,r0		# source end (last byte) must be non-negative
	decl	r0
	jlss	copy_out_of_range	# fail if not in user space
	jbr	copy_common

	.globl	_ALLOW_FAULT_END
_ALLOW_FAULT_END:


/*
 * non-local goto's
 */
#ifdef	notdef		/* this is now expanded completely inline */
	.align	1
JSBENTRY(Setjmp, R0)
	movl	fp,(r0)+	# current stack frame
	movl	(sp),(r0)	# resuming pc
	clrl	r0
	rsb
#endif

#define PCLOC 16	/* location of pc in calls frame */
#define APLOC 8		/* location of ap,fp in calls frame */
	.align	1
JSBENTRY(Longjmp, R0)
	movl	(r0)+,newfp	# must save parameters in memory as all
	movl	(r0),newpc	# registers may be clobbered.
1:
	cmpl	fp,newfp	# are we there yet?
	bgequ	2f		# yes
	moval	1b,PCLOC(fp)	# redirect return pc to us!
	ret			# pop next frame
2:
	beql	3f		# did we miss our frame?
	pushab	4f		# yep ?!?
	calls	$1,_panic
3:
	movl	newpc,r0	# all done, just return to the `setjmp'
	TS

	.data
newpc:	.space	4
newfp:	.space	4
4:	.asciz	"longjmp"
	.text

#if	NCPUS > 1
/*
 *	Since there are as many ways of getting the CPU number as there are
 *	multiprocessor Vaxen, we do an indirect jsb through this pointer
 *	to call the right routine.
 */
	.data
	.globl	_Cpu_number_ptr			# address of per-cpu routine
_Cpu_number_ptr:
	.long	cpu_number_zero			# starts out as 0
	.text

 # Return 0 for single CPU configurations.
cpu_number_zero:
	clrl	r0
	rsb

cpu_number_780:
#if	NMACH_MPM > 0
 # Look in the multi-port memory on the 780 (if we have it).
	.data
	.globl	_mpm_port_addr
_mpm_port_addr:
	.long	zero
	.text
	extzv	$0,$2,*_mpm_port_addr,r0	# low 2 bits
#else	NMACH_MPM > 0
	clrl	r0
#endif	NMACH_MPM > 0
	rsb

 # There's a processor register on the 8200.
cpu_number_8200:
	mfpr	$BINID,r0
	rsb

 # And it's hidden somewhere else on the 8800.
cpu_number_8800:
	mfpr	$SID,r0
	extzv	$23,$1,r0,r0			# it's in bit 23
	rsb

cpu_number_6200:
#if	VAX6200
	.globl	_ka62a_csr1
	extzv	$0,$4,*_ka62a_csr1,r0			# low 4 bits 
#else	VAX6200
	clrl	r0
#endif	VAX6200
	rsb

zero:	.long	0

/*
 *	Call this just before going virtual, to set the CPU number routine.
 */
set_cpu_number_ptr:
	movl	_cpu,r0
	movl	cpu_number_routine-4[r0],_Cpu_number_ptr
	rsb

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
 # Dummy set_cpu_number to avoid changing the world in case I come up with a
 # better solution.
	.globl	_set_cpu_number
_set_cpu_number:
	.word	0
	ret

#endif	NCPUS > 1

#if	VAX6200
#include <vaxnb/ka62a.h>
	.globl	_ka62a_csr1_quad_iqo_hack
	.globl	_ka62a_csr1
	.align 1
_ka62a_csr1_quad_iqo_hack:
	.word 	0x0
	movl	*_ka62a_csr1, r2
	bisl3	$(ka62aCSR1_FCI | ka62aCSR1_FMISS), r2, r0
	bicl3	$(ka62aCSR1_FCI | ka62aCSR1_FMISS), r2, r1
	bisl2	$ka62aCSR1_DLCKOUTEN, r1
	movq	r0, *_ka62a_csr1
	ret

	.globl	_ka62a_rtm
_ka62a_rtm:
	.word 0x0
	CPU_NUMBER_R0
	movl	_interrupt_stack[r0],r0		# virtual stack
	addl2	$INTSTACK_SIZE,r0		# start and end
	bbcc	$31, r0, 0f
0:	ashl	$-PGSHIFT, r0, r1		# page offset
	movl	*_vax_vsbr[r1], r2		# page num
	bicl2	$~0x1fffff, r2			# clear pg_xx
	ashl	$PGSHIFT, r2, sp
	mtpr	$0, $MAPEN			# will this help?
	halt
#endif	VAX6200

	.globl	_Load_context
_Load_context:
	COUNT(V_SWTCH)
	extzv	$0,$30,THREAD_PCB(r0),r0	# strip out high bits of PCB
	extzv	$9,$21,r0,r1			# get page number
	insv	*_vax_vsbr[r1],$9,$21,r0	# insert physical page number
						# in proper place
	mtpr	r0,$PCBB			# put physical address in PCB
						# register
	ldpctx					# switch to new context
	rei

	.align	1
JSBENTRY(Fuword, R0|R2)
	tstl	r0			# source must be non-negative
	blss	fs_bad
	mfpr	$2,r2
	movab	fs_fail,THREAD_RECOVER(r2)
	movl	(r0),r0
	clrl	THREAD_RECOVER(r2)
	rsb
	.align	1
JSBENTRY(Suword, R0|R1|R2)
	tstl	r0			# dest must be non-negative
	blss	fs_bad
	mfpr	$2,r2
	movab	fs_fail,THREAD_RECOVER(r2)
	movl	r1,(r0)
	clrl	THREAD_RECOVER(r2)
	clrl	r0
	rsb
fs_fail:
	clrl	THREAD_RECOVER(r2)
fs_bad:	movl	$-1,r0
	rsb

/*
 * kernacc - check for kernel access privileges
 *
 * We can't use the probe instruction directly because
 * it ors together current and previous mode.
 */
 ENTRY(kernacc, 0)
	movl	4(ap),r0	# virtual address
	bbcc	$31,r0,kacc1
	bbs	$30,r0,kacerr
	movl	_Sysmap, r2
	mfpr	$SLR,r3
	brb	kacc2
kacc1:
	bbsc	$30,r0,kacc3
	mfpr	$P0BR,r2	# user P0
	mfpr	$P0LR,r3
	brb	kacc2
kacc3:
	mfpr	$P1BR,r2	# user P1 (stack)
	mfpr	$P1LR,r3
kacc2:
	addl3	8(ap),r0,r1	# ending virtual address
	addl2	$NBPG-1,r1
	ashl	$-PGSHIFT,r0,r0
	ashl	$-PGSHIFT,r1,r1
	bbs	$31,4(ap),kacc6
	bbc	$30,4(ap),kacc6
	cmpl	r0,r3		# user stack
	blss	kacerr		# address too low
	brb	kacc4
kacc6:
	cmpl	r1,r3		# compare last page to P0LR or SLR
	bgtr	kacerr		# address too high
kacc4:	
	movl	(r2)[r0],r3
	bbc	$31,4(ap),kacc4a
	bbc	$31,r3,kacerr	# valid bit is off
kacc4a:
	cmpzv	$27,$4,r3,$1	# check protection code
	bleq	kacerr		# no access allowed
	tstb	12(ap)
	bneq	kacc5		# only check read access
	cmpzv	$27,$2,r3,$3	# check low 2 bits of prot code
	beql	kacerr		# no write access
kacc5:
	aoblss	r1,r0,kacc4	# next page
	movl	$1,r0		# no errors
	ret
kacerr:
	clrl	r0		# error
	ret
