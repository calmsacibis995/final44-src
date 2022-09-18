/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fork.s,v $
 * Revision 2.3  92/01/23  15:22:46  rpd
 * 	Removed dependency on syscall.h by adding
 * 	an explicit definition of SYS_fork.
 * 	[92/01/16            rpd]
 * 
 * Revision 2.2  92/01/16  00:02:35  rpd
 * 	Moved from user collection to mk collection.
 * 
 * Revision 2.2  91/04/11  11:45:33  mrt
 * 	Copied from libc.a
 * 
 * 
 */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
_sccsid:.asciz	"@(#)fork.c	5.2.M (Mach) 19-aug-86"
#endif not lint

#include "SYS.h"

#define SYS_fork	2

	.globl	_mach_init

SYSCALL(fork)
	jlbc	r1,1f	# parent, since r1 == 0 in parent, 1 in child
	calls	$0,_mach_init
	clrl	r0
1:
	ret		# pid = fork()
