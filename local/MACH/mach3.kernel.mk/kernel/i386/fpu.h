/* 
 * Mach Operating System
 * Copyright (c) 1994,1992,1991 Carnegie Mellon University
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
 * HISTORY
 * $Log:	fpu.h,v $
 * Revision 2.4  94/12/15  15:23:56  dbg
 * 	Added ANSI function prototypes.
 * 	[94/01/13            dbg]
 * 
 * Revision 2.3  92/02/19  15:08:04  elf
 * 	Added fwait()
 * 	[92/01/19            jvh]
 * 
 * Revision 2.2  92/01/03  20:05:49  dbg
 * 	Created.
 * 	[91/12/23  16:32:15  dbg]
 * 
 */

#ifndef	_I386_FPU_H_
#define	_I386_FPU_H_

/*
 * Macro definitions for routines to manipulate the
 * floating-point processor.
 */

#include <cpus.h>
#include <fpe.h>

#include <mach/kern_return.h>
#include <kern/kern_types.h>

#include <i386/proc_reg.h>
#include <i386/thread.h>

#ifdef	__GNUC__
/*
 * FPU instructions.
 */
#define	fninit() \
	asm volatile("fninit")

#define	fnstcw(control) \
	asm("fnstcw %0" : "=m" (*(unsigned short *)(control)))

#define	fldcw(control) \
	asm volatile("fldcw %0" : : "m" (*(unsigned short *) &(control)) )

#define	fnstsw() \
    ({ \
	unsigned short _status__; \
	asm("fnstsw %0" : "=ma" (_status__)); \
	_status__; \
    })

#define	fnclex() \
	asm volatile("fnclex")

#define	fnsave(state) \
	asm volatile("fnsave %0" : "=m" (*state))

#define	frstor(state) \
	asm volatile("frstor %0" : : "m" (state))

#define fwait() \
    	asm volatile("fwait")

#endif	/* __GNUC__ */

/*
 *	Exported routines for FPU.
 */

extern void
init_fpu(void);

extern void
fpu_module_init(void);

extern void
fp_free(struct i386_fpsave_state *);

extern kern_return_t
fpu_set_state(
	thread_t	thread,
	struct i386_float_state *state);

extern kern_return_t
fpu_get_state(
	thread_t	thread,
	struct i386_float_state *state);

extern void
fpnoextflt(void);

extern no_return
fpextovrflt(void);

extern void
fpexterrflt(void);

extern void
fp_save(thread_t);

extern void
fp_state_alloc(void);

extern void
fpintr(void);

#if	FPE
/*
 *	Routines from floating-point emulator linkage.
 */
extern void fpe_init(void);

extern void enable_fpe(
	struct i386_fpsave_state *);

extern void disable_fpe(void);

extern boolean_t
fp_emul_error(struct i386_saved_state *);

extern no_return
fpe_exception_fixup(
	int	exc,
	int	code,
	int	subcode);

#endif	/* FPE */

/*
 * If floating-point instructions are emulated,
 * we must load the floating-point register selector
 * when switching to a new thread.
 */
#if	FPE
#define	fpu_save_context(thread) \
    { \
	if (fp_kind == FP_SOFT) \
	    disable_fpe(); \
	else \
	    set_ts(); \
    }

#define	fpu_load_context(pcb) \
    { \
	register struct i386_fpsave_state *ifps; \
	if (fp_kind == FP_SOFT && (ifps = pcb->ims.ifps) != 0) \
	    enable_fpe(ifps); \
    }

#else	/* no FPE */

#define	fpu_load_context(pcb)

/*
 * Save thread`s FPU context.
 * If only one CPU, we just set the task-switched bit,
 * to keep the new thread from using the coprocessor.
 * If multiple CPUs, we save the entire state.
 */
#if	NCPUS > 1
#define	fpu_save_context(thread) \
    { \
	register struct i386_fpsave_state *ifps; \
	ifps = (thread)->pcb->ims.ifps; \
	if (ifps != 0 && !ifps->fp_valid) { \
	    /* registers are in FPU - save to memory */ \
	    ifps->fp_valid = TRUE; \
	    fnsave(&ifps->fp_save_state); \
	    set_ts(); \
	} \
    }
	    
#else	/* NCPUS == 1 */
#define	fpu_save_context(thread) \
    { \
	    set_ts(); \
    }

#endif	/* NCPUS == 1 */

#endif	/* no FPE */

extern int	fp_kind;

#endif	/* _I386_FPU_H_ */
