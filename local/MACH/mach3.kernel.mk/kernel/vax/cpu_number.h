/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
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
 * $Log:	cpu_number.h,v $
 * Revision 2.3  91/05/14  17:42:25  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:15:45  dbg
 * 	Added inline assembler definition for GCC.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.1  89/08/03  16:28:22  rwd
 * Created.
 * 
 *  8-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

#ifndef	_VAX_CPU_NUMBER_H_
#define	_VAX_CPU_NUMBER_H_

/*
 *	Machine-dependent definitions for cpu identification.
 *
 *	On the VAX, cpu_number() is defined by inline.
 */
#ifdef	__GNUC__

#define	cpu_number() \
	({  register int _mycpu__ asm("r0"); \
	    asm("jsb *_Cpu_number_ptr" \
		: "=r" (_mycpu__) \
		); \
	    _mycpu__; })

#endif	/* __GNUC__ */

#endif	/* _VAX_CPU_NUMBER_H_ */
