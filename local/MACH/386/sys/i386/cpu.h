/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	cpu.h,v $
 * Revision 1.3  89/02/26  12:27:09  gm0w
 * 	Changes for cleanup.
 * 
 *  2-Jan-89  Robert Baron (rvb) at Carnegie-Mellon University
 *	This all seems necessary.
 *
 */

#define cpu_number() (0)
#define set_cpu_number()

int cpu;

int master_cpu;
