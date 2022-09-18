/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	setup.c,v $
 * Revision 2.4  89/03/09  21:35:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:42:50  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized include of setup.68 on whether mc68000
 *	defined instead of sun.
 */
/*	@(#)setup.c 1.1 86/02/03 SMI	*/

#ifdef	vax
#include <setup.vax>
#endif
#ifdef	mc68000
#include <sun3/kdb/setup.68>
#endif
