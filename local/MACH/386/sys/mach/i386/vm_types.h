/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_types.h,v $
 * Revision 1.3  89/03/09  20:20:12  rpd
 * 	More cleanup.
 * 
 * Revision 1.2  89/02/26  13:01:20  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 * 23-Apr-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed things to "unsigned int" to appease the user community :-).
 *
 */

/*
 *	File:	vm_types.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Header file for VM data types.  I386 version.
 */

#ifndef	_MACH_I386_VM_TYPES_H_
#define _MACH_I386_VM_TYPES_H_

#ifdef	ASSEMBLER
#else	ASSEMBLER
typedef	unsigned int	vm_offset_t;
typedef	unsigned int	vm_size_t;
#endif	ASSEMBLER
#endif	_MACH_I386_VM_TYPES_H_
