/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	stubs.s,v $
 * Revision 2.2  89/07/12  00:22:21  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
| 	stubs.s 	1.4	88/02/08

	.globl	_nullsys, _xxboot, _xxprobe, _ttboot
_nullsys:
_xxprobe:
_xxboot:
_ttboot:
	movl	#-1,d0
	rts
