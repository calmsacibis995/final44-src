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
 * $Log:	error.h,v $
 * Revision 2.5  89/03/09  20:19:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:13:18  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  00:51:57  mwyoung
 * Relocated from sys/error.h
 * 
 * Revision 2.2  88/10/18  00:37:31  mwyoung
 * 	Added {system,sub and code}_emask 
 * 	[88/10/17  17:06:58  mrt]
 * 
 *	Added {system,sub and code}_emask 
 *
 *  12-May-88 Mary Thompson (mrt) at Carnegie Mellon
 *	Changed mach_error_t from unsigned int to kern_return_t
 *	which is a 32 bit integer regardless of machine type.
 *      insigned int was incompatible with old usages of mach_error.
 *
 *  10-May-88 Douglas Orr (dorr) at Carnegie-Mellon University
 *	Missing endif replaced
 *
 *   5-May-88 Mary Thompson (mrt) at Carnegie Mellon
 *	Changed typedef of mach_error_t from long to unsigned int
 *	to keep our Camelot users happy. Also moved the nonkernel
 *	function declarations from here to mach_error.h.
 *
 *  10-Feb-88 Douglas Orr (dorr) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * File:	mach/error.h
 * Purpose:
 *	error module definitions
 *
 */

#ifndef	_MACH_ERROR_H_
#define _MACH_ERROR_H_

#include <mach/kern_return.h>

/*
 *	error number layout as follows:
 *
 *	hi		 		       lo
 *	| system(6) | subsystem(12) | code(14) |
 */


#define err_none		(mach_error_t)0
#define ERR_SUCCESS		(mach_error_t)0
#define ERR_ROUTINE_NIL		(mach_error_fn_t)0


#define err_system(x)		(((x)&0x3f)<<26)
#define err_sub(x)		(((x)&0xfff)<<14)

#define err_get_system(err)	(((err)>>26)&0x3f)
#define err_get_sub(err)	(((err)>>14)&0xfff)
#define err_get_code(err)	((err)&0x3fff)

#define system_emask		(err_system(0x3f))
#define sub_emask		(err_sub(0xfff))
#define code_emask		(0x3fff)


/*	major error systems	*/
#define err_kern		err_system(0x0)		/* kernel */
#define err_us			err_system(0x1)		/* user space library */
#define err_server		err_system(0x2)		/* user space servers */
#define err_ipc			err_system(0x3)		/* mach-ipc errors */
#define err_local		err_system(0x3e)	/* user defined errors */
#define err_ipc_compat		err_system(0x3f)	/* (compatibility) mach-ipc errors */

#define err_max_system		0x3f


/*	unix errors get lumped into one subsystem  */
#define unix_err(errno)		(err_kern|err_sub(3)|errno)

typedef	kern_return_t	mach_error_t;
typedef mach_error_t	(* mach_error_fn_t)();

#endif	_MACH_ERROR_H_
