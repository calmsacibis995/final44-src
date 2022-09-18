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
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
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
 * any improvements or extensions that they make and grant Carnegie the rights
 * to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	varargs.h,v $
 * Revision 2.1.1.1  91/03/15  15:58:06  rvb
 * 	This is the 3.0 sys/varargs.h.
 * 
 * 
 * Revision 2.1  91/03/15  15:55:30  rvb
 * to 2.1
 * 
 * Revision 2.5  91/02/05  17:57:12  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:49:51  mrt]
 * 
 * Revision 2.4  90/11/25  17:48:50  jsb
 * 	Added i860 support.
 * 	[90/11/25  16:54:09  jsb]
 * 
 * Revision 2.3  90/05/03  15:51:29  dbg
 * 	Added i386.
 * 	[90/02/08            dbg]
 * 
 * Revision 2.2  89/11/29  14:16:44  af
 * 	RCS-ed, added mips case.  Mips also needs it in Mach standalone
 * 	programs.
 * 	[89/10/28  10:39:14  af]
 * 
 */

#ifndef _SYS_VARARGS_H_
#define _SYS_VARARGS_H_

#ifdef	luna88k
#include	<machine/varargs.h>
#endif	luna88k

#if	defined(vax) || defined(sun3) || defined(mips) || defined(i386)
#define	va_dcl	int	va_alist;
typedef	char *	va_list;

#define	va_start(pvar)	(pvar) = (va_list)&va_alist
#define	va_end(pvar)
#ifdef	mips
# define va_arg(pvar, type) ((type *)(pvar = \
		(va_list) (sizeof(type) > 4 ? ((int)pvar + 2*8 - 1) & -8 \
				   : ((int)pvar + 2*4 - 1) & -4)))[-1]
#else	mips
#define	va_arg(pvar,type)	(		\
		(pvar) += ((sizeof(type)+3) & ~0x3),	\
		*((type *)((pvar) - ((sizeof(type)+3) & ~0x3))) )
#endif	mips
#endif	/* vax */

/*
 * Try to make varargs work for the Multimax so that _doprnt can be
 * declared as
 *	_doprnt(file, fmt, list)
 *	FILE	*file;
 *	char	*fmt;
 *	va_list *list;
 * and use
 *
 *	n = va_arg(*list, type)
 *
 * without needing to drag in extra declarations
 *
 * and printf becomes
 *
 * printf(fmt, va_alist)
 *	char	*fmt;
 *	va_dcl
 * {
 *	va_list listp;
 *	va_start(listp);
 *	_doprnt((FILE *)0, fmt, &listp);
 *	va_end(listp);
 * }
 */

#if	defined(multimax) && defined(KERNEL)

/*
 * the vararglist pointer is an elaborate structure (ecch)
 */
typedef struct va_list {
	char	*va_item;	/* current item */
	int	*va_ptr1,	/* arglist pointers for 1, 2, n */
		*va_ptr2,
		*va_ptrn;
	int	va_ct;		/* current argument number */
} va_list;

#define	va_alist	va_arg1, va_arg2, va_argn
#define	va_dcl		int	va_arg1, va_arg2, va_argn;

#define	va_start(pvar)	(		\
	(pvar).va_ptr1 = &va_arg1,	\
	(pvar).va_ptr2 = &va_arg2,	\
	(pvar).va_ptrn = &va_argn,	\
	(pvar).va_ct = 0 )

#define	va_end(pvar)

#define	va_arg(pvar, type)	(	\
	(pvar).va_ct++,			\
	(pvar).va_item = (char *)	\
	  ( ((pvar).va_ct == 1)		\
	    ? (pvar).va_ptr1		\
	    : ((pvar).va_ct == 2)	\
	      ? (pvar).va_ptr2		\
	      : (pvar).va_ptrn++ ) ,	\
	*((type *)((pvar).va_item)) )

/* what a mess! */
#endif	/* defined(multimax) && defined(KERNEL) */

#if i860
#include <i860/i860_varargs.h>		/* Intel proprietary information */
#endif

#endif _SYS_VARARGS_H_
