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
 * $Log:	stdarg.h,v $
 * Revision 2.2  93/11/17  19:11:46  dbg
 * 	Created.
 * 	[93/10/27            dbg]
 * 
 */

#ifndef	_I386_STDARG_H_
#define	_I386_STDARG_H_

/*
 *	STDARG for i386
 *
 *	All arguments are on the stack.
 *	Sizes are rounded to the nearest integer (4 bytes).
 */

typedef	char *	va_list;

#define	va_start(ap, last)	((ap) = (char *)(&(last)+1))
#define	va_end(ap)

#define	va_arg(ap, type) \
	( (ap) += ((sizeof(type)+3) & ~0x3),	/* advance */	\
	  *((type *)((ap) - ((sizeof(type)+3) & ~0x3))) )

#endif	/* _I386_STDARG_H_ */
