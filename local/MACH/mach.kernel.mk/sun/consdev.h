/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	consdev.h,v $
 * Revision 2.2  89/02/25  19:27:34  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)consdev.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

dev_t	consdev;	/* user retargettable console */
dev_t	rconsdev;	/* real console - 0 if monitor */
dev_t	mousedev;	/* default mouse device */
dev_t	kbddev;		/* default keyboard device */
int	kbddevopen;	/* keyboard open flag */
dev_t	fbdev;		/* default framebuffer device */

