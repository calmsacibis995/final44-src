/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	consdev.h,v $
 * Revision 2.2  89/07/11  23:28:15  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)consdev.h 5.6 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

dev_t	consdev;	/* user retargettable console */
struct vnode *consvp;	/* pointer to vnode for that device */
dev_t	rconsdev;	/* real console - 0 if not retargetted */
struct vnode *rconsvp;	/* pointer to vnode for that device */
dev_t	mousedev;	/* default mouse device */
dev_t	kbddev;		/* default keyboard device */
int	kbddevopen;	/* keyboard open flag */
dev_t	fbdev;		/* default framebuffer device */

