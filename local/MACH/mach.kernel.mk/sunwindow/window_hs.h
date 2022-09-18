/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	window_hs.h,v $
 * Revision 2.4  89/03/09  21:59:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:07:18  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
#ifndef	WINDOW_HS_H_
#define WINDOW_HS_H_	1
/*      @(#)window_hs.h 1.2 86/10/08 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Include this header file to get all sunwindow related header files.
 */

#include <sys/time.h>
#include <pixrect/pixrect_hs.h>
#include <sunwindow/notify.h>
#include <sunwindow/rect.h>
#include <sunwindow/rectlist.h>
#include <sunwindow/pixwin.h>
#include <sunwindow/pw_util.h>
#include <sunwindow/win_struct.h>
#include <sunwindow/win_environ.h>
#include <sunwindow/cms.h>
#include <sunwindow/win_screen.h>
#include <sunwindow/win_input.h>
#include <sunwindow/win_cursor.h>
#include <sunwindow/win_notify.h>

#endif	WINDOW_HS_H_
