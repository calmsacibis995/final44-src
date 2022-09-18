/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ipconfig.h,v $
 * Revision 2.2  89/02/26  11:04:11  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
** $ Header: /a/display/h/RCS/ipconfig.h,v 2.1 84/01/18 10:31:59 bob Exp $
**
** Hardware configuration of our 8500.
*/
#define MONITOR_SZ	(1024)
#define BOARD_RES	(1024)	/* this 8500 has hi res boards */
#define NBOARDS		(18)	/* # of memory boards in this 8500 */
#define XMAXRES		(2048)	/* 8500 has 2048 max res/chan in x */
#define YMAXRES		(2048)	/* 8500 has 2048 max res/chan in y */
#define NVOC		(2)	/* 8500 has 2 vidoe output controllers */
