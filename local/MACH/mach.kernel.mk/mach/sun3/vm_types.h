/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_types.h,v $
 * Revision 2.4  89/03/09  20:23:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:41:01  gm0w
 * 	Changes for cleanup.
 * 
 * 13-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Copied RT version for Sun 3.
 * 13-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 *	Header file for VM data types.  Sun version.
 */

#ifndef	_MACH_SUN3_VM_TYPES_H_
#define _MACH_SUN3_VM_TYPES_H_

#ifndef	ASSEMBLER
#ifndef	MACHINE_VM_TYPES_H_
#define MACHINE_VM_TYPES_H_

typedef	unsigned long	vm_offset_t;
typedef	unsigned long	vm_size_t;

#endif	MACHNE_VM_TYPES_H_
#endif	ASSEMBLER
#endif	_MACH_SUN3_VM_TYPES_H_
