/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kern_return.h,v $
 * Revision 1.3  89/03/09  20:19:48  rpd
 * 	More cleanup.
 * 
 * Revision 1.2  89/02/26  13:00:54  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Allow inclusion in assembler input.
 *
 * 14-Oct-85  Michael Wayne Young (mwyoung) at Carnegie-Mellon University
 *	Created.
 */

/*
 *	File:	kern_return.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Machine-dependent kernel return definitions.
 */

#ifndef	_MACH_I386_KERN_RETURN_H_
#define _MACH_I386_KERN_RETURN_H_

#ifndef	ASSEMBLER
typedef	int		kern_return_t;
#endif	ASSEMBLER
#endif	_MACH_I386_KERN_RETURN_H_
