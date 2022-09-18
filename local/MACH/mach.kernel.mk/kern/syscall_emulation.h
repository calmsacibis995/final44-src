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
 * $Log:	syscall_emulation.h,v $
 * Revision 2.5  89/03/09  20:16:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:08:48  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  01:04:35  mwyoung
 * Relocated from sys/syscall_emulation.h
 * 
 * Revision 2.2  88/08/03  15:34:07  dorr
 * Get rid of errno and eosys fields.  Use return value and
 * special return code of ERESTART to represent same information.
 * 
 * 26-Jan-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Added maxsyscall variable and typedefs for user space emulation library
 *
 */ 

#ifndef	_KERN_SYSCALL_EMULATION_H_
#define _KERN_SYSCALL_EMULATION_H_

#define EML_MIN_SYSCALL		-9

#ifndef	ASSEMBLER
typedef	 unsigned long 	eml_routine_t;

typedef struct eml_dispatch {
	int		eml_ref;	/* reference count */
	int 		disp_count; 	/* count of entries in vector */
	eml_routine_t	disp_vector[1];	/* first entry in array (array is really disp_count large) */
					/* of dispatch routines */
} *eml_dispatch_t;

typedef struct syscall_val {
	int	rv_val1;
	int	rv_val2;
} syscall_val_t;


#define EML_ROUTINE_NULL	(eml_routine_t)0
#define EML_DISPATCH_NULL	(eml_dispatch_t)0

#define EML_SUCCESS		(0)

#define EML_MOD			(err_kern|err_sub(2))
#define EML_BAD_TASK		(EML_MOD|0x0001)
#define EML_BAD_CNT		(EML_MOD|0x0002)

#define EML_OFFSET(x)		((x)-EML_MIN_SYSCALL)

#endif	ASSEMBLER
#endif	_KERN_SYSCALL_EMULATION_H_
