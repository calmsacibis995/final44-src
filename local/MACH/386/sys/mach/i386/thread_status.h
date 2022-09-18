/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	thread_status.h,v $
 * Revision 1.3.1.4  90/12/07  22:54:22  rvb
 * 	Add ISA_PORT_MAP_BITMAP state
 * 	[90/12/07            rvb]
 * 
 * Revision 1.3.1.3  90/06/07  08:05:50  rvb
 * 	Update reg.h to track thread_status.h and put in some comments
 * 	to tie the two together. 		[kupfer]
 * 
 * Revision 1.3.1.2  90/03/28  08:31:11  rvb
 * 	v86 changes: 4 more word for stack	[grm]
 * 
 * Revision 1.3.1.1  90/02/28  15:51:01  rvb
 * 	Revision 1.8  89/11/02  14:16:47  kupfer
 * 	Debugger support: add flavor for FP coprocessor state.  And, for the
 * 	nth time, the USER_REGS macro is correct.  The system would have
 * 	failed long ago if it weren't.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.3  89/03/09  20:19:59  rpd
 * 	More cleanup.
 * 
 * Revision 1.2  89/02/26  13:01:07  gm0w
 * 	Changes for cleanup.
 * 
 * 24-Feb-89  Robert Baron (rvb) at Carnegie-Mellon University
 *	May need some work.
 */

/*
 *	File:	thread_status.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for the thread
 *	state as applied to I386 processors.
 */

#ifndef	_MACH_I386_THREAD_STATUS_H_
#define _MACH_I386_THREAD_STATUS_H_

#include <sys/types.h>
#include <i386/fpreg.h>

/*
 *	Three structures are defined:
 *
 *	i386_thread_state	this is the structure that is exported
 *				to user threads for use in status/mutate
 *				calls.  This structure should never
 *				change.
 *
 *	i386_float_state	exported to use threads for access to 
 *				floating point registers. Try not to 
 *				change this one, either.
 *
 *	i386_isa_port_map_state	exported to user threads to allow
 *				selective in/out operations
 *
 *	i386_saved_state	this structure corresponds to the state
 *				of the user registers as saved on the
 *				stack upon kernel entry.  This structure
 *				is used internally only.  Since this
 *				structure may change from version to
 *				version, it is hidden from the user.
 */

#define i386_THREAD_STATE	1
#define i386_FLOAT_STATE	2
#define i386_ISA_PORT_MAP_STATE	3

struct i386_thread_state {
	unsigned int	gs;
	unsigned int	fs;
	unsigned int	es;
	unsigned int	ds;
	unsigned int	edi;
	unsigned int	esi;
	unsigned int	ebp;
	unsigned int	esp;
	unsigned int	ebx;
	unsigned int	edx;
	unsigned int	ecx;
	unsigned int	eax;
	unsigned int	eip;
	unsigned int	cs;
	unsigned int	efl;
	unsigned int	uesp;
	unsigned int	ss;
};

/* 
 * Floating point state.
 *
 * fpkind tells in what way floating point operations are supported.  
 * See the values for fp_kind in <i386/fpreg.h>.
 * 
 * If the kind is FP_NO, then calls to set the state will fail, and 
 * thread_getstatus will return garbage for the rest of the state.
 * If "initialized" is false, then the rest of the state is garbage.  
 * Clients can set "initialized" to false to force the coprocessor to 
 * be reset.
 * "exc_status" is non-zero if the thread has noticed (but not 
 * proceeded from) a coprocessor exception.  It contains the status 
 * word with the exception bits set.  The status word in "hw_state" 
 * will have the exception bits turned off.  If an exception bit in 
 * "hw_state" is turned on, then "exc_status" should be zero.  This 
 * happens when the coprocessor exception is noticed after the system 
 * has context switched to some other thread.
 * 
 * If kind is FP_387, then "state" is a i387_state.  Other kinds might
 * also use i387_state, but somebody will have to verify it (XXX).
 * Note that the registers are ordered from top-of-stack down, not
 * according to physical register number.
 */

struct i386_float_state {
	int	fpkind;			/* FP_NO..FP_387 (readonly) */
	boolean_t	initialized;
	u_char	hw_state[FP_STATE_BYTES]; /* actual "hardware" state */
	u_short	exc_status;		/* exception status (readonly) */
};

#define PORT_MAP_BITS 0x400
struct i386_isa_port_map_state {
	u_char	pm[PORT_MAP_BITS>>3];
};

#define i386_THREAD_STATE_COUNT	(sizeof(struct i386_thread_state)/sizeof(unsigned int))
#define i386_FLOAT_STATE_COUNT (sizeof(struct i386_float_state)/sizeof(unsigned int))
#define i386_ISA_PORT_MAP_STATE_COUNT (sizeof(struct i386_isa_port_map_state)/sizeof(unsigned int))


#ifdef	KERNEL

/* 
 * If you change the definition of i386_saved_state, please also 
 * fix the symbolic constants in i386/reg.h.
 */
struct i386_saved_state {
	unsigned int	gs;
	unsigned int	fs;
	unsigned int	es;
	unsigned int	ds;
	unsigned int	edi;
	unsigned int	esi;
	unsigned int	ebp;
	unsigned int	esp;
	unsigned int	ebx;
	unsigned int	edx;
	unsigned int	ecx;
	unsigned int	eax;
	unsigned int	trapno;
	unsigned int	err;
	unsigned int	eip;
	unsigned int	cs;
	unsigned int	efl;
	unsigned int	uesp;
	unsigned int	ss;
	struct i386_v86_info {
		/* v86 mode registers (optional) */
		unsigned int	oldes;
		unsigned int	oldds;
		unsigned int	oldfs;
		unsigned int	oldgs;
	} v86;
};

#define USER_REGS(thread)	(((struct i386_saved_state *)	\
					((thread)->kernel_stack	\
					 + KERNEL_STACK_SIZE)	\
					) - 1)
#endif	KERNEL
#endif	_MACH_I386_THREAD_STATUS_H_
