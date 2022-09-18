/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
 * $Log:	thread.h,v $
 * Revision 2.5  92/03/03  14:23:01  rpd
 * 	Added dummy definition of syscall_emulation_sync.
 * 	[92/03/03            rpd]
 * 
 * Revision 2.4  91/05/14  17:46:11  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:27:47  dbg
 * 	Support stack switching.
 * 	Add inline assembler definition for current_thread and
 * 	load_context.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.2  91/01/08  16:42:18  rpd
 * 	Added KEEP_STACKS support.
 * 	[91/01/06            rpd]
 * 
 * Revision 2.1  89/08/03  16:13:44  rwd
 * Created.
 * 
 * 18-Jul-88  David Golub (dbg) at Carnegie-Mellon University
 *	Moved saved kernel and user state definitions from pcb.h to this
 *	file.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created by defining CURRENT_THREAD.
 *
 */

/*
 *	File:	vax/thread.h
 *	Author:	Avadis Tevanian, Jr., 1987.
 *
 *	This file defines machine specific, thread related structures,
 *	variables and macros.
 */

#ifndef	_VAX_THREAD_H_
#define	_VAX_THREAD_H_

#include <mach/kern_return.h>

#include <vax/ast.h>
#include <vax/psl.h>

/*
 *	State saved on trap or system call,
 *	by user or kernel.  User state is in PCB.
 *	Kernel state is on kernel stack.
 *	Stack pointer is NOT saved.  It is in processor
 *	register USP or in PCB for user state.
 */

struct vax_saved_state {
	int	r0;
	int	r1;
	int	r2;
	int	r3;
	int	r4;
	int	r5;
	int	r6;
	int	r7;
	int	r8;
	int	r9;
	int	r10;
	int	r11;
	int	ap;
	int	fp;
	int	exception;
	int	code;
	int	subcode;
	int	pc;
	int	psl;
};

/*
 * State saved on kernel context switch.
 * Includes space for 3 arguments passed to switch_context.
 */
struct vax_kernel_state {
	int	handler;
	int	mask;		/* callS, save r6..r11 */
	int	ap;
	int	fp;
	int	pc;
	int	r6;
	int	r7;
	int	r8;
	int	r9;
	int	r10;
	int	r11;
	int	arg_count;	/* 3 arguments to switch_context */
	int	old_thread;
	int	continuation;
	int	new_thread;
};

struct vax_pcb {
	struct vax_kernel_state	*vks_p;	/* KNOWN to be at offset 0 */
	struct vax_saved_state	vss;	/* user register state */
	int			v_usp;	/* user stack pointer */
};
typedef	struct vax_pcb	*pcb_t;

/*
 *	Routine definitions
 */
extern void		pcb_init();
extern kern_return_t	thread_setstatus();
extern kern_return_t	thread_getstatus();

#define syscall_emulation_sync(task)	/* do nothing */

/*
 *	The current_thread is saved in the VAX supervisor stack pointer,
 *	so signify that there is a machine specific way to get this.
 */
/*
 *	The current_thread is saved in the VAX supervisor stack pointer,
 *	so signify that there is a machine specific way to get this.
 */
#define	CURRENT_THREAD

#ifdef	__GNUC__

#define	current_thread() \
	({ struct thread * _th__; \
	asm("mfpr $2, %0" : "=g" (_th__)); \
	_th__; })

#else	/* __GNUC__ */

struct thread	*current_thread();

#endif	/* __GNUC__ */

#endif	/* _VAX_THREAD_H_ */
