/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	blituser.h,v $
 * Revision 1.5.1.3  90/11/27  13:41:08  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.5.1.3) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/05/03  15:41:10  dbg
 * 	First checkin.
 * 
 * Revision 1.5.1.2  90/02/28  15:49:05  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.5.1.1  90/01/08  13:32:14  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.5  89/09/20  17:27:19  rvb
 * 	Revision 1.2  89/07/26  22:39:04  kupfer
 * 	tweaks, better support for user code that wants to use the 786.
 * 
 * 	Revision 1.1.2.1  89/07/21  22:48:07  kupfer
 * 	Get rid of old System V ioctl's and add ioctl for management of
 * 	on-card memory.
 * 
 * 	Revision 1.1  89/07/13  19:51:36  kupfer
 * 	Initial revision
 * 
 * Revision 1.4  89/03/09  20:05:02  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:41:31  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/* **********************************************************************
 File:         blituser.h
 Description:  User-program definitions for Bell Tech Blit card

 Copyright Ing. C. Olivetti & C. S.p.A. 1988, 1989.
 All rights reserved.
********************************************************************** */
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef	_BLITUSER_
#define _BLITUSER_

#include <sys/ioctl.h>

/*
 * Ioctl's.
 */

/* 
 * BLIT_1ST_UNUSED returns a byte offset into the Blit graphics 
 * memory.  The user is free to allocate and use any graphics memory 
 * starting at that offset.
 */

#define BLIT_1ST_UNUSED	_IOR(b, 1, int)

#endif	/* _BLITUSER_ */
