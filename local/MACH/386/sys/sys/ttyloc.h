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
 * $Log:	ttyloc.h,v $
 * Revision 2.3  89/03/09  22:09:20  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  17:57:39  gm0w
 * 	Changes for cleanup.
 * 
 * 15-Aug-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed TLC_MYHOST to expand to the host ID.
 *
 * 15-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Made conditional on _TTYLOC_ symbol to permit recursive
 *	includes.
 *	[V1(1)]
 *
 * 09-Sep-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added TLC_TACTTY and TLC_RANDOMTTY definitions.
 *
 * 28-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created (V3.06h).
 *
 */

#ifndef	_SYS_TTYLOC_H_
#define _SYS_TTYLOC_H_

struct ttyloc
{
    long tlc_hostid;		/* host identifier of location (on Internet) */
    long tlc_ttyid;		/* terminal identifier of location (on host) */
};

/*
 *  Pseudo host location of Front Ends
 */
#define TLC_FEHOST	((128<<24)|(2<<16)|(254<<8)|255)
#define TLC_SPECHOST	((0<<24)|(0<<16)|(0<<8)|0)

/*
 *  Pseudo terminal index of console
 */
#define TLC_CONSOLE	((unsigned short)0177777)
#define TLC_DISPLAY	((unsigned short)0177776)

/*
 *  Constants
 */
#define TLC_UNKHOST	((long)(0))
#define TLC_UNKTTY	((long)(-1))
#define TLC_DETACH	((long)(-2))
#define TLC_TACTTY	((long)(-3))		/* unused by kernel */
#define TLC_RANDOMTTY	((long)(-4))		/* unused by kernel */

#ifdef	KERNEL
#include <sys/kernel.h>		/* for hostid */

/*
 *  IP address of local host (as determined by the network module)
 */
#define TLC_MYHOST	(hostid)

#endif	KERNEL
#endif	_SYS_TTYLOC_H_
