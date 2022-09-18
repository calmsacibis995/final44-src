/* 
 * Mach Operating System
 * Copyright (c) 1992,1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	vm_types.h,v $
 * Revision 2.5  93/03/09  11:16:53  danner
 * 	Changed include conditional  to _MACHINE_VM_TYPES_H_ since
 * 	that is what sys/types.h is expecting.
 * 	[93/02/20            mrt]
 * 
 * Revision 2.4  93/01/14  17:48:54  danner
 * 	Standardized include symbol name.
 * 	[92/06/10            pds]
 * 	New (more) fundamental types.
 * 	Standardized conditional that controls multiple inclusion.
 * 	[92/06/03            af]
 * 
 * Revision 2.3  91/05/14  17:02:31  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/02/05  17:37:20  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:15:39  mrt]
 * 
 * Revision 2.1  89/08/03  16:02:00  rwd
 * Created.
 * 
 * Revision 2.3  89/02/25  18:42:11  gm0w
 * 	Changes for cleanup.
 * 
 * 23-Apr-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed things to "unsigned int" to appease the user community :-).
 *
 * 13-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vm_types.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1985
 *
 *	Header file for VM data types.  VAX version.
 */

#ifndef	_MACHINE_VM_TYPES_H_
#define	_MACHINE_VM_TYPES_H_	1


#ifdef	ASSEMBLER
#else	/* ASSEMBLER */

/*
 * A natural_t is the type for the native
 * integer type, e.g. 32 or 64 or.. whatever
 * register size the machine has.  Unsigned, it is
 * used for entities that might be either
 * unsigned integers or pointers, and for
 * type-casting between the two.
 * For instance, the IPC system represents
 * a port in user space as an integer and
 * in kernel space as a pointer.
 */
typedef unsigned int	natural_t;

/*
 * An integer_t is the signed counterpart
 * of the natural_t type. Both types are
 * only supposed to be used to define
 * other types in a machine-independent
 * way.
 */
typedef int		integer_t;

/*
 * An int32 is an integer that is at least 32 bits wide
 */
typedef int		int32;
typedef unsigned int	uint32;

/*
 * A vm_offset_t is a type-neutral pointer,
 * e.g. an offset into a virtual memory space.
 */
typedef	natural_t	vm_offset_t;

/*
 * A vm_size_t is the proper type for e.g.
 * expressing the difference between two
 * vm_offset_t entities.
 */
typedef	natural_t	vm_size_t;

#endif	/* ASSEMBLER  */
/*
 * If composing messages by hand (please dont)
 */

#define	MACH_MSG_TYPE_INTEGER_T	MACH_MSG_TYPE_INTEGER_32


#endif	/* _MACHINE_VM_TYPES_H_ */

