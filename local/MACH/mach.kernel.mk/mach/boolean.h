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
 * $Log:	boolean.h,v $
 * Revision 2.6  89/04/05  13:03:18  rvb
 * 	DON'T type cast TRUE and FALSE this causes major problems with
 * 	GCC, since boolean_t is an int and can not fit into a 1 bit
 * 	unsigned field.  BUT 0 and 1 can.
 * 	[89/03/21            rvb]
 * 
 * Revision 2.5  89/03/09  20:18:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:12:08  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  00:51:34  mwyoung
 * Relocated from sys/boolean.h
 * 
 * Revision 2.2  88/08/24  02:23:06  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:09:46  mwyoung]
 *
 * 18-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Header file fixup, purge history.
 *
 */
/*
 *	File:	mach/boolean.h
 *
 *	Boolean data type.
 *
 */

#ifndef	_MACH_BOOLEAN_H_
#define _MACH_BOOLEAN_H_

/*
 *	Pick up "boolean_t" type definition
 */

#ifndef	ASSEMBLER
#include <mach/machine/boolean.h>
#endif	ASSEMBLER
#endif	_MACH_BOOLEAN_H_

/*
 *	Define TRUE and FALSE, only if they haven't been before,
 *	and not if they're explicitly refused.  Note that we're
 *	outside the BOOLEAN_H_ conditional, to avoid ordering
 *	problems.
 */

#if	(defined(KERNEL) || defined(EXPORT_BOOLEAN)) && !defined(NOBOOL)

#ifndef	TRUE
#define TRUE	1
#endif	TRUE

#ifndef	FALSE
#define FALSE	0
#endif	FALSE

#endif	(defined(KERNEL) || defined(EXPORT_BOOLEAN)) && !defined(NOBOOL)
