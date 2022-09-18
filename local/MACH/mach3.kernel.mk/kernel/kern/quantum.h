/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	quantum.h,v $
 * Revision 2.2  93/11/17  17:19:18  dbg
 * 	Created.
 * 	[93/05/11            dbg]
 * 
 */

#ifndef	_KERN_QUANTUM_H_
#define	_KERN_QUANTUM_H_

#include <kern/kern_types.h>

/*
 *	Routines to perform quantum adjustment.
 */
extern int	min_quantum;		/* maximum context switch rate,
					   in microseconds */

/*
 *	Precalculate the quanta for a processor set.
 */
extern void quantum_set(
	processor_set_t pset);

/*
 *	Recalculate quantum (and thread priority) at
 *	each clock tick.
 */
void clock_quantum_update(
	thread_t	thread,
	int		mycpu,
	unsigned int	usecs);

#endif	/* _KERN_QUANTUM_H_ */
