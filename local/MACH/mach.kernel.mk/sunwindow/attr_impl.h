/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	attr_impl.h,v $
 * Revision 2.4  89/03/09  21:56:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:03:57  gm0w
 * 	Changes for cleanup.
 * 
 */
/*      @(#)attr_impl.h 1.2 86/09/02 SMI      */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef	attr_impl_DEFINED
#define attr_impl_DEFINED

#include <sys/types.h>
#include <varargs.h>
#include <sunwindow/attr.h>

/* NON_PORTABLE means that the var-args list is treated
 * as an avlist.  This is known to work for Sun1/2/3/rise.
 * If the implementation of varargs.h does not have va_arg()
 * equivalent to an array access (e.g. *avlist++), then
 * NON_PORTABLE should NOT be defined.
 */
#define NON_PORTABLE

/* size of an attribute */
#define ATTR_SIZE	(sizeof(caddr_t))

/* package private routines */
extern Attr_avlist	attr_copy_avlist();
extern void		attr_check_pkg();
extern int		attr_count_avlist();
extern Attr_avlist	attr_copy_valist();

#endif	not attr_impl_DEFINED
