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
 * $Log:	exception.h,v $
 * Revision 2.4  93/01/14  17:48:28  danner
 * 	Added standard inclusion protection symbol.
 * 	[92/06/10            pds]
 * 
 * Revision 2.3  91/05/14  17:01:53  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/02/05  17:37:00  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:14:49  mrt]
 * 
 * Revision 2.1  89/08/03  16:01:02  rwd
 * Created.
 * 
 * Revision 2.3  89/02/25  18:41:46  gm0w
 * 	Changes for cleanup.
 * 
 *  2-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

#ifndef	_MACH_VAX_EXCEPTION_H_
#define	_MACH_VAX_EXCEPTION_H_

/*
 *	Codes and subcodes for vax exceptions.
 */

/*
 *	EXC_BAD_INSTRUCTION
 */

#define	EXC_VAX_PRIVINST		1
#define	EXC_VAX_RESOPND			2
#define	EXC_VAX_RESADDR			3
#define	EXC_VAX_COMPAT			4

/*
 *	COMPAT subcodes
 */
#define	EXC_VAX_COMPAT_RESINST		0
#define	EXC_VAX_COMPAT_BPT		1
#define	EXC_VAX_COMPAT_IOT		2
#define	EXC_VAX_COMPAT_EMT		3
#define	EXC_VAX_COMPAT_TRAP		4
#define	EXC_VAX_COMPAT_RESOP		5
#define	EXC_VAX_COMPAT_ODDADDR		6

/*
 *	EXC_ARITHMETIC
 */

#define	EXC_VAX_INT_OVF			1
#define	EXC_VAX_INT_DIV			2
#define	EXC_VAX_FLT_OVF_T		3
#define	EXC_VAX_FLT_DIV_T		4
#define	EXC_VAX_FLT_UND_T		5
#define	EXC_VAX_DEC_OVF			6

#define	EXC_VAX_FLT_OVF_F		8
#define	EXC_VAX_FLT_DIV_F		9
#define	EXC_VAX_FLT_UND_F		10

/*
 *	EXC_SOFTWARE
 */

#define EXC_VAX_SUB_RNG			7

/*
 *	EXC_BREAKPOINT
 */

#define	EXC_VAX_BPT			1
#define EXC_VAX_TRACE			2

#endif	/* _MACH_VAX_EXCEPTION_H_ */
