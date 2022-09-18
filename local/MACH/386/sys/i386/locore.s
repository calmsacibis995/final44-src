/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	locore.s,v $
 * Revision 1.7.1.24  91/05/03  10:57:06  rvb
 * 	The l{in,out}{b,w} routines MUST do a "cld" or you can cause
 * 	major problems; this could happen to the disk in particular.
 * 	[91/04/25            rvb]
 * 
 * Revision 1.7.1.23  91/03/29  16:23:52  rvb
 * 	X134 uses aston/astoff macros that set need_ast vs do_an_ast.
 * 	[91/03/29            rvb]
 * 
 * Revision 1.7.1.22  91/03/28  08:43:54  rvb
 * 	Revision 2.12  89/10/11  14:55:18  dlb
 * 		Don't have to check thread exit code any more.
 * 		[89/02/02            dlb]
 * 
 * Revision 1.7.1.21  91/01/06  22:10:41  rvb
 * 	Split out trap's for v86 to call trapv86()
 * 	[90/12/13            rvb]
 * 
 * Revision 1.7.1.20  90/11/27  13:39:46  rvb
 * 	Change Prime copyright as per Peter J. Weyman authorization.
 * 	[90/11/19            rvb]
 * 
 * 	Fix up ipl0panic code; problem noted by MT.Xinu
 * 	[90/11/09            rvb]
 * 
 * Revision 1.7.1.19  90/09/18  08:33:21  rvb
 * 	IFF efl has VM on, make sure we treat this as a USER
 * 	CS, not a KERNEL CS
 * 	[90/09/12            rvb]
 * 
 * Revision 1.7.1.18  90/08/25  17:53:24  rvb
 * 	Typo
 * 
 * 
 * Revision 1.7.1.17  90/07/27  11:23:06  rvb
 * 	INTERRUPT interface must not do sti when it drops priority  
 * 	and hence can not call set_spl, or splx.
 * 	[90/07/26            rvb]
 * 
 * Revision 1.7.1.16  90/07/10  11:42:12  rvb
 * 	On interrupt dispatch, translate pic slot to unit using iunit.
 * 	Use MAGIC to tell BIOS not to test memory on reboot.
 * 	[90/06/15            rvb]
 * 
 * Revision 1.7.1.15  90/05/22  08:19:37  rvb
 * 	Make Bpt have a frame -- for easier debugging.
 * 	[90/05/21            rvb]
 * 
 * Revision 1.7.1.14  90/05/14  13:19:20  rvb
 * 	Bring kdb up to Mach 2.5 production quality:
 * 	It is now expect that an interrupt will have have one
 * 	argument, and then locr0 begins.  kdintr needs this.
 * 	[90/05/10            rvb]
 * 
 * 	all copy's to str.s
 * 	[90/04/23            rvb]
 * 
 * Revision 1.7.1.13  90/03/16  18:14:55  rvb
 * 	Add support for 3com 3c501 ether:
 * 		linb and loutb 	 [bernadat]
 * 
 * Revision 1.7.1.12  90/03/12  11:16:57  rvb
 * 	Eliminate userwrite check in bzero.  It was never checked.
 * 	[90/03/10            rvb]
 * 
 * Revision 1.7.1.11  90/03/07  13:27:15  rvb
 * 	Add spl counters.
 * 	bcopy can not make a stack frame any more.
 * 	{f,s}{,i}u{byte,word} moved to copy_user.s.
 * 
 * 		I386e- merge.	[kupfer]
 * 
 * Revision 1.7.1.10  90/02/28  15:47:50  rvb
 * 	Olivetti Changes [kupfer]
 * 	engineer the i386_coproc_hang to run on timeout()
 * 	started in start_init [rvb]
 * 
 * Revision 1.18  90/02/26  17:54:03  kupfer
 * Synch with CMU.  h/w workarounds ifdef'd by h/w type.
 * 
 * Revision 1.7.1.7  90/02/01  16:16:37  rvb
 *	Fix FAULT_ERROR so that MACH_KDB can be 0.
 *	[90/02/01            rvb]
 *   
 * Revision 1.7.1.6  90/02/01  13:36:05  rvb
 *	Fix FAULT_ERROR so it can be used by kdb{w,r}long
 *	which has no saved state.
 *   
 * Revision 1.7.1.5  90/01/16  15:54:00  rvb
 *	-1!exp in coff asm => -1^exp in gas
 *	[90/01/08            rvb]
 *   
 * Revision 1.7.1.4  90/01/02  13:47:25  rvb
 *	Typo
 *   
 * Revision 1.7.1.3  89/12/21  17:13:30  rvb
 *	Slave on irq2
 *   
 *	Revision 1.16  89/12/05  18:05:15  kupfer
 *	Fix FAULT_ERROR to work with gcc 1.36 -O, plus related cleanups.
 *   
 *	Revision 1.15  89/10/22  11:30:49  rvb
 *	kernacc() moves to pmap.c (from Lance).
 *   
 *	Revision 1.14  89/11/16  16:24:11  kupfer
 *	Add workaround for Errata 17 for B1 step 80386s (coprocessor
 *	instruction that spans page boundary).
 *	[89/12/21            rvb]
 * 
 * Revision 1.7.1.2  89/10/30  12:26:23  rvb
 * 	Fix some "typo's" in the fp support.
 * 	[89/10/27            rvb]
 * 
 * Revision 1.7.1.1  89/10/22  11:30:49  rvb
 * 	Revision 1.13  89/10/16  14:52:44  lance
 * 	Fixed usage of EFAULT
 * 
 * 	Revision 1.12  89/10/16  14:40:27  lance
 * 	Added errata workaround to set_cr3().
 * 	New a.out and coff compatible .s files.
 * 	[89/10/16            rvb]
 * 
 * 	Fix from Joseph Lin for spurious intnull(15)'s
 * 	[89/10/02            rvb]
 * 
 * 	Flush blatantly sysV spath/upath and plock/prele code.  Was
 * 	commented out anyway.
 * 	[89/09/27            rvb]
 * 
 * Revision 1.7  89/09/25  12:24:48  rvb
 * 	Make mathemul configurable.
 * 	[89/09/23            rvb]
 * 
 * 	This is UNPUBLISHED PROPRIETARY SOURCE CODE of Prime Computer, Inc.
 * 	[89/09/23            rvb]
 * 
 */

#ifdef	M380
#define COPROC_SPANPAGE_BUG	1
#define COPROC_CR3	1
#endif	M380

#include <i386/asm.h>

/*
Copyright (c) 1988,1989 Prime Computer, Inc.  Natick, MA 01760
All Rights Reserved.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and
without fee is hereby granted, provided that the above
copyright notice appears in all copies and that both the
copyright notice and this permission notice appear in
supporting documentation, and that the name of Prime
Computer, Inc. not be used in advertising or publicity
pertaining to distribution of the software without
specific, written prior permission.

THIS SOFTWARE IS PROVIDED "AS IS", AND PRIME COMPUTER,
INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN
NO EVENT SHALL PRIME COMPUTER, INC.  BE LIABLE FOR ANY
SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN ACTION OF CONTRACT, NEGLIGENCE, OR
OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <mach_kdb.h>
#include <mach_emulation.h>
#include <cputypes.h>
#include <sys/errno.h>
#include <mach/kern_return.h>
#include <i386/ipl.h>
#include <i386/pic.h>
#include <i386/reg.h>
#include <mach/i386/vm_param.h>

/
/			 GLOBAL DEFINITIONS
	.data
	.set    CR0_ET,		0x0010            / extension type
	.set    CR0_TS,		0x0008            / task switched
	.set    CR0_EM,		0x0004            / use math emulation
	.set    CR0_MP,		0x0002            / math coprocessor present
	.set    CR0_PE,		0x0001            / protection enable
	.set    FP_SW,		0x0001            / fp emulator is used
	.set    FP_287,		0x0002            / 80287 present
	.set    FP_387,		0x0003            / 80387 present
	.set    F_OFF,		0x0002		/ kernel mode flags, ints off
	.set    F_ON,		0x0202		/ kernel mode flags, ints on
	.set    IS_LDT_SEL,	0x0004		/ GDT/LDT bit in selector
	.set	KSTKSZ,		0x1000
	.set    KVBASE,		0xC0000000	/ base address of the kernel
	.set	MASK,		0x0004
	.set	NBPC,		0x1000		/ Page Size from param.h
	.set	PC,		0x0008
	.set	PROTPORT,	0x00E0
	.set	PROTVAL,	0x0001
	.set	TICS,		0x0010
	.set	UPROF,		0x000C
	.set	USER_CS,	0x0017
	.set	USER_DS,	0x001F
	.set	USIZE,		0x0003		/ No. of pages in U Block
	.set    UVBASE,		0x00000000	/ main store start v_addr
	.set    MAXUVADR,	KVBASE		/ maximum user vaddr.
	.set    MINKVADR,	KVBASE		/ minimum kernel vaddr.
	.set    MINUVADR,	UVBASE		/ minimum user vaddr.
	.set    UVTEXT,		UVBASE		/ beginning addr of user text

/
/			 GLOBAL VARIABLES
	.data
DATA(loadpt)
	.long 	0
DATA(loadpg)
	.long	0 
DATA(eaxsave)
	.long	0
#ifdef	THREAD_EXIT
DATA(need_ast)
	.long	0
#endif	THREAD_EXIT

#ifdef	COPROC_SPANPAGE_BUG
DATA(intrlocr0)
	.long	0			/ see "interrupt"
#endif	/* COPROC_SPANPAGE_BUG */

/
/			 MACROES
	.text
///////////////////////////////////////////////////////////////////////////////
/	EXCEPTION : macro to handle trap where error code is not automatically 
/	pushed on stack by i80386, calls the trap handling routine and passes 
/	parameters on the stack, dummies out the trap name so that we only need
/	to write one trap handler, with common stack image.
///////////////////////////////////////////////////////////////////////////////

#define EXCEPTION(trp_name,number)					\
Entry(trp_name)				;				\
		pushl	$0x00		;				\
		pushl	$number		;				\
		jmp	trap_handler

///////////////////////////////////////////////////////////////////////////////
/	 EXCEPTERR : macro to handle trap where error code is automatically 
/	 pushed on stack by i80386, calls the trap handling routine and passes
/	 parameters on the stack.
///////////////////////////////////////////////////////////////////////////////
 
#define EXCEPTERR(err_name,number)					\
Entry(err_name)				;				\
		pushl	$number		;				\
		jmp	trap_handler

///////////////////////////////////////////////////////////////////////////////
/	INTERRUPT : macro to handle interrupt call whether external or software
/	based, calls interrupt handling routine passing parameters on stack.
///////////////////////////////////////////////////////////////////////////////

#define INTERRUPT(int_name,number)					\
Entry(int_name)				;				\
		pushl	$0x00		;				\
		pushl	$number		;				\
		jmp	interrupt

///////////////////////////////////////////////////////////////////////////////
/	KERNEL_RETURN : procedure to follow to return to kernel routine 
/	for system calls, traps, interrupts etc.
///////////////////////////////////////////////////////////////////////////////

#define KERNEL_RETURN			 				\
		popl	%gs		;				\
		popl	%fs		;				\
		popl	%es		;				\
		popl	%ds		;				\
		popa			;				\
		addl	$0x08, %esp	;				\
		iret

///////////////////////////////////////////////////////////////////////////////
/ 	INTERRUPT_RETURN : this routine is run to return from an interrupt
/ 	handling routine. This is implemented as a macroe for efficiency 
/ 	reasons.
///////////////////////////////////////////////////////////////////////////////

#define INTERRUPT_RETURN		 				\
		movl	Times(CS,4)(%ebp), %eax	;			\
		testw	$IS_LDT_SEL,%ax		;			\
		jnz	user_return		;			\
		movl	Times(EFL,4)(%ebp), %eax;			\
		btl	$17,%eax		;			\
		jc	user_return		;			\
KERNEL_RETURN			


///////////////////////////////////////////////////////////////////////////////
/	SET_PIC_MASK : this routine is run to set the pic masks, it is 
/	implemented as a macroe for efficiency reasons.
///////////////////////////////////////////////////////////////////////////////

#define SET_PIC_MASK							\
		movl	EXT(master_ocw),%edx	;			\
		OUTB				;			\
		addw	$SIZE_PIC,%dx		;			\
		movb	%ah,%al			;			\
		OUTB

/
/			MACRO CALLS 

///////////////////////////////////////////////////////////////////////////////
/	Faults : reported BEFORE execution instruction causing exception.
/ 	Trap   : reported AFTER  execution instruction causing exception.
/	Abort  : reported where error location is not known and program
/		restart impossible.
/ 
/ 	Exceptions 0x0E and (0x11 - 0x1F) are reserved by Intel
/ 	Exception  0x02 is for the Non Maskable Interrupt.
/ 	Exceptions 0x40 - 0xFF are assigned to external interrupts.
///////////////////////////////////////////////////////////////////////////////

EXCEPTION(trp_divr,0x00)
EXCEPTION(trp_debg,0x01)
EXCEPTION(int__nmi,0x02)
EXCEPTION(trp_brpt,0x03)
EXCEPTION(trp_over,0x04)
EXCEPTION(flt_bnds,0x05)
EXCEPTION(flt_opcd,0x06)
EXCEPTION(flt_ncpr,0x07)
EXCEPTERR(abt_dblf,0x08)
EXCEPTION(abt_over,0x09)
EXCEPTERR(flt_btss,0x0A)
EXCEPTERR(flt_bseg,0x0B)
EXCEPTERR(flt_bstk,0x0C)
EXCEPTERR(flt_prot,0x0D)
EXCEPTERR(flt_page,0x0E)
EXCEPTION(trp_0x0F,0x0F)
EXCEPTION(flt_bcpr,0x10)
EXCEPTION(trp_0x11,0x11)
EXCEPTION(trp_0x12,0x12)
EXCEPTION(trp_0x13,0x13)
EXCEPTION(trp_0x14,0x14)
EXCEPTION(trp_0x15,0x15)
EXCEPTION(trp_0x16,0x16)
EXCEPTION(trp_0x17,0x17)
EXCEPTION(trp_0x18,0x18)
EXCEPTION(trp_0x19,0x19)
EXCEPTION(trp_0x1A,0x1A)
EXCEPTION(trp_0x1B,0x1B)
EXCEPTION(trp_0x1C,0x1C)
EXCEPTION(trp_0x1D,0x1D)
EXCEPTION(trp_0x1E,0x1E)
EXCEPTION(trp_0x1F,0x1F)
EXCEPTION(trp_0x20,0x20)
EXCEPTION(trp_0x21,0x21)
EXCEPTION(trp_0x22,0x22)
EXCEPTION(trp_0x23,0x23)
EXCEPTION(trp_0x24,0x24)
EXCEPTION(trp_0x25,0x25)
EXCEPTION(trp_0x26,0x26)
EXCEPTION(trp_0x27,0x27)
EXCEPTION(trp_0x28,0x28)
EXCEPTION(trp_0x29,0x29)
EXCEPTION(trp_0x2A,0x2A)
EXCEPTION(trp_0x2B,0x2B)
EXCEPTION(trp_0x2C,0x2C)
EXCEPTION(trp_0x2D,0x2D)
EXCEPTION(trp_0x2E,0x2E)
EXCEPTION(trp_0x2F,0x2F)
EXCEPTION(trp_0x30,0x30)
EXCEPTION(trp_0x31,0x31)
EXCEPTION(trp_0x32,0x32)
EXCEPTION(trp_0x33,0x33)
EXCEPTION(trp_0x34,0x34)
EXCEPTION(trp_0x35,0x35)
EXCEPTION(trp_0x36,0x36)
EXCEPTION(trp_0x37,0x37)
EXCEPTION(trp_0x38,0x38)
EXCEPTION(trp_0x39,0x39)
EXCEPTION(trp_0x3A,0x3A)
EXCEPTION(trp_0x3B,0x3B)
EXCEPTION(trp_0x3C,0x3C)
EXCEPTION(trp_0x3D,0x3D)
EXCEPTION(trp_0x3E,0x3E)
EXCEPTION(trp_0x3F,0x3F)
/
INTERRUPT(int_0x00,0x00)
INTERRUPT(int_0x01,0x01)
INTERRUPT(int_0x02,0x02)
INTERRUPT(int_0x03,0x03)
INTERRUPT(int_0x04,0x04)
INTERRUPT(int_0x05,0x05)
INTERRUPT(int_0x06,0x06)
INTERRUPT(int_0x07,0x07)
INTERRUPT(int_0x08,0x08)
INTERRUPT(int_0x09,0x09)
INTERRUPT(int_0x0A,0x0A)
INTERRUPT(int_0x0B,0x0B)
INTERRUPT(int_0x0C,0x0C)
INTERRUPT(int_0x0D,0x0D)
INTERRUPT(int_0x0E,0x0E)
INTERRUPT(int_0x0F,0x0F)
INTERRUPT(int_0x10,0x10)
INTERRUPT(int_0x11,0x11)
INTERRUPT(int_0x12,0x12)
INTERRUPT(int_0x13,0x13)
INTERRUPT(int_0x14,0x14)
INTERRUPT(int_0x15,0x15)
INTERRUPT(int_0x16,0x16)
INTERRUPT(int_0x17,0x17)
INTERRUPT(int_0x18,0x18)
INTERRUPT(int_0x19,0x19)
INTERRUPT(int_0x1A,0x1A)
INTERRUPT(int_0x1B,0x1B)
INTERRUPT(int_0x1C,0x1C)
INTERRUPT(int_0x1D,0x1D)
INTERRUPT(int_0x1E,0x1E)
INTERRUPT(int_0x1F,0x1F)
INTERRUPT(int_0x20,0x20)
INTERRUPT(int_0x21,0x21)
INTERRUPT(int_0x22,0x22)
INTERRUPT(int_0x23,0x23)
INTERRUPT(int_0x24,0x24)
INTERRUPT(int_0x25,0x25)
INTERRUPT(int_0x26,0x26)
INTERRUPT(int_0x27,0x27)
INTERRUPT(int_0x28,0x28)
INTERRUPT(int_0x29,0x29)
INTERRUPT(int_0x2A,0x2A)
INTERRUPT(int_0x2B,0x2B)
INTERRUPT(int_0x2C,0x2C)
INTERRUPT(int_0x2D,0x2D)
INTERRUPT(int_0x2E,0x2E)
INTERRUPT(int_0x2F,0x2F)
INTERRUPT(int_0x30,0x30)
INTERRUPT(int_0x31,0x31)
INTERRUPT(int_0x32,0x32)
INTERRUPT(int_0x33,0x33)
INTERRUPT(int_0x34,0x34)
INTERRUPT(int_0x35,0x35)
INTERRUPT(int_0x36,0x36)
INTERRUPT(int_0x37,0x37)
INTERRUPT(int_0x38,0x38)
INTERRUPT(int_0x39,0x39)
INTERRUPT(int_0x3A,0x3A)
INTERRUPT(int_0x3B,0x3B)
INTERRUPT(int_0x3C,0x3C)
INTERRUPT(int_0x3D,0x3D)
INTERRUPT(int_0x3E,0x3E)
INTERRUPT(int_0x3F,0x3F)
INTERRUPT(int_0x40,0x40)
INTERRUPT(int_0x41,0x41)
INTERRUPT(int_0x42,0x42)
INTERRUPT(int_0x43,0x43)
INTERRUPT(int_0x44,0x44)
INTERRUPT(int_0x45,0x45)
INTERRUPT(int_0x46,0x46)
INTERRUPT(int_0x47,0x47)
INTERRUPT(int_0x48,0x48)
INTERRUPT(int_0x49,0x49)
INTERRUPT(int_0x4A,0x4A)
INTERRUPT(int_0x4B,0x4B)
INTERRUPT(int_0x4C,0x4C)
INTERRUPT(int_0x4D,0x4D)
INTERRUPT(int_0x4E,0x4E)
INTERRUPT(int_0x4F,0x4F)
INTERRUPT(int_0x50,0x50)
INTERRUPT(int_0x51,0x51)
INTERRUPT(int_0x52,0x52)
INTERRUPT(int_0x53,0x53)
INTERRUPT(int_0x54,0x54)
INTERRUPT(int_0x55,0x55)
INTERRUPT(int_0x56,0x56)
INTERRUPT(int_0x57,0x57)
INTERRUPT(int_0x58,0x58)
INTERRUPT(int_0x59,0x59)
INTERRUPT(int_0x5A,0x5A)
INTERRUPT(int_0x5B,0x5B)
INTERRUPT(int_0x5C,0x5C)
INTERRUPT(int_0x5D,0x5D)
INTERRUPT(int_0x5E,0x5E)
INTERRUPT(int_0x5F,0x5F)
INTERRUPT(int_0x60,0x60)
INTERRUPT(int_0x61,0x61)
INTERRUPT(int_0x62,0x62)
INTERRUPT(int_0x63,0x63)
INTERRUPT(int_0x64,0x64)
INTERRUPT(int_0x65,0x65)
INTERRUPT(int_0x66,0x66)
INTERRUPT(int_0x67,0x67)
INTERRUPT(int_0x68,0x68)
INTERRUPT(int_0x69,0x69)
INTERRUPT(int_0x6A,0x6A)
INTERRUPT(int_0x6B,0x6B)
INTERRUPT(int_0x6C,0x6C)
INTERRUPT(int_0x6D,0x6D)
INTERRUPT(int_0x6E,0x6E)
INTERRUPT(int_0x6F,0x6F)
INTERRUPT(int_0x70,0x70)
INTERRUPT(int_0x71,0x71)
INTERRUPT(int_0x72,0x72)
INTERRUPT(int_0x73,0x73)
INTERRUPT(int_0x74,0x74)
INTERRUPT(int_0x75,0x75)
INTERRUPT(int_0x76,0x76)
INTERRUPT(int_0x77,0x77)
INTERRUPT(int_0x78,0x78)
INTERRUPT(int_0x79,0x79)
INTERRUPT(int_0x7A,0x7A)
INTERRUPT(int_0x7B,0x7B)
INTERRUPT(int_0x7C,0x7C)
INTERRUPT(int_0x7D,0x7D)
INTERRUPT(int_0x7E,0x7E)
INTERRUPT(int_0x7F,0x7F)
INTERRUPT(int_0x80,0x80)
INTERRUPT(int_0x81,0x81)
INTERRUPT(int_0x82,0x82)
INTERRUPT(int_0x83,0x83)
INTERRUPT(int_0x84,0x84)
INTERRUPT(int_0x85,0x85)
INTERRUPT(int_0x86,0x86)
INTERRUPT(int_0x87,0x87)
INTERRUPT(int_0x88,0x88)
INTERRUPT(int_0x89,0x89)
INTERRUPT(int_0x8A,0x8A)
INTERRUPT(int_0x8B,0x8B)
INTERRUPT(int_0x8C,0x8C)
INTERRUPT(int_0x8D,0x8D)
INTERRUPT(int_0x8E,0x8E)
INTERRUPT(int_0x8F,0x8F)
INTERRUPT(int_0x90,0x90)
INTERRUPT(int_0x91,0x91)
INTERRUPT(int_0x92,0x92)
INTERRUPT(int_0x93,0x93)
INTERRUPT(int_0x94,0x94)
INTERRUPT(int_0x95,0x95)
INTERRUPT(int_0x96,0x96)
INTERRUPT(int_0x97,0x97)
INTERRUPT(int_0x98,0x98)
INTERRUPT(int_0x99,0x99)
INTERRUPT(int_0x9A,0x9A)
INTERRUPT(int_0x9B,0x9B)
INTERRUPT(int_0x9C,0x9C)
INTERRUPT(int_0x9D,0x9D)
INTERRUPT(int_0x9E,0x9E)
INTERRUPT(int_0x9F,0x9F)
INTERRUPT(int_0xA0,0xA0)
INTERRUPT(int_0xA1,0xA1)
INTERRUPT(int_0xA2,0xA2)
INTERRUPT(int_0xA3,0xA3)
INTERRUPT(int_0xA4,0xA4)
INTERRUPT(int_0xA5,0xA5)
INTERRUPT(int_0xA6,0xA6)
INTERRUPT(int_0xA7,0xA7)
INTERRUPT(int_0xA8,0xA8)
INTERRUPT(int_0xA9,0xA9)
INTERRUPT(int_0xAA,0xAA)
INTERRUPT(int_0xAB,0xAB)
INTERRUPT(int_0xAC,0xAC)
INTERRUPT(int_0xAD,0xAD)
INTERRUPT(int_0xAE,0xAE)
INTERRUPT(int_0xAF,0xAF)
INTERRUPT(int_0xB0,0xB0)
INTERRUPT(int_0xB1,0xB1)
INTERRUPT(int_0xB2,0xB2)
INTERRUPT(int_0xB3,0xB3)
INTERRUPT(int_0xB4,0xB4)
INTERRUPT(int_0xB5,0xB5)
INTERRUPT(int_0xB6,0xB6)
INTERRUPT(int_0xB7,0xB7)
INTERRUPT(int_0xB8,0xB8)
INTERRUPT(int_0xB9,0xB9)
INTERRUPT(int_0xBA,0xBA)
INTERRUPT(int_0xBB,0xBB)
INTERRUPT(int_0xBC,0xBC)
INTERRUPT(int_0xBD,0xBD)
INTERRUPT(int_0xBE,0xBE)
INTERRUPT(int_0xBF,0xBF)

	.text
/
///////////////////////////////////////////////////////////////////////////////
/	TRAP_HANDLER	: routine to handle exceptions, args passed
/	via stack, some exceptions cause an error code to be pushed
/	onto the stack by the processor prior to calling the relevant
/	exception handler, (most dont), in each case the exception
/	handling routine pads the stack image out as required and
/	calls this trap handler with a trap number.This routine
/	basically determines whether or not we were running as kernel
/	at the time of the exception and calls the routine "trap()"
/	with the correct parameters.
///////////////////////////////////////////////////////////////////////////////

/	1. As this is a trap handler and so was called (for some
/	reason) during execution of some routine, we save the state of
/	the running program.  
/	// See 80386 System Software Writers Guide , pp (3-4) for
/	stack layout.

Entry(TRAP)
trap_handler:
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/	2. Now we need to establish ourselves as running in Kernel
/	mode by selecting the Kernel's data space.

	movw	$KDSSEL,%ax		/  4 / %ds can't be affected directly.
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp, %ebp		/  2 / save a copy of stack pointer.

/	3. The first argument for the trap handler (trap()) is the
/	location of the stack image that we have just created, so we
/	push the current value of %esp.

	pushl	%esp			/  2 /

/	4. Now we need to know whether the process that was running
/	when the exception was detected was part of the Kernel or
/	running in User space.  This we can tell from the %cs stored
/	on the stack. In either case we call trap() but in the user
/	space case we must do some extra checking when done with
/	trap() to see if a context switch is warranted or not.

	movl	Times(EFL,4)(%ebp), %eax
	btl	$17,%eax
	jc	v86_trap_handler
	movl	Times(CS,4)(%ebp), %eax	/  2 /	
	testw	$IS_LDT_SEL,%ax		/  2 /
	jnz	user_trap_handler	/ ** /

///////////////////////////////////////////////////////////////////////////////
/ 	5. Kernel mode case : call trap(), then remove stack image created 
/	earlier, and return from whence we came.
///////////////////////////////////////////////////////////////////////////////

kernel_trap_handler:
	call 	EXT(trap)		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
					/      created above.
short_user_ret:
kernel_return:
KERNEL_RETURN

///////////////////////////////////////////////////////////////////////////////
/ 	5. User mode case : call trap(), check to see if a context switch is 
/	warranted then remove stack image created earlier, and return from 
/	whence we came.
///////////////////////////////////////////////////////////////////////////////

v86_trap_handler:
	call 	EXT(trapv86)		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
	jmp	user_return

user_trap_handler:
	call 	EXT(trap)		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
					/      created above.

user_return:
	cmpl	$0x01, EXT(need_ast)	/  4 / See if context switch flag is set
	jne	check_curr_ipl		/ ** /

user_cswitch_check:
	movl	$0x00, EXT(need_ast)	/  4 / reset context switch flag.
	pushl	%esp			/  2 / save stack ptr for return
	call	EXT(astintr)		/ ** / call context switch routine.
	addl	$0x04, %esp		/  2 / clear stack ptr.
	
check_curr_ipl:
	cmpl	$0x00,EXT(curr_ipl)	/  4 / check current ipl
	jz 	final_return		/ ** / see if it is zero.
	jmp	ipl0panic

final_return:
	popl	%gs			/  2 / pop stack structure created
	popl	%fs			/  2 /
	popl	%es			/  2 /
	popl	%ds			/  2 /
	popa				/ 18 /
	
	addl	$0x08,%esp		/  2 / remove hardware structure 
	iret				/275 /
/
///////////////////////////////////////////////////////////////////////////////
/ 	SYSTEM_CALL : a routine to handle system calls which arrive
/	via call gates. The hardware places the same stack image as
/	for a trap EXCEPT that the flags register (EFLAGS) is not
/	pushed, INSTEAD the trap gate is set up such that 1 longword
/	on the stack is set aside for parameters to be passed, also
/	there are no trap #'s or error codes passed, so we set aside
/	space for them such that we maintain a consistant stack image
/	and can take advantage of stack offsets used by various pieces
/	of code.  Basically when done we call syscall() with the same
/	stack image format that exception() above uses to call trap().
/	Basically system calls are treated the same as exceptions, in
/	that we figure out whether we have a regular or a MACH
/	specific system call, and, if regular we call syscall(),
/	otherwise we call MACH_sys_call(), which basically forms the
/	address of the system_call handler and invokes it.
///////////////////////////////////////////////////////////////////////////////

Entry(system_call)

/	1. Form stack image as above, and pad out hardware defined
/	fields.  There are 3 fields that are different here, call
/	gates do not cause the flags register to be pushed as do trap
/	gates, so the call gate is defined such that space is
/	allocated for 1 parameter to be passed from the user stack to
/	the kernel/system call stack. This paramater happens to be
/	placed where the flags register would be put in a trap call,
/	in fact the last pushed entity is copied from the user stack
/	to the kernel stack, so we just rewrite it with the flags
/	register. The other 2 fields that are different are the trap
/	number and error code fields, which are easy to dummy out as
/	they are the last things that would be pushed by the processor
/	had this been a trap call anyway.

	pushf				/  4 / pad out trap number field.
	pushf				/  4 / dummy out error code field.
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/	2. Now we wish to push the flags register onto the stack so as
/	to make it consistant with #defines used elsewhere. The flags
/	register is not directly accessable, so we push it onto the
/	stack ( already done to dummy out trap# and error code
/	fields), and then simply copy it from where it is to where we
/	want it to be.

	movl	Times(ERR,4)(%esp), %eax /  4 /
	movl	%eax,Times(EFL,4)(%esp)	/  4 /

/	3. Now we change to the kernel data space, as we are now in
/	kernel mod and copy the current stack pointer.

	movw	$KDSSEL,%ax		/  2 /
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp,%ebp		/  2 /

/	4. Now we must determine whether this is a common system call
/	or whether this is a special MACH system call demanding quick
/	attention.  We do this by examining the sys_call number passed
/	via %eax (now on the stack). If the number is less then -0x09
/	then this is a special MACH system call.

	movl	Times(EAX,4)(%esp),%eax	/  4 /
	cmpl	$-0x09,%eax		/  2 /
	jnl	user_sys_call		/ ** / 

///////////////////////////////////////////////////////////////////////////////
/ 	MACH_SYS_CALL : a quick subroutine, which instead of calling
/ 	syscall(), calculates the sys_call handling routine address
/ 	and invokes same. This of course only works for a small subset
/ 	of the possible range of system calls.
///////////////////////////////////////////////////////////////////////////////

/	1. Firstly the system call number passed is less than -0x09,
/	so negate it making it positive so that it can be used as an
/	array index. Then we check it aginst boundary limits and call
/	the routine which actually does the real work.

MACH_sys_call:
	negl	%eax			/  2 /
	cmpl	%eax,EXT(mach_trap_count) /  2 /
	jge	call_MACH_trap		/ ** / this is a -ve number inverted

mach_failure:
	movl	$KERN_FAILURE,%eax	/  2 /
	jmp	user_return		/ ** /


/	CALL_MACH_TRAP : %eax is used as an index into a trap handler
/	table, where we can get the trap handler address and the
/	number of parameters to pass to it. Then we use copyin() to
/	get the parameters from user stack into kernel stack.

call_MACH_trap:
	shl	$0x03, %eax		/  3 / adapt index to array element size
	movswl	EXT(mach_trap_table)(%eax),%ecx	/ arg. count
					/  4 / 
	movl	EXT(mach_trap_table)+0x04(%eax), %ebx	/ call handler
					/  4 /
	subl	$0x04,%ecx		/  2 / argv[0] is routine name
					/      so we modify arg. count

/	3. Now take stack pointer and modify it to allow room for the
/	syscall parameters, call copyin() to get the paramaters from
/	user space stack

	subl	%ecx,%esp		/   2 / adjust stack pointer
	movl	%esp,%eax		/   2 / save this stack pointer
		
 	pushl	%ecx			/  2 / push arg count for copyin()
	pushl	%eax			/  2 / push stack pointer for copyin()
	movl	Times(UESP,4)(%ebp), %eax /  4 / get user stk pointer (user args)
	addl	$0x04,%eax		/  2 / adjust to point to parameters
	push	%eax			/  2 / push this for copyin()
	call	EXT(copyin)		/ ** / copyin(arg#,*kern_stk,*user_stk)
	
	addl	$0x0C,%esp		/  2 / get copyin() parameters off stack
	
	call	*%ebx			/ ** / call MACH_system_call handler.

	movl	%ebp,%esp		/  2 / pop system call parameters
	movl	%eax,Times(EAX,4)(%esp)	/  4 / set return value
	movl	%edx,Times(EDX,4)(%esp)	/  4 / 
	
	/*
	 *	Test whether a signal has been requested.  If it has,
	 *	schedule an AST, which will take effect as soon as we
	 *	leave the kernel.  (It's too messy to call psig() here.)
	 */
	call	EXT(current_thread)			/ get the thread
#ifdef	THREAD_EXIT
	cmpl	$THREAD_EXIT,THREAD_EXIT_CODE(%eax)     / abnormal exit?
	jne	alt_call_AST		/ take it with AST if so
#endif	THREAD_EXIT
	movl	UTASK(%eax),%eax	/ point to task U-area
	movl	U_PROCP(%eax),%eax	/ then to proc table slot
	orl	%eax, %eax
	jz	alt_call_restore_state	/ skip if no proc table

	movzbl	P_CURSIG(%eax),%edx
	orl	P_SIG(%eax),%edx
	jz	alt_call_restore_state

#ifdef	THREAD_EXIT
alt_call_AST:
	movl	$0x01, EXT(need_ast)	/ take AST trap (signal) on return to user
#endif	THREAD_EXIT
alt_call_restore_state:
	
	jmp	user_return		/ ** / 

/ 	5. If a common system call, push stack pointer, and call syscall(), on 
/	return remove stack pointer from stack, and return to the user space 
/	routine.

user_sys_call:
#if	MACH_EMULATION > 0
	cmpl	$0,%eax			/  2 /
	jl	normal_sys_call
	call	EXT(current_thread)
	movl	THREAD_TASK(%eax),%eax
	movl	EML_DISPATCH(%eax),%eax
	cmpl	$0,%eax
	je	normal_sys_call		/ eml_dispatch is null, no emulation /
	movl	Times(EAX,4)(%esp),%ebx	/  4 /
	cmpl	%ebx,DISP_COUNT(%eax)
	jle	normal_sys_call		/ Not emulated
	movl	DISP_VECTOR(%eax,%ebx,4),%eax
	cmpl	$0,%eax
	je	normal_sys_call		/ Not emulated

	movl	%esp, %ebp
	pushl	%eax
	subl	$4, Times(UESP,4)(%ebp)	/ make room to push the new sp

	pushl	$4			/ push the new sp
	pushl	Times(UESP,4)(%ebp)
	leal	Times(EIP,4)(%ebp),%ebx
	pushl	%ebx
	call	EXT(copyout)
	leal	12(%esp), %esp
	cmpl	$0, %eax
	je	emul_ok

	leal	4(%esp), %esp		/ pop off eax
	jmp	mach_failure		/ copyout failed

emul_ok:
	popl	%eax			/ get the new pc value back
	movl	%eax,Times(EIP,4)(%esp)	/ fix the PC
	jmp	user_return		/ return 
normal_sys_call:
#endif	MACH_EMULATION > 0
	pushl	%esp			/  2 /
	call	EXT(syscall)		/ ** /
	addl	$0x04,%esp		/  2 /
	jmp	user_return		/ ** /
/
///////////////////////////////////////////////////////////////////////////////
/ 	interrupt :  routine to handle interrupts from external events, this 
/	often requires a change of interrupt priority level, and a call of the 
/	relevant interrupt routine. This routine disables and enable interrupt 
/	as necessary and handles the hardware handshaking with the interrupt 
/	controller hardware.
///////////////////////////////////////////////////////////////////////////////
Entry(INTERRUPT)
interrupt:
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/ 	1. Now that we are in Kernel mode we must select the Kernel data area, 
/	and save a copy of the current stack pointer.

	movw	$KDSSEL,%ax		/  2 /
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp,%ebp		/  2 /

#ifdef	COPROC_SPANPAGE_BUG

/	Save a pointer to the user's registers (cf trap_handler).
/	The user's EIP will be checked in the scheduler to see if
/	we've hit a certain i386 chip bug.

	movl	%esp,EXT(intrlocr0)
#endif	COPROC_SPANPAGE_BUG

/ 	1a. Now we must acknowledge the interrupt and issue an EOI command to 
/	the pics, we send a NON-SPECIFIC EOI, as we assume that the pic 
/	automatically interrupts us with only the highest priority interrupt.

	movl	EXT(master_icw),%edx	/  2 / EOI for master.
	movw	EXT(PICM_OCW2),%ax	/  2 /
	OUTB				/  4 /

	movw	EXT(PICS_OCW2),%ax	/  2 / EOI for slave.
	addw	$SIZE_PIC,%dx		/  2 /
	OUTB				/  4 /

/ 	2. Now we must change the interrupt priority level, with interrupts 
/	turned off. First we get the interrupt number off the stack and get the
/	interrupt level associated with it, then we call set_spl().

	movl	Times(TRAPNO,4)(%ebp), %edi	/  2 /

/	check for spurious interrupt
	movl	EXT(master_icw), %edx
/	AT's slave the second pic on IRQ2
	cmpl	$2, %edi			/ IRQ2
	je	int_check
	cmpl	$15, %edi			/ IRQ15
	jne	int_ok
	addw	$SIZE_PIC,%dx			/  2 /
int_check:
	INB					/ read ISR
	testb	$0x80, %al			/ return if IS7 is off
	jz	interrupt_return

int_ok:
	movzbl	EXT(intpri)(%edi), %eax	/  4 / intpri[int#]  
	cmpl	$SPLHI, %eax		/  2 /
	je	clock_int_handler	/ ** / 
	cmpl	EXT(curr_ipl), %eax	/  2 / 
	je	no_spl			/ ** /

	call	set_spl			/ ** /

/	3. If the new priority is SPLHI this is a special case and means that 
/	this is a clock interrupt, in which case we call a special clock 
/	interrupt handler.

/ 	4. Otherwise, re-enable interrupts and call the relevant interrupt 
/	handler as per the ivect[] array set up in pic_init().

no_spl:
	movl	%eax, %esi		/  2 /

	sti
/	pushl	%edi			/  2 / push int# as int handler arg
	pushl	EXT(iunit)(,%edi,4)	/  2 / push unit# as int handler arg
	movl	$EXT(ivect), %ebx	/  2 / get base of ivect[] array
	call	*(%ebx, %edi, 4)	/  4 / *ivect[int#]()
	addl	$0x04, %esp		/  2 / on return remove int# from stack
	cli				/  3 / disable interrupts

/	 5. Having dealt with the interrupt now we must return to the previous 
/	 interrupt priority level, this is done with interrupts turned off.

	movl	EXT(curr_ipl), %eax
	cmp	%esi, %eax	/  2 / check to see if splx needed
	je	no_splx
	movl	%esi, %eax
	call	iret_spl
no_splx:

/	6. Check to see if interrupt occurred in Kernel or user mode
/	and use the appropriate return algorithm.

interrupt_return:
INTERRUPT_RETURN

///////////////////////////////////////////////////////////////////////////////
/	CLOCK_INT_HANDLER : whereas for any other interrupt, newly
/	arriving interrupts are suppressed only while the interrupt
/	priority level is being changed, this interrupt warrants
/	having new interrupts disabled completely. Here we push the
/	old CS:IP and call hardclock(), in addition if we were
/	interrupted during a user level function AND if the flag
/	dotimein is set, then we call softclock(), on return we reset
/	the interrupt priority level back to what it was before.
///////////////////////////////////////////////////////////////////////////////

clock_int_handler:

	movl	Times(EFL,4)(%ebp), %eax
	btl	$17,%eax
	jnc	1f
	pushl	$USER_CS
	jmp	2f
1:	movl	Times(CS,4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
2:	movl	Times(EIP,4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
	call	EXT(hardclock)		/ ** / hardclock(int#,cs,ip)
	addl	$0x08, %esp		/  2 /
	cmpl	$0x00,EXT(curr_ipl)	/  2 / see if softclock() should
	jnz	int_return		/ ** / be run, if not return.
	cmpl	$0x00,EXT(dotimein)	/  2 /
	jz	int_return
	
	movl	$0x00,EXT(dotimein)	/  2 /
	call	EXT(spl1)		/ ** /	 this piece at spl1
	sti
	movl	Times(EFL,4)(%ebp), %eax
	btl	$17,%eax
	jnc	1f
	pushl	$USER_CS
	jmp	2f
1:	movl	Times(CS,4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
2:	movl	Times(EIP,4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
	call 	EXT(softclock)		/ ** / softclock(int#,cs,ip)
	addl	$0x08,%esp		/  2 /
	cli				/  3 /
	call	EXT(spl0)		/ ** /
int_return:
INTERRUPT_RETURN

Entry(Bpt)
ENTRY(bpt)
	pushl	%ebp
	movl	%esp, %ebp
	.byte	0xcc
	leave
	ret
/
///////////////////////////////////////////////////////////////////////////////
/	SPLn : change interrupt priority level to that in %eax
/	SPLOFF : disable all interrupts, saving interrupt flag
/	SPLON: re-enable interrupt flag, undoes sploff()
/	Warning: SPLn and SPLOFF aren't nestable.  That is,
/		a = sploff();
/		...
/		b = splmumble();
/		...
/		splx(b);
/		...
/		splon(a);
/	is going to do the wrong thing.
///////////////////////////////////////////////////////////////////////////////
#ifdef	SPL_COUNT
#define SPL_INC(x) incl	EXT(c/**/x)
		.data
DATA(cspl0)	.long 0
DATA(cspl1)	.long 0
DATA(cspl2)	.long 0
DATA(cspl3)	.long 0

DATA(cspl4)	.long 0
DATA(cspl5)	.long 0
DATA(cspl6)	.long 0
DATA(cspl7)	.long 0

DATA(csplx)	.long 0
DATA(csply)	.long 0
DATA(csplz)	.long 0
DATA(csplw)	.long 0
#else	SPL_COUNT
#define SPL_INC(x)
#endif	SPL_COUNT
		.text

Entry(spl0)
SPL_INC(spl0)
	movl    $SPL0, %eax
	jmp	set_spl

Entry(splsoftclock)
Entry(spl1)
SPL_INC(spl1)
	movl    $SPL1, %eax
	jmp	set_spl

Entry(spl2)
SPL_INC(spl2)
	movl    $SPL2, %eax
	jmp	set_spl

Entry(spl3)
SPL_INC(spl3)
	movl    $SPL3, %eax
	jmp	set_spl

Entry(splnet)
Entry(splhdw)
Entry(spl4)
SPL_INC(spl4)
	movl    $SPL4, %eax
	jmp	set_spl

Entry(splbio)
Entry(spl5)
SPL_INC(spl5)
	movl    $SPL5, %eax
	jmp	set_spl

Entry(spltty)
Entry(spl6)
SPL_INC(spl6)
	movl    $SPL6, %eax
	jmp	set_spl

Entry(splimp)
Entry(splclock)
Entry(splvm)
Entry(splsched)
Entry(splhigh)
Entry(splhi)
Entry(spl7)
SPL_INC(spl7)
	cli				/  3 / disable interrupts
	movl	EXT(curr_ipl),%eax	/  4 /
	movl	$IPLHI, EXT(curr_ipl)	/  2 /
	ret				/ 10 /
/					------
/					  19

Entry(sploff)				/  7 /
	pushf				/  2 / Flags reg NOT accessable
	popl	%eax			/  2 / push onto stk, pop it into reg.
	cli				/  3 / DISABLE ALL INTERRUPTS
	ret				/  7 /
/					------
/					  21

Entry(splon)				/  7 /
	pushl	MASK(%esp)		/  4 / Flags regs not directly settable.
	popf				/  4 / push value, pop into flags reg.
					/      IF ints were enabled before 
					/	then they are re-enabled now.
	ret				/  7 /
/					------
/					  22

///////////////////////////////////////////////////////////////////////////////
/	SPL : this routine sets the interrupt priority level, it is
/	called from one of the above spln subroutines ONLY, NO-ONE
/	should EVER call set_spl directly as it assumes that the
/	parameters passed in are gospel.  
/	SPLX	: This routine is used to set the ipl BACK to a level
/	it was at before spln() was called, which in turn calls
/	set_spl(), which returns (via %eax) the value of the curr_ipl
/	prior to spln() being called, this routine is passed this
/	level and so must check that it makes sense and if so then
/	simply calls set_spl() with the appropriate interrupt level.
///////////////////////////////////////////////////////////////////////////////

Entry(splx)
SPL_INC(splx)
	movl	0x04(%esp),%eax		/  4 / get interrupt level from stack

	cmpl	$0x00,%eax		/  2 / check if  < 0
	jl	splxpanic		/  3 /

	cmpl	$SPLHI,%eax		/  2 / check if too high
	ja	splxpanic		/  3 /
/					------
/					  14

///////////////////////////////////////////////////////////////////////////////
/	SET_SPL : This routine sets curr_spl, ipl, and the pic_mask as
/	appropriate, basically given an spl# to adopt, see if it is
/	the same as the old spl#, if so return. If the numbers are
/	different, then set curr_spl, now check the corresponding ipl
/	for the spl requested, if they are the same then return
/	otherwise set the new ipl and set the pic masks accordingly.
///////////////////////////////////////////////////////////////////////////////

set_spl:				

	pushl	%ebp			/ 2 /
	movl	%esp,%ebp		/ 2 /
	cli				/ 3 / disable interrupts
	movl	EXT(curr_ipl), %edx	/ 4 / get OLD ipl level
	pushl	%edx			/ 2 / save old level for return
	movl	%eax,EXT(curr_ipl)	/ 4 / set NEW ipl level
	cmpl	$SPLHI, %eax		/  2 / if SPLHI
	je	spl_intoff		/  3 / return with interrupt off
	movw	EXT(pic_mask)(,%eax,2), %ax / 5 /
	cmpw	EXT(curr_pic_mask),%ax 	/ 5 /
	je	spl_return		/ 7 /
	movw	%ax, EXT(curr_pic_mask)
	SPL_INC(sply)
SET_PIC_MASK				/16 /
spl_return:
	sti				/ 3 /
spl_intoff:
	popl	%eax			/ 2 / return old level
	pop	%ebp			/ 2 /
	ret				/10 /
/					-----
/				         79

iret_spl:				
	cli				/ 3 / disable interrupts
	movl	%eax,EXT(curr_ipl)	/ 4 / set NEW ipl level
/ SPLHI is not possible, for we can not be returning to splhi since
/ we'd never be interrupted.
/	cmpl	$SPLHI, %eax		/  2 / if SPLHI
/	je	1f
	movw	EXT(pic_mask)(,%eax,2), %ax / 5 /
	cmpw	EXT(curr_pic_mask),%ax 	/ 5 /
	je	1f
	movw	%ax, EXT(curr_pic_mask)
	SPL_INC(sply)
SET_PIC_MASK				/16 /
1:
	ret				/10 /
/					-----
/				         79

/


///////////////////////////////////////////////////////////////////////////////
/	These routine get/set various registers that are not directly
/	accessable by NORMAL user level routines.
///////////////////////////////////////////////////////////////////////////////

/*
 * _clts();
 *	clear Task Switched bit in CR0 
 */
ENTRY(_clts)
	clts
	ret

/* 
 * _fnclex();
 *	clear '387 exceptions 
 */
ENTRY(_fnclex)
	fnclex
	ret

/* 
 * _fninit();
 *	initialize '387 
 */
ENTRY(_fninit)
	fninit
	ret

/* 
 * _fldcw(cw);
 * short cw;
 *	load control word
 */
ENTRY(_fldcw)
	fldcw	4(%esp)
	ret

/*
 * cw = _fstcw();
 * short cw;
 *	store control word
 */
ENTRY(_fstcw)
	pushl	%eax
	fstcw	(%esp)
	popl	%eax
	ret

/*
 * sw = _fnstsw();
 * short sw;
 *	store status word
 */
ENTRY(_fnstsw)
	pushl	%eax
	fnstsw	(%esp)
	popl	%eax
	ret

/*
 * savefp(addr);
 * u_char *addr;
 *	Save coprocessor state into buffer starting at "addr".
 *	Note that unmasked coprocessor exceptions are not handled;
 *	they'll eventually be handled when the coprocessor state is
 *	restored.  I'm not sure about needing the "fnclex".  It might
 *	be important on non-AT systems. -mdk
 *	Called from fpsave().
 */
ENTRY(savefp)
	clts
	movl	4(%esp), %eax
	fnsave	(%eax)
	fnclex
	fwait
	ret

/*
 * restorefp(addr);
 * u_char *addr;
 *	Restore coprocesor state from buffer starting at "addr".
 */
ENTRY(restorefp)
	clts
	movl    4(%esp), %eax
	frstor  (%eax)
	ret

ENTRY(setts)
	movl    %cr0, %eax
	orl     $0x08, %eax
	movl    %eax, %cr0
	ret

ENTRY(flushtlb)				/  7 /
	movl	%cr3, %eax		/  2 /
	movl	%eax, %cr3		/  2 /
	ret				/  7 /
/					------
/					  18

ENTRY(_cr2)				/  7 /
	movl	%cr2, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_cr3)				/  7 /
	movl	%cr3, %eax		/  2 /
	andl	$0x7FFFFFFF,%eax	/  2 /
	ret 				/  7 /
/					------
/					  18

ENTRY(_dr0)				/  7 /
	movl    %db0, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_dr1)				/  7 /
	movl    %db1, %eax		/  2 /
	ret				/  7 /
/					------
/					  16 

ENTRY(_dr2)				/  7 /
	movl    %db2, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_dr3)				/  7 /
	movl    %db3, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_dr6)				/  7 /
	movl    %db6, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_dr7)				/  7 /
	movl    %db7, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

ENTRY(_wdr0)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db0		/  2 /
	ret				/  7 /
/					------
/					  18

ENTRY(_wdr1)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db1		/  2 /
	ret				/  7 /
/					------
/					  18

ENTRY(_wdr2)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db2		/  2 /
	ret				/  7 /
/					------
/					  18

ENTRY(_wdr3)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db3		/  2 /
	ret				/  7 /

ENTRY(_wdr6)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db6		/  2 /
	ret				/  7 /

ENTRY(_wdr7)				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db7		/  2 /
	ret				/  7 /

ENTRY(get_tr)				/  7 /
	xorl	%eax, %eax		/  2 /
	str	%ax			/  2 /
	ret				/  7 /

ENTRY(loadtr)				/  7 /
	movw	0x04(%esp), %ax		/  2 /
	ltr	%ax			/ 23 /
	ret				/  7 /

Entry(get_ldt)				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	movl	0x08(%ebp),%eax		/  4 /
	sldt	%eax			/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /

Entry(set_ldt)
	pushl	%ebp			/  7 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	movl	0x08(%ebp),%eax		/  4 /
	lldt	%eax			/ 20 /
	popl	%ebp			/  2 /
	ret				/  7 /

Entry(get_gdt)				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	movl	0x08(%ebp),%ebx		/  4 /
	sgdt	(%ebx)			/  9 /
	popl	%ebp			/  2 /
	ret				/  7 /

Entry(get_cr3)				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	movl	%cr3,%eax		/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /

	.data
	.align ALIGN
cr3_kludge:
#ifdef	COPROC_CR3
	.long	0x080000000
#else	COPROC_CR3
	.long	0
#endif	COPROC_CR3

	.text
Entry(set_cr3)				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	movl	0x08(%ebp),%eax		/  4 /

/ Setting the high order bit of the page directory base is a workaround
/ for 386 B-step errata #21. It works on Olivetti, Intel, and Prime
/ machines, but it is not guaranteed to work on all systems.

	orl     cr3_kludge, %eax
	movl	%eax,%cr3		/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /
/
#ifdef	THREAD_EXIT
//////////////////////////////////////////////////////////////////////////////
/	ASTON, ASTOFF routines to change the value of do_an_ast, a global 
/	variable that is used to determine whether or not a context switch 
/	should be considered during the return from any interrupts to a user
/	level routine. ast = ASynchronous Task.
//////////////////////////////////////////////////////////////////////////////

ENTRY(aston)				/  7 / 
	movl	$0x01,EXT(need_ast)	/  4 /
	ret				/  7 /
/					------
/					  18

ENTRY(astoff)				/  7 /
	movl	$0x00,EXT(need_ast)	/  4 /
	ret				/  7 /
/					------
/					  18
#endif	THREAD_EXIT
/////////////////////////////////////////////////////////////////////////////
/	THREAD_BOOTSTRAP : tbd
/////////////////////////////////////////////////////////////////////////////

Entry(thread_bootstrap)
	call	EXT(spl0)
/	incl	cnt+V_SYSCALL
	jmp     user_return	/ jump to common return to user code

/
/			PANIC CALLS
ipl0panic:
	pushl	EXT(curr_ipl)
	pushl	$ipl0panic1
	call	EXT(printf)
	jmp	panic_hlt

splpanic:
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splpanic2
	call	EXT(printf)
	jmp	panic_hlt

spl7panic:
	pushl	$0
	pushl	%eax
	pushl	$spl7panic2
	call	EXT(printf)
	jmp	panic_hlt

splxpanic:
	pushl	EXT(curr_ipl)	/ current level
	pushl	%eax		/ new level
	pushl	$splxpanic2
	call	EXT(printf)
	jmp	panic_hlt

splintpanic:
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splintpanic2
	call	EXT(printf)
	jmp	panic_hlt

splxintpanic:
	cli
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splxintpanic2
	call	EXT(printf)

panic_hlt:
	/*
	 * We haven't poped printf's args.  Do we care?
	 */
	pushl	$splpanicstr
	call	EXT(panic)
	hlt
	.data
splpanicstr:
	String	"splpanic"
	.byte	0
ipl0panic1:
	String	"ret_user(%x): IPL not zero at return to user mode\n"
	.byte	0
splpanic2:
	String	"spl(%x, %x): logic error in locore.s\n"
	.byte	0
spl7panic2:
	String	"spl7(%x, %x): logic error in locore.s\n"
	.byte	0
splxpanic2:
	String	"splx(old %x, new %x): logic error in locore.s\n"
	.byte	0
splintpanic2:
	String	"splint(%x, %x): logic error in locore.s\n"
	.byte	0
splxintpanic2:
	String	"splxint(%x, %x): logic error in locore.s\n"
	.byte	0
	.text
/

Entry(vstart)				/  7 /
	call	EXT(i386_init)

/ Set up for floating point.  Check for any chip at all by trying to
/ do a reset.  if that succeeds, differentiate via cr0.

	clts                            / clear task switched bit in CR0
	fninit                          / initialize chip
	fstsw	%ax			/ get status
	orb	%al,%al			/ status zero? 0 = chip present
	jnz     mathemul                / no, use emulator

/ at this point we know we have a chip of some sort; 
/ use cr0 to differentiate.

	movl    %cr0,%edx               / check for 387 present flag
	testl	$CR0_ET,%edx            / ...
	jz      is287                   / z -> 387 not present
	movb    $FP_387,EXT(fp_kind)	/ we have a 387 chip
	jmp     mathchip

/ No 387; determine whether we have a 80287.
is287:
/	fsetpm				/ set the 80287 into protected mode
	.byte	0xe4, 0xdb, 0x9b
	movb	$FP_287,EXT(fp_kind)	/ we have a 287 chip

/ We have either a 287 or a 387.
mathchip:
#ifdef	wheeze
	andl    $-1![CR0_TS|CR0_EM],%edx / clear emulate math chip bit
#else	wheeze
	andl    $-1^(CR0_TS|CR0_EM),%edx / clear emulate math chip bit
#endif	wheeze
	orl     $CR0_MP,%edx            / set math chip present bit
	movl    %edx,%cr0               / in machine status word
	jmp	cont

mathemul:
/ Assume we have an emulator
	movl	%cr0,%edx
#ifdef	wheeze
	andl	$-1!CR0_MP,%edx
#else	wheeze
	andl	$-1^CR0_MP,%edx
#endif	wheeze
	orl     $CR0_EM,%edx            / set math emulation
	movl	%edx,%cr0
	movb	$FP_SW,EXT(fp_kind)	/ signify that we are emulating
cont:
/ BIOS/DOS hack				/ this says don't test memory
	movl	$0xc0000000, %edx
	addl	$0x472, %edx		/ on reboot/reset
	movw	$0x1234, %ax		/ pretty obscure
	movw	%ax, (%edx)
/ BIOS/DOS hack
	call	EXT(setup_main)

/ Task switch to the first thread.
/	This is a 16 bit long jump.
	.byte	0xEA
	.long	0
	Value	JTSSSEL

	pushl	$panic_msg1
	jmp	setup_hlt

ENTRY(system_bootstrap)
	call	EXT(main)
/	Should never get here
	pushl	$panic_msg
setup_hlt:
	call	EXT(panic)
	jmp	setup_hlt

ENTRY(start_init)
	addl	$8,%esp			/ return addresses
	pushl	%esp
	call	EXT(init_regs)
	popl	%eax
#ifdef	COPROC_SPANPAGE_BUG
	pushl	$0
	call	EXT(i386_coproc_hang)
	leal	4(%esp), %esp
#endif	COPROC_SPANPAGE_BUG
	jmp	user_return

panic_msg:
	String	"First thread returned\n"
	.byte	0
panic_msg1:
	String	"Jump to tss failed\n"
	.byte	0



/////////////////////////////////////////////////////////////////////////////
/	The following routines read and write I/O adress space
/		outb (port_addr, val)
/		outw (port_addr, val)
/		outl (port_addr, val)
/		loutw(port_addr, mem_addr, cnt)
/	unchar	inb  (port_addr     )
/	ushort	inw  (port_addr     )
/	long	inl  (port_addr     )
/	ushort	linw (port_addr, mem_addr, cnt)
/////////////////////////////////////////////////////////////////////////////

#define PORT	 4
#define VAL	 8
#define ADDR	 8
#define COUNT	12

ENTRY(outb)				/  7 / 
	movw	PORT(%esp), %dx		/  4 /
	movb	VAL(%esp), %al		/  4 /
	OUTB				/  4 /
#ifdef	iPSC2
	mull    %ecx    / Delay by doing long multiply
#endif	iPSC2

	ret				/  7 /
/					------
/					  26
ENTRY(outw)				/  7 /	outw ( port#, data )
	movw	PORT(%esp), %dx		/  4 /
	movw	VAL(%esp), %ax		/  4 /
	data16				
	OUTL				/  4 /
	ret				/  7 /
/					------
/					  26
ENTRY(outl)				/  7 /	outl ( port#, data)
	movw	PORT(%esp), %dx		/  4 /
	movl	VAL(%esp), %eax		/  4 /
	OUTL				/  4 /
	ret				/  7 /
/					------
/					  26
ENTRY(loutw)				/  7 /	loutw( port#, addr, cnt)
	movl	%esi, %eax		/  ? /

	movl	PORT(%esp),%edx		/  4 /
	movl	ADDR(%esp),%esi		/  4 /
	movl	COUNT(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	data16
	outsl				/  8 /

	movl	%eax, %esi		/  ? /
	ret				/  7 /
/					------
/					  ??
ENTRY(loutb)				/  7 /	loutw( port#, addr, cnt)
	movl	%esi, %eax		/  ? /

	movl	PORT(%esp),%edx		/  4 /
	movl	ADDR(%esp),%esi		/  4 /
	movl	COUNT(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	data16
	outsb				/  8 /

	movl	%eax, %esi		/  ? /
	ret				/  7 /
/					------
/					  50 + (ECX * 11)

ENTRY(inb)				/  7 /
	subl    %eax, %eax		/  2 /	clear EAX
	movw	PORT(%esp), %dx		/  4 /
	INB				/  4 /
#ifdef	iPSC2
/ Do a long multiply to delay, must save and restore EAX which
/ is used to hold result of multiply
	pushl   %eax
	mull    %ecx
	popl    %eax
#endif	iPSC2
	ret				/  7 /
/					------
/					  24

ENTRY(inw)				/  7 /
	subl    %eax, %eax		/  2 /
	movw	PORT(%esp), %dx		/  4 /
	data16
	INL				/  4 /
	ret				/  7 /
/					------
/					  24

ENTRY(inl)				/  7 /
	movw	PORT(%esp), %dx		/  4 /
	INL				/  4 /
	ret				/  7 /
/					------
/					  22

ENTRY(linw)				/  7 /
	movl	%edi, %eax		/  ? /

	movl	PORT(%esp),%edx		/  4 /
	movl	ADDR(%esp),%edi		/  4 /
	movl	COUNT(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	data16
	insl				/  6 /

	movl	%eax, %edi		/  ? /
	ret				/  7 /
/					------
/					  ??

ENTRY(linb)				/  7 /
	movl	%edi, %eax		/  2 /

	movl	PORT(%esp),%edx		/  4 /
	movl	ADDR(%esp),%edi		/  4 /
	movl	COUNT(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	data16
	insb				/  6 /

	movl	%eax, %edi		/  2 /
	ret				/  7 /
/					------
/					  50 + (ECX * 11)

///////////////////////////////////////////////////////////////////////////////
/	addupc(pc, &u.u_prof, tics)
///////////////////////////////////////////////////////////////////////////////

/ offset relative to u.u_prof.

Entry(addupc)
	pushl	%ebp
	movl	%esp, %ebp		/ set up frame
	MCOUNT
	pushl	%edi

	movl	UPROF(%ebp), %ecx	/ &u.u_prof
	movl	PC(%ebp), %eax		/ pc
	subl	PR_OFF(%ecx), %eax	/ corrected pc
	jl	addret1
	mull	PR_SCALE(%ecx)		/ Multiply by fractional result
	shrdl	$16,%edx,%eax
	andl	$0xFFFFFFFE, %eax
	cmpl	PR_SIZE(%ecx), %eax	/ length
	jg	addret1
	addl	PR_BASE(%ecx), %eax	/ base
	movl	%eax, %edi		/ Save during userwrite call
	pushl	$4			/ COUNT
	pushl	%edi			/ ADDRESS
	call	EXT(userwrite)
	addl	$8, %esp
	orl	%eax,%eax
	jnz	adderr
	call	EXT(current_thread)
	movl	$adderr,THREAD_RECOVER(%eax)
	movswl	(%edi), %ecx
	addl	TICS(%ebp), %ecx
	movw	%ecx, (%edi)
addret1:
	movl	$0,THREAD_RECOVER(%eax)
	popl	%edi
	popl	%ebp
	ret
adderr:
	movl	$0, PR_SCALE(%ebx)
	jmp	addret1
/
///////////////////////////////////////////////////////////////////////////////
/	ISUSERDATA : This function returns with ZF set if its arg is in user 
/	space, else with ZF cleared. For the sake of performance, the argument 
/	is in EAX, not on the stack. This is NOT a public function.  
/	Mainly used in fubyte(), etc.
///////////////////////////////////////////////////////////////////////////////

LCL(isuserdata):			/  7 /
	cmpl    $MINUVADR, %eax		/  2 /
	jb	notuser			/ ** /
	cmpl    $MAXUVADR-1, %eax	/  2 /
	ja      notuser			/ ** /
userok:
	xorl	%ebx, %ebx		/  2 / set zero flag
notuser:
	ret				/  7 /
/					------
/		is usersata		  26
/		is NOT userdata		  16/28

///////////////////////////////////////////////////////////////////////////////
/	ISUSERSTRING : Same as isuser, but tests for an entire string in user 
/	space. On entry, start of string is in eax, end in edx. On return, 
/	ZF ==> string is OK.  This is NOT a public function.  
///////////////////////////////////////////////////////////////////////////////

isuserstring:				/  7 /
	cmpl    $MINUVADR, %eax		/  2 /
	jb	notuser			/ ** /
	cmpl    $MAXUVADR-1, %eax	/  2 /
	ja      notuser			/ ** /

	cmpl    $MINUVADR, %edx		/  2 /
	jb      notuser			/ ** /
	cmpl    $MAXUVADR-1, %edx	/  2 /
	ja      notuser			/ ** /

	jmp	userok			/  7 /
/					------
/	is     userstring		  41
/	is NOT userstring		21/28/33/38


///////////////////////////////////////////////////////////////////////////////
/	CURRENT_THREAD : returns number of CURRENTLY active threads
///////////////////////////////////////////////////////////////////////////////

ENTRY(current_thread)			/  7 /
	movl	EXT(active_threads),%eax /  4 / only because cpu_number()==0
	ret				/  7 /
/					------
/					  18

///////////////////////////////////////////////////////////////////////////////
/	TENMICROSEC : The following code is used to waste 10 microseconds.
/	It is initialized in pit.c.
///////////////////////////////////////////////////////////////////////////////

ENTRY(tenmicrosec)			/  7 /
	movl	EXT(microdata), %ecx	/  4 / Loop uses ecx.

microloop:
	loop	microloop		/ 11 /
	ret				/  7 /
/					------
/					18 + (ECX * 11)

///////////////////////////////////////////////////////////////////////////////
/	PRF_ACCESS : tbd
///////////////////////////////////////////////////////////////////////////////

Entry(prf_access)			/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	MCOUNT
	pushl	%es			/  2 /

	movl	8(%ebp),%eax		/  4 /
	movw	%ax,%es			/  2 /
	xorl	%eax,%eax		/  2 /
	movb	%es:12(%ebp),%al	/  4 /

	popl	%es			/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /
/					------
/					  36

///////////////////////////////////////////////////////////////////////////////
/	SIG_CLEAN : tbd
///////////////////////////////////////////////////////////////////////////////

ENTRY(sig_clean)
	/ set up the stack to look as in reg.h
	subl    $8, %esp        	/  2 / pad stk with ERRCODE and TRAPNO
	pusha				/ 18 / save user registers
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

	pushfl				/  2 /
	popl	%eax			/  2 /
	movl    %eax, Times(EFL,4)(%esp) /  4 /
	movw	$KDSSEL, %ax		/  2 /
	movw	%ax, %ds		/  2 /
	movw	%ax, %es		/  2 /
	movl	%esp, %ebp		/  2 /
	pushl   $F_ON			/  2 /
	popfl				/  2 /

	pushl	%esp			/  2 / argument to sigclean
	call    EXT(osigreturn)		/ restore pre-signal state
	addl    $4, %esp        	/  2 / pop arg


	jmp	short_user_ret
/	jmp     do_ret          / Can't do regular return-to-user processing



///////////////////////////////////////////////////////////////////////////////
/	check for kernel access
/	assume segment descr. allows access
/	check page dir and page table entries
/	check for VALID page or page with USER protection
///////////////////////////////////////////////////////////////////////////////

/ENTRY(kernacc)				/  7 /
/	pushl	%ebp			/  2 /  set up stack image
/	movl	%esp,%ebp		/  2 /
/	pushl	%esi			/  2 /
/	pushl	%ebx			/  2 /
/	movl	%cr3,%esi		/  4 /
/	addl	$KVBASE,%esi		/  2 / kpde
/	movl	8(%ebp),%eax		/  4 / first address
/	movl	12(%ebp),%ebx		/  4 / length
/	addl	%eax,%ebx		/  2 /
/	decl	%ebx			/  2 / last adr
/	shrl	$PTESHIFT,%eax		/  2 / first chunk/page
/	shrl	$PTESHIFT,%ebx		/  2 / last chunk/page
/kacc1:
/	movl	%eax,%ecx
/	shrl	$PDESHIFT-PTESHIFT,%ecx	/  2 / dxr index
/	movl	(%esi,%ecx,4),%edx	/  4 / pd entry
/	testb	$1,%dl			/  2 / VALID
/	jz	kaccerr			/ ** /
/	addl	$KVBASE,%edx		/  2 /
/	andl	$-1!I386_OFFMASK,%edx	/  4 /
/	movl	%eax,%ecx		/  2 /
/	andl	$PTEMASK,%ecx		/  2 /
/	movl	(%edx,%ecx,4),%edx	/  4 / pt entry
/	testb	$5,%dl			/  2 / VALID or USER page
/	jz	kaccerr			/ ** /
/	incl	%eax			/  2 /
/	cmpl	%ebx,%eax		/  2 /
/	jle	kacc1			/ ** /
/	movl	$1,%eax			/  2 /
/kaccout:
/	popl	%ebx			/  2 /
/	popl	%esi			/  2 /
/	popl	%ebp			/  2 /
/	ret				/  7 /
/kaccerr:
/	subl	%eax,%eax		/  2 /
/	jmp	kaccout			/  7 /
