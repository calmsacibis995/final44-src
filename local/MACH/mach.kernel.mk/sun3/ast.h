/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ast.h,v $
 * Revision 2.3  89/10/15  02:06:44  rpd
 * 	Minor cleanups.
 * 
 * Revision 2.2  89/10/11  14:49:39  dlb
 * 	Created based on vax/ast.h and sun3/pcb.h
 * 	[89/02/10            dlb]
 * 
 */

/*
 *	sun3/ast.h: Definitions for sun3 hardware ast mechanism.
 */

#ifndef	_SUN3_AST_H_
#define	_SUN3_AST_H_

#include <kern/macro_help.h>
#include <kern/thread.h>

#include <sun3/pcb.h>

/*
 *	ast_context sets up ast context for this thread on
 *	the specified cpu (always the current cpu).  On sun3 this
 *	goes into the pcb.  If we don't need an ast, clear out any
 *	previous pending one.
 */

#define	ast_context(thread, cpu) 					\
			MACRO_BEGIN					\
			if ((thread)->ast) {				\
				(thread)->pcb->pcb_flag |= AST_SCHED;	\
			} else {					\
				(thread)->pcb->pcb_flag &= ~AST_SCHED;	\
			}						\
			MACRO_END
/*
 *	ast_propagate: cause an ast if needed.
 */

#define ast_propagate(thread, cpu)					\
			MACRO_BEGIN					\
			if ((thread)->ast) {				\
				(thread)->pcb->pcb_flag |= AST_SCHED;	\
			}						\
			MACRO_END
/*
 *	ast_needed: Is an ast already pending?
 */

#define ast_needed(cpu)							\
	((current_thread()->pcb->pcb_flag & AST_SCHED) == AST_SCHED)

#endif	_SUN3_AST_H_
