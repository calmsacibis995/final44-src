/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kbdreg.h,v $
 * Revision 2.3  89/03/09  21:42:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:52:05  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)kbdreg.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Keyboard implementation private definitions.
 */

struct keyboardstate {
	u_char	k_id;
	u_char	k_idstate;
	u_char	k_state;
	u_char	k_rptkey;
	u_int	k_buckybits;
	u_int	k_shiftmask;
	struct	keyboard *k_curkeyboard;
	u_int	k_togglemask;	/* Toggle shifts state */
};

/*
 * States of keyboard ID recognizer
 */
#define KID_NONE	0		/* startup */
#define KID_IDLE	1		/* saw IDLE code */
#define KID_LKSUN2	2		/* probably Sun-2 */
#define KID_OK		3		/* locked on ID */
