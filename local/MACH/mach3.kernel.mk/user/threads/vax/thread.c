/* 
 * Mach Operating System
 * Copyright (c) 1992,1991,1990,1989 Carnegie Mellon University
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
 * $Log:	thread.c,v $
 * Revision 2.11  93/05/14  15:10:45  rvb
 * 	#include string.h->strings.h; kill stdlib.h
 * 	[93/05/14            rvb]
 * 
 * Revision 2.10  93/02/02  21:55:26  mrt
 * 	Changed include of mach/mach.h to mach.h
 * 	[93/02/02            mrt]
 * 
 * Revision 2.9  93/01/14  18:06:36  danner
 * 	Converted file to ANSI C.
 * 	Fixed argument types.
 * 	[92/12/18            pds]
 * 
 * Revision 2.8  91/10/09  16:21:43  af
 * 	 Revision 2.7.1.1  91/09/16  10:26:26  rpd
 * 	 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.7.1.1  91/09/16  10:26:26  rpd
 * 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.7  91/08/01  09:12:11  dbg
 * 	Let this file still compile with PCC.
 * 	[91/08/01            dbg]
 * 
 * Revision 2.6  91/07/31  18:40:30  dbg
 * 	Undefine cthread_sp macro around function.
 * 	[91/07/25            dbg]
 * 
 * Revision 2.5  91/05/14  18:00:56  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/02/14  14:22:04  mrt
 * 	Added new Mach copyright
 * 	[91/02/13  12:40:16  mrt]
 * 
 * Revision 2.3  90/06/02  15:14:30  rpd
 * 	Added definition of cthread_sp.
 * 	[90/04/24            rpd]
 * 
 * Revision 2.2  89/12/08  19:55:37  rwd
 * 	cproc_setup now takes the routine to start running.
 * 	[89/11/25            rwd]
 * 	Fix MACH_CALL reference
 * 	[89/11/15            rwd]
 * 	Changed calling format and removed conditionals
 * 	[89/10/23            rwd]
 * 
 */
/*
 * vax/thread.c
 *
 * Cproc startup for VAX MTHREAD implementation.
 */


#include <cthreads.h>
#include "cthread_internals.h"
#include <mach.h>
#include <strings.h>

/*
 * Set up the initial state of a MACH thread so that it will invoke
 * cthread_body(child) when it is resumed.
 */
void
cproc_setup(register cproc_t child, thread_t thread, void (*routine)(cproc_t))
{
	register int *top = (int *) (child->stack_base + child->stack_size);
	struct vax_thread_state state;
	register struct vax_thread_state *ts = &state;
	kern_return_t r;

	/*
	 * Set up VAX call frame and registers.
	 * See VAX Architecture Handbook.
	 */
	memset(ts, 0, sizeof(struct vax_thread_state));
	/*
	 * Set pc to location after register save mask at procedure entry.
	 * Inner cast needed since too many C compilers choke on the type
	 * void (*)().
	 */
	ts->pc = ((int) routine) + 2;
	*--top = (int) child;	/* argument to function */
	*--top = 1;		/* number of arguments */
	ts->ap = (int) top;
	*--top = 0; *--top = 0; *--top = 0;
	*--top = (1 << 29);
	*--top = 0;
	ts->fp = ts->sp = (int) top;

	MACH_CALL(thread_set_state(thread, VAX_THREAD_STATE, (thread_state_t) &state, VAX_THREAD_STATE_COUNT),r);
}

#if	defined(cthread_sp)
#undef	cthread_sp
#endif

int
cthread_sp(void)
{
	int x;

	return (int) &x;
}

