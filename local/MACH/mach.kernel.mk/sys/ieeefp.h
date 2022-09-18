/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ieeefp.h,v $
 * Revision 2.3  90/02/19  15:14:19  jjc
 * 	Upgraded to SunOS 4.0 version.
 * 	[90/01/29            jjc]
 * 
 * Revision 2.2  89/07/12  01:27:51  jjc
 * 	Picked up for Sun 4.
 * 	[89/06/30            jjc]
 * 
 */
/*	@(#)ieeefp.h 1.5 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
		 #include <sys/ieeefp.h> 

contains definitions for constants and types for IEEE floating point.

Source at       /usr/src/sys/sys/ieeefp.h
Install at      /usr/include/sys/ieeefp.h
*/

/*	Sun TYPES for IEEE floating point.	*/

#ifdef sparc
enum fp_direction_type 		/* rounding direction */
	{
	fp_nearest	= 0,
	fp_tozero	= 1,
	fp_positive	= 2,
	fp_negative	= 3
	} ;
#endif
#ifdef i386
enum fp_direction_type 		/* rounding direction */
	{
	fp_nearest	= 0,
	fp_negative	= 1,
	fp_positive	= 2,
	fp_tozero	= 3
	} ;
#endif
#ifdef mc68000
enum fp_direction_type 		/* rounding direction */
	{
	fp_nearest	= 0,
	fp_tozero	= 1,
	fp_negative	= 2,
	fp_positive	= 3
	} ;
#endif

#ifdef i386
enum fp_precision_type		/* extended rounding precision */
	{
	fp_single	= 0,
	fp_precision_3	= 1,
	fp_double	= 2,
	fp_extended	= 3
	} ;
#else
enum fp_precision_type		/* extended rounding precision */
	{
	fp_extended	= 0,
	fp_single	= 1,
	fp_double	= 2,
	fp_precision_3	= 3
	} ;
#endif

#ifdef i386
enum fp_exception_type		/* exceptions according to bit number */
	{
	fp_invalid	= 0,
	fp_denormalized	= 1,
	fp_division	= 2,
	fp_overflow	= 3,
	fp_underflow	= 4,
	fp_inexact	= 5
	} ;
#else
enum fp_exception_type		/* exceptions according to bit number */
	{
	fp_inexact	= 0,
	fp_division	= 1,
	fp_underflow	= 2,
	fp_overflow	= 3,
	fp_invalid	= 4
	} ;
#endif

enum fp_class_type		/* floating-point classes */
	{
	fp_zero		= 0,
	fp_subnormal	= 1,
	fp_normal	= 2,
	fp_infinity   	= 3,
	fp_quiet	= 4,
	fp_signaling	= 5
	} ;
