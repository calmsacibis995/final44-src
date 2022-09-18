/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	machtypes.h,v $
 * Revision 2.2  89/02/25  19:44:57  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 13-Jun-85  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Copied VAX version for Sun 3.
 *
 * 11-Mar-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	sun3/machtypes.h
 *
 *	Basic system types for Sun.
 */

#ifndef	MACHTYPES_H_
#define MACHTYPES_H_

typedef int		boolean_t;

/*
 *	Dare I define these here?
 */

#if	defined(KERNEL) && !defined(NOBOOL) && !defined(TRUE)
#define TRUE	((boolean_t) 1)
#define FALSE	((boolean_t) 0)
typedef enum	{ false = 0, true = 1 } bool;
#endif	defined(KERNEL) && !defined(NOBOOL) && !defined(TRUE)

#ifdef	KERNEL
#define NULL	0
#endif	KERNEL

#endif	MACHTYPES_H_
