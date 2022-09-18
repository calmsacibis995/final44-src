/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	memory.h,v $
 * Revision 2.2  93/11/17  19:06:10  dbg
 * 	Created.
 * 	[93/09/28            dbg]
 * 
 */

#ifndef	_KERN_MEMORY_H_
#define	_KERN_MEMORY_H_

/*
 *	Clear a region of memory
 */
#ifndef	bzero				/* may be builtin */
extern void bzero(
	void *		dest,
	unsigned long	size);
#endif

/*
 *	Copy one region of memory to another
 */
#ifndef	bcopy				/* may be builtin */
extern void bcopy(
	const void *	src,
	void *		dest,
	unsigned long	size);
#endif

/*
 * Copy memory from user to kernel.
 * Returns non-zero if user memory inaccessible.
 */
extern int copyin(
	const void *	user_src,
	void *		kernel_dest,
	unsigned long	size);

/*
 * Copy memory from kernel to user.
 * Returns non-zero if user memory inaccessible.
 */
extern int copyout(
	const void *	kernel_src,
	void *		user_dest,
	unsigned long	size);

/*
 * Same as copyin, but memory must be 32-bit aligned.
 */
extern int copyinmsg(
	const void *	user_src,
	void *		kernel_dest,
	unsigned long	size);

/*
 * Same as copyout, but memory must be 32-bit aligned.
 */
extern int copyoutmsg(
	const void *	kernel_src,
	void *		user_dest,
	unsigned long	size);

#endif	/* _KERN_MEMORY_H_ */
