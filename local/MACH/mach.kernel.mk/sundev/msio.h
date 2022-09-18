/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	msio.h,v $
 * Revision 2.4  89/03/09  21:43:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:52:51  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*      @(#)msio.h 1.1 86/09/25 SMI      */
#ifndef	MSIO_H_
#define MSIO_H_

/*
 * msio.h:	Copyright (c) 1986 by Sun Microsystems, Inc.
 */

typedef struct {
    int             jitter_thresh;
    int             speed_law;
    int             speed_limit;
}               Ms_parms;

#define MSIOGETPARMS	_IOR(m, 2, Ms_parms) /*  get / set jitter, speed  */
#define MSIOSETPARMS	_IOW(m, 3, Ms_parms) /*  law, or speed limit	   */

#endif	MSIO_H_
