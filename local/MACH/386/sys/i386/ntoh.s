/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ntoh.s,v $
 * Revision 2.1.1.2  90/02/27  08:47:37  rvb
 * 	Fixed for Profiling.  (You can only have one ENTRY() in a list
 * 	of Entry() points.  The .align's get you.)
 * 	[90/02/26            rvb]
 * 
 * Revision 2.1.1.1  89/10/22  11:31:16  rvb
 * 	New a.out and coff compatible .s files.
 * 	[89/10/16            rvb]
 * 
 * Revision 1.3  89/02/26  12:35:37  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Feb-89  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created.
 *
 */

#include <i386/asm.h>

Entry(ntohl)
ENTRY(htonl)
	movl	4(%esp), %eax
	rorw	$8, %ax
	ror	$16,%eax
	rorw	$8, %ax
	ret


Entry(ntohs)
ENTRY(htons)
	movzwl	4(%esp), %eax
	rorw	$8, %ax
	ret
