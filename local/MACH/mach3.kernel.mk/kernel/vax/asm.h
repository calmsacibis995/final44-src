/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 *	File:	vax/asm.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This header file is intended to hold definitions useful for Vax
 *	assembly routines.
 *
 * HISTORY
 * $Log:	asm.h,v $
 * Revision 2.4  93/02/01  09:51:25  danner
 * 	Added include of gcc_asm.h to compensate for lack of working -include switch.
 * 
 * Revision 2.3  91/05/14  17:40:59  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:10:05  dbg
 * 	Convert for ANSI C.
 * 	[91/04/23            dbg]
 * 
 * Revision 2.1  89/08/03  16:13:08  rwd
 * Created.
 * 
 *  5-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved CPU_NUMBER_R0 here from vax/cpu.h.  Made it dispatch
 *	to a model-dependent cpu_number routine; the ESP hack is not
 *	reliable.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created with defintions for ENTRY and JSBENTRY.
 *
 */

#include <cpus.h>
#ifdef MACH_KERNEL
#include <vax/gcc_asm.h>
#endif

#ifdef GPROF
#ifdef	__STDC__
#define	ENTRY(name, regs) \
	.globl _ ## name; .align 1; _ ## name: .word regs; jsb mcount
#define	JSBENTRY(name, regs) \
	.globl _ ## name; _ ## name: \
	movl fp,-(sp); movab -12(sp),fp; pushr $(regs); jsb mcount; \
	popr $(regs); movl (sp)+,fp
#else
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs; jsb mcount
#define	JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name: \
	movl fp,-(sp); movab -12(sp),fp; pushr $(regs); jsb mcount; \
	popr $(regs); movl (sp)+,fp
#endif	/* __STDC__ */
#else
#ifdef	__STDC__
#define	ENTRY(name, regs) \
	.globl _ ## name; .align 1; _ ## name ## : .word regs
#define	JSBENTRY(name, regs) \
	.globl _ ## name; _ ## name ## :
#else
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs
#define	JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name:
#endif	/* __STDC__ */
#endif GPROF

#define R0	0x01
#define R1	0x02
#define R2	0x04
#define R3	0x08
#define R4	0x10
#define R5	0x20
#define R6	0x40
#define R7	0x80
#define R8	0x100
#define R9	0x200
#define R10	0x400
#define R11	0x800

#if	MACH
#if	NCPUS == 1
#define CPU_NUMBER_R0	clrl	r0
#else	NCPUS == 1
#define	CPU_NUMBER_R0	jsb	*_Cpu_number_ptr
#endif	NCPUS == 1
#endif	MACH
