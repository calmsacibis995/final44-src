/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	thread_bootstrap.s,v $
 * Revision 2.3  89/03/09  22:21:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:29:11  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Check for request to halt thread (before it even has a chance to
 *	start).
 *
 * 28-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/thread_bootstrap.s
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Assembly language support for bootstrapping user threads.
 */
#include <vax/asm.h>
#include <vax/mtpr.h>

#define LOCORE
#include <assym.s>

/*
 *	thread_bootstrap:
 *
 *	Bootstrap a new thread using the vax thread state that has been
 *	placed on the stack.  Our fp has been set up for us, we only need
 *	to fix up a few things in the saved frame, then get into
 *	usermode via an rei.
 */

JSBENTRY(thread_bootstrap, 0)
	clrl	(fp)			# no condition handler
	movl	$0x2fff0000,4(fp)	# simulate calls, saving all regs.
	movab	1f,0x10(fp)		# pc to return to.
	mfpr	$SSP,r0			# should we stop before we even
	cmpl	THREAD_EXIT_CODE(r0),$THREAD_EXIT	# start?
	beql	0f
	mtpr	$3,$ASTLVL		# request AST to stop if so
0:
	ret
1:
	mtpr	(sp)+,$USP		# restore user stack pointer
	addl2	$8,sp			# remove garbage from normal trap
	rei				# into user mode!
