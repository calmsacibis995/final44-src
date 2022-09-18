/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	report.h,v $
 * Revision 2.2  89/02/25  19:12:57  gm0w
 * 	Changes for cleanup.
 * 
 */

/*	@(#) pixrect.h 1.21 84/05/31  sml */
/*
/*
/*	Copyright (c) 1983 by Sun Microsystems, Inc.
/*
/*
*/
/* this is a global structure declaration.
*/
	struct test_report{
		char oper[80];
		int iter;
		int total_time;
		int oper_time;
		}; report;
