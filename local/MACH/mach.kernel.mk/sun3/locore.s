/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	locore.s,v $
 * Revision 2.11  91/05/24  15:42:18  mbj
 * 	Support emulation of negative system calls.
 * 	[91/05/21            mbj]
 * 	Change emulation entry sequence to match the pure kernel.
 * 	Specifically, push the pc, sr & syscall # onto the user's stack.
 * 	[91/05/20            mbj]
 * 
 * Revision 2.10  90/04/28  00:02:50  jjc
 * 	Changed Mach emulation code in syscall() to skip FPA
 * 	exception code on return to user.
 * 	[90/04/03            jjc]
 * 
 * Revision 2.9  90/02/21  13:40:03  mrt
 * 	Fix copy{in,out} bug.
 * 	[90/02/21            rwd]
 * 
 * Revision 2.8  90/02/19  15:47:50  jjc
 * 	Faster copyin/copyout.
 * 	[90/02/12            rwd]
 * 
 * Revision 2.7  89/03/09  21:36:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  19:44:16  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.5  88/08/03  15:44:44  dorr
 * Fixed log message.
 * 
 * Revision 2.4  88/08/03  15:36:24  dorr
 * fix typeo in syscall emulation path -- d1->d0
 * 
 *  8-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Eliminate uses of _cnt.
 *
 * 16-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed syscall() to test FPA_USED bit in pcb_fpa_flags to
 *	see if FPA is being used.
 *
 * 28-Jan-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed syscall() to set syscall number to 63 (nosys) if
 *	fault during a system call, and then call _syscall().
 *
 * 27-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Initialize stack for start_init to value that a real syscall
 *	would see.
 *
 * 26-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Don't flush cacr at syscall end; do it in load_context.
 *
 * 12-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added savefppregs.
 *
 * ??-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to syscall() to return from FPA exception.
 *	Added {on,off}_enablereg().
 *
 * 10-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Don't bother including "../sundev/mbvar.h" because it
 *	does not define anything we need in here.
 *
 * 20-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added changes for MACH.
 *
 * 13-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added setcacheenable.
 *
 * 16-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added INCLUDE_VERSION definition.
 *	[ V5.1(F7) ]
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Undef LOCORE before forcing its definition (just in case it was
 *	already defined).
 *
 * 22-Oct-86  David Golub (dbg)	at Carnegie-Mellon University
 *	Removed MACH_SHM.  Made MACH work.  Check for writing
 *	into U area (it is in user space if MACH is off).
 *
 * 12-Sep-86  David Golub and Jonathan J. Chew (dbg and jjc)
 *		at Carnegie-Mellon University
 *	Added kernel-debugger support - always load symbols,
 *	and add 'k' to boot switches.
 *
 *  9-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach:
 *	1) Conditionalized initialization of system page tables
 *	   and mapping of u-area on whether MACH is off.
 *	2) Added calls to "sun_init" and "setup_main" for Mach VM.
 *	3) Replaced all occurences of "romp" with "sunromp" to avoid
 *	   name conflict with IBM PC RT "romp".
 *	4) Replaced PCB_P0LR with PCB_FLAG from thread.
 *	5) Catch faults and place the recovery address in thread
 *	   structure rather than u-area.
 *	6) Added "master_idle".
 *	7) Conditionalized LED update in level 5 interrupt handler
 *	   on whether MACH is off.
 *	8) Added string copying routines, "copystr", "copyinstr",
 *	   and "copyoutstr".
 *	9) Run off of interrupt stack until just before main().
 *
 */
	.data
	.asciz	"@(#)locore.s 1.1 86/02/03 Copyr 1985 Sun Micro"
	.even
	.text
/*
 *	Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <mach_kdb.h>
#include <mach_emulation.h>
#include <kern/syscall_emulation.h>
#undef	LOCORE
#define LOCORE
#include <sys/param.h>
#include <sys/vmparam.h>
#include <sys/errno.h>

/* Don't need anything from this include file <sundev/mbvar.h> */

#include <sun3/asm_linkage.h>
#include <sun3/buserr.h>
#include <sun3/clock.h>
#include <sun3/cpu.h>
#include <sun3/diag.h>
#include <sun3/enable.h>
#include <sun3/interreg.h>
#include <sun3/memerr.h>
#include <sun3/mmu.h>
#include <sun3/pcb.h>
#include <sun3/psl.h>
#include <sun3/reg.h>
#include <sun3/trap.h>
#include <fpa.h>
#if	NFPA > 0
#include <sundev/fpareg.h>
#endif	NFPA > 0

#include <sun3/cpu.h>

#define COUNT(x)
#include <assym.s>

/* 
 * Absolute external symbols
 */
	.globl	_DVMA
_DVMA	= 0x0FF00000	| 28 bit virtual address for system DVMA

/*
 * The interrupt stack.  This must be the first thing in the data
 * segment (other than an sccs string) so that we don't stomp
 * on anything important during interrupt handling.  We get a
 * red zone below this stack for free when the kernel text is
 * write protected.  Since the kernel is loaded with the "-N"
 * flag, we pad this stack by a page because when the page
 * level protection is done, we will lose part of this interrupt
 * stack.  Thus the true interrupt stack will be at least MIN_INTSTACK_SZ
 * bytes and at most MIN_INTSTACK_SZ+NBPG bytes.  The interrupt entry
 * code assumes that the interrupt stack is at a lower address than
 * both eintstack and the kernel stack in the u area.
 */
#define MIN_INTSTACK_SZ	0x800
	.data
	.globl _intstack, eintstack
_intstack:				| bottom of interrupt stack
	. = . + NBPG + MIN_INTSTACK_SZ
eintstack:				| end (top) of interrupt stack


	.data
	.globl	_master_idle
_master_idle:
	.long	0

#if	MACH_KDB
/*
 *	End of symbol table loaded by boot
 */
	.data
	.globl	_esym
_esym:
	.long	0
#endif	MACH_KDB

/*
 * Software copy of system enable register
 * This is always atomically updated
 */
	.data
	.globl	_enablereg
_enablereg:	.byte	0			| UNIX's system enable register
	.even
	.text

/*
 * Macro to save all registers and switch to kernel context
 * 1: Save and switch context
 * 2: Save all registers
 * 3: Save user stack pointer
 */
#define SAVEALL() \
	clrw	sp@-;\
	moveml	#0xFFFF,sp@-;\
	movl	usp,a0;\
	movl	a0,sp@(R_SP)

/* Normal trap sequence */
#define TRAP(type) \
	SAVEALL();\
	movl	#type,sp@-;\
	jra	trap

/*
 * System initialization
 * UNIX receives control at the label `_start' which
 * must be at offset zero in this file; this file must
 * be the first thing in the boot image.
 */
	.text
	.globl	_start
_start:
/*
 * We should reset the world here, but it screws the UART settings.
 *
 * Do a halfhearted job of setting up the mmu so that we can run out
 * of the high address space.  We do this by reading the current pmegs
 * for the `real' locations and using them for the virtual relocation.
 * NOTE - Assumes that the real and virtual locations have the same
 * segment offsets from 0 and KERNELBASE!!!
 *
 * We make the following assumptions about our environment
 * as set up by the monitor:
 *
 *	- we have enough memory mapped for the entire kernel + some more
 *	- all pages are writable
 *	- the last pmeg [SEGINV] has no valid pme's
 *	- the highest virtual segment has a pmeg allocated to it
 *	- when the monitor's sunromp->v_memorybitmap points to a zero
 *	    - each low segment i is mapped to use pmeg i
 *	    - each page map entry i maps physical page i
 *	- the monitor's scb is NOT in low memory
 *	- on systems w/ ecc memory, that the monitor has set the base
 *	    addresses and enabled all the memory cards correctly
 *
 * We will set the protection properly in startup().
 */

/*
 * Before we set up the new mapping and start running with the correct
 * addresses, all of the code must be carefully written to be position
 * independent code, since we are linked for running out of high addresses,
 * but we get control running in low addresses.  We continue to run
 * off the stack set up by the monitor until after we set up the u area.
 */
#if	MACH_KDB
	movl	d0, d5			| save load end address in a
					| safe place
#endif	MACH_KDB
	movw	#SR_HIGH,sr		| lock out interrupts
	moveq	#FC_MAP,d0
	movc	d0,sfc			| set default sfc to FC_MAP
	movc	d0,dfc			| set default dfc to FC_MAP
	moveq	#KCONTEXT,d0	
	movsb	d0,CONTEXTBASE		| now running in KCONTEXT

leax:	lea	pc@(_start-(leax+2)),a2	| a2 = true current location of _start
	movl	a2,d2			| real start address
	andl	#SEGMENTADDRBITS,d2	| clear extraneous bits
	orl	#SEGMENTBASE,d2		| set to segment map offset
	movl	d2,a2			| a2 = real adddress map pointer

	movl	#_start,d3		| virtual start address
	andl	#SEGMENTADDRBITS,d3	| clear extraneous bits
	orl	#SEGMENTBASE,d3		| set to segment map offset
	movl	d3,a3			| a3 = virtual address map pointer

/*
 * Compute the number used to control the dbra loop.
 * By doing ((end - 1) - KERNELBASE) >> SGSHIFT we
 * essentially get ctos(btoc(end - KERNELBASE)) - 1
 * where the - 1 is adjustment for the dbra loop.
 */
#if	MACH_KDB
	movl	d5,d1			| get last loaded address + 1
	subql	#1,d1			| -1
					| assume 'real' kernel base is 0
#else	MACH_KDB
	movl	#_end-1,d1		| get virtual end
	subl	#KERNELBASE,d1		| subtract off base address
#endif	MACH_KDB
	movl	#SGSHIFT,d0		| load up segment shift value
	lsrl	d0,d1			| d1 = # of segments to map - 1

/*
 * Now loop through the real addresses where we are loaded and set
 * up the virtual segments for where we want to be virtually to be the same.
 */
0:
	movsb	a2@,d0			| get real segno value
	movsb	d0,a3@			| set virtual segno value
	addl	#NBSG,a2		| bump real address map pointer
	addl	#NBSG,a3		| bump virtual address map pointer
	dbra	d1,0b			| decrement count and loop

	movl	#CACHE_CLEAR+CACHE_ENABLE,d0
	movc	d0,cacr			| clear (and enable) the cache

	jmp	cont:l			| force non-PC rel branch
cont:

/*
 * PHEW!  Now we are running with correct addresses
 * and can use non-position independent code.
 */

#if	MACH_KDB
/*
 *	Store the (relocated) address of the end of the symbol table.
 */
	addl	#KERNELBASE,d5		| relocate esym to the loaded
					| address
	movl	d5,_esym		| and save it.
#endif	MACH_KDB

/*
 * Now map in our own copies of the eeprom, clock, memory error
 * register, interrupt control register, and ecc regs into the
 * last virtual segment which already has a pmeg allocated to it
 * when we get control from the monitor.
 */
	lea	EEPROM_ADDR_MAPVAL,a0	| map in eeprom
	movl	#EEPROM_ADDR_PTE,d0
	movsl	d0,a0@

	lea	CLKADDR_MAPVAL,a0	| map in clock
	movl	#CLKADDR_PTE,d0
	movsl	d0,a0@

	lea	MEMREG_MAPVAL,a0	| map in memory error register
	movl	#MEMREG_PTE,d0
	movsl	d0,a0@

	lea	INTERREG_MAPVAL,a0	| map in interrupt control reg
	movl	#INTERREG_PTE,d0
	movsl	d0,a0@

	lea	ECCREG_MAPVAL,a0	| map in ecc regs
	movl	#ECCREG_PTE,d0
	movsl	d0,a0@

/*
 * Check to see if memory was all mapped in correctly.  On versions >= 'N',
 * if ROMP_ROMVEC_VERSION is greater than zero, then ROMP_MEMORYBITMAP
 * contains the address of a pointer to an array of bits
 * If this pointer is non-zero, then we had some bad pages
 * Until we get smarter, we give up if we find this condition.
 */
	tstl	ROMP_ROMVEC_VERSION
	ble	1f			| field is <= zero, don't do next test
	movl	ROMP_MEMORYBITMAP,a0
	tstl	a0@
	jeq	1f			| pointer is zero, all ok
	pea	0f
	jsr	_halt
	addqw	#4,sp			| in case they really want to try this
	.data
0:	.asciz "Memory bad"
	.even
	.text
1:


| zero first page which will be scb/usrpt page
	movl	#((NBPG-1)/4),d0	| dbra byte count
	lea	0,a0			| start at zero
0:	clrl	a0@+			| clear long word and increment
	dbra	d0,0b			| decrement count and loop

| zero bss (using low addresses)
	movl	#_end-KERNELBASE-1,d0
	lea	_edata-KERNELBASE,a0	| get bss start
	subl	a0,d0			| get bss length
	lsrl	#2,d0			| shift for long count
0:	clrl	a0@+			| clear long word and increment
	dbra	d0,0b			| decrement count and loop

/*
 * Set up the stack.  From now we continue to use the 68020 ISP
 * (interrupt stack pointer).  This is because the MSP (master
 * stack pointer) as implemented by Motorola is too painful to
 * use since we have to play lots of games and add extra tests
 * to set something in the master stack if we running on the
 * interrupt stack and we are about to pop off a throw away
 * stack frame.
 *
 * Thus it is possible to having naming conflicts.  In general,
 * when the term "interrupt stack" (no pointer) is used, it
 * is referring to the software implemented interrupt stack
 * and the "kernel stack" is the per user kernel stack in the
 * user area.  We handling switching between the two different
 * address ranges upon interrupt entry/exit.  We will use ISP
 * and MSP if we are referring to the hardstack stack pointers.
 */
setstack:
	lea	eintstack,sp | set to top of interrupt stack

	/*
	 * See if we have a 68881 attached.
	 * _fppstate is 0 if no fpp,
	 * 1 if fpp is present and enabled,
	 * and -1 if fpp is present but disabled
	 * (not currently used).
	 */
	.data
	.globl	_fppstate
_fppstate:	.word 1		| mark as present until we find out otherwise
	.text

flinevec = 0x2c
fppcheck:
	movsb	ENABLEREG,d0		| get the current enable register
	orb	#ENA_FPP,d0		| or in FPP enable bit
	movsb	d0,ENABLEREG		| set in the enable register
	movl	sp,a1			| save sp in case of fline fault
	movc	vbr,a0			| get vbr
	movl	a0@(flinevec),d1	| save old f line trap handler
	movl	#ffault,a0@(flinevec)	| set up f line handler
	frestore fnull
	jra	1f

fnull:	.long	0			| null fpp internal state

ffault:					| handler for no fpp present
	movw	#0,_fppstate		| set global to say no fpp
	andb	#~ENA_FPP,d0		| clear ENA_FPP enable bit
	movl	a1,sp			| clean up stack

1:
	movl	d1,a0@(flinevec)	| restore old f line trap handler
	movsb	d0,ENABLEREG		| set up enable reg
	movb	d0,_enablereg		| save soft copy of enable register

	jsr	_sun_init
	jsr	_setup_main
/*
 * Set context for initial thread
 */
	movl	d0,a0			| thread
	movl	a0@(THREAD_TASK),a1	| thread->task
	movl	a1@(TASK_MAP),a1	| thread->task->map
	movl	a1@(VM_MAP_PMAP),a1	| thread->task->map->pmap
	movl	a1@(PMAP_CTX),a1	| thread->task->map->pmap->ctx (phew!)
	movw	a1@(CTX_CONTEXT),d1	| put context number in d1
	movsb	d1,CONTEXTBASE		| set up the context

/*
 * Switch to kernel stack
 */
	movl	a0@(THREAD_PCB),a1	| thread->pcb
	movl	a1@(PCB_KSP),sp		| set up kernel stack
	jsr	_main			| simulate interrupt -> main
/*
 *	call to main never returns.  Instead, process 1 starts up here
 *	to load /etc/init over itself.
 */
	.globl	_sun_load_init_program

ENTRY(start_init)
	movl	#USRSTACK,a0		| init user stack pointer
	movl	a0,usp
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a1@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread on cpu
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a0	| got pcb and WE KNOW it is
	lea	a0@(KERNEL_STACK_SIZE), sp | the ksp base 
	clrw	sp@-			| dummy fmt & vor
	movl	#USRTEXT,sp@-		| pc (will be changed)
	movw	#SR_USER,sp@-		| sr
	lea	0,a6			| stack frame link 0
	SAVEALL()			| rest of registers
	jsr	_sun_load_init_program	| load /etc/init
	clrl	d0			| fake return value from trap
	jra	rei

/*
 * Entry points for interrupt and trap vectors
 */
	.globl	buserr, addrerr, coprocerr, fmterr, illinst, zerodiv, chkinst
	.globl	trapv, privvio, trace, emu1010, emu1111, spurious
	.globl	badtrap, brkpt, floaterr, level2, level3, level4, level5
	.globl	_level7, errorvec

buserr:
	TRAP(T_BUSERR)

addrerr:
	TRAP(T_ADDRERR)

coprocerr:
	TRAP(T_COPROCERR)

fmterr:
	TRAP(T_FMTERR)

illinst:
	TRAP(T_ILLINST)

zerodiv:
	TRAP(T_ZERODIV)

chkinst:
	TRAP(T_CHKINST)

trapv:
	TRAP(T_TRAPV)

privvio:
	TRAP(T_PRIVVIO)

trace:
	TRAP(T_TRACE)

emu1010:
	TRAP(T_EMU1010)

emu1111:
	TRAP(T_EMU1111)

spurious:
	TRAP(T_SPURIOUS)

badtrap:
	TRAP(T_M_BADTRAP)

brkpt:
	TRAP(T_BRKPT)

floaterr:
	TRAP(T_M_FLOATERR)

errorvec:
	TRAP(T_M_ERRORVEC)

level2:
	IOINTR(2)

level3:
	IOINTR(3)

level4:
	IOINTR(4)

	.data
	.globl	_ledcnt
ledpat:
	.byte	~0x80
	.byte	~0x40
	.byte	~0x20
	.byte	~0x10
	.byte	~0x08
	.byte	~0x04
	.byte	~0x02
	.byte	~0x01
	.byte	~0x02
	.byte	~0x04
	.byte	~0x08
	.byte	~0x10
	.byte	~0x20
	.byte	~0x40
endpat:
	.even
ledptr:		.long	ledpat
flag5:		.word	0
flag7:		.word	0
_ledcnt:	.word	50		| once per second min LED update rate
ledcnt:		.word	0
	.text

/*
 * This code assumes that the real time clock interrupts 100 times
 * a second and that we want to only call hardclock 50 times/sec
 * We update the LEDs with new values so at least a user can tell
 * that something is still running before calling hardclock().
 */
level5:					| default clock interrupt
	tstb	CLKADDR+CLK_INTRREG	| read CLKADDR->clk_intrreg to clear
	andb	#~IR_ENA_CLK5,INTERREG	| clear interrupt request
	orb	#IR_ENA_CLK5,INTERREG	| and re-enable
	tstb	CLKADDR+CLK_INTRREG	| clear interrupt register again,
					| if we lost interrupt we will
					| resync later anyway.
| for 100 hz operation, comment out from here ...
	notw	flag5			| toggle flag
	jeq	0f			| if result zero skip ahead
	rte
0:
| ... to here
	moveml	#0xC0E0,sp@-		| save d0,d1,a0,a1,a2

	movl	sp,a2			| save copy of previous sp
	cmpl	#eintstack,sp		| on interrupt stack?
	jls	1f			| yes, skip
	lea	eintstack,sp		| no, switch to interrupt stack
1:

			/* check for LED update */
	movl	a2@(5*4+2),a1		| get saved pc
	movw	a2@(5*4),d0		| get saved sr
	movl	d0,sp@-			| push it as a long
	movl	a1,sp@-			| push saved pc
	jsr	_hardclock		| call UNIX routine
	movl	a2,sp			| restore old sp
	moveml	sp@+,#0x0703		| restore all saved regs
	jra	rei_io			| all done

/*
 * Level 7 interrupts can be caused by parity/ECC errors or the
 * clock chip.  The clock chip is tied to level 7 interrupts
 * only if we are profiling.  Because of the way nmi's work,
 * we clear the any level 7 clock interrupts first before
 * checking the memory error register.
 */
_level7:
#ifdef	GPROF
	tstb	CLKADDR+CLK_INTRREG	| read CLKADDR->clk_intrreg to clear
	andb	#~IR_ENA_CLK7,INTERREG	| clear interrupt request
	orb	#IR_ENA_CLK7,INTERREG	| and re-enable
#endif	GPROF

	moveml	#0xC0C0,sp@-		| save C regs
	movb	MEMREG,d0		| read memory error register
	andb	#ER_INTR,d0		| a parity/ECC interrupt pending?
	jeq	0f			| if not, jmp
	jsr	_memerr			| dump memory error info
	/*MAYBE REACHED*/		| if we do return to here, then
	jra	1f			| we had a non-fatal memory problem
0:

#ifdef	GPROF
| for 100 hz profiling, comment out from here ...
	notw	flag7			| toggle flag
	jne	1f			| if result non-zero return
| ... to here
	jsr	kprof			| do the profiling
#else	GPROF
	pea	0f			| push message printf
	jsr	_printf			| print the message
	addqw	#4,sp			| pop argument
	.data
0:	.asciz	"stray level 7 interrupt\012"
	.even
	.text
#endif	GPROF
1:
	moveml	sp@+,#0x0303		| restore regs
	rte

/*
 * Called by trap #2 to do an instruction cache flush operation
 */
	.globl	flush
flush:
	movl	#CACHE_CLEAR+CACHE_ENABLE,d0
	movc	d0,cacr			| clear (and enable) the cache
	rte

	.globl	syscall, trap, rei
/*
 * Special case for syscall.
 * Everything in line because this is by far the most
 * common interrupt.
 */
syscall:
	subqw	#2,sp			| empty space
	moveml	#0xFFFF,sp@-		| save all regs
	movl	usp,a0			| get usp
	movl	a0,sp@(R_SP)		| save usp
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#syserr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	a0@,d0			| get the syscall code
#if	MACH_EMULATION
/*
 *  check for user space emulation of this syscall...
 */
	movl	d0,d1			| adjust for minimum emulated syscall
	subl	#EML_MIN_SYSCALL,d1	| one of our system calls?
	jlt	syscont			| < EML_MIN_SYSCALL => no emulation

	movl	a1@(THREAD_TASK)@(EML_DISPATCH),a2
					| get the dispatch structure
	tstl	a2			| just in case...
	jeq	syscont			|

	cmpl	a2@(DISP_COUNT),d1	| system call in emulated range?
	jge	syscont

	movl	a2@(DISP_VECTOR,d1:l:4),a2
					| get the entry
	tstl	a2			| is this entry filled in?
	jeq	syscont

/*
 * Emulated syscall.  Push the saved pc, sr, and syscall number on the user
 * stack and return to the pc specified in the emulation vector.
 */

	subl	#6,a0			| Step on syscall #, room for pc, sr
	movl	a0,sp@(R_SP)		| New user sp

	movl	sp@(R_PC),sp@-		| Store pc, sr, syscall # together so
	movw	sp@(R_SR+4),sp@-	| a single copyout can be used
	movl	d0,sp@-
	subqw	#2,sp			| Align sp

	movl	#10,sp@-
	movl	a0,sp@-
	pea	sp@(10)			| & syscall #, sr, pc
	jsr	_copyout		| copyout(&locals, uesp, 10)
	addw	#24,sp			| pop copyout parameters, locals

	movl	a2,sp@(R_PC)		| change where we "return" to

#if	NFPA > 0
	jmp	2f			| restore regs and head for user space
#else	NFPA > 0
	jmp	3f			| restore regs and head for user space
#endif	NFPA > 0
#endif	MACH_EMULATION
syscont:
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	movl	d0,sp@-			| push syscall code
	jsr	_syscall		| go to C routine
	addqw	#4,sp			| pop arg
	orw	#SR_INTPRI,sr		| need to test atomicly, rte will lower
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread on cpu
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a1	| pointer to PCB of active thread
	bclr	#AST_STEP_BIT-24,a1@(PCB_FLAG) | need to single step?
	jne	4f
	bclr	#AST_SCHED_BIT-24,a1@(PCB_FLAG) | need to reschedule?
	jeq	3f			| no, get out
4:	bset	#TRACE_AST_BIT-24,a1@(PCB_FLAG) | say that we're tracing for AST
	jne	3f			| if already doing it, skip
	bset	#SR_TRACE_BIT-8,sp@(R_SR) | set trace mode
	jeq	3f			| if wasn't set, continue
	bset	#TRACE_USER_BIT-24,a1@(PCB_FLAG) | save fact that trace was set
3:
#if	NFPA > 0
	movw	a1@(PCB_FPA_FLAGS),d0
	andl	#FPA_USED,d0
	tstl	d0			| to check pcb->pcb_fpa_flags
	beq	2f			| FPA is not used, skip
	movl	a1@(PCB_FPA_PC),d0	| saved user PC on FPA exception
	cmpl	sp@(R_PC),d0		| if equal, should rte to fpa user code
	bne	2f			| not equal, skip the following
	clrl	a1@(PCB_FPA_PC)		| clear pcb->pcb_fpa_pc
					| sp points to d0 of kernel stack
	lea	sp@(R_KSTK),a0		| a0 points to bottom of kernel stack
					| (a short beyond <0000, voffset>)
	movl	a1@(PCB_FPA_FMTPTR),a2	| a2 points to saved area
	movw	a2@+,d0			| d0 has the size to restore
	extl	d0			| make it a long
	subl	d0,a0			| a0 points to top of new kernel stack
					| (d0), also (to) in dbra loop below
	addql	#2,a2			| a2 points to saved AST bits
| load back upper 5 bits of pcb->pcb_flag to be consistent w/ saved SR
	movl	a1@(PCB_FLAG),d1	| get current pcb flag
	andl	#NOAST_BITS,d1		| clear upper 5 bits
	orl	a2@+,d1			| oring saved upper 5 bits; a2=+4
	movl	d1,a1@(PCB_FLAG)	| set pcb flag

					| a2 points to saved d0
	movl	a0,sp			| sp points to top of new kernel stack
	asrl	#1,d0			| d0 gets (short count)
	subl	#1,d0			| compensate for dbra (off by 1)
0:	movw	a2@+,a0@+		| move a short
	dbra	d0,0b			| decrement (short count) and loop

2:
#endif	NFPA > 0
	movl	sp@(R_SP),a0		| restore user SP
	movl	a0,usp
 #	movl	#CACHE_CLEAR+CACHE_ENABLE,d0
 #	movc	d0,cacr			| clear (and enable) the cache
1:
	moveml	sp@,#0x7FFF		| restore all but SP
	addw	#R_SR,sp		| pop all saved regs
	rte				| and return!

syserr:
	movl	#63,d0			| set code to nosys
	jra	syscont			| back to mainline

/*
 *	Bootstrap code for new (forked) thread.
 */
ENTRY(thread_bootstrap)
	movl	sp@(R_SP),a0		| restore user SP
	movl	a0,usp
	movl	#CACHE_CLEAR+CACHE_ENABLE,d0
	movc	d0,cacr			| clear (and enable) the cache
	moveml	sp@,#0x7FFF		| restore all but SP
	addw	#R_SR,sp		| pop all saved regs
	rte				| and return!


/*
 * We reset the sfc and dfc to FC_MAP in case we came in from
 * a trap while in the monitor since the monitor uses movs
 * instructions after dorking w/ sfc and dfc during its operation.
 */
trap:
	moveq	#FC_MAP,d0
	movc	d0,sfc	
	movc	d0,dfc
	jsr	_trap			| Enter C trap routine
	addqw	#4,sp			| Pop trap type

/*
 * Return from interrupt or trap, check for AST's.
 * d0 contains the size of info to pop (if any)
 */
rei:
	btst	#SR_SMODE_BIT-8,sp@(R_SR) | SR_SMODE ?
	bne	1f			| skip if system
	orw	#SR_INTPRI,sr		| need to test atomicly, rte will lower
#if	NCPUS > 1
	movl	d0,d1			| save d0
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
	movl	d1,d0			| restore d0
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread on cpu
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a0	| pointer to PCB of active thread
	bclr	#AST_STEP_BIT-24,a0@(PCB_FLAG) | need to single step?
	jne	4f
	bclr	#AST_SCHED_BIT-24,a0@(PCB_FLAG) | need to reschedule?
	jeq	3f			| no, get out
4:	bset	#TRACE_AST_BIT-24,a0@(PCB_FLAG) | say that we're tracing for AST
	bne	3f			| if already doing it, skip
	bset	#SR_TRACE_BIT-8,sp@(R_SR) | set trace mode
	jeq	3f			| if wasn't set, continue
	bset	#TRACE_USER_BIT-24,a0@(PCB_FLAG) | save fact that trace was set
3:	movl	sp@(R_SP),a0		| restore user SP
	movl	a0,usp
	movl	#CACHE_CLEAR+CACHE_ENABLE,a0
	movc	a0,cacr			| clear (and enable) the cache
1:
	tstl	d0			| any cleanup needed?
	beq	2f			| no, skip
	movl	sp,a0			| get current sp
	addw	d0,a0			| pop off d0 bytes of crud
	clrw	a0@(R_VOR)		| dummy VOR
	movl	sp@(R_PC),a0@(R_PC)	| move PC
	movw	sp@(R_SR),a0@(R_SR)	| move SR
	movl	a0,sp@(R_SP)		| stash new sp value
	moveml	sp@,#0xFFFF		| restore all including SP
	addw	#R_SR,sp		| pop all saved regs
	rte				| and return!
2:
	moveml	sp@,#0x7FFF		| restore all but SP
	addw	#R_SR,sp		| pop all saved regs
	rte				| and return!

/*
 * Return from I/O interrupt, check for AST's.
 */
	.globl	rei_io
rei_iop:
	moveml	sp@+,#0x0707		| pop regs <a2,a1,a0,d2,d1,d0>
rei_io:
rei_si:
	moveml	#0x8080,sp@-		| save a0, d0
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread on cpu
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a0	| pointer to PCB of active thread
#if	MACH_KDB
	bclr	#KDB_STEP_BIT-24,a0@(PCB_FLAG)	| single-step for KDB?
	jeq	3f				| if so:
	bset	#TRACE_KDB_BIT-24,a0@(PCB_FLAG) | show that trace should trap
						| to KDB
	jne	5f				| if we haven't set trace mode,
	bset	#SR_TRACE_BIT-8,sp@(2*4)	| set trace mode in SR atop stack
	bra	5f			| clean up stack
3:
#endif	MACH_KDB
	btst	#SR_SMODE_BIT-8,sp@(2*4)	| SR_SMODE?  (SR is atop stack)
	jne	5f				| if not, test for AST trace
	bclr	#AST_STEP_BIT-24,a0@(PCB_FLAG)	| need to single step?
	jne	4f
	bclr	#AST_SCHED_BIT-24,a0@(PCB_FLAG) | need to reschedule?
	jeq	5f				| no, get out
4:	bset	#TRACE_AST_BIT-24,a0@(PCB_FLAG) | say that we're tracing for AST
	jne	5f				| if already doing it, skip
	bset	#SR_TRACE_BIT-8,sp@(2*4)	| set trace mode in SR atop stack
						| (hidden by 2 saved registers)
	jeq	5f				| if wasn't set, continue
	bset	#TRACE_USER_BIT-24,a0@(PCB_FLAG) | save fact that trace was set
5:
	moveml	sp@+,#0x0101		| restore regs <a0,d0>
3:
	rte				| and return!

/*
 * Handle software interrupts
 * Just call C routine
 */
	.globl	softint
softint:
	moveml	#0xC0E0,sp@-		| save regs we trash <d0,d1,a0,a1,a2>
	movl	sp,a2			| save copy of previous sp
	cmpl	#eintstack,sp		| on interrupt stack?
	jls	0f			| yes, skip
	lea	eintstack,sp		| no, switch to interrupt stack
0:
	bclr    #IR_SOFT_INT1_BIT,INTERREG| clear interrupt request
	jsr	_softint		| Call C
	movl	a2,sp			| restore old sp
	moveml	sp@+,#0x0703		| restore saved regs <a2,a1,a0,d1,d0>
	jra	rei_si

/*
 * Turn on a software interrupt (H/W level 1).
 */
	ENTRY(siron)
	bset	#IR_SOFT_INT1_BIT,INTERREG | trigger level 1 intr
	rts

/*
 * return 1 if an interrupt is being serviced (on interrupt stack),
 * otherwise return 0.
 */
	ENTRY(intsvc)
	clrl	d0			| assume false
	cmpl	#eintstack,sp		| on interrupt stack?
	bhi	1f			| no, skip
	movl	#1,d0			| return true
1:
	rts

#if	MACH_KDB
/*
 *	Ugly code to turn a soft interrupt for KDB into a KDB trap.
 *	Called from _softint.
 */
	.globl	_enter_kdb
_enter_kdb:
	/*
	 *	We know that we're called from _softint, which is in turn
	 *	called from softint (above).  Make _softint return to
	 *	the following stretch of code because only the C compiler
	 *	knows where it hid the registers.
	 *	A6 points at _softint's call frame.
	 */
	movl	#kdb_enter_grab_regs,a6@(4)
	rts

kdb_enter_grab_regs:
	/*
	 *	We have all the registers except d0/d1/a0-a2, which
	 *	are on the old stack, pointed to by a2.  Grab them;
	 *	then turn the interrupt frame into a trap frame
	 *	and make this look like a trace trap.
	 */
	movl	a2,sp			| restore old stack
	moveml	sp@+,d0/d1/a0/a1/a2	| and registers
	TRAP(T_TRACE)			| make it look like a trace trap

#endif	MACH_KDB
/*
 * Enable and disable DVMA.
 */
	ENTRY(enable_dvma)
1:
	orb	#ENA_SDVMA,_enablereg	| enable System DVMA
	movb	_enablereg,d0		| get it in a register
	movsb	d0,ENABLEREG		| put enable register back
	cmpb	_enablereg,d0		| see if someone higher changed it
	bne	1b			| if so, try again
	rts
	
	ENTRY(disable_dvma)
1:
	andb	#~ENA_SDVMA,_enablereg	| disable System DVMA
	movb	_enablereg,d0		| get it in a register
	movsb	d0,ENABLEREG		| put enable register back
	cmpb	_enablereg,d0		| see if someone higher changed it
	bne	1b			| if so, try again
	rts

/*
 * Transfer data to and from user space -
 * Note that these routines can cause faults
 * It is assumed that the kernel has nothing at
 * less than KERNELBASE in the virtual address space.
 */

| Fetch user byte		_fubyte(address)
	ENTRY2(fubyte,fuibyte)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-1,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movb	a0@,d0			| get the byte
	andl	#0xFF,d0
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts


| Fetch user (short) word:	 _fusword(address)
	ENTRY(fusword)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-2,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movw	a0@,d0			| get the word
	andl	#0xFFFF,d0
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

| Fetch user (long) word:	_fuword(address)
	ENTRY2(fuword,fuiword)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-4,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movl	a0@,d0			| get the long word
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

| Set user byte:		_subyte(address, value)
	ENTRY2(subyte,suibyte)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-1,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movb	sp@(8+3),a0@		| set the byte
	clrl	d0			| indicate success
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

| Set user short word:		_susword(address, value)
	ENTRY(susword)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-2,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movw	sp@(8+2),a0@		| set the word
	clrl	d0			| indicate success
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

| Set user (long) word:		_suword(address, value)
	ENTRY2(suword,suiword)
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a1
	movl	a1@(0,d0:l:4),a1	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a1	| active thread on cpu
#endif	NCPUS > 1
	movl	#fsuerr,a1@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(4),a0		| get address
	cmpl	#KERNELBASE-4,a0	| check address range
	jhi	fsuerr			| jmp if greater than
	movl	sp@(8+0),a0@		| set the long word
	clrl	d0			| indicate success
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

fsuerr:
	movl	#-1,d0			| return error
	clrl	a1@(THREAD_RECOVER)	| clear recovery address
	rts

/*
 * copyout() - except for _u+U_LOFAULT and address
 * checking this is just bcopy().
 */
	ENTRY(copyout)
	movl	a2,sp@-			| save a2
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a2
	movl	a2@(0,d0:l:4),a2	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a2	| active thread
#endif	NCPUS > 1
	movl	#cpctxerr,a2@(THREAD_RECOVER)	| catch faults
	movl	sp@(8),a0
	movl	sp@(12),a1
	movl	sp@(16),d0
	jle	odone			| leave if ridiculous count
copyoutcheck:
	movl	a1,d1			| get starting address
	cmpl	#KERNELBASE,d1		| check starting address
	jpl	cpctxerr		| jmp on error
	addl	d0,d1			| compute ending address
	cmpl	#KERNELBASE,d1		| check ending address
	jhi	cpctxerr		| jmp on error
	cmpl	d1,a1			| check for wrap around
	jhi	cpctxerr		| jmp on error
/* move that data */
	moveq	#64,d1
	cmpl	d0,d1
	bgt	1f
/* 64 bytes at a time */
2:	movl	d0,d1
	lsrl	#6,d0
	subql	#1,d0
3:	movl	a0@+,a1@+
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
	dbra	d0,3b
	clrw	d0
	subql	#1,d0
	bcc	3b
	moveq	#63,d0
	andl	d1,d0
	beq	odone
/* 4 bytes at a time */
1:	moveq	#4,d1
	cmpl	d0,d1
	bgt	5f
	movl	d0,d1
	lsrl	#2,d0
	subql	#1,d0
4:	movl	a0@+,a1@+
	dbra	d0,4b
	clrw	d0
	subql	#1,d0
	bcc 	4b
	moveq	#3,d0
	andl	d1,d0
	beq	odone
/* 1 byte at a time */
5:	subql	#1,d0
6:	movb	a0@+,a1@+
	dbra	d0,6b
	clrw	d0
	subql	#1,d0
	bcc	6b
/* done */
odone:	clrl	d0			| indicate success
	clrl	a2@(THREAD_RECOVER)	| clear recovery address
	movl	sp@+,a2			| and restore a2
	rts				| and return

/*
 * copyin() - except for _u+U_LOFAULT and address
 * checking this is just bcopy().
 */
	ENTRY(copyin)
	movl	a2,sp@-			| save a2
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a2
	movl	a2@(0,d0:l:4),a2	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a2	| active thread on cpu
#endif	NCPUS > 1
	movl	#cpctxerr,a2@(THREAD_RECOVER)	| catch faults
	movl	sp@(8),a0
	movl	sp@(12),a1
	movl	sp@(16),d0
	jle	idone			| leave if ridiculous count
copyincheck:
	movl	a0,d1			| get starting address
	cmpl	#KERNELBASE,d1		| check starting address
	jpl	cpctxerr		| jmp on error
	addl	d0,d1			| compute ending address
	cmpl	#KERNELBASE,d1		| check ending address
	jhi	cpctxerr		| jmp on error
	cmpl	d1,a0			| check for wrap around
	jhi	cpctxerr		| jmp on error
/* move that data */
	moveq	#64,d1
	cmpl	d0,d1
	bgt	1f
/* 64 bytes at a time */
2:	movl	d0,d1
	lsrl	#6,d0
	subql	#1,d0
3:	movl	a0@+,a1@+
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
	dbra	d0,3b
	clrw	d0
	subql	#1,d0
	bcc	3b
	moveq	#63,d0
	andl	d1,d0
	beq	idone
/* 4 bytes at a time */
1:	moveq	#4,d1
	cmpl	d0,d1
	bgt	5f
	movl	d0,d1
	lsrl	#2,d0
	subql	#1,d0
4:	movl	a0@+,a1@+
	dbra	d0,4b
	clrw	d0
	subql	#1,d0
	bcc 	4b
	moveq	#3,d0
	andl	d1,d0
	beq	idone
/* 1 byte at a time */
5:	subql	#1,d0
6:	movb	a0@+,a1@+
	dbra	d0,6b
	clrw	d0
	subql	#1,d0
	bcc	6b
/* done */
idone:	clrl	d0			| indicate success
	clrl	a2@(THREAD_RECOVER)	| clear recovery address
	movl	sp@+,a2			| and restore a2
	rts				| and return

cpctxerr:
	movl	#EFAULT,d0		| return error
	clrl	a2@(THREAD_RECOVER)	| clear recovery address
	movl	sp@+,a2			| and restore a2
	rts

/*
 * fetch user longwords  -- used by syscall -- faster than copyin
 * Doesn't worry about alignment of transfer, let the 68020 worry
 * about that - we won't be doing more than 8 long words anyways.
 * Use copyin to do more careful checking if we are real close.
 * fulwds(uadd, sadd, nlwds)
 */
	ENTRY(fulwds)
	movl	a2,sp@-			| save a2
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a2
	movl	a2@(0,d0:l:4),a2	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a2	| active thread on cpu
#endif	NCPUS > 1
	movl	#cpctxerr,a2@(THREAD_RECOVER)	| catch a fault if and when
	movl	sp@(8),a0		| user address
	movl	sp@(12),a1		| system address
	movl	sp@(16),d0		| number of words
	cmpl	#KERNELBASE-8*4,a0	| check starting address
	jls	1f			| enter loop at bottom if ok
	lsll	#2,d0			| convert to byte count
	jra	copyincheck		| let copyin code handle
2:	movl	a0@+,a1@+		| get longword
1:	dbra	d0,2b			| loop on count
	clrl	d0			| indicate success
	clrl	a2@(THREAD_RECOVER)	| clear recovery address
	movl	sp@+,a2			| and restore a2
	rts

/*
 * Get/Set vector base register
 */
	ENTRY(getvbr)
	movc	vbr,d0
	rts

	ENTRY(setvbr)
	movl	sp@(4),d0
	movc	d0,vbr
	rts

/*
 * Enter the monitor -- called for console abort
 */
	ENTRY(montrap)
	jsr	_startnmi		| enable monitor nmi routine
	movl	sp@(4),a0		| address to trap to
	clrw	sp@-			| dummy VOR
	pea	0f			| return address
	movw	sr,sp@-			| current sr
	jra	a0@			| trap to monitor
0:
	jsr	_stopnmi		| disable monitor nmi routine
	rts

/*
 * Read the ID prom.  This is mapped from IDPROMBASE for IDPROMSIZE
 * bytes in the FC_MAP address space for byte access only.  Assumes
 * that the sfc has already been set to FC_MAP.
 */
	ENTRY(getidprom)
	movl	sp@(4),a0		| address to copy bytes to
	lea	IDPROMBASE,a1		| select id prom
	movl	#(IDPROMSIZE-1),d1	| byte loop counter
0:	movsb	a1@+,d0			| get a byte
	movb	d0,a0@+			| save it
	dbra	d1,0b			| and loop
	rts

/*
 *	Enable and disable cache.
 */
	ENTRY(setcacheenable)
1:	
	tstl	sp@(4)			| is bit on or off
	jeq	2f
	orb	#ENA_CACHE,_enablereg	| enable cache
	jra	3f
2:
	andb	#~ENA_CACHE,_enablereg	| disable cache
3:
	movb	_enablereg,d0		| get it in a register
	movsb	d0,ENABLEREG		| put enable register back
	cmpb	_enablereg,d0		| see if someone higher changed it
	bne	1b			| if so, try again
	rts

/*
 * Enable and disable video.
 */
	ENTRY(setvideoenable)
1:	
	tstl	sp@(4)			| is bit on or off
	jeq	2f
	orb	#ENA_VIDEO,_enablereg	| enable video
	jra	3f
2:
	andb	#~ENA_VIDEO,_enablereg	| disable video
3:
	movb	_enablereg,d0		| get it in a register
	movsb	d0,ENABLEREG		| put enable register back
	cmpb	_enablereg,d0		| see if someone higher changed it
	bne	1b			| if so, try again
	rts

/*
 * Enable and disable video Copy.
 */
	ENTRY(setcopyenable)
1:	
	tstl	sp@(4)			| is bit on or off
	jeq	2f
	orb	#ENA_COPY,_enablereg	| enable video copy
	jra	3f
2:
	andb	#~ENA_COPY,_enablereg	| disable copy
3:
	movb	_enablereg,d0		| get it in a register
	movsb	d0,ENABLEREG		| put enable register back
	cmpb	_enablereg,d0		| see if someone higher changed it
	bne	1b			| if so, try again
	rts

/*
 * Enable and disable video interrupt.
 */
	ENTRY(setintrenable)
	tstl	sp@(4)			| is bit on or off
	jeq	1f
	orb	#IR_ENA_VID4,INTERREG	| enable video interrupt
	rts
1:	
	andb	#~IR_ENA_VID4,INTERREG	| disable
	rts

/*
 * Read the bus error register
 */
	ENTRY(getbuserr)
	clrl	d0
	movsb   BUSERRREG,d0            | get the buserr register
	rts

/*
 * Set the fpp registers to the u area values
 * If running Mach VM, then set them to the values saved in PCB instead.
 */
	ENTRY(setfppregs)
	tstw	_fppstate		| is fpp present and enabled?
	jle	1f			| branch if not
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a0	| active thread
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a0	| pointer to PCB of active thread
	fmovem	a0@(PCB_FPS_REGS),fp0-fp7	| set fp data registers
	fmovem	a0@(PCB_FPS_CTRL),fpc/fps/fpi	| set control registers
1:
	rts

/*
 *	Save FP registers into PCB for the current thread.
 */
ENTRY(savefppregs)
	tstw	_fppstate		| fpp present and enabled?
	jle	1f			| bail out if not
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a0
	movl	a0@(0,d0:l:4),a0
#else	NCPUS > 1
	movl	_active_threads,a0	| get current thread
#endif	NCPUS > 1
	movl	a0@(THREAD_PCB),a0	| point to its PCB
	fsave	a0@(PCB_FP_ISTATE)	| save internal state
	tstw	a0@(PCB_FP_ISTATE)	| is there any?
	jeq	1f			| bail out if not
	fmovem	fpc/fps/fpi,a0@(PCB_FPS_CTRL)	| save control regs
	fmovem	fp0-fp7,a0@(PCB_FPS_REGS)	| and data regs
	frestore a0@(PCB_FP_ISTATE)	| restore internal state
1:
	rts

/*
 * Copy a null terminated string from one point to another in kernel virtual
 * address space.  Returns a nonzero error code if the last character copied
 * was not the null character.
 *
 *	copystr(from, to, maxlength, &lencopied)
 */
	ENTRY(copystr)
	moveml	a2/d2,sp@-		| save registers
	movl	sp@(8+4),a0		| from
	movl	sp@(8+8),a1		| to
	movl	sp@(8+12),d1		| maxlen
	movl	sp@(8+16),a2		| lencopied
	moveq	#0,d2			| bytescopied = 0
0:
	cmpl	d1,d2			| bytescopied >= maxlen?
	jge	2f			| yes, go return error.
	addql	#1,d2			| bytescopied++
	movb	a0@+,a1@+		| to++ = from++
	jne	0b			| keep copying?
1:
	moveq	#0,d0			| return 0
	tstl	a2			| null lencopied ptr.?
	jeq	3f			| yes, just return
	movl	d2,a2@			| *lencopied = bytescopied
	jra	3f
2:
	moveq	#ENOENT,d0		| return ENOENT
3:
	moveml	sp@+,a2/d2		| restore registers
	rts

/*
 * Copy a null terminated string from user to kernel address space.
 *
 *	copyinstr(from, to, maxlength, &lencopied)
 */
	ENTRY(copyinstr)
	moveml	a2/a3/d2,sp@-		| save registers
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a3
	movl	a3@(0,d0:l:4),a3	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a3	| active thread on cpu
#endif	NCPUS > 1
	movl	#cpstrerr,a3@(THREAD_RECOVER)	| catch a fault if and when

	movl	sp@(12+4),a0		| from
	movl	sp@(12+8),a1		| to
	movl	sp@(12+12),d1		| maxlen
	movl	sp@(12+16),a2		| lencopied
	moveq	#0,d2			| bytescopied = 0
0:
	cmpl	d1,d2			| bytescopied >= maxlen?
	jge	2f			| yes, go return error.
	addql	#1,d2			| bytescopied++
	movb	a0@+,a1@+		| to++ = from++
	jne	0b			| keep copying?
1:
	moveq	#0,d0			| return 0
	tstl	a2			| null lencopied ptr.?
	jeq	3f			| yes, just return
	movl	d2,a2@			| *lencopied = bytescopied
	jra	3f
2:
	moveq	#ENOENT,d0		| return ENOENT
3:
	clrl	a3@(THREAD_RECOVER)	| clear recovery address
	moveml	sp@+,a2/a3/d2		| restore registers
	rts


/*
 * Copy a null terminated string from kernel to user address space.
 *
 *	copyoutstr(from, to, maxlength, &lencopied)
 */
	ENTRY(copyoutstr)
	moveml	a2/a3/d2,sp@-		| save registers
#if	NCPUS > 1
	CPU_NUMBER_D0
	lea	_active_threads,a3
	movl	a3@(0,d0:l:4),a3	| active thread on current cpu
#else	NCPUS > 1
	movl	_active_threads,a3	| active thread on cpu
#endif	NCPUS > 1
	movl	#cpstrerr,a3@(THREAD_RECOVER)	| catch a fault if and when

	movl	sp@(12+4),a0		| from
	movl	sp@(12+8),a1		| to
	movl	sp@(12+12),d1		| maxlen
	movl	sp@(12+16),a2		| lencopied
	moveq	#0,d2			| bytescopied = 0
0:
	cmpl	d1,d2			| bytescopied >= maxlen?
	jge	2f			| yes, go return error.
	addql	#1,d2			| bytescopied++
	movb	a0@+,a1@+		| to++ = from++
	jne	0b			| keep copying?
1:
	moveq	#0,d0			| return 0
	tstl	a2			| null lencopied ptr.?
	jeq	3f			| yes, just return
	movl	d2,a2@			| *lencopied = bytescopied
	jra	3f
2:
	moveq	#ENOENT,d0		| return ENOENT
3:
	clrl	a3@(THREAD_RECOVER)	| clear recovery address
	moveml	sp@+,a2/a3/d2		| restore registers
	rts

| here if invalid address caught by page fault
cpstrerr:
	moveq	#EFAULT,d0		| return EFAULT
	clrl	a3@(THREAD_RECOVER)	| clear recovery address
	moveml	sp@+,a2/a3/d2		| restore registers
	rts

/*
 * Enable bit in both Unix _enablereg and hard ENABLEREG.
 * on_enablereg(bit) turns on enable register by oring it and bit.
 * E.g. on_enablereg((u_char)ENA_FPA)
 */
	ENTRY(on_enablereg)
	movb	sp@(7),d0		| get byte
	orb	d0,_enablereg		| turn on a bit
	movb	_enablereg,d0           | get it in a register
	movsb   d0,ENABLEREG            | put into hard ENABLEREG
	rts
 
/*
 * Disable bit in both Unix _enablereg and hard ENABLEREG. 
 * off_enablereg(bit) turns off enable register by anding it and bit.
 * E.g. off_enablereg((u_char)ENA_FPA)
 */ 
	ENTRY(off_enablereg) 
	movb	sp@(7),d0		| get byte
	notb	d0			| ~bit
	andb	d0,_enablereg		| turn off a bit
	movb	_enablereg,d0		| get it in a register 
	movsb	d0,ENABLEREG		| put into hard ENABLEREG 
	rts

/*
 * Define some variables used by post-modem debuggers
 * to help them work on kernels with changing structures.
 */
	.globl UPAGES_DEBUG, KERNELBASE_DEBUG, VADDR_MASK_DEBUG
	.globl PGSHIFT_DEBUG, SLOAD_DEBUG

UPAGES_DEBUG		= UPAGES
KERNELBASE_DEBUG	= KERNELBASE
VADDR_MASK_DEBUG	= 0x0fffffff
PGSHIFT_DEBUG		= PGSHIFT
SLOAD_DEBUG		= SLOAD
/* 
 *  Arrange for the include file version number to appear directly in
 *  the name list.
 */
#include <sys/version.h>
	.globl _INCLUDE_VERSION
_INCLUDE_VERSION	= INCLUDE_VERSION
