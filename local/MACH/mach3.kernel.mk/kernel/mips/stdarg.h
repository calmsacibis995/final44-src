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
 * Revision 2.2  93/11/17  19:10:47  dbg
 * 	Created.
 * 	[93/10/28            dbg]
 * 
 */

#ifndef	_MIPS_STDARG_H_
#define	_MIPS_STDARG_H_

/*
 *	STDARG for mips
 *
 *	All arguments are on the stack (the compiler will
 *	copy the first 4 to the stack).  Sizes are rounded
 *	to the nearest integer (4 bytes), except for items
 *	larger than 4 bytes, which are rounded to the
 *	nearest 8 bytes.
 */

#ifdef	__GNUC__

/*
 * Amount of space required in an argument list for an arg of type TYPE.
 * TYPE may alternatively be an expression whose type is used.  */

#define	__va_size_in_ints(__TYPE)					\
    ((sizeof(__TYPE) + sizeof(int) - 1) / sizeof(int))

#define __va_rounded_size(__TYPE) (__va_size_in_ints(__TYPE) * sizeof(int))

typedef	char *	va_list;

#define	va_start(__AP, __LASTARG) \
	((__AP) = (va_list) &(__LASTARG) + __va_rounded_size(__LASTARG))
#define	va_end(__AP)

#define va_arg(__AP, __TYPE)						\
    (((__TYPE *) (void *) (__AP = (va_list) ((__alignof(__TYPE) > 4	\
					     ? ((int)__AP + 8 - 1) & -8	\
					     : ((int)__AP + 4 - 1) & -4)\
					    + __va_rounded_size(__TYPE))))[-1])

#else	/* not GNUC */
	This only works with GCC
#endif	/* __GNUC__ */

#endif	/* _MIPS_STDARG_H_ */
