/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	opset.c,v $
 * Revision 2.4  89/03/09  21:34:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:41:38  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalize include of opset.68 on whether mc68000 is
 *	defined rather than sun.
 */
/*	@(#)opset.c 1.1 86/02/03 SMI	*/

#ifdef	vax
#include <opset.vax>
#endif
#ifdef	mc68000
#include <sun3/kdb/opset.68>
#endif
