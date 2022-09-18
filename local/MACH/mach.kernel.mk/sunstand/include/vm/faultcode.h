/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	faultcode.h,v $
 * Revision 2.2  89/07/12  00:18:20  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)faultcode.h	1.2 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _vm_faultcode_h
#define _vm_faultcode_h
/*
 * This file describes the "code" that is delivered during
 * SIGBUS and SIGSEGV exceptions.  It also describes the data
 * type returned by vm routines which handle faults.
 *
 * If FC_CODE(fc) == FC_OBJERR, then FC_ERRNO(fc) contains the errno value
 * returned by the underlying object mapped at the fault address.
 */
#define	FC_HWERR	0x1	/* misc hardware error (e.g. bus timeout) */
#define	FC_ALIGN	0x2	/* hardware alignment error */
#define	FC_NOMAP	0x3	/* no mapping at the fault address */
#define	FC_PROT		0x4	/* access exceeded current protections */
#define	FC_OBJERR	0x5	/* underlying object returned errno value */

#define	FC_MAKE_ERR(e)	(((e) << 8) | FC_OBJERR)

#define	FC_CODE(fc)	((fc) & 0xff)
#define	FC_ERRNO(fc)	((unsigned)(fc) >> 8)

#ifndef LOCORE
typedef	int	faultcode_t;	/* type returned by vm fault routines */
#endif LOCORE

#endif !_vm_faultcode_h
