/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	diag.h,v $
 * Revision 2.3  89/03/09  21:32:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:33:46  gm0w
 * 	Changes for cleanup.
 * 
 */
/*      @(#)diag.h 1.1 86/02/03 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * The diagnostic register drvies an 8-bit LED display.
 * This register is addressed in FC_MAP space and is write only.
 * A "0" bit written will cause the corresponding LED to light up,
 * a "1" bit to be dark.
 */

#define DIAGREG		0x70000000	/* addr of diag reg in FC_MAP space */
