/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	assert.h,v $
 * Revision 2.10  89/03/09  20:10:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  17:59:55  gm0w
 * 	Changed CMUCS_ASSERT to MACH_ASSERTIONS
 * 	Put entire file under #ifdef KERNEL
 * 	[89/02/15            mrt]
 * 
 * Revision 2.8  89/02/07  01:01:43  mwyoung
 * Relocated from sys/assert.h
 * 
 * Revision 2.7  88/12/19  02:41:59  mwyoung
 * 	It appears to be impossible to avoid lint for expressions
 * 	of the form (constant1 < constant2).  Make assert_static empty
 * 	for lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.6  88/10/18  03:37:27  mwyoung
 * 	Use MACRO_BEGIN, MACRO_END.
 * 	[88/10/11            mwyoung]
 * 	
 * 	Avoid lint warnings about constants in the "while" clause.
 * 	[88/10/06            mwyoung]
 * 
 * Revision 2.5  88/10/01  21:58:26  rpd
 * 	Changed CS_ASSERT to CMUCS_ASSERT
 * 	[88/10/01  21:32:39  rpd]
 * 
 * Revision 2.4  88/09/25  22:15:40  rpd
 * 	Changed to use Debugger instead of panic.
 * 	[88/09/12  23:04:20  rpd]
 * 
 * Revision 2.3  88/08/24  02:22:40  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:08:36  mwyoung]
 * 
 * Revision 2.2  88/07/20  16:44:48  rpd
 * Modify assert for kernel use.
 * 
 */

/*	assert.h	4.2	85/01/21	*/

/*
 * Handy assert macro.
 */

#ifndef	_KERN_ASSERT_H_
#define _KERN_ASSERT_H_

#include <mach_assert.h>

#include <kern/macro_help.h>

#if	MACH_ASSERT
#define assert(ex)							\
MACRO_BEGIN								\
	if (!(ex)) {							\
		printf("Assertion failed: file \"%s\", line %d\n",	\
		       __FILE__, __LINE__);				\
		Debugger("assertion failure");				\
	}								\
MACRO_END

#ifdef	lint
#define assert_static(x)
#else	lint
#define assert_static(x)	assert(x)
#endif	lint

#else	MACH_ASSERT
#define assert(ex)
#define assert_static(ex)
#endif	MACH_ASSERT

#endif	_KERN_ASSERT_H_
